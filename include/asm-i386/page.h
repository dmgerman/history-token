macro_line|#ifndef _I386_PAGE_H
DECL|macro|_I386_PAGE_H
mdefine_line|#define _I386_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|LARGE_PAGE_MASK
mdefine_line|#define LARGE_PAGE_MASK (~(LARGE_PAGE_SIZE-1))
DECL|macro|LARGE_PAGE_SIZE
mdefine_line|#define LARGE_PAGE_SIZE (1UL &lt;&lt; PMD_SHIFT)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_X86_USE_3DNOW
macro_line|#include &lt;asm/mmx.h&gt;
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;mmx_clear_page((void *)(page))
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;mmx_copy_page(to,from)
macro_line|#else
multiline_comment|/*&n; *&t;On older X86 processors its not a win to use MMX here it seems.&n; *&t;Maybe the K6-III ?&n; */
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#endif
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr, pg)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, pg)&t;copy_page(to, from)
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
macro_line|#if CONFIG_X86_PAE
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
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte_low | ((unsigned long long)(x).pte_high &lt;&lt; 32))
macro_line|#else
DECL|member|pte_low
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte_low
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
mdefine_line|#define pte_val(x)&t;((x).pte_low)
macro_line|#endif
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
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/*&n; * This handles the memory map.. We could make this a config&n; * option, but too many people screw it up, and too few need&n; * it.&n; *&n; * A __PAGE_OFFSET of 0xC0000000 means that the kernel has&n; * a virtual address space of one gigabyte, which limits the&n; * amount of physical memory you can use to about 950MB. &n; *&n; * If you want more physical memory than this then see the CONFIG_HIGHMEM4G&n; * and CONFIG_HIGHMEM64G options in the kernel configuration.&n; */
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET&t;&t;(0xC0000000)
multiline_comment|/*&n; * This much address space is reserved for vmalloc() and iomap()&n; * as well as fixmap mappings.&n; */
DECL|macro|__VMALLOC_RESERVE
mdefine_line|#define __VMALLOC_RESERVE&t;(128 &lt;&lt; 20)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Tell the user there is some problem. Beep too, so we can&n; * see^H^H^Hhear bugs in early bootup as well!&n; * The offending file and line are encoded after the &quot;officially&n; * undefined&quot; opcode for parsing in the trap handler.&n; */
macro_line|#if 1&t;/* Set to zero for a slightly smaller kernel */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;&t;&t;&bslash;&n; __asm__ __volatile__(&t;&quot;ud2&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.word %c0&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;&quot;&bslash;t.long %c1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t; : : &quot;i&quot; (__LINE__), &quot;i&quot; (__FILE__))
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() __asm__ __volatile__(&quot;ud2&bslash;n&quot;)
macro_line|#endif
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
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;((unsigned long)__PAGE_OFFSET)
DECL|macro|VMALLOC_RESERVE
mdefine_line|#define VMALLOC_RESERVE&t;&t;((unsigned long)__VMALLOC_RESERVE)
DECL|macro|__MAXMEM
mdefine_line|#define __MAXMEM&t;&t;(-__PAGE_OFFSET-__VMALLOC_RESERVE)
DECL|macro|MAXMEM
mdefine_line|#define MAXMEM&t;&t;&t;((unsigned long)(-PAGE_OFFSET-VMALLOC_RESERVE))
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_PAGE_H */
eof
