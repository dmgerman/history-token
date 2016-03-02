macro_line|#ifndef __ASM_SH64_PAGE_H
DECL|macro|__ASM_SH64_PAGE_H
mdefine_line|#define __ASM_SH64_PAGE_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/page.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * benedict.gaster@superh.com 19th, 24th July 2002.&n; *&n; * Modified to take account of enabling for D-CACHE support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
macro_line|#ifdef __ASSEMBLY__
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;4096
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|PTE_MASK
mdefine_line|#define PTE_MASK&t;PAGE_MASK
macro_line|#if defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
DECL|macro|HPAGE_SHIFT
mdefine_line|#define HPAGE_SHIFT&t;16
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
DECL|macro|HPAGE_SHIFT
mdefine_line|#define HPAGE_SHIFT&t;20
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_512MB)
DECL|macro|HPAGE_SHIFT
mdefine_line|#define HPAGE_SHIFT&t;29
macro_line|#endif
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|HPAGE_SIZE
mdefine_line|#define HPAGE_SIZE&t;&t;(1UL &lt;&lt; HPAGE_SHIFT)
DECL|macro|HPAGE_MASK
mdefine_line|#define HPAGE_MASK&t;&t;(~(HPAGE_SIZE-1))
DECL|macro|HUGETLB_PAGE_ORDER
mdefine_line|#define HUGETLB_PAGE_ORDER&t;(HPAGE_SHIFT-PAGE_SHIFT)
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_struct
id|page
op_star
id|mem_map
suffix:semicolon
r_extern
r_void
id|sh64_page_clear
c_func
(paren
r_void
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|sh64_page_copy
c_func
(paren
r_void
op_star
id|from
comma
r_void
op_star
id|to
)paren
suffix:semicolon
DECL|macro|clear_page
mdefine_line|#define clear_page(page)               sh64_page_clear(page)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)             sh64_page_copy(from, to)
macro_line|#if defined(CONFIG_DCACHE_DISABLED)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg)&t;copy_page(to, from)
macro_line|#else
r_extern
r_void
id|clear_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|address
comma
r_struct
id|page
op_star
id|pg
)paren
suffix:semicolon
r_extern
r_void
id|copy_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
r_int
id|address
comma
r_struct
id|page
op_star
id|pg
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_DCACHE_DISABLED) */
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x) ((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x) ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x) ((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/*&n; * Kconfig defined.&n; */
DECL|macro|__MEMORY_START
mdefine_line|#define __MEMORY_START&t;&t;(CONFIG_MEMORY_START)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(CONFIG_CACHED_MEMORY_OFFSET)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;((__pa(addr)-__MEMORY_START) &gt;&gt; PAGE_SHIFT)
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
DECL|macro|phys_to_page
mdefine_line|#define phys_to_page(phys)&t;(mem_map + (((phys) - __MEMORY_START) &gt;&gt; PAGE_SHIFT))
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(((page - mem_map) &lt;&lt; PAGE_SHIFT) + __MEMORY_START)
multiline_comment|/* PFN start number, because of __MEMORY_START */
DECL|macro|PFN_START
mdefine_line|#define PFN_START&t;&t;(__MEMORY_START &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + (pfn) - PFN_START)
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)((page) - mem_map) + PFN_START)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(((pfn) - PFN_START) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_extern
id|__inline__
r_int
id|get_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
id|size
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
suffix:semicolon
id|order
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|order
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH64_PAGE_H */
eof
