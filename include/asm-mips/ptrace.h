multiline_comment|/* $Id: ptrace.h,v 1.7 1999/09/28 22:27:17 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998 by Ralf Baechle&n; *&n; * Machine dependent structs and defines to help the user use&n; * the ptrace system call.&n; */
macro_line|#ifndef __ASM_MIPS_PTRACE_H
DECL|macro|__ASM_MIPS_PTRACE_H
mdefine_line|#define __ASM_MIPS_PTRACE_H
macro_line|#include &lt;asm/isadep.h&gt;
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
multiline_comment|/*&n; * This struct defines the way the registers are stored on the stack during a&n; * system call/exception. As usual the registers k0/k1 aren&squot;t being saved.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* Pad bytes for argument save space on the stack. */
DECL|member|pad0
r_int
r_int
id|pad0
(braket
l_int|6
)braket
suffix:semicolon
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
macro_line|#endif /* !(_LANGUAGE_ASSEMBLY) */
macro_line|#ifdef _LANGUAGE_ASSEMBLY
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Does the process account for user or for system time?&n; */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;cp0_status &amp; KU_MASK) == KU_USER)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;cp0_epc)
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
macro_line|#endif /* !(_LANGUAGE_ASSEMBLY) */
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_PTRACE_H */
eof
