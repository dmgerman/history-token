macro_line|#ifndef _SPARC64_TLB_H
DECL|macro|_SPARC64_TLB_H
mdefine_line|#define _SPARC64_TLB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
DECL|macro|TLB_BATCH_NR
mdefine_line|#define TLB_BATCH_NR&t;192
multiline_comment|/*&n; * For UP we don&squot;t need to worry about TLB flush&n; * and page free order so much..&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|FREE_PTE_NR
mdefine_line|#define FREE_PTE_NR&t;506
DECL|macro|tlb_fast_mode
mdefine_line|#define tlb_fast_mode(bp) ((bp)-&gt;pages_nr == ~0U)
macro_line|#else
DECL|macro|FREE_PTE_NR
mdefine_line|#define FREE_PTE_NR&t;1
DECL|macro|tlb_fast_mode
mdefine_line|#define tlb_fast_mode(bp) 1
macro_line|#endif
DECL|struct|mmu_gather
r_struct
id|mmu_gather
(brace
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|pages_nr
r_int
r_int
id|pages_nr
suffix:semicolon
DECL|member|need_flush
r_int
r_int
id|need_flush
suffix:semicolon
DECL|member|tlb_frozen
r_int
r_int
id|tlb_frozen
suffix:semicolon
DECL|member|tlb_nr
r_int
r_int
id|tlb_nr
suffix:semicolon
DECL|member|freed
r_int
r_int
id|freed
suffix:semicolon
DECL|member|vaddrs
r_int
r_int
id|vaddrs
(braket
id|TLB_BATCH_NR
)braket
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
id|pages
(braket
id|FREE_PTE_NR
)braket
suffix:semicolon
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_flush_tlb_pending
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|__flush_tlb_pending
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_pending
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|tlb_gather_mmu
r_static
r_inline
r_struct
id|mmu_gather
op_star
id|tlb_gather_mmu
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|full_mm_flush
)paren
(brace
r_struct
id|mmu_gather
op_star
id|mp
op_assign
op_amp
id|per_cpu
c_func
(paren
id|mmu_gathers
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mp-&gt;tlb_nr
)paren
suffix:semicolon
id|mp-&gt;mm
op_assign
id|mm
suffix:semicolon
id|mp-&gt;pages_nr
op_assign
id|num_online_cpus
c_func
(paren
)paren
OG
l_int|1
ques
c_cond
l_int|0U
suffix:colon
op_complement
l_int|0U
suffix:semicolon
id|mp-&gt;tlb_frozen
op_assign
id|full_mm_flush
suffix:semicolon
id|mp-&gt;freed
op_assign
l_int|0
suffix:semicolon
r_return
id|mp
suffix:semicolon
)brace
DECL|function|tlb_flush_mmu
r_static
r_inline
r_void
id|tlb_flush_mmu
c_func
(paren
r_struct
id|mmu_gather
op_star
id|mp
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;need_flush
)paren
(brace
id|mp-&gt;need_flush
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tlb_fast_mode
c_func
(paren
id|mp
)paren
)paren
(brace
id|free_pages_and_swap_cache
c_func
(paren
id|mp-&gt;pages
comma
id|mp-&gt;pages_nr
)paren
suffix:semicolon
id|mp-&gt;pages_nr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
DECL|macro|do_flush_tlb_mm
mdefine_line|#define do_flush_tlb_mm(mm) smp_flush_tlb_mm(mm)
macro_line|#else
DECL|macro|do_flush_tlb_mm
mdefine_line|#define do_flush_tlb_mm(mm) __flush_tlb_mm(CTX_HWBITS(mm-&gt;context), SECONDARY_CONTEXT)
macro_line|#endif
DECL|function|tlb_finish_mmu
r_static
r_inline
r_void
id|tlb_finish_mmu
c_func
(paren
r_struct
id|mmu_gather
op_star
id|mp
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|freed
op_assign
id|mp-&gt;freed
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|mp-&gt;mm
suffix:semicolon
r_int
r_int
id|rss
op_assign
id|mm-&gt;rss
suffix:semicolon
r_if
c_cond
(paren
id|rss
OL
id|freed
)paren
id|freed
op_assign
id|rss
suffix:semicolon
id|mm-&gt;rss
op_assign
id|rss
op_minus
id|freed
suffix:semicolon
id|tlb_flush_mmu
c_func
(paren
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;tlb_frozen
)paren
(brace
r_int
r_int
id|context
op_assign
id|mm-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|CTX_VALID
c_func
(paren
id|context
)paren
)paren
id|do_flush_tlb_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
id|mp-&gt;tlb_frozen
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* keep the page table cache within bounds */
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tlb_is_full_mm
r_static
r_inline
r_int
r_int
id|tlb_is_full_mm
c_func
(paren
r_struct
id|mmu_gather
op_star
id|mp
)paren
(brace
r_return
id|mp-&gt;tlb_frozen
suffix:semicolon
)brace
DECL|function|tlb_remove_page
r_static
r_inline
r_void
id|tlb_remove_page
c_func
(paren
r_struct
id|mmu_gather
op_star
id|mp
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|mp-&gt;need_flush
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tlb_fast_mode
c_func
(paren
id|mp
)paren
)paren
(brace
id|free_page_and_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mp-&gt;pages
(braket
id|mp-&gt;pages_nr
op_increment
)braket
op_assign
id|page
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;pages_nr
op_ge
id|FREE_PTE_NR
)paren
id|tlb_flush_mmu
c_func
(paren
id|mp
)paren
suffix:semicolon
)brace
DECL|macro|tlb_remove_tlb_entry
mdefine_line|#define tlb_remove_tlb_entry(mp,ptep,addr) do { } while (0)
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(mp,ptepage) pte_free(ptepage)
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(mp,pmdp) pmd_free(pmdp)
DECL|macro|tlb_migrate_finish
mdefine_line|#define tlb_migrate_finish(mm)&t;do { } while (0)
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma) do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;do { } while (0)
macro_line|#endif /* _SPARC64_TLB_H */
eof
