multiline_comment|/*&n; * class.c - driverfs bindings for device classes.&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;fs.h&quot;
DECL|variable|class_dir
r_static
r_struct
id|driver_dir_entry
id|class_dir
suffix:semicolon
DECL|macro|to_class_attr
mdefine_line|#define to_class_attr(_attr) container_of(_attr,struct devclass_attribute,attr)
DECL|macro|to_class
mdefine_line|#define to_class(d) container_of(d,struct device_class,dir)
r_static
id|ssize_t
DECL|function|devclass_attr_show
id|devclass_attr_show
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
id|devclass_attribute
op_star
id|class_attr
op_assign
id|to_class_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device_class
op_star
id|dc
op_assign
id|to_class
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
id|class_attr-&gt;show
)paren
id|ret
op_assign
id|class_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|dc
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
DECL|function|devclass_attr_store
id|devclass_attr_store
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
id|devclass_attribute
op_star
id|class_attr
op_assign
id|to_class_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device_class
op_star
id|dc
op_assign
id|to_class
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
id|class_attr-&gt;store
)paren
id|ret
op_assign
id|class_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|dc
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
DECL|variable|devclass_attr_ops
r_static
r_struct
id|driverfs_ops
id|devclass_attr_ops
op_assign
(brace
id|show
suffix:colon
id|devclass_attr_show
comma
id|store
suffix:colon
id|devclass_attr_store
comma
)brace
suffix:semicolon
DECL|function|devclass_create_file
r_int
id|devclass_create_file
c_func
(paren
r_struct
id|device_class
op_star
id|dc
comma
r_struct
id|devclass_attribute
op_star
id|attr
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|dc
)paren
(brace
id|error
op_assign
id|driverfs_create_file
c_func
(paren
op_amp
id|attr-&gt;attr
comma
op_amp
id|dc-&gt;dir
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|devclass_remove_file
r_void
id|devclass_remove_file
c_func
(paren
r_struct
id|device_class
op_star
id|dc
comma
r_struct
id|devclass_attribute
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|dc
)paren
id|driverfs_remove_file
c_func
(paren
op_amp
id|dc-&gt;dir
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;devclass_dev_link - create symlink to device&squot;s directory&n; *&t;@cls - device class we&squot;re a part of &n; *&t;@dev - device we&squot;re linking to &n; *&n; *&t;Create a symlink in the class&squot;s devices/ directory to @dev&squot;s &n; *&t;directory in the physical hierarchy. The name is the device&squot;s &n; *&t;class-enumerated value (struct device::class_num). We&squot;re &n; *&t;creating:&n; *&t;&t;class/&lt;class name&gt;/devices/&lt;link name&gt; -&gt;&n; *&t;&t;root/&lt;path to device&gt;/&lt;device&squot;s dir&gt;&n; *&t;So, the link looks like:&n; *&t;&t;../../../root/&lt;path to device&gt;/&n; */
DECL|function|devclass_dev_link
r_int
id|devclass_dev_link
c_func
(paren
r_struct
id|device_class
op_star
id|cls
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_char
id|linkname
(braket
l_int|16
)braket
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|length
suffix:semicolon
r_int
id|error
suffix:semicolon
id|length
op_assign
id|get_devpath_length
c_func
(paren
id|dev
)paren
suffix:semicolon
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
id|snprintf
c_func
(paren
id|linkname
comma
l_int|16
comma
l_string|&quot;%u&quot;
comma
id|dev-&gt;class_num
)paren
suffix:semicolon
id|error
op_assign
id|driverfs_create_symlink
c_func
(paren
op_amp
id|cls-&gt;device_dir
comma
id|linkname
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
DECL|function|devclass_dev_unlink
r_void
id|devclass_dev_unlink
c_func
(paren
r_struct
id|device_class
op_star
id|cls
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_char
id|linkname
(braket
l_int|16
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|linkname
comma
l_int|16
comma
l_string|&quot;%u&quot;
comma
id|dev-&gt;class_num
)paren
suffix:semicolon
id|driverfs_remove_file
c_func
(paren
op_amp
id|cls-&gt;device_dir
comma
id|linkname
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;devclass_drv_link - create symlink to driver&squot;s directory&n; *&t;@drv:&t;driver we&squot;re linking up&n; *&n; *&t;Create a symlink in the class&squot;s drivers/ directory to @drv&squot;s&n; *&t;directory (in the bus&squot;s directory). It&squot;s name is &lt;bus&gt;:&lt;driver&gt;&n; *&t;to prevent naming conflicts.&n; *&n; *&t;We&squot;re creating &n; *&t;&t;class/&lt;class name&gt;/drivers/&lt;link name&gt; -&gt; &n; *&t;&t;bus/&lt;bus name&gt;/drivers/&lt;driver name&gt;/&n; *&t;So, the link looks like: &n; *&t;&t;../../../bus/&lt;bus name&gt;/drivers/&lt;driver name&gt;&n; */
DECL|function|devclass_drv_link
r_int
id|devclass_drv_link
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|drv-&gt;name
)paren
op_plus
id|strlen
c_func
(paren
id|drv-&gt;bus-&gt;name
)paren
op_plus
l_int|2
suffix:semicolon
id|name
op_assign
id|kmalloc
c_func
(paren
id|namelen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|namelen
comma
l_string|&quot;%s:%s&quot;
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|pathlen
op_assign
id|strlen
c_func
(paren
l_string|&quot;../../../bus/&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|drv-&gt;bus-&gt;name
)paren
op_plus
id|strlen
c_func
(paren
l_string|&quot;/drivers/&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|drv-&gt;name
)paren
op_plus
l_int|1
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
id|pathlen
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|path
comma
id|pathlen
comma
l_string|&quot;%s%s%s%s&quot;
comma
l_string|&quot;../../../bus/&quot;
comma
id|drv-&gt;bus-&gt;name
comma
l_string|&quot;/drivers/&quot;
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|error
op_assign
id|driverfs_create_symlink
c_func
(paren
op_amp
id|drv-&gt;devclass-&gt;driver_dir
comma
id|name
comma
id|path
)paren
suffix:semicolon
id|Done
suffix:colon
id|kfree
c_func
(paren
id|name
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
DECL|function|devclass_drv_unlink
r_void
id|devclass_drv_unlink
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|length
suffix:semicolon
id|length
op_assign
id|strlen
c_func
(paren
id|drv-&gt;name
)paren
op_plus
id|strlen
c_func
(paren
id|drv-&gt;bus-&gt;name
)paren
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|name
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
(brace
id|driverfs_remove_file
c_func
(paren
op_amp
id|drv-&gt;devclass-&gt;driver_dir
comma
id|name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
)brace
DECL|function|devclass_remove_dir
r_void
id|devclass_remove_dir
c_func
(paren
r_struct
id|device_class
op_star
id|dc
)paren
(brace
id|driverfs_remove_dir
c_func
(paren
op_amp
id|dc-&gt;device_dir
)paren
suffix:semicolon
id|driverfs_remove_dir
c_func
(paren
op_amp
id|dc-&gt;driver_dir
)paren
suffix:semicolon
id|driverfs_remove_dir
c_func
(paren
op_amp
id|dc-&gt;dir
)paren
suffix:semicolon
)brace
DECL|function|devclass_make_dir
r_int
id|devclass_make_dir
c_func
(paren
r_struct
id|device_class
op_star
id|dc
)paren
(brace
r_int
id|error
suffix:semicolon
id|dc-&gt;dir.name
op_assign
id|dc-&gt;name
suffix:semicolon
id|dc-&gt;dir.ops
op_assign
op_amp
id|devclass_attr_ops
suffix:semicolon
id|error
op_assign
id|device_create_dir
c_func
(paren
op_amp
id|dc-&gt;dir
comma
op_amp
id|class_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|dc-&gt;driver_dir.name
op_assign
l_string|&quot;drivers&quot;
suffix:semicolon
id|error
op_assign
id|device_create_dir
c_func
(paren
op_amp
id|dc-&gt;driver_dir
comma
op_amp
id|dc-&gt;dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|dc-&gt;device_dir.name
op_assign
l_string|&quot;devices&quot;
suffix:semicolon
id|error
op_assign
id|device_create_dir
c_func
(paren
op_amp
id|dc-&gt;device_dir
comma
op_amp
id|dc-&gt;dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
id|driverfs_remove_dir
c_func
(paren
op_amp
id|dc-&gt;dir
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|variable|class_dir
r_static
r_struct
id|driver_dir_entry
id|class_dir
op_assign
(brace
id|name
suffix:colon
l_string|&quot;class&quot;
comma
id|mode
suffix:colon
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
DECL|function|devclass_driverfs_init
r_static
r_int
id|__init
id|devclass_driverfs_init
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
id|class_dir
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|devclass_driverfs_init
id|core_initcall
c_func
(paren
id|devclass_driverfs_init
)paren
suffix:semicolon
DECL|variable|devclass_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|devclass_create_file
)paren
suffix:semicolon
DECL|variable|devclass_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|devclass_remove_file
)paren
suffix:semicolon
eof
