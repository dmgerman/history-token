macro_line|#ifndef _CRIS_PAGE_H
DECL|macro|_CRIS_PAGE_H
mdefine_line|#define _CRIS_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;13
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)        memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)      memcpy((void *)(to), (void *)(from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)    clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr) copy_page(to, from)
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
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
macro_line|#else
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
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;(x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;(x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* This handles the memory map.. */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;KSEG_6   /* kseg_6 is mapped to physical ram */
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;KSEG_C   /* kseg_c is mapped to physical ram */
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;  printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;         BUG(); &bslash;&n;} while (0)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* macros to convert between really physical and virtual addresses&n; * by stripping a selected bit, we can convert between KSEG_x and 0x40000000 where&n; * the DRAM really resides&n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
multiline_comment|/* we have DRAM virtually at 0x6 */
DECL|macro|__pa
mdefine_line|#define __pa(x)                 ((unsigned long)(x) &amp; 0xdfffffff)
DECL|macro|__va
mdefine_line|#define __va(x)                 ((void *)((unsigned long)(x) | 0x20000000))
macro_line|#else
multiline_comment|/* we have DRAM virtually at 0xc */
DECL|macro|__pa
mdefine_line|#define __pa(x)                 ((unsigned long)(x) &amp; 0x7fffffff)
DECL|macro|__va
mdefine_line|#define __va(x)                 ((void *)((unsigned long)(x) | 0x80000000))
macro_line|#endif
multiline_comment|/* to index into the page map. our pages all start at physical addr PAGE_OFFSET so&n; * we can let the map start there. notice that we subtract PAGE_OFFSET because&n; * we start our mem_map there - in other ports they map mem_map physically and&n; * use __pa instead. in our system both the physical and virtual address of DRAM&n; * is too high to let mem_map start at 0, so we do it this way instead (similar&n; * to arm and m68k I think)&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)    (mem_map + (((unsigned long)(kaddr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)       (((page) - mem_map) &lt; max_mapnr)
multiline_comment|/* convert a page (based on mem_map and forward) to a physical address&n; * do this by figuring out the virtual address and then use __pa&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)     __pa((((page) - mem_map) &lt;&lt; PAGE_SHIFT) + PAGE_OFFSET)
multiline_comment|/* from linker script */
r_extern
r_int
r_int
id|dram_start
comma
id|dram_end
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _CRIS_PAGE_H */
eof
