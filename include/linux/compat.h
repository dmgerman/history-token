macro_line|#ifndef _LINUX_COMPAT_H
DECL|macro|_LINUX_COMPAT_H
mdefine_line|#define _LINUX_COMPAT_H
multiline_comment|/*&n; * These are the type definitions for the architecture specific&n; * syscall compatibility layer.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_COMPAT
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;&t;/* for HZ */
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;asm/compat.h&gt;
macro_line|#include &lt;asm/siginfo.h&gt;
DECL|macro|compat_jiffies_to_clock_t
mdefine_line|#define compat_jiffies_to_clock_t(x)&t;&bslash;&n;&t;&t;(((unsigned long)(x) * COMPAT_USER_HZ) / HZ)
DECL|struct|compat_itimerspec
r_struct
id|compat_itimerspec
(brace
DECL|member|it_interval
r_struct
id|compat_timespec
id|it_interval
suffix:semicolon
DECL|member|it_value
r_struct
id|compat_timespec
id|it_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_utimbuf
r_struct
id|compat_utimbuf
(brace
DECL|member|actime
id|compat_time_t
id|actime
suffix:semicolon
DECL|member|modtime
id|compat_time_t
id|modtime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_itimerval
r_struct
id|compat_itimerval
(brace
DECL|member|it_interval
r_struct
id|compat_timeval
id|it_interval
suffix:semicolon
DECL|member|it_value
r_struct
id|compat_timeval
id|it_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_tms
r_struct
id|compat_tms
(brace
DECL|member|tms_utime
id|compat_clock_t
id|tms_utime
suffix:semicolon
DECL|member|tms_stime
id|compat_clock_t
id|tms_stime
suffix:semicolon
DECL|member|tms_cutime
id|compat_clock_t
id|tms_cutime
suffix:semicolon
DECL|member|tms_cstime
id|compat_clock_t
id|tms_cstime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|_COMPAT_NSIG_WORDS
mdefine_line|#define _COMPAT_NSIG_WORDS&t;(_COMPAT_NSIG / _COMPAT_NSIG_BPW)
r_typedef
r_struct
(brace
DECL|member|sig
id|compat_sigset_word
id|sig
(braket
id|_COMPAT_NSIG_WORDS
)braket
suffix:semicolon
DECL|typedef|compat_sigset_t
)brace
id|compat_sigset_t
suffix:semicolon
r_extern
r_int
id|cp_compat_stat
c_func
(paren
r_struct
id|kstat
op_star
comma
r_struct
id|compat_stat
id|__user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_compat_timespec
c_func
(paren
r_struct
id|timespec
op_star
comma
r_const
r_struct
id|compat_timespec
id|__user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|put_compat_timespec
c_func
(paren
r_const
r_struct
id|timespec
op_star
comma
r_struct
id|compat_timespec
id|__user
op_star
)paren
suffix:semicolon
DECL|struct|compat_iovec
r_struct
id|compat_iovec
(brace
DECL|member|iov_base
id|compat_uptr_t
id|iov_base
suffix:semicolon
DECL|member|iov_len
id|compat_size_t
id|iov_len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_rlimit
r_struct
id|compat_rlimit
(brace
DECL|member|rlim_cur
id|compat_ulong_t
id|rlim_cur
suffix:semicolon
DECL|member|rlim_max
id|compat_ulong_t
id|rlim_max
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|compat_rusage
r_struct
id|compat_rusage
(brace
DECL|member|ru_utime
r_struct
id|compat_timeval
id|ru_utime
suffix:semicolon
DECL|member|ru_stime
r_struct
id|compat_timeval
id|ru_stime
suffix:semicolon
DECL|member|ru_maxrss
id|compat_long_t
id|ru_maxrss
suffix:semicolon
DECL|member|ru_ixrss
id|compat_long_t
id|ru_ixrss
suffix:semicolon
DECL|member|ru_idrss
id|compat_long_t
id|ru_idrss
suffix:semicolon
DECL|member|ru_isrss
id|compat_long_t
id|ru_isrss
suffix:semicolon
DECL|member|ru_minflt
id|compat_long_t
id|ru_minflt
suffix:semicolon
DECL|member|ru_majflt
id|compat_long_t
id|ru_majflt
suffix:semicolon
DECL|member|ru_nswap
id|compat_long_t
id|ru_nswap
suffix:semicolon
DECL|member|ru_inblock
id|compat_long_t
id|ru_inblock
suffix:semicolon
DECL|member|ru_oublock
id|compat_long_t
id|ru_oublock
suffix:semicolon
DECL|member|ru_msgsnd
id|compat_long_t
id|ru_msgsnd
suffix:semicolon
DECL|member|ru_msgrcv
id|compat_long_t
id|ru_msgrcv
suffix:semicolon
DECL|member|ru_nsignals
id|compat_long_t
id|ru_nsignals
suffix:semicolon
DECL|member|ru_nvcsw
id|compat_long_t
id|ru_nvcsw
suffix:semicolon
DECL|member|ru_nivcsw
id|compat_long_t
id|ru_nivcsw
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|put_compat_rusage
c_func
(paren
r_const
r_struct
id|rusage
op_star
comma
r_struct
id|compat_rusage
id|__user
op_star
)paren
suffix:semicolon
DECL|struct|compat_dirent
r_struct
id|compat_dirent
(brace
DECL|member|d_ino
id|u32
id|d_ino
suffix:semicolon
DECL|member|d_off
id|compat_off_t
id|d_off
suffix:semicolon
DECL|member|d_reclen
id|u16
id|d_reclen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|union|compat_sigval
r_typedef
r_union
id|compat_sigval
(brace
DECL|member|sival_int
id|compat_int_t
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
id|compat_uptr_t
id|sival_ptr
suffix:semicolon
DECL|typedef|compat_sigval_t
)brace
id|compat_sigval_t
suffix:semicolon
DECL|struct|compat_sigevent
r_typedef
r_struct
id|compat_sigevent
(brace
DECL|member|sigev_value
id|compat_sigval_t
id|sigev_value
suffix:semicolon
DECL|member|sigev_signo
id|compat_int_t
id|sigev_signo
suffix:semicolon
DECL|member|sigev_notify
id|compat_int_t
id|sigev_notify
suffix:semicolon
r_union
(brace
DECL|member|_pad
id|compat_int_t
id|_pad
(braket
id|SIGEV_PAD_SIZE
)braket
suffix:semicolon
DECL|member|_tid
id|compat_int_t
id|_tid
suffix:semicolon
r_struct
(brace
DECL|member|_function
id|compat_uptr_t
id|_function
suffix:semicolon
DECL|member|_attribute
id|compat_uptr_t
id|_attribute
suffix:semicolon
DECL|member|_sigev_thread
)brace
id|_sigev_thread
suffix:semicolon
DECL|member|_sigev_un
)brace
id|_sigev_un
suffix:semicolon
DECL|typedef|compat_sigevent_t
)brace
id|compat_sigevent_t
suffix:semicolon
r_int
id|compat_sys_semctl
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_msgsnd
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_msgrcv
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
r_int
id|msgtyp
comma
r_int
id|third
comma
r_int
id|version
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_msgctl
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_shmat
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
id|compat_uptr_t
id|third
comma
r_int
id|version
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_shmctl
c_func
(paren
r_int
id|first
comma
r_int
id|second
comma
r_void
id|__user
op_star
id|uptr
)paren
suffix:semicolon
r_int
id|compat_sys_semtimedop
c_func
(paren
r_int
id|semid
comma
r_struct
id|sembuf
id|__user
op_star
id|tsems
comma
r_int
id|nsems
comma
r_const
r_struct
id|compat_timespec
id|__user
op_star
id|timeout
)paren
suffix:semicolon
id|asmlinkage
r_int
id|compat_sys_keyctl
c_func
(paren
id|u32
id|option
comma
id|u32
id|arg2
comma
id|u32
id|arg3
comma
id|u32
id|arg4
comma
id|u32
id|arg5
)paren
suffix:semicolon
id|asmlinkage
id|ssize_t
id|compat_sys_readv
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|compat_iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
)paren
suffix:semicolon
id|asmlinkage
id|ssize_t
id|compat_sys_writev
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_struct
id|compat_iovec
id|__user
op_star
id|vec
comma
r_int
r_int
id|vlen
)paren
suffix:semicolon
r_int
id|compat_do_execve
c_func
(paren
r_char
op_star
id|filename
comma
id|compat_uptr_t
id|__user
op_star
id|argv
comma
id|compat_uptr_t
id|__user
op_star
id|envp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
id|asmlinkage
r_int
id|compat_sys_select
c_func
(paren
r_int
id|n
comma
id|compat_ulong_t
id|__user
op_star
id|inp
comma
id|compat_ulong_t
id|__user
op_star
id|outp
comma
id|compat_ulong_t
id|__user
op_star
id|exp
comma
r_struct
id|compat_timeval
id|__user
op_star
id|tvp
)paren
suffix:semicolon
DECL|macro|BITS_PER_COMPAT_LONG
mdefine_line|#define BITS_PER_COMPAT_LONG    (8*sizeof(compat_long_t))
DECL|macro|BITS_TO_COMPAT_LONGS
mdefine_line|#define BITS_TO_COMPAT_LONGS(bits) &bslash;&n;&t;(((bits)+BITS_PER_COMPAT_LONG-1)/BITS_PER_COMPAT_LONG)
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
suffix:semicolon
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
suffix:semicolon
macro_line|#endif /* CONFIG_COMPAT */
macro_line|#endif /* _LINUX_COMPAT_H */
eof
