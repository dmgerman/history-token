multiline_comment|/* gdb-io.h: FR403 GDB I/O port defs&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _GDB_IO_H
DECL|macro|_GDB_IO_H
mdefine_line|#define _GDB_IO_H
macro_line|#include &lt;asm/serial-regs.h&gt;
DECL|macro|UART_RX
macro_line|#undef UART_RX
DECL|macro|UART_TX
macro_line|#undef UART_TX
DECL|macro|UART_DLL
macro_line|#undef UART_DLL
DECL|macro|UART_DLM
macro_line|#undef UART_DLM
DECL|macro|UART_IER
macro_line|#undef UART_IER
DECL|macro|UART_IIR
macro_line|#undef UART_IIR
DECL|macro|UART_FCR
macro_line|#undef UART_FCR
DECL|macro|UART_LCR
macro_line|#undef UART_LCR
DECL|macro|UART_MCR
macro_line|#undef UART_MCR
DECL|macro|UART_LSR
macro_line|#undef UART_LSR
DECL|macro|UART_MSR
macro_line|#undef UART_MSR
DECL|macro|UART_SCR
macro_line|#undef UART_SCR
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0*8&t;/* In:  Receive buffer (DLAB=0) */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;0*8&t;/* Out: Transmit buffer (DLAB=0) */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0*8&t;/* Out: Divisor Latch Low (DLAB=1) */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;1*8&t;/* Out: Divisor Latch High (DLAB=1) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;1*8&t;/* Out: Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;2*8&t;/* In:  Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;2*8&t;/* Out: FIFO Control Register */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;3*8&t;/* Out: Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;4*8&t;/* Out: Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;5*8&t;/* In:  Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;6*8&t;/* In:  Modem Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;7*8&t;/* I/O: Scratch Register */
DECL|macro|UART_LCR_DLAB
mdefine_line|#define UART_LCR_DLAB&t;0x80&t;/* Divisor latch access bit */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;0x40&t;/* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;0x20&t;/* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;0x10&t;/* Even parity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;0x08&t;/* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;0x04&t;/* Stop bits: 0=1 stop bit, 1= 2 stop bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5  0x00&t;/* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6  0x01&t;/* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7  0x02&t;/* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8  0x03&t;/* Wordlength: 8 bits */
macro_line|#endif /* _GDB_IO_H */
eof
