multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Ralf Baechle&n; */
macro_line|#ifndef _ASM_PGTABLE_H
DECL|macro|_ASM_PGTABLE_H
mdefine_line|#define _ASM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MIPS32
macro_line|#include &lt;asm/pgtable-32.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
macro_line|#include &lt;asm/pgtable-64.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/pgtable-bits.h&gt;
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _CACHE_CACHABLE_NONCOHERENT)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | &bslash;&n;&t;&t;&t;_PAGE_GLOBAL | PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_USERIO
mdefine_line|#define PAGE_USERIO&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_KERNEL_UNCACHED
mdefine_line|#define PAGE_KERNEL_UNCACHED __pgprot(_PAGE_PRESENT | __READABLE | &bslash;&n;&t;&t;&t;__WRITEABLE | _PAGE_GLOBAL | _CACHE_UNCACHED)
multiline_comment|/*&n; * MIPS can&squot;t do page protection for execute, and considers that the same like&n; * read. Also, write permissions imply read permissions. This is the closest&n; * we can get by reasonable means..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero; used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
r_extern
r_int
r_int
id|zero_page_mask
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) &bslash;&n;&t;(virt_to_page(empty_zero_page + (((unsigned long)(vaddr)) &amp; zero_page_mask)))
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;page_pte_prot(page, __pgprot(0))
DECL|macro|pmd_phys
mdefine_line|#define pmd_phys(pmd)&t;&t;(pmd_val(pmd) - PAGE_OFFSET)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_phys(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;pmd_val(pmd)
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!(pte_val(pte) &amp; ~_PAGE_GLOBAL))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; _PAGE_PRESENT)
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32)
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
singleline_comment|//printk(&quot;pte_high %x pte_low %x&bslash;n&quot;, ptep-&gt;pte_high, ptep-&gt;pte_low);
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_GLOBAL
)paren
(brace
id|pte_t
op_star
id|buddy
op_assign
id|ptep_buddy
c_func
(paren
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make sure the buddy is global too (if it&squot;s !none,&n;&t;&t; * it better already be global)&n;&t;&t; */
r_if
c_cond
(paren
id|pte_none
c_func
(paren
op_star
id|buddy
)paren
)paren
id|buddy-&gt;pte_low
op_or_assign
id|_PAGE_GLOBAL
suffix:semicolon
)brace
)brace
DECL|function|pte_clear
r_static
r_inline
r_void
id|pte_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
multiline_comment|/* Preserve global status for the pair */
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|ptep_buddy
c_func
(paren
id|ptep
)paren
)paren
op_amp
id|_PAGE_GLOBAL
)paren
id|set_pte
c_func
(paren
id|ptep
comma
id|__pte
c_func
(paren
id|_PAGE_GLOBAL
)paren
)paren
suffix:semicolon
r_else
id|set_pte
c_func
(paren
id|ptep
comma
id|__pte
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
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
id|pteval
)paren
(brace
op_star
id|ptep
op_assign
id|pteval
suffix:semicolon
macro_line|#if !defined(CONFIG_CPU_R3000) &amp;&amp; !defined(CONFIG_CPU_TX39XX)
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pteval
)paren
op_amp
id|_PAGE_GLOBAL
)paren
(brace
id|pte_t
op_star
id|buddy
op_assign
id|ptep_buddy
c_func
(paren
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make sure the buddy is global too (if it&squot;s !none,&n;&t;&t; * it better already be global)&n;&t;&t; */
r_if
c_cond
(paren
id|pte_none
c_func
(paren
op_star
id|buddy
)paren
)paren
id|pte_val
c_func
(paren
op_star
id|buddy
)paren
op_assign
id|pte_val
c_func
(paren
op_star
id|buddy
)paren
op_or
id|_PAGE_GLOBAL
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|pte_clear
r_static
r_inline
r_void
id|pte_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#if !defined(CONFIG_CPU_R3000) &amp;&amp; !defined(CONFIG_CPU_TX39XX)
multiline_comment|/* Preserve global status for the pair */
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|ptep_buddy
c_func
(paren
id|ptep
)paren
)paren
op_amp
id|_PAGE_GLOBAL
)paren
id|set_pte
c_func
(paren
id|ptep
comma
id|__pte
c_func
(paren
id|_PAGE_GLOBAL
)paren
)paren
suffix:semicolon
r_else
macro_line|#endif
id|set_pte
c_func
(paren
id|ptep
comma
id|__pte
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) do { *(pmdptr) = (pmdval); } while(0)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) do { *(pgdptr) = (pgdval); } while(0)
DECL|macro|PGD_T_LOG2
mdefine_line|#define PGD_T_LOG2&t;ffz(~sizeof(pgd_t))
DECL|macro|PMD_T_LOG2
mdefine_line|#define PMD_T_LOG2&t;ffz(~sizeof(pmd_t))
DECL|macro|PTE_T_LOG2
mdefine_line|#define PTE_T_LOG2&t;ffz(~sizeof(pte_t))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_user
r_static
r_inline
r_int
id|pte_user
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32)
DECL|function|pte_read
r_static
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_READ
suffix:semicolon
)brace
DECL|function|pte_write
r_static
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_WRITE
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_MODIFIED
suffix:semicolon
)brace
DECL|function|pte_young
r_static
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_file
r_static
r_inline
r_int
id|pte_file
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_static
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
(paren
id|_PAGE_WRITE
op_or
id|_PAGE_SILENT_WRITE
)paren
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_and_assign
op_complement
id|_PAGE_SILENT_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_static
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
(paren
id|_PAGE_READ
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_and_assign
op_complement
id|_PAGE_SILENT_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
(paren
id|_PAGE_MODIFIED
op_or
id|_PAGE_SILENT_WRITE
)paren
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_and_assign
op_complement
id|_PAGE_SILENT_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_static
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
(paren
id|_PAGE_ACCESSED
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_and_assign
op_complement
id|_PAGE_SILENT_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_static
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_WRITE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_MODIFIED
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_static
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_READ
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_ACCESSED
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_MODIFIED
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_WRITE
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_static
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_READ
)paren
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
(paren
id|pte
)paren
dot
id|pte_high
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
macro_line|#else
DECL|function|pte_read
r_static
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
suffix:semicolon
)brace
DECL|function|pte_write
r_static
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_WRITE
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_MODIFIED
suffix:semicolon
)brace
DECL|function|pte_young
r_static
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_file
r_static
r_inline
r_int
id|pte_file
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_static
r_inline
id|pte_t
id|pte_wrprotect
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
op_and_assign
op_complement
(paren
id|_PAGE_WRITE
op_or
id|_PAGE_SILENT_WRITE
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_static
r_inline
id|pte_t
id|pte_rdprotect
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
op_and_assign
op_complement
(paren
id|_PAGE_READ
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
r_inline
id|pte_t
id|pte_mkclean
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
op_and_assign
op_complement
(paren
id|_PAGE_MODIFIED
op_or
id|_PAGE_SILENT_WRITE
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_static
r_inline
id|pte_t
id|pte_mkold
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
op_and_assign
op_complement
(paren
id|_PAGE_ACCESSED
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_static
r_inline
id|pte_t
id|pte_mkwrite
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
id|_PAGE_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_MODIFIED
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_static
r_inline
id|pte_t
id|pte_mkread
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
id|_PAGE_READ
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
r_inline
id|pte_t
id|pte_mkdirty
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
id|_PAGE_MODIFIED
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_WRITE
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_static
r_inline
id|pte_t
id|pte_mkyoung
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
id|_PAGE_ACCESSED
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Macro to make mark a page protection value as &quot;uncacheable&quot;.  Note&n; * that &quot;protection&quot; is really a misnomer here as the protection value&n; * contains the memory attribute bits, dirty bits, and various other&n; * bits as well.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached pgprot_noncached
DECL|function|pgprot_noncached
r_static
r_inline
id|pgprot_t
id|pgprot_noncached
c_func
(paren
id|pgprot_t
id|_prot
)paren
(brace
r_int
r_int
id|prot
op_assign
id|pgprot_val
c_func
(paren
id|_prot
)paren
suffix:semicolon
id|prot
op_assign
(paren
id|prot
op_amp
op_complement
id|_CACHE_MASK
)paren
op_or
id|_CACHE_UNCACHED
suffix:semicolon
r_return
id|__pgprot
c_func
(paren
id|prot
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32)
DECL|function|pte_modify
r_static
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte.pte_low
op_and_assign
id|_PAGE_CHG_MASK
suffix:semicolon
id|pte.pte_low
op_or_assign
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
id|pte.pte_high
op_or_assign
id|pgprot_val
c_func
(paren
id|newprot
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
macro_line|#else
DECL|function|pte_modify
r_static
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
r_return
id|__pte
c_func
(paren
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_void
id|__update_tlb
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
suffix:semicolon
r_extern
r_void
id|__update_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
suffix:semicolon
DECL|function|update_mmu_cache
r_static
r_inline
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
id|__update_tlb
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
suffix:semicolon
id|__update_cache
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
macro_line|#endif
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
r_extern
id|phys_t
id|fixup_bigphys_addr
c_func
(paren
id|phys_t
id|phys_addr
comma
id|phys_t
id|size
)paren
suffix:semicolon
r_extern
r_int
id|remap_pfn_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|pfn
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
DECL|function|io_remap_page_range
r_static
r_inline
r_int
id|io_remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
(brace
id|phys_t
id|phys_addr_high
op_assign
id|fixup_bigphys_addr
c_func
(paren
id|paddr
comma
id|size
)paren
suffix:semicolon
r_return
id|remap_pfn_range
c_func
(paren
id|vma
comma
id|vaddr
comma
id|phys_addr_high
op_rshift
id|PAGE_SHIFT
comma
id|size
comma
id|prot
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
macro_line|#endif
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * We provide our own get_unmapped area to cope with the virtual aliasing&n; * constraints placed on us by the cache architecture.&n; */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* _ASM_PGTABLE_H */
eof
