multiline_comment|/*&n; *  linux/fs/adfs/file.c&n; *&n; * Copyright (C) 1997-1999 Russell King&n; * from:&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  adfs regular file handling primitives           &n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;&t;/* for file_fsync() */
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &quot;adfs.h&quot;
DECL|variable|adfs_file_operations
r_struct
id|file_operations
id|adfs_file_operations
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
id|generic_file_read
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|fsync
op_assign
id|file_fsync
comma
dot
id|write
op_assign
id|generic_file_write
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|adfs_file_inode_operations
r_struct
id|inode_operations
id|adfs_file_inode_operations
op_assign
(brace
dot
id|setattr
op_assign
id|adfs_notify_change
comma
)brace
suffix:semicolon
eof
