macro_line|#ifndef _ASM_IA64_OFFSETS_H
DECL|macro|_ASM_IA64_OFFSETS_H
mdefine_line|#define _ASM_IA64_OFFSETS_H
multiline_comment|/*&n; * DO NOT MODIFY&n; *&n; * This file was generated by arch/ia64/tools/print_offsets.awk.&n; *&n; */
DECL|macro|CLONE_IDLETASK_BIT
mdefine_line|#define CLONE_IDLETASK_BIT&t;12
DECL|macro|IA64_TASK_SIZE
mdefine_line|#define IA64_TASK_SIZE&t;&t;&t;3952&t;/* 0xf70 */
DECL|macro|IA64_THREAD_INFO_SIZE
mdefine_line|#define IA64_THREAD_INFO_SIZE&t;&t;32&t;/* 0x20 */
DECL|macro|IA64_PT_REGS_SIZE
mdefine_line|#define IA64_PT_REGS_SIZE&t;&t;400&t;/* 0x190 */
DECL|macro|IA64_SWITCH_STACK_SIZE
mdefine_line|#define IA64_SWITCH_STACK_SIZE&t;&t;560&t;/* 0x230 */
DECL|macro|IA64_SIGINFO_SIZE
mdefine_line|#define IA64_SIGINFO_SIZE&t;&t;128&t;/* 0x80 */
DECL|macro|IA64_CPU_SIZE
mdefine_line|#define IA64_CPU_SIZE&t;&t;&t;224&t;/* 0xe0 */
DECL|macro|SIGFRAME_SIZE
mdefine_line|#define SIGFRAME_SIZE&t;&t;&t;2816&t;/* 0xb00 */
DECL|macro|UNW_FRAME_INFO_SIZE
mdefine_line|#define UNW_FRAME_INFO_SIZE&t;&t;448&t;/* 0x1c0 */
DECL|macro|IA64_TASK_THREAD_KSP_OFFSET
mdefine_line|#define IA64_TASK_THREAD_KSP_OFFSET&t;1496&t;/* 0x5d8 */
DECL|macro|IA64_TASK_PID_OFFSET
mdefine_line|#define IA64_TASK_PID_OFFSET&t;&t;212&t;/* 0xd4 */
DECL|macro|IA64_PT_REGS_CR_IPSR_OFFSET
mdefine_line|#define IA64_PT_REGS_CR_IPSR_OFFSET&t;0&t;/* 0x0 */
DECL|macro|IA64_PT_REGS_CR_IIP_OFFSET
mdefine_line|#define IA64_PT_REGS_CR_IIP_OFFSET&t;8&t;/* 0x8 */
DECL|macro|IA64_PT_REGS_CR_IFS_OFFSET
mdefine_line|#define IA64_PT_REGS_CR_IFS_OFFSET&t;16&t;/* 0x10 */
DECL|macro|IA64_PT_REGS_AR_UNAT_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_UNAT_OFFSET&t;24&t;/* 0x18 */
DECL|macro|IA64_PT_REGS_AR_PFS_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_PFS_OFFSET&t;32&t;/* 0x20 */
DECL|macro|IA64_PT_REGS_AR_RSC_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_RSC_OFFSET&t;40&t;/* 0x28 */
DECL|macro|IA64_PT_REGS_AR_RNAT_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_RNAT_OFFSET&t;48&t;/* 0x30 */
DECL|macro|IA64_PT_REGS_AR_BSPSTORE_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_BSPSTORE_OFFSET&t;56&t;/* 0x38 */
DECL|macro|IA64_PT_REGS_PR_OFFSET
mdefine_line|#define IA64_PT_REGS_PR_OFFSET&t;&t;64&t;/* 0x40 */
DECL|macro|IA64_PT_REGS_B6_OFFSET
mdefine_line|#define IA64_PT_REGS_B6_OFFSET&t;&t;72&t;/* 0x48 */
DECL|macro|IA64_PT_REGS_LOADRS_OFFSET
mdefine_line|#define IA64_PT_REGS_LOADRS_OFFSET&t;80&t;/* 0x50 */
DECL|macro|IA64_PT_REGS_R1_OFFSET
mdefine_line|#define IA64_PT_REGS_R1_OFFSET&t;&t;88&t;/* 0x58 */
DECL|macro|IA64_PT_REGS_R2_OFFSET
mdefine_line|#define IA64_PT_REGS_R2_OFFSET&t;&t;96&t;/* 0x60 */
DECL|macro|IA64_PT_REGS_R3_OFFSET
mdefine_line|#define IA64_PT_REGS_R3_OFFSET&t;&t;104&t;/* 0x68 */
DECL|macro|IA64_PT_REGS_R12_OFFSET
mdefine_line|#define IA64_PT_REGS_R12_OFFSET&t;&t;112&t;/* 0x70 */
DECL|macro|IA64_PT_REGS_R13_OFFSET
mdefine_line|#define IA64_PT_REGS_R13_OFFSET&t;&t;120&t;/* 0x78 */
DECL|macro|IA64_PT_REGS_R14_OFFSET
mdefine_line|#define IA64_PT_REGS_R14_OFFSET&t;&t;128&t;/* 0x80 */
DECL|macro|IA64_PT_REGS_R15_OFFSET
mdefine_line|#define IA64_PT_REGS_R15_OFFSET&t;&t;136&t;/* 0x88 */
DECL|macro|IA64_PT_REGS_R8_OFFSET
mdefine_line|#define IA64_PT_REGS_R8_OFFSET&t;&t;144&t;/* 0x90 */
DECL|macro|IA64_PT_REGS_R9_OFFSET
mdefine_line|#define IA64_PT_REGS_R9_OFFSET&t;&t;152&t;/* 0x98 */
DECL|macro|IA64_PT_REGS_R10_OFFSET
mdefine_line|#define IA64_PT_REGS_R10_OFFSET&t;&t;160&t;/* 0xa0 */
DECL|macro|IA64_PT_REGS_R11_OFFSET
mdefine_line|#define IA64_PT_REGS_R11_OFFSET&t;&t;168&t;/* 0xa8 */
DECL|macro|IA64_PT_REGS_R16_OFFSET
mdefine_line|#define IA64_PT_REGS_R16_OFFSET&t;&t;176&t;/* 0xb0 */
DECL|macro|IA64_PT_REGS_R17_OFFSET
mdefine_line|#define IA64_PT_REGS_R17_OFFSET&t;&t;184&t;/* 0xb8 */
DECL|macro|IA64_PT_REGS_R18_OFFSET
mdefine_line|#define IA64_PT_REGS_R18_OFFSET&t;&t;192&t;/* 0xc0 */
DECL|macro|IA64_PT_REGS_R19_OFFSET
mdefine_line|#define IA64_PT_REGS_R19_OFFSET&t;&t;200&t;/* 0xc8 */
DECL|macro|IA64_PT_REGS_R20_OFFSET
mdefine_line|#define IA64_PT_REGS_R20_OFFSET&t;&t;208&t;/* 0xd0 */
DECL|macro|IA64_PT_REGS_R21_OFFSET
mdefine_line|#define IA64_PT_REGS_R21_OFFSET&t;&t;216&t;/* 0xd8 */
DECL|macro|IA64_PT_REGS_R22_OFFSET
mdefine_line|#define IA64_PT_REGS_R22_OFFSET&t;&t;224&t;/* 0xe0 */
DECL|macro|IA64_PT_REGS_R23_OFFSET
mdefine_line|#define IA64_PT_REGS_R23_OFFSET&t;&t;232&t;/* 0xe8 */
DECL|macro|IA64_PT_REGS_R24_OFFSET
mdefine_line|#define IA64_PT_REGS_R24_OFFSET&t;&t;240&t;/* 0xf0 */
DECL|macro|IA64_PT_REGS_R25_OFFSET
mdefine_line|#define IA64_PT_REGS_R25_OFFSET&t;&t;248&t;/* 0xf8 */
DECL|macro|IA64_PT_REGS_R26_OFFSET
mdefine_line|#define IA64_PT_REGS_R26_OFFSET&t;&t;256&t;/* 0x100 */
DECL|macro|IA64_PT_REGS_R27_OFFSET
mdefine_line|#define IA64_PT_REGS_R27_OFFSET&t;&t;264&t;/* 0x108 */
DECL|macro|IA64_PT_REGS_R28_OFFSET
mdefine_line|#define IA64_PT_REGS_R28_OFFSET&t;&t;272&t;/* 0x110 */
DECL|macro|IA64_PT_REGS_R29_OFFSET
mdefine_line|#define IA64_PT_REGS_R29_OFFSET&t;&t;280&t;/* 0x118 */
DECL|macro|IA64_PT_REGS_R30_OFFSET
mdefine_line|#define IA64_PT_REGS_R30_OFFSET&t;&t;288&t;/* 0x120 */
DECL|macro|IA64_PT_REGS_R31_OFFSET
mdefine_line|#define IA64_PT_REGS_R31_OFFSET&t;&t;296&t;/* 0x128 */
DECL|macro|IA64_PT_REGS_AR_CCV_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_CCV_OFFSET&t;304&t;/* 0x130 */
DECL|macro|IA64_PT_REGS_AR_FPSR_OFFSET
mdefine_line|#define IA64_PT_REGS_AR_FPSR_OFFSET&t;312&t;/* 0x138 */
DECL|macro|IA64_PT_REGS_B0_OFFSET
mdefine_line|#define IA64_PT_REGS_B0_OFFSET&t;&t;320&t;/* 0x140 */
DECL|macro|IA64_PT_REGS_B7_OFFSET
mdefine_line|#define IA64_PT_REGS_B7_OFFSET&t;&t;328&t;/* 0x148 */
DECL|macro|IA64_PT_REGS_F6_OFFSET
mdefine_line|#define IA64_PT_REGS_F6_OFFSET&t;&t;336&t;/* 0x150 */
DECL|macro|IA64_PT_REGS_F7_OFFSET
mdefine_line|#define IA64_PT_REGS_F7_OFFSET&t;&t;352&t;/* 0x160 */
DECL|macro|IA64_PT_REGS_F8_OFFSET
mdefine_line|#define IA64_PT_REGS_F8_OFFSET&t;&t;368&t;/* 0x170 */
DECL|macro|IA64_PT_REGS_F9_OFFSET
mdefine_line|#define IA64_PT_REGS_F9_OFFSET&t;&t;384&t;/* 0x180 */
DECL|macro|IA64_SWITCH_STACK_CALLER_UNAT_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_CALLER_UNAT_OFFSET 0&t;/* 0x0 */
DECL|macro|IA64_SWITCH_STACK_AR_FPSR_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_FPSR_OFFSET 8&t;/* 0x8 */
DECL|macro|IA64_SWITCH_STACK_F2_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F2_OFFSET&t;16&t;/* 0x10 */
DECL|macro|IA64_SWITCH_STACK_F3_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F3_OFFSET&t;32&t;/* 0x20 */
DECL|macro|IA64_SWITCH_STACK_F4_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F4_OFFSET&t;48&t;/* 0x30 */
DECL|macro|IA64_SWITCH_STACK_F5_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F5_OFFSET&t;64&t;/* 0x40 */
DECL|macro|IA64_SWITCH_STACK_F10_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F10_OFFSET&t;80&t;/* 0x50 */
DECL|macro|IA64_SWITCH_STACK_F11_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F11_OFFSET&t;96&t;/* 0x60 */
DECL|macro|IA64_SWITCH_STACK_F12_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F12_OFFSET&t;112&t;/* 0x70 */
DECL|macro|IA64_SWITCH_STACK_F13_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F13_OFFSET&t;128&t;/* 0x80 */
DECL|macro|IA64_SWITCH_STACK_F14_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F14_OFFSET&t;144&t;/* 0x90 */
DECL|macro|IA64_SWITCH_STACK_F15_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F15_OFFSET&t;160&t;/* 0xa0 */
DECL|macro|IA64_SWITCH_STACK_F16_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F16_OFFSET&t;176&t;/* 0xb0 */
DECL|macro|IA64_SWITCH_STACK_F17_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F17_OFFSET&t;192&t;/* 0xc0 */
DECL|macro|IA64_SWITCH_STACK_F18_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F18_OFFSET&t;208&t;/* 0xd0 */
DECL|macro|IA64_SWITCH_STACK_F19_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F19_OFFSET&t;224&t;/* 0xe0 */
DECL|macro|IA64_SWITCH_STACK_F20_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F20_OFFSET&t;240&t;/* 0xf0 */
DECL|macro|IA64_SWITCH_STACK_F21_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F21_OFFSET&t;256&t;/* 0x100 */
DECL|macro|IA64_SWITCH_STACK_F22_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F22_OFFSET&t;272&t;/* 0x110 */
DECL|macro|IA64_SWITCH_STACK_F23_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F23_OFFSET&t;288&t;/* 0x120 */
DECL|macro|IA64_SWITCH_STACK_F24_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F24_OFFSET&t;304&t;/* 0x130 */
DECL|macro|IA64_SWITCH_STACK_F25_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F25_OFFSET&t;320&t;/* 0x140 */
DECL|macro|IA64_SWITCH_STACK_F26_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F26_OFFSET&t;336&t;/* 0x150 */
DECL|macro|IA64_SWITCH_STACK_F27_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F27_OFFSET&t;352&t;/* 0x160 */
DECL|macro|IA64_SWITCH_STACK_F28_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F28_OFFSET&t;368&t;/* 0x170 */
DECL|macro|IA64_SWITCH_STACK_F29_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F29_OFFSET&t;384&t;/* 0x180 */
DECL|macro|IA64_SWITCH_STACK_F30_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F30_OFFSET&t;400&t;/* 0x190 */
DECL|macro|IA64_SWITCH_STACK_F31_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_F31_OFFSET&t;416&t;/* 0x1a0 */
DECL|macro|IA64_SWITCH_STACK_R4_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_R4_OFFSET&t;432&t;/* 0x1b0 */
DECL|macro|IA64_SWITCH_STACK_R5_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_R5_OFFSET&t;440&t;/* 0x1b8 */
DECL|macro|IA64_SWITCH_STACK_R6_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_R6_OFFSET&t;448&t;/* 0x1c0 */
DECL|macro|IA64_SWITCH_STACK_R7_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_R7_OFFSET&t;456&t;/* 0x1c8 */
DECL|macro|IA64_SWITCH_STACK_B0_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B0_OFFSET&t;464&t;/* 0x1d0 */
DECL|macro|IA64_SWITCH_STACK_B1_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B1_OFFSET&t;472&t;/* 0x1d8 */
DECL|macro|IA64_SWITCH_STACK_B2_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B2_OFFSET&t;480&t;/* 0x1e0 */
DECL|macro|IA64_SWITCH_STACK_B3_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B3_OFFSET&t;488&t;/* 0x1e8 */
DECL|macro|IA64_SWITCH_STACK_B4_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B4_OFFSET&t;496&t;/* 0x1f0 */
DECL|macro|IA64_SWITCH_STACK_B5_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_B5_OFFSET&t;504&t;/* 0x1f8 */
DECL|macro|IA64_SWITCH_STACK_AR_PFS_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_PFS_OFFSET&t;512&t;/* 0x200 */
DECL|macro|IA64_SWITCH_STACK_AR_LC_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_LC_OFFSET&t;520&t;/* 0x208 */
DECL|macro|IA64_SWITCH_STACK_AR_UNAT_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_UNAT_OFFSET 528&t;/* 0x210 */
DECL|macro|IA64_SWITCH_STACK_AR_RNAT_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_RNAT_OFFSET 536&t;/* 0x218 */
DECL|macro|IA64_SWITCH_STACK_AR_BSPSTORE_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_AR_BSPSTORE_OFFSET 544&t;/* 0x220 */
DECL|macro|IA64_SWITCH_STACK_PR_OFFSET
mdefine_line|#define IA64_SWITCH_STACK_PR_OFFSET&t;552&t;/* 0x228 */
DECL|macro|IA64_SIGCONTEXT_IP_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_IP_OFFSET&t;40&t;/* 0x28 */
DECL|macro|IA64_SIGCONTEXT_AR_BSP_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_AR_BSP_OFFSET&t;72&t;/* 0x48 */
DECL|macro|IA64_SIGCONTEXT_AR_FPSR_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_AR_FPSR_OFFSET&t;104&t;/* 0x68 */
DECL|macro|IA64_SIGCONTEXT_AR_RNAT_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_AR_RNAT_OFFSET&t;80&t;/* 0x50 */
DECL|macro|IA64_SIGCONTEXT_AR_UNAT_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_AR_UNAT_OFFSET&t;96&t;/* 0x60 */
DECL|macro|IA64_SIGCONTEXT_B0_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_B0_OFFSET&t;136&t;/* 0x88 */
DECL|macro|IA64_SIGCONTEXT_CFM_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_CFM_OFFSET&t;48&t;/* 0x30 */
DECL|macro|IA64_SIGCONTEXT_FLAGS_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_FLAGS_OFFSET&t;0&t;/* 0x0 */
DECL|macro|IA64_SIGCONTEXT_FR6_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_FR6_OFFSET&t;560&t;/* 0x230 */
DECL|macro|IA64_SIGCONTEXT_PR_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_PR_OFFSET&t;128&t;/* 0x80 */
DECL|macro|IA64_SIGCONTEXT_R12_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_R12_OFFSET&t;296&t;/* 0x128 */
DECL|macro|IA64_SIGCONTEXT_RBS_BASE_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_RBS_BASE_OFFSET&t;2512&t;/* 0x9d0 */
DECL|macro|IA64_SIGCONTEXT_LOADRS_OFFSET
mdefine_line|#define IA64_SIGCONTEXT_LOADRS_OFFSET&t;2520&t;/* 0x9d8 */
DECL|macro|IA64_SIGFRAME_ARG0_OFFSET
mdefine_line|#define IA64_SIGFRAME_ARG0_OFFSET&t;0&t;/* 0x0 */
DECL|macro|IA64_SIGFRAME_ARG1_OFFSET
mdefine_line|#define IA64_SIGFRAME_ARG1_OFFSET&t;8&t;/* 0x8 */
DECL|macro|IA64_SIGFRAME_ARG2_OFFSET
mdefine_line|#define IA64_SIGFRAME_ARG2_OFFSET&t;16&t;/* 0x10 */
DECL|macro|IA64_SIGFRAME_HANDLER_OFFSET
mdefine_line|#define IA64_SIGFRAME_HANDLER_OFFSET&t;24&t;/* 0x18 */
DECL|macro|IA64_SIGFRAME_SIGCONTEXT_OFFSET
mdefine_line|#define IA64_SIGFRAME_SIGCONTEXT_OFFSET&t;160&t;/* 0xa0 */
DECL|macro|IA64_CLONE_VFORK
mdefine_line|#define IA64_CLONE_VFORK&t;&t;16384&t;/* 0x4000 */
DECL|macro|IA64_CLONE_VM
mdefine_line|#define IA64_CLONE_VM&t;&t;&t;256&t;/* 0x100 */
macro_line|#endif /* _ASM_IA64_OFFSETS_H */
eof
