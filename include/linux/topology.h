multiline_comment|/*&n; * include/linux/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _LINUX_TOPOLOGY_H
DECL|macro|_LINUX_TOPOLOGY_H
mdefine_line|#define _LINUX_TOPOLOGY_H
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
macro_line|#ifndef nr_cpus_node
DECL|macro|nr_cpus_node
mdefine_line|#define nr_cpus_node(node)&t;(hweight_long(node_to_cpumask(node)))
macro_line|#endif
DECL|function|__next_node_with_cpus
r_static
r_inline
r_int
id|__next_node_with_cpus
c_func
(paren
r_int
id|node
)paren
(brace
r_do
op_increment
id|node
suffix:semicolon
r_while
c_loop
(paren
id|node
OL
id|numnodes
op_logical_and
op_logical_neg
id|nr_cpus_node
c_func
(paren
id|node
)paren
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|macro|for_each_node_with_cpus
mdefine_line|#define for_each_node_with_cpus(node) &bslash;&n;&t;for (node = 0; node &lt; numnodes; node = __next_node_with_cpus(node))
macro_line|#endif /* _LINUX_TOPOLOGY_H */
eof
