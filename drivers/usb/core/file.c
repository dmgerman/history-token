multiline_comment|/*&n; * drivers/usb/file.c&n; *&n; * (C) Copyright Linus Torvalds 1999&n; * (C) Copyright Johannes Erdfelt 1999-2001&n; * (C) Copyright Andreas Gal 1999&n; * (C) Copyright Gregory P. Smith 1999&n; * (C) Copyright Deti Fliegl 1999 (new USB architecture)&n; * (C) Copyright Randy Dunlap 2000&n; * (C) Copyright David Brownell 2000-2001 (kernel hotplug, usb_device_id,&n; &t;more docs, etc)&n; * (C) Copyright Yggdrasil Computing, Inc. 2000&n; *     (usb_device_id matching changes by Adam J. Richter)&n; * (C) Copyright Greg Kroah-Hartman 2002&n; *&n; */
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
DECL|variable|usb_devfs_handle
id|devfs_handle_t
id|usb_devfs_handle
suffix:semicolon
multiline_comment|/* /dev/usb dir. */
DECL|variable|usb_devfs_handle
id|EXPORT_SYMBOL
c_func
(paren
id|usb_devfs_handle
)paren
suffix:semicolon
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
id|minor
c_func
(paren
id|inode-&gt;i_rdev
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
id|usb_devfs_handle
op_assign
id|devfs_mk_dir
c_func
(paren
l_string|&quot;usb&quot;
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
id|devfs_unregister
c_func
(paren
id|usb_devfs_handle
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
multiline_comment|/**&n; * usb_register_dev - register a USB device, and ask for a minor number&n; * @fops: the file operations for this USB device&n; * @minor: the requested starting minor for this device.&n; * @num_minors: number of minor numbers requested for this device&n; * @start_minor: place to put the new starting minor number&n; *&n; * This should be called by all USB drivers that use the USB major number.&n; * If CONFIG_USB_DYNAMIC_MINORS is enabled, the minor number will be&n; * dynamically allocated out of the list of available ones.  If it is not&n; * enabled, the minor number will be based on the next available free minor,&n; * starting at the requested @minor.&n; *&n; * usb_deregister_dev() must be called when the driver is done with&n; * the minor numbers given out by this function.&n; *&n; * Returns -EINVAL if something bad happens with trying to register a&n; * device, and 0 on success, alone with a value that the driver should&n; * use in start_minor.&n; */
DECL|function|usb_register_dev
r_int
id|usb_register_dev
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|minor
comma
r_int
id|num_minors
comma
r_int
op_star
id|start_minor
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|good_spot
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
macro_line|#ifdef CONFIG_USB_DYNAMIC_MINORS
multiline_comment|/* &n;&t; * We don&squot;t care what the device tries to start at, we want to start&n;&t; * at zero to pack the devices into the smallest available space with&n;&t; * no holes in the minor range.&n;&t; */
id|minor
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|dbg
(paren
l_string|&quot;asking for %d minors, starting at %d&quot;
comma
id|num_minors
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fops
op_eq
l_int|NULL
)paren
r_goto
m_exit
suffix:semicolon
op_star
id|start_minor
op_assign
l_int|0
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
id|i
op_assign
id|minor
suffix:semicolon
id|i
OL
id|MAX_USB_MINORS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|usb_minors
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|good_spot
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
op_le
id|num_minors
op_minus
l_int|1
suffix:semicolon
op_increment
id|j
)paren
r_if
c_cond
(paren
id|usb_minors
(braket
id|i
op_plus
id|j
)braket
)paren
(brace
id|good_spot
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|good_spot
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
op_star
id|start_minor
op_assign
id|i
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;found a minor chunk free, starting at %d&quot;
comma
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_star
id|start_minor
suffix:semicolon
id|i
OL
(paren
op_star
id|start_minor
op_plus
id|num_minors
)paren
suffix:semicolon
op_increment
id|i
)paren
id|usb_minors
(braket
id|i
)braket
op_assign
id|fops
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
m_exit
suffix:colon
id|spin_unlock
(paren
op_amp
id|minor_lock
)paren
suffix:semicolon
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
multiline_comment|/**&n; * usb_deregister_dev - deregister a USB device&squot;s dynamic minor.&n; * @num_minors: number of minor numbers to put back.&n; * @start_minor: the starting minor number&n; *&n; * Used in conjunction with usb_register_dev().  This function is called&n; * when the USB driver is finished with the minor numbers gotten from a&n; * call to usb_register_dev() (usually when the device is disconnected&n; * from the system.)&n; * &n; * This should be called by all drivers that use the USB major number.&n; */
DECL|function|usb_deregister_dev
r_void
id|usb_deregister_dev
(paren
r_int
id|num_minors
comma
r_int
id|start_minor
)paren
(brace
r_int
id|i
suffix:semicolon
id|dbg
(paren
l_string|&quot;removing %d minors starting at %d&quot;
comma
id|num_minors
comma
id|start_minor
)paren
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
id|i
op_assign
id|start_minor
suffix:semicolon
id|i
OL
(paren
id|start_minor
op_plus
id|num_minors
)paren
suffix:semicolon
op_increment
id|i
)paren
id|usb_minors
(braket
id|i
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
)brace
DECL|variable|usb_deregister_dev
id|EXPORT_SYMBOL
c_func
(paren
id|usb_deregister_dev
)paren
suffix:semicolon
eof
