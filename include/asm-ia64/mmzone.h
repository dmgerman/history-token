multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2002 NEC Corp.&n; * Copyright (c) 2002 Erich Focht &lt;efocht@ess.nec.de&gt;&n; * Copyright (c) 2002 Kimio Suganuma &lt;k-suganuma@da.jp.nec.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_MMZONE_H
DECL|macro|_ASM_IA64_MMZONE_H
mdefine_line|#define _ASM_IA64_MMZONE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Given a kaddr, find the base mem_map address for the start of the mem_map&n; * entries for the bank containing the kaddr.&n; */
DECL|macro|BANK_MEM_MAP_BASE
mdefine_line|#define BANK_MEM_MAP_BASE(kaddr) local_node_data-&gt;bank_mem_map_base[BANK_MEM_MAP_INDEX(kaddr)]
multiline_comment|/*&n; * Given a kaddr, this macro return the relative map number &n; * within the bank.&n; */
DECL|macro|BANK_MAP_NR
mdefine_line|#define BANK_MAP_NR(kaddr) &t;(BANK_OFFSET(kaddr) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Given a pte, this macro returns a pointer to the page struct for the pte.&n; */
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;virt_to_page(PAGE_OFFSET | (pte_val(pte)&amp;_PFN_MASK))
multiline_comment|/*&n; * Determine if a kaddr is a valid memory address of memory that&n; * actually exists. &n; *&n; * The check consists of 2 parts:&n; *&t;- verify that the address is a region 7 address &amp; does not &n; *&t;  contain any bits that preclude it from being a valid platform&n; *&t;  memory address&n; *&t;- verify that the chunk actually exists.&n; *&n; * Note that IO addresses are NOT considered valid addresses.&n; *&n; * Note, many platforms can simply check if kaddr exceeds a specific size.  &n; *&t;(However, this won&squot;t work on SGI platforms since IO space is embedded &n; * &t;within the range of valid memory addresses &amp; nodes have holes in the &n; *&t;address range between banks). &n; */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;&t;({long _kav=(long)(kaddr);&t;&bslash;&n;&t;&t;&t;&t;&t;VALID_MEM_KADDR(_kav);})
multiline_comment|/*&n; * Given a kaddr, return a pointer to the page struct for the page.&n; * If the kaddr does not represent RAM memory that potentially exists, return&n; * a pointer the page struct for max_mapnr. IO addresses will&n; * return the page for max_nr. Addresses in unpopulated RAM banks may&n; * return undefined results OR may panic the system.&n; *&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;({long _kvtp=(long)(kaddr);&t;&bslash;&n;&t;&t;&t;&t;(VALID_MEM_KADDR(_kvtp))&t;&bslash;&n;&t;&t;&t;&t;&t;? BANK_MEM_MAP_BASE(_kvtp) + BANK_MAP_NR(_kvtp)&t;&bslash;&n;&t;&t;&t;&t;&t;: NULL;})
multiline_comment|/*&n; * Given a page struct entry, return the physical address that the page struct represents.&n; * Since IA64 has all memory in the DMA zone, the following works:&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;__pa(page_address(page))
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;((pfn) - NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(struct page *)(node_mem_map(pfn_to_nid(pfn)) + node_localnr(pfn, pfn_to_nid(pfn)))
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t; local_node_data-&gt;node_id_map[(pfn &lt;&lt; PAGE_SHIFT) &gt;&gt; BANKSHIFT]
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;(long)((page - page_zone(page)-&gt;zone_mem_map) + page_zone(page)-&gt;zone_start_pfn)
multiline_comment|/*&n; * pfn_valid should be made as fast as possible, and the current definition&n; * is valid for machines that are NUMA, but still contiguous, which is what&n; * is currently supported. A more generalised, but slower definition would&n; * be something like this - mbligh:&n; * ( pfn_to_pgdat(pfn) &amp;&amp; (pfn &lt; node_end_pfn(pfn_to_nid(pfn))) )&n; */
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)          (pfn &lt; max_low_pfn)
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_DIG
multiline_comment|/*&n; * Platform definitions for DIG platform with contiguous memory.&n; */
DECL|macro|MAX_PHYSNODE_ID
mdefine_line|#define MAX_PHYSNODE_ID&t;8&t;/* Maximum node number +1 */
DECL|macro|NR_NODES
mdefine_line|#define NR_NODES&t;8&t;/* Maximum number of nodes in SSI */
DECL|macro|MAX_PHYS_MEMORY
mdefine_line|#define MAX_PHYS_MEMORY&t;(1UL &lt;&lt; 40)&t;/* 1 TB */
multiline_comment|/*&n; * Bank definitions.&n; * Configurable settings for DIG: 512MB/bank:  16GB/node,&n; *                               2048MB/bank:  64GB/node,&n; *                               8192MB/bank: 256GB/node.&n; */
DECL|macro|NR_BANKS_PER_NODE
mdefine_line|#define NR_BANKS_PER_NODE&t;32
macro_line|#if defined(CONFIG_IA64_NODESIZE_16GB)
DECL|macro|BANKSHIFT
macro_line|# define BANKSHIFT&t;&t;29
macro_line|#elif defined(CONFIG_IA64_NODESIZE_64GB)
DECL|macro|BANKSHIFT
macro_line|# define BANKSHIFT&t;&t;31
macro_line|#elif defined(CONFIG_IA64_NODESIZE_256GB)
DECL|macro|BANKSHIFT
macro_line|# define BANKSHIFT&t;&t;33
macro_line|#else
macro_line|# error Unsupported bank and nodesize!
macro_line|#endif
DECL|macro|BANKSIZE
mdefine_line|#define BANKSIZE&t;&t;(1UL &lt;&lt; BANKSHIFT)
DECL|macro|BANK_OFFSET
mdefine_line|#define BANK_OFFSET(addr)&t;((unsigned long)(addr) &amp; (BANKSIZE-1))
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS&t;&t;(NR_BANKS_PER_NODE * NR_NODES)
multiline_comment|/*&n; * VALID_MEM_KADDR returns a boolean to indicate if a kaddr is&n; * potentially a valid cacheable identity mapped RAM memory address.&n; * Note that the RAM may or may not actually be present!!&n; */
DECL|macro|VALID_MEM_KADDR
mdefine_line|#define VALID_MEM_KADDR(kaddr)&t;1
multiline_comment|/*&n; * Given a nodeid &amp; a bank number, find the address of the mem_map&n; * entry for the first page of the bank.&n; */
DECL|macro|BANK_MEM_MAP_INDEX
mdefine_line|#define BANK_MEM_MAP_INDEX(kaddr) &bslash;&n;&t;(((unsigned long)(kaddr) &amp; (MAX_PHYS_MEMORY-1)) &gt;&gt; BANKSHIFT)
macro_line|#elif defined(CONFIG_IA64_SGI_SN2)
multiline_comment|/*&n; * SGI SN2 discontig definitions&n; */
DECL|macro|MAX_PHYSNODE_ID
mdefine_line|#define MAX_PHYSNODE_ID&t;2048&t;/* 2048 node ids (also called nasid) */
DECL|macro|NR_NODES
mdefine_line|#define NR_NODES&t;128&t;/* Maximum number of nodes in SSI */
DECL|macro|MAX_PHYS_MEMORY
mdefine_line|#define MAX_PHYS_MEMORY&t;(1UL &lt;&lt; 49)
DECL|macro|BANKSHIFT
mdefine_line|#define BANKSHIFT&t;&t;38
DECL|macro|NR_BANKS_PER_NODE
mdefine_line|#define NR_BANKS_PER_NODE&t;4
DECL|macro|SN2_NODE_SIZE
mdefine_line|#define SN2_NODE_SIZE&t;&t;(64UL*1024*1024*1024)&t;/* 64GB per node */
DECL|macro|BANKSIZE
mdefine_line|#define BANKSIZE&t;&t;(SN2_NODE_SIZE/NR_BANKS_PER_NODE)
DECL|macro|BANK_OFFSET
mdefine_line|#define BANK_OFFSET(addr)&t;((unsigned long)(addr) &amp; (BANKSIZE-1))
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS&t;&t;(NR_BANKS_PER_NODE * NR_NODES)
DECL|macro|VALID_MEM_KADDR
mdefine_line|#define VALID_MEM_KADDR(kaddr)&t;1
multiline_comment|/*&n; * Given a nodeid &amp; a bank number, find the address of the mem_map&n; * entry for the first page of the bank.&n; */
DECL|macro|BANK_MEM_MAP_INDEX
mdefine_line|#define BANK_MEM_MAP_INDEX(kaddr) &bslash;&n;&t;(((unsigned long)(kaddr) &amp; (MAX_PHYS_MEMORY-1)) &gt;&gt; BANKSHIFT)
macro_line|#endif /* CONFIG_IA64_DIG */
macro_line|#endif /* _ASM_IA64_MMZONE_H */
eof
