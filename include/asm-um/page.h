multiline_comment|/*&n; * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Copyright 2003 PathScale, Inc.&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PAGE_H
DECL|macro|__UM_PAGE_H
mdefine_line|#define __UM_PAGE_H
r_struct
id|page
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/vm-flags.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg)&t;copy_page(to, from)
macro_line|#if defined(CONFIG_3_LEVEL_PGTABLES) &amp;&amp; !defined(CONFIG_64_BIT)
DECL|member|pte_low
DECL|member|pte_high
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte_low
comma
id|pte_high
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x) ((x).pte_low | ((unsigned long long) (x).pte_high &lt;&lt; 32))
DECL|macro|pte_get_bits
mdefine_line|#define pte_get_bits(pte, bits) ((pte).pte_low &amp; (bits))
DECL|macro|pte_set_bits
mdefine_line|#define pte_set_bits(pte, bits) ((pte).pte_low |= (bits))
DECL|macro|pte_clear_bits
mdefine_line|#define pte_clear_bits(pte, bits) ((pte).pte_low &amp;= ~(bits))
DECL|macro|pte_copy
mdefine_line|#define pte_copy(to, from) ({ (to).pte_high = (from).pte_high; &bslash;&n;&t;&t;&t;      smp_wmb(); &bslash;&n;&t;&t;&t;      (to).pte_low = (from).pte_low; })
DECL|macro|pte_is_zero
mdefine_line|#define pte_is_zero(pte) (!((pte).pte_low &amp; ~_PAGE_NEWPAGE) &amp;&amp; !(pte).pte_high)
DECL|macro|pte_set_val
mdefine_line|#define pte_set_val(pte, phys, prot) &bslash;&n;&t;({ (pte).pte_high = (phys) &gt;&gt; 32; &bslash;&n;&t;   (pte).pte_low = (phys) | pgprot_val(prot); })
DECL|typedef|pfn_t
r_typedef
r_int
r_int
r_int
id|pfn_t
suffix:semicolon
DECL|typedef|phys_t
r_typedef
r_int
r_int
r_int
id|phys_t
suffix:semicolon
macro_line|#else
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
macro_line|#ifdef CONFIG_3_LEVEL_PGTABLES
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
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|__pmd
mdefine_line|#define __pmd(x) ((pmd_t) { (x) } )
macro_line|#endif
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pte_get_bits
mdefine_line|#define pte_get_bits(p, bits) ((p).pte &amp; (bits))
DECL|macro|pte_set_bits
mdefine_line|#define pte_set_bits(p, bits) ((p).pte |= (bits))
DECL|macro|pte_clear_bits
mdefine_line|#define pte_clear_bits(p, bits) ((p).pte &amp;= ~(bits))
DECL|macro|pte_copy
mdefine_line|#define pte_copy(to, from) ((to).pte = (from).pte)
DECL|macro|pte_is_zero
mdefine_line|#define pte_is_zero(p) (!((p).pte &amp; ~_PAGE_NEWPAGE))
DECL|macro|pte_set_val
mdefine_line|#define pte_set_val(p, phys, prot) (p).pte = (phys | pgprot_val(prot))
DECL|typedef|pfn_t
r_typedef
r_int
r_int
id|pfn_t
suffix:semicolon
DECL|typedef|phys_t
r_typedef
r_int
r_int
id|phys_t
suffix:semicolon
macro_line|#endif
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
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x) ((pte_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x) ((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
r_extern
r_int
r_int
id|uml_physmem
suffix:semicolon
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET (uml_physmem)
DECL|macro|KERNELBASE
mdefine_line|#define KERNELBASE PAGE_OFFSET
DECL|macro|__va_space
mdefine_line|#define __va_space (8*1024*1024)
r_extern
r_int
r_int
id|to_phys
c_func
(paren
r_void
op_star
id|virt
)paren
suffix:semicolon
r_extern
r_void
op_star
id|to_virt
c_func
(paren
r_int
r_int
id|phys
)paren
suffix:semicolon
DECL|macro|__pa
mdefine_line|#define __pa(virt) to_phys((void *) virt)
DECL|macro|__va
mdefine_line|#define __va(phys) to_virt((unsigned long) phys)
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page) ((page) - mem_map)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn) (mem_map + (pfn))
DECL|macro|phys_to_pfn
mdefine_line|#define phys_to_pfn(p) ((p) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_phys
mdefine_line|#define pfn_to_phys(pfn) ((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn) ((pfn) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(v) pfn_valid(phys_to_pfn(__pa(v)))
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_static
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
r_extern
r_struct
id|page
op_star
id|arch_validate
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|mask
comma
r_int
id|order
)paren
suffix:semicolon
DECL|macro|HAVE_ARCH_VALIDATE
mdefine_line|#define HAVE_ARCH_VALIDATE
r_extern
r_void
id|arch_free_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|order
)paren
suffix:semicolon
DECL|macro|HAVE_ARCH_FREE_PAGE
mdefine_line|#define HAVE_ARCH_FREE_PAGE
macro_line|#endif
eof
