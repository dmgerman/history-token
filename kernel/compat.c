multiline_comment|/*&n; *  linux/kernel/compat.c&n; *&n; *  Kernel compatibililty routines for e.g. 32 bit syscall support&n; *  on 64 bit kernels.&n; *&n; *  Copyright (C) 2002-2003 Stephen Rothwell, IBM Corporation&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* for MAX_SCHEDULE_TIMEOUT */
macro_line|#include &lt;linux/futex.h&gt;&t;/* for FUTEX_WAIT */
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|get_compat_timespec
r_int
id|get_compat_timespec
c_func
(paren
r_struct
id|timespec
op_star
id|ts
comma
r_const
r_struct
id|compat_timespec
id|__user
op_star
id|cts
)paren
(brace
r_return
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|cts
comma
r_sizeof
(paren
op_star
id|cts
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ts-&gt;tv_sec
comma
op_amp
id|cts-&gt;tv_sec
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ts-&gt;tv_nsec
comma
op_amp
id|cts-&gt;tv_nsec
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|put_compat_timespec
r_int
id|put_compat_timespec
c_func
(paren
r_const
r_struct
id|timespec
op_star
id|ts
comma
r_struct
id|compat_timespec
id|__user
op_star
id|cts
)paren
(brace
r_return
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|cts
comma
r_sizeof
(paren
op_star
id|cts
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|ts-&gt;tv_sec
comma
op_amp
id|cts-&gt;tv_sec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|ts-&gt;tv_nsec
comma
op_amp
id|cts-&gt;tv_nsec
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|compat_nanosleep_restart
r_static
r_int
id|compat_nanosleep_restart
c_func
(paren
r_struct
id|restart_block
op_star
id|restart
)paren
(brace
r_int
r_int
id|expire
op_assign
id|restart-&gt;arg0
comma
id|now
op_assign
id|jiffies
suffix:semicolon
r_struct
id|compat_timespec
id|__user
op_star
id|rmtp
suffix:semicolon
multiline_comment|/* Did it expire while we handled signals? */
r_if
c_cond
(paren
op_logical_neg
id|time_after
c_func
(paren
id|expire
comma
id|now
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|expire
op_assign
id|schedule_timeout
c_func
(paren
id|expire
op_minus
id|now
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expire
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|rmtp
op_assign
(paren
r_struct
id|compat_timespec
id|__user
op_star
)paren
id|restart-&gt;arg1
suffix:semicolon
r_if
c_cond
(paren
id|rmtp
)paren
(brace
r_struct
id|compat_timespec
id|ct
suffix:semicolon
r_struct
id|timespec
id|t
suffix:semicolon
id|jiffies_to_timespec
c_func
(paren
id|expire
comma
op_amp
id|t
)paren
suffix:semicolon
id|ct.tv_sec
op_assign
id|t.tv_sec
suffix:semicolon
id|ct.tv_nsec
op_assign
id|t.tv_nsec
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|rmtp
comma
op_amp
id|ct
comma
r_sizeof
(paren
id|ct
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* The &squot;restart&squot; block is already filled in */
r_return
op_minus
id|ERESTART_RESTARTBLOCK
suffix:semicolon
)brace
DECL|function|compat_sys_nanosleep
id|asmlinkage
r_int
id|compat_sys_nanosleep
c_func
(paren
r_struct
id|compat_timespec
id|__user
op_star
id|rqtp
comma
r_struct
id|compat_timespec
id|__user
op_star
id|rmtp
)paren
(brace
r_struct
id|timespec
id|t
suffix:semicolon
r_struct
id|restart_block
op_star
id|restart
suffix:semicolon
r_int
r_int
id|expire
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|t
comma
id|rqtp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t.tv_nsec
op_ge
l_int|1000000000L
)paren
op_logical_or
(paren
id|t.tv_nsec
OL
l_int|0
)paren
op_logical_or
(paren
id|t.tv_sec
OL
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|expire
op_assign
id|timespec_to_jiffies
c_func
(paren
op_amp
id|t
)paren
op_plus
(paren
id|t.tv_sec
op_logical_or
id|t.tv_nsec
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|expire
op_assign
id|schedule_timeout
c_func
(paren
id|expire
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expire
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rmtp
)paren
(brace
id|jiffies_to_timespec
c_func
(paren
id|expire
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_compat_timespec
c_func
(paren
op_amp
id|t
comma
id|rmtp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|restart
op_assign
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block
suffix:semicolon
id|restart-&gt;fn
op_assign
id|compat_nanosleep_restart
suffix:semicolon
id|restart-&gt;arg0
op_assign
id|jiffies
op_plus
id|expire
suffix:semicolon
id|restart-&gt;arg1
op_assign
(paren
r_int
r_int
)paren
id|rmtp
suffix:semicolon
r_return
op_minus
id|ERESTART_RESTARTBLOCK
suffix:semicolon
)brace
DECL|function|get_compat_itimerval
r_static
r_inline
r_int
id|get_compat_itimerval
c_func
(paren
r_struct
id|itimerval
op_star
id|o
comma
r_struct
id|compat_itimerval
id|__user
op_star
id|i
)paren
(brace
r_return
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|i
comma
r_sizeof
(paren
op_star
id|i
)paren
)paren
op_logical_or
(paren
id|__get_user
c_func
(paren
id|o-&gt;it_interval.tv_sec
comma
op_amp
id|i-&gt;it_interval.tv_sec
)paren
op_or
id|__get_user
c_func
(paren
id|o-&gt;it_interval.tv_usec
comma
op_amp
id|i-&gt;it_interval.tv_usec
)paren
op_or
id|__get_user
c_func
(paren
id|o-&gt;it_value.tv_sec
comma
op_amp
id|i-&gt;it_value.tv_sec
)paren
op_or
id|__get_user
c_func
(paren
id|o-&gt;it_value.tv_usec
comma
op_amp
id|i-&gt;it_value.tv_usec
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|put_compat_itimerval
r_static
r_inline
r_int
id|put_compat_itimerval
c_func
(paren
r_struct
id|compat_itimerval
id|__user
op_star
id|o
comma
r_struct
id|itimerval
op_star
id|i
)paren
(brace
r_return
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|o
comma
r_sizeof
(paren
op_star
id|o
)paren
)paren
op_logical_or
(paren
id|__put_user
c_func
(paren
id|i-&gt;it_interval.tv_sec
comma
op_amp
id|o-&gt;it_interval.tv_sec
)paren
op_or
id|__put_user
c_func
(paren
id|i-&gt;it_interval.tv_usec
comma
op_amp
id|o-&gt;it_interval.tv_usec
)paren
op_or
id|__put_user
c_func
(paren
id|i-&gt;it_value.tv_sec
comma
op_amp
id|o-&gt;it_value.tv_sec
)paren
op_or
id|__put_user
c_func
(paren
id|i-&gt;it_value.tv_usec
comma
op_amp
id|o-&gt;it_value.tv_usec
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_getitimer
id|asmlinkage
r_int
id|compat_sys_getitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|compat_itimerval
id|__user
op_star
id|it
)paren
(brace
r_struct
id|itimerval
id|kit
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_getitimer
c_func
(paren
id|which
comma
op_amp
id|kit
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|put_compat_itimerval
c_func
(paren
id|it
comma
op_amp
id|kit
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|compat_sys_setitimer
id|asmlinkage
r_int
id|compat_sys_setitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|compat_itimerval
id|__user
op_star
id|in
comma
r_struct
id|compat_itimerval
id|__user
op_star
id|out
)paren
(brace
r_struct
id|itimerval
id|kin
comma
id|kout
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|in
)paren
(brace
r_if
c_cond
(paren
id|get_compat_itimerval
c_func
(paren
op_amp
id|kin
comma
id|in
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
op_amp
id|kin
comma
l_int|0
comma
r_sizeof
(paren
id|kin
)paren
)paren
suffix:semicolon
id|error
op_assign
id|do_setitimer
c_func
(paren
id|which
comma
op_amp
id|kin
comma
id|out
ques
c_cond
op_amp
id|kout
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|out
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|put_compat_itimerval
c_func
(paren
id|out
comma
op_amp
id|kout
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compat_sys_times
id|asmlinkage
r_int
id|compat_sys_times
c_func
(paren
r_struct
id|compat_tms
id|__user
op_star
id|tbuf
)paren
(brace
multiline_comment|/*&n;&t; *&t;In the SMP world we might just be unlucky and have one of&n;&t; *&t;the times increment as we use it. Since the value is an&n;&t; *&t;atomically safe type this is just fine. Conceptually its&n;&t; *&t;as if the syscall took an instant longer to occur.&n;&t; */
r_if
c_cond
(paren
id|tbuf
)paren
(brace
r_struct
id|compat_tms
id|tmp
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|task_struct
op_star
id|t
suffix:semicolon
r_int
r_int
id|utime
comma
id|stime
comma
id|cutime
comma
id|cstime
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|utime
op_assign
id|tsk-&gt;signal-&gt;utime
suffix:semicolon
id|stime
op_assign
id|tsk-&gt;signal-&gt;stime
suffix:semicolon
id|t
op_assign
id|tsk
suffix:semicolon
r_do
(brace
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
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * While we have tasklist_lock read-locked, no dying thread&n;&t;&t; * can be updating current-&gt;signal-&gt;[us]time.  Instead,&n;&t;&t; * we got their counts included in the live thread loop.&n;&t;&t; * However, another thread can come in right now and&n;&t;&t; * do a wait call that updates current-&gt;signal-&gt;c[us]time.&n;&t;&t; * To make sure we always see that pair updated atomically,&n;&t;&t; * we take the siglock around fetching them.&n;&t;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|tsk-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|cutime
op_assign
id|tsk-&gt;signal-&gt;cutime
suffix:semicolon
id|cstime
op_assign
id|tsk-&gt;signal-&gt;cstime
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|tsk-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|tmp.tms_utime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|utime
)paren
suffix:semicolon
id|tmp.tms_stime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|stime
)paren
suffix:semicolon
id|tmp.tms_cutime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|cutime
)paren
suffix:semicolon
id|tmp.tms_cstime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|cstime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|compat_jiffies_to_clock_t
c_func
(paren
id|jiffies
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Assumption: old_sigset_t and compat_old_sigset_t are both&n; * types that can be passed to put_user()/get_user().&n; */
DECL|function|compat_sys_sigpending
id|asmlinkage
r_int
id|compat_sys_sigpending
c_func
(paren
id|compat_old_sigset_t
id|__user
op_star
id|set
)paren
(brace
id|old_sigset_t
id|s
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
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
id|ret
op_assign
id|sys_sigpending
c_func
(paren
(paren
id|old_sigset_t
id|__user
op_star
)paren
op_amp
id|s
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|put_user
c_func
(paren
id|s
comma
id|set
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|compat_sys_sigprocmask
id|asmlinkage
r_int
id|compat_sys_sigprocmask
c_func
(paren
r_int
id|how
comma
id|compat_old_sigset_t
id|__user
op_star
id|set
comma
id|compat_old_sigset_t
id|__user
op_star
id|oset
)paren
(brace
id|old_sigset_t
id|s
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_if
c_cond
(paren
id|set
op_logical_and
id|get_user
c_func
(paren
id|s
comma
id|set
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|old_fs
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
id|ret
op_assign
id|sys_sigprocmask
c_func
(paren
id|how
comma
id|set
ques
c_cond
(paren
id|old_sigset_t
id|__user
op_star
)paren
op_amp
id|s
suffix:colon
l_int|NULL
comma
id|oset
ques
c_cond
(paren
id|old_sigset_t
id|__user
op_star
)paren
op_amp
id|s
suffix:colon
l_int|NULL
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|oset
)paren
id|ret
op_assign
id|put_user
c_func
(paren
id|s
comma
id|oset
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FUTEX
DECL|function|compat_sys_futex
id|asmlinkage
r_int
id|compat_sys_futex
c_func
(paren
id|u32
id|__user
op_star
id|uaddr
comma
r_int
id|op
comma
r_int
id|val
comma
r_struct
id|compat_timespec
id|__user
op_star
id|utime
comma
id|u32
id|__user
op_star
id|uaddr2
comma
r_int
id|val3
)paren
(brace
r_struct
id|timespec
id|t
suffix:semicolon
r_int
r_int
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
r_int
id|val2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|op
op_eq
id|FUTEX_WAIT
)paren
op_logical_and
id|utime
)paren
(brace
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|t
comma
id|utime
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|timeout
op_assign
id|timespec_to_jiffies
c_func
(paren
op_amp
id|t
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
op_ge
id|FUTEX_REQUEUE
)paren
id|val2
op_assign
(paren
r_int
)paren
(paren
r_int
r_int
)paren
id|utime
suffix:semicolon
r_return
id|do_futex
c_func
(paren
(paren
r_int
r_int
)paren
id|uaddr
comma
id|op
comma
id|val
comma
id|timeout
comma
(paren
r_int
r_int
)paren
id|uaddr2
comma
id|val2
comma
id|val3
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|compat_sys_setrlimit
id|asmlinkage
r_int
id|compat_sys_setrlimit
c_func
(paren
r_int
r_int
id|resource
comma
r_struct
id|compat_rlimit
id|__user
op_star
id|rlim
)paren
(brace
r_struct
id|rlimit
id|r
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource
op_ge
id|RLIM_NLIMITS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|rlim
comma
r_sizeof
(paren
op_star
id|rlim
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|r.rlim_cur
comma
op_amp
id|rlim-&gt;rlim_cur
)paren
op_logical_or
id|__get_user
c_func
(paren
id|r.rlim_max
comma
op_amp
id|rlim-&gt;rlim_max
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|r.rlim_cur
op_eq
id|COMPAT_RLIM_INFINITY
)paren
id|r.rlim_cur
op_assign
id|RLIM_INFINITY
suffix:semicolon
r_if
c_cond
(paren
id|r.rlim_max
op_eq
id|COMPAT_RLIM_INFINITY
)paren
id|r.rlim_max
op_assign
id|RLIM_INFINITY
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_setrlimit
c_func
(paren
id|resource
comma
(paren
r_struct
id|rlimit
id|__user
op_star
)paren
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef COMPAT_RLIM_OLD_INFINITY
DECL|function|compat_sys_old_getrlimit
id|asmlinkage
r_int
id|compat_sys_old_getrlimit
c_func
(paren
r_int
r_int
id|resource
comma
r_struct
id|compat_rlimit
id|__user
op_star
id|rlim
)paren
(brace
r_struct
id|rlimit
id|r
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
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
id|ret
op_assign
id|sys_old_getrlimit
c_func
(paren
id|resource
comma
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_if
c_cond
(paren
id|r.rlim_cur
OG
id|COMPAT_RLIM_OLD_INFINITY
)paren
id|r.rlim_cur
op_assign
id|COMPAT_RLIM_INFINITY
suffix:semicolon
r_if
c_cond
(paren
id|r.rlim_max
OG
id|COMPAT_RLIM_OLD_INFINITY
)paren
id|r.rlim_max
op_assign
id|COMPAT_RLIM_INFINITY
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
id|rlim
comma
r_sizeof
(paren
op_star
id|rlim
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r.rlim_cur
comma
op_amp
id|rlim-&gt;rlim_cur
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r.rlim_max
comma
op_amp
id|rlim-&gt;rlim_max
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|compat_sys_getrlimit
id|asmlinkage
r_int
id|compat_sys_getrlimit
(paren
r_int
r_int
id|resource
comma
r_struct
id|compat_rlimit
id|__user
op_star
id|rlim
)paren
(brace
r_struct
id|rlimit
id|r
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
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
id|ret
op_assign
id|sys_getrlimit
c_func
(paren
id|resource
comma
(paren
r_struct
id|rlimit
id|__user
op_star
)paren
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_if
c_cond
(paren
id|r.rlim_cur
OG
id|COMPAT_RLIM_INFINITY
)paren
id|r.rlim_cur
op_assign
id|COMPAT_RLIM_INFINITY
suffix:semicolon
r_if
c_cond
(paren
id|r.rlim_max
OG
id|COMPAT_RLIM_INFINITY
)paren
id|r.rlim_max
op_assign
id|COMPAT_RLIM_INFINITY
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
id|rlim
comma
r_sizeof
(paren
op_star
id|rlim
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r.rlim_cur
comma
op_amp
id|rlim-&gt;rlim_cur
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r.rlim_max
comma
op_amp
id|rlim-&gt;rlim_max
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|put_compat_rusage
r_int
id|put_compat_rusage
c_func
(paren
r_const
r_struct
id|rusage
op_star
id|r
comma
r_struct
id|compat_rusage
id|__user
op_star
id|ru
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|ru
comma
r_sizeof
(paren
op_star
id|ru
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_utime.tv_sec
comma
op_amp
id|ru-&gt;ru_utime.tv_sec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_utime.tv_usec
comma
op_amp
id|ru-&gt;ru_utime.tv_usec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_stime.tv_sec
comma
op_amp
id|ru-&gt;ru_stime.tv_sec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_stime.tv_usec
comma
op_amp
id|ru-&gt;ru_stime.tv_usec
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_maxrss
comma
op_amp
id|ru-&gt;ru_maxrss
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_ixrss
comma
op_amp
id|ru-&gt;ru_ixrss
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_idrss
comma
op_amp
id|ru-&gt;ru_idrss
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_isrss
comma
op_amp
id|ru-&gt;ru_isrss
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_minflt
comma
op_amp
id|ru-&gt;ru_minflt
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_majflt
comma
op_amp
id|ru-&gt;ru_majflt
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_nswap
comma
op_amp
id|ru-&gt;ru_nswap
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_inblock
comma
op_amp
id|ru-&gt;ru_inblock
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_oublock
comma
op_amp
id|ru-&gt;ru_oublock
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_msgsnd
comma
op_amp
id|ru-&gt;ru_msgsnd
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_msgrcv
comma
op_amp
id|ru-&gt;ru_msgrcv
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_nsignals
comma
op_amp
id|ru-&gt;ru_nsignals
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_nvcsw
comma
op_amp
id|ru-&gt;ru_nvcsw
)paren
op_logical_or
id|__put_user
c_func
(paren
id|r-&gt;ru_nivcsw
comma
op_amp
id|ru-&gt;ru_nivcsw
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compat_sys_getrusage
id|asmlinkage
r_int
id|compat_sys_getrusage
c_func
(paren
r_int
id|who
comma
r_struct
id|compat_rusage
id|__user
op_star
id|ru
)paren
(brace
r_struct
id|rusage
id|r
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
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
id|ret
op_assign
id|sys_getrusage
c_func
(paren
id|who
comma
(paren
r_struct
id|rusage
id|__user
op_star
)paren
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|put_compat_rusage
c_func
(paren
op_amp
id|r
comma
id|ru
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|compat_sys_wait4
id|compat_sys_wait4
c_func
(paren
id|compat_pid_t
id|pid
comma
id|compat_uint_t
id|__user
op_star
id|stat_addr
comma
r_int
id|options
comma
r_struct
id|compat_rusage
id|__user
op_star
id|ru
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ru
)paren
(brace
r_return
id|sys_wait4
c_func
(paren
id|pid
comma
id|stat_addr
comma
id|options
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|rusage
id|r
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_wait4
c_func
(paren
id|pid
comma
(paren
id|stat_addr
ques
c_cond
(paren
r_int
r_int
id|__user
op_star
)paren
op_amp
id|status
suffix:colon
l_int|NULL
)paren
comma
id|options
comma
(paren
r_struct
id|rusage
id|__user
op_star
)paren
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|put_compat_rusage
c_func
(paren
op_amp
id|r
comma
id|ru
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|stat_addr
op_logical_and
id|put_user
c_func
(paren
id|status
comma
id|stat_addr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
)brace
DECL|function|compat_get_user_cpu_mask
r_static
r_int
id|compat_get_user_cpu_mask
c_func
(paren
id|compat_ulong_t
id|__user
op_star
id|user_mask_ptr
comma
r_int
id|len
comma
id|cpumask_t
op_star
id|new_mask
)paren
(brace
r_int
r_int
op_star
id|k
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
id|cpumask_t
)paren
)paren
id|memset
c_func
(paren
id|new_mask
comma
l_int|0
comma
r_sizeof
(paren
id|cpumask_t
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
id|cpumask_t
)paren
)paren
id|len
op_assign
r_sizeof
(paren
id|cpumask_t
)paren
suffix:semicolon
id|k
op_assign
id|cpus_addr
c_func
(paren
op_star
id|new_mask
)paren
suffix:semicolon
r_return
id|compat_get_bitmap
c_func
(paren
id|k
comma
id|user_mask_ptr
comma
id|len
op_star
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_sched_setaffinity
id|asmlinkage
r_int
id|compat_sys_sched_setaffinity
c_func
(paren
id|compat_pid_t
id|pid
comma
r_int
r_int
id|len
comma
id|compat_ulong_t
id|__user
op_star
id|user_mask_ptr
)paren
(brace
id|cpumask_t
id|new_mask
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|compat_get_user_cpu_mask
c_func
(paren
id|user_mask_ptr
comma
id|len
comma
op_amp
id|new_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|sched_setaffinity
c_func
(paren
id|pid
comma
id|new_mask
)paren
suffix:semicolon
)brace
DECL|function|compat_sys_sched_getaffinity
id|asmlinkage
r_int
id|compat_sys_sched_getaffinity
c_func
(paren
id|compat_pid_t
id|pid
comma
r_int
r_int
id|len
comma
id|compat_ulong_t
id|__user
op_star
id|user_mask_ptr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|cpumask_t
id|mask
suffix:semicolon
r_int
r_int
op_star
id|k
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
id|cpumask_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|sched_getaffinity
c_func
(paren
id|pid
comma
op_amp
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|k
op_assign
id|cpus_addr
c_func
(paren
id|mask
)paren
suffix:semicolon
id|ret
op_assign
id|compat_put_bitmap
c_func
(paren
id|user_mask_ptr
comma
id|k
comma
r_sizeof
(paren
id|cpumask_t
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
r_sizeof
(paren
id|cpumask_t
)paren
suffix:semicolon
)brace
DECL|function|get_compat_itimerspec
r_static
r_int
id|get_compat_itimerspec
c_func
(paren
r_struct
id|itimerspec
op_star
id|dst
comma
r_struct
id|compat_itimerspec
id|__user
op_star
id|src
)paren
(brace
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|dst-&gt;it_interval
comma
op_amp
id|src-&gt;it_interval
)paren
op_logical_or
id|get_compat_timespec
c_func
(paren
op_amp
id|dst-&gt;it_value
comma
op_amp
id|src-&gt;it_value
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|put_compat_itimerspec
r_static
r_int
id|put_compat_itimerspec
c_func
(paren
r_struct
id|compat_itimerspec
id|__user
op_star
id|dst
comma
r_struct
id|itimerspec
op_star
id|src
)paren
(brace
r_if
c_cond
(paren
id|put_compat_timespec
c_func
(paren
op_amp
id|src-&gt;it_interval
comma
op_amp
id|dst-&gt;it_interval
)paren
op_logical_or
id|put_compat_timespec
c_func
(paren
op_amp
id|src-&gt;it_value
comma
op_amp
id|dst-&gt;it_value
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compat_timer_settime
r_int
id|compat_timer_settime
c_func
(paren
id|timer_t
id|timer_id
comma
r_int
id|flags
comma
r_struct
id|compat_itimerspec
id|__user
op_star
r_new
comma
r_struct
id|compat_itimerspec
id|__user
op_star
id|old
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|itimerspec
id|newts
comma
id|oldts
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_itimerspec
c_func
(paren
op_amp
id|newts
comma
r_new
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_timer_settime
c_func
(paren
id|timer_id
comma
id|flags
comma
(paren
r_struct
id|itimerspec
id|__user
op_star
)paren
op_amp
id|newts
comma
(paren
r_struct
id|itimerspec
id|__user
op_star
)paren
op_amp
id|oldts
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|old
op_logical_and
id|put_compat_itimerspec
c_func
(paren
id|old
comma
op_amp
id|oldts
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_timer_gettime
r_int
id|compat_timer_gettime
c_func
(paren
id|timer_t
id|timer_id
comma
r_struct
id|compat_itimerspec
id|__user
op_star
id|setting
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|itimerspec
id|ts
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_timer_gettime
c_func
(paren
id|timer_id
comma
(paren
r_struct
id|itimerspec
id|__user
op_star
)paren
op_amp
id|ts
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|put_compat_itimerspec
c_func
(paren
id|setting
comma
op_amp
id|ts
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_clock_settime
r_int
id|compat_clock_settime
c_func
(paren
id|clockid_t
id|which_clock
comma
r_struct
id|compat_timespec
id|__user
op_star
id|tp
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|timespec
id|ts
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|ts
comma
id|tp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_clock_settime
c_func
(paren
id|which_clock
comma
(paren
r_struct
id|timespec
id|__user
op_star
)paren
op_amp
id|ts
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_clock_gettime
r_int
id|compat_clock_gettime
c_func
(paren
id|clockid_t
id|which_clock
comma
r_struct
id|compat_timespec
id|__user
op_star
id|tp
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|timespec
id|ts
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_clock_gettime
c_func
(paren
id|which_clock
comma
(paren
r_struct
id|timespec
id|__user
op_star
)paren
op_amp
id|ts
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|put_compat_timespec
c_func
(paren
op_amp
id|ts
comma
id|tp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_clock_getres
r_int
id|compat_clock_getres
c_func
(paren
id|clockid_t
id|which_clock
comma
r_struct
id|compat_timespec
id|__user
op_star
id|tp
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|timespec
id|ts
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_clock_getres
c_func
(paren
id|which_clock
comma
(paren
r_struct
id|timespec
id|__user
op_star
)paren
op_amp
id|ts
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|tp
op_logical_and
id|put_compat_timespec
c_func
(paren
op_amp
id|ts
comma
id|tp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|compat_clock_nanosleep
r_int
id|compat_clock_nanosleep
c_func
(paren
id|clockid_t
id|which_clock
comma
r_int
id|flags
comma
r_struct
id|compat_timespec
id|__user
op_star
id|rqtp
comma
r_struct
id|compat_timespec
id|__user
op_star
id|rmtp
)paren
(brace
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldfs
suffix:semicolon
r_struct
id|timespec
id|in
comma
id|out
suffix:semicolon
r_if
c_cond
(paren
id|get_compat_timespec
c_func
(paren
op_amp
id|in
comma
id|rqtp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|oldfs
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
id|err
op_assign
id|sys_clock_nanosleep
c_func
(paren
id|which_clock
comma
id|flags
comma
(paren
r_struct
id|timespec
id|__user
op_star
)paren
op_amp
id|in
comma
(paren
r_struct
id|timespec
id|__user
op_star
)paren
op_amp
id|out
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
op_logical_and
id|rmtp
op_logical_and
id|put_compat_timespec
c_func
(paren
op_amp
id|out
comma
id|rmtp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* timer_create is architecture specific because it needs sigevent conversion */
DECL|function|compat_get_bitmap
r_int
id|compat_get_bitmap
c_func
(paren
r_int
r_int
op_star
id|mask
comma
id|compat_ulong_t
id|__user
op_star
id|umask
comma
r_int
r_int
id|bitmap_size
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|m
suffix:semicolon
id|compat_ulong_t
id|um
suffix:semicolon
r_int
r_int
id|nr_compat_longs
suffix:semicolon
multiline_comment|/* align bitmap up to nearest compat_long_t boundary */
id|bitmap_size
op_assign
id|ALIGN
c_func
(paren
id|bitmap_size
comma
id|BITS_PER_COMPAT_LONG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|umask
comma
id|bitmap_size
op_div
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|nr_compat_longs
op_assign
id|BITS_TO_COMPAT_LONGS
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BITS_TO_LONGS
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|m
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
r_sizeof
(paren
id|m
)paren
op_div
r_sizeof
(paren
id|um
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We dont want to read past the end of the userspace&n;&t;&t;&t; * bitmap. We must however ensure the end of the&n;&t;&t;&t; * kernel bitmap is zeroed.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|nr_compat_longs
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|um
comma
id|umask
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|um
op_assign
l_int|0
suffix:semicolon
)brace
id|umask
op_increment
suffix:semicolon
id|m
op_or_assign
(paren
r_int
)paren
id|um
op_lshift
(paren
id|j
op_star
id|BITS_PER_COMPAT_LONG
)paren
suffix:semicolon
)brace
op_star
id|mask
op_increment
op_assign
id|m
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compat_put_bitmap
r_int
id|compat_put_bitmap
c_func
(paren
id|compat_ulong_t
id|__user
op_star
id|umask
comma
r_int
r_int
op_star
id|mask
comma
r_int
r_int
id|bitmap_size
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|m
suffix:semicolon
id|compat_ulong_t
id|um
suffix:semicolon
r_int
r_int
id|nr_compat_longs
suffix:semicolon
multiline_comment|/* align bitmap up to nearest compat_long_t boundary */
id|bitmap_size
op_assign
id|ALIGN
c_func
(paren
id|bitmap_size
comma
id|BITS_PER_COMPAT_LONG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|umask
comma
id|bitmap_size
op_div
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|nr_compat_longs
op_assign
id|BITS_TO_COMPAT_LONGS
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BITS_TO_LONGS
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|m
op_assign
op_star
id|mask
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
r_sizeof
(paren
id|m
)paren
op_div
r_sizeof
(paren
id|um
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|um
op_assign
id|m
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We dont want to write past the end of the userspace&n;&t;&t;&t; * bitmap.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|nr_compat_longs
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|um
comma
id|umask
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|umask
op_increment
suffix:semicolon
id|m
op_rshift_assign
l_int|4
op_star
r_sizeof
(paren
id|um
)paren
suffix:semicolon
id|m
op_rshift_assign
l_int|4
op_star
r_sizeof
(paren
id|um
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
