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
multiline_comment|/*&n; * The next 16 interrupts are for board specific purposes.  Since&n; * the kernel can only run on one machine at a time, we can re-use&n; * these.  If you need more, increase IRQ_BOARD_END, but keep it&n; * within sensible limits.&n; */
DECL|macro|IRQ_BOARD_START
mdefine_line|#define IRQ_BOARD_START&t;&t;(IRQ_GPIO(80) + 1)
DECL|macro|IRQ_BOARD_END
mdefine_line|#define IRQ_BOARD_END&t;&t;(IRQ_BOARD_START + 16)
DECL|macro|IRQ_SA1111_START
mdefine_line|#define IRQ_SA1111_START&t;(IRQ_BOARD_END)
DECL|macro|IRQ_GPAIN0
mdefine_line|#define IRQ_GPAIN0&t;&t;(IRQ_BOARD_END + 0)
DECL|macro|IRQ_GPAIN1
mdefine_line|#define IRQ_GPAIN1&t;&t;(IRQ_BOARD_END + 1)
DECL|macro|IRQ_GPAIN2
mdefine_line|#define IRQ_GPAIN2&t;&t;(IRQ_BOARD_END + 2)
DECL|macro|IRQ_GPAIN3
mdefine_line|#define IRQ_GPAIN3&t;&t;(IRQ_BOARD_END + 3)
DECL|macro|IRQ_GPBIN0
mdefine_line|#define IRQ_GPBIN0&t;&t;(IRQ_BOARD_END + 4)
DECL|macro|IRQ_GPBIN1
mdefine_line|#define IRQ_GPBIN1&t;&t;(IRQ_BOARD_END + 5)
DECL|macro|IRQ_GPBIN2
mdefine_line|#define IRQ_GPBIN2&t;&t;(IRQ_BOARD_END + 6)
DECL|macro|IRQ_GPBIN3
mdefine_line|#define IRQ_GPBIN3&t;&t;(IRQ_BOARD_END + 7)
DECL|macro|IRQ_GPBIN4
mdefine_line|#define IRQ_GPBIN4&t;&t;(IRQ_BOARD_END + 8)
DECL|macro|IRQ_GPBIN5
mdefine_line|#define IRQ_GPBIN5&t;&t;(IRQ_BOARD_END + 9)
DECL|macro|IRQ_GPCIN0
mdefine_line|#define IRQ_GPCIN0&t;&t;(IRQ_BOARD_END + 10)
DECL|macro|IRQ_GPCIN1
mdefine_line|#define IRQ_GPCIN1&t;&t;(IRQ_BOARD_END + 11)
DECL|macro|IRQ_GPCIN2
mdefine_line|#define IRQ_GPCIN2&t;&t;(IRQ_BOARD_END + 12)
DECL|macro|IRQ_GPCIN3
mdefine_line|#define IRQ_GPCIN3&t;&t;(IRQ_BOARD_END + 13)
DECL|macro|IRQ_GPCIN4
mdefine_line|#define IRQ_GPCIN4&t;&t;(IRQ_BOARD_END + 14)
DECL|macro|IRQ_GPCIN5
mdefine_line|#define IRQ_GPCIN5&t;&t;(IRQ_BOARD_END + 15)
DECL|macro|IRQ_GPCIN6
mdefine_line|#define IRQ_GPCIN6&t;&t;(IRQ_BOARD_END + 16)
DECL|macro|IRQ_GPCIN7
mdefine_line|#define IRQ_GPCIN7&t;&t;(IRQ_BOARD_END + 17)
DECL|macro|IRQ_MSTXINT
mdefine_line|#define IRQ_MSTXINT&t;&t;(IRQ_BOARD_END + 18)
DECL|macro|IRQ_MSRXINT
mdefine_line|#define IRQ_MSRXINT&t;&t;(IRQ_BOARD_END + 19)
DECL|macro|IRQ_MSSTOPERRINT
mdefine_line|#define IRQ_MSSTOPERRINT&t;(IRQ_BOARD_END + 20)
DECL|macro|IRQ_TPTXINT
mdefine_line|#define IRQ_TPTXINT&t;&t;(IRQ_BOARD_END + 21)
DECL|macro|IRQ_TPRXINT
mdefine_line|#define IRQ_TPRXINT&t;&t;(IRQ_BOARD_END + 22)
DECL|macro|IRQ_TPSTOPERRINT
mdefine_line|#define IRQ_TPSTOPERRINT&t;(IRQ_BOARD_END + 23)
DECL|macro|SSPXMTINT
mdefine_line|#define SSPXMTINT&t;&t;(IRQ_BOARD_END + 24)
DECL|macro|SSPRCVINT
mdefine_line|#define SSPRCVINT&t;&t;(IRQ_BOARD_END + 25)
DECL|macro|SSPROR
mdefine_line|#define SSPROR&t;&t;&t;(IRQ_BOARD_END + 26)
DECL|macro|AUDXMTDMADONEA
mdefine_line|#define AUDXMTDMADONEA&t;&t;(IRQ_BOARD_END + 32)
DECL|macro|AUDRCVDMADONEA
mdefine_line|#define AUDRCVDMADONEA&t;&t;(IRQ_BOARD_END + 33)
DECL|macro|AUDXMTDMADONEB
mdefine_line|#define AUDXMTDMADONEB&t;&t;(IRQ_BOARD_END + 34)
DECL|macro|AUDRCVDMADONEB
mdefine_line|#define AUDRCVDMADONEB&t;&t;(IRQ_BOARD_END + 35)
DECL|macro|AUDTFSR
mdefine_line|#define AUDTFSR&t;&t;&t;(IRQ_BOARD_END + 36)
DECL|macro|AUDRFSR
mdefine_line|#define AUDRFSR&t;&t;&t;(IRQ_BOARD_END + 37)
DECL|macro|AUDTUR
mdefine_line|#define AUDTUR&t;&t;&t;(IRQ_BOARD_END + 38)
DECL|macro|AUDROR
mdefine_line|#define AUDROR&t;&t;&t;(IRQ_BOARD_END + 39)
DECL|macro|AUDDTS
mdefine_line|#define AUDDTS&t;&t;&t;(IRQ_BOARD_END + 40)
DECL|macro|AUDRDD
mdefine_line|#define AUDRDD&t;&t;&t;(IRQ_BOARD_END + 41)
DECL|macro|AUDSTO
mdefine_line|#define AUDSTO&t;&t;&t;(IRQ_BOARD_END + 42)
DECL|macro|IRQ_USBPWR
mdefine_line|#define IRQ_USBPWR&t;&t;(IRQ_BOARD_END + 43)
DECL|macro|IRQ_HCIM
mdefine_line|#define IRQ_HCIM&t;&t;(IRQ_BOARD_END + 44)
DECL|macro|IRQ_HCIBUFFACC
mdefine_line|#define IRQ_HCIBUFFACC&t;&t;(IRQ_BOARD_END + 45)
DECL|macro|IRQ_HCIRMTWKP
mdefine_line|#define IRQ_HCIRMTWKP&t;&t;(IRQ_BOARD_END + 46)
DECL|macro|IRQ_NHCIMFCIR
mdefine_line|#define IRQ_NHCIMFCIR&t;&t;(IRQ_BOARD_END + 47)
DECL|macro|IRQ_USB_PORT_RESUME
mdefine_line|#define IRQ_USB_PORT_RESUME&t;(IRQ_BOARD_END + 48)
DECL|macro|IRQ_S0_READY_NINT
mdefine_line|#define IRQ_S0_READY_NINT&t;(IRQ_BOARD_END + 49)
DECL|macro|IRQ_S1_READY_NINT
mdefine_line|#define IRQ_S1_READY_NINT&t;(IRQ_BOARD_END + 50)
DECL|macro|IRQ_S0_CD_VALID
mdefine_line|#define IRQ_S0_CD_VALID&t;&t;(IRQ_BOARD_END + 51)
DECL|macro|IRQ_S1_CD_VALID
mdefine_line|#define IRQ_S1_CD_VALID&t;&t;(IRQ_BOARD_END + 52)
DECL|macro|IRQ_S0_BVD1_STSCHG
mdefine_line|#define IRQ_S0_BVD1_STSCHG&t;(IRQ_BOARD_END + 53)
DECL|macro|IRQ_S1_BVD1_STSCHG
mdefine_line|#define IRQ_S1_BVD1_STSCHG&t;(IRQ_BOARD_END + 54)
multiline_comment|/*&n; * Figure out the MAX IRQ number.&n; *&n; * If we have an SA1111, the max IRQ is S1_BVD1_STSCHG+1.&n; * Otherwise, we have the standard IRQs only.&n; */
macro_line|#ifdef CONFIG_SA1111
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IRQ_S1_BVD1_STSCHG + 1)
macro_line|#elif defined(CONFIG_ARCH_LUBBOCK)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IRQ_BOARD_END)
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IRQ_BOARD_START)
macro_line|#endif
multiline_comment|/*&n; * Board specific IRQs.  Define them here.&n; * Do not surround them with ifdefs.&n; */
DECL|macro|LUBBOCK_IRQ
mdefine_line|#define LUBBOCK_IRQ(x)&t;&t;(IRQ_BOARD_START + (x))
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
eof
