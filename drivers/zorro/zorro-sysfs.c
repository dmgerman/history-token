multiline_comment|/*&n; *  File Attributes for Zorro Devices&n; *&n; *  Copyright (C) 2003 Geert Uytterhoeven&n; *&n; *  Loosely based on drivers/pci/pci-sysfs.c&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;zorro.h&quot;
multiline_comment|/* show configuration fields */
DECL|macro|zorro_config_attr
mdefine_line|#define zorro_config_attr(name, field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##name(struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct zorro_dev *z;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;z = to_zorro_dev(dev);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, format_string, z-&gt;field);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(name, S_IRUGO, show_##name, NULL);
id|zorro_config_attr
c_func
(paren
id|id
comma
id|id
comma
l_string|&quot;0x%08x&bslash;n&quot;
)paren
suffix:semicolon
id|zorro_config_attr
c_func
(paren
id|type
comma
id|rom.er_Type
comma
l_string|&quot;0x%02x&bslash;n&quot;
)paren
suffix:semicolon
id|zorro_config_attr
c_func
(paren
id|serial
comma
id|rom.er_SerialNumber
comma
l_string|&quot;0x%08x&bslash;n&quot;
)paren
suffix:semicolon
id|zorro_config_attr
c_func
(paren
id|slotaddr
comma
id|slotaddr
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|zorro_config_attr
c_func
(paren
id|slotsize
comma
id|slotsize
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|zorro_show_resource
r_static
id|ssize_t
id|zorro_show_resource
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
id|zorro_dev
op_star
id|z
op_assign
id|to_zorro_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;0x%08lx 0x%08lx 0x%08lx&bslash;n&quot;
comma
id|zorro_resource_start
c_func
(paren
id|z
)paren
comma
id|zorro_resource_end
c_func
(paren
id|z
)paren
comma
id|zorro_resource_flags
c_func
(paren
id|z
)paren
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
id|zorro_show_resource
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|zorro_read_config
r_static
id|ssize_t
id|zorro_read_config
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
id|zorro_dev
op_star
id|z
op_assign
id|to_zorro_dev
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
r_struct
id|ConfigDev
id|cd
suffix:semicolon
r_int
r_int
id|size
op_assign
r_sizeof
(paren
id|cd
)paren
suffix:semicolon
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
id|count
op_assign
id|size
op_minus
id|off
suffix:semicolon
multiline_comment|/* Construct a ConfigDev */
id|memset
c_func
(paren
op_amp
id|cd
comma
l_int|0
comma
r_sizeof
(paren
id|cd
)paren
)paren
suffix:semicolon
id|cd.cd_Rom
op_assign
id|z-&gt;rom
suffix:semicolon
id|cd.cd_SlotAddr
op_assign
id|z-&gt;slotaddr
suffix:semicolon
id|cd.cd_SlotSize
op_assign
id|z-&gt;slotsize
suffix:semicolon
id|cd.cd_BoardAddr
op_assign
(paren
r_void
op_star
)paren
id|zorro_resource_start
c_func
(paren
id|z
)paren
suffix:semicolon
id|cd.cd_BoardSize
op_assign
id|zorro_resource_len
c_func
(paren
id|z
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
op_amp
id|cd
op_plus
id|off
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|zorro_config_attr
r_static
r_struct
id|bin_attribute
id|zorro_config_attr
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
)brace
comma
dot
id|size
op_assign
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
comma
dot
id|read
op_assign
id|zorro_read_config
comma
)brace
suffix:semicolon
DECL|function|zorro_create_sysfs_dev_files
r_void
id|zorro_create_sysfs_dev_files
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|z-&gt;dev
suffix:semicolon
multiline_comment|/* current configuration&squot;s attributes */
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_id
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_type
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_serial
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_slotaddr
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_slotsize
)paren
suffix:semicolon
id|device_create_file
c_func
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
id|zorro_config_attr
)paren
suffix:semicolon
)brace
eof
