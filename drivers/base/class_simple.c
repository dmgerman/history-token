multiline_comment|/*&n; * class_simple.c - a &quot;simple&quot; interface for classes for simple char devices.&n; *&n; * Copyright (c) 2003-2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (c) 2003-2004 IBM Corp.&n; *&n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/err.h&gt;
DECL|struct|class_simple
r_struct
id|class_simple
(brace
DECL|member|attr
r_struct
id|class_device_attribute
id|attr
suffix:semicolon
DECL|member|class
r_struct
r_class
r_class
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_class_simple
mdefine_line|#define to_class_simple(d) container_of(d, struct class_simple, class)
DECL|struct|simple_dev
r_struct
id|simple_dev
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_simple_dev
mdefine_line|#define to_simple_dev(d) container_of(d, struct simple_dev, class_dev)
r_static
id|LIST_HEAD
c_func
(paren
id|simple_dev_list
)paren
suffix:semicolon
DECL|variable|simple_dev_list_lock
r_static
id|spinlock_t
id|simple_dev_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|release_simple_dev
r_static
r_void
id|release_simple_dev
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|simple_dev
op_star
id|s_dev
op_assign
id|to_simple_dev
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s_dev
)paren
suffix:semicolon
)brace
DECL|function|show_dev
r_static
id|ssize_t
id|show_dev
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|simple_dev
op_star
id|s_dev
op_assign
id|to_simple_dev
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|print_dev_t
c_func
(paren
id|buf
comma
id|s_dev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|class_simple_release
r_static
r_void
id|class_simple_release
c_func
(paren
r_struct
r_class
op_star
r_class
)paren
(brace
r_struct
id|class_simple
op_star
id|cs
op_assign
id|to_class_simple
c_func
(paren
r_class
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * class_simple_create - create a struct class_simple structure&n; * @owner: pointer to the module that is to &quot;own&quot; this struct class_simple&n; * @name: pointer to a string for the name of this class.&n; *&n; * This is used to create a struct class_simple pointer that can then be used&n; * in calls to class_simple_device_add().  This is used when you do not wish to&n; * create a full blown class support for a type of char devices.&n; *&n; * Note, the pointer created here is to be destroyed when finished by making a&n; * call to class_simple_destroy().&n; */
DECL|function|class_simple_create
r_struct
id|class_simple
op_star
id|class_simple_create
c_func
(paren
r_struct
id|module
op_star
id|owner
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|class_simple
op_star
id|cs
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|cs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cs
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memset
c_func
(paren
id|cs
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|cs
)paren
)paren
suffix:semicolon
id|cs
op_member_access_from_pointer
r_class
dot
id|name
op_assign
id|name
suffix:semicolon
id|cs
op_member_access_from_pointer
r_class
dot
id|class_release
op_assign
id|class_simple_release
suffix:semicolon
id|cs
op_member_access_from_pointer
r_class
dot
id|release
op_assign
id|release_simple_dev
suffix:semicolon
id|cs-&gt;attr.attr.name
op_assign
l_string|&quot;dev&quot;
suffix:semicolon
id|cs-&gt;attr.attr.mode
op_assign
id|S_IRUGO
suffix:semicolon
id|cs-&gt;attr.attr.owner
op_assign
id|owner
suffix:semicolon
id|cs-&gt;attr.show
op_assign
id|show_dev
suffix:semicolon
id|cs-&gt;attr.store
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
id|class_register
c_func
(paren
op_amp
id|cs
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error
suffix:semicolon
r_return
id|cs
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|retval
)paren
suffix:semicolon
)brace
DECL|variable|class_simple_create
id|EXPORT_SYMBOL
c_func
(paren
id|class_simple_create
)paren
suffix:semicolon
multiline_comment|/**&n; * class_simple_destroy - destroys a struct class_simple structure&n; * @cs: pointer to the struct class_simple that is to be destroyed&n; *&n; * Note, the pointer to be destroyed must have been created with a call to&n; * class_simple_create().&n; */
DECL|function|class_simple_destroy
r_void
id|class_simple_destroy
c_func
(paren
r_struct
id|class_simple
op_star
id|cs
)paren
(brace
r_if
c_cond
(paren
(paren
id|cs
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|IS_ERR
c_func
(paren
id|cs
)paren
)paren
)paren
r_return
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|cs
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
)brace
DECL|variable|class_simple_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|class_simple_destroy
)paren
suffix:semicolon
multiline_comment|/**&n; * class_simple_device_add - adds a class device to sysfs for a character driver&n; * @cs: pointer to the struct class_simple that this device should be registered to.&n; * @dev: the dev_t for the device to be added.&n; * @device: a pointer to a struct device that is assiociated with this class device.&n; * @fmt: string for the class device&squot;s name&n; *&n; * This function can be used by simple char device classes that do not&n; * implement their own class device registration.  A struct class_device will&n; * be created in sysfs, registered to the specified class.  A &quot;dev&quot; file will&n; * be created, showing the dev_t for the device.  The pointer to the struct&n; * class_device will be returned from the call.  Any further sysfs files that&n; * might be required can be created using this pointer.&n; * Note: the struct class_device passed to this function must have previously been&n; * created with a call to class_simple_create().&n; */
DECL|function|class_simple_device_add
r_struct
id|class_device
op_star
id|class_simple_device_add
c_func
(paren
r_struct
id|class_simple
op_star
id|cs
comma
id|dev_t
id|dev
comma
r_struct
id|device
op_star
id|device
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_struct
id|simple_dev
op_star
id|s_dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|IS_ERR
c_func
(paren
id|cs
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|s_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s_dev
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|memset
c_func
(paren
id|s_dev
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|s_dev
)paren
)paren
suffix:semicolon
id|s_dev-&gt;dev
op_assign
id|dev
suffix:semicolon
id|s_dev-&gt;class_dev.dev
op_assign
id|device
suffix:semicolon
id|s_dev-&gt;class_dev
dot
r_class
op_assign
op_amp
id|cs
op_member_access_from_pointer
r_class
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|s_dev-&gt;class_dev.class_id
comma
id|BUS_ID_SIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|retval
op_assign
id|class_device_register
c_func
(paren
op_amp
id|s_dev-&gt;class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error
suffix:semicolon
id|class_device_create_file
c_func
(paren
op_amp
id|s_dev-&gt;class_dev
comma
op_amp
id|cs-&gt;attr
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|simple_dev_list_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|s_dev-&gt;node
comma
op_amp
id|simple_dev_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|simple_dev_list_lock
)paren
suffix:semicolon
r_return
op_amp
id|s_dev-&gt;class_dev
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|s_dev
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|retval
)paren
suffix:semicolon
)brace
DECL|variable|class_simple_device_add
id|EXPORT_SYMBOL
c_func
(paren
id|class_simple_device_add
)paren
suffix:semicolon
multiline_comment|/**&n; * class_simple_set_hotplug - set the hotplug callback in the embedded struct class&n; * @cs: pointer to the struct class_simple to hold the pointer&n; * @hotplug: function pointer to the hotplug function&n; *&n; * Implement and set a hotplug function to add environment variables specific to this&n; * class on the hotplug event.&n; */
DECL|function|class_simple_set_hotplug
r_int
id|class_simple_set_hotplug
c_func
(paren
r_struct
id|class_simple
op_star
id|cs
comma
r_int
(paren
op_star
id|hotplug
)paren
(paren
r_struct
id|class_device
op_star
id|dev
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
)paren
(brace
r_if
c_cond
(paren
(paren
id|cs
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|IS_ERR
c_func
(paren
id|cs
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cs
op_member_access_from_pointer
r_class
dot
id|hotplug
op_assign
id|hotplug
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|class_simple_set_hotplug
id|EXPORT_SYMBOL
c_func
(paren
id|class_simple_set_hotplug
)paren
suffix:semicolon
multiline_comment|/**&n; * class_simple_device_remove - removes a class device that was created with class_simple_device_add()&n; * @dev: the dev_t of the device that was previously registered.&n; *&n; * This call unregisters and cleans up a class device that was created with a&n; * call to class_device_simple_add()&n; */
DECL|function|class_simple_device_remove
r_void
id|class_simple_device_remove
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|simple_dev
op_star
id|s_dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|simple_dev_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|s_dev
comma
op_amp
id|simple_dev_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|s_dev-&gt;dev
op_eq
id|dev
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|s_dev-&gt;node
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|simple_dev_list_lock
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|s_dev-&gt;class_dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|simple_dev_list_lock
)paren
suffix:semicolon
)brace
)brace
DECL|variable|class_simple_device_remove
id|EXPORT_SYMBOL
c_func
(paren
id|class_simple_device_remove
)paren
suffix:semicolon
eof
