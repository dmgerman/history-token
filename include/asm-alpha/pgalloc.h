macro_line|#ifndef _ALPHA_PGALLOC_H
DECL|macro|_ALPHA_PGALLOC_H
mdefine_line|#define _ALPHA_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
multiline_comment|/*      &n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
r_static
r_inline
r_void
DECL|function|pmd_populate
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
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
(paren
id|page_to_pa
c_func
(paren
id|pte
)paren
op_plus
id|PAGE_OFFSET
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pmd_populate_kernel
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
r_static
r_inline
r_void
DECL|function|pgd_populate
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
r_extern
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
suffix:semicolon
r_static
r_inline
r_void
DECL|function|pgd_free
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
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
r_static
r_inline
id|pmd_t
op_star
DECL|function|pmd_alloc_one
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
id|pmd_t
op_star
id|ret
op_assign
(paren
id|pmd_t
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
id|ret
)paren
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pmd_free
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
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
r_extern
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
id|addr
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|pte_free_kernel
id|pte_free_kernel
c_func
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
r_static
r_inline
r_struct
id|page
op_star
DECL|function|pte_alloc_one
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
id|addr
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_one_kernel
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
r_return
id|virt_to_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pte_free
id|pte_free
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif /* _ALPHA_PGALLOC_H */
eof
