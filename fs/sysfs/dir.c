multiline_comment|/*&n; * dir.c - Operations for sysfs directories.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|variable|sysfs_rename_sem
id|DECLARE_RWSEM
c_func
(paren
id|sysfs_rename_sem
)paren
suffix:semicolon
DECL|function|sysfs_d_iput
r_static
r_void
id|sysfs_d_iput
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
r_struct
id|sysfs_dirent
op_star
id|sd
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|sd
)paren
(brace
id|BUG_ON
c_func
(paren
id|sd-&gt;s_dentry
op_ne
id|dentry
)paren
suffix:semicolon
id|sd-&gt;s_dentry
op_assign
l_int|NULL
suffix:semicolon
id|sysfs_put
c_func
(paren
id|sd
)paren
suffix:semicolon
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_dentry_ops
r_static
r_struct
id|dentry_operations
id|sysfs_dentry_ops
op_assign
(brace
dot
id|d_iput
op_assign
id|sysfs_d_iput
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocates a new sysfs_dirent and links it to the parent sysfs_dirent&n; */
DECL|function|sysfs_new_dirent
r_static
r_struct
id|sysfs_dirent
op_star
id|sysfs_new_dirent
c_func
(paren
r_struct
id|sysfs_dirent
op_star
id|parent_sd
comma
r_void
op_star
id|element
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|sd
suffix:semicolon
id|sd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sd
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sd
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sd-&gt;s_count
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sd-&gt;s_children
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|sd-&gt;s_sibling
comma
op_amp
id|parent_sd-&gt;s_children
)paren
suffix:semicolon
id|sd-&gt;s_element
op_assign
id|element
suffix:semicolon
r_return
id|sd
suffix:semicolon
)brace
DECL|function|sysfs_make_dirent
r_int
id|sysfs_make_dirent
c_func
(paren
r_struct
id|sysfs_dirent
op_star
id|parent_sd
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_void
op_star
id|element
comma
id|umode_t
id|mode
comma
r_int
id|type
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|sd
suffix:semicolon
id|sd
op_assign
id|sysfs_new_dirent
c_func
(paren
id|parent_sd
comma
id|element
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sd-&gt;s_mode
op_assign
id|mode
suffix:semicolon
id|sd-&gt;s_type
op_assign
id|type
suffix:semicolon
id|sd-&gt;s_dentry
op_assign
id|dentry
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
id|sysfs_get
c_func
(paren
id|sd
)paren
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|sysfs_dentry_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|sysfs_dir_operations
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
id|umode_t
id|mode
op_assign
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
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
id|mode
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
id|error
op_assign
id|sysfs_make_dirent
c_func
(paren
id|p-&gt;d_fsdata
comma
op_star
id|d
comma
id|k
comma
id|mode
comma
id|SYSFS_DIR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|p-&gt;d_inode-&gt;i_nlink
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
id|d_drop
c_func
(paren
op_star
id|d
)paren
suffix:semicolon
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|kobj
)paren
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
r_struct
id|sysfs_dirent
op_star
id|sd
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
id|sd
op_assign
id|d-&gt;d_fsdata
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|sd-&gt;s_sibling
)paren
suffix:semicolon
id|sysfs_put
c_func
(paren
id|sd
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
id|sysfs_dirent
op_star
id|parent_sd
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|sd
comma
op_star
id|tmp
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
id|list_for_each_entry_safe
c_func
(paren
id|sd
comma
id|tmp
comma
op_amp
id|parent_sd-&gt;s_children
comma
id|s_sibling
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sd-&gt;s_element
)paren
r_continue
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|sd-&gt;s_sibling
)paren
suffix:semicolon
id|sysfs_drop_dentry
c_func
(paren
id|sd
comma
id|dentry
)paren
suffix:semicolon
id|sysfs_put
c_func
(paren
id|sd
)paren
suffix:semicolon
)brace
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
r_int
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
r_int
id|error
op_assign
l_int|0
suffix:semicolon
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
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj-&gt;parent
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|sysfs_rename_sem
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|new_dentry
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|new_dentry-&gt;d_inode
)paren
(brace
id|error
op_assign
id|kobject_set_name
c_func
(paren
id|kobj
comma
l_string|&quot;%s&quot;
comma
id|new_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|d_move
c_func
(paren
id|kobj-&gt;dentry
comma
id|new_dentry
)paren
suffix:semicolon
r_else
id|d_drop
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|EEXIST
suffix:semicolon
id|dput
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|sysfs_rename_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_dir_open
r_static
r_int
id|sysfs_dir_open
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
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|parent_sd
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
id|sysfs_new_dirent
c_func
(paren
id|parent_sd
comma
l_int|NULL
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|file-&gt;private_data
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|sysfs_dir_close
r_static
r_int
id|sysfs_dir_close
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
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|cursor
op_assign
id|file-&gt;private_data
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|cursor-&gt;s_sibling
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|sysfs_put
c_func
(paren
id|file-&gt;private_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Relationship between s_mode and the DT_xxx types */
DECL|function|dt_type
r_static
r_inline
r_int
r_char
id|dt_type
c_func
(paren
r_struct
id|sysfs_dirent
op_star
id|sd
)paren
(brace
r_return
(paren
id|sd-&gt;s_mode
op_rshift
l_int|12
)paren
op_amp
l_int|15
suffix:semicolon
)brace
DECL|function|sysfs_readdir
r_static
r_int
id|sysfs_readdir
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
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|parent_sd
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|cursor
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|q
op_assign
op_amp
id|cursor-&gt;s_sibling
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_int
id|i
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|ino
op_assign
id|dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
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
id|i
comma
id|ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_int|1
suffix:colon
id|ino
op_assign
id|parent_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
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
id|i
comma
id|ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|2
)paren
(brace
id|list_del
c_func
(paren
id|q
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|q
comma
op_amp
id|parent_sd-&gt;s_children
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|q-&gt;next
suffix:semicolon
id|p
op_ne
op_amp
id|parent_sd-&gt;s_children
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|next
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|len
suffix:semicolon
id|next
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|sysfs_dirent
comma
id|s_sibling
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next-&gt;s_element
)paren
r_continue
suffix:semicolon
id|name
op_assign
id|sysfs_get_name
c_func
(paren
id|next
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next-&gt;s_dentry
)paren
id|ino
op_assign
id|next-&gt;s_dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_else
id|ino
op_assign
id|iunique
c_func
(paren
id|sysfs_sb
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|name
comma
id|len
comma
id|filp-&gt;f_pos
comma
id|ino
comma
id|dt_type
c_func
(paren
id|next
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|list_del
c_func
(paren
id|q
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|q
comma
id|p
)paren
suffix:semicolon
id|p
op_assign
id|q
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysfs_dir_lseek
r_static
id|loff_t
id|sysfs_dir_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
)paren
r_break
suffix:semicolon
r_default
suffix:colon
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
l_int|2
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|sd
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|sysfs_dirent
op_star
id|cursor
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|loff_t
id|n
op_assign
id|file-&gt;f_pos
op_minus
l_int|2
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cursor-&gt;s_sibling
)paren
suffix:semicolon
id|p
op_assign
id|sd-&gt;s_children.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
id|p
op_ne
op_amp
id|sd-&gt;s_children
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|next
suffix:semicolon
id|next
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|sysfs_dirent
comma
id|s_sibling
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next-&gt;s_element
)paren
id|n
op_decrement
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|list_add_tail
c_func
(paren
op_amp
id|cursor-&gt;s_sibling
comma
id|p
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
DECL|variable|sysfs_dir_operations
r_struct
id|file_operations
id|sysfs_dir_operations
op_assign
(brace
dot
id|open
op_assign
id|sysfs_dir_open
comma
dot
id|release
op_assign
id|sysfs_dir_close
comma
dot
id|llseek
op_assign
id|sysfs_dir_lseek
comma
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|sysfs_readdir
comma
)brace
suffix:semicolon
DECL|variable|sysfs_create_dir
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_create_dir
)paren
suffix:semicolon
DECL|variable|sysfs_remove_dir
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_remove_dir
)paren
suffix:semicolon
DECL|variable|sysfs_rename_dir
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_rename_dir
)paren
suffix:semicolon
eof
