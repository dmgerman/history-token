macro_line|#ifndef _I386_PGTABLE_3LEVEL_H
DECL|macro|_I386_PGTABLE_3LEVEL_H
mdefine_line|#define _I386_PGTABLE_3LEVEL_H
multiline_comment|/*&n; * Intel Physical Address Extension (PAE) Mode - three-level page&n; * tables on PPro+ CPUs.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
multiline_comment|/*&n; * PGDIR_SHIFT determines what a top-level page table entry can map&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;30
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;4
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a middle-level&n; * page table can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;21
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;512
multiline_comment|/*&n; * entries per page directory level&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;512
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %p(%08lx%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), (e).pte_high, (e).pte_low)
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %p(%016Lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %p(%016Lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pgd_val(e))
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
multiline_comment|/* Rules for using set_pte: the pte being assigned *must* be&n; * either not present or in a state where the hardware will&n; * not attempt to update the pte.  In places where this is&n; * not possible, use pte_get_and_clear to obtain the old pte&n; * value and then use set_pte to update it.  -ben&n; */
DECL|function|set_pte
r_static
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
(brace
id|ptep-&gt;pte_high
op_assign
id|pte.pte_high
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
id|ptep-&gt;pte_low
op_assign
id|pte.pte_low
suffix:semicolon
)brace
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr,pmdval) &bslash;&n;&t;&t;set_64bit((unsigned long long *)(pmdptr),pmd_val(pmdval))
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr,pgdval) &bslash;&n;&t;&t;set_64bit((unsigned long long *)(pgdptr),pgd_val(pgdval))
multiline_comment|/*&n; * Pentium-II erratum A13: in PAE mode we explicitly have to flush&n; * the TLB via cr3 if the top-level pgd is changed...&n; * We do not let the generic code free and clear pgd entries due to&n; * this erratum.&n; */
DECL|function|pgd_clear
r_static
r_inline
r_void
id|pgd_clear
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
)brace
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) &bslash;&n;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *) pgd_page(*(dir)) + &bslash;&n;&t;&t;&t;__pmd_offset(address))
DECL|function|ptep_get_and_clear
r_static
r_inline
id|pte_t
id|ptep_get_and_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_t
id|res
suffix:semicolon
multiline_comment|/* xchg acts as a barrier before the setting of the high bits */
id|res.pte_low
op_assign
id|xchg
c_func
(paren
op_amp
id|ptep-&gt;pte_low
comma
l_int|0
)paren
suffix:semicolon
id|res.pte_high
op_assign
id|ptep-&gt;pte_high
suffix:semicolon
id|ptep-&gt;pte_high
op_assign
l_int|0
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|pte_same
r_static
r_inline
r_int
id|pte_same
c_func
(paren
id|pte_t
id|a
comma
id|pte_t
id|b
)paren
(brace
r_return
id|a.pte_low
op_eq
id|b.pte_low
op_logical_and
id|a.pte_high
op_eq
id|b.pte_high
suffix:semicolon
)brace
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;(mem_map+(((x).pte_low &gt;&gt; PAGE_SHIFT) | ((x).pte_high &lt;&lt; (32 - PAGE_SHIFT))))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!(x).pte_low &amp;&amp; !(x).pte_high)
DECL|function|__mk_pte
r_static
r_inline
id|pte_t
id|__mk_pte
c_func
(paren
r_int
r_int
id|page_nr
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte.pte_high
op_assign
id|page_nr
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|pte.pte_low
op_assign
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
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
macro_line|#endif /* _I386_PGTABLE_3LEVEL_H */
eof
