multiline_comment|/*&n; * drivers/usb/file.c&n; *&n; * (C) Copyright Linus Torvalds 1999&n; * (C) Copyright Johannes Erdfelt 1999-2001&n; * (C) Copyright Andreas Gal 1999&n; * (C) Copyright Gregory P. Smith 1999&n; * (C) Copyright Deti Fliegl 1999 (new USB architecture)&n; * (C) Copyright Randy Dunlap 2000&n; * (C) Copyright David Brownell 2000-2001 (kernel hotplug, usb_device_id,&n; &t;more docs, etc)&n; * (C) Copyright Yggdrasil Computing, Inc. 2000&n; *     (usb_device_id matching changes by Adam J. Richter)&n; * (C) Copyright Greg Kroah-Hartman 2002-2003&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|MAX_USB_MINORS
mdefine_line|#define MAX_USB_MINORS&t;256
DECL|variable|usb_minors
r_static
r_struct
id|file_operations
op_star
id|usb_minors
(braket
id|MAX_USB_MINORS
)braket
suffix:semicolon
DECL|variable|minor_lock
r_static
id|spinlock_t
id|minor_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|usb_open
r_static
r_int
id|usb_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|file_operations
op_star
id|c
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
comma
op_star
id|new_fops
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
id|c
op_assign
id|usb_minors
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
op_logical_neg
(paren
id|new_fops
op_assign
id|fops_get
c_func
(paren
id|c
)paren
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|new_fops
suffix:semicolon
multiline_comment|/* Curiouser and curiouser... NULL -&gt;open() as &quot;no device&quot; ? */
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|usb_fops
r_static
r_struct
id|file_operations
id|usb_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|usb_open
comma
)brace
suffix:semicolon
DECL|function|release_usb_class_dev
r_static
r_void
id|release_usb_class_dev
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - %s&quot;
comma
id|__FUNCTION__
comma
id|class_dev-&gt;class_id
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
DECL|variable|usb_class
r_static
r_struct
r_class
id|usb_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb&quot;
comma
dot
id|release
op_assign
op_amp
id|release_usb_class_dev
comma
)brace
suffix:semicolon
DECL|function|usb_major_init
r_int
id|usb_major_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|USB_MAJOR
comma
l_string|&quot;usb&quot;
comma
op_amp
id|usb_fops
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;unable to get major %d for usb devices&quot;
comma
id|USB_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|devfs_mk_dir
c_func
(paren
l_string|&quot;usb&quot;
)paren
suffix:semicolon
id|class_register
c_func
(paren
op_amp
id|usb_class
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_major_cleanup
r_void
id|usb_major_cleanup
c_func
(paren
r_void
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|usb_class
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;usb&quot;
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|USB_MAJOR
comma
l_string|&quot;usb&quot;
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
r_int
id|minor
op_assign
(paren
r_int
)paren
id|class_get_devdata
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
id|MKDEV
c_func
(paren
id|USB_MAJOR
comma
id|minor
)paren
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|dev
comma
id|S_IRUGO
comma
id|show_dev
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; * usb_register_dev - register a USB device, and ask for a minor number&n; * @intf: pointer to the usb_interface that is being registered&n; * @class_driver: pointer to the usb_class_driver for this device&n; *&n; * This should be called by all USB drivers that use the USB major number.&n; * If CONFIG_USB_DYNAMIC_MINORS is enabled, the minor number will be&n; * dynamically allocated out of the list of available ones.  If it is not&n; * enabled, the minor number will be based on the next available free minor,&n; * starting at the class_driver-&gt;minor_base.&n; *&n; * This function also creates the devfs file for the usb device, if devfs&n; * is enabled, and creates a usb class device in the sysfs tree.&n; *&n; * usb_deregister_dev() must be called when the driver is done with&n; * the minor numbers given out by this function.&n; *&n; * Returns -EINVAL if something bad happens with trying to register a&n; * device, and 0 on success.&n; */
DECL|function|usb_register_dev
r_int
id|usb_register_dev
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_struct
id|usb_class_driver
op_star
id|class_driver
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
id|minor_base
op_assign
id|class_driver-&gt;minor_base
suffix:semicolon
r_int
id|minor
op_assign
l_int|0
suffix:semicolon
r_char
id|name
(braket
id|DEVICE_ID_SIZE
)braket
suffix:semicolon
r_struct
id|class_device
op_star
id|class_dev
suffix:semicolon
r_char
op_star
id|temp
suffix:semicolon
macro_line|#ifdef CONFIG_USB_DYNAMIC_MINORS
multiline_comment|/* &n;&t; * We don&squot;t care what the device tries to start at, we want to start&n;&t; * at zero to pack the devices into the smallest available space with&n;&t; * no holes in the minor range.&n;&t; */
id|minor_base
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|intf-&gt;minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|dbg
(paren
l_string|&quot;looking for a minor, starting at %d&quot;
comma
id|minor_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_driver-&gt;fops
op_eq
l_int|NULL
)paren
r_goto
m_exit
suffix:semicolon
id|spin_lock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
id|minor_base
suffix:semicolon
id|minor
OL
id|MAX_USB_MINORS
suffix:semicolon
op_increment
id|minor
)paren
(brace
r_if
c_cond
(paren
id|usb_minors
(braket
id|minor
)braket
)paren
r_continue
suffix:semicolon
id|usb_minors
(braket
id|minor
)braket
op_assign
id|class_driver-&gt;fops
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|intf-&gt;minor
op_assign
id|minor
suffix:semicolon
multiline_comment|/* handle the devfs registration */
id|snprintf
c_func
(paren
id|name
comma
id|DEVICE_ID_SIZE
comma
id|class_driver-&gt;name
comma
id|minor
op_minus
id|minor_base
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|USB_MAJOR
comma
id|minor
)paren
comma
id|class_driver-&gt;mode
comma
id|name
)paren
suffix:semicolon
multiline_comment|/* create a usb class device for this usb interface */
id|class_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|class_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|class_dev
)paren
(brace
id|memset
c_func
(paren
id|class_dev
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|class_device
)paren
)paren
suffix:semicolon
id|class_dev
op_member_access_from_pointer
r_class
op_assign
op_amp
id|usb_class
suffix:semicolon
id|class_dev-&gt;dev
op_assign
op_amp
id|intf-&gt;dev
suffix:semicolon
id|temp
op_assign
id|strrchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_logical_and
(paren
id|temp
(braket
l_int|1
)braket
op_ne
l_int|0x00
)paren
)paren
op_increment
id|temp
suffix:semicolon
r_else
id|temp
op_assign
id|name
suffix:semicolon
id|snprintf
c_func
(paren
id|class_dev-&gt;class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%s&quot;
comma
id|temp
)paren
suffix:semicolon
id|class_set_devdata
c_func
(paren
id|class_dev
comma
(paren
r_void
op_star
)paren
id|intf-&gt;minor
)paren
suffix:semicolon
id|class_device_register
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_create_file
c_func
(paren
id|class_dev
comma
op_amp
id|class_device_attr_dev
)paren
suffix:semicolon
id|intf-&gt;class_dev
op_assign
id|class_dev
suffix:semicolon
)brace
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|usb_register_dev
id|EXPORT_SYMBOL
c_func
(paren
id|usb_register_dev
)paren
suffix:semicolon
multiline_comment|/**&n; * usb_deregister_dev - deregister a USB device&squot;s dynamic minor.&n; * @intf: pointer to the usb_interface that is being deregistered&n; * @class_driver: pointer to the usb_class_driver for this device&n; *&n; * Used in conjunction with usb_register_dev().  This function is called&n; * when the USB driver is finished with the minor numbers gotten from a&n; * call to usb_register_dev() (usually when the device is disconnected&n; * from the system.)&n; *&n; * This function also cleans up the devfs file for the usb device, if devfs&n; * is enabled, and removes the usb class device from the sysfs tree.&n; * &n; * This should be called by all drivers that use the USB major number.&n; */
DECL|function|usb_deregister_dev
r_void
id|usb_deregister_dev
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_struct
id|usb_class_driver
op_star
id|class_driver
)paren
(brace
r_int
id|minor_base
op_assign
id|class_driver-&gt;minor_base
suffix:semicolon
r_char
id|name
(braket
id|DEVICE_ID_SIZE
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_USB_DYNAMIC_MINORS
id|minor_base
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|intf-&gt;minor
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
id|dbg
(paren
l_string|&quot;removing %d minor&quot;
comma
id|intf-&gt;minor
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
id|usb_minors
(braket
id|intf-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|DEVICE_ID_SIZE
comma
id|class_driver-&gt;name
comma
id|intf-&gt;minor
op_minus
id|minor_base
)paren
suffix:semicolon
id|devfs_remove
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intf-&gt;class_dev
)paren
(brace
id|class_device_unregister
c_func
(paren
id|intf-&gt;class_dev
)paren
suffix:semicolon
id|intf-&gt;class_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|intf-&gt;minor
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|usb_deregister_dev
id|EXPORT_SYMBOL
c_func
(paren
id|usb_deregister_dev
)paren
suffix:semicolon
eof
