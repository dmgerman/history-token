multiline_comment|/*&n; * USB Compaq iPAQ driver&n; *&n; *&t;Copyright (C) 2001 - 2002&n; *&t;    Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * (12/12/2002) ganesh&n; * &t;Added support for practically all devices supported by ActiveSync&n; * &t;on Windows. Thanks to Wes Cilldhaire &lt;billybobjoehenrybob@hotmail.com&gt;.&n; *&n; * (26/11/2002) ganesh&n; * &t;Added insmod options to specify product and vendor id.&n; * &t;Use modprobe ipaq vendor=0xfoo product=0xbar&n; *&n; * (26/7/2002) ganesh&n; * &t;Fixed up broken error handling in ipaq_open. Retry the &quot;kickstart&quot;&n; * &t;packet much harder - this drastically reduces connection failures.&n; *&n; * (30/4/2002) ganesh&n; * &t;Added support for the Casio EM500. Completely untested. Thanks&n; * &t;to info from Nathan &lt;wfilardo@fuse.net&gt;&n; *&n; * (19/3/2002) ganesh&n; *&t;Don&squot;t submit urbs while holding spinlocks. Not strictly necessary&n; *&t;in 2.5.x.&n; *&n; * (8/3/2002) ganesh&n; * &t;The ipaq sometimes emits a &squot;&bslash;0&squot; before the CLIENT string. At this&n; * &t;point of time, the ppp ldisc is not yet attached to the tty, so&n; * &t;n_tty echoes &quot;^ &quot; to the ipaq, which messes up the chat. In 2.5.6-pre2&n; * &t;this causes a panic because echo_char() tries to sleep in interrupt&n; * &t;context.&n; * &t;The fix is to tell the upper layers that this is a raw device so that&n; * &t;echoing is suppressed. Thanks to Lyle Lindholm for a detailed bug&n; * &t;report.&n; *&n; * (25/2/2002) ganesh&n; * &t;Added support for the HP Jornada 548 and 568. Completely untested.&n; * &t;Thanks to info from Heath Robinson and Arieh Davidoff.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;usb-serial.h&quot;
macro_line|#include &quot;ipaq.h&quot;
DECL|macro|KP_RETRIES
mdefine_line|#define KP_RETRIES&t;100
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.5&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB PocketPC PDA driver&quot;
DECL|variable|product
DECL|variable|vendor
r_static
id|__u16
id|product
comma
id|vendor
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
multiline_comment|/* Function prototypes for an ipaq */
r_static
r_int
id|ipaq_open
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
id|ipaq_close
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
r_int
id|ipaq_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|ipaq_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|ipaq_write
c_func
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
r_int
id|ipaq_write_bulk
c_func
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
id|ipaq_write_gather
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|ipaq_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|ipaq_write_bulk_callback
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|ipaq_write_room
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|ipaq_chars_in_buffer
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|ipaq_destroy_lists
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|variable|ipaq_id_table
r_static
r_struct
id|usb_device_id
id|ipaq_id_table
(braket
)braket
op_assign
(brace
multiline_comment|/* The first entry is a placeholder for the insmod-specified device */
(brace
id|USB_DEVICE
c_func
(paren
id|COMPAQ_VENDOR_ID
comma
id|COMPAQ_IPAQ_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ASKEY_VENDOR_ID
comma
id|ASKEY_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|BCOM_VENDOR_ID
comma
id|BCOM_0065_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|BCOM_VENDOR_ID
comma
id|BCOM_0066_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|BCOM_VENDOR_ID
comma
id|BCOM_0067_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|CASIO_VENDOR_ID
comma
id|CASIO_2001_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|CASIO_VENDOR_ID
comma
id|CASIO_EM500_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|COMPAQ_VENDOR_ID
comma
id|COMPAQ_IPAQ_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|COMPAQ_VENDOR_ID
comma
id|COMPAQ_0032_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|DELL_VENDOR_ID
comma
id|DELL_AXIM_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|FSC_VENDOR_ID
comma
id|FSC_LOOX_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_JORNADA_548_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_JORNADA_568_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_2016_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_2116_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_2216_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_3016_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_3116_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_3216_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_4016_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_4116_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_4216_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_5016_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_5116_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HP_VENDOR_ID
comma
id|HP_5216_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|LINKUP_VENDOR_ID
comma
id|LINKUP_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|MICROSOFT_VENDOR_ID
comma
id|MICROSOFT_00CE_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|PORTATEC_VENDOR_ID
comma
id|PORTATEC_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ROVER_VENDOR_ID
comma
id|ROVER_P5_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|SAGEM_VENDOR_ID
comma
id|SAGEM_WIRELESS_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|SOCKET_VENDOR_ID
comma
id|SOCKET_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|TOSHIBA_VENDOR_ID
comma
id|TOSHIBA_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|TOSHIBA_VENDOR_ID
comma
id|TOSHIBA_E310_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|TOSHIBA_VENDOR_ID
comma
id|TOSHIBA_E740_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|TOSHIBA_VENDOR_ID
comma
id|TOSHIBA_E335_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|HTC_VENDOR_ID
comma
id|HTC_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|NEC_VENDOR_ID
comma
id|NEC_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ASUS_VENDOR_ID
comma
id|ASUS_A600_PRODUCT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ASUS_VENDOR_ID
comma
id|ASUS_A620_PRODUCT_ID
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
id|ipaq_id_table
)paren
suffix:semicolon
DECL|variable|ipaq_driver
r_static
r_struct
id|usb_driver
id|ipaq_driver
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
l_string|&quot;ipaq&quot;
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
id|ipaq_id_table
comma
)brace
suffix:semicolon
multiline_comment|/* All of the device info needed for the Compaq iPAQ */
DECL|variable|ipaq_device
r_static
r_struct
id|usb_serial_device_type
id|ipaq_device
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
l_string|&quot;PocketPC PDA&quot;
comma
dot
id|id_table
op_assign
id|ipaq_id_table
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
l_int|1
comma
dot
id|num_bulk_out
op_assign
l_int|1
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|open
op_assign
id|ipaq_open
comma
dot
id|close
op_assign
id|ipaq_close
comma
dot
id|attach
op_assign
id|ipaq_startup
comma
dot
id|shutdown
op_assign
id|ipaq_shutdown
comma
dot
id|write
op_assign
id|ipaq_write
comma
dot
id|write_room
op_assign
id|ipaq_write_room
comma
dot
id|chars_in_buffer
op_assign
id|ipaq_chars_in_buffer
comma
dot
id|read_bulk_callback
op_assign
id|ipaq_read_bulk_callback
comma
dot
id|write_bulk_callback
op_assign
id|ipaq_write_bulk_callback
comma
)brace
suffix:semicolon
DECL|variable|write_list_lock
r_static
id|spinlock_t
id|write_list_lock
suffix:semicolon
DECL|variable|bytes_in
r_static
r_int
id|bytes_in
suffix:semicolon
DECL|variable|bytes_out
r_static
r_int
id|bytes_out
suffix:semicolon
DECL|function|ipaq_open
r_static
r_int
id|ipaq_open
c_func
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
r_struct
id|ipaq_private
op_star
id|priv
suffix:semicolon
r_struct
id|ipaq_packet
op_star
id|pkt
suffix:semicolon
r_int
id|i
comma
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|retries
op_assign
id|KP_RETRIES
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
id|bytes_in
op_assign
l_int|0
suffix:semicolon
id|bytes_out
op_assign
l_int|0
suffix:semicolon
id|priv
op_assign
(paren
r_struct
id|ipaq_private
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipaq_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s - Out of memory&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|usb_set_serial_port_data
c_func
(paren
id|port
comma
id|priv
)paren
suffix:semicolon
id|priv-&gt;active
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;queue_len
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|priv-&gt;queue
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|priv-&gt;freelist
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
id|URBDATA_QUEUE_MAX
op_div
id|PACKET_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pkt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipaq_packet
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt
op_eq
l_int|NULL
)paren
(brace
r_goto
id|enomem
suffix:semicolon
)brace
id|pkt-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|PACKET_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|pkt
)paren
suffix:semicolon
r_goto
id|enomem
suffix:semicolon
)brace
id|pkt-&gt;len
op_assign
l_int|0
suffix:semicolon
id|pkt-&gt;written
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|pkt-&gt;list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|pkt-&gt;list
comma
op_amp
id|priv-&gt;freelist
)paren
suffix:semicolon
id|priv-&gt;free_len
op_add_assign
id|PACKET_SIZE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Force low latency on. This will immediately push data to the line&n;&t; * discipline instead of queueing.&n;&t; */
id|port-&gt;tty-&gt;low_latency
op_assign
l_int|1
suffix:semicolon
id|port-&gt;tty-&gt;raw
op_assign
l_int|1
suffix:semicolon
id|port-&gt;tty-&gt;real_raw
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Lose the small buffers usbserial provides. Make larger ones.&n;&t; */
id|kfree
c_func
(paren
id|port-&gt;bulk_in_buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port-&gt;bulk_out_buffer
)paren
suffix:semicolon
id|port-&gt;bulk_in_buffer
op_assign
id|kmalloc
c_func
(paren
id|URBDATA_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;bulk_in_buffer
op_eq
l_int|NULL
)paren
(brace
r_goto
id|enomem
suffix:semicolon
)brace
id|port-&gt;bulk_out_buffer
op_assign
id|kmalloc
c_func
(paren
id|URBDATA_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;bulk_out_buffer
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|port-&gt;bulk_in_buffer
)paren
suffix:semicolon
r_goto
id|enomem
suffix:semicolon
)brace
id|port-&gt;read_urb-&gt;transfer_buffer
op_assign
id|port-&gt;bulk_in_buffer
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer
op_assign
id|port-&gt;bulk_out_buffer
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_buffer_length
op_assign
id|URBDATA_SIZE
suffix:semicolon
id|port-&gt;bulk_out_size
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|URBDATA_SIZE
suffix:semicolon
multiline_comment|/* Start reading from the device */
id|usb_fill_bulk_urb
c_func
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
id|ipaq_read_bulk_callback
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
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Send out control message observed in win98 sniffs. Not sure what&n;&t; * it does, but from empirical observations, it seems that the device&n;&t; * will start the chat sequence once one of these messages gets&n;&t; * through. Since this has a reasonably high failure rate, we retry&n;&t; * several times.&n;&t; */
r_while
c_loop
(paren
id|retries
op_decrement
)paren
(brace
id|result
op_assign
id|usb_control_msg
c_func
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
l_int|0x22
comma
l_int|0x21
comma
l_int|0x1
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_div
l_int|10
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|err
c_func
(paren
l_string|&quot;%s - failed doing control urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
id|enomem
suffix:colon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|err
c_func
(paren
l_string|&quot;%s - Out of memory&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|error
suffix:colon
id|ipaq_destroy_lists
c_func
(paren
id|port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ipaq_close
r_static
r_void
id|ipaq_close
c_func
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
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
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
multiline_comment|/*&n;&t; * shut down bulk read and write&n;&t; */
id|usb_unlink_urb
c_func
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
id|ipaq_destroy_lists
c_func
(paren
id|port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
id|usb_set_serial_port_data
c_func
(paren
id|port
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Uncomment the following line if you want to see some statistics in your syslog */
multiline_comment|/* info (&quot;Bytes In = %d  Bytes Out = %d&quot;, bytes_in, bytes_out); */
)brace
DECL|function|ipaq_read_bulk_callback
r_static
r_void
id|ipaq_read_bulk_callback
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
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
comma
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
id|urb-&gt;status
)paren
(brace
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
r_return
suffix:semicolon
)brace
id|usb_serial_debug_data
c_func
(paren
id|debug
comma
op_amp
id|port-&gt;dev
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
id|tty
op_logical_and
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
multiline_comment|/* if we insert more than TTY_FLIPBUF_SIZE characters, we drop them. */
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
multiline_comment|/* this doesn&squot;t actually push the data through unless tty-&gt;low_latency is set */
id|tty_insert_flip_char
c_func
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
c_func
(paren
id|tty
)paren
suffix:semicolon
id|bytes_in
op_add_assign
id|urb-&gt;actual_length
suffix:semicolon
)brace
multiline_comment|/* Continue trying to always read  */
id|usb_fill_bulk_urb
c_func
(paren
id|port-&gt;read_urb
comma
id|port-&gt;serial-&gt;dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;bulk_in_endpointAddress
)paren
comma
id|port-&gt;read_urb-&gt;transfer_buffer
comma
id|port-&gt;read_urb-&gt;transfer_buffer_length
comma
id|ipaq_read_bulk_callback
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
r_return
suffix:semicolon
)brace
DECL|function|ipaq_write
r_static
r_int
id|ipaq_write
c_func
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
r_const
r_int
r_char
op_star
id|current_position
op_assign
id|buf
suffix:semicolon
r_int
id|bytes_sent
op_assign
l_int|0
suffix:semicolon
r_int
id|transfer_size
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
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|transfer_size
op_assign
id|min
c_func
(paren
id|count
comma
id|PACKET_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipaq_write_bulk
c_func
(paren
id|port
comma
id|from_user
comma
id|current_position
comma
id|transfer_size
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|current_position
op_add_assign
id|transfer_size
suffix:semicolon
id|bytes_sent
op_add_assign
id|transfer_size
suffix:semicolon
id|count
op_sub_assign
id|transfer_size
suffix:semicolon
id|bytes_out
op_add_assign
id|transfer_size
suffix:semicolon
)brace
r_return
id|bytes_sent
suffix:semicolon
)brace
DECL|function|ipaq_write_bulk
r_static
r_int
id|ipaq_write_bulk
c_func
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
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
r_struct
id|ipaq_packet
op_star
id|pkt
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;free_len
op_le
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - we&squot;re stuffed&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|priv-&gt;freelist
)paren
)paren
(brace
id|pkt
op_assign
id|list_entry
c_func
(paren
id|priv-&gt;freelist.next
comma
r_struct
id|ipaq_packet
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|pkt-&gt;list
)paren
suffix:semicolon
id|priv-&gt;free_len
op_sub_assign
id|PACKET_SIZE
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt
op_eq
l_int|NULL
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - we&squot;re stuffed&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
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
c_func
(paren
id|pkt-&gt;data
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
c_func
(paren
id|pkt-&gt;data
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
id|usb_serial_debug_data
c_func
(paren
id|debug
comma
op_amp
id|port-&gt;dev
comma
id|__FUNCTION__
comma
id|count
comma
id|pkt-&gt;data
)paren
suffix:semicolon
id|pkt-&gt;len
op_assign
id|count
suffix:semicolon
id|pkt-&gt;written
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|pkt-&gt;list
comma
op_amp
id|priv-&gt;queue
)paren
suffix:semicolon
id|priv-&gt;queue_len
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;active
op_eq
l_int|0
)paren
(brace
id|priv-&gt;active
op_assign
l_int|1
suffix:semicolon
id|ipaq_write_gather
c_func
(paren
id|port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
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
(brace
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
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|ipaq_write_gather
r_static
r_void
id|ipaq_write_gather
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_int
id|count
comma
id|room
suffix:semicolon
r_struct
id|ipaq_packet
op_star
id|pkt
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
id|port-&gt;write_urb
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
multiline_comment|/* Should never happen */
id|err
c_func
(paren
l_string|&quot;%s - flushing while urb is active !&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|room
op_assign
id|URBDATA_SIZE
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|priv-&gt;queue.next
suffix:semicolon
id|tmp
op_ne
op_amp
id|priv-&gt;queue
suffix:semicolon
)paren
(brace
id|pkt
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|ipaq_packet
comma
id|list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|count
op_assign
id|min
c_func
(paren
id|room
comma
(paren
r_int
)paren
(paren
id|pkt-&gt;len
op_minus
id|pkt-&gt;written
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|urb-&gt;transfer_buffer
op_plus
(paren
id|URBDATA_SIZE
op_minus
id|room
)paren
comma
id|pkt-&gt;data
op_plus
id|pkt-&gt;written
comma
id|count
)paren
suffix:semicolon
id|room
op_sub_assign
id|count
suffix:semicolon
id|pkt-&gt;written
op_add_assign
id|count
suffix:semicolon
id|priv-&gt;queue_len
op_sub_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|pkt-&gt;written
op_eq
id|pkt-&gt;len
)paren
(brace
id|list_move
c_func
(paren
op_amp
id|pkt-&gt;list
comma
op_amp
id|priv-&gt;freelist
)paren
suffix:semicolon
id|priv-&gt;free_len
op_add_assign
id|PACKET_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|room
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|count
op_assign
id|URBDATA_SIZE
op_minus
id|room
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|port-&gt;write_urb
comma
id|serial-&gt;dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|serial-&gt;dev
comma
id|port-&gt;bulk_out_endpointAddress
)paren
comma
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|count
comma
id|ipaq_write_bulk_callback
comma
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ipaq_write_bulk_callback
r_static
r_void
id|ipaq_write_bulk_callback
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
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
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|flags
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
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|priv-&gt;queue
)paren
)paren
(brace
id|ipaq_write_gather
c_func
(paren
id|port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
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
(brace
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
)brace
r_else
(brace
id|priv-&gt;active
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|write_list_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|schedule_work
c_func
(paren
op_amp
id|port-&gt;work
)paren
suffix:semicolon
)brace
DECL|function|ipaq_write_room
r_static
r_int
id|ipaq_write_room
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - freelen %d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;free_len
)paren
suffix:semicolon
r_return
id|priv-&gt;free_len
suffix:semicolon
)brace
DECL|function|ipaq_chars_in_buffer
r_static
r_int
id|ipaq_chars_in_buffer
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - queuelen %d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;queue_len
)paren
suffix:semicolon
r_return
id|priv-&gt;queue_len
suffix:semicolon
)brace
DECL|function|ipaq_destroy_lists
r_static
r_void
id|ipaq_destroy_lists
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|ipaq_packet
op_star
id|pkt
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|priv-&gt;queue.next
suffix:semicolon
id|tmp
op_ne
op_amp
id|priv-&gt;queue
suffix:semicolon
)paren
(brace
id|pkt
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|ipaq_packet
comma
id|list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|pkt-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pkt
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp
op_assign
id|priv-&gt;freelist.next
suffix:semicolon
id|tmp
op_ne
op_amp
id|priv-&gt;freelist
suffix:semicolon
)paren
(brace
id|pkt
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|ipaq_packet
comma
id|list
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|pkt-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pkt
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|ipaq_startup
r_static
r_int
id|ipaq_startup
c_func
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;dev-&gt;actconfig-&gt;desc.bConfigurationValue
op_ne
l_int|1
)paren
(brace
id|err
c_func
(paren
l_string|&quot;active config #%d != 1 ??&quot;
comma
id|serial-&gt;dev-&gt;actconfig-&gt;desc.bConfigurationValue
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|usb_reset_configuration
(paren
id|serial-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|ipaq_shutdown
r_static
r_void
id|ipaq_shutdown
c_func
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|function|ipaq_init
r_static
r_int
id|__init
id|ipaq_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|write_list_lock
)paren
suffix:semicolon
id|retval
op_assign
id|usb_serial_register
c_func
(paren
op_amp
id|ipaq_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|failed_usb_serial_register
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vendor
)paren
(brace
id|ipaq_id_table
(braket
l_int|0
)braket
dot
id|idVendor
op_assign
id|vendor
suffix:semicolon
id|ipaq_id_table
(braket
l_int|0
)braket
dot
id|idProduct
op_assign
id|product
suffix:semicolon
)brace
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|ipaq_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|failed_usb_register
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|failed_usb_register
suffix:colon
id|usb_serial_deregister
c_func
(paren
op_amp
id|ipaq_device
)paren
suffix:semicolon
id|failed_usb_serial_register
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ipaq_exit
r_static
r_void
id|__exit
id|ipaq_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|ipaq_driver
)paren
suffix:semicolon
id|usb_serial_deregister
c_func
(paren
op_amp
id|ipaq_device
)paren
suffix:semicolon
)brace
DECL|variable|ipaq_init
id|module_init
c_func
(paren
id|ipaq_init
)paren
suffix:semicolon
DECL|variable|ipaq_exit
id|module_exit
c_func
(paren
id|ipaq_exit
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
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|vendor
comma
id|ushort
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vendor
comma
l_string|&quot;User specified USB idVendor&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|product
comma
id|ushort
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|product
comma
l_string|&quot;User specified USB idProduct&quot;
)paren
suffix:semicolon
eof
