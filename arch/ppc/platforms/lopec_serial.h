multiline_comment|/*&n; * include/asm-ppc/lopec_serial.h&n; * &n; * Definitions for Motorola LoPEC board.&n; *&n; * Author: Dan Cox&n; *         danc@mvista.com (or, alternately, source@mvista.com)&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __H_LOPEC_SERIAL
DECL|macro|__H_LOPEC_SERIAL
mdefine_line|#define __H_LOPEC_SERIAL
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 3
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;         { 0, BASE_BAUD, 0xffe10000, 29, STD_COM_FLAGS, &bslash;&n;           iomem_base: (u8 *) 0xffe10000, &bslash;&n;           io_type: SERIAL_IO_MEM }, &bslash;&n;         { 0, BASE_BAUD, 0xffe11000, 20, STD_COM_FLAGS, &bslash;&n;           iomem_base: (u8 *) 0xffe11000, &bslash;&n;           io_type: SERIAL_IO_MEM }, &bslash;&n;         { 0, BASE_BAUD, 0xffe12000, 21, STD_COM_FLAGS, &bslash;&n;           iomem_base: (u8 *) 0xffe12000, &bslash;&n;           io_type: SERIAL_IO_MEM }
macro_line|#endif
eof
