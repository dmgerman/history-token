macro_line|#ifndef _ASM_IA64_KREGS_H
DECL|macro|_ASM_IA64_KREGS_H
mdefine_line|#define _ASM_IA64_KREGS_H
multiline_comment|/*&n; * Copyright (C) 2001-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * This file defines the kernel register usage convention used by Linux/ia64.&n; */
multiline_comment|/*&n; * Kernel registers:&n; */
DECL|macro|IA64_KR_IO_BASE
mdefine_line|#define IA64_KR_IO_BASE&t;&t;0&t;/* ar.k0: legacy I/O base address */
DECL|macro|IA64_KR_TSSD
mdefine_line|#define IA64_KR_TSSD&t;&t;1&t;/* ar.k1: IVE uses this as the TSSD */
DECL|macro|IA64_KR_CURRENT_STACK
mdefine_line|#define IA64_KR_CURRENT_STACK&t;4&t;/* ar.k4: what&squot;s mapped in IA64_TR_CURRENT_STACK */
DECL|macro|IA64_KR_FPU_OWNER
mdefine_line|#define IA64_KR_FPU_OWNER&t;5&t;/* ar.k5: fpu-owner (UP only, at the moment) */
DECL|macro|IA64_KR_CURRENT
mdefine_line|#define IA64_KR_CURRENT&t;&t;6&t;/* ar.k6: &quot;current&quot; task pointer */
DECL|macro|IA64_KR_PT_BASE
mdefine_line|#define IA64_KR_PT_BASE&t;&t;7&t;/* ar.k7: page table base address (physical) */
DECL|macro|_IA64_KR_PASTE
mdefine_line|#define _IA64_KR_PASTE(x,y)&t;x##y
DECL|macro|_IA64_KR_PREFIX
mdefine_line|#define _IA64_KR_PREFIX(n)&t;_IA64_KR_PASTE(ar.k, n)
DECL|macro|IA64_KR
mdefine_line|#define IA64_KR(n)&t;&t;_IA64_KR_PREFIX(IA64_KR_##n)
multiline_comment|/*&n; * Translation registers:&n; */
DECL|macro|IA64_TR_KERNEL
mdefine_line|#define IA64_TR_KERNEL&t;&t;0&t;/* itr0, dtr0: maps kernel image (code &amp; data) */
DECL|macro|IA64_TR_PALCODE
mdefine_line|#define IA64_TR_PALCODE&t;&t;1&t;/* itr1: maps PALcode as required by EFI */
DECL|macro|IA64_TR_PERCPU_DATA
mdefine_line|#define IA64_TR_PERCPU_DATA&t;1&t;/* dtr1: percpu data */
DECL|macro|IA64_TR_CURRENT_STACK
mdefine_line|#define IA64_TR_CURRENT_STACK&t;2&t;/* dtr2: maps kernel&squot;s memory- &amp; register-stacks */
multiline_comment|/* Processor status register bits: */
DECL|macro|IA64_PSR_BE_BIT
mdefine_line|#define IA64_PSR_BE_BIT&t;&t;1
DECL|macro|IA64_PSR_UP_BIT
mdefine_line|#define IA64_PSR_UP_BIT&t;&t;2
DECL|macro|IA64_PSR_AC_BIT
mdefine_line|#define IA64_PSR_AC_BIT&t;&t;3
DECL|macro|IA64_PSR_MFL_BIT
mdefine_line|#define IA64_PSR_MFL_BIT&t;4
DECL|macro|IA64_PSR_MFH_BIT
mdefine_line|#define IA64_PSR_MFH_BIT&t;5
DECL|macro|IA64_PSR_IC_BIT
mdefine_line|#define IA64_PSR_IC_BIT&t;&t;13
DECL|macro|IA64_PSR_I_BIT
mdefine_line|#define IA64_PSR_I_BIT&t;&t;14
DECL|macro|IA64_PSR_PK_BIT
mdefine_line|#define IA64_PSR_PK_BIT&t;&t;15
DECL|macro|IA64_PSR_DT_BIT
mdefine_line|#define IA64_PSR_DT_BIT&t;&t;17
DECL|macro|IA64_PSR_DFL_BIT
mdefine_line|#define IA64_PSR_DFL_BIT&t;18
DECL|macro|IA64_PSR_DFH_BIT
mdefine_line|#define IA64_PSR_DFH_BIT&t;19
DECL|macro|IA64_PSR_SP_BIT
mdefine_line|#define IA64_PSR_SP_BIT&t;&t;20
DECL|macro|IA64_PSR_PP_BIT
mdefine_line|#define IA64_PSR_PP_BIT&t;&t;21
DECL|macro|IA64_PSR_DI_BIT
mdefine_line|#define IA64_PSR_DI_BIT&t;&t;22
DECL|macro|IA64_PSR_SI_BIT
mdefine_line|#define IA64_PSR_SI_BIT&t;&t;23
DECL|macro|IA64_PSR_DB_BIT
mdefine_line|#define IA64_PSR_DB_BIT&t;&t;24
DECL|macro|IA64_PSR_LP_BIT
mdefine_line|#define IA64_PSR_LP_BIT&t;&t;25
DECL|macro|IA64_PSR_TB_BIT
mdefine_line|#define IA64_PSR_TB_BIT&t;&t;26
DECL|macro|IA64_PSR_RT_BIT
mdefine_line|#define IA64_PSR_RT_BIT&t;&t;27
multiline_comment|/* The following are not affected by save_flags()/restore_flags(): */
DECL|macro|IA64_PSR_CPL0_BIT
mdefine_line|#define IA64_PSR_CPL0_BIT&t;32
DECL|macro|IA64_PSR_CPL1_BIT
mdefine_line|#define IA64_PSR_CPL1_BIT&t;33
DECL|macro|IA64_PSR_IS_BIT
mdefine_line|#define IA64_PSR_IS_BIT&t;&t;34
DECL|macro|IA64_PSR_MC_BIT
mdefine_line|#define IA64_PSR_MC_BIT&t;&t;35
DECL|macro|IA64_PSR_IT_BIT
mdefine_line|#define IA64_PSR_IT_BIT&t;&t;36
DECL|macro|IA64_PSR_ID_BIT
mdefine_line|#define IA64_PSR_ID_BIT&t;&t;37
DECL|macro|IA64_PSR_DA_BIT
mdefine_line|#define IA64_PSR_DA_BIT&t;&t;38
DECL|macro|IA64_PSR_DD_BIT
mdefine_line|#define IA64_PSR_DD_BIT&t;&t;39
DECL|macro|IA64_PSR_SS_BIT
mdefine_line|#define IA64_PSR_SS_BIT&t;&t;40
DECL|macro|IA64_PSR_RI_BIT
mdefine_line|#define IA64_PSR_RI_BIT&t;&t;41
DECL|macro|IA64_PSR_ED_BIT
mdefine_line|#define IA64_PSR_ED_BIT&t;&t;43
DECL|macro|IA64_PSR_BN_BIT
mdefine_line|#define IA64_PSR_BN_BIT&t;&t;44
DECL|macro|IA64_PSR_BE
mdefine_line|#define IA64_PSR_BE&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_BE_BIT)
DECL|macro|IA64_PSR_UP
mdefine_line|#define IA64_PSR_UP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_UP_BIT)
DECL|macro|IA64_PSR_AC
mdefine_line|#define IA64_PSR_AC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_AC_BIT)
DECL|macro|IA64_PSR_MFL
mdefine_line|#define IA64_PSR_MFL&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MFL_BIT)
DECL|macro|IA64_PSR_MFH
mdefine_line|#define IA64_PSR_MFH&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MFH_BIT)
DECL|macro|IA64_PSR_IC
mdefine_line|#define IA64_PSR_IC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IC_BIT)
DECL|macro|IA64_PSR_I
mdefine_line|#define IA64_PSR_I&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_I_BIT)
DECL|macro|IA64_PSR_PK
mdefine_line|#define IA64_PSR_PK&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_PK_BIT)
DECL|macro|IA64_PSR_DT
mdefine_line|#define IA64_PSR_DT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DT_BIT)
DECL|macro|IA64_PSR_DFL
mdefine_line|#define IA64_PSR_DFL&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DFL_BIT)
DECL|macro|IA64_PSR_DFH
mdefine_line|#define IA64_PSR_DFH&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DFH_BIT)
DECL|macro|IA64_PSR_SP
mdefine_line|#define IA64_PSR_SP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SP_BIT)
DECL|macro|IA64_PSR_PP
mdefine_line|#define IA64_PSR_PP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_PP_BIT)
DECL|macro|IA64_PSR_DI
mdefine_line|#define IA64_PSR_DI&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DI_BIT)
DECL|macro|IA64_PSR_SI
mdefine_line|#define IA64_PSR_SI&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SI_BIT)
DECL|macro|IA64_PSR_DB
mdefine_line|#define IA64_PSR_DB&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DB_BIT)
DECL|macro|IA64_PSR_LP
mdefine_line|#define IA64_PSR_LP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_LP_BIT)
DECL|macro|IA64_PSR_TB
mdefine_line|#define IA64_PSR_TB&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_TB_BIT)
DECL|macro|IA64_PSR_RT
mdefine_line|#define IA64_PSR_RT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_RT_BIT)
multiline_comment|/* The following are not affected by save_flags()/restore_flags(): */
DECL|macro|IA64_PSR_IS
mdefine_line|#define IA64_PSR_IS&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IS_BIT)
DECL|macro|IA64_PSR_MC
mdefine_line|#define IA64_PSR_MC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MC_BIT)
DECL|macro|IA64_PSR_IT
mdefine_line|#define IA64_PSR_IT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IT_BIT)
DECL|macro|IA64_PSR_ID
mdefine_line|#define IA64_PSR_ID&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_ID_BIT)
DECL|macro|IA64_PSR_DA
mdefine_line|#define IA64_PSR_DA&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DA_BIT)
DECL|macro|IA64_PSR_DD
mdefine_line|#define IA64_PSR_DD&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DD_BIT)
DECL|macro|IA64_PSR_SS
mdefine_line|#define IA64_PSR_SS&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SS_BIT)
DECL|macro|IA64_PSR_RI
mdefine_line|#define IA64_PSR_RI&t;(__IA64_UL(3) &lt;&lt; IA64_PSR_RI_BIT)
DECL|macro|IA64_PSR_ED
mdefine_line|#define IA64_PSR_ED&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_ED_BIT)
DECL|macro|IA64_PSR_BN
mdefine_line|#define IA64_PSR_BN&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_BN_BIT)
multiline_comment|/* User mask bits: */
DECL|macro|IA64_PSR_UM
mdefine_line|#define IA64_PSR_UM&t;(IA64_PSR_BE | IA64_PSR_UP | IA64_PSR_AC | IA64_PSR_MFL | IA64_PSR_MFH)
multiline_comment|/* Default Control Register */
DECL|macro|IA64_DCR_PP_BIT
mdefine_line|#define IA64_DCR_PP_BIT&t;&t; 0&t;/* privileged performance monitor default */
DECL|macro|IA64_DCR_BE_BIT
mdefine_line|#define IA64_DCR_BE_BIT&t;&t; 1&t;/* big-endian default */
DECL|macro|IA64_DCR_LC_BIT
mdefine_line|#define IA64_DCR_LC_BIT&t;&t; 2&t;/* ia32 lock-check enable */
DECL|macro|IA64_DCR_DM_BIT
mdefine_line|#define IA64_DCR_DM_BIT&t;&t; 8&t;/* defer TLB miss faults */
DECL|macro|IA64_DCR_DP_BIT
mdefine_line|#define IA64_DCR_DP_BIT&t;&t; 9&t;/* defer page-not-present faults */
DECL|macro|IA64_DCR_DK_BIT
mdefine_line|#define IA64_DCR_DK_BIT&t;&t;10&t;/* defer key miss faults */
DECL|macro|IA64_DCR_DX_BIT
mdefine_line|#define IA64_DCR_DX_BIT&t;&t;11&t;/* defer key permission faults */
DECL|macro|IA64_DCR_DR_BIT
mdefine_line|#define IA64_DCR_DR_BIT&t;&t;12&t;/* defer access right faults */
DECL|macro|IA64_DCR_DA_BIT
mdefine_line|#define IA64_DCR_DA_BIT&t;&t;13&t;/* defer access bit faults */
DECL|macro|IA64_DCR_DD_BIT
mdefine_line|#define IA64_DCR_DD_BIT&t;&t;14&t;/* defer debug faults */
DECL|macro|IA64_DCR_PP
mdefine_line|#define IA64_DCR_PP&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_PP_BIT)
DECL|macro|IA64_DCR_BE
mdefine_line|#define IA64_DCR_BE&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_BE_BIT)
DECL|macro|IA64_DCR_LC
mdefine_line|#define IA64_DCR_LC&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_LC_BIT)
DECL|macro|IA64_DCR_DM
mdefine_line|#define IA64_DCR_DM&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DM_BIT)
DECL|macro|IA64_DCR_DP
mdefine_line|#define IA64_DCR_DP&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DP_BIT)
DECL|macro|IA64_DCR_DK
mdefine_line|#define IA64_DCR_DK&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DK_BIT)
DECL|macro|IA64_DCR_DX
mdefine_line|#define IA64_DCR_DX&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DX_BIT)
DECL|macro|IA64_DCR_DR
mdefine_line|#define IA64_DCR_DR&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DR_BIT)
DECL|macro|IA64_DCR_DA
mdefine_line|#define IA64_DCR_DA&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DA_BIT)
DECL|macro|IA64_DCR_DD
mdefine_line|#define IA64_DCR_DD&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DD_BIT)
multiline_comment|/* Interrupt Status Register */
DECL|macro|IA64_ISR_X_BIT
mdefine_line|#define IA64_ISR_X_BIT&t;&t;32&t;/* execute access */
DECL|macro|IA64_ISR_W_BIT
mdefine_line|#define IA64_ISR_W_BIT&t;&t;33&t;/* write access */
DECL|macro|IA64_ISR_R_BIT
mdefine_line|#define IA64_ISR_R_BIT&t;&t;34&t;/* read access */
DECL|macro|IA64_ISR_NA_BIT
mdefine_line|#define IA64_ISR_NA_BIT&t;&t;35&t;/* non-access */
DECL|macro|IA64_ISR_SP_BIT
mdefine_line|#define IA64_ISR_SP_BIT&t;&t;36&t;/* speculative load exception */
DECL|macro|IA64_ISR_RS_BIT
mdefine_line|#define IA64_ISR_RS_BIT&t;&t;37&t;/* mandatory register-stack exception */
DECL|macro|IA64_ISR_IR_BIT
mdefine_line|#define IA64_ISR_IR_BIT&t;&t;38&t;/* invalid register frame exception */
DECL|macro|IA64_ISR_CODE_MASK
mdefine_line|#define IA64_ISR_CODE_MASK&t;0xf
DECL|macro|IA64_ISR_X
mdefine_line|#define IA64_ISR_X&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_X_BIT)
DECL|macro|IA64_ISR_W
mdefine_line|#define IA64_ISR_W&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_W_BIT)
DECL|macro|IA64_ISR_R
mdefine_line|#define IA64_ISR_R&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_R_BIT)
DECL|macro|IA64_ISR_NA
mdefine_line|#define IA64_ISR_NA&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_NA_BIT)
DECL|macro|IA64_ISR_SP
mdefine_line|#define IA64_ISR_SP&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_SP_BIT)
DECL|macro|IA64_ISR_RS
mdefine_line|#define IA64_ISR_RS&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_RS_BIT)
DECL|macro|IA64_ISR_IR
mdefine_line|#define IA64_ISR_IR&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_IR_BIT)
multiline_comment|/* ISR code field for non-access instructions */
DECL|macro|IA64_ISR_CODE_TPA
mdefine_line|#define IA64_ISR_CODE_TPA&t;0
DECL|macro|IA64_ISR_CODE_FC
mdefine_line|#define IA64_ISR_CODE_FC&t;1
DECL|macro|IA64_ISR_CODE_PROBE
mdefine_line|#define IA64_ISR_CODE_PROBE&t;2
DECL|macro|IA64_ISR_CODE_TAK
mdefine_line|#define IA64_ISR_CODE_TAK&t;3
DECL|macro|IA64_ISR_CODE_LFETCH
mdefine_line|#define IA64_ISR_CODE_LFETCH&t;4
DECL|macro|IA64_ISR_CODE_PROBEF
mdefine_line|#define IA64_ISR_CODE_PROBEF&t;5
macro_line|#endif /* _ASM_IA64_kREGS_H */
eof
