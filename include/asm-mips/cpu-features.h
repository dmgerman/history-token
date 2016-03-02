multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Ralf Baechle&n; */
macro_line|#ifndef __ASM_CPU_FEATURES_H
DECL|macro|__ASM_CPU_FEATURES_H
mdefine_line|#define __ASM_CPU_FEATURES_H
macro_line|#include &lt;cpu-feature-overrides.h&gt;
multiline_comment|/*&n; * SMP assumption: Options of CPU 0 are a superset of all processors.&n; * This is true for all known MIPS systems.&n; */
macro_line|#ifndef cpu_has_tlb
DECL|macro|cpu_has_tlb
mdefine_line|#define cpu_has_tlb&t;&t;(cpu_data[0].options &amp; MIPS_CPU_TLB)
macro_line|#endif
macro_line|#ifndef cpu_has_4kex
DECL|macro|cpu_has_4kex
mdefine_line|#define cpu_has_4kex&t;&t;(cpu_data[0].options &amp; MIPS_CPU_4KEX)
macro_line|#endif
macro_line|#ifndef cpu_has_4ktlb
DECL|macro|cpu_has_4ktlb
mdefine_line|#define cpu_has_4ktlb&t;&t;(cpu_data[0].options &amp; MIPS_CPU_4KTLB)
macro_line|#endif
macro_line|#ifndef cpu_has_fpu
DECL|macro|cpu_has_fpu
mdefine_line|#define cpu_has_fpu&t;&t;(cpu_data[0].options &amp; MIPS_CPU_FPU)
macro_line|#endif
macro_line|#ifndef cpu_has_32fpr
DECL|macro|cpu_has_32fpr
mdefine_line|#define cpu_has_32fpr&t;&t;(cpu_data[0].options &amp; MIPS_CPU_32FPR)
macro_line|#endif
macro_line|#ifndef cpu_has_counter
DECL|macro|cpu_has_counter
mdefine_line|#define cpu_has_counter&t;&t;(cpu_data[0].options &amp; MIPS_CPU_COUNTER)
macro_line|#endif
macro_line|#ifndef cpu_has_watch
DECL|macro|cpu_has_watch
mdefine_line|#define cpu_has_watch&t;&t;(cpu_data[0].options &amp; MIPS_CPU_WATCH)
macro_line|#endif
macro_line|#ifndef cpu_has_mips16
DECL|macro|cpu_has_mips16
mdefine_line|#define cpu_has_mips16&t;&t;(cpu_data[0].options &amp; MIPS_CPU_MIPS16)
macro_line|#endif
macro_line|#ifndef cpu_has_divec
DECL|macro|cpu_has_divec
mdefine_line|#define cpu_has_divec&t;&t;(cpu_data[0].options &amp; MIPS_CPU_DIVEC)
macro_line|#endif
macro_line|#ifndef cpu_has_vce
DECL|macro|cpu_has_vce
mdefine_line|#define cpu_has_vce&t;&t;(cpu_data[0].options &amp; MIPS_CPU_VCE)
macro_line|#endif
macro_line|#ifndef cpu_has_cache_cdex_p
DECL|macro|cpu_has_cache_cdex_p
mdefine_line|#define cpu_has_cache_cdex_p&t;(cpu_data[0].options &amp; MIPS_CPU_CACHE_CDEX_P)
macro_line|#endif
macro_line|#ifndef cpu_has_cache_cdex_s
DECL|macro|cpu_has_cache_cdex_s
mdefine_line|#define cpu_has_cache_cdex_s&t;(cpu_data[0].options &amp; MIPS_CPU_CACHE_CDEX_S)
macro_line|#endif
macro_line|#ifndef cpu_has_prefetch
DECL|macro|cpu_has_prefetch
mdefine_line|#define cpu_has_prefetch&t;(cpu_data[0].options &amp; MIPS_CPU_PREFETCH)
macro_line|#endif
macro_line|#ifndef cpu_has_mcheck
DECL|macro|cpu_has_mcheck
mdefine_line|#define cpu_has_mcheck&t;&t;(cpu_data[0].options &amp; MIPS_CPU_MCHECK)
macro_line|#endif
macro_line|#ifndef cpu_has_ejtag
DECL|macro|cpu_has_ejtag
mdefine_line|#define cpu_has_ejtag&t;&t;(cpu_data[0].options &amp; MIPS_CPU_EJTAG)
macro_line|#endif
macro_line|#ifndef cpu_has_llsc
DECL|macro|cpu_has_llsc
mdefine_line|#define cpu_has_llsc&t;&t;(cpu_data[0].options &amp; MIPS_CPU_LLSC)
macro_line|#endif
macro_line|#ifndef cpu_has_vtag_icache
DECL|macro|cpu_has_vtag_icache
mdefine_line|#define cpu_has_vtag_icache&t;(cpu_data[0].icache.flags &amp; MIPS_CACHE_VTAG)
macro_line|#endif
macro_line|#ifndef cpu_has_dc_aliases
DECL|macro|cpu_has_dc_aliases
mdefine_line|#define cpu_has_dc_aliases&t;(cpu_data[0].dcache.flags &amp; MIPS_CACHE_ALIASES)
macro_line|#endif
macro_line|#ifndef cpu_has_ic_fills_f_dc
DECL|macro|cpu_has_ic_fills_f_dc
mdefine_line|#define cpu_has_ic_fills_f_dc&t;(cpu_data[0].dcache.flags &amp; MIPS_CACHE_IC_F_DC)
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS32
macro_line|# ifndef cpu_has_nofpuex
DECL|macro|cpu_has_nofpuex
macro_line|# define cpu_has_nofpuex&t;(cpu_data[0].options &amp; MIPS_CPU_NOFPUEX)
macro_line|# endif
macro_line|# ifndef cpu_has_64bits
DECL|macro|cpu_has_64bits
macro_line|# define cpu_has_64bits&t;&t;(cpu_data[0].isa_level &amp; MIPS_CPU_ISA_64BIT)
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_zero_reg
DECL|macro|cpu_has_64bit_zero_reg
macro_line|# define cpu_has_64bit_zero_reg&t;(cpu_data[0].isa_level &amp; MIPS_CPU_ISA_64BIT)
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_gp_regs
DECL|macro|cpu_has_64bit_gp_regs
macro_line|# define cpu_has_64bit_gp_regs&t;&t;0
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_addresses
DECL|macro|cpu_has_64bit_addresses
macro_line|# define cpu_has_64bit_addresses&t;0
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
macro_line|# ifndef cpu_has_nofpuex
DECL|macro|cpu_has_nofpuex
macro_line|# define cpu_has_nofpuex&t;&t;0
macro_line|# endif
macro_line|# ifndef cpu_has_64bits
DECL|macro|cpu_has_64bits
macro_line|# define cpu_has_64bits&t;&t;&t;1
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_zero_reg
DECL|macro|cpu_has_64bit_zero_reg
macro_line|# define cpu_has_64bit_zero_reg&t;&t;1
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_gp_regs
DECL|macro|cpu_has_64bit_gp_regs
macro_line|# define cpu_has_64bit_gp_regs&t;&t;1
macro_line|# endif
macro_line|# ifndef cpu_has_64bit_addresses
DECL|macro|cpu_has_64bit_addresses
macro_line|# define cpu_has_64bit_addresses&t;1
macro_line|# endif
macro_line|#endif
macro_line|#ifndef cpu_has_subset_pcaches
DECL|macro|cpu_has_subset_pcaches
mdefine_line|#define cpu_has_subset_pcaches&t;(cpu_data[0].options &amp; MIPS_CPU_SUBSET_CACHES)
macro_line|#endif
macro_line|#ifndef cpu_dcache_line_size
DECL|macro|cpu_dcache_line_size
mdefine_line|#define cpu_dcache_line_size()&t;current_cpu_data.dcache.linesz
macro_line|#endif
macro_line|#ifndef cpu_icache_line_size
DECL|macro|cpu_icache_line_size
mdefine_line|#define cpu_icache_line_size()&t;current_cpu_data.icache.linesz
macro_line|#endif
macro_line|#ifndef cpu_scache_line_size
DECL|macro|cpu_scache_line_size
mdefine_line|#define cpu_scache_line_size()&t;current_cpu_data.scache.linesz
macro_line|#endif
macro_line|#endif /* __ASM_CPU_FEATURES_H */
eof
