multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995-1997,1999,2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_IA64_SN_ARCH_H
DECL|macro|_ASM_IA64_SN_ARCH_H
mdefine_line|#define _ASM_IA64_SN_ARCH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#if defined(CONFIG_IA64_SGI_SN1) 
macro_line|#include &lt;asm/sn/sn1/arch.h&gt;
macro_line|#elif defined(CONFIG_IA64_SGI_SN2)
macro_line|#include &lt;asm/sn/sn2/arch.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_IA64_SGI_SN1) 
DECL|typedef|bdrkreg_t
r_typedef
id|u64
id|bdrkreg_t
suffix:semicolon
macro_line|#elif defined(CONFIG_IA64_SGI_SN2)
DECL|typedef|shubreg_t
r_typedef
id|u64
id|shubreg_t
suffix:semicolon
macro_line|#endif
DECL|typedef|hubreg_t
r_typedef
id|u64
id|hubreg_t
suffix:semicolon
DECL|typedef|mmr_t
r_typedef
id|u64
id|mmr_t
suffix:semicolon
DECL|typedef|nic_t
r_typedef
id|u64
id|nic_t
suffix:semicolon
DECL|macro|CNODE_TO_CPU_BASE
mdefine_line|#define CNODE_TO_CPU_BASE(_cnode)&t;(NODEPDA(_cnode)-&gt;node_first_cpu)
DECL|macro|NASID_TO_COMPACT_NODEID
mdefine_line|#define NASID_TO_COMPACT_NODEID(nasid)  (nasid_to_cnodeid(nasid))
DECL|macro|COMPACT_TO_NASID_NODEID
mdefine_line|#define COMPACT_TO_NASID_NODEID(cnode)  (cnodeid_to_nasid(cnode))
DECL|macro|INVALID_NASID
mdefine_line|#define INVALID_NASID&t;&t;((nasid_t)-1)
DECL|macro|INVALID_CNODEID
mdefine_line|#define INVALID_CNODEID&t;&t;((cnodeid_t)-1)
DECL|macro|INVALID_PNODEID
mdefine_line|#define INVALID_PNODEID&t;&t;((pnodeid_t)-1)
DECL|macro|INVALID_MODULE
mdefine_line|#define INVALID_MODULE&t;&t;((moduleid_t)-1)
DECL|macro|INVALID_PARTID
mdefine_line|#define&t;INVALID_PARTID&t;&t;((partid_t)-1)
r_extern
id|cpuid_t
id|cnodetocpu
c_func
(paren
id|cnodeid_t
)paren
suffix:semicolon
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
r_extern
r_int
id|is_fine_dirmode
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_ARCH_H */
eof
