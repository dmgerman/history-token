multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifndef _PPC_PAGE_H
DECL|macro|_PPC_PAGE_H
mdefine_line|#define _PPC_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Be sure to change arch/ppc/Makefile to match */
macro_line|#ifdef CONFIG_KERNEL_START_BOOL
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;CONFIG_KERNEL_START
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0xc0000000
macro_line|#endif /* CONFIG_KERNEL_START_BOOL */
DECL|macro|KERNELBASE
mdefine_line|#define KERNELBASE&t;PAGE_OFFSET
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/system.h&gt; /* for xmon definition */
macro_line|#ifdef CONFIG_XMON
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;xmon(0); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;__asm__ __volatile__(&quot;.long 0x0&quot;); &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
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
multiline_comment|/* align addr on a size boundry - adjust address up if needed -- Cort */
DECL|macro|_ALIGN
mdefine_line|#define _ALIGN(addr,size)&t;(((addr)+size-1)&amp;(~(size-1)))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
r_extern
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
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
r_extern
r_void
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
id|vaddr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ppc_memstart
suffix:semicolon
r_extern
r_int
r_int
id|ppc_memoffset
suffix:semicolon
macro_line|#ifndef CONFIG_APUS
DECL|macro|PPC_MEMSTART
mdefine_line|#define PPC_MEMSTART&t;0
DECL|macro|PPC_MEMOFFSET
mdefine_line|#define PPC_MEMOFFSET&t;PAGE_OFFSET
macro_line|#else
DECL|macro|PPC_MEMSTART
mdefine_line|#define PPC_MEMSTART&t;ppc_memstart
DECL|macro|PPC_MEMOFFSET
mdefine_line|#define PPC_MEMOFFSET&t;ppc_memoffset
macro_line|#endif
macro_line|#if defined(CONFIG_APUS) &amp;&amp; !defined(MODULE)
multiline_comment|/* map phys-&gt;virtual and virtual-&gt;phys for RAM pages */
DECL|function|___pa
r_static
r_inline
r_int
r_int
id|___pa
c_func
(paren
r_int
r_int
id|v
)paren
(brace
r_int
r_int
id|p
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: addis %0, %1, %2;&quot;
l_string|&quot;.section &bslash;&quot;.vtop_fixup&bslash;&quot;,&bslash;&quot;aw&bslash;&quot;;&quot;
l_string|&quot;.align  1;&quot;
l_string|&quot;.long   1b;&quot;
l_string|&quot;.previous;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|p
)paren
suffix:colon
l_string|&quot;b&quot;
(paren
id|v
)paren
comma
l_string|&quot;K&quot;
(paren
(paren
(paren
op_minus
id|PAGE_OFFSET
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|___va
r_static
r_inline
r_void
op_star
id|___va
c_func
(paren
r_int
r_int
id|p
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1: addis %0, %1, %2;&quot;
l_string|&quot;.section &bslash;&quot;.ptov_fixup&bslash;&quot;,&bslash;&quot;aw&bslash;&quot;;&quot;
l_string|&quot;.align  1;&quot;
l_string|&quot;.long   1b;&quot;
l_string|&quot;.previous;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|v
)paren
suffix:colon
l_string|&quot;b&quot;
(paren
id|p
)paren
comma
l_string|&quot;K&quot;
(paren
(paren
(paren
id|PAGE_OFFSET
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|v
suffix:semicolon
)brace
macro_line|#else
DECL|macro|___pa
mdefine_line|#define ___pa(vaddr) ((vaddr)-PPC_MEMOFFSET)
DECL|macro|___va
mdefine_line|#define ___va(paddr) ((paddr)+PPC_MEMOFFSET)
macro_line|#endif
DECL|macro|__pa
mdefine_line|#define __pa(x) ___pa((unsigned long)(x))
DECL|macro|__va
mdefine_line|#define __va(x) ((void *)(___va((unsigned long)(x))))
DECL|macro|MAP_PAGE_RESERVED
mdefine_line|#define MAP_PAGE_RESERVED&t;(1&lt;&lt;15)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (((unsigned long)kaddr-PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
r_extern
r_int
r_int
id|get_zero_page_fast
c_func
(paren
r_void
)paren
suffix:semicolon
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
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC_PAGE_H */
eof
