multiline_comment|/*&n; * USB Empeg empeg-car player driver&n; *&n; *&t;Copyright (C) 2000, 2001&n; *&t;    Gary Brubaker (xavyer@ix.netcom.com)&n; *&n; *&t;Copyright (C) 1999 - 2001&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License, as published by&n; *&t;the Free Software Foundation, version 2.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; * &n; * (05/30/2001) gkh&n; *&t;switched from using spinlock to a semaphore, which fixes lots of problems.&n; *&n; * (04/08/2001) gb&n; *      Identify version on module load.&n; * &n; * (01/22/2001) gb&n; *&t;Added write_room() and chars_in_buffer() support. &n; * &n; * (12/21/2000) gb&n; *&t;Moved termio stuff inside the port-&gt;active check.&n; *&t;Moved MOD_DEC_USE_COUNT to end of empeg_close().&n; * &n; * (12/03/2000) gb&n; *&t;Added port-&gt;tty-&gt;ldisc.set_termios(port-&gt;tty, NULL) to empeg_open()&n; *&t;This notifies the tty driver that the termios have changed.&n; * &n; * (11/13/2000) gb&n; *&t;Moved tty-&gt;low_latency = 1 from empeg_read_bulk_callback() to empeg_open()&n; *&t;(It only needs to be set once - Doh!)&n; * &n; * (11/11/2000) gb&n; *&t;Updated to work with id_table structure.&n; * &n; * (11/04/2000) gb&n; *&t;Forked this from visor.c, and hacked it up to work with an&n; *&t;Empeg ltd. empeg-car player.  Constructive criticism welcomed.&n; *&t;I would like to say, &squot;Thank You&squot; to Greg Kroah-Hartman for the&n; *&t;use of his code, and for his guidance, advice and patience. :)&n; *&t;A &squot;Thank You&squot; is in order for John Ripley of Empeg ltd for his&n; *&t;advice, and patience too.&n; * &n; */
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
mdefine_line|#define DRIVER_AUTHOR &quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;, Gary Brubaker &lt;xavyer@ix.netcom.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Empeg Mark I/II Driver&quot;
DECL|macro|EMPEG_VENDOR_ID
mdefine_line|#define EMPEG_VENDOR_ID&t;&t;&t;0x084f
DECL|macro|EMPEG_PRODUCT_ID
mdefine_line|#define EMPEG_PRODUCT_ID&t;&t;0x0001
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;&t;(((a)&lt;(b))?(a):(b))
multiline_comment|/* function prototypes for an empeg-car player */
r_static
r_int
id|empeg_open
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
id|empeg_close
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
id|empeg_write
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
id|empeg_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|empeg_chars_in_buffer
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|empeg_throttle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|empeg_unthrottle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|empeg_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|empeg_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|empeg_ioctl
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
id|empeg_set_termios
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
r_static
r_void
id|empeg_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_void
id|empeg_read_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
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
id|EMPEG_VENDOR_ID
comma
id|EMPEG_PRODUCT_ID
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
DECL|variable|empeg_device
r_struct
id|usb_serial_device_type
id|empeg_device
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Empeg&quot;
comma
id|id_table
suffix:colon
id|id_table
comma
id|needs_interrupt_in
suffix:colon
id|MUST_HAVE_NOT
comma
multiline_comment|/* must not have an interrupt in endpoint */
id|needs_bulk_in
suffix:colon
id|MUST_HAVE
comma
multiline_comment|/* must have a bulk in endpoint */
id|needs_bulk_out
suffix:colon
id|MUST_HAVE
comma
multiline_comment|/* must have a bulk out endpoint */
id|num_interrupt_in
suffix:colon
l_int|0
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
id|empeg_open
comma
id|close
suffix:colon
id|empeg_close
comma
id|throttle
suffix:colon
id|empeg_throttle
comma
id|unthrottle
suffix:colon
id|empeg_unthrottle
comma
id|startup
suffix:colon
id|empeg_startup
comma
id|shutdown
suffix:colon
id|empeg_shutdown
comma
id|ioctl
suffix:colon
id|empeg_ioctl
comma
id|set_termios
suffix:colon
id|empeg_set_termios
comma
id|write
suffix:colon
id|empeg_write
comma
id|write_room
suffix:colon
id|empeg_write_room
comma
id|chars_in_buffer
suffix:colon
id|empeg_chars_in_buffer
comma
id|write_bulk_callback
suffix:colon
id|empeg_write_bulk_callback
comma
id|read_bulk_callback
suffix:colon
id|empeg_read_bulk_callback
comma
)brace
suffix:semicolon
DECL|macro|NUM_URBS
mdefine_line|#define NUM_URBS&t;&t;&t;16
DECL|macro|URB_TRANSFER_BUFFER_SIZE
mdefine_line|#define URB_TRANSFER_BUFFER_SIZE&t;4096
DECL|variable|write_urb_pool
r_static
r_struct
id|urb
op_star
id|write_urb_pool
(braket
id|NUM_URBS
)braket
suffix:semicolon
DECL|variable|write_urb_pool_lock
r_static
id|spinlock_t
id|write_urb_pool_lock
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
multiline_comment|/******************************************************************************&n; * Empeg specific driver functions&n; ******************************************************************************/
DECL|function|empeg_open
r_static
r_int
id|empeg_open
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
multiline_comment|/* gb - 2000/11/05&n;&t;&t; * personally, I think these termios should be set in&n;&t;&t; * empeg_startup(), but it appears doing so leads to one&n;&t;&t; * of those chicken/egg problems. :)&n;&t;&t; */
id|port-&gt;tty-&gt;termios-&gt;c_iflag
op_and_assign
op_complement
(paren
id|IGNBRK
op_or
id|BRKINT
op_or
id|PARMRK
op_or
id|ISTRIP
op_or
id|INLCR
op_or
id|IGNCR
op_or
id|ICRNL
op_or
id|IXON
)paren
suffix:semicolon
id|port-&gt;tty-&gt;termios-&gt;c_oflag
op_and_assign
op_complement
id|OPOST
suffix:semicolon
id|port-&gt;tty-&gt;termios-&gt;c_lflag
op_and_assign
op_complement
(paren
id|ECHO
op_or
id|ECHONL
op_or
id|ICANON
op_or
id|ISIG
op_or
id|IEXTEN
)paren
suffix:semicolon
id|port-&gt;tty-&gt;termios-&gt;c_cflag
op_and_assign
op_complement
(paren
id|CSIZE
op_or
id|PARENB
)paren
suffix:semicolon
id|port-&gt;tty-&gt;termios-&gt;c_cflag
op_or_assign
id|CS8
suffix:semicolon
multiline_comment|/* gb - 2000/12/03&n;&t;&t; * Contributed by Borislav Deianov&n;&t;&t; * Notify the tty driver that the termios have changed!!&n;&t;&t; */
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
multiline_comment|/* gb - 2000/11/05&n;&t;&t; * force low_latency on&n;&t;&t; *&n;&t;&t; * The tty_flip_buffer_push()&squot;s in empeg_read_bulk_callback() will actually&n;&t;&t; * force the data through if low_latency is set.  Otherwise the pushes are&n;&t;&t; * scheduled; this is bad as it opens up the possibility of dropping bytes&n;&t;&t; * on the floor.  We are trying to sustain high data transfer rates; and&n;&t;&t; * don&squot;t want to drop bytes on the floor.&n;&t;&t; * Moral: use low_latency - drop no bytes - life is good. :)&n;&t;&t; */
id|port-&gt;tty-&gt;low_latency
op_assign
l_int|1
suffix:semicolon
id|port-&gt;active
op_assign
l_int|1
suffix:semicolon
id|bytes_in
op_assign
l_int|0
suffix:semicolon
id|bytes_out
op_assign
l_int|0
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
id|empeg_read_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_flags
op_or_assign
id|USB_QUEUE_BULK
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;read_urb
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
DECL|function|empeg_close
r_static
r_void
id|empeg_close
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
r_int
r_char
op_star
id|transfer_buffer
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
id|transfer_buffer
op_assign
id|kmalloc
(paren
l_int|0x12
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transfer_buffer
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - kmalloc(%d) failed.&quot;
comma
l_int|0x12
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree
(paren
id|transfer_buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* shutdown our bulk read */
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
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
multiline_comment|/* Uncomment the following line if you want to see some statistics in your syslog */
multiline_comment|/* info (&quot;Bytes In = %d  Bytes Out = %d&quot;, bytes_in, bytes_out); */
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|empeg_write
r_static
r_int
id|empeg_write
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
id|urb
op_star
id|urb
suffix:semicolon
r_const
r_int
r_char
op_star
id|current_position
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|i
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
multiline_comment|/* try to find a free urb in our list of them */
id|urb
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
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
id|NUM_URBS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|write_urb_pool
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_ne
op_minus
id|EINPROGRESS
)paren
(brace
id|urb
op_assign
id|write_urb_pool
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb
op_eq
l_int|NULL
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - no more free urbs&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer
op_eq
l_int|NULL
)paren
(brace
id|urb-&gt;transfer_buffer
op_assign
id|kmalloc
(paren
id|URB_TRANSFER_BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; no more kernel memory...&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|transfer_size
op_assign
id|MIN
(paren
id|count
comma
id|URB_TRANSFER_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_user
)paren
(brace
id|copy_from_user
(paren
id|urb-&gt;transfer_buffer
comma
id|current_position
comma
id|transfer_size
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
(paren
id|urb-&gt;transfer_buffer
comma
id|current_position
comma
id|transfer_size
)paren
suffix:semicolon
)brace
multiline_comment|/* build up our urb */
id|FILL_BULK_URB
(paren
id|urb
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
id|urb-&gt;transfer_buffer
comma
id|transfer_size
comma
id|empeg_write_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|urb-&gt;transfer_flags
op_or_assign
id|USB_QUEUE_BULK
suffix:semicolon
multiline_comment|/* send it down the pipe */
id|status
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
id|status
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - usb_submit_urb(write bulk) failed with status = %d&quot;
comma
id|status
)paren
suffix:semicolon
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
m_exit
suffix:colon
r_return
id|bytes_sent
suffix:semicolon
)brace
DECL|function|empeg_write_room
r_static
r_int
id|empeg_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|room
op_assign
l_int|0
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
id|spin_lock_irqsave
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* tally up the number of bytes available */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_URBS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|write_urb_pool
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_ne
op_minus
id|EINPROGRESS
)paren
(brace
id|room
op_add_assign
id|URB_TRANSFER_BUFFER_SIZE
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - returns %d&quot;
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
DECL|function|empeg_chars_in_buffer
r_static
r_int
id|empeg_chars_in_buffer
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|chars
op_assign
l_int|0
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
id|spin_lock_irqsave
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* tally up the number of bytes waiting */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_URBS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|write_urb_pool
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
id|chars
op_add_assign
id|URB_TRANSFER_BUFFER_SIZE
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - returns %d&quot;
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
DECL|function|empeg_write_bulk_callback
r_static
r_void
id|empeg_write_bulk_callback
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
DECL|function|empeg_read_bulk_callback
r_static
r_void
id|empeg_read_bulk_callback
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
multiline_comment|/* gb - 2000/11/13&n;&t;&t;&t; * If we insert too many characters we&squot;ll overflow the buffer.&n;&t;&t;&t; * This means we&squot;ll lose bytes - Decidedly bad.&n;&t;&t;&t; */
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
multiline_comment|/* gb - 2000/11/13&n;&t;&t; * Goes straight through instead of scheduling - if tty-&gt;low_latency is set.&n;&t;&t; */
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
id|empeg_read_bulk_callback
comma
id|port
)paren
suffix:semicolon
id|port-&gt;read_urb-&gt;transfer_flags
op_or_assign
id|USB_QUEUE_BULK
suffix:semicolon
id|result
op_assign
id|usb_submit_urb
c_func
(paren
id|port-&gt;read_urb
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
DECL|function|empeg_throttle
r_static
r_void
id|empeg_throttle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
id|dbg
c_func
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
id|usb_unlink_urb
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|empeg_unthrottle
r_static
r_void
id|empeg_unthrottle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_int
id|result
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
id|down
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
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
id|up
(paren
op_amp
id|port-&gt;sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|empeg_startup
r_static
r_int
id|empeg_startup
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
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - Set config to 1&quot;
)paren
suffix:semicolon
id|usb_set_configuration
(paren
id|serial-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* continue on with initialization */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|empeg_shutdown
r_static
r_void
id|empeg_shutdown
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
id|empeg_close
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
DECL|function|empeg_ioctl
r_static
r_int
id|empeg_ioctl
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
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - port %d, cmd 0x%.4x&quot;
comma
id|port-&gt;number
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
multiline_comment|/* This function is all nice and good, but we don&squot;t change anything based on it :) */
DECL|function|empeg_set_termios
r_static
r_void
id|empeg_set_termios
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
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
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
id|__FUNCTION__
l_string|&quot; - nothing to change...&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
id|__FUNCTION__
l_string|&quot; - no tty structures&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* get the byte size */
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
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - data bits = 5&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - data bits = 6&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - data bits = 7&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
id|CS8
suffix:colon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - data bits = 8&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* determine the parity */
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
r_if
c_cond
(paren
id|cflag
op_amp
id|PARODD
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - parity = odd&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - parity = even&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - parity = none&quot;
)paren
suffix:semicolon
multiline_comment|/* figure out the stop bits requested */
r_if
c_cond
(paren
id|cflag
op_amp
id|CSTOPB
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - stop bits = 2&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - stop bits = 1&quot;
)paren
suffix:semicolon
multiline_comment|/* figure out the flow control settings */
r_if
c_cond
(paren
id|cflag
op_amp
id|CRTSCTS
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - RTS/CTS is enabled&quot;
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - RTS/CTS is disabled&quot;
)paren
suffix:semicolon
multiline_comment|/* determine software flow control */
r_if
c_cond
(paren
id|I_IXOFF
c_func
(paren
id|port-&gt;tty
)paren
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - XON/XOFF is enabled, XON = %2x, XOFF = %2x&quot;
comma
id|START_CHAR
c_func
(paren
id|port-&gt;tty
)paren
comma
id|STOP_CHAR
c_func
(paren
id|port-&gt;tty
)paren
)paren
suffix:semicolon
r_else
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - XON/XOFF is disabled&quot;
)paren
suffix:semicolon
multiline_comment|/* get the baud rate wanted */
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - baud rate = %d&quot;
comma
id|tty_get_baud_rate
c_func
(paren
id|port-&gt;tty
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|empeg_init
r_static
r_int
id|__init
id|empeg_init
(paren
r_void
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_int
id|i
suffix:semicolon
id|usb_serial_register
(paren
op_amp
id|empeg_device
)paren
suffix:semicolon
multiline_comment|/* create our write urb pool and transfer buffers */
id|spin_lock_init
(paren
op_amp
id|write_urb_pool_lock
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
id|NUM_URBS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_urb_pool
(braket
id|i
)braket
op_assign
id|urb
suffix:semicolon
r_if
c_cond
(paren
id|urb
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;No more urbs???&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|urb-&gt;transfer_buffer
op_assign
l_int|NULL
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|kmalloc
(paren
id|URB_TRANSFER_BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb-&gt;transfer_buffer
)paren
(brace
id|err
(paren
id|__FUNCTION__
l_string|&quot; - out of memory for urb buffers.&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
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
DECL|function|empeg_exit
r_static
r_void
id|__exit
id|empeg_exit
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|empeg_device
)paren
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
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
id|NUM_URBS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|write_urb_pool
(braket
id|i
)braket
)paren
(brace
multiline_comment|/* FIXME - uncomment the following usb_unlink_urb call when&n;&t;&t;&t; * the host controllers get fixed to set urb-&gt;dev = NULL after&n;&t;&t;&t; * the urb is finished.  Otherwise this call oopses. */
multiline_comment|/* usb_unlink_urb(write_urb_pool[i]); */
r_if
c_cond
(paren
id|write_urb_pool
(braket
id|i
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
id|kfree
c_func
(paren
id|write_urb_pool
(braket
id|i
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
(paren
id|write_urb_pool
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|write_urb_pool_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|empeg_init
id|module_init
c_func
(paren
id|empeg_init
)paren
suffix:semicolon
DECL|variable|empeg_exit
id|module_exit
c_func
(paren
id|empeg_exit
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
