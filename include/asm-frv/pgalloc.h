multiline_comment|/* pgalloc.h: Page allocation routines for FRV&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Derived from:&n; *&t;include/asm-m68knommu/pgalloc.h&n; *&t;include/asm-i386/pgalloc.h&n; */
macro_line|#ifndef _ASM_PGALLOC_H
DECL|macro|_ASM_PGALLOC_H
mdefine_line|#define _ASM_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#ifdef CONFIG_MMU
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(mm, pmd, pte) __set_pmd(pmd, __pa(pte) | _PAGE_TABLE)
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(MM, PMD, PAGE)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__set_pmd((PMD), page_to_pfn(PAGE) &lt;&lt; PAGE_SHIFT | _PAGE_TABLE);&t;&bslash;&n;} while(0)
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
DECL|macro|__pte_free_tlb
mdefine_line|#define __pte_free_tlb(tlb,pte)&t;&t;tlb_remove_page((tlb),(pte))
multiline_comment|/*&n; * allocating and freeing a pmd is trivial: the 1-entry pmd is&n; * inside the pgd, so has no extra memory associated with it.&n; * (In the PAE case we free the pmds as part of the pgd.)&n; */
DECL|macro|pmd_alloc_one
mdefine_line|#define pmd_alloc_one(mm, addr)&t;&t;({ BUG(); ((pmd_t *) 2); })
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb,x)&t;&t;do { } while (0)
macro_line|#endif /* CONFIG_MMU */
macro_line|#endif /* _ASM_PGALLOC_H */
eof
