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
macro_line|#ifdef __ASSEMBLER__
multiline_comment|/*&n; *&t;The M5249C3 board needs a little help getting all its SIM devices&n; *&t;initialized at kernel start time. dBUG doesn&squot;t set much up, so&n; *&t;we need to do it manually.&n; */
dot
id|macro
id|m5249c3_setup
multiline_comment|/*&n;&t; *&t;Set MBAR1 and MBAR2, just incase they are not set.&n;&t; */
id|movel
macro_line|#0x10000001,%a0
DECL|variable|a0
id|movec
op_mod
id|a0
comma
op_mod
id|MBAR
multiline_comment|/* map MBAR region */
DECL|variable|subql
id|subql
macro_line|#1,%a0&t;&t;&t;&t;/* get MBAR address in a0 */
DECL|variable|x80000001
id|movel
macro_line|#0x80000001,%a1
DECL|variable|a1
id|movec
op_mod
id|a1
comma
macro_line|#3086&t;&t;&t;/* map MBAR2 region */
DECL|variable|subql
id|subql
macro_line|#1,%a1&t;&t;&t;&t;/* get MBAR2 address in a1 */
multiline_comment|/*&n;&t; *      Move secondary interrupts to base at 128.&n;&t; */
DECL|variable|x80
id|moveb
macro_line|#0x80,%d0
DECL|variable|d0
id|moveb
op_mod
id|d0
comma
l_int|0x16b
(paren
op_mod
id|a1
)paren
multiline_comment|/* interrupt base register */
multiline_comment|/*&n;&t; *      Work around broken CSMR0/DRAM vector problem.&n;&t; */
DECL|variable|x001F0021
id|movel
macro_line|#0x001F0021,%d0&t;&t;&t;/* disable C/I bit */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x84
(paren
op_mod
id|a0
)paren
multiline_comment|/* set CSMR0 */
multiline_comment|/*&n;&t; *&t;Disable the PLL firstly. (Who knows what state it is&n;&t; *&t;in here!).&n;&t; */
id|movel
l_int|0x180
(paren
op_mod
id|a1
)paren
comma
op_mod
id|d0
multiline_comment|/* get current PLL value */
DECL|variable|xfffffffe
id|andl
macro_line|#0xfffffffe,%d0&t;&t;&t;/* PLL bypass first */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x180
(paren
op_mod
id|a1
)paren
multiline_comment|/* set PLL register */
id|nop
macro_line|#ifdef CONFIG_CLOCK_140MHz
multiline_comment|/*&n;&t; *&t;Set initial clock frequency. This assumes M5249C3 board&n;&t; *&t;is fitted with 11.2896MHz crystal. It will program the&n;&t; *&t;PLL for 140MHz. Lets go fast :-)&n;&t; */
DECL|variable|x125a40f0
id|movel
macro_line|#0x125a40f0,%d0&t;&t;&t;/* set for 140MHz */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x180
(paren
op_mod
id|a1
)paren
multiline_comment|/* set PLL register */
DECL|variable|x1
id|orl
macro_line|#0x1,%d0
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x180
(paren
op_mod
id|a1
)paren
multiline_comment|/* set PLL register */
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Setup CS1 for ethernet controller.&n;&t; *&t;(Setup as per M5249C3 doco).&n;&t; */
DECL|variable|xe0000000
id|movel
macro_line|#0xe0000000,%d0&t;&t;&t;/* CS1 mapped at 0xe0000000 */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x8c
(paren
op_mod
id|a0
)paren
DECL|variable|x001f0021
id|movel
macro_line|#0x001f0021,%d0&t;&t;&t;/* CS1 size of 1Mb */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x90
(paren
op_mod
id|a0
)paren
DECL|variable|x0080
id|movew
macro_line|#0x0080,%d0&t;&t;&t;/* CS1 = 16bit port, AA */
DECL|variable|d0
id|movew
op_mod
id|d0
comma
l_int|0x96
(paren
op_mod
id|a0
)paren
multiline_comment|/*&n;&t; *&t;Setup CS2 for IDE interface.&n;&t; */
DECL|variable|x50000000
id|movel
macro_line|#0x50000000,%d0&t;&t;&t;/* CS2 mapped at 0x50000000 */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x98
(paren
op_mod
id|a0
)paren
DECL|variable|x001f0001
id|movel
macro_line|#0x001f0001,%d0&t;&t;&t;/* CS2 size of 1MB */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x9c
(paren
op_mod
id|a0
)paren
DECL|variable|x0080
id|movew
macro_line|#0x0080,%d0&t;&t;&t;/* CS2 = 16bit, TA */
DECL|variable|d0
id|movew
op_mod
id|d0
comma
l_int|0xa2
(paren
op_mod
id|a0
)paren
DECL|variable|x00107000
id|movel
macro_line|#0x00107000,%d0&t;&t;&t;/* IDEconfig1 */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x18c
(paren
op_mod
id|a1
)paren
DECL|variable|x000c0400
id|movel
macro_line|#0x000c0400,%d0&t;&t;&t;/* IDEconfig2 */
DECL|variable|d0
id|movel
op_mod
id|d0
comma
l_int|0x190
(paren
op_mod
id|a1
)paren
DECL|variable|x00080000
id|movel
macro_line|#0x00080000,%d0&t;&t;&t;/* GPIO19, IDE reset bit */
DECL|variable|d0
id|orl
op_mod
id|d0
comma
l_int|0xc
(paren
op_mod
id|a1
)paren
multiline_comment|/* function GPIO19 */
DECL|variable|d0
id|orl
op_mod
id|d0
comma
l_int|0x8
(paren
op_mod
id|a1
)paren
multiline_comment|/* enable GPIO19 as output */
DECL|variable|d0
id|orl
op_mod
id|d0
comma
l_int|0x4
(paren
op_mod
id|a1
)paren
multiline_comment|/* de-assert IDE reset */
dot
id|endm
DECL|macro|PLATFORM_SETUP
mdefine_line|#define&t;PLATFORM_SETUP&t;m5249c3_setup
macro_line|#endif /* __ASSEMBLER__ */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* m5249sim_h */
eof
