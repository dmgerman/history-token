multiline_comment|/*&n; * USB Skeleton driver - 0.8&n; *&n; * Copyright (c) 2001-2002 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; *&n; * This driver is to be used as a skeleton driver to be able to create a&n; * USB driver quickly.  The design of it is based on the usb-serial and&n; * dc2xx drivers.&n; *&n; * Thanks to Oliver Neukum and David Brownell for their help in debugging&n; * this driver.&n; *&n; * TODO:&n; *&t;- fix urb-&gt;status race condition in write sequence&n; *&t;- move minor_table to a dynamic list.&n; *&n; * History:&n; *&n; * 2002_09_26 - 0.8 - changes due to USB core conversion to struct device&n; *&t;&t;&t;driver.&n; * 2002_02_12 - 0.7 - zero out dev in probe function for devices that do&n; *&t;&t;&t;not have both a bulk in and bulk out endpoint.&n; *&t;&t;&t;Thanks to Holger Waechtler for the fix.&n; * 2001_11_05 - 0.6 - fix minor locking problem in skel_disconnect.&n; *&t;&t;&t;Thanks to Pete Zaitcev for the fix.&n; * 2001_09_04 - 0.5 - fix devfs bug in skel_disconnect. Thanks to wim delvaux&n; * 2001_08_21 - 0.4 - more small bug fixes.&n; * 2001_05_29 - 0.3 - more bug fixes based on review from linux-usb-devel&n; * 2001_05_24 - 0.2 - bug fixes based on review from linux-usb-devel people&n; * 2001_05_01 - 0.1 - first version&n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
macro_line|#endif
multiline_comment|/* Use our own dbg macro */
DECL|macro|dbg
macro_line|#undef dbg
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do { if (debug) printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg); } while (0)
multiline_comment|/* Version Information */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.4&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Greg Kroah-Hartman, greg@kroah.com&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Skeleton Driver&quot;
multiline_comment|/* Module paramaters */
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
multiline_comment|/* Define these values to match your device */
DECL|macro|USB_SKEL_VENDOR_ID
mdefine_line|#define USB_SKEL_VENDOR_ID&t;0xfff0
DECL|macro|USB_SKEL_PRODUCT_ID
mdefine_line|#define USB_SKEL_PRODUCT_ID&t;0xfff0
multiline_comment|/* table of devices that work with this driver */
DECL|variable|skel_table
r_static
r_struct
id|usb_device_id
id|skel_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_SKEL_VENDOR_ID
comma
id|USB_SKEL_PRODUCT_ID
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|skel_table
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB_DYNAMIC_MINORS
multiline_comment|/* &n; * if the user wants to use dynamic minor numbers, then we can have up to 256&n; * devices&n; */
DECL|macro|USB_SKEL_MINOR_BASE
mdefine_line|#define USB_SKEL_MINOR_BASE&t;0
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES&t;&t;256
macro_line|#else
multiline_comment|/* Get a minor range for your devices from the usb maintainer */
DECL|macro|USB_SKEL_MINOR_BASE
mdefine_line|#define USB_SKEL_MINOR_BASE&t;200
multiline_comment|/* we can have up to this number of device plugged in at once */
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES&t;&t;16
macro_line|#endif
multiline_comment|/* Structure to hold all of our device specific stuff */
DECL|struct|usb_skel
r_struct
id|usb_skel
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
multiline_comment|/* save off the usb device pointer */
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
multiline_comment|/* the interface for this device */
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
multiline_comment|/* devfs device node */
DECL|member|minor
r_int
r_char
id|minor
suffix:semicolon
multiline_comment|/* the starting minor number for this device */
DECL|member|num_ports
r_int
r_char
id|num_ports
suffix:semicolon
multiline_comment|/* the number of ports this device has */
DECL|member|num_interrupt_in
r_char
id|num_interrupt_in
suffix:semicolon
multiline_comment|/* number of interrupt in endpoints we have */
DECL|member|num_bulk_in
r_char
id|num_bulk_in
suffix:semicolon
multiline_comment|/* number of bulk in endpoints we have */
DECL|member|num_bulk_out
r_char
id|num_bulk_out
suffix:semicolon
multiline_comment|/* number of bulk out endpoints we have */
DECL|member|bulk_in_buffer
r_int
r_char
op_star
id|bulk_in_buffer
suffix:semicolon
multiline_comment|/* the buffer to receive data */
DECL|member|bulk_in_size
r_int
id|bulk_in_size
suffix:semicolon
multiline_comment|/* the size of the receive buffer */
DECL|member|bulk_in_endpointAddr
id|__u8
id|bulk_in_endpointAddr
suffix:semicolon
multiline_comment|/* the address of the bulk in endpoint */
DECL|member|bulk_out_buffer
r_int
r_char
op_star
id|bulk_out_buffer
suffix:semicolon
multiline_comment|/* the buffer to send data */
DECL|member|bulk_out_size
r_int
id|bulk_out_size
suffix:semicolon
multiline_comment|/* the size of the send buffer */
DECL|member|write_urb
r_struct
id|urb
op_star
id|write_urb
suffix:semicolon
multiline_comment|/* the urb used to send data */
DECL|member|bulk_out_endpointAddr
id|__u8
id|bulk_out_endpointAddr
suffix:semicolon
multiline_comment|/* the address of the bulk out endpoint */
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
multiline_comment|/* work queue entry for line discipline waking up */
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
multiline_comment|/* number of times this port has been opened */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* locks this structure */
)brace
suffix:semicolon
multiline_comment|/* the global usb devfs handle */
r_extern
id|devfs_handle_t
id|usb_devfs_handle
suffix:semicolon
multiline_comment|/* local function prototypes */
r_static
id|ssize_t
id|skel_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|ssize_t
id|skel_write
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
id|skel_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|skel_open
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
suffix:semicolon
r_static
r_int
id|skel_release
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
suffix:semicolon
r_static
r_int
id|skel_probe
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
suffix:semicolon
r_static
r_void
id|skel_disconnect
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_static
r_void
id|skel_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* array of pointers to our devices that are currently connected */
DECL|variable|minor_table
r_static
r_struct
id|usb_skel
op_star
id|minor_table
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
multiline_comment|/* lock to protect the minor_table structure */
r_static
id|DECLARE_MUTEX
(paren
id|minor_table_mutex
)paren
suffix:semicolon
multiline_comment|/*&n; * File operations needed when we register this driver.&n; * This assumes that this driver NEEDS file operations,&n; * of course, which means that the driver is expected&n; * to have a node in the /dev directory. If the USB&n; * device were for a network interface then the driver&n; * would use &quot;struct net_driver&quot; instead, and a serial&n; * device would use &quot;struct tty_driver&quot;. &n; */
DECL|variable|skel_fops
r_static
r_struct
id|file_operations
id|skel_fops
op_assign
(brace
multiline_comment|/*&n;&t; * The owner field is part of the module-locking&n;&t; * mechanism. The idea is that the kernel knows&n;&t; * which module to increment the use-counter of&n;&t; * BEFORE it calls the device&squot;s open() function.&n;&t; * This also means that the kernel can decrement&n;&t; * the use-counter again before calling release()&n;&t; * or should the open() function fail.&n;&t; *&n;&t; * Not all device structures have an &quot;owner&quot; field&n;&t; * yet. &quot;struct file_operations&quot; and &quot;struct net_device&quot;&n;&t; * do, while &quot;struct tty_driver&quot; does not. If the struct&n;&t; * has an &quot;owner&quot; field, then initialize it to the value&n;&t; * THIS_MODULE and the kernel will handle all module&n;&t; * locking for you automatically. Otherwise, you must&n;&t; * increment the use-counter in the open() function&n;&t; * and decrement it again in the release() function&n;&t; * yourself.&n;&t; */
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|skel_read
comma
dot
id|write
op_assign
id|skel_write
comma
dot
id|ioctl
op_assign
id|skel_ioctl
comma
dot
id|open
op_assign
id|skel_open
comma
dot
id|release
op_assign
id|skel_release
comma
)brace
suffix:semicolon
multiline_comment|/* usb specific object needed to register this driver with the usb subsystem */
DECL|variable|skel_driver
r_static
r_struct
id|usb_driver
id|skel_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;skeleton&quot;
comma
dot
id|probe
op_assign
id|skel_probe
comma
dot
id|disconnect
op_assign
id|skel_disconnect
comma
dot
id|id_table
op_assign
id|skel_table
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;usb_skel_debug_data&n; */
DECL|function|usb_skel_debug_data
r_static
r_inline
r_void
id|usb_skel_debug_data
(paren
r_const
r_char
op_star
id|function
comma
r_int
id|size
comma
r_const
r_int
r_char
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|debug
)paren
r_return
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
id|__FILE__
l_string|&quot;: %s - length = %d, data = &quot;
comma
id|function
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
op_increment
id|i
)paren
(brace
id|printk
(paren
l_string|&quot;%.2x &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_delete&n; */
DECL|function|skel_delete
r_static
r_inline
r_void
id|skel_delete
(paren
r_struct
id|usb_skel
op_star
id|dev
)paren
(brace
id|minor_table
(braket
id|dev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bulk_in_buffer
op_ne
l_int|NULL
)paren
id|kfree
(paren
id|dev-&gt;bulk_in_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bulk_out_buffer
op_ne
l_int|NULL
)paren
id|kfree
(paren
id|dev-&gt;bulk_out_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;write_urb
op_ne
l_int|NULL
)paren
id|usb_free_urb
(paren
id|dev-&gt;write_urb
)paren
suffix:semicolon
id|kfree
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_open&n; */
DECL|function|skel_open
r_static
r_int
id|skel_open
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
r_struct
id|usb_skel
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|subminor
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
)paren
suffix:semicolon
id|subminor
op_assign
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|USB_SKEL_MINOR_BASE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|subminor
OL
l_int|0
)paren
op_logical_or
(paren
id|subminor
op_ge
id|MAX_DEVICES
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Increment our usage count for the module.&n;&t; * This is redundant here, because &quot;struct file_operations&quot;&n;&t; * has an &quot;owner&quot; field. This line is included here soley as&n;&t; * a reference for drivers using lesser structures... ;-)&n;&t; */
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* lock our minor table and get our local data for this minor */
id|down
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
id|dev
op_assign
id|minor_table
(braket
id|subminor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* lock this device */
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* unlock the minor table */
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
multiline_comment|/* increment our usage count for the driver */
op_increment
id|dev-&gt;open_count
suffix:semicolon
multiline_comment|/* save our object in the file&squot;s private structure */
id|file-&gt;private_data
op_assign
id|dev
suffix:semicolon
multiline_comment|/* unlock this device */
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_release&n; */
DECL|function|skel_release
r_static
r_int
id|skel_release
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
r_struct
id|usb_skel
op_star
id|dev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_skel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - object is NULL&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - minor %d&quot;
comma
id|dev-&gt;minor
)paren
suffix:semicolon
multiline_comment|/* lock our minor table */
id|down
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
multiline_comment|/* lock our device */
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;open_count
op_le
l_int|0
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - device not opened&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|exit_not_opened
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;udev
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* the device was unplugged before the file was released */
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|skel_delete
(paren
id|dev
)paren
suffix:semicolon
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* decrement our usage count for the device */
op_decrement
id|dev-&gt;open_count
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;open_count
op_le
l_int|0
)paren
(brace
multiline_comment|/* shutdown any bulk writes that might be going on */
id|usb_unlink_urb
(paren
id|dev-&gt;write_urb
)paren
suffix:semicolon
id|dev-&gt;open_count
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* decrement our usage count for the module */
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|exit_not_opened
suffix:colon
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_read&n; */
DECL|function|skel_read
r_static
id|ssize_t
id|skel_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|usb_skel
op_star
id|dev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_skel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - minor %d, count = %d&quot;
comma
id|dev-&gt;minor
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* lock this object */
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* verify that the device wasn&squot;t unplugged */
r_if
c_cond
(paren
id|dev-&gt;udev
op_eq
l_int|NULL
)paren
(brace
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* do an immediate bulk read to get data from the device */
id|retval
op_assign
id|usb_bulk_msg
(paren
id|dev-&gt;udev
comma
id|usb_rcvbulkpipe
(paren
id|dev-&gt;udev
comma
id|dev-&gt;bulk_in_endpointAddr
)paren
comma
id|dev-&gt;bulk_in_buffer
comma
id|dev-&gt;bulk_in_size
comma
op_amp
id|count
comma
id|HZ
op_star
l_int|10
)paren
suffix:semicolon
multiline_comment|/* if the read was successful, copy the data to userspace */
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buffer
comma
id|dev-&gt;bulk_in_buffer
comma
id|count
)paren
)paren
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
id|retval
op_assign
id|count
suffix:semicolon
)brace
multiline_comment|/* unlock the device */
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_write&n; */
DECL|function|skel_write
r_static
id|ssize_t
id|skel_write
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|usb_skel
op_star
id|dev
suffix:semicolon
id|ssize_t
id|bytes_written
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_skel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - minor %d, count = %d&quot;
comma
id|dev-&gt;minor
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* lock this object */
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* verify that the device wasn&squot;t unplugged */
r_if
c_cond
(paren
id|dev-&gt;udev
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* verify that we actually have some data to write */
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - write request of 0 bytes&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* see if we are already in the middle of a write */
r_if
c_cond
(paren
id|dev-&gt;write_urb-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
id|dbg
(paren
id|__FUNCTION__
l_string|&quot; - already writing&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* we can only write as much as 1 urb will hold */
id|bytes_written
op_assign
(paren
id|count
OG
id|dev-&gt;bulk_out_size
)paren
ques
c_cond
id|dev-&gt;bulk_out_size
suffix:colon
id|count
suffix:semicolon
multiline_comment|/* copy the data from userspace into our urb */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|dev-&gt;write_urb-&gt;transfer_buffer
comma
id|buffer
comma
id|bytes_written
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|usb_skel_debug_data
(paren
id|__FUNCTION__
comma
id|bytes_written
comma
id|dev-&gt;write_urb-&gt;transfer_buffer
)paren
suffix:semicolon
multiline_comment|/* set up our urb */
id|usb_fill_bulk_urb
c_func
(paren
id|dev-&gt;write_urb
comma
id|dev-&gt;udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dev-&gt;udev
comma
id|dev-&gt;bulk_out_endpointAddr
)paren
comma
id|dev-&gt;write_urb-&gt;transfer_buffer
comma
id|bytes_written
comma
id|skel_write_bulk_callback
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* send the data out the bulk port */
multiline_comment|/* a character device write uses GFP_KERNEL,&n;&t; unless a spinlock is held */
id|retval
op_assign
id|usb_submit_urb
c_func
(paren
id|dev-&gt;write_urb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|err
c_func
(paren
id|__FUNCTION__
l_string|&quot; - failed submitting write urb, error %d&quot;
comma
id|retval
)paren
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
id|bytes_written
suffix:semicolon
)brace
m_exit
suffix:colon
multiline_comment|/* unlock the device */
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_ioctl&n; */
DECL|function|skel_ioctl
r_static
r_int
id|skel_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|usb_skel
op_star
id|dev
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_skel
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
multiline_comment|/* lock this object */
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* verify that the device wasn&squot;t unplugged */
r_if
c_cond
(paren
id|dev-&gt;udev
op_eq
l_int|NULL
)paren
(brace
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - minor %d, cmd 0x%.4x, arg %ld&quot;
comma
id|dev-&gt;minor
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* fill in your device specific stuff here */
multiline_comment|/* unlock the device */
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* return that we did not understand this ioctl call */
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_write_bulk_callback&n; */
DECL|function|skel_write_bulk_callback
r_static
r_void
id|skel_write_bulk_callback
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_skel
op_star
id|dev
op_assign
(paren
r_struct
id|usb_skel
op_star
)paren
id|urb-&gt;context
suffix:semicolon
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - minor %d&quot;
comma
id|dev-&gt;minor
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|urb-&gt;status
op_ne
op_minus
id|ENOENT
)paren
op_logical_and
(paren
id|urb-&gt;status
op_ne
op_minus
id|ECONNRESET
)paren
)paren
(brace
id|dbg
c_func
(paren
id|__FUNCTION__
l_string|&quot; - nonzero write bulk status received: %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_probe&n; *&n; *&t;Called by the usb core when a new device is connected that it thinks&n; *&t;this driver might be interested in.&n; */
DECL|function|skel_probe
r_static
r_int
id|skel_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|interface
)paren
suffix:semicolon
r_struct
id|usb_skel
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|iface_desc
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_int
id|minor
suffix:semicolon
r_int
id|buffer_size
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* See if the device offered us matches what we can accept */
r_if
c_cond
(paren
(paren
id|udev-&gt;descriptor.idVendor
op_ne
id|USB_SKEL_VENDOR_ID
)paren
op_logical_or
(paren
id|udev-&gt;descriptor.idProduct
op_ne
id|USB_SKEL_PRODUCT_ID
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|down
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
id|retval
op_assign
id|usb_register_dev
(paren
op_amp
id|skel_fops
comma
id|USB_SKEL_MINOR_BASE
comma
l_int|1
comma
op_amp
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
multiline_comment|/* something prevented us from registering this driver */
id|err
(paren
l_string|&quot;Not able to get a minor for this device.&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* allocate memory for our device state and intialize it */
id|dev
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|usb_skel
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|err
(paren
l_string|&quot;Out of memory&quot;
)paren
suffix:semicolon
r_goto
id|exit_minor
suffix:semicolon
)brace
id|memset
(paren
id|dev
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|minor_table
(braket
id|minor
)braket
op_assign
id|dev
suffix:semicolon
id|init_MUTEX
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|dev-&gt;udev
op_assign
id|udev
suffix:semicolon
id|dev-&gt;interface
op_assign
id|interface
suffix:semicolon
id|dev-&gt;minor
op_assign
id|minor
suffix:semicolon
multiline_comment|/* set up the endpoint information */
multiline_comment|/* check out the endpoints */
id|iface_desc
op_assign
op_amp
id|interface-&gt;altsetting
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|iface_desc-&gt;bNumEndpoints
suffix:semicolon
op_increment
id|i
)paren
(brace
id|endpoint
op_assign
op_amp
id|iface_desc-&gt;endpoint
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_eq
l_int|0x02
)paren
)paren
(brace
multiline_comment|/* we found a bulk in endpoint */
id|buffer_size
op_assign
id|endpoint-&gt;wMaxPacketSize
suffix:semicolon
id|dev-&gt;bulk_in_size
op_assign
id|buffer_size
suffix:semicolon
id|dev-&gt;bulk_in_endpointAddr
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
id|dev-&gt;bulk_in_buffer
op_assign
id|kmalloc
(paren
id|buffer_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bulk_in_buffer
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Couldn&squot;t allocate bulk_in_buffer&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
op_eq
l_int|0x00
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_eq
l_int|0x02
)paren
)paren
(brace
multiline_comment|/* we found a bulk out endpoint */
multiline_comment|/* a probe() may sleep and has no restrictions on memory allocations */
id|dev-&gt;write_urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;write_urb
)paren
(brace
id|err
c_func
(paren
l_string|&quot;No free urbs available&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|buffer_size
op_assign
id|endpoint-&gt;wMaxPacketSize
suffix:semicolon
id|dev-&gt;bulk_out_size
op_assign
id|buffer_size
suffix:semicolon
id|dev-&gt;bulk_out_endpointAddr
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
id|dev-&gt;bulk_out_buffer
op_assign
id|kmalloc
(paren
id|buffer_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bulk_out_buffer
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Couldn&squot;t allocate bulk_out_buffer&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|usb_fill_bulk_urb
c_func
(paren
id|dev-&gt;write_urb
comma
id|udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|udev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|dev-&gt;bulk_out_buffer
comma
id|buffer_size
comma
id|skel_write_bulk_callback
comma
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* initialize the devfs node for this device and register it */
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;skel%d&quot;
comma
id|dev-&gt;minor
)paren
suffix:semicolon
id|dev-&gt;devfs
op_assign
id|devfs_register
(paren
id|usb_devfs_handle
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|USB_MAJOR
comma
id|USB_SKEL_MINOR_BASE
op_plus
id|dev-&gt;minor
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
op_or
id|S_IWGRP
op_or
id|S_IROTH
comma
op_amp
id|skel_fops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* let the user know what node this device is now attached to */
id|info
(paren
l_string|&quot;USB Skeleton device now attached to USBSkel%d&quot;
comma
id|dev-&gt;minor
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
id|error
suffix:colon
id|skel_delete
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|exit_minor
suffix:colon
id|usb_deregister_dev
(paren
l_int|1
comma
id|minor
)paren
suffix:semicolon
m_exit
suffix:colon
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|dev_set_drvdata
(paren
op_amp
id|interface-&gt;dev
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;skel_disconnect&n; *&n; *&t;Called by the usb core when the device is removed from the system.&n; */
DECL|function|skel_disconnect
r_static
r_void
id|skel_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
)paren
(brace
r_struct
id|usb_skel
op_star
id|dev
suffix:semicolon
r_int
id|minor
suffix:semicolon
id|dev
op_assign
id|dev_get_drvdata
(paren
op_amp
id|interface-&gt;dev
)paren
suffix:semicolon
id|dev_set_drvdata
(paren
op_amp
id|interface-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
suffix:semicolon
id|down
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|minor
op_assign
id|dev-&gt;minor
suffix:semicolon
multiline_comment|/* remove our devfs node */
id|devfs_unregister
(paren
id|dev-&gt;devfs
)paren
suffix:semicolon
multiline_comment|/* give back our dynamic minor */
id|usb_deregister_dev
(paren
l_int|1
comma
id|minor
)paren
suffix:semicolon
multiline_comment|/* if the device is not opened, then we clean up right now */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;open_count
)paren
(brace
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|skel_delete
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;udev
op_assign
l_int|NULL
suffix:semicolon
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
)brace
id|info
c_func
(paren
l_string|&quot;USB Skeleton #%d now disconnected&quot;
comma
id|minor
)paren
suffix:semicolon
id|up
(paren
op_amp
id|minor_table_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;usb_skel_init&n; */
DECL|function|usb_skel_init
r_static
r_int
id|__init
id|usb_skel_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
multiline_comment|/* register this driver with the USB subsystem */
id|result
op_assign
id|usb_register
c_func
(paren
op_amp
id|skel_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usb_register failed for the &quot;
id|__FILE__
l_string|&quot; driver. Error number %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;usb_skel_exit&n; */
DECL|function|usb_skel_exit
r_static
r_void
id|__exit
id|usb_skel_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* deregister this driver with the USB subsystem */
id|usb_deregister
c_func
(paren
op_amp
id|skel_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_skel_init
id|module_init
(paren
id|usb_skel_init
)paren
suffix:semicolon
DECL|variable|usb_skel_exit
id|module_exit
(paren
id|usb_skel_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
