multiline_comment|/*&n; *  file.c&n; *&n; *  Copyright (C) 1995, 1996, 1997 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; *  Please add a note about your changes to smbfs in the ChangeLog file.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/smbno.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &quot;smb_debug.h&quot;
macro_line|#include &quot;proto.h&quot;
r_static
r_int
DECL|function|smb_fsync
id|smb_fsync
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
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;sync file %s/%s&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The VFS will writepage() all dirty pages for us, but we&n;&t; * should send a SMBflush to the server, letting it know that&n;&t; * we want things synchronized with actual storage.&n;&t; *&n;&t; * Note: this function requires all pages to have been written already&n;&t; *       (should be ok with writepage_sync)&n;&t; */
id|result
op_assign
id|smb_proc_flush
c_func
(paren
id|server
comma
id|SMB_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|fileid
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page synchronously.&n; */
r_static
r_int
DECL|function|smb_readpage_sync
id|smb_readpage_sync
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_char
op_star
id|buffer
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|loff_t
id|offset
op_assign
(paren
id|loff_t
)paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_int
r_int
id|rsize
op_assign
id|smb_get_rsize
c_func
(paren
id|server
)paren
suffix:semicolon
r_int
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_int
id|result
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, count=%d@%Ld, rsize=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|count
comma
id|offset
comma
id|rsize
)paren
suffix:semicolon
id|result
op_assign
id|smb_open
c_func
(paren
id|dentry
comma
id|SMB_O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|io_error
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|rsize
)paren
id|rsize
op_assign
id|count
suffix:semicolon
id|result
op_assign
id|server-&gt;ops
op_member_access_from_pointer
id|read
c_func
(paren
id|dentry-&gt;d_inode
comma
id|offset
comma
id|rsize
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|io_error
suffix:semicolon
id|count
op_sub_assign
id|result
suffix:semicolon
id|offset
op_add_assign
id|result
suffix:semicolon
id|buffer
op_add_assign
id|result
suffix:semicolon
id|dentry-&gt;d_inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|rsize
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|count
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
id|result
op_assign
l_int|0
suffix:semicolon
id|io_error
suffix:colon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * We are called with the page locked and we unlock it when done.&n; */
r_static
r_int
DECL|function|smb_readpage
id|smb_readpage
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
r_int
id|error
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|error
op_assign
id|smb_readpage_sync
c_func
(paren
id|dentry
comma
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a page synchronously.&n; * Offset is the data offset within the page.&n; */
r_static
r_int
DECL|function|smb_writepage_sync
id|smb_writepage_sync
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|pageoffset
comma
r_int
r_int
id|count
)paren
(brace
id|loff_t
id|offset
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|pageoffset
suffix:semicolon
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
id|wsize
op_assign
id|smb_get_wsize
c_func
(paren
id|server
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|offset
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
id|pageoffset
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file ino=%ld, fileid=%d, count=%d@%Ld, wsize=%d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|SMB_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fileid
comma
id|count
comma
id|offset
comma
id|wsize
)paren
suffix:semicolon
r_do
(brace
r_int
id|write_ret
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|wsize
)paren
id|wsize
op_assign
id|count
suffix:semicolon
id|write_ret
op_assign
id|server-&gt;ops
op_member_access_from_pointer
id|write
c_func
(paren
id|inode
comma
id|offset
comma
id|wsize
comma
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_ret
OL
l_int|0
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;failed write, wsize=%d, write_ret=%d&bslash;n&quot;
comma
id|wsize
comma
id|write_ret
)paren
suffix:semicolon
id|ret
op_assign
id|write_ret
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* N.B. what if result &lt; wsize?? */
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
id|write_ret
OL
id|wsize
)paren
id|PARANOIA
c_func
(paren
l_string|&quot;short write, wsize=%d, write_ret=%d&bslash;n&quot;
comma
id|wsize
comma
id|write_ret
)paren
suffix:semicolon
macro_line|#endif
id|buffer
op_add_assign
id|wsize
suffix:semicolon
id|offset
op_add_assign
id|wsize
suffix:semicolon
id|count
op_sub_assign
id|wsize
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Update the inode now rather than waiting for a refresh.&n;&t;&t; */
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|SMB_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|SMB_F_LOCALWRITE
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|inode-&gt;i_size
)paren
id|inode-&gt;i_size
op_assign
id|offset
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Write a page to the server. This will be used for NFS swapping only&n; * (for now), and we currently do this synchronously only.&n; *&n; * We are called with the page locked and we unlock it when done.&n; */
r_static
r_int
DECL|function|smb_writepage
id|smb_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|end_index
suffix:semicolon
r_int
id|offset
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
id|BUG
c_func
(paren
)paren
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
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|end_index
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* easy case */
r_if
c_cond
(paren
id|page-&gt;index
OL
id|end_index
)paren
r_goto
id|do_it
suffix:semicolon
multiline_comment|/* things got complicated... */
id|offset
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* OK, are we completely out? */
r_if
c_cond
(paren
id|page-&gt;index
op_ge
id|end_index
op_plus
l_int|1
op_logical_or
op_logical_neg
id|offset
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* truncated - don&squot;t care */
id|do_it
suffix:colon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|smb_writepage_sync
c_func
(paren
id|inode
comma
id|page
comma
l_int|0
comma
id|offset
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_updatepage
id|smb_updatepage
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
r_int
id|offset
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|DEBUG1
c_func
(paren
l_string|&quot;(%s/%s %d@%ld)&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|count
comma
(paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_return
id|smb_writepage_sync
c_func
(paren
id|dentry-&gt;d_inode
comma
id|page
comma
id|offset
comma
id|count
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|smb_file_read
id|smb_file_read
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|ssize_t
id|status
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, count=%lu@%lu&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
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
id|status
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s validation failed, error=%Zd&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|status
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|VERBOSE
c_func
(paren
l_string|&quot;before read, size=%ld, flags=%x, atime=%ld&bslash;n&quot;
comma
(paren
r_int
)paren
id|dentry-&gt;d_inode-&gt;i_size
comma
id|dentry-&gt;d_inode-&gt;i_flags
comma
id|dentry-&gt;d_inode-&gt;i_atime
)paren
suffix:semicolon
id|status
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
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_file_mmap
id|smb_file_mmap
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
r_int
id|status
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, address %lu - %lu&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
)paren
suffix:semicolon
id|status
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s validation failed, error=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|status
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|smb_file_sendfile
id|smb_file_sendfile
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|__user
op_star
id|target
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
id|ssize_t
id|status
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, pos=%Ld, count=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
op_star
id|ppos
comma
id|count
)paren
suffix:semicolon
id|status
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s validation failed, error=%zd&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|status
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|status
op_assign
id|generic_file_sendfile
c_func
(paren
id|file
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
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * This does the &quot;real&quot; work of the write. The generic routine has&n; * allocated the page, locked it, done all the page alignment stuff&n; * calculations etc. Now we should just copy the data from user&n; * space and write it back to the real medium..&n; *&n; * If the writer ends up delaying the write, the writer needs to&n; * increment the page use counts until he is done with the page.&n; */
DECL|function|smb_prepare_write
r_static
r_int
id|smb_prepare_write
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
l_int|0
suffix:semicolon
)brace
DECL|function|smb_commit_write
r_static
r_int
id|smb_commit_write
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
id|status
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|smb_updatepage
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
DECL|variable|smb_file_aops
r_struct
id|address_space_operations
id|smb_file_aops
op_assign
(brace
dot
id|readpage
op_assign
id|smb_readpage
comma
dot
id|writepage
op_assign
id|smb_writepage
comma
dot
id|prepare_write
op_assign
id|smb_prepare_write
comma
dot
id|commit_write
op_assign
id|smb_commit_write
)brace
suffix:semicolon
multiline_comment|/* &n; * Write to a file (through the page cache).&n; */
r_static
id|ssize_t
DECL|function|smb_file_write
id|smb_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|ssize_t
id|result
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, count=%lu@%lu&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
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
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s validation failed, error=%Zd&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|result
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|result
op_assign
id|smb_open
c_func
(paren
id|dentry
comma
id|SMB_O_WRONLY
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
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
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
id|VERBOSE
c_func
(paren
l_string|&quot;pos=%ld, size=%ld, mtime=%ld, atime=%ld&bslash;n&quot;
comma
(paren
r_int
)paren
id|file-&gt;f_pos
comma
(paren
r_int
)paren
id|dentry-&gt;d_inode-&gt;i_size
comma
id|dentry-&gt;d_inode-&gt;i_mtime
comma
id|dentry-&gt;d_inode-&gt;i_atime
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_file_open
id|smb_file_open
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
id|file
)paren
(brace
r_int
id|result
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_int
id|smb_mode
op_assign
(paren
id|file-&gt;f_mode
op_amp
id|O_ACCMODE
)paren
op_minus
l_int|1
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|smb_open
c_func
(paren
id|dentry
comma
id|smb_mode
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
id|SMB_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|openers
op_increment
suffix:semicolon
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
r_static
r_int
DECL|function|smb_file_release
id|smb_file_release
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
id|file
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|SMB_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|openers
)paren
(brace
multiline_comment|/* We must flush any dirty pages now as we won&squot;t be able to&n;&t;&t;   write anything after close. mmap can trigger this.&n;&t;&t;   &quot;openers&quot; should perhaps include mmap&squot;ers ... */
id|filemap_fdatawrite
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|filemap_fdatawait
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
id|smb_close
c_func
(paren
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether the required access is compatible with&n; * an inode&squot;s permission. SMB doesn&squot;t recognize superuser&n; * privileges, so we need our own check for this.&n; */
r_static
r_int
DECL|function|smb_file_permission
id|smb_file_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;mode=%x, mask=%x&bslash;n&quot;
comma
id|mode
comma
id|mask
)paren
suffix:semicolon
multiline_comment|/* Look at user permissions */
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mode
op_amp
l_int|7
op_amp
id|mask
)paren
op_ne
id|mask
)paren
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|smb_file_operations
r_struct
id|file_operations
id|smb_file_operations
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
id|smb_file_read
comma
dot
id|write
op_assign
id|smb_file_write
comma
dot
id|ioctl
op_assign
id|smb_ioctl
comma
dot
id|mmap
op_assign
id|smb_file_mmap
comma
dot
id|open
op_assign
id|smb_file_open
comma
dot
id|release
op_assign
id|smb_file_release
comma
dot
id|fsync
op_assign
id|smb_fsync
comma
dot
id|sendfile
op_assign
id|smb_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|smb_file_inode_operations
r_struct
id|inode_operations
id|smb_file_inode_operations
op_assign
(brace
dot
id|permission
op_assign
id|smb_file_permission
comma
dot
id|getattr
op_assign
id|smb_getattr
comma
dot
id|setattr
op_assign
id|smb_notify_change
comma
)brace
suffix:semicolon
eof
