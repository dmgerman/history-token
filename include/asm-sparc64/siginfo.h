macro_line|#ifndef _SPARC64_SIGINFO_H
DECL|macro|_SPARC64_SIGINFO_H
mdefine_line|#define _SPARC64_SIGINFO_H
DECL|macro|SI_PAD_SIZE
mdefine_line|#define SI_PAD_SIZE&t;((SI_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|SI_PAD_SIZE32
mdefine_line|#define SI_PAD_SIZE32&t;((SI_MAX_SIZE/sizeof(int)) - 3)
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|SIGEV_PAD_SIZE32
mdefine_line|#define SIGEV_PAD_SIZE32 ((SIGEV_MAX_SIZE/sizeof(int)) - 3)
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
DECL|macro|HAVE_ARCH_COPY_SIGINFO_TO_USER
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO_TO_USER
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#ifdef __KERNEL__
DECL|union|sigval32
r_typedef
r_union
id|sigval32
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
id|u32
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|struct|siginfo
r_typedef
r_struct
id|siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SI_PAD_SIZE
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|uid_t
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
multiline_comment|/* POSIX.1b timers */
r_struct
(brace
DECL|member|_timer1
r_int
r_int
id|_timer1
suffix:semicolon
DECL|member|_timer2
r_int
r_int
id|_timer2
suffix:semicolon
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|uid_t
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigval
id|sigval_t
id|_sigval
suffix:semicolon
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
id|uid_t
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|clock_t
id|_utime
suffix:semicolon
DECL|member|_stime
id|clock_t
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS, SIGEMT */
r_struct
(brace
DECL|member|_addr
r_void
op_star
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_trapno
r_int
id|_trapno
suffix:semicolon
multiline_comment|/* TRAP # which caused the signal */
DECL|member|_sigfault
)brace
id|_sigfault
suffix:semicolon
multiline_comment|/* SIGPOLL */
r_struct
(brace
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t
)brace
id|siginfo_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|siginfo32
r_typedef
r_struct
id|siginfo32
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SI_PAD_SIZE32
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
id|__kernel_pid_t32
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
multiline_comment|/* POSIX.1b timers */
r_struct
(brace
DECL|member|_timer1
r_int
r_int
id|_timer1
suffix:semicolon
DECL|member|_timer2
r_int
r_int
id|_timer2
suffix:semicolon
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
id|__kernel_pid_t32
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
id|__kernel_pid_t32
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|__kernel_clock_t32
id|_utime
suffix:semicolon
DECL|member|_stime
id|__kernel_clock_t32
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS, SIGEMT */
r_struct
(brace
DECL|member|_addr
id|u32
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_trapno
r_int
id|_trapno
suffix:semicolon
DECL|member|_sigfault
)brace
id|_sigfault
suffix:semicolon
multiline_comment|/* SIGPOLL */
r_struct
(brace
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t32
)brace
id|siginfo_t32
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|macro|si_trapno
mdefine_line|#define si_trapno&t;_sifields._sigfault._trapno
DECL|macro|SI_NOINFO
mdefine_line|#define SI_NOINFO&t;32767&t;&t;/* no information in siginfo_t */
multiline_comment|/*&n; * SIGEMT si_codes&n; */
DECL|macro|EMT_TAGOVF
mdefine_line|#define EMT_TAGOVF&t;(__SI_FAULT|1)&t;/* tag overflow */
DECL|macro|NSIGEMT
mdefine_line|#define NSIGEMT&t;&t;1
macro_line|#ifdef __KERNEL__
DECL|struct|sigevent32
r_typedef
r_struct
id|sigevent32
(brace
DECL|member|sigev_value
id|sigval_t
id|sigev_value
suffix:semicolon
DECL|member|sigev_signo
r_int
id|sigev_signo
suffix:semicolon
DECL|member|sigev_notify
r_int
id|sigev_notify
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SIGEV_PAD_SIZE32
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_function
id|u32
id|_function
suffix:semicolon
DECL|member|_attribute
id|u32
id|_attribute
suffix:semicolon
multiline_comment|/* really pthread_attr_t */
DECL|member|_sigev_thread
)brace
id|_sigev_thread
suffix:semicolon
DECL|member|_sigev_un
)brace
id|_sigev_un
suffix:semicolon
DECL|typedef|sigevent_t32
)brace
id|sigevent_t32
suffix:semicolon
macro_line|#include &lt;linux/string.h&gt;
DECL|function|copy_siginfo
r_extern
r_inline
r_void
id|copy_siginfo
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
op_star
id|to
op_assign
op_star
id|from
suffix:semicolon
r_else
multiline_comment|/* _sigchld is currently the largest know union member */
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
l_int|4
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
id|from-&gt;_sifields._sigchld
)paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|copy_siginfo_to_user32
c_func
(paren
id|siginfo_t32
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
