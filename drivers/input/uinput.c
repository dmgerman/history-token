multiline_comment|/*&n; *  User level driver support for input subsystem&n; *&n; * Heavily based on evdev.c by Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Author: Aristeu Sergio Rozanski Filho &lt;aris@cathedrallabs.org&gt;&n; * &n; * Changes/Revisions:&n; *&t;0.1&t;20/06/2002&n; *&t;&t;- first public version&n; */
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/uinput.h&gt;
DECL|function|uinput_dev_open
r_static
r_int
id|uinput_dev_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_dev_close
r_static
r_void
id|uinput_dev_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
)brace
DECL|function|uinput_dev_event
r_static
r_int
id|uinput_dev_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
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
id|uinput_device
op_star
id|udev
suffix:semicolon
id|udev
op_assign
(paren
r_struct
id|uinput_device
op_star
)paren
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|udev-&gt;head
op_assign
(paren
id|udev-&gt;head
op_plus
l_int|1
)paren
op_amp
l_int|0xF
suffix:semicolon
id|udev-&gt;buff
(braket
id|udev-&gt;head
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|udev-&gt;buff
(braket
id|udev-&gt;head
)braket
dot
id|code
op_assign
id|code
suffix:semicolon
id|udev-&gt;buff
(braket
id|udev-&gt;head
)braket
dot
id|value
op_assign
id|value
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|udev-&gt;buff
(braket
id|udev-&gt;head
)braket
dot
id|time
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|udev-&gt;waitq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_dev_upload_effect
r_static
r_int
id|uinput_dev_upload_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ff_effect
op_star
id|effect
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_dev_erase_effect
r_static
r_int
id|uinput_dev_erase_effect
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
id|effect_id
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_create_device
r_static
r_int
id|uinput_create_device
c_func
(paren
r_struct
id|uinput_device
op_star
id|udev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|udev-&gt;dev-&gt;name
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: write device info first&bslash;n&quot;
comma
id|UINPUT_NAME
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|udev-&gt;dev-&gt;open
op_assign
id|uinput_dev_open
suffix:semicolon
id|udev-&gt;dev-&gt;close
op_assign
id|uinput_dev_close
suffix:semicolon
id|udev-&gt;dev-&gt;event
op_assign
id|uinput_dev_event
suffix:semicolon
id|udev-&gt;dev-&gt;upload_effect
op_assign
id|uinput_dev_upload_effect
suffix:semicolon
id|udev-&gt;dev-&gt;erase_effect
op_assign
id|uinput_dev_erase_effect
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
(paren
id|udev-&gt;waitq
)paren
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
id|udev-&gt;dev
)paren
suffix:semicolon
id|udev-&gt;state
op_or_assign
id|UIST_CREATED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_destroy_device
r_static
r_int
id|uinput_destroy_device
c_func
(paren
r_struct
id|uinput_device
op_star
id|udev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|udev-&gt;state
op_amp
id|UIST_CREATED
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: create the device first&bslash;n&quot;
comma
id|UINPUT_NAME
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|input_unregister_device
c_func
(paren
id|udev-&gt;dev
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_open
r_static
r_int
id|uinput_open
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
id|uinput_device
op_star
id|newdev
suffix:semicolon
r_struct
id|input_dev
op_star
id|newinput
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|newdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|uinput_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newdev
)paren
r_goto
id|error
suffix:semicolon
id|memset
c_func
(paren
id|newdev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|uinput_device
)paren
)paren
suffix:semicolon
id|newinput
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|input_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newinput
)paren
r_goto
id|cleanup
suffix:semicolon
id|memset
c_func
(paren
id|newinput
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|input_dev
)paren
)paren
suffix:semicolon
id|newdev-&gt;dev
op_assign
id|newinput
suffix:semicolon
id|file-&gt;private_data
op_assign
id|newdev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|cleanup
suffix:colon
id|kfree
c_func
(paren
id|newdev
)paren
suffix:semicolon
id|error
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|uinput_alloc_device
r_static
r_int
id|uinput_alloc_device
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
)paren
(brace
r_struct
id|uinput_user_dev
id|user_dev
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
r_struct
id|uinput_device
op_star
id|udev
suffix:semicolon
r_int
id|size
comma
id|retval
suffix:semicolon
id|retval
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user_dev
comma
id|buffer
comma
r_sizeof
(paren
r_struct
id|uinput_user_dev
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
m_exit
suffix:semicolon
)brace
id|udev
op_assign
(paren
r_struct
id|uinput_device
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|dev
op_assign
id|udev-&gt;dev
suffix:semicolon
id|size
op_assign
id|strnlen
c_func
(paren
id|user_dev.name
comma
id|UINPUT_MAX_NAME_SIZE
)paren
suffix:semicolon
id|dev-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|size
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;name
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|user_dev.name
comma
id|size
)paren
suffix:semicolon
id|dev-&gt;name
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|dev-&gt;idbus
op_assign
id|user_dev.idbus
suffix:semicolon
id|dev-&gt;idvendor
op_assign
id|user_dev.idvendor
suffix:semicolon
id|dev-&gt;idproduct
op_assign
id|user_dev.idproduct
suffix:semicolon
id|dev-&gt;idversion
op_assign
id|user_dev.idversion
suffix:semicolon
id|dev-&gt;ff_effects_max
op_assign
id|user_dev.ff_effects_max
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_int
r_int
)paren
op_star
id|NBITS
c_func
(paren
id|ABS_MAX
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absmax
comma
id|user_dev.absmax
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absmin
comma
id|user_dev.absmin
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absfuzz
comma
id|user_dev.absfuzz
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absflat
comma
id|user_dev.absflat
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* check if absmin/absmax/absfuzz/absflat are filled as&n;&t; * told in Documentation/input/input-programming.txt */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|EV_ABS
comma
id|dev-&gt;evbit
)paren
)paren
(brace
r_int
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|1
suffix:semicolon
id|cnt
OL
id|ABS_MAX
suffix:semicolon
id|cnt
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|cnt
comma
id|dev-&gt;absbit
)paren
op_logical_and
(paren
op_logical_neg
id|dev-&gt;absmin
(braket
id|cnt
)braket
op_logical_or
op_logical_neg
id|dev-&gt;absmax
(braket
id|cnt
)braket
op_logical_or
op_logical_neg
id|dev-&gt;absfuzz
(braket
id|cnt
)braket
op_logical_or
op_logical_neg
id|dev-&gt;absflat
(braket
id|cnt
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: set abs fields &quot;
l_string|&quot;first&bslash;n&quot;
comma
id|UINPUT_NAME
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|free_name
suffix:semicolon
)brace
)brace
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
id|free_name
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
DECL|function|uinput_write
r_static
r_int
id|uinput_write
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
id|uinput_device
op_star
id|udev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;state
op_amp
id|UIST_CREATED
)paren
(brace
r_struct
id|input_event
id|ev
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ev
comma
id|buffer
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
id|udev-&gt;dev
comma
id|ev.type
comma
id|ev.code
comma
id|ev.value
)paren
suffix:semicolon
)brace
r_else
id|count
op_assign
id|uinput_alloc_device
c_func
(paren
id|file
comma
id|buffer
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|uinput_read
r_static
id|ssize_t
id|uinput_read
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
id|uinput_device
op_star
id|udev
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|waitq
comma
id|current
)paren
suffix:semicolon
id|udev
op_assign
(paren
r_struct
id|uinput_device
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;head
op_eq
id|udev-&gt;tail
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|udev-&gt;waitq
comma
op_amp
id|waitq
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_while
c_loop
(paren
id|udev-&gt;head
op_eq
id|udev-&gt;tail
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|udev-&gt;state
op_amp
id|UIST_CREATED
)paren
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
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|udev-&gt;waitq
comma
op_amp
id|waitq
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
id|udev-&gt;head
op_ne
id|udev-&gt;tail
op_logical_and
id|retval
op_plus
r_sizeof
(paren
r_struct
id|uinput_device
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
op_amp
(paren
id|udev-&gt;buff
(braket
id|udev-&gt;tail
)braket
)paren
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
id|udev-&gt;tail
op_assign
(paren
id|udev-&gt;tail
op_plus
l_int|1
)paren
op_mod
(paren
id|UINPUT_BUFFER_SIZE
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
DECL|function|uinput_poll
r_static
r_int
r_int
id|uinput_poll
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
id|uinput_device
op_star
id|udev
op_assign
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|udev-&gt;waitq
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;head
op_ne
id|udev-&gt;tail
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
DECL|function|uinput_burn_device
r_static
r_int
id|uinput_burn_device
c_func
(paren
r_struct
id|uinput_device
op_star
id|udev
)paren
(brace
r_if
c_cond
(paren
id|udev-&gt;state
op_amp
id|UIST_CREATED
)paren
id|uinput_destroy_device
c_func
(paren
id|udev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|udev-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|udev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uinput_close
r_static
r_int
id|uinput_close
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
id|retval
suffix:semicolon
id|retval
op_assign
id|uinput_burn_device
c_func
(paren
(paren
r_struct
id|uinput_device
op_star
)paren
id|file-&gt;private_data
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|uinput_ioctl
r_static
r_int
id|uinput_ioctl
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
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|uinput_device
op_star
id|udev
suffix:semicolon
id|udev
op_assign
(paren
r_struct
id|uinput_device
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ge
id|UI_SET_EVBIT
op_logical_and
(paren
id|udev-&gt;state
op_amp
id|UIST_CREATED
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|UI_DEV_CREATE
suffix:colon
id|retval
op_assign
id|uinput_create_device
c_func
(paren
id|udev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_DEV_DESTROY
suffix:colon
id|retval
op_assign
id|uinput_destroy_device
c_func
(paren
id|udev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_EVBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;evbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_KEYBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;keybit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_RELBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;relbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_ABSBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;absbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_MSCBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;mscbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_LEDBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;ledbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_SNDBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;sndbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UI_SET_FFBIT
suffix:colon
id|set_bit
c_func
(paren
id|arg
comma
id|udev-&gt;dev-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|uinput_fops
r_struct
id|file_operations
id|uinput_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|uinput_open
comma
id|release
suffix:colon
id|uinput_close
comma
id|read
suffix:colon
id|uinput_read
comma
id|write
suffix:colon
id|uinput_write
comma
id|poll
suffix:colon
id|uinput_poll
comma
singleline_comment|//&t;fasync:&t;&t;uinput_fasync,
id|ioctl
suffix:colon
id|uinput_ioctl
comma
)brace
suffix:semicolon
DECL|variable|uinput_misc
r_static
r_struct
id|miscdevice
id|uinput_misc
op_assign
(brace
id|fops
suffix:colon
op_amp
id|uinput_fops
comma
id|minor
suffix:colon
id|UINPUT_MINOR
comma
id|name
suffix:colon
id|UINPUT_NAME
comma
)brace
suffix:semicolon
DECL|function|uinput_init
r_static
r_int
id|__init
id|uinput_init
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
id|misc_register
c_func
(paren
op_amp
id|uinput_misc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: User level driver support for input subsystem loaded&bslash;n&quot;
comma
id|UINPUT_NAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Aristeu Sergio Rozanski Filho &lt;aris@cathedrallabs.org&gt;&bslash;n&quot;
comma
id|UINPUT_NAME
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|uinput_exit
r_static
r_void
id|__exit
id|uinput_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|uinput_misc
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Aristeu Sergio Rozanski Filho&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;User level driver support for input subsystem&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|uinput_init
id|module_init
c_func
(paren
id|uinput_init
)paren
suffix:semicolon
DECL|variable|uinput_exit
id|module_exit
c_func
(paren
id|uinput_exit
)paren
suffix:semicolon
eof
