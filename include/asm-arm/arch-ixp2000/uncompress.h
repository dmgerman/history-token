multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp2000/uncompress.h&n; *&n; *&n; * Original Author: Naeem Afzal &lt;naeem.m.afzal@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2002 Intel Corp.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; */
macro_line|#include &lt;linux/serial_reg.h&gt;
DECL|macro|UART_BASE
mdefine_line|#define UART_BASE&t;0xc0030000
DECL|macro|PHYS
mdefine_line|#define PHYS(x)          ((volatile unsigned long *)(UART_BASE + x))
DECL|macro|UARTDR
mdefine_line|#define UARTDR          PHYS(0x00)      /* Transmit reg dlab=0 */
DECL|macro|UARTDLL
mdefine_line|#define UARTDLL         PHYS(0x00)      /* Divisor Latch reg dlab=1*/
DECL|macro|UARTDLM
mdefine_line|#define UARTDLM         PHYS(0x04)      /* Divisor Latch reg dlab=1*/
DECL|macro|UARTIER
mdefine_line|#define UARTIER         PHYS(0x04)      /* Interrupt enable reg */
DECL|macro|UARTFCR
mdefine_line|#define UARTFCR         PHYS(0x08)      /* FIFO control reg dlab =0*/
DECL|macro|UARTLCR
mdefine_line|#define UARTLCR         PHYS(0x0c)      /* Control reg */
DECL|macro|UARTSR
mdefine_line|#define UARTSR          PHYS(0x14)      /* Status reg */
DECL|function|putc
r_static
id|__inline__
r_void
id|putc
c_func
(paren
r_char
id|c
)paren
(brace
r_int
id|j
op_assign
l_int|0x1000
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|j
op_logical_and
op_logical_neg
(paren
op_star
id|UARTSR
op_amp
id|UART_LSR_THRE
)paren
)paren
suffix:semicolon
op_star
id|UARTDR
op_assign
id|c
suffix:semicolon
)brace
DECL|function|putstr
r_static
r_void
id|putstr
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_while
c_loop
(paren
op_star
id|s
)paren
(brace
id|putc
c_func
(paren
op_star
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|s
op_increment
suffix:semicolon
)brace
)brace
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
