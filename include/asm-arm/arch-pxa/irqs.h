multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/irqs.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|PXA_IRQ_SKIP
mdefine_line|#define PXA_IRQ_SKIP&t;8&t;/* The first 8 IRQs are reserved */
DECL|macro|PXA_IRQ
mdefine_line|#define PXA_IRQ(x)&t;&t;((x) - PXA_IRQ_SKIP)
DECL|macro|IRQ_GPIO0
mdefine_line|#define&t;IRQ_GPIO0&t;PXA_IRQ(8)&t;/* GPIO0 Edge Detect */
DECL|macro|IRQ_GPIO1
mdefine_line|#define&t;IRQ_GPIO1&t;PXA_IRQ(9)&t;/* GPIO1 Edge Detect */
DECL|macro|IRQ_GPIO_2_80
mdefine_line|#define&t;IRQ_GPIO_2_80&t;PXA_IRQ(10)&t;/* GPIO[2-80] Edge Detect */
DECL|macro|IRQ_USB
mdefine_line|#define&t;IRQ_USB&t;&t;PXA_IRQ(11)&t;/* USB Service */
DECL|macro|IRQ_PMU
mdefine_line|#define&t;IRQ_PMU&t;&t;PXA_IRQ(12)&t;/* Performance Monitoring Unit */
DECL|macro|IRQ_I2S
mdefine_line|#define&t;IRQ_I2S&t;&t;PXA_IRQ(13)&t;/* I2S Interrupt */
DECL|macro|IRQ_AC97
mdefine_line|#define&t;IRQ_AC97&t;PXA_IRQ(14)&t;/* AC97 Interrupt */
DECL|macro|IRQ_LCD
mdefine_line|#define&t;IRQ_LCD&t;&t;PXA_IRQ(17)&t;/* LCD Controller Service Request */
DECL|macro|IRQ_I2C
mdefine_line|#define&t;IRQ_I2C&t;&t;PXA_IRQ(18)&t;/* I2C Service Request */
DECL|macro|IRQ_ICP
mdefine_line|#define&t;IRQ_ICP&t;&t;PXA_IRQ(19)&t;/* ICP Transmit/Receive/Error */
DECL|macro|IRQ_STUART
mdefine_line|#define&t;IRQ_STUART&t;PXA_IRQ(20)&t;/* STUART Transmit/Receive/Error */
DECL|macro|IRQ_BTUART
mdefine_line|#define&t;IRQ_BTUART&t;PXA_IRQ(21)&t;/* BTUART Transmit/Receive/Error */
DECL|macro|IRQ_FFUART
mdefine_line|#define&t;IRQ_FFUART&t;PXA_IRQ(22)&t;/* FFUART Transmit/Receive/Error*/
DECL|macro|IRQ_MMC
mdefine_line|#define&t;IRQ_MMC&t;&t;PXA_IRQ(23)&t;/* MMC Status/Error Detection */
DECL|macro|IRQ_SSP
mdefine_line|#define&t;IRQ_SSP&t;&t;PXA_IRQ(24)&t;/* SSP Service Request */
DECL|macro|IRQ_DMA
mdefine_line|#define&t;IRQ_DMA &t;PXA_IRQ(25)&t;/* DMA Channel Service Request */
DECL|macro|IRQ_OST0
mdefine_line|#define&t;IRQ_OST0 &t;PXA_IRQ(26)&t;/* OS Timer match 0 */
DECL|macro|IRQ_OST1
mdefine_line|#define&t;IRQ_OST1 &t;PXA_IRQ(27)&t;/* OS Timer match 1 */
DECL|macro|IRQ_OST2
mdefine_line|#define&t;IRQ_OST2 &t;PXA_IRQ(28)&t;/* OS Timer match 2 */
DECL|macro|IRQ_OST3
mdefine_line|#define&t;IRQ_OST3 &t;PXA_IRQ(29)&t;/* OS Timer match 3 */
DECL|macro|IRQ_RTC1Hz
mdefine_line|#define&t;IRQ_RTC1Hz&t;PXA_IRQ(30)&t;/* RTC HZ Clock Tick */
DECL|macro|IRQ_RTCAlrm
mdefine_line|#define&t;IRQ_RTCAlrm&t;PXA_IRQ(31)&t;/* RTC Alarm */
DECL|macro|GPIO_2_80_TO_IRQ
mdefine_line|#define GPIO_2_80_TO_IRQ(x)&t;&bslash;&n;&t;&t;&t;PXA_IRQ((x) - 2 + 32)
DECL|macro|IRQ_GPIO
mdefine_line|#define IRQ_GPIO(x)&t;(((x) &lt; 2) ? (IRQ_GPIO0 + (x)) : GPIO_2_80_TO_IRQ(x))
DECL|macro|IRQ_TO_GPIO_2_80
mdefine_line|#define IRQ_TO_GPIO_2_80(i)&t;&bslash;&n;&t;&t;&t;((i) - PXA_IRQ(32) + 2)
DECL|macro|IRQ_TO_GPIO
mdefine_line|#define IRQ_TO_GPIO(i)&t;((i) - (((i) &gt; IRQ_GPIO1) ? IRQ_GPIO(2) : IRQ_GPIO(0)))
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;&t;(IRQ_GPIO(80) + 1)
macro_line|#if defined(CONFIG_SA1111)
DECL|macro|IRQ_SA1111_START
mdefine_line|#define IRQ_SA1111_START&t;(IRQ_GPIO(80) + 1)
DECL|macro|SA1111_IRQ
mdefine_line|#define SA1111_IRQ(x)&t;&t;(IRQ_SA1111_START + (x))
DECL|macro|IRQ_GPAIN0
mdefine_line|#define IRQ_GPAIN0&t;&t;SA1111_IRQ(0)
DECL|macro|IRQ_GPAIN1
mdefine_line|#define IRQ_GPAIN1&t;&t;SA1111_IRQ(1)
DECL|macro|IRQ_GPAIN2
mdefine_line|#define IRQ_GPAIN2&t;&t;SA1111_IRQ(2)
DECL|macro|IRQ_GPAIN3
mdefine_line|#define IRQ_GPAIN3&t;&t;SA1111_IRQ(3)
DECL|macro|IRQ_GPBIN0
mdefine_line|#define IRQ_GPBIN0&t;&t;SA1111_IRQ(4)
DECL|macro|IRQ_GPBIN1
mdefine_line|#define IRQ_GPBIN1&t;&t;SA1111_IRQ(5)
DECL|macro|IRQ_GPBIN2
mdefine_line|#define IRQ_GPBIN2&t;&t;SA1111_IRQ(6)
DECL|macro|IRQ_GPBIN3
mdefine_line|#define IRQ_GPBIN3&t;&t;SA1111_IRQ(7)
DECL|macro|IRQ_GPBIN4
mdefine_line|#define IRQ_GPBIN4&t;&t;SA1111_IRQ(8)
DECL|macro|IRQ_GPBIN5
mdefine_line|#define IRQ_GPBIN5&t;&t;SA1111_IRQ(9)
DECL|macro|IRQ_GPCIN0
mdefine_line|#define IRQ_GPCIN0&t;&t;SA1111_IRQ(10)
DECL|macro|IRQ_GPCIN1
mdefine_line|#define IRQ_GPCIN1&t;&t;SA1111_IRQ(11)
DECL|macro|IRQ_GPCIN2
mdefine_line|#define IRQ_GPCIN2&t;&t;SA1111_IRQ(12)
DECL|macro|IRQ_GPCIN3
mdefine_line|#define IRQ_GPCIN3&t;&t;SA1111_IRQ(13)
DECL|macro|IRQ_GPCIN4
mdefine_line|#define IRQ_GPCIN4&t;&t;SA1111_IRQ(14)
DECL|macro|IRQ_GPCIN5
mdefine_line|#define IRQ_GPCIN5&t;&t;SA1111_IRQ(15)
DECL|macro|IRQ_GPCIN6
mdefine_line|#define IRQ_GPCIN6&t;&t;SA1111_IRQ(16)
DECL|macro|IRQ_GPCIN7
mdefine_line|#define IRQ_GPCIN7&t;&t;SA1111_IRQ(17)
DECL|macro|IRQ_MSTXINT
mdefine_line|#define IRQ_MSTXINT&t;&t;SA1111_IRQ(18)
DECL|macro|IRQ_MSRXINT
mdefine_line|#define IRQ_MSRXINT&t;&t;SA1111_IRQ(19)
DECL|macro|IRQ_MSSTOPERRINT
mdefine_line|#define IRQ_MSSTOPERRINT&t;SA1111_IRQ(20)
DECL|macro|IRQ_TPTXINT
mdefine_line|#define IRQ_TPTXINT&t;&t;SA1111_IRQ(21)
DECL|macro|IRQ_TPRXINT
mdefine_line|#define IRQ_TPRXINT&t;&t;SA1111_IRQ(22)
DECL|macro|IRQ_TPSTOPERRINT
mdefine_line|#define IRQ_TPSTOPERRINT&t;SA1111_IRQ(23)
DECL|macro|SSPXMTINT
mdefine_line|#define SSPXMTINT&t;SA1111_IRQ(24)
DECL|macro|SSPRCVINT
mdefine_line|#define SSPRCVINT&t;SA1111_IRQ(25)
DECL|macro|SSPROR
mdefine_line|#define SSPROR&t;&t;SA1111_IRQ(26)
DECL|macro|AUDXMTDMADONEA
mdefine_line|#define AUDXMTDMADONEA&t;SA1111_IRQ(32)
DECL|macro|AUDRCVDMADONEA
mdefine_line|#define AUDRCVDMADONEA&t;SA1111_IRQ(33)
DECL|macro|AUDXMTDMADONEB
mdefine_line|#define AUDXMTDMADONEB&t;SA1111_IRQ(34)
DECL|macro|AUDRCVDMADONEB
mdefine_line|#define AUDRCVDMADONEB&t;SA1111_IRQ(35)
DECL|macro|AUDTFSR
mdefine_line|#define AUDTFSR&t;&t;SA1111_IRQ(36)
DECL|macro|AUDRFSR
mdefine_line|#define AUDRFSR&t;&t;SA1111_IRQ(37)
DECL|macro|AUDTUR
mdefine_line|#define AUDTUR&t;&t;SA1111_IRQ(38)
DECL|macro|AUDROR
mdefine_line|#define AUDROR&t;&t;SA1111_IRQ(39)
DECL|macro|AUDDTS
mdefine_line|#define AUDDTS&t;&t;SA1111_IRQ(40)
DECL|macro|AUDRDD
mdefine_line|#define AUDRDD&t;&t;SA1111_IRQ(41)
DECL|macro|AUDSTO
mdefine_line|#define AUDSTO&t;&t;SA1111_IRQ(42)
DECL|macro|USBPWR
mdefine_line|#define USBPWR&t;&t;SA1111_IRQ(43)
DECL|macro|NIRQHCIM
mdefine_line|#define NIRQHCIM&t;SA1111_IRQ(44)
DECL|macro|HCIBUFFACC
mdefine_line|#define HCIBUFFACC&t;SA1111_IRQ(45)
DECL|macro|HCIRMTWKP
mdefine_line|#define HCIRMTWKP&t;SA1111_IRQ(46)
DECL|macro|NHCIMFCIR
mdefine_line|#define NHCIMFCIR&t;SA1111_IRQ(47)
DECL|macro|PORT_RESUME
mdefine_line|#define PORT_RESUME&t;SA1111_IRQ(48)
DECL|macro|S0_READY_NINT
mdefine_line|#define S0_READY_NINT&t;SA1111_IRQ(49)
DECL|macro|S1_READY_NINT
mdefine_line|#define S1_READY_NINT&t;SA1111_IRQ(50)
DECL|macro|S0_CD_VALID
mdefine_line|#define S0_CD_VALID&t;SA1111_IRQ(51)
DECL|macro|S1_CD_VALID
mdefine_line|#define S1_CD_VALID&t;SA1111_IRQ(52)
DECL|macro|S0_BVD1_STSCHG
mdefine_line|#define S0_BVD1_STSCHG&t;SA1111_IRQ(53)
DECL|macro|S1_BVD1_STSCHG
mdefine_line|#define S1_BVD1_STSCHG&t;SA1111_IRQ(54)
DECL|macro|SA1111_IRQ_MAX
mdefine_line|#define SA1111_IRQ_MAX&t;SA1111_IRQ(54)
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(SA1111_IRQ_MAX + 1)
macro_line|#endif&t;
singleline_comment|// defined(CONFIG_SA1111)
macro_line|#if defined(CONFIG_ARCH_LUBBOCK) || defined(CONFIG_ARCH_PXA_IDP)
macro_line|#if CONFIG_SA1111
DECL|macro|LUBBOCK_IRQ
mdefine_line|#define LUBBOCK_IRQ(x)&t;(SA1111_IRQ_MAX + 1 + (x))
macro_line|#else
DECL|macro|LUBBOCK_IRQ
mdefine_line|#define LUBBOCK_IRQ(x)&t;(IRQ_GPIO(80) + 1 + (x))
macro_line|#endif
DECL|macro|LUBBOCK_SD_IRQ
mdefine_line|#define LUBBOCK_SD_IRQ&t;&t;LUBBOCK_IRQ(0)
DECL|macro|LUBBOCK_SA1111_IRQ
mdefine_line|#define LUBBOCK_SA1111_IRQ&t;LUBBOCK_IRQ(1)
DECL|macro|LUBBOCK_USB_IRQ
mdefine_line|#define LUBBOCK_USB_IRQ&t;&t;LUBBOCK_IRQ(2)
DECL|macro|LUBBOCK_ETH_IRQ
mdefine_line|#define LUBBOCK_ETH_IRQ&t;&t;LUBBOCK_IRQ(3)
DECL|macro|LUBBOCK_UCB1400_IRQ
mdefine_line|#define LUBBOCK_UCB1400_IRQ&t;LUBBOCK_IRQ(4)
DECL|macro|LUBBOCK_BB_IRQ
mdefine_line|#define LUBBOCK_BB_IRQ&t;&t;LUBBOCK_IRQ(5)
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(LUBBOCK_IRQ(5) + 1)
macro_line|#endif&t;
singleline_comment|// CONFIG_ARCH_LUBBOCK
eof
