multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Ralf Baechle&n; *&n; * SNI RM200 C apparently was only shipped with R4600 V2.0 and R5000 processors.&n; */
macro_line|#ifndef __ASM_MACH_RM200_CPU_FEATURE_OVERRIDES_H
DECL|macro|__ASM_MACH_RM200_CPU_FEATURE_OVERRIDES_H
mdefine_line|#define __ASM_MACH_RM200_CPU_FEATURE_OVERRIDES_H
macro_line|#include &lt;cpu-feature-overrides.h&gt;
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;1
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;1
DECL|macro|cpu_has_4ktlb
mdefine_line|#define cpu_has_4ktlb&t;&t;1
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;&t;1
DECL|macro|cpu_has_32fpr
mdefine_line|#define cpu_has_32fpr&t;&t;1
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;1
DECL|macro|cpu_has_watch
mdefine_line|#define cpu_has_watch&t;&t;0
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;0
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;0
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;0
DECL|macro|cpu_has_cache_cdex_p
mdefine_line|#define cpu_has_cache_cdex_p&t;1
DECL|macro|cpu_has_cache_cdex_s
mdefine_line|#define cpu_has_cache_cdex_s&t;0
DECL|macro|cpu_has_prefetch
mdefine_line|#define cpu_has_prefetch&t;0
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;0
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;0
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;0
DECL|macro|cpu_has_dc_aliases
mdefine_line|#define cpu_has_dc_aliases&t;(PAGE_SIZE &lt; 0x4000)
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;0
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;0
DECL|macro|cpu_has_64bits
mdefine_line|#define cpu_has_64bits&t;&t;1
DECL|macro|cpu_has_subset_pcaches
mdefine_line|#define cpu_has_subset_pcaches&t;0&t;/* No S-cache on R5000 I think ...  */
DECL|macro|cpu_dcache_line_size
mdefine_line|#define cpu_dcache_line_size()&t;32
DECL|macro|cpu_icache_line_size
mdefine_line|#define cpu_icache_line_size()&t;32
DECL|macro|cpu_scache_line_size
mdefine_line|#define cpu_scache_line_size()&t;0&t;/* No S-cache on R5000 I think ...  */
macro_line|#endif /* __ASM_MACH_RM200_CPU_FEATURE_OVERRIDES_H */
eof
