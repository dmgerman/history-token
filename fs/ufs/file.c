multiline_comment|/*&n; *  linux/fs/ufs/file.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/file.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 fs regular file handling primitives&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; * We have mostly NULL&squot;s here: the current defaults are ok for&n; * the ufs filesystem.&n; */
DECL|variable|ufs_file_operations
r_struct
id|file_operations
id|ufs_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|generic_file_llseek
comma
id|read
suffix:colon
id|generic_file_read
comma
id|write
suffix:colon
id|generic_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|open
suffix:colon
id|generic_file_open
comma
)brace
suffix:semicolon
DECL|variable|ufs_file_inode_operations
r_struct
id|inode_operations
id|ufs_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|ufs_truncate
comma
)brace
suffix:semicolon
eof
