multiline_comment|/*&n; * Written by Pat Gaughen (gone@us.ibm.com) Mar 2002&n; *&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#ifdef CONFIG_NUMA
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/numaq.h&gt;
macro_line|#else&t;/* summit or generic arch */
macro_line|#include &lt;asm/srat.h&gt;
macro_line|#endif
macro_line|#else /* !CONFIG_NUMA */
DECL|macro|get_memcfg_numa
mdefine_line|#define get_memcfg_numa get_memcfg_numa_flat
DECL|macro|get_zholes_size
mdefine_line|#define get_zholes_size(n) (0)
macro_line|#endif /* CONFIG_NUMA */
r_extern
r_struct
id|pglist_data
op_star
id|node_data
(braket
)braket
suffix:semicolon
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(node_data[nid])
multiline_comment|/*&n; * generic node memory support, the following assumptions apply:&n; *&n; * 1) memory comes in 256Mb contigious chunks which are either present or not&n; * 2) we will not have more than 64Gb in total&n; *&n; * for now assume that 64Gb is max amount of RAM for whole system&n; *    64Gb / 4096bytes/page = 16777216 pages&n; */
DECL|macro|MAX_NR_PAGES
mdefine_line|#define MAX_NR_PAGES 16777216
DECL|macro|MAX_ELEMENTS
mdefine_line|#define MAX_ELEMENTS 256
DECL|macro|PAGES_PER_ELEMENT
mdefine_line|#define PAGES_PER_ELEMENT (MAX_NR_PAGES/MAX_ELEMENTS)
r_extern
id|s8
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
macro_line|#ifdef CONFIG_NUMA
r_return
(paren
r_int
)paren
id|physnode_map
(braket
(paren
id|pfn
)paren
op_div
id|PAGES_PER_ELEMENT
)braket
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
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
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_end_pfn
mdefine_line|#define node_end_pfn(nid)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pg_data_t *__pgdat = NODE_DATA(nid);&t;&t;&t;&t;&bslash;&n;&t;__pgdat-&gt;node_start_pfn + __pgdat-&gt;node_spanned_pages;&t;&t;&bslash;&n;})
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = __pa(kvaddr) &gt;&gt; PAGE_SHIFT;&t;&t;&bslash;&n;&t;(__pfn - node_start_pfn(pfn_to_nid(__pfn)));&t;&t;&t;&bslash;&n;})
multiline_comment|/* XXX: FIXME -- wli */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;(0)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = pfn;&t;&t;&t;&t;&t;&bslash;&n;&t;int __node  = pfn_to_nid(__pfn);&t;&t;&t;&t;&bslash;&n;&t;&amp;node_mem_map(__node)[node_localnr(__pfn,__node)];&t;&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(pg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *__page = pg;&t;&t;&t;&t;&t;&bslash;&n;&t;struct zone *__zone = page_zone(__page);&t;&t;&t;&bslash;&n;&t;(unsigned long)(__page - __zone-&gt;zone_mem_map)&t;&t;&t;&bslash;&n;&t;&t;+ __zone-&gt;zone_start_pfn;&t;&t;&t;&t;&bslash;&n;})
macro_line|#ifdef CONFIG_X86_NUMAQ            /* we have contiguous memory on NUMA-Q */
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)          ((pfn) &lt; num_physpages)
macro_line|#else
DECL|function|pfn_valid
r_static
r_inline
r_int
id|pfn_valid
c_func
(paren
r_int
id|pfn
)paren
(brace
r_int
id|nid
op_assign
id|pfn_to_nid
c_func
(paren
id|pfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nid
op_ge
l_int|0
)paren
r_return
(paren
id|pfn
OL
id|node_end_pfn
c_func
(paren
id|nid
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_int
id|get_memcfg_numa_flat
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This allows any one NUMA architecture to be compiled&n; * for, and still fall back to the flat function if it&n; * fails.&n; */
DECL|function|get_memcfg_numa
r_static
r_inline
r_void
id|get_memcfg_numa
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_X86_NUMAQ
r_if
c_cond
(paren
id|get_memcfg_numaq
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
macro_line|#elif CONFIG_ACPI_SRAT
r_if
c_cond
(paren
id|get_memcfg_from_srat
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|get_memcfg_numa_flat
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
