multiline_comment|/*&n; * arch/ppc/platforms/ibm440gx.h&n; *&n; * PPC440GX definitions&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2002 Roland Dreier&n; * Copyright 2003 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; * &n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_PLATFORMS_IBM440GX_H
DECL|macro|__PPC_PLATFORMS_IBM440GX_H
mdefine_line|#define __PPC_PLATFORMS_IBM440GX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ibm44x.h&gt;
multiline_comment|/* UART */
DECL|macro|PPC440GX_UART0_ADDR
mdefine_line|#define PPC440GX_UART0_ADDR&t;0x0000000140000200ULL
DECL|macro|PPC440GX_UART1_ADDR
mdefine_line|#define PPC440GX_UART1_ADDR&t;0x0000000140000300ULL
DECL|macro|UART0_IRQ
mdefine_line|#define UART0_IRQ&t;&t;0
DECL|macro|UART1_IRQ
mdefine_line|#define UART1_IRQ&t;&t;1
multiline_comment|/* EMAC */
DECL|macro|PPC440GX_EMAC0_ADDR
mdefine_line|#define PPC440GX_EMAC0_ADDR&t;0x0000000140000800ULL
DECL|macro|PPC440GX_EMAC1_ADDR
mdefine_line|#define PPC440GX_EMAC1_ADDR&t;0x0000000140000900ULL
DECL|macro|PPC440GX_EMAC2_ADDR
mdefine_line|#define PPC440GX_EMAC2_ADDR&t;0x0000000140000C00ULL
DECL|macro|PPC440GX_EMAC3_ADDR
mdefine_line|#define PPC440GX_EMAC3_ADDR&t;0x0000000140000E00ULL
DECL|macro|PPC440GX_EMAC_SIZE
mdefine_line|#define PPC440GX_EMAC_SIZE&t;0xFC
DECL|macro|EMAC_NUMS
mdefine_line|#define EMAC_NUMS               2
DECL|macro|BL_MAC_WOL
mdefine_line|#define BL_MAC_WOL&t;61&t;/* WOL */
DECL|macro|BL_MAC_WOL1
mdefine_line|#define BL_MAC_WOL1&t;63&t;/* WOL */
DECL|macro|BL_MAC_WOL2
mdefine_line|#define BL_MAC_WOL2&t;65&t;/* WOL */
DECL|macro|BL_MAC_WOL3
mdefine_line|#define BL_MAC_WOL3&t;67&t;/* WOL */
DECL|macro|BL_MAL_SERR
mdefine_line|#define BL_MAL_SERR&t;32&t;/* MAL SERR */
DECL|macro|BL_MAL_TXDE
mdefine_line|#define BL_MAL_TXDE&t;33&t;/* MAL TXDE */
DECL|macro|BL_MAL_RXDE
mdefine_line|#define BL_MAL_RXDE&t;34&t;/* MAL RXDE */
DECL|macro|BL_MAL_TXEOB
mdefine_line|#define BL_MAL_TXEOB&t;10&t;/* MAL TX EOB */
DECL|macro|BL_MAL_RXEOB
mdefine_line|#define BL_MAL_RXEOB&t;11&t;/* MAL RX EOB */
DECL|macro|BL_MAC_ETH0
mdefine_line|#define BL_MAC_ETH0&t;60&t;/* MAC */
DECL|macro|BL_MAC_ETH1
mdefine_line|#define BL_MAC_ETH1&t;62&t;/* MAC */
DECL|macro|BL_MAC_ETH2
mdefine_line|#define BL_MAC_ETH2&t;64&t;/* MAC */
DECL|macro|BL_MAC_ETH3
mdefine_line|#define BL_MAC_ETH3&t;66&t;/* MAC */
DECL|macro|BL_TAH0
mdefine_line|#define BL_TAH0&t;&t;68&t;/* TAH 0 */
DECL|macro|BL_TAH1
mdefine_line|#define BL_TAH1&t;&t;69&t;/* TAH 1 */
multiline_comment|/* TAH */
DECL|macro|PPC440GX_TAH0_ADDR
mdefine_line|#define PPC440GX_TAH0_ADDR&t;0x0000000140000B00ULL
DECL|macro|PPC440GX_TAH1_ADDR
mdefine_line|#define PPC440GX_TAH1_ADDR&t;0x0000000140000D00ULL
DECL|macro|PPC440GX_TAH_SIZE
mdefine_line|#define PPC440GX_TAH_SIZE&t;0xFC
multiline_comment|/* ZMII */
DECL|macro|PPC440GX_ZMII_ADDR
mdefine_line|#define PPC440GX_ZMII_ADDR&t;0x0000000140000780ULL
DECL|macro|PPC440GX_ZMII_SIZE
mdefine_line|#define PPC440GX_ZMII_SIZE&t;0x0c
multiline_comment|/* RGMII */
DECL|macro|PPC440GX_RGMII_ADDR
mdefine_line|#define PPC440GX_RGMII_ADDR&t;0x0000000140000790ULL
DECL|macro|PPC440GX_RGMII_SIZE
mdefine_line|#define PPC440GX_RGMII_SIZE&t;0x0c
multiline_comment|/* IIC  */
DECL|macro|PPC440GX_IIC0_ADDR
mdefine_line|#define PPC440GX_IIC0_ADDR&t;0x40000400
DECL|macro|PPC440GX_IIC1_ADDR
mdefine_line|#define PPC440GX_IIC1_ADDR&t;0x40000500
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;&t;2
DECL|macro|IIC1_IRQ
mdefine_line|#define IIC1_IRQ&t;&t;3
multiline_comment|/* GPIO */
DECL|macro|PPC440GX_GPIO0_ADDR
mdefine_line|#define PPC440GX_GPIO0_ADDR&t;0x0000000140000700ULL
multiline_comment|/* Clock and Power Management */
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;&t;0x80000000&t;/* IIC interface */
DECL|macro|IBM_CPM_IIC1
mdefine_line|#define IBM_CPM_IIC1&t;&t;0x40000000&t;/* IIC interface */
DECL|macro|IBM_CPM_PCI
mdefine_line|#define IBM_CPM_PCI&t;&t;0x20000000&t;/* PCI bridge */
DECL|macro|IBM_CPM_RGMII
mdefine_line|#define IBM_CPM_RGMII&t;&t;0x10000000&t;/* RGMII */
DECL|macro|IBM_CPM_TAHOE0
mdefine_line|#define IBM_CPM_TAHOE0&t;&t;0x08000000&t;/* TAHOE 0 */
DECL|macro|IBM_CPM_TAHOE1
mdefine_line|#define IBM_CPM_TAHOE1&t;&t;0x04000000&t;/* TAHOE 1 */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU&t;&t;    0x02000000&t;/* processor core */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA&t;&t;    0x01000000&t;/* DMA controller */
DECL|macro|IBM_CPM_BGO
mdefine_line|#define IBM_CPM_BGO&t;&t;    0x00800000&t;/* PLB to OPB bus arbiter */
DECL|macro|IBM_CPM_BGI
mdefine_line|#define IBM_CPM_BGI&t;&t;    0x00400000&t;/* OPB to PLB bridge */
DECL|macro|IBM_CPM_EBC
mdefine_line|#define IBM_CPM_EBC&t;&t;    0x00200000&t;/* External Bux Controller */
DECL|macro|IBM_CPM_EBM
mdefine_line|#define IBM_CPM_EBM&t;&t;    0x00100000&t;/* Ext Bus Master Interface */
DECL|macro|IBM_CPM_DMC
mdefine_line|#define IBM_CPM_DMC&t;&t;    0x00080000&t;/* SDRAM peripheral controller */
DECL|macro|IBM_CPM_PLB
mdefine_line|#define IBM_CPM_PLB&t;&t;    0x00040000&t;/* PLB bus arbiter */
DECL|macro|IBM_CPM_SRAM
mdefine_line|#define IBM_CPM_SRAM&t;&t;0x00020000&t;/* SRAM memory controller */
DECL|macro|IBM_CPM_PPM
mdefine_line|#define IBM_CPM_PPM&t;&t;    0x00002000&t;/* PLB Performance Monitor */
DECL|macro|IBM_CPM_UIC1
mdefine_line|#define IBM_CPM_UIC1&t;&t;0x00001000&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0&t;&t;0x00000800&t;/* General Purpose IO (??) */
DECL|macro|IBM_CPM_GPT
mdefine_line|#define IBM_CPM_GPT&t;&t;    0x00000400&t;/* General Purpose Timers  */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0&t;&t;0x00000200&t;/* serial port 0 */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1&t;&t;0x00000100&t;/* serial port 1 */
DECL|macro|IBM_CPM_UIC0
mdefine_line|#define IBM_CPM_UIC0&t;&t;0x00000080&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK&t;&t;0x00000040&t;/* CPU timers */
DECL|macro|IBM_CPM_EMAC0
mdefine_line|#define IBM_CPM_EMAC0  &t;&t;0x00000020&t;/* EMAC 0     */
DECL|macro|IBM_CPM_EMAC1
mdefine_line|#define IBM_CPM_EMAC1  &t;&t;0x00000010&t;/* EMAC 1     */
DECL|macro|IBM_CPM_EMAC2
mdefine_line|#define IBM_CPM_EMAC2  &t;&t;0x00000008&t;/* EMAC 2     */
DECL|macro|IBM_CPM_EMAC3
mdefine_line|#define IBM_CPM_EMAC3  &t;&t;0x00000004&t;/* EMAC 3     */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;&t;~(IBM_CPM_UIC | IBM_CPM_UIC1 | IBM_CPM_CPU &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBC | IBM_CPM_SRAM | IBM_CPM_BGO &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBM | IBM_CPM_PLB | IBM_CPM_OPB &bslash;&n;&t;&t;&t;&t;| IBM_CPM_TMRCLK | IBM_CPM_DMA | IBM_CPM_PCI &bslash;&n;&t;&t;&t;&t;| IBM_CPM_TAHOE0 | IBM_CPM_TAHOE1 &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EMAC0 | IBM_CPM_EMAC1 &bslash;&n;&t;&t;&t;  &t;| IBM_CPM_EMAC2 | IBM_CPM_EMAC3 )&t;
multiline_comment|/* OPB */
DECL|macro|PPC440GX_OPB_BASE_START
mdefine_line|#define PPC440GX_OPB_BASE_START&t;0x0000000140000000ULL
multiline_comment|/*&n; * Serial port defines&n; */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
macro_line|#endif /* __PPC_PLATFORMS_IBM440GX_H */
macro_line|#endif /* __KERNEL__ */
eof
