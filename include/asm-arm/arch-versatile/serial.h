multiline_comment|/*&n; *  linux/include/asm-arm/arch-versatile/serial.h&n; *&n; *  Copyright (C) 2003 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 14.7456 MHz clock UART.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 115200
multiline_comment|/* UART CLK        PORT  IRQ     FLAGS        */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS &bslash;&n;&t;{ 0, BASE_BAUD, 0, 0, ASYNC_SKIP_TEST },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, 0, ASYNC_SKIP_TEST },&t;/* ttyS1 */     &bslash;&n;&t;{ 0, BASE_BAUD, 0, 0, ASYNC_SKIP_TEST },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, 0, ASYNC_SKIP_TEST },&t;/* ttyS3 */
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
macro_line|#endif
eof
