macro_line|#ifndef _ASM_M32R_PTRACE_H
DECL|macro|_ASM_M32R_PTRACE_H
mdefine_line|#define _ASM_M32R_PTRACE_H
multiline_comment|/*&n; * linux/include/asm-m32r/ptrace.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * M32R version:&n; *   Copyright (C) 2001-2002, 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;&t;&t;/* M32R_PSW_BSM, M32R_PSW_BPM */
multiline_comment|/* 0 - 13 are integer registers (general purpose registers).  */
DECL|macro|PT_R4
mdefine_line|#define PT_R4&t;&t;0
DECL|macro|PT_R5
mdefine_line|#define PT_R5&t;&t;1
DECL|macro|PT_R6
mdefine_line|#define PT_R6&t;&t;2
DECL|macro|PT_REGS
mdefine_line|#define PT_REGS &t;3
DECL|macro|PT_R0
mdefine_line|#define PT_R0&t;&t;4
DECL|macro|PT_R1
mdefine_line|#define PT_R1&t;&t;5
DECL|macro|PT_R2
mdefine_line|#define PT_R2&t;&t;6
DECL|macro|PT_R3
mdefine_line|#define PT_R3&t;&t;7
DECL|macro|PT_R7
mdefine_line|#define PT_R7&t;&t;8
DECL|macro|PT_R8
mdefine_line|#define PT_R8&t;&t;9
DECL|macro|PT_R9
mdefine_line|#define PT_R9&t;&t;10
DECL|macro|PT_R10
mdefine_line|#define PT_R10&t;&t;11
DECL|macro|PT_R11
mdefine_line|#define PT_R11&t;&t;12
DECL|macro|PT_R12
mdefine_line|#define PT_R12&t;&t;13
DECL|macro|PT_SYSCNR
mdefine_line|#define PT_SYSCNR&t;14
DECL|macro|PT_R13
mdefine_line|#define PT_R13&t;&t;PT_FP
DECL|macro|PT_R14
mdefine_line|#define PT_R14&t;&t;PT_LR
DECL|macro|PT_R15
mdefine_line|#define PT_R15&t;&t;PT_SP
multiline_comment|/* processor status and miscellaneous context registers.  */
macro_line|#if defined(CONFIG_ISA_M32R2) &amp;&amp; defined(CONFIG_ISA_DSP_LEVEL2)
DECL|macro|PT_ACC0H
mdefine_line|#define PT_ACC0H&t;15
DECL|macro|PT_ACC0L
mdefine_line|#define PT_ACC0L&t;16
DECL|macro|PT_ACC1H
mdefine_line|#define PT_ACC1H&t;17
DECL|macro|PT_ACC1L
mdefine_line|#define PT_ACC1L&t;18
DECL|macro|PT_ACCH
mdefine_line|#define PT_ACCH&t;&t;PT_ACC0H
DECL|macro|PT_ACCL
mdefine_line|#define PT_ACCL&t;&t;PT_ACC0L
DECL|macro|PT_PSW
mdefine_line|#define PT_PSW&t;&t;19
DECL|macro|PT_BPC
mdefine_line|#define PT_BPC&t;&t;20
DECL|macro|PT_BBPSW
mdefine_line|#define PT_BBPSW&t;21
DECL|macro|PT_BBPC
mdefine_line|#define PT_BBPC&t;&t;22
DECL|macro|PT_SPU
mdefine_line|#define PT_SPU&t;&t;23
DECL|macro|PT_FP
mdefine_line|#define PT_FP&t;&t;24
DECL|macro|PT_LR
mdefine_line|#define PT_LR&t;&t;25
DECL|macro|PT_SPI
mdefine_line|#define PT_SPI&t;&t;26
DECL|macro|PT_ORIGR0
mdefine_line|#define PT_ORIGR0&t;27
macro_line|#elif defined(CONFIG_ISA_M32R2) || defined(CONFIG_ISA_M32R)
DECL|macro|PT_ACCH
mdefine_line|#define PT_ACCH&t;&t;15
DECL|macro|PT_ACCL
mdefine_line|#define PT_ACCL&t;&t;16
DECL|macro|PT_PSW
mdefine_line|#define PT_PSW&t;&t;17
DECL|macro|PT_BPC
mdefine_line|#define PT_BPC&t;&t;18
DECL|macro|PT_BBPSW
mdefine_line|#define PT_BBPSW&t;19
DECL|macro|PT_BBPC
mdefine_line|#define PT_BBPC&t;&t;20
DECL|macro|PT_SPU
mdefine_line|#define PT_SPU&t;&t;21
DECL|macro|PT_FP
mdefine_line|#define PT_FP&t;&t;22
DECL|macro|PT_LR
mdefine_line|#define PT_LR&t;&t;23
DECL|macro|PT_SPI
mdefine_line|#define PT_SPI&t;&t;24
DECL|macro|PT_ORIGR0
mdefine_line|#define PT_ORIGR0&t;25
macro_line|#else
macro_line|#error unknown isa conifiguration
macro_line|#endif
multiline_comment|/* virtual pt_reg entry for gdb */
DECL|macro|PT_PC
mdefine_line|#define PT_PC&t;&t;30
DECL|macro|PT_CBR
mdefine_line|#define PT_CBR&t;&t;31
DECL|macro|PT_EVB
mdefine_line|#define PT_EVB&t;&t;32
multiline_comment|/* Control registers.  */
DECL|macro|SPR_CR0
mdefine_line|#define SPR_CR0 PT_PSW
DECL|macro|SPR_CR1
mdefine_line|#define SPR_CR1 PT_CBR&t;&t;/* read only */
DECL|macro|SPR_CR2
mdefine_line|#define SPR_CR2 PT_SPI
DECL|macro|SPR_CR3
mdefine_line|#define SPR_CR3 PT_SPU
DECL|macro|SPR_CR4
mdefine_line|#define SPR_CR4
DECL|macro|SPR_CR5
mdefine_line|#define SPR_CR5 PT_EVB&t;&t;/* part of M32R/E, M32R/I core only */
DECL|macro|SPR_CR6
mdefine_line|#define SPR_CR6 PT_BPC
DECL|macro|SPR_CR7
mdefine_line|#define SPR_CR7
DECL|macro|SPR_CR8
mdefine_line|#define SPR_CR8 PT_BBPSW
DECL|macro|SPR_CR9
mdefine_line|#define SPR_CR9
DECL|macro|SPR_CR10
mdefine_line|#define SPR_CR10
DECL|macro|SPR_CR11
mdefine_line|#define SPR_CR11
DECL|macro|SPR_CR12
mdefine_line|#define SPR_CR12
DECL|macro|SPR_CR13
mdefine_line|#define SPR_CR13 PT_WR
DECL|macro|SPR_CR14
mdefine_line|#define SPR_CR14 PT_BBPC
DECL|macro|SPR_CR15
mdefine_line|#define SPR_CR15
multiline_comment|/* this struct defines the way the registers are stored on the&n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* Saved main processor registers. */
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|pt_regs
r_struct
id|pt_regs
op_star
id|pt_regs
suffix:semicolon
DECL|member|r0
r_int
r_int
id|r0
suffix:semicolon
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
DECL|member|syscall_nr
r_int
id|syscall_nr
suffix:semicolon
multiline_comment|/* Saved main processor status and miscellaneous context registers. */
macro_line|#if defined(CONFIG_ISA_M32R2) &amp;&amp; defined(CONFIG_ISA_DSP_LEVEL2)
DECL|member|acc0h
r_int
r_int
id|acc0h
suffix:semicolon
DECL|member|acc0l
r_int
r_int
id|acc0l
suffix:semicolon
DECL|member|acc1h
r_int
r_int
id|acc1h
suffix:semicolon
DECL|member|acc1l
r_int
r_int
id|acc1l
suffix:semicolon
macro_line|#elif defined(CONFIG_ISA_M32R2) || defined(CONFIG_ISA_M32R)
DECL|member|acch
r_int
r_int
id|acch
suffix:semicolon
DECL|member|accl
r_int
r_int
id|accl
suffix:semicolon
macro_line|#else
macro_line|#error unknown isa configuration
macro_line|#endif
DECL|member|psw
r_int
r_int
id|psw
suffix:semicolon
DECL|member|bpc
r_int
r_int
id|bpc
suffix:semicolon
multiline_comment|/* saved PC for TRAP syscalls */
DECL|member|bbpsw
r_int
r_int
id|bbpsw
suffix:semicolon
DECL|member|bbpc
r_int
r_int
id|bbpc
suffix:semicolon
DECL|member|spu
r_int
r_int
id|spu
suffix:semicolon
multiline_comment|/* saved user stack */
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* saved PC for JL syscalls */
DECL|member|spi
r_int
r_int
id|spi
suffix:semicolon
multiline_comment|/* saved kernel stack */
DECL|member|orig_r0
r_int
r_int
id|orig_r0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS&t;&t;12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS&t;&t;13
DECL|macro|PTRACE_OLDSETOPTIONS
mdefine_line|#define PTRACE_OLDSETOPTIONS&t;21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
macro_line|#ifdef __KERNEL__
macro_line|#if defined(CONFIG_ISA_M32R2) || defined(CONFIG_CHIP_VDEC2)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((M32R_PSW_BPM &amp; (regs)-&gt;psw) != 0)
macro_line|#elif defined(CONFIG_ISA_M32R)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((M32R_PSW_BSM &amp; (regs)-&gt;psw) != 0)
macro_line|#else
macro_line|#error unknown isa configuration
macro_line|#endif
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;bpc)
DECL|macro|profile_pc
mdefine_line|#define profile_pc(regs) instruction_pointer(regs)
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
r_extern
r_void
id|withdraw_debug_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL */
macro_line|#endif /* _ASM_M32R_PTRACE_H */
eof
