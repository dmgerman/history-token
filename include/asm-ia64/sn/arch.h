multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995-1997,1999,2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_IA64_SN_ARCH_H
DECL|macro|_ASM_IA64_SN_ARCH_H
mdefine_line|#define _ASM_IA64_SN_ARCH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/*&n; * This is the maximum number of nodes that can be part of a kernel.&n; * Effectively, it&squot;s the maximum number of compact node ids (cnodeid_t).&n; * This is not necessarily the same as MAX_NASIDS.&n; */
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES       2048
DECL|typedef|nic_t
r_typedef
id|u64
id|nic_t
suffix:semicolon
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nasid)  (nasid_to_cnodeid(nasid))
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)  (cnodeid_to_nasid(cnode))
DECL|macro|INVALID_NASID
mdefine_line|#define INVALID_NASID&t;&t;((nasid_t)-1)
DECL|macro|INVALID_SLAB
mdefine_line|#define INVALID_SLAB            (slabid_t)-1
DECL|macro|INVALID_MODULE
mdefine_line|#define INVALID_MODULE&t;&t;((moduleid_t)-1)
DECL|macro|INVALID_PARTID
mdefine_line|#define&t;INVALID_PARTID&t;&t;((partid_t)-1)
r_extern
r_void
id|sn_flush_all_caches
c_func
(paren
r_int
id|addr
comma
r_int
id|bytes
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_ARCH_H */
eof
