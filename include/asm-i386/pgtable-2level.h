macro_line|#ifndef _I386_PGTABLE_2LEVEL_H
DECL|macro|_I386_PGTABLE_2LEVEL_H
mdefine_line|#define _I386_PGTABLE_2LEVEL_H
macro_line|#include &lt;asm-generic/pgtable-nopmd.h&gt;
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, (e).pte_low)
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) (*(pteptr) = pteval)
DECL|macro|set_pte_atomic
mdefine_line|#define set_pte_atomic(pteptr, pteval) set_pte(pteptr,pteval)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))
DECL|macro|ptep_get_and_clear
mdefine_line|#define ptep_get_and_clear(xp)&t;__pte(xchg(&amp;(xp)-&gt;pte_low, 0))
DECL|macro|pte_same
mdefine_line|#define pte_same(a, b)&t;&t;((a).pte_low == (b).pte_low)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;&t;(!(x).pte_low)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)(((x).pte_low &gt;&gt; PAGE_SHIFT)))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(pfn, prot)&t;__pmd(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) (pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) &bslash;&n;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/*&n; * All present user pages are user-executable:&n; */
DECL|function|pte_exec
r_static
r_inline
r_int
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_user
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * All present pages are kernel-executable:&n; */
DECL|function|pte_exec_kernel
r_static
r_inline
r_int
id|pte_exec_kernel
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Bits 0, 6 and 7 are taken, split up the 29 bits of offset&n; * into this range:&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;29
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) &bslash;&n;&t;((((pte).pte_low &gt;&gt; 1) &amp; 0x1f ) + (((pte).pte_low &gt;&gt; 8) &lt;&lt; 5 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x1f) &lt;&lt; 1) + (((off) &gt;&gt; 5) &lt;&lt; 8) + _PAGE_FILE })
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { (pte).pte_low })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* _I386_PGTABLE_2LEVEL_H */
eof
