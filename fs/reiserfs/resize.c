multiline_comment|/* &n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
multiline_comment|/* &n; * Written by Alexander Zarochentcev.&n; *&n; * The kernel part of the (on-line) reiserfs resizer.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs_sb.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|function|reiserfs_resize
r_int
id|reiserfs_resize
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
r_int
id|block_count_new
)paren
(brace
r_struct
id|reiserfs_super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|bitmap
comma
op_star
id|bh
suffix:semicolon
r_struct
id|reiserfs_transaction_handle
id|th
suffix:semicolon
r_int
r_int
id|bmap_nr_new
comma
id|bmap_nr
suffix:semicolon
r_int
r_int
id|block_r_new
comma
id|block_r
suffix:semicolon
r_struct
id|reiserfs_list_bitmap
op_star
id|jb
suffix:semicolon
r_struct
id|reiserfs_list_bitmap
id|jbitmap
(braket
id|JOURNAL_NUM_BITMAPS
)braket
suffix:semicolon
r_int
r_int
r_int
id|block_count
comma
id|free_blocks
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|copy_size
suffix:semicolon
id|sb
op_assign
id|SB_DISK_SUPER_BLOCK
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SB_BLOCK_COUNT
c_func
(paren
id|s
)paren
op_ge
id|block_count_new
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;can&bslash;&squot;t shrink filesystem on-line&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* check the device size */
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|block_count_new
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;reiserfs_resize: can&bslash;&squot;t read last block&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* old disk layout detection; those partitions can be mounted, but&n;&t; * cannot be resized */
r_if
c_cond
(paren
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|b_blocknr
op_star
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|b_size
op_ne
id|REISERFS_DISK_OFFSET_IN_BYTES
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;reiserfs_resize: unable to resize a reiserfs without distributed bitmap (fs version &lt; 3.5.12)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOTSUPP
suffix:semicolon
)brace
multiline_comment|/* count used bits in last bitmap block */
id|block_r
op_assign
id|SB_BLOCK_COUNT
c_func
(paren
id|s
)paren
op_minus
(paren
id|SB_BMAP_NR
c_func
(paren
id|s
)paren
op_minus
l_int|1
)paren
op_star
id|s-&gt;s_blocksize
op_star
l_int|8
suffix:semicolon
multiline_comment|/* count bitmap blocks in new fs */
id|bmap_nr_new
op_assign
id|block_count_new
op_div
(paren
id|s-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
id|block_r_new
op_assign
id|block_count_new
op_minus
id|bmap_nr_new
op_star
id|s-&gt;s_blocksize
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|block_r_new
)paren
id|bmap_nr_new
op_increment
suffix:semicolon
r_else
id|block_r_new
op_assign
id|s-&gt;s_blocksize
op_star
l_int|8
suffix:semicolon
multiline_comment|/* save old values */
id|block_count
op_assign
id|SB_BLOCK_COUNT
c_func
(paren
id|s
)paren
suffix:semicolon
id|bmap_nr
op_assign
id|SB_BMAP_NR
c_func
(paren
id|s
)paren
suffix:semicolon
multiline_comment|/* resizing of reiserfs bitmaps (journal and real), if needed */
r_if
c_cond
(paren
id|bmap_nr_new
OG
id|bmap_nr
)paren
(brace
multiline_comment|/* reallocate journal bitmaps */
r_if
c_cond
(paren
id|reiserfs_allocate_list_bitmaps
c_func
(paren
id|s
comma
id|jbitmap
comma
id|bmap_nr_new
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;reiserfs_resize: unable to allocate memory for journal bitmaps&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* the new journal bitmaps are zero filled, now we copy in the bitmap&n;&t;    ** node pointers from the old journal bitmap structs, and then&n;&t;    ** transfer the new data structures into the journal struct.&n;&t;    **&n;&t;    ** using the copy_size var below allows this code to work for&n;&t;    ** both shrinking and expanding the FS.&n;&t;    */
id|copy_size
op_assign
id|bmap_nr_new
OL
id|bmap_nr
ques
c_cond
id|bmap_nr_new
suffix:colon
id|bmap_nr
suffix:semicolon
id|copy_size
op_assign
id|copy_size
op_star
r_sizeof
(paren
r_struct
id|reiserfs_list_bitmap_node
op_star
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
id|JOURNAL_NUM_BITMAPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|reiserfs_bitmap_node
op_star
op_star
id|node_tmp
suffix:semicolon
id|jb
op_assign
id|SB_JOURNAL
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|j_list_bitmap
op_plus
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|jbitmap
(braket
id|i
)braket
dot
id|bitmaps
comma
id|jb-&gt;bitmaps
comma
id|copy_size
)paren
suffix:semicolon
multiline_comment|/* just in case vfree schedules on us, copy the new&n;&t;&t;** pointer into the journal struct before freeing the &n;&t;&t;** old one&n;&t;&t;*/
id|node_tmp
op_assign
id|jb-&gt;bitmaps
suffix:semicolon
id|jb-&gt;bitmaps
op_assign
id|jbitmap
(braket
id|i
)braket
dot
id|bitmaps
suffix:semicolon
id|vfree
c_func
(paren
id|node_tmp
)paren
suffix:semicolon
)brace
multiline_comment|/* allocate additional bitmap blocks, reallocate array of bitmap&n;&t;     * block pointers */
id|bitmap
op_assign
id|reiserfs_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|buffer_head
op_star
)paren
op_star
id|bmap_nr_new
comma
id|GFP_KERNEL
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;reiserfs_resize: unable to allocate memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|bmap_nr
suffix:semicolon
id|i
op_increment
)paren
id|bitmap
(braket
id|i
)braket
op_assign
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|bmap_nr
suffix:semicolon
id|i
OL
id|bmap_nr_new
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bitmap
(braket
id|i
)braket
op_assign
id|sb_getblk
c_func
(paren
id|s
comma
id|i
op_star
id|s-&gt;s_blocksize
op_star
l_int|8
)paren
suffix:semicolon
id|memset
c_func
(paren
id|bitmap
(braket
id|i
)braket
op_member_access_from_pointer
id|b_data
comma
l_int|0
comma
id|sb_blocksize
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
id|reiserfs_test_and_set_le_bit
c_func
(paren
l_int|0
comma
id|bitmap
(braket
id|i
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bitmap
(braket
id|i
)braket
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bitmap
(braket
id|i
)braket
)paren
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
id|bitmap
op_plus
id|i
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bitmap
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* free old bitmap blocks array */
id|reiserfs_kfree
c_func
(paren
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
comma
r_sizeof
(paren
r_struct
id|buffer_head
op_star
)paren
op_star
id|bmap_nr
comma
id|s
)paren
suffix:semicolon
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
op_assign
id|bitmap
suffix:semicolon
)brace
multiline_comment|/* begin transaction */
id|journal_begin
c_func
(paren
op_amp
id|th
comma
id|s
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* correct last bitmap blocks in old and new disk layout */
id|reiserfs_prepare_for_journal
c_func
(paren
id|s
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr
op_minus
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|block_r
suffix:semicolon
id|i
OL
id|s-&gt;s_blocksize
op_star
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|reiserfs_test_and_clear_le_bit
c_func
(paren
id|i
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|journal_mark_dirty
c_func
(paren
op_amp
id|th
comma
id|s
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|reiserfs_prepare_for_journal
c_func
(paren
id|s
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr_new
op_minus
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|block_r_new
suffix:semicolon
id|i
OL
id|s-&gt;s_blocksize
op_star
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|reiserfs_test_and_set_le_bit
c_func
(paren
id|i
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr_new
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|journal_mark_dirty
c_func
(paren
op_amp
id|th
comma
id|s
comma
id|SB_AP_BITMAP
c_func
(paren
id|s
)paren
(braket
id|bmap_nr_new
op_minus
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* update super */
id|reiserfs_prepare_for_journal
c_func
(paren
id|s
comma
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_blocks
op_assign
id|SB_FREE_BLOCKS
c_func
(paren
id|s
)paren
suffix:semicolon
id|PUT_SB_FREE_BLOCKS
c_func
(paren
id|s
comma
id|free_blocks
op_plus
(paren
id|block_count_new
op_minus
id|block_count
op_minus
(paren
id|bmap_nr_new
op_minus
id|bmap_nr
)paren
)paren
)paren
suffix:semicolon
id|PUT_SB_BLOCK_COUNT
c_func
(paren
id|s
comma
id|block_count_new
)paren
suffix:semicolon
id|PUT_SB_BMAP_NR
c_func
(paren
id|s
comma
id|bmap_nr_new
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
id|journal_mark_dirty
c_func
(paren
op_amp
id|th
comma
id|s
comma
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
id|SB_JOURNAL
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|j_must_wait
op_assign
l_int|1
suffix:semicolon
id|journal_end
c_func
(paren
op_amp
id|th
comma
id|s
comma
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
