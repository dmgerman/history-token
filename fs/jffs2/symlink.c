multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: symlink.c,v 1.12 2003/10/04 08:33:07 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;nodelist.h&quot;
r_int
id|jffs2_readlink
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
suffix:semicolon
r_int
id|jffs2_follow_link
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
suffix:semicolon
DECL|variable|jffs2_symlink_inode_operations
r_struct
id|inode_operations
id|jffs2_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|jffs2_readlink
comma
dot
id|follow_link
op_assign
id|jffs2_follow_link
comma
dot
id|setattr
op_assign
id|jffs2_setattr
)brace
suffix:semicolon
DECL|function|jffs2_readlink
r_int
id|jffs2_readlink
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
r_int
r_char
op_star
id|kbuf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|kbuf
op_assign
id|jffs2_getlink
c_func
(paren
id|JFFS2_SB_INFO
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_sb
)paren
comma
id|JFFS2_INODE_INFO
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|kbuf
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|kbuf
)paren
suffix:semicolon
id|ret
op_assign
id|vfs_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
comma
id|kbuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_follow_link
r_int
id|jffs2_follow_link
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
r_int
r_char
op_star
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|buf
op_assign
id|jffs2_getlink
c_func
(paren
id|JFFS2_SB_INFO
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_sb
)paren
comma
id|JFFS2_INODE_INFO
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|buf
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|buf
)paren
suffix:semicolon
id|ret
op_assign
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
