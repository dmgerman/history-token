multiline_comment|/*&n; *  linux/arch/m32r/kernel/io_usrv.c&n; *&n; *  Typical I/O routines for uServer board.&n; *&n; *  Copyright (c) 2001 - 2003  Hiroyuki Kondo, Hirokazu Takata,&n; *                             Hitoshi Yamamoto, Takeo Takahashi&n; *&n; *  This file is subject to the terms and conditions of the GNU General&n; *  Public License.  See the file &quot;COPYING&quot; in the main directory of this&n; *  archive for more details.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;../drivers/m32r_cfc.h&quot;
r_extern
r_void
id|pcc_ioread_byte
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_ioread_word
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_iowrite_byte
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pcc_iowrite_word
c_func
(paren
r_int
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|CFC_IOSTART
mdefine_line|#define CFC_IOSTART&t;CFC_IOPORT_BASE
DECL|macro|CFC_IOEND
mdefine_line|#define CFC_IOEND&t;(CFC_IOSTART + (M32R_PCC_MAPSIZE * M32R_MAX_PCC) - 1)
macro_line|#if defined(CONFIG_SERIAL_8250) || defined(CONFIG_SERIAL_8250_MODULE)
DECL|macro|UART0_REGSTART
mdefine_line|#define UART0_REGSTART&t;&t;0x04c20000
DECL|macro|UART1_REGSTART
mdefine_line|#define UART1_REGSTART&t;&t;0x04c20100
DECL|macro|UART_IOMAP_SIZE
mdefine_line|#define UART_IOMAP_SIZE&t;&t;8
DECL|macro|UART0_IOSTART
mdefine_line|#define UART0_IOSTART&t;&t;0x3f8
DECL|macro|UART0_IOEND
mdefine_line|#define UART0_IOEND&t;&t;(UART0_IOSTART + UART_IOMAP_SIZE - 1)
DECL|macro|UART1_IOSTART
mdefine_line|#define UART1_IOSTART&t;&t;0x2f8
DECL|macro|UART1_IOEND
mdefine_line|#define UART1_IOEND&t;&t;(UART1_IOSTART + UART_IOMAP_SIZE - 1)
macro_line|#endif&t;/* CONFIG_SERIAL_8250 || CONFIG_SERIAL_8250_MODULE */
DECL|macro|PORT2ADDR
mdefine_line|#define PORT2ADDR(port)&t;_port2addr(port)
DECL|function|_port2addr
r_static
id|__inline__
r_void
op_star
id|_port2addr
c_func
(paren
r_int
r_int
id|port
)paren
(brace
macro_line|#if defined(CONFIG_SERIAL_8250) || defined(CONFIG_SERIAL_8250_MODULE)
r_if
c_cond
(paren
id|port
op_ge
id|UART0_IOSTART
op_logical_and
id|port
op_le
id|UART0_IOEND
)paren
id|port
op_assign
(paren
(paren
id|port
op_minus
id|UART0_IOSTART
)paren
op_lshift
l_int|1
)paren
op_plus
id|UART0_REGSTART
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_ge
id|UART1_IOSTART
op_logical_and
id|port
op_le
id|UART1_IOEND
)paren
id|port
op_assign
(paren
(paren
id|port
op_minus
id|UART1_IOSTART
)paren
op_lshift
l_int|1
)paren
op_plus
id|UART1_REGSTART
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_8250 || CONFIG_SERIAL_8250_MODULE */
r_return
(paren
r_void
op_star
)paren
(paren
id|port
op_plus
id|NONCACHE_OFFSET
)paren
suffix:semicolon
)brace
DECL|function|delay
r_static
id|__inline__
r_void
id|delay
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;push r0; &bslash;n&bslash;t pop r0;&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_inb
r_int
r_char
id|_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
r_else
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inw
r_int
r_int
id|_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
r_else
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inl
r_int
r_int
id|_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|l
comma
r_sizeof
(paren
id|l
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|l
suffix:semicolon
)brace
r_else
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|_inb_p
r_int
r_char
id|_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
(brace
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
)brace
DECL|function|_inw_p
r_int
r_int
id|_inw_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
(brace
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
r_else
(brace
id|w
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|w
suffix:semicolon
)brace
)brace
DECL|function|_inl_p
r_int
r_int
id|_inl_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|_outb
r_void
id|_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_else
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|_outw
r_void
id|_outw
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_else
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|_outl
r_void
id|_outl
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|l
comma
r_sizeof
(paren
id|l
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_else
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|l
suffix:semicolon
)brace
DECL|function|_outb_p
r_void
id|_outb_p
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|b
comma
r_sizeof
(paren
id|b
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_else
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_outw_p
r_void
id|_outw_p
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
op_amp
id|w
comma
r_sizeof
(paren
id|w
)paren
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_else
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|w
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_outl_p
r_void
id|_outl_p
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|l
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|_insb
r_void
id|_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_ioread_byte
c_func
(paren
l_int|0
comma
id|port
comma
id|addr
comma
r_sizeof
(paren
r_int
r_char
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
r_else
(brace
r_int
r_char
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
suffix:semicolon
)brace
)brace
)brace
DECL|function|_insw
r_void
id|_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_ioread_word
c_func
(paren
l_int|0
comma
id|port
comma
id|addr
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
suffix:semicolon
)brace
)brace
DECL|function|_insl
r_void
id|_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|buf
op_increment
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
suffix:semicolon
)brace
DECL|function|_outsb
r_void
id|_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_char
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_byte
c_func
(paren
l_int|0
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_char
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|_outsw
r_void
id|_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_int
op_star
id|portp
suffix:semicolon
r_if
c_cond
(paren
id|port
op_ge
id|CFC_IOSTART
op_logical_and
id|port
op_le
id|CFC_IOEND
)paren
id|pcc_iowrite_word
c_func
(paren
l_int|0
comma
id|port
comma
(paren
r_void
op_star
)paren
id|addr
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|_outsl
r_void
id|_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|addr
suffix:semicolon
r_int
r_char
op_star
id|portp
suffix:semicolon
id|portp
op_assign
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|portp
op_assign
op_star
id|buf
op_increment
suffix:semicolon
)brace
eof
