multiline_comment|/*&n; *  User level driver support for input subsystem&n; *&n; * Heavily based on evdev.c by Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Author: Aristeu Sergio Rozanski Filho &lt;aris@cathedrallabs.org&gt;&n; *&n; * Changes/Revisions:&n; *&t;0.1&t;20/06/2002&n; *&t;&t;- first public version&n; */
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
id|udev-&gt;head
op_assign
(paren
id|udev-&gt;head
op_plus
l_int|1
)paren
op_mod
id|UINPUT_BUFFER_SIZE
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
id|udev-&gt;dev
op_member_access_from_pointer
r_private
op_assign
id|udev
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
id|set_bit
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
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|uinput_validate_absbits
r_static
r_int
id|uinput_validate_absbits
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|cnt
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|ABS_MAX
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|cnt
comma
id|dev-&gt;absbit
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*!dev-&gt;absmin[cnt] || !dev-&gt;absmax[cnt] || */
(paren
id|dev-&gt;absmax
(braket
id|cnt
)braket
op_le
id|dev-&gt;absmin
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
l_string|&quot;%s: invalid abs[%02x] min:%d max:%d&bslash;n&quot;
comma
id|UINPUT_NAME
comma
id|cnt
comma
id|dev-&gt;absmin
(braket
id|cnt
)braket
comma
id|dev-&gt;absmax
(braket
id|cnt
)braket
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dev-&gt;absflat
(braket
id|cnt
)braket
OL
id|dev-&gt;absmin
(braket
id|cnt
)braket
)paren
op_logical_or
(paren
id|dev-&gt;absflat
(braket
id|cnt
)braket
OG
id|dev-&gt;absmax
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
l_string|&quot;%s: absflat[%02x] out of range: %d &quot;
l_string|&quot;(min:%d/max:%d)&bslash;n&quot;
comma
id|UINPUT_NAME
comma
id|cnt
comma
id|dev-&gt;absflat
(braket
id|cnt
)braket
comma
id|dev-&gt;absmin
(braket
id|cnt
)braket
comma
id|dev-&gt;absmax
(braket
id|cnt
)braket
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
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
id|__user
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
r_struct
id|uinput_user_dev
op_star
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
id|user_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|user_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_dev
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
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
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
r_if
c_cond
(paren
l_int|NULL
op_ne
id|dev-&gt;name
)paren
id|kfree
c_func
(paren
id|dev-&gt;name
)paren
suffix:semicolon
id|size
op_assign
id|strnlen
c_func
(paren
id|user_dev-&gt;name
comma
id|UINPUT_MAX_NAME_SIZE
)paren
op_plus
l_int|1
suffix:semicolon
id|dev-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|size
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
id|strlcpy
c_func
(paren
id|dev-&gt;name
comma
id|user_dev-&gt;name
comma
id|size
)paren
suffix:semicolon
id|dev-&gt;id.bustype
op_assign
id|user_dev-&gt;id.bustype
suffix:semicolon
id|dev-&gt;id.vendor
op_assign
id|user_dev-&gt;id.vendor
suffix:semicolon
id|dev-&gt;id.product
op_assign
id|user_dev-&gt;id.product
suffix:semicolon
id|dev-&gt;id.version
op_assign
id|user_dev-&gt;id.version
suffix:semicolon
id|dev-&gt;ff_effects_max
op_assign
id|user_dev-&gt;ff_effects_max
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_int
)paren
op_star
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
id|user_dev-&gt;absmax
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absmin
comma
id|user_dev-&gt;absmin
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absfuzz
comma
id|user_dev-&gt;absfuzz
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;absflat
comma
id|user_dev-&gt;absflat
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
id|retval
op_assign
id|uinput_validate_absbits
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
id|kfree
c_func
(paren
id|dev-&gt;name
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
id|kfree
c_func
(paren
id|user_dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|uinput_write
r_static
id|ssize_t
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
id|uinput_device
op_star
id|udev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
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
id|uinput_device
op_star
id|udev
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
op_logical_neg
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|udev-&gt;head
op_eq
id|udev-&gt;tail
)paren
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
id|udev-&gt;waitq
comma
(paren
id|udev-&gt;head
op_ne
id|udev-&gt;tail
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
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
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
(paren
id|udev-&gt;head
op_ne
id|udev-&gt;tail
)paren
op_logical_and
(paren
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
id|UINPUT_BUFFER_SIZE
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
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
)paren
r_return
l_int|0
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
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
)paren
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
r_return
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
multiline_comment|/* device attributes can not be changed after the device is created */
r_if
c_cond
(paren
id|cmd
op_ge
id|UI_SET_EVBIT
op_logical_and
id|test_bit
c_func
(paren
id|UIST_CREATED
comma
op_amp
(paren
id|udev-&gt;state
)paren
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
r_if
c_cond
(paren
id|arg
OG
id|EV_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|KEY_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|REL_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|ABS_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|MSC_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|LED_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|SND_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|arg
OG
id|FF_MAX
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|uinput_open
comma
dot
id|release
op_assign
id|uinput_close
comma
dot
id|read
op_assign
id|uinput_read
comma
dot
id|write
op_assign
id|uinput_write
comma
dot
id|poll
op_assign
id|uinput_poll
comma
dot
id|ioctl
op_assign
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
dot
id|fops
op_assign
op_amp
id|uinput_fops
comma
dot
id|minor
op_assign
id|UINPUT_MINOR
comma
dot
id|name
op_assign
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
r_return
id|misc_register
c_func
(paren
op_amp
id|uinput_misc
)paren
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
