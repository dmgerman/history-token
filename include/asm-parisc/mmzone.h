macro_line|#ifndef _PARISC_MMZONE_H
DECL|macro|_PARISC_MMZONE_H
mdefine_line|#define _PARISC_MMZONE_H
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|MAX_PHYSMEM_RANGES
mdefine_line|#define MAX_PHYSMEM_RANGES 8 /* Fix the size for now (current known max is 3) */
r_extern
r_int
id|npmem_ranges
suffix:semicolon
DECL|struct|node_map_data
r_struct
id|node_map_data
(brace
DECL|member|pg_data
id|pg_data_t
id|pg_data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|node_map_data
id|node_data
(braket
)braket
suffix:semicolon
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)          (&amp;node_data[nid].pg_data)
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kaddr)&t;pfn_to_nid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_end_pfn
mdefine_line|#define node_end_pfn(nid)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pg_data_t *__pgdat = NODE_DATA(nid);&t;&t;&t;&t;&bslash;&n;&t;__pgdat-&gt;node_start_pfn + __pgdat-&gt;node_spanned_pages;&t;&t;&bslash;&n;})
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;&t;((pfn) - node_start_pfn(nid))
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = __pa(kvaddr) &gt;&gt; PAGE_SHIFT;&t;&t;&bslash;&n;&t;(__pfn - node_start_pfn(pfn_to_nid(__pfn)));&t;&t;&t;&bslash;&n;})
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __pfn = (pfn);&t;&t;&t;&t;&t;&bslash;&n;&t;int __node  = pfn_to_nid(__pfn);&t;&t;&t;&t;&bslash;&n;&t;&amp;node_mem_map(__node)[node_localnr(__pfn,__node)];&t;&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(pg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *__page = pg;&t;&t;&t;&t;&t;&bslash;&n;&t;struct zone *__zone = page_zone(__page);&t;&t;&t;&bslash;&n;&t;BUG_ON(__zone == NULL);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned long)(__page - __zone-&gt;zone_mem_map)&t;&t;&t;&bslash;&n;&t;&t;+ __zone-&gt;zone_start_pfn;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* We have these possible memory map layouts:&n; * Astro: 0-3.75, 67.75-68, 4-64&n; * zx1: 0-1, 257-260, 4-256&n; * Stretch (N-class): 0-2, 4-32, 34-xxx&n; */
multiline_comment|/* Since each 1GB can only belong to one region (node), we can create&n; * an index table for pfn to nid lookup; each entry in pfnnid_map &n; * represents 1GB, and contains the node that the memory belongs to. */
DECL|macro|PFNNID_SHIFT
mdefine_line|#define PFNNID_SHIFT (30 - PAGE_SHIFT)
DECL|macro|PFNNID_MAP_MAX
mdefine_line|#define PFNNID_MAP_MAX  512     /* support 512GB */
r_extern
r_int
r_char
id|pfnnid_map
(braket
id|PFNNID_MAP_MAX
)braket
suffix:semicolon
macro_line|#ifndef __LP64__
DECL|macro|pfn_is_io
mdefine_line|#define pfn_is_io(pfn) ((pfn &amp; (0xf0000000UL &gt;&gt; PAGE_SHIFT)) == (0xf0000000UL &gt;&gt; PAGE_SHIFT))
macro_line|#else
multiline_comment|/* io can be 0xf0f0f0f0f0xxxxxx or 0xfffffffff0000000 */
DECL|macro|pfn_is_io
mdefine_line|#define pfn_is_io(pfn) ((pfn &amp; (0xf000000000000000UL &gt;&gt; PAGE_SHIFT)) == (0xf000000000000000UL &gt;&gt; PAGE_SHIFT))
macro_line|#endif
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
r_int
r_int
id|i
suffix:semicolon
r_int
r_char
id|r
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pfn_is_io
c_func
(paren
id|pfn
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|pfn
op_rshift
id|PFNNID_SHIFT
suffix:semicolon
id|BUG_ON
c_func
(paren
id|i
op_ge
r_sizeof
(paren
id|pfnnid_map
)paren
op_div
r_sizeof
(paren
id|pfnnid_map
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|r
op_assign
id|pfnnid_map
(braket
id|i
)braket
suffix:semicolon
id|BUG_ON
c_func
(paren
id|r
op_eq
l_int|0xff
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|r
suffix:semicolon
)brace
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
macro_line|#else /* !CONFIG_DISCONTIGMEM */
DECL|macro|MAX_PHYSMEM_RANGES
mdefine_line|#define MAX_PHYSMEM_RANGES &t;1 
macro_line|#endif
macro_line|#endif /* _PARISC_MMZONE_H */
eof
