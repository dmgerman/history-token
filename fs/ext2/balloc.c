multiline_comment|/*&n; *  linux/fs/ext2/balloc.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  Enhanced block allocation by Stephen Tweedie (sct@dcs.ed.ac.uk), 1993&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
multiline_comment|/*&n; * balloc.c contains the blocks allocation and deallocation routines&n; */
multiline_comment|/*&n; * The free blocks are managed by bitmaps.  A file system contains several&n; * blocks groups.  Each group contains 1 bitmap block for blocks, 1 bitmap&n; * block for inodes, N blocks for the inode table and data blocks.&n; *&n; * The file system contains group descriptors which are located after the&n; * super block.  Each descriptor contains the number of the bitmap block and&n; * the free blocks count in the block.  The descriptors are loaded in memory&n; * when a file system is mounted (see ext2_read_super).&n; */
DECL|macro|in_range
mdefine_line|#define in_range(b, first, len)&t;((b) &gt;= (first) &amp;&amp; (b) &lt;= (first) + (len) - 1)
DECL|function|ext2_get_group_desc
r_struct
id|ext2_group_desc
op_star
id|ext2_get_group_desc
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_int
r_int
id|group_desc
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_struct
id|ext2_sb_info
op_star
id|sbi
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block_group
op_ge
id|sbi-&gt;s_groups_count
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_get_group_desc&quot;
comma
l_string|&quot;block_group &gt;= groups_count - &quot;
l_string|&quot;block_group = %d, groups_count = %lu&quot;
comma
id|block_group
comma
id|sbi-&gt;s_groups_count
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|group_desc
op_assign
id|block_group
op_div
id|EXT2_DESC_PER_BLOCK
c_func
(paren
id|sb
)paren
suffix:semicolon
id|offset
op_assign
id|block_group
op_mod
id|EXT2_DESC_PER_BLOCK
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;s_group_desc
(braket
id|group_desc
)braket
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_get_group_desc&quot;
comma
l_string|&quot;Group descriptor not loaded - &quot;
l_string|&quot;block_group = %d, group_desc = %lu, desc = %lu&quot;
comma
id|block_group
comma
id|group_desc
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|desc
op_assign
(paren
r_struct
id|ext2_group_desc
op_star
)paren
id|sbi-&gt;s_group_desc
(braket
id|group_desc
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
op_star
id|bh
op_assign
id|sbi-&gt;s_group_desc
(braket
id|group_desc
)braket
suffix:semicolon
r_return
id|desc
op_plus
id|offset
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the bitmap for a given block_group, reading into the specified &n; * slot in the superblock&squot;s bitmap cache.&n; *&n; * Return buffer_head on success or NULL in case of failure.&n; */
r_static
r_struct
id|buffer_head
op_star
DECL|function|read_block_bitmap
id|read_block_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
)paren
(brace
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|block_group
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_goto
id|error_out
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_block_bitmap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;read_block_bitmap&quot;
comma
l_string|&quot;Cannot read block bitmap - &quot;
l_string|&quot;block_group = %d, block_bitmap = %lu&quot;
comma
id|block_group
comma
(paren
r_int
r_int
)paren
id|desc-&gt;bg_block_bitmap
)paren
suffix:semicolon
id|error_out
suffix:colon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|reserve_blocks
r_static
r_inline
r_int
id|reserve_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|count
)paren
(brace
r_struct
id|ext2_sb_info
op_star
id|sbi
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
op_assign
id|sbi-&gt;s_es
suffix:semicolon
r_int
id|free_blocks
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_blocks_count
)paren
suffix:semicolon
r_int
id|root_blocks
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_r_blocks_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_blocks
OL
id|count
)paren
id|count
op_assign
id|free_blocks
suffix:semicolon
r_if
c_cond
(paren
id|free_blocks
OL
id|root_blocks
op_plus
id|count
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RESOURCE
)paren
op_logical_and
id|sbi-&gt;s_resuid
op_ne
id|current-&gt;fsuid
op_logical_and
(paren
id|sbi-&gt;s_resgid
op_eq
l_int|0
op_logical_or
op_logical_neg
id|in_group_p
(paren
id|sbi-&gt;s_resgid
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We are too close to reserve and we are not privileged.&n;&t;&t; * Can we allocate anything at all?&n;&t;&t; */
r_if
c_cond
(paren
id|free_blocks
OG
id|root_blocks
)paren
id|count
op_assign
id|free_blocks
op_minus
id|root_blocks
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|es-&gt;s_free_blocks_count
op_assign
id|cpu_to_le32
c_func
(paren
id|free_blocks
op_minus
id|count
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|release_blocks
r_static
r_inline
r_void
id|release_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
r_struct
id|ext2_sb_info
op_star
id|sbi
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
op_assign
id|sbi-&gt;s_es
suffix:semicolon
r_int
id|free_blocks
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_blocks_count
)paren
suffix:semicolon
id|es-&gt;s_free_blocks_count
op_assign
id|cpu_to_le32
c_func
(paren
id|free_blocks
op_plus
id|count
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_sbh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|group_reserve_blocks
r_static
r_inline
r_int
id|group_reserve_blocks
c_func
(paren
r_struct
id|ext2_group_desc
op_star
id|desc
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|count
)paren
(brace
r_int
id|free_blocks
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;bg_free_blocks_count
)paren
r_return
l_int|0
suffix:semicolon
id|free_blocks
op_assign
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_blocks
OL
id|count
)paren
id|count
op_assign
id|free_blocks
suffix:semicolon
id|desc-&gt;bg_free_blocks_count
op_assign
id|cpu_to_le16
c_func
(paren
id|free_blocks
op_minus
id|count
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|group_release_blocks
r_static
r_inline
r_void
id|group_release_blocks
c_func
(paren
r_struct
id|ext2_group_desc
op_star
id|desc
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
id|free_blocks
op_assign
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
suffix:semicolon
id|desc-&gt;bg_free_blocks_count
op_assign
id|cpu_to_le16
c_func
(paren
id|free_blocks
op_plus
id|count
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Free given blocks, update quota and i_blocks field */
DECL|function|ext2_free_blocks
r_void
id|ext2_free_blocks
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|block
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bitmap_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_int
r_int
id|block_group
suffix:semicolon
r_int
r_int
id|bit
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|overflow
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_int
id|freed
op_assign
l_int|0
comma
id|group_freed
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es
suffix:semicolon
r_if
c_cond
(paren
id|block
template_param
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_blocks_count
)paren
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_free_blocks&quot;
comma
l_string|&quot;Freeing blocks not in datazone - &quot;
l_string|&quot;block = %lu, count = %lu&quot;
comma
id|block
comma
id|count
)paren
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
id|ext2_debug
(paren
l_string|&quot;freeing block(s) %lu-%lu&bslash;n&quot;
comma
id|block
comma
id|block
op_plus
id|count
op_minus
l_int|1
)paren
suffix:semicolon
id|do_more
suffix:colon
id|overflow
op_assign
l_int|0
suffix:semicolon
id|block_group
op_assign
(paren
id|block
op_minus
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
)paren
op_div
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|bit
op_assign
(paren
id|block
op_minus
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
)paren
op_mod
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check to see if we are freeing blocks across a group&n;&t; * boundary.&n;&t; */
r_if
c_cond
(paren
id|bit
op_plus
id|count
OG
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
)paren
(brace
id|overflow
op_assign
id|bit
op_plus
id|count
op_minus
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
id|count
op_sub_assign
id|overflow
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
id|bitmap_bh
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|block_group
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap_bh
)paren
r_goto
id|error_return
suffix:semicolon
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|block_group
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_goto
id|error_return
suffix:semicolon
r_if
c_cond
(paren
id|in_range
(paren
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_block_bitmap
)paren
comma
id|block
comma
id|count
)paren
op_logical_or
id|in_range
(paren
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_bitmap
)paren
comma
id|block
comma
id|count
)paren
op_logical_or
id|in_range
(paren
id|block
comma
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_table
)paren
comma
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_itb_per_group
)paren
op_logical_or
id|in_range
(paren
id|block
op_plus
id|count
op_minus
l_int|1
comma
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_table
)paren
comma
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_itb_per_group
)paren
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_free_blocks&quot;
comma
l_string|&quot;Freeing blocks in system zones - &quot;
l_string|&quot;Block = %lu, count = %lu&quot;
comma
id|block
comma
id|count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|group_freed
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ext2_clear_bit
c_func
(paren
id|bit
op_plus
id|i
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_free_blocks&quot;
comma
l_string|&quot;bit already cleared for block %lu&quot;
comma
id|block
op_plus
id|i
)paren
suffix:semicolon
r_else
id|group_freed
op_increment
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bitmap_bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
)brace
id|group_release_blocks
c_func
(paren
id|desc
comma
id|bh2
comma
id|group_freed
)paren
suffix:semicolon
id|freed
op_add_assign
id|group_freed
suffix:semicolon
r_if
c_cond
(paren
id|overflow
)paren
(brace
id|block
op_add_assign
id|count
suffix:semicolon
id|count
op_assign
id|overflow
suffix:semicolon
r_goto
id|do_more
suffix:semicolon
)brace
id|error_return
suffix:colon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
id|release_blocks
c_func
(paren
id|sb
comma
id|freed
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|DQUOT_FREE_BLOCK
c_func
(paren
id|inode
comma
id|freed
)paren
suffix:semicolon
)brace
DECL|function|grab_block
r_static
r_int
id|grab_block
c_func
(paren
r_char
op_star
id|map
comma
r_int
id|size
comma
r_int
id|goal
)paren
(brace
r_int
id|k
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|r
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
c_func
(paren
id|goal
comma
id|map
)paren
)paren
r_goto
id|got_it
suffix:semicolon
r_if
c_cond
(paren
id|goal
)paren
(brace
multiline_comment|/*&n;&t;&t; * The goal was occupied; search forward for a free &n;&t;&t; * block within the next XX blocks.&n;&t;&t; *&n;&t;&t; * end_goal is more or less random, but it has to be&n;&t;&t; * less than EXT2_BLOCKS_PER_GROUP. Aligning up to the&n;&t;&t; * next 64-bit boundary is simple..&n;&t;&t; */
id|k
op_assign
(paren
id|goal
op_plus
l_int|63
)paren
op_amp
op_complement
l_int|63
suffix:semicolon
id|goal
op_assign
id|ext2_find_next_zero_bit
c_func
(paren
id|map
comma
id|k
comma
id|goal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|goal
OL
id|k
)paren
r_goto
id|got_it
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Search in the remainder of the current group.&n;&t;&t; */
)brace
id|p
op_assign
id|map
op_plus
(paren
id|goal
op_rshift
l_int|3
)paren
suffix:semicolon
id|r
op_assign
id|memscan
c_func
(paren
id|p
comma
l_int|0
comma
(paren
id|size
op_minus
id|goal
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|k
op_assign
(paren
id|r
op_minus
id|map
)paren
op_lshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|k
OL
id|size
)paren
(brace
multiline_comment|/* &n;&t;&t; * We have succeeded in finding a free byte in the block&n;&t;&t; * bitmap.  Now search backwards to find the start of this&n;&t;&t; * group of free blocks - won&squot;t take more than 7 iterations.&n;&t;&t; */
r_for
c_loop
(paren
id|goal
op_assign
id|k
suffix:semicolon
id|goal
op_logical_and
op_logical_neg
id|ext2_test_bit
(paren
id|goal
op_minus
l_int|1
comma
id|map
)paren
suffix:semicolon
id|goal
op_decrement
)paren
suffix:semicolon
r_goto
id|got_it
suffix:semicolon
)brace
id|k
op_assign
id|ext2_find_next_zero_bit
(paren
(paren
id|u32
op_star
)paren
id|map
comma
id|size
comma
id|goal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|k
OL
id|size
)paren
(brace
id|goal
op_assign
id|k
suffix:semicolon
r_goto
id|got_it
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
id|got_it
suffix:colon
id|ext2_set_bit
c_func
(paren
id|goal
comma
id|map
)paren
suffix:semicolon
r_return
id|goal
suffix:semicolon
)brace
multiline_comment|/*&n; * ext2_new_block uses a goal block to assist allocation.  If the goal is&n; * free, or there is a free block within 32 blocks of the goal, that block&n; * is allocated.  Otherwise a forward search is made for a free block; within &n; * each block group the search first looks for an entire free byte in the block&n; * bitmap, and then for any free bit if that fails.&n; * This function also updates quota and i_blocks field.&n; */
DECL|function|ext2_new_block
r_int
id|ext2_new_block
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|goal
comma
id|u32
op_star
id|prealloc_count
comma
id|u32
op_star
id|prealloc_block
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|buffer_head
op_star
id|bitmap_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|tmp
suffix:semicolon
r_int
id|block
op_assign
l_int|0
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|ext2_sb_info
op_star
id|sbi
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
op_assign
id|sbi-&gt;s_es
suffix:semicolon
r_int
id|group_size
op_assign
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|prealloc_goal
op_assign
id|es-&gt;s_prealloc_blocks
suffix:semicolon
r_int
id|group_alloc
op_assign
l_int|0
comma
id|es_alloc
comma
id|dq_alloc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prealloc_goal
op_decrement
)paren
id|prealloc_goal
op_assign
id|EXT2_DEFAULT_PREALLOC_BLOCKS
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prealloc_count
op_logical_or
op_star
id|prealloc_count
)paren
id|prealloc_goal
op_assign
l_int|0
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|EDQUOT
suffix:semicolon
r_if
c_cond
(paren
id|DQUOT_ALLOC_BLOCK
c_func
(paren
id|inode
comma
l_int|1
)paren
)paren
r_goto
id|out
suffix:semicolon
r_while
c_loop
(paren
id|prealloc_goal
op_logical_and
id|DQUOT_PREALLOC_BLOCK
c_func
(paren
id|inode
comma
id|prealloc_goal
)paren
)paren
id|prealloc_goal
op_decrement
suffix:semicolon
id|dq_alloc
op_assign
id|prealloc_goal
op_plus
l_int|1
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es_alloc
op_assign
id|reserve_blocks
c_func
(paren
id|sb
comma
id|dq_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|es_alloc
)paren
r_goto
id|out_unlock
suffix:semicolon
id|ext2_debug
(paren
l_string|&quot;goal=%lu.&bslash;n&quot;
comma
id|goal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|goal
OL
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
op_logical_or
id|goal
op_ge
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_blocks_count
)paren
)paren
id|goal
op_assign
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
suffix:semicolon
id|i
op_assign
(paren
id|goal
op_minus
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
)paren
op_div
id|group_size
suffix:semicolon
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_goto
id|io_error
suffix:semicolon
id|group_alloc
op_assign
id|group_reserve_blocks
c_func
(paren
id|desc
comma
id|bh2
comma
id|es_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|group_alloc
)paren
(brace
id|j
op_assign
(paren
(paren
id|goal
op_minus
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
)paren
op_mod
id|group_size
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
id|bitmap_bh
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap_bh
)paren
r_goto
id|io_error
suffix:semicolon
id|ext2_debug
(paren
l_string|&quot;goal is at %d:%d.&bslash;n&quot;
comma
id|i
comma
id|j
)paren
suffix:semicolon
id|j
op_assign
id|grab_block
c_func
(paren
id|bitmap_bh-&gt;b_data
comma
id|group_size
comma
id|j
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ge
l_int|0
)paren
r_goto
id|got_block
suffix:semicolon
id|group_release_blocks
c_func
(paren
id|desc
comma
id|bh2
comma
id|group_alloc
)paren
suffix:semicolon
id|group_alloc
op_assign
l_int|0
suffix:semicolon
)brace
id|ext2_debug
(paren
l_string|&quot;Bit not found in block group %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now search the rest of the groups.  We assume that &n;&t; * i and desc correctly point to the last group visited.&n;&t; */
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|group_alloc
op_logical_and
id|k
OL
id|sbi-&gt;s_groups_count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|sbi-&gt;s_groups_count
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|i
comma
op_amp
id|bh2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_goto
id|io_error
suffix:semicolon
id|group_alloc
op_assign
id|group_reserve_blocks
c_func
(paren
id|desc
comma
id|bh2
comma
id|es_alloc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_ge
id|sbi-&gt;s_groups_count
)paren
r_goto
id|out_release
suffix:semicolon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
id|bitmap_bh
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap_bh
)paren
r_goto
id|io_error
suffix:semicolon
id|j
op_assign
id|grab_block
c_func
(paren
id|bitmap_bh-&gt;b_data
comma
id|group_size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|0
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_new_block&quot;
comma
l_string|&quot;Free blocks count corrupted for block group %d&quot;
comma
id|i
)paren
suffix:semicolon
id|group_alloc
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
)brace
id|got_block
suffix:colon
id|ext2_debug
c_func
(paren
l_string|&quot;using block group %d(%d)&bslash;n&quot;
comma
id|i
comma
id|desc-&gt;bg_free_blocks_count
)paren
suffix:semicolon
id|tmp
op_assign
id|j
op_plus
id|i
op_star
id|group_size
op_plus
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_first_data_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_block_bitmap
)paren
op_logical_or
id|tmp
op_eq
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_bitmap
)paren
op_logical_or
id|in_range
(paren
id|tmp
comma
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_table
)paren
comma
id|sbi-&gt;s_itb_per_group
)paren
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_new_block&quot;
comma
l_string|&quot;Allocating block in system zone - &quot;
l_string|&quot;block = %u&quot;
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ge
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_blocks_count
)paren
)paren
(brace
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_new_block&quot;
comma
l_string|&quot;block(%d) &gt;= blocks count(%d) - &quot;
l_string|&quot;block_group = %d, es == %p &quot;
comma
id|j
comma
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_blocks_count
)paren
comma
id|i
comma
id|es
)paren
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
)brace
id|block
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* OK, we _had_ allocated something */
id|ext2_debug
(paren
l_string|&quot;found bit %d&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
id|dq_alloc
op_decrement
suffix:semicolon
id|es_alloc
op_decrement
suffix:semicolon
id|group_alloc
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * Do block preallocation now if required.&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|EXT2_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_meta_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|group_alloc
op_logical_and
op_logical_neg
op_star
id|prealloc_count
)paren
(brace
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|group_alloc
op_logical_and
op_increment
id|j
OL
id|group_size
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ext2_set_bit
c_func
(paren
id|j
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
r_break
suffix:semicolon
)brace
op_star
id|prealloc_block
op_assign
id|block
op_plus
l_int|1
suffix:semicolon
op_star
id|prealloc_count
op_assign
id|n
suffix:semicolon
id|es_alloc
op_sub_assign
id|n
suffix:semicolon
id|dq_alloc
op_sub_assign
id|n
suffix:semicolon
id|group_alloc
op_sub_assign
id|n
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|EXT2_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_meta_lock
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bitmap_bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
)brace
id|ext2_debug
(paren
l_string|&quot;allocating block %d. &quot;
comma
id|block
)paren
suffix:semicolon
id|out_release
suffix:colon
id|group_release_blocks
c_func
(paren
id|desc
comma
id|bh2
comma
id|group_alloc
)paren
suffix:semicolon
id|release_blocks
c_func
(paren
id|sb
comma
id|es_alloc
)paren
suffix:semicolon
op_star
id|err
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|DQUOT_FREE_BLOCK
c_func
(paren
id|inode
comma
id|dq_alloc
)paren
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
r_return
id|block
suffix:semicolon
id|io_error
suffix:colon
op_star
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_release
suffix:semicolon
)brace
DECL|function|ext2_count_free_blocks
r_int
r_int
id|ext2_count_free_blocks
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
macro_line|#ifdef EXT2FS_DEBUG
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_int
id|i
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
id|es
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|desc
op_assign
l_int|NULL
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
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|bitmap_bh
suffix:semicolon
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_continue
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
suffix:semicolon
id|bitmap_bh
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap_bh
)paren
r_continue
suffix:semicolon
id|x
op_assign
id|ext2_count_free
c_func
(paren
id|bitmap_bh
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;group %d: stored = %d, counted = %lu&bslash;n&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ext2_count_free_blocks: stored = %lu, computed = %lu, %lu&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_blocks_count
)paren
comma
id|desc_count
comma
id|bitmap_count
)paren
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
r_return
id|bitmap_count
suffix:semicolon
macro_line|#else
r_return
id|le32_to_cpu
c_func
(paren
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es-&gt;s_free_blocks_count
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|block_in_use
r_static
r_inline
r_int
id|block_in_use
(paren
r_int
r_int
id|block
comma
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_char
op_star
id|map
)paren
(brace
r_return
id|ext2_test_bit
(paren
(paren
id|block
op_minus
id|le32_to_cpu
c_func
(paren
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es-&gt;s_first_data_block
)paren
)paren
op_mod
id|EXT2_BLOCKS_PER_GROUP
c_func
(paren
id|sb
)paren
comma
id|map
)paren
suffix:semicolon
)brace
DECL|function|test_root
r_static
r_inline
r_int
id|test_root
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|a
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|a
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a
op_mod
id|b
)paren
r_return
l_int|0
suffix:semicolon
id|a
op_assign
id|a
op_div
id|b
suffix:semicolon
)brace
)brace
DECL|function|ext2_group_sparse
r_static
r_int
id|ext2_group_sparse
c_func
(paren
r_int
id|group
)paren
(brace
r_return
(paren
id|test_root
c_func
(paren
id|group
comma
l_int|3
)paren
op_logical_or
id|test_root
c_func
(paren
id|group
comma
l_int|5
)paren
op_logical_or
id|test_root
c_func
(paren
id|group
comma
l_int|7
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ext2_bg_has_super - number of blocks used by the superblock in group&n; *&t;@sb: superblock for filesystem&n; *&t;@group: group number to check&n; *&n; *&t;Return the number of blocks used by the superblock (primary or backup)&n; *&t;in this group.  Currently this will be only 0 or 1.&n; */
DECL|function|ext2_bg_has_super
r_int
id|ext2_bg_has_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
(brace
r_if
c_cond
(paren
id|EXT2_HAS_RO_COMPAT_FEATURE
c_func
(paren
id|sb
comma
id|EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER
)paren
op_logical_and
op_logical_neg
id|ext2_group_sparse
c_func
(paren
id|group
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;ext2_bg_num_gdb - number of blocks used by the group table in group&n; *&t;@sb: superblock for filesystem&n; *&t;@group: group number to check&n; *&n; *&t;Return the number of blocks used by the group descriptor table&n; *&t;(primary or backup) in this group.  In the future there may be a&n; *&t;different number of descriptor blocks in each group.&n; */
DECL|function|ext2_bg_num_gdb
r_int
r_int
id|ext2_bg_num_gdb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
(brace
r_if
c_cond
(paren
id|EXT2_HAS_RO_COMPAT_FEATURE
c_func
(paren
id|sb
comma
id|EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER
)paren
op_logical_and
op_logical_neg
id|ext2_group_sparse
c_func
(paren
id|group
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_gdb_count
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_EXT2_CHECK
multiline_comment|/* Called at mount-time, super-block is locked */
DECL|function|ext2_check_blocks_bitmap
r_void
id|ext2_check_blocks_bitmap
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|buffer_head
op_star
id|bitmap_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|es
suffix:semicolon
r_int
r_int
id|desc_count
comma
id|bitmap_count
comma
id|x
comma
id|j
suffix:semicolon
r_int
r_int
id|desc_blocks
suffix:semicolon
r_struct
id|ext2_group_desc
op_star
id|desc
suffix:semicolon
r_int
id|i
suffix:semicolon
id|es
op_assign
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es
suffix:semicolon
id|desc_count
op_assign
l_int|0
suffix:semicolon
id|bitmap_count
op_assign
l_int|0
suffix:semicolon
id|desc
op_assign
l_int|NULL
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
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_groups_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|desc
op_assign
id|ext2_get_group_desc
(paren
id|sb
comma
id|i
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
r_continue
suffix:semicolon
id|desc_count
op_add_assign
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
id|bitmap_bh
op_assign
id|read_block_bitmap
c_func
(paren
id|sb
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap_bh
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ext2_bg_has_super
c_func
(paren
id|sb
comma
id|i
)paren
op_logical_and
op_logical_neg
id|ext2_test_bit
c_func
(paren
l_int|0
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;Superblock in group %d is marked free&quot;
comma
id|i
)paren
suffix:semicolon
id|desc_blocks
op_assign
id|ext2_bg_num_gdb
c_func
(paren
id|sb
comma
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
id|desc_blocks
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
c_func
(paren
id|j
op_plus
l_int|1
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;Descriptor block #%ld in group &quot;
l_string|&quot;%d is marked free&quot;
comma
id|j
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block_in_use
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_block_bitmap
)paren
comma
id|sb
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
c_func
(paren
id|sb
comma
l_string|&quot;ext2_check_blocks_bitmap&quot;
comma
l_string|&quot;Block bitmap for group %d is marked free&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block_in_use
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_bitmap
)paren
comma
id|sb
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
c_func
(paren
id|sb
comma
l_string|&quot;ext2_check_blocks_bitmap&quot;
comma
l_string|&quot;Inode bitmap for group %d is marked free&quot;
comma
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
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_itb_per_group
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|block_in_use
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|desc-&gt;bg_inode_table
)paren
op_plus
id|j
comma
id|sb
comma
id|bitmap_bh-&gt;b_data
)paren
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_blocks_bitmap&quot;
comma
l_string|&quot;Block #%ld of the inode table in &quot;
l_string|&quot;group %d is marked free&quot;
comma
id|j
comma
id|i
)paren
suffix:semicolon
id|x
op_assign
id|ext2_count_free
c_func
(paren
id|bitmap_bh
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
op_ne
id|x
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_blocks_bitmap&quot;
comma
l_string|&quot;Wrong free blocks count for group %d, &quot;
l_string|&quot;stored = %d, counted = %lu&quot;
comma
id|i
comma
id|le16_to_cpu
c_func
(paren
id|desc-&gt;bg_free_blocks_count
)paren
comma
id|x
)paren
suffix:semicolon
id|bitmap_count
op_add_assign
id|x
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_blocks_count
)paren
op_ne
id|bitmap_count
)paren
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_blocks_bitmap&quot;
comma
l_string|&quot;Wrong free blocks count in super block, &quot;
l_string|&quot;stored = %lu, counted = %lu&quot;
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|es-&gt;s_free_blocks_count
)paren
comma
id|bitmap_count
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bitmap_bh
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
