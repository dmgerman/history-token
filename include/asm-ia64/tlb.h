macro_line|#ifndef _ASM_IA64_TLB_H
DECL|macro|_ASM_IA64_TLB_H
mdefine_line|#define _ASM_IA64_TLB_H
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * This file was derived from asm-generic/tlb.h.&n; */
multiline_comment|/*&n; * Removing a translation from a page table (including TLB-shootdown) is a four-step&n; * procedure:&n; *&n; *&t;(1) Flush (virtual) caches --- ensures virtual memory is coherent with kernel memory&n; *&t;    (this is a no-op on ia64).&n; *&t;(2) Clear the relevant portions of the page-table&n; *&t;(3) Flush the TLBs --- ensures that stale content is gone from CPU TLBs&n; *&t;(4) Release the pages that were freed up in step (2).&n; *&n; * Note that the ordering of these steps is crucial to avoid races on MP machines.&n; *&n; * The Linux kernel defines several platform-specific hooks for TLB-shootdown.  When&n; * unmapping a portion of the virtual address space, these hooks are called according to&n; * the following template:&n; *&n; *&t;tlb &lt;- tlb_gather_mmu(mm, full_mm_flush);&t;// start unmap for address space MM&n; *&t;{&n; *&t;  for each vma that needs a shootdown do {&n; *&t;    tlb_start_vma(tlb, vma);&n; *&t;      for each page-table-entry PTE that needs to be removed do {&n; *&t;&t;tlb_remove_tlb_entry(tlb, pte, address);&n; *&t;&t;if (pte refers to a normal page) {&n; *&t;&t;  tlb_remove_page(tlb, page);&n; *&t;&t;}&n; *&t;      }&n; *&t;    tlb_end_vma(tlb, vma);&n; *&t;  }&n; *&t;}&n; *&t;tlb_finish_mmu(tlb, start, end);&t;// finish unmap for address space MM&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifdef CONFIG_SMP
DECL|macro|FREE_PTE_NR
macro_line|# define FREE_PTE_NR&t;&t;2048
DECL|macro|tlb_fast_mode
macro_line|# define tlb_fast_mode(tlb)&t;((tlb)-&gt;nr == ~0U)
macro_line|#else
DECL|macro|FREE_PTE_NR
macro_line|# define FREE_PTE_NR&t;&t;0
DECL|macro|tlb_fast_mode
macro_line|# define tlb_fast_mode(tlb)&t;(1)
macro_line|#endif
r_typedef
r_struct
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
multiline_comment|/* == ~0U =&gt; fast mode */
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
multiline_comment|/* number of pages freed */
DECL|member|start_addr
r_int
r_int
id|start_addr
suffix:semicolon
DECL|member|end_addr
r_int
r_int
id|end_addr
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
multiline_comment|/*&n; * Flush the TLB for address range START to END and, if not in fast mode, release the&n; * freed pages that where gathered up to this point.&n; */
r_static
r_inline
r_void
DECL|function|ia64_tlb_flush_mmu
id|ia64_tlb_flush_mmu
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
r_int
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|tlb-&gt;fullmm
)paren
(brace
multiline_comment|/*&n;&t;&t; * Tearing down the entire address space.  This happens both as a result&n;&t;&t; * of exit() and execve().  The latter case necessitates the call to&n;&t;&t; * flush_tlb_mm() here.&n;&t;&t; */
id|flush_tlb_mm
c_func
(paren
id|tlb-&gt;mm
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
(paren
id|end
op_minus
id|start
op_ge
l_int|1024
op_star
l_int|1024
op_star
l_int|1024
op_star
l_int|1024UL
op_logical_or
id|REGION_NUMBER
c_func
(paren
id|start
)paren
op_ne
id|REGION_NUMBER
c_func
(paren
id|end
op_minus
l_int|1
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we flush more than a tera-byte or across regions, we&squot;re probably&n;&t;&t; * better off just flushing the entire TLB(s).  This should be very rare&n;&t;&t; * and is not worth optimizing for.&n;&t;&t; */
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * XXX fix me: flush_tlb_range() should take an mm pointer instead of a&n;&t;&t; * vma pointer.&n;&t;&t; */
r_struct
id|vm_area_struct
id|vma
suffix:semicolon
id|vma.vm_mm
op_assign
id|tlb-&gt;mm
suffix:semicolon
multiline_comment|/* flush the address range from the tlb: */
id|flush_tlb_range
c_func
(paren
op_amp
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
multiline_comment|/* now flush the virt. page-table area mapping the address range: */
id|flush_tlb_range
c_func
(paren
op_amp
id|vma
comma
id|ia64_thash
c_func
(paren
id|start
)paren
comma
id|ia64_thash
c_func
(paren
id|end
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* lastly, release the freed pages */
id|nr
op_assign
id|tlb-&gt;nr
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
r_int
r_int
id|i
suffix:semicolon
id|tlb-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|tlb-&gt;start_addr
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
op_increment
id|i
)paren
id|free_page_and_swap_cache
c_func
(paren
id|tlb-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Return a pointer to an initialized mmu_gather_t.&n; */
r_static
r_inline
id|mmu_gather_t
op_star
DECL|function|tlb_gather_mmu
id|tlb_gather_mmu
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
multiline_comment|/*&n;&t; * Use fast mode if only 1 CPU is online.&n;&t; *&n;&t; * It would be tempting to turn on fast-mode for full_mm_flush as well.  But this&n;&t; * doesn&squot;t work because of speculative accesses and software prefetching: the page&n;&t; * table of &quot;mm&quot; may (and usually is) the currently active page table and even&n;&t; * though the kernel won&squot;t do any user-space accesses during the TLB shoot down, a&n;&t; * compiler might use speculation or lfetch.fault on what happens to be a valid&n;&t; * user-space address.  This in turn could trigger a TLB miss fault (or a VHPT&n;&t; * walk) and re-insert a TLB entry we just removed.  Slow mode avoids such&n;&t; * problems.  (We could make fast-mode work by switching the current task to a&n;&t; * different &quot;mm&quot; during the shootdown.) --davidm 08/02/2002&n;&t; */
id|tlb-&gt;nr
op_assign
(paren
id|num_online_cpus
c_func
(paren
)paren
op_eq
l_int|1
)paren
ques
c_cond
op_complement
l_int|0U
suffix:colon
l_int|0
suffix:semicolon
id|tlb-&gt;fullmm
op_assign
id|full_mm_flush
suffix:semicolon
id|tlb-&gt;freed
op_assign
l_int|0
suffix:semicolon
id|tlb-&gt;start_addr
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_return
id|tlb
suffix:semicolon
)brace
multiline_comment|/*&n; * Called at the end of the shootdown operation to free up any resources that were&n; * collected.  The page table lock is still held at this point.&n; */
r_static
r_inline
r_void
DECL|function|tlb_finish_mmu
id|tlb_finish_mmu
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
multiline_comment|/*&n;&t; * Note: tlb-&gt;nr may be 0 at this point, so we can&squot;t rely on tlb-&gt;start_addr and&n;&t; * tlb-&gt;end_addr.&n;&t; */
id|ia64_tlb_flush_mmu
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
multiline_comment|/*&n; * Remove TLB entry for PTE mapped at virtual address ADDRESS.  This is called for any&n; * PTE, not just those pointing to (normal) physical memory.&n; */
r_static
r_inline
r_void
DECL|function|tlb_remove_tlb_entry
id|tlb_remove_tlb_entry
(paren
id|mmu_gather_t
op_star
id|tlb
comma
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|address
)paren
(brace
r_if
c_cond
(paren
id|tlb-&gt;start_addr
op_eq
op_complement
l_int|0UL
)paren
id|tlb-&gt;start_addr
op_assign
id|address
suffix:semicolon
id|tlb-&gt;end_addr
op_assign
id|address
op_plus
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/*&n; * Logically, this routine frees PAGE.  On MP machines, the actual freeing of the page&n; * must be delayed until after the TLB has been flushed (see comments at the beginning of&n; * this file).&n; */
r_static
r_inline
r_void
DECL|function|tlb_remove_page
id|tlb_remove_page
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
id|ia64_tlb_flush_mmu
c_func
(paren
id|tlb
comma
id|tlb-&gt;start_addr
comma
id|tlb-&gt;end_addr
)paren
suffix:semicolon
)brace
DECL|macro|tlb_start_vma
mdefine_line|#define tlb_start_vma(tlb, vma)&t;&t;&t;do { } while (0)
DECL|macro|tlb_end_vma
mdefine_line|#define tlb_end_vma(tlb, vma)&t;&t;&t;do { } while (0)
macro_line|#endif /* _ASM_IA64_TLB_H */
eof
