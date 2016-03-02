macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &quot;fs.h&quot;
multiline_comment|/**&n; * driver_make_dir - create a driverfs directory for a driver&n; * @drv:&t;driver in question&n; */
DECL|function|driver_make_dir
r_int
id|driver_make_dir
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
id|drv-&gt;dir.name
op_assign
id|drv-&gt;name
suffix:semicolon
r_return
id|device_create_dir
c_func
(paren
op_amp
id|drv-&gt;dir
comma
op_amp
id|drv-&gt;bus-&gt;driver_dir
)paren
suffix:semicolon
)brace
DECL|function|driver_remove_dir
r_void
id|driver_remove_dir
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
id|driverfs_remove_dir
c_func
(paren
op_amp
id|drv-&gt;dir
)paren
suffix:semicolon
)brace
eof
