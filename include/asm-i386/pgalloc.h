macro_line|#ifndef _I386_PGALLOC_H
DECL|macro|_I386_PGALLOC_H
mdefine_line|#define _I386_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* for struct page */
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(mm, pmd, pte) &bslash;&n;&t;&t;set_pmd(pmd, __pmd(_PAGE_TABLE + __pa(pte)))
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
op_plus
(paren
(paren
r_int
r_int
r_int
)paren
(paren
id|pte
op_minus
id|mem_map
)paren
op_lshift
(paren
r_int
r_int
r_int
)paren
id|PAGE_SHIFT
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and free page tables.&n; */
r_extern
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
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
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb,pte) tlb_remove_page((tlb),(pte))
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; * (In the PAE case we free the pmds as part of the pgd.)&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm, addr)&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb,x)&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pmd, pte)&t;BUG()
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif /* _I386_PGALLOC_H */
eof
