multiline_comment|/*&n; * multipath.c : Multiple Devices driver for Linux&n; *&n; * Copyright (C) 1999, 2000, 2001 Ingo Molnar, Red Hat&n; *&n; * Copyright (C) 1996, 1997, 1998 Ingo Molnar, Miguel de Icaza, Gadi Oxman&n; *&n; * MULTIPATH management functions.&n; *&n; * derived from raid1.c.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/raid/multipath.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
DECL|macro|MAX_WORK_PER_DISK
mdefine_line|#define MAX_WORK_PER_DISK 128
DECL|macro|NR_RESERVED_BUFS
mdefine_line|#define&t;NR_RESERVED_BUFS&t;32
DECL|variable|multipath_personality
r_static
id|mdk_personality_t
id|multipath_personality
suffix:semicolon
DECL|variable|retry_list_lock
r_static
id|spinlock_t
id|retry_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|multipath_retry_list
DECL|variable|multipath_retry_tail
r_struct
id|multipath_bh
op_star
id|multipath_retry_list
op_assign
l_int|NULL
comma
op_star
op_star
id|multipath_retry_tail
suffix:semicolon
DECL|function|mp_pool_alloc
r_static
r_void
op_star
id|mp_pool_alloc
c_func
(paren
r_int
id|gfp_flags
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|multipath_bh
op_star
id|mpb
suffix:semicolon
id|mpb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mpb
)paren
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpb
)paren
id|memset
c_func
(paren
id|mpb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mpb
)paren
)paren
suffix:semicolon
r_return
id|mpb
suffix:semicolon
)brace
DECL|function|mp_pool_free
r_static
r_void
id|mp_pool_free
c_func
(paren
r_void
op_star
id|mpb
comma
r_void
op_star
id|data
)paren
(brace
id|kfree
c_func
(paren
id|mpb
)paren
suffix:semicolon
)brace
DECL|function|multipath_map
r_static
r_int
id|multipath_map
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
op_star
id|rdevp
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_int
id|i
comma
id|disks
op_assign
id|conf-&gt;raid_disks
suffix:semicolon
multiline_comment|/*&n;&t; * Later we do read balancing on the read side &n;&t; * now we use the first available disk.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
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
id|disks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mdk_rdev_t
op_star
id|rdev
op_assign
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|rdev
suffix:semicolon
r_if
c_cond
(paren
id|rdev
op_logical_and
id|rdev-&gt;in_sync
)paren
(brace
op_star
id|rdevp
op_assign
id|rdev
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rdev-&gt;nr_pending
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath_map(): no more operational IO paths?&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|multipath_reschedule_retry
r_static
r_void
id|multipath_reschedule_retry
(paren
r_struct
id|multipath_bh
op_star
id|mp_bh
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|mddev_t
op_star
id|mddev
op_assign
id|mp_bh-&gt;mddev
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|retry_list_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|multipath_retry_list
op_eq
l_int|NULL
)paren
id|multipath_retry_tail
op_assign
op_amp
id|multipath_retry_list
suffix:semicolon
op_star
id|multipath_retry_tail
op_assign
id|mp_bh
suffix:semicolon
id|multipath_retry_tail
op_assign
op_amp
id|mp_bh-&gt;next_mp
suffix:semicolon
id|mp_bh-&gt;next_mp
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|retry_list_lock
comma
id|flags
)paren
suffix:semicolon
id|md_wakeup_thread
c_func
(paren
id|mddev-&gt;thread
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * multipath_end_bh_io() is called when we have finished servicing a multipathed&n; * operation and are ready to return a success/failure code to the buffer&n; * cache layer.&n; */
DECL|function|multipath_end_bh_io
r_static
r_void
id|multipath_end_bh_io
(paren
r_struct
id|multipath_bh
op_star
id|mp_bh
comma
r_int
id|uptodate
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
id|mp_bh-&gt;master_bio
suffix:semicolon
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mp_bh-&gt;mddev
)paren
suffix:semicolon
id|bio_endio
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
comma
id|uptodate
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|mp_bh
comma
id|conf-&gt;pool
)paren
suffix:semicolon
)brace
DECL|function|multipath_end_request
r_int
id|multipath_end_request
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|bytes_done
comma
r_int
id|error
)paren
(brace
r_int
id|uptodate
op_assign
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
r_struct
id|multipath_bh
op_star
id|mp_bh
op_assign
(paren
r_struct
id|multipath_bh
op_star
)paren
(paren
id|bio-&gt;bi_private
)paren
suffix:semicolon
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mp_bh-&gt;mddev
)paren
suffix:semicolon
id|mdk_rdev_t
op_star
id|rdev
op_assign
id|conf-&gt;multipaths
(braket
id|mp_bh-&gt;path
)braket
dot
id|rdev
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|uptodate
)paren
id|multipath_end_bh_io
c_func
(paren
id|mp_bh
comma
id|uptodate
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t; * oops, IO error:&n;&t;&t; */
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|md_error
(paren
id|mp_bh-&gt;mddev
comma
id|rdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: %s: rescheduling sector %llu&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|rdev-&gt;bdev
comma
id|b
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|bio-&gt;bi_sector
)paren
suffix:semicolon
id|multipath_reschedule_retry
c_func
(paren
id|mp_bh
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|rdev-&gt;nr_pending
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine returns the disk from which the requested read should&n; * be done.&n; */
DECL|function|multipath_read_balance
r_static
r_int
id|multipath_read_balance
(paren
id|multipath_conf_t
op_star
id|conf
)paren
(brace
r_int
id|disk
suffix:semicolon
r_for
c_loop
(paren
id|disk
op_assign
l_int|0
suffix:semicolon
id|disk
OL
id|conf-&gt;raid_disks
suffix:semicolon
id|disk
op_increment
)paren
(brace
id|mdk_rdev_t
op_star
id|rdev
op_assign
id|conf-&gt;multipaths
(braket
id|disk
)braket
dot
id|rdev
suffix:semicolon
r_if
c_cond
(paren
id|rdev
op_logical_and
id|rdev-&gt;in_sync
)paren
r_return
id|disk
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unplug_slaves
r_static
r_void
id|unplug_slaves
c_func
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_int
id|i
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
id|mddev-&gt;raid_disks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mdk_rdev_t
op_star
id|rdev
op_assign
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|rdev
suffix:semicolon
r_if
c_cond
(paren
id|rdev
op_logical_and
op_logical_neg
id|rdev-&gt;faulty
)paren
(brace
id|request_queue_t
op_star
id|r_queue
op_assign
id|bdev_get_queue
c_func
(paren
id|rdev-&gt;bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r_queue-&gt;unplug_fn
)paren
id|r_queue
op_member_access_from_pointer
id|unplug_fn
c_func
(paren
id|r_queue
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|multipath_unplug
r_static
r_void
id|multipath_unplug
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
id|unplug_slaves
c_func
(paren
id|q-&gt;queuedata
)paren
suffix:semicolon
)brace
DECL|function|multipath_make_request
r_static
r_int
id|multipath_make_request
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|mddev_t
op_star
id|mddev
op_assign
id|q-&gt;queuedata
suffix:semicolon
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_struct
id|multipath_bh
op_star
id|mp_bh
suffix:semicolon
r_struct
id|multipath_info
op_star
id|multipath
suffix:semicolon
id|mp_bh
op_assign
id|mempool_alloc
c_func
(paren
id|conf-&gt;pool
comma
id|GFP_NOIO
)paren
suffix:semicolon
id|mp_bh-&gt;master_bio
op_assign
id|bio
suffix:semicolon
id|mp_bh-&gt;mddev
op_assign
id|mddev
suffix:semicolon
r_if
c_cond
(paren
id|bio_data_dir
c_func
(paren
id|bio
)paren
op_eq
id|WRITE
)paren
(brace
id|disk_stat_inc
c_func
(paren
id|mddev-&gt;gendisk
comma
id|writes
)paren
suffix:semicolon
id|disk_stat_add
c_func
(paren
id|mddev-&gt;gendisk
comma
id|write_sectors
comma
id|bio_sectors
c_func
(paren
id|bio
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|disk_stat_inc
c_func
(paren
id|mddev-&gt;gendisk
comma
id|reads
)paren
suffix:semicolon
id|disk_stat_add
c_func
(paren
id|mddev-&gt;gendisk
comma
id|read_sectors
comma
id|bio_sectors
c_func
(paren
id|bio
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * read balancing logic:&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
id|mp_bh-&gt;path
op_assign
id|multipath_read_balance
c_func
(paren
id|conf
)paren
suffix:semicolon
id|multipath
op_assign
id|conf-&gt;multipaths
op_plus
id|mp_bh-&gt;path
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|multipath-&gt;rdev-&gt;nr_pending
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
id|mp_bh-&gt;bio
op_assign
op_star
id|bio
suffix:semicolon
id|mp_bh-&gt;bio.bi_bdev
op_assign
id|multipath-&gt;rdev-&gt;bdev
suffix:semicolon
id|mp_bh-&gt;bio.bi_rw
op_or_assign
(paren
l_int|1
op_lshift
id|BIO_RW_FAILFAST
)paren
suffix:semicolon
id|mp_bh-&gt;bio.bi_end_io
op_assign
id|multipath_end_request
suffix:semicolon
id|mp_bh-&gt;bio.bi_private
op_assign
id|mp_bh
suffix:semicolon
id|generic_make_request
c_func
(paren
op_amp
id|mp_bh-&gt;bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|multipath_status
r_static
r_void
id|multipath_status
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|mddev_t
op_star
id|mddev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|seq_printf
(paren
id|seq
comma
l_string|&quot; [%d/%d] [&quot;
comma
id|conf-&gt;raid_disks
comma
id|conf-&gt;working_disks
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
id|conf-&gt;raid_disks
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
(paren
id|seq
comma
l_string|&quot;%s&quot;
comma
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|rdev
op_logical_and
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|rdev-&gt;in_sync
ques
c_cond
l_string|&quot;U&quot;
suffix:colon
l_string|&quot;_&quot;
)paren
suffix:semicolon
id|seq_printf
(paren
id|seq
comma
l_string|&quot;]&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Careful, this can execute in IRQ contexts as well!&n; */
DECL|function|multipath_error
r_static
r_void
id|multipath_error
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
id|rdev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;working_disks
op_le
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Uh oh, we can do nothing if this is our last path, but&n;&t;&t; * first check if this is a queued request for a device&n;&t;&t; * which has just failed.&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;multipath: only one IO path left and IO error.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* leave it active... it&squot;s all we have */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Mark disk as unusable&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rdev-&gt;faulty
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|rdev-&gt;in_sync
op_assign
l_int|0
suffix:semicolon
id|rdev-&gt;faulty
op_assign
l_int|1
suffix:semicolon
id|mddev-&gt;sb_dirty
op_assign
l_int|1
suffix:semicolon
id|conf-&gt;working_disks
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;multipath: IO failure on %s,&quot;
l_string|&quot; disabling IO path. &bslash;n&t;Operation continuing&quot;
l_string|&quot; on %d IO paths.&bslash;n&quot;
comma
id|bdevname
(paren
id|rdev-&gt;bdev
comma
id|b
)paren
comma
id|conf-&gt;working_disks
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|print_multipath_conf
r_static
r_void
id|print_multipath_conf
(paren
id|multipath_conf_t
op_star
id|conf
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|multipath_info
op_star
id|tmp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MULTIPATH conf printout:&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(conf==NULL)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; --- wd:%d rd:%d&bslash;n&quot;
comma
id|conf-&gt;working_disks
comma
id|conf-&gt;raid_disks
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
id|conf-&gt;raid_disks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|tmp
op_assign
id|conf-&gt;multipaths
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;rdev
)paren
id|printk
c_func
(paren
l_string|&quot; disk%d, o:%d, dev:%s&bslash;n&quot;
comma
id|i
comma
op_logical_neg
id|tmp-&gt;rdev-&gt;faulty
comma
id|bdevname
c_func
(paren
id|tmp-&gt;rdev-&gt;bdev
comma
id|b
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|multipath_add_disk
r_static
r_int
id|multipath_add_disk
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
id|mdk_rdev_t
op_star
id|rdev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_int
id|path
suffix:semicolon
r_struct
id|multipath_info
op_star
id|p
suffix:semicolon
id|print_multipath_conf
c_func
(paren
id|conf
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|path
op_assign
l_int|0
suffix:semicolon
id|path
OL
id|mddev-&gt;raid_disks
suffix:semicolon
id|path
op_increment
)paren
r_if
c_cond
(paren
(paren
id|p
op_assign
id|conf-&gt;multipaths
op_plus
id|path
)paren
op_member_access_from_pointer
id|rdev
op_eq
l_int|NULL
)paren
(brace
id|p-&gt;rdev
op_assign
id|rdev
suffix:semicolon
id|blk_queue_stack_limits
c_func
(paren
id|mddev-&gt;queue
comma
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue
)paren
suffix:semicolon
multiline_comment|/* as we don&squot;t honour merge_bvec_fn, we must never risk&n;&t;&t; * violating it, so limit -&gt;max_sector to one PAGE, as&n;&t;&t; * a one page request is never in violation.&n;&t;&t; * (Note: it is very unlikely that a device with&n;&t;&t; * merge_bvec_fn will be involved in multipath.)&n;&t;&t; */
r_if
c_cond
(paren
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue-&gt;merge_bvec_fn
op_logical_and
id|mddev-&gt;queue-&gt;max_sectors
OG
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
)paren
id|mddev-&gt;queue-&gt;max_sectors
op_assign
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
id|conf-&gt;working_disks
op_increment
suffix:semicolon
id|rdev-&gt;raid_disk
op_assign
id|path
suffix:semicolon
id|rdev-&gt;in_sync
op_assign
l_int|1
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
id|print_multipath_conf
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|function|multipath_remove_disk
r_static
r_int
id|multipath_remove_disk
c_func
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|number
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|err
op_assign
l_int|1
suffix:semicolon
r_struct
id|multipath_info
op_star
id|p
op_assign
id|conf-&gt;multipaths
op_plus
id|number
suffix:semicolon
id|print_multipath_conf
c_func
(paren
id|conf
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;rdev
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;rdev-&gt;in_sync
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|p-&gt;rdev-&gt;nr_pending
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hot-remove-disk, slot %d is identified&quot;
l_string|&quot; but is still operational!&bslash;n&quot;
comma
id|number
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|p-&gt;rdev
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
id|MD_BUG
c_func
(paren
)paren
suffix:semicolon
m_abort
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|conf-&gt;device_lock
)paren
suffix:semicolon
id|print_multipath_conf
c_func
(paren
id|conf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a kernel thread which:&n; *&n; *&t;1.&t;Retries failed read operations on working multipaths.&n; *&t;2.&t;Updates the raid superblock when problems encounter.&n; *&t;3.&t;Performs writes following reads for array syncronising.&n; */
DECL|function|multipathd
r_static
r_void
id|multipathd
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
r_struct
id|multipath_bh
op_star
id|mp_bh
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|mdk_rdev_t
op_star
id|rdev
suffix:semicolon
id|md_check_recovery
c_func
(paren
id|mddev
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|retry_list_lock
comma
id|flags
)paren
suffix:semicolon
id|mp_bh
op_assign
id|multipath_retry_list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mp_bh
)paren
r_break
suffix:semicolon
id|multipath_retry_list
op_assign
id|mp_bh-&gt;next_mp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|retry_list_lock
comma
id|flags
)paren
suffix:semicolon
id|mddev
op_assign
id|mp_bh-&gt;mddev
suffix:semicolon
id|bio
op_assign
op_amp
id|mp_bh-&gt;bio
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|mp_bh-&gt;master_bio-&gt;bi_sector
suffix:semicolon
id|rdev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|multipath_map
(paren
id|mddev
comma
op_amp
id|rdev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;multipath: %s: unrecoverable IO read&quot;
l_string|&quot; error for block %llu&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bio-&gt;bi_bdev
comma
id|b
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|bio-&gt;bi_sector
)paren
suffix:semicolon
id|multipath_end_bh_io
c_func
(paren
id|mp_bh
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: %s: redirecting sector %llu&quot;
l_string|&quot; to another IO path&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bio-&gt;bi_bdev
comma
id|b
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|bio-&gt;bi_sector
)paren
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|rdev-&gt;bdev
suffix:semicolon
id|generic_make_request
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|retry_list_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|multipath_run
r_static
r_int
id|multipath_run
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
suffix:semicolon
r_int
id|disk_idx
suffix:semicolon
r_struct
id|multipath_info
op_star
id|disk
suffix:semicolon
id|mdk_rdev_t
op_star
id|rdev
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|mddev-&gt;level
op_ne
id|LEVEL_MULTIPATH
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;multipath: %s: raid level not set to multipath IO (%d)&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
comma
id|mddev-&gt;level
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * copy the already verified devices into our private MULTIPATH&n;&t; * bookkeeping area. [whatever we allocate in multipath_run(),&n;&t; * should be freed in multipath_stop()]&n;&t; */
id|conf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|multipath_conf_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
id|conf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: couldn&squot;t allocate memory for %s&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|conf
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|conf
)paren
)paren
suffix:semicolon
id|conf-&gt;multipaths
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|multipath_info
)paren
op_star
id|mddev-&gt;raid_disks
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;multipaths
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: couldn&squot;t allocate memory for %s&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
r_goto
id|out_free_conf
suffix:semicolon
)brace
id|memset
c_func
(paren
id|conf-&gt;multipaths
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|multipath_info
)paren
op_star
id|mddev-&gt;raid_disks
)paren
suffix:semicolon
id|mddev-&gt;queue-&gt;unplug_fn
op_assign
id|multipath_unplug
suffix:semicolon
id|conf-&gt;working_disks
op_assign
l_int|0
suffix:semicolon
id|ITERATE_RDEV
c_func
(paren
id|mddev
comma
id|rdev
comma
id|tmp
)paren
(brace
id|disk_idx
op_assign
id|rdev-&gt;raid_disk
suffix:semicolon
r_if
c_cond
(paren
id|disk_idx
OL
l_int|0
op_logical_or
id|disk_idx
op_ge
id|mddev-&gt;raid_disks
)paren
r_continue
suffix:semicolon
id|disk
op_assign
id|conf-&gt;multipaths
op_plus
id|disk_idx
suffix:semicolon
id|disk-&gt;rdev
op_assign
id|rdev
suffix:semicolon
id|blk_queue_stack_limits
c_func
(paren
id|mddev-&gt;queue
comma
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue
)paren
suffix:semicolon
multiline_comment|/* as we don&squot;t honour merge_bvec_fn, we must never risk&n;&t;&t; * violating it, not that we ever expect a device with&n;&t;&t; * a merge_bvec_fn to be involved in multipath */
r_if
c_cond
(paren
id|rdev-&gt;bdev-&gt;bd_disk-&gt;queue-&gt;merge_bvec_fn
op_logical_and
id|mddev-&gt;queue-&gt;max_sectors
OG
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
)paren
id|mddev-&gt;queue-&gt;max_sectors
op_assign
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rdev-&gt;faulty
)paren
id|conf-&gt;working_disks
op_increment
suffix:semicolon
)brace
id|conf-&gt;raid_disks
op_assign
id|mddev-&gt;raid_disks
suffix:semicolon
id|mddev-&gt;sb_dirty
op_assign
l_int|1
suffix:semicolon
id|conf-&gt;mddev
op_assign
id|mddev
suffix:semicolon
id|conf-&gt;device_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;working_disks
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: no operational IO paths for %s&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
r_goto
id|out_free_conf
suffix:semicolon
)brace
id|mddev-&gt;degraded
op_assign
id|conf-&gt;raid_disks
op_assign
id|conf-&gt;working_disks
suffix:semicolon
id|conf-&gt;pool
op_assign
id|mempool_create
c_func
(paren
id|NR_RESERVED_BUFS
comma
id|mp_pool_alloc
comma
id|mp_pool_free
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;pool
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: couldn&squot;t allocate memory for %s&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
r_goto
id|out_free_conf
suffix:semicolon
)brace
(brace
id|mddev-&gt;thread
op_assign
id|md_register_thread
c_func
(paren
id|multipathd
comma
id|mddev
comma
l_string|&quot;%s_multipath&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mddev-&gt;thread
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: couldn&squot;t allocate thread&quot;
l_string|&quot; for %s&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
)paren
suffix:semicolon
r_goto
id|out_free_conf
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;multipath: array %s active with %d out of %d IO paths&bslash;n&quot;
comma
id|mdname
c_func
(paren
id|mddev
)paren
comma
id|conf-&gt;working_disks
comma
id|mddev-&gt;raid_disks
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, everything is just fine now&n;&t; */
id|mddev-&gt;array_size
op_assign
id|mddev-&gt;size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_free_conf
suffix:colon
r_if
c_cond
(paren
id|conf-&gt;pool
)paren
id|mempool_destroy
c_func
(paren
id|conf-&gt;pool
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;multipaths
)paren
id|kfree
c_func
(paren
id|conf-&gt;multipaths
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|multipath_stop
r_static
r_int
id|multipath_stop
(paren
id|mddev_t
op_star
id|mddev
)paren
(brace
id|multipath_conf_t
op_star
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|md_unregister_thread
c_func
(paren
id|mddev-&gt;thread
)paren
suffix:semicolon
id|mempool_destroy
c_func
(paren
id|conf-&gt;pool
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conf-&gt;multipaths
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|conf
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|multipath_personality
r_static
id|mdk_personality_t
id|multipath_personality
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;multipath&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|make_request
op_assign
id|multipath_make_request
comma
dot
id|run
op_assign
id|multipath_run
comma
dot
id|stop
op_assign
id|multipath_stop
comma
dot
id|status
op_assign
id|multipath_status
comma
dot
id|error_handler
op_assign
id|multipath_error
comma
dot
id|hot_add_disk
op_assign
id|multipath_add_disk
comma
dot
id|hot_remove_disk
op_assign
id|multipath_remove_disk
comma
)brace
suffix:semicolon
DECL|function|multipath_init
r_static
r_int
id|__init
id|multipath_init
(paren
r_void
)paren
(brace
r_return
id|register_md_personality
(paren
id|MULTIPATH
comma
op_amp
id|multipath_personality
)paren
suffix:semicolon
)brace
DECL|function|multipath_exit
r_static
r_void
id|__exit
id|multipath_exit
(paren
r_void
)paren
(brace
id|unregister_md_personality
(paren
id|MULTIPATH
)paren
suffix:semicolon
)brace
DECL|variable|multipath_init
id|module_init
c_func
(paren
id|multipath_init
)paren
suffix:semicolon
DECL|variable|multipath_exit
id|module_exit
c_func
(paren
id|multipath_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;md-personality-7&quot;
)paren
suffix:semicolon
multiline_comment|/* MULTIPATH */
eof
