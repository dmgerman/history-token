multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_NODEPDA_H
DECL|macro|_ASM_SN_NODEPDA_H
mdefine_line|#define _ASM_SN_NODEPDA_H
macro_line|#ifdef&t;__cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/agent.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/router.h&gt;
multiline_comment|/* #include &lt;SN/klkernvars.h&gt; */
macro_line|#ifdef IRIX
DECL|typedef|module_t
r_typedef
r_struct
id|module_s
id|module_t
suffix:semicolon
multiline_comment|/* Avoids sys/SN/module.h */
macro_line|#else
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#endif
multiline_comment|/* #include &lt;SN/slotnum.h&gt; */
multiline_comment|/*&n; * NUMA Node-Specific Data structures are defined in this file.&n; * In particular, this is the location of the node PDA.&n; * A pointer to the right node PDA is saved in each CPU PDA.&n; */
multiline_comment|/*&n; * Subnode PDA structures. Each node needs a few data structures that &n; * correspond to the PIs on the HUB chip that supports the node.&n; *&n; * WARNING!!!! 6.5.x compatibility requirements prevent us from&n; * changing or reordering fields in the following structure for IP27.&n; * It is essential that the data mappings not change for IP27 platforms.&n; * It is OK to add fields that are IP35 specific if they are under #ifdef IP35.&n; */
DECL|struct|subnodepda_s
r_struct
id|subnodepda_s
(brace
DECL|member|intr_dispatch0
id|intr_vecblk_t
id|intr_dispatch0
suffix:semicolon
DECL|member|intr_dispatch1
id|intr_vecblk_t
id|intr_dispatch1
suffix:semicolon
DECL|member|next_prof_timeout
r_uint64
id|next_prof_timeout
suffix:semicolon
DECL|member|prof_count
r_int
id|prof_count
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|subnode_pda_t
r_typedef
r_struct
id|subnodepda_s
id|subnode_pda_t
suffix:semicolon
r_struct
id|ptpool_s
suffix:semicolon
multiline_comment|/*&n; * Node-specific data structure.&n; *&n; * One of these structures is allocated on each node of a NUMA system.&n; * Non-NUMA systems are considered to be systems with one node, and&n; * hence there will be one of this structure for the entire system.&n; *&n; * This structure provides a convenient way of keeping together &n; * all per-node data structures. &n; */
macro_line|#ifndef CONFIG_IA64_SGI_IO
multiline_comment|/*&n; * The following structure is contained in the nodepda &amp; contains&n; * a lock &amp; queue-head for sanon pages that belong to the node.&n; * See the anon manager for more details.&n; */
r_typedef
r_struct
(brace
DECL|member|sal_lock
id|lock_t
id|sal_lock
suffix:semicolon
DECL|member|sal_listhead
id|plist_t
id|sal_listhead
suffix:semicolon
DECL|typedef|sanon_list_head_t
)brace
id|sanon_list_head_t
suffix:semicolon
macro_line|#endif
DECL|struct|nodepda_s
r_struct
id|nodepda_s
(brace
macro_line|#ifdef&t;NUMA_BASE
multiline_comment|/* &n;&t; * Pointer to this node&squot;s copy of Nodepdaindr &n;&t; */
DECL|member|pernode_pdaindr
r_struct
id|nodepda_s
op_star
op_star
id|pernode_pdaindr
suffix:semicolon
multiline_comment|/*&n;         * Data used for migration control&n;         */
DECL|member|mcd
r_struct
id|migr_control_data_s
op_star
id|mcd
suffix:semicolon
multiline_comment|/*&n;         * Data used for replication control&n;         */
DECL|member|rcd
r_struct
id|repl_control_data_s
op_star
id|rcd
suffix:semicolon
multiline_comment|/*&n;         * Numa statistics&n;         */
DECL|member|numa_stats
r_struct
id|numa_stats_s
op_star
id|numa_stats
suffix:semicolon
multiline_comment|/*&n;         * Load distribution&n;         */
DECL|member|memfit_assign
id|uint
id|memfit_assign
suffix:semicolon
multiline_comment|/*&n;         * New extended memory reference counters&n;         */
DECL|member|migr_refcnt_counterbase
r_void
op_star
id|migr_refcnt_counterbase
suffix:semicolon
DECL|member|migr_refcnt_counterbuffer
r_void
op_star
id|migr_refcnt_counterbuffer
suffix:semicolon
DECL|member|migr_refcnt_cbsize
r_int
id|migr_refcnt_cbsize
suffix:semicolon
DECL|member|migr_refcnt_numsets
r_int
id|migr_refcnt_numsets
suffix:semicolon
multiline_comment|/*&n;         * mem_tick quiescing lock&n;         */
DECL|member|mem_tick_lock
id|uint
id|mem_tick_lock
suffix:semicolon
multiline_comment|/*&n;         * Migration candidate set&n;         * by migration prologue intr handler&n;         */
DECL|member|migr_candidate
r_uint64
id|migr_candidate
suffix:semicolon
multiline_comment|/*&n;&t; * Each node gets its own syswait counter to remove contention&n;&t; * on the global one.&n;&t; */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|syswait
r_struct
id|syswait
id|syswait
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* NUMA_BASE */
multiline_comment|/*&n;&t; * Node-specific Zone structures.&n;&t; */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|node_zones
id|zoneset_element_t
id|node_zones
suffix:semicolon
DECL|member|node_pg_data
id|pg_data_t
id|node_pg_data
suffix:semicolon
multiline_comment|/* VM page data structures */
DECL|member|error_discard_plist
id|plist_t
id|error_discard_plist
suffix:semicolon
macro_line|#endif
DECL|member|error_discard_count
id|uint
id|error_discard_count
suffix:semicolon
DECL|member|error_page_count
id|uint
id|error_page_count
suffix:semicolon
DECL|member|error_cleaned_count
id|uint
id|error_cleaned_count
suffix:semicolon
DECL|member|error_discard_lock
id|spinlock_t
id|error_discard_lock
suffix:semicolon
multiline_comment|/* Information needed for SN Hub chip interrupt handling. */
DECL|member|snpda
id|subnode_pda_t
id|snpda
(braket
id|NUM_SUBNODES
)braket
suffix:semicolon
multiline_comment|/* Distributed kernel support */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|kern_vars
id|kern_vars_t
id|kern_vars
suffix:semicolon
macro_line|#endif
multiline_comment|/* Vector operation support */
multiline_comment|/* Change this to a sleep lock? */
DECL|member|vector_lock
id|spinlock_t
id|vector_lock
suffix:semicolon
multiline_comment|/* State of the vector unit for this node */
DECL|member|vector_unit_busy
r_char
id|vector_unit_busy
suffix:semicolon
DECL|member|node_first_cpu
id|cpuid_t
id|node_first_cpu
suffix:semicolon
multiline_comment|/* Starting cpu number for node */
DECL|member|node_num_cpus
id|ushort
id|node_num_cpus
suffix:semicolon
multiline_comment|/* Number of cpus present       */
multiline_comment|/* node utlbmiss info */
DECL|member|node_utlbswitchlock
id|spinlock_t
id|node_utlbswitchlock
suffix:semicolon
DECL|member|node_utlbmiss_flush
r_volatile
id|cpumask_t
id|node_utlbmiss_flush
suffix:semicolon
DECL|member|node_need_utlbmiss_patch
r_volatile
r_int
r_char
id|node_need_utlbmiss_patch
suffix:semicolon
DECL|member|node_utlbmiss_patched
r_volatile
r_char
id|node_utlbmiss_patched
suffix:semicolon
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
DECL|member|dependent_routers
r_int
id|dependent_routers
suffix:semicolon
DECL|member|xbow_vhdl
id|devfs_handle_t
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
DECL|member|module_id
id|moduleid_t
id|module_id
suffix:semicolon
multiline_comment|/* Module ID (redundant local copy) */
DECL|member|module
id|module_t
op_star
id|module
suffix:semicolon
multiline_comment|/* Pointer to containing module */
DECL|member|hub_chip_rev
r_int
id|hub_chip_rev
suffix:semicolon
multiline_comment|/* Rev of my Hub chip */
DECL|member|nasid_mask
r_char
id|nasid_mask
(braket
id|NASID_MASK_BYTES
)braket
suffix:semicolon
multiline_comment|/* Need a copy of the nasid mask&n;&t;&t;&t;&t;&t; * on every node */
DECL|member|basew_id
id|xwidgetnum_t
id|basew_id
suffix:semicolon
DECL|member|basew_xc
id|devfs_handle_t
id|basew_xc
suffix:semicolon
DECL|member|fprom_lock
id|spinlock_t
id|fprom_lock
suffix:semicolon
DECL|member|ni_error_print
r_char
id|ni_error_print
suffix:semicolon
multiline_comment|/* For printing ni error state&n;&t;&t;&t;&t;&t; * only once during system panic&n;&t;&t;&t;&t;&t; */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|node_md_perfmon
id|md_perf_monitor_t
id|node_md_perfmon
suffix:semicolon
DECL|member|hubstats
id|hubstat_t
id|hubstats
suffix:semicolon
DECL|member|hubticks
r_int
id|hubticks
suffix:semicolon
DECL|member|huberror_ticks
r_int
id|huberror_ticks
suffix:semicolon
DECL|member|sbe_info
id|sbe_info_t
op_star
id|sbe_info
suffix:semicolon
multiline_comment|/* ECC single-bit error statistics */
macro_line|#endif&t;/* !CONFIG_IA64_SGI_IO */
DECL|member|visited_router_q
id|router_queue_t
op_star
id|visited_router_q
suffix:semicolon
DECL|member|bfs_router_q
id|router_queue_t
op_star
id|bfs_router_q
suffix:semicolon
multiline_comment|/* Used for router traversal */
macro_line|#if defined (CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|member|router_map
id|router_map_ent_t
id|router_map
(braket
id|MAX_RTR_BREADTH
)braket
suffix:semicolon
macro_line|#endif
DECL|member|num_routers
r_int
id|num_routers
suffix:semicolon
multiline_comment|/* Total routers in the system */
DECL|member|membank_flavor
r_char
id|membank_flavor
suffix:semicolon
multiline_comment|/* Indicates what sort of memory &n;&t;&t;&t;&t;&t; * banks are present on this node&n;&t;&t;&t;&t;&t; */
DECL|member|hwg_node_name
r_char
op_star
id|hwg_node_name
suffix:semicolon
multiline_comment|/* hwgraph node name */
DECL|member|widget_info
r_struct
id|widget_info_t
op_star
id|widget_info
suffix:semicolon
multiline_comment|/* Node as xtalk widget */
DECL|member|node_vertex
id|devfs_handle_t
id|node_vertex
suffix:semicolon
multiline_comment|/* Hwgraph vertex for this node */
DECL|member|pdinfo
r_void
op_star
id|pdinfo
suffix:semicolon
multiline_comment|/* Platform-dependent per-node info */
DECL|member|dump_stack
r_uint64
op_star
id|dump_stack
suffix:semicolon
multiline_comment|/* Dump stack during nmi handling */
DECL|member|dump_count
r_int
id|dump_count
suffix:semicolon
multiline_comment|/* To allow only one cpu-per-node */
macro_line|#if defined BRINGUP
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|node_io_perfmon
id|io_perf_monitor_t
id|node_io_perfmon
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;&t; * Each node gets its own pdcount counter to remove contention&n;&t; * on the global one.&n;&t; */
DECL|member|pdcount
r_int
id|pdcount
suffix:semicolon
multiline_comment|/* count of pdinserted pages */
macro_line|#ifdef&t;NUMA_BASE
DECL|member|cached_global_pool
r_void
op_star
id|cached_global_pool
suffix:semicolon
multiline_comment|/* pointer to cached vmpool */
macro_line|#endif /* NUMA_BASE */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|sanon_list_head
id|sanon_list_head_t
id|sanon_list_head
suffix:semicolon
multiline_comment|/* head for sanon pages */
macro_line|#endif
macro_line|#ifdef&t;NUMA_BASE
DECL|member|ptpool
r_struct
id|ptpool_s
op_star
id|ptpool
suffix:semicolon
multiline_comment|/* ptpool for this node */
macro_line|#endif /* NUMA_BASE */
multiline_comment|/*&n;&t; * The BTEs on this node are shared by the local cpus&n;&t; */
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|member|node_bte_info
id|bteinfo_t
op_star
id|node_bte_info
(braket
id|BTES_PER_NODE
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
suffix:semicolon
DECL|typedef|nodepda_t
r_typedef
r_struct
id|nodepda_s
id|nodepda_t
suffix:semicolon
DECL|macro|NODE_MODULEID
mdefine_line|#define NODE_MODULEID(_node)&t;(NODEPDA(_node)-&gt;module_id)
DECL|macro|NODE_SLOTID
mdefine_line|#define NODE_SLOTID(_node)&t;(NODEPDA(_node)-&gt;slotdesc)
macro_line|#ifdef&t;NUMA_BASE
multiline_comment|/*&n; * Access Functions for node PDA.&n; * Since there is one nodepda for each node, we need a convenient mechanism&n; * to access these nodepdas without cluttering code with #ifdefs.&n; * The next set of definitions provides this.&n; * Routines are expected to use &n; *&n; *&t;nodepda&t;&t;-&gt; to access PDA for the node on which code is running&n; *&t;subnodepda&t;-&gt; to access subnode PDA for the node on which code is running&n; *&n; *&t;NODEPDA(x)&t;-&gt; to access node PDA for cnodeid &squot;x&squot;&n; *&t;SUBNODEPDA(x,s)&t;-&gt; to access subnode PDA for cnodeid/slice &squot;x&squot;&n; */
macro_line|#ifndef CONFIG_IA64_SGI_IO
DECL|macro|nodepda
mdefine_line|#define&t;nodepda&t;&t;private.p_nodepda&t;/* Ptr to this node&squot;s PDA */
macro_line|#if CONFIG_SGI_IP35 || CONFIG_IA64_SGI_SN1 || CONFIG_IA64_GENERIC
DECL|macro|subnodepda
mdefine_line|#define subnodepda&t;private.p_subnodepda&t;/* Ptr to this node&squot;s subnode PDA */
macro_line|#endif
macro_line|#else
multiline_comment|/*&n; * Until we have a shared node local area defined, do it this way ..&n; * like in Caliase space.  See above.&n; */
r_extern
id|nodepda_t
op_star
id|nodepda
suffix:semicolon
r_extern
id|subnode_pda_t
op_star
id|subnodepda
suffix:semicolon
macro_line|#endif
multiline_comment|/* &n; * Nodepdaindr[]&n; * This is a private data structure for use only in early initialization.&n; * All users of nodepda should use the macro NODEPDA(nodenum) to get&n; * the suitable nodepda structure.&n; * This macro has the advantage of not requiring #ifdefs for NUMA and&n; * non-NUMA code.&n; */
r_extern
id|nodepda_t
op_star
id|Nodepdaindr
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * NODEPDA_GLOBAL(x) macro should ONLY be used during early initialization.&n; * Once meminit is complete, NODEPDA(x) is ready to use.&n; * During early init, the system fills up Nodepdaindr.  By the time we&n; * are in meminit(), all nodepdas are initialized, and hence&n; * we can fill up the node_pdaindr array in each nodepda structure.&n; */
DECL|macro|NODEPDA_GLOBAL
mdefine_line|#define&t;NODEPDA_GLOBAL(x)&t;Nodepdaindr[x]
multiline_comment|/*&n; * Returns a pointer to a given node&squot;s nodepda.&n; */
DECL|macro|NODEPDA
mdefine_line|#define&t;NODEPDA(x)&t;&t;(nodepda-&gt;pernode_pdaindr[x])
multiline_comment|/*&n; * Returns a pointer to a given node/slice&squot;s subnodepda.&n; *&t;SUBNODEPDA(cnode, subnode) - uses cnode as first arg&n; *&t;SNPDA(npda, subnode)&t;   - uses pointer to nodepda as first arg&n; */
DECL|macro|SUBNODEPDA
mdefine_line|#define&t;SUBNODEPDA(x,sn)&t;(&amp;nodepda-&gt;pernode_pdaindr[x]-&gt;snpda[sn])
DECL|macro|SNPDA
mdefine_line|#define&t;SNPDA(npda,sn)&t;&t;(&amp;(npda)-&gt;snpda[sn])
DECL|macro|NODEPDA_ERROR_FOOTPRINT
mdefine_line|#define NODEPDA_ERROR_FOOTPRINT(node, cpu) &bslash;&n;                   (&amp;(NODEPDA(node)-&gt;error_stamp[cpu]))
DECL|macro|NODEPDA_MDP_MON
mdefine_line|#define NODEPDA_MDP_MON(node)&t;(&amp;(NODEPDA(node)-&gt;node_md_perfmon))
DECL|macro|NODEPDA_IOP_MON
mdefine_line|#define NODEPDA_IOP_MON(node)&t;(&amp;(NODEPDA(node)-&gt;node_io_perfmon))
multiline_comment|/*&n; * Macros to access data structures inside nodepda &n; */
macro_line|#if NUMA_MIGR_CONTROL
DECL|macro|NODEPDA_MCD
mdefine_line|#define NODEPDA_MCD(node) (NODEPDA(node)-&gt;mcd)
macro_line|#endif /* NUMA_MIGR_CONTROL */
macro_line|#if NUMA_REPL_CONTROL
DECL|macro|NODEPDA_RCD
mdefine_line|#define NODEPDA_RCD(node) (NODEPDA(node)-&gt;rcd)
macro_line|#endif /* NUMA_REPL_CONTROL */
macro_line|#if (NUMA_MIGR_CONTROL || NUMA_REPL_CONTROL)
DECL|macro|NODEPDA_LRS
mdefine_line|#define NODEPDA_LRS(node) (NODEPDA(node)-&gt;lrs)
macro_line|#endif /* (NUMA_MIGR_CONTROL || NUMA_REPL_CONTROL) */
multiline_comment|/* &n; * Exported functions&n; */
r_extern
id|nodepda_t
op_star
id|nodepda_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else&t;/* !NUMA_BASE */
multiline_comment|/*&n; * For a single-node system we will just have one global nodepda pointer&n; * allocated at startup.  The global nodepda will point to this nodepda &n; * structure.&n; */
r_extern
id|nodepda_t
op_star
id|Nodepdaindr
suffix:semicolon
multiline_comment|/*&n; * On non-NUMA systems, NODEPDA_GLOBAL and NODEPDA macros collapse to&n; * be the same.&n; */
DECL|macro|NODEPDA_GLOBAL
mdefine_line|#define&t;NODEPDA_GLOBAL(x)&t;Nodepdaindr
multiline_comment|/*&n; * Returns a pointer to a given node&squot;s nodepda.&n; */
DECL|macro|NODEPDA
mdefine_line|#define&t;NODEPDA(x)&t;Nodepdaindr
multiline_comment|/*&n; * nodepda can also be defined as private.p_nodepda.&n; * But on non-NUMA systems, there is only one nodepda, and there is&n; * no reason to go through the PDA to access this pointer.&n; * Hence nodepda aliases to the global nodepda directly.&n; *&n; * Routines should use nodepda to access the local node&squot;s PDA.&n; */
DECL|macro|nodepda
mdefine_line|#define&t;nodepda&t;&t;(Nodepdaindr)
macro_line|#endif&t;/* NUMA_BASE */
multiline_comment|/* Quickly convert a compact node ID into a hwgraph vertex */
DECL|macro|cnodeid_to_vertex
mdefine_line|#define cnodeid_to_vertex(cnodeid) (NODEPDA(cnodeid)-&gt;node_vertex)
multiline_comment|/* Check if given a compact node id the corresponding node has all the&n; * cpus disabled. &n; */
DECL|macro|is_headless_node
mdefine_line|#define is_headless_node(_cnode)&t;((_cnode == CNODEID_NONE) || &bslash;&n;&t;&t;&t;&t;&t; (CNODE_NUM_CPUS(_cnode) == 0))
multiline_comment|/* Check if given a node vertex handle the corresponding node has all the&n; * cpus disabled. &n; */
DECL|macro|is_headless_node_vertex
mdefine_line|#define is_headless_node_vertex(_nodevhdl) &bslash;&n;&t;&t;&t;is_headless_node(nodevertex_to_cnodeid(_nodevhdl))
macro_line|#ifdef&t;__cplusplus
)brace
macro_line|#endif
macro_line|#ifdef NUMA_BASE
multiline_comment|/*&n; * To remove contention on the global syswait counter each node will have&n; * its own.  Each clock tick the clock cpu will re-calculate the global&n; * syswait counter by summing from each of the nodes.  The other cpus will&n; * continue to read the global one during their clock ticks.   This does &n; * present a problem when a thread increments the count on one node and wakes&n; * up on a different node and decrements it there.  Eventually the count could&n; * overflow if this happens continually for a long period.  To prevent this&n; * second_thread() periodically preserves the current syswait state and&n; * resets the counters.&n; */
DECL|macro|ADD_SYSWAIT
mdefine_line|#define ADD_SYSWAIT(_field)&t;atomicAddInt(&amp;nodepda-&gt;syswait._field, 1)
DECL|macro|SUB_SYSWAIT
mdefine_line|#define SUB_SYSWAIT(_field)&t;atomicAddInt(&amp;nodepda-&gt;syswait._field, -1)
macro_line|#else
DECL|macro|ADD_SYSWAIT
mdefine_line|#define ADD_SYSWAIT(_field)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT(syswait._field &gt;= 0);&t;&t;&t;&bslash;&n;&t;atomicAddInt(&amp;syswait._field, 1);&t;&t;&bslash;&n;}
DECL|macro|SUB_SYSWAIT
mdefine_line|#define SUB_SYSWAIT(_field)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT(syswait._field &gt; 0);&t;&t;&t;&bslash;&n;&t;atomicAddInt(&amp;syswait._field, -1);&t;&t;&bslash;&n;}
macro_line|#endif /* NUMA_BASE */
macro_line|#ifdef NUMA_BASE
multiline_comment|/*&n; * Another global variable to remove contention from: pdcount.&n; * See above comments for SYSWAIT.&n; */
DECL|macro|ADD_PDCOUNT
mdefine_line|#define ADD_PDCOUNT(_n)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;atomicAddInt(&amp;nodepda-&gt;pdcount, _n);&t;&t;&bslash;&n;&t;if (_n &gt; 0 &amp;&amp; !pdflag)&t;&t;&t;&t;&bslash;&n;&t;&t;pdflag = 1;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|ADD_PDCOUNT
mdefine_line|#define ADD_PDCOUNT(_n)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT(&amp;pdcount &gt;= 0);&t;&t;&t;&t;&bslash;&n;&t;atomicAddInt(&amp;pdcount, _n);&t;&t;&t;&bslash;&n;&t;if (_n &gt; 0 &amp;&amp; !pdflag)&t;&t;&t;&t;&bslash;&n;&t;&t;pdflag = 1;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* NUMA_BASE */
macro_line|#endif /* _ASM_SN_NODEPDA_H */
eof
