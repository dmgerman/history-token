macro_line|#ifndef _ASM_M32R_PAGE_H
DECL|macro|_ASM_M32R_PAGE_H
mdefine_line|#define _ASM_M32R_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
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
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg)&t;copy_page(to, from)
DECL|macro|alloc_zeroed_user_highpage
mdefine_line|#define alloc_zeroed_user_highpage(vma, vaddr) alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO, vma, vaddr)
DECL|macro|__HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
mdefine_line|#define __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|PTE_MASK
mdefine_line|#define PTE_MASK&t;PAGE_MASK
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
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
multiline_comment|/*&n; * This handles the memory map.. We could make this a config&n; * option, but too many people screw it up, and too few need&n; * it.&n; *&n; * A __PAGE_OFFSET of 0xC0000000 means that the kernel has&n; * a virtual address space of one gigabyte, which limits the&n; * amount of physical memory you can use to about 950MB.&n; *&n; * If you want more physical memory than this then see the CONFIG_HIGHMEM4G&n; * and CONFIG_HIGHMEM64G options in the kernel configuration.&n; */
multiline_comment|/* This handles the memory map.. */
macro_line|#ifndef __ASSEMBLY__
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
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|__MEMORY_START
mdefine_line|#define __MEMORY_START  CONFIG_MEMORY_START
DECL|macro|__MEMORY_SIZE
mdefine_line|#define __MEMORY_SIZE   CONFIG_MEMORY_SIZE
macro_line|#ifdef CONFIG_MMU
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET  (0x80000000)
macro_line|#else
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET  (0x00000000)
macro_line|#endif
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;((unsigned long)__PAGE_OFFSET)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x) + PAGE_OFFSET))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|PFN_BASE
mdefine_line|#define PFN_BASE&t;&t;(CONFIG_MEMORY_START &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + ((pfn) - PFN_BASE))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;&bslash;&n;&t;((unsigned long)((page) - mem_map) + PFN_BASE)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(((pfn) - PFN_BASE) &lt; max_mapnr)
macro_line|#endif  /* !CONFIG_DISCONTIGMEM */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC )
DECL|macro|devmem_is_allowed
mdefine_line|#define devmem_is_allowed(x) 1
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_M32R_PAGE_H */
eof
