multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 2001 by Ralf Baechle at alii&n; * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PGTABLE_H
DECL|macro|_ASM_PGTABLE_H
mdefine_line|#define _ASM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty&t;&t;&t;PG_arch_1
DECL|macro|Page_dcache_dirty
mdefine_line|#define Page_dcache_dirty(page)&t;&t;&bslash;&n;&t;test_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
DECL|macro|SetPageDcacheDirty
mdefine_line|#define SetPageDcacheDirty(page)&t;&bslash;&n;&t;set_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
DECL|macro|ClearPageDcacheDirty
mdefine_line|#define ClearPageDcacheDirty(page)&t;&bslash;&n;&t;clear_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
multiline_comment|/*&n; * Each address space has 2 4K pages as its page directory, giving 1024&n; * (== PTRS_PER_PGD) 8 byte pointers to pmd tables. Each pmd table is a&n; * pair of 4K pages, giving 1024 (== PTRS_PER_PMD) 8 byte pointers to&n; * page tables. Each page table is a single 4K page, giving 512 (==&n; * PTRS_PER_PTE) 8 byte ptes. Each pgde is initialized to point to&n; * invalid_pmd_table, each pmde is initialized to point to&n; * invalid_pte_table, each pte is initialized to 0. When memory is low,&n; * and a pmd table or a page table allocation fails, empty_bad_pmd_table&n; * and empty_bad_page_table is returned back to higher layer code, so&n; * that the failure is recognized later on. Linux does not seem to&n; * handle these failures very well though. The empty_bad_page_table has&n; * invalid pte entries in it, to force page faults.&n; * Vmalloc handling: vmalloc uses swapper_pg_dir[0] (returned by&n; * pgd_offset_k), which is initalized to point to kpmdtbl. kpmdtbl is&n; * the only single page pmd in the system. kpmdtbl entries point into&n; * kptbl[] array. We reserve 1 &lt;&lt; PGD_ORDER pages to hold the&n; * vmalloc range translations, which the fault handler looks at.&n; */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT - 3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PMD_SHIFT + (PAGE_SHIFT + 1 - 3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/* Entries per page directory level: we use two-level, so we don&squot;t really&n;   have any PMD directory physically.  */
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1024
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;512
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;&t;1
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;&t;1
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;&t;0
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;XKSEG
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&bslash;&n;&t;(VMALLOC_START + ((1 &lt;&lt; PGD_ORDER) * PTRS_PER_PTE * PAGE_SIZE))
macro_line|#include &lt;asm/pgtable-bits.h&gt;
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _CACHE_CACHABLE_NONCOHERENT)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | &bslash;&n;&t;&t;&t;_PAGE_GLOBAL | PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_USERIO
mdefine_line|#define PAGE_USERIO     __pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
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
macro_line|#ifndef __ASSEMBLY__
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
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
id|pte_t
id|invalid_pte_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pte_t
)paren
)braket
suffix:semicolon
r_extern
id|pte_t
id|empty_bad_page_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pte_t
)paren
)braket
suffix:semicolon
r_extern
id|pmd_t
id|invalid_pmd_table
(braket
l_int|2
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
suffix:semicolon
r_extern
id|pmd_t
id|empty_bad_pmd_table
(braket
l_int|2
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
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
DECL|function|pgd_page
r_static
r_inline
r_int
r_int
id|pgd_page
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
suffix:semicolon
)brace
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
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_GLOBAL
)paren
suffix:semicolon
)brace
DECL|function|pte_present
r_static
r_inline
r_int
id|pte_present
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
id|_PAGE_PRESENT
suffix:semicolon
)brace
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
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) do { *(pmdptr) = (pmdval); } while(0)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) do { *(pgdptr) = (pgdval); } while(0)
multiline_comment|/*&n; * Empty pmd entries point to the invalid_pte_table.&n; */
DECL|function|pmd_none
r_static
r_inline
r_int
id|pmd_none
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_eq
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp;~ PAGE_MASK)
DECL|function|pmd_present
r_static
r_inline
r_int
id|pmd_present
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_ne
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
DECL|function|pmd_clear
r_static
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
(paren
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Empty pgd entries point to the invalid_pmd_table.&n; */
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_eq
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
)brace
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(pgd_val(pgd) &amp;~ PAGE_MASK)
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_ne
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
)brace
DECL|function|pgd_clear
r_static
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
(paren
(paren
r_int
r_int
)paren
id|invalid_pmd_table
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (NODE_MEM_MAP(PHYSADDR_TO_NID(pte_val(x))) +&t;&bslash;&n;&t;PLAT_NODE_DATA_LOCALNR(pte_val(x), PHYSADDR_TO_NID(pte_val(x))))
macro_line|#else
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map+(unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)((x).pte &gt;&gt; PAGE_SHIFT))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
macro_line|#endif
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS       27
macro_line|#if defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
multiline_comment|/*&n; * Bits 0, 1, 2, 9 and 10 are taken, split up the 27 bits of offset&n; * into this range:&n; */
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) &bslash;&n;&t;((((_pte).pte &gt;&gt; 3) &amp; 0x3f ) + (((_pte).pte &gt;&gt; 11) &lt;&lt; 8 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x3f) &lt;&lt; 3) + (((off) &gt;&gt; 8) &lt;&lt; 11) + _PAGE_FILE })
macro_line|#else
multiline_comment|/*&n; * Bits 0, 1, 2, 7 and 8 are taken, split up the 27 bits of offset&n; * into this range:&n; */
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) &bslash;&n;&t;((((_pte).pte &gt;&gt; 3) &amp; 0x1f ) + (((_pte).pte &gt;&gt; 9) &lt;&lt; 6 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x1f) &lt;&lt; 3) + (((off) &gt;&gt; 6) &lt;&lt; 9) + _PAGE_FILE })
macro_line|#endif
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
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, 0)
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;&t;((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm,addr)&t;((mm)-&gt;pgd + pgd_index(addr))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|pgd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *) (pmd_page_kernel(*dir)) + __pte_offset(address))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address)&t;&t;&t;&t;&bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) ((void)(pte))
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) ((void)(pte))
multiline_comment|/*&n; * Initialize a new pgd / pmd table with invalid pointers.&n; */
r_extern
r_void
id|pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|pmd_init
c_func
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|pagetable
)paren
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Non-present pages:  high 24 bits are offset, next 8 bits type,&n; * low 32 bits zero.&n; */
DECL|function|mk_swap_pte
r_static
r_inline
id|pte_t
id|mk_swap_pte
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|offset
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|type
op_lshift
l_int|32
)paren
op_or
(paren
id|offset
op_lshift
l_int|40
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 32) &amp; 0xff)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 40)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
macro_line|#endif
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#include &lt;asm-generic/pgtable.h&gt;
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
multiline_comment|/*&n; * We provide our own get_unmapped area to cope with the virtual aliasing&n; * constraints placed on us by the cache architecture.&n; */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_PGTABLE_H */
eof
