multiline_comment|/*&n; * linux/drivers/char/raw.c&n; *&n; * Front-end raw character devices.  These can be bound to any block&n; * devices to provide genuine Unix raw character device semantics.&n; *&n; * We reserve minor number 0 for a control interface.  ioctl()s on this&n; * device are used to bind the other minor numbers to block devices.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/raw.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|struct|raw_device_data
r_struct
id|raw_device_data
(brace
DECL|member|binding
r_struct
id|block_device
op_star
id|binding
suffix:semicolon
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|raw_devices
r_static
r_struct
id|raw_device_data
id|raw_devices
(braket
l_int|256
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|raw_mutex
)paren
suffix:semicolon
DECL|variable|raw_ctl_fops
r_static
r_struct
id|file_operations
id|raw_ctl_fops
suffix:semicolon
multiline_comment|/*&n; * Open/close code for raw IO.&n; *&n; * Set the device&squot;s soft blocksize to the minimum possible.  This gives the&n; * finest possible alignment and has no adverse impact on performance.&n; */
DECL|function|raw_open
r_static
r_int
id|raw_open
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
id|filp
)paren
(brace
r_const
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
l_int|0
)paren
(brace
multiline_comment|/* It is the control device */
id|filp-&gt;f_op
op_assign
op_amp
id|raw_ctl_fops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * All we need to do on open is check that the device is bound.&n;&t; */
id|bdev
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
suffix:semicolon
id|err
op_assign
id|blkdev_get
c_func
(paren
id|bdev
comma
id|filp-&gt;f_mode
comma
l_int|0
comma
id|BDEV_RAW
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|err
op_assign
id|set_blocksize
c_func
(paren
id|bdev
comma
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
id|raw_devices
(braket
id|minor
)braket
dot
id|inuse
op_increment
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|raw_release
r_static
r_int
id|raw_release
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
id|filp
)paren
(brace
r_const
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|down
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
id|bdev
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
suffix:semicolon
id|raw_devices
(braket
id|minor
)braket
dot
id|inuse
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_RAW
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Forward ioctls to the underlying block device.&n; */
r_static
r_int
DECL|function|raw_ioctl
id|raw_ioctl
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
id|filp
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_const
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|minor
template_param
l_int|255
)paren
r_goto
id|out
suffix:semicolon
id|bdev
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bdev
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_inode
op_logical_and
id|bdev-&gt;bd_op
op_logical_and
id|bdev-&gt;bd_op-&gt;ioctl
)paren
id|err
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|bdev-&gt;bd_inode
comma
l_int|NULL
comma
id|command
comma
id|arg
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Deal with ioctls against the raw-device control interface, to bind&n; * and unbind other raw devices.&n; */
r_static
r_int
DECL|function|raw_ctl_ioctl
id|raw_ctl_ioctl
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
id|filp
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|raw_config_request
id|rq
suffix:semicolon
r_struct
id|raw_device_data
op_star
id|rawdev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|RAW_SETBIND
suffix:colon
r_case
id|RAW_GETBIND
suffix:colon
multiline_comment|/* First, find out which raw minor we want */
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rq
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|rq
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rq.raw_minor
template_param
id|MINORMASK
)paren
r_goto
id|out
suffix:semicolon
id|rawdev
op_assign
op_amp
id|raw_devices
(braket
id|rq.raw_minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|command
op_eq
id|RAW_SETBIND
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This is like making block devices, so demand the&n;&t;&t;&t; * same capability&n;&t;&t;&t; */
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * For now, we don&squot;t need to check that the underlying&n;&t;&t;&t; * block device is present or not: we can do that when&n;&t;&t;&t; * the raw device is opened.  Just check that the&n;&t;&t;&t; * major/minor numbers make sense.&n;&t;&t;&t; */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq.block_major
op_eq
l_int|0
op_logical_and
id|rq.block_minor
op_ne
l_int|0
)paren
op_logical_or
id|rq.block_major
OG
id|MAX_BLKDEV
op_logical_or
id|rq.block_minor
OG
id|MINORMASK
)paren
r_goto
id|out
suffix:semicolon
id|down
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|rawdev-&gt;inuse
)paren
(brace
id|up
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rawdev-&gt;binding
)paren
(brace
id|bdput
c_func
(paren
id|rawdev-&gt;binding
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rq.block_major
op_eq
l_int|0
op_logical_and
id|rq.block_minor
op_eq
l_int|0
)paren
(brace
multiline_comment|/* unbind */
id|rawdev-&gt;binding
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|kdev_t
id|kdev
suffix:semicolon
id|kdev
op_assign
id|mk_kdev
c_func
(paren
id|rq.block_major
comma
id|rq.block_minor
)paren
suffix:semicolon
id|rawdev-&gt;binding
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|kdev
)paren
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
id|down
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
id|bdev
op_assign
id|rawdev-&gt;binding
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
(brace
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
id|rq.block_major
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rq.block_minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|rq.block_major
op_assign
id|rq.block_minor
op_assign
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|raw_mutex
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
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
op_amp
id|rq
comma
r_sizeof
(paren
id|rq
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|rw_raw_dev
id|rw_raw_dev
c_func
(paren
r_int
id|rw
comma
r_struct
id|file
op_star
id|filp
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_const
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|bdev-&gt;bd_inode
suffix:semicolon
r_int
id|count
op_assign
id|iov_length
c_func
(paren
id|iov
comma
id|nr_segs
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ssize_t
)paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offp
op_ge
id|inode-&gt;i_size
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|count
op_plus
op_star
id|offp
OG
id|inode-&gt;i_size
)paren
(brace
id|count
op_assign
id|inode-&gt;i_size
op_minus
op_star
id|offp
suffix:semicolon
id|nr_segs
op_assign
id|iov_shorten
c_func
(paren
(paren
r_struct
id|iovec
op_star
)paren
id|iov
comma
id|nr_segs
comma
id|count
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|generic_file_direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|iov
comma
op_star
id|offp
comma
id|nr_segs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
op_star
id|offp
op_add_assign
id|ret
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|raw_read
id|raw_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|size
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_struct
id|iovec
id|local_iov
op_assign
(brace
dot
id|iov_base
op_assign
id|buf
comma
dot
id|iov_len
op_assign
id|size
)brace
suffix:semicolon
r_return
id|rw_raw_dev
c_func
(paren
id|READ
comma
id|filp
comma
op_amp
id|local_iov
comma
l_int|1
comma
id|offp
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|raw_write
id|raw_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|size
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_struct
id|iovec
id|local_iov
op_assign
(brace
dot
id|iov_base
op_assign
id|buf
comma
dot
id|iov_len
op_assign
id|size
)brace
suffix:semicolon
r_return
id|rw_raw_dev
c_func
(paren
id|WRITE
comma
id|filp
comma
op_amp
id|local_iov
comma
l_int|1
comma
id|offp
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|raw_readv
id|raw_readv
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_return
id|rw_raw_dev
c_func
(paren
id|READ
comma
id|filp
comma
id|iov
comma
id|nr_segs
comma
id|offp
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|raw_writev
id|raw_writev
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_return
id|rw_raw_dev
c_func
(paren
id|WRITE
comma
id|filp
comma
id|iov
comma
id|nr_segs
comma
id|offp
)paren
suffix:semicolon
)brace
DECL|variable|raw_fops
r_static
r_struct
id|file_operations
id|raw_fops
op_assign
(brace
dot
id|read
op_assign
id|raw_read
comma
dot
id|write
op_assign
id|raw_write
comma
dot
id|open
op_assign
id|raw_open
comma
dot
id|release
op_assign
id|raw_release
comma
dot
id|ioctl
op_assign
id|raw_ioctl
comma
dot
id|readv
op_assign
id|raw_readv
comma
dot
id|writev
op_assign
id|raw_writev
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|raw_ctl_fops
r_static
r_struct
id|file_operations
id|raw_ctl_fops
op_assign
(brace
dot
id|ioctl
op_assign
id|raw_ctl_ioctl
comma
dot
id|open
op_assign
id|raw_open
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|raw_init
r_static
r_int
id|__init
id|raw_init
c_func
(paren
r_void
)paren
(brace
id|register_chrdev
c_func
(paren
id|RAW_MAJOR
comma
l_string|&quot;raw&quot;
comma
op_amp
id|raw_fops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|raw_exit
r_static
r_void
id|__exit
id|raw_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|RAW_MAJOR
comma
l_string|&quot;raw&quot;
)paren
suffix:semicolon
)brace
DECL|variable|raw_init
id|module_init
c_func
(paren
id|raw_init
)paren
suffix:semicolon
DECL|variable|raw_exit
id|module_exit
c_func
(paren
id|raw_exit
)paren
suffix:semicolon
eof
