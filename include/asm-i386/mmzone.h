multiline_comment|/*&n; * Written by Pat Gaughen (gone@us.ibm.com) Mar 2002&n; *&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/numaq.h&gt;
macro_line|#else
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;(0)
macro_line|#ifdef CONFIG_NUMA
DECL|macro|_cpu_to_node
mdefine_line|#define _cpu_to_node(cpu) 0
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#ifdef CONFIG_NUMA
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id() _cpu_to_node(smp_processor_id())
macro_line|#endif /* CONFIG_NUMA */
r_extern
r_struct
id|pglist_data
op_star
id|node_data
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
DECL|macro|node_size
mdefine_line|#define node_size(nid)&t;&t;(node_data[nid]-&gt;node_size)
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;((pfn) - node_data[nid]-&gt;node_start_pfn)
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kaddr)&t;pfn_to_nid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(node_data[nid])
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_end_pfn
mdefine_line|#define node_end_pfn(nid)       (NODE_DATA(nid)-&gt;node_start_pfn + &bslash;&n;&t;&t;&t;&t; NODE_DATA(nid)-&gt;node_size)
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr) &bslash;&n;&t;( (__pa(kvaddr) &gt;&gt; PAGE_SHIFT) - node_start_pfn(kvaddr_to_nid(kvaddr)) )
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;test_bit(local_mapnr(kaddr), &bslash;&n;&t;&t; NODE_DATA(kvaddr_to_nid(kaddr))-&gt;valid_addr_bitmap)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(node_mem_map(pfn_to_nid(pfn)) + node_localnr(pfn, pfn_to_nid(pfn)))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((page - page_zone(page)-&gt;zone_mem_map) + page_zone(page)-&gt;zone_start_pfn)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
multiline_comment|/*&n; * pfn_valid should be made as fast as possible, and the current definition &n; * is valid for machines that are NUMA, but still contiguous, which is what&n; * is currently supported. A more generalised, but slower definition would&n; * be something like this - mbligh:&n; * ( pfn_to_pgdat(pfn) &amp;&amp; (pfn &lt; node_end_pfn(pfn_to_nid(pfn))) ) &n; */
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)          (pfn &lt; num_physpages)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
