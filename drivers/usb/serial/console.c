multiline_comment|/*&n; * USB Serial Console driver&n; *&n; * Copyright (C) 2001 - 2002 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; * &n; * Thanks to Randy Dunlap for the original version of this code.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
macro_line|#include &quot;usb-serial.h&quot;
DECL|struct|usbcons_info
r_struct
id|usbcons_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|break_flag
r_int
id|break_flag
suffix:semicolon
DECL|member|port
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|usbcons_info
r_static
r_struct
id|usbcons_info
id|usbcons_info
suffix:semicolon
DECL|variable|usbcons
r_static
r_struct
id|console
id|usbcons
suffix:semicolon
multiline_comment|/*&n; * ------------------------------------------------------------&n; * USB Serial console driver&n; *&n; * Much of the code here is copied from drivers/char/serial.c&n; * and implements a phony serial console in the same way that&n; * serial.c does so that in case some software queries it,&n; * it will get the same results.&n; *&n; * Things that are different from the way the serial port code&n; * does things, is that we call the lower level usb-serial&n; * driver code to initialize the device, and we set the initial&n; * console speeds based on the command line arguments.&n; * ------------------------------------------------------------&n; */
multiline_comment|/*&n; * The parsing of the command line works exactly like the&n; * serial.c code, except that the specifier is &quot;ttyUSB&quot; instead&n; * of &quot;ttyS&quot;.&n; */
DECL|function|usb_console_setup
r_static
r_int
id|__init
id|usb_console_setup
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
r_struct
id|usbcons_info
op_star
id|info
op_assign
op_amp
id|usbcons_info
suffix:semicolon
r_int
id|baud
op_assign
l_int|9600
suffix:semicolon
r_int
id|bits
op_assign
l_int|8
suffix:semicolon
r_int
id|parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_int
id|doflow
op_assign
l_int|0
suffix:semicolon
r_int
id|cflag
op_assign
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_struct
id|usb_serial
op_star
id|serial
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_struct
id|termios
op_star
id|termios
suffix:semicolon
id|dbg
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|options
)paren
(brace
id|baud
op_assign
id|simple_strtoul
c_func
(paren
id|options
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|s
op_assign
id|options
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|s
op_le
l_char|&squot;9&squot;
)paren
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
id|parity
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
id|bits
op_assign
op_star
id|s
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
id|doflow
op_assign
(paren
op_star
id|s
op_increment
op_eq
l_char|&squot;r&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* build a cflag setting */
r_switch
c_cond
(paren
id|baud
)paren
(brace
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
r_case
l_int|57600
suffix:colon
id|cflag
op_or_assign
id|B57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|115200
suffix:colon
id|cflag
op_or_assign
id|B115200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9600
suffix:colon
r_default
suffix:colon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Set this to a sane value to prevent a divide error&n;&t;&t;&t; */
id|baud
op_assign
l_int|9600
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
l_int|7
suffix:colon
id|cflag
op_or_assign
id|CS7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_int|8
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
r_case
l_char|&squot;O&squot;
suffix:colon
id|cflag
op_or_assign
id|PARODD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;e&squot;
suffix:colon
r_case
l_char|&squot;E&squot;
suffix:colon
id|cflag
op_or_assign
id|PARENB
suffix:semicolon
r_break
suffix:semicolon
)brace
id|co-&gt;cflag
op_assign
id|cflag
suffix:semicolon
multiline_comment|/* grab the first serial port that happens to be connected */
id|serial
op_assign
id|usb_serial_get_by_index
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial_paranoia_check
(paren
id|serial
comma
id|__FUNCTION__
)paren
)paren
(brace
multiline_comment|/* no device is connected yet, sorry :( */
id|err
(paren
l_string|&quot;No USB device connected to ttyUSB0&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|port
op_assign
op_amp
id|serial-&gt;port
(braket
l_int|0
)braket
suffix:semicolon
id|port-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;port
op_assign
id|port
suffix:semicolon
op_increment
id|port-&gt;open_count
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;open_count
op_eq
l_int|1
)paren
(brace
multiline_comment|/* only call the device specific open if this &n;&t;&t; * is the first time the port is opened */
r_if
c_cond
(paren
id|serial-&gt;type-&gt;open
)paren
id|retval
op_assign
id|serial-&gt;type
op_member_access_from_pointer
id|open
c_func
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|retval
op_assign
id|usb_serial_generic_open
c_func
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|port-&gt;open_count
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
(brace
id|err
(paren
l_string|&quot;could not open USB console port&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial-&gt;type-&gt;set_termios
)paren
(brace
multiline_comment|/* build up a fake tty structure so that the open call has something&n;&t;&t; * to look at to get the cflag value */
id|tty
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|tty
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
(brace
id|err
(paren
l_string|&quot;no more memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|termios
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|termios
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|termios
)paren
(brace
id|err
(paren
l_string|&quot;no more memory&quot;
)paren
suffix:semicolon
id|kfree
(paren
id|tty
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
(paren
id|tty
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|tty
)paren
)paren
suffix:semicolon
id|memset
(paren
id|termios
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|termios
)paren
)paren
suffix:semicolon
id|termios-&gt;c_cflag
op_assign
id|cflag
suffix:semicolon
id|tty-&gt;termios
op_assign
id|termios
suffix:semicolon
id|port-&gt;tty
op_assign
id|tty
suffix:semicolon
multiline_comment|/* set up the initial termios settings */
id|serial-&gt;type
op_member_access_from_pointer
id|set_termios
c_func
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
id|port-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
id|kfree
(paren
id|termios
)paren
suffix:semicolon
id|kfree
(paren
id|tty
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_console_write
r_static
r_void
id|usb_console_write
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
id|buf
comma
r_int
id|count
)paren
(brace
r_static
r_struct
id|usbcons_info
op_star
id|info
op_assign
op_amp
id|usbcons_info
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|port
op_assign
id|info-&gt;port
suffix:semicolon
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|get_usb_serial
(paren
id|port
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial
op_logical_or
op_logical_neg
id|port
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d, %d byte(s)&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;open_count
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - port not opened&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* pass on to the driver specific version of this function if it is available */
r_if
c_cond
(paren
id|serial-&gt;type-&gt;write
)paren
id|retval
op_assign
id|serial-&gt;type
op_member_access_from_pointer
id|write
c_func
(paren
id|port
comma
l_int|0
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_else
id|retval
op_assign
id|usb_serial_generic_write
c_func
(paren
id|port
comma
l_int|0
comma
id|buf
comma
id|count
)paren
suffix:semicolon
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - return value (if we had one): %d&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
)brace
DECL|variable|usbcons
r_static
r_struct
id|console
id|usbcons
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ttyUSB&quot;
comma
dot
id|write
op_assign
id|usb_console_write
comma
dot
id|setup
op_assign
id|usb_console_setup
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
DECL|function|usb_serial_console_init
r_void
id|usb_serial_console_init
(paren
r_int
id|serial_debug
comma
r_int
id|minor
)paren
(brace
id|debug
op_assign
id|serial_debug
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &n;&t;&t; * Call register_console() if this is the first device plugged&n;&t;&t; * in.  If we call it earlier, then the callback to&n;&t;&t; * console_setup() will fail, as there is not a device seen by&n;&t;&t; * the USB subsystem yet.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Register console.&n;&t;&t; * NOTES:&n;&t;&t; * console_setup() is called (back) immediately (from register_console).&n;&t;&t; * console_write() is called immediately from register_console iff&n;&t;&t; * CON_PRINTBUFFER is set in flags.&n;&t;&t; */
id|dbg
(paren
l_string|&quot;registering the USB serial console.&quot;
)paren
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|usbcons
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_serial_console_exit
r_void
id|usb_serial_console_exit
(paren
r_void
)paren
(brace
id|unregister_console
c_func
(paren
op_amp
id|usbcons
)paren
suffix:semicolon
)brace
eof
