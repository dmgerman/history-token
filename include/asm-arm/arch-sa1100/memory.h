multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/memory.h&n; *&n; * Copyright (C) 1999-2000 Nicolas Pitre &lt;nico@cam.org&gt;&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x04000000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xc0000000UL)
multiline_comment|/*&n; * Physical DRAM offset is 0xc0000000 on the SA1100&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xc0000000UL)
multiline_comment|/*&n; * We take advantage of the fact that physical and virtual address can be the&n; * same.  The NUMA code is handling the large holes that might exist between&n; * all memory banks.&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(x)&t;(x)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(x)&t;(x)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; *&n; * On the SA1100, bus addresses are equivalent to physical addresses.&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Because of the wide memory address space between physical RAM banks on the &n; * SA1100, it&squot;s much convenient to use Linux&squot;s NUMA support to implement our &n; * memory map representation.  Assuming all memory nodes have equal access &n; * characteristics, we then have generic discontigous memory support.&n; *&n; * Of course, all this isn&squot;t mandatory for SA1100 implementations with only&n; * one used memory bank.  For those, simply undefine CONFIG_DISCONTIGMEM.&n; *&n; * The nodes are matched with the physical memory bank addresses which are &n; * incidentally the same as virtual addresses.&n; * &n; * &t;node 0:  0xc0000000 - 0xc7ffffff&n; * &t;node 1:  0xc8000000 - 0xcfffffff&n; * &t;node 2:  0xd0000000 - 0xd7ffffff&n; * &t;node 3:  0xd8000000 - 0xdfffffff&n; */
DECL|macro|NR_NODES
mdefine_line|#define NR_NODES&t;4
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(addr) (((unsigned long)(addr) - PAGE_OFFSET) &gt;&gt; 27)
multiline_comment|/*&n; * Given a page frame number, convert it to a node id.&n; */
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(pfn)&t;&t;(((pfn) - PHYS_PFN_OFFSET) &gt;&gt; (27 - PAGE_SHIFT))
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and return the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr)&t;NODE_MEM_MAP(KVADDR_TO_NID(kaddr))
multiline_comment|/*&n; * Given a page frame number, find the owning node of the memory&n; * and return the mem_map of that node.&n; */
DECL|macro|PFN_TO_MAPBASE
mdefine_line|#define PFN_TO_MAPBASE(pfn)&t;NODE_MEM_MAP(PFN_TO_NID(pfn))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(addr) &bslash;&n;&t;(((unsigned long)(addr) &amp; 0x07ffffff) &gt;&gt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(addr)&t;(0)
macro_line|#endif
macro_line|#endif
eof
