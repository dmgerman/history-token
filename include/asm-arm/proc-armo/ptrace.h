multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/ptrace.h&n; *&n; *  Copyright (C) 1996-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_PTRACE_H
DECL|macro|__ASM_PROC_PTRACE_H
mdefine_line|#define __ASM_PROC_PTRACE_H
DECL|macro|USR26_MODE
mdefine_line|#define USR26_MODE&t;0x00
DECL|macro|FIQ26_MODE
mdefine_line|#define FIQ26_MODE&t;0x01
DECL|macro|IRQ26_MODE
mdefine_line|#define IRQ26_MODE&t;0x02
DECL|macro|SVC26_MODE
mdefine_line|#define SVC26_MODE&t;0x03
DECL|macro|MODE_MASK
mdefine_line|#define MODE_MASK&t;0x03
DECL|macro|F_BIT
mdefine_line|#define F_BIT&t;&t;(1 &lt;&lt; 26)
DECL|macro|I_BIT
mdefine_line|#define I_BIT&t;&t;(1 &lt;&lt; 27)
DECL|macro|CC_V_BIT
mdefine_line|#define CC_V_BIT&t;(1 &lt;&lt; 28)
DECL|macro|CC_C_BIT
mdefine_line|#define CC_C_BIT&t;(1 &lt;&lt; 29)
DECL|macro|CC_Z_BIT
mdefine_line|#define CC_Z_BIT&t;(1 &lt;&lt; 30)
DECL|macro|CC_N_BIT
mdefine_line|#define CC_N_BIT&t;(1 &lt;&lt; 31)
DECL|macro|PCMASK
mdefine_line|#define PCMASK&t;&t;0xfc000003
macro_line|#ifndef __ASSEMBLY__
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
mdefine_line|#define user_mode(regs) &bslash;&n;&t;(processor_mode(regs) == USR26_MODE)
DECL|macro|thumb_mode
mdefine_line|#define thumb_mode(regs) (0)
DECL|macro|interrupts_enabled
mdefine_line|#define interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; I_BIT))
DECL|macro|fast_interrupts_enabled
mdefine_line|#define fast_interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_pc &amp; F_BIT))
DECL|macro|condition_codes
mdefine_line|#define condition_codes(regs) &bslash;&n;&t;((regs)-&gt;ARM_pc &amp; (CC_V_BIT|CC_C_BIT|CC_Z_BIT|CC_N_BIT))
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
id|F_BIT
op_or
id|I_BIT
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
id|F_BIT
op_or
id|I_BIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif
eof
