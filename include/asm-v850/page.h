multiline_comment|/*&n; * include/asm-v850/page.h -- VM ops&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_PAGE_H__
DECL|macro|__V850_PAGE_H__
mdefine_line|#define __V850_PAGE_H__
macro_line|#include &lt;asm/machdep.h&gt;
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE       (1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK       (~(PAGE_SIZE-1))
multiline_comment|/*&n; * PAGE_OFFSET -- the first address of the first page of memory. For archs with&n; * no MMU this corresponds to the first free page in physical memory (aligned&n; * on a page boundary).&n; */
macro_line|#ifndef PAGE_OFFSET
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET  0x0000000
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset ((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to, from)&t;memcpy ((void *)(to), (void *)from, PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(addr, vaddr, page)&t;&bslash;&n;&t;do { &t;clear_page(addr);&t;&t;&bslash;&n;&t;&t;flush_dcache_page(page);&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, page)&t;&bslash;&n;&t;do {&t;copy_page(to, from);&t;&t;&bslash;&n;&t;&t;flush_dcache_page(page);&t;&bslash;&n;&t;} while (0)
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
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
mdefine_line|#define pte_val(x)      ((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      ((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   ((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)        ((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)        ((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     ((pgprot_t) { (x) } )
macro_line|#else /* !STRICT_MM_TYPECHECKS */
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)      (x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      (x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      (x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   (x)
DECL|macro|__pte
mdefine_line|#define __pte(x)        (x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)        (x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     (x)
macro_line|#endif /* STRICT_MM_TYPECHECKS */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_extern
id|__inline__
r_int
id|get_order
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
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* No current v850 processor has virtual memory.  */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(addr)&t;(addr)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(addr)&t;(addr)
DECL|macro|virt_to_pfn
mdefine_line|#define virt_to_pfn(kaddr)&t;(__virt_to_phys (kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_virt
mdefine_line|#define pfn_to_virt(pfn)&t;__phys_to_virt ((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(kaddr) &bslash;&n;  (((unsigned long)(kaddr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + MAP_NR (kaddr))
DECL|macro|page_to_virt
mdefine_line|#define page_to_virt(page) &bslash;&n;  ((((page) - mem_map) &lt;&lt; PAGE_SHIFT) + PAGE_OFFSET)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;virt_to_page (pfn_to_virt (pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;virt_to_pfn (page_to_virt (page))
DECL|macro|virt_addr_valid
mdefine_line|#define&t;virt_addr_valid(kaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;  (((void *)(kaddr) &gt;= (void *)PAGE_OFFSET) &amp;&amp; MAP_NR (kaddr) &lt; max_mapnr)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;     __virt_to_phys ((unsigned long)(x))
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;     ((void *)__phys_to_virt ((unsigned long)(x)))
macro_line|#endif /* KERNEL */
macro_line|#endif /* __V850_PAGE_H__ */
eof
