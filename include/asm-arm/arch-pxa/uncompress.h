multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/uncompress.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|FFUART
mdefine_line|#define FFUART&t;&t;((volatile unsigned long *)0x40100000)
DECL|macro|BTUART
mdefine_line|#define BTUART&t;&t;((volatile unsigned long *)0x40200000)
DECL|macro|STUART
mdefine_line|#define STUART&t;&t;((volatile unsigned long *)0x40700000)
DECL|macro|UART
mdefine_line|#define UART&t;&t;FFUART
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
r_while
c_loop
(paren
op_logical_neg
(paren
id|UART
(braket
l_int|5
)braket
op_amp
l_int|0x20
)paren
)paren
suffix:semicolon
id|UART
(braket
l_int|0
)braket
op_assign
id|c
suffix:semicolon
)brace
multiline_comment|/*&n; * This does not append a newline&n; */
DECL|function|puts
r_static
r_void
id|puts
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
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
