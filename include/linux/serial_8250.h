multiline_comment|/*&n; *  linux/include/linux/serial_8250.h&n; *&n; *  Copyright (C) 2004 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_SERIAL_8250_H
DECL|macro|_LINUX_SERIAL_8250_H
mdefine_line|#define _LINUX_SERIAL_8250_H
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/device.h&gt;
DECL|struct|plat_serial8250_port
r_struct
id|plat_serial8250_port
(brace
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
multiline_comment|/* io base address */
DECL|member|membase
r_void
id|__iomem
op_star
id|membase
suffix:semicolon
multiline_comment|/* ioremap cookie or NULL */
DECL|member|mapbase
r_int
r_int
id|mapbase
suffix:semicolon
multiline_comment|/* resource base */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt number */
DECL|member|uartclk
r_int
r_int
id|uartclk
suffix:semicolon
multiline_comment|/* UART clock rate */
DECL|member|regshift
r_int
r_char
id|regshift
suffix:semicolon
multiline_comment|/* register shift */
DECL|member|iotype
r_int
r_char
id|iotype
suffix:semicolon
multiline_comment|/* UPIO_* */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* UPF_* flags */
)brace
suffix:semicolon
macro_line|#endif
eof
