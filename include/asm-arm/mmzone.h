multiline_comment|/*&n; *  linux/include/asm-arm/mmzone.h&n; *&n; *  1999-12-29&t;Nicolas Pitre&t;&t;Created&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_MMZONE_H
DECL|macro|__ASM_MMZONE_H
mdefine_line|#define __ASM_MMZONE_H
multiline_comment|/*&n; * Currently defined in arch/arm/mm/discontig.c&n; */
r_extern
id|pg_data_t
id|discontig_node_data
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;discontig_node_data[nid])
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
macro_line|#include &lt;asm/arch/mmzone.h&gt;
macro_line|#endif
eof
