multiline_comment|/* $Id: processor.h,v 1.83 2001/10/08 09:32:13 davem Exp $&n; * include/asm-sparc/processor.h&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC_PROCESSOR_H
DECL|macro|__ASM_SPARC_PROCESSOR_H
mdefine_line|#define __ASM_SPARC_PROCESSOR_H
multiline_comment|/*&n; * Sparc32 implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;sethi %%hi(1f), %0; or %0, %%lo(1f), %0;&bslash;n1:&quot; : &quot;=r&quot; (pc)); pc; })
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * The sparc has no problems with write protection&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* Whee, this is STACK_TOP + PAGE_SIZE and the lowest kernel address too... &n; * That one page is used to protect kernel from intruders, so that&n; * we can make our access_ok test faster&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;PAGE_OFFSET
r_struct
id|task_struct
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|fpq
r_struct
id|fpq
(brace
DECL|member|insn_addr
r_int
r_int
op_star
id|insn_addr
suffix:semicolon
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|seg
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/* The Sparc processor specific thread struct. */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
DECL|member|_pad1
r_int
r_int
id|_pad1
suffix:semicolon
multiline_comment|/* Special child fork kpsr/kwim values. */
DECL|member|fork_kpsr
r_int
r_int
id|fork_kpsr
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|member|fork_kwim
r_int
r_int
id|fork_kwim
suffix:semicolon
multiline_comment|/* Floating point regs */
DECL|member|float_regs
r_int
r_int
id|float_regs
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|member|fsr
r_int
r_int
id|fsr
suffix:semicolon
DECL|member|fpqdepth
r_int
r_int
id|fpqdepth
suffix:semicolon
DECL|member|fpqueue
r_struct
id|fpq
id|fpqueue
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|current_ds
id|mm_segment_t
id|current_ds
suffix:semicolon
DECL|member|core_exec
r_struct
id|exec
id|core_exec
suffix:semicolon
multiline_comment|/* just what it says. */
DECL|member|new_signal
r_int
id|new_signal
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_FLAG_KTHREAD
mdefine_line|#define SPARC_FLAG_KTHREAD      0x1    /* task is a kernel thread */
DECL|macro|SPARC_FLAG_UNALIGNED
mdefine_line|#define SPARC_FLAG_UNALIGNED    0x2    /* is allowed to do unaligned accesses */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;&t;.flags = SPARC_FLAG_KTHREAD, &bslash;&n;&t;.current_ds = KERNEL_DS, &bslash;&n;}
multiline_comment|/* Return saved PC of a blocked thread. */
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
multiline_comment|/* Do necessary setup to start up a newly executed thread. */
DECL|function|start_thread
r_extern
id|__inline__
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
r_register
r_int
r_int
id|zero
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|regs-&gt;psr
op_assign
(paren
id|regs-&gt;psr
op_amp
(paren
id|PSR_CWP
)paren
)paren
op_or
id|PSR_S
suffix:semicolon
id|regs-&gt;pc
op_assign
(paren
(paren
id|pc
op_amp
(paren
op_complement
l_int|3
)paren
)paren
op_minus
l_int|4
)paren
suffix:semicolon
id|regs-&gt;npc
op_assign
id|regs-&gt;pc
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;y
op_assign
l_int|0
suffix:semicolon
id|zero
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x00]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x08]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x10]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x18]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x20]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x28]&bslash;n&bslash;t&quot;
l_string|&quot;std&bslash;t%%g0, [%0 + %3 + 0x30]&bslash;n&bslash;t&quot;
l_string|&quot;st&bslash;t%1, [%0 + %3 + 0x38]&bslash;n&bslash;t&quot;
l_string|&quot;st&bslash;t%%g0, [%0 + %3 + 0x3c]&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|regs
)paren
comma
l_string|&quot;r&quot;
(paren
id|sp
op_minus
r_sizeof
(paren
r_struct
id|reg_window
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|zero
)paren
comma
l_string|&quot;i&quot;
(paren
(paren
r_const
r_int
r_int
)paren
(paren
op_amp
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|u_regs
(braket
l_int|0
)braket
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(tsk)&t;&t;do { } while(0)
r_extern
id|pid_t
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
r_extern
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.kregs-&gt;pc)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.kregs-&gt;u_regs[UREG_FP])
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif
macro_line|#endif /* __ASM_SPARC_PROCESSOR_H */
eof
