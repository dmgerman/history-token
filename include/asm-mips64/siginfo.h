multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999, 2001 Ralf Baechle&n; * Copyright (C) 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SIGINFO_H
DECL|macro|_ASM_SIGINFO_H
mdefine_line|#define _ASM_SIGINFO_H
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
DECL|macro|HAVE_ARCH_SIGEVENT_T
mdefine_line|#define HAVE_ARCH_SIGEVENT_T
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
DECL|macro|HAVE_ARCH_COPY_SIGINFO_TO_USER
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO_TO_USER
macro_line|#include &lt;asm-generic/siginfo.h&gt;
multiline_comment|/* The sigval union matches IRIX 32/n32 ABIs for binary compatibility. */
multiline_comment|/* This structure matches IRIX 32/n32 ABIs for binary compatibility but&n;   has Linux extensions.  */
DECL|struct|siginfo
r_typedef
r_struct
id|siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
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
DECL|member|_utime
id|clock_t
id|_utime
suffix:semicolon
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_stime
id|clock_t
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* IRIX SIGCHLD */
r_struct
(brace
DECL|member|_pid
id|pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_utime
id|clock_t
id|_utime
suffix:semicolon
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_stime
id|clock_t
id|_stime
suffix:semicolon
DECL|member|_irix_sigchld
)brace
id|_irix_sigchld
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
multiline_comment|/* SIGPOLL, SIGXFSZ (To do ...)  */
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
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t
)brace
id|siginfo_t
suffix:semicolon
multiline_comment|/*&n; * si_code values&n; * Again these have been choosen to be IRIX compatible.&n; */
DECL|macro|SI_ASYNCIO
macro_line|#undef SI_ASYNCIO
DECL|macro|SI_TIMER
macro_line|#undef SI_TIMER
DECL|macro|SI_MESGQ
macro_line|#undef SI_MESGQ
DECL|macro|SI_ASYNCIO
mdefine_line|#define SI_ASYNCIO&t;-2&t;/* sent by AIO completion */
DECL|macro|SI_TIMER
mdefine_line|#define SI_TIMER __SI_CODE(__SI_TIMER,-3) /* sent by timer expiration */
DECL|macro|SI_MESGQ
mdefine_line|#define SI_MESGQ&t;-4&t;/* sent by real time mesq state change */
multiline_comment|/*&n; * sigevent definitions&n; * &n; * It seems likely that SIGEV_THREAD will have to be handled from &n; * userspace, libpthread transmuting it to SIGEV_SIGNAL, which the&n; * thread manager then catches and does the appropriate nonsense.&n; * However, everything is written out here so as to not get lost.&n; */
DECL|macro|SIGEV_NONE
macro_line|#undef SIGEV_NONE
DECL|macro|SIGEV_SIGNAL
macro_line|#undef SIGEV_SIGNAL
DECL|macro|SIGEV_THREAD
macro_line|#undef SIGEV_THREAD
DECL|macro|SIGEV_NONE
mdefine_line|#define SIGEV_NONE&t;128&t;/* other notification: meaningless */
DECL|macro|SIGEV_SIGNAL
mdefine_line|#define SIGEV_SIGNAL&t;129&t;/* notify via signal */
DECL|macro|SIGEV_CALLBACK
mdefine_line|#define SIGEV_CALLBACK&t;130&t;/* ??? */
DECL|macro|SIGEV_THREAD
mdefine_line|#define SIGEV_THREAD&t;131&t;/* deliver via thread creation */
multiline_comment|/* XXX This one isn&squot;t yet IRIX / ABI compatible.  */
DECL|struct|sigevent
r_typedef
r_struct
id|sigevent
(brace
DECL|member|sigev_notify
r_int
id|sigev_notify
suffix:semicolon
DECL|member|sigev_value
id|sigval_t
id|sigev_value
suffix:semicolon
DECL|member|sigev_signo
r_int
id|sigev_signo
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SIGEV_PAD_SIZE
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_function
r_void
(paren
op_star
id|_function
)paren
(paren
id|sigval_t
)paren
suffix:semicolon
DECL|member|_attribute
r_void
op_star
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
DECL|typedef|sigevent_t
)brace
id|sigevent_t
suffix:semicolon
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
macro_line|#endif
macro_line|#endif /* _ASM_SIGINFO_H */
eof
