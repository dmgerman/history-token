multiline_comment|/* serial-regs.h: serial port registers&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SERIAL_REGS_H
DECL|macro|_ASM_SERIAL_REGS_H
mdefine_line|#define _ASM_SERIAL_REGS_H
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/irc-regs.h&gt;
DECL|macro|SERIAL_ICLK
mdefine_line|#define SERIAL_ICLK&t;33333333&t;/* the target serial input clock */
DECL|macro|UART0_BASE
mdefine_line|#define UART0_BASE&t;0xfeff9c00
DECL|macro|UART1_BASE
mdefine_line|#define UART1_BASE&t;0xfeff9c40
DECL|macro|__get_UART0
mdefine_line|#define __get_UART0(R) ({ __reg(UART0_BASE + (R) * 8) &gt;&gt; 24; })
DECL|macro|__get_UART1
mdefine_line|#define __get_UART1(R) ({ __reg(UART1_BASE + (R) * 8) &gt;&gt; 24; })
DECL|macro|__set_UART0
mdefine_line|#define __set_UART0(R,V) do { __reg(UART0_BASE + (R) * 8) = (V) &lt;&lt; 24; } while(0)
DECL|macro|__set_UART1
mdefine_line|#define __set_UART1(R,V) do { __reg(UART1_BASE + (R) * 8) = (V) &lt;&lt; 24; } while(0)
DECL|macro|__get_UART0_LSR
mdefine_line|#define __get_UART0_LSR() ({ __get_UART0(UART_LSR); })
DECL|macro|__get_UART1_LSR
mdefine_line|#define __get_UART1_LSR() ({ __get_UART1(UART_LSR); })
DECL|macro|__set_UART0_IER
mdefine_line|#define __set_UART0_IER(V) __set_UART0(UART_IER,(V))
DECL|macro|__set_UART1_IER
mdefine_line|#define __set_UART1_IER(V) __set_UART1(UART_IER,(V))
multiline_comment|/* serial prescaler select register */
DECL|macro|__get_UCPSR
mdefine_line|#define __get_UCPSR()&t;({ *(volatile unsigned long *)(0xfeff9c90); })
DECL|macro|__set_UCPSR
mdefine_line|#define __set_UCPSR(V)&t;do { *(volatile unsigned long *)(0xfeff9c90) = (V); } while(0)
DECL|macro|UCPSR_SELECT0
mdefine_line|#define UCPSR_SELECT0&t;0x07000000
DECL|macro|UCPSR_SELECT1
mdefine_line|#define UCPSR_SELECT1&t;0x38000000
multiline_comment|/* serial prescaler base value register */
DECL|macro|__get_UCPVR
mdefine_line|#define __get_UCPVR()&t;({ *(volatile unsigned long *)(0xfeff9c98); mb(); })
DECL|macro|__set_UCPVR
mdefine_line|#define __set_UCPVR(V)&t;do { *(volatile unsigned long *)(0xfeff9c98) = (V) &lt;&lt; 24; mb(); } while(0)
macro_line|#endif /* _ASM_SERIAL_REGS_H */
eof
