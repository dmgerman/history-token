multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2002 NEC Corp.&n; * Copyright (c) 2002 Erich Focht &lt;efocht@ess.nec.de&gt;&n; * Copyright (c) 2002 Kimio Suganuma &lt;k-suganuma@da.jp.nec.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_NODEDATA_H
DECL|macro|_ASM_IA64_NODEDATA_H
mdefine_line|#define _ASM_IA64_NODEDATA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/numa.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
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
id|MAX_NUMNODES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Return a pointer to the node_data structure for the executing cpu.&n; */
DECL|macro|local_node_data
mdefine_line|#define local_node_data&t;&t;(local_cpu_data-&gt;node_data)
multiline_comment|/*&n; * Given a node id, return a pointer to the pg_data_t for the node.&n; *&n; * NODE_DATA &t;- should be used in all code not related to system&n; *&t;&t;  initialization. It uses pernode data structures to minimize&n; *&t;&t;  offnode memory references. However, these structure are not &n; *&t;&t;  present during boot. This macro can be used once cpu_init&n; *&t;&t;  completes.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(local_node_data-&gt;pg_data_ptrs[nid])
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_IA64_NODEDATA_H */
eof
