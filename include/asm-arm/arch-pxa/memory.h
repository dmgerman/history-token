multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/memory.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xa0000000UL)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * The nodes are matched with the physical SDRAM banks as follows:&n; *&n; * &t;node 0:  0xa0000000-0xa3ffffff&t;--&gt;  0xc0000000-0xc3ffffff&n; * &t;node 1:  0xa4000000-0xa7ffffff&t;--&gt;  0xc4000000-0xc7ffffff&n; * &t;node 2:  0xa8000000-0xabffffff&t;--&gt;  0xc8000000-0xcbffffff&n; * &t;node 3:  0xac000000-0xafffffff&t;--&gt;  0xcc000000-0xcfffffff&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(addr) (((unsigned long)(addr) - PAGE_OFFSET) &gt;&gt; 26)
multiline_comment|/*&n; * Given a page frame number, convert it to a node id.&n; */
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(pfn)&t;&t;(((pfn) - PHYS_PFN_OFFSET) &gt;&gt; (26 - PAGE_SHIFT))
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr)&t;NODE_MEM_MAP(KVADDR_TO_NID(kaddr))
multiline_comment|/*&n; * Given a page frame number, find the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|PFN_TO_MAPBASE
mdefine_line|#define PFN_TO_MAPBASE(pfn)&t;NODE_MEM_MAP(PFN_TO_NID(pfn))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(addr) &bslash;&n;&t;(((unsigned long)(addr) &amp; 0x03ffffff) &gt;&gt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(addr)&t;(0)
macro_line|#endif
macro_line|#endif
eof
