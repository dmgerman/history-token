macro_line|#ifndef _ASM_IA64_PGALLOC_H
DECL|macro|_ASM_IA64_PGALLOC_H
mdefine_line|#define _ASM_IA64_PGALLOC_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to allocate&n; * page tables.&n; *&n; * This hopefully works with any (fixed) ia-64 page-size, as defined&n; * in &lt;asm/page.h&gt; (currently 8192).&n; *&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 2000, Goutham Rao &lt;goutham.rao@intel.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/page-flags.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Very stupidly, we used to get new pgd&squot;s and pmd&squot;s, init their contents&n; * to point to the NULL versions of the next level page table, later on&n; * completely re-init them the same way, then free them up.  This wasted&n; * a lot of work and caused unnecessary memory traffic.  How broken...&n; * We fix this by caching them.&n; */
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist&t;&t;(local_cpu_data-&gt;pgd_quick)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist&t;&t;(local_cpu_data-&gt;pmd_quick)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size&t;(local_cpu_data-&gt;pgtable_cache_sz)
r_static
r_inline
id|pgd_t
op_star
DECL|function|pgd_alloc_one_fast
id|pgd_alloc_one_fast
(paren
r_struct
id|mm_struct
op_star
id|mm
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
id|likely
c_func
(paren
id|ret
op_ne
l_int|NULL
)paren
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
l_int|0
suffix:semicolon
op_decrement
id|pgtable_cache_size
suffix:semicolon
)brace
r_else
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|pgd_t
op_star
)paren
id|ret
suffix:semicolon
)brace
r_static
r_inline
id|pgd_t
op_star
DECL|function|pgd_alloc
id|pgd_alloc
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* the VM system never calls pgd_alloc_one_fast(), so we do it here. */
id|pgd_t
op_star
id|pgd
op_assign
id|pgd_alloc_one_fast
c_func
(paren
id|mm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pgd
op_eq
l_int|NULL
)paren
)paren
(brace
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pgd
op_ne
l_int|NULL
)paren
)paren
id|clear_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pgd_free
id|pgd_free
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
op_increment
id|pgtable_cache_size
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pgd_populate
id|pgd_populate
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pgd_t
op_star
id|pgd_entry
comma
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgd_entry
)paren
op_assign
id|__pa
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
r_static
r_inline
id|pmd_t
op_star
DECL|function|pmd_alloc_one_fast
id|pmd_alloc_one_fast
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
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
id|likely
c_func
(paren
id|ret
op_ne
l_int|NULL
)paren
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
l_int|0
suffix:semicolon
op_decrement
id|pgtable_cache_size
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
r_static
r_inline
id|pmd_t
op_star
DECL|function|pmd_alloc_one
id|pmd_alloc_one
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pmd
op_ne
l_int|NULL
)paren
)paren
id|clear_page
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pmd_free
id|pmd_free
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
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
op_increment
id|pgtable_cache_size
suffix:semicolon
)brace
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb, pmd)&t;pmd_free(pmd)
r_static
r_inline
r_void
DECL|function|pmd_populate
id|pmd_populate
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd_entry
comma
r_struct
id|page
op_star
id|pte
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd_entry
)paren
op_assign
id|page_to_phys
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pmd_populate_kernel
id|pmd_populate_kernel
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd_entry
comma
id|pte_t
op_star
id|pte
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd_entry
)paren
op_assign
id|__pa
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|page
op_star
DECL|function|pte_alloc_one
id|pte_alloc_one
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|page
op_star
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pte
op_ne
l_int|NULL
)paren
)paren
id|clear_page
c_func
(paren
id|page_address
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
r_static
r_inline
id|pte_t
op_star
DECL|function|pte_alloc_one_kernel
id|pte_alloc_one_kernel
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pte
op_ne
l_int|NULL
)paren
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pte_free
id|pte_free
(paren
r_struct
id|page
op_star
id|pte
)paren
(brace
id|__free_page
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pte_free_kernel
id|pte_free_kernel
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
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb, pte)&t;tlb_remove_page((tlb), (pte))
r_extern
r_void
id|check_pgt_cache
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * IA-64 doesn&squot;t have any external MMU info: the page tables contain all the necessary&n; * information.  However, we use this macro to take care of any (delayed) i-cache flushing&n; * that may be necessary.&n; */
r_static
r_inline
r_void
DECL|function|update_mmu_cache
id|update_mmu_cache
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_exec
c_func
(paren
id|pte
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* not an executable page... */
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
multiline_comment|/* don&squot;t use VADDR: it may not be mapped on this CPU (or may have just been flushed): */
id|addr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* i-cache is already coherent with d-cache */
id|flush_icache_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* mark page as clean */
)brace
macro_line|#endif /* _ASM_IA64_PGALLOC_H */
eof
