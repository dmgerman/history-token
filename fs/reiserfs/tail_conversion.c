multiline_comment|/*&n; * Copyright 1999 Hans Reiser, see reiserfs/README for licensing and copyright details&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#else
macro_line|#include &quot;nokernel.h&quot;
macro_line|#endif
multiline_comment|/* access to tail : when one is going to read tail it must make sure, that is not running.&n; direct2indirect and indirect2direct can not run concurrently */
multiline_comment|/* Converts direct items to an unformatted node. Panics if file has no&n;   tail. -ENOSPC if no disk space for conversion */
multiline_comment|/* path points to first direct item of the file regarless of how many of&n;   them are there */
DECL|function|direct2indirect
r_int
id|direct2indirect
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|path
op_star
id|path
comma
r_struct
id|buffer_head
op_star
id|unbh
comma
id|loff_t
id|tail_offset
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|up_to_date_bh
suffix:semicolon
r_struct
id|item_head
op_star
id|p_le_ih
op_assign
id|PATH_PITEM_HEAD
(paren
id|path
)paren
suffix:semicolon
r_struct
id|cpu_key
id|end_key
suffix:semicolon
multiline_comment|/* Key to search for the last byte of the&n;&t;&t;&t;&t;converted item. */
r_struct
id|item_head
id|ind_ih
suffix:semicolon
multiline_comment|/* new indirect item to be inserted or&n;                                key of unfm pointer to be pasted */
r_int
id|n_blk_size
comma
id|n_retval
suffix:semicolon
multiline_comment|/* returned value for reiserfs_insert_item and clones */
r_struct
id|unfm_nodeinfo
id|unfm_ptr
suffix:semicolon
multiline_comment|/* Handle on an unformatted node&n;&t;&t;&t;&t;       that will be inserted in the&n;&t;&t;&t;&t;       tree. */
id|sb-&gt;u.reiserfs_sb.s_direct2indirect
op_increment
suffix:semicolon
id|n_blk_size
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
multiline_comment|/* and key to search for append or insert pointer to the new&n;       unformatted node. */
id|copy_item_head
(paren
op_amp
id|ind_ih
comma
id|p_le_ih
)paren
suffix:semicolon
id|set_le_ih_k_offset
(paren
op_amp
id|ind_ih
comma
id|tail_offset
)paren
suffix:semicolon
id|set_le_ih_k_type
(paren
op_amp
id|ind_ih
comma
id|TYPE_INDIRECT
)paren
suffix:semicolon
multiline_comment|/* Set the key to search for the place for new unfm pointer */
id|make_cpu_key
(paren
op_amp
id|end_key
comma
id|inode
comma
id|tail_offset
comma
id|TYPE_INDIRECT
comma
l_int|4
)paren
suffix:semicolon
singleline_comment|// FIXME: we could avoid this 
r_if
c_cond
(paren
id|search_for_position_by_key
(paren
id|sb
comma
op_amp
id|end_key
comma
id|path
)paren
op_eq
id|POSITION_FOUND
)paren
id|reiserfs_panic
(paren
id|sb
comma
l_string|&quot;PAP-14030: direct2indirect: &quot;
l_string|&quot;pasted or inserted byte exists in the tree&quot;
)paren
suffix:semicolon
id|p_le_ih
op_assign
id|PATH_PITEM_HEAD
(paren
id|path
)paren
suffix:semicolon
id|unfm_ptr.unfm_nodenum
op_assign
id|cpu_to_le32
(paren
id|unbh-&gt;b_blocknr
)paren
suffix:semicolon
id|unfm_ptr.unfm_freespace
op_assign
l_int|0
suffix:semicolon
singleline_comment|// ???
r_if
c_cond
(paren
id|is_statdata_le_ih
(paren
id|p_le_ih
)paren
)paren
(brace
multiline_comment|/* Insert new indirect item. */
id|set_ih_free_space
(paren
op_amp
id|ind_ih
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* delete at nearest future */
id|ind_ih.ih_item_len
op_assign
id|cpu_to_le16
(paren
id|UNFM_P_SIZE
)paren
suffix:semicolon
id|PATH_LAST_POSITION
(paren
id|path
)paren
op_increment
suffix:semicolon
id|n_retval
op_assign
id|reiserfs_insert_item
(paren
id|th
comma
id|path
comma
op_amp
id|end_key
comma
op_amp
id|ind_ih
comma
(paren
r_char
op_star
)paren
op_amp
id|unfm_ptr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Paste into last indirect item of an object. */
id|n_retval
op_assign
id|reiserfs_paste_into_item
c_func
(paren
id|th
comma
id|path
comma
op_amp
id|end_key
comma
(paren
r_char
op_star
)paren
op_amp
id|unfm_ptr
comma
id|UNFM_P_SIZE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n_retval
)paren
(brace
r_return
id|n_retval
suffix:semicolon
)brace
singleline_comment|// note: from here there are two keys which have matching first
singleline_comment|// three key components. They only differ by the fourth one.
multiline_comment|/* Set the key to search for the direct items of the file */
id|make_cpu_key
(paren
op_amp
id|end_key
comma
id|inode
comma
id|max_reiserfs_offset
(paren
id|inode
)paren
comma
id|TYPE_DIRECT
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Move bytes from the direct items to the new unformatted node&n;       and delete them. */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|tail_size
suffix:semicolon
multiline_comment|/* end_key.k_offset is set so, that we will always have found&n;           last item of the file */
r_if
c_cond
(paren
id|search_for_position_by_key
(paren
id|sb
comma
op_amp
id|end_key
comma
id|path
)paren
op_eq
id|POSITION_FOUND
)paren
id|reiserfs_panic
(paren
id|sb
comma
l_string|&quot;PAP-14050: direct2indirect: &quot;
l_string|&quot;direct item (%k) not found&quot;
comma
op_amp
id|end_key
)paren
suffix:semicolon
id|p_le_ih
op_assign
id|PATH_PITEM_HEAD
(paren
id|path
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REISERFS_CHECK
r_if
c_cond
(paren
op_logical_neg
id|is_direct_le_ih
(paren
id|p_le_ih
)paren
)paren
id|reiserfs_panic
(paren
id|sb
comma
l_string|&quot;vs-14055: direct2indirect: &quot;
l_string|&quot;direct item expected(%k), found %h&quot;
comma
op_amp
id|end_key
comma
id|p_le_ih
)paren
suffix:semicolon
macro_line|#endif
id|tail_size
op_assign
(paren
id|le_ih_k_offset
(paren
id|p_le_ih
)paren
op_amp
(paren
id|n_blk_size
op_minus
l_int|1
)paren
)paren
op_plus
id|ih_item_len
c_func
(paren
id|p_le_ih
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* we only send the unbh pointer if the buffer is not up to date.&n;&t;** this avoids overwriting good data from writepage() with old data&n;&t;** from the disk or buffer cache&n;&t;*/
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|unbh
)paren
op_logical_or
id|Page_Uptodate
c_func
(paren
id|unbh-&gt;b_page
)paren
)paren
(brace
id|up_to_date_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|up_to_date_bh
op_assign
id|unbh
suffix:semicolon
)brace
id|n_retval
op_assign
id|reiserfs_delete_item
(paren
id|th
comma
id|path
comma
op_amp
id|end_key
comma
id|inode
comma
id|up_to_date_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tail_size
op_eq
id|n_retval
)paren
singleline_comment|// done: file does not have direct items anymore
r_break
suffix:semicolon
)brace
id|inode-&gt;u.reiserfs_i.i_first_direct_byte
op_assign
id|U32_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* stolen from fs/buffer.c */
DECL|function|reiserfs_unmap_buffer
r_void
id|reiserfs_unmap_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
id|buffer_journaled
c_func
(paren
id|bh
)paren
op_logical_or
id|buffer_journal_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|mark_buffer_clean
c_func
(paren
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
singleline_comment|// clear_bit(BH_Uptodate, &amp;bh-&gt;b_state) ;
id|clear_bit
c_func
(paren
id|BH_Mapped
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BH_Req
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BH_New
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|unmap_buffers
id|unmap_buffers
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|head
suffix:semicolon
r_struct
id|buffer_head
op_star
id|next
suffix:semicolon
r_int
r_int
id|tail_index
suffix:semicolon
r_int
r_int
id|cur_index
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;buffers
)paren
(brace
id|tail_index
op_assign
id|pos
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|cur_index
op_assign
l_int|0
suffix:semicolon
id|head
op_assign
id|page-&gt;buffers
suffix:semicolon
id|bh
op_assign
id|head
suffix:semicolon
r_do
(brace
id|next
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
multiline_comment|/* we want to unmap the buffers that contain the tail, and&n;        ** all the buffers after it (since the tail must be at the&n;        ** end of the file).  We don&squot;t want to unmap file data &n;        ** before the tail, since it might be dirty and waiting to &n;        ** reach disk&n;        */
id|cur_index
op_add_assign
id|bh-&gt;b_size
suffix:semicolon
r_if
c_cond
(paren
id|cur_index
OG
id|tail_index
)paren
(brace
id|reiserfs_unmap_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|bh
op_assign
id|next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|bh
op_ne
id|head
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* this first locks inode (neither reads nor sync are permitted),&n;   reads tail through page cache, insert direct item. When direct item&n;   inserted successfully inode is left locked. Return value is always&n;   what we expect from it (number of cut bytes). But when tail remains&n;   in the unformatted node, we set mode to SKIP_BALANCING and unlock&n;   inode */
DECL|function|indirect2direct
r_int
id|indirect2direct
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|p_s_inode
comma
r_struct
id|page
op_star
id|page
comma
r_struct
id|path
op_star
id|p_s_path
comma
multiline_comment|/* path to the indirect item. */
r_struct
id|cpu_key
op_star
id|p_s_item_key
comma
multiline_comment|/* Key to look for unformatted node pointer to be cut. */
id|loff_t
id|n_new_file_size
comma
multiline_comment|/* New file size. */
r_char
op_star
id|p_c_mode
)paren
(brace
r_struct
id|super_block
op_star
id|p_s_sb
op_assign
id|p_s_inode-&gt;i_sb
suffix:semicolon
r_struct
id|item_head
id|s_ih
suffix:semicolon
r_int
r_int
id|n_block_size
op_assign
id|p_s_sb-&gt;s_blocksize
suffix:semicolon
r_char
op_star
id|tail
suffix:semicolon
r_int
id|tail_len
comma
id|round_tail_len
suffix:semicolon
id|loff_t
id|pos
comma
id|pos1
suffix:semicolon
multiline_comment|/* position of first byte of the tail */
r_struct
id|cpu_key
id|key
suffix:semicolon
id|p_s_sb-&gt;u.reiserfs_sb.s_indirect2direct
op_increment
suffix:semicolon
op_star
id|p_c_mode
op_assign
id|M_SKIP_BALANCING
suffix:semicolon
multiline_comment|/* store item head path points to. */
id|copy_item_head
(paren
op_amp
id|s_ih
comma
id|PATH_PITEM_HEAD
c_func
(paren
id|p_s_path
)paren
)paren
suffix:semicolon
id|tail_len
op_assign
(paren
id|n_new_file_size
op_amp
(paren
id|n_block_size
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_format_only
(paren
id|p_s_sb
)paren
)paren
id|round_tail_len
op_assign
id|ROUND_UP
(paren
id|tail_len
)paren
suffix:semicolon
r_else
id|round_tail_len
op_assign
id|tail_len
suffix:semicolon
id|pos
op_assign
id|le_ih_k_offset
(paren
op_amp
id|s_ih
)paren
op_minus
l_int|1
op_plus
(paren
id|le16_to_cpu
(paren
id|s_ih.ih_item_len
)paren
op_div
id|UNFM_P_SIZE
op_minus
l_int|1
)paren
op_star
id|p_s_sb-&gt;s_blocksize
suffix:semicolon
id|pos1
op_assign
id|pos
suffix:semicolon
singleline_comment|// we are protected by i_sem. The tail can not disapper, not
singleline_comment|// append can be done either
singleline_comment|// we are in truncate or packing tail in file_release
id|tail
op_assign
(paren
r_char
op_star
)paren
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* this can schedule */
r_if
c_cond
(paren
id|path_changed
(paren
op_amp
id|s_ih
comma
id|p_s_path
)paren
)paren
(brace
multiline_comment|/* re-search indirect item */
r_if
c_cond
(paren
id|search_for_position_by_key
(paren
id|p_s_sb
comma
id|p_s_item_key
comma
id|p_s_path
)paren
op_eq
id|POSITION_NOT_FOUND
)paren
id|reiserfs_panic
c_func
(paren
id|p_s_sb
comma
l_string|&quot;PAP-5520: indirect2direct: &quot;
l_string|&quot;item to be converted %k does not exist&quot;
comma
id|p_s_item_key
)paren
suffix:semicolon
id|copy_item_head
c_func
(paren
op_amp
id|s_ih
comma
id|PATH_PITEM_HEAD
c_func
(paren
id|p_s_path
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REISERFS_CHECK
id|pos
op_assign
id|le_ih_k_offset
(paren
op_amp
id|s_ih
)paren
op_minus
l_int|1
op_plus
(paren
id|le16_to_cpu
(paren
id|s_ih.ih_item_len
)paren
op_div
id|UNFM_P_SIZE
op_minus
l_int|1
)paren
op_star
id|p_s_sb-&gt;s_blocksize
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ne
id|pos1
)paren
id|reiserfs_panic
(paren
id|p_s_sb
comma
l_string|&quot;vs-5530: indirect2direct: &quot;
l_string|&quot;tail position changed while we were reading it&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Set direct item header to insert. */
id|make_le_item_head
(paren
op_amp
id|s_ih
comma
l_int|0
comma
id|inode_items_version
(paren
id|p_s_inode
)paren
comma
id|pos1
op_plus
l_int|1
comma
id|TYPE_DIRECT
comma
id|round_tail_len
comma
l_int|0xffff
multiline_comment|/*ih_free_space*/
)paren
suffix:semicolon
multiline_comment|/* we want a pointer to the first byte of the tail in the page.&n;    ** the page was locked and this part of the page was up to date when&n;    ** indirect2direct was called, so we know the bytes are still valid&n;    */
id|tail
op_assign
id|tail
op_plus
(paren
id|pos
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|PATH_LAST_POSITION
c_func
(paren
id|p_s_path
)paren
op_increment
suffix:semicolon
id|key
op_assign
op_star
id|p_s_item_key
suffix:semicolon
id|set_cpu_key_k_type
(paren
op_amp
id|key
comma
id|TYPE_DIRECT
)paren
suffix:semicolon
id|key.key_length
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* Insert tail as new direct item in the tree */
r_if
c_cond
(paren
id|reiserfs_insert_item
c_func
(paren
id|th
comma
id|p_s_path
comma
op_amp
id|key
comma
op_amp
id|s_ih
comma
id|tail
ques
c_cond
id|tail
suffix:colon
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* No disk memory. So we can not convert last unformatted node&n;&t;   to the direct item.  In this case we used to adjust&n;&t;   indirect items&squot;s ih_free_space. Now ih_free_space is not&n;&t;   used, it would be ideal to write zeros to corresponding&n;&t;   unformatted node. For now i_size is considered as guard for&n;&t;   going out of file size */
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|n_block_size
op_minus
id|round_tail_len
suffix:semicolon
)brace
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* this will invalidate all the buffers in the page after&n;    ** pos1&n;    */
id|unmap_buffers
c_func
(paren
id|page
comma
id|pos1
)paren
suffix:semicolon
singleline_comment|// note: we have now the same as in above direct2indirect
singleline_comment|// conversion: there are two keys which have matching first three
singleline_comment|// key components. They only differ by the fouhth one.
multiline_comment|/* We have inserted new direct item and must remove last&n;       unformatted node. */
id|p_s_inode-&gt;i_blocks
op_add_assign
(paren
id|p_s_sb-&gt;s_blocksize
op_div
l_int|512
)paren
suffix:semicolon
op_star
id|p_c_mode
op_assign
id|M_CUT
suffix:semicolon
multiline_comment|/* we store position of first direct item in the in-core inode */
singleline_comment|//mark_file_with_tail (p_s_inode, pos1 + 1);
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
op_assign
id|pos1
op_plus
l_int|1
suffix:semicolon
r_return
id|n_block_size
op_minus
id|round_tail_len
suffix:semicolon
)brace
eof
