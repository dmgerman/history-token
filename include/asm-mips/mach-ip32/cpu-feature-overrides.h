multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2005 Ilya A. Volynets-Evenbakh&n; * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; */
macro_line|#ifndef __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H
DECL|macro|__ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H
mdefine_line|#define __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * R5000 has an interesting &quot;restriction&quot;:  ll(d)/sc(d)&n; * instructions to XKPHYS region simply do uncached bus&n; * requests. This breaks all the atomic bitops functions.&n; * so, for 64bit IP32 kernel we just don&squot;t use ll/sc.&n; * This does not affect luserland.&n; */
macro_line|#if defined(CONFIG_CPU_R5000) &amp;&amp; defined(CONFIG_MIPS64)
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;0
macro_line|#else
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
macro_line|#endif
multiline_comment|/* Settings which are common for all ip32 CPUs */
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;1
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;1
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;&t;1
DECL|macro|cpu_has_32fpr
mdefine_line|#define cpu_has_32fpr&t;&t;1
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;1
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;0
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;0
DECL|macro|cpu_has_cache_cdex_s
mdefine_line|#define cpu_has_cache_cdex_s&t;0
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;0
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;0
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;0
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;0
macro_line|#endif /* __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H */
eof
