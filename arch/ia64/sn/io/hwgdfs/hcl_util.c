multiline_comment|/* $Id: hcl_util.c,v 1.3 2003/04/24 13:59:39 pfg Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/devfs_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
DECL|variable|hwgraph_all_cnodes
r_static
id|vertex_hdl_t
id|hwgraph_all_cnodes
op_assign
id|GRAPH_VERTEX_NONE
suffix:semicolon
r_extern
id|vertex_hdl_t
id|hwgraph_root
suffix:semicolon
multiline_comment|/*&n;** Return the &quot;master&quot; for a given vertex.  A master vertex is a&n;** controller or adapter or other piece of hardware that the given&n;** vertex passes through on the way to the rest of the system.&n;*/
id|vertex_hdl_t
DECL|function|device_master_get
id|device_master_get
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
(brace
id|graph_error_t
id|rc
suffix:semicolon
id|vertex_hdl_t
id|master
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_get
c_func
(paren
id|vhdl
comma
id|EDGE_LBL_MASTER
comma
op_amp
id|master
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|GRAPH_SUCCESS
)paren
r_return
id|master
suffix:semicolon
r_else
r_return
id|GRAPH_VERTEX_NONE
suffix:semicolon
)brace
multiline_comment|/*&n;** Set the master for a given vertex.&n;** Returns 0 on success, non-0 indicates failure&n;*/
r_int
DECL|function|device_master_set
id|device_master_set
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
id|vertex_hdl_t
id|master
)paren
(brace
id|graph_error_t
id|rc
suffix:semicolon
id|rc
op_assign
id|hwgraph_edge_add
c_func
(paren
id|vhdl
comma
id|master
comma
id|EDGE_LBL_MASTER
)paren
suffix:semicolon
r_return
id|rc
op_ne
id|GRAPH_SUCCESS
suffix:semicolon
)brace
multiline_comment|/*&n;** Return the compact node id of the node that ultimately &quot;owns&quot; the specified&n;** vertex.  In order to do this, we walk back through masters and connect points&n;** until we reach a vertex that represents a node.&n;*/
id|cnodeid_t
DECL|function|master_node_get
id|master_node_get
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
(brace
id|cnodeid_t
id|cnodeid
suffix:semicolon
id|vertex_hdl_t
id|master
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|cnodeid
op_assign
id|nodevertex_to_cnodeid
c_func
(paren
id|vhdl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnodeid
op_ne
id|CNODEID_NONE
)paren
r_return
id|cnodeid
suffix:semicolon
id|master
op_assign
id|device_master_get
c_func
(paren
id|vhdl
)paren
suffix:semicolon
multiline_comment|/* Check for exceptional cases */
r_if
c_cond
(paren
id|master
op_eq
id|vhdl
)paren
(brace
multiline_comment|/* Since we got a reference to the &quot;master&quot; thru&n;&t;&t;&t; * device_master_get() we should decrement&n;&t;&t;&t; * its reference count by 1&n;&t;&t;&t; */
r_return
id|CNODEID_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|master
op_eq
id|GRAPH_VERTEX_NONE
)paren
(brace
id|master
op_assign
id|hwgraph_connectpt_get
c_func
(paren
id|vhdl
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|master
op_eq
id|GRAPH_VERTEX_NONE
)paren
op_logical_or
(paren
id|master
op_eq
id|vhdl
)paren
)paren
(brace
r_return
id|CNODEID_NONE
suffix:semicolon
)brace
)brace
id|vhdl
op_assign
id|master
suffix:semicolon
)brace
)brace
DECL|variable|hwgraph_all_cpuids
r_static
id|vertex_hdl_t
id|hwgraph_all_cpuids
op_assign
id|GRAPH_VERTEX_NONE
suffix:semicolon
r_extern
r_int
id|maxcpus
suffix:semicolon
r_void
DECL|function|mark_cpuvertex_as_cpu
id|mark_cpuvertex_as_cpu
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
id|cpuid_t
id|cpuid
)paren
(brace
r_if
c_cond
(paren
id|cpuid
op_eq
id|CPU_NONE
)paren
r_return
suffix:semicolon
(paren
r_void
)paren
id|labelcl_info_add_LBL
c_func
(paren
id|vhdl
comma
id|INFO_LBL_CPUID
comma
id|INFO_DESC_EXPORT
comma
(paren
id|arbitrary_info_t
)paren
id|cpuid
)paren
suffix:semicolon
(brace
r_char
id|cpuid_buffer
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_all_cpuids
op_eq
id|GRAPH_VERTEX_NONE
)paren
(brace
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|EDGE_LBL_CPUNUM
comma
op_amp
id|hwgraph_all_cpuids
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|cpuid_buffer
comma
l_string|&quot;%ld&quot;
comma
id|cpuid
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_edge_add
c_func
(paren
id|hwgraph_all_cpuids
comma
id|vhdl
comma
id|cpuid_buffer
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** If the specified device represents a node, return its&n;** compact node ID; otherwise, return CNODEID_NONE.&n;*/
id|cnodeid_t
DECL|function|nodevertex_to_cnodeid
id|nodevertex_to_cnodeid
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
id|arbitrary_info_t
id|cnodeid
op_assign
id|CNODEID_NONE
suffix:semicolon
id|rv
op_assign
id|labelcl_info_get_LBL
c_func
(paren
id|vhdl
comma
id|INFO_LBL_CNODEID
comma
l_int|NULL
comma
op_amp
id|cnodeid
)paren
suffix:semicolon
r_return
(paren
id|cnodeid_t
)paren
id|cnodeid
suffix:semicolon
)brace
r_void
DECL|function|mark_nodevertex_as_node
id|mark_nodevertex_as_node
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
id|cnodeid_t
id|cnodeid
)paren
(brace
r_if
c_cond
(paren
id|cnodeid
op_eq
id|CNODEID_NONE
)paren
r_return
suffix:semicolon
id|cnodeid_to_vertex
c_func
(paren
id|cnodeid
)paren
op_assign
id|vhdl
suffix:semicolon
id|labelcl_info_add_LBL
c_func
(paren
id|vhdl
comma
id|INFO_LBL_CNODEID
comma
id|INFO_DESC_EXPORT
comma
(paren
id|arbitrary_info_t
)paren
id|cnodeid
)paren
suffix:semicolon
(brace
r_char
id|cnodeid_buffer
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_all_cnodes
op_eq
id|GRAPH_VERTEX_NONE
)paren
(brace
(paren
r_void
)paren
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|EDGE_LBL_NODENUM
comma
op_amp
id|hwgraph_all_cnodes
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|cnodeid_buffer
comma
l_string|&quot;%d&quot;
comma
id|cnodeid
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_edge_add
c_func
(paren
id|hwgraph_all_cnodes
comma
id|vhdl
comma
id|cnodeid_buffer
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;** If the specified device represents a CPU, return its cpuid;&n;** otherwise, return CPU_NONE.&n;*/
id|cpuid_t
DECL|function|cpuvertex_to_cpuid
id|cpuvertex_to_cpuid
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
(brace
id|arbitrary_info_t
id|cpuid
op_assign
id|CPU_NONE
suffix:semicolon
(paren
r_void
)paren
id|labelcl_info_get_LBL
c_func
(paren
id|vhdl
comma
id|INFO_LBL_CPUID
comma
l_int|NULL
comma
op_amp
id|cpuid
)paren
suffix:semicolon
r_return
(paren
id|cpuid_t
)paren
id|cpuid
suffix:semicolon
)brace
multiline_comment|/*&n;** dev_to_name converts a vertex_hdl_t into a canonical name.  If the vertex_hdl_t&n;** represents a vertex in the hardware graph, it is converted in the&n;** normal way for vertices.  If the vertex_hdl_t is an old vertex_hdl_t (one which&n;** does not represent a hwgraph vertex), we synthesize a name based&n;** on major/minor number.&n;**&n;** Usually returns a pointer to the original buffer, filled in as&n;** appropriate.  If the buffer is too small to hold the entire name,&n;** or if anything goes wrong while determining the name, dev_to_name&n;** returns &quot;UnknownDevice&quot;.&n;*/
r_char
op_star
DECL|function|dev_to_name
id|dev_to_name
c_func
(paren
id|vertex_hdl_t
id|dev
comma
r_char
op_star
id|buf
comma
id|uint
id|buflen
)paren
(brace
r_return
id|vertex_to_name
c_func
(paren
id|dev
comma
id|buf
comma
id|buflen
)paren
suffix:semicolon
)brace
eof
