multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Putting things on the screen/serial line using YAMONs facilities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_MIPS_ATLAS
macro_line|#include &lt;asm/mips-boards/atlas.h&gt;
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
DECL|macro|PORT
mdefine_line|#define PORT(offset) (ATLAS_UART_REGS_BASE     + ((offset)&lt;&lt;3))
macro_line|#else
DECL|macro|PORT
mdefine_line|#define PORT(offset) (ATLAS_UART_REGS_BASE + 3 + ((offset)&lt;&lt;3))
macro_line|#endif
macro_line|#elif defined(CONFIG_MIPS_SEAD)
macro_line|#include &lt;asm/mips-boards/sead.h&gt;
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
DECL|macro|PORT
mdefine_line|#define PORT(offset) (SEAD_UART0_REGS_BASE     + ((offset)&lt;&lt;3))
macro_line|#else
DECL|macro|PORT
mdefine_line|#define PORT(offset) (SEAD_UART0_REGS_BASE + 3 + ((offset)&lt;&lt;3))
macro_line|#endif
macro_line|#else
DECL|macro|PORT
mdefine_line|#define PORT(offset) (0x3f8 + (offset))
macro_line|#endif
DECL|function|serial_in
r_static
r_inline
r_int
r_int
id|serial_in
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
id|inb
c_func
(paren
id|PORT
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|serial_out
r_static
r_inline
r_void
id|serial_out
c_func
(paren
r_int
id|offset
comma
r_int
id|value
)paren
(brace
id|outb
c_func
(paren
id|value
comma
id|PORT
c_func
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|prom_putchar
r_int
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
id|serial_in
c_func
(paren
id|UART_LSR
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|serial_out
c_func
(paren
id|UART_TX
comma
id|c
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|prom_getchar
r_char
id|prom_getchar
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|serial_in
c_func
(paren
id|UART_LSR
)paren
op_amp
id|UART_LSR_DR
)paren
)paren
suffix:semicolon
r_return
id|serial_in
c_func
(paren
id|UART_RX
)paren
suffix:semicolon
)brace
eof
