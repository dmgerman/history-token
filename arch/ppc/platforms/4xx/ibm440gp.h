multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibm440gp.h&n; *&n; * PPC440GP definitions&n; *&n; * Roland Dreier &lt;roland@digitalvampire.org&gt;&n; *&n; * Copyright 2002 Roland Dreier&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * This file contains code that was originally in the files ibm44x.h&n; * and ebony.h, which were written by Matt Porter of MontaVista Software Inc.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_PLATFORMS_IBM440GP_H
DECL|macro|__PPC_PLATFORMS_IBM440GP_H
mdefine_line|#define __PPC_PLATFORMS_IBM440GP_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|EMAC_NUMS
mdefine_line|#define EMAC_NUMS&t;&t;2
DECL|macro|UART_NUMS
mdefine_line|#define UART_NUMS&t;&t;2
DECL|macro|ZMII_NUMS
mdefine_line|#define ZMII_NUMS&t;&t;1
DECL|macro|IIC_NUMS
mdefine_line|#define IIC_NUMS&t;&t;2
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;&t;2
DECL|macro|IIC1_IRQ
mdefine_line|#define IIC1_IRQ&t;&t;3
DECL|macro|GPIO_NUMS
mdefine_line|#define GPIO_NUMS&t;&t;1
multiline_comment|/* UART location */
DECL|macro|PPC440GP_UART0_ADDR
mdefine_line|#define PPC440GP_UART0_ADDR&t;0x0000000140000200ULL
DECL|macro|PPC440GP_UART1_ADDR
mdefine_line|#define PPC440GP_UART1_ADDR&t;0x0000000140000300ULL
multiline_comment|/* EMAC location */
DECL|macro|PPC440GP_EMAC0_ADDR
mdefine_line|#define PPC440GP_EMAC0_ADDR&t;0x0000000140000800ULL
DECL|macro|PPC440GP_EMAC1_ADDR
mdefine_line|#define PPC440GP_EMAC1_ADDR&t;0x0000000140000900ULL
DECL|macro|PPC440GP_EMAC_SIZE
mdefine_line|#define PPC440GP_EMAC_SIZE&t;0x70
multiline_comment|/* EMAC IRQ&squot;s */
DECL|macro|BL_MAC_WOL
mdefine_line|#define BL_MAC_WOL&t;61&t;/* WOL */
DECL|macro|BL_MAC_WOL1
mdefine_line|#define BL_MAC_WOL1&t;63&t;/* WOL */
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
multiline_comment|/* ZMII location */
DECL|macro|PPC440GP_ZMII_ADDR
mdefine_line|#define PPC440GP_ZMII_ADDR&t;0x0000000140000780ULL
DECL|macro|PPC440GP_ZMII_SIZE
mdefine_line|#define PPC440GP_ZMII_SIZE&t;0x0c
multiline_comment|/* I2C location */
DECL|macro|PPC440GP_IIC0_ADDR
mdefine_line|#define PPC440GP_IIC0_ADDR&t;0x40000400
DECL|macro|PPC440GP_IIC1_ADDR
mdefine_line|#define PPC440GP_IIC1_ADDR&t;0x40000500
multiline_comment|/* GPIO location */
DECL|macro|PPC440GP_GPIO0_ADDR
mdefine_line|#define PPC440GP_GPIO0_ADDR&t;0x0000000140000700ULL
multiline_comment|/* Clock and Power Management */
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;&t;0x80000000&t;/* IIC interface */
DECL|macro|IBM_CPM_IIC1
mdefine_line|#define IBM_CPM_IIC1&t;&t;0x40000000&t;/* IIC interface */
DECL|macro|IBM_CPM_PCI
mdefine_line|#define IBM_CPM_PCI&t;&t;0x20000000&t;/* PCI bridge */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU&t;&t;0x02000000&t;/* processor core */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA&t;&t;0x01000000&t;/* DMA controller */
DECL|macro|IBM_CPM_BGO
mdefine_line|#define IBM_CPM_BGO&t;&t;0x00800000&t;/* PLB to OPB bus arbiter */
DECL|macro|IBM_CPM_BGI
mdefine_line|#define IBM_CPM_BGI&t;&t;0x00400000&t;/* OPB to PLB bridge */
DECL|macro|IBM_CPM_EBC
mdefine_line|#define IBM_CPM_EBC&t;&t;0x00200000&t;/* External Bux Controller */
DECL|macro|IBM_CPM_EBM
mdefine_line|#define IBM_CPM_EBM&t;&t;0x00100000&t;/* Ext Bus Master Interface */
DECL|macro|IBM_CPM_DMC
mdefine_line|#define IBM_CPM_DMC&t;&t;0x00080000&t;/* SDRAM peripheral controller */
DECL|macro|IBM_CPM_PLB
mdefine_line|#define IBM_CPM_PLB&t;&t;0x00040000&t;/* PLB bus arbiter */
DECL|macro|IBM_CPM_SRAM
mdefine_line|#define IBM_CPM_SRAM&t;&t;0x00020000&t;/* SRAM memory controller */
DECL|macro|IBM_CPM_PPM
mdefine_line|#define IBM_CPM_PPM&t;&t;0x00002000&t;/* PLB Performance Monitor */
DECL|macro|IBM_CPM_UIC1
mdefine_line|#define IBM_CPM_UIC1&t;&t;0x00001000&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0&t;&t;0x00000800&t;/* General Purpose IO (??) */
DECL|macro|IBM_CPM_GPT
mdefine_line|#define IBM_CPM_GPT&t;&t;0x00000400&t;/* General Purpose Timers  */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0&t;&t;0x00000200&t;/* serial port 0 */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1&t;&t;0x00000100&t;/* serial port 1 */
DECL|macro|IBM_CPM_UIC0
mdefine_line|#define IBM_CPM_UIC0&t;&t;0x00000080&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK&t;&t;0x00000040&t;/* CPU timers */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;&t;~(IBM_CPM_UIC | IBM_CPM_UIC1 | IBM_CPM_CPU &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBC | IBM_CPM_SRAM | IBM_CPM_BGO &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBM | IBM_CPM_PLB | IBM_CPM_OPB &bslash;&n;&t;&t;&t;&t;| IBM_CPM_TMRCLK | IBM_CPM_DMA | IBM_CPM_PCI)
DECL|macro|PPC440GP_OPB_BASE_START
mdefine_line|#define PPC440GP_OPB_BASE_START&t;0x0000000140000000ULL
multiline_comment|/*&n; * Serial port defines&n; */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
macro_line|#include &lt;asm/ibm44x.h&gt;
macro_line|#include &lt;syslib/ibm440gp_common.h&gt;
macro_line|#endif /* __PPC_PLATFORMS_IBM440GP_H */
macro_line|#endif /* __KERNEL__ */
eof
