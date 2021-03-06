multiline_comment|/*&n; *  linux/fs/ufs/symlink.c&n; *&n; * Only fast symlinks left here - the rest is done by generic code. AV, 1999&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@emai.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  from&n; *&n; *  linux/fs/ext2/symlink.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/symlink.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 symlink handling code&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
DECL|function|ufs_follow_link
r_static
r_int
id|ufs_follow_link
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
id|ufs_inode_info
op_star
id|p
op_assign
id|UFS_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
id|nd_set_link
c_func
(paren
id|nd
comma
(paren
r_char
op_star
)paren
id|p-&gt;i_u1.i_symlink
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ufs_fast_symlink_inode_operations
r_struct
id|inode_operations
id|ufs_fast_symlink_inode_operations
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
id|ufs_follow_link
comma
)brace
suffix:semicolon
eof
