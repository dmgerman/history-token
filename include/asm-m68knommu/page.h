macro_line|#ifndef _M68KNOMMU_PAGE_H
DECL|macro|_M68KNOMMU_PAGE_H
mdefine_line|#define _M68KNOMMU_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;(12)
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#if !defined(CONFIG_SMALL_TASKS) &amp;&amp; PAGE_SHIFT &lt; 13
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (8192)
macro_line|#else
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE PAGE_SIZE
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|get_user_page
mdefine_line|#define get_user_page(vaddr)&t;&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_user_page
mdefine_line|#define free_user_page(page, addr)&t;free_page(addr)
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((to), (from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg)&t;copy_page(to, from)
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
(braket
l_int|16
)braket
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
mdefine_line|#define pmd_val(x)&t;((&amp;x)-&gt;pmd[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
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
r_extern
r_int
r_int
id|memory_start
suffix:semicolon
r_extern
r_int
r_int
id|memory_end
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#include &lt;asm/page_offset.h&gt;
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(PAGE_OFFSET_RAW)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__pa
mdefine_line|#define __pa(vaddr)&t;&t;virt_to_phys((void *)vaddr)
DECL|macro|__va
mdefine_line|#define __va(paddr)&t;&t;phys_to_virt((unsigned long)paddr)
DECL|macro|virt_to_pfn
mdefine_line|#define virt_to_pfn(kaddr)&t;(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_virt
mdefine_line|#define pfn_to_virt(pfn)&t;__va((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(addr)&t;(mem_map + (((unsigned long)(addr)-PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|page_to_virt
mdefine_line|#define page_to_virt(page)&t;((((page) - mem_map) &lt;&lt; PAGE_SHIFT) + PAGE_OFFSET)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;virt_to_page(pfn_to_virt(pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;virt_to_pfn(page_to_virt(page))
DECL|macro|virt_addr_valid
mdefine_line|#define&t;virt_addr_valid(kaddr)&t;(((void *)(kaddr) &gt;= (void *)PAGE_OFFSET) &amp;&amp; &bslash;&n;&t;&t;&t;&t;((void *)(kaddr) &lt; (void *)memory_end))
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68KNOMMU_PAGE_H */
eof
