multiline_comment|/*&n; * linux/include/asm-generic/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_GENERIC_TOPOLOGY_H
DECL|macro|_ASM_GENERIC_TOPOLOGY_H
mdefine_line|#define _ASM_GENERIC_TOPOLOGY_H
multiline_comment|/* Other architectures wishing to use this simple topology API should fill&n;   in the below functions as appropriate in their own &lt;asm/topology.h&gt; file. */
macro_line|#ifndef __cpu_to_node
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu)&t;&t;(0)
macro_line|#endif
macro_line|#ifndef __memblk_to_node
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk)&t;(0)
macro_line|#endif
macro_line|#ifndef __parent_node
DECL|macro|__parent_node
mdefine_line|#define __parent_node(node)&t;&t;(0)
macro_line|#endif
macro_line|#ifndef __node_to_first_cpu
DECL|macro|__node_to_first_cpu
mdefine_line|#define __node_to_first_cpu(node)&t;(0)
macro_line|#endif
macro_line|#ifndef __node_to_cpu_mask
DECL|macro|__node_to_cpu_mask
mdefine_line|#define __node_to_cpu_mask(node)&t;(cpu_online_map)
macro_line|#endif
macro_line|#ifndef __node_to_memblk
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node)&t;&t;(0)
macro_line|#endif
multiline_comment|/* Cross-node load balancing interval. */
macro_line|#ifndef NODE_BALANCE_RATE
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 10
macro_line|#endif
macro_line|#endif /* _ASM_GENERIC_TOPOLOGY_H */
eof
