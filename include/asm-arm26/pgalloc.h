multiline_comment|/*&n; *  linux/include/asm-arm/pgalloc.h&n; *&n; *  Copyright (C) 2000-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGALLOC_H
DECL|macro|_ASMARM_PGALLOC_H
mdefine_line|#define _ASMARM_PGALLOC_H
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
r_extern
id|kmem_cache_t
op_star
id|pte_cache
suffix:semicolon
DECL|function|pte_alloc_one_kernel
r_static
r_inline
id|pte_t
(def_block
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
(brace
r_return
id|kmem_cache_alloc
c_func
(paren
id|pte_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
)def_block
DECL|function|pte_free_kernel
r_static
r_inline
r_void
(def_block
id|pte_free_kernel
c_func
(paren
id|pte_t
op_star
id|pte
)paren
(brace
r_if
c_cond
(paren
id|pte
)paren
id|kmem_cache_free
c_func
(paren
id|pte_cache
comma
id|pte
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Populate the pmdp entry with a pointer to the pte.  This pmd is part&n; * of the mm address space.&n; *&n; * If &squot;mm&squot; is the init tasks mm, then we are doing a vmalloc, and we&n; * need to set stuff up correctly for it.&n; */
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
id|pmdp
comma
id|pte_t
op_star
id|ptep
)paren
(brace
singleline_comment|//FIXME - is this doing the right thing?
id|set_pmd
c_func
(paren
id|pmdp
comma
(paren
r_int
r_int
)paren
id|ptep
op_or
l_int|1
multiline_comment|/*FIXME _PMD_PRESENT*/
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME - We use the old 2.5.5-rmk1 hack for this.&n; * This is not truly correct, but should be functional.&n; */
DECL|macro|pte_alloc_one
mdefine_line|#define pte_alloc_one(mm,addr)  ((struct page *)pte_alloc_one_kernel(mm,addr))
DECL|macro|pte_free
mdefine_line|#define pte_free(pte)           pte_free_kernel((pte_t *)pte)
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm,pmdp,ptep) pmd_populate_kernel(mm,pmdp,(pte_t *)ptep)
multiline_comment|/*&n; * Since we have only two-level page tables, these are trivial&n; * &n; * trick __pmd_alloc into optimising away. The actual value is irrelevant though as it&n; * is thrown away. It just cant be zero. -IM&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm,addr)&t;&t;({ BUG(); ((pmd_t *)2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(pmd)&t;&t;&t;do { } while (0)
DECL|macro|pgd_populate
mdefine_line|#define pgd_populate(mm,pmd,pte)&t;BUG()
r_extern
id|pgd_t
op_star
id|get_pgd_slow
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
id|free_pgd_slow
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
DECL|macro|pgd_alloc
mdefine_line|#define pgd_alloc(mm)&t;&t;&t;get_pgd_slow(mm)
DECL|macro|pgd_free
mdefine_line|#define pgd_free(pgd)&t;&t;&t;free_pgd_slow(pgd)
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;&t;do { } while (0)
macro_line|#endif
eof
