multiline_comment|/* $Id: processor.h,v 1.75 2001/09/20 00:35:34 davem Exp $&n; * include/asm-sparc64/processor.h&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
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
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Bus types */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* The sparc has no problems with write protection */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User lives in his very own context, and cannot reference us. Note&n; * that TASK_SIZE is a misnomer, it really gives maximum user virtual &n; * address that the kernel will allocate out.&n; */
DECL|macro|VA_BITS
mdefine_line|#define VA_BITS&t;&t;44
DECL|macro|VPTE_SIZE
mdefine_line|#define VPTE_SIZE&t;(1UL &lt;&lt; (VA_BITS - PAGE_SHIFT + 3))
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;((unsigned long)-VPTE_SIZE)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|NSWINS
mdefine_line|#define NSWINS&t;&t;7
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
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* D$ line 1 */
DECL|member|ksp
r_int
r_int
id|ksp
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|wstate
DECL|member|cwp
DECL|member|flags
r_int
r_char
id|wstate
comma
id|cwp
comma
id|flags
suffix:semicolon
DECL|member|current_ds
id|mm_segment_t
id|current_ds
suffix:semicolon
DECL|member|w_saved
DECL|member|fpdepth
DECL|member|fault_code
DECL|member|use_blkcommit
r_int
r_char
id|w_saved
comma
id|fpdepth
comma
id|fault_code
comma
id|use_blkcommit
suffix:semicolon
DECL|member|fault_address
r_int
r_int
id|fault_address
suffix:semicolon
DECL|member|fpsaved
r_int
r_char
id|fpsaved
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|__pad2
r_int
r_char
id|__pad2
suffix:semicolon
multiline_comment|/* D$ line 2, 3, 4 */
DECL|member|kregs
r_struct
id|pt_regs
op_star
id|kregs
suffix:semicolon
DECL|member|utraps
r_int
r_int
op_star
id|utraps
suffix:semicolon
DECL|member|gsr
r_int
r_int
id|gsr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|xfsr
r_int
r_int
id|xfsr
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|reg_window
r_struct
id|reg_window
id|reg_window
(braket
id|NSWINS
)braket
suffix:semicolon
DECL|member|rwbuf_stkptrs
r_int
r_int
id|rwbuf_stkptrs
(braket
id|NSWINS
)braket
suffix:semicolon
multiline_comment|/* Performance counter state */
DECL|member|user_cntd0
DECL|member|user_cntd1
id|u64
op_star
id|user_cntd0
comma
op_star
id|user_cntd1
suffix:semicolon
DECL|member|kernel_cntd0
DECL|member|kernel_cntd1
id|u64
id|kernel_cntd0
comma
id|kernel_cntd1
suffix:semicolon
DECL|member|pcr_reg
id|u64
id|pcr_reg
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
DECL|macro|SPARC_FLAG_UNALIGNED
mdefine_line|#define SPARC_FLAG_UNALIGNED    0x01    /* is allowed to do unaligned accesses&t;*/
DECL|macro|SPARC_FLAG_NEWSIGNALS
mdefine_line|#define SPARC_FLAG_NEWSIGNALS   0x02    /* task wants new-style signals&t;&t;*/
DECL|macro|SPARC_FLAG_32BIT
mdefine_line|#define SPARC_FLAG_32BIT        0x04    /* task is older 32-bit binary&t;&t;*/
DECL|macro|SPARC_FLAG_NEWCHILD
mdefine_line|#define SPARC_FLAG_NEWCHILD     0x08    /* task is just-spawned child process&t;*/
DECL|macro|SPARC_FLAG_PERFCTR
mdefine_line|#define SPARC_FLAG_PERFCTR&t;0x10    /* task has performance counters active&t;*/
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE&t;0x01&t;/* Write access, implies D-TLB&t;&t;*/
DECL|macro|FAULT_CODE_DTLB
mdefine_line|#define FAULT_CODE_DTLB&t;&t;0x02&t;/* Miss happened in D-TLB&t;&t;*/
DECL|macro|FAULT_CODE_ITLB
mdefine_line|#define FAULT_CODE_ITLB&t;&t;0x04&t;/* Miss happened in I-TLB&t;&t;*/
DECL|macro|FAULT_CODE_WINFIXUP
mdefine_line|#define FAULT_CODE_WINFIXUP&t;0x08&t;/* Miss happened during spill/fill&t;*/
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  {&t;&t;&t;&t;&t;&bslash;&n;/* ksp, wstate, cwp, flags, current_ds, */ &t;&t;&bslash;&n;   0,   0,      0,   0,     KERNEL_DS,&t;&t;&t;&bslash;&n;/* w_saved, fpdepth, fault_code, use_blkcommit, */&t;&bslash;&n;   0,       0,       0,          0,&t;&t;&t;&bslash;&n;/* fault_address, fpsaved, __pad2, kregs, */&t;&t;&bslash;&n;   0,             { 0 },   0,      0,&t;&t;&t;&bslash;&n;/* utraps, gsr,   xfsr, */&t;&t;&t;&t;&bslash;&n;   0,&t;   { 0 }, { 0 },&t;&t;&t;&t;&bslash;&n;/* reg_window */&t;&t;&t;&t;&t;&bslash;&n;   { { { 0, }, { 0, } }, }, &t;&t;&t;&t;&bslash;&n;/* rwbuf_stkptrs */&t;&t;&t;&t;&t;&bslash;&n;   { 0, 0, 0, 0, 0, 0, 0, },&t;&t;&t;&t;&bslash;&n;/* user_cntd0, user_cndd1, kernel_cntd0, kernel_cntd0, pcr_reg */ &bslash;&n;   0,          0,          0,&t;&t; 0,            0, &bslash;&n;}
macro_line|#ifdef __KERNEL__
macro_line|#if PAGE_SHIFT == 13
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT (PAGE_SHIFT + 1)
macro_line|#else /* PAGE_SHIFT == 13 */
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE PAGE_SIZE
DECL|macro|THREAD_SHIFT
mdefine_line|#define THREAD_SHIFT PAGE_SHIFT
macro_line|#endif /* PAGE_SHIFT == 13 */
macro_line|#endif /* __KERNEL__ */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Return saved PC of a blocked thread. */
DECL|function|thread_saved_pc
r_extern
id|__inline__
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_int
r_int
id|ret
op_assign
l_int|0xdeadbeefUL
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;ksp
)paren
(brace
r_int
r_int
op_star
id|sp
suffix:semicolon
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|t-&gt;ksp
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|sp
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0UL
op_logical_and
id|sp
(braket
l_int|14
)braket
)paren
(brace
r_int
r_int
op_star
id|fp
suffix:semicolon
id|fp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|sp
(braket
l_int|14
)braket
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|fp
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0UL
)paren
id|ret
op_assign
id|fp
(braket
l_int|15
)braket
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
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
mdefine_line|#define start_thread(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP)) | (TSTATE_INITIAL_MM|TSTATE_IE) | (ASI_PNF &lt;&lt; 24); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;thread.wstate = (1 &lt;&lt; 3); &bslash;&n;&t;if (current-&gt;thread.utraps) { &bslash;&n;&t;&t;if (*(current-&gt;thread.utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree (current-&gt;thread.utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current-&gt;thread.utraps))--; &bslash;&n;&t;&t;current-&gt;thread.utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (1 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN_SZ - STACK_BIAS), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while(0)
DECL|macro|start_thread32
mdefine_line|#define start_thread32(regs, pc, sp) &bslash;&n;do { &bslash;&n;&t;pc &amp;= 0x00000000ffffffffUL; &bslash;&n;&t;sp &amp;= 0x00000000ffffffffUL; &bslash;&n;&bslash;&n;&t;regs-&gt;tstate = (regs-&gt;tstate &amp; (TSTATE_CWP))|(TSTATE_INITIAL_MM|TSTATE_IE|TSTATE_AM); &bslash;&n;&t;regs-&gt;tpc = ((pc &amp; (~3)) - 4); &bslash;&n;&t;regs-&gt;tnpc = regs-&gt;tpc + 4; &bslash;&n;&t;regs-&gt;y = 0; &bslash;&n;&t;current-&gt;thread.wstate = (2 &lt;&lt; 3); &bslash;&n;&t;if (current-&gt;thread.utraps) { &bslash;&n;&t;&t;if (*(current-&gt;thread.utraps) &lt; 2) &bslash;&n;&t;&t;&t;kfree (current-&gt;thread.utraps); &bslash;&n;&t;&t;else &bslash;&n;&t;&t;&t;(*(current-&gt;thread.utraps))--; &bslash;&n;&t;&t;current-&gt;thread.utraps = NULL; &bslash;&n;&t;} &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x00]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x08]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x10]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x18]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x20]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x28]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x30]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x38]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x40]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x48]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x50]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x58]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x60]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x68]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%1,   [%0 + %2 + 0x70]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stx&t;&t;%%g0, [%0 + %2 + 0x78]&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;wrpr&t;&t;%%g0, (2 &lt;&lt; 3), %%wstate&bslash;n&bslash;t&quot; &bslash;&n;&t;: &bslash;&n;&t;: &quot;r&quot; (regs), &quot;r&quot; (sp - REGWIN32_SZ), &bslash;&n;&t;  &quot;i&quot; ((const unsigned long)(&amp;((struct pt_regs *)0)-&gt;u_regs[0]))); &bslash;&n;} while(0)
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
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
DECL|macro|get_wchan
mdefine_line|#define get_wchan(__TSK) &bslash;&n;({&t;extern void scheduling_functions_start_here(void); &bslash;&n;&t;extern void scheduling_functions_end_here(void); &bslash;&n;&t;unsigned long pc, fp, bias = 0; &bslash;&n;&t;unsigned long task_base = (unsigned long) (__TSK); &bslash;&n;&t;struct reg_window *rw; &bslash;&n;        unsigned long __ret = 0; &bslash;&n;&t;int count = 0; &bslash;&n;&t;if (!(__TSK) || (__TSK) == current || &bslash;&n;            (__TSK)-&gt;state == TASK_RUNNING) &bslash;&n;&t;&t;goto __out; &bslash;&n;&t;bias = STACK_BIAS; &bslash;&n;&t;fp = (__TSK)-&gt;thread.ksp + bias; &bslash;&n;&t;do { &bslash;&n;&t;&t;/* Bogus frame pointer? */ &bslash;&n;&t;&t;if (fp &lt; (task_base + sizeof(struct task_struct)) || &bslash;&n;&t;&t;    fp &gt;= (task_base + THREAD_SIZE)) &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;rw = (struct reg_window *) fp; &bslash;&n;&t;&t;pc = rw-&gt;ins[7]; &bslash;&n;&t;&t;if (pc &lt; ((unsigned long) scheduling_functions_start_here) || &bslash;&n;&t;&t;    pc &gt;= ((unsigned long) scheduling_functions_end_here)) { &bslash;&n;&t;&t;&t;__ret = pc; &bslash;&n;&t;&t;&t;goto __out; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;fp = rw-&gt;ins[6] + bias; &bslash;&n;&t;} while (++count &lt; 16); &bslash;&n;__out:&t;__ret; &bslash;&n;})
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.kregs-&gt;tpc)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.kregs-&gt;u_regs[UREG_FP])
macro_line|#ifdef __KERNEL__
multiline_comment|/* Allocation and freeing of task_struct and kernel stack. */
macro_line|#if PAGE_SHIFT == 13
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()   ((struct task_struct *)__get_free_pages(GFP_KERNEL, 1))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(tsk) free_pages((unsigned long)(tsk),1)
macro_line|#else /* PAGE_SHIFT == 13 */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct()   ((struct task_struct *)__get_free_pages(GFP_KERNEL, 0))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(tsk) free_pages((unsigned long)(tsk),0)
macro_line|#endif /* PAGE_SHIFT == 13 */
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)      atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__ASM_SPARC64_PROCESSOR_H) */
eof
