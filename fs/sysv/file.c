multiline_comment|/*&n; *  linux/fs/sysv/file.c&n; *&n; *  minix/file.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  coh/file.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/file.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  SystemV/Coherent regular file handling primitives&n; */
macro_line|#include &quot;sysv.h&quot;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the coh filesystem.&n; */
DECL|variable|sysv_file_operations
r_struct
id|file_operations
id|sysv_file_operations
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
id|write
op_assign
id|generic_file_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|fsync
op_assign
id|sysv_sync_file
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|sysv_file_inode_operations
r_struct
id|inode_operations
id|sysv_file_inode_operations
op_assign
(brace
dot
id|truncate
op_assign
id|sysv_truncate
comma
dot
id|getattr
op_assign
id|sysv_getattr
comma
)brace
suffix:semicolon
DECL|function|sysv_sync_file
r_int
id|sysv_sync_file
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
id|err
suffix:semicolon
id|err
op_assign
id|sync_mapping_buffers
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|datasync
op_logical_and
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY_DATASYNC
)paren
)paren
r_return
id|err
suffix:semicolon
id|err
op_or_assign
id|sysv_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
