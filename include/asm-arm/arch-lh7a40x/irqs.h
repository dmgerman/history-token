multiline_comment|/* include/asm-arm/arch-lh7a40x/irqs.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
multiline_comment|/* It is to be seen whether or not we can build a kernel for more than&n; * one board.  For the time being, these macros assume that we cannot.&n; * Thus, it is OK to ifdef machine/board specific IRQ assignments.&n; */
macro_line|#ifndef __ASM_ARCH_IRQS_H
DECL|macro|__ASM_ARCH_IRQS_H
mdefine_line|#define __ASM_ARCH_IRQS_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|FIQ_START
mdefine_line|#define FIQ_START&t;80
macro_line|#if defined (CONFIG_ARCH_LH7A400)
multiline_comment|/* FIQs */
DECL|macro|IRQ_GPIO0FIQ
macro_line|# define IRQ_GPIO0FIQ&t;0&t;/* GPIO External FIQ Interrupt on F0 */
DECL|macro|IRQ_BLINT
macro_line|# define IRQ_BLINT&t;1&t;/* Battery Low */
DECL|macro|IRQ_WEINT
macro_line|# define IRQ_WEINT&t;2&t;/* Watchdog Timer, WDT overflow&t;*/
DECL|macro|IRQ_MCINT
macro_line|# define IRQ_MCINT&t;3&t;/* Media Change, MEDCHG pin rising */
multiline_comment|/* IRQs */
DECL|macro|IRQ_CSINT
macro_line|# define IRQ_CSINT&t;4&t;/* Audio Codec (ACI) */
DECL|macro|IRQ_GPIO1INTR
macro_line|# define IRQ_GPIO1INTR&t;5&t;/* GPIO External IRQ Interrupt on F1 */
DECL|macro|IRQ_GPIO2INTR
macro_line|# define IRQ_GPIO2INTR&t;6&t;/* GPIO External IRQ Interrupt on F2 */
DECL|macro|IRQ_GPIO3INTR
macro_line|# define IRQ_GPIO3INTR&t;7&t;/* GPIO External IRQ Interrupt on F3 */
DECL|macro|IRQ_T1UI
macro_line|# define IRQ_T1UI&t;8&t;/* Timer 1 underflow */
DECL|macro|IRQ_T2UI
macro_line|# define IRQ_T2UI&t;9&t;/* Timer 2 underflow */
DECL|macro|IRQ_RTCMI
macro_line|# define IRQ_RTCMI&t;10
DECL|macro|IRQ_TINTR
macro_line|# define IRQ_TINTR&t;11&t;/* Clock State Controller 64 Hz tick (CSC) */
DECL|macro|IRQ_UART1INTR
macro_line|# define IRQ_UART1INTR&t;12
DECL|macro|IRQ_UART2INTR
macro_line|# define IRQ_UART2INTR&t;13
DECL|macro|IRQ_LCDINTR
macro_line|# define IRQ_LCDINTR&t;14
DECL|macro|IRQ_SSIEOT
macro_line|# define IRQ_SSIEOT&t;15&t;/* Synchronous Serial Interface (SSI) */
DECL|macro|IRQ_UART3INTR
macro_line|# define IRQ_UART3INTR&t;16
DECL|macro|IRQ_SCIINTR
macro_line|# define IRQ_SCIINTR&t;17&t;/* Smart Card Interface (SCI) */
DECL|macro|IRQ_AACINTR
macro_line|# define IRQ_AACINTR&t;18&t;/* Advanced Audio Codec (AAC) */
DECL|macro|IRQ_MMCINTR
macro_line|# define IRQ_MMCINTR&t;19&t;/* Multimedia Card (MMC) */
DECL|macro|IRQ_USBINTR
macro_line|# define IRQ_USBINTR&t;20
DECL|macro|IRQ_DMAINTR
macro_line|# define IRQ_DMAINTR&t;21
DECL|macro|IRQ_T3UI
macro_line|# define IRQ_T3UI&t;22&t;/* Timer 3 underflow */
DECL|macro|IRQ_GPIO4INTR
macro_line|# define IRQ_GPIO4INTR&t;23&t;/* GPIO External IRQ Interrupt on F4 */
DECL|macro|IRQ_GPIO5INTR
macro_line|# define IRQ_GPIO5INTR&t;24&t;/* GPIO External IRQ Interrupt on F5 */
DECL|macro|IRQ_GPIO6INTR
macro_line|# define IRQ_GPIO6INTR&t;25&t;/* GPIO External IRQ Interrupt on F6 */
DECL|macro|IRQ_GPIO7INTR
macro_line|# define IRQ_GPIO7INTR&t;26&t;/* GPIO External IRQ Interrupt on F7 */
DECL|macro|IRQ_BMIINTR
macro_line|# define IRQ_BMIINTR&t;27&t;/* Battery Monitor Interface (BMI) */
DECL|macro|NR_IRQ_CPU
macro_line|# define NR_IRQ_CPU&t;28&t;/* IRQs directly recognized by CPU */
multiline_comment|/* Given IRQ, return GPIO interrupt number 0-7 */
DECL|macro|IRQ_TO_GPIO
macro_line|# define IRQ_TO_GPIO(i)  ((i) &bslash;&n;&t;- (((i) &gt; IRQ_GPIO3INTR) ? IRQ_GPIO4INTR - IRQ_GPIO3INTR - 1 : 0)&bslash;&n;&t;- (((i) &gt; IRQ_GPIO0INTR) ? IRQ_GPIO1INTR - IRQ_GPIO0INTR - 1 : 0))
macro_line|#endif
macro_line|#if defined (CONFIG_ARCH_LH7A404)
DECL|macro|IRQ_BROWN
macro_line|# define IRQ_BROWN&t;0&t;/* Brownout */
DECL|macro|IRQ_WDTINTR
macro_line|# define IRQ_WDTINTR&t;1&t;/* Watchdog Timer */
DECL|macro|IRQ_COMMRX
macro_line|# define IRQ_COMMRX&t;2&t;/* ARM Comm Rx for Debug */
DECL|macro|IRQ_COMMTX
macro_line|# define IRQ_COMMTX&t;3&t;/* ARM Comm Tx for Debug */
DECL|macro|IRQ_T1UI
macro_line|# define IRQ_T1UI&t;4&t;/* Timer 1 underflow */
DECL|macro|IRQ_T2UI
macro_line|# define IRQ_T2UI&t;5&t;/* Timer 2 underflow */
DECL|macro|IRQ_CSINT
macro_line|# define IRQ_CSINT&t;6&t;/* Codec Interrupt (shared by AAC on 404) */
DECL|macro|IRQ_DMAM2P0
macro_line|# define IRQ_DMAM2P0&t;7&t;/* -- DMA Memory to Peripheral */
DECL|macro|IRQ_DMAM2P1
macro_line|# define IRQ_DMAM2P1&t;8
DECL|macro|IRQ_DMAM2P2
macro_line|# define IRQ_DMAM2P2&t;9
DECL|macro|IRQ_DMAM2P3
macro_line|# define IRQ_DMAM2P3&t;10
DECL|macro|IRQ_DMAM2P4
macro_line|# define IRQ_DMAM2P4&t;11
DECL|macro|IRQ_DMAM2P5
macro_line|# define IRQ_DMAM2P5&t;12
DECL|macro|IRQ_DMAM2P6
macro_line|# define IRQ_DMAM2P6&t;13
DECL|macro|IRQ_DMAM2P7
macro_line|# define IRQ_DMAM2P7&t;14
DECL|macro|IRQ_DMAM2P8
macro_line|# define IRQ_DMAM2P8&t;15
DECL|macro|IRQ_DMAM2P9
macro_line|# define IRQ_DMAM2P9&t;16
DECL|macro|IRQ_DMAM2M0
macro_line|# define IRQ_DMAM2M0&t;17&t;/* -- DMA Memory to Memory */
DECL|macro|IRQ_DMAM2M1
macro_line|# define IRQ_DMAM2M1&t;18
DECL|macro|IRQ_GPIO0INTR
macro_line|# define IRQ_GPIO0INTR&t;19&t;/* -- GPIOF Interrupt */
DECL|macro|IRQ_GPIO1INTR
macro_line|# define IRQ_GPIO1INTR&t;20
DECL|macro|IRQ_GPIO2INTR
macro_line|# define IRQ_GPIO2INTR&t;21
DECL|macro|IRQ_GPIO3INTR
macro_line|# define IRQ_GPIO3INTR&t;22
DECL|macro|IRQ_SOFT_V1_23
macro_line|# define IRQ_SOFT_V1_23&t;23&t;/* -- Unassigned */
DECL|macro|IRQ_SOFT_V1_24
macro_line|# define IRQ_SOFT_V1_24&t;24
DECL|macro|IRQ_SOFT_V1_25
macro_line|# define IRQ_SOFT_V1_25&t;25
DECL|macro|IRQ_SOFT_V1_26
macro_line|# define IRQ_SOFT_V1_26&t;26
DECL|macro|IRQ_SOFT_V1_27
macro_line|# define IRQ_SOFT_V1_27&t;27
DECL|macro|IRQ_SOFT_V1_28
macro_line|# define IRQ_SOFT_V1_28&t;28
DECL|macro|IRQ_SOFT_V1_29
macro_line|# define IRQ_SOFT_V1_29&t;29
DECL|macro|IRQ_SOFT_V1_30
macro_line|# define IRQ_SOFT_V1_30&t;30
DECL|macro|IRQ_SOFT_V1_31
macro_line|# define IRQ_SOFT_V1_31&t;31
DECL|macro|IRQ_BLINT
macro_line|# define IRQ_BLINT&t;32&t;/* Battery Low */
DECL|macro|IRQ_BMIINTR
macro_line|# define IRQ_BMIINTR&t;33&t;/* Battery Monitor */
DECL|macro|IRQ_MCINTR
macro_line|# define IRQ_MCINTR&t;34&t;/* Media Change */
DECL|macro|IRQ_TINTR
macro_line|# define IRQ_TINTR&t;35&t;/* 64Hz Tick */
DECL|macro|IRQ_WEINT
macro_line|# define IRQ_WEINT&t;36&t;/* Watchdog Expired */
DECL|macro|IRQ_RTCMI
macro_line|# define IRQ_RTCMI&t;37&t;/* Real-time Clock Match */
DECL|macro|IRQ_UART1INTR
macro_line|# define IRQ_UART1INTR&t;38&t;/* UART1 Interrupt (including error) */
DECL|macro|IRQ_UART1ERR
macro_line|# define IRQ_UART1ERR&t;39&t;/* UART1 Error */
DECL|macro|IRQ_UART2INTR
macro_line|# define IRQ_UART2INTR&t;40&t;/* UART2 Interrupt (including error) */
DECL|macro|IRQ_UART2ERR
macro_line|# define IRQ_UART2ERR&t;41&t;/* UART2 Error */
DECL|macro|IRQ_UART3INTR
macro_line|# define IRQ_UART3INTR&t;42&t;/* UART3 Interrupt (including error) */
DECL|macro|IRQ_UART3ERR
macro_line|# define IRQ_UART3ERR&t;43&t;/* UART3 Error */
DECL|macro|IRQ_SCIINTR
macro_line|# define IRQ_SCIINTR&t;44&t;/* Smart Card */
DECL|macro|IRQ_TSCINTR
macro_line|# define IRQ_TSCINTR&t;45&t;/* Touchscreen */
DECL|macro|IRQ_KMIINTR
macro_line|# define IRQ_KMIINTR&t;46&t;/* Keyboard/Mouse (PS/2) */
DECL|macro|IRQ_GPIO4INTR
macro_line|# define IRQ_GPIO4INTR&t;47&t;/* -- GPIOF Interrupt */
DECL|macro|IRQ_GPIO5INTR
macro_line|# define IRQ_GPIO5INTR&t;48
DECL|macro|IRQ_GPIO6INTR
macro_line|# define IRQ_GPIO6INTR&t;49
DECL|macro|IRQ_GPIO7INTR
macro_line|# define IRQ_GPIO7INTR&t;50
DECL|macro|IRQ_T3UI
macro_line|# define IRQ_T3UI&t;51&t;/* Timer 3 underflow */
DECL|macro|IRQ_LCDINTR
macro_line|# define IRQ_LCDINTR&t;52&t;/* LCD Controller */
DECL|macro|IRQ_SSPINTR
macro_line|# define IRQ_SSPINTR&t;53&t;/* Synchronous Serial Port */
DECL|macro|IRQ_SDINTR
macro_line|# define IRQ_SDINTR&t;54&t;/* Secure Digital Port (MMC) */
DECL|macro|IRQ_USBINTR
macro_line|# define IRQ_USBINTR&t;55&t;/* USB Device Port */
DECL|macro|IRQ_USHINTR
macro_line|# define IRQ_USHINTR&t;56&t;/* USB Host Port */
DECL|macro|IRQ_SOFT_V2_25
macro_line|# define IRQ_SOFT_V2_25&t;57&t;/* -- Unassigned */
DECL|macro|IRQ_SOFT_V2_26
macro_line|# define IRQ_SOFT_V2_26&t;58
DECL|macro|IRQ_SOFT_V2_27
macro_line|# define IRQ_SOFT_V2_27&t;59
DECL|macro|IRQ_SOFT_V2_28
macro_line|# define IRQ_SOFT_V2_28&t;60
DECL|macro|IRQ_SOFT_V2_29
macro_line|# define IRQ_SOFT_V2_29&t;61
DECL|macro|IRQ_SOFT_V2_30
macro_line|# define IRQ_SOFT_V2_30&t;62
DECL|macro|IRQ_SOFT_V2_31
macro_line|# define IRQ_SOFT_V2_31&t;63
DECL|macro|NR_IRQ_CPU
macro_line|# define NR_IRQ_CPU&t;64&t;/* IRQs directly recognized by CPU */
multiline_comment|/* Given IRQ, return GPIO interrupt number 0-7 */
DECL|macro|IRQ_TO_GPIO
macro_line|# define IRQ_TO_GPIO(i)  ((i) &bslash;&n;&t;- (((i) &gt; IRQ_GPIO3INTR) ? IRQ_GPIO4INTR - IRQ_GPIO3INTR - 1 : 0)&bslash;&n;&t;- IRQ_GPIO0INTR)
multiline_comment|/* Vector Address constants */
DECL|macro|VA_VECTORED
macro_line|# define VA_VECTORED&t;0x100&t;/* Set for vectored interrupt */
DECL|macro|VA_VIC1DEFAULT
macro_line|# define VA_VIC1DEFAULT&t;0x200&t;/* Set as default VECTADDR for VIC1 */
DECL|macro|VA_VIC2DEFAULT
macro_line|# define VA_VIC2DEFAULT&t;0x400&t;/* Set as default VECTADDR for VIC2 */
macro_line|#endif
multiline_comment|/* IRQ aliases */
macro_line|#if !defined (IRQ_GPIO0INTR)
DECL|macro|IRQ_GPIO0INTR
macro_line|# define IRQ_GPIO0INTR&t;IRQ_GPIO0FIQ
macro_line|#endif
DECL|macro|IRQ_TICK
mdefine_line|#define IRQ_TICK &t;IRQ_TINTR
DECL|macro|IRQ_PCC1_RDY
mdefine_line|#define IRQ_PCC1_RDY&t;IRQ_GPIO6INTR&t;/* PCCard 1 ready */
DECL|macro|IRQ_PCC2_RDY
mdefine_line|#define IRQ_PCC2_RDY&t;IRQ_GPIO7INTR&t;/* PCCard 2 ready */
macro_line|#ifdef CONFIG_MACH_KEV7A400
DECL|macro|IRQ_TS
macro_line|# define IRQ_TS&t;&t;IRQ_GPIOFIQ&t;/* Touchscreen */
DECL|macro|IRQ_CPLD
macro_line|# define IRQ_CPLD&t;IRQ_GPIO1INTR&t;/* CPLD cascade */
DECL|macro|IRQ_PCC1_CD
macro_line|# define IRQ_PCC1_CD&t;IRQ_GPIO_F2&t;/* PCCard 1 card detect */
DECL|macro|IRQ_PCC2_CD
macro_line|# define IRQ_PCC2_CD&t;IRQ_GPIO_F3&t;/* PCCard 2 card detect */
macro_line|#endif
macro_line|#if defined (CONFIG_MACH_LPD7A400) || defined (CONFIG_MACH_LPD7A404)
DECL|macro|IRQ_CPLD_V28
macro_line|# define IRQ_CPLD_V28&t;IRQ_GPIO7INTR&t;/* CPLD cascade through GPIO_PF7 */
DECL|macro|IRQ_CPLD_V34
macro_line|# define IRQ_CPLD_V34&t;IRQ_GPIO3INTR&t;/* CPLD cascade through GPIO_PF3 */
macro_line|#endif
multiline_comment|/* System specific IRQs */
DECL|macro|IRQ_BOARD_START
mdefine_line|#define IRQ_BOARD_START NR_IRQ_CPU
macro_line|#ifdef CONFIG_MACH_KEV7A400
DECL|macro|IRQ_KEV7A400_CPLD
macro_line|# define IRQ_KEV7A400_CPLD&t;IRQ_BOARD_START
DECL|macro|NR_IRQ_BOARD
macro_line|# define NR_IRQ_BOARD&t;&t;5
DECL|macro|IRQ_KEV7A400_MMC_CD
macro_line|# define IRQ_KEV7A400_MMC_CD&t;IRQ_KEV7A400_CPLD + 0&t;/* MMC Card Detect */
DECL|macro|IRQ_KEV7A400_RI2
macro_line|# define IRQ_KEV7A400_RI2&t;IRQ_KEV7A400_CPLD + 1&t;/* Ring Indicator 2 */
DECL|macro|IRQ_KEV7A400_IDE_CF
macro_line|# define IRQ_KEV7A400_IDE_CF&t;IRQ_KEV7A400_CPLD + 2&t;/* Compact Flash (?) */
DECL|macro|IRQ_KEV7A400_ETH_INT
macro_line|# define IRQ_KEV7A400_ETH_INT&t;IRQ_KEV7A400_CPLD + 3&t;/* Ethernet chip */
DECL|macro|IRQ_KEV7A400_INT
macro_line|# define IRQ_KEV7A400_INT&t;IRQ_KEV7A400_CPLD + 4
macro_line|#endif
macro_line|#if defined (CONFIG_MACH_LPD7A400) || defined (CONFIG_MACH_LPD7A404)
DECL|macro|IRQ_LPD7A40X_CPLD
macro_line|# define IRQ_LPD7A40X_CPLD&t;IRQ_BOARD_START
DECL|macro|NR_IRQ_BOARD
macro_line|# define NR_IRQ_BOARD&t;&t;2
DECL|macro|IRQ_LPD7A40X_ETH_INT
macro_line|# define IRQ_LPD7A40X_ETH_INT&t;IRQ_LPD7A40X_CPLD + 0&t;/* Ethernet chip */
DECL|macro|IRQ_LPD7A400_TS
macro_line|# define IRQ_LPD7A400_TS&t;IRQ_LPD7A40X_CPLD + 1&t;/* Touch screen */
macro_line|#endif
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(NR_IRQ_CPU + NR_IRQ_BOARD)
macro_line|#endif
eof
