multiline_comment|/*&n; * arch/ppc/platforms/ev64260.h&n; * &n; * Definitions for Marvell/Galileo EV-64260-BP Evaluation Board.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * The GT64260 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; * We&squot;ll only use one PCI MEM window on each PCI bus.&n; */
macro_line|#ifndef __PPC_PLATFORMS_EV64260_H
DECL|macro|__PPC_PLATFORMS_EV64260_H
mdefine_line|#define __PPC_PLATFORMS_EV64260_H
DECL|macro|EV64260_BRIDGE_REG_BASE
mdefine_line|#define&t;EV64260_BRIDGE_REG_BASE&t;&t;0xf8000000
DECL|macro|EV64260_BRIDGE_REG_BASE_TO_TOP
mdefine_line|#define&t;EV64260_BRIDGE_REG_BASE_TO_TOP&t;0x08000000U
DECL|macro|EV64260_TODC_BASE
mdefine_line|#define&t;EV64260_TODC_BASE&t;&t;0xfc800000
DECL|macro|EV64260_TODC_LEN
mdefine_line|#define&t;EV64260_TODC_LEN&t;&t;0x00800000
DECL|macro|EV64260_TODC_END
mdefine_line|#define&t;EV64260_TODC_END&t;&t;(EV64260_TODC_BASE + &bslash;&n;&t;&t;&t;&t;&t; EV64260_TODC_LEN - 1)
DECL|macro|EV64260_UART_BASE
mdefine_line|#define&t;EV64260_UART_BASE&t;&t;0xfd000000
DECL|macro|EV64260_UART_LEN
mdefine_line|#define&t;EV64260_UART_LEN&t;&t;0x00800000
DECL|macro|EV64260_UART_END
mdefine_line|#define&t;EV64260_UART_END&t;&t;(EV64260_UART_BASE + &bslash;&n;&t;&t;&t;&t;&t; EV64260_UART_LEN - 1)
multiline_comment|/* Serial driver setup.  */
DECL|macro|EV64260_SERIAL_0
mdefine_line|#define EV64260_SERIAL_0&t;&t;(EV64260_UART_BASE + 0x20)
DECL|macro|EV64260_SERIAL_1
mdefine_line|#define EV64260_SERIAL_1&t;&t;EV64260_UART_BASE
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 3686400 / 16 )
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
macro_line|#if&t;!defined(CONFIG_GT64260_CONSOLE)
multiline_comment|/* Required for bootloader&squot;s ns16550.c code */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &t;&t;&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, EV64260_SERIAL_0, 85, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;iomem_base: (u8 *)EV64260_SERIAL_0,&t;&t;&t;&t;&bslash;&n;&t;iomem_reg_shift: 2,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#else
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS
macro_line|#endif
macro_line|#endif /* __PPC_PLATFORMS_EV64260_H */
eof
