multiline_comment|/*&n; * include/asm-v850/ptrace.h -- Access to CPU registers&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_PTRACE_H__
DECL|macro|__V850_PTRACE_H__
mdefine_line|#define __V850_PTRACE_H__
multiline_comment|/* v850 general purpose registers with special meanings.  */
DECL|macro|GPR_ZERO
mdefine_line|#define GPR_ZERO&t;0&t;/* constant zero */
DECL|macro|GPR_ASM
mdefine_line|#define GPR_ASM&t;&t;1&t;/* reserved for assembler */
DECL|macro|GPR_SP
mdefine_line|#define GPR_SP&t;&t;3&t;/* stack pointer */
DECL|macro|GPR_GP
mdefine_line|#define GPR_GP&t;&t;4&t;/* global data pointer */
DECL|macro|GPR_TP
mdefine_line|#define GPR_TP&t;&t;5&t;/* `text pointer&squot; */
DECL|macro|GPR_EP
mdefine_line|#define GPR_EP&t;&t;30&t;/* `element pointer&squot; */
DECL|macro|GPR_LP
mdefine_line|#define GPR_LP&t;&t;31&t;/* link pointer (current return address) */
multiline_comment|/* These aren&squot;t official names, but they make some code more descriptive.  */
DECL|macro|GPR_ARG0
mdefine_line|#define GPR_ARG0&t;6
DECL|macro|GPR_ARG1
mdefine_line|#define GPR_ARG1&t;7
DECL|macro|GPR_ARG2
mdefine_line|#define GPR_ARG2&t;8
DECL|macro|GPR_ARG3
mdefine_line|#define GPR_ARG3&t;9
DECL|macro|GPR_RVAL0
mdefine_line|#define GPR_RVAL0&t;10
DECL|macro|GPR_RVAL1
mdefine_line|#define GPR_RVAL1&t;11
DECL|macro|GPR_RVAL
mdefine_line|#define GPR_RVAL&t;GPR_RVAL0
DECL|macro|NUM_GPRS
mdefine_line|#define NUM_GPRS&t;32
multiline_comment|/* v850 `system&squot; registers.  */
DECL|macro|SR_EIPC
mdefine_line|#define SR_EIPC&t;&t;0
DECL|macro|SR_EIPSW
mdefine_line|#define SR_EIPSW&t;1
DECL|macro|SR_FEPC
mdefine_line|#define SR_FEPC&t;&t;2
DECL|macro|SR_FEPSW
mdefine_line|#define SR_FEPSW&t;3
DECL|macro|SR_ECR
mdefine_line|#define SR_ECR&t;&t;4
DECL|macro|SR_PSW
mdefine_line|#define SR_PSW&t;&t;5
DECL|macro|SR_CTPC
mdefine_line|#define SR_CTPC&t;&t;16
DECL|macro|SR_CTPSW
mdefine_line|#define SR_CTPSW&t;17
DECL|macro|SR_DBPC
mdefine_line|#define SR_DBPC&t;&t;18
DECL|macro|SR_DBPSW
mdefine_line|#define SR_DBPSW&t;19
DECL|macro|SR_CTBP
mdefine_line|#define SR_CTBP&t;&t;20
DECL|macro|SR_DIR
mdefine_line|#define SR_DIR&t;&t;21
DECL|macro|SR_ASID
mdefine_line|#define SR_ASID&t;&t;23
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|v850_reg_t
r_typedef
r_int
r_int
id|v850_reg_t
suffix:semicolon
multiline_comment|/* How processor state is stored on the stack during a syscall/signal.&n;   If you change this structure, change the associated assembly-language&n;   macros below too (PT_*)!  */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* General purpose registers.  */
DECL|member|gpr
id|v850_reg_t
id|gpr
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|pc
id|v850_reg_t
id|pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|psw
id|v850_reg_t
id|psw
suffix:semicolon
multiline_comment|/* program status word */
multiline_comment|/* Registers used by `callt&squot; instruction:  */
DECL|member|ctpc
id|v850_reg_t
id|ctpc
suffix:semicolon
multiline_comment|/* saved program counter */
DECL|member|ctpsw
id|v850_reg_t
id|ctpsw
suffix:semicolon
multiline_comment|/* saved psw */
DECL|member|ctbp
id|v850_reg_t
id|ctbp
suffix:semicolon
multiline_comment|/* base pointer for callt table */
DECL|member|kernel_mode
r_char
id|kernel_mode
suffix:semicolon
multiline_comment|/* 1 if in `kernel mode&squot;, 0 if user mode */
)brace
suffix:semicolon
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs)&t;((regs)-&gt;pc)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;&t;&t;(!(regs)-&gt;kernel_mode)
multiline_comment|/* When a struct pt_regs is used to save user state for a system call in&n;   the kernel, the system call is stored in the space for R0 (since it&squot;s&n;   never used otherwise, R0 being a constant 0).  Non-system-calls&n;   simply store 0 there.  */
DECL|macro|PT_REGS_SYSCALL
mdefine_line|#define PT_REGS_SYSCALL(regs)&t;&t;(regs)-&gt;gpr[0]
DECL|macro|PT_REGS_SET_SYSCALL
mdefine_line|#define PT_REGS_SET_SYSCALL(regs, val)&t;((regs)-&gt;gpr[0] = (val))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* The number of bytes used to store each register.  */
DECL|macro|_PT_REG_SIZE
mdefine_line|#define _PT_REG_SIZE&t;4
multiline_comment|/* Offset of a general purpose register in a stuct pt_regs.  */
DECL|macro|PT_GPR
mdefine_line|#define PT_GPR(num)&t;((num) * _PT_REG_SIZE)
multiline_comment|/* Offsets of various special registers &amp; fields in a struct pt_regs.  */
DECL|macro|PT_PC
mdefine_line|#define PT_PC&t;&t;((NUM_GPRS + 0) * _PT_REG_SIZE)
DECL|macro|PT_PSW
mdefine_line|#define PT_PSW&t;&t;((NUM_GPRS + 1) * _PT_REG_SIZE)
DECL|macro|PT_CTPC
mdefine_line|#define PT_CTPC&t;&t;((NUM_GPRS + 2) * _PT_REG_SIZE)
DECL|macro|PT_CTPSW
mdefine_line|#define PT_CTPSW&t;((NUM_GPRS + 3) * _PT_REG_SIZE)
DECL|macro|PT_CTBP
mdefine_line|#define PT_CTBP&t;&t;((NUM_GPRS + 4) * _PT_REG_SIZE)
DECL|macro|PT_KERNEL_MODE
mdefine_line|#define PT_KERNEL_MODE&t;((NUM_GPRS + 5) * _PT_REG_SIZE)
multiline_comment|/* Where the current syscall number is stashed; obviously only valid in&n;   the kernel!  */
DECL|macro|PT_CUR_SYSCALL
mdefine_line|#define PT_CUR_SYSCALL&t;PT_GPR(0)
multiline_comment|/* Size of struct pt_regs, including alignment.  */
DECL|macro|PT_SIZE
mdefine_line|#define PT_SIZE&t;&t;((NUM_GPRS + 6) * _PT_REG_SIZE)
multiline_comment|/* These are `magic&squot; values for PTRACE_PEEKUSR that return info about where&n;   a process is located in memory.  */
DECL|macro|PT_TEXT_ADDR
mdefine_line|#define PT_TEXT_ADDR&t;(PT_SIZE + 1)
DECL|macro|PT_TEXT_LEN
mdefine_line|#define PT_TEXT_LEN&t;(PT_SIZE + 2)
DECL|macro|PT_DATA_ADDR
mdefine_line|#define PT_DATA_ADDR&t;(PT_SIZE + 3)
macro_line|#endif /* __V850_PTRACE_H__ */
eof
