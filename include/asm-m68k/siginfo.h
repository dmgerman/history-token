macro_line|#ifndef _M68K_SIGINFO_H
DECL|macro|_M68K_SIGINFO_H
mdefine_line|#define _M68K_SIGINFO_H
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
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
DECL|member|_tid
id|timer_t
id|_tid
suffix:semicolon
multiline_comment|/* timer id */
DECL|member|_overrun
r_int
id|_overrun
suffix:semicolon
multiline_comment|/* overrun count */
DECL|member|_pad
r_char
id|_pad
(braket
r_sizeof
(paren
id|__ARCH_SI_UID_T
)paren
op_minus
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
DECL|member|_sigval
id|sigval_t
id|_sigval
suffix:semicolon
multiline_comment|/* same as below */
DECL|member|_sys_private
r_int
id|_sys_private
suffix:semicolon
multiline_comment|/* not to be passed to user */
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
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
DECL|function|copy_siginfo
r_static
r_inline
r_void
id|copy_siginfo
c_func
(paren
r_struct
id|siginfo
op_star
id|to
comma
r_struct
id|siginfo
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
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|to
)paren
)paren
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
l_int|3
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
