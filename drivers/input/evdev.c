multiline_comment|/*&n; * $Id: evdev.c,v 1.48 2002/05/26 14:28:26 jdeneux Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; *&n; *  Event char devices, giving access to raw input device events.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
DECL|macro|EVDEV_MINOR_BASE
mdefine_line|#define EVDEV_MINOR_BASE&t;64
DECL|macro|EVDEV_MINORS
mdefine_line|#define EVDEV_MINORS&t;&t;32
DECL|macro|EVDEV_BUFFER_SIZE
mdefine_line|#define EVDEV_BUFFER_SIZE&t;64
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|struct|evdev
r_struct
id|evdev
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
DECL|member|handle
r_struct
id|input_handle
id|handle
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
DECL|member|list
r_struct
id|evdev_list
op_star
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|evdev_list
r_struct
id|evdev_list
(brace
DECL|member|buffer
r_struct
id|input_event
id|buffer
(braket
id|EVDEV_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|evdev
r_struct
id|evdev
op_star
id|evdev
suffix:semicolon
DECL|member|next
r_struct
id|evdev_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|evdev_table
r_static
r_struct
id|evdev
op_star
id|evdev_table
(braket
id|EVDEV_MINORS
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* ... */
)brace
suffix:semicolon
DECL|function|evdev_event
r_static
r_void
id|evdev_event
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
id|evdev
op_star
id|evdev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|evdev_list
op_star
id|list
op_assign
id|evdev-&gt;list
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
id|do_gettimeofday
c_func
(paren
op_amp
id|list-&gt;buffer
(braket
id|list-&gt;head
)braket
dot
id|time
)paren
suffix:semicolon
id|list-&gt;buffer
(braket
id|list-&gt;head
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|list-&gt;buffer
(braket
id|list-&gt;head
)braket
dot
id|code
op_assign
id|code
suffix:semicolon
id|list-&gt;buffer
(braket
id|list-&gt;head
)braket
dot
id|value
op_assign
id|value
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
id|EVDEV_BUFFER_SIZE
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
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|evdev-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|evdev_fasync
r_static
r_int
id|evdev_fasync
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
r_int
id|retval
suffix:semicolon
r_struct
id|evdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
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
DECL|function|evdev_flush
r_static
r_int
id|evdev_flush
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|evdev_list
op_star
id|list
op_assign
(paren
r_struct
id|evdev_list
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;evdev-&gt;exist
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|input_flush_device
c_func
(paren
op_amp
id|list-&gt;evdev-&gt;handle
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|evdev_release
r_static
r_int
id|evdev_release
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
id|evdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|evdev_list
op_star
op_star
id|listptr
suffix:semicolon
id|listptr
op_assign
op_amp
id|list-&gt;evdev-&gt;list
suffix:semicolon
id|evdev_fasync
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
r_while
c_loop
(paren
op_star
id|listptr
op_logical_and
(paren
op_star
id|listptr
op_ne
id|list
)paren
)paren
id|listptr
op_assign
op_amp
(paren
(paren
op_star
id|listptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|listptr
op_assign
(paren
op_star
id|listptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|list-&gt;evdev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;evdev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|list-&gt;evdev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|list-&gt;evdev-&gt;devfs
)paren
suffix:semicolon
id|evdev_table
(braket
id|list-&gt;evdev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|list-&gt;evdev
)paren
suffix:semicolon
)brace
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
DECL|function|evdev_open
r_static
r_int
id|evdev_open
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
id|evdev_list
op_star
id|list
suffix:semicolon
r_int
id|i
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|EVDEV_MINOR_BASE
suffix:semicolon
r_int
id|accept_err
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|EVDEV_MINORS
op_logical_or
op_logical_neg
id|evdev_table
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Ask the driver if he wishes to accept the open() */
r_if
c_cond
(paren
(paren
id|accept_err
op_assign
id|input_accept_process
c_func
(paren
op_amp
(paren
id|evdev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|handle
)paren
comma
id|file
)paren
)paren
)paren
(brace
r_return
id|accept_err
suffix:semicolon
)brace
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
id|evdev_list
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
id|evdev_list
)paren
)paren
suffix:semicolon
id|list-&gt;evdev
op_assign
id|evdev_table
(braket
id|i
)braket
suffix:semicolon
id|list-&gt;next
op_assign
id|evdev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
suffix:semicolon
id|evdev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
op_assign
id|list
suffix:semicolon
id|file-&gt;private_data
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;evdev-&gt;open
op_increment
)paren
r_if
c_cond
(paren
id|list-&gt;evdev-&gt;exist
)paren
id|input_open_device
c_func
(paren
op_amp
id|list-&gt;evdev-&gt;handle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|evdev_write
r_static
id|ssize_t
id|evdev_write
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
id|evdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|input_event
id|event
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;evdev-&gt;exist
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
id|retval
OL
id|count
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|event
comma
id|buffer
op_plus
id|retval
comma
r_sizeof
(paren
r_struct
id|input_event
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|input_event
c_func
(paren
id|list-&gt;evdev-&gt;handle.dev
comma
id|event.type
comma
id|event.code
comma
id|event.value
)paren
suffix:semicolon
id|retval
op_add_assign
r_sizeof
(paren
r_struct
id|input_event
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|evdev_read
r_static
id|ssize_t
id|evdev_read
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
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|evdev_list
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
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|list-&gt;evdev-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list-&gt;head
op_eq
id|list-&gt;tail
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;evdev-&gt;exist
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
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
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|list-&gt;evdev-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
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
r_struct
id|input_event
)paren
op_le
id|count
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
op_plus
id|retval
comma
id|list-&gt;buffer
op_plus
id|list-&gt;tail
comma
r_sizeof
(paren
r_struct
id|input_event
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
id|EVDEV_BUFFER_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|retval
op_add_assign
r_sizeof
(paren
r_struct
id|input_event
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* No kernel lock - fine */
DECL|function|evdev_poll
r_static
r_int
r_int
id|evdev_poll
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
id|evdev_list
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
id|list-&gt;evdev-&gt;wait
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
DECL|function|evdev_ioctl
r_static
r_int
id|evdev_ioctl
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
id|evdev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|evdev
op_star
id|evdev
op_assign
id|list-&gt;evdev
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
id|evdev-&gt;handle.dev
suffix:semicolon
r_struct
id|input_devinfo
id|id
suffix:semicolon
r_int
id|retval
comma
id|t
comma
id|u
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|evdev-&gt;exist
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
id|EVIOCGVERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|EV_VERSION
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|EVIOCGID
suffix:colon
id|id.bustype
op_assign
id|dev-&gt;id.bustype
suffix:semicolon
id|id.vendor
op_assign
id|dev-&gt;id.vendor
suffix:semicolon
id|id.product
op_assign
id|dev-&gt;id.product
suffix:semicolon
id|id.version
op_assign
id|dev-&gt;id.version
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|id
comma
r_sizeof
(paren
r_struct
id|input_devinfo
)paren
)paren
suffix:semicolon
r_case
id|EVIOCGREP
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;rep
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|0
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;rep
(braket
l_int|1
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|1
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|EVIOCSREP
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|dev-&gt;rep
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|0
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|dev-&gt;rep
(braket
l_int|1
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|1
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|EVIOCGKEYCODE
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|t
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|0
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|t
template_param
id|dev-&gt;keycodemax
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;keycodesize
)paren
(brace
r_case
l_int|1
suffix:colon
id|u
op_assign
op_star
(paren
id|u8
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|u
op_assign
op_star
(paren
id|u16
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
op_star
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|u
op_assign
op_star
(paren
id|u32
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|u
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|1
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|EVIOCSKEYCODE
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|t
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|0
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|t
template_param
id|dev-&gt;keycodemax
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|get_user
c_func
(paren
id|u
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|1
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;keycodesize
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
(paren
id|u8
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
)paren
op_assign
id|u
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
id|u16
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
op_star
l_int|2
)paren
op_assign
id|u
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
id|u32
op_star
)paren
(paren
id|dev-&gt;keycode
op_plus
id|t
op_star
l_int|4
)paren
op_assign
id|u
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|EVIOCSFF
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;upload_effect
)paren
(brace
r_struct
id|ff_effect
id|effect
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
(paren
op_amp
id|effect
)paren
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|effect
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|err
op_assign
id|dev
op_member_access_from_pointer
id|upload_effect
c_func
(paren
id|dev
comma
op_amp
id|effect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|effect.id
comma
op_amp
(paren
(paren
(paren
r_struct
id|ff_effect
op_star
)paren
id|arg
)paren
op_member_access_from_pointer
id|id
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_case
id|EVIOCRMFF
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;erase_effect
)paren
(brace
r_return
id|dev
op_member_access_from_pointer
id|erase_effect
c_func
(paren
id|dev
comma
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_case
id|EVIOCGEFFECTS
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;ff_effects_max
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|_IOC_TYPE
c_func
(paren
id|cmd
)paren
op_ne
l_char|&squot;E&squot;
op_logical_or
id|_IOC_DIR
c_func
(paren
id|cmd
)paren
op_ne
id|_IOC_READ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_amp
op_complement
id|EV_MAX
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGBIT
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
r_int
op_star
id|bits
suffix:semicolon
r_int
id|len
suffix:semicolon
r_switch
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_amp
id|EV_MAX
)paren
(brace
r_case
l_int|0
suffix:colon
id|bits
op_assign
id|dev-&gt;evbit
suffix:semicolon
id|len
op_assign
id|EV_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_KEY
suffix:colon
id|bits
op_assign
id|dev-&gt;keybit
suffix:semicolon
id|len
op_assign
id|KEY_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_REL
suffix:colon
id|bits
op_assign
id|dev-&gt;relbit
suffix:semicolon
id|len
op_assign
id|REL_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_ABS
suffix:colon
id|bits
op_assign
id|dev-&gt;absbit
suffix:semicolon
id|len
op_assign
id|ABS_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_LED
suffix:colon
id|bits
op_assign
id|dev-&gt;ledbit
suffix:semicolon
id|len
op_assign
id|LED_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_SND
suffix:colon
id|bits
op_assign
id|dev-&gt;sndbit
suffix:semicolon
id|len
op_assign
id|SND_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_FF
suffix:colon
id|bits
op_assign
id|dev-&gt;ffbit
suffix:semicolon
id|len
op_assign
id|FF_MAX
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|len
op_assign
id|NBITS
c_func
(paren
id|len
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|bits
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGKEY
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;key
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGLED
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|NBITS
c_func
(paren
id|LED_MAX
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;led
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGSND
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|NBITS
c_func
(paren
id|SND_MAX
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;snd
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGNAME
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;name
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;name
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGPHYS
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;phys
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|dev-&gt;phys
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;phys
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGUNIQ
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;uniq
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|dev-&gt;uniq
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
)paren
id|len
op_assign
id|_IOC_SIZE
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|dev-&gt;uniq
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_amp
op_complement
id|ABS_MAX
)paren
op_eq
id|_IOC_NR
c_func
(paren
id|EVIOCGABS
c_func
(paren
l_int|0
)paren
)paren
)paren
(brace
r_int
id|t
op_assign
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_amp
id|ABS_MAX
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;abs
(braket
id|t
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|0
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;absmin
(braket
id|t
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|1
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;absmax
(braket
id|t
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|2
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;absfuzz
(braket
id|t
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|3
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|put_user
c_func
(paren
id|dev-&gt;absflat
(braket
id|t
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
op_plus
l_int|4
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|evdev_fops
r_static
r_struct
id|file_operations
id|evdev_fops
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
id|evdev_read
comma
dot
id|write
op_assign
id|evdev_write
comma
dot
id|poll
op_assign
id|evdev_poll
comma
dot
id|open
op_assign
id|evdev_open
comma
dot
id|release
op_assign
id|evdev_release
comma
dot
id|ioctl
op_assign
id|evdev_ioctl
comma
dot
id|fasync
op_assign
id|evdev_fasync
comma
dot
id|flush
op_assign
id|evdev_flush
)brace
suffix:semicolon
DECL|function|evdev_connect
r_static
r_struct
id|input_handle
op_star
id|evdev_connect
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
id|evdev
op_star
id|evdev
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
id|EVDEV_MINORS
op_logical_and
id|evdev_table
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
id|EVDEV_MINORS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;evdev: no more free evdev devices&bslash;n&quot;
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
id|evdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|evdev
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
id|evdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|evdev
)paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|evdev-&gt;wait
)paren
suffix:semicolon
id|evdev-&gt;minor
op_assign
id|minor
suffix:semicolon
id|evdev_table
(braket
id|minor
)braket
op_assign
id|evdev
suffix:semicolon
id|sprintf
c_func
(paren
id|evdev-&gt;name
comma
l_string|&quot;event%d&quot;
comma
id|minor
)paren
suffix:semicolon
id|evdev-&gt;handle.dev
op_assign
id|dev
suffix:semicolon
id|evdev-&gt;handle.name
op_assign
id|evdev-&gt;name
suffix:semicolon
id|evdev-&gt;handle.handler
op_assign
id|handler
suffix:semicolon
id|evdev-&gt;handle
dot
r_private
op_assign
id|evdev
suffix:semicolon
id|evdev-&gt;devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;event%d&quot;
comma
id|minor
comma
id|EVDEV_MINOR_BASE
)paren
suffix:semicolon
id|evdev-&gt;exist
op_assign
l_int|1
suffix:semicolon
r_return
op_amp
id|evdev-&gt;handle
suffix:semicolon
)brace
DECL|function|evdev_disconnect
r_static
r_void
id|evdev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|evdev
op_star
id|evdev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
id|evdev-&gt;exist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|evdev-&gt;open
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
id|evdev-&gt;wait
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|evdev-&gt;devfs
)paren
suffix:semicolon
id|evdev_table
(braket
id|evdev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|evdev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|evdev_ids
r_static
r_struct
id|input_device_id
id|evdev_ids
(braket
)braket
op_assign
(brace
(brace
id|driver_info
suffix:colon
l_int|1
)brace
comma
multiline_comment|/* Matches all devices */
(brace
)brace
comma
multiline_comment|/* Terminating zero entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|input
comma
id|evdev_ids
)paren
suffix:semicolon
DECL|variable|evdev_handler
r_static
r_struct
id|input_handler
id|evdev_handler
op_assign
(brace
dot
id|event
op_assign
id|evdev_event
comma
dot
id|connect
op_assign
id|evdev_connect
comma
dot
id|disconnect
op_assign
id|evdev_disconnect
comma
dot
id|fops
op_assign
op_amp
id|evdev_fops
comma
dot
id|minor
op_assign
id|EVDEV_MINOR_BASE
comma
dot
id|name
op_assign
l_string|&quot;evdev&quot;
comma
dot
id|id_table
op_assign
id|evdev_ids
comma
)brace
suffix:semicolon
DECL|function|evdev_init
r_static
r_int
id|__init
id|evdev_init
c_func
(paren
r_void
)paren
(brace
id|input_register_handler
c_func
(paren
op_amp
id|evdev_handler
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|evdev_exit
r_static
r_void
id|__exit
id|evdev_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_handler
c_func
(paren
op_amp
id|evdev_handler
)paren
suffix:semicolon
)brace
DECL|variable|evdev_init
id|module_init
c_func
(paren
id|evdev_init
)paren
suffix:semicolon
DECL|variable|evdev_exit
id|module_exit
c_func
(paren
id|evdev_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Input driver event char devices&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
