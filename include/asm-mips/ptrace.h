multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PTRACE_H
DECL|macro|_ASM_PTRACE_H
mdefine_line|#define _ASM_PTRACE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
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
multiline_comment|/*&n; * This struct defines the way the registers are stored on the stack during a&n; * system call/exception. As usual the registers k0/k1 aren&squot;t being saved.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
macro_line|#ifdef CONFIG_MIPS32
multiline_comment|/* Pad bytes for argument save space on the stack. */
DECL|member|pad0
r_int
r_int
id|pad0
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Saved main processor registers. */
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Saved special registers. */
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
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
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
DECL|member|cp0_cause
r_int
r_int
id|cp0_cause
suffix:semicolon
DECL|member|cp0_epc
r_int
r_int
id|cp0_epc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
multiline_comment|/* #define PTRACE_GETREGS&t;&t;12 */
multiline_comment|/* #define PTRACE_SETREGS&t;&t;13 */
multiline_comment|/* #define PTRACE_GETFPREGS&t;&t;14 */
multiline_comment|/* #define PTRACE_SETFPREGS&t;&t;15 */
multiline_comment|/* #define PTRACE_GETFPXREGS&t;&t;18 */
multiline_comment|/* #define PTRACE_SETFPXREGS&t;&t;19 */
DECL|macro|PTRACE_OLDSETOPTIONS
mdefine_line|#define PTRACE_OLDSETOPTIONS&t;21
DECL|macro|PTRACE_GET_THREAD_AREA
mdefine_line|#define PTRACE_GET_THREAD_AREA&t;25
DECL|macro|PTRACE_SET_THREAD_AREA
mdefine_line|#define PTRACE_SET_THREAD_AREA&t;26
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * Does the process account for user or for system time?&n; */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;cp0_status &amp; KU_MASK) == KU_USER)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;cp0_epc)
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
id|asmlinkage
r_void
id|do_syscall_trace
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|entryexit
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_PTRACE_H */
eof
