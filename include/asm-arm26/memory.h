multiline_comment|/*&n; *  linux/include/asm-arm26/memory.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Note: this file should not be included by non-asm/.h files&n; */
macro_line|#ifndef __ASM_ARM_MEMORY_H
DECL|macro|__ASM_ARM_MEMORY_H
mdefine_line|#define __ASM_ARM_MEMORY_H
multiline_comment|/*&n; * User space: 26MB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE       (0x01a00000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * Page offset: 32MB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET     (0x02000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET     (0x02000000UL)
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)       (0)
multiline_comment|/*&n; * PFNs are used to describe any physical page; this means&n; * PFN 0 == physical address 0.&n; *&n; * This is the PFN of the first RAM page in the kernel&n; * direct-mapped view.  We assume this is the first page&n; * of RAM in the mem_map as well.&n; */
DECL|macro|PHYS_PFN_OFFSET
mdefine_line|#define PHYS_PFN_OFFSET&t;(PHYS_OFFSET &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * These are *only* valid on the kernel direct mapped RAM memory.&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_void
op_star
id|x
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|x
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|x
)paren
suffix:semicolon
)brace
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;(unsigned long)(x)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)(unsigned long)(x))
multiline_comment|/*&n; * Virtual &lt;-&gt; DMA view memory address translations&n; * Again, these are *only* valid on the kernel direct mapped RAM&n; * memory.  Use of these is *depreciated*.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)&t;&t;((unsigned long)(x))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)&t;&t;((void *)((unsigned long)(x)))
multiline_comment|/*&n; * Conversion between a struct page and a physical address.&n; *&n; * Note: when converting an unknown physical address to a&n; * struct page, the resulting pointer must be validated&n; * using VALID_PAGE().  It must return an invalid struct page&n; * for any physical address not corresponding to a system&n; * RAM address.&n; *&n; *  page_to_pfn(page)&t;convert a struct page * to a PFN number&n; *  pfn_to_page(pfn)&t;convert a _valid_ PFN number to struct page *&n; *  pfn_valid(pfn)&t;indicates whether a PFN number is valid&n; *&n; *  virt_to_page(k)&t;convert a _valid_ virtual address to struct page *&n; *  virt_addr_valid(k)&t;indicates whether a virtual address is valid&n; */
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;(((page) - mem_map) + PHYS_PFN_OFFSET)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;((mem_map + (pfn)) - PHYS_PFN_OFFSET)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &gt;= PHYS_PFN_OFFSET &amp;&amp; (pfn) &lt; (PHYS_PFN_OFFSET + max_mapnr))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;((int)(kaddr) &gt;= PAGE_OFFSET &amp;&amp; (int)(kaddr) &lt; (unsigned long)high_memory)
multiline_comment|/*&n; * For BIO.  &quot;will die&quot;.  Kill me when bio_to_phys() and bvec_to_phys() die.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * We should really eliminate virt_to_bus() here - it&squot;s depreciated.&n; */
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus(page)&t;(page_address(page))
macro_line|#endif
eof
