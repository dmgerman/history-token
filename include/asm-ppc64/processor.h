macro_line|#ifndef __ASM_PPC64_PROCESSOR_H
DECL|macro|__ASM_PPC64_PROCESSOR_H
mdefine_line|#define __ASM_PPC64_PROCESSOR_H
multiline_comment|/*&n; * Copyright (C) 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
multiline_comment|/* Machine State Register (MSR) Fields */
DECL|macro|MSR_SF_LG
mdefine_line|#define MSR_SF_LG&t;63              /* Enable 64 bit mode */
DECL|macro|MSR_ISF_LG
mdefine_line|#define MSR_ISF_LG&t;61              /* Interrupt 64b mode valid on 630 */
DECL|macro|MSR_HV_LG
mdefine_line|#define MSR_HV_LG &t;60              /* Hypervisor state */
DECL|macro|MSR_VEC_LG
mdefine_line|#define MSR_VEC_LG&t;25&t;        /* Enable AltiVec */
DECL|macro|MSR_POW_LG
mdefine_line|#define MSR_POW_LG&t;18&t;&t;/* Enable Power Management */
DECL|macro|MSR_WE_LG
mdefine_line|#define MSR_WE_LG&t;18&t;&t;/* Wait State Enable */
DECL|macro|MSR_TGPR_LG
mdefine_line|#define MSR_TGPR_LG&t;17&t;&t;/* TLB Update registers in use */
DECL|macro|MSR_CE_LG
mdefine_line|#define MSR_CE_LG&t;17&t;&t;/* Critical Interrupt Enable */
DECL|macro|MSR_ILE_LG
mdefine_line|#define MSR_ILE_LG&t;16&t;&t;/* Interrupt Little Endian */
DECL|macro|MSR_EE_LG
mdefine_line|#define MSR_EE_LG&t;15&t;&t;/* External Interrupt Enable */
DECL|macro|MSR_PR_LG
mdefine_line|#define MSR_PR_LG&t;14&t;&t;/* Problem State / Privilege Level */
DECL|macro|MSR_FP_LG
mdefine_line|#define MSR_FP_LG&t;13&t;&t;/* Floating Point enable */
DECL|macro|MSR_ME_LG
mdefine_line|#define MSR_ME_LG&t;12&t;&t;/* Machine Check Enable */
DECL|macro|MSR_FE0_LG
mdefine_line|#define MSR_FE0_LG&t;11&t;&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE_LG
mdefine_line|#define MSR_SE_LG&t;10&t;&t;/* Single Step */
DECL|macro|MSR_BE_LG
mdefine_line|#define MSR_BE_LG&t;9&t;&t;/* Branch Trace */
DECL|macro|MSR_DE_LG
mdefine_line|#define MSR_DE_LG&t;9 &t;&t;/* Debug Exception Enable */
DECL|macro|MSR_FE1_LG
mdefine_line|#define MSR_FE1_LG&t;8&t;&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP_LG
mdefine_line|#define MSR_IP_LG&t;6&t;&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR_LG
mdefine_line|#define MSR_IR_LG&t;5 &t;&t;/* Instruction Relocate */
DECL|macro|MSR_DR_LG
mdefine_line|#define MSR_DR_LG&t;4 &t;&t;/* Data Relocate */
DECL|macro|MSR_PE_LG
mdefine_line|#define MSR_PE_LG&t;3&t;&t;/* Protection Enable */
DECL|macro|MSR_PX_LG
mdefine_line|#define MSR_PX_LG&t;2&t;&t;/* Protection Exclusive Mode */
DECL|macro|MSR_PMM_LG
mdefine_line|#define MSR_PMM_LG&t;2&t;&t;/* Performance monitor */
DECL|macro|MSR_RI_LG
mdefine_line|#define MSR_RI_LG&t;1&t;&t;/* Recoverable Exception */
DECL|macro|MSR_LE_LG
mdefine_line|#define MSR_LE_LG&t;0 &t;&t;/* Little Endian */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__MASK
mdefine_line|#define __MASK(X)&t;(1&lt;&lt;(X))
macro_line|#else
DECL|macro|__MASK
mdefine_line|#define __MASK(X)&t;(1UL&lt;&lt;(X))
macro_line|#endif
DECL|macro|MSR_SF
mdefine_line|#define MSR_SF&t;&t;__MASK(MSR_SF_LG)&t;/* Enable 64 bit mode */
DECL|macro|MSR_ISF
mdefine_line|#define MSR_ISF&t;&t;__MASK(MSR_ISF_LG)&t;/* Interrupt 64b mode valid on 630 */
DECL|macro|MSR_HV
mdefine_line|#define MSR_HV &t;&t;__MASK(MSR_HV_LG)&t;/* Hypervisor state */
DECL|macro|MSR_VEC
mdefine_line|#define MSR_VEC&t;&t;__MASK(MSR_VEC_LG)&t;/* Enable AltiVec */
DECL|macro|MSR_POW
mdefine_line|#define MSR_POW&t;&t;__MASK(MSR_POW_LG)&t;/* Enable Power Management */
DECL|macro|MSR_WE
mdefine_line|#define MSR_WE&t;&t;__MASK(MSR_WE_LG)&t;/* Wait State Enable */
DECL|macro|MSR_TGPR
mdefine_line|#define MSR_TGPR&t;__MASK(MSR_TGPR_LG)&t;/* TLB Update registers in use */
DECL|macro|MSR_CE
mdefine_line|#define MSR_CE&t;&t;__MASK(MSR_CE_LG)&t;/* Critical Interrupt Enable */
DECL|macro|MSR_ILE
mdefine_line|#define MSR_ILE&t;&t;__MASK(MSR_ILE_LG)&t;/* Interrupt Little Endian */
DECL|macro|MSR_EE
mdefine_line|#define MSR_EE&t;&t;__MASK(MSR_EE_LG)&t;/* External Interrupt Enable */
DECL|macro|MSR_PR
mdefine_line|#define MSR_PR&t;&t;__MASK(MSR_PR_LG)&t;/* Problem State / Privilege Level */
DECL|macro|MSR_FP
mdefine_line|#define MSR_FP&t;&t;__MASK(MSR_FP_LG)&t;/* Floating Point enable */
DECL|macro|MSR_ME
mdefine_line|#define MSR_ME&t;&t;__MASK(MSR_ME_LG)&t;/* Machine Check Enable */
DECL|macro|MSR_FE0
mdefine_line|#define MSR_FE0&t;&t;__MASK(MSR_FE0_LG)&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE
mdefine_line|#define MSR_SE&t;&t;__MASK(MSR_SE_LG)&t;/* Single Step */
DECL|macro|MSR_BE
mdefine_line|#define MSR_BE&t;&t;__MASK(MSR_BE_LG)&t;/* Branch Trace */
DECL|macro|MSR_DE
mdefine_line|#define MSR_DE&t;&t;__MASK(MSR_DE_LG)&t;/* Debug Exception Enable */
DECL|macro|MSR_FE1
mdefine_line|#define MSR_FE1&t;&t;__MASK(MSR_FE1_LG)&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP
mdefine_line|#define MSR_IP&t;&t;__MASK(MSR_IP_LG)&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR
mdefine_line|#define MSR_IR&t;&t;__MASK(MSR_IR_LG)&t;/* Instruction Relocate */
DECL|macro|MSR_DR
mdefine_line|#define MSR_DR&t;&t;__MASK(MSR_DR_LG)&t;/* Data Relocate */
DECL|macro|MSR_PE
mdefine_line|#define MSR_PE&t;&t;__MASK(MSR_PE_LG)&t;/* Protection Enable */
DECL|macro|MSR_PX
mdefine_line|#define MSR_PX&t;&t;__MASK(MSR_PX_LG)&t;/* Protection Exclusive Mode */
DECL|macro|MSR_PMM
mdefine_line|#define MSR_PMM&t;&t;__MASK(MSR_PMM_LG)&t;/* Performance monitor */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;__MASK(MSR_RI_LG)&t;/* Recoverable Exception */
DECL|macro|MSR_LE
mdefine_line|#define MSR_LE&t;&t;__MASK(MSR_LE_LG)&t;/* Little Endian */
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;MSR_ME | MSR_RI | MSR_IR | MSR_DR | MSR_ISF
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL      MSR_ | MSR_SF | MSR_HV
DECL|macro|MSR_USER32
mdefine_line|#define MSR_USER32&t;MSR_ | MSR_PR | MSR_EE
DECL|macro|MSR_USER64
mdefine_line|#define MSR_USER64&t;MSR_USER32 | MSR_SF
multiline_comment|/* Floating Point Status and Control Register (FPSCR) Fields */
DECL|macro|FPSCR_FX
mdefine_line|#define FPSCR_FX&t;0x80000000&t;/* FPU exception summary */
DECL|macro|FPSCR_FEX
mdefine_line|#define FPSCR_FEX&t;0x40000000&t;/* FPU enabled exception summary */
DECL|macro|FPSCR_VX
mdefine_line|#define FPSCR_VX&t;0x20000000&t;/* Invalid operation summary */
DECL|macro|FPSCR_OX
mdefine_line|#define FPSCR_OX&t;0x10000000&t;/* Overflow exception summary */
DECL|macro|FPSCR_UX
mdefine_line|#define FPSCR_UX&t;0x08000000&t;/* Underflow exception summary */
DECL|macro|FPSCR_ZX
mdefine_line|#define FPSCR_ZX&t;0x04000000&t;/* Zero-divide exception summary */
DECL|macro|FPSCR_XX
mdefine_line|#define FPSCR_XX&t;0x02000000&t;/* Inexact exception summary */
DECL|macro|FPSCR_VXSNAN
mdefine_line|#define FPSCR_VXSNAN&t;0x01000000&t;/* Invalid op for SNaN */
DECL|macro|FPSCR_VXISI
mdefine_line|#define FPSCR_VXISI&t;0x00800000&t;/* Invalid op for Inv - Inv */
DECL|macro|FPSCR_VXIDI
mdefine_line|#define FPSCR_VXIDI&t;0x00400000&t;/* Invalid op for Inv / Inv */
DECL|macro|FPSCR_VXZDZ
mdefine_line|#define FPSCR_VXZDZ&t;0x00200000&t;/* Invalid op for Zero / Zero */
DECL|macro|FPSCR_VXIMZ
mdefine_line|#define FPSCR_VXIMZ&t;0x00100000&t;/* Invalid op for Inv * Zero */
DECL|macro|FPSCR_VXVC
mdefine_line|#define FPSCR_VXVC&t;0x00080000&t;/* Invalid op for Compare */
DECL|macro|FPSCR_FR
mdefine_line|#define FPSCR_FR&t;0x00040000&t;/* Fraction rounded */
DECL|macro|FPSCR_FI
mdefine_line|#define FPSCR_FI&t;0x00020000&t;/* Fraction inexact */
DECL|macro|FPSCR_FPRF
mdefine_line|#define FPSCR_FPRF&t;0x0001f000&t;/* FPU Result Flags */
DECL|macro|FPSCR_FPCC
mdefine_line|#define FPSCR_FPCC&t;0x0000f000&t;/* FPU Condition Codes */
DECL|macro|FPSCR_VXSOFT
mdefine_line|#define FPSCR_VXSOFT&t;0x00000400&t;/* Invalid op for software request */
DECL|macro|FPSCR_VXSQRT
mdefine_line|#define FPSCR_VXSQRT&t;0x00000200&t;/* Invalid op for square root */
DECL|macro|FPSCR_VXCVI
mdefine_line|#define FPSCR_VXCVI&t;0x00000100&t;/* Invalid op for integer convert */
DECL|macro|FPSCR_VE
mdefine_line|#define FPSCR_VE&t;0x00000080&t;/* Invalid op exception enable */
DECL|macro|FPSCR_OE
mdefine_line|#define FPSCR_OE&t;0x00000040&t;/* IEEE overflow exception enable */
DECL|macro|FPSCR_UE
mdefine_line|#define FPSCR_UE&t;0x00000020&t;/* IEEE underflow exception enable */
DECL|macro|FPSCR_ZE
mdefine_line|#define FPSCR_ZE&t;0x00000010&t;/* IEEE zero divide exception enable */
DECL|macro|FPSCR_XE
mdefine_line|#define FPSCR_XE&t;0x00000008&t;/* FP inexact exception enable */
DECL|macro|FPSCR_NI
mdefine_line|#define FPSCR_NI&t;0x00000004&t;/* FPU non IEEE-Mode */
DECL|macro|FPSCR_RN
mdefine_line|#define FPSCR_RN&t;0x00000003&t;/* FPU rounding control */
multiline_comment|/* Special Purpose Registers (SPRNs)*/
DECL|macro|SPRN_CDBCR
mdefine_line|#define&t;SPRN_CDBCR&t;0x3D7&t;/* Cache Debug Control Register */
DECL|macro|SPRN_CTR
mdefine_line|#define&t;SPRN_CTR&t;0x009&t;/* Count Register */
DECL|macro|SPRN_DABR
mdefine_line|#define&t;SPRN_DABR&t;0x3F5&t;/* Data Address Breakpoint Register */
DECL|macro|SPRN_DAC1
mdefine_line|#define&t;SPRN_DAC1&t;0x3F6&t;/* Data Address Compare 1 */
DECL|macro|SPRN_DAC2
mdefine_line|#define&t;SPRN_DAC2&t;0x3F7&t;/* Data Address Compare 2 */
DECL|macro|SPRN_DAR
mdefine_line|#define&t;SPRN_DAR&t;0x013&t;/* Data Address Register */
DECL|macro|SPRN_DBCR
mdefine_line|#define&t;SPRN_DBCR&t;0x3F2&t;/* Debug Control Regsiter */
DECL|macro|DBCR_EDM
mdefine_line|#define&t;  DBCR_EDM&t;0x80000000
DECL|macro|DBCR_IDM
mdefine_line|#define&t;  DBCR_IDM&t;0x40000000
DECL|macro|DBCR_RST
mdefine_line|#define&t;  DBCR_RST(x)&t;(((x) &amp; 0x3) &lt;&lt; 28)
DECL|macro|DBCR_RST_NONE
mdefine_line|#define&t;    DBCR_RST_NONE       &t;0
DECL|macro|DBCR_RST_CORE
mdefine_line|#define&t;    DBCR_RST_CORE       &t;1
DECL|macro|DBCR_RST_CHIP
mdefine_line|#define&t;    DBCR_RST_CHIP       &t;2
DECL|macro|DBCR_RST_SYSTEM
mdefine_line|#define&t;    DBCR_RST_SYSTEM&t;&t;3
DECL|macro|DBCR_IC
mdefine_line|#define&t;  DBCR_IC&t;0x08000000&t;/* Instruction Completion Debug Evnt */
DECL|macro|DBCR_BT
mdefine_line|#define&t;  DBCR_BT&t;0x04000000&t;/* Branch Taken Debug Event */
DECL|macro|DBCR_EDE
mdefine_line|#define&t;  DBCR_EDE&t;0x02000000&t;/* Exception Debug Event */
DECL|macro|DBCR_TDE
mdefine_line|#define&t;  DBCR_TDE&t;0x01000000&t;/* TRAP Debug Event */
DECL|macro|DBCR_FER
mdefine_line|#define&t;  DBCR_FER&t;0x00F80000&t;/* First Events Remaining Mask */
DECL|macro|DBCR_FT
mdefine_line|#define&t;  DBCR_FT&t;0x00040000&t;/* Freeze Timers on Debug Event */
DECL|macro|DBCR_IA1
mdefine_line|#define&t;  DBCR_IA1&t;0x00020000&t;/* Instr. Addr. Compare 1 Enable */
DECL|macro|DBCR_IA2
mdefine_line|#define&t;  DBCR_IA2&t;0x00010000&t;/* Instr. Addr. Compare 2 Enable */
DECL|macro|DBCR_D1R
mdefine_line|#define&t;  DBCR_D1R&t;0x00008000&t;/* Data Addr. Compare 1 Read Enable */
DECL|macro|DBCR_D1W
mdefine_line|#define&t;  DBCR_D1W&t;0x00004000&t;/* Data Addr. Compare 1 Write Enable */
DECL|macro|DBCR_D1S
mdefine_line|#define&t;  DBCR_D1S(x)&t;(((x) &amp; 0x3) &lt;&lt; 12)&t;/* Data Adrr. Compare 1 Size */
DECL|macro|DAC_BYTE
mdefine_line|#define&t;    DAC_BYTE&t;0
DECL|macro|DAC_HALF
mdefine_line|#define&t;    DAC_HALF&t;1
DECL|macro|DAC_WORD
mdefine_line|#define&t;    DAC_WORD&t;2
DECL|macro|DAC_QUAD
mdefine_line|#define&t;    DAC_QUAD&t;3
DECL|macro|DBCR_D2R
mdefine_line|#define&t;  DBCR_D2R&t;0x00000800&t;/* Data Addr. Compare 2 Read Enable */
DECL|macro|DBCR_D2W
mdefine_line|#define&t;  DBCR_D2W&t;0x00000400&t;/* Data Addr. Compare 2 Write Enable */
DECL|macro|DBCR_D2S
mdefine_line|#define&t;  DBCR_D2S(x)&t;(((x) &amp; 0x3) &lt;&lt; 8)&t;/* Data Addr. Compare 2 Size */
DECL|macro|DBCR_SBT
mdefine_line|#define&t;  DBCR_SBT&t;0x00000040&t;/* Second Branch Taken Debug Event */
DECL|macro|DBCR_SED
mdefine_line|#define&t;  DBCR_SED&t;0x00000020&t;/* Second Exception Debug Event */
DECL|macro|DBCR_STD
mdefine_line|#define&t;  DBCR_STD&t;0x00000010&t;/* Second Trap Debug Event */
DECL|macro|DBCR_SIA
mdefine_line|#define&t;  DBCR_SIA&t;0x00000008&t;/* Second IAC Enable */
DECL|macro|DBCR_SDA
mdefine_line|#define&t;  DBCR_SDA&t;0x00000004&t;/* Second DAC Enable */
DECL|macro|DBCR_JOI
mdefine_line|#define&t;  DBCR_JOI&t;0x00000002&t;/* JTAG Serial Outbound Int. Enable */
DECL|macro|DBCR_JII
mdefine_line|#define&t;  DBCR_JII&t;0x00000001&t;/* JTAG Serial Inbound Int. Enable */
DECL|macro|SPRN_DBCR0
mdefine_line|#define&t;SPRN_DBCR0&t;0x3F2&t;/* Debug Control Register 0 */
DECL|macro|SPRN_DBCR1
mdefine_line|#define&t;SPRN_DBCR1&t;0x3BD&t;/* Debug Control Register 1 */
DECL|macro|SPRN_DBSR
mdefine_line|#define&t;SPRN_DBSR&t;0x3F0&t;/* Debug Status Register */
DECL|macro|SPRN_DCCR
mdefine_line|#define&t;SPRN_DCCR&t;0x3FA&t;/* Data Cache Cacheability Register */
DECL|macro|DCCR_NOCACHE
mdefine_line|#define&t;  DCCR_NOCACHE&t;&t;0&t;/* Noncacheable */
DECL|macro|DCCR_CACHE
mdefine_line|#define&t;  DCCR_CACHE&t;&t;1&t;/* Cacheable */
DECL|macro|SPRN_DCMP
mdefine_line|#define&t;SPRN_DCMP&t;0x3D1&t;/* Data TLB Compare Register */
DECL|macro|SPRN_DCWR
mdefine_line|#define&t;SPRN_DCWR&t;0x3BA&t;/* Data Cache Write-thru Register */
DECL|macro|DCWR_COPY
mdefine_line|#define&t;  DCWR_COPY&t;&t;0&t;/* Copy-back */
DECL|macro|DCWR_WRITE
mdefine_line|#define&t;  DCWR_WRITE&t;&t;1&t;/* Write-through */
DECL|macro|SPRN_DEAR
mdefine_line|#define&t;SPRN_DEAR&t;0x3D5&t;/* Data Error Address Register */
DECL|macro|SPRN_DEC
mdefine_line|#define&t;SPRN_DEC&t;0x016&t;/* Decrement Register */
DECL|macro|SPRN_DMISS
mdefine_line|#define&t;SPRN_DMISS&t;0x3D0&t;/* Data TLB Miss Register */
DECL|macro|SPRN_DSISR
mdefine_line|#define&t;SPRN_DSISR&t;0x012&t;/* Data Storage Interrupt Status Register */
DECL|macro|SPRN_EAR
mdefine_line|#define&t;SPRN_EAR&t;0x11A&t;/* External Address Register */
DECL|macro|SPRN_ESR
mdefine_line|#define&t;SPRN_ESR&t;0x3D4&t;/* Exception Syndrome Register */
DECL|macro|ESR_IMCP
mdefine_line|#define&t;  ESR_IMCP&t;0x80000000&t;/* Instr. Machine Check - Protection */
DECL|macro|ESR_IMCN
mdefine_line|#define&t;  ESR_IMCN&t;0x40000000&t;/* Instr. Machine Check - Non-config */
DECL|macro|ESR_IMCB
mdefine_line|#define&t;  ESR_IMCB&t;0x20000000&t;/* Instr. Machine Check - Bus error */
DECL|macro|ESR_IMCT
mdefine_line|#define&t;  ESR_IMCT&t;0x10000000&t;/* Instr. Machine Check - Timeout */
DECL|macro|ESR_PIL
mdefine_line|#define&t;  ESR_PIL&t;0x08000000&t;/* Program Exception - Illegal */
DECL|macro|ESR_PPR
mdefine_line|#define&t;  ESR_PPR&t;0x04000000&t;/* Program Exception - Priveleged */
DECL|macro|ESR_PTR
mdefine_line|#define&t;  ESR_PTR&t;0x02000000&t;/* Program Exception - Trap */
DECL|macro|ESR_DST
mdefine_line|#define&t;  ESR_DST&t;0x00800000&t;/* Storage Exception - Data miss */
DECL|macro|ESR_DIZ
mdefine_line|#define&t;  ESR_DIZ&t;0x00400000&t;/* Storage Exception - Zone fault */
DECL|macro|SPRN_EVPR
mdefine_line|#define&t;SPRN_EVPR&t;0x3D6&t;/* Exception Vector Prefix Register */
DECL|macro|SPRN_HASH1
mdefine_line|#define&t;SPRN_HASH1&t;0x3D2&t;/* Primary Hash Address Register */
DECL|macro|SPRN_HASH2
mdefine_line|#define&t;SPRN_HASH2&t;0x3D3&t;/* Secondary Hash Address Resgister */
DECL|macro|SPRN_HID0
mdefine_line|#define&t;SPRN_HID0&t;0x3F0&t;/* Hardware Implementation Register 0 */
DECL|macro|HID0_EMCP
mdefine_line|#define&t;  HID0_EMCP&t;(1&lt;&lt;31)&t;&t;/* Enable Machine Check pin */
DECL|macro|HID0_EBA
mdefine_line|#define&t;  HID0_EBA&t;(1&lt;&lt;29)&t;&t;/* Enable Bus Address Parity */
DECL|macro|HID0_EBD
mdefine_line|#define&t;  HID0_EBD&t;(1&lt;&lt;28)&t;&t;/* Enable Bus Data Parity */
DECL|macro|HID0_SBCLK
mdefine_line|#define&t;  HID0_SBCLK&t;(1&lt;&lt;27)
DECL|macro|HID0_EICE
mdefine_line|#define&t;  HID0_EICE&t;(1&lt;&lt;26)
DECL|macro|HID0_ECLK
mdefine_line|#define&t;  HID0_ECLK&t;(1&lt;&lt;25)
DECL|macro|HID0_PAR
mdefine_line|#define&t;  HID0_PAR&t;(1&lt;&lt;24)
DECL|macro|HID0_DOZE
mdefine_line|#define&t;  HID0_DOZE&t;(1&lt;&lt;23)
DECL|macro|HID0_NAP
mdefine_line|#define&t;  HID0_NAP&t;(1&lt;&lt;22)
DECL|macro|HID0_SLEEP
mdefine_line|#define&t;  HID0_SLEEP&t;(1&lt;&lt;21)
DECL|macro|HID0_DPM
mdefine_line|#define&t;  HID0_DPM&t;(1&lt;&lt;20)
DECL|macro|HID0_ICE
mdefine_line|#define&t;  HID0_ICE&t;(1&lt;&lt;15)&t;&t;/* Instruction Cache Enable */
DECL|macro|HID0_DCE
mdefine_line|#define&t;  HID0_DCE&t;(1&lt;&lt;14)&t;&t;/* Data Cache Enable */
DECL|macro|HID0_ILOCK
mdefine_line|#define&t;  HID0_ILOCK&t;(1&lt;&lt;13)&t;&t;/* Instruction Cache Lock */
DECL|macro|HID0_DLOCK
mdefine_line|#define&t;  HID0_DLOCK&t;(1&lt;&lt;12)&t;&t;/* Data Cache Lock */
DECL|macro|HID0_ICFI
mdefine_line|#define&t;  HID0_ICFI&t;(1&lt;&lt;11)&t;&t;/* Instr. Cache Flash Invalidate */
DECL|macro|HID0_DCI
mdefine_line|#define&t;  HID0_DCI&t;(1&lt;&lt;10)&t;&t;/* Data Cache Invalidate */
DECL|macro|HID0_SPD
mdefine_line|#define   HID0_SPD&t;(1&lt;&lt;9)&t;&t;/* Speculative disable */
DECL|macro|HID0_SGE
mdefine_line|#define   HID0_SGE&t;(1&lt;&lt;7)&t;&t;/* Store Gathering Enable */
DECL|macro|HID0_SIED
mdefine_line|#define&t;  HID0_SIED&t;(1&lt;&lt;7)&t;&t;/* Serial Instr. Execution [Disable] */
DECL|macro|HID0_BTIC
mdefine_line|#define   HID0_BTIC&t;(1&lt;&lt;5)&t;&t;/* Branch Target Instruction Cache Enable */
DECL|macro|HID0_ABE
mdefine_line|#define   HID0_ABE&t;(1&lt;&lt;3)&t;&t;/* Address Broadcast Enable */
DECL|macro|HID0_BHTE
mdefine_line|#define&t;  HID0_BHTE&t;(1&lt;&lt;2)&t;&t;/* Branch History Table Enable */
DECL|macro|HID0_BTCD
mdefine_line|#define&t;  HID0_BTCD&t;(1&lt;&lt;1)&t;&t;/* Branch target cache disable */
DECL|macro|SPRN_MSRDORM
mdefine_line|#define&t;SPRN_MSRDORM&t;0x3F1&t;/* Hardware Implementation Register 1 */
DECL|macro|SPRN_HID1
mdefine_line|#define SPRN_HID1&t;0x3F1&t;/* Hardware Implementation Register 1 */
DECL|macro|SPRN_IABR
mdefine_line|#define&t;SPRN_IABR&t;0x3F2&t;/* Instruction Address Breakpoint Register */
DECL|macro|SPRN_NIADORM
mdefine_line|#define&t;SPRN_NIADORM&t;0x3F3&t;/* Hardware Implementation Register 2 */
DECL|macro|SPRN_HID4
mdefine_line|#define SPRN_HID4&t;0x3F4&t;/* 970 HID4 */
DECL|macro|SPRN_HID5
mdefine_line|#define SPRN_HID5&t;0x3F6&t;/* 970 HID5 */
DECL|macro|SPRN_TSC
mdefine_line|#define&t;SPRN_TSC &t;0x3FD&t;/* Thread switch control */
DECL|macro|SPRN_TST
mdefine_line|#define&t;SPRN_TST &t;0x3FC&t;/* Thread switch timeout */
DECL|macro|SPRN_IAC1
mdefine_line|#define&t;SPRN_IAC1&t;0x3F4&t;/* Instruction Address Compare 1 */
DECL|macro|SPRN_IAC2
mdefine_line|#define&t;SPRN_IAC2&t;0x3F5&t;/* Instruction Address Compare 2 */
DECL|macro|SPRN_ICCR
mdefine_line|#define&t;SPRN_ICCR&t;0x3FB&t;/* Instruction Cache Cacheability Register */
DECL|macro|ICCR_NOCACHE
mdefine_line|#define&t;  ICCR_NOCACHE&t;&t;0&t;/* Noncacheable */
DECL|macro|ICCR_CACHE
mdefine_line|#define&t;  ICCR_CACHE&t;&t;1&t;/* Cacheable */
DECL|macro|SPRN_ICDBDR
mdefine_line|#define&t;SPRN_ICDBDR&t;0x3D3&t;/* Instruction Cache Debug Data Register */
DECL|macro|SPRN_ICMP
mdefine_line|#define&t;SPRN_ICMP&t;0x3D5&t;/* Instruction TLB Compare Register */
DECL|macro|SPRN_ICTC
mdefine_line|#define&t;SPRN_ICTC&t;0x3FB&t;/* Instruction Cache Throttling Control Reg */
DECL|macro|SPRN_IMISS
mdefine_line|#define&t;SPRN_IMISS&t;0x3D4&t;/* Instruction TLB Miss Register */
DECL|macro|SPRN_IMMR
mdefine_line|#define&t;SPRN_IMMR&t;0x27E  &t;/* Internal Memory Map Register */
DECL|macro|SPRN_L2CR
mdefine_line|#define&t;SPRN_L2CR&t;0x3F9&t;/* Level 2 Cache Control Regsiter */
DECL|macro|SPRN_LR
mdefine_line|#define&t;SPRN_LR&t;&t;0x008&t;/* Link Register */
DECL|macro|SPRN_PBL1
mdefine_line|#define&t;SPRN_PBL1&t;0x3FC&t;/* Protection Bound Lower 1 */
DECL|macro|SPRN_PBL2
mdefine_line|#define&t;SPRN_PBL2&t;0x3FE&t;/* Protection Bound Lower 2 */
DECL|macro|SPRN_PBU1
mdefine_line|#define&t;SPRN_PBU1&t;0x3FD&t;/* Protection Bound Upper 1 */
DECL|macro|SPRN_PBU2
mdefine_line|#define&t;SPRN_PBU2&t;0x3FF&t;/* Protection Bound Upper 2 */
DECL|macro|SPRN_PID
mdefine_line|#define&t;SPRN_PID&t;0x3B1&t;/* Process ID */
DECL|macro|SPRN_PIR
mdefine_line|#define&t;SPRN_PIR&t;0x3FF&t;/* Processor Identification Register */
DECL|macro|SPRN_PIT
mdefine_line|#define&t;SPRN_PIT&t;0x3DB&t;/* Programmable Interval Timer */
DECL|macro|SPRN_PURR
mdefine_line|#define&t;SPRN_PURR&t;0x135&t;/* Processor Utilization of Resources Register */
DECL|macro|SPRN_PVR
mdefine_line|#define&t;SPRN_PVR&t;0x11F&t;/* Processor Version Register */
DECL|macro|SPRN_RPA
mdefine_line|#define&t;SPRN_RPA&t;0x3D6&t;/* Required Physical Address Register */
DECL|macro|SPRN_SDA
mdefine_line|#define&t;SPRN_SDA&t;0x3BF&t;/* Sampled Data Address Register */
DECL|macro|SPRN_SDR1
mdefine_line|#define&t;SPRN_SDR1&t;0x019&t;/* MMU Hash Base Register */
DECL|macro|SPRN_SGR
mdefine_line|#define&t;SPRN_SGR&t;0x3B9&t;/* Storage Guarded Register */
DECL|macro|SGR_NORMAL
mdefine_line|#define&t;  SGR_NORMAL&t;&t;0
DECL|macro|SGR_GUARDED
mdefine_line|#define&t;  SGR_GUARDED&t;&t;1
DECL|macro|SPRN_SIA
mdefine_line|#define&t;SPRN_SIA&t;0x3BB&t;/* Sampled Instruction Address Register */
DECL|macro|SPRN_SPRG0
mdefine_line|#define&t;SPRN_SPRG0&t;0x110&t;/* Special Purpose Register General 0 */
DECL|macro|SPRN_SPRG1
mdefine_line|#define&t;SPRN_SPRG1&t;0x111&t;/* Special Purpose Register General 1 */
DECL|macro|SPRN_SPRG2
mdefine_line|#define&t;SPRN_SPRG2&t;0x112&t;/* Special Purpose Register General 2 */
DECL|macro|SPRN_SPRG3
mdefine_line|#define&t;SPRN_SPRG3&t;0x113&t;/* Special Purpose Register General 3 */
DECL|macro|SPRN_SRR0
mdefine_line|#define&t;SPRN_SRR0&t;0x01A&t;/* Save/Restore Register 0 */
DECL|macro|SPRN_SRR1
mdefine_line|#define&t;SPRN_SRR1&t;0x01B&t;/* Save/Restore Register 1 */
DECL|macro|SPRN_TBRL
mdefine_line|#define&t;SPRN_TBRL&t;0x10C&t;/* Time Base Read Lower Register (user, R/O) */
DECL|macro|SPRN_TBRU
mdefine_line|#define&t;SPRN_TBRU&t;0x10D&t;/* Time Base Read Upper Register (user, R/O) */
DECL|macro|SPRN_TBWL
mdefine_line|#define&t;SPRN_TBWL&t;0x11C&t;/* Time Base Lower Register (super, W/O) */
DECL|macro|SPRN_TBWU
mdefine_line|#define&t;SPRN_TBWU&t;0x11D&t;/* Time Base Write Upper Register (super, W/O) */
DECL|macro|SPRN_HIOR
mdefine_line|#define SPRN_HIOR&t;0x137&t;/* 970 Hypervisor interrupt offset */
DECL|macro|SPRN_TCR
mdefine_line|#define&t;SPRN_TCR&t;0x3DA&t;/* Timer Control Register */
DECL|macro|TCR_WP
mdefine_line|#define&t;  TCR_WP(x)&t;&t;(((x)&amp;0x3)&lt;&lt;30)&t;/* WDT Period */
DECL|macro|WP_2_17
mdefine_line|#define&t;    WP_2_17&t;&t;0&t;&t;/* 2^17 clocks */
DECL|macro|WP_2_21
mdefine_line|#define&t;    WP_2_21&t;&t;1&t;&t;/* 2^21 clocks */
DECL|macro|WP_2_25
mdefine_line|#define&t;    WP_2_25&t;&t;2&t;&t;/* 2^25 clocks */
DECL|macro|WP_2_29
mdefine_line|#define&t;    WP_2_29&t;&t;3&t;&t;/* 2^29 clocks */
DECL|macro|TCR_WRC
mdefine_line|#define&t;  TCR_WRC(x)&t;&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Control */
DECL|macro|WRC_NONE
mdefine_line|#define&t;    WRC_NONE&t;&t;0&t;&t;/* No reset will occur */
DECL|macro|WRC_CORE
mdefine_line|#define&t;    WRC_CORE&t;&t;1&t;&t;/* Core reset will occur */
DECL|macro|WRC_CHIP
mdefine_line|#define&t;    WRC_CHIP&t;&t;2&t;&t;/* Chip reset will occur */
DECL|macro|WRC_SYSTEM
mdefine_line|#define&t;    WRC_SYSTEM&t;&t;3&t;&t;/* System reset will occur */
DECL|macro|TCR_WIE
mdefine_line|#define&t;  TCR_WIE&t;&t;0x08000000&t;/* WDT Interrupt Enable */
DECL|macro|TCR_PIE
mdefine_line|#define&t;  TCR_PIE&t;&t;0x04000000&t;/* PIT Interrupt Enable */
DECL|macro|TCR_FP
mdefine_line|#define&t;  TCR_FP(x)&t;&t;(((x)&amp;0x3)&lt;&lt;24)&t;/* FIT Period */
DECL|macro|FP_2_9
mdefine_line|#define&t;    FP_2_9&t;&t;0&t;&t;/* 2^9 clocks */
DECL|macro|FP_2_13
mdefine_line|#define&t;    FP_2_13&t;&t;1&t;&t;/* 2^13 clocks */
DECL|macro|FP_2_17
mdefine_line|#define&t;    FP_2_17&t;&t;2&t;&t;/* 2^17 clocks */
DECL|macro|FP_2_21
mdefine_line|#define&t;    FP_2_21&t;&t;3&t;&t;/* 2^21 clocks */
DECL|macro|TCR_FIE
mdefine_line|#define&t;  TCR_FIE&t;&t;0x00800000&t;/* FIT Interrupt Enable */
DECL|macro|TCR_ARE
mdefine_line|#define&t;  TCR_ARE&t;&t;0x00400000&t;/* Auto Reload Enable */
DECL|macro|SPRN_THRM1
mdefine_line|#define&t;SPRN_THRM1&t;0x3FC&t;/* Thermal Management Register 1 */
DECL|macro|THRM1_TIN
mdefine_line|#define&t;  THRM1_TIN&t;&t;(1&lt;&lt;0)
DECL|macro|THRM1_TIV
mdefine_line|#define&t;  THRM1_TIV&t;&t;(1&lt;&lt;1)
DECL|macro|THRM1_THRES
mdefine_line|#define&t;  THRM1_THRES&t;&t;(0x7f&lt;&lt;2)
DECL|macro|THRM1_TID
mdefine_line|#define&t;  THRM1_TID&t;&t;(1&lt;&lt;29)
DECL|macro|THRM1_TIE
mdefine_line|#define&t;  THRM1_TIE&t;&t;(1&lt;&lt;30)
DECL|macro|THRM1_V
mdefine_line|#define&t;  THRM1_V&t;&t;(1&lt;&lt;31)
DECL|macro|SPRN_THRM2
mdefine_line|#define&t;SPRN_THRM2&t;0x3FD&t;/* Thermal Management Register 2 */
DECL|macro|SPRN_THRM3
mdefine_line|#define&t;SPRN_THRM3&t;0x3FE&t;/* Thermal Management Register 3 */
DECL|macro|THRM3_E
mdefine_line|#define&t;  THRM3_E&t;&t;(1&lt;&lt;31)
DECL|macro|SPRN_TSR
mdefine_line|#define&t;SPRN_TSR&t;0x3D8&t;/* Timer Status Register */
DECL|macro|TSR_ENW
mdefine_line|#define&t;  TSR_ENW&t;&t;0x80000000&t;/* Enable Next Watchdog */
DECL|macro|TSR_WIS
mdefine_line|#define&t;  TSR_WIS&t;&t;0x40000000&t;/* WDT Interrupt Status */
DECL|macro|TSR_WRS
mdefine_line|#define&t;  TSR_WRS(x)&t;&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Status */
DECL|macro|WRS_NONE
mdefine_line|#define&t;    WRS_NONE&t;&t;0&t;&t;/* No WDT reset occurred */
DECL|macro|WRS_CORE
mdefine_line|#define&t;    WRS_CORE&t;&t;1&t;&t;/* WDT forced core reset */
DECL|macro|WRS_CHIP
mdefine_line|#define&t;    WRS_CHIP&t;&t;2&t;&t;/* WDT forced chip reset */
DECL|macro|WRS_SYSTEM
mdefine_line|#define&t;    WRS_SYSTEM&t;&t;3&t;&t;/* WDT forced system reset */
DECL|macro|TSR_PIS
mdefine_line|#define&t;  TSR_PIS&t;&t;0x08000000&t;/* PIT Interrupt Status */
DECL|macro|TSR_FIS
mdefine_line|#define&t;  TSR_FIS&t;&t;0x04000000&t;/* FIT Interrupt Status */
DECL|macro|SPRN_USIA
mdefine_line|#define&t;SPRN_USIA&t;0x3AB&t;/* User Sampled Instruction Address Register */
DECL|macro|SPRN_XER
mdefine_line|#define&t;SPRN_XER&t;0x001&t;/* Fixed Point Exception Register */
DECL|macro|SPRN_ZPR
mdefine_line|#define&t;SPRN_ZPR&t;0x3B0&t;/* Zone Protection Register */
DECL|macro|SPRN_VRSAVE
mdefine_line|#define SPRN_VRSAVE     0x100   /* Vector save */
multiline_comment|/* Performance monitor SPRs */
DECL|macro|SPRN_SIAR
mdefine_line|#define SPRN_SIAR&t;780
DECL|macro|SPRN_SDAR
mdefine_line|#define SPRN_SDAR&t;781
DECL|macro|SPRN_MMCRA
mdefine_line|#define SPRN_MMCRA&t;786
DECL|macro|MMCRA_SIHV
mdefine_line|#define   MMCRA_SIHV&t;0x10000000UL /* state of MSR HV when SIAR set */
DECL|macro|MMCRA_SIPR
mdefine_line|#define   MMCRA_SIPR&t;0x08000000UL /* state of MSR PR when SIAR set */
DECL|macro|MMCRA_SAMPLE_ENABLE
mdefine_line|#define   MMCRA_SAMPLE_ENABLE 0x00000001UL /* enable sampling */
DECL|macro|SPRN_PMC1
mdefine_line|#define SPRN_PMC1&t;787
DECL|macro|SPRN_PMC2
mdefine_line|#define SPRN_PMC2&t;788
DECL|macro|SPRN_PMC3
mdefine_line|#define SPRN_PMC3&t;789
DECL|macro|SPRN_PMC4
mdefine_line|#define SPRN_PMC4&t;790
DECL|macro|SPRN_PMC5
mdefine_line|#define SPRN_PMC5&t;791
DECL|macro|SPRN_PMC6
mdefine_line|#define SPRN_PMC6&t;792
DECL|macro|SPRN_PMC7
mdefine_line|#define SPRN_PMC7&t;793
DECL|macro|SPRN_PMC8
mdefine_line|#define SPRN_PMC8&t;794
DECL|macro|SPRN_MMCR0
mdefine_line|#define SPRN_MMCR0&t;795
DECL|macro|MMCR0_FC
mdefine_line|#define   MMCR0_FC&t;0x80000000UL /* freeze counters. set to 1 on a perfmon exception */
DECL|macro|MMCR0_FCS
mdefine_line|#define   MMCR0_FCS&t;0x40000000UL /* freeze in supervisor state */
DECL|macro|MMCR0_KERNEL_DISABLE
mdefine_line|#define   MMCR0_KERNEL_DISABLE MMCR0_FCS
DECL|macro|MMCR0_FCP
mdefine_line|#define   MMCR0_FCP&t;0x20000000UL /* freeze in problem state */
DECL|macro|MMCR0_PROBLEM_DISABLE
mdefine_line|#define   MMCR0_PROBLEM_DISABLE MMCR0_FCP
DECL|macro|MMCR0_FCM1
mdefine_line|#define   MMCR0_FCM1&t;0x10000000UL /* freeze counters while MSR mark = 1 */
DECL|macro|MMCR0_FCM0
mdefine_line|#define   MMCR0_FCM0&t;0x08000000UL /* freeze counters while MSR mark = 0 */
DECL|macro|MMCR0_PMXE
mdefine_line|#define   MMCR0_PMXE&t;0x04000000UL /* performance monitor exception enable */
DECL|macro|MMCR0_FCECE
mdefine_line|#define   MMCR0_FCECE&t;0x02000000UL /* freeze counters on enabled condition or event */
multiline_comment|/* time base exception enable */
DECL|macro|MMCR0_TBEE
mdefine_line|#define   MMCR0_TBEE&t;0x00400000UL /* time base exception enable */
DECL|macro|MMCR0_PMC1CE
mdefine_line|#define   MMCR0_PMC1CE&t;0x00008000UL /* PMC1 count enable*/
DECL|macro|MMCR0_PMCjCE
mdefine_line|#define   MMCR0_PMCjCE&t;0x00004000UL /* PMCj count enable*/
DECL|macro|MMCR0_TRIGGER
mdefine_line|#define   MMCR0_TRIGGER&t;0x00002000UL /* TRIGGER enable */
DECL|macro|MMCR0_PMAO
mdefine_line|#define   MMCR0_PMAO&t;0x00000080UL /* performance monitor alert has occurred, set to 0 after handling exception */
DECL|macro|MMCR0_SHRFC
mdefine_line|#define   MMCR0_SHRFC&t;0x00000040UL /* SHRre freeze conditions between threads */
DECL|macro|MMCR0_FCTI
mdefine_line|#define   MMCR0_FCTI&t;0x00000008UL /* freeze counters in tags inactive mode */
DECL|macro|MMCR0_FCTA
mdefine_line|#define   MMCR0_FCTA&t;0x00000004UL /* freeze counters in tags active mode */
DECL|macro|MMCR0_FCWAIT
mdefine_line|#define   MMCR0_FCWAIT&t;0x00000002UL /* freeze counter in WAIT state */
DECL|macro|MMCR0_FCHV
mdefine_line|#define   MMCR0_FCHV&t;0x00000001UL /* freeze conditions in hypervisor mode */
DECL|macro|SPRN_MMCR1
mdefine_line|#define SPRN_MMCR1&t;798
multiline_comment|/* Short-hand versions for a number of the above SPRNs */
DECL|macro|CTR
mdefine_line|#define&t;CTR&t;SPRN_CTR&t;/* Counter Register */
DECL|macro|DAR
mdefine_line|#define&t;DAR&t;SPRN_DAR&t;/* Data Address Register */
DECL|macro|DABR
mdefine_line|#define&t;DABR&t;SPRN_DABR&t;/* Data Address Breakpoint Register */
DECL|macro|DCMP
mdefine_line|#define&t;DCMP&t;SPRN_DCMP      &t;/* Data TLB Compare Register */
DECL|macro|DEC
mdefine_line|#define&t;DEC&t;SPRN_DEC       &t;/* Decrement Register */
DECL|macro|DMISS
mdefine_line|#define&t;DMISS&t;SPRN_DMISS     &t;/* Data TLB Miss Register */
DECL|macro|DSISR
mdefine_line|#define&t;DSISR&t;SPRN_DSISR&t;/* Data Storage Interrupt Status Register */
DECL|macro|EAR
mdefine_line|#define&t;EAR&t;SPRN_EAR       &t;/* External Address Register */
DECL|macro|HASH1
mdefine_line|#define&t;HASH1&t;SPRN_HASH1&t;/* Primary Hash Address Register */
DECL|macro|HASH2
mdefine_line|#define&t;HASH2&t;SPRN_HASH2&t;/* Secondary Hash Address Register */
DECL|macro|HID0
mdefine_line|#define&t;HID0&t;SPRN_HID0&t;/* Hardware Implementation Register 0 */
DECL|macro|MSRDORM
mdefine_line|#define&t;MSRDORM&t;SPRN_MSRDORM&t;/* MSR Dormant Register */
DECL|macro|NIADORM
mdefine_line|#define&t;NIADORM&t;SPRN_NIADORM&t;/* NIA Dormant Register */
DECL|macro|TSC
mdefine_line|#define&t;TSC    &t;SPRN_TSC &t;/* Thread switch control */
DECL|macro|TST
mdefine_line|#define&t;TST    &t;SPRN_TST &t;/* Thread switch timeout */
DECL|macro|IABR
mdefine_line|#define&t;IABR&t;SPRN_IABR      &t;/* Instruction Address Breakpoint Register */
DECL|macro|ICMP
mdefine_line|#define&t;ICMP&t;SPRN_ICMP&t;/* Instruction TLB Compare Register */
DECL|macro|IMISS
mdefine_line|#define&t;IMISS&t;SPRN_IMISS&t;/* Instruction TLB Miss Register */
DECL|macro|IMMR
mdefine_line|#define&t;IMMR&t;SPRN_IMMR      &t;/* PPC 860/821 Internal Memory Map Register */
DECL|macro|L2CR
mdefine_line|#define&t;L2CR&t;SPRN_L2CR    &t;/* PPC 750 L2 control register */
DECL|macro|__LR
mdefine_line|#define&t;__LR&t;SPRN_LR
DECL|macro|PVR
mdefine_line|#define&t;PVR&t;SPRN_PVR&t;/* Processor Version */
DECL|macro|PIR
mdefine_line|#define&t;PIR&t;SPRN_PIR&t;/* Processor ID */
DECL|macro|PURR
mdefine_line|#define&t;PURR&t;SPRN_PURR&t;/* Processor Utilization of Resource Register */
singleline_comment|//#define&t;RPA&t;SPRN_RPA&t;/* Required Physical Address Register */
DECL|macro|SDR1
mdefine_line|#define&t;SDR1&t;SPRN_SDR1      &t;/* MMU hash base register */
DECL|macro|SPR0
mdefine_line|#define&t;SPR0&t;SPRN_SPRG0&t;/* Supervisor Private Registers */
DECL|macro|SPR1
mdefine_line|#define&t;SPR1&t;SPRN_SPRG1
DECL|macro|SPR2
mdefine_line|#define&t;SPR2&t;SPRN_SPRG2
DECL|macro|SPR3
mdefine_line|#define&t;SPR3&t;SPRN_SPRG3
DECL|macro|SPRG0
mdefine_line|#define&t;SPRG0   SPRN_SPRG0
DECL|macro|SPRG1
mdefine_line|#define&t;SPRG1   SPRN_SPRG1
DECL|macro|SPRG2
mdefine_line|#define&t;SPRG2   SPRN_SPRG2
DECL|macro|SPRG3
mdefine_line|#define&t;SPRG3   SPRN_SPRG3
DECL|macro|SRR0
mdefine_line|#define&t;SRR0&t;SPRN_SRR0&t;/* Save and Restore Register 0 */
DECL|macro|SRR1
mdefine_line|#define&t;SRR1&t;SPRN_SRR1&t;/* Save and Restore Register 1 */
DECL|macro|TBRL
mdefine_line|#define&t;TBRL&t;SPRN_TBRL&t;/* Time Base Read Lower Register */
DECL|macro|TBRU
mdefine_line|#define&t;TBRU&t;SPRN_TBRU&t;/* Time Base Read Upper Register */
DECL|macro|TBWL
mdefine_line|#define&t;TBWL&t;SPRN_TBWL&t;/* Time Base Write Lower Register */
DECL|macro|TBWU
mdefine_line|#define&t;TBWU&t;SPRN_TBWU&t;/* Time Base Write Upper Register */
DECL|macro|ICTC
mdefine_line|#define ICTC&t;1019
DECL|macro|THRM1
mdefine_line|#define&t;THRM1&t;SPRN_THRM1&t;/* Thermal Management Register 1 */
DECL|macro|THRM2
mdefine_line|#define&t;THRM2&t;SPRN_THRM2&t;/* Thermal Management Register 2 */
DECL|macro|THRM3
mdefine_line|#define&t;THRM3&t;SPRN_THRM3&t;/* Thermal Management Register 3 */
DECL|macro|XER
mdefine_line|#define&t;XER&t;SPRN_XER
multiline_comment|/* Processor Version Register (PVR) field extraction */
DECL|macro|PVR_VER
mdefine_line|#define&t;PVR_VER(pvr)  (((pvr) &gt;&gt;  16) &amp; 0xFFFF)&t;/* Version field */
DECL|macro|PVR_REV
mdefine_line|#define&t;PVR_REV(pvr)  (((pvr) &gt;&gt;   0) &amp; 0xFFFF)&t;/* Revison field */
multiline_comment|/* Processor Version Numbers */
DECL|macro|PV_NORTHSTAR
mdefine_line|#define&t;PV_NORTHSTAR&t;0x0033
DECL|macro|PV_PULSAR
mdefine_line|#define&t;PV_PULSAR&t;0x0034
DECL|macro|PV_POWER4
mdefine_line|#define&t;PV_POWER4&t;0x0035
DECL|macro|PV_ICESTAR
mdefine_line|#define&t;PV_ICESTAR&t;0x0036
DECL|macro|PV_SSTAR
mdefine_line|#define&t;PV_SSTAR&t;0x0037
DECL|macro|PV_POWER4p
mdefine_line|#define&t;PV_POWER4p&t;0x0038
DECL|macro|PV_970
mdefine_line|#define PV_970&t;&t;0x0039
DECL|macro|PV_POWER5
mdefine_line|#define&t;PV_POWER5&t;0x003A
DECL|macro|PV_POWER5p
mdefine_line|#define PV_POWER5p&t;0x003B
DECL|macro|PV_970FX
mdefine_line|#define PV_970FX&t;0x003C
DECL|macro|PV_630
mdefine_line|#define&t;PV_630        &t;0x0040
DECL|macro|PV_630p
mdefine_line|#define&t;PV_630p&t;        0x0041
multiline_comment|/* Platforms supported by PPC64 */
DECL|macro|PLATFORM_PSERIES
mdefine_line|#define PLATFORM_PSERIES      0x0100
DECL|macro|PLATFORM_PSERIES_LPAR
mdefine_line|#define PLATFORM_PSERIES_LPAR 0x0101
DECL|macro|PLATFORM_ISERIES_LPAR
mdefine_line|#define PLATFORM_ISERIES_LPAR 0x0201
DECL|macro|PLATFORM_LPAR
mdefine_line|#define PLATFORM_LPAR         0x0001
DECL|macro|PLATFORM_POWERMAC
mdefine_line|#define PLATFORM_POWERMAC     0x0400
DECL|macro|PLATFORM_MAPLE
mdefine_line|#define PLATFORM_MAPLE        0x0500
multiline_comment|/* Compatibility with drivers coming from PPC32 world */
DECL|macro|_machine
mdefine_line|#define _machine&t;(systemcfg-&gt;platform)
DECL|macro|_MACH_Pmac
mdefine_line|#define _MACH_Pmac&t;PLATFORM_POWERMAC
multiline_comment|/*&n; * List of interrupt controllers.&n; */
DECL|macro|IC_INVALID
mdefine_line|#define IC_INVALID    0
DECL|macro|IC_OPEN_PIC
mdefine_line|#define IC_OPEN_PIC   1
DECL|macro|IC_PPC_XIC
mdefine_line|#define IC_PPC_XIC    2
DECL|macro|XGLUE
mdefine_line|#define XGLUE(a,b) a##b
DECL|macro|GLUE
mdefine_line|#define GLUE(a,b) XGLUE(a,b)
multiline_comment|/* iSeries CTRL register (for runlatch) */
DECL|macro|CTRLT
mdefine_line|#define CTRLT&t;&t;0x098
DECL|macro|CTRLF
mdefine_line|#define CTRLF&t;&t;0x088
DECL|macro|RUNLATCH
mdefine_line|#define RUNLATCH&t;0x0001
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_GLOBAL
mdefine_line|#define _GLOBAL(name) &bslash;&n;&t;.section &quot;.text&quot;; &bslash;&n;&t;.align 2 ; &bslash;&n;&t;.globl name; &bslash;&n;&t;.globl GLUE(.,name); &bslash;&n;&t;.section &quot;.opd&quot;,&quot;aw&quot;; &bslash;&n;name: &bslash;&n;&t;.quad GLUE(.,name); &bslash;&n;&t;.quad .TOC.@tocbase; &bslash;&n;&t;.quad 0; &bslash;&n;&t;.previous; &bslash;&n;&t;.type GLUE(.,name),@function; &bslash;&n;GLUE(.,name):
DECL|macro|_STATIC
mdefine_line|#define _STATIC(name) &bslash;&n;&t;.section &quot;.text&quot;; &bslash;&n;&t;.align 2 ; &bslash;&n;&t;.section &quot;.opd&quot;,&quot;aw&quot;; &bslash;&n;name: &bslash;&n;&t;.quad GLUE(.,name); &bslash;&n;&t;.quad .TOC.@tocbase; &bslash;&n;&t;.quad 0; &bslash;&n;&t;.previous; &bslash;&n;&t;.type GLUE(.,name),@function; &bslash;&n;GLUE(.,name):
macro_line|#else /* __ASSEMBLY__ */
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() ({ __label__ _l; _l: &amp;&amp;_l;})
multiline_comment|/* Macros for setting and retrieving special purpose registers */
DECL|macro|mfmsr
mdefine_line|#define mfmsr()&t;&t;({unsigned long rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfmsr %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|macro|__mtmsrd
mdefine_line|#define __mtmsrd(v, l)&t;asm volatile(&quot;mtmsrd %0,&quot; __stringify(l) &bslash;&n;&t;&t;&t;&t;     : : &quot;r&quot; (v))
DECL|macro|mtmsrd
mdefine_line|#define mtmsrd(v)&t;__mtmsrd((v), 0)
DECL|macro|mfspr
mdefine_line|#define mfspr(rn)&t;({unsigned long rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfspr %0,&quot; __stringify(rn) &bslash;&n;&t;&t;&t;&t;     : &quot;=r&quot; (rval)); rval;})
DECL|macro|mtspr
mdefine_line|#define mtspr(rn, v)&t;asm volatile(&quot;mtspr &quot; __stringify(rn) &quot;,%0&quot; : : &quot;r&quot; (v))
DECL|macro|mftb
mdefine_line|#define mftb()&t;&t;({unsigned long rval;&t;&bslash;&n;&t;&t;&t;asm volatile(&quot;mftb %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|macro|mttbl
mdefine_line|#define mttbl(v)&t;asm volatile(&quot;mttbl %0&quot;:: &quot;r&quot;(v))
DECL|macro|mttbu
mdefine_line|#define mttbu(v)&t;asm volatile(&quot;mttbu %0&quot;:: &quot;r&quot;(v))
DECL|macro|mfasr
mdefine_line|#define mfasr()&t;&t;({unsigned long rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfasr %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|function|set_tb
r_static
r_inline
r_void
id|set_tb
c_func
(paren
r_int
r_int
id|upper
comma
r_int
r_int
id|lower
)paren
(brace
id|mttbl
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|mttbu
c_func
(paren
id|upper
)paren
suffix:semicolon
id|mttbl
c_func
(paren
id|lower
)paren
suffix:semicolon
)brace
DECL|macro|__get_SP
mdefine_line|#define __get_SP()&t;({unsigned long sp; &bslash;&n;&t;&t;&t;asm volatile(&quot;mr %0,1&quot;: &quot;=r&quot; (sp)); sp;})
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|have_of
suffix:semicolon
r_extern
id|u64
id|ppc64_interrupt_controller
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fdptr
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
r_extern
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/* Create a new kernel thread. */
r_extern
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_altivec
suffix:semicolon
multiline_comment|/* 64-bit user address space is 41-bits (2TBs user VM) */
DECL|macro|TASK_SIZE_USER64
mdefine_line|#define TASK_SIZE_USER64 (0x0000020000000000UL)
multiline_comment|/* &n; * 32-bit user address space is 4GB - 1 page &n; * (this 1 page is needed so referencing of 0xFFFFFFFF generates EFAULT&n; */
DECL|macro|TASK_SIZE_USER32
mdefine_line|#define TASK_SIZE_USER32 (0x0000000100000000UL - (1*PAGE_SIZE))
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE (test_thread_flag(TIF_32BIT) ? &bslash;&n;&t;&t;TASK_SIZE_USER32 : TASK_SIZE_USER64)
multiline_comment|/* We can&squot;t actually tell the TASK_SIZE given just the mm, but default&n; * to the 64-bit case to make sure that enough gets cleaned up. */
DECL|macro|MM_VM_SIZE
mdefine_line|#define MM_VM_SIZE(mm)&t;TASK_SIZE_USER64
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE_USER32
mdefine_line|#define TASK_UNMAPPED_BASE_USER32 (PAGE_ALIGN(STACK_TOP_USER32 / 4))
DECL|macro|TASK_UNMAPPED_BASE_USER64
mdefine_line|#define TASK_UNMAPPED_BASE_USER64 (PAGE_ALIGN(STACK_TOP_USER64 / 4))
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE ((test_thread_flag(TIF_32BIT)||(ppcdebugset(PPCDBG_BINFMT_32ADDR))) ? &bslash;&n;&t;&t;TASK_UNMAPPED_BASE_USER32 : TASK_UNMAPPED_BASE_USER64 )
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* Kernel stack pointer */
DECL|member|ksp_vsid
r_int
r_int
id|ksp_vsid
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* Pointer to saved register state */
DECL|member|fs
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/* for get_fs() validation */
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* Floating point status (plus pad) */
DECL|member|fpexc_mode
r_int
r_int
id|fpexc_mode
suffix:semicolon
multiline_comment|/* Floating-point exception mode */
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* was saved_msr, saved_softe */
macro_line|#ifdef CONFIG_ALTIVEC
multiline_comment|/* Complete AltiVec register set */
id|vector128
id|vr
(braket
l_int|32
)braket
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* AltiVec status */
id|vector128
id|vscr
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|member|vrsave
r_int
r_int
id|vrsave
suffix:semicolon
DECL|member|used_vr
r_int
id|used_vr
suffix:semicolon
multiline_comment|/* set if process has used altivec */
macro_line|#endif /* CONFIG_ALTIVEC */
)brace
suffix:semicolon
DECL|macro|ARCH_MIN_TASKALIGN
mdefine_line|#define ARCH_MIN_TASKALIGN 16
DECL|macro|INIT_SP
mdefine_line|#define INIT_SP&t;&t;(sizeof(init_stack) + (unsigned long) &amp;init_stack)
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD  { &bslash;&n;&t;.ksp = INIT_SP, &bslash;&n;&t;.regs = (struct pt_regs *)INIT_SP - 1, &bslash;&n;&t;.fs = KERNEL_DS, &bslash;&n;&t;.fpr = {0}, &bslash;&n;&t;.fpscr = 0, &bslash;&n;&t;.fpexc_mode = MSR_FE0|MSR_FE1, &bslash;&n;}
multiline_comment|/*&n; * Note: the vm_start and vm_end fields here should *not*&n; * be in kernel space.  (Could vm_end == vm_start perhaps?)&n; */
DECL|macro|IOREMAP_MMAP
mdefine_line|#define IOREMAP_MMAP { &amp;ioremap_mm, 0, 0x1000, NULL, &bslash;&n;&t;&t;    PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, &bslash;&n;&t;&t;    1, NULL, NULL }
r_extern
r_struct
id|mm_struct
id|ioremap_mm
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread. For now, this is the &quot;user&quot; PC&n; */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(tsk)    &bslash;&n;        ((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)  ((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;nip: 0)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.regs? (tsk)-&gt;thread.regs-&gt;gpr[1]: 0)
multiline_comment|/* Get/set floating-point exception mode */
DECL|macro|GET_FPEXC_CTL
mdefine_line|#define GET_FPEXC_CTL(tsk, adr) get_fpexc_mode((tsk), (adr))
DECL|macro|SET_FPEXC_CTL
mdefine_line|#define SET_FPEXC_CTL(tsk, val) set_fpexc_mode((tsk), (val))
r_extern
r_int
id|get_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|adr
)paren
suffix:semicolon
r_extern
r_int
id|set_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|__unpack_fe01
r_static
r_inline
r_int
r_int
id|__unpack_fe01
c_func
(paren
r_int
r_int
id|msr_bits
)paren
(brace
r_return
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE0
)paren
op_rshift
l_int|10
)paren
op_or
(paren
(paren
id|msr_bits
op_amp
id|MSR_FE1
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|__pack_fe01
r_static
r_inline
r_int
r_int
id|__pack_fe01
c_func
(paren
r_int
r_int
id|fpmode
)paren
(brace
r_return
(paren
(paren
id|fpmode
op_lshift
l_int|10
)paren
op_amp
id|MSR_FE0
)paren
op_or
(paren
(paren
id|fpmode
op_lshift
l_int|8
)paren
op_amp
id|MSR_FE1
)paren
suffix:semicolon
)brace
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()&t;do { HMT_low(); HMT_medium(); barrier(); } while (0)
multiline_comment|/*&n; * Prefetch macros.&n; */
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|function|prefetch
r_static
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbt 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|function|prefetchw
r_static
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;dcbtst 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x)&t;prefetchw(x)
DECL|macro|HAVE_ARCH_PICK_MMAP_LAYOUT
mdefine_line|#define HAVE_ARCH_PICK_MMAP_LAYOUT
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Number of entries in the SLB. If this ever changes we should handle&n; * it with a use a cpu feature fixup.&n; */
DECL|macro|SLB_NUM_ENTRIES
mdefine_line|#define SLB_NUM_ENTRIES 64
macro_line|#endif /* __ASM_PPC64_PROCESSOR_H */
eof
