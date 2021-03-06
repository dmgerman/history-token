multiline_comment|/*&n; * USB LED driver - 1.1&n; *&n; * Copyright (C) 2004 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;1
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Greg Kroah-Hartman, greg@kroah.com&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB LED Driver&quot;
DECL|macro|VENDOR_ID
mdefine_line|#define VENDOR_ID&t;0x0fc5
DECL|macro|PRODUCT_ID
mdefine_line|#define PRODUCT_ID&t;0x1223
multiline_comment|/* table of devices that work with this driver */
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
id|VENDOR_ID
comma
id|PRODUCT_ID
)paren
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|id_table
)paren
suffix:semicolon
DECL|struct|usb_led
r_struct
id|usb_led
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|blue
r_int
r_char
id|blue
suffix:semicolon
DECL|member|red
r_int
r_char
id|red
suffix:semicolon
DECL|member|green
r_int
r_char
id|green
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BLUE
mdefine_line|#define BLUE&t;0x04
DECL|macro|RED
mdefine_line|#define RED&t;0x02
DECL|macro|GREEN
mdefine_line|#define GREEN&t;0x01
DECL|function|change_color
r_static
r_void
id|change_color
c_func
(paren
r_struct
id|usb_led
op_star
id|led
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
r_char
id|color
op_assign
l_int|0x07
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
l_int|8
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|led-&gt;udev-&gt;dev
comma
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|led-&gt;blue
)paren
id|color
op_and_assign
op_complement
(paren
id|BLUE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|led-&gt;red
)paren
id|color
op_and_assign
op_complement
(paren
id|RED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|led-&gt;green
)paren
id|color
op_and_assign
op_complement
(paren
id|GREEN
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|led-&gt;udev-&gt;dev
comma
l_string|&quot;blue = %d, red = %d, green = %d, color = %.2x&bslash;n&quot;
comma
id|led-&gt;blue
comma
id|led-&gt;red
comma
id|led-&gt;green
comma
id|color
)paren
suffix:semicolon
id|retval
op_assign
id|usb_control_msg
c_func
(paren
id|led-&gt;udev
comma
id|usb_sndctrlpipe
c_func
(paren
id|led-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x12
comma
l_int|0xc8
comma
(paren
l_int|0x02
op_star
l_int|0x100
)paren
op_plus
l_int|0x0a
comma
(paren
l_int|0x00
op_star
l_int|0x100
)paren
op_plus
id|color
comma
id|buffer
comma
l_int|8
comma
l_int|2000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|dev_dbg
c_func
(paren
op_amp
id|led-&gt;udev-&gt;dev
comma
l_string|&quot;retval = %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
DECL|macro|show_set
mdefine_line|#define show_set(value)&t;&bslash;&n;static ssize_t show_##value(struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_interface *intf = to_usb_interface(dev);&t;&t;&bslash;&n;&t;struct usb_led *led = usb_get_intfdata(intf);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, led-&gt;value);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_interface *intf = to_usb_interface(dev);&t;&t;&bslash;&n;&t;struct usb_led *led = usb_get_intfdata(intf);&t;&t;&t;&bslash;&n;&t;int temp = simple_strtoul(buf, NULL, 10);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;led-&gt;value = temp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;change_color(led);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(value, S_IWUGO | S_IRUGO, show_##value, set_##value);
DECL|variable|blue
id|show_set
c_func
(paren
id|blue
)paren
suffix:semicolon
DECL|variable|red
id|show_set
c_func
(paren
id|red
)paren
suffix:semicolon
DECL|variable|green
id|show_set
c_func
(paren
id|green
)paren
suffix:semicolon
DECL|function|led_probe
r_static
r_int
id|led_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|interface
)paren
suffix:semicolon
r_struct
id|usb_led
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_led
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|interface-&gt;dev
comma
l_string|&quot;Out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memset
(paren
id|dev
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;udev
op_assign
id|usb_get_dev
c_func
(paren
id|udev
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|interface
comma
id|dev
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_blue
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_red
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_green
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|interface-&gt;dev
comma
l_string|&quot;USB LED device now attached&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|led_disconnect
r_static
r_void
id|led_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
)paren
(brace
r_struct
id|usb_led
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|usb_get_intfdata
(paren
id|interface
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|interface
comma
l_int|NULL
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_blue
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_red
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
op_amp
id|interface-&gt;dev
comma
op_amp
id|dev_attr_green
)paren
suffix:semicolon
id|usb_put_dev
c_func
(paren
id|dev-&gt;udev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|interface-&gt;dev
comma
l_string|&quot;USB LED now disconnected&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|led_driver
r_static
r_struct
id|usb_driver
id|led_driver
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
l_string|&quot;usbled&quot;
comma
dot
id|probe
op_assign
id|led_probe
comma
dot
id|disconnect
op_assign
id|led_disconnect
comma
dot
id|id_table
op_assign
id|id_table
comma
)brace
suffix:semicolon
DECL|function|usb_led_init
r_static
r_int
id|__init
id|usb_led_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|led_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|err
c_func
(paren
l_string|&quot;usb_register failed. Error number %d&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_led_exit
r_static
r_void
id|__exit
id|usb_led_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|led_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_led_init
id|module_init
(paren
id|usb_led_init
)paren
suffix:semicolon
DECL|variable|usb_led_exit
id|module_exit
(paren
id|usb_led_exit
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
eof
