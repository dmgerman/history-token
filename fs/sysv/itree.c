multiline_comment|/*&n; *  linux/fs/sysv/itree.c&n; *&n; *  Handling of indirect blocks&squot; trees.&n; *  AV, Sep--Dec 2000&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;sysv.h&quot;
DECL|enumerator|DIRECT
DECL|enumerator|DEPTH
r_enum
(brace
id|DIRECT
op_assign
l_int|10
comma
id|DEPTH
op_assign
l_int|4
)brace
suffix:semicolon
multiline_comment|/* Have triple indirect */
DECL|function|dirty_indirect
r_static
r_inline
r_void
id|dirty_indirect
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
)paren
id|sync_dirty_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|block_to_path
r_static
r_int
id|block_to_path
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
comma
r_int
id|offsets
(braket
id|DEPTH
)braket
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
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|ptrs_bits
op_assign
id|sbi-&gt;s_ind_per_block_bits
suffix:semicolon
r_int
r_int
id|indirect_blocks
op_assign
id|sbi-&gt;s_ind_per_block
comma
id|double_blocks
op_assign
id|sbi-&gt;s_ind_per_block_2
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_block_map: block &lt; 0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|block
OL
id|DIRECT
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|block
op_sub_assign
id|DIRECT
)paren
OL
id|indirect_blocks
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|DIRECT
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|block
op_sub_assign
id|indirect_blocks
)paren
OL
id|double_blocks
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|DIRECT
op_plus
l_int|1
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_rshift
id|ptrs_bits
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_amp
(paren
id|indirect_blocks
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|block
op_sub_assign
id|double_blocks
)paren
op_rshift
(paren
id|ptrs_bits
op_star
l_int|2
)paren
)paren
OL
id|indirect_blocks
)paren
(brace
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|DIRECT
op_plus
l_int|2
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_rshift
(paren
id|ptrs_bits
op_star
l_int|2
)paren
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
(paren
id|block
op_rshift
id|ptrs_bits
)paren
op_amp
(paren
id|indirect_blocks
op_minus
l_int|1
)paren
suffix:semicolon
id|offsets
(braket
id|n
op_increment
)braket
op_assign
id|block
op_amp
(paren
id|indirect_blocks
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|block_to_cpu
r_static
r_inline
r_int
id|block_to_cpu
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|u32
id|nr
)paren
(brace
r_return
id|sbi-&gt;s_block_base
op_plus
id|fs32_to_cpu
c_func
(paren
id|sbi
comma
id|nr
)paren
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|p
id|u32
op_star
id|p
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
DECL|typedef|Indirect
)brace
id|Indirect
suffix:semicolon
DECL|variable|pointers_lock
r_static
id|rwlock_t
id|pointers_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|add_chain
r_static
r_inline
r_void
id|add_chain
c_func
(paren
id|Indirect
op_star
id|p
comma
r_struct
id|buffer_head
op_star
id|bh
comma
id|u32
op_star
id|v
)paren
(brace
id|p-&gt;key
op_assign
op_star
(paren
id|p-&gt;p
op_assign
id|v
)paren
suffix:semicolon
id|p-&gt;bh
op_assign
id|bh
suffix:semicolon
)brace
DECL|function|verify_chain
r_static
r_inline
r_int
id|verify_chain
c_func
(paren
id|Indirect
op_star
id|from
comma
id|Indirect
op_star
id|to
)paren
(brace
r_while
c_loop
(paren
id|from
op_le
id|to
op_logical_and
id|from-&gt;key
op_eq
op_star
id|from-&gt;p
)paren
id|from
op_increment
suffix:semicolon
r_return
(paren
id|from
OG
id|to
)paren
suffix:semicolon
)brace
DECL|function|block_end
r_static
r_inline
id|u32
op_star
id|block_end
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
(paren
id|u32
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
id|bh-&gt;b_size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Requires read_lock(&amp;pointers_lock) or write_lock(&amp;pointers_lock)&n; */
DECL|function|get_branch
r_static
id|Indirect
op_star
id|get_branch
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|depth
comma
r_int
id|offsets
(braket
)braket
comma
id|Indirect
id|chain
(braket
)braket
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|Indirect
op_star
id|p
op_assign
id|chain
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
op_star
id|err
op_assign
l_int|0
suffix:semicolon
id|add_chain
c_func
(paren
id|chain
comma
l_int|NULL
comma
id|SYSV_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
op_plus
op_star
id|offsets
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;key
)paren
r_goto
id|no_block
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|depth
)paren
(brace
r_int
id|block
op_assign
id|block_to_cpu
c_func
(paren
id|SYSV_SB
c_func
(paren
id|sb
)paren
comma
id|p-&gt;key
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|failure
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_chain
c_func
(paren
id|chain
comma
id|p
)paren
)paren
r_goto
id|changed
suffix:semicolon
id|add_chain
c_func
(paren
op_increment
id|p
comma
id|bh
comma
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_plus
op_star
op_increment
id|offsets
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;key
)paren
r_goto
id|no_block
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
id|changed
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|no_block
suffix:semicolon
id|failure
suffix:colon
op_star
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|no_block
suffix:colon
r_return
id|p
suffix:semicolon
)brace
DECL|function|alloc_branch
r_static
r_int
id|alloc_branch
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|num
comma
r_int
op_star
id|offsets
comma
id|Indirect
op_star
id|branch
)paren
(brace
r_int
id|blocksize
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|branch
(braket
l_int|0
)braket
dot
id|key
op_assign
id|sysv_new_block
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|branch
(braket
l_int|0
)braket
dot
id|key
)paren
r_for
c_loop
(paren
id|n
op_assign
l_int|1
suffix:semicolon
id|n
OL
id|num
suffix:semicolon
id|n
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|parent
suffix:semicolon
multiline_comment|/* Allocate the next block */
id|branch
(braket
id|n
)braket
dot
id|key
op_assign
id|sysv_new_block
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch
(braket
id|n
)braket
dot
id|key
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get buffer_head for parent block, zero it out and set &n;&t;&t; * the pointer to new one, then send parent to disk.&n;&t;&t; */
id|parent
op_assign
id|block_to_cpu
c_func
(paren
id|SYSV_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
comma
id|branch
(braket
id|n
op_minus
l_int|1
)braket
dot
id|key
)paren
suffix:semicolon
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|inode-&gt;i_sb
comma
id|parent
)paren
suffix:semicolon
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|memset
c_func
(paren
id|bh-&gt;b_data
comma
l_int|0
comma
id|blocksize
)paren
suffix:semicolon
id|branch
(braket
id|n
)braket
dot
id|bh
op_assign
id|bh
suffix:semicolon
id|branch
(braket
id|n
)braket
dot
id|p
op_assign
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
op_plus
id|offsets
(braket
id|n
)braket
suffix:semicolon
op_star
id|branch
(braket
id|n
)braket
dot
id|p
op_assign
id|branch
(braket
id|n
)braket
dot
id|key
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|dirty_indirect
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_eq
id|num
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Allocation failed, free what we already allocated */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
id|bforget
c_func
(paren
id|branch
(braket
id|i
)braket
dot
id|bh
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|sysv_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|branch
(braket
id|i
)braket
dot
id|key
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|splice_branch
r_static
r_inline
r_int
id|splice_branch
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|Indirect
id|chain
(braket
)braket
comma
id|Indirect
op_star
id|where
comma
r_int
id|num
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Verify that place we are splicing to is still there and vacant */
id|write_lock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_chain
c_func
(paren
id|chain
comma
id|where
op_minus
l_int|1
)paren
op_logical_or
op_star
id|where-&gt;p
)paren
r_goto
id|changed
suffix:semicolon
op_star
id|where-&gt;p
op_assign
id|where-&gt;key
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
multiline_comment|/* had we spliced it onto indirect block? */
r_if
c_cond
(paren
id|where-&gt;bh
)paren
id|dirty_indirect
c_func
(paren
id|where-&gt;bh
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
)paren
id|sysv_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|changed
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
id|bforget
c_func
(paren
id|where
(braket
id|i
)braket
dot
id|bh
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
id|num
suffix:semicolon
id|i
op_increment
)paren
id|sysv_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|where
(braket
id|i
)braket
dot
id|key
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|get_block
r_static
r_int
id|get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
id|offsets
(braket
id|DEPTH
)braket
suffix:semicolon
id|Indirect
id|chain
(braket
id|DEPTH
)braket
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|Indirect
op_star
id|partial
suffix:semicolon
r_int
id|left
suffix:semicolon
r_int
id|depth
op_assign
id|block_to_path
c_func
(paren
id|inode
comma
id|iblock
comma
id|offsets
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|reread
suffix:colon
id|read_lock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
id|partial
op_assign
id|get_branch
c_func
(paren
id|inode
comma
id|depth
comma
id|offsets
comma
id|chain
comma
op_amp
id|err
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
multiline_comment|/* Simplest case - block found, no allocation needed */
r_if
c_cond
(paren
op_logical_neg
id|partial
)paren
(brace
id|got_it
suffix:colon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
id|block_to_cpu
c_func
(paren
id|SYSV_SB
c_func
(paren
id|sb
)paren
comma
id|chain
(braket
id|depth
op_minus
l_int|1
)braket
dot
id|key
)paren
)paren
suffix:semicolon
multiline_comment|/* Clean up and exit */
id|partial
op_assign
id|chain
op_plus
id|depth
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* the whole chain */
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Next simple case - plain lookup or failed read of indirect block */
r_if
c_cond
(paren
op_logical_neg
id|create
op_logical_or
id|err
op_eq
op_minus
id|EIO
)paren
(brace
id|cleanup
suffix:colon
r_while
c_loop
(paren
id|partial
OG
id|chain
)paren
(brace
id|brelse
c_func
(paren
id|partial-&gt;bh
)paren
suffix:semicolon
id|partial
op_decrement
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Indirect block might be removed by truncate while we were&n;&t; * reading it. Handling of that case (forget what we&squot;ve got and&n;&t; * reread) is taken out of the main path.&n;&t; */
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EAGAIN
)paren
r_goto
id|changed
suffix:semicolon
id|left
op_assign
(paren
id|chain
op_plus
id|depth
)paren
op_minus
id|partial
suffix:semicolon
id|err
op_assign
id|alloc_branch
c_func
(paren
id|inode
comma
id|left
comma
id|offsets
op_plus
(paren
id|partial
op_minus
id|chain
)paren
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|cleanup
suffix:semicolon
r_if
c_cond
(paren
id|splice_branch
c_func
(paren
id|inode
comma
id|chain
comma
id|partial
comma
id|left
)paren
OL
l_int|0
)paren
r_goto
id|changed
suffix:semicolon
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
r_goto
id|got_it
suffix:semicolon
id|changed
suffix:colon
r_while
c_loop
(paren
id|partial
OG
id|chain
)paren
(brace
id|brelse
c_func
(paren
id|partial-&gt;bh
)paren
suffix:semicolon
id|partial
op_decrement
suffix:semicolon
)brace
r_goto
id|reread
suffix:semicolon
)brace
DECL|function|all_zeroes
r_static
r_inline
r_int
id|all_zeroes
c_func
(paren
id|u32
op_star
id|p
comma
id|u32
op_star
id|q
)paren
(brace
r_while
c_loop
(paren
id|p
OL
id|q
)paren
r_if
c_cond
(paren
op_star
id|p
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|find_shared
r_static
id|Indirect
op_star
id|find_shared
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|depth
comma
r_int
id|offsets
(braket
)braket
comma
id|Indirect
id|chain
(braket
)braket
comma
id|u32
op_star
id|top
)paren
(brace
id|Indirect
op_star
id|partial
comma
op_star
id|p
suffix:semicolon
r_int
id|k
comma
id|err
suffix:semicolon
op_star
id|top
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|depth
suffix:semicolon
id|k
OG
l_int|1
op_logical_and
op_logical_neg
id|offsets
(braket
id|k
op_minus
l_int|1
)braket
suffix:semicolon
id|k
op_decrement
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
id|partial
op_assign
id|get_branch
c_func
(paren
id|inode
comma
id|k
comma
id|offsets
comma
id|chain
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|partial
)paren
id|partial
op_assign
id|chain
op_plus
id|k
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * If the branch acquired continuation since we&squot;ve looked at it -&n;&t; * fine, it should all survive and (new) top doesn&squot;t belong to us.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|partial-&gt;key
op_logical_and
op_star
id|partial-&gt;p
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
r_goto
id|no_top
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|partial
suffix:semicolon
id|p
OG
id|chain
op_logical_and
id|all_zeroes
c_func
(paren
(paren
id|u32
op_star
)paren
id|p-&gt;bh-&gt;b_data
comma
id|p-&gt;p
)paren
suffix:semicolon
id|p
op_decrement
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * OK, we&squot;ve found the last block that must survive. The rest of our&n;&t; * branch should be detached before unlocking. However, if that rest&n;&t; * of branch is all ours and does not grow immediately from the inode&n;&t; * it&squot;s easier to cheat and just decrement partial-&gt;p.&n;&t; */
r_if
c_cond
(paren
id|p
op_eq
id|chain
op_plus
id|k
op_minus
l_int|1
op_logical_and
id|p
OG
id|chain
)paren
(brace
id|p-&gt;p
op_decrement
suffix:semicolon
)brace
r_else
(brace
op_star
id|top
op_assign
op_star
id|p-&gt;p
suffix:semicolon
op_star
id|p-&gt;p
op_assign
l_int|0
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|pointers_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|partial
OG
id|p
)paren
(brace
id|brelse
c_func
(paren
id|partial-&gt;bh
)paren
suffix:semicolon
id|partial
op_decrement
suffix:semicolon
)brace
id|no_top
suffix:colon
r_return
id|partial
suffix:semicolon
)brace
DECL|function|free_data
r_static
r_inline
r_void
id|free_data
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|p
comma
id|u32
op_star
id|q
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|p
OL
id|q
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u32
id|nr
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|nr
)paren
(brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|sysv_free_block
c_func
(paren
id|inode-&gt;i_sb
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|free_branches
r_static
r_void
id|free_branches
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
op_star
id|p
comma
id|u32
op_star
id|q
comma
r_int
id|depth
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_decrement
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|p
OL
id|q
suffix:semicolon
id|p
op_increment
)paren
(brace
r_int
id|block
suffix:semicolon
id|u32
id|nr
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
r_continue
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|block_to_cpu
c_func
(paren
id|SYSV_SB
c_func
(paren
id|sb
)paren
comma
id|nr
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_continue
suffix:semicolon
id|free_branches
c_func
(paren
id|inode
comma
(paren
id|u32
op_star
)paren
id|bh-&gt;b_data
comma
id|block_end
c_func
(paren
id|bh
)paren
comma
id|depth
)paren
suffix:semicolon
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sysv_free_block
c_func
(paren
id|sb
comma
id|nr
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_else
id|free_data
c_func
(paren
id|inode
comma
id|p
comma
id|q
)paren
suffix:semicolon
)brace
DECL|function|sysv_truncate
r_void
id|sysv_truncate
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|u32
op_star
id|i_data
op_assign
id|SYSV_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
suffix:semicolon
r_int
id|offsets
(braket
id|DEPTH
)braket
suffix:semicolon
id|Indirect
id|chain
(braket
id|DEPTH
)braket
suffix:semicolon
id|Indirect
op_star
id|partial
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_int
id|n
suffix:semicolon
r_int
id|iblock
suffix:semicolon
r_int
id|blocksize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
)paren
r_return
suffix:semicolon
id|blocksize
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
id|iblock
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|blocksize
op_minus
l_int|1
)paren
op_rshift
id|inode-&gt;i_sb-&gt;s_blocksize_bits
suffix:semicolon
id|block_truncate_page
c_func
(paren
id|inode-&gt;i_mapping
comma
id|inode-&gt;i_size
comma
id|get_block
)paren
suffix:semicolon
id|n
op_assign
id|block_to_path
c_func
(paren
id|inode
comma
id|iblock
comma
id|offsets
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|1
)paren
(brace
id|free_data
c_func
(paren
id|inode
comma
id|i_data
op_plus
id|offsets
(braket
l_int|0
)braket
comma
id|i_data
op_plus
id|DIRECT
)paren
suffix:semicolon
r_goto
id|do_indirects
suffix:semicolon
)brace
id|partial
op_assign
id|find_shared
c_func
(paren
id|inode
comma
id|n
comma
id|offsets
comma
id|chain
comma
op_amp
id|nr
)paren
suffix:semicolon
multiline_comment|/* Kill the top of shared branch (already detached) */
r_if
c_cond
(paren
id|nr
)paren
(brace
r_if
c_cond
(paren
id|partial
op_eq
id|chain
)paren
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
id|dirty_indirect
c_func
(paren
id|partial-&gt;bh
comma
id|inode
)paren
suffix:semicolon
id|free_branches
c_func
(paren
id|inode
comma
op_amp
id|nr
comma
op_amp
id|nr
op_plus
l_int|1
comma
(paren
id|chain
op_plus
id|n
op_minus
l_int|1
)paren
op_minus
id|partial
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the ends of indirect blocks on the shared branch */
r_while
c_loop
(paren
id|partial
OG
id|chain
)paren
(brace
id|free_branches
c_func
(paren
id|inode
comma
id|partial-&gt;p
op_plus
l_int|1
comma
id|block_end
c_func
(paren
id|partial-&gt;bh
)paren
comma
(paren
id|chain
op_plus
id|n
op_minus
l_int|1
)paren
op_minus
id|partial
)paren
suffix:semicolon
id|dirty_indirect
c_func
(paren
id|partial-&gt;bh
comma
id|inode
)paren
suffix:semicolon
id|brelse
(paren
id|partial-&gt;bh
)paren
suffix:semicolon
id|partial
op_decrement
suffix:semicolon
)brace
id|do_indirects
suffix:colon
multiline_comment|/* Kill the remaining (whole) subtrees (== subtrees deeper than...) */
r_while
c_loop
(paren
id|n
OL
id|DEPTH
)paren
(brace
id|nr
op_assign
id|i_data
(braket
id|DIRECT
op_plus
id|n
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nr
)paren
(brace
id|i_data
(braket
id|DIRECT
op_plus
id|n
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|free_branches
c_func
(paren
id|inode
comma
op_amp
id|nr
comma
op_amp
id|nr
op_plus
l_int|1
comma
id|n
)paren
suffix:semicolon
)brace
id|n
op_increment
suffix:semicolon
)brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
)paren
id|sysv_sync_inode
(paren
id|inode
)paren
suffix:semicolon
r_else
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|sysv_nblocks
r_static
r_int
id|sysv_nblocks
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|loff_t
id|size
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|ptrs_bits
op_assign
id|sbi-&gt;s_ind_per_block_bits
suffix:semicolon
r_int
id|blocks
comma
id|res
comma
id|direct
op_assign
id|DIRECT
comma
id|i
op_assign
id|DEPTH
suffix:semicolon
id|blocks
op_assign
(paren
id|size
op_plus
id|s-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|s-&gt;s_blocksize_bits
suffix:semicolon
id|res
op_assign
id|blocks
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_logical_and
id|blocks
OG
id|direct
)paren
(brace
id|blocks
op_assign
(paren
(paren
id|blocks
op_minus
id|direct
op_minus
l_int|1
)paren
op_rshift
id|ptrs_bits
)paren
op_plus
l_int|1
suffix:semicolon
id|res
op_add_assign
id|blocks
suffix:semicolon
id|direct
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|blocks
suffix:semicolon
)brace
DECL|function|sysv_getattr
r_int
id|sysv_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|mnt-&gt;mnt_sb
suffix:semicolon
id|generic_fillattr
c_func
(paren
id|dentry-&gt;d_inode
comma
id|stat
)paren
suffix:semicolon
id|stat-&gt;blocks
op_assign
(paren
id|s-&gt;s_blocksize
op_div
l_int|512
)paren
op_star
id|sysv_nblocks
c_func
(paren
id|s
comma
id|stat-&gt;size
)paren
suffix:semicolon
id|stat-&gt;blksize
op_assign
id|s-&gt;s_blocksize
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysv_writepage
r_static
r_int
id|sysv_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|get_block
comma
id|wbc
)paren
suffix:semicolon
)brace
DECL|function|sysv_readpage
r_static
r_int
id|sysv_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|get_block
)paren
suffix:semicolon
)brace
DECL|function|sysv_prepare_write
r_static
r_int
id|sysv_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|get_block
)paren
suffix:semicolon
)brace
DECL|function|sysv_bmap
r_static
id|sector_t
id|sysv_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|sector_t
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|get_block
)paren
suffix:semicolon
)brace
DECL|variable|sysv_aops
r_struct
id|address_space_operations
id|sysv_aops
op_assign
(brace
dot
id|readpage
op_assign
id|sysv_readpage
comma
dot
id|writepage
op_assign
id|sysv_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|sysv_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|sysv_bmap
)brace
suffix:semicolon
eof
