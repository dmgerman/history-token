multiline_comment|/*&n; * driver.c - centralized device driver management&n; *&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|function|driver_for_each_dev
r_int
id|driver_for_each_dev
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
comma
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|callback
)paren
(paren
r_struct
id|device
op_star
comma
r_void
op_star
)paren
)paren
(brace
r_struct
id|device
op_star
id|next
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|get_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|drv-&gt;lock
)paren
suffix:semicolon
id|node
op_assign
id|drv-&gt;devices.next
suffix:semicolon
r_while
c_loop
(paren
id|node
op_ne
op_amp
id|drv-&gt;devices
)paren
(brace
id|next
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|device
comma
id|driver_list
)paren
suffix:semicolon
id|get_device
c_func
(paren
id|next
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|drv-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|callback
c_func
(paren
id|dev
comma
id|data
)paren
)paren
)paren
(brace
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|drv-&gt;lock
)paren
suffix:semicolon
id|node
op_assign
id|dev-&gt;driver_list.next
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|drv-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * driver_make_dir - create a driverfs directory for a driver&n; * @drv:&t;driver in question&n; */
DECL|function|driver_make_dir
r_static
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
multiline_comment|/**&n; * driver_register - register driver with bus&n; * @drv:&t;driver to register&n; * &n; * Add to bus&squot;s list of devices&n; */
DECL|function|driver_register
r_int
id|driver_register
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|drv-&gt;bus
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Registering driver &squot;%s&squot; with bus &squot;%s&squot;&bslash;n&quot;
comma
id|drv-&gt;name
comma
id|drv-&gt;bus-&gt;name
)paren
suffix:semicolon
id|get_bus
c_func
(paren
id|drv-&gt;bus
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|drv-&gt;refcount
comma
l_int|2
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|drv-&gt;lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|drv-&gt;devices
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|drv-&gt;bus_list
comma
op_amp
id|drv-&gt;bus-&gt;drivers
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;lock
)paren
suffix:semicolon
id|driver_make_dir
c_func
(paren
id|drv
)paren
suffix:semicolon
id|driver_attach
c_func
(paren
id|drv
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__remove_driver
r_static
r_void
id|__remove_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;bus
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Unregistering driver &squot;%s&squot; from bus &squot;%s&squot;&bslash;n&quot;
comma
id|drv-&gt;name
comma
id|drv-&gt;bus-&gt;name
)paren
suffix:semicolon
id|driver_detach
c_func
(paren
id|drv
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drv-&gt;bus_list
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;lock
)paren
suffix:semicolon
id|driverfs_remove_dir
c_func
(paren
op_amp
id|drv-&gt;dir
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|drv-&gt;bus
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drv-&gt;release
)paren
id|drv
op_member_access_from_pointer
id|release
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|remove_driver
r_void
id|remove_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|device_lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|drv-&gt;refcount
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|device_lock
)paren
suffix:semicolon
id|__remove_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * put_driver - decrement driver&squot;s refcount and clean up if necessary&n; * @drv:&t;driver in question&n; */
DECL|function|put_driver
r_void
id|put_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|drv-&gt;refcount
comma
op_amp
id|device_lock
)paren
)paren
r_return
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|device_lock
)paren
suffix:semicolon
id|__remove_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|variable|driver_for_each_dev
id|EXPORT_SYMBOL
c_func
(paren
id|driver_for_each_dev
)paren
suffix:semicolon
DECL|variable|driver_register
id|EXPORT_SYMBOL
c_func
(paren
id|driver_register
)paren
suffix:semicolon
DECL|variable|put_driver
id|EXPORT_SYMBOL
c_func
(paren
id|put_driver
)paren
suffix:semicolon
DECL|variable|remove_driver
id|EXPORT_SYMBOL
c_func
(paren
id|remove_driver
)paren
suffix:semicolon
eof
