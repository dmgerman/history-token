multiline_comment|/*&n; * Copyright (C) 2001 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|MAX_DEPTH
mdefine_line|#define MAX_DEPTH 16
DECL|macro|NODE_SIZE
mdefine_line|#define NODE_SIZE L1_CACHE_BYTES
DECL|macro|KEYS_PER_NODE
mdefine_line|#define KEYS_PER_NODE (NODE_SIZE / sizeof(sector_t))
DECL|macro|CHILDREN_PER_NODE
mdefine_line|#define CHILDREN_PER_NODE (KEYS_PER_NODE + 1)
DECL|struct|dm_table
r_struct
id|dm_table
(brace
DECL|member|holders
id|atomic_t
id|holders
suffix:semicolon
multiline_comment|/* btree table */
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
DECL|member|counts
r_int
r_int
id|counts
(braket
id|MAX_DEPTH
)braket
suffix:semicolon
multiline_comment|/* in nodes */
DECL|member|index
id|sector_t
op_star
id|index
(braket
id|MAX_DEPTH
)braket
suffix:semicolon
DECL|member|num_targets
r_int
r_int
id|num_targets
suffix:semicolon
DECL|member|num_allocated
r_int
r_int
id|num_allocated
suffix:semicolon
DECL|member|highs
id|sector_t
op_star
id|highs
suffix:semicolon
DECL|member|targets
r_struct
id|dm_target
op_star
id|targets
suffix:semicolon
multiline_comment|/*&n;&t; * Indicates the rw permissions for the new logical&n;&t; * device.  This should be a combination of FMODE_READ&n;&t; * and FMODE_WRITE.&n;&t; */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* a list of devices used by this table */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/*&n;&t; * These are optimistic limits taken from all the&n;&t; * targets, some targets will need smaller limits.&n;&t; */
DECL|member|limits
r_struct
id|io_restrictions
id|limits
suffix:semicolon
multiline_comment|/*&n;&t; * A waitqueue for processes waiting for something&n;&t; * interesting to happen to this table.&n;&t; */
DECL|member|eventq
id|wait_queue_head_t
id|eventq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Similar to ceiling(log_size(n))&n; */
DECL|function|int_log
r_static
r_int
r_int
id|int_log
c_func
(paren
r_int
r_int
id|n
comma
r_int
r_int
id|base
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|n
OG
l_int|1
)paren
(brace
id|n
op_assign
id|dm_div_up
c_func
(paren
id|n
comma
id|base
)paren
suffix:semicolon
id|result
op_increment
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the minimum that is _not_ zero, unless both are zero.&n; */
DECL|macro|min_not_zero
mdefine_line|#define min_not_zero(l, r) (l == 0) ? r : ((r == 0) ? l : min(l, r))
multiline_comment|/*&n; * Combine two io_restrictions, always taking the lower value.&n; */
DECL|function|combine_restrictions_low
r_static
r_void
id|combine_restrictions_low
c_func
(paren
r_struct
id|io_restrictions
op_star
id|lhs
comma
r_struct
id|io_restrictions
op_star
id|rhs
)paren
(brace
id|lhs-&gt;max_sectors
op_assign
id|min_not_zero
c_func
(paren
id|lhs-&gt;max_sectors
comma
id|rhs-&gt;max_sectors
)paren
suffix:semicolon
id|lhs-&gt;max_phys_segments
op_assign
id|min_not_zero
c_func
(paren
id|lhs-&gt;max_phys_segments
comma
id|rhs-&gt;max_phys_segments
)paren
suffix:semicolon
id|lhs-&gt;max_hw_segments
op_assign
id|min_not_zero
c_func
(paren
id|lhs-&gt;max_hw_segments
comma
id|rhs-&gt;max_hw_segments
)paren
suffix:semicolon
id|lhs-&gt;hardsect_size
op_assign
id|max
c_func
(paren
id|lhs-&gt;hardsect_size
comma
id|rhs-&gt;hardsect_size
)paren
suffix:semicolon
id|lhs-&gt;max_segment_size
op_assign
id|min_not_zero
c_func
(paren
id|lhs-&gt;max_segment_size
comma
id|rhs-&gt;max_segment_size
)paren
suffix:semicolon
id|lhs-&gt;seg_boundary_mask
op_assign
id|min_not_zero
c_func
(paren
id|lhs-&gt;seg_boundary_mask
comma
id|rhs-&gt;seg_boundary_mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate the index of the child node of the n&squot;th node k&squot;th key.&n; */
DECL|function|get_child
r_static
r_inline
r_int
r_int
id|get_child
c_func
(paren
r_int
r_int
id|n
comma
r_int
r_int
id|k
)paren
(brace
r_return
(paren
id|n
op_star
id|CHILDREN_PER_NODE
)paren
op_plus
id|k
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the n&squot;th node of level l from table t.&n; */
DECL|function|get_node
r_static
r_inline
id|sector_t
op_star
id|get_node
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_int
r_int
id|l
comma
r_int
r_int
id|n
)paren
(brace
r_return
id|t-&gt;index
(braket
id|l
)braket
op_plus
(paren
id|n
op_star
id|KEYS_PER_NODE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the highest key that you could lookup from the n&squot;th&n; * node on level l of the btree.&n; */
DECL|function|high
r_static
id|sector_t
id|high
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_int
r_int
id|l
comma
r_int
r_int
id|n
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|l
OL
id|t-&gt;depth
op_minus
l_int|1
suffix:semicolon
id|l
op_increment
)paren
id|n
op_assign
id|get_child
c_func
(paren
id|n
comma
id|CHILDREN_PER_NODE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|t-&gt;counts
(braket
id|l
)braket
)paren
r_return
(paren
id|sector_t
)paren
op_minus
l_int|1
suffix:semicolon
r_return
id|get_node
c_func
(paren
id|t
comma
id|l
comma
id|n
)paren
(braket
id|KEYS_PER_NODE
op_minus
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Fills in a level of the btree based on the highs of the level&n; * below it.&n; */
DECL|function|setup_btree_index
r_static
r_int
id|setup_btree_index
c_func
(paren
r_int
r_int
id|l
comma
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_int
r_int
id|n
comma
id|k
suffix:semicolon
id|sector_t
op_star
id|node
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0U
suffix:semicolon
id|n
OL
id|t-&gt;counts
(braket
id|l
)braket
suffix:semicolon
id|n
op_increment
)paren
(brace
id|node
op_assign
id|get_node
c_func
(paren
id|t
comma
id|l
comma
id|n
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0U
suffix:semicolon
id|k
OL
id|KEYS_PER_NODE
suffix:semicolon
id|k
op_increment
)paren
id|node
(braket
id|k
)braket
op_assign
id|high
c_func
(paren
id|t
comma
id|l
op_plus
l_int|1
comma
id|get_child
c_func
(paren
id|n
comma
id|k
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_vcalloc
r_static
r_void
op_star
id|dm_vcalloc
c_func
(paren
r_int
r_int
id|nmemb
comma
r_int
r_int
id|elem_size
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
multiline_comment|/*&n;&t; * Check that we&squot;re not going to overflow.&n;&t; */
r_if
c_cond
(paren
id|nmemb
OG
(paren
id|ULONG_MAX
op_div
id|elem_size
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|size
op_assign
id|nmemb
op_star
id|elem_size
suffix:semicolon
id|addr
op_assign
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|memset
c_func
(paren
id|addr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * highs, and targets are managed as dynamic arrays during a&n; * table load.&n; */
DECL|function|alloc_targets
r_static
r_int
id|alloc_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_int
r_int
id|num
)paren
(brace
id|sector_t
op_star
id|n_highs
suffix:semicolon
r_struct
id|dm_target
op_star
id|n_targets
suffix:semicolon
r_int
id|n
op_assign
id|t-&gt;num_targets
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate both the target array and offset array at once.&n;&t; */
id|n_highs
op_assign
(paren
id|sector_t
op_star
)paren
id|dm_vcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dm_target
)paren
op_plus
r_sizeof
(paren
id|sector_t
)paren
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n_highs
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|n_targets
op_assign
(paren
r_struct
id|dm_target
op_star
)paren
(paren
id|n_highs
op_plus
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
id|memcpy
c_func
(paren
id|n_highs
comma
id|t-&gt;highs
comma
r_sizeof
(paren
op_star
id|n_highs
)paren
op_star
id|n
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|n_targets
comma
id|t-&gt;targets
comma
r_sizeof
(paren
op_star
id|n_targets
)paren
op_star
id|n
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|n_highs
op_plus
id|n
comma
op_minus
l_int|1
comma
r_sizeof
(paren
op_star
id|n_highs
)paren
op_star
(paren
id|num
op_minus
id|n
)paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|t-&gt;highs
)paren
suffix:semicolon
id|t-&gt;num_allocated
op_assign
id|num
suffix:semicolon
id|t-&gt;highs
op_assign
id|n_highs
suffix:semicolon
id|t-&gt;targets
op_assign
id|n_targets
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_table_create
r_int
id|dm_table_create
c_func
(paren
r_struct
id|dm_table
op_star
op_star
id|result
comma
r_int
id|mode
)paren
(brace
r_struct
id|dm_table
op_star
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|t
)paren
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|t
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|t-&gt;devices
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|t-&gt;holders
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* allocate a single nodes worth of targets to begin with */
r_if
c_cond
(paren
id|alloc_targets
c_func
(paren
id|t
comma
id|KEYS_PER_NODE
)paren
)paren
(brace
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
id|t
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|t-&gt;eventq
)paren
suffix:semicolon
id|t-&gt;mode
op_assign
id|mode
suffix:semicolon
op_star
id|result
op_assign
id|t
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_devices
r_static
r_void
id|free_devices
c_func
(paren
r_struct
id|list_head
op_star
id|devices
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|devices-&gt;next
suffix:semicolon
id|tmp
op_ne
id|devices
suffix:semicolon
id|tmp
op_assign
id|next
)paren
(brace
r_struct
id|dm_dev
op_star
id|dd
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|dm_dev
comma
id|list
)paren
suffix:semicolon
id|next
op_assign
id|tmp-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|dd
)paren
suffix:semicolon
)brace
)brace
DECL|function|table_destroy
r_void
id|table_destroy
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|DMWARN
c_func
(paren
l_string|&quot;destroying table&quot;
)paren
suffix:semicolon
multiline_comment|/* destroying the table counts as an event */
id|dm_table_event
c_func
(paren
id|t
)paren
suffix:semicolon
multiline_comment|/* free the indexes (see dm_table_complete) */
r_if
c_cond
(paren
id|t-&gt;depth
op_ge
l_int|2
)paren
id|vfree
c_func
(paren
id|t-&gt;index
(braket
id|t-&gt;depth
op_minus
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* free the targets */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|t-&gt;num_targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dm_target
op_star
id|tgt
op_assign
id|t-&gt;targets
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|tgt-&gt;type-&gt;dtr
)paren
id|tgt-&gt;type
op_member_access_from_pointer
id|dtr
c_func
(paren
id|tgt
)paren
suffix:semicolon
id|dm_put_target_type
c_func
(paren
id|tgt-&gt;type
)paren
suffix:semicolon
)brace
id|vfree
c_func
(paren
id|t-&gt;highs
)paren
suffix:semicolon
multiline_comment|/* free the device list */
r_if
c_cond
(paren
id|t-&gt;devices.next
op_ne
op_amp
id|t-&gt;devices
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;devices still present during destroy: &quot;
l_string|&quot;dm_table_remove_device calls missing&quot;
)paren
suffix:semicolon
id|free_devices
c_func
(paren
op_amp
id|t-&gt;devices
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
DECL|function|dm_table_get
r_void
id|dm_table_get
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|t-&gt;holders
)paren
suffix:semicolon
)brace
DECL|function|dm_table_put
r_void
id|dm_table_put
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|t-&gt;holders
)paren
)paren
id|table_destroy
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Checks to see if we need to extend highs or targets.&n; */
DECL|function|check_space
r_static
r_inline
r_int
id|check_space
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;num_targets
op_ge
id|t-&gt;num_allocated
)paren
r_return
id|alloc_targets
c_func
(paren
id|t
comma
id|t-&gt;num_allocated
op_star
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert a device path to a dev_t.&n; */
DECL|function|lookup_device
r_static
r_int
id|lookup_device
c_func
(paren
r_const
r_char
op_star
id|path
comma
id|dev_t
op_star
id|dev
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|path_lookup
c_func
(paren
id|path
comma
id|LOOKUP_FOLLOW
comma
op_amp
id|nd
)paren
)paren
)paren
r_return
id|r
suffix:semicolon
id|inode
op_assign
id|nd.dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|r
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|r
op_assign
op_minus
id|ENOTBLK
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
op_star
id|dev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|out
suffix:colon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * See if we&squot;ve already got a device in the list.&n; */
DECL|function|find_device
r_static
r_struct
id|dm_dev
op_star
id|find_device
c_func
(paren
r_struct
id|list_head
op_star
id|l
comma
id|dev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
id|l
)paren
(brace
r_struct
id|dm_dev
op_star
id|dd
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|dm_dev
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dd-&gt;bdev-&gt;bd_dev
op_eq
id|dev
)paren
r_return
id|dd
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Open a device so we can use it as a map destination.&n; */
DECL|function|open_dev
r_static
r_int
id|open_dev
c_func
(paren
r_struct
id|dm_dev
op_star
id|d
comma
id|dev_t
id|dev
)paren
(brace
r_static
r_char
op_star
id|_claim_ptr
op_assign
l_string|&quot;I belong to device-mapper&quot;
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bdev
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|bdev
op_assign
id|open_by_devnum
c_func
(paren
id|dev
comma
id|d-&gt;mode
comma
id|BDEV_RAW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|bdev
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|r
op_assign
id|bd_claim
c_func
(paren
id|bdev
comma
id|_claim_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_RAW
)paren
suffix:semicolon
r_else
id|d-&gt;bdev
op_assign
id|bdev
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * Close a device that we&squot;ve been using.&n; */
DECL|function|close_dev
r_static
r_void
id|close_dev
c_func
(paren
r_struct
id|dm_dev
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;bdev
)paren
r_return
suffix:semicolon
id|bd_release
c_func
(paren
id|d-&gt;bdev
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|d-&gt;bdev
comma
id|BDEV_RAW
)paren
suffix:semicolon
id|d-&gt;bdev
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * If possible (ie. blk_size[major] is set), this checks an area&n; * of a destination device is valid.&n; */
DECL|function|check_device_area
r_static
r_int
id|check_device_area
c_func
(paren
r_struct
id|dm_dev
op_star
id|dd
comma
id|sector_t
id|start
comma
id|sector_t
id|len
)paren
(brace
id|sector_t
id|dev_size
suffix:semicolon
id|dev_size
op_assign
id|dd-&gt;bdev-&gt;bd_inode-&gt;i_size
op_rshift
id|SECTOR_SHIFT
suffix:semicolon
r_return
(paren
(paren
id|start
OL
id|dev_size
)paren
op_logical_and
(paren
id|len
op_le
(paren
id|dev_size
op_minus
id|start
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This upgrades the mode on an already open dm_dev.  Being&n; * careful to leave things as they were if we fail to reopen the&n; * device.&n; */
DECL|function|upgrade_mode
r_static
r_int
id|upgrade_mode
c_func
(paren
r_struct
id|dm_dev
op_star
id|dd
comma
r_int
id|new_mode
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|dm_dev
id|dd_copy
suffix:semicolon
id|dev_t
id|dev
op_assign
id|dd-&gt;bdev-&gt;bd_dev
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dd_copy
comma
id|dd
comma
r_sizeof
(paren
id|dd_copy
)paren
)paren
suffix:semicolon
id|dd-&gt;mode
op_or_assign
id|new_mode
suffix:semicolon
id|dd-&gt;bdev
op_assign
l_int|NULL
suffix:semicolon
id|r
op_assign
id|open_dev
c_func
(paren
id|dd
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
id|close_dev
c_func
(paren
op_amp
id|dd_copy
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|dd
comma
op_amp
id|dd_copy
comma
r_sizeof
(paren
id|dd_copy
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a device to the list, or just increment the usage count if&n; * it&squot;s already present.&n; */
DECL|function|__table_get_device
r_static
r_int
id|__table_get_device
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_struct
id|dm_target
op_star
id|ti
comma
r_const
r_char
op_star
id|path
comma
id|sector_t
id|start
comma
id|sector_t
id|len
comma
r_int
id|mode
comma
r_struct
id|dm_dev
op_star
op_star
id|result
)paren
(brace
r_int
id|r
suffix:semicolon
id|dev_t
id|dev
suffix:semicolon
r_struct
id|dm_dev
op_star
id|dd
suffix:semicolon
r_int
id|major
comma
id|minor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|path
comma
l_string|&quot;%x:%x&quot;
comma
op_amp
id|major
comma
op_amp
id|minor
)paren
op_eq
l_int|2
)paren
(brace
multiline_comment|/* Extract the major/minor numbers */
id|dev
op_assign
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* convert the path to a device */
r_if
c_cond
(paren
(paren
id|r
op_assign
id|lookup_device
c_func
(paren
id|path
comma
op_amp
id|dev
)paren
)paren
)paren
r_return
id|r
suffix:semicolon
)brace
id|dd
op_assign
id|find_device
c_func
(paren
op_amp
id|t-&gt;devices
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dd
)paren
(brace
id|dd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dd-&gt;mode
op_assign
id|mode
suffix:semicolon
id|dd-&gt;bdev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|open_dev
c_func
(paren
id|dd
comma
id|dev
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|dd
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|dd-&gt;count
comma
l_int|0
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dd-&gt;list
comma
op_amp
id|t-&gt;devices
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dd-&gt;mode
op_ne
(paren
id|mode
op_or
id|dd-&gt;mode
)paren
)paren
(brace
id|r
op_assign
id|upgrade_mode
c_func
(paren
id|dd
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|dd-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_device_area
c_func
(paren
id|dd
comma
id|start
comma
id|len
)paren
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;device %s too small for target&quot;
comma
id|path
)paren
suffix:semicolon
id|dm_put_device
c_func
(paren
id|ti
comma
id|dd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|result
op_assign
id|dd
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_get_device
r_int
id|dm_get_device
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_const
r_char
op_star
id|path
comma
id|sector_t
id|start
comma
id|sector_t
id|len
comma
r_int
id|mode
comma
r_struct
id|dm_dev
op_star
op_star
id|result
)paren
(brace
r_int
id|r
op_assign
id|__table_get_device
c_func
(paren
id|ti-&gt;table
comma
id|ti
comma
id|path
comma
id|start
comma
id|len
comma
id|mode
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
id|request_queue_t
op_star
id|q
op_assign
id|bdev_get_queue
c_func
(paren
(paren
op_star
id|result
)paren
op_member_access_from_pointer
id|bdev
)paren
suffix:semicolon
r_struct
id|io_restrictions
op_star
id|rs
op_assign
op_amp
id|ti-&gt;limits
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Combine the device limits low.&n;&t;&t; *&n;&t;&t; * FIXME: if we move an io_restriction struct&n;&t;&t; *        into q this would just be a call to&n;&t;&t; *        combine_restrictions_low()&n;&t;&t; */
id|rs-&gt;max_sectors
op_assign
id|min_not_zero
c_func
(paren
id|rs-&gt;max_sectors
comma
id|q-&gt;max_sectors
)paren
suffix:semicolon
id|rs-&gt;max_phys_segments
op_assign
id|min_not_zero
c_func
(paren
id|rs-&gt;max_phys_segments
comma
id|q-&gt;max_phys_segments
)paren
suffix:semicolon
id|rs-&gt;max_hw_segments
op_assign
id|min_not_zero
c_func
(paren
id|rs-&gt;max_hw_segments
comma
id|q-&gt;max_hw_segments
)paren
suffix:semicolon
id|rs-&gt;hardsect_size
op_assign
id|max
c_func
(paren
id|rs-&gt;hardsect_size
comma
id|q-&gt;hardsect_size
)paren
suffix:semicolon
id|rs-&gt;max_segment_size
op_assign
id|min_not_zero
c_func
(paren
id|rs-&gt;max_segment_size
comma
id|q-&gt;max_segment_size
)paren
suffix:semicolon
id|rs-&gt;seg_boundary_mask
op_assign
id|min_not_zero
c_func
(paren
id|rs-&gt;seg_boundary_mask
comma
id|q-&gt;seg_boundary_mask
)paren
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrement a devices use count and remove it if necessary.&n; */
DECL|function|dm_put_device
r_void
id|dm_put_device
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|dm_dev
op_star
id|dd
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|dd-&gt;count
)paren
)paren
(brace
id|close_dev
c_func
(paren
id|dd
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dd-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dd
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Checks to see if the target joins onto the end of the table.&n; */
DECL|function|adjoin
r_static
r_int
id|adjoin
c_func
(paren
r_struct
id|dm_table
op_star
id|table
comma
r_struct
id|dm_target
op_star
id|ti
)paren
(brace
r_struct
id|dm_target
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table-&gt;num_targets
)paren
r_return
op_logical_neg
id|ti-&gt;begin
suffix:semicolon
id|prev
op_assign
op_amp
id|table-&gt;targets
(braket
id|table-&gt;num_targets
op_minus
l_int|1
)braket
suffix:semicolon
r_return
(paren
id|ti-&gt;begin
op_eq
(paren
id|prev-&gt;begin
op_plus
id|prev-&gt;len
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Destructively splits up the argument list to pass to ctr.&n; */
DECL|function|split_args
r_static
r_int
id|split_args
c_func
(paren
r_int
id|max
comma
r_int
op_star
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
id|input
)paren
(brace
r_char
op_star
id|start
comma
op_star
id|end
op_assign
id|input
comma
op_star
id|out
suffix:semicolon
op_star
id|argc
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|start
op_assign
id|end
suffix:semicolon
multiline_comment|/* Skip whitespace */
r_while
c_loop
(paren
op_star
id|start
op_logical_and
id|isspace
c_func
(paren
op_star
id|start
)paren
)paren
id|start
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|start
)paren
r_break
suffix:semicolon
multiline_comment|/* success, we hit the end */
multiline_comment|/* &squot;out&squot; is used to remove any back-quotes */
id|end
op_assign
id|out
op_assign
id|start
suffix:semicolon
r_while
c_loop
(paren
op_star
id|end
)paren
(brace
multiline_comment|/* Everything apart from &squot;&bslash;0&squot; can be quoted */
r_if
c_cond
(paren
op_star
id|end
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
op_star
(paren
id|end
op_plus
l_int|1
)paren
)paren
(brace
op_star
id|out
op_increment
op_assign
op_star
(paren
id|end
op_plus
l_int|1
)paren
suffix:semicolon
id|end
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isspace
c_func
(paren
op_star
id|end
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* end of token */
op_star
id|out
op_increment
op_assign
op_star
id|end
op_increment
suffix:semicolon
)brace
multiline_comment|/* have we already filled the array ? */
r_if
c_cond
(paren
(paren
op_star
id|argc
op_plus
l_int|1
)paren
OG
id|max
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* we know this is whitespace */
r_if
c_cond
(paren
op_star
id|end
)paren
id|end
op_increment
suffix:semicolon
multiline_comment|/* terminate the string and put it in the array */
op_star
id|out
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|argv
(braket
op_star
id|argc
)braket
op_assign
id|start
suffix:semicolon
(paren
op_star
id|argc
)paren
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_table_add_target
r_int
id|dm_table_add_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_const
r_char
op_star
id|type
comma
id|sector_t
id|start
comma
id|sector_t
id|len
comma
r_char
op_star
id|params
)paren
(brace
r_int
id|r
op_assign
op_minus
id|EINVAL
comma
id|argc
suffix:semicolon
r_char
op_star
id|argv
(braket
l_int|32
)braket
suffix:semicolon
r_struct
id|dm_target
op_star
id|tgt
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|check_space
c_func
(paren
id|t
)paren
)paren
)paren
r_return
id|r
suffix:semicolon
id|tgt
op_assign
id|t-&gt;targets
op_plus
id|t-&gt;num_targets
suffix:semicolon
id|memset
c_func
(paren
id|tgt
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tgt
)paren
)paren
suffix:semicolon
id|tgt-&gt;type
op_assign
id|dm_get_target_type
c_func
(paren
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tgt-&gt;type
)paren
(brace
id|tgt-&gt;error
op_assign
l_string|&quot;unknown target type&quot;
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tgt-&gt;table
op_assign
id|t
suffix:semicolon
id|tgt-&gt;begin
op_assign
id|start
suffix:semicolon
id|tgt-&gt;len
op_assign
id|len
suffix:semicolon
id|tgt-&gt;error
op_assign
l_string|&quot;Unknown error&quot;
suffix:semicolon
multiline_comment|/*&n;&t; * Does this target adjoin the previous one ?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|adjoin
c_func
(paren
id|t
comma
id|tgt
)paren
)paren
(brace
id|tgt-&gt;error
op_assign
l_string|&quot;Gap in table&quot;
suffix:semicolon
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|r
op_assign
id|split_args
c_func
(paren
id|ARRAY_SIZE
c_func
(paren
id|argv
)paren
comma
op_amp
id|argc
comma
id|argv
comma
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|tgt-&gt;error
op_assign
l_string|&quot;couldn&squot;t split parameters&quot;
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|r
op_assign
id|tgt-&gt;type
op_member_access_from_pointer
id|ctr
c_func
(paren
id|tgt
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_goto
id|bad
suffix:semicolon
id|t-&gt;highs
(braket
id|t-&gt;num_targets
op_increment
)braket
op_assign
id|tgt-&gt;begin
op_plus
id|tgt-&gt;len
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* FIXME: the plan is to combine high here and then have&n;&t; * the merge fn apply the target level restrictions. */
id|combine_restrictions_low
c_func
(paren
op_amp
id|t-&gt;limits
comma
op_amp
id|tgt-&gt;limits
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
id|DM_NAME
l_string|&quot;: %s&bslash;n&quot;
comma
id|tgt-&gt;error
)paren
suffix:semicolon
id|dm_put_target_type
c_func
(paren
id|tgt-&gt;type
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|setup_indexes
r_static
r_int
id|setup_indexes
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
id|sector_t
op_star
id|indexes
suffix:semicolon
multiline_comment|/* allocate the space for *all* the indexes */
r_for
c_loop
(paren
id|i
op_assign
id|t-&gt;depth
op_minus
l_int|2
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|t-&gt;counts
(braket
id|i
)braket
op_assign
id|dm_div_up
c_func
(paren
id|t-&gt;counts
(braket
id|i
op_plus
l_int|1
)braket
comma
id|CHILDREN_PER_NODE
)paren
suffix:semicolon
id|total
op_add_assign
id|t-&gt;counts
(braket
id|i
)braket
suffix:semicolon
)brace
id|indexes
op_assign
(paren
id|sector_t
op_star
)paren
id|dm_vcalloc
c_func
(paren
id|total
comma
(paren
r_int
r_int
)paren
id|NODE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|indexes
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* set up internal nodes, bottom-up */
r_for
c_loop
(paren
id|i
op_assign
id|t-&gt;depth
op_minus
l_int|2
comma
id|total
op_assign
l_int|0
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|t-&gt;index
(braket
id|i
)braket
op_assign
id|indexes
suffix:semicolon
id|indexes
op_add_assign
(paren
id|KEYS_PER_NODE
op_star
id|t-&gt;counts
(braket
id|i
)braket
)paren
suffix:semicolon
id|setup_btree_index
c_func
(paren
id|i
comma
id|t
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Builds the btree to index the map.&n; */
DECL|function|dm_table_complete
r_int
id|dm_table_complete
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|leaf_nodes
suffix:semicolon
multiline_comment|/* how many indexes will the btree have ? */
id|leaf_nodes
op_assign
id|dm_div_up
c_func
(paren
id|t-&gt;num_targets
comma
id|KEYS_PER_NODE
)paren
suffix:semicolon
id|t-&gt;depth
op_assign
l_int|1
op_plus
id|int_log
c_func
(paren
id|leaf_nodes
comma
id|CHILDREN_PER_NODE
)paren
suffix:semicolon
multiline_comment|/* leaf layer has already been set up */
id|t-&gt;counts
(braket
id|t-&gt;depth
op_minus
l_int|1
)braket
op_assign
id|leaf_nodes
suffix:semicolon
id|t-&gt;index
(braket
id|t-&gt;depth
op_minus
l_int|1
)braket
op_assign
id|t-&gt;highs
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;depth
op_ge
l_int|2
)paren
id|r
op_assign
id|setup_indexes
c_func
(paren
id|t
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_table_event
r_void
id|dm_table_event
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|t-&gt;eventq
)paren
suffix:semicolon
)brace
DECL|function|dm_table_get_size
id|sector_t
id|dm_table_get_size
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_return
id|t-&gt;num_targets
ques
c_cond
(paren
id|t-&gt;highs
(braket
id|t-&gt;num_targets
op_minus
l_int|1
)braket
op_plus
l_int|1
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|dm_table_get_target
r_struct
id|dm_target
op_star
id|dm_table_get_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_int
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|index
OG
id|t-&gt;num_targets
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|t-&gt;targets
op_plus
id|index
suffix:semicolon
)brace
multiline_comment|/*&n; * Search the btree for the correct target.&n; */
DECL|function|dm_table_find_target
r_struct
id|dm_target
op_star
id|dm_table_find_target
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
id|sector_t
id|sector
)paren
(brace
r_int
r_int
id|l
comma
id|n
op_assign
l_int|0
comma
id|k
op_assign
l_int|0
suffix:semicolon
id|sector_t
op_star
id|node
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
id|l
OL
id|t-&gt;depth
suffix:semicolon
id|l
op_increment
)paren
(brace
id|n
op_assign
id|get_child
c_func
(paren
id|n
comma
id|k
)paren
suffix:semicolon
id|node
op_assign
id|get_node
c_func
(paren
id|t
comma
id|l
comma
id|n
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|KEYS_PER_NODE
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|node
(braket
id|k
)braket
op_ge
id|sector
)paren
r_break
suffix:semicolon
)brace
r_return
op_amp
id|t-&gt;targets
(braket
(paren
id|KEYS_PER_NODE
op_star
id|n
)paren
op_plus
id|k
)braket
suffix:semicolon
)brace
DECL|function|dm_table_set_restrictions
r_void
id|dm_table_set_restrictions
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
r_struct
id|request_queue
op_star
id|q
)paren
(brace
multiline_comment|/*&n;&t; * Make sure we obey the optimistic sub devices&n;&t; * restrictions.&n;&t; */
id|q-&gt;max_sectors
op_assign
id|t-&gt;limits.max_sectors
suffix:semicolon
id|q-&gt;max_phys_segments
op_assign
id|t-&gt;limits.max_phys_segments
suffix:semicolon
id|q-&gt;max_hw_segments
op_assign
id|t-&gt;limits.max_hw_segments
suffix:semicolon
id|q-&gt;hardsect_size
op_assign
id|t-&gt;limits.hardsect_size
suffix:semicolon
id|q-&gt;max_segment_size
op_assign
id|t-&gt;limits.max_segment_size
suffix:semicolon
id|q-&gt;seg_boundary_mask
op_assign
id|t-&gt;limits.seg_boundary_mask
suffix:semicolon
)brace
DECL|function|dm_table_get_num_targets
r_int
r_int
id|dm_table_get_num_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_return
id|t-&gt;num_targets
suffix:semicolon
)brace
DECL|function|dm_table_get_devices
r_struct
id|list_head
op_star
id|dm_table_get_devices
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_return
op_amp
id|t-&gt;devices
suffix:semicolon
)brace
DECL|function|dm_table_get_mode
r_int
id|dm_table_get_mode
c_func
(paren
r_struct
id|dm_table
op_star
id|t
)paren
(brace
r_return
id|t-&gt;mode
suffix:semicolon
)brace
DECL|function|dm_table_add_wait_queue
r_void
id|dm_table_add_wait_queue
c_func
(paren
r_struct
id|dm_table
op_star
id|t
comma
id|wait_queue_t
op_star
id|wq
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|t-&gt;eventq
comma
id|wq
)paren
suffix:semicolon
)brace
DECL|function|dm_table_suspend_targets
r_void
id|dm_table_suspend_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
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
id|t-&gt;num_targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dm_target
op_star
id|ti
op_assign
id|t-&gt;targets
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ti-&gt;type-&gt;suspend
)paren
id|ti-&gt;type
op_member_access_from_pointer
id|suspend
c_func
(paren
id|ti
)paren
suffix:semicolon
)brace
)brace
DECL|function|dm_table_resume_targets
r_void
id|dm_table_resume_targets
c_func
(paren
r_struct
id|dm_table
op_star
id|t
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
id|t-&gt;num_targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dm_target
op_star
id|ti
op_assign
id|t-&gt;targets
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ti-&gt;type-&gt;resume
)paren
id|ti-&gt;type
op_member_access_from_pointer
id|resume
c_func
(paren
id|ti
)paren
suffix:semicolon
)brace
)brace
DECL|variable|dm_get_device
id|EXPORT_SYMBOL
c_func
(paren
id|dm_get_device
)paren
suffix:semicolon
DECL|variable|dm_put_device
id|EXPORT_SYMBOL
c_func
(paren
id|dm_put_device
)paren
suffix:semicolon
DECL|variable|dm_table_event
id|EXPORT_SYMBOL
c_func
(paren
id|dm_table_event
)paren
suffix:semicolon
DECL|variable|dm_table_get_mode
id|EXPORT_SYMBOL
c_func
(paren
id|dm_table_get_mode
)paren
suffix:semicolon
eof
