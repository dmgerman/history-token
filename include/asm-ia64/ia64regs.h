multiline_comment|/*&n; * Copyright (C) 2002,2003 Intel Corp.&n; *      Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; *      Suresh Siddha &lt;suresh.b.siddha@intel.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_IA64REGS_H
DECL|macro|_ASM_IA64_IA64REGS_H
mdefine_line|#define _ASM_IA64_IA64REGS_H
multiline_comment|/*&n; * Register Names for getreg() and setreg().&n; *&n; * The &quot;magic&quot; numbers happen to match the values used by the Intel compiler&squot;s&n; * getreg()/setreg() intrinsics.&n; */
multiline_comment|/* Special Registers */
DECL|macro|_IA64_REG_IP
mdefine_line|#define _IA64_REG_IP&t;&t;1016&t;/* getreg only */
DECL|macro|_IA64_REG_PSR
mdefine_line|#define _IA64_REG_PSR&t;&t;1019
DECL|macro|_IA64_REG_PSR_L
mdefine_line|#define _IA64_REG_PSR_L&t;&t;1019
multiline_comment|/* General Integer Registers */
DECL|macro|_IA64_REG_GP
mdefine_line|#define _IA64_REG_GP&t;&t;1025&t;/* R1 */
DECL|macro|_IA64_REG_R8
mdefine_line|#define _IA64_REG_R8&t;&t;1032&t;/* R8 */
DECL|macro|_IA64_REG_R9
mdefine_line|#define _IA64_REG_R9&t;&t;1033&t;/* R9 */
DECL|macro|_IA64_REG_SP
mdefine_line|#define _IA64_REG_SP&t;&t;1036&t;/* R12 */
DECL|macro|_IA64_REG_TP
mdefine_line|#define _IA64_REG_TP&t;&t;1037&t;/* R13 */
multiline_comment|/* Application Registers */
DECL|macro|_IA64_REG_AR_KR0
mdefine_line|#define _IA64_REG_AR_KR0&t;3072
DECL|macro|_IA64_REG_AR_KR1
mdefine_line|#define _IA64_REG_AR_KR1&t;3073
DECL|macro|_IA64_REG_AR_KR2
mdefine_line|#define _IA64_REG_AR_KR2&t;3074
DECL|macro|_IA64_REG_AR_KR3
mdefine_line|#define _IA64_REG_AR_KR3&t;3075
DECL|macro|_IA64_REG_AR_KR4
mdefine_line|#define _IA64_REG_AR_KR4&t;3076
DECL|macro|_IA64_REG_AR_KR5
mdefine_line|#define _IA64_REG_AR_KR5&t;3077
DECL|macro|_IA64_REG_AR_KR6
mdefine_line|#define _IA64_REG_AR_KR6&t;3078
DECL|macro|_IA64_REG_AR_KR7
mdefine_line|#define _IA64_REG_AR_KR7&t;3079
DECL|macro|_IA64_REG_AR_RSC
mdefine_line|#define _IA64_REG_AR_RSC&t;3088
DECL|macro|_IA64_REG_AR_BSP
mdefine_line|#define _IA64_REG_AR_BSP&t;3089
DECL|macro|_IA64_REG_AR_BSPSTORE
mdefine_line|#define _IA64_REG_AR_BSPSTORE&t;3090
DECL|macro|_IA64_REG_AR_RNAT
mdefine_line|#define _IA64_REG_AR_RNAT&t;3091
DECL|macro|_IA64_REG_AR_FCR
mdefine_line|#define _IA64_REG_AR_FCR&t;3093
DECL|macro|_IA64_REG_AR_EFLAG
mdefine_line|#define _IA64_REG_AR_EFLAG&t;3096
DECL|macro|_IA64_REG_AR_CSD
mdefine_line|#define _IA64_REG_AR_CSD&t;3097
DECL|macro|_IA64_REG_AR_SSD
mdefine_line|#define _IA64_REG_AR_SSD&t;3098
DECL|macro|_IA64_REG_AR_CFLAG
mdefine_line|#define _IA64_REG_AR_CFLAG&t;3099
DECL|macro|_IA64_REG_AR_FSR
mdefine_line|#define _IA64_REG_AR_FSR&t;3100
DECL|macro|_IA64_REG_AR_FIR
mdefine_line|#define _IA64_REG_AR_FIR&t;3101
DECL|macro|_IA64_REG_AR_FDR
mdefine_line|#define _IA64_REG_AR_FDR&t;3102
DECL|macro|_IA64_REG_AR_CCV
mdefine_line|#define _IA64_REG_AR_CCV&t;3104
DECL|macro|_IA64_REG_AR_UNAT
mdefine_line|#define _IA64_REG_AR_UNAT&t;3108
DECL|macro|_IA64_REG_AR_FPSR
mdefine_line|#define _IA64_REG_AR_FPSR&t;3112
DECL|macro|_IA64_REG_AR_ITC
mdefine_line|#define _IA64_REG_AR_ITC&t;3116
DECL|macro|_IA64_REG_AR_PFS
mdefine_line|#define _IA64_REG_AR_PFS&t;3136
DECL|macro|_IA64_REG_AR_LC
mdefine_line|#define _IA64_REG_AR_LC&t;&t;3137
DECL|macro|_IA64_REG_AR_EC
mdefine_line|#define _IA64_REG_AR_EC&t;&t;3138
multiline_comment|/* Control Registers */
DECL|macro|_IA64_REG_CR_DCR
mdefine_line|#define _IA64_REG_CR_DCR&t;4096
DECL|macro|_IA64_REG_CR_ITM
mdefine_line|#define _IA64_REG_CR_ITM&t;4097
DECL|macro|_IA64_REG_CR_IVA
mdefine_line|#define _IA64_REG_CR_IVA&t;4098
DECL|macro|_IA64_REG_CR_PTA
mdefine_line|#define _IA64_REG_CR_PTA&t;4104
DECL|macro|_IA64_REG_CR_IPSR
mdefine_line|#define _IA64_REG_CR_IPSR&t;4112
DECL|macro|_IA64_REG_CR_ISR
mdefine_line|#define _IA64_REG_CR_ISR&t;4113
DECL|macro|_IA64_REG_CR_IIP
mdefine_line|#define _IA64_REG_CR_IIP&t;4115
DECL|macro|_IA64_REG_CR_IFA
mdefine_line|#define _IA64_REG_CR_IFA&t;4116
DECL|macro|_IA64_REG_CR_ITIR
mdefine_line|#define _IA64_REG_CR_ITIR&t;4117
DECL|macro|_IA64_REG_CR_IIPA
mdefine_line|#define _IA64_REG_CR_IIPA&t;4118
DECL|macro|_IA64_REG_CR_IFS
mdefine_line|#define _IA64_REG_CR_IFS&t;4119
DECL|macro|_IA64_REG_CR_IIM
mdefine_line|#define _IA64_REG_CR_IIM&t;4120
DECL|macro|_IA64_REG_CR_IHA
mdefine_line|#define _IA64_REG_CR_IHA&t;4121
DECL|macro|_IA64_REG_CR_LID
mdefine_line|#define _IA64_REG_CR_LID&t;4160
DECL|macro|_IA64_REG_CR_IVR
mdefine_line|#define _IA64_REG_CR_IVR&t;4161&t;/* getreg only */
DECL|macro|_IA64_REG_CR_TPR
mdefine_line|#define _IA64_REG_CR_TPR&t;4162
DECL|macro|_IA64_REG_CR_EOI
mdefine_line|#define _IA64_REG_CR_EOI&t;4163
DECL|macro|_IA64_REG_CR_IRR0
mdefine_line|#define _IA64_REG_CR_IRR0&t;4164&t;/* getreg only */
DECL|macro|_IA64_REG_CR_IRR1
mdefine_line|#define _IA64_REG_CR_IRR1&t;4165&t;/* getreg only */
DECL|macro|_IA64_REG_CR_IRR2
mdefine_line|#define _IA64_REG_CR_IRR2&t;4166&t;/* getreg only */
DECL|macro|_IA64_REG_CR_IRR3
mdefine_line|#define _IA64_REG_CR_IRR3&t;4167&t;/* getreg only */
DECL|macro|_IA64_REG_CR_ITV
mdefine_line|#define _IA64_REG_CR_ITV&t;4168
DECL|macro|_IA64_REG_CR_PMV
mdefine_line|#define _IA64_REG_CR_PMV&t;4169
DECL|macro|_IA64_REG_CR_CMCV
mdefine_line|#define _IA64_REG_CR_CMCV&t;4170
DECL|macro|_IA64_REG_CR_LRR0
mdefine_line|#define _IA64_REG_CR_LRR0&t;4176
DECL|macro|_IA64_REG_CR_LRR1
mdefine_line|#define _IA64_REG_CR_LRR1&t;4177
multiline_comment|/* Indirect Registers for getindreg() and setindreg() */
DECL|macro|_IA64_REG_INDR_CPUID
mdefine_line|#define _IA64_REG_INDR_CPUID&t;9000&t;/* getindreg only */
DECL|macro|_IA64_REG_INDR_DBR
mdefine_line|#define _IA64_REG_INDR_DBR&t;9001
DECL|macro|_IA64_REG_INDR_IBR
mdefine_line|#define _IA64_REG_INDR_IBR&t;9002
DECL|macro|_IA64_REG_INDR_PKR
mdefine_line|#define _IA64_REG_INDR_PKR&t;9003
DECL|macro|_IA64_REG_INDR_PMC
mdefine_line|#define _IA64_REG_INDR_PMC&t;9004
DECL|macro|_IA64_REG_INDR_PMD
mdefine_line|#define _IA64_REG_INDR_PMD&t;9005
DECL|macro|_IA64_REG_INDR_RR
mdefine_line|#define _IA64_REG_INDR_RR&t;9006
macro_line|#endif /* _ASM_IA64_IA64REGS_H */
eof
