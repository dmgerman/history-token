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
mdefine_line|#define KVADDR_TO_NID(addr) &bslash;&n;&t;&t;(((unsigned long)(addr) - 0xc0000000) &gt;&gt; 27)
multiline_comment|/*&n; * Given a physical address, convert it to a node id.&n; */
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr) KVADDR_TO_NID(__phys_to_virt(addr))
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr) &amp; 0x07ffffff) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Given a kaddr, virt_to_page returns a pointer to the corresponding &n; * mem_map entry.&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr) &bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
multiline_comment|/*&n; * VALID_PAGE returns a non-zero value if given page pointer is valid.&n; * This assumes all node&squot;s mem_maps are stored within the node they refer to.&n; */
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page) &bslash;&n;({ unsigned int node = KVADDR_TO_NID(page); &bslash;&n;   ( (node &lt; NR_NODES) &amp;&amp; &bslash;&n;     ((unsigned)((page) - NODE_MEM_MAP(node)) &lt; NODE_DATA(node)-&gt;node_size) ); &bslash;&n;})
macro_line|#else
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
macro_line|#endif
eof
