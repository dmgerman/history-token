multiline_comment|/* &n; * dvbdev.c&n; *&n; * Copyright (C) 2000 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                  &amp; Marcus Metzler &lt;marcus@convergence.de&gt;&n; *                    for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|variable|dvbdev_debug
r_static
r_int
id|dvbdev_debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk if (dvbdev_debug) printk
r_static
id|LIST_HEAD
c_func
(paren
id|dvb_adapter_list
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|dvbdev_register_lock
)paren
suffix:semicolon
DECL|variable|dnames
r_static
r_char
op_star
id|dnames
(braket
)braket
op_assign
(brace
l_string|&quot;video&quot;
comma
l_string|&quot;audio&quot;
comma
l_string|&quot;sec&quot;
comma
l_string|&quot;frontend&quot;
comma
l_string|&quot;demux&quot;
comma
l_string|&quot;dvr&quot;
comma
l_string|&quot;ca&quot;
comma
l_string|&quot;net&quot;
comma
l_string|&quot;osd&quot;
)brace
suffix:semicolon
DECL|macro|DVB_MAX_IDS
mdefine_line|#define DVB_MAX_IDS              4
DECL|macro|nums2minor
mdefine_line|#define nums2minor(num,type,id)  ((num &lt;&lt; 6) | (id &lt;&lt; 4) | type)
DECL|function|dvbdev_find_device
r_static
r_struct
id|dvb_device
op_star
id|dvbdev_find_device
(paren
r_int
id|minor
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|dvb_adapter_list
)paren
(brace
r_struct
id|list_head
op_star
id|entry0
suffix:semicolon
r_struct
id|dvb_adapter
op_star
id|adap
suffix:semicolon
id|adap
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|dvb_adapter
comma
id|list_head
)paren
suffix:semicolon
id|list_for_each
(paren
id|entry0
comma
op_amp
id|adap-&gt;device_list
)paren
(brace
r_struct
id|dvb_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|list_entry
(paren
id|entry0
comma
r_struct
id|dvb_device
comma
id|list_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nums2minor
c_func
(paren
id|adap-&gt;num
comma
id|dev-&gt;type
comma
id|dev-&gt;id
)paren
op_eq
id|minor
)paren
r_return
id|dev
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dvb_device_open
r_static
r_int
id|dvb_device_open
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
id|dvb_device
op_star
id|dvbdev
suffix:semicolon
id|dvbdev
op_assign
id|dvbdev_find_device
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dvbdev
op_logical_and
id|dvbdev-&gt;fops
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
suffix:semicolon
id|file-&gt;private_data
op_assign
id|dvbdev
suffix:semicolon
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|dvbdev-&gt;fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
(brace
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|dvb_device_fops
r_static
r_struct
id|file_operations
id|dvb_device_fops
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
id|dvb_device_open
comma
)brace
suffix:semicolon
DECL|function|dvb_generic_open
r_int
id|dvb_generic_open
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
id|dvb_device
op_star
id|dvbdev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev-&gt;users
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_ne
id|O_RDONLY
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dvbdev-&gt;writers
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|dvbdev-&gt;writers
op_decrement
suffix:semicolon
)brace
id|dvbdev-&gt;users
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_generic_release
r_int
id|dvb_generic_release
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
id|dvb_device
op_star
id|dvbdev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_ne
id|O_RDONLY
)paren
id|dvbdev-&gt;writers
op_increment
suffix:semicolon
id|dvbdev-&gt;users
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_generic_ioctl
r_int
id|dvb_generic_ioctl
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
id|dvb_device
op_star
id|dvbdev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev-&gt;kernel_ioctl
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|dvb_usercopy
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|dvbdev-&gt;kernel_ioctl
)paren
suffix:semicolon
)brace
DECL|function|dvbdev_get_free_id
r_static
r_int
id|dvbdev_get_free_id
(paren
r_struct
id|dvb_adapter
op_star
id|adap
comma
r_int
id|type
)paren
(brace
id|u32
id|id
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|id
OL
id|DVB_MAX_IDS
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|adap-&gt;device_list
)paren
(brace
r_struct
id|dvb_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|dvb_device
comma
id|list_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|type
op_logical_and
id|dev-&gt;id
op_eq
id|id
)paren
r_goto
id|skip
suffix:semicolon
)brace
r_return
id|id
suffix:semicolon
id|skip
suffix:colon
id|id
op_increment
suffix:semicolon
)brace
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
DECL|function|dvb_register_device
r_int
id|dvb_register_device
c_func
(paren
r_struct
id|dvb_adapter
op_star
id|adap
comma
r_struct
id|dvb_device
op_star
op_star
id|pdvbdev
comma
r_const
r_struct
id|dvb_device
op_star
r_template
comma
r_void
op_star
id|priv
comma
r_int
id|type
)paren
(brace
r_struct
id|dvb_device
op_star
id|dvbdev
suffix:semicolon
r_int
id|id
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|dvbdev_register_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_assign
id|dvbdev_get_free_id
(paren
id|adap
comma
id|type
)paren
)paren
OL
l_int|0
)paren
(brace
id|up
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
op_star
id|pdvbdev
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: could get find free device id...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
op_star
id|pdvbdev
op_assign
id|dvbdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dvbdev
)paren
(brace
id|up
c_func
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|up
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dvbdev
comma
r_template
comma
r_sizeof
(paren
r_struct
id|dvb_device
)paren
)paren
suffix:semicolon
id|dvbdev-&gt;type
op_assign
id|type
suffix:semicolon
id|dvbdev-&gt;id
op_assign
id|id
suffix:semicolon
id|dvbdev-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|dvbdev-&gt;priv
op_assign
id|priv
suffix:semicolon
id|list_add_tail
(paren
op_amp
id|dvbdev-&gt;list_head
comma
op_amp
id|adap-&gt;device_list
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|DVB_MAJOR
comma
id|nums2minor
c_func
(paren
id|adap-&gt;num
comma
id|type
comma
id|id
)paren
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;dvb/adapter%d/%s%d&quot;
comma
id|adap-&gt;num
comma
id|dnames
(braket
id|type
)braket
comma
id|id
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;DVB: register adapter%d/%s%d @ minor: %i (0x%02x)&bslash;n&quot;
comma
id|adap-&gt;num
comma
id|dnames
(braket
id|type
)braket
comma
id|id
comma
id|nums2minor
c_func
(paren
id|adap-&gt;num
comma
id|type
comma
id|id
)paren
comma
id|nums2minor
c_func
(paren
id|adap-&gt;num
comma
id|type
comma
id|id
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_unregister_device
r_void
id|dvb_unregister_device
c_func
(paren
r_struct
id|dvb_device
op_star
id|dvbdev
)paren
(brace
r_if
c_cond
(paren
id|dvbdev
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;dvb/adapter%d/%s%d&quot;
comma
id|dvbdev-&gt;adapter-&gt;num
comma
id|dnames
(braket
id|dvbdev-&gt;type
)braket
comma
id|dvbdev-&gt;id
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dvbdev-&gt;list_head
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dvbdev
)paren
suffix:semicolon
)brace
)brace
DECL|function|dvbdev_get_free_adapter_num
r_static
r_int
id|dvbdev_get_free_adapter_num
(paren
r_void
)paren
(brace
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|dvb_adapter_list
)paren
(brace
r_struct
id|dvb_adapter
op_star
id|adap
suffix:semicolon
id|adap
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|dvb_adapter
comma
id|list_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adap-&gt;num
op_eq
id|num
)paren
r_goto
id|skip
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
id|skip
suffix:colon
id|num
op_increment
suffix:semicolon
)brace
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
DECL|function|dvb_register_adapter
r_int
id|dvb_register_adapter
c_func
(paren
r_struct
id|dvb_adapter
op_star
op_star
id|padap
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|dvb_adapter
op_star
id|adap
suffix:semicolon
r_int
id|num
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|dvbdev_register_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|num
op_assign
id|dvbdev_get_free_adapter_num
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|up
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|padap
op_assign
id|adap
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_adapter
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
(paren
id|adap
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dvb_adapter
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|adap-&gt;device_list
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;DVB: registering new adapter (%s).&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;dvb/adapter%d&quot;
comma
id|num
)paren
suffix:semicolon
id|adap-&gt;num
op_assign
id|num
suffix:semicolon
id|adap-&gt;name
op_assign
id|name
suffix:semicolon
id|list_add_tail
(paren
op_amp
id|adap-&gt;list_head
comma
op_amp
id|dvb_adapter_list
)paren
suffix:semicolon
id|up
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
DECL|function|dvb_unregister_adapter
r_int
id|dvb_unregister_adapter
c_func
(paren
r_struct
id|dvb_adapter
op_star
id|adap
)paren
(brace
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|dvbdev_register_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;dvb/adapter%d&quot;
comma
id|adap-&gt;num
)paren
suffix:semicolon
id|list_del
(paren
op_amp
id|adap-&gt;list_head
)paren
suffix:semicolon
id|up
(paren
op_amp
id|dvbdev_register_lock
)paren
suffix:semicolon
id|kfree
(paren
id|adap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_dvbdev
r_static
r_int
id|__init
id|init_dvbdev
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;dvb&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|register_chrdev
c_func
(paren
id|DVB_MAJOR
comma
l_string|&quot;DVB&quot;
comma
op_amp
id|dvb_device_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|printk
c_func
(paren
l_string|&quot;video_dev: unable to get major %d&bslash;n&quot;
comma
id|DVB_MAJOR
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|exit_dvbdev
r_static
r_void
id|__exit
id|exit_dvbdev
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|DVB_MAJOR
comma
l_string|&quot;DVB&quot;
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;dvb&quot;
)paren
suffix:semicolon
)brace
DECL|variable|init_dvbdev
id|module_init
c_func
(paren
id|init_dvbdev
)paren
suffix:semicolon
DECL|variable|exit_dvbdev
id|module_exit
c_func
(paren
id|exit_dvbdev
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DVB Core Driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Marcus Metzler, Ralph Metzler, Holger Waechtler&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dvbdev_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dvbdev_debug
comma
l_string|&quot;enable verbose debug messages&quot;
)paren
suffix:semicolon
eof
