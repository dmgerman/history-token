multiline_comment|/*&n; * USB Serial Converter driver&n; *&n; *&t;Copyright (C) 1999 - 2004&n; *&t;    Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * (03/26/2002) gkh&n; *&t;removed the port-&gt;tty check from port_paranoia_check() due to serial&n; *&t;consoles not having a tty device assigned to them.&n; *&n; * (12/03/2001) gkh&n; *&t;removed active from the port structure.&n; *&t;added documentation to the usb_serial_device_type structure&n; *&n; * (10/10/2001) gkh&n; *&t;added vendor and product to serial structure.  Needed to determine device&n; *&t;owner when the device is disconnected.&n; *&n; * (05/30/2001) gkh&n; *&t;added sem to port structure and removed port_lock&n; *&n; * (10/05/2000) gkh&n; *&t;Added interrupt_in_endpointAddress and bulk_in_endpointAddress to help&n; *&t;fix bug with urb-&gt;dev not being set properly, now that the usb core&n; *&t;needs it.&n; * &n; * (09/11/2000) gkh&n; *&t;Added usb_serial_debug_data function to help get rid of #DEBUG in the&n; *&t;drivers.&n; *&n; * (08/28/2000) gkh&n; *&t;Added port_lock to port structure.&n; *&n; * (08/08/2000) gkh&n; *&t;Added open_count to port structure.&n; *&n; * (07/23/2000) gkh&n; *&t;Added bulk_out_endpointAddress to port structure.&n; *&n; * (07/19/2000) gkh, pberger, and borchers&n; *&t;Modifications to allow usb-serial drivers to be modules.&n; *&n; * &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_H
DECL|macro|__LINUX_USB_SERIAL_H
mdefine_line|#define __LINUX_USB_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kref.h&gt;
DECL|macro|SERIAL_TTY_MAJOR
mdefine_line|#define SERIAL_TTY_MAJOR&t;188&t;/* Nice legal number now */
DECL|macro|SERIAL_TTY_MINORS
mdefine_line|#define SERIAL_TTY_MINORS&t;255&t;/* loads of devices :) */
DECL|macro|MAX_NUM_PORTS
mdefine_line|#define MAX_NUM_PORTS&t;&t;8&t;/* The maximum number of ports one device can grab at once */
multiline_comment|/* parity check flag */
DECL|macro|RELEVANT_IFLAG
mdefine_line|#define RELEVANT_IFLAG(iflag)&t;(iflag &amp; (IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK))
multiline_comment|/**&n; * usb_serial_port: structure for the specific ports of a device.&n; * @serial: pointer back to the struct usb_serial owner of this port.&n; * @tty: pointer to the corresponding tty for this port.&n; * @number: the number of the port (the minor number).&n; * @interrupt_in_buffer: pointer to the interrupt in buffer for this port.&n; * @interrupt_in_urb: pointer to the interrupt in struct urb for this port.&n; * @interrupt_in_endpointAddress: endpoint address for the interrupt in pipe&n; *&t;for this port.&n; * @bulk_in_buffer: pointer to the bulk in buffer for this port.&n; * @read_urb: pointer to the bulk in struct urb for this port.&n; * @bulk_in_endpointAddress: endpoint address for the bulk in pipe for this&n; *&t;port.&n; * @bulk_out_buffer: pointer to the bulk out buffer for this port.&n; * @bulk_out_size: the size of the bulk_out_buffer, in bytes.&n; * @write_urb: pointer to the bulk out struct urb for this port.&n; * @bulk_out_endpointAddress: endpoint address for the bulk out pipe for this&n; *&t;port.&n; * @write_wait: a wait_queue_head_t used by the port.&n; * @work: work queue entry for the line discipline waking up.&n; * @open_count: number of times this port has been opened.&n; *&n; * This structure is used by the usb-serial core and drivers for the specific&n; * ports of a device.&n; */
DECL|struct|usb_serial_port
r_struct
id|usb_serial_port
(brace
DECL|member|serial
r_struct
id|usb_serial
op_star
id|serial
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
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
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_usb_serial_port
mdefine_line|#define to_usb_serial_port(d) container_of(d, struct usb_serial_port, dev)
multiline_comment|/* get and set the port private data pointer helper functions */
DECL|function|usb_get_serial_port_data
r_static
r_inline
r_void
op_star
id|usb_get_serial_port_data
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
(brace
r_return
id|dev_get_drvdata
c_func
(paren
op_amp
id|port-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|usb_set_serial_port_data
r_static
r_inline
r_void
id|usb_set_serial_port_data
(paren
r_struct
id|usb_serial_port
op_star
id|port
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|port-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_serial - structure used by the usb-serial core for a device&n; * @dev: pointer to the struct usb_device for this device&n; * @type: pointer to the struct usb_serial_device_type for this device&n; * @interface: pointer to the struct usb_interface for this device&n; * @minor: the starting minor number for this device&n; * @num_ports: the number of ports this device has&n; * @num_interrupt_in: number of interrupt in endpoints we have&n; * @num_bulk_in: number of bulk in endpoints we have&n; * @num_bulk_out: number of bulk out endpoints we have&n; * @vendor: vendor id of this device&n; * @product: product id of this device&n; * @port: array of struct usb_serial_port structures for the different ports.&n; * @private: place to put any driver specific information that is needed.  The&n; *&t;usb-serial driver is required to manage this data, the usb-serial core&n; *&t;will not touch this.  Use usb_get_serial_data() and&n; *&t;usb_set_serial_data() to access this.&n; */
DECL|struct|usb_serial
r_struct
id|usb_serial
(brace
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
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
DECL|member|minor
r_int
r_char
id|minor
suffix:semicolon
DECL|member|num_ports
r_int
r_char
id|num_ports
suffix:semicolon
DECL|member|num_port_pointers
r_int
r_char
id|num_port_pointers
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
DECL|member|vendor
id|__u16
id|vendor
suffix:semicolon
DECL|member|product
id|__u16
id|product
suffix:semicolon
DECL|member|port
r_struct
id|usb_serial_port
op_star
id|port
(braket
id|MAX_NUM_PORTS
)braket
suffix:semicolon
DECL|member|kref
r_struct
id|kref
id|kref
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_usb_serial
mdefine_line|#define to_usb_serial(d) container_of(d, struct usb_serial, kref)
DECL|macro|NUM_DONT_CARE
mdefine_line|#define NUM_DONT_CARE&t;(-1)
multiline_comment|/* get and set the serial private data pointer helper functions */
DECL|function|usb_get_serial_data
r_static
r_inline
r_void
op_star
id|usb_get_serial_data
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
(brace
r_return
id|serial
op_member_access_from_pointer
r_private
suffix:semicolon
)brace
DECL|function|usb_set_serial_data
r_static
r_inline
r_void
id|usb_set_serial_data
(paren
r_struct
id|usb_serial
op_star
id|serial
comma
r_void
op_star
id|data
)paren
(brace
id|serial
op_member_access_from_pointer
r_private
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_serial_device_type - a structure that defines a usb serial device&n; * @owner: pointer to the module that owns this device.&n; * @name: pointer to a string that describes this device.  This string used&n; *&t;in the syslog messages when a device is inserted or removed.&n; * @short_name: a pointer to a string that describes this device in&n; *&t;KOBJ_NAME_LEN characters or less.  This is used for the sysfs interface&n; *&t;to describe the driver.&n; * @id_table: pointer to a list of usb_device_id structures that define all&n; *&t;of the devices this structure can support.&n; * @num_interrupt_in: the number of interrupt in endpoints this device will&n; *&t;have.&n; * @num_bulk_in: the number of bulk in endpoints this device will have.&n; * @num_bulk_out: the number of bulk out endpoints this device will have.&n; * @num_ports: the number of different ports this device will have.&n; * @calc_num_ports: pointer to a function to determine how many ports this&n; *&t;device has dynamically.  It will be called after the probe()&n; *&t;callback is called, but before attach()&n; * @probe: pointer to the driver&squot;s probe function.&n; *&t;This will be called when the device is inserted into the system,&n; *&t;but before the device has been fully initialized by the usb_serial&n; *&t;subsystem.  Use this function to download any firmware to the device,&n; *&t;or any other early initialization that might be needed.&n; *&t;Return 0 to continue on with the initialization sequence.  Anything &n; *&t;else will abort it.&n; * @attach: pointer to the driver&squot;s attach function.&n; *&t;This will be called when the struct usb_serial structure is fully set&n; *&t;set up.  Do any local initialization of the device, or any private&n; *&t;memory structure allocation at this point in time.&n; * @shutdown: pointer to the driver&squot;s shutdown function.  This will be&n; *&t;called when the device is removed from the system.&n; *&n; * This structure is defines a USB Serial device.  It provides all of&n; * the information that the USB serial core code needs.  If the function&n; * pointers are defined, then the USB serial core code will call them when&n; * the corresponding tty port functions are called.  If they are not&n; * called, the generic serial function will be used instead.&n; */
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
DECL|member|short_name
r_char
op_star
id|short_name
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
DECL|member|driver
r_struct
id|device_driver
id|driver
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
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
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
DECL|member|port_probe
r_int
(paren
op_star
id|port_probe
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
DECL|member|port_remove
r_int
(paren
op_star
id|port_remove
)paren
(paren
r_struct
id|usb_serial_port
op_star
id|port
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
DECL|member|tiocmget
r_int
(paren
op_star
id|tiocmget
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
)paren
suffix:semicolon
DECL|member|tiocmset
r_int
(paren
op_star
id|tiocmset
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
id|set
comma
r_int
r_int
id|clear
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
comma
r_struct
id|pt_regs
op_star
id|regs
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
comma
r_struct
id|pt_regs
op_star
id|regs
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
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_usb_serial_driver
mdefine_line|#define to_usb_serial_driver(d) container_of(d, struct usb_serial_device_type, driver)
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
r_extern
r_void
id|usb_serial_port_softint
c_func
(paren
r_void
op_star
r_private
)paren
suffix:semicolon
r_extern
r_int
id|usb_serial_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|iface
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
suffix:semicolon
r_extern
r_void
id|usb_serial_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|iface
)paren
suffix:semicolon
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
multiline_comment|/* USB Serial console functions */
macro_line|#ifdef CONFIG_USB_SERIAL_CONSOLE
r_extern
r_void
id|usb_serial_console_init
(paren
r_int
id|debug
comma
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_void
id|usb_serial_console_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|usb_serial_console_init
r_static
r_inline
r_void
id|usb_serial_console_init
(paren
r_int
id|debug
comma
r_int
id|minor
)paren
(brace
)brace
DECL|function|usb_serial_console_exit
r_static
r_inline
r_void
id|usb_serial_console_exit
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/* Functions needed by other parts of the usbserial core */
r_extern
r_struct
id|usb_serial
op_star
id|usb_serial_get_by_index
(paren
r_int
r_int
id|minor
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|usb_serial_generic_write_room
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_extern
r_int
id|usb_serial_generic_chars_in_buffer
(paren
r_struct
id|usb_serial_port
op_star
id|port
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|usb_serial_generic_shutdown
(paren
r_struct
id|usb_serial
op_star
id|serial
)paren
suffix:semicolon
r_extern
r_int
id|usb_serial_generic_register
(paren
r_int
id|debug
)paren
suffix:semicolon
r_extern
r_void
id|usb_serial_generic_deregister
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|usb_serial_bus_register
(paren
r_struct
id|usb_serial_device_type
op_star
id|device
)paren
suffix:semicolon
r_extern
r_void
id|usb_serial_bus_deregister
(paren
r_struct
id|usb_serial_device_type
op_star
id|device
)paren
suffix:semicolon
r_extern
r_struct
id|usb_serial_device_type
id|usb_serial_generic_device
suffix:semicolon
r_extern
r_struct
id|bus_type
id|usb_serial_bus_type
suffix:semicolon
r_extern
r_struct
id|tty_driver
op_star
id|usb_serial_tty_driver
suffix:semicolon
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
id|serial_paranoia_check
(paren
id|port-&gt;serial
comma
id|function
)paren
)paren
(brace
multiline_comment|/* then say that we don&squot;t have a valid usb_serial thing, which will&n;&t;&t; * end up genrating -ENODEV return values */
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
mdefine_line|#define dbg(format, arg...) do { if (debug) printk(KERN_DEBUG &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg); } while (0)
macro_line|#endif&t;/* ifdef __LINUX_USB_SERIAL_H */
eof
