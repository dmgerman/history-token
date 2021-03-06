multiline_comment|/*&n; * Silicon Laboratories CP2101/CP2102 USB to RS232 serial adaptor driver&n; *&n; * Copyright (C) 2005 Craig Shelley (craig@microtron.org.uk)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;usb-serial.h&quot;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.03&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;Silicon Labs CP2101/CP2102 RS232 serial adaptor driver&quot;
multiline_comment|/*&n; * Function Prototypes&n; */
r_static
r_int
id|cp2101_open
c_func
(paren
r_struct
id|usb_serial_port
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_cleanup
c_func
(paren
r_struct
id|usb_serial_port
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_close
c_func
(paren
r_struct
id|usb_serial_port
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_get_termios
c_func
(paren
r_struct
id|usb_serial_port
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_set_termios
c_func
(paren
r_struct
id|usb_serial_port
op_star
comma
r_struct
id|termios
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_break_ctl
c_func
(paren
r_struct
id|usb_serial_port
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|cp2101_startup
(paren
r_struct
id|usb_serial
op_star
)paren
suffix:semicolon
r_static
r_void
id|cp2101_shutdown
c_func
(paren
r_struct
id|usb_serial
op_star
)paren
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|id_table
r_static
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
l_int|0x10c4
comma
l_int|0xea60
)paren
)brace
comma
multiline_comment|/*Silicon labs factory default*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x10ab
comma
l_int|0x10c5
)paren
)brace
comma
multiline_comment|/*Siemens MC60 Cable*/
(brace
)brace
multiline_comment|/* Terminating Entry*/
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|id_table
)paren
suffix:semicolon
DECL|variable|cp2101_driver
r_static
r_struct
id|usb_driver
id|cp2101_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;CP2101&quot;
comma
dot
id|probe
op_assign
id|usb_serial_probe
comma
dot
id|disconnect
op_assign
id|usb_serial_disconnect
comma
dot
id|id_table
op_assign
id|id_table
comma
)brace
suffix:semicolon
DECL|variable|cp2101_device
r_static
r_struct
id|usb_serial_device_type
id|cp2101_device
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;CP2101&quot;
comma
dot
id|id_table
op_assign
id|id_table
comma
dot
id|num_interrupt_in
op_assign
l_int|0
comma
dot
id|num_bulk_in
op_assign
l_int|0
comma
dot
id|num_bulk_out
op_assign
l_int|0
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|open
op_assign
id|cp2101_open
comma
dot
id|close
op_assign
id|cp2101_close
comma
dot
id|break_ctl
op_assign
id|cp2101_break_ctl
comma
dot
id|set_termios
op_assign
id|cp2101_set_termios
comma
dot
id|attach
op_assign
id|cp2101_startup
comma
dot
id|shutdown
op_assign
id|cp2101_shutdown
comma
)brace
suffix:semicolon
multiline_comment|/*Config request types*/
DECL|macro|REQTYPE_HOST_TO_DEVICE
mdefine_line|#define REQTYPE_HOST_TO_DEVICE&t;0x41
DECL|macro|REQTYPE_DEVICE_TO_HOST
mdefine_line|#define REQTYPE_DEVICE_TO_HOST&t;0xc1
multiline_comment|/*Config SET requests. To GET, add 1 to the request number*/
DECL|macro|CP2101_UART
mdefine_line|#define CP2101_UART &t;&t;0x00&t;/*Enable / Disable*/
DECL|macro|CP2101_BAUDRATE
mdefine_line|#define CP2101_BAUDRATE&t;&t;0x01&t;/*(BAUD_RATE_GEN_FREQ / baudrate)*/
DECL|macro|CP2101_BITS
mdefine_line|#define CP2101_BITS&t;&t;0x03&t;/*0x(0)(data bits)(parity)(stop bits)*/
DECL|macro|CP2101_BREAK
mdefine_line|#define CP2101_BREAK&t;&t;0x05&t;/*On / Off*/
DECL|macro|CP2101_DTRRTS
mdefine_line|#define CP2101_DTRRTS&t;&t;0x07&t;/*101 / 202  ???*/
DECL|macro|CP2101_CONFIG_16
mdefine_line|#define CP2101_CONFIG_16&t;0x13&t;/*16 bytes of config data ???*/
DECL|macro|CP2101_CONFIG_6
mdefine_line|#define CP2101_CONFIG_6&t;&t;0x19&t;/*6 bytes of config data ???*/
multiline_comment|/*CP2101_UART*/
DECL|macro|UART_ENABLE
mdefine_line|#define UART_ENABLE&t;&t;0x0001
DECL|macro|UART_DISABLE
mdefine_line|#define UART_DISABLE&t;&t;0x0000
multiline_comment|/*CP2101_BAUDRATE*/
DECL|macro|BAUD_RATE_GEN_FREQ
mdefine_line|#define BAUD_RATE_GEN_FREQ&t;0x384000
multiline_comment|/*CP2101_BITS*/
DECL|macro|BITS_DATA_MASK
mdefine_line|#define BITS_DATA_MASK&t;&t;0X0f00
DECL|macro|BITS_DATA_6
mdefine_line|#define BITS_DATA_6&t;&t;0X0600
DECL|macro|BITS_DATA_7
mdefine_line|#define BITS_DATA_7&t;&t;0X0700
DECL|macro|BITS_DATA_8
mdefine_line|#define BITS_DATA_8&t;&t;0X0800
DECL|macro|BITS_DATA_9
mdefine_line|#define BITS_DATA_9&t;&t;0X0900
DECL|macro|BITS_PARITY_MASK
mdefine_line|#define BITS_PARITY_MASK&t;0x00f0
DECL|macro|BITS_PARITY_NONE
mdefine_line|#define BITS_PARITY_NONE&t;0x0000
DECL|macro|BITS_PARITY_ODD
mdefine_line|#define BITS_PARITY_ODD&t;&t;0x0010
DECL|macro|BITS_PARITY_EVEN
mdefine_line|#define BITS_PARITY_EVEN&t;0x0020
DECL|macro|BITS_PARITY_MARK
mdefine_line|#define BITS_PARITY_MARK&t;0x0030
DECL|macro|BITS_PARITY_SPACE
mdefine_line|#define BITS_PARITY_SPACE&t;0x0040
DECL|macro|BITS_STOP_MASK
mdefine_line|#define BITS_STOP_MASK&t;&t;0x000f
DECL|macro|BITS_STOP_1
mdefine_line|#define BITS_STOP_1&t;&t;0x0000
DECL|macro|BITS_STOP_1_5
mdefine_line|#define BITS_STOP_1_5&t;&t;0x0001
DECL|macro|BITS_STOP_2
mdefine_line|#define BITS_STOP_2&t;&t;0x0002
DECL|macro|BREAK_ON
mdefine_line|#define BREAK_ON&t;&t;0x0000
DECL|macro|BREAK_OFF
mdefine_line|#define BREAK_OFF&t;&t;0x0001
DECL|function|cp2101_get_config
r_static
r_int
id|cp2101_get_config
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
id|u8
id|request
)paren
(brace
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
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_int
id|result
comma
id|i
suffix:semicolon
multiline_comment|/*For get requests, the request number must be incremented*/
id|request
op_increment
suffix:semicolon
multiline_comment|/*Issue the request, attempting to read 4 bytes*/
id|result
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
id|request
comma
id|REQTYPE_DEVICE_TO_HOST
comma
l_int|0x0000
comma
l_int|0
comma
id|buf
comma
l_int|4
comma
l_int|300
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - Unable to send config request, &quot;
l_string|&quot;request=0x%x result=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|request
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*Assemble each byte read into an integer value*/
id|value
op_assign
l_int|0
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
l_int|4
op_logical_and
id|i
OL
id|result
suffix:semicolon
id|i
op_increment
)paren
id|value
op_or_assign
(paren
id|buf
(braket
id|i
)braket
op_lshift
(paren
id|i
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot; %s - request=0x%x result=%d value=0x%x&quot;
comma
id|__FUNCTION__
comma
id|request
comma
id|result
comma
id|value
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|cp2101_set_config
r_static
r_int
id|cp2101_set_config
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
id|u8
id|request
comma
id|u16
id|value
)paren
(brace
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|serial-&gt;dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
comma
id|request
comma
id|REQTYPE_HOST_TO_DEVICE
comma
id|value
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|300
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - Unable to send config request, &quot;
l_string|&quot;request=0x%x value=0x%x result=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|request
comma
id|value
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot; %s - request=0x%x value=0x%x result=%d&quot;
comma
id|__FUNCTION__
comma
id|request
comma
id|value
comma
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cp2101_open
r_static
r_int
id|cp2101_open
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
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_UART
comma
id|UART_ENABLE
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - Unable to enable UART&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
multiline_comment|/* Start reading from the device */
id|usb_fill_bulk_urb
(paren
id|port-&gt;read_urb
comma
id|serial-&gt;dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|serial-&gt;dev
comma
id|port-&gt;bulk_in_endpointAddress
)paren
comma
id|port-&gt;read_urb-&gt;transfer_buffer
comma
id|port-&gt;read_urb-&gt;transfer_buffer_length
comma
id|serial-&gt;type-&gt;read_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;read_urb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - failed resubmitting read urb, &quot;
l_string|&quot;error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*Configure the termios structure*/
id|cp2101_get_termios
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cp2101_cleanup
r_static
r_void
id|cp2101_cleanup
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;dev
)paren
(brace
multiline_comment|/* shutdown any bulk reads that might be going on */
r_if
c_cond
(paren
id|serial-&gt;num_bulk_out
)paren
id|usb_kill_urb
c_func
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;num_bulk_in
)paren
id|usb_kill_urb
c_func
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
)brace
)brace
DECL|function|cp2101_close
r_static
r_void
id|cp2101_close
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
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
multiline_comment|/* shutdown our urbs */
id|dbg
c_func
(paren
l_string|&quot;%s - shutting down urbs&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_UART
comma
id|UART_DISABLE
)paren
suffix:semicolon
)brace
multiline_comment|/* cp2101_get_termios*/
multiline_comment|/* Reads the baud rate, data bits, parity and stop bits from the device*/
multiline_comment|/* Corrects any unsupported values*/
multiline_comment|/* Configures the termios structure to reflect the state of the device*/
DECL|function|cp2101_get_termios
r_static
r_void
id|cp2101_get_termios
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_int
r_int
id|cflag
suffix:semicolon
r_int
id|baud
suffix:semicolon
r_int
id|bits
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|port-&gt;tty
)paren
op_logical_or
(paren
op_logical_neg
id|port-&gt;tty-&gt;termios
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - no tty structures&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
id|baud
op_assign
id|cp2101_get_config
c_func
(paren
id|port
comma
id|CP2101_BAUDRATE
)paren
suffix:semicolon
multiline_comment|/*Convert to baudrate*/
r_if
c_cond
(paren
id|baud
)paren
id|baud
op_assign
id|BAUD_RATE_GEN_FREQ
op_div
id|baud
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - baud rate = %d&quot;
comma
id|__FUNCTION__
comma
id|baud
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|CBAUD
suffix:semicolon
r_switch
c_cond
(paren
id|baud
)paren
(brace
multiline_comment|/* The baud rates which are commented out below&n;&t;&t; * appear to be supported by the device&n;&t;&t; * but are non-standard&n;&t;&t; */
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
l_int|1800
suffix:colon
id|cflag
op_or_assign
id|B1800
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
multiline_comment|/*case 7200:&t;cflag |= B7200;&t;&t;break;*/
r_case
l_int|9600
suffix:colon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case 14400:&t;cflag |= B14400;&t;break;*/
r_case
l_int|19200
suffix:colon
id|cflag
op_or_assign
id|B19200
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case 28800:&t;cflag |= B28800;&t;break;*/
r_case
l_int|38400
suffix:colon
id|cflag
op_or_assign
id|B38400
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case 55854:&t;cflag |= B55054;&t;break;*/
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
multiline_comment|/*case 127117:&t;cflag |= B127117;&t;break;*/
r_case
l_int|230400
suffix:colon
id|cflag
op_or_assign
id|B230400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|460800
suffix:colon
id|cflag
op_or_assign
id|B460800
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|921600
suffix:colon
id|cflag
op_or_assign
id|B921600
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case 3686400:&t;cflag |= B3686400;&t;break;*/
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Baud rate is not supported, &quot;
l_string|&quot;using 9600 baud&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BAUDRATE
comma
(paren
id|BAUD_RATE_GEN_FREQ
op_div
l_int|9600
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|bits
op_assign
id|cp2101_get_config
c_func
(paren
id|port
comma
id|CP2101_BITS
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|CSIZE
suffix:semicolon
r_switch
c_cond
(paren
id|bits
op_amp
id|BITS_DATA_MASK
)paren
(brace
r_case
id|BITS_DATA_6
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 6&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CS6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_DATA_7
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 7&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CS7
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_DATA_8
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 8&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CS8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_DATA_9
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 9 (not supported, &quot;
l_string|&quot;using 8 data bits)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CS8
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_DATA_MASK
suffix:semicolon
id|bits
op_or_assign
id|BITS_DATA_8
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Unknown number of data bits, &quot;
l_string|&quot;using 8&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CS8
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_DATA_MASK
suffix:semicolon
id|bits
op_or_assign
id|BITS_DATA_8
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|bits
op_amp
id|BITS_PARITY_MASK
)paren
(brace
r_case
id|BITS_PARITY_NONE
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = NONE&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|PARENB
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_PARITY_ODD
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = ODD&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
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
id|BITS_PARITY_EVEN
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = EVEN&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|PARODD
suffix:semicolon
id|cflag
op_or_assign
id|PARENB
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_PARITY_MARK
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = MARK (not supported, &quot;
l_string|&quot;disabling parity)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|PARENB
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_PARITY_MASK
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_PARITY_SPACE
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = SPACE (not supported, &quot;
l_string|&quot;disabling parity)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|PARENB
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_PARITY_MASK
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Unknown parity mode, &quot;
l_string|&quot;disabling parity&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|PARENB
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_PARITY_MASK
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cflag
op_and_assign
op_complement
id|CSTOPB
suffix:semicolon
r_switch
c_cond
(paren
id|bits
op_amp
id|BITS_STOP_MASK
)paren
(brace
r_case
id|BITS_STOP_1
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - stop bits = 1&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_STOP_1_5
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - stop bits = 1.5 (not supported, &quot;
l_string|&quot;using 1 stop bit&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_STOP_MASK
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BITS_STOP_2
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - stop bits = 2&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|cflag
op_or_assign
id|CSTOPB
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Unknown number of stop bits, &quot;
l_string|&quot;using 1 stop bit&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_STOP_MASK
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|port-&gt;tty-&gt;termios-&gt;c_cflag
op_assign
id|cflag
suffix:semicolon
)brace
DECL|function|cp2101_set_termios
r_static
r_void
id|cp2101_set_termios
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
r_int
r_int
id|cflag
comma
id|old_cflag
op_assign
l_int|0
suffix:semicolon
r_int
id|baud
op_assign
l_int|0
suffix:semicolon
r_int
id|bits
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|port-&gt;tty
)paren
op_logical_or
(paren
op_logical_neg
id|port-&gt;tty-&gt;termios
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - no tty structures&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
multiline_comment|/* check that they really want us to change something */
r_if
c_cond
(paren
id|old_termios
)paren
(brace
r_if
c_cond
(paren
(paren
id|cflag
op_eq
id|old_termios-&gt;c_cflag
)paren
op_logical_and
(paren
id|RELEVANT_IFLAG
c_func
(paren
id|port-&gt;tty-&gt;termios-&gt;c_iflag
)paren
op_eq
id|RELEVANT_IFLAG
c_func
(paren
id|old_termios-&gt;c_iflag
)paren
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - nothing to change...&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|old_cflag
op_assign
id|old_termios-&gt;c_cflag
suffix:semicolon
)brace
multiline_comment|/* If the baud rate is to be updated*/
r_if
c_cond
(paren
(paren
id|cflag
op_amp
id|CBAUD
)paren
op_ne
(paren
id|old_cflag
op_amp
id|CBAUD
)paren
)paren
(brace
r_switch
c_cond
(paren
id|cflag
op_amp
id|CBAUD
)paren
(brace
multiline_comment|/* The baud rates which are commented out below&n;&t;&t;&t; * appear to be supported by the device&n;&t;&t;&t; * but are non-standard&n;&t;&t;&t; */
r_case
id|B0
suffix:colon
id|baud
op_assign
l_int|0
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
multiline_comment|/*case B7200:&t;baud = 7200;&t;break;*/
r_case
id|B9600
suffix:colon
id|baud
op_assign
l_int|9600
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*ase B14400:&t;baud = 14400;&t;break;*/
r_case
id|B19200
suffix:colon
id|baud
op_assign
l_int|19200
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case B28800:&t;baud = 28800;&t;break;*/
r_case
id|B38400
suffix:colon
id|baud
op_assign
l_int|38400
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case B55854:&t;baud = 55054;&t;break;*/
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
multiline_comment|/*case B127117:&t;baud = 127117;&t;break;*/
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
r_case
id|B921600
suffix:colon
id|baud
op_assign
l_int|921600
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case B3686400:&t;baud = 3686400;&t;break;*/
r_default
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;cp2101 driver does not &quot;
l_string|&quot;support the baudrate requested&bslash;n&quot;
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
id|dbg
c_func
(paren
l_string|&quot;%s - Setting baud rate to %d baud&quot;
comma
id|__FUNCTION__
comma
id|baud
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BAUDRATE
comma
(paren
id|BAUD_RATE_GEN_FREQ
op_div
id|baud
)paren
)paren
)paren
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;Baud rate requested not &quot;
l_string|&quot;supported by device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*If the number of data bits is to be updated*/
r_if
c_cond
(paren
(paren
id|cflag
op_amp
id|CSIZE
)paren
op_ne
(paren
id|old_cflag
op_amp
id|CSIZE
)paren
)paren
(brace
id|bits
op_assign
id|cp2101_get_config
c_func
(paren
id|port
comma
id|CP2101_BITS
)paren
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_DATA_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|cflag
op_amp
id|CSIZE
)paren
(brace
r_case
id|CS6
suffix:colon
id|bits
op_or_assign
id|BITS_DATA_6
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 6&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|bits
op_or_assign
id|BITS_DATA_7
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 7&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS8
suffix:colon
id|bits
op_or_assign
id|BITS_DATA_8
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - data bits = 8&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*case CS9:&n;&t;&t;&t; &t;bits |= BITS_DATA_9;&n;&t;&t;&t;&t;dbg(&quot;%s - data bits = 9&quot;, __FUNCTION__);&n;&t;&t;&t;&t;break;*/
r_default
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;cp2101 driver does not &quot;
l_string|&quot;support the number of bits requested,&quot;
l_string|&quot; using 8 bit mode&bslash;n&quot;
)paren
suffix:semicolon
id|bits
op_or_assign
id|BITS_DATA_8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
)paren
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;Number of data bits requested &quot;
l_string|&quot;not supported by device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cflag
op_amp
(paren
id|PARENB
op_or
id|PARODD
)paren
)paren
op_ne
(paren
id|old_cflag
op_amp
(paren
id|PARENB
op_or
id|PARODD
)paren
)paren
)paren
(brace
id|bits
op_assign
id|cp2101_get_config
c_func
(paren
id|port
comma
id|CP2101_BITS
)paren
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_PARITY_MASK
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
(brace
r_if
c_cond
(paren
id|cflag
op_amp
id|PARODD
)paren
(brace
id|bits
op_or_assign
id|BITS_PARITY_ODD
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = ODD&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_else
(brace
id|bits
op_or_assign
id|BITS_PARITY_EVEN
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - parity = EVEN&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
)paren
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;Parity mode not supported &quot;
l_string|&quot;by device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cflag
op_amp
id|CSTOPB
)paren
op_ne
(paren
id|old_cflag
op_amp
id|CSTOPB
)paren
)paren
(brace
id|bits
op_assign
id|cp2101_get_config
c_func
(paren
id|port
comma
id|CP2101_BITS
)paren
suffix:semicolon
id|bits
op_and_assign
op_complement
id|BITS_STOP_MASK
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|CSTOPB
)paren
(brace
id|bits
op_or_assign
id|BITS_STOP_2
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - stop bits = 2&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_else
(brace
id|bits
op_or_assign
id|BITS_STOP_1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - stop bits = 1&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BITS
comma
id|bits
)paren
)paren
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;Number of stop bits requested &quot;
l_string|&quot;not supported by device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|cp2101_break_ctl
r_static
r_void
id|cp2101_break_ctl
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
id|u16
id|state
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|break_state
op_eq
l_int|0
)paren
id|state
op_assign
id|BREAK_OFF
suffix:semicolon
r_else
id|state
op_assign
id|BREAK_ON
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - turning break %s&quot;
comma
id|__FUNCTION__
comma
id|state
op_eq
id|BREAK_OFF
ques
c_cond
l_string|&quot;off&quot;
suffix:colon
l_string|&quot;on&quot;
)paren
suffix:semicolon
id|cp2101_set_config
c_func
(paren
id|port
comma
id|CP2101_BREAK
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|cp2101_startup
r_static
r_int
id|cp2101_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
multiline_comment|/*CP2101 buffers behave strangely unless device is reset*/
id|usb_reset_device
c_func
(paren
id|serial-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cp2101_shutdown
r_static
r_void
id|cp2101_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_int
id|i
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* stop reads and writes on all ports */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|serial-&gt;num_ports
suffix:semicolon
op_increment
id|i
)paren
(brace
id|cp2101_cleanup
c_func
(paren
id|serial-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|cp2101_init
r_static
r_int
id|__init
id|cp2101_init
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|usb_serial_register
c_func
(paren
op_amp
id|cp2101_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/*Failed to register*/
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|cp2101_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
multiline_comment|/*Failed to register*/
id|usb_serial_deregister
c_func
(paren
op_amp
id|cp2101_device
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*Success*/
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
DECL|function|cp2101_exit
r_static
r_void
id|__exit
id|cp2101_exit
(paren
r_void
)paren
(brace
id|usb_deregister
(paren
op_amp
id|cp2101_driver
)paren
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|cp2101_device
)paren
suffix:semicolon
)brace
DECL|variable|cp2101_init
id|module_init
c_func
(paren
id|cp2101_init
)paren
suffix:semicolon
DECL|variable|cp2101_exit
id|module_exit
c_func
(paren
id|cp2101_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
DECL|variable|DRIVER_VERSION
id|MODULE_VERSION
c_func
(paren
id|DRIVER_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_bool
comma
id|S_IRUGO
op_or
id|S_IWUSR
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Enable verbose debugging messages&quot;
)paren
suffix:semicolon
eof
