macro_line|#ifndef _X86_64_PGALLOC_H
DECL|macro|_X86_64_PGALLOC_H
mdefine_line|#define _X86_64_PGALLOC_H
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(mm, pmd, pte) &bslash;&n;&t;&t;set_pmd(pmd, __pmd(_PAGE_TABLE | __pa(pte)))
DECL|macro|pud_populate
mdefine_line|#define pud_populate(mm, pud, pmd) &bslash;&n;&t;&t;set_pud(pud, __pud(_PAGE_TABLE | __pa(pmd)))
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pgd, pud) &bslash;&n;&t;&t;set_pgd(pgd, __pgd(_PAGE_TABLE | __pa(pud)))
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
id|pte
)paren
(brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_or
(paren
id|page_to_pfn
c_func
(paren
id|pte
)paren
op_lshift
id|PAGE_SHIFT
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_pmd
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|pmd_free
r_extern
id|__inline__
r_void
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pmd_alloc_one
r_static
r_inline
id|pmd_t
op_star
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
r_return
(paren
id|pmd_t
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
)brace
DECL|function|pud_alloc_one
r_static
r_inline
id|pud_t
op_star
id|pud_alloc_one
c_func
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
r_return
(paren
id|pud_t
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
)brace
DECL|function|pud_free
r_static
r_inline
r_void
id|pud_free
(paren
id|pud_t
op_star
id|pud
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
r_int
)paren
id|pud
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pud
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
r_int
id|boundary
suffix:semicolon
id|pgd_t
op_star
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
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Copy kernel pointers in from init.&n;&t; * Could keep a freelist or slab cache of those because the kernel&n;&t; * part never changes.&n;&t; */
id|boundary
op_assign
id|pgd_index
c_func
(paren
id|__PAGE_OFFSET
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pgd
comma
l_int|0
comma
id|boundary
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pgd
op_plus
id|boundary
comma
id|init_level4_pgt
op_plus
id|boundary
comma
(paren
id|PTRS_PER_PGD
op_minus
id|boundary
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
r_return
id|pgd
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
id|BUG_ON
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
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
r_return
(paren
id|pte_t
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
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
r_void
op_star
id|p
op_assign
(paren
r_void
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|virt_to_page
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* Should really implement gc for free page table pages. This could be&n;   done with a reference count in struct page. */
DECL|function|pte_free_kernel
r_extern
id|__inline__
r_void
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
id|BUG_ON
c_func
(paren
(paren
r_int
r_int
)paren
id|pte
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
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
DECL|function|pte_free
r_extern
r_inline
r_void
id|pte_free
c_func
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
DECL|macro|__pte_free_tlb
mdefine_line|#define __pte_free_tlb(tlb,pte) tlb_remove_page((tlb),(pte))
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb,x)   tlb_remove_page((tlb),virt_to_page(x))
DECL|macro|__pud_free_tlb
mdefine_line|#define __pud_free_tlb(tlb,x)   tlb_remove_page((tlb),virt_to_page(x))
macro_line|#endif /* _X86_64_PGALLOC_H */
eof
