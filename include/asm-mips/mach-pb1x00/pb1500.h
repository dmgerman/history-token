multiline_comment|/*&n; * Alchemy Semi PB1500 Referrence Board&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; *&n; */
macro_line|#ifndef __ASM_PB1500_H
DECL|macro|__ASM_PB1500_H
mdefine_line|#define __ASM_PB1500_H
DECL|macro|IDENT_BOARD_REG
mdefine_line|#define IDENT_BOARD_REG           0xAE000000
DECL|macro|BOARD_STATUS_REG
mdefine_line|#define BOARD_STATUS_REG          0xAE000004
DECL|macro|PCI_BOARD_REG
mdefine_line|#define PCI_BOARD_REG             0xAE000010
DECL|macro|PCMCIA_BOARD_REG
mdefine_line|#define PCMCIA_BOARD_REG          0xAE000010
DECL|macro|PC_DEASSERT_RST
mdefine_line|#define PC_DEASSERT_RST               0x80
DECL|macro|PC_DRV_EN
mdefine_line|#define PC_DRV_EN                     0x10 
DECL|macro|PB1500_G_CONTROL
mdefine_line|#define PB1500_G_CONTROL          0xAE000014
DECL|macro|PB1500_RST_VDDI
mdefine_line|#define PB1500_RST_VDDI           0xAE00001C
DECL|macro|PB1500_LEDS
mdefine_line|#define PB1500_LEDS               0xAE000018
DECL|macro|PB1500_HEX_LED
mdefine_line|#define PB1500_HEX_LED            0xAF000004
DECL|macro|PB1500_HEX_LED_BLANK
mdefine_line|#define PB1500_HEX_LED_BLANK      0xAF000008
multiline_comment|/* PCMCIA PB1500 specific defines */
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 0
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
multiline_comment|/* VPP/VCC */
DECL|macro|SET_VCC_VPP
mdefine_line|#define SET_VCC_VPP(VCC, VPP) (((VCC)&lt;&lt;2) | ((VPP)&lt;&lt;0))
macro_line|#endif /* __ASM_PB1500_H */
eof
