multiline_comment|/* asm-generic/tlb.h&n; *&n; *&t;Generic TLB shootdown code&n; *&n; * Copyright 2001 Red Hat, Inc.&n; * Based on code from mm/memory.c Copyright Linus Torvalds and others.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_GENERIC__TLB_H
DECL|macro|_ASM_GENERIC__TLB_H
mdefine_line|#define _ASM_GENERIC__TLB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * For UP we don&squot;t need to worry about TLB flush&n; * and page free order so much..&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|FREE_PTE_NR
mdefine_line|#define FREE_PTE_NR&t;506
DECL|macro|tlb_fast_mode
mdefine_line|#define tlb_fast_mode(tlb) ((tlb)-&gt;nr == ~0U)
macro_line|#else
DECL|macro|FREE_PTE_NR
mdefine_line|#define FREE_PTE_NR&t;1
DECL|macro|tlb_fast_mode
mdefine_line|#define tlb_fast_mode(tlb) 1
macro_line|#endif
multiline_comment|/* mmu_gather_t is an opaque type used by the mm code for passing around any&n; * data needed by arch specific code for tlb_remove_page.  This structure can&n; * be per-CPU or per-MM as the page table lock is held for the duration of TLB&n; * shootdown.&n; */
DECL|struct|free_pte_ctx
r_typedef
r_struct
id|free_pte_ctx
(brace
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
multiline_comment|/* set to ~0U means fast mode */
DECL|member|need_flush
r_int
r_int
id|need_flush
suffix:semicolon
multiline_comment|/* Really unmapped some ptes? */
DECL|member|fullmm
r_int
r_int
id|fullmm
suffix:semicolon
multiline_comment|/* non-zero means full mm flush */
DECL|member|freed
r_int
r_int
id|freed
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
DECL|typedef|mmu_gather_t
)brace
id|mmu_gather_t
suffix:semicolon
multiline_comment|/* Users of the generic TLB shootdown code must declare this storage space. */
r_extern
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* tlb_gather_mmu&n; *&t;Return a pointer to an initialized mmu_gather_t.&n; */
DECL|function|tlb_gather_mmu
r_static
r_inline
id|mmu_gather_t
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
id|mmu_gather_t
op_star
id|tlb
op_assign
op_amp
id|mmu_gathers
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|tlb-&gt;mm
op_assign
id|mm
suffix:semicolon
multiline_comment|/* Use fast mode if only one CPU is online */
id|tlb-&gt;nr
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
id|tlb-&gt;fullmm
op_assign
id|full_mm_flush
suffix:semicolon
id|tlb-&gt;freed
op_assign
l_int|0
suffix:semicolon
r_return
id|tlb
suffix:semicolon
)brace
DECL|function|tlb_flush_mmu
r_static
r_inline
r_void
id|tlb_flush_mmu
c_func
(paren
id|mmu_gather_t
op_star
id|tlb
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
r_if
c_cond
(paren
op_logical_neg
id|tlb-&gt;need_flush
)paren
r_return
suffix:semicolon
id|tlb-&gt;need_flush
op_assign
l_int|0
suffix:semicolon
id|tlb_flush
c_func
(paren
id|tlb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tlb_fast_mode
c_func
(paren
id|tlb
)paren
)paren
(brace
id|free_pages_and_swap_cache
c_func
(paren
id|tlb-&gt;pages
comma
id|tlb-&gt;nr
)paren
suffix:semicolon
id|tlb-&gt;nr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* tlb_finish_mmu&n; *&t;Called at the end of the shootdown operation to free up any resources&n; *&t;that were required.  The page table lock is still held at this point.&n; */
DECL|function|tlb_finish_mmu
r_static
r_inline
r_void
id|tlb_finish_mmu
c_func
(paren
id|mmu_gather_t
op_star
id|tlb
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
id|freed
op_assign
id|tlb-&gt;freed
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tlb-&gt;mm
suffix:semicolon
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
id|tlb
comma
id|start
comma
id|end
)paren
suffix:semicolon
multiline_comment|/* keep the page table cache within bounds */
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* void tlb_remove_page(mmu_gather_t *tlb, pte_t *ptep, unsigned long addr)&n; *&t;Must perform the equivalent to __free_pte(pte_get_and_clear(ptep)), while&n; *&t;handling the additional races in SMP caused by other CPUs caching valid&n; *&t;mappings in their TLBs.&n; */
DECL|function|tlb_remove_page
r_static
r_inline
r_void
id|tlb_remove_page
c_func
(paren
id|mmu_gather_t
op_star
id|tlb
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|tlb-&gt;need_flush
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tlb_fast_mode
c_func
(paren
id|tlb
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
id|tlb-&gt;pages
(braket
id|tlb-&gt;nr
op_increment
)braket
op_assign
id|page
suffix:semicolon
r_if
c_cond
(paren
id|tlb-&gt;nr
op_ge
id|FREE_PTE_NR
)paren
id|tlb_flush_mmu
c_func
(paren
id|tlb
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * tlb_remove_tlb_entry - remember a pte unmapping for later tlb invalidation.&n; *&n; * Record the fact that pte&squot;s were really umapped in -&gt;need_flush, so we can&n; * later optimise away the tlb invalidate.   This helps when userspace is&n; * unmapping already-unmapped pages, which happens quite a lot.&n; */
DECL|macro|tlb_remove_tlb_entry
mdefine_line|#define tlb_remove_tlb_entry(tlb, ptep, address)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tlb-&gt;need_flush = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;__tlb_remove_tlb_entry(tlb, ptep, address);&t;&bslash;&n;&t;} while (0)
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb, ptep)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tlb-&gt;need_flush = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;__pte_free_tlb(tlb, ptep);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb, pmdp)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tlb-&gt;need_flush = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;__pmd_free_tlb(tlb, pmdp);&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif /* _ASM_GENERIC__TLB_H */
eof
