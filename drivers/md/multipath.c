multiline_comment|/*&n; * multipath.c : Multiple Devices driver for Linux&n; *&n; * Copyright (C) 1999, 2000, 2001 Ingo Molnar, Red Hat&n; *&n; * Copyright (C) 1996, 1997, 1998 Ingo Molnar, Miguel de Icaza, Gadi Oxman&n; *&n; * MULTIPATH management functions.&n; *&n; * derived from raid1.c.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/raid/multipath.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
DECL|macro|MAX_WORK_PER_DISK
mdefine_line|#define MAX_WORK_PER_DISK 128
DECL|macro|NR_RESERVED_BUFS
mdefine_line|#define&t;NR_RESERVED_BUFS&t;32
multiline_comment|/*&n; * The following can be used to debug the driver&n; */
DECL|macro|MULTIPATH_DEBUG
mdefine_line|#define MULTIPATH_DEBUG&t;0
macro_line|#if MULTIPATH_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x...)   printk(x)
DECL|macro|inline
mdefine_line|#define inline
DECL|macro|__inline__
mdefine_line|#define __inline__
macro_line|#else
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x...)  do { } while (0)
macro_line|#endif
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
r_struct
id|block_device
op_star
op_star
id|bdev
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
id|MD_SB_DISKS
suffix:semicolon
multiline_comment|/*&n;&t; * Later we do read balancing on the read side &n;&t; * now we use the first available disk.&n;&t; */
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
r_if
c_cond
(paren
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|operational
)paren
(brace
op_star
id|bdev
op_assign
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|bdev
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|printk
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
id|conf-&gt;thread
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
id|uptodate
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
r_void
id|multipath_end_request
c_func
(paren
r_struct
id|bio
op_star
id|bio
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
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_if
c_cond
(paren
id|uptodate
)paren
(brace
id|multipath_end_bh_io
c_func
(paren
id|mp_bh
comma
id|uptodate
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * oops, IO error:&n;&t; */
id|conf
op_assign
id|mddev_to_conf
c_func
(paren
id|mp_bh-&gt;mddev
)paren
suffix:semicolon
id|bdev
op_assign
id|conf-&gt;multipaths
(braket
id|mp_bh-&gt;path
)braket
dot
id|bdev
suffix:semicolon
id|md_error
(paren
id|mp_bh-&gt;mddev
comma
id|bdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;multipath: %s: rescheduling sector %lu&bslash;n&quot;
comma
id|bdev_partition_name
c_func
(paren
id|bdev
)paren
comma
id|bio-&gt;bi_sector
)paren
suffix:semicolon
id|multipath_reschedule_retry
c_func
(paren
id|mp_bh
)paren
suffix:semicolon
r_return
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
id|MD_SB_DISKS
suffix:semicolon
id|disk
op_increment
)paren
r_if
c_cond
(paren
id|conf-&gt;multipaths
(braket
id|disk
)braket
dot
id|operational
)paren
r_return
id|disk
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/*&n;&t; * read balancing logic:&n;&t; */
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
id|mp_bh-&gt;bio
op_assign
op_star
id|bio
suffix:semicolon
id|mp_bh-&gt;bio.bi_bdev
op_assign
id|multipath-&gt;bdev
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
r_int
id|multipath_status
(paren
r_char
op_star
id|page
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
id|sz
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
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
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;%s&quot;
comma
id|conf-&gt;multipaths
(braket
id|i
)braket
dot
id|operational
ques
c_cond
l_string|&quot;U&quot;
suffix:colon
l_string|&quot;_&quot;
)paren
suffix:semicolon
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;]&quot;
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
DECL|macro|LAST_DISK
mdefine_line|#define LAST_DISK KERN_ALERT &bslash;&n;&quot;multipath: only one IO path left and IO error.&bslash;n&quot;
DECL|macro|NO_SPARE_DISK
mdefine_line|#define NO_SPARE_DISK KERN_ALERT &bslash;&n;&quot;multipath: no spare IO path left!&bslash;n&quot;
DECL|macro|DISK_FAILED
mdefine_line|#define DISK_FAILED KERN_ALERT &bslash;&n;&quot;multipath: IO failure on %s, disabling IO path. &bslash;n&quot; &bslash;&n;&quot;&t;Operation continuing on %d IO paths.&bslash;n&quot;
DECL|function|mark_disk_bad
r_static
r_void
id|mark_disk_bad
(paren
id|mddev_t
op_star
id|mddev
comma
r_int
id|failed
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
r_struct
id|multipath_info
op_star
id|multipath
op_assign
id|conf-&gt;multipaths
op_plus
id|failed
suffix:semicolon
id|mdp_super_t
op_star
id|sb
op_assign
id|mddev-&gt;sb
suffix:semicolon
id|multipath-&gt;operational
op_assign
l_int|0
suffix:semicolon
id|mark_disk_faulty
c_func
(paren
id|sb-&gt;disks
op_plus
id|multipath-&gt;number
)paren
suffix:semicolon
id|mark_disk_nonsync
c_func
(paren
id|sb-&gt;disks
op_plus
id|multipath-&gt;number
)paren
suffix:semicolon
id|mark_disk_inactive
c_func
(paren
id|sb-&gt;disks
op_plus
id|multipath-&gt;number
)paren
suffix:semicolon
id|sb-&gt;active_disks
op_decrement
suffix:semicolon
id|sb-&gt;working_disks
op_decrement
suffix:semicolon
id|sb-&gt;failed_disks
op_increment
suffix:semicolon
id|mddev-&gt;sb_dirty
op_assign
l_int|1
suffix:semicolon
id|conf-&gt;working_disks
op_decrement
suffix:semicolon
id|printk
(paren
id|DISK_FAILED
comma
id|bdev_partition_name
(paren
id|multipath-&gt;bdev
)paren
comma
id|conf-&gt;working_disks
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Careful, this can execute in IRQ contexts as well!&n; */
DECL|function|multipath_error
r_static
r_int
id|multipath_error
(paren
id|mddev_t
op_star
id|mddev
comma
r_struct
id|block_device
op_star
id|bdev
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
r_struct
id|multipath_info
op_star
id|multipaths
op_assign
id|conf-&gt;multipaths
suffix:semicolon
r_int
id|disks
op_assign
id|MD_SB_DISKS
suffix:semicolon
r_int
id|i
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
r_if
c_cond
(paren
id|multipaths
(braket
id|i
)braket
dot
id|bdev
op_eq
id|bdev
op_logical_and
op_logical_neg
id|multipaths
(braket
id|i
)braket
dot
id|operational
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|printk
(paren
id|LAST_DISK
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* leave it active... it&squot;s all we have */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Mark disk as unusable&n;&t;&t; */
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
r_if
c_cond
(paren
id|multipaths
(braket
id|i
)braket
dot
id|bdev
op_eq
id|bdev
op_logical_and
id|multipaths
(braket
id|i
)braket
dot
id|operational
)paren
(brace
id|mark_disk_bad
c_func
(paren
id|mddev
comma
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|LAST_DISK
macro_line|#undef LAST_DISK
DECL|macro|NO_SPARE_DISK
macro_line|#undef NO_SPARE_DISK
DECL|macro|DISK_FAILED
macro_line|#undef DISK_FAILED
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
l_string|&quot; --- wd:%d rd:%d nd:%d&bslash;n&quot;
comma
id|conf-&gt;working_disks
comma
id|conf-&gt;raid_disks
comma
id|conf-&gt;nr_disks
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
id|MD_SB_DISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|conf-&gt;multipaths
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;operational
op_logical_or
id|tmp-&gt;number
op_logical_or
id|tmp-&gt;raid_disk
op_logical_or
id|tmp-&gt;used_slot
)paren
id|printk
c_func
(paren
l_string|&quot; disk%d, o:%d, n:%d rd:%d us:%d dev:%s&bslash;n&quot;
comma
id|i
comma
id|tmp-&gt;operational
comma
id|tmp-&gt;number
comma
id|tmp-&gt;raid_disk
comma
id|tmp-&gt;used_slot
comma
id|bdev_partition_name
c_func
(paren
id|tmp-&gt;bdev
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
id|mdp_disk_t
op_star
id|added_desc
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
id|err
op_assign
l_int|1
suffix:semicolon
r_int
id|i
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MD_SB_DISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|multipath_info
op_star
id|p
op_assign
id|conf-&gt;multipaths
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;used_slot
)paren
(brace
r_if
c_cond
(paren
id|added_desc-&gt;number
op_ne
id|i
)paren
r_break
suffix:semicolon
id|p-&gt;number
op_assign
id|added_desc-&gt;number
suffix:semicolon
id|p-&gt;raid_disk
op_assign
id|added_desc-&gt;raid_disk
suffix:semicolon
id|p-&gt;bdev
op_assign
id|rdev-&gt;bdev
suffix:semicolon
id|p-&gt;operational
op_assign
l_int|1
suffix:semicolon
id|p-&gt;used_slot
op_assign
l_int|1
suffix:semicolon
id|conf-&gt;nr_disks
op_increment
suffix:semicolon
id|conf-&gt;working_disks
op_increment
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|p-&gt;used_slot
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;operational
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hot-remove-disk, slot %d is identified but is still operational!&bslash;n&quot;
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
id|p-&gt;bdev
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;used_slot
op_assign
l_int|0
suffix:semicolon
id|conf-&gt;nr_disks
op_decrement
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
DECL|macro|IO_ERROR
mdefine_line|#define IO_ERROR KERN_ALERT &bslash;&n;&quot;multipath: %s: unrecoverable IO read error for block %lu&bslash;n&quot;
DECL|macro|REDIRECT_SECTOR
mdefine_line|#define REDIRECT_SECTOR KERN_ERR &bslash;&n;&quot;multipath: %s: redirecting sector %lu to another IO path&bslash;n&quot;
multiline_comment|/*&n; * This is a kernel thread which:&n; *&n; *&t;1.&t;Retries failed read operations on working multipaths.&n; *&t;2.&t;Updates the raid superblock when problems encounter.&n; *&t;3.&t;Performs writes following reads for array syncronising.&n; */
DECL|function|multipathd
r_static
r_void
id|multipathd
(paren
r_void
op_star
id|data
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
id|mddev_t
op_star
id|mddev
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
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
id|bdev
op_assign
id|bio-&gt;bi_bdev
suffix:semicolon
id|multipath_map
(paren
id|mddev
comma
op_amp
id|bio-&gt;bi_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_bdev
op_eq
id|bdev
)paren
(brace
id|printk
c_func
(paren
id|IO_ERROR
comma
id|bdev_partition_name
c_func
(paren
id|bio-&gt;bi_bdev
)paren
comma
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
id|REDIRECT_SECTOR
comma
id|bdev_partition_name
c_func
(paren
id|bio-&gt;bi_bdev
)paren
comma
id|bio-&gt;bi_sector
)paren
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
DECL|macro|IO_ERROR
macro_line|#undef IO_ERROR
DECL|macro|REDIRECT_SECTOR
macro_line|#undef REDIRECT_SECTOR
DECL|macro|INVALID_LEVEL
mdefine_line|#define INVALID_LEVEL KERN_WARNING &bslash;&n;&quot;multipath: md%d: raid level not set to multipath IO (%d)&bslash;n&quot;
DECL|macro|NO_SB
mdefine_line|#define NO_SB KERN_ERR &bslash;&n;&quot;multipath: disabled IO path %s (couldn&squot;t access raid superblock)&bslash;n&quot;
DECL|macro|ERRORS
mdefine_line|#define ERRORS KERN_ERR &bslash;&n;&quot;multipath: disabled IO path %s (errors detected)&bslash;n&quot;
DECL|macro|NOT_IN_SYNC
mdefine_line|#define NOT_IN_SYNC KERN_ERR &bslash;&n;&quot;multipath: making IO path %s a spare path (not in sync)&bslash;n&quot;
DECL|macro|INCONSISTENT
mdefine_line|#define INCONSISTENT KERN_ERR &bslash;&n;&quot;multipath: disabled IO path %s (inconsistent descriptor)&bslash;n&quot;
DECL|macro|ALREADY_RUNNING
mdefine_line|#define ALREADY_RUNNING KERN_ERR &bslash;&n;&quot;multipath: disabled IO path %s (multipath %d already operational)&bslash;n&quot;
DECL|macro|OPERATIONAL
mdefine_line|#define OPERATIONAL KERN_INFO &bslash;&n;&quot;multipath: device %s operational as IO path %d&bslash;n&quot;
DECL|macro|MEM_ERROR
mdefine_line|#define MEM_ERROR KERN_ERR &bslash;&n;&quot;multipath: couldn&squot;t allocate memory for md%d&bslash;n&quot;
DECL|macro|SPARE
mdefine_line|#define SPARE KERN_INFO &bslash;&n;&quot;multipath: spare IO path %s&bslash;n&quot;
DECL|macro|NONE_OPERATIONAL
mdefine_line|#define NONE_OPERATIONAL KERN_ERR &bslash;&n;&quot;multipath: no operational IO paths for md%d&bslash;n&quot;
DECL|macro|SB_DIFFERENCES
mdefine_line|#define SB_DIFFERENCES KERN_ERR &bslash;&n;&quot;multipath: detected IO path differences!&bslash;n&quot;
DECL|macro|ARRAY_IS_ACTIVE
mdefine_line|#define ARRAY_IS_ACTIVE KERN_INFO &bslash;&n;&quot;multipath: array md%d active with %d out of %d IO paths (%d spare IO paths)&bslash;n&quot;
DECL|macro|THREAD_ERROR
mdefine_line|#define THREAD_ERROR KERN_ERR &bslash;&n;&quot;multipath: couldn&squot;t allocate thread for md%d&bslash;n&quot;
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
id|i
comma
id|j
comma
id|disk_idx
suffix:semicolon
r_struct
id|multipath_info
op_star
id|disk
suffix:semicolon
id|mdp_super_t
op_star
id|sb
op_assign
id|mddev-&gt;sb
suffix:semicolon
id|mdp_disk_t
op_star
id|desc
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
r_int
id|num_rdevs
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;level
op_ne
id|LEVEL_MULTIPATH
)paren
(brace
id|printk
c_func
(paren
id|INVALID_LEVEL
comma
id|mdidx
c_func
(paren
id|mddev
)paren
comma
id|sb-&gt;level
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
id|MEM_ERROR
comma
id|mdidx
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
r_if
c_cond
(paren
id|rdev-&gt;faulty
)paren
(brace
multiline_comment|/* this is a &quot;should never happen&quot; case and if it */
multiline_comment|/* ever does happen, a continue; won&squot;t help */
id|printk
c_func
(paren
id|ERRORS
comma
id|bdev_partition_name
c_func
(paren
id|rdev-&gt;bdev
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* this is a &quot;should never happen&quot; case and if it */
multiline_comment|/* ever does happen, a continue; won&squot;t help */
r_if
c_cond
(paren
op_logical_neg
id|rdev-&gt;sb
)paren
(brace
id|MD_BUG
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rdev-&gt;desc_nr
op_eq
op_minus
l_int|1
)paren
(brace
id|MD_BUG
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|desc
op_assign
op_amp
id|sb-&gt;disks
(braket
id|rdev-&gt;desc_nr
)braket
suffix:semicolon
id|disk_idx
op_assign
id|desc-&gt;raid_disk
suffix:semicolon
id|disk
op_assign
id|conf-&gt;multipaths
op_plus
id|disk_idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk_sync
c_func
(paren
id|desc
)paren
)paren
id|printk
c_func
(paren
id|NOT_IN_SYNC
comma
id|bdev_partition_name
c_func
(paren
id|rdev-&gt;bdev
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Mark all disks as active to start with, there are no&n;&t;&t; * spares.  multipath_read_balance deals with choose&n;&t;&t; * the &quot;best&quot; operational device.&n;&t;&t; */
id|disk-&gt;number
op_assign
id|desc-&gt;number
suffix:semicolon
id|disk-&gt;raid_disk
op_assign
id|desc-&gt;raid_disk
suffix:semicolon
id|disk-&gt;bdev
op_assign
id|rdev-&gt;bdev
suffix:semicolon
id|disk-&gt;operational
op_assign
l_int|1
suffix:semicolon
id|disk-&gt;used_slot
op_assign
l_int|1
suffix:semicolon
id|mark_disk_sync
c_func
(paren
id|desc
)paren
suffix:semicolon
id|mark_disk_active
c_func
(paren
id|desc
)paren
suffix:semicolon
id|num_rdevs
op_increment
suffix:semicolon
)brace
id|conf-&gt;raid_disks
op_assign
id|sb-&gt;raid_disks
op_assign
id|sb-&gt;active_disks
op_assign
id|num_rdevs
suffix:semicolon
id|conf-&gt;nr_disks
op_assign
id|sb-&gt;nr_disks
op_assign
id|sb-&gt;working_disks
op_assign
id|num_rdevs
suffix:semicolon
id|sb-&gt;failed_disks
op_assign
l_int|0
suffix:semicolon
id|sb-&gt;spare_disks
op_assign
l_int|0
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
id|NONE_OPERATIONAL
comma
id|mdidx
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
id|MEM_ERROR
comma
id|mdidx
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
r_const
r_char
op_star
id|name
op_assign
l_string|&quot;multipathd&quot;
suffix:semicolon
id|conf-&gt;thread
op_assign
id|md_register_thread
c_func
(paren
id|multipathd
comma
id|conf
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conf-&gt;thread
)paren
(brace
id|printk
c_func
(paren
id|THREAD_ERROR
comma
id|mdidx
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
multiline_comment|/*&n;&t; * Regenerate the &quot;device is in sync with the raid set&quot; bit for&n;&t; * each device.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MD_SB_DISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mark_disk_nonsync
c_func
(paren
id|sb-&gt;disks
op_plus
id|i
)paren
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
id|sb-&gt;raid_disks
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;disks
(braket
id|i
)braket
dot
id|number
op_eq
id|conf-&gt;multipaths
(braket
id|j
)braket
dot
id|number
)paren
id|mark_disk_sync
c_func
(paren
id|sb-&gt;disks
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|ARRAY_IS_ACTIVE
comma
id|mdidx
c_func
(paren
id|mddev
)paren
comma
id|sb-&gt;active_disks
comma
id|sb-&gt;raid_disks
comma
id|sb-&gt;spare_disks
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, everything is just fine now&n;&t; */
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|macro|INVALID_LEVEL
macro_line|#undef INVALID_LEVEL
DECL|macro|NO_SB
macro_line|#undef NO_SB
DECL|macro|ERRORS
macro_line|#undef ERRORS
DECL|macro|NOT_IN_SYNC
macro_line|#undef NOT_IN_SYNC
DECL|macro|INCONSISTENT
macro_line|#undef INCONSISTENT
DECL|macro|ALREADY_RUNNING
macro_line|#undef ALREADY_RUNNING
DECL|macro|OPERATIONAL
macro_line|#undef OPERATIONAL
DECL|macro|SPARE
macro_line|#undef SPARE
DECL|macro|NONE_OPERATIONAL
macro_line|#undef NONE_OPERATIONAL
DECL|macro|SB_DIFFERENCES
macro_line|#undef SB_DIFFERENCES
DECL|macro|ARRAY_IS_ACTIVE
macro_line|#undef ARRAY_IS_ACTIVE
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
id|conf-&gt;thread
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
id|conf
)paren
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
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
id|name
suffix:colon
l_string|&quot;multipath&quot;
comma
id|make_request
suffix:colon
id|multipath_make_request
comma
id|run
suffix:colon
id|multipath_run
comma
id|stop
suffix:colon
id|multipath_stop
comma
id|status
suffix:colon
id|multipath_status
comma
id|error_handler
suffix:colon
id|multipath_error
comma
id|hot_add_disk
suffix:colon
id|multipath_add_disk
comma
id|hot_remove_disk
suffix:colon
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
eof
