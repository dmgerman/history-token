multiline_comment|/* $Id: pgalloc.h,v 1.16 2001/12/21 04:56:17 davem Exp $ */
macro_line|#ifndef _SPARC_PGALLOC_H
DECL|macro|_SPARC_PGALLOC_H
mdefine_line|#define _SPARC_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
r_struct
id|page
suffix:semicolon
DECL|struct|pgtable_cache_struct
r_extern
r_struct
id|pgtable_cache_struct
(brace
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
DECL|member|pgd_cache_sz
r_int
r_int
id|pgd_cache_sz
suffix:semicolon
)brace
id|pgt_quicklists
suffix:semicolon
DECL|macro|pgd_quicklist
mdefine_line|#define pgd_quicklist           (pgt_quicklists.pgd_cache)
DECL|macro|pmd_quicklist
mdefine_line|#define pmd_quicklist           ((unsigned long *)0)
DECL|macro|pte_quicklist
mdefine_line|#define pte_quicklist           (pgt_quicklists.pte_cache)
DECL|macro|pgtable_cache_size
mdefine_line|#define pgtable_cache_size      (pgt_quicklists.pgtable_cache_sz)
DECL|macro|pgd_cache_size
mdefine_line|#define pgd_cache_size&t;&t;(pgt_quicklists.pgd_cache_sz)
r_extern
r_void
id|check_pgt_cache
c_func
(paren
r_void
)paren
suffix:semicolon
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|do_check_pgt_cache
comma
r_int
comma
r_int
)paren
DECL|macro|do_check_pgt_cache
mdefine_line|#define do_check_pgt_cache(low,high) BTFIXUP_CALL(do_check_pgt_cache)(low,high)
id|BTFIXUPDEF_CALL
c_func
(paren
id|pgd_t
op_star
comma
id|get_pgd_fast
comma
r_void
)paren
DECL|macro|get_pgd_fast
mdefine_line|#define get_pgd_fast()&t;&t;BTFIXUP_CALL(get_pgd_fast)()
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|free_pgd_fast
comma
id|pgd_t
op_star
)paren
DECL|macro|free_pgd_fast
mdefine_line|#define free_pgd_fast(pgd)&t;BTFIXUP_CALL(free_pgd_fast)(pgd)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;free_pgd_fast(pgd)
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;get_pgd_fast()
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pgd_set
comma
id|pgd_t
op_star
comma
id|pmd_t
op_star
)paren
DECL|macro|pgd_set
mdefine_line|#define pgd_set(pgdp,pmdp) BTFIXUP_CALL(pgd_set)(pgdp,pmdp)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(MM, PGD, PMD)      pgd_set(PGD, PMD)
id|BTFIXUPDEF_CALL
c_func
(paren
id|pmd_t
op_star
comma
id|pmd_alloc_one
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm, address)&t;BTFIXUP_CALL(pmd_alloc_one)(mm, address)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|free_pmd_fast
comma
id|pmd_t
op_star
)paren
DECL|macro|free_pmd_fast
mdefine_line|#define free_pmd_fast(pmd)&t;BTFIXUP_CALL(free_pmd_fast)(pmd)
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)           free_pmd_fast(pmd)
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb, pmd)&t;pmd_free(pmd)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pmd_populate
comma
id|pmd_t
op_star
comma
r_struct
id|page
op_star
)paren
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(MM, PMD, PTE)        BTFIXUP_CALL(pmd_populate)(PMD, PTE)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pmd_set
comma
id|pmd_t
op_star
comma
id|pte_t
op_star
)paren
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(MM, PMD, PTE) BTFIXUP_CALL(pmd_set)(PMD, PTE)
id|BTFIXUPDEF_CALL
c_func
(paren
r_struct
id|page
op_star
comma
id|pte_alloc_one
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|pte_alloc_one
mdefine_line|#define pte_alloc_one(mm, address)&t;BTFIXUP_CALL(pte_alloc_one)(mm, address)
id|BTFIXUPDEF_CALL
c_func
(paren
id|pte_t
op_star
comma
id|pte_alloc_one_kernel
comma
r_struct
id|mm_struct
op_star
comma
r_int
r_int
)paren
DECL|macro|pte_alloc_one_kernel
mdefine_line|#define pte_alloc_one_kernel(mm, addr)&t;BTFIXUP_CALL(pte_alloc_one_kernel)(mm, addr)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|free_pte_fast
comma
id|pte_t
op_star
)paren
DECL|macro|pte_free_kernel
mdefine_line|#define pte_free_kernel(pte)&t;BTFIXUP_CALL(free_pte_fast)(pte)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pte_free
comma
r_struct
id|page
op_star
)paren
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)&t;&t;BTFIXUP_CALL(pte_free)(pte)
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb, pte)&t;pte_free(pte)
macro_line|#endif /* _SPARC_PGALLOC_H */
eof
