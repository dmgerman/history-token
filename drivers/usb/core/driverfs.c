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
DECL|macro|usb_actconfig_show
mdefine_line|#define usb_actconfig_show(field, multiplier, format_string)&t;&t;&bslash;&n;static ssize_t  show_##field (struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_device *udev;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;udev = to_usb_device (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;if (udev-&gt;actconfig)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return sprintf (buf, format_string,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;udev-&gt;actconfig-&gt;desc.field * multiplier);&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;
DECL|macro|usb_actconfig_attr
mdefine_line|#define usb_actconfig_attr(field, multiplier, format_string)&t;&t;&bslash;&n;usb_actconfig_show(field, multiplier, format_string)&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|usb_actconfig_attr
(paren
id|bNumInterfaces
comma
l_int|1
comma
l_string|&quot;%2d&bslash;n&quot;
)paren
id|usb_actconfig_attr
(paren
id|bmAttributes
comma
l_int|1
comma
l_string|&quot;%2x&bslash;n&quot;
)paren
id|usb_actconfig_attr
(paren
id|bMaxPower
comma
l_int|2
comma
l_string|&quot;%3dmA&bslash;n&quot;
)paren
multiline_comment|/* configuration value is always present, and r/w */
id|usb_actconfig_show
c_func
(paren
id|bConfigurationValue
comma
l_int|1
comma
l_string|&quot;%u&bslash;n&quot;
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|set_bConfigurationValue
id|set_bConfigurationValue
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
r_int
id|config
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|config
)paren
op_ne
l_int|1
op_logical_or
id|config
OG
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|udev-&gt;serialize
)paren
suffix:semicolon
id|value
op_assign
id|usb_set_configuration
(paren
id|udev
comma
id|config
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|udev-&gt;serialize
)paren
suffix:semicolon
r_return
(paren
id|value
OL
l_int|0
)paren
ques
c_cond
id|value
suffix:colon
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|bConfigurationValue
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_bConfigurationValue
comma
id|set_bConfigurationValue
)paren
suffix:semicolon
multiline_comment|/* String fields */
DECL|macro|usb_string_attr
mdefine_line|#define usb_string_attr(name, field)&t;&t;&bslash;&n;static ssize_t  show_##name(struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_device *udev;&t;&t;&t;&t;&t;&bslash;&n;&t;int len;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;udev = to_usb_device (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;len = usb_string(udev, udev-&gt;descriptor.field, buf, PAGE_SIZE);&t;&bslash;&n;&t;if (len &lt; 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;buf[len] = &squot;&bslash;n&squot;;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;buf[len+1] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return len+1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(name, S_IRUGO, show_##name, NULL);
id|usb_string_attr
c_func
(paren
id|product
comma
id|iProduct
)paren
suffix:semicolon
id|usb_string_attr
c_func
(paren
id|manufacturer
comma
id|iManufacturer
)paren
suffix:semicolon
id|usb_string_attr
c_func
(paren
id|serial
comma
id|iSerialNumber
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
r_static
id|ssize_t
DECL|function|show_devnum
id|show_devnum
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|udev-&gt;devnum
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|devnum
comma
id|S_IRUGO
comma
id|show_devnum
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_version
id|show_version
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%2x.%02x&bslash;n&quot;
comma
id|udev-&gt;descriptor.bcdUSB
op_rshift
l_int|8
comma
id|udev-&gt;descriptor.bcdUSB
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|version
comma
id|S_IRUGO
comma
id|show_version
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_maxchild
id|show_maxchild
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|udev
op_assign
id|to_usb_device
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|udev-&gt;maxchild
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|maxchild
comma
id|S_IRUGO
comma
id|show_maxchild
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Descriptor fields */
DECL|macro|usb_descriptor_attr
mdefine_line|#define usb_descriptor_attr(field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_device *udev;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;udev = to_usb_device (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, udev-&gt;descriptor.field);&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
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
id|usb_descriptor_attr
(paren
id|bNumConfigurations
comma
l_string|&quot;%d&bslash;n&quot;
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
multiline_comment|/* current configuration&squot;s attributes */
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
multiline_comment|/* device attributes */
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
id|dev_attr_bNumConfigurations
)paren
suffix:semicolon
multiline_comment|/* speed varies depending on how you connect the device */
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_speed
)paren
suffix:semicolon
singleline_comment|// FIXME iff there are other speed configs, show how many
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
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_devnum
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_version
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_maxchild
)paren
suffix:semicolon
)brace
multiline_comment|/* Interface fields */
DECL|macro|usb_intf_attr
mdefine_line|#define usb_intf_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct usb_interface *intf = to_usb_interface (dev);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, intf-&gt;cur_altsetting-&gt;desc.field); &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|usb_intf_attr
(paren
id|bInterfaceNumber
comma
l_string|&quot;%02x&bslash;n&quot;
)paren
id|usb_intf_attr
(paren
id|bAlternateSetting
comma
l_string|&quot;%2d&bslash;n&quot;
)paren
id|usb_intf_attr
(paren
id|bNumEndpoints
comma
l_string|&quot;%02x&bslash;n&quot;
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
id|usb_intf_attr
(paren
id|iInterface
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
id|dev_attr_bInterfaceNumber
)paren
suffix:semicolon
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
id|dev_attr_bNumEndpoints
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
id|device_create_file
(paren
op_amp
id|intf-&gt;dev
comma
op_amp
id|dev_attr_iInterface
)paren
suffix:semicolon
)brace
eof
