multiline_comment|/*&n; * bus.c - bus driver management&n; * &n; * Copyright (c) 2002 Patrick Mochel&n; *&t;&t; 2002 Open Source Development Lab&n; * &n; * &n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|macro|to_dev
mdefine_line|#define to_dev(node) container_of(node,struct device,bus_list)
DECL|macro|to_drv
mdefine_line|#define to_drv(node) container_of(node,struct device_driver,kobj.entry)
DECL|macro|to_bus_attr
mdefine_line|#define to_bus_attr(_attr) container_of(_attr,struct bus_attribute,attr)
DECL|macro|to_bus
mdefine_line|#define to_bus(obj) container_of(obj,struct bus_type,subsys.kset.kobj)
multiline_comment|/*&n; * sysfs bindings for drivers&n; */
DECL|macro|to_drv_attr
mdefine_line|#define to_drv_attr(_attr) container_of(_attr,struct driver_attribute,attr)
DECL|macro|to_driver
mdefine_line|#define to_driver(obj) container_of(obj, struct device_driver, kobj)
r_static
id|ssize_t
DECL|function|drv_attr_show
id|drv_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|driver_attribute
op_star
id|drv_attr
op_assign
id|to_drv_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device_driver
op_star
id|drv
op_assign
id|to_driver
c_func
(paren
id|kobj
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
id|drv_attr-&gt;show
)paren
id|ret
op_assign
id|drv_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|drv
comma
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|drv_attr_store
id|drv_attr_store
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
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
)paren
(brace
r_struct
id|driver_attribute
op_star
id|drv_attr
op_assign
id|to_drv_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|device_driver
op_star
id|drv
op_assign
id|to_driver
c_func
(paren
id|kobj
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
id|drv_attr-&gt;store
)paren
id|ret
op_assign
id|drv_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|drv
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|driver_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|driver_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|drv_attr_show
comma
dot
id|store
op_assign
id|drv_attr_store
comma
)brace
suffix:semicolon
DECL|function|driver_release
r_static
r_void
id|driver_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|device_driver
op_star
id|drv
op_assign
id|to_driver
c_func
(paren
id|kobj
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
DECL|variable|ktype_driver
r_static
r_struct
id|kobj_type
id|ktype_driver
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|driver_sysfs_ops
comma
dot
id|release
op_assign
id|driver_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * sysfs bindings for buses&n; */
r_static
id|ssize_t
DECL|function|bus_attr_show
id|bus_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
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
id|kobj
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
id|kobject
op_star
id|kobj
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
id|kobj
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
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|bus_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|bus_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|bus_attr_show
comma
dot
id|store
op_assign
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
id|sysfs_create_file
c_func
(paren
op_amp
id|bus-&gt;subsys.kset.kobj
comma
op_amp
id|attr-&gt;attr
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
id|sysfs_remove_file
c_func
(paren
op_amp
id|bus-&gt;subsys.kset.kobj
comma
op_amp
id|attr-&gt;attr
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
DECL|variable|ktype_bus
r_static
r_struct
id|kobj_type
id|ktype_bus
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|bus_sysfs_ops
comma
)brace
suffix:semicolon
id|decl_subsys
c_func
(paren
id|bus
comma
op_amp
id|ktype_bus
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;bus_for_each_dev - device iterator.&n; *&t;@bus:&t;bus type.&n; *&t;@start:&t;device to start iterating from.&n; *&t;@data:&t;data for the callback.&n; *&t;@fn:&t;function to be called for each device.&n; *&n; *&t;Iterate over @bus&squot;s list of devices, and call @fn for each,&n; *&t;passing it @data. If @start is not NULL, we use that device to&n; *&t;begin iterating from.&n; *&n; *&t;We check the return of @fn each time. If it returns anything&n; *&t;other than 0, we break out and return that value.&n; *&n; *&t;NOTE: The device that returns a non-zero value is not retained&n; *&t;in any way, nor is its refcount incremented. If the caller needs&n; *&t;to retain this data, it should do, and increment the reference &n; *&t;count in the supplied callback.&n; */
DECL|function|bus_for_each_dev
r_int
id|bus_for_each_dev
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|device
op_star
id|start
comma
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fn
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
id|list_head
op_star
id|head
comma
op_star
id|entry
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
(paren
id|bus
op_assign
id|get_bus
c_func
(paren
id|bus
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|head
op_assign
id|start
ques
c_cond
op_amp
id|start-&gt;bus_list
suffix:colon
op_amp
id|bus-&gt;devices.list
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
id|head
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|get_device
c_func
(paren
id|to_dev
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|error
op_assign
id|fn
c_func
(paren
id|dev
comma
id|data
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_for_each_drv - driver iterator&n; *&t;@bus:&t;bus we&squot;re dealing with.&n; *&t;@start:&t;driver to start iterating on.&n; *&t;@data:&t;data to pass to the callback.&n; *&t;@fn:&t;function to call for each driver.&n; *&n; *&t;This is nearly identical to the device iterator above.&n; *&t;We iterate over each driver that belongs to @bus, and call&n; *&t;@fn for each. If @fn returns anything but 0, we break out&n; *&t;and return it. If @start is not NULL, we use it as the head&n; *&t;of the list.&n; *&n; *&t;NOTE: we don&squot;t return the driver that returns a non-zero &n; *&t;value, nor do we leave the reference count incremented for that&n; *&t;driver. If the caller needs to know that info, it must set it&n; *&t;in the callback. It must also be sure to increment the refcount&n; *&t;so it doesn&squot;t disappear before returning to the caller.&n; */
DECL|function|bus_for_each_drv
r_int
id|bus_for_each_drv
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|device_driver
op_star
id|start
comma
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|device_driver
op_star
comma
r_void
op_star
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|head
comma
op_star
id|entry
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
(paren
id|bus
op_assign
id|get_bus
c_func
(paren
id|bus
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|head
op_assign
id|start
ques
c_cond
op_amp
id|start-&gt;kobj.entry
suffix:colon
op_amp
id|bus-&gt;drivers.list
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
id|head
)paren
(brace
r_struct
id|device_driver
op_star
id|drv
op_assign
id|get_driver
c_func
(paren
id|to_drv
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|error
op_assign
id|fn
c_func
(paren
id|drv
comma
id|data
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_bind_driver - bind a driver to one device.&n; *&t;@dev:&t;device.&n; *&n; *&t;Allow manual attachment of a driver to a deivce.&n; *&t;Caller must have already set @dev-&gt;driver.&n; *&n; *&t;Note that this does not modify the bus reference count &n; *&t;nor take the bus&squot;s rwsem. Please verify those are accounted &n; *&t;for before calling this. (It is ok to call with no other effort&n; *&t;from a driver&squot;s probe() method.)&n; */
DECL|function|device_bind_driver
r_void
id|device_bind_driver
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;bound device &squot;%s&squot; to driver &squot;%s&squot;&bslash;n&quot;
comma
id|dev-&gt;bus_id
comma
id|dev-&gt;driver-&gt;name
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;driver_list
comma
op_amp
id|dev-&gt;driver-&gt;devices
)paren
suffix:semicolon
id|sysfs_create_link
c_func
(paren
op_amp
id|dev-&gt;driver-&gt;kobj
comma
op_amp
id|dev-&gt;kobj
comma
id|dev-&gt;kobj.name
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_match - check compatibility between device &amp; driver.&n; *&t;@dev:&t;device.&n; *&t;@drv:&t;driver.&n; *&n; *&t;First, we call the bus&squot;s match function, which should compare&n; *&t;the device IDs the driver supports with the device IDs of the &n; *&t;device. Note we don&squot;t do this ourselves because we don&squot;t know &n; *&t;the format of the ID structures, nor what is to be considered&n; *&t;a match and what is not.&n; *&t;&n; *&t;If we find a match, we call @drv-&gt;probe(@dev) if it exists, and &n; *&t;call attach() above.&n; */
DECL|function|bus_match
r_static
r_int
id|bus_match
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus
op_member_access_from_pointer
id|match
c_func
(paren
id|dev
comma
id|drv
)paren
)paren
(brace
id|dev-&gt;driver
op_assign
id|drv
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;probe
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|dev
)paren
)paren
)paren
(brace
id|dev-&gt;driver
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
)brace
id|device_bind_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_attach - try to attach device to a driver.&n; *&t;@dev:&t;device.&n; *&n; *&t;Walk the list of drivers that the bus has and call bus_match() &n; *&t;for each pair. If a compatible pair is found, break out and return.&n; */
DECL|function|device_attach
r_static
r_int
id|device_attach
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
)paren
(brace
id|device_bind_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;match
)paren
r_return
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|bus-&gt;drivers.list
)paren
(brace
r_struct
id|device_driver
op_star
id|drv
op_assign
id|to_drv
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|bus_match
c_func
(paren
id|dev
comma
id|drv
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;driver_attach - try to bind driver to devices.&n; *&t;@drv:&t;driver.&n; *&n; *&t;Walk the list of devices that the bus has on it and try to match&n; *&t;the driver with each one.&n; *&t;If bus_match() returns 0 and the @dev-&gt;driver is set, we&squot;ve found&n; *&t;a compatible pair, so we call devclass_add_device() to add the &n; *&t;device to the class. &n; *&n; *&t;Note that we ignore the error from bus_match(), since it&squot;s perfectly&n; *&t;valid for a driver not to bind to any devices.&n; */
DECL|function|driver_attach
r_static
r_int
id|driver_attach
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|drv-&gt;bus
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;match
)paren
r_return
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|bus-&gt;devices.list
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|entry
comma
r_struct
id|device
comma
id|bus_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;driver
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bus_match
c_func
(paren
id|dev
comma
id|drv
)paren
op_logical_and
id|dev-&gt;driver
)paren
id|devclass_add_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_release_driver - manually detach device from driver.&n; *&t;@dev:&t;device.&n; *&n; *&t;Manually detach device from driver.&n; *&t;Note that this is called without incrementing the bus&n; *&t;reference count nor taking the bus&squot;s rwsem. Be sure that&n; *&t;those are accounted for before calling this function.&n; */
DECL|function|device_release_driver
r_void
id|device_release_driver
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|device_driver
op_star
id|drv
op_assign
id|dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|drv-&gt;kobj
comma
id|dev-&gt;kobj.name
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|dev-&gt;driver_list
)paren
suffix:semicolon
id|devclass_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;remove
)paren
id|drv
op_member_access_from_pointer
id|remove
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;driver
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;driver_detach - detach driver from all devices it controls.&n; *&t;@drv:&t;driver.&n; */
DECL|function|driver_detach
r_static
r_void
id|driver_detach
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|list_head
op_star
id|entry
comma
op_star
id|next
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|entry
comma
id|next
comma
op_amp
id|drv-&gt;devices
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|container_of
c_func
(paren
id|entry
comma
r_struct
id|device
comma
id|driver_list
)paren
suffix:semicolon
id|device_release_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;bus_add_device - add device to bus&n; *&t;@dev:&t;device being added&n; *&n; *&t;- Add the device to its bus&squot;s list of devices.&n; *&t;- Try to attach to driver.&n; *&t;- Create link to device&squot;s physical location.&n; */
DECL|function|bus_add_device
r_int
id|bus_add_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|get_bus
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;bus %s: add device %s&bslash;n&quot;
comma
id|bus-&gt;name
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;bus_list
comma
op_amp
id|dev-&gt;bus-&gt;devices.list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_attach
c_func
(paren
id|dev
)paren
)paren
)paren
id|list_del_init
c_func
(paren
op_amp
id|dev-&gt;bus_list
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|sysfs_create_link
c_func
(paren
op_amp
id|bus-&gt;devices.kobj
comma
op_amp
id|dev-&gt;kobj
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_remove_device - remove device from bus&n; *&t;@dev:&t;device to be removed&n; *&n; *&t;- Remove symlink from bus&squot;s directory.&n; *&t;- Delete device from bus&squot;s list.&n; *&t;- Detach from its driver.&n; *&t;- Drop reference taken in bus_add_device().&n; */
DECL|function|bus_remove_device
r_void
id|bus_remove_device
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
id|dev-&gt;bus
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;devices.kobj
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;bus %s: remove device %s&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;name
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|device_release_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|dev-&gt;bus_list
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|dev-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;bus_add_driver - Add a driver to the bus.&n; *&t;@drv:&t;driver.&n; *&n; */
DECL|function|bus_add_driver
r_int
id|bus_add_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|bus_type
op_star
id|bus
op_assign
id|get_bus
c_func
(paren
id|drv-&gt;bus
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;bus %s: add driver %s&bslash;n&quot;
comma
id|bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|drv-&gt;kobj.name
comma
id|drv-&gt;name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
id|drv-&gt;kobj.kset
op_assign
op_amp
id|bus-&gt;drivers
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|kobject_register
c_func
(paren
op_amp
id|drv-&gt;kobj
)paren
)paren
)paren
(brace
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|devclass_add_driver
c_func
(paren
id|drv
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|driver_attach
c_func
(paren
id|drv
)paren
)paren
)paren
(brace
id|devclass_remove_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kobject_unregister
c_func
(paren
op_amp
id|drv-&gt;kobj
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
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_remove_driver - delete driver from bus&squot;s knowledge.&n; *&t;@drv:&t;driver.&n; *&n; *&t;Detach the driver from the devices it controls, and remove&n; *&t;it from it&squot;s bus&squot;s list of drivers. Finally, we drop the reference&n; *&t;to the bus we took in bus_add_driver().&n; */
DECL|function|bus_remove_driver
r_void
id|bus_remove_driver
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
id|down_write
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;bus %s: remove driver %s&bslash;n&quot;
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|driver_detach
c_func
(paren
id|drv
)paren
suffix:semicolon
id|devclass_remove_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|drv-&gt;bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|kobject_unregister
c_func
(paren
op_amp
id|drv-&gt;kobj
)paren
suffix:semicolon
id|put_bus
c_func
(paren
id|drv-&gt;bus
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_bus
r_struct
id|bus_type
op_star
id|get_bus
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
r_return
id|bus
ques
c_cond
id|container_of
c_func
(paren
id|subsys_get
c_func
(paren
op_amp
id|bus-&gt;subsys
)paren
comma
r_struct
id|bus_type
comma
id|subsys
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|put_bus
r_void
id|put_bus
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
id|subsys_put
c_func
(paren
op_amp
id|bus-&gt;subsys
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;find_bus - locate bus by name.&n; *&t;@name:&t;name of bus.&n; *&n; *&t;Call kset_find_obj() to iterate over list of buses to&n; *&t;find a bus by name. Return bus if found.&n; */
DECL|function|find_bus
r_struct
id|bus_type
op_star
id|find_bus
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|kobject
op_star
id|k
op_assign
id|kset_find_obj
c_func
(paren
op_amp
id|bus_subsys.kset
comma
id|name
)paren
suffix:semicolon
r_return
id|k
ques
c_cond
id|to_bus
c_func
(paren
id|k
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_register - register a bus with the system.&n; *&t;@bus:&t;bus.&n; *&n; *&t;Once we have that, we registered the bus with the kobject&n; *&t;infrastructure, then register the children subsystems it has:&n; *&t;the devices and drivers that belong to the bus. &n; */
DECL|function|bus_register
r_int
id|bus_register
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
id|strncpy
c_func
(paren
id|bus-&gt;subsys.kset.kobj.name
comma
id|bus-&gt;name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
id|subsys_set_kset
c_func
(paren
id|bus
comma
id|bus_subsys
)paren
suffix:semicolon
id|subsystem_register
c_func
(paren
op_amp
id|bus-&gt;subsys
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|bus-&gt;devices.kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;devices&quot;
)paren
suffix:semicolon
id|bus-&gt;devices.subsys
op_assign
op_amp
id|bus-&gt;subsys
suffix:semicolon
id|kset_register
c_func
(paren
op_amp
id|bus-&gt;devices
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|bus-&gt;drivers.kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;drivers&quot;
)paren
suffix:semicolon
id|bus-&gt;drivers.subsys
op_assign
op_amp
id|bus-&gt;subsys
suffix:semicolon
id|bus-&gt;drivers.ktype
op_assign
op_amp
id|ktype_driver
suffix:semicolon
id|kset_register
c_func
(paren
op_amp
id|bus-&gt;drivers
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;bus type &squot;%s&squot; registered&bslash;n&quot;
comma
id|bus-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bus_unregister - remove a bus from the system &n; *&t;@bus:&t;bus.&n; *&n; *&t;Unregister the child subsystems and the bus itself.&n; *&t;Finally, we call put_bus() to release the refcount&n; */
DECL|function|bus_unregister
r_void
id|bus_unregister
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;bus %s: unregistering&bslash;n&quot;
comma
id|bus-&gt;name
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|bus-&gt;drivers
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|bus-&gt;devices
)paren
suffix:semicolon
id|subsystem_unregister
c_func
(paren
op_amp
id|bus-&gt;subsys
)paren
suffix:semicolon
)brace
DECL|function|bus_subsys_init
r_static
r_int
id|__init
id|bus_subsys_init
c_func
(paren
r_void
)paren
(brace
r_return
id|subsystem_register
c_func
(paren
op_amp
id|bus_subsys
)paren
suffix:semicolon
)brace
DECL|variable|bus_subsys_init
id|core_initcall
c_func
(paren
id|bus_subsys_init
)paren
suffix:semicolon
DECL|variable|bus_for_each_dev
id|EXPORT_SYMBOL
c_func
(paren
id|bus_for_each_dev
)paren
suffix:semicolon
DECL|variable|bus_for_each_drv
id|EXPORT_SYMBOL
c_func
(paren
id|bus_for_each_drv
)paren
suffix:semicolon
DECL|variable|device_bind_driver
id|EXPORT_SYMBOL
c_func
(paren
id|device_bind_driver
)paren
suffix:semicolon
DECL|variable|device_release_driver
id|EXPORT_SYMBOL
c_func
(paren
id|device_release_driver
)paren
suffix:semicolon
DECL|variable|bus_add_device
id|EXPORT_SYMBOL
c_func
(paren
id|bus_add_device
)paren
suffix:semicolon
DECL|variable|bus_remove_device
id|EXPORT_SYMBOL
c_func
(paren
id|bus_remove_device
)paren
suffix:semicolon
DECL|variable|bus_register
id|EXPORT_SYMBOL
c_func
(paren
id|bus_register
)paren
suffix:semicolon
DECL|variable|bus_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|bus_unregister
)paren
suffix:semicolon
DECL|variable|get_bus
id|EXPORT_SYMBOL
c_func
(paren
id|get_bus
)paren
suffix:semicolon
DECL|variable|put_bus
id|EXPORT_SYMBOL
c_func
(paren
id|put_bus
)paren
suffix:semicolon
DECL|variable|find_bus
id|EXPORT_SYMBOL
c_func
(paren
id|find_bus
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
