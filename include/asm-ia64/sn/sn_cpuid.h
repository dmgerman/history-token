multiline_comment|/* &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN_CPUID_H
DECL|macro|_ASM_IA64_SN_SN_CPUID_H
mdefine_line|#define _ASM_IA64_SN_SN_CPUID_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/nodedata.h&gt;
multiline_comment|/*&n; * Functions for converting between cpuids, nodeids and NASIDs.&n; * &n; * These are for SGI platforms only.&n; *&n; */
multiline_comment|/*&n; *  Definitions of terms (these definitions are for IA64 ONLY. Other architectures&n; *  use cpuid/cpunum quite defferently):&n; *&n; *&t;   CPUID - a number in range of 0..NR_CPUS-1 that uniquely identifies&n; *&t;&t;the cpu. The value cpuid has no significance on IA64 other than&n; *&t;&t;the boot cpu is 0.&n; *&t;&t;&t;smp_processor_id() returns the cpuid of the current cpu.&n; *&n; *&t;   CPUNUM - On IA64, a cpunum and cpuid are the same. This is NOT true&n; *&t;&t;on other architectures like IA32.&n; *&n; * &t;   CPU_PHYSICAL_ID (also known as HARD_PROCESSOR_ID)&n; *&t;&t;This is the same as 31:24 of the processor LID register&n; *&t;&t;&t;hard_smp_processor_id()- cpu_physical_id of current processor&n; *&t;&t;&t;cpu_physical_id(cpuid) - convert a &lt;cpuid&gt; to a &lt;physical_cpuid&gt;&n; *&t;&t;&t;cpu_logical_id(phy_id) - convert a &lt;physical_cpuid&gt; to a &lt;cpuid&gt; &n; *&t;&t;&t;&t;* not real efficient - dont use in perf critical code&n; *&n; *         LID - processor defined register (see PRM V2).&n; *&n; *           On SN1&n; *&t;&t;31:24 - id   Contains the NASID&n; *&t;&t;23:16 - eid  Contains 0-3 to identify the cpu on the node&n; *&t;&t;&t;&t;bit 17 - synergy number&n; *&t;&t;&t;&t;bit 16 - FSB slot number &n; *           On SN2&n; *&t;&t;31:28 - id   Contains 0-3 to identify the cpu on the node&n; *&t;&t;27:16 - eid  Contains the NASID&n; *&n; *&n; *&n; * The following assumes the following mappings for LID register values:&n; *&n; * The macros convert between cpu physical ids &amp; slice/fsb/synergy/nasid/cnodeid.&n; * These terms are described below:&n; *&n; *&n; *          -----   -----           -----   -----       CPU&n; *          | 0 |   | 1 |           | 2 |   | 3 |       SLICE&n; *          -----   -----           -----   -----&n; *            |       |               |       |&n; *            |       |               |       |&n; *          0 |       | 1           0 |       | 1       FSB SLOT&n; *             -------                 -------  &n; *                |                       |&n; *                |                       |&n; *             -------                 -------&n; *             |     |                 |     |&n; *             |  0  |                 |  1  |         SYNERGY (SN1 only)&n; *             |     |                 |     |&n; *             -------                 -------&n; *                |                       |&n; *                |                       |&n; *             -------------------------------&n; *             |                             |&n; *             |         BEDROCK / SHUB      |        NASID   (0..MAX_NASIDS)&n; *             |                             |        CNODEID (0..num_compact_nodes-1)&n; *             |                             |&n; *             |                             |&n; *             -------------------------------&n; *                           |&n; *&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|cpu_logical_id
mdefine_line|#define cpu_logical_id(cpu)&t;&t;&t;&t;0
DECL|macro|cpu_physical_id
mdefine_line|#define cpu_physical_id(cpuid)&t;&t;&t;((ia64_get_lid() &gt;&gt; 16) &amp; 0xffff)
macro_line|#endif
macro_line|#ifdef CONFIG_IA64_SGI_SN1
multiline_comment|/*&n; * macros for some of these exist in sn/addrs.h &amp; sn/arch.h, etc. However, &n; * trying #include these files here causes circular dependencies.&n; */
DECL|macro|cpu_physical_id_to_nasid
mdefine_line|#define cpu_physical_id_to_nasid(cpi)&t;&t;((cpi) &gt;&gt; 8)
DECL|macro|cpu_physical_id_to_synergy
mdefine_line|#define cpu_physical_id_to_synergy(cpi)&t;&t;(((cpi) &gt;&gt; 1) &amp; 1)
DECL|macro|cpu_physical_id_to_fsb_slot
mdefine_line|#define cpu_physical_id_to_fsb_slot(cpi)&t;((cpi) &amp; 1)
DECL|macro|cpu_physical_id_to_slice
mdefine_line|#define cpu_physical_id_to_slice(cpi)&t;&t;((cpi) &amp; 3)
DECL|macro|get_nasid
mdefine_line|#define get_nasid()&t;&t;&t;&t;((ia64_get_lid() &gt;&gt; 24))
DECL|macro|get_slice
mdefine_line|#define get_slice()&t;&t;&t;&t;((ia64_get_lid() &gt;&gt; 16) &amp; 3)
DECL|macro|get_node_number
mdefine_line|#define get_node_number(addr)&t;&t;&t;(((unsigned long)(addr)&gt;&gt;33) &amp; 0x7f)
macro_line|#else
DECL|macro|cpu_physical_id_to_nasid
mdefine_line|#define cpu_physical_id_to_nasid(cpi)&t;&t;((cpi) &amp;0xfff)
DECL|macro|cpu_physical_id_to_slice
mdefine_line|#define cpu_physical_id_to_slice(cpi)&t;&t;((cpi&gt;&gt;12) &amp; 3)
DECL|macro|get_nasid
mdefine_line|#define get_nasid()&t;&t;&t;&t;((ia64_get_lid() &gt;&gt; 16) &amp; 0xfff)
DECL|macro|get_slice
mdefine_line|#define get_slice()&t;&t;&t;&t;((ia64_get_lid() &gt;&gt; 28) &amp; 0xf)
DECL|macro|get_node_number
mdefine_line|#define get_node_number(addr)&t;&t;&t;(((unsigned long)(addr)&gt;&gt;38) &amp; 0x7ff)
macro_line|#endif
multiline_comment|/*&n; * NOTE: id &amp; eid refer to Intels definitions of the LID register&n; *&t;(id = NASID, eid = slice)&n; * NOTE: on non-MP systems, only cpuid 0 exists&n; */
DECL|macro|id_eid_to_cpu_physical_id
mdefine_line|#define id_eid_to_cpu_physical_id(id,eid)       (((id)&lt;&lt;8) | (eid))
DECL|macro|id_eid_to_cpuid
mdefine_line|#define id_eid_to_cpuid(id,eid)         &t;(cpu_logical_id(id_eid_to_cpu_physical_id((id),(eid))))
multiline_comment|/*&n; * The following table/struct  is used for managing PTC coherency domains.&n; */
r_typedef
r_struct
(brace
DECL|member|domain
id|u8
id|domain
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|sapicid
id|u16
id|sapicid
suffix:semicolon
DECL|typedef|sn_sapicid_info_t
)brace
id|sn_sapicid_info_t
suffix:semicolon
r_extern
id|sn_sapicid_info_t
id|sn_sapicid_info
(braket
)braket
suffix:semicolon
multiline_comment|/* indexed by cpuid */
macro_line|#ifdef CONFIG_IA64_SGI_SN1
multiline_comment|/*&n; * cpuid_to_fsb_slot  - convert a cpuid to the fsb slot number that it is in.&n; *   (there are 2 cpus per FSB. This function returns 0 or 1)&n; */
DECL|macro|cpuid_to_fsb_slot
mdefine_line|#define cpuid_to_fsb_slot(cpuid)&t;(cpu_physical_id_to_fsb_slot(cpu_physical_id(cpuid)))
multiline_comment|/*&n; * cpuid_to_synergy  - convert a cpuid to the synergy that it resides on&n; *   (there are 2 synergies per node. Function returns 0 or 1 to&n; *    specify which synergy the cpu is on)&n; */
DECL|macro|cpuid_to_synergy
mdefine_line|#define cpuid_to_synergy(cpuid)&t;&t;(cpu_physical_id_to_synergy(cpu_physical_id(cpuid)))
macro_line|#endif
multiline_comment|/*&n; * cpuid_to_slice  - convert a cpuid to the slice that it resides on&n; *  There are 4 cpus per node. This function returns 0 .. 3)&n; */
DECL|macro|cpuid_to_slice
mdefine_line|#define cpuid_to_slice(cpuid)&t;&t;(cpu_physical_id_to_slice(cpu_physical_id(cpuid)))
multiline_comment|/*&n; * cpuid_to_nasid  - convert a cpuid to the NASID that it resides on&n; */
DECL|macro|cpuid_to_nasid
mdefine_line|#define cpuid_to_nasid(cpuid)&t;&t;(cpu_physical_id_to_nasid(cpu_physical_id(cpuid)))
multiline_comment|/*&n; * cpuid_to_cnodeid  - convert a cpuid to the cnode that it resides on&n; */
DECL|macro|cpuid_to_cnodeid
mdefine_line|#define cpuid_to_cnodeid(cpuid)&t;&t;(local_node_data-&gt;physical_node_map[cpuid_to_nasid(cpuid)])
multiline_comment|/*&n; * cnodeid_to_nasid - convert a cnodeid to a NASID&n; *&t;Macro relies on pg_data for a node being on the node itself.&n; *&t;Just extract the NASID from the pointer.&n; *&n; */
DECL|macro|cnodeid_to_nasid
mdefine_line|#define cnodeid_to_nasid(cnodeid)&t;(get_node_number(local_node_data-&gt;pg_data_ptrs[cnodeid]))
multiline_comment|/*&n; * nasid_to_cnodeid - convert a NASID to a cnodeid&n; */
DECL|macro|nasid_to_cnodeid
mdefine_line|#define nasid_to_cnodeid(nasid)&t;&t;(local_node_data-&gt;physical_node_map[nasid])
multiline_comment|/*&n; * cnode_slice_to_cpuid - convert a codeid &amp; slice to a cpuid&n; */
DECL|macro|cnode_slice_to_cpuid
mdefine_line|#define cnode_slice_to_cpuid(cnodeid,slice) (id_eid_to_cpuid(cnodeid_to_nasid(cnodeid),(slice)))
multiline_comment|/*&n; * cpuid_to_subnode - convert a cpuid to the subnode it resides on.&n; *   slice 0 &amp; 1 are on subnode 0&n; *   slice 2 &amp; 3 are on subnode 1.&n; */
DECL|macro|cpuid_to_subnode
mdefine_line|#define cpuid_to_subnode(cpuid)&t;&t;((cpuid_to_slice(cpuid)&lt;2) ? 0 : 1)
multiline_comment|/*&n; * cpuid_to_localslice - convert a cpuid to a local slice&n; *    slice 0 &amp; 2 are local slice 0&n; *    slice 1 &amp; 3 are local slice 1&n; */
DECL|macro|cpuid_to_localslice
mdefine_line|#define cpuid_to_localslice(cpuid)&t;(cpuid_to_slice(cpuid) &amp; 1)
DECL|macro|smp_physical_node_id
mdefine_line|#define smp_physical_node_id()&t;&t;&t;(cpuid_to_nasid(smp_processor_id()))
multiline_comment|/*&n; * cnodeid_to_cpuid - convert a cnode  to a cpuid of a cpu on the node.&n; *&t;returns -1 if no cpus exist on the node&n; */
r_extern
r_int
id|cnodeid_to_cpuid
c_func
(paren
r_int
id|cnode
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SN_CPUID_H */
eof
