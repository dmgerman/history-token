multiline_comment|/*&n; *  linux/fs/nfs/file.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Changes Copyright (C) 1994 by Florian La Roche&n; *   - Do not copy data too often around in the kernel.&n; *   - In nfs_file_read the return value of kmalloc wasn&squot;t checked.&n; *   - Put in a better version of read look-ahead buffering. Original idea&n; *     and implementation by Wai S Kok elekokws@ee.nus.sg.&n; *&n; *  Expire cache on write to a file by Wai S Kok (Oct 1994).&n; *&n; *  Total rewrite of read side for new NFS buffer cache.. Linus.&n; *&n; *  nfs regular file handling functions&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_FILE
r_static
r_int
id|nfs_file_mmap
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|nfs_file_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|nfs_file_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_file_flush
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
suffix:semicolon
DECL|variable|nfs_file_operations
r_struct
id|file_operations
id|nfs_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|remote_llseek
comma
id|read
suffix:colon
id|nfs_file_read
comma
id|write
suffix:colon
id|nfs_file_write
comma
id|mmap
suffix:colon
id|nfs_file_mmap
comma
id|open
suffix:colon
id|nfs_open
comma
id|flush
suffix:colon
id|nfs_file_flush
comma
id|release
suffix:colon
id|nfs_release
comma
id|fsync
suffix:colon
id|nfs_fsync
comma
id|lock
suffix:colon
id|nfs_lock
comma
)brace
suffix:semicolon
DECL|variable|nfs_file_inode_operations
r_struct
id|inode_operations
id|nfs_file_inode_operations
op_assign
(brace
id|permission
suffix:colon
id|nfs_permission
comma
id|revalidate
suffix:colon
id|nfs_revalidate
comma
id|setattr
suffix:colon
id|nfs_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Flush all dirty pages, and check for write errors.&n; *&n; */
r_static
r_int
DECL|function|nfs_file_flush
id|nfs_file_flush
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: flush(%s/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
multiline_comment|/* Make sure all async reads have been sent off. We don&squot;t bother&n;&t; * waiting on them though... */
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
id|nfs_pagein_inode
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|status
op_assign
id|nfs_wb_file
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|status
op_assign
id|file-&gt;f_error
suffix:semicolon
id|file-&gt;f_error
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|nfs_file_read
id|nfs_file_read
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
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|result
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: read(%s/%s, %lu@%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
op_star
id|ppos
)paren
suffix:semicolon
id|result
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
id|result
op_assign
id|generic_file_read
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_file_mmap
id|nfs_file_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: mmap(%s/%s)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|status
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
id|status
op_assign
id|generic_file_mmap
c_func
(paren
id|file
comma
id|vma
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Flush any dirty pages for this process, and check for write errors.&n; * The return status from this call provides a reliable indication of&n; * whether any write errors occurred for this process.&n; */
r_static
r_int
DECL|function|nfs_fsync
id|nfs_fsync
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: fsync(%s/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|nfs_wb_file
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|status
op_assign
id|file-&gt;f_error
suffix:semicolon
id|file-&gt;f_error
op_assign
l_int|0
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * This does the &quot;real&quot; work of the write. The generic routine has&n; * allocated the page, locked it, done all the page alignment stuff&n; * calculations etc. Now we should just copy the data from user&n; * space and write it back to the real medium..&n; *&n; * If the writer ends up delaying the write, the writer needs to&n; * increment the page use counts until he is done with the page.&n; */
DECL|function|nfs_prepare_write
r_static
r_int
id|nfs_prepare_write
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
r_return
id|nfs_flush_incompatible
c_func
(paren
id|file
comma
id|page
)paren
suffix:semicolon
)brace
DECL|function|nfs_commit_write
r_static
r_int
id|nfs_commit_write
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
r_int
id|status
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|nfs_updatepage
c_func
(paren
id|file
comma
id|page
comma
id|offset
comma
id|to
op_minus
id|offset
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * The following is used by wait_on_page(), generic_file_readahead()&n; * to initiate the completion of any page readahead operations.&n; */
DECL|function|nfs_sync_page
r_static
r_int
id|nfs_sync_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|index
op_assign
id|page_index
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
r_int
id|rpages
suffix:semicolon
r_int
id|result
suffix:semicolon
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
r_return
l_int|0
suffix:semicolon
id|inode
op_assign
id|mapping-&gt;host
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|0
suffix:semicolon
id|rpages
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rpages
suffix:semicolon
id|result
op_assign
id|nfs_pagein_inode
c_func
(paren
id|inode
comma
id|index
comma
id|rpages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nfs_file_aops
r_struct
id|address_space_operations
id|nfs_file_aops
op_assign
(brace
id|readpage
suffix:colon
id|nfs_readpage
comma
id|sync_page
suffix:colon
id|nfs_sync_page
comma
id|writepage
suffix:colon
id|nfs_writepage
comma
id|prepare_write
suffix:colon
id|nfs_prepare_write
comma
id|commit_write
suffix:colon
id|nfs_commit_write
)brace
suffix:semicolon
multiline_comment|/* &n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|nfs_file_write
id|nfs_file_write
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
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|result
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: write(%s/%s(%ld), %lu@%lu)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|inode-&gt;i_ino
comma
(paren
r_int
r_int
)paren
id|count
comma
(paren
r_int
r_int
)paren
op_star
id|ppos
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out_swapfile
suffix:semicolon
id|result
op_assign
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|out
suffix:semicolon
id|result
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_goto
id|out
suffix:semicolon
id|result
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
id|out_swapfile
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NFS: attempt to write to active swap file!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Lock a (portion of) a file&n; */
r_int
DECL|function|nfs_lock
id|nfs_lock
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
id|cmd
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_lock(f=%s/%ld, t=%x, fl=%x, r=%Ld:%Ld)&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
comma
id|fl-&gt;fl_type
comma
id|fl-&gt;fl_flags
comma
(paren
r_int
r_int
)paren
id|fl-&gt;fl_start
comma
(paren
r_int
r_int
)paren
id|fl-&gt;fl_end
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
id|EINVAL
suffix:semicolon
multiline_comment|/* No mandatory locks over NFS */
r_if
c_cond
(paren
(paren
id|inode-&gt;i_mode
op_amp
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
op_eq
id|S_ISGID
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* Fake OK code if mounted without NLM support */
r_if
c_cond
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|NFS_MOUNT_NONLM
)paren
(brace
r_if
c_cond
(paren
id|IS_GETLK
c_func
(paren
id|cmd
)paren
)paren
id|status
op_assign
id|LOCK_USE_CLNT
suffix:semicolon
r_goto
id|out_ok
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No BSD flocks over NFS allowed.&n;&t; * Note: we could try to fake a POSIX lock request here by&n;&t; * using ((u32) filp | 0x80000000) or some such as the pid.&n;&t; * Not sure whether that would be unique, though, or whether&n;&t; * that would break in other places.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|fl-&gt;fl_owner
op_logical_or
(paren
id|fl-&gt;fl_flags
op_amp
(paren
id|FL_POSIX
op_or
id|FL_BROKEN
)paren
)paren
op_ne
id|FL_POSIX
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/*&n;&t; * Flush all pending writes before doing anything&n;&t; * with locks..&n;&t; */
id|filemap_fdatasync
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|status
op_assign
id|nfs_wb_all
c_func
(paren
id|inode
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|nlmclnt_proc
c_func
(paren
id|inode
comma
id|cmd
comma
id|fl
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure we clear the cache whenever we try to get the lock.&n;&t; * This makes locking act as a cache coherency point.&n;&t; */
id|out_ok
suffix:colon
r_if
c_cond
(paren
(paren
id|IS_SETLK
c_func
(paren
id|cmd
)paren
op_logical_or
id|IS_SETLKW
c_func
(paren
id|cmd
)paren
)paren
op_logical_and
id|fl-&gt;fl_type
op_ne
id|F_UNLCK
)paren
(brace
id|filemap_fdatasync
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|nfs_wb_all
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* we may have slept */
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|nfs_zap_caches
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
eof
