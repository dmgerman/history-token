multiline_comment|/*&n; * $Id: tsdev.c,v 1.15 2002/04/10 16:50:19 jsimmons Exp $&n; *&n; *  Copyright (c) 2001 &quot;Crazy&quot; james Simmons &n; *&n; *  Input driver to Touchscreen device driver module.&n; *&n; *  Sponsored by Transvirtual Technology&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;jsimmons@transvirtual.com&gt;.&n; */
DECL|macro|TSDEV_MINOR_BASE
mdefine_line|#define TSDEV_MINOR_BASE &t;128
DECL|macro|TSDEV_MINORS
mdefine_line|#define TSDEV_MINORS&t;&t;32
DECL|macro|TSDEV_BUFFER_SIZE
mdefine_line|#define TSDEV_BUFFER_SIZE&t;64
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#ifndef CONFIG_INPUT_TSDEV_SCREEN_X
DECL|macro|CONFIG_INPUT_TSDEV_SCREEN_X
mdefine_line|#define CONFIG_INPUT_TSDEV_SCREEN_X&t;240
macro_line|#endif
macro_line|#ifndef CONFIG_INPUT_TSDEV_SCREEN_Y
DECL|macro|CONFIG_INPUT_TSDEV_SCREEN_Y
mdefine_line|#define CONFIG_INPUT_TSDEV_SCREEN_Y&t;320
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@transvirtual.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Input driver to touchscreen converter&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|xres
r_static
r_int
id|xres
op_assign
id|CONFIG_INPUT_TSDEV_SCREEN_X
suffix:semicolon
id|module_param
c_func
(paren
id|xres
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|xres
comma
l_string|&quot;Horizontal screen resolution&quot;
)paren
suffix:semicolon
DECL|variable|yres
r_static
r_int
id|yres
op_assign
id|CONFIG_INPUT_TSDEV_SCREEN_Y
suffix:semicolon
id|module_param
c_func
(paren
id|yres
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|yres
comma
l_string|&quot;Vertical screen resolution&quot;
)paren
suffix:semicolon
DECL|struct|tsdev
r_struct
id|tsdev
(brace
DECL|member|exist
r_int
id|exist
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
id|handle
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* From Compaq&squot;s Touch Screen Specification version 0.2 (draft) */
r_typedef
r_struct
(brace
DECL|member|pressure
r_int
id|pressure
suffix:semicolon
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|member|millisecs
r_int
id|millisecs
suffix:semicolon
DECL|typedef|TS_EVENT
)brace
id|TS_EVENT
suffix:semicolon
DECL|struct|tsdev_list
r_struct
id|tsdev_list
(brace
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|tsdev
r_struct
id|tsdev
op_star
id|tsdev
suffix:semicolon
DECL|member|head
DECL|member|tail
r_int
id|head
comma
id|tail
suffix:semicolon
DECL|member|oldx
DECL|member|oldy
DECL|member|pendown
r_int
id|oldx
comma
id|oldy
comma
id|pendown
suffix:semicolon
DECL|member|event
id|TS_EVENT
id|event
(braket
id|TSDEV_BUFFER_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|tsdev_handler
r_static
r_struct
id|input_handler
id|tsdev_handler
suffix:semicolon
DECL|variable|tsdev_table
r_static
r_struct
id|tsdev
op_star
id|tsdev_table
(braket
id|TSDEV_MINORS
)braket
suffix:semicolon
DECL|function|tsdev_fasync
r_static
r_int
id|tsdev_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|on
)paren
(brace
r_struct
id|tsdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|list-&gt;fasync
)paren
suffix:semicolon
r_return
id|retval
OL
l_int|0
ques
c_cond
id|retval
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|tsdev_open
r_static
r_int
id|tsdev_open
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
id|i
op_assign
id|iminor
c_func
(paren
id|inode
)paren
op_minus
id|TSDEV_MINOR_BASE
suffix:semicolon
r_struct
id|tsdev_list
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|TSDEV_MINORS
op_logical_or
op_logical_neg
id|tsdev_table
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|list
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tsdev_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|list
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tsdev_list
)paren
)paren
suffix:semicolon
id|list-&gt;tsdev
op_assign
id|tsdev_table
(braket
id|i
)braket
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|list-&gt;node
comma
op_amp
id|tsdev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;tsdev-&gt;open
op_increment
)paren
r_if
c_cond
(paren
id|list-&gt;tsdev-&gt;exist
)paren
id|input_open_device
c_func
(paren
op_amp
id|list-&gt;tsdev-&gt;handle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tsdev_free
r_static
r_void
id|tsdev_free
c_func
(paren
r_struct
id|tsdev
op_star
id|tsdev
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;input/ts%d&quot;
comma
id|tsdev-&gt;minor
)paren
suffix:semicolon
id|tsdev_table
(braket
id|tsdev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|tsdev
)paren
suffix:semicolon
)brace
DECL|function|tsdev_release
r_static
r_int
id|tsdev_release
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
id|tsdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|tsdev_fasync
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|list-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|list-&gt;tsdev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;tsdev-&gt;exist
)paren
id|input_close_device
c_func
(paren
op_amp
id|list-&gt;tsdev-&gt;handle
)paren
suffix:semicolon
r_else
id|tsdev_free
c_func
(paren
id|list-&gt;tsdev
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tsdev_read
r_static
id|ssize_t
id|tsdev_read
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
id|tsdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;head
op_eq
id|list-&gt;tail
op_logical_and
id|list-&gt;tsdev-&gt;exist
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|retval
op_assign
id|wait_event_interruptible
c_func
(paren
id|list-&gt;tsdev-&gt;wait
comma
(paren
id|list-&gt;head
op_ne
id|list-&gt;tail
)paren
op_logical_and
id|list-&gt;tsdev-&gt;exist
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
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;tsdev-&gt;exist
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
id|list-&gt;head
op_ne
id|list-&gt;tail
op_logical_and
id|retval
op_plus
r_sizeof
(paren
id|TS_EVENT
)paren
op_le
id|count
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buffer
op_plus
id|retval
comma
id|list-&gt;event
op_plus
id|list-&gt;tail
comma
r_sizeof
(paren
id|TS_EVENT
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|list-&gt;tail
op_assign
(paren
id|list-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|TSDEV_BUFFER_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|retval
op_add_assign
r_sizeof
(paren
id|TS_EVENT
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* No kernel lock - fine */
DECL|function|tsdev_poll
r_static
r_int
r_int
id|tsdev_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|tsdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|list-&gt;tsdev-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;head
op_ne
id|list-&gt;tail
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tsdev_ioctl
r_static
r_int
id|tsdev_ioctl
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
multiline_comment|/*&n;&t;struct tsdev_list *list = file-&gt;private_data;&n;        struct tsdev *evdev = list-&gt;tsdev;&n;        struct input_dev *dev = tsdev-&gt;handle.dev;&n;        int retval;&n;&t;&n;&t;switch (cmd) {&n;&t;&t;case HHEHE:&n;&t;&t;&t;return 0;&n;&t;&t;case hjff:&n;&t;&t;&t;return 0;&n;&t;&t;default:&n;&t;&t;&t;return 0;&n;&t;}&n;*/
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|tsdev_fops
r_struct
id|file_operations
id|tsdev_fops
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
id|tsdev_open
comma
dot
id|release
op_assign
id|tsdev_release
comma
dot
id|read
op_assign
id|tsdev_read
comma
dot
id|poll
op_assign
id|tsdev_poll
comma
dot
id|fasync
op_assign
id|tsdev_fasync
comma
dot
id|ioctl
op_assign
id|tsdev_ioctl
comma
)brace
suffix:semicolon
DECL|function|tsdev_event
r_static
r_void
id|tsdev_event
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|tsdev
op_star
id|tsdev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|tsdev_list
op_star
id|list
suffix:semicolon
r_struct
id|timeval
id|time
suffix:semicolon
r_int
id|size
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|list
comma
op_amp
id|tsdev-&gt;list
comma
id|node
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_ABS
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ABS_X
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;pendown
)paren
r_return
suffix:semicolon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_X
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_X
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
id|list-&gt;oldx
op_assign
(paren
(paren
id|value
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_X
)braket
)paren
op_star
id|xres
op_div
id|size
)paren
suffix:semicolon
r_else
id|list-&gt;oldx
op_assign
(paren
(paren
id|value
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_X
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_Y
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;pendown
)paren
r_return
suffix:semicolon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_Y
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_Y
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
id|list-&gt;oldy
op_assign
(paren
(paren
id|value
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_Y
)braket
)paren
op_star
id|yres
op_div
id|size
)paren
suffix:semicolon
r_else
id|list-&gt;oldy
op_assign
(paren
(paren
id|value
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_Y
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_PRESSURE
suffix:colon
id|list-&gt;pendown
op_assign
(paren
(paren
id|value
OG
id|handle-&gt;dev
op_member_access_from_pointer
id|absmin
(braket
id|ABS_PRESSURE
)braket
)paren
)paren
ques
c_cond
id|value
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_PRESSURE
)braket
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_REL
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|REL_X
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;pendown
)paren
r_return
suffix:semicolon
id|list-&gt;oldx
op_add_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;oldx
OL
l_int|0
)paren
id|list-&gt;oldx
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|list-&gt;oldx
OG
id|xres
)paren
id|list-&gt;oldx
op_assign
id|xres
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REL_Y
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;pendown
)paren
r_return
suffix:semicolon
id|list-&gt;oldy
op_add_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;oldy
OL
l_int|0
)paren
id|list-&gt;oldy
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|list-&gt;oldy
OG
id|xres
)paren
id|list-&gt;oldy
op_assign
id|xres
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_KEY
suffix:colon
r_if
c_cond
(paren
id|code
op_eq
id|BTN_TOUCH
op_logical_or
id|code
op_eq
id|BTN_MOUSE
)paren
(brace
r_switch
c_cond
(paren
id|value
)paren
(brace
r_case
l_int|0
suffix:colon
id|list-&gt;pendown
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;pendown
)paren
id|list-&gt;pendown
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
suffix:semicolon
)brace
)brace
r_else
r_return
suffix:semicolon
r_break
suffix:semicolon
)brace
id|do_gettimeofday
c_func
(paren
op_amp
id|time
)paren
suffix:semicolon
id|list-&gt;event
(braket
id|list-&gt;head
)braket
dot
id|millisecs
op_assign
id|time.tv_usec
op_div
l_int|100
suffix:semicolon
id|list-&gt;event
(braket
id|list-&gt;head
)braket
dot
id|pressure
op_assign
id|list-&gt;pendown
suffix:semicolon
id|list-&gt;event
(braket
id|list-&gt;head
)braket
dot
id|x
op_assign
id|list-&gt;oldx
suffix:semicolon
id|list-&gt;event
(braket
id|list-&gt;head
)braket
dot
id|y
op_assign
id|list-&gt;oldy
suffix:semicolon
id|list-&gt;head
op_assign
(paren
id|list-&gt;head
op_plus
l_int|1
)paren
op_amp
(paren
id|TSDEV_BUFFER_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|list-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|tsdev-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|tsdev_connect
r_static
r_struct
id|input_handle
op_star
id|tsdev_connect
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
comma
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|input_device_id
op_star
id|id
)paren
(brace
r_struct
id|tsdev
op_star
id|tsdev
suffix:semicolon
r_int
id|minor
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|TSDEV_MINORS
op_logical_and
id|tsdev_table
(braket
id|minor
)braket
suffix:semicolon
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
id|TSDEV_MINORS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tsdev: You have way too many touchscreens&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tsdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tsdev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|tsdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tsdev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|tsdev-&gt;list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|tsdev-&gt;wait
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|tsdev-&gt;name
comma
l_string|&quot;ts%d&quot;
comma
id|minor
)paren
suffix:semicolon
id|tsdev-&gt;exist
op_assign
l_int|1
suffix:semicolon
id|tsdev-&gt;minor
op_assign
id|minor
suffix:semicolon
id|tsdev-&gt;handle.dev
op_assign
id|dev
suffix:semicolon
id|tsdev-&gt;handle.name
op_assign
id|tsdev-&gt;name
suffix:semicolon
id|tsdev-&gt;handle.handler
op_assign
id|handler
suffix:semicolon
id|tsdev-&gt;handle
dot
r_private
op_assign
id|tsdev
suffix:semicolon
id|tsdev_table
(braket
id|minor
)braket
op_assign
id|tsdev
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|INPUT_MAJOR
comma
id|TSDEV_MINOR_BASE
op_plus
id|minor
)paren
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
l_string|&quot;input/ts%d&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_amp
id|tsdev-&gt;handle
suffix:semicolon
)brace
DECL|function|tsdev_disconnect
r_static
r_void
id|tsdev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|tsdev
op_star
id|tsdev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
id|tsdev-&gt;exist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tsdev-&gt;open
)paren
(brace
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|tsdev-&gt;wait
)paren
suffix:semicolon
)brace
r_else
id|tsdev_free
c_func
(paren
id|tsdev
)paren
suffix:semicolon
)brace
DECL|variable|tsdev_ids
r_static
r_struct
id|input_device_id
id|tsdev_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_KEYBIT
op_or
id|INPUT_DEVICE_ID_MATCH_RELBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
)brace
comma
dot
id|relbit
op_assign
(brace
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
)brace
comma
)brace
comma
multiline_comment|/* A mouse like device, at least one button, two relative axes */
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
op_or
id|INPUT_DEVICE_ID_MATCH_KEYBIT
op_or
id|INPUT_DEVICE_ID_MATCH_ABSBIT
comma
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
)brace
comma
dot
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
)brace
comma
)brace
comma
multiline_comment|/* A tablet like device, at least touch detection, two absolute axes */
(brace
)brace
comma
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|input
comma
id|tsdev_ids
)paren
suffix:semicolon
DECL|variable|tsdev_handler
r_static
r_struct
id|input_handler
id|tsdev_handler
op_assign
(brace
dot
id|event
op_assign
id|tsdev_event
comma
dot
id|connect
op_assign
id|tsdev_connect
comma
dot
id|disconnect
op_assign
id|tsdev_disconnect
comma
dot
id|fops
op_assign
op_amp
id|tsdev_fops
comma
dot
id|minor
op_assign
id|TSDEV_MINOR_BASE
comma
dot
id|name
op_assign
l_string|&quot;tsdev&quot;
comma
dot
id|id_table
op_assign
id|tsdev_ids
comma
)brace
suffix:semicolon
DECL|function|tsdev_init
r_static
r_int
id|__init
id|tsdev_init
c_func
(paren
r_void
)paren
(brace
id|input_register_handler
c_func
(paren
op_amp
id|tsdev_handler
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ts: Compaq touchscreen protocol output&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tsdev_exit
r_static
r_void
id|__exit
id|tsdev_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_handler
c_func
(paren
op_amp
id|tsdev_handler
)paren
suffix:semicolon
)brace
DECL|variable|tsdev_init
id|module_init
c_func
(paren
id|tsdev_init
)paren
suffix:semicolon
DECL|variable|tsdev_exit
id|module_exit
c_func
(paren
id|tsdev_exit
)paren
suffix:semicolon
eof
