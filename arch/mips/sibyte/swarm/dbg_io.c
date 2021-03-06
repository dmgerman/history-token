multiline_comment|/*&n; * kgdb debug routines for SiByte boards.&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
multiline_comment|/* -------------------- BEGINNING OF CONFIG --------------------- */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_uart.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * We use the second serial port for kgdb traffic.&n; * &t;115200, 8, N, 1.&n; */
DECL|macro|BAUD_RATE
mdefine_line|#define&t;BAUD_RATE&t;&t;115200
DECL|macro|CLK_DIVISOR
mdefine_line|#define&t;CLK_DIVISOR&t;&t;V_DUART_BAUD_RATE(BAUD_RATE)
DECL|macro|DATA_BITS
mdefine_line|#define&t;DATA_BITS&t;&t;V_DUART_BITS_PER_CHAR_8&t;&t;/* or 7    */
DECL|macro|PARITY
mdefine_line|#define&t;PARITY&t;&t;&t;V_DUART_PARITY_MODE_NONE&t;/* or even */
DECL|macro|STOP_BITS
mdefine_line|#define&t;STOP_BITS&t;&t;M_DUART_STOP_BIT_LEN_1&t;&t;/* or 2    */
DECL|variable|duart_initialized
r_static
r_int
id|duart_initialized
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0: need to be init&squot;ed by kgdb */
multiline_comment|/* -------------------- END OF CONFIG --------------------- */
r_extern
r_int
id|kgdb_port
suffix:semicolon
DECL|macro|duart_out
mdefine_line|#define&t;duart_out(reg, val)&t;csr_out32(val, IOADDR(A_DUART_CHANREG(kgdb_port,reg)))
DECL|macro|duart_in
mdefine_line|#define duart_in(reg)&t;&t;csr_in32(IOADDR(A_DUART_CHANREG(kgdb_port,reg)))
r_void
id|putDebugChar
c_func
(paren
r_int
r_char
id|c
)paren
suffix:semicolon
r_int
r_char
id|getDebugChar
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
DECL|function|duart_init
id|duart_init
c_func
(paren
r_int
id|clk_divisor
comma
r_int
id|data
comma
r_int
id|parity
comma
r_int
id|stop
)paren
(brace
id|duart_out
c_func
(paren
id|R_DUART_MODE_REG_1
comma
id|data
op_or
id|parity
)paren
suffix:semicolon
id|duart_out
c_func
(paren
id|R_DUART_MODE_REG_2
comma
id|stop
)paren
suffix:semicolon
id|duart_out
c_func
(paren
id|R_DUART_CLK_SEL
comma
id|clk_divisor
)paren
suffix:semicolon
id|duart_out
c_func
(paren
id|R_DUART_CMD
comma
id|M_DUART_RX_EN
op_or
id|M_DUART_TX_EN
)paren
suffix:semicolon
multiline_comment|/* enable rx and tx */
)brace
r_void
DECL|function|putDebugChar
id|putDebugChar
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|duart_initialized
)paren
(brace
id|duart_initialized
op_assign
l_int|1
suffix:semicolon
id|duart_init
c_func
(paren
id|CLK_DIVISOR
comma
id|DATA_BITS
comma
id|PARITY
comma
id|STOP_BITS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|duart_in
c_func
(paren
id|R_DUART_STATUS
)paren
op_amp
id|M_DUART_TX_RDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|duart_out
c_func
(paren
id|R_DUART_TX_HOLD
comma
id|c
)paren
suffix:semicolon
)brace
r_int
r_char
DECL|function|getDebugChar
id|getDebugChar
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|duart_initialized
)paren
(brace
id|duart_initialized
op_assign
l_int|1
suffix:semicolon
id|duart_init
c_func
(paren
id|CLK_DIVISOR
comma
id|DATA_BITS
comma
id|PARITY
comma
id|STOP_BITS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|duart_in
c_func
(paren
id|R_DUART_STATUS
)paren
op_amp
id|M_DUART_RX_RDY
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|duart_in
c_func
(paren
id|R_DUART_RX_HOLD
)paren
suffix:semicolon
)brace
eof
