multiline_comment|/*&n; * drivers/base/core.c - core driver model code (device registration, etc)&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; * &n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;base.h&quot;
macro_line|#include &quot;power/power.h&quot;
DECL|variable|platform_notify
r_int
(paren
op_star
id|platform_notify
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|platform_notify_remove
r_int
(paren
op_star
id|platform_notify_remove
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * sysfs bindings for devices.&n; */
DECL|macro|to_dev
mdefine_line|#define to_dev(obj) container_of(obj,struct device,kobj)
DECL|macro|to_dev_attr
mdefine_line|#define to_dev_attr(_attr) container_of(_attr,struct device_attribute,attr)
r_extern
r_struct
id|attribute
op_star
id|dev_default_attrs
(braket
)braket
suffix:semicolon
r_static
id|ssize_t
DECL|function|dev_attr_show
id|dev_attr_show
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
id|to_dev
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
id|to_dev
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
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dev_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|dev_sysfs_ops
op_assign
(brace
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
multiline_comment|/**&n; *&t;device_release - free device structure.&n; *&t;@kobj:&t;device&squot;s kobject.&n; *&n; *&t;This is called once the reference count for the object&n; *&t;reaches 0. We forward the call to the device&squot;s release&n; *&t;method, which should handle actually freeing the structure.&n; */
DECL|function|device_release
r_static
r_void
id|device_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;release
)paren
id|dev
op_member_access_from_pointer
id|release
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Device &squot;%s&squot; does not have a release() function, &quot;
l_string|&quot;it is broken and must be fixed.&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|variable|ktype_device
r_static
r_struct
id|kobj_type
id|ktype_device
op_assign
(brace
dot
id|release
op_assign
id|device_release
comma
dot
id|sysfs_ops
op_assign
op_amp
id|dev_sysfs_ops
comma
dot
id|default_attrs
op_assign
id|dev_default_attrs
comma
)brace
suffix:semicolon
DECL|function|dev_hotplug_filter
r_static
r_int
id|dev_hotplug_filter
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobj_type
op_star
id|ktype
op_assign
id|get_ktype
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ktype
op_eq
op_amp
id|ktype_device
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dev_hotplug_name
r_static
r_char
op_star
id|dev_hotplug_name
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_return
id|dev-&gt;bus-&gt;name
suffix:semicolon
)brace
DECL|function|dev_hotplug
r_static
r_int
id|dev_hotplug
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;hotplug
)paren
(brace
multiline_comment|/* have the bus specific function add its stuff */
id|retval
op_assign
id|dev-&gt;bus-&gt;hotplug
(paren
id|dev
comma
id|envp
comma
id|num_envp
comma
id|buffer
comma
id|buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|pr_debug
(paren
l_string|&quot;%s - hotplug() returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|device_hotplug_ops
r_static
r_struct
id|kset_hotplug_ops
id|device_hotplug_ops
op_assign
(brace
dot
id|filter
op_assign
id|dev_hotplug_filter
comma
dot
id|name
op_assign
id|dev_hotplug_name
comma
dot
id|hotplug
op_assign
id|dev_hotplug
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;device_subsys - structure to be registered with kobject core.&n; */
id|decl_subsys
c_func
(paren
id|devices
comma
op_amp
id|ktype_device
comma
op_amp
id|device_hotplug_ops
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;device_create_file - create sysfs attribute file for device.&n; *&t;@dev:&t;device.&n; *&t;@attr:&t;device attribute descriptor.&n; */
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
id|attr
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_device
c_func
(paren
id|dev
)paren
)paren
(brace
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|attr-&gt;attr
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
multiline_comment|/**&n; *&t;device_remove_file - remove sysfs attribute file.&n; *&t;@dev:&t;device.&n; *&t;@attr:&t;device attribute descriptor.&n; */
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
id|get_device
c_func
(paren
id|dev
)paren
)paren
(brace
id|sysfs_remove_file
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|attr-&gt;attr
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
multiline_comment|/**&n; *&t;device_initialize - init device structure.&n; *&t;@dev:&t;device.&n; *&n; *&t;This prepares the device for use by other layers,&n; *&t;including adding it to the device hierarchy. &n; *&t;It is the first half of device_register(), if called by&n; *&t;that, though it can also be called separately, so one&n; *&t;may use @dev&squot;s fields (e.g. the refcount).&n; */
DECL|function|device_initialize
r_void
id|device_initialize
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|kobj_set_kset_s
c_func
(paren
id|dev
comma
id|devices_subsys
)paren
suffix:semicolon
id|kobject_init
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;node
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;children
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;driver_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;bus_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;dma_pools
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_add - add device to device hierarchy.&n; *&t;@dev:&t;device.&n; *&n; *&t;This is part 2 of device_register(), though may be called &n; *&t;separately _iff_ device_initialize() has been called separately.&n; *&n; *&t;This adds it to the kobject hierarchy via kobject_add(), adds it&n; *&t;to the global and sibling lists for the device, then&n; *&t;adds it to the other relevant subsystems of the driver model.&n; */
DECL|function|device_add
r_int
id|device_add
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|device
op_star
id|parent
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dev
op_assign
id|get_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|strlen
c_func
(paren
id|dev-&gt;bus_id
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|parent
op_assign
id|get_device
c_func
(paren
id|dev-&gt;parent
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;DEV: registering device: ID = &squot;%s&squot;&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
multiline_comment|/* first, register with generic layer. */
id|kobject_set_name
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|dev-&gt;kobj.parent
op_assign
op_amp
id|parent-&gt;kobj
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|kobject_add
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
)paren
)paren
r_goto
id|Error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|device_pm_add
c_func
(paren
id|dev
)paren
)paren
)paren
r_goto
id|PMError
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|bus_add_device
c_func
(paren
id|dev
)paren
)paren
)paren
r_goto
id|BusError
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;node
comma
op_amp
id|parent-&gt;children
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
multiline_comment|/* notify platform of device entry */
r_if
c_cond
(paren
id|platform_notify
)paren
id|platform_notify
c_func
(paren
id|dev
)paren
suffix:semicolon
id|Done
suffix:colon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|BusError
suffix:colon
id|device_pm_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
id|PMError
suffix:colon
id|kobject_del
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
suffix:semicolon
id|Error
suffix:colon
r_if
c_cond
(paren
id|parent
)paren
id|put_device
c_func
(paren
id|parent
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_register - register a device with the system.&n; *&t;@dev:&t;pointer to the device structure&n; *&n; *&t;This happens in two clean steps - initialize the device&n; *&t;and add it to the system. The two steps can be called &n; *&t;separately, but this is the easiest and most common. &n; *&t;I.e. you should only call the two helpers separately if &n; *&t;have a clearly defined need to use and refcount the device&n; *&t;before it is added to the hierarchy.&n; */
DECL|function|device_register
r_int
id|device_register
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|device_initialize
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|device_add
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_device - increment reference count for device.&n; *&t;@dev:&t;device.&n; *&n; *&t;This simply forwards the call to kobject_get(), though&n; *&t;we do take care to provide for the case that we get a NULL&n; *&t;pointer passed in.&n; */
DECL|function|get_device
r_struct
id|device
op_star
id|get_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|dev
ques
c_cond
id|to_dev
c_func
(paren
id|kobject_get
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;put_device - decrement reference count.&n; *&t;@dev:&t;device in question.&n; */
DECL|function|put_device
r_void
id|put_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|kobject_put
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_del - delete device from system.&n; *&t;@dev:&t;device.&n; *&n; *&t;This is the first part of the device unregistration &n; *&t;sequence. This removes the device from the lists we control&n; *&t;from here, has it removed from the other driver model &n; *&t;subsystems it was added to in device_add(), and removes it&n; *&t;from the kobject hierarchy.&n; *&n; *&t;NOTE: this should be called manually _iff_ device_add() was &n; *&t;also called manually.&n; */
DECL|function|device_del
r_void
id|device_del
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|device
op_star
id|parent
op_assign
id|dev-&gt;parent
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|list_del_init
c_func
(paren
op_amp
id|dev-&gt;node
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
multiline_comment|/* Notify the platform of the removal, in case they&n;&t; * need to do anything...&n;&t; */
r_if
c_cond
(paren
id|platform_notify_remove
)paren
id|platform_notify_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
id|bus_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|device_pm_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kobject_del
c_func
(paren
op_amp
id|dev-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|put_device
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_unregister - unregister device from system.&n; *&t;@dev:&t;device going away.&n; *&n; *&t;We do this in two parts, like we do device_register(). First,&n; *&t;we remove it from all the subsystems with device_del(), then&n; *&t;we decrement the reference count via put_device(). If that&n; *&t;is the final reference count, the device will be cleaned up&n; *&t;via device_release() above. Otherwise, the structure will &n; *&t;stick around until the final reference to the device is dropped.&n; */
DECL|function|device_unregister
r_void
id|device_unregister
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
l_string|&quot;DEV: Unregistering device. ID = &squot;%s&squot;&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|device_del
c_func
(paren
id|dev
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;device_for_each_child - device child iterator.&n; *&t;@dev:&t;parent struct device.&n; *&t;@data:&t;data for the callback.&n; *&t;@fn:&t;function to be called for each device.&n; *&n; *&t;Iterate over @dev&squot;s child devices, and call @fn for each,&n; *&t;passing it @data. &n; *&n; *&t;We check the return of @fn each time. If it returns anything&n; *&t;other than 0, we break out and return that value.&n; */
DECL|function|device_for_each_child
r_int
id|device_for_each_child
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|device
op_star
id|child
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|child
comma
op_amp
id|dev-&gt;children
comma
id|node
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|fn
c_func
(paren
id|child
comma
id|data
)paren
)paren
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
id|devices_subsys.rwsem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|device_find
r_struct
id|device
op_star
id|device_find
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|bus_type
op_star
id|bus
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
id|bus-&gt;devices
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|k
)paren
r_return
id|to_dev
c_func
(paren
id|k
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devices_init
r_int
id|__init
id|devices_init
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
id|devices_subsys
)paren
suffix:semicolon
)brace
DECL|variable|device_for_each_child
id|EXPORT_SYMBOL
c_func
(paren
id|device_for_each_child
)paren
suffix:semicolon
DECL|variable|device_initialize
id|EXPORT_SYMBOL
c_func
(paren
id|device_initialize
)paren
suffix:semicolon
DECL|variable|device_add
id|EXPORT_SYMBOL
c_func
(paren
id|device_add
)paren
suffix:semicolon
DECL|variable|device_register
id|EXPORT_SYMBOL
c_func
(paren
id|device_register
)paren
suffix:semicolon
DECL|variable|device_del
id|EXPORT_SYMBOL
c_func
(paren
id|device_del
)paren
suffix:semicolon
DECL|variable|device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|device_unregister
)paren
suffix:semicolon
DECL|variable|get_device
id|EXPORT_SYMBOL
c_func
(paren
id|get_device
)paren
suffix:semicolon
DECL|variable|put_device
id|EXPORT_SYMBOL
c_func
(paren
id|put_device
)paren
suffix:semicolon
DECL|variable|device_find
id|EXPORT_SYMBOL
c_func
(paren
id|device_find
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
