multiline_comment|/*&n; *  linux/include/asm-arm/memory.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Note: this file should not be included by non-asm/.h files&n; */
macro_line|#ifndef __ASM_ARM_MEMORY_H
DECL|macro|__ASM_ARM_MEMORY_H
mdefine_line|#define __ASM_ARM_MEMORY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
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
id|__virt_to_phys
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|x
)paren
)paren
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
id|__phys_to_virt
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|x
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;__virt_to_phys((unsigned long)(x))
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)__phys_to_virt((unsigned long)(x)))
multiline_comment|/*&n; * Virtual &lt;-&gt; DMA view memory address translations&n; * Again, these are *only* valid on the kernel direct mapped RAM&n; * memory.  Use of these is *depreciated*.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)&t;&t;(__virt_to_bus((unsigned long)(x)))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)&t;&t;((void *)(__bus_to_virt((unsigned long)(x))))
multiline_comment|/*&n; * Conversion between a struct page and a physical address.&n; *&n; * Note: when converting an unknown physical address to a&n; * struct page, the resulting pointer must be validated&n; * using VALID_PAGE().  It must return an invalid struct page&n; * for any physical address not corresponding to a system&n; * RAM address.&n; *&n; *  page_to_pfn(page)&t;convert a struct page * to a PFN number&n; *  pfn_to_page(pfn)&t;convert a _valid_ PFN number to struct page *&n; *  pfn_valid(pfn)&t;indicates whether a PFN number is valid&n; *&n; *  virt_to_page(k)&t;convert a _valid_ virtual address to struct page *&n; *  virt_addr_valid(k)&t;indicates whether a virtual address is valid&n; */
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;(((page) - mem_map) + PHYS_PFN_OFFSET)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;((mem_map + (pfn)) - PHYS_PFN_OFFSET)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;((pfn) &gt;= PHYS_PFN_OFFSET &amp;&amp; (pfn) &lt; (PHYS_PFN_OFFSET + max_mapnr))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;((kaddr) &gt;= PAGE_OFFSET &amp;&amp; (kaddr) &lt; (unsigned long)high_memory)
macro_line|#else
multiline_comment|/*&n; * This is more complex.  We have a set of mem_map arrays spread&n; * around in memory.&n; */
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;&t;&t;&t;&t;&bslash;&n;&t;(((page) - page_zone(page)-&gt;zone_mem_map)&t;&t;&bslash;&n;&t;  + (page_zone(page)-&gt;zone_start_paddr &gt;&gt; PAGE_SHIFT))
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&bslash;&n;&t;(PFN_TO_MAPBASE(pfn) + LOCAL_MAP_NR((pfn) &lt;&lt; PAGE_SHIFT))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(PFN_TO_NID(pfn) &lt; NR_NODES)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;(KVADDR_TO_NID(kaddr) &lt; NR_NODES)
multiline_comment|/*&n; * Common discontigmem stuff.&n; *  PHYS_TO_NID is used by the ARM kernel/setup.c&n; */
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;PFN_TO_NID((addr) &gt;&gt; PAGE_SHIFT)
macro_line|#endif
multiline_comment|/*&n; * For BIO.  &quot;will die&quot;.  Kill me when bio_to_phys() and bvec_to_phys() die.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * We should really eliminate virt_to_bus() here - it&squot;s depreciated.&n; */
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus(page)&t;(virt_to_bus(page_address(page)))
macro_line|#endif
eof
