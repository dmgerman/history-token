multiline_comment|/*&n; * Contains register definitions common to the Book E PowerPC&n; * specification.  Notice that while the IBM-40x series of CPUs&n; * are not true Book E PowerPCs, they borrowed a number of features&n; * before Book E was finalized, and are included here as well.  Unfortunatly,&n; * they sometimes used different locations than true Book E CPUs did.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_REG_BOOKE_H__
DECL|macro|__ASM_PPC_REG_BOOKE_H__
mdefine_line|#define __ASM_PPC_REG_BOOKE_H__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Device Control Registers */
DECL|macro|mfdcr
mdefine_line|#define mfdcr(rn) mfdcr_or_dflt(rn, 0)
DECL|macro|mfdcr_or_dflt
mdefine_line|#define mfdcr_or_dflt(rn,default_rval)&t;&t;&t;&t;&t;&bslash;&n;&t;({unsigned int rval;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (rn == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;rval = default_rval;&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile(&quot;mfdcr %0,&quot; __stringify(rn) : &quot;=r&quot; (rval)); &bslash;&n;&t;rval;})
DECL|macro|mtdcr
mdefine_line|#define mtdcr(rn, v)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (rn != 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile(&quot;mtdcr &quot; __stringify(rn) &quot;,%0&quot; : : &quot;r&quot; (v)); &bslash;&n;} while (0)
multiline_comment|/* R/W of indirect DCRs make use of standard naming conventions for DCRs */
DECL|macro|mfdcri
mdefine_line|#define mfdcri(base, reg)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mtdcr(base ## _CFGADDR, base ## _ ## reg);&t;&bslash;&n;&t;mfdcr(base ## _CFGDATA);&t;&t;&t;&bslash;&n;})
DECL|macro|mtdcri
mdefine_line|#define mtdcri(base, reg, data)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mtdcr(base ## _CFGADDR, base ## _ ## reg);&t;&bslash;&n;&t;mtdcr(base ## _CFGDATA, data);&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Machine State Register (MSR) Fields */
DECL|macro|MSR_DWE
mdefine_line|#define MSR_DWE&t;&t;(1&lt;&lt;10)&t;/* Debug Wait Enable */
DECL|macro|MSR_IS
mdefine_line|#define MSR_IS&t;&t;MSR_IR&t;/* Instruction Space */
DECL|macro|MSR_DS
mdefine_line|#define MSR_DS&t;&t;MSR_DR&t;/* Data Space */
multiline_comment|/* Default MSR for kernel mode. */
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL&t;(MSR_ME|MSR_RI|MSR_IR|MSR_DR|MSR_CE|MSR_DE)
multiline_comment|/* Special Purpose Registers (SPRNs)*/
DECL|macro|SPRN_DECAR
mdefine_line|#define SPRN_DECAR&t;0x036&t;/* Decrementer Auto Reload Register */
DECL|macro|SPRN_CSRR0
mdefine_line|#define SPRN_CSRR0&t;0x03A&t;/* Critical Save and Restore Register 0 */
DECL|macro|SPRN_CSRR1
mdefine_line|#define SPRN_CSRR1&t;0x03B&t;/* Critical Save and Restore Register 1 */
DECL|macro|SPRN_IVPR
mdefine_line|#define SPRN_IVPR&t;0x03F&t;/* Interrupt Vector Prefix Register */
DECL|macro|SPRN_USPRG0
mdefine_line|#define SPRN_USPRG0&t;0x100&t;/* User Special Purpose Register General 0 */
DECL|macro|SPRN_SPRG4R
mdefine_line|#define SPRN_SPRG4R&t;0x104&t;/* Special Purpose Register General 4 Read */
DECL|macro|SPRN_SPRG5R
mdefine_line|#define SPRN_SPRG5R&t;0x105&t;/* Special Purpose Register General 5 Read */
DECL|macro|SPRN_SPRG6R
mdefine_line|#define SPRN_SPRG6R&t;0x106&t;/* Special Purpose Register General 6 Read */
DECL|macro|SPRN_SPRG7R
mdefine_line|#define SPRN_SPRG7R&t;0x107&t;/* Special Purpose Register General 7 Read */
DECL|macro|SPRN_TBRL
mdefine_line|#define SPRN_TBRL&t;0x10C&t;/* Time Base Read Lower Register (user, R/O) */
DECL|macro|SPRN_TBRU
mdefine_line|#define SPRN_TBRU&t;0x10D&t;/* Time Base Read Upper Register (user, R/O) */
DECL|macro|SPRN_SPRG4W
mdefine_line|#define SPRN_SPRG4W&t;0x114&t;/* Special Purpose Register General 4 Write */
DECL|macro|SPRN_SPRG5W
mdefine_line|#define SPRN_SPRG5W&t;0x115&t;/* Special Purpose Register General 5 Write */
DECL|macro|SPRN_SPRG6W
mdefine_line|#define SPRN_SPRG6W&t;0x116&t;/* Special Purpose Register General 6 Write */
DECL|macro|SPRN_SPRG7W
mdefine_line|#define SPRN_SPRG7W&t;0x117&t;/* Special Purpose Register General 7 Write */
DECL|macro|SPRN_TBWL
mdefine_line|#define SPRN_TBWL&t;0x11C&t;/* Time Base Lower Register (super, R/W) */
DECL|macro|SPRN_TBWU
mdefine_line|#define SPRN_TBWU&t;0x11D&t;/* Time Base Upper Register (super, R/W) */
DECL|macro|SPRN_DBCR2
mdefine_line|#define SPRN_DBCR2&t;0x136&t;/* Debug Control Register 2 */
DECL|macro|SPRN_IAC3
mdefine_line|#define SPRN_IAC3&t;0x13A&t;/* Instruction Address Compare 3 */
DECL|macro|SPRN_IAC4
mdefine_line|#define SPRN_IAC4&t;0x13B&t;/* Instruction Address Compare 4 */
DECL|macro|SPRN_DVC1
mdefine_line|#define SPRN_DVC1&t;0x13E&t;/* Data Value Compare Register 1 */
DECL|macro|SPRN_DVC2
mdefine_line|#define SPRN_DVC2&t;0x13F&t;/* Data Value Compare Register 2 */
DECL|macro|SPRN_IVOR0
mdefine_line|#define SPRN_IVOR0&t;0x190&t;/* Interrupt Vector Offset Register 0 */
DECL|macro|SPRN_IVOR1
mdefine_line|#define SPRN_IVOR1&t;0x191&t;/* Interrupt Vector Offset Register 1 */
DECL|macro|SPRN_IVOR2
mdefine_line|#define SPRN_IVOR2&t;0x192&t;/* Interrupt Vector Offset Register 2 */
DECL|macro|SPRN_IVOR3
mdefine_line|#define SPRN_IVOR3&t;0x193&t;/* Interrupt Vector Offset Register 3 */
DECL|macro|SPRN_IVOR4
mdefine_line|#define SPRN_IVOR4&t;0x194&t;/* Interrupt Vector Offset Register 4 */
DECL|macro|SPRN_IVOR5
mdefine_line|#define SPRN_IVOR5&t;0x195&t;/* Interrupt Vector Offset Register 5 */
DECL|macro|SPRN_IVOR6
mdefine_line|#define SPRN_IVOR6&t;0x196&t;/* Interrupt Vector Offset Register 6 */
DECL|macro|SPRN_IVOR7
mdefine_line|#define SPRN_IVOR7&t;0x197&t;/* Interrupt Vector Offset Register 7 */
DECL|macro|SPRN_IVOR8
mdefine_line|#define SPRN_IVOR8&t;0x198&t;/* Interrupt Vector Offset Register 8 */
DECL|macro|SPRN_IVOR9
mdefine_line|#define SPRN_IVOR9&t;0x199&t;/* Interrupt Vector Offset Register 9 */
DECL|macro|SPRN_IVOR10
mdefine_line|#define SPRN_IVOR10&t;0x19A&t;/* Interrupt Vector Offset Register 10 */
DECL|macro|SPRN_IVOR11
mdefine_line|#define SPRN_IVOR11&t;0x19B&t;/* Interrupt Vector Offset Register 11 */
DECL|macro|SPRN_IVOR12
mdefine_line|#define SPRN_IVOR12&t;0x19C&t;/* Interrupt Vector Offset Register 12 */
DECL|macro|SPRN_IVOR13
mdefine_line|#define SPRN_IVOR13&t;0x19D&t;/* Interrupt Vector Offset Register 13 */
DECL|macro|SPRN_IVOR14
mdefine_line|#define SPRN_IVOR14&t;0x19E&t;/* Interrupt Vector Offset Register 14 */
DECL|macro|SPRN_IVOR15
mdefine_line|#define SPRN_IVOR15&t;0x19F&t;/* Interrupt Vector Offset Register 15 */
DECL|macro|SPRN_ZPR
mdefine_line|#define SPRN_ZPR&t;0x3B0&t;/* Zone Protection Register (40x) */
DECL|macro|SPRN_MMUCR
mdefine_line|#define SPRN_MMUCR&t;0x3B2&t;/* MMU Control Register */
DECL|macro|SPRN_CCR0
mdefine_line|#define SPRN_CCR0&t;0x3B3&t;/* Core Configuration Register */
DECL|macro|SPRN_SGR
mdefine_line|#define SPRN_SGR&t;0x3B9&t;/* Storage Guarded Register */
DECL|macro|SPRN_DCWR
mdefine_line|#define SPRN_DCWR&t;0x3BA&t;/* Data Cache Write-thru Register */
DECL|macro|SPRN_SLER
mdefine_line|#define SPRN_SLER&t;0x3BB&t;/* Little-endian real mode */
DECL|macro|SPRN_SU0R
mdefine_line|#define SPRN_SU0R&t;0x3BC&t;/* &quot;User 0&quot; real mode (40x) */
DECL|macro|SPRN_DCMP
mdefine_line|#define SPRN_DCMP&t;0x3D1&t;/* Data TLB Compare Register */
DECL|macro|SPRN_ICDBDR
mdefine_line|#define SPRN_ICDBDR&t;0x3D3&t;/* Instruction Cache Debug Data Register */
DECL|macro|SPRN_EVPR
mdefine_line|#define SPRN_EVPR&t;0x3D6&t;/* Exception Vector Prefix Register */
DECL|macro|SPRN_PIT
mdefine_line|#define SPRN_PIT&t;0x3DB&t;/* Programmable Interval Timer */
DECL|macro|SPRN_DCCR
mdefine_line|#define SPRN_DCCR&t;0x3FA&t;/* Data Cache Cacheability Register */
DECL|macro|SPRN_ICCR
mdefine_line|#define SPRN_ICCR&t;0x3FB&t;/* Instruction Cache Cacheability Register */
multiline_comment|/*&n; * SPRs which have conflicting definitions on true Book E versus classic,&n; * or IBM 40x.&n; */
macro_line|#ifdef CONFIG_BOOKE
DECL|macro|SPRN_PID
mdefine_line|#define SPRN_PID&t;0x030&t;/* Process ID */
DECL|macro|SPRN_DEAR
mdefine_line|#define SPRN_DEAR&t;0x03D&t;/* Data Error Address Register */
DECL|macro|SPRN_ESR
mdefine_line|#define SPRN_ESR&t;0x03E&t;/* Exception Syndrome Register */
DECL|macro|SPRN_PIR
mdefine_line|#define SPRN_PIR&t;0x11E&t;/* Processor Identification Register */
DECL|macro|SPRN_DBSR
mdefine_line|#define SPRN_DBSR&t;0x130&t;/* Debug Status Register */
DECL|macro|SPRN_DBCR0
mdefine_line|#define SPRN_DBCR0&t;0x134&t;/* Debug Control Register 0 */
DECL|macro|SPRN_DBCR1
mdefine_line|#define SPRN_DBCR1&t;0x135&t;/* Debug Control Register 1 */
DECL|macro|SPRN_IAC1
mdefine_line|#define SPRN_IAC1&t;0x138&t;/* Instruction Address Compare 1 */
DECL|macro|SPRN_IAC2
mdefine_line|#define SPRN_IAC2&t;0x139&t;/* Instruction Address Compare 2 */
DECL|macro|SPRN_DAC1
mdefine_line|#define SPRN_DAC1&t;0x13C&t;/* Data Address Compare 1 */
DECL|macro|SPRN_DAC2
mdefine_line|#define SPRN_DAC2&t;0x13D&t;/* Data Address Compare 2 */
DECL|macro|SPRN_TSR
mdefine_line|#define SPRN_TSR&t;0x150&t;/* Timer Status Register */
DECL|macro|SPRN_TCR
mdefine_line|#define SPRN_TCR&t;0x154&t;/* Timer Control Register */
macro_line|#endif /* Book E */
macro_line|#ifdef CONFIG_40x
DECL|macro|SPRN_PID
mdefine_line|#define SPRN_PID&t;0x3B1&t;/* Process ID */
DECL|macro|SPRN_DBCR1
mdefine_line|#define SPRN_DBCR1&t;0x3BD&t;/* Debug Control Register 1 */&t;&t;
DECL|macro|SPRN_ESR
mdefine_line|#define SPRN_ESR&t;0x3D4&t;/* Exception Syndrome Register */
DECL|macro|SPRN_DEAR
mdefine_line|#define SPRN_DEAR&t;0x3D5&t;/* Data Error Address Register */
DECL|macro|SPRN_TSR
mdefine_line|#define SPRN_TSR&t;0x3D8&t;/* Timer Status Register */
DECL|macro|SPRN_TCR
mdefine_line|#define SPRN_TCR&t;0x3DA&t;/* Timer Control Register */
DECL|macro|SPRN_DBSR
mdefine_line|#define SPRN_DBSR&t;0x3F0&t;/* Debug Status Register */&t;&t;
DECL|macro|SPRN_DBCR0
mdefine_line|#define SPRN_DBCR0&t;0x3F2&t;/* Debug Control Register 0 */
macro_line|#endif
multiline_comment|/* Bit definitions for the DBSR. */
multiline_comment|/*&n; * DBSR bits which have conflicting definitions on true Book E versus IBM 40x.&n; */
macro_line|#ifdef CONFIG_BOOKE
DECL|macro|DBSR_IC
mdefine_line|#define DBSR_IC&t;&t;0x08000000&t;/* Instruction Completion */
DECL|macro|DBSR_TIE
mdefine_line|#define DBSR_TIE&t;0x01000000&t;/* Trap Instruction Event */
macro_line|#endif
macro_line|#ifdef CONFIG_40x
DECL|macro|DBSR_IC
mdefine_line|#define DBSR_IC&t;&t;0x80000000&t;/* Instruction Completion */
DECL|macro|DBSR_BT
mdefine_line|#define DBSR_BT&t;&t;0x40000000&t;/* Branch taken */
DECL|macro|DBSR_TIE
mdefine_line|#define DBSR_TIE&t;0x10000000&t;/* Trap Instruction debug Event */
macro_line|#endif
multiline_comment|/* Bit definitions related to the ESR. */
DECL|macro|ESR_MCI
mdefine_line|#define ESR_MCI&t;&t;0x80000000&t;/* Machine Check - Instruction */
DECL|macro|ESR_IMCP
mdefine_line|#define ESR_IMCP&t;0x80000000&t;/* Instr. Machine Check - Protection */
DECL|macro|ESR_IMCN
mdefine_line|#define ESR_IMCN&t;0x40000000&t;/* Instr. Machine Check - Non-config */
DECL|macro|ESR_IMCB
mdefine_line|#define ESR_IMCB&t;0x20000000&t;/* Instr. Machine Check - Bus error */
DECL|macro|ESR_IMCT
mdefine_line|#define ESR_IMCT&t;0x10000000&t;/* Instr. Machine Check - Timeout */
DECL|macro|ESR_PIL
mdefine_line|#define ESR_PIL&t;&t;0x08000000&t;/* Program Exception - Illegal */
DECL|macro|ESR_PPR
mdefine_line|#define ESR_PPR&t;&t;0x04000000&t;/* Program Exception - Priveleged */
DECL|macro|ESR_PTR
mdefine_line|#define ESR_PTR&t;&t;0x02000000&t;/* Program Exception - Trap */
DECL|macro|ESR_DST
mdefine_line|#define ESR_DST&t;&t;0x00800000&t;/* Storage Exception - Data miss */
DECL|macro|ESR_DIZ
mdefine_line|#define ESR_DIZ&t;&t;0x00400000&t;/* Storage Exception - Zone fault */
DECL|macro|ESR_ST
mdefine_line|#define ESR_ST&t;&t;0x00800000&t;/* Store Operation */
multiline_comment|/* Bit definitions related to the DBCR0. */
DECL|macro|DBCR0_EDM
mdefine_line|#define DBCR0_EDM&t;0x80000000&t;/* External Debug Mode */
DECL|macro|DBCR0_IDM
mdefine_line|#define DBCR0_IDM&t;0x40000000&t;/* Internal Debug Mode */
DECL|macro|DBCR0_RST
mdefine_line|#define DBCR0_RST&t;0x30000000&t;/* all the bits in the RST field */
DECL|macro|DBCR0_RST_SYSTEM
mdefine_line|#define DBCR0_RST_SYSTEM 0x30000000&t;/* System Reset */
DECL|macro|DBCR0_RST_CHIP
mdefine_line|#define DBCR0_RST_CHIP&t;0x20000000&t;/* Chip Reset */
DECL|macro|DBCR0_RST_CORE
mdefine_line|#define DBCR0_RST_CORE&t;0x10000000&t;/* Core Reset */
DECL|macro|DBCR0_RST_NONE
mdefine_line|#define DBCR0_RST_NONE&t;0x00000000&t;/* No Reset */
DECL|macro|DBCR0_IC
mdefine_line|#define DBCR0_IC&t;0x08000000&t;/* Instruction Completion */
DECL|macro|DBCR0_BT
mdefine_line|#define DBCR0_BT&t;0x04000000&t;/* Branch Taken */
DECL|macro|DBCR0_EDE
mdefine_line|#define DBCR0_EDE&t;0x02000000&t;/* Exception Debug Event */
DECL|macro|DBCR0_TDE
mdefine_line|#define DBCR0_TDE&t;0x01000000&t;/* TRAP Debug Event */
DECL|macro|DBCR0_IA1
mdefine_line|#define DBCR0_IA1&t;0x00800000&t;/* Instr Addr compare 1 enable */
DECL|macro|DBCR0_IA2
mdefine_line|#define DBCR0_IA2&t;0x00400000&t;/* Instr Addr compare 2 enable */
DECL|macro|DBCR0_IA12
mdefine_line|#define DBCR0_IA12&t;0x00200000&t;/* Instr Addr 1-2 range enable */
DECL|macro|DBCR0_IA12X
mdefine_line|#define DBCR0_IA12X&t;0x00100000&t;/* Instr Addr 1-2 range eXclusive */
DECL|macro|DBCR0_IA3
mdefine_line|#define DBCR0_IA3&t;0x00080000&t;/* Instr Addr compare 3 enable */
DECL|macro|DBCR0_IA4
mdefine_line|#define DBCR0_IA4&t;0x00040000&t;/* Instr Addr compare 4 enable */
DECL|macro|DBCR0_IA34
mdefine_line|#define DBCR0_IA34&t;0x00020000&t;/* Instr Addr 3-4 range Enable */
DECL|macro|DBCR0_IA34X
mdefine_line|#define DBCR0_IA34X&t;0x00010000&t;/* Instr Addr 3-4 range eXclusive */
DECL|macro|DBCR0_IA12T
mdefine_line|#define DBCR0_IA12T&t;0x00008000&t;/* Instr Addr 1-2 range Toggle */
DECL|macro|DBCR0_IA34T
mdefine_line|#define DBCR0_IA34T&t;0x00004000&t;/* Instr Addr 3-4 range Toggle */
DECL|macro|DBCR0_FT
mdefine_line|#define DBCR0_FT&t;0x00000001&t;/* Freeze Timers on debug event */
multiline_comment|/* Bit definitions related to the TCR. */
DECL|macro|TCR_WP
mdefine_line|#define TCR_WP(x)&t;(((x)&amp;0x3)&lt;&lt;30)&t;/* WDT Period */
DECL|macro|TCR_WP_MASK
mdefine_line|#define TCR_WP_MASK&t;TCR_WP(3)
DECL|macro|WP_2_17
mdefine_line|#define WP_2_17&t;&t;0&t;&t;/* 2^17 clocks */
DECL|macro|WP_2_21
mdefine_line|#define WP_2_21&t;&t;1&t;&t;/* 2^21 clocks */
DECL|macro|WP_2_25
mdefine_line|#define WP_2_25&t;&t;2&t;&t;/* 2^25 clocks */
DECL|macro|WP_2_29
mdefine_line|#define WP_2_29&t;&t;3&t;&t;/* 2^29 clocks */
DECL|macro|TCR_WRC
mdefine_line|#define TCR_WRC(x)&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Control */
DECL|macro|TCR_WRC_MASK
mdefine_line|#define TCR_WRC_MASK&t;TCR_WRC(3)
DECL|macro|WRC_NONE
mdefine_line|#define WRC_NONE&t;0&t;&t;/* No reset will occur */
DECL|macro|WRC_CORE
mdefine_line|#define WRC_CORE&t;1&t;&t;/* Core reset will occur */
DECL|macro|WRC_CHIP
mdefine_line|#define WRC_CHIP&t;2&t;&t;/* Chip reset will occur */
DECL|macro|WRC_SYSTEM
mdefine_line|#define WRC_SYSTEM&t;3&t;&t;/* System reset will occur */
DECL|macro|TCR_WIE
mdefine_line|#define TCR_WIE&t;&t;0x08000000&t;/* WDT Interrupt Enable */
DECL|macro|TCR_PIE
mdefine_line|#define TCR_PIE&t;&t;0x04000000&t;/* PIT Interrupt Enable */
DECL|macro|TCR_DIE
mdefine_line|#define TCR_DIE&t;&t;TCR_PIE&t;&t;/* DEC Interrupt Enable */
DECL|macro|TCR_FP
mdefine_line|#define TCR_FP(x)&t;(((x)&amp;0x3)&lt;&lt;24)&t;/* FIT Period */
DECL|macro|TCR_FP_MASK
mdefine_line|#define TCR_FP_MASK&t;TCR_FP(3)
DECL|macro|FP_2_9
mdefine_line|#define FP_2_9&t;&t;0&t;&t;/* 2^9 clocks */
DECL|macro|FP_2_13
mdefine_line|#define FP_2_13&t;&t;1&t;&t;/* 2^13 clocks */
DECL|macro|FP_2_17
mdefine_line|#define FP_2_17&t;&t;2&t;&t;/* 2^17 clocks */
DECL|macro|FP_2_21
mdefine_line|#define FP_2_21&t;&t;3&t;&t;/* 2^21 clocks */
DECL|macro|TCR_FIE
mdefine_line|#define TCR_FIE&t;&t;0x00800000&t;/* FIT Interrupt Enable */
DECL|macro|TCR_ARE
mdefine_line|#define TCR_ARE&t;&t;0x00400000&t;/* Auto Reload Enable */
multiline_comment|/* Bit definitions for the TSR. */
DECL|macro|TSR_ENW
mdefine_line|#define TSR_ENW&t;&t;0x80000000&t;/* Enable Next Watchdog */
DECL|macro|TSR_WIS
mdefine_line|#define TSR_WIS&t;&t;0x40000000&t;/* WDT Interrupt Status */
DECL|macro|TSR_WRS
mdefine_line|#define TSR_WRS(x)&t;(((x)&amp;0x3)&lt;&lt;28)&t;/* WDT Reset Status */
DECL|macro|WRS_NONE
mdefine_line|#define WRS_NONE&t;0&t;&t;/* No WDT reset occurred */
DECL|macro|WRS_CORE
mdefine_line|#define WRS_CORE&t;1&t;&t;/* WDT forced core reset */
DECL|macro|WRS_CHIP
mdefine_line|#define WRS_CHIP&t;2&t;&t;/* WDT forced chip reset */
DECL|macro|WRS_SYSTEM
mdefine_line|#define WRS_SYSTEM&t;3&t;&t;/* WDT forced system reset */
DECL|macro|TSR_PIS
mdefine_line|#define TSR_PIS&t;&t;0x08000000&t;/* PIT Interrupt Status */
DECL|macro|TSR_DIS
mdefine_line|#define TSR_DIS&t;&t;TSR_PIS&t;&t;/* DEC Interrupt Status */
DECL|macro|TSR_FIS
mdefine_line|#define TSR_FIS&t;&t;0x04000000&t;/* FIT Interrupt Status */
multiline_comment|/* Bit definitions for the DCCR. */
DECL|macro|DCCR_NOCACHE
mdefine_line|#define DCCR_NOCACHE&t;0&t;&t;/* Noncacheable */
DECL|macro|DCCR_CACHE
mdefine_line|#define DCCR_CACHE&t;1&t;&t;/* Cacheable */
multiline_comment|/* Bit definitions for DCWR. */
DECL|macro|DCWR_COPY
mdefine_line|#define DCWR_COPY&t;0&t;&t;/* Copy-back */
DECL|macro|DCWR_WRITE
mdefine_line|#define DCWR_WRITE&t;1&t;&t;/* Write-through */
multiline_comment|/* Bit definitions for ICCR. */
DECL|macro|ICCR_NOCACHE
mdefine_line|#define ICCR_NOCACHE&t;0&t;&t;/* Noncacheable */
DECL|macro|ICCR_CACHE
mdefine_line|#define ICCR_CACHE&t;1&t;&t;/* Cacheable */
multiline_comment|/* Bit definitions for SGR. */
DECL|macro|SGR_NORMAL
mdefine_line|#define SGR_NORMAL&t;0&t;&t;/* Speculative fetching allowed. */
DECL|macro|SGR_GUARDED
mdefine_line|#define SGR_GUARDED&t;1&t;&t;/* Speculative fetching disallowed. */
multiline_comment|/* Short-hand for various SPRs. */
DECL|macro|CSRR0
mdefine_line|#define CSRR0&t;SPRN_CSRR0&t;/* Critical Save and Restore Register 0 */
DECL|macro|CSRR1
mdefine_line|#define CSRR1&t;SPRN_CSRR1&t;/* Critical Save and Restore Register 1 */
DECL|macro|DCMP
mdefine_line|#define DCMP&t;SPRN_DCMP&t;/* Data TLB Compare Register */
DECL|macro|SPRG4R
mdefine_line|#define SPRG4R&t;SPRN_SPRG4R&t;/* Supervisor Private Registers */
DECL|macro|SPRG5R
mdefine_line|#define SPRG5R&t;SPRN_SPRG5R
DECL|macro|SPRG6R
mdefine_line|#define SPRG6R&t;SPRN_SPRG6R
DECL|macro|SPRG7R
mdefine_line|#define SPRG7R&t;SPRN_SPRG7R
DECL|macro|SPRG4W
mdefine_line|#define SPRG4W&t;SPRN_SPRG4W
DECL|macro|SPRG5W
mdefine_line|#define SPRG5W&t;SPRN_SPRG5W
DECL|macro|SPRG6W
mdefine_line|#define SPRG6W&t;SPRN_SPRG6W
DECL|macro|SPRG7W
mdefine_line|#define SPRG7W&t;SPRN_SPRG7W
DECL|macro|TBRL
mdefine_line|#define TBRL&t;SPRN_TBRL&t;/* Time Base Read Lower Register */
DECL|macro|TBRU
mdefine_line|#define TBRU&t;SPRN_TBRU&t;/* Time Base Read Upper Register */
DECL|macro|TBWL
mdefine_line|#define TBWL&t;SPRN_TBWL&t;/* Time Base Write Lower Register */
DECL|macro|TBWU
mdefine_line|#define TBWU&t;SPRN_TBWU&t;/* Time Base Write Upper Register */
multiline_comment|/*&n; * The IBM-403 is an even more odd special case, as it is much&n; * older than the IBM-405 series.  We put these down here incase someone&n; * wishes to support these machines again.&n; */
macro_line|#ifdef CONFIG_403GCX
multiline_comment|/* Special Purpose Registers (SPRNs)*/
DECL|macro|SPRN_TBHU
mdefine_line|#define SPRN_TBHU&t;0x3CC&t;/* Time Base High User-mode */
DECL|macro|SPRN_TBLU
mdefine_line|#define SPRN_TBLU&t;0x3CD&t;/* Time Base Low User-mode */
DECL|macro|SPRN_CDBCR
mdefine_line|#define SPRN_CDBCR&t;0x3D7&t;/* Cache Debug Control Register */
DECL|macro|SPRN_TBHI
mdefine_line|#define SPRN_TBHI&t;0x3DC&t;/* Time Base High */
DECL|macro|SPRN_TBLO
mdefine_line|#define SPRN_TBLO&t;0x3DD&t;/* Time Base Low */
DECL|macro|SPRN_DBCR
mdefine_line|#define SPRN_DBCR&t;0x3F2&t;/* Debug Control Regsiter */
DECL|macro|SPRN_PBL1
mdefine_line|#define SPRN_PBL1&t;0x3FC&t;/* Protection Bound Lower 1 */
DECL|macro|SPRN_PBL2
mdefine_line|#define SPRN_PBL2&t;0x3FE&t;/* Protection Bound Lower 2 */
DECL|macro|SPRN_PBU1
mdefine_line|#define SPRN_PBU1&t;0x3FD&t;/* Protection Bound Upper 1 */
DECL|macro|SPRN_PBU2
mdefine_line|#define SPRN_PBU2&t;0x3FF&t;/* Protection Bound Upper 2 */
multiline_comment|/* Bit definitions for the DBCR. */
DECL|macro|DBCR_EDM
mdefine_line|#define DBCR_EDM&t;DBCR0_EDM
DECL|macro|DBCR_IDM
mdefine_line|#define DBCR_IDM&t;DBCR0_IDM
DECL|macro|DBCR_RST
mdefine_line|#define DBCR_RST(x)&t;(((x) &amp; 0x3) &lt;&lt; 28)
DECL|macro|DBCR_RST_NONE
mdefine_line|#define DBCR_RST_NONE&t;0
DECL|macro|DBCR_RST_CORE
mdefine_line|#define DBCR_RST_CORE&t;1
DECL|macro|DBCR_RST_CHIP
mdefine_line|#define DBCR_RST_CHIP&t;2
DECL|macro|DBCR_RST_SYSTEM
mdefine_line|#define DBCR_RST_SYSTEM&t;3
DECL|macro|DBCR_IC
mdefine_line|#define DBCR_IC&t;&t;DBCR0_IC&t;/* Instruction Completion Debug Evnt */
DECL|macro|DBCR_BT
mdefine_line|#define DBCR_BT&t;&t;DBCR0_BT&t;/* Branch Taken Debug Event */
DECL|macro|DBCR_EDE
mdefine_line|#define DBCR_EDE&t;DBCR0_EDE&t;/* Exception Debug Event */
DECL|macro|DBCR_TDE
mdefine_line|#define DBCR_TDE&t;DBCR0_TDE&t;/* TRAP Debug Event */
DECL|macro|DBCR_FER
mdefine_line|#define DBCR_FER&t;0x00F80000&t;/* First Events Remaining Mask */
DECL|macro|DBCR_FT
mdefine_line|#define DBCR_FT&t;&t;0x00040000&t;/* Freeze Timers on Debug Event */
DECL|macro|DBCR_IA1
mdefine_line|#define DBCR_IA1&t;0x00020000&t;/* Instr. Addr. Compare 1 Enable */
DECL|macro|DBCR_IA2
mdefine_line|#define DBCR_IA2&t;0x00010000&t;/* Instr. Addr. Compare 2 Enable */
DECL|macro|DBCR_D1R
mdefine_line|#define DBCR_D1R&t;0x00008000&t;/* Data Addr. Compare 1 Read Enable */
DECL|macro|DBCR_D1W
mdefine_line|#define DBCR_D1W&t;0x00004000&t;/* Data Addr. Compare 1 Write Enable */
DECL|macro|DBCR_D1S
mdefine_line|#define DBCR_D1S(x)&t;(((x) &amp; 0x3) &lt;&lt; 12)&t;/* Data Adrr. Compare 1 Size */
DECL|macro|DAC_BYTE
mdefine_line|#define DAC_BYTE&t;0
DECL|macro|DAC_HALF
mdefine_line|#define DAC_HALF&t;1
DECL|macro|DAC_WORD
mdefine_line|#define DAC_WORD&t;2
DECL|macro|DAC_QUAD
mdefine_line|#define DAC_QUAD&t;3
DECL|macro|DBCR_D2R
mdefine_line|#define DBCR_D2R&t;0x00000800&t;/* Data Addr. Compare 2 Read Enable */
DECL|macro|DBCR_D2W
mdefine_line|#define DBCR_D2W&t;0x00000400&t;/* Data Addr. Compare 2 Write Enable */
DECL|macro|DBCR_D2S
mdefine_line|#define DBCR_D2S(x)&t;(((x) &amp; 0x3) &lt;&lt; 8)&t;/* Data Addr. Compare 2 Size */
DECL|macro|DBCR_SBT
mdefine_line|#define DBCR_SBT&t;0x00000040&t;/* Second Branch Taken Debug Event */
DECL|macro|DBCR_SED
mdefine_line|#define DBCR_SED&t;0x00000020&t;/* Second Exception Debug Event */
DECL|macro|DBCR_STD
mdefine_line|#define DBCR_STD&t;0x00000010&t;/* Second Trap Debug Event */
DECL|macro|DBCR_SIA
mdefine_line|#define DBCR_SIA&t;0x00000008&t;/* Second IAC Enable */
DECL|macro|DBCR_SDA
mdefine_line|#define DBCR_SDA&t;0x00000004&t;/* Second DAC Enable */
DECL|macro|DBCR_JOI
mdefine_line|#define DBCR_JOI&t;0x00000002&t;/* JTAG Serial Outbound Int. Enable */
DECL|macro|DBCR_JII
mdefine_line|#define DBCR_JII&t;0x00000001&t;/* JTAG Serial Inbound Int. Enable */
macro_line|#endif /* 403GCX */
macro_line|#endif /* __ASM_PPC_REG_BOOKE_H__ */
macro_line|#endif /* __KERNEL__ */
eof
