multiline_comment|/*&n; * USB ZyXEL omni.net LCD PLUS driver&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * Please report both successes and troubles to the author at omninet@kroah.com&n; * &n; * (05/30/2001) gkh&n; *&t;switched from using spinlock to a semaphore, which fixes lots of problems.&n; *&n; * (04/08/2001) gb&n; *&t;Identify version on module load.&n; *&n; * (11/01/2000) Adam J. Richter&n; *&t;usb_device_id table support&n; * &n; * (10/05/2000) gkh&n; *&t;Fixed bug with urb-&gt;dev not being set properly, now that the usb&n; *&t;core needs it.&n; * &n; * (08/28/2000) gkh&n; *&t;Added locks for SMP safeness.&n; *&t;Fixed MOD_INC and MOD_DEC logic and the ability to open a port more &n; *&t;than once.&n; *&t;Fixed potential race in omninet_write_bulk_callback&n; *&n; * (07/19/2000) gkh&n; *&t;Added module_init and module_exit functions to handle the fact that this&n; *&t;driver is a loadable module now.&n; *&n; */
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
mdefine_line|#define DRIVER_VERSION &quot;v1.1&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Anonymous&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB ZyXEL omni.net LCD PLUS Driver&quot;
DECL|macro|ZYXEL_VENDOR_ID
mdefine_line|#define ZYXEL_VENDOR_ID&t;&t;0x0586
DECL|macro|ZYXEL_OMNINET_ID
mdefine_line|#define ZYXEL_OMNINET_ID&t;0x1000
multiline_comment|/* function prototypes */
r_static
r_int
id|omninet_open
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
id|omninet_close
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
id|omninet_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|omninet_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|omninet_write
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
id|omninet_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|omninet_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
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
id|ZYXEL_VENDOR_ID
comma
id|ZYXEL_OMNINET_ID
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
DECL|variable|zyxel_omninet_device
r_static
r_struct
id|usb_serial_device_type
id|zyxel_omninet_device
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;ZyXEL - omni.net lcd plus usb&quot;
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
l_int|2
comma
id|num_ports
suffix:colon
l_int|1
comma
id|open
suffix:colon
id|omninet_open
comma
id|close
suffix:colon
id|omninet_close
comma
id|write
suffix:colon
id|omninet_write
comma
id|write_room
suffix:colon
id|omninet_write_room
comma
id|read_bulk_callback
suffix:colon
id|omninet_read_bulk_callback
comma
id|write_bulk_callback
suffix:colon
id|omninet_write_bulk_callback
comma
id|shutdown
suffix:colon
id|omninet_shutdown
comma
)brace
suffix:semicolon
multiline_comment|/* The protocol.&n; *&n; * The omni.net always exchange 64 bytes of data with the host. The first&n; * four bytes are the control header, you can see it in the above structure.&n; *&n; * oh_seq is a sequence number. Don&squot;t know if/how it&squot;s used.&n; * oh_len is the length of the data bytes in the packet.&n; * oh_xxx Bit-mapped, related to handshaking and status info.&n; *&t;I normally set it to 0x03 in trasmitted frames.&n; *&t;7: Active when the TA is in a CONNECTed state.&n; *&t;6: unknown&n; *&t;5: handshaking, unknown&n; *&t;4: handshaking, unknown&n; *&t;3: unknown, usually 0&n; *&t;2: unknown, usually 0&n; *&t;1: handshaking, unknown, usually set to 1 in trasmitted frames&n; *&t;0: handshaking, unknown, usually set to 1 in trasmitted frames&n; * oh_pad Probably a pad byte.&n; *&n; * After the header you will find data bytes if oh_len was greater than zero.&n; *&n; */
DECL|struct|omninet_header
r_struct
id|omninet_header
(brace
DECL|member|oh_seq
id|__u8
id|oh_seq
suffix:semicolon
DECL|member|oh_len
id|__u8
id|oh_len
suffix:semicolon
DECL|member|oh_xxx
id|__u8
id|oh_xxx
suffix:semicolon
DECL|member|oh_pad
id|__u8
id|oh_pad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omninet_data
r_struct
id|omninet_data
(brace
DECL|member|od_outseq
id|__u8
id|od_outseq
suffix:semicolon
singleline_comment|// Sequence number for bulk_out URBs
)brace
suffix:semicolon
DECL|function|omninet_open
r_static
r_int
id|omninet_open
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
id|usb_serial_port
op_star
id|wport
suffix:semicolon
r_struct
id|omninet_data
op_star
id|od
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
id|__FUNCTION__
l_string|&quot; - port %d&quot;
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
op_minus
id|ENODEV
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
r_if
c_cond
(paren
id|port-&gt;open_count
op_eq
l_int|1
)paren
(brace
id|od
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|omninet_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|od
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot;- kmalloc(%Zd) failed.&quot;
comma
r_sizeof
(paren
r_struct
id|omninet_data
)paren
)paren
suffix:semicolon
id|port-&gt;open_count
op_assign
l_int|0
suffix:semicolon
id|up
(paren
op_amp
id|port-&gt;sem
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
id|od
suffix:semicolon
id|wport
op_assign
op_amp
id|serial-&gt;port
(braket
l_int|1
)braket
suffix:semicolon
id|wport-&gt;tty
op_assign
id|port-&gt;tty
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
id|omninet_read_bulk_callback
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
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|omninet_close
r_static
r_void
id|omninet_close
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
id|usb_serial_port
op_star
id|wport
suffix:semicolon
r_struct
id|omninet_data
op_star
id|od
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
r_if
c_cond
(paren
id|serial-&gt;dev
)paren
(brace
id|wport
op_assign
op_amp
id|serial-&gt;port
(braket
l_int|1
)braket
suffix:semicolon
id|usb_unlink_urb
(paren
id|wport-&gt;write_urb
)paren
suffix:semicolon
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
)brace
id|port-&gt;open_count
op_assign
l_int|0
suffix:semicolon
id|od
op_assign
(paren
r_struct
id|omninet_data
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|od
)paren
id|kfree
c_func
(paren
id|od
)paren
suffix:semicolon
)brace
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
)brace
DECL|macro|OMNINET_DATAOFFSET
mdefine_line|#define OMNINET_DATAOFFSET&t;0x04
DECL|macro|OMNINET_HEADERLEN
mdefine_line|#define OMNINET_HEADERLEN&t;sizeof(struct omninet_header)
DECL|macro|OMNINET_BULKOUTSIZE
mdefine_line|#define OMNINET_BULKOUTSIZE &t;(64 - OMNINET_HEADERLEN)
DECL|function|omninet_read_bulk_callback
r_static
r_void
id|omninet_read_bulk_callback
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
r_int
r_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_struct
id|omninet_header
op_star
id|header
op_assign
(paren
r_struct
id|omninet_header
op_star
)paren
op_amp
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|result
suffix:semicolon
singleline_comment|//&t;dbg(&quot;omninet_read_bulk_callback&quot;);
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
r_if
c_cond
(paren
(paren
id|debug
)paren
op_logical_and
(paren
id|header-&gt;oh_xxx
op_ne
l_int|0x30
)paren
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;actual_length
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: omninet_read %d: &quot;
comma
id|header-&gt;oh_len
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
(paren
id|header-&gt;oh_len
op_plus
id|OMNINET_HEADERLEN
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
l_string|&quot;%.2x &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|urb-&gt;actual_length
op_logical_and
id|header-&gt;oh_len
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
id|header-&gt;oh_len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tty_insert_flip_char
c_func
(paren
id|port-&gt;tty
comma
id|data
(braket
id|OMNINET_DATAOFFSET
op_plus
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
id|port-&gt;tty
)paren
suffix:semicolon
)brace
multiline_comment|/* Continue trying to always read  */
id|FILL_BULK_URB
c_func
(paren
id|urb
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
id|urb-&gt;transfer_buffer
comma
id|urb-&gt;transfer_buffer_length
comma
id|omninet_read_bulk_callback
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
id|__FUNCTION__
l_string|&quot; - failed resubmitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|omninet_write
r_static
r_int
id|omninet_write
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
id|usb_serial_port
op_star
id|wport
op_assign
op_amp
id|serial-&gt;port
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|omninet_data
op_star
id|od
op_assign
(paren
r_struct
id|omninet_data
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|omninet_header
op_star
id|header
op_assign
(paren
r_struct
id|omninet_header
op_star
)paren
id|wport-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|result
suffix:semicolon
singleline_comment|//&t;dbg(&quot;omninet_write port %d&quot;, port-&gt;number);
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
id|__FUNCTION__
l_string|&quot; - write request of 0 bytes&quot;
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
id|wport-&gt;write_urb-&gt;status
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
id|OMNINET_BULKOUTSIZE
)paren
ques
c_cond
id|OMNINET_BULKOUTSIZE
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
id|wport-&gt;write_urb-&gt;transfer_buffer
op_plus
id|OMNINET_DATAOFFSET
comma
id|buf
comma
id|count
)paren
op_ne
l_int|0
)paren
(brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
r_else
(brace
id|memcpy
(paren
id|wport-&gt;write_urb-&gt;transfer_buffer
op_plus
id|OMNINET_DATAOFFSET
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
id|wport-&gt;write_urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|header-&gt;oh_seq
op_assign
id|od-&gt;od_outseq
op_increment
suffix:semicolon
id|header-&gt;oh_len
op_assign
id|count
suffix:semicolon
id|header-&gt;oh_xxx
op_assign
l_int|0x03
suffix:semicolon
id|header-&gt;oh_pad
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* send the data out the bulk port, always 64 bytes */
id|wport-&gt;write_urb-&gt;transfer_buffer_length
op_assign
l_int|64
suffix:semicolon
id|wport-&gt;write_urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|wport-&gt;write_urb
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
m_exit
suffix:colon
r_return
id|result
suffix:semicolon
)brace
DECL|function|omninet_write_room
r_static
r_int
id|omninet_write_room
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
r_struct
id|usb_serial_port
op_star
id|wport
op_assign
op_amp
id|serial-&gt;port
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|room
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Default: no room
r_if
c_cond
(paren
id|wport-&gt;write_urb-&gt;status
op_ne
op_minus
id|EINPROGRESS
)paren
id|room
op_assign
id|wport-&gt;bulk_out_size
op_minus
id|OMNINET_HEADERLEN
suffix:semicolon
singleline_comment|//&t;dbg(&quot;omninet_write_room returns %d&quot;, room);
r_return
(paren
id|room
)paren
suffix:semicolon
)brace
DECL|function|omninet_write_bulk_callback
r_static
r_void
id|omninet_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
multiline_comment|/*&t;struct omninet_header&t;*header = (struct omninet_header  *) urb-&gt;transfer_buffer; */
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
suffix:semicolon
singleline_comment|//&t;dbg(&quot;omninet_write_bulk_callback, port %0x&bslash;n&quot;, port);
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
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - nonzero write bulk status received: %d&quot;
comma
id|urb-&gt;status
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
singleline_comment|//&t;dbg(&quot;omninet_write_bulk_callback, tty %0x&bslash;n&quot;, tty);
r_return
suffix:semicolon
)brace
DECL|function|omninet_shutdown
r_static
r_void
id|omninet_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
)paren
suffix:semicolon
r_while
c_loop
(paren
id|serial-&gt;port
(braket
l_int|0
)braket
dot
id|open_count
OG
l_int|0
)paren
(brace
id|omninet_close
(paren
op_amp
id|serial-&gt;port
(braket
l_int|0
)braket
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
DECL|function|omninet_init
r_static
r_int
id|__init
id|omninet_init
(paren
r_void
)paren
(brace
id|usb_serial_register
(paren
op_amp
id|zyxel_omninet_device
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|omninet_exit
r_static
r_void
id|__exit
id|omninet_exit
(paren
r_void
)paren
(brace
id|usb_serial_deregister
(paren
op_amp
id|zyxel_omninet_device
)paren
suffix:semicolon
)brace
DECL|variable|omninet_init
id|module_init
c_func
(paren
id|omninet_init
)paren
suffix:semicolon
DECL|variable|omninet_exit
id|module_exit
c_func
(paren
id|omninet_exit
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
