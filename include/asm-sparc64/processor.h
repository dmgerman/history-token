multiline_comment|/* $Id: processor.h,v 1.83 2002/02/10 06:04:33 davem Exp $&n; * include/asm-sparc64/processor.h&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC64_PROCESSOR_H
DECL|macro|__ASM_SPARC64_PROCESSOR_H
mdefine_line|#define __ASM_SPARC64_PROCESSOR_H
multiline_comment|/*&n; * Sparc64 implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ void *pc; __asm__(&quot;rd %%pc, %0&quot; : &quot;=r&quot; (pc)); pc; })
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/pstate.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* The sparc has no problems with write protection */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User lives in his very own context, and cannot reference us. Note&n; * that TASK_SIZE is a misnomer, it really gives maximum user virtual &n; * address that the kernel will allocate out.&n; */
DECL|macro|VA_BITS
mdefine_line|#define VA_BITS&t;&t;44
macro_line|#ifndef __ASSEMBLY__
DECL|macro|VPTE_SIZE
mdefine_line|#define VPTE_SIZE&t;(1UL &lt;&lt; (VA_BITS - PAGE_SHIFT + 3))
macro_line|#else
DECL|macro|VPTE_SIZE
mdefine_line|#define VPTE_SIZE&t;(1 &lt;&lt; (VA_BITS - PAGE_SHIFT + 3))
macro_line|#endif
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;((unsigned long)-VPTE_SIZE)
multiline_comment|/*&n; * The vpte base must be able to hold the entire vpte, half&n; * of which lives above, and half below, the base. And it&n; * is placed as close to the highest address range as possible.&n; */
DECL|macro|VPTE_BASE_SPITFIRE
mdefine_line|#define VPTE_BASE_SPITFIRE&t;(-(VPTE_SIZE/2))
macro_line|#if 1
DECL|macro|VPTE_BASE_CHEETAH
mdefine_line|#define VPTE_BASE_CHEETAH&t;VPTE_BASE_SPITFIRE
macro_line|#else
DECL|macro|VPTE_BASE_CHEETAH
mdefine_line|#define VPTE_BASE_CHEETAH&t;0xffe0000000000000
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_char
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
multiline_comment|/* The Sparc processor specific thread struct. */
multiline_comment|/* XXX This should die, everything can go into thread_info now. */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
multiline_comment|/* How many spinlocks held by this thread.&n;&t; * Used with spin lock debugging to catch tasks&n;&t; * sleeping illegally with locks held.&n;&t; */
DECL|member|smp_lock_count
r_int
id|smp_lock_count
suffix:semicolon
DECL|member|smp_lock_pc
r_int
r_int
id|smp_lock_pc
suffix:semicolon
macro_line|#else
r_int
id|dummy
suffix:semicolon
multiline_comment|/* f&squot;in gcc bug... */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#ifndef CONFIG_DEBUG_SPINLOCK
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&bslash;&n;}
macro_line|#else /* CONFIG_DEBUG_SPINLOCK */
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&bslash;&n;/* smp_lock_count, smp_lock_pc, */&t;&t;&t;&bslash;&n;   0,&t;&t;   0,&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* !(CONFIG_DEBUG_SPINLOCK) */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Return saved PC of a blocked thread. */
r_struct
id|task_struct
suffix:semicolon
r_extern
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* On Uniprocessor, even in RMO processes see TSO semantics */
macro_line|#ifdef CONFIG_SMP
DECL|macro|TSTATE_INITIAL_MM
mdefine_line|#define TSTATE_INITIAL_MM&t;TSTATE_TSO
macro_line|#else
DECL|macro|TSTATE_INITIAL_MM
mdefine_line|#define TSTATE_INITIAL_MM&t;TSTATE_RMO
macro_line|#endif
multiline_comment|/* Do necessary setup to start up a newly executed thread. */
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP)) | (TSTATE_INITIAL_MM|TSTATE_IE) | (ASI_PNF &lt;&lt; 24); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;set_thread_wstate(1 &lt;&lt; 3); &bslash;&n;&t;if (current_thread_info()-&gt;utraps) { &bslash;&n;&t;&t;if (*(current_thread_info()-&gt;utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree(current_thread_info()-&gt;utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current_thread_info()-&gt;utraps))--; &bslash;&n;&t;&t;current_thread_info()-&gt;utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (1 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - sizeof(struct reg_window) - STACK_BIAS), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while (0)
DECL|macro|start_thread32
mdefine_line|#define start_thread32(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;pc &amp;= 0x00000000ffffffffUL; &bslash;&n;&t;sp &amp;= 0x00000000ffffffffUL; &bslash;&n;&bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP))|(TSTATE_INITIAL_MM|TSTATE_IE|TSTATE_AM); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;set_thread_wstate(2 &lt;&lt; 3); &bslash;&n;&t;if (current_thread_info()-&gt;utraps) { &bslash;&n;&t;&t;if (*(current_thread_info()-&gt;utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree(current_thread_info()-&gt;utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current_thread_info()-&gt;utraps))--; &bslash;&n;&t;&t;current_thread_info()-&gt;utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (2 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - sizeof(struct reg_window32)), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while (0)
multiline_comment|/* Free all resources held by a thread. */
DECL|macro|release_thread
mdefine_line|#define release_thread(tsk)&t;&t;do { } while (0)
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
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
r_extern
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread_info-&gt;kregs-&gt;tpc)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread_info-&gt;kregs-&gt;u_regs[UREG_FP])
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;barrier()
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__ASM_SPARC64_PROCESSOR_H) */
eof
