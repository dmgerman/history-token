multiline_comment|/*&n; * arch/ppc/platforms/pal4_serial.h&n; * &n; * Definitions for SBS PalomarIV serial support &n; *&n; * Author: Dan Cox&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_PAL4_SERIAL_H
DECL|macro|__PPC_PAL4_SERIAL_H
mdefine_line|#define __PPC_PAL4_SERIAL_H
DECL|macro|CPC700_SERIAL_1
mdefine_line|#define CPC700_SERIAL_1       0xff600300
DECL|macro|CPC700_SERIAL_2
mdefine_line|#define CPC700_SERIAL_2       0xff600400
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE     2
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD         (33333333 / 4 / 16)
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF)
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;      {0, BASE_BAUD, CPC700_SERIAL_1, 3, STD_COM_FLAGS, &bslash;&n;       iomem_base: (unsigned char *) CPC700_SERIAL_1, &bslash;&n;       io_type: SERIAL_IO_MEM},   /* ttyS0 */ &bslash;&n;      {0, BASE_BAUD, CPC700_SERIAL_2, 4, STD_COM_FLAGS, &bslash;&n;       iomem_base: (unsigned char *) CPC700_SERIAL_2, &bslash;&n;       io_type: SERIAL_IO_MEM}
macro_line|#endif
eof
