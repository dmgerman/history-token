multiline_comment|/* -*- c -*- --------------------------------------------------------------- *&n; *&n; * linux/fs/autofs/root.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *  Copyright 1999-2000 Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
r_static
r_struct
id|dentry
op_star
id|autofs4_dir_lookup
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
id|autofs4_dir_symlink
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
id|autofs4_dir_unlink
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
id|autofs4_dir_rmdir
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
id|autofs4_dir_mkdir
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
id|autofs4_root_ioctl
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
r_static
r_struct
id|dentry
op_star
id|autofs4_root_lookup
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
DECL|variable|autofs4_root_operations
r_struct
id|file_operations
id|autofs4_root_operations
op_assign
(brace
id|open
suffix:colon
id|dcache_dir_open
comma
id|release
suffix:colon
id|dcache_dir_close
comma
id|llseek
suffix:colon
id|dcache_dir_lseek
comma
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|dcache_readdir
comma
id|ioctl
suffix:colon
id|autofs4_root_ioctl
comma
)brace
suffix:semicolon
DECL|variable|autofs4_root_inode_operations
r_struct
id|inode_operations
id|autofs4_root_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|autofs4_root_lookup
comma
id|unlink
suffix:colon
id|autofs4_dir_unlink
comma
id|symlink
suffix:colon
id|autofs4_dir_symlink
comma
id|mkdir
suffix:colon
id|autofs4_dir_mkdir
comma
id|rmdir
suffix:colon
id|autofs4_dir_rmdir
comma
)brace
suffix:semicolon
DECL|variable|autofs4_dir_inode_operations
r_struct
id|inode_operations
id|autofs4_dir_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|autofs4_dir_lookup
comma
id|unlink
suffix:colon
id|autofs4_dir_unlink
comma
id|symlink
suffix:colon
id|autofs4_dir_symlink
comma
id|mkdir
suffix:colon
id|autofs4_dir_mkdir
comma
id|rmdir
suffix:colon
id|autofs4_dir_rmdir
comma
)brace
suffix:semicolon
multiline_comment|/* Update usage from here to top of tree, so that scan of&n;   top-level directories will give a useful result */
DECL|function|autofs4_update_usage
r_static
r_void
id|autofs4_update_usage
c_func
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
id|top
op_assign
id|dentry-&gt;d_sb-&gt;s_root
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|dentry
op_ne
id|top
suffix:semicolon
id|dentry
op_assign
id|dentry-&gt;d_parent
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
)paren
(brace
id|update_atime
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
id|ino-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
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
id|autofs_info
op_star
id|de_info
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Block on any pending expiry here; invalidate the dentry&n;           when expiration is done to trigger mount request with a new&n;           dentry */
r_if
c_cond
(paren
id|de_info
op_logical_and
(paren
id|de_info-&gt;flags
op_amp
id|AUTOFS_INF_EXPIRING
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: waiting for expire %p name=%.*s, flags&amp;PENDING=%s de_info=%p de_info-&gt;flags=%x&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
ques
c_cond
l_string|&quot;t&quot;
suffix:colon
l_string|&quot;f&quot;
comma
id|de_info
comma
id|de_info
ques
c_cond
id|de_info-&gt;flags
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|status
op_assign
id|autofs4_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
comma
id|NFY_NONE
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: expire done status=%d&bslash;n&quot;
comma
id|status
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: dentry=%p %.*s ino=%p&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
multiline_comment|/* Wait for a pending mount, triggering one if there isn&squot;t one already */
r_while
c_loop
(paren
id|dentry-&gt;d_inode
op_eq
l_int|NULL
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: waiting for mount name=%.*s, de_info=%p de_info-&gt;flags=%x&bslash;n&quot;
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
comma
id|de_info
comma
id|de_info
ques
c_cond
id|de_info-&gt;flags
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|status
op_assign
id|autofs4_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
comma
id|NFY_MOUNT
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: mount done status=%d&bslash;n&quot;
comma
id|status
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_logical_and
id|dentry-&gt;d_inode
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Try to get the kernel to invalidate this dentry */
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
)brace
multiline_comment|/* If this is an unused directory that isn&squot;t a mount point,&n;&t;   bitch at the daemon and fix it in user space */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
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
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|dentry-&gt;d_subdirs
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;try_to_fill_entry: mounting existing dir&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
id|autofs4_wait
c_func
(paren
id|sbi
comma
op_amp
id|dentry-&gt;d_name
comma
id|NFY_MOUNT
)paren
op_eq
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t update the usages for the autofs daemon itself, this&n;&t;   is necessary for recursive autofs mounts */
r_if
c_cond
(paren
op_logical_neg
id|autofs4_oz_mode
c_func
(paren
id|sbi
)paren
)paren
id|autofs4_update_usage
c_func
(paren
id|dentry
)paren
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
multiline_comment|/*&n; * Revalidate is called on every cache lookup.  Some of those&n; * cache lookups may actually happen while the dentry is not&n; * yet completely filled in, and revalidate has to delay such&n; * lookups..&n; */
DECL|function|autofs4_root_revalidate
r_static
r_int
id|autofs4_root_revalidate
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
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_struct
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|ino
suffix:semicolon
r_int
id|oz_mode
op_assign
id|autofs4_oz_mode
c_func
(paren
id|sbi
)paren
suffix:semicolon
multiline_comment|/* Pending dentry */
r_if
c_cond
(paren
id|autofs4_ispending
c_func
(paren
id|dentry
)paren
)paren
(brace
r_if
c_cond
(paren
id|autofs4_oz_mode
c_func
(paren
id|sbi
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
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
)brace
multiline_comment|/* Negative dentry.. invalidate if &quot;old&quot; */
r_if
c_cond
(paren
id|dentry-&gt;d_inode
op_eq
l_int|NULL
)paren
r_return
(paren
id|dentry-&gt;d_time
op_minus
id|jiffies
op_le
id|AUTOFS_NEGATIVE_TIMEOUT
)paren
suffix:semicolon
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* Check for a non-mountpoint directory with no contents */
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
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
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|dentry-&gt;d_subdirs
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_root_revalidate: dentry=%p %.*s, emptydir&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oz_mode
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
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
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
multiline_comment|/* Update the usage list */
r_if
c_cond
(paren
op_logical_neg
id|oz_mode
)paren
id|autofs4_update_usage
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|autofs4_revalidate
r_static
r_int
id|autofs4_revalidate
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
id|autofs_sb_info
op_star
id|sbi
op_assign
id|autofs4_sbi
c_func
(paren
id|dentry-&gt;d_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|autofs4_oz_mode
c_func
(paren
id|sbi
)paren
)paren
id|autofs4_update_usage
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|autofs4_dentry_release
r_static
r_void
id|autofs4_dentry_release
c_func
(paren
r_struct
id|dentry
op_star
id|de
)paren
(brace
r_struct
id|autofs_info
op_star
id|inf
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs4_dentry_release: releasing %p&bslash;n&quot;
comma
id|de
)paren
)paren
suffix:semicolon
id|inf
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|de
)paren
suffix:semicolon
id|de-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inf
)paren
(brace
id|inf-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
id|inf-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
id|autofs4_free_ino
c_func
(paren
id|inf
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* For dentries of directories in the root dir */
DECL|variable|autofs4_root_dentry_operations
r_static
r_struct
id|dentry_operations
id|autofs4_root_dentry_operations
op_assign
(brace
id|d_revalidate
suffix:colon
id|autofs4_root_revalidate
comma
id|d_release
suffix:colon
id|autofs4_dentry_release
comma
)brace
suffix:semicolon
multiline_comment|/* For other dentries */
DECL|variable|autofs4_dentry_operations
r_static
r_struct
id|dentry_operations
id|autofs4_dentry_operations
op_assign
(brace
id|d_revalidate
suffix:colon
id|autofs4_revalidate
comma
id|d_release
suffix:colon
id|autofs4_dentry_release
comma
)brace
suffix:semicolon
multiline_comment|/* Lookups in non-root dirs never find anything - if it&squot;s there, it&squot;s&n;   already in the dcache */
multiline_comment|/* SMP-safe */
DECL|function|autofs4_dir_lookup
r_static
r_struct
id|dentry
op_star
id|autofs4_dir_lookup
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
macro_line|#if 0
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_dir_lookup: ignoring lookup of %.*s/%.*s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.len
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
macro_line|#endif
id|dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
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
multiline_comment|/* Lookups in the root directory */
DECL|function|autofs4_root_lookup
r_static
r_struct
id|dentry
op_star
id|autofs4_root_lookup
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
l_string|&quot;autofs_root_lookup: name = %.*s&bslash;n&quot;
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|NAME_MAX
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
multiline_comment|/* File name too long to exist */
id|sbi
op_assign
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|oz_mode
op_assign
id|autofs4_oz_mode
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
id|autofs4_root_dentry_operations
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oz_mode
)paren
id|dentry-&gt;d_flags
op_or_assign
id|DCACHE_AUTOFS_PENDING
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_op
op_logical_and
id|dentry-&gt;d_op-&gt;d_revalidate
)paren
(brace
id|up
c_func
(paren
op_amp
id|dir-&gt;i_sem
)paren
suffix:semicolon
(paren
id|dentry-&gt;d_op-&gt;d_revalidate
)paren
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
)brace
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
DECL|function|autofs4_dir_symlink
r_static
r_int
id|autofs4_dir_symlink
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
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_dir_symlink: %s &lt;- %.*s&bslash;n&quot;
comma
id|symname
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
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
id|autofs4_oz_mode
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
id|ino
op_assign
id|autofs4_init_ino
c_func
(paren
id|ino
comma
id|sbi
comma
id|S_IFLNK
op_or
l_int|0555
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
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
id|ino-&gt;size
op_assign
id|strlen
c_func
(paren
id|symname
)paren
suffix:semicolon
id|ino-&gt;u.symlink
op_assign
id|cp
op_assign
id|kmalloc
c_func
(paren
id|ino-&gt;size
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|ino
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
id|strcpy
c_func
(paren
id|cp
comma
id|symname
)paren
suffix:semicolon
id|inode
op_assign
id|autofs4_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
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
r_if
c_cond
(paren
id|dir
op_eq
id|dir-&gt;i_sb-&gt;s_root-&gt;d_inode
)paren
id|dentry-&gt;d_op
op_assign
op_amp
id|autofs4_root_dentry_operations
suffix:semicolon
r_else
id|dentry-&gt;d_op
op_assign
op_amp
id|autofs4_dentry_operations
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
id|ino
suffix:semicolon
id|ino-&gt;dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|ino-&gt;inode
op_assign
id|inode
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
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
multiline_comment|/*&n; * NOTE!&n; *&n; * Normal filesystems would do a &quot;d_delete()&quot; to tell the VFS dcache&n; * that the file no longer exists. However, doing that means that the&n; * VFS layer can turn the dentry into a negative dentry.  We don&squot;t want&n; * this, because since the unlink is probably the result of an expire.&n; * We simply d_drop it, which allows the dentry lookup to remount it&n; * if necessary.&n; *&n; * If a process is blocked on the dentry waiting for the expire to finish,&n; * it will invalidate the dentry and try to mount with a new one.&n; *&n; * Also see autofs_dir_rmdir().. &n; */
DECL|function|autofs4_dir_unlink
r_static
r_int
id|autofs4_dir_unlink
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
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
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
id|autofs4_oz_mode
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
id|dput
c_func
(paren
id|ino-&gt;dentry
)paren
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
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
DECL|function|autofs4_dir_rmdir
r_static
r_int
id|autofs4_dir_rmdir
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
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
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
id|autofs4_oz_mode
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
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dentry-&gt;d_subdirs
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
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOTEMPTY
suffix:semicolon
)brace
id|list_del_init
c_func
(paren
op_amp
id|dentry-&gt;d_hash
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|dput
c_func
(paren
id|ino-&gt;dentry
)paren
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_nlink
)paren
id|dir-&gt;i_nlink
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
DECL|function|autofs4_dir_mkdir
r_static
r_int
id|autofs4_dir_mkdir
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
id|autofs4_sbi
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
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
id|autofs4_oz_mode
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
id|DPRINTK
c_func
(paren
(paren
l_string|&quot;autofs_dir_mkdir: dentry %p, creating %.*s&bslash;n&quot;
comma
id|dentry
comma
id|dentry-&gt;d_name.len
comma
id|dentry-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|ino
op_assign
id|autofs4_init_ino
c_func
(paren
id|ino
comma
id|sbi
comma
id|S_IFDIR
op_or
l_int|0555
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_eq
l_int|NULL
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
id|inode
op_assign
id|autofs4_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
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
r_if
c_cond
(paren
id|dir
op_eq
id|dir-&gt;i_sb-&gt;s_root-&gt;d_inode
)paren
id|dentry-&gt;d_op
op_assign
op_amp
id|autofs4_root_dentry_operations
suffix:semicolon
r_else
id|dentry-&gt;d_op
op_assign
op_amp
id|autofs4_dentry_operations
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
id|ino
suffix:semicolon
id|ino-&gt;dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|ino-&gt;inode
op_assign
id|inode
suffix:semicolon
id|dir-&gt;i_nlink
op_increment
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME
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
DECL|function|autofs4_get_set_timeout
r_static
r_inline
r_int
id|autofs4_get_set_timeout
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
id|rv
suffix:semicolon
r_int
r_int
id|ntimeout
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rv
op_assign
id|get_user
c_func
(paren
id|ntimeout
comma
id|p
)paren
)paren
op_logical_or
(paren
id|rv
op_assign
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
)paren
r_return
id|rv
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
DECL|function|autofs4_get_protover
r_static
r_inline
r_int
id|autofs4_get_protover
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
id|sbi-&gt;version
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* Identify autofs_dentries - this is so we can tell if there&squot;s&n;   an extra dentry refcount or not.  We only hold a refcount on the&n;   dentry if its non-negative (ie, d_inode != NULL)&n;*/
DECL|function|is_autofs4_dentry
r_int
id|is_autofs4_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
id|dentry
op_logical_and
id|dentry-&gt;d_inode
op_logical_and
(paren
id|dentry-&gt;d_op
op_eq
op_amp
id|autofs4_root_dentry_operations
op_logical_or
id|dentry-&gt;d_op
op_eq
op_amp
id|autofs4_dentry_operations
)paren
op_logical_and
id|dentry-&gt;d_fsdata
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl()&squot;s on the root directory is the chief method for the daemon to&n; * generate kernel reactions&n; */
DECL|function|autofs4_root_ioctl
r_static
r_int
id|autofs4_root_ioctl
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
id|autofs4_sbi
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
id|autofs4_oz_mode
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
id|autofs4_wait_release
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
id|autofs4_wait_release
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
id|autofs4_catatonic_mode
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
id|autofs4_get_protover
c_func
(paren
id|sbi
comma
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
id|autofs4_get_set_timeout
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
multiline_comment|/* return a single thing to expire */
r_case
id|AUTOFS_IOC_EXPIRE
suffix:colon
r_return
id|autofs4_expire_run
c_func
(paren
id|inode-&gt;i_sb
comma
id|filp-&gt;f_vfsmnt
comma
id|sbi
comma
(paren
r_struct
id|autofs_packet_expire
op_star
)paren
id|arg
)paren
suffix:semicolon
multiline_comment|/* same as above, but can send multiple expires through pipe */
r_case
id|AUTOFS_IOC_EXPIRE_MULTI
suffix:colon
r_return
id|autofs4_expire_multi
c_func
(paren
id|inode-&gt;i_sb
comma
id|filp-&gt;f_vfsmnt
comma
id|sbi
comma
(paren
r_int
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
