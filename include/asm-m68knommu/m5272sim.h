multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m5272sim.h -- ColdFire 5272 System Integration Module support.&n; *&n; *&t;(C) Copyright 1999, Greg Ungerer (gerg@snapgear.com)&n; * &t;(C) Copyright 2000, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m5272sim_h
DECL|macro|m5272sim_h
mdefine_line|#define&t;m5272sim_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the 5272 SIM register set addresses.&n; */
DECL|macro|MCFSIM_SCR
mdefine_line|#define&t;MCFSIM_SCR&t;&t;0x04&t;&t;/* SIM Config reg (r/w) */
DECL|macro|MCFSIM_SPR
mdefine_line|#define&t;MCFSIM_SPR&t;&t;0x06&t;&t;/* System Protection reg (r/w)*/
DECL|macro|MCFSIM_PMR
mdefine_line|#define&t;MCFSIM_PMR&t;&t;0x08&t;&t;/* Power Management reg (r/w) */
DECL|macro|MCFSIM_APMR
mdefine_line|#define&t;MCFSIM_APMR&t;&t;0x0e&t;&t;/* Active Low Power reg (r/w) */
DECL|macro|MCFSIM_DIR
mdefine_line|#define&t;MCFSIM_DIR&t;&t;0x10&t;&t;/* Device Identity reg (r/w) */
DECL|macro|MCFSIM_ICR1
mdefine_line|#define&t;MCFSIM_ICR1&t;&t;0x20&t;&t;/* Intr Ctrl reg 1 (r/w) */
DECL|macro|MCFSIM_ICR2
mdefine_line|#define&t;MCFSIM_ICR2&t;&t;0x24&t;&t;/* Intr Ctrl reg 2 (r/w) */
DECL|macro|MCFSIM_ICR3
mdefine_line|#define&t;MCFSIM_ICR3&t;&t;0x28&t;&t;/* Intr Ctrl reg 3 (r/w) */
DECL|macro|MCFSIM_ICR4
mdefine_line|#define&t;MCFSIM_ICR4&t;&t;0x2c&t;&t;/* Intr Ctrl reg 4 (r/w) */
DECL|macro|MCFSIM_ISR
mdefine_line|#define MCFSIM_ISR&t;&t;0x30&t;&t;/* Interrupt Source reg (r/w) */
DECL|macro|MCFSIM_PITR
mdefine_line|#define MCFSIM_PITR&t;&t;0x34&t;&t;/* Interrupt Transition (r/w) */
DECL|macro|MCFSIM_PIWR
mdefine_line|#define&t;MCFSIM_PIWR&t;&t;0x38&t;&t;/* Interrupt Wakeup reg (r/w) */
DECL|macro|MCFSIM_PIVR
mdefine_line|#define&t;MCFSIM_PIVR&t;&t;0x3f&t;&t;/* Interrupt Vector reg (r/w( */
DECL|macro|MCFSIM_WRRR
mdefine_line|#define&t;MCFSIM_WRRR&t;&t;0x280&t;&t;/* Watchdog reference (r/w) */
DECL|macro|MCFSIM_WIRR
mdefine_line|#define&t;MCFSIM_WIRR&t;&t;0x284&t;&t;/* Watchdog interrupt (r/w) */
DECL|macro|MCFSIM_WCR
mdefine_line|#define&t;MCFSIM_WCR&t;&t;0x288&t;&t;/* Watchdog counter (r/w) */
DECL|macro|MCFSIM_WER
mdefine_line|#define&t;MCFSIM_WER&t;&t;0x28c&t;&t;/* Watchdog event (r/w) */
DECL|macro|MCFSIM_CSBR0
mdefine_line|#define&t;MCFSIM_CSBR0&t;&t;0x40&t;&t;/* CS0 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR0
mdefine_line|#define&t;MCFSIM_CSOR0&t;&t;0x44&t;&t;/* CS0 Option (r/w) */
DECL|macro|MCFSIM_CSBR1
mdefine_line|#define&t;MCFSIM_CSBR1&t;&t;0x48&t;&t;/* CS1 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR1
mdefine_line|#define&t;MCFSIM_CSOR1&t;&t;0x4c&t;&t;/* CS1 Option (r/w) */
DECL|macro|MCFSIM_CSBR2
mdefine_line|#define&t;MCFSIM_CSBR2&t;&t;0x50&t;&t;/* CS2 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR2
mdefine_line|#define&t;MCFSIM_CSOR2&t;&t;0x54&t;&t;/* CS2 Option (r/w) */
DECL|macro|MCFSIM_CSBR3
mdefine_line|#define&t;MCFSIM_CSBR3&t;&t;0x58&t;&t;/* CS3 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR3
mdefine_line|#define&t;MCFSIM_CSOR3&t;&t;0x5c&t;&t;/* CS3 Option (r/w) */
DECL|macro|MCFSIM_CSBR4
mdefine_line|#define&t;MCFSIM_CSBR4&t;&t;0x60&t;&t;/* CS4 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR4
mdefine_line|#define&t;MCFSIM_CSOR4&t;&t;0x64&t;&t;/* CS4 Option (r/w) */
DECL|macro|MCFSIM_CSBR5
mdefine_line|#define&t;MCFSIM_CSBR5&t;&t;0x68&t;&t;/* CS5 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR5
mdefine_line|#define&t;MCFSIM_CSOR5&t;&t;0x6c&t;&t;/* CS5 Option (r/w) */
DECL|macro|MCFSIM_CSBR6
mdefine_line|#define&t;MCFSIM_CSBR6&t;&t;0x70&t;&t;/* CS6 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR6
mdefine_line|#define&t;MCFSIM_CSOR6&t;&t;0x74&t;&t;/* CS6 Option (r/w) */
DECL|macro|MCFSIM_CSBR7
mdefine_line|#define&t;MCFSIM_CSBR7&t;&t;0x78&t;&t;/* CS7 Base Address (r/w) */
DECL|macro|MCFSIM_CSOR7
mdefine_line|#define&t;MCFSIM_CSOR7&t;&t;0x7c&t;&t;/* CS7 Option (r/w) */
DECL|macro|MCFSIM_SDCR
mdefine_line|#define&t;MCFSIM_SDCR&t;&t;0x180&t;&t;/* SDRAM Configuration (r/w) */
DECL|macro|MCFSIM_SDTR
mdefine_line|#define&t;MCFSIM_SDTR&t;&t;0x184&t;&t;/* SDRAM Timing (r/w) */
DECL|macro|MCFSIM_DCAR0
mdefine_line|#define&t;MCFSIM_DCAR0&t;&t;0x4c&t;&t;/* DRAM 0 Address reg(r/w) */
DECL|macro|MCFSIM_DCMR0
mdefine_line|#define&t;MCFSIM_DCMR0&t;&t;0x50&t;&t;/* DRAM 0 Mask reg (r/w) */
DECL|macro|MCFSIM_DCCR0
mdefine_line|#define&t;MCFSIM_DCCR0&t;&t;0x57&t;&t;/* DRAM 0 Control reg (r/w) */
DECL|macro|MCFSIM_DCAR1
mdefine_line|#define&t;MCFSIM_DCAR1&t;&t;0x58&t;&t;/* DRAM 1 Address reg (r/w) */
DECL|macro|MCFSIM_DCMR1
mdefine_line|#define&t;MCFSIM_DCMR1&t;&t;0x5c&t;&t;/* DRAM 1 Mask reg (r/w) */
DECL|macro|MCFSIM_DCCR1
mdefine_line|#define&t;MCFSIM_DCCR1&t;&t;0x63&t;&t;/* DRAM 1 Control reg (r/w) */
DECL|macro|MCFSIM_PACNT
mdefine_line|#define&t;MCFSIM_PACNT&t;&t;0x80&t;&t;/* Port A Control (r/w) */
DECL|macro|MCFSIM_PADDR
mdefine_line|#define&t;MCFSIM_PADDR&t;&t;0x84&t;&t;/* Port A Direction (r/w) */
DECL|macro|MCFSIM_PADAT
mdefine_line|#define&t;MCFSIM_PADAT&t;&t;0x86&t;&t;/* Port A Data (r/w) */
DECL|macro|MCFSIM_PBCNT
mdefine_line|#define&t;MCFSIM_PBCNT&t;&t;0x88&t;&t;/* Port B Control (r/w) */
DECL|macro|MCFSIM_PBDDR
mdefine_line|#define&t;MCFSIM_PBDDR&t;&t;0x8c&t;&t;/* Port B Direction (r/w) */
DECL|macro|MCFSIM_PBDAT
mdefine_line|#define&t;MCFSIM_PBDAT&t;&t;0x8e&t;&t;/* Port B Data (r/w) */
DECL|macro|MCFSIM_PCDDR
mdefine_line|#define&t;MCFSIM_PCDDR&t;&t;0x94&t;&t;/* Port C Direction (r/w) */
DECL|macro|MCFSIM_PCDAT
mdefine_line|#define&t;MCFSIM_PCDAT&t;&t;0x96&t;&t;/* Port C Data (r/w) */
DECL|macro|MCFSIM_PDCNT
mdefine_line|#define&t;MCFSIM_PDCNT&t;&t;0x98&t;&t;/* Port D Control (r/w) */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m5272sim_h */
eof
