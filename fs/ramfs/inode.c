multiline_comment|/*&n; * Resizable simple ram filesystem for Linux.&n; *&n; * Copyright (C) 2000 Linus Torvalds.&n; *               2000 Transmeta Corp.&n; *&n; * Usage limits added by David Gibson, Linuxcare Australia.&n; * This file is released under the GPL.&n; */
multiline_comment|/*&n; * NOTE! This filesystem is probably most useful&n; * not as a real filesystem, but as an example of&n; * how virtual filesystems can be written.&n; *&n; * It doesn&squot;t get much simpler than this. Consider&n; * that this file implements the full semantics of&n; * a POSIX-compliant read-write filesystem.&n; *&n; * Note in particular how the filesystem does not&n; * need to implement any data structures of its own&n; * to keep track of the virtual data: using the VFS&n; * caches is sufficient.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* some random number */
DECL|macro|RAMFS_MAGIC
mdefine_line|#define RAMFS_MAGIC&t;0x858458f6
DECL|variable|ramfs_ops
r_static
r_struct
id|super_operations
id|ramfs_ops
suffix:semicolon
DECL|variable|ramfs_aops
r_static
r_struct
id|address_space_operations
id|ramfs_aops
suffix:semicolon
DECL|variable|ramfs_file_operations
r_static
r_struct
id|file_operations
id|ramfs_file_operations
suffix:semicolon
DECL|variable|ramfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|ramfs_dir_inode_operations
suffix:semicolon
DECL|variable|ramfs_backing_dev_info
r_static
r_struct
id|backing_dev_info
id|ramfs_backing_dev_info
op_assign
(brace
dot
id|ra_pages
op_assign
l_int|0
comma
multiline_comment|/* No readahead */
dot
id|memory_backed
op_assign
l_int|1
comma
multiline_comment|/* Does not contribute to dirty memory */
)brace
suffix:semicolon
DECL|function|ramfs_get_inode
r_struct
id|inode
op_star
id|ramfs_get_inode
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
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ramfs_aops
suffix:semicolon
id|inode-&gt;i_mapping-&gt;backing_dev_info
op_assign
op_amp
id|ramfs_backing_dev_info
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
id|ramfs_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|ramfs_dir_inode_operations
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
multiline_comment|/*&n; * File creation. Allocate an inode, and we&squot;re done..&n; */
multiline_comment|/* SMP-safe */
DECL|function|ramfs_mknod
r_static
r_int
id|ramfs_mknod
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
id|ramfs_get_inode
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
multiline_comment|/* Extra count - pin the dentry in core */
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|ramfs_mkdir
r_static
r_int
id|ramfs_mkdir
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
id|retval
op_assign
id|ramfs_mknod
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
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ramfs_create
r_static
r_int
id|ramfs_create
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
r_return
id|ramfs_mknod
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
)brace
DECL|function|ramfs_symlink
r_static
r_int
id|ramfs_symlink
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
id|inode
op_assign
id|ramfs_get_inode
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
DECL|variable|ramfs_aops
r_static
r_struct
id|address_space_operations
id|ramfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|simple_readpage
comma
dot
id|writepage
op_assign
id|fail_writepage
comma
dot
id|prepare_write
op_assign
id|simple_prepare_write
comma
dot
id|commit_write
op_assign
id|simple_commit_write
)brace
suffix:semicolon
DECL|variable|ramfs_file_operations
r_static
r_struct
id|file_operations
id|ramfs_file_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|write
op_assign
id|generic_file_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|fsync
op_assign
id|simple_sync_file
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|ramfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|ramfs_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|ramfs_create
comma
dot
id|lookup
op_assign
id|simple_lookup
comma
dot
id|link
op_assign
id|simple_link
comma
dot
id|unlink
op_assign
id|simple_unlink
comma
dot
id|symlink
op_assign
id|ramfs_symlink
comma
dot
id|mkdir
op_assign
id|ramfs_mkdir
comma
dot
id|rmdir
op_assign
id|simple_rmdir
comma
dot
id|mknod
op_assign
id|ramfs_mknod
comma
dot
id|rename
op_assign
id|simple_rename
comma
)brace
suffix:semicolon
DECL|variable|ramfs_ops
r_static
r_struct
id|super_operations
id|ramfs_ops
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
DECL|function|ramfs_fill_super
r_static
r_int
id|ramfs_fill_super
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
id|RAMFS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|ramfs_ops
suffix:semicolon
id|inode
op_assign
id|ramfs_get_inode
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
DECL|function|ramfs_get_sb
r_static
r_struct
id|super_block
op_star
id|ramfs_get_sb
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
id|get_sb_nodev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|ramfs_fill_super
)paren
suffix:semicolon
)brace
DECL|function|rootfs_get_sb
r_static
r_struct
id|super_block
op_star
id|rootfs_get_sb
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
id|get_sb_nodev
c_func
(paren
id|fs_type
comma
id|flags
op_or
id|MS_NOUSER
comma
id|data
comma
id|ramfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|ramfs_fs_type
r_static
r_struct
id|file_system_type
id|ramfs_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ramfs&quot;
comma
dot
id|get_sb
op_assign
id|ramfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|variable|rootfs_fs_type
r_static
r_struct
id|file_system_type
id|rootfs_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;rootfs&quot;
comma
dot
id|get_sb
op_assign
id|rootfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|init_ramfs_fs
r_static
r_int
id|__init
id|init_ramfs_fs
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
id|ramfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_ramfs_fs
r_static
r_void
id|__exit
id|exit_ramfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|ramfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|module_init
id|module_init
c_func
(paren
id|init_ramfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_ramfs_fs
)paren
r_int
id|__init
id|init_rootfs
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
id|rootfs_fs_type
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
