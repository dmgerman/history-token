macro_line|#ifndef _ASM_PAGE_H
DECL|macro|_ASM_PAGE_H
mdefine_line|#define _ASM_PAGE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#include &lt;asm/mem-layout.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|get_user_page
mdefine_line|#define get_user_page(vaddr)&t;&t;&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_user_page
mdefine_line|#define free_user_page(page, addr)&t;&t;free_page(addr)
DECL|macro|clear_page
mdefine_line|#define clear_page(pgaddr)&t;&t;&t;memset((pgaddr), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;&t;&t;memcpy((to), (from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(pgaddr, vaddr, page)&t;memset((pgaddr), 0, PAGE_SIZE)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(vto, vfrom, vaddr, topg)&t;memcpy((vto), (vfrom), PAGE_SIZE)
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
DECL|member|ste
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|ste
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pue
DECL|typedef|pud_t
r_typedef
r_struct
(brace
id|pmd_t
id|pue
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|pud_t
suffix:semicolon
DECL|member|pge
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
id|pud_t
id|pge
(braket
l_int|1
)braket
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
mdefine_line|#define pmd_val(x)&t;((x).ste[0])
DECL|macro|pud_val
mdefine_line|#define pud_val(x)&t;((x).pue[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pge[0])
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pud
mdefine_line|#define __pud(x)&t;((pud_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
DECL|macro|PTE_MASK
mdefine_line|#define PTE_MASK&t;PAGE_MASK
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
multiline_comment|/* Pure 2^n version of get_order */
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
id|__attribute_const__
suffix:semicolon
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
DECL|macro|devmem_is_allowed
mdefine_line|#define devmem_is_allowed(pfn)&t;1
DECL|macro|__pa
mdefine_line|#define __pa(vaddr)&t;&t;virt_to_phys((void *) vaddr)
DECL|macro|__va
mdefine_line|#define __va(paddr)&t;&t;phys_to_virt((unsigned long) paddr)
DECL|macro|pfn_to_kaddr
mdefine_line|#define pfn_to_kaddr(pfn)&t;__va((pfn) &lt;&lt; PAGE_SHIFT)
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
r_extern
r_int
r_int
id|min_low_pfn
suffix:semicolon
r_extern
r_int
r_int
id|max_pfn
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + (pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long) ((page) - mem_map))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &lt; max_mapnr)
macro_line|#else
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(&amp;mem_map[(pfn) - (PAGE_OFFSET &gt;&gt; PAGE_SHIFT)])
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((PAGE_OFFSET &gt;&gt; PAGE_SHIFT) + (unsigned long) ((page) - mem_map))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &gt;= min_low_pfn &amp;&amp; (pfn) &lt; max_low_pfn)
macro_line|#endif
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
macro_line|#ifdef CONFIG_MMU
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS &bslash;&n;&t;(VM_READ | VM_WRITE | &bslash;&n;&t;((current-&gt;personality &amp; READ_IMPLIES_EXEC) ? VM_EXEC : 0 ) | &bslash;&n;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#ifdef CONFIG_CONTIGUOUS_PAGE_ALLOC
DECL|macro|WANT_PAGE_VIRTUAL
mdefine_line|#define WANT_PAGE_VIRTUAL&t;1
macro_line|#endif
macro_line|#endif /* _ASM_PAGE_H */
eof
