multiline_comment|/*&n; *  linux/fs/ext3/symlink.c&n; *&n; * Only fast symlinks left here - the rest is done by generic code. AV, 1999&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/symlink.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext3 symlink handling code&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
DECL|function|ext3_readlink
r_static
r_int
id|ext3_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_struct
id|ext3_inode_info
op_star
id|ei
op_assign
id|EXT3_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
id|vfs_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
comma
(paren
r_char
op_star
)paren
id|ei-&gt;i_data
)paren
suffix:semicolon
)brace
DECL|function|ext3_follow_link
r_static
r_int
id|ext3_follow_link
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
r_struct
id|ext3_inode_info
op_star
id|ei
op_assign
id|EXT3_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
id|vfs_follow_link
c_func
(paren
id|nd
comma
(paren
r_char
op_star
)paren
id|ei-&gt;i_data
)paren
suffix:semicolon
)brace
DECL|variable|ext3_fast_symlink_inode_operations
r_struct
id|inode_operations
id|ext3_fast_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|ext3_readlink
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
dot
id|follow_link
op_assign
id|ext3_follow_link
comma
multiline_comment|/* BKL not held.  Don&squot;t need */
)brace
suffix:semicolon
eof
