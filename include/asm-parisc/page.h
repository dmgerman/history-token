macro_line|#ifndef _PARISC_PAGE_H
DECL|macro|_PARISC_PAGE_H
mdefine_line|#define _PARISC_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/cache.h&gt;
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)      copy_user_page_asm((void *)(to), (void *)(from))
r_struct
id|page
suffix:semicolon
r_extern
r_void
id|purge_kernel_dcache_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|copy_user_page_asm
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
r_extern
r_void
id|clear_user_page_asm
c_func
(paren
r_void
op_star
id|page
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|copy_user_page
id|copy_user_page
c_func
(paren
r_void
op_star
id|vto
comma
r_void
op_star
id|vfrom
comma
r_int
r_int
id|vaddr
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
id|copy_user_page_asm
c_func
(paren
id|vto
comma
id|vfrom
)paren
suffix:semicolon
id|flush_kernel_dcache_page
c_func
(paren
id|vto
)paren
suffix:semicolon
multiline_comment|/* XXX: ppc flushes icache too, should we? */
)brace
r_static
r_inline
r_void
DECL|function|clear_user_page
id|clear_user_page
c_func
(paren
r_void
op_star
id|page
comma
r_int
r_int
id|vaddr
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
id|purge_kernel_dcache_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
id|clear_user_page_asm
c_func
(paren
id|page
comma
id|vaddr
)paren
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
macro_line|#ifdef __LP64__
DECL|macro|MAX_PHYSMEM_RANGES
mdefine_line|#define MAX_PHYSMEM_RANGES 8 /* Fix the size for now (current known max is 3) */
macro_line|#else
DECL|macro|MAX_PHYSMEM_RANGES
mdefine_line|#define MAX_PHYSMEM_RANGES 1 /* First range is only range that fits in 32 bits */
macro_line|#endif
DECL|struct|__physmem_range
r_typedef
r_struct
id|__physmem_range
(brace
DECL|member|start_pfn
r_int
r_int
id|start_pfn
suffix:semicolon
DECL|member|pages
r_int
r_int
id|pages
suffix:semicolon
multiline_comment|/* PAGE_SIZE pages */
DECL|typedef|physmem_range_t
)brace
id|physmem_range_t
suffix:semicolon
r_extern
id|physmem_range_t
id|pmem_ranges
(braket
)braket
suffix:semicolon
r_extern
r_int
id|npmem_ranges
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|LINUX_GATEWAY_SPACE
mdefine_line|#define LINUX_GATEWAY_SPACE     0
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET           (0x10000000)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;((unsigned long)__PAGE_OFFSET)
multiline_comment|/* These macros don&squot;t work for 64-bit C code -- don&squot;t allow in C at all */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|PA
macro_line|#   define PA(x)&t;((x)-__PAGE_OFFSET)
DECL|macro|VA
macro_line|#   define VA(x)&t;((x)+__PAGE_OFFSET)
macro_line|#endif
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + (pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)((page) - mem_map))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)     (mem_map + (__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
macro_line|#endif  /* !CONFIG_DISCONTIGMEM */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PARISC_PAGE_H */
eof
