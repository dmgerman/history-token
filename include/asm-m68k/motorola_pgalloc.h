macro_line|#ifndef _MOTOROLA_PGALLOC_H
DECL|macro|_MOTOROLA_PGALLOC_H
mdefine_line|#define _MOTOROLA_PGALLOC_H
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pmd_cache
r_int
r_int
op_star
id|pmd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
multiline_comment|/* This counts in units of pointer tables, of which can be eight per page. */
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
id|quicklists
suffix:semicolon
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist ((unsigned long *)0)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist (quicklists.pmd_cache)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist (quicklists.pte_cache)
multiline_comment|/* This isn&squot;t accurate because of fragmentation of allocated pages for&n;   pointer tables, but that should not be a problem. */
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size ((quicklists.pgtable_cache_sz+7)/8)
r_extern
id|pte_t
op_star
id|get_pte_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|offset
)paren
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
id|offset
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
id|get_pointer_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|free_pointer_table
c_func
(paren
id|pmd_t
op_star
)paren
suffix:semicolon
DECL|function|get_pte_fast
r_extern
r_inline
id|pte_t
op_star
id|get_pte_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|pte_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|pte_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
op_star
id|ret
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|quicklists.pgtable_cache_sz
op_sub_assign
l_int|8
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
r_inline
r_void
id|free_pte_fast
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
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
id|quicklists.pgtable_cache_sz
op_add_assign
l_int|8
suffix:semicolon
)brace
DECL|function|free_pte_slow
r_extern
r_inline
r_void
id|free_pte_slow
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|cache_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
)paren
suffix:semicolon
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
DECL|function|get_pmd_fast
r_extern
r_inline
id|pmd_t
op_star
id|get_pmd_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|pmd_quicklist
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|pmd_quicklist
op_assign
(paren
r_int
r_int
op_star
)paren
op_star
id|ret
suffix:semicolon
id|ret
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|quicklists.pgtable_cache_sz
op_decrement
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
r_inline
r_void
id|free_pmd_fast
c_func
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
id|quicklists.pgtable_cache_sz
op_increment
suffix:semicolon
)brace
DECL|function|free_pmd_slow
r_extern
r_inline
r_int
id|free_pmd_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_return
id|free_pointer_table
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
multiline_comment|/* The pgd cache is folded into the pmd cache, so these are dummy routines. */
DECL|function|get_pgd_fast
r_extern
r_inline
id|pgd_t
op_star
id|get_pgd_fast
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pgd_t
op_star
)paren
l_int|0
suffix:semicolon
)brace
DECL|function|free_pgd_fast
r_extern
r_inline
r_void
id|free_pgd_fast
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
)brace
DECL|function|free_pgd_slow
r_extern
r_inline
r_void
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
)brace
r_extern
r_void
id|__bad_pte
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__bad_pmd
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|function|pte_free
r_extern
r_inline
r_void
id|pte_free
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_pte_fast
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc
r_extern
r_inline
id|pte_t
op_star
id|pte_alloc
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
id|address
op_assign
(paren
id|address
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
id|page
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
id|page
)paren
r_return
id|get_pte_slow
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|pmd_set
c_func
(paren
id|pmd
comma
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
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
(brace
id|__bad_pte
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pte_t
op_star
)paren
id|__pmd_page
c_func
(paren
op_star
id|pmd
)paren
op_plus
id|address
suffix:semicolon
)brace
DECL|function|pmd_free
r_extern
r_inline
r_void
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_pmd_fast
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc
r_extern
r_inline
id|pmd_t
op_star
id|pmd_alloc
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
(brace
id|address
op_assign
(paren
id|address
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
id|page
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
id|page
)paren
r_return
id|get_pmd_slow
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
id|page
)paren
suffix:semicolon
r_return
id|page
op_plus
id|address
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
(brace
id|__bad_pmd
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
id|__pgd_page
c_func
(paren
op_star
id|pgd
)paren
op_plus
id|address
suffix:semicolon
)brace
DECL|function|pte_free_kernel
r_extern
r_inline
r_void
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|free_pte_fast
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_kernel
r_extern
r_inline
id|pte_t
op_star
id|pte_alloc_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pte_alloc
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pmd_free_kernel
r_extern
r_inline
r_void
id|pmd_free_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_pmd_fast
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc_kernel
r_extern
r_inline
id|pmd_t
op_star
id|pmd_alloc_kernel
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
(brace
r_return
id|pmd_alloc
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|pgd_free
r_extern
r_inline
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_pmd_fast
c_func
(paren
(paren
id|pmd_t
op_star
)paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pgd_alloc
r_extern
r_inline
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|get_pmd_fast
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
(paren
id|pgd_t
op_star
)paren
id|get_pointer_table
c_func
(paren
)paren
suffix:semicolon
r_return
id|pgd
suffix:semicolon
)brace
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|function|set_pgdir
r_extern
r_inline
r_void
id|set_pgdir
c_func
(paren
r_int
r_int
id|address
comma
id|pgd_t
id|entry
)paren
(brace
)brace
multiline_comment|/*&n; * flush all user-space atc entries.&n; */
DECL|function|__flush_tlb
r_static
r_inline
r_void
id|__flush_tlb
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;pflushan&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;pflush #0,#4&quot;
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb040_one
r_static
r_inline
r_void
id|__flush_tlb040_one
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;pflush (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_one
r_static
r_inline
r_void
id|__flush_tlb_one
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|__flush_tlb040_one
c_func
(paren
id|addr
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;pflush #0,#4,(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|flush_tlb
mdefine_line|#define flush_tlb() __flush_tlb()
multiline_comment|/*&n; * flush all atc entries (both kernel and user-space entries).&n; */
DECL|function|flush_tlb_all
r_static
r_inline
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;pflusha&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;pflusha&quot;
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_static
r_inline
r_void
id|flush_tlb_mm
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
id|mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_static
r_inline
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb_one
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_range
r_static
r_inline
r_void
id|flush_tlb_range
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
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;mm
)paren
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_kernel_page
r_extern
r_inline
r_void
id|flush_tlb_kernel_page
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;pflush (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
)brace
r_else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;pflush #4,#4,(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
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
)brace
macro_line|#endif /* _MOTOROLA_PGALLOC_H */
eof
