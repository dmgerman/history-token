macro_line|#ifndef _ASM_IA64_SN_MMZONE_SN1_H
DECL|macro|_ASM_IA64_SN_MMZONE_SN1_H
mdefine_line|#define _ASM_IA64_SN_MMZONE_SN1_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * SGI SN1 Arch defined values&n; *&n; * &t;An SN1 physical address is broken down as follows:&n; *&n; *             +-----------------------------------------+&n; *             |         |    |      |   node offset     |&n; *             | unused  | AS | node |-------------------|&n; *             |         |    |      | cn | clump offset |&n; *             +-----------------------------------------+&n; *              6       4 4  4 3    3 3  3 2            0&n; *              3       4 3  0 9    3 2  0 9            0&n; *&n; *&t;&t;bits 63-44&t;Unused - must be zero&n; *&t;&t;bits 43-40&t;Address space ID. Cached memory has a value of 0.&n; *&t;&t;&t;&t;Chipset &amp; IO addresses have non-zero values.&n; *&t;&t;bits 39-33&t;Node number. Note that some configurations do NOT&n; *&t;&t;&t;&t;have a node zero.&n; *&t;&t;bits 32-0&t;Node offset.&n; *&n; *&t;The node offset can be further broken down as:&n; *&t;&t;bits 32-30&t;Clump (bank) number.&n; *&t;&t;bits 29-0&t;Clump (bank) offset.&n; *&n; *&t;A node consists of up to 8 clumps (banks) of memory. A clump may be empty, or may be&n; *&t;populated with a single contiguous block of memory starting at clump&n; *&t;offset 0. The size of the block is (2**n) * 64MB, where 0&lt;n&lt;5.&n; *&n; *&n; * NOTE: This file exports symbols prefixed with &quot;PLAT_&quot;. Symbols prefixed with&n; *&t; &quot;SN_&quot; are intended for internal use only and should not be used in&n; *&t; any platform independent code. &n; *&n; *&t; This file is also responsible for exporting the following definitions:&n; *&t;&t;cnodeid_t&t;Define a compact node id. &n; */
DECL|typedef|cnodeid_t
r_typedef
r_int
r_int
id|cnodeid_t
suffix:semicolon
DECL|macro|SN1_BANKS_PER_NODE
mdefine_line|#define SN1_BANKS_PER_NODE&t;&t;8
DECL|macro|SN1_NODE_SIZE
mdefine_line|#define SN1_NODE_SIZE&t;&t;&t;(8UL*1024*1024*1024)&t;/* 8 GB per node */
DECL|macro|SN1_BANK_SIZE
mdefine_line|#define SN1_BANK_SIZE&t;&t;&t;(SN1_NODE_SIZE/SN1_BANKS_PER_NODE)
DECL|macro|SN1_NODE_SHIFT
mdefine_line|#define SN1_NODE_SHIFT&t;&t;&t;33
DECL|macro|SN1_NODE_MASK
mdefine_line|#define SN1_NODE_MASK&t;&t;&t;0x7fUL
DECL|macro|SN1_NODE_OFFSET_MASK
mdefine_line|#define SN1_NODE_OFFSET_MASK&t;&t;(SN1_NODE_SIZE-1)
DECL|macro|SN1_NODE_NUMBER
mdefine_line|#define SN1_NODE_NUMBER(addr)&t;&t;(((unsigned long)(addr) &gt;&gt; SN1_NODE_SHIFT) &amp; SN1_NODE_MASK)
DECL|macro|SN1_NODE_CLUMP_NUMBER
mdefine_line|#define SN1_NODE_CLUMP_NUMBER(addr)&t;(((unsigned long)(addr) &gt;&gt;30) &amp; 7)
DECL|macro|SN1_NODE_OFFSET
mdefine_line|#define SN1_NODE_OFFSET(addr)&t;&t;(((unsigned long)(addr)) &amp; SN1_NODE_OFFSET_MASK)
DECL|macro|SN1_KADDR
mdefine_line|#define SN1_KADDR(nasid, offset)&t;(((unsigned long)(nasid)&lt;&lt;SN1_NODE_SHIFT) | (offset) | PAGE_OFFSET)
DECL|macro|PLAT_MAX_NODE_NUMBER
mdefine_line|#define PLAT_MAX_NODE_NUMBER&t;&t;128&t;&t;&t;/* Maximum node number +1 */
DECL|macro|PLAT_MAX_COMPACT_NODES
mdefine_line|#define PLAT_MAX_COMPACT_NODES&t;&t;128&t;&t;&t;/* Maximum number of nodes in SSI */
DECL|macro|PLAT_MAX_PHYS_MEMORY
mdefine_line|#define PLAT_MAX_PHYS_MEMORY&t;&t;(1UL &lt;&lt; 40)
multiline_comment|/*&n; * On the SN platforms, a clump is the same as a memory bank.&n; */
DECL|macro|PLAT_CLUMPS_PER_NODE
mdefine_line|#define PLAT_CLUMPS_PER_NODE&t;&t;SN1_BANKS_PER_NODE
DECL|macro|PLAT_CLUMP_OFFSET
mdefine_line|#define PLAT_CLUMP_OFFSET(addr)&t;&t;((unsigned long)(addr) &amp; 0x3fffffffUL)
DECL|macro|PLAT_CLUMPSIZE
mdefine_line|#define PLAT_CLUMPSIZE                  (SN1_NODE_SIZE/PLAT_CLUMPS_PER_NODE)
DECL|macro|PLAT_MAXCLUMPS
mdefine_line|#define PLAT_MAXCLUMPS&t;&t;&t;(PLAT_CLUMPS_PER_NODE*PLAT_MAX_COMPACT_NODES)
multiline_comment|/*&n; * PLAT_VALID_MEM_KADDR returns a boolean to indicate if a kaddr is potentially a&n; * valid cacheable identity mapped RAM memory address.&n; * Note that the RAM may or may not actually be present!!&n; */
DECL|macro|SN1_VALID_KERN_ADDR_MASK
mdefine_line|#define SN1_VALID_KERN_ADDR_MASK&t;0xffffff0000000000UL
DECL|macro|SN1_VALID_KERN_ADDR_VALUE
mdefine_line|#define SN1_VALID_KERN_ADDR_VALUE&t;0xe000000000000000UL
DECL|macro|PLAT_VALID_MEM_KADDR
mdefine_line|#define PLAT_VALID_MEM_KADDR(kaddr)&t;(((unsigned long)(kaddr) &amp; SN1_VALID_KERN_ADDR_MASK) == SN1_VALID_KERN_ADDR_VALUE)
multiline_comment|/*&n; * Memory is conceptually divided into chunks. A chunk is either&n; * completely present, or else the kernel assumes it is completely&n; * absent. Each node consists of a number of possibly discontiguous chunks.&n; */
DECL|macro|SN1_CHUNKSHIFT
mdefine_line|#define SN1_CHUNKSHIFT&t;&t;&t;26&t;&t;&t;/* 64 MB */
DECL|macro|SN1_CHUNKSIZE
mdefine_line|#define SN1_CHUNKSIZE&t;&t;&t;(1UL &lt;&lt; SN1_CHUNKSHIFT)
DECL|macro|PLAT_CHUNKNUM
mdefine_line|#define PLAT_CHUNKNUM(addr)&t;&t;(((addr) &amp; (PLAT_MAX_PHYS_MEMORY-1)) &gt;&gt; SN1_CHUNKSHIFT)
multiline_comment|/*&n; * Given a kaddr, find the nid (compact nodeid)&n; */
macro_line|#ifdef CONFIG_IA64_SGI_SN_DEBUG
DECL|macro|DISCONBUG
mdefine_line|#define DISCONBUG(kaddr)&t;&t;panic(&quot;DISCONTIG BUG: line %d, %s. kaddr 0x%lx&quot;,&t; &t;&bslash;&n;&t;&t;&t;&t;&t;&t;__LINE__, __FILE__, (long)(kaddr))
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;&t;({long _ktn=(long)(kaddr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;kern_addr_valid(_ktn) ? &t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;local_node_data-&gt;physical_node_map[SN1_NODE_NUMBER(_ktn)] :&bslash;&n;&t;&t;&t;&t;&t;&t;(DISCONBUG(_ktn), 0UL);})
macro_line|#else
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;&t;(local_node_data-&gt;physical_node_map[SN1_NODE_NUMBER(kaddr)])
macro_line|#endif
multiline_comment|/*&n; * Given a kaddr, find the index into the clump_mem_map_base array of the page struct entry&n; * for the first page of the clump.&n; */
DECL|macro|PLAT_CLUMP_MEM_MAP_INDEX
mdefine_line|#define PLAT_CLUMP_MEM_MAP_INDEX(kaddr)&t;&t;({long _kmmi=(long)(kaddr);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;KVADDR_TO_NID(_kmmi) * PLAT_CLUMPS_PER_NODE +&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;SN1_NODE_CLUMP_NUMBER(_kmmi);})
multiline_comment|/*&n; * Calculate a &quot;goal&quot; value to be passed to __alloc_bootmem_node for allocating structures on&n; * nodes so that they dont alias to the same line in the cache as the previous allocated structure.&n; * This macro takes an address of the end of previous allocation, rounds it to a page boundary &amp; &n; * changes the node number.&n; */
DECL|macro|PLAT_BOOTMEM_ALLOC_GOAL
mdefine_line|#define PLAT_BOOTMEM_ALLOC_GOAL(cnode,kaddr)&t;SN1_KADDR(PLAT_PXM_TO_PHYS_NODE_NUMBER(nid_to_pxm_map[cnodeid]),&t;&bslash;&n;&t;&t;&t;&t;&t;&t;  (SN1_NODE_OFFSET(kaddr) + PAGE_SIZE - 1) &gt;&gt; PAGE_SHIFT &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Convert a proximity domain number (from the ACPI tables) into a physical node number.&n; */
DECL|macro|PLAT_PXM_TO_PHYS_NODE_NUMBER
mdefine_line|#define PLAT_PXM_TO_PHYS_NODE_NUMBER(pxm)&t;(pxm)
macro_line|#endif /* _ASM_IA64_SN_MMZONE_SN1_H */
eof
