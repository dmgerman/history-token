multiline_comment|/*&n; * arch/ppc/platforms/85xx/mpc85xx_cds_common.h&n; *&n; * MPC85xx CDS board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_MPC85XX_CDS_H__
DECL|macro|__MACH_MPC85XX_CDS_H__
mdefine_line|#define __MACH_MPC85XX_CDS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;syslib/ppc85xx_setup.h&gt;
DECL|macro|BOARD_CCSRBAR
mdefine_line|#define BOARD_CCSRBAR           ((uint)0xe0000000)
DECL|macro|CCSRBAR_SIZE
mdefine_line|#define CCSRBAR_SIZE            ((uint)1024*1024)
multiline_comment|/* CADMUS info */
DECL|macro|CADMUS_BASE
mdefine_line|#define CADMUS_BASE (0xf8004000)
DECL|macro|CADMUS_SIZE
mdefine_line|#define CADMUS_SIZE (256)
DECL|macro|CM_VER
mdefine_line|#define CM_VER&t;(0)
DECL|macro|CM_CSR
mdefine_line|#define CM_CSR&t;(1)
DECL|macro|CM_RST
mdefine_line|#define CM_RST&t;(2)
multiline_comment|/* PCI config */
DECL|macro|PCI1_CFG_ADDR_OFFSET
mdefine_line|#define PCI1_CFG_ADDR_OFFSET&t;(0x8000)
DECL|macro|PCI1_CFG_DATA_OFFSET
mdefine_line|#define PCI1_CFG_DATA_OFFSET&t;(0x8004)
DECL|macro|PCI2_CFG_ADDR_OFFSET
mdefine_line|#define PCI2_CFG_ADDR_OFFSET&t;(0x9000)
DECL|macro|PCI2_CFG_DATA_OFFSET
mdefine_line|#define PCI2_CFG_DATA_OFFSET&t;(0x9004)
multiline_comment|/* PCI interrupt controller */
DECL|macro|PIRQ0A
mdefine_line|#define PIRQ0A                   MPC85xx_IRQ_EXT0
DECL|macro|PIRQ0B
mdefine_line|#define PIRQ0B                   MPC85xx_IRQ_EXT1
DECL|macro|PIRQ0C
mdefine_line|#define PIRQ0C                   MPC85xx_IRQ_EXT2
DECL|macro|PIRQ0D
mdefine_line|#define PIRQ0D                   MPC85xx_IRQ_EXT3
DECL|macro|PIRQ1A
mdefine_line|#define PIRQ1A                   MPC85xx_IRQ_EXT11
multiline_comment|/* PCI 1 memory map */
DECL|macro|MPC85XX_PCI1_LOWER_IO
mdefine_line|#define MPC85XX_PCI1_LOWER_IO        0x00000000
DECL|macro|MPC85XX_PCI1_UPPER_IO
mdefine_line|#define MPC85XX_PCI1_UPPER_IO        0x00ffffff
DECL|macro|MPC85XX_PCI1_LOWER_MEM
mdefine_line|#define MPC85XX_PCI1_LOWER_MEM       0x80000000
DECL|macro|MPC85XX_PCI1_UPPER_MEM
mdefine_line|#define MPC85XX_PCI1_UPPER_MEM       0x9fffffff
DECL|macro|MPC85XX_PCI1_IO_BASE
mdefine_line|#define MPC85XX_PCI1_IO_BASE         0xe2000000
DECL|macro|MPC85XX_PCI1_MEM_OFFSET
mdefine_line|#define MPC85XX_PCI1_MEM_OFFSET      0x00000000
DECL|macro|MPC85XX_PCI1_IO_SIZE
mdefine_line|#define MPC85XX_PCI1_IO_SIZE         0x01000000
multiline_comment|/* PCI 2 memory map */
multiline_comment|/* Note: the standard PPC fixups will cause IO space to get bumped by&n; * hose-&gt;io_base_virt - isa_io_base =&gt; MPC85XX_PCI1_IO_SIZE */
DECL|macro|MPC85XX_PCI2_LOWER_IO
mdefine_line|#define MPC85XX_PCI2_LOWER_IO        0x00000000
DECL|macro|MPC85XX_PCI2_UPPER_IO
mdefine_line|#define MPC85XX_PCI2_UPPER_IO        0x00ffffff
DECL|macro|MPC85XX_PCI2_LOWER_MEM
mdefine_line|#define MPC85XX_PCI2_LOWER_MEM       0xa0000000
DECL|macro|MPC85XX_PCI2_UPPER_MEM
mdefine_line|#define MPC85XX_PCI2_UPPER_MEM       0xbfffffff
DECL|macro|MPC85XX_PCI2_IO_BASE
mdefine_line|#define MPC85XX_PCI2_IO_BASE         0xe3000000
DECL|macro|MPC85XX_PCI2_MEM_OFFSET
mdefine_line|#define MPC85XX_PCI2_MEM_OFFSET      0x00000000
DECL|macro|MPC85XX_PCI2_IO_SIZE
mdefine_line|#define MPC85XX_PCI2_IO_SIZE         0x01000000
macro_line|#endif /* __MACH_MPC85XX_CDS_H__ */
eof
