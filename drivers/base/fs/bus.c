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
dot
id|name
op_assign
l_string|&quot;bus&quot;
comma
dot
id|mode
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
eof
