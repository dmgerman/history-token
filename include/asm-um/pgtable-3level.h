multiline_comment|/*&n; * Copyright 2003 PathScale Inc&n; * Derived from include/asm-i386/pgtable.h&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PGTABLE_3LEVEL_H
DECL|macro|__UM_PGTABLE_3LEVEL_H
mdefine_line|#define __UM_PGTABLE_3LEVEL_H
macro_line|#include &lt;asm-generic/pgtable-nopud.h&gt;
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;30
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can&n; * map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;21
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/*&n; * entries per page directory level&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE 512
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD 512
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD ((TASK_SIZE + (PGDIR_SIZE - 1)) / PGDIR_SIZE)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD 512
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR       0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pte %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), &bslash;&n;&t;       pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pmd %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), &bslash;&n;&t;       pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pgd %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), &bslash;&n;&t;       pgd_val(e))
DECL|macro|pud_none
mdefine_line|#define pud_none(x)&t;(!(pud_val(x) &amp; ~_PAGE_NEWPAGE))
DECL|macro|pud_bad
mdefine_line|#define&t;pud_bad(x)&t;((pud_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pud_present
mdefine_line|#define pud_present(x)&t;(pud_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pud_populate
mdefine_line|#define pud_populate(mm, pud, pmd) &bslash;&n;&t;set_pud(pud, __pud(_PAGE_TABLE + __pa(pmd)))
DECL|macro|set_pud
mdefine_line|#define set_pud(pudptr, pudval) set_64bit((phys_t *) (pudptr), pud_val(pudval))
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PAGE_NEWPAGE
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_and_assign
op_complement
id|_PAGE_NEWPAGE
suffix:semicolon
)brace
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;pte_get_bits(x, (_PAGE_PRESENT | _PAGE_PROTNONE))
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
id|pte_set_bits
c_func
(paren
id|pte
comma
id|_PAGE_NEWPROT
)paren
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
id|pte_set_bits
c_func
(paren
id|pte
comma
id|_PAGE_NEWPAGE
)paren
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
id|pte_copy
c_func
(paren
op_star
id|pteptr
comma
id|pteval
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s a swap entry, it needs to be marked _PAGE_NEWPAGE so&n;&t; * fix_range knows to unmap it.  _PAGE_NEWPROT is specific to&n;&t; * mapped pages.&n;&t; */
op_star
id|pteptr
op_assign
id|pte_mknewpage
c_func
(paren
op_star
id|pteptr
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
mdefine_line|#define set_pmd(pmdptr, pmdval) set_64bit((phys_t *) (pmdptr), pmd_val(pmdval))
DECL|function|pmd_alloc_one
r_static
r_inline
id|pmd_t
op_star
id|pmd_alloc_one
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
id|pmd_t
op_star
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
)paren
(brace
id|memset
c_func
(paren
id|pmd
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_return
id|pmd
suffix:semicolon
)brace
DECL|function|pmd_free
r_static
r_inline
r_void
(def_block
id|pmd_free
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd
)paren
suffix:semicolon
)brace
)def_block
DECL|macro|__pmd_free_tlb
mdefine_line|#define __pmd_free_tlb(tlb,x)   do { } while (0)
DECL|function|pud_clear
r_static
r_inline
r_void
id|pud_clear
(paren
id|pud_t
op_star
id|pud
)paren
(brace
)brace
DECL|macro|pud_page
mdefine_line|#define pud_page(pud) &bslash;&n;&t;((struct page *) __va(pud_val(pud) &amp; PAGE_MASK))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(pud, address) ((pmd_t *) pud_page(*(pud)) + &bslash;&n;&t;&t;&t;pmd_index(address))
DECL|macro|pte_page
mdefine_line|#define pte_page(x) pfn_to_page(pte_pfn(x))
DECL|function|pte_none
r_static
r_inline
r_int
id|pte_none
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_is_zero
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_pfn
r_static
r_inline
r_int
r_int
id|pte_pfn
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|phys_to_pfn
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
)brace
DECL|function|pfn_pte
r_static
r_inline
id|pte_t
id|pfn_pte
c_func
(paren
id|pfn_t
id|page_nr
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|phys_t
id|phys
op_assign
id|pfn_to_phys
c_func
(paren
id|page_nr
)paren
suffix:semicolon
id|pte_set_val
c_func
(paren
id|pte
comma
id|phys
comma
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pfn_pmd
r_static
r_inline
id|pmd_t
id|pfn_pmd
c_func
(paren
id|pfn_t
id|page_nr
comma
id|pgprot_t
id|pgprot
)paren
(brace
r_return
id|__pmd
c_func
(paren
(paren
id|page_nr
op_lshift
id|PAGE_SHIFT
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bits 0 through 3 are taken in the low part of the pte,&n; * put the 32 bits of offset into the high part.&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;32
macro_line|#ifdef CONFIG_64_BIT
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(p) ((p).pte &gt;&gt; 32)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) ((pte_t) { ((off) &lt; 32) | _PAGE_FILE })
macro_line|#else
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) ((pte).pte_high)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) ((pte_t) { _PAGE_FILE, (off) })
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
