multiline_comment|/*&n; *  include/asm-s390/pgalloc.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999, 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hpenner@de.ibm.com)&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/pgalloc.h&quot;&n; *    Copyright (C) 1994  Linus Torvalds&n; */
macro_line|#ifndef _S390_PGALLOC_H
DECL|macro|_S390_PGALLOC_H
mdefine_line|#define _S390_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist (S390_lowcore.cpu_data.pgd_quick)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist (S390_lowcore.cpu_data.pmd_quick)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist (S390_lowcore.cpu_data.pte_quick)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size (S390_lowcore.cpu_data.pgtable_cache_sz)
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
multiline_comment|/*&n; * page directory allocation/free routines.&n; */
DECL|function|get_pgd_slow
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_slow
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|pgd_t
op_star
id|ret
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
id|pgd_clear
c_func
(paren
id|ret
op_plus
id|i
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|get_pgd_fast
r_extern
id|__inline__
id|pgd_t
op_star
id|get_pgd_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
id|pgd_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|pgd_alloc
r_extern
id|__inline__
id|pgd_t
op_star
id|pgd_alloc
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pgd
op_assign
id|get_pgd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
id|pgd
op_assign
id|get_pgd_slow
c_func
(paren
)paren
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_extern
id|__inline__
r_void
id|free_pgd_fast
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|pgd
op_assign
(paren
r_int
r_int
)paren
id|pgd_quicklist
suffix:semicolon
id|pgd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pgd
suffix:semicolon
id|pgtable_cache_size
op_add_assign
l_int|4
suffix:semicolon
)brace
DECL|function|free_pgd_slow
r_extern
id|__inline__
r_void
id|free_pgd_slow
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;free_pgd_fast(pgd)
multiline_comment|/*&n; * page middle directory allocation/free routines.&n; */
r_extern
id|pmd_t
id|empty_bad_pmd_table
(braket
)braket
suffix:semicolon
r_extern
id|pmd_t
op_star
id|get_pmd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|function|get_pmd_fast
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|pmd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pmd_fast
r_extern
id|__inline__
r_void
id|free_pmd_fast
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_if
c_cond
(paren
id|pmd
op_eq
id|empty_bad_pmd_table
)paren
r_return
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|pmd
op_assign
(paren
r_int
r_int
)paren
id|pmd_quicklist
suffix:semicolon
id|pmd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pmd
suffix:semicolon
id|pgtable_cache_size
op_add_assign
l_int|4
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_extern
id|__inline__
r_void
id|free_pmd_slow
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc
r_extern
id|__inline__
id|pmd_t
op_star
id|pmd_alloc
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|vmaddr
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd_t
op_star
id|pmd_page
op_assign
id|get_pmd_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_page
)paren
r_return
id|get_pmd_slow
c_func
(paren
id|pgd
comma
id|offset
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
id|pmd_page
)paren
suffix:semicolon
r_return
id|pmd_page
op_plus
id|offset
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|offset
suffix:semicolon
)brace
DECL|macro|pmd_alloc_kernel
mdefine_line|#define pmd_alloc_kernel(pgd, addr)&t;pmd_alloc(pgd, addr)
DECL|macro|pmd_free_kernel
mdefine_line|#define pmd_free_kernel(pmd)&t;free_pmd_fast(pmd)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;free_pmd_fast(pmd)
multiline_comment|/*&n; * page table entry allocation/free routines.&n; */
r_extern
id|pte_t
id|empty_bad_pte_table
(braket
)braket
suffix:semicolon
r_extern
id|pte_t
op_star
id|get_pte_slow
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address_preadjusted
)paren
suffix:semicolon
DECL|function|get_pte_fast
r_extern
id|__inline__
id|pte_t
op_star
id|get_pte_fast
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|ret
)paren
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
id|ret
(braket
l_int|1
)braket
suffix:semicolon
id|pgtable_cache_size
op_decrement
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|free_pte_fast
r_extern
id|__inline__
r_void
id|free_pte_fast
(paren
id|pte_t
op_star
id|pte
)paren
(brace
r_if
c_cond
(paren
id|pte
op_eq
id|empty_bad_pte_table
)paren
r_return
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
op_assign
(paren
r_int
r_int
)paren
id|pte_quicklist
suffix:semicolon
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
id|pgtable_cache_size
op_increment
suffix:semicolon
)brace
DECL|function|free_pte_slow
r_extern
id|__inline__
r_void
id|free_pte_slow
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc
r_extern
id|__inline__
id|pte_t
op_star
id|pte_alloc
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|vmaddr
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte_t
op_star
id|pte_page
op_assign
id|get_pte_fast
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|offset
)paren
suffix:semicolon
id|pmd_set
c_func
(paren
id|pmd
comma
id|pte_page
)paren
suffix:semicolon
r_return
id|pte_page
op_plus
id|offset
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|offset
suffix:semicolon
)brace
DECL|macro|pte_alloc_kernel
mdefine_line|#define pte_alloc_kernel(pmd, addr)&t;pte_alloc(pmd, addr)
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;free_pte_fast(pte)
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;free_pte_fast(pte)
r_extern
r_int
id|do_check_pgt_cache
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This establishes kernel virtual mappings (e.g., as a result of a&n; * vmalloc call).  Since s390-esame uses a separate kernel page table,&n; * there is nothing to do here... :)&n; */
DECL|macro|set_pgdir
mdefine_line|#define set_pgdir(vmaddr, entry)&t;do { } while(0)
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs &n; *    called only from vmalloc/vfree&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; *  - flush_tlb_pgtables(mm, start, end) flushes a range of page tables&n; */
multiline_comment|/*&n; * S/390 has three ways of flushing TLBs&n; * &squot;ptlb&squot; does a flush of the local processor&n; * &squot;csp&squot; flushes the TLBs on all PUs of a SMP&n; * &squot;ipte&squot; invalidates a pte in a page table and flushes that out of&n; * the TLBs of all PUs of a SMP&n; */
DECL|macro|local_flush_tlb
mdefine_line|#define local_flush_tlb() &bslash;&n;do {  __asm__ __volatile__(&quot;ptlb&quot;: : :&quot;memory&quot;); } while (0)
macro_line|#ifndef CONFIG_SMP
multiline_comment|/*&n; * We always need to flush, since s390 does not flush tlb&n; * on each context switch&n; */
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;&t;&t;local_flush_tlb()
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;local_flush_tlb()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;local_flush_tlb()
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, va)&t;&t;local_flush_tlb()
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm, start, end)&t;local_flush_tlb()
macro_line|#else
macro_line|#include &lt;asm/smp.h&gt;
DECL|function|global_flush_tlb
r_static
r_inline
r_void
id|global_flush_tlb
c_func
(paren
r_void
)paren
(brace
r_int
id|dummy
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;    la   4,3(%0)&bslash;n&quot;
l_string|&quot;    nill 4,0xfffc&bslash;n&quot;
l_string|&quot;    la   4,1(4)&bslash;n&quot;
l_string|&quot;    slr  2,2&bslash;n&quot;
l_string|&quot;    slr  3,3&bslash;n&quot;
l_string|&quot;    csp  2,4&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|dummy
)paren
suffix:colon
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We only have to do global flush of tlb if process run since last&n; * flush on any other pu than current. &n; * If we have threads (mm-&gt;count &gt; 1) we always do a global flush, &n; * since the process runs on more than one processor at the same time.&n; */
DECL|function|__flush_tlb_mm
r_static
r_inline
r_void
id|__flush_tlb_mm
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
(paren
id|smp_num_cpus
OG
l_int|1
)paren
op_logical_and
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_count
)paren
op_ne
l_int|1
)paren
op_logical_or
(paren
id|mm-&gt;cpu_vm_mask
op_ne
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
)paren
)paren
(brace
id|mm-&gt;cpu_vm_mask
op_assign
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|global_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb()&t;&t;&t;__flush_tlb_mm(current-&gt;mm)
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;global_flush_tlb()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;__flush_tlb_mm(mm)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, va)&t;&t;__flush_tlb_mm((vma)-&gt;vm_mm)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm, start, end)&t;__flush_tlb_mm(mm)
macro_line|#endif
DECL|function|flush_tlb_pgtables
r_extern
r_inline
r_void
id|flush_tlb_pgtables
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
multiline_comment|/* S/390 does not keep any page table caches in TLB */
)brace
DECL|function|ptep_test_and_clear_and_flush_young
r_static
r_inline
r_int
id|ptep_test_and_clear_and_flush_young
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|ptep
)paren
(brace
multiline_comment|/* No need to flush TLB; bits are in storage key */
r_return
id|ptep_test_and_clear_young
c_func
(paren
id|ptep
)paren
suffix:semicolon
)brace
DECL|function|ptep_test_and_clear_and_flush_dirty
r_static
r_inline
r_int
id|ptep_test_and_clear_and_flush_dirty
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|ptep
)paren
(brace
multiline_comment|/* No need to flush TLB; bits are in storage key */
r_return
id|ptep_test_and_clear_dirty
c_func
(paren
id|ptep
)paren
suffix:semicolon
)brace
DECL|function|ptep_invalidate
r_static
r_inline
id|pte_t
id|ptep_invalidate
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID
)paren
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;ipte %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|ptep
)paren
comma
l_string|&quot;a&quot;
(paren
id|address
)paren
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|ptep_establish
r_static
r_inline
r_void
id|ptep_establish
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|entry
)paren
(brace
id|ptep_invalidate
c_func
(paren
id|vma
comma
id|address
comma
id|ptep
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|entry
)paren
suffix:semicolon
)brace
macro_line|#endif /* _S390_PGALLOC_H */
eof
