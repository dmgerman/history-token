multiline_comment|/*&n; * include/asm-ppc/mpc83xx.h&n; *&n; * MPC83xx definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_MPC83xx_H__
DECL|macro|__ASM_MPC83xx_H__
mdefine_line|#define __ASM_MPC83xx_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#ifdef CONFIG_83xx
macro_line|#ifdef CONFIG_MPC834x_SYS
macro_line|#include &lt;platforms/83xx/mpc834x_sys.h&gt;
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
multiline_comment|/* Internal IRQs on MPC83xx OpenPIC */
multiline_comment|/* Not all of these exist on all MPC83xx implementations */
macro_line|#ifndef MPC83xx_IPIC_IRQ_OFFSET
DECL|macro|MPC83xx_IPIC_IRQ_OFFSET
mdefine_line|#define MPC83xx_IPIC_IRQ_OFFSET&t;0
macro_line|#endif
DECL|macro|NR_IPIC_INTS
mdefine_line|#define NR_IPIC_INTS 128
DECL|macro|MPC83xx_IRQ_UART1
mdefine_line|#define MPC83xx_IRQ_UART1&t;( 9 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_UART2
mdefine_line|#define MPC83xx_IRQ_UART2&t;(10 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_SEC2
mdefine_line|#define MPC83xx_IRQ_SEC2&t;(11 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_IIC1
mdefine_line|#define MPC83xx_IRQ_IIC1&t;(14 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_IIC2
mdefine_line|#define MPC83xx_IRQ_IIC2&t;(15 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_SPI
mdefine_line|#define MPC83xx_IRQ_SPI&t;&t;(16 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT1
mdefine_line|#define MPC83xx_IRQ_EXT1&t;(17 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT2
mdefine_line|#define MPC83xx_IRQ_EXT2&t;(18 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT3
mdefine_line|#define MPC83xx_IRQ_EXT3&t;(19 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT4
mdefine_line|#define MPC83xx_IRQ_EXT4&t;(20 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT5
mdefine_line|#define MPC83xx_IRQ_EXT5&t;(21 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT6
mdefine_line|#define MPC83xx_IRQ_EXT6&t;(22 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT7
mdefine_line|#define MPC83xx_IRQ_EXT7&t;(23 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC1_TX
mdefine_line|#define MPC83xx_IRQ_TSEC1_TX&t;(32 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC1_RX
mdefine_line|#define MPC83xx_IRQ_TSEC1_RX&t;(33 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC1_ERROR
mdefine_line|#define MPC83xx_IRQ_TSEC1_ERROR&t;(34 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC2_TX
mdefine_line|#define MPC83xx_IRQ_TSEC2_TX&t;(35 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC2_RX
mdefine_line|#define MPC83xx_IRQ_TSEC2_RX&t;(36 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_TSEC2_ERROR
mdefine_line|#define MPC83xx_IRQ_TSEC2_ERROR&t;(37 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_USB2_DR
mdefine_line|#define MPC83xx_IRQ_USB2_DR&t;(38 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_USB2_MPH
mdefine_line|#define MPC83xx_IRQ_USB2_MPH&t;(39 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_EXT0
mdefine_line|#define MPC83xx_IRQ_EXT0&t;(48 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_RTC_SEC
mdefine_line|#define MPC83xx_IRQ_RTC_SEC&t;(64 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_PIT
mdefine_line|#define MPC83xx_IRQ_PIT&t;&t;(65 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_PCI1
mdefine_line|#define MPC83xx_IRQ_PCI1&t;(66 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_PCI2
mdefine_line|#define MPC83xx_IRQ_PCI2&t;(67 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_RTC_ALR
mdefine_line|#define MPC83xx_IRQ_RTC_ALR&t;(68 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_MU
mdefine_line|#define MPC83xx_IRQ_MU&t;&t;(69 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_SBA
mdefine_line|#define MPC83xx_IRQ_SBA&t;&t;(70 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_DMA
mdefine_line|#define MPC83xx_IRQ_DMA&t;&t;(71 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM4
mdefine_line|#define MPC83xx_IRQ_GTM4&t;(72 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM8
mdefine_line|#define MPC83xx_IRQ_GTM8&t;(73 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GPIO1
mdefine_line|#define MPC83xx_IRQ_GPIO1&t;(74 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GPIO2
mdefine_line|#define MPC83xx_IRQ_GPIO2&t;(75 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_DDR
mdefine_line|#define MPC83xx_IRQ_DDR&t;&t;(76 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_LBC
mdefine_line|#define MPC83xx_IRQ_LBC&t;&t;(77 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM2
mdefine_line|#define MPC83xx_IRQ_GTM2&t;(78 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM6
mdefine_line|#define MPC83xx_IRQ_GTM6&t;(79 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_PMC
mdefine_line|#define MPC83xx_IRQ_PMC&t;&t;(80 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM3
mdefine_line|#define MPC83xx_IRQ_GTM3&t;(84 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM7
mdefine_line|#define MPC83xx_IRQ_GTM7&t;(85 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM1
mdefine_line|#define MPC83xx_IRQ_GTM1&t;(90 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_IRQ_GTM5
mdefine_line|#define MPC83xx_IRQ_GTM5&t;(91 + MPC83xx_IPIC_IRQ_OFFSET)
DECL|macro|MPC83xx_CCSRBAR_SIZE
mdefine_line|#define MPC83xx_CCSRBAR_SIZE&t;(1024*1024)
multiline_comment|/* Let modules/drivers get at immrbar (physical) */
r_extern
id|phys_addr_t
id|immrbar
suffix:semicolon
DECL|enum|ppc_sys_devices
r_enum
id|ppc_sys_devices
(brace
DECL|enumerator|MPC83xx_TSEC1
id|MPC83xx_TSEC1
comma
DECL|enumerator|MPC83xx_TSEC2
id|MPC83xx_TSEC2
comma
DECL|enumerator|MPC83xx_IIC1
id|MPC83xx_IIC1
comma
DECL|enumerator|MPC83xx_IIC2
id|MPC83xx_IIC2
comma
DECL|enumerator|MPC83xx_DUART
id|MPC83xx_DUART
comma
DECL|enumerator|MPC83xx_SEC2
id|MPC83xx_SEC2
comma
DECL|enumerator|MPC83xx_USB2_DR
id|MPC83xx_USB2_DR
comma
DECL|enumerator|MPC83xx_USB2_MPH
id|MPC83xx_USB2_MPH
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_83xx */
macro_line|#endif /* __ASM_MPC83xx_H__ */
macro_line|#endif /* __KERNEL__ */
eof
