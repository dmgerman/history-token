multiline_comment|/***************************************************************************** &n; *                          USBLCD Kernel Driver                             *&n; *        See http://www.usblcd.de for Hardware and Documentation.           *&n; *                            Version 1.03                                   *&n; *             (C) 2002 Adams IT Services &lt;info@usblcd.de&gt;                   *&n; *                                                                           *&n; *     This file is licensed under the GPL. See COPYING in the package.      *&n; * Based on rio500.c by Cesar Miquel (miquel@df.uba.ar) which is based on    *&n; * hp_scanner.c by David E. Nelson (dnelson@jump.net)                        *&n; *                                                                           *&n; * 23.7.02 RA changed minor device number to the official assigned one       *&n; *****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;USBLCD Driver Version 1.03&quot;
DECL|macro|USBLCD_MINOR
mdefine_line|#define USBLCD_MINOR&t;&t;144
DECL|macro|IOCTL_GET_HARD_VERSION
mdefine_line|#define IOCTL_GET_HARD_VERSION&t;1
DECL|macro|IOCTL_GET_DRV_VERSION
mdefine_line|#define IOCTL_GET_DRV_VERSION&t;2
multiline_comment|/* stall/wait timeout for USBLCD */
DECL|macro|NAK_TIMEOUT
mdefine_line|#define NAK_TIMEOUT&t;(10*HZ)
DECL|macro|IBUF_SIZE
mdefine_line|#define IBUF_SIZE&t;0x1000
DECL|macro|OBUF_SIZE
mdefine_line|#define OBUF_SIZE&t;0x10000
DECL|struct|lcd_usb_data
r_struct
id|lcd_usb_data
(brace
DECL|member|lcd_dev
r_struct
id|usb_device
op_star
id|lcd_dev
suffix:semicolon
multiline_comment|/* init: probe_lcd */
DECL|member|ifnum
r_int
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* Interface number of the USB device */
DECL|member|isopen
r_int
id|isopen
suffix:semicolon
multiline_comment|/* nz if open */
DECL|member|present
r_int
id|present
suffix:semicolon
multiline_comment|/* Device is present on the bus */
DECL|member|obuf
DECL|member|ibuf
r_char
op_star
id|obuf
comma
op_star
id|ibuf
suffix:semicolon
multiline_comment|/* transfer buffers */
DECL|member|bulk_in_ep
DECL|member|bulk_out_ep
r_char
id|bulk_in_ep
comma
id|bulk_out_ep
suffix:semicolon
multiline_comment|/* Endpoint assignments */
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
multiline_comment|/* for timeouts */
)brace
suffix:semicolon
DECL|variable|lcd_instance
r_static
r_struct
id|lcd_usb_data
id|lcd_instance
suffix:semicolon
DECL|function|open_lcd
r_static
r_int
id|open_lcd
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
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
r_if
c_cond
(paren
id|lcd-&gt;isopen
op_logical_or
op_logical_neg
id|lcd-&gt;present
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|lcd-&gt;isopen
op_assign
l_int|1
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|lcd-&gt;wait_q
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USBLCD opened.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|close_lcd
r_static
r_int
id|close_lcd
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
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
id|lcd-&gt;isopen
op_assign
l_int|0
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USBLCD closed.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ioctl_lcd
id|ioctl_lcd
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
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|buf
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Sanity check to make sure lcd is connected, powered, etc */
r_if
c_cond
(paren
id|lcd
op_eq
l_int|NULL
op_logical_or
id|lcd-&gt;present
op_eq
l_int|0
op_logical_or
id|lcd-&gt;lcd_dev
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
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
id|i
op_assign
(paren
id|lcd-&gt;lcd_dev
)paren
op_member_access_from_pointer
id|descriptor.bcdDevice
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%1d%1d.%1d%1d&quot;
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
r_static
id|ssize_t
DECL|function|write_lcd
id|write_lcd
c_func
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
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
r_int
r_int
id|copy_size
suffix:semicolon
r_int
r_int
id|bytes_written
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|partial
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|maxretry
suffix:semicolon
multiline_comment|/* Sanity check to make sure lcd is connected, powered, etc */
r_if
c_cond
(paren
id|lcd
op_eq
l_int|NULL
op_logical_or
id|lcd-&gt;present
op_eq
l_int|0
op_logical_or
id|lcd-&gt;lcd_dev
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_do
(brace
r_int
r_int
id|thistime
suffix:semicolon
r_char
op_star
id|obuf
op_assign
id|lcd-&gt;obuf
suffix:semicolon
id|thistime
op_assign
id|copy_size
op_assign
(paren
id|count
op_ge
id|OBUF_SIZE
)paren
ques
c_cond
id|OBUF_SIZE
suffix:colon
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|lcd-&gt;obuf
comma
id|buffer
comma
id|copy_size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|maxretry
op_assign
l_int|5
suffix:semicolon
r_while
c_loop
(paren
id|thistime
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lcd-&gt;lcd_dev
)paren
r_return
op_minus
id|ENODEV
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
(brace
r_return
id|bytes_written
ques
c_cond
id|bytes_written
suffix:colon
op_minus
id|EINTR
suffix:semicolon
)brace
id|result
op_assign
id|usb_bulk_msg
c_func
(paren
id|lcd-&gt;lcd_dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|lcd-&gt;lcd_dev
comma
l_int|1
)paren
comma
id|obuf
comma
id|thistime
comma
op_amp
id|partial
comma
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;write stats: result:%d thistime:%lu partial:%u&quot;
comma
id|result
comma
id|thistime
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ETIMEDOUT
)paren
(brace
multiline_comment|/* NAK - so hold for a while */
r_if
c_cond
(paren
op_logical_neg
id|maxretry
op_decrement
)paren
(brace
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|lcd
op_member_access_from_pointer
id|wait_q
comma
id|NAK_TIMEOUT
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|result
op_logical_and
id|partial
)paren
(brace
id|obuf
op_add_assign
id|partial
suffix:semicolon
id|thistime
op_sub_assign
id|partial
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Write Whoops - %x&quot;
comma
id|result
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|bytes_written
op_add_assign
id|copy_size
suffix:semicolon
id|count
op_sub_assign
id|copy_size
suffix:semicolon
id|buffer
op_add_assign
id|copy_size
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
suffix:semicolon
r_return
id|bytes_written
ques
c_cond
id|bytes_written
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|read_lcd
id|read_lcd
c_func
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
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
id|ssize_t
id|read_count
suffix:semicolon
r_int
r_int
id|partial
suffix:semicolon
r_int
id|this_read
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|maxretry
op_assign
l_int|10
suffix:semicolon
r_char
op_star
id|ibuf
op_assign
id|lcd-&gt;ibuf
suffix:semicolon
multiline_comment|/* Sanity check to make sure lcd is connected, powered, etc */
r_if
c_cond
(paren
id|lcd
op_eq
l_int|NULL
op_logical_or
id|lcd-&gt;present
op_eq
l_int|0
op_logical_or
id|lcd-&gt;lcd_dev
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|read_count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_return
id|read_count
ques
c_cond
id|read_count
suffix:colon
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|lcd-&gt;lcd_dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|this_read
op_assign
(paren
id|count
op_ge
id|IBUF_SIZE
)paren
ques
c_cond
id|IBUF_SIZE
suffix:colon
id|count
suffix:semicolon
id|result
op_assign
id|usb_bulk_msg
c_func
(paren
id|lcd-&gt;lcd_dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|lcd-&gt;lcd_dev
comma
l_int|0
)paren
comma
id|ibuf
comma
id|this_read
comma
op_amp
id|partial
comma
(paren
r_int
)paren
(paren
id|HZ
op_star
l_int|8
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
id|KERN_DEBUG
l_string|&quot;read stats: result:%d this_read:%u partial:%u&quot;
comma
id|result
comma
id|this_read
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|partial
)paren
(brace
id|count
op_assign
id|this_read
op_assign
id|partial
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ETIMEDOUT
op_logical_or
id|result
op_eq
l_int|15
)paren
(brace
multiline_comment|/* FIXME: 15 ??? */
r_if
c_cond
(paren
op_logical_neg
id|maxretry
op_decrement
)paren
(brace
id|err
c_func
(paren
l_string|&quot;read_lcd: maxretry timeout&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|lcd-&gt;wait_q
comma
id|NAK_TIMEOUT
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
op_ne
op_minus
id|EREMOTEIO
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Read Whoops - result:%u partial:%u this_read:%u&quot;
comma
id|result
comma
id|partial
comma
id|this_read
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|this_read
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
id|ibuf
comma
id|this_read
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|count
op_sub_assign
id|this_read
suffix:semicolon
id|read_count
op_add_assign
id|this_read
suffix:semicolon
id|buffer
op_add_assign
id|this_read
suffix:semicolon
)brace
)brace
r_return
id|read_count
suffix:semicolon
)brace
r_static
r_struct
DECL|variable|usb_lcd_fops
id|file_operations
id|usb_lcd_fops
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
id|read_lcd
comma
dot
id|write
op_assign
id|write_lcd
comma
dot
id|ioctl
op_assign
id|ioctl_lcd
comma
dot
id|open
op_assign
id|open_lcd
comma
dot
id|release
op_assign
id|close_lcd
comma
)brace
suffix:semicolon
DECL|variable|usb_lcd_class
r_static
r_struct
id|usb_class_driver
id|usb_lcd_class
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
id|usb_lcd_fops
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
comma
dot
id|minor_base
op_assign
id|USBLCD_MINOR
comma
)brace
suffix:semicolon
DECL|function|probe_lcd
r_static
r_int
id|probe_lcd
c_func
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
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;descriptor.idProduct
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
r_if
c_cond
(paren
id|lcd-&gt;present
op_eq
l_int|1
)paren
(brace
id|warn
c_func
(paren
id|KERN_INFO
l_string|&quot;Multiple USBLCDs are not supported!&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|i
op_assign
id|dev-&gt;descriptor.bcdDevice
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
id|dev-&gt;devnum
)paren
suffix:semicolon
id|retval
op_assign
id|usb_register_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_lcd_class
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
l_string|&quot;Not able to get a minor for this device.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|lcd-&gt;present
op_assign
l_int|1
suffix:semicolon
id|lcd-&gt;lcd_dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lcd-&gt;obuf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|OBUF_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;probe_lcd: Not enough memory for the output buffer&quot;
)paren
suffix:semicolon
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_lcd_class
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;probe_lcd: obuf address:%p&quot;
comma
id|lcd-&gt;obuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lcd-&gt;ibuf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|IBUF_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;probe_lcd: Not enough memory for the input buffer&quot;
)paren
suffix:semicolon
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_lcd_class
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lcd-&gt;obuf
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;probe_lcd: ibuf address:%p&quot;
comma
id|lcd-&gt;ibuf
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
id|lcd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disconnect_lcd
r_static
r_void
id|disconnect_lcd
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|lcd_usb_data
op_star
id|lcd
op_assign
id|usb_get_intfdata
(paren
id|intf
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lcd
)paren
(brace
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_lcd_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lcd-&gt;isopen
)paren
(brace
id|lcd-&gt;isopen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* better let it finish - the release will do whats needed */
id|lcd-&gt;lcd_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|lcd-&gt;ibuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|lcd-&gt;obuf
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USBLCD disconnected.&quot;
)paren
suffix:semicolon
id|lcd-&gt;present
op_assign
l_int|0
suffix:semicolon
)brace
)brace
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
r_static
r_struct
DECL|variable|lcd_driver
id|usb_driver
id|lcd_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usblcd&quot;
comma
dot
id|probe
op_assign
(paren
r_void
op_star
)paren
id|probe_lcd
comma
dot
id|disconnect
op_assign
id|disconnect_lcd
comma
dot
id|id_table
op_assign
id|id_table
comma
)brace
suffix:semicolon
DECL|function|usb_lcd_init
r_int
id|usb_lcd_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|lcd_driver
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s (C) Adams IT Services http://www.usblcd.de&quot;
comma
id|DRIVER_VERSION
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USBLCD support registered.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_lcd_cleanup
r_void
id|usb_lcd_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|lcd_usb_data
op_star
id|lcd
op_assign
op_amp
id|lcd_instance
suffix:semicolon
id|lcd-&gt;present
op_assign
l_int|0
suffix:semicolon
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
DECL|variable|usb_lcd_cleanup
id|module_exit
c_func
(paren
id|usb_lcd_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Adams IT Services &lt;info@usblcd.de&gt;&quot;
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
