macro_line|#ifndef _ASM_IA64_SIGINFO_H
DECL|macro|_ASM_IA64_SIGINFO_H
mdefine_line|#define _ASM_IA64_SIGINFO_H
multiline_comment|/*&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|SI_PAD_SIZE
mdefine_line|#define SI_PAD_SIZE&t;((SI_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|HAVE_ARCH_SIGINFO_T
mdefine_line|#define HAVE_ARCH_SIGINFO_T
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
DECL|macro|HAVE_ARCH_COPY_SIGINFO_TO_USER
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO_TO_USER
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
DECL|member|__pad0
r_int
id|__pad0
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
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
r_struct
(brace
DECL|member|_addr
r_void
op_star
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_imm
r_int
id|_imm
suffix:semicolon
multiline_comment|/* immediate value for &quot;break&quot; */
DECL|member|_flags
r_int
r_int
id|_flags
suffix:semicolon
multiline_comment|/* see below */
DECL|member|_isr
r_int
r_int
id|_isr
suffix:semicolon
multiline_comment|/* isr */
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
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG (XPG requires a &quot;long&quot;) */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
multiline_comment|/* SIGPROF */
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
DECL|member|_pfm_ovfl_counters
r_int
r_int
id|_pfm_ovfl_counters
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* which PMU counter overflowed */
DECL|member|_sigprof
)brace
id|_sigprof
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t
)brace
id|siginfo_t
suffix:semicolon
DECL|macro|si_imm
mdefine_line|#define si_imm&t;&t;_sifields._sigfault._imm&t;/* as per UNIX SysV ABI spec */
DECL|macro|si_flags
mdefine_line|#define si_flags&t;_sifields._sigfault._flags
multiline_comment|/*&n; * si_isr is valid for SIGILL, SIGFPE, SIGSEGV, SIGBUS, and SIGTRAP provided that&n; * si_code is non-zero and __ISR_VALID is set in si_flags.&n; */
DECL|macro|si_isr
mdefine_line|#define si_isr&t;&t;_sifields._sigfault._isr
DECL|macro|si_pfm_ovfl
mdefine_line|#define si_pfm_ovfl&t;_sifields._sigprof._pfm_ovfl_counters
multiline_comment|/*&n; * Flag values for si_flags:&n; */
DECL|macro|__ISR_VALID_BIT
mdefine_line|#define __ISR_VALID_BIT&t;0
DECL|macro|__ISR_VALID
mdefine_line|#define __ISR_VALID&t;(1 &lt;&lt; __ISR_VALID_BIT)
multiline_comment|/*&n; * si_code values&n; * Positive values for kernel-generated signals.&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|__SI_PROF
mdefine_line|#define __SI_PROF&t;(6 &lt;&lt; 16)
macro_line|#endif
multiline_comment|/*&n; * SIGILL si_codes&n; */
DECL|macro|ILL_BADIADDR
mdefine_line|#define ILL_BADIADDR&t;(__SI_FAULT|9)&t;/* unimplemented instruction address */
DECL|macro|__ILL_BREAK
mdefine_line|#define __ILL_BREAK&t;(__SI_FAULT|10)&t;/* illegal break */
DECL|macro|__ILL_BNDMOD
mdefine_line|#define __ILL_BNDMOD&t;(__SI_FAULT|11)&t;/* bundle-update (modification) in progress */
DECL|macro|NSIGILL
macro_line|#undef NSIGILL
DECL|macro|NSIGILL
mdefine_line|#define NSIGILL&t;&t;11
multiline_comment|/*&n; * SIGFPE si_codes&n; */
DECL|macro|__FPE_DECOVF
mdefine_line|#define __FPE_DECOVF&t;(__SI_FAULT|9)&t;/* decimal overflow */
DECL|macro|__FPE_DECDIV
mdefine_line|#define __FPE_DECDIV&t;(__SI_FAULT|10)&t;/* decimal division by zero */
DECL|macro|__FPE_DECERR
mdefine_line|#define __FPE_DECERR&t;(__SI_FAULT|11)&t;/* packed decimal error */
DECL|macro|__FPE_INVASC
mdefine_line|#define __FPE_INVASC&t;(__SI_FAULT|12)&t;/* invalid ASCII digit */
DECL|macro|__FPE_INVDEC
mdefine_line|#define __FPE_INVDEC&t;(__SI_FAULT|13)&t;/* invalid decimal digit */
DECL|macro|NSIGFPE
macro_line|#undef NSIGFPE
DECL|macro|NSIGFPE
mdefine_line|#define NSIGFPE&t;&t;13
multiline_comment|/*&n; * SIGSEGV si_codes&n; */
DECL|macro|__SEGV_PSTKOVF
mdefine_line|#define __SEGV_PSTKOVF&t;(__SI_FAULT|3)&t;/* paragraph stack overflow */
DECL|macro|NSIGSEGV
macro_line|#undef NSIGSEGV
DECL|macro|NSIGSEGV
mdefine_line|#define NSIGSEGV&t;3
multiline_comment|/*&n; * SIGTRAP si_codes&n; */
DECL|macro|TRAP_BRANCH
mdefine_line|#define TRAP_BRANCH&t;(__SI_FAULT|3)&t;/* process taken branch trap */
DECL|macro|TRAP_HWBKPT
mdefine_line|#define TRAP_HWBKPT&t;(__SI_FAULT|4)&t;/* hardware breakpoint or watchpoint */
DECL|macro|NSIGTRAP
macro_line|#undef NSIGTRAP
DECL|macro|NSIGTRAP
mdefine_line|#define NSIGTRAP&t;4
multiline_comment|/*&n; * SIGPROF si_codes&n; */
DECL|macro|PROF_OVFL
mdefine_line|#define PROF_OVFL&t;(__SI_PROF|1)  /* some counters overflowed */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
r_static
r_inline
r_void
DECL|function|copy_siginfo
id|copy_siginfo
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
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
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
id|copy_siginfo_from_user
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
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_SIGINFO_H */
eof
