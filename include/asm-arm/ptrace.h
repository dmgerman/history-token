macro_line|#ifndef __ASM_ARM_PTRACE_H
DECL|macro|__ASM_ARM_PTRACE_H
mdefine_line|#define __ASM_ARM_PTRACE_H
macro_line|#include &lt;asm/proc/ptrace.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|pc_pointer
mdefine_line|#define pc_pointer(v) &bslash;&n;&t;((v) &amp; ~PCMASK)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) &bslash;&n;&t;(pc_pointer((regs)-&gt;ARM_pc))
macro_line|#ifdef __KERNEL__
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS&t;&t;12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS&t;&t;13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS&t;14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS&t;15
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|predicate
mdefine_line|#define predicate(x)&t;(x &amp; 0xf0000000)
DECL|macro|PREDICATE_ALWAYS
mdefine_line|#define PREDICATE_ALWAYS&t;0xe0000000
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
