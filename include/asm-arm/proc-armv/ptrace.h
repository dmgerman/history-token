multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/ptrace.h&n; *&n; *  Copyright (C) 1996-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_PTRACE_H
DECL|macro|__ASM_PROC_PTRACE_H
mdefine_line|#define __ASM_PROC_PTRACE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * PSR bits&n; */
DECL|macro|USR26_MODE
mdefine_line|#define USR26_MODE&t;0x00000000
DECL|macro|FIQ26_MODE
mdefine_line|#define FIQ26_MODE&t;0x00000001
DECL|macro|IRQ26_MODE
mdefine_line|#define IRQ26_MODE&t;0x00000002
DECL|macro|SVC26_MODE
mdefine_line|#define SVC26_MODE&t;0x00000003
DECL|macro|USR_MODE
mdefine_line|#define USR_MODE&t;0x00000010
DECL|macro|FIQ_MODE
mdefine_line|#define FIQ_MODE&t;0x00000011
DECL|macro|IRQ_MODE
mdefine_line|#define IRQ_MODE&t;0x00000012
DECL|macro|SVC_MODE
mdefine_line|#define SVC_MODE&t;0x00000013
DECL|macro|ABT_MODE
mdefine_line|#define ABT_MODE&t;0x00000017
DECL|macro|UND_MODE
mdefine_line|#define UND_MODE&t;0x0000001b
DECL|macro|SYSTEM_MODE
mdefine_line|#define SYSTEM_MODE&t;0x0000001f
DECL|macro|MODE32_BIT
mdefine_line|#define MODE32_BIT&t;0x00000010
DECL|macro|MODE_MASK
mdefine_line|#define MODE_MASK&t;0x0000001f
DECL|macro|PSR_T_BIT
mdefine_line|#define PSR_T_BIT&t;0x00000020
DECL|macro|PSR_F_BIT
mdefine_line|#define PSR_F_BIT&t;0x00000040
DECL|macro|PSR_I_BIT
mdefine_line|#define PSR_I_BIT&t;0x00000080
DECL|macro|PSR_J_BIT
mdefine_line|#define PSR_J_BIT&t;0x01000000
DECL|macro|PSR_V_BIT
mdefine_line|#define PSR_V_BIT&t;0x10000000
DECL|macro|PSR_C_BIT
mdefine_line|#define PSR_C_BIT&t;0x20000000
DECL|macro|PSR_Z_BIT
mdefine_line|#define PSR_Z_BIT&t;0x40000000
DECL|macro|PSR_N_BIT
mdefine_line|#define PSR_N_BIT&t;0x80000000
DECL|macro|PCMASK
mdefine_line|#define PCMASK&t;&t;0
multiline_comment|/*&n; * CR1 bits&n; */
DECL|macro|CR1_M
mdefine_line|#define CR1_M&t;&t;0x00000001&t;/* MMU&t;&t;&t;*/
DECL|macro|CR1_A
mdefine_line|#define CR1_A&t;&t;0x00000002&t;/* Alignment fault&t;*/
DECL|macro|CR1_C
mdefine_line|#define CR1_C&t;&t;0x00000004&t;/* Dcache&t;&t;*/
DECL|macro|CR1_W
mdefine_line|#define CR1_W&t;&t;0x00000008&t;/* Write buffer&t;&t;*/
DECL|macro|CR1_P
mdefine_line|#define CR1_P&t;&t;0x00000010&t;/* Prog32&t;&t;*/
DECL|macro|CR1_D
mdefine_line|#define CR1_D&t;&t;0x00000020&t;/* Data32&t;&t;*/
DECL|macro|CR1_L
mdefine_line|#define CR1_L&t;&t;0x00000040&t;/* Late abort&t;&t;*/
DECL|macro|CR1_B
mdefine_line|#define CR1_B&t;&t;0x00000080&t;/* Big endian&t;&t;*/
DECL|macro|CR1_S
mdefine_line|#define CR1_S&t;&t;0x00000100&t;/* System protection&t;*/
DECL|macro|CR1_R
mdefine_line|#define CR1_R&t;&t;0x00000200&t;/* ROM protection&t;*/
DECL|macro|CR1_F
mdefine_line|#define CR1_F&t;&t;0x00000400
DECL|macro|CR1_Z
mdefine_line|#define CR1_Z&t;&t;0x00000800&t;/* BTB enable&t;&t;*/
DECL|macro|CR1_I
mdefine_line|#define CR1_I&t;&t;0x00001000&t;/* Icache&t;&t;*/
DECL|macro|CR1_V
mdefine_line|#define CR1_V&t;&t;0x00002000&t;/* Vector relocation&t;*/
DECL|macro|CR1_RR
mdefine_line|#define CR1_RR&t;&t;0x00004000&t;/* Round Robin&t;&t;*/
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
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ARM_cpsr
mdefine_line|#define ARM_cpsr&t;uregs[16]
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
mdefine_line|#define ARM_ORIG_r0&t;uregs[17]
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;&bslash;&n;&t;(((regs)-&gt;ARM_cpsr &amp; 0xf) == 0)
macro_line|#ifdef CONFIG_ARM_THUMB
DECL|macro|thumb_mode
mdefine_line|#define thumb_mode(regs) &bslash;&n;&t;(((regs)-&gt;ARM_cpsr &amp; PSR_T_BIT))
macro_line|#else
DECL|macro|thumb_mode
mdefine_line|#define thumb_mode(regs) (0)
macro_line|#endif
DECL|macro|processor_mode
mdefine_line|#define processor_mode(regs) &bslash;&n;&t;((regs)-&gt;ARM_cpsr &amp; MODE_MASK)
DECL|macro|interrupts_enabled
mdefine_line|#define interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_cpsr &amp; PSR_I_BIT))
DECL|macro|fast_interrupts_enabled
mdefine_line|#define fast_interrupts_enabled(regs) &bslash;&n;&t;(!((regs)-&gt;ARM_cpsr &amp; PSR_F_BIT))
DECL|macro|condition_codes
mdefine_line|#define condition_codes(regs) &bslash;&n;&t;((regs)-&gt;ARM_cpsr &amp; (PSR_V_BIT|PSR_C_BIT|PSR_Z_BIT|PSR_N_BIT))
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
id|regs-&gt;ARM_cpsr
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
multiline_comment|/*&n;&t; * Force CPSR to something logical...&n;&t; */
id|regs-&gt;ARM_cpsr
op_and_assign
(paren
id|PSR_V_BIT
op_or
id|PSR_C_BIT
op_or
id|PSR_Z_BIT
op_or
id|PSR_N_BIT
op_or
id|MODE32_BIT
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
