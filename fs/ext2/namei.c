multiline_comment|/*&n; * linux/fs/ext2/namei.c&n; *&n; * Rewrite to pagecache. Almost all code had been changed, so blame me&n; * if the things go wrong. Please, send bug reports to viro@math.psu.edu&n; *&n; * Stuff here is basically a glue between the VFS and generic UNIXish&n; * filesystem that keeps everything in pagecache. All knowledge of the&n; * directory layout is in fs/ext2/dir.c - it turned out to be easily separatable&n; * and it&squot;s easier to debug that way. In principle we might want to&n; * generalize that a bit and turn it into a library. Or not.&n; *&n; * The only non-static object here is ext2_dir_inode_operations.&n; *&n; * TODO: get rid of kmap() use, add readahead.&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/namei.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &quot;xattr.h&quot;
macro_line|#include &quot;acl.h&quot;
multiline_comment|/*&n; * Couple of helper functions - make the code slightly cleaner.&n; */
DECL|function|ext2_inc_count
r_static
r_inline
r_void
id|ext2_inc_count
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ext2_dec_count
r_static
r_inline
r_void
id|ext2_dec_count
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ext2_add_nondir
r_static
r_inline
r_int
id|ext2_add_nondir
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|err
op_assign
id|ext2_add_link
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
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
r_return
l_int|0
suffix:semicolon
)brace
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Methods themselves.&n; */
DECL|function|ext2_lookup
r_static
r_struct
id|dentry
op_star
id|ext2_lookup
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
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|EXT2_NAME_LEN
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
id|ino
op_assign
id|ext2_inode_by_name
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ino
)paren
(brace
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
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
id|EACCES
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode
)paren
r_return
id|d_splice_alias
c_func
(paren
id|inode
comma
id|dentry
)paren
suffix:semicolon
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
DECL|function|ext2_get_parent
r_struct
id|dentry
op_star
id|ext2_get_parent
c_func
(paren
r_struct
id|dentry
op_star
id|child
)paren
(brace
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
id|dotdot
suffix:semicolon
id|dotdot.d_name.name
op_assign
l_string|&quot;..&quot;
suffix:semicolon
id|dotdot.d_name.len
op_assign
l_int|2
suffix:semicolon
id|ino
op_assign
id|ext2_inode_by_name
c_func
(paren
id|child-&gt;d_inode
comma
op_amp
id|dotdot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|child-&gt;d_inode-&gt;i_sb
comma
id|ino
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
id|EACCES
)paren
suffix:semicolon
id|parent
op_assign
id|d_alloc_anon
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|parent
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_return
id|parent
suffix:semicolon
)brace
multiline_comment|/*&n; * By the time this is called, we already have created&n; * the directory cache entry for the new file, but it&n; * is so far negative - it has no inode.&n; *&n; * If the create succeeds, we fill in the inode information&n; * with d_instantiate(). &n; */
DECL|function|ext2_create
r_static
r_int
id|ext2_create
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
id|ext2_new_inode
(paren
id|dir
comma
id|mode
)paren
suffix:semicolon
r_int
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ext2_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|ext2_file_operations
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|NOBH
)paren
)paren
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_nobh_aops
suffix:semicolon
r_else
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_aops
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|ext2_mknod
r_static
r_int
id|ext2_mknod
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
id|rdev
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_valid_dev
c_func
(paren
id|rdev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|inode
op_assign
id|ext2_new_inode
(paren
id|dir
comma
id|mode
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
(brace
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|rdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EXT2_FS_XATTR
id|inode-&gt;i_op
op_assign
op_amp
id|ext2_special_inode_operations
suffix:semicolon
macro_line|#endif
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|ext2_symlink
r_static
r_int
id|ext2_symlink
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
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|symname
)paren
op_plus
l_int|1
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|sb-&gt;s_blocksize
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|ext2_new_inode
(paren
id|dir
comma
id|S_IFLNK
op_or
id|S_IRWXUGO
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
r_sizeof
(paren
id|EXT2_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
)paren
)paren
(brace
multiline_comment|/* slow symlink */
id|inode-&gt;i_op
op_assign
op_amp
id|ext2_symlink_inode_operations
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|NOBH
)paren
)paren
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_nobh_aops
suffix:semicolon
r_else
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_aops
suffix:semicolon
id|err
op_assign
id|page_symlink
c_func
(paren
id|inode
comma
id|symname
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* fast symlink */
id|inode-&gt;i_op
op_assign
op_amp
id|ext2_fast_symlink_inode_operations
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|EXT2_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
)paren
comma
id|symname
comma
id|l
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|l
op_minus
l_int|1
suffix:semicolon
)brace
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_fail
suffix:colon
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ext2_link
r_static
r_int
id|ext2_link
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_ge
id|EXT2_LINK_MAX
)paren
r_return
op_minus
id|EMLINK
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|ext2_inc_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
suffix:semicolon
r_return
id|ext2_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ext2_mkdir
r_static
r_int
id|ext2_mkdir
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
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EMLINK
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_nlink
op_ge
id|EXT2_LINK_MAX
)paren
r_goto
id|out
suffix:semicolon
id|ext2_inc_count
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode
op_assign
id|ext2_new_inode
(paren
id|dir
comma
id|S_IFDIR
op_or
id|mode
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out_dir
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|ext2_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|ext2_dir_operations
suffix:semicolon
r_if
c_cond
(paren
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|NOBH
)paren
)paren
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_nobh_aops
suffix:semicolon
r_else
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ext2_aops
suffix:semicolon
id|ext2_inc_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_make_empty
c_func
(paren
id|inode
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
id|err
op_assign
id|ext2_add_link
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_fail
suffix:colon
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out_dir
suffix:colon
id|ext2_dec_count
c_func
(paren
id|dir
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ext2_unlink
r_static
r_int
id|ext2_unlink
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
id|ext2_dir_entry_2
op_star
id|de
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|de
op_assign
id|ext2_find_entry
(paren
id|dir
comma
id|dentry
comma
op_amp
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|ext2_delete_entry
(paren
id|de
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ext2_rmdir
r_static
r_int
id|ext2_rmdir
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
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|ext2_empty_dir
c_func
(paren
id|inode
)paren
)paren
(brace
id|err
op_assign
id|ext2_unlink
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|ext2_rename
r_static
r_int
id|ext2_rename
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_struct
id|inode
op_star
id|old_inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|dir_page
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ext2_dir_entry_2
op_star
id|dir_de
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|page
op_star
id|old_page
suffix:semicolon
r_struct
id|ext2_dir_entry_2
op_star
id|old_de
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|old_de
op_assign
id|ext2_find_entry
(paren
id|old_dir
comma
id|old_dentry
comma
op_amp
id|old_page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_de
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|dir_de
op_assign
id|ext2_dotdot
c_func
(paren
id|old_inode
comma
op_amp
id|dir_page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_de
)paren
r_goto
id|out_old
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_inode
)paren
(brace
r_struct
id|page
op_star
id|new_page
suffix:semicolon
r_struct
id|ext2_dir_entry_2
op_star
id|new_de
suffix:semicolon
id|err
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
op_logical_and
op_logical_neg
id|ext2_empty_dir
(paren
id|new_inode
)paren
)paren
r_goto
id|out_dir
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|new_de
op_assign
id|ext2_find_entry
(paren
id|new_dir
comma
id|new_dentry
comma
op_amp
id|new_page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_de
)paren
r_goto
id|out_dir
suffix:semicolon
id|ext2_inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|ext2_set_link
c_func
(paren
id|new_dir
comma
id|new_de
comma
id|new_page
comma
id|old_inode
)paren
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
)paren
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dir_de
)paren
(brace
id|err
op_assign
op_minus
id|EMLINK
suffix:semicolon
r_if
c_cond
(paren
id|new_dir-&gt;i_nlink
op_ge
id|EXT2_LINK_MAX
)paren
r_goto
id|out_dir
suffix:semicolon
)brace
id|ext2_inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_add_link
c_func
(paren
id|new_dentry
comma
id|old_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|ext2_dec_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
r_goto
id|out_dir
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir_de
)paren
id|ext2_inc_count
c_func
(paren
id|new_dir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Like most other Unix systems, set the ctime for inodes on a&n; &t; * rename.&n;&t; * ext2_dec_count() will mark the inode dirty.&n;&t; */
id|old_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|ext2_delete_entry
(paren
id|old_de
comma
id|old_page
)paren
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
)paren
(brace
id|ext2_set_link
c_func
(paren
id|old_inode
comma
id|dir_de
comma
id|dir_page
comma
id|new_dir
)paren
suffix:semicolon
id|ext2_dec_count
c_func
(paren
id|old_dir
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_dir
suffix:colon
r_if
c_cond
(paren
id|dir_de
)paren
(brace
id|kunmap
c_func
(paren
id|dir_page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|dir_page
)paren
suffix:semicolon
)brace
id|out_old
suffix:colon
id|kunmap
c_func
(paren
id|old_page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|old_page
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|ext2_dir_inode_operations
r_struct
id|inode_operations
id|ext2_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|ext2_create
comma
dot
id|lookup
op_assign
id|ext2_lookup
comma
dot
id|link
op_assign
id|ext2_link
comma
dot
id|unlink
op_assign
id|ext2_unlink
comma
dot
id|symlink
op_assign
id|ext2_symlink
comma
dot
id|mkdir
op_assign
id|ext2_mkdir
comma
dot
id|rmdir
op_assign
id|ext2_rmdir
comma
dot
id|mknod
op_assign
id|ext2_mknod
comma
dot
id|rename
op_assign
id|ext2_rename
comma
dot
id|setxattr
op_assign
id|ext2_setxattr
comma
dot
id|getxattr
op_assign
id|ext2_getxattr
comma
dot
id|listxattr
op_assign
id|ext2_listxattr
comma
dot
id|removexattr
op_assign
id|ext2_removexattr
comma
dot
id|setattr
op_assign
id|ext2_setattr
comma
dot
id|permission
op_assign
id|ext2_permission
comma
)brace
suffix:semicolon
DECL|variable|ext2_special_inode_operations
r_struct
id|inode_operations
id|ext2_special_inode_operations
op_assign
(brace
dot
id|setxattr
op_assign
id|ext2_setxattr
comma
dot
id|getxattr
op_assign
id|ext2_getxattr
comma
dot
id|listxattr
op_assign
id|ext2_listxattr
comma
dot
id|removexattr
op_assign
id|ext2_removexattr
comma
dot
id|setattr
op_assign
id|ext2_setattr
comma
dot
id|permission
op_assign
id|ext2_permission
comma
)brace
suffix:semicolon
eof
