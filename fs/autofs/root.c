multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/root.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
r_static
r_int
id|autofs_root_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|autofs_root_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|autofs_root_symlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|autofs_root_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|autofs_root_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|autofs_root_mkdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|autofs_root_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|autofs_root_operations
r_struct
id|file_operations
id|autofs_root_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|autofs_root_readdir
comma
id|ioctl
suffix:colon
id|autofs_root_ioctl
comma
)brace
suffix:semicolon
DECL|variable|autofs_root_inode_operations
r_struct
id|inode_operations
id|autofs_root_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|autofs_root_lookup
comma
id|unlink
suffix:colon
id|autofs_root_unlink
comma
id|symlink
suffix:colon
id|autofs_root_symlink
comma
id|mkdir
suffix:colon
id|autofs_root_mkdir
comma
id|rmdir
suffix:colon
id|autofs_root_rmdir
comma
)brace
suffix:semicolon
DECL|function|autofs_root_readdir
r_static
r_int
id|autofs_root_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
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
id|autofs_dir_ent
op_star
id|ent
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|autofs_dirhash
op_star
id|dirhash
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|off_t
id|onr
comma
id|nr
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|dirhash
op_assign
op_amp
id|sbi-&gt;dirhash
suffix:semicolon
id|nr
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|nr
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|nr
comma
id|inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp-&gt;f_pos
op_assign
op_increment
id|nr
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|nr
comma
id|inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp-&gt;f_pos
op_assign
op_increment
id|nr
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_while
c_loop
(paren
id|onr
op_assign
id|nr
comma
id|ent
op_assign
id|autofs_hash_enum
c_func
(paren
id|dirhash
comma
op_amp
id|nr
comma
id|ent
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ent-&gt;dentry
op_logical_or
id|d_mountpoint
c_func
(paren
id|ent-&gt;dentry
)paren
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|ent-&gt;name
comma
id|ent-&gt;len
comma
id|onr
comma
id|ent-&gt;ino
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|nr
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|try_to_fill_dentry
r_static
r_int
id|try_to_fill_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ent
op_assign
id|autofs_hash_lookup
c_func
(paren
op_amp
id|sbi-&gt;dirhash
comma
op_amp
id|dentry-&gt;d_name
)paren
)paren
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
id|status
op_logical_and
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|status
op_ne
op_minus
id|ENOENT
)paren
id|printk
c_func
(paren
l_string|&quot;autofs warning: lookup failure on positive dentry, status = %d, name = %s&bslash;n&quot;
comma
id|status
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Try to get the kernel to invalidate this dentry */
)brace
multiline_comment|/* Turn this into a real negative dentry? */
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|ENOENT
)paren
(brace
id|dentry-&gt;d_time
op_assign
id|jiffies
op_plus
id|AUTOFS_NEGATIVE_TIMEOUT
suffix:semicolon
id|dentry-&gt;d_flags
op_and_assign
op_complement
id|DCACHE_AUTOFS_PENDING
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* Return a negative dentry, but leave it &quot;pending&quot; */
r_return
l_int|1
suffix:semicolon
)brace
id|status
op_assign
id|autofs_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|ent
op_assign
id|autofs_hash_lookup
c_func
(paren
op_amp
id|sbi-&gt;dirhash
comma
op_amp
id|dentry-&gt;d_name
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Abuse this field as a pointer to the directory entry, used to&n;&t;   find the expire list pointers */
id|dentry-&gt;d_time
op_assign
(paren
r_int
r_int
)paren
id|ent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
(brace
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|ent-&gt;ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
multiline_comment|/* Failed, but leave pending for next time */
r_return
l_int|1
suffix:semicolon
)brace
id|dentry-&gt;d_inode
op_assign
id|inode
suffix:semicolon
)brace
multiline_comment|/* If this is a directory that isn&squot;t a mount point, bitch at the&n;&t;   daemon and fix it in user space */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
r_return
op_logical_neg
id|autofs_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
)paren
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t update the usages for the autofs daemon itself, this&n;&t;   is necessary for recursive autofs mounts */
r_if
c_cond
(paren
op_logical_neg
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
)paren
(brace
id|autofs_update_usage
c_func
(paren
op_amp
id|sbi-&gt;dirhash
comma
id|ent
)paren
suffix:semicolon
)brace
id|dentry-&gt;d_flags
op_and_assign
op_complement
id|DCACHE_AUTOFS_PENDING
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Revalidate is called on every cache lookup.  Some of those&n; * cache lookups may actually happen while the dentry is not&n; * yet completely filled in, and revalidate has to delay such&n; * lookups..&n; */
DECL|function|autofs_revalidate
r_static
r_int
id|autofs_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flags
)paren
(brace
r_struct
id|inode
op_star
id|dir
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
r_int
id|res
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
multiline_comment|/* Pending dentry */
r_if
c_cond
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
)paren
(brace
r_if
c_cond
(paren
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
)paren
id|res
op_assign
l_int|1
suffix:semicolon
r_else
id|res
op_assign
id|try_to_fill_dentry
c_func
(paren
id|dentry
comma
id|dir-&gt;i_sb
comma
id|sbi
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
multiline_comment|/* Negative dentry.. invalidate if &quot;old&quot; */
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|dentry-&gt;d_time
op_minus
id|jiffies
op_le
id|AUTOFS_NEGATIVE_TIMEOUT
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for a non-mountpoint directory */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
id|d_mountpoint
c_func
(paren
id|dentry
)paren
)paren
(brace
r_if
c_cond
(paren
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
)paren
id|res
op_assign
l_int|1
suffix:semicolon
r_else
id|res
op_assign
id|try_to_fill_dentry
c_func
(paren
id|dentry
comma
id|dir-&gt;i_sb
comma
id|sbi
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
multiline_comment|/* Update the usage list */
r_if
c_cond
(paren
op_logical_neg
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
)paren
(brace
id|ent
op_assign
(paren
r_struct
id|autofs_dir_ent
op_star
)paren
id|dentry-&gt;d_time
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
id|autofs_update_usage
c_func
(paren
op_amp
id|sbi-&gt;dirhash
comma
id|ent
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|autofs_dentry_operations
r_static
r_struct
id|dentry_operations
id|autofs_dentry_operations
op_assign
(brace
id|d_revalidate
suffix:colon
id|autofs_revalidate
comma
)brace
suffix:semicolon
DECL|function|autofs_root_lookup
r_static
r_struct
id|dentry
op_star
id|autofs_root_lookup
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
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
r_int
id|oz_mode
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_root_lookup: name = &quot;
)paren
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|autofs_say
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|NAME_MAX
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
id|ENAMETOOLONG
)paren
suffix:semicolon
multiline_comment|/* File name too long to exist */
)brace
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|oz_mode
op_assign
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_lookup: pid = %u, pgrp = %u, catatonic = %d, oz_mode = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;pgrp
comma
id|sbi-&gt;catatonic
comma
id|oz_mode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mark the dentry incomplete, but add it. This is needed so&n;&t; * that the VFS layer knows about the dentry, and we can count&n;&t; * on catching any lookups through the revalidate.&n;&t; *&n;&t; * Let all the hard work be done by the revalidate function that&n;&t; * needs to be able to do this anyway..&n;&t; *&n;&t; * We need to do this before we release the directory semaphore.&n;&t; */
id|dentry-&gt;d_op
op_assign
op_amp
id|autofs_dentry_operations
suffix:semicolon
id|dentry-&gt;d_flags
op_or_assign
id|DCACHE_AUTOFS_PENDING
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
id|autofs_revalidate
c_func
(paren
id|dentry
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we are still pending, check if we had to handle&n;&t; * a signal. If so we can force a restart..&n;&t; */
r_if
c_cond
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
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
id|ERESTARTNOINTR
)paren
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If this dentry is unhashed, then we shouldn&squot;t honour this&n;&t; * lookup even if the dentry is positive.  Returning ENOENT here&n;&t; * doesn&squot;t do the right thing for all system calls, but it should&n;&t; * be OK for the operations we permit from an autofs.&n;&t; */
r_if
c_cond
(paren
id|dentry-&gt;d_inode
op_logical_and
id|d_unhashed
c_func
(paren
id|dentry
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|autofs_root_symlink
r_static
r_int
id|autofs_root_symlink
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
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_dirhash
op_star
id|dh
op_assign
op_amp
id|sbi-&gt;dirhash
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_int
id|slsize
suffix:semicolon
r_struct
id|autofs_symlink
op_star
id|sl
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_root_symlink: %s &lt;- &quot;
comma
id|symname
)paren
)paren
suffix:semicolon
id|autofs_say
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
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
id|autofs_oz_mode
c_func
(paren
id|sbi
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
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|autofs_hash_lookup
c_func
(paren
id|dh
comma
op_amp
id|dentry-&gt;d_name
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
id|EEXIST
suffix:semicolon
)brace
id|n
op_assign
id|find_first_zero_bit
c_func
(paren
id|sbi-&gt;symlink_bitmap
comma
id|AUTOFS_MAX_SYMLINKS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|AUTOFS_MAX_SYMLINKS
)paren
(brace
id|unlock_kernel
c_func
(paren
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
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
suffix:semicolon
id|sl
op_assign
op_amp
id|sbi-&gt;symlink
(braket
id|n
)braket
suffix:semicolon
id|sl-&gt;len
op_assign
id|strlen
c_func
(paren
id|symname
)paren
suffix:semicolon
id|sl-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|slsize
op_assign
id|sl-&gt;len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sl-&gt;data
)paren
(brace
id|clear_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|ent
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|autofs_dir_ent
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
(brace
id|kfree
c_func
(paren
id|sl-&gt;data
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|ent-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|dentry-&gt;d_name.len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|sl-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ent
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|sl-&gt;data
comma
id|symname
comma
id|slsize
)paren
suffix:semicolon
id|sl-&gt;mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|ent-&gt;ino
op_assign
id|AUTOFS_FIRST_SYMLINK
op_plus
id|n
suffix:semicolon
id|ent-&gt;hash
op_assign
id|dentry-&gt;d_name.hash
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|dentry-&gt;d_name.name
comma
l_int|1
op_plus
(paren
id|ent-&gt;len
op_assign
id|dentry-&gt;d_name.len
)paren
)paren
suffix:semicolon
id|ent-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We don&squot;t keep the dentry for symlinks */
id|autofs_hash_insert
c_func
(paren
id|dh
comma
id|ent
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ent-&gt;ino
)paren
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
multiline_comment|/*&n; * NOTE!&n; *&n; * Normal filesystems would do a &quot;d_delete()&quot; to tell the VFS dcache&n; * that the file no longer exists. However, doing that means that the&n; * VFS layer can turn the dentry into a negative dentry, which we&n; * obviously do not want (we&squot;re dropping the entry not because it&n; * doesn&squot;t exist, but because it has timed out).&n; *&n; * Also see autofs_root_rmdir()..&n; */
DECL|function|autofs_root_unlink
r_static
r_int
id|autofs_root_unlink
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
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_dirhash
op_star
id|dh
op_assign
op_amp
id|sbi-&gt;dirhash
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
multiline_comment|/* This allows root to remove symlinks */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
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
id|EACCES
suffix:semicolon
)brace
id|ent
op_assign
id|autofs_hash_lookup
c_func
(paren
id|dh
comma
op_amp
id|dentry-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|n
op_assign
id|ent-&gt;ino
op_minus
id|AUTOFS_FIRST_SYMLINK
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|AUTOFS_MAX_SYMLINKS
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EISDIR
suffix:semicolon
multiline_comment|/* It&squot;s a directory, dummy */
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
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
id|EINVAL
suffix:semicolon
multiline_comment|/* Nonexistent symlink?  Shouldn&squot;t happen */
)brace
id|dentry-&gt;d_time
op_assign
(paren
r_int
r_int
)paren
(paren
r_struct
id|autofs_dirhash
op_star
)paren
l_int|NULL
suffix:semicolon
id|autofs_hash_delete
c_func
(paren
id|ent
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|n
comma
id|sbi-&gt;symlink_bitmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi-&gt;symlink
(braket
id|n
)braket
dot
id|data
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|dentry
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
DECL|function|autofs_root_rmdir
r_static
r_int
id|autofs_root_rmdir
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
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_dirhash
op_star
id|dh
op_assign
op_amp
id|sbi-&gt;dirhash
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
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
id|autofs_oz_mode
c_func
(paren
id|sbi
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
id|EACCES
suffix:semicolon
)brace
id|ent
op_assign
id|autofs_hash_lookup
c_func
(paren
id|dh
comma
op_amp
id|dentry-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
(brace
id|unlock_kernel
c_func
(paren
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
(paren
r_int
r_int
)paren
id|ent-&gt;ino
OL
id|AUTOFS_FIRST_DIR_INO
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOTDIR
suffix:semicolon
multiline_comment|/* Not a directory */
)brace
r_if
c_cond
(paren
id|ent-&gt;dentry
op_ne
id|dentry
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs_rmdir: odentry != dentry for entry %s&bslash;n&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
id|dentry-&gt;d_time
op_assign
(paren
r_int
r_int
)paren
(paren
r_struct
id|autofs_dir_ent
op_star
)paren
l_int|NULL
suffix:semicolon
id|autofs_hash_delete
c_func
(paren
id|ent
)paren
suffix:semicolon
id|dir-&gt;i_nlink
op_decrement
suffix:semicolon
id|d_drop
c_func
(paren
id|dentry
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
DECL|function|autofs_root_mkdir
r_static
r_int
id|autofs_root_mkdir
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
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_dirhash
op_star
id|dh
op_assign
op_amp
id|sbi-&gt;dirhash
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
id|ino_t
id|ino
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
id|autofs_oz_mode
c_func
(paren
id|sbi
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
id|EACCES
suffix:semicolon
)brace
id|ent
op_assign
id|autofs_hash_lookup
c_func
(paren
id|dh
comma
op_amp
id|dentry-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sbi-&gt;next_dir_ino
OL
id|AUTOFS_FIRST_DIR_INO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;autofs: Out of inode numbers -- what the heck did you do??&bslash;n&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|ino
op_assign
id|sbi-&gt;next_dir_ino
op_increment
suffix:semicolon
id|ent
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|autofs_dir_ent
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|ent-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|dentry-&gt;d_name.len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent-&gt;name
)paren
(brace
id|kfree
c_func
(paren
id|ent
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|ent-&gt;hash
op_assign
id|dentry-&gt;d_name.hash
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|dentry-&gt;d_name.name
comma
l_int|1
op_plus
(paren
id|ent-&gt;len
op_assign
id|dentry-&gt;d_name.len
)paren
)paren
suffix:semicolon
id|ent-&gt;ino
op_assign
id|ino
suffix:semicolon
id|ent-&gt;dentry
op_assign
id|dentry
suffix:semicolon
id|autofs_hash_insert
c_func
(paren
id|dh
comma
id|ent
)paren
suffix:semicolon
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
)paren
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
multiline_comment|/* Get/set timeout ioctl() operation */
DECL|function|autofs_get_set_timeout
r_static
r_inline
r_int
id|autofs_get_set_timeout
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
r_int
op_star
id|p
)paren
(brace
r_int
r_int
id|ntimeout
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ntimeout
comma
id|p
)paren
op_logical_or
id|put_user
c_func
(paren
id|sbi-&gt;exp_timeout
op_div
id|HZ
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ntimeout
OG
id|ULONG_MAX
op_div
id|HZ
)paren
id|sbi-&gt;exp_timeout
op_assign
l_int|0
suffix:semicolon
r_else
id|sbi-&gt;exp_timeout
op_assign
id|ntimeout
op_star
id|HZ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return protocol version */
DECL|function|autofs_get_protover
r_static
r_inline
r_int
id|autofs_get_protover
c_func
(paren
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
id|AUTOFS_PROTO_VERSION
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* Perform an expiry operation */
DECL|function|autofs_expire_run
r_static
r_inline
r_int
id|autofs_expire_run
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|autofs_packet_expire
op_star
id|pkt_p
)paren
(brace
r_struct
id|autofs_dir_ent
op_star
id|ent
suffix:semicolon
r_struct
id|autofs_packet_expire
id|pkt
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pkt
comma
l_int|0
comma
r_sizeof
id|pkt
)paren
suffix:semicolon
id|pkt.hdr.proto_version
op_assign
id|AUTOFS_PROTO_VERSION
suffix:semicolon
id|pkt.hdr.type
op_assign
id|autofs_ptype_expire
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi-&gt;exp_timeout
op_logical_or
op_logical_neg
(paren
id|ent
op_assign
id|autofs_expire
c_func
(paren
id|sb
comma
id|sbi
comma
id|mnt
)paren
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|pkt.len
op_assign
id|ent-&gt;len
suffix:semicolon
id|memcpy
c_func
(paren
id|pkt.name
comma
id|ent-&gt;name
comma
id|pkt.len
)paren
suffix:semicolon
id|pkt.name
(braket
id|pkt.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|pkt_p
comma
op_amp
id|pkt
comma
r_sizeof
(paren
r_struct
id|autofs_packet_expire
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl()&squot;s on the root directory is the chief method for the daemon to&n; * generate kernel reactions&n; */
DECL|function|autofs_root_ioctl
r_static
r_int
id|autofs_root_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs_sbi
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_ioctl: cmd = 0x%08x, arg = 0x%08lx, sbi = %p, pgrp = %u&bslash;n&quot;
comma
id|cmd
comma
id|arg
comma
id|sbi
comma
id|current-&gt;pgrp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_IOC_TYPE
c_func
(paren
id|cmd
)paren
op_ne
id|_IOC_TYPE
c_func
(paren
id|AUTOFS_IOC_FIRST
)paren
op_logical_or
id|_IOC_NR
c_func
(paren
id|cmd
)paren
op_minus
id|_IOC_NR
c_func
(paren
id|AUTOFS_IOC_FIRST
)paren
op_ge
id|AUTOFS_IOC_COUNT
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|autofs_oz_mode
c_func
(paren
id|sbi
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|AUTOFS_IOC_READY
suffix:colon
multiline_comment|/* Wait queue: go ahead and retry */
r_return
id|autofs_wait_release
c_func
(paren
id|sbi
comma
(paren
id|autofs_wqt_t
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_case
id|AUTOFS_IOC_FAIL
suffix:colon
multiline_comment|/* Wait queue: fail with ENOENT */
r_return
id|autofs_wait_release
c_func
(paren
id|sbi
comma
(paren
id|autofs_wqt_t
)paren
id|arg
comma
op_minus
id|ENOENT
)paren
suffix:semicolon
r_case
id|AUTOFS_IOC_CATATONIC
suffix:colon
multiline_comment|/* Enter catatonic mode (daemon shutdown) */
id|autofs_catatonic_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|AUTOFS_IOC_PROTOVER
suffix:colon
multiline_comment|/* Get protocol version */
r_return
id|autofs_get_protover
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|AUTOFS_IOC_SETTIMEOUT
suffix:colon
r_return
id|autofs_get_set_timeout
c_func
(paren
id|sbi
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|AUTOFS_IOC_EXPIRE
suffix:colon
r_return
id|autofs_expire_run
c_func
(paren
id|inode-&gt;i_sb
comma
id|sbi
comma
id|filp-&gt;f_vfsmnt
comma
(paren
r_struct
id|autofs_packet_expire
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
)brace
eof
