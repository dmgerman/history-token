multiline_comment|/*&n; * linux/drivers/firmware/smbios.c&n; *  Copyright (C) 2004 Dell Inc.&n; *  by Michael Brown &lt;Michael_E_Brown@dell.com&gt;&n; *  vim:noet:ts=8:sw=8:filetype=c:textwidth=80:&n; *&n; * BIOS SMBIOS Table access&n; * conformant to DMTF SMBIOS definition&n; *   at http://www.dmtf.org/standards/smbios&n; *&n; * This code takes information provided by SMBIOS tables&n; * and presents it in sysfs as:&n; *    /sys/firmware/smbios&n; *&t;&t;&t;|--&gt; /table_entry_point&n; *&t;&t;&t;|--&gt; /table&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License v2.0 as published by&n; * the Free Software Foundation&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;smbios.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michael Brown &lt;Michael_E_Brown@Dell.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;sysfs interface to SMBIOS information&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|SMBIOS_VERSION
mdefine_line|#define SMBIOS_VERSION &quot;1.0 2004-04-19&quot;
DECL|struct|smbios_device
r_struct
id|smbios_device
(brace
DECL|member|table_eps
r_struct
id|smbios_table_entry_point
id|table_eps
suffix:semicolon
DECL|member|smbios_table_real_length
r_int
r_int
id|smbios_table_real_length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* there shall be only one */
DECL|variable|the_smbios_device
r_static
r_struct
id|smbios_device
id|the_smbios_device
suffix:semicolon
DECL|macro|to_smbios_device
mdefine_line|#define to_smbios_device(obj) container_of(obj,struct smbios_device,kobj)
multiline_comment|/* don&squot;t currently have any &quot;normal&quot; attributes, so we don&squot;t need a way to&n; * show them. */
DECL|variable|smbios_attr_ops
r_static
r_struct
id|sysfs_ops
id|smbios_attr_ops
op_assign
(brace
)brace
suffix:semicolon
r_static
id|__init
r_int
DECL|function|checksum_eps
id|checksum_eps
c_func
(paren
r_struct
id|smbios_table_entry_point
op_star
id|table_eps
)paren
(brace
id|u8
op_star
id|p
op_assign
(paren
id|u8
op_star
)paren
id|table_eps
suffix:semicolon
id|u8
id|checksum
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
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
id|table_eps-&gt;eps_length
op_logical_and
id|i
OL
r_sizeof
(paren
op_star
id|table_eps
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|checksum
op_add_assign
id|p
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
id|checksum
op_eq
l_int|0
suffix:semicolon
)brace
r_static
id|__init
r_int
DECL|function|find_table_entry_point
id|find_table_entry_point
c_func
(paren
r_struct
id|smbios_device
op_star
id|sdev
)paren
(brace
r_struct
id|smbios_table_entry_point
op_star
id|table_eps
op_assign
op_amp
(paren
id|sdev-&gt;table_eps
)paren
suffix:semicolon
id|u32
id|fp
op_assign
l_int|0xF0000
suffix:semicolon
r_while
c_loop
(paren
id|fp
OL
l_int|0xFFFFF
)paren
(brace
id|isa_memcpy_fromio
c_func
(paren
id|table_eps
comma
id|fp
comma
r_sizeof
(paren
op_star
id|table_eps
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|table_eps-&gt;anchor
comma
l_string|&quot;_SM_&quot;
comma
l_int|4
)paren
op_eq
l_int|0
op_logical_and
id|checksum_eps
c_func
(paren
id|table_eps
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|fp
op_add_assign
l_int|16
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMBIOS table entry point not found in &quot;
l_string|&quot;0xF0000 - 0xFFFFF&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
id|__init
r_int
DECL|function|find_table_max_address
id|find_table_max_address
c_func
(paren
r_struct
id|smbios_device
op_star
id|sdev
)paren
(brace
multiline_comment|/* break out on one of three conditions:&n;&t; *   -- hit table_eps.table_length&n;&t; *   -- hit number of items that table claims we have&n;&t; *   -- hit structure type 127&n;&t; */
id|u8
op_star
id|buf
op_assign
id|ioremap
c_func
(paren
id|sdev-&gt;table_eps.table_address
comma
id|sdev-&gt;table_eps.table_length
)paren
suffix:semicolon
id|u8
op_star
id|ptr
op_assign
id|buf
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|keep_going
op_assign
l_int|1
suffix:semicolon
r_int
id|max_count
op_assign
id|sdev-&gt;table_eps.table_num_structs
suffix:semicolon
r_int
id|max_length
op_assign
id|sdev-&gt;table_eps.table_length
suffix:semicolon
r_while
c_loop
(paren
id|keep_going
op_logical_and
(paren
(paren
id|ptr
op_minus
id|buf
)paren
op_le
id|max_length
)paren
op_logical_and
id|count
OL
id|max_count
)paren
(brace
r_if
c_cond
(paren
id|ptr
(braket
l_int|0
)braket
op_eq
l_int|0x7F
)paren
(brace
multiline_comment|/* ptr[0] is type */
id|keep_going
op_assign
l_int|0
suffix:semicolon
)brace
id|ptr
op_add_assign
id|ptr
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* ptr[1] is length, skip structure */
multiline_comment|/* skip strings at end of structure */
r_while
c_loop
(paren
(paren
id|ptr
op_minus
id|buf
)paren
OL
id|max_length
op_logical_and
(paren
id|ptr
(braket
l_int|0
)braket
op_logical_or
id|ptr
(braket
l_int|1
)braket
)paren
)paren
(brace
op_increment
id|ptr
suffix:semicolon
)brace
multiline_comment|/* string area ends in double-null. skip it. */
id|ptr
op_add_assign
l_int|2
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
id|sdev-&gt;smbios_table_real_length
op_assign
(paren
id|ptr
op_minus
id|buf
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|max_count
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Warning: SMBIOS table structure count&quot;
l_string|&quot; does not match count specified in the&quot;
l_string|&quot; table entry point.&bslash;n&quot;
l_string|&quot; Table entry point count: %d&bslash;n&quot;
l_string|&quot; Actual count: %d&bslash;n&quot;
comma
id|max_count
comma
id|count
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|keep_going
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Warning: SMBIOS table does not end with a&quot;
l_string|&quot; structure type 127. This may indicate a&quot;
l_string|&quot; truncated table.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sdev-&gt;smbios_table_real_length
op_ne
id|max_length
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Warning: BIOS specified SMBIOS table length&quot;
l_string|&quot; does not match calculated length.&bslash;n&quot;
l_string|&quot; BIOS specified: %d&bslash;n&quot;
l_string|&quot; calculated length: %d&bslash;n&quot;
comma
id|max_length
comma
id|sdev-&gt;smbios_table_real_length
)paren
suffix:semicolon
)brace
r_return
id|sdev-&gt;smbios_table_real_length
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|smbios_read_table_entry_point
id|smbios_read_table_entry_point
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|pos
comma
r_int
id|size
)paren
(brace
r_struct
id|smbios_device
op_star
id|sdev
op_assign
op_amp
id|the_smbios_device
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
(paren
r_const
r_char
op_star
)paren
op_amp
(paren
id|sdev-&gt;table_eps
)paren
suffix:semicolon
r_int
r_int
id|count
op_assign
id|size
OG
r_sizeof
(paren
id|sdev-&gt;table_eps
)paren
ques
c_cond
r_sizeof
(paren
id|sdev-&gt;table_eps
)paren
suffix:colon
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|p
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|smbios_read_table
id|smbios_read_table
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|pos
comma
r_int
id|size
)paren
(brace
r_struct
id|smbios_device
op_star
id|sdev
op_assign
op_amp
id|the_smbios_device
suffix:semicolon
id|u8
op_star
id|buf
suffix:semicolon
r_int
r_int
id|count
op_assign
id|sdev-&gt;smbios_table_real_length
op_minus
id|pos
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
id|count
OL
id|size
ques
c_cond
id|count
suffix:colon
id|size
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|sdev-&gt;smbios_table_real_length
)paren
r_return
l_int|0
suffix:semicolon
id|buf
op_assign
id|ioremap
c_func
(paren
id|sdev-&gt;table_eps.table_address
comma
id|sdev-&gt;smbios_table_real_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* memcpy( buffer, buf+pos, count ); */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
op_increment
id|i
)paren
(brace
id|buffer
(braket
id|i
)braket
op_assign
id|readb
c_func
(paren
id|buf
op_plus
id|pos
op_plus
id|i
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|tep_attr
r_static
r_struct
id|bin_attribute
id|tep_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;table_entry_point&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|mode
op_assign
l_int|0444
)brace
comma
dot
id|size
op_assign
r_sizeof
(paren
r_struct
id|smbios_table_entry_point
)paren
comma
dot
id|read
op_assign
id|smbios_read_table_entry_point
comma
multiline_comment|/* not writeable */
)brace
suffix:semicolon
DECL|variable|table_attr
r_static
r_struct
id|bin_attribute
id|table_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;table&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|mode
op_assign
l_int|0444
)brace
comma
multiline_comment|/* size set later, we don&squot;t know it here. */
dot
id|read
op_assign
id|smbios_read_table
comma
multiline_comment|/* not writeable */
)brace
suffix:semicolon
multiline_comment|/* no default attributes yet. */
DECL|variable|def_attrs
r_static
r_struct
id|attribute
op_star
id|def_attrs
(braket
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|ktype_smbios
r_static
r_struct
id|kobj_type
id|ktype_smbios
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|smbios_attr_ops
comma
dot
id|default_attrs
op_assign
id|def_attrs
comma
multiline_comment|/* statically allocated, no release method necessary */
)brace
suffix:semicolon
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
id|smbios
comma
op_amp
id|ktype_smbios
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|smbios_device_unregister
r_static
r_void
id|smbios_device_unregister
c_func
(paren
r_void
)paren
(brace
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|smbios_subsys.kset.kobj
comma
op_amp
id|tep_attr
)paren
suffix:semicolon
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|smbios_subsys.kset.kobj
comma
op_amp
id|table_attr
)paren
suffix:semicolon
)brace
DECL|function|smbios_device_register
r_static
r_void
id|__init
id|smbios_device_register
c_func
(paren
r_void
)paren
(brace
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|smbios_subsys.kset.kobj
comma
op_amp
id|tep_attr
)paren
suffix:semicolon
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|smbios_subsys.kset.kobj
comma
op_amp
id|table_attr
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|smbios_init
id|smbios_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMBIOS facility v%s&bslash;n&quot;
comma
id|SMBIOS_VERSION
)paren
suffix:semicolon
id|rc
op_assign
id|find_table_entry_point
c_func
(paren
op_amp
id|the_smbios_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|table_attr.size
op_assign
id|find_table_max_address
c_func
(paren
op_amp
id|the_smbios_device
)paren
suffix:semicolon
id|rc
op_assign
id|firmware_register
c_func
(paren
op_amp
id|smbios_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|smbios_device_register
c_func
(paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|smbios_exit
id|smbios_exit
c_func
(paren
r_void
)paren
(brace
id|smbios_device_unregister
c_func
(paren
)paren
suffix:semicolon
id|firmware_unregister
c_func
(paren
op_amp
id|smbios_subsys
)paren
suffix:semicolon
)brace
DECL|variable|smbios_init
id|late_initcall
c_func
(paren
id|smbios_init
)paren
suffix:semicolon
DECL|variable|smbios_exit
id|module_exit
c_func
(paren
id|smbios_exit
)paren
suffix:semicolon
eof
