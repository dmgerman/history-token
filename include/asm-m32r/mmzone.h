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
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(node_data[nid])
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;((pfn) - NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_end_pfn
mdefine_line|#define node_end_pfn(nid)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pg_data_t *__pgdat = NODE_DATA(nid);&t;&t;&t;&t;&bslash;&n;&t;__pgdat-&gt;node_start_pfn + __pgdat-&gt;node_spanned_pages - 1;&t;&bslash;&n;})
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = __pa(kvaddr) &gt;&gt; PAGE_SHIFT;&t;&t;&bslash;&n;&t;(__pfn - node_start_pfn(pfn_to_nid(__pfn)));&t;&t;&t;&bslash;&n;})
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = pfn;&t;&t;&t;&t;&t;&bslash;&n;&t;int __node  = pfn_to_nid(__pfn);&t;&t;&t;&t;&bslash;&n;&t;&amp;node_mem_map(__node)[node_localnr(__pfn,__node)];&t;&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(pg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *__page = pg;&t;&t;&t;&t;&t;&bslash;&n;&t;struct zone *__zone = page_zone(__page);&t;&t;&t;&bslash;&n;&t;(unsigned long)(__page - __zone-&gt;zone_mem_map)&t;&t;&t;&bslash;&n;&t;&t;+ __zone-&gt;zone_start_pfn;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
multiline_comment|/*&n; * pfn_valid should be made as fast as possible, and the current definition&n; * is valid for machines that are NUMA, but still contiguous, which is what&n; * is currently supported. A more generalised, but slower definition would&n; * be something like this - mbligh:&n; * ( pfn_to_pgdat(pfn) &amp;&amp; ((pfn) &lt; node_end_pfn(pfn_to_nid(pfn))) )&n; */
macro_line|#if 1&t;/* M32R_FIXME */
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;(1)
macro_line|#else
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;((pfn) &lt; num_physpages)
macro_line|#endif
multiline_comment|/*&n; * generic node memory support, the following assumptions apply:&n; */
DECL|function|pfn_to_nid
r_static
id|__inline__
r_int
id|pfn_to_nid
c_func
(paren
r_int
r_int
id|pfn
)paren
(brace
r_int
id|node
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|MAX_NUMNODES
suffix:semicolon
id|node
op_increment
)paren
r_if
c_cond
(paren
id|pfn
op_ge
id|node_start_pfn
c_func
(paren
id|node
)paren
op_logical_and
id|pfn
op_le
id|node_end_pfn
c_func
(paren
id|node
)paren
)paren
r_break
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|function|pfn_to_pgdat
r_static
id|__inline__
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
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
