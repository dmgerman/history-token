multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc800_serial.h&n; * &n; * Definitions for Motorola MCG PRPMC800 cPCI board support&n; *&n; * Author: Dale Farnsworth&t;dale.farnsworth@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_PRPMC800_SERIAL_H
DECL|macro|__ASMPPC_PRPMC800_SERIAL_H
mdefine_line|#define __ASMPPC_PRPMC800_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/prpmc800.h&gt;
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (PRPMC800_BASE_BAUD / 16)
macro_line|#ifndef SERIAL_MAGIC_KEY
DECL|macro|kernel_debugger
mdefine_line|#define kernel_debugger ppc_kernel_debug
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
multiline_comment|/* UARTS are at IRQ 16 */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, PRPMC800_SERIAL_1, 16, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;&t;iomem_base: (unsigned char *)PRPMC800_SERIAL_1,&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASMPPC_PRPMC800_SERIAL_H */
eof
