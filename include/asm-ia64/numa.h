multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains NUMA specific prototypes and definitions.&n; * &n; * 2002/08/05 Erich Focht &lt;efocht@ess.nec.de&gt;&n; *&n; */
macro_line|#ifndef _ASM_IA64_NUMA_H
DECL|macro|_ASM_IA64_NUMA_H
mdefine_line|#define _ASM_IA64_NUMA_H
macro_line|#ifdef CONFIG_NUMA
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|# include &lt;asm/mmzone.h&gt;
DECL|macro|NR_NODES
macro_line|# define NR_NODES     (PLAT_MAX_COMPACT_NODES)
DECL|macro|NR_MEMBLKS
macro_line|# define NR_MEMBLKS   (PLAT_MAXCLUMPS)
macro_line|#else
DECL|macro|NR_NODES
macro_line|# define NR_NODES     (8)
DECL|macro|NR_MEMBLKS
macro_line|# define NR_MEMBLKS   (NR_NODES * 8)
macro_line|#endif
multiline_comment|/* Stuff below this line could be architecture independent */
r_extern
r_int
id|num_memblks
suffix:semicolon
multiline_comment|/* total number of memory chunks */
multiline_comment|/*&n; * List of node memory chunks. Filled when parsing SRAT table to&n; * obtain information about memory nodes.&n;*/
DECL|struct|node_memblk_s
r_struct
id|node_memblk_s
(brace
DECL|member|start_paddr
r_int
r_int
id|start_paddr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|nid
r_int
id|nid
suffix:semicolon
multiline_comment|/* which logical node contains this chunk? */
DECL|member|bank
r_int
id|bank
suffix:semicolon
multiline_comment|/* which mem bank on this node */
)brace
suffix:semicolon
DECL|struct|node_cpuid_s
r_struct
id|node_cpuid_s
(brace
DECL|member|phys_id
id|u16
id|phys_id
suffix:semicolon
multiline_comment|/* id &lt;&lt; 8 | eid */
DECL|member|nid
r_int
id|nid
suffix:semicolon
multiline_comment|/* logical node containing this CPU */
)brace
suffix:semicolon
r_extern
r_struct
id|node_memblk_s
id|node_memblk
(braket
id|NR_MEMBLKS
)braket
suffix:semicolon
r_extern
r_struct
id|node_cpuid_s
id|node_cpuid
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 SLIT (System Locality Information Table)&n; * http://devresource.hp.com/devresource/Docs/TechPapers/IA64/slit.pdf&n; *&n; * This is a matrix with &quot;distances&quot; between nodes, they should be&n; * proportional to the memory access latency ratios.&n; */
r_extern
id|u8
id|numa_slit
(braket
id|NR_NODES
op_star
id|NR_NODES
)braket
suffix:semicolon
DECL|macro|node_distance
mdefine_line|#define node_distance(from,to) (numa_slit[from * numnodes + to])
r_extern
r_int
id|paddr_to_nid
c_func
(paren
r_int
r_int
id|paddr
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_IA64_NUMA_H */
eof
