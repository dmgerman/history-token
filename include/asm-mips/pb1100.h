multiline_comment|/*&n; * Alchemy Semi PB1100 Referrence Board&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; *&n; */
macro_line|#ifndef __ASM_PB1100_H
DECL|macro|__ASM_PB1100_H
mdefine_line|#define __ASM_PB1100_H
DECL|macro|PB1100_IDENT
mdefine_line|#define PB1100_IDENT          0xAE000000
DECL|macro|BOARD_STATUS_REG
mdefine_line|#define BOARD_STATUS_REG      0xAE000004
DECL|macro|PB1100_ROM_SEL
mdefine_line|#define PB1100_ROM_SEL         (1&lt;&lt;15)
DECL|macro|PB1100_ROM_SIZ
mdefine_line|#define PB1100_ROM_SIZ         (1&lt;&lt;14)
DECL|macro|PB1100_SWAP_BOOT
mdefine_line|#define PB1100_SWAP_BOOT       (1&lt;&lt;13)
DECL|macro|PB1100_FLASH_WP
mdefine_line|#define PB1100_FLASH_WP        (1&lt;&lt;12)
DECL|macro|PB1100_ROM_H_STS
mdefine_line|#define PB1100_ROM_H_STS       (1&lt;&lt;11)
DECL|macro|PB1100_ROM_L_STS
mdefine_line|#define PB1100_ROM_L_STS       (1&lt;&lt;10)
DECL|macro|PB1100_FLASH_H_STS
mdefine_line|#define PB1100_FLASH_H_STS      (1&lt;&lt;9)
DECL|macro|PB1100_FLASH_L_STS
mdefine_line|#define PB1100_FLASH_L_STS      (1&lt;&lt;8)
DECL|macro|PB1100_SRAM_SIZ
mdefine_line|#define PB1100_SRAM_SIZ         (1&lt;&lt;7)
DECL|macro|PB1100_TSC_BUSY
mdefine_line|#define PB1100_TSC_BUSY         (1&lt;&lt;6)
DECL|macro|PB1100_PCMCIA_VS_MASK
mdefine_line|#define PB1100_PCMCIA_VS_MASK   (3&lt;&lt;4)
DECL|macro|PB1100_RS232_CD
mdefine_line|#define PB1100_RS232_CD         (1&lt;&lt;3)
DECL|macro|PB1100_RS232_CTS
mdefine_line|#define PB1100_RS232_CTS        (1&lt;&lt;2)
DECL|macro|PB1100_RS232_DSR
mdefine_line|#define PB1100_RS232_DSR        (1&lt;&lt;1)
DECL|macro|PB1100_RS232_RI
mdefine_line|#define PB1100_RS232_RI         (1&lt;&lt;0)
DECL|macro|PB1100_IRDA_RS232
mdefine_line|#define PB1100_IRDA_RS232     0xAE00000C
DECL|macro|PB1100_IRDA_FULL
mdefine_line|#define PB1100_IRDA_FULL       (0&lt;&lt;14) /* full power */
DECL|macro|PB1100_IRDA_SHUTDOWN
mdefine_line|#define PB1100_IRDA_SHUTDOWN   (1&lt;&lt;14)
DECL|macro|PB1100_IRDA_TT
mdefine_line|#define PB1100_IRDA_TT         (2&lt;&lt;14) /* 2/3 power */
DECL|macro|PB1100_IRDA_OT
mdefine_line|#define PB1100_IRDA_OT         (3&lt;&lt;14) /* 1/3 power */
DECL|macro|PB1100_IRDA_FIR
mdefine_line|#define PB1100_IRDA_FIR        (1&lt;&lt;13)
DECL|macro|PCMCIA_BOARD_REG
mdefine_line|#define PCMCIA_BOARD_REG     0xAE000010
DECL|macro|PB1100_SD_WP1_RO
mdefine_line|#define PB1100_SD_WP1_RO       (1&lt;&lt;15) /* read only */
DECL|macro|PB1100_SD_WP0_RO
mdefine_line|#define PB1100_SD_WP0_RO       (1&lt;&lt;14) /* read only */
DECL|macro|PB1100_SD_PWR1
mdefine_line|#define PB1100_SD_PWR1         (1&lt;&lt;11) /* applies power to SD1 */
DECL|macro|PB1100_SD_PWR0
mdefine_line|#define PB1100_SD_PWR0         (1&lt;&lt;10) /* applies power to SD0 */
DECL|macro|PB1100_SEL_SD_CONN1
mdefine_line|#define PB1100_SEL_SD_CONN1     (1&lt;&lt;9)
DECL|macro|PB1100_SEL_SD_CONN0
mdefine_line|#define PB1100_SEL_SD_CONN0     (1&lt;&lt;8)
DECL|macro|PC_DEASSERT_RST
mdefine_line|#define PC_DEASSERT_RST         (1&lt;&lt;7)
DECL|macro|PC_DRV_EN
mdefine_line|#define PC_DRV_EN               (1&lt;&lt;4)
DECL|macro|PB1100_G_CONTROL
mdefine_line|#define PB1100_G_CONTROL      0xAE000014 /* graphics control */
DECL|macro|PB1100_RST_VDDI
mdefine_line|#define PB1100_RST_VDDI       0xAE00001C
DECL|macro|PB1100_SOFT_RESET
mdefine_line|#define PB1100_SOFT_RESET      (1&lt;&lt;15) /* clear to reset the board */
DECL|macro|PB1100_VDDI_MASK
mdefine_line|#define PB1100_VDDI_MASK        (0x1F)
DECL|macro|PB1100_LEDS
mdefine_line|#define PB1100_LEDS           0xAE000018
multiline_comment|/* 11:8 is 4 discreet LEDs. Clearing a bit illuminates the LED.&n; * 7:0 is the LED Display&squot;s decimal points.&n; */
DECL|macro|PB1100_HEX_LED
mdefine_line|#define PB1100_HEX_LED        0xAE000018
multiline_comment|/* PCMCIA PB1100 specific defines */
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 0
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
multiline_comment|/* VPP/VCC */
DECL|macro|SET_VCC_VPP
mdefine_line|#define SET_VCC_VPP(VCC, VPP) (((VCC)&lt;&lt;2) | ((VPP)&lt;&lt;0))
macro_line|#endif /* __ASM_PB1100_H */
eof
