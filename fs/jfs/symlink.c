multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
r_static
r_int
id|jfs_readlink
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
suffix:semicolon
r_static
r_int
id|jfs_follow_link
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
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|jfs_symlink_inode_operations
r_struct
id|inode_operations
id|jfs_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|jfs_readlink
comma
id|follow_link
suffix:colon
id|jfs_follow_link
comma
)brace
suffix:semicolon
DECL|function|jfs_follow_link
r_static
r_int
id|jfs_follow_link
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
id|JFS_IP
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|i_inline
suffix:semicolon
r_return
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|jfs_readlink
r_static
r_int
id|jfs_readlink
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
r_char
op_star
id|s
op_assign
id|JFS_IP
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|i_inline
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
id|s
)paren
suffix:semicolon
)brace
eof
