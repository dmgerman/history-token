multiline_comment|/*&n; * linux/include/asm-i386/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_I386_TOPOLOGY_H
DECL|macro|_ASM_I386_TOPOLOGY_H
mdefine_line|#define _ASM_I386_TOPOLOGY_H
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/* Mappings between logical cpu number and node number */
r_extern
r_volatile
r_int
r_int
id|node_2_cpu_mask
(braket
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_2_node
(braket
)braket
suffix:semicolon
multiline_comment|/* Returns the number of the node containing CPU &squot;cpu&squot; */
DECL|function|__cpu_to_node
r_static
r_inline
r_int
id|__cpu_to_node
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu_2_node
(braket
id|cpu
)braket
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the node containing MemBlk &squot;memblk&squot; */
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk) (memblk)
multiline_comment|/* Returns the number of the node containing Node &squot;node&squot;.  This architecture is flat, &n;   so it is a pretty simple function! */
DECL|macro|__parent_node
mdefine_line|#define __parent_node(node) (node)
multiline_comment|/* Returns a bitmask of CPUs on Node &squot;node&squot;. */
DECL|function|__node_to_cpu_mask
r_static
r_inline
r_int
r_int
id|__node_to_cpu_mask
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|node_2_cpu_mask
(braket
id|node
)braket
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the first CPU on Node &squot;node&squot;. */
DECL|function|__node_to_first_cpu
r_static
r_inline
r_int
id|__node_to_first_cpu
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|__ffs
c_func
(paren
id|__node_to_cpu_mask
c_func
(paren
id|node
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the first MemBlk on Node &squot;node&squot; */
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node) (node)
macro_line|#else /* !CONFIG_NUMA */
multiline_comment|/*&n; * Other i386 platforms should define their own version of the &n; * above macros here.&n; */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_I386_TOPOLOGY_H */
eof
