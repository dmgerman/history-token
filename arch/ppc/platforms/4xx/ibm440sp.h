multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibm440sp.h&n; *&n; * PPC440SP definitions&n; *&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * Copyright 2004-2005 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_PLATFORMS_IBM440SP_H
DECL|macro|__PPC_PLATFORMS_IBM440SP_H
mdefine_line|#define __PPC_PLATFORMS_IBM440SP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ibm44x.h&gt;
multiline_comment|/* UART */
DECL|macro|PPC440SP_UART0_ADDR
mdefine_line|#define PPC440SP_UART0_ADDR&t;0x00000001f0000200ULL
DECL|macro|PPC440SP_UART1_ADDR
mdefine_line|#define PPC440SP_UART1_ADDR&t;0x00000001f0000300ULL
DECL|macro|PPC440SP_UART2_ADDR
mdefine_line|#define PPC440SP_UART2_ADDR&t;0x00000001f0000600ULL
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;&t;0
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;&t;1
DECL|macro|UART2_INT
mdefine_line|#define UART2_INT&t;&t;2
multiline_comment|/* Clock and Power Management */
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;&t;0x80000000&t;/* IIC interface */
DECL|macro|IBM_CPM_IIC1
mdefine_line|#define IBM_CPM_IIC1&t;&t;0x40000000&t;/* IIC interface */
DECL|macro|IBM_CPM_PCI
mdefine_line|#define IBM_CPM_PCI&t;&t;0x20000000&t;/* PCI bridge */
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
DECL|macro|IBM_CPM_UART2
mdefine_line|#define IBM_CPM_UART2&t;&t;0x00000100&t;/* serial port 1 */
DECL|macro|IBM_CPM_UIC0
mdefine_line|#define IBM_CPM_UIC0&t;&t;0x00000080&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK&t;&t;0x00000040&t;/* CPU timers */
DECL|macro|IBM_CPM_EMAC0
mdefine_line|#define IBM_CPM_EMAC0  &t;&t;0x00000020&t;/* EMAC 0     */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;&t;~(IBM_CPM_UIC | IBM_CPM_UIC1 | IBM_CPM_CPU &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBC | IBM_CPM_SRAM | IBM_CPM_BGO &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EBM | IBM_CPM_PLB | IBM_CPM_OPB &bslash;&n;&t;&t;&t;&t;| IBM_CPM_TMRCLK | IBM_CPM_DMA | IBM_CPM_PCI &bslash;&n;&t;&t;&t;&t;| IBM_CPM_TAHOE0 | IBM_CPM_TAHOE1 &bslash;&n;&t;&t;&t;&t;| IBM_CPM_EMAC0 | IBM_CPM_EMAC1 &bslash;&n;&t;&t;&t;  &t;| IBM_CPM_EMAC2 | IBM_CPM_EMAC3 )
macro_line|#endif /* __PPC_PLATFORMS_IBM440SP_H */
macro_line|#endif /* __KERNEL__ */
eof
