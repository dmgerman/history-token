multiline_comment|/*&n; *  Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README  &n; */
multiline_comment|/*&n; * Contains code from&n; *&n; *  linux/include/linux/lock.h and linux/fs/buffer.c /linux/fs/minix/fsync.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; *  wait_buffer_until_released&n; *  reiserfs_bread&n; *  reiserfs_getblk&n; *  get_new_buffer&n; */
multiline_comment|/* when we allocate a new block (get_new_buffer, get_empty_nodes) and&n;   get buffer for it, it is possible that it is held by someone else&n;   or even by this process. In this function we wait until all other&n;   holders release buffer. To make sure, that current process does not&n;   hold we did free all buffers in tree balance structure&n;   (get_empty_nodes and get_nodes_for_preserving) or in path structure&n;   only (get_new_buffer) just before calling this */
DECL|function|wait_buffer_until_released
r_void
id|wait_buffer_until_released
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|repeat_counter
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
(paren
op_amp
(paren
id|bh-&gt;b_count
)paren
)paren
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
op_increment
id|repeat_counter
op_mod
l_int|30000000
)paren
)paren
(brace
id|reiserfs_warning
(paren
l_string|&quot;vs-3050: wait_buffer_until_released: nobody releases buffer (%b). Still waiting (%d) %cJDIRTY %cJWAIT&bslash;n&quot;
comma
id|bh
comma
id|repeat_counter
comma
id|buffer_journaled
c_func
(paren
id|bh
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;!&squot;
comma
id|buffer_journal_dirty
c_func
(paren
id|bh
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;!&squot;
)paren
suffix:semicolon
)brace
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
multiline_comment|/*current-&gt;counter = 0;*/
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|repeat_counter
OG
l_int|30000000
)paren
(brace
id|reiserfs_warning
c_func
(paren
l_string|&quot;vs-3051: done waiting, ignore vs-3050 messages for (%b)&bslash;n&quot;
comma
id|bh
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * reiserfs_bread() reads a specified block and returns the buffer that contains&n; * it. It returns NULL if the block was unreadable.&n; */
multiline_comment|/* It first tries to find the block in cache, and if it cannot do so&n;   then it creates a new buffer and schedules I/O to read the&n;   block. */
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|reiserfs_bread
r_struct
id|buffer_head
op_star
id|reiserfs_bread
(paren
id|kdev_t
id|n_dev
comma
r_int
id|n_block
comma
r_int
id|n_size
)paren
(brace
r_return
id|bread
(paren
id|n_dev
comma
id|n_block
comma
id|n_size
)paren
suffix:semicolon
)brace
multiline_comment|/* This function looks for a buffer which contains a given block.  If&n;   the block is in cache it returns it, otherwise it returns a new&n;   buffer which is not uptodate.  This is called by reiserfs_bread and&n;   other functions. Note that get_new_buffer ought to be called this&n;   and this ought to be called get_new_buffer, since this doesn&squot;t&n;   actually get the block off of the disk. */
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|reiserfs_getblk
r_struct
id|buffer_head
op_star
id|reiserfs_getblk
(paren
id|kdev_t
id|n_dev
comma
r_int
id|n_block
comma
r_int
id|n_size
)paren
(brace
r_return
id|getblk
(paren
id|n_dev
comma
id|n_block
comma
id|n_size
)paren
suffix:semicolon
)brace
macro_line|#ifdef NEW_GET_NEW_BUFFER
multiline_comment|/* returns one buffer with a blocknr near blocknr. */
DECL|function|get_new_buffer_near_blocknr
r_static
r_int
id|get_new_buffer_near_blocknr
c_func
(paren
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_int
id|blocknr
comma
r_struct
id|buffer_head
op_star
op_star
id|pp_s_new_bh
comma
r_struct
id|path
op_star
id|p_s_path
)paren
(brace
r_int
r_int
id|n_new_blocknumber
op_assign
l_int|0
suffix:semicolon
r_int
id|n_ret_value
comma
id|n_repeat
op_assign
id|CARRY_ON
suffix:semicolon
macro_line|#ifdef CONFIG_REISERFS_CHECK
r_int
id|repeat_counter
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocknr
)paren
id|printk
(paren
l_string|&quot;blocknr passed to get_new_buffer_near_blocknr was 0&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|n_ret_value
op_assign
id|reiserfs_new_blocknrs
(paren
id|p_s_sb
comma
op_amp
id|n_new_blocknumber
comma
id|blocknr
comma
l_int|1
)paren
)paren
op_eq
id|NO_DISK_SPACE
)paren
r_return
id|NO_DISK_SPACE
suffix:semicolon
op_star
id|pp_s_new_bh
op_assign
id|reiserfs_getblk
c_func
(paren
id|p_s_sb-&gt;s_dev
comma
id|n_new_blocknumber
comma
id|p_s_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
op_star
id|pp_s_new_bh
)paren
)paren
(brace
id|RFALSE
c_func
(paren
id|buffer_dirty
c_func
(paren
op_star
id|pp_s_new_bh
)paren
op_logical_or
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_dev
op_eq
id|NODEV
comma
l_string|&quot;PAP-14080: invalid uptodate buffer %b for the new block&quot;
comma
op_star
id|pp_s_new_bh
)paren
suffix:semicolon
multiline_comment|/* Free path buffers to prevent deadlock. */
multiline_comment|/* It is possible that this process has the buffer, which this function is getting, already in&n;       its path, and is responsible for double incrementing the value of b_count.  If we recalculate&n;       the path after schedule we can avoid risking an endless loop.  This problematic situation is&n;       possible in a multiple processing environment.  Suppose process 1 has acquired a path P; then&n;       process 2 balanced and remove block A from the tree.  Process 1 continues and runs&n;       get_new_buffer, that returns buffer with block A. If node A was on the path P, then it will&n;       have b_count == 2. If we now will simply wait in while ( (*pp_s_new_bh)-&gt;b_count &gt; 1 ) we get&n;       into an endless loop, as nobody will release this buffer and the current process holds buffer&n;       twice. That is why we do decrement_counters_in_path(p_s_path) before waiting until b_count&n;       becomes 1. (it there were other processes holding node A, then eventually we will get a&n;       moment, when all of them released a buffer). */
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
(paren
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_count
)paren
)paren
OG
l_int|1
)paren
(brace
id|decrement_counters_in_path
c_func
(paren
id|p_s_path
)paren
suffix:semicolon
id|n_ret_value
op_or_assign
id|SCHEDULE_OCCURRED
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_read
(paren
op_amp
(paren
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_count
)paren
)paren
OG
l_int|1
)paren
(brace
macro_line|#ifdef REISERFS_INFO
id|printk
c_func
(paren
l_string|&quot;get_new_buffer() calls schedule to decrement b_count&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_REISERFS_CHECK
r_if
c_cond
(paren
op_logical_neg
(paren
op_increment
id|repeat_counter
op_mod
l_int|10000
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;get_new_buffer(%u): counter(%d) too big&quot;
comma
id|current-&gt;pid
comma
id|repeat_counter
)paren
suffix:semicolon
macro_line|#endif
id|current-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_REISERFS_CHECK
r_if
c_cond
(paren
id|buffer_dirty
c_func
(paren
op_star
id|pp_s_new_bh
)paren
op_logical_or
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_dev
op_eq
id|NODEV
)paren
(brace
id|print_buffer_head
c_func
(paren
op_star
id|pp_s_new_bh
comma
l_string|&quot;get_new_buffer&quot;
)paren
suffix:semicolon
id|reiserfs_panic
c_func
(paren
id|p_s_sb
comma
l_string|&quot;PAP-14090: get_new_buffer: invalid uptodate buffer %b for the new block(case 2)&quot;
comma
op_star
id|pp_s_new_bh
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
suffix:semicolon
id|RFALSE
c_func
(paren
id|atomic_read
(paren
op_amp
(paren
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_count
)paren
)paren
op_ne
l_int|1
comma
l_string|&quot;PAP-14100: not uptodate buffer %b for the new block has b_count more than one&quot;
comma
op_star
id|pp_s_new_bh
)paren
suffix:semicolon
)brace
r_return
(paren
id|n_ret_value
op_or
id|n_repeat
)paren
suffix:semicolon
)brace
multiline_comment|/* returns the block number of the last unformatted node, assumes p_s_key_to_search.k_offset is a byte in the tail of&n;   the file, Useful for when you want to append to a file, and convert a direct item into an unformatted node near the&n;   last unformatted node of the file.  Putting the unformatted node near the direct item is potentially very bad to do.&n;   If there is no unformatted node in the file, then we return the block number of the direct item.  */
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|get_last_unformatted_node_blocknr_of_file
r_inline
r_int
id|get_last_unformatted_node_blocknr_of_file
c_func
(paren
r_struct
id|key
op_star
id|p_s_key_to_search
comma
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_struct
id|buffer_head
op_star
id|p_s_bh
r_struct
id|path
op_star
id|p_unf_search_path
comma
r_struct
id|inode
op_star
id|p_s_inode
)paren
(brace
r_struct
id|key
id|unf_key_to_search
suffix:semicolon
r_struct
id|item_head
op_star
id|p_s_ih
suffix:semicolon
r_int
id|n_pos_in_item
suffix:semicolon
r_struct
id|buffer_head
op_star
id|p_indirect_item_bh
suffix:semicolon
id|copy_key
c_func
(paren
op_amp
id|unf_key_to_search
comma
id|p_s_key_to_search
)paren
suffix:semicolon
id|unf_key_to_search.k_uniqueness
op_assign
id|TYPE_INDIRECT
suffix:semicolon
id|unf_key_to_search.k_offset
op_assign
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* p_s_key_to_search-&gt;k_offset -  MAX_ITEM_LEN(p_s_sb-&gt;s_blocksize); */
r_if
c_cond
(paren
id|search_for_position_by_key
(paren
id|p_s_sb
comma
op_amp
id|unf_key_to_search
comma
id|p_unf_search_path
comma
op_amp
id|n_pos_in_item
)paren
op_eq
id|POSITION_FOUND
)paren
(brace
id|p_s_ih
op_assign
id|B_N_PITEM_HEAD
c_func
(paren
id|p_indirect_item_bh
op_assign
id|PATH_PLAST_BUFFER
c_func
(paren
id|p_unf_search_path
)paren
comma
id|PATH_LAST_POSITION
c_func
(paren
id|p_unf_search_path
)paren
)paren
suffix:semicolon
r_return
(paren
id|B_I_POS_UNFM_POINTER
c_func
(paren
id|p_indirect_item_bh
comma
id|p_s_ih
comma
id|n_pos_in_item
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  else */
id|printk
c_func
(paren
l_string|&quot;reiser-1800: search for unformatted node failed, p_s_key_to_search-&gt;k_offset = %u,  unf_key_to_search.k_offset = %u, MAX_ITEM_LEN(p_s_sb-&gt;s_blocksize) = %ld, debug this&bslash;n&quot;
comma
id|p_s_key_to_search-&gt;k_offset
comma
id|unf_key_to_search.k_offset
comma
id|MAX_ITEM_LEN
c_func
(paren
id|p_s_sb-&gt;s_blocksize
)paren
)paren
suffix:semicolon
id|print_buffer_head
c_func
(paren
id|PATH_PLAST_BUFFER
c_func
(paren
id|p_unf_search_path
)paren
comma
l_string|&quot;the buffer holding the item before the key we failed to find&quot;
)paren
suffix:semicolon
id|print_block_head
c_func
(paren
id|PATH_PLAST_BUFFER
c_func
(paren
id|p_unf_search_path
)paren
comma
l_string|&quot;the block head&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* keeps the compiler quiet */
)brace
multiline_comment|/* hasn&squot;t been out of disk space tested  */
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|get_buffer_near_last_unf
r_static
r_int
id|get_buffer_near_last_unf
(paren
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_struct
id|key
op_star
id|p_s_key_to_search
comma
r_struct
id|inode
op_star
id|p_s_inode
comma
r_struct
id|buffer_head
op_star
id|p_s_bh
comma
r_struct
id|buffer_head
op_star
op_star
id|pp_s_un_bh
comma
r_struct
id|path
op_star
id|p_s_search_path
)paren
(brace
r_int
id|unf_blocknr
op_assign
l_int|0
comma
multiline_comment|/* blocknr from which we start search for a free block for an unformatted node, if 0&n;                          then we didn&squot;t find an unformatted node though we might have found a file hole */
id|n_repeat
op_assign
id|CARRY_ON
suffix:semicolon
r_struct
id|key
id|unf_key_to_search
suffix:semicolon
r_struct
id|path
id|unf_search_path
suffix:semicolon
id|copy_key
c_func
(paren
op_amp
id|unf_key_to_search
comma
id|p_s_key_to_search
)paren
suffix:semicolon
id|unf_key_to_search.k_uniqueness
op_assign
id|TYPE_INDIRECT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
OG
l_int|4095
)paren
multiline_comment|/* i_first_direct_byte gets used for all sorts of&n;                                                              crap other than what the name indicates, thus&n;                                                              testing to see if it is 0 is not enough */
op_logical_and
(paren
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
OL
id|MAX_KEY_OFFSET
)paren
multiline_comment|/* if there is no direct item then&n;                                                                           i_first_direct_byte = MAX_KEY_OFFSET */
)paren
(brace
multiline_comment|/* actually, we don&squot;t want the last unformatted node, we want the last unformatted node&n;                                   which is before the current file offset */
id|unf_key_to_search.k_offset
op_assign
(paren
(paren
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
op_minus
l_int|1
)paren
OL
id|unf_key_to_search.k_offset
)paren
ques
c_cond
id|p_s_inode-&gt;u.reiserfs_i.i_first_direct_byte
op_minus
l_int|1
suffix:colon
id|unf_key_to_search.k_offset
suffix:semicolon
r_while
c_loop
(paren
id|unf_key_to_search.k_offset
OG
op_minus
l_int|1
)paren
(brace
multiline_comment|/* This is our poorly documented way of initializing paths. -Hans */
id|init_path
(paren
op_amp
id|unf_search_path
)paren
suffix:semicolon
multiline_comment|/* get the blocknr from which we start the search for a free block. */
id|unf_blocknr
op_assign
id|get_last_unformatted_node_blocknr_of_file
c_func
(paren
id|p_s_key_to_search
comma
multiline_comment|/* assumes this points to the file tail */
id|p_s_sb
comma
multiline_comment|/* lets us figure out the block size */
id|p_s_bh
comma
multiline_comment|/* if there is no unformatted node in the file,&n;                                                                               then it returns p_s_bh-&gt;b_blocknr */
op_amp
id|unf_search_path
comma
id|p_s_inode
)paren
suffix:semicolon
multiline_comment|/*        printk(&quot;in while loop: unf_blocknr = %d,  *pp_s_un_bh = %p&bslash;n&quot;, unf_blocknr, *pp_s_un_bh); */
r_if
c_cond
(paren
id|unf_blocknr
)paren
r_break
suffix:semicolon
r_else
multiline_comment|/* release the path and search again, this could be really slow for huge&n;                                   holes.....better to spend the coding time adding compression though.... -Hans */
(brace
multiline_comment|/* Vladimir, is it a problem that I don&squot;t brelse these buffers ?-Hans */
id|decrement_counters_in_path
c_func
(paren
op_amp
id|unf_search_path
)paren
suffix:semicolon
id|unf_key_to_search.k_offset
op_sub_assign
l_int|4096
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|unf_blocknr
)paren
(brace
id|n_repeat
op_or_assign
id|get_new_buffer_near_blocknr
c_func
(paren
id|p_s_sb
comma
id|unf_blocknr
comma
id|pp_s_un_bh
comma
id|p_s_search_path
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* all unformatted nodes are holes */
id|n_repeat
op_or_assign
id|get_new_buffer_near_blocknr
c_func
(paren
id|p_s_sb
comma
id|p_s_bh-&gt;b_blocknr
comma
id|pp_s_un_bh
comma
id|p_s_search_path
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* file has no unformatted nodes */
id|n_repeat
op_or_assign
id|get_new_buffer_near_blocknr
c_func
(paren
id|p_s_sb
comma
id|p_s_bh-&gt;b_blocknr
comma
id|pp_s_un_bh
comma
id|p_s_search_path
)paren
suffix:semicolon
multiline_comment|/*     printk(&quot;in else: unf_blocknr = %d,  *pp_s_un_bh = %p&bslash;n&quot;, unf_blocknr, *pp_s_un_bh); */
multiline_comment|/*     print_path (0,  p_s_search_path); */
)brace
r_return
id|n_repeat
suffix:semicolon
)brace
macro_line|#endif /* NEW_GET_NEW_BUFFER */
macro_line|#ifdef OLD_GET_NEW_BUFFER
multiline_comment|/* The function is NOT SCHEDULE-SAFE! */
DECL|function|get_new_buffer
r_int
id|get_new_buffer
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|buffer_head
op_star
id|p_s_bh
comma
r_struct
id|buffer_head
op_star
op_star
id|pp_s_new_bh
comma
r_struct
id|path
op_star
id|p_s_path
)paren
(brace
r_int
r_int
id|n_new_blocknumber
op_assign
l_int|0
suffix:semicolon
r_int
id|n_repeat
suffix:semicolon
r_struct
id|super_block
op_star
id|p_s_sb
op_assign
id|th-&gt;t_super
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n_repeat
op_assign
id|reiserfs_new_unf_blocknrs
(paren
id|th
comma
op_amp
id|n_new_blocknumber
comma
id|p_s_bh-&gt;b_blocknr
)paren
)paren
op_eq
id|NO_DISK_SPACE
)paren
r_return
id|NO_DISK_SPACE
suffix:semicolon
op_star
id|pp_s_new_bh
op_assign
id|reiserfs_getblk
c_func
(paren
id|p_s_sb-&gt;s_dev
comma
id|n_new_blocknumber
comma
id|p_s_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_count
)paren
OG
l_int|1
)paren
(brace
multiline_comment|/* Free path buffers to prevent deadlock which can occur in the&n;       situation like : this process holds p_s_path; Block&n;       (*pp_s_new_bh)-&gt;b_blocknr is on the path p_s_path, but it is&n;       not necessary, that *pp_s_new_bh is in the tree; process 2&n;       could remove it from the tree and freed block&n;       (*pp_s_new_bh)-&gt;b_blocknr. Reiserfs_new_blocknrs in above&n;       returns block (*pp_s_new_bh)-&gt;b_blocknr. Reiserfs_getblk gets&n;       buffer for it, and it has b_count &gt; 1. If we now will simply&n;       wait in while ( (*pp_s_new_bh)-&gt;b_count &gt; 1 ) we get into an&n;       endless loop, as nobody will release this buffer and the&n;       current process holds buffer twice. That is why we do&n;       decrement_counters_in_path(p_s_path) before waiting until&n;       b_count becomes 1. (it there were other processes holding node&n;       pp_s_new_bh, then eventually we will get a moment, when all of&n;       them released a buffer). */
id|decrement_counters_in_path
c_func
(paren
id|p_s_path
)paren
suffix:semicolon
id|wait_buffer_until_released
(paren
op_star
id|pp_s_new_bh
)paren
suffix:semicolon
id|n_repeat
op_or_assign
id|SCHEDULE_OCCURRED
suffix:semicolon
)brace
id|RFALSE
c_func
(paren
id|atomic_read
(paren
op_amp
(paren
(paren
op_star
id|pp_s_new_bh
)paren
op_member_access_from_pointer
id|b_count
)paren
)paren
op_ne
l_int|1
op_logical_or
id|buffer_dirty
(paren
op_star
id|pp_s_new_bh
)paren
comma
l_string|&quot;PAP-14100: not free or dirty buffer %b for the new block&quot;
comma
op_star
id|pp_s_new_bh
)paren
suffix:semicolon
r_return
id|n_repeat
suffix:semicolon
)brace
macro_line|#endif /* OLD_GET_NEW_BUFFER */
macro_line|#ifdef GET_MANY_BLOCKNRS
multiline_comment|/* code not yet functional */
DECL|function|get_next_blocknr
id|get_next_blocknr
(paren
r_int
r_int
op_star
id|p_blocknr_array
comma
multiline_comment|/* we get a whole bunch of blocknrs all at once for&n;                                                                     the write.  This is better than getting them one at&n;                                                                     a time.  */
r_int
r_int
op_star
op_star
id|p_blocknr_index
comma
multiline_comment|/* pointer to current offset into the array. */
r_int
r_int
id|blocknr_array_length
)paren
(brace
r_int
r_int
id|return_value
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p_blocknr_index
OL
id|p_blocknr_array
op_plus
id|blocknr_array_length
)paren
(brace
id|return_value
op_assign
op_star
op_star
id|p_blocknr_index
suffix:semicolon
op_star
op_star
id|p_blocknr_index
op_assign
l_int|0
suffix:semicolon
op_star
id|p_blocknr_index
op_increment
suffix:semicolon
r_return
(paren
id|return_value
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree
(paren
id|p_blocknr_array
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* GET_MANY_BLOCKNRS */
eof
