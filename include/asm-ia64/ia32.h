macro_line|#ifndef _ASM_IA64_IA32_H
DECL|macro|_ASM_IA64_IA32_H
mdefine_line|#define _ASM_IA64_IA32_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
DECL|macro|IA32_NR_syscalls
mdefine_line|#define IA32_NR_syscalls&t;&t;285&t;/* length of syscall table */
DECL|macro|IA32_PAGE_SHIFT
mdefine_line|#define IA32_PAGE_SHIFT&t;&t;&t;12&t;/* 4KB pages */
macro_line|#ifndef __ASSEMBLY__
macro_line|# ifdef CONFIG_IA32_SUPPORT
r_extern
r_void
id|ia32_cpu_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia32_mem_init
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
r_extern
r_int
id|ia32_clone_tls
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_struct
id|pt_regs
op_star
id|childregs
)paren
suffix:semicolon
macro_line|# endif /* !CONFIG_IA32_SUPPORT */
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
macro_line|#if PAGE_SHIFT &gt; IA32_PAGE_SHIFT
r_extern
r_int
id|ia32_copy_partial_page_list
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ia32_drop_partial_page_list
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ia32_copy_partial_page_list
macro_line|# define ia32_copy_partial_page_list(a1, a2)&t;0
DECL|macro|ia32_drop_partial_page_list
macro_line|# define ia32_drop_partial_page_list(a1)&t;do { ; } while (0)
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_IA32_H */
eof
