multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI specific setup.&n; *&n; * Copyright (C) 1995-1997,1999,2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_IA64_SN_ARCH_H
DECL|macro|_ASM_IA64_SN_ARCH_H
mdefine_line|#define _ASM_IA64_SN_ARCH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/percpu.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/*&n; * The following defines attributes of the HUB chip. These attributes are&n; * frequently referenced. They are kept in the per-cpu data areas of each cpu.&n; * They are kept together in a struct to minimize cache misses.&n; */
DECL|struct|sn_hub_info_s
r_struct
id|sn_hub_info_s
(brace
DECL|member|shub2
id|u8
id|shub2
suffix:semicolon
DECL|member|nasid_shift
id|u8
id|nasid_shift
suffix:semicolon
DECL|member|as_shift
id|u8
id|as_shift
suffix:semicolon
DECL|member|shub_1_1_found
id|u8
id|shub_1_1_found
suffix:semicolon
DECL|member|nasid_bitmask
id|u16
id|nasid_bitmask
suffix:semicolon
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|sn_hub_info_s
comma
id|__sn_hub_info
)paren
suffix:semicolon
DECL|macro|sn_hub_info
mdefine_line|#define sn_hub_info &t;(&amp;__get_cpu_var(__sn_hub_info))
DECL|macro|is_shub2
mdefine_line|#define is_shub2()&t;(sn_hub_info-&gt;shub2)
DECL|macro|is_shub1
mdefine_line|#define is_shub1()&t;(sn_hub_info-&gt;shub2 == 0)
multiline_comment|/*&n; * Use this macro to test if shub 1.1 wars should be enabled&n; */
DECL|macro|enable_shub_wars_1_1
mdefine_line|#define enable_shub_wars_1_1()&t;(sn_hub_info-&gt;shub_1_1_found)
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
