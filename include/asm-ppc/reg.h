multiline_comment|/*&n; * Contains the definition of registers common to all PowerPC variants.&n; * If a register definition has been changed in a different PowerPC&n; * variant, we will case it in #ifndef XXX ... #endif, and have the&n; * number used in the Programming Environments Manual For 32-Bit&n; * Implementations of the PowerPC Architecture (a.k.a. Green Book) here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_REGS_H__
DECL|macro|__ASM_PPC_REGS_H__
mdefine_line|#define __ASM_PPC_REGS_H__
macro_line|#include &lt;linux/stringify.h&gt;
multiline_comment|/* Pickup Book E specific registers. */
macro_line|#if defined(CONFIG_BOOKE) || defined(CONFIG_40x)
macro_line|#include &lt;asm/reg_booke.h&gt;
macro_line|#endif
multiline_comment|/* Machine State Register (MSR) Fields */
DECL|macro|MSR_SF
mdefine_line|#define MSR_SF&t;&t;(1&lt;&lt;63)
DECL|macro|MSR_ISF
mdefine_line|#define MSR_ISF&t;&t;(1&lt;&lt;61)
DECL|macro|MSR_VEC
mdefine_line|#define MSR_VEC&t;&t;(1&lt;&lt;25)&t;&t;/* Enable AltiVec */
DECL|macro|MSR_POW
mdefine_line|#define MSR_POW&t;&t;(1&lt;&lt;18)&t;&t;/* Enable Power Management */
DECL|macro|MSR_WE
mdefine_line|#define MSR_WE&t;&t;(1&lt;&lt;18)&t;&t;/* Wait State Enable */
DECL|macro|MSR_TGPR
mdefine_line|#define MSR_TGPR&t;(1&lt;&lt;17)&t;&t;/* TLB Update registers in use */
DECL|macro|MSR_CE
mdefine_line|#define MSR_CE&t;&t;(1&lt;&lt;17)&t;&t;/* Critical Interrupt Enable */
DECL|macro|MSR_ILE
mdefine_line|#define MSR_ILE&t;&t;(1&lt;&lt;16)&t;&t;/* Interrupt Little Endian */
DECL|macro|MSR_EE
mdefine_line|#define MSR_EE&t;&t;(1&lt;&lt;15)&t;&t;/* External Interrupt Enable */
DECL|macro|MSR_PR
mdefine_line|#define MSR_PR&t;&t;(1&lt;&lt;14)&t;&t;/* Problem State / Privilege Level */
DECL|macro|MSR_FP
mdefine_line|#define MSR_FP&t;&t;(1&lt;&lt;13)&t;&t;/* Floating Point enable */
DECL|macro|MSR_ME
mdefine_line|#define MSR_ME&t;&t;(1&lt;&lt;12)&t;&t;/* Machine Check Enable */
DECL|macro|MSR_FE0
mdefine_line|#define MSR_FE0&t;&t;(1&lt;&lt;11)&t;&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE
mdefine_line|#define MSR_SE&t;&t;(1&lt;&lt;10)&t;&t;/* Single Step */
DECL|macro|MSR_BE
mdefine_line|#define MSR_BE&t;&t;(1&lt;&lt;9)&t;&t;/* Branch Trace */
DECL|macro|MSR_DE
mdefine_line|#define MSR_DE&t;&t;(1&lt;&lt;9)&t;&t;/* Debug Exception Enable */
DECL|macro|MSR_FE1
mdefine_line|#define MSR_FE1&t;&t;(1&lt;&lt;8)&t;&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP
mdefine_line|#define MSR_IP&t;&t;(1&lt;&lt;6)&t;&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR
mdefine_line|#define MSR_IR&t;&t;(1&lt;&lt;5)&t;&t;/* Instruction Relocate */
DECL|macro|MSR_DR
mdefine_line|#define MSR_DR&t;&t;(1&lt;&lt;4)&t;&t;/* Data Relocate */
DECL|macro|MSR_PE
mdefine_line|#define MSR_PE&t;&t;(1&lt;&lt;3)&t;&t;/* Protection Enable */
DECL|macro|MSR_PX
mdefine_line|#define MSR_PX&t;&t;(1&lt;&lt;2)&t;&t;/* Protection Exclusive Mode */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;(1&lt;&lt;1)&t;&t;/* Recoverable Exception */
DECL|macro|MSR_LE
mdefine_line|#define MSR_LE&t;&t;(1&lt;&lt;0)&t;&t;/* Little Endian */
multiline_comment|/* Default MSR for kernel mode. */
macro_line|#ifdef CONFIG_APUS_FAST_EXCEPT
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL&t;(MSR_ME|MSR_IP|MSR_RI|MSR_IR|MSR_DR)
macro_line|#endif
macro_line|#ifndef MSR_KERNEL
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL&t;(MSR_ME|MSR_RI|MSR_IR|MSR_DR)
macro_line|#endif
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;(MSR_KERNEL|MSR_PR|MSR_EE)
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
mdefine_line|#define FPSCR_ZX&t;0x04000000&t;/* Zero-devide exception summary */
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
DECL|macro|SPRN_CTR
mdefine_line|#define SPRN_CTR&t;0x009&t;/* Count Register */
DECL|macro|SPRN_DABR
mdefine_line|#define SPRN_DABR&t;0x3F5&t;/* Data Address Breakpoint Register */
DECL|macro|SPRN_DAR
mdefine_line|#define SPRN_DAR&t;0x013&t;/* Data Address Register */
DECL|macro|SPRN_TBRL
mdefine_line|#define SPRN_TBRL&t;0x10C&t;/* Time Base Read Lower Register (user, R/O) */
DECL|macro|SPRN_TBRU
mdefine_line|#define SPRN_TBRU&t;0x10D&t;/* Time Base Read Upper Register (user, R/O) */
DECL|macro|SPRN_TBWL
mdefine_line|#define SPRN_TBWL&t;0x11C&t;/* Time Base Lower Register (super, R/W) */
DECL|macro|SPRN_TBWU
mdefine_line|#define SPRN_TBWU&t;0x11D&t;/* Time Base Upper Register (super, R/W) */
DECL|macro|SPRN_HIOR
mdefine_line|#define SPRN_HIOR&t;0x137&t;/* 970 Hypervisor interrupt offset */
DECL|macro|SPRN_DBAT0L
mdefine_line|#define SPRN_DBAT0L&t;0x219&t;/* Data BAT 0 Lower Register */
DECL|macro|SPRN_DBAT0U
mdefine_line|#define SPRN_DBAT0U&t;0x218&t;/* Data BAT 0 Upper Register */
DECL|macro|SPRN_DBAT1L
mdefine_line|#define SPRN_DBAT1L&t;0x21B&t;/* Data BAT 1 Lower Register */
DECL|macro|SPRN_DBAT1U
mdefine_line|#define SPRN_DBAT1U&t;0x21A&t;/* Data BAT 1 Upper Register */
DECL|macro|SPRN_DBAT2L
mdefine_line|#define SPRN_DBAT2L&t;0x21D&t;/* Data BAT 2 Lower Register */
DECL|macro|SPRN_DBAT2U
mdefine_line|#define SPRN_DBAT2U&t;0x21C&t;/* Data BAT 2 Upper Register */
DECL|macro|SPRN_DBAT3L
mdefine_line|#define SPRN_DBAT3L&t;0x21F&t;/* Data BAT 3 Lower Register */
DECL|macro|SPRN_DBAT3U
mdefine_line|#define SPRN_DBAT3U&t;0x21E&t;/* Data BAT 3 Upper Register */
DECL|macro|SPRN_DBAT4L
mdefine_line|#define SPRN_DBAT4L&t;0x239&t;/* Data BAT 4 Lower Register */
DECL|macro|SPRN_DBAT4U
mdefine_line|#define SPRN_DBAT4U&t;0x238&t;/* Data BAT 4 Upper Register */
DECL|macro|SPRN_DBAT5L
mdefine_line|#define SPRN_DBAT5L&t;0x23B&t;/* Data BAT 5 Lower Register */
DECL|macro|SPRN_DBAT5U
mdefine_line|#define SPRN_DBAT5U&t;0x23A&t;/* Data BAT 5 Upper Register */
DECL|macro|SPRN_DBAT6L
mdefine_line|#define SPRN_DBAT6L&t;0x23D&t;/* Data BAT 6 Lower Register */
DECL|macro|SPRN_DBAT6U
mdefine_line|#define SPRN_DBAT6U&t;0x23C&t;/* Data BAT 6 Upper Register */
DECL|macro|SPRN_DBAT7L
mdefine_line|#define SPRN_DBAT7L&t;0x23F&t;/* Data BAT 7 Lower Register */
DECL|macro|SPRN_DBAT7U
mdefine_line|#define SPRN_DBAT7U&t;0x23E&t;/* Data BAT 7 Upper Register */
DECL|macro|SPRN_DEC
mdefine_line|#define SPRN_DEC&t;0x016&t;&t;/* Decrement Register */
DECL|macro|SPRN_DER
mdefine_line|#define SPRN_DER&t;0x095&t;&t;/* Debug Enable Regsiter */
DECL|macro|DER_RSTE
mdefine_line|#define DER_RSTE&t;0x40000000&t;/* Reset Interrupt */
DECL|macro|DER_CHSTPE
mdefine_line|#define DER_CHSTPE&t;0x20000000&t;/* Check Stop */
DECL|macro|DER_MCIE
mdefine_line|#define DER_MCIE&t;0x10000000&t;/* Machine Check Interrupt */
DECL|macro|DER_EXTIE
mdefine_line|#define DER_EXTIE&t;0x02000000&t;/* External Interrupt */
DECL|macro|DER_ALIE
mdefine_line|#define DER_ALIE&t;0x01000000&t;/* Alignment Interrupt */
DECL|macro|DER_PRIE
mdefine_line|#define DER_PRIE&t;0x00800000&t;/* Program Interrupt */
DECL|macro|DER_FPUVIE
mdefine_line|#define DER_FPUVIE&t;0x00400000&t;/* FP Unavailable Interrupt */
DECL|macro|DER_DECIE
mdefine_line|#define DER_DECIE&t;0x00200000&t;/* Decrementer Interrupt */
DECL|macro|DER_SYSIE
mdefine_line|#define DER_SYSIE&t;0x00040000&t;/* System Call Interrupt */
DECL|macro|DER_TRE
mdefine_line|#define DER_TRE&t;&t;0x00020000&t;/* Trace Interrupt */
DECL|macro|DER_SEIE
mdefine_line|#define DER_SEIE&t;0x00004000&t;/* FP SW Emulation Interrupt */
DECL|macro|DER_ITLBMSE
mdefine_line|#define DER_ITLBMSE&t;0x00002000&t;/* Imp. Spec. Instruction TLB Miss */
DECL|macro|DER_ITLBERE
mdefine_line|#define DER_ITLBERE&t;0x00001000&t;/* Imp. Spec. Instruction TLB Error */
DECL|macro|DER_DTLBMSE
mdefine_line|#define DER_DTLBMSE&t;0x00000800&t;/* Imp. Spec. Data TLB Miss */
DECL|macro|DER_DTLBERE
mdefine_line|#define DER_DTLBERE&t;0x00000400&t;/* Imp. Spec. Data TLB Error */
DECL|macro|DER_LBRKE
mdefine_line|#define DER_LBRKE&t;0x00000008&t;/* Load/Store Breakpoint Interrupt */
DECL|macro|DER_IBRKE
mdefine_line|#define DER_IBRKE&t;0x00000004&t;/* Instruction Breakpoint Interrupt */
DECL|macro|DER_EBRKE
mdefine_line|#define DER_EBRKE&t;0x00000002&t;/* External Breakpoint Interrupt */
DECL|macro|DER_DPIE
mdefine_line|#define DER_DPIE&t;0x00000001&t;/* Dev. Port Nonmaskable Request */
DECL|macro|SPRN_DMISS
mdefine_line|#define SPRN_DMISS&t;0x3D0&t;&t;/* Data TLB Miss Register */
DECL|macro|SPRN_DSISR
mdefine_line|#define SPRN_DSISR&t;0x012&t;/* Data Storage Interrupt Status Register */
DECL|macro|SPRN_EAR
mdefine_line|#define SPRN_EAR&t;0x11A&t;&t;/* External Address Register */
DECL|macro|SPRN_HASH1
mdefine_line|#define SPRN_HASH1&t;0x3D2&t;&t;/* Primary Hash Address Register */
DECL|macro|SPRN_HASH2
mdefine_line|#define SPRN_HASH2&t;0x3D3&t;&t;/* Secondary Hash Address Resgister */
DECL|macro|SPRN_HID0
mdefine_line|#define SPRN_HID0&t;0x3F0&t;&t;/* Hardware Implementation Register 0 */
DECL|macro|HID0_EMCP
mdefine_line|#define HID0_EMCP&t;(1&lt;&lt;31)&t;&t;/* Enable Machine Check pin */
DECL|macro|HID0_EBA
mdefine_line|#define HID0_EBA&t;(1&lt;&lt;29)&t;&t;/* Enable Bus Address Parity */
DECL|macro|HID0_EBD
mdefine_line|#define HID0_EBD&t;(1&lt;&lt;28)&t;&t;/* Enable Bus Data Parity */
DECL|macro|HID0_SBCLK
mdefine_line|#define HID0_SBCLK&t;(1&lt;&lt;27)
DECL|macro|HID0_EICE
mdefine_line|#define HID0_EICE&t;(1&lt;&lt;26)
DECL|macro|HID0_TBEN
mdefine_line|#define HID0_TBEN&t;(1&lt;&lt;26)&t;&t;/* Timebase enable - 745x */
DECL|macro|HID0_ECLK
mdefine_line|#define HID0_ECLK&t;(1&lt;&lt;25)
DECL|macro|HID0_PAR
mdefine_line|#define HID0_PAR&t;(1&lt;&lt;24)
DECL|macro|HID0_STEN
mdefine_line|#define HID0_STEN&t;(1&lt;&lt;24)&t;&t;/* Software table search enable - 745x */
DECL|macro|HID0_HIGH_BAT
mdefine_line|#define HID0_HIGH_BAT&t;(1&lt;&lt;23)&t;&t;/* Enable high BATs - 7455 */
DECL|macro|HID0_DOZE
mdefine_line|#define HID0_DOZE&t;(1&lt;&lt;23)
DECL|macro|HID0_NAP
mdefine_line|#define HID0_NAP&t;(1&lt;&lt;22)
DECL|macro|HID0_SLEEP
mdefine_line|#define HID0_SLEEP&t;(1&lt;&lt;21)
DECL|macro|HID0_DPM
mdefine_line|#define HID0_DPM&t;(1&lt;&lt;20)
DECL|macro|HID0_BHTCLR
mdefine_line|#define HID0_BHTCLR&t;(1&lt;&lt;18)&t;&t;/* Clear branch history table - 7450 */
DECL|macro|HID0_XAEN
mdefine_line|#define HID0_XAEN&t;(1&lt;&lt;17)&t;&t;/* Extended addressing enable - 7450 */
DECL|macro|HID0_NHR
mdefine_line|#define HID0_NHR&t;(1&lt;&lt;16)&t;&t;/* Not hard reset (software bit-7450)*/
DECL|macro|HID0_ICE
mdefine_line|#define HID0_ICE&t;(1&lt;&lt;15)&t;&t;/* Instruction Cache Enable */
DECL|macro|HID0_DCE
mdefine_line|#define HID0_DCE&t;(1&lt;&lt;14)&t;&t;/* Data Cache Enable */
DECL|macro|HID0_ILOCK
mdefine_line|#define HID0_ILOCK&t;(1&lt;&lt;13)&t;&t;/* Instruction Cache Lock */
DECL|macro|HID0_DLOCK
mdefine_line|#define HID0_DLOCK&t;(1&lt;&lt;12)&t;&t;/* Data Cache Lock */
DECL|macro|HID0_ICFI
mdefine_line|#define HID0_ICFI&t;(1&lt;&lt;11)&t;&t;/* Instr. Cache Flash Invalidate */
DECL|macro|HID0_DCI
mdefine_line|#define HID0_DCI&t;(1&lt;&lt;10)&t;&t;/* Data Cache Invalidate */
DECL|macro|HID0_SPD
mdefine_line|#define HID0_SPD&t;(1&lt;&lt;9)&t;&t;/* Speculative disable */
DECL|macro|HID0_SGE
mdefine_line|#define HID0_SGE&t;(1&lt;&lt;7)&t;&t;/* Store Gathering Enable */
DECL|macro|HID0_SIED
mdefine_line|#define HID0_SIED&t;(1&lt;&lt;7)&t;&t;/* Serial Instr. Execution [Disable] */
DECL|macro|HID0_DFCA
mdefine_line|#define HID0_DFCA&t;(1&lt;&lt;6)&t;&t;/* Data Cache Flush Assist */
DECL|macro|HID0_LRSTK
mdefine_line|#define HID0_LRSTK&t;(1&lt;&lt;4)&t;&t;/* Link register stack - 745x */
DECL|macro|HID0_BTIC
mdefine_line|#define HID0_BTIC&t;(1&lt;&lt;5)&t;&t;/* Branch Target Instr Cache Enable */
DECL|macro|HID0_ABE
mdefine_line|#define HID0_ABE&t;(1&lt;&lt;3)&t;&t;/* Address Broadcast Enable */
DECL|macro|HID0_FOLD
mdefine_line|#define HID0_FOLD&t;(1&lt;&lt;3)&t;&t;/* Branch Folding enable - 745x */
DECL|macro|HID0_BHTE
mdefine_line|#define HID0_BHTE&t;(1&lt;&lt;2)&t;&t;/* Branch History Table Enable */
DECL|macro|HID0_BTCD
mdefine_line|#define HID0_BTCD&t;(1&lt;&lt;1)&t;&t;/* Branch target cache disable */
DECL|macro|HID0_NOPDST
mdefine_line|#define HID0_NOPDST&t;(1&lt;&lt;1)&t;&t;/* No-op dst, dstt, etc. instr. */
DECL|macro|HID0_NOPTI
mdefine_line|#define HID0_NOPTI&t;(1&lt;&lt;0)&t;&t;/* No-op dcbt and dcbst instr. */
DECL|macro|SPRN_HID1
mdefine_line|#define SPRN_HID1&t;0x3F1&t;&t;/* Hardware Implementation Register 1 */
DECL|macro|HID1_EMCP
mdefine_line|#define HID1_EMCP&t;(1&lt;&lt;31)&t;&t;/* 7450 Machine Check Pin Enable */
DECL|macro|HID1_DFS
mdefine_line|#define HID1_DFS&t;(1&lt;&lt;22)&t;&t;/* 7447A Dynamic Frequency Scaling */
DECL|macro|HID1_PC0
mdefine_line|#define HID1_PC0&t;(1&lt;&lt;16)&t;&t;/* 7450 PLL_CFG[0] */
DECL|macro|HID1_PC1
mdefine_line|#define HID1_PC1&t;(1&lt;&lt;15)&t;&t;/* 7450 PLL_CFG[1] */
DECL|macro|HID1_PC2
mdefine_line|#define HID1_PC2&t;(1&lt;&lt;14)&t;&t;/* 7450 PLL_CFG[2] */
DECL|macro|HID1_PC3
mdefine_line|#define HID1_PC3&t;(1&lt;&lt;13)&t;&t;/* 7450 PLL_CFG[3] */
DECL|macro|HID1_SYNCBE
mdefine_line|#define HID1_SYNCBE&t;(1&lt;&lt;11)&t;&t;/* 7450 ABE for sync, eieio */
DECL|macro|HID1_ABE
mdefine_line|#define HID1_ABE&t;(1&lt;&lt;10)&t;&t;/* 7450 Address Broadcast Enable */
DECL|macro|SPRN_HID2
mdefine_line|#define SPRN_HID2&t;0x3F8&t;&t;/* Hardware Implementation Register 2 */
DECL|macro|SPRN_IABR
mdefine_line|#define SPRN_IABR&t;0x3F2&t;/* Instruction Address Breakpoint Register */
DECL|macro|SPRN_HID4
mdefine_line|#define SPRN_HID4&t;0x3F4&t;&t;/* 970 HID4 */
DECL|macro|SPRN_HID5
mdefine_line|#define SPRN_HID5&t;0x3F6&t;&t;/* 970 HID5 */
macro_line|#if !defined(SPRN_IAC1) &amp;&amp; !defined(SPRN_IAC2)
DECL|macro|SPRN_IAC1
mdefine_line|#define SPRN_IAC1&t;0x3F4&t;&t;/* Instruction Address Compare 1 */
DECL|macro|SPRN_IAC2
mdefine_line|#define SPRN_IAC2&t;0x3F5&t;&t;/* Instruction Address Compare 2 */
macro_line|#endif
DECL|macro|SPRN_IBAT0L
mdefine_line|#define SPRN_IBAT0L&t;0x211&t;&t;/* Instruction BAT 0 Lower Register */
DECL|macro|SPRN_IBAT0U
mdefine_line|#define SPRN_IBAT0U&t;0x210&t;&t;/* Instruction BAT 0 Upper Register */
DECL|macro|SPRN_IBAT1L
mdefine_line|#define SPRN_IBAT1L&t;0x213&t;&t;/* Instruction BAT 1 Lower Register */
DECL|macro|SPRN_IBAT1U
mdefine_line|#define SPRN_IBAT1U&t;0x212&t;&t;/* Instruction BAT 1 Upper Register */
DECL|macro|SPRN_IBAT2L
mdefine_line|#define SPRN_IBAT2L&t;0x215&t;&t;/* Instruction BAT 2 Lower Register */
DECL|macro|SPRN_IBAT2U
mdefine_line|#define SPRN_IBAT2U&t;0x214&t;&t;/* Instruction BAT 2 Upper Register */
DECL|macro|SPRN_IBAT3L
mdefine_line|#define SPRN_IBAT3L&t;0x217&t;&t;/* Instruction BAT 3 Lower Register */
DECL|macro|SPRN_IBAT3U
mdefine_line|#define SPRN_IBAT3U&t;0x216&t;&t;/* Instruction BAT 3 Upper Register */
DECL|macro|SPRN_IBAT4L
mdefine_line|#define SPRN_IBAT4L&t;0x231&t;&t;/* Instruction BAT 4 Lower Register */
DECL|macro|SPRN_IBAT4U
mdefine_line|#define SPRN_IBAT4U&t;0x230&t;&t;/* Instruction BAT 4 Upper Register */
DECL|macro|SPRN_IBAT5L
mdefine_line|#define SPRN_IBAT5L&t;0x233&t;&t;/* Instruction BAT 5 Lower Register */
DECL|macro|SPRN_IBAT5U
mdefine_line|#define SPRN_IBAT5U&t;0x232&t;&t;/* Instruction BAT 5 Upper Register */
DECL|macro|SPRN_IBAT6L
mdefine_line|#define SPRN_IBAT6L&t;0x235&t;&t;/* Instruction BAT 6 Lower Register */
DECL|macro|SPRN_IBAT6U
mdefine_line|#define SPRN_IBAT6U&t;0x234&t;&t;/* Instruction BAT 6 Upper Register */
DECL|macro|SPRN_IBAT7L
mdefine_line|#define SPRN_IBAT7L&t;0x237&t;&t;/* Instruction BAT 7 Lower Register */
DECL|macro|SPRN_IBAT7U
mdefine_line|#define SPRN_IBAT7U&t;0x236&t;&t;/* Instruction BAT 7 Upper Register */
DECL|macro|SPRN_ICMP
mdefine_line|#define SPRN_ICMP&t;0x3D5&t;&t;/* Instruction TLB Compare Register */
DECL|macro|SPRN_ICTC
mdefine_line|#define SPRN_ICTC&t;0x3FB&t;/* Instruction Cache Throttling Control Reg */
DECL|macro|SPRN_ICTRL
mdefine_line|#define SPRN_ICTRL&t;0x3F3&t;/* 1011 7450 icache and interrupt ctrl */
DECL|macro|ICTRL_EICE
mdefine_line|#define ICTRL_EICE&t;0x08000000&t;/* enable icache parity errs */
DECL|macro|ICTRL_EDC
mdefine_line|#define ICTRL_EDC&t;0x04000000&t;/* enable dcache parity errs */
DECL|macro|ICTRL_EICP
mdefine_line|#define ICTRL_EICP&t;0x00000100&t;/* enable icache par. check */
DECL|macro|SPRN_IMISS
mdefine_line|#define SPRN_IMISS&t;0x3D4&t;&t;/* Instruction TLB Miss Register */
DECL|macro|SPRN_IMMR
mdefine_line|#define SPRN_IMMR&t;0x27E&t;&t;/* Internal Memory Map Register */
DECL|macro|SPRN_L2CR
mdefine_line|#define SPRN_L2CR&t;0x3F9&t;&t;/* Level 2 Cache Control Regsiter */
DECL|macro|SPRN_L2CR2
mdefine_line|#define SPRN_L2CR2&t;0x3f8
DECL|macro|L2CR_L2E
mdefine_line|#define L2CR_L2E&t;&t;0x80000000&t;/* L2 enable */
DECL|macro|L2CR_L2PE
mdefine_line|#define L2CR_L2PE&t;&t;0x40000000&t;/* L2 parity enable */
DECL|macro|L2CR_L2SIZ_MASK
mdefine_line|#define L2CR_L2SIZ_MASK&t;&t;0x30000000&t;/* L2 size mask */
DECL|macro|L2CR_L2SIZ_256KB
mdefine_line|#define L2CR_L2SIZ_256KB&t;0x10000000&t;/* L2 size 256KB */
DECL|macro|L2CR_L2SIZ_512KB
mdefine_line|#define L2CR_L2SIZ_512KB&t;0x20000000&t;/* L2 size 512KB */
DECL|macro|L2CR_L2SIZ_1MB
mdefine_line|#define L2CR_L2SIZ_1MB&t;&t;0x30000000&t;/* L2 size 1MB */
DECL|macro|L2CR_L2CLK_MASK
mdefine_line|#define L2CR_L2CLK_MASK&t;&t;0x0e000000&t;/* L2 clock mask */
DECL|macro|L2CR_L2CLK_DISABLED
mdefine_line|#define L2CR_L2CLK_DISABLED&t;0x00000000&t;/* L2 clock disabled */
DECL|macro|L2CR_L2CLK_DIV1
mdefine_line|#define L2CR_L2CLK_DIV1&t;&t;0x02000000&t;/* L2 clock / 1 */
DECL|macro|L2CR_L2CLK_DIV1_5
mdefine_line|#define L2CR_L2CLK_DIV1_5&t;0x04000000&t;/* L2 clock / 1.5 */
DECL|macro|L2CR_L2CLK_DIV2
mdefine_line|#define L2CR_L2CLK_DIV2&t;&t;0x08000000&t;/* L2 clock / 2 */
DECL|macro|L2CR_L2CLK_DIV2_5
mdefine_line|#define L2CR_L2CLK_DIV2_5&t;0x0a000000&t;/* L2 clock / 2.5 */
DECL|macro|L2CR_L2CLK_DIV3
mdefine_line|#define L2CR_L2CLK_DIV3&t;&t;0x0c000000&t;/* L2 clock / 3 */
DECL|macro|L2CR_L2RAM_MASK
mdefine_line|#define L2CR_L2RAM_MASK&t;&t;0x01800000&t;/* L2 RAM type mask */
DECL|macro|L2CR_L2RAM_FLOW
mdefine_line|#define L2CR_L2RAM_FLOW&t;&t;0x00000000&t;/* L2 RAM flow through */
DECL|macro|L2CR_L2RAM_PIPE
mdefine_line|#define L2CR_L2RAM_PIPE&t;&t;0x01000000&t;/* L2 RAM pipelined */
DECL|macro|L2CR_L2RAM_PIPE_LW
mdefine_line|#define L2CR_L2RAM_PIPE_LW&t;0x01800000&t;/* L2 RAM pipelined latewr */
DECL|macro|L2CR_L2DO
mdefine_line|#define L2CR_L2DO&t;&t;0x00400000&t;/* L2 data only */
DECL|macro|L2CR_L2I
mdefine_line|#define L2CR_L2I&t;&t;0x00200000&t;/* L2 global invalidate */
DECL|macro|L2CR_L2CTL
mdefine_line|#define L2CR_L2CTL&t;&t;0x00100000&t;/* L2 RAM control */
DECL|macro|L2CR_L2WT
mdefine_line|#define L2CR_L2WT&t;&t;0x00080000&t;/* L2 write-through */
DECL|macro|L2CR_L2TS
mdefine_line|#define L2CR_L2TS&t;&t;0x00040000&t;/* L2 test support */
DECL|macro|L2CR_L2OH_MASK
mdefine_line|#define L2CR_L2OH_MASK&t;&t;0x00030000&t;/* L2 output hold mask */
DECL|macro|L2CR_L2OH_0_5
mdefine_line|#define L2CR_L2OH_0_5&t;&t;0x00000000&t;/* L2 output hold 0.5 ns */
DECL|macro|L2CR_L2OH_1_0
mdefine_line|#define L2CR_L2OH_1_0&t;&t;0x00010000&t;/* L2 output hold 1.0 ns */
DECL|macro|L2CR_L2SL
mdefine_line|#define L2CR_L2SL&t;&t;0x00008000&t;/* L2 DLL slow */
DECL|macro|L2CR_L2DF
mdefine_line|#define L2CR_L2DF&t;&t;0x00004000&t;/* L2 differential clock */
DECL|macro|L2CR_L2BYP
mdefine_line|#define L2CR_L2BYP&t;&t;0x00002000&t;/* L2 DLL bypass */
DECL|macro|L2CR_L2IP
mdefine_line|#define L2CR_L2IP&t;&t;0x00000001&t;/* L2 GI in progress */
DECL|macro|L2CR_L2IO_745x
mdefine_line|#define L2CR_L2IO_745x&t;&t;0x00100000&t;/* L2 instr. only (745x) */
DECL|macro|L2CR_L2DO_745x
mdefine_line|#define L2CR_L2DO_745x&t;&t;0x00010000&t;/* L2 data only (745x) */
DECL|macro|L2CR_L2REP_745x
mdefine_line|#define L2CR_L2REP_745x&t;&t;0x00001000&t;/* L2 repl. algorithm (745x) */
DECL|macro|L2CR_L2HWF_745x
mdefine_line|#define L2CR_L2HWF_745x&t;&t;0x00000800&t;/* L2 hardware flush (745x) */
DECL|macro|SPRN_L3CR
mdefine_line|#define SPRN_L3CR&t;&t;0x3FA&t;/* Level 3 Cache Control Regsiter */
DECL|macro|L3CR_L3E
mdefine_line|#define L3CR_L3E&t;&t;0x80000000&t;/* L3 enable */
DECL|macro|L3CR_L3PE
mdefine_line|#define L3CR_L3PE&t;&t;0x40000000&t;/* L3 data parity enable */
DECL|macro|L3CR_L3APE
mdefine_line|#define L3CR_L3APE&t;&t;0x20000000&t;/* L3 addr parity enable */
DECL|macro|L3CR_L3SIZ
mdefine_line|#define L3CR_L3SIZ&t;&t;0x10000000&t;/* L3 size */
DECL|macro|L3CR_L3CLKEN
mdefine_line|#define L3CR_L3CLKEN&t;&t;0x08000000&t;/* L3 clock enable */
DECL|macro|L3CR_L3RES
mdefine_line|#define L3CR_L3RES&t;&t;0x04000000&t;/* L3 special reserved bit */
DECL|macro|L3CR_L3CLKDIV
mdefine_line|#define L3CR_L3CLKDIV&t;&t;0x03800000&t;/* L3 clock divisor */
DECL|macro|L3CR_L3IO
mdefine_line|#define L3CR_L3IO&t;&t;0x00400000&t;/* L3 instruction only */
DECL|macro|L3CR_L3SPO
mdefine_line|#define L3CR_L3SPO&t;&t;0x00040000&t;/* L3 sample point override */
DECL|macro|L3CR_L3CKSP
mdefine_line|#define L3CR_L3CKSP&t;&t;0x00030000&t;/* L3 clock sample point */
DECL|macro|L3CR_L3PSP
mdefine_line|#define L3CR_L3PSP&t;&t;0x0000e000&t;/* L3 P-clock sample point */
DECL|macro|L3CR_L3REP
mdefine_line|#define L3CR_L3REP&t;&t;0x00001000&t;/* L3 replacement algorithm */
DECL|macro|L3CR_L3HWF
mdefine_line|#define L3CR_L3HWF&t;&t;0x00000800&t;/* L3 hardware flush */
DECL|macro|L3CR_L3I
mdefine_line|#define L3CR_L3I&t;&t;0x00000400&t;/* L3 global invalidate */
DECL|macro|L3CR_L3RT
mdefine_line|#define L3CR_L3RT&t;&t;0x00000300&t;/* L3 SRAM type */
DECL|macro|L3CR_L3NIRCA
mdefine_line|#define L3CR_L3NIRCA&t;&t;0x00000080&t;/* L3 non-integer ratio clock adj. */
DECL|macro|L3CR_L3DO
mdefine_line|#define L3CR_L3DO&t;&t;0x00000040&t;/* L3 data only mode */
DECL|macro|L3CR_PMEN
mdefine_line|#define L3CR_PMEN&t;&t;0x00000004&t;/* L3 private memory enable */
DECL|macro|L3CR_PMSIZ
mdefine_line|#define L3CR_PMSIZ&t;&t;0x00000001&t;/* L3 private memory size */
DECL|macro|SPRN_MSSCR0
mdefine_line|#define SPRN_MSSCR0&t;0x3f6&t;/* Memory Subsystem Control Register 0 */
DECL|macro|SPRN_MSSSR0
mdefine_line|#define SPRN_MSSSR0&t;0x3f7&t;/* Memory Subsystem Status Register 1 */
DECL|macro|SPRN_LDSTCR
mdefine_line|#define SPRN_LDSTCR&t;0x3f8&t;/* Load/Store control register */
DECL|macro|SPRN_LDSTDB
mdefine_line|#define SPRN_LDSTDB&t;0x3f4&t;/* */
DECL|macro|SPRN_LR
mdefine_line|#define SPRN_LR&t;&t;0x008&t;/* Link Register */
DECL|macro|SPRN_MMCR0
mdefine_line|#define SPRN_MMCR0&t;0x3B8&t;/* Monitor Mode Control Register 0 */
DECL|macro|SPRN_MMCR1
mdefine_line|#define SPRN_MMCR1&t;0x3BC&t;/* Monitor Mode Control Register 1 */
macro_line|#ifndef SPRN_PIR
DECL|macro|SPRN_PIR
mdefine_line|#define SPRN_PIR&t;0x3FF&t;/* Processor Identification Register */
macro_line|#endif
DECL|macro|SPRN_PMC1
mdefine_line|#define SPRN_PMC1&t;0x3B9&t;/* Performance Counter Register 1 */
DECL|macro|SPRN_PMC2
mdefine_line|#define SPRN_PMC2&t;0x3BA&t;/* Performance Counter Register 2 */
DECL|macro|SPRN_PMC3
mdefine_line|#define SPRN_PMC3&t;0x3BD&t;/* Performance Counter Register 3 */
DECL|macro|SPRN_PMC4
mdefine_line|#define SPRN_PMC4&t;0x3BE&t;/* Performance Counter Register 4 */
DECL|macro|SPRN_PTEHI
mdefine_line|#define SPRN_PTEHI&t;0x3D5&t;/* 981 7450 PTE HI word (S/W TLB load) */
DECL|macro|SPRN_PTELO
mdefine_line|#define SPRN_PTELO&t;0x3D6&t;/* 982 7450 PTE LO word (S/W TLB load) */
DECL|macro|SPRN_PVR
mdefine_line|#define SPRN_PVR&t;0x11F&t;/* Processor Version Register */
DECL|macro|SPRN_RPA
mdefine_line|#define SPRN_RPA&t;0x3D6&t;/* Required Physical Address Register */
DECL|macro|SPRN_SDA
mdefine_line|#define SPRN_SDA&t;0x3BF&t;/* Sampled Data Address Register */
DECL|macro|SPRN_SDR1
mdefine_line|#define SPRN_SDR1&t;0x019&t;/* MMU Hash Base Register */
DECL|macro|SPRN_SIA
mdefine_line|#define SPRN_SIA&t;0x3BB&t;/* Sampled Instruction Address Register */
DECL|macro|SPRN_SPRG0
mdefine_line|#define SPRN_SPRG0&t;0x110&t;/* Special Purpose Register General 0 */
DECL|macro|SPRN_SPRG1
mdefine_line|#define SPRN_SPRG1&t;0x111&t;/* Special Purpose Register General 1 */
DECL|macro|SPRN_SPRG2
mdefine_line|#define SPRN_SPRG2&t;0x112&t;/* Special Purpose Register General 2 */
DECL|macro|SPRN_SPRG3
mdefine_line|#define SPRN_SPRG3&t;0x113&t;/* Special Purpose Register General 3 */
DECL|macro|SPRN_SPRG4
mdefine_line|#define SPRN_SPRG4&t;0x114&t;/* Special Purpose Register General 4 */
DECL|macro|SPRN_SPRG5
mdefine_line|#define SPRN_SPRG5&t;0x115&t;/* Special Purpose Register General 5 */
DECL|macro|SPRN_SPRG6
mdefine_line|#define SPRN_SPRG6&t;0x116&t;/* Special Purpose Register General 6 */
DECL|macro|SPRN_SPRG7
mdefine_line|#define SPRN_SPRG7&t;0x117&t;/* Special Purpose Register General 7 */
DECL|macro|SPRN_SRR0
mdefine_line|#define SPRN_SRR0&t;0x01A&t;/* Save/Restore Register 0 */
DECL|macro|SPRN_SRR1
mdefine_line|#define SPRN_SRR1&t;0x01B&t;/* Save/Restore Register 1 */
macro_line|#ifndef SPRN_SVR
DECL|macro|SPRN_SVR
mdefine_line|#define SPRN_SVR&t;0x11E&t;/* System Version Register */
macro_line|#endif
DECL|macro|SPRN_THRM1
mdefine_line|#define SPRN_THRM1&t;0x3FC&t;&t;/* Thermal Management Register 1 */
multiline_comment|/* these bits were defined in inverted endian sense originally, ugh, confusing */
DECL|macro|THRM1_TIN
mdefine_line|#define THRM1_TIN&t;(1 &lt;&lt; 31)
DECL|macro|THRM1_TIV
mdefine_line|#define THRM1_TIV&t;(1 &lt;&lt; 30)
DECL|macro|THRM1_THRES
mdefine_line|#define THRM1_THRES(x)&t;((x&amp;0x7f)&lt;&lt;23)
DECL|macro|THRM3_SITV
mdefine_line|#define THRM3_SITV(x)&t;((x&amp;0x3fff)&lt;&lt;1)
DECL|macro|THRM1_TID
mdefine_line|#define THRM1_TID&t;(1&lt;&lt;2)
DECL|macro|THRM1_TIE
mdefine_line|#define THRM1_TIE&t;(1&lt;&lt;1)
DECL|macro|THRM1_V
mdefine_line|#define THRM1_V&t;&t;(1&lt;&lt;0)
DECL|macro|SPRN_THRM2
mdefine_line|#define SPRN_THRM2&t;0x3FD&t;&t;/* Thermal Management Register 2 */
DECL|macro|SPRN_THRM3
mdefine_line|#define SPRN_THRM3&t;0x3FE&t;&t;/* Thermal Management Register 3 */
DECL|macro|THRM3_E
mdefine_line|#define THRM3_E&t;&t;(1&lt;&lt;0)
DECL|macro|SPRN_TLBMISS
mdefine_line|#define SPRN_TLBMISS&t;0x3D4&t;&t;/* 980 7450 TLB Miss Register */
DECL|macro|SPRN_UMMCR0
mdefine_line|#define SPRN_UMMCR0&t;0x3A8&t;/* User Monitor Mode Control Register 0 */
DECL|macro|SPRN_UMMCR1
mdefine_line|#define SPRN_UMMCR1&t;0x3AC&t;/* User Monitor Mode Control Register 0 */
DECL|macro|SPRN_UPMC1
mdefine_line|#define SPRN_UPMC1&t;0x3A9&t;/* User Performance Counter Register 1 */
DECL|macro|SPRN_UPMC2
mdefine_line|#define SPRN_UPMC2&t;0x3AA&t;/* User Performance Counter Register 2 */
DECL|macro|SPRN_UPMC3
mdefine_line|#define SPRN_UPMC3&t;0x3AD&t;/* User Performance Counter Register 3 */
DECL|macro|SPRN_UPMC4
mdefine_line|#define SPRN_UPMC4&t;0x3AE&t;/* User Performance Counter Register 4 */
DECL|macro|SPRN_USIA
mdefine_line|#define SPRN_USIA&t;0x3AB&t;/* User Sampled Instruction Address Register */
DECL|macro|SPRN_VRSAVE
mdefine_line|#define SPRN_VRSAVE&t;0x100&t;/* Vector Register Save Register */
DECL|macro|SPRN_XER
mdefine_line|#define SPRN_XER&t;0x001&t;/* Fixed Point Exception Register */
multiline_comment|/* Bit definitions for MMCR0 and PMC1 / PMC2. */
DECL|macro|MMCR0_PMC1_CYCLES
mdefine_line|#define MMCR0_PMC1_CYCLES&t;(1 &lt;&lt; 7)
DECL|macro|MMCR0_PMC1_ICACHEMISS
mdefine_line|#define MMCR0_PMC1_ICACHEMISS&t;(5 &lt;&lt; 7)
DECL|macro|MMCR0_PMC1_DTLB
mdefine_line|#define MMCR0_PMC1_DTLB&t;&t;(6 &lt;&lt; 7)
DECL|macro|MMCR0_PMC2_DCACHEMISS
mdefine_line|#define MMCR0_PMC2_DCACHEMISS&t;0x6
DECL|macro|MMCR0_PMC2_CYCLES
mdefine_line|#define MMCR0_PMC2_CYCLES&t;0x1
DECL|macro|MMCR0_PMC2_ITLB
mdefine_line|#define MMCR0_PMC2_ITLB&t;&t;0x7
DECL|macro|MMCR0_PMC2_LOADMISSTIME
mdefine_line|#define MMCR0_PMC2_LOADMISSTIME&t;0x5
DECL|macro|MMCR0_PMXE
mdefine_line|#define MMCR0_PMXE&t;(1 &lt;&lt; 26)
multiline_comment|/* Short-hand versions for a number of the above SPRNs */
DECL|macro|CTR
mdefine_line|#define CTR&t;SPRN_CTR&t;/* Counter Register */
DECL|macro|DAR
mdefine_line|#define DAR&t;SPRN_DAR&t;/* Data Address Register */
DECL|macro|DABR
mdefine_line|#define DABR&t;SPRN_DABR&t;/* Data Address Breakpoint Register */
DECL|macro|DBAT0L
mdefine_line|#define DBAT0L&t;SPRN_DBAT0L&t;/* Data BAT 0 Lower Register */
DECL|macro|DBAT0U
mdefine_line|#define DBAT0U&t;SPRN_DBAT0U&t;/* Data BAT 0 Upper Register */
DECL|macro|DBAT1L
mdefine_line|#define DBAT1L&t;SPRN_DBAT1L&t;/* Data BAT 1 Lower Register */
DECL|macro|DBAT1U
mdefine_line|#define DBAT1U&t;SPRN_DBAT1U&t;/* Data BAT 1 Upper Register */
DECL|macro|DBAT2L
mdefine_line|#define DBAT2L&t;SPRN_DBAT2L&t;/* Data BAT 2 Lower Register */
DECL|macro|DBAT2U
mdefine_line|#define DBAT2U&t;SPRN_DBAT2U&t;/* Data BAT 2 Upper Register */
DECL|macro|DBAT3L
mdefine_line|#define DBAT3L&t;SPRN_DBAT3L&t;/* Data BAT 3 Lower Register */
DECL|macro|DBAT3U
mdefine_line|#define DBAT3U&t;SPRN_DBAT3U&t;/* Data BAT 3 Upper Register */
DECL|macro|DBAT4L
mdefine_line|#define DBAT4L&t;SPRN_DBAT4L&t;/* Data BAT 4 Lower Register */
DECL|macro|DBAT4U
mdefine_line|#define DBAT4U&t;SPRN_DBAT4U&t;/* Data BAT 4 Upper Register */
DECL|macro|DBAT5L
mdefine_line|#define DBAT5L&t;SPRN_DBAT5L&t;/* Data BAT 5 Lower Register */
DECL|macro|DBAT5U
mdefine_line|#define DBAT5U&t;SPRN_DBAT5U&t;/* Data BAT 5 Upper Register */
DECL|macro|DBAT6L
mdefine_line|#define DBAT6L&t;SPRN_DBAT6L&t;/* Data BAT 6 Lower Register */
DECL|macro|DBAT6U
mdefine_line|#define DBAT6U&t;SPRN_DBAT6U&t;/* Data BAT 6 Upper Register */
DECL|macro|DBAT7L
mdefine_line|#define DBAT7L&t;SPRN_DBAT7L&t;/* Data BAT 7 Lower Register */
DECL|macro|DBAT7U
mdefine_line|#define DBAT7U&t;SPRN_DBAT7U&t;/* Data BAT 7 Upper Register */
singleline_comment|//#define DEC&t;SPRN_DEC&t;/* Decrement Register */
DECL|macro|DMISS
mdefine_line|#define DMISS&t;SPRN_DMISS&t;/* Data TLB Miss Register */
DECL|macro|DSISR
mdefine_line|#define DSISR&t;SPRN_DSISR&t;/* Data Storage Interrupt Status Register */
DECL|macro|EAR
mdefine_line|#define EAR&t;SPRN_EAR&t;/* External Address Register */
DECL|macro|HASH1
mdefine_line|#define HASH1&t;SPRN_HASH1&t;/* Primary Hash Address Register */
DECL|macro|HASH2
mdefine_line|#define HASH2&t;SPRN_HASH2&t;/* Secondary Hash Address Register */
DECL|macro|HID0
mdefine_line|#define HID0&t;SPRN_HID0&t;/* Hardware Implementation Register 0 */
DECL|macro|HID1
mdefine_line|#define HID1&t;SPRN_HID1&t;/* Hardware Implementation Register 1 */
DECL|macro|IABR
mdefine_line|#define IABR&t;SPRN_IABR&t;/* Instruction Address Breakpoint Register */
DECL|macro|IBAT0L
mdefine_line|#define IBAT0L&t;SPRN_IBAT0L&t;/* Instruction BAT 0 Lower Register */
DECL|macro|IBAT0U
mdefine_line|#define IBAT0U&t;SPRN_IBAT0U&t;/* Instruction BAT 0 Upper Register */
DECL|macro|IBAT1L
mdefine_line|#define IBAT1L&t;SPRN_IBAT1L&t;/* Instruction BAT 1 Lower Register */
DECL|macro|IBAT1U
mdefine_line|#define IBAT1U&t;SPRN_IBAT1U&t;/* Instruction BAT 1 Upper Register */
DECL|macro|IBAT2L
mdefine_line|#define IBAT2L&t;SPRN_IBAT2L&t;/* Instruction BAT 2 Lower Register */
DECL|macro|IBAT2U
mdefine_line|#define IBAT2U&t;SPRN_IBAT2U&t;/* Instruction BAT 2 Upper Register */
DECL|macro|IBAT3L
mdefine_line|#define IBAT3L&t;SPRN_IBAT3L&t;/* Instruction BAT 3 Lower Register */
DECL|macro|IBAT3U
mdefine_line|#define IBAT3U&t;SPRN_IBAT3U&t;/* Instruction BAT 3 Upper Register */
DECL|macro|IBAT4L
mdefine_line|#define IBAT4L&t;SPRN_IBAT4L&t;/* Instruction BAT 4 Lower Register */
DECL|macro|IBAT4U
mdefine_line|#define IBAT4U&t;SPRN_IBAT4U&t;/* Instruction BAT 4 Upper Register */
DECL|macro|IBAT5L
mdefine_line|#define IBAT5L&t;SPRN_IBAT5L&t;/* Instruction BAT 5 Lower Register */
DECL|macro|IBAT5U
mdefine_line|#define IBAT5U&t;SPRN_IBAT5U&t;/* Instruction BAT 5 Upper Register */
DECL|macro|IBAT6L
mdefine_line|#define IBAT6L&t;SPRN_IBAT6L&t;/* Instruction BAT 6 Lower Register */
DECL|macro|IBAT6U
mdefine_line|#define IBAT6U&t;SPRN_IBAT6U&t;/* Instruction BAT 6 Upper Register */
DECL|macro|IBAT7L
mdefine_line|#define IBAT7L&t;SPRN_IBAT7L&t;/* Instruction BAT 7 Lower Register */
DECL|macro|IBAT7U
mdefine_line|#define IBAT7U&t;SPRN_IBAT7U&t;/* Instruction BAT 7 Upper Register */
DECL|macro|ICMP
mdefine_line|#define ICMP&t;SPRN_ICMP&t;/* Instruction TLB Compare Register */
DECL|macro|IMISS
mdefine_line|#define IMISS&t;SPRN_IMISS&t;/* Instruction TLB Miss Register */
DECL|macro|IMMR
mdefine_line|#define IMMR&t;SPRN_IMMR&t;/* PPC 860/821 Internal Memory Map Register */
DECL|macro|L2CR
mdefine_line|#define L2CR&t;SPRN_L2CR&t;/* Classic PPC L2 cache control register */
DECL|macro|L3CR
mdefine_line|#define L3CR&t;SPRN_L3CR&t;/* PPC 745x L3 cache control register */
singleline_comment|//#define LR&t;SPRN_LR
DECL|macro|PVR
mdefine_line|#define PVR&t;SPRN_PVR&t;/* Processor Version */
singleline_comment|//#define RPA&t;SPRN_RPA&t;/* Required Physical Address Register */
DECL|macro|SDR1
mdefine_line|#define SDR1&t;SPRN_SDR1&t;/* MMU hash base register */
DECL|macro|SPR0
mdefine_line|#define SPR0&t;SPRN_SPRG0&t;/* Supervisor Private Registers */
DECL|macro|SPR1
mdefine_line|#define SPR1&t;SPRN_SPRG1
DECL|macro|SPR2
mdefine_line|#define SPR2&t;SPRN_SPRG2
DECL|macro|SPR3
mdefine_line|#define SPR3&t;SPRN_SPRG3
DECL|macro|SPR4
mdefine_line|#define SPR4&t;SPRN_SPRG4
DECL|macro|SPR5
mdefine_line|#define SPR5&t;SPRN_SPRG5
DECL|macro|SPR6
mdefine_line|#define SPR6&t;SPRN_SPRG6
DECL|macro|SPR7
mdefine_line|#define SPR7&t;SPRN_SPRG7
DECL|macro|SPRG0
mdefine_line|#define SPRG0&t;SPRN_SPRG0
DECL|macro|SPRG1
mdefine_line|#define SPRG1&t;SPRN_SPRG1
DECL|macro|SPRG2
mdefine_line|#define SPRG2&t;SPRN_SPRG2
DECL|macro|SPRG3
mdefine_line|#define SPRG3&t;SPRN_SPRG3
DECL|macro|SPRG4
mdefine_line|#define SPRG4&t;SPRN_SPRG4
DECL|macro|SPRG5
mdefine_line|#define SPRG5&t;SPRN_SPRG5
DECL|macro|SPRG6
mdefine_line|#define SPRG6&t;SPRN_SPRG6
DECL|macro|SPRG7
mdefine_line|#define SPRG7&t;SPRN_SPRG7
DECL|macro|SRR0
mdefine_line|#define SRR0&t;SPRN_SRR0&t;/* Save and Restore Register 0 */
DECL|macro|SRR1
mdefine_line|#define SRR1&t;SPRN_SRR1&t;/* Save and Restore Register 1 */
DECL|macro|SRR2
mdefine_line|#define SRR2&t;SPRN_SRR2&t;/* Save and Restore Register 2 */
DECL|macro|SRR3
mdefine_line|#define SRR3&t;SPRN_SRR3&t;/* Save and Restore Register 3 */
DECL|macro|SVR
mdefine_line|#define SVR&t;SPRN_SVR&t;/* System Version Register */
DECL|macro|ICTC
mdefine_line|#define ICTC&t;SPRN_ICTC&t;/* Instruction Cache Throttling Control Reg */
DECL|macro|THRM1
mdefine_line|#define THRM1&t;SPRN_THRM1&t;/* Thermal Management Register 1 */
DECL|macro|THRM2
mdefine_line|#define THRM2&t;SPRN_THRM2&t;/* Thermal Management Register 2 */
DECL|macro|THRM3
mdefine_line|#define THRM3&t;SPRN_THRM3&t;/* Thermal Management Register 3 */
DECL|macro|XER
mdefine_line|#define XER&t;SPRN_XER
DECL|macro|TBRL
mdefine_line|#define TBRL&t;SPRN_TBRL&t;/* Time Base Read Lower Register */
DECL|macro|TBRU
mdefine_line|#define TBRU&t;SPRN_TBRU&t;/* Time Base Read Upper Register */
DECL|macro|TBWL
mdefine_line|#define TBWL&t;SPRN_TBWL&t;/* Time Base Write Lower Register */
DECL|macro|TBWU
mdefine_line|#define TBWU&t;SPRN_TBWU&t;/* Time Base Write Upper Register */
multiline_comment|/* Processor Version Register */
multiline_comment|/* Processor Version Register (PVR) field extraction */
DECL|macro|PVR_VER
mdefine_line|#define PVR_VER(pvr)&t;(((pvr) &gt;&gt;  16) &amp; 0xFFFF)&t;/* Version field */
DECL|macro|PVR_REV
mdefine_line|#define PVR_REV(pvr)&t;(((pvr) &gt;&gt;   0) &amp; 0xFFFF)&t;/* Revison field */
multiline_comment|/*&n; * IBM has further subdivided the standard PowerPC 16-bit version and&n; * revision subfields of the PVR for the PowerPC 403s into the following:&n; */
DECL|macro|PVR_FAM
mdefine_line|#define PVR_FAM(pvr)&t;(((pvr) &gt;&gt; 20) &amp; 0xFFF)&t;/* Family field */
DECL|macro|PVR_MEM
mdefine_line|#define PVR_MEM(pvr)&t;(((pvr) &gt;&gt; 16) &amp; 0xF)&t;/* Member field */
DECL|macro|PVR_CORE
mdefine_line|#define PVR_CORE(pvr)&t;(((pvr) &gt;&gt; 12) &amp; 0xF)&t;/* Core field */
DECL|macro|PVR_CFG
mdefine_line|#define PVR_CFG(pvr)&t;(((pvr) &gt;&gt;  8) &amp; 0xF)&t;/* Configuration field */
DECL|macro|PVR_MAJ
mdefine_line|#define PVR_MAJ(pvr)&t;(((pvr) &gt;&gt;  4) &amp; 0xF)&t;/* Major revision field */
DECL|macro|PVR_MIN
mdefine_line|#define PVR_MIN(pvr)&t;(((pvr) &gt;&gt;  0) &amp; 0xF)&t;/* Minor revision field */
multiline_comment|/* Processor Version Numbers */
DECL|macro|PVR_403GA
mdefine_line|#define PVR_403GA&t;0x00200000
DECL|macro|PVR_403GB
mdefine_line|#define PVR_403GB&t;0x00200100
DECL|macro|PVR_403GC
mdefine_line|#define PVR_403GC&t;0x00200200
DECL|macro|PVR_403GCX
mdefine_line|#define PVR_403GCX&t;0x00201400
DECL|macro|PVR_405GP
mdefine_line|#define PVR_405GP&t;0x40110000
DECL|macro|PVR_STB03XXX
mdefine_line|#define PVR_STB03XXX&t;0x40310000
DECL|macro|PVR_NP405H
mdefine_line|#define PVR_NP405H&t;0x41410000
DECL|macro|PVR_NP405L
mdefine_line|#define PVR_NP405L&t;0x41610000
DECL|macro|PVR_440GP_RB
mdefine_line|#define PVR_440GP_RB&t;0x40120440
DECL|macro|PVR_440GP_RC1
mdefine_line|#define PVR_440GP_RC1&t;0x40120481
DECL|macro|PVR_440GP_RC2
mdefine_line|#define PVR_440GP_RC2&t;0x40200481
DECL|macro|PVR_440GX_RA
mdefine_line|#define PVR_440GX_RA&t;0x51b21850
DECL|macro|PVR_440GX_RB
mdefine_line|#define PVR_440GX_RB&t;0x51b21851
DECL|macro|PVR_440GX_RC
mdefine_line|#define PVR_440GX_RC&t;0x51b21892
DECL|macro|PVR_601
mdefine_line|#define PVR_601&t;&t;0x00010000
DECL|macro|PVR_602
mdefine_line|#define PVR_602&t;&t;0x00050000
DECL|macro|PVR_603
mdefine_line|#define PVR_603&t;&t;0x00030000
DECL|macro|PVR_603e
mdefine_line|#define PVR_603e&t;0x00060000
DECL|macro|PVR_603ev
mdefine_line|#define PVR_603ev&t;0x00070000
DECL|macro|PVR_603r
mdefine_line|#define PVR_603r&t;0x00071000
DECL|macro|PVR_604
mdefine_line|#define PVR_604&t;&t;0x00040000
DECL|macro|PVR_604e
mdefine_line|#define PVR_604e&t;0x00090000
DECL|macro|PVR_604r
mdefine_line|#define PVR_604r&t;0x000A0000
DECL|macro|PVR_620
mdefine_line|#define PVR_620&t;&t;0x00140000
DECL|macro|PVR_740
mdefine_line|#define PVR_740&t;&t;0x00080000
DECL|macro|PVR_750
mdefine_line|#define PVR_750&t;&t;PVR_740
DECL|macro|PVR_740P
mdefine_line|#define PVR_740P&t;0x10080000
DECL|macro|PVR_750P
mdefine_line|#define PVR_750P&t;PVR_740P
DECL|macro|PVR_7400
mdefine_line|#define PVR_7400&t;0x000C0000
DECL|macro|PVR_7410
mdefine_line|#define PVR_7410&t;0x800C0000
DECL|macro|PVR_7450
mdefine_line|#define PVR_7450&t;0x80000000
DECL|macro|PVR_8540
mdefine_line|#define PVR_8540&t;0x80200000
DECL|macro|PVR_8560
mdefine_line|#define PVR_8560&t;0x80200000
multiline_comment|/*&n; * For the 8xx processors, all of them report the same PVR family for&n; * the PowerPC core. The various versions of these processors must be&n; * differentiated by the version number in the Communication Processor&n; * Module (CPM).&n; */
DECL|macro|PVR_821
mdefine_line|#define PVR_821&t;&t;0x00500000
DECL|macro|PVR_823
mdefine_line|#define PVR_823&t;&t;PVR_821
DECL|macro|PVR_850
mdefine_line|#define PVR_850&t;&t;PVR_821
DECL|macro|PVR_860
mdefine_line|#define PVR_860&t;&t;PVR_821
DECL|macro|PVR_8240
mdefine_line|#define PVR_8240&t;0x00810100
DECL|macro|PVR_8245
mdefine_line|#define PVR_8245&t;0x80811014
DECL|macro|PVR_8260
mdefine_line|#define PVR_8260&t;PVR_8240
multiline_comment|/* System Version Numbers */
DECL|macro|SVR_8540
mdefine_line|#define SVR_8540&t;0x80300000
DECL|macro|SVR_8541E
mdefine_line|#define SVR_8541E&t;0x807A0000
DECL|macro|SVR_8555E
mdefine_line|#define SVR_8555E&t;0x80790000
DECL|macro|SVR_8560
mdefine_line|#define SVR_8560&t;0x80700000
macro_line|#if 0
multiline_comment|/* Segment Registers */
mdefine_line|#define SR0&t;0
mdefine_line|#define SR1&t;1
mdefine_line|#define SR2&t;2
mdefine_line|#define SR3&t;3
mdefine_line|#define SR4&t;4
mdefine_line|#define SR5&t;5
mdefine_line|#define SR6&t;6
mdefine_line|#define SR7&t;7
mdefine_line|#define SR8&t;8
mdefine_line|#define SR9&t;9
mdefine_line|#define SR10&t;10
mdefine_line|#define SR11&t;11
mdefine_line|#define SR12&t;12
mdefine_line|#define SR13&t;13
mdefine_line|#define SR14&t;14
mdefine_line|#define SR15&t;15
macro_line|#endif
multiline_comment|/* Macros for setting and retrieving special purpose registers */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|mfmsr
mdefine_line|#define mfmsr()&t;&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfmsr %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|macro|mtmsr
mdefine_line|#define mtmsr(v)&t;asm volatile(&quot;mtmsr %0&quot; : : &quot;r&quot; (v))
DECL|macro|mfspr
mdefine_line|#define mfspr(rn)&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfspr %0,&quot; __stringify(rn) &bslash;&n;&t;&t;&t;&t;: &quot;=r&quot; (rval)); rval;})
DECL|macro|mtspr
mdefine_line|#define mtspr(rn, v)&t;asm volatile(&quot;mtspr &quot; __stringify(rn) &quot;,%0&quot; : : &quot;r&quot; (v))
DECL|macro|mfsrin
mdefine_line|#define mfsrin(v)&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfsrin %0,%1&quot; : &quot;=r&quot; (rval) : &quot;r&quot; (v)); &bslash;&n;&t;&t;&t;&t;&t;rval;})
DECL|macro|proc_trap
mdefine_line|#define proc_trap()&t;asm volatile(&quot;trap&quot;)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PPC_REGS_H__ */
macro_line|#endif /* __KERNEL__ */
eof
