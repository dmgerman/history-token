multiline_comment|/*&n; * Joystick device driver for the input driver suite.&n; *&n; * Copyright (c) 1999-2002 Vojtech Pavlik &n; * Copyright (c) 1999 Colin Van Dyke &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/joystick.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/device.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Joystick device interfaces&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;input/js&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|JOYDEV_MINOR_BASE
mdefine_line|#define JOYDEV_MINOR_BASE&t;0
DECL|macro|JOYDEV_MINORS
mdefine_line|#define JOYDEV_MINORS&t;&t;16&t;
DECL|macro|JOYDEV_BUFFER_SIZE
mdefine_line|#define JOYDEV_BUFFER_SIZE&t;64
DECL|macro|MSECS
mdefine_line|#define MSECS(t)&t;(1000 * ((t) / HZ) + 1000 * ((t) % HZ) / HZ)
DECL|struct|joydev
r_struct
id|joydev
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
id|list_head
id|list
suffix:semicolon
DECL|member|corr
r_struct
id|js_corr
id|corr
(braket
id|ABS_MAX
)braket
suffix:semicolon
DECL|member|glue
r_struct
id|JS_DATA_SAVE_TYPE
id|glue
suffix:semicolon
DECL|member|nabs
r_int
id|nabs
suffix:semicolon
DECL|member|nkey
r_int
id|nkey
suffix:semicolon
DECL|member|keymap
id|__u16
id|keymap
(braket
id|KEY_MAX
op_minus
id|BTN_MISC
)braket
suffix:semicolon
DECL|member|keypam
id|__u16
id|keypam
(braket
id|KEY_MAX
op_minus
id|BTN_MISC
)braket
suffix:semicolon
DECL|member|absmap
id|__u8
id|absmap
(braket
id|ABS_MAX
)braket
suffix:semicolon
DECL|member|abspam
id|__u8
id|abspam
(braket
id|ABS_MAX
)braket
suffix:semicolon
DECL|member|abs
id|__s16
id|abs
(braket
id|ABS_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|joydev_list
r_struct
id|joydev_list
(brace
DECL|member|buffer
r_struct
id|js_event
id|buffer
(braket
id|JOYDEV_BUFFER_SIZE
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
DECL|member|startup
r_int
id|startup
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|joydev
r_struct
id|joydev
op_star
id|joydev
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|joydev_table
r_static
r_struct
id|joydev
op_star
id|joydev_table
(braket
id|JOYDEV_MINORS
)braket
suffix:semicolon
DECL|function|joydev_correct
r_static
r_int
id|joydev_correct
c_func
(paren
r_int
id|value
comma
r_struct
id|js_corr
op_star
id|corr
)paren
(brace
r_switch
c_cond
(paren
id|corr-&gt;type
)paren
(brace
r_case
id|JS_CORR_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|JS_CORR_BROKEN
suffix:colon
id|value
op_assign
id|value
OG
id|corr-&gt;coef
(braket
l_int|0
)braket
ques
c_cond
(paren
id|value
OL
id|corr-&gt;coef
(braket
l_int|1
)braket
ques
c_cond
l_int|0
suffix:colon
(paren
(paren
id|corr-&gt;coef
(braket
l_int|3
)braket
op_star
(paren
id|value
op_minus
id|corr-&gt;coef
(braket
l_int|1
)braket
)paren
)paren
op_rshift
l_int|14
)paren
)paren
suffix:colon
(paren
(paren
id|corr-&gt;coef
(braket
l_int|2
)braket
op_star
(paren
id|value
op_minus
id|corr-&gt;coef
(braket
l_int|0
)braket
)paren
)paren
op_rshift
l_int|14
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
OL
op_minus
l_int|32767
)paren
r_return
op_minus
l_int|32767
suffix:semicolon
r_if
c_cond
(paren
id|value
OG
l_int|32767
)paren
r_return
l_int|32767
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|joydev_event
r_static
r_void
id|joydev_event
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
id|joydev
op_star
id|joydev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|joydev_list
op_star
id|list
suffix:semicolon
r_struct
id|js_event
id|event
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_KEY
suffix:colon
r_if
c_cond
(paren
id|code
OL
id|BTN_MISC
op_logical_or
id|value
op_eq
l_int|2
)paren
r_return
suffix:semicolon
id|event.type
op_assign
id|JS_EVENT_BUTTON
suffix:semicolon
id|event.number
op_assign
id|joydev-&gt;keymap
(braket
id|code
op_minus
id|BTN_MISC
)braket
suffix:semicolon
id|event.value
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EV_ABS
suffix:colon
id|event.type
op_assign
id|JS_EVENT_AXIS
suffix:semicolon
id|event.number
op_assign
id|joydev-&gt;absmap
(braket
id|code
)braket
suffix:semicolon
id|event.value
op_assign
id|joydev_correct
c_func
(paren
id|value
comma
id|joydev-&gt;corr
op_plus
id|event.number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event.value
op_eq
id|joydev-&gt;abs
(braket
id|event.number
)braket
)paren
r_return
suffix:semicolon
id|joydev-&gt;abs
(braket
id|event.number
)braket
op_assign
id|event.value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|event.time
op_assign
id|MSECS
c_func
(paren
id|jiffies
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|list
comma
op_amp
id|joydev-&gt;list
comma
id|node
)paren
(brace
id|memcpy
c_func
(paren
id|list-&gt;buffer
op_plus
id|list-&gt;head
comma
op_amp
id|event
comma
r_sizeof
(paren
r_struct
id|js_event
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;startup
op_eq
id|joydev-&gt;nabs
op_plus
id|joydev-&gt;nkey
)paren
r_if
c_cond
(paren
id|list-&gt;tail
op_eq
(paren
id|list-&gt;head
op_assign
(paren
id|list-&gt;head
op_plus
l_int|1
)paren
op_amp
(paren
id|JOYDEV_BUFFER_SIZE
op_minus
l_int|1
)paren
)paren
)paren
id|list-&gt;startup
op_assign
l_int|0
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
id|joydev-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|joydev_fasync
r_static
r_int
id|joydev_fasync
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
id|joydev_list
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
DECL|function|joydev_release
r_static
r_int
id|joydev_release
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
id|joydev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|joydev_fasync
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
id|list-&gt;joydev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;joydev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|list-&gt;joydev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|list-&gt;joydev-&gt;devfs
)paren
suffix:semicolon
id|joydev_table
(braket
id|list-&gt;joydev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|list-&gt;joydev
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
DECL|function|joydev_open
r_static
r_int
id|joydev_open
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
id|joydev_list
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
id|JOYDEV_MINOR_BASE
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|JOYDEV_MINORS
op_logical_or
op_logical_neg
id|joydev_table
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
id|joydev_list
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
id|joydev_list
)paren
)paren
suffix:semicolon
id|list-&gt;joydev
op_assign
id|joydev_table
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
id|joydev_table
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
id|list-&gt;joydev-&gt;open
op_increment
)paren
r_if
c_cond
(paren
id|list-&gt;joydev-&gt;exist
)paren
id|input_open_device
c_func
(paren
op_amp
id|list-&gt;joydev-&gt;handle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|joydev_write
r_static
id|ssize_t
id|joydev_write
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|joydev_read
r_static
id|ssize_t
id|joydev_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
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
id|joydev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|joydev
op_star
id|joydev
op_assign
id|list-&gt;joydev
suffix:semicolon
r_struct
id|input_dev
op_star
id|input
op_assign
id|joydev-&gt;handle.dev
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
id|list-&gt;joydev-&gt;exist
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
r_sizeof
(paren
r_struct
id|js_event
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
r_sizeof
(paren
r_struct
id|JS_DATA_TYPE
)paren
)paren
(brace
r_struct
id|JS_DATA_TYPE
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|data.buttons
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
op_logical_and
id|i
OL
id|joydev-&gt;nkey
suffix:semicolon
id|i
op_increment
)paren
id|data.buttons
op_or_assign
id|test_bit
c_func
(paren
id|joydev-&gt;keypam
(braket
id|i
)braket
comma
id|input-&gt;key
)paren
ques
c_cond
(paren
l_int|1
op_lshift
id|i
)paren
suffix:colon
l_int|0
suffix:semicolon
id|data.x
op_assign
(paren
id|joydev-&gt;abs
(braket
l_int|0
)braket
op_div
l_int|256
op_plus
l_int|128
)paren
op_rshift
id|joydev-&gt;glue.JS_CORR.x
suffix:semicolon
id|data.y
op_assign
(paren
id|joydev-&gt;abs
(braket
l_int|1
)braket
op_div
l_int|256
op_plus
l_int|128
)paren
op_rshift
id|joydev-&gt;glue.JS_CORR.y
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|data
comma
r_sizeof
(paren
r_struct
id|JS_DATA_TYPE
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|list-&gt;startup
op_assign
l_int|0
suffix:semicolon
id|list-&gt;tail
op_assign
id|list-&gt;head
suffix:semicolon
r_return
r_sizeof
(paren
r_struct
id|JS_DATA_TYPE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list-&gt;startup
op_eq
id|joydev-&gt;nabs
op_plus
id|joydev-&gt;nkey
op_logical_and
id|list-&gt;head
op_eq
id|list-&gt;tail
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
id|list-&gt;joydev-&gt;wait
comma
id|list-&gt;joydev-&gt;exist
op_logical_and
(paren
id|list-&gt;startup
OL
id|joydev-&gt;nabs
op_plus
id|joydev-&gt;nkey
op_logical_or
id|list-&gt;head
op_ne
id|list-&gt;tail
)paren
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
id|list-&gt;joydev-&gt;exist
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
id|list-&gt;startup
OL
id|joydev-&gt;nabs
op_plus
id|joydev-&gt;nkey
op_logical_and
id|retval
op_plus
r_sizeof
(paren
r_struct
id|js_event
)paren
op_le
id|count
)paren
(brace
r_struct
id|js_event
id|event
suffix:semicolon
id|event.time
op_assign
id|MSECS
c_func
(paren
id|jiffies
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;startup
OL
id|joydev-&gt;nkey
)paren
(brace
id|event.type
op_assign
id|JS_EVENT_BUTTON
op_or
id|JS_EVENT_INIT
suffix:semicolon
id|event.number
op_assign
id|list-&gt;startup
suffix:semicolon
id|event.value
op_assign
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|joydev-&gt;keypam
(braket
id|event.number
)braket
comma
id|input-&gt;key
)paren
suffix:semicolon
)brace
r_else
(brace
id|event.type
op_assign
id|JS_EVENT_AXIS
op_or
id|JS_EVENT_INIT
suffix:semicolon
id|event.number
op_assign
id|list-&gt;startup
op_minus
id|joydev-&gt;nkey
suffix:semicolon
id|event.value
op_assign
id|joydev-&gt;abs
(braket
id|event.number
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
op_plus
id|retval
comma
op_amp
id|event
comma
r_sizeof
(paren
r_struct
id|js_event
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|list-&gt;startup
op_increment
suffix:semicolon
id|retval
op_add_assign
r_sizeof
(paren
r_struct
id|js_event
)paren
suffix:semicolon
)brace
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
id|js_event
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
id|buf
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
id|js_event
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
id|JOYDEV_BUFFER_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|retval
op_add_assign
r_sizeof
(paren
r_struct
id|js_event
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* No kernel lock - fine */
DECL|function|joydev_poll
r_static
r_int
r_int
id|joydev_poll
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
id|joydev_list
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
id|list-&gt;joydev-&gt;wait
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
op_logical_or
id|list-&gt;startup
OL
id|list-&gt;joydev-&gt;nabs
op_plus
id|list-&gt;joydev-&gt;nkey
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
DECL|function|joydev_ioctl
r_static
r_int
id|joydev_ioctl
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
id|joydev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|joydev
op_star
id|joydev
op_assign
id|list-&gt;joydev
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
id|joydev-&gt;handle.dev
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|joydev-&gt;exist
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
id|JS_SET_CAL
suffix:colon
r_return
id|copy_from_user
c_func
(paren
op_amp
id|joydev-&gt;glue.JS_CORR
comma
(paren
r_struct
id|JS_DATA_TYPE
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|JS_DATA_TYPE
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JS_GET_CAL
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
r_struct
id|JS_DATA_TYPE
op_star
)paren
id|arg
comma
op_amp
id|joydev-&gt;glue.JS_CORR
comma
r_sizeof
(paren
r_struct
id|JS_DATA_TYPE
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JS_SET_TIMEOUT
suffix:colon
r_return
id|get_user
c_func
(paren
id|joydev-&gt;glue.JS_TIMEOUT
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JS_GET_TIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|joydev-&gt;glue.JS_TIMEOUT
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JS_SET_TIMELIMIT
suffix:colon
r_return
id|get_user
c_func
(paren
id|joydev-&gt;glue.JS_TIMELIMIT
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JS_GET_TIMELIMIT
suffix:colon
r_return
id|put_user
c_func
(paren
id|joydev-&gt;glue.JS_TIMELIMIT
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JS_SET_ALL
suffix:colon
r_return
id|copy_from_user
c_func
(paren
op_amp
id|joydev-&gt;glue
comma
(paren
r_struct
id|JS_DATA_SAVE_TYPE
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|JS_DATA_SAVE_TYPE
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JS_GET_ALL
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
r_struct
id|JS_DATA_SAVE_TYPE
op_star
)paren
id|arg
comma
op_amp
id|joydev-&gt;glue
comma
r_sizeof
(paren
r_struct
id|JS_DATA_SAVE_TYPE
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JSIOCGVERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|JS_VERSION
comma
(paren
id|__u32
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JSIOCGAXES
suffix:colon
r_return
id|put_user
c_func
(paren
id|joydev-&gt;nabs
comma
(paren
id|__u8
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JSIOCGBUTTONS
suffix:colon
r_return
id|put_user
c_func
(paren
id|joydev-&gt;nkey
comma
(paren
id|__u8
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|JSIOCSCORR
suffix:colon
r_return
id|copy_from_user
c_func
(paren
id|joydev-&gt;corr
comma
(paren
r_struct
id|js_corr
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|js_corr
)paren
op_star
id|joydev-&gt;nabs
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JSIOCGCORR
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
r_struct
id|js_corr
op_star
)paren
id|arg
comma
id|joydev-&gt;corr
comma
r_sizeof
(paren
r_struct
id|js_corr
)paren
op_star
id|joydev-&gt;nabs
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JSIOCSAXMAP
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|joydev-&gt;abspam
comma
(paren
id|__u8
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|__u8
)paren
op_star
id|ABS_MAX
)paren
)paren
r_return
op_minus
id|EFAULT
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
id|joydev-&gt;nabs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|joydev-&gt;abspam
(braket
id|i
)braket
OG
id|ABS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|joydev-&gt;absmap
(braket
id|joydev-&gt;abspam
(braket
id|i
)braket
)braket
op_assign
id|i
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|JSIOCGAXMAP
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
id|__u8
op_star
)paren
id|arg
comma
id|joydev-&gt;abspam
comma
r_sizeof
(paren
id|__u8
)paren
op_star
id|ABS_MAX
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|JSIOCSBTNMAP
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|joydev-&gt;keypam
comma
(paren
id|__u16
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|__u16
)paren
op_star
(paren
id|KEY_MAX
op_minus
id|BTN_MISC
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
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
id|joydev-&gt;nkey
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
(brace
r_if
c_cond
(paren
id|joydev-&gt;keypam
(braket
id|i
)braket
OG
id|KEY_MAX
op_logical_or
id|joydev-&gt;keypam
(braket
id|i
)braket
OL
id|BTN_MISC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|joydev-&gt;keymap
(braket
id|joydev-&gt;keypam
(braket
id|i
)braket
op_minus
id|BTN_MISC
)braket
op_assign
id|i
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|JSIOCGBTNMAP
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
id|__u16
op_star
)paren
id|arg
comma
id|joydev-&gt;keypam
comma
r_sizeof
(paren
id|__u16
)paren
op_star
(paren
id|KEY_MAX
op_minus
id|BTN_MISC
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
(paren
id|cmd
op_amp
op_complement
(paren
id|_IOC_SIZEMASK
op_lshift
id|_IOC_SIZESHIFT
)paren
)paren
op_eq
id|JSIOCGNAME
c_func
(paren
l_int|0
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
l_int|0
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
r_if
c_cond
(paren
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
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|joydev_fops
r_static
r_struct
id|file_operations
id|joydev_fops
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
id|joydev_read
comma
dot
id|write
op_assign
id|joydev_write
comma
dot
id|poll
op_assign
id|joydev_poll
comma
dot
id|open
op_assign
id|joydev_open
comma
dot
id|release
op_assign
id|joydev_release
comma
dot
id|ioctl
op_assign
id|joydev_ioctl
comma
dot
id|fasync
op_assign
id|joydev_fasync
comma
)brace
suffix:semicolon
DECL|function|joydev_connect
r_static
r_struct
id|input_handle
op_star
id|joydev_connect
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
id|joydev
op_star
id|joydev
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|t
comma
id|minor
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BTN_TOUCH
comma
id|dev-&gt;keybit
)paren
)paren
r_return
l_int|NULL
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
id|JOYDEV_MINORS
op_logical_and
id|joydev_table
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
id|JOYDEV_MINORS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;joydev: no more free joydev devices&bslash;n&quot;
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
id|joydev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|joydev
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
id|joydev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|joydev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|joydev-&gt;list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|joydev-&gt;wait
)paren
suffix:semicolon
id|joydev-&gt;minor
op_assign
id|minor
suffix:semicolon
id|joydev-&gt;exist
op_assign
l_int|1
suffix:semicolon
id|joydev-&gt;handle.dev
op_assign
id|dev
suffix:semicolon
id|joydev-&gt;handle.name
op_assign
id|joydev-&gt;name
suffix:semicolon
id|joydev-&gt;handle.handler
op_assign
id|handler
suffix:semicolon
id|joydev-&gt;handle
dot
r_private
op_assign
id|joydev
suffix:semicolon
id|sprintf
c_func
(paren
id|joydev-&gt;name
comma
l_string|&quot;js%d&quot;
comma
id|minor
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
id|ABS_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|dev-&gt;absbit
)paren
)paren
(brace
id|joydev-&gt;absmap
(braket
id|i
)braket
op_assign
id|joydev-&gt;nabs
suffix:semicolon
id|joydev-&gt;abspam
(braket
id|joydev-&gt;nabs
)braket
op_assign
id|i
suffix:semicolon
id|joydev-&gt;nabs
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|BTN_JOYSTICK
op_minus
id|BTN_MISC
suffix:semicolon
id|i
OL
id|KEY_MAX
op_minus
id|BTN_MISC
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
op_plus
id|BTN_MISC
comma
id|dev-&gt;keybit
)paren
)paren
(brace
id|joydev-&gt;keymap
(braket
id|i
)braket
op_assign
id|joydev-&gt;nkey
suffix:semicolon
id|joydev-&gt;keypam
(braket
id|joydev-&gt;nkey
)braket
op_assign
id|i
op_plus
id|BTN_MISC
suffix:semicolon
id|joydev-&gt;nkey
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BTN_JOYSTICK
op_minus
id|BTN_MISC
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
op_plus
id|BTN_MISC
comma
id|dev-&gt;keybit
)paren
)paren
(brace
id|joydev-&gt;keymap
(braket
id|i
)braket
op_assign
id|joydev-&gt;nkey
suffix:semicolon
id|joydev-&gt;keypam
(braket
id|joydev-&gt;nkey
)braket
op_assign
id|i
op_plus
id|BTN_MISC
suffix:semicolon
id|joydev-&gt;nkey
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|joydev-&gt;nabs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|joydev-&gt;abspam
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;absmax
(braket
id|j
)braket
op_eq
id|dev-&gt;absmin
(braket
id|j
)braket
)paren
(brace
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|type
op_assign
id|JS_CORR_NONE
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|type
op_assign
id|JS_CORR_BROKEN
suffix:semicolon
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|prec
op_assign
id|dev-&gt;absfuzz
(braket
id|j
)braket
suffix:semicolon
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|coef
(braket
l_int|0
)braket
op_assign
(paren
id|dev-&gt;absmax
(braket
id|j
)braket
op_plus
id|dev-&gt;absmin
(braket
id|j
)braket
)paren
op_div
l_int|2
op_minus
id|dev-&gt;absflat
(braket
id|j
)braket
suffix:semicolon
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|coef
(braket
l_int|1
)braket
op_assign
(paren
id|dev-&gt;absmax
(braket
id|j
)braket
op_plus
id|dev-&gt;absmin
(braket
id|j
)braket
)paren
op_div
l_int|2
op_plus
id|dev-&gt;absflat
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|t
op_assign
(paren
(paren
id|dev-&gt;absmax
(braket
id|j
)braket
op_minus
id|dev-&gt;absmin
(braket
id|j
)braket
)paren
op_div
l_int|2
op_minus
l_int|2
op_star
id|dev-&gt;absflat
(braket
id|j
)braket
)paren
)paren
)paren
r_continue
suffix:semicolon
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|coef
(braket
l_int|2
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
op_div
id|t
suffix:semicolon
id|joydev-&gt;corr
(braket
id|i
)braket
dot
id|coef
(braket
l_int|3
)braket
op_assign
(paren
l_int|1
op_lshift
l_int|29
)paren
op_div
id|t
suffix:semicolon
id|joydev-&gt;abs
(braket
id|i
)braket
op_assign
id|joydev_correct
c_func
(paren
id|dev-&gt;abs
(braket
id|j
)braket
comma
id|joydev-&gt;corr
op_plus
id|i
)paren
suffix:semicolon
)brace
id|joydev_table
(braket
id|minor
)braket
op_assign
id|joydev
suffix:semicolon
id|joydev-&gt;devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;js%d&quot;
comma
id|minor
comma
id|JOYDEV_MINOR_BASE
)paren
suffix:semicolon
r_return
op_amp
id|joydev-&gt;handle
suffix:semicolon
)brace
DECL|function|joydev_disconnect
r_static
r_void
id|joydev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|joydev
op_star
id|joydev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
id|joydev-&gt;exist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|joydev-&gt;open
)paren
(brace
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|joydev-&gt;devfs
)paren
suffix:semicolon
id|joydev_table
(braket
id|joydev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|joydev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|joydev_ids
r_static
r_struct
id|input_device_id
id|joydev_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
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
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_X
)paren
)brace
comma
)brace
comma
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
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
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_WHEEL
)paren
)brace
comma
)brace
comma
(brace
dot
id|flags
op_assign
id|INPUT_DEVICE_ID_MATCH_EVBIT
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
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_THROTTLE
)paren
)brace
comma
)brace
comma
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
id|joydev_ids
)paren
suffix:semicolon
DECL|variable|joydev_handler
r_static
r_struct
id|input_handler
id|joydev_handler
op_assign
(brace
dot
id|event
op_assign
id|joydev_event
comma
dot
id|connect
op_assign
id|joydev_connect
comma
dot
id|disconnect
op_assign
id|joydev_disconnect
comma
dot
id|fops
op_assign
op_amp
id|joydev_fops
comma
dot
id|minor
op_assign
id|JOYDEV_MINOR_BASE
comma
dot
id|name
op_assign
l_string|&quot;joydev&quot;
comma
dot
id|id_table
op_assign
id|joydev_ids
comma
)brace
suffix:semicolon
DECL|variable|joydev_intf
r_static
r_struct
id|device_interface
id|joydev_intf
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;joystick&quot;
comma
dot
id|devclass
op_assign
op_amp
id|input_devclass
comma
)brace
suffix:semicolon
DECL|function|joydev_init
r_static
r_int
id|__init
id|joydev_init
c_func
(paren
r_void
)paren
(brace
id|interface_register
c_func
(paren
op_amp
id|joydev_intf
)paren
suffix:semicolon
id|input_register_handler
c_func
(paren
op_amp
id|joydev_handler
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|joydev_exit
r_static
r_void
id|__exit
id|joydev_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_handler
c_func
(paren
op_amp
id|joydev_handler
)paren
suffix:semicolon
id|interface_unregister
c_func
(paren
op_amp
id|joydev_intf
)paren
suffix:semicolon
)brace
DECL|variable|joydev_init
id|module_init
c_func
(paren
id|joydev_init
)paren
suffix:semicolon
DECL|variable|joydev_exit
id|module_exit
c_func
(paren
id|joydev_exit
)paren
suffix:semicolon
eof
