multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; *&n; * PowerPC64 port:&n; * Copyright (C) 2002 Anton Blanchard, IBM Corp.&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
DECL|struct|plat_pglist_data
r_typedef
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
DECL|typedef|plat_pg_data_t
)brace
id|plat_pg_data_t
suffix:semicolon
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
r_extern
id|plat_pg_data_t
id|plat_node_data
(braket
)braket
suffix:semicolon
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES 4
multiline_comment|/* XXX grab this from the device tree - Anton */
DECL|macro|MEMORY_ZONE_BITS
mdefine_line|#define MEMORY_ZONE_BITS&t;33
DECL|macro|CPU_SHIFT_BITS
mdefine_line|#define CPU_SHIFT_BITS          1
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa)&t;&t;((pa) &gt;&gt; MEMORY_ZONE_BITS)
DECL|macro|PLAT_NODE_DATA
mdefine_line|#define PLAT_NODE_DATA(n)&t;&t;(&amp;plat_node_data[(n)])
DECL|macro|PLAT_NODE_DATA_STARTNR
mdefine_line|#define PLAT_NODE_DATA_STARTNR(n)&t;&bslash;&n;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_start_mapnr)
DECL|macro|PLAT_NODE_DATA_SIZE
mdefine_line|#define PLAT_NODE_DATA_SIZE(n)&t;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_size)
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(p, n)&t;&bslash;&n;&t;(((p) &gt;&gt; PAGE_SHIFT) - PLAT_NODE_DATA(n)-&gt;gendata.node_start_pfn)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;PHYSADDR_TO_NID(__pa(kaddr))
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(n)&t;(&amp;((PLAT_NODE_DATA(n))-&gt;gendata))
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr) &bslash;&n;&t;((unsigned long)__va(NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;node_start_pfn &lt;&lt; PAGE_SHIFT))
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR(kvaddr)) &gt;&gt; PAGE_SHIFT)
macro_line|#if 0
multiline_comment|/* XXX fix - Anton */
mdefine_line|#define kern_addr_valid(kaddr)&t;test_bit(LOCAL_MAP_NR(kaddr), &bslash;&n;&t;&t;&t;&t;&t; NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;valid_addr_bitmap)
macro_line|#endif
DECL|macro|discontigmem_pfn_to_page
mdefine_line|#define discontigmem_pfn_to_page(pfn) &bslash;&n;({ &bslash;&n;&t;unsigned long kaddr = (unsigned long)__va(pfn &lt;&lt; PAGE_SHIFT); &bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr)); &bslash;&n;})
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/* XXX grab this from the device tree - Anton */
DECL|macro|cputonode
mdefine_line|#define cputonode(cpu)&t;((cpu) &gt;&gt; CPU_SHIFT_BITS)
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;cputonode(smp_processor_id())
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
