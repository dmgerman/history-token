multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SN_ARCH_H
DECL|macro|_ASM_SN_ARCH_H
mdefine_line|#define _ASM_SN_ARCH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#ifdef CONFIG_SGI_IP27
macro_line|#include &lt;asm/sn/sn0/arch.h&gt;
macro_line|#endif
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
DECL|macro|cputonasid
mdefine_line|#define cputonasid(cpu)&t;&t;&t;(cpu_data[(cpu)].p_nasid)
DECL|macro|cputoslice
mdefine_line|#define cputoslice(cpu)&t;&t;&t;(cpu_data[(cpu)].p_slice)
DECL|macro|makespnum
mdefine_line|#define makespnum(_nasid, _slice)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((_nasid) &lt;&lt; CPUS_PER_NODE_SHFT) | (_slice))
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
id|cpuid_t
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
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nnode)&t;(nasid_to_compact_node[nnode])
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)&t;(compact_to_nasid_node[cnode])
DECL|macro|CPUID_TO_COMPACT_NODEID
mdefine_line|#define CPUID_TO_COMPACT_NODEID(cpu)&t;(cpuid_to_compact_node[(cpu)])
macro_line|#endif /* _ASM_SN_ARCH_H */
eof
