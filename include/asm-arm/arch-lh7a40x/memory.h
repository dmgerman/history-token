multiline_comment|/* include/asm-arm/arch-lh7a40x/memory.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; *&n; *  Refer to &lt;file:Documentation/arm/Sharp-LH/SDRAM&gt; for more information.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xc0000000UL)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;4&t;/* Up to 16 nodes */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
macro_line|# ifdef CONFIG_LH7A40X_ONE_BANK_PER_NODE
DECL|macro|KVADDR_TO_NID
macro_line|#  define KVADDR_TO_NID(addr) &bslash;&n;  (  ((((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; 24) &amp;  1)&bslash;&n;   | ((((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; 25) &amp; ~1))
macro_line|# else  /* 2 banks per node */
DECL|macro|KVADDR_TO_NID
macro_line|#  define KVADDR_TO_NID(addr) &bslash;&n;      (((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; 26)
macro_line|# endif
multiline_comment|/*&n; * Given a page frame number, convert it to a node id.&n; */
macro_line|# ifdef CONFIG_LH7A40X_ONE_BANK_PER_NODE
DECL|macro|PFN_TO_NID
macro_line|#  define PFN_TO_NID(pfn) &bslash;&n;  (((((pfn) - PHYS_PFN_OFFSET) &gt;&gt; (24 - PAGE_SHIFT)) &amp;  1)&bslash;&n; | ((((pfn) - PHYS_PFN_OFFSET) &gt;&gt; (25 - PAGE_SHIFT)) &amp; ~1))
macro_line|# else  /* 2 banks per node */
DECL|macro|PFN_TO_NID
macro_line|#  define PFN_TO_NID(pfn) &bslash;&n;    (((pfn) - PHYS_PFN_OFFSET) &gt;&gt; (26 - PAGE_SHIFT))
macro_line|#endif
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and return the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
macro_line|# define ADDR_TO_MAPBASE(kaddr)&t;NODE_MEM_MAP(KVADDR_TO_NID(kaddr))
multiline_comment|/*&n; * Given a page frame number, find the owning node of the memory&n; * and return the mem_map of that node.&n; */
DECL|macro|PFN_TO_MAPBASE
macro_line|# define PFN_TO_MAPBASE(pfn)&t;NODE_MEM_MAP(PFN_TO_NID(pfn))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
macro_line|# ifdef CONFIG_LH7A40X_ONE_BANK_PER_NODE
DECL|macro|LOCAL_MAP_NR
macro_line|#  define LOCAL_MAP_NR(addr) &bslash;&n;       (((unsigned long)(addr) &amp; 0x003fffff) &gt;&gt; PAGE_SHIFT)
macro_line|# else  /* 2 banks per node */
DECL|macro|LOCAL_MAP_NR
macro_line|#  define LOCAL_MAP_NR(addr) &bslash;&n;       (((unsigned long)(addr) &amp; 0x01ffffff) &gt;&gt; PAGE_SHIFT)
macro_line|# endif
macro_line|#else
DECL|macro|PFN_TO_NID
macro_line|# define PFN_TO_NID(addr)&t;(0)
macro_line|#endif
macro_line|#endif
eof
