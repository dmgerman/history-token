multiline_comment|/* Siemens ID Mouse driver v0.5&n;&n;  This program is free software; you can redistribute it and/or&n;  modify it under the terms of the GNU General Public License as&n;  published by the Free Software Foundation; either version 2 of&n;  the License, or (at your option) any later version.&n;&n;  Copyright (C) 2004-5 by Florian &squot;Floe&squot; Echtler  &lt;echtler@fs.tum.de&gt;&n;                      and Andreas  &squot;ad&squot;  Deresch &lt;aderesch@fs.tum.de&gt;&n;&n;  Derived from the USB Skeleton driver 1.1,&n;  Copyright (C) 2003 Greg Kroah-Hartman (greg@kroah.com)&n;&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|WIDTH
mdefine_line|#define WIDTH 225
DECL|macro|HEIGHT
mdefine_line|#define HEIGHT 288
DECL|macro|HEADER
mdefine_line|#define HEADER &quot;P5 225 288 255 &quot;
DECL|macro|IMGSIZE
mdefine_line|#define IMGSIZE ((WIDTH * HEIGHT) + sizeof(HEADER)-1)
multiline_comment|/* Version Information */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;0.5&quot;
DECL|macro|DRIVER_SHORT
mdefine_line|#define DRIVER_SHORT   &quot;idmouse&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR  &quot;Florian &squot;Floe&squot; Echtler &lt;echtler@fs.tum.de&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC    &quot;Siemens ID Mouse FingerTIP Sensor Driver&quot;
multiline_comment|/* Siemens ID Mouse */
DECL|macro|USB_IDMOUSE_VENDOR_ID
mdefine_line|#define USB_IDMOUSE_VENDOR_ID  0x0681
DECL|macro|USB_IDMOUSE_PRODUCT_ID
mdefine_line|#define USB_IDMOUSE_PRODUCT_ID 0x0005
multiline_comment|/* we still need a minor number */
DECL|macro|USB_IDMOUSE_MINOR_BASE
mdefine_line|#define USB_IDMOUSE_MINOR_BASE 132
DECL|variable|idmouse_table
r_static
r_struct
id|usb_device_id
id|idmouse_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_IDMOUSE_VENDOR_ID
comma
id|USB_IDMOUSE_PRODUCT_ID
)paren
)brace
comma
(brace
)brace
multiline_comment|/* null entry at the end */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|idmouse_table
)paren
suffix:semicolon
multiline_comment|/* structure to hold all of our device specific stuff */
DECL|struct|usb_idmouse
r_struct
id|usb_idmouse
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
DECL|member|open
r_int
id|open
suffix:semicolon
multiline_comment|/* if the port is open or not */
DECL|member|present
r_int
id|present
suffix:semicolon
multiline_comment|/* if the device is not disconnected */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* locks this structure */
)brace
suffix:semicolon
multiline_comment|/* local function prototypes */
r_static
id|ssize_t
id|idmouse_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
id|idmouse_open
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
suffix:semicolon
r_static
r_int
id|idmouse_release
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
suffix:semicolon
r_static
r_int
id|idmouse_probe
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
suffix:semicolon
r_static
r_void
id|idmouse_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
)paren
suffix:semicolon
multiline_comment|/* file operation pointers */
DECL|variable|idmouse_fops
r_static
r_struct
id|file_operations
id|idmouse_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|idmouse_read
comma
dot
id|open
op_assign
id|idmouse_open
comma
dot
id|release
op_assign
id|idmouse_release
comma
)brace
suffix:semicolon
multiline_comment|/* class driver information for devfs */
DECL|variable|idmouse_class
r_static
r_struct
id|usb_class_driver
id|idmouse_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb/idmouse%d&quot;
comma
dot
id|fops
op_assign
op_amp
id|idmouse_fops
comma
dot
id|mode
op_assign
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IRGRP
op_or
id|S_IROTH
comma
multiline_comment|/* filemode (char, 444) */
dot
id|minor_base
op_assign
id|USB_IDMOUSE_MINOR_BASE
comma
)brace
suffix:semicolon
multiline_comment|/* usb specific object needed to register this driver with the usb subsystem */
DECL|variable|idmouse_driver
r_static
r_struct
id|usb_driver
id|idmouse_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
id|DRIVER_SHORT
comma
dot
id|probe
op_assign
id|idmouse_probe
comma
dot
id|disconnect
op_assign
id|idmouse_disconnect
comma
dot
id|id_table
op_assign
id|idmouse_table
comma
)brace
suffix:semicolon
singleline_comment|// prevent races between open() and disconnect()
r_static
id|DECLARE_MUTEX
c_func
(paren
id|disconnect_sem
)paren
suffix:semicolon
DECL|function|idmouse_create_image
r_static
r_int
id|idmouse_create_image
c_func
(paren
r_struct
id|usb_idmouse
op_star
id|dev
)paren
(brace
r_int
id|bytes_read
op_assign
l_int|0
suffix:semicolon
r_int
id|bulk_read
op_assign
l_int|0
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bulk_in_size
OL
r_sizeof
(paren
id|HEADER
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;bulk_in_buffer
comma
id|HEADER
comma
r_sizeof
(paren
id|HEADER
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|bytes_read
op_add_assign
r_sizeof
(paren
id|HEADER
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Dump the setup packets. Yes, they are uncommented, simply &n;&t;   because they were sniffed under Windows using SnoopyPro.&n;&t;   I _guess_ that 0x22 is a kind of reset command and 0x21 &n;&t;   means init..&n;&t;*/
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x21
comma
l_int|0x42
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x20
comma
l_int|0x42
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x22
comma
l_int|0x42
comma
l_int|0x0000
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x21
comma
l_int|0x42
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x20
comma
l_int|0x42
comma
l_int|0x0001
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x20
comma
l_int|0x42
comma
l_int|0x0000
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* loop over a blocking bulk read to get data from the device */
r_while
c_loop
(paren
id|bytes_read
OL
id|IMGSIZE
)paren
(brace
id|result
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
op_plus
id|bytes_read
comma
id|dev-&gt;bulk_in_size
comma
op_amp
id|bulk_read
comma
id|HZ
op_star
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
id|bytes_read
op_add_assign
id|bulk_read
suffix:semicolon
)brace
multiline_comment|/* reset the device */
id|result
op_assign
id|usb_control_msg
(paren
id|dev-&gt;udev
comma
id|usb_sndctrlpipe
(paren
id|dev-&gt;udev
comma
l_int|0
)paren
comma
l_int|0x22
comma
l_int|0x42
comma
l_int|0x0000
comma
l_int|0x0002
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* should be IMGSIZE == 64815 */
id|dbg
c_func
(paren
l_string|&quot;read %d bytes fingerprint data&quot;
comma
id|bytes_read
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idmouse_delete
r_static
r_inline
r_void
id|idmouse_delete
c_func
(paren
r_struct
id|usb_idmouse
op_star
id|dev
)paren
(brace
id|kfree
c_func
(paren
id|dev-&gt;bulk_in_buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|idmouse_open
r_static
r_int
id|idmouse_open
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
r_struct
id|usb_idmouse
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* prevent disconnects */
id|down
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
multiline_comment|/* get the interface from minor number and driver information */
id|interface
op_assign
id|usb_find_interface
(paren
op_amp
id|idmouse_driver
comma
id|iminor
(paren
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interface
)paren
(brace
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* get the device information block from the interface */
id|dev
op_assign
id|usb_get_intfdata
c_func
(paren
id|interface
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* lock this device */
id|down
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* check if already open */
r_if
c_cond
(paren
id|dev-&gt;open
)paren
(brace
multiline_comment|/* already open, so fail */
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* create a new image and check for success */
id|result
op_assign
id|idmouse_create_image
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* increment our usage count for the driver */
op_increment
id|dev-&gt;open
suffix:semicolon
multiline_comment|/* save our object in the file&squot;s private structure */
id|file-&gt;private_data
op_assign
id|dev
suffix:semicolon
)brace
id|error
suffix:colon
multiline_comment|/* unlock this device */
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* unlock the disconnect semaphore */
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|idmouse_release
r_static
r_int
id|idmouse_release
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
r_struct
id|usb_idmouse
op_star
id|dev
suffix:semicolon
multiline_comment|/* prevent a race condition with open() */
id|down
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_idmouse
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
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* lock our device */
id|down
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* are we really open? */
r_if
c_cond
(paren
id|dev-&gt;open
op_le
l_int|0
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
op_decrement
id|dev-&gt;open
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;present
)paren
(brace
multiline_comment|/* the device was unplugged before the file was released */
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|idmouse_delete
c_func
(paren
id|dev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idmouse_read
r_static
id|ssize_t
id|idmouse_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
id|usb_idmouse
op_star
id|dev
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_idmouse
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
singleline_comment|// lock this object
id|down
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
singleline_comment|// verify that the device wasn&squot;t unplugged
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;present
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
r_if
c_cond
(paren
op_star
id|ppos
op_ge
id|IMGSIZE
)paren
(brace
id|up
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|IMGSIZE
op_minus
op_star
id|ppos
)paren
id|count
op_assign
id|IMGSIZE
op_minus
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buffer
comma
id|dev-&gt;bulk_in_buffer
op_plus
op_star
id|ppos
comma
id|count
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|count
suffix:semicolon
)brace
singleline_comment|// unlock the device 
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|idmouse_probe
r_static
r_int
id|idmouse_probe
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
id|usb_idmouse
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|iface_desc
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_int
id|buffer_size
suffix:semicolon
r_int
id|result
suffix:semicolon
multiline_comment|/* check if we have gotten the data or the hid interface */
id|iface_desc
op_assign
op_amp
id|interface-&gt;altsetting
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|iface_desc-&gt;desc.bInterfaceClass
op_ne
l_int|0x0A
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* allocate memory for our device state and initialize it */
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
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
id|init_MUTEX
c_func
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
multiline_comment|/* set up the endpoint information - use only the first bulk-in endpoint */
id|endpoint
op_assign
op_amp
id|iface_desc-&gt;endpoint
(braket
l_int|0
)braket
dot
id|desc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bulk_in_endpointAddr
op_logical_and
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
id|USB_DIR_IN
)paren
op_logical_and
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
id|USB_ENDPOINT_XFERTYPE_MASK
)paren
op_eq
id|USB_ENDPOINT_XFER_BULK
)paren
)paren
(brace
multiline_comment|/* we found a bulk in endpoint */
id|buffer_size
op_assign
id|le16_to_cpu
c_func
(paren
id|endpoint-&gt;wMaxPacketSize
)paren
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
c_func
(paren
id|IMGSIZE
op_plus
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
l_string|&quot;Unable to allocate input buffer.&quot;
)paren
suffix:semicolon
id|idmouse_delete
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;bulk_in_endpointAddr
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Unable to find bulk-in endpoint.&quot;
)paren
suffix:semicolon
id|idmouse_delete
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* allow device read, write and ioctl */
id|dev-&gt;present
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we can register the device now, as it is ready */
id|usb_set_intfdata
c_func
(paren
id|interface
comma
id|dev
)paren
suffix:semicolon
id|result
op_assign
id|usb_register_dev
c_func
(paren
id|interface
comma
op_amp
id|idmouse_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
multiline_comment|/* something prevented us from registering this device */
id|err
c_func
(paren
l_string|&quot;Unble to allocate minor number.&quot;
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|interface
comma
l_int|NULL
)paren
suffix:semicolon
id|idmouse_delete
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* be noisy */
id|dev_info
c_func
(paren
op_amp
id|interface-&gt;dev
comma
l_string|&quot;%s now attached&bslash;n&quot;
comma
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idmouse_disconnect
r_static
r_void
id|idmouse_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
)paren
(brace
r_struct
id|usb_idmouse
op_star
id|dev
suffix:semicolon
multiline_comment|/* prevent races with open() */
id|down
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
multiline_comment|/* get device structure */
id|dev
op_assign
id|usb_get_intfdata
c_func
(paren
id|interface
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|interface
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* lock it */
id|down
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* give back our minor */
id|usb_deregister_dev
c_func
(paren
id|interface
comma
op_amp
id|idmouse_class
)paren
suffix:semicolon
multiline_comment|/* prevent device read, write and ioctl */
id|dev-&gt;present
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* unlock */
id|up
c_func
(paren
op_amp
id|dev-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* if the device is opened, idmouse_release will clean this up */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;open
)paren
id|idmouse_delete
c_func
(paren
id|dev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|disconnect_sem
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s disconnected&quot;
comma
id|DRIVER_DESC
)paren
suffix:semicolon
)brace
DECL|function|usb_idmouse_init
r_static
r_int
id|__init
id|usb_idmouse_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
multiline_comment|/* register this driver with the USB subsystem */
id|result
op_assign
id|usb_register
c_func
(paren
op_amp
id|idmouse_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|err
c_func
(paren
l_string|&quot;Unable to register device (error %d).&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|usb_idmouse_exit
r_static
r_void
id|__exit
id|usb_idmouse_exit
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
id|idmouse_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_idmouse_init
id|module_init
c_func
(paren
id|usb_idmouse_init
)paren
suffix:semicolon
DECL|variable|usb_idmouse_exit
id|module_exit
c_func
(paren
id|usb_idmouse_exit
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
