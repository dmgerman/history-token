macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;fs.h&quot;
DECL|variable|bus_dir
r_static
r_struct
id|driver_dir_entry
id|bus_dir
suffix:semicolon
DECL|macro|to_bus_attr
mdefine_line|#define to_bus_attr(_attr) container_of(_attr,struct bus_attribute,attr)
DECL|macro|to_bus
mdefine_line|#define to_bus(dir) container_of(dir,struct bus_type,dir)
multiline_comment|/* driverfs ops for device attribute files */
r_static
r_int
DECL|function|bus_attr_open
id|bus_attr_open
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|to_bus
c_func
(paren
id|dir
)paren
suffix:semicolon
id|get_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|bus_attr_close
id|bus_attr_close
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|to_bus
c_func
(paren
id|dir
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|bus_attr_show
id|bus_attr_show
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
id|bus_attribute
op_star
id|bus_attr
op_assign
id|to_bus_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|bus_type
op_star
id|bus
op_assign
id|to_bus
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
id|bus_attr-&gt;show
)paren
id|ret
op_assign
id|bus_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|bus
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
DECL|function|bus_attr_store
id|bus_attr_store
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
id|bus_attribute
op_star
id|bus_attr
op_assign
id|to_bus_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|bus_type
op_star
id|bus
op_assign
id|to_bus
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
id|bus_attr-&gt;store
)paren
id|ret
op_assign
id|bus_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|bus
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
DECL|variable|bus_attr_ops
r_static
r_struct
id|driverfs_ops
id|bus_attr_ops
op_assign
(brace
id|open
suffix:colon
id|bus_attr_open
comma
id|close
suffix:colon
id|bus_attr_close
comma
id|show
suffix:colon
id|bus_attr_show
comma
id|store
suffix:colon
id|bus_attr_store
comma
)brace
suffix:semicolon
DECL|function|bus_create_file
r_int
id|bus_create_file
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|bus_attribute
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
id|get_bus
c_func
(paren
id|bus
)paren
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
id|bus-&gt;dir
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|bus
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
DECL|function|bus_remove_file
r_void
id|bus_remove_file
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|bus_attribute
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|get_bus
c_func
(paren
id|bus
)paren
)paren
(brace
id|driverfs_remove_file
c_func
(paren
op_amp
id|bus-&gt;dir
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
)brace
DECL|function|bus_make_dir
r_int
id|bus_make_dir
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
r_int
id|error
suffix:semicolon
id|bus-&gt;dir.name
op_assign
id|bus-&gt;name
suffix:semicolon
id|bus-&gt;dir.ops
op_assign
op_amp
id|bus_attr_ops
suffix:semicolon
id|error
op_assign
id|device_create_dir
c_func
(paren
op_amp
id|bus-&gt;dir
comma
op_amp
id|bus_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|bus-&gt;device_dir.name
op_assign
l_string|&quot;devices&quot;
suffix:semicolon
id|device_create_dir
c_func
(paren
op_amp
id|bus-&gt;device_dir
comma
op_amp
id|bus-&gt;dir
)paren
suffix:semicolon
id|bus-&gt;driver_dir.name
op_assign
l_string|&quot;drivers&quot;
suffix:semicolon
id|device_create_dir
c_func
(paren
op_amp
id|bus-&gt;driver_dir
comma
op_amp
id|bus-&gt;dir
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|bus_remove_dir
r_void
id|bus_remove_dir
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
multiline_comment|/* remove driverfs entries */
id|driverfs_remove_dir
c_func
(paren
op_amp
id|bus-&gt;driver_dir
)paren
suffix:semicolon
id|driverfs_remove_dir
c_func
(paren
op_amp
id|bus-&gt;device_dir
)paren
suffix:semicolon
id|driverfs_remove_dir
c_func
(paren
op_amp
id|bus-&gt;dir
)paren
suffix:semicolon
)brace
DECL|variable|bus_dir
r_static
r_struct
id|driver_dir_entry
id|bus_dir
op_assign
(brace
id|name
suffix:colon
l_string|&quot;bus&quot;
comma
id|mode
suffix:colon
(paren
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
comma
)brace
suffix:semicolon
DECL|function|bus_init
r_static
r_int
id|__init
id|bus_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* make &squot;bus&squot; driverfs directory */
r_return
id|driverfs_create_dir
c_func
(paren
op_amp
id|bus_dir
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|bus_init
id|core_initcall
c_func
(paren
id|bus_init
)paren
suffix:semicolon
DECL|variable|bus_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|bus_create_file
)paren
suffix:semicolon
DECL|variable|bus_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|bus_remove_file
)paren
suffix:semicolon
eof
