multiline_comment|/* suncore.c&n; *&n; * Common SUN serial routines.  Based entirely&n; * upon drivers/sbus/char/sunserial.c which is:&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; *&n; * Adaptation to new UART layer is:&n; *&n; * Copyright (C) 2002 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &quot;suncore.h&quot;
DECL|variable|serial_console
r_int
id|serial_console
suffix:semicolon
DECL|variable|stop_a_enabled
r_int
id|stop_a_enabled
op_assign
l_int|1
suffix:semicolon
DECL|variable|sunserial_current_minor
r_int
id|sunserial_current_minor
op_assign
l_int|64
suffix:semicolon
DECL|variable|serial_console
id|EXPORT_SYMBOL
c_func
(paren
id|serial_console
)paren
suffix:semicolon
DECL|variable|stop_a_enabled
id|EXPORT_SYMBOL
c_func
(paren
id|stop_a_enabled
)paren
suffix:semicolon
DECL|variable|sunserial_current_minor
id|EXPORT_SYMBOL
c_func
(paren
id|sunserial_current_minor
)paren
suffix:semicolon
r_void
DECL|function|sunserial_console_termios
id|sunserial_console_termios
c_func
(paren
r_struct
id|console
op_star
id|con
)paren
(brace
r_char
id|mode
(braket
l_int|16
)braket
comma
id|buf
(braket
l_int|16
)braket
comma
op_star
id|s
suffix:semicolon
r_char
op_star
id|mode_prop
op_assign
l_string|&quot;ttyX-mode&quot;
suffix:semicolon
r_char
op_star
id|cd_prop
op_assign
l_string|&quot;ttyX-ignore-cd&quot;
suffix:semicolon
r_char
op_star
id|dtr_prop
op_assign
l_string|&quot;ttyX-rts-dtr-off&quot;
suffix:semicolon
r_int
id|baud
comma
id|bits
comma
id|stop
comma
id|cflag
suffix:semicolon
r_char
id|parity
suffix:semicolon
r_int
id|carrier
op_assign
l_int|0
suffix:semicolon
r_int
id|rtsdtr
op_assign
l_int|1
suffix:semicolon
r_int
id|topnd
comma
id|nd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|serial_console
op_eq
l_int|1
)paren
(brace
id|mode_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
id|cd_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
id|dtr_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;a&squot;
suffix:semicolon
)brace
r_else
(brace
id|mode_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|cd_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|dtr_prop
(braket
l_int|3
)braket
op_assign
l_char|&squot;b&squot;
suffix:semicolon
)brace
id|topnd
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|nd
op_assign
id|prom_searchsiblings
c_func
(paren
id|topnd
comma
l_string|&quot;options&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nd
)paren
(brace
id|strcpy
c_func
(paren
id|mode
comma
l_string|&quot;9600,8,n,1,-&quot;
)paren
suffix:semicolon
r_goto
id|no_options
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prom_node_has_property
c_func
(paren
id|nd
comma
id|mode_prop
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|mode
comma
l_string|&quot;9600,8,n,1,-&quot;
)paren
suffix:semicolon
r_goto
id|no_options
suffix:semicolon
)brace
id|memset
c_func
(paren
id|mode
comma
l_int|0
comma
r_sizeof
(paren
id|mode
)paren
)paren
suffix:semicolon
id|prom_getstring
c_func
(paren
id|nd
comma
id|mode_prop
comma
id|mode
comma
r_sizeof
(paren
id|mode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_node_has_property
c_func
(paren
id|nd
comma
id|cd_prop
)paren
)paren
(brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|prom_getstring
c_func
(paren
id|nd
comma
id|cd_prop
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;false&quot;
)paren
)paren
id|carrier
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* XXX: this is unused below. */
)brace
r_if
c_cond
(paren
id|prom_node_has_property
c_func
(paren
id|nd
comma
id|dtr_prop
)paren
)paren
(brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|prom_getstring
c_func
(paren
id|nd
comma
id|dtr_prop
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;false&quot;
)paren
)paren
id|rtsdtr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX: this is unused below. */
)brace
id|no_options
suffix:colon
id|cflag
op_assign
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
id|s
op_assign
id|mode
suffix:semicolon
id|baud
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
id|bits
op_assign
id|simple_strtoul
c_func
(paren
op_increment
id|s
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
id|parity
op_assign
op_star
(paren
op_increment
id|s
)paren
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
id|stop
op_assign
id|simple_strtoul
c_func
(paren
op_increment
id|s
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
multiline_comment|/* XXX handshake is not handled here. */
r_switch
c_cond
(paren
id|baud
)paren
(brace
r_case
l_int|150
suffix:colon
id|cflag
op_or_assign
id|B150
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|300
suffix:colon
id|cflag
op_or_assign
id|B300
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|600
suffix:colon
id|cflag
op_or_assign
id|B600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1200
suffix:colon
id|cflag
op_or_assign
id|B1200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2400
suffix:colon
id|cflag
op_or_assign
id|B2400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4800
suffix:colon
id|cflag
op_or_assign
id|B4800
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9600
suffix:colon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|cflag
op_or_assign
id|B19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|cflag
op_or_assign
id|B38400
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|baud
op_assign
l_int|9600
suffix:semicolon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|bits
)paren
(brace
r_case
l_int|5
suffix:colon
id|cflag
op_or_assign
id|CS5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|cflag
op_or_assign
id|CS6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|cflag
op_or_assign
id|CS7
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|cflag
op_or_assign
id|CS8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cflag
op_or_assign
id|CS8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|parity
)paren
(brace
r_case
l_char|&squot;o&squot;
suffix:colon
id|cflag
op_or_assign
(paren
id|PARENB
op_or
id|PARODD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;e&squot;
suffix:colon
id|cflag
op_or_assign
id|PARENB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|stop
)paren
(brace
r_case
l_int|2
suffix:colon
id|cflag
op_or_assign
id|CSTOPB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|con-&gt;cflag
op_assign
id|cflag
suffix:semicolon
)brace
DECL|variable|sunserial_console_termios
id|EXPORT_SYMBOL
c_func
(paren
id|sunserial_console_termios
)paren
suffix:semicolon
r_void
DECL|function|sun_do_break
id|sun_do_break
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|stop_a_enabled
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|flush_user_windows
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SPARC64
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|linux_dbvec
op_ge
id|DEBUG_FIRSTVADDR
op_logical_and
(paren
r_int
r_int
)paren
id|linux_dbvec
op_le
id|DEBUG_LASTVADDR
)paren
id|sp_enter_debugger
c_func
(paren
)paren
suffix:semicolon
r_else
macro_line|#endif
id|prom_cmdline
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sun_do_break
id|EXPORT_SYMBOL
c_func
(paren
id|sun_do_break
)paren
suffix:semicolon
multiline_comment|/* Sun serial MOUSE auto baud rate detection.  */
DECL|struct|mouse_baud_cflag
r_static
r_struct
id|mouse_baud_cflag
(brace
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|cflag
r_int
r_int
id|cflag
suffix:semicolon
DECL|variable|mouse_baud_table
)brace
id|mouse_baud_table
(braket
)braket
op_assign
(brace
(brace
l_int|1200
comma
id|B1200
)brace
comma
(brace
l_int|2400
comma
id|B2400
)brace
comma
(brace
l_int|4800
comma
id|B4800
)brace
comma
(brace
l_int|9600
comma
id|B9600
)brace
comma
(brace
op_minus
l_int|1
comma
op_complement
l_int|0
)brace
comma
(brace
op_minus
l_int|1
comma
op_complement
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|function|suncore_mouse_baud_cflag_next
r_int
r_int
id|suncore_mouse_baud_cflag_next
c_func
(paren
r_int
r_int
id|cflag
comma
r_int
op_star
id|new_baud
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|mouse_baud_table
(braket
id|i
)braket
dot
id|baud
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mouse_baud_table
(braket
id|i
)braket
dot
id|cflag
op_eq
(paren
id|cflag
op_amp
id|CBAUD
)paren
)paren
r_break
suffix:semicolon
id|i
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mouse_baud_table
(braket
id|i
)braket
dot
id|baud
op_eq
op_minus
l_int|1
)paren
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|new_baud
op_assign
id|mouse_baud_table
(braket
id|i
)braket
dot
id|baud
suffix:semicolon
r_return
id|mouse_baud_table
(braket
id|i
)braket
dot
id|cflag
suffix:semicolon
)brace
DECL|variable|suncore_mouse_baud_cflag_next
id|EXPORT_SYMBOL
c_func
(paren
id|suncore_mouse_baud_cflag_next
)paren
suffix:semicolon
multiline_comment|/* Basically, when the baud rate is wrong the mouse spits out&n; * breaks to us.&n; */
DECL|function|suncore_mouse_baud_detection
r_int
id|suncore_mouse_baud_detection
c_func
(paren
r_int
r_char
id|ch
comma
r_int
id|is_break
)paren
(brace
r_static
r_int
id|mouse_got_break
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|ctr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_break
)paren
(brace
multiline_comment|/* Let a few normal bytes go by before we jump the gun&n;&t;&t; * and say we need to try another baud rate.&n;&t;&t; */
r_if
c_cond
(paren
id|mouse_got_break
op_logical_and
id|ctr
OL
l_int|8
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Ok, we need to try another baud. */
id|ctr
op_assign
l_int|0
suffix:semicolon
id|mouse_got_break
op_assign
l_int|1
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mouse_got_break
)paren
(brace
id|ctr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|0x87
)paren
(brace
multiline_comment|/* Correct baud rate determined. */
id|mouse_got_break
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|suncore_mouse_baud_detection
id|EXPORT_SYMBOL
c_func
(paren
id|suncore_mouse_baud_detection
)paren
suffix:semicolon
DECL|function|suncore_init
r_static
r_int
id|__init
id|suncore_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|suncore_exit
r_static
r_void
id|__exit
id|suncore_exit
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|suncore_init
id|module_init
c_func
(paren
id|suncore_init
)paren
suffix:semicolon
DECL|variable|suncore_exit
id|module_exit
c_func
(paren
id|suncore_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eddie C. Dost, David S. Miller&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Sun serial common layer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
