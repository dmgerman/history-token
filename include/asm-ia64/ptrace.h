macro_line|#ifndef _ASM_IA64_PTRACE_H
DECL|macro|_ASM_IA64_PTRACE_H
mdefine_line|#define _ASM_IA64_PTRACE_H
multiline_comment|/*&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * 12/07/98&t;S. Eranian&t;added pt_regs &amp; switch_stack&n; * 12/21/98&t;D. Mosberger&t;updated to match latest code&n; *  6/17/99&t;D. Mosberger&t;added second unat member to &quot;struct switch_stack&quot;&n; *&n; */
multiline_comment|/*&n; * When a user process is blocked, its state looks as follows:&n; *&n; *            +----------------------+&t;-------&t;IA64_STK_OFFSET&n; *     &t;      |&t;&t;&t;     |&t; ^&n; *            | struct pt_regs       |&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *            +----------------------+&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *     &t;      |&t;   memory stack&t;     |&t; |&n; *&t;      |&t;(growing downwards)  |&t; |&n; *&t;      //.....................//&t; |&n; *&t;&t;&t;&t;&t; |&n; *&t;      //.....................//&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *            +----------------------+&t; |&n; *            | struct switch_stack  |&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *&t;      +----------------------+&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *&t;      //.....................//&t; |&n; *&t;&t;&t;&t;&t; |&n; *&t;      //.....................//&t; |&n; *&t;      |&t;&t;&t;     |&t; |&n; *&t;      |&t; register stack&t;     |&t; |&n; *&t;      |&t;(growing upwards)    |&t; |&n; *            |&t;&t;&t;     |&t; |&n; *&t;      +----------------------+&t; |  ---&t;IA64_RBS_OFFSET&n; *            |  struct thread_info  |&t; |  ^&n; *&t;      +----------------------+&t; |  |&n; *&t;      |&t;&t;&t;     |&t; |  |&n; *            |  struct task_struct  |&t; |  |&n; * current -&gt; |&t;&t;&t;     |   |  |&n; *&t;      +----------------------+ -------&n; *&n; * Note that ar.ec is not saved explicitly in pt_reg or switch_stack.&n; * This is because ar.ec is saved as part of ar.pfs.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/offsets.h&gt;
multiline_comment|/*&n; * Base-2 logarithm of number of pages to allocate per task structure&n; * (including register backing store and memory stack):&n; */
macro_line|#if defined(CONFIG_IA64_PAGE_SIZE_4KB)
DECL|macro|KERNEL_STACK_SIZE_ORDER
macro_line|# define KERNEL_STACK_SIZE_ORDER&t;&t;3
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_8KB)
DECL|macro|KERNEL_STACK_SIZE_ORDER
macro_line|# define KERNEL_STACK_SIZE_ORDER&t;&t;2
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_16KB)
DECL|macro|KERNEL_STACK_SIZE_ORDER
macro_line|# define KERNEL_STACK_SIZE_ORDER&t;&t;1
macro_line|#else
DECL|macro|KERNEL_STACK_SIZE_ORDER
macro_line|# define KERNEL_STACK_SIZE_ORDER&t;&t;0
macro_line|#endif
DECL|macro|IA64_RBS_OFFSET
mdefine_line|#define IA64_RBS_OFFSET&t;&t;&t;((IA64_TASK_SIZE + IA64_THREAD_INFO_SIZE + 15) &amp; ~15)
DECL|macro|IA64_STK_OFFSET
mdefine_line|#define IA64_STK_OFFSET&t;&t;&t;((1 &lt;&lt; KERNEL_STACK_SIZE_ORDER)*PAGE_SIZE)
DECL|macro|KERNEL_STACK_SIZE
mdefine_line|#define KERNEL_STACK_SIZE&t;&t;IA64_STK_OFFSET
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * This struct defines the way the registers are saved on system&n; * calls.&n; *&n; * We don&squot;t save all floating point register because the kernel&n; * is compiled to use only a very small subset, so the other are&n; * untouched.&n; *&n; * THIS STRUCTURE MUST BE A MULTIPLE 16-BYTE IN SIZE&n; * (because the memory stack pointer MUST ALWAYS be aligned this way)&n; *&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
multiline_comment|/* The following registers are saved by SAVE_MIN: */
DECL|member|cr_ipsr
r_int
r_int
id|cr_ipsr
suffix:semicolon
multiline_comment|/* interrupted task&squot;s psr */
DECL|member|cr_iip
r_int
r_int
id|cr_iip
suffix:semicolon
multiline_comment|/* interrupted task&squot;s instruction pointer */
DECL|member|cr_ifs
r_int
r_int
id|cr_ifs
suffix:semicolon
multiline_comment|/* interrupted task&squot;s function state */
DECL|member|ar_unat
r_int
r_int
id|ar_unat
suffix:semicolon
multiline_comment|/* interrupted task&squot;s NaT register (preserved) */
DECL|member|ar_pfs
r_int
r_int
id|ar_pfs
suffix:semicolon
multiline_comment|/* prev function state  */
DECL|member|ar_rsc
r_int
r_int
id|ar_rsc
suffix:semicolon
multiline_comment|/* RSE configuration */
multiline_comment|/* The following two are valid only if cr_ipsr.cpl &gt; 0: */
DECL|member|ar_rnat
r_int
r_int
id|ar_rnat
suffix:semicolon
multiline_comment|/* RSE NaT */
DECL|member|ar_bspstore
r_int
r_int
id|ar_bspstore
suffix:semicolon
multiline_comment|/* RSE bspstore */
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
multiline_comment|/* 64 predicate registers (1 bit each) */
DECL|member|b6
r_int
r_int
id|b6
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|loadrs
r_int
r_int
id|loadrs
suffix:semicolon
multiline_comment|/* size of dirty partition &lt;&lt; 16 */
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
multiline_comment|/* the gp pointer */
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
multiline_comment|/* interrupted task&squot;s memory stack pointer */
DECL|member|r13
r_int
r_int
id|r13
suffix:semicolon
multiline_comment|/* thread pointer */
DECL|member|r14
r_int
r_int
id|r14
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r15
r_int
r_int
id|r15
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
multiline_comment|/* scratch (return value register 0) */
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
multiline_comment|/* scratch (return value register 1) */
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
multiline_comment|/* scratch (return value register 2) */
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
multiline_comment|/* scratch (return value register 3) */
multiline_comment|/* The following registers are saved by SAVE_REST: */
DECL|member|r16
r_int
r_int
id|r16
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r17
r_int
r_int
id|r17
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r18
r_int
r_int
id|r18
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r19
r_int
r_int
id|r19
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r20
r_int
r_int
id|r20
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r21
r_int
r_int
id|r21
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r22
r_int
r_int
id|r22
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r23
r_int
r_int
id|r23
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r24
r_int
r_int
id|r24
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r25
r_int
r_int
id|r25
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r26
r_int
r_int
id|r26
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r27
r_int
r_int
id|r27
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r28
r_int
r_int
id|r28
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r29
r_int
r_int
id|r29
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r30
r_int
r_int
id|r30
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|r31
r_int
r_int
id|r31
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|ar_ccv
r_int
r_int
id|ar_ccv
suffix:semicolon
multiline_comment|/* compare/exchange value (scratch) */
DECL|member|ar_fpsr
r_int
r_int
id|ar_fpsr
suffix:semicolon
multiline_comment|/* floating point status (preserved) */
DECL|member|b0
r_int
r_int
id|b0
suffix:semicolon
multiline_comment|/* return pointer (bp) */
DECL|member|b7
r_int
r_int
id|b7
suffix:semicolon
multiline_comment|/* scratch */
multiline_comment|/*&n;&t; * Floating point registers that the kernel considers&n;&t; * scratch:&n;&t; */
DECL|member|f6
r_struct
id|ia64_fpreg
id|f6
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|f7
r_struct
id|ia64_fpreg
id|f7
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|f8
r_struct
id|ia64_fpreg
id|f8
suffix:semicolon
multiline_comment|/* scratch */
DECL|member|f9
r_struct
id|ia64_fpreg
id|f9
suffix:semicolon
multiline_comment|/* scratch */
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure contains the addition registers that need to&n; * preserved across a context switch.  This generally consists of&n; * &quot;preserved&quot; registers.&n; */
DECL|struct|switch_stack
r_struct
id|switch_stack
(brace
DECL|member|caller_unat
r_int
r_int
id|caller_unat
suffix:semicolon
multiline_comment|/* user NaT collection register (preserved) */
DECL|member|ar_fpsr
r_int
r_int
id|ar_fpsr
suffix:semicolon
multiline_comment|/* floating-point status register */
DECL|member|f2
r_struct
id|ia64_fpreg
id|f2
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f3
r_struct
id|ia64_fpreg
id|f3
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f4
r_struct
id|ia64_fpreg
id|f4
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f5
r_struct
id|ia64_fpreg
id|f5
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f10
r_struct
id|ia64_fpreg
id|f10
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f11
r_struct
id|ia64_fpreg
id|f11
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f12
r_struct
id|ia64_fpreg
id|f12
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f13
r_struct
id|ia64_fpreg
id|f13
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f14
r_struct
id|ia64_fpreg
id|f14
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f15
r_struct
id|ia64_fpreg
id|f15
suffix:semicolon
multiline_comment|/* scratch, but untouched by kernel */
DECL|member|f16
r_struct
id|ia64_fpreg
id|f16
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f17
r_struct
id|ia64_fpreg
id|f17
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f18
r_struct
id|ia64_fpreg
id|f18
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f19
r_struct
id|ia64_fpreg
id|f19
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f20
r_struct
id|ia64_fpreg
id|f20
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f21
r_struct
id|ia64_fpreg
id|f21
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f22
r_struct
id|ia64_fpreg
id|f22
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f23
r_struct
id|ia64_fpreg
id|f23
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f24
r_struct
id|ia64_fpreg
id|f24
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f25
r_struct
id|ia64_fpreg
id|f25
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f26
r_struct
id|ia64_fpreg
id|f26
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f27
r_struct
id|ia64_fpreg
id|f27
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f28
r_struct
id|ia64_fpreg
id|f28
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f29
r_struct
id|ia64_fpreg
id|f29
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f30
r_struct
id|ia64_fpreg
id|f30
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|f31
r_struct
id|ia64_fpreg
id|f31
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
multiline_comment|/* preserved */
DECL|member|b0
r_int
r_int
id|b0
suffix:semicolon
multiline_comment|/* so we can force a direct return in copy_thread */
DECL|member|b1
r_int
r_int
id|b1
suffix:semicolon
DECL|member|b2
r_int
r_int
id|b2
suffix:semicolon
DECL|member|b3
r_int
r_int
id|b3
suffix:semicolon
DECL|member|b4
r_int
r_int
id|b4
suffix:semicolon
DECL|member|b5
r_int
r_int
id|b5
suffix:semicolon
DECL|member|ar_pfs
r_int
r_int
id|ar_pfs
suffix:semicolon
multiline_comment|/* previous function state */
DECL|member|ar_lc
r_int
r_int
id|ar_lc
suffix:semicolon
multiline_comment|/* loop counter (preserved) */
DECL|member|ar_unat
r_int
r_int
id|ar_unat
suffix:semicolon
multiline_comment|/* NaT bits for r4-r7 */
DECL|member|ar_rnat
r_int
r_int
id|ar_rnat
suffix:semicolon
multiline_comment|/* RSE NaT collection register */
DECL|member|ar_bspstore
r_int
r_int
id|ar_bspstore
suffix:semicolon
multiline_comment|/* RSE dirty base (preserved) */
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
multiline_comment|/* 64 predicate registers (1 bit each) */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* given a pointer to a task_struct, return the user&squot;s pt_regs */
DECL|macro|ia64_task_regs
macro_line|# define ia64_task_regs(t)&t;&t;(((struct pt_regs *) ((char *) (t) + IA64_STK_OFFSET)) - 1)
DECL|macro|ia64_psr
macro_line|# define ia64_psr(regs)&t;&t;&t;((struct ia64_psr *) &amp;(regs)-&gt;cr_ipsr)
DECL|macro|user_mode
macro_line|# define user_mode(regs)&t;&t;(((struct ia64_psr *) &amp;(regs)-&gt;cr_ipsr)-&gt;cpl != 0)
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* forward decl */
r_extern
r_void
id|show_regs
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ia64_get_user_rbs_end
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ia64_peek
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|switch_stack
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ia64_poke
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|switch_stack
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ia64_flush_fph
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ia64_sync_fph
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ia64_sync_user_rbs
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|switch_stack
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* get nat bits for scratch registers such that bit N==1 iff scratch register rN is a NaT */
r_extern
r_int
r_int
id|ia64_get_scratch_nat_bits
(paren
r_struct
id|pt_regs
op_star
id|pt
comma
r_int
r_int
id|scratch_unat
)paren
suffix:semicolon
multiline_comment|/* put nat bits for scratch registers such that scratch register rN is a NaT iff bit N==1 */
r_extern
r_int
r_int
id|ia64_put_scratch_nat_bits
(paren
r_struct
id|pt_regs
op_star
id|pt
comma
r_int
r_int
id|nat
)paren
suffix:semicolon
r_extern
r_void
id|ia64_increment_ip
(paren
r_struct
id|pt_regs
op_star
id|pt
)paren
suffix:semicolon
r_extern
r_void
id|ia64_decrement_ip
(paren
r_struct
id|pt_regs
op_star
id|pt
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|force_successful_syscall_return
id|force_successful_syscall_return
(paren
r_void
)paren
(brace
id|ia64_task_regs
c_func
(paren
id|current
)paren
op_member_access_from_pointer
id|r8
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !__KERNEL__ */
multiline_comment|/* pt_all_user_regs is used for PTRACE_GETREGS PTRACE_SETREGS */
DECL|struct|pt_all_user_regs
r_struct
id|pt_all_user_regs
(brace
DECL|member|nat
r_int
r_int
id|nat
suffix:semicolon
DECL|member|cr_iip
r_int
r_int
id|cr_iip
suffix:semicolon
DECL|member|cfm
r_int
r_int
id|cfm
suffix:semicolon
DECL|member|cr_ipsr
r_int
r_int
id|cr_ipsr
suffix:semicolon
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
DECL|member|gr
r_int
r_int
id|gr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|br
r_int
r_int
id|br
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ar
r_int
r_int
id|ar
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|fr
r_struct
id|ia64_fpreg
id|fr
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* indices to application-registers array in pt_all_user_regs */
DECL|macro|PT_AUR_RSC
mdefine_line|#define PT_AUR_RSC&t;16
DECL|macro|PT_AUR_BSP
mdefine_line|#define PT_AUR_BSP&t;17
DECL|macro|PT_AUR_BSPSTORE
mdefine_line|#define PT_AUR_BSPSTORE&t;18
DECL|macro|PT_AUR_RNAT
mdefine_line|#define PT_AUR_RNAT&t;19
DECL|macro|PT_AUR_CCV
mdefine_line|#define PT_AUR_CCV&t;32
DECL|macro|PT_AUR_UNAT
mdefine_line|#define PT_AUR_UNAT&t;36
DECL|macro|PT_AUR_FPSR
mdefine_line|#define PT_AUR_FPSR&t;40
DECL|macro|PT_AUR_PFS
mdefine_line|#define PT_AUR_PFS&t;64
DECL|macro|PT_AUR_LC
mdefine_line|#define PT_AUR_LC&t;65
DECL|macro|PT_AUR_EC
mdefine_line|#define PT_AUR_EC&t;66
multiline_comment|/*&n; * The numbers chosen here are somewhat arbitrary but absolutely MUST&n; * not overlap with any of the number assigned in &lt;linux/ptrace.h&gt;.&n; */
DECL|macro|PTRACE_SINGLEBLOCK
mdefine_line|#define PTRACE_SINGLEBLOCK&t;12&t;/* resume execution until next branch */
DECL|macro|PTRACE_GETSIGINFO
mdefine_line|#define PTRACE_GETSIGINFO&t;13&t;/* get child&squot;s siginfo structure */
DECL|macro|PTRACE_SETSIGINFO
mdefine_line|#define PTRACE_SETSIGINFO&t;14&t;/* set child&squot;s siginfo structure */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS&t;&t;18&t;/* get all registers (pt_all_user_regs) in one shot */
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS&t;&t;19&t;/* set all registers (pt_all_user_regs) in one shot */
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS&t;21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD&t;0x00000001
macro_line|#endif /* _ASM_IA64_PTRACE_H */
eof
