multiline_comment|/*&n; *  linux/kernel/compat.c&n; *&n; *  Kernel compatibililty routines for e.g. 32 bit syscall support&n; *  on 64 bit kernels.&n; *&n; *  Copyright (C) 2002-2003 Stephen Rothwell, IBM Corporation&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* for MAX_SCHEDULE_TIMEOUT */
macro_line|#include &lt;linux/futex.h&gt;&t;/* for FUTEX_WAIT */
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
r_struct
id|compat_timespec
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
r_struct
id|timespec
op_star
id|ts
comma
r_struct
id|compat_timespec
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
op_star
id|rqtp
comma
r_struct
id|compat_timespec
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
r_extern
r_int
id|do_getitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
id|value
)paren
suffix:semicolon
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
r_extern
r_int
id|do_setitimer
c_func
(paren
r_int
id|which
comma
r_struct
id|itimerval
op_star
comma
r_struct
id|itimerval
op_star
)paren
suffix:semicolon
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
op_star
id|in
comma
r_struct
id|compat_itimerval
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
id|tmp.tms_utime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|current-&gt;utime
)paren
suffix:semicolon
id|tmp.tms_stime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|current-&gt;stime
)paren
suffix:semicolon
id|tmp.tms_cutime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|current-&gt;cutime
)paren
suffix:semicolon
id|tmp.tms_cstime
op_assign
id|compat_jiffies_to_clock_t
c_func
(paren
id|current-&gt;cstime
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
r_extern
id|asmlinkage
r_int
id|sys_sigpending
c_func
(paren
id|old_sigset_t
op_star
)paren
suffix:semicolon
DECL|function|compat_sys_sigpending
id|asmlinkage
r_int
id|compat_sys_sigpending
c_func
(paren
id|compat_old_sigset_t
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
r_extern
id|asmlinkage
r_int
id|sys_sigprocmask
c_func
(paren
r_int
comma
id|old_sigset_t
op_star
comma
id|old_sigset_t
op_star
)paren
suffix:semicolon
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
op_star
id|set
comma
id|compat_old_sigset_t
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
op_amp
id|s
suffix:colon
l_int|NULL
comma
id|oset
ques
c_cond
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
op_star
id|utime
comma
id|u32
op_star
id|uaddr2
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
op_eq
id|FUTEX_REQUEUE
)paren
id|val2
op_assign
(paren
r_int
)paren
(paren
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
)paren
suffix:semicolon
)brace
macro_line|#endif
id|asmlinkage
r_int
id|sys_setrlimit
c_func
(paren
r_int
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
suffix:semicolon
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
id|asmlinkage
r_int
id|sys_old_getrlimit
c_func
(paren
r_int
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
suffix:semicolon
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
id|asmlinkage
r_int
id|sys_getrlimit
(paren
r_int
r_int
id|resource
comma
r_struct
id|rlimit
op_star
id|rlim
)paren
suffix:semicolon
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
r_static
r_int
id|put_compat_rusage
(paren
r_struct
id|compat_rusage
op_star
id|ru
comma
r_struct
id|rusage
op_star
id|r
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
id|asmlinkage
r_int
id|sys_getrusage
c_func
(paren
r_int
id|who
comma
r_struct
id|rusage
op_star
id|ru
)paren
suffix:semicolon
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
id|ru
comma
op_amp
id|r
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
op_star
id|stat_addr
comma
r_int
id|options
comma
r_struct
id|compat_rusage
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
id|stat_addr
ques
c_cond
op_amp
id|status
suffix:colon
l_int|NULL
comma
id|options
comma
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
id|ru
comma
op_amp
id|r
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
r_extern
id|asmlinkage
r_int
id|sys_sched_setaffinity
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
id|len
comma
r_int
r_int
op_star
id|user_mask_ptr
)paren
suffix:semicolon
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
op_star
id|user_mask_ptr
)paren
(brace
r_int
r_int
id|kernel_mask
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|kernel_mask
comma
id|user_mask_ptr
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
id|sys_sched_setaffinity
c_func
(paren
id|pid
comma
r_sizeof
(paren
id|kernel_mask
)paren
comma
op_amp
id|kernel_mask
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
r_extern
id|asmlinkage
r_int
id|sys_sched_getaffinity
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
id|len
comma
r_int
r_int
op_star
id|user_mask_ptr
)paren
suffix:semicolon
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
op_star
id|user_mask_ptr
)paren
(brace
r_int
r_int
id|kernel_mask
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|ret
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
id|sys_sched_getaffinity
c_func
(paren
id|pid
comma
r_sizeof
(paren
id|kernel_mask
)paren
comma
op_amp
id|kernel_mask
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
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|kernel_mask
comma
id|user_mask_ptr
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
r_sizeof
(paren
id|compat_ulong_t
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
