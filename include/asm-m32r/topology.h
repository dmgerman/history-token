multiline_comment|/*&n; * linux/include/asm-generic/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_M32R_TOPOLOGY_H
DECL|macro|_ASM_M32R_TOPOLOGY_H
mdefine_line|#define _ASM_M32R_TOPOLOGY_H
multiline_comment|/* Other architectures wishing to use this simple topology API should fill&n;   in the below functions as appropriate in their own &lt;asm/topology.h&gt; file. */
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;(0)
macro_line|#ifndef parent_node
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;(0)
macro_line|#endif
macro_line|#ifndef node_to_cpumask
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;(cpu_online_map)
macro_line|#endif
macro_line|#ifndef node_to_first_cpu
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node)&t;(0)
macro_line|#endif
macro_line|#ifndef pcibus_to_cpumask
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus)&t;(cpu_online_map)
macro_line|#endif
multiline_comment|/* Cross-node load balancing interval. */
macro_line|#ifndef NODE_BALANCE_RATE
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 10
macro_line|#endif
macro_line|#endif /* _ASM_M32R_TOPOLOGY_H */
eof
