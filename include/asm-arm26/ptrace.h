macro_line|#ifndef __ASM_ARM_PTRACE_H
DECL|macro|__ASM_ARM_PTRACE_H
mdefine_line|#define __ASM_ARM_PTRACE_H
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS&t;&t;12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS&t;&t;13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS&t;14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS&t;15
DECL|macro|PTRACE_OLDSETOPTIONS
mdefine_line|#define PTRACE_OLDSETOPTIONS    21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
DECL|macro|MODE_USR26
mdefine_line|#define MODE_USR26      0x00000000
DECL|macro|MODE_FIQ26
mdefine_line|#define MODE_FIQ26      0x00000001
DECL|macro|MODE_IRQ26
mdefine_line|#define MODE_IRQ26      0x00000002
DECL|macro|MODE_SVC26
mdefine_line|#define MODE_SVC26      0x00000003
DECL|macro|MODE_MASK
mdefine_line|#define MODE_MASK       0x00000003
DECL|macro|PSR_F_BIT
mdefine_line|#define PSR_F_BIT       0x04000000
DECL|macro|PSR_I_BIT
mdefine_line|#define PSR_I_BIT       0x08000000
DECL|macro|PSR_V_BIT
mdefine_line|#define PSR_V_BIT       0x10000000
DECL|macro|PSR_C_BIT
mdefine_line|#define PSR_C_BIT       0x20000000
DECL|macro|PSR_Z_BIT
mdefine_line|#define PSR_Z_BIT       0x40000000
DECL|macro|PSR_N_BIT
mdefine_line|#define PSR_N_BIT       0x80000000
DECL|macro|PCMASK
mdefine_line|#define PCMASK          0xfc000003
macro_line|#ifndef __ASSEMBLY__
DECL|macro|pc_pointer
mdefine_line|#define pc_pointer(v) ((v) &amp; ~PCMASK)   /* convert v to pc type address */
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) (pc_pointer((regs)-&gt;ARM_pc)) /* get pc */
multiline_comment|/* this struct defines the way the registers are stored on the&n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|uregs
r_int
id|uregs
(braket
l_int|17
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ARM_pc
mdefine_line|#define ARM_pc&t;&t;uregs[15]
DECL|macro|ARM_lr
mdefine_line|#define ARM_lr&t;&t;uregs[14]
DECL|macro|ARM_sp
mdefine_line|#define ARM_sp&t;&t;uregs[13]
DECL|macro|ARM_ip
mdefine_line|#define ARM_ip&t;&t;uregs[12]
DECL|macro|ARM_fp
mdefine_line|#define ARM_fp&t;&t;uregs[11]
DECL|macro|ARM_r10
mdefine_line|#define ARM_r10&t;&t;uregs[10]
DECL|macro|ARM_r9
mdefine_line|#define ARM_r9&t;&t;uregs[9]
DECL|macro|ARM_r8
mdefine_line|#define ARM_r8&t;&t;uregs[8]
DECL|macro|ARM_r7
mdefine_line|#define ARM_r7&t;&t;uregs[7]
DECL|macro|ARM_r6
mdefine_line|#define ARM_r6&t;&t;uregs[6]
DECL|macro|ARM_r5
mdefine_line|#define ARM_r5&t;&t;uregs[5]
DECL|macro|ARM_r4
mdefine_line|#define ARM_r4&t;&t;uregs[4]
DECL|macro|ARM_r3
mdefine_line|#define ARM_r3&t;&t;uregs[3]
DECL|macro|ARM_r2
mdefine_line|#define ARM_r2&t;&t;uregs[2]
DECL|macro|ARM_r1
mdefine_line|#define ARM_r1&t;&t;uregs[1]
DECL|macro|ARM_r0
mdefine_line|#define ARM_r0&t;&t;uregs[0]
DECL|macro|ARM_ORIG_r0
mdefine_line|#define ARM_ORIG_r0&t;uregs[16]
macro_line|#ifdef __KERNEL__
DECL|macro|processor_mode
mdefine_line|#define processor_mode(regs) &bslash;&n;&t;((regs)-&gt;ARM_pc &amp; MODE_MASK)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) &bslash;&n;&t;(processor_mode(regs) == MODE_USR26)
DECL|macro|interrupts_enabled
mdefine_line|#define interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; PSR_I_BIT))
DECL|macro|fast_interrupts_enabled
mdefine_line|#define fast_interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; PSR_F_BIT))
DECL|macro|condition_codes
mdefine_line|#define condition_codes(regs) &bslash;&n;&t;((regs)-&gt;ARM_pc &amp; (PSR_V_BIT|PSR_C_BIT|PSR_Z_BIT|PSR_N_BIT))
multiline_comment|/* Are the current registers suitable for user mode?&n; * (used to maintain security in signal handlers)&n; */
DECL|function|valid_user_regs
r_static
r_inline
r_int
id|valid_user_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
(paren
id|regs-&gt;ARM_pc
op_amp
(paren
id|PSR_F_BIT
op_or
id|PSR_I_BIT
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * force it to be something sensible&n;&t; */
id|regs-&gt;ARM_pc
op_and_assign
op_complement
(paren
id|MODE_MASK
op_or
id|PSR_F_BIT
op_or
id|PSR_I_BIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
mdefine_line|#define predicate(x)    (x &amp; 0xf0000000)
DECL|macro|PREDICATE_ALWAYS
mdefine_line|#define PREDICATE_ALWAYS        0xe0000000
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif
eof
