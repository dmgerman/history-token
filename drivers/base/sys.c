multiline_comment|/*&n; * sys.c - pseudo-bus for system &squot;devices&squot; (cpus, PICs, timers, etc)&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; *               2002-3 Open Source Development Lab&n; *&n; * This file is released under the GPLv2&n; * &n; * This exports a &squot;system&squot; bus type. &n; * By default, a &squot;sys&squot; bus gets added to the root of the system. There will&n; * always be core system devices. Devices can use sys_device_register() to&n; * add themselves as children of the system bus.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
r_extern
r_struct
id|subsystem
id|devices_subsys
suffix:semicolon
DECL|macro|to_sysdev
mdefine_line|#define to_sysdev(k) container_of(k,struct sys_device,kobj)
DECL|macro|to_sysdev_attr
mdefine_line|#define to_sysdev_attr(a) container_of(a,struct sysdev_attribute,attr)
r_static
id|ssize_t
DECL|function|sysdev_show
id|sysdev_show
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
id|buffer
)paren
(brace
r_struct
id|sys_device
op_star
id|sysdev
op_assign
id|to_sysdev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|sysdev_attribute
op_star
id|sysdev_attr
op_assign
id|to_sysdev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sysdev_attr-&gt;show
)paren
r_return
id|sysdev_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|sysdev
comma
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|sysdev_store
id|sysdev_store
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
id|buffer
comma
r_int
id|count
)paren
(brace
r_struct
id|sys_device
op_star
id|sysdev
op_assign
id|to_sysdev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|sysdev_attribute
op_star
id|sysdev_attr
op_assign
id|to_sysdev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sysdev_attr-&gt;store
)paren
r_return
id|sysdev_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|sysdev
comma
id|buffer
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysfs_ops
r_static
r_struct
id|sysfs_ops
id|sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|sysdev_show
comma
dot
id|store
op_assign
id|sysdev_store
comma
)brace
suffix:semicolon
DECL|variable|ktype_sysdev
r_static
r_struct
id|kobj_type
id|ktype_sysdev
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|sysfs_ops
comma
)brace
suffix:semicolon
DECL|function|sysdev_create_file
r_int
id|sysdev_create_file
c_func
(paren
r_struct
id|sys_device
op_star
id|s
comma
r_struct
id|sysdev_attribute
op_star
id|a
)paren
(brace
r_return
id|sysfs_create_file
c_func
(paren
op_amp
id|s-&gt;kobj
comma
op_amp
id|a-&gt;attr
)paren
suffix:semicolon
)brace
DECL|function|sysdev_remove_file
r_void
id|sysdev_remove_file
c_func
(paren
r_struct
id|sys_device
op_star
id|s
comma
r_struct
id|sysdev_attribute
op_star
id|a
)paren
(brace
id|sysfs_remove_file
c_func
(paren
op_amp
id|s-&gt;kobj
comma
op_amp
id|a-&gt;attr
)paren
suffix:semicolon
)brace
DECL|variable|sysdev_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|sysdev_create_file
)paren
suffix:semicolon
DECL|variable|sysdev_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|sysdev_remove_file
)paren
suffix:semicolon
multiline_comment|/* &n; * declare system_subsys &n; */
id|decl_subsys
c_func
(paren
id|system
comma
op_amp
id|ktype_sysdev
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|sysdev_class_register
r_int
id|sysdev_class_register
c_func
(paren
r_struct
id|sysdev_class
op_star
id|cls
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Registering sysdev class &squot;%s&squot;&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cls-&gt;drivers
)paren
suffix:semicolon
id|cls-&gt;kset.subsys
op_assign
op_amp
id|system_subsys
suffix:semicolon
id|kset_set_kset_s
c_func
(paren
id|cls
comma
id|system_subsys
)paren
suffix:semicolon
r_return
id|kset_register
c_func
(paren
op_amp
id|cls-&gt;kset
)paren
suffix:semicolon
)brace
DECL|function|sysdev_class_unregister
r_void
id|sysdev_class_unregister
c_func
(paren
r_struct
id|sysdev_class
op_star
id|cls
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Unregistering sysdev class &squot;%s&squot;&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|cls-&gt;kset
)paren
suffix:semicolon
)brace
DECL|variable|sysdev_class_register
id|EXPORT_SYMBOL
c_func
(paren
id|sysdev_class_register
)paren
suffix:semicolon
DECL|variable|sysdev_class_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|sysdev_class_unregister
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|global_drivers
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;sysdev_driver_register - Register auxillary driver&n; * &t;@cls:&t;Device class driver belongs to.&n; *&t;@drv:&t;Driver.&n; *&n; *&t;If @cls is valid, then @drv is inserted into @cls-&gt;drivers to be &n; *&t;called on each operation on devices of that class. The refcount&n; *&t;of @cls is incremented. &n; *&t;Otherwise, @drv is inserted into global_drivers, and called for &n; *&t;each device.&n; */
DECL|function|sysdev_driver_register
r_int
id|sysdev_driver_register
c_func
(paren
r_struct
id|sysdev_class
op_star
id|cls
comma
r_struct
id|sysdev_driver
op_star
id|drv
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cls
op_logical_and
id|kset_get
c_func
(paren
op_amp
id|cls-&gt;kset
)paren
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|drv-&gt;entry
comma
op_amp
id|cls-&gt;drivers
)paren
suffix:semicolon
multiline_comment|/* If devices of this class already exist, tell the driver */
r_if
c_cond
(paren
id|drv-&gt;add
)paren
(brace
r_struct
id|sys_device
op_star
id|dev
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|cls-&gt;kset.list
comma
id|kobj.entry
)paren
id|drv
op_member_access_from_pointer
id|add
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_else
id|list_add_tail
c_func
(paren
op_amp
id|drv-&gt;entry
comma
op_amp
id|global_drivers
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysdev_driver_unregister - Remove an auxillary driver.&n; *&t;@cls:&t;Class driver belongs to.&n; *&t;@drv:&t;Driver.&n; */
DECL|function|sysdev_driver_unregister
r_void
id|sysdev_driver_unregister
c_func
(paren
r_struct
id|sysdev_class
op_star
id|cls
comma
r_struct
id|sysdev_driver
op_star
id|drv
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drv-&gt;entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cls
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;remove
)paren
(brace
r_struct
id|sys_device
op_star
id|dev
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|cls-&gt;kset.list
comma
id|kobj.entry
)paren
id|drv
op_member_access_from_pointer
id|remove
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|kset_put
c_func
(paren
op_amp
id|cls-&gt;kset
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sys_device_register - add a system device to the tree&n; *&t;@sysdev:&t;device in question&n; *&n; */
DECL|function|sys_device_register
r_int
id|sys_device_register
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|sysdev_class
op_star
id|cls
op_assign
id|sysdev-&gt;cls
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cls
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Make sure the kset is set */
id|sysdev-&gt;kobj.kset
op_assign
op_amp
id|cls-&gt;kset
suffix:semicolon
multiline_comment|/* But make sure we point to the right type for sysfs translation */
id|sysdev-&gt;kobj.ktype
op_assign
op_amp
id|ktype_sysdev
suffix:semicolon
id|kobject_set_name
c_func
(paren
op_amp
id|sysdev-&gt;kobj
comma
l_string|&quot;%s%d&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
comma
id|sysdev-&gt;id
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Registering sys device &squot;%s&squot;&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* Register the object */
id|error
op_assign
id|kobject_register
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_struct
id|sysdev_driver
op_star
id|drv
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
multiline_comment|/* Generic notification is implicit, because it&squot;s that &n;&t;&t; * code that should have called us. &n;&t;&t; */
multiline_comment|/* Notify global drivers */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|global_drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;add
)paren
id|drv
op_member_access_from_pointer
id|add
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
multiline_comment|/* Notify class auxillary drivers */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|cls-&gt;drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;add
)paren
id|drv
op_member_access_from_pointer
id|add
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_device_unregister
r_void
id|sys_device_unregister
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
)paren
(brace
r_struct
id|sysdev_driver
op_star
id|drv
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|global_drivers
comma
id|entry
)paren
(brace
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
id|sysdev
)paren
suffix:semicolon
)brace
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|sysdev-&gt;cls-&gt;drivers
comma
id|entry
)paren
(brace
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
id|sysdev
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
id|kobject_unregister
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysdev_shutdown - Shut down all system devices.&n; *&n; *&t;Loop over each class of system devices, and the devices in each&n; *&t;of those classes. For each device, we call the shutdown method for&n; *&t;each driver registered for the device - the globals, the auxillaries,&n; *&t;and the class driver. &n; *&n; *&t;Note: The list is iterated in reverse order, so that we shut down&n; *&t;child devices before we shut down thier parents. The list ordering&n; *&t;is guaranteed by virtue of the fact that child devices are registered&n; *&t;after their parents. &n; */
DECL|function|sysdev_shutdown
r_void
id|sysdev_shutdown
c_func
(paren
r_void
)paren
(brace
r_struct
id|sysdev_class
op_star
id|cls
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Shutting Down System Devices&bslash;n&quot;
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each_entry_reverse
c_func
(paren
id|cls
comma
op_amp
id|system_subsys.kset.list
comma
id|kset.kobj.entry
)paren
(brace
r_struct
id|sys_device
op_star
id|sysdev
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Shutting down type &squot;%s&squot;:&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|sysdev
comma
op_amp
id|cls-&gt;kset.list
comma
id|kobj.entry
)paren
(brace
r_struct
id|sysdev_driver
op_star
id|drv
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; %s&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* Call global drivers first. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|global_drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;shutdown
)paren
id|drv
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
multiline_comment|/* Call auxillary drivers next. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|cls-&gt;drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;shutdown
)paren
id|drv
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
multiline_comment|/* Now call the generic one */
r_if
c_cond
(paren
id|cls-&gt;shutdown
)paren
id|cls
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|system_subsys.rwsem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysdev_suspend - Suspend all system devices.&n; *&t;@state:&t;&t;Power state to enter.&n; *&n; *&t;We perform an almost identical operation as sys_device_shutdown()&n; *&t;above, though calling -&gt;suspend() instead. Interrupts are disabled&n; *&t;when this called. Devices are responsible for both saving state and&n; *&t;quiescing or powering down the device. &n; *&n; *&t;This is only called by the device PM core, so we let them handle&n; *&t;all synchronization.&n; */
DECL|function|sysdev_suspend
r_int
id|sysdev_suspend
c_func
(paren
id|u32
id|state
)paren
(brace
r_struct
id|sysdev_class
op_star
id|cls
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Suspending System Devices&bslash;n&quot;
)paren
suffix:semicolon
id|list_for_each_entry_reverse
c_func
(paren
id|cls
comma
op_amp
id|system_subsys.kset.list
comma
id|kset.kobj.entry
)paren
(brace
r_struct
id|sys_device
op_star
id|sysdev
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Suspending type &squot;%s&squot;:&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|sysdev
comma
op_amp
id|cls-&gt;kset.list
comma
id|kobj.entry
)paren
(brace
r_struct
id|sysdev_driver
op_star
id|drv
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; %s&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* Call global drivers first. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|global_drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;suspend
)paren
id|drv
op_member_access_from_pointer
id|suspend
c_func
(paren
id|sysdev
comma
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* Call auxillary drivers next. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|cls-&gt;drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;suspend
)paren
id|drv
op_member_access_from_pointer
id|suspend
c_func
(paren
id|sysdev
comma
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* Now call the generic one */
r_if
c_cond
(paren
id|cls-&gt;suspend
)paren
id|cls
op_member_access_from_pointer
id|suspend
c_func
(paren
id|sysdev
comma
id|state
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysdev_resume - Bring system devices back to life.&n; *&n; *&t;Similar to sys_device_suspend(), but we iterate the list forwards&n; *&t;to guarantee that parent devices are resumed before their children.&n; *&n; *&t;Note: Interrupts are disabled when called. &n; */
DECL|function|sysdev_resume
r_int
id|sysdev_resume
c_func
(paren
r_void
)paren
(brace
r_struct
id|sysdev_class
op_star
id|cls
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Resuming System Devices&bslash;n&quot;
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cls
comma
op_amp
id|system_subsys.kset.list
comma
id|kset.kobj.entry
)paren
(brace
r_struct
id|sys_device
op_star
id|sysdev
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Resuming type &squot;%s&squot;:&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|cls-&gt;kset.kobj
)paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|sysdev
comma
op_amp
id|cls-&gt;kset.list
comma
id|kobj.entry
)paren
(brace
r_struct
id|sysdev_driver
op_star
id|drv
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; %s&bslash;n&quot;
comma
id|kobject_name
c_func
(paren
op_amp
id|sysdev-&gt;kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* First, call the class-specific one */
r_if
c_cond
(paren
id|cls-&gt;resume
)paren
id|cls
op_member_access_from_pointer
id|resume
c_func
(paren
id|sysdev
)paren
suffix:semicolon
multiline_comment|/* Call auxillary drivers next. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|cls-&gt;drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;resume
)paren
id|drv
op_member_access_from_pointer
id|resume
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
multiline_comment|/* Call global drivers. */
id|list_for_each_entry
c_func
(paren
id|drv
comma
op_amp
id|global_drivers
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;resume
)paren
id|drv
op_member_access_from_pointer
id|resume
c_func
(paren
id|sysdev
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_bus_init
r_int
id|__init
id|sys_bus_init
c_func
(paren
r_void
)paren
(brace
id|system_subsys.kset.kobj.parent
op_assign
op_amp
id|devices_subsys.kset.kobj
suffix:semicolon
r_return
id|subsystem_register
c_func
(paren
op_amp
id|system_subsys
)paren
suffix:semicolon
)brace
DECL|variable|sys_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|sys_device_register
)paren
suffix:semicolon
DECL|variable|sys_device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|sys_device_unregister
)paren
suffix:semicolon
eof
