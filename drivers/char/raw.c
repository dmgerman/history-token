multiline_comment|/*&n; * linux/drivers/char/raw.c&n; *&n; * Front-end raw character devices.  These can be bound to any block&n; * devices to provide genuine Unix raw character device semantics.&n; *&n; * We reserve minor number 0 for a control interface.  ioctl()s on this&n; * device are used to bind the other minor numbers to block devices.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/raw.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|dprintk
mdefine_line|#define dprintk(x...) 
DECL|struct|raw_device_data_s
r_typedef
r_struct
id|raw_device_data_s
(brace
DECL|member|binding
r_struct
id|block_device
op_star
id|binding
suffix:semicolon
DECL|member|inuse
DECL|member|sector_size
DECL|member|sector_bits
r_int
id|inuse
comma
id|sector_size
comma
id|sector_bits
suffix:semicolon
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|typedef|raw_device_data_t
)brace
id|raw_device_data_t
suffix:semicolon
DECL|variable|raw_devices
r_static
id|raw_device_data_t
id|raw_devices
(braket
l_int|256
)braket
suffix:semicolon
r_static
id|ssize_t
id|rw_raw_dev
c_func
(paren
r_int
id|rw
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
id|ssize_t
id|raw_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
id|ssize_t
id|raw_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|raw_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|raw_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|raw_ctl_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|raw_fops
r_static
r_struct
id|file_operations
id|raw_fops
op_assign
(brace
id|read
suffix:colon
id|raw_read
comma
id|write
suffix:colon
id|raw_write
comma
id|open
suffix:colon
id|raw_open
comma
id|release
suffix:colon
id|raw_release
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
id|ioctl
suffix:colon
id|raw_ctl_ioctl
comma
id|open
suffix:colon
id|raw_open
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
r_int
id|i
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|init_MUTEX
c_func
(paren
op_amp
id|raw_devices
(braket
id|i
)braket
dot
id|mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|raw_init
id|__initcall
c_func
(paren
id|raw_init
)paren
suffix:semicolon
multiline_comment|/* &n; * Open/close code for raw IO.&n; */
DECL|function|raw_open
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
r_int
id|minor
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|kdev_t
id|rdev
suffix:semicolon
multiline_comment|/* it should eventually go away */
r_int
id|err
suffix:semicolon
r_int
id|sector_size
suffix:semicolon
r_int
id|sector_bits
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Is it the control device? &n;&t; */
r_if
c_cond
(paren
id|minor
op_eq
l_int|0
)paren
(brace
id|filp-&gt;f_op
op_assign
op_amp
id|raw_ctl_fops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_iobuf
)paren
(brace
id|err
op_assign
id|alloc_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|filp-&gt;f_iobuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * No, it is a normal raw device.  All we need to do on open is&n;&t; * to check that the device is bound, and force the underlying&n;&t; * block device to a sector-size blocksize. &n;&t; */
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
op_logical_neg
id|bdev
)paren
r_goto
id|out
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
suffix:semicolon
id|rdev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
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
id|err
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t change the blocksize if we already have users using&n;&t; * this device &n;&t; */
r_if
c_cond
(paren
id|raw_devices
(braket
id|minor
)braket
dot
id|inuse
op_increment
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* &n;&t; * Don&squot;t interfere with mounted devices: we cannot safely set&n;&t; * the blocksize on a device which is already mounted.  &n;&t; */
id|sector_size
op_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
id|is_mounted
c_func
(paren
id|rdev
)paren
)paren
(brace
r_if
c_cond
(paren
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|rdev
)paren
)braket
)paren
id|sector_size
op_assign
id|blksize_size
(braket
id|MAJOR
c_func
(paren
id|rdev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|rdev
)paren
)braket
suffix:semicolon
)brace
r_else
id|sector_size
op_assign
id|get_hardsect_size
c_func
(paren
id|rdev
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|rdev
comma
id|sector_size
)paren
suffix:semicolon
id|raw_devices
(braket
id|minor
)braket
dot
id|sector_size
op_assign
id|sector_size
suffix:semicolon
r_for
c_loop
(paren
id|sector_bits
op_assign
l_int|0
suffix:semicolon
op_logical_neg
(paren
id|sector_size
op_amp
l_int|1
)paren
suffix:semicolon
)paren
id|sector_size
op_rshift_assign
l_int|1
comma
id|sector_bits
op_increment
suffix:semicolon
id|raw_devices
(braket
id|minor
)braket
dot
id|sector_bits
op_assign
id|sector_bits
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|raw_release
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
r_int
id|minor
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
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
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
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
multiline_comment|/*&n; * Deal with ioctls against the raw-device control interface, to bind&n; * and unbind other raw devices.  &n; */
DECL|function|raw_ctl_ioctl
r_int
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
id|flip
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
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|minor
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
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
id|minor
op_assign
id|rq.raw_minor
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_le
l_int|0
op_logical_or
id|minor
OG
id|MINORMASK
)paren
(brace
id|err
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
id|command
op_eq
id|RAW_SETBIND
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This is like making block devices, so demand the&n;&t;&t;&t; * same capability&n;&t;&t;&t; */
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
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* &n;&t;&t;&t; * For now, we don&squot;t need to check that the underlying&n;&t;&t;&t; * block device is present or not: we can do that when&n;&t;&t;&t; * the raw device is opened.  Just check that the&n;&t;&t;&t; * major/minor numbers make sense. &n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|rq.block_major
op_eq
id|NODEV
op_logical_and
id|rq.block_minor
op_ne
id|NODEV
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
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raw_devices
(braket
id|minor
)braket
dot
id|inuse
)paren
(brace
id|up
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
)paren
id|bdput
c_func
(paren
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
)paren
suffix:semicolon
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|MKDEV
c_func
(paren
id|rq.block_major
comma
id|rq.block_minor
)paren
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|raw_devices
(braket
id|minor
)braket
dot
id|mutex
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
id|bdev
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|binding
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
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rq.block_minor
op_assign
id|MINOR
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
id|err
op_assign
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
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|raw_read
id|ssize_t
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
r_return
id|rw_raw_dev
c_func
(paren
id|READ
comma
id|filp
comma
id|buf
comma
id|size
comma
id|offp
)paren
suffix:semicolon
)brace
DECL|function|raw_write
id|ssize_t
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
r_return
id|rw_raw_dev
c_func
(paren
id|WRITE
comma
id|filp
comma
(paren
r_char
op_star
)paren
id|buf
comma
id|size
comma
id|offp
)paren
suffix:semicolon
)brace
DECL|macro|SECTOR_BITS
mdefine_line|#define SECTOR_BITS 9
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE (1U &lt;&lt; SECTOR_BITS)
DECL|macro|SECTOR_MASK
mdefine_line|#define SECTOR_MASK (SECTOR_SIZE - 1)
DECL|function|rw_raw_dev
id|ssize_t
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
id|kiobuf
op_star
id|iobuf
suffix:semicolon
r_int
id|new_iobuf
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|blocks
suffix:semicolon
r_int
id|transferred
suffix:semicolon
r_int
id|iosize
suffix:semicolon
r_int
id|minor
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
r_int
id|sector_size
comma
id|sector_bits
comma
id|sector_mask
suffix:semicolon
id|sector_t
id|blocknr
suffix:semicolon
multiline_comment|/*&n;&t; * First, a few checks on device size limits &n;&t; */
id|minor
op_assign
id|MINOR
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
id|new_iobuf
op_assign
l_int|0
suffix:semicolon
id|iobuf
op_assign
id|filp-&gt;f_iobuf
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|filp-&gt;f_iobuf_lock
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * A parallel read/write is using the preallocated iobuf&n;&t;&t; * so just run slow and allocate a new one.&n;&t;&t; */
id|err
op_assign
id|alloc_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|iobuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|new_iobuf
op_assign
l_int|1
suffix:semicolon
)brace
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|raw_devices
(braket
id|minor
)braket
dot
id|binding-&gt;bd_dev
)paren
suffix:semicolon
id|sector_size
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|sector_size
suffix:semicolon
id|sector_bits
op_assign
id|raw_devices
(braket
id|minor
)braket
dot
id|sector_bits
suffix:semicolon
id|sector_mask
op_assign
id|sector_size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
)paren
id|limit
op_assign
(paren
(paren
(paren
id|loff_t
)paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|dev
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
)paren
op_lshift
id|BLOCK_SIZE_BITS
)paren
op_rshift
id|sector_bits
suffix:semicolon
r_else
id|limit
op_assign
id|INT_MAX
suffix:semicolon
id|dprintk
(paren
l_string|&quot;rw_raw_dev: dev %d:%d (+%d)&bslash;n&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
comma
id|limit
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offp
op_amp
id|sector_mask
)paren
op_logical_or
(paren
id|size
op_amp
id|sector_mask
)paren
)paren
r_goto
id|out_free
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|err
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offp
op_rshift
id|sector_bits
)paren
op_ge
id|limit
)paren
r_goto
id|out_free
suffix:semicolon
id|transferred
op_assign
l_int|0
suffix:semicolon
id|blocknr
op_assign
op_star
id|offp
op_rshift
id|sector_bits
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|blocks
op_assign
id|size
op_rshift
id|sector_bits
suffix:semicolon
r_if
c_cond
(paren
id|blocks
OG
id|limit
op_minus
id|blocknr
)paren
id|blocks
op_assign
id|limit
op_minus
id|blocknr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocks
)paren
r_break
suffix:semicolon
id|iosize
op_assign
id|blocks
op_lshift
id|sector_bits
suffix:semicolon
id|err
op_assign
id|map_user_kiobuf
c_func
(paren
id|rw
comma
id|iobuf
comma
(paren
r_int
r_int
)paren
id|buf
comma
id|iosize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
id|err
op_assign
id|brw_kiovec
c_func
(paren
id|rw
comma
l_int|1
comma
op_amp
id|iobuf
comma
id|dev
comma
op_amp
id|blocknr
comma
id|sector_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
op_logical_and
id|err
OG
l_int|0
)paren
id|mark_dirty_kiobuf
c_func
(paren
id|iobuf
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
id|transferred
op_add_assign
id|err
suffix:semicolon
id|size
op_sub_assign
id|err
suffix:semicolon
id|buf
op_add_assign
id|err
suffix:semicolon
)brace
id|blocknr
op_add_assign
id|blocks
suffix:semicolon
id|unmap_kiobuf
c_func
(paren
id|iobuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|iosize
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|transferred
)paren
(brace
op_star
id|offp
op_add_assign
id|transferred
suffix:semicolon
id|err
op_assign
id|transferred
suffix:semicolon
)brace
id|out_free
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|new_iobuf
)paren
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|filp-&gt;f_iobuf_lock
)paren
suffix:semicolon
r_else
id|free_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|iobuf
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
eof
