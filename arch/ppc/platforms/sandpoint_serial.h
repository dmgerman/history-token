multiline_comment|/*&n; * include/asm-ppc/sandpoint_serial.h&n; * &n; * Definitions for Motorola SPS Sandpoint Test Platform&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_SANDPOINT_SERIAL_H
DECL|macro|__ASMPPC_SANDPOINT_SERIAL_H
mdefine_line|#define __ASMPPC_SANDPOINT_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SANDPOINT_SERIAL_0
mdefine_line|#define SANDPOINT_SERIAL_0&t;&t;0xfe0003f8
DECL|macro|SANDPOINT_SERIAL_1
mdefine_line|#define SANDPOINT_SERIAL_1&t;&t;0xfe0002f8
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, SANDPOINT_SERIAL_0, 4, STD_COM_FLAGS, /* ttyS0 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SANDPOINT_SERIAL_0,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;  &bslash;&n;        { 0, BASE_BAUD, SANDPOINT_SERIAL_1, 3, STD_COM_FLAGS, /* ttyS1 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SANDPOINT_SERIAL_1,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASMPPC_SANDPOINT_SERIAL_H */
eof
