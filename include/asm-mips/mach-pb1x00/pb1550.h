multiline_comment|/*&n; * AMD Alchemy Semi PB1550 Referrence Board&n; * Board Registers defines.&n; *&n; * Copyright 2004 Embedded Edge LLC.&n; * Copyright 2005 Ralf Baechle (ralf@linux-mips.org)&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; *&n; */
macro_line|#ifndef __ASM_PB1550_H
DECL|macro|__ASM_PB1550_H
mdefine_line|#define __ASM_PB1550_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|DBDMA_AC97_TX_CHAN
mdefine_line|#define DBDMA_AC97_TX_CHAN DSCR_CMD0_PSC1_TX
DECL|macro|DBDMA_AC97_RX_CHAN
mdefine_line|#define DBDMA_AC97_RX_CHAN DSCR_CMD0_PSC1_RX
DECL|macro|DBDMA_I2S_TX_CHAN
mdefine_line|#define DBDMA_I2S_TX_CHAN DSCR_CMD0_PSC3_TX
DECL|macro|DBDMA_I2S_RX_CHAN
mdefine_line|#define DBDMA_I2S_RX_CHAN DSCR_CMD0_PSC3_RX
DECL|macro|SPI_PSC_BASE
mdefine_line|#define SPI_PSC_BASE        PSC0_BASE_ADDR
DECL|macro|AC97_PSC_BASE
mdefine_line|#define AC97_PSC_BASE       PSC1_BASE_ADDR
DECL|macro|SMBUS_PSC_BASE
mdefine_line|#define SMBUS_PSC_BASE      PSC2_BASE_ADDR
DECL|macro|I2S_PSC_BASE
mdefine_line|#define I2S_PSC_BASE        PSC3_BASE_ADDR
DECL|macro|BCSR_PHYS_ADDR
mdefine_line|#define BCSR_PHYS_ADDR 0xAF000000
r_typedef
r_volatile
r_struct
(brace
DECL|member|whoami
multiline_comment|/*00*/
id|u16
id|whoami
suffix:semicolon
DECL|member|reserved0
id|u16
id|reserved0
suffix:semicolon
DECL|member|status
multiline_comment|/*04*/
id|u16
id|status
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|switches
multiline_comment|/*08*/
id|u16
id|switches
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|resets
multiline_comment|/*0C*/
id|u16
id|resets
suffix:semicolon
DECL|member|reserved3
id|u16
id|reserved3
suffix:semicolon
DECL|member|pcmcia
multiline_comment|/*10*/
id|u16
id|pcmcia
suffix:semicolon
DECL|member|reserved4
id|u16
id|reserved4
suffix:semicolon
DECL|member|pci
multiline_comment|/*14*/
id|u16
id|pci
suffix:semicolon
DECL|member|reserved5
id|u16
id|reserved5
suffix:semicolon
DECL|member|leds
multiline_comment|/*18*/
id|u16
id|leds
suffix:semicolon
DECL|member|reserved6
id|u16
id|reserved6
suffix:semicolon
DECL|member|system
multiline_comment|/*1C*/
id|u16
id|system
suffix:semicolon
DECL|member|reserved7
id|u16
id|reserved7
suffix:semicolon
DECL|typedef|BCSR
)brace
id|BCSR
suffix:semicolon
DECL|variable|bcsr
r_static
id|BCSR
op_star
r_const
id|bcsr
op_assign
(paren
id|BCSR
op_star
)paren
id|BCSR_PHYS_ADDR
suffix:semicolon
multiline_comment|/*&n; * Register bit definitions for the BCSRs&n; */
DECL|macro|BCSR_WHOAMI_DCID
mdefine_line|#define BCSR_WHOAMI_DCID&t;0x000F
DECL|macro|BCSR_WHOAMI_CPLD
mdefine_line|#define BCSR_WHOAMI_CPLD&t;0x00F0
DECL|macro|BCSR_WHOAMI_BOARD
mdefine_line|#define BCSR_WHOAMI_BOARD&t;0x0F00
DECL|macro|BCSR_STATUS_PCMCIA0VS
mdefine_line|#define BCSR_STATUS_PCMCIA0VS&t;0x0003
DECL|macro|BCSR_STATUS_PCMCIA1VS
mdefine_line|#define BCSR_STATUS_PCMCIA1VS&t;0x000C
DECL|macro|BCSR_STATUS_PCMCIA0FI
mdefine_line|#define BCSR_STATUS_PCMCIA0FI&t;0x0010
DECL|macro|BCSR_STATUS_PCMCIA1FI
mdefine_line|#define BCSR_STATUS_PCMCIA1FI&t;0x0020
DECL|macro|BCSR_STATUS_SWAPBOOT
mdefine_line|#define BCSR_STATUS_SWAPBOOT&t;0x0040
DECL|macro|BCSR_STATUS_SRAMWIDTH
mdefine_line|#define BCSR_STATUS_SRAMWIDTH&t;0x0080
DECL|macro|BCSR_STATUS_FLASHBUSY
mdefine_line|#define BCSR_STATUS_FLASHBUSY&t;0x0100
DECL|macro|BCSR_STATUS_ROMBUSY
mdefine_line|#define BCSR_STATUS_ROMBUSY&t;0x0200
DECL|macro|BCSR_STATUS_USBOTGID
mdefine_line|#define BCSR_STATUS_USBOTGID&t;0x0800
DECL|macro|BCSR_STATUS_U0RXD
mdefine_line|#define BCSR_STATUS_U0RXD&t;0x1000
DECL|macro|BCSR_STATUS_U1RXD
mdefine_line|#define BCSR_STATUS_U1RXD&t;0x2000
DECL|macro|BCSR_STATUS_U3RXD
mdefine_line|#define BCSR_STATUS_U3RXD&t;0x8000
DECL|macro|BCSR_SWITCHES_OCTAL
mdefine_line|#define BCSR_SWITCHES_OCTAL&t;0x00FF
DECL|macro|BCSR_SWITCHES_DIP_1
mdefine_line|#define BCSR_SWITCHES_DIP_1&t;0x0080
DECL|macro|BCSR_SWITCHES_DIP_2
mdefine_line|#define BCSR_SWITCHES_DIP_2&t;0x0040
DECL|macro|BCSR_SWITCHES_DIP_3
mdefine_line|#define BCSR_SWITCHES_DIP_3&t;0x0020
DECL|macro|BCSR_SWITCHES_DIP_4
mdefine_line|#define BCSR_SWITCHES_DIP_4&t;0x0010
DECL|macro|BCSR_SWITCHES_DIP_5
mdefine_line|#define BCSR_SWITCHES_DIP_5&t;0x0008
DECL|macro|BCSR_SWITCHES_DIP_6
mdefine_line|#define BCSR_SWITCHES_DIP_6&t;0x0004
DECL|macro|BCSR_SWITCHES_DIP_7
mdefine_line|#define BCSR_SWITCHES_DIP_7&t;0x0002
DECL|macro|BCSR_SWITCHES_DIP_8
mdefine_line|#define BCSR_SWITCHES_DIP_8&t;0x0001
DECL|macro|BCSR_SWITCHES_ROTARY
mdefine_line|#define BCSR_SWITCHES_ROTARY&t;0x0F00
DECL|macro|BCSR_RESETS_PHY0
mdefine_line|#define BCSR_RESETS_PHY0&t;0x0001
DECL|macro|BCSR_RESETS_PHY1
mdefine_line|#define BCSR_RESETS_PHY1&t;0x0002
DECL|macro|BCSR_RESETS_DC
mdefine_line|#define BCSR_RESETS_DC&t;&t;0x0004
DECL|macro|BCSR_RESETS_WSC
mdefine_line|#define BCSR_RESETS_WSC&t;&t;0x2000
DECL|macro|BCSR_RESETS_SPISEL
mdefine_line|#define BCSR_RESETS_SPISEL&t;0x4000
DECL|macro|BCSR_RESETS_DMAREQ
mdefine_line|#define BCSR_RESETS_DMAREQ&t;0x8000
DECL|macro|BCSR_PCMCIA_PC0VPP
mdefine_line|#define BCSR_PCMCIA_PC0VPP&t;0x0003
DECL|macro|BCSR_PCMCIA_PC0VCC
mdefine_line|#define BCSR_PCMCIA_PC0VCC&t;0x000C
DECL|macro|BCSR_PCMCIA_PC0DRVEN
mdefine_line|#define BCSR_PCMCIA_PC0DRVEN&t;0x0010
DECL|macro|BCSR_PCMCIA_PC0RST
mdefine_line|#define BCSR_PCMCIA_PC0RST&t;0x0080
DECL|macro|BCSR_PCMCIA_PC1VPP
mdefine_line|#define BCSR_PCMCIA_PC1VPP&t;0x0300
DECL|macro|BCSR_PCMCIA_PC1VCC
mdefine_line|#define BCSR_PCMCIA_PC1VCC&t;0x0C00
DECL|macro|BCSR_PCMCIA_PC1DRVEN
mdefine_line|#define BCSR_PCMCIA_PC1DRVEN&t;0x1000
DECL|macro|BCSR_PCMCIA_PC1RST
mdefine_line|#define BCSR_PCMCIA_PC1RST&t;0x8000
DECL|macro|BCSR_PCI_M66EN
mdefine_line|#define BCSR_PCI_M66EN&t;&t;0x0001
DECL|macro|BCSR_PCI_M33
mdefine_line|#define BCSR_PCI_M33&t;&t;0x0100
DECL|macro|BCSR_PCI_EXTERNARB
mdefine_line|#define BCSR_PCI_EXTERNARB&t;0x0200
DECL|macro|BCSR_PCI_GPIO200RST
mdefine_line|#define BCSR_PCI_GPIO200RST&t;0x0400
DECL|macro|BCSR_PCI_CLKOUT
mdefine_line|#define BCSR_PCI_CLKOUT&t;&t;0x0800
DECL|macro|BCSR_PCI_CFGHOST
mdefine_line|#define BCSR_PCI_CFGHOST&t;0x1000
DECL|macro|BCSR_LEDS_DECIMALS
mdefine_line|#define BCSR_LEDS_DECIMALS&t;0x00FF
DECL|macro|BCSR_LEDS_LED0
mdefine_line|#define BCSR_LEDS_LED0&t;&t;0x0100
DECL|macro|BCSR_LEDS_LED1
mdefine_line|#define BCSR_LEDS_LED1&t;&t;0x0200
DECL|macro|BCSR_LEDS_LED2
mdefine_line|#define BCSR_LEDS_LED2&t;&t;0x0400
DECL|macro|BCSR_LEDS_LED3
mdefine_line|#define BCSR_LEDS_LED3&t;&t;0x0800
DECL|macro|BCSR_SYSTEM_VDDI
mdefine_line|#define BCSR_SYSTEM_VDDI&t;0x001F
DECL|macro|BCSR_SYSTEM_POWEROFF
mdefine_line|#define BCSR_SYSTEM_POWEROFF&t;0x4000
DECL|macro|BCSR_SYSTEM_RESET
mdefine_line|#define BCSR_SYSTEM_RESET&t;0x8000
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 1
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
multiline_comment|/* VPP/VCC */
DECL|macro|SET_VCC_VPP
mdefine_line|#define SET_VCC_VPP(VCC, VPP, SLOT)&bslash;&n;&t;((((VCC)&lt;&lt;2) | ((VPP)&lt;&lt;0)) &lt;&lt; ((SLOT)*8))
macro_line|#if defined(CONFIG_MTD_PB1550_BOOT) &amp;&amp; defined(CONFIG_MTD_PB1550_USER)
DECL|macro|PB1550_BOTH_BANKS
mdefine_line|#define PB1550_BOTH_BANKS
macro_line|#elif defined(CONFIG_MTD_PB1550_BOOT) &amp;&amp; !defined(CONFIG_MTD_PB1550_USER)
DECL|macro|PB1550_BOOT_ONLY
mdefine_line|#define PB1550_BOOT_ONLY
macro_line|#elif !defined(CONFIG_MTD_PB1550_BOOT) &amp;&amp; defined(CONFIG_MTD_PB1550_USER)
DECL|macro|PB1550_USER_ONLY
mdefine_line|#define PB1550_USER_ONLY
macro_line|#endif
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
macro_line|#endif /* __ASM_PB1550_H */
eof
