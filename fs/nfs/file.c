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
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_FILE
r_static
r_int
id|nfs_file_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_file_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
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
id|nfs_file_sendfile
c_func
(paren
r_struct
id|file
op_star
comma
id|loff_t
op_star
comma
r_int
comma
id|read_actor_t
comma
r_void
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|nfs_file_read
c_func
(paren
r_struct
id|kiocb
op_star
comma
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
)paren
suffix:semicolon
r_static
id|ssize_t
id|nfs_file_write
c_func
(paren
r_struct
id|kiocb
op_star
comma
r_const
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
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
r_static
r_int
id|nfs_check_flags
c_func
(paren
r_int
id|flags
)paren
suffix:semicolon
DECL|variable|nfs_file_operations
r_struct
id|file_operations
id|nfs_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|remote_llseek
comma
dot
id|read
op_assign
id|do_sync_read
comma
dot
id|write
op_assign
id|do_sync_write
comma
dot
id|aio_read
op_assign
id|nfs_file_read
comma
dot
id|aio_write
op_assign
id|nfs_file_write
comma
dot
id|mmap
op_assign
id|nfs_file_mmap
comma
dot
id|open
op_assign
id|nfs_file_open
comma
dot
id|flush
op_assign
id|nfs_file_flush
comma
dot
id|release
op_assign
id|nfs_file_release
comma
dot
id|fsync
op_assign
id|nfs_fsync
comma
dot
id|lock
op_assign
id|nfs_lock
comma
dot
id|sendfile
op_assign
id|nfs_file_sendfile
comma
dot
id|check_flags
op_assign
id|nfs_check_flags
comma
)brace
suffix:semicolon
DECL|variable|nfs_file_inode_operations
r_struct
id|inode_operations
id|nfs_file_inode_operations
op_assign
(brace
dot
id|permission
op_assign
id|nfs_permission
comma
dot
id|getattr
op_assign
id|nfs_getattr
comma
dot
id|setattr
op_assign
id|nfs_setattr
comma
)brace
suffix:semicolon
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
DECL|function|nfs_check_flags
r_static
r_int
id|nfs_check_flags
c_func
(paren
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|O_APPEND
op_or
id|O_DIRECT
)paren
)paren
op_eq
(paren
id|O_APPEND
op_or
id|O_DIRECT
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Open file&n; */
r_static
r_int
DECL|function|nfs_file_open
id|nfs_file_open
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
id|nfs_server
op_star
id|server
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
id|nfs_check_flags
c_func
(paren
id|filp-&gt;f_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do NFSv4 open() call */
r_if
c_cond
(paren
(paren
id|open
op_assign
id|server-&gt;rpc_ops-&gt;file_open
)paren
op_ne
l_int|NULL
)paren
id|res
op_assign
id|open
c_func
(paren
id|inode
comma
id|filp
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
r_static
r_int
DECL|function|nfs_file_release
id|nfs_file_release
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
r_return
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_release
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ensure that data+attribute caches are up to date after close() */
id|status
op_assign
id|nfs_wb_all
c_func
(paren
id|inode
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
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
id|__nfs_revalidate_inode
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
r_static
id|ssize_t
DECL|function|nfs_file_read
id|nfs_file_read
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|iocb-&gt;ki_filp-&gt;f_dentry
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
macro_line|#ifdef CONFIG_NFS_DIRECTIO
r_if
c_cond
(paren
id|iocb-&gt;ki_filp-&gt;f_flags
op_amp
id|O_DIRECT
)paren
r_return
id|nfs_file_direct_read
c_func
(paren
id|iocb
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
macro_line|#endif
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
id|pos
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
id|generic_file_aio_read
c_func
(paren
id|iocb
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|nfs_file_sendfile
id|nfs_file_sendfile
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|count
comma
id|read_actor_t
id|actor
comma
r_void
op_star
id|target
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|res
suffix:semicolon
id|dfprintk
c_func
(paren
id|VFS
comma
l_string|&quot;nfs: sendfile(%s/%s, %lu@%Lu)&bslash;n&quot;
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
r_int
)paren
op_star
id|ppos
)paren
suffix:semicolon
id|res
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
id|res
)paren
id|res
op_assign
id|generic_file_sendfile
c_func
(paren
id|filp
comma
id|ppos
comma
id|count
comma
id|actor
comma
id|target
)paren
suffix:semicolon
r_return
id|res
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
id|nfs_wb_all
c_func
(paren
id|inode
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
DECL|variable|nfs_file_aops
r_struct
id|address_space_operations
id|nfs_file_aops
op_assign
(brace
dot
id|readpage
op_assign
id|nfs_readpage
comma
dot
id|readpages
op_assign
id|nfs_readpages
comma
dot
id|set_page_dirty
op_assign
id|__set_page_dirty_nobuffers
comma
dot
id|writepage
op_assign
id|nfs_writepage
comma
dot
id|writepages
op_assign
id|nfs_writepages
comma
dot
id|prepare_write
op_assign
id|nfs_prepare_write
comma
dot
id|commit_write
op_assign
id|nfs_commit_write
comma
macro_line|#ifdef CONFIG_NFS_DIRECTIO
dot
id|direct_IO
op_assign
id|nfs_direct_IO
comma
macro_line|#endif
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
id|kiocb
op_star
id|iocb
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|iocb-&gt;ki_filp-&gt;f_dentry
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
macro_line|#ifdef CONFIG_NFS_DIRECTIO
r_if
c_cond
(paren
id|iocb-&gt;ki_filp-&gt;f_flags
op_amp
id|O_DIRECT
)paren
r_return
id|nfs_file_direct_write
c_func
(paren
id|iocb
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
macro_line|#endif
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
id|pos
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
id|generic_file_aio_write
c_func
(paren
id|iocb
comma
id|buf
comma
id|count
comma
id|pos
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
id|filp-&gt;f_mapping-&gt;host
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
id|status2
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
r_if
c_cond
(paren
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|version
op_ne
l_int|4
)paren
(brace
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
)brace
multiline_comment|/*&n;&t; * No BSD flocks over NFS allowed.&n;&t; * Note: we could try to fake a POSIX lock request here by&n;&t; * using ((u32) filp | 0x80000000) or some such as the pid.&n;&t; * Not sure whether that would be unique, though, or whether&n;&t; * that would break in other places.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|fl-&gt;fl_owner
op_logical_or
op_logical_neg
(paren
id|fl-&gt;fl_flags
op_amp
id|FL_POSIX
)paren
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/*&n;&t; * Flush all pending writes before doing anything&n;&t; * with locks..&n;&t; */
id|status
op_assign
id|filemap_fdatawrite
c_func
(paren
id|filp-&gt;f_mapping
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|status2
op_assign
id|nfs_wb_all
c_func
(paren
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
id|status2
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|status2
op_assign
id|filemap_fdatawait
c_func
(paren
id|filp-&gt;f_mapping
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
id|status2
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
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|lock
c_func
(paren
id|filp
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
id|filemap_fdatawrite
c_func
(paren
id|filp-&gt;f_mapping
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
id|filp-&gt;f_mapping
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
