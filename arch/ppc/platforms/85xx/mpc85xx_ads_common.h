multiline_comment|/*&n; * arch/ppc/platforms/85xx/mpc85xx_ads_common.h&n; *&n; * MPC85XX ADS common board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_MPC85XX_ADS_H__
DECL|macro|__MACH_MPC85XX_ADS_H__
mdefine_line|#define __MACH_MPC85XX_ADS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|BOARD_CCSRBAR
mdefine_line|#define BOARD_CCSRBAR&t;&t;((uint)0xe0000000)
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0xf8000000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(32 * 1024))
r_extern
r_int
id|mpc85xx_ads_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
r_extern
r_void
id|mpc85xx_ads_init_IRQ
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|mpc85xx_ads_map_io
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* PCI interrupt controller */
DECL|macro|PIRQA
mdefine_line|#define PIRQA&t;&t;MPC85xx_IRQ_EXT1
DECL|macro|PIRQB
mdefine_line|#define PIRQB&t;&t;MPC85xx_IRQ_EXT2
DECL|macro|PIRQC
mdefine_line|#define PIRQC&t;&t;MPC85xx_IRQ_EXT3
DECL|macro|PIRQD
mdefine_line|#define PIRQD&t;&t;MPC85xx_IRQ_EXT4
DECL|macro|MPC85XX_PCI1_LOWER_IO
mdefine_line|#define MPC85XX_PCI1_LOWER_IO&t;0x00000000
DECL|macro|MPC85XX_PCI1_UPPER_IO
mdefine_line|#define MPC85XX_PCI1_UPPER_IO&t;0x00ffffff
DECL|macro|MPC85XX_PCI1_LOWER_MEM
mdefine_line|#define MPC85XX_PCI1_LOWER_MEM&t;0x80000000
DECL|macro|MPC85XX_PCI1_UPPER_MEM
mdefine_line|#define MPC85XX_PCI1_UPPER_MEM&t;0x9fffffff
DECL|macro|MPC85XX_PCI1_IO_BASE
mdefine_line|#define MPC85XX_PCI1_IO_BASE&t;0xe2000000
DECL|macro|MPC85XX_PCI1_MEM_OFFSET
mdefine_line|#define MPC85XX_PCI1_MEM_OFFSET&t;0x00000000
DECL|macro|MPC85XX_PCI1_IO_SIZE
mdefine_line|#define MPC85XX_PCI1_IO_SIZE&t;0x01000000
macro_line|#endif&t;&t;&t;&t;/* __MACH_MPC85XX_ADS_H__ */
eof
