macro_line|#ifndef _ALPHA_PAGE_H
DECL|macro|_ALPHA_PAGE_H
mdefine_line|#define _ALPHA_PAGE_H
macro_line|#include &lt;asm/pal.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;13
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
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
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)&t;clear_page(page)
r_extern
r_void
id|copy_page
c_func
(paren
r_void
op_star
id|_to
comma
r_void
op_star
id|_from
)paren
suffix:semicolon
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr)&t;copy_page(to, from)
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
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif /* STRICT_MM_TYPECHECKS */
multiline_comment|/* ??? Would be nice to use .gprel32 here, but we can&squot;t be sure that the&n;   function loaded the GP, so this could fail in modules.  */
DECL|macro|BUG
mdefine_line|#define BUG() &bslash;&n;  __asm__ __volatile__(&quot;call_pal %0  # bugchk&bslash;n&bslash;t&quot;&quot;.long %1&bslash;n&bslash;t.8byte %2&quot; &bslash;&n;&t;&t;       : : &quot;i&quot; (PAL_bugchk), &quot;i&quot;(__LINE__), &quot;i&quot;(__FILE__))
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;BUG()
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
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xffff800000000000
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xfffffc0000000000
macro_line|#endif
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long) (x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long) (x) + PAGE_OFFSET))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;(((page) - mem_map) &lt; max_mapnr)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_PAGE_H */
eof
