multiline_comment|/* -*- linux-c -*- */
multiline_comment|/* &n; * Driver for USB Rio 500&n; *&n; * Cesar Miquel (miquel@df.uba.ar)&n; * &n; * based on hp_scanner.c by David E. Nelson (dnelson@jump.net)&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Based upon mouse.c (Brad Keryan) and printer.c (Michael Gee).&n; *&n; * Changelog:&n; * 30/05/2003  replaced lock/unlock kernel with up/down&n; *             Daniele Bellucci  bellucda@tiscali.it&n; * */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &quot;rio500_usb.h&quot;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v1.1&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Cesar Miquel &lt;miquel@df.uba.ar&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Rio 500 driver&quot;
DECL|macro|RIO_MINOR
mdefine_line|#define RIO_MINOR&t;64
multiline_comment|/* stall/wait timeout for rio */
DECL|macro|NAK_TIMEOUT
mdefine_line|#define NAK_TIMEOUT (HZ)
DECL|macro|IBUF_SIZE
mdefine_line|#define IBUF_SIZE 0x1000
multiline_comment|/* Size of the rio buffer */
DECL|macro|OBUF_SIZE
mdefine_line|#define OBUF_SIZE 0x10000
DECL|struct|rio_usb_data
r_struct
id|rio_usb_data
(brace
DECL|member|rio_dev
r_struct
id|usb_device
op_star
id|rio_dev
suffix:semicolon
multiline_comment|/* init: probe_rio */
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
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* general race avoidance */
)brace
suffix:semicolon
DECL|variable|rio_instance
r_static
r_struct
id|rio_usb_data
id|rio_instance
suffix:semicolon
DECL|function|open_rio
r_static
r_int
id|open_rio
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
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rio-&gt;isopen
op_logical_or
op_logical_neg
id|rio-&gt;present
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|rio-&gt;isopen
op_assign
l_int|1
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|rio-&gt;wait_q
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;Rio opened.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|close_rio
r_static
r_int
id|close_rio
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
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
suffix:semicolon
id|rio-&gt;isopen
op_assign
l_int|0
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;Rio closed.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ioctl_rio
id|ioctl_rio
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
id|RioCommand
id|rio_cmd
suffix:semicolon
r_struct
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
suffix:semicolon
r_void
id|__user
op_star
id|data
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|result
comma
id|requesttype
suffix:semicolon
r_int
id|retries
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
multiline_comment|/* Sanity check to make sure rio is connected, powered, etc */
r_if
c_cond
(paren
id|rio
op_eq
l_int|NULL
op_logical_or
id|rio-&gt;present
op_eq
l_int|0
op_logical_or
id|rio-&gt;rio_dev
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
id|err_out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RIO_RECV_COMMAND
suffix:colon
id|data
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rio_cmd
comma
id|data
comma
r_sizeof
(paren
r_struct
id|RioCommand
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rio_cmd.length
template_param
id|PAGE_SIZE
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|rio_cmd.buffer
comma
id|rio_cmd.length
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|requesttype
op_assign
id|rio_cmd.requesttype
op_or
id|USB_DIR_IN
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
suffix:semicolon
id|dbg
(paren
l_string|&quot;sending command:reqtype=%0x req=%0x value=%0x index=%0x len=%0x&quot;
comma
id|requesttype
comma
id|rio_cmd.request
comma
id|rio_cmd.value
comma
id|rio_cmd.index
comma
id|rio_cmd.length
)paren
suffix:semicolon
multiline_comment|/* Send rio control message */
id|retries
op_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|retries
)paren
(brace
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|rio-&gt;rio_dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|rio
op_member_access_from_pointer
id|rio_dev
comma
l_int|0
)paren
comma
id|rio_cmd.request
comma
id|requesttype
comma
id|rio_cmd.value
comma
id|rio_cmd.index
comma
id|buffer
comma
id|rio_cmd.length
comma
id|jiffies_to_msecs
c_func
(paren
id|rio_cmd.timeout
)paren
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
id|retries
op_decrement
suffix:semicolon
r_else
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
l_string|&quot;Error executing ioctrl. code = %d&quot;
comma
id|result
)paren
suffix:semicolon
id|retries
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dbg
c_func
(paren
l_string|&quot;Executed ioctl. Result = %d (data=%02x)&quot;
comma
id|result
comma
id|buffer
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|rio_cmd.buffer
comma
id|buffer
comma
id|rio_cmd.length
)paren
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|retries
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* rio_cmd.buffer contains a raw stream of single byte&n;&t;&t;&t;   data which has been returned from rio.  Data is&n;&t;&t;&t;   interpreted at application level.  For data that&n;&t;&t;&t;   will be cast to data types longer than 1 byte, data&n;&t;&t;&t;   will be little_endian and will potentially need to&n;&t;&t;&t;   be swapped at the app level */
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RIO_SEND_COMMAND
suffix:colon
id|data
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rio_cmd
comma
id|data
comma
r_sizeof
(paren
r_struct
id|RioCommand
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rio_cmd.length
template_param
id|PAGE_SIZE
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|rio_cmd.buffer
comma
id|rio_cmd.length
)paren
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|requesttype
op_assign
id|rio_cmd.requesttype
op_or
id|USB_DIR_OUT
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;sending command: reqtype=%0x req=%0x value=%0x index=%0x len=%0x&quot;
comma
id|requesttype
comma
id|rio_cmd.request
comma
id|rio_cmd.value
comma
id|rio_cmd.index
comma
id|rio_cmd.length
)paren
suffix:semicolon
multiline_comment|/* Send rio control message */
id|retries
op_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|retries
)paren
(brace
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|rio-&gt;rio_dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|rio
op_member_access_from_pointer
id|rio_dev
comma
l_int|0
)paren
comma
id|rio_cmd.request
comma
id|requesttype
comma
id|rio_cmd.value
comma
id|rio_cmd.index
comma
id|buffer
comma
id|rio_cmd.length
comma
id|jiffies_to_msecs
c_func
(paren
id|rio_cmd.timeout
)paren
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
id|retries
op_decrement
suffix:semicolon
r_else
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
l_string|&quot;Error executing ioctrl. code = %d&quot;
comma
id|result
)paren
suffix:semicolon
id|retries
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dbg
c_func
(paren
l_string|&quot;Executed ioctl. Result = %d&quot;
comma
id|result
)paren
suffix:semicolon
id|retries
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|ENOTTY
suffix:semicolon
r_break
suffix:semicolon
)brace
id|err_out
suffix:colon
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|write_rio
id|write_rio
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
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
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
r_int
id|errn
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
multiline_comment|/* Sanity check to make sure rio is connected, powered, etc */
r_if
c_cond
(paren
id|rio
op_eq
l_int|NULL
op_logical_or
id|rio-&gt;present
op_eq
l_int|0
op_logical_or
id|rio-&gt;rio_dev
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
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
id|rio-&gt;obuf
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
id|rio-&gt;obuf
comma
id|buffer
comma
id|copy_size
)paren
)paren
(brace
id|errn
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
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
id|rio-&gt;rio_dev
)paren
(brace
id|errn
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
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
id|rio-&gt;rio_dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|rio-&gt;rio_dev
comma
l_int|2
)paren
comma
id|obuf
comma
id|thistime
comma
op_amp
id|partial
comma
l_int|5000
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
id|errn
op_assign
op_minus
id|ETIME
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|prepare_to_wait
c_func
(paren
op_amp
id|rio-&gt;wait_q
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|NAK_TIMEOUT
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
op_amp
id|rio-&gt;wait_q
comma
op_amp
id|wait
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
id|errn
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
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
id|error
suffix:colon
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
id|errn
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|read_rio
id|read_rio
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
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
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
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
multiline_comment|/* Sanity check to make sure rio is connected, powered, etc */
r_if
c_cond
(paren
id|rio
op_eq
l_int|NULL
op_logical_or
id|rio-&gt;present
op_eq
l_int|0
op_logical_or
id|rio-&gt;rio_dev
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ibuf
op_assign
id|rio-&gt;ibuf
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
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
id|rio-&gt;rio_dev
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
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
id|rio-&gt;rio_dev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|rio-&gt;rio_dev
comma
l_int|1
)paren
comma
id|ibuf
comma
id|this_read
comma
op_amp
id|partial
comma
l_int|8000
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
id|err
c_func
(paren
l_string|&quot;read_rio: maxretry timeout&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
id|prepare_to_wait
c_func
(paren
op_amp
id|rio-&gt;wait_q
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|NAK_TIMEOUT
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
op_amp
id|rio-&gt;wait_q
comma
op_amp
id|wait
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
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
(brace
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
id|read_count
suffix:semicolon
)brace
r_static
r_struct
DECL|variable|usb_rio_fops
id|file_operations
id|usb_rio_fops
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
id|read_rio
comma
dot
id|write
op_assign
id|write_rio
comma
dot
id|ioctl
op_assign
id|ioctl_rio
comma
dot
id|open
op_assign
id|open_rio
comma
dot
id|release
op_assign
id|close_rio
comma
)brace
suffix:semicolon
DECL|variable|usb_rio_class
r_static
r_struct
id|usb_class_driver
id|usb_rio_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb/rio500%d&quot;
comma
dot
id|fops
op_assign
op_amp
id|usb_rio_fops
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
id|RIO_MINOR
comma
)brace
suffix:semicolon
DECL|function|probe_rio
r_static
r_int
id|probe_rio
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
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USB Rio found at address %d&quot;
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
id|usb_rio_class
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
id|rio-&gt;rio_dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rio-&gt;obuf
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
l_string|&quot;probe_rio: Not enough memory for the output buffer&quot;
)paren
suffix:semicolon
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_rio_class
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
l_string|&quot;probe_rio: obuf address:%p&quot;
comma
id|rio-&gt;obuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rio-&gt;ibuf
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
l_string|&quot;probe_rio: Not enough memory for the input buffer&quot;
)paren
suffix:semicolon
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_rio_class
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rio-&gt;obuf
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
l_string|&quot;probe_rio: ibuf address:%p&quot;
comma
id|rio-&gt;ibuf
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
id|rio
)paren
suffix:semicolon
id|rio-&gt;present
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disconnect_rio
r_static
r_void
id|disconnect_rio
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|rio_usb_data
op_star
id|rio
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
id|rio
)paren
(brace
id|usb_deregister_dev
c_func
(paren
id|intf
comma
op_amp
id|usb_rio_class
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rio-&gt;isopen
)paren
(brace
id|rio-&gt;isopen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* better let it finish - the release will do whats needed */
id|rio-&gt;rio_dev
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|rio-&gt;ibuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rio-&gt;obuf
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;USB Rio disconnected.&quot;
)paren
suffix:semicolon
id|rio-&gt;present
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|rio-&gt;lock
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|rio_table
r_static
r_struct
id|usb_device_id
id|rio_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0841
comma
l_int|1
)paren
)brace
comma
multiline_comment|/* Rio 500 */
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|rio_table
)paren
suffix:semicolon
DECL|variable|rio_driver
r_static
r_struct
id|usb_driver
id|rio_driver
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
l_string|&quot;rio500&quot;
comma
dot
id|probe
op_assign
id|probe_rio
comma
dot
id|disconnect
op_assign
id|disconnect_rio
comma
dot
id|id_table
op_assign
id|rio_table
comma
)brace
suffix:semicolon
DECL|function|usb_rio_init
r_static
r_int
id|__init
id|usb_rio_init
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
id|usb_register
c_func
(paren
op_amp
id|rio_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|usb_rio_cleanup
r_static
r_void
id|__exit
id|usb_rio_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|rio_usb_data
op_star
id|rio
op_assign
op_amp
id|rio_instance
suffix:semicolon
id|rio-&gt;present
op_assign
l_int|0
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|rio_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_rio_init
id|module_init
c_func
(paren
id|usb_rio_init
)paren
suffix:semicolon
DECL|variable|usb_rio_cleanup
id|module_exit
c_func
(paren
id|usb_rio_cleanup
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
