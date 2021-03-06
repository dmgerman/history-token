multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/symlink.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &quot;autofs_i.h&quot;
DECL|function|autofs_follow_link
r_static
r_int
id|autofs_follow_link
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
r_char
op_star
id|s
op_assign
(paren
(paren
r_struct
id|autofs_symlink
op_star
)paren
id|dentry-&gt;d_inode-&gt;u.generic_ip
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
id|nd_set_link
c_func
(paren
id|nd
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|autofs_symlink_inode_operations
r_struct
id|inode_operations
id|autofs_symlink_inode_operations
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
id|autofs_follow_link
)brace
suffix:semicolon
eof
