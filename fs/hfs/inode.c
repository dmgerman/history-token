multiline_comment|/*&n; *  linux/fs/hfs/inode.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains inode-related functions which do not depend on&n; * which scheme is being used to represent forks.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; */
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &quot;hfs_fs.h&quot;
macro_line|#include &quot;btree.h&quot;
multiline_comment|/*================ Variable-like macros ================*/
DECL|macro|HFS_VALID_MODE_BITS
mdefine_line|#define HFS_VALID_MODE_BITS  (S_IFREG | S_IFDIR | S_IRWXUGO)
DECL|function|hfs_writepage
r_static
r_int
id|hfs_writepage
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
id|hfs_get_block
comma
id|wbc
)paren
suffix:semicolon
)brace
DECL|function|hfs_readpage
r_static
r_int
id|hfs_readpage
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
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfs_prepare_write
r_static
r_int
id|hfs_prepare_write
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
id|hfs_get_block
comma
op_amp
id|HFS_I
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
op_member_access_from_pointer
id|phys_size
)paren
suffix:semicolon
)brace
DECL|function|hfs_bmap
r_static
id|sector_t
id|hfs_bmap
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
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfs_releasepage
r_int
id|hfs_releasepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|mask
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|node
suffix:semicolon
id|u32
id|nidx
suffix:semicolon
r_int
id|i
comma
id|res
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|inode-&gt;i_ino
)paren
(brace
r_case
id|HFS_EXT_CNID
suffix:colon
id|tree
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|ext_tree
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_CAT_CNID
suffix:colon
id|tree
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cat_tree
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tree-&gt;node_size
op_ge
id|PAGE_CACHE_SIZE
)paren
(brace
id|nidx
op_assign
id|page-&gt;index
op_rshift
(paren
id|tree-&gt;node_size_shift
op_minus
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
id|node
op_assign
id|hfs_bnode_findhash
c_func
(paren
id|tree
comma
id|nidx
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
id|res
op_assign
l_int|0
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|tree-&gt;pages_per_bnode
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|PageActive
c_func
(paren
id|node-&gt;page
(braket
id|i
)braket
)paren
)paren
(brace
id|res
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|res
op_logical_and
id|node
)paren
(brace
id|hfs_bnode_unhash
c_func
(paren
id|node
)paren
suffix:semicolon
id|hfs_bnode_free
c_func
(paren
id|node
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|nidx
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|tree-&gt;node_size_shift
)paren
suffix:semicolon
id|i
op_assign
l_int|1
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|tree-&gt;node_size_shift
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
r_do
(brace
id|node
op_assign
id|hfs_bnode_findhash
c_func
(paren
id|tree
comma
id|nidx
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|node-&gt;refcnt
)paren
)paren
(brace
id|res
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hfs_bnode_unhash
c_func
(paren
id|node
)paren
suffix:semicolon
id|hfs_bnode_free
c_func
(paren
id|node
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
op_logical_and
id|nidx
OL
id|tree-&gt;node_count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tree-&gt;hash_lock
)paren
suffix:semicolon
)brace
singleline_comment|//printk(&quot;releasepage: %lu,%x = %d&bslash;n&quot;, page-&gt;index, mask, res);
r_return
id|res
suffix:semicolon
)brace
DECL|function|hfs_get_blocks
r_static
r_int
id|hfs_get_blocks
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
r_int
r_int
id|max_blocks
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
id|ret
suffix:semicolon
id|ret
op_assign
id|hfs_get_block
c_func
(paren
id|inode
comma
id|iblock
comma
id|bh_result
comma
id|create
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|bh_result-&gt;b_size
op_assign
(paren
l_int|1
op_lshift
id|inode-&gt;i_blkbits
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hfs_direct_IO
r_static
id|ssize_t
id|hfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|kiocb
op_star
id|iocb
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping-&gt;host
suffix:semicolon
r_return
id|blockdev_direct_IO
c_func
(paren
id|rw
comma
id|iocb
comma
id|inode
comma
id|inode-&gt;i_sb-&gt;s_bdev
comma
id|iov
comma
id|offset
comma
id|nr_segs
comma
id|hfs_get_blocks
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|hfs_writepages
r_static
r_int
id|hfs_writepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_return
id|mpage_writepages
c_func
(paren
id|mapping
comma
id|wbc
comma
id|hfs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|hfs_btree_aops
r_struct
id|address_space_operations
id|hfs_btree_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hfs_readpage
comma
dot
id|writepage
op_assign
id|hfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|hfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|hfs_bmap
comma
dot
id|releasepage
op_assign
id|hfs_releasepage
comma
)brace
suffix:semicolon
DECL|variable|hfs_aops
r_struct
id|address_space_operations
id|hfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hfs_readpage
comma
dot
id|writepage
op_assign
id|hfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|hfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|hfs_bmap
comma
dot
id|direct_IO
op_assign
id|hfs_direct_IO
comma
dot
id|writepages
op_assign
id|hfs_writepages
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * hfs_new_inode&n; */
DECL|function|hfs_new_inode
r_struct
id|inode
op_star
id|hfs_new_inode
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_int
id|mode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|NULL
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|extents_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|open_dir_list
)paren
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
(paren
id|btree_key
op_star
)paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cat_key
comma
id|dir-&gt;i_ino
comma
id|name
)paren
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|next_id
op_increment
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|2
suffix:semicolon
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|folder_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|HFS_ROOT_CNID
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|root_dirs
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|clump_blocks
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clumpablks
suffix:semicolon
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|file_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|HFS_ROOT_CNID
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|root_files
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|phys_size
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|alloc_blocks
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|first_blocks
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cached_start
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cached_blocks
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|first_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfs_extent_rec
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cached_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfs_extent_rec
)paren
)paren
suffix:semicolon
)brace
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|HFS_FLG_MDB_DIRTY
comma
op_amp
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|hfs_delete_inode
r_void
id|hfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_INODE
comma
l_string|&quot;delete_inode: %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|folder_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cat_key.ParID
op_eq
id|cpu_to_be32
c_func
(paren
id|HFS_ROOT_CNID
)paren
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|root_dirs
op_decrement
suffix:semicolon
id|set_bit
c_func
(paren
id|HFS_FLG_MDB_DIRTY
comma
op_amp
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|file_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cat_key.ParID
op_eq
id|cpu_to_be32
c_func
(paren
id|HFS_ROOT_CNID
)paren
)paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|root_files
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|hfs_file_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
id|set_bit
c_func
(paren
id|HFS_FLG_MDB_DIRTY
comma
op_amp
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|hfs_inode_read_fork
r_void
id|hfs_inode_read_fork
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_extent
op_star
id|ext
comma
id|__be32
id|__log_size
comma
id|__be32
id|phys_size
comma
id|u32
id|clump_size
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|u32
id|log_size
op_assign
id|be32_to_cpu
c_func
(paren
id|__log_size
)paren
suffix:semicolon
id|u16
id|count
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|first_extents
comma
id|ext
comma
r_sizeof
(paren
id|hfs_extent_rec
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|count
op_add_assign
id|be16_to_cpu
c_func
(paren
id|ext
(braket
id|i
)braket
dot
id|count
)paren
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|first_blocks
op_assign
id|count
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|phys_size
op_assign
id|log_size
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|log_size
op_plus
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|alloc_blocks
op_assign
id|be32_to_cpu
c_func
(paren
id|phys_size
)paren
op_div
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|alloc_blksz
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|clump_blocks
op_assign
id|clump_size
op_div
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|alloc_blksz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|clump_blocks
)paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|clump_blocks
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clumpablks
suffix:semicolon
)brace
DECL|struct|hfs_iget_data
r_struct
id|hfs_iget_data
(brace
DECL|member|key
r_struct
id|hfs_cat_key
op_star
id|key
suffix:semicolon
DECL|member|rec
id|hfs_cat_rec
op_star
id|rec
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hfs_test_inode
r_int
id|hfs_test_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|hfs_iget_data
op_star
id|idata
op_assign
id|data
suffix:semicolon
id|hfs_cat_rec
op_star
id|rec
suffix:semicolon
id|rec
op_assign
id|idata-&gt;rec
suffix:semicolon
r_switch
c_cond
(paren
id|rec-&gt;type
)paren
(brace
r_case
id|HFS_CDR_DIR
suffix:colon
r_return
id|inode-&gt;i_ino
op_eq
id|be32_to_cpu
c_func
(paren
id|rec-&gt;dir.DirID
)paren
suffix:semicolon
r_case
id|HFS_CDR_FIL
suffix:colon
r_return
id|inode-&gt;i_ino
op_eq
id|be32_to_cpu
c_func
(paren
id|rec-&gt;file.FlNum
)paren
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * hfs_read_inode&n; */
DECL|function|hfs_read_inode
r_int
id|hfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|hfs_iget_data
op_star
id|idata
op_assign
id|data
suffix:semicolon
r_struct
id|hfs_sb_info
op_star
id|hsb
op_assign
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|hfs_cat_rec
op_star
id|rec
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
op_assign
l_int|NULL
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|extents_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|open_dir_list
)paren
suffix:semicolon
multiline_comment|/* Initialize the inode */
id|inode-&gt;i_uid
op_assign
id|hsb-&gt;s_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|hsb-&gt;s_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|idata-&gt;key
)paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cat_key
op_assign
op_star
id|idata-&gt;key
suffix:semicolon
r_else
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|HFS_FLG_RSRC
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|tz_secondswest
op_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
id|rec
op_assign
id|idata-&gt;rec
suffix:semicolon
r_switch
c_cond
(paren
id|rec-&gt;type
)paren
(brace
r_case
id|HFS_CDR_FIL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|HFS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
(brace
id|hfs_inode_read_fork
c_func
(paren
id|inode
comma
id|rec-&gt;file.ExtRec
comma
id|rec-&gt;file.LgLen
comma
id|rec-&gt;file.PyLen
comma
id|be16_to_cpu
c_func
(paren
id|rec-&gt;file.ClpSize
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|hfs_inode_read_fork
c_func
(paren
id|inode
comma
id|rec-&gt;file.RExtRec
comma
id|rec-&gt;file.RLgLen
comma
id|rec-&gt;file.RPyLen
comma
id|be16_to_cpu
c_func
(paren
id|rec-&gt;file.ClpSize
)paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|rec-&gt;file.FlNum
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rec-&gt;file.Flags
op_amp
id|HFS_FIL_LOCK
)paren
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_IWUGO
suffix:semicolon
id|inode-&gt;i_mode
op_and_assign
id|hsb-&gt;s_file_umask
suffix:semicolon
id|inode-&gt;i_mode
op_or_assign
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|hfs_m_to_utime
c_func
(paren
id|rec-&gt;file.MdDat
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfs_aops
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|phys_size
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_CDR_DIR
suffix:colon
id|inode-&gt;i_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|rec-&gt;dir.DirID
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|be16_to_cpu
c_func
(paren
id|rec-&gt;dir.Val
)paren
op_plus
l_int|2
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
(paren
id|S_IRWXUGO
op_amp
id|hsb-&gt;s_dir_umask
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|hfs_m_to_utime
c_func
(paren
id|rec-&gt;file.MdDat
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfs_dir_operations
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * __hfs_iget()&n; *&n; * Given the MDB for a HFS filesystem, a &squot;key&squot; and an &squot;entry&squot; in&n; * the catalog B-tree and the &squot;type&squot; of the desired file return the&n; * inode for that file/directory or NULL.  Note that &squot;type&squot; indicates&n; * whether we want the actual file or directory, or the corresponding&n; * metadata (AppleDouble header file or CAP metadata file).&n; */
DECL|function|hfs_iget
r_struct
id|inode
op_star
id|hfs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|hfs_cat_key
op_star
id|key
comma
id|hfs_cat_rec
op_star
id|rec
)paren
(brace
r_struct
id|hfs_iget_data
id|data
op_assign
(brace
id|key
comma
id|rec
)brace
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|u32
id|cnid
suffix:semicolon
r_switch
c_cond
(paren
id|rec-&gt;type
)paren
(brace
r_case
id|HFS_CDR_DIR
suffix:colon
id|cnid
op_assign
id|be32_to_cpu
c_func
(paren
id|rec-&gt;dir.DirID
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFS_CDR_FIL
suffix:colon
id|cnid
op_assign
id|be32_to_cpu
c_func
(paren
id|rec-&gt;file.FlNum
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inode
op_assign
id|iget5_locked
c_func
(paren
id|sb
comma
id|cnid
comma
id|hfs_test_inode
comma
id|hfs_read_inode
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_logical_and
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
)paren
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|hfs_inode_write_fork
r_void
id|hfs_inode_write_fork
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_extent
op_star
id|ext
comma
id|__be32
op_star
id|log_size
comma
id|__be32
op_star
id|phys_size
)paren
(brace
id|memcpy
c_func
(paren
id|ext
comma
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|first_extents
comma
r_sizeof
(paren
id|hfs_extent_rec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_size
)paren
op_star
id|log_size
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys_size
)paren
op_star
id|phys_size
op_assign
id|cpu_to_be32
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|alloc_blocks
op_star
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|alloc_blksz
)paren
suffix:semicolon
)brace
DECL|function|hfs_write_inode
r_int
id|hfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|unused
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|hfs_cat_rec
id|rec
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_INODE
comma
l_string|&quot;hfs_write_inode: %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|hfs_ext_write_extent
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
OL
id|HFS_FIRSTUSER_CNID
)paren
(brace
r_switch
c_cond
(paren
id|inode-&gt;i_ino
)paren
(brace
r_case
id|HFS_ROOT_CNID
suffix:colon
r_break
suffix:semicolon
r_case
id|HFS_EXT_CNID
suffix:colon
id|hfs_btree_write
c_func
(paren
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|ext_tree
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HFS_CAT_CNID
suffix:colon
id|hfs_btree_write
c_func
(paren
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cat_tree
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
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
)brace
r_if
c_cond
(paren
id|HFS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
(brace
id|mark_inode_dirty
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
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
id|inode-&gt;i_nlink
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|fd
)paren
)paren
multiline_comment|/* panic? */
r_return
op_minus
id|EIO
suffix:semicolon
id|fd.search_key-&gt;cat
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cat_key
suffix:semicolon
r_if
c_cond
(paren
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
)paren
multiline_comment|/* panic? */
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|fd.entrylength
OL
r_sizeof
(paren
r_struct
id|hfs_cat_dir
)paren
)paren
multiline_comment|/* panic? */
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|rec
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfs_cat_dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec.type
op_ne
id|HFS_CDR_DIR
op_logical_or
id|be32_to_cpu
c_func
(paren
id|rec.dir.DirID
)paren
op_ne
id|inode-&gt;i_ino
)paren
(brace
)brace
id|rec.dir.MdDat
op_assign
id|hfs_u_to_mtime
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|rec.dir.Val
op_assign
id|cpu_to_be16
c_func
(paren
id|inode-&gt;i_size
op_minus
l_int|2
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|fd.bnode
comma
op_amp
id|rec
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfs_cat_dir
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|fd.entrylength
OL
r_sizeof
(paren
r_struct
id|hfs_cat_file
)paren
)paren
multiline_comment|/* panic? */
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|rec
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfs_cat_file
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec.type
op_ne
id|HFS_CDR_FIL
op_logical_or
id|be32_to_cpu
c_func
(paren
id|rec.file.FlNum
)paren
op_ne
id|inode-&gt;i_ino
)paren
(brace
)brace
r_if
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_IWUSR
)paren
id|rec.file.Flags
op_and_assign
op_complement
id|HFS_FIL_LOCK
suffix:semicolon
r_else
id|rec.file.Flags
op_or_assign
id|HFS_FIL_LOCK
suffix:semicolon
id|hfs_inode_write_fork
c_func
(paren
id|inode
comma
id|rec.file.ExtRec
comma
op_amp
id|rec.file.LgLen
comma
op_amp
id|rec.file.PyLen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
)paren
id|hfs_inode_write_fork
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
comma
id|rec.file.RExtRec
comma
op_amp
id|rec.file.RLgLen
comma
op_amp
id|rec.file.RPyLen
)paren
suffix:semicolon
id|rec.file.MdDat
op_assign
id|hfs_u_to_mtime
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|fd.bnode
comma
op_amp
id|rec
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfs_cat_file
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfs_file_lookup
r_static
r_struct
id|dentry
op_star
id|hfs_file_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
id|hfs_cat_rec
id|rec
suffix:semicolon
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|HFS_IS_RSRC
c_func
(paren
id|dir
)paren
op_logical_or
id|strcmp
c_func
(paren
id|dentry-&gt;d_name.name
comma
l_string|&quot;rsrc&quot;
)paren
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|rsrc_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|fd.search_key-&gt;cat
op_assign
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|cat_key
suffix:semicolon
id|res
op_assign
id|hfs_brec_read
c_func
(paren
op_amp
id|fd
comma
op_amp
id|rec
comma
r_sizeof
(paren
id|rec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_struct
id|hfs_iget_data
id|idata
op_assign
(brace
l_int|NULL
comma
op_amp
id|rec
)brace
suffix:semicolon
id|hfs_read_inode
c_func
(paren
id|inode
comma
op_amp
id|idata
)paren
suffix:semicolon
)brace
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
op_assign
id|dir
suffix:semicolon
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|rsrc_inode
op_assign
id|inode
suffix:semicolon
id|igrab
c_func
(paren
id|dir
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|inode-&gt;i_hash
comma
op_amp
id|HFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|rsrc_inodes
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hfs_clear_inode
r_void
id|hfs_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|HFS_IS_RSRC
c_func
(paren
id|inode
)paren
op_logical_and
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
)paren
(brace
id|HFS_I
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
)paren
op_member_access_from_pointer
id|rsrc_inode
op_assign
l_int|NULL
suffix:semicolon
id|iput
c_func
(paren
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|hfs_permission
r_static
r_int
id|hfs_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|mask
op_amp
id|MAY_EXEC
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|vfs_permission
c_func
(paren
id|inode
comma
id|mask
)paren
suffix:semicolon
)brace
DECL|function|hfs_file_open
r_static
r_int
id|hfs_file_open
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
r_if
c_cond
(paren
id|HFS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
id|inode
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|file-&gt;f_count
)paren
op_ne
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opencnt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfs_file_release
r_static
r_int
id|hfs_file_release
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
singleline_comment|//struct super_block *sb = inode-&gt;i_sb;
r_if
c_cond
(paren
id|HFS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
id|inode
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsrc_inode
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|file-&gt;f_count
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|opencnt
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|hfs_file_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
singleline_comment|//if (inode-&gt;i_flags &amp; S_DEAD) {
singleline_comment|//&t;hfs_delete_cat(inode-&gt;i_ino, HFSPLUS_SB(sb).hidden_dir, NULL);
singleline_comment|//&t;hfs_delete_inode(inode);
singleline_comment|//}
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_notify_change()&n; *&n; * Based very closely on fs/msdos/inode.c by Werner Almesberger&n; *&n; * This is the notify_change() field in the super_operations structure&n; * for HFS file systems.  The purpose is to take that changes made to&n; * an inode and apply then in a filesystem-dependent manner.  In this&n; * case the process has a few of tasks to do:&n; *  1) prevent changes to the i_uid and i_gid fields.&n; *  2) map file permissions to the closest allowable permissions&n; *  3) Since multiple Linux files can share the same on-disk inode under&n; *     HFS (for instance the data and resource forks of a file) a change&n; *     to permissions must be applied to all other in-core inodes which&n; *     correspond to the same HFS file.&n; */
DECL|function|hfs_inode_setattr
r_int
id|hfs_inode_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|hfs_sb_info
op_star
id|hsb
op_assign
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
multiline_comment|/* basic permission checks */
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* no uig/gid changes and limit which mode bits can be set */
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|attr-&gt;ia_uid
op_ne
id|hsb-&gt;s_uid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
id|attr-&gt;ia_gid
op_ne
id|hsb-&gt;s_gid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
op_logical_and
(paren
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
(paren
id|attr-&gt;ia_mode
op_ne
id|inode-&gt;i_mode
)paren
)paren
op_logical_or
(paren
id|attr-&gt;ia_mode
op_amp
op_complement
id|HFS_VALID_MODE_BITS
)paren
)paren
)paren
)paren
(brace
r_return
id|hsb-&gt;s_quiet
ques
c_cond
l_int|0
suffix:colon
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
multiline_comment|/* Only the &squot;w&squot; bits can ever change and only all together. */
r_if
c_cond
(paren
id|attr-&gt;ia_mode
op_amp
id|S_IWUSR
)paren
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
op_or
id|S_IWUGO
suffix:semicolon
r_else
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
op_amp
op_complement
id|S_IWUGO
suffix:semicolon
id|attr-&gt;ia_mode
op_and_assign
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
ques
c_cond
op_complement
id|hsb-&gt;s_dir_umask
suffix:colon
op_complement
id|hsb-&gt;s_file_umask
suffix:semicolon
)brace
id|error
op_assign
id|inode_setattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hfs_file_operations
r_struct
id|file_operations
id|hfs_file_operations
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
id|generic_file_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
dot
id|fsync
op_assign
id|file_fsync
comma
dot
id|open
op_assign
id|hfs_file_open
comma
dot
id|release
op_assign
id|hfs_file_release
comma
)brace
suffix:semicolon
DECL|variable|hfs_file_inode_operations
r_struct
id|inode_operations
id|hfs_file_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|hfs_file_lookup
comma
dot
id|truncate
op_assign
id|hfs_file_truncate
comma
dot
id|setattr
op_assign
id|hfs_inode_setattr
comma
dot
id|permission
op_assign
id|hfs_permission
comma
)brace
suffix:semicolon
eof
