macro_line|#ifndef _PGTABLE_NOPUD_H
DECL|macro|_PGTABLE_NOPUD_H
mdefine_line|#define _PGTABLE_NOPUD_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Having the pud type consist of a pgd gets the size right, and allows&n; * us to conceptually access the pgd entry that this pud is folded into&n; * without casting.&n; */
DECL|member|pgd
DECL|typedef|pud_t
r_typedef
r_struct
(brace
id|pgd_t
id|pgd
suffix:semicolon
)brace
id|pud_t
suffix:semicolon
DECL|macro|PUD_SHIFT
mdefine_line|#define PUD_SHIFT&t;PGDIR_SHIFT
DECL|macro|PTRS_PER_PUD
mdefine_line|#define PTRS_PER_PUD&t;1
DECL|macro|PUD_SIZE
mdefine_line|#define PUD_SIZE  &t;(1UL &lt;&lt; PUD_SHIFT)
DECL|macro|PUD_MASK
mdefine_line|#define PUD_MASK  &t;(~(PUD_SIZE-1))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pud is never bad, and a pud always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
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
DECL|macro|pud_ERROR
mdefine_line|#define pud_ERROR(pud)&t;&t;&t;&t;(pgd_ERROR((pud).pgd))
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pgd, pud)&t;&t;do { } while (0)
multiline_comment|/*&n; * (puds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval)&t;&t;&t;set_pud((pud_t *)(pgdptr), (pud_t) { pgdval })
DECL|function|pud_offset
r_static
r_inline
id|pud_t
op_star
id|pud_offset
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
id|pud_t
op_star
)paren
id|pgd
suffix:semicolon
)brace
DECL|macro|pud_val
mdefine_line|#define pud_val(x)&t;&t;&t;&t;(pgd_val((x).pgd))
DECL|macro|__pud
mdefine_line|#define __pud(x)&t;&t;&t;&t;((pud_t) { __pgd(x) } )
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;&t;&t;(pud_page((pud_t){ pgd }))
DECL|macro|pgd_page_kernel
mdefine_line|#define pgd_page_kernel(pgd)&t;&t;&t;(pud_page_kernel((pud_t){ pgd }))
multiline_comment|/*&n; * allocating and freeing a pud is trivial: the 1-entry pud is&n; * inside the pgd, so has no extra memory associated with it.&n; */
DECL|macro|pud_alloc_one
mdefine_line|#define pud_alloc_one(mm, address)&t;&t;NULL
DECL|macro|pud_free
mdefine_line|#define pud_free(x)&t;&t;&t;&t;do { } while (0)
DECL|macro|__pud_free_tlb
mdefine_line|#define __pud_free_tlb(tlb, x)&t;&t;&t;do { } while (0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PGTABLE_NOPUD_H */
eof
