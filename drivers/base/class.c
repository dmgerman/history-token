multiline_comment|/*&n; * class.c - basic device class management&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|macro|to_class_attr
mdefine_line|#define to_class_attr(_attr) container_of(_attr,struct devclass_attribute,attr)
DECL|macro|to_class
mdefine_line|#define to_class(obj) container_of(obj,struct device_class,subsys.kset.kobj)
DECL|variable|devclass_sem
id|DECLARE_MUTEX
c_func
(paren
id|devclass_sem
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|devclass_attr_show
id|devclass_attr_show
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
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|class_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|class_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|devclass_attr_show
comma
dot
id|store
op_assign
id|devclass_attr_store
comma
)brace
suffix:semicolon
DECL|variable|ktype_devclass
r_static
r_struct
id|kobj_type
id|ktype_devclass
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|class_sysfs_ops
comma
)brace
suffix:semicolon
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
r_class
comma
op_amp
id|ktype_devclass
)paren
suffix:semicolon
DECL|function|devclass_dev_link
r_static
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
r_return
id|sysfs_create_link
c_func
(paren
op_amp
id|cls-&gt;devices.kobj
comma
op_amp
id|dev-&gt;kobj
comma
id|linkname
)paren
suffix:semicolon
)brace
DECL|function|devclass_dev_unlink
r_static
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
id|sysfs_remove_link
c_func
(paren
op_amp
id|cls-&gt;devices.kobj
comma
id|linkname
)paren
suffix:semicolon
)brace
DECL|function|devclass_drv_link
r_static
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
id|name
(braket
id|KOBJ_NAME_LEN
op_star
l_int|3
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|KOBJ_NAME_LEN
op_star
l_int|3
comma
l_string|&quot;%s:%s&quot;
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
r_return
id|sysfs_create_link
c_func
(paren
op_amp
id|drv-&gt;devclass-&gt;drivers.kobj
comma
op_amp
id|drv-&gt;kobj
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|devclass_drv_unlink
r_static
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
id|name
(braket
id|KOBJ_NAME_LEN
op_star
l_int|3
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|KOBJ_NAME_LEN
op_star
l_int|3
comma
l_string|&quot;%s:%s&quot;
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
r_return
id|sysfs_remove_link
c_func
(paren
op_amp
id|drv-&gt;devclass-&gt;drivers.kobj
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|devclass_create_file
r_int
id|devclass_create_file
c_func
(paren
r_struct
id|device_class
op_star
id|cls
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
id|cls
)paren
(brace
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|cls-&gt;subsys.kset.kobj
comma
op_amp
id|attr-&gt;attr
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
id|cls
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
id|cls
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|cls-&gt;subsys.kset.kobj
comma
op_amp
id|attr-&gt;attr
)paren
suffix:semicolon
)brace
DECL|function|devclass_add_driver
r_int
id|devclass_add_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|device_class
op_star
id|cls
op_assign
id|get_devclass
c_func
(paren
id|drv-&gt;devclass
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
id|cls
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class %s: adding driver %s:%s&bslash;n&quot;
comma
id|cls-&gt;name
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|error
op_assign
id|devclass_drv_link
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|list_add_tail
c_func
(paren
op_amp
id|drv-&gt;class_list
comma
op_amp
id|cls-&gt;drivers.list
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|devclass_remove_driver
r_void
id|devclass_remove_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|device_class
op_star
id|cls
op_assign
id|drv-&gt;devclass
suffix:semicolon
r_if
c_cond
(paren
id|cls
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class %s: removing driver %s:%s&bslash;n&quot;
comma
id|cls-&gt;name
comma
id|drv-&gt;bus-&gt;name
comma
id|drv-&gt;name
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|drv-&gt;class_list
)paren
suffix:semicolon
id|devclass_drv_unlink
c_func
(paren
id|drv
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_devclass
c_func
(paren
id|cls
)paren
suffix:semicolon
)brace
)brace
DECL|function|enum_device
r_static
r_void
id|enum_device
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
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|cls-&gt;devnum
op_increment
suffix:semicolon
id|dev-&gt;class_num
op_assign
id|val
suffix:semicolon
id|devclass_dev_link
c_func
(paren
id|cls
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|unenum_device
r_static
r_void
id|unenum_device
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
id|devclass_dev_unlink
c_func
(paren
id|cls
comma
id|dev
)paren
suffix:semicolon
id|dev-&gt;class_num
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;devclass_add_device - register device with device class&n; *&t;@dev:   device to be registered &n; *&n; *&t;This is called when a device is either registered with the &n; *&t;core, or after the a driver module is loaded and bound to&n; *&t;the device. &n; *&t;The class is determined by looking at @dev&squot;s driver, so one&n; *&t;way or another, it must be bound to something. Once the &n; *&t;class is determined, it&squot;s set to prevent against concurrent&n; *&t;calls for the same device stomping on each other. &n; *&n; *&t;/sbin/hotplug should be called once the device is added to &n; *&t;class and all the interfaces. &n; */
DECL|function|devclass_add_device
r_int
id|devclass_add_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|device_class
op_star
id|cls
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|devclass_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
)paren
(brace
id|cls
op_assign
id|get_devclass
c_func
(paren
id|dev-&gt;driver-&gt;devclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cls
)paren
r_goto
id|Done
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class %s: adding device %s&bslash;n&quot;
comma
id|cls-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;add_device
)paren
id|error
op_assign
id|cls
op_member_access_from_pointer
id|add_device
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
(brace
id|put_devclass
c_func
(paren
id|cls
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|enum_device
c_func
(paren
id|cls
comma
id|dev
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;class_list
comma
op_amp
id|cls-&gt;devices.list
)paren
suffix:semicolon
multiline_comment|/* notify userspace (call /sbin/hotplug) */
id|class_hotplug
(paren
id|dev
comma
l_string|&quot;add&quot;
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|interface_add_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|Done
suffix:colon
id|up
c_func
(paren
op_amp
id|devclass_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|devclass_remove_device
r_void
id|devclass_remove_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|device_class
op_star
id|cls
suffix:semicolon
id|down
c_func
(paren
op_amp
id|devclass_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
)paren
(brace
id|cls
op_assign
id|dev-&gt;driver-&gt;devclass
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cls
)paren
r_goto
id|Done
suffix:semicolon
id|interface_remove_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class %s: removing device %s&bslash;n&quot;
comma
id|cls-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|unenum_device
c_func
(paren
id|cls
comma
id|dev
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;class_list
)paren
suffix:semicolon
multiline_comment|/* notify userspace (call /sbin/hotplug) */
id|class_hotplug
(paren
id|dev
comma
l_string|&quot;remove&quot;
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|cls-&gt;subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;remove_device
)paren
id|cls
op_member_access_from_pointer
id|remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|put_devclass
c_func
(paren
id|cls
)paren
suffix:semicolon
)brace
id|Done
suffix:colon
id|up
c_func
(paren
op_amp
id|devclass_sem
)paren
suffix:semicolon
)brace
DECL|function|get_devclass
r_struct
id|device_class
op_star
id|get_devclass
c_func
(paren
r_struct
id|device_class
op_star
id|cls
)paren
(brace
r_return
id|cls
ques
c_cond
id|container_of
c_func
(paren
id|subsys_get
c_func
(paren
op_amp
id|cls-&gt;subsys
)paren
comma
r_struct
id|device_class
comma
id|subsys
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|put_devclass
r_void
id|put_devclass
c_func
(paren
r_struct
id|device_class
op_star
id|cls
)paren
(brace
id|subsys_put
c_func
(paren
op_amp
id|cls-&gt;subsys
)paren
suffix:semicolon
)brace
DECL|function|devclass_register
r_int
id|devclass_register
c_func
(paren
r_struct
id|device_class
op_star
id|cls
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;device class &squot;%s&squot;: registering&bslash;n&quot;
comma
id|cls-&gt;name
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|cls-&gt;subsys.kset.kobj.name
comma
id|cls-&gt;name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
id|subsys_set_kset
c_func
(paren
id|cls
comma
id|class_subsys
)paren
suffix:semicolon
id|subsystem_register
c_func
(paren
op_amp
id|cls-&gt;subsys
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|cls-&gt;devices.kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;devices&quot;
)paren
suffix:semicolon
id|cls-&gt;devices.subsys
op_assign
op_amp
id|cls-&gt;subsys
suffix:semicolon
id|kset_register
c_func
(paren
op_amp
id|cls-&gt;devices
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|cls-&gt;drivers.kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;drivers&quot;
)paren
suffix:semicolon
id|cls-&gt;drivers.subsys
op_assign
op_amp
id|cls-&gt;subsys
suffix:semicolon
id|kset_register
c_func
(paren
op_amp
id|cls-&gt;drivers
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devclass_unregister
r_void
id|devclass_unregister
c_func
(paren
r_struct
id|device_class
op_star
id|cls
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;device class &squot;%s&squot;: unregistering&bslash;n&quot;
comma
id|cls-&gt;name
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|cls-&gt;drivers
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|cls-&gt;devices
)paren
suffix:semicolon
id|subsystem_unregister
c_func
(paren
op_amp
id|cls-&gt;subsys
)paren
suffix:semicolon
)brace
DECL|function|class_subsys_init
r_static
r_int
id|__init
id|class_subsys_init
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
id|class_subsys
)paren
suffix:semicolon
)brace
DECL|variable|class_subsys_init
id|core_initcall
c_func
(paren
id|class_subsys_init
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
DECL|variable|devclass_register
id|EXPORT_SYMBOL
c_func
(paren
id|devclass_register
)paren
suffix:semicolon
DECL|variable|devclass_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|devclass_unregister
)paren
suffix:semicolon
DECL|variable|get_devclass
id|EXPORT_SYMBOL
c_func
(paren
id|get_devclass
)paren
suffix:semicolon
DECL|variable|put_devclass
id|EXPORT_SYMBOL
c_func
(paren
id|put_devclass
)paren
suffix:semicolon
eof
