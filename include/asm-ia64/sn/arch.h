multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SN_ARCH_H
DECL|macro|_ASM_SN_ARCH_H
mdefine_line|#define _ASM_SN_ARCH_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#if defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_SGI_IP37) || defined(CONFIG_IA64_GENERIC)
macro_line|#include &lt;asm/sn/sn1/arch.h&gt;
macro_line|#endif
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
DECL|typedef|hubreg_t
r_typedef
id|u64
id|hubreg_t
suffix:semicolon
DECL|typedef|nic_t
r_typedef
id|u64
id|nic_t
suffix:semicolon
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|typedef|bdrkreg_t
r_typedef
id|u64
id|bdrkreg_t
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SGI_xxxxx */
macro_line|#endif&t;/* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|macro|CPUS_PER_NODE
mdefine_line|#define CPUS_PER_NODE&t;&t;4&t;/* CPUs on a single hub */
DECL|macro|CPUS_PER_NODE_SHFT
mdefine_line|#define CPUS_PER_NODE_SHFT&t;2&t;/* Bits to shift in the node number */
DECL|macro|CPUS_PER_SUBNODE
mdefine_line|#define CPUS_PER_SUBNODE&t;2&t;/* CPUs on a single hub PI */
macro_line|#endif
DECL|macro|CNODE_NUM_CPUS
mdefine_line|#define CNODE_NUM_CPUS(_cnode)&t;&t;(NODEPDA(_cnode)-&gt;node_num_cpus)
DECL|macro|CNODE_TO_CPU_BASE
mdefine_line|#define CNODE_TO_CPU_BASE(_cnode)&t;(NODEPDA(_cnode)-&gt;node_first_cpu)
DECL|macro|makespnum
mdefine_line|#define makespnum(_nasid, _slice)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((_nasid) &lt;&lt; CPUS_PER_NODE_SHFT) | (_slice))
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
multiline_comment|/*&n; * There are 2 very similar macros for dealing with &quot;slices&quot;. Make sure&n; * you use the right one. &n; * Unfortunately, on all platforms except IP35 (currently), the 2 macros &n; * are interchangible. &n; *&n; * On IP35, there are 4 cpus per node. Each cpu is refered to by it&squot;s slice.&n; * The slices are numbered 0 thru 3. &n; *&n; * There are also 2 PI interfaces per node. Each PI interface supports 2 cpus.&n; * The term &quot;local slice&quot; specifies the cpu number relative to the PI.&n; *&n; * The cpus on the node are numbered:&n; *&t;slice&t;localslice&n; *&t;  0          0&n; *&t;  1          1&n; *&t;  2          0&n; *&t;  3          1&n; *&n; *&t;cputoslice - returns a number 0..3 that is the slice of the specified cpu.&n; *&t;cputolocalslice - returns a number 0..1 that identifies the local slice of&n; *&t;&t;&t;the cpu within it&squot;s PI interface.&n; */
macro_line|#ifdef LATER
multiline_comment|/* These are dummied up for now ..... */
DECL|macro|cputocnode
mdefine_line|#define cputocnode(cpu)&t;&t;&t;&t;&bslash;&n;               (pdaindr[(cpu)].p_nodeid)
DECL|macro|cputonasid
mdefine_line|#define cputonasid(cpu)&t;&t;&t;&t;&bslash;&n;               (pdaindr[(cpu)].p_nasid)
DECL|macro|cputoslice
mdefine_line|#define cputoslice(cpu)&t;&t;&t;&t;&bslash;&n;               (ASSERT(pdaindr[(cpu)].pda), (pdaindr[(cpu)].pda-&gt;p_slice))
DECL|macro|cputolocalslice
mdefine_line|#define cputolocalslice(cpu)&t;&t;&t;&bslash;&n;               (ASSERT(pdaindr[(cpu)].pda), (LOCALCPU(pdaindr[(cpu)].pda-&gt;p_slice)))
DECL|macro|cputosubnode
mdefine_line|#define cputosubnode(cpu)&t;&t;&t;&bslash;&n;&t;&t;(ASSERT(pdaindr[(cpu)].pda), (SUBNODE(pdaindr[(cpu)].pda-&gt;p_slice)))
macro_line|#else
DECL|macro|cputocnode
mdefine_line|#define cputocnode(cpu) 0
DECL|macro|cputonasid
mdefine_line|#define cputonasid(cpu) 0
DECL|macro|cputoslice
mdefine_line|#define cputoslice(cpu) 0
DECL|macro|cputolocalslice
mdefine_line|#define cputolocalslice(cpu) 0
DECL|macro|cputosubnode
mdefine_line|#define cputosubnode(cpu) 0
macro_line|#endif&t;/* LATER */
macro_line|#endif&t;/* CONFIG_SGI_IP35 */
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
DECL|macro|INVALID_NASID
mdefine_line|#define INVALID_NASID&t;&t;(nasid_t)-1
DECL|macro|INVALID_CNODEID
mdefine_line|#define INVALID_CNODEID&t;&t;(cnodeid_t)-1
DECL|macro|INVALID_PNODEID
mdefine_line|#define INVALID_PNODEID&t;&t;(pnodeid_t)-1
DECL|macro|INVALID_MODULE
mdefine_line|#define INVALID_MODULE&t;&t;(moduleid_t)-1
DECL|macro|INVALID_PARTID
mdefine_line|#define&t;INVALID_PARTID&t;&t;(partid_t)-1
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
r_extern
r_int
id|get_slice
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|cpuid_t
id|get_cnode_cpu
c_func
(paren
id|cnodeid_t
)paren
suffix:semicolon
r_extern
r_int
id|get_cpu_slice
c_func
(paren
id|cpuid_t
)paren
suffix:semicolon
r_extern
id|cpuid_t
id|cnodetocpu
c_func
(paren
id|cnodeid_t
)paren
suffix:semicolon
singleline_comment|// extern cpuid_t cnode_slice_to_cpuid(cnodeid_t, int);
r_extern
r_int
id|cnode_exists
c_func
(paren
id|cnodeid_t
id|cnode
)paren
suffix:semicolon
r_extern
id|cnodeid_t
id|cpuid_to_compact_node
(braket
id|MAXCPUS
)braket
suffix:semicolon
macro_line|#endif&t;/* CONFIG_IP35 */
r_extern
id|nasid_t
id|get_nasid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|cnodeid_t
id|get_cpu_cnode
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|get_cpu_slice
c_func
(paren
id|cpuid_t
)paren
suffix:semicolon
multiline_comment|/*&n; * NO ONE should access these arrays directly.  The only reason we refer to&n; * them here is to avoid the procedure call that would be required in the&n; * macros below.  (Really want private data members here :-)&n; */
r_extern
id|cnodeid_t
id|nasid_to_compact_node
(braket
id|MAX_NASIDS
)braket
suffix:semicolon
r_extern
id|nasid_t
id|compact_to_nasid_node
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
multiline_comment|/*&n; * These macros are used by various parts of the kernel to convert&n; * between the three different kinds of node numbering.   At least some&n; * of them may change to procedure calls in the future, but the macros&n; * will continue to work.  Don&squot;t use the arrays above directly.&n; */
DECL|macro|NASID_TO_REGION
mdefine_line|#define&t;NASID_TO_REGION(nnode)&t;      &t;&bslash;&n;    ((nnode) &gt;&gt; &bslash;&n;     (is_fine_dirmode() ? NASID_TO_FINEREG_SHFT : NASID_TO_COARSEREG_SHFT))
macro_line|#ifndef __ia64
r_extern
id|cnodeid_t
id|nasid_to_compact_node
(braket
id|MAX_NASIDS
)braket
suffix:semicolon
r_extern
id|nasid_t
id|compact_to_nasid_node
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
r_extern
id|cnodeid_t
id|cpuid_to_compact_node
(braket
id|MAXCPUS
)braket
suffix:semicolon
macro_line|#if !defined(DEBUG)
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nnode)&t;(nasid_to_compact_node[nnode])
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)&t;(compact_to_nasid_node[cnode])
DECL|macro|CPUID_TO_COMPACT_NODEID
mdefine_line|#define CPUID_TO_COMPACT_NODEID(cpu)&t;(cpuid_to_compact_node[(cpu)])
macro_line|#else
multiline_comment|/*&n; * These functions can do type checking and fail if they need to return&n; * a bad nodeid, but they&squot;re not as fast so just use &squot;em for debug kernels.&n; */
id|cnodeid_t
id|nasid_to_compact_nodeid
c_func
(paren
id|nasid_t
id|nasid
)paren
suffix:semicolon
id|nasid_t
id|compact_to_nasid_nodeid
c_func
(paren
id|cnodeid_t
id|cnode
)paren
suffix:semicolon
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nnode)&t;nasid_to_compact_nodeid(nnode)
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)&t;compact_to_nasid_nodeid(cnode)
DECL|macro|CPUID_TO_COMPACT_NODEID
mdefine_line|#define CPUID_TO_COMPACT_NODEID(cpu)&t;(cpuid_to_compact_node[(cpu)])
macro_line|#endif
macro_line|#else
multiline_comment|/*&n; * IA64 specific nasid and cnode ids.&n; */
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nasid)  (nasid_to_cnodeid(nasid))
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)  (cnodeid_to_nasid(cnode))
DECL|macro|CPUID_TO_COMPACT_NODEID
mdefine_line|#define CPUID_TO_COMPACT_NODEID(cpu)    (cpuid_to_cnodeid(cpu))
macro_line|#endif /* #ifndef __ia64 */
r_extern
r_int
id|node_getlastslot
c_func
(paren
id|cnodeid_t
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
DECL|macro|SLOT_BITMASK
mdefine_line|#define SLOT_BITMASK    &t;(MAX_MEM_SLOTS - 1)
DECL|macro|SLOT_SIZE
mdefine_line|#define SLOT_SIZE&t;&t;(1LL&lt;&lt;SLOT_SHIFT)
DECL|macro|node_getnumslots
mdefine_line|#define node_getnumslots(node)&t;(MAX_MEM_SLOTS)
DECL|macro|NODE_MAX_MEM_SIZE
mdefine_line|#define NODE_MAX_MEM_SIZE&t;SLOT_SIZE * MAX_MEM_SLOTS
multiline_comment|/*&n; * New stuff in here from Irix sys/pfdat.h.&n; */
DECL|macro|SLOT_PFNSHIFT
mdefine_line|#define&t;SLOT_PFNSHIFT&t;&t;(SLOT_SHIFT - PAGE_SHIFT)
DECL|macro|PFN_NASIDSHFT
mdefine_line|#define&t;PFN_NASIDSHFT&t;&t;(NASID_SHFT - PAGE_SHIFT)
DECL|macro|mkpfn
mdefine_line|#define mkpfn(nasid, off)&t;(((pfn_t)(nasid) &lt;&lt; PFN_NASIDSHFT) | (off))
DECL|macro|slot_getbasepfn
mdefine_line|#define slot_getbasepfn(node,slot) &bslash;&n;&t;&t;(mkpfn(COMPACT_TO_NASID_NODEID(node), slot&lt;&lt;SLOT_PFNSHIFT))
macro_line|#endif /* _ASM_SN_ARCH_H */
eof
