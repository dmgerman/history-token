multiline_comment|/*&n; * Resizable simple ram filesystem for Linux.&n; *&n; * Copyright (C) 2000 Linus Torvalds.&n; *               2000 Transmeta Corp.&n; *&n; * Usage limits added by David Gibson, Linuxcare Australia.&n; * This file is released under the GPL.&n; */
multiline_comment|/*&n; * NOTE! This filesystem is probably most useful&n; * not as a real filesystem, but as an example of&n; * how virtual filesystems can be written.&n; *&n; * It doesn&squot;t get much simpler than this. Consider&n; * that this file implements the full semantics of&n; * a POSIX-compliant read-write filesystem.&n; *&n; * Note in particular how the filesystem does not&n; * need to implement any data structures of its own&n; * to keep track of the virtual data: using the VFS&n; * caches is sufficient.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
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
multiline_comment|/*&n; * Read a page. Again trivial. If it didn&squot;t already exist&n; * in the page cache, it is zero-filled.&n; */
DECL|function|ramfs_readpage
r_static
r_int
id|ramfs_readpage
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
id|Page_Uptodate
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
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ramfs_prepare_write
r_static
r_int
id|ramfs_prepare_write
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
id|Page_Uptodate
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
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ramfs_commit_write
r_static
r_int
id|ramfs_commit_write
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
id|S_IFDIR
comma
l_int|0
)paren
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
multiline_comment|/*&n; * Link a file..&n; */
DECL|function|ramfs_link
r_static
r_int
id|ramfs_link
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
id|old_dentry-&gt;d_inode
suffix:semicolon
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
suffix:semicolon
multiline_comment|/* New dentry reference */
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Extra pinning count for the created dentry */
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ramfs_positive
r_static
r_inline
r_int
id|ramfs_positive
c_func
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
multiline_comment|/*&n; * Check that a directory is empty (this works&n; * for regular files too, they&squot;ll just always be&n; * considered empty..).&n; *&n; * Note that an empty directory can still have&n; * children, they just all have to be negative..&n; */
DECL|function|ramfs_empty
r_static
r_int
id|ramfs_empty
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
id|list
op_assign
id|dentry-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|list
op_ne
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
id|ramfs_positive
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
id|list
op_assign
id|list-&gt;next
suffix:semicolon
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
multiline_comment|/*&n; * This works for both directories and regular files.&n; * (non-directories will always have empty subdirs)&n; */
DECL|function|ramfs_unlink
r_static
r_int
id|ramfs_unlink
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
id|retval
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|ramfs_empty
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
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Undo the count from &quot;create&quot; - this does all the work */
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|ramfs_rmdir
mdefine_line|#define ramfs_rmdir ramfs_unlink
multiline_comment|/*&n; * The VFS layer already does all the dentry stuff for rename,&n; * we just have to decrement the usage count for the target if&n; * it exists so that the VFS layer correctly free&squot;s it when it&n; * gets overwritten.&n; */
DECL|function|ramfs_rename
r_static
r_int
id|ramfs_rename
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
r_int
id|error
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|ramfs_empty
c_func
(paren
id|new_dentry
)paren
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|dput
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|error
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
id|block_symlink
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
DECL|function|ramfs_sync_file
r_static
r_int
id|ramfs_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ramfs_aops
r_static
r_struct
id|address_space_operations
id|ramfs_aops
op_assign
(brace
id|readpage
suffix:colon
id|ramfs_readpage
comma
id|writepage
suffix:colon
id|fail_writepage
comma
id|prepare_write
suffix:colon
id|ramfs_prepare_write
comma
id|commit_write
suffix:colon
id|ramfs_commit_write
)brace
suffix:semicolon
DECL|variable|ramfs_file_operations
r_static
r_struct
id|file_operations
id|ramfs_file_operations
op_assign
(brace
id|read
suffix:colon
id|generic_file_read
comma
id|write
suffix:colon
id|generic_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|fsync
suffix:colon
id|ramfs_sync_file
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
id|create
suffix:colon
id|ramfs_create
comma
id|lookup
suffix:colon
id|simple_lookup
comma
id|link
suffix:colon
id|ramfs_link
comma
id|unlink
suffix:colon
id|ramfs_unlink
comma
id|symlink
suffix:colon
id|ramfs_symlink
comma
id|mkdir
suffix:colon
id|ramfs_mkdir
comma
id|rmdir
suffix:colon
id|ramfs_rmdir
comma
id|mknod
suffix:colon
id|ramfs_mknod
comma
id|rename
suffix:colon
id|ramfs_rename
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
id|statfs
suffix:colon
id|simple_statfs
comma
id|put_inode
suffix:colon
id|force_delete
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
DECL|variable|ramfs_fs_type
r_static
r_struct
id|file_system_type
id|ramfs_fs_type
op_assign
(brace
id|name
suffix:colon
l_string|&quot;ramfs&quot;
comma
id|get_sb
suffix:colon
id|ramfs_get_sb
comma
id|kill_sb
suffix:colon
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
id|name
suffix:colon
l_string|&quot;rootfs&quot;
comma
id|get_sb
suffix:colon
id|ramfs_get_sb
comma
id|kill_sb
suffix:colon
id|kill_litter_super
comma
id|fs_flags
suffix:colon
id|FS_NOMOUNT
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
