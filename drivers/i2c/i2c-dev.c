multiline_comment|/*&n;    i2c-dev.c - i2c-bus driver, char device interface  &n;&n;    Copyright (C) 1995-97 Simon G. Vogl&n;    Copyright (C) 1998-99 Frodo Looijaard &lt;frodol@dds.nl&gt;&n;    Copyright (C) 2003 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* Note that this is a complete rewrite of Simon Vogl&squot;s i2c-dev module.&n;   But I have used so much of his original code and ideas that it seems&n;   only fair to recognize him as co-author -- Frodo */
multiline_comment|/* The I2C_RDWR ioctl code is written by Kolja Waschk &lt;waschk@telos.de&gt; */
multiline_comment|/* The devfs code is contributed by Philipp Matthias Hahn &n;   &lt;pmhahn@titan.lahn.de&gt; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-dev.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|i2cdev_client_template
r_static
r_struct
id|i2c_client
id|i2cdev_client_template
suffix:semicolon
DECL|struct|i2c_dev
r_struct
id|i2c_dev
(brace
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|adap
r_struct
id|i2c_adapter
op_star
id|adap
suffix:semicolon
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
DECL|member|released
r_struct
id|completion
id|released
suffix:semicolon
multiline_comment|/* FIXME, we need a class_device_unregister() */
)brace
suffix:semicolon
DECL|macro|to_i2c_dev
mdefine_line|#define to_i2c_dev(d) container_of(d, struct i2c_dev, class_dev)
DECL|macro|I2C_MINORS
mdefine_line|#define I2C_MINORS&t;256
DECL|variable|i2c_dev_array
r_static
r_struct
id|i2c_dev
op_star
id|i2c_dev_array
(braket
id|I2C_MINORS
)braket
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|i2c_dev_array_lock
)paren
suffix:semicolon
DECL|function|i2c_dev_get_by_minor
r_static
r_struct
id|i2c_dev
op_star
id|i2c_dev_get_by_minor
c_func
(paren
r_int
id|index
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
id|i2c_dev
op_assign
id|i2c_dev_array
(braket
id|index
)braket
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
r_return
id|i2c_dev
suffix:semicolon
)brace
DECL|function|i2c_dev_get_by_adapter
r_static
r_struct
id|i2c_dev
op_star
id|i2c_dev_get_by_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i2c_dev_array
(braket
id|adap-&gt;nr
)braket
)paren
op_logical_and
(paren
id|i2c_dev_array
(braket
id|adap-&gt;nr
)braket
op_member_access_from_pointer
id|adap
op_eq
id|adap
)paren
)paren
id|i2c_dev
op_assign
id|i2c_dev_array
(braket
id|adap-&gt;nr
)braket
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
r_return
id|i2c_dev
suffix:semicolon
)brace
DECL|function|get_free_i2c_dev
r_static
r_struct
id|i2c_dev
op_star
id|get_free_i2c_dev
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
suffix:semicolon
id|i2c_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|i2c_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_dev
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|i2c_dev
comma
l_int|0x00
comma
r_sizeof
(paren
op_star
id|i2c_dev
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_dev_array
(braket
id|adap-&gt;nr
)braket
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;i2c-dev already has a device assigned to this adapter&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|i2c_dev-&gt;minor
op_assign
id|adap-&gt;nr
suffix:semicolon
id|i2c_dev_array
(braket
id|adap-&gt;nr
)braket
op_assign
id|i2c_dev
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
r_return
id|i2c_dev
suffix:semicolon
id|error
suffix:colon
id|kfree
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
DECL|function|return_i2c_dev
r_static
r_void
id|return_i2c_dev
c_func
(paren
r_struct
id|i2c_dev
op_star
id|i2c_dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
id|i2c_dev_array
(braket
id|i2c_dev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i2c_dev_array_lock
)paren
suffix:semicolon
)brace
DECL|function|show_adapter_name
r_static
id|ssize_t
id|show_adapter_name
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
op_assign
id|to_i2c_dev
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|i2c_dev-&gt;adap-&gt;name
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|name
comma
id|S_IRUGO
comma
id|show_adapter_name
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|i2cdev_read
r_static
id|ssize_t
id|i2cdev_read
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
op_assign
(paren
r_struct
id|i2c_client
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|8192
)paren
id|count
op_assign
l_int|8192
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i2c-dev: i2c-%d reading %zd bytes.&bslash;n&quot;
comma
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
comma
id|count
)paren
suffix:semicolon
id|ret
op_assign
id|i2c_master_recv
c_func
(paren
id|client
comma
id|tmp
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|ret
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|tmp
comma
id|count
)paren
ques
op_minus
id|EFAULT
suffix:colon
id|ret
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|i2cdev_write
r_static
id|ssize_t
id|i2cdev_write
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
op_assign
(paren
r_struct
id|i2c_client
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|8192
)paren
id|count
op_assign
l_int|8192
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|tmp
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;i2c-dev: i2c-%d writing %zd bytes.&bslash;n&quot;
comma
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
comma
id|count
)paren
suffix:semicolon
id|ret
op_assign
id|i2c_master_send
c_func
(paren
id|client
comma
id|tmp
comma
id|count
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|i2cdev_ioctl
r_static
r_int
id|i2cdev_ioctl
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
id|i2c_client
op_star
id|client
op_assign
(paren
r_struct
id|i2c_client
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|i2c_rdwr_ioctl_data
id|rdwr_arg
suffix:semicolon
r_struct
id|i2c_smbus_ioctl_data
id|data_arg
suffix:semicolon
r_union
id|i2c_smbus_data
id|temp
suffix:semicolon
r_struct
id|i2c_msg
op_star
id|rdwr_pa
suffix:semicolon
id|u8
id|__user
op_star
op_star
id|data_ptrs
suffix:semicolon
r_int
id|i
comma
id|datasize
comma
id|res
suffix:semicolon
r_int
r_int
id|funcs
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;adapter-&gt;dev
comma
l_string|&quot;i2c-%d ioctl, cmd: 0x%x, arg: %lx.&bslash;n&quot;
comma
id|iminor
c_func
(paren
id|inode
)paren
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|I2C_SLAVE
suffix:colon
r_case
id|I2C_SLAVE_FORCE
suffix:colon
r_if
c_cond
(paren
(paren
id|arg
OG
l_int|0x3ff
)paren
op_logical_or
(paren
(paren
(paren
id|client-&gt;flags
op_amp
id|I2C_M_TEN
)paren
op_eq
l_int|0
)paren
op_logical_and
id|arg
OG
l_int|0x7f
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_eq
id|I2C_SLAVE
)paren
op_logical_and
id|i2c_check_addr
c_func
(paren
id|client-&gt;adapter
comma
id|arg
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|client-&gt;addr
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|I2C_TENBIT
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|client-&gt;flags
op_or_assign
id|I2C_M_TEN
suffix:semicolon
r_else
id|client-&gt;flags
op_and_assign
op_complement
id|I2C_M_TEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|I2C_PEC
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|client-&gt;flags
op_or_assign
id|I2C_CLIENT_PEC
suffix:semicolon
r_else
id|client-&gt;flags
op_and_assign
op_complement
id|I2C_CLIENT_PEC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|I2C_FUNCS
suffix:colon
id|funcs
op_assign
id|i2c_get_functionality
c_func
(paren
id|client-&gt;adapter
)paren
suffix:semicolon
r_return
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
comma
op_amp
id|funcs
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
ques
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|I2C_RDWR
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rdwr_arg
comma
(paren
r_struct
id|i2c_rdwr_ioctl_data
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|rdwr_arg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Put an arbritrary limit on the number of messages that can&n;&t;&t; * be sent at once */
r_if
c_cond
(paren
id|rdwr_arg.nmsgs
OG
id|I2C_RDRW_IOCTL_MAX_MSGS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|rdwr_pa
op_assign
(paren
r_struct
id|i2c_msg
op_star
)paren
id|kmalloc
c_func
(paren
id|rdwr_arg.nmsgs
op_star
r_sizeof
(paren
r_struct
id|i2c_msg
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdwr_pa
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rdwr_pa
comma
id|rdwr_arg.msgs
comma
id|rdwr_arg.nmsgs
op_star
r_sizeof
(paren
r_struct
id|i2c_msg
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|rdwr_pa
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|data_ptrs
op_assign
id|kmalloc
c_func
(paren
id|rdwr_arg.nmsgs
op_star
r_sizeof
(paren
id|u8
id|__user
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_ptrs
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|rdwr_pa
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|res
op_assign
l_int|0
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
id|rdwr_arg.nmsgs
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Limit the size of the message to a sane amount */
r_if
c_cond
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|len
OG
l_int|8192
)paren
(brace
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|data_ptrs
(braket
id|i
)braket
op_assign
(paren
id|u8
id|__user
op_star
)paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
suffix:semicolon
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
op_assign
id|kmalloc
c_func
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
op_eq
l_int|NULL
)paren
(brace
id|res
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
comma
id|data_ptrs
(braket
id|i
)braket
comma
id|rdwr_pa
(braket
id|i
)braket
dot
id|len
)paren
)paren
(brace
op_increment
id|i
suffix:semicolon
multiline_comment|/* Needs to be kfreed too */
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
op_increment
id|j
)paren
id|kfree
c_func
(paren
id|rdwr_pa
(braket
id|j
)braket
dot
id|buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data_ptrs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rdwr_pa
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|res
op_assign
id|i2c_transfer
c_func
(paren
id|client-&gt;adapter
comma
id|rdwr_pa
comma
id|rdwr_arg.nmsgs
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|res
op_ge
l_int|0
op_logical_and
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|flags
op_amp
id|I2C_M_RD
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|data_ptrs
(braket
id|i
)braket
comma
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
comma
id|rdwr_pa
(braket
id|i
)braket
dot
id|len
)paren
)paren
(brace
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|rdwr_pa
(braket
id|i
)braket
dot
id|buf
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|data_ptrs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rdwr_pa
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
r_case
id|I2C_SMBUS
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data_arg
comma
(paren
r_struct
id|i2c_smbus_ioctl_data
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|i2c_smbus_ioctl_data
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_BYTE
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_QUICK
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_BYTE_DATA
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_WORD_DATA
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_PROC_CALL
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_BLOCK_DATA
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
op_logical_and
(paren
id|data_arg.size
op_ne
id|I2C_SMBUS_BLOCK_PROC_CALL
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;adapter-&gt;dev
comma
l_string|&quot;size out of range (%x) in ioctl I2C_SMBUS.&bslash;n&quot;
comma
id|data_arg.size
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Note that I2C_SMBUS_READ and I2C_SMBUS_WRITE are 0 and 1, &n;&t;&t;   so the check is valid if size==I2C_SMBUS_QUICK too. */
r_if
c_cond
(paren
(paren
id|data_arg.read_write
op_ne
id|I2C_SMBUS_READ
)paren
op_logical_and
(paren
id|data_arg.read_write
op_ne
id|I2C_SMBUS_WRITE
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;adapter-&gt;dev
comma
l_string|&quot;read_write out of range (%x) in ioctl I2C_SMBUS.&bslash;n&quot;
comma
id|data_arg.read_write
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Note that command values are always valid! */
r_if
c_cond
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_QUICK
)paren
op_logical_or
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_BYTE
)paren
op_logical_and
(paren
id|data_arg.read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
)paren
)paren
multiline_comment|/* These are special: we do not use data */
r_return
id|i2c_smbus_xfer
c_func
(paren
id|client-&gt;adapter
comma
id|client-&gt;addr
comma
id|client-&gt;flags
comma
id|data_arg.read_write
comma
id|data_arg.command
comma
id|data_arg.size
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_arg.data
op_eq
l_int|NULL
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;adapter-&gt;dev
comma
l_string|&quot;data is NULL pointer in ioctl I2C_SMBUS.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_BYTE_DATA
)paren
op_logical_or
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_BYTE
)paren
)paren
id|datasize
op_assign
r_sizeof
(paren
id|data_arg.data-&gt;byte
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_WORD_DATA
)paren
op_logical_or
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_PROC_CALL
)paren
)paren
id|datasize
op_assign
r_sizeof
(paren
id|data_arg.data-&gt;word
)paren
suffix:semicolon
r_else
multiline_comment|/* size == smbus block, i2c block, or block proc. call */
id|datasize
op_assign
r_sizeof
(paren
id|data_arg.data-&gt;block
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_PROC_CALL
)paren
op_logical_or
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_BLOCK_PROC_CALL
)paren
op_logical_or
(paren
id|data_arg.read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|temp
comma
id|data_arg.data
comma
id|datasize
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|res
op_assign
id|i2c_smbus_xfer
c_func
(paren
id|client-&gt;adapter
comma
id|client-&gt;addr
comma
id|client-&gt;flags
comma
id|data_arg.read_write
comma
id|data_arg.command
comma
id|data_arg.size
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
op_logical_and
(paren
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_PROC_CALL
)paren
op_logical_or
(paren
id|data_arg.size
op_eq
id|I2C_SMBUS_BLOCK_PROC_CALL
)paren
op_logical_or
(paren
id|data_arg.read_write
op_eq
id|I2C_SMBUS_READ
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|data_arg.data
comma
op_amp
id|temp
comma
id|datasize
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
r_default
suffix:colon
r_return
id|i2c_control
c_func
(paren
id|client
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2cdev_open
r_static
r_int
id|i2cdev_open
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
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|i2c_adapter
op_star
id|adap
suffix:semicolon
r_struct
id|i2c_dev
op_star
id|i2c_dev
suffix:semicolon
id|i2c_dev
op_assign
id|i2c_dev_get_by_minor
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|adap
op_assign
id|i2c_get_adapter
c_func
(paren
id|i2c_dev-&gt;adap-&gt;nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adap
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|client
)paren
(brace
id|i2c_put_adapter
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|client
comma
op_amp
id|i2cdev_client_template
comma
r_sizeof
(paren
op_star
id|client
)paren
)paren
suffix:semicolon
multiline_comment|/* registered with adapter, passed as client to user */
id|client-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|file-&gt;private_data
op_assign
id|client
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2cdev_release
r_static
r_int
id|i2cdev_release
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
id|i2c_client
op_star
id|client
op_assign
id|file-&gt;private_data
suffix:semicolon
id|i2c_put_adapter
c_func
(paren
id|client-&gt;adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|i2cdev_fops
r_static
r_struct
id|file_operations
id|i2cdev_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|i2cdev_read
comma
dot
id|write
op_assign
id|i2cdev_write
comma
dot
id|ioctl
op_assign
id|i2cdev_ioctl
comma
dot
id|open
op_assign
id|i2cdev_open
comma
dot
id|release
op_assign
id|i2cdev_release
comma
)brace
suffix:semicolon
DECL|function|release_i2c_dev
r_static
r_void
id|release_i2c_dev
c_func
(paren
r_struct
id|class_device
op_star
id|dev
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
op_assign
id|to_i2c_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|i2c_dev-&gt;released
)paren
suffix:semicolon
)brace
DECL|variable|i2c_dev_class
r_static
r_struct
r_class
id|i2c_dev_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2c-dev&quot;
comma
dot
id|release
op_assign
op_amp
id|release_i2c_dev
comma
)brace
suffix:semicolon
DECL|function|i2cdev_attach_adapter
r_static
r_int
id|i2cdev_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|i2c_dev
op_assign
id|get_free_i2c_dev
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|i2c_dev
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|I2C_MAJOR
comma
id|i2c_dev-&gt;minor
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;i2c/%d&quot;
comma
id|i2c_dev-&gt;minor
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Registered as minor %d&bslash;n&quot;
comma
id|i2c_dev-&gt;minor
)paren
suffix:semicolon
multiline_comment|/* register this i2c device with the driver core */
id|i2c_dev-&gt;adap
op_assign
id|adap
suffix:semicolon
r_if
c_cond
(paren
id|adap-&gt;dev.parent
op_eq
op_amp
id|platform_bus
)paren
id|i2c_dev-&gt;class_dev.dev
op_assign
op_amp
id|adap-&gt;dev
suffix:semicolon
r_else
id|i2c_dev-&gt;class_dev.dev
op_assign
id|adap-&gt;dev.parent
suffix:semicolon
id|i2c_dev-&gt;class_dev
dot
r_class
op_assign
op_amp
id|i2c_dev_class
suffix:semicolon
id|i2c_dev-&gt;class_dev.devt
op_assign
id|MKDEV
c_func
(paren
id|I2C_MAJOR
comma
id|i2c_dev-&gt;minor
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|i2c_dev-&gt;class_dev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;i2c-%d&quot;
comma
id|i2c_dev-&gt;minor
)paren
suffix:semicolon
id|retval
op_assign
id|class_device_register
c_func
(paren
op_amp
id|i2c_dev-&gt;class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error
suffix:semicolon
id|class_device_create_file
c_func
(paren
op_amp
id|i2c_dev-&gt;class_dev
comma
op_amp
id|class_device_attr_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|return_i2c_dev
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|i2cdev_detach_adapter
r_static
r_int
id|i2cdev_detach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_dev
op_star
id|i2c_dev
suffix:semicolon
id|i2c_dev
op_assign
id|i2c_dev_get_by_adapter
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|i2c_dev-&gt;released
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;i2c/%d&quot;
comma
id|i2c_dev-&gt;minor
)paren
suffix:semicolon
id|return_i2c_dev
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|i2c_dev-&gt;class_dev
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|i2c_dev-&gt;released
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i2c_dev
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Adapter unregistered&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2cdev_detach_client
r_static
r_int
id|i2cdev_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2cdev_command
r_static
r_int
id|i2cdev_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|i2cdev_driver
r_static
r_struct
id|i2c_driver
id|i2cdev_driver
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
l_string|&quot;dev_driver&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_I2CDEV
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|i2cdev_attach_adapter
comma
dot
id|detach_adapter
op_assign
id|i2cdev_detach_adapter
comma
dot
id|detach_client
op_assign
id|i2cdev_detach_client
comma
dot
id|command
op_assign
id|i2cdev_command
comma
)brace
suffix:semicolon
DECL|variable|i2cdev_client_template
r_static
r_struct
id|i2c_client
id|i2cdev_client_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;I2C /dev entry&quot;
comma
dot
id|addr
op_assign
op_minus
l_int|1
comma
dot
id|driver
op_assign
op_amp
id|i2cdev_driver
comma
)brace
suffix:semicolon
DECL|function|i2c_dev_init
r_static
r_int
id|__init
id|i2c_dev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|res
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c /dev entries driver&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
id|register_chrdev
c_func
(paren
id|I2C_MAJOR
comma
l_string|&quot;i2c&quot;
comma
op_amp
id|i2cdev_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
id|res
op_assign
id|class_register
c_func
(paren
op_amp
id|i2c_dev_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out_unreg_chrdev
suffix:semicolon
id|res
op_assign
id|i2c_add_driver
c_func
(paren
op_amp
id|i2cdev_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out_unreg_class
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;i2c&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_unreg_class
suffix:colon
id|class_unregister
c_func
(paren
op_amp
id|i2c_dev_class
)paren
suffix:semicolon
id|out_unreg_chrdev
suffix:colon
id|unregister_chrdev
c_func
(paren
id|I2C_MAJOR
comma
l_string|&quot;i2c&quot;
)paren
suffix:semicolon
id|out
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Driver Initialisation failed&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|i2c_dev_exit
r_static
r_void
id|__exit
id|i2c_dev_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|i2cdev_driver
)paren
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|i2c_dev_class
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;i2c&quot;
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|I2C_MAJOR
comma
l_string|&quot;i2c&quot;
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt; and &quot;
l_string|&quot;Simon G. Vogl &lt;simon@tk.uni-linz.ac.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C /dev entries driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_dev_init
id|module_init
c_func
(paren
id|i2c_dev_init
)paren
suffix:semicolon
DECL|variable|i2c_dev_exit
id|module_exit
c_func
(paren
id|i2c_dev_exit
)paren
suffix:semicolon
eof
