multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/mux.h&n; *&n; * Table of the Omap register configurations for the FUNC_MUX and&n; * PULL_DWN combinations.&n; *&n; * Copyright (C) 2003 Nokia Corporation&n; *&n; * Written by Tony Lindgren &lt;tony.lindgren@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * NOTE: Please use the following naming style for new pin entries.&n; *&t; For example, W8_1610_MMC2_DAT0, where:&n; *&t; - W8&t;     = ball&n; *&t; - 1610&t;     = 1510 or 1610, none if common for both 1510 and 1610&n; *&t; - MMC2_DAT0 = function&n; *&n; * Change log:&n; *   Added entry for the I2C interface. (02Feb 2004)&n; *   Copyright (C) 2004 Texas Instruments&n; *&n; *   Added entry for the keypad and uwire CS1. (09Mar 2004)&n; *   Copyright (C) 2004 Texas Instruments&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MUX_H
DECL|macro|__ASM_ARCH_MUX_H
mdefine_line|#define __ASM_ARCH_MUX_H
DECL|macro|PU_PD_SEL_NA
mdefine_line|#define PU_PD_SEL_NA&t;&t;0&t;/* No pu_pd reg available */
DECL|macro|PULL_DWN_CTRL_NA
mdefine_line|#define PULL_DWN_CTRL_NA&t;0&t;/* No pull-down control needed */
DECL|macro|DEBUG_MUX
mdefine_line|#define DEBUG_MUX
macro_line|#ifdef DEBUG_MUX
DECL|macro|MUX_REG
mdefine_line|#define MUX_REG(reg, mode_offset, mode) .mux_reg_name = &quot;FUNC_MUX_CTRL_&quot;#reg, &bslash;&n;&t;&t;&t;&t;&t;.mux_reg = FUNC_MUX_CTRL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.mask_offset = mode_offset, &bslash;&n;&t;&t;&t;&t;&t;.mask = mode,
DECL|macro|PULL_REG
mdefine_line|#define PULL_REG(reg, bit, status)&t;.pull_name = &quot;PULL_DWN_CTRL_&quot;#reg, &bslash;&n;&t;&t;&t;&t;&t;.pull_reg = PULL_DWN_CTRL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.pull_bit = bit, &bslash;&n;&t;&t;&t;&t;&t;.pull_val = status,
DECL|macro|PU_PD_REG
mdefine_line|#define PU_PD_REG(reg, status)&t;&t;.pu_pd_name = &quot;PU_PD_SEL_&quot;#reg, &bslash;&n;&t;&t;&t;&t;&t;.pu_pd_reg = PU_PD_SEL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.pu_pd_val = status,
macro_line|#else
DECL|macro|MUX_REG
mdefine_line|#define MUX_REG(reg, mode_offset, mode) .mux_reg = FUNC_MUX_CTRL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.mask_offset = mode_offset, &bslash;&n;&t;&t;&t;&t;&t;.mask = mode,
DECL|macro|PULL_REG
mdefine_line|#define PULL_REG(reg, bit, status)&t;.pull_reg = PULL_DWN_CTRL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.pull_bit = bit, &bslash;&n;&t;&t;&t;&t;&t;.pull_val = status,
DECL|macro|PU_PD_REG
mdefine_line|#define PU_PD_REG(reg, status)&t;&t;.pu_pd_reg = PU_PD_SEL_##reg, &bslash;&n;&t;&t;&t;&t;&t;.pu_pd_val = status,
macro_line|#endif 
singleline_comment|// DEBUG_MUX
DECL|macro|MUX_CFG
mdefine_line|#define MUX_CFG(desc, mux_reg, mode_offset, mode,&t;&bslash;&n;&t;&t;pull_reg, pull_bit, pull_status,&t;&bslash;&n;&t;&t;pu_pd_reg, pu_pd_status, debug_status)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.name =&t; desc,&t;&t;&t;&t;&t;&bslash;&n;&t;.debug = debug_status,&t;&t;&t;&t;&bslash;&n;&t;MUX_REG(mux_reg, mode_offset, mode)&t;&t;&bslash;&n;&t;PULL_REG(pull_reg, pull_bit, pull_status)&t;&bslash;&n;&t;PU_PD_REG(pu_pd_reg, pu_pd_status)&t;&t;&bslash;&n;},
DECL|macro|PULL_DISABLED
mdefine_line|#define PULL_DISABLED&t;0
DECL|macro|PULL_ENABLED
mdefine_line|#define PULL_ENABLED&t;1
DECL|macro|PULL_DOWN
mdefine_line|#define PULL_DOWN&t;0
DECL|macro|PULL_UP
mdefine_line|#define PULL_UP&t;&t;1
r_typedef
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|busy
r_int
r_char
id|busy
suffix:semicolon
DECL|member|debug
r_int
r_char
id|debug
suffix:semicolon
DECL|member|mux_reg_name
r_const
r_char
op_star
id|mux_reg_name
suffix:semicolon
DECL|member|mux_reg
r_const
r_int
r_int
id|mux_reg
suffix:semicolon
DECL|member|mask_offset
r_const
r_int
r_char
id|mask_offset
suffix:semicolon
DECL|member|mask
r_const
r_int
r_char
id|mask
suffix:semicolon
DECL|member|pull_name
r_const
r_char
op_star
id|pull_name
suffix:semicolon
DECL|member|pull_reg
r_const
r_int
r_int
id|pull_reg
suffix:semicolon
DECL|member|pull_val
r_const
r_int
r_char
id|pull_val
suffix:semicolon
DECL|member|pull_bit
r_const
r_int
r_char
id|pull_bit
suffix:semicolon
DECL|member|pu_pd_name
r_const
r_char
op_star
id|pu_pd_name
suffix:semicolon
DECL|member|pu_pd_reg
r_const
r_int
r_int
id|pu_pd_reg
suffix:semicolon
DECL|member|pu_pd_val
r_const
r_int
r_char
id|pu_pd_val
suffix:semicolon
DECL|typedef|reg_cfg_set
)brace
id|reg_cfg_set
suffix:semicolon
multiline_comment|/*&n; * Lookup table for FUNC_MUX and PULL_DWN register combinations for each&n; * device. See also reg_cfg_table below for the register values.&n; */
r_typedef
r_enum
(brace
multiline_comment|/* UART1 (BT_UART_GATING)*/
DECL|enumerator|UART1_TX
id|UART1_TX
op_assign
l_int|0
comma
DECL|enumerator|UART1_RTS
id|UART1_RTS
comma
multiline_comment|/* UART2 (COM_UART_GATING)*/
DECL|enumerator|UART2_TX
id|UART2_TX
comma
DECL|enumerator|UART2_RX
id|UART2_RX
comma
DECL|enumerator|UART2_CTS
id|UART2_CTS
comma
DECL|enumerator|UART2_RTS
id|UART2_RTS
comma
multiline_comment|/* UART3 (GIGA_UART_GATING) */
DECL|enumerator|UART3_TX
id|UART3_TX
comma
DECL|enumerator|UART3_RX
id|UART3_RX
comma
DECL|enumerator|UART3_CTS
id|UART3_CTS
comma
DECL|enumerator|UART3_RTS
id|UART3_RTS
comma
DECL|enumerator|UART3_CLKREQ
id|UART3_CLKREQ
comma
DECL|enumerator|UART3_BCLK
id|UART3_BCLK
comma
multiline_comment|/* 12MHz clock out */
multiline_comment|/* USB master generic */
DECL|enumerator|R18_USB_VBUS
id|R18_USB_VBUS
comma
DECL|enumerator|R18_1510_USB_GPIO0
id|R18_1510_USB_GPIO0
comma
DECL|enumerator|W4_USB_PUEN
id|W4_USB_PUEN
comma
DECL|enumerator|W4_USB_CLKO
id|W4_USB_CLKO
comma
multiline_comment|/* USB1 master */
DECL|enumerator|USB1_SUSP
id|USB1_SUSP
comma
DECL|enumerator|USB1_SEO
id|USB1_SEO
comma
DECL|enumerator|USB1_TXEN
id|USB1_TXEN
comma
DECL|enumerator|USB1_TXD
id|USB1_TXD
comma
DECL|enumerator|USB1_VP
id|USB1_VP
comma
DECL|enumerator|USB1_VM
id|USB1_VM
comma
DECL|enumerator|USB1_RCV
id|USB1_RCV
comma
DECL|enumerator|USB1_SPEED
id|USB1_SPEED
comma
multiline_comment|/* USB2 master */
DECL|enumerator|USB2_SUSP
id|USB2_SUSP
comma
DECL|enumerator|USB2_VP
id|USB2_VP
comma
DECL|enumerator|USB2_TXEN
id|USB2_TXEN
comma
DECL|enumerator|USB2_VM
id|USB2_VM
comma
DECL|enumerator|USB2_RCV
id|USB2_RCV
comma
DECL|enumerator|USB2_SEO
id|USB2_SEO
comma
DECL|enumerator|USB2_TXD
id|USB2_TXD
comma
multiline_comment|/* OMAP-1510 GPIO */
DECL|enumerator|R18_1510_GPIO0
id|R18_1510_GPIO0
comma
DECL|enumerator|R19_1510_GPIO1
id|R19_1510_GPIO1
comma
DECL|enumerator|M14_1510_GPIO2
id|M14_1510_GPIO2
comma
multiline_comment|/* MPUIO */
DECL|enumerator|MPUIO2
id|MPUIO2
comma
DECL|enumerator|MPUIO4
id|MPUIO4
comma
DECL|enumerator|MPUIO5
id|MPUIO5
comma
DECL|enumerator|T20_1610_MPUIO5
id|T20_1610_MPUIO5
comma
DECL|enumerator|W11_1610_MPUIO6
id|W11_1610_MPUIO6
comma
DECL|enumerator|V10_1610_MPUIO7
id|V10_1610_MPUIO7
comma
DECL|enumerator|W11_1610_MPUIO9
id|W11_1610_MPUIO9
comma
DECL|enumerator|V10_1610_MPUIO10
id|V10_1610_MPUIO10
comma
DECL|enumerator|W10_1610_MPUIO11
id|W10_1610_MPUIO11
comma
DECL|enumerator|E20_1610_MPUIO13
id|E20_1610_MPUIO13
comma
DECL|enumerator|U20_1610_MPUIO14
id|U20_1610_MPUIO14
comma
DECL|enumerator|E19_1610_MPUIO15
id|E19_1610_MPUIO15
comma
multiline_comment|/* MCBSP2 */
DECL|enumerator|MCBSP2_CLKR
id|MCBSP2_CLKR
comma
DECL|enumerator|MCBSP2_CLKX
id|MCBSP2_CLKX
comma
DECL|enumerator|MCBSP2_DR
id|MCBSP2_DR
comma
DECL|enumerator|MCBSP2_DX
id|MCBSP2_DX
comma
DECL|enumerator|MCBSP2_FSR
id|MCBSP2_FSR
comma
DECL|enumerator|MCBSP2_FSX
id|MCBSP2_FSX
comma
multiline_comment|/* MCBSP3 */
DECL|enumerator|MCBSP3_CLKX
id|MCBSP3_CLKX
comma
multiline_comment|/* Misc ballouts */
DECL|enumerator|BALLOUT_V8_ARMIO3
id|BALLOUT_V8_ARMIO3
comma
multiline_comment|/* OMAP-1610 MMC2 */
DECL|enumerator|W8_1610_MMC2_DAT0
id|W8_1610_MMC2_DAT0
comma
DECL|enumerator|V8_1610_MMC2_DAT1
id|V8_1610_MMC2_DAT1
comma
DECL|enumerator|W15_1610_MMC2_DAT2
id|W15_1610_MMC2_DAT2
comma
DECL|enumerator|R10_1610_MMC2_DAT3
id|R10_1610_MMC2_DAT3
comma
DECL|enumerator|Y10_1610_MMC2_CLK
id|Y10_1610_MMC2_CLK
comma
DECL|enumerator|Y8_1610_MMC2_CMD
id|Y8_1610_MMC2_CMD
comma
DECL|enumerator|V9_1610_MMC2_CMDDIR
id|V9_1610_MMC2_CMDDIR
comma
DECL|enumerator|V5_1610_MMC2_DATDIR0
id|V5_1610_MMC2_DATDIR0
comma
DECL|enumerator|W19_1610_MMC2_DATDIR1
id|W19_1610_MMC2_DATDIR1
comma
DECL|enumerator|R18_1610_MMC2_CLKIN
id|R18_1610_MMC2_CLKIN
comma
multiline_comment|/* OMAP-1610 External Trace Interface */
DECL|enumerator|M19_1610_ETM_PSTAT0
id|M19_1610_ETM_PSTAT0
comma
DECL|enumerator|L15_1610_ETM_PSTAT1
id|L15_1610_ETM_PSTAT1
comma
DECL|enumerator|L18_1610_ETM_PSTAT2
id|L18_1610_ETM_PSTAT2
comma
DECL|enumerator|L19_1610_ETM_D0
id|L19_1610_ETM_D0
comma
DECL|enumerator|J19_1610_ETM_D6
id|J19_1610_ETM_D6
comma
DECL|enumerator|J18_1610_ETM_D7
id|J18_1610_ETM_D7
comma
multiline_comment|/* OMAP-1610 GPIO */
DECL|enumerator|P20_1610_GPIO4
id|P20_1610_GPIO4
comma
DECL|enumerator|V9_1610_GPIO7
id|V9_1610_GPIO7
comma
DECL|enumerator|N19_1610_GPIO13
id|N19_1610_GPIO13
comma
DECL|enumerator|P10_1610_GPIO22
id|P10_1610_GPIO22
comma
DECL|enumerator|V5_1610_GPIO24
id|V5_1610_GPIO24
comma
DECL|enumerator|AA20_1610_GPIO_41
id|AA20_1610_GPIO_41
comma
multiline_comment|/* OMAP-1610 uWire */
DECL|enumerator|V19_1610_UWIRE_SCLK
id|V19_1610_UWIRE_SCLK
comma
DECL|enumerator|U18_1610_UWIRE_SDI
id|U18_1610_UWIRE_SDI
comma
DECL|enumerator|W21_1610_UWIRE_SDO
id|W21_1610_UWIRE_SDO
comma
DECL|enumerator|N14_1610_UWIRE_CS0
id|N14_1610_UWIRE_CS0
comma
DECL|enumerator|P15_1610_UWIRE_CS0
id|P15_1610_UWIRE_CS0
comma
DECL|enumerator|N15_1610_UWIRE_CS1
id|N15_1610_UWIRE_CS1
comma
multiline_comment|/* First MMC */
DECL|enumerator|MMC_CMD
id|MMC_CMD
comma
DECL|enumerator|MMC_DAT1
id|MMC_DAT1
comma
DECL|enumerator|MMC_DAT2
id|MMC_DAT2
comma
DECL|enumerator|MMC_DAT0
id|MMC_DAT0
comma
DECL|enumerator|MMC_CLK
id|MMC_CLK
comma
DECL|enumerator|MMC_DAT3
id|MMC_DAT3
comma
multiline_comment|/* OMAP-1610 USB0 alternate pin configuration */
DECL|enumerator|W9_USB0_TXEN
id|W9_USB0_TXEN
comma
DECL|enumerator|AA9_USB0_VP
id|AA9_USB0_VP
comma
DECL|enumerator|Y5_USB0_RCV
id|Y5_USB0_RCV
comma
DECL|enumerator|R9_USB0_VM
id|R9_USB0_VM
comma
DECL|enumerator|V6_USB0_TXD
id|V6_USB0_TXD
comma
DECL|enumerator|W5_USB0_SE0
id|W5_USB0_SE0
comma
DECL|enumerator|V9_USB0_SPEED
id|V9_USB0_SPEED
comma
DECL|enumerator|V9_USB0_SUSP
id|V9_USB0_SUSP
comma
multiline_comment|/* USB2 */
DECL|enumerator|W9_USB2_TXEN
id|W9_USB2_TXEN
comma
DECL|enumerator|AA9_USB2_VP
id|AA9_USB2_VP
comma
DECL|enumerator|Y5_USB2_RCV
id|Y5_USB2_RCV
comma
DECL|enumerator|R9_USB2_VM
id|R9_USB2_VM
comma
DECL|enumerator|V6_USB2_TXD
id|V6_USB2_TXD
comma
DECL|enumerator|W5_USB2_SE0
id|W5_USB2_SE0
comma
multiline_comment|/* UART1 1610 */
DECL|enumerator|R13_1610_UART1_TX
id|R13_1610_UART1_TX
comma
DECL|enumerator|V14_1610_UART1_RX
id|V14_1610_UART1_RX
comma
DECL|enumerator|R14_1610_UART1_CTS
id|R14_1610_UART1_CTS
comma
DECL|enumerator|AA15_1610_UART1_RTS
id|AA15_1610_UART1_RTS
comma
multiline_comment|/* I2C OMAP-1610 */
DECL|enumerator|I2C_SCL
id|I2C_SCL
comma
DECL|enumerator|I2C_SDA
id|I2C_SDA
comma
multiline_comment|/* Keypad */
DECL|enumerator|F18_1610_KBC0
id|F18_1610_KBC0
comma
DECL|enumerator|D20_1610_KBC1
id|D20_1610_KBC1
comma
DECL|enumerator|D19_1610_KBC2
id|D19_1610_KBC2
comma
DECL|enumerator|E18_1610_KBC3
id|E18_1610_KBC3
comma
DECL|enumerator|C21_1610_KBC4
id|C21_1610_KBC4
comma
DECL|enumerator|G18_1610_KBR0
id|G18_1610_KBR0
comma
DECL|enumerator|F19_1610_KBR1
id|F19_1610_KBR1
comma
DECL|enumerator|H14_1610_KBR2
id|H14_1610_KBR2
comma
DECL|enumerator|E20_1610_KBR3
id|E20_1610_KBR3
comma
DECL|enumerator|E19_1610_KBR4
id|E19_1610_KBR4
comma
DECL|enumerator|N19_1610_KBR5
id|N19_1610_KBR5
comma
multiline_comment|/* Power management */
DECL|enumerator|T20_1610_LOW_PWR
id|T20_1610_LOW_PWR
comma
DECL|typedef|reg_cfg_t
)brace
id|reg_cfg_t
suffix:semicolon
macro_line|#if defined(__MUX_C__) &amp;&amp; defined(CONFIG_OMAP_MUX)
multiline_comment|/*&n; * Table of various FUNC_MUX and PULL_DWN combinations for each device.&n; * See also reg_cfg_t above for the lookup table.&n; */
DECL|variable|reg_cfg_table
r_static
id|reg_cfg_set
id|reg_cfg_table
(braket
)braket
op_assign
(brace
multiline_comment|/*&n; *&t; description&t;&t;mux  mode   mux&t; pull pull  pull  pu_pd&t; pu  dbg&n; *&t;&t;&t;&t;reg  offset mode reg  bit   ena&t;  reg&n; */
id|MUX_CFG
c_func
(paren
l_string|&quot;UART1_TX&quot;
comma
l_int|9
comma
l_int|21
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART1_RTS&quot;
comma
l_int|9
comma
l_int|12
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
multiline_comment|/* UART2 (COM_UART_GATING), conflicts with USB2 */
id|MUX_CFG
c_func
(paren
l_string|&quot;UART2_TX&quot;
comma
id|C
comma
l_int|27
comma
l_int|1
comma
l_int|3
comma
l_int|3
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART2_RX&quot;
comma
id|C
comma
l_int|18
comma
l_int|0
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART2_CTS&quot;
comma
id|C
comma
l_int|21
comma
l_int|0
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART2_RTS&quot;
comma
id|C
comma
l_int|24
comma
l_int|1
comma
l_int|3
comma
l_int|2
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
multiline_comment|/* UART3 (GIGA_UART_GATING) */
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_TX&quot;
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|30
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_RX&quot;
comma
l_int|6
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|31
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_CTS&quot;
comma
l_int|5
comma
l_int|12
comma
l_int|2
comma
l_int|0
comma
l_int|24
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_RTS&quot;
comma
l_int|5
comma
l_int|15
comma
l_int|2
comma
l_int|0
comma
l_int|25
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_CLKREQ&quot;
comma
l_int|9
comma
l_int|27
comma
l_int|0
comma
l_int|2
comma
l_int|5
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;UART3_BCLK&quot;
comma
id|A
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|6
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
multiline_comment|/* USB internal master generic */
id|MUX_CFG
c_func
(paren
l_string|&quot;R18_USB_VBUS&quot;
comma
l_int|7
comma
l_int|9
comma
l_int|2
comma
l_int|1
comma
l_int|11
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R18_1510_USB_GPIO0&quot;
comma
l_int|7
comma
l_int|9
comma
l_int|0
comma
l_int|1
comma
l_int|11
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W4_USB_PUEN&quot;
comma
id|D
comma
l_int|3
comma
l_int|0
comma
l_int|3
comma
l_int|5
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W4_USB_CLKO&quot;
comma
id|D
comma
l_int|3
comma
l_int|1
comma
l_int|3
comma
l_int|5
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* USB1 master */
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_SUSP&quot;
comma
l_int|8
comma
l_int|27
comma
l_int|2
comma
l_int|1
comma
l_int|27
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_SE0&quot;
comma
l_int|9
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|28
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_TXEN&quot;
comma
l_int|9
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|29
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_TXD&quot;
comma
l_int|9
comma
l_int|24
comma
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_VP&quot;
comma
id|A
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
l_int|7
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_VM&quot;
comma
id|A
comma
l_int|6
comma
l_int|1
comma
l_int|2
comma
l_int|8
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_RCV&quot;
comma
id|A
comma
l_int|9
comma
l_int|1
comma
l_int|2
comma
l_int|9
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB1_SPEED&quot;
comma
id|A
comma
l_int|12
comma
l_int|2
comma
l_int|2
comma
l_int|10
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* USB2 master */
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_SUSP&quot;
comma
id|B
comma
l_int|3
comma
l_int|1
comma
l_int|2
comma
l_int|17
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_VP&quot;
comma
id|B
comma
l_int|6
comma
l_int|1
comma
l_int|2
comma
l_int|18
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_TXEN&quot;
comma
id|B
comma
l_int|9
comma
l_int|1
comma
l_int|2
comma
l_int|19
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_VM&quot;
comma
id|C
comma
l_int|18
comma
l_int|1
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_RCV&quot;
comma
id|C
comma
l_int|21
comma
l_int|1
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_SE0&quot;
comma
id|C
comma
l_int|24
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;USB2_TXD&quot;
comma
id|C
comma
l_int|27
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* OMAP-1510 GPIO */
id|MUX_CFG
c_func
(paren
l_string|&quot;R18_1510_GPIO0&quot;
comma
l_int|7
comma
l_int|9
comma
l_int|0
comma
l_int|1
comma
l_int|11
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R19_1510_GPIO1&quot;
comma
l_int|7
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|10
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;M14_1510_GPIO2&quot;
comma
l_int|7
comma
l_int|3
comma
l_int|0
comma
l_int|1
comma
l_int|9
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* MPUIO */
id|MUX_CFG
c_func
(paren
l_string|&quot;MPUIO2&quot;
comma
l_int|7
comma
l_int|18
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MPUIO4&quot;
comma
l_int|7
comma
l_int|15
comma
l_int|0
comma
l_int|1
comma
l_int|13
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MPUIO5&quot;
comma
l_int|7
comma
l_int|12
comma
l_int|0
comma
l_int|1
comma
l_int|12
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;T20_1610_MPUIO5&quot;
comma
l_int|7
comma
l_int|12
comma
l_int|0
comma
l_int|1
comma
l_int|12
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W11_1610_MPUIO6&quot;
comma
l_int|10
comma
l_int|15
comma
l_int|2
comma
l_int|3
comma
l_int|8
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V10_1610_MPUIO7&quot;
comma
id|A
comma
l_int|24
comma
l_int|2
comma
l_int|2
comma
l_int|14
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W11_1610_MPUIO9&quot;
comma
l_int|10
comma
l_int|15
comma
l_int|1
comma
l_int|3
comma
l_int|8
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V10_1610_MPUIO10&quot;
comma
id|A
comma
l_int|24
comma
l_int|1
comma
l_int|2
comma
l_int|14
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W10_1610_MPUIO11&quot;
comma
id|A
comma
l_int|18
comma
l_int|2
comma
l_int|2
comma
l_int|11
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;E20_1610_MPUIO13&quot;
comma
l_int|3
comma
l_int|21
comma
l_int|1
comma
l_int|0
comma
l_int|7
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;U20_1610_MPUIO14&quot;
comma
l_int|9
comma
l_int|6
comma
l_int|6
comma
l_int|0
comma
l_int|30
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;E19_1610_MPUIO15&quot;
comma
l_int|3
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* MCBSP2 */
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_CLKR&quot;
comma
id|C
comma
l_int|6
comma
l_int|0
comma
l_int|2
comma
l_int|27
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_CLKX&quot;
comma
id|C
comma
l_int|9
comma
l_int|0
comma
l_int|2
comma
l_int|29
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_DR&quot;
comma
id|C
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|26
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_DX&quot;
comma
id|C
comma
l_int|15
comma
l_int|0
comma
l_int|2
comma
l_int|31
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_FSR&quot;
comma
id|C
comma
l_int|12
comma
l_int|0
comma
l_int|2
comma
l_int|30
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP2_FSX&quot;
comma
id|C
comma
l_int|3
comma
l_int|0
comma
l_int|2
comma
l_int|27
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* MCBSP3 NOTE: Mode must 1 for clock */
id|MUX_CFG
c_func
(paren
l_string|&quot;MCBSP3_CLKX&quot;
comma
l_int|9
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|29
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* Misc ballouts */
id|MUX_CFG
c_func
(paren
l_string|&quot;BALLOUT_V8_ARMIO3&quot;
comma
id|B
comma
l_int|18
comma
l_int|0
comma
l_int|2
comma
l_int|25
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* OMAP-1610 MMC2 */
id|MUX_CFG
c_func
(paren
l_string|&quot;W8_1610_MMC2_DAT0&quot;
comma
id|B
comma
l_int|21
comma
l_int|6
comma
l_int|2
comma
l_int|23
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V8_1610_MMC2_DAT1&quot;
comma
id|B
comma
l_int|27
comma
l_int|6
comma
l_int|2
comma
l_int|25
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W15_1610_MMC2_DAT2&quot;
comma
l_int|9
comma
l_int|12
comma
l_int|6
comma
l_int|2
comma
l_int|5
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R10_1610_MMC2_DAT3&quot;
comma
id|B
comma
l_int|18
comma
l_int|6
comma
l_int|2
comma
l_int|22
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;Y10_1610_MMC2_CLK&quot;
comma
id|B
comma
l_int|3
comma
l_int|6
comma
l_int|2
comma
l_int|17
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;Y8_1610_MMC2_CMD&quot;
comma
id|B
comma
l_int|24
comma
l_int|6
comma
l_int|2
comma
l_int|24
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V9_1610_MMC2_CMDDIR&quot;
comma
id|B
comma
l_int|12
comma
l_int|6
comma
l_int|2
comma
l_int|20
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V5_1610_MMC2_DATDIR0&quot;
comma
id|B
comma
l_int|15
comma
l_int|6
comma
l_int|2
comma
l_int|21
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W19_1610_MMC2_DATDIR1&quot;
comma
l_int|8
comma
l_int|15
comma
l_int|6
comma
l_int|1
comma
l_int|23
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R18_1610_MMC2_CLKIN&quot;
comma
l_int|7
comma
l_int|9
comma
l_int|6
comma
l_int|1
comma
l_int|11
comma
l_int|0
comma
l_int|1
comma
l_int|11
comma
l_int|1
)paren
multiline_comment|/* OMAP-1610 External Trace Interface */
id|MUX_CFG
c_func
(paren
l_string|&quot;M19_1610_ETM_PSTAT0&quot;
comma
l_int|5
comma
l_int|27
comma
l_int|1
comma
l_int|0
comma
l_int|29
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;L15_1610_ETM_PSTAT1&quot;
comma
l_int|5
comma
l_int|24
comma
l_int|1
comma
l_int|0
comma
l_int|28
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;L18_1610_ETM_PSTAT2&quot;
comma
l_int|5
comma
l_int|21
comma
l_int|1
comma
l_int|0
comma
l_int|27
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;L19_1610_ETM_D0&quot;
comma
l_int|5
comma
l_int|18
comma
l_int|1
comma
l_int|0
comma
l_int|26
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;J19_1610_ETM_D6&quot;
comma
l_int|5
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|20
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;J18_1610_ETM_D7&quot;
comma
l_int|5
comma
l_int|27
comma
l_int|1
comma
l_int|0
comma
l_int|19
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* OMAP-1610 GPIO */
id|MUX_CFG
c_func
(paren
l_string|&quot;P20_1610_GPIO4&quot;
comma
l_int|6
comma
l_int|27
comma
l_int|0
comma
l_int|1
comma
l_int|7
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V9_1610_GPIO7&quot;
comma
id|B
comma
l_int|12
comma
l_int|1
comma
l_int|2
comma
l_int|20
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;N19_1610_GPIO13&quot;
comma
l_int|6
comma
l_int|12
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;P10_1610_GPIO22&quot;
comma
id|C
comma
l_int|0
comma
l_int|7
comma
l_int|2
comma
l_int|26
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V5_1610_GPIO24&quot;
comma
id|B
comma
l_int|15
comma
l_int|7
comma
l_int|2
comma
l_int|21
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;AA20_1610_GPIO_41&quot;
comma
l_int|9
comma
l_int|9
comma
l_int|7
comma
l_int|1
comma
l_int|31
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
multiline_comment|/* OMAP-1610 uWire */
id|MUX_CFG
c_func
(paren
l_string|&quot;V19_1610_UWIRE_SCLK&quot;
comma
l_int|8
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|20
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;U18_1610_UWIRE_SDI&quot;
comma
l_int|8
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|18
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W21_1610_UWIRE_SDO&quot;
comma
l_int|8
comma
l_int|3
comma
l_int|0
comma
l_int|1
comma
l_int|19
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;N14_1610_UWIRE_CS0&quot;
comma
l_int|8
comma
l_int|9
comma
l_int|1
comma
l_int|1
comma
l_int|21
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;P15_1610_UWIRE_CS3&quot;
comma
l_int|8
comma
l_int|12
comma
l_int|1
comma
l_int|1
comma
l_int|22
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;N15_1610_UWIRE_CS1&quot;
comma
l_int|7
comma
l_int|18
comma
l_int|2
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
multiline_comment|/* First MMC interface, same on 1510 and 1610 */
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_CMD&quot;
comma
id|A
comma
l_int|27
comma
l_int|0
comma
l_int|2
comma
l_int|15
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_DAT1&quot;
comma
id|A
comma
l_int|24
comma
l_int|0
comma
l_int|2
comma
l_int|14
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_DAT2&quot;
comma
id|A
comma
l_int|18
comma
l_int|0
comma
l_int|2
comma
l_int|12
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_DAT0&quot;
comma
id|B
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|16
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_CLK&quot;
comma
id|A
comma
l_int|21
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;MMC_DAT3&quot;
comma
l_int|10
comma
l_int|15
comma
l_int|0
comma
l_int|3
comma
l_int|8
comma
l_int|1
comma
l_int|3
comma
l_int|1
comma
l_int|1
)paren
multiline_comment|/* OMAP-1610 USB0 alternate configuration */
id|MUX_CFG
c_func
(paren
l_string|&quot;W9_USB0_TXEN&quot;
comma
id|B
comma
l_int|9
comma
l_int|5
comma
l_int|2
comma
l_int|19
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;AA9_USB0_VP&quot;
comma
id|B
comma
l_int|6
comma
l_int|5
comma
l_int|2
comma
l_int|18
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;Y5_USB0_RCV&quot;
comma
id|C
comma
l_int|21
comma
l_int|5
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R9_USB0_VM&quot;
comma
id|C
comma
l_int|18
comma
l_int|5
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V6_USB0_TXD&quot;
comma
id|C
comma
l_int|27
comma
l_int|5
comma
l_int|3
comma
l_int|3
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W5_USB0_SE0&quot;
comma
id|C
comma
l_int|24
comma
l_int|5
comma
l_int|3
comma
l_int|2
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V9_USB0_SPEED&quot;
comma
id|B
comma
l_int|12
comma
l_int|5
comma
l_int|2
comma
l_int|20
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;Y10_USB0_SUSP&quot;
comma
id|B
comma
l_int|3
comma
l_int|5
comma
l_int|2
comma
l_int|17
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* USB2 interface */
id|MUX_CFG
c_func
(paren
l_string|&quot;W9_USB2_TXEN&quot;
comma
id|B
comma
l_int|9
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;AA9_USB2_VP&quot;
comma
id|B
comma
l_int|6
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;Y5_USB2_RCV&quot;
comma
id|C
comma
l_int|21
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R8_USB2_VM&quot;
comma
id|C
comma
l_int|18
comma
l_int|1
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V6_USB2_TXD&quot;
comma
id|C
comma
l_int|27
comma
l_int|2
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;W5_USB2_SE0&quot;
comma
id|C
comma
l_int|24
comma
l_int|2
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* UART1 */
id|MUX_CFG
c_func
(paren
l_string|&quot;R13_1610_UART1_TX&quot;
comma
id|A
comma
l_int|12
comma
l_int|6
comma
l_int|2
comma
l_int|10
comma
l_int|0
comma
l_int|2
comma
l_int|10
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;V14_1610_UART1_RX&quot;
comma
l_int|9
comma
l_int|18
comma
l_int|0
comma
l_int|2
comma
l_int|2
comma
l_int|0
comma
l_int|2
comma
l_int|2
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;R14_1610_UART1_CTS&quot;
comma
l_int|9
comma
l_int|15
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|1
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;AA15_1610_UART1_RTS&quot;
comma
l_int|9
comma
l_int|12
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|1
)paren
multiline_comment|/* I2C interface */
id|MUX_CFG
c_func
(paren
l_string|&quot;I2C_SCL&quot;
comma
l_int|7
comma
l_int|24
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;I2C_SDA&quot;
comma
l_int|7
comma
l_int|27
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
multiline_comment|/* Keypad */
id|MUX_CFG
c_func
(paren
l_string|&quot;F18_1610_KBC0&quot;
comma
l_int|3
comma
l_int|15
comma
l_int|0
comma
l_int|0
comma
l_int|5
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;D20_1610_KBC1&quot;
comma
l_int|3
comma
l_int|12
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;D19_1610_KBC2&quot;
comma
l_int|3
comma
l_int|9
comma
l_int|0
comma
l_int|0
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;E18_1610_KBC3&quot;
comma
l_int|3
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;C21_1610_KBC4&quot;
comma
l_int|3
comma
l_int|3
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;G18_1610_KBR0&quot;
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|10
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;F19_1610_KBR1&quot;
comma
l_int|3
comma
l_int|27
comma
l_int|0
comma
l_int|0
comma
l_int|9
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;H14_1610_KBR2&quot;
comma
l_int|3
comma
l_int|24
comma
l_int|0
comma
l_int|0
comma
l_int|8
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;E20_1610_KBR3&quot;
comma
l_int|3
comma
l_int|21
comma
l_int|0
comma
l_int|0
comma
l_int|7
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;E19_1610_KBR4&quot;
comma
l_int|3
comma
l_int|18
comma
l_int|0
comma
l_int|0
comma
l_int|6
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
id|MUX_CFG
c_func
(paren
l_string|&quot;N19_1610_KBR5&quot;
comma
l_int|6
comma
l_int|12
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
multiline_comment|/* Power management */
id|MUX_CFG
c_func
(paren
l_string|&quot;T20_1610_LOW_PWR&quot;
comma
l_int|7
comma
l_int|12
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|NA
comma
l_int|0
comma
l_int|0
)paren
)brace
suffix:semicolon
macro_line|#endif&t;/* __MUX_C__ */
r_extern
r_int
id|omap_cfg_reg
c_func
(paren
id|reg_cfg_t
id|reg_cfg
)paren
suffix:semicolon
macro_line|#endif
eof
