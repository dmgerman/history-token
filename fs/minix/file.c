multiline_comment|/*&n; *  linux/fs/minix/file.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix regular file handling primitives&n; */
macro_line|#include &quot;minix.h&quot;
multiline_comment|/*&n; * We have mostly NULLs here: the current defaults are OK for&n; * the minix filesystem.&n; */
r_int
id|minix_sync_file
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|minix_file_operations
r_struct
id|file_operations
id|minix_file_operations
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
id|fsync
suffix:colon
id|minix_sync_file
comma
)brace
suffix:semicolon
DECL|variable|minix_file_inode_operations
r_struct
id|inode_operations
id|minix_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|minix_truncate
comma
)brace
suffix:semicolon
DECL|function|minix_sync_file
r_int
id|minix_sync_file
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
id|minix_sync_inode
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
