multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H
DECL|macro|__ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H
mdefine_line|#define __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H
multiline_comment|/*&n; * IP22 with a variety of processors so we can&squot;t use defaults for everything.&n; */
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;0
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;0
DECL|macro|cpu_has_cache_cdex_p
mdefine_line|#define cpu_has_cache_cdex_p&t;1
DECL|macro|cpu_has_prefetch
mdefine_line|#define cpu_has_prefetch&t;0
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;0
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;0
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;1
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;0&t;&t;/* Needs to change for R8000 */
DECL|macro|cpu_has_dc_aliases
mdefine_line|#define cpu_has_dc_aliases&t;(PAGE_SIZE &lt; 0x4000)
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;0
DECL|macro|cpu_has_nofpuex
mdefine_line|#define cpu_has_nofpuex&t;&t;0
DECL|macro|cpu_has_64bits
mdefine_line|#define cpu_has_64bits&t;&t;1
macro_line|#endif /* __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H */
eof
