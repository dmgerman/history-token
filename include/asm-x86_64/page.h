macro_line|#ifndef _X86_64_PAGE_H
DECL|macro|_X86_64_PAGE_H
mdefine_line|#define _X86_64_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
macro_line|#ifdef __ASSEMBLY__
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(0x1 &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE (2*PAGE_SIZE)
DECL|macro|CURRENT_MASK
mdefine_line|#define CURRENT_MASK (~(THREAD_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#if 0 
macro_line|#include &lt;asm/mmx.h&gt;
mdefine_line|#define clear_page(page)&t;mmx_clear_page((void *)(page))
mdefine_line|#define copy_page(to,from)&t;mmx_copy_page(to,from)
macro_line|#else
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#endif
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(page, vaddr)&t;clear_page(page)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr)&t;copy_page(to, from)
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
DECL|member|pml4
DECL|typedef|pml4_t
r_typedef
r_struct
(brace
r_int
r_int
id|pml4
suffix:semicolon
)brace
id|pml4_t
suffix:semicolon
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pml4_val
mdefine_line|#define pml4_val(x)&t;((x).pml4)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x) ((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x) ((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x) ((pgd_t) { (x) } )
DECL|macro|__level4
mdefine_line|#define __level4(x) ((level4_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* See Documentation/x86_64/mm.txt for a description of the layout. */
DECL|macro|__START_KERNEL
mdefine_line|#define __START_KERNEL&t;&t;0xffffffff80100000
DECL|macro|__START_KERNEL_map
mdefine_line|#define __START_KERNEL_map&t;0xffffffff80000000
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET           0x0000010000000000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Tell the user there is some problem.  The exception handler decodes this frame.&n; */
DECL|struct|bug_frame
r_struct
id|bug_frame
(brace
DECL|member|ud2
r_int
r_char
id|ud2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|filename
r_char
op_star
id|filename
suffix:semicolon
multiline_comment|/* should use 32bit offset instead, but the assembler doesn&squot;t like it */
DECL|member|line
r_int
r_int
id|line
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() asm volatile(&quot;ud2 ; .quad %c1 ; .short %c0&quot; :: &quot;i&quot;(__LINE__), &quot;i&quot; (__FILE__))
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) BUG()
r_void
id|out_of_line_bug
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
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;((unsigned long)__PAGE_OFFSET)
multiline_comment|/* Note: __pa(&amp;symbol_visible_to_c) should be always replaced with __pa_symbol.&n;   Otherwise you risk miscompilation. */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;(((unsigned long)(x)&gt;=__START_KERNEL_map)?(unsigned long)(x) - (unsigned long)__START_KERNEL_map:(unsigned long)(x) - PAGE_OFFSET)
multiline_comment|/* __pa_symbol should be used for C visible symbols.&n;   This seems to be the official gcc blessed way to do such arithmetic. */
DECL|macro|__pa_symbol
mdefine_line|#define __pa_symbol(x)&t;&t;&bslash;&n;&t;({unsigned long v;  &bslash;&n;&t;  asm(&quot;&quot; : &quot;=r&quot; (v) : &quot;0&quot; (x)); &bslash;&n;&t;  __pa(v); })
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + (__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS  (VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;                                VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _X86_64_PAGE_H */
eof
