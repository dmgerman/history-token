multiline_comment|/* sun3_pgalloc.h --&n; * reorganization around 2.3.39, routines moved from sun3_pgtable.h &n; *&n; *&n; * 02/27/2002 -- Modified to support &quot;highpte&quot; implementation in 2.5.5 (Sam)&n; *&n; * moved 1/26/2000 Sam Creasey&n; */
macro_line|#ifndef _SUN3_PGALLOC_H
DECL|macro|_SUN3_PGALLOC_H
mdefine_line|#define _SUN3_PGALLOC_H
macro_line|#include &lt;asm/tlb.h&gt;
multiline_comment|/* FIXME - when we get this compiling */
multiline_comment|/* erm, now that it&squot;s compiling, what do we do with it? */
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE 0
r_extern
r_const
r_char
id|bad_pmd_string
(braket
)braket
suffix:semicolon
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm,address)       ({ BUG(); ((pmd_t *)2); })
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
DECL|function|__pte_free_tlb
r_static
r_inline
r_void
id|__pte_free_tlb
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
id|tlb_remove_page
c_func
(paren
id|tlb
comma
id|page
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
r_int
r_int
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
(paren
id|page
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
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|clear_highpage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
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
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
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
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb, x)&t;&t;do { } while (0)
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
id|new_pgd
suffix:semicolon
id|new_pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_pgd
comma
id|swapper_pg_dir
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
id|new_pgd
comma
l_int|0
comma
(paren
id|PAGE_OFFSET
op_rshift
id|PGDIR_SHIFT
)paren
)paren
suffix:semicolon
r_return
id|new_pgd
suffix:semicolon
)brace
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pmd, pte) BUG()
macro_line|#endif /* SUN3_PGALLOC_H */
eof
