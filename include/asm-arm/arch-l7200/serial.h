multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/serial.h&n; *&n; * Copyright (c) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *  03-20-2000  SJH     Created&n; *  03-26-2000  SJH     Added flags for serial ports&n; *  03-27-2000  SJH     Corrected BASE_BAUD value&n; *  04-14-2000  RS      Made register addr dependent on IO_BASE&n; *  05-03-2000  SJH     Complete rewrite&n; *  05-09-2000&t;SJH&t;Stripped out architecture specific serial stuff&n; *                      and placed it in a separate file&n; *  07-28-2000&t;SJH&t;Moved base baud rate variable&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 3.6864 MHz clock for your UART.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;3686400
multiline_comment|/*&n; * Standard COM flags&n; */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE 2
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;/* MAGIC UART CLK   PORT       IRQ     FLAGS */&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, UART1_BASE, IRQ_UART_1, STD_COM_FLAGS },  /* ttyLU0 */ &bslash;&n;&t;{ 0, BASE_BAUD, UART2_BASE, IRQ_UART_2, STD_COM_FLAGS },  /* ttyLU1 */ &bslash;&n;
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
