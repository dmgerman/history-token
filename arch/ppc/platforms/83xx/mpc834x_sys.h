multiline_comment|/*&n; * arch/ppc/platforms/83xx/mpc834x_sys.h&n; *&n; * MPC834X SYS common board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_MPC83XX_SYS_H__
DECL|macro|__MACH_MPC83XX_SYS_H__
mdefine_line|#define __MACH_MPC83XX_SYS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;syslib/ppc83xx_setup.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|VIRT_IMMRBAR
mdefine_line|#define VIRT_IMMRBAR&t;&t;((uint)0xfe000000)
DECL|macro|BCSR_PHYS_ADDR
mdefine_line|#define BCSR_PHYS_ADDR&t;&t;((uint)0xf8000000)
DECL|macro|BCSR_VIRT_ADDR
mdefine_line|#define BCSR_VIRT_ADDR&t;&t;((uint)0xfe100000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(32 * 1024))
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* PCI interrupt controller */
DECL|macro|PIRQA
mdefine_line|#define PIRQA        MPC83xx_IRQ_IRQ4
DECL|macro|PIRQB
mdefine_line|#define PIRQB        MPC83xx_IRQ_IRQ5
DECL|macro|PIRQC
mdefine_line|#define PIRQC        MPC83xx_IRQ_IRQ6
DECL|macro|PIRQD
mdefine_line|#define PIRQD        MPC83xx_IRQ_IRQ7
DECL|macro|MPC834x_SYS_PCI1_LOWER_IO
mdefine_line|#define MPC834x_SYS_PCI1_LOWER_IO        0x00000000
DECL|macro|MPC834x_SYS_PCI1_UPPER_IO
mdefine_line|#define MPC834x_SYS_PCI1_UPPER_IO        0x00ffffff
DECL|macro|MPC834x_SYS_PCI1_LOWER_MEM
mdefine_line|#define MPC834x_SYS_PCI1_LOWER_MEM       0x80000000
DECL|macro|MPC834x_SYS_PCI1_UPPER_MEM
mdefine_line|#define MPC834x_SYS_PCI1_UPPER_MEM       0x9fffffff
DECL|macro|MPC834x_SYS_PCI1_IO_BASE
mdefine_line|#define MPC834x_SYS_PCI1_IO_BASE         0xe2000000
DECL|macro|MPC834x_SYS_PCI1_MEM_OFFSET
mdefine_line|#define MPC834x_SYS_PCI1_MEM_OFFSET      0x00000000
DECL|macro|MPC834x_SYS_PCI1_IO_SIZE
mdefine_line|#define MPC834x_SYS_PCI1_IO_SIZE         0x01000000
macro_line|#endif /* CONFIG_PCI */
macro_line|#endif                /* __MACH_MPC83XX_SYS_H__ */
eof
