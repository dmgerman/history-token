multiline_comment|/*&n; * driverfs.c - The device driver file system&n; *&n; * Copyright (c) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * This is a simple, ram-based filesystem, which allows kernel&n; * callbacks for read/write of files.&n; *&n; * Please see Documentation/filesystems/driverfs.txt for more information.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/driverfs_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
macro_line|# define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG(x...)
macro_line|#endif
multiline_comment|/* Random magic number */
DECL|macro|DRIVERFS_MAGIC
mdefine_line|#define DRIVERFS_MAGIC 0x42454552
DECL|variable|driverfs_ops
r_static
r_struct
id|super_operations
id|driverfs_ops
suffix:semicolon
DECL|variable|driverfs_file_operations
r_static
r_struct
id|file_operations
id|driverfs_file_operations
suffix:semicolon
DECL|variable|driverfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|driverfs_dir_inode_operations
suffix:semicolon
DECL|variable|driverfs_aops
r_static
r_struct
id|address_space_operations
id|driverfs_aops
suffix:semicolon
DECL|variable|driverfs_mount
r_static
r_struct
id|vfsmount
op_star
id|driverfs_mount
suffix:semicolon
DECL|variable|mount_lock
r_static
id|spinlock_t
id|mount_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|mount_count
r_static
r_int
id|mount_count
op_assign
l_int|0
suffix:semicolon
DECL|function|driverfs_readpage
r_static
r_int
id|driverfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
id|memset
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|driverfs_prepare_write
r_static
r_int
id|driverfs_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_void
op_star
id|addr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
id|memset
c_func
(paren
id|addr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|driverfs_commit_write
r_static
r_int
id|driverfs_commit_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
id|loff_t
id|pos
op_assign
(paren
(paren
id|loff_t
)paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|to
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|inode-&gt;i_size
)paren
id|inode-&gt;i_size
op_assign
id|pos
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|driverfs_get_inode
r_struct
id|inode
op_star
id|driverfs_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
comma
r_int
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
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
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|NODEV
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|driverfs_aops
suffix:semicolon
r_switch
c_cond
(paren
id|mode
op_amp
id|S_IFMT
)paren
(brace
r_default
suffix:colon
id|init_special_inode
c_func
(paren
id|inode
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFREG
suffix:colon
id|inode-&gt;i_fop
op_assign
op_amp
id|driverfs_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|driverfs_dir_inode_operations
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
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|driverfs_mknod
r_static
r_int
id|driverfs_mknod
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
r_int
id|dev
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
multiline_comment|/* only allow create if -&gt;d_fsdata is not NULL (so we can assume it &n;&t; * comes from the driverfs API below. */
id|inode
op_assign
id|driverfs_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|mode
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
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
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|driverfs_mkdir
r_static
r_int
id|driverfs_mkdir
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
r_int
id|res
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_amp
(paren
id|S_IRWXUGO
op_or
id|S_ISVTX
)paren
)paren
op_or
id|S_IFDIR
suffix:semicolon
id|res
op_assign
id|driverfs_mknod
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
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|driverfs_create
r_static
r_int
id|driverfs_create
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
r_int
id|res
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
op_or
id|S_IFREG
suffix:semicolon
id|res
op_assign
id|driverfs_mknod
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
r_return
id|res
suffix:semicolon
)brace
DECL|function|driverfs_symlink
r_static
r_int
id|driverfs_symlink
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
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|inode
op_assign
id|driverfs_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|S_IFLNK
op_or
id|S_IRWXUGO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
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
op_logical_neg
id|error
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
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_else
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|driverfs_positive
r_static
r_inline
r_int
id|driverfs_positive
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
(paren
id|dentry-&gt;d_inode
op_logical_and
op_logical_neg
id|d_unhashed
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
)brace
DECL|function|driverfs_empty
r_static
r_int
id|driverfs_empty
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dentry-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|de
op_assign
id|list_entry
c_func
(paren
id|list
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driverfs_positive
c_func
(paren
id|de
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|0
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|driverfs_unlink
r_static
r_int
id|driverfs_unlink
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
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|d_invalidate
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_read_file - &quot;read&quot; data from a file.&n; * @file:&t;file pointer&n; * @buf:&t;buffer to fill&n; * @count:&t;number of bytes to read&n; * @ppos:&t;starting offset in file&n; *&n; * Userspace wants data from a file. It is up to the creator of the file to&n; * provide that data.&n; * There is a struct device_attribute embedded in file-&gt;private_data. We&n; * obtain that and check if the read callback is implemented. If so, we call&n; * it, passing the data field of the file entry.&n; * Said callback is responsible for filling the buffer and returning the number&n; * of bytes it put in it. We update @ppos correctly.&n; */
r_static
id|ssize_t
DECL|function|driverfs_read_file
id|driverfs_read_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|attribute
op_star
id|attr
op_assign
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|driver_dir_entry
op_star
id|dir
suffix:semicolon
r_int
r_char
op_star
id|page
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
id|dir
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;ops-&gt;show
)paren
r_return
l_int|0
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
id|page
op_assign
(paren
r_int
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|ssize_t
id|len
suffix:semicolon
id|len
op_assign
id|dir-&gt;ops
op_member_access_from_pointer
id|show
c_func
(paren
id|dir
comma
id|attr
comma
id|page
comma
id|count
comma
op_star
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|retval
op_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|page
comma
id|len
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|len
suffix:semicolon
id|count
op_sub_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
id|retval
op_add_assign
id|len
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_write_file - &quot;write&quot; to a file&n; * @file:&t;file pointer&n; * @buf:&t;data to write&n; * @count:&t;number of bytes&n; * @ppos:&t;starting offset&n; *&n; * Similarly to driverfs_read_file, we act essentially as a bit pipe.&n; * We check for a &quot;write&quot; callback in file-&gt;private_data, and pass&n; * @buffer, @count, @ppos, and the file entry&squot;s data to the callback.&n; * The number of bytes written is returned, and we handle updating&n; * @ppos properly.&n; */
r_static
id|ssize_t
DECL|function|driverfs_write_file
id|driverfs_write_file
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|attribute
op_star
id|attr
op_assign
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|driver_dir_entry
op_star
id|dir
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
id|dir
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|page
comma
id|buf
comma
id|count
)paren
)paren
r_goto
id|done
suffix:semicolon
op_star
(paren
id|page
op_plus
id|count
)paren
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|ssize_t
id|len
suffix:semicolon
id|len
op_assign
id|dir-&gt;ops
op_member_access_from_pointer
id|store
c_func
(paren
id|dir
comma
id|attr
comma
id|page
op_plus
id|retval
comma
id|count
comma
op_star
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|retval
op_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
id|retval
op_add_assign
id|len
suffix:semicolon
id|count
op_sub_assign
id|len
suffix:semicolon
op_star
id|ppos
op_add_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
)brace
id|done
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
id|loff_t
DECL|function|driverfs_file_lseek
id|driverfs_file_lseek
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
id|orig
)paren
(brace
id|loff_t
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|offset
OG
l_int|0
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|retval
op_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|file-&gt;f_pos
)paren
OG
l_int|0
)paren
(brace
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|retval
op_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|driverfs_open_file
r_static
r_int
id|driverfs_open_file
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
id|filp
)paren
(brace
r_struct
id|driver_dir_entry
op_star
id|dir
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|dir
op_assign
(paren
r_struct
id|driver_dir_entry
op_star
)paren
id|filp-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
r_struct
id|attribute
op_star
id|attr
op_assign
id|filp-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_logical_and
id|dir-&gt;ops
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;ops-&gt;open
)paren
id|error
op_assign
id|dir-&gt;ops
op_member_access_from_pointer
id|open
c_func
(paren
id|dir
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
)brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|driverfs_release
r_static
r_int
id|driverfs_release
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
id|filp
)paren
(brace
r_struct
id|driver_dir_entry
op_star
id|dir
suffix:semicolon
id|dir
op_assign
(paren
r_struct
id|driver_dir_entry
op_star
)paren
id|filp-&gt;f_dentry-&gt;d_parent-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;ops-&gt;close
)paren
id|dir-&gt;ops
op_member_access_from_pointer
id|close
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driverfs_file_operations
r_static
r_struct
id|file_operations
id|driverfs_file_operations
op_assign
(brace
dot
id|read
op_assign
id|driverfs_read_file
comma
dot
id|write
op_assign
id|driverfs_write_file
comma
dot
id|llseek
op_assign
id|driverfs_file_lseek
comma
dot
id|open
op_assign
id|driverfs_open_file
comma
dot
id|release
op_assign
id|driverfs_release
comma
)brace
suffix:semicolon
DECL|variable|driverfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|driverfs_dir_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|simple_lookup
comma
)brace
suffix:semicolon
DECL|variable|driverfs_aops
r_static
r_struct
id|address_space_operations
id|driverfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|driverfs_readpage
comma
dot
id|writepage
op_assign
id|fail_writepage
comma
dot
id|prepare_write
op_assign
id|driverfs_prepare_write
comma
dot
id|commit_write
op_assign
id|driverfs_commit_write
)brace
suffix:semicolon
DECL|variable|driverfs_ops
r_static
r_struct
id|super_operations
id|driverfs_ops
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
DECL|function|driverfs_fill_super
r_static
r_int
id|driverfs_fill_super
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
id|DRIVERFS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|driverfs_ops
suffix:semicolon
id|inode
op_assign
id|driverfs_get_inode
c_func
(paren
id|sb
comma
id|S_IFDIR
op_or
l_int|0755
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%s: could not get inode!&bslash;n&quot;
comma
id|__FUNCTION__
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
id|DBG
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
id|sb-&gt;s_root
op_assign
id|root
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|driverfs_get_sb
r_static
r_struct
id|super_block
op_star
id|driverfs_get_sb
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
id|driverfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|driverfs_fs_type
r_static
r_struct
id|file_system_type
id|driverfs_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;driverfs&quot;
comma
dot
id|get_sb
op_assign
id|driverfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|get_mount
r_static
r_int
id|get_mount
c_func
(paren
r_void
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driverfs_mount
)paren
(brace
id|mntget
c_func
(paren
id|driverfs_mount
)paren
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_goto
id|go_ahead
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|driverfs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|mnt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;driverfs: could not mount!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driverfs_mount
)paren
(brace
id|driverfs_mount
op_assign
id|mnt
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_goto
id|go_ahead
suffix:semicolon
)brace
id|mntget
c_func
(paren
id|driverfs_mount
)paren
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|go_ahead
suffix:colon
id|DBG
c_func
(paren
l_string|&quot;driverfs: mount_count = %d&bslash;n&quot;
comma
id|mount_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|put_mount
r_static
r_void
id|put_mount
c_func
(paren
r_void
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|mnt
op_assign
id|driverfs_mount
suffix:semicolon
op_decrement
id|mount_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mount_count
)paren
id|driverfs_mount
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;driverfs: mount_count = %d&bslash;n&quot;
comma
id|mount_count
)paren
suffix:semicolon
)brace
DECL|function|init_driverfs_fs
r_int
id|__init
id|init_driverfs_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|driverfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|get_dentry
r_static
r_struct
id|dentry
op_star
id|get_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|qstr
id|qstr
suffix:semicolon
id|qstr.name
op_assign
id|name
suffix:semicolon
id|qstr.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|qstr.hash
op_assign
id|full_name_hash
c_func
(paren
id|name
comma
id|qstr.len
)paren
suffix:semicolon
r_return
id|lookup_hash
c_func
(paren
op_amp
id|qstr
comma
id|parent
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_create_dir - create a directory in the filesystem&n; * @entry:&t;directory entry&n; * @parent:&t;parent directory entry&n; */
r_int
DECL|function|driverfs_create_dir
id|driverfs_create_dir
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|entry
comma
r_struct
id|driver_dir_entry
op_star
id|parent
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
id|parent_dentry
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
id|entry
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|get_mount
c_func
(paren
)paren
suffix:semicolon
id|parent_dentry
op_assign
id|parent
ques
c_cond
id|parent-&gt;dentry
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_dentry
)paren
r_if
c_cond
(paren
id|driverfs_mount
op_logical_and
id|driverfs_mount-&gt;mnt_sb
)paren
id|parent_dentry
op_assign
id|driverfs_mount-&gt;mnt_sb-&gt;s_root
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_dentry
)paren
(brace
id|put_mount
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|parent_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|get_dentry
c_func
(paren
id|parent_dentry
comma
id|entry-&gt;name
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
id|entry
suffix:semicolon
id|entry-&gt;dentry
op_assign
id|dentry
suffix:semicolon
id|error
op_assign
id|driverfs_mkdir
c_func
(paren
id|parent_dentry-&gt;d_inode
comma
id|dentry
comma
id|entry-&gt;mode
)paren
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
id|parent_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|put_mount
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_create_file - create a file&n; * @entry:&t;structure describing the file&n; * @parent:&t;directory to create it in&n; */
r_int
DECL|function|driverfs_create_file
id|driverfs_create_file
c_func
(paren
r_struct
id|attribute
op_star
id|entry
comma
r_struct
id|driver_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
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
id|entry
op_logical_or
op_logical_neg
id|parent
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent-&gt;dentry
)paren
(brace
id|put_mount
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|parent-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|get_dentry
c_func
(paren
id|parent-&gt;dentry
comma
id|entry-&gt;name
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
id|entry
suffix:semicolon
id|error
op_assign
id|driverfs_create
c_func
(paren
id|parent-&gt;dentry-&gt;d_inode
comma
id|dentry
comma
id|entry-&gt;mode
)paren
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
id|parent-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_create_symlink - make a symlink&n; * @parent:&t;directory we&squot;re creating in &n; * @entry:&t;entry describing link&n; * @target:&t;place we&squot;re symlinking to&n; * &n; */
DECL|function|driverfs_create_symlink
r_int
id|driverfs_create_symlink
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|parent
comma
r_char
op_star
id|name
comma
r_char
op_star
id|target
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
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
id|parent
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent-&gt;dentry
)paren
(brace
id|put_mount
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|parent-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|get_dentry
c_func
(paren
id|parent-&gt;dentry
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
id|dentry
)paren
)paren
id|error
op_assign
id|driverfs_symlink
c_func
(paren
id|parent-&gt;dentry-&gt;d_inode
comma
id|dentry
comma
id|target
)paren
suffix:semicolon
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
id|parent-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_remove_file - exported file removal&n; * @dir:&t;directory the file supposedly resides in&n; * @name:&t;name of the file&n; *&n; * Try and find the file in the dir&squot;s list.&n; * If it&squot;s there, call __remove_file() (above) for the dentry.&n; */
DECL|function|driverfs_remove_file
r_void
id|driverfs_remove_file
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;dentry
)paren
r_return
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|get_dentry
c_func
(paren
id|dir-&gt;dentry
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
id|dentry
)paren
)paren
(brace
multiline_comment|/* make sure dentry is really there */
r_if
c_cond
(paren
id|dentry-&gt;d_inode
op_logical_and
(paren
id|dentry-&gt;d_parent-&gt;d_inode
op_eq
id|dir-&gt;dentry-&gt;d_inode
)paren
)paren
(brace
id|driverfs_unlink
c_func
(paren
id|dir-&gt;dentry-&gt;d_inode
comma
id|dentry
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dir-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_remove_dir - exportable directory removal&n; * @dir:&t;directory to remove&n; *&n; * To make sure we don&squot;t orphan anyone, first remove&n; * all the children in the list, then do clean up the directory.&n; */
DECL|function|driverfs_remove_dir
r_void
id|driverfs_remove_dir
c_func
(paren
r_struct
id|driver_dir_entry
op_star
id|dir
)paren
(brace
r_struct
id|list_head
op_star
id|node
comma
op_star
id|next
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|dir-&gt;dentry
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
r_goto
id|done
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
id|list_for_each_safe
c_func
(paren
id|node
comma
id|next
comma
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
multiline_comment|/* make sure dentry is still there */
r_if
c_cond
(paren
id|d-&gt;d_inode
)paren
id|driverfs_unlink
c_func
(paren
id|dentry-&gt;d_inode
comma
id|d
)paren
suffix:semicolon
)brace
id|d_invalidate
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driverfs_empty
c_func
(paren
id|dentry
)paren
)paren
(brace
id|dentry-&gt;d_inode-&gt;i_nlink
op_sub_assign
l_int|2
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_flags
op_or_assign
id|S_DEAD
suffix:semicolon
id|parent-&gt;d_inode-&gt;i_nlink
op_decrement
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
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
id|done
suffix:colon
id|put_mount
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|driverfs_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|driverfs_create_file
)paren
suffix:semicolon
DECL|variable|driverfs_create_symlink
id|EXPORT_SYMBOL
c_func
(paren
id|driverfs_create_symlink
)paren
suffix:semicolon
DECL|variable|driverfs_create_dir
id|EXPORT_SYMBOL
c_func
(paren
id|driverfs_create_dir
)paren
suffix:semicolon
DECL|variable|driverfs_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|driverfs_remove_file
)paren
suffix:semicolon
DECL|variable|driverfs_remove_dir
id|EXPORT_SYMBOL
c_func
(paren
id|driverfs_remove_dir
)paren
suffix:semicolon
eof
