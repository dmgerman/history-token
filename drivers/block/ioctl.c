macro_line|#include &lt;linux/sched.h&gt;&t;&t;/* for capable() */
macro_line|#include &lt;linux/blk.h&gt;&t;&t;&t;/* for set_device_ro() */
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|blkpg_ioctl
r_static
r_int
id|blkpg_ioctl
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_struct
id|blkpg_ioctl_arg
op_star
id|arg
)paren
(brace
r_struct
id|block_device
op_star
id|bdevp
suffix:semicolon
r_int
id|holder
suffix:semicolon
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
r_struct
id|blkpg_ioctl_arg
id|a
suffix:semicolon
r_struct
id|blkpg_partition
id|p
suffix:semicolon
r_int
r_int
id|start
comma
id|length
suffix:semicolon
r_int
id|part
suffix:semicolon
r_int
id|i
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
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|blkpg_ioctl_arg
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
id|copy_from_user
c_func
(paren
op_amp
id|p
comma
id|a.data
comma
r_sizeof
(paren
r_struct
id|blkpg_partition
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|disk
op_assign
id|get_gendisk
c_func
(paren
id|bdev-&gt;bd_dev
comma
op_amp
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|bdev
op_ne
id|bdev-&gt;bd_contains
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|part
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|part
op_assign
id|p.pno
suffix:semicolon
r_if
c_cond
(paren
id|part
op_le
l_int|0
op_logical_or
id|part
op_ge
id|disk-&gt;minors
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|a.op
)paren
(brace
r_case
id|BLKPG_ADD_PARTITION
suffix:colon
id|start
op_assign
id|p.start
op_rshift
l_int|9
suffix:semicolon
id|length
op_assign
id|p.length
op_rshift
l_int|9
suffix:semicolon
multiline_comment|/* check for fit in a hd_struct */
r_if
c_cond
(paren
r_sizeof
(paren
id|sector_t
)paren
op_eq
r_sizeof
(paren
r_int
)paren
op_logical_and
r_sizeof
(paren
r_int
r_int
)paren
OG
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_int
id|pstart
op_assign
id|start
comma
id|plength
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|pstart
op_ne
id|start
op_logical_or
id|plength
op_ne
id|length
op_logical_or
id|pstart
OL
l_int|0
op_logical_or
id|plength
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* partition number in use? */
r_if
c_cond
(paren
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
dot
id|nr_sects
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* overlap? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|disk-&gt;minors
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|hd_struct
op_star
id|s
op_assign
op_amp
id|disk-&gt;part
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|start
op_plus
id|length
op_le
id|s-&gt;start_sect
op_logical_or
id|start
op_ge
id|s-&gt;start_sect
op_plus
id|s-&gt;nr_sects
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* all seems OK */
id|add_partition
c_func
(paren
id|disk
comma
id|part
comma
id|start
comma
id|length
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKPG_DEL_PARTITION
suffix:colon
r_if
c_cond
(paren
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
dot
id|nr_sects
op_eq
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* partition in use? Incomplete check for now. */
id|bdevp
op_assign
id|bdget
c_func
(paren
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
op_plus
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdevp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|bd_claim
c_func
(paren
id|bdevp
comma
op_amp
id|holder
)paren
OL
l_int|0
)paren
(brace
id|bdput
c_func
(paren
id|bdevp
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* all seems OK */
id|fsync_bdev
c_func
(paren
id|bdevp
)paren
suffix:semicolon
id|invalidate_bdev
c_func
(paren
id|bdevp
comma
l_int|0
)paren
suffix:semicolon
id|delete_partition
c_func
(paren
id|disk
comma
id|part
)paren
suffix:semicolon
id|bd_release
c_func
(paren
id|bdevp
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdevp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|blkdev_reread_part
r_static
r_int
id|blkdev_reread_part
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_int
id|part
suffix:semicolon
r_struct
id|gendisk
op_star
id|disk
op_assign
id|get_gendisk
c_func
(paren
id|bdev-&gt;bd_dev
comma
op_amp
id|part
)paren
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
op_logical_or
id|disk-&gt;minors
op_eq
l_int|1
op_logical_or
id|bdev
op_ne
id|bdev-&gt;bd_contains
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|part
)paren
id|BUG
c_func
(paren
)paren
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
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|res
op_assign
id|rescan_partitions
c_func
(paren
id|disk
comma
id|bdev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|put_ushort
r_static
r_int
id|put_ushort
c_func
(paren
r_int
r_int
id|arg
comma
r_int
r_int
id|val
)paren
(brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|put_int
r_static
r_int
id|put_int
c_func
(paren
r_int
r_int
id|arg
comma
r_int
id|val
)paren
(brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|put_long
r_static
r_int
id|put_long
c_func
(paren
r_int
r_int
id|arg
comma
r_int
id|val
)paren
(brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|put_ulong
r_static
r_int
id|put_ulong
c_func
(paren
r_int
r_int
id|arg
comma
r_int
r_int
id|val
)paren
(brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|put_u64
r_static
r_int
id|put_u64
c_func
(paren
r_int
r_int
id|arg
comma
id|u64
id|val
)paren
(brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
id|u64
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|blkdev_ioctl
r_int
id|blkdev_ioctl
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
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
r_struct
id|backing_dev_info
op_star
id|bdi
suffix:semicolon
r_int
id|holder
suffix:semicolon
r_int
id|ret
comma
id|n
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKELVGET
suffix:colon
r_case
id|BLKELVSET
suffix:colon
multiline_comment|/* deprecated, use the /proc/iosched interface instead */
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_case
id|BLKRAGET
suffix:colon
r_case
id|BLKFRAGET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|bdi
op_assign
id|blk_get_backing_dev_info
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdi
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_return
id|put_long
c_func
(paren
id|arg
comma
(paren
id|bdi-&gt;ra_pages
op_star
id|PAGE_CACHE_SIZE
)paren
op_div
l_int|512
)paren
suffix:semicolon
r_case
id|BLKROGET
suffix:colon
r_return
id|put_int
c_func
(paren
id|arg
comma
id|bdev_read_only
c_func
(paren
id|bdev
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_case
id|BLKBSZGET
suffix:colon
multiline_comment|/* get the logical block size (cf. BLKSSZGET) */
r_return
id|put_int
c_func
(paren
id|arg
comma
id|block_size
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
r_case
id|BLKSSZGET
suffix:colon
multiline_comment|/* get block device hardware sector size */
r_return
id|put_int
c_func
(paren
id|arg
comma
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
r_case
id|BLKSECTGET
suffix:colon
r_return
id|put_ushort
c_func
(paren
id|arg
comma
id|bdev-&gt;bd_queue-&gt;max_sectors
)paren
suffix:semicolon
r_case
id|BLKRASET
suffix:colon
r_case
id|BLKFRASET
suffix:colon
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
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|bdi
op_assign
id|blk_get_backing_dev_info
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdi
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
id|bdi-&gt;ra_pages
op_assign
(paren
id|arg
op_star
l_int|512
)paren
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKBSZSET
suffix:colon
multiline_comment|/* set the logical block size */
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
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|n
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|PAGE_SIZE
op_logical_or
id|n
OL
l_int|512
op_logical_or
(paren
id|n
op_amp
(paren
id|n
op_minus
l_int|1
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bd_claim
c_func
(paren
id|bdev
comma
op_amp
id|holder
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|set_blocksize
c_func
(paren
id|bdev
comma
id|n
)paren
suffix:semicolon
id|bd_release
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKPG
suffix:colon
r_return
id|blkpg_ioctl
c_func
(paren
id|bdev
comma
(paren
r_struct
id|blkpg_ioctl_arg
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKRRPART
suffix:colon
r_return
id|blkdev_reread_part
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_case
id|BLKGETSIZE
suffix:colon
r_if
c_cond
(paren
(paren
id|bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
)paren
OG
op_complement
l_int|0UL
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
r_return
id|put_ulong
c_func
(paren
id|arg
comma
id|bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
)paren
suffix:semicolon
r_case
id|BLKGETSIZE64
suffix:colon
r_return
id|put_u64
c_func
(paren
id|arg
comma
id|bdev-&gt;bd_inode-&gt;i_size
)paren
suffix:semicolon
r_case
id|BLKFLSBUF
suffix:colon
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
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;ioctl
)paren
(brace
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|EINVAL
)paren
r_return
id|ret
suffix:semicolon
)brace
id|fsync_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|invalidate_bdev
c_func
(paren
id|bdev
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKROSET
suffix:colon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;ioctl
)paren
(brace
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|EINVAL
)paren
r_return
id|ret
suffix:semicolon
)brace
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
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|n
comma
(paren
r_int
op_star
)paren
(paren
id|arg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|set_device_ro
c_func
(paren
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
comma
id|n
)paren
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
id|bdev-&gt;bd_op-&gt;ioctl
)paren
(brace
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|EINVAL
)paren
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
eof
