multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PAGE_H
DECL|macro|_ASM_PAGE_H
mdefine_line|#define _ASM_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;spaces.h&gt;
macro_line|#endif
multiline_comment|/*&n; * PAGE_SHIFT determines the page size&n; */
macro_line|#ifdef CONFIG_PAGE_SIZE_4KB
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_8KB
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;13
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_16KB
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;14
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_64KB
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;16
macro_line|#endif
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK       (~((1 &lt;&lt; PAGE_SHIFT) - 1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
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
r_int
r_int
id|shm_align_mask
suffix:semicolon
DECL|function|pages_do_alias
r_static
r_inline
r_int
r_int
id|pages_do_alias
c_func
(paren
r_int
r_int
id|addr1
comma
r_int
r_int
id|addr2
)paren
(brace
r_return
(paren
id|addr1
op_xor
id|addr2
)paren
op_amp
id|shm_align_mask
suffix:semicolon
)brace
r_struct
id|page
suffix:semicolon
DECL|function|clear_user_page
r_static
r_inline
r_void
id|clear_user_page
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|vaddr
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_extern
r_void
(paren
op_star
id|flush_data_cache_page
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
id|clear_page
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages_do_alias
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
comma
id|vaddr
)paren
)paren
id|flush_data_cache_page
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|copy_user_page
r_static
r_inline
r_void
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
id|to
)paren
(brace
r_extern
r_void
(paren
op_star
id|flush_data_cache_page
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
id|copy_page
c_func
(paren
id|vto
comma
id|vfrom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages_do_alias
c_func
(paren
(paren
r_int
r_int
)paren
id|vto
comma
id|vaddr
)paren
)paren
id|flush_data_cache_page
c_func
(paren
(paren
r_int
r_int
)paren
id|vto
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
macro_line|#ifdef CONFIG_CPU_MIPS32
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x)    ((x).pte_low | ((unsigned long long)(x).pte_high &lt;&lt; 32))
macro_line|#else
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
macro_line|#endif
macro_line|#else
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
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
macro_line|#endif
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
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|ptep_buddy
mdefine_line|#define ptep_buddy(x)&t;((pte_t *)((unsigned long)(x) ^ sizeof(pte_t)))
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
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long) (x) - PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long) (x) + PAGE_OFFSET))
DECL|macro|pfn_to_kaddr
mdefine_line|#define pfn_to_kaddr(pfn)&t;__va((pfn) &lt;&lt; PAGE_SHIFT)
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + (pfn))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)((page) - mem_map))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &lt; max_mapnr)
macro_line|#endif
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
DECL|macro|UNCAC_ADDR
mdefine_line|#define UNCAC_ADDR(addr)&t;((addr) - PAGE_OFFSET + UNCAC_BASE)
DECL|macro|CAC_ADDR
mdefine_line|#define CAC_ADDR(addr)&t;&t;((addr) - UNCAC_BASE + PAGE_OFFSET)
macro_line|#endif /* defined (__KERNEL__) */
macro_line|#ifdef CONFIG_LIMITED_DMA
DECL|macro|WANT_PAGE_VIRTUAL
mdefine_line|#define WANT_PAGE_VIRTUAL
macro_line|#endif
macro_line|#endif /* _ASM_PAGE_H */
eof
