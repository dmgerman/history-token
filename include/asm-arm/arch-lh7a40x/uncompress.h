multiline_comment|/* include/asm-arm/arch-lh7a40x/uncompress.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;asm/arch/registers.h&gt;
macro_line|#ifndef UART_R_DATA
DECL|macro|UART_R_DATA
macro_line|# define UART_R_DATA&t;(0x00)
macro_line|#endif
macro_line|#ifndef UART_R_STATUS
DECL|macro|UART_R_STATUS
macro_line|# define UART_R_STATUS&t;(0x10)
macro_line|#endif
DECL|macro|nTxRdy
mdefine_line|#define nTxRdy  &t;(0x20)&t;/* Not TxReady (literally Tx FIFO full) */
multiline_comment|/* Access UART with physical addresses before MMU is setup */
DECL|macro|UART_STATUS
mdefine_line|#define UART_STATUS (*(volatile unsigned long*) (UART2_PHYS + UART_R_STATUS))
DECL|macro|UART_DATA
mdefine_line|#define UART_DATA   (*(volatile unsigned long*) (UART2_PHYS + UART_R_DATA))
DECL|function|putc
r_static
id|__inline__
r_void
id|putc
(paren
r_char
id|ch
)paren
(brace
r_while
c_loop
(paren
id|UART_STATUS
op_amp
id|nTxRdy
)paren
suffix:semicolon
id|UART_DATA
op_assign
id|ch
suffix:semicolon
)brace
DECL|function|putstr
r_static
r_void
id|putstr
(paren
r_const
r_char
op_star
id|sz
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|sz
suffix:semicolon
op_increment
id|sz
)paren
(brace
id|putc
(paren
op_star
id|sz
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sz
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|putc
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* NULL functions; we don&squot;t presently need them */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
