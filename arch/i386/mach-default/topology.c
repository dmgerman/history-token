multiline_comment|/*&n; * arch/i386/mach-generic/topology.c - Populate driverfs with topology information&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; * Original Code: Paul Dorwin, IBM Corporation, Patrick Mochel, OSDL&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
DECL|variable|cpu_devices
r_struct
id|i386_cpu
id|cpu_devices
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/node.h&gt;
DECL|variable|node_devices
r_struct
id|i386_node
id|node_devices
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
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
id|num_online_nodes
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
id|arch_register_node
c_func
(paren
id|i
)paren
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|arch_register_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_NUMA */
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|arch_register_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NUMA */
DECL|variable|topology_init
id|subsys_initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
