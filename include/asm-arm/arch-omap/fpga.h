multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/fpga.h&n; *&n; * Interrupt handler for OMAP-1510 FPGA&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; *&n; * Separated FPGA interrupts from innovator1510.c and cleaned up for 2.6&n; * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_FPGA_H
DECL|macro|__ASM_ARCH_OMAP_FPGA_H
mdefine_line|#define __ASM_ARCH_OMAP_FPGA_H
macro_line|#if defined(CONFIG_MACH_OMAP_INNOVATOR) &amp;&amp; defined(CONFIG_ARCH_OMAP1510)
r_extern
r_void
id|omap1510_fpga_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|omap1510_fpga_init_irq
mdefine_line|#define omap1510_fpga_init_irq()&t;(0)
macro_line|#endif
DECL|macro|fpga_read
mdefine_line|#define fpga_read(reg)&t;&t;&t;__raw_readb(reg)
DECL|macro|fpga_write
mdefine_line|#define fpga_write(val, reg)&t;&t;__raw_writeb(val, reg)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; *  H2/P2 Debug board FPGA&n; * ---------------------------------------------------------------------------&n; */
multiline_comment|/* maps in the FPGA registers and the ETHR registers */
DECL|macro|H2P2_DBG_FPGA_BASE
mdefine_line|#define H2P2_DBG_FPGA_BASE&t;&t;0xE8000000&t;/* VA */
DECL|macro|H2P2_DBG_FPGA_SIZE
mdefine_line|#define H2P2_DBG_FPGA_SIZE&t;&t;SZ_4K&t;&t;/* SIZE */
DECL|macro|H2P2_DBG_FPGA_START
mdefine_line|#define H2P2_DBG_FPGA_START&t;&t;0x04000000&t;/* PA */
DECL|macro|H2P2_DBG_FPGA_ETHR_START
mdefine_line|#define H2P2_DBG_FPGA_ETHR_START&t;(H2P2_DBG_FPGA_START + 0x300)
DECL|macro|H2P2_DBG_FPGA_FPGA_REV
mdefine_line|#define H2P2_DBG_FPGA_FPGA_REV&t;&t;(H2P2_DBG_FPGA_BASE + 0x10)&t;/* FPGA Revision */
DECL|macro|H2P2_DBG_FPGA_BOARD_REV
mdefine_line|#define H2P2_DBG_FPGA_BOARD_REV&t;&t;(H2P2_DBG_FPGA_BASE + 0x12)&t;/* Board Revision */
DECL|macro|H2P2_DBG_FPGA_GPIO
mdefine_line|#define H2P2_DBG_FPGA_GPIO&t;&t;(H2P2_DBG_FPGA_BASE + 0x14)&t;/* GPIO outputs */
DECL|macro|H2P2_DBG_FPGA_LEDS
mdefine_line|#define H2P2_DBG_FPGA_LEDS&t;&t;(H2P2_DBG_FPGA_BASE + 0x16)&t;/* LEDs outputs */
DECL|macro|H2P2_DBG_FPGA_MISC_INPUTS
mdefine_line|#define H2P2_DBG_FPGA_MISC_INPUTS&t;(H2P2_DBG_FPGA_BASE + 0x18)&t;/* Misc inputs */
DECL|macro|H2P2_DBG_FPGA_LAN_STATUS
mdefine_line|#define H2P2_DBG_FPGA_LAN_STATUS&t;(H2P2_DBG_FPGA_BASE + 0x1A)&t;/* LAN Status line */
DECL|macro|H2P2_DBG_FPGA_LAN_RESET
mdefine_line|#define H2P2_DBG_FPGA_LAN_RESET&t;&t;(H2P2_DBG_FPGA_BASE + 0x1C)&t;/* LAN Reset line */
multiline_comment|/* NOTE:  most boards don&squot;t have a static mapping for the FPGA ... */
DECL|struct|h2p2_dbg_fpga
r_struct
id|h2p2_dbg_fpga
(brace
multiline_comment|/* offset 0x00 */
DECL|member|smc91x
id|u16
id|smc91x
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* offset 0x10 */
DECL|member|fpga_rev
id|u16
id|fpga_rev
suffix:semicolon
DECL|member|board_rev
id|u16
id|board_rev
suffix:semicolon
DECL|member|gpio_outputs
id|u16
id|gpio_outputs
suffix:semicolon
DECL|member|leds
id|u16
id|leds
suffix:semicolon
multiline_comment|/* offset 0x18 */
DECL|member|misc_inputs
id|u16
id|misc_inputs
suffix:semicolon
DECL|member|lan_status
id|u16
id|lan_status
suffix:semicolon
DECL|member|lan_reset
id|u16
id|lan_reset
suffix:semicolon
DECL|member|reserved0
id|u16
id|reserved0
suffix:semicolon
multiline_comment|/* offset 0x20 */
DECL|member|ps2_data
id|u16
id|ps2_data
suffix:semicolon
DECL|member|ps2_ctrl
id|u16
id|ps2_ctrl
suffix:semicolon
multiline_comment|/* plus also 4 rs232 ports ... */
)brace
suffix:semicolon
multiline_comment|/* LEDs definition on debug board (16 LEDs, all physically green) */
DECL|macro|H2P2_DBG_FPGA_LED_GREEN
mdefine_line|#define H2P2_DBG_FPGA_LED_GREEN&t;&t;(1 &lt;&lt; 15)
DECL|macro|H2P2_DBG_FPGA_LED_AMBER
mdefine_line|#define H2P2_DBG_FPGA_LED_AMBER&t;&t;(1 &lt;&lt; 14)
DECL|macro|H2P2_DBG_FPGA_LED_RED
mdefine_line|#define H2P2_DBG_FPGA_LED_RED&t;&t;(1 &lt;&lt; 13)
DECL|macro|H2P2_DBG_FPGA_LED_BLUE
mdefine_line|#define H2P2_DBG_FPGA_LED_BLUE&t;&t;(1 &lt;&lt; 12)
multiline_comment|/*  cpu0 load-meter LEDs */
DECL|macro|H2P2_DBG_FPGA_LOAD_METER
mdefine_line|#define H2P2_DBG_FPGA_LOAD_METER&t;(1 &lt;&lt; 0)&t;
singleline_comment|// A bit of fun on our board ...
DECL|macro|H2P2_DBG_FPGA_LOAD_METER_SIZE
mdefine_line|#define H2P2_DBG_FPGA_LOAD_METER_SIZE&t;11
DECL|macro|H2P2_DBG_FPGA_LOAD_METER_MASK
mdefine_line|#define H2P2_DBG_FPGA_LOAD_METER_MASK&t;((1 &lt;&lt; H2P2_DBG_FPGA_LOAD_METER_SIZE) - 1)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; *  OMAP-1510 FPGA&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP1510_FPGA_BASE
mdefine_line|#define OMAP1510_FPGA_BASE&t;&t;&t;0xE8000000&t;/* Virtual */
DECL|macro|OMAP1510_FPGA_SIZE
mdefine_line|#define OMAP1510_FPGA_SIZE&t;&t;&t;SZ_4K
DECL|macro|OMAP1510_FPGA_START
mdefine_line|#define OMAP1510_FPGA_START&t;&t;&t;0x08000000&t;/* Physical */
multiline_comment|/* Revision */
DECL|macro|OMAP1510_FPGA_REV_LOW
mdefine_line|#define OMAP1510_FPGA_REV_LOW&t;&t;&t;(OMAP1510_FPGA_BASE + 0x0)
DECL|macro|OMAP1510_FPGA_REV_HIGH
mdefine_line|#define OMAP1510_FPGA_REV_HIGH&t;&t;&t;(OMAP1510_FPGA_BASE + 0x1)
DECL|macro|OMAP1510_FPGA_LCD_PANEL_CONTROL
mdefine_line|#define OMAP1510_FPGA_LCD_PANEL_CONTROL&t;&t;(OMAP1510_FPGA_BASE + 0x2)
DECL|macro|OMAP1510_FPGA_LED_DIGIT
mdefine_line|#define OMAP1510_FPGA_LED_DIGIT&t;&t;&t;(OMAP1510_FPGA_BASE + 0x3)
DECL|macro|INNOVATOR_FPGA_HID_SPI
mdefine_line|#define INNOVATOR_FPGA_HID_SPI&t;&t;&t;(OMAP1510_FPGA_BASE + 0x4)
DECL|macro|OMAP1510_FPGA_POWER
mdefine_line|#define OMAP1510_FPGA_POWER&t;&t;&t;(OMAP1510_FPGA_BASE + 0x5)
multiline_comment|/* Interrupt status */
DECL|macro|OMAP1510_FPGA_ISR_LO
mdefine_line|#define OMAP1510_FPGA_ISR_LO&t;&t;&t;(OMAP1510_FPGA_BASE + 0x6)
DECL|macro|OMAP1510_FPGA_ISR_HI
mdefine_line|#define OMAP1510_FPGA_ISR_HI&t;&t;&t;(OMAP1510_FPGA_BASE + 0x7)
multiline_comment|/* Interrupt mask */
DECL|macro|OMAP1510_FPGA_IMR_LO
mdefine_line|#define OMAP1510_FPGA_IMR_LO&t;&t;&t;(OMAP1510_FPGA_BASE + 0x8)
DECL|macro|OMAP1510_FPGA_IMR_HI
mdefine_line|#define OMAP1510_FPGA_IMR_HI&t;&t;&t;(OMAP1510_FPGA_BASE + 0x9)
multiline_comment|/* Reset registers */
DECL|macro|OMAP1510_FPGA_HOST_RESET
mdefine_line|#define OMAP1510_FPGA_HOST_RESET&t;&t;(OMAP1510_FPGA_BASE + 0xa)
DECL|macro|OMAP1510_FPGA_RST
mdefine_line|#define OMAP1510_FPGA_RST&t;&t;&t;(OMAP1510_FPGA_BASE + 0xb)
DECL|macro|OMAP1510_FPGA_AUDIO
mdefine_line|#define OMAP1510_FPGA_AUDIO&t;&t;&t;(OMAP1510_FPGA_BASE + 0xc)
DECL|macro|OMAP1510_FPGA_DIP
mdefine_line|#define OMAP1510_FPGA_DIP&t;&t;&t;(OMAP1510_FPGA_BASE + 0xe)
DECL|macro|OMAP1510_FPGA_FPGA_IO
mdefine_line|#define OMAP1510_FPGA_FPGA_IO&t;&t;&t;(OMAP1510_FPGA_BASE + 0xf)
DECL|macro|OMAP1510_FPGA_UART1
mdefine_line|#define OMAP1510_FPGA_UART1&t;&t;&t;(OMAP1510_FPGA_BASE + 0x14)
DECL|macro|OMAP1510_FPGA_UART2
mdefine_line|#define OMAP1510_FPGA_UART2&t;&t;&t;(OMAP1510_FPGA_BASE + 0x15)
DECL|macro|OMAP1510_FPGA_OMAP1510_STATUS
mdefine_line|#define OMAP1510_FPGA_OMAP1510_STATUS&t;&t;(OMAP1510_FPGA_BASE + 0x16)
DECL|macro|OMAP1510_FPGA_BOARD_REV
mdefine_line|#define OMAP1510_FPGA_BOARD_REV&t;&t;&t;(OMAP1510_FPGA_BASE + 0x18)
DECL|macro|OMAP1510P1_PPT_DATA
mdefine_line|#define OMAP1510P1_PPT_DATA&t;&t;&t;(OMAP1510_FPGA_BASE + 0x100)
DECL|macro|OMAP1510P1_PPT_STATUS
mdefine_line|#define OMAP1510P1_PPT_STATUS&t;&t;&t;(OMAP1510_FPGA_BASE + 0x101)
DECL|macro|OMAP1510P1_PPT_CONTROL
mdefine_line|#define OMAP1510P1_PPT_CONTROL&t;&t;&t;(OMAP1510_FPGA_BASE + 0x102)
DECL|macro|OMAP1510_FPGA_TOUCHSCREEN
mdefine_line|#define OMAP1510_FPGA_TOUCHSCREEN&t;&t;(OMAP1510_FPGA_BASE + 0x204)
DECL|macro|INNOVATOR_FPGA_INFO
mdefine_line|#define INNOVATOR_FPGA_INFO&t;&t;&t;(OMAP1510_FPGA_BASE + 0x205)
DECL|macro|INNOVATOR_FPGA_LCD_BRIGHT_LO
mdefine_line|#define INNOVATOR_FPGA_LCD_BRIGHT_LO&t;&t;(OMAP1510_FPGA_BASE + 0x206)
DECL|macro|INNOVATOR_FPGA_LCD_BRIGHT_HI
mdefine_line|#define INNOVATOR_FPGA_LCD_BRIGHT_HI&t;&t;(OMAP1510_FPGA_BASE + 0x207)
DECL|macro|INNOVATOR_FPGA_LED_GRN_LO
mdefine_line|#define INNOVATOR_FPGA_LED_GRN_LO&t;&t;(OMAP1510_FPGA_BASE + 0x208)
DECL|macro|INNOVATOR_FPGA_LED_GRN_HI
mdefine_line|#define INNOVATOR_FPGA_LED_GRN_HI&t;&t;(OMAP1510_FPGA_BASE + 0x209)
DECL|macro|INNOVATOR_FPGA_LED_RED_LO
mdefine_line|#define INNOVATOR_FPGA_LED_RED_LO&t;&t;(OMAP1510_FPGA_BASE + 0x20a)
DECL|macro|INNOVATOR_FPGA_LED_RED_HI
mdefine_line|#define INNOVATOR_FPGA_LED_RED_HI&t;&t;(OMAP1510_FPGA_BASE + 0x20b)
DECL|macro|INNOVATOR_FPGA_CAM_USB_CONTROL
mdefine_line|#define INNOVATOR_FPGA_CAM_USB_CONTROL&t;&t;(OMAP1510_FPGA_BASE + 0x20c)
DECL|macro|INNOVATOR_FPGA_EXP_CONTROL
mdefine_line|#define INNOVATOR_FPGA_EXP_CONTROL&t;&t;(OMAP1510_FPGA_BASE + 0x20d)
DECL|macro|INNOVATOR_FPGA_ISR2
mdefine_line|#define INNOVATOR_FPGA_ISR2&t;&t;&t;(OMAP1510_FPGA_BASE + 0x20e)
DECL|macro|INNOVATOR_FPGA_IMR2
mdefine_line|#define INNOVATOR_FPGA_IMR2&t;&t;&t;(OMAP1510_FPGA_BASE + 0x210)
DECL|macro|OMAP1510_FPGA_ETHR_START
mdefine_line|#define OMAP1510_FPGA_ETHR_START&t;&t;(OMAP1510_FPGA_START + 0x300)
multiline_comment|/*&n; * Power up Giga UART driver, turn on HID clock.&n; * Turn off BT power, since we&squot;re not using it and it&n; * draws power.&n; */
DECL|macro|OMAP1510_FPGA_RESET_VALUE
mdefine_line|#define OMAP1510_FPGA_RESET_VALUE&t;&t;0x42
DECL|macro|OMAP1510_FPGA_PCR_IF_PD0
mdefine_line|#define OMAP1510_FPGA_PCR_IF_PD0&t;&t;(1 &lt;&lt; 7)
DECL|macro|OMAP1510_FPGA_PCR_COM2_EN
mdefine_line|#define OMAP1510_FPGA_PCR_COM2_EN&t;&t;(1 &lt;&lt; 6)
DECL|macro|OMAP1510_FPGA_PCR_COM1_EN
mdefine_line|#define OMAP1510_FPGA_PCR_COM1_EN&t;&t;(1 &lt;&lt; 5)
DECL|macro|OMAP1510_FPGA_PCR_EXP_PD0
mdefine_line|#define OMAP1510_FPGA_PCR_EXP_PD0&t;&t;(1 &lt;&lt; 4)
DECL|macro|OMAP1510_FPGA_PCR_EXP_PD1
mdefine_line|#define OMAP1510_FPGA_PCR_EXP_PD1&t;&t;(1 &lt;&lt; 3)
DECL|macro|OMAP1510_FPGA_PCR_48MHZ_CLK
mdefine_line|#define OMAP1510_FPGA_PCR_48MHZ_CLK&t;&t;(1 &lt;&lt; 2)
DECL|macro|OMAP1510_FPGA_PCR_4MHZ_CLK
mdefine_line|#define OMAP1510_FPGA_PCR_4MHZ_CLK&t;&t;(1 &lt;&lt; 1)
DECL|macro|OMAP1510_FPGA_PCR_RSRVD_BIT0
mdefine_line|#define OMAP1510_FPGA_PCR_RSRVD_BIT0&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * Innovator/OMAP1510 FPGA HID register bit definitions&n; */
DECL|macro|OMAP1510_FPGA_HID_SCLK
mdefine_line|#define OMAP1510_FPGA_HID_SCLK&t;(1&lt;&lt;0)&t;/* output */
DECL|macro|OMAP1510_FPGA_HID_MOSI
mdefine_line|#define OMAP1510_FPGA_HID_MOSI&t;(1&lt;&lt;1)&t;/* output */
DECL|macro|OMAP1510_FPGA_HID_nSS
mdefine_line|#define OMAP1510_FPGA_HID_nSS&t;(1&lt;&lt;2)&t;/* output 0/1 chip idle/select */
DECL|macro|OMAP1510_FPGA_HID_nHSUS
mdefine_line|#define OMAP1510_FPGA_HID_nHSUS&t;(1&lt;&lt;3)&t;/* output 0/1 host active/suspended */
DECL|macro|OMAP1510_FPGA_HID_MISO
mdefine_line|#define OMAP1510_FPGA_HID_MISO&t;(1&lt;&lt;4)&t;/* input */
DECL|macro|OMAP1510_FPGA_HID_ATN
mdefine_line|#define OMAP1510_FPGA_HID_ATN&t;(1&lt;&lt;5)&t;/* input  0/1 chip idle/ATN */
DECL|macro|OMAP1510_FPGA_HID_rsrvd
mdefine_line|#define OMAP1510_FPGA_HID_rsrvd&t;(1&lt;&lt;6)
DECL|macro|OMAP1510_FPGA_HID_RESETn
mdefine_line|#define OMAP1510_FPGA_HID_RESETn (1&lt;&lt;7)&t;/* output - 0/1 USAR reset/run */
multiline_comment|/* The FPGA IRQ is cascaded through GPIO_13 */
DECL|macro|OMAP1510_INT_FPGA
mdefine_line|#define OMAP1510_INT_FPGA&t;&t;(IH_GPIO_BASE + 13)
multiline_comment|/* IRQ Numbers for interrupts muxed through the FPGA */
DECL|macro|OMAP1510_IH_FPGA_BASE
mdefine_line|#define OMAP1510_IH_FPGA_BASE&t;&t;IH_BOARD_BASE
DECL|macro|OMAP1510_INT_FPGA_ATN
mdefine_line|#define OMAP1510_INT_FPGA_ATN&t;&t;(OMAP1510_IH_FPGA_BASE + 0)
DECL|macro|OMAP1510_INT_FPGA_ACK
mdefine_line|#define OMAP1510_INT_FPGA_ACK&t;&t;(OMAP1510_IH_FPGA_BASE + 1)
DECL|macro|OMAP1510_INT_FPGA2
mdefine_line|#define OMAP1510_INT_FPGA2&t;&t;(OMAP1510_IH_FPGA_BASE + 2)
DECL|macro|OMAP1510_INT_FPGA3
mdefine_line|#define OMAP1510_INT_FPGA3&t;&t;(OMAP1510_IH_FPGA_BASE + 3)
DECL|macro|OMAP1510_INT_FPGA4
mdefine_line|#define OMAP1510_INT_FPGA4&t;&t;(OMAP1510_IH_FPGA_BASE + 4)
DECL|macro|OMAP1510_INT_FPGA5
mdefine_line|#define OMAP1510_INT_FPGA5&t;&t;(OMAP1510_IH_FPGA_BASE + 5)
DECL|macro|OMAP1510_INT_FPGA6
mdefine_line|#define OMAP1510_INT_FPGA6&t;&t;(OMAP1510_IH_FPGA_BASE + 6)
DECL|macro|OMAP1510_INT_FPGA7
mdefine_line|#define OMAP1510_INT_FPGA7&t;&t;(OMAP1510_IH_FPGA_BASE + 7)
DECL|macro|OMAP1510_INT_FPGA8
mdefine_line|#define OMAP1510_INT_FPGA8&t;&t;(OMAP1510_IH_FPGA_BASE + 8)
DECL|macro|OMAP1510_INT_FPGA9
mdefine_line|#define OMAP1510_INT_FPGA9&t;&t;(OMAP1510_IH_FPGA_BASE + 9)
DECL|macro|OMAP1510_INT_FPGA10
mdefine_line|#define OMAP1510_INT_FPGA10&t;&t;(OMAP1510_IH_FPGA_BASE + 10)
DECL|macro|OMAP1510_INT_FPGA11
mdefine_line|#define OMAP1510_INT_FPGA11&t;&t;(OMAP1510_IH_FPGA_BASE + 11)
DECL|macro|OMAP1510_INT_FPGA12
mdefine_line|#define OMAP1510_INT_FPGA12&t;&t;(OMAP1510_IH_FPGA_BASE + 12)
DECL|macro|OMAP1510_INT_ETHER
mdefine_line|#define OMAP1510_INT_ETHER&t;&t;(OMAP1510_IH_FPGA_BASE + 13)
DECL|macro|OMAP1510_INT_FPGAUART1
mdefine_line|#define OMAP1510_INT_FPGAUART1&t;&t;(OMAP1510_IH_FPGA_BASE + 14)
DECL|macro|OMAP1510_INT_FPGAUART2
mdefine_line|#define OMAP1510_INT_FPGAUART2&t;&t;(OMAP1510_IH_FPGA_BASE + 15)
DECL|macro|OMAP1510_INT_FPGA_TS
mdefine_line|#define OMAP1510_INT_FPGA_TS&t;&t;(OMAP1510_IH_FPGA_BASE + 16)
DECL|macro|OMAP1510_INT_FPGA17
mdefine_line|#define OMAP1510_INT_FPGA17&t;&t;(OMAP1510_IH_FPGA_BASE + 17)
DECL|macro|OMAP1510_INT_FPGA_CAM
mdefine_line|#define OMAP1510_INT_FPGA_CAM&t;&t;(OMAP1510_IH_FPGA_BASE + 18)
DECL|macro|OMAP1510_INT_FPGA_RTC_A
mdefine_line|#define OMAP1510_INT_FPGA_RTC_A&t;&t;(OMAP1510_IH_FPGA_BASE + 19)
DECL|macro|OMAP1510_INT_FPGA_RTC_B
mdefine_line|#define OMAP1510_INT_FPGA_RTC_B&t;&t;(OMAP1510_IH_FPGA_BASE + 20)
DECL|macro|OMAP1510_INT_FPGA_CD
mdefine_line|#define OMAP1510_INT_FPGA_CD&t;&t;(OMAP1510_IH_FPGA_BASE + 21)
DECL|macro|OMAP1510_INT_FPGA22
mdefine_line|#define OMAP1510_INT_FPGA22&t;&t;(OMAP1510_IH_FPGA_BASE + 22)
DECL|macro|OMAP1510_INT_FPGA23
mdefine_line|#define OMAP1510_INT_FPGA23&t;&t;(OMAP1510_IH_FPGA_BASE + 23)
macro_line|#endif
eof
