multiline_comment|/*&n; * USB Serial Converter Bus specific functions&n; *&n; * Copyright (C) 2002 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version&n; *&t;2 as published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
DECL|function|usb_serial_device_match
r_static
r_int
id|usb_serial_device_match
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|usb_serial_device_type
op_star
id|driver
suffix:semicolon
r_const
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
multiline_comment|/*&n;&t; * drivers are already assigned to ports in serial_probe so it&squot;s&n;&t; * a simple check here.&n;&t; */
id|port
op_assign
id|to_usb_serial_port
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
r_return
l_int|0
suffix:semicolon
id|driver
op_assign
id|to_usb_serial_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driver
op_eq
id|port-&gt;serial-&gt;type
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|usb_serial_bus_type
r_struct
id|bus_type
id|usb_serial_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb-serial&quot;
comma
dot
id|match
op_assign
id|usb_serial_device_match
comma
)brace
suffix:semicolon
DECL|function|usb_serial_device_probe
r_static
r_int
id|usb_serial_device_probe
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|usb_serial_device_type
op_star
id|driver
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|minor
suffix:semicolon
id|port
op_assign
id|to_usb_serial_port
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|driver
op_assign
id|port-&gt;serial-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|driver-&gt;port_probe
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|driver-&gt;owner
)paren
)paren
(brace
id|err
(paren
l_string|&quot;module get failed, exiting&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|retval
op_assign
id|driver-&gt;port_probe
(paren
id|port
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|driver-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
)brace
id|minor
op_assign
id|port-&gt;number
suffix:semicolon
id|tty_register_devfs
(paren
op_amp
id|usb_serial_tty_driver
comma
l_int|0
comma
id|minor
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s converter now attached to ttyUSB%d (or usb/tts/%d for devfs)&quot;
comma
id|driver-&gt;name
comma
id|minor
comma
id|minor
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_serial_device_remove
r_static
r_int
id|usb_serial_device_remove
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|usb_serial_device_type
op_star
id|driver
suffix:semicolon
r_struct
id|usb_serial_port
op_star
id|port
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|minor
suffix:semicolon
id|port
op_assign
id|to_usb_serial_port
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|driver
op_assign
id|port-&gt;serial-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|driver-&gt;port_remove
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|driver-&gt;owner
)paren
)paren
(brace
id|err
(paren
l_string|&quot;module get failed, exiting&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|retval
op_assign
id|driver-&gt;port_remove
(paren
id|port
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|driver-&gt;owner
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
id|minor
op_assign
id|port-&gt;number
suffix:semicolon
id|tty_unregister_devfs
(paren
op_amp
id|usb_serial_tty_driver
comma
id|minor
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s converter now disconnected from ttyUSB%d&quot;
comma
id|driver-&gt;name
comma
id|minor
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_serial_bus_register
r_int
id|usb_serial_bus_register
c_func
(paren
r_struct
id|usb_serial_device_type
op_star
id|device
)paren
(brace
r_int
id|retval
suffix:semicolon
id|device-&gt;driver.name
op_assign
(paren
r_char
op_star
)paren
id|device-&gt;name
suffix:semicolon
id|device-&gt;driver.bus
op_assign
op_amp
id|usb_serial_bus_type
suffix:semicolon
id|device-&gt;driver.probe
op_assign
id|usb_serial_device_probe
suffix:semicolon
id|device-&gt;driver.remove
op_assign
id|usb_serial_device_remove
suffix:semicolon
id|retval
op_assign
id|driver_register
c_func
(paren
op_amp
id|device-&gt;driver
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_serial_bus_deregister
r_void
id|usb_serial_bus_deregister
c_func
(paren
r_struct
id|usb_serial_device_type
op_star
id|device
)paren
(brace
id|driver_unregister
(paren
op_amp
id|device-&gt;driver
)paren
suffix:semicolon
)brace
eof
