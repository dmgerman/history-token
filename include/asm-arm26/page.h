macro_line|#ifndef _ASMARM_PAGE_H
DECL|macro|_ASMARM_PAGE_H
mdefine_line|#define _ASMARM_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__clear_user_page
c_func
(paren
r_void
op_star
id|p
comma
r_int
r_int
id|user
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
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|user
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
r_const
r_void
op_star
id|from
)paren
suffix:semicolon
singleline_comment|//FIXME these may be wrong on ARM26
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(addr,vaddr,pg)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;&t;__clear_user_page(addr, vaddr);&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to,from,vaddr,pg)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;&t;__copy_user_page(to, from, vaddr);&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memzero((void *)(page), PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to, from)  __copy_user_page(to, from, 0);
DECL|macro|STRICT_MM_TYPECHECKS
macro_line|#undef STRICT_MM_TYPECHECKS
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
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
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      ((x).pgd)
DECL|macro|pte_val
mdefine_line|#define pte_val(x)      ((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   ((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)        ((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        ((pmd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     ((pgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
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
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
singleline_comment|//FIXME - should these cast to unsigned long?
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)      (x)
DECL|macro|pte_val
mdefine_line|#define pte_val(x)      (x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      (x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)   (x)
DECL|macro|__pte
mdefine_line|#define __pte(x)        (x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)        (x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)     (x)
macro_line|#endif /* STRICT_MM_TYPECHECKS */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* PAGE_SHIFT determines the page size.  This is configurable. */
macro_line|#if defined(CONFIG_PAGESIZE_16)
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT      14              /* 16K */
macro_line|#else           /* default */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT      15              /* 32K */
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE   32768
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;(~(PAGE_SIZE-1))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
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
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
