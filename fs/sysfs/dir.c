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
id|kobj-&gt;name
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
id|kobj
suffix:semicolon
id|kobj-&gt;dentry
op_assign
id|dentry
suffix:semicolon
id|error
op_assign
id|sysfs_create
c_func
(paren
id|dentry
comma
(paren
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
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
id|parent-&gt;d_inode-&gt;i_nlink
op_increment
suffix:semicolon
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
r_struct
id|dentry
op_star
id|parent
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
id|parent
op_assign
id|dget
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
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
id|list_del_init
c_func
(paren
id|node
)paren
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
id|d-&gt;d_inode
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
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot; done&bslash;n&quot;
)paren
suffix:semicolon
id|node
op_assign
id|dentry-&gt;d_subdirs.next
suffix:semicolon
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
id|d_delete
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|simple_rmdir
c_func
(paren
id|parent-&gt;d_inode
comma
id|dentry
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; o %s removing done (%d)&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
comma
id|atomic_read
c_func
(paren
op_amp
id|dentry-&gt;d_count
)paren
)paren
suffix:semicolon
multiline_comment|/**&n;&t; * Drop reference from dget() on entrance.&n;&t; */
id|dput
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
id|dput
c_func
(paren
id|parent
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
eof
