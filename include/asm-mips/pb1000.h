multiline_comment|/*&n; * Alchemy Semi PB1000 Referrence Board&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; *&n; */
macro_line|#ifndef __ASM_PB1000_H
DECL|macro|__ASM_PB1000_H
mdefine_line|#define __ASM_PB1000_H
multiline_comment|/* PCMCIA PB1000 specific defines */
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 1
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
DECL|macro|PB1000_PCR
mdefine_line|#define PB1000_PCR     0xBE000000
DECL|macro|PCR_SLOT_0_VPP0
mdefine_line|#define PCR_SLOT_0_VPP0  (1&lt;&lt;0)
DECL|macro|PCR_SLOT_0_VPP1
mdefine_line|#define PCR_SLOT_0_VPP1  (1&lt;&lt;1)
DECL|macro|PCR_SLOT_0_VCC0
mdefine_line|#define PCR_SLOT_0_VCC0  (1&lt;&lt;2)
DECL|macro|PCR_SLOT_0_VCC1
mdefine_line|#define PCR_SLOT_0_VCC1  (1&lt;&lt;3)
DECL|macro|PCR_SLOT_0_RST
mdefine_line|#define PCR_SLOT_0_RST   (1&lt;&lt;4)
DECL|macro|PCR_SLOT_1_VPP0
mdefine_line|#define PCR_SLOT_1_VPP0  (1&lt;&lt;8)
DECL|macro|PCR_SLOT_1_VPP1
mdefine_line|#define PCR_SLOT_1_VPP1  (1&lt;&lt;9)
DECL|macro|PCR_SLOT_1_VCC0
mdefine_line|#define PCR_SLOT_1_VCC0  (1&lt;&lt;10)
DECL|macro|PCR_SLOT_1_VCC1
mdefine_line|#define PCR_SLOT_1_VCC1  (1&lt;&lt;11)
DECL|macro|PCR_SLOT_1_RST
mdefine_line|#define PCR_SLOT_1_RST   (1&lt;&lt;12)
DECL|macro|PB1000_MDR
mdefine_line|#define PB1000_MDR     0xBE000004
DECL|macro|MDR_PI
mdefine_line|#define MDR_PI        (1&lt;&lt;5)  /* pcmcia int latch  */
DECL|macro|MDR_EPI
mdefine_line|#define MDR_EPI      (1&lt;&lt;14)  /* enable pcmcia int */
DECL|macro|MDR_CPI
mdefine_line|#define MDR_CPI      (1&lt;&lt;15)  /* clear pcmcia int  */
DECL|macro|PB1000_ACR1
mdefine_line|#define PB1000_ACR1    0xBE000008
DECL|macro|ACR1_SLOT_0_CD1
mdefine_line|#define ACR1_SLOT_0_CD1    (1&lt;&lt;0)  /* card detect 1     */
DECL|macro|ACR1_SLOT_0_CD2
mdefine_line|#define ACR1_SLOT_0_CD2    (1&lt;&lt;1)  /* card detect 2     */
DECL|macro|ACR1_SLOT_0_READY
mdefine_line|#define ACR1_SLOT_0_READY  (1&lt;&lt;2)  /* ready             */
DECL|macro|ACR1_SLOT_0_STATUS
mdefine_line|#define ACR1_SLOT_0_STATUS (1&lt;&lt;3)  /* status change     */
DECL|macro|ACR1_SLOT_0_VS1
mdefine_line|#define ACR1_SLOT_0_VS1    (1&lt;&lt;4)  /* voltage sense 1   */
DECL|macro|ACR1_SLOT_0_VS2
mdefine_line|#define ACR1_SLOT_0_VS2    (1&lt;&lt;5)  /* voltage sense 2   */
DECL|macro|ACR1_SLOT_0_INPACK
mdefine_line|#define ACR1_SLOT_0_INPACK (1&lt;&lt;6)  /* inpack pin status */
DECL|macro|ACR1_SLOT_1_CD1
mdefine_line|#define ACR1_SLOT_1_CD1    (1&lt;&lt;8)  /* card detect 1     */
DECL|macro|ACR1_SLOT_1_CD2
mdefine_line|#define ACR1_SLOT_1_CD2    (1&lt;&lt;9)  /* card detect 2     */
DECL|macro|ACR1_SLOT_1_READY
mdefine_line|#define ACR1_SLOT_1_READY  (1&lt;&lt;10) /* ready             */
DECL|macro|ACR1_SLOT_1_STATUS
mdefine_line|#define ACR1_SLOT_1_STATUS (1&lt;&lt;11) /* status change     */
DECL|macro|ACR1_SLOT_1_VS1
mdefine_line|#define ACR1_SLOT_1_VS1    (1&lt;&lt;12) /* voltage sense 1   */
DECL|macro|ACR1_SLOT_1_VS2
mdefine_line|#define ACR1_SLOT_1_VS2    (1&lt;&lt;13) /* voltage sense 2   */
DECL|macro|ACR1_SLOT_1_INPACK
mdefine_line|#define ACR1_SLOT_1_INPACK (1&lt;&lt;14) /* inpack pin status */
DECL|macro|CPLD_AUX0
mdefine_line|#define CPLD_AUX0      0xBE00000C
DECL|macro|CPLD_AUX1
mdefine_line|#define CPLD_AUX1      0xBE000010
DECL|macro|CPLD_AUX2
mdefine_line|#define CPLD_AUX2      0xBE000014
multiline_comment|/* Voltage levels */
multiline_comment|/* VPPEN1 - VPPEN0 */
DECL|macro|VPP_GND
mdefine_line|#define VPP_GND ((0&lt;&lt;1) | (0&lt;&lt;0))
DECL|macro|VPP_5V
mdefine_line|#define VPP_5V  ((1&lt;&lt;1) | (0&lt;&lt;0))
DECL|macro|VPP_3V
mdefine_line|#define VPP_3V  ((0&lt;&lt;1) | (1&lt;&lt;0))
DECL|macro|VPP_12V
mdefine_line|#define VPP_12V ((0&lt;&lt;1) | (1&lt;&lt;0))
DECL|macro|VPP_HIZ
mdefine_line|#define VPP_HIZ ((1&lt;&lt;1) | (1&lt;&lt;0))
multiline_comment|/* VCCEN1 - VCCEN0 */
DECL|macro|VCC_3V
mdefine_line|#define VCC_3V  ((0&lt;&lt;1) | (1&lt;&lt;0))
DECL|macro|VCC_5V
mdefine_line|#define VCC_5V  ((1&lt;&lt;1) | (0&lt;&lt;0))
DECL|macro|VCC_HIZ
mdefine_line|#define VCC_HIZ ((0&lt;&lt;1) | (0&lt;&lt;0))
multiline_comment|/* VPP/VCC */
DECL|macro|SET_VCC_VPP
mdefine_line|#define SET_VCC_VPP(VCC, VPP, SLOT)&bslash;&n;&t;((((VCC)&lt;&lt;2) | ((VPP)&lt;&lt;0)) &lt;&lt; ((SLOT)*8))
multiline_comment|/* PCI PB1000 specific defines */
multiline_comment|/* The reason these defines are here instead of au1000.h is because&n; * the Au1000 does not have a PCI bus controller so the PCI implementation&n; * on the some of the older Pb1000 boards was very board specific.&n; */
DECL|macro|PCI_CONFIG_BASE
mdefine_line|#define PCI_CONFIG_BASE   0xBA020000 /* the only external slot */
DECL|macro|SDRAM_DEVID
mdefine_line|#define SDRAM_DEVID       0xBA010000
DECL|macro|SDRAM_CMD
mdefine_line|#define SDRAM_CMD         0xBA010004
DECL|macro|SDRAM_CLASS
mdefine_line|#define SDRAM_CLASS       0xBA010008
DECL|macro|SDRAM_MISC
mdefine_line|#define SDRAM_MISC        0xBA01000C
DECL|macro|SDRAM_MBAR
mdefine_line|#define SDRAM_MBAR        0xBA010010
DECL|macro|PCI_IO_DATA_PORT
mdefine_line|#define PCI_IO_DATA_PORT  0xBA800000
DECL|macro|PCI_IO_ADDR
mdefine_line|#define PCI_IO_ADDR       0xBE00001C
DECL|macro|PCI_INT_ACK
mdefine_line|#define PCI_INT_ACK       0xBBC00000
DECL|macro|PCI_IO_READ
mdefine_line|#define PCI_IO_READ       0xBBC00020
DECL|macro|PCI_IO_WRITE
mdefine_line|#define PCI_IO_WRITE      0xBBC00030
DECL|macro|PCI_BRIDGE_CONFIG
mdefine_line|#define PCI_BRIDGE_CONFIG 0xBE000018
DECL|macro|PCI_IO_START
mdefine_line|#define PCI_IO_START      0x10000000
DECL|macro|PCI_IO_END
mdefine_line|#define PCI_IO_END        0x1000ffff
DECL|macro|PCI_MEM_START
mdefine_line|#define PCI_MEM_START     0x18000000
DECL|macro|PCI_MEM_END
mdefine_line|#define PCI_MEM_END       0x18ffffff
DECL|macro|PCI_FIRST_DEVFN
mdefine_line|#define PCI_FIRST_DEVFN   0
DECL|macro|PCI_LAST_DEVFN
mdefine_line|#define PCI_LAST_DEVFN    1
DECL|function|au_pci_io_readb
r_static
r_inline
id|u8
id|au_pci_io_readb
c_func
(paren
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
)paren
op_or
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
r_return
(paren
id|readl
c_func
(paren
id|PCI_IO_DATA_PORT
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|au_pci_io_readw
r_static
r_inline
id|u16
id|au_pci_io_readw
c_func
(paren
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
)paren
op_or
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
r_return
(paren
id|readl
c_func
(paren
id|PCI_IO_DATA_PORT
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
DECL|function|au_pci_io_readl
r_static
r_inline
id|u32
id|au_pci_io_readl
c_func
(paren
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
)paren
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
r_return
id|readl
c_func
(paren
id|PCI_IO_DATA_PORT
)paren
suffix:semicolon
)brace
DECL|function|au_pci_io_writeb
r_static
r_inline
r_void
id|au_pci_io_writeb
c_func
(paren
id|u8
id|val
comma
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
)paren
op_or
(paren
l_int|1
op_lshift
l_int|12
)paren
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|PCI_IO_DATA_PORT
)paren
suffix:semicolon
)brace
DECL|function|au_pci_io_writew
r_static
r_inline
r_void
id|au_pci_io_writew
c_func
(paren
id|u16
id|val
comma
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
)paren
op_or
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|PCI_IO_DATA_PORT
)paren
suffix:semicolon
)brace
DECL|function|au_pci_io_writel
r_static
r_inline
r_void
id|au_pci_io_writel
c_func
(paren
id|u32
id|val
comma
id|u32
id|addr
)paren
(brace
id|writel
c_func
(paren
id|addr
comma
id|PCI_IO_ADDR
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffcfff
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|PCI_IO_DATA_PORT
)paren
suffix:semicolon
)brace
DECL|function|set_sdram_extbyte
r_static
r_inline
r_void
id|set_sdram_extbyte
c_func
(paren
r_void
)paren
(brace
id|writel
c_func
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffff00
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
)brace
DECL|function|set_slot_extbyte
r_static
r_inline
r_void
id|set_slot_extbyte
c_func
(paren
r_void
)paren
(brace
id|writel
c_func
(paren
(paren
id|readl
c_func
(paren
id|PCI_BRIDGE_CONFIG
)paren
op_amp
l_int|0xffffbf00
)paren
op_or
l_int|0x18
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_PB1000_H */
eof
