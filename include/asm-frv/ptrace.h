multiline_comment|/* ptrace.h: ptrace() relevant definitions&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_PTRACE_H
DECL|macro|_ASM_PTRACE_H
mdefine_line|#define _ASM_PTRACE_H
macro_line|#include &lt;asm/registers.h&gt;
DECL|macro|in_syscall
mdefine_line|#define in_syscall(regs) (((regs)-&gt;tbr &amp; TBR_TT) == TBR_TT_TRAP0)
DECL|macro|PT_PSR
mdefine_line|#define PT_PSR&t;&t;0
DECL|macro|PT_ISR
mdefine_line|#define&t;PT_ISR&t;&t;1
DECL|macro|PT_CCR
mdefine_line|#define PT_CCR&t;&t;2
DECL|macro|PT_CCCR
mdefine_line|#define PT_CCCR&t;&t;3
DECL|macro|PT_LR
mdefine_line|#define PT_LR&t;&t;4
DECL|macro|PT_LCR
mdefine_line|#define PT_LCR&t;&t;5
DECL|macro|PT_PC
mdefine_line|#define PT_PC&t;&t;6
DECL|macro|PT__STATUS
mdefine_line|#define PT__STATUS&t;7&t;/* exception status */
DECL|macro|PT_SYSCALLNO
mdefine_line|#define PT_SYSCALLNO&t;8&t;/* syscall number or -1 */
DECL|macro|PT_ORIG_GR8
mdefine_line|#define PT_ORIG_GR8&t;9&t;/* saved GR8 for signal handling */
DECL|macro|PT_GNER0
mdefine_line|#define PT_GNER0&t;10
DECL|macro|PT_GNER1
mdefine_line|#define PT_GNER1&t;11
DECL|macro|PT_IACC0H
mdefine_line|#define PT_IACC0H&t;12
DECL|macro|PT_IACC0L
mdefine_line|#define PT_IACC0L&t;13
DECL|macro|PT_GR
mdefine_line|#define PT_GR(j)&t;( 14 + (j))&t;/* GRj for 0&lt;=j&lt;=63 */
DECL|macro|PT_FR
mdefine_line|#define PT_FR(j)&t;( 78 + (j))&t;/* FRj for 0&lt;=j&lt;=63 */
DECL|macro|PT_FNER
mdefine_line|#define PT_FNER(j)&t;(142 + (j))&t;/* FNERj for 0&lt;=j&lt;=1 */
DECL|macro|PT_MSR
mdefine_line|#define PT_MSR(j)&t;(144 + (j))&t;/* MSRj for 0&lt;=j&lt;=2 */
DECL|macro|PT_ACC
mdefine_line|#define PT_ACC(j)&t;(146 + (j))&t;/* ACCj for 0&lt;=j&lt;=7 */
DECL|macro|PT_ACCG
mdefine_line|#define PT_ACCG(jklm)&t;(154 + (jklm))&t;/* ACCGjklm for 0&lt;=jklm&lt;=1 (reads four regs per slot) */
DECL|macro|PT_FSR
mdefine_line|#define PT_FSR(j)&t;(156 + (j))&t;/* FSRj for 0&lt;=j&lt;=0 */
DECL|macro|PT__GPEND
mdefine_line|#define PT__GPEND&t;78
DECL|macro|PT__END
mdefine_line|#define PT__END&t;&t;157
DECL|macro|PT_TBR
mdefine_line|#define PT_TBR&t;&t;PT_GR(0)
DECL|macro|PT_SP
mdefine_line|#define PT_SP&t;&t;PT_GR(1)
DECL|macro|PT_FP
mdefine_line|#define PT_FP&t;&t;PT_GR(2)
DECL|macro|PT_PREV_FRAME
mdefine_line|#define PT_PREV_FRAME&t;PT_GR(28)&t;/* previous exception frame pointer (old gr28 value) */
DECL|macro|PT_CURR_TASK
mdefine_line|#define PT_CURR_TASK&t;PT_GR(29)&t;/* current task */
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS&t;&t;12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS&t;&t;13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS&t;14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS&t;15
DECL|macro|PTRACE_GETFDPIC
mdefine_line|#define PTRACE_GETFDPIC&t;&t;31&t;/* get the ELF fdpic loadmap address */
DECL|macro|PTRACE_GETFDPIC_EXEC
mdefine_line|#define PTRACE_GETFDPIC_EXEC&t;0&t;/* [addr] request the executable loadmap */
DECL|macro|PTRACE_GETFDPIC_INTERP
mdefine_line|#define PTRACE_GETFDPIC_INTERP&t;1&t;/* [addr] request the interpreter loadmap */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * dedicate GR28; to keeping the a pointer to the current exception frame&n; */
r_register
r_struct
id|pt_regs
op_star
id|__frame
id|asm
c_func
(paren
l_string|&quot;gr28&quot;
)paren
suffix:semicolon
r_register
r_struct
id|pt_regs
op_star
id|__debug_frame
id|asm
c_func
(paren
l_string|&quot;gr31&quot;
)paren
suffix:semicolon
macro_line|#ifndef container_of
DECL|macro|container_of
mdefine_line|#define container_of(ptr, type, member) ({&t;&t;&t;&bslash;&n;        const typeof( ((type *)0)-&gt;member ) *__mptr = (ptr);&t;&bslash;&n;        (type *)( (char *)__mptr - offsetof(type,member) );})
macro_line|#endif
DECL|macro|__debug_regs
mdefine_line|#define __debug_regs container_of(__debug_frame, struct pt_debug_regs, normal_regs)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs)&t;&t;&t;(!((regs)-&gt;psr &amp; PSR_S))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs)&t;((regs)-&gt;pc)
r_extern
r_int
r_int
id|user_stack
c_func
(paren
r_const
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
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
DECL|macro|profile_pc
mdefine_line|#define profile_pc(regs) ((regs)-&gt;pc)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_PTRACE_H */
eof
