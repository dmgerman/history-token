multiline_comment|/*&n; *&t;fs/bfs/file.c&n; *&t;BFS file operations.&n; *&t;Copyright (C) 1999,2000 Tigran Aivazian &lt;tigran@veritas.com&gt;&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/bfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;bfs_defs.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)&t;printf(x)
macro_line|#else
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)
macro_line|#endif
DECL|variable|bfs_file_operations
r_struct
id|file_operations
id|bfs_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|generic_file_read
comma
id|write
suffix:colon
id|generic_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
)brace
suffix:semicolon
DECL|function|bfs_move_block
r_static
r_int
id|bfs_move_block
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
r_new
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_new
op_assign
id|sb_getblk
c_func
(paren
id|sb
comma
id|to
)paren
suffix:semicolon
id|memcpy
c_func
(paren
r_new
op_member_access_from_pointer
id|b_data
comma
id|bh-&gt;b_data
comma
id|bh-&gt;b_size
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
r_new
)paren
suffix:semicolon
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfs_move_blocks
r_static
r_int
id|bfs_move_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
r_int
id|where
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|dprintf
c_func
(paren
l_string|&quot;%08lx-%08lx-&gt;%08lx&bslash;n&quot;
comma
id|start
comma
id|end
comma
id|where
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
op_le
id|end
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bfs_move_block
c_func
(paren
id|i
comma
id|where
op_plus
id|i
comma
id|sb
)paren
)paren
(brace
id|dprintf
c_func
(paren
l_string|&quot;failed to move block %08lx -&gt; %08lx&bslash;n&quot;
comma
id|i
comma
id|where
op_plus
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfs_get_block
r_static
r_int
id|bfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|block
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
id|phys
suffix:semicolon
r_int
id|err
suffix:semicolon
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
id|sbh
op_assign
id|sb-&gt;su_sbh
suffix:semicolon
r_if
c_cond
(paren
id|block
template_param
id|sb-&gt;su_blocks
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|phys
op_assign
id|inode-&gt;iu_sblock
op_plus
id|block
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
(brace
r_if
c_cond
(paren
id|phys
op_le
id|inode-&gt;iu_eblock
)paren
(brace
id|dprintf
c_func
(paren
l_string|&quot;c=%d, b=%08lx, phys=%08lx (granted)&bslash;n&quot;
comma
id|create
comma
id|block
comma
id|phys
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
id|phys
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* if the file is not empty and the requested block is within the range&n;&t;   of blocks allocated for this file, we can grant it */
r_if
c_cond
(paren
id|inode-&gt;i_size
op_logical_and
id|phys
op_le
id|inode-&gt;iu_eblock
)paren
(brace
id|dprintf
c_func
(paren
l_string|&quot;c=%d, b=%08lx, phys=%08lx (interim block granted)&bslash;n&quot;
comma
id|create
comma
id|block
comma
id|phys
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
id|phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* the rest has to be protected against itself */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if the last data block for this file is the last allocated block, we can&n;&t;   extend the file trivially, without moving it anywhere */
r_if
c_cond
(paren
id|inode-&gt;iu_eblock
op_eq
id|sb-&gt;su_lf_eblk
)paren
(brace
id|dprintf
c_func
(paren
l_string|&quot;c=%d, b=%08lx, phys=%08lx (simple extension)&bslash;n&quot;
comma
id|create
comma
id|block
comma
id|phys
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
id|phys
)paren
suffix:semicolon
id|sb-&gt;su_freeb
op_sub_assign
id|phys
op_minus
id|inode-&gt;iu_eblock
suffix:semicolon
id|sb-&gt;su_lf_eblk
op_assign
id|inode-&gt;iu_eblock
op_assign
id|phys
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbh
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Ok, we have to move this entire file to the next free block */
id|phys
op_assign
id|sb-&gt;su_lf_eblk
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;iu_sblock
)paren
(brace
multiline_comment|/* if data starts on block 0 then there is no data */
id|err
op_assign
id|bfs_move_blocks
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;iu_sblock
comma
id|inode-&gt;iu_eblock
comma
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|dprintf
c_func
(paren
l_string|&quot;failed to move ino=%08lx -&gt; fs corruption&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
id|err
op_assign
l_int|0
suffix:semicolon
id|dprintf
c_func
(paren
l_string|&quot;c=%d, b=%08lx, phys=%08lx (moved)&bslash;n&quot;
comma
id|create
comma
id|block
comma
id|phys
)paren
suffix:semicolon
id|inode-&gt;iu_sblock
op_assign
id|phys
suffix:semicolon
id|phys
op_add_assign
id|block
suffix:semicolon
id|sb-&gt;su_lf_eblk
op_assign
id|inode-&gt;iu_eblock
op_assign
id|phys
suffix:semicolon
multiline_comment|/* this assumes nothing can write the inode back while we are here&n;&t; * and thus update inode-&gt;i_blocks! (XXX)*/
id|sb-&gt;su_freeb
op_sub_assign
id|inode-&gt;iu_eblock
op_minus
id|inode-&gt;iu_sblock
op_plus
l_int|1
op_minus
id|inode-&gt;i_blocks
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbh
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|sb
comma
id|phys
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bfs_writepage
r_static
r_int
id|bfs_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|bfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|bfs_readpage
r_static
r_int
id|bfs_readpage
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
id|bfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|bfs_prepare_write
r_static
r_int
id|bfs_prepare_write
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
id|bfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|bfs_bmap
r_static
r_int
id|bfs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
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
id|bfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|bfs_aops
r_struct
id|address_space_operations
id|bfs_aops
op_assign
(brace
id|readpage
suffix:colon
id|bfs_readpage
comma
id|writepage
suffix:colon
id|bfs_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|bfs_prepare_write
comma
id|commit_write
suffix:colon
id|generic_commit_write
comma
id|bmap
suffix:colon
id|bfs_bmap
comma
)brace
suffix:semicolon
DECL|variable|bfs_file_inops
r_struct
id|inode_operations
id|bfs_file_inops
suffix:semicolon
eof
