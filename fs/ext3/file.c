multiline_comment|/*&n; *  linux/fs/ext3/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext3 fs regular file handling primitives&n; *&n; *  64-bit file support on 64-bit platforms by Jakub Jelinek&n; *&t;(jj@sunsite.ms.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
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
multiline_comment|/*&n; * ext3_file_write().&n; *&n; * Most things are done in ext3_prepare_write() and ext3_commit_write().&n; */
r_static
id|ssize_t
DECL|function|ext3_file_write
id|ext3_file_write
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
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/*&n;&t; * Nasty: if the file is subject to synchronous writes then we need&n;&t; * to force generic_osync_inode() to call ext3_write_inode().&n;&t; * We do that by marking the inode dirty.  This adds much more&n;&t; * computational expense than we need, but we&squot;re going to sync&n;&t; * anyway.&n;&t; */
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
)paren
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
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
)brace
DECL|variable|ext3_file_operations
r_struct
id|file_operations
id|ext3_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
multiline_comment|/* BKL held */
id|read
suffix:colon
id|generic_file_read
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
id|write
suffix:colon
id|ext3_file_write
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
id|ioctl
suffix:colon
id|ext3_ioctl
comma
multiline_comment|/* BKL held */
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|open
suffix:colon
id|ext3_open_file
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
id|release
suffix:colon
id|ext3_release_file
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
id|fsync
suffix:colon
id|ext3_sync_file
comma
multiline_comment|/* BKL held */
)brace
suffix:semicolon
DECL|variable|ext3_file_inode_operations
r_struct
id|inode_operations
id|ext3_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|ext3_truncate
comma
multiline_comment|/* BKL held */
id|setattr
suffix:colon
id|ext3_setattr
comma
multiline_comment|/* BKL held */
)brace
suffix:semicolon
eof
