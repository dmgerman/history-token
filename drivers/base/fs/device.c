multiline_comment|/*&n; * drivers/base/fs.c - driver model interface to driverfs &n; *&n; * Copyright (c) 2002 Patrick Mochel&n; *&t;&t; 2002 Open Source Development Lab&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
DECL|variable|device_root_dir
r_static
r_struct
id|driver_dir_entry
id|device_root_dir
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;root&quot;
comma
dot
id|mode
op_assign
(paren
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
comma
)brace
suffix:semicolon
r_extern
r_struct
id|device_attribute
op_star
id|device_default_files
(braket
)braket
suffix:semicolon
DECL|macro|to_dev_attr
mdefine_line|#define to_dev_attr(_attr) container_of(_attr,struct device_attribute,attr)
DECL|macro|to_device
mdefine_line|#define to_device(d) container_of(d, struct device, dir)
multiline_comment|/* driverfs ops for device attribute files */
r_static
r_int
DECL|function|dev_attr_open
id|dev_attr_open
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_device
c_func
(paren
id|dir
)paren
suffix:semicolon
id|get_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dev_attr_close
id|dev_attr_close
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_device
c_func
(paren
id|dir
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dev_attr_show
id|dev_attr_show
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_struct
id|attribute
op_star
id|attr
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
id|device_attribute
op_star
id|dev_attr
op_assign
id|to_dev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|to_device
c_func
(paren
id|dir
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev_attr-&gt;show
)paren
id|ret
op_assign
id|dev_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|dev
comma
id|buf
comma
id|count
comma
id|off
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dev_attr_store
id|dev_attr_store
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_struct
id|attribute
op_star
id|attr
comma
r_const
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
id|device_attribute
op_star
id|dev_attr
op_assign
id|to_dev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|to_device
c_func
(paren
id|dir
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev_attr-&gt;store
)paren
id|ret
op_assign
id|dev_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|dev
comma
id|buf
comma
id|count
comma
id|off
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dev_attr_ops
r_static
r_struct
id|driverfs_ops
id|dev_attr_ops
op_assign
(brace
dot
id|open
op_assign
id|dev_attr_open
comma
dot
id|close
op_assign
id|dev_attr_close
comma
dot
id|show
op_assign
id|dev_attr_show
comma
dot
id|store
op_assign
id|dev_attr_store
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * device_create_file - create a driverfs file for a device&n; * @dev:&t;device requesting file&n; * @entry:&t;entry describing file&n; *&n; * Allocate space for file entry, copy descriptor, and create.&n; */
DECL|function|device_create_file
r_int
id|device_create_file
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_attribute
op_star
id|entry
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|get_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|error
op_assign
id|driverfs_create_file
c_func
(paren
op_amp
id|entry-&gt;attr
comma
op_amp
id|dev-&gt;dir
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * device_remove_file - remove a device&squot;s file by name&n; * @dev:&t;device requesting removal&n; * @name:&t;name of the file&n; *&n; */
DECL|function|device_remove_file
r_void
id|device_remove_file
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_attribute
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
(brace
id|get_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|driverfs_remove_file
c_func
(paren
op_amp
id|dev-&gt;dir
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * device_remove_dir - remove a device&squot;s directory&n; * @dev:&t;device in question&n; */
DECL|function|device_remove_dir
r_void
id|device_remove_dir
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
id|driverfs_remove_dir
c_func
(paren
op_amp
id|dev-&gt;dir
)paren
suffix:semicolon
)brace
DECL|function|get_devpath_length
r_int
id|get_devpath_length
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|length
op_assign
l_int|1
suffix:semicolon
r_struct
id|device
op_star
id|parent
op_assign
id|dev
suffix:semicolon
multiline_comment|/* walk up the ancestors until we hit the root.&n;&t; * Add 1 to strlen for leading &squot;/&squot; of each level.&n;&t; */
r_do
(brace
id|length
op_add_assign
id|strlen
c_func
(paren
id|parent-&gt;bus_id
)paren
op_plus
l_int|1
suffix:semicolon
id|parent
op_assign
id|parent-&gt;parent
suffix:semicolon
)brace
r_while
c_loop
(paren
id|parent
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|fill_devpath
r_void
id|fill_devpath
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|path
comma
r_int
id|length
)paren
(brace
r_struct
id|device
op_star
id|parent
suffix:semicolon
op_decrement
id|length
suffix:semicolon
r_for
c_loop
(paren
id|parent
op_assign
id|dev
suffix:semicolon
id|parent
suffix:semicolon
id|parent
op_assign
id|parent-&gt;parent
)paren
(brace
r_int
id|cur
op_assign
id|strlen
c_func
(paren
id|parent-&gt;bus_id
)paren
suffix:semicolon
multiline_comment|/* back up enough to print this bus id with &squot;/&squot; */
id|length
op_sub_assign
id|cur
suffix:semicolon
id|strncpy
c_func
(paren
id|path
op_plus
id|length
comma
id|parent-&gt;bus_id
comma
id|cur
)paren
suffix:semicolon
op_star
(paren
id|path
op_plus
op_decrement
id|length
)paren
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: path = &squot;%s&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|device_bus_link
r_int
id|device_bus_link
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_char
op_star
id|path
suffix:semicolon
r_int
id|length
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bus
)paren
r_return
l_int|0
suffix:semicolon
id|length
op_assign
id|get_devpath_length
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* now add the path from the bus directory&n;&t; * It should be &squot;../../..&squot; (one to get to the bus&squot;s directory,&n;&t; * one to get to the &squot;bus&squot; directory, and one to get to the root &n;&t; * of the fs.)&n;&t; */
id|length
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;../../../root&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|PATH_MAX
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|path
op_assign
id|kmalloc
c_func
(paren
id|length
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|path
comma
l_int|0
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* our relative position */
id|strcpy
c_func
(paren
id|path
comma
l_string|&quot;../../../root&quot;
)paren
suffix:semicolon
id|fill_devpath
c_func
(paren
id|dev
comma
id|path
comma
id|length
)paren
suffix:semicolon
id|error
op_assign
id|driverfs_create_symlink
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;device_dir
comma
id|dev-&gt;bus_id
comma
id|path
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|device_remove_symlink
r_void
id|device_remove_symlink
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|driverfs_remove_file
c_func
(paren
id|dir
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|device_create_dir
r_int
id|device_create_dir
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_struct
id|driver_dir_entry
op_star
id|parent
)paren
(brace
id|dir-&gt;mode
op_assign
(paren
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
suffix:semicolon
r_return
id|driverfs_create_dir
c_func
(paren
id|dir
comma
id|parent
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * device_make_dir - create a driverfs directory&n; * @name:&t;name of directory&n; * @parent:&t;dentry for the parent directory&n; *&n; * Do the initial creation of the device&squot;s driverfs directory&n; * and populate it with the one default file.&n; *&n; * This is just a helper for device_register(), as we&n; * don&squot;t export this function. (Yes, that means we don&squot;t allow&n; * devices to create subdirectories).&n; */
DECL|function|device_make_dir
r_int
id|device_make_dir
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|driver_dir_entry
op_star
id|parent
suffix:semicolon
r_struct
id|device_attribute
op_star
id|entry
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
suffix:semicolon
id|parent
op_assign
id|dev-&gt;parent
ques
c_cond
op_amp
id|dev-&gt;parent-&gt;dir
suffix:colon
op_amp
id|device_root_dir
suffix:semicolon
id|dev-&gt;dir.name
op_assign
id|dev-&gt;bus_id
suffix:semicolon
id|dev-&gt;dir.ops
op_assign
op_amp
id|dev_attr_ops
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_create_dir
c_func
(paren
op_amp
id|dev-&gt;dir
comma
id|parent
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|entry
op_assign
op_star
(paren
id|device_default_files
op_plus
id|i
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
id|entry
)paren
)paren
)paren
(brace
id|device_remove_dir
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|device_driverfs_init
r_static
r_int
id|device_driverfs_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driverfs_create_dir
c_func
(paren
op_amp
id|device_root_dir
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|device_driverfs_init
id|core_initcall
c_func
(paren
id|device_driverfs_init
)paren
suffix:semicolon
DECL|variable|device_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|device_create_file
)paren
suffix:semicolon
DECL|variable|device_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|device_remove_file
)paren
suffix:semicolon
eof
