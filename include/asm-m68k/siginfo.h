macro_line|#ifndef _M68K_SIGINFO_H
DECL|macro|_M68K_SIGINFO_H
mdefine_line|#define _M68K_SIGINFO_H
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
macro_line|#include &lt;asm-generic/siginfo.h&gt;
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
id|__kernel_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|__kernel_uid_t
id|_uid
suffix:semicolon
multiline_comment|/* backwards compatibility */
DECL|member|_uid32
id|__kernel_uid32_t
id|_uid32
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
id|__kernel_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|__kernel_uid_t
id|_uid
suffix:semicolon
multiline_comment|/* backwards compatibility */
DECL|member|_sigval
id|sigval_t
id|_sigval
suffix:semicolon
DECL|member|_uid32
id|__kernel_uid32_t
id|_uid32
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
id|__kernel_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
id|__kernel_uid_t
id|_uid
suffix:semicolon
multiline_comment|/* backwards compatibility */
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
DECL|member|_uid32
id|__kernel_uid32_t
id|_uid32
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
r_struct
(brace
DECL|member|_addr
r_void
op_star
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
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
DECL|macro|UID16_SIGINFO_COMPAT_NEEDED
mdefine_line|#define UID16_SIGINFO_COMPAT_NEEDED
multiline_comment|/*&n; * How these fields are to be accessed.&n; */
DECL|macro|si_uid
macro_line|#undef si_uid
macro_line|#ifdef __KERNEL__
DECL|macro|si_uid
mdefine_line|#define si_uid&t;&t;_sifields._kill._uid32
DECL|macro|si_uid16
mdefine_line|#define si_uid16&t;_sifields._kill._uid
macro_line|#else
DECL|macro|si_uid
mdefine_line|#define si_uid&t;&t;_sifields._kill._uid
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
