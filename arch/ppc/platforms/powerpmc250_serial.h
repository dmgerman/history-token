multiline_comment|/*&n; * include/asm-ppc/platforms/powerpmc250_serial.h&n; * &n; * Motorola PrPMC750 serial support&n; *&n; * Author: Troy Benjegerdes &lt;tbenjegerdes@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASMPPC_POWERPMC250_SERIAL_H
DECL|macro|__ASMPPC_POWERPMC250_SERIAL_H
mdefine_line|#define __ASMPPC_POWERPMC250_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/powerpmc250.h&gt;
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  1
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (POWERPMC250_BASE_BAUD / 16)
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
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;{ 0, BASE_BAUD, POWERPMC250_SERIAL, POWERPMC250_SERIAL_IRQ, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;&t;iomem_base: (u8 *)POWERPMC250_SERIAL,&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM }
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
