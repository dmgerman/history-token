multiline_comment|/*&n; * drm_sysfs.c - Modifications to drm_sysfs_class.c to support&n; *               extra sysfs attribute from DRM. Normal drm_sysfs_class&n; *               does not allow adding attributes.&n; *&n; * Copyright (c) 2004 Jon Smirl &lt;jonsmirl@gmail.com&gt;&n; * Copyright (c) 2003-2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * Copyright (c) 2003-2004 IBM Corp.&n; *&n; * This file is released under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &quot;drm_core.h&quot;
DECL|struct|drm_sysfs_class
r_struct
id|drm_sysfs_class
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
DECL|macro|to_drm_sysfs_class
mdefine_line|#define to_drm_sysfs_class(d) container_of(d, struct drm_sysfs_class, class)
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
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|simple_dev_list_lock
)paren
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
DECL|function|drm_sysfs_class_release
r_static
r_void
id|drm_sysfs_class_release
c_func
(paren
r_struct
r_class
op_star
r_class
)paren
(brace
r_struct
id|drm_sysfs_class
op_star
id|cs
op_assign
id|to_drm_sysfs_class
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
multiline_comment|/* Display the version of drm_core. This doesn&squot;t work right in current design */
DECL|function|version_show
r_static
id|ssize_t
id|version_show
c_func
(paren
r_struct
r_class
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s %d.%d.%d %s&bslash;n&quot;
comma
id|DRIVER_NAME
comma
id|DRIVER_MAJOR
comma
id|DRIVER_MINOR
comma
id|DRIVER_PATCHLEVEL
comma
id|DRIVER_DATE
)paren
suffix:semicolon
)brace
r_static
id|CLASS_ATTR
c_func
(paren
id|version
comma
id|S_IRUGO
comma
id|version_show
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; * drm_sysfs_create - create a struct drm_sysfs_class structure&n; * @owner: pointer to the module that is to &quot;own&quot; this struct drm_sysfs_class&n; * @name: pointer to a string for the name of this class.&n; *&n; * This is used to create a struct drm_sysfs_class pointer that can then be used&n; * in calls to drm_sysfs_device_add().&n; *&n; * Note, the pointer created here is to be destroyed when finished by making a&n; * call to drm_sysfs_destroy().&n; */
DECL|function|drm_sysfs_create
r_struct
id|drm_sysfs_class
op_star
id|drm_sysfs_create
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
id|drm_sysfs_class
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
id|drm_sysfs_class_release
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
id|class_create_file
c_func
(paren
op_amp
id|cs
op_member_access_from_pointer
r_class
comma
op_amp
id|class_attr_version
)paren
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
multiline_comment|/**&n; * drm_sysfs_destroy - destroys a struct drm_sysfs_class structure&n; * @cs: pointer to the struct drm_sysfs_class that is to be destroyed&n; *&n; * Note, the pointer to be destroyed must have been created with a call to&n; * drm_sysfs_create().&n; */
DECL|function|drm_sysfs_destroy
r_void
id|drm_sysfs_destroy
c_func
(paren
r_struct
id|drm_sysfs_class
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
multiline_comment|/**&n; * drm_sysfs_device_add - adds a class device to sysfs for a character driver&n; * @cs: pointer to the struct drm_sysfs_class that this device should be registered to.&n; * @dev: the dev_t for the device to be added.&n; * @device: a pointer to a struct device that is assiociated with this class device.&n; * @fmt: string for the class device&squot;s name&n; *&n; * A struct class_device will be created in sysfs, registered to the specified&n; * class.  A &quot;dev&quot; file will be created, showing the dev_t for the device.  The&n; * pointer to the struct class_device will be returned from the call.  Any further&n; * sysfs files that might be required can be created using this pointer.&n; * Note: the struct drm_sysfs_class passed to this function must have previously been&n; * created with a call to drm_sysfs_create().&n; */
DECL|function|drm_sysfs_device_add
r_struct
id|class_device
op_star
id|drm_sysfs_device_add
c_func
(paren
r_struct
id|drm_sysfs_class
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
multiline_comment|/**&n; * drm_sysfs_device_remove - removes a class device that was created with drm_sysfs_device_add()&n; * @dev: the dev_t of the device that was previously registered.&n; *&n; * This call unregisters and cleans up a class device that was created with a&n; * call to drm_sysfs_device_add()&n; */
DECL|function|drm_sysfs_device_remove
r_void
id|drm_sysfs_device_remove
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
eof
