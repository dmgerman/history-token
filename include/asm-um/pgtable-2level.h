multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Copyright 2003 PathScale, Inc.&n; * Derived from include/asm-i386/pgtable.h&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PGTABLE_2LEVEL_H
DECL|macro|__UM_PGTABLE_2LEVEL_H
mdefine_line|#define __UM_PGTABLE_2LEVEL_H
macro_line|#include &lt;asm-generic/pgtable-nopmd.h&gt;
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the i386 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD ((TASK_SIZE + (PGDIR_SIZE - 1)) / PGDIR_SIZE)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR       0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pte %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), &bslash;&n;&t;       pte_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pgd %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), &bslash;&n;&t;       pgd_val(e))
DECL|function|pgd_newpage
r_static
r_inline
r_int
id|pgd_newpage
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
DECL|function|pgd_mkuptodate
r_static
r_inline
r_void
id|pgd_mkuptodate
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
)brace
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|function|pte_mknewprot
r_static
r_inline
id|pte_t
id|pte_mknewprot
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NEWPROT
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mknewpage
r_static
r_inline
id|pte_t
id|pte_mknewpage
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_NEWPAGE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|set_pte
r_static
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
(brace
multiline_comment|/* If it&squot;s a swap entry, it needs to be marked _PAGE_NEWPAGE so&n;&t; * fix_range knows to unmap it.  _PAGE_NEWPROT is specific to&n;&t; * mapped pages.&n;&t; */
op_star
id|pteptr
op_assign
id|pte_mknewpage
c_func
(paren
id|pteval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pteptr
)paren
)paren
(brace
op_star
id|pteptr
op_assign
id|pte_mknewprot
c_func
(paren
op_star
id|pteptr
)paren
suffix:semicolon
)brace
)brace
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))
DECL|macro|pte_page
mdefine_line|#define pte_page(x) pfn_to_page(pte_pfn(x))
DECL|macro|pte_none
mdefine_line|#define pte_none(x) !(pte_val(x) &amp; ~_PAGE_NEWPAGE)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x) phys_to_pfn(pte_val(x))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot) __pte(pfn_to_phys(pfn) | pgprot_val(prot))
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(pfn, prot) __pmd(pfn_to_phys(pfn) | pgprot_val(prot))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) &bslash;&n;&t;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/*&n; * Bits 0 through 3 are taken&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;28
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) (pte_val(pte) &gt;&gt; 4)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) ((pte_t) { ((off) &lt;&lt; 4) + _PAGE_FILE })
macro_line|#endif
eof
