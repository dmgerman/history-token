multiline_comment|/*&n; *  linux/fs/ext3/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext3 fs regular file handling primitives&n; *&n; *  64-bit file support on 64-bit platforms by Jakub Jelinek&n; *&t;(jj@sunsite.ms.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &quot;xattr.h&quot;
macro_line|#include &quot;acl.h&quot;
multiline_comment|/*&n; * Called when an inode is released. Note that this is different&n; * from ext3_file_open: open gets called at every open, but release&n; * gets called only when /all/ the files are closed.&n; */
DECL|function|ext3_release_file
r_static
r_int
id|ext3_release_file
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
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
id|ext3_discard_prealloc
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_dx
c_func
(paren
id|inode
)paren
op_logical_and
id|filp-&gt;private_data
)paren
id|ext3_htree_free_dir_info
c_func
(paren
id|filp-&gt;private_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when an inode is about to be opened.&n; * We use this to disallow opening RW large files on 32bit systems if&n; * the caller didn&squot;t specify O_LARGEFILE.  On 64bit systems we force&n; * on this flag in sys_open.&n; */
DECL|function|ext3_open_file
r_static
r_int
id|ext3_open_file
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_LARGEFILE
)paren
op_logical_and
id|inode-&gt;i_size
OG
l_int|0x7FFFFFFFLL
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ext3_file_write
id|ext3_file_write
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
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
id|pos
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|iocb-&gt;ki_filp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ret
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
multiline_comment|/*&n;&t; * Skip flushing if there was an error, or if nothing was written.&n;&t; */
r_if
c_cond
(paren
id|ret
op_le
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * If the inode is IS_SYNC, or is O_SYNC and we are doing data&n;&t; * journalling then we need to make sure that we force the transaction&n;&t; * to disk to keep all metadata uptodate synchronously.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we are non-data-journaled, then the dirty data has&n;&t;&t; * already been flushed to backing store by generic_osync_inode,&n;&t;&t; * and the inode has been flushed too if there have been any&n;&t;&t; * modifications other than mere timestamp updates.&n;&t;&t; *&n;&t;&t; * Open question --- do we care about flushing timestamps too&n;&t;&t; * if the inode is IS_SYNC?&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ext3_should_journal_data
c_func
(paren
id|inode
)paren
)paren
r_return
id|ret
suffix:semicolon
r_goto
id|force_commit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * So we know that there has been no forced data flush.  If the inode&n;&t; * is marked IS_SYNC, we need to force one ourselves.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|IS_SYNC
c_func
(paren
id|inode
)paren
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Open question #2 --- should we force data to disk here too?  If we&n;&t; * don&squot;t, the only impact is that data=writeback filesystems won&squot;t&n;&t; * flush data to disk automatically on IS_SYNC, only metadata (but&n;&t; * historically, that is what ext2 has done.)&n;&t; */
id|force_commit
suffix:colon
id|err
op_assign
id|ext3_force_commit
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ext3_file_operations
r_struct
id|file_operations
id|ext3_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
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
id|generic_file_aio_read
comma
dot
id|aio_write
op_assign
id|ext3_file_write
comma
dot
id|readv
op_assign
id|generic_file_readv
comma
dot
id|writev
op_assign
id|generic_file_writev
comma
dot
id|ioctl
op_assign
id|ext3_ioctl
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|open
op_assign
id|ext3_open_file
comma
dot
id|release
op_assign
id|ext3_release_file
comma
dot
id|fsync
op_assign
id|ext3_sync_file
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|ext3_file_inode_operations
r_struct
id|inode_operations
id|ext3_file_inode_operations
op_assign
(brace
dot
id|truncate
op_assign
id|ext3_truncate
comma
dot
id|setattr
op_assign
id|ext3_setattr
comma
dot
id|setxattr
op_assign
id|ext3_setxattr
comma
dot
id|getxattr
op_assign
id|ext3_getxattr
comma
dot
id|listxattr
op_assign
id|ext3_listxattr
comma
dot
id|removexattr
op_assign
id|ext3_removexattr
comma
dot
id|permission
op_assign
id|ext3_permission
comma
)brace
suffix:semicolon
eof
