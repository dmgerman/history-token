multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000 by Ralf Baechle&n; *&n; * Machine dependent structs and defines to help the user use&n; * the ptrace system call.&n; */
macro_line|#ifndef _ASM_PTRACE_H
DECL|macro|_ASM_PTRACE_H
mdefine_line|#define _ASM_PTRACE_H
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
macro_line|#ifndef __ASSEMBLY__
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
DECL|macro|__str2
mdefine_line|#define __str2(x) #x
DECL|macro|__str
mdefine_line|#define __str(x) __str2(x)
DECL|macro|save_static_function
mdefine_line|#define save_static_function(symbol)                                    &bslash;&n;__asm__ (                                                               &bslash;&n;&t;&quot;.text&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        &quot;.globl&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;                                       &bslash;&n;        &quot;.align&bslash;t2&bslash;n&bslash;t&quot;                                                 &bslash;&n;        &quot;.type&bslash;t&quot; #symbol &quot;, @function&bslash;n&bslash;t&quot;                             &bslash;&n;        &quot;.ent&bslash;t&quot; #symbol &quot;, 0&bslash;n&quot;                                        &bslash;&n;        #symbol&quot;:&bslash;n&bslash;t&quot;                                                  &bslash;&n;        &quot;.frame&bslash;t$29, 0, $31&bslash;n&bslash;t&quot;                                       &bslash;&n;        &quot;sw&bslash;t$16,&quot;__str(PT_R16)&quot;($29)&bslash;t&bslash;t&bslash;t# save_static_function&bslash;n&bslash;t&quot;  &bslash;&n;        &quot;sw&bslash;t$17,&quot;__str(PT_R17)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$18,&quot;__str(PT_R18)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$19,&quot;__str(PT_R19)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$20,&quot;__str(PT_R20)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$21,&quot;__str(PT_R21)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$22,&quot;__str(PT_R22)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$23,&quot;__str(PT_R23)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;sw&bslash;t$30,&quot;__str(PT_R30)&quot;($29)&bslash;n&bslash;t&quot;                              &bslash;&n;        &quot;.end&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;                                         &bslash;&n;        &quot;.size&bslash;t&quot; #symbol&quot;,. - &quot; #symbol)
multiline_comment|/* Used in declaration of save_static functions.  */
DECL|macro|static_unused
mdefine_line|#define static_unused static __attribute__((unused))
macro_line|#endif /* !__ASSEMBLY__ */
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
macro_line|#ifdef __ASSEMBLY__
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
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
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif
macro_line|#endif /* _ASM_PTRACE_H */
eof
