multiline_comment|/*&n; * Directory operations for Coda filesystem&n; * Original version: (C) 1996 P. Braam and M. Callahan&n; * Rewritten for Linux 2.1. (C) 1997 Carnegie Mellon University&n; * &n; * Carnegie Mellon encourages users to contribute improvements to&n; * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
macro_line|#include &lt;linux/coda_proc.h&gt;
multiline_comment|/* dir inode-ops */
r_static
r_int
id|coda_create
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
r_new
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|coda_mknod
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
r_new
comma
r_int
id|mode
comma
r_int
id|rdev
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|coda_lookup
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
id|target
)paren
suffix:semicolon
r_static
r_int
id|coda_link
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
id|dir_inode
comma
r_struct
id|dentry
op_star
id|entry
)paren
suffix:semicolon
r_static
r_int
id|coda_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|entry
)paren
suffix:semicolon
r_static
r_int
id|coda_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|entry
comma
r_const
r_char
op_star
id|symname
)paren
suffix:semicolon
r_static
r_int
id|coda_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|entry
comma
r_int
id|mode
)paren
suffix:semicolon
r_static
r_int
id|coda_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|entry
)paren
suffix:semicolon
r_static
r_int
id|coda_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_inode
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_inode
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
multiline_comment|/* dir file-ops */
r_static
r_int
id|coda_readdir
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
multiline_comment|/* dentry ops */
r_static
r_int
id|coda_dentry_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|coda_dentry_delete
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* support routines */
r_static
r_int
id|coda_venus_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|filldir_t
id|filldir
comma
r_void
op_star
id|dirent
comma
r_struct
id|dentry
op_star
id|dir
)paren
suffix:semicolon
r_int
id|coda_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
suffix:semicolon
DECL|variable|coda_hasmknod
r_int
id|coda_hasmknod
suffix:semicolon
DECL|variable|coda_dentry_operations
r_struct
id|dentry_operations
id|coda_dentry_operations
op_assign
(brace
dot
id|d_revalidate
op_assign
id|coda_dentry_revalidate
comma
dot
id|d_delete
op_assign
id|coda_dentry_delete
comma
)brace
suffix:semicolon
DECL|variable|coda_dir_inode_operations
r_struct
id|inode_operations
id|coda_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|coda_create
comma
dot
id|lookup
op_assign
id|coda_lookup
comma
dot
id|link
op_assign
id|coda_link
comma
dot
id|unlink
op_assign
id|coda_unlink
comma
dot
id|symlink
op_assign
id|coda_symlink
comma
dot
id|mkdir
op_assign
id|coda_mkdir
comma
dot
id|rmdir
op_assign
id|coda_rmdir
comma
dot
id|mknod
op_assign
id|coda_mknod
comma
dot
id|rename
op_assign
id|coda_rename
comma
dot
id|permission
op_assign
id|coda_permission
comma
dot
id|getattr
op_assign
id|coda_getattr
comma
dot
id|setattr
op_assign
id|coda_setattr
comma
)brace
suffix:semicolon
DECL|variable|coda_dir_operations
r_struct
id|file_operations
id|coda_dir_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|coda_readdir
comma
dot
id|open
op_assign
id|coda_open
comma
dot
id|flush
op_assign
id|coda_flush
comma
dot
id|release
op_assign
id|coda_release
comma
dot
id|fsync
op_assign
id|coda_fsync
comma
)brace
suffix:semicolon
multiline_comment|/* inode operations for directories */
multiline_comment|/* access routines: lookup, readlink, permission */
DECL|function|coda_lookup
r_static
r_struct
id|dentry
op_star
id|coda_lookup
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
id|entry
)paren
(brace
r_struct
id|inode
op_star
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ViceFid
id|resfid
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|dropme
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to indicate entry should not be cached */
r_int
id|type
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|entry-&gt;d_name.name
suffix:semicolon
r_int
id|length
op_assign
id|entry-&gt;d_name.len
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|CODA_MAXNAMLEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;name too long: lookup, %s (%*s)&bslash;n&quot;
comma
id|coda_i2s
c_func
(paren
id|dir
)paren
comma
(paren
r_int
)paren
id|length
comma
id|name
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* control object, create inode on the fly */
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|length
)paren
)paren
(brace
id|error
op_assign
id|coda_cnode_makectl
c_func
(paren
op_amp
id|res_inode
comma
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|dropme
op_assign
l_int|1
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|error
op_assign
id|venus_lookup
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
(paren
r_const
r_char
op_star
)paren
id|name
comma
id|length
comma
op_amp
id|type
comma
op_amp
id|resfid
)paren
suffix:semicolon
id|res_inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|type
op_amp
id|CODA_NOCACHE
)paren
(brace
id|type
op_and_assign
(paren
op_complement
id|CODA_NOCACHE
)paren
suffix:semicolon
id|dropme
op_assign
l_int|1
suffix:semicolon
)brace
id|error
op_assign
id|coda_cnode_make
c_func
(paren
op_amp
id|res_inode
comma
op_amp
id|resfid
comma
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
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
)brace
r_else
r_if
c_cond
(paren
id|error
op_ne
op_minus
id|ENOENT
)paren
(brace
id|unlock_kernel
c_func
(paren
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
m_exit
suffix:colon
id|entry-&gt;d_time
op_assign
l_int|0
suffix:semicolon
id|entry-&gt;d_op
op_assign
op_amp
id|coda_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|entry
comma
id|res_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dropme
)paren
(brace
id|d_drop
c_func
(paren
id|entry
)paren
suffix:semicolon
id|coda_flag_inode
c_func
(paren
id|res_inode
comma
id|C_VATTR
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|coda_permission
r_int
id|coda_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.permission
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_cache_check
c_func
(paren
id|inode
comma
id|mask
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|venus_access
c_func
(paren
id|inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|inode
)paren
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|coda_cache_enter
c_func
(paren
id|inode
comma
id|mask
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|coda_dir_changed
r_static
r_inline
r_void
id|coda_dir_changed
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|link
)paren
(brace
macro_line|#ifdef REQUERY_VENUS_FOR_MTIME
multiline_comment|/* invalidate the directory cnode&squot;s attributes so we refetch the&n;&t; * attributes from venus next time the inode is referenced */
id|coda_flag_inode
c_func
(paren
id|dir
comma
id|C_VATTR
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* optimistically we can also act as if our nose bleeds. The&n;         * granularity of the mtime is coarse anyways so we might actually be&n;         * right most of the time. Note: we only do this for directories. */
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|link
)paren
id|dir-&gt;i_nlink
op_add_assign
id|link
suffix:semicolon
)brace
multiline_comment|/* creation routines: create, mknod, mkdir, link, symlink */
DECL|function|coda_create
r_static
r_int
id|coda_create
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
id|de
comma
r_int
id|mode
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|length
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|ViceFid
id|newfid
suffix:semicolon
r_struct
id|coda_vattr
id|attrs
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.create
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|length
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|error
op_assign
id|venus_create
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
id|name
comma
id|length
comma
l_int|0
comma
id|mode
comma
l_int|0
comma
op_amp
id|newfid
comma
op_amp
id|attrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|inode
op_assign
id|coda_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|newfid
comma
op_amp
id|attrs
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* invalidate the directory cnode&squot;s attributes */
id|coda_dir_changed
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_mknod
r_static
r_int
id|coda_mknod
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
id|de
comma
r_int
id|mode
comma
r_int
id|rdev
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|length
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|ViceFid
id|newfid
suffix:semicolon
r_struct
id|coda_vattr
id|attrs
suffix:semicolon
r_if
c_cond
(paren
id|coda_hasmknod
op_eq
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.create
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|length
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|error
op_assign
id|venus_create
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
id|name
comma
id|length
comma
l_int|0
comma
id|mode
comma
id|rdev
comma
op_amp
id|newfid
comma
op_amp
id|attrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|inode
op_assign
id|coda_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|newfid
comma
op_amp
id|attrs
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* invalidate the directory cnode&squot;s attributes */
id|coda_dir_changed
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_mkdir
r_static
r_int
id|coda_mkdir
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
id|de
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
r_struct
id|coda_vattr
id|attrs
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|ViceFid
id|newfid
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.mkdir
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|len
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|attrs.va_mode
op_assign
id|mode
suffix:semicolon
id|error
op_assign
id|venus_mkdir
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
id|name
comma
id|len
comma
op_amp
id|newfid
comma
op_amp
id|attrs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|inode
op_assign
id|coda_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|newfid
comma
op_amp
id|attrs
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
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/* invalidate the directory cnode&squot;s attributes */
id|coda_dir_changed
c_func
(paren
id|dir
comma
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* try to make de an entry in dir_inodde linked to source_de */
DECL|function|coda_link
r_static
r_int
id|coda_link
c_func
(paren
r_struct
id|dentry
op_star
id|source_de
comma
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|de
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|source_de-&gt;d_inode
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.link
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir_inode
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|len
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|error
op_assign
id|venus_link
c_func
(paren
id|dir_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|inode
)paren
comma
id|coda_i2f
c_func
(paren
id|dir_inode
)paren
comma
(paren
r_const
r_char
op_star
)paren
id|name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|coda_dir_changed
c_func
(paren
id|dir_inode
comma
l_int|0
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|coda_symlink
r_static
r_int
id|coda_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir_inode
comma
r_struct
id|dentry
op_star
id|de
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_int
id|symlen
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.symlink
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
c_func
(paren
id|dir_inode
)paren
op_logical_and
id|coda_iscontrol
c_func
(paren
id|name
comma
id|len
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|symlen
op_assign
id|strlen
c_func
(paren
id|symname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symlen
OG
id|CODA_MAXPATHLEN
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This entry is now negative. Since we do not create&n;&t; * an inode for the entry we have to drop it. &n;&t; */
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
id|error
op_assign
id|venus_symlink
c_func
(paren
id|dir_inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir_inode
)paren
comma
id|name
comma
id|len
comma
id|symname
comma
id|symlen
)paren
suffix:semicolon
multiline_comment|/* mtime is no good anymore */
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|coda_dir_changed
c_func
(paren
id|dir_inode
comma
l_int|0
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* destruction routines: unlink, rmdir */
DECL|function|coda_unlink
r_int
id|coda_unlink
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
id|de
)paren
(brace
r_int
id|error
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;d_name.len
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.unlink
op_increment
suffix:semicolon
id|error
op_assign
id|venus_remove
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|coda_dir_changed
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
id|de-&gt;d_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_rmdir
r_int
id|coda_rmdir
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
id|de
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|de-&gt;d_name.name
suffix:semicolon
r_int
id|len
op_assign
id|de-&gt;d_name.len
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.rmdir
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_unhashed
c_func
(paren
id|de
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|error
op_assign
id|venus_rmdir
c_func
(paren
id|dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|dir
)paren
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|coda_dir_changed
c_func
(paren
id|dir
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|de-&gt;d_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|d_delete
c_func
(paren
id|de
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* rename */
DECL|function|coda_rename
r_static
r_int
id|coda_rename
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
r_const
r_char
op_star
id|old_name
op_assign
id|old_dentry-&gt;d_name.name
suffix:semicolon
r_const
r_char
op_star
id|new_name
op_assign
id|new_dentry-&gt;d_name.name
suffix:semicolon
r_int
id|old_length
op_assign
id|old_dentry-&gt;d_name.len
suffix:semicolon
r_int
id|new_length
op_assign
id|new_dentry-&gt;d_name.len
suffix:semicolon
r_int
id|link_adjust
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|coda_vfs_stat.rename
op_increment
suffix:semicolon
id|error
op_assign
id|venus_rename
c_func
(paren
id|old_dir-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|old_dir
)paren
comma
id|coda_i2f
c_func
(paren
id|new_dir
)paren
comma
id|old_length
comma
id|new_length
comma
(paren
r_const
r_char
op_star
)paren
id|old_name
comma
(paren
r_const
r_char
op_star
)paren
id|new_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|new_dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|new_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|link_adjust
op_assign
l_int|1
suffix:semicolon
id|coda_dir_changed
c_func
(paren
id|old_dir
comma
op_minus
id|link_adjust
)paren
suffix:semicolon
id|coda_dir_changed
c_func
(paren
id|new_dir
comma
id|link_adjust
)paren
suffix:semicolon
id|coda_flag_inode
c_func
(paren
id|new_dentry-&gt;d_inode
comma
id|C_VATTR
)paren
suffix:semicolon
)brace
r_else
(brace
id|coda_flag_inode
c_func
(paren
id|old_dir
comma
id|C_VATTR
)paren
suffix:semicolon
id|coda_flag_inode
c_func
(paren
id|new_dir
comma
id|C_VATTR
)paren
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* file operations for directories */
DECL|function|coda_readdir
r_int
id|coda_readdir
c_func
(paren
r_struct
id|file
op_star
id|coda_file
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
id|coda_dentry
op_assign
id|coda_file-&gt;f_dentry
suffix:semicolon
r_struct
id|coda_file_info
op_star
id|cfi
suffix:semicolon
r_struct
id|file
op_star
id|host_file
suffix:semicolon
r_struct
id|inode
op_star
id|host_inode
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|cfi
op_assign
id|CODA_FTOC
c_func
(paren
id|coda_file
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cfi
op_logical_or
id|cfi-&gt;cfi_magic
op_ne
id|CODA_MAGIC
)paren
suffix:semicolon
id|host_file
op_assign
id|cfi-&gt;cfi_container
suffix:semicolon
id|coda_vfs_stat.readdir
op_increment
suffix:semicolon
id|host_inode
op_assign
id|host_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|host_inode-&gt;i_sem
)paren
suffix:semicolon
id|host_file-&gt;f_pos
op_assign
id|coda_file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op-&gt;readdir
)paren
(brace
multiline_comment|/* Venus: we must read Venus dirents from the file */
id|ret
op_assign
id|coda_venus_readdir
c_func
(paren
id|host_file
comma
id|filldir
comma
id|dirent
comma
id|coda_dentry
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* potemkin case: we were handed a directory inode. */
multiline_comment|/* Yuk, we can&squot;t call vfs_readdir because we are already&n;&t;&t; * holding the inode semaphore. */
id|ret
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host_file-&gt;f_op
op_logical_or
op_logical_neg
id|host_file-&gt;f_op-&gt;readdir
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_DEADDIR
c_func
(paren
id|host_inode
)paren
)paren
id|ret
op_assign
id|host_file-&gt;f_op
op_member_access_from_pointer
id|readdir
c_func
(paren
id|host_file
comma
id|filldir
comma
id|dirent
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|coda_file-&gt;f_pos
op_assign
id|host_file-&gt;f_pos
suffix:semicolon
id|up
c_func
(paren
op_amp
id|host_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|CDT2DT
r_static
r_inline
r_int
r_int
id|CDT2DT
c_func
(paren
r_int
r_char
id|cdt
)paren
(brace
r_int
r_int
id|dt
suffix:semicolon
r_switch
c_cond
(paren
id|cdt
)paren
(brace
r_case
id|CDT_UNKNOWN
suffix:colon
id|dt
op_assign
id|DT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_FIFO
suffix:colon
id|dt
op_assign
id|DT_FIFO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_CHR
suffix:colon
id|dt
op_assign
id|DT_CHR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_DIR
suffix:colon
id|dt
op_assign
id|DT_DIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_BLK
suffix:colon
id|dt
op_assign
id|DT_BLK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_REG
suffix:colon
id|dt
op_assign
id|DT_REG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_LNK
suffix:colon
id|dt
op_assign
id|DT_LNK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_SOCK
suffix:colon
id|dt
op_assign
id|DT_SOCK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDT_WHT
suffix:colon
id|dt
op_assign
id|DT_WHT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dt
op_assign
id|DT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|dt
suffix:semicolon
)brace
multiline_comment|/* support routines */
DECL|function|coda_venus_readdir
r_static
r_int
id|coda_venus_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|filldir_t
id|filldir
comma
r_void
op_star
id|dirent
comma
r_struct
id|dentry
op_star
id|dir
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # of entries returned */
r_struct
id|venus_dirent
op_star
id|vdir
suffix:semicolon
r_int
r_int
id|vdir_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
(paren
(paren
r_struct
id|venus_dirent
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|d_name
)paren
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
r_struct
id|qstr
id|name
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
id|vdir
op_assign
(paren
r_struct
id|venus_dirent
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|vdir
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vdir
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|ret
op_assign
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
id|dir-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|result
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_int|1
suffix:colon
id|ret
op_assign
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
id|dir-&gt;d_parent-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|result
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_default
suffix:colon
(brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* read entries from the directory file */
id|ret
op_assign
id|kernel_read
c_func
(paren
id|filp
comma
id|filp-&gt;f_pos
op_minus
l_int|2
comma
(paren
r_char
op_star
)paren
id|vdir
comma
r_sizeof
(paren
op_star
id|vdir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_venus_readdir: read dir failed %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* end of directory file reached */
multiline_comment|/* catch truncated reads */
r_if
c_cond
(paren
id|ret
OL
id|vdir_size
op_logical_or
id|ret
OL
id|vdir_size
op_plus
id|vdir-&gt;d_namlen
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_venus_readdir: short read: %ld&bslash;n&quot;
comma
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* validate whether the directory file actually makes sense */
r_if
c_cond
(paren
id|vdir-&gt;d_reclen
template_param
id|CODA_MAXNAMLEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_venus_readdir: Invalid dir: %ld&bslash;n&quot;
comma
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBADF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|name.len
op_assign
id|vdir-&gt;d_namlen
suffix:semicolon
id|name.name
op_assign
id|vdir-&gt;d_name
suffix:semicolon
multiline_comment|/* Make sure we skip &squot;.&squot; and &squot;..&squot;, we already got those */
r_if
c_cond
(paren
id|name.name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|name.len
op_eq
l_int|1
op_logical_or
(paren
id|vdir-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|name.len
op_eq
l_int|2
)paren
)paren
)paren
id|vdir-&gt;d_fileno
op_assign
id|name.len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* skip null entries */
r_if
c_cond
(paren
id|vdir-&gt;d_fileno
op_logical_and
id|name.len
)paren
(brace
multiline_comment|/* try to look up this entry in the dcache, that way&n;&t;&t;&t; * userspace doesn&squot;t have to worry about breaking&n;&t;&t;&t; * getcwd by having mismatched inode numbers for&n;&t;&t;&t; * internal volume mountpoints. */
id|ino
op_assign
id|find_inode_number
c_func
(paren
id|dir
comma
op_amp
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
id|ino
op_assign
id|vdir-&gt;d_fileno
suffix:semicolon
id|type
op_assign
id|CDT2DT
c_func
(paren
id|vdir-&gt;d_type
)paren
suffix:semicolon
id|ret
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|name.name
comma
id|name.len
comma
id|filp-&gt;f_pos
comma
id|ino
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* failure means no space for filling in this round */
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|result
op_increment
suffix:semicolon
)brace
multiline_comment|/* we&squot;ll always have progress because d_reclen is unsigned and&n;&t;&t; * we&squot;ve already established it is non-zero. */
id|filp-&gt;f_pos
op_add_assign
id|vdir-&gt;d_reclen
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|vdir
)paren
suffix:semicolon
r_return
id|result
ques
c_cond
id|result
suffix:colon
id|ret
suffix:semicolon
)brace
multiline_comment|/* called when a cache lookup succeeds */
DECL|function|coda_dentry_revalidate
r_static
r_int
id|coda_dentry_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_int
id|flags
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|1
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|coda_isroot
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
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
r_goto
id|bad
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|de-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cii-&gt;c_flags
op_amp
(paren
id|C_PURGE
op_or
id|C_FLUSH
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|shrink_dcache_parent
c_func
(paren
id|de
)paren
suffix:semicolon
multiline_comment|/* propagate for a flush */
r_if
c_cond
(paren
id|cii-&gt;c_flags
op_amp
id|C_FLUSH
)paren
id|coda_flag_inode_children
c_func
(paren
id|inode
comma
id|C_FLUSH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|de-&gt;d_count
)paren
OG
l_int|1
)paren
multiline_comment|/* pretend it&squot;s valid, but don&squot;t change the flags */
r_goto
id|out
suffix:semicolon
multiline_comment|/* clear the flags. */
id|cii-&gt;c_flags
op_and_assign
op_complement
(paren
id|C_VATTR
op_or
id|C_PURGE
op_or
id|C_FLUSH
)paren
suffix:semicolon
id|bad
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the callback from dput() when d_count is going to 0.&n; * We use this to unhash dentries with bad inodes.&n; */
DECL|function|coda_dentry_delete
r_static
r_int
id|coda_dentry_delete
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
r_return
l_int|0
suffix:semicolon
id|flags
op_assign
(paren
id|ITOC
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|c_flags
)paren
op_amp
id|C_PURGE
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_logical_or
id|flags
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when we want to check if the inode has&n; * changed on the server.  Coda makes this easy since the&n; * cache manager Venus issues a downcall to the kernel when this &n; * happens &n; */
DECL|function|coda_revalidate_inode
r_int
id|coda_revalidate_inode
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|coda_vattr
id|attr
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|old_mode
suffix:semicolon
id|ino_t
id|old_ino
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cii-&gt;c_flags
)paren
r_goto
id|ok
suffix:semicolon
r_if
c_cond
(paren
id|cii-&gt;c_flags
op_amp
(paren
id|C_VATTR
op_or
id|C_PURGE
op_or
id|C_FLUSH
)paren
)paren
(brace
id|error
op_assign
id|venus_getattr
c_func
(paren
id|inode-&gt;i_sb
comma
op_amp
(paren
id|cii-&gt;c_fid
)paren
comma
op_amp
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|return_bad
suffix:semicolon
multiline_comment|/* this inode may be lost if:&n;&t;&t;   - it&squot;s ino changed &n;&t;&t;   - type changes must be permitted for repair and&n;&t;&t;   missing mount points.&n;&t;&t;*/
id|old_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|old_ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|coda_vattr_to_iattr
c_func
(paren
id|inode
comma
op_amp
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old_mode
op_amp
id|S_IFMT
)paren
op_ne
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Coda: inode %ld, fid %s changed type!&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|coda_f2s
c_func
(paren
op_amp
(paren
id|cii-&gt;c_fid
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* the following can happen when a local fid is replaced &n;&t;&t;   with a global one, here we lose and declare the inode bad */
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_ne
id|old_ino
)paren
r_goto
id|return_bad
suffix:semicolon
id|coda_flag_inode_children
c_func
(paren
id|inode
comma
id|C_FLUSH
)paren
suffix:semicolon
id|cii-&gt;c_flags
op_and_assign
op_complement
(paren
id|C_VATTR
op_or
id|C_PURGE
op_or
id|C_FLUSH
)paren
suffix:semicolon
)brace
id|ok
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|return_bad
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
eof
