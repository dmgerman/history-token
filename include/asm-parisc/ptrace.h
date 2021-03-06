macro_line|#ifndef _PARISC_PTRACE_H
DECL|macro|_PARISC_PTRACE_H
mdefine_line|#define _PARISC_PTRACE_H
multiline_comment|/* written by Philipp Rumpf, Copyright (C) 1999 SuSE GmbH Nuernberg&n;** Copyright (C) 2000 Grant Grundler, Hewlett-Packard&n;*/
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* This struct defines the way the registers are stored on the &n; * stack during a system call.&n; *&n; * N.B. gdb/strace care about the size and offsets within this&n; * structure. If you change things, you may break object compatibility&n; * for those applications.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|gr
r_int
r_int
id|gr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PSW is in gr[0] */
DECL|member|fr
id|__u64
id|fr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|iasq
r_int
r_int
id|iasq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|iaoq
r_int
r_int
id|iaoq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cr27
r_int
r_int
id|cr27
suffix:semicolon
DECL|member|pad0
r_int
r_int
id|pad0
suffix:semicolon
multiline_comment|/* available for other uses */
DECL|member|orig_r28
r_int
r_int
id|orig_r28
suffix:semicolon
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|kpc
r_int
r_int
id|kpc
suffix:semicolon
DECL|member|sar
r_int
r_int
id|sar
suffix:semicolon
multiline_comment|/* CR11 */
DECL|member|iir
r_int
r_int
id|iir
suffix:semicolon
multiline_comment|/* CR19 */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* CR20 */
DECL|member|ior
r_int
r_int
id|ior
suffix:semicolon
multiline_comment|/* CR21 */
DECL|member|ipsw
r_int
r_int
id|ipsw
suffix:semicolon
multiline_comment|/* CR22 */
)brace
suffix:semicolon
DECL|macro|task_regs
mdefine_line|#define task_regs(task) ((struct pt_regs *) ((char *)(task) + TASK_REGS))
multiline_comment|/*&n; * The numbers chosen here are somewhat arbitrary but absolutely MUST&n; * not overlap with any of the number assigned in &lt;linux/ptrace.h&gt;.&n; *&n; * These ones are taken from IA-64 on the assumption that theirs are&n; * the most correct (and we also want to support PTRACE_SINGLEBLOCK&n; * since we have taken branch traps too)&n; */
DECL|macro|PTRACE_SINGLEBLOCK
mdefine_line|#define PTRACE_SINGLEBLOCK&t;12&t;/* resume execution until next branch */
macro_line|#ifdef __KERNEL__
multiline_comment|/* XXX should we use iaoq[1] or iaoq[0] ? */
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;&t;&t;(((regs)-&gt;iaoq[0] &amp; 3) ? 1 : 0)
DECL|macro|user_space
mdefine_line|#define user_space(regs)&t;&t;(((regs)-&gt;iasq[1] != 0) ? 1 : 0)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs)&t;((regs)-&gt;iaoq[0] &amp; ~3)
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
macro_line|#endif
macro_line|#endif
eof
