multiline_comment|/*&n; *  linux/include/asm-arm/memory.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Note: this file should not be included by non-asm/.h files&n; */
macro_line|#ifndef __ASM_ARM_MEMORY_H
DECL|macro|__ASM_ARM_MEMORY_H
mdefine_line|#define __ASM_ARM_MEMORY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#ifndef TASK_SIZE
multiline_comment|/*&n; * TASK_SIZE - the maximum size of a user space task.&n; * TASK_UNMAPPED_BASE - the lower boundary of the mmap VM area&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(0xbf000000UL)
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(0x40000000UL)
macro_line|#endif
multiline_comment|/*&n; * The maximum size of a 26-bit user space task.&n; */
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;&t;(0x04000000UL)
multiline_comment|/*&n; * Page offset: 3GB&n; */
macro_line|#ifndef PAGE_OFFSET
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0xc0000000UL)
macro_line|#endif
multiline_comment|/*&n; * Physical vs virtual RAM address space conversion.  These are&n; * private definitions which should NOT be used outside memory.h&n; * files.  Use virt_to_phys/phys_to_virt/__pa/__va instead.&n; */
macro_line|#ifndef __virt_to_phys
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(x)&t;((x) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(x)&t;((x) - PHYS_OFFSET + PAGE_OFFSET)
macro_line|#endif
multiline_comment|/*&n; * The module space lives between the addresses given by TASK_SIZE&n; * and PAGE_OFFSET - it must be within 32MB of the kernel text.&n; */
DECL|macro|MODULE_END
mdefine_line|#define MODULE_END&t;(PAGE_OFFSET)
DECL|macro|MODULE_START
mdefine_line|#define MODULE_START&t;(MODULE_END - 16*1048576)
macro_line|#if TASK_SIZE &gt; MODULE_START
macro_line|#error Top of user space clashes with start of module space
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The DMA mask corresponding to the maximum bus address allocatable&n; * using GFP_DMA.  The default here places no restriction on DMA&n; * allocations.  This must be the smallest DMA mask in the system,&n; * so a successful GFP_DMA allocation will always satisfy this.&n; */
macro_line|#ifndef ISA_DMA_THRESHOLD
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(0xffffffffULL)
macro_line|#endif
macro_line|#ifndef arch_adjust_zones
DECL|macro|arch_adjust_zones
mdefine_line|#define arch_adjust_zones(node,size,holes) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * PFNs are used to describe any physical page; this means&n; * PFN 0 == physical address 0.&n; *&n; * This is the PFN of the first RAM page in the kernel&n; * direct-mapped view.  We assume this is the first page&n; * of RAM in the mem_map as well.&n; */
DECL|macro|PHYS_PFN_OFFSET
mdefine_line|#define PHYS_PFN_OFFSET&t;(PHYS_OFFSET &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * These are *only* valid on the kernel direct mapped RAM memory.&n; * Note: Drivers should NOT use these.  They are the wrong&n; * translation for translating DMA addresses.  Use the driver&n; * DMA support - see dma-mapping.h.&n; */
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
multiline_comment|/*&n; * Drivers should NOT use these either.&n; */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;__virt_to_phys((unsigned long)(x))
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)__phys_to_virt((unsigned long)(x)))
multiline_comment|/*&n; * Virtual &lt;-&gt; DMA view memory address translations&n; * Again, these are *only* valid on the kernel direct mapped RAM&n; * memory.  Use of these is *deprecated* (and that doesn&squot;t mean&n; * use the __ prefixed forms instead.)  See dma-mapping.h.&n; */
DECL|function|virt_to_bus
r_static
r_inline
id|__deprecated
r_int
r_int
id|virt_to_bus
c_func
(paren
r_void
op_star
id|x
)paren
(brace
r_return
id|__virt_to_bus
c_func
(paren
(paren
r_int
r_int
)paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_static
r_inline
id|__deprecated
r_void
op_star
id|bus_to_virt
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
id|__bus_to_virt
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
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
mdefine_line|#define virt_addr_valid(kaddr)&t;((unsigned long)(kaddr) &gt;= PAGE_OFFSET &amp;&amp; (unsigned long)(kaddr) &lt; (unsigned long)high_memory)
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#else /* CONFIG_DISCONTIGMEM */
multiline_comment|/*&n; * This is more complex.  We have a set of mem_map arrays spread&n; * around in memory.&n; */
macro_line|#include &lt;linux/numa.h&gt;
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;&t;&t;&t;&t;&bslash;&n;&t;(( (page) - page_zone(page)-&gt;zone_mem_map)&t;&t;&bslash;&n;&t;  + page_zone(page)-&gt;zone_start_pfn)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&bslash;&n;&t;(PFN_TO_MAPBASE(pfn) + LOCAL_MAP_NR((pfn) &lt;&lt; PAGE_SHIFT))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(PFN_TO_NID(pfn) &lt; MAX_NUMNODES)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;(KVADDR_TO_NID(kaddr) &lt; MAX_NUMNODES)
multiline_comment|/*&n; * Common discontigmem stuff.&n; *  PHYS_TO_NID is used by the ARM kernel/setup.c&n; */
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;PFN_TO_NID((addr) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
multiline_comment|/*&n; * For BIO.  &quot;will die&quot;.  Kill me when bio_to_phys() and bvec_to_phys() die.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Optional device DMA address remapping. Do _not_ use directly!&n; * We should really eliminate virt_to_bus() here - it&squot;s deprecated.&n; */
macro_line|#ifndef __arch_page_to_dma
DECL|macro|page_to_dma
mdefine_line|#define page_to_dma(dev, page)&t;&t;((dma_addr_t)__virt_to_bus((unsigned long)page_address(page)))
DECL|macro|dma_to_virt
mdefine_line|#define dma_to_virt(dev, addr)&t;&t;((void *)__bus_to_virt(addr))
DECL|macro|virt_to_dma
mdefine_line|#define virt_to_dma(dev, addr)&t;&t;((dma_addr_t)__virt_to_bus((unsigned long)(addr)))
macro_line|#else
DECL|macro|page_to_dma
mdefine_line|#define page_to_dma(dev, page)&t;&t;(__arch_page_to_dma(dev, page))
DECL|macro|dma_to_virt
mdefine_line|#define dma_to_virt(dev, addr)&t;&t;(__arch_dma_to_virt(dev, addr))
DECL|macro|virt_to_dma
mdefine_line|#define virt_to_dma(dev, addr)&t;&t;(__arch_virt_to_dma(dev, addr))
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
