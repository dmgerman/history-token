multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/irqs.h&n; *&n; * Copyright (C) 1996 Russell King&n; * Copyright (C) 1998 Deborah Wallach (updates for SA1100/Brutus).&n; * Copyright (C) 1999 Nicolas Pitre (full GPIO irq isolation)&n; *&n; * 2001/11/14&t;RMK&t;Cleaned up and standardised a lot of the IRQs.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|IRQ_GPIO0
mdefine_line|#define&t;IRQ_GPIO0&t;&t;0
DECL|macro|IRQ_GPIO1
mdefine_line|#define&t;IRQ_GPIO1&t;&t;1
DECL|macro|IRQ_GPIO2
mdefine_line|#define&t;IRQ_GPIO2&t;&t;2
DECL|macro|IRQ_GPIO3
mdefine_line|#define&t;IRQ_GPIO3&t;&t;3
DECL|macro|IRQ_GPIO4
mdefine_line|#define&t;IRQ_GPIO4&t;&t;4
DECL|macro|IRQ_GPIO5
mdefine_line|#define&t;IRQ_GPIO5&t;&t;5
DECL|macro|IRQ_GPIO6
mdefine_line|#define&t;IRQ_GPIO6&t;&t;6
DECL|macro|IRQ_GPIO7
mdefine_line|#define&t;IRQ_GPIO7&t;&t;7
DECL|macro|IRQ_GPIO8
mdefine_line|#define&t;IRQ_GPIO8&t;&t;8
DECL|macro|IRQ_GPIO9
mdefine_line|#define&t;IRQ_GPIO9&t;&t;9
DECL|macro|IRQ_GPIO10
mdefine_line|#define&t;IRQ_GPIO10&t;&t;10
DECL|macro|IRQ_GPIO11_27
mdefine_line|#define&t;IRQ_GPIO11_27&t;&t;11
DECL|macro|IRQ_LCD
mdefine_line|#define&t;IRQ_LCD  &t;&t;12&t;/* LCD controller           */
DECL|macro|IRQ_Ser0UDC
mdefine_line|#define&t;IRQ_Ser0UDC&t;&t;13&t;/* Ser. port 0 UDC          */
DECL|macro|IRQ_Ser1SDLC
mdefine_line|#define&t;IRQ_Ser1SDLC&t;&t;14&t;/* Ser. port 1 SDLC         */
DECL|macro|IRQ_Ser1UART
mdefine_line|#define&t;IRQ_Ser1UART&t;&t;15&t;/* Ser. port 1 UART         */
DECL|macro|IRQ_Ser2ICP
mdefine_line|#define&t;IRQ_Ser2ICP&t;&t;16&t;/* Ser. port 2 ICP          */
DECL|macro|IRQ_Ser3UART
mdefine_line|#define&t;IRQ_Ser3UART&t;&t;17&t;/* Ser. port 3 UART         */
DECL|macro|IRQ_Ser4MCP
mdefine_line|#define&t;IRQ_Ser4MCP&t;&t;18&t;/* Ser. port 4 MCP          */
DECL|macro|IRQ_Ser4SSP
mdefine_line|#define&t;IRQ_Ser4SSP&t;&t;19&t;/* Ser. port 4 SSP          */
DECL|macro|IRQ_DMA0
mdefine_line|#define&t;IRQ_DMA0 &t;&t;20&t;/* DMA controller channel 0 */
DECL|macro|IRQ_DMA1
mdefine_line|#define&t;IRQ_DMA1 &t;&t;21&t;/* DMA controller channel 1 */
DECL|macro|IRQ_DMA2
mdefine_line|#define&t;IRQ_DMA2 &t;&t;22&t;/* DMA controller channel 2 */
DECL|macro|IRQ_DMA3
mdefine_line|#define&t;IRQ_DMA3 &t;&t;23&t;/* DMA controller channel 3 */
DECL|macro|IRQ_DMA4
mdefine_line|#define&t;IRQ_DMA4 &t;&t;24&t;/* DMA controller channel 4 */
DECL|macro|IRQ_DMA5
mdefine_line|#define&t;IRQ_DMA5 &t;&t;25&t;/* DMA controller channel 5 */
DECL|macro|IRQ_OST0
mdefine_line|#define&t;IRQ_OST0 &t;&t;26&t;/* OS Timer match 0         */
DECL|macro|IRQ_OST1
mdefine_line|#define&t;IRQ_OST1 &t;&t;27&t;/* OS Timer match 1         */
DECL|macro|IRQ_OST2
mdefine_line|#define&t;IRQ_OST2 &t;&t;28&t;/* OS Timer match 2         */
DECL|macro|IRQ_OST3
mdefine_line|#define&t;IRQ_OST3 &t;&t;29&t;/* OS Timer match 3         */
DECL|macro|IRQ_RTC1Hz
mdefine_line|#define&t;IRQ_RTC1Hz&t;&t;30&t;/* RTC 1 Hz clock           */
DECL|macro|IRQ_RTCAlrm
mdefine_line|#define&t;IRQ_RTCAlrm&t;&t;31&t;/* RTC Alarm                */
DECL|macro|IRQ_GPIO11
mdefine_line|#define&t;IRQ_GPIO11&t;&t;32
DECL|macro|IRQ_GPIO12
mdefine_line|#define&t;IRQ_GPIO12&t;&t;33
DECL|macro|IRQ_GPIO13
mdefine_line|#define&t;IRQ_GPIO13&t;&t;34
DECL|macro|IRQ_GPIO14
mdefine_line|#define&t;IRQ_GPIO14&t;&t;35
DECL|macro|IRQ_GPIO15
mdefine_line|#define&t;IRQ_GPIO15&t;&t;36
DECL|macro|IRQ_GPIO16
mdefine_line|#define&t;IRQ_GPIO16&t;&t;37
DECL|macro|IRQ_GPIO17
mdefine_line|#define&t;IRQ_GPIO17&t;&t;38
DECL|macro|IRQ_GPIO18
mdefine_line|#define&t;IRQ_GPIO18&t;&t;39
DECL|macro|IRQ_GPIO19
mdefine_line|#define&t;IRQ_GPIO19&t;&t;40
DECL|macro|IRQ_GPIO20
mdefine_line|#define&t;IRQ_GPIO20&t;&t;41
DECL|macro|IRQ_GPIO21
mdefine_line|#define&t;IRQ_GPIO21&t;&t;42
DECL|macro|IRQ_GPIO22
mdefine_line|#define&t;IRQ_GPIO22&t;&t;43
DECL|macro|IRQ_GPIO23
mdefine_line|#define&t;IRQ_GPIO23&t;&t;44
DECL|macro|IRQ_GPIO24
mdefine_line|#define&t;IRQ_GPIO24&t;&t;45
DECL|macro|IRQ_GPIO25
mdefine_line|#define&t;IRQ_GPIO25&t;&t;46
DECL|macro|IRQ_GPIO26
mdefine_line|#define&t;IRQ_GPIO26&t;&t;47
DECL|macro|IRQ_GPIO27
mdefine_line|#define&t;IRQ_GPIO27&t;&t;48
multiline_comment|/*&n; * To get the GPIO number from an IRQ number&n; */
DECL|macro|GPIO_11_27_IRQ
mdefine_line|#define GPIO_11_27_IRQ(i)&t;((i) - 21)
multiline_comment|/*&n; * The next 16 interrupts are for board specific purposes.  Since&n; * the kernel can only run on one machine at a time, we can re-use&n; * these.  If you need more, increase IRQ_BOARD_END, but keep it&n; * within sensible limits.  IRQs 49 to 64 are available.&n; */
DECL|macro|IRQ_BOARD_START
mdefine_line|#define IRQ_BOARD_START&t;&t;49
DECL|macro|IRQ_BOARD_END
mdefine_line|#define IRQ_BOARD_END&t;&t;65
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
DECL|macro|USBPWR
mdefine_line|#define USBPWR&t;&t;&t;(IRQ_BOARD_END + 43)
DECL|macro|NIRQHCIM
mdefine_line|#define NIRQHCIM&t;&t;(IRQ_BOARD_END + 44)
DECL|macro|IRQHCIBUFFACC
mdefine_line|#define IRQHCIBUFFACC&t;&t;(IRQ_BOARD_END + 45)
DECL|macro|IRQHCIRMTWKP
mdefine_line|#define IRQHCIRMTWKP&t;&t;(IRQ_BOARD_END + 46)
DECL|macro|NHCIMFCIR
mdefine_line|#define NHCIMFCIR&t;&t;(IRQ_BOARD_END + 47)
DECL|macro|USB_PORT_RESUME
mdefine_line|#define USB_PORT_RESUME&t;&t;(IRQ_BOARD_END + 48)
DECL|macro|S0_READY_NINT
mdefine_line|#define S0_READY_NINT&t;&t;(IRQ_BOARD_END + 49)
DECL|macro|S1_READY_NINT
mdefine_line|#define S1_READY_NINT&t;&t;(IRQ_BOARD_END + 50)
DECL|macro|S0_CD_VALID
mdefine_line|#define S0_CD_VALID&t;&t;(IRQ_BOARD_END + 51)
DECL|macro|S1_CD_VALID
mdefine_line|#define S1_CD_VALID&t;&t;(IRQ_BOARD_END + 52)
DECL|macro|S0_BVD1_STSCHG
mdefine_line|#define S0_BVD1_STSCHG&t;&t;(IRQ_BOARD_END + 53)
DECL|macro|S1_BVD1_STSCHG
mdefine_line|#define S1_BVD1_STSCHG&t;&t;(IRQ_BOARD_END + 54)
multiline_comment|/*&n; * Figure out the MAX IRQ number.&n; *&n; * If we have an SA1111, the max IRQ is S1_BVD1_STSCHG+1.&n; * If graphicsclient or graphicsmaster, we don&squot;t have a SA1111.&n; * Otherwise, we have the standard IRQs only.&n; */
macro_line|#ifdef CONFIG_SA1111
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(S1_BVD1_STSCHG + 1)
macro_line|#elif defined(CONFIG_SA1100_GRAPHICSCLIENT) || &bslash;&n;      defined(CONFIG_SA1100_GRAPHICSMASTER)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IRQ_BOARD_END)
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(IRQ_BOARD_START)
macro_line|#endif
multiline_comment|/*&n; * Board specific IRQs.  Define them here.&n; * Do not surround them with ifdefs.&n; */
DECL|macro|IRQ_NEPONSET_SMC9196
mdefine_line|#define IRQ_NEPONSET_SMC9196&t;(IRQ_BOARD_START + 0)
DECL|macro|IRQ_NEPONSET_USAR
mdefine_line|#define IRQ_NEPONSET_USAR&t;(IRQ_BOARD_START + 1)
multiline_comment|/* PT Digital Board Interrupts (CONFIG_SA1100_PT_SYSTEM3) */
DECL|macro|IRQ_SYSTEM3_SMC9196
mdefine_line|#define IRQ_SYSTEM3_SMC9196&t;(IRQ_BOARD_START + 0)
eof
