macro_line|#ifndef _PPC64_PPC32_H
DECL|macro|_PPC64_PPC32_H
mdefine_line|#define _PPC64_PPC32_H
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;asm/siginfo.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
multiline_comment|/*&n; * Data types and macros for providing 32b PowerPC support.&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Use this to get at 32-bit user passed pointers. */
multiline_comment|/* Things to consider: the low-level assembly stub does&n;   srl x, 0, x for first four arguments, so if you have&n;   pointer to something in the first four arguments, just&n;   declare it as a pointer, not u32. On the other side, &n;   arguments from 5th onwards should be declared as u32&n;   for pointers, and need AA() around each usage.&n;   A() macro should be used for places where you e.g.&n;   have some internal variable u32 and just want to get&n;   rid of a compiler warning. AA() has to be used in&n;   places where you want to convert a function argument&n;   to 32bit pointer or when you e.g. access pt_regs&n;   structure and want to consider 32bit registers only.&n;   -&n; */
DECL|macro|A
mdefine_line|#define A(__x) ((unsigned long)(__x))
DECL|macro|AA
mdefine_line|#define AA(__x)&t;&t;&t;&t;&bslash;&n;({&t;unsigned long __ret;&t;&t;&bslash;&n;&t;__asm__ (&quot;clrldi&t;%0, %0, 32&quot;&t;&bslash;&n;&t;&t; : &quot;=r&quot; (__ret)&t;&t;&bslash;&n;&t;&t; : &quot;0&quot; (__x));&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* These are here to support 32-bit syscalls on a 64-bit kernel. */
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
r_int
r_int
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
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|compat_clock_t
id|_utime
suffix:semicolon
DECL|member|_stime
id|compat_clock_t
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
r_int
r_int
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
DECL|typedef|siginfo_t32
)brace
id|siginfo_t32
suffix:semicolon
DECL|macro|__old_sigaction32
mdefine_line|#define __old_sigaction32&t;old_sigaction32
DECL|struct|__old_sigaction32
r_struct
id|__old_sigaction32
(brace
DECL|member|sa_handler
r_int
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|compat_old_sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* not used by Linux/SPARC yet */
)brace
suffix:semicolon
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal with 32 bits */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
)brace
suffix:semicolon
DECL|struct|sigaltstack_32
r_typedef
r_struct
id|sigaltstack_32
(brace
DECL|member|ss_sp
r_int
r_int
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
id|compat_size_t
id|ss_size
suffix:semicolon
DECL|typedef|stack_32_t
)brace
id|stack_32_t
suffix:semicolon
DECL|struct|sigcontext32
r_struct
id|sigcontext32
(brace
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|handler
r_int
r_int
id|handler
suffix:semicolon
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|regs
id|u32
id|regs
suffix:semicolon
multiline_comment|/* 4 byte pointer to the pt_regs32 structure. */
)brace
suffix:semicolon
DECL|struct|ucontext32
r_struct
id|ucontext32
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_int
r_int
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_32_t
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|sigcontext32
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
DECL|struct|ipc_kludge_32
r_struct
id|ipc_kludge_32
(brace
DECL|member|msgp
r_int
r_int
id|msgp
suffix:semicolon
DECL|member|msgtyp
r_int
id|msgtyp
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif  /* _PPC64_PPC32_H */
eof
