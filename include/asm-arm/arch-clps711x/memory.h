multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/mmu.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
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
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xc0000000UL)
multiline_comment|/*&n; * On integrator, the dram is contiguous&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((vpage) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((ppage) + PAGE_OFFSET - PHYS_OFFSET)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *              address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *              to an address that the kernel can use.&n; */
macro_line|#if defined(CONFIG_ARCH_CDB89712)
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(x)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;(x)
macro_line|#elif defined (CONFIG_ARCH_AUTCPU12)
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(x)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;(x)
macro_line|#else
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;((x) - PAGE_OFFSET)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;((x) + PAGE_OFFSET)
macro_line|#endif
multiline_comment|/*&n; * Like the SA1100, the EDB7211 has a large gap between physical RAM&n; * banks.  In 2.2, the Psion (CL-PS7110) port added custom support for&n; * discontiguous physical memory.  In 2.4, we can use the standard&n; * Linux NUMA support.&n; *&n; * This is not necessary for EP7211 implementations with only one used&n; * memory bank.  For those systems, simply undefine CONFIG_DISCONTIGMEM.&n; */
macro_line|#ifdef CONFIG_ARCH_EDB7211
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Because of the wide memory address space between physical RAM banks on the &n; * SA1100, it&squot;s much more convenient to use Linux&squot;s NUMA support to implement&n; * our memory map representation.  Assuming all memory nodes have equal access &n; * characteristics, we then have generic discontigous memory support.&n; *&n; * Of course, all this isn&squot;t mandatory for SA1100 implementations with only&n; * one used memory bank.  For those, simply undefine CONFIG_DISCONTIGMEM.&n; *&n; * The nodes are matched with the physical memory bank addresses which are &n; * incidentally the same as virtual addresses.&n; * &n; * &t;node 0:  0xc0000000 - 0xc7ffffff&n; * &t;node 1:  0xc8000000 - 0xcfffffff&n; * &t;node 2:  0xd0000000 - 0xd7ffffff&n; * &t;node 3:  0xd8000000 - 0xdfffffff&n; */
DECL|macro|NR_NODES
mdefine_line|#define NR_NODES&t;4
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(addr) &bslash;&n;&t;&t;(((unsigned long)(addr) - PAGE_OFFSET) &gt;&gt; NODE_MAX_MEM_SHIFT)
multiline_comment|/*&n; * Given a physical address, convert it to a node id.&n; */
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr) KVADDR_TO_NID(__phys_to_virt(addr))
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MAR_NR finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kaddr) &bslash;&n;&t;(((unsigned long)(kaddr)-LOCAL_BASE_ADDR((kaddr))) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Given a kaddr, virt_to_page returns a pointer to the corresponding &n; * mem_map entry.&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr) &bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
multiline_comment|/*&n; * VALID_PAGE returns a non-zero value if given page pointer is valid.&n; * This assumes all node&squot;s mem_maps are stored within the node they refer to.&n; */
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page) &bslash;&n;({ unsigned int node = KVADDR_TO_NID(page); &bslash;&n;   ( (node &lt; NR_NODES) &amp;&amp; &bslash;&n;     ((unsigned)((page) - NODE_MEM_MAP(node)) &lt; NODE_DATA(node)-&gt;node_size) ); &bslash;&n;})
multiline_comment|/*&n; * The PS7211 allows up to 256MB max per DRAM bank, but the EDB7211&n; * uses only one of the two banks (bank #1).  However, even within&n; * bank #1, memory is discontiguous.&n; *&n; * The EDB7211 has two 8MB DRAM areas with 8MB of empty space between&n; * them, so we use 24 for the node max shift to get 16MB node sizes.&n; */
DECL|macro|NODE_MAX_MEM_SHIFT
mdefine_line|#define NODE_MAX_MEM_SHIFT&t;24
DECL|macro|NODE_MAX_MEM_SIZE
mdefine_line|#define NODE_MAX_MEM_SIZE&t;(1&lt;&lt;NODE_MAX_MEM_SHIFT)
multiline_comment|/*&n; * Given a mem_map_t, LOCAL_MAP_BASE finds the owning node for the&n; * physical page and returns the kaddr for the mem_map of that node.&n; */
DECL|macro|LOCAL_MAP_BASE
mdefine_line|#define LOCAL_MAP_BASE(page) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(page)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;((unsigned long)(kaddr) &amp; ~(NODE_MAX_MEM_SIZE-1))
multiline_comment|/* &n; * With discontigmem, the conceptual mem_map array starts from PAGE_OFFSET.&n; * Given a kaddr, MAP_NR returns the appropriate global mem_map index so &n; * it matches the corresponding node&squot;s local mem_map.&n; */
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(kaddr)&t;(LOCAL_MAP_NR((kaddr)) + &bslash;&n;&t;&t;(((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;&t;&t;sizeof(mem_map_t)))
macro_line|#else
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif&t;/* CONFIG_ARCH_EDB7211 */
macro_line|#ifndef PHYS_TO_NID
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
macro_line|#endif
eof
