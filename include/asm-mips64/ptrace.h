multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PTRACE_H
DECL|macro|_ASM_PTRACE_H
mdefine_line|#define _ASM_PTRACE_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* 0 - 31 are integer registers, 32 - 63 are fp registers.  */
DECL|macro|FPR_BASE
mdefine_line|#define FPR_BASE&t;32
DECL|macro|PC
mdefine_line|#define PC&t;&t;64
DECL|macro|CAUSE
mdefine_line|#define CAUSE&t;&t;65
DECL|macro|BADVADDR
mdefine_line|#define BADVADDR&t;66
DECL|macro|MMHI
mdefine_line|#define MMHI&t;&t;67
DECL|macro|MMLO
mdefine_line|#define MMLO&t;&t;68
DECL|macro|FPC_CSR
mdefine_line|#define FPC_CSR&t;&t;69
DECL|macro|FPC_EIR
mdefine_line|#define FPC_EIR&t;&t;70
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|macro|abi64_no_regargs
mdefine_line|#define abi64_no_regargs&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy2,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy3,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy4,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy5,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy6,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy7
multiline_comment|/*&n; * This struct defines the way the registers are stored on the stack during a&n; * system call/exception. As usual the registers k0/k1 aren&squot;t being saved.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* Saved main processor registers. */
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Other saved registers. */
DECL|member|lo
r_int
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
r_int
id|hi
suffix:semicolon
multiline_comment|/*&n;&t; * saved cp0 registers&n;&t; */
DECL|member|cp0_epc
r_int
r_int
id|cp0_epc
suffix:semicolon
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
DECL|member|cp0_cause
r_int
r_int
id|cp0_cause
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(_LANGUAGE_ASSEMBLY__) */
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
multiline_comment|/* #define PTRACE_GETREGS&t;&t;12 */
multiline_comment|/* #define PTRACE_SETREGS&t;&t;13 */
multiline_comment|/* #define PTRACE_GETFPREGS&t;&t;14 */
multiline_comment|/* #define PTRACE_SETFPREGS&t;&t;15 */
multiline_comment|/* #define PTRACE_GETFPXREGS&t;&t;18 */
multiline_comment|/* #define PTRACE_SETFPXREGS&t;&t;19 */
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS&t;21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
macro_line|#ifdef _LANGUAGE_ASSEMBLY
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#endif /* (_LANGUAGE_ASSEMBLY__) */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;cp0_epc)
r_extern
r_void
(paren
op_star
id|_show_regs
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|show_regs
mdefine_line|#define show_regs(regs)&t;_show_regs(regs)
macro_line|#endif /* !(_LANGUAGE_ASSEMBLY__) */
macro_line|#endif
macro_line|#endif /* _ASM_PTRACE_H */
eof
