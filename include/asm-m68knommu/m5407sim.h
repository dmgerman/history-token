multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m5407sim.h -- ColdFire 5407 System Integration Module support.&n; *&n; *&t;(C) Copyright 2000,  Lineo (www.lineo.com)&n; *&t;(C) Copyright 1999,  Moreton Bay Ventures Pty Ltd.&n; *&n; *      Modified by David W. Miller for the MCF5307 Eval Board.&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m5407sim_h
DECL|macro|m5407sim_h
mdefine_line|#define&t;m5407sim_h
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Define the 5407 SIM register set addresses.&n; */
DECL|macro|MCFSIM_RSR
mdefine_line|#define&t;MCFSIM_RSR&t;&t;0x00&t;&t;/* Reset Status reg (r/w) */
DECL|macro|MCFSIM_SYPCR
mdefine_line|#define&t;MCFSIM_SYPCR&t;&t;0x01&t;&t;/* System Protection reg (r/w)*/
DECL|macro|MCFSIM_SWIVR
mdefine_line|#define&t;MCFSIM_SWIVR&t;&t;0x02&t;&t;/* SW Watchdog intr reg (r/w) */
DECL|macro|MCFSIM_SWSR
mdefine_line|#define&t;MCFSIM_SWSR&t;&t;0x03&t;&t;/* SW Watchdog service (r/w) */
DECL|macro|MCFSIM_PAR
mdefine_line|#define&t;MCFSIM_PAR&t;&t;0x04&t;&t;/* Pin Assignment reg (r/w) */
DECL|macro|MCFSIM_IRQPAR
mdefine_line|#define&t;MCFSIM_IRQPAR&t;&t;0x06&t;&t;/* Interrupt Assignment reg (r/w) */
DECL|macro|MCFSIM_PLLCR
mdefine_line|#define&t;MCFSIM_PLLCR&t;&t;0x08&t;&t;/* PLL Controll Reg*/
DECL|macro|MCFSIM_MPARK
mdefine_line|#define&t;MCFSIM_MPARK&t;&t;0x0C&t;&t;/* BUS Master Control Reg*/
DECL|macro|MCFSIM_IPR
mdefine_line|#define&t;MCFSIM_IPR&t;&t;0x40&t;&t;/* Interrupt Pend reg (r/w) */
DECL|macro|MCFSIM_IMR
mdefine_line|#define&t;MCFSIM_IMR&t;&t;0x44&t;&t;/* Interrupt Mask reg (r/w) */
DECL|macro|MCFSIM_AVR
mdefine_line|#define&t;MCFSIM_AVR&t;&t;0x4b&t;&t;/* Autovector Ctrl reg (r/w) */
DECL|macro|MCFSIM_ICR0
mdefine_line|#define&t;MCFSIM_ICR0&t;&t;0x4c&t;&t;/* Intr Ctrl reg 0 (r/w) */
DECL|macro|MCFSIM_ICR1
mdefine_line|#define&t;MCFSIM_ICR1&t;&t;0x4d&t;&t;/* Intr Ctrl reg 1 (r/w) */
DECL|macro|MCFSIM_ICR2
mdefine_line|#define&t;MCFSIM_ICR2&t;&t;0x4e&t;&t;/* Intr Ctrl reg 2 (r/w) */
DECL|macro|MCFSIM_ICR3
mdefine_line|#define&t;MCFSIM_ICR3&t;&t;0x4f&t;&t;/* Intr Ctrl reg 3 (r/w) */
DECL|macro|MCFSIM_ICR4
mdefine_line|#define&t;MCFSIM_ICR4&t;&t;0x50&t;&t;/* Intr Ctrl reg 4 (r/w) */
DECL|macro|MCFSIM_ICR5
mdefine_line|#define&t;MCFSIM_ICR5&t;&t;0x51&t;&t;/* Intr Ctrl reg 5 (r/w) */
DECL|macro|MCFSIM_ICR6
mdefine_line|#define&t;MCFSIM_ICR6&t;&t;0x52&t;&t;/* Intr Ctrl reg 6 (r/w) */
DECL|macro|MCFSIM_ICR7
mdefine_line|#define&t;MCFSIM_ICR7&t;&t;0x53&t;&t;/* Intr Ctrl reg 7 (r/w) */
DECL|macro|MCFSIM_ICR8
mdefine_line|#define&t;MCFSIM_ICR8&t;&t;0x54&t;&t;/* Intr Ctrl reg 8 (r/w) */
DECL|macro|MCFSIM_ICR9
mdefine_line|#define&t;MCFSIM_ICR9&t;&t;0x55&t;&t;/* Intr Ctrl reg 9 (r/w) */
DECL|macro|MCFSIM_ICR10
mdefine_line|#define&t;MCFSIM_ICR10&t;&t;0x56&t;&t;/* Intr Ctrl reg 10 (r/w) */
DECL|macro|MCFSIM_ICR11
mdefine_line|#define&t;MCFSIM_ICR11&t;&t;0x57&t;&t;/* Intr Ctrl reg 11 (r/w) */
DECL|macro|MCFSIM_CSAR0
mdefine_line|#define MCFSIM_CSAR0&t;&t;0x80&t;&t;/* CS 0 Address 0 reg (r/w) */
DECL|macro|MCFSIM_CSMR0
mdefine_line|#define MCFSIM_CSMR0&t;&t;0x84&t;&t;/* CS 0 Mask 0 reg (r/w) */
DECL|macro|MCFSIM_CSCR0
mdefine_line|#define MCFSIM_CSCR0&t;&t;0x8a&t;&t;/* CS 0 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR1
mdefine_line|#define MCFSIM_CSAR1&t;&t;0x8c&t;&t;/* CS 1 Address reg (r/w) */
DECL|macro|MCFSIM_CSMR1
mdefine_line|#define MCFSIM_CSMR1&t;&t;0x90&t;&t;/* CS 1 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR1
mdefine_line|#define MCFSIM_CSCR1&t;&t;0x96&t;&t;/* CS 1 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR2
mdefine_line|#define MCFSIM_CSAR2&t;&t;0x98&t;&t;/* CS 2 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR2
mdefine_line|#define MCFSIM_CSMR2&t;&t;0x9c&t;&t;/* CS 2 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR2
mdefine_line|#define MCFSIM_CSCR2&t;&t;0xa2&t;&t;/* CS 2 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR3
mdefine_line|#define MCFSIM_CSAR3&t;&t;0xa4&t;&t;/* CS 3 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR3
mdefine_line|#define MCFSIM_CSMR3&t;&t;0xa8&t;&t;/* CS 3 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR3
mdefine_line|#define MCFSIM_CSCR3&t;&t;0xae&t;&t;/* CS 3 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR4
mdefine_line|#define MCFSIM_CSAR4&t;&t;0xb0&t;&t;/* CS 4 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR4
mdefine_line|#define MCFSIM_CSMR4&t;&t;0xb4&t;&t;/* CS 4 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR4
mdefine_line|#define MCFSIM_CSCR4&t;&t;0xba&t;&t;/* CS 4 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR5
mdefine_line|#define MCFSIM_CSAR5&t;&t;0xbc&t;&t;/* CS 5 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR5
mdefine_line|#define MCFSIM_CSMR5&t;&t;0xc0&t;&t;/* CS 5 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR5
mdefine_line|#define MCFSIM_CSCR5&t;&t;0xc6&t;&t;/* CS 5 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR6
mdefine_line|#define MCFSIM_CSAR6&t;&t;0xc8&t;&t;/* CS 6 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR6
mdefine_line|#define MCFSIM_CSMR6&t;&t;0xcc&t;&t;/* CS 6 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR6
mdefine_line|#define MCFSIM_CSCR6&t;&t;0xd2&t;&t;/* CS 6 Control reg (r/w) */
DECL|macro|MCFSIM_CSAR7
mdefine_line|#define MCFSIM_CSAR7&t;&t;0xd4&t;&t;/* CS 7 Adress reg (r/w) */
DECL|macro|MCFSIM_CSMR7
mdefine_line|#define MCFSIM_CSMR7&t;&t;0xd8&t;&t;/* CS 7 Mask reg (r/w) */
DECL|macro|MCFSIM_CSCR7
mdefine_line|#define MCFSIM_CSCR7&t;&t;0xde&t;&t;/* CS 7 Control reg (r/w) */
DECL|macro|MCFSIM_DCR
mdefine_line|#define MCFSIM_DCR&t;&t;0x100&t;&t;/* DRAM Control reg (r/w) */
DECL|macro|MCFSIM_DACR0
mdefine_line|#define MCFSIM_DACR0&t;&t;0x108&t;&t;/* DRAM 0 Addr and Ctrl (r/w) */
DECL|macro|MCFSIM_DMR0
mdefine_line|#define MCFSIM_DMR0&t;&t;0x10c&t;&t;/* DRAM 0 Mask reg (r/w) */
DECL|macro|MCFSIM_DACR1
mdefine_line|#define MCFSIM_DACR1&t;&t;0x110&t;&t;/* DRAM 1 Addr and Ctrl (r/w) */
DECL|macro|MCFSIM_DMR1
mdefine_line|#define MCFSIM_DMR1&t;&t;0x114&t;&t;/* DRAM 1 Mask reg (r/w) */
DECL|macro|MCFSIM_PADDR
mdefine_line|#define&t;MCFSIM_PADDR&t;&t;0x244&t;&t;/* Parallel Direction (r/w) */
DECL|macro|MCFSIM_PADAT
mdefine_line|#define&t;MCFSIM_PADAT&t;&t;0x248&t;&t;/* Parallel Data (r/w) */
multiline_comment|/*&n; *&t;Some symbol defines for the above...&n; */
DECL|macro|MCFSIM_SWDICR
mdefine_line|#define&t;MCFSIM_SWDICR&t;&t;MCFSIM_ICR0&t;/* Watchdog timer ICR */
DECL|macro|MCFSIM_TIMER1ICR
mdefine_line|#define&t;MCFSIM_TIMER1ICR&t;MCFSIM_ICR1&t;/* Timer 1 ICR */
DECL|macro|MCFSIM_TIMER2ICR
mdefine_line|#define&t;MCFSIM_TIMER2ICR&t;MCFSIM_ICR2&t;/* Timer 2 ICR */
DECL|macro|MCFSIM_UART1ICR
mdefine_line|#define&t;MCFSIM_UART1ICR&t;&t;MCFSIM_ICR4&t;/* UART 1 ICR */
DECL|macro|MCFSIM_UART2ICR
mdefine_line|#define&t;MCFSIM_UART2ICR&t;&t;MCFSIM_ICR5&t;/* UART 2 ICR */
DECL|macro|MCFSIM_DMA0ICR
mdefine_line|#define&t;MCFSIM_DMA0ICR&t;&t;MCFSIM_ICR6&t;/* DMA 0 ICR */
DECL|macro|MCFSIM_DMA1ICR
mdefine_line|#define&t;MCFSIM_DMA1ICR&t;&t;MCFSIM_ICR7&t;/* DMA 1 ICR */
DECL|macro|MCFSIM_DMA2ICR
mdefine_line|#define&t;MCFSIM_DMA2ICR&t;&t;MCFSIM_ICR8&t;/* DMA 2 ICR */
DECL|macro|MCFSIM_DMA3ICR
mdefine_line|#define&t;MCFSIM_DMA3ICR&t;&t;MCFSIM_ICR9&t;/* DMA 3 ICR */
multiline_comment|/*&n; *&t;Macro to set IMR register. It is 32 bits on the 5407.&n; */
DECL|macro|mcf_getimr
mdefine_line|#define&t;mcf_getimr()&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IMR))
DECL|macro|mcf_setimr
mdefine_line|#define&t;mcf_setimr(imr)&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IMR)) = (imr);
DECL|macro|mcf_getipr
mdefine_line|#define&t;mcf_getipr()&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IPR))
multiline_comment|/*&n; *&t;Some symbol defines for the Parallel Port Pin Assignment Register&n; */
DECL|macro|MCFSIM_PAR_DREQ0
mdefine_line|#define MCFSIM_PAR_DREQ0        0x40            /* Set to select DREQ0 input */
multiline_comment|/* Clear to select par I/O */
DECL|macro|MCFSIM_PAR_DREQ1
mdefine_line|#define MCFSIM_PAR_DREQ1        0x20            /* Select DREQ1 input */
multiline_comment|/* Clear to select par I/O */
multiline_comment|/*&n; *       Defines for the IRQPAR Register&n; */
DECL|macro|IRQ5_LEVEL4
mdefine_line|#define IRQ5_LEVEL4&t;0x80
DECL|macro|IRQ3_LEVEL6
mdefine_line|#define IRQ3_LEVEL6&t;0x40
DECL|macro|IRQ1_LEVEL2
mdefine_line|#define IRQ1_LEVEL2&t;0x20
multiline_comment|/*&n; *&t;Define the Cache register flags.&n; */
DECL|macro|CACR_DEC
mdefine_line|#define&t;CACR_DEC&t;&t;0x80000000&t;/* Enable data cache */
DECL|macro|CACR_DWP
mdefine_line|#define&t;CACR_DWP&t;&t;0x40000000&t;/* Data write protection */
DECL|macro|CACR_DESB
mdefine_line|#define&t;CACR_DESB&t;&t;0x20000000&t;/* Enable data store buffer */
DECL|macro|CACR_DDPI
mdefine_line|#define&t;CACR_DDPI&t;&t;0x10000000&t;/* Disable CPUSHL */
DECL|macro|CACR_DHCLK
mdefine_line|#define&t;CACR_DHCLK&t;&t;0x08000000&t;/* Half data cache lock mode */
DECL|macro|CACR_DDCM_WT
mdefine_line|#define&t;CACR_DDCM_WT&t;&t;0x00000000&t;/* Write through cache*/
DECL|macro|CACR_DDCM_CP
mdefine_line|#define&t;CACR_DDCM_CP&t;&t;0x02000000&t;/* Copyback cache */
DECL|macro|CACR_DDCM_P
mdefine_line|#define&t;CACR_DDCM_P&t;&t;0x04000000&t;/* No cache, precise */
DECL|macro|CACR_DDCM_IMP
mdefine_line|#define&t;CACR_DDCM_IMP&t;&t;0x06000000&t;/* No cache, imprecise */
DECL|macro|CACR_DCINVA
mdefine_line|#define&t;CACR_DCINVA&t;&t;0x01000000&t;/* Invalidate data cache */
DECL|macro|CACR_BEC
mdefine_line|#define&t;CACR_BEC&t;&t;0x00080000&t;/* Enable branch cache */
DECL|macro|CACR_BCINVA
mdefine_line|#define&t;CACR_BCINVA&t;&t;0x00040000&t;/* Invalidate branch cache */
DECL|macro|CACR_IEC
mdefine_line|#define&t;CACR_IEC&t;&t;0x00008000&t;/* Enable instruction cache */
DECL|macro|CACR_DNFB
mdefine_line|#define&t;CACR_DNFB&t;&t;0x00002000&t;/* Inhibited fill buffer */
DECL|macro|CACR_IDPI
mdefine_line|#define&t;CACR_IDPI&t;&t;0x00001000&t;/* Disable CPUSHL */
DECL|macro|CACR_IHLCK
mdefine_line|#define&t;CACR_IHLCK&t;&t;0x00000800&t;/* Intruction cache half lock */
DECL|macro|CACR_IDCM
mdefine_line|#define&t;CACR_IDCM&t;&t;0x00000400&t;/* Intruction cache inhibit */
DECL|macro|CACR_ICINVA
mdefine_line|#define&t;CACR_ICINVA&t;&t;0x00000100&t;/* Invalidate instr cache */
DECL|macro|ACR_BASE_POS
mdefine_line|#define&t;ACR_BASE_POS&t;&t;24&t;&t;/* Address Base */
DECL|macro|ACR_MASK_POS
mdefine_line|#define&t;ACR_MASK_POS&t;&t;16&t;&t;/* Address Mask */
DECL|macro|ACR_ENABLE
mdefine_line|#define&t;ACR_ENABLE&t;&t;0x00008000&t;/* Enable address */
DECL|macro|ACR_USER
mdefine_line|#define&t;ACR_USER&t;&t;0x00000000&t;/* User mode access only */
DECL|macro|ACR_SUPER
mdefine_line|#define&t;ACR_SUPER&t;&t;0x00002000&t;/* Supervisor mode only */
DECL|macro|ACR_ANY
mdefine_line|#define&t;ACR_ANY&t;&t;&t;0x00004000&t;/* Match any access mode */
DECL|macro|ACR_CM_WT
mdefine_line|#define&t;ACR_CM_WT&t;&t;0x00000000&t;/* Write through mode */
DECL|macro|ACR_CM_CP
mdefine_line|#define&t;ACR_CM_CP&t;&t;0x00000020&t;/* Copyback mode */
DECL|macro|ACR_CM_OFF_PRE
mdefine_line|#define&t;ACR_CM_OFF_PRE&t;&t;0x00000040&t;/* No cache, precise */
DECL|macro|ACR_CM_OFF_IMP
mdefine_line|#define&t;ACR_CM_OFF_IMP&t;&t;0x00000060&t;/* No cache, imprecise */
DECL|macro|ACR_WPROTECT
mdefine_line|#define&t;ACR_WPROTECT&t;&t;0x00000004&t;/* Write protect */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m5407sim_h */
eof
