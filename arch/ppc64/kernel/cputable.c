multiline_comment|/*&n; *  arch/ppc64/kernel/cputable.c&n; *&n; *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  Modifications for ppc64:&n; *      Copyright (C) 2003 Dave Engebretsen &lt;engebret@us.ibm.com&gt;&n; * &n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
op_assign
l_int|NULL
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
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
r_extern
r_void
id|__setup_cpu_power4
c_func
(paren
r_int
r_int
id|offset
comma
r_struct
id|cpu_spec
op_star
id|spec
)paren
suffix:semicolon
multiline_comment|/* We only set the altivec features if the kernel was compiled with altivec&n; * support&n; */
macro_line|#ifdef CONFIG_ALTIVEC
DECL|macro|CPU_FTR_ALTIVEC_COMP
mdefine_line|#define CPU_FTR_ALTIVEC_COMP&t;CPU_FTR_ALTIVEC
DECL|macro|PPC_FEATURE_HAS_ALTIVEC_COMP
mdefine_line|#define PPC_FEATURE_HAS_ALTIVEC_COMP PPC_FEATURE_HAS_ALTIVEC
macro_line|#else
DECL|macro|CPU_FTR_ALTIVEC_COMP
mdefine_line|#define CPU_FTR_ALTIVEC_COMP&t;0
DECL|macro|PPC_FEATURE_HAS_ALTIVEC_COMP
mdefine_line|#define PPC_FEATURE_HAS_ALTIVEC_COMP    0
macro_line|#endif
DECL|variable|cpu_specs
r_struct
id|cpu_spec
id|cpu_specs
(braket
)braket
op_assign
(brace
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
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
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
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* Northstar */
l_int|0xffff0000
comma
l_int|0x00330000
comma
l_string|&quot;Northstar&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* Pulsar */
l_int|0xffff0000
comma
l_int|0x00340000
comma
l_string|&quot;Pulsar&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
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
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
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
op_or
id|CPU_FTR_DABR
op_or
id|CPU_FTR_IABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power3
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* Power4 */
l_int|0xffff0000
comma
l_int|0x00350000
comma
l_string|&quot;Power4&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_PPCAS_ARCH_V2
op_or
id|CPU_FTR_DABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power4
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* Power4+ */
l_int|0xffff0000
comma
l_int|0x00380000
comma
l_string|&quot;Power4+&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_PPCAS_ARCH_V2
op_or
id|CPU_FTR_DABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power4
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* PPC970 */
l_int|0xffff0000
comma
l_int|0x00390000
comma
l_string|&quot;PPC970&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_PPCAS_ARCH_V2
op_or
id|CPU_FTR_ALTIVEC_COMP
comma
id|COMMON_USER_PPC64
op_or
id|PPC_FEATURE_HAS_ALTIVEC_COMP
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power4
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* Power5 */
l_int|0xffff0000
comma
l_int|0x003a0000
comma
l_string|&quot;Power5&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_PPCAS_ARCH_V2
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power4
comma
id|COMMON_PPC64_FW
)brace
comma
(brace
multiline_comment|/* default match */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_string|&quot;(Power4-Compatible)&quot;
comma
id|CPU_FTR_SPLIT_ID_CACHE
op_or
id|CPU_FTR_USE_TB
op_or
id|CPU_FTR_HPTE_TABLE
op_or
id|CPU_FTR_PPCAS_ARCH_V2
op_or
id|CPU_FTR_DABR
comma
id|COMMON_USER_PPC64
comma
l_int|128
comma
l_int|128
comma
id|__setup_cpu_power4
comma
id|COMMON_PPC64_FW
)brace
)brace
suffix:semicolon
DECL|variable|firmware_features_table
id|firmware_feature_t
id|firmware_features_table
(braket
id|FIRMWARE_MAX_FEATURES
)braket
op_assign
(brace
(brace
id|FW_FEATURE_PFT
comma
l_string|&quot;hcall-pft&quot;
)brace
comma
(brace
id|FW_FEATURE_TCE
comma
l_string|&quot;hcall-tce&quot;
)brace
comma
(brace
id|FW_FEATURE_SPRG0
comma
l_string|&quot;hcall-sprg0&quot;
)brace
comma
(brace
id|FW_FEATURE_DABR
comma
l_string|&quot;hcall-dabr&quot;
)brace
comma
(brace
id|FW_FEATURE_COPY
comma
l_string|&quot;hcall-copy&quot;
)brace
comma
(brace
id|FW_FEATURE_ASR
comma
l_string|&quot;hcall-asr&quot;
)brace
comma
(brace
id|FW_FEATURE_DEBUG
comma
l_string|&quot;hcall-debug&quot;
)brace
comma
(brace
id|FW_FEATURE_PERF
comma
l_string|&quot;hcall-perf&quot;
)brace
comma
(brace
id|FW_FEATURE_DUMP
comma
l_string|&quot;hcall-dump&quot;
)brace
comma
(brace
id|FW_FEATURE_INTERRUPT
comma
l_string|&quot;hcall-interrupt&quot;
)brace
comma
(brace
id|FW_FEATURE_MIGRATE
comma
l_string|&quot;hcall-migrate&quot;
)brace
comma
(brace
id|FW_FEATURE_PERFMON
comma
l_string|&quot;hcall-perfmon&quot;
)brace
comma
(brace
id|FW_FEATURE_CRQ
comma
l_string|&quot;hcall-crq&quot;
)brace
comma
(brace
id|FW_FEATURE_VIO
comma
l_string|&quot;hcall-vio&quot;
)brace
comma
(brace
id|FW_FEATURE_RDMA
comma
l_string|&quot;hcall-rdma&quot;
)brace
comma
(brace
id|FW_FEATURE_LLAN
comma
l_string|&quot;hcall-lLAN&quot;
)brace
comma
(brace
id|FW_FEATURE_BULK
comma
l_string|&quot;hcall-bulk&quot;
)brace
comma
(brace
id|FW_FEATURE_XDABR
comma
l_string|&quot;hcall-xdabr&quot;
)brace
comma
(brace
id|FW_FEATURE_MULTITCE
comma
l_string|&quot;hcall-multi-tce&quot;
)brace
comma
(brace
id|FW_FEATURE_SPLPAR
comma
l_string|&quot;hcall-splpar&quot;
)brace
comma
)brace
suffix:semicolon
eof
