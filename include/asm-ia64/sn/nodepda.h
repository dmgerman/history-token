multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_NODEPDA_H
DECL|macro|_ASM_IA64_SN_NODEPDA_H
mdefine_line|#define _ASM_IA64_SN_NODEPDA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/router.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
multiline_comment|/*&n; * NUMA Node-Specific Data structures are defined in this file.&n; * In particular, this is the location of the node PDA.&n; * A pointer to the right node PDA is saved in each CPU PDA.&n; */
multiline_comment|/*&n; * Node-specific data structure.&n; *&n; * One of these structures is allocated on each node of a NUMA system.&n; *&n; * This structure provides a convenient way of keeping together &n; * all per-node data structures. &n; */
DECL|struct|nodepda_s
r_struct
id|nodepda_s
(brace
DECL|member|node_first_cpu
id|cpuid_t
id|node_first_cpu
suffix:semicolon
multiline_comment|/* Starting cpu number for node */
multiline_comment|/* WARNING: no guarantee that   */
multiline_comment|/*  the second cpu on a node is */
multiline_comment|/*  node_first_cpu+1.           */
DECL|member|xbow_vhdl
id|vertex_hdl_t
id|xbow_vhdl
suffix:semicolon
DECL|member|xbow_peer
id|nasid_t
id|xbow_peer
suffix:semicolon
multiline_comment|/* NASID of our peer hub on xbow */
DECL|member|xbow_sema
r_struct
id|semaphore
id|xbow_sema
suffix:semicolon
multiline_comment|/* Sema for xbow synchronization */
DECL|member|slotdesc
id|slotid_t
id|slotdesc
suffix:semicolon
DECL|member|geoid
id|geoid_t
id|geoid
suffix:semicolon
DECL|member|module
id|module_t
op_star
id|module
suffix:semicolon
multiline_comment|/* Pointer to containing module */
DECL|member|basew_id
id|xwidgetnum_t
id|basew_id
suffix:semicolon
DECL|member|basew_xc
id|vertex_hdl_t
id|basew_xc
suffix:semicolon
DECL|member|hubticks
r_int
id|hubticks
suffix:semicolon
DECL|member|num_routers
r_int
id|num_routers
suffix:semicolon
multiline_comment|/* XXX not setup! Total routers in the system */
DECL|member|hwg_node_name
r_char
op_star
id|hwg_node_name
suffix:semicolon
multiline_comment|/* hwgraph node name */
DECL|member|node_vertex
id|vertex_hdl_t
id|node_vertex
suffix:semicolon
multiline_comment|/* Hwgraph vertex for this node */
DECL|member|pdinfo
r_void
op_star
id|pdinfo
suffix:semicolon
multiline_comment|/* Platform-dependent per-node info */
DECL|member|npda_rip_first
id|nodepda_router_info_t
op_star
id|npda_rip_first
suffix:semicolon
DECL|member|npda_rip_last
id|nodepda_router_info_t
op_star
op_star
id|npda_rip_last
suffix:semicolon
multiline_comment|/*&n;&t; * The BTEs on this node are shared by the local cpus&n;&t; */
DECL|member|bte_if
r_struct
id|bteinfo_s
id|bte_if
(braket
id|BTES_PER_NODE
)braket
suffix:semicolon
multiline_comment|/* Virtual Interface */
DECL|member|bte_recovery_timer
r_struct
id|timer_list
id|bte_recovery_timer
suffix:semicolon
DECL|member|bte_recovery_lock
id|spinlock_t
id|bte_recovery_lock
suffix:semicolon
multiline_comment|/* &n;&t; * Array of pointers to the nodepdas for each node.&n;&t; */
DECL|member|pernode_pdaindr
r_struct
id|nodepda_s
op_star
id|pernode_pdaindr
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|nodepda_t
r_typedef
r_struct
id|nodepda_s
id|nodepda_t
suffix:semicolon
DECL|struct|irqpda_s
r_struct
id|irqpda_s
(brace
DECL|member|num_irq_used
r_int
id|num_irq_used
suffix:semicolon
DECL|member|irq_flags
r_char
id|irq_flags
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|member|device_dev
r_struct
id|pci_dev
op_star
id|device_dev
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|member|share_count
r_char
id|share_count
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|member|current
r_struct
id|pci_dev
op_star
id|current
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|irqpda_t
r_typedef
r_struct
id|irqpda_s
id|irqpda_t
suffix:semicolon
multiline_comment|/*&n; * Access Functions for node PDA.&n; * Since there is one nodepda for each node, we need a convenient mechanism&n; * to access these nodepdas without cluttering code with #ifdefs.&n; * The next set of definitions provides this.&n; * Routines are expected to use &n; *&n; *&t;nodepda&t;&t;&t;-&gt; to access node PDA for the node on which code is running&n; *&t;subnodepda&t;&t;-&gt; to access subnode PDA for the subnode on which code is running&n; *&n; *&t;NODEPDA(cnode)&t;&t;-&gt; to access node PDA for cnodeid &n; *&t;SUBNODEPDA(cnode,sn)&t;-&gt; to access subnode PDA for cnodeid/subnode&n; */
DECL|macro|nodepda
mdefine_line|#define&t;nodepda&t;&t;pda-&gt;p_nodepda&t;&t;/* Ptr to this node&squot;s PDA */
DECL|macro|NODEPDA
mdefine_line|#define&t;NODEPDA(cnode)&t;&t;(nodepda-&gt;pernode_pdaindr[cnode])
multiline_comment|/*&n; * Macros to access data structures inside nodepda &n; */
DECL|macro|NODE_MODULEID
mdefine_line|#define NODE_MODULEID(cnode)    geo_module((NODEPDA(cnode)-&gt;geoid))
DECL|macro|NODE_SLOTID
mdefine_line|#define NODE_SLOTID(cnode)&t;(NODEPDA(cnode)-&gt;slotdesc)
multiline_comment|/*&n; * Quickly convert a compact node ID into a hwgraph vertex&n; */
DECL|macro|cnodeid_to_vertex
mdefine_line|#define cnodeid_to_vertex(cnodeid) (NODEPDA(cnodeid)-&gt;node_vertex)
multiline_comment|/*&n; * Check if given a compact node id the corresponding node has all the&n; * cpus disabled. &n; */
DECL|macro|is_headless_node
mdefine_line|#define is_headless_node(cnode)&t;&t;(!test_bit(cnode, &amp;node_has_active_cpus))
multiline_comment|/*&n; * Check if given a node vertex handle the corresponding node has all the&n; * cpus disabled. &n; */
DECL|macro|is_headless_node_vertex
mdefine_line|#define is_headless_node_vertex(_nodevhdl) &bslash;&n;&t;&t;&t;is_headless_node(nodevertex_to_cnodeid(_nodevhdl))
macro_line|#endif /* _ASM_IA64_SN_NODEPDA_H */
eof
