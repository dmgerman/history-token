multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;m5249sim.h -- ColdFire 5249 System Integration Module support.&n; *&n; *&t;(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;m5249sim_h
DECL|macro|m5249sim_h
mdefine_line|#define&t;m5249sim_h
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Define the 5249 SIM register set addresses.&n; */
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
multiline_comment|/*&n; *&t;General purpose IO registers (in MBAR2).&n; */
DECL|macro|MCFSIM2_GPIOREAD
mdefine_line|#define&t;MCFSIM2_GPIOREAD&t;0x0&t;&t;/* GPIO read values */
DECL|macro|MCFSIM2_GPIOWRITE
mdefine_line|#define&t;MCFSIM2_GPIOWRITE&t;0x4&t;&t;/* GPIO write values */
DECL|macro|MCFSIM2_GPIOENABLE
mdefine_line|#define&t;MCFSIM2_GPIOENABLE&t;0x8&t;&t;/* GPIO enabled */
DECL|macro|MCFSIM2_GPIOFUNC
mdefine_line|#define&t;MCFSIM2_GPIOFUNC&t;0xc&t;&t;/* GPIO function */
DECL|macro|MCFSIM2_GPIO1READ
mdefine_line|#define&t;MCFSIM2_GPIO1READ&t;0xb0&t;&t;/* GPIO1 read values */
DECL|macro|MCFSIM2_GPIO1WRITE
mdefine_line|#define&t;MCFSIM2_GPIO1WRITE&t;0xb4&t;&t;/* GPIO1 write values */
DECL|macro|MCFSIM2_GPIO1ENABLE
mdefine_line|#define&t;MCFSIM2_GPIO1ENABLE&t;0xb8&t;&t;/* GPIO1 enabled */
DECL|macro|MCFSIM2_GPIO1FUNC
mdefine_line|#define&t;MCFSIM2_GPIO1FUNC&t;0xbc&t;&t;/* GPIO1 function */
DECL|macro|MCFSIM2_GPIOINTSTAT
mdefine_line|#define&t;MCFSIM2_GPIOINTSTAT&t;0xc0&t;&t;/* GPIO interrupt status */
DECL|macro|MCFSIM2_GPIOINTCLEAR
mdefine_line|#define&t;MCFSIM2_GPIOINTCLEAR&t;0xc0&t;&t;/* GPIO interrupt clear */
DECL|macro|MCFSIM2_GPIOINTENABLE
mdefine_line|#define&t;MCFSIM2_GPIOINTENABLE&t;0xc4&t;&t;/* GPIO interrupt enable */
DECL|macro|MCFSIM2_INTLEVEL1
mdefine_line|#define&t;MCFSIM2_INTLEVEL1&t;0x140&t;&t;/* Interrupt level reg 1 */
DECL|macro|MCFSIM2_INTLEVEL2
mdefine_line|#define&t;MCFSIM2_INTLEVEL2&t;0x144&t;&t;/* Interrupt level reg 2 */
DECL|macro|MCFSIM2_INTLEVEL3
mdefine_line|#define&t;MCFSIM2_INTLEVEL3&t;0x148&t;&t;/* Interrupt level reg 3 */
DECL|macro|MCFSIM2_INTLEVEL4
mdefine_line|#define&t;MCFSIM2_INTLEVEL4&t;0x14c&t;&t;/* Interrupt level reg 4 */
DECL|macro|MCFSIM2_INTLEVEL5
mdefine_line|#define&t;MCFSIM2_INTLEVEL5&t;0x150&t;&t;/* Interrupt level reg 5 */
DECL|macro|MCFSIM2_INTLEVEL6
mdefine_line|#define&t;MCFSIM2_INTLEVEL6&t;0x154&t;&t;/* Interrupt level reg 6 */
DECL|macro|MCFSIM2_INTLEVEL7
mdefine_line|#define&t;MCFSIM2_INTLEVEL7&t;0x158&t;&t;/* Interrupt level reg 7 */
DECL|macro|MCFSIM2_INTLEVEL8
mdefine_line|#define&t;MCFSIM2_INTLEVEL8&t;0x15c&t;&t;/* Interrupt level reg 8 */
DECL|macro|MCFSIM2_DMAROUTE
mdefine_line|#define&t;MCFSIM2_DMAROUTE&t;0x188&t;&t;/* DMA routing */
DECL|macro|MCFSIM2_IDECONFIG1
mdefine_line|#define&t;MCFSIM2_IDECONFIG1&t;0x18c&t;&t;/* IDEconfig1 */
DECL|macro|MCFSIM2_IDECONFIG2
mdefine_line|#define&t;MCFSIM2_IDECONFIG2&t;0x190&t;&t;/* IDEconfig2 */
multiline_comment|/*&n; *&t;Macro to set IMR register. It is 32 bits on the 5249.&n; */
DECL|macro|MCFSIM_IMR_MASKALL
mdefine_line|#define&t;MCFSIM_IMR_MASKALL&t;0x7fffe&t;&t;/* All SIM intr sources */
DECL|macro|mcf_getimr
mdefine_line|#define&t;mcf_getimr()&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IMR))
DECL|macro|mcf_setimr
mdefine_line|#define&t;mcf_setimr(imr)&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IMR)) = (imr);
DECL|macro|mcf_getipr
mdefine_line|#define&t;mcf_getipr()&t;&t;&bslash;&n;&t;*((volatile unsigned long *) (MCF_MBAR + MCFSIM_IPR))
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m5249sim_h */
eof
