multiline_comment|/*&n; *  linux/include/asm-arm/arch-omap/irqs.h&n; *&n; *  Copyright (C) Greg Lonnon 2001&n; *  Updated for OMAP-1610 by Tony Lindgren &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * NOTE: The interrupt vectors for the OMAP-1509, OMAP-1510, and OMAP-1610&n; *&t; are different.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP1510_IRQS_H
DECL|macro|__ASM_ARCH_OMAP1510_IRQS_H
mdefine_line|#define __ASM_ARCH_OMAP1510_IRQS_H
multiline_comment|/*&n; * IRQ numbers for interrupt handler 1&n; *&n; * NOTE: See also the OMAP-1510 and 1610 specific IRQ numbers below&n; *&n; */
DECL|macro|INT_IH2_IRQ
mdefine_line|#define INT_IH2_IRQ&t;&t;0
DECL|macro|INT_CAMERA
mdefine_line|#define INT_CAMERA&t;&t;1
DECL|macro|INT_FIQ
mdefine_line|#define INT_FIQ&t;&t;&t;3
DECL|macro|INT_RTDX
mdefine_line|#define INT_RTDX&t;&t;6
DECL|macro|INT_DSP_MMU_ABORT
mdefine_line|#define INT_DSP_MMU_ABORT&t;7
DECL|macro|INT_HOST
mdefine_line|#define INT_HOST&t;&t;8
DECL|macro|INT_ABORT
mdefine_line|#define INT_ABORT&t;&t;9
DECL|macro|INT_DSP_MAILBOX1
mdefine_line|#define INT_DSP_MAILBOX1&t;10
DECL|macro|INT_DSP_MAILBOX2
mdefine_line|#define INT_DSP_MAILBOX2&t;11
DECL|macro|INT_BRIDGE_PRIV
mdefine_line|#define INT_BRIDGE_PRIV&t;&t;13
DECL|macro|INT_GPIO_BANK1
mdefine_line|#define INT_GPIO_BANK1&t;&t;14
DECL|macro|INT_UART3
mdefine_line|#define INT_UART3&t;&t;15
DECL|macro|INT_TIMER3
mdefine_line|#define INT_TIMER3&t;&t;16
DECL|macro|INT_DMA_CH0_6
mdefine_line|#define INT_DMA_CH0_6&t;&t;19
DECL|macro|INT_DMA_CH1_7
mdefine_line|#define INT_DMA_CH1_7&t;&t;20
DECL|macro|INT_DMA_CH2_8
mdefine_line|#define INT_DMA_CH2_8&t;&t;21
DECL|macro|INT_DMA_CH3
mdefine_line|#define INT_DMA_CH3&t;&t;22
DECL|macro|INT_DMA_CH4
mdefine_line|#define INT_DMA_CH4&t;&t;23
DECL|macro|INT_DMA_CH5
mdefine_line|#define INT_DMA_CH5&t;&t;24
DECL|macro|INT_DMA_LCD
mdefine_line|#define INT_DMA_LCD&t;&t;25
DECL|macro|INT_TIMER1
mdefine_line|#define INT_TIMER1&t;&t;26
DECL|macro|INT_WD_TIMER
mdefine_line|#define INT_WD_TIMER&t;&t;27
DECL|macro|INT_BRIDGE_PUB
mdefine_line|#define INT_BRIDGE_PUB&t;&t;28
DECL|macro|INT_TIMER2
mdefine_line|#define INT_TIMER2&t;&t;30
DECL|macro|INT_LCD_CTRL
mdefine_line|#define INT_LCD_CTRL&t;&t;31
multiline_comment|/*&n; * OMAP-1510 specific IRQ numbers for interrupt handler 1&n; */
DECL|macro|INT_1510_RES2
mdefine_line|#define INT_1510_RES2&t;&t;2
DECL|macro|INT_1510_SPI_TX
mdefine_line|#define INT_1510_SPI_TX&t;&t;4
DECL|macro|INT_1510_SPI_RX
mdefine_line|#define INT_1510_SPI_RX&t;&t;5
DECL|macro|INT_1510_RES12
mdefine_line|#define INT_1510_RES12&t;&t;12
DECL|macro|INT_1510_LB_MMU
mdefine_line|#define INT_1510_LB_MMU&t;&t;17
DECL|macro|INT_1510_RES18
mdefine_line|#define INT_1510_RES18&t;&t;18
DECL|macro|INT_1510_LOCAL_BUS
mdefine_line|#define INT_1510_LOCAL_BUS&t;29
multiline_comment|/*&n; * OMAP-1610 specific IRQ numbers for interrupt handler 1&n; */
DECL|macro|INT_1610_IH2_FIQ
mdefine_line|#define INT_1610_IH2_FIQ&t;2
DECL|macro|INT_1610_McBSP2_TX
mdefine_line|#define INT_1610_McBSP2_TX&t;4
DECL|macro|INT_1610_McBSP2_RX
mdefine_line|#define INT_1610_McBSP2_RX&t;5
DECL|macro|INT_1610_LCD_LINE
mdefine_line|#define INT_1610_LCD_LINE&t;12
DECL|macro|INT_1610_GPTIMER1
mdefine_line|#define INT_1610_GPTIMER1&t;17
DECL|macro|INT_1610_GPTIMER2
mdefine_line|#define INT_1610_GPTIMER2&t;18
DECL|macro|INT_1610_SSR_FIFO_0
mdefine_line|#define INT_1610_SSR_FIFO_0&t;29
multiline_comment|/*&n; * OMAP-730 specific IRQ numbers for interrupt handler 1&n; */
DECL|macro|INT_730_IH2_FIQ
mdefine_line|#define INT_730_IH2_FIQ&t;&t;0
DECL|macro|INT_730_IH2_IRQ
mdefine_line|#define INT_730_IH2_IRQ&t;&t;1
DECL|macro|INT_730_USB_NON_ISO
mdefine_line|#define INT_730_USB_NON_ISO&t;2
DECL|macro|INT_730_USB_ISO
mdefine_line|#define INT_730_USB_ISO&t;&t;3
DECL|macro|INT_730_ICR
mdefine_line|#define INT_730_ICR&t;&t;4
DECL|macro|INT_730_EAC
mdefine_line|#define INT_730_EAC&t;&t;5
DECL|macro|INT_730_GPIO_BANK1
mdefine_line|#define INT_730_GPIO_BANK1&t;6
DECL|macro|INT_730_GPIO_BANK2
mdefine_line|#define INT_730_GPIO_BANK2&t;7
DECL|macro|INT_730_GPIO_BANK3
mdefine_line|#define INT_730_GPIO_BANK3&t;8
DECL|macro|INT_730_McBSP2TX
mdefine_line|#define INT_730_McBSP2TX&t;10
DECL|macro|INT_730_McBSP2RX
mdefine_line|#define INT_730_McBSP2RX&t;11
DECL|macro|INT_730_McBSP2RX_OVF
mdefine_line|#define INT_730_McBSP2RX_OVF&t;12
DECL|macro|INT_730_LCD_LINE
mdefine_line|#define INT_730_LCD_LINE&t;14
DECL|macro|INT_730_GSM_PROTECT
mdefine_line|#define INT_730_GSM_PROTECT&t;15
DECL|macro|INT_730_TIMER3
mdefine_line|#define INT_730_TIMER3&t;&t;16
DECL|macro|INT_730_GPIO_BANK5
mdefine_line|#define INT_730_GPIO_BANK5&t;17
DECL|macro|INT_730_GPIO_BANK6
mdefine_line|#define INT_730_GPIO_BANK6&t;18
DECL|macro|INT_730_SPGIO_WR
mdefine_line|#define INT_730_SPGIO_WR&t;29
multiline_comment|/*&n; * IRQ numbers for interrupt handler 2&n; *&n; * NOTE: See also the OMAP-1510 and 1610 specific IRQ numbers below&n; */
DECL|macro|IH2_BASE
mdefine_line|#define IH2_BASE&t;&t;32
DECL|macro|INT_KEYBOARD
mdefine_line|#define INT_KEYBOARD&t;&t;(1 + IH2_BASE)
DECL|macro|INT_uWireTX
mdefine_line|#define INT_uWireTX&t;&t;(2 + IH2_BASE)
DECL|macro|INT_uWireRX
mdefine_line|#define INT_uWireRX&t;&t;(3 + IH2_BASE)
DECL|macro|INT_I2C
mdefine_line|#define INT_I2C&t;&t;&t;(4 + IH2_BASE)
DECL|macro|INT_MPUIO
mdefine_line|#define INT_MPUIO&t;&t;(5 + IH2_BASE)
DECL|macro|INT_USB_HHC_1
mdefine_line|#define INT_USB_HHC_1&t;&t;(6 + IH2_BASE)
DECL|macro|INT_McBSP3TX
mdefine_line|#define INT_McBSP3TX&t;&t;(10 + IH2_BASE)
DECL|macro|INT_McBSP3RX
mdefine_line|#define INT_McBSP3RX&t;&t;(11 + IH2_BASE)
DECL|macro|INT_McBSP1TX
mdefine_line|#define INT_McBSP1TX&t;&t;(12 + IH2_BASE)
DECL|macro|INT_McBSP1RX
mdefine_line|#define INT_McBSP1RX&t;&t;(13 + IH2_BASE)
DECL|macro|INT_UART1
mdefine_line|#define INT_UART1&t;&t;(14 + IH2_BASE)
DECL|macro|INT_UART2
mdefine_line|#define INT_UART2&t;&t;(15 + IH2_BASE)
DECL|macro|INT_BT_MCSI1TX
mdefine_line|#define INT_BT_MCSI1TX&t;&t;(16 + IH2_BASE)
DECL|macro|INT_BT_MCSI1RX
mdefine_line|#define INT_BT_MCSI1RX&t;&t;(17 + IH2_BASE)
DECL|macro|INT_USB_W2FC
mdefine_line|#define INT_USB_W2FC&t;&t;(20 + IH2_BASE)
DECL|macro|INT_1WIRE
mdefine_line|#define INT_1WIRE&t;&t;(21 + IH2_BASE)
DECL|macro|INT_OS_TIMER
mdefine_line|#define INT_OS_TIMER&t;&t;(22 + IH2_BASE)
DECL|macro|INT_MMC
mdefine_line|#define INT_MMC&t;&t;&t;(23 + IH2_BASE)
DECL|macro|INT_GAUGE_32K
mdefine_line|#define INT_GAUGE_32K&t;&t;(24 + IH2_BASE)
DECL|macro|INT_RTC_TIMER
mdefine_line|#define INT_RTC_TIMER&t;&t;(25 + IH2_BASE)
DECL|macro|INT_RTC_ALARM
mdefine_line|#define INT_RTC_ALARM&t;&t;(26 + IH2_BASE)
DECL|macro|INT_MEM_STICK
mdefine_line|#define INT_MEM_STICK&t;&t;(27 + IH2_BASE)
DECL|macro|INT_DSP_MMU
mdefine_line|#define INT_DSP_MMU&t;&t;(28 + IH2_BASE)
multiline_comment|/*&n; * OMAP-1510 specific IRQ numbers for interrupt handler 2&n; */
DECL|macro|INT_1510_OS_32kHz_TIMER
mdefine_line|#define INT_1510_OS_32kHz_TIMER (22 + IH2_BASE)
DECL|macro|INT_1510_COM_SPI_RO
mdefine_line|#define INT_1510_COM_SPI_RO&t;(31 + IH2_BASE)
multiline_comment|/*&n; * OMAP-1610 specific IRQ numbers for interrupt handler 2&n; */
DECL|macro|INT_1610_FAC
mdefine_line|#define INT_1610_FAC&t;&t;(0 + IH2_BASE)
DECL|macro|INT_1610_USB_HHC_2
mdefine_line|#define INT_1610_USB_HHC_2&t;(7 + IH2_BASE)
DECL|macro|INT_1610_USB_OTG
mdefine_line|#define INT_1610_USB_OTG&t;(8 + IH2_BASE)
DECL|macro|INT_1610_SoSSI
mdefine_line|#define INT_1610_SoSSI&t;&t;(9 + IH2_BASE)
DECL|macro|INT_1610_SoSSI_MATCH
mdefine_line|#define INT_1610_SoSSI_MATCH&t;(19 + IH2_BASE)
DECL|macro|INT_1610_McBSP2RX_OF
mdefine_line|#define INT_1610_McBSP2RX_OF&t;(31 + IH2_BASE)
DECL|macro|INT_1610_GPIO_BANK2
mdefine_line|#define INT_1610_GPIO_BANK2&t;(40 + IH2_BASE)
DECL|macro|INT_1610_GPIO_BANK3
mdefine_line|#define INT_1610_GPIO_BANK3&t;(41 + IH2_BASE)
DECL|macro|INT_1610_MMC2
mdefine_line|#define INT_1610_MMC2&t;&t;(42 + IH2_BASE)
DECL|macro|INT_1610_GPIO_BANK4
mdefine_line|#define INT_1610_GPIO_BANK4&t;(48 + IH2_BASE)
DECL|macro|INT_1610_SPI
mdefine_line|#define INT_1610_SPI&t;&t;(49 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH6
mdefine_line|#define INT_1610_DMA_CH6&t;(53 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH7
mdefine_line|#define INT_1610_DMA_CH7&t;(54 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH8
mdefine_line|#define INT_1610_DMA_CH8&t;(55 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH9
mdefine_line|#define INT_1610_DMA_CH9&t;(56 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH10
mdefine_line|#define INT_1610_DMA_CH10&t;(57 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH11
mdefine_line|#define INT_1610_DMA_CH11&t;(58 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH12
mdefine_line|#define INT_1610_DMA_CH12&t;(59 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH13
mdefine_line|#define INT_1610_DMA_CH13&t;(60 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH14
mdefine_line|#define INT_1610_DMA_CH14&t;(61 + IH2_BASE)
DECL|macro|INT_1610_DMA_CH15
mdefine_line|#define INT_1610_DMA_CH15&t;(62 + IH2_BASE)
DECL|macro|INT_1610_NAND
mdefine_line|#define INT_1610_NAND&t;&t;(63 + IH2_BASE)
multiline_comment|/*&n; * OMAP-730 specific IRQ numbers for interrupt handler 2&n; */
DECL|macro|INT_730_HW_ERRORS
mdefine_line|#define INT_730_HW_ERRORS&t;(0 + IH2_BASE)
DECL|macro|INT_730_NFIQ_PWR_FAIL
mdefine_line|#define INT_730_NFIQ_PWR_FAIL&t;(1 + IH2_BASE)
DECL|macro|INT_730_CFCD
mdefine_line|#define INT_730_CFCD&t;&t;(2 + IH2_BASE)
DECL|macro|INT_730_CFIREQ
mdefine_line|#define INT_730_CFIREQ&t;&t;(3 + IH2_BASE)
DECL|macro|INT_730_I2C
mdefine_line|#define INT_730_I2C&t;&t;(4 + IH2_BASE)
DECL|macro|INT_730_PCC
mdefine_line|#define INT_730_PCC&t;&t;(5 + IH2_BASE)
DECL|macro|INT_730_MPU_EXT_NIRQ
mdefine_line|#define INT_730_MPU_EXT_NIRQ&t;(6 + IH2_BASE)
DECL|macro|INT_730_SPI_100K_1
mdefine_line|#define INT_730_SPI_100K_1&t;(7 + IH2_BASE)
DECL|macro|INT_730_SYREN_SPI
mdefine_line|#define INT_730_SYREN_SPI&t;(8 + IH2_BASE)
DECL|macro|INT_730_VLYNQ
mdefine_line|#define INT_730_VLYNQ&t;&t;(9 + IH2_BASE)
DECL|macro|INT_730_GPIO_BANK4
mdefine_line|#define INT_730_GPIO_BANK4&t;(10 + IH2_BASE)
DECL|macro|INT_730_McBSP1TX
mdefine_line|#define INT_730_McBSP1TX&t;(11 + IH2_BASE)
DECL|macro|INT_730_McBSP1RX
mdefine_line|#define INT_730_McBSP1RX&t;(12 + IH2_BASE)
DECL|macro|INT_730_McBSP1RX_OF
mdefine_line|#define INT_730_McBSP1RX_OF&t;(13 + IH2_BASE)
DECL|macro|INT_730_UART_MODEM_IRDA_2
mdefine_line|#define INT_730_UART_MODEM_IRDA_2 (14 + IH2_BASE)
DECL|macro|INT_730_UART_MODEM_1
mdefine_line|#define INT_730_UART_MODEM_1&t;(15 + IH2_BASE)
DECL|macro|INT_730_MCSI
mdefine_line|#define INT_730_MCSI&t;&t;(16 + IH2_BASE)
DECL|macro|INT_730_uWireTX
mdefine_line|#define INT_730_uWireTX&t;&t;(17 + IH2_BASE)
DECL|macro|INT_730_uWireRX
mdefine_line|#define INT_730_uWireRX&t;&t;(18 + IH2_BASE)
DECL|macro|INT_730_SMC_CD
mdefine_line|#define INT_730_SMC_CD&t;&t;(19 + IH2_BASE)
DECL|macro|INT_730_SMC_IREQ
mdefine_line|#define INT_730_SMC_IREQ&t;(20 + IH2_BASE)
DECL|macro|INT_730_HDQ_1WIRE
mdefine_line|#define INT_730_HDQ_1WIRE&t;(21 + IH2_BASE)
DECL|macro|INT_730_TIMER32K
mdefine_line|#define INT_730_TIMER32K&t;(22 + IH2_BASE)
DECL|macro|INT_730_MMC_SDIO
mdefine_line|#define INT_730_MMC_SDIO&t;(23 + IH2_BASE)
DECL|macro|INT_730_UPLD
mdefine_line|#define INT_730_UPLD&t;&t;(24 + IH2_BASE)
DECL|macro|INT_730_USB_HHC_1
mdefine_line|#define INT_730_USB_HHC_1&t;(27 + IH2_BASE)
DECL|macro|INT_730_USB_HHC_2
mdefine_line|#define INT_730_USB_HHC_2&t;(28 + IH2_BASE)
DECL|macro|INT_730_USB_GENI
mdefine_line|#define INT_730_USB_GENI&t;(29 + IH2_BASE)
DECL|macro|INT_730_USB_OTG
mdefine_line|#define INT_730_USB_OTG&t;&t;(30 + IH2_BASE)
DECL|macro|INT_730_CAMERA_IF
mdefine_line|#define INT_730_CAMERA_IF&t;(31 + IH2_BASE)
DECL|macro|INT_730_RNG
mdefine_line|#define INT_730_RNG&t;&t;(32 + IH2_BASE)
DECL|macro|INT_730_DUAL_MODE_TIMER
mdefine_line|#define INT_730_DUAL_MODE_TIMER (33 + IH2_BASE)
DECL|macro|INT_730_DBB_RF_EN
mdefine_line|#define INT_730_DBB_RF_EN&t;(34 + IH2_BASE)
DECL|macro|INT_730_MPUIO_KEYPAD
mdefine_line|#define INT_730_MPUIO_KEYPAD&t;(35 + IH2_BASE)
DECL|macro|INT_730_SHA1_MD5
mdefine_line|#define INT_730_SHA1_MD5&t;(36 + IH2_BASE)
DECL|macro|INT_730_SPI_100K_2
mdefine_line|#define INT_730_SPI_100K_2&t;(37 + IH2_BASE)
DECL|macro|INT_730_RNG_IDLE
mdefine_line|#define INT_730_RNG_IDLE&t;(38 + IH2_BASE)
DECL|macro|INT_730_MPUIO
mdefine_line|#define INT_730_MPUIO&t;&t;(39 + IH2_BASE)
DECL|macro|INT_730_LLPC_LCD_CTRL_CAN_BE_OFF
mdefine_line|#define INT_730_LLPC_LCD_CTRL_CAN_BE_OFF&t;(40 + IH2_BASE)
DECL|macro|INT_730_LLPC_OE_FALLING
mdefine_line|#define INT_730_LLPC_OE_FALLING (41 + IH2_BASE)
DECL|macro|INT_730_LLPC_OE_RISING
mdefine_line|#define INT_730_LLPC_OE_RISING&t;(42 + IH2_BASE)
DECL|macro|INT_730_LLPC_VSYNC
mdefine_line|#define INT_730_LLPC_VSYNC&t;(43 + IH2_BASE)
DECL|macro|INT_730_WAKE_UP_REQ
mdefine_line|#define INT_730_WAKE_UP_REQ&t;(46 + IH2_BASE)
DECL|macro|INT_730_DMA_CH6
mdefine_line|#define INT_730_DMA_CH6&t;&t;(53 + IH2_BASE)
DECL|macro|INT_730_DMA_CH7
mdefine_line|#define INT_730_DMA_CH7&t;&t;(54 + IH2_BASE)
DECL|macro|INT_730_DMA_CH8
mdefine_line|#define INT_730_DMA_CH8&t;&t;(55 + IH2_BASE)
DECL|macro|INT_730_DMA_CH9
mdefine_line|#define INT_730_DMA_CH9&t;&t;(56 + IH2_BASE)
DECL|macro|INT_730_DMA_CH10
mdefine_line|#define INT_730_DMA_CH10&t;(57 + IH2_BASE)
DECL|macro|INT_730_DMA_CH11
mdefine_line|#define INT_730_DMA_CH11&t;(58 + IH2_BASE)
DECL|macro|INT_730_DMA_CH12
mdefine_line|#define INT_730_DMA_CH12&t;(59 + IH2_BASE)
DECL|macro|INT_730_DMA_CH13
mdefine_line|#define INT_730_DMA_CH13&t;(60 + IH2_BASE)
DECL|macro|INT_730_DMA_CH14
mdefine_line|#define INT_730_DMA_CH14&t;(61 + IH2_BASE)
DECL|macro|INT_730_DMA_CH15
mdefine_line|#define INT_730_DMA_CH15&t;(62 + IH2_BASE)
DECL|macro|INT_730_NAND
mdefine_line|#define INT_730_NAND&t;&t;(63 + IH2_BASE)
multiline_comment|/* Max. 128 level 2 IRQs (OMAP1610), 192 GPIOs (OMAP730) and&n; * 16 MPUIO lines */
DECL|macro|OMAP_MAX_GPIO_LINES
mdefine_line|#define OMAP_MAX_GPIO_LINES&t;192
DECL|macro|IH_GPIO_BASE
mdefine_line|#define IH_GPIO_BASE&t;&t;(128 + IH2_BASE)
DECL|macro|IH_MPUIO_BASE
mdefine_line|#define IH_MPUIO_BASE&t;&t;(OMAP_MAX_GPIO_LINES + IH_GPIO_BASE)
DECL|macro|IH_BOARD_BASE
mdefine_line|#define IH_BOARD_BASE&t;&t;(16 + IH_MPUIO_BASE)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|omap_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The definition of NR_IRQS is in board-specific header file, which is&n; * included via hardware.h&n; */
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#ifndef NR_IRQS
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS                 IH_BOARD_BASE
macro_line|#endif
macro_line|#endif
eof
