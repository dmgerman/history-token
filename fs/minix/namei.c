multiline_comment|/*&n; *  linux/fs/minix/namei.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &quot;minix.h&quot;
DECL|function|inc_count
r_static
r_inline
r_void
id|inc_count
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
DECL|function|dec_count
r_static
r_inline
r_void
id|dec_count
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
DECL|function|add_nondir
r_static
r_int
id|add_nondir
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
id|minix_add_link
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
id|dec_count
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
DECL|function|minix_hash
r_static
r_int
id|minix_hash
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
r_const
r_int
r_char
op_star
id|name
suffix:semicolon
id|i
op_assign
id|minix_sb
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_namelen
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|qstr-&gt;len
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Truncate the name in place, avoids having to define a compare&n;&t;   function. */
id|qstr-&gt;len
op_assign
id|i
suffix:semicolon
id|name
op_assign
id|qstr-&gt;name
suffix:semicolon
id|hash
op_assign
id|init_name_hash
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
op_star
id|name
op_increment
comma
id|hash
)paren
suffix:semicolon
id|qstr-&gt;hash
op_assign
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|minix_dentry_operations
r_struct
id|dentry_operations
id|minix_dentry_operations
op_assign
(brace
dot
id|d_hash
op_assign
id|minix_hash
comma
)brace
suffix:semicolon
DECL|function|minix_lookup
r_static
r_struct
id|dentry
op_star
id|minix_lookup
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
id|ino_t
id|ino
suffix:semicolon
id|dentry-&gt;d_op
op_assign
id|dir-&gt;i_sb-&gt;s_root-&gt;d_op
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|minix_sb
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_namelen
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
id|minix_inode_by_name
c_func
(paren
id|dentry
)paren
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
DECL|function|minix_mknod
r_static
r_int
id|minix_mknod
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
id|rdev
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_valid_dev
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
id|minix_new_inode
c_func
(paren
id|dir
comma
op_amp
id|error
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
id|minix_set_inode
c_func
(paren
id|inode
comma
id|rdev
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
id|add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|minix_create
r_static
r_int
id|minix_create
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
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_return
id|minix_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|minix_symlink
r_static
r_int
id|minix_symlink
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
r_const
r_char
op_star
id|symname
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_int
id|i
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
id|i
OG
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
r_goto
id|out
suffix:semicolon
id|inode
op_assign
id|minix_new_inode
c_func
(paren
id|dir
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
l_int|0777
suffix:semicolon
id|minix_set_inode
c_func
(paren
id|inode
comma
l_int|0
)paren
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
id|i
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
id|add_nondir
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
id|dec_count
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
r_goto
id|out
suffix:semicolon
)brace
DECL|function|minix_link
r_static
r_int
id|minix_link
c_func
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
id|minix_sb
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_link_max
)paren
r_return
op_minus
id|EMLINK
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|inc_count
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
id|add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
)brace
DECL|function|minix_mkdir
r_static
r_int
id|minix_mkdir
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
id|minix_sb
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_link_max
)paren
r_goto
id|out
suffix:semicolon
id|inc_count
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode
op_assign
id|minix_new_inode
c_func
(paren
id|dir
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_dir
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
id|inode-&gt;i_mode
op_or_assign
id|S_ISGID
suffix:semicolon
id|minix_set_inode
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
id|inc_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|minix_make_empty
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
id|minix_add_link
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
id|dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dec_count
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
id|dec_count
c_func
(paren
id|dir
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|minix_unlink
r_static
r_int
id|minix_unlink
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
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
suffix:semicolon
id|de
op_assign
id|minix_find_entry
c_func
(paren
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
id|end_unlink
suffix:semicolon
id|err
op_assign
id|minix_delete_entry
c_func
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
id|end_unlink
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
suffix:semicolon
id|dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|end_unlink
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|minix_rmdir
r_static
r_int
id|minix_rmdir
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
r_int
id|err
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|minix_empty_dir
c_func
(paren
id|inode
)paren
)paren
(brace
id|err
op_assign
id|minix_unlink
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
id|dec_count
c_func
(paren
id|dir
)paren
suffix:semicolon
id|dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|minix_rename
r_static
r_int
id|minix_rename
c_func
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
id|minix_sb_info
op_star
id|info
op_assign
id|minix_sb
c_func
(paren
id|old_dir-&gt;i_sb
)paren
suffix:semicolon
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
id|minix_dir_entry
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
id|minix_dir_entry
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
id|minix_find_entry
c_func
(paren
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
id|minix_dotdot
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
id|minix_dir_entry
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
id|minix_empty_dir
c_func
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
id|minix_find_entry
c_func
(paren
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
id|inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|minix_set_link
c_func
(paren
id|new_de
comma
id|new_page
comma
id|old_inode
)paren
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
)paren
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|dec_count
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
id|info-&gt;s_link_max
)paren
r_goto
id|out_dir
suffix:semicolon
)brace
id|inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|err
op_assign
id|minix_add_link
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
id|dec_count
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
id|inc_count
c_func
(paren
id|new_dir
)paren
suffix:semicolon
)brace
id|minix_delete_entry
c_func
(paren
id|old_de
comma
id|old_page
)paren
suffix:semicolon
id|dec_count
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
id|minix_set_link
c_func
(paren
id|dir_de
comma
id|dir_page
comma
id|new_dir
)paren
suffix:semicolon
id|dec_count
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
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|minix_dir_inode_operations
r_struct
id|inode_operations
id|minix_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|minix_create
comma
dot
id|lookup
op_assign
id|minix_lookup
comma
dot
id|link
op_assign
id|minix_link
comma
dot
id|unlink
op_assign
id|minix_unlink
comma
dot
id|symlink
op_assign
id|minix_symlink
comma
dot
id|mkdir
op_assign
id|minix_mkdir
comma
dot
id|rmdir
op_assign
id|minix_rmdir
comma
dot
id|mknod
op_assign
id|minix_mknod
comma
dot
id|rename
op_assign
id|minix_rename
comma
dot
id|getattr
op_assign
id|minix_getattr
comma
)brace
suffix:semicolon
eof
