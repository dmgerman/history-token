multiline_comment|/*&n; * Written by Pat Gaughen (gone@us.ibm.com) Mar 2002&n; *&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/numaq.h&gt;
macro_line|#else
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa)&t;(0)
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(pfn)&t;&t;(0)
macro_line|#ifdef CONFIG_NUMA
DECL|macro|_cpu_to_node
mdefine_line|#define _cpu_to_node(cpu) 0
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#ifdef CONFIG_NUMA
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id() _cpu_to_node(smp_processor_id())
macro_line|#endif /* CONFIG_NUMA */
DECL|struct|plat_pglist_data
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|plat_pglist_data
op_star
id|plat_node_data
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
DECL|macro|reserve_bootmem
mdefine_line|#define reserve_bootmem(addr, size) &bslash;&n;&t;reserve_bootmem_node(NODE_DATA(0), (addr), (size))
DECL|macro|alloc_bootmem
mdefine_line|#define alloc_bootmem(x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), SMP_CACHE_BYTES, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_low
mdefine_line|#define alloc_bootmem_low(x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), SMP_CACHE_BYTES, 0)
DECL|macro|alloc_bootmem_pages
mdefine_line|#define alloc_bootmem_pages(x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), PAGE_SIZE, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_low_pages
mdefine_line|#define alloc_bootmem_low_pages(x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), PAGE_SIZE, 0)
DECL|macro|alloc_bootmem_node
mdefine_line|#define alloc_bootmem_node(ignore, x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), SMP_CACHE_BYTES, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_pages_node
mdefine_line|#define alloc_bootmem_pages_node(ignore, x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), PAGE_SIZE, __pa(MAX_DMA_ADDRESS))
DECL|macro|alloc_bootmem_low_pages_node
mdefine_line|#define alloc_bootmem_low_pages_node(ignore, x) &bslash;&n;&t;__alloc_bootmem_node(NODE_DATA(0), (x), PAGE_SIZE, 0)
DECL|macro|PLAT_NODE_DATA
mdefine_line|#define PLAT_NODE_DATA(n)&t;&t;(plat_node_data[(n)])
DECL|macro|PLAT_NODE_DATA_STARTNR
mdefine_line|#define PLAT_NODE_DATA_STARTNR(n)&t;&bslash;&n;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_start_mapnr)
DECL|macro|PLAT_NODE_DATA_SIZE
mdefine_line|#define PLAT_NODE_DATA_SIZE(n)&t;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_size)
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(pfn, n) &bslash;&n;&t;((pfn) - PLAT_NODE_DATA(n)-&gt;gendata.node_start_pfn)
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
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;((unsigned long)__va(NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;node_start_pfn &lt;&lt; PAGE_SHIFT))
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR(kvaddr)) &gt;&gt; PAGE_SHIFT)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;test_bit(LOCAL_MAP_NR(kaddr), &bslash;&n;&t;&t;&t;&t;&t; NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;valid_addr_bitmap)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(NODE_MEM_MAP(PFN_TO_NID(pfn)) + PLAT_NODE_DATA_LOCALNR(pfn, PFN_TO_NID(pfn)))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((page - page_zone(page)-&gt;zone_mem_map) + page_zone(page)-&gt;zone_start_pfn)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
