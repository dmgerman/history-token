multiline_comment|/*&n; * USB Serial Converter driver&n; *&n; *&t;Copyright (C) 1999 - 2002&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * (03/26/2002) gkh&n; *&t;removed the port-&gt;tty check from port_paranoia_check() due to serial&n; *&t;consoles not having a tty device assigned to them.&n; *&n; * (12/03/2001) gkh&n; *&t;removed active from the port structure.&n; *&t;added documentation to the usb_serial_device_type structure&n; *&n; * (10/10/2001) gkh&n; *&t;added vendor and product to serial structure.  Needed to determine device&n; *&t;owner when the device is disconnected.&n; *&n; * (05/30/2001) gkh&n; *&t;added sem to port structure and removed port_lock&n; *&n; * (10/05/2000) gkh&n; *&t;Added interrupt_in_endpointAddress and bulk_in_endpointAddress to help&n; *&t;fix bug with urb-&gt;dev not being set properly, now that the usb core&n; *&t;needs it.&n; * &n; * (09/11/2000) gkh&n; *&t;Added usb_serial_debug_data function to help get rid of #DEBUG in the&n; *&t;drivers.&n; *&n; * (08/28/2000) gkh&n; *&t;Added port_lock to port structure.&n; *&n; * (08/08/2000) gkh&n; *&t;Added open_count to port structure.&n; *&n; * (07/23/2000) gkh&n; *&t;Added bulk_out_endpointAddress to port structure.&n; *&n; * (07/19/2000) gkh, pberger, and borchers&n; *&t;Modifications to allow usb-serial drivers to be modules.&n; *&n; * &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_H
DECL|macro|__LINUX_USB_SERIAL_H
mdefine_line|#define __LINUX_USB_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SERIAL_TTY_MAJOR
mdefine_line|#define SERIAL_TTY_MAJOR&t;188&t;/* Nice legal number now */
DECL|macro|SERIAL_TTY_MINORS
mdefine_line|#define SERIAL_TTY_MINORS&t;255&t;/* loads of devices :) */
DECL|macro|MAX_NUM_PORTS
mdefine_line|#define MAX_NUM_PORTS&t;&t;8&t;/* The maximum number of ports one device can grab at once */
DECL|macro|USB_SERIAL_MAGIC
mdefine_line|#define USB_SERIAL_MAGIC&t;0x6702&t;/* magic number for usb_serial struct */
DECL|macro|USB_SERIAL_PORT_MAGIC
mdefine_line|#define USB_SERIAL_PORT_MAGIC&t;0x7301&t;/* magic number for usb_serial_port struct */
multiline_comment|/* parity check flag */
DECL|macro|RELEVANT_IFLAG
mdefine_line|#define RELEVANT_IFLAG(iflag)&t;(iflag &amp; (IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK))
DECL|struct|usb_serial_port
r_struct
id|usb_serial_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|serial
r_struct
id|usb_serial
op_star
id|serial
suffix:semicolon
multiline_comment|/* pointer back to the owner of this port */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* the coresponding tty for this port */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
DECL|member|interrupt_in_buffer
r_int
r_char
op_star
id|interrupt_in_buffer
suffix:semicolon
DECL|member|interrupt_in_urb
r_struct
id|urb
op_star
id|interrupt_in_urb
suffix:semicolon
DECL|member|interrupt_in_endpointAddress
id|__u8
id|interrupt_in_endpointAddress
suffix:semicolon
DECL|member|bulk_in_buffer
r_int
r_char
op_star
id|bulk_in_buffer
suffix:semicolon
DECL|member|read_urb
r_struct
id|urb
op_star
id|read_urb
suffix:semicolon
DECL|member|bulk_in_endpointAddress
id|__u8
id|bulk_in_endpointAddress
suffix:semicolon
DECL|member|bulk_out_buffer
r_int
r_char
op_star
id|bulk_out_buffer
suffix:semicolon
DECL|member|bulk_out_size
r_int
id|bulk_out_size
suffix:semicolon
DECL|member|write_urb
r_struct
id|urb
op_star
id|write_urb
suffix:semicolon
DECL|member|bulk_out_endpointAddress
id|__u8
id|bulk_out_endpointAddress
suffix:semicolon
DECL|member|write_wait
id|wait_queue_head_t
id|write_wait
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
multiline_comment|/* task queue for line discipline waking up */
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
multiline_comment|/* number of times this port has been opened */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* locks this structure */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* data private to the specific port */
)brace
suffix:semicolon
DECL|struct|usb_serial
r_struct
id|usb_serial
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|type
r_struct
id|usb_serial_device_type
op_star
id|type
suffix:semicolon
multiline_comment|/* the type of usb serial device this is */
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
multiline_comment|/* the interface for this device */
DECL|member|tty_driver
r_struct
id|tty_driver
op_star
id|tty_driver
suffix:semicolon
multiline_comment|/* the tty_driver for this device */
DECL|member|minor
r_int
r_char
id|minor
suffix:semicolon
multiline_comment|/* the starting minor number for this device */
DECL|member|num_ports
r_int
r_char
id|num_ports
suffix:semicolon
multiline_comment|/* the number of ports this device has */
DECL|member|num_interrupt_in
r_char
id|num_interrupt_in
suffix:semicolon
multiline_comment|/* number of interrupt in endpoints we have */
DECL|member|num_bulk_in
r_char
id|num_bulk_in
suffix:semicolon
multiline_comment|/* number of bulk in endpoints we have */
DECL|member|num_bulk_out
r_char
id|num_bulk_out
suffix:semicolon
multiline_comment|/* number of bulk out endpoints we have */
DECL|member|vendor
id|__u16
id|vendor
suffix:semicolon
multiline_comment|/* vendor id of this device */
DECL|member|product
id|__u16
id|product
suffix:semicolon
multiline_comment|/* product id of this device */
DECL|member|port
r_struct
id|usb_serial_port
id|port
(braket
id|MAX_NUM_PORTS
)braket
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* data private to the specific driver */
)brace
suffix:semicolon
DECL|macro|NUM_DONT_CARE
mdefine_line|#define NUM_DONT_CARE&t;(-1)
multiline_comment|/**&n; * usb_serial_device_type - a structure that defines a usb serial device&n; * @owner: pointer to the module that owns this device.&n; * @name: pointer to a string that describes this device.  This string used&n; *&t;in the syslog messages when a device is inserted or removed.&n; * @id_table: pointer to a list of usb_device_id structures that define all&n; *&t;of the devices this structure can support.&n; * @num_interrupt_in: the number of interrupt in endpoints this device will&n; *&t;have.&n; * @num_bulk_in: the number of bulk in endpoints this device will have.&n; * @num_bulk_out: the number of bulk out endpoints this device will have.&n; * @num_ports: the number of different ports this device will have.&n; * @calc_num_ports: pointer to a function to determine how many ports this&n; *&t;device has dynamically.  It will be called after the probe()&n; *&t;callback is called, but before attach()&n; * @probe: pointer to the driver&squot;s probe function.&n; *&t;This will be called when the device is inserted into the system,&n; *&t;but before the device has been fully initialized by the usb_serial&n; *&t;subsystem.  Use this function to download any firmware to the device,&n; *&t;or any other early initialization that might be needed.&n; *&t;Return 0 to continue on with the initialization sequence.  Anything &n; *&t;else will abort it.&n; * @attach: pointer to the driver&squot;s attach function.&n; *&t;This will be called when the struct usb_serial structure is fully set&n; *&t;set up.  Do any local initialization of the device, or any private&n; *&t;memory structure allocation at this point in time.&n; * @shutdown: pointer to the driver&squot;s shutdown function.  This will be&n; *&t;called when the device is removed from the system.&n; *&n; * This structure is defines a USB Serial device.  It provides all of&n; * the information that the USB serial core code needs.  If the function&n; * pointers are defined, then the USB serial core code will call them when&n; * the corresponding tty port functions are called.  If they are not&n; * called, the generic serial function will be used instead.&n; */
DECL|struct|usb_serial_device_type
r_struct
id|usb_serial_device_type
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|usb_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|num_interrupt_in
r_char
id|num_interrupt_in
suffix:semicolon
DECL|member|num_bulk_in
r_char
id|num_bulk_in
suffix:semicolon
DECL|member|num_bulk_out
r_char
id|num_bulk_out
suffix:semicolon
DECL|member|num_ports
r_char
id|num_ports
suffix:semicolon
DECL|member|driver_list
r_struct
id|list_head
id|driver_list
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
DECL|member|calc_num_ports
r_int
(paren
op_star
id|calc_num_ports
)paren
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
multiline_comment|/* serial function calls */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
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
DECL|member|close
r_void
(paren
op_star
id|close
)paren
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
DECL|member|write
r_int
(paren
op_star
id|write
)paren
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
DECL|member|write_room
r_int
(paren
op_star
id|write_room
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
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
DECL|member|set_termios
r_void
(paren
op_star
id|set_termios
)paren
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
DECL|member|break_ctl
r_void
(paren
op_star
id|break_ctl
)paren
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
DECL|member|chars_in_buffer
r_int
(paren
op_star
id|chars_in_buffer
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|member|throttle
r_void
(paren
op_star
id|throttle
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|member|unthrottle
r_void
(paren
op_star
id|unthrottle
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|member|read_int_callback
r_void
(paren
op_star
id|read_int_callback
)paren
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|read_bulk_callback
r_void
(paren
op_star
id|read_bulk_callback
)paren
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|write_bulk_callback
r_void
(paren
op_star
id|write_bulk_callback
)paren
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|usb_serial_register
c_func
(paren
r_struct
id|usb_serial_device_type
op_star
id|new_device
)paren
suffix:semicolon
r_extern
r_void
id|usb_serial_deregister
c_func
(paren
r_struct
id|usb_serial_device_type
op_star
id|device
)paren
suffix:semicolon
multiline_comment|/* determine if we should include the EzUSB loader functions */
DECL|macro|USES_EZUSB_FUNCTIONS
macro_line|#undef USES_EZUSB_FUNCTIONS
macro_line|#if defined(CONFIG_USB_SERIAL_KEYSPAN_PDA) || defined(CONFIG_USB_SERIAL_KEYSPAN_PDA_MODULE)
DECL|macro|USES_EZUSB_FUNCTIONS
mdefine_line|#define USES_EZUSB_FUNCTIONS
macro_line|#endif
macro_line|#if defined(CONFIG_USB_SERIAL_XIRCOM) || defined(CONFIG_USB_SERIAL_XIRCOM_MODULE)
DECL|macro|USES_EZUSB_FUNCTIONS
mdefine_line|#define USES_EZUSB_FUNCTIONS
macro_line|#endif
macro_line|#if defined(CONFIG_USB_SERIAL_KEYSPAN) || defined(CONFIG_USB_SERIAL_KEYSPAN_MODULE)
DECL|macro|USES_EZUSB_FUNCTIONS
mdefine_line|#define USES_EZUSB_FUNCTIONS
macro_line|#endif
macro_line|#if defined(CONFIG_USB_SERIAL_WHITEHEAT) || defined(CONFIG_USB_SERIAL_WHITEHEAT_MODULE)
DECL|macro|USES_EZUSB_FUNCTIONS
mdefine_line|#define USES_EZUSB_FUNCTIONS
macro_line|#endif
macro_line|#ifdef USES_EZUSB_FUNCTIONS
r_extern
r_int
id|ezusb_writememory
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_int
id|address
comma
r_int
r_char
op_star
id|data
comma
r_int
id|length
comma
id|__u8
id|bRequest
)paren
suffix:semicolon
r_extern
r_int
id|ezusb_set_reset
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_int
r_char
id|reset_bit
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Inline functions to check the sanity of a pointer that is passed to us */
DECL|function|serial_paranoia_check
r_static
r_inline
r_int
id|serial_paranoia_check
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_const
r_char
op_star
id|function
)paren
(brace
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
l_string|&quot;%s - serial == NULL&quot;
comma
id|function
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
id|serial-&gt;magic
op_ne
id|USB_SERIAL_MAGIC
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - bad magic number for serial&quot;
comma
id|function
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
op_logical_neg
id|serial-&gt;type
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - serial-&gt;type == NULL!&quot;
comma
id|function
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|port_paranoia_check
r_static
r_inline
r_int
id|port_paranoia_check
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_const
r_char
op_star
id|function
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - port == NULL&quot;
comma
id|function
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
id|port-&gt;magic
op_ne
id|USB_SERIAL_PORT_MAGIC
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - bad magic number for port&quot;
comma
id|function
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
op_logical_neg
id|port-&gt;serial
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - port-&gt;serial == NULL&quot;
comma
id|function
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_usb_serial
r_static
r_inline
r_struct
id|usb_serial
op_star
id|get_usb_serial
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_const
r_char
op_star
id|function
)paren
(brace
multiline_comment|/* if no port was specified, or it fails a paranoia check */
r_if
c_cond
(paren
op_logical_neg
id|port
op_logical_or
id|port_paranoia_check
(paren
id|port
comma
id|function
)paren
op_logical_or
id|serial_paranoia_check
(paren
id|port-&gt;serial
comma
id|function
)paren
)paren
(brace
multiline_comment|/* then say that we dont have a valid usb_serial thing, which will&n;&t;&t; * end up genrating -ENODEV return values */
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|port-&gt;serial
suffix:semicolon
)brace
DECL|function|usb_serial_debug_data
r_static
r_inline
r_void
id|usb_serial_debug_data
(paren
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|function
comma
r_int
id|size
comma
r_const
r_int
r_char
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|debug
)paren
r_return
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: %s - length = %d, data = &quot;
comma
id|file
comma
id|function
comma
id|size
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
id|size
suffix:semicolon
op_increment
id|i
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
multiline_comment|/* Use our own dbg macro */
DECL|macro|dbg
macro_line|#undef dbg
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do { if (debug) printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg); } while (0)
macro_line|#endif&t;/* ifdef __LINUX_USB_SERIAL_H */
eof
