multiline_comment|/*&n; *  linux/include/asm-sh/mmzone.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_SH_MMZONE_H
DECL|macro|__ASM_SH_MMZONE_H
mdefine_line|#define __ASM_SH_MMZONE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Currently, just for HP690 */
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(phys)&t;((((phys) - __MEMORY_START) &gt;= 0x01000000)?1:0)
DECL|macro|NR_NODES
mdefine_line|#define NR_NODES 2
r_extern
id|pg_data_t
id|discontig_page_data
(braket
id|NR_NODES
)braket
suffix:semicolon
r_extern
id|bootmem_data_t
id|discontig_node_bdata
(braket
id|NR_NODES
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;PHYSADDR_TO_NID(__pa(kaddr))
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;discontig_page_data[nid])
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|phys_to_page
mdefine_line|#define phys_to_page(phys)&t;&t;&t;&t;&t;&t;&bslash;&n;({ unsigned int node = PHYSADDR_TO_NID(phys); &t;&t;      &t;&t;&bslash;&n;   NODE_MEM_MAP(node)&t;&t;&t;&t; &t;&t; &t;&bslash;&n;     + (((phys) - NODE_DATA(node)-&gt;node_start_paddr) &gt;&gt; PAGE_SHIFT); })
DECL|function|is_valid_page
r_static
r_inline
r_int
id|is_valid_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_NODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page
op_ge
id|NODE_MEM_MAP
c_func
(paren
id|i
)paren
op_logical_and
id|page
OL
id|NODE_MEM_MAP
c_func
(paren
id|i
)paren
op_plus
id|NODE_DATA
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|node_size
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;is_valid_page(page)
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;PHYSADDR(page_address(page))
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif
eof
