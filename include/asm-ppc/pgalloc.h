multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_PGALLOC_H
DECL|macro|_PPC_PGALLOC_H
mdefine_line|#define _PPC_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
multiline_comment|/*&n; * We don&squot;t have any real pmd&squot;s, and this code never triggers because&n; * the pgd will always be present..&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm,address)       ({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)                     do { } while (0)
DECL|macro|pmd_free_tlb
mdefine_line|#define pmd_free_tlb(tlb,x)&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm, pmd, pte)      BUG()
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(mm, pmd, pte)&t;&bslash;&n;&t;&t;(pmd_val(*(pmd)) = __pa(pte))
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm, pmd, pte)&t;&bslash;&n;&t;&t;(pmd_val(*(pmd)) = ((pte) - mem_map) &lt;&lt; PAGE_SHIFT)
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
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
suffix:semicolon
r_extern
r_void
id|pte_free
c_func
(paren
r_struct
id|page
op_star
id|pte
)paren
suffix:semicolon
DECL|macro|pte_free_tlb
mdefine_line|#define pte_free_tlb(tlb, pte)&t;pte_free((pte))
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif /* _PPC_PGALLOC_H */
macro_line|#endif /* __KERNEL__ */
eof
