multiline_comment|/*&n; *  REINER SCT cyberJack pinpad/e-com USB Chipcard Reader Driver&n; *&n; *  Copyright (C) 2001  REINER SCT&n; *  Author: Matthias Bruestle&n; *&n; *  Contact: linux-usb@sii.li (see MAINTAINERS)&n; *&n; *  This program is largely derived from work by the linux-usb group&n; *  and associated source files.  Please see the usb/serial files for&n; *  individual credits and copyrights.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  Thanks to Greg Kroah-Hartman (greg@kroah.com) for his help and&n; *  patience.&n; *&n; *  In case of problems, please write to the contact e-mail address&n; *  mentioned above.&n; */
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
DECL|macro|CYBERJACK_LOCAL_BUF_SIZE
mdefine_line|#define CYBERJACK_LOCAL_BUF_SIZE 32
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
mdefine_line|#define DRIVER_VERSION &quot;v1.0&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Matthias Bruestle&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;REINER SCT cyberJack pinpad/e-com USB Chipcard Reader Driver&quot;
DECL|macro|CYBERJACK_VENDOR_ID
mdefine_line|#define CYBERJACK_VENDOR_ID&t;0x0C4B
DECL|macro|CYBERJACK_PRODUCT_ID
mdefine_line|#define CYBERJACK_PRODUCT_ID&t;0x0100
multiline_comment|/* Function prototypes */
r_static
r_int
id|cyberjack_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|cyberjack_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|cyberjack_open
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
id|cyberjack_close
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
id|cyberjack_write
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
id|cyberjack_write_room
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
id|cyberjack_read_int_callback
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
id|cyberjack_read_bulk_callback
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
id|cyberjack_write_bulk_callback
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
id|CYBERJACK_VENDOR_ID
comma
id|CYBERJACK_PRODUCT_ID
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
DECL|variable|cyberjack_driver
r_static
r_struct
id|usb_driver
id|cyberjack_driver
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
l_string|&quot;cyberjack&quot;
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
DECL|variable|cyberjack_device
r_static
r_struct
id|usb_serial_device_type
id|cyberjack_device
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
l_string|&quot;Reiner SCT Cyberjack USB card reader&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;cyberjack&quot;
comma
dot
id|id_table
op_assign
id|id_table
comma
dot
id|num_interrupt_in
op_assign
l_int|1
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
id|attach
op_assign
id|cyberjack_startup
comma
dot
id|shutdown
op_assign
id|cyberjack_shutdown
comma
dot
id|open
op_assign
id|cyberjack_open
comma
dot
id|close
op_assign
id|cyberjack_close
comma
dot
id|write
op_assign
id|cyberjack_write
comma
dot
id|write_room
op_assign
id|cyberjack_write_room
comma
dot
id|read_int_callback
op_assign
id|cyberjack_read_int_callback
comma
dot
id|read_bulk_callback
op_assign
id|cyberjack_read_bulk_callback
comma
dot
id|write_bulk_callback
op_assign
id|cyberjack_write_bulk_callback
comma
)brace
suffix:semicolon
DECL|struct|cyberjack_private
r_struct
id|cyberjack_private
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Lock for SMP */
DECL|member|rdtodo
r_int
id|rdtodo
suffix:semicolon
multiline_comment|/* Bytes still to read */
DECL|member|wrbuf
r_int
r_char
id|wrbuf
(braket
l_int|5
op_star
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Buffer for collecting data to write */
DECL|member|wrfilled
r_int
id|wrfilled
suffix:semicolon
multiline_comment|/* Overall data size we already got */
DECL|member|wrsent
r_int
id|wrsent
suffix:semicolon
multiline_comment|/* Data akready sent */
)brace
suffix:semicolon
multiline_comment|/* do some startup allocations not currently performed by usb_serial_probe() */
DECL|function|cyberjack_startup
r_static
r_int
id|cyberjack_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_struct
id|cyberjack_private
op_star
id|priv
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* allocate the private data structure */
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cyberjack_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* set initial values */
id|spin_lock_init
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|priv-&gt;rdtodo
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
id|usb_set_serial_port_data
c_func
(paren
id|serial-&gt;port
(braket
l_int|0
)braket
comma
id|priv
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|serial-&gt;port
(braket
l_int|0
)braket
op_member_access_from_pointer
id|write_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cyberjack_shutdown
r_static
r_void
id|cyberjack_shutdown
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
multiline_comment|/* My special items, the standard routines free my urbs */
id|kfree
c_func
(paren
id|usb_get_serial_port_data
c_func
(paren
id|serial-&gt;port
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|usb_set_serial_port_data
c_func
(paren
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
DECL|function|cyberjack_open
r_static
r_int
id|cyberjack_open
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
id|cyberjack_private
op_star
id|priv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|result
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
id|dbg
c_func
(paren
l_string|&quot;%s - usb_clear_halt&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;write_urb-&gt;pipe
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;read_urb-&gt;pipe
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;interrupt_in_urb-&gt;pipe
)paren
suffix:semicolon
multiline_comment|/* force low_latency on so that our tty_push actually forces&n;&t; * the data through, otherwise it is scheduled, and with high&n;&t; * data rates (like with OHCI) data can get lost.&n;&t; */
id|port-&gt;tty-&gt;low_latency
op_assign
l_int|1
suffix:semicolon
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|port
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|priv-&gt;rdtodo
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* shutdown any bulk reads that might be going on */
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
id|port-&gt;interrupt_in_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;interrupt_in_urb
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
l_string|&quot; usb_submit_urb(read int) failed&quot;
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - usb_submit_urb(int urb)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|cyberjack_close
r_static
r_void
id|cyberjack_close
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
r_if
c_cond
(paren
id|port-&gt;serial-&gt;dev
)paren
(brace
multiline_comment|/* shutdown any bulk reads that might be going on */
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
id|dbg
c_func
(paren
l_string|&quot;%s - usb_clear_halt&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;write_urb-&gt;pipe
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;read_urb-&gt;pipe
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|port-&gt;serial-&gt;dev
comma
id|port-&gt;interrupt_in_urb-&gt;pipe
)paren
suffix:semicolon
)brace
)brace
DECL|function|cyberjack_write
r_static
r_int
id|cyberjack_write
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
r_struct
id|cyberjack_private
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
r_int
id|wrexpected
suffix:semicolon
r_int
r_char
id|localbuf
(braket
id|CYBERJACK_LOCAL_BUF_SIZE
)braket
suffix:semicolon
multiline_comment|/* Buffer for collecting data to write */
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
id|dbg
c_func
(paren
l_string|&quot;%s - from_user %d&quot;
comma
id|__FUNCTION__
comma
id|from_user
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_plus
id|priv-&gt;wrfilled
)paren
OG
r_sizeof
(paren
id|priv-&gt;wrbuf
)paren
op_logical_or
(paren
id|count
OG
r_sizeof
(paren
id|localbuf
)paren
)paren
)paren
(brace
multiline_comment|/* To much data  for buffer. Reset buffer. */
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Copy data */
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
id|localbuf
comma
id|buf
comma
id|count
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
id|memcpy
(paren
id|localbuf
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|memcpy
(paren
id|priv-&gt;wrbuf
op_plus
id|priv-&gt;wrfilled
comma
id|localbuf
comma
id|count
)paren
suffix:semicolon
id|usb_serial_debug_data
(paren
id|__FILE__
comma
id|__FUNCTION__
comma
id|count
comma
id|priv-&gt;wrbuf
op_plus
id|priv-&gt;wrfilled
)paren
suffix:semicolon
id|priv-&gt;wrfilled
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;wrfilled
op_ge
l_int|3
)paren
(brace
id|wrexpected
op_assign
(paren
(paren
r_int
)paren
id|priv-&gt;wrbuf
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_plus
id|priv-&gt;wrbuf
(braket
l_int|1
)braket
op_plus
l_int|3
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - expected data: %d&quot;
comma
id|__FUNCTION__
comma
id|wrexpected
)paren
suffix:semicolon
)brace
r_else
(brace
id|wrexpected
op_assign
r_sizeof
(paren
id|priv-&gt;wrbuf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;wrfilled
op_ge
id|wrexpected
)paren
(brace
multiline_comment|/* We have enough data to begin transmission */
r_int
id|length
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - transmitting data (frame 1)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|length
op_assign
(paren
id|wrexpected
OG
id|port-&gt;bulk_out_size
)paren
ques
c_cond
id|port-&gt;bulk_out_size
suffix:colon
id|wrexpected
suffix:semicolon
id|memcpy
(paren
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|priv-&gt;wrbuf
comma
id|length
)paren
suffix:semicolon
id|priv-&gt;wrsent
op_assign
id|length
suffix:semicolon
multiline_comment|/* set up our urb */
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
id|length
comma
(paren
(paren
id|serial-&gt;type-&gt;write_bulk_callback
)paren
ques
c_cond
id|serial-&gt;type-&gt;write_bulk_callback
suffix:colon
id|cyberjack_write_bulk_callback
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
multiline_comment|/* Throw away data. No better idea what to do with it. */
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - priv-&gt;wrsent=%d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;wrsent
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - priv-&gt;wrfilled=%d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;wrfilled
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;wrsent
op_ge
id|priv-&gt;wrfilled
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - buffer cleaned&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|memset
c_func
(paren
id|priv-&gt;wrbuf
comma
l_int|0
comma
r_sizeof
(paren
id|priv-&gt;wrbuf
)paren
)paren
suffix:semicolon
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|count
)paren
suffix:semicolon
)brace
DECL|function|cyberjack_write_room
r_static
r_int
id|cyberjack_write_room
c_func
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_return
id|CYBERJACK_LOCAL_BUF_SIZE
suffix:semicolon
)brace
DECL|function|cyberjack_read_int_callback
r_static
r_void
id|cyberjack_read_int_callback
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
id|cyberjack_private
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
multiline_comment|/* the urb might have been killed. */
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
id|serial
op_assign
id|port-&gt;serial
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
r_return
suffix:semicolon
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
multiline_comment|/* React only to interrupts signaling a bulk_in transfer */
r_if
c_cond
(paren
(paren
id|urb-&gt;actual_length
op_eq
l_int|4
)paren
op_logical_and
(paren
id|data
(braket
l_int|0
)braket
op_eq
l_int|0x01
)paren
)paren
(brace
r_int
id|old_rdtodo
suffix:semicolon
r_int
id|result
suffix:semicolon
multiline_comment|/* This is a announcement of coming bulk_ins. */
r_int
r_int
id|size
op_assign
(paren
(paren
r_int
r_int
)paren
id|data
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
op_plus
id|data
(braket
l_int|2
)braket
op_plus
l_int|3
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|old_rdtodo
op_assign
id|priv-&gt;rdtodo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old_rdtodo
op_plus
id|size
)paren
OL
(paren
id|old_rdtodo
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;To many bulk_in urbs to do.&quot;
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
r_goto
id|resubmit
suffix:semicolon
)brace
multiline_comment|/* &quot;+=&quot; is probably more fault tollerant than &quot;=&quot; */
id|priv-&gt;rdtodo
op_add_assign
id|size
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - rdtodo: %d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;rdtodo
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_rdtodo
)paren
(brace
id|port-&gt;read_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
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
(brace
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
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - usb_submit_urb(read urb)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
id|resubmit
suffix:colon
id|port-&gt;interrupt_in_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;interrupt_in_urb
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
l_string|&quot; usb_submit_urb(read int) failed&quot;
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - usb_submit_urb(int urb)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|function|cyberjack_read_bulk_callback
r_static
r_void
id|cyberjack_read_bulk_callback
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
id|cyberjack_private
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
id|todo
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
id|spin_lock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* Reduce urbs to do by one. */
id|priv-&gt;rdtodo
op_sub_assign
id|urb-&gt;actual_length
suffix:semicolon
multiline_comment|/* Just to be sure */
r_if
c_cond
(paren
id|priv-&gt;rdtodo
OL
l_int|0
)paren
id|priv-&gt;rdtodo
op_assign
l_int|0
suffix:semicolon
id|todo
op_assign
id|priv-&gt;rdtodo
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - rdtodo: %d&quot;
comma
id|__FUNCTION__
comma
id|todo
)paren
suffix:semicolon
multiline_comment|/* Continue to read if we have still urbs to do. */
r_if
c_cond
(paren
id|todo
multiline_comment|/* || (urb-&gt;actual_length==port-&gt;bulk_in_endpointAddress)*/
)paren
(brace
id|port-&gt;read_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
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
id|dbg
c_func
(paren
l_string|&quot;%s - usb_submit_urb(read urb)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
DECL|function|cyberjack_write_bulk_callback
r_static
r_void
id|cyberjack_write_bulk_callback
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
id|cyberjack_private
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
id|spin_lock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* only do something if we have more data to send */
r_if
c_cond
(paren
id|priv-&gt;wrfilled
)paren
(brace
r_int
id|length
comma
id|blksize
comma
id|result
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
c_func
(paren
l_string|&quot;%s - already writing&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - transmitting data (frame n)&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|length
op_assign
(paren
(paren
id|priv-&gt;wrfilled
op_minus
id|priv-&gt;wrsent
)paren
OG
id|port-&gt;bulk_out_size
)paren
ques
c_cond
id|port-&gt;bulk_out_size
suffix:colon
(paren
id|priv-&gt;wrfilled
op_minus
id|priv-&gt;wrsent
)paren
suffix:semicolon
id|memcpy
(paren
id|port-&gt;write_urb-&gt;transfer_buffer
comma
id|priv-&gt;wrbuf
op_plus
id|priv-&gt;wrsent
comma
id|length
)paren
suffix:semicolon
id|priv-&gt;wrsent
op_add_assign
id|length
suffix:semicolon
multiline_comment|/* set up our urb */
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
id|length
comma
(paren
(paren
id|serial-&gt;type-&gt;write_bulk_callback
)paren
ques
c_cond
id|serial-&gt;type-&gt;write_bulk_callback
suffix:colon
id|cyberjack_write_bulk_callback
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
multiline_comment|/* Throw away data. No better idea what to do with it. */
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - priv-&gt;wrsent=%d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;wrsent
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - priv-&gt;wrfilled=%d&quot;
comma
id|__FUNCTION__
comma
id|priv-&gt;wrfilled
)paren
suffix:semicolon
id|blksize
op_assign
(paren
(paren
r_int
)paren
id|priv-&gt;wrbuf
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_plus
id|priv-&gt;wrbuf
(braket
l_int|1
)braket
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priv-&gt;wrsent
op_ge
id|priv-&gt;wrfilled
)paren
op_logical_or
(paren
id|priv-&gt;wrsent
op_ge
id|blksize
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - buffer cleaned&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|memset
c_func
(paren
id|priv-&gt;wrbuf
comma
l_int|0
comma
r_sizeof
(paren
id|priv-&gt;wrbuf
)paren
)paren
suffix:semicolon
id|priv-&gt;wrfilled
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;wrsent
op_assign
l_int|0
suffix:semicolon
)brace
)brace
m_exit
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|priv-&gt;lock
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
DECL|function|cyberjack_init
r_static
r_int
id|__init
id|cyberjack_init
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
id|cyberjack_device
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
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|cyberjack_driver
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
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot; &quot;
id|DRIVER_AUTHOR
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
)paren
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
id|cyberjack_device
)paren
suffix:semicolon
id|failed_usb_serial_register
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|cyberjack_exit
r_static
r_void
id|__exit
id|cyberjack_exit
(paren
r_void
)paren
(brace
id|usb_deregister
(paren
op_amp
id|cyberjack_driver
)paren
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|cyberjack_device
)paren
suffix:semicolon
)brace
DECL|variable|cyberjack_init
id|module_init
c_func
(paren
id|cyberjack_init
)paren
suffix:semicolon
DECL|variable|cyberjack_exit
id|module_exit
c_func
(paren
id|cyberjack_exit
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
