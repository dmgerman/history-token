multiline_comment|/*&n; * bin.c - binary file operations for sysfs.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|variable|bin_fops
r_static
r_struct
id|file_operations
id|bin_fops
suffix:semicolon
DECL|function|fill_read
r_static
r_int
id|fill_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
)paren
(brace
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;data
)paren
id|attr
op_member_access_from_pointer
id|read
c_func
(paren
id|kobj
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer-&gt;size
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|flush_read
r_static
r_int
id|flush_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|userbuf
comma
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
)paren
(brace
r_return
id|copy_to_user
c_func
(paren
id|userbuf
comma
id|buffer-&gt;data
op_plus
id|buffer-&gt;offset
comma
id|buffer-&gt;count
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|read
id|read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|userbuf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|fill_read
c_func
(paren
id|file
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|Done
suffix:semicolon
id|buffer-&gt;offset
op_assign
op_star
id|off
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
id|buffer-&gt;size
op_minus
op_star
id|off
)paren
)paren
id|count
op_assign
id|buffer-&gt;size
op_minus
op_star
id|off
suffix:semicolon
id|buffer-&gt;count
op_assign
id|count
suffix:semicolon
id|ret
op_assign
id|flush_read
c_func
(paren
id|file
comma
id|userbuf
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
op_star
id|off
op_add_assign
id|count
suffix:semicolon
id|ret
op_assign
id|count
suffix:semicolon
)brace
id|Done
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|alloc_buf_data
r_int
id|alloc_buf_data
c_func
(paren
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
)paren
(brace
id|buffer-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|buffer-&gt;count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;data
)paren
(brace
id|memset
c_func
(paren
id|buffer-&gt;data
comma
l_int|0
comma
id|buffer-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|fill_write
r_static
r_int
id|fill_write
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
id|userbuf
comma
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
)paren
(brace
r_return
id|copy_from_user
c_func
(paren
id|buffer
comma
id|userbuf
comma
id|buffer-&gt;count
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|flush_write
r_static
r_int
id|flush_write
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
id|userbuf
comma
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
)paren
(brace
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
r_return
id|attr
op_member_access_from_pointer
id|write
c_func
(paren
id|kobj
comma
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|write
r_static
id|ssize_t
id|write
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
id|userbuf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
id|buffer-&gt;count
op_assign
id|count
suffix:semicolon
id|ret
op_assign
id|alloc_buf_data
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|Done
suffix:semicolon
id|ret
op_assign
id|fill_write
c_func
(paren
id|file
comma
id|userbuf
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|Done
suffix:semicolon
id|ret
op_assign
id|flush_write
c_func
(paren
id|file
comma
id|userbuf
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
op_star
id|off
op_add_assign
id|count
suffix:semicolon
id|Done
suffix:colon
r_if
c_cond
(paren
id|buffer-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|buffer-&gt;data
)paren
suffix:semicolon
id|buffer-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|check_perm
r_static
r_int
id|check_perm
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
id|kobject
op_star
id|kobj
op_assign
id|kobject_get
c_func
(paren
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
)paren
suffix:semicolon
r_struct
id|bin_attribute
op_star
id|attr
op_assign
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|sysfs_bin_buffer
op_star
id|buffer
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|attr
)paren
r_goto
id|Einval
suffix:semicolon
multiline_comment|/* File needs write support.&n;&t; * The inode&squot;s perms must say it&squot;s ok, &n;&t; * and we must have a store method.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
id|S_IWUGO
)paren
op_logical_or
op_logical_neg
id|attr-&gt;write
)paren
r_goto
id|Eaccess
suffix:semicolon
)brace
multiline_comment|/* File needs read support.&n;&t; * The inode&squot;s perms must say it&squot;s ok, and we there&n;&t; * must be a show method for it.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
id|S_IRUGO
)paren
op_logical_or
op_logical_neg
id|attr-&gt;read
)paren
r_goto
id|Eaccess
suffix:semicolon
)brace
id|buffer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sysfs_bin_buffer
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
(brace
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sysfs_bin_buffer
)paren
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|buffer
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Einval
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Eaccess
suffix:colon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
id|Done
suffix:colon
r_if
c_cond
(paren
id|error
op_logical_and
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|open
r_static
r_int
id|open
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
r_return
id|check_perm
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|release
r_static
r_int
id|release
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
id|kobject
op_star
id|kobj
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bin_fops
r_static
r_struct
id|file_operations
id|bin_fops
op_assign
(brace
dot
id|read
op_assign
id|read
comma
dot
id|write
op_assign
id|write
comma
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|open
op_assign
id|open
comma
dot
id|release
op_assign
id|release
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;sysfs_create_bin_file - create binary file for object.&n; *&t;@kobj:&t;object.&n; *&t;@attr:&t;attribute descriptor.&n; *&n; */
DECL|function|sysfs_create_bin_file
r_int
id|sysfs_create_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|attr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|parent
op_assign
id|kobj-&gt;dentry
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|sysfs_get_dentry
c_func
(paren
id|parent
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
id|dentry-&gt;d_fsdata
op_assign
(paren
r_void
op_star
)paren
id|attr
suffix:semicolon
id|error
op_assign
id|sysfs_create
c_func
(paren
id|dentry
comma
(paren
id|attr-&gt;attr.mode
op_amp
id|S_IALLUGO
)paren
op_or
id|S_IFREG
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|dentry-&gt;d_inode-&gt;i_size
op_assign
id|attr-&gt;size
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_fop
op_assign
op_amp
id|bin_fops
suffix:semicolon
)brace
)brace
r_else
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_remove_bin_file - remove binary file for object.&n; *&t;@kobj:&t;object.&n; *&t;@attr:&t;attribute descriptor.&n; *&n; */
DECL|function|sysfs_remove_bin_file
r_int
id|sysfs_remove_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
)paren
(brace
id|sysfs_hash_and_remove
c_func
(paren
id|kobj-&gt;dentry
comma
id|attr-&gt;attr.name
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_create_bin_file
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_create_bin_file
)paren
suffix:semicolon
DECL|variable|sysfs_remove_bin_file
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_remove_bin_file
)paren
suffix:semicolon
eof
