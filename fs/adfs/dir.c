multiline_comment|/*&n; *  linux/fs/adfs/dir.c&n; *&n; *  Copyright (C) 1999-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Common directory handling for ADFS&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;adfs.h&quot;
multiline_comment|/*&n; * For future.  This should probably be per-directory.&n; */
DECL|variable|adfs_dir_lock
r_static
id|rwlock_t
id|adfs_dir_lock
suffix:semicolon
r_static
r_int
DECL|function|adfs_readdir
id|adfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|adfs_dir_ops
op_star
id|ops
op_assign
id|sb-&gt;u.adfs_sb.s_dir
suffix:semicolon
r_struct
id|object_info
id|obj
suffix:semicolon
r_struct
id|adfs_dir
id|dir
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_rshift
l_int|32
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|read
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_size
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
l_int|0
comma
id|inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|free_out
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
l_int|1
comma
id|dir.parent_id
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|free_out
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
l_int|1
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|setpos
c_func
(paren
op_amp
id|dir
comma
id|filp-&gt;f_pos
op_minus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|unlock_out
suffix:semicolon
r_while
c_loop
(paren
id|ops
op_member_access_from_pointer
id|getnext
c_func
(paren
op_amp
id|dir
comma
op_amp
id|obj
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|obj.name
comma
id|obj.name_len
comma
id|filp-&gt;f_pos
comma
id|obj.file_id
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
r_goto
id|unlock_out
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
l_int|1
suffix:semicolon
)brace
id|unlock_out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|free_out
suffix:colon
id|ops
op_member_access_from_pointer
id|free
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|adfs_dir_update
id|adfs_dir_update
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|object_info
op_star
id|obj
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
macro_line|#ifdef CONFIG_ADFS_FS_RW
r_struct
id|adfs_dir_ops
op_star
id|ops
op_assign
id|sb-&gt;u.adfs_sb.s_dir
suffix:semicolon
r_struct
id|adfs_dir
id|dir
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;adfs_dir_update: object %06X in dir %06X&bslash;n&quot;
comma
id|obj-&gt;file_id
comma
id|obj-&gt;parent_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;update
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|read
c_func
(paren
id|sb
comma
id|obj-&gt;parent_id
comma
l_int|0
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|update
c_func
(paren
op_amp
id|dir
comma
id|obj
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|ops
op_member_access_from_pointer
id|free
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|adfs_match
id|adfs_match
c_func
(paren
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|object_info
op_star
id|obj
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|name-&gt;len
op_ne
id|obj-&gt;name_len
)paren
r_return
l_int|0
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
id|name-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c1
comma
id|c2
suffix:semicolon
id|c1
op_assign
id|name-&gt;name
(braket
id|i
)braket
suffix:semicolon
id|c2
op_assign
id|obj-&gt;name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c1
op_le
l_char|&squot;Z&squot;
)paren
id|c1
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c2
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c2
op_le
l_char|&squot;Z&squot;
)paren
id|c2
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|adfs_dir_lookup_byname
id|adfs_dir_lookup_byname
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|object_info
op_star
id|obj
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
id|adfs_dir_ops
op_star
id|ops
op_assign
id|sb-&gt;u.adfs_sb.s_dir
suffix:semicolon
r_struct
id|adfs_dir
id|dir
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|read
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_size
comma
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|parent_id
op_ne
id|dir.parent_id
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;parent directory changed under me! (%lx but got %lx)&bslash;n&quot;
comma
id|ADFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|parent_id
comma
id|dir.parent_id
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|free_out
suffix:semicolon
)brace
id|obj-&gt;parent_id
op_assign
id|inode-&gt;i_ino
suffix:semicolon
multiline_comment|/*&n;&t; * &squot;.&squot; is handled by reserved_lookup() in fs/namei.c&n;&t; */
r_if
c_cond
(paren
id|name-&gt;len
op_eq
l_int|2
op_logical_and
id|name-&gt;name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|name-&gt;name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t; * Currently unable to fill in the rest of &squot;obj&squot;,&n;&t;&t; * but this is better than nothing.  We need to&n;&t;&t; * ascend one level to find it&squot;s parent.&n;&t;&t; */
id|obj-&gt;name_len
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;file_id
op_assign
id|obj-&gt;parent_id
suffix:semicolon
r_goto
id|free_out
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|ret
op_assign
id|ops
op_member_access_from_pointer
id|setpos
c_func
(paren
op_amp
id|dir
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|unlock_out
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_while
c_loop
(paren
id|ops
op_member_access_from_pointer
id|getnext
c_func
(paren
op_amp
id|dir
comma
id|obj
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|adfs_match
c_func
(paren
id|name
comma
id|obj
)paren
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|unlock_out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|adfs_dir_lock
)paren
suffix:semicolon
id|free_out
suffix:colon
id|ops
op_member_access_from_pointer
id|free
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|adfs_dir_operations
r_struct
id|file_operations
id|adfs_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|adfs_readdir
comma
id|fsync
suffix:colon
id|file_fsync
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|adfs_hash
id|adfs_hash
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|qstr
op_star
id|qstr
)paren
(brace
r_const
r_int
r_int
id|name_len
op_assign
id|parent-&gt;d_sb-&gt;u.adfs_sb.s_namelen
suffix:semicolon
r_const
r_int
r_char
op_star
id|name
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|qstr-&gt;len
OL
id|name_len
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Truncate the name in place, avoids&n;&t; * having to define a compare function.&n;&t; */
id|qstr-&gt;len
op_assign
id|i
op_assign
id|name_len
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
(brace
r_char
id|c
suffix:semicolon
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
id|c
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|c
comma
id|hash
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Compare two names, taking note of the name length&n; * requirements of the underlying filesystem.&n; */
r_static
r_int
DECL|function|adfs_compare
id|adfs_compare
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|qstr
op_star
id|entry
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;len
op_ne
id|name-&gt;len
)paren
r_return
l_int|1
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
id|name-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|a
comma
id|b
suffix:semicolon
id|a
op_assign
id|entry-&gt;name
(braket
id|i
)braket
suffix:semicolon
id|b
op_assign
id|name-&gt;name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ge
l_char|&squot;A&squot;
op_logical_and
id|a
op_le
l_char|&squot;Z&squot;
)paren
id|a
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|b
op_ge
l_char|&squot;A&squot;
op_logical_and
id|b
op_le
l_char|&squot;Z&squot;
)paren
id|b
op_add_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ne
id|b
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|adfs_dentry_operations
r_struct
id|dentry_operations
id|adfs_dentry_operations
op_assign
(brace
id|d_hash
suffix:colon
id|adfs_hash
comma
id|d_compare
suffix:colon
id|adfs_compare
comma
)brace
suffix:semicolon
DECL|function|adfs_lookup
r_struct
id|dentry
op_star
id|adfs_lookup
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
l_int|NULL
suffix:semicolon
r_struct
id|object_info
id|obj
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|adfs_dentry_operations
suffix:semicolon
id|error
op_assign
id|adfs_dir_lookup_byname
c_func
(paren
id|dir
comma
op_amp
id|dentry-&gt;d_name
comma
op_amp
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This only returns NULL if get_empty_inode&n;&t;&t; * fails.&n;&t;&t; */
id|inode
op_assign
id|adfs_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|error
op_assign
l_int|0
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
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * directories can handle most operations...&n; */
DECL|variable|adfs_dir_inode_operations
r_struct
id|inode_operations
id|adfs_dir_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|adfs_lookup
comma
id|setattr
suffix:colon
id|adfs_notify_change
comma
)brace
suffix:semicolon
eof
