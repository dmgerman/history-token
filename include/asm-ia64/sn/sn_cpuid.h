multiline_comment|/* &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN_CPUID_H
DECL|macro|_ASM_IA64_SN_SN_CPUID_H
mdefine_line|#define _ASM_IA64_SN_SN_CPUID_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
multiline_comment|/*&n; * Functions for converting between cpuids, nodeids and NASIDs.&n; * &n; * These are for SGI platforms only.&n; *&n; */
multiline_comment|/*&n; *  Definitions of terms (these definitions are for IA64 ONLY. Other architectures&n; *  use cpuid/cpunum quite defferently):&n; *&n; *&t;   CPUID - a number in range of 0..NR_CPUS-1 that uniquely identifies&n; *&t;&t;the cpu. The value cpuid has no significance on IA64 other than&n; *&t;&t;the boot cpu is 0.&n; *&t;&t;&t;smp_processor_id() returns the cpuid of the current cpu.&n; *&n; * &t;   CPU_PHYSICAL_ID (also known as HARD_PROCESSOR_ID)&n; *&t;&t;This is the same as 31:24 of the processor LID register&n; *&t;&t;&t;hard_smp_processor_id()- cpu_physical_id of current processor&n; *&t;&t;&t;cpu_physical_id(cpuid) - convert a &lt;cpuid&gt; to a &lt;physical_cpuid&gt;&n; *&t;&t;&t;cpu_logical_id(phy_id) - convert a &lt;physical_cpuid&gt; to a &lt;cpuid&gt; &n; *&t;&t;&t;&t;* not real efficient - don&squot;t use in perf critical code&n; *&n; *         SLICE - a number in the range of 0 - 3 (typically) that represents the&n; *&t;&t;cpu number on a brick.&n; *&n; *&t;   SUBNODE - (almost obsolete) the number of the FSB that a cpu is&n; *&t;&t;connected to. This is also the same as the PI number. Usually 0 or 1.&n; *&n; *&t;NOTE!!!: the value of the bits in the cpu physical id (SAPICid or LID) of a cpu has no &n; *&t;significance. The SAPIC id (LID) is a 16-bit cookie that has meaning only to the PROM.&n; *&n; *&n; * The macros convert between cpu physical ids &amp; slice/nasid/cnodeid.&n; * These terms are described below:&n; *&n; *&n; * Brick&n; *          -----   -----           -----   -----       CPU&n; *          | 0 |   | 1 |           | 0 |   | 1 |       SLICE&n; *          -----   -----           -----   -----&n; *            |       |               |       |&n; *            |       |               |       |&n; *          0 |       | 2           0 |       | 2       FSB SLOT&n; *             -------                 -------  &n; *                |                       |&n; *                |                       |&n; *                |                       |&n; *             ------------      -------------&n; *             |          |      |           |&n; *             |    SHUB  |      |   SHUB    |        NASID   (0..MAX_NASIDS)&n; *             |          |----- |           |        CNODEID (0..num_compact_nodes-1)&n; *             |          |      |           |&n; *             |          |      |           |&n; *             ------------      -------------&n; *                   |                 |&n; *                           &n; *&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|cpu_logical_id
mdefine_line|#define cpu_logical_id(cpu)&t;&t;&t;0
DECL|macro|cpu_physical_id
mdefine_line|#define cpu_physical_id(cpuid)&t;&t;&t;((ia64_getreg(_IA64_REG_CR_LID) &gt;&gt; 16) &amp; 0xffff)
macro_line|#endif
DECL|macro|get_node_number
mdefine_line|#define get_node_number(addr)&t;&t;&t;NASID_GET(addr)
multiline_comment|/*&n; * NOTE: on non-MP systems, only cpuid 0 exists&n; */
r_extern
r_int
id|physical_node_map
(braket
)braket
suffix:semicolon
multiline_comment|/* indexed by nasid to get cnode */
multiline_comment|/*&n; * Macros for retrieving info about current cpu&n; */
DECL|macro|get_nasid
mdefine_line|#define get_nasid()&t;&t;&t;(nodepda-&gt;phys_cpuid[smp_processor_id()].nasid)
DECL|macro|get_subnode
mdefine_line|#define get_subnode()&t;&t;&t;(nodepda-&gt;phys_cpuid[smp_processor_id()].subnode)
DECL|macro|get_slice
mdefine_line|#define get_slice()&t;&t;&t;(nodepda-&gt;phys_cpuid[smp_processor_id()].slice)
DECL|macro|get_cnode
mdefine_line|#define get_cnode()&t;&t;&t;(nodepda-&gt;phys_cpuid[smp_processor_id()].cnode)
DECL|macro|get_sapicid
mdefine_line|#define get_sapicid()&t;&t;&t;((ia64_getreg(_IA64_REG_CR_LID) &gt;&gt; 16) &amp; 0xffff)
multiline_comment|/*&n; * Macros for retrieving info about an arbitrary cpu&n; *&t;cpuid - logical cpu id&n; */
DECL|macro|cpuid_to_nasid
mdefine_line|#define cpuid_to_nasid(cpuid)&t;&t;(nodepda-&gt;phys_cpuid[cpuid].nasid)
DECL|macro|cpuid_to_subnode
mdefine_line|#define cpuid_to_subnode(cpuid)&t;&t;(nodepda-&gt;phys_cpuid[cpuid].subnode)
DECL|macro|cpuid_to_slice
mdefine_line|#define cpuid_to_slice(cpuid)&t;&t;(nodepda-&gt;phys_cpuid[cpuid].slice)
DECL|macro|cpuid_to_cnodeid
mdefine_line|#define cpuid_to_cnodeid(cpuid)&t;&t;(physical_node_map[cpuid_to_nasid(cpuid)])
multiline_comment|/*&n; * Dont use the following in performance critical code. They require scans&n; * of potentially large tables.&n; */
r_extern
r_int
id|nasid_slice_to_cpuid
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|nasid_slice_to_cpu_physical_id
mdefine_line|#define nasid_slice_to_cpu_physical_id(nasid, slice)&t;&t;&t;&bslash;&n;&t;cpu_physical_id(nasid_slice_to_cpuid(nasid, slice))
multiline_comment|/*&n; * cnodeid_to_nasid - convert a cnodeid to a NASID&n; *&t;Macro relies on pg_data for a node being on the node itself.&n; *&t;Just extract the NASID from the pointer.&n; *&n; */
DECL|macro|cnodeid_to_nasid
mdefine_line|#define cnodeid_to_nasid(cnodeid)&t;pda-&gt;cnodeid_to_nasid_table[cnodeid]
multiline_comment|/*&n; * nasid_to_cnodeid - convert a NASID to a cnodeid&n; */
DECL|macro|nasid_to_cnodeid
mdefine_line|#define nasid_to_cnodeid(nasid)&t;&t;(physical_node_map[nasid])
multiline_comment|/*&n; * partition_coherence_id - cget the coherence ID of the current partition&n; */
DECL|macro|partition_coherence_id
mdefine_line|#define partition_coherence_id()&t;(get_nasid() &gt;&gt; 9)
macro_line|#endif /* _ASM_IA64_SN_SN_CPUID_H */
eof
