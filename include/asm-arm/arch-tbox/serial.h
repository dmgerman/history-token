multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/serial.h&n; *&n; * Copyright (c) 1996 Russell King.&n; * Copyright (c) 1998 Phil Blundell&n; *&n; * Changelog:&n; *  15-10-1996&t;RMK&t;Created&n; *  09-06-1998  PJB&t;tbox version&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/* UART CLK        PORT  IRQ     FLAGS        */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS &bslash;&n;&t;{ 0, BASE_BAUD, 0xffff4000 &gt;&gt; 2, 6, STD_COM_FLAGS }, /* ttyS0 */ &bslash;&n;&t;{ 0, BASE_BAUD, 0xffff5000 &gt;&gt; 2, 7, STD_COM_FLAGS }, /* ttyS1 */
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
