multiline_comment|/*&n; * drivers/pci/pci-sysfs.c&n; *&n; * (C) Copyright 2002 Greg Kroah-Hartman&n; * (C) Copyright 2002 IBM Corp.&n; * (C) Copyright 2003 Matthew Wilcox&n; * (C) Copyright 2003 Hewlett-Packard&n; *&n; * File attributes for PCI devices&n; *&n; * Modeled after usb&squot;s driverfs.c &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/* show configuration fields */
DECL|macro|pci_config_attr
mdefine_line|#define pci_config_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct pci_dev *pdev;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pdev = to_pci_dev (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, pdev-&gt;field);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
id|pci_config_attr
c_func
(paren
id|vendor
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|device
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|subsystem_vendor
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|subsystem_device
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
r_class
comma
l_string|&quot;0x%06x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|irq
comma
l_string|&quot;%u&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* show resources */
r_static
id|ssize_t
DECL|function|pci_show_resources
id|pci_show_resources
c_func
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
id|pci_dev
op_star
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|max
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev-&gt;subordinate
)paren
id|max
op_assign
id|DEVICE_COUNT_RESOURCE
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;0x%016lx 0x%016lx 0x%016lx&bslash;n&quot;
comma
id|pci_resource_start
c_func
(paren
id|pci_dev
comma
id|i
)paren
comma
id|pci_resource_end
c_func
(paren
id|pci_dev
comma
id|i
)paren
comma
id|pci_resource_flags
c_func
(paren
id|pci_dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|resource
comma
id|S_IRUGO
comma
id|pci_show_resources
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|pci_read_config
id|pci_read_config
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_int
r_int
id|size
op_assign
l_int|64
suffix:semicolon
id|loff_t
id|init_off
op_assign
id|off
suffix:semicolon
multiline_comment|/* Several chips lock up trying to read undefined config space */
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
id|size
op_assign
l_int|256
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
(brace
id|size
op_assign
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
OG
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|size
)paren
(brace
id|size
op_sub_assign
id|off
suffix:semicolon
id|count
op_assign
id|size
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
id|count
suffix:semicolon
)brace
r_while
c_loop
(paren
id|off
op_amp
l_int|3
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
suffix:semicolon
id|off
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|3
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|1
)braket
op_assign
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|2
)braket
op_assign
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|3
)braket
op_assign
(paren
id|val
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|off
op_add_assign
l_int|4
suffix:semicolon
id|size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
suffix:semicolon
id|off
op_increment
suffix:semicolon
op_decrement
id|size
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pci_write_config
id|pci_write_config
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_int
r_int
id|size
op_assign
id|count
suffix:semicolon
id|loff_t
id|init_off
op_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
l_int|256
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
l_int|256
)paren
(brace
id|size
op_assign
l_int|256
op_minus
id|off
suffix:semicolon
id|count
op_assign
id|size
suffix:semicolon
)brace
r_while
c_loop
(paren
id|off
op_amp
l_int|3
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|buf
(braket
id|off
op_minus
id|init_off
)braket
)paren
suffix:semicolon
id|off
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|3
)paren
(brace
r_int
r_int
id|val
op_assign
id|buf
(braket
id|off
op_minus
id|init_off
)braket
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|1
)braket
op_lshift
l_int|8
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|2
)braket
op_lshift
l_int|16
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|3
)braket
op_lshift
l_int|24
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|off
comma
id|val
)paren
suffix:semicolon
id|off
op_add_assign
l_int|4
suffix:semicolon
id|size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|buf
(braket
id|off
op_minus
id|init_off
)braket
)paren
suffix:semicolon
id|off
op_increment
suffix:semicolon
op_decrement
id|size
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|pci_config_attr
r_static
r_struct
id|bin_attribute
id|pci_config_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;config&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
op_or
id|S_IWUSR
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
comma
dot
id|size
op_assign
l_int|256
comma
dot
id|read
op_assign
id|pci_read_config
comma
dot
id|write
op_assign
id|pci_write_config
comma
)brace
suffix:semicolon
DECL|function|pci_create_sysfs_dev_files
r_void
id|pci_create_sysfs_dev_files
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
multiline_comment|/* current configuration&squot;s attributes */
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_vendor
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_device
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_subsystem_vendor
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_subsystem_device
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_class
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_irq
)paren
suffix:semicolon
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_resource
)paren
suffix:semicolon
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|pci_config_attr
)paren
suffix:semicolon
multiline_comment|/* add platform-specific attributes */
id|pcibios_add_platform_entries
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
eof
