multiline_comment|/*&n; * USB Compaq iPAQ driver&n; *&n; *&t;Copyright (C) 2001 - 2002&n; *&t;    Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * (8/3/2002) ganesh&n; * &t;The ipaq sometimes emits a &squot;&bslash;0&squot; before the CLIENT string. At this&n; * &t;point of time, the ppp ldisc is not yet attached to the tty, so&n; * &t;n_tty echoes &quot;^ &quot; to the ipaq, which messes up the chat. In 2.5.6-pre2&n; * &t;this causes a panic because echo_char() tries to sleep in interrupt&n; * &t;context.&n; * &t;The fix is to tell the upper layers that this is a raw device so that&n; * &t;echoing is suppressed. Thanks to Lyle Lindholm for a detailed bug&n; * &t;report.&n; *&n; * (25/2/2002) ganesh&n; * &t;Added support for the HP Jornada 548 and 568. Completely untested.&n; * &t;Thanks to info from Heath Robinson and Arieh Davidoff.&n; */
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
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;usb-serial.h&quot;
macro_line|#include &quot;ipaq.h&quot;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.2&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Ganesh Varadarajan &lt;ganesh@veritas.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Compaq iPAQ, HP Jornada driver&quot;
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
r_int
id|ipaq_write_flush
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
id|__devinitdata
r_struct
id|usb_device_id
id|ipaq_id_table
(braket
)braket
op_assign
(brace
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
multiline_comment|/* All of the device info needed for the Compaq iPAQ */
DECL|variable|ipaq_device
r_struct
id|usb_serial_device_type
id|ipaq_device
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;Compaq iPAQ&quot;
comma
id|id_table
suffix:colon
id|ipaq_id_table
comma
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
id|ipaq_open
comma
id|close
suffix:colon
id|ipaq_close
comma
id|startup
suffix:colon
id|ipaq_startup
comma
id|shutdown
suffix:colon
id|ipaq_shutdown
comma
id|write
suffix:colon
id|ipaq_write
comma
id|write_room
suffix:colon
id|ipaq_write_room
comma
id|chars_in_buffer
suffix:colon
id|ipaq_chars_in_buffer
comma
id|read_bulk_callback
suffix:colon
id|ipaq_read_bulk_callback
comma
id|write_bulk_callback
suffix:colon
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
r_if
c_cond
(paren
id|port_paranoia_check
c_func
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
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
id|__FUNCTION__
l_string|&quot; - Out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|port
op_member_access_from_pointer
r_private
op_assign
(paren
r_void
op_star
)paren
id|priv
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
multiline_comment|/*&n;&t;&t; * Force low latency on. This will immediately push data to the line&n;&t;&t; * discipline instead of queueing.&n;&t;&t; */
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
multiline_comment|/*&n;&t;&t; * Lose the small buffers usbserial provides. Make larger ones.&n;&t;&t; */
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
id|FILL_BULK_URB
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
id|__FUNCTION__
l_string|&quot; - failed submitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Send out two control messages observed in win98 sniffs. Not sure what&n;&t;&t; * they do.&n;&t;&t; */
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
l_int|5
op_star
id|HZ
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
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed doing control urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
)brace
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
l_int|5
op_star
id|HZ
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
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed doing control urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
)brace
)brace
r_return
id|result
suffix:semicolon
id|enomem
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
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - Out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
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
id|usb_serial
op_star
id|serial
suffix:semicolon
r_struct
id|ipaq_private
op_star
id|priv
op_assign
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
c_func
(paren
id|port
comma
id|__FUNCTION__
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
id|serial
op_assign
id|get_usb_serial
c_func
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
multiline_comment|/*&n;&t;&t; * shut down bulk read and write&n;&t;&t; */
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
id|port
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|port-&gt;open_count
op_assign
l_int|0
suffix:semicolon
)brace
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
comma
id|result
suffix:semicolon
r_if
c_cond
(paren
id|port_paranoia_check
c_func
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
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - nonzero read bulk status received: %d&quot;
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
id|FILL_BULK_URB
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
id|__FUNCTION__
l_string|&quot; - failed resubmitting read urb, error %d&quot;
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
id|__FUNCTION__
l_string|&quot; - port %d&quot;
comma
id|port-&gt;number
)paren
suffix:semicolon
id|usb_serial_debug_data
c_func
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|count
comma
id|buf
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
id|port
op_member_access_from_pointer
r_private
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
id|__FUNCTION__
l_string|&quot; - we&squot;re stuffed&quot;
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
id|__FUNCTION__
l_string|&quot; - we&squot;re stuffed&quot;
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
id|copy_from_user
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
id|__FILE__
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
id|result
op_assign
id|ipaq_write_flush
c_func
(paren
id|port
)paren
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
r_return
id|result
suffix:semicolon
)brace
DECL|function|ipaq_write_flush
r_static
r_int
id|ipaq_write_flush
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
(paren
r_struct
id|ipaq_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
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
comma
id|result
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
id|__FUNCTION__
l_string|&quot; - flushing while urb is active !&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
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
id|list_del
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
id|FILL_BULK_URB
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
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
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
id|__FUNCTION__
l_string|&quot; - failed submitting write urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
)brace
r_return
id|result
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
(paren
r_struct
id|ipaq_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_int
id|flags
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
(brace
r_return
suffix:semicolon
)brace
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
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - nonzero write bulk status received: %d&quot;
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
id|ipaq_write_flush
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_else
(brace
id|priv-&gt;active
op_assign
l_int|0
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
(paren
r_struct
id|ipaq_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - freelen %d&quot;
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
(paren
r_struct
id|ipaq_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - queuelen %d&quot;
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
(paren
r_struct
id|ipaq_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
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
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_set_configuration
c_func
(paren
id|serial-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
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
r_int
id|i
suffix:semicolon
id|dbg
(paren
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
r_while
c_loop
(paren
id|serial-&gt;port
(braket
id|i
)braket
dot
id|open_count
OG
l_int|0
)paren
(brace
id|ipaq_close
c_func
(paren
op_amp
id|serial-&gt;port
(braket
id|i
)braket
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
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
id|usb_serial_register
c_func
(paren
op_amp
id|ipaq_device
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
