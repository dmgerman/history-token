multiline_comment|/*&n; * USB IR Dongle driver&n; *&n; *&t;Copyright (C) 2001-2002&t;Greg Kroah-Hartman (greg@kroah.com)&n; *&t;Copyright (C) 2002&t;Gary Brubaker (xavyer@ix.netcom.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * This driver allows a USB IrDA device to be used as a &quot;dumb&quot; serial device.&n; * This can be useful if you do not have access to a full IrDA stack on the&n; * other side of the connection.  If you do have an IrDA stack on both devices,&n; * please use the usb-irda driver, as it contains the proper error checking and&n; * other goodness of a full IrDA stack.&n; *&n; * Portions of this driver were taken from drivers/net/irda/irda-usb.c, which&n; * was written by Roman Weissgaerber &lt;weissg@vienna.at&gt;, Dag Brattli&n; * &lt;dag@brattli.net&gt;, and Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * 2002_Mar_07&t;greg kh&n; *&t;moved some needed structures and #define values from the&n; *&t;net/irda/irda-usb.h file into our file, as we don&squot;t want to depend on&n; *&t;that codebase compiling correctly :)&n; *&n; * 2002_Jan_14  gb&n; *&t;Added module parameter to force specific number of XBOFs.&n; *&t;Added ir_xbof_change().&n; *&t;Reorganized read_bulk_callback error handling.&n; *&t;Switched from FILL_BULK_URB() to usb_fill_bulk_urb().&n; *&n; * 2001_Nov_08  greg kh&n; *&t;Changed the irda_usb_find_class_desc() function based on comments and&n; *&t;code from Martin Diehl.&n; *&n; * 2001_Nov_01&t;greg kh&n; *&t;Added support for more IrDA USB devices.&n; *&t;Added support for zero packet.  Added buffer override paramater, so&n; *&t;users can transfer larger packets at once if they wish.  Both patches&n; *&t;came from Dag Brattli &lt;dag@obexcode.com&gt;.&n; *&n; * 2001_Oct_07&t;greg kh&n; *&t;initial version released.&n; */
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
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.4&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB IR Dongle driver&quot;
multiline_comment|/* USB IrDA class spec information */
DECL|macro|USB_CLASS_IRDA
mdefine_line|#define USB_CLASS_IRDA&t;&t;0x02
DECL|macro|USB_DT_IRDA
mdefine_line|#define USB_DT_IRDA&t;&t;0x21
DECL|macro|IU_REQ_GET_CLASS_DESC
mdefine_line|#define IU_REQ_GET_CLASS_DESC&t;0x06
DECL|macro|SPEED_2400
mdefine_line|#define SPEED_2400&t;&t;0x01
DECL|macro|SPEED_9600
mdefine_line|#define SPEED_9600&t;&t;0x02
DECL|macro|SPEED_19200
mdefine_line|#define SPEED_19200&t;&t;0x03
DECL|macro|SPEED_38400
mdefine_line|#define SPEED_38400&t;&t;0x04
DECL|macro|SPEED_57600
mdefine_line|#define SPEED_57600&t;&t;0x05
DECL|macro|SPEED_115200
mdefine_line|#define SPEED_115200&t;&t;0x06
DECL|macro|SPEED_576000
mdefine_line|#define SPEED_576000&t;&t;0x07
DECL|macro|SPEED_1152000
mdefine_line|#define SPEED_1152000&t;&t;0x08
DECL|macro|SPEED_4000000
mdefine_line|#define SPEED_4000000&t;&t;0x09
DECL|struct|irda_class_desc
r_struct
id|irda_class_desc
(brace
DECL|member|bLength
id|u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdSpecRevision
id|u16
id|bcdSpecRevision
suffix:semicolon
DECL|member|bmDataSize
id|u8
id|bmDataSize
suffix:semicolon
DECL|member|bmWindowSize
id|u8
id|bmWindowSize
suffix:semicolon
DECL|member|bmMinTurnaroundTime
id|u8
id|bmMinTurnaroundTime
suffix:semicolon
DECL|member|wBaudRate
id|u16
id|wBaudRate
suffix:semicolon
DECL|member|bmAdditionalBOFs
id|u8
id|bmAdditionalBOFs
suffix:semicolon
DECL|member|bIrdaRateSniff
id|u8
id|bIrdaRateSniff
suffix:semicolon
DECL|member|bMaxUnicastList
id|u8
id|bMaxUnicastList
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* if overridden by the user, then use their value for the size of the read and&n; * write urbs */
DECL|variable|buffer_size
r_static
r_int
id|buffer_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if overridden by the user, then use the specified number of XBOFs */
DECL|variable|xbof
r_static
r_int
id|xbof
op_assign
op_minus
l_int|1
suffix:semicolon
r_static
r_int
id|ir_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|ir_open
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filep
)paren
suffix:semicolon
r_static
r_void
id|ir_close
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_struct
id|file
op_star
id|filep
)paren
suffix:semicolon
r_static
r_int
id|ir_write
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
id|ir_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|ir_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|ir_set_termios
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
suffix:semicolon
DECL|variable|ir_baud
r_static
id|u8
id|ir_baud
op_assign
l_int|0
suffix:semicolon
DECL|variable|ir_xbof
r_static
id|u8
id|ir_xbof
op_assign
l_int|0
suffix:semicolon
DECL|variable|ir_add_bof
r_static
id|u8
id|ir_add_bof
op_assign
l_int|0
suffix:semicolon
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
l_int|0x050f
comma
l_int|0x0180
)paren
)brace
comma
multiline_comment|/* KC Technology, KC-180 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x08e9
comma
l_int|0x0100
)paren
)brace
comma
multiline_comment|/* XTNDAccess */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x09c4
comma
l_int|0x0011
)paren
)brace
comma
multiline_comment|/* ACTiSys ACT-IR2000U */
(brace
id|USB_INTERFACE_INFO
(paren
id|USB_CLASS_APP_SPEC
comma
id|USB_CLASS_IRDA
comma
l_int|0
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
DECL|variable|ir_device
r_struct
id|usb_serial_device_type
id|ir_device
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;IR Dongle&quot;
comma
id|id_table
suffix:colon
id|id_table
comma
id|num_interrupt_in
suffix:colon
l_int|1
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
id|set_termios
suffix:colon
id|ir_set_termios
comma
id|startup
suffix:colon
id|ir_startup
comma
id|open
suffix:colon
id|ir_open
comma
id|close
suffix:colon
id|ir_close
comma
id|write
suffix:colon
id|ir_write
comma
id|write_bulk_callback
suffix:colon
id|ir_write_bulk_callback
comma
id|read_bulk_callback
suffix:colon
id|ir_read_bulk_callback
comma
)brace
suffix:semicolon
DECL|function|irda_usb_dump_class_desc
r_static
r_inline
r_void
id|irda_usb_dump_class_desc
c_func
(paren
r_struct
id|irda_class_desc
op_star
id|desc
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;bLength=%x&quot;
comma
id|desc-&gt;bLength
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bDescriptorType=%x&quot;
comma
id|desc-&gt;bDescriptorType
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bcdSpecRevision=%x&quot;
comma
id|desc-&gt;bcdSpecRevision
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bmDataSize=%x&quot;
comma
id|desc-&gt;bmDataSize
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bmWindowSize=%x&quot;
comma
id|desc-&gt;bmWindowSize
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bmMinTurnaroundTime=%d&quot;
comma
id|desc-&gt;bmMinTurnaroundTime
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;wBaudRate=%x&quot;
comma
id|desc-&gt;wBaudRate
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bmAdditionalBOFs=%x&quot;
comma
id|desc-&gt;bmAdditionalBOFs
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bIrdaRateSniff=%x&quot;
comma
id|desc-&gt;bIrdaRateSniff
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;bMaxUnicastList=%x&quot;
comma
id|desc-&gt;bMaxUnicastList
)paren
suffix:semicolon
)brace
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*&n; * Function irda_usb_find_class_desc(dev, ifnum)&n; *&n; *    Returns instance of IrDA class descriptor, or NULL if not found&n; *&n; * The class descriptor is some extra info that IrDA USB devices will&n; * offer to us, describing their IrDA characteristics. We will use that in&n; * irda_usb_init_qos()&n; *&n; * Based on the same function in drivers/net/irda/irda-usb.c&n; */
DECL|function|irda_usb_find_class_desc
r_static
r_struct
id|irda_class_desc
op_star
id|irda_usb_find_class_desc
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
)paren
(brace
r_struct
id|irda_class_desc
op_star
id|desc
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|desc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irda_class_desc
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|desc
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_class_desc
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|IU_REQ_GET_CLASS_DESC
comma
id|USB_DIR_IN
op_or
id|USB_TYPE_CLASS
op_or
id|USB_RECIP_INTERFACE
comma
l_int|0
comma
id|ifnum
comma
id|desc
comma
r_sizeof
(paren
op_star
id|desc
)paren
comma
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s -  ret=%d&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
r_sizeof
(paren
op_star
id|desc
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - class descriptor read %s (%d)&quot;
comma
id|__FUNCTION__
comma
(paren
id|ret
OL
l_int|0
)paren
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;too short&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|desc-&gt;bDescriptorType
op_ne
id|USB_DT_IRDA
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - bad class descriptor type&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|irda_usb_dump_class_desc
c_func
(paren
id|desc
)paren
suffix:semicolon
r_return
id|desc
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|desc
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ir_xbof_change
r_static
id|u8
id|ir_xbof_change
c_func
(paren
id|u8
id|xbof
)paren
(brace
id|u8
id|result
suffix:semicolon
multiline_comment|/* reference irda-usb.c */
r_switch
c_cond
(paren
id|xbof
)paren
(brace
r_case
l_int|48
suffix:colon
id|result
op_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|28
suffix:colon
r_case
l_int|24
suffix:colon
id|result
op_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_int|12
suffix:colon
id|result
op_assign
l_int|0x30
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
id|result
op_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|result
op_assign
l_int|0x50
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|result
op_assign
l_int|0x60
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|result
op_assign
l_int|0x70
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|result
op_assign
l_int|0x80
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|ir_startup
r_static
r_int
id|ir_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_struct
id|irda_class_desc
op_star
id|irda_desc
suffix:semicolon
id|irda_desc
op_assign
id|irda_usb_find_class_desc
(paren
id|serial-&gt;dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irda_desc
op_eq
l_int|NULL
)paren
(brace
id|err
(paren
l_string|&quot;IRDA class descriptor not found, device not bound&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;%s - Baud rates supported:%s%s%s%s%s%s%s%s%s&quot;
comma
id|__FUNCTION__
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0001
)paren
ques
c_cond
l_string|&quot; 2400&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0002
)paren
ques
c_cond
l_string|&quot; 9600&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0004
)paren
ques
c_cond
l_string|&quot; 19200&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0008
)paren
ques
c_cond
l_string|&quot; 38400&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0010
)paren
ques
c_cond
l_string|&quot; 57600&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0020
)paren
ques
c_cond
l_string|&quot; 115200&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0040
)paren
ques
c_cond
l_string|&quot; 576000&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0080
)paren
ques
c_cond
l_string|&quot; 1152000&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|irda_desc-&gt;wBaudRate
op_amp
l_int|0x0100
)paren
ques
c_cond
l_string|&quot; 4000000&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irda_desc-&gt;bmAdditionalBOFs
)paren
(brace
r_case
l_int|0x01
suffix:colon
id|ir_add_bof
op_assign
l_int|48
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|ir_add_bof
op_assign
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
id|ir_add_bof
op_assign
l_int|12
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08
suffix:colon
id|ir_add_bof
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|ir_add_bof
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20
suffix:colon
id|ir_add_bof
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
id|ir_add_bof
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|ir_add_bof
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
id|kfree
(paren
id|irda_desc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ir_open
r_static
r_int
id|ir_open
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
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|result
op_assign
l_int|0
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
id|buffer_size
)paren
(brace
multiline_comment|/* override the default buffer sizes */
id|buffer
op_assign
id|kmalloc
(paren
id|buffer_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|err
(paren
l_string|&quot;%s - out of memory.&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kfree
(paren
id|port-&gt;read_urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_buffer
op_assign
id|buffer
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_buffer_length
op_assign
id|buffer_size
suffix:semicolon
id|buffer
op_assign
id|kmalloc
(paren
id|buffer_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|err
(paren
l_string|&quot;%s - out of memory.&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kfree
(paren
id|port-&gt;write_urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer
op_assign
id|buffer
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|buffer_size
suffix:semicolon
id|port-&gt;bulk_out_size
op_assign
id|buffer_size
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
id|ir_read_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_flags
op_assign
id|USB_QUEUE_BULK
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
id|err
c_func
(paren
l_string|&quot;%s - failed submitting read urb, error %d&quot;
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
DECL|function|ir_close
r_static
r_void
id|ir_close
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
l_string|&quot;%s - port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
id|serial
op_assign
id|get_usb_serial
(paren
id|port
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;dev
)paren
(brace
multiline_comment|/* shutdown our bulk read */
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
)brace
)brace
DECL|function|ir_write
r_static
r_int
id|ir_write
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
r_char
op_star
id|transfer_buffer
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|transfer_size
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - port = %d, count = %d&quot;
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
id|port-&gt;tty
)paren
(brace
id|err
(paren
l_string|&quot;%s - no tty???&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
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
l_string|&quot;%s - already writing&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|transfer_buffer
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
id|transfer_size
op_assign
id|min
c_func
(paren
id|count
comma
id|port-&gt;bulk_out_size
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The first byte of the packet we send to the device contains an&n;&t; * inband header which indicates an additional number of BOFs and&n;&t; * a baud rate change.&n;&t; *&n;&t; * See section 5.4.2.2 of the USB IrDA spec.&n;&t; */
op_star
id|transfer_buffer
op_assign
id|ir_xbof
op_or
id|ir_baud
suffix:semicolon
op_increment
id|transfer_buffer
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
id|transfer_buffer
comma
id|buf
comma
id|transfer_size
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
id|transfer_buffer
comma
id|buf
comma
id|transfer_size
)paren
suffix:semicolon
)brace
id|usb_fill_bulk_urb
(paren
id|port-&gt;write_urb
comma
id|port-&gt;serial-&gt;dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;bulk_out_endpointAddress
)paren
comma
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|transfer_size
op_plus
l_int|1
comma
id|ir_write_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_flags
op_assign
id|USB_QUEUE_BULK
op_or
id|USB_ZERO_PACKET
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;write_urb
comma
id|GFP_ATOMIC
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
l_string|&quot;%s - failed submitting write urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_else
id|result
op_assign
id|transfer_size
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ir_write_bulk_callback
r_static
r_void
id|ir_write_bulk_callback
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
id|urb-&gt;status
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - nonzero write bulk status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
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
id|urb-&gt;transfer_buffer
)paren
suffix:semicolon
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
DECL|function|ir_read_bulk_callback
r_static
r_void
id|ir_read_bulk_callback
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
op_logical_neg
id|serial
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - bad serial pointer, exiting&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;open_count
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - port closed.&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|urb-&gt;status
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Successful */
multiline_comment|/*&n;&t;&t;&t; * The first byte of the packet we get from the device&n;&t;&t;&t; * contains a busy indicator and baud rate change.&n;&t;&t;&t; * See section 5.4.1.2 of the USB IrDA spec.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
op_star
id|data
op_amp
l_int|0x0f
)paren
OG
l_int|0
)paren
(brace
id|ir_baud
op_assign
op_star
id|data
op_amp
l_int|0x0f
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
multiline_comment|/*&n;&t;&t;&t; * Bypass flip-buffers, and feed the ldisc directly&n;&t;&t;&t; * due to our potentally large buffer size.  Since we&n;&t;&t;&t; * used to set low_latency, this is exactly what the&n;&t;&t;&t; * tty layer did anyway :)&n;&t;&t;&t; */
id|tty
op_assign
id|port-&gt;tty
suffix:semicolon
id|tty-&gt;ldisc
dot
id|receive_buf
c_func
(paren
id|tty
comma
id|data
op_plus
l_int|1
comma
l_int|NULL
comma
id|urb-&gt;actual_length
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * No break here.&n;&t;&t;&t; * We want to resubmit the urb so we can read&n;&t;&t;&t; * again.&n;&t;&t;&t; */
r_case
op_minus
id|EPROTO
suffix:colon
multiline_comment|/* taking inspiration from pl2303.c */
multiline_comment|/* Continue trying to always read */
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
id|ir_read_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_flags
op_assign
id|USB_QUEUE_BULK
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;read_urb
comma
id|GFP_ATOMIC
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
l_string|&quot;%s - failed resubmitting read urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - nonzero read bulk status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|ir_set_termios
r_static
r_void
id|ir_set_termios
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
r_char
op_star
id|transfer_buffer
suffix:semicolon
r_int
r_int
id|cflag
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
)brace
multiline_comment|/* All we can change is the baud rate */
r_if
c_cond
(paren
id|cflag
op_amp
id|CBAUD
)paren
(brace
id|dbg
(paren
l_string|&quot;%s - asking for baud %d&quot;
comma
id|__FUNCTION__
comma
id|tty_get_baud_rate
c_func
(paren
id|port-&gt;tty
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * FIXME, we should compare the baud request against the&n;&t;&t; * capability stated in the IR header that we got in the&n;&t;&t; * startup funtion.&n;&t;&t; */
r_switch
c_cond
(paren
id|cflag
op_amp
id|CBAUD
)paren
(brace
r_case
id|B2400
suffix:colon
id|ir_baud
op_assign
id|SPEED_2400
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
id|B9600
suffix:colon
id|ir_baud
op_assign
id|SPEED_9600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B19200
suffix:colon
id|ir_baud
op_assign
id|SPEED_19200
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B38400
suffix:colon
id|ir_baud
op_assign
id|SPEED_38400
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B57600
suffix:colon
id|ir_baud
op_assign
id|SPEED_57600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B115200
suffix:colon
id|ir_baud
op_assign
id|SPEED_115200
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B576000
suffix:colon
id|ir_baud
op_assign
id|SPEED_576000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B1152000
suffix:colon
id|ir_baud
op_assign
id|SPEED_1152000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B4000000
suffix:colon
id|ir_baud
op_assign
id|SPEED_4000000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xbof
op_eq
op_minus
l_int|1
)paren
(brace
id|ir_xbof
op_assign
id|ir_xbof_change
c_func
(paren
id|ir_add_bof
)paren
suffix:semicolon
)brace
r_else
(brace
id|ir_xbof
op_assign
id|ir_xbof_change
c_func
(paren
id|xbof
)paren
suffix:semicolon
)brace
multiline_comment|/* Notify the tty driver that the termios have changed. */
id|port-&gt;tty-&gt;ldisc
dot
id|set_termios
c_func
(paren
id|port-&gt;tty
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* FIXME need to check to see if our write urb is busy right&n;&t;&t; * now, or use a urb pool.&n;&t;&t; *&n;&t;&t; * send the baud change out on an &quot;empty&quot; data packet&n;&t;&t; */
id|transfer_buffer
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
op_star
id|transfer_buffer
op_assign
id|ir_xbof
op_or
id|ir_baud
suffix:semicolon
id|usb_fill_bulk_urb
(paren
id|port-&gt;write_urb
comma
id|port-&gt;serial-&gt;dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;bulk_out_endpointAddress
)paren
comma
id|port-&gt;write_urb-&gt;transfer_buffer
comma
l_int|1
comma
id|ir_write_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_flags
op_assign
id|USB_QUEUE_BULK
op_or
id|USB_ZERO_PACKET
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
(paren
id|port-&gt;write_urb
comma
id|GFP_KERNEL
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
l_string|&quot;%s - failed submitting write urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|ir_init
r_static
r_int
id|__init
id|ir_init
(paren
r_void
)paren
(brace
id|usb_serial_register
(paren
op_amp
id|ir_device
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
DECL|function|ir_exit
r_static
r_void
id|__exit
id|ir_exit
(paren
r_void
)paren
(brace
id|usb_serial_deregister
(paren
op_amp
id|ir_device
)paren
suffix:semicolon
)brace
DECL|variable|ir_init
id|module_init
c_func
(paren
id|ir_init
)paren
suffix:semicolon
DECL|variable|ir_exit
id|module_exit
c_func
(paren
id|ir_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
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
id|MODULE_PARM
c_func
(paren
id|xbof
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|xbof
comma
l_string|&quot;Force specific number of XBOFs&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|buffer_size
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|buffer_size
comma
l_string|&quot;Size of the transfer buffers&quot;
)paren
suffix:semicolon
eof
