multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/memory.h&n; *&n; * Copyright (C) 1999-2000 Nicolas Pitre &lt;nico@cam.org&gt;&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
multiline_comment|/*&n; * Physical DRAM offset is 0xc0000000 on the SA1100&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xc0000000UL)
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_SA1111
r_static
r_inline
r_void
DECL|function|__arch_adjust_zones
id|__arch_adjust_zones
c_func
(paren
r_int
id|node
comma
r_int
r_int
op_star
id|size
comma
r_int
r_int
op_star
id|holes
)paren
(brace
r_int
r_int
id|sz
op_assign
id|SZ_1M
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|node
op_ne
l_int|0
)paren
id|sz
op_assign
l_int|0
suffix:semicolon
id|size
(braket
l_int|1
)braket
op_assign
id|size
(braket
l_int|0
)braket
op_minus
id|sz
suffix:semicolon
id|size
(braket
l_int|0
)braket
op_assign
id|sz
suffix:semicolon
)brace
DECL|macro|arch_adjust_zones
mdefine_line|#define arch_adjust_zones(node, size, holes) &bslash;&n;&t;__arch_adjust_zones(node, size, holes)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(PHYS_OFFSET + SZ_1M - 1)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; *&n; * On the SA1100, bus addresses are equivalent to physical addresses.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t; __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t; __phys_to_virt(x)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Because of the wide memory address space between physical RAM banks on the &n; * SA1100, it&squot;s much convenient to use Linux&squot;s NUMA support to implement our &n; * memory map representation.  Assuming all memory nodes have equal access &n; * characteristics, we then have generic discontiguous memory support.&n; *&n; * Of course, all this isn&squot;t mandatory for SA1100 implementations with only&n; * one used memory bank.  For those, simply undefine CONFIG_DISCONTIGMEM.&n; *&n; * The nodes are matched with the physical memory bank addresses which are &n; * incidentally the same as virtual addresses.&n; * &n; * &t;node 0:  0xc0000000 - 0xc7ffffff&n; * &t;node 1:  0xc8000000 - 0xcfffffff&n; * &t;node 2:  0xd0000000 - 0xd7ffffff&n; * &t;node 3:  0xd8000000 - 0xdfffffff&n; */
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
