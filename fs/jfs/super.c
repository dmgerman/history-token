multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *   Portions Copyright (c) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_metapage.h&quot;
macro_line|#include &quot;jfs_superblock.h&quot;
macro_line|#include &quot;jfs_dmap.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_acl.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Journaled Filesystem (JFS)&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Steve Best/Dave Kleikamp/Barry Arndt, IBM&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|jfs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|jfs_inode_cachep
suffix:semicolon
DECL|variable|jfs_super_operations
r_static
r_struct
id|super_operations
id|jfs_super_operations
suffix:semicolon
DECL|variable|jfs_export_operations
r_static
r_struct
id|export_operations
id|jfs_export_operations
suffix:semicolon
DECL|variable|jfs_fs_type
r_static
r_struct
id|file_system_type
id|jfs_fs_type
suffix:semicolon
DECL|variable|jfs_stop_threads
r_int
id|jfs_stop_threads
suffix:semicolon
DECL|variable|jfsIOthread
r_static
id|pid_t
id|jfsIOthread
suffix:semicolon
DECL|variable|jfsCommitThread
r_static
id|pid_t
id|jfsCommitThread
suffix:semicolon
DECL|variable|jfsSyncThread
r_static
id|pid_t
id|jfsSyncThread
suffix:semicolon
DECL|variable|jfsIOwait
id|DECLARE_COMPLETION
c_func
(paren
id|jfsIOwait
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_JFS_DEBUG
DECL|variable|jfsloglevel
r_int
id|jfsloglevel
op_assign
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|jfsloglevel
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|jfsloglevel
comma
l_string|&quot;Specify JFS loglevel (0, 1 or 2)&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * External declarations&n; */
r_extern
r_struct
id|inode
op_star
id|jfs_iget
c_func
(paren
r_struct
id|super_block
op_star
comma
id|ino_t
)paren
suffix:semicolon
r_extern
r_int
id|jfs_mount
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|jfs_mount_rw
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|jfs_umount
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|jfs_umount_rw
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|jfsIOWait
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|jfs_lazycommit
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|jfs_sync
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|jfs_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|jfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|jfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|jfs_get_parent
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|jfs_extendfs
c_func
(paren
r_struct
id|super_block
op_star
comma
id|s64
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef PROC_FS_JFS&t;&t;/* see jfs_debug.h */
r_extern
r_void
id|jfs_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jfs_proc_clean
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
id|wait_queue_head_t
id|jfs_IO_thread_wait
suffix:semicolon
r_extern
id|wait_queue_head_t
id|jfs_commit_thread_wait
suffix:semicolon
r_extern
id|wait_queue_head_t
id|jfs_sync_thread_wait
suffix:semicolon
DECL|function|jfs_alloc_inode
r_static
r_struct
id|inode
op_star
id|jfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jfs_inode_info
op_star
id|jfs_inode
suffix:semicolon
id|jfs_inode
op_assign
id|kmem_cache_alloc
c_func
(paren
id|jfs_inode_cachep
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jfs_inode
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|jfs_inode-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|jfs_destroy_inode
r_static
r_void
id|jfs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ji-&gt;active_ag
op_ne
op_minus
l_int|1
)paren
(brace
r_struct
id|bmap
op_star
id|bmap
op_assign
id|JFS_SBI
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|bmap
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bmap-&gt;db_active
(braket
id|ji-&gt;active_ag
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_JFS_POSIX_ACL
r_if
c_cond
(paren
id|ji-&gt;i_acl
op_logical_and
(paren
id|ji-&gt;i_acl
op_ne
id|JFS_ACL_NOT_CACHED
)paren
)paren
id|posix_acl_release
c_func
(paren
id|ji-&gt;i_acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ji-&gt;i_default_acl
op_logical_and
(paren
id|ji-&gt;i_default_acl
op_ne
id|JFS_ACL_NOT_CACHED
)paren
)paren
id|posix_acl_release
c_func
(paren
id|ji-&gt;i_default_acl
)paren
suffix:semicolon
macro_line|#endif
id|kmem_cache_free
c_func
(paren
id|jfs_inode_cachep
comma
id|ji
)paren
suffix:semicolon
)brace
DECL|function|jfs_statfs
r_static
r_int
id|jfs_statfs
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
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
id|s64
id|maxinodes
suffix:semicolon
r_struct
id|inomap
op_star
id|imap
op_assign
id|JFS_IP
c_func
(paren
id|sbi-&gt;ipimap
)paren
op_member_access_from_pointer
id|i_imap
suffix:semicolon
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In jfs_statfs&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|JFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sbi-&gt;bsize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|sbi-&gt;bmap-&gt;db_mapsize
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|sbi-&gt;bmap-&gt;db_nfree
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|sbi-&gt;bmap-&gt;db_nfree
suffix:semicolon
multiline_comment|/*&n;&t; * If we really return the number of allocated &amp; free inodes, some&n;&t; * applications will fail because they won&squot;t see enough free inodes.&n;&t; * We&squot;ll try to calculate some guess as to how may inodes we can&n;&t; * really allocate&n;&t; *&n;&t; * buf-&gt;f_files = atomic_read(&amp;imap-&gt;im_numinos);&n;&t; * buf-&gt;f_ffree = atomic_read(&amp;imap-&gt;im_numfree);&n;&t; */
id|maxinodes
op_assign
id|min
c_func
(paren
(paren
id|s64
)paren
id|atomic_read
c_func
(paren
op_amp
id|imap-&gt;im_numinos
)paren
op_plus
(paren
(paren
id|sbi-&gt;bmap-&gt;db_nfree
op_rshift
id|imap-&gt;im_l2nbperiext
)paren
op_lshift
id|L2INOSPEREXT
)paren
comma
(paren
id|s64
)paren
l_int|0xffffffffLL
)paren
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|maxinodes
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|maxinodes
op_minus
(paren
id|atomic_read
c_func
(paren
op_amp
id|imap-&gt;im_numinos
)paren
op_minus
id|atomic_read
c_func
(paren
op_amp
id|imap-&gt;im_numfree
)paren
)paren
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|JFS_NAME_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jfs_put_super
r_static
r_void
id|jfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In jfs_put_super&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|jfs_umount
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_umount failed with return code %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
id|unload_nls
c_func
(paren
id|sbi-&gt;nls_tab
)paren
suffix:semicolon
id|sbi-&gt;nls_tab
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_struct
id|super_block
op_star
id|sb
comma
id|s64
op_star
id|newLVSize
)paren
(brace
r_void
op_star
id|nls_map
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|this_char
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
op_star
id|newLVSize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_char
op_assign
id|strsep
c_func
(paren
op_amp
id|options
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
id|this_char
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
id|this_char
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
id|this_char
comma
l_string|&quot;iocharset&quot;
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
op_star
id|value
)paren
r_goto
id|needs_arg
suffix:semicolon
r_if
c_cond
(paren
id|nls_map
)paren
multiline_comment|/* specified iocharset twice! */
id|unload_nls
c_func
(paren
id|nls_map
)paren
suffix:semicolon
id|nls_map
op_assign
id|load_nls
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nls_map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFS: charset not found&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;resize&quot;
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
op_star
id|value
)paren
(brace
op_star
id|newLVSize
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_size
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
op_star
id|newLVSize
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFS: Cannot determine volume size&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
op_star
id|newLVSize
op_assign
id|simple_strtoull
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
multiline_comment|/* Silently ignore the quota options */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;grpquota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;noquota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;quota&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|this_char
comma
l_string|&quot;usrquota&quot;
)paren
)paren
multiline_comment|/* Don&squot;t do anything ;-) */
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;jfs: Unrecognized mount option %s&bslash;n&quot;
comma
id|this_char
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nls_map
)paren
(brace
multiline_comment|/* Discard old (if remount) */
r_if
c_cond
(paren
id|sbi-&gt;nls_tab
)paren
id|unload_nls
c_func
(paren
id|sbi-&gt;nls_tab
)paren
suffix:semicolon
id|sbi-&gt;nls_tab
op_assign
id|nls_map
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|needs_arg
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFS: %s needs an argument&bslash;n&quot;
comma
id|this_char
)paren
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|nls_map
)paren
id|unload_nls
c_func
(paren
id|nls_map
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jfs_remount
r_int
id|jfs_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
id|s64
id|newLVSize
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
id|data
comma
id|sb
comma
op_amp
id|newLVSize
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newLVSize
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFS: resize requires volume to be mounted read-write&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EROFS
suffix:semicolon
)brace
id|rc
op_assign
id|jfs_extendfs
c_func
(paren
id|sb
comma
id|newLVSize
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
op_logical_and
op_logical_neg
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
id|jfs_mount_rw
c_func
(paren
id|sb
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
op_logical_and
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
id|jfs_umount_rw
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jfs_fill_super
r_static
r_int
id|jfs_fill_super
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
id|jfs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|s64
id|newLVSize
op_assign
l_int|0
suffix:semicolon
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In jfs_read_super: s_flags=0x%lx&bslash;n&quot;
comma
id|sb-&gt;s_flags
)paren
)paren
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|jfs_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|memset
c_func
(paren
id|sbi
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|jfs_sb_info
)paren
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|sbi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
(paren
r_char
op_star
)paren
id|data
comma
id|sb
comma
op_amp
id|newLVSize
)paren
)paren
(brace
id|kfree
c_func
(paren
id|sbi
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
id|newLVSize
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;resize option for remount only&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize blocksize to 4K.&n;&t; */
id|sb_set_blocksize
c_func
(paren
id|sb
comma
id|PSIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set method vectors.&n;&t; */
id|sb-&gt;s_op
op_assign
op_amp
id|jfs_super_operations
suffix:semicolon
id|sb-&gt;s_export_op
op_assign
op_amp
id|jfs_export_operations
suffix:semicolon
id|rc
op_assign
id|jfs_mount
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_mount failed w/return code = %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_goto
id|out_kfree
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
id|sbi-&gt;log
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|rc
op_assign
id|jfs_mount_rw
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_mount_rw failed w/return code = %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_goto
id|out_no_rw
suffix:semicolon
)brace
)brace
id|sb-&gt;s_magic
op_assign
id|JFS_SUPER_MAGIC
suffix:semicolon
id|inode
op_assign
id|jfs_iget
c_func
(paren
id|sb
comma
id|ROOT_I
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out_no_root
suffix:semicolon
id|sb-&gt;s_root
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
id|sb-&gt;s_root
)paren
r_goto
id|out_no_root
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;nls_tab
)paren
id|sbi-&gt;nls_tab
op_assign
id|load_nls_default
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* logical blocks are represented by 40 bits in pxd_t, etc. */
id|sb-&gt;s_maxbytes
op_assign
(paren
(paren
id|u64
)paren
id|sb-&gt;s_blocksize
)paren
op_lshift
l_int|40
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
multiline_comment|/*&n;&t; * Page cache is indexed by long.&n;&t; * I would use MAX_LFS_FILESIZE, but it&squot;s only half as big&n;&t; */
id|sb-&gt;s_maxbytes
op_assign
id|min
c_func
(paren
(paren
(paren
id|u64
)paren
id|PAGE_CACHE_SIZE
op_lshift
l_int|32
)paren
op_minus
l_int|1
comma
id|sb-&gt;s_maxbytes
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|out_no_root
suffix:colon
id|jEVENT
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_read_super: get root inode failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out_no_rw
suffix:colon
id|rc
op_assign
id|jfs_umount
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_umount failed with return code %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
id|out_kfree
suffix:colon
r_if
c_cond
(paren
id|sbi-&gt;nls_tab
)paren
id|unload_nls
c_func
(paren
id|sbi-&gt;nls_tab
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|jfs_write_super_lockfs
r_static
r_void
id|jfs_write_super_lockfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
op_assign
id|sbi-&gt;log
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|txQuiesce
c_func
(paren
id|sb
)paren
suffix:semicolon
id|lmLogShutdown
c_func
(paren
id|log
)paren
suffix:semicolon
)brace
)brace
DECL|function|jfs_unlockfs
r_static
r_void
id|jfs_unlockfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
op_assign
id|sbi-&gt;log
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|lmLogInit
c_func
(paren
id|log
)paren
)paren
)paren
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;jfs_unlock failed with return code %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_else
id|txResume
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
)brace
DECL|function|jfs_get_sb
r_static
r_struct
id|super_block
op_star
id|jfs_get_sb
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
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|jfs_fill_super
)paren
suffix:semicolon
)brace
DECL|function|jfs_sync_fs
r_static
r_int
id|jfs_sync_fs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|wait
)paren
(brace
r_struct
id|jfs_log
op_star
id|log
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|log
suffix:semicolon
multiline_comment|/* log == NULL indicates read-only mount */
r_if
c_cond
(paren
id|log
)paren
id|jfs_flush_journal
c_func
(paren
id|log
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jfs_super_operations
r_static
r_struct
id|super_operations
id|jfs_super_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|jfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|jfs_destroy_inode
comma
dot
id|dirty_inode
op_assign
id|jfs_dirty_inode
comma
dot
id|write_inode
op_assign
id|jfs_write_inode
comma
dot
id|delete_inode
op_assign
id|jfs_delete_inode
comma
dot
id|put_super
op_assign
id|jfs_put_super
comma
dot
id|sync_fs
op_assign
id|jfs_sync_fs
comma
dot
id|write_super_lockfs
op_assign
id|jfs_write_super_lockfs
comma
dot
id|unlockfs
op_assign
id|jfs_unlockfs
comma
dot
id|statfs
op_assign
id|jfs_statfs
comma
dot
id|remount_fs
op_assign
id|jfs_remount
comma
)brace
suffix:semicolon
DECL|variable|jfs_export_operations
r_static
r_struct
id|export_operations
id|jfs_export_operations
op_assign
(brace
dot
id|get_parent
op_assign
id|jfs_get_parent
comma
)brace
suffix:semicolon
DECL|variable|jfs_fs_type
r_static
r_struct
id|file_system_type
id|jfs_fs_type
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
l_string|&quot;jfs&quot;
comma
dot
id|get_sb
op_assign
id|jfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
r_extern
r_int
id|metapage_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|txInit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|txExit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|metapage_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|jfs_inode_info
op_star
id|jfs_ip
op_assign
(paren
r_struct
id|jfs_inode_info
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|jfs_ip-&gt;anon_inode_list
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|jfs_ip-&gt;rdwrlock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|jfs_ip-&gt;commit_sem
)paren
suffix:semicolon
id|jfs_ip-&gt;atlhead
op_assign
l_int|0
suffix:semicolon
id|jfs_ip-&gt;active_ag
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_JFS_POSIX_ACL
id|jfs_ip-&gt;i_acl
op_assign
id|JFS_ACL_NOT_CACHED
suffix:semicolon
id|jfs_ip-&gt;i_default_acl
op_assign
id|JFS_ACL_NOT_CACHED
suffix:semicolon
macro_line|#endif
id|inode_init_once
c_func
(paren
op_amp
id|jfs_ip-&gt;vfs_inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|init_jfs_fs
r_static
r_int
id|__init
id|init_jfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|jfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;jfs_ip&quot;
comma
r_sizeof
(paren
r_struct
id|jfs_inode_info
)paren
comma
l_int|0
comma
l_int|0
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jfs_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * Metapage initialization&n;&t; */
id|rc
op_assign
id|metapage_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;metapage_init failed w/rc = %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_goto
id|free_slab
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Transaction Manager initialization&n;&t; */
id|rc
op_assign
id|txInit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;txInit failed w/rc = %d&bslash;n&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
r_goto
id|free_metapage
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * I/O completion thread (endio)&n;&t; */
id|jfsIOthread
op_assign
id|kernel_thread
c_func
(paren
id|jfsIOWait
comma
l_int|0
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jfsIOthread
OL
l_int|0
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;init_jfs_fs: fork failed w/rc = %d&bslash;n&quot;
comma
id|jfsIOthread
)paren
)paren
suffix:semicolon
r_goto
id|end_txmngr
suffix:semicolon
)brace
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until thread starts */
id|jfsCommitThread
op_assign
id|kernel_thread
c_func
(paren
id|jfs_lazycommit
comma
l_int|0
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jfsCommitThread
OL
l_int|0
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;init_jfs_fs: fork failed w/rc = %d&bslash;n&quot;
comma
id|jfsCommitThread
)paren
)paren
suffix:semicolon
r_goto
id|kill_iotask
suffix:semicolon
)brace
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until thread starts */
id|jfsSyncThread
op_assign
id|kernel_thread
c_func
(paren
id|jfs_sync
comma
l_int|0
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jfsSyncThread
OL
l_int|0
)paren
(brace
id|jERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;init_jfs_fs: fork failed w/rc = %d&bslash;n&quot;
comma
id|jfsSyncThread
)paren
)paren
suffix:semicolon
r_goto
id|kill_committask
suffix:semicolon
)brace
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until thread starts */
macro_line|#ifdef PROC_FS_JFS
id|jfs_proc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|register_filesystem
c_func
(paren
op_amp
id|jfs_fs_type
)paren
suffix:semicolon
id|kill_committask
suffix:colon
id|jfs_stop_threads
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|jfs_commit_thread_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait for thread exit */
id|kill_iotask
suffix:colon
id|jfs_stop_threads
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|jfs_IO_thread_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait for thread exit */
id|end_txmngr
suffix:colon
id|txExit
c_func
(paren
)paren
suffix:semicolon
id|free_metapage
suffix:colon
id|metapage_exit
c_func
(paren
)paren
suffix:semicolon
id|free_slab
suffix:colon
id|kmem_cache_destroy
c_func
(paren
id|jfs_inode_cachep
)paren
suffix:semicolon
r_return
op_minus
id|rc
suffix:semicolon
)brace
DECL|function|exit_jfs_fs
r_static
r_void
id|__exit
id|exit_jfs_fs
c_func
(paren
r_void
)paren
(brace
id|jFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;exit_jfs_fs called&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|jfs_stop_threads
op_assign
l_int|1
suffix:semicolon
id|txExit
c_func
(paren
)paren
suffix:semicolon
id|metapage_exit
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|jfs_IO_thread_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until IO thread exits */
id|wake_up
c_func
(paren
op_amp
id|jfs_commit_thread_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until Commit thread exits */
id|wake_up
c_func
(paren
op_amp
id|jfs_sync_thread_wait
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|jfsIOwait
)paren
suffix:semicolon
multiline_comment|/* Wait until Sync thread exits */
macro_line|#ifdef PROC_FS_JFS
id|jfs_proc_clean
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|unregister_filesystem
c_func
(paren
op_amp
id|jfs_fs_type
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|jfs_inode_cachep
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_jfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_jfs_fs
)paren
eof
