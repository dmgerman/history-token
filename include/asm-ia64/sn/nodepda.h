multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_NODEPDA_H
DECL|macro|_ASM_IA64_SN_NODEPDA_H
mdefine_line|#define _ASM_IA64_SN_NODEPDA_H
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
multiline_comment|/*&n; * NUMA Node-Specific Data structures are defined in this file.&n; * In particular, this is the location of the node PDA.&n; * A pointer to the right node PDA is saved in each CPU PDA.&n; */
multiline_comment|/*&n; * Node-specific data structure.&n; *&n; * One of these structures is allocated on each node of a NUMA system.&n; *&n; * This structure provides a convenient way of keeping together &n; * all per-node data structures. &n; */
DECL|struct|phys_cpuid
r_struct
id|phys_cpuid
(brace
DECL|member|nasid
r_int
id|nasid
suffix:semicolon
DECL|member|subnode
r_char
id|subnode
suffix:semicolon
DECL|member|slice
r_char
id|slice
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nodepda_s
r_struct
id|nodepda_s
(brace
DECL|member|pdinfo
r_void
op_star
id|pdinfo
suffix:semicolon
multiline_comment|/* Platform-dependent per-node info */
DECL|member|bist_lock
id|spinlock_t
id|bist_lock
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
multiline_comment|/*&n;&t; * Array of physical cpu identifiers. Indexed by cpuid.&n;&t; */
DECL|member|phys_cpuid
r_struct
id|phys_cpuid
id|phys_cpuid
(braket
id|NR_CPUS
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
multiline_comment|/*&n; * Access Functions for node PDA.&n; * Since there is one nodepda for each node, we need a convenient mechanism&n; * to access these nodepdas without cluttering code with #ifdefs.&n; * The next set of definitions provides this.&n; * Routines are expected to use &n; *&n; *&t;nodepda&t;&t;&t;-&gt; to access node PDA for the node on which code is running&n; *&t;subnodepda&t;&t;-&gt; to access subnode PDA for the subnode on which code is running&n; *&n; *&t;NODEPDA(cnode)&t;&t;-&gt; to access node PDA for cnodeid &n; *&t;SUBNODEPDA(cnode,sn)&t;-&gt; to access subnode PDA for cnodeid/subnode&n; */
DECL|macro|nodepda
mdefine_line|#define&t;nodepda&t;&t;pda-&gt;p_nodepda&t;&t;/* Ptr to this node&squot;s PDA */
DECL|macro|NODEPDA
mdefine_line|#define&t;NODEPDA(cnode)&t;&t;(nodepda-&gt;pernode_pdaindr[cnode])
multiline_comment|/*&n; * Check if given a compact node id the corresponding node has all the&n; * cpus disabled. &n; */
DECL|macro|is_headless_node
mdefine_line|#define is_headless_node(cnode)&t;&t;(nr_cpus_node(cnode) == 0)
macro_line|#endif /* _ASM_IA64_SN_NODEPDA_H */
eof
