multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_ACL
DECL|macro|_H_JFS_ACL
mdefine_line|#define _H_JFS_ACL
macro_line|#ifdef CONFIG_JFS_POSIX_ACL
macro_line|#include &lt;linux/xattr_acl.h&gt;
r_struct
id|posix_acl
op_star
id|jfs_get_acl
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|jfs_set_acl
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|posix_acl
op_star
)paren
suffix:semicolon
r_int
id|jfs_permission
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
r_int
id|jfs_init_acl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|jfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;/* CONFIG_JFS_POSIX_ACL */
macro_line|#endif&t;&t;/* _H_JFS_ACL */
eof
