multiline_comment|/*&n; * class.c - basic device class management&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; * Copyright (c) 2003-2004 Greg Kroah-Hartman&n; * Copyright (c) 2003-2004 IBM Corp.&n; * &n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|macro|to_class_attr
mdefine_line|#define to_class_attr(_attr) container_of(_attr,struct class_attribute,attr)
DECL|macro|to_class
mdefine_line|#define to_class(obj) container_of(obj,struct class,subsys.kset.kobj)
r_static
id|ssize_t
DECL|function|class_attr_show
id|class_attr_show
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
id|class_attribute
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
r_class
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
DECL|function|class_attr_store
id|class_attr_store
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
id|class_attribute
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
r_class
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
DECL|function|class_release
r_static
r_void
id|class_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
r_class
op_star
r_class
op_assign
id|to_class
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;class &squot;%s&squot;: release.&bslash;n&quot;
comma
r_class
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
r_class
op_member_access_from_pointer
id|class_release
)paren
r_class
op_member_access_from_pointer
id|class_release
c_func
(paren
r_class
)paren
suffix:semicolon
r_else
id|pr_debug
c_func
(paren
l_string|&quot;class &squot;%s&squot; does not have a release() function, &quot;
l_string|&quot;be careful&bslash;n&quot;
comma
r_class
op_member_access_from_pointer
id|name
)paren
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
id|class_attr_show
comma
dot
id|store
op_assign
id|class_attr_store
comma
)brace
suffix:semicolon
DECL|variable|ktype_class
r_static
r_struct
id|kobj_type
id|ktype_class
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|class_sysfs_ops
comma
dot
id|release
op_assign
id|class_release
comma
)brace
suffix:semicolon
multiline_comment|/* Hotplug events for classes go to the class_obj subsys */
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
r_class
comma
op_amp
id|ktype_class
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|class_create_file
r_int
id|class_create_file
c_func
(paren
r_struct
r_class
op_star
id|cls
comma
r_const
r_struct
id|class_attribute
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
DECL|function|class_remove_file
r_void
id|class_remove_file
c_func
(paren
r_struct
r_class
op_star
id|cls
comma
r_const
r_struct
id|class_attribute
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
DECL|function|class_get
r_struct
r_class
op_star
id|class_get
c_func
(paren
r_struct
r_class
op_star
id|cls
)paren
(brace
r_if
c_cond
(paren
id|cls
)paren
r_return
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
r_class
comma
id|subsys
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|class_put
r_void
id|class_put
c_func
(paren
r_struct
r_class
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
DECL|function|add_class_attrs
r_static
r_int
id|add_class_attrs
c_func
(paren
r_struct
r_class
op_star
id|cls
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;class_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attr_name
c_func
(paren
id|cls-&gt;class_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|class_create_file
c_func
(paren
id|cls
comma
op_amp
id|cls-&gt;class_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|Err
suffix:semicolon
)brace
)brace
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
id|Err
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
id|class_remove_file
c_func
(paren
id|cls
comma
op_amp
id|cls-&gt;class_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|function|remove_class_attrs
r_static
r_void
id|remove_class_attrs
c_func
(paren
r_struct
r_class
op_star
id|cls
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;class_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attr_name
c_func
(paren
id|cls-&gt;class_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
id|class_remove_file
c_func
(paren
id|cls
comma
op_amp
id|cls-&gt;class_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|class_register
r_int
id|class_register
c_func
(paren
r_struct
r_class
op_star
id|cls
)paren
(brace
r_int
id|error
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class &squot;%s&squot;: registering&bslash;n&quot;
comma
id|cls-&gt;name
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cls-&gt;children
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cls-&gt;interfaces
)paren
suffix:semicolon
id|error
op_assign
id|kobject_set_name
c_func
(paren
op_amp
id|cls-&gt;subsys.kset.kobj
comma
id|cls-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|subsys_set_kset
c_func
(paren
id|cls
comma
id|class_subsys
)paren
suffix:semicolon
id|error
op_assign
id|subsystem_register
c_func
(paren
op_amp
id|cls-&gt;subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|add_class_attrs
c_func
(paren
id|class_get
c_func
(paren
id|cls
)paren
)paren
suffix:semicolon
id|class_put
c_func
(paren
id|cls
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|class_unregister
r_void
id|class_unregister
c_func
(paren
r_struct
r_class
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
id|remove_class_attrs
c_func
(paren
id|cls
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
multiline_comment|/* Class Device Stuff */
DECL|function|class_device_create_file
r_int
id|class_device_create_file
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_const
r_struct
id|class_device_attribute
op_star
id|attr
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|class_dev
)paren
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|attr-&gt;attr
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|class_device_remove_file
r_void
id|class_device_remove_file
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_const
r_struct
id|class_device_attribute
op_star
id|attr
)paren
(brace
r_if
c_cond
(paren
id|class_dev
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|attr-&gt;attr
)paren
suffix:semicolon
)brace
DECL|function|class_device_dev_link
r_static
r_int
id|class_device_dev_link
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_if
c_cond
(paren
id|class_dev-&gt;dev
)paren
r_return
id|sysfs_create_link
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|class_dev-&gt;dev-&gt;kobj
comma
l_string|&quot;device&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|class_device_dev_unlink
r_static
r_void
id|class_device_dev_unlink
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
l_string|&quot;device&quot;
)paren
suffix:semicolon
)brace
DECL|function|class_device_driver_link
r_static
r_int
id|class_device_driver_link
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|class_dev-&gt;dev
)paren
op_logical_and
(paren
id|class_dev-&gt;dev-&gt;driver
)paren
)paren
r_return
id|sysfs_create_link
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|class_dev-&gt;dev-&gt;driver-&gt;kobj
comma
l_string|&quot;driver&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|class_device_driver_unlink
r_static
r_void
id|class_device_driver_unlink
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
l_string|&quot;driver&quot;
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|class_device_attr_show
id|class_device_attr_show
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
id|class_device_attribute
op_star
id|class_dev_attr
op_assign
id|to_class_dev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|class_device
op_star
id|cd
op_assign
id|to_class_dev
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
id|class_dev_attr-&gt;show
)paren
id|ret
op_assign
id|class_dev_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|cd
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
DECL|function|class_device_attr_store
id|class_device_attr_store
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
id|class_device_attribute
op_star
id|class_dev_attr
op_assign
id|to_class_dev_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|class_device
op_star
id|cd
op_assign
id|to_class_dev
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
id|class_dev_attr-&gt;store
)paren
id|ret
op_assign
id|class_dev_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|cd
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
DECL|variable|class_dev_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|class_dev_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|class_device_attr_show
comma
dot
id|store
op_assign
id|class_device_attr_store
comma
)brace
suffix:semicolon
DECL|function|class_dev_release
r_static
r_void
id|class_dev_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|class_device
op_star
id|cd
op_assign
id|to_class_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
r_class
op_star
id|cls
op_assign
id|cd
op_member_access_from_pointer
r_class
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;device class &squot;%s&squot;: release.&bslash;n&quot;
comma
id|cd-&gt;class_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;release
)paren
id|cls
op_member_access_from_pointer
id|release
c_func
(paren
id|cd
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Device class &squot;%s&squot; does not have a release() function, &quot;
l_string|&quot;it is broken and must be fixed.&bslash;n&quot;
comma
id|cd-&gt;class_id
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
DECL|variable|ktype_class_device
r_static
r_struct
id|kobj_type
id|ktype_class_device
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|class_dev_sysfs_ops
comma
dot
id|release
op_assign
id|class_dev_release
comma
)brace
suffix:semicolon
DECL|function|class_hotplug_filter
r_static
r_int
id|class_hotplug_filter
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
id|ktype_class_device
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
op_assign
id|to_class_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_dev
op_member_access_from_pointer
r_class
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|class_hotplug_name
r_static
r_char
op_star
id|class_hotplug_name
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
id|class_device
op_star
id|class_dev
op_assign
id|to_class_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_return
id|class_dev
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|name
suffix:semicolon
)brace
DECL|function|class_hotplug
r_static
r_int
id|class_hotplug
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
id|class_device
op_star
id|class_dev
op_assign
id|to_class_dev
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
id|pr_debug
c_func
(paren
l_string|&quot;%s - name = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|class_dev-&gt;class_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_dev
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|hotplug
)paren
(brace
multiline_comment|/* have the bus specific function add its stuff */
id|retval
op_assign
id|class_dev
op_member_access_from_pointer
r_class
op_member_access_from_pointer
id|hotplug
(paren
id|class_dev
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
DECL|variable|class_hotplug_ops
r_static
r_struct
id|kset_hotplug_ops
id|class_hotplug_ops
op_assign
(brace
dot
id|filter
op_assign
id|class_hotplug_filter
comma
dot
id|name
op_assign
id|class_hotplug_name
comma
dot
id|hotplug
op_assign
id|class_hotplug
comma
)brace
suffix:semicolon
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
id|class_obj
comma
op_amp
id|ktype_class_device
comma
op_amp
id|class_hotplug_ops
)paren
suffix:semicolon
DECL|function|class_device_add_attrs
r_static
r_int
id|class_device_add_attrs
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
r_class
op_star
id|cls
op_assign
id|cd
op_member_access_from_pointer
r_class
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;class_dev_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attr_name
c_func
(paren
id|cls-&gt;class_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|class_device_create_file
c_func
(paren
id|cd
comma
op_amp
id|cls-&gt;class_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|Err
suffix:semicolon
)brace
)brace
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
id|Err
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
id|class_device_remove_file
c_func
(paren
id|cd
comma
op_amp
id|cls-&gt;class_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|function|class_device_remove_attrs
r_static
r_void
id|class_device_remove_attrs
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
r_class
op_star
id|cls
op_assign
id|cd
op_member_access_from_pointer
r_class
suffix:semicolon
r_if
c_cond
(paren
id|cls-&gt;class_dev_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attr_name
c_func
(paren
id|cls-&gt;class_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
id|class_device_remove_file
c_func
(paren
id|cd
comma
op_amp
id|cls-&gt;class_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|class_device_initialize
r_void
id|class_device_initialize
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|kobj_set_kset_s
c_func
(paren
id|class_dev
comma
id|class_obj_subsys
)paren
suffix:semicolon
id|kobject_init
c_func
(paren
op_amp
id|class_dev-&gt;kobj
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|class_dev-&gt;node
)paren
suffix:semicolon
)brace
DECL|function|class_device_add
r_int
id|class_device_add
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
r_class
op_star
id|parent
suffix:semicolon
r_struct
id|class_interface
op_star
id|class_intf
suffix:semicolon
r_int
id|error
suffix:semicolon
id|class_dev
op_assign
id|class_device_get
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|class_dev
op_logical_or
op_logical_neg
id|strlen
c_func
(paren
id|class_dev-&gt;class_id
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|parent
op_assign
id|class_get
c_func
(paren
id|class_dev
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;CLASS: registering class device: ID = &squot;%s&squot;&bslash;n&quot;
comma
id|class_dev-&gt;class_id
)paren
suffix:semicolon
multiline_comment|/* first, register with generic layer. */
id|kobject_set_name
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
id|class_dev-&gt;class_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|class_dev-&gt;kobj.parent
op_assign
op_amp
id|parent-&gt;subsys.kset.kobj
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
id|class_dev-&gt;kobj
)paren
)paren
)paren
r_goto
id|register_done
suffix:semicolon
multiline_comment|/* now take care of our own registration */
r_if
c_cond
(paren
id|parent
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|class_dev-&gt;node
comma
op_amp
id|parent-&gt;children
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|class_intf
comma
op_amp
id|parent-&gt;interfaces
comma
id|node
)paren
r_if
c_cond
(paren
id|class_intf-&gt;add
)paren
id|class_intf
op_member_access_from_pointer
id|add
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
)brace
id|class_device_add_attrs
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_dev_link
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_driver_link
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|register_done
suffix:colon
r_if
c_cond
(paren
id|error
op_logical_and
id|parent
)paren
id|class_put
c_func
(paren
id|parent
)paren
suffix:semicolon
id|class_device_put
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|class_device_register
r_int
id|class_device_register
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|class_device_initialize
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|class_device_add
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
DECL|function|class_device_del
r_void
id|class_device_del
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
r_class
op_star
id|parent
op_assign
id|class_dev
op_member_access_from_pointer
r_class
suffix:semicolon
r_struct
id|class_interface
op_star
id|class_intf
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|class_dev-&gt;node
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|class_intf
comma
op_amp
id|parent-&gt;interfaces
comma
id|node
)paren
r_if
c_cond
(paren
id|class_intf-&gt;remove
)paren
id|class_intf
op_member_access_from_pointer
id|remove
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
)brace
id|class_device_dev_unlink
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_driver_unlink
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_remove_attrs
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|kobject_del
c_func
(paren
op_amp
id|class_dev-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|class_put
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|function|class_device_unregister
r_void
id|class_device_unregister
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;CLASS: Unregistering class device. ID = &squot;%s&squot;&bslash;n&quot;
comma
id|class_dev-&gt;class_id
)paren
suffix:semicolon
id|class_device_del
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_put
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
DECL|function|class_device_rename
r_int
id|class_device_rename
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_char
op_star
id|new_name
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|class_dev
op_assign
id|class_device_get
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|class_dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;CLASS: renaming &squot;%s&squot; to &squot;%s&squot;&bslash;n&quot;
comma
id|class_dev-&gt;class_id
comma
id|new_name
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|class_dev-&gt;class_id
comma
id|new_name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
id|error
op_assign
id|kobject_rename
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
id|new_name
)paren
suffix:semicolon
id|class_device_put
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|class_device_get
r_struct
id|class_device
op_star
id|class_device_get
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_if
c_cond
(paren
id|class_dev
)paren
r_return
id|to_class_dev
c_func
(paren
id|kobject_get
c_func
(paren
op_amp
id|class_dev-&gt;kobj
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|class_device_put
r_void
id|class_device_put
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|kobject_put
c_func
(paren
op_amp
id|class_dev-&gt;kobj
)paren
suffix:semicolon
)brace
DECL|function|class_interface_register
r_int
id|class_interface_register
c_func
(paren
r_struct
id|class_interface
op_star
id|class_intf
)paren
(brace
r_struct
r_class
op_star
id|parent
suffix:semicolon
r_struct
id|class_device
op_star
id|class_dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|class_intf
op_logical_or
op_logical_neg
id|class_intf
op_member_access_from_pointer
r_class
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|parent
op_assign
id|class_get
c_func
(paren
id|class_intf
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|class_intf-&gt;node
comma
op_amp
id|parent-&gt;interfaces
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_intf-&gt;add
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|class_dev
comma
op_amp
id|parent-&gt;children
comma
id|node
)paren
id|class_intf
op_member_access_from_pointer
id|add
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|class_interface_unregister
r_void
id|class_interface_unregister
c_func
(paren
r_struct
id|class_interface
op_star
id|class_intf
)paren
(brace
r_struct
r_class
op_star
id|parent
op_assign
id|class_intf
op_member_access_from_pointer
r_class
suffix:semicolon
r_struct
id|class_device
op_star
id|class_dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
r_return
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|class_intf-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_intf-&gt;remove
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|class_dev
comma
op_amp
id|parent-&gt;children
comma
id|node
)paren
id|class_intf
op_member_access_from_pointer
id|remove
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|parent-&gt;subsys.rwsem
)paren
suffix:semicolon
id|class_put
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|function|classes_init
r_int
id|__init
id|classes_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|subsystem_register
c_func
(paren
op_amp
id|class_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* ick, this is ugly, the things we go through to keep from showing up&n;&t; * in sysfs... */
id|subsystem_init
c_func
(paren
op_amp
id|class_obj_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|class_obj_subsys.kset.subsys
)paren
id|class_obj_subsys.kset.subsys
op_assign
op_amp
id|class_obj_subsys
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|class_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|class_create_file
)paren
suffix:semicolon
DECL|variable|class_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|class_remove_file
)paren
suffix:semicolon
DECL|variable|class_register
id|EXPORT_SYMBOL
c_func
(paren
id|class_register
)paren
suffix:semicolon
DECL|variable|class_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|class_unregister
)paren
suffix:semicolon
DECL|variable|class_get
id|EXPORT_SYMBOL
c_func
(paren
id|class_get
)paren
suffix:semicolon
DECL|variable|class_put
id|EXPORT_SYMBOL
c_func
(paren
id|class_put
)paren
suffix:semicolon
DECL|variable|class_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_register
)paren
suffix:semicolon
DECL|variable|class_device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_unregister
)paren
suffix:semicolon
DECL|variable|class_device_initialize
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_initialize
)paren
suffix:semicolon
DECL|variable|class_device_add
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_add
)paren
suffix:semicolon
DECL|variable|class_device_del
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_del
)paren
suffix:semicolon
DECL|variable|class_device_get
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_get
)paren
suffix:semicolon
DECL|variable|class_device_put
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_put
)paren
suffix:semicolon
DECL|variable|class_device_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_create_file
)paren
suffix:semicolon
DECL|variable|class_device_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|class_device_remove_file
)paren
suffix:semicolon
DECL|variable|class_interface_register
id|EXPORT_SYMBOL
c_func
(paren
id|class_interface_register
)paren
suffix:semicolon
DECL|variable|class_interface_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|class_interface_unregister
)paren
suffix:semicolon
eof
