multiline_comment|/*&n; * arch/ppc/boot/common/misc-common.c&n; * &n; * Misc. bootloader code (almost) all platforms can use&n; *&n; * Author: Johnnie Peters &lt;jpeters@mvista.com&gt;&n; * Editor: Tom Rini &lt;trini@mvista.com&gt;&n; *&n; * Derived from arch/ppc/boot/prep/misc.c&n; *&n; * Copyright 2000-2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;stdarg.h&gt;&t;/* for va_ bits */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;zlib.h&quot;
macro_line|#include &quot;nonstdio.h&quot;
multiline_comment|/* If we&squot;re on a ALL_PPC, assume we have a keyboard controller&n; * Also note, if we&squot;re not ALL_PPC, we assume you are a serial&n; * console - Tom */
macro_line|#if defined(CONFIG_ALL_PPC) &amp;&amp; defined(CONFIG_VGA_CONSOLE)
r_extern
r_void
id|cursor
c_func
(paren
r_int
id|x
comma
r_int
id|y
)paren
suffix:semicolon
r_extern
r_void
id|scroll
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|vidmem
suffix:semicolon
r_extern
r_int
id|lines
comma
id|cols
suffix:semicolon
r_extern
r_int
id|orig_x
comma
id|orig_y
suffix:semicolon
r_extern
r_int
id|keyb_present
suffix:semicolon
r_extern
r_int
id|CRT_tstc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|CRT_getc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|cursor
r_int
id|cursor
c_func
(paren
r_int
id|x
comma
r_int
id|y
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scroll
r_void
id|scroll
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|vidmem
r_char
id|vidmem
(braket
l_int|1
)braket
suffix:semicolon
DECL|macro|lines
mdefine_line|#define lines 0
DECL|macro|cols
mdefine_line|#define cols 0
DECL|variable|orig_x
r_int
id|orig_x
op_assign
l_int|0
suffix:semicolon
DECL|variable|orig_y
r_int
id|orig_y
op_assign
l_int|0
suffix:semicolon
DECL|macro|keyb_present
mdefine_line|#define keyb_present 0
DECL|function|CRT_tstc
r_int
id|CRT_tstc
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CRT_getc
r_int
id|CRT_getc
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_char
op_star
id|avail_ram
suffix:semicolon
r_extern
r_char
op_star
id|end_avail
suffix:semicolon
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_void
id|putc
c_func
(paren
r_const
r_char
id|c
)paren
suffix:semicolon
r_void
id|puthex
c_func
(paren
r_int
r_int
id|val
)paren
suffix:semicolon
r_void
id|_bcopy
c_func
(paren
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_int
id|_cvt
c_func
(paren
r_int
r_int
id|val
comma
r_char
op_star
id|buf
comma
r_int
id|radix
comma
r_char
op_star
id|digits
)paren
suffix:semicolon
r_void
id|_vprintk
c_func
(paren
r_void
(paren
op_star
id|putc
)paren
(paren
r_const
r_char
)paren
comma
r_const
r_char
op_star
id|fmt0
comma
id|va_list
id|ap
)paren
suffix:semicolon
DECL|variable|ISA_io
r_int
r_char
op_star
id|ISA_io
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
r_extern
r_int
r_int
id|com_port
suffix:semicolon
r_extern
r_int
id|serial_tstc
c_func
(paren
r_int
r_int
id|com_port
)paren
suffix:semicolon
r_extern
r_int
r_char
id|serial_getc
c_func
(paren
r_int
r_int
id|com_port
)paren
suffix:semicolon
r_extern
r_void
id|serial_putc
c_func
(paren
r_int
r_int
id|com_port
comma
r_int
r_char
id|c
)paren
suffix:semicolon
macro_line|#endif
DECL|function|pause
r_void
id|pause
c_func
(paren
r_void
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;pause&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|exit
r_void
m_exit
(paren
r_void
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;exit&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|tstc
r_int
id|tstc
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
r_if
c_cond
(paren
id|keyb_present
)paren
(brace
r_return
(paren
id|CRT_tstc
c_func
(paren
)paren
op_logical_or
id|serial_tstc
c_func
(paren
id|com_port
)paren
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
id|serial_tstc
c_func
(paren
id|com_port
)paren
)paren
suffix:semicolon
macro_line|#else
r_return
id|CRT_tstc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|getc
r_int
id|getc
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
r_if
c_cond
(paren
id|serial_tstc
c_func
(paren
id|com_port
)paren
)paren
r_return
(paren
id|serial_getc
c_func
(paren
id|com_port
)paren
)paren
suffix:semicolon
macro_line|#endif /* serial console */
r_if
c_cond
(paren
id|keyb_present
)paren
r_if
c_cond
(paren
id|CRT_tstc
c_func
(paren
)paren
)paren
(brace
r_return
(paren
id|CRT_getc
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|putc
id|putc
c_func
(paren
r_const
r_char
id|c
)paren
(brace
r_int
id|x
comma
id|y
suffix:semicolon
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
id|serial_putc
c_func
(paren
id|com_port
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|serial_putc
c_func
(paren
id|com_port
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
macro_line|#endif /* serial console */
id|x
op_assign
id|orig_x
suffix:semicolon
id|y
op_assign
id|orig_y
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;b&squot;
)paren
(brace
r_if
c_cond
(paren
id|x
OG
l_int|0
)paren
(brace
id|x
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|vidmem
(braket
(paren
id|x
op_plus
id|cols
op_star
id|y
)paren
op_star
l_int|2
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_ge
id|cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
)brace
id|cursor
c_func
(paren
id|x
comma
id|y
)paren
suffix:semicolon
id|orig_x
op_assign
id|x
suffix:semicolon
id|orig_y
op_assign
id|y
suffix:semicolon
)brace
DECL|function|puts
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
r_int
id|x
comma
id|y
suffix:semicolon
r_char
id|c
suffix:semicolon
id|x
op_assign
id|orig_x
suffix:semicolon
id|y
op_assign
id|orig_y
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
macro_line|#if defined(CONFIG_SERIAL_CONSOLE) || defined(CONFIG_SERIAL_8250_CONSOLE)
id|serial_putc
c_func
(paren
id|com_port
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|serial_putc
c_func
(paren
id|com_port
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
macro_line|#endif /* serial console */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;b&squot;
)paren
(brace
r_if
c_cond
(paren
id|x
OG
l_int|0
)paren
(brace
id|x
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|vidmem
(braket
(paren
id|x
op_plus
id|cols
op_star
id|y
)paren
op_star
l_int|2
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_ge
id|cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
id|scroll
c_func
(paren
)paren
suffix:semicolon
id|y
op_decrement
suffix:semicolon
)brace
)brace
)brace
)brace
id|cursor
c_func
(paren
id|x
comma
id|y
)paren
suffix:semicolon
id|orig_x
op_assign
id|x
suffix:semicolon
id|orig_y
op_assign
id|y
suffix:semicolon
)brace
DECL|function|error
r_void
id|error
c_func
(paren
r_char
op_star
id|x
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|puts
c_func
(paren
id|x
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&bslash;n -- System halted&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Halt */
)brace
DECL|function|zalloc
r_void
op_star
id|zalloc
c_func
(paren
r_void
op_star
id|x
comma
r_int
id|items
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|p
op_assign
id|avail_ram
suffix:semicolon
id|size
op_mul_assign
id|items
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|7
)paren
op_amp
op_minus
l_int|8
suffix:semicolon
id|avail_ram
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
OG
id|end_avail
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;oops... out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|zfree
r_void
id|zfree
c_func
(paren
r_void
op_star
id|x
comma
r_void
op_star
id|addr
comma
r_int
id|nb
)paren
(brace
)brace
DECL|macro|HEAD_CRC
mdefine_line|#define HEAD_CRC&t;2
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD&t;4
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME&t;8
DECL|macro|COMMENT
mdefine_line|#define COMMENT&t;&t;0x10
DECL|macro|RESERVED
mdefine_line|#define RESERVED&t;0xe0
DECL|macro|DEFLATED
mdefine_line|#define DEFLATED&t;8
DECL|function|gunzip
r_void
id|gunzip
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_int
r_char
op_star
id|src
comma
r_int
op_star
id|lenp
)paren
(brace
id|z_stream
id|s
suffix:semicolon
r_int
id|r
comma
id|i
comma
id|flags
suffix:semicolon
multiline_comment|/* skip header */
id|i
op_assign
l_int|10
suffix:semicolon
id|flags
op_assign
id|src
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_ne
id|DEFLATED
op_logical_or
(paren
id|flags
op_amp
id|RESERVED
)paren
op_ne
l_int|0
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;bad gzipped data&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|EXTRA_FIELD
)paren
op_ne
l_int|0
)paren
id|i
op_assign
l_int|12
op_plus
id|src
(braket
l_int|10
)braket
op_plus
(paren
id|src
(braket
l_int|11
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ORIG_NAME
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|COMMENT
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|HEAD_CRC
)paren
op_ne
l_int|0
)paren
id|i
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
op_star
id|lenp
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;gunzip: ran out of data in header&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.zalloc
op_assign
id|zalloc
suffix:semicolon
id|s.zfree
op_assign
id|zfree
suffix:semicolon
id|r
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|s
comma
op_minus
id|MAX_WBITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;inflateInit2 returned &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|r
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.next_in
op_assign
id|src
op_plus
id|i
suffix:semicolon
id|s.avail_in
op_assign
op_star
id|lenp
op_minus
id|i
suffix:semicolon
id|s.next_out
op_assign
id|dst
suffix:semicolon
id|s.avail_out
op_assign
id|dstlen
suffix:semicolon
id|r
op_assign
id|inflate
c_func
(paren
op_amp
id|s
comma
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_and
id|r
op_ne
id|Z_STREAM_END
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;inflate returned &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
id|r
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
id|s.next_out
op_minus
(paren
r_int
r_char
op_star
)paren
id|dst
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
)brace
r_void
DECL|function|puthex
id|puthex
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|buf
(braket
id|i
)braket
op_assign
l_string|&quot;0123456789ABCDEF&quot;
(braket
id|val
op_amp
l_int|0x0F
)braket
suffix:semicolon
id|val
op_rshift_assign
l_int|4
suffix:semicolon
)brace
id|buf
(braket
l_int|8
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|puts
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE  1
r_void
DECL|function|_printk
id|_printk
c_func
(paren
r_char
r_const
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|_vprintk
c_func
(paren
id|putc
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|macro|is_digit
mdefine_line|#define is_digit(c) ((c &gt;= &squot;0&squot;) &amp;&amp; (c &lt;= &squot;9&squot;))
r_void
DECL|function|_vprintk
id|_vprintk
c_func
(paren
r_void
(paren
op_star
id|putc
)paren
(paren
r_const
r_char
)paren
comma
r_const
r_char
op_star
id|fmt0
comma
id|va_list
id|ap
)paren
(brace
r_char
id|c
comma
id|sign
comma
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
r_int
id|left_prec
comma
id|right_prec
comma
id|zero_fill
comma
id|length
op_assign
l_int|0
comma
id|pad
comma
id|pad_on_right
suffix:semicolon
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|val
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|fmt0
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;%&squot;
)paren
(brace
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
id|left_prec
op_assign
id|right_prec
op_assign
id|pad_on_right
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
id|pad_on_right
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|zero_fill
op_assign
id|TRUE
suffix:semicolon
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
)brace
r_else
(brace
id|zero_fill
op_assign
id|FALSE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|is_digit
c_func
(paren
id|c
)paren
)paren
(brace
id|left_prec
op_assign
(paren
id|left_prec
op_star
l_int|10
)paren
op_plus
(paren
id|c
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
(brace
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
id|zero_fill
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|is_digit
c_func
(paren
id|c
)paren
)paren
(brace
id|right_prec
op_assign
(paren
id|right_prec
op_star
l_int|10
)paren
op_plus
(paren
id|c
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|c
op_assign
op_star
id|fmt0
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|right_prec
op_assign
id|left_prec
suffix:semicolon
)brace
id|sign
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;x&squot;
suffix:colon
r_case
l_char|&squot;X&squot;
suffix:colon
id|val
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_int
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|val
op_assign
op_minus
id|val
suffix:semicolon
)brace
id|length
op_assign
id|_cvt
c_func
(paren
id|val
comma
id|buf
comma
l_int|10
comma
l_string|&quot;0123456789&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
id|length
op_assign
id|_cvt
c_func
(paren
id|val
comma
id|buf
comma
l_int|16
comma
l_string|&quot;0123456789abcdef&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
id|length
op_assign
id|_cvt
c_func
(paren
id|val
comma
id|buf
comma
l_int|16
comma
l_string|&quot;0123456789ABCDEF&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cp
op_assign
id|buf
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|cp
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_char
op_star
)paren
suffix:semicolon
id|length
op_assign
id|strlen
c_func
(paren
id|cp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
id|c
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_int
multiline_comment|/*char*/
)paren
suffix:semicolon
(paren
op_star
id|putc
)paren
(paren
id|c
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
(paren
op_star
id|putc
)paren
(paren
l_char|&squot;?&squot;
)paren
suffix:semicolon
)brace
id|pad
op_assign
id|left_prec
op_minus
id|length
suffix:semicolon
r_if
c_cond
(paren
id|sign
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|pad
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|zero_fill
)paren
(brace
id|c
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|sign
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
id|sign
)paren
suffix:semicolon
id|sign
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_else
(brace
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pad_on_right
)paren
(brace
r_while
c_loop
(paren
id|pad
op_decrement
OG
l_int|0
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sign
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
id|sign
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
op_decrement
OG
l_int|0
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
id|c
op_assign
op_star
id|cp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pad_on_right
)paren
(brace
r_while
c_loop
(paren
id|pad
op_decrement
OG
l_int|0
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
(paren
op_star
id|putc
)paren
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
(paren
op_star
id|putc
)paren
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_int
DECL|function|_cvt
id|_cvt
c_func
(paren
r_int
r_int
id|val
comma
r_char
op_star
id|buf
comma
r_int
id|radix
comma
r_char
op_star
id|digits
)paren
(brace
r_char
id|temp
(braket
l_int|80
)braket
suffix:semicolon
r_char
op_star
id|cp
op_assign
id|temp
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Special case */
op_star
id|cp
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|val
)paren
(brace
op_star
id|cp
op_increment
op_assign
id|digits
(braket
id|val
op_mod
id|radix
)braket
suffix:semicolon
id|val
op_div_assign
id|radix
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cp
op_ne
id|temp
)paren
(brace
op_star
id|buf
op_increment
op_assign
op_star
op_decrement
id|cp
suffix:semicolon
id|length
op_increment
suffix:semicolon
)brace
op_star
id|buf
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
r_void
DECL|function|_dump_buf_with_offset
id|_dump_buf_with_offset
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|s
comma
r_int
r_char
op_star
id|base
)paren
(brace
r_int
id|i
comma
id|c
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|s
OG
(paren
r_int
r_int
)paren
id|p
)paren
(brace
id|s
op_assign
(paren
r_int
r_int
)paren
id|s
op_minus
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|s
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|base
)paren
(brace
id|_printk
c_func
(paren
l_string|&quot;%06X: &quot;
comma
(paren
r_int
)paren
id|p
op_minus
(paren
r_int
)paren
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
id|_printk
c_func
(paren
l_string|&quot;%06X: &quot;
comma
id|p
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|s
)paren
(brace
id|_printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|p
(braket
id|i
)braket
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
r_else
(brace
id|_printk
c_func
(paren
l_string|&quot;  &quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|2
)paren
op_eq
l_int|1
)paren
id|_printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|7
)paren
id|_printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|_printk
c_func
(paren
l_string|&quot; |&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|s
)paren
(brace
id|c
op_assign
id|p
(braket
id|i
)braket
op_amp
l_int|0xFF
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
OL
l_int|0x20
)paren
op_logical_or
(paren
id|c
op_ge
l_int|0x7F
)paren
)paren
id|c
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
r_else
(brace
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|_printk
c_func
(paren
l_string|&quot;%c&quot;
comma
id|c
)paren
suffix:semicolon
)brace
id|_printk
c_func
(paren
l_string|&quot;|&bslash;n&quot;
)paren
suffix:semicolon
id|s
op_sub_assign
l_int|16
suffix:semicolon
id|p
op_add_assign
l_int|16
suffix:semicolon
)brace
)brace
r_void
DECL|function|_dump_buf
id|_dump_buf
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_int
id|s
)paren
(brace
id|_printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|_dump_buf_with_offset
c_func
(paren
id|p
comma
id|s
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Very simple inb/outb routines.  We declare ISA_io to be 0 above, and&n; * then modify it on platforms which need to.  We do it like this&n; * because on some platforms we give inb/outb an exact location, and&n; * on others it&squot;s an offset from a given location. -- Tom&n; */
r_void
DECL|function|outb
id|outb
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
multiline_comment|/* Ensure I/O operations complete */
id|__asm__
r_volatile
(paren
l_string|&quot;eieio&quot;
)paren
suffix:semicolon
id|ISA_io
(braket
id|port
)braket
op_assign
id|val
suffix:semicolon
)brace
r_int
r_char
DECL|function|inb
id|inb
c_func
(paren
r_int
id|port
)paren
(brace
multiline_comment|/* Ensure I/O operations complete */
id|__asm__
r_volatile
(paren
l_string|&quot;eieio&quot;
)paren
suffix:semicolon
r_return
(paren
id|ISA_io
(braket
id|port
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
