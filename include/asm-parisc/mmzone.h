macro_line|#ifndef _PARISC_MMZONE_H
DECL|macro|_PARISC_MMZONE_H
mdefine_line|#define _PARISC_MMZONE_H
DECL|struct|node_map_data
r_struct
id|node_map_data
(brace
DECL|member|pg_data
id|pg_data_t
id|pg_data
suffix:semicolon
DECL|member|adj_node_mem_map
r_struct
id|page
op_star
id|adj_node_mem_map
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
r_extern
r_int
r_char
op_star
id|chunkmap
suffix:semicolon
DECL|macro|BADCHUNK
mdefine_line|#define BADCHUNK                ((unsigned char)0xff)
DECL|macro|CHUNKSZ
mdefine_line|#define CHUNKSZ                 (256*1024*1024)
DECL|macro|CHUNKSHIFT
mdefine_line|#define CHUNKSHIFT              28
DECL|macro|CHUNKMASK
mdefine_line|#define CHUNKMASK               (~(CHUNKSZ - 1))
DECL|macro|CHUNKNUM
mdefine_line|#define CHUNKNUM(paddr)         ((paddr) &gt;&gt; CHUNKSHIFT)
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)          (&amp;node_data[nid].pg_data)
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)       (NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|ADJ_NODE_MEM_MAP
mdefine_line|#define ADJ_NODE_MEM_MAP(nid)   (node_data[nid].adj_node_mem_map)
DECL|macro|phys_to_page
mdefine_line|#define phys_to_page(paddr) &bslash;&n;&t;(ADJ_NODE_MEM_MAP(chunkmap[CHUNKNUM((paddr))]) &bslash;&n;&t;+ ((paddr) &gt;&gt; PAGE_SHIFT))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kvaddr) phys_to_page(__pa(kvaddr))
multiline_comment|/* This is kind of bogus, need to investigate performance of doing it right */
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
macro_line|#endif /* !_PARISC_MMZONE_H */
eof
