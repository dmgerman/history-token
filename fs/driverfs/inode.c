multiline_comment|/*&n; * driverfs.c - The device driver file system&n; *&n; * Copyright (c) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * This is a simple, ram-based filesystem, which allows kernel&n; * callbacks for read/write of files.&n; *&n; * Please see Documentation/filesystems/driverfs.txt for more information.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
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
DECL|variable|driverfs_dir_operations
r_static
r_struct
id|file_operations
id|driverfs_dir_operations
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
DECL|variable|driverfs_dentry_dir_ops
r_static
r_struct
id|dentry_operations
id|driverfs_dentry_dir_ops
suffix:semicolon
DECL|variable|driverfs_dentry_file_ops
r_static
r_struct
id|dentry_operations
id|driverfs_dentry_file_ops
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
DECL|function|driverfs_statfs
r_static
r_int
id|driverfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
id|buf-&gt;f_type
op_assign
id|DRIVERFS_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
l_int|255
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* SMP-safe */
DECL|function|driverfs_lookup
r_static
r_struct
id|dentry
op_star
id|driverfs_lookup
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
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|driverfs_dir_operations
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
r_int
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* only allow create if -&gt;d_fsdata is not NULL (so we can assume it &n;&t; * comes from the driverfs API below. */
r_if
c_cond
(paren
id|dentry-&gt;d_fsdata
op_logical_and
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
id|dget
c_func
(paren
id|dentry
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
id|dentry-&gt;d_op
op_assign
op_amp
id|driverfs_dentry_dir_ops
suffix:semicolon
r_return
id|driverfs_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
op_or
id|S_IFDIR
comma
l_int|0
)paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dentry-&gt;d_op
op_assign
op_amp
id|driverfs_dentry_file_ops
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
op_or
id|S_IFREG
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
id|res
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
r_int
id|error
op_assign
op_minus
id|ENOTEMPTY
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
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
DECL|macro|driverfs_rmdir
mdefine_line|#define driverfs_rmdir driverfs_unlink
multiline_comment|/**&n; * driverfs_read_file - &quot;read&quot; data from a file.&n; * @file:&t;file pointer&n; * @buf:&t;buffer to fill&n; * @count:&t;number of bytes to read&n; * @ppos:&t;starting offset in file&n; *&n; * Userspace wants data from a file. It is up to the creator of the file to&n; * provide that data.&n; * There is a struct driver_file_entry embedded in file-&gt;private_data. We&n; * obtain that and check if the read callback is implemented. If so, we call&n; * it, passing the data field of the file entry.&n; * Said callback is responsible for filling the buffer and returning the number&n; * of bytes it put in it. We update @ppos correctly.&n; */
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
id|driver_file_entry
op_star
id|entry
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
r_struct
id|device
op_star
id|dev
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|driver_file_entry
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%s: file entry is NULL&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;show
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
id|dev
op_assign
id|list_entry
c_func
(paren
id|entry-&gt;parent
comma
r_struct
id|device
comma
id|dir
)paren
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
id|entry
op_member_access_from_pointer
id|show
c_func
(paren
id|dev
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
id|driver_file_entry
op_star
id|entry
suffix:semicolon
r_struct
id|device
op_star
id|dev
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
id|entry
op_assign
(paren
r_struct
id|driver_file_entry
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%s: file entry is NULL&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;store
)paren
r_return
l_int|0
suffix:semicolon
id|dev
op_assign
id|list_entry
c_func
(paren
id|entry-&gt;parent
comma
r_struct
id|device
comma
id|dir
)paren
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
id|entry
op_member_access_from_pointer
id|store
c_func
(paren
id|dev
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
id|lock_kernel
c_func
(paren
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
id|unlock_kernel
c_func
(paren
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
id|driver_file_entry
op_star
id|entry
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|driver_file_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
id|list_entry
c_func
(paren
id|entry-&gt;parent
comma
r_struct
id|device
comma
id|dir
)paren
suffix:semicolon
id|get_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
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
id|driver_file_entry
op_star
id|entry
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|driver_file_entry
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
id|list_entry
c_func
(paren
id|entry-&gt;parent
comma
r_struct
id|device
comma
id|dir
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|driverfs_d_delete_file
r_static
r_int
id|driverfs_d_delete_file
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|driver_file_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|driver_file_entry
op_star
)paren
id|dentry-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|kfree
c_func
(paren
id|entry
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
id|read
suffix:colon
id|driverfs_read_file
comma
id|write
suffix:colon
id|driverfs_write_file
comma
id|llseek
suffix:colon
id|driverfs_file_lseek
comma
id|open
suffix:colon
id|driverfs_open_file
comma
id|release
suffix:colon
id|driverfs_release
comma
)brace
suffix:semicolon
DECL|variable|driverfs_dir_operations
r_static
r_struct
id|file_operations
id|driverfs_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|dcache_readdir
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
id|create
suffix:colon
id|driverfs_create
comma
id|lookup
suffix:colon
id|driverfs_lookup
comma
id|unlink
suffix:colon
id|driverfs_unlink
comma
id|mkdir
suffix:colon
id|driverfs_mkdir
comma
id|rmdir
suffix:colon
id|driverfs_rmdir
comma
)brace
suffix:semicolon
DECL|variable|driverfs_dentry_file_ops
r_static
r_struct
id|dentry_operations
id|driverfs_dentry_file_ops
op_assign
(brace
id|d_delete
suffix:colon
id|driverfs_d_delete_file
comma
)brace
suffix:semicolon
DECL|variable|driverfs_ops
r_static
r_struct
id|super_operations
id|driverfs_ops
op_assign
(brace
id|statfs
suffix:colon
id|driverfs_statfs
comma
id|put_inode
suffix:colon
id|force_delete
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
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;driverfs&quot;
comma
id|get_sb
suffix:colon
id|driverfs_get_sb
comma
id|fs_flags
suffix:colon
id|FS_LITTER
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
r_struct
id|qstr
id|qstr
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
id|qstr.name
op_assign
id|entry-&gt;name
suffix:semicolon
id|qstr.len
op_assign
id|strlen
c_func
(paren
id|entry-&gt;name
)paren
suffix:semicolon
id|qstr.hash
op_assign
id|full_name_hash
c_func
(paren
id|entry-&gt;name
comma
id|qstr.len
)paren
suffix:semicolon
id|dentry
op_assign
id|lookup_hash
c_func
(paren
op_amp
id|qstr
comma
id|parent_dentry
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
id|vfs_mkdir
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
id|driver_file_entry
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
r_struct
id|qstr
id|qstr
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
multiline_comment|/* make sure we&squot;re mounted */
id|get_mount
c_func
(paren
)paren
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
id|qstr.name
op_assign
id|entry-&gt;name
suffix:semicolon
id|qstr.len
op_assign
id|strlen
c_func
(paren
id|entry-&gt;name
)paren
suffix:semicolon
id|qstr.hash
op_assign
id|full_name_hash
c_func
(paren
id|entry-&gt;name
comma
id|qstr.len
)paren
suffix:semicolon
id|dentry
op_assign
id|lookup_hash
c_func
(paren
op_amp
id|qstr
comma
id|parent-&gt;dentry
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
id|vfs_create
c_func
(paren
id|parent-&gt;dentry-&gt;d_inode
comma
id|dentry
comma
id|entry-&gt;mode
)paren
suffix:semicolon
multiline_comment|/* Still good? Ok, then fill in the blanks: */
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|dentry-&gt;d_inode-&gt;u.generic_ip
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
id|entry-&gt;parent
op_assign
id|parent
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|entry-&gt;node
comma
op_amp
id|parent-&gt;files
)paren
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
id|parent-&gt;dentry-&gt;d_inode-&gt;i_sem
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
id|list_head
op_star
id|node
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
id|node
op_assign
id|dir-&gt;files.next
suffix:semicolon
r_while
c_loop
(paren
id|node
op_ne
op_amp
id|dir-&gt;files
)paren
(brace
r_struct
id|driver_file_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|driver_file_entry
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|name
)paren
)paren
(brace
id|list_del_init
c_func
(paren
id|node
)paren
suffix:semicolon
id|vfs_unlink
c_func
(paren
id|entry-&gt;dentry-&gt;d_parent-&gt;d_inode
comma
id|entry-&gt;dentry
)paren
suffix:semicolon
id|put_mount
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|node
op_assign
id|node-&gt;next
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dir-&gt;dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * driverfs_remove_dir - exportable directory removal&n; * @dir:&t;directory to remove&n; *&n; * To make sure we don&squot;t orphan anyone, first remove&n; * all the children in the list, then do vfs_rmdir() to remove it&n; * and decrement the refcount..&n; */
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
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|dir-&gt;dentry
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
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|node
op_assign
id|dir-&gt;files.next
suffix:semicolon
r_while
c_loop
(paren
id|node
op_ne
op_amp
id|dir-&gt;files
)paren
(brace
r_struct
id|driver_file_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|driver_file_entry
comma
id|node
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|node
)paren
suffix:semicolon
id|vfs_unlink
c_func
(paren
id|dentry-&gt;d_inode
comma
id|entry-&gt;dentry
)paren
suffix:semicolon
id|put_mount
c_func
(paren
)paren
suffix:semicolon
id|node
op_assign
id|dir-&gt;files.next
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|vfs_rmdir
c_func
(paren
id|dentry-&gt;d_parent-&gt;d_inode
comma
id|dentry
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dentry-&gt;d_parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
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
