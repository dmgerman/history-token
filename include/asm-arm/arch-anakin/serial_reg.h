multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/serial_reg.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   09-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef ASM_ARCH_SERIAL_REG_H
DECL|macro|ASM_ARCH_SERIAL_REG_H
mdefine_line|#define ASM_ARCH_SERIAL_REG_H
multiline_comment|/*&n; * Serial registers (other than tx/rx)&n; */
multiline_comment|/*&n; * [UARTx + 0x10]&n; */
DECL|macro|RXRELEASE
mdefine_line|#define RXRELEASE&t;&t;(1 &lt;&lt; 0)
DECL|macro|TXEMPTY
mdefine_line|#define TXEMPTY&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|CTS
mdefine_line|#define CTS&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|PRESCALER
mdefine_line|#define PRESCALER&t;&t;(31 &lt;&lt; 3)
DECL|macro|SETBAUD
mdefine_line|#define SETBAUD(baud)&t;&t;((230400 / (baud) - 1) &lt;&lt; 3)
DECL|macro|GETBAUD
mdefine_line|#define GETBAUD(prescaler)&t;(230400 / (((prescaler) &gt;&gt; 3) + 1))
multiline_comment|/*&n; * [UARTx + 0x18]&n; */
DECL|macro|IRQENABLE
mdefine_line|#define IRQENABLE&t;&t;(1 &lt;&lt; 0)
DECL|macro|SENDREQUEST
mdefine_line|#define SENDREQUEST&t;&t;(1 &lt;&lt; 1)
DECL|macro|RTS
mdefine_line|#define RTS&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|DTR
mdefine_line|#define DTR&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|DCD
mdefine_line|#define DCD&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|BLOCKRX
mdefine_line|#define BLOCKRX&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|PARITY
mdefine_line|#define PARITY&t;&t;&t;(3 &lt;&lt; 6)
DECL|macro|SETPARITY
mdefine_line|#define SETPARITY(parity)&t;((parity) &lt;&lt; 6)
DECL|macro|GETPARITY
mdefine_line|#define GETPARITY(parity)&t;((parity) &gt;&gt; 6)
DECL|macro|NONEPARITY
mdefine_line|#define NONEPARITY              (0)
DECL|macro|ODDPARITY
mdefine_line|#define ODDPARITY               (1)
DECL|macro|EVENPARITY
mdefine_line|#define EVENPARITY              (2)
multiline_comment|/*&n; * [UARTx + 0x1c]&n; */
DECL|macro|TX
mdefine_line|#define TX&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|RX
mdefine_line|#define RX&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|OVERRUN
mdefine_line|#define OVERRUN&t;&t;&t;(1 &lt;&lt; 2)
multiline_comment|/*&n; * [UARTx + 0x20]&n; */
DECL|macro|SETBREAK
mdefine_line|#define SETBREAK&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * Software interrupt register&n; */
DECL|macro|TXENABLE
mdefine_line|#define TXENABLE&t;&t;(1 &lt;&lt; 0)
macro_line|#endif 
eof
