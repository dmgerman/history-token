multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/serial.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   11-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * UART3 and UART4 are not supported yet&n; */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;&t;3
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;{ 0, 0, IO_BASE + UART0, IRQ_UART0, 0 }, &bslash;&n;&t;{ 0, 0, IO_BASE + UART1, IRQ_UART1, 0 }, &bslash;&n;&t;{ 0, 0, IO_BASE + UART2, IRQ_UART2, 0 }
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
