macro_line|#ifndef _ASMARM_PAGE_H
DECL|macro|_ASMARM_PAGE_H
mdefine_line|#define _ASMARM_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/glue.h&gt;
DECL|struct|cpu_user_fns
r_struct
id|cpu_user_fns
(brace
DECL|member|cpu_clear_user_page
r_void
(paren
op_star
id|cpu_clear_user_page
)paren
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
DECL|member|cpu_copy_user_page
r_void
(paren
op_star
id|cpu_copy_user_page
)paren
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
)brace
suffix:semicolon
macro_line|#ifdef MULTI_USER
r_extern
r_struct
id|cpu_user_fns
id|cpu_user
suffix:semicolon
DECL|macro|__cpu_clear_user_page
mdefine_line|#define __cpu_clear_user_page&t;cpu_user.cpu_clear_user_page
DECL|macro|__cpu_copy_user_page
mdefine_line|#define __cpu_copy_user_page&t;cpu_user.cpu_copy_user_page
macro_line|#else
DECL|macro|__cpu_clear_user_page
mdefine_line|#define __cpu_clear_user_page&t;__glue(_USER,_clear_user_page)
DECL|macro|__cpu_copy_user_page
mdefine_line|#define __cpu_copy_user_page&t;__glue(_USER,_copy_user_page)
r_extern
r_void
id|__cpu_clear_user_page
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
id|__cpu_copy_user_page
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
macro_line|#endif
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(addr,vaddr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;&t;__cpu_clear_user_page(addr, vaddr);&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to,from,vaddr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&bslash;&n;&t;&t;__cpu_copy_user_page(to, from, vaddr);&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memzero((void *)(page), PAGE_SIZE)
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
DECL|macro|STRICT_MM_TYPECHECKS
macro_line|#undef STRICT_MM_TYPECHECKS
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
macro_line|#include &lt;asm/proc/page.h&gt;
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;(~(PAGE_SIZE-1))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
r_extern
r_void
id|__bug
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* give file/line information */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;__bug(__FILE__, __LINE__, NULL)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;__bug(__FILE__, __LINE__, page)
macro_line|#else
multiline_comment|/* these just cause an oops */
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;(*(int *)0 = 0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;(*(int *)0 = 0)
macro_line|#endif
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
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#include &lt;asm/arch/memory.h&gt;
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;__virt_to_phys((unsigned long)(x))
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)__phys_to_virt((unsigned long)(x)))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (__pa(kaddr) &gt;&gt; PAGE_SHIFT) - &bslash;&n;&t;&t;&t;&t; (PHYS_OFFSET &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
macro_line|#endif
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
