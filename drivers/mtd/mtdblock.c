multiline_comment|/* &n; * Direct MTD block device access&n; *&n; * $Id: mtdblock.c,v 1.47 2001/10/02 15:05:11 dwmw2 Exp $&n; *&n; * 02-nov-2000&t;Nicolas Pitre&t;&t;Added read-modify-write with cache&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MTD_BLOCK_MAJOR
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;mtdblock&quot;
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (device)
DECL|macro|LOCAL_END_REQUEST
mdefine_line|#define LOCAL_END_REQUEST
macro_line|#include &lt;linux/blk.h&gt;
multiline_comment|/* for old kernels... */
macro_line|#ifndef QUEUE_EMPTY
DECL|macro|QUEUE_EMPTY
mdefine_line|#define QUEUE_EMPTY  (!CURRENT)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
DECL|macro|QUEUE_PLUGGED
mdefine_line|#define QUEUE_PLUGGED (blk_dev[MAJOR_NR].plug_tq.sync)
macro_line|#else
DECL|macro|QUEUE_PLUGGED
mdefine_line|#define QUEUE_PLUGGED (blk_queue_plugged(QUEUE))
macro_line|#endif
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
r_static
r_void
id|mtd_notify_add
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
r_static
r_void
id|mtd_notify_remove
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
suffix:semicolon
DECL|variable|notifier
r_static
r_struct
id|mtd_notifier
id|notifier
op_assign
(brace
id|mtd_notify_add
comma
id|mtd_notify_remove
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|devfs_dir_handle
r_static
id|devfs_handle_t
id|devfs_dir_handle
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|devfs_rw_handle
r_static
id|devfs_handle_t
id|devfs_rw_handle
(braket
id|MAX_MTD_DEVICES
)braket
suffix:semicolon
macro_line|#endif
DECL|struct|mtdblk_dev
r_static
r_struct
id|mtdblk_dev
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
multiline_comment|/* Locked */
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|cache_sem
r_struct
id|semaphore
id|cache_sem
suffix:semicolon
DECL|member|cache_data
r_int
r_char
op_star
id|cache_data
suffix:semicolon
DECL|member|cache_offset
r_int
r_int
id|cache_offset
suffix:semicolon
DECL|member|cache_size
r_int
r_int
id|cache_size
suffix:semicolon
DECL|enumerator|STATE_EMPTY
DECL|enumerator|STATE_CLEAN
DECL|enumerator|STATE_DIRTY
DECL|member|cache_state
r_enum
(brace
id|STATE_EMPTY
comma
id|STATE_CLEAN
comma
id|STATE_DIRTY
)brace
id|cache_state
suffix:semicolon
DECL|variable|mtdblks
)brace
op_star
id|mtdblks
(braket
id|MAX_MTD_DEVICES
)braket
suffix:semicolon
DECL|variable|mtdblks_lock
r_static
id|spinlock_t
id|mtdblks_lock
suffix:semicolon
DECL|variable|mtd_sizes
r_static
r_int
id|mtd_sizes
(braket
id|MAX_MTD_DEVICES
)braket
suffix:semicolon
DECL|variable|mtd_blksizes
r_static
r_int
id|mtd_blksizes
(braket
id|MAX_MTD_DEVICES
)braket
suffix:semicolon
multiline_comment|/*&n; * Cache stuff...&n; * &n; * Since typical flash erasable sectors are much larger than what Linux&squot;s&n; * buffer cache can handle, we must implement read-modify-write on flash&n; * sectors for each block write requests.  To avoid over-erasing flash sectors&n; * and to speed things up, we locally cache a whole flash sector while it is&n; * being written to until a different sector is required.&n; */
DECL|function|erase_callback
r_static
r_void
id|erase_callback
c_func
(paren
r_struct
id|erase_info
op_star
id|done
)paren
(brace
id|wait_queue_head_t
op_star
id|wait_q
op_assign
(paren
id|wait_queue_head_t
op_star
)paren
id|done-&gt;priv
suffix:semicolon
id|wake_up
c_func
(paren
id|wait_q
)paren
suffix:semicolon
)brace
DECL|function|erase_write
r_static
r_int
id|erase_write
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
r_int
id|pos
comma
r_int
id|len
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_struct
id|erase_info
id|erase
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|wait_queue_head_t
id|wait_q
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * First, let&squot;s erase the flash block.&n;&t; */
id|init_waitqueue_head
c_func
(paren
op_amp
id|wait_q
)paren
suffix:semicolon
id|erase.mtd
op_assign
id|mtd
suffix:semicolon
id|erase.callback
op_assign
id|erase_callback
suffix:semicolon
id|erase.addr
op_assign
id|pos
suffix:semicolon
id|erase.len
op_assign
id|len
suffix:semicolon
id|erase.priv
op_assign
(paren
id|u_long
)paren
op_amp
id|wait_q
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
id|ret
op_assign
id|MTD_ERASE
c_func
(paren
id|mtd
comma
op_amp
id|erase
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;mtdblock: erase of region [0x%lx, 0x%x] &quot;
l_string|&quot;on &bslash;&quot;%s&bslash;&quot; failed&bslash;n&quot;
comma
id|pos
comma
id|len
comma
id|mtd-&gt;name
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Wait for erase to finish. */
id|remove_wait_queue
c_func
(paren
op_amp
id|wait_q
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Next, writhe data to flash.&n;&t; */
id|ret
op_assign
id|MTD_WRITE
(paren
id|mtd
comma
id|pos
comma
id|len
comma
op_amp
id|retlen
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|retlen
op_ne
id|len
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_cached_data
r_static
r_int
id|write_cached_data
(paren
r_struct
id|mtdblk_dev
op_star
id|mtdblk
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
id|mtdblk-&gt;mtd
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|mtdblk-&gt;cache_state
op_ne
id|STATE_DIRTY
)paren
r_return
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL2
comma
l_string|&quot;mtdblock: writing cached data for &bslash;&quot;%s&bslash;&quot; &quot;
l_string|&quot;at 0x%lx, size 0x%x&bslash;n&quot;
comma
id|mtd-&gt;name
comma
id|mtdblk-&gt;cache_offset
comma
id|mtdblk-&gt;cache_size
)paren
suffix:semicolon
id|ret
op_assign
id|erase_write
(paren
id|mtd
comma
id|mtdblk-&gt;cache_offset
comma
id|mtdblk-&gt;cache_size
comma
id|mtdblk-&gt;cache_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Here we could argably set the cache state to STATE_CLEAN.&n;&t; * However this could lead to inconsistency since we will not &n;&t; * be notified if this content is altered on the flash by other &n;&t; * means.  Let&squot;s declare it empty and leave buffering tasks to&n;&t; * the buffer cache instead.&n;&t; */
id|mtdblk-&gt;cache_state
op_assign
id|STATE_EMPTY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_cached_write
r_static
r_int
id|do_cached_write
(paren
r_struct
id|mtdblk_dev
op_star
id|mtdblk
comma
r_int
r_int
id|pos
comma
r_int
id|len
comma
r_const
r_char
op_star
id|buf
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
id|mtdblk-&gt;mtd
suffix:semicolon
r_int
r_int
id|sect_size
op_assign
id|mtdblk-&gt;cache_size
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL2
comma
l_string|&quot;mtdblock: write on &bslash;&quot;%s&bslash;&quot; at 0x%lx, size 0x%x&bslash;n&quot;
comma
id|mtd-&gt;name
comma
id|pos
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sect_size
)paren
r_return
id|MTD_WRITE
(paren
id|mtd
comma
id|pos
comma
id|len
comma
op_amp
id|retlen
comma
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
r_int
id|sect_start
op_assign
(paren
id|pos
op_div
id|sect_size
)paren
op_star
id|sect_size
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|pos
op_minus
id|sect_start
suffix:semicolon
r_int
r_int
id|size
op_assign
id|sect_size
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|len
)paren
(brace
id|size
op_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
id|sect_size
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * We are covering a whole sector.  Thus there is no&n;&t;&t;&t; * need to bother with the cache while it may still be&n;&t;&t;&t; * useful for other partial writes.&n;&t;&t;&t; */
id|ret
op_assign
id|erase_write
(paren
id|mtd
comma
id|pos
comma
id|size
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Partial sector: need to use the cache */
r_if
c_cond
(paren
id|mtdblk-&gt;cache_state
op_eq
id|STATE_DIRTY
op_logical_and
id|mtdblk-&gt;cache_offset
op_ne
id|sect_start
)paren
(brace
id|ret
op_assign
id|write_cached_data
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mtdblk-&gt;cache_state
op_eq
id|STATE_EMPTY
op_logical_or
id|mtdblk-&gt;cache_offset
op_ne
id|sect_start
)paren
(brace
multiline_comment|/* fill the cache with the current sector */
id|mtdblk-&gt;cache_state
op_assign
id|STATE_EMPTY
suffix:semicolon
id|ret
op_assign
id|MTD_READ
c_func
(paren
id|mtd
comma
id|sect_start
comma
id|sect_size
comma
op_amp
id|retlen
comma
id|mtdblk-&gt;cache_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|retlen
op_ne
id|sect_size
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|mtdblk-&gt;cache_offset
op_assign
id|sect_start
suffix:semicolon
id|mtdblk-&gt;cache_size
op_assign
id|sect_size
suffix:semicolon
id|mtdblk-&gt;cache_state
op_assign
id|STATE_CLEAN
suffix:semicolon
)brace
multiline_comment|/* write data to our local cache */
id|memcpy
(paren
id|mtdblk-&gt;cache_data
op_plus
id|offset
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|mtdblk-&gt;cache_state
op_assign
id|STATE_DIRTY
suffix:semicolon
)brace
id|buf
op_add_assign
id|size
suffix:semicolon
id|pos
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_cached_read
r_static
r_int
id|do_cached_read
(paren
r_struct
id|mtdblk_dev
op_star
id|mtdblk
comma
r_int
r_int
id|pos
comma
r_int
id|len
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
id|mtdblk-&gt;mtd
suffix:semicolon
r_int
r_int
id|sect_size
op_assign
id|mtdblk-&gt;cache_size
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL2
comma
l_string|&quot;mtdblock: read on &bslash;&quot;%s&bslash;&quot; at 0x%lx, size 0x%x&bslash;n&quot;
comma
id|mtd-&gt;name
comma
id|pos
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sect_size
)paren
r_return
id|MTD_READ
(paren
id|mtd
comma
id|pos
comma
id|len
comma
op_amp
id|retlen
comma
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
r_int
id|sect_start
op_assign
(paren
id|pos
op_div
id|sect_size
)paren
op_star
id|sect_size
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|pos
op_minus
id|sect_start
suffix:semicolon
r_int
r_int
id|size
op_assign
id|sect_size
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|len
)paren
id|size
op_assign
id|len
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check if the requested data is already cached&n;&t;&t; * Read the requested amount of data from our internal cache if it&n;&t;&t; * contains what we want, otherwise we read the data directly&n;&t;&t; * from flash.&n;&t;&t; */
r_if
c_cond
(paren
id|mtdblk-&gt;cache_state
op_ne
id|STATE_EMPTY
op_logical_and
id|mtdblk-&gt;cache_offset
op_eq
id|sect_start
)paren
(brace
id|memcpy
(paren
id|buf
comma
id|mtdblk-&gt;cache_data
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|MTD_READ
(paren
id|mtd
comma
id|pos
comma
id|size
comma
op_amp
id|retlen
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|retlen
op_ne
id|size
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|buf
op_add_assign
id|size
suffix:semicolon
id|pos
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mtdblock_open
r_static
r_int
id|mtdblock_open
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
id|mtdblk_dev
op_star
id|mtdblk
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
r_int
id|dev
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL1
comma
l_string|&quot;mtdblock_open&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|MAX_MTD_DEVICES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|MTD_ABSENT
op_eq
id|mtd-&gt;type
)paren
(brace
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s already open, no need to piss about. */
r_if
c_cond
(paren
id|mtdblks
(braket
id|dev
)braket
)paren
(brace
id|mtdblks
(braket
id|dev
)braket
op_member_access_from_pointer
id|count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* OK, it&squot;s not open. Try to find it */
multiline_comment|/* First we have to drop the lock, because we have to&n;&t;   to things which might sleep.&n;&t;*/
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
id|mtdblk
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mtdblk_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtdblk
)paren
(brace
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|mtdblk
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mtdblk
)paren
)paren
suffix:semicolon
id|mtdblk-&gt;count
op_assign
l_int|1
suffix:semicolon
id|mtdblk-&gt;mtd
op_assign
id|mtd
suffix:semicolon
id|init_MUTEX
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|mtdblk-&gt;cache_state
op_assign
id|STATE_EMPTY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mtdblk-&gt;mtd-&gt;flags
op_amp
id|MTD_CAP_RAM
)paren
op_ne
id|MTD_CAP_RAM
op_logical_and
id|mtdblk-&gt;mtd-&gt;erasesize
)paren
(brace
id|mtdblk-&gt;cache_size
op_assign
id|mtdblk-&gt;mtd-&gt;erasesize
suffix:semicolon
id|mtdblk-&gt;cache_data
op_assign
id|vmalloc
c_func
(paren
id|mtdblk-&gt;mtd-&gt;erasesize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtdblk-&gt;cache_data
)paren
(brace
id|put_mtd_device
c_func
(paren
id|mtdblk-&gt;mtd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
multiline_comment|/* OK, we&squot;ve created a new one. Add it to the list. */
id|spin_lock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtdblks
(braket
id|dev
)braket
)paren
(brace
multiline_comment|/* Another CPU made one at the same time as us. */
id|mtdblks
(braket
id|dev
)braket
op_member_access_from_pointer
id|count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtdblk-&gt;mtd
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|mtdblk-&gt;cache_data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|mtdblks
(braket
id|dev
)braket
op_assign
id|mtdblk
suffix:semicolon
id|mtd_sizes
(braket
id|dev
)braket
op_assign
id|mtdblk-&gt;mtd-&gt;size
op_div
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|mtdblk-&gt;mtd-&gt;erasesize
)paren
id|mtd_blksizes
(braket
id|dev
)braket
op_assign
id|mtdblk-&gt;mtd-&gt;erasesize
suffix:semicolon
r_if
c_cond
(paren
id|mtd_blksizes
(braket
id|dev
)braket
OG
id|PAGE_SIZE
)paren
id|mtd_blksizes
(braket
id|dev
)braket
op_assign
id|PAGE_SIZE
suffix:semicolon
id|set_device_ro
(paren
id|inode-&gt;i_rdev
comma
op_logical_neg
(paren
id|mtdblk-&gt;mtd-&gt;flags
op_amp
id|MTD_WRITEABLE
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL1
comma
l_string|&quot;ok&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mtdblock_release
r_static
id|release_t
id|mtdblock_release
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
id|dev
suffix:semicolon
r_struct
id|mtdblk_dev
op_star
id|mtdblk
suffix:semicolon
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL1
comma
l_string|&quot;mtdblock_release&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
l_int|NULL
)paren
id|release_return
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|invalidate_device
c_func
(paren
id|inode-&gt;i_rdev
comma
l_int|1
)paren
suffix:semicolon
id|dev
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|mtdblk
op_assign
id|mtdblks
(braket
id|dev
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|write_cached_data
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|mtdblk-&gt;count
)paren
(brace
multiline_comment|/* It was the last usage. Free the device */
id|mtdblks
(braket
id|dev
)braket
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtdblk-&gt;mtd-&gt;sync
)paren
id|mtdblk-&gt;mtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|mtdblk-&gt;mtd
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtdblk-&gt;mtd
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|mtdblk-&gt;cache_data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|MTD_DEBUG_LEVEL1
comma
l_string|&quot;ok&bslash;n&quot;
)paren
suffix:semicolon
id|release_return
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * This is a special request_fn because it is executed in a process context &n; * to be able to sleep independently of the caller.  The queue_lock &n; * is held upon entry and exit.&n; * The head of our request queue is considered active so there is no need &n; * to dequeue requests before we are done.&n; */
DECL|function|handle_mtdblock_request
r_static
r_void
id|handle_mtdblock_request
c_func
(paren
r_void
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|mtdblk_dev
op_star
id|mtdblk
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|INIT_REQUEST
suffix:semicolon
id|req
op_assign
id|CURRENT
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|QUEUE-&gt;queue_lock
)paren
suffix:semicolon
id|mtdblk
op_assign
id|mtdblks
(braket
id|minor
c_func
(paren
id|req-&gt;rq_dev
)paren
)braket
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|minor
c_func
(paren
id|req-&gt;rq_dev
)paren
op_ge
id|MAX_MTD_DEVICES
)paren
id|panic
c_func
(paren
id|__FUNCTION__
l_string|&quot;: minor out of bound&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
id|REQ_CMD
)paren
r_goto
id|end_req
suffix:semicolon
r_if
c_cond
(paren
(paren
id|req-&gt;sector
op_plus
id|req-&gt;current_nr_sectors
)paren
OG
(paren
id|mtdblk-&gt;mtd-&gt;size
op_rshift
l_int|9
)paren
)paren
r_goto
id|end_req
suffix:semicolon
singleline_comment|// Handle the request
r_switch
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|CURRENT
)paren
)paren
(brace
r_int
id|err
suffix:semicolon
r_case
id|READ
suffix:colon
id|down
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|err
op_assign
id|do_cached_read
(paren
id|mtdblk
comma
id|req-&gt;sector
op_lshift
l_int|9
comma
id|req-&gt;current_nr_sectors
op_lshift
l_int|9
comma
id|req-&gt;buffer
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|res
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
singleline_comment|// Read only device
r_if
c_cond
(paren
op_logical_neg
(paren
id|mtdblk-&gt;mtd-&gt;flags
op_amp
id|MTD_WRITEABLE
)paren
)paren
r_break
suffix:semicolon
singleline_comment|// Do the write
id|down
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|err
op_assign
id|do_cached_write
(paren
id|mtdblk
comma
id|req-&gt;sector
op_lshift
l_int|9
comma
id|req-&gt;current_nr_sectors
op_lshift
l_int|9
comma
id|req-&gt;buffer
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|res
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|end_req
suffix:colon
id|spin_lock_irq
c_func
(paren
op_amp
id|QUEUE-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|end_that_request_first
c_func
(paren
id|req
comma
id|res
comma
id|req-&gt;hard_cur_sectors
)paren
)paren
(brace
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
)brace
)brace
DECL|variable|leaving
r_static
r_volatile
r_int
id|leaving
op_assign
l_int|0
suffix:semicolon
r_static
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|thread_sem
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|thr_wq
)paren
suffix:semicolon
DECL|function|mtdblock_thread
r_int
id|mtdblock_thread
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
multiline_comment|/* we might get involved when memory gets low, so use PF_MEMALLOC */
id|tsk-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;mtdblockd&quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|tsk-&gt;blocked
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|leaving
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|thr_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|QUEUE-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|QUEUE_EMPTY
op_logical_or
id|QUEUE_PLUGGED
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|QUEUE-&gt;queue_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|thr_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_else
(brace
id|remove_wait_queue
c_func
(paren
op_amp
id|thr_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|handle_mtdblock_request
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|QUEUE-&gt;queue_lock
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|thread_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
DECL|macro|RQFUNC_ARG
mdefine_line|#define RQFUNC_ARG void
macro_line|#else
DECL|macro|RQFUNC_ARG
mdefine_line|#define RQFUNC_ARG request_queue_t *q
macro_line|#endif
DECL|function|mtdblock_request
r_static
r_void
id|mtdblock_request
c_func
(paren
id|RQFUNC_ARG
)paren
(brace
multiline_comment|/* Don&squot;t do anything, except wake the thread if necessary */
id|wake_up
c_func
(paren
op_amp
id|thr_wq
)paren
suffix:semicolon
)brace
DECL|function|mtdblock_ioctl
r_static
r_int
id|mtdblock_ioctl
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
id|mtdblk_dev
op_star
id|mtdblk
suffix:semicolon
id|mtdblk
op_assign
id|mtdblks
(braket
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
macro_line|#ifdef PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|mtdblk
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKGETSIZE
suffix:colon
multiline_comment|/* Return device size */
r_return
id|put_user
c_func
(paren
(paren
id|mtdblk-&gt;mtd-&gt;size
op_rshift
l_int|9
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKGETSIZE64
suffix:colon
r_return
id|put_user
c_func
(paren
(paren
id|u64
)paren
id|mtdblk-&gt;mtd-&gt;size
comma
(paren
id|u64
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKFLSBUF
suffix:colon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,2,0)
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
macro_line|#endif
id|fsync_bdev
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
id|write_cached_data
c_func
(paren
id|mtdblk
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtdblk-&gt;cache_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtdblk-&gt;mtd-&gt;sync
)paren
id|mtdblk-&gt;mtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|mtdblk-&gt;mtd
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
macro_line|#if LINUX_VERSION_CODE &lt; 0x20326
DECL|variable|mtd_fops
r_static
r_struct
id|file_operations
id|mtd_fops
op_assign
(brace
id|open
suffix:colon
id|mtdblock_open
comma
id|ioctl
suffix:colon
id|mtdblock_ioctl
comma
id|release
suffix:colon
id|mtdblock_release
comma
id|read
suffix:colon
id|block_read
comma
id|write
suffix:colon
id|block_write
)brace
suffix:semicolon
macro_line|#else
DECL|variable|mtd_fops
r_static
r_struct
id|block_device_operations
id|mtd_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|mtdblock_open
comma
id|release
suffix:colon
id|mtdblock_release
comma
id|ioctl
suffix:colon
id|mtdblock_ioctl
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEVFS_FS
multiline_comment|/* Notification that a new device has been added. Create the devfs entry for&n; * it. */
DECL|function|mtd_notify_add
r_static
r_void
id|mtd_notify_add
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
op_logical_or
id|mtd-&gt;type
op_eq
id|MTD_ABSENT
)paren
r_return
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|mtd-&gt;index
)paren
suffix:semicolon
id|devfs_rw_handle
(braket
id|mtd-&gt;index
)braket
op_assign
id|devfs_register
c_func
(paren
id|devfs_dir_handle
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|MTD_BLOCK_MAJOR
comma
id|mtd-&gt;index
comma
id|S_IFBLK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|mtd_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|mtd_notify_remove
r_static
r_void
id|mtd_notify_remove
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mtd
op_logical_or
id|mtd-&gt;type
op_eq
id|MTD_ABSENT
)paren
r_return
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|devfs_rw_handle
(braket
id|mtd-&gt;index
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|mtddev_lock
r_static
id|spinlock_t
id|mtddev_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|init_mtdblock
r_int
id|__init
id|init_mtdblock
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|mtdblks_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
r_if
c_cond
(paren
id|devfs_register_blkdev
c_func
(paren
id|MTD_BLOCK_MAJOR
comma
id|DEVICE_NAME
comma
op_amp
id|mtd_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Can&squot;t allocate major number %d for Memory Technology Devices.&bslash;n&quot;
comma
id|MTD_BLOCK_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|devfs_dir_handle
op_assign
id|devfs_mk_dir
c_func
(paren
l_int|NULL
comma
id|DEVICE_NAME
comma
l_int|NULL
)paren
suffix:semicolon
id|register_mtd_user
c_func
(paren
op_amp
id|notifier
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|MAJOR_NR
comma
id|DEVICE_NAME
comma
op_amp
id|mtd_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Can&squot;t allocate major number %d for Memory Technology Devices.&bslash;n&quot;
comma
id|MTD_BLOCK_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* We fill it in at open() time. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mtd_sizes
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|mtd_blksizes
(braket
id|i
)braket
op_assign
id|BLOCK_SIZE
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|thr_wq
)paren
suffix:semicolon
multiline_comment|/* Allow the block size to default to BLOCK_SIZE. */
id|blksize_size
(braket
id|MAJOR_NR
)braket
op_assign
id|mtd_blksizes
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|mtd_sizes
suffix:semicolon
id|blk_init_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
comma
op_amp
id|mtdblock_request
comma
op_amp
id|mtddev_lock
)paren
suffix:semicolon
id|kernel_thread
(paren
id|mtdblock_thread
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_mtdblock
r_static
r_void
id|__exit
id|cleanup_mtdblock
c_func
(paren
r_void
)paren
(brace
id|leaving
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|thr_wq
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|thread_sem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|unregister_mtd_user
c_func
(paren
op_amp
id|notifier
)paren
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|devfs_dir_handle
)paren
suffix:semicolon
id|devfs_unregister_blkdev
c_func
(paren
id|MTD_BLOCK_MAJOR
comma
id|DEVICE_NAME
)paren
suffix:semicolon
macro_line|#else
id|unregister_blkdev
c_func
(paren
id|MAJOR_NR
comma
id|DEVICE_NAME
)paren
suffix:semicolon
macro_line|#endif
id|blk_cleanup_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
)paren
suffix:semicolon
id|blksize_size
(braket
id|MAJOR_NR
)braket
op_assign
l_int|NULL
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|init_mtdblock
id|module_init
c_func
(paren
id|init_mtdblock
)paren
suffix:semicolon
DECL|variable|cleanup_mtdblock
id|module_exit
c_func
(paren
id|cleanup_mtdblock
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Nicolas Pitre &lt;nico@cam.org&gt; et al.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Caching read/erase/writeback block device emulation access to MTD devices&quot;
)paren
suffix:semicolon
eof
