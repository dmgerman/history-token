multiline_comment|/*&n; *  linux/fs/fat/file.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *&n; *  regular file handling primitives for fat-based filesystems&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
r_static
id|ssize_t
id|fat_file_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
id|__user
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
suffix:semicolon
DECL|variable|fat_file_operations
r_struct
id|file_operations
id|fat_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|write
op_assign
id|fat_file_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|fsync
op_assign
id|file_fsync
comma
dot
id|readv
op_assign
id|generic_file_readv
comma
dot
id|writev
op_assign
id|generic_file_writev
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|fat_file_inode_operations
r_struct
id|inode_operations
id|fat_file_inode_operations
op_assign
(brace
dot
id|truncate
op_assign
id|fat_truncate
comma
dot
id|setattr
op_assign
id|fat_notify_change
comma
)brace
suffix:semicolon
DECL|function|fat_get_block
r_int
id|fat_get_block
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
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|sector_t
id|phys
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|fat_bmap
c_func
(paren
id|inode
comma
id|iblock
comma
op_amp
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|phys
)paren
(brace
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
op_ne
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;corrupted file size (i_pos %lld, %lld)&quot;
comma
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pos
comma
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
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
op_logical_neg
(paren
(paren
r_int
r_int
)paren
id|iblock
op_amp
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|sec_per_clus
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|fat_add_cluster
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
)brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_add_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|err
op_assign
id|fat_bmap
c_func
(paren
id|inode
comma
id|iblock
comma
op_amp
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys
)paren
id|BUG
c_func
(paren
)paren
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
id|sb
comma
id|phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fat_file_write
r_static
id|ssize_t
id|fat_file_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
id|__user
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
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|generic_file_write
c_func
(paren
id|filp
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
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fat_truncate
r_void
id|fat_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_const
r_int
r_int
id|cluster_size
op_assign
id|sbi-&gt;cluster_size
suffix:semicolon
r_int
id|nr_clusters
suffix:semicolon
multiline_comment|/* &n;&t; * This protects against truncating a file bigger than it was then&n;&t; * trying to write into the hole.&n;&t; */
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
OG
id|inode-&gt;i_size
)paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|nr_clusters
op_assign
(paren
id|inode-&gt;i_size
op_plus
(paren
id|cluster_size
op_minus
l_int|1
)paren
)paren
op_rshift
id|sbi-&gt;cluster_bits
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fat_free
c_func
(paren
id|inode
comma
id|nr_clusters
)paren
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
eof
