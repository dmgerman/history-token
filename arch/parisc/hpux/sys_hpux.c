multiline_comment|/*&n; * linux/arch/parisc/kernel/sys_hpux.c&n; *&n; * implements HPUX syscalls.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_int
r_int
id|sys_brk
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|function|hpux_brk
r_int
r_int
id|hpux_brk
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* Sigh.  Looks like HP/UX libc relies on kernel bugs. */
r_return
id|sys_brk
c_func
(paren
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|hpux_sbrk
r_int
id|hpux_sbrk
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/* Random other syscalls */
DECL|function|hpux_nice
r_int
id|hpux_nice
c_func
(paren
r_int
id|priority_change
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|hpux_ptrace
r_int
id|hpux_ptrace
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|hpux_wait
r_int
id|hpux_wait
c_func
(paren
r_int
op_star
id|stat_loc
)paren
(brace
r_extern
r_int
id|sys_waitpid
c_func
(paren
r_int
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_return
id|sys_waitpid
c_func
(paren
op_minus
l_int|1
comma
id|stat_loc
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|_SC_CPU_VERSION
mdefine_line|#define _SC_CPU_VERSION&t;10001
DECL|macro|_SC_OPEN_MAX
mdefine_line|#define _SC_OPEN_MAX&t;4
DECL|macro|CPU_PA_RISC1_1
mdefine_line|#define CPU_PA_RISC1_1&t;0x210
DECL|function|hpux_sysconf
r_int
id|hpux_sysconf
c_func
(paren
r_int
id|which
)paren
(brace
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|_SC_CPU_VERSION
suffix:colon
r_return
id|CPU_PA_RISC1_1
suffix:semicolon
r_case
id|_SC_OPEN_MAX
suffix:colon
r_return
id|INT_MAX
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*****************************************************************************/
DECL|macro|HPUX_UTSLEN
mdefine_line|#define HPUX_UTSLEN 9
DECL|macro|HPUX_SNLEN
mdefine_line|#define HPUX_SNLEN 15
DECL|struct|hpux_utsname
r_struct
id|hpux_utsname
(brace
DECL|member|sysname
r_char
id|sysname
(braket
id|HPUX_UTSLEN
)braket
suffix:semicolon
DECL|member|nodename
r_char
id|nodename
(braket
id|HPUX_UTSLEN
)braket
suffix:semicolon
DECL|member|release
r_char
id|release
(braket
id|HPUX_UTSLEN
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|HPUX_UTSLEN
)braket
suffix:semicolon
DECL|member|machine
r_char
id|machine
(braket
id|HPUX_UTSLEN
)braket
suffix:semicolon
DECL|member|idnumber
r_char
id|idnumber
(braket
id|HPUX_SNLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hpux_ustat
r_struct
id|hpux_ustat
(brace
DECL|member|f_tfree
r_int32
id|f_tfree
suffix:semicolon
multiline_comment|/* total free (daddr_t)  */
DECL|member|f_tinode
id|u_int32_t
id|f_tinode
suffix:semicolon
multiline_comment|/* total inodes free (ino_t)  */
DECL|member|f_fname
r_char
id|f_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* filsys name */
DECL|member|f_fpack
r_char
id|f_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* filsys pack name */
DECL|member|f_blksize
id|u_int32_t
id|f_blksize
suffix:semicolon
multiline_comment|/* filsys block size (int) */
)brace
suffix:semicolon
multiline_comment|/*&n; * HPUX&squot;s utssys() call.  It&squot;s a collection of miscellaneous functions,&n; * alas, so there&squot;s no nice way of splitting them up.&n; */
multiline_comment|/*  This function is called from hpux_utssys(); HP-UX implements&n; *  ustat() as an option to utssys().&n; *&n; *  Now, struct ustat on HP-UX is exactly the same as on Linux, except&n; *  that it contains one addition field on the end, int32_t f_blksize.&n; *  So, we could have written this function to just call the Linux&n; *  sys_ustat(), (defined in linux/fs/super.c), and then just&n; *  added this additional field to the user&squot;s structure.  But I figure&n; *  if we&squot;re gonna be digging through filesystem structures to get&n; *  this, we might as well just do the whole enchilada all in one go.&n; *&n; *  So, most of this function is almost identical to sys_ustat().&n; *  I have placed comments at the few lines changed or added, to&n; *  aid in porting forward if and when sys_ustat() is changed from&n; *  its form in kernel 2.2.5.&n; */
DECL|function|hpux_ustat
r_static
r_int
id|hpux_ustat
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|hpux_ustat
op_star
id|ubuf
)paren
(brace
r_struct
id|super_block
op_star
id|s
suffix:semicolon
r_struct
id|hpux_ustat
id|tmp
suffix:semicolon
multiline_comment|/* Changed to hpux_ustat */
r_struct
id|statfs
id|sbuf
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|s
op_assign
id|get_super
c_func
(paren
id|to_kdev_t
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|vfs_statfs
c_func
(paren
id|s
comma
op_amp
id|sbuf
)paren
suffix:semicolon
id|drop_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hpux_ustat
)paren
)paren
suffix:semicolon
multiline_comment|/* Changed to hpux_ustat */
id|tmp.f_tfree
op_assign
(paren
r_int32
)paren
id|sbuf.f_bfree
suffix:semicolon
id|tmp.f_tinode
op_assign
(paren
id|u_int32_t
)paren
id|sbuf.f_ffree
suffix:semicolon
id|tmp.f_blksize
op_assign
(paren
id|u_int32_t
)paren
id|sbuf.f_bsize
suffix:semicolon
multiline_comment|/*  Added this line  */
multiline_comment|/* Changed to hpux_ustat:  */
id|err
op_assign
id|copy_to_user
c_func
(paren
id|ubuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
r_struct
id|hpux_ustat
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*  This function is called from hpux_utssys(); HP-UX implements&n; *  uname() as an option to utssys().&n; *&n; *  The form of this function is pretty much copied from sys_olduname(),&n; *  defined in linux/arch/i386/kernel/sys_i386.c.&n; */
multiline_comment|/*  TODO: Are these put_user calls OK?  Should they pass an int?&n; *        (I copied it from sys_i386.c like this.)&n; */
DECL|function|hpux_uname
r_static
r_int
id|hpux_uname
c_func
(paren
r_struct
id|hpux_utsname
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
(paren
r_struct
id|hpux_utsname
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|system_utsname.sysname
comma
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;sysname
op_plus
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|system_utsname.nodename
comma
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;nodename
op_plus
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|system_utsname.release
comma
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;release
op_plus
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|system_utsname.version
comma
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;version
op_plus
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|system_utsname.machine
comma
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;machine
op_plus
id|HPUX_UTSLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
multiline_comment|/*  HP-UX  utsname has no domainname field.  */
multiline_comment|/*  TODO:  Implement idnumber!!!  */
macro_line|#if 0
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;idnumber
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;idnumber
op_plus
id|HPUX_SNLEN
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_int
id|sys_sethostname
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|sys_gethostname
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*  Note: HP-UX just uses the old suser() function to check perms&n; *  in this system call.  We&squot;ll use capable(CAP_SYS_ADMIN).&n; */
DECL|function|hpux_utssys
r_int
id|hpux_utssys
c_func
(paren
r_char
op_star
id|ubuf
comma
r_int
id|n
comma
r_int
id|type
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
id|error
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*  uname():  */
r_return
id|hpux_uname
c_func
(paren
(paren
r_struct
id|hpux_utsname
op_star
)paren
id|ubuf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/*  Obsolete (used to be umask().)  */
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/*  ustat():  */
r_return
id|hpux_ustat
c_func
(paren
(paren
id|dev_t
)paren
id|n
comma
(paren
r_struct
id|hpux_ustat
op_star
)paren
id|ubuf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/*  setuname():&n;&t;&t; *&n;&t;&t; *  On linux (unlike HP-UX), utsname.nodename&n;&t;&t; *  is the same as the hostname.&n;&t;&t; *&n;&t;&t; *  sys_sethostname() is defined in linux/kernel/sys.c.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX returns an error if n==0:  */
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX truncates it if n is too big:  */
id|len
op_assign
(paren
id|n
op_le
id|__NEW_UTS_LEN
)paren
ques
c_cond
id|n
suffix:colon
id|__NEW_UTS_LEN
suffix:semicolon
r_return
id|sys_sethostname
c_func
(paren
id|ubuf
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/*  sethostname():&n;&t;&t; *&n;&t;&t; *  sys_sethostname() is defined in linux/kernel/sys.c.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX returns an error if n==0:  */
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX truncates it if n is too big:  */
id|len
op_assign
(paren
id|n
op_le
id|__NEW_UTS_LEN
)paren
ques
c_cond
id|n
suffix:colon
id|__NEW_UTS_LEN
suffix:semicolon
r_return
id|sys_sethostname
c_func
(paren
id|ubuf
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/*  gethostname():&n;&t;&t; *&n;&t;&t; *  sys_gethostname() is defined in linux/kernel/sys.c.&n;&t;&t; */
multiline_comment|/*  Unlike Linux, HP-UX returns an error if n==0:  */
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sys_gethostname
c_func
(paren
id|ubuf
comma
id|n
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/*  Supposedly called from setuname() in libc.&n;&t;&t; *  TODO: When and why is this called?&n;&t;&t; *        Is it ever even called?&n;&t;&t; *&n;&t;&t; *  This code should look a lot like sys_sethostname(),&n;&t;&t; *  defined in linux/kernel/sys.c.  If that gets updated,&n;&t;&t; *  update this code similarly.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX returns an error if n==0:  */
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX truncates it if n is too big:  */
id|len
op_assign
(paren
id|n
op_le
id|__NEW_UTS_LEN
)paren
ques
c_cond
id|n
suffix:colon
id|__NEW_UTS_LEN
suffix:semicolon
multiline_comment|/**/
multiline_comment|/*  TODO:  print a warning about using this?  */
id|down_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_from_user
c_func
(paren
id|system_utsname.sysname
comma
id|ubuf
comma
id|len
)paren
)paren
(brace
id|system_utsname.sysname
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/*  Sets utsname.release, if you&squot;re allowed.&n;&t;&t; *  Undocumented.  Used by swinstall to change the&n;&t;&t; *  OS version, during OS updates.  Yuck!!!&n;&t;&t; *&n;&t;&t; *  This code should look a lot like sys_sethostname()&n;&t;&t; *  in linux/kernel/sys.c.  If that gets updated, update&n;&t;&t; *  this code similarly.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX returns an error if n==0:  */
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Unlike Linux, HP-UX truncates it if n is too big:  */
id|len
op_assign
(paren
id|n
op_le
id|__NEW_UTS_LEN
)paren
ques
c_cond
id|n
suffix:colon
id|__NEW_UTS_LEN
suffix:semicolon
multiline_comment|/**/
multiline_comment|/*  TODO:  print a warning about this?  */
id|down_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_from_user
c_func
(paren
id|system_utsname.release
comma
id|ubuf
comma
id|len
)paren
)paren
(brace
id|system_utsname.release
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*  This system call returns -EFAULT if given an unknown type.&n;&t; &t; *  Why not -EINVAL?  I don&squot;t know, it&squot;s just not what they did.&n;&t; &t; */
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
DECL|function|hpux_getdomainname
r_int
id|hpux_getdomainname
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|nlen
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|nlen
op_assign
id|strlen
c_func
(paren
id|system_utsname.domainname
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nlen
OL
id|len
)paren
id|len
op_assign
id|nlen
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|__NEW_UTS_LEN
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|name
comma
id|system_utsname.domainname
comma
id|len
)paren
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|done
suffix:colon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hpux_pipe
r_int
id|hpux_pipe
c_func
(paren
r_int
op_star
id|kstack_fildes
)paren
(brace
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|do_pipe
c_func
(paren
id|kstack_fildes
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
