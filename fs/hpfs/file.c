multiline_comment|/*&n; *  linux/fs/hpfs/file.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  file VFS functions&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;hpfs_fn.h&quot;
DECL|macro|BLOCKS
mdefine_line|#define BLOCKS(size) (((size) + 511) &gt;&gt; 9)
multiline_comment|/* HUH? */
DECL|function|hpfs_open
r_int
id|hpfs_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|hpfs_lock_inode
c_func
(paren
id|i
)paren
suffix:semicolon
id|hpfs_unlock_inode
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/* make sure nobody is deleting the file */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i-&gt;i_nlink
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_file_release
r_int
id|hpfs_file_release
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
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|hpfs_write_if_changed
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_file_fsync
r_int
id|hpfs_file_fsync
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
multiline_comment|/*return file_fsync(file, dentry);*/
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t fsync :-) */
)brace
multiline_comment|/*&n; * generic_file_read often calls bmap with non-existing sector,&n; * so we must ignore such errors.&n; */
DECL|function|hpfs_bmap
id|secno
id|hpfs_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|file_secno
)paren
(brace
r_struct
id|hpfs_inode_info
op_star
id|hpfs_inode
op_assign
id|hpfs_i
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|n
comma
id|disk_secno
suffix:semicolon
r_struct
id|fnode
op_star
id|fnode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|BLOCKS
c_func
(paren
id|hpfs_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
)paren
op_le
id|file_secno
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
id|file_secno
op_minus
id|hpfs_inode-&gt;i_file_sec
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|hpfs_inode-&gt;i_n_secs
)paren
r_return
id|hpfs_inode-&gt;i_disk_sec
op_plus
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fnode
op_assign
id|hpfs_map_fnode
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|disk_secno
op_assign
id|hpfs_bplus_lookup
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode
comma
op_amp
id|fnode-&gt;btree
comma
id|file_secno
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk_secno
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hpfs_chk_sectors
c_func
(paren
id|inode-&gt;i_sb
comma
id|disk_secno
comma
l_int|1
comma
l_string|&quot;bmap&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|disk_secno
suffix:semicolon
)brace
DECL|function|hpfs_truncate
r_void
id|hpfs_truncate
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|i
)paren
)paren
r_return
multiline_comment|/*-EPERM*/
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|hpfs_i
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|i_n_secs
op_assign
l_int|0
suffix:semicolon
id|i-&gt;i_blocks
op_assign
l_int|1
op_plus
(paren
(paren
id|i-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
id|hpfs_i
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|i-&gt;i_size
suffix:semicolon
id|hpfs_truncate_btree
c_func
(paren
id|i-&gt;i_sb
comma
id|i-&gt;i_ino
comma
l_int|1
comma
(paren
(paren
id|i-&gt;i_size
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
)paren
suffix:semicolon
id|hpfs_write_inode
c_func
(paren
id|i
)paren
suffix:semicolon
id|hpfs_i
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|i_n_secs
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|hpfs_get_block
r_int
id|hpfs_get_block
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
id|secno
id|s
suffix:semicolon
id|s
op_assign
id|hpfs_bmap
c_func
(paren
id|inode
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
id|map_bh
c_func
(paren
id|bh_result
comma
id|inode-&gt;i_sb
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iblock
op_lshift
l_int|9
op_ne
id|hpfs_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|s
op_assign
id|hpfs_add_sector_to_btree
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
l_int|1
comma
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|hpfs_truncate_btree
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
l_int|1
comma
id|inode-&gt;i_blocks
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_increment
suffix:semicolon
id|hpfs_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_add_assign
l_int|512
suffix:semicolon
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
id|map_bh
c_func
(paren
id|bh_result
comma
id|inode-&gt;i_sb
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_writepage
r_static
r_int
id|hpfs_writepage
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
id|hpfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hpfs_readpage
r_static
r_int
id|hpfs_readpage
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
id|hpfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hpfs_prepare_write
r_static
r_int
id|hpfs_prepare_write
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
id|cont_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|hpfs_get_block
comma
op_amp
id|hpfs_i
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
op_member_access_from_pointer
id|mmu_private
)paren
suffix:semicolon
)brace
DECL|function|_hpfs_bmap
r_static
id|sector_t
id|_hpfs_bmap
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
id|hpfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|hpfs_aops
r_struct
id|address_space_operations
id|hpfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hpfs_readpage
comma
dot
id|writepage
op_assign
id|hpfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|hpfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|_hpfs_bmap
)brace
suffix:semicolon
DECL|function|hpfs_file_write
id|ssize_t
id|hpfs_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|ssize_t
id|retval
suffix:semicolon
id|retval
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|hpfs_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_dirty
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
