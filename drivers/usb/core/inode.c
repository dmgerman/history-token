multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;inode.c  --  Inode/Dentry functions for the USB device file system.&n; *&n; *&t;Copyright (C) 2000 Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&t;Copyright (c) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  History:&n; *   0.1  04.01.2000  Created&n; *   0.2  10.12.2001  converted to use the vfs layer better&n; */
multiline_comment|/*****************************************************************************/
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/usbdevice_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|variable|usbfs_ops
r_static
r_struct
id|super_operations
id|usbfs_ops
suffix:semicolon
DECL|variable|default_file_operations
r_static
r_struct
id|file_operations
id|default_file_operations
suffix:semicolon
DECL|variable|usbfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|usbfs_dir_inode_operations
suffix:semicolon
DECL|variable|usbfs_mount
r_static
r_struct
id|vfsmount
op_star
id|usbfs_mount
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
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|devices_dentry
r_static
r_struct
id|dentry
op_star
id|devices_dentry
suffix:semicolon
DECL|variable|num_buses
r_static
r_int
id|num_buses
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|devuid
r_static
id|uid_t
id|devuid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|busuid
r_static
id|uid_t
id|busuid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|listuid
r_static
id|uid_t
id|listuid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|devgid
r_static
id|gid_t
id|devgid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|busgid
r_static
id|gid_t
id|busgid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|listgid
r_static
id|gid_t
id|listgid
suffix:semicolon
multiline_comment|/* = 0 */
DECL|variable|devmode
r_static
id|umode_t
id|devmode
op_assign
id|S_IWUSR
op_or
id|S_IRUGO
suffix:semicolon
DECL|variable|busmode
r_static
id|umode_t
id|busmode
op_assign
id|S_IXUGO
op_or
id|S_IRUGO
suffix:semicolon
DECL|variable|listmode
r_static
id|umode_t
id|listmode
op_assign
id|S_IRUGO
suffix:semicolon
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_char
op_star
id|data
)paren
(brace
r_char
op_star
id|curopt
op_assign
l_int|NULL
comma
op_star
id|value
suffix:semicolon
r_while
c_loop
(paren
(paren
id|curopt
op_assign
id|strsep
c_func
(paren
op_amp
id|data
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|curopt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
op_assign
id|strchr
c_func
(paren
id|curopt
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;devuid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|devuid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;devgid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|devgid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;devmode&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|devmode
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
op_amp
id|S_IRWXUGO
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;busuid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|busuid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;busgid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|busgid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;busmode&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|busmode
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
op_amp
id|S_IRWXUGO
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;listuid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|listuid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;listgid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|listgid
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|curopt
comma
l_string|&quot;listmode&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|value
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|listmode
op_assign
id|simple_strtoul
c_func
(paren
id|value
comma
op_amp
id|value
comma
l_int|0
)paren
op_amp
id|S_IRWXUGO
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|usbfs_get_inode
r_static
r_struct
id|inode
op_star
id|usbfs_get_inode
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
id|default_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|usbfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/* SMP-safe */
DECL|function|usbfs_mknod
r_static
r_int
id|usbfs_mknod
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
id|usbfs_get_inode
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
id|ENOSPC
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
DECL|function|usbfs_mkdir
r_static
r_int
id|usbfs_mkdir
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
r_return
id|usbfs_mknod
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
DECL|function|usbfs_create
r_static
r_int
id|usbfs_create
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
r_return
id|usbfs_mknod
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
)brace
DECL|function|usbfs_positive
r_static
r_inline
r_int
id|usbfs_positive
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|dentry-&gt;d_inode
op_logical_and
op_logical_neg
id|d_unhashed
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
DECL|function|usbfs_empty
r_static
r_int
id|usbfs_empty
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
id|usbfs_positive
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
DECL|function|usbfs_unlink
r_static
r_int
id|usbfs_unlink
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
id|usbfs_empty
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
DECL|macro|usbfs_rmdir
mdefine_line|#define usbfs_rmdir usbfs_unlink
multiline_comment|/* default file operations */
DECL|function|default_read_file
r_static
id|ssize_t
id|default_read_file
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|default_write_file
r_static
id|ssize_t
id|default_write_file
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
r_return
id|count
suffix:semicolon
)brace
DECL|function|default_file_lseek
r_static
id|loff_t
id|default_file_lseek
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
DECL|function|default_open
r_static
r_int
id|default_open
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
r_if
c_cond
(paren
id|inode-&gt;u.generic_ip
)paren
id|filp-&gt;private_data
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|default_file_operations
r_static
r_struct
id|file_operations
id|default_file_operations
op_assign
(brace
id|read
suffix:colon
id|default_read_file
comma
id|write
suffix:colon
id|default_write_file
comma
id|open
suffix:colon
id|default_open
comma
id|llseek
suffix:colon
id|default_file_lseek
comma
)brace
suffix:semicolon
DECL|variable|usbfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|usbfs_dir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|usbfs_create
comma
id|lookup
suffix:colon
id|simple_lookup
comma
id|unlink
suffix:colon
id|usbfs_unlink
comma
id|mkdir
suffix:colon
id|usbfs_mkdir
comma
id|rmdir
suffix:colon
id|usbfs_rmdir
comma
)brace
suffix:semicolon
DECL|variable|usbfs_ops
r_static
r_struct
id|super_operations
id|usbfs_ops
op_assign
(brace
id|statfs
suffix:colon
id|simple_statfs
comma
id|drop_inode
suffix:colon
id|generic_delete_inode
comma
)brace
suffix:semicolon
DECL|function|usbfs_fill_super
r_static
r_int
id|usbfs_fill_super
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
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|sb
comma
id|data
)paren
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;usbfs: mount parameter error:&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|USBDEVICE_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|usbfs_ops
suffix:semicolon
id|inode
op_assign
id|usbfs_get_inode
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
id|dbg
c_func
(paren
l_string|&quot;%s: could not get inode!&quot;
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
id|dbg
c_func
(paren
l_string|&quot;%s: could not get root dentry!&quot;
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
multiline_comment|/**&n; * fs_create_by_name - create a file, given a name&n; * @name:&t;name of file&n; * @mode:&t;type of file&n; * @parent:&t;dentry of directory to create it in&n; * @dentry:&t;resulting dentry of file&n; *&n; * There is a bit of overhead in creating a file - basically, we &n; * have to hash the name of the file, then look it up. This will&n; * prevent files of the same name. &n; * We then call the proper vfs_ function to take care of all the &n; * file creation details. &n; * This function handles both regular files and directories.&n; */
DECL|function|fs_create_by_name
r_static
r_int
id|fs_create_by_name
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|dentry
op_star
op_star
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
id|d
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|qstr
id|qstr
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* If the parent is not specified, we create it in the root.&n;&t; * We need the root dentry to do this, which is in the super &n;&t; * block. A pointer to that is in the struct vfsmount that we&n;&t; * have around.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
r_if
c_cond
(paren
id|usbfs_mount
op_logical_and
id|usbfs_mount-&gt;mnt_sb
)paren
(brace
id|parent
op_assign
id|usbfs_mount-&gt;mnt_sb-&gt;s_root
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;Ah! can not find a parent!&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|dentry
op_assign
l_int|NULL
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
id|parent
op_assign
id|dget
c_func
(paren
id|parent
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|d
op_assign
id|lookup_hash
c_func
(paren
op_amp
id|qstr
comma
id|parent
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|d
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
(brace
r_switch
c_cond
(paren
id|mode
op_amp
id|S_IFMT
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
id|S_IFREG
suffix:colon
id|error
op_assign
id|vfs_create
c_func
(paren
id|parent-&gt;d_inode
comma
id|d
comma
id|mode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|error
op_assign
id|vfs_mkdir
c_func
(paren
id|parent-&gt;d_inode
comma
id|d
comma
id|mode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
c_func
(paren
l_string|&quot;cannot create special files&quot;
)paren
suffix:semicolon
)brace
op_star
id|dentry
op_assign
id|d
suffix:semicolon
)brace
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
r_return
id|error
suffix:semicolon
)brace
DECL|function|fs_create_file
r_static
r_struct
id|dentry
op_star
id|fs_create_file
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|dentry
op_star
id|parent
comma
r_void
op_star
id|data
comma
r_struct
id|file_operations
op_star
id|fops
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;creating file &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
id|error
op_assign
id|fs_create_by_name
c_func
(paren
id|name
comma
id|mode
comma
id|parent
comma
op_amp
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|data
)paren
id|dentry-&gt;d_inode-&gt;u.generic_ip
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|fops
)paren
id|dentry-&gt;d_inode-&gt;i_fop
op_assign
id|fops
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_uid
op_assign
id|uid
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_gid
op_assign
id|gid
suffix:semicolon
)brace
)brace
r_return
id|dentry
suffix:semicolon
)brace
DECL|function|fs_remove_file
r_static
r_void
id|fs_remove_file
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
id|parent
op_assign
id|dentry-&gt;d_parent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
op_logical_or
op_logical_neg
id|parent-&gt;d_inode
)paren
r_return
suffix:semicolon
id|down
c_func
(paren
op_amp
id|parent-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usbfs_positive
c_func
(paren
id|dentry
)paren
)paren
(brace
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
id|vfs_rmdir
c_func
(paren
id|parent-&gt;d_inode
comma
id|dentry
)paren
suffix:semicolon
r_else
id|vfs_unlink
c_func
(paren
id|parent-&gt;d_inode
comma
id|dentry
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dentry
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
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * The usbdevfs name is now deprecated (as of 2.5.1).&n; * It will be removed when the 2.7.x development cycle is started.&n; * You have been warned :)&n; */
DECL|function|usb_get_sb
r_static
r_struct
id|super_block
op_star
id|usb_get_sb
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
id|usbfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|usbdevice_fs_type
r_static
r_struct
id|file_system_type
id|usbdevice_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;usbdevfs&quot;
comma
id|get_sb
suffix:colon
id|usb_get_sb
comma
id|kill_sb
suffix:colon
id|kill_anon_super
comma
)brace
suffix:semicolon
DECL|variable|usb_fs_type
r_static
r_struct
id|file_system_type
id|usb_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;usbfs&quot;
comma
id|get_sb
suffix:colon
id|usb_get_sb
comma
id|kill_sb
suffix:colon
id|kill_anon_super
comma
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|get_mount
r_static
r_int
id|get_mount
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
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usbfs_mount
)paren
(brace
id|mntget
c_func
(paren
id|usbfs_mount
)paren
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
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
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|mnt
op_assign
id|kern_mount
(paren
op_amp
id|usbdevice_fs_type
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
id|err
(paren
l_string|&quot;could not mount the fs...erroring out!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|spin_lock
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbfs_mount
)paren
(brace
id|usbfs_mount
op_assign
id|mnt
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
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
id|usbfs_mount
)paren
suffix:semicolon
op_increment
id|mount_count
suffix:semicolon
id|spin_unlock
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
id|go_ahead
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;mount_count = %d&quot;
comma
id|mount_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_mount
r_static
r_void
id|remove_mount
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
(paren
op_amp
id|mount_lock
)paren
suffix:semicolon
id|mnt
op_assign
id|usbfs_mount
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
id|usbfs_mount
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
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
id|dbg
c_func
(paren
l_string|&quot;mount_count = %d&quot;
comma
id|mount_count
)paren
suffix:semicolon
)brace
DECL|function|create_special_files
r_static
r_int
id|create_special_files
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
multiline_comment|/* create the devices and drivers special files */
id|retval
op_assign
id|get_mount
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|devices_dentry
op_assign
id|fs_create_file
(paren
l_string|&quot;devices&quot;
comma
id|listmode
op_or
id|S_IFREG
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|usbdevfs_devices_fops
comma
id|listuid
comma
id|listgid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devices_dentry
op_eq
l_int|NULL
)paren
(brace
id|err
(paren
l_string|&quot;Unable to create devices usbfs file&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_special_files
r_static
r_void
id|remove_special_files
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|devices_dentry
)paren
id|fs_remove_file
(paren
id|devices_dentry
)paren
suffix:semicolon
id|devices_dentry
op_assign
l_int|NULL
suffix:semicolon
id|remove_mount
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|usbfs_update_special
r_void
id|usbfs_update_special
(paren
r_void
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|devices_dentry
)paren
(brace
id|inode
op_assign
id|devices_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
)brace
DECL|function|usbfs_add_bus
r_void
id|usbfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|retval
suffix:semicolon
multiline_comment|/* create the special files if this is the first bus added */
r_if
c_cond
(paren
id|num_buses
op_eq
l_int|0
)paren
(brace
id|retval
op_assign
id|create_special_files
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
suffix:semicolon
)brace
op_increment
id|num_buses
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;%03d&quot;
comma
id|bus-&gt;busnum
)paren
suffix:semicolon
id|bus-&gt;dentry
op_assign
id|fs_create_file
(paren
id|name
comma
id|busmode
op_or
id|S_IFDIR
comma
l_int|NULL
comma
id|bus
comma
l_int|NULL
comma
id|busuid
comma
id|busgid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;dentry
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|usbfs_update_special
c_func
(paren
)paren
suffix:semicolon
id|usbdevfs_conn_disc_event
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|usbfs_remove_bus
r_void
id|usbfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;dentry
)paren
(brace
id|fs_remove_file
(paren
id|bus-&gt;dentry
)paren
suffix:semicolon
id|bus-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
op_decrement
id|num_buses
suffix:semicolon
r_if
c_cond
(paren
id|num_buses
op_le
l_int|0
)paren
(brace
id|remove_special_files
c_func
(paren
)paren
suffix:semicolon
id|num_buses
op_assign
l_int|0
suffix:semicolon
)brace
id|usbfs_update_special
c_func
(paren
)paren
suffix:semicolon
id|usbdevfs_conn_disc_event
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|usbfs_add_device
r_void
id|usbfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|i_size
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;%03d&quot;
comma
id|dev-&gt;devnum
)paren
suffix:semicolon
id|dev-&gt;dentry
op_assign
id|fs_create_file
(paren
id|name
comma
id|devmode
op_or
id|S_IFREG
comma
id|dev-&gt;bus-&gt;dentry
comma
id|dev
comma
op_amp
id|usbdevfs_device_file_operations
comma
id|devuid
comma
id|devgid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dentry
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Set the size of the device&squot;s file to be&n;&t; * equal to the size of the device descriptors. */
id|i_size
op_assign
r_sizeof
(paren
r_struct
id|usb_device_descriptor
)paren
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
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|usb_config_descriptor
op_star
id|config
op_assign
(paren
r_struct
id|usb_config_descriptor
op_star
)paren
id|dev-&gt;rawdescriptors
(braket
id|i
)braket
suffix:semicolon
id|i_size
op_add_assign
id|le16_to_cpu
(paren
id|config-&gt;wTotalLength
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;dentry-&gt;d_inode
)paren
id|dev-&gt;dentry-&gt;d_inode-&gt;i_size
op_assign
id|i_size
suffix:semicolon
id|usbfs_update_special
c_func
(paren
)paren
suffix:semicolon
id|usbdevfs_conn_disc_event
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|usbfs_remove_device
r_void
id|usbfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_struct
id|dev_state
op_star
id|ds
suffix:semicolon
r_struct
id|siginfo
id|sinfo
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dentry
)paren
(brace
id|fs_remove_file
(paren
id|dev-&gt;dentry
)paren
suffix:semicolon
id|dev-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dev-&gt;filelist
)paren
)paren
(brace
id|ds
op_assign
id|list_entry
c_func
(paren
id|dev-&gt;filelist.next
comma
r_struct
id|dev_state
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|ds-&gt;list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ds-&gt;list
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|ds-&gt;devsem
)paren
suffix:semicolon
id|ds-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|ds-&gt;devsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ds-&gt;discsignr
)paren
(brace
id|sinfo.si_signo
op_assign
id|SIGPIPE
suffix:semicolon
id|sinfo.si_errno
op_assign
id|EPIPE
suffix:semicolon
id|sinfo.si_code
op_assign
id|SI_ASYNCIO
suffix:semicolon
id|sinfo.si_addr
op_assign
id|ds-&gt;disccontext
suffix:semicolon
id|send_sig_info
c_func
(paren
id|ds-&gt;discsignr
comma
op_amp
id|sinfo
comma
id|ds-&gt;disctask
)paren
suffix:semicolon
)brace
)brace
id|usbfs_update_special
c_func
(paren
)paren
suffix:semicolon
id|usbdevfs_conn_disc_event
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_PROC_FS&t;&t;
DECL|variable|usbdir
r_static
r_struct
id|proc_dir_entry
op_star
id|usbdir
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;
DECL|function|usbfs_init
r_int
id|__init
id|usbfs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|usbdevfs_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|usb_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|usbdevfs_driver
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|retval
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|usbdevice_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|usb_fs_type
)paren
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|usbdevfs_driver
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS&t;&t;
multiline_comment|/* create mount point for usbdevfs */
id|usbdir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;usb&quot;
comma
id|proc_bus
)paren
suffix:semicolon
macro_line|#endif&t;
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usbfs_cleanup
r_void
id|__exit
id|usbfs_cleanup
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|usbdevfs_driver
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|usb_fs_type
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|usbdevice_fs_type
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS&t;
r_if
c_cond
(paren
id|usbdir
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;usb&quot;
comma
id|proc_bus
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
