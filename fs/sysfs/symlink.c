multiline_comment|/*&n; * symlink.c - operations for sysfs symlinks.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|function|init_symlink
r_static
r_int
id|init_symlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysfs_symlink
r_static
r_int
id|sysfs_symlink
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
id|error
suffix:semicolon
id|error
op_assign
id|sysfs_create
c_func
(paren
id|dentry
comma
id|S_IFLNK
op_or
id|S_IRWXUGO
comma
id|init_symlink
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
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
id|error
op_assign
id|page_symlink
c_func
(paren
id|dentry-&gt;d_inode
comma
id|symname
comma
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|iput
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|object_depth
r_static
r_int
id|object_depth
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobject
op_star
id|p
op_assign
id|kobj
suffix:semicolon
r_int
id|depth
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|depth
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|p
op_assign
id|p-&gt;parent
)paren
)paren
suffix:semicolon
r_return
id|depth
suffix:semicolon
)brace
DECL|function|object_path_length
r_static
r_int
id|object_path_length
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobject
op_star
id|p
op_assign
id|kobj
suffix:semicolon
r_int
id|length
op_assign
l_int|1
suffix:semicolon
r_do
(brace
id|length
op_add_assign
id|strlen
c_func
(paren
id|kobject_name
c_func
(paren
id|p
)paren
)paren
op_plus
l_int|1
suffix:semicolon
id|p
op_assign
id|p-&gt;parent
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|fill_object_path
r_static
r_void
id|fill_object_path
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_struct
id|kobject
op_star
id|p
suffix:semicolon
op_decrement
id|length
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|kobj
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;parent
)paren
(brace
r_int
id|cur
op_assign
id|strlen
c_func
(paren
id|kobject_name
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
multiline_comment|/* back up enough to print this bus id with &squot;/&squot; */
id|length
op_sub_assign
id|cur
suffix:semicolon
id|strncpy
c_func
(paren
id|buffer
op_plus
id|length
comma
id|kobject_name
c_func
(paren
id|p
)paren
comma
id|cur
)paren
suffix:semicolon
op_star
(paren
id|buffer
op_plus
op_decrement
id|length
)paren
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;sysfs_create_link - create symlink between two objects.&n; *&t;@kobj:&t;object whose directory we&squot;re creating the link in.&n; *&t;@target:&t;object we&squot;re pointing to.&n; *&t;@name:&t;&t;name of the symlink.&n; */
DECL|function|sysfs_create_link
r_int
id|sysfs_create_link
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|kobject
op_star
id|target
comma
r_char
op_star
id|name
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|kobj-&gt;dentry
suffix:semicolon
r_struct
id|dentry
op_star
id|d
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|depth
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
id|depth
op_assign
id|object_depth
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|size
op_assign
id|object_path_length
c_func
(paren
id|target
)paren
op_plus
id|depth
op_star
l_int|3
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|PATH_MAX
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: depth = %d, size = %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|depth
comma
id|size
)paren
suffix:semicolon
id|path
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|path
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|path
suffix:semicolon
id|depth
op_decrement
suffix:semicolon
id|s
op_add_assign
l_int|3
)paren
id|strcpy
c_func
(paren
id|s
comma
l_string|&quot;../&quot;
)paren
suffix:semicolon
id|fill_object_path
c_func
(paren
id|target
comma
id|path
comma
id|size
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: path = &squot;%s&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|path
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|d
op_assign
id|sysfs_get_dentry
c_func
(paren
id|dentry
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
id|d
)paren
)paren
id|error
op_assign
id|sysfs_symlink
c_func
(paren
id|dentry-&gt;d_inode
comma
id|d
comma
id|path
)paren
suffix:semicolon
r_else
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|d
)paren
suffix:semicolon
id|dput
c_func
(paren
id|d
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_remove_link - remove symlink in object&squot;s directory.&n; *&t;@kobj:&t;object we&squot;re acting for.&n; *&t;@name:&t;name of the symlink to remove.&n; */
DECL|function|sysfs_remove_link
r_void
id|sysfs_remove_link
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|name
)paren
(brace
id|sysfs_hash_and_remove
c_func
(paren
id|kobj-&gt;dentry
comma
id|name
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_create_link
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_create_link
)paren
suffix:semicolon
DECL|variable|sysfs_remove_link
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_remove_link
)paren
suffix:semicolon
eof
