multiline_comment|/*&n; * inode.c - basic inode and dentry operations.&n; *&n; * sysfs is Copyright (c) 2001-3 Patrick Mochel&n; *&n; * Please see Documentation/filesystems/sysfs.txt for more information.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG 
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
r_extern
r_struct
id|super_block
op_star
id|sysfs_sb
suffix:semicolon
DECL|variable|sysfs_aops
r_static
r_struct
id|address_space_operations
id|sysfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|simple_readpage
comma
dot
id|prepare_write
op_assign
id|simple_prepare_write
comma
dot
id|commit_write
op_assign
id|simple_commit_write
)brace
suffix:semicolon
DECL|variable|sysfs_backing_dev_info
r_static
r_struct
id|backing_dev_info
id|sysfs_backing_dev_info
op_assign
(brace
dot
id|ra_pages
op_assign
l_int|0
comma
multiline_comment|/* No readahead */
dot
id|memory_backed
op_assign
l_int|1
comma
multiline_comment|/* Does not contribute to dirty memory */
)brace
suffix:semicolon
DECL|function|sysfs_new_inode
r_struct
id|inode
op_star
id|sysfs_new_inode
c_func
(paren
id|mode_t
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
id|sysfs_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
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
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|sysfs_aops
suffix:semicolon
id|inode-&gt;i_mapping-&gt;backing_dev_info
op_assign
op_amp
id|sysfs_backing_dev_info
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|sysfs_create
r_int
id|sysfs_create
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|inode
op_star
)paren
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
(paren
id|inode
op_assign
id|sysfs_new_inode
c_func
(paren
id|mode
)paren
)paren
)paren
r_goto
id|Proceed
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Proceed
suffix:colon
r_if
c_cond
(paren
id|init
)paren
id|error
op_assign
id|init
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Extra count - pin the dentry in core */
)brace
r_else
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_mknod
r_int
id|sysfs_mknod
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
r_int
id|mode
comma
id|dev_t
id|dev
)paren
(brace
r_return
id|sysfs_create
c_func
(paren
id|dentry
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|sysfs_get_dentry
r_struct
id|dentry
op_star
id|sysfs_get_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|qstr
id|qstr
suffix:semicolon
id|qstr.name
op_assign
id|name
suffix:semicolon
id|qstr.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|qstr.hash
op_assign
id|full_name_hash
c_func
(paren
id|name
comma
id|qstr.len
)paren
suffix:semicolon
r_return
id|lookup_hash
c_func
(paren
op_amp
id|qstr
comma
id|parent
)paren
suffix:semicolon
)brace
DECL|function|sysfs_hash_and_remove
r_void
id|sysfs_hash_and_remove
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|dentry
op_star
id|victim
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|victim
op_assign
id|sysfs_get_dentry
c_func
(paren
id|dir
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|victim
)paren
)paren
(brace
multiline_comment|/* make sure dentry is really there */
r_if
c_cond
(paren
id|victim-&gt;d_inode
op_logical_and
(paren
id|victim-&gt;d_parent-&gt;d_inode
op_eq
id|dir-&gt;d_inode
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;sysfs: Removing %s (%d)&bslash;n&quot;
comma
id|victim-&gt;d_name.name
comma
id|atomic_read
c_func
(paren
op_amp
id|victim-&gt;d_count
)paren
)paren
suffix:semicolon
id|d_delete
c_func
(paren
id|victim
)paren
suffix:semicolon
id|simple_unlink
c_func
(paren
id|dir-&gt;d_inode
comma
id|victim
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Drop reference from sysfs_get_dentry() above.&n;&t;&t; */
id|dput
c_func
(paren
id|victim
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
eof
