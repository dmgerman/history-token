multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m5206sim.h -- ColdFire 5206 System Integration Module support.&n; *&n; *&t;(C) Copyright 1999, Greg Ungerer (gerg@snapgear.com)&n; * &t;(C) Copyright 2000, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m5206sim_h
DECL|macro|m5206sim_h
mdefine_line|#define&t;m5206sim_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the 5206 SIM register set addresses.&n; */
DECL|macro|MCFSIM_SIMR
mdefine_line|#define&t;MCFSIM_SIMR&t;&t;0x03&t;&t;/* SIM Config reg (r/w) */
DECL|macro|MCFSIM_ICR1
mdefine_line|#define&t;MCFSIM_ICR1&t;&t;0x14&t;&t;/* Intr Ctrl reg 1 (r/w) */
DECL|macro|MCFSIM_ICR2
mdefine_line|#define&t;MCFSIM_ICR2&t;&t;0x15&t;&t;/* Intr Ctrl reg 2 (r/w) */
DECL|macro|MCFSIM_ICR3
mdefine_line|#define&t;MCFSIM_ICR3&t;&t;0x16&t;&t;/* Intr Ctrl reg 3 (r/w) */
DECL|macro|MCFSIM_ICR4
mdefine_line|#define&t;MCFSIM_ICR4&t;&t;0x17&t;&t;/* Intr Ctrl reg 4 (r/w) */
DECL|macro|MCFSIM_ICR5
mdefine_line|#define&t;MCFSIM_ICR5&t;&t;0x18&t;&t;/* Intr Ctrl reg 5 (r/w) */
DECL|macro|MCFSIM_ICR6
mdefine_line|#define&t;MCFSIM_ICR6&t;&t;0x19&t;&t;/* Intr Ctrl reg 6 (r/w) */
DECL|macro|MCFSIM_ICR7
mdefine_line|#define&t;MCFSIM_ICR7&t;&t;0x1a&t;&t;/* Intr Ctrl reg 7 (r/w) */
DECL|macro|MCFSIM_ICR8
mdefine_line|#define&t;MCFSIM_ICR8&t;&t;0x1b&t;&t;/* Intr Ctrl reg 8 (r/w) */
DECL|macro|MCFSIM_ICR9
mdefine_line|#define&t;MCFSIM_ICR9&t;&t;0x1c&t;&t;/* Intr Ctrl reg 9 (r/w) */
DECL|macro|MCFSIM_ICR10
mdefine_line|#define&t;MCFSIM_ICR10&t;&t;0x1d&t;&t;/* Intr Ctrl reg 10 (r/w) */
DECL|macro|MCFSIM_ICR11
mdefine_line|#define&t;MCFSIM_ICR11&t;&t;0x1e&t;&t;/* Intr Ctrl reg 11 (r/w) */
DECL|macro|MCFSIM_ICR12
mdefine_line|#define&t;MCFSIM_ICR12&t;&t;0x1f&t;&t;/* Intr Ctrl reg 12 (r/w) */
DECL|macro|MCFSIM_ICR13
mdefine_line|#define&t;MCFSIM_ICR13&t;&t;0x20&t;&t;/* Intr Ctrl reg 13 (r/w) */
macro_line|#ifdef CONFIG_M5206e
DECL|macro|MCFSIM_ICR14
mdefine_line|#define&t;MCFSIM_ICR14&t;&t;0x21&t;&t;/* Intr Ctrl reg 14 (r/w) */
DECL|macro|MCFSIM_ICR15
mdefine_line|#define&t;MCFSIM_ICR15&t;&t;0x22&t;&t;/* Intr Ctrl reg 15 (r/w) */
macro_line|#endif
DECL|macro|MCFSIM_IMR
mdefine_line|#define MCFSIM_IMR&t;&t;0x36&t;&t;/* Interrupt Mask reg (r/w) */
DECL|macro|MCFSIM_IPR
mdefine_line|#define MCFSIM_IPR&t;&t;0x3a&t;&t;/* Interrupt Pend reg (r/w) */
DECL|macro|MCFSIM_RSR
mdefine_line|#define&t;MCFSIM_RSR&t;&t;0x40&t;&t;/* Reset Status reg (r/w) */
DECL|macro|MCFSIM_SYPCR
mdefine_line|#define&t;MCFSIM_SYPCR&t;&t;0x41&t;&t;/* System Protection reg (r/w)*/
DECL|macro|MCFSIM_SWIVR
mdefine_line|#define&t;MCFSIM_SWIVR&t;&t;0x42&t;&t;/* SW Watchdog intr reg (r/w) */
DECL|macro|MCFSIM_SWSR
mdefine_line|#define&t;MCFSIM_SWSR&t;&t;0x43&t;&t;/* SW Watchdog service (r/w) */
DECL|macro|MCFSIM_DCRR
mdefine_line|#define&t;MCFSIM_DCRR&t;&t;0x46&t;&t;/* DRAM Refresh reg (r/w) */
DECL|macro|MCFSIM_DCTR
mdefine_line|#define&t;MCFSIM_DCTR&t;&t;0x4a&t;&t;/* DRAM Timing reg (r/w) */
DECL|macro|MCFSIM_DAR0
mdefine_line|#define&t;MCFSIM_DAR0&t;&t;0x4c&t;&t;/* DRAM 0 Address reg(r/w) */
DECL|macro|MCFSIM_DMR0
mdefine_line|#define&t;MCFSIM_DMR0&t;&t;0x50&t;&t;/* DRAM 0 Mask reg (r/w) */
DECL|macro|MCFSIM_DCR0
mdefine_line|#define&t;MCFSIM_DCR0&t;&t;0x57&t;&t;/* DRAM 0 Control reg (r/w) */
DECL|macro|MCFSIM_DAR1
mdefine_line|#define&t;MCFSIM_DAR1&t;&t;0x58&t;&t;/* DRAM 1 Address reg (r/w) */
DECL|macro|MCFSIM_DMR1
mdefine_line|#define&t;MCFSIM_DMR1&t;&t;0x5c&t;&t;/* DRAM 1 Mask reg (r/w) */
DECL|macro|MCFSIM_DCR1
mdefine_line|#define&t;MCFSIM_DCR1&t;&t;0x63&t;&t;/* DRAM 1 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR0
mdefine_line|#define&t;MCFSIM_CSAR0&t;&t;0x64&t;&t;/* CS 0 Address 0 reg (r/w) */
DECL|macro|MCFSIM_CSMR0
mdefine_line|#define&t;MCFSIM_CSMR0&t;&t;0x68&t;&t;/* CS 0 Mask 0 reg (r/w) */
DECL|macro|MCFSIM_CSCR0
mdefine_line|#define&t;MCFSIM_CSCR0&t;&t;0x6e&t;&t;/* CS 0 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR1
mdefine_line|#define&t;MCFSIM_CSAR1&t;&t;0x70&t;&t;/* CS 1 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR1
mdefine_line|#define&t;MCFSIM_CSMR1&t;&t;0x74&t;&t;/* CS 1 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR1
mdefine_line|#define&t;MCFSIM_CSCR1&t;&t;0x7a&t;&t;/* CS 1 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR2
mdefine_line|#define&t;MCFSIM_CSAR2&t;&t;0x7c&t;&t;/* CS 2 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR2
mdefine_line|#define&t;MCFSIM_CSMR2&t;&t;0x80&t;&t;/* CS 2 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR2
mdefine_line|#define&t;MCFSIM_CSCR2&t;&t;0x86&t;&t;/* CS 2 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR3
mdefine_line|#define&t;MCFSIM_CSAR3&t;&t;0x88&t;&t;/* CS 3 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR3
mdefine_line|#define&t;MCFSIM_CSMR3&t;&t;0x8c&t;&t;/* CS 3 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR3
mdefine_line|#define&t;MCFSIM_CSCR3&t;&t;0x92&t;&t;/* CS 3 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR4
mdefine_line|#define&t;MCFSIM_CSAR4&t;&t;0x94&t;&t;/* CS 4 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR4
mdefine_line|#define&t;MCFSIM_CSMR4&t;&t;0x98&t;&t;/* CS 4 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR4
mdefine_line|#define&t;MCFSIM_CSCR4&t;&t;0x9e&t;&t;/* CS 4 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR5
mdefine_line|#define&t;MCFSIM_CSAR5&t;&t;0xa0&t;&t;/* CS 5 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR5
mdefine_line|#define&t;MCFSIM_CSMR5&t;&t;0xa4&t;&t;/* CS 5 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR5
mdefine_line|#define&t;MCFSIM_CSCR5&t;&t;0xaa&t;&t;/* CS 5 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR6
mdefine_line|#define&t;MCFSIM_CSAR6&t;&t;0xac&t;&t;/* CS 6 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR6
mdefine_line|#define&t;MCFSIM_CSMR6&t;&t;0xb0&t;&t;/* CS 6 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR6
mdefine_line|#define&t;MCFSIM_CSCR6&t;&t;0xb6&t;&t;/* CS 6 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR7
mdefine_line|#define&t;MCFSIM_CSAR7&t;&t;0xb8&t;&t;/* CS 7 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR7
mdefine_line|#define&t;MCFSIM_CSMR7&t;&t;0xbc&t;&t;/* CS 7 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR7
mdefine_line|#define&t;MCFSIM_CSCR7&t;&t;0xc2&t;&t;/* CS 7 Control reg (r/w) */
DECL|macro|MCFSIM_DMCR
mdefine_line|#define&t;MCFSIM_DMCR&t;&t;0xc6&t;&t;/* Default control */
macro_line|#ifdef CONFIG_M5206e
DECL|macro|MCFSIM_PAR
mdefine_line|#define&t;MCFSIM_PAR&t;&t;0xca&t;&t;/* Pin Assignment reg (r/w) */
macro_line|#else
DECL|macro|MCFSIM_PAR
mdefine_line|#define&t;MCFSIM_PAR&t;&t;0xcb&t;&t;/* Pin Assignment reg (r/w) */
macro_line|#endif
DECL|macro|MCFSIM_PADDR
mdefine_line|#define&t;MCFSIM_PADDR&t;&t;0x1c5&t;&t;/* Parallel Direction (r/w) */
DECL|macro|MCFSIM_PADAT
mdefine_line|#define&t;MCFSIM_PADAT&t;&t;0x1c9&t;&t;/* Parallel Port Value (r/w) */
multiline_comment|/*&n; *&t;Some symbol defines for the Parallel Port Pin Assignment Register&n; */
macro_line|#ifdef CONFIG_M5206e
DECL|macro|MCFSIM_PAR_DREQ0
mdefine_line|#define MCFSIM_PAR_DREQ0        0x100           /* Set to select DREQ0 input */
multiline_comment|/* Clear to select T0 input */
DECL|macro|MCFSIM_PAR_DREQ1
mdefine_line|#define MCFSIM_PAR_DREQ1        0x200           /* Select DREQ1 input */
multiline_comment|/* Clear to select T0 output */
macro_line|#endif
multiline_comment|/*&n; *&t;Some symbol defines for the Interrupt Control Register&n; */
DECL|macro|MCFSIM_SWDICR
mdefine_line|#define&t;MCFSIM_SWDICR&t;&t;MCFSIM_ICR8&t;/* Watchdog timer ICR */
DECL|macro|MCFSIM_TIMER1ICR
mdefine_line|#define&t;MCFSIM_TIMER1ICR&t;MCFSIM_ICR9&t;/* Timer 1 ICR */
DECL|macro|MCFSIM_TIMER2ICR
mdefine_line|#define&t;MCFSIM_TIMER2ICR&t;MCFSIM_ICR10&t;/* Timer 2 ICR */
DECL|macro|MCFSIM_UART1ICR
mdefine_line|#define&t;MCFSIM_UART1ICR&t;&t;MCFSIM_ICR12&t;/* UART 1 ICR */
DECL|macro|MCFSIM_UART2ICR
mdefine_line|#define&t;MCFSIM_UART2ICR&t;&t;MCFSIM_ICR13&t;/* UART 2 ICR */
macro_line|#ifdef CONFIG_M5206e
DECL|macro|MCFSIM_DMA1ICR
mdefine_line|#define&t;MCFSIM_DMA1ICR&t;&t;MCFSIM_ICR14&t;/* DMA 1 ICR */
DECL|macro|MCFSIM_DMA2ICR
mdefine_line|#define&t;MCFSIM_DMA2ICR&t;&t;MCFSIM_ICR15&t;/* DMA 2 ICR */
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e)
DECL|macro|MCFSIM_IMR_MASKALL
mdefine_line|#define&t;MCFSIM_IMR_MASKALL&t;0xfffe&t;&t;/* All SIM intr sources */
macro_line|#endif
multiline_comment|/*&n; *&t;Macro to get and set IMR register. It is 16 bits on the 5206.&n; */
DECL|macro|mcf_getimr
mdefine_line|#define&t;mcf_getimr()&t;&t;&bslash;&n;&t;*((volatile unsigned short *) (MCF_MBAR + MCFSIM_IMR))
DECL|macro|mcf_setimr
mdefine_line|#define&t;mcf_setimr(imr)&t;&t;&bslash;&n;&t;*((volatile unsigned short *) (MCF_MBAR + MCFSIM_IMR)) = (imr)
DECL|macro|mcf_getipr
mdefine_line|#define&t;mcf_getipr()&t;&t;&bslash;&n;&t;*((volatile unsigned short *) (MCF_MBAR + MCFSIM_IPR))
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m5206sim_h */
eof
