macro_line|#ifndef _MOTOROLA_PGALLOC_H
DECL|macro|_MOTOROLA_PGALLOC_H
mdefine_line|#define _MOTOROLA_PGALLOC_H
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
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
DECL|function|pte_alloc_one_kernel
r_static
r_inline
id|pte_t
op_star
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
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
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|__flush_page_to_ram
c_func
(paren
id|pte
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|pte
)paren
suffix:semicolon
id|nocache_page
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_free_kernel
r_static
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
id|cache_page
c_func
(paren
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
DECL|function|pte_alloc_one
r_static
r_inline
r_struct
id|page
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|pte
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|__flush_page_to_ram
c_func
(paren
id|pte
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|pte
)paren
suffix:semicolon
id|nocache_page
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
id|kunmap
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|pte_free
r_static
r_inline
r_void
id|pte_free
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|cache_page
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|__pte_free_tlb
r_static
r_inline
r_void
id|__pte_free_tlb
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|cache_page
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc_one
r_static
r_inline
id|pmd_t
op_star
id|pmd_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|get_pointer_table
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmd_free
r_static
r_inline
r_int
id|pmd_free
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
DECL|function|__pmd_free_tlb
r_static
r_inline
r_int
id|__pmd_free_tlb
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
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
DECL|function|pgd_free
r_static
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
id|pmd_free
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
r_static
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
r_return
(paren
id|pgd_t
op_star
)paren
id|get_pointer_table
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmd_populate_kernel
r_static
r_inline
r_void
id|pmd_populate_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd
comma
id|pte_t
op_star
id|pte
)paren
(brace
id|pmd_set
c_func
(paren
id|pmd
comma
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pmd_populate
r_static
r_inline
r_void
id|pmd_populate
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|pmd_set
c_func
(paren
id|pmd
comma
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_populate
r_static
r_inline
r_void
id|pgd_populate
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pgd_t
op_star
id|pgd
comma
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pgd_set
c_func
(paren
id|pgd
comma
id|pmd
)paren
suffix:semicolon
)brace
macro_line|#endif /* _MOTOROLA_PGALLOC_H */
eof
