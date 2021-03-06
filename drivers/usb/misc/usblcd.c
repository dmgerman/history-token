multiline_comment|/*****************************************************************************&n; *                          USBLCD Kernel Driver                             *&n; *                            Version 1.05                                   *&n; *             (C) 2005 Georges Toth &lt;g.toth@e-biz.lu&gt;                       *&n; *                                                                           *&n; *     This file is licensed under the GPL. See COPYING in the package.      *&n; * Based on usb-skeleton.c 2.0 by Greg Kroah-Hartman (greg@kroah.com)        *&n; *                                                                           *&n; *                                                                           *&n; * 28.02.05 Complete rewrite of the original usblcd.c driver,                *&n; *          based on usb_skeleton.c.                                         *&n; *          This new driver allows more than one USB-LCD to be connected     *&n; *          and controlled, at once                                          *&n; *****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;USBLCD Driver Version 1.05&quot;
DECL|macro|USBLCD_MINOR
mdefine_line|#define USBLCD_MINOR&t;&t;144
DECL|macro|IOCTL_GET_HARD_VERSION
mdefine_line|#define IOCTL_GET_HARD_VERSION&t;1
DECL|macro|IOCTL_GET_DRV_VERSION
mdefine_line|#define IOCTL_GET_DRV_VERSION&t;2
DECL|variable|id_table
r_static
r_struct
id|usb_device_id
id|id_table
(braket
)braket
op_assign
(brace
(brace
dot
id|idVendor
op_assign
l_int|0x10D2
comma
dot
id|match_flags
op_assign
id|USB_DEVICE_ID_MATCH_VENDOR
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|id_table
)paren
suffix:semicolon
DECL|struct|usb_lcd
r_struct
id|usb_lcd
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
multiline_comment|/* init: probe_lcd */
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
DECL|member|bulk_out_endpointAddr
id|__u8
id|bulk_out_endpointAddr
suffix:semicolon
multiline_comment|/* the address of the bulk out endpoint */
DECL|member|kref
r_struct
id|kref
id|kref
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_lcd_dev
mdefine_line|#define to_lcd_dev(d) container_of(d, struct usb_lcd, kref)
DECL|variable|lcd_driver
r_static
r_struct
id|usb_driver
id|lcd_driver
suffix:semicolon
DECL|function|lcd_delete
r_static
r_void
id|lcd_delete
c_func
(paren
r_struct
id|kref
op_star
id|kref
)paren
(brace
r_struct
id|usb_lcd
op_star
id|dev
op_assign
id|to_lcd_dev
c_func
(paren
id|kref
)paren
suffix:semicolon
id|usb_put_dev
c_func
(paren
id|dev-&gt;udev
)paren
suffix:semicolon
id|kfree
(paren
id|dev-&gt;bulk_in_buffer
)paren
suffix:semicolon
id|kfree
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|lcd_open
r_static
r_int
id|lcd_open
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
id|usb_lcd
op_star
id|dev
suffix:semicolon
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
r_int
id|subminor
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|subminor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
id|interface
op_assign
id|usb_find_interface
c_func
(paren
op_amp
id|lcd_driver
comma
id|subminor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interface
)paren
(brace
id|err
(paren
l_string|&quot;USBLCD: %s - error, can&squot;t find device for minor %d&quot;
comma
id|__FUNCTION__
comma
id|subminor
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
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
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* increment our usage count for the device */
id|kref_get
c_func
(paren
op_amp
id|dev-&gt;kref
)paren
suffix:semicolon
multiline_comment|/* save our object in the file&squot;s private structure */
id|file-&gt;private_data
op_assign
id|dev
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|lcd_release
r_static
r_int
id|lcd_release
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
id|usb_lcd
op_star
id|dev
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_lcd
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
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* decrement the count on our device */
id|kref_put
c_func
(paren
op_amp
id|dev-&gt;kref
comma
id|lcd_delete
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lcd_read
r_static
id|ssize_t
id|lcd_read
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
id|usb_lcd
op_star
id|dev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|bytes_read
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_lcd
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
multiline_comment|/* do a blocking bulk read to get data from the device */
id|retval
op_assign
id|usb_bulk_msg
c_func
(paren
id|dev-&gt;udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dev-&gt;udev
comma
id|dev-&gt;bulk_in_endpointAddr
)paren
comma
id|dev-&gt;bulk_in_buffer
comma
id|min
c_func
(paren
id|dev-&gt;bulk_in_size
comma
id|count
)paren
comma
op_amp
id|bytes_read
comma
l_int|10000
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
c_func
(paren
id|buffer
comma
id|dev-&gt;bulk_in_buffer
comma
id|bytes_read
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
id|bytes_read
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|lcd_ioctl
r_static
r_int
id|lcd_ioctl
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
id|usb_lcd
op_star
id|dev
suffix:semicolon
id|u16
id|bcdDevice
suffix:semicolon
r_char
id|buf
(braket
l_int|30
)braket
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_lcd
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
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|IOCTL_GET_HARD_VERSION
suffix:colon
id|bcdDevice
op_assign
id|le16_to_cpu
c_func
(paren
(paren
id|dev-&gt;udev
)paren
op_member_access_from_pointer
id|descriptor.bcdDevice
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%1d%1d.%1d%1d&quot;
comma
(paren
id|bcdDevice
op_amp
l_int|0xF000
)paren
op_rshift
l_int|12
comma
(paren
id|bcdDevice
op_amp
l_int|0xF00
)paren
op_rshift
l_int|8
comma
(paren
id|bcdDevice
op_amp
l_int|0xF0
)paren
op_rshift
l_int|4
comma
(paren
id|bcdDevice
op_amp
l_int|0xF
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
id|buf
comma
id|strlen
c_func
(paren
id|buf
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_GET_DRV_VERSION
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
id|DRIVER_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
id|buf
comma
id|strlen
c_func
(paren
id|buf
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lcd_write_bulk_callback
r_static
r_void
id|lcd_write_bulk_callback
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|usb_lcd
op_star
id|dev
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_lcd
op_star
)paren
id|urb-&gt;context
suffix:semicolon
multiline_comment|/* sync/async unlink faults aren&squot;t errors */
r_if
c_cond
(paren
id|urb-&gt;status
op_logical_and
op_logical_neg
(paren
id|urb-&gt;status
op_eq
op_minus
id|ENOENT
op_logical_or
id|urb-&gt;status
op_eq
op_minus
id|ECONNRESET
op_logical_or
id|urb-&gt;status
op_eq
op_minus
id|ESHUTDOWN
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;USBLCD: %s - nonzero write bulk status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
)brace
multiline_comment|/* free up our allocated buffer */
id|usb_buffer_free
c_func
(paren
id|urb-&gt;dev
comma
id|urb-&gt;transfer_buffer_length
comma
id|urb-&gt;transfer_buffer
comma
id|urb-&gt;transfer_dma
)paren
suffix:semicolon
)brace
DECL|function|lcd_write
r_static
id|ssize_t
id|lcd_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|user_buffer
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
id|usb_lcd
op_star
id|dev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|usb_lcd
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
multiline_comment|/* verify that we actually have some data to write */
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
m_exit
suffix:semicolon
multiline_comment|/* create a urb, and a buffer for it, and copy the data to the urb */
id|urb
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
id|urb
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
id|buf
op_assign
id|usb_buffer_alloc
c_func
(paren
id|dev-&gt;udev
comma
id|count
comma
id|GFP_KERNEL
comma
op_amp
id|urb-&gt;transfer_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
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
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|user_buffer
comma
id|count
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* initialize the urb properly */
id|usb_fill_bulk_urb
c_func
(paren
id|urb
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
id|buf
comma
id|count
comma
id|lcd_write_bulk_callback
comma
id|dev
)paren
suffix:semicolon
id|urb-&gt;transfer_flags
op_or_assign
id|URB_NO_TRANSFER_DMA_MAP
suffix:semicolon
multiline_comment|/* send the data out the bulk port */
id|retval
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
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
l_string|&quot;USBLCD: %s - failed submitting write urb, error %d&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* release our reference to this urb, the USB core will eventually free it entirely */
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|count
suffix:semicolon
id|error
suffix:colon
id|usb_buffer_free
c_func
(paren
id|dev-&gt;udev
comma
id|count
comma
id|buf
comma
id|urb-&gt;transfer_dma
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|lcd_fops
r_static
r_struct
id|file_operations
id|lcd_fops
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
id|lcd_read
comma
dot
id|write
op_assign
id|lcd_write
comma
dot
id|open
op_assign
id|lcd_open
comma
dot
id|ioctl
op_assign
id|lcd_ioctl
comma
dot
id|release
op_assign
id|lcd_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  * usb class driver info in order to get a minor number from the usb core,&n; *   * and to have the device registered with devfs and the driver core&n; *    */
DECL|variable|lcd_class
r_static
r_struct
id|usb_class_driver
id|lcd_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb/lcd%d&quot;
comma
dot
id|fops
op_assign
op_amp
id|lcd_fops
comma
dot
id|mode
op_assign
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
dot
id|minor_base
op_assign
id|USBLCD_MINOR
comma
)brace
suffix:semicolon
DECL|function|lcd_probe
r_static
r_int
id|lcd_probe
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
id|usb_lcd
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
id|i
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENOMEM
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
(brace
id|err
c_func
(paren
l_string|&quot;Out of memory&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
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
id|kref_init
c_func
(paren
op_amp
id|dev-&gt;kref
)paren
suffix:semicolon
id|dev-&gt;udev
op_assign
id|usb_get_dev
c_func
(paren
id|interface_to_usbdev
c_func
(paren
id|interface
)paren
)paren
suffix:semicolon
id|dev-&gt;interface
op_assign
id|interface
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|dev-&gt;udev-&gt;descriptor.idProduct
)paren
op_ne
l_int|0x0001
)paren
(brace
id|warn
c_func
(paren
id|KERN_INFO
l_string|&quot;USBLCD model not supported.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* set up the endpoint information */
multiline_comment|/* use only the first bulk-in and bulk-out endpoints */
id|iface_desc
op_assign
id|interface-&gt;cur_altsetting
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
id|iface_desc-&gt;desc.bNumEndpoints
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
l_string|&quot;Could not allocate bulk_in_buffer&quot;
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
op_logical_neg
id|dev-&gt;bulk_out_endpointAddr
op_logical_and
op_logical_neg
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
multiline_comment|/* we found a bulk out endpoint */
id|dev-&gt;bulk_out_endpointAddr
op_assign
id|endpoint-&gt;bEndpointAddress
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;bulk_in_endpointAddr
op_logical_and
id|dev-&gt;bulk_out_endpointAddr
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Could not find both bulk-in and bulk-out endpoints&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* save our data pointer in this interface device */
id|usb_set_intfdata
c_func
(paren
id|interface
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* we can register the device now, as it is ready */
id|retval
op_assign
id|usb_register_dev
c_func
(paren
id|interface
comma
op_amp
id|lcd_class
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
c_func
(paren
l_string|&quot;Not able to get a minor for this device.&quot;
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
r_goto
id|error
suffix:semicolon
)brace
id|i
op_assign
id|le16_to_cpu
c_func
(paren
id|dev-&gt;udev-&gt;descriptor.bcdDevice
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USBLCD Version %1d%1d.%1d%1d found at address %d&quot;
comma
(paren
id|i
op_amp
l_int|0xF000
)paren
op_rshift
l_int|12
comma
(paren
id|i
op_amp
l_int|0xF00
)paren
op_rshift
l_int|8
comma
(paren
id|i
op_amp
l_int|0xF0
)paren
op_rshift
l_int|4
comma
(paren
id|i
op_amp
l_int|0xF
)paren
comma
id|dev-&gt;udev-&gt;devnum
)paren
suffix:semicolon
multiline_comment|/* let the user know what node this device is now attached to */
id|info
c_func
(paren
l_string|&quot;USB LCD device now attached to USBLCD-%d&quot;
comma
id|interface-&gt;minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|dev
)paren
id|kref_put
c_func
(paren
op_amp
id|dev-&gt;kref
comma
id|lcd_delete
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|lcd_disconnect
r_static
r_void
id|lcd_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
)paren
(brace
r_struct
id|usb_lcd
op_star
id|dev
suffix:semicolon
r_int
id|minor
op_assign
id|interface-&gt;minor
suffix:semicolon
multiline_comment|/* prevent skel_open() from racing skel_disconnect() */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/* give back our minor */
id|usb_deregister_dev
c_func
(paren
id|interface
comma
op_amp
id|lcd_class
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* decrement our usage count */
id|kref_put
c_func
(paren
op_amp
id|dev-&gt;kref
comma
id|lcd_delete
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USB LCD #%d now disconnected&quot;
comma
id|minor
)paren
suffix:semicolon
)brace
DECL|variable|lcd_driver
r_static
r_struct
id|usb_driver
id|lcd_driver
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
l_string|&quot;usblcd&quot;
comma
dot
id|probe
op_assign
id|lcd_probe
comma
dot
id|disconnect
op_assign
id|lcd_disconnect
comma
dot
id|id_table
op_assign
id|id_table
comma
)brace
suffix:semicolon
DECL|function|usb_lcd_init
r_static
r_int
id|__init
id|usb_lcd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|usb_register
c_func
(paren
op_amp
id|lcd_driver
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
l_string|&quot;usb_register failed. Error number %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|usb_lcd_exit
r_static
r_void
id|__exit
id|usb_lcd_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|lcd_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_lcd_init
id|module_init
c_func
(paren
id|usb_lcd_init
)paren
suffix:semicolon
DECL|variable|usb_lcd_exit
id|module_exit
c_func
(paren
id|usb_lcd_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Georges Toth &lt;g.toth@e-biz.lu&gt;&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_VERSION
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
