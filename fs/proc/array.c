multiline_comment|/*&n; *  linux/fs/proc/array.c&n; *&n; *  Copyright (C) 1992  by Linus Torvalds&n; *  based on ideas by Darren Senn&n; *&n; * Fixes:&n; * Michael. K. Johnson: stat,statm extensions.&n; *                      &lt;johnsonm@stolaf.edu&gt;&n; *&n; * Pauline Middelink :  Made cmdline,envline only break at &squot;&bslash;0&squot;s, to&n; *                      make sure SET_PROCTITLE works. Also removed&n; *                      bad &squot;!&squot; which forced address recalculation for&n; *                      EVERY character on the current page.&n; *                      &lt;middelin@polyware.iaf.nl&gt;&n; *&n; * Danny ter Haar    :&t;added cpuinfo&n; *&t;&t;&t;&lt;dth@cistron.nl&gt;&n; *&n; * Alessandro Rubini :  profile extension.&n; *                      &lt;rubini@ipvvis.unipv.it&gt;&n; *&n; * Jeff Tranter      :  added BogoMips field to cpuinfo&n; *                      &lt;Jeff_Tranter@Mitel.COM&gt;&n; *&n; * Bruno Haible      :  remove 4K limit for the maps file&n; *&t;&t;&t;&lt;haible@ma2s2.mathematik.uni-karlsruhe.de&gt;&n; *&n; * Yves Arrouye      :  remove removal of trailing spaces in get_array.&n; *&t;&t;&t;&lt;Yves.Arrouye@marin.fdn.fr&gt;&n; *&n; * Jerome Forissier  :  added per-CPU time information to /proc/stat&n; *                      and /proc/&lt;pid&gt;/cpu extension&n; *                      &lt;forissier@isia.cma.fr&gt;&n; *&t;&t;&t;- Incorporation and non-SMP safe operation&n; *&t;&t;&t;of forissier patch in 2.1.78 by&n; *&t;&t;&t;Hans Marcus &lt;crowbar@concepts.nl&gt;&n; *&n; * aeb@cwi.nl        :  /proc/partitions&n; *&n; *&n; * Alan Cox&t;     :  security fixes.&n; *&t;&t;&t;&lt;Alan.Cox@linux.org&gt;&n; *&n; * Al Viro           :  safe handling of mm_struct&n; *&n; * Gerhard Wichert   :  added BIGMEM support&n; * Siemens AG           &lt;Gerhard.Wichert@pdb.siemens.de&gt;&n; *&n; * Al Viro &amp; Jeff Garzik :  moved most of the thing into base.c and&n; *&t;&t;&t; :  proc_misc.c. The rest may eventually go into&n; *&t;&t;&t; :  base.c too.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* Gcc optimizes away &quot;strlen(x)&quot; for constant x */
DECL|macro|ADDBUF
mdefine_line|#define ADDBUF(buffer, string) &bslash;&n;do { memcpy(buffer, string, strlen(string)); &bslash;&n;     buffer += strlen(string); } while (0)
DECL|function|task_name
r_static
r_inline
r_char
op_star
id|task_name
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_char
id|tcomm
(braket
r_sizeof
(paren
id|p-&gt;comm
)paren
)braket
suffix:semicolon
id|get_task_comm
c_func
(paren
id|tcomm
comma
id|p
)paren
suffix:semicolon
id|ADDBUF
c_func
(paren
id|buf
comma
l_string|&quot;Name:&bslash;t&quot;
)paren
suffix:semicolon
id|name
op_assign
id|tcomm
suffix:semicolon
id|i
op_assign
r_sizeof
(paren
id|tcomm
)paren
suffix:semicolon
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|name
suffix:semicolon
id|name
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
op_star
id|buf
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_assign
id|c
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|buf
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|buf
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The task state array is a strange &quot;bitmap&quot; of&n; * reasons to sleep. Thus &quot;running&quot; is zero, and&n; * you can test for combinations of others with&n; * simple bit tests.&n; */
DECL|variable|task_state_array
r_static
r_const
r_char
op_star
id|task_state_array
(braket
)braket
op_assign
(brace
l_string|&quot;R (running)&quot;
comma
multiline_comment|/*  0 */
l_string|&quot;S (sleeping)&quot;
comma
multiline_comment|/*  1 */
l_string|&quot;D (disk sleep)&quot;
comma
multiline_comment|/*  2 */
l_string|&quot;T (stopped)&quot;
comma
multiline_comment|/*  4 */
l_string|&quot;T (tracing stop)&quot;
comma
multiline_comment|/*  8 */
l_string|&quot;Z (zombie)&quot;
comma
multiline_comment|/* 16 */
l_string|&quot;X (dead)&quot;
multiline_comment|/* 32 */
)brace
suffix:semicolon
DECL|function|get_task_state
r_static
r_inline
r_const
r_char
op_star
id|get_task_state
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|state
op_assign
(paren
id|tsk-&gt;state
op_amp
(paren
id|TASK_RUNNING
op_or
id|TASK_INTERRUPTIBLE
op_or
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_STOPPED
op_or
id|TASK_TRACED
)paren
)paren
op_or
(paren
id|tsk-&gt;exit_state
op_amp
(paren
id|EXIT_ZOMBIE
op_or
id|EXIT_DEAD
)paren
)paren
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
op_assign
op_amp
id|task_state_array
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|state
)paren
(brace
id|p
op_increment
suffix:semicolon
id|state
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
op_star
id|p
suffix:semicolon
)brace
DECL|function|task_state
r_static
r_inline
r_char
op_star
id|task_state
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|group_info
op_star
id|group_info
suffix:semicolon
r_int
id|g
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;State:&bslash;t%s&bslash;n&quot;
l_string|&quot;SleepAVG:&bslash;t%lu%%&bslash;n&quot;
l_string|&quot;Tgid:&bslash;t%d&bslash;n&quot;
l_string|&quot;Pid:&bslash;t%d&bslash;n&quot;
l_string|&quot;PPid:&bslash;t%d&bslash;n&quot;
l_string|&quot;TracerPid:&bslash;t%d&bslash;n&quot;
l_string|&quot;Uid:&bslash;t%d&bslash;t%d&bslash;t%d&bslash;t%d&bslash;n&quot;
l_string|&quot;Gid:&bslash;t%d&bslash;t%d&bslash;t%d&bslash;t%d&bslash;n&quot;
comma
id|get_task_state
c_func
(paren
id|p
)paren
comma
(paren
id|p-&gt;sleep_avg
op_div
l_int|1024
)paren
op_star
l_int|100
op_div
(paren
l_int|1020000000
op_div
l_int|1024
)paren
comma
id|p-&gt;tgid
comma
id|p-&gt;pid
comma
id|pid_alive
c_func
(paren
id|p
)paren
ques
c_cond
id|p-&gt;group_leader-&gt;real_parent-&gt;tgid
suffix:colon
l_int|0
comma
id|pid_alive
c_func
(paren
id|p
)paren
op_logical_and
id|p-&gt;ptrace
ques
c_cond
id|p-&gt;parent-&gt;pid
suffix:colon
l_int|0
comma
id|p-&gt;uid
comma
id|p-&gt;euid
comma
id|p-&gt;suid
comma
id|p-&gt;fsuid
comma
id|p-&gt;gid
comma
id|p-&gt;egid
comma
id|p-&gt;sgid
comma
id|p-&gt;fsgid
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;FDSize:&bslash;t%d&bslash;n&quot;
l_string|&quot;Groups:&bslash;t&quot;
comma
id|p-&gt;files
ques
c_cond
id|p-&gt;files-&gt;max_fds
suffix:colon
l_int|0
)paren
suffix:semicolon
id|group_info
op_assign
id|p-&gt;group_info
suffix:semicolon
id|get_group_info
c_func
(paren
id|group_info
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
r_for
c_loop
(paren
id|g
op_assign
l_int|0
suffix:semicolon
id|g
OL
id|min
c_func
(paren
id|group_info-&gt;ngroups
comma
id|NGROUPS_SMALL
)paren
suffix:semicolon
id|g
op_increment
)paren
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d &quot;
comma
id|GROUP_AT
c_func
(paren
id|group_info
comma
id|g
)paren
)paren
suffix:semicolon
id|put_group_info
c_func
(paren
id|group_info
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|render_sigset_t
r_static
r_char
op_star
id|render_sigset_t
c_func
(paren
r_const
r_char
op_star
id|header
comma
id|sigset_t
op_star
id|set
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|header
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|header
comma
id|len
)paren
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
id|i
op_assign
id|_NSIG
suffix:semicolon
r_do
(brace
r_int
id|x
op_assign
l_int|0
suffix:semicolon
id|i
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|sigismember
c_func
(paren
id|set
comma
id|i
op_plus
l_int|1
)paren
)paren
id|x
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sigismember
c_func
(paren
id|set
comma
id|i
op_plus
l_int|2
)paren
)paren
id|x
op_or_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|sigismember
c_func
(paren
id|set
comma
id|i
op_plus
l_int|3
)paren
)paren
id|x
op_or_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|sigismember
c_func
(paren
id|set
comma
id|i
op_plus
l_int|4
)paren
)paren
id|x
op_or_assign
l_int|8
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
(paren
id|x
OL
l_int|10
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot;a&squot;
op_minus
l_int|10
)paren
op_plus
id|x
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ge
l_int|4
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
op_star
id|buffer
op_assign
l_int|0
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|collect_sigign_sigcatch
r_static
r_void
id|collect_sigign_sigcatch
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
id|sigset_t
op_star
id|ign
comma
id|sigset_t
op_star
r_catch
)paren
(brace
r_struct
id|k_sigaction
op_star
id|k
suffix:semicolon
r_int
id|i
suffix:semicolon
id|k
op_assign
id|p-&gt;sighand-&gt;action
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|_NSIG
suffix:semicolon
op_increment
id|i
comma
op_increment
id|k
)paren
(brace
r_if
c_cond
(paren
id|k-&gt;sa.sa_handler
op_eq
id|SIG_IGN
)paren
id|sigaddset
c_func
(paren
id|ign
comma
id|i
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|k-&gt;sa.sa_handler
op_ne
id|SIG_DFL
)paren
id|sigaddset
c_func
(paren
r_catch
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|task_sig
r_static
r_inline
r_char
op_star
id|task_sig
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
id|sigset_t
id|pending
comma
id|shpending
comma
id|blocked
comma
id|ignored
comma
id|caught
suffix:semicolon
r_int
id|num_threads
op_assign
l_int|0
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|pending
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|shpending
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|blocked
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|ignored
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|caught
)paren
suffix:semicolon
multiline_comment|/* Gather all the data with the appropriate locks held */
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sighand
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|p-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|pending
op_assign
id|p-&gt;pending.signal
suffix:semicolon
id|shpending
op_assign
id|p-&gt;signal-&gt;shared_pending.signal
suffix:semicolon
id|blocked
op_assign
id|p-&gt;blocked
suffix:semicolon
id|collect_sigign_sigcatch
c_func
(paren
id|p
comma
op_amp
id|ignored
comma
op_amp
id|caught
)paren
suffix:semicolon
id|num_threads
op_assign
id|atomic_read
c_func
(paren
op_amp
id|p-&gt;signal-&gt;count
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|p-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Threads:&bslash;t%d&bslash;n&quot;
comma
id|num_threads
)paren
suffix:semicolon
multiline_comment|/* render them all */
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
l_string|&quot;SigPnd:&bslash;t&quot;
comma
op_amp
id|pending
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
l_string|&quot;ShdPnd:&bslash;t&quot;
comma
op_amp
id|shpending
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
l_string|&quot;SigBlk:&bslash;t&quot;
comma
op_amp
id|blocked
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
l_string|&quot;SigIgn:&bslash;t&quot;
comma
op_amp
id|ignored
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
l_string|&quot;SigCgt:&bslash;t&quot;
comma
op_amp
id|caught
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|task_cap
r_static
r_inline
r_char
op_star
id|task_cap
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
r_return
id|buffer
op_plus
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;CapInh:&bslash;t%016x&bslash;n&quot;
l_string|&quot;CapPrm:&bslash;t%016x&bslash;n&quot;
l_string|&quot;CapEff:&bslash;t%016x&bslash;n&quot;
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_inheritable
)paren
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_permitted
)paren
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_effective
)paren
)paren
suffix:semicolon
)brace
DECL|function|proc_pid_status
r_int
id|proc_pid_status
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_char
op_star
id|orig
op_assign
id|buffer
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
id|buffer
op_assign
id|task_name
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|task_state
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|buffer
op_assign
id|task_mem
c_func
(paren
id|mm
comma
id|buffer
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|task_sig
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|task_cap
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_S390)
id|buffer
op_assign
id|task_show_regs
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
macro_line|#endif
r_return
id|buffer
op_minus
id|orig
suffix:semicolon
)brace
DECL|function|do_task_stat
r_static
r_int
id|do_task_stat
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
comma
r_int
id|whole
)paren
(brace
r_int
r_int
id|vsize
comma
id|eip
comma
id|esp
comma
id|wchan
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_int
id|priority
comma
id|nice
suffix:semicolon
r_int
id|tty_pgrp
op_assign
op_minus
l_int|1
comma
id|tty_nr
op_assign
l_int|0
suffix:semicolon
id|sigset_t
id|sigign
comma
id|sigcatch
suffix:semicolon
r_char
id|state
suffix:semicolon
r_int
id|res
suffix:semicolon
id|pid_t
id|ppid
comma
id|pgid
op_assign
op_minus
l_int|1
comma
id|sid
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|num_threads
op_assign
l_int|0
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
r_int
r_int
id|start_time
suffix:semicolon
r_int
r_int
id|cmin_flt
op_assign
l_int|0
comma
id|cmaj_flt
op_assign
l_int|0
comma
id|cutime
op_assign
l_int|0
comma
id|cstime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|min_flt
op_assign
l_int|0
comma
id|maj_flt
op_assign
l_int|0
comma
id|utime
op_assign
l_int|0
comma
id|stime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rsslim
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|t
suffix:semicolon
r_char
id|tcomm
(braket
r_sizeof
(paren
id|task-&gt;comm
)paren
)braket
suffix:semicolon
id|state
op_assign
op_star
id|get_task_state
c_func
(paren
id|task
)paren
suffix:semicolon
id|vsize
op_assign
id|eip
op_assign
id|esp
op_assign
l_int|0
suffix:semicolon
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|vsize
op_assign
id|task_vsize
c_func
(paren
id|mm
)paren
suffix:semicolon
id|eip
op_assign
id|KSTK_EIP
c_func
(paren
id|task
)paren
suffix:semicolon
id|esp
op_assign
id|KSTK_ESP
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
id|get_task_comm
c_func
(paren
id|tcomm
comma
id|task
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sigign
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sigcatch
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;sighand
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|task-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|num_threads
op_assign
id|atomic_read
c_func
(paren
op_amp
id|task-&gt;signal-&gt;count
)paren
suffix:semicolon
id|collect_sigign_sigcatch
c_func
(paren
id|task
comma
op_amp
id|sigign
comma
op_amp
id|sigcatch
)paren
suffix:semicolon
multiline_comment|/* add up live thread stats at the group level */
r_if
c_cond
(paren
id|whole
)paren
(brace
id|t
op_assign
id|task
suffix:semicolon
r_do
(brace
id|min_flt
op_add_assign
id|t-&gt;min_flt
suffix:semicolon
id|maj_flt
op_add_assign
id|t-&gt;maj_flt
suffix:semicolon
id|utime
op_add_assign
id|t-&gt;utime
suffix:semicolon
id|stime
op_add_assign
id|t-&gt;stime
suffix:semicolon
id|t
op_assign
id|next_thread
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|t
op_ne
id|task
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|task-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task-&gt;signal
)paren
(brace
r_if
c_cond
(paren
id|task-&gt;signal-&gt;tty
)paren
(brace
id|tty_pgrp
op_assign
id|task-&gt;signal-&gt;tty-&gt;pgrp
suffix:semicolon
id|tty_nr
op_assign
id|new_encode_dev
c_func
(paren
id|tty_devnum
c_func
(paren
id|task-&gt;signal-&gt;tty
)paren
)paren
suffix:semicolon
)brace
id|pgid
op_assign
id|process_group
c_func
(paren
id|task
)paren
suffix:semicolon
id|sid
op_assign
id|task-&gt;signal-&gt;session
suffix:semicolon
id|cmin_flt
op_assign
id|task-&gt;signal-&gt;cmin_flt
suffix:semicolon
id|cmaj_flt
op_assign
id|task-&gt;signal-&gt;cmaj_flt
suffix:semicolon
id|cutime
op_assign
id|task-&gt;signal-&gt;cutime
suffix:semicolon
id|cstime
op_assign
id|task-&gt;signal-&gt;cstime
suffix:semicolon
id|rsslim
op_assign
id|task-&gt;signal-&gt;rlim
(braket
id|RLIMIT_RSS
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|whole
)paren
(brace
id|min_flt
op_add_assign
id|task-&gt;signal-&gt;min_flt
suffix:semicolon
id|maj_flt
op_add_assign
id|task-&gt;signal-&gt;maj_flt
suffix:semicolon
id|utime
op_add_assign
id|task-&gt;signal-&gt;utime
suffix:semicolon
id|stime
op_add_assign
id|task-&gt;signal-&gt;stime
suffix:semicolon
)brace
)brace
id|ppid
op_assign
id|pid_alive
c_func
(paren
id|task
)paren
ques
c_cond
id|task-&gt;group_leader-&gt;real_parent-&gt;tgid
suffix:colon
l_int|0
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|whole
op_logical_or
id|num_threads
OL
l_int|2
)paren
id|wchan
op_assign
id|get_wchan
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|whole
)paren
(brace
id|min_flt
op_assign
id|task-&gt;min_flt
suffix:semicolon
id|maj_flt
op_assign
id|task-&gt;maj_flt
suffix:semicolon
id|utime
op_assign
id|task-&gt;utime
suffix:semicolon
id|stime
op_assign
id|task-&gt;stime
suffix:semicolon
)brace
multiline_comment|/* scale priority and nice values from timeslices to -20..20 */
multiline_comment|/* to make it look like a &quot;normal&quot; Unix priority/nice value  */
id|priority
op_assign
id|task_prio
c_func
(paren
id|task
)paren
suffix:semicolon
id|nice
op_assign
id|task_nice
c_func
(paren
id|task
)paren
suffix:semicolon
multiline_comment|/* Temporary variable needed for gcc-2.96 */
multiline_comment|/* convert timespec -&gt; nsec*/
id|start_time
op_assign
(paren
r_int
r_int
r_int
)paren
id|task-&gt;start_time.tv_sec
op_star
id|NSEC_PER_SEC
op_plus
id|task-&gt;start_time.tv_nsec
suffix:semicolon
multiline_comment|/* convert nsec -&gt; ticks */
id|start_time
op_assign
id|nsec_to_clock_t
c_func
(paren
id|start_time
)paren
suffix:semicolon
id|res
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d (%s) %c %d %d %d %d %d %lu %lu &bslash;&n;%lu %lu %lu %lu %lu %ld %ld %ld %ld %d %ld %llu %lu %ld %lu %lu %lu %lu %lu &bslash;&n;%lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu&bslash;n&quot;
comma
id|task-&gt;pid
comma
id|tcomm
comma
id|state
comma
id|ppid
comma
id|pgid
comma
id|sid
comma
id|tty_nr
comma
id|tty_pgrp
comma
id|task-&gt;flags
comma
id|min_flt
comma
id|cmin_flt
comma
id|maj_flt
comma
id|cmaj_flt
comma
id|jiffies_to_clock_t
c_func
(paren
id|utime
)paren
comma
id|jiffies_to_clock_t
c_func
(paren
id|stime
)paren
comma
id|jiffies_to_clock_t
c_func
(paren
id|cutime
)paren
comma
id|jiffies_to_clock_t
c_func
(paren
id|cstime
)paren
comma
id|priority
comma
id|nice
comma
id|num_threads
comma
id|jiffies_to_clock_t
c_func
(paren
id|task-&gt;it_real_value
)paren
comma
id|start_time
comma
id|vsize
comma
id|mm
ques
c_cond
id|mm-&gt;rss
suffix:colon
l_int|0
comma
multiline_comment|/* you might want to shift this left 3 */
id|rsslim
comma
id|mm
ques
c_cond
id|mm-&gt;start_code
suffix:colon
l_int|0
comma
id|mm
ques
c_cond
id|mm-&gt;end_code
suffix:colon
l_int|0
comma
id|mm
ques
c_cond
id|mm-&gt;start_stack
suffix:colon
l_int|0
comma
id|esp
comma
id|eip
comma
multiline_comment|/* The signal information here is obsolete.&n;&t;&t; * It must be decimal for Linux 2.0 compatibility.&n;&t;&t; * Use /proc/#/status for real-time signals.&n;&t;&t; */
id|task-&gt;pending.signal.sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|task-&gt;blocked.sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|sigign
dot
id|sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|sigcatch
dot
id|sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|wchan
comma
l_int|0UL
comma
l_int|0UL
comma
id|task-&gt;exit_signal
comma
id|task_cpu
c_func
(paren
id|task
)paren
comma
id|task-&gt;rt_priority
comma
id|task-&gt;policy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|proc_tid_stat
r_int
id|proc_tid_stat
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_return
id|do_task_stat
c_func
(paren
id|task
comma
id|buffer
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|proc_tgid_stat
r_int
id|proc_tgid_stat
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_return
id|do_task_stat
c_func
(paren
id|task
comma
id|buffer
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|proc_pid_statm
r_int
id|proc_pid_statm
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|size
op_assign
l_int|0
comma
id|resident
op_assign
l_int|0
comma
id|shared
op_assign
l_int|0
comma
id|text
op_assign
l_int|0
comma
id|lib
op_assign
l_int|0
comma
id|data
op_assign
l_int|0
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|size
op_assign
id|task_statm
c_func
(paren
id|mm
comma
op_amp
id|shared
comma
op_amp
id|text
comma
op_amp
id|data
comma
op_amp
id|resident
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d %d %d %d %d %d %d&bslash;n&quot;
comma
id|size
comma
id|resident
comma
id|shared
comma
id|text
comma
id|lib
comma
id|data
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
