multiline_comment|/*&n; * Prolific PL2303 USB to serial adaptor driver&n; *&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; * Original driver for 2.2.x by anonymous&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * 2001_Aug_30 gkh&n; *&t;fixed oops in write_bulk_callback.&n; *&n; * 2001_Aug_28 gkh&n; *&t;reworked buffer logic to be like other usb-serial drivers.  Hopefully&n; *&t;removing some reported problems.&n; *&n; * 2001_Jun_06 gkh&n; *&t;finished porting to 2.4 format.&n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#ifdef CONFIG_USB_SERIAL_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;usb-serial.h&quot;
macro_line|#include &quot;pl2303.h&quot;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.7&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;Prolific PL2303 USB to serial adaptor driver&quot;
DECL|variable|id_table
r_static
id|__devinitdata
r_struct
id|usb_device_id
id|id_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|PL2303_VENDOR_ID
comma
id|PL2303_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ATEN_VENDOR_ID
comma
id|ATEN_PRODUCT_ID
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|id_table
)paren
suffix:semicolon
multiline_comment|/* function prototypes for a PL2303 serial converter */
r_static
r_int
id|pl2303_open
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_void
id|pl2303_close
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_static
r_void
id|pl2303_set_termios
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|termios
op_star
id|old
)paren
suffix:semicolon
r_static
r_int
id|pl2303_ioctl
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_void
id|pl2303_read_int_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|pl2303_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|pl2303_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|pl2303_write
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|pl2303_break_ctl
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|break_state
)paren
suffix:semicolon
multiline_comment|/* All of the device info needed for the PL2303 SIO serial converter */
DECL|variable|pl2303_device
r_static
r_struct
id|usb_serial_device_type
id|pl2303_device
op_assign
(brace
id|name
suffix:colon
l_string|&quot;PL-2303&quot;
comma
id|id_table
suffix:colon
id|id_table
comma
id|needs_interrupt_in
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* this device must have an interrupt in endpoint */
id|needs_bulk_in
suffix:colon
id|MUST_HAVE
comma
multiline_comment|/* this device must have a bulk in endpoint */
id|needs_bulk_out
suffix:colon
id|MUST_HAVE
comma
multiline_comment|/* this device must have a bulk out endpoint */
id|num_interrupt_in
suffix:colon
id|NUM_DONT_CARE
comma
id|num_bulk_in
suffix:colon
l_int|1
comma
id|num_bulk_out
suffix:colon
l_int|1
comma
id|num_ports
suffix:colon
l_int|1
comma
id|open
suffix:colon
id|pl2303_open
comma
id|close
suffix:colon
id|pl2303_close
comma
id|write
suffix:colon
id|pl2303_write
comma
id|ioctl
suffix:colon
id|pl2303_ioctl
comma
id|break_ctl
suffix:colon
id|pl2303_break_ctl
comma
id|set_termios
suffix:colon
id|pl2303_set_termios
comma
id|read_bulk_callback
suffix:colon
id|pl2303_read_bulk_callback
comma
id|read_int_callback
suffix:colon
id|pl2303_read_int_callback
comma
id|write_bulk_callback
suffix:colon
id|pl2303_write_bulk_callback
comma
)brace
suffix:semicolon
DECL|function|pl2303_write
r_static
r_int
id|pl2303_write
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|result
suffix:semicolon
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - port %d, %d bytes&quot;
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
id|port-&gt;tty
)paren
(brace
id|err
(paren
id|__FUNCTION__
l_string|&quot; - no tty???&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;write_urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - already writing&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|count
op_assign
(paren
id|count
OG
id|port-&gt;bulk_out_size
)paren
ques
c_cond
id|port-&gt;bulk_out_size
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
(paren
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|memcpy
(paren
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
id|usb_serial_debug_data
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|count
comma
id|port-&gt;write_urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|count
suffix:semicolon
id|port-&gt;write_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed submitting write urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
r_else
id|result
op_assign
id|count
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_void
DECL|function|pl2303_set_termios
id|pl2303_set_termios
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|termios
op_star
id|old_termios
)paren
(brace
multiline_comment|/* pl2303_set_termios */
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
r_int
id|cflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|7
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|baud
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dbg
(paren
l_string|&quot;pl2303_set_termios port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_rcvctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x21
comma
l_int|0xa1
comma
l_int|0
comma
l_int|0
comma
id|buf
comma
l_int|7
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0xa1:0x21:0:0  %d - %x %x %x %x %x %x %x&quot;
comma
id|i
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
comma
id|buf
(braket
l_int|4
)braket
comma
id|buf
(braket
l_int|5
)braket
comma
id|buf
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|1
comma
l_int|0x40
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
comma
l_int|0
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0x40:1:0:1  %d&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|CSIZE
)paren
(brace
r_switch
c_cond
(paren
id|cflag
op_amp
id|CSIZE
)paren
(brace
r_case
id|CS5
suffix:colon
id|buf
(braket
l_int|6
)braket
op_assign
l_int|5
suffix:semicolon
id|dbg
(paren
l_string|&quot;Setting CS5&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|buf
(braket
l_int|6
)braket
op_assign
l_int|6
suffix:semicolon
id|dbg
(paren
l_string|&quot;Setting CS6&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|buf
(braket
l_int|6
)braket
op_assign
l_int|7
suffix:semicolon
id|dbg
(paren
l_string|&quot;Setting CS7&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS8
suffix:colon
id|buf
(braket
l_int|6
)braket
op_assign
l_int|8
suffix:semicolon
id|dbg
(paren
l_string|&quot;Setting CS8&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
(paren
l_string|&quot;CSIZE was set but not CS5-CS8&quot;
)paren
suffix:semicolon
)brace
)brace
id|baud
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cflag
op_amp
id|CBAUD
)paren
(brace
r_case
id|B75
suffix:colon
id|baud
op_assign
l_int|75
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B150
suffix:colon
id|baud
op_assign
l_int|150
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B300
suffix:colon
id|baud
op_assign
l_int|300
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B600
suffix:colon
id|baud
op_assign
l_int|600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B1200
suffix:colon
id|baud
op_assign
l_int|1200
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B1800
suffix:colon
id|baud
op_assign
l_int|1800
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B2400
suffix:colon
id|baud
op_assign
l_int|2400
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B4800
suffix:colon
id|baud
op_assign
l_int|4800
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B9600
suffix:colon
id|baud
op_assign
l_int|9600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B19200
suffix:colon
id|baud
op_assign
l_int|19200
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B38400
suffix:colon
id|baud
op_assign
l_int|38400
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B57600
suffix:colon
id|baud
op_assign
l_int|57600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B115200
suffix:colon
id|baud
op_assign
l_int|115200
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B230400
suffix:colon
id|baud
op_assign
l_int|230400
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B460800
suffix:colon
id|baud
op_assign
l_int|460800
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
(paren
l_string|&quot;pl2303 driver does not support the baudrate requested (fix it)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|baud
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
id|baud
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|baud
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
id|baud
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|baud
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* For reference buf[4]=0 is 1 stop bits */
multiline_comment|/* For reference buf[4]=1 is 1.5 stop bits */
multiline_comment|/* For reference buf[4]=2 is 2 stop bits */
r_if
c_cond
(paren
id|cflag
op_amp
id|CSTOPB
)paren
(brace
id|buf
(braket
l_int|4
)braket
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
(brace
multiline_comment|/* For reference buf[5]=0 is none parity */
multiline_comment|/* For reference buf[5]=1 is odd parity */
multiline_comment|/* For reference buf[5]=2 is even parity */
multiline_comment|/* For reference buf[5]=3 is mark parity */
multiline_comment|/* For reference buf[5]=4 is space parity */
r_if
c_cond
(paren
id|cflag
op_amp
id|PARODD
)paren
(brace
id|buf
(braket
l_int|5
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|buf
(braket
l_int|5
)braket
op_assign
l_int|2
suffix:semicolon
)brace
)brace
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x20
comma
l_int|0x21
comma
l_int|0
comma
l_int|0
comma
id|buf
comma
l_int|7
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0x21:0x20:0:0  %d&quot;
comma
id|i
)paren
suffix:semicolon
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x22
comma
l_int|0x21
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0x21:0x22:1:0  %d&quot;
comma
id|i
)paren
suffix:semicolon
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x22
comma
l_int|0x21
comma
l_int|3
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0x21:0x22:3:0  %d&quot;
comma
id|i
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|buf
(braket
l_int|1
)braket
op_assign
id|buf
(braket
l_int|2
)braket
op_assign
id|buf
(braket
l_int|3
)braket
op_assign
id|buf
(braket
l_int|4
)braket
op_assign
id|buf
(braket
l_int|5
)braket
op_assign
id|buf
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_rcvctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x21
comma
l_int|0xa1
comma
l_int|0
comma
l_int|0
comma
id|buf
comma
l_int|7
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0xa1:0x21:0:0  %d - %x %x %x %x %x %x %x&quot;
comma
id|i
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
comma
id|buf
(braket
l_int|4
)braket
comma
id|buf
(braket
l_int|5
)braket
comma
id|buf
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|CRTSCTS
)paren
(brace
id|i
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x01
comma
l_int|0x40
comma
l_int|0x0
comma
l_int|0x41
comma
l_int|NULL
comma
l_int|0
comma
l_int|100
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;0x40:0x1:0x0:0x41  %d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|pl2303_open
r_static
r_int
id|pl2303_open
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|termios
id|tmp_termios
suffix:semicolon
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dbg
(paren
id|__FUNCTION__
l_string|&quot;-  port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
id|down
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
op_increment
id|port-&gt;open_count
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;active
)paren
(brace
id|port-&gt;active
op_assign
l_int|1
suffix:semicolon
DECL|macro|FISH
mdefine_line|#define FISH(a,b,c,d)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;result=usb_control_msg(serial-&gt;dev, usb_rcvctrlpipe(serial-&gt;dev,0),&t;&bslash;&n;&t;&t;&t;&t;       b, a, c, d, buf, 1, 100);&t;&t;&t;&bslash;&n;&t;&t;dbg(&quot;0x%x:0x%x:0x%x:0x%x  %d - %x&quot;,a,b,c,d,result,buf[0]);
DECL|macro|SOUP
mdefine_line|#define SOUP(a,b,c,d)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;result=usb_control_msg(serial-&gt;dev, usb_sndctrlpipe(serial-&gt;dev,0),&t;&bslash;&n;&t;&t;&t;&t;       b, a, c , d, NULL, 0, 100);&t;&t;&t;&bslash;&n;&t;&t;dbg(&quot;0x%x:0x%x:0x%x:0x%x  %d&quot;,a,b,c,d,result);
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8484
comma
l_int|0
)paren
suffix:semicolon
id|SOUP
(paren
l_int|0x40
comma
l_int|1
comma
l_int|0x0404
comma
l_int|0
)paren
suffix:semicolon
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8484
comma
l_int|0
)paren
suffix:semicolon
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8383
comma
l_int|0
)paren
suffix:semicolon
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8484
comma
l_int|0
)paren
suffix:semicolon
id|SOUP
(paren
l_int|0x40
comma
l_int|1
comma
l_int|0x0404
comma
l_int|1
)paren
suffix:semicolon
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8484
comma
l_int|0
)paren
suffix:semicolon
id|FISH
(paren
l_int|0xc0
comma
l_int|1
comma
l_int|0x8383
comma
l_int|0
)paren
suffix:semicolon
id|SOUP
(paren
l_int|0x40
comma
l_int|1
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|SOUP
(paren
l_int|0x40
comma
l_int|1
comma
l_int|1
comma
l_int|0xc0
)paren
suffix:semicolon
id|SOUP
(paren
l_int|0x40
comma
l_int|1
comma
l_int|2
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Setup termios */
op_star
(paren
id|port-&gt;tty-&gt;termios
)paren
op_assign
id|tty_std_termios
suffix:semicolon
id|port-&gt;tty-&gt;termios-&gt;c_cflag
op_assign
id|B9600
op_or
id|CS8
op_or
id|CREAD
op_or
id|HUPCL
op_or
id|CLOCAL
suffix:semicolon
id|pl2303_set_termios
(paren
id|port
comma
op_amp
id|tmp_termios
)paren
suffix:semicolon
singleline_comment|//FIXME: need to assert RTS and DTR if CRTSCTS off
id|port-&gt;read_urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed submitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
id|pl2303_close
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
id|port-&gt;interrupt_in_urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;interrupt_in_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed submitting interrupt urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
id|pl2303_close
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
)brace
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pl2303_close
r_static
r_void
id|pl2303_close
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
r_int
id|c_cflag
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
r_return
suffix:semicolon
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
id|down
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
op_decrement
id|port-&gt;open_count
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;open_count
op_le
l_int|0
)paren
(brace
id|c_cflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
r_if
c_cond
(paren
id|c_cflag
op_amp
id|HUPCL
)paren
(brace
singleline_comment|//FIXME: Do drop DTR
singleline_comment|//FIXME: Do drop RTS
)brace
multiline_comment|/* shutdown our urbs */
id|usb_unlink_urb
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
id|usb_unlink_urb
(paren
id|port-&gt;interrupt_in_urb
)paren
suffix:semicolon
id|port-&gt;active
op_assign
l_int|0
suffix:semicolon
id|port-&gt;open_count
op_assign
l_int|0
suffix:semicolon
)brace
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pl2303_ioctl
id|pl2303_ioctl
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
singleline_comment|// struct usb_serial *serial = port-&gt;serial;
singleline_comment|// __u16 urb_value=0; /* Will hold the new flags */
singleline_comment|// char buf[1];
singleline_comment|// int  ret, mask;
id|dbg
(paren
l_string|&quot;pl2303_sio ioctl 0x%04x&quot;
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Based on code from acm.c and others */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMGET
suffix:colon
id|dbg
(paren
l_string|&quot;TIOCMGET&quot;
)paren
suffix:semicolon
r_return
id|put_user
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCMBIS
suffix:colon
r_case
id|TIOCMBIC
suffix:colon
r_case
id|TIOCMSET
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* This is not an error - turns out the higher layers will do &n;&t;&t;&t; *  some ioctls itself (see comment above)&n;&t;&t;&t; */
id|dbg
(paren
l_string|&quot;pl2303_sio ioctl arg not supported - it was 0x%04x&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;pl2303_ioctl returning 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* pl2303_ioctl */
DECL|function|pl2303_break_ctl
r_static
r_void
id|pl2303_break_ctl
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
id|break_state
)paren
(brace
singleline_comment|//FIXME
)brace
r_static
r_void
DECL|function|pl2303_read_int_callback
id|pl2303_read_int_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_serial_port
op_star
id|port
op_assign
(paren
r_struct
id|usb_serial_port
op_star
)paren
id|urb-&gt;context
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
l_string|&quot;pl2303_read_int_callback&quot;
)paren
suffix:semicolon
singleline_comment|//unsigned char *data = urb-&gt;transfer_buffer;
singleline_comment|//int i;
singleline_comment|//ints auto restart...
r_if
c_cond
(paren
op_logical_neg
id|serial
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|urb-&gt;status
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usb_serial_debug_data
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|urb-&gt;actual_length
comma
id|urb-&gt;transfer_buffer
)paren
suffix:semicolon
macro_line|#if 0
singleline_comment|//FIXME need to update state of terminal lines variable
macro_line|#endif
r_return
suffix:semicolon
)brace
DECL|function|pl2303_read_bulk_callback
r_static
r_void
id|pl2303_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_serial_port
op_star
id|port
op_assign
(paren
r_struct
id|usb_serial_port
op_star
)paren
id|urb-&gt;context
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
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
r_return
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial
)paren
(brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - bad serial pointer, exiting&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* PL2303 mysteriously fails with -EPROTO reschedule the read */
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|urb-&gt;status
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed resubmitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usb_serial_debug_data
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|urb-&gt;actual_length
comma
id|data
)paren
suffix:semicolon
id|tty
op_assign
id|port-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;actual_length
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|urb-&gt;actual_length
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
(brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
id|tty_insert_flip_char
(paren
id|tty
comma
id|data
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tty_flip_buffer_push
(paren
id|tty
)paren
suffix:semicolon
)brace
multiline_comment|/* Schedule the next read*/
id|urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed resubmitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|pl2303_write_bulk_callback
r_static
r_void
id|pl2303_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_serial_port
op_star
id|port
op_assign
(paren
r_struct
id|usb_serial_port
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
r_return
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
multiline_comment|/* error in the urb, so we have to resubmit it */
r_if
c_cond
(paren
id|serial_paranoia_check
(paren
id|port-&gt;serial
comma
id|__FUNCTION__
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - Overflow in write&quot;
)paren
suffix:semicolon
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - nonzero write bulk status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
l_int|1
suffix:semicolon
id|port-&gt;write_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed resubmitting write urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|queue_task
c_func
(paren
op_amp
id|port-&gt;tqueue
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|pl2303_init
r_static
r_int
id|__init
id|pl2303_init
(paren
r_void
)paren
(brace
id|usb_serial_register
(paren
op_amp
id|pl2303_device
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pl2303_exit
r_static
r_void
id|__exit
id|pl2303_exit
(paren
r_void
)paren
(brace
id|usb_serial_deregister
(paren
op_amp
id|pl2303_device
)paren
suffix:semicolon
)brace
DECL|variable|pl2303_init
id|module_init
c_func
(paren
id|pl2303_init
)paren
suffix:semicolon
DECL|variable|pl2303_exit
id|module_exit
c_func
(paren
id|pl2303_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
eof
