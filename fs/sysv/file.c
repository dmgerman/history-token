multiline_comment|/*&n; *  linux/fs/sysv/file.c&n; *&n; *  minix/file.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/file.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/file.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent regular file handling primitives&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the coh filesystem.&n; */
DECL|variable|sysv_file_operations
r_struct
id|file_operations
id|sysv_file_operations
op_assign
(brace
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
id|fsync
suffix:colon
id|sysv_sync_file
comma
)brace
suffix:semicolon
DECL|variable|sysv_file_inode_operations
r_struct
id|inode_operations
id|sysv_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|sysv_truncate
comma
id|setattr
suffix:colon
id|sysv_notify_change
comma
)brace
suffix:semicolon
eof
