multiline_comment|/*&n; * drivers/usb/core/driverfs.c&n; *&n; * (C) Copyright 2002 David Brownell&n; * (C) Copyright 2002 Greg Kroah-Hartman&n; * (C) Copyright 2002 IBM Corp.&n; *&n; * All of the driverfs file attributes for usb devices and interfaces.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;usb.h&quot;
multiline_comment|/* Active configuration fields */
DECL|macro|usb_actconfig_attr
mdefine_line|#define usb_actconfig_attr(field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf, size_t count, loff_t off)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_device *udev;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (off)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;udev = to_usb_device (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, udev-&gt;actconfig-&gt;desc.field); &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|usb_actconfig_attr
(paren
id|bNumInterfaces
comma
l_string|&quot;%2d&bslash;n&quot;
)paren
id|usb_actconfig_attr
(paren
id|bConfigurationValue
comma
l_string|&quot;%2d&bslash;n&quot;
)paren
id|usb_actconfig_attr
(paren
id|bmAttributes
comma
l_string|&quot;%2x&bslash;n&quot;
)paren
id|usb_actconfig_attr
(paren
id|bMaxPower
comma
l_string|&quot;%3dmA&bslash;n&quot;
)paren
multiline_comment|/* String fields */
DECL|function|show_product
r_static
id|ssize_t
id|show_product
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
id|len
op_assign
id|usb_string
c_func
(paren
id|udev
comma
id|udev-&gt;descriptor.iProduct
comma
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|len
op_plus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
op_plus
l_int|1
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|product
comma
id|S_IRUGO
comma
id|show_product
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_manufacturer
id|show_manufacturer
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
id|len
op_assign
id|usb_string
c_func
(paren
id|udev
comma
id|udev-&gt;descriptor.iManufacturer
comma
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|len
op_plus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
op_plus
l_int|1
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|manufacturer
comma
id|S_IRUGO
comma
id|show_manufacturer
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_serial
id|show_serial
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
id|len
op_assign
id|usb_string
c_func
(paren
id|udev
comma
id|udev-&gt;descriptor.iSerialNumber
comma
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|len
op_plus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
op_plus
l_int|1
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|serial
comma
id|S_IRUGO
comma
id|show_serial
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_speed
id|show_speed
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
r_char
op_star
id|speed
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|udev-&gt;speed
)paren
(brace
r_case
id|USB_SPEED_LOW
suffix:colon
id|speed
op_assign
l_string|&quot;1.5&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_UNKNOWN
suffix:colon
r_case
id|USB_SPEED_FULL
suffix:colon
id|speed
op_assign
l_string|&quot;12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_HIGH
suffix:colon
id|speed
op_assign
l_string|&quot;480&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|speed
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|speed
comma
id|S_IRUGO
comma
id|show_speed
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Descriptor fields */
DECL|macro|usb_descriptor_attr
mdefine_line|#define usb_descriptor_attr(field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf, size_t count, loff_t off)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_device *udev;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (off)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;udev = to_usb_device (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, udev-&gt;descriptor.field);&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|usb_descriptor_attr
(paren
id|idVendor
comma
l_string|&quot;%04x&bslash;n&quot;
)paren
id|usb_descriptor_attr
(paren
id|idProduct
comma
l_string|&quot;%04x&bslash;n&quot;
)paren
id|usb_descriptor_attr
(paren
id|bcdDevice
comma
l_string|&quot;%04x&bslash;n&quot;
)paren
id|usb_descriptor_attr
(paren
id|bDeviceClass
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
id|usb_descriptor_attr
(paren
id|bDeviceSubClass
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
id|usb_descriptor_attr
(paren
id|bDeviceProtocol
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
DECL|function|usb_create_driverfs_dev_files
r_void
id|usb_create_driverfs_dev_files
(paren
r_struct
id|usb_device
op_star
id|udev
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|udev-&gt;dev
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bNumInterfaces
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bConfigurationValue
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bmAttributes
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bMaxPower
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_idVendor
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_idProduct
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bcdDevice
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bDeviceClass
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bDeviceSubClass
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_bDeviceProtocol
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;descriptor.iManufacturer
)paren
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_manufacturer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;descriptor.iProduct
)paren
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_product
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;descriptor.iSerialNumber
)paren
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_serial
)paren
suffix:semicolon
)brace
multiline_comment|/* Interface fields */
DECL|macro|usb_intf_attr
mdefine_line|#define usb_intf_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf, size_t count, loff_t off)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_interface *intf;&t;&t;&t;&t;&t;&bslash;&n;&t;int alt;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (off)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;intf = to_usb_interface (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;alt = intf-&gt;act_altsetting;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, intf-&gt;altsetting[alt].desc.field); &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|usb_intf_attr
(paren
id|bAlternateSetting
comma
l_string|&quot;%2d&bslash;n&quot;
)paren
id|usb_intf_attr
(paren
id|bInterfaceClass
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
id|usb_intf_attr
(paren
id|bInterfaceSubClass
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
id|usb_intf_attr
(paren
id|bInterfaceProtocol
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
DECL|function|usb_create_driverfs_intf_files
r_void
id|usb_create_driverfs_intf_files
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
id|device_create_file
(paren
op_amp
id|intf-&gt;dev
comma
op_amp
id|dev_attr_bAlternateSetting
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|intf-&gt;dev
comma
op_amp
id|dev_attr_bInterfaceClass
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|intf-&gt;dev
comma
op_amp
id|dev_attr_bInterfaceSubClass
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|intf-&gt;dev
comma
op_amp
id|dev_attr_bInterfaceProtocol
)paren
suffix:semicolon
)brace
eof
