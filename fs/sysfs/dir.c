multiline_comment|/*&n; * dir.c - Operations for sysfs directories.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|function|init_dir
r_static
r_int
id|init_dir
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
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
multiline_comment|/* directory inodes start off with i_nlink == 2 (for &quot;.&quot; entry) */
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_dir
r_static
r_int
id|create_dir
c_func
(paren
r_struct
id|kobject
op_star
id|k
comma
r_struct
id|dentry
op_star
id|p
comma
r_const
r_char
op_star
id|n
comma
r_struct
id|dentry
op_star
op_star
id|d
)paren
(brace
r_int
id|error
suffix:semicolon
id|down
c_func
(paren
op_amp
id|p-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
op_star
id|d
op_assign
id|sysfs_get_dentry
c_func
(paren
id|p
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
op_star
id|d
)paren
)paren
(brace
id|error
op_assign
id|sysfs_create
c_func
(paren
op_star
id|d
comma
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
id|init_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
(paren
op_star
id|d
)paren
op_member_access_from_pointer
id|d_fsdata
op_assign
id|k
suffix:semicolon
id|p-&gt;d_inode-&gt;i_nlink
op_increment
suffix:semicolon
)brace
id|dput
c_func
(paren
op_star
id|d
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
id|PTR_ERR
c_func
(paren
op_star
id|d
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|p-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_create_subdir
r_int
id|sysfs_create_subdir
c_func
(paren
r_struct
id|kobject
op_star
id|k
comma
r_const
r_char
op_star
id|n
comma
r_struct
id|dentry
op_star
op_star
id|d
)paren
(brace
r_return
id|create_dir
c_func
(paren
id|k
comma
id|k-&gt;dentry
comma
id|n
comma
id|d
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_create_dir - create a directory for an object.&n; *&t;@parent:&t;parent parent object.&n; *&t;@kobj:&t;&t;object we&squot;re creating directory for. &n; */
DECL|function|sysfs_create_dir
r_int
id|sysfs_create_dir
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
l_int|NULL
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
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|kobj-&gt;parent
)paren
id|parent
op_assign
id|kobj-&gt;parent-&gt;dentry
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sysfs_mount
op_logical_and
id|sysfs_mount-&gt;mnt_sb
)paren
id|parent
op_assign
id|sysfs_mount-&gt;mnt_sb-&gt;s_root
suffix:semicolon
r_else
r_return
op_minus
id|EFAULT
suffix:semicolon
id|error
op_assign
id|create_dir
c_func
(paren
id|kobj
comma
id|parent
comma
id|kobject_name
c_func
(paren
id|kobj
)paren
comma
op_amp
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|kobj-&gt;dentry
op_assign
id|dentry
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|remove_dir
r_static
r_void
id|remove_dir
c_func
(paren
r_struct
id|dentry
op_star
id|d
)paren
(brace
r_struct
id|dentry
op_star
id|parent
op_assign
id|dget
c_func
(paren
id|d-&gt;d_parent
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|d_delete
c_func
(paren
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;d_inode
)paren
id|simple_rmdir
c_func
(paren
id|parent-&gt;d_inode
comma
id|d
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; o %s removing done (%d)&bslash;n&quot;
comma
id|d-&gt;d_name.name
comma
id|atomic_read
c_func
(paren
op_amp
id|d-&gt;d_count
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dput
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|function|sysfs_remove_subdir
r_void
id|sysfs_remove_subdir
c_func
(paren
r_struct
id|dentry
op_star
id|d
)paren
(brace
id|remove_dir
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_remove_dir - remove an object&squot;s directory.&n; *&t;@kobj:&t;object. &n; *&n; *&t;The only thing special about this is that we remove any files in &n; *&t;the directory before we remove the directory, and we&squot;ve inlined&n; *&t;what used to be sysfs_rmdir() below, instead of calling separately.&n; */
DECL|function|sysfs_remove_dir
r_void
id|sysfs_remove_dir
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|dget
c_func
(paren
id|kobj-&gt;dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_return
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;sysfs %s: removing dir&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|restart
suffix:colon
id|node
op_assign
id|dentry-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|node
op_ne
op_amp
id|dentry-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|d
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
id|node
op_assign
id|node-&gt;next
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; o %s (%d): &quot;
comma
id|d-&gt;d_name.name
comma
id|atomic_read
c_func
(paren
op_amp
id|d-&gt;d_count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_unhashed
c_func
(paren
id|d
)paren
op_logical_and
(paren
id|d-&gt;d_inode
)paren
)paren
(brace
id|d
op_assign
id|dget_locked
c_func
(paren
id|d
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;removing&quot;
)paren
suffix:semicolon
multiline_comment|/**&n;&t;&t;&t; * Unlink and unhash.&n;&t;&t;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|d_delete
c_func
(paren
id|d
)paren
suffix:semicolon
id|simple_unlink
c_func
(paren
id|dentry-&gt;d_inode
comma
id|d
)paren
suffix:semicolon
id|dput
c_func
(paren
id|d
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; done&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
multiline_comment|/* re-acquired dcache_lock, need to restart */
r_goto
id|restart
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|remove_dir
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/**&n;&t; * Drop reference from dget() on entrance.&n;&t; */
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
DECL|function|sysfs_rename_dir
r_void
id|sysfs_rename_dir
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_char
op_star
id|new_name
)paren
(brace
r_struct
id|dentry
op_star
id|new_dentry
comma
op_star
id|parent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kobject_name
c_func
(paren
id|kobj
)paren
comma
id|new_name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj-&gt;parent
)paren
r_return
suffix:semicolon
id|parent
op_assign
id|kobj-&gt;parent-&gt;dentry
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|new_dentry
op_assign
id|sysfs_get_dentry
c_func
(paren
id|parent
comma
id|new_name
)paren
suffix:semicolon
id|d_move
c_func
(paren
id|kobj-&gt;dentry
comma
id|new_dentry
)paren
suffix:semicolon
id|kobject_set_name
c_func
(paren
id|kobj
comma
id|new_name
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_create_dir
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_create_dir
)paren
suffix:semicolon
DECL|variable|sysfs_remove_dir
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_remove_dir
)paren
suffix:semicolon
DECL|variable|sysfs_rename_dir
id|EXPORT_SYMBOL
c_func
(paren
id|sysfs_rename_dir
)paren
suffix:semicolon
eof
