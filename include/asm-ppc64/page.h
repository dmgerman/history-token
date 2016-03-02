macro_line|#ifndef _PPC64_PAGE_H
DECL|macro|_PPC64_PAGE_H
mdefine_line|#define _PPC64_PAGE_H
multiline_comment|/*&n; * Copyright (C) 2001 PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE_SIZE
macro_line|# define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
macro_line|# define PAGE_SIZE&t;(1 &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|PAGE_OFFSET_MASK
mdefine_line|#define PAGE_OFFSET_MASK (PAGE_SIZE-1)
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|HPAGE_SHIFT
mdefine_line|#define HPAGE_SHIFT&t;24
DECL|macro|HPAGE_SIZE
mdefine_line|#define HPAGE_SIZE&t;((1UL) &lt;&lt; HPAGE_SHIFT)
DECL|macro|HPAGE_MASK
mdefine_line|#define HPAGE_MASK&t;(~(HPAGE_SIZE - 1))
DECL|macro|HUGETLB_PAGE_ORDER
mdefine_line|#define HUGETLB_PAGE_ORDER&t;(HPAGE_SHIFT - PAGE_SHIFT)
multiline_comment|/* For 64-bit processes the hugepage range is 1T-1.5T */
DECL|macro|TASK_HPAGE_BASE
mdefine_line|#define TASK_HPAGE_BASE &t;(0x0000010000000000UL)
DECL|macro|TASK_HPAGE_END
mdefine_line|#define TASK_HPAGE_END &t;(0x0000018000000000UL)
multiline_comment|/* For 32-bit processes the hugepage range is 2-3G */
DECL|macro|TASK_HPAGE_BASE_32
mdefine_line|#define TASK_HPAGE_BASE_32&t;(0x80000000UL)
DECL|macro|TASK_HPAGE_END_32
mdefine_line|#define TASK_HPAGE_END_32&t;(0xc0000000UL)
DECL|macro|ARCH_HAS_HUGEPAGE_ONLY_RANGE
mdefine_line|#define ARCH_HAS_HUGEPAGE_ONLY_RANGE
DECL|macro|is_hugepage_only_range
mdefine_line|#define is_hugepage_only_range(addr, len) &bslash;&n;&t;( ((addr &gt; (TASK_HPAGE_BASE-len)) &amp;&amp; (addr &lt; TASK_HPAGE_END)) || &bslash;&n;&t;  ((current-&gt;mm-&gt;context &amp; CONTEXT_LOW_HPAGES) &amp;&amp; &bslash;&n;&t;   (addr &gt; (TASK_HPAGE_BASE_32-len)) &amp;&amp; (addr &lt; TASK_HPAGE_END_32)) )
DECL|macro|hugetlb_free_pgtables
mdefine_line|#define hugetlb_free_pgtables free_pgtables
DECL|macro|HAVE_ARCH_HUGETLB_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
DECL|macro|in_hugepage_area
mdefine_line|#define in_hugepage_area(context, addr) &bslash;&n;&t;((cur_cpu_spec-&gt;cpu_features &amp; CPU_FTR_16M_PAGE) &amp;&amp; &bslash;&n;&t; ((((addr) &gt;= TASK_HPAGE_BASE) &amp;&amp; ((addr) &lt; TASK_HPAGE_END)) || &bslash;&n;&t;  (((context) &amp; CONTEXT_LOW_HPAGES) &amp;&amp; &bslash;&n;&t;   (((addr) &gt;= TASK_HPAGE_BASE_32) &amp;&amp; ((addr) &lt; TASK_HPAGE_END_32)))))
macro_line|#else /* !CONFIG_HUGETLB_PAGE */
DECL|macro|in_hugepage_area
mdefine_line|#define in_hugepage_area(mm, addr)&t;0
macro_line|#endif /* !CONFIG_HUGETLB_PAGE */
DECL|macro|SID_SHIFT
mdefine_line|#define SID_SHIFT       28
DECL|macro|SID_MASK
mdefine_line|#define SID_MASK        0xfffffffff
DECL|macro|GET_ESID
mdefine_line|#define GET_ESID(x)     (((x) &gt;&gt; SID_SHIFT) &amp; SID_MASK)
multiline_comment|/* align addr on a size boundary - adjust address up/down if needed */
DECL|macro|_ALIGN_UP
mdefine_line|#define _ALIGN_UP(addr,size)&t;(((addr)+((size)-1))&amp;(~((size)-1)))
DECL|macro|_ALIGN_DOWN
mdefine_line|#define _ALIGN_DOWN(addr,size)&t;((addr)&amp;(~((size)-1)))
multiline_comment|/* align addr on a size boundary - adjust address up if needed */
DECL|macro|_ALIGN
mdefine_line|#define _ALIGN(addr,size)     _ALIGN_UP(addr,size)
multiline_comment|/* to align the pointer to the (next) double word boundary */
DECL|macro|DOUBLEWORD_ALIGN
mdefine_line|#define DOUBLEWORD_ALIGN(addr)&t;_ALIGN(addr,sizeof(unsigned long))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;_ALIGN(addr, PAGE_SIZE)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/naca.h&gt;
DECL|macro|STRICT_MM_TYPECHECKS
macro_line|#undef STRICT_MM_TYPECHECKS
DECL|macro|REGION_SIZE
mdefine_line|#define REGION_SIZE   4UL
DECL|macro|REGION_SHIFT
mdefine_line|#define REGION_SHIFT  60UL
DECL|macro|REGION_MASK
mdefine_line|#define REGION_MASK   (((1UL&lt;&lt;REGION_SIZE)-1UL)&lt;&lt;REGION_SHIFT)
DECL|macro|REGION_STRIDE
mdefine_line|#define REGION_STRIDE (1UL &lt;&lt; REGION_SHIFT)
DECL|function|clear_page
r_static
id|__inline__
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|lines
comma
id|line_size
suffix:semicolon
id|line_size
op_assign
id|systemcfg-&gt;dCacheL1LineSize
suffix:semicolon
id|lines
op_assign
id|naca-&gt;dCacheL1LinesPerPage
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mtctr  &t;%1&t;# clear_page&bslash;n&bslash;&n;1:      dcbz  &t;0,%0&bslash;n&bslash;&n;&t;add&t;%0,%0,%3&bslash;n&bslash;&n;&t;bdnz+&t;1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|lines
)paren
comma
l_string|&quot;0&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|line_size
)paren
suffix:colon
l_string|&quot;ctr&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
r_struct
id|page
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
comma
r_struct
id|page
op_star
id|pg
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
comma
r_struct
id|page
op_star
id|p
)paren
suffix:semicolon
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking.  &n; * Entries in the pte table are 64b, while entries in the pgd &amp; pmd are 32b.&n; */
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
DECL|macro|__pa
mdefine_line|#define __pa(x) ((unsigned long)(x)-PAGE_OFFSET)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#ifdef MODULE
DECL|macro|__page_aligned
mdefine_line|#define __page_aligned __attribute__((__aligned__(PAGE_SIZE)))
macro_line|#else
DECL|macro|__page_aligned
mdefine_line|#define __page_aligned &bslash;&n;&t;__attribute__((__aligned__(PAGE_SIZE), &bslash;&n;&t;&t;__section__(&quot;.data.page_aligned&quot;)))
macro_line|#endif
multiline_comment|/* This must match the -Ttext linker address            */
multiline_comment|/* Note: tophys &amp; tovirt make assumptions about how     */
multiline_comment|/*       KERNELBASE is defined for performance reasons. */
multiline_comment|/*       When KERNELBASE moves, those macros may have   */
multiline_comment|/*             to change!                               */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET     0xC000000000000000
DECL|macro|KERNELBASE
mdefine_line|#define KERNELBASE      PAGE_OFFSET
DECL|macro|VMALLOCBASE
mdefine_line|#define VMALLOCBASE     0xD000000000000000
DECL|macro|IOREGIONBASE
mdefine_line|#define IOREGIONBASE    0xE000000000000000
DECL|macro|EEHREGIONBASE
mdefine_line|#define EEHREGIONBASE   0xA000000000000000
DECL|macro|IO_REGION_ID
mdefine_line|#define IO_REGION_ID       (IOREGIONBASE&gt;&gt;REGION_SHIFT)
DECL|macro|EEH_REGION_ID
mdefine_line|#define EEH_REGION_ID      (EEHREGIONBASE&gt;&gt;REGION_SHIFT)
DECL|macro|VMALLOC_REGION_ID
mdefine_line|#define VMALLOC_REGION_ID  (VMALLOCBASE&gt;&gt;REGION_SHIFT)
DECL|macro|KERNEL_REGION_ID
mdefine_line|#define KERNEL_REGION_ID   (KERNELBASE&gt;&gt;REGION_SHIFT)
DECL|macro|USER_REGION_ID
mdefine_line|#define USER_REGION_ID     (0UL)
DECL|macro|REGION_ID
mdefine_line|#define REGION_ID(X)&t;   (((unsigned long)(X))&gt;&gt;REGION_SHIFT)
multiline_comment|/*&n; * Define valid/invalid EA bits (for all ranges)&n; */
DECL|macro|VALID_EA_BITS
mdefine_line|#define VALID_EA_BITS   (0x000001ffffffffffUL)
DECL|macro|INVALID_EA_BITS
mdefine_line|#define INVALID_EA_BITS (~(REGION_MASK|VALID_EA_BITS))
DECL|macro|IS_VALID_REGION_ID
mdefine_line|#define IS_VALID_REGION_ID(x) &bslash;&n;        (((x) == USER_REGION_ID) || ((x) &gt;= KERNEL_REGION_ID))
DECL|macro|IS_VALID_EA
mdefine_line|#define IS_VALID_EA(x) &bslash;&n;        ((!((x) &amp; INVALID_EA_BITS)) &amp;&amp; IS_VALID_REGION_ID(REGION_ID(x)))
DECL|macro|__bpn_to_ba
mdefine_line|#define __bpn_to_ba(x) ((((unsigned long)(x))&lt;&lt;PAGE_SHIFT) + KERNELBASE)
DECL|macro|__ba_to_bpn
mdefine_line|#define __ba_to_bpn(x) ((((unsigned long)(x)) &amp; ~REGION_MASK) &gt;&gt; PAGE_SHIFT)
DECL|macro|__va
mdefine_line|#define __va(x) ((void *)((unsigned long)(x) + KERNELBASE))
multiline_comment|/* Given that physical addresses do not map 1-1 to absolute addresses, we&n; * use these macros to better specify exactly what we want to do.&n; * The only restriction on their use is that the absolute address&n; * macros cannot be used until after the LMB structure has been&n; * initialized in prom.c.  -Peter&n; */
DECL|macro|__v2p
mdefine_line|#define __v2p(x) ((void *) __pa(x))
DECL|macro|__v2a
mdefine_line|#define __v2a(x) ((void *) phys_to_absolute(__pa(x)))
DECL|macro|__p2a
mdefine_line|#define __p2a(x) ((void *) phys_to_absolute(x))
DECL|macro|__p2v
mdefine_line|#define __p2v(x) ((void *) __va(x))
DECL|macro|__a2p
mdefine_line|#define __a2p(x) ((void *) absolute_to_phys(x))
DECL|macro|__a2v
mdefine_line|#define __a2v(x) ((void *) __va(absolute_to_phys(x)))
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;discontigmem_page_to_pfn(page)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;discontigmem_pfn_to_page(pfn)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;discontigmem_pfn_valid(pfn)
macro_line|#else
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC64_PAGE_H */
eof
