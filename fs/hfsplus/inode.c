multiline_comment|/*&n; *  linux/fs/hfsplus/inode.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Inode handling routines&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &quot;hfsplus_fs.h&quot;
macro_line|#include &quot;hfsplus_raw.h&quot;
DECL|function|hfsplus_readpage
r_static
r_int
id|hfsplus_readpage
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
singleline_comment|//printk(&quot;readpage: %lu&bslash;n&quot;, page-&gt;index);
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|hfsplus_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_writepage
r_static
r_int
id|hfsplus_writepage
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
singleline_comment|//printk(&quot;writepage: %lu&bslash;n&quot;, page-&gt;index);
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|hfsplus_get_block
comma
id|wbc
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_prepare_write
r_static
r_int
id|hfsplus_prepare_write
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
id|hfsplus_get_block
comma
op_amp
id|HFSPLUS_I
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
dot
id|phys_size
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_bmap
r_static
id|sector_t
id|hfsplus_bmap
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
id|hfsplus_get_block
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_releasepage
r_int
id|hfsplus_releasepage
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
id|HFSPLUS_EXT_CNID
suffix:colon
id|tree
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|ext_tree
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFSPLUS_CAT_CNID
suffix:colon
id|tree
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|cat_tree
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HFSPLUS_ATTR_CNID
suffix:colon
id|tree
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|attr_tree
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
DECL|function|hfsplus_get_blocks
r_static
r_int
id|hfsplus_get_blocks
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
id|hfsplus_get_block
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
DECL|function|hfsplus_direct_IO
r_static
id|ssize_t
id|hfsplus_direct_IO
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
id|hfsplus_get_blocks
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_writepages
r_static
r_int
id|hfsplus_writepages
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
id|hfsplus_get_block
)paren
suffix:semicolon
)brace
DECL|variable|hfsplus_btree_aops
r_struct
id|address_space_operations
id|hfsplus_btree_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hfsplus_readpage
comma
dot
id|writepage
op_assign
id|hfsplus_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|hfsplus_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|hfsplus_bmap
comma
dot
id|releasepage
op_assign
id|hfsplus_releasepage
comma
)brace
suffix:semicolon
DECL|variable|hfsplus_aops
r_struct
id|address_space_operations
id|hfsplus_aops
op_assign
(brace
dot
id|readpage
op_assign
id|hfsplus_readpage
comma
dot
id|writepage
op_assign
id|hfsplus_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|prepare_write
op_assign
id|hfsplus_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|hfsplus_bmap
comma
dot
id|direct_IO
op_assign
id|hfsplus_direct_IO
comma
dot
id|writepages
op_assign
id|hfsplus_writepages
comma
)brace
suffix:semicolon
DECL|function|hfsplus_file_lookup
r_static
r_struct
id|dentry
op_star
id|hfsplus_file_lookup
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
id|hfs_find_data
id|fd
suffix:semicolon
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
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_IS_RSRC
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
id|HFSPLUS_I
c_func
(paren
id|dir
)paren
dot
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
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|open_dir_list
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_assign
id|HFSPLUS_FLG_RSRC
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|err
op_assign
id|hfsplus_find_cat
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
comma
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|hfsplus_cat_read_inode
c_func
(paren
id|inode
comma
op_amp
id|fd
)paren
suffix:semicolon
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
id|err
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
id|err
)paren
suffix:semicolon
)brace
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rsrc_inode
op_assign
id|dir
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|dir
)paren
dot
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|rsrc_inodes
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
(brace
r_void
id|hfsplus_inode_check
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|inode_cnt
)paren
suffix:semicolon
id|hfsplus_inode_check
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
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
DECL|function|hfsplus_get_perms
r_static
r_void
id|hfsplus_get_perms
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfsplus_perm
op_star
id|perms
comma
r_int
id|dir
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|u16
id|mode
suffix:semicolon
id|mode
op_assign
id|be16_to_cpu
c_func
(paren
id|perms-&gt;mode
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|be32_to_cpu
c_func
(paren
id|perms-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_uid
op_logical_and
op_logical_neg
id|mode
)paren
id|inode-&gt;i_uid
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|be32_to_cpu
c_func
(paren
id|perms-&gt;group
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_gid
op_logical_and
op_logical_neg
id|mode
)paren
id|inode-&gt;i_gid
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|gid
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|mode
op_assign
id|mode
ques
c_cond
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
suffix:colon
(paren
id|S_IRWXUGO
op_amp
op_complement
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|umask
)paren
)paren
suffix:semicolon
id|mode
op_or_assign
id|S_IFDIR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
id|mode
op_assign
id|S_IFREG
op_or
(paren
(paren
id|S_IRUGO
op_or
id|S_IWUGO
)paren
op_amp
op_complement
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|umask
)paren
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rootflags
op_assign
id|perms-&gt;rootflags
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|userflags
op_assign
id|perms-&gt;userflags
suffix:semicolon
r_if
c_cond
(paren
id|perms-&gt;rootflags
op_amp
id|HFSPLUS_FLG_IMMUTABLE
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_IMMUTABLE
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_IMMUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|perms-&gt;rootflags
op_amp
id|HFSPLUS_FLG_APPEND
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_APPEND
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_APPEND
suffix:semicolon
)brace
DECL|function|hfsplus_set_perms
r_static
r_void
id|hfsplus_set_perms
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfsplus_perm
op_star
id|perms
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_flags
op_amp
id|S_IMMUTABLE
)paren
id|perms-&gt;rootflags
op_or_assign
id|HFSPLUS_FLG_IMMUTABLE
suffix:semicolon
r_else
id|perms-&gt;rootflags
op_and_assign
op_complement
id|HFSPLUS_FLG_IMMUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_flags
op_amp
id|S_APPEND
)paren
id|perms-&gt;rootflags
op_or_assign
id|HFSPLUS_FLG_APPEND
suffix:semicolon
r_else
id|perms-&gt;rootflags
op_and_assign
op_complement
id|HFSPLUS_FLG_APPEND
suffix:semicolon
id|perms-&gt;userflags
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|userflags
suffix:semicolon
id|perms-&gt;mode
op_assign
id|cpu_to_be16
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|perms-&gt;owner
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|perms-&gt;group
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|perms-&gt;dev
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|dev
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_permission
r_static
r_int
id|hfsplus_permission
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
multiline_comment|/* MAY_EXEC is also used for lookup, if no x bit is set allow lookup,&n;&t; * open_exec has the same test, so it&squot;s still not executable, if a x bit&n;&t; * is set fall back to standard permission check.&n;&t; */
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
op_logical_and
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
l_int|0111
)paren
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
DECL|function|hfsplus_file_open
r_static
r_int
id|hfsplus_file_open
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
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
id|inode
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
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
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|opencnt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hfsplus_file_release
r_static
r_int
id|hfsplus_file_release
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
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
id|inode
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
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
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
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
id|hfsplus_file_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_flags
op_amp
id|S_DEAD
)paren
(brace
id|hfsplus_delete_cat
c_func
(paren
id|inode-&gt;i_ino
comma
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|hidden_dir
comma
l_int|NULL
)paren
suffix:semicolon
id|hfsplus_delete_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
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
r_extern
r_struct
id|inode_operations
id|hfsplus_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|hfsplus_dir_operations
suffix:semicolon
DECL|variable|hfsplus_file_inode_operations
r_struct
id|inode_operations
id|hfsplus_file_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|hfsplus_file_lookup
comma
dot
id|truncate
op_assign
id|hfsplus_file_truncate
comma
dot
id|permission
op_assign
id|hfsplus_permission
comma
)brace
suffix:semicolon
DECL|variable|hfsplus_file_operations
r_struct
id|file_operations
id|hfsplus_file_operations
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
id|fsync
op_assign
id|file_fsync
comma
dot
id|open
op_assign
id|hfsplus_file_open
comma
dot
id|release
op_assign
id|hfsplus_file_release
comma
dot
id|ioctl
op_assign
id|hfsplus_ioctl
comma
)brace
suffix:semicolon
DECL|function|hfsplus_new_inode
r_struct
id|inode
op_star
id|hfsplus_new_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
)paren
(brace
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
(brace
r_void
id|hfsplus_inode_check
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|inode_cnt
)paren
suffix:semicolon
id|hfsplus_inode_check
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
id|inode-&gt;i_ino
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|next_cnid
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
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|open_dir_list
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|extents_lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|opencnt
comma
l_int|0
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rsrc_inode
op_assign
l_int|0
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|folder_count
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfsplus_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfsplus_dir_operations
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|file_count
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfsplus_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfsplus_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfsplus_aops
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|data_clump_blocks
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|file_count
op_increment
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfsplus_aops
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|file_count
op_increment
suffix:semicolon
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
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|hfsplus_delete_inode
r_void
id|hfsplus_delete_inode
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|folder_count
op_decrement
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|file_count
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
id|hfsplus_file_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|hfsplus_file_truncate
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|hfsplus_inode_read_fork
r_void
id|hfsplus_inode_read_fork
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfsplus_fork_raw
op_star
id|fork
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
id|count
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
op_amp
id|fork-&gt;extents
comma
r_sizeof
(paren
id|hfsplus_extent_rec
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|count
op_add_assign
id|be32_to_cpu
c_func
(paren
id|fork-&gt;extents
(braket
id|i
)braket
dot
id|block_count
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_blocks
op_assign
id|count
suffix:semicolon
id|memset
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_extents
comma
l_int|0
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_start
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|cached_blocks
op_assign
l_int|0
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
op_assign
id|be32_to_cpu
c_func
(paren
id|fork-&gt;total_blocks
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|phys_size
op_assign
id|be64_to_cpu
c_func
(paren
id|fork-&gt;total_size
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
op_assign
id|be32_to_cpu
c_func
(paren
id|fork-&gt;clump_size
)paren
op_rshift
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
)paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|clump_blocks
op_assign
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
ques
c_cond
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|rsrc_clump_blocks
suffix:colon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|data_clump_blocks
suffix:semicolon
)brace
DECL|function|hfsplus_inode_write_fork
r_void
id|hfsplus_inode_write_fork
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfsplus_fork_raw
op_star
id|fork
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|fork-&gt;extents
comma
op_amp
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|first_extents
comma
r_sizeof
(paren
id|hfsplus_extent_rec
)paren
)paren
suffix:semicolon
id|fork-&gt;total_size
op_assign
id|cpu_to_be64
c_func
(paren
id|inode-&gt;i_size
)paren
suffix:semicolon
id|fork-&gt;total_blocks
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|alloc_blocks
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_cat_read_inode
r_int
id|hfsplus_cat_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfs_find_data
op_star
id|fd
)paren
(brace
id|hfsplus_cat_entry
id|entry
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|u16
id|type
suffix:semicolon
id|type
op_assign
id|hfs_bnode_read_u16
c_func
(paren
id|fd-&gt;bnode
comma
id|fd-&gt;entryoffset
)paren
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|dev
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Doesn&squot;t seem to be useful... */
r_if
c_cond
(paren
id|type
op_eq
id|HFSPLUS_FOLDER
)paren
(brace
r_struct
id|hfsplus_cat_folder
op_star
id|folder
op_assign
op_amp
id|entry.folder
suffix:semicolon
r_if
c_cond
(paren
id|fd-&gt;entrylength
OL
r_sizeof
(paren
r_struct
id|hfsplus_cat_folder
)paren
)paren
multiline_comment|/* panic? */
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd-&gt;bnode
comma
op_amp
id|entry
comma
id|fd-&gt;entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_folder
)paren
)paren
suffix:semicolon
id|hfsplus_get_perms
c_func
(paren
id|inode
comma
op_amp
id|folder-&gt;permissions
comma
l_int|1
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_size
op_assign
l_int|2
op_plus
id|be32_to_cpu
c_func
(paren
id|folder-&gt;valence
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|hfsp_mt2ut
c_func
(paren
id|folder-&gt;access_date
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|hfsp_mt2ut
c_func
(paren
id|folder-&gt;content_mod_date
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfsplus_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfsplus_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|HFSPLUS_FILE
)paren
(brace
r_struct
id|hfsplus_cat_file
op_star
id|file
op_assign
op_amp
id|entry.file
suffix:semicolon
r_if
c_cond
(paren
id|fd-&gt;entrylength
OL
r_sizeof
(paren
r_struct
id|hfsplus_cat_file
)paren
)paren
multiline_comment|/* panic? */
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd-&gt;bnode
comma
op_amp
id|entry
comma
id|fd-&gt;entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_file
)paren
)paren
suffix:semicolon
id|hfsplus_inode_read_fork
c_func
(paren
id|inode
comma
id|HFSPLUS_IS_DATA
c_func
(paren
id|inode
)paren
ques
c_cond
op_amp
id|file-&gt;data_fork
suffix:colon
op_amp
id|file-&gt;rsrc_fork
)paren
suffix:semicolon
id|hfsplus_get_perms
c_func
(paren
id|inode
comma
op_amp
id|file-&gt;permissions
comma
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
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
id|file-&gt;permissions.dev
)paren
id|inode-&gt;i_nlink
op_assign
id|be32_to_cpu
c_func
(paren
id|file-&gt;permissions.dev
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|hfsplus_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|hfsplus_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfsplus_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|hfsplus_aops
suffix:semicolon
)brace
r_else
(brace
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|be32_to_cpu
c_func
(paren
id|file-&gt;permissions.dev
)paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_atime
op_assign
id|hfsp_mt2ut
c_func
(paren
id|file-&gt;access_date
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|hfsp_mt2ut
c_func
(paren
id|file-&gt;content_mod_date
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;HFS+-fs: bad catalog entry used to create inode&bslash;n&quot;
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|hfsplus_cat_write_inode
r_void
id|hfsplus_cat_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
id|hfsplus_cat_entry
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_IS_RSRC
c_func
(paren
id|inode
)paren
)paren
(brace
id|mark_inode_dirty
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rsrc_inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|cat_tree
comma
op_amp
id|fd
)paren
)paren
multiline_comment|/* panic? */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|hfsplus_find_cat
c_func
(paren
id|inode-&gt;i_sb
comma
id|inode-&gt;i_ino
comma
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
r_struct
id|hfsplus_cat_folder
op_star
id|folder
op_assign
op_amp
id|entry.folder
suffix:semicolon
r_if
c_cond
(paren
id|fd.entrylength
OL
r_sizeof
(paren
r_struct
id|hfsplus_cat_folder
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
id|entry
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_folder
)paren
)paren
suffix:semicolon
multiline_comment|/* simple node checks? */
id|hfsplus_set_perms
c_func
(paren
id|inode
comma
op_amp
id|folder-&gt;permissions
)paren
suffix:semicolon
id|folder-&gt;access_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_atime
)paren
suffix:semicolon
id|folder-&gt;content_mod_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|folder-&gt;attribute_mod_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_ctime
)paren
suffix:semicolon
id|folder-&gt;valence
op_assign
id|cpu_to_be32
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
id|entry
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_folder
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|hfsplus_cat_file
op_star
id|file
op_assign
op_amp
id|entry.file
suffix:semicolon
r_if
c_cond
(paren
id|fd.entrylength
OL
r_sizeof
(paren
r_struct
id|hfsplus_cat_file
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
id|entry
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_file
)paren
)paren
suffix:semicolon
id|hfsplus_inode_write_fork
c_func
(paren
id|inode
comma
op_amp
id|file-&gt;data_fork
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rsrc_inode
)paren
id|hfsplus_inode_write_fork
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rsrc_inode
comma
op_amp
id|file-&gt;rsrc_fork
)paren
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
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|dev
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|dev
op_assign
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|hfsplus_set_perms
c_func
(paren
id|inode
comma
op_amp
id|file-&gt;permissions
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;permissions.rootflags
op_or
id|file-&gt;permissions.userflags
)paren
op_amp
id|HFSPLUS_FLG_IMMUTABLE
)paren
id|file-&gt;flags
op_or_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_FILE_LOCKED
)paren
suffix:semicolon
r_else
id|file-&gt;flags
op_and_assign
id|cpu_to_be16
c_func
(paren
op_complement
id|HFSPLUS_FILE_LOCKED
)paren
suffix:semicolon
id|file-&gt;access_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_atime
)paren
suffix:semicolon
id|file-&gt;content_mod_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
id|file-&gt;attribute_mod_date
op_assign
id|hfsp_ut2mt
c_func
(paren
id|inode-&gt;i_ctime
)paren
suffix:semicolon
id|hfs_bnode_write
c_func
(paren
id|fd.bnode
comma
op_amp
id|entry
comma
id|fd.entryoffset
comma
r_sizeof
(paren
r_struct
id|hfsplus_cat_file
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
)brace
eof
