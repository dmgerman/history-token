macro_line|#ifndef _ASM_IA64_SN_MMZONE_SN2_H
DECL|macro|_ASM_IA64_SN_MMZONE_SN2_H
mdefine_line|#define _ASM_IA64_SN_MMZONE_SN2_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * SGI SN2 Arch defined values&n; *&n; * &t;An SN2 physical address is broken down as follows:&n; *&n; *             +-----------------------------------------+&n; *             |         |      |    |   node offset     |&n; *             | unused  | node | AS |-------------------|&n; *             |         |      |    | cn | clump offset |&n; *             +-----------------------------------------+&n; *              6       4 4    3 3  3 3  3 3            0&n; *              3       9 8    8 7  6 5  4 3            0&n; *&n; *&t;&t;bits 63-49&t;Unused - must be zero&n; *&t;&t;bits 48-38&t;Node number. Note that some configurations do NOT&n; *&t;&t;&t;&t;have a node zero.&n; *&t;&t;bits 37-36&t;Address space ID. Cached memory has a value of 3 (!!!).&n; *&t;&t;&t;&t;Chipset &amp; IO addresses have other values.&n; *&t;&t;&t;&t;  (Yikes!! The hardware folks hate us...)&n; *&t;&t;bits 35-0&t;Node offset.&n; *&n; *&t;The node offset can be further broken down as:&n; *&t;&t;bits 35-34&t;Clump (bank) number.&n; *&t;&t;bits 33-0&t;Clump (bank) offset.&n; *&n; *&t;A node consists of up to 4 clumps (banks) of memory. A clump may be empty, or may be&n; *&t;populated with a single contiguous block of memory starting at clump&n; *&t;offset 0. The size of the block is (2**n) * 64MB, where 0&lt;n&lt;9.&n; *&n; *&t;Important notes:&n; *&t;&t;- IO space addresses are embedded with the range of valid memory addresses.&n; *&t;&t;- All cached memory addresses have bits 36 &amp; 37 set to 1&squot;s.&n; *&t;&t;- There is no physical address 0.&n; *&n; * NOTE: This file exports symbols prefixed with &quot;PLAT_&quot;. Symbols prefixed with&n; *&t; &quot;SN_&quot; are intended for internal use only and should not be used in&n; *&t; any platform independent code. &n; *&n; *&t; This file is also responsible for exporting the following definitions:&n; *&t;&t;cnodeid_t&t;Define a compact node id. &n; */
DECL|typedef|cnodeid_t
r_typedef
r_int
r_int
id|cnodeid_t
suffix:semicolon
DECL|macro|SN2_BANKS_PER_NODE
mdefine_line|#define SN2_BANKS_PER_NODE&t;&t;4
DECL|macro|SN2_NODE_SIZE
mdefine_line|#define SN2_NODE_SIZE&t;&t;&t;(64UL*1024*1024*1024)&t;/* 64GB per node */
DECL|macro|SN2_BANK_SIZE
mdefine_line|#define SN2_BANK_SIZE&t;&t;&t;(SN2_NODE_SIZE/SN2_BANKS_PER_NODE)
DECL|macro|SN2_NODE_SHIFT
mdefine_line|#define SN2_NODE_SHIFT&t;&t;&t;38
DECL|macro|SN2_NODE_MASK
mdefine_line|#define SN2_NODE_MASK&t;&t;&t;0x7ffUL
DECL|macro|SN2_NODE_OFFSET_MASK
mdefine_line|#define SN2_NODE_OFFSET_MASK&t;&t;(SN2_NODE_SIZE-1)
DECL|macro|SN2_NODE_NUMBER
mdefine_line|#define SN2_NODE_NUMBER(addr)&t;&t;(((unsigned long)(addr) &gt;&gt; SN2_NODE_SHIFT) &amp; SN2_NODE_MASK)
DECL|macro|SN2_NODE_CLUMP_NUMBER
mdefine_line|#define SN2_NODE_CLUMP_NUMBER(kaddr)&t;(((unsigned long)(kaddr) &gt;&gt;34) &amp; 3)
DECL|macro|SN2_NODE_OFFSET
mdefine_line|#define SN2_NODE_OFFSET(addr)&t;&t;(((unsigned long)(addr)) &amp; SN2_NODE_OFFSET_MASK)
DECL|macro|SN2_KADDR
mdefine_line|#define SN2_KADDR(nasid, offset)&t;(((unsigned long)(nasid)&lt;&lt;SN2_NODE_SHIFT) | (offset) | SN2_PAGE_OFFSET)
DECL|macro|SN2_PAGE_OFFSET
mdefine_line|#define SN2_PAGE_OFFSET&t;&t;&t;0xe000003000000000UL      /* Cacheable memory space */
DECL|macro|PLAT_MAX_NODE_NUMBER
mdefine_line|#define PLAT_MAX_NODE_NUMBER&t;&t;2048&t;&t;&t;/* Maximum node number + 1 */
DECL|macro|PLAT_MAX_COMPACT_NODES
mdefine_line|#define PLAT_MAX_COMPACT_NODES&t;&t;128&t;&t;&t;/* Maximum number of nodes in SSI system */
DECL|macro|PLAT_MAX_PHYS_MEMORY
mdefine_line|#define PLAT_MAX_PHYS_MEMORY&t;&t;(1UL &lt;&lt; 49)
multiline_comment|/*&n; * On the SN platforms, a clump is the same as a memory bank.&n; */
DECL|macro|PLAT_CLUMPS_PER_NODE
mdefine_line|#define PLAT_CLUMPS_PER_NODE&t;&t;SN2_BANKS_PER_NODE
DECL|macro|PLAT_CLUMP_OFFSET
mdefine_line|#define PLAT_CLUMP_OFFSET(addr)&t;&t;((unsigned long)(addr) &amp; 0x3ffffffffUL)
DECL|macro|PLAT_CLUMPSIZE
mdefine_line|#define PLAT_CLUMPSIZE&t;&t;&t;(SN2_NODE_SIZE/PLAT_CLUMPS_PER_NODE)
DECL|macro|PLAT_MAXCLUMPS
mdefine_line|#define PLAT_MAXCLUMPS&t;&t;&t;(PLAT_CLUMPS_PER_NODE * PLAT_MAX_COMPACT_NODES)
multiline_comment|/*&n; * PLAT_VALID_MEM_KADDR returns a boolean to indicate if a kaddr is potentially a&n; * valid cacheable identity mapped RAM memory address.&n; * Note that the RAM may or may not actually be present!!&n; */
DECL|macro|SN2_VALID_KERN_ADDR_MASK
mdefine_line|#define SN2_VALID_KERN_ADDR_MASK&t;0xffff003000000000UL
DECL|macro|SN2_VALID_KERN_ADDR_VALUE
mdefine_line|#define SN2_VALID_KERN_ADDR_VALUE&t;0xe000003000000000UL
DECL|macro|PLAT_VALID_MEM_KADDR
mdefine_line|#define PLAT_VALID_MEM_KADDR(kaddr)&t;(((unsigned long)(kaddr) &amp; SN2_VALID_KERN_ADDR_MASK) == SN2_VALID_KERN_ADDR_VALUE)
multiline_comment|/*&n; * Memory is conceptually divided into chunks. A chunk is either&n; * completely present, or else the kernel assumes it is completely&n; * absent. Each node consists of a number of possibly contiguous chunks.&n; */
DECL|macro|SN2_CHUNKSHIFT
mdefine_line|#define SN2_CHUNKSHIFT&t;&t;&t;25&t;&t;&t;/* 32 MB */
DECL|macro|SN2_CHUNKSIZE
mdefine_line|#define SN2_CHUNKSIZE&t;&t;&t;(1UL &lt;&lt; SN2_CHUNKSHIFT)
DECL|macro|PLAT_CHUNKNUM
mdefine_line|#define PLAT_CHUNKNUM(addr)&t;&t;({unsigned long _p=(unsigned long)(addr);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;(((_p&amp;SN2_NODE_MASK)&gt;&gt;2) | &t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;(_p&amp;SN2_NODE_OFFSET_MASK)) &gt;&gt;SN2_CHUNKSHIFT;})
multiline_comment|/*&n; * Given a kaddr, find the nid (compact nodeid)&n; */
macro_line|#ifdef CONFIG_IA64_SGI_SN_DEBUG
DECL|macro|DISCONBUG
mdefine_line|#define DISCONBUG(kaddr)&t;&t;panic(&quot;DISCONTIG BUG: line %d, %s. kaddr 0x%lx&quot;,&t; &t;&bslash;&n;&t;&t;&t;&t;&t;&t;__LINE__, __FILE__, (long)(kaddr))
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;&t;({long _ktn=(long)(kaddr);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;kern_addr_valid(_ktn) ? &t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;local_node_data-&gt;physical_node_map[SN2_NODE_NUMBER(_ktn)] :&t;&bslash;&n;&t;&t;&t;&t;&t;&t;(DISCONBUG(_ktn), 0UL);})
macro_line|#else
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;&t;(local_node_data-&gt;physical_node_map[SN2_NODE_NUMBER(kaddr)])
macro_line|#endif
multiline_comment|/*&n; * Given a kaddr, find the index into the clump_mem_map_base array of the page struct entry &n; * for the first page of the clump.&n; */
DECL|macro|PLAT_CLUMP_MEM_MAP_INDEX
mdefine_line|#define PLAT_CLUMP_MEM_MAP_INDEX(kaddr)&t;&t;({long _kmmi=(long)(kaddr);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;KVADDR_TO_NID(_kmmi) * PLAT_CLUMPS_PER_NODE +&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;SN2_NODE_CLUMP_NUMBER(_kmmi);})
multiline_comment|/*&n; * Calculate a &quot;goal&quot; value to be passed to __alloc_bootmem_node for allocating structures on&n; * nodes so that they dont alias to the same line in the cache as the previous allocated structure.&n; * This macro takes an address of the end of previous allocation, rounds it to a page boundary &amp; &n; * changes the node number.&n; */
DECL|macro|PLAT_BOOTMEM_ALLOC_GOAL
mdefine_line|#define PLAT_BOOTMEM_ALLOC_GOAL(cnode,kaddr)&t;SN2_KADDR(PLAT_PXM_TO_PHYS_NODE_NUMBER(nid_to_pxm_map[cnodeid]),       &bslash;&n;&t;&t;&t;&t;&t;&t; (SN2_NODE_OFFSET(kaddr) + PAGE_SIZE - 1) &gt;&gt; PAGE_SHIFT &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Convert a proximity domain number (from the ACPI tables) into a physical node number.&n; *&t;Note: on SN2, the promity domain number is the same as bits [8:1] of the NASID. The following&n; *&t;algorithm relies on:&n; *&t;&t;- bit 0 of the NASID for cpu nodes is always 0&n; *&t;&t;- bits [10:9] of all NASIDs in a partition are always the same&n; *&t;&t;- hard_smp_processor_id return the SAPIC of the current cpu &amp;&n; *&t;&t;&t;bits 0..11 contain the NASID.&n; *&n; *&t;All of this complexity is because MS architectually limited proximity domain numbers to&n; *&t;8 bits. &n; */
DECL|macro|PLAT_PXM_TO_PHYS_NODE_NUMBER
mdefine_line|#define PLAT_PXM_TO_PHYS_NODE_NUMBER(pxm)&t;(((pxm)&lt;&lt;1) | (hard_smp_processor_id() &amp; 0x300))
macro_line|#endif /* _ASM_IA64_SN_MMZONE_SN2_H */
eof
