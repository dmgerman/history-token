multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995-1997,1999,2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_IA64_SN_ARCH_H
DECL|macro|_ASM_IA64_SN_ARCH_H
mdefine_line|#define _ASM_IA64_SN_ARCH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/*&n; * This is the maximum number of nodes that can be part of a kernel.&n; * Effectively, it&squot;s the maximum number of compact node ids (cnodeid_t).&n; * This is not necessarily the same as MAX_NASIDS.&n; */
DECL|macro|MAX_COMPACT_NODES
mdefine_line|#define MAX_COMPACT_NODES&t;2048
DECL|macro|CPUS_PER_NODE
mdefine_line|#define CPUS_PER_NODE&t;&t;4
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
