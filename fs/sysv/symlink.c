multiline_comment|/*&n; *  linux/fs/sysv/symlink.c&n; *&n; *  Handling of System V filesystem fast symlinks extensions.&n; *  Aug 2001, Christoph Hellwig (hch@infradead.org)&n; */
macro_line|#include &quot;sysv.h&quot;
macro_line|#include &lt;linux/namei.h&gt;
DECL|function|sysv_follow_link
r_static
r_int
id|sysv_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
id|nd_set_link
c_func
(paren
id|nd
comma
(paren
r_char
op_star
)paren
id|SYSV_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|i_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysv_fast_symlink_inode_operations
r_struct
id|inode_operations
id|sysv_fast_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|generic_readlink
comma
dot
id|follow_link
op_assign
id|sysv_follow_link
comma
)brace
suffix:semicolon
eof
