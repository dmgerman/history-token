multiline_comment|/*&n; * arch/ppc/syslib/ppc405_serial.c&n; *&n; * Author: MontaVista Software, Inc.&n; *         &t;frank_rowand@mvista.com or source@mvista.com&n; * &t;   &t;debbie_chu@mvista.com&n; *&n; * This is a fairly standard 165xx type device that will eventually&n; * be merged with other similar processor/boards.&t;-- Dan&n; *&n; * 2000 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * Console I/O support for Early kernel bringup.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_IBM405GP) || defined(CONFIG_IBM405CR)
macro_line|#ifdef CONFIG_KGDB
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_BRINGUP
macro_line|#include &lt;linux/console.h&gt;
r_extern
r_void
id|ftr_reset_preferred_console
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ppc405_sercons_setup
r_static
r_int
id|ppc405_sercons_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
macro_line|#ifdef CONFIG_UART0_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_dll
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600300
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_fcr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600302
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lcr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600303
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UART1_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_dll
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600400
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_fcr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600402
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lcr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600403
suffix:semicolon
macro_line|#endif
op_star
id|uart_lcr
op_assign
op_star
id|uart_lcr
op_or
l_int|0x80
suffix:semicolon
multiline_comment|/* DLAB on  */
multiline_comment|/* ftr revisit - there is no config option for this&n;**  also see include/asm-ppc/ppc405_serial.h&n;**&n;** #define CONFIG_IBM405GP_INTERNAL_CLOCK&n;*/
macro_line|#ifdef  CONFIG_IBM405GP_INTERNAL_CLOCK
multiline_comment|/* ftr revisit&n;    ** why is bit 19 of chcr0 (0x1000) being set?&n;    */
multiline_comment|/* 0x2a results in data corruption, kgdb works with 0x28 */
op_star
id|uart_dll
op_assign
l_int|0x28
suffix:semicolon
multiline_comment|/* 9600 baud */
id|_put_CHCR0
c_func
(paren
(paren
id|_get_CHCR0
c_func
(paren
)paren
op_amp
l_int|0xffffe000
)paren
op_or
l_int|0x103e
)paren
suffix:semicolon
macro_line|#else
op_star
id|uart_dll
op_assign
l_int|0x48
suffix:semicolon
multiline_comment|/* 9600 baud */
macro_line|#endif
op_star
id|uart_lcr
op_assign
op_star
id|uart_lcr
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* DLAB off */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a bringup hack, writing directly to uart0 or uart1&n; */
r_static
r_void
DECL|function|ppc405_sercons_write
id|ppc405_sercons_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_UART0_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_xmit
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600300
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lsr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600305
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UART1_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_xmit
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600400
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lsr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600405
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nb
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/* wait for transmit reg (possibly fifo) to empty */
r_while
c_loop
(paren
(paren
op_star
id|uart_lsr
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
id|uart_xmit
op_assign
(paren
id|ptr
(braket
id|i
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* add a carriage return */
multiline_comment|/* wait for transmit reg (possibly fifo) to empty */
r_while
c_loop
(paren
(paren
op_star
id|uart_lsr
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
id|uart_xmit
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
r_static
r_int
DECL|function|ppc405_sercons_read
id|ppc405_sercons_read
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|ptr
comma
r_int
id|nb
)paren
(brace
macro_line|#ifdef CONFIG_UART0_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_rcv
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600300
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lsr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600305
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UART1_DEBUG_CONSOLE
r_volatile
r_int
r_char
op_star
id|uart_rcv
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600400
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|uart_lsr
op_assign
(paren
r_char
op_star
)paren
l_int|0xef600405
suffix:semicolon
macro_line|#endif
multiline_comment|/* ftr revisit: not tested */
r_if
c_cond
(paren
id|nb
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* wait for receive reg (possibly fifo) to contain data */
r_while
c_loop
(paren
(paren
op_star
id|uart_lsr
op_amp
l_int|0x01
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
id|ptr
op_assign
op_star
id|uart_rcv
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ppc405_sercons
r_static
r_struct
id|console
id|ppc405_sercons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dbg_cons&quot;
comma
dot
id|write
op_assign
id|ppc405_console_write
comma
dot
id|setup
op_assign
id|ppc405_console_setup
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
r_void
DECL|function|register_debug_console
id|register_debug_console
c_func
(paren
r_void
)paren
(brace
id|register_console
c_func
(paren
op_amp
id|ppc405_sercons
)paren
suffix:semicolon
)brace
r_void
DECL|function|unregister_debug_console
id|unregister_debug_console
c_func
(paren
r_void
)paren
(brace
id|unregister_console
c_func
(paren
op_amp
id|ppc405_sercons
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_DEBUG_BRINGUP */
macro_line|#endif&t;/* #if defined(CONFIG_IBM405GP) || defined(CONFIG_IBM405CR) */
eof
