multiline_comment|/*&n; * Belkin USB Serial Adapter Driver&n; *&n; *  Copyright (C) 2000&t;&t;William Greathouse (wgreathouse@smva.com)&n; *  Copyright (C) 2000-2001 &t;Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *  This program is largely derived from work by the linux-usb group&n; *  and associated source files.  Please see the usb/serial files for&n; *  individual credits and copyrights.&n; *  &n; * &t;This program is free software; you can redistribute it and/or modify&n; * &t;it under the terms of the GNU General Public License as published by&n; * &t;the Free Software Foundation; either version 2 of the License, or&n; * &t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * TODO:&n; * -- Add true modem contol line query capability.  Currently we track the&n; *    states reported by the interrupt and the states we request.&n; * -- Add error reporting back to application for UART error conditions.&n; *    Just point me at how to implement this and I&squot;ll do it. I&squot;ve put the&n; *    framework in, but haven&squot;t analyzed the &quot;tty_flip&quot; interface yet.&n; * -- Add support for flush commands&n; * -- Add everything that is missing :)&n; *&n; * 27-Nov-2001 gkh&n; * &t;compressed all the differnent device entries into 1.&n; *&n; * 30-May-2001 gkh&n; *&t;switched from using spinlock to a semaphore, which fixes lots of problems.&n; *&n; * 08-Apr-2001 gb&n; *&t;- Identify version on module load.&n; *&n; * 12-Mar-2001 gkh&n; *&t;- Added support for the GoHubs GO-COM232 device which is the same as the&n; *&t;  Peracom device.&n; *&n; * 06-Nov-2000 gkh&n; *&t;- Added support for the old Belkin and Peracom devices.&n; *&t;- Made the port able to be opened multiple times.&n; *&t;- Added some defaults incase the line settings are things these devices&n; *&t;  can&squot;t support. &n; *&n; * 18-Oct-2000 William Greathouse&n; *    Released into the wild (linux-usb-devel)&n; *&n; * 17-Oct-2000 William Greathouse&n; *    Add code to recognize firmware version and set hardware flow control&n; *    appropriately.  Belkin states that firmware prior to 3.05 does not&n; *    operate correctly in hardware handshake mode.  I have verified this&n; *    on firmware 2.05 -- for both RTS and DTR input flow control, the control&n; *    line is not reset.  The test performed by the Belkin Win* driver is&n; *    to enable hardware flow control for firmware 2.06 or greater and&n; *    for 1.00 or prior.  I am only enabling for 2.06 or greater.&n; *&n; * 12-Oct-2000 William Greathouse&n; *    First cut at supporting Belkin USB Serial Adapter F5U103&n; *    I did not have a copy of the original work to support this&n; *    adapter, so pardon any stupid mistakes.  All of the information&n; *    I am using to write this driver was acquired by using a modified&n; *    UsbSnoop on Windows2000 and from examining the other USB drivers.&n; */
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
macro_line|#include &quot;belkin_sa.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v1.2&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;William Greathouse &lt;wgreathouse@smva.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Belkin Serial converter driver&quot;
multiline_comment|/* function prototypes for a Belkin USB Serial Adapter F5U103 */
r_static
r_int
id|belkin_sa_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_void
id|belkin_sa_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_static
r_int
id|belkin_sa_open
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
id|belkin_sa_close
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
id|belkin_sa_read_int_callback
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
id|belkin_sa_set_termios
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
id|belkin_sa_ioctl
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
id|belkin_sa_break_ctl
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
r_static
r_int
id|belkin_sa_tiocmget
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
)paren
suffix:semicolon
r_static
r_int
id|belkin_sa_tiocmset
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
id|set
comma
r_int
r_int
id|clear
)paren
suffix:semicolon
DECL|variable|id_table_combined
r_static
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
id|BELKIN_SA_VID
comma
id|BELKIN_SA_PID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|BELKIN_OLD_VID
comma
id|BELKIN_OLD_PID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|PERACOM_VID
comma
id|PERACOM_PID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|GOHUBS_VID
comma
id|GOHUBS_PID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|GOHUBS_VID
comma
id|HANDYLINK_PID
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|BELKIN_DOCKSTATION_VID
comma
id|BELKIN_DOCKSTATION_PID
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
DECL|variable|belkin_driver
r_static
r_struct
id|usb_driver
id|belkin_driver
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
l_string|&quot;belkin&quot;
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
id|id_table_combined
comma
)brace
suffix:semicolon
multiline_comment|/* All of the device info needed for the serial converters */
DECL|variable|belkin_device
r_static
r_struct
id|usb_serial_device_type
id|belkin_device
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
l_string|&quot;Belkin / Peracom / GoHubs USB Serial Adapter&quot;
comma
dot
id|short_name
op_assign
l_string|&quot;belkin&quot;
comma
dot
id|id_table
op_assign
id|id_table_combined
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
id|open
op_assign
id|belkin_sa_open
comma
dot
id|close
op_assign
id|belkin_sa_close
comma
dot
id|read_int_callback
op_assign
id|belkin_sa_read_int_callback
comma
multiline_comment|/* How we get the status info */
dot
id|ioctl
op_assign
id|belkin_sa_ioctl
comma
dot
id|set_termios
op_assign
id|belkin_sa_set_termios
comma
dot
id|break_ctl
op_assign
id|belkin_sa_break_ctl
comma
dot
id|tiocmget
op_assign
id|belkin_sa_tiocmget
comma
dot
id|tiocmset
op_assign
id|belkin_sa_tiocmset
comma
dot
id|attach
op_assign
id|belkin_sa_startup
comma
dot
id|shutdown
op_assign
id|belkin_sa_shutdown
comma
)brace
suffix:semicolon
DECL|struct|belkin_sa_private
r_struct
id|belkin_sa_private
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|control_state
r_int
r_int
id|control_state
suffix:semicolon
DECL|member|last_lsr
r_int
r_char
id|last_lsr
suffix:semicolon
DECL|member|last_msr
r_int
r_char
id|last_msr
suffix:semicolon
DECL|member|bad_flow_control
r_int
id|bad_flow_control
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ***************************************************************************&n; * Belkin USB Serial Adapter F5U103 specific driver functions&n; * ***************************************************************************&n; */
DECL|macro|WDR_TIMEOUT
mdefine_line|#define WDR_TIMEOUT (HZ * 5 ) /* default urb timeout */
multiline_comment|/* assumes that struct usb_serial *serial is available */
DECL|macro|BSA_USB_CMD
mdefine_line|#define BSA_USB_CMD(c,v) usb_control_msg(serial-&gt;dev, usb_sndctrlpipe(serial-&gt;dev, 0), &bslash;&n;&t;&t;&t;&t;&t;    (c), BELKIN_SA_SET_REQUEST_TYPE, &bslash;&n;&t;&t;&t;&t;&t;    (v), 0, NULL, 0, WDR_TIMEOUT)
multiline_comment|/* do some startup allocations not currently performed by usb_serial_probe() */
DECL|function|belkin_sa_startup
r_static
r_int
id|belkin_sa_startup
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|serial-&gt;dev
suffix:semicolon
r_struct
id|belkin_sa_private
op_star
id|priv
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
id|belkin_sa_private
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
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* error */
multiline_comment|/* set initial values for control structures */
id|spin_lock_init
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|priv-&gt;control_state
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;last_lsr
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;last_msr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* see comments at top of file */
id|priv-&gt;bad_flow_control
op_assign
(paren
id|dev-&gt;descriptor.bcdDevice
op_le
l_int|0x0206
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;bcdDevice: %04x, bfc: %d&quot;
comma
id|dev-&gt;descriptor.bcdDevice
comma
id|priv-&gt;bad_flow_control
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|belkin_sa_shutdown
r_static
r_void
id|belkin_sa_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_struct
id|belkin_sa_private
op_star
id|priv
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dbg
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
multiline_comment|/* My special items, the standard routines free my urbs */
id|priv
op_assign
id|usb_get_serial_port_data
c_func
(paren
id|serial-&gt;port
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv
)paren
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
)brace
DECL|function|belkin_sa_open
r_static
r_int
id|belkin_sa_open
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
id|retval
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
multiline_comment|/*Start reading from the device*/
multiline_comment|/* TODO: Look at possibility of submitting multiple URBs to device to&n;&t; *       enhance buffering.  Win trace shows 16 initial read URBs.&n;&t; */
id|port-&gt;read_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|retval
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
id|retval
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usb_submit_urb(read bulk) failed&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|port-&gt;interrupt_in_urb-&gt;dev
op_assign
id|port-&gt;serial-&gt;dev
suffix:semicolon
id|retval
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
id|retval
)paren
(brace
id|usb_kill_urb
c_func
(paren
id|port-&gt;read_urb
)paren
suffix:semicolon
id|err
c_func
(paren
l_string|&quot; usb_submit_urb(read int) failed&quot;
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* belkin_sa_open */
DECL|function|belkin_sa_close
r_static
r_void
id|belkin_sa_close
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
l_string|&quot;%s port %d&quot;
comma
id|__FUNCTION__
comma
id|port-&gt;number
)paren
suffix:semicolon
multiline_comment|/* shutdown our bulk reads and writes */
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
id|usb_kill_urb
c_func
(paren
id|port-&gt;interrupt_in_urb
)paren
suffix:semicolon
)brace
multiline_comment|/* belkin_sa_close */
DECL|function|belkin_sa_read_int_callback
r_static
r_void
id|belkin_sa_read_int_callback
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
id|belkin_sa_private
op_star
id|priv
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|urb-&gt;status
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* success */
r_break
suffix:semicolon
r_case
op_minus
id|ECONNRESET
suffix:colon
r_case
op_minus
id|ENOENT
suffix:colon
r_case
op_minus
id|ESHUTDOWN
suffix:colon
multiline_comment|/* this urb is terminated, clean up */
id|dbg
c_func
(paren
l_string|&quot;%s - urb shutting down with status: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - nonzero urb status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_goto
m_exit
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
multiline_comment|/* Handle known interrupt data */
multiline_comment|/* ignore data[0] and data[1] */
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
id|priv-&gt;last_msr
op_assign
id|data
(braket
id|BELKIN_SA_MSR_INDEX
)braket
suffix:semicolon
multiline_comment|/* Record Control Line states */
r_if
c_cond
(paren
id|priv-&gt;last_msr
op_amp
id|BELKIN_SA_MSR_DSR
)paren
id|priv-&gt;control_state
op_or_assign
id|TIOCM_DSR
suffix:semicolon
r_else
id|priv-&gt;control_state
op_and_assign
op_complement
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;last_msr
op_amp
id|BELKIN_SA_MSR_CTS
)paren
id|priv-&gt;control_state
op_or_assign
id|TIOCM_CTS
suffix:semicolon
r_else
id|priv-&gt;control_state
op_and_assign
op_complement
id|TIOCM_CTS
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;last_msr
op_amp
id|BELKIN_SA_MSR_RI
)paren
id|priv-&gt;control_state
op_or_assign
id|TIOCM_RI
suffix:semicolon
r_else
id|priv-&gt;control_state
op_and_assign
op_complement
id|TIOCM_RI
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;last_msr
op_amp
id|BELKIN_SA_MSR_CD
)paren
id|priv-&gt;control_state
op_or_assign
id|TIOCM_CD
suffix:semicolon
r_else
id|priv-&gt;control_state
op_and_assign
op_complement
id|TIOCM_CD
suffix:semicolon
multiline_comment|/* Now to report any errors */
id|priv-&gt;last_lsr
op_assign
id|data
(braket
id|BELKIN_SA_LSR_INDEX
)braket
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * fill in the flip buffer here, but I do not know the relation&n;&t; * to the current/next receive buffer or characters.  I need&n;&t; * to look in to this before committing any code.&n;&t; */
r_if
c_cond
(paren
id|priv-&gt;last_lsr
op_amp
id|BELKIN_SA_LSR_ERR
)paren
(brace
id|tty
op_assign
id|port-&gt;tty
suffix:semicolon
multiline_comment|/* Overrun Error */
r_if
c_cond
(paren
id|priv-&gt;last_lsr
op_amp
id|BELKIN_SA_LSR_OE
)paren
(brace
)brace
multiline_comment|/* Parity Error */
r_if
c_cond
(paren
id|priv-&gt;last_lsr
op_amp
id|BELKIN_SA_LSR_PE
)paren
(brace
)brace
multiline_comment|/* Framing Error */
r_if
c_cond
(paren
id|priv-&gt;last_lsr
op_amp
id|BELKIN_SA_LSR_FE
)paren
(brace
)brace
multiline_comment|/* Break Indicator */
r_if
c_cond
(paren
id|priv-&gt;last_lsr
op_amp
id|BELKIN_SA_LSR_BI
)paren
(brace
)brace
)brace
macro_line|#endif
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
m_exit
suffix:colon
id|retval
op_assign
id|usb_submit_urb
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|err
(paren
l_string|&quot;%s - usb_submit_urb failed with result %d&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
)brace
DECL|function|belkin_sa_set_termios
r_static
r_void
id|belkin_sa_set_termios
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
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_struct
id|belkin_sa_private
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
id|iflag
suffix:semicolon
r_int
r_int
id|cflag
suffix:semicolon
r_int
r_int
id|old_iflag
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|old_cflag
op_assign
l_int|0
suffix:semicolon
id|__u16
id|urb_value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Will hold the new flags */
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|control_state
suffix:semicolon
r_int
id|bad_flow_control
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
(paren
l_string|&quot;%s - no tty or termios structure&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_iflag
suffix:semicolon
id|cflag
op_assign
id|port-&gt;tty-&gt;termios-&gt;c_cflag
suffix:semicolon
multiline_comment|/* get a local copy of the current port settings */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|control_state
op_assign
id|priv-&gt;control_state
suffix:semicolon
id|bad_flow_control
op_assign
id|priv-&gt;bad_flow_control
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
id|old_iflag
op_assign
id|old_termios-&gt;c_iflag
suffix:semicolon
id|old_cflag
op_assign
id|old_termios-&gt;c_cflag
suffix:semicolon
)brace
multiline_comment|/* Set the baud rate */
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
multiline_comment|/* reassert DTR and (maybe) RTS on transition from B0 */
r_if
c_cond
(paren
(paren
id|old_cflag
op_amp
id|CBAUD
)paren
op_eq
id|B0
)paren
(brace
id|control_state
op_or_assign
(paren
id|TIOCM_DTR
op_or
id|TIOCM_RTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_DTR_REQUEST
comma
l_int|1
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set DTR error&quot;
)paren
suffix:semicolon
multiline_comment|/* don&squot;t set RTS if using hardware flow control */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old_cflag
op_amp
id|CRTSCTS
)paren
)paren
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_RTS_REQUEST
comma
l_int|1
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set RTS error&quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cflag
op_amp
id|CBAUD
)paren
(brace
r_case
id|B0
suffix:colon
multiline_comment|/* handled below */
r_break
suffix:semicolon
r_case
id|B300
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|300
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B600
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|600
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B1200
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|1200
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B2400
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|2400
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B4800
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|4800
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B9600
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|9600
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B19200
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|19200
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B38400
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|38400
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B57600
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|57600
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B115200
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|115200
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B230400
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|230400
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
c_func
(paren
l_string|&quot;BELKIN USB Serial Adapter: unsupported baudrate request, using default of 9600&quot;
)paren
suffix:semicolon
id|urb_value
op_assign
id|BELKIN_SA_BAUD
c_func
(paren
l_int|9600
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cflag
op_amp
id|CBAUD
)paren
op_ne
id|B0
)paren
(brace
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_BAUDRATE_REQUEST
comma
id|urb_value
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set baudrate error&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Disable flow control */
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_FLOW_CTRL_REQUEST
comma
id|BELKIN_SA_FLOW_NONE
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Disable flowcontrol error&quot;
)paren
suffix:semicolon
multiline_comment|/* Drop RTS and DTR */
id|control_state
op_and_assign
op_complement
(paren
id|TIOCM_DTR
op_or
id|TIOCM_RTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_DTR_REQUEST
comma
l_int|0
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;DTR LOW error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_RTS_REQUEST
comma
l_int|0
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;RTS LOW error&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* set the parity */
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
r_if
c_cond
(paren
id|cflag
op_amp
id|PARENB
)paren
id|urb_value
op_assign
(paren
id|cflag
op_amp
id|PARODD
)paren
ques
c_cond
id|BELKIN_SA_PARITY_ODD
suffix:colon
id|BELKIN_SA_PARITY_EVEN
suffix:semicolon
r_else
id|urb_value
op_assign
id|BELKIN_SA_PARITY_NONE
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_PARITY_REQUEST
comma
id|urb_value
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set parity error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* set the number of data bits */
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
id|urb_value
op_assign
id|BELKIN_SA_DATA_BITS
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS6
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_DATA_BITS
c_func
(paren
l_int|6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS7
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_DATA_BITS
c_func
(paren
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS8
suffix:colon
id|urb_value
op_assign
id|BELKIN_SA_DATA_BITS
c_func
(paren
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
c_func
(paren
l_string|&quot;CSIZE was not CS5-CS8, using default of 8&quot;
)paren
suffix:semicolon
id|urb_value
op_assign
id|BELKIN_SA_DATA_BITS
c_func
(paren
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_DATA_BITS_REQUEST
comma
id|urb_value
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set data bits error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* set the number of stop bits */
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
id|urb_value
op_assign
(paren
id|cflag
op_amp
id|CSTOPB
)paren
ques
c_cond
id|BELKIN_SA_STOP_BITS
c_func
(paren
l_int|2
)paren
suffix:colon
id|BELKIN_SA_STOP_BITS
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_STOP_BITS_REQUEST
comma
id|urb_value
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set stop bits error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Set flow control */
r_if
c_cond
(paren
(paren
id|iflag
op_amp
id|IXOFF
)paren
op_ne
(paren
id|old_iflag
op_amp
id|IXOFF
)paren
op_logical_or
(paren
id|iflag
op_amp
id|IXON
)paren
op_ne
(paren
id|old_iflag
op_amp
id|IXON
)paren
op_logical_or
(paren
id|cflag
op_amp
id|CRTSCTS
)paren
op_ne
(paren
id|old_cflag
op_amp
id|CRTSCTS
)paren
)paren
(brace
id|urb_value
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iflag
op_amp
id|IXOFF
)paren
op_logical_or
(paren
id|iflag
op_amp
id|IXON
)paren
)paren
id|urb_value
op_or_assign
(paren
id|BELKIN_SA_FLOW_OXON
op_or
id|BELKIN_SA_FLOW_IXON
)paren
suffix:semicolon
r_else
id|urb_value
op_and_assign
op_complement
(paren
id|BELKIN_SA_FLOW_OXON
op_or
id|BELKIN_SA_FLOW_IXON
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cflag
op_amp
id|CRTSCTS
)paren
id|urb_value
op_or_assign
(paren
id|BELKIN_SA_FLOW_OCTS
op_or
id|BELKIN_SA_FLOW_IRTS
)paren
suffix:semicolon
r_else
id|urb_value
op_and_assign
op_complement
(paren
id|BELKIN_SA_FLOW_OCTS
op_or
id|BELKIN_SA_FLOW_IRTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad_flow_control
)paren
id|urb_value
op_and_assign
op_complement
(paren
id|BELKIN_SA_FLOW_IRTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_FLOW_CTRL_REQUEST
comma
id|urb_value
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set flow control error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* save off the modified port settings */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|priv-&gt;control_state
op_assign
id|control_state
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
)brace
multiline_comment|/* belkin_sa_set_termios */
DECL|function|belkin_sa_break_ctl
r_static
r_void
id|belkin_sa_break_ctl
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
r_struct
id|usb_serial
op_star
id|serial
op_assign
id|port-&gt;serial
suffix:semicolon
r_if
c_cond
(paren
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_BREAK_REQUEST
comma
id|break_state
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;Set break_ctl %d&quot;
comma
id|break_state
)paren
suffix:semicolon
)brace
DECL|function|belkin_sa_tiocmget
r_static
r_int
id|belkin_sa_tiocmget
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
)paren
(brace
r_struct
id|belkin_sa_private
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
id|control_state
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
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
id|control_state
op_assign
id|priv-&gt;control_state
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
id|control_state
suffix:semicolon
)brace
DECL|function|belkin_sa_tiocmset
r_static
r_int
id|belkin_sa_tiocmset
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
id|set
comma
r_int
r_int
id|clear
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
id|belkin_sa_private
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
id|control_state
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|rts
op_assign
l_int|0
suffix:semicolon
r_int
id|dtr
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&quot;
comma
id|__FUNCTION__
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
id|control_state
op_assign
id|priv-&gt;control_state
suffix:semicolon
r_if
c_cond
(paren
id|set
op_amp
id|TIOCM_RTS
)paren
(brace
id|control_state
op_or_assign
id|TIOCM_RTS
suffix:semicolon
id|rts
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|set
op_amp
id|TIOCM_DTR
)paren
(brace
id|control_state
op_or_assign
id|TIOCM_DTR
suffix:semicolon
id|dtr
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clear
op_amp
id|TIOCM_RTS
)paren
(brace
id|control_state
op_and_assign
op_complement
id|TIOCM_RTS
suffix:semicolon
id|rts
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clear
op_amp
id|TIOCM_DTR
)paren
(brace
id|control_state
op_and_assign
op_complement
id|TIOCM_DTR
suffix:semicolon
id|dtr
op_assign
l_int|0
suffix:semicolon
)brace
id|priv-&gt;control_state
op_assign
id|control_state
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
id|retval
op_assign
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_RTS_REQUEST
comma
id|rts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Set RTS error %d&quot;
comma
id|retval
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|retval
op_assign
id|BSA_USB_CMD
c_func
(paren
id|BELKIN_SA_SET_DTR_REQUEST
comma
id|dtr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Set DTR error %d&quot;
comma
id|retval
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|belkin_sa_ioctl
r_static
r_int
id|belkin_sa_ioctl
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCMIWAIT
suffix:colon
multiline_comment|/* wait for any of the 4 modem inputs (DCD,RI,DSR,CTS)*/
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
r_case
id|TIOCGICOUNT
suffix:colon
multiline_comment|/* return count of modemline transitions */
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;belkin_sa_ioctl arg not supported - 0x%04x&quot;
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* belkin_sa_ioctl */
DECL|function|belkin_sa_init
r_static
r_int
id|__init
id|belkin_sa_init
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
id|belkin_device
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
id|belkin_driver
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
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
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
id|belkin_device
)paren
suffix:semicolon
id|failed_usb_serial_register
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|belkin_sa_exit
r_static
r_void
id|__exit
id|belkin_sa_exit
(paren
r_void
)paren
(brace
id|usb_deregister
(paren
op_amp
id|belkin_driver
)paren
suffix:semicolon
id|usb_serial_deregister
(paren
op_amp
id|belkin_device
)paren
suffix:semicolon
)brace
DECL|variable|belkin_sa_init
id|module_init
(paren
id|belkin_sa_init
)paren
suffix:semicolon
DECL|variable|belkin_sa_exit
id|module_exit
(paren
id|belkin_sa_exit
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
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
eof
