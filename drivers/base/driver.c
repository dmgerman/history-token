multiline_comment|/*&n; * driver.c - centralized device driver management&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; * &n; * This file is released under the GPLv2&n; *&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|macro|to_dev
mdefine_line|#define to_dev(node) container_of(node,struct device,driver_list)
DECL|macro|to_drv
mdefine_line|#define to_drv(obj) container_of(obj,struct device_driver,kobj)
multiline_comment|/**&n; *&t;driver_create_file - create sysfs file for driver.&n; *&t;@drv:&t;driver.&n; *&t;@attr:&t;driver attribute descriptor.&n; */
DECL|function|driver_create_file
r_int
id|driver_create_file
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
comma
r_struct
id|driver_attribute
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
id|get_driver
c_func
(paren
id|drv
)paren
)paren
(brace
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|drv-&gt;kobj
comma
op_amp
id|attr-&gt;attr
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
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
multiline_comment|/**&n; *&t;driver_remove_file - remove sysfs file for driver.&n; *&t;@drv:&t;driver.&n; *&t;@attr:&t;driver attribute descriptor.&n; */
DECL|function|driver_remove_file
r_void
id|driver_remove_file
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
comma
r_struct
id|driver_attribute
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|get_driver
c_func
(paren
id|drv
)paren
)paren
(brace
id|sysfs_remove_file
c_func
(paren
op_amp
id|drv-&gt;kobj
comma
op_amp
id|attr-&gt;attr
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;get_driver - increment driver reference count.&n; *&t;@drv:&t;driver.&n; */
DECL|function|get_driver
r_struct
id|device_driver
op_star
id|get_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_return
id|drv
ques
c_cond
id|to_drv
c_func
(paren
id|kobject_get
c_func
(paren
op_amp
id|drv-&gt;kobj
)paren
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;put_driver - decrement driver&squot;s refcount.&n; *&t;@drv:&t;driver.&n; */
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
id|kobject_put
c_func
(paren
op_amp
id|drv-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;driver_register - register driver with bus&n; *&t;@drv:&t;driver to register&n; *&n; *&t;We pass off most of the work to the bus_add_driver() call,&n; *&t;since most of the things we have to do deal with the bus &n; *&t;structures.&n; *&n; *&t;The one interesting aspect is that we initialize @drv-&gt;unload_sem&n; *&t;to a locked state here. It will be unlocked when the driver&n; *&t;reference count reaches 0.&n; */
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
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|drv-&gt;devices
)paren
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|drv-&gt;unload_sem
)paren
suffix:semicolon
r_return
id|bus_add_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;driver_unregister - remove driver from system.&n; *&t;@drv:&t;driver.&n; *&n; *&t;Again, we pass off most of the work to the bus-level call.&n; *&n; *&t;Though, once that is done, we attempt to take @drv-&gt;unload_sem.&n; *&t;This will block until the driver refcount reaches 0, and it is&n; *&t;released. Only modular drivers will call this function, and we &n; *&t;have to guarantee that it won&squot;t complete, letting the driver &n; *&t;unload until all references are gone.&n; */
DECL|function|driver_unregister
r_void
id|driver_unregister
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
id|bus_remove_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|drv-&gt;unload_sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|drv-&gt;unload_sem
)paren
suffix:semicolon
)brace
DECL|variable|driver_register
id|EXPORT_SYMBOL
c_func
(paren
id|driver_register
)paren
suffix:semicolon
DECL|variable|driver_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|driver_unregister
)paren
suffix:semicolon
DECL|variable|get_driver
id|EXPORT_SYMBOL
c_func
(paren
id|get_driver
)paren
suffix:semicolon
DECL|variable|put_driver
id|EXPORT_SYMBOL
c_func
(paren
id|put_driver
)paren
suffix:semicolon
DECL|variable|driver_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|driver_create_file
)paren
suffix:semicolon
DECL|variable|driver_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|driver_remove_file
)paren
suffix:semicolon
eof
