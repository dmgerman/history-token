multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/irqs.h&n; *&n; * Copyright (C) 1996 Russell King&n; * Copyright (C) 1998 Deborah Wallach (updates for SA1100/Brutus).&n; * Copyright (C) 1999 Nicolas Pitre (full GPIO irq isolation)&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SA1100_IRQ
mdefine_line|#define SA1100_IRQ(x)&t;&t;(0 + (x))
DECL|macro|IRQ_GPIO0
mdefine_line|#define&t;IRQ_GPIO0&t;&t;SA1100_IRQ(0)
DECL|macro|IRQ_GPIO1
mdefine_line|#define&t;IRQ_GPIO1&t;&t;SA1100_IRQ(1)
DECL|macro|IRQ_GPIO2
mdefine_line|#define&t;IRQ_GPIO2&t;&t;SA1100_IRQ(2)
DECL|macro|IRQ_GPIO3
mdefine_line|#define&t;IRQ_GPIO3&t;&t;SA1100_IRQ(3)
DECL|macro|IRQ_GPIO4
mdefine_line|#define&t;IRQ_GPIO4&t;&t;SA1100_IRQ(4)
DECL|macro|IRQ_GPIO5
mdefine_line|#define&t;IRQ_GPIO5&t;&t;SA1100_IRQ(5)
DECL|macro|IRQ_GPIO6
mdefine_line|#define&t;IRQ_GPIO6&t;&t;SA1100_IRQ(6)
DECL|macro|IRQ_GPIO7
mdefine_line|#define&t;IRQ_GPIO7&t;&t;SA1100_IRQ(7)
DECL|macro|IRQ_GPIO8
mdefine_line|#define&t;IRQ_GPIO8&t;&t;SA1100_IRQ(8)
DECL|macro|IRQ_GPIO9
mdefine_line|#define&t;IRQ_GPIO9&t;&t;SA1100_IRQ(9)
DECL|macro|IRQ_GPIO10
mdefine_line|#define&t;IRQ_GPIO10&t;&t;SA1100_IRQ(10)
DECL|macro|IRQ_GPIO11_27
mdefine_line|#define&t;IRQ_GPIO11_27&t;&t;SA1100_IRQ(11)
DECL|macro|IRQ_LCD
mdefine_line|#define&t;IRQ_LCD  &t;&t;SA1100_IRQ(12)&t;/* LCD controller           */
DECL|macro|IRQ_Ser0UDC
mdefine_line|#define&t;IRQ_Ser0UDC&t;&t;SA1100_IRQ(13)&t;/* Ser. port 0 UDC          */
DECL|macro|IRQ_Ser1SDLC
mdefine_line|#define&t;IRQ_Ser1SDLC&t;&t;SA1100_IRQ(14)&t;/* Ser. port 1 SDLC         */
DECL|macro|IRQ_Ser1UART
mdefine_line|#define&t;IRQ_Ser1UART&t;&t;SA1100_IRQ(15)&t;/* Ser. port 1 UART         */
DECL|macro|IRQ_Ser2ICP
mdefine_line|#define&t;IRQ_Ser2ICP&t;&t;SA1100_IRQ(16)&t;/* Ser. port 2 ICP          */
DECL|macro|IRQ_Ser3UART
mdefine_line|#define&t;IRQ_Ser3UART&t;&t;SA1100_IRQ(17)&t;/* Ser. port 3 UART         */
DECL|macro|IRQ_Ser4MCP
mdefine_line|#define&t;IRQ_Ser4MCP&t;&t;SA1100_IRQ(18)&t;/* Ser. port 4 MCP          */
DECL|macro|IRQ_Ser4SSP
mdefine_line|#define&t;IRQ_Ser4SSP&t;&t;SA1100_IRQ(19)&t;/* Ser. port 4 SSP          */
DECL|macro|IRQ_DMA0
mdefine_line|#define&t;IRQ_DMA0 &t;&t;SA1100_IRQ(20)&t;/* DMA controller channel 0 */
DECL|macro|IRQ_DMA1
mdefine_line|#define&t;IRQ_DMA1 &t;&t;SA1100_IRQ(21)&t;/* DMA controller channel 1 */
DECL|macro|IRQ_DMA2
mdefine_line|#define&t;IRQ_DMA2 &t;&t;SA1100_IRQ(22)&t;/* DMA controller channel 2 */
DECL|macro|IRQ_DMA3
mdefine_line|#define&t;IRQ_DMA3 &t;&t;SA1100_IRQ(23)&t;/* DMA controller channel 3 */
DECL|macro|IRQ_DMA4
mdefine_line|#define&t;IRQ_DMA4 &t;&t;SA1100_IRQ(24)&t;/* DMA controller channel 4 */
DECL|macro|IRQ_DMA5
mdefine_line|#define&t;IRQ_DMA5 &t;&t;SA1100_IRQ(25)&t;/* DMA controller channel 5 */
DECL|macro|IRQ_OST0
mdefine_line|#define&t;IRQ_OST0 &t;&t;SA1100_IRQ(26)&t;/* OS Timer match 0         */
DECL|macro|IRQ_OST1
mdefine_line|#define&t;IRQ_OST1 &t;&t;SA1100_IRQ(27)&t;/* OS Timer match 1         */
DECL|macro|IRQ_OST2
mdefine_line|#define&t;IRQ_OST2 &t;&t;SA1100_IRQ(28)&t;/* OS Timer match 2         */
DECL|macro|IRQ_OST3
mdefine_line|#define&t;IRQ_OST3 &t;&t;SA1100_IRQ(29)&t;/* OS Timer match 3         */
DECL|macro|IRQ_RTC1Hz
mdefine_line|#define&t;IRQ_RTC1Hz&t;&t;SA1100_IRQ(30)&t;/* RTC 1 Hz clock           */
DECL|macro|IRQ_RTCAlrm
mdefine_line|#define&t;IRQ_RTCAlrm&t;&t;SA1100_IRQ(31)&t;/* RTC Alarm                */
DECL|macro|IRQ_GPIO_11_27
mdefine_line|#define&t;IRQ_GPIO_11_27(x)&t;(32 + (x) - 11)
DECL|macro|IRQ_GPIO11
mdefine_line|#define&t;IRQ_GPIO11&t;&t;IRQ_GPIO_11_27(11)
DECL|macro|IRQ_GPIO12
mdefine_line|#define&t;IRQ_GPIO12&t;&t;IRQ_GPIO_11_27(12)
DECL|macro|IRQ_GPIO13
mdefine_line|#define&t;IRQ_GPIO13&t;&t;IRQ_GPIO_11_27(13)
DECL|macro|IRQ_GPIO14
mdefine_line|#define&t;IRQ_GPIO14&t;&t;IRQ_GPIO_11_27(14)
DECL|macro|IRQ_GPIO15
mdefine_line|#define&t;IRQ_GPIO15&t;&t;IRQ_GPIO_11_27(15)
DECL|macro|IRQ_GPIO16
mdefine_line|#define&t;IRQ_GPIO16&t;&t;IRQ_GPIO_11_27(16)
DECL|macro|IRQ_GPIO17
mdefine_line|#define&t;IRQ_GPIO17&t;&t;IRQ_GPIO_11_27(17)
DECL|macro|IRQ_GPIO18
mdefine_line|#define&t;IRQ_GPIO18&t;&t;IRQ_GPIO_11_27(18)
DECL|macro|IRQ_GPIO19
mdefine_line|#define&t;IRQ_GPIO19&t;&t;IRQ_GPIO_11_27(19)
DECL|macro|IRQ_GPIO20
mdefine_line|#define&t;IRQ_GPIO20&t;&t;IRQ_GPIO_11_27(20)
DECL|macro|IRQ_GPIO21
mdefine_line|#define&t;IRQ_GPIO21&t;&t;IRQ_GPIO_11_27(21)
DECL|macro|IRQ_GPIO22
mdefine_line|#define&t;IRQ_GPIO22&t;&t;IRQ_GPIO_11_27(22)
DECL|macro|IRQ_GPIO23
mdefine_line|#define&t;IRQ_GPIO23&t;&t;IRQ_GPIO_11_27(23)
DECL|macro|IRQ_GPIO24
mdefine_line|#define&t;IRQ_GPIO24&t;&t;IRQ_GPIO_11_27(24)
DECL|macro|IRQ_GPIO25
mdefine_line|#define&t;IRQ_GPIO25&t;&t;IRQ_GPIO_11_27(25)
DECL|macro|IRQ_GPIO26
mdefine_line|#define&t;IRQ_GPIO26&t;&t;IRQ_GPIO_11_27(26)
DECL|macro|IRQ_GPIO27
mdefine_line|#define&t;IRQ_GPIO27&t;&t;IRQ_GPIO_11_27(27)
DECL|macro|SA1100_GPIO_TO_IRQ
mdefine_line|#define SA1100_GPIO_TO_IRQ(i)&t;(((i) &lt; 11) ? SA1100_IRQ(i) : IRQ_GPIO_11_27(i))
multiline_comment|/* To get the GPIO number from an IRQ number */
DECL|macro|GPIO_11_27_IRQ
mdefine_line|#define GPIO_11_27_IRQ(i)&t;(11 + (i) - 32)
DECL|macro|SA1100_IRQ_TO_GPIO
mdefine_line|#define SA1100_IRQ_TO_GPIO(i) &t;(((i) &lt; 11) ? (i) : GPIO_11_27_IRQ(i))
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;&t;(IRQ_GPIO27 + 1)
macro_line|#if defined(CONFIG_SA1100_GRAPHICSCLIENT) || defined(CONFIG_SA1100_GRAPHICSMASTER)
DECL|macro|ADS_EXT_IRQ
mdefine_line|#define ADS_EXT_IRQ(x)&t;(IRQ_GPIO27 + 1 + (x))
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(ADS_EXT_IRQ(15) + 1)
macro_line|#endif
macro_line|#if defined(CONFIG_SA1111)
macro_line|#if defined(CONFIG_SA1100_GRAPHICSMASTER)
DECL|macro|SA1111_IRQ
mdefine_line|#define&t;SA1111_IRQ(x)&t;(ADS_EXT_IRQ(15) + 1 + 1 + (x))
macro_line|#else
DECL|macro|SA1111_IRQ
mdefine_line|#define SA1111_IRQ(x)&t;(IRQ_GPIO27 + 1 + (x))
macro_line|#endif
DECL|macro|GPAIN0
mdefine_line|#define GPAIN0&t;&t;SA1111_IRQ(0)
DECL|macro|GPAIN1
mdefine_line|#define GPAIN1&t;&t;SA1111_IRQ(1)
DECL|macro|GPAIN2
mdefine_line|#define GPAIN2&t;&t;SA1111_IRQ(2)
DECL|macro|GPAIN3
mdefine_line|#define GPAIN3&t;&t;SA1111_IRQ(3)
DECL|macro|GPBIN0
mdefine_line|#define GPBIN0&t;&t;SA1111_IRQ(4)
DECL|macro|GPBIN1
mdefine_line|#define GPBIN1&t;&t;SA1111_IRQ(5)
DECL|macro|GPBIN2
mdefine_line|#define GPBIN2&t;&t;SA1111_IRQ(6)
DECL|macro|GPBIN3
mdefine_line|#define GPBIN3&t;&t;SA1111_IRQ(7)
DECL|macro|GPBIN4
mdefine_line|#define GPBIN4&t;&t;SA1111_IRQ(8)
DECL|macro|GPBIN5
mdefine_line|#define GPBIN5&t;&t;SA1111_IRQ(9)
DECL|macro|GPCIN0
mdefine_line|#define GPCIN0&t;&t;SA1111_IRQ(10)
DECL|macro|GPCIN1
mdefine_line|#define GPCIN1&t;&t;SA1111_IRQ(11)
DECL|macro|GPCIN2
mdefine_line|#define GPCIN2&t;&t;SA1111_IRQ(12)
DECL|macro|GPCIN3
mdefine_line|#define GPCIN3&t;&t;SA1111_IRQ(13)
DECL|macro|GPCIN4
mdefine_line|#define GPCIN4&t;&t;SA1111_IRQ(14)
DECL|macro|GPCIN5
mdefine_line|#define GPCIN5&t;&t;SA1111_IRQ(15)
DECL|macro|GPCIN6
mdefine_line|#define GPCIN6&t;&t;SA1111_IRQ(16)
DECL|macro|GPCIN7
mdefine_line|#define GPCIN7&t;&t;SA1111_IRQ(17)
DECL|macro|MSTXINT
mdefine_line|#define MSTXINT&t;&t;SA1111_IRQ(18)
DECL|macro|MSRXINT
mdefine_line|#define MSRXINT&t;&t;SA1111_IRQ(19)
DECL|macro|MSSTOPERRINT
mdefine_line|#define MSSTOPERRINT&t;SA1111_IRQ(20)
DECL|macro|TPTXINT
mdefine_line|#define TPTXINT&t;&t;SA1111_IRQ(21)
DECL|macro|TPRXINT
mdefine_line|#define TPRXINT&t;&t;SA1111_IRQ(22)
DECL|macro|TPSTOPERRINT
mdefine_line|#define TPSTOPERRINT&t;SA1111_IRQ(23)
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
DECL|macro|IRQHCIBUFFACC
mdefine_line|#define IRQHCIBUFFACC&t;SA1111_IRQ(45)
DECL|macro|IRQHCIRMTWKP
mdefine_line|#define IRQHCIRMTWKP&t;SA1111_IRQ(46)
DECL|macro|NHCIMFCIR
mdefine_line|#define NHCIMFCIR&t;SA1111_IRQ(47)
DECL|macro|USB_PORT_RESUME
mdefine_line|#define USB_PORT_RESUME&t;SA1111_IRQ(48)
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
macro_line|#ifdef CONFIG_ASSABET_NEPONSET
DECL|macro|MISC_IRQ0
mdefine_line|#define MISC_IRQ0&t;SA1111_IRQ(55)
DECL|macro|MISC_IRQ1
mdefine_line|#define MISC_IRQ1&t;SA1111_IRQ(56)
DECL|macro|NR_IRQS
macro_line|#undef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(SA1111_IRQ_MAX + 3)
macro_line|#endif  /* CONFIG_ASSABET_NEPONSET */
macro_line|#endif  /* CONFIG_SA1111 */
eof
