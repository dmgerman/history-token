macro_line|#ifndef _ASM_PGALLOC_H
DECL|macro|_ASM_PGALLOC_H
mdefine_line|#define _ASM_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
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
macro_line|#ifdef __LP64__
multiline_comment|/* Three Level Page Table Support for pmd&squot;s */
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
id|pgd_val
c_func
(paren
op_star
id|pgd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
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
id|pmd
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
DECL|function|pmd_free
r_static
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
macro_line|#else
multiline_comment|/* Two Level Page Table Support for pmd&squot;s */
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm, addr)&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pmd, pte)&t;BUG()
macro_line|#endif
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
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|_PAGE_TABLE
op_plus
id|__pa
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
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm, pmd, pte_page) &bslash;&n;&t;pmd_populate_kernel(mm, pmd, page_address(pte_page))
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
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_page
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
id|page
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
id|page
)paren
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
r_static
r_inline
id|pte_t
op_star
DECL|function|pte_alloc_one_kernel
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
DECL|macro|pte_free
mdefine_line|#define pte_free(page)&t;pte_free_kernel(page_address(page))
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
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif
eof
