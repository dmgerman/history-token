multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2002 NEC Corp.&n; * Copyright (c) 2002 Erich Focht &lt;efocht@ess.nec.de&gt;&n; * Copyright (c) 2002 Kimio Suganuma &lt;k-suganuma@da.jp.nec.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_NODEDATA_H
DECL|macro|_ASM_IA64_NODEDATA_H
mdefine_line|#define _ASM_IA64_NODEDATA_H
macro_line|#include &lt;asm/mmzone.h&gt;
multiline_comment|/*&n; * Node Data. One of these structures is located on each node of a NUMA system.&n; */
r_struct
id|pglist_data
suffix:semicolon
DECL|struct|ia64_node_data
r_struct
id|ia64_node_data
(brace
DECL|member|active_cpu_count
r_int
id|active_cpu_count
suffix:semicolon
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|pg_data_ptrs
r_struct
id|pglist_data
op_star
id|pg_data_ptrs
(braket
id|NR_NODES
)braket
suffix:semicolon
DECL|member|bank_mem_map_base
r_struct
id|page
op_star
id|bank_mem_map_base
(braket
id|NR_BANKS
)braket
suffix:semicolon
DECL|member|node_data_ptrs
r_struct
id|ia64_node_data
op_star
id|node_data_ptrs
(braket
id|NR_NODES
)braket
suffix:semicolon
DECL|member|node_id_map
r_int
id|node_id_map
(braket
id|NR_BANKS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Return a pointer to the node_data structure for the executing cpu.&n; */
DECL|macro|local_node_data
mdefine_line|#define local_node_data&t;&t;(local_cpu_data-&gt;node_data)
multiline_comment|/*&n; * Return a pointer to the node_data structure for the specified node.&n; */
DECL|macro|node_data
mdefine_line|#define node_data(node)&t;(local_node_data-&gt;node_data_ptrs[node])
multiline_comment|/*&n; * Get a pointer to the node_id/node_data for the current cpu.&n; *    (boot time only)&n; */
r_extern
r_int
id|boot_get_local_nodeid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|ia64_node_data
op_star
id|get_node_data_ptr
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Given a node id, return a pointer to the pg_data_t for the node.&n; * The following 2 macros are similar. &n; *&n; * NODE_DATA &t;- should be used in all code not related to system&n; *&t;&t;  initialization. It uses pernode data structures to minimize&n; *&t;&t;  offnode memory references. However, these structure are not &n; *&t;&t;  present during boot. This macro can be used once cpu_init&n; *&t;&t;  completes.&n; *&n; * BOOT_NODE_DATA&n; *&t;&t;- should be used during system initialization &n; *&t;&t;  prior to freeing __initdata. It does not depend on the percpu&n; *&t;&t;  area being present.&n; *&n; * NOTE:   The names of these macros are misleading but are difficult to change&n; *&t;   since they are used in generic linux &amp; on other architecures.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(local_node_data-&gt;pg_data_ptrs[nid])
DECL|macro|BOOT_NODE_DATA
mdefine_line|#define BOOT_NODE_DATA(nid)&t;boot_get_pg_data_ptr((long)(nid))
r_struct
id|pglist_data
suffix:semicolon
r_extern
r_struct
id|pglist_data
op_star
id|__init
id|boot_get_pg_data_ptr
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_NODEDATA_H */
eof
