multiline_comment|/*&n; *  include/asm-ppc64/cputable.h&n; *&n; *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  Modifications for ppc64:&n; *      Copyright (C) 2003 Dave Engebretsen &lt;engebret@us.ibm.com&gt;&n; * &n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_PPC_CPUTABLE_H
DECL|macro|__ASM_PPC_CPUTABLE_H
mdefine_line|#define __ASM_PPC_CPUTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt; /* for ASM_CONST */
multiline_comment|/* Exposed to userland CPU features - Must match ppc32 definitions */
DECL|macro|PPC_FEATURE_32
mdefine_line|#define PPC_FEATURE_32&t;&t;&t;0x80000000
DECL|macro|PPC_FEATURE_64
mdefine_line|#define PPC_FEATURE_64&t;&t;&t;0x40000000
DECL|macro|PPC_FEATURE_601_INSTR
mdefine_line|#define PPC_FEATURE_601_INSTR&t;&t;0x20000000
DECL|macro|PPC_FEATURE_HAS_ALTIVEC
mdefine_line|#define PPC_FEATURE_HAS_ALTIVEC&t;&t;0x10000000
DECL|macro|PPC_FEATURE_HAS_FPU
mdefine_line|#define PPC_FEATURE_HAS_FPU&t;&t;0x08000000
DECL|macro|PPC_FEATURE_HAS_MMU
mdefine_line|#define PPC_FEATURE_HAS_MMU&t;&t;0x04000000
DECL|macro|PPC_FEATURE_HAS_4xxMAC
mdefine_line|#define PPC_FEATURE_HAS_4xxMAC&t;&t;0x02000000
DECL|macro|PPC_FEATURE_UNIFIED_CACHE
mdefine_line|#define PPC_FEATURE_UNIFIED_CACHE&t;0x01000000
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This structure can grow, it&squot;s real size is used by head.S code&n; * via the mkdefs mechanism.&n; */
r_struct
id|cpu_spec
suffix:semicolon
DECL|typedef|cpu_setup_t
r_typedef
r_void
(paren
op_star
id|cpu_setup_t
)paren
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
DECL|struct|cpu_spec
r_struct
id|cpu_spec
(brace
multiline_comment|/* CPU is matched via (PVR &amp; pvr_mask) == pvr_value */
DECL|member|pvr_mask
r_int
r_int
id|pvr_mask
suffix:semicolon
DECL|member|pvr_value
r_int
r_int
id|pvr_value
suffix:semicolon
DECL|member|cpu_name
r_char
op_star
id|cpu_name
suffix:semicolon
DECL|member|cpu_features
r_int
r_int
id|cpu_features
suffix:semicolon
multiline_comment|/* Kernel features */
DECL|member|cpu_user_features
r_int
r_int
id|cpu_user_features
suffix:semicolon
multiline_comment|/* Userland features */
multiline_comment|/* cache line sizes */
DECL|member|icache_bsize
r_int
r_int
id|icache_bsize
suffix:semicolon
DECL|member|dcache_bsize
r_int
r_int
id|dcache_bsize
suffix:semicolon
multiline_comment|/* this is called to initialize various CPU bits like L1 cache,&n;&t; * BHT, SPD, etc... from head.S before branching to identify_machine&n;&t; */
DECL|member|cpu_setup
id|cpu_setup_t
id|cpu_setup
suffix:semicolon
multiline_comment|/* This is used to identify firmware features which are available&n;&t; * to the kernel.&n;&t; */
DECL|member|firmware_features
r_int
r_int
id|firmware_features
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpu_spec
id|cpu_specs
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|cpu_spec
op_star
id|cur_cpu_spec
suffix:semicolon
DECL|function|cpu_has_feature
r_static
r_inline
r_int
r_int
id|cpu_has_feature
c_func
(paren
r_int
r_int
id|feature
)paren
(brace
r_return
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|feature
suffix:semicolon
)brace
multiline_comment|/* firmware feature bitmask values */
DECL|macro|FIRMWARE_MAX_FEATURES
mdefine_line|#define FIRMWARE_MAX_FEATURES 63
DECL|macro|FW_FEATURE_PFT
mdefine_line|#define FW_FEATURE_PFT&t;&t;(1UL&lt;&lt;0)
DECL|macro|FW_FEATURE_TCE
mdefine_line|#define FW_FEATURE_TCE&t;&t;(1UL&lt;&lt;1)&t;
DECL|macro|FW_FEATURE_SPRG0
mdefine_line|#define FW_FEATURE_SPRG0&t;(1UL&lt;&lt;2)&t;
DECL|macro|FW_FEATURE_DABR
mdefine_line|#define FW_FEATURE_DABR&t;&t;(1UL&lt;&lt;3)&t;
DECL|macro|FW_FEATURE_COPY
mdefine_line|#define FW_FEATURE_COPY&t;&t;(1UL&lt;&lt;4)&t;
DECL|macro|FW_FEATURE_ASR
mdefine_line|#define FW_FEATURE_ASR&t;&t;(1UL&lt;&lt;5)&t;
DECL|macro|FW_FEATURE_DEBUG
mdefine_line|#define FW_FEATURE_DEBUG&t;(1UL&lt;&lt;6)&t;
DECL|macro|FW_FEATURE_TERM
mdefine_line|#define FW_FEATURE_TERM&t;&t;(1UL&lt;&lt;7)&t;
DECL|macro|FW_FEATURE_PERF
mdefine_line|#define FW_FEATURE_PERF&t;&t;(1UL&lt;&lt;8)&t;
DECL|macro|FW_FEATURE_DUMP
mdefine_line|#define FW_FEATURE_DUMP&t;&t;(1UL&lt;&lt;9)&t;
DECL|macro|FW_FEATURE_INTERRUPT
mdefine_line|#define FW_FEATURE_INTERRUPT&t;(1UL&lt;&lt;10)&t;
DECL|macro|FW_FEATURE_MIGRATE
mdefine_line|#define FW_FEATURE_MIGRATE&t;(1UL&lt;&lt;11)&t;
DECL|macro|FW_FEATURE_PERFMON
mdefine_line|#define FW_FEATURE_PERFMON&t;(1UL&lt;&lt;12)&t;
DECL|macro|FW_FEATURE_CRQ
mdefine_line|#define FW_FEATURE_CRQ   &t;(1UL&lt;&lt;13)&t;
DECL|macro|FW_FEATURE_VIO
mdefine_line|#define FW_FEATURE_VIO   &t;(1UL&lt;&lt;14)&t;
DECL|macro|FW_FEATURE_RDMA
mdefine_line|#define FW_FEATURE_RDMA   &t;(1UL&lt;&lt;15)&t;
DECL|macro|FW_FEATURE_LLAN
mdefine_line|#define FW_FEATURE_LLAN   &t;(1UL&lt;&lt;16)&t;
DECL|macro|FW_FEATURE_BULK
mdefine_line|#define FW_FEATURE_BULK   &t;(1UL&lt;&lt;17)&t;
DECL|macro|FW_FEATURE_XDABR
mdefine_line|#define FW_FEATURE_XDABR   &t;(1UL&lt;&lt;18)&t;
DECL|macro|FW_FEATURE_MULTITCE
mdefine_line|#define FW_FEATURE_MULTITCE   &t;(1UL&lt;&lt;19)&t;
DECL|macro|FW_FEATURE_SPLPAR
mdefine_line|#define FW_FEATURE_SPLPAR   &t;(1UL&lt;&lt;20)&t;
r_typedef
r_struct
(brace
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|typedef|firmware_feature_t
)brace
id|firmware_feature_t
suffix:semicolon
r_extern
id|firmware_feature_t
id|firmware_features_table
(braket
)braket
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* CPU kernel features */
multiline_comment|/* Retain the 32b definitions for the time being - use bottom half of word */
DECL|macro|CPU_FTR_SPLIT_ID_CACHE
mdefine_line|#define CPU_FTR_SPLIT_ID_CACHE&t;&t;ASM_CONST(0x0000000000000001)
DECL|macro|CPU_FTR_L2CR
mdefine_line|#define CPU_FTR_L2CR&t;&t;&t;ASM_CONST(0x0000000000000002)
DECL|macro|CPU_FTR_SPEC7450
mdefine_line|#define CPU_FTR_SPEC7450&t;&t;ASM_CONST(0x0000000000000004)
DECL|macro|CPU_FTR_ALTIVEC
mdefine_line|#define CPU_FTR_ALTIVEC&t;&t;&t;ASM_CONST(0x0000000000000008)
DECL|macro|CPU_FTR_TAU
mdefine_line|#define CPU_FTR_TAU&t;&t;&t;ASM_CONST(0x0000000000000010)
DECL|macro|CPU_FTR_CAN_DOZE
mdefine_line|#define CPU_FTR_CAN_DOZE&t;&t;ASM_CONST(0x0000000000000020)
DECL|macro|CPU_FTR_USE_TB
mdefine_line|#define CPU_FTR_USE_TB&t;&t;&t;ASM_CONST(0x0000000000000040)
DECL|macro|CPU_FTR_604_PERF_MON
mdefine_line|#define CPU_FTR_604_PERF_MON&t;&t;ASM_CONST(0x0000000000000080)
DECL|macro|CPU_FTR_601
mdefine_line|#define CPU_FTR_601&t;&t;&t;ASM_CONST(0x0000000000000100)
DECL|macro|CPU_FTR_HPTE_TABLE
mdefine_line|#define CPU_FTR_HPTE_TABLE&t;&t;ASM_CONST(0x0000000000000200)
DECL|macro|CPU_FTR_CAN_NAP
mdefine_line|#define CPU_FTR_CAN_NAP&t;&t;&t;ASM_CONST(0x0000000000000400)
DECL|macro|CPU_FTR_L3CR
mdefine_line|#define CPU_FTR_L3CR&t;&t;&t;ASM_CONST(0x0000000000000800)
DECL|macro|CPU_FTR_L3_DISABLE_NAP
mdefine_line|#define CPU_FTR_L3_DISABLE_NAP&t;&t;ASM_CONST(0x0000000000001000)
DECL|macro|CPU_FTR_NAP_DISABLE_L2_PR
mdefine_line|#define CPU_FTR_NAP_DISABLE_L2_PR&t;ASM_CONST(0x0000000000002000)
DECL|macro|CPU_FTR_DUAL_PLL_750FX
mdefine_line|#define CPU_FTR_DUAL_PLL_750FX&t;&t;ASM_CONST(0x0000000000004000)
multiline_comment|/* Add the 64b processor unique features in the top half of the word */
DECL|macro|CPU_FTR_SLB
mdefine_line|#define CPU_FTR_SLB           &t;&t;ASM_CONST(0x0000000100000000)
DECL|macro|CPU_FTR_16M_PAGE
mdefine_line|#define CPU_FTR_16M_PAGE      &t;&t;ASM_CONST(0x0000000200000000)
DECL|macro|CPU_FTR_TLBIEL
mdefine_line|#define CPU_FTR_TLBIEL         &t;&t;ASM_CONST(0x0000000400000000)
DECL|macro|CPU_FTR_NOEXECUTE
mdefine_line|#define CPU_FTR_NOEXECUTE     &t;&t;ASM_CONST(0x0000000800000000)
DECL|macro|CPU_FTR_NODSISRALIGN
mdefine_line|#define CPU_FTR_NODSISRALIGN  &t;&t;ASM_CONST(0x0000001000000000)
DECL|macro|CPU_FTR_IABR
mdefine_line|#define CPU_FTR_IABR  &t;&t;&t;ASM_CONST(0x0000002000000000)
DECL|macro|CPU_FTR_MMCRA
mdefine_line|#define CPU_FTR_MMCRA  &t;&t;&t;ASM_CONST(0x0000004000000000)
DECL|macro|CPU_FTR_PMC8
mdefine_line|#define CPU_FTR_PMC8  &t;&t;&t;ASM_CONST(0x0000008000000000)
DECL|macro|CPU_FTR_SMT
mdefine_line|#define CPU_FTR_SMT  &t;&t;&t;ASM_CONST(0x0000010000000000)
DECL|macro|CPU_FTR_COHERENT_ICACHE
mdefine_line|#define CPU_FTR_COHERENT_ICACHE  &t;ASM_CONST(0x0000020000000000)
DECL|macro|CPU_FTR_LOCKLESS_TLBIE
mdefine_line|#define CPU_FTR_LOCKLESS_TLBIE&t;&t;ASM_CONST(0x0000040000000000)
DECL|macro|CPU_FTR_MMCRA_SIHV
mdefine_line|#define CPU_FTR_MMCRA_SIHV&t;&t;ASM_CONST(0x0000080000000000)
multiline_comment|/* Platform firmware features */
DECL|macro|FW_FTR_
mdefine_line|#define FW_FTR_&t;&t;&t;&t;ASM_CONST(0x0000000000000001)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|COMMON_USER_PPC64
mdefine_line|#define COMMON_USER_PPC64&t;(PPC_FEATURE_32 | PPC_FEATURE_64 | &bslash;&n;&t;&t;&t;         PPC_FEATURE_HAS_FPU | PPC_FEATURE_HAS_MMU)
DECL|macro|CPU_FTR_PPCAS_ARCH_V2_BASE
mdefine_line|#define CPU_FTR_PPCAS_ARCH_V2_BASE (CPU_FTR_SLB | &bslash;&n;                                 CPU_FTR_TLBIEL | CPU_FTR_NOEXECUTE | &bslash;&n;                                 CPU_FTR_NODSISRALIGN)
multiline_comment|/* iSeries doesn&squot;t support large pages */
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|macro|CPU_FTR_PPCAS_ARCH_V2
mdefine_line|#define CPU_FTR_PPCAS_ARCH_V2&t;(CPU_FTR_PPCAS_ARCH_V2_BASE)
macro_line|#else
DECL|macro|CPU_FTR_PPCAS_ARCH_V2
mdefine_line|#define CPU_FTR_PPCAS_ARCH_V2&t;(CPU_FTR_PPCAS_ARCH_V2_BASE | CPU_FTR_16M_PAGE)
macro_line|#endif
DECL|macro|COMMON_PPC64_FW
mdefine_line|#define COMMON_PPC64_FW&t;(0)
macro_line|#endif
macro_line|#ifdef __ASSEMBLY__
DECL|macro|BEGIN_FTR_SECTION
mdefine_line|#define BEGIN_FTR_SECTION&t;&t;98:
DECL|macro|END_FTR_SECTION
mdefine_line|#define END_FTR_SECTION(msk, val)&t;&t;&bslash;&n;99:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.section __ftr_fixup,&quot;a&quot;;&t;&t;&bslash;&n;&t;.align 3;&t;&t;&t;&t;&bslash;&n;&t;.llong msk;&t;&t;&t;        &bslash;&n;&t;.llong val;&t;&t;&t;        &bslash;&n;&t;.llong 98b;&t;&t;&t;        &bslash;&n;&t;.llong 99b;&t; &t;&t;        &bslash;&n;&t;.previous
macro_line|#else
DECL|macro|BEGIN_FTR_SECTION
mdefine_line|#define BEGIN_FTR_SECTION&t;&t;&quot;98:&bslash;n&quot;
DECL|macro|END_FTR_SECTION
mdefine_line|#define END_FTR_SECTION(msk, val)&t;&t;&bslash;&n;&quot;99:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;.section __ftr_fixup,&bslash;&quot;a&bslash;&quot;;&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;.align 3;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&quot;&t;.llong &quot;#msk&quot;;&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;.llong &quot;#val&quot;;&bslash;n&quot;&t;&t;&t;&bslash;&n;&quot;&t;.llong 98b;&bslash;n&quot;&t;&t;&t;        &bslash;&n;&quot;&t;.llong 99b;&bslash;n&quot;&t; &t;&t;        &bslash;&n;&quot;&t;.previous&bslash;n&quot;
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|END_FTR_SECTION_IFSET
mdefine_line|#define END_FTR_SECTION_IFSET(msk)&t;END_FTR_SECTION((msk), (msk))
DECL|macro|END_FTR_SECTION_IFCLR
mdefine_line|#define END_FTR_SECTION_IFCLR(msk)&t;END_FTR_SECTION((msk), 0)
macro_line|#endif /* __ASM_PPC_CPUTABLE_H */
macro_line|#endif /* __KERNEL__ */
eof
