multiline_comment|/*&n;  File: fs/xattr.c&n;&n;  Extended attribute handling.&n;&n;  Copyright (C) 2001 by Andreas Gruenbacher &lt;a.gruenbacher@computer.org&gt;&n;  Copyright (C) 2001 SGI - Silicon Graphics, Inc &lt;linux-xfs@oss.sgi.com&gt;&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Extended attribute SET operations&n; */
r_static
r_int
DECL|function|setxattr
id|setxattr
c_func
(paren
r_struct
id|dentry
op_star
id|d
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
id|error
suffix:semicolon
r_void
op_star
id|kvalue
op_assign
l_int|NULL
suffix:semicolon
r_char
id|kname
(braket
id|XATTR_NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
(paren
id|XATTR_CREATE
op_or
id|XATTR_REPLACE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|strncpy_from_user
c_func
(paren
id|kname
comma
id|name
comma
r_sizeof
(paren
id|kname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
op_logical_or
id|error
op_eq
r_sizeof
(paren
id|kname
)paren
)paren
id|error
op_assign
op_minus
id|ERANGE
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OG
id|XATTR_SIZE_MAX
)paren
r_return
op_minus
id|E2BIG
suffix:semicolon
id|kvalue
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
id|kvalue
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kvalue
comma
id|value
comma
id|size
)paren
)paren
(brace
id|kfree
c_func
(paren
id|kvalue
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|error
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;d_inode-&gt;i_op
op_logical_and
id|d-&gt;d_inode-&gt;i_op-&gt;setxattr
)paren
(brace
id|down
c_func
(paren
op_amp
id|d-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|error
op_assign
id|security_inode_setxattr
c_func
(paren
id|d
comma
id|kname
comma
id|kvalue
comma
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|d-&gt;d_inode-&gt;i_op
op_member_access_from_pointer
id|setxattr
c_func
(paren
id|d
comma
id|kname
comma
id|kvalue
comma
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|security_inode_post_setxattr
c_func
(paren
id|d
comma
id|kname
comma
id|kvalue
comma
id|size
comma
id|flags
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|d-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kvalue
)paren
id|kfree
c_func
(paren
id|kvalue
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_setxattr
id|sys_setxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|setxattr
c_func
(paren
id|nd.dentry
comma
id|name
comma
id|value
comma
id|size
comma
id|flags
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_lsetxattr
id|sys_lsetxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|setxattr
c_func
(paren
id|nd.dentry
comma
id|name
comma
id|value
comma
id|size
comma
id|flags
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_fsetxattr
id|sys_fsetxattr
c_func
(paren
r_int
id|fd
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|f
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|setxattr
c_func
(paren
id|f-&gt;f_dentry
comma
id|name
comma
id|value
comma
id|size
comma
id|flags
)paren
suffix:semicolon
id|fput
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Extended attribute GET operations&n; */
r_static
id|ssize_t
DECL|function|getxattr
id|getxattr
c_func
(paren
r_struct
id|dentry
op_star
id|d
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
)paren
(brace
id|ssize_t
id|error
suffix:semicolon
r_void
op_star
id|kvalue
op_assign
l_int|NULL
suffix:semicolon
r_char
id|kname
(braket
id|XATTR_NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|error
op_assign
id|strncpy_from_user
c_func
(paren
id|kname
comma
id|name
comma
r_sizeof
(paren
id|kname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
op_logical_or
id|error
op_eq
r_sizeof
(paren
id|kname
)paren
)paren
id|error
op_assign
op_minus
id|ERANGE
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OG
id|XATTR_SIZE_MAX
)paren
id|size
op_assign
id|XATTR_SIZE_MAX
suffix:semicolon
id|kvalue
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
id|kvalue
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;d_inode-&gt;i_op
op_logical_and
id|d-&gt;d_inode-&gt;i_op-&gt;getxattr
)paren
(brace
id|error
op_assign
id|security_inode_getxattr
c_func
(paren
id|d
comma
id|kname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|d-&gt;d_inode-&gt;i_op
op_member_access_from_pointer
id|getxattr
c_func
(paren
id|d
comma
id|kname
comma
id|kvalue
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|size
op_logical_and
id|copy_to_user
c_func
(paren
id|value
comma
id|kvalue
comma
id|error
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|ERANGE
op_logical_and
id|size
op_ge
id|XATTR_SIZE_MAX
)paren
(brace
multiline_comment|/* The file system tried to returned a value bigger&n;&t;&t;&t;   than XATTR_SIZE_MAX bytes. Not possible. */
id|error
op_assign
op_minus
id|E2BIG
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|kvalue
)paren
id|kfree
c_func
(paren
id|kvalue
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_getxattr
id|sys_getxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
id|ssize_t
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|getxattr
c_func
(paren
id|nd.dentry
comma
id|name
comma
id|value
comma
id|size
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_lgetxattr
id|sys_lgetxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
id|ssize_t
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|getxattr
c_func
(paren
id|nd.dentry
comma
id|name
comma
id|value
comma
id|size
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_fgetxattr
id|sys_fgetxattr
c_func
(paren
r_int
id|fd
comma
r_char
id|__user
op_star
id|name
comma
r_void
id|__user
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
id|ssize_t
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|f
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|getxattr
c_func
(paren
id|f-&gt;f_dentry
comma
id|name
comma
id|value
comma
id|size
)paren
suffix:semicolon
id|fput
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Extended attribute LIST operations&n; */
r_static
id|ssize_t
DECL|function|listxattr
id|listxattr
c_func
(paren
r_struct
id|dentry
op_star
id|d
comma
r_char
id|__user
op_star
id|list
comma
r_int
id|size
)paren
(brace
id|ssize_t
id|error
suffix:semicolon
r_char
op_star
id|klist
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OG
id|XATTR_LIST_MAX
)paren
id|size
op_assign
id|XATTR_LIST_MAX
suffix:semicolon
id|klist
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
id|klist
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;d_inode-&gt;i_op
op_logical_and
id|d-&gt;d_inode-&gt;i_op-&gt;listxattr
)paren
(brace
id|error
op_assign
id|security_inode_listxattr
c_func
(paren
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|d-&gt;d_inode-&gt;i_op
op_member_access_from_pointer
id|listxattr
c_func
(paren
id|d
comma
id|klist
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|size
op_logical_and
id|copy_to_user
c_func
(paren
id|list
comma
id|klist
comma
id|error
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|ERANGE
op_logical_and
id|size
op_ge
id|XATTR_LIST_MAX
)paren
(brace
multiline_comment|/* The file system tried to returned a list bigger&n;&t;&t;&t;   than XATTR_LIST_MAX bytes. Not possible. */
id|error
op_assign
op_minus
id|E2BIG
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|klist
)paren
id|kfree
c_func
(paren
id|klist
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_listxattr
id|sys_listxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|list
comma
r_int
id|size
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
id|ssize_t
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|listxattr
c_func
(paren
id|nd.dentry
comma
id|list
comma
id|size
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_llistxattr
id|sys_llistxattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|list
comma
r_int
id|size
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
id|ssize_t
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|listxattr
c_func
(paren
id|nd.dentry
comma
id|list
comma
id|size
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
id|ssize_t
DECL|function|sys_flistxattr
id|sys_flistxattr
c_func
(paren
r_int
id|fd
comma
r_char
id|__user
op_star
id|list
comma
r_int
id|size
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
id|ssize_t
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|f
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|listxattr
c_func
(paren
id|f-&gt;f_dentry
comma
id|list
comma
id|size
)paren
suffix:semicolon
id|fput
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Extended attribute REMOVE operations&n; */
r_static
r_int
DECL|function|removexattr
id|removexattr
c_func
(paren
r_struct
id|dentry
op_star
id|d
comma
r_char
id|__user
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
id|kname
(braket
id|XATTR_NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|error
op_assign
id|strncpy_from_user
c_func
(paren
id|kname
comma
id|name
comma
r_sizeof
(paren
id|kname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
op_logical_or
id|error
op_eq
r_sizeof
(paren
id|kname
)paren
)paren
id|error
op_assign
op_minus
id|ERANGE
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;d_inode-&gt;i_op
op_logical_and
id|d-&gt;d_inode-&gt;i_op-&gt;removexattr
)paren
(brace
id|error
op_assign
id|security_inode_removexattr
c_func
(paren
id|d
comma
id|kname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|down
c_func
(paren
op_amp
id|d-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|error
op_assign
id|d-&gt;d_inode-&gt;i_op
op_member_access_from_pointer
id|removexattr
c_func
(paren
id|d
comma
id|kname
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|d-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_removexattr
id|sys_removexattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|removexattr
c_func
(paren
id|nd.dentry
comma
id|name
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_lremovexattr
id|sys_lremovexattr
c_func
(paren
r_char
id|__user
op_star
id|path
comma
r_char
id|__user
op_star
id|name
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|user_path_walk_link
c_func
(paren
id|path
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|removexattr
c_func
(paren
id|nd.dentry
comma
id|name
)paren
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_fremovexattr
id|sys_fremovexattr
c_func
(paren
r_int
id|fd
comma
r_char
id|__user
op_star
id|name
)paren
(brace
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|f
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|removexattr
c_func
(paren
id|f-&gt;f_dentry
comma
id|name
)paren
suffix:semicolon
id|fput
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
