multiline_comment|/*&n; * Block driver for media (i.e., flash cards)&n; *&n; * Copyright 2002 Hewlett-Packard Company&n; *&n; * Use consistent with the GNU GPL is permitted,&n; * provided that this copyright notice is&n; * preserved in its entirety in all copies and derived works.&n; *&n; * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,&n; * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS&n; * FITNESS FOR ANY PARTICULAR PURPOSE.&n; *&n; * Many thanks to Alessandro Rubini and Jonathan Corbet!&n; *&n; * Author:  Andrew Christian&n; *          28 May 2002&n; */
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/mmc/card.h&gt;
macro_line|#include &lt;linux/mmc/protocol.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;mmc_queue.h&quot;
multiline_comment|/*&n; * max 8 partitions per card&n; */
DECL|macro|MMC_SHIFT
mdefine_line|#define MMC_SHIFT&t;3
DECL|variable|mmc_major
r_static
r_int
id|mmc_major
suffix:semicolon
multiline_comment|/*&n; * There is one mmc_blk_data per slot.&n; */
DECL|struct|mmc_blk_data
r_struct
id|mmc_blk_data
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|disk
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
DECL|member|queue
r_struct
id|mmc_queue
id|queue
suffix:semicolon
DECL|member|usage
r_int
r_int
id|usage
suffix:semicolon
DECL|member|block_bits
r_int
r_int
id|block_bits
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|open_lock
)paren
suffix:semicolon
DECL|function|mmc_blk_get
r_static
r_struct
id|mmc_blk_data
op_star
id|mmc_blk_get
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
suffix:semicolon
id|down
c_func
(paren
op_amp
id|open_lock
)paren
suffix:semicolon
id|md
op_assign
id|disk-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|md
op_logical_and
id|md-&gt;usage
op_eq
l_int|0
)paren
id|md
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
id|md-&gt;usage
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|open_lock
)paren
suffix:semicolon
r_return
id|md
suffix:semicolon
)brace
DECL|function|mmc_blk_put
r_static
r_void
id|mmc_blk_put
c_func
(paren
r_struct
id|mmc_blk_data
op_star
id|md
)paren
(brace
id|down
c_func
(paren
op_amp
id|open_lock
)paren
suffix:semicolon
id|md-&gt;usage
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|md-&gt;usage
op_eq
l_int|0
)paren
(brace
id|put_disk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
id|mmc_cleanup_queue
c_func
(paren
op_amp
id|md-&gt;queue
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|open_lock
)paren
suffix:semicolon
)brace
DECL|function|mmc_blk_open
r_static
r_int
id|mmc_blk_open
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
r_struct
id|mmc_blk_data
op_star
id|md
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
id|md
op_assign
id|mmc_blk_get
c_func
(paren
id|inode-&gt;i_bdev-&gt;bd_disk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
(brace
r_if
c_cond
(paren
id|md-&gt;usage
op_eq
l_int|2
)paren
id|check_disk_change
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mmc_blk_release
r_static
r_int
id|mmc_blk_release
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
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|mmc_blk_put
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|mmc_blk_ioctl
id|mmc_blk_ioctl
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
r_if
c_cond
(paren
id|cmd
op_eq
id|HDIO_GETGEO
)paren
(brace
r_struct
id|hd_geometry
id|geo
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|geo
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hd_geometry
)paren
)paren
suffix:semicolon
id|geo.cylinders
op_assign
id|get_capacity
c_func
(paren
id|bdev-&gt;bd_disk
)paren
op_div
(paren
l_int|4
op_star
l_int|16
)paren
suffix:semicolon
id|geo.heads
op_assign
l_int|4
suffix:semicolon
id|geo.sectors
op_assign
l_int|16
suffix:semicolon
id|geo.start
op_assign
id|get_start_sect
c_func
(paren
id|bdev
)paren
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
id|geo
comma
r_sizeof
(paren
id|geo
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|variable|mmc_bdops
r_static
r_struct
id|block_device_operations
id|mmc_bdops
op_assign
(brace
dot
id|open
op_assign
id|mmc_blk_open
comma
dot
id|release
op_assign
id|mmc_blk_release
comma
dot
id|ioctl
op_assign
id|mmc_blk_ioctl
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|struct|mmc_blk_request
r_struct
id|mmc_blk_request
(brace
DECL|member|mrq
r_struct
id|mmc_request
id|mrq
suffix:semicolon
DECL|member|cmd
r_struct
id|mmc_command
id|cmd
suffix:semicolon
DECL|member|stop
r_struct
id|mmc_command
id|stop
suffix:semicolon
DECL|member|data
r_struct
id|mmc_data
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mmc_blk_prep_rq
r_static
r_int
id|mmc_blk_prep_rq
c_func
(paren
r_struct
id|mmc_queue
op_star
id|mq
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|mq-&gt;data
suffix:semicolon
r_int
id|stat
op_assign
id|BLKPREP_OK
suffix:semicolon
multiline_comment|/*&n;&t; * If we have no device, we haven&squot;t finished initialising.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|md
op_logical_or
op_logical_neg
id|mq-&gt;card
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: killing request - no device/host&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
)paren
suffix:semicolon
id|stat
op_assign
id|BLKPREP_KILL
suffix:semicolon
)brace
r_return
id|stat
suffix:semicolon
)brace
DECL|function|mmc_blk_issue_rq
r_static
r_int
id|mmc_blk_issue_rq
c_func
(paren
r_struct
id|mmc_queue
op_star
id|mq
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|mq-&gt;data
suffix:semicolon
r_struct
id|mmc_card
op_star
id|card
op_assign
id|md-&gt;queue.card
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|mmc_card_claim_host
c_func
(paren
id|card
)paren
)paren
r_goto
id|cmd_err
suffix:semicolon
r_do
(brace
r_struct
id|mmc_blk_request
id|brq
suffix:semicolon
r_struct
id|mmc_command
id|cmd
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|brq
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mmc_blk_request
)paren
)paren
suffix:semicolon
id|brq.mrq.cmd
op_assign
op_amp
id|brq.cmd
suffix:semicolon
id|brq.mrq.data
op_assign
op_amp
id|brq.data
suffix:semicolon
id|brq.cmd.arg
op_assign
id|req-&gt;sector
op_lshift
l_int|9
suffix:semicolon
id|brq.cmd.flags
op_assign
id|MMC_RSP_R1
suffix:semicolon
id|brq.data.req
op_assign
id|req
suffix:semicolon
id|brq.data.timeout_ns
op_assign
id|card-&gt;csd.tacc_ns
op_star
l_int|10
suffix:semicolon
id|brq.data.timeout_clks
op_assign
id|card-&gt;csd.tacc_clks
op_star
l_int|10
suffix:semicolon
id|brq.data.blksz_bits
op_assign
id|md-&gt;block_bits
suffix:semicolon
id|brq.data.blocks
op_assign
id|req-&gt;nr_sectors
op_rshift
(paren
id|md-&gt;block_bits
op_minus
l_int|9
)paren
suffix:semicolon
id|brq.stop.opcode
op_assign
id|MMC_STOP_TRANSMISSION
suffix:semicolon
id|brq.stop.arg
op_assign
l_int|0
suffix:semicolon
id|brq.stop.flags
op_assign
id|MMC_RSP_R1B
suffix:semicolon
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|READ
)paren
(brace
id|brq.cmd.opcode
op_assign
id|brq.data.blocks
OG
l_int|1
ques
c_cond
id|MMC_READ_MULTIPLE_BLOCK
suffix:colon
id|MMC_READ_SINGLE_BLOCK
suffix:semicolon
id|brq.data.flags
op_or_assign
id|MMC_DATA_READ
suffix:semicolon
)brace
r_else
(brace
id|brq.cmd.opcode
op_assign
id|MMC_WRITE_BLOCK
suffix:semicolon
id|brq.cmd.flags
op_assign
id|MMC_RSP_R1B
suffix:semicolon
id|brq.data.flags
op_or_assign
id|MMC_DATA_WRITE
suffix:semicolon
id|brq.data.blocks
op_assign
l_int|1
suffix:semicolon
)brace
id|brq.mrq.stop
op_assign
id|brq.data.blocks
OG
l_int|1
ques
c_cond
op_amp
id|brq.stop
suffix:colon
l_int|NULL
suffix:semicolon
id|mmc_wait_for_req
c_func
(paren
id|card-&gt;host
comma
op_amp
id|brq.mrq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brq.cmd.error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: error %d sending read/write command&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
comma
id|brq.cmd.error
)paren
suffix:semicolon
r_goto
id|cmd_err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|brq.data.error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: error %d transferring data&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
comma
id|brq.data.error
)paren
suffix:semicolon
r_goto
id|cmd_err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|brq.stop.error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: error %d sending stop command&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
comma
id|brq.stop.error
)paren
suffix:semicolon
r_goto
id|cmd_err
suffix:semicolon
)brace
r_do
(brace
r_int
id|err
suffix:semicolon
id|cmd.opcode
op_assign
id|MMC_SEND_STATUS
suffix:semicolon
id|cmd.arg
op_assign
id|card-&gt;rca
op_lshift
l_int|16
suffix:semicolon
id|cmd.flags
op_assign
id|MMC_RSP_R1
suffix:semicolon
id|err
op_assign
id|mmc_wait_for_cmd
c_func
(paren
id|card-&gt;host
comma
op_amp
id|cmd
comma
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: error %d requesting status&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
comma
id|err
)paren
suffix:semicolon
r_goto
id|cmd_err
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|cmd.resp
(braket
l_int|0
)braket
op_amp
id|R1_READY_FOR_DATA
)paren
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|cmd.resp
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0x00000900
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: status = %08x&bslash;n&quot;
comma
id|req-&gt;rq_disk-&gt;disk_name
comma
id|cmd.resp
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmc_decode_status
c_func
(paren
id|cmd.resp
)paren
)paren
r_goto
id|cmd_err
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * A block was successfully transferred.&n;&t;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|ret
op_assign
id|end_that_request_chunk
c_func
(paren
id|req
comma
l_int|1
comma
id|brq.data.bytes_xfered
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The whole request completed successfully.&n;&t;&t;&t; */
id|add_disk_randomness
c_func
(paren
id|req-&gt;rq_disk
)paren
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ret
)paren
suffix:semicolon
id|mmc_card_release_host
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|cmd_err
suffix:colon
id|mmc_card_release_host
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is a little draconian, but until we get proper&n;&t; * error handling sorted out here, its the best we can&n;&t; * do - especially as some hosts have no idea how much&n;&t; * data was transferred before the error occurred.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|end_that_request_chunk
c_func
(paren
id|req
comma
l_int|0
comma
id|req-&gt;current_nr_sectors
op_lshift
l_int|9
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ret
)paren
suffix:semicolon
id|add_disk_randomness
c_func
(paren
id|req-&gt;rq_disk
)paren
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MMC_NUM_MINORS
mdefine_line|#define MMC_NUM_MINORS&t;(256 &gt;&gt; MMC_SHIFT)
DECL|variable|dev_use
r_static
r_int
r_int
id|dev_use
(braket
id|MMC_NUM_MINORS
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|function|mmc_blk_alloc
r_static
r_struct
id|mmc_blk_data
op_star
id|mmc_blk_alloc
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
suffix:semicolon
r_int
id|devidx
comma
id|ret
suffix:semicolon
id|devidx
op_assign
id|find_first_zero_bit
c_func
(paren
id|dev_use
comma
id|MMC_NUM_MINORS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devidx
op_ge
id|MMC_NUM_MINORS
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
id|__set_bit
c_func
(paren
id|devidx
comma
id|dev_use
)paren
suffix:semicolon
id|md
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mmc_blk_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
(brace
id|memset
c_func
(paren
id|md
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mmc_blk_data
)paren
)paren
suffix:semicolon
id|md-&gt;disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
op_lshift
id|MMC_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md-&gt;disk
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
id|md
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|md-&gt;usage
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|mmc_init_queue
c_func
(paren
op_amp
id|md-&gt;queue
comma
id|card
comma
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|put_disk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
id|md
op_assign
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|md-&gt;queue.prep_fn
op_assign
id|mmc_blk_prep_rq
suffix:semicolon
id|md-&gt;queue.issue_fn
op_assign
id|mmc_blk_issue_rq
suffix:semicolon
id|md-&gt;queue.data
op_assign
id|md
suffix:semicolon
id|md-&gt;disk-&gt;major
op_assign
id|mmc_major
suffix:semicolon
id|md-&gt;disk-&gt;first_minor
op_assign
id|devidx
op_lshift
id|MMC_SHIFT
suffix:semicolon
id|md-&gt;disk-&gt;fops
op_assign
op_amp
id|mmc_bdops
suffix:semicolon
id|md-&gt;disk-&gt;private_data
op_assign
id|md
suffix:semicolon
id|md-&gt;disk-&gt;queue
op_assign
id|md-&gt;queue.queue
suffix:semicolon
id|md-&gt;disk-&gt;driverfs_dev
op_assign
op_amp
id|card-&gt;dev
suffix:semicolon
id|sprintf
c_func
(paren
id|md-&gt;disk-&gt;disk_name
comma
l_string|&quot;mmcblk%d&quot;
comma
id|devidx
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|md-&gt;disk-&gt;devfs_name
comma
l_string|&quot;mmc/blk%d&quot;
comma
id|devidx
)paren
suffix:semicolon
id|md-&gt;block_bits
op_assign
id|card-&gt;csd.read_blkbits
suffix:semicolon
id|blk_queue_hardsect_size
c_func
(paren
id|md-&gt;queue.queue
comma
l_int|1
op_lshift
id|md-&gt;block_bits
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|md-&gt;disk
comma
id|card-&gt;csd.capacity
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|md
suffix:semicolon
)brace
r_static
r_int
DECL|function|mmc_blk_set_blksize
id|mmc_blk_set_blksize
c_func
(paren
r_struct
id|mmc_blk_data
op_star
id|md
comma
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_struct
id|mmc_command
id|cmd
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mmc_card_claim_host
c_func
(paren
id|card
)paren
suffix:semicolon
id|cmd.opcode
op_assign
id|MMC_SET_BLOCKLEN
suffix:semicolon
id|cmd.arg
op_assign
l_int|1
op_lshift
id|card-&gt;csd.read_blkbits
suffix:semicolon
id|cmd.flags
op_assign
id|MMC_RSP_R1
suffix:semicolon
id|err
op_assign
id|mmc_wait_for_cmd
c_func
(paren
id|card-&gt;host
comma
op_amp
id|cmd
comma
l_int|5
)paren
suffix:semicolon
id|mmc_card_release_host
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to set block size to %d: %d&bslash;n&quot;
comma
id|md-&gt;disk-&gt;disk_name
comma
id|cmd.arg
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmc_blk_probe
r_static
r_int
id|mmc_blk_probe
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;csd.cmdclass
op_amp
op_complement
l_int|0x1ff
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;csd.read_blkbits
OL
l_int|9
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: read blocksize too small (%u)&bslash;n&quot;
comma
id|mmc_card_id
c_func
(paren
id|card
)paren
comma
l_int|1
op_lshift
id|card-&gt;csd.read_blkbits
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|md
op_assign
id|mmc_blk_alloc
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|md
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|md
)paren
suffix:semicolon
id|err
op_assign
id|mmc_blk_set_blksize
c_func
(paren
id|md
comma
id|card
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %s %s %dKiB&bslash;n&quot;
comma
id|md-&gt;disk-&gt;disk_name
comma
id|mmc_card_id
c_func
(paren
id|card
)paren
comma
id|mmc_card_name
c_func
(paren
id|card
)paren
comma
(paren
id|card-&gt;csd.capacity
op_lshift
id|card-&gt;csd.read_blkbits
)paren
op_div
l_int|1024
)paren
suffix:semicolon
id|mmc_set_drvdata
c_func
(paren
id|card
comma
id|md
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|mmc_blk_put
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|mmc_blk_remove
r_static
r_void
id|mmc_blk_remove
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|mmc_get_drvdata
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
(brace
r_int
id|devidx
suffix:semicolon
id|del_gendisk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * I think this is needed.&n;&t;&t; */
id|md-&gt;disk-&gt;queue
op_assign
l_int|NULL
suffix:semicolon
id|devidx
op_assign
id|md-&gt;disk-&gt;first_minor
op_rshift
id|MMC_SHIFT
suffix:semicolon
id|__clear_bit
c_func
(paren
id|devidx
comma
id|dev_use
)paren
suffix:semicolon
id|mmc_blk_put
c_func
(paren
id|md
)paren
suffix:semicolon
)brace
id|mmc_set_drvdata
c_func
(paren
id|card
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|mmc_blk_suspend
r_static
r_int
id|mmc_blk_suspend
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
comma
id|u32
id|state
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|mmc_get_drvdata
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
(brace
id|blk_stop_queue
c_func
(paren
id|md-&gt;queue.queue
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmc_blk_resume
r_static
r_int
id|mmc_blk_resume
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_struct
id|mmc_blk_data
op_star
id|md
op_assign
id|mmc_get_drvdata
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|md
)paren
(brace
id|mmc_blk_set_blksize
c_func
(paren
id|md
comma
id|card
)paren
suffix:semicolon
id|blk_start_queue
c_func
(paren
id|md-&gt;queue.queue
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|mmc_blk_suspend
mdefine_line|#define&t;mmc_blk_suspend&t;NULL
DECL|macro|mmc_blk_resume
mdefine_line|#define mmc_blk_resume&t;NULL
macro_line|#endif
DECL|variable|mmc_driver
r_static
r_struct
id|mmc_driver
id|mmc_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mmcblk&quot;
comma
)brace
comma
dot
id|probe
op_assign
id|mmc_blk_probe
comma
dot
id|remove
op_assign
id|mmc_blk_remove
comma
dot
id|suspend
op_assign
id|mmc_blk_suspend
comma
dot
id|resume
op_assign
id|mmc_blk_resume
comma
)brace
suffix:semicolon
DECL|function|mmc_blk_init
r_static
r_int
id|__init
id|mmc_blk_init
c_func
(paren
r_void
)paren
(brace
r_int
id|res
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|res
op_assign
id|register_blkdev
c_func
(paren
id|mmc_major
comma
l_string|&quot;mmc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unable to get major %d for MMC media: %d&bslash;n&quot;
comma
id|mmc_major
comma
id|res
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mmc_major
op_eq
l_int|0
)paren
id|mmc_major
op_assign
id|res
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;mmc&quot;
)paren
suffix:semicolon
r_return
id|mmc_register_driver
c_func
(paren
op_amp
id|mmc_driver
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|res
suffix:semicolon
)brace
DECL|function|mmc_blk_exit
r_static
r_void
id|__exit
id|mmc_blk_exit
c_func
(paren
r_void
)paren
(brace
id|mmc_unregister_driver
c_func
(paren
op_amp
id|mmc_driver
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;mmc&quot;
)paren
suffix:semicolon
id|unregister_blkdev
c_func
(paren
id|mmc_major
comma
l_string|&quot;mmc&quot;
)paren
suffix:semicolon
)brace
DECL|variable|mmc_blk_init
id|module_init
c_func
(paren
id|mmc_blk_init
)paren
suffix:semicolon
DECL|variable|mmc_blk_exit
id|module_exit
c_func
(paren
id|mmc_blk_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Multimedia Card (MMC) block device driver&quot;
)paren
suffix:semicolon
eof
