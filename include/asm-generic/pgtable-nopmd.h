macro_line|#ifndef _PGTABLE_NOPMD_H
DECL|macro|_PGTABLE_NOPMD_H
mdefine_line|#define _PGTABLE_NOPMD_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Having the pmd type consist of a pgd gets the size right, and allows&n; * us to conceptually access the pgd entry that this pmd is folded into&n; * without casting.&n; */
DECL|member|pgd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
id|pgd_t
id|pgd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;PGDIR_SHIFT
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE  &t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK  &t;(~(PMD_SIZE-1))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pmd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_static
r_inline
r_int
id|pgd_none
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_bad
r_static
r_inline
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_static
r_inline
r_int
id|pgd_present
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pgd_clear
r_static
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
)brace
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(pmd)&t;&t;&t;&t;(pgd_ERROR((pmd).pgd))
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pmd, pte)&t;&t;do { } while (0)
DECL|macro|pgd_populate_kernel
mdefine_line|#define pgd_populate_kernel(mm, pmd, pte)&t;do { } while (0)
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval)&t;&t;&t;set_pmd((pmd_t *)(pgdptr), (pmd_t) { pgdval })
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
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
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
)brace
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;&t;&t;&t;(pgd_val((x).pgd))
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;&t;&t;&t;((pmd_t) { __pgd(x) } )
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;&t;&t;(pmd_page((pmd_t){ pgd }))
DECL|macro|pgd_page_kernel
mdefine_line|#define pgd_page_kernel(pgd)&t;&t;&t;(pmd_page_kernel((pmd_t){ pgd }))
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm, address)&t;&t;NULL
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;&t;do { } while (0)
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb, x)&t;&t;&t;do { } while (0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PGTABLE_NOPMD_H */
eof
