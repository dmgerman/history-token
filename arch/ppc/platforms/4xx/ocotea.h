multiline_comment|/*&n; * arch/ppc/platforms/ocotea.h&n; *&n; * Ocotea board definitions&n; *&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * Copyright 2003-2005 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_OCOTEA_H__
DECL|macro|__ASM_OCOTEA_H__
mdefine_line|#define __ASM_OCOTEA_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/4xx/ibm440gx.h&gt;
multiline_comment|/* F/W TLB mapping used in bootloader glue to reset EMAC */
DECL|macro|PPC44x_EMAC0_MR0
mdefine_line|#define PPC44x_EMAC0_MR0&t;0xe0000800
multiline_comment|/* Location of MAC addresses in PIBS image */
DECL|macro|PIBS_FLASH_BASE
mdefine_line|#define PIBS_FLASH_BASE&t;&t;0xfff00000
DECL|macro|PIBS_MAC_BASE
mdefine_line|#define PIBS_MAC_BASE&t;&t;(PIBS_FLASH_BASE+0xb0500)
DECL|macro|PIBS_MAC_SIZE
mdefine_line|#define PIBS_MAC_SIZE&t;&t;0x200
DECL|macro|PIBS_MAC_OFFSET
mdefine_line|#define PIBS_MAC_OFFSET&t;&t;0x100
multiline_comment|/* External timer clock frequency */
DECL|macro|OCOTEA_TMR_CLK
mdefine_line|#define OCOTEA_TMR_CLK&t;25000000
multiline_comment|/* RTC/NVRAM location */
DECL|macro|OCOTEA_RTC_ADDR
mdefine_line|#define OCOTEA_RTC_ADDR&t;&t;0x0000000148000000ULL
DECL|macro|OCOTEA_RTC_SIZE
mdefine_line|#define OCOTEA_RTC_SIZE&t;&t;0x2000
multiline_comment|/* Flash */
DECL|macro|OCOTEA_FPGA_REG_0
mdefine_line|#define OCOTEA_FPGA_REG_0&t;&t;0x0000000148300000ULL
DECL|macro|OCOTEA_BOOT_LARGE_FLASH
mdefine_line|#define OCOTEA_BOOT_LARGE_FLASH(x)&t;(x &amp; 0x40)
DECL|macro|OCOTEA_SMALL_FLASH_LOW
mdefine_line|#define OCOTEA_SMALL_FLASH_LOW&t;&t;0x00000001ff900000ULL
DECL|macro|OCOTEA_SMALL_FLASH_HIGH
mdefine_line|#define OCOTEA_SMALL_FLASH_HIGH&t;&t;0x00000001fff00000ULL
DECL|macro|OCOTEA_SMALL_FLASH_SIZE
mdefine_line|#define OCOTEA_SMALL_FLASH_SIZE&t;&t;0x100000
DECL|macro|OCOTEA_LARGE_FLASH_LOW
mdefine_line|#define OCOTEA_LARGE_FLASH_LOW&t;&t;0x00000001ff800000ULL
DECL|macro|OCOTEA_LARGE_FLASH_HIGH
mdefine_line|#define OCOTEA_LARGE_FLASH_HIGH&t;&t;0x00000001ffc00000ULL
DECL|macro|OCOTEA_LARGE_FLASH_SIZE
mdefine_line|#define OCOTEA_LARGE_FLASH_SIZE&t;&t;0x400000
multiline_comment|/* FPGA_REG_3 (Ethernet Groups) */
DECL|macro|OCOTEA_FPGA_REG_3
mdefine_line|#define OCOTEA_FPGA_REG_3&t;&t;0x0000000148300003ULL
multiline_comment|/*&n; * Serial port defines&n; */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
multiline_comment|/* OpenBIOS defined UART mappings, used before early_serial_setup */
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;(u8 *) 0xE0000200
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;(u8 *) 0xE0000300
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;11059200/16
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base: UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
multiline_comment|/* PCI support */
DECL|macro|OCOTEA_PCI_LOWER_IO
mdefine_line|#define OCOTEA_PCI_LOWER_IO&t;0x00000000
DECL|macro|OCOTEA_PCI_UPPER_IO
mdefine_line|#define OCOTEA_PCI_UPPER_IO&t;0x0000ffff
DECL|macro|OCOTEA_PCI_LOWER_MEM
mdefine_line|#define OCOTEA_PCI_LOWER_MEM&t;0x80000000
DECL|macro|OCOTEA_PCI_UPPER_MEM
mdefine_line|#define OCOTEA_PCI_UPPER_MEM&t;0xffffefff
DECL|macro|OCOTEA_PCI_CFGREGS_BASE
mdefine_line|#define OCOTEA_PCI_CFGREGS_BASE&t;0x000000020ec00000ULL
DECL|macro|OCOTEA_PCI_CFGA_PLB32
mdefine_line|#define OCOTEA_PCI_CFGA_PLB32&t;0x0ec00000
DECL|macro|OCOTEA_PCI_CFGD_PLB32
mdefine_line|#define OCOTEA_PCI_CFGD_PLB32&t;0x0ec00004
DECL|macro|OCOTEA_PCI_IO_BASE
mdefine_line|#define OCOTEA_PCI_IO_BASE&t;0x0000000208000000ULL
DECL|macro|OCOTEA_PCI_IO_SIZE
mdefine_line|#define OCOTEA_PCI_IO_SIZE&t;0x00010000
DECL|macro|OCOTEA_PCI_MEM_OFFSET
mdefine_line|#define OCOTEA_PCI_MEM_OFFSET&t;0x00000000
macro_line|#endif&t;&t;&t;&t;/* __ASM_OCOTEA_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
