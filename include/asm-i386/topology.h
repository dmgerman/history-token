multiline_comment|/*&n; * linux/include/asm-i386/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_I386_TOPOLOGY_H
DECL|macro|_ASM_I386_TOPOLOGY_H
mdefine_line|#define _ASM_I386_TOPOLOGY_H
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/smpboot.h&gt;
multiline_comment|/* Returns the number of the node containing CPU &squot;cpu&squot; */
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu) (cpu_to_logical_apicid(cpu) &gt;&gt; 4)
multiline_comment|/* Returns the number of the node containing MemBlk &squot;memblk&squot; */
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk) (memblk)
multiline_comment|/* Returns the number of the node containing Node &squot;nid&squot;.  This architecture is flat, &n;   so it is a pretty simple function! */
DECL|macro|__parent_node
mdefine_line|#define __parent_node(nid) (nid)
multiline_comment|/* Returns the number of the first CPU on Node &squot;node&squot;.&n; * This should be changed to a set of cached values&n; * but this will do for now.&n; */
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
r_int
id|i
comma
id|cpu
comma
id|logical_apicid
op_assign
id|node
op_lshift
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_lshift_assign
l_int|1
)paren
multiline_comment|/* check to see if the cpu is in the system */
r_if
c_cond
(paren
(paren
id|cpu
op_assign
id|logical_apicid_to_cpu
c_func
(paren
id|logical_apicid
op_or
id|i
)paren
)paren
op_ge
l_int|0
)paren
multiline_comment|/* if yes, return it to caller */
r_return
id|cpu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns a bitmask of CPUs on Node &squot;node&squot;.&n; * This should be changed to a set of cached bitmasks&n; * but this will do for now.&n; */
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
r_int
id|i
comma
id|cpu
comma
id|logical_apicid
op_assign
id|node
op_lshift
l_int|4
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_lshift_assign
l_int|1
)paren
multiline_comment|/* check to see if the cpu is in the system */
r_if
c_cond
(paren
(paren
id|cpu
op_assign
id|logical_apicid_to_cpu
c_func
(paren
id|logical_apicid
op_or
id|i
)paren
)paren
op_ge
l_int|0
)paren
multiline_comment|/* if yes, add to bitmask */
id|mask
op_or_assign
l_int|1
op_lshift
id|cpu
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the first MemBlk on Node &squot;node&squot; */
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node) (node)
macro_line|#else /* !CONFIG_X86_NUMAQ */
multiline_comment|/*&n; * Other i386 platforms should define their own version of the &n; * above macros here.&n; */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#endif /* _ASM_I386_TOPOLOGY_H */
eof
