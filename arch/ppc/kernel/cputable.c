multiline_comment|/*&n; *  arch/ppc/kernel/cputable.c&n; *&n; *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
DECL|variable|cur_cpu_spec
r_struct
id|cpu_spec
op_star
id|cur_cpu_spec
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|__setup_cpu_601
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_603
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_604
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_750
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_750cx
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_750fx
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_7400
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_7410
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_745x
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_power3
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_8xx
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_generic
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|cpu_nr
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
DECL|macro|CLASSIC_PPC
mdefine_line|#define CLASSIC_PPC (!defined(CONFIG_8xx) &amp;&amp; !defined(CONFIG_4xx) &amp;&amp; &bslash;&n;&t;&t;     !defined(CONFIG_POWER3))
multiline_comment|/* This table only contains &quot;desktop&quot; CPUs, it need to be filled with embedded&n; * ones as well...&n; */
DECL|macro|COMMON_PPC
mdefine_line|#define COMMON_PPC&t;(PPC_FEATURE_32 | PPC_FEATURE_HAS_FPU | &bslash;&n;&t;&t;&t; PPC_FEATURE_HAS_MMU)
multiline_comment|/* We only set the altivec features if the kernel was compiled with altivec&n; * support&n; */
macro_line|#ifdef CONFIG_ALTIVEC
DECL|macro|CPU_FTR_ALTIVEC_COMP
mdefine_line|#define CPU_FTR_ALTIVEC_COMP&t;CPU_FTR_ALTIVEC
macro_line|#else
DECL|macro|CPU_FTR_ALTIVEC_COMP
mdefine_line|#define CPU_FTR_ALTIVEC_COMP&t;0
macro_line|#endif
DECL|variable|cpu_specs
r_struct
id|cpu_spec
id|cpu_specs
(braket
)braket
op_assign
(brace
macro_line|#if CLASSIC_PPC
(brace
multiline_comment|/* 601 */
l_int|0xffff0000
comma
l_int|0x00010000
comma
l_string|&quot;601&quot;
comma
id|CPU_FTR_601
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_601_INSTR
op_or
id|PPC_FEATURE_UNIFIED_CACHE
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_601
)brace
comma
(brace
multiline_comment|/* 603 */
l_int|0xffff0000
comma
l_int|0x00030000
comma
l_string|&quot;603&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_603
)brace
comma
(brace
multiline_comment|/* 603e */
l_int|0xffff0000
comma
l_int|0x00060000
comma
l_string|&quot;603e&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_603
)brace
comma
(brace
multiline_comment|/* 603ev */
l_int|0xffff0000
comma
l_int|0x00070000
comma
l_string|&quot;603ev&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_603
)brace
comma
(brace
multiline_comment|/* 604 */
l_int|0xffff0000
comma
l_int|0x00040000
comma
l_string|&quot;604&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_604_PERF_MON
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_604
)brace
comma
(brace
multiline_comment|/* 604e */
l_int|0xfffff000
comma
l_int|0x00090000
comma
l_string|&quot;604e&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_604_PERF_MON
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_604
)brace
comma
(brace
multiline_comment|/* 604r */
l_int|0xffff0000
comma
l_int|0x00090000
comma
l_string|&quot;604r&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_604_PERF_MON
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_604
)brace
comma
(brace
multiline_comment|/* 604ev */
l_int|0xffff0000
comma
l_int|0x000a0000
comma
l_string|&quot;604ev&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_604_PERF_MON
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_604
)brace
comma
(brace
multiline_comment|/* 740/750 (0x4202, don&squot;t support TAU ?) */
l_int|0xffffffff
comma
l_int|0x00084202
comma
l_string|&quot;740/750&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750
)brace
comma
(brace
multiline_comment|/* 745/755 */
l_int|0xfffff000
comma
l_int|0x00083000
comma
l_string|&quot;745/755&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750
)brace
comma
(brace
multiline_comment|/* 750CX (80100 and 8010x?) */
l_int|0xfffffff0
comma
l_int|0x00080100
comma
l_string|&quot;750CX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750cx
)brace
comma
(brace
multiline_comment|/* 750CX (82201 and 82202) */
l_int|0xfffffff0
comma
l_int|0x00082200
comma
l_string|&quot;750CX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750cx
)brace
comma
(brace
multiline_comment|/* 750CXe (82214) */
l_int|0xfffffff0
comma
l_int|0x00082210
comma
l_string|&quot;750CXe&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750cx
)brace
comma
(brace
multiline_comment|/* 750FX rev 1.x */
l_int|0xffffff00
comma
l_int|0x70000100
comma
l_string|&quot;750FX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_DUAL_PLL_750FX
op_or
id|CPU_FTR_NO_DPM
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750
)brace
comma
(brace
multiline_comment|/* 750FX rev 2.0 must disable HID0[DPM] */
l_int|0xffffffff
comma
l_int|0x70000200
comma
l_string|&quot;750FX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_NO_DPM
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750
)brace
comma
(brace
multiline_comment|/* 750FX (All revs except 2.0) */
l_int|0xffff0000
comma
l_int|0x70000000
comma
l_string|&quot;750FX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_DUAL_PLL_750FX
op_or
id|CPU_FTR_HAS_HIGH_BATS
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750fx
)brace
comma
(brace
multiline_comment|/* 740/750 (L2CR bit need fixup for 740) */
l_int|0xffff0000
comma
l_int|0x00080000
comma
l_string|&quot;740/750&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_750
)brace
comma
(brace
multiline_comment|/* 7400 rev 1.1 ? (no TAU) */
l_int|0xffffffff
comma
l_int|0x000c1101
comma
l_string|&quot;7400 (1.1)&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_7400
)brace
comma
(brace
multiline_comment|/* 7400 */
l_int|0xffff0000
comma
l_int|0x000c0000
comma
l_string|&quot;7400&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_7400
)brace
comma
(brace
multiline_comment|/* 7410 */
l_int|0xffff0000
comma
l_int|0x800c0000
comma
l_string|&quot;7410&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_TAU
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_CAN_NAP
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_7410
)brace
comma
(brace
multiline_comment|/* 7450 2.0 - no doze/nap */
l_int|0xffffffff
comma
l_int|0x80000200
comma
l_string|&quot;7450&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7450 2.1 */
l_int|0xffffffff
comma
l_int|0x80000201
comma
l_string|&quot;7450&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_NAP_DISABLE_L2_PR
op_or
id|CPU_FTR_L3_DISABLE_NAP
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7450 2.3 and newer */
l_int|0xffff0000
comma
l_int|0x80000000
comma
l_string|&quot;7450&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_NAP_DISABLE_L2_PR
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7455 rev 1.x */
l_int|0xffffff00
comma
l_int|0x80010100
comma
l_string|&quot;7455&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_HAS_HIGH_BATS
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7455 rev 2.0 */
l_int|0xffffffff
comma
l_int|0x80010200
comma
l_string|&quot;7455&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_NAP_DISABLE_L2_PR
op_or
id|CPU_FTR_L3_DISABLE_NAP
op_or
id|CPU_FTR_HAS_HIGH_BATS
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7455 others */
l_int|0xffff0000
comma
l_int|0x80010000
comma
l_string|&quot;7455&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_NAP_DISABLE_L2_PR
op_or
id|CPU_FTR_HAS_HIGH_BATS
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 7457 */
l_int|0xffff0000
comma
l_int|0x80020000
comma
l_string|&quot;7457&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_CAN_NAP
op_or
id|CPU_FTR_L2CR
op_or
id|CPU_FTR_ALTIVEC_COMP
op_or
id|CPU_FTR_L3CR
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_SPEC7450
op_or
id|CPU_FTR_NAP_DISABLE_L2_PR
op_or
id|CPU_FTR_HAS_HIGH_BATS
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_HAS_ALTIVEC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_745x
)brace
comma
(brace
multiline_comment|/* 82xx (8240, 8245, 8260 are all 603e cores) */
l_int|0x7fff0000
comma
l_int|0x00810000
comma
l_string|&quot;82xx&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_CAN_DOZE
op_or
id|CPU_FTR_USE_TB
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_603
)brace
comma
(brace
multiline_comment|/* default match, we assume split I/D cache &amp; TB (non-601)... */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_string|&quot;(generic PPC)&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
comma
l_int|32
comma
l_int|32
comma
id|__setup_cpu_generic
)brace
comma
macro_line|#endif /* CLASSIC_PPC */    
macro_line|#ifdef CONFIG_PPC64BRIDGE
(brace
multiline_comment|/* Power3 */
l_int|0xffff0000
comma
l_int|0x00400000
comma
l_string|&quot;Power3 (630)&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
)brace
comma
(brace
multiline_comment|/* Power3+ */
l_int|0xffff0000
comma
l_int|0x00410000
comma
l_string|&quot;Power3 (630+)&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
)brace
comma
(brace
multiline_comment|/* I-star */
l_int|0xffff0000
comma
l_int|0x00360000
comma
l_string|&quot;I-star&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
)brace
comma
(brace
multiline_comment|/* S-star */
l_int|0xffff0000
comma
l_int|0x00370000
comma
l_string|&quot;S-star&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
comma
id|COMMON_PPC
op_or
id|PPC_FEATURE_64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
)brace
comma
macro_line|#endif /* CONFIG_PPC64BRIDGE */    
macro_line|#ifdef CONFIG_8xx
(brace
multiline_comment|/* 8xx */
l_int|0xffff0000
comma
l_int|0x00500000
comma
l_string|&quot;8xx&quot;
comma
multiline_comment|/* CPU_FTR_CAN_DOZE is possible, if the 8xx code is there.... */
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|16
comma
l_int|16
comma
id|__setup_cpu_8xx
multiline_comment|/* Empty */
)brace
comma
macro_line|#endif /* CONFIG_8xx */
macro_line|#ifdef CONFIG_40x
(brace
multiline_comment|/* 403GC */
l_int|0xffffff00
comma
l_int|0x00200200
comma
l_string|&quot;403GC&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|16
comma
l_int|16
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_403 */
)brace
comma
(brace
multiline_comment|/* 403GCX */
l_int|0xffffff00
comma
l_int|0x00201400
comma
l_string|&quot;403GCX&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|16
comma
l_int|16
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_403 */
)brace
comma
(brace
multiline_comment|/* 403G ?? */
l_int|0xffff0000
comma
l_int|0x00200000
comma
l_string|&quot;403G ??&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|16
comma
l_int|16
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_403 */
)brace
comma
(brace
multiline_comment|/* 405GP */
l_int|0xffff0000
comma
l_int|0x40110000
comma
l_string|&quot;405GP&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* STB 03xxx */
l_int|0xffff0000
comma
l_int|0x40130000
comma
l_string|&quot;STB03xxx&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* STB 04xxx */
l_int|0xffff0000
comma
l_int|0x41810000
comma
l_string|&quot;STB04xxx&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* NP405L */
l_int|0xffff0000
comma
l_int|0x41610000
comma
l_string|&quot;NP405L&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* NP4GS3 */
l_int|0xffff0000
comma
l_int|0x40B10000
comma
l_string|&quot;NP4GS3&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* NP405H */
l_int|0xffff0000
comma
l_int|0x41410000
comma
l_string|&quot;NP405H&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* 405GPr */
l_int|0xffff0000
comma
l_int|0x50910000
comma
l_string|&quot;405GPr&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* STBx25xx */
l_int|0xffff0000
comma
l_int|0x51510000
comma
l_string|&quot;STBx25xx&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* 405LP */
l_int|0xffff0000
comma
l_int|0x41F10000
comma
l_string|&quot;405LP&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
(brace
multiline_comment|/* Xilinx Virtex-II Pro  */
l_int|0xffff0000
comma
l_int|0x20010000
comma
l_string|&quot;Virtex-II Pro&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
op_or
id|PPC_FEATURE_HAS_4xxMAC
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_405 */
)brace
comma
macro_line|#endif /* CONFIG_40x */
macro_line|#ifdef CONFIG_440
(brace
multiline_comment|/* 440GP Rev. B */
l_int|0xf0000fff
comma
l_int|0x40000440
comma
l_string|&quot;440GP Rev. B&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_440 */
)brace
comma
(brace
multiline_comment|/* 440GP Rev. C */
l_int|0xf0000fff
comma
l_int|0x40000481
comma
l_string|&quot;440GP Rev. C&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
comma
id|PPC_FEATURE_32
op_or
id|PPC_FEATURE_HAS_MMU
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
multiline_comment|/*__setup_cpu_440 */
)brace
comma
macro_line|#endif /* CONFIG_440 */
macro_line|#if !CLASSIC_PPC
(brace
multiline_comment|/* default match */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_string|&quot;(generic PPC)&quot;
comma
l_int|0
comma
id|PPC_FEATURE_32
comma
l_int|32
comma
l_int|32
comma
l_int|0
comma
)brace
macro_line|#endif /* !CLASSIC_PPC */
)brace
suffix:semicolon
eof
