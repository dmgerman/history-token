multiline_comment|/*&n; * USB Serial Converter Generic functions&n; *&n; * Copyright (C) 1999 - 2002 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
macro_line|#ifdef CONFIG_USB_SERIAL_GENERIC
DECL|variable|vendor
r_static
id|__u16
id|vendor
op_assign
l_int|0x05f9
suffix:semicolon
DECL|variable|product
r_static
id|__u16
id|product
op_assign
l_int|0xffff
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vendor
comma
l_string|&quot;h&quot;
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
id|MODULE_PARM
c_func
(paren
id|product
comma
l_string|&quot;h&quot;
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
DECL|variable|generic_device_ids
r_static
r_struct
id|usb_device_id
id|generic_device_ids
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Initially all zeroes. */
multiline_comment|/* All of the device info needed for the Generic Serial Converter */
DECL|variable|usb_serial_generic_device
r_struct
id|usb_serial_device_type
id|usb_serial_generic_device
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
l_string|&quot;Generic&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;generic&quot;
comma
dot
id|id_table
op_assign
id|generic_device_ids
comma
dot
id|num_interrupt_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_in
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_bulk_out
op_assign
id|NUM_DONT_CARE
comma
dot
id|num_ports
op_assign
l_int|1
comma
dot
id|shutdown
op_assign
id|usb_serial_generic_shutdown
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|usb_serial_generic_register
r_int
id|usb_serial_generic_register
(paren
r_int
id|_debug
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|debug
op_assign
id|_debug
suffix:semicolon
macro_line|#ifdef CONFIG_USB_SERIAL_GENERIC
id|generic_device_ids
(braket
l_int|0
)braket
dot
id|idVendor
op_assign
id|vendor
suffix:semicolon
id|generic_device_ids
(braket
l_int|0
)braket
dot
id|idProduct
op_assign
id|product
suffix:semicolon
id|generic_device_ids
(braket
l_int|0
)braket
dot
id|match_flags
op_assign
id|USB_DEVICE_ID_MATCH_VENDOR
op_or
id|USB_DEVICE_ID_MATCH_PRODUCT
suffix:semicolon
multiline_comment|/* register our generic driver with ourselves */
id|retval
op_assign
id|usb_serial_register
(paren
op_amp
id|usb_serial_generic_device
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_serial_generic_deregister
r_void
id|usb_serial_generic_deregister
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_USB_SERIAL_GENERIC
multiline_comment|/* remove our generic driver */
id|usb_serial_deregister
(paren
op_amp
id|usb_serial_generic_device
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|usb_serial_generic_open
r_int
id|usb_serial_generic_open
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
multiline_comment|/* force low_latency on so that our tty_push actually forces the data through, &n;&t;   otherwise it is scheduled, and with high data rates (like with OHCI) data&n;&t;   can get lost. */
r_if
c_cond
(paren
id|port-&gt;tty
)paren
id|port-&gt;tty-&gt;low_latency
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* if we have a bulk interrupt, start reading from it */
r_if
c_cond
(paren
id|serial-&gt;num_bulk_in
)paren
(brace
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
(paren
(paren
id|serial-&gt;type-&gt;read_bulk_callback
)paren
ques
c_cond
id|serial-&gt;type-&gt;read_bulk_callback
suffix:colon
id|usb_serial_generic_read_bulk_callback
)paren
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
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - failed resubmitting read urb, error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|generic_cleanup
r_static
r_void
id|generic_cleanup
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
id|usb_unlink_urb
(paren
id|port-&gt;write_urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial-&gt;num_bulk_in
)paren
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_serial_generic_close
r_void
id|usb_serial_generic_close
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
id|generic_cleanup
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_write
r_int
id|usb_serial_generic_write
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
id|count
op_eq
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - write request of 0 bytes&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* only do something if we have a bulk out endpoint */
r_if
c_cond
(paren
id|serial-&gt;num_bulk_out
)paren
(brace
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
c_func
(paren
l_string|&quot;%s - already writing&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
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
c_func
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
multiline_comment|/* set up our urb */
id|usb_fill_bulk_urb
(paren
id|port-&gt;write_urb
comma
id|serial-&gt;dev
comma
id|usb_sndbulkpipe
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
(paren
(paren
id|serial-&gt;type-&gt;write_bulk_callback
)paren
ques
c_cond
id|serial-&gt;type-&gt;write_bulk_callback
suffix:colon
id|usb_serial_generic_write_bulk_callback
)paren
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* send the data out the bulk port */
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
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - failed submitting write urb, error %d&bslash;n&quot;
comma
id|__FUNCTION__
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
multiline_comment|/* no bulk out, so return 0 bytes written */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_write_room
r_int
id|usb_serial_generic_write_room
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
r_int
id|room
op_assign
l_int|0
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
id|serial-&gt;num_bulk_out
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;write_urb-&gt;status
op_ne
op_minus
id|EINPROGRESS
)paren
id|room
op_assign
id|port-&gt;bulk_out_size
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - returns %d&quot;
comma
id|__FUNCTION__
comma
id|room
)paren
suffix:semicolon
r_return
(paren
id|room
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_chars_in_buffer
r_int
id|usb_serial_generic_chars_in_buffer
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
r_int
id|chars
op_assign
l_int|0
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
id|serial-&gt;num_bulk_out
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;write_urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
id|chars
op_assign
id|port-&gt;write_urb-&gt;transfer_buffer_length
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - returns %d&quot;
comma
id|__FUNCTION__
comma
id|chars
)paren
suffix:semicolon
r_return
(paren
id|chars
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_read_bulk_callback
r_void
id|usb_serial_generic_read_bulk_callback
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
)brace
multiline_comment|/* Continue trying to always read  */
id|usb_fill_bulk_urb
(paren
id|port-&gt;read_urb
comma
id|serial-&gt;dev
comma
id|usb_rcvbulkpipe
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
(paren
(paren
id|serial-&gt;type-&gt;read_bulk_callback
)paren
ques
c_cond
id|serial-&gt;type-&gt;read_bulk_callback
suffix:colon
id|usb_serial_generic_read_bulk_callback
)paren
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
id|dev_err
c_func
(paren
op_amp
id|port-&gt;dev
comma
l_string|&quot;%s - failed resubmitting read urb, error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_write_bulk_callback
r_void
id|usb_serial_generic_write_bulk_callback
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
id|usb_serial_port_softint
c_func
(paren
(paren
r_void
op_star
)paren
id|port
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|port-&gt;work
)paren
suffix:semicolon
)brace
DECL|function|usb_serial_generic_shutdown
r_void
id|usb_serial_generic_shutdown
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
id|generic_cleanup
(paren
op_amp
id|serial-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
eof
