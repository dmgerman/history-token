multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999, 2001, 2003 Ralf Baechle&n; * Copyright (C) 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SIGINFO_H
DECL|macro|_ASM_SIGINFO_H
mdefine_line|#define _ASM_SIGINFO_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SIGEV_HEAD_SIZE
mdefine_line|#define SIGEV_HEAD_SIZE&t;(sizeof(long) + 2*sizeof(int))
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE-SIGEV_HEAD_SIZE) / sizeof(int))
DECL|macro|SI_PAD_SIZE
mdefine_line|#define SI_PAD_SIZE&t;((SI_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
multiline_comment|/*&n; * We duplicate the generic versions - &lt;asm-generic/siginfo.h&gt; is just borked&n; * by design ...&n; */
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
r_struct
id|siginfo
suffix:semicolon
macro_line|#include &lt;asm-generic/siginfo.h&gt;
multiline_comment|/* This structure matches the 32/n32 ABIs for source compatibility but&n;   has Linux extensions.  */
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
macro_line|#ifdef CONFIG_MIPS32
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
macro_line|#endif
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
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(CONFIG_COMPAT)
macro_line|#include &lt;linux/compat.h&gt;
DECL|macro|SI_PAD_SIZE32
mdefine_line|#define SI_PAD_SIZE32   ((SI_MAX_SIZE/sizeof(int)) - 3)
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
id|s32
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
DECL|struct|siginfo32
r_typedef
r_struct
id|siginfo32
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
id|SI_PAD_SIZE32
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
id|compat_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|compat_uid_t
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
id|compat_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
id|compat_uid_t
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_utime
id|compat_clock_t
id|_utime
suffix:semicolon
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_stime
id|compat_clock_t
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
id|compat_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_utime
id|compat_clock_t
id|_utime
suffix:semicolon
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_stime
id|compat_clock_t
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
id|s32
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
id|compat_pid_t
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
id|compat_uid_t
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
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t32
)brace
id|siginfo_t32
suffix:semicolon
macro_line|#endif /* defined(__KERNEL__) &amp;&amp; defined(CONFIG_COMPAT) */
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
mdefine_line|#define SI_MESGQ __SI_CODE(__SI_MESGQ,-4) /* sent by real time mesq state change */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Duplicated here because of &lt;asm-generic/siginfo.h&gt; braindamage ...&n; */
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
