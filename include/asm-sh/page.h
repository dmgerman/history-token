macro_line|#ifndef __ASM_SH_PAGE_H
DECL|macro|__ASM_SH_PAGE_H
mdefine_line|#define __ASM_SH_PAGE_H
multiline_comment|/*&n; * Copyright (C) 1999  Niibe Yutaka&n; */
multiline_comment|/*&n;   [ P0/U0 (virtual) ]&t;&t;0x00000000     &lt;------ User space&n;   [ P1 (fixed)   cached ]&t;0x80000000     &lt;------ Kernel space&n;   [ P2 (fixed)  non-cachable]&t;0xA0000000     &lt;------ Physical access&n;   [ P3 (virtual) cached]&t;0xC0000000     &lt;------ vmalloced area&n;   [ P4 control   ]&t;&t;0xE0000000&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|PTE_MASK
mdefine_line|#define PTE_MASK&t;PAGE_MASK
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|to
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#if defined(__sh3__)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr)&t;copy_page(to, from)
macro_line|#elif defined(__SH4__)
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
)paren
suffix:semicolon
r_extern
r_void
id|__clear_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|orig_to
)paren
suffix:semicolon
r_extern
r_void
id|__copy_user_page
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
r_void
op_star
id|orig_to
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; * IF YOU CHANGE THIS, PLEASE ALSO CHANGE&n; *&n; *&t;arch/sh/vmlinux.lds.S&n; *&n; * which has the same constant encoded..&n; */
DECL|macro|__MEMORY_START
mdefine_line|#define __MEMORY_START&t;&t;CONFIG_MEMORY_START
DECL|macro|__MEMORY_SIZE
mdefine_line|#define __MEMORY_SIZE&t;&t;CONFIG_MEMORY_SIZE
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/* Just for HP690, for now.. */
DECL|macro|__MEMORY_START_2ND
mdefine_line|#define __MEMORY_START_2ND&t;(__MEMORY_START+0x02000000)
DECL|macro|__MEMORY_SIZE_2ND
mdefine_line|#define __MEMORY_SIZE_2ND&t;0x001000000 /* 16MB */
macro_line|#endif
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0x80000000UL)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|phys_to_page
mdefine_line|#define phys_to_page(phys)&t;(mem_map + (((phys)-__MEMORY_START) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(((page - mem_map) &lt;&lt; PAGE_SHIFT) + __MEMORY_START)
macro_line|#endif
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;phys_to_page(__pa(kaddr))
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Tell the user there is some problem.&n; */
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;asm volatile(&quot;nop&quot;); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
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
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_PAGE_H */
eof
