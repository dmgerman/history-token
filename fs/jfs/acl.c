multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Copyright (c) Andreas Gruenbacher, 2001&n; *   Copyright (c) Linus Torvalds, 1991, 1992&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_xattr.h&quot;
macro_line|#include &quot;jfs_acl.h&quot;
DECL|function|jfs_get_acl
r_struct
id|posix_acl
op_star
id|jfs_get_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
r_char
op_star
id|ea_name
suffix:semicolon
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|posix_acl
op_star
op_star
id|p_acl
suffix:semicolon
r_int
id|size
suffix:semicolon
r_char
op_star
id|value
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|ea_name
op_assign
id|XATTR_NAME_ACL_ACCESS
suffix:semicolon
id|p_acl
op_assign
op_amp
id|ji-&gt;i_acl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|ea_name
op_assign
id|XATTR_NAME_ACL_DEFAULT
suffix:semicolon
id|p_acl
op_assign
op_amp
id|ji-&gt;i_default_acl
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p_acl
op_ne
id|JFS_ACL_NOT_CACHED
)paren
r_return
id|posix_acl_dup
c_func
(paren
op_star
id|p_acl
)paren
suffix:semicolon
id|size
op_assign
id|__jfs_getxattr
c_func
(paren
id|inode
comma
id|ea_name
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
id|value
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|size
op_assign
id|__jfs_getxattr
c_func
(paren
id|inode
comma
id|ea_name
comma
id|value
comma
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
op_minus
id|ENODATA
)paren
(brace
op_star
id|p_acl
op_assign
l_int|NULL
suffix:semicolon
id|acl
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|acl
op_assign
id|ERR_PTR
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|acl
op_assign
id|posix_acl_from_xattr
c_func
(paren
id|value
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
op_star
id|p_acl
op_assign
id|posix_acl_dup
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
)paren
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
id|acl
suffix:semicolon
)brace
DECL|function|jfs_set_acl
r_int
id|jfs_set_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
comma
r_struct
id|posix_acl
op_star
id|acl
)paren
(brace
r_char
op_star
id|ea_name
suffix:semicolon
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|posix_acl
op_star
op_star
id|p_acl
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|value
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACL_TYPE_ACCESS
suffix:colon
id|ea_name
op_assign
id|XATTR_NAME_ACL_ACCESS
suffix:semicolon
id|p_acl
op_assign
op_amp
id|ji-&gt;i_acl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACL_TYPE_DEFAULT
suffix:colon
id|ea_name
op_assign
id|XATTR_NAME_ACL_DEFAULT
suffix:semicolon
id|p_acl
op_assign
op_amp
id|ji-&gt;i_default_acl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
id|acl
ques
c_cond
op_minus
id|EACCES
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acl
)paren
(brace
id|size
op_assign
id|xattr_acl_size
c_func
(paren
id|acl-&gt;a_count
)paren
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rc
op_assign
id|posix_acl_to_xattr
c_func
(paren
id|acl
comma
id|value
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
id|rc
op_assign
id|__jfs_setxattr
c_func
(paren
id|inode
comma
id|ea_name
comma
id|value
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|value
)paren
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
r_if
c_cond
(paren
op_star
id|p_acl
op_logical_and
(paren
op_star
id|p_acl
op_ne
id|JFS_ACL_NOT_CACHED
)paren
)paren
id|posix_acl_release
c_func
(paren
op_star
id|p_acl
)paren
suffix:semicolon
op_star
id|p_acl
op_assign
id|posix_acl_dup
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;jfs_permission()&n; *&n; * modified vfs_permission to check posix acl&n; */
DECL|function|jfs_permission
r_int
id|jfs_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
id|umode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|MAY_WRITE
)paren
(brace
multiline_comment|/*&n;&t;&t; * Nobody gets write access to a read-only fs.&n;&t;&t; */
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
op_logical_and
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Nobody gets write access to an immutable file.&n;&t;&t; */
r_if
c_cond
(paren
id|IS_IMMUTABLE
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;fsuid
op_eq
id|inode-&gt;i_uid
)paren
(brace
id|mode
op_rshift_assign
l_int|6
suffix:semicolon
r_goto
id|check_mode
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * ACL can&squot;t contain additional permissions if the ACL_MASK entry&n;&t; * is zero.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|S_IRWXG
)paren
)paren
r_goto
id|check_groups
suffix:semicolon
r_if
c_cond
(paren
id|ji-&gt;i_acl
op_eq
id|JFS_ACL_NOT_CACHED
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
suffix:semicolon
id|acl
op_assign
id|jfs_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ji-&gt;i_acl
)paren
(brace
r_int
id|rc
op_assign
id|posix_acl_permission
c_func
(paren
id|inode
comma
id|ji-&gt;i_acl
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
op_minus
id|EACCES
)paren
r_goto
id|check_capabilities
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|check_groups
suffix:colon
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
)paren
id|mode
op_rshift_assign
l_int|3
suffix:semicolon
id|check_mode
suffix:colon
multiline_comment|/*&n;&t; * If the DACs are ok we don&squot;t need any capability check.&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|mode
op_amp
id|mask
op_amp
(paren
id|MAY_READ
op_or
id|MAY_WRITE
op_or
id|MAY_EXEC
)paren
)paren
op_eq
id|mask
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|check_capabilities
suffix:colon
multiline_comment|/*&n;&t; * Read/write DACs are always overridable.&n;&t; * Executable DACs are overridable if at least one exec bit is set.&n;&t; */
r_if
c_cond
(paren
(paren
id|mask
op_amp
(paren
id|MAY_READ
op_or
id|MAY_WRITE
)paren
)paren
op_logical_or
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXUGO
)paren
)paren
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_DAC_OVERRIDE
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Searching includes executable on directories, else just read.&n;&t; */
r_if
c_cond
(paren
id|mask
op_eq
id|MAY_READ
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
op_logical_neg
(paren
id|mask
op_amp
id|MAY_WRITE
)paren
)paren
)paren
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_DAC_READ_SEARCH
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
DECL|function|jfs_init_acl
r_int
id|jfs_init_acl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|posix_acl
op_star
id|clone
suffix:semicolon
id|mode_t
id|mode
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|acl
op_assign
id|jfs_get_acl
c_func
(paren
id|dir
comma
id|ACL_TYPE_DEFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acl
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|rc
op_assign
id|jfs_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_DEFAULT
comma
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|cleanup
suffix:semicolon
)brace
id|clone
op_assign
id|posix_acl_clone
c_func
(paren
id|acl
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clone
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|rc
op_assign
id|posix_acl_create_masq
c_func
(paren
id|clone
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ge
l_int|0
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|0
)paren
id|rc
op_assign
id|jfs_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|clone
)paren
suffix:semicolon
)brace
id|posix_acl_release
c_func
(paren
id|clone
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
)brace
r_else
id|inode-&gt;i_mode
op_and_assign
op_complement
id|current-&gt;fs-&gt;umask
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|jfs_acl_chmod
r_int
id|jfs_acl_chmod
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|posix_acl
op_star
id|acl
comma
op_star
id|clone
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|acl
op_assign
id|jfs_get_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|acl
)paren
op_logical_or
op_logical_neg
id|acl
)paren
r_return
id|PTR_ERR
c_func
(paren
id|acl
)paren
suffix:semicolon
id|clone
op_assign
id|posix_acl_clone
c_func
(paren
id|acl
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|acl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clone
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rc
op_assign
id|posix_acl_chmod_masq
c_func
(paren
id|clone
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
id|jfs_set_acl
c_func
(paren
id|inode
comma
id|ACL_TYPE_ACCESS
comma
id|clone
)paren
suffix:semicolon
id|posix_acl_release
c_func
(paren
id|clone
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|jfs_setattr
r_int
id|jfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|iattr
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
id|rc
suffix:semicolon
id|rc
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|iattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|inode_setattr
c_func
(paren
id|inode
comma
id|iattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iattr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
id|rc
op_assign
id|jfs_acl_chmod
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
