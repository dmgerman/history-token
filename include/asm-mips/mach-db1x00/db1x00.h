multiline_comment|/*&n; * AMD Alchemy DB1x00 Reference Boards&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; * Copyright (C) 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * &n; */
macro_line|#ifndef __ASM_DB1X00_H
DECL|macro|__ASM_DB1X00_H
mdefine_line|#define __ASM_DB1X00_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MIPS_DB1550
DECL|macro|BCSR_KSEG1_ADDR
mdefine_line|#define BCSR_KSEG1_ADDR 0xAF000000
DECL|macro|NAND_PHYS_ADDR
mdefine_line|#define NAND_PHYS_ADDR  0x20000000
macro_line|#else
DECL|macro|BCSR_KSEG1_ADDR
mdefine_line|#define BCSR_KSEG1_ADDR 0xAE000000
macro_line|#endif
multiline_comment|/*&n; * Overlay data structure of the Db1x00 board registers.&n; * Registers located at physical 0E0000xx, KSEG1 0xAE0000xx&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|whoami
multiline_comment|/*00*/
r_int
r_int
id|whoami
suffix:semicolon
DECL|member|reserved0
r_int
r_int
id|reserved0
suffix:semicolon
DECL|member|status
multiline_comment|/*04*/
r_int
r_int
id|status
suffix:semicolon
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:semicolon
DECL|member|switches
multiline_comment|/*08*/
r_int
r_int
id|switches
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
DECL|member|resets
multiline_comment|/*0C*/
r_int
r_int
id|resets
suffix:semicolon
DECL|member|reserved3
r_int
r_int
id|reserved3
suffix:semicolon
DECL|member|pcmcia
multiline_comment|/*10*/
r_int
r_int
id|pcmcia
suffix:semicolon
DECL|member|reserved4
r_int
r_int
id|reserved4
suffix:semicolon
DECL|member|specific
multiline_comment|/*14*/
r_int
r_int
id|specific
suffix:semicolon
DECL|member|reserved5
r_int
r_int
id|reserved5
suffix:semicolon
DECL|member|leds
multiline_comment|/*18*/
r_int
r_int
id|leds
suffix:semicolon
DECL|member|reserved6
r_int
r_int
id|reserved6
suffix:semicolon
DECL|member|swreset
multiline_comment|/*1C*/
r_int
r_int
id|swreset
suffix:semicolon
DECL|member|reserved7
r_int
r_int
id|reserved7
suffix:semicolon
DECL|typedef|BCSR
)brace
id|BCSR
suffix:semicolon
multiline_comment|/*&n; * Register/mask bit definitions for the BCSRs&n; */
DECL|macro|BCSR_WHOAMI_DCID
mdefine_line|#define BCSR_WHOAMI_DCID&t;&t;0x000F
DECL|macro|BCSR_WHOAMI_CPLD
mdefine_line|#define BCSR_WHOAMI_CPLD&t;&t;0x00F0
DECL|macro|BCSR_WHOAMI_BOARD
mdefine_line|#define BCSR_WHOAMI_BOARD&t;&t;0x0F00
DECL|macro|BCSR_STATUS_PC0VS
mdefine_line|#define BCSR_STATUS_PC0VS&t;&t;0x0003
DECL|macro|BCSR_STATUS_PC1VS
mdefine_line|#define BCSR_STATUS_PC1VS&t;&t;0x000C
DECL|macro|BCSR_STATUS_PC0FI
mdefine_line|#define BCSR_STATUS_PC0FI&t;&t;0x0010
DECL|macro|BCSR_STATUS_PC1FI
mdefine_line|#define BCSR_STATUS_PC1FI&t;&t;0x0020
DECL|macro|BCSR_STATUS_FLASHBUSY
mdefine_line|#define BCSR_STATUS_FLASHBUSY&t;&t;0x0100
DECL|macro|BCSR_STATUS_ROMBUSY
mdefine_line|#define BCSR_STATUS_ROMBUSY&t;&t;0x0400
DECL|macro|BCSR_STATUS_SWAPBOOT
mdefine_line|#define BCSR_STATUS_SWAPBOOT&t;&t;0x2000
DECL|macro|BCSR_STATUS_FLASHDEN
mdefine_line|#define BCSR_STATUS_FLASHDEN&t;&t;0xC000
DECL|macro|BCSR_SWITCHES_DIP
mdefine_line|#define BCSR_SWITCHES_DIP&t;&t;0x00FF
DECL|macro|BCSR_SWITCHES_DIP_1
mdefine_line|#define BCSR_SWITCHES_DIP_1&t;&t;0x0080
DECL|macro|BCSR_SWITCHES_DIP_2
mdefine_line|#define BCSR_SWITCHES_DIP_2&t;&t;0x0040
DECL|macro|BCSR_SWITCHES_DIP_3
mdefine_line|#define BCSR_SWITCHES_DIP_3&t;&t;0x0020
DECL|macro|BCSR_SWITCHES_DIP_4
mdefine_line|#define BCSR_SWITCHES_DIP_4&t;&t;0x0010
DECL|macro|BCSR_SWITCHES_DIP_5
mdefine_line|#define BCSR_SWITCHES_DIP_5&t;&t;0x0008
DECL|macro|BCSR_SWITCHES_DIP_6
mdefine_line|#define BCSR_SWITCHES_DIP_6&t;&t;0x0004
DECL|macro|BCSR_SWITCHES_DIP_7
mdefine_line|#define BCSR_SWITCHES_DIP_7&t;&t;0x0002
DECL|macro|BCSR_SWITCHES_DIP_8
mdefine_line|#define BCSR_SWITCHES_DIP_8&t;&t;0x0001
DECL|macro|BCSR_SWITCHES_ROTARY
mdefine_line|#define BCSR_SWITCHES_ROTARY&t;&t;0x0F00
DECL|macro|BCSR_RESETS_PHY0
mdefine_line|#define BCSR_RESETS_PHY0&t;&t;0x0001
DECL|macro|BCSR_RESETS_PHY1
mdefine_line|#define BCSR_RESETS_PHY1&t;&t;0x0002
DECL|macro|BCSR_RESETS_DC
mdefine_line|#define BCSR_RESETS_DC&t;&t;&t;0x0004
DECL|macro|BCSR_RESETS_FIR_SEL
mdefine_line|#define BCSR_RESETS_FIR_SEL&t;&t;0x2000
DECL|macro|BCSR_RESETS_IRDA_MODE_MASK
mdefine_line|#define BCSR_RESETS_IRDA_MODE_MASK&t;0xC000
DECL|macro|BCSR_RESETS_IRDA_MODE_FULL
mdefine_line|#define BCSR_RESETS_IRDA_MODE_FULL&t;0x0000
DECL|macro|BCSR_RESETS_IRDA_MODE_OFF
mdefine_line|#define BCSR_RESETS_IRDA_MODE_OFF&t;0x4000
DECL|macro|BCSR_RESETS_IRDA_MODE_2_3
mdefine_line|#define BCSR_RESETS_IRDA_MODE_2_3&t;0x8000
DECL|macro|BCSR_RESETS_IRDA_MODE_1_3
mdefine_line|#define BCSR_RESETS_IRDA_MODE_1_3&t;0xC000
DECL|macro|BCSR_PCMCIA_PC0VPP
mdefine_line|#define BCSR_PCMCIA_PC0VPP&t;&t;0x0003
DECL|macro|BCSR_PCMCIA_PC0VCC
mdefine_line|#define BCSR_PCMCIA_PC0VCC&t;&t;0x000C
DECL|macro|BCSR_PCMCIA_PC0DRVEN
mdefine_line|#define BCSR_PCMCIA_PC0DRVEN&t;&t;0x0010
DECL|macro|BCSR_PCMCIA_PC0RST
mdefine_line|#define BCSR_PCMCIA_PC0RST&t;&t;0x0080
DECL|macro|BCSR_PCMCIA_PC1VPP
mdefine_line|#define BCSR_PCMCIA_PC1VPP&t;&t;0x0300
DECL|macro|BCSR_PCMCIA_PC1VCC
mdefine_line|#define BCSR_PCMCIA_PC1VCC&t;&t;0x0C00
DECL|macro|BCSR_PCMCIA_PC1DRVEN
mdefine_line|#define BCSR_PCMCIA_PC1DRVEN&t;&t;0x1000
DECL|macro|BCSR_PCMCIA_PC1RST
mdefine_line|#define BCSR_PCMCIA_PC1RST&t;&t;0x8000
DECL|macro|BCSR_BOARD_PCIM66EN
mdefine_line|#define BCSR_BOARD_PCIM66EN&t;&t;0x0001
DECL|macro|BCSR_BOARD_SD0_PWR
mdefine_line|#define BCSR_BOARD_SD0_PWR&t;&t;0x0040
DECL|macro|BCSR_BOARD_SD1_PWR
mdefine_line|#define BCSR_BOARD_SD1_PWR&t;&t;0x0080
DECL|macro|BCSR_BOARD_PCIM33
mdefine_line|#define BCSR_BOARD_PCIM33&t;&t;0x0100
DECL|macro|BCSR_BOARD_GPIO200RST
mdefine_line|#define BCSR_BOARD_GPIO200RST&t;&t;0x0400
DECL|macro|BCSR_BOARD_PCICFG
mdefine_line|#define BCSR_BOARD_PCICFG&t;&t;0x1000
DECL|macro|BCSR_BOARD_SD0_WP
mdefine_line|#define BCSR_BOARD_SD0_WP&t;&t;0x4000
DECL|macro|BCSR_BOARD_SD1_WP
mdefine_line|#define BCSR_BOARD_SD1_WP&t;&t;0x8000
DECL|macro|BCSR_LEDS_DECIMALS
mdefine_line|#define BCSR_LEDS_DECIMALS&t;&t;0x0003
DECL|macro|BCSR_LEDS_LED0
mdefine_line|#define BCSR_LEDS_LED0&t;&t;&t;0x0100
DECL|macro|BCSR_LEDS_LED1
mdefine_line|#define BCSR_LEDS_LED1&t;&t;&t;0x0200
DECL|macro|BCSR_LEDS_LED2
mdefine_line|#define BCSR_LEDS_LED2&t;&t;&t;0x0400
DECL|macro|BCSR_LEDS_LED3
mdefine_line|#define BCSR_LEDS_LED3&t;&t;&t;0x0800
DECL|macro|BCSR_SWRESET_RESET
mdefine_line|#define BCSR_SWRESET_RESET&t;&t;0x0080
multiline_comment|/* PCMCIA Db1x00 specific defines */
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 1
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
multiline_comment|/* VPP/VCC */
DECL|macro|SET_VCC_VPP
mdefine_line|#define SET_VCC_VPP(VCC, VPP, SLOT)&bslash;&n;&t;((((VCC)&lt;&lt;2) | ((VPP)&lt;&lt;0)) &lt;&lt; ((SLOT)*8))
multiline_comment|/* SD controller macros */
multiline_comment|/*&n; * Detect card.&n; */
DECL|macro|mmc_card_inserted
mdefine_line|#define mmc_card_inserted(_n_, _res_) &bslash;&n;&t;do { &bslash;&n;&t;&t;BCSR * const bcsr = (BCSR *)0xAE000000; &bslash;&n;&t;&t;unsigned long mmc_wp, board_specific; &bslash;&n;&t;&t;if ((_n_)) { &bslash;&n;&t;&t;&t;mmc_wp = BCSR_BOARD_SD1_WP; &bslash;&n;&t;&t;} else { &bslash;&n;&t;&t;&t;mmc_wp = BCSR_BOARD_SD0_WP; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;board_specific = au_readl((unsigned long)(&amp;bcsr-&gt;specific)); &bslash;&n;&t;&t;if (!(board_specific &amp; mmc_wp)) {/* low means card present */ &bslash;&n;&t;&t;&t;*(int *)(_res_) = 1; &bslash;&n;&t;&t;} else { &bslash;&n;&t;&t;&t;*(int *)(_res_) = 0; &bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Apply power to card slot(s).&n; */
DECL|macro|mmc_power_on
mdefine_line|#define mmc_power_on(_n_) &bslash;&n;&t;do { &bslash;&n;&t;&t;BCSR * const bcsr = (BCSR *)0xAE000000; &bslash;&n;&t;&t;unsigned long mmc_pwr, mmc_wp, board_specific; &bslash;&n;&t;&t;if ((_n_)) { &bslash;&n;&t;&t;&t;mmc_pwr = BCSR_BOARD_SD1_PWR; &bslash;&n;&t;&t;&t;mmc_wp = BCSR_BOARD_SD1_WP; &bslash;&n;&t;&t;} else { &bslash;&n;&t;&t;&t;mmc_pwr = BCSR_BOARD_SD0_PWR; &bslash;&n;&t;&t;&t;mmc_wp = BCSR_BOARD_SD0_WP; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;board_specific = au_readl((unsigned long)(&amp;bcsr-&gt;specific)); &bslash;&n;&t;&t;if (!(board_specific &amp; mmc_wp)) {/* low means card present */ &bslash;&n;&t;&t;&t;board_specific |= mmc_pwr; &bslash;&n;&t;&t;&t;au_writel(board_specific, (int)(&amp;bcsr-&gt;specific)); &bslash;&n;&t;&t;&t;au_sync(); &bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
multiline_comment|/* NAND defines */
multiline_comment|/* Timing values as described in databook, * ns value stripped of&n; * lower 2 bits.&n; * These defines are here rather than an SOC1550 generic file because&n; * the parts chosen on another board may be different and may require&n; * different timings.&n; */
DECL|macro|NAND_T_H
mdefine_line|#define NAND_T_H&t;&t;&t;(18 &gt;&gt; 2)
DECL|macro|NAND_T_PUL
mdefine_line|#define NAND_T_PUL&t;&t;&t;(30 &gt;&gt; 2)
DECL|macro|NAND_T_SU
mdefine_line|#define NAND_T_SU&t;&t;&t;(30 &gt;&gt; 2)
DECL|macro|NAND_T_WH
mdefine_line|#define NAND_T_WH&t;&t;&t;(30 &gt;&gt; 2)
multiline_comment|/* Bitfield shift amounts */
DECL|macro|NAND_T_H_SHIFT
mdefine_line|#define NAND_T_H_SHIFT&t;&t;0
DECL|macro|NAND_T_PUL_SHIFT
mdefine_line|#define NAND_T_PUL_SHIFT&t;4
DECL|macro|NAND_T_SU_SHIFT
mdefine_line|#define NAND_T_SU_SHIFT&t;&t;8
DECL|macro|NAND_T_WH_SHIFT
mdefine_line|#define NAND_T_WH_SHIFT&t;&t;12
DECL|macro|NAND_TIMING
mdefine_line|#define NAND_TIMING&t;((NAND_T_H   &amp; 0xF)&t;&lt;&lt; NAND_T_H_SHIFT)   | &bslash;&n;&t;&t;&t;((NAND_T_PUL &amp; 0xF)&t;&lt;&lt; NAND_T_PUL_SHIFT) | &bslash;&n;&t;&t;&t;((NAND_T_SU  &amp; 0xF)&t;&lt;&lt; NAND_T_SU_SHIFT)  | &bslash;&n;&t;&t;&t;((NAND_T_WH  &amp; 0xF)&t;&lt;&lt; NAND_T_WH_SHIFT)
macro_line|#endif /* __ASM_DB1X00_H */
eof
