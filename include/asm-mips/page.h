multiline_comment|/* $Id: page.h,v 1.9 2000/02/24 00:13:19 ralf Exp $&n; *&n; * Definitions for page handling&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_PAGE_H
DECL|macro|__ASM_PAGE_H
mdefine_line|#define __ASM_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _LANGUAGE_ASSEMBLY
DECL|macro|BUG
mdefine_line|#define BUG() do { printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); *(int *)0=0; } while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do {  BUG(); } while (0)
r_extern
r_void
(paren
op_star
id|_clear_page
)paren
(paren
r_void
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_copy_page
)paren
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
suffix:semicolon
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;_clear_page(page)
DECL|macro|copy_page
mdefine_line|#define copy_page(to, from)&t;_copy_page(to, from)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr)&t;copy_page(to, from)
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
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pme
mdefine_line|#define __pme(x)&t;((pme_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
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
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/*&n; * This handles the memory map.&n; * We handle pages at KSEG0 for kernels with 32 bit address space.&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0x80000000UL
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;((unsigned long) (x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;((void *)((unsigned long) (x) + PAGE_OFFSET))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* defined (__KERNEL__) */
macro_line|#endif /* __ASM_PAGE_H */
eof
