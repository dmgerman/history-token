multiline_comment|/*&n; * Written by Pat Gaughen (gone@us.ibm.com) Mar 2002&n; *&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
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
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;&t;((pfn) - node_data[nid]-&gt;node_start_pfn)
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
mdefine_line|#define node_end_pfn(nid)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pg_data_t *__pgdat = NODE_DATA(nid);&t;&t;&t;&t;&bslash;&n;&t;__pgdat-&gt;node_start_pfn + __pgdat-&gt;node_spanned_pages;&t;&t;&bslash;&n;})
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = __pa(kvaddr) &gt;&gt; PAGE_SHIFT;&t;&t;&bslash;&n;&t;(__pfn - node_start_pfn(pfn_to_nid(__pfn)));&t;&t;&t;&bslash;&n;})
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __kaddr = (unsigned long)(kaddr);&t;&t;&t;&bslash;&n;&t;pg_data_t *__pgdat = NODE_DATA(kvaddr_to_nid(__kaddr));&t;&t;&bslash;&n;&t;test_bit(local_mapnr(__kaddr), __pgdat-&gt;valid_addr_bitmap);&t;&bslash;&n;})
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = pfn;&t;&t;&t;&t;&t;&bslash;&n;&t;int __node  = pfn_to_nid(__pfn);&t;&t;&t;&t;&bslash;&n;&t;&amp;node_mem_map(__node)[node_localnr(__pfn,__node)];&t;&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(pg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *__page = pg;&t;&t;&t;&t;&t;&bslash;&n;&t;struct zone *__zone = page_zone(__page);&t;&t;&t;&bslash;&n;&t;(unsigned long)(__page - __zone-&gt;zone_mem_map)&t;&t;&t;&bslash;&n;&t;&t;+ __zone-&gt;zone_start_pfn;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
multiline_comment|/*&n; * pfn_valid should be made as fast as possible, and the current definition &n; * is valid for machines that are NUMA, but still contiguous, which is what&n; * is currently supported. A more generalised, but slower definition would&n; * be something like this - mbligh:&n; * ( pfn_to_pgdat(pfn) &amp;&amp; ((pfn) &lt; node_end_pfn(pfn_to_nid(pfn))) ) &n; */
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)          ((pfn) &lt; num_physpages)
multiline_comment|/*&n; * generic node memory support, the following assumptions apply:&n; *&n; * 1) memory comes in 256Mb contigious chunks which are either present or not&n; * 2) we will not have more than 64Gb in total&n; *&n; * for now assume that 64Gb is max amount of RAM for whole system&n; *    64Gb / 4096bytes/page = 16777216 pages&n; */
DECL|macro|MAX_NR_PAGES
mdefine_line|#define MAX_NR_PAGES 16777216
DECL|macro|MAX_ELEMENTS
mdefine_line|#define MAX_ELEMENTS 256
DECL|macro|PAGES_PER_ELEMENT
mdefine_line|#define PAGES_PER_ELEMENT (MAX_NR_PAGES/MAX_ELEMENTS)
r_extern
id|u8
id|physnode_map
(braket
)braket
suffix:semicolon
DECL|function|pfn_to_nid
r_static
r_inline
r_int
id|pfn_to_nid
c_func
(paren
r_int
r_int
id|pfn
)paren
(brace
r_return
id|physnode_map
(braket
(paren
id|pfn
)paren
op_div
id|PAGES_PER_ELEMENT
)braket
suffix:semicolon
)brace
DECL|function|pfn_to_pgdat
r_static
r_inline
r_struct
id|pglist_data
op_star
id|pfn_to_pgdat
c_func
(paren
r_int
r_int
id|pfn
)paren
(brace
r_return
id|NODE_DATA
c_func
(paren
id|pfn_to_nid
c_func
(paren
id|pfn
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/numaq.h&gt;
macro_line|#elif CONFIG_NUMA&t;/* summit or generic arch */
macro_line|#include &lt;asm/srat.h&gt;
macro_line|#elif CONFIG_X86_PC
DECL|macro|get_memcfg_numa
mdefine_line|#define get_memcfg_numa get_memcfg_numa_flat
DECL|macro|get_zholes_size
mdefine_line|#define get_zholes_size(n) (0)
macro_line|#else
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;(0)
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
