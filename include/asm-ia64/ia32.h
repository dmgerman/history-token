macro_line|#ifndef _ASM_IA64_IA32_H
DECL|macro|_ASM_IA64_IA32_H
mdefine_line|#define _ASM_IA64_IA32_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_extern
r_void
id|ia32_cpu_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_gdt_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ia32_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|isr
)paren
suffix:semicolon
r_extern
r_int
id|ia32_intercept
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|isr
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_IA32_SUPPORT */
multiline_comment|/* Declare this unconditionally, so we don&squot;t get warnings for unreachable code.  */
r_extern
r_int
id|ia32_setup_frame1
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_IA32_H */
eof
