multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/uncompress.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
DECL|macro|AMBA_UART_DR
mdefine_line|#define AMBA_UART_DR&t;(*(volatile unsigned char *)0x16000000)
DECL|macro|AMBA_UART_LCRH
mdefine_line|#define AMBA_UART_LCRH&t;(*(volatile unsigned char *)0x16000008)
DECL|macro|AMBA_UART_LCRM
mdefine_line|#define AMBA_UART_LCRM&t;(*(volatile unsigned char *)0x1600000c)
DECL|macro|AMBA_UART_LCRL
mdefine_line|#define AMBA_UART_LCRL&t;(*(volatile unsigned char *)0x16000010)
DECL|macro|AMBA_UART_CR
mdefine_line|#define AMBA_UART_CR&t;(*(volatile unsigned char *)0x16000014)
DECL|macro|AMBA_UART_FR
mdefine_line|#define AMBA_UART_FR&t;(*(volatile unsigned char *)0x16000018)
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
r_while
c_loop
(paren
id|AMBA_UART_FR
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|AMBA_UART_DR
op_assign
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
id|AMBA_UART_FR
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|AMBA_UART_DR
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
id|s
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|AMBA_UART_FR
op_amp
(paren
l_int|1
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
