macro_line|#ifndef _PPC64_PAGE_H
DECL|macro|_PPC64_PAGE_H
mdefine_line|#define _PPC64_PAGE_H
multiline_comment|/*&n; * Copyright (C) 2001 PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
DECL|macro|PAGE_OFFSET_MASK
mdefine_line|#define PAGE_OFFSET_MASK (PAGE_SIZE-1)
DECL|macro|SID_SHIFT
mdefine_line|#define SID_SHIFT       28
DECL|macro|SID_MASK
mdefine_line|#define SID_MASK        0xfffffffff
DECL|macro|GET_ESID
mdefine_line|#define GET_ESID(x)     (((x) &gt;&gt; SID_SHIFT) &amp; SID_MASK)
multiline_comment|/* Define an illegal instr to trap on the bug.&n; * We don&squot;t use 0 because that marks the end of a function&n; * in the ELF ABI.  That&squot;s &quot;Boo Boo&quot; in case you wonder...&n; */
DECL|macro|BUG_OPCODE
mdefine_line|#define BUG_OPCODE .long 0x00b00b00  /* For asm */
DECL|macro|BUG_ILLEGAL_INSTR
mdefine_line|#define BUG_ILLEGAL_INSTR &quot;0x00b00b00&quot; /* For BUG macro */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/Naca.h&gt;
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
DECL|macro|REGION_SIZE
mdefine_line|#define REGION_SIZE   4UL
DECL|macro|OFFSET_SIZE
mdefine_line|#define OFFSET_SIZE   60UL
DECL|macro|REGION_SHIFT
mdefine_line|#define REGION_SHIFT  60UL
DECL|macro|OFFSET_SHIFT
mdefine_line|#define OFFSET_SHIFT  0UL
DECL|macro|REGION_MASK
mdefine_line|#define REGION_MASK   (((1UL&lt;&lt;REGION_SIZE)-1UL)&lt;&lt;REGION_SHIFT)
DECL|macro|REGION_STRIDE
mdefine_line|#define REGION_STRIDE (1UL &lt;&lt; REGION_SHIFT)
DECL|union|ppc64_va
r_typedef
r_union
id|ppc64_va
(brace
r_struct
(brace
DECL|member|off
r_int
r_int
id|off
suffix:colon
id|OFFSET_SIZE
suffix:semicolon
multiline_comment|/* intra-region offset */
DECL|member|reg
r_int
r_int
id|reg
suffix:colon
id|REGION_SIZE
suffix:semicolon
multiline_comment|/* region number */
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|l
r_int
r_int
id|l
suffix:semicolon
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
DECL|typedef|ppc64_va
)brace
id|ppc64_va
suffix:semicolon
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
id|naca-&gt;dCacheL1LineSize
suffix:semicolon
id|lines
op_assign
id|naca-&gt;dCacheL1LinesPerPage
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;  &t;mtctr  &t;%1&bslash;n&bslash;&n;1:      dcbz  &t;0,%0&bslash;n&bslash;&n;&t;add&t;%0,%0,%3&bslash;n&bslash;&n;&t;bdnz+&t;1b&quot;
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
macro_line|#ifdef CONFIG_XMON
macro_line|#include &lt;asm/ptrace.h&gt;
r_extern
r_void
id|xmon
c_func
(paren
r_struct
id|pt_regs
op_star
id|excp
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;xmon(0); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;__asm__ __volatile__(&quot;.long &quot; BUG_ILLEGAL_INSTR); &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { BUG(); } while (0)
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
DECL|macro|__pa
mdefine_line|#define __pa(x) ((unsigned long)(x)-PAGE_OFFSET)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* align addr on a size boundry - adjust address up/down if needed */
DECL|macro|_ALIGN_UP
mdefine_line|#define _ALIGN_UP(addr,size)&t;(((addr)+((size)-1))&amp;(~((size)-1)))
DECL|macro|_ALIGN_DOWN
mdefine_line|#define _ALIGN_DOWN(addr,size)&t;((addr)&amp;(~((size)-1)))
multiline_comment|/* align addr on a size boundry - adjust address up if needed */
DECL|macro|_ALIGN
mdefine_line|#define _ALIGN(addr,size)     _ALIGN_UP(addr,size)
multiline_comment|/* to align the pointer to the (next) double word boundary */
DECL|macro|DOUBLEWORD_ALIGN
mdefine_line|#define DOUBLEWORD_ALIGN(addr)&t;_ALIGN(addr,sizeof(unsigned long))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;_ALIGN(addr, PAGE_SIZE)
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
DECL|macro|IO_REGION_ID
mdefine_line|#define IO_REGION_ID       (IOREGIONBASE&gt;&gt;REGION_SHIFT)
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
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr) (mem_map+(__pa((unsigned long)kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)    ((page - mem_map) &lt; max_mapnr)
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)        (__pa(addr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC64_PAGE_H */
eof
