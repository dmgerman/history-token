multiline_comment|/*&n; *  linux/include/asm-arm/serial.h&n; *&n; *  Copyright (C) 1996 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   15-10-1996&t;RMK&t;Created&n; */
macro_line|#ifndef __ASM_SERIAL_H
DECL|macro|__ASM_SERIAL_H
mdefine_line|#define __ASM_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE   16
macro_line|#if defined(CONFIG_ARCH_A5K)
multiline_comment|/* UART CLK        PORT  IRQ     FLAGS        */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS                                           &bslash;&n;        { 0, BASE_BAUD, 0x3F8, 10, STD_COM_FLAGS },     /* ttyS0 */     &bslash;&n;        { 0, BASE_BAUD, 0x2F8, 10, STD_COM_FLAGS },     /* ttyS1 */
macro_line|#else
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS                                           &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS0 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS1 */
macro_line|#endif
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS2 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS3 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS4 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS5 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS6 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS7 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS8 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS9 */     &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS10 */    &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS11 */    &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS12 */    &bslash;&n;        { 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },     /* ttyS13 */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&bslash;&n;&t;STD_SERIAL_PORT_DEFNS&t;&t;&bslash;&n;&t;EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
