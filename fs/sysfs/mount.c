multiline_comment|/*&n; * mount.c - operations for initializing and mounting sysfs.&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG 
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;sysfs.h&quot;
multiline_comment|/* Random magic number */
DECL|macro|SYSFS_MAGIC
mdefine_line|#define SYSFS_MAGIC 0x62656572
DECL|variable|sysfs_mount
r_struct
id|vfsmount
op_star
id|sysfs_mount
suffix:semicolon
DECL|variable|sysfs_sb
r_struct
id|super_block
op_star
id|sysfs_sb
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sysfs_ops
r_static
r_struct
id|super_operations
id|sysfs_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
dot
id|drop_inode
op_assign
id|generic_delete_inode
comma
)brace
suffix:semicolon
DECL|variable|sysfs_root
r_static
r_struct
id|sysfs_dirent
id|sysfs_root
op_assign
(brace
dot
id|s_sibling
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|sysfs_root.s_sibling
)paren
comma
dot
id|s_children
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|sysfs_root.s_children
)paren
comma
dot
id|s_element
op_assign
l_int|NULL
comma
dot
id|s_type
op_assign
id|SYSFS_ROOT
comma
)brace
suffix:semicolon
DECL|function|sysfs_fill_super
r_static
r_int
id|sysfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|SYSFS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|sysfs_ops
suffix:semicolon
id|sb-&gt;s_time_gran
op_assign
l_int|1
suffix:semicolon
id|sysfs_sb
op_assign
id|sb
suffix:semicolon
id|inode
op_assign
id|sysfs_new_inode
c_func
(paren
id|S_IFDIR
op_or
id|S_IRWXU
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|sysfs_dir_inode_operations
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
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;sysfs: could not get root inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: could not get root dentry!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|root-&gt;d_fsdata
op_assign
op_amp
id|sysfs_root
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sysfs_get_sb
r_static
r_struct
id|super_block
op_star
id|sysfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_single
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|sysfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_fs_type
r_static
r_struct
id|file_system_type
id|sysfs_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sysfs&quot;
comma
dot
id|get_sb
op_assign
id|sysfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|sysfs_init
r_int
id|__init
id|sysfs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|sysfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|sysfs_mount
op_assign
id|kern_mount
c_func
(paren
op_amp
id|sysfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sysfs_mount
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sysfs: could not mount!&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|sysfs_mount
)paren
suffix:semicolon
id|sysfs_mount
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
eof
