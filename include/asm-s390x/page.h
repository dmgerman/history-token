multiline_comment|/*&n; *  include/asm-s390/page.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hpenner@de.ibm.com)&n; */
macro_line|#ifndef _S390_PAGE_H
DECL|macro|_S390_PAGE_H
mdefine_line|#define _S390_PAGE_H
macro_line|#include &lt;asm/setup.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT      12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE       (1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK       (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|function|clear_page
r_static
r_inline
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;   lgr  2,%0&bslash;n&quot;
l_string|&quot;   lghi 3,4096&bslash;n&quot;
l_string|&quot;   slgr 1,1&bslash;n&quot;
l_string|&quot;   mvcl 2,0&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
(paren
r_void
op_star
)paren
(paren
id|page
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
)brace
DECL|function|copy_page
r_static
r_inline
r_void
id|copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
id|MACHINE_HAS_MVPG
)paren
id|asm
r_volatile
(paren
l_string|&quot;   sgr  0,0&bslash;n&quot;
l_string|&quot;   mvpg %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
(paren
r_void
op_star
)paren
(paren
id|to
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
(paren
r_void
op_star
)paren
(paren
id|from
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_else
id|asm
r_volatile
(paren
l_string|&quot;   mvc  0(256,%0),0(%1)&bslash;n&quot;
l_string|&quot;   mvc  256(256,%0),256(%1)&bslash;n&quot;
l_string|&quot;   mvc  512(256,%0),512(%1)&bslash;n&quot;
l_string|&quot;   mvc  768(256,%0),768(%1)&bslash;n&quot;
l_string|&quot;   mvc  1024(256,%0),1024(%1)&bslash;n&quot;
l_string|&quot;   mvc  1280(256,%0),1280(%1)&bslash;n&quot;
l_string|&quot;   mvc  1536(256,%0),1536(%1)&bslash;n&quot;
l_string|&quot;   mvc  1792(256,%0),1792(%1)&bslash;n&quot;
l_string|&quot;   mvc  2048(256,%0),2048(%1)&bslash;n&quot;
l_string|&quot;   mvc  2304(256,%0),2304(%1)&bslash;n&quot;
l_string|&quot;   mvc  2560(256,%0),2560(%1)&bslash;n&quot;
l_string|&quot;   mvc  2816(256,%0),2816(%1)&bslash;n&quot;
l_string|&quot;   mvc  3072(256,%0),3072(%1)&bslash;n&quot;
l_string|&quot;   mvc  3328(256,%0),3328(%1)&bslash;n&quot;
l_string|&quot;   mvc  3584(256,%0),3584(%1)&bslash;n&quot;
l_string|&quot;   mvc  3840(256,%0),3840(%1)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
(paren
r_void
op_star
)paren
(paren
id|to
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
(paren
r_void
op_star
)paren
(paren
id|from
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)    clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg) copy_page(to, from)
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
r_typedef
r_struct
(brace
DECL|member|pmd0
r_int
r_int
id|pmd0
suffix:semicolon
DECL|member|pmd1
r_int
r_int
id|pmd1
suffix:semicolon
DECL|typedef|pmd_t
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
mdefine_line|#define pmd_val(x)      ((x).pmd0)
DECL|macro|pmd_val1
mdefine_line|#define pmd_val1(x)     ((x).pmd1)
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
macro_line|#endif                                 /* !__ASSEMBLY__                    */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)        (((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET           0x0UL
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET             0x0UL
DECL|macro|__pa
mdefine_line|#define __pa(x)                 (unsigned long)(x)
DECL|macro|__va
mdefine_line|#define __va(x)                 (void *)(unsigned long)(x)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + (pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)((page) - mem_map))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif                                 /* __KERNEL__                       */
macro_line|#endif                                 /* _S390_PAGE_H                     */
eof
