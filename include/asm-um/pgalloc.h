multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Copyright 2003 PathScale, Inc.&n; * Derived from include/asm-i386/pgalloc.h and include/asm-i386/pgtable.h&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PGALLOC_H
DECL|macro|__UM_PGALLOC_H
mdefine_line|#define __UM_PGALLOC_H
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;asm/fixmap.h&quot;
DECL|macro|pmd_populate_kernel
mdefine_line|#define pmd_populate_kernel(mm, pmd, pte) &bslash;&n;&t;set_pmd(pmd, __pmd(_PAGE_TABLE + (unsigned long) __pa(pte)))
DECL|macro|pmd_populate
mdefine_line|#define pmd_populate(mm, pmd, pte) &t;&t;&t;&t;&bslash;&n;&t;set_pmd(pmd, __pmd(_PAGE_TABLE +&t;&t;&t;&bslash;&n;&t;&t;((unsigned long long)page_to_pfn(pte) &lt;&lt;&t;&bslash;&n;&t;&t;&t;(unsigned long long) PAGE_SHIFT)))
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
DECL|macro|__pte_free_tlb
mdefine_line|#define __pte_free_tlb(tlb,pte) tlb_remove_page((tlb),(pte))
macro_line|#ifdef CONFIG_3_LEVEL_PGTABLES
multiline_comment|/*&n; * In the 3-level case we free the pmds as part of the pgd.&n; */
DECL|macro|pmd_free
mdefine_line|#define pmd_free(x)&t;&t;&t;do { } while (0)
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb,x)&t;&t;do { } while (0)
macro_line|#endif
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
