multiline_comment|/*&n; * arch/ppc/platforms/ebony.h&n; *&n; * Ebony board definitions&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_EBONY_H__
DECL|macro|__ASM_EBONY_H__
mdefine_line|#define __ASM_EBONY_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/4xx/ibm440gp.h&gt;
multiline_comment|/* F/W TLB mapping used in bootloader glue to reset EMAC */
DECL|macro|PPC44x_EMAC0_MR0
mdefine_line|#define PPC44x_EMAC0_MR0&t;0xE0000800
multiline_comment|/* Where to find the MAC info */
DECL|macro|EBONY_OPENBIOS_MAC_BASE
mdefine_line|#define EBONY_OPENBIOS_MAC_BASE   0xfffffe0c
DECL|macro|EBONY_OPENBIOS_MAC_OFFSET
mdefine_line|#define EBONY_OPENBIOS_MAC_OFFSET 0x0c
multiline_comment|/* Default clock rates for Rev. B and Rev. C silicon */
DECL|macro|EBONY_440GP_RB_SYSCLK
mdefine_line|#define EBONY_440GP_RB_SYSCLK&t;33000000
DECL|macro|EBONY_440GP_RC_SYSCLK
mdefine_line|#define EBONY_440GP_RC_SYSCLK&t;400000000
multiline_comment|/* RTC/NVRAM location */
DECL|macro|EBONY_RTC_ADDR
mdefine_line|#define EBONY_RTC_ADDR&t;&t;0x0000000148000000ULL
DECL|macro|EBONY_RTC_SIZE
mdefine_line|#define EBONY_RTC_SIZE&t;&t;0x2000
multiline_comment|/* Flash */
DECL|macro|EBONY_FPGA_ADDR
mdefine_line|#define EBONY_FPGA_ADDR&t;&t;0x0000000148300000ULL
DECL|macro|EBONY_BOOT_SMALL_FLASH
mdefine_line|#define EBONY_BOOT_SMALL_FLASH(x)&t;(x &amp; 0x20)
DECL|macro|EBONY_ONBRD_FLASH_EN
mdefine_line|#define EBONY_ONBRD_FLASH_EN(x)&t;&t;(x &amp; 0x02)
DECL|macro|EBONY_FLASH_SEL
mdefine_line|#define EBONY_FLASH_SEL(x)&t;&t;(x &amp; 0x01)
DECL|macro|EBONY_SMALL_FLASH_LOW1
mdefine_line|#define EBONY_SMALL_FLASH_LOW1&t;0x00000001ff800000ULL
DECL|macro|EBONY_SMALL_FLASH_LOW2
mdefine_line|#define EBONY_SMALL_FLASH_LOW2&t;0x00000001ff880000ULL
DECL|macro|EBONY_SMALL_FLASH_HIGH1
mdefine_line|#define EBONY_SMALL_FLASH_HIGH1&t;0x00000001fff00000ULL
DECL|macro|EBONY_SMALL_FLASH_HIGH2
mdefine_line|#define EBONY_SMALL_FLASH_HIGH2&t;0x00000001fff80000ULL
DECL|macro|EBONY_SMALL_FLASH_SIZE
mdefine_line|#define EBONY_SMALL_FLASH_SIZE&t;0x80000
DECL|macro|EBONY_LARGE_FLASH_LOW
mdefine_line|#define EBONY_LARGE_FLASH_LOW&t;0x00000001ff800000ULL
DECL|macro|EBONY_LARGE_FLASH_HIGH
mdefine_line|#define EBONY_LARGE_FLASH_HIGH&t;0x00000001ffc00000ULL
DECL|macro|EBONY_LARGE_FLASH_SIZE
mdefine_line|#define EBONY_LARGE_FLASH_SIZE&t;0x400000
DECL|macro|EBONY_SMALL_FLASH_BASE
mdefine_line|#define EBONY_SMALL_FLASH_BASE&t;0x00000001fff80000ULL
DECL|macro|EBONY_LARGE_FLASH_BASE
mdefine_line|#define EBONY_LARGE_FLASH_BASE&t;0x00000001ff800000ULL
multiline_comment|/*&n; * Serial port defines&n; */
multiline_comment|/* OpenBIOS defined UART mappings, used before early_serial_setup */
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;(u8 *) 0xE0000200
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;(u8 *) 0xE0000300
multiline_comment|/* external Epson SG-615P */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;691200
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base: UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
multiline_comment|/* PCI support */
DECL|macro|EBONY_PCI_LOWER_IO
mdefine_line|#define EBONY_PCI_LOWER_IO&t;0x00000000
DECL|macro|EBONY_PCI_UPPER_IO
mdefine_line|#define EBONY_PCI_UPPER_IO&t;0x0000ffff
DECL|macro|EBONY_PCI_LOWER_MEM
mdefine_line|#define EBONY_PCI_LOWER_MEM&t;0x80002000
DECL|macro|EBONY_PCI_UPPER_MEM
mdefine_line|#define EBONY_PCI_UPPER_MEM&t;0xffffefff
DECL|macro|EBONY_PCI_CFGREGS_BASE
mdefine_line|#define EBONY_PCI_CFGREGS_BASE&t;0x000000020ec00000
DECL|macro|EBONY_PCI_CFGA_PLB32
mdefine_line|#define EBONY_PCI_CFGA_PLB32&t;0x0ec00000
DECL|macro|EBONY_PCI_CFGD_PLB32
mdefine_line|#define EBONY_PCI_CFGD_PLB32&t;0x0ec00004
DECL|macro|EBONY_PCI_IO_BASE
mdefine_line|#define EBONY_PCI_IO_BASE&t;0x0000000208000000ULL
DECL|macro|EBONY_PCI_IO_SIZE
mdefine_line|#define EBONY_PCI_IO_SIZE&t;0x00010000
DECL|macro|EBONY_PCI_MEM_OFFSET
mdefine_line|#define EBONY_PCI_MEM_OFFSET&t;0x00000000
macro_line|#endif&t;&t;&t;&t;/* __ASM_EBONY_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
