multiline_comment|/*&n; *  linux/kernel/acct.c&n; *&n; *  BSD Process Accounting for Linux&n; *&n; *  Author: Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; *  Some code based on ideas and code from:&n; *  Thomas K. Dyas &lt;tdyas@eden.rutgers.edu&gt;&n; *&n; *  This file implements BSD-style process accounting. Whenever any&n; *  process exits, an accounting record of type &quot;struct acct&quot; is&n; *  written to the file specified with the acct() system call. It is&n; *  up to user-level programs to do useful things with the accounting&n; *  log. The kernel just provides the raw accounting information.&n; *&n; * (C) Copyright 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.&n; *&n; *  Plugged two leaks. 1) It didn&squot;t return acct_file into the free_filps if&n; *  the file happened to be read-only. 2) If the accounting was suspended&n; *  due to the lack of space it happily allowed to reopen it and completely&n; *  lost the old acct_file. 3/10/98, Al Viro.&n; *&n; *  Now we silently close acct_file on attempt to reopen. Cleaned sys_acct().&n; *  XTerms and EMACS are manifestations of pure evil. 21/10/98, AV.&n; *&n; *  Fixed a nasty interaction with with sys_umount(). If the accointing&n; *  was suspeneded we failed to stop it on umount(). Messy.&n; *  Another one: remount to readonly didn&squot;t stop accounting.&n; *&t;Question: what should we do if we have CAP_SYS_ADMIN but not&n; *  CAP_SYS_PACCT? Current code does the following: umount returns -EBUSY&n; *  unless we are messing with the root. In that case we are getting a&n; *  real mess with do_remount_sb(). 9/11/98, AV.&n; *&n; *  Fixed a bunch of races (and pair of leaks). Probably not the best way,&n; *  but this one obviously doesn&squot;t introduce deadlocks. Later. BTW, found&n; *  one race (and leak) in BSD implementation.&n; *  OK, that&squot;s better. ANOTHER race and leak in BSD variant. There always&n; *  is one more bug... 10/11/98, AV.&n; *&n; *&t;Oh, fsck... Oopsable SMP race in do_process_acct() - we must hold&n; * -&gt;mmap_sem to walk the vma list of current-&gt;mm. Nasty, since it leaks&n; * a struct file opened for write. Fixed. 2/6/2000, AV.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/acct.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt; /* sector_div */
multiline_comment|/*&n; * These constants control the amount of freespace that suspend and&n; * resume the process accounting system, and the time delay between&n; * each check.&n; * Turned into sysctl-controllable parameters. AV, 12/11/98&n; */
DECL|variable|acct_parm
r_int
id|acct_parm
(braket
l_int|3
)braket
op_assign
(brace
l_int|4
comma
l_int|2
comma
l_int|30
)brace
suffix:semicolon
DECL|macro|RESUME
mdefine_line|#define RESUME&t;&t;(acct_parm[0])&t;/* &gt;foo% free space - resume */
DECL|macro|SUSPEND
mdefine_line|#define SUSPEND&t;&t;(acct_parm[1])&t;/* &lt;foo% free space - suspend */
DECL|macro|ACCT_TIMEOUT
mdefine_line|#define ACCT_TIMEOUT&t;(acct_parm[2])&t;/* foo second timeout between checks */
multiline_comment|/*&n; * External references and all of the globals.&n; */
r_static
r_void
id|do_acct_process
c_func
(paren
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This structure is used so that all the data protected by lock&n; * can be placed in the same cache line as the lock.  This primes&n; * the cache line to have the data after getting the lock.&n; */
DECL|struct|acct_glbs
r_struct
id|acct_glbs
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|active
r_volatile
r_int
id|active
suffix:semicolon
DECL|member|needcheck
r_volatile
r_int
id|needcheck
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__cacheline_aligned
r_static
r_struct
id|acct_glbs
id|acct_globals
id|__cacheline_aligned
op_assign
(brace
id|SPIN_LOCK_UNLOCKED
)brace
suffix:semicolon
multiline_comment|/*&n; * Called whenever the timer says to check the free space.&n; */
DECL|function|acct_timeout
r_static
r_void
id|acct_timeout
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
id|acct_globals.needcheck
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the amount of free space and suspend/resume accordingly.&n; */
DECL|function|check_free_space
r_static
r_int
id|check_free_space
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|kstatfs
id|sbuf
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
id|act
suffix:semicolon
id|sector_t
id|resume
suffix:semicolon
id|sector_t
id|suspend
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
id|res
op_assign
id|acct_globals.active
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
op_logical_or
op_logical_neg
id|acct_globals.needcheck
)paren
r_goto
id|out
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
multiline_comment|/* May block */
r_if
c_cond
(paren
id|vfs_statfs
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sb
comma
op_amp
id|sbuf
)paren
)paren
r_return
id|res
suffix:semicolon
id|suspend
op_assign
id|sbuf.f_blocks
op_star
id|SUSPEND
suffix:semicolon
id|resume
op_assign
id|sbuf.f_blocks
op_star
id|RESUME
suffix:semicolon
id|sector_div
c_func
(paren
id|suspend
comma
l_int|100
)paren
suffix:semicolon
id|sector_div
c_func
(paren
id|resume
comma
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbuf.f_bavail
op_le
id|suspend
)paren
id|act
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbuf.f_bavail
op_ge
id|resume
)paren
id|act
op_assign
l_int|1
suffix:semicolon
r_else
id|act
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If some joker switched acct_globals.file under us we&squot;ld better be&n;&t; * silent and _not_ touch anything.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
op_ne
id|acct_globals.file
)paren
(brace
r_if
c_cond
(paren
id|act
)paren
id|res
op_assign
id|act
OG
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acct_globals.active
)paren
(brace
r_if
c_cond
(paren
id|act
OL
l_int|0
)paren
(brace
id|acct_globals.active
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Process accounting paused&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|act
OG
l_int|0
)paren
(brace
id|acct_globals.active
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Process accounting resumed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|del_timer
c_func
(paren
op_amp
id|acct_globals.timer
)paren
suffix:semicolon
id|acct_globals.needcheck
op_assign
l_int|0
suffix:semicolon
id|acct_globals.timer.expires
op_assign
id|jiffies
op_plus
id|ACCT_TIMEOUT
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|acct_globals.timer
)paren
suffix:semicolon
id|res
op_assign
id|acct_globals.active
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Close the old accouting file (if currently open) and then replace&n; * it with file (if non-NULL).&n; *&n; * NOTE: acct_globals.lock MUST be held on entry and exit.&n; */
DECL|function|acct_file_reopen
r_void
id|acct_file_reopen
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|file
op_star
id|old_acct
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|acct_globals.file
)paren
(brace
id|old_acct
op_assign
id|acct_globals.file
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|acct_globals.timer
)paren
suffix:semicolon
id|acct_globals.active
op_assign
l_int|0
suffix:semicolon
id|acct_globals.needcheck
op_assign
l_int|0
suffix:semicolon
id|acct_globals.file
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file
)paren
(brace
id|acct_globals.file
op_assign
id|file
suffix:semicolon
id|acct_globals.needcheck
op_assign
l_int|0
suffix:semicolon
id|acct_globals.active
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* It&squot;s been deleted if it was used before so this is safe */
id|init_timer
c_func
(paren
op_amp
id|acct_globals.timer
)paren
suffix:semicolon
id|acct_globals.timer.function
op_assign
id|acct_timeout
suffix:semicolon
id|acct_globals.timer.expires
op_assign
id|jiffies
op_plus
id|ACCT_TIMEOUT
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|acct_globals.timer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_acct
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
id|do_acct_process
c_func
(paren
l_int|0
comma
id|old_acct
)paren
suffix:semicolon
id|filp_close
c_func
(paren
id|old_acct
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  sys_acct() is the only system call needed to implement process&n; *  accounting. It takes the name of the file where accounting records&n; *  should be written. If the filename is NULL, accounting will be&n; *  shutdown.&n; */
DECL|function|sys_acct
id|asmlinkage
r_int
id|sys_acct
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_PACCT
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
id|tmp
op_assign
id|getname
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|tmp
)paren
)paren
(brace
r_return
(paren
id|PTR_ERR
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Difference from BSD - they don&squot;t do O_APPEND */
id|file
op_assign
id|filp_open
c_func
(paren
id|tmp
comma
id|O_WRONLY
op_or
id|O_APPEND
comma
l_int|0
)paren
suffix:semicolon
id|putname
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|file
)paren
)paren
(brace
r_return
(paren
id|PTR_ERR
c_func
(paren
id|file
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
id|filp_close
c_func
(paren
id|file
comma
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op-&gt;write
)paren
(brace
id|filp_close
c_func
(paren
id|file
comma
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
)brace
id|error
op_assign
id|security_acct
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
id|acct_file_reopen
c_func
(paren
id|file
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If the accouting is turned on for a file in the filesystem pointed&n; * to by sb, turn accouting off.&n; */
DECL|function|acct_auto_close
r_void
id|acct_auto_close
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acct_globals.file
op_logical_and
id|acct_globals.file-&gt;f_dentry-&gt;d_inode-&gt;i_sb
op_eq
id|sb
)paren
(brace
id|acct_file_reopen
c_func
(paren
(paren
r_struct
id|file
op_star
)paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  encode an unsigned long into a comp_t&n; *&n; *  This routine has been adopted from the encode_comp_t() function in&n; *  the kern_acct.c file of the FreeBSD operating system. The encoding&n; *  is a 13-bit fraction with a 3-bit (base 8) exponent.&n; */
DECL|macro|MANTSIZE
mdefine_line|#define&t;MANTSIZE&t;13&t;&t;&t;/* 13 bit mantissa. */
DECL|macro|EXPSIZE
mdefine_line|#define&t;EXPSIZE&t;&t;3&t;&t;&t;/* Base 8 (3 bit) exponent. */
DECL|macro|MAXFRACT
mdefine_line|#define&t;MAXFRACT&t;((1 &lt;&lt; MANTSIZE) - 1)&t;/* Maximum fractional value. */
DECL|function|encode_comp_t
r_static
id|comp_t
id|encode_comp_t
c_func
(paren
r_int
r_int
id|value
)paren
(brace
r_int
id|exp
comma
id|rnd
suffix:semicolon
id|exp
op_assign
id|rnd
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|value
OG
id|MAXFRACT
)paren
(brace
id|rnd
op_assign
id|value
op_amp
(paren
l_int|1
op_lshift
(paren
id|EXPSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Round up? */
id|value
op_rshift_assign
id|EXPSIZE
suffix:semicolon
multiline_comment|/* Base 8 exponent == 3 bit shift. */
id|exp
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * If we need to round up, do it (and handle overflow correctly).&n;         */
r_if
c_cond
(paren
id|rnd
op_logical_and
(paren
op_increment
id|value
OG
id|MAXFRACT
)paren
)paren
(brace
id|value
op_rshift_assign
id|EXPSIZE
suffix:semicolon
id|exp
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * Clean it up and polish it off.&n;         */
id|exp
op_lshift_assign
id|MANTSIZE
suffix:semicolon
multiline_comment|/* Shift the exponent into place */
id|exp
op_add_assign
id|value
suffix:semicolon
multiline_comment|/* and add on the mantissa. */
r_return
id|exp
suffix:semicolon
)brace
multiline_comment|/*&n; *  Write an accounting entry for an exiting process&n; *&n; *  The acct_process() call is the workhorse of the process&n; *  accounting system. The struct acct is built here and then written&n; *  into the accounting file. This function should only be called from&n; *  do_exit().&n; */
multiline_comment|/*&n; *  do_acct_process does all actual work. Caller holds the reference to file.&n; */
DECL|function|do_acct_process
r_static
r_void
id|do_acct_process
c_func
(paren
r_int
id|exitcode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|acct
id|ac
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_int
r_int
id|vsize
suffix:semicolon
r_int
r_int
id|flim
suffix:semicolon
id|u64
id|elapsed
suffix:semicolon
multiline_comment|/*&n;&t; * First check to see if there is enough free_space to continue&n;&t; * the process accounting system.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|check_free_space
c_func
(paren
id|file
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Fill the accounting struct with the needed info as recorded&n;&t; * by the different kernel functions.&n;&t; */
id|memset
c_func
(paren
(paren
id|caddr_t
)paren
op_amp
id|ac
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acct
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|ac.ac_comm
comma
id|current-&gt;comm
comma
r_sizeof
(paren
id|ac.ac_comm
)paren
)paren
suffix:semicolon
id|elapsed
op_assign
id|get_jiffies_64
c_func
(paren
)paren
op_minus
id|current-&gt;start_time
suffix:semicolon
id|ac.ac_etime
op_assign
id|encode_comp_t
c_func
(paren
id|elapsed
OL
(paren
r_int
r_int
)paren
op_minus
l_int|1l
ques
c_cond
(paren
r_int
r_int
)paren
id|elapsed
suffix:colon
(paren
r_int
r_int
)paren
op_minus
l_int|1l
)paren
suffix:semicolon
id|do_div
c_func
(paren
id|elapsed
comma
id|HZ
)paren
suffix:semicolon
id|ac.ac_btime
op_assign
id|xtime.tv_sec
op_minus
id|elapsed
suffix:semicolon
id|ac.ac_utime
op_assign
id|encode_comp_t
c_func
(paren
id|current-&gt;utime
)paren
suffix:semicolon
id|ac.ac_stime
op_assign
id|encode_comp_t
c_func
(paren
id|current-&gt;stime
)paren
suffix:semicolon
id|ac.ac_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|ac.ac_gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|ac.ac_tty
op_assign
id|current-&gt;tty
ques
c_cond
id|tty_devnum
c_func
(paren
id|current-&gt;tty
)paren
suffix:colon
l_int|0
suffix:semicolon
id|ac.ac_flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FORKNOEXEC
)paren
id|ac.ac_flag
op_or_assign
id|AFORK
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_SUPERPRIV
)paren
id|ac.ac_flag
op_or_assign
id|ASU
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_DUMPCORE
)paren
id|ac.ac_flag
op_or_assign
id|ACORE
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_SIGNALED
)paren
id|ac.ac_flag
op_or_assign
id|AXSIG
suffix:semicolon
id|vsize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|vma
)paren
(brace
id|vsize
op_add_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
id|vsize
op_assign
id|vsize
op_div
l_int|1024
suffix:semicolon
id|ac.ac_mem
op_assign
id|encode_comp_t
c_func
(paren
id|vsize
)paren
suffix:semicolon
id|ac.ac_io
op_assign
id|encode_comp_t
c_func
(paren
l_int|0
multiline_comment|/* current-&gt;io_usage */
)paren
suffix:semicolon
multiline_comment|/* %% */
id|ac.ac_rw
op_assign
id|encode_comp_t
c_func
(paren
id|ac.ac_io
op_div
l_int|1024
)paren
suffix:semicolon
id|ac.ac_minflt
op_assign
id|encode_comp_t
c_func
(paren
id|current-&gt;min_flt
)paren
suffix:semicolon
id|ac.ac_majflt
op_assign
id|encode_comp_t
c_func
(paren
id|current-&gt;maj_flt
)paren
suffix:semicolon
id|ac.ac_swaps
op_assign
id|encode_comp_t
c_func
(paren
id|current-&gt;nswap
)paren
suffix:semicolon
id|ac.ac_exitcode
op_assign
id|exitcode
suffix:semicolon
multiline_comment|/*&n;         * Kernel segment override to datasegment and write it&n;         * to the accounting file.&n;         */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * Accounting records are not subject to resource limits.&n; &t; */
id|flim
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
suffix:semicolon
id|current-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
op_assign
id|RLIM_INFINITY
suffix:semicolon
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
(paren
r_char
op_star
)paren
op_amp
id|ac
comma
r_sizeof
(paren
r_struct
id|acct
)paren
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
id|current-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
op_assign
id|flim
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * acct_process - now just a wrapper around do_acct_process&n; */
DECL|function|acct_process
r_void
id|acct_process
c_func
(paren
r_int
id|exitcode
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * accelerate the common fastpath:&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acct_globals.file
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
id|file
op_assign
id|acct_globals.file
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|file
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acct_globals.lock
)paren
suffix:semicolon
id|do_acct_process
c_func
(paren
id|exitcode
comma
id|file
)paren
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
eof
