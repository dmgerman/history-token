multiline_comment|/*&n; * Raw serio device providing access to a raw byte stream from underlying&n; * serio port. Closely emulates behavior of pre-2.6 /dev/psaux device&n; *&n; * Copyright (c) 2004 Dmitry Torokhov&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;Raw serio driver&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dmitry Torokhov &lt;dtor@mail.ru&gt;&quot;
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
DECL|macro|SERIO_RAW_QUEUE_LEN
mdefine_line|#define SERIO_RAW_QUEUE_LEN&t;64
DECL|struct|serio_raw
r_struct
id|serio_raw
(brace
DECL|member|queue
r_int
r_char
id|queue
(braket
id|SERIO_RAW_QUEUE_LEN
)braket
suffix:semicolon
DECL|member|tail
DECL|member|head
r_int
r_int
id|tail
comma
id|head
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|refcnt
r_int
r_int
id|refcnt
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|dev
r_struct
id|miscdevice
id|dev
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
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|serio_raw_list
r_struct
id|serio_raw_list
(brace
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|serio_raw
r_struct
id|serio_raw
op_star
id|serio_raw
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|serio_raw_sem
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|serio_raw_list
)paren
suffix:semicolon
DECL|variable|serio_raw_no
r_static
r_int
r_int
id|serio_raw_no
suffix:semicolon
multiline_comment|/*********************************************************************&n; *             Interface with userspace (file operations)            *&n; *********************************************************************/
DECL|function|serio_raw_fasync
r_static
r_int
id|serio_raw_fasync
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
id|serio_raw_list
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
DECL|function|serio_raw_locate
r_static
r_struct
id|serio_raw
op_star
id|serio_raw_locate
c_func
(paren
r_int
id|minor
)paren
(brace
r_struct
id|serio_raw
op_star
id|serio_raw
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|serio_raw
comma
op_amp
id|serio_raw_list
comma
id|node
)paren
(brace
r_if
c_cond
(paren
id|serio_raw-&gt;dev.minor
op_eq
id|minor
)paren
r_return
id|serio_raw
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|serio_raw_open
r_static
r_int
id|serio_raw_open
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
id|serio_raw
op_star
id|serio_raw
suffix:semicolon
r_struct
id|serio_raw_list
op_star
id|list
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|down_interruptible
c_func
(paren
op_amp
id|serio_raw_sem
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
(paren
id|serio_raw
op_assign
id|serio_raw_locate
c_func
(paren
id|iminor
c_func
(paren
id|inode
)paren
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|serio_raw-&gt;serio
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
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
id|serio_raw_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|serio_raw_list
)paren
)paren
suffix:semicolon
id|list-&gt;serio_raw
op_assign
id|serio_raw
suffix:semicolon
id|file-&gt;private_data
op_assign
id|list
suffix:semicolon
id|serio_raw-&gt;refcnt
op_increment
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|list-&gt;node
comma
op_amp
id|serio_raw-&gt;list
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|serio_raw_cleanup
r_static
r_int
id|serio_raw_cleanup
c_func
(paren
r_struct
id|serio_raw
op_star
id|serio_raw
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|serio_raw-&gt;refcnt
op_eq
l_int|0
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|serio_raw-&gt;dev
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|serio_raw-&gt;node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serio_raw
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_raw_release
r_static
r_int
id|serio_raw_release
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
id|serio_raw_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|serio_raw
op_star
id|serio_raw
op_assign
id|list-&gt;serio_raw
suffix:semicolon
id|down
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
id|serio_raw_fasync
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
id|serio_raw_cleanup
c_func
(paren
id|serio_raw
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_raw_fetch_byte
r_static
r_int
id|serio_raw_fetch_byte
c_func
(paren
r_struct
id|serio_raw
op_star
id|serio_raw
comma
r_char
op_star
id|c
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|empty
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|serio_raw-&gt;serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|empty
op_assign
id|serio_raw-&gt;head
op_eq
id|serio_raw-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty
)paren
(brace
op_star
id|c
op_assign
id|serio_raw-&gt;queue
(braket
id|serio_raw-&gt;tail
)braket
suffix:semicolon
id|serio_raw-&gt;tail
op_assign
(paren
id|serio_raw-&gt;tail
op_plus
l_int|1
)paren
op_mod
id|SERIO_RAW_QUEUE_LEN
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|serio_raw-&gt;serio-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_logical_neg
id|empty
suffix:semicolon
)brace
DECL|function|serio_raw_read
r_static
id|ssize_t
id|serio_raw_read
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
id|serio_raw_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|serio_raw
op_star
id|serio_raw
op_assign
id|list-&gt;serio_raw
suffix:semicolon
r_char
id|c
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serio_raw-&gt;serio
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|serio_raw-&gt;head
op_eq
id|serio_raw-&gt;tail
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
id|list-&gt;serio_raw-&gt;wait
comma
id|serio_raw-&gt;head
op_ne
id|serio_raw-&gt;tail
op_logical_or
op_logical_neg
id|serio_raw-&gt;serio
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
id|serio_raw-&gt;serio
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
op_logical_and
id|serio_raw_fetch_byte
c_func
(paren
id|serio_raw
comma
op_amp
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|retval
op_increment
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|serio_raw_write
r_static
id|ssize_t
id|serio_raw_write
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
id|serio_raw_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|ssize_t
id|written
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|retval
op_assign
id|down_interruptible
c_func
(paren
op_amp
id|serio_raw_sem
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
id|list-&gt;serio_raw-&gt;serio
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|32
)paren
id|count
op_assign
l_int|32
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serio_write
c_func
(paren
id|list-&gt;serio_raw-&gt;serio
comma
id|c
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|written
op_increment
suffix:semicolon
)brace
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
DECL|function|serio_raw_poll
r_static
r_int
r_int
id|serio_raw_poll
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
id|serio_raw_list
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
id|list-&gt;serio_raw-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;serio_raw-&gt;head
op_ne
id|list-&gt;serio_raw-&gt;tail
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
DECL|variable|serio_raw_fops
r_struct
id|file_operations
id|serio_raw_fops
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
id|serio_raw_open
comma
dot
id|release
op_assign
id|serio_raw_release
comma
dot
id|read
op_assign
id|serio_raw_read
comma
dot
id|write
op_assign
id|serio_raw_write
comma
dot
id|poll
op_assign
id|serio_raw_poll
comma
dot
id|fasync
op_assign
id|serio_raw_fasync
comma
)brace
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                   Interface with serio port   &t;             *&n; *********************************************************************/
DECL|function|serio_raw_interrupt
r_static
id|irqreturn_t
id|serio_raw_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|dfl
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|serio_raw
op_star
id|serio_raw
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|serio_raw_list
op_star
id|list
suffix:semicolon
r_int
r_int
id|head
op_assign
id|serio_raw-&gt;head
suffix:semicolon
multiline_comment|/* we are holding serio-&gt;lock here so we are prootected */
id|serio_raw-&gt;queue
(braket
id|head
)braket
op_assign
id|data
suffix:semicolon
id|head
op_assign
(paren
id|head
op_plus
l_int|1
)paren
op_mod
id|SERIO_RAW_QUEUE_LEN
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|head
op_ne
id|serio_raw-&gt;tail
)paren
)paren
(brace
id|serio_raw-&gt;head
op_assign
id|head
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|list
comma
op_amp
id|serio_raw-&gt;list
comma
id|node
)paren
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
id|wake_up_interruptible
c_func
(paren
op_amp
id|serio_raw-&gt;wait
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|serio_raw_connect
r_static
r_void
id|serio_raw_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|serio_raw
op_star
id|serio_raw
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_8042
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|serio_raw
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serio_raw
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;serio_raw.c: can&squot;t allocate memory for a device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
id|memset
c_func
(paren
id|serio_raw
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serio_raw
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|serio_raw-&gt;name
comma
r_sizeof
(paren
id|serio_raw-&gt;name
)paren
comma
l_string|&quot;serio_raw%d&quot;
comma
id|serio_raw_no
op_increment
)paren
suffix:semicolon
id|serio_raw-&gt;refcnt
op_assign
l_int|1
suffix:semicolon
id|serio_raw-&gt;serio
op_assign
id|serio
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|serio_raw-&gt;list
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|serio_raw-&gt;wait
)paren
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|serio_raw
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|drv
)paren
)paren
r_goto
id|out_free
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|serio_raw-&gt;node
comma
op_amp
id|serio_raw_list
)paren
suffix:semicolon
id|serio_raw-&gt;dev.minor
op_assign
id|PSMOUSE_MINOR
suffix:semicolon
id|serio_raw-&gt;dev.name
op_assign
id|serio_raw-&gt;name
suffix:semicolon
id|serio_raw-&gt;dev.fops
op_assign
op_amp
id|serio_raw_fops
suffix:semicolon
id|err
op_assign
id|misc_register
c_func
(paren
op_amp
id|serio_raw-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|serio_raw-&gt;dev.minor
op_assign
id|MISC_DYNAMIC_MINOR
suffix:semicolon
id|err
op_assign
id|misc_register
c_func
(paren
op_amp
id|serio_raw-&gt;dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio_raw: failed to register raw access device for %s&bslash;n&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio_raw: raw access enabled on %s (%s, minor %d)&bslash;n&quot;
comma
id|serio-&gt;phys
comma
id|serio_raw-&gt;name
comma
id|serio_raw-&gt;dev.minor
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_close
suffix:colon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|serio_raw-&gt;node
)paren
suffix:semicolon
id|out_free
suffix:colon
id|serio
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|serio_raw
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
)brace
DECL|function|serio_raw_reconnect
r_static
r_int
id|serio_raw_reconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_raw
op_star
id|serio_raw
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|serio_driver
op_star
id|drv
op_assign
id|serio-&gt;drv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
op_logical_or
op_logical_neg
id|serio_raw
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;serio_raw: reconnect request, but serio is disconnected, ignoring...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Nothing needs to be done here, we just need this method to&n;&t; * keep the same device.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_raw_disconnect
r_static
r_void
id|serio_raw_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|serio_raw
op_star
id|serio_raw
suffix:semicolon
id|down
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
id|serio_raw
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|serio_raw-&gt;serio
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serio_raw_cleanup
c_func
(paren
id|serio_raw
)paren
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|serio_raw-&gt;wait
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|serio_raw_sem
)paren
suffix:semicolon
)brace
DECL|variable|serio_raw_drv
r_static
r_struct
id|serio_driver
id|serio_raw_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serio_raw&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|interrupt
op_assign
id|serio_raw_interrupt
comma
dot
id|connect
op_assign
id|serio_raw_connect
comma
dot
id|reconnect
op_assign
id|serio_raw_reconnect
comma
dot
id|disconnect
op_assign
id|serio_raw_disconnect
comma
dot
id|manual_bind
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|serio_raw_init
r_int
id|__init
id|serio_raw_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|serio_raw_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serio_raw_exit
r_void
id|__exit
id|serio_raw_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|serio_raw_drv
)paren
suffix:semicolon
)brace
DECL|variable|serio_raw_init
id|module_init
c_func
(paren
id|serio_raw_init
)paren
suffix:semicolon
DECL|variable|serio_raw_exit
id|module_exit
c_func
(paren
id|serio_raw_exit
)paren
suffix:semicolon
eof
