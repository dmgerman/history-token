multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 Waldorf GMBH&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle&n; * Copyright (C) 1996 Paul M. Antoine&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_CPU_INFO_H
DECL|macro|__ASM_CPU_INFO_H
mdefine_line|#define __ASM_CPU_INFO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#ifdef CONFIG_SGI_IP27
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Descriptor for a cache&n; */
DECL|struct|cache_desc
r_struct
id|cache_desc
(brace
DECL|member|linesz
r_int
r_int
id|linesz
suffix:semicolon
multiline_comment|/* Size of line in bytes */
DECL|member|ways
r_int
r_int
id|ways
suffix:semicolon
multiline_comment|/* Number of ways */
DECL|member|sets
r_int
r_int
id|sets
suffix:semicolon
multiline_comment|/* Number of lines per set */
DECL|member|waysize
r_int
r_int
id|waysize
suffix:semicolon
multiline_comment|/* Bytes per way */
DECL|member|waybit
r_int
r_int
id|waybit
suffix:semicolon
multiline_comment|/* Bits to select in a cache set */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags describing cache properties */
)brace
suffix:semicolon
multiline_comment|/*&n; * Flag definitions&n; */
DECL|macro|MIPS_CACHE_NOT_PRESENT
mdefine_line|#define MIPS_CACHE_NOT_PRESENT&t;0x00000001
DECL|macro|MIPS_CACHE_VTAG
mdefine_line|#define MIPS_CACHE_VTAG&t;&t;0x00000002&t;/* Virtually tagged cache */
DECL|macro|MIPS_CACHE_ALIASES
mdefine_line|#define MIPS_CACHE_ALIASES&t;0x00000004&t;/* Cache could have aliases */
DECL|macro|MIPS_CACHE_IC_F_DC
mdefine_line|#define MIPS_CACHE_IC_F_DC&t;0x00000008&t;/* Ic can refill from D-cache */
DECL|struct|cpuinfo_mips
r_struct
id|cpuinfo_mips
(brace
DECL|member|udelay_val
r_int
r_int
id|udelay_val
suffix:semicolon
DECL|member|asid_cache
r_int
r_int
id|asid_cache
suffix:semicolon
macro_line|#if defined(CONFIG_SGI_IP27)
singleline_comment|//&t;cpuid_t&t;&t;p_cpuid;&t;/* PROM assigned cpuid */
DECL|member|p_nodeid
id|cnodeid_t
id|p_nodeid
suffix:semicolon
multiline_comment|/* my node ID in compact-id-space */
DECL|member|p_nasid
id|nasid_t
id|p_nasid
suffix:semicolon
multiline_comment|/* my node ID in numa-as-id-space */
DECL|member|p_slice
r_int
r_char
id|p_slice
suffix:semicolon
multiline_comment|/* Physical position on node board */
macro_line|#endif
macro_line|#if 0
r_int
r_int
id|loops_per_sec
suffix:semicolon
r_int
r_int
id|ipi_count
suffix:semicolon
r_int
r_int
id|irq_attempt
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_int
r_int
id|smp_local_irq_count
suffix:semicolon
r_int
r_int
id|prof_multiplier
suffix:semicolon
r_int
r_int
id|prof_counter
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Capability and feature descriptor structure for MIPS CPU&n;&t; */
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
DECL|member|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
DECL|member|fpu_id
r_int
r_int
id|fpu_id
suffix:semicolon
DECL|member|cputype
r_int
r_int
id|cputype
suffix:semicolon
DECL|member|isa_level
r_int
id|isa_level
suffix:semicolon
DECL|member|tlbsize
r_int
id|tlbsize
suffix:semicolon
DECL|member|icache
r_struct
id|cache_desc
id|icache
suffix:semicolon
multiline_comment|/* Primary I-cache */
DECL|member|dcache
r_struct
id|cache_desc
id|dcache
suffix:semicolon
multiline_comment|/* Primary D or combined I/D cache */
DECL|member|scache
r_struct
id|cache_desc
id|scache
suffix:semicolon
multiline_comment|/* Secondary cache */
DECL|member|tcache
r_struct
id|cache_desc
id|tcache
suffix:semicolon
multiline_comment|/* Tertiary/split secondary cache */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* Additional data */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
r_extern
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_report
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_CPU_INFO_H */
eof
