multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_YOSEMITE_CPU_FEATURE_OVERRIDES_H
DECL|macro|__ASM_MACH_YOSEMITE_CPU_FEATURE_OVERRIDES_H
mdefine_line|#define __ASM_MACH_YOSEMITE_CPU_FEATURE_OVERRIDES_H
multiline_comment|/*&n; * Momentum Jaguar ATX always has the RM9000 processor.&n; */
DECL|macro|cpu_has_watch
mdefine_line|#define cpu_has_watch&t;&t;1
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;0
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;0
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;0
DECL|macro|cpu_has_cache_cdex_p
mdefine_line|#define cpu_has_cache_cdex_p&t;0
DECL|macro|cpu_has_cache_cdex_s
mdefine_line|#define cpu_has_cache_cdex_s&t;0
DECL|macro|cpu_has_prefetch
mdefine_line|#define cpu_has_prefetch&t;1
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;0
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;0
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;0
DECL|macro|cpu_has_dc_aliases
mdefine_line|#define cpu_has_dc_aliases&t;0
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;0
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;0
DECL|macro|cpu_has_64bits
mdefine_line|#define cpu_has_64bits&t;&t;1
DECL|macro|cpu_has_subset_pcaches
mdefine_line|#define cpu_has_subset_pcaches&t;0
DECL|macro|cpu_dcache_line_size
mdefine_line|#define cpu_dcache_line_size()&t;32
DECL|macro|cpu_icache_line_size
mdefine_line|#define cpu_icache_line_size()&t;32
DECL|macro|cpu_scache_line_size
mdefine_line|#define cpu_scache_line_size()&t;32
multiline_comment|/*&n; * On the RM9000 we need to ensure that I-cache lines being fetches only&n; * contain valid instructions are funny things will happen.&n; */
DECL|macro|PLAT_TRAMPOLINE_STUFF_LINE
mdefine_line|#define PLAT_TRAMPOLINE_STUFF_LINE&t;32UL
macro_line|#endif /* __ASM_MACH_YOSEMITE_CPU_FEATURE_OVERRIDES_H */
eof
