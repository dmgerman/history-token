multiline_comment|/* registers.h: register frame declarations&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * notes:&n; *&n; * (1) that the members of all these structures are carefully aligned to permit&n; *     usage of STD/STDF instructions&n; *&n; * (2) if you change these structures, you must change the code in&n; *     arch/frvnommu/kernel/{break.S,entry.S,switch_to.S,gdb-stub.c}&n; *&n; *&n; * the kernel stack space block looks like this:&n; *&n; *&t;+0x2000&t;+----------------------&n; *&t;&t;| union {&n; *&t;&t;|&t;struct user_context&n; *&t;&t;|&t;struct pt_regs [user exception]&n; *&t;&t;| }&n; *&t;&t;+---------------------- &lt;-- __kernel_frame0_ptr (maybe GR28)&n; *&t;&t;|&n; *&t;&t;| kernel stack&n; *&t;&t;|&n; *&t;&t;|......................&n; *&t;&t;| struct pt_regs [kernel exception]&n; *&t;&t;|...................... &lt;-- __kernel_frame0_ptr (maybe GR28)&n; *&t;&t;|&n; *&t;&t;| kernel stack&n; *&t;&t;|&n; *&t;&t;|...................... &lt;-- stack pointer (GR1)&n; *&t;&t;|&n; *&t;&t;| unused stack space&n; *&t;&t;|&n; *&t;&t;+----------------------&n; *&t;&t;| struct thread_info&n; *&t;+0x0000&t;+---------------------- &lt;-- __current_thread_info (GR15);&n; *&n; * note that GR28 points to the current exception frame&n; */
macro_line|#ifndef _ASM_REGISTERS_H
DECL|macro|_ASM_REGISTERS_H
mdefine_line|#define _ASM_REGISTERS_H
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__OFFSET
mdefine_line|#define __OFFSET(X)&t;(X)
DECL|macro|__OFFSETC
mdefine_line|#define __OFFSETC(X,N)&t;xxxxxxxxxxxxxxxxxxxxxxxx
macro_line|#else
DECL|macro|__OFFSET
mdefine_line|#define __OFFSET(X)&t;((X)*4)
DECL|macro|__OFFSETC
mdefine_line|#define __OFFSETC(X,N)&t;((X)*4+(N))
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Exception/Interrupt frame&n; * - held on kernel stack&n; * - 8-byte aligned on stack (old SP is saved in frame)&n; * - GR0 is fixed 0, so we don&squot;t save it&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
multiline_comment|/* Processor Status Register */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* Integer Status Register */
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/* Condition Code Register */
DECL|member|cccr
r_int
r_int
id|cccr
suffix:semicolon
multiline_comment|/* Condition Code for Conditional Insns Register */
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* Link Register */
DECL|member|lcr
r_int
r_int
id|lcr
suffix:semicolon
multiline_comment|/* Loop Count Register */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* Program Counter Register */
DECL|member|__status
r_int
r_int
id|__status
suffix:semicolon
multiline_comment|/* exception status */
DECL|member|syscallno
r_int
r_int
id|syscallno
suffix:semicolon
multiline_comment|/* syscall number or -1 */
DECL|member|orig_gr8
r_int
r_int
id|orig_gr8
suffix:semicolon
multiline_comment|/* original syscall arg #1 */
DECL|member|gner0
r_int
r_int
id|gner0
suffix:semicolon
DECL|member|gner1
r_int
r_int
id|gner1
suffix:semicolon
DECL|member|iacc0
r_int
r_int
r_int
id|iacc0
suffix:semicolon
DECL|member|tbr
r_int
r_int
id|tbr
suffix:semicolon
multiline_comment|/* GR0 is fixed zero, so we use this for TBR */
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* GR1: USP/KSP */
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
multiline_comment|/* GR2: FP */
DECL|member|gr3
r_int
r_int
id|gr3
suffix:semicolon
DECL|member|gr4
r_int
r_int
id|gr4
suffix:semicolon
DECL|member|gr5
r_int
r_int
id|gr5
suffix:semicolon
DECL|member|gr6
r_int
r_int
id|gr6
suffix:semicolon
DECL|member|gr7
r_int
r_int
id|gr7
suffix:semicolon
multiline_comment|/* syscall number */
DECL|member|gr8
r_int
r_int
id|gr8
suffix:semicolon
multiline_comment|/* 1st syscall param; syscall return */
DECL|member|gr9
r_int
r_int
id|gr9
suffix:semicolon
multiline_comment|/* 2nd syscall param */
DECL|member|gr10
r_int
r_int
id|gr10
suffix:semicolon
multiline_comment|/* 3rd syscall param */
DECL|member|gr11
r_int
r_int
id|gr11
suffix:semicolon
multiline_comment|/* 4th syscall param */
DECL|member|gr12
r_int
r_int
id|gr12
suffix:semicolon
multiline_comment|/* 5th syscall param */
DECL|member|gr13
r_int
r_int
id|gr13
suffix:semicolon
multiline_comment|/* 6th syscall param */
DECL|member|gr14
r_int
r_int
id|gr14
suffix:semicolon
DECL|member|gr15
r_int
r_int
id|gr15
suffix:semicolon
DECL|member|gr16
r_int
r_int
id|gr16
suffix:semicolon
multiline_comment|/* GP pointer */
DECL|member|gr17
r_int
r_int
id|gr17
suffix:semicolon
multiline_comment|/* small data */
DECL|member|gr18
r_int
r_int
id|gr18
suffix:semicolon
multiline_comment|/* PIC/PID */
DECL|member|gr19
r_int
r_int
id|gr19
suffix:semicolon
DECL|member|gr20
r_int
r_int
id|gr20
suffix:semicolon
DECL|member|gr21
r_int
r_int
id|gr21
suffix:semicolon
DECL|member|gr22
r_int
r_int
id|gr22
suffix:semicolon
DECL|member|gr23
r_int
r_int
id|gr23
suffix:semicolon
DECL|member|gr24
r_int
r_int
id|gr24
suffix:semicolon
DECL|member|gr25
r_int
r_int
id|gr25
suffix:semicolon
DECL|member|gr26
r_int
r_int
id|gr26
suffix:semicolon
DECL|member|gr27
r_int
r_int
id|gr27
suffix:semicolon
DECL|member|next_frame
r_struct
id|pt_regs
op_star
id|next_frame
suffix:semicolon
multiline_comment|/* GR28 - next exception frame */
DECL|member|gr29
r_int
r_int
id|gr29
suffix:semicolon
multiline_comment|/* GR29 - OS reserved */
DECL|member|gr30
r_int
r_int
id|gr30
suffix:semicolon
multiline_comment|/* GR30 - OS reserved */
DECL|member|gr31
r_int
r_int
id|gr31
suffix:semicolon
multiline_comment|/* GR31 - OS reserved */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|REG_PSR
mdefine_line|#define REG_PSR&t;&t;__OFFSET( 0)&t;/* Processor Status Register */
DECL|macro|REG_ISR
mdefine_line|#define REG_ISR&t;&t;__OFFSET( 1)&t;/* Integer Status Register */
DECL|macro|REG_CCR
mdefine_line|#define REG_CCR&t;&t;__OFFSET( 2)&t;/* Condition Code Register */
DECL|macro|REG_CCCR
mdefine_line|#define REG_CCCR&t;__OFFSET( 3)&t;/* Condition Code for Conditional Insns Register */
DECL|macro|REG_LR
mdefine_line|#define REG_LR&t;&t;__OFFSET( 4)&t;/* Link Register */
DECL|macro|REG_LCR
mdefine_line|#define REG_LCR&t;&t;__OFFSET( 5)&t;/* Loop Count Register */
DECL|macro|REG_PC
mdefine_line|#define REG_PC&t;&t;__OFFSET( 6)&t;/* Program Counter */
DECL|macro|REG__STATUS
mdefine_line|#define REG__STATUS&t;__OFFSET( 7)&t;/* exception status */
DECL|macro|REG__STATUS_STEP
mdefine_line|#define REG__STATUS_STEP&t;0x00000001&t;/* - reenable single stepping on return */
DECL|macro|REG__STATUS_STEPPED
mdefine_line|#define REG__STATUS_STEPPED&t;0x00000002&t;/* - single step caused exception */
DECL|macro|REG__STATUS_BROKE
mdefine_line|#define REG__STATUS_BROKE&t;0x00000004&t;/* - BREAK insn caused exception */
DECL|macro|REG__STATUS_SYSC_ENTRY
mdefine_line|#define REG__STATUS_SYSC_ENTRY&t;0x40000000&t;/* - T on syscall entry (ptrace.c only) */
DECL|macro|REG__STATUS_SYSC_EXIT
mdefine_line|#define REG__STATUS_SYSC_EXIT&t;0x80000000&t;/* - T on syscall exit (ptrace.c only) */
DECL|macro|REG_SYSCALLNO
mdefine_line|#define REG_SYSCALLNO&t;__OFFSET( 8)&t;/* syscall number or -1 */
DECL|macro|REG_ORIG_GR8
mdefine_line|#define REG_ORIG_GR8&t;__OFFSET( 9)&t;/* saved GR8 for signal handling */
DECL|macro|REG_GNER0
mdefine_line|#define REG_GNER0&t;__OFFSET(10)
DECL|macro|REG_GNER1
mdefine_line|#define REG_GNER1&t;__OFFSET(11)
DECL|macro|REG_IACC0
mdefine_line|#define REG_IACC0&t;__OFFSET(12)
DECL|macro|REG_TBR
mdefine_line|#define REG_TBR&t;&t;__OFFSET(14)&t;/* Trap Vector Register */
DECL|macro|REG_GR
mdefine_line|#define REG_GR(R)&t;__OFFSET((14+(R)))
DECL|macro|REG__END
mdefine_line|#define REG__END&t;REG_GR(32)
DECL|macro|REG_SP
mdefine_line|#define REG_SP&t;&t;REG_GR(1)
DECL|macro|REG_FP
mdefine_line|#define REG_FP&t;&t;REG_GR(2)
DECL|macro|REG_PREV_FRAME
mdefine_line|#define REG_PREV_FRAME&t;REG_GR(28)&t;/* previous exception frame pointer (old gr28 value) */
DECL|macro|REG_CURR_TASK
mdefine_line|#define REG_CURR_TASK&t;REG_GR(29)&t;/* current task */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * extension tacked in front of the exception frame in debug mode&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pt_debug_regs
r_struct
id|pt_debug_regs
(brace
DECL|member|bpsr
r_int
r_int
id|bpsr
suffix:semicolon
DECL|member|dcr
r_int
r_int
id|dcr
suffix:semicolon
DECL|member|brr
r_int
r_int
id|brr
suffix:semicolon
DECL|member|nmar
r_int
r_int
id|nmar
suffix:semicolon
DECL|member|normal_regs
r_struct
id|pt_regs
id|normal_regs
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|REG_NMAR
mdefine_line|#define REG_NMAR&t;&t;__OFFSET(-1)
DECL|macro|REG_BRR
mdefine_line|#define REG_BRR&t;&t;&t;__OFFSET(-2)
DECL|macro|REG_DCR
mdefine_line|#define REG_DCR&t;&t;&t;__OFFSET(-3)
DECL|macro|REG_BPSR
mdefine_line|#define REG_BPSR&t;&t;__OFFSET(-4)
DECL|macro|REG__DEBUG_XTRA
mdefine_line|#define REG__DEBUG_XTRA&t;&t;__OFFSET(4)
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * userspace registers&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|user_int_regs
r_struct
id|user_int_regs
(brace
multiline_comment|/* integer registers&n;&t; * - up to gr[31] mirror pt_regs&n;&t; * - total size must be multiple of 8 bytes&n;&t; */
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
multiline_comment|/* Processor Status Register */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* Integer Status Register */
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/* Condition Code Register */
DECL|member|cccr
r_int
r_int
id|cccr
suffix:semicolon
multiline_comment|/* Condition Code for Conditional Insns Register */
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* Link Register */
DECL|member|lcr
r_int
r_int
id|lcr
suffix:semicolon
multiline_comment|/* Loop Count Register */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* Program Counter Register */
DECL|member|__status
r_int
r_int
id|__status
suffix:semicolon
multiline_comment|/* exception status */
DECL|member|syscallno
r_int
r_int
id|syscallno
suffix:semicolon
multiline_comment|/* syscall number or -1 */
DECL|member|orig_gr8
r_int
r_int
id|orig_gr8
suffix:semicolon
multiline_comment|/* original syscall arg #1 */
DECL|member|gner
r_int
r_int
id|gner
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|iacc
r_int
r_int
r_int
id|iacc
(braket
l_int|1
)braket
suffix:semicolon
r_union
(brace
DECL|member|tbr
r_int
r_int
id|tbr
suffix:semicolon
DECL|member|gr
r_int
r_int
id|gr
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|user_fpmedia_regs
r_struct
id|user_fpmedia_regs
(brace
multiline_comment|/* FP/Media registers */
DECL|member|fr
r_int
r_int
id|fr
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fner
r_int
r_int
id|fner
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|msr
r_int
r_int
id|msr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|acc
r_int
r_int
id|acc
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|accg
r_int
r_char
id|accg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fsr
r_int
r_int
id|fsr
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|user_context
r_struct
id|user_context
(brace
DECL|member|i
r_struct
id|user_int_regs
id|i
suffix:semicolon
DECL|member|f
r_struct
id|user_fpmedia_regs
id|f
suffix:semicolon
multiline_comment|/* we provide a context extension so that we can save the regs for CPUs that&n;&t; * implement many more of Fujitsu&squot;s lavish register spec&n;&t; */
DECL|member|extension
r_void
op_star
id|extension
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|NR_USER_INT_REGS
mdefine_line|#define NR_USER_INT_REGS&t;(14 + 64)
DECL|macro|NR_USER_FPMEDIA_REGS
mdefine_line|#define NR_USER_FPMEDIA_REGS&t;(64 + 2 + 2 + 8 + 8/4 + 1)
DECL|macro|NR_USER_CONTEXT
mdefine_line|#define NR_USER_CONTEXT&t;&t;(NR_USER_INT_REGS + NR_USER_FPMEDIA_REGS + 1)
DECL|macro|USER_CONTEXT_SIZE
mdefine_line|#define USER_CONTEXT_SIZE&t;(((NR_USER_CONTEXT + 1) &amp; ~1) * 4)
DECL|macro|__THREAD_FRAME
mdefine_line|#define __THREAD_FRAME&t;&t;__OFFSET(0)
DECL|macro|__THREAD_CURR
mdefine_line|#define __THREAD_CURR&t;&t;__OFFSET(1)
DECL|macro|__THREAD_SP
mdefine_line|#define __THREAD_SP&t;&t;__OFFSET(2)
DECL|macro|__THREAD_FP
mdefine_line|#define __THREAD_FP&t;&t;__OFFSET(3)
DECL|macro|__THREAD_LR
mdefine_line|#define __THREAD_LR&t;&t;__OFFSET(4)
DECL|macro|__THREAD_PC
mdefine_line|#define __THREAD_PC&t;&t;__OFFSET(5)
DECL|macro|__THREAD_GR
mdefine_line|#define __THREAD_GR(R)&t;&t;__OFFSET(6 + (R) - 16)
DECL|macro|__THREAD_FRAME0
mdefine_line|#define __THREAD_FRAME0&t;&t;__OFFSET(19)
DECL|macro|__THREAD_USER
mdefine_line|#define __THREAD_USER&t;&t;__OFFSET(19)
DECL|macro|__USER_INT
mdefine_line|#define __USER_INT&t;&t;__OFFSET(0)
DECL|macro|__INT_GR
mdefine_line|#define __INT_GR(R)&t;&t;__OFFSET(14 + (R))
DECL|macro|__USER_FPMEDIA
mdefine_line|#define __USER_FPMEDIA&t;&t;__OFFSET(NR_USER_INT_REGS)
DECL|macro|__FPMEDIA_FR
mdefine_line|#define __FPMEDIA_FR(R)&t;&t;__OFFSET(NR_USER_INT_REGS + (R))
DECL|macro|__FPMEDIA_FNER
mdefine_line|#define __FPMEDIA_FNER(R)&t;__OFFSET(NR_USER_INT_REGS + 64 + (R))
DECL|macro|__FPMEDIA_MSR
mdefine_line|#define __FPMEDIA_MSR(R)&t;__OFFSET(NR_USER_INT_REGS + 66 + (R))
DECL|macro|__FPMEDIA_ACC
mdefine_line|#define __FPMEDIA_ACC(R)&t;__OFFSET(NR_USER_INT_REGS + 68 + (R))
DECL|macro|__FPMEDIA_ACCG
mdefine_line|#define __FPMEDIA_ACCG(R)&t;__OFFSETC(NR_USER_INT_REGS + 76, (R))
DECL|macro|__FPMEDIA_FSR
mdefine_line|#define __FPMEDIA_FSR(R)&t;__OFFSET(NR_USER_INT_REGS + 78 + (R))
macro_line|#endif /* _ASM_REGISTERS_H */
eof
