multiline_comment|/*&n; *  linux/include/asm-arm/pgalloc.h&n; *&n; *  Copyright (C) 2000-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGALLOC_H
DECL|macro|_ASMARM_PGALLOC_H
mdefine_line|#define _ASMARM_PGALLOC_H
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Since we have only two-level page tables, these are trivial&n; */
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
multiline_comment|/*&n; * Allocate one PTE table.&n; *&n; * This actually allocates two hardware PTE tables, but we wrap this up&n; * into one table thus:&n; *&n; *  +------------+&n; *  |  h/w pt 0  |&n; *  +------------+&n; *  |  h/w pt 1  |&n; *  +------------+&n; *  | Linux pt 0 |&n; *  +------------+&n; *  | Linux pt 1 |&n; *  +------------+&n; */
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
suffix:semicolon
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
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
id|clean_dcache_area
c_func
(paren
id|pte
comma
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
)paren
suffix:semicolon
id|pte
op_add_assign
id|PTRS_PER_PTE
suffix:semicolon
)brace
r_return
id|pte
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
r_struct
id|page
op_star
id|pte
suffix:semicolon
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
(brace
r_void
op_star
id|page
op_assign
id|page_address
c_func
(paren
id|pte
)paren
suffix:semicolon
id|clean_dcache_area
c_func
(paren
id|page
comma
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
)paren
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Free one PTE table.&n; */
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
r_if
c_cond
(paren
id|pte
)paren
(brace
id|pte
op_sub_assign
id|PTRS_PER_PTE
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
multiline_comment|/*&n; * Populate the pmdp entry with a pointer to the pte.  This pmd is part&n; * of the mm address space.&n; *&n; * Ensure that we always set both PMD entries.&n; */
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
r_int
r_int
id|pte_ptr
op_assign
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
r_int
r_int
id|pmdval
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mm
op_ne
op_amp
id|init_mm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The pmd must be loaded with the physical&n;&t; * address of the PTE table&n;&t; */
id|pte_ptr
op_sub_assign
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|pmdval
op_assign
id|__pa
c_func
(paren
id|pte_ptr
)paren
op_or
id|_PAGE_KERNEL_TABLE
suffix:semicolon
id|pmdp
(braket
l_int|0
)braket
op_assign
id|__pmd
c_func
(paren
id|pmdval
)paren
suffix:semicolon
id|pmdp
(braket
l_int|1
)braket
op_assign
id|__pmd
c_func
(paren
id|pmdval
op_plus
l_int|256
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|flush_pmd_entry
c_func
(paren
id|pmdp
)paren
suffix:semicolon
)brace
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
id|pmdp
comma
r_struct
id|page
op_star
id|ptep
)paren
(brace
r_int
r_int
id|pmdval
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mm
op_eq
op_amp
id|init_mm
)paren
suffix:semicolon
id|pmdval
op_assign
id|page_to_pfn
c_func
(paren
id|ptep
)paren
op_lshift
id|PAGE_SHIFT
op_or
id|_PAGE_USER_TABLE
suffix:semicolon
id|pmdp
(braket
l_int|0
)braket
op_assign
id|__pmd
c_func
(paren
id|pmdval
)paren
suffix:semicolon
id|pmdp
(braket
l_int|1
)braket
op_assign
id|__pmd
c_func
(paren
id|pmdval
op_plus
l_int|256
op_star
r_sizeof
(paren
id|pte_t
)paren
)paren
suffix:semicolon
id|flush_pmd_entry
c_func
(paren
id|pmdp
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
