multiline_comment|/*&n; * linux/fs/ufs/namei.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/namei.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/namei.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|macro|UFS_NAMEI_DEBUG
macro_line|#undef UFS_NAMEI_DEBUG
macro_line|#ifdef UFS_NAMEI_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s: &quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
DECL|function|ufs_inc_count
r_static
r_inline
r_void
id|ufs_inc_count
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_nlink
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|ufs_dec_count
r_static
r_inline
r_void
id|ufs_dec_count
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
)brace
DECL|function|ufs_add_nondir
r_static
r_inline
r_int
id|ufs_add_nondir
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
r_int
id|err
op_assign
id|ufs_add_link
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
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
r_return
l_int|0
suffix:semicolon
)brace
id|ufs_dec_count
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
r_return
id|err
suffix:semicolon
)brace
DECL|function|ufs_lookup
r_static
r_struct
id|dentry
op_star
id|ufs_lookup
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
l_int|NULL
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|UFS_MAXNAMLEN
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
id|ino
op_assign
id|ufs_inode_by_name
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
)paren
(brace
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
multiline_comment|/*&n; * By the time this is called, we already have created&n; * the directory cache entry for the new file, but it&n; * is so far negative - it has no inode.&n; *&n; * If the create succeeds, we fill in the inode information&n; * with d_instantiate(). &n; */
DECL|function|ufs_create
r_static
r_int
id|ufs_create
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
r_struct
id|inode
op_star
id|inode
op_assign
id|ufs_new_inode
c_func
(paren
id|dir
comma
id|mode
)paren
suffix:semicolon
r_int
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|ufs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ufs_aops
suffix:semicolon
id|mark_inode_dirty
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
id|err
op_assign
id|ufs_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|ufs_mknod
r_static
r_int
id|ufs_mknod
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
id|rdev
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|ufs_new_inode
c_func
(paren
id|dir
comma
id|mode
)paren
suffix:semicolon
r_int
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|inode
)paren
)paren
(brace
id|init_special_inode
c_func
(paren
id|inode
comma
id|mode
comma
id|rdev
)paren
suffix:semicolon
id|mark_inode_dirty
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
id|err
op_assign
id|ufs_add_nondir
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|ufs_symlink
r_static
r_int
id|ufs_symlink
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
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
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
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|sb-&gt;s_blocksize
)paren
r_goto
id|out
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode
op_assign
id|ufs_new_inode
c_func
(paren
id|dir
comma
id|S_IFLNK
op_or
id|S_IRWXUGO
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
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
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|sb-&gt;u.ufs_sb.s_uspi-&gt;s_maxsymlinklen
)paren
(brace
multiline_comment|/* slow symlink */
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ufs_aops
suffix:semicolon
id|err
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
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* fast symlink */
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_fast_symlink_inode_operations
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|UFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_u1.i_data
comma
id|symname
comma
id|l
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|l
op_minus
l_int|1
suffix:semicolon
)brace
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ufs_add_nondir
c_func
(paren
id|dentry
comma
id|inode
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
id|err
suffix:semicolon
id|out_fail
suffix:colon
id|ufs_dec_count
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
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ufs_link
r_static
r_int
id|ufs_link
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
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_ge
id|UFS_LINK_MAX
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EMLINK
suffix:semicolon
)brace
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|ufs_inc_count
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
id|error
op_assign
id|ufs_add_nondir
c_func
(paren
id|dentry
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
id|error
suffix:semicolon
)brace
DECL|function|ufs_mkdir
r_static
r_int
id|ufs_mkdir
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
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EMLINK
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_nlink
op_ge
id|UFS_LINK_MAX
)paren
r_goto
id|out
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ufs_inc_count
c_func
(paren
id|dir
)paren
suffix:semicolon
id|inode
op_assign
id|ufs_new_inode
c_func
(paren
id|dir
comma
id|S_IFDIR
op_or
id|mode
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|inode
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
r_goto
id|out_dir
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|ufs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|ufs_dir_operations
suffix:semicolon
id|ufs_inc_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ufs_make_empty
c_func
(paren
id|inode
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
id|err
op_assign
id|ufs_add_link
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_fail
suffix:semicolon
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
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_fail
suffix:colon
id|ufs_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
(paren
id|inode
)paren
suffix:semicolon
id|out_dir
suffix:colon
id|ufs_dec_count
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
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ufs_unlink
r_static
r_int
id|ufs_unlink
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
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|de
op_assign
id|ufs_find_entry
(paren
id|dentry
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|ufs_delete_entry
(paren
id|dir
comma
id|de
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|dir-&gt;i_ctime
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|err
op_assign
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
id|err
suffix:semicolon
)brace
DECL|function|ufs_rmdir
r_static
r_int
id|ufs_rmdir
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
r_int
id|err
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ufs_empty_dir
(paren
id|inode
)paren
)paren
(brace
id|err
op_assign
id|ufs_unlink
c_func
(paren
id|dir
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|dir
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
id|err
suffix:semicolon
)brace
DECL|function|ufs_rename
r_static
r_int
id|ufs_rename
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
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|inode
op_star
id|new_inode
op_assign
id|new_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dir_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|dir_de
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|old_bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|old_de
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|old_de
op_assign
id|ufs_find_entry
(paren
id|old_dentry
comma
op_amp
id|old_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_de
)paren
r_goto
id|out
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
(brace
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|dir_de
op_assign
id|ufs_dotdot
c_func
(paren
id|old_inode
comma
op_amp
id|dir_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_de
)paren
r_goto
id|out_old
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_inode
)paren
(brace
r_struct
id|buffer_head
op_star
id|new_bh
suffix:semicolon
r_struct
id|ufs_dir_entry
op_star
id|new_de
suffix:semicolon
id|err
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
op_logical_and
op_logical_neg
id|ufs_empty_dir
(paren
id|new_inode
)paren
)paren
r_goto
id|out_dir
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|new_de
op_assign
id|ufs_find_entry
(paren
id|new_dentry
comma
op_amp
id|new_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_de
)paren
r_goto
id|out_dir
suffix:semicolon
id|ufs_inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|ufs_set_link
c_func
(paren
id|new_dir
comma
id|new_de
comma
id|new_bh
comma
id|old_inode
)paren
suffix:semicolon
id|new_inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
)paren
id|new_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|new_inode
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dir_de
)paren
(brace
id|err
op_assign
op_minus
id|EMLINK
suffix:semicolon
r_if
c_cond
(paren
id|new_dir-&gt;i_nlink
op_ge
id|UFS_LINK_MAX
)paren
r_goto
id|out_dir
suffix:semicolon
)brace
id|ufs_inc_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
id|err
op_assign
id|ufs_add_link
c_func
(paren
id|new_dentry
comma
id|old_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|ufs_dec_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
r_goto
id|out_dir
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir_de
)paren
id|ufs_inc_count
c_func
(paren
id|new_dir
)paren
suffix:semicolon
)brace
id|ufs_delete_entry
(paren
id|old_dir
comma
id|old_de
comma
id|old_bh
)paren
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|old_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir_de
)paren
(brace
id|ufs_set_link
c_func
(paren
id|old_inode
comma
id|dir_de
comma
id|dir_bh
comma
id|new_dir
)paren
suffix:semicolon
id|ufs_dec_count
c_func
(paren
id|old_dir
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_dir
suffix:colon
r_if
c_cond
(paren
id|dir_de
)paren
id|brelse
c_func
(paren
id|dir_bh
)paren
suffix:semicolon
id|out_old
suffix:colon
id|brelse
(paren
id|old_bh
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
id|err
suffix:semicolon
)brace
DECL|variable|ufs_dir_inode_operations
r_struct
id|inode_operations
id|ufs_dir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|ufs_create
comma
id|lookup
suffix:colon
id|ufs_lookup
comma
id|link
suffix:colon
id|ufs_link
comma
id|unlink
suffix:colon
id|ufs_unlink
comma
id|symlink
suffix:colon
id|ufs_symlink
comma
id|mkdir
suffix:colon
id|ufs_mkdir
comma
id|rmdir
suffix:colon
id|ufs_rmdir
comma
id|mknod
suffix:colon
id|ufs_mknod
comma
id|rename
suffix:colon
id|ufs_rename
comma
)brace
suffix:semicolon
eof
