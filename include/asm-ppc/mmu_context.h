multiline_comment|/*&n; * BK Id: SCCS/s.mmu_context.h 1.18 09/26/01 16:02:49 paulus&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_MMU_CONTEXT_H
DECL|macro|__PPC_MMU_CONTEXT_H
mdefine_line|#define __PPC_MMU_CONTEXT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
multiline_comment|/*&n; * On 32-bit PowerPC 6xx/7xx/7xxx CPUs, we use a set of 16 VSIDs&n; * (virtual segment identifiers) for each context.  Although the&n; * hardware supports 24-bit VSIDs, and thus &gt;1 million contexts,&n; * we only use 32,768 of them.  That is ample, since there can be&n; * at most around 30,000 tasks in the system anyway, and it means&n; * that we can use a bitmap to indicate which contexts are in use.&n; * Using a bitmap means that we entirely avoid all of the problems&n; * that we used to have when the context number overflowed,&n; * particularly on SMP systems.&n; *  -- paulus.&n; */
multiline_comment|/*&n; * This function defines the mapping from contexts to VSIDs (virtual&n; * segment IDs).  We use a skew on both the context and the high 4 bits&n; * of the 32-bit virtual address (the &quot;effective segment ID&quot;) in order&n; * to spread out the entries in the MMU hash table.  Note, if this&n; * function is changed then arch/ppc/mm/hashtable.S will have to be&n; * changed to correspond.&n; */
DECL|macro|CTX_TO_VSID
mdefine_line|#define CTX_TO_VSID(ctx, va)&t;(((ctx) * (897 * 16) + ((va) &gt;&gt; 28) * 0x111) &bslash;&n;&t;&t;&t;&t; &amp; 0xffffff)
multiline_comment|/*&n;   The MPC8xx has only 16 contexts.  We rotate through them on each&n;   task switch.  A better way would be to keep track of tasks that&n;   own contexts, and implement an LRU usage.  That way very active&n;   tasks don&squot;t always have to pay the TLB reload overhead.  The&n;   kernel pages are mapped shared, so the kernel can run on behalf&n;   of any task that makes a kernel entry.  Shared does not mean they&n;   are not protected, just that the ASID comparison is not performed.&n;        -- Dan&n;&n;   The IBM4xx has 256 contexts, so we can just rotate through these&n;   as a way of &quot;switching&quot; contexts.  If the TID of the TLB is zero,&n;   the PID/TID comparison is disabled, so we can use a TID of zero&n;   to represent all kernel pages as shared among all contexts.&n;   &t;-- Dan&n; */
DECL|function|enter_lazy_tlb
r_static
r_inline
r_void
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|cpu
)paren
(brace
)brace
macro_line|#ifdef CONFIG_8xx
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT      &t;16
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT    &t;15
DECL|macro|FIRST_CONTEXT
mdefine_line|#define FIRST_CONTEXT    &t;0
macro_line|#elif CONFIG_4xx
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT      &t;256
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT    &t;255
DECL|macro|FIRST_CONTEXT
mdefine_line|#define FIRST_CONTEXT    &t;1
macro_line|#else
multiline_comment|/* PPC 6xx, 7xx CPUs */
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT      &t;((mm_context_t) -1)
DECL|macro|LAST_CONTEXT
mdefine_line|#define LAST_CONTEXT    &t;32767
DECL|macro|FIRST_CONTEXT
mdefine_line|#define FIRST_CONTEXT    &t;1
macro_line|#endif
multiline_comment|/*&n; * Set the current MMU context.&n; * On 32-bit PowerPCs (other than the 8xx embedded chips), this is done by&n; * loading up the segment registers for the user part of the address space.&n; *&n; * Since the PGD is immediately available, it is much faster to simply&n; * pass this along as a second parameter, which is required for 8xx and&n; * can be used for debugging on all processors (if you happen to have&n; * an Abatron).&n; */
r_extern
r_void
id|set_context
c_func
(paren
id|mm_context_t
id|context
comma
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
multiline_comment|/*&n; * Bitmap of contexts in use.&n; * The size of this bitmap is LAST_CONTEXT + 1 bits.&n; */
r_extern
r_int
r_int
id|context_map
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * This caches the next context number that we expect to be free.&n; * Its use is an optimization only, we can&squot;t rely on this context&n; * number to be free, but it usually will be.&n; */
r_extern
id|mm_context_t
id|next_mmu_context
suffix:semicolon
multiline_comment|/*&n; * If we don&squot;t have sufficient contexts to give one to every task&n; * that could be in the system, we need to be able to steal contexts.&n; * These variables support that.&n; */
macro_line|#if LAST_CONTEXT &lt; 30000
DECL|macro|FEW_CONTEXTS
mdefine_line|#define FEW_CONTEXTS&t;1
r_extern
id|atomic_t
id|nr_free_contexts
suffix:semicolon
r_extern
r_struct
id|mm_struct
op_star
id|context_mm
(braket
id|LAST_CONTEXT
op_plus
l_int|1
)braket
suffix:semicolon
r_extern
r_void
id|steal_context
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Get a new mmu context for the address space described by `mm&squot;.&n; */
DECL|function|get_mmu_context
r_static
r_inline
r_void
id|get_mmu_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|mm_context_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
r_return
suffix:semicolon
macro_line|#ifdef FEW_CONTEXTS
r_while
c_loop
(paren
id|atomic_dec_if_positive
c_func
(paren
op_amp
id|nr_free_contexts
)paren
OL
l_int|0
)paren
id|steal_context
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ctx
op_assign
id|next_mmu_context
suffix:semicolon
r_while
c_loop
(paren
id|test_and_set_bit
c_func
(paren
id|ctx
comma
id|context_map
)paren
)paren
(brace
id|ctx
op_assign
id|find_next_zero_bit
c_func
(paren
id|context_map
comma
id|LAST_CONTEXT
op_plus
l_int|1
comma
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx
OG
id|LAST_CONTEXT
)paren
id|ctx
op_assign
l_int|0
suffix:semicolon
)brace
id|next_mmu_context
op_assign
(paren
id|ctx
op_plus
l_int|1
)paren
op_amp
id|LAST_CONTEXT
suffix:semicolon
id|mm-&gt;context
op_assign
id|ctx
suffix:semicolon
macro_line|#ifdef FEW_CONTEXTS
id|context_mm
(braket
id|ctx
)braket
op_assign
id|mm
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Set up the context for a new address space.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)&t;(((mm)-&gt;context = NO_CONTEXT), 0)
multiline_comment|/*&n; * We&squot;re finished using the context for an address space.&n; */
DECL|function|destroy_context
r_static
r_inline
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;context
op_ne
id|NO_CONTEXT
)paren
(brace
id|clear_bit
c_func
(paren
id|mm-&gt;context
comma
id|context_map
)paren
suffix:semicolon
id|mm-&gt;context
op_assign
id|NO_CONTEXT
suffix:semicolon
macro_line|#ifdef FEW_CONTEXTS
id|atomic_inc
c_func
(paren
op_amp
id|nr_free_contexts
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|switch_mm
r_static
r_inline
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|cpu
)paren
(brace
id|tsk-&gt;thread.pgdir
op_assign
id|next-&gt;pgd
suffix:semicolon
id|get_mmu_context
c_func
(paren
id|next
)paren
suffix:semicolon
id|set_context
c_func
(paren
id|next-&gt;context
comma
id|next-&gt;pgd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * After we have set current-&gt;mm to a new value, this activates&n; * the context for the new mm so we see the new mappings.&n; */
DECL|function|activate_mm
r_static
r_inline
r_void
id|activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|active_mm
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|current-&gt;thread.pgdir
op_assign
id|mm-&gt;pgd
suffix:semicolon
id|get_mmu_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|set_context
c_func
(paren
id|mm-&gt;context
comma
id|mm-&gt;pgd
)paren
suffix:semicolon
)brace
r_extern
r_void
id|mmu_context_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __PPC_MMU_CONTEXT_H */
macro_line|#endif /* __KERNEL__ */
eof
