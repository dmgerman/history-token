multiline_comment|/*&n; * BK Id: SCCS/s.cputable.h 1.3 08/19/01 22:31:46 paulus&n; */
multiline_comment|/*&n; *  include/asm-ppc/cputable.h&n; *&n; *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_PPC_CPUTABLE_H
DECL|macro|__ASM_PPC_CPUTABLE_H
mdefine_line|#define __ASM_PPC_CPUTABLE_H
multiline_comment|/* Exposed to userland CPU features */
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
multiline_comment|/* This structure can grow, it&squot;s real size is used by head.S code&n; * via the mkdefs mecanism.&n; */
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
r_void
(paren
op_star
id|cpu_setup
)paren
(paren
r_int
id|cpu_nr
)paren
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
(braket
)braket
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* CPU kernel features */
DECL|macro|CPU_FTR_SPLIT_ID_CACHE
mdefine_line|#define CPU_FTR_SPLIT_ID_CACHE&t;&t;0x00000001
DECL|macro|CPU_FTR_L2CR
mdefine_line|#define CPU_FTR_L2CR&t;&t;&t;0x00000002
DECL|macro|CPU_FTR_SPEC7450
mdefine_line|#define CPU_FTR_SPEC7450&t;&t;0x00000004
DECL|macro|CPU_FTR_ALTIVEC
mdefine_line|#define CPU_FTR_ALTIVEC&t;&t;&t;0x00000008
DECL|macro|CPU_FTR_TAU
mdefine_line|#define CPU_FTR_TAU&t;&t;&t;0x00000010
DECL|macro|CPU_FTR_CAN_DOZE
mdefine_line|#define CPU_FTR_CAN_DOZE&t;&t;0x00000020
DECL|macro|CPU_FTR_USE_TB
mdefine_line|#define CPU_FTR_USE_TB&t;&t;&t;0x00000040
DECL|macro|CPU_FTR_604_PERF_MON
mdefine_line|#define CPU_FTR_604_PERF_MON&t;&t;0x00000080
DECL|macro|CPU_FTR_601
mdefine_line|#define CPU_FTR_601&t;&t;&t;0x00000100
DECL|macro|CPU_FTR_HPTE_TABLE
mdefine_line|#define CPU_FTR_HPTE_TABLE&t;&t;0x00000200
DECL|macro|CPU_FTR_CAN_NAP
mdefine_line|#define CPU_FTR_CAN_NAP&t;&t;&t;0x00000400
DECL|macro|CPU_FTR_L3CR
mdefine_line|#define CPU_FTR_L3CR&t;&t;&t;0x00000800
macro_line|#ifdef __ASSEMBLY__
DECL|macro|BEGIN_FTR_SECTION
mdefine_line|#define BEGIN_FTR_SECTION&t;&t;98:
DECL|macro|END_FTR_SECTION
mdefine_line|#define END_FTR_SECTION(msk, val)&t;&t;&bslash;&n;99:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.section __ftr_fixup,&quot;a&quot;;&t;&t;&bslash;&n;&t;.align 2;&t;&t;&t;&t;&bslash;&n;&t;.long msk;&t;&t;&t;&t;&bslash;&n;&t;.long val;&t;&t;&t;&t;&bslash;&n;&t;.long 98b;&t;&t;&t;&t;&bslash;&n;&t;.long 99b;&t;&t;&t;&t;&bslash;&n;&t;.previous
DECL|macro|END_FTR_SECTION_IFSET
mdefine_line|#define END_FTR_SECTION_IFSET(msk)&t;END_FTR_SECTION((msk), (msk))
DECL|macro|END_FTR_SECTION_IFCLR
mdefine_line|#define END_FTR_SECTION_IFCLR(msk)&t;END_FTR_SECTION((msk), 0)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PPC_CPUTABLE_H */
macro_line|#endif /* __KERNEL__ */
eof
