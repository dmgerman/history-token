multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Chris Dearman&n; */
macro_line|#ifndef __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H
DECL|macro|__ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H
mdefine_line|#define __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H
multiline_comment|/*&n; * CPU feature overrides for MIPS boards&n; */
macro_line|#ifdef CONFIG_CPU_MIPS32
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;1
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;1
DECL|macro|cpu_has_4ktlb
mdefine_line|#define cpu_has_4ktlb&t;&t;1
multiline_comment|/* #define cpu_has_fpu&t;&t;? */
multiline_comment|/* #define cpu_has_32fpr&t;? */
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;1
multiline_comment|/* #define cpu_has_watch&t;? */
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;1
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;0
multiline_comment|/* #define cpu_has_cache_cdex_p&t;? */
multiline_comment|/* #define cpu_has_cache_cdex_s&t;? */
multiline_comment|/* #define cpu_has_prefetch&t;? */
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;1
multiline_comment|/* #define cpu_has_ejtag&t;? */
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
multiline_comment|/* #define cpu_has_vtag_icache&t;? */
multiline_comment|/* #define cpu_has_dc_aliases&t;? */
multiline_comment|/* #define cpu_has_ic_fills_f_dc ? */
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;0
multiline_comment|/* #define cpu_has_64bits&t;? */
multiline_comment|/* #define cpu_has_64bit_zero_reg ? */
multiline_comment|/* #define cpu_has_subset_pcaches ? */
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_MIPS64
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;1
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;1
DECL|macro|cpu_has_4ktlb
mdefine_line|#define cpu_has_4ktlb&t;&t;1
multiline_comment|/* #define cpu_has_fpu&t;&t;? */
multiline_comment|/* #define cpu_has_32fpr&t;? */
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;1
multiline_comment|/* #define cpu_has_watch&t;? */
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;1
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;0
multiline_comment|/* #define cpu_has_cache_cdex_p&t;? */
multiline_comment|/* #define cpu_has_cache_cdex_s&t;? */
multiline_comment|/* #define cpu_has_prefetch&t;? */
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;1
multiline_comment|/* #define cpu_has_ejtag&t;? */
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
multiline_comment|/* #define cpu_has_vtag_icache&t;? */
multiline_comment|/* #define cpu_has_dc_aliases&t;? */
multiline_comment|/* #define cpu_has_ic_fills_f_dc ? */
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;0
multiline_comment|/* #define cpu_has_64bits&t;? */
multiline_comment|/* #define cpu_has_64bit_zero_reg ? */
multiline_comment|/* #define cpu_has_subset_pcaches ? */
macro_line|#endif
macro_line|#endif /* __ASM_MACH_MIPS_CPU_FEATURE_OVERRIDES_H */
eof
