multiline_comment|/*&n;   ataraid.c  Copyright (C) 2001 Red Hat, Inc. All rights reserved.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;   &n;   Authors: &t;Arjan van de Ven &lt;arjanv@redhat.com&gt;&n;   &t;&t;&n;   &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ataraid.h&quot;
DECL|variable|ataraid_hardsect_size
r_static
r_int
id|ataraid_hardsect_size
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|ataraid_blksize_size
r_static
r_int
id|ataraid_blksize_size
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|ataraid_ops
r_static
r_struct
id|raid_device_operations
op_star
id|ataraid_ops
(braket
l_int|16
)braket
suffix:semicolon
r_static
r_int
id|ataraid_ioctl
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
suffix:semicolon
r_static
r_int
id|ataraid_open
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
suffix:semicolon
r_static
r_int
id|ataraid_release
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
suffix:semicolon
r_static
r_void
id|ataraid_split_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|variable|ataraid_gendisk
r_struct
id|gendisk
id|ataraid_gendisk
suffix:semicolon
DECL|variable|ataraid_gendisk_sizes
r_static
r_int
id|ataraid_gendisk_sizes
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|ataraid_readahead
r_static
r_int
id|ataraid_readahead
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|ataraid_fops
r_static
r_struct
id|block_device_operations
id|ataraid_fops
op_assign
(brace
id|open
suffix:colon
id|ataraid_open
comma
id|release
suffix:colon
id|ataraid_release
comma
id|ioctl
suffix:colon
id|ataraid_ioctl
comma
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|ataraid_sem
)paren
suffix:semicolon
multiline_comment|/* Bitmap for the devices currently in use */
DECL|variable|ataraiduse
r_static
r_int
r_int
id|ataraiduse
suffix:semicolon
multiline_comment|/* structure for the splitting of bufferheads */
DECL|struct|ataraid_bh_private
r_struct
id|ataraid_bh_private
(brace
DECL|member|parent
r_struct
id|buffer_head
op_star
id|parent
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* stub fops functions */
DECL|function|ataraid_ioctl
r_static
r_int
id|ataraid_ioctl
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
id|minor
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
id|SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ataraid_ops
(braket
id|minor
)braket
)paren
op_logical_and
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|ioctl
)paren
)paren
r_return
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|ioctl
)paren
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ataraid_open
r_static
r_int
id|ataraid_open
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
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
id|SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ataraid_ops
(braket
id|minor
)braket
)paren
op_logical_and
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|open
)paren
)paren
r_return
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|open
)paren
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ataraid_release
r_static
r_int
id|ataraid_release
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
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
id|SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ataraid_ops
(braket
id|minor
)braket
)paren
op_logical_and
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|release
)paren
)paren
r_return
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|release
)paren
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ataraid_make_request
r_static
r_int
id|ataraid_make_request
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|minor
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|bh-&gt;b_rdev
)paren
op_rshift
id|SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ataraid_ops
(braket
id|minor
)braket
)paren
op_logical_and
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|make_request
)paren
)paren
(brace
id|retval
op_assign
(paren
id|ataraid_ops
(braket
id|minor
)braket
op_member_access_from_pointer
id|make_request
)paren
(paren
id|q
comma
id|rw
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
op_minus
l_int|1
)paren
(brace
id|ataraid_split_request
c_func
(paren
id|q
comma
id|rw
comma
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|retval
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|get_bhead
r_static
r_struct
id|buffer_head
op_star
id|get_bhead
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|ptr
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ptr
)paren
(brace
id|ptr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|buffer_head
)paren
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|get_private
r_static
r_struct
id|ataraid_bh_private
op_star
id|get_private
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|ptr
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ptr
)paren
(brace
id|ptr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ataraid_bh_private
)paren
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|ataraid_end_request
r_static
r_void
id|ataraid_end_request
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
r_struct
id|ataraid_bh_private
op_star
r_private
op_assign
id|bh-&gt;b_private
suffix:semicolon
r_if
c_cond
(paren
r_private
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|count
)paren
)paren
(brace
r_private
op_member_access_from_pointer
id|parent
op_member_access_from_pointer
id|b_end_io
c_func
(paren
r_private
op_member_access_from_pointer
id|parent
comma
id|uptodate
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|parent
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
r_private
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|ataraid_split_request
r_static
r_void
id|ataraid_split_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh1
comma
op_star
id|bh2
suffix:semicolon
r_struct
id|ataraid_bh_private
op_star
r_private
suffix:semicolon
id|bh1
op_assign
id|get_bhead
c_func
(paren
)paren
suffix:semicolon
id|bh2
op_assign
id|get_bhead
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If either of those ever fails we&squot;re doomed */
r_if
c_cond
(paren
(paren
op_logical_neg
id|bh1
)paren
op_logical_or
(paren
op_logical_neg
id|bh2
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_private
op_assign
id|get_private
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
r_private
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|bh1
comma
id|bh
comma
r_sizeof
(paren
op_star
id|bh
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|bh2
comma
id|bh
comma
r_sizeof
(paren
op_star
id|bh
)paren
)paren
suffix:semicolon
id|bh1-&gt;b_end_io
op_assign
id|ataraid_end_request
suffix:semicolon
id|bh2-&gt;b_end_io
op_assign
id|ataraid_end_request
suffix:semicolon
id|bh2-&gt;b_rsector
op_add_assign
id|bh-&gt;b_size
op_rshift
l_int|10
suffix:semicolon
id|bh1-&gt;b_size
op_div_assign
l_int|2
suffix:semicolon
id|bh2-&gt;b_size
op_div_assign
l_int|2
suffix:semicolon
r_private
op_member_access_from_pointer
id|parent
op_assign
id|bh
suffix:semicolon
id|bh1-&gt;b_private
op_assign
r_private
suffix:semicolon
id|bh2-&gt;b_private
op_assign
r_private
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|count
comma
l_int|2
)paren
suffix:semicolon
id|bh2-&gt;b_data
op_add_assign
id|bh-&gt;b_size
op_div
l_int|2
suffix:semicolon
id|generic_make_request
c_func
(paren
id|rw
comma
id|bh1
)paren
suffix:semicolon
id|generic_make_request
c_func
(paren
id|rw
comma
id|bh2
)paren
suffix:semicolon
)brace
multiline_comment|/* device register / release functions */
DECL|function|ataraid_get_device
r_int
id|ataraid_get_device
c_func
(paren
r_struct
id|raid_device_operations
op_star
id|fops
)paren
(brace
r_int
id|bit
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ataraid_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ataraiduse
op_eq
op_complement
l_int|0U
)paren
(brace
id|up
c_func
(paren
op_amp
id|ataraid_sem
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|bit
op_assign
id|ffz
c_func
(paren
id|ataraiduse
)paren
suffix:semicolon
id|ataraiduse
op_or_assign
l_int|1
op_lshift
id|bit
suffix:semicolon
id|ataraid_ops
(braket
id|bit
)braket
op_assign
id|fops
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ataraid_sem
)paren
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
DECL|function|ataraid_release_device
r_void
id|ataraid_release_device
c_func
(paren
r_int
id|device
)paren
(brace
id|down
c_func
(paren
op_amp
id|ataraid_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ataraiduse
op_amp
(paren
l_int|1
op_lshift
id|device
)paren
)paren
op_eq
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* device wasn&squot;t registered at all */
id|ataraiduse
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|device
)paren
suffix:semicolon
id|ataraid_ops
(braket
id|device
)braket
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ataraid_sem
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|ataraid_register_disk
r_void
id|ataraid_register_disk
c_func
(paren
r_int
id|device
comma
r_int
id|size
)paren
(brace
id|register_disk
c_func
(paren
op_amp
id|ataraid_gendisk
comma
id|MKDEV
c_func
(paren
id|ATAMAJOR
comma
l_int|16
op_star
id|device
)paren
comma
l_int|16
comma
op_amp
id|ataraid_fops
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|ataraid_init
r_static
id|__init
r_int
id|ataraid_init
c_func
(paren
r_void
)paren
(brace
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ataraid_hardsect_size
(braket
id|i
)braket
op_assign
l_int|512
suffix:semicolon
id|ataraid_blksize_size
(braket
id|i
)braket
op_assign
l_int|1024
suffix:semicolon
id|ataraid_readahead
(braket
id|i
)braket
op_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
id|blksize_size
(braket
id|ATAMAJOR
)braket
op_eq
l_int|NULL
)paren
id|blksize_size
(braket
id|ATAMAJOR
)braket
op_assign
id|ataraid_blksize_size
suffix:semicolon
r_if
c_cond
(paren
id|hardsect_size
(braket
id|ATAMAJOR
)braket
op_eq
l_int|NULL
)paren
id|hardsect_size
(braket
id|ATAMAJOR
)braket
op_assign
id|ataraid_hardsect_size
suffix:semicolon
multiline_comment|/* setup the gendisk structure */
id|ataraid_gendisk.part
op_assign
id|kmalloc
c_func
(paren
l_int|256
op_star
r_sizeof
(paren
r_struct
id|hd_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ataraid_gendisk.part
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ataraid: Couldn&squot;t allocate memory, aborting &bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|ataraid_gendisk.part
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|256
op_star
r_sizeof
(paren
r_struct
id|hd_struct
)paren
)paren
suffix:semicolon
id|ataraid_gendisk.major
op_assign
id|ATAMAJOR
suffix:semicolon
id|ataraid_gendisk.major_name
op_assign
l_string|&quot;ataraid&quot;
suffix:semicolon
id|ataraid_gendisk.minor_shift
op_assign
l_int|4
suffix:semicolon
id|ataraid_gendisk.max_p
op_assign
l_int|15
suffix:semicolon
id|ataraid_gendisk.sizes
op_assign
op_amp
id|ataraid_gendisk_sizes
(braket
l_int|0
)braket
suffix:semicolon
id|ataraid_gendisk.nr_real
op_assign
l_int|16
suffix:semicolon
id|ataraid_gendisk.fops
op_assign
op_amp
id|ataraid_fops
suffix:semicolon
id|add_gendisk
c_func
(paren
op_amp
id|ataraid_gendisk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|ATAMAJOR
comma
l_string|&quot;ataraid&quot;
comma
op_amp
id|ataraid_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ataraid: Could not get major %d &bslash;n&quot;
comma
id|ATAMAJOR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|blk_queue_make_request
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|ATAMAJOR
)paren
comma
id|ataraid_make_request
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ataraid_exit
r_static
r_void
id|__exit
id|ataraid_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_blkdev
c_func
(paren
id|ATAMAJOR
comma
l_string|&quot;ataraid&quot;
)paren
suffix:semicolon
id|hardsect_size
(braket
id|ATAMAJOR
)braket
op_assign
l_int|NULL
suffix:semicolon
id|blk_size
(braket
id|ATAMAJOR
)braket
op_assign
l_int|NULL
suffix:semicolon
id|blksize_size
(braket
id|ATAMAJOR
)braket
op_assign
l_int|NULL
suffix:semicolon
id|max_readahead
(braket
id|ATAMAJOR
)braket
op_assign
l_int|NULL
suffix:semicolon
id|del_gendisk
c_func
(paren
op_amp
id|ataraid_gendisk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ataraid_gendisk.part
)paren
(brace
id|kfree
c_func
(paren
id|ataraid_gendisk.part
)paren
suffix:semicolon
id|ataraid_gendisk.part
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|ataraid_init
id|module_init
c_func
(paren
id|ataraid_init
)paren
suffix:semicolon
DECL|variable|ataraid_exit
id|module_exit
c_func
(paren
id|ataraid_exit
)paren
suffix:semicolon
DECL|variable|ataraid_get_device
id|EXPORT_SYMBOL
c_func
(paren
id|ataraid_get_device
)paren
suffix:semicolon
DECL|variable|ataraid_release_device
id|EXPORT_SYMBOL
c_func
(paren
id|ataraid_release_device
)paren
suffix:semicolon
DECL|variable|ataraid_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|ataraid_gendisk
)paren
suffix:semicolon
DECL|variable|ataraid_register_disk
id|EXPORT_SYMBOL
c_func
(paren
id|ataraid_register_disk
)paren
suffix:semicolon
eof
