multiline_comment|/*&n; * USB ConnectTech WhiteHEAT driver&n; *&n; *&t;Copyright (C) 1999 - 2001&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; * &n; * 2001_Mar_19 gkh&n; *&t;Fixed MOD_INC and MOD_DEC logic, the ability to open a port more &n; *&t;than once, and the got the proper usb_device_id table entries so&n; *&t;the driver works again.&n; *&n; * (11/01/2000) Adam J. Richter&n; *&t;usb_device_id table support&n; * &n; * (10/05/2000) gkh&n; *&t;Fixed bug with urb-&gt;dev not being set properly, now that the usb&n; *&t;core needs it.&n; * &n; * (10/03/2000) smd&n; *&t;firmware is improved to guard against crap sent to device&n; *&t;firmware now replies CMD_FAILURE on bad things&n; *&t;read_callback fix you provided for private info struct&n; *&t;command_finished now indicates success or fail&n; *&t;setup_port struct now packed to avoid gcc padding&n; *&t;firmware uses 1 based port numbering, driver now handles that&n; *&n; * (09/11/2000) gkh&n; *&t;Removed DEBUG #ifdefs with call to usb_serial_debug_data&n; *&n; * (07/19/2000) gkh&n; *&t;Added module_init and module_exit functions to handle the fact that this&n; *&t;driver is a loadable module now.&n; *&t;Fixed bug with port-&gt;minor that was found by Al Borchers&n; *&n; * (07/04/2000) gkh&n; *&t;Added support for port settings. Baud rate can now be changed. Line signals&n; *&t;are not transferred to and from the tty layer yet, but things seem to be &n; *&t;working well now.&n; *&n; * (05/04/2000) gkh&n; *&t;First cut at open and close commands. Data can flow through the ports at&n; *&t;default speeds now.&n; *&n; * (03/26/2000) gkh&n; *&t;Split driver up into device specific pieces.&n; * &n; */
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
macro_line|#include &quot;whiteheat_fw.h&quot;&t;&t;/* firmware for the ConnectTech WhiteHEAT device */
macro_line|#include &quot;whiteheat.h&quot;&t;&t;&t;/* WhiteHEAT specific commands */
DECL|macro|CONNECT_TECH_VENDOR_ID
mdefine_line|#define CONNECT_TECH_VENDOR_ID&t;&t;0x0710
DECL|macro|CONNECT_TECH_FAKE_WHITE_HEAT_ID
mdefine_line|#define CONNECT_TECH_FAKE_WHITE_HEAT_ID&t;0x0001
DECL|macro|CONNECT_TECH_WHITE_HEAT_ID
mdefine_line|#define CONNECT_TECH_WHITE_HEAT_ID&t;0x8001
multiline_comment|/*&n;   ID tables for whiteheat are unusual, because we want to different&n;   things for different versions of the device.  Eventually, this&n;   will be doable from a single table.  But, for now, we define two&n;   separate ID tables, and then a third table that combines them&n;   just for the purpose of exporting the autoloading information.&n;*/
DECL|variable|id_table_std
r_static
id|__devinitdata
r_struct
id|usb_device_id
id|id_table_std
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|CONNECT_TECH_VENDOR_ID
comma
id|CONNECT_TECH_WHITE_HEAT_ID
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|variable|id_table_prerenumeration
r_static
id|__devinitdata
r_struct
id|usb_device_id
id|id_table_prerenumeration
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|CONNECT_TECH_VENDOR_ID
comma
id|CONNECT_TECH_FAKE_WHITE_HEAT_ID
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
DECL|variable|id_table_combined
r_static
id|__devinitdata
r_struct
id|usb_device_id
id|id_table_combined
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|CONNECT_TECH_VENDOR_ID
comma
id|CONNECT_TECH_WHITE_HEAT_ID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|CONNECT_TECH_VENDOR_ID
comma
id|CONNECT_TECH_FAKE_WHITE_HEAT_ID
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
id|id_table_combined
)paren
suffix:semicolon
multiline_comment|/* function prototypes for the Connect Tech WhiteHEAT serial converter */
r_static
r_int
id|whiteheat_open
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
id|whiteheat_close
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
id|whiteheat_ioctl
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
id|whiteheat_set_termios
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
r_void
id|whiteheat_throttle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|whiteheat_unthrottle
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_int
id|whiteheat_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|whiteheat_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
DECL|variable|whiteheat_fake_device
r_struct
id|usb_serial_device_type
id|whiteheat_fake_device
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Connect Tech - WhiteHEAT - (prerenumeration)&quot;
comma
id|id_table
suffix:colon
id|id_table_prerenumeration
comma
id|needs_interrupt_in
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have an interrupt in endpoint */
id|needs_bulk_in
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have a bulk in endpoint */
id|needs_bulk_out
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have a bulk out endpoint */
id|num_interrupt_in
suffix:colon
id|NUM_DONT_CARE
comma
id|num_bulk_in
suffix:colon
id|NUM_DONT_CARE
comma
id|num_bulk_out
suffix:colon
id|NUM_DONT_CARE
comma
id|num_ports
suffix:colon
l_int|1
comma
id|startup
suffix:colon
id|whiteheat_startup
)brace
suffix:semicolon
DECL|variable|whiteheat_device
r_struct
id|usb_serial_device_type
id|whiteheat_device
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Connect Tech - WhiteHEAT&quot;
comma
id|id_table
suffix:colon
id|id_table_std
comma
id|needs_interrupt_in
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have an interrupt in endpoint */
id|needs_bulk_in
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have a bulk in endpoint */
id|needs_bulk_out
suffix:colon
id|DONT_CARE
comma
multiline_comment|/* don&squot;t have to have a bulk out endpoint */
id|num_interrupt_in
suffix:colon
id|NUM_DONT_CARE
comma
id|num_bulk_in
suffix:colon
id|NUM_DONT_CARE
comma
id|num_bulk_out
suffix:colon
id|NUM_DONT_CARE
comma
id|num_ports
suffix:colon
l_int|4
comma
id|open
suffix:colon
id|whiteheat_open
comma
id|close
suffix:colon
id|whiteheat_close
comma
id|throttle
suffix:colon
id|whiteheat_throttle
comma
id|unthrottle
suffix:colon
id|whiteheat_unthrottle
comma
id|ioctl
suffix:colon
id|whiteheat_ioctl
comma
id|set_termios
suffix:colon
id|whiteheat_set_termios
comma
id|shutdown
suffix:colon
id|whiteheat_shutdown
comma
)brace
suffix:semicolon
DECL|struct|whiteheat_private
r_struct
id|whiteheat_private
(brace
DECL|member|command_finished
id|__u8
id|command_finished
suffix:semicolon
DECL|member|wait_command
id|wait_queue_head_t
id|wait_command
suffix:semicolon
multiline_comment|/* for handling sleeping while waiting for a command to finish */
)brace
suffix:semicolon
multiline_comment|/* local function prototypes */
r_static
r_inline
r_void
id|set_rts
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|rts
)paren
suffix:semicolon
r_static
r_inline
r_void
id|set_dtr
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|dtr
)paren
suffix:semicolon
r_static
r_inline
r_void
id|set_break
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|brk
)paren
suffix:semicolon
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT&t;&t;4
DECL|macro|COMMAND_TIMEOUT
mdefine_line|#define COMMAND_TIMEOUT&t;&t;(2*HZ)&t;/* 2 second timeout for a command */
multiline_comment|/*****************************************************************************&n; * Connect Tech&squot;s White Heat specific driver functions&n; *****************************************************************************/
DECL|function|command_port_write_callback
r_static
r_void
id|command_port_write_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|dbg
(paren
l_string|&quot;nonzero urb status: %d&quot;
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
r_return
suffix:semicolon
)brace
DECL|function|command_port_read_callback
r_static
r_void
id|command_port_read_callback
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
id|whiteheat_private
op_star
id|info
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
(paren
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - nonzero urb status: %d&quot;
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
id|info
op_assign
(paren
r_struct
id|whiteheat_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - info is NULL, exiting.&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* right now, if the command is COMMAND_COMPLETE, just flip the bit saying the command finished */
multiline_comment|/* in the future we&squot;re going to have to pay attention to the actual command that completed */
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_eq
id|WHITEHEAT_CMD_COMPLETE
)paren
(brace
id|info-&gt;command_finished
op_assign
id|WHITEHEAT_CMD_COMPLETE
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|info-&gt;wait_command
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_eq
id|WHITEHEAT_CMD_FAILURE
)paren
(brace
id|info-&gt;command_finished
op_assign
id|WHITEHEAT_CMD_FAILURE
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|info-&gt;wait_command
)paren
suffix:semicolon
)brace
multiline_comment|/* Continue trying to always read */
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
id|command_port_read_callback
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed resubmitting read urb, error %d&quot;
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|whiteheat_send_cmd
r_static
r_int
id|whiteheat_send_cmd
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
id|__u8
id|command
comma
id|__u8
op_star
id|data
comma
id|__u8
id|datasize
)paren
(brace
r_struct
id|whiteheat_private
op_star
id|info
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|__u8
op_star
id|transfer_buffer
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - command %d&quot;
comma
id|command
)paren
suffix:semicolon
id|port
op_assign
op_amp
id|serial-&gt;port
(braket
id|COMMAND_PORT
)braket
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|whiteheat_private
op_star
)paren
id|port
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;command_finished
op_assign
id|FALSE
suffix:semicolon
id|transfer_buffer
op_assign
(paren
id|__u8
op_star
)paren
id|port-&gt;write_urb-&gt;transfer_buffer
suffix:semicolon
id|transfer_buffer
(braket
l_int|0
)braket
op_assign
id|command
suffix:semicolon
id|memcpy
(paren
op_amp
id|transfer_buffer
(braket
l_int|1
)braket
comma
id|data
comma
id|datasize
)paren
suffix:semicolon
id|port-&gt;write_urb-&gt;transfer_buffer_length
op_assign
id|datasize
op_plus
l_int|1
suffix:semicolon
id|port-&gt;write_urb-&gt;dev
op_assign
id|serial-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
(paren
id|port-&gt;write_urb
)paren
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - submit urb failed&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* wait for the command to complete */
id|timeout
op_assign
id|COMMAND_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_logical_and
(paren
id|info-&gt;command_finished
op_eq
id|FALSE
)paren
)paren
(brace
id|timeout
op_assign
id|interruptible_sleep_on_timeout
(paren
op_amp
id|info-&gt;wait_command
comma
id|timeout
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;command_finished
op_eq
id|FALSE
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - command timed out.&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;command_finished
op_eq
id|WHITEHEAT_CMD_FAILURE
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - command failed.&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;command_finished
op_eq
id|WHITEHEAT_CMD_COMPLETE
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - command completed.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|whiteheat_open
r_static
r_int
id|whiteheat_open
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
id|whiteheat_min_set
id|open_command
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|command_port
suffix:semicolon
r_struct
id|whiteheat_private
op_star
id|info
suffix:semicolon
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
multiline_comment|/* set up some stuff for our command port */
id|command_port
op_assign
op_amp
id|port-&gt;serial-&gt;port
(braket
id|COMMAND_PORT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|command_port
op_member_access_from_pointer
r_private
op_eq
l_int|NULL
)paren
(brace
id|info
op_assign
(paren
r_struct
id|whiteheat_private
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|whiteheat_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|info-&gt;wait_command
)paren
suffix:semicolon
id|command_port
op_member_access_from_pointer
r_private
op_assign
id|info
suffix:semicolon
id|command_port-&gt;write_urb-&gt;complete
op_assign
id|command_port_write_callback
suffix:semicolon
id|command_port-&gt;read_urb-&gt;complete
op_assign
id|command_port_read_callback
suffix:semicolon
id|command_port-&gt;read_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|command_port-&gt;tty
op_assign
id|port-&gt;tty
suffix:semicolon
multiline_comment|/* need this to &quot;fake&quot; our our sanity check macros */
id|usb_submit_urb
(paren
id|command_port-&gt;read_urb
)paren
suffix:semicolon
)brace
multiline_comment|/* Start reading from the device */
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
multiline_comment|/* send an open port command */
multiline_comment|/* firmware uses 1 based port numbering */
id|open_command.port
op_assign
id|port-&gt;number
op_minus
id|port-&gt;serial-&gt;minor
op_plus
l_int|1
suffix:semicolon
id|whiteheat_send_cmd
(paren
id|port-&gt;serial
comma
id|WHITEHEAT_OPEN
comma
(paren
id|__u8
op_star
)paren
op_amp
id|open_command
comma
r_sizeof
(paren
id|open_command
)paren
)paren
suffix:semicolon
multiline_comment|/* Need to do device specific setup here (control lines, baud rate, etc.) */
multiline_comment|/* FIXME!!! */
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - exit&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|whiteheat_close
r_static
r_void
id|whiteheat_close
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
id|whiteheat_min_set
id|close_command
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
multiline_comment|/* send a close command to the port */
multiline_comment|/* firmware uses 1 based port numbering */
id|close_command.port
op_assign
id|port-&gt;number
op_minus
id|port-&gt;serial-&gt;minor
op_plus
l_int|1
suffix:semicolon
id|whiteheat_send_cmd
(paren
id|port-&gt;serial
comma
id|WHITEHEAT_CLOSE
comma
(paren
id|__u8
op_star
)paren
op_amp
id|close_command
comma
r_sizeof
(paren
id|close_command
)paren
)paren
suffix:semicolon
multiline_comment|/* Need to change the control lines here */
multiline_comment|/* FIXME */
multiline_comment|/* shutdown our bulk reads and writes */
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
id|port-&gt;active
op_assign
l_int|0
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|whiteheat_ioctl
r_static
r_int
id|whiteheat_ioctl
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
DECL|function|whiteheat_set_termios
r_static
r_void
id|whiteheat_set_termios
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
r_struct
id|whiteheat_port_settings
id|port_settings
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; -port %d&quot;
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
multiline_comment|/* set the port number */
multiline_comment|/* firmware uses 1 based port numbering */
id|port_settings.port
op_assign
id|port-&gt;number
op_plus
l_int|1
suffix:semicolon
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
id|port_settings.bits
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|port_settings.bits
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|port_settings.bits
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
id|CS8
suffix:colon
id|port_settings.bits
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - data bits = %d&quot;
comma
id|port_settings.bits
)paren
suffix:semicolon
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
id|port_settings.parity
op_assign
l_char|&squot;o&squot;
suffix:semicolon
r_else
id|port_settings.parity
op_assign
l_char|&squot;e&squot;
suffix:semicolon
r_else
id|port_settings.parity
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - parity = %c&quot;
comma
id|port_settings.parity
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
id|port_settings.stop
op_assign
l_int|2
suffix:semicolon
r_else
id|port_settings.stop
op_assign
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - stop bits = %d&quot;
comma
id|port_settings.stop
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
id|port_settings.hflow
op_assign
(paren
id|WHITEHEAT_CTS_FLOW
op_or
id|WHITEHEAT_RTS_FLOW
)paren
suffix:semicolon
r_else
id|port_settings.hflow
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - hardware flow control = %s %s %s %s&quot;
comma
(paren
id|port_settings.hflow
op_amp
id|WHITEHEAT_CTS_FLOW
)paren
ques
c_cond
l_string|&quot;CTS&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|port_settings.hflow
op_amp
id|WHITEHEAT_RTS_FLOW
)paren
ques
c_cond
l_string|&quot;RTS&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|port_settings.hflow
op_amp
id|WHITEHEAT_DSR_FLOW
)paren
ques
c_cond
l_string|&quot;DSR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|port_settings.hflow
op_amp
id|WHITEHEAT_DTR_FLOW
)paren
ques
c_cond
l_string|&quot;DTR&quot;
suffix:colon
l_string|&quot;&quot;
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
id|port_settings.sflow
op_assign
l_char|&squot;b&squot;
suffix:semicolon
r_else
id|port_settings.sflow
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - software flow control = %c&quot;
comma
id|port_settings.sflow
)paren
suffix:semicolon
id|port_settings.xon
op_assign
id|START_CHAR
c_func
(paren
id|port-&gt;tty
)paren
suffix:semicolon
id|port_settings.xoff
op_assign
id|STOP_CHAR
c_func
(paren
id|port-&gt;tty
)paren
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - XON = %2x, XOFF = %2x&quot;
comma
id|port_settings.xon
comma
id|port_settings.xoff
)paren
suffix:semicolon
multiline_comment|/* get the baud rate wanted */
id|port_settings.baud
op_assign
id|tty_get_baud_rate
c_func
(paren
id|port-&gt;tty
)paren
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - baud rate = %d&quot;
comma
id|port_settings.baud
)paren
suffix:semicolon
multiline_comment|/* handle any settings that aren&squot;t specified in the tty structure */
id|port_settings.lloop
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now send the message to the device */
id|whiteheat_send_cmd
(paren
id|port-&gt;serial
comma
id|WHITEHEAT_SETUP_PORT
comma
(paren
id|__u8
op_star
)paren
op_amp
id|port_settings
comma
r_sizeof
(paren
id|port_settings
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|whiteheat_throttle
r_static
r_void
id|whiteheat_throttle
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
multiline_comment|/* Change the control signals */
multiline_comment|/* FIXME!!! */
r_return
suffix:semicolon
)brace
DECL|function|whiteheat_unthrottle
r_static
r_void
id|whiteheat_unthrottle
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
multiline_comment|/* Change the control signals */
multiline_comment|/* FIXME!!! */
r_return
suffix:semicolon
)brace
multiline_comment|/* steps to download the firmware to the WhiteHEAT device:&n; - hold the reset (by writing to the reset bit of the CPUCS register)&n; - download the VEND_AX.HEX file to the chip using VENDOR_REQUEST-ANCHOR_LOAD&n; - release the reset (by writing to the CPUCS register)&n; - download the WH.HEX file for all addresses greater than 0x1b3f using&n;   VENDOR_REQUEST-ANCHOR_EXTERNAL_RAM_LOAD&n; - hold the reset&n; - download the WH.HEX file for all addresses less than 0x1b40 using&n;   VENDOR_REQUEST_ANCHOR_LOAD&n; - release the reset&n; - device renumerated itself and comes up as new device id with all&n;   firmware download completed.&n;*/
DECL|function|whiteheat_startup
r_static
r_int
id|whiteheat_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_int
id|response
suffix:semicolon
r_const
r_struct
id|whiteheat_hex_record
op_star
id|record
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|response
op_assign
id|ezusb_set_reset
(paren
id|serial
comma
l_int|1
)paren
suffix:semicolon
id|record
op_assign
op_amp
id|whiteheat_loader
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|record-&gt;address
op_ne
l_int|0xffff
)paren
(brace
id|response
op_assign
id|ezusb_writememory
(paren
id|serial
comma
id|record-&gt;address
comma
(paren
r_int
r_char
op_star
)paren
id|record-&gt;data
comma
id|record-&gt;data_size
comma
l_int|0xa0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|response
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - ezusb_writememory failed for loader (%d %04X %p %d)&quot;
comma
id|response
comma
id|record-&gt;address
comma
id|record-&gt;data
comma
id|record-&gt;data_size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|record
suffix:semicolon
)brace
id|response
op_assign
id|ezusb_set_reset
(paren
id|serial
comma
l_int|0
)paren
suffix:semicolon
id|record
op_assign
op_amp
id|whiteheat_firmware
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|record-&gt;address
OL
l_int|0x1b40
)paren
(brace
op_increment
id|record
suffix:semicolon
)brace
r_while
c_loop
(paren
id|record-&gt;address
op_ne
l_int|0xffff
)paren
(brace
id|response
op_assign
id|ezusb_writememory
(paren
id|serial
comma
id|record-&gt;address
comma
(paren
r_int
r_char
op_star
)paren
id|record-&gt;data
comma
id|record-&gt;data_size
comma
l_int|0xa3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|response
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - ezusb_writememory failed for first firmware step (%d %04X %p %d)&quot;
comma
id|response
comma
id|record-&gt;address
comma
id|record-&gt;data
comma
id|record-&gt;data_size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|record
suffix:semicolon
)brace
id|response
op_assign
id|ezusb_set_reset
(paren
id|serial
comma
l_int|1
)paren
suffix:semicolon
id|record
op_assign
op_amp
id|whiteheat_firmware
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|record-&gt;address
OL
l_int|0x1b40
)paren
(brace
id|response
op_assign
id|ezusb_writememory
(paren
id|serial
comma
id|record-&gt;address
comma
(paren
r_int
r_char
op_star
)paren
id|record-&gt;data
comma
id|record-&gt;data_size
comma
l_int|0xa0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|response
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - ezusb_writememory failed for second firmware step (%d %04X %p %d)&quot;
comma
id|response
comma
id|record-&gt;address
comma
id|record-&gt;data
comma
id|record-&gt;data_size
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_increment
id|record
suffix:semicolon
)brace
id|response
op_assign
id|ezusb_set_reset
(paren
id|serial
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* we want this device to fail to have a driver assigned to it. */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|whiteheat_shutdown
r_static
r_void
id|whiteheat_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_struct
id|usb_serial_port
op_star
id|command_port
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dbg
c_func
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
id|whiteheat_close
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
multiline_comment|/* free up our private data for our command port */
id|command_port
op_assign
op_amp
id|serial-&gt;port
(braket
id|COMMAND_PORT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|command_port
op_member_access_from_pointer
r_private
op_ne
l_int|NULL
)paren
(brace
id|kfree
(paren
id|command_port
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|command_port
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|set_command
r_static
r_void
id|set_command
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|state
comma
r_int
r_char
id|command
)paren
(brace
r_struct
id|whiteheat_rdb_set
id|rdb_command
suffix:semicolon
multiline_comment|/* send a set rts command to the port */
multiline_comment|/* firmware uses 1 based port numbering */
id|rdb_command.port
op_assign
id|port-&gt;number
op_minus
id|port-&gt;serial-&gt;minor
op_plus
l_int|1
suffix:semicolon
id|rdb_command.state
op_assign
id|state
suffix:semicolon
id|whiteheat_send_cmd
(paren
id|port-&gt;serial
comma
id|command
comma
(paren
id|__u8
op_star
)paren
op_amp
id|rdb_command
comma
r_sizeof
(paren
id|rdb_command
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_rts
r_static
r_inline
r_void
id|set_rts
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|rts
)paren
(brace
id|set_command
(paren
id|port
comma
id|rts
comma
id|WHITEHEAT_SET_RTS
)paren
suffix:semicolon
)brace
DECL|function|set_dtr
r_static
r_inline
r_void
id|set_dtr
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|dtr
)paren
(brace
id|set_command
(paren
id|port
comma
id|dtr
comma
id|WHITEHEAT_SET_DTR
)paren
suffix:semicolon
)brace
DECL|function|set_break
r_static
r_inline
r_void
id|set_break
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_int
r_char
id|brk
)paren
(brace
id|set_command
(paren
id|port
comma
id|brk
comma
id|WHITEHEAT_SET_BREAK
)paren
suffix:semicolon
)brace
DECL|function|whiteheat_init
r_static
r_int
id|__init
id|whiteheat_init
(paren
r_void
)paren
(brace
id|usb_serial_register
(paren
op_amp
id|whiteheat_fake_device
)paren
suffix:semicolon
id|usb_serial_register
(paren
op_amp
id|whiteheat_device
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|whiteheat_exit
r_static
r_void
id|__exit
id|whiteheat_exit
(paren
r_void
)paren
(brace
id|usb_serial_deregister
(paren
op_amp
id|whiteheat_fake_device
)paren
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|whiteheat_device
)paren
suffix:semicolon
)brace
DECL|variable|whiteheat_init
id|module_init
c_func
(paren
id|whiteheat_init
)paren
suffix:semicolon
DECL|variable|whiteheat_exit
id|module_exit
c_func
(paren
id|whiteheat_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;USB ConnectTech WhiteHEAT driver&quot;
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
