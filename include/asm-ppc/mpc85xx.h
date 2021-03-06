multiline_comment|/*&n; * include/asm-ppc/mpc85xx.h&n; *&n; * MPC85xx definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_MPC85xx_H__
DECL|macro|__ASM_MPC85xx_H__
mdefine_line|#define __ASM_MPC85xx_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#ifdef CONFIG_85xx
macro_line|#ifdef CONFIG_MPC8540_ADS
macro_line|#include &lt;platforms/85xx/mpc8540_ads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MPC8555_CDS
macro_line|#include &lt;platforms/85xx/mpc8555_cds.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MPC8560_ADS
macro_line|#include &lt;platforms/85xx/mpc8560_ads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SBC8560
macro_line|#include &lt;platforms/85xx/sbc8560.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_STX_GP3
macro_line|#include &lt;platforms/85xx/stx_gp3.h&gt;
macro_line|#endif
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE        isa_io_base
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE   isa_mem_base
macro_line|#ifdef CONFIG_PCI
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET pci_dram_offset
macro_line|#else
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#endif
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
multiline_comment|/* Offset from CCSRBAR */
DECL|macro|MPC85xx_CPM_OFFSET
mdefine_line|#define MPC85xx_CPM_OFFSET&t;(0x80000)
DECL|macro|MPC85xx_CPM_SIZE
mdefine_line|#define MPC85xx_CPM_SIZE&t;(0x40000)
DECL|macro|MPC85xx_DMA_OFFSET
mdefine_line|#define MPC85xx_DMA_OFFSET&t;(0x21000)
DECL|macro|MPC85xx_DMA_SIZE
mdefine_line|#define MPC85xx_DMA_SIZE&t;(0x01000)
DECL|macro|MPC85xx_DMA0_OFFSET
mdefine_line|#define MPC85xx_DMA0_OFFSET&t;(0x21100)
DECL|macro|MPC85xx_DMA0_SIZE
mdefine_line|#define MPC85xx_DMA0_SIZE&t;(0x00080)
DECL|macro|MPC85xx_DMA1_OFFSET
mdefine_line|#define MPC85xx_DMA1_OFFSET&t;(0x21180)
DECL|macro|MPC85xx_DMA1_SIZE
mdefine_line|#define MPC85xx_DMA1_SIZE&t;(0x00080)
DECL|macro|MPC85xx_DMA2_OFFSET
mdefine_line|#define MPC85xx_DMA2_OFFSET&t;(0x21200)
DECL|macro|MPC85xx_DMA2_SIZE
mdefine_line|#define MPC85xx_DMA2_SIZE&t;(0x00080)
DECL|macro|MPC85xx_DMA3_OFFSET
mdefine_line|#define MPC85xx_DMA3_OFFSET&t;(0x21280)
DECL|macro|MPC85xx_DMA3_SIZE
mdefine_line|#define MPC85xx_DMA3_SIZE&t;(0x00080)
DECL|macro|MPC85xx_ENET1_OFFSET
mdefine_line|#define MPC85xx_ENET1_OFFSET&t;(0x24000)
DECL|macro|MPC85xx_ENET1_SIZE
mdefine_line|#define MPC85xx_ENET1_SIZE&t;(0x01000)
DECL|macro|MPC85xx_ENET2_OFFSET
mdefine_line|#define MPC85xx_ENET2_OFFSET&t;(0x25000)
DECL|macro|MPC85xx_ENET2_SIZE
mdefine_line|#define MPC85xx_ENET2_SIZE&t;(0x01000)
DECL|macro|MPC85xx_ENET3_OFFSET
mdefine_line|#define MPC85xx_ENET3_OFFSET&t;(0x26000)
DECL|macro|MPC85xx_ENET3_SIZE
mdefine_line|#define MPC85xx_ENET3_SIZE&t;(0x01000)
DECL|macro|MPC85xx_GUTS_OFFSET
mdefine_line|#define MPC85xx_GUTS_OFFSET&t;(0xe0000)
DECL|macro|MPC85xx_GUTS_SIZE
mdefine_line|#define MPC85xx_GUTS_SIZE&t;(0x01000)
DECL|macro|MPC85xx_IIC1_OFFSET
mdefine_line|#define MPC85xx_IIC1_OFFSET&t;(0x03000)
DECL|macro|MPC85xx_IIC1_SIZE
mdefine_line|#define MPC85xx_IIC1_SIZE&t;(0x01000)
DECL|macro|MPC85xx_OPENPIC_OFFSET
mdefine_line|#define MPC85xx_OPENPIC_OFFSET&t;(0x40000)
DECL|macro|MPC85xx_OPENPIC_SIZE
mdefine_line|#define MPC85xx_OPENPIC_SIZE&t;(0x40000)
DECL|macro|MPC85xx_PCI1_OFFSET
mdefine_line|#define MPC85xx_PCI1_OFFSET&t;(0x08000)
DECL|macro|MPC85xx_PCI1_SIZE
mdefine_line|#define MPC85xx_PCI1_SIZE&t;(0x01000)
DECL|macro|MPC85xx_PCI2_OFFSET
mdefine_line|#define MPC85xx_PCI2_OFFSET&t;(0x09000)
DECL|macro|MPC85xx_PCI2_SIZE
mdefine_line|#define MPC85xx_PCI2_SIZE&t;(0x01000)
DECL|macro|MPC85xx_PERFMON_OFFSET
mdefine_line|#define MPC85xx_PERFMON_OFFSET&t;(0xe1000)
DECL|macro|MPC85xx_PERFMON_SIZE
mdefine_line|#define MPC85xx_PERFMON_SIZE&t;(0x01000)
DECL|macro|MPC85xx_SEC2_OFFSET
mdefine_line|#define MPC85xx_SEC2_OFFSET&t;(0x30000)
DECL|macro|MPC85xx_SEC2_SIZE
mdefine_line|#define MPC85xx_SEC2_SIZE&t;(0x10000)
DECL|macro|MPC85xx_UART0_OFFSET
mdefine_line|#define MPC85xx_UART0_OFFSET&t;(0x04500)
DECL|macro|MPC85xx_UART0_SIZE
mdefine_line|#define MPC85xx_UART0_SIZE&t;(0x00100)
DECL|macro|MPC85xx_UART1_OFFSET
mdefine_line|#define MPC85xx_UART1_OFFSET&t;(0x04600)
DECL|macro|MPC85xx_UART1_SIZE
mdefine_line|#define MPC85xx_UART1_SIZE&t;(0x00100)
DECL|macro|MPC85xx_CCSRBAR_SIZE
mdefine_line|#define MPC85xx_CCSRBAR_SIZE&t;(1024*1024)
multiline_comment|/* Let modules/drivers get at CCSRBAR */
r_extern
id|phys_addr_t
id|get_ccsrbar
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|CCSRBAR
mdefine_line|#define CCSRBAR get_ccsrbar()
macro_line|#else
DECL|macro|CCSRBAR
mdefine_line|#define CCSRBAR BOARD_CCSRBAR
macro_line|#endif
DECL|enum|ppc_sys_devices
r_enum
id|ppc_sys_devices
(brace
DECL|enumerator|MPC85xx_TSEC1
id|MPC85xx_TSEC1
comma
DECL|enumerator|MPC85xx_TSEC2
id|MPC85xx_TSEC2
comma
DECL|enumerator|MPC85xx_FEC
id|MPC85xx_FEC
comma
DECL|enumerator|MPC85xx_IIC1
id|MPC85xx_IIC1
comma
DECL|enumerator|MPC85xx_DMA0
id|MPC85xx_DMA0
comma
DECL|enumerator|MPC85xx_DMA1
id|MPC85xx_DMA1
comma
DECL|enumerator|MPC85xx_DMA2
id|MPC85xx_DMA2
comma
DECL|enumerator|MPC85xx_DMA3
id|MPC85xx_DMA3
comma
DECL|enumerator|MPC85xx_DUART
id|MPC85xx_DUART
comma
DECL|enumerator|MPC85xx_PERFMON
id|MPC85xx_PERFMON
comma
DECL|enumerator|MPC85xx_SEC2
id|MPC85xx_SEC2
comma
DECL|enumerator|MPC85xx_CPM_SPI
id|MPC85xx_CPM_SPI
comma
DECL|enumerator|MPC85xx_CPM_I2C
id|MPC85xx_CPM_I2C
comma
DECL|enumerator|MPC85xx_CPM_USB
id|MPC85xx_CPM_USB
comma
DECL|enumerator|MPC85xx_CPM_SCC1
id|MPC85xx_CPM_SCC1
comma
DECL|enumerator|MPC85xx_CPM_SCC2
id|MPC85xx_CPM_SCC2
comma
DECL|enumerator|MPC85xx_CPM_SCC3
id|MPC85xx_CPM_SCC3
comma
DECL|enumerator|MPC85xx_CPM_SCC4
id|MPC85xx_CPM_SCC4
comma
DECL|enumerator|MPC85xx_CPM_FCC1
id|MPC85xx_CPM_FCC1
comma
DECL|enumerator|MPC85xx_CPM_FCC2
id|MPC85xx_CPM_FCC2
comma
DECL|enumerator|MPC85xx_CPM_FCC3
id|MPC85xx_CPM_FCC3
comma
DECL|enumerator|MPC85xx_CPM_MCC1
id|MPC85xx_CPM_MCC1
comma
DECL|enumerator|MPC85xx_CPM_MCC2
id|MPC85xx_CPM_MCC2
comma
DECL|enumerator|MPC85xx_CPM_SMC1
id|MPC85xx_CPM_SMC1
comma
DECL|enumerator|MPC85xx_CPM_SMC2
id|MPC85xx_CPM_SMC2
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_85xx */
macro_line|#endif /* __ASM_MPC85xx_H__ */
macro_line|#endif /* __KERNEL__ */
eof
