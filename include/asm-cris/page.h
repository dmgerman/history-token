macro_line|#ifndef _CRIS_PAGE_H
DECL|macro|_CRIS_PAGE_H
mdefine_line|#define _CRIS_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/page.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;13
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1 &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)        memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)      memcpy((void *)(to), (void *)(from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)    clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg) copy_page(to, from)
DECL|macro|alloc_zeroed_user_highpage
mdefine_line|#define alloc_zeroed_user_highpage(vma, vaddr) alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO, vma, vaddr)
DECL|macro|__HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
mdefine_line|#define __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
macro_line|#ifndef __ASSEMBLY__
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
macro_line|#endif
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
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
multiline_comment|/* On CRIS the PFN numbers doesn&squot;t start at 0 so we have to compensate */
multiline_comment|/* for that before indexing into the page table starting at mem_map    */
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + ((pfn) - (PAGE_OFFSET &gt;&gt; PAGE_SHIFT)))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)((page) - mem_map) + (PAGE_OFFSET &gt;&gt; PAGE_SHIFT))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(((pfn) - (PAGE_OFFSET &gt;&gt; PAGE_SHIFT)) &lt; max_mapnr)
multiline_comment|/* to index into the page map. our pages all start at physical addr PAGE_OFFSET so&n; * we can let the map start there. notice that we subtract PAGE_OFFSET because&n; * we start our mem_map there - in other ports they map mem_map physically and&n; * use __pa instead. in our system both the physical and virtual address of DRAM&n; * is too high to let mem_map start at 0, so we do it this way instead (similar&n; * to arm and m68k I think)&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)    (mem_map + (((unsigned long)(kaddr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)       (((page) - mem_map) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid((unsigned)(kaddr) &gt;&gt; PAGE_SHIFT)
multiline_comment|/* convert a page (based on mem_map and forward) to a physical address&n; * do this by figuring out the virtual address and then use __pa&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)     __pa((((page) - mem_map) &lt;&lt; PAGE_SHIFT) + PAGE_OFFSET)
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;  printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;         BUG(); &bslash;&n;} while (0)
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_static
r_inline
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
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _CRIS_PAGE_H */
eof
