multiline_comment|/*&n; *&t;fs/bfs/dir.c&n; *&t;BFS directory operations.&n; *&t;Copyright (C) 1999,2000  Tigran Aivazian &lt;tigran@veritas.com&gt;&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;bfs.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)&t;printf(x)
macro_line|#else
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)
macro_line|#endif
r_static
r_int
id|bfs_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_int
id|ino
)paren
suffix:semicolon
r_static
r_struct
id|buffer_head
op_star
id|bfs_find_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|bfs_dirent
op_star
op_star
id|res_dir
)paren
suffix:semicolon
DECL|function|bfs_readdir
r_static
r_int
id|bfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|f
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
id|inode
op_star
id|dir
op_assign
id|f-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|de
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|block
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;f_pos
op_amp
(paren
id|BFS_DIRENT_SIZE
op_minus
l_int|1
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Bad f_pos=%08lx for %s:%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|f-&gt;f_pos
comma
id|dir-&gt;i_sb-&gt;s_id
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_while
c_loop
(paren
id|f-&gt;f_pos
OL
id|dir-&gt;i_size
)paren
(brace
id|offset
op_assign
id|f-&gt;f_pos
op_amp
(paren
id|BFS_BSIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|block
op_assign
id|BFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_sblock
op_plus
(paren
id|f-&gt;f_pos
op_rshift
id|BFS_BSIZE_BITS
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|dir-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|f-&gt;f_pos
op_add_assign
id|BFS_BSIZE
op_minus
id|offset
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_do
(brace
id|de
op_assign
(paren
r_struct
id|bfs_dirent
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;ino
)paren
(brace
r_int
id|size
op_assign
id|strnlen
c_func
(paren
id|de-&gt;name
comma
id|BFS_NAMELEN
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
id|de-&gt;name
comma
id|size
comma
id|f-&gt;f_pos
comma
id|de-&gt;ino
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
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
)brace
id|offset
op_add_assign
id|BFS_DIRENT_SIZE
suffix:semicolon
id|f-&gt;f_pos
op_add_assign
id|BFS_DIRENT_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|BFS_BSIZE
op_logical_and
id|f-&gt;f_pos
OL
id|dir-&gt;i_size
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|update_atime
c_func
(paren
id|dir
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
DECL|variable|bfs_dir_operations
r_struct
id|file_operations
id|bfs_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|bfs_readdir
comma
dot
id|fsync
op_assign
id|file_fsync
comma
)brace
suffix:semicolon
r_extern
r_void
id|dump_imap
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|function|bfs_create
r_static
r_int
id|bfs_create
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
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|super_block
op_star
id|s
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|bfs_sb_info
op_star
id|info
op_assign
id|BFS_SB
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|s
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
id|ENOSPC
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ino
op_assign
id|find_first_zero_bit
c_func
(paren
id|info-&gt;si_imap
comma
id|info-&gt;si_lasti
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
OG
id|info-&gt;si_lasti
)paren
(brace
id|unlock_kernel
c_func
(paren
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
id|ENOSPC
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|ino
comma
id|info-&gt;si_imap
)paren
suffix:semicolon
id|info-&gt;si_freei
op_decrement
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
ques
c_cond
id|dir-&gt;i_gid
suffix:colon
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|bfs_file_inops
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|bfs_aops
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|ino
suffix:semicolon
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_dsk_ino
op_assign
id|ino
suffix:semicolon
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_sblock
op_assign
l_int|0
suffix:semicolon
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
op_assign
l_int|0
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|dump_imap
c_func
(paren
l_string|&quot;create&quot;
comma
id|s
)paren
suffix:semicolon
id|err
op_assign
id|bfs_add_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
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
DECL|function|bfs_lookup
r_static
r_struct
id|dentry
op_star
id|bfs_lookup
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
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|BFS_NAMELEN
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|bh
op_assign
id|bfs_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
r_int
r_int
id|ino
op_assign
id|le32_to_cpu
c_func
(paren
id|de-&gt;ino
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
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
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bfs_link
r_static
r_int
id|bfs_link
c_func
(paren
r_struct
id|dentry
op_star
id|old
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
r_new
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|old-&gt;d_inode
suffix:semicolon
r_int
id|err
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|bfs_add_entry
c_func
(paren
id|dir
comma
r_new
op_member_access_from_pointer
id|d_name.name
comma
r_new
op_member_access_from_pointer
id|d_name.len
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
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
r_new
comma
id|inode
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
DECL|function|bfs_unlink
r_static
r_int
id|bfs_unlink
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
id|ENOENT
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|de
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|bh
op_assign
id|bfs_find_entry
c_func
(paren
id|dir
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|de-&gt;ino
op_ne
id|inode-&gt;i_ino
)paren
r_goto
id|out_brelse
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;unlinking non-existent file %s:%lu (nlink=%d)&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
id|de-&gt;ino
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|out_brelse
suffix:colon
id|brelse
c_func
(paren
id|bh
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
DECL|function|bfs_rename
r_static
r_int
id|bfs_rename
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
r_struct
id|inode
op_star
id|old_inode
comma
op_star
id|new_inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|old_bh
comma
op_star
id|new_bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|old_de
comma
op_star
id|new_de
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|old_bh
op_assign
id|new_bh
op_assign
l_int|NULL
suffix:semicolon
id|old_inode
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|old_inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|old_bh
op_assign
id|bfs_find_entry
c_func
(paren
id|old_dir
comma
id|old_dentry-&gt;d_name.name
comma
id|old_dentry-&gt;d_name.len
comma
op_amp
id|old_de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_bh
op_logical_or
id|old_de-&gt;ino
op_ne
id|old_inode-&gt;i_ino
)paren
r_goto
id|end_rename
suffix:semicolon
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
id|new_bh
op_assign
id|bfs_find_entry
c_func
(paren
id|new_dir
comma
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
comma
op_amp
id|new_de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_bh
op_logical_and
op_logical_neg
id|new_inode
)paren
(brace
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
id|new_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_bh
)paren
(brace
id|error
op_assign
id|bfs_add_entry
c_func
(paren
id|new_dir
comma
id|new_dentry-&gt;d_name.name
comma
id|new_dentry-&gt;d_name.len
comma
id|old_inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|end_rename
suffix:semicolon
)brace
id|old_de-&gt;ino
op_assign
l_int|0
suffix:semicolon
id|old_dir-&gt;i_ctime
op_assign
id|old_dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|old_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
(brace
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|end_rename
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|old_bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|new_bh
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|bfs_dir_inops
r_struct
id|inode_operations
id|bfs_dir_inops
op_assign
(brace
dot
id|create
op_assign
id|bfs_create
comma
dot
id|lookup
op_assign
id|bfs_lookup
comma
dot
id|link
op_assign
id|bfs_link
comma
dot
id|unlink
op_assign
id|bfs_unlink
comma
dot
id|rename
op_assign
id|bfs_rename
comma
)brace
suffix:semicolon
DECL|function|bfs_add_entry
r_static
r_int
id|bfs_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_int
id|ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|de
suffix:semicolon
r_int
id|block
comma
id|sblock
comma
id|eblock
comma
id|off
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintf
c_func
(paren
l_string|&quot;name=%s, namelen=%d&bslash;n&quot;
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
id|BFS_NAMELEN
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
id|sblock
op_assign
id|BFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_sblock
suffix:semicolon
id|eblock
op_assign
id|BFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_eblock
suffix:semicolon
r_for
c_loop
(paren
id|block
op_assign
id|sblock
suffix:semicolon
id|block
op_le
id|eblock
suffix:semicolon
id|block
op_increment
)paren
(brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|dir-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_for
c_loop
(paren
id|off
op_assign
l_int|0
suffix:semicolon
id|off
OL
id|BFS_BSIZE
suffix:semicolon
id|off
op_add_assign
id|BFS_DIRENT_SIZE
)paren
(brace
id|de
op_assign
(paren
r_struct
id|bfs_dirent
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;ino
)paren
(brace
r_if
c_cond
(paren
(paren
id|block
op_minus
id|sblock
)paren
op_star
id|BFS_BSIZE
op_plus
id|off
op_ge
id|dir-&gt;i_size
)paren
(brace
id|dir-&gt;i_size
op_add_assign
id|BFS_DIRENT_SIZE
suffix:semicolon
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|de-&gt;ino
op_assign
id|ino
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
id|BFS_NAMELEN
suffix:semicolon
id|i
op_increment
)paren
id|de-&gt;name
(braket
id|i
)braket
op_assign
(paren
id|i
OL
id|namelen
)paren
ques
c_cond
id|name
(braket
id|i
)braket
suffix:colon
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|bfs_namecmp
r_static
r_inline
r_int
id|bfs_namecmp
c_func
(paren
r_int
id|len
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|len
OL
id|BFS_NAMELEN
op_logical_and
id|buffer
(braket
id|len
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|bfs_find_entry
r_static
r_struct
id|buffer_head
op_star
id|bfs_find_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|bfs_dirent
op_star
op_star
id|res_dir
)paren
(brace
r_int
r_int
id|block
comma
id|offset
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_dirent
op_star
id|de
suffix:semicolon
op_star
id|res_dir
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
id|BFS_NAMELEN
)paren
r_return
l_int|NULL
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|block
op_assign
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|block
op_star
id|BFS_BSIZE
op_plus
id|offset
OL
id|dir-&gt;i_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|sb_bread
c_func
(paren
id|dir-&gt;i_sb
comma
id|BFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_sblock
op_plus
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|block
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|de
op_assign
(paren
r_struct
id|bfs_dirent
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
id|offset
op_add_assign
id|BFS_DIRENT_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;ino
op_logical_and
id|bfs_namecmp
c_func
(paren
id|namelen
comma
id|name
comma
id|de-&gt;name
)paren
)paren
(brace
op_star
id|res_dir
op_assign
id|de
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
id|bh-&gt;b_size
)paren
r_continue
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
eof
