multiline_comment|/*&n; * linux/fs/ext3/xattr_user.c&n; * Handler for extended user attributes.&n; *&n; * Copyright (C) 2001 by Andreas Gruenbacher, &lt;a.gruenbacher@computer.org&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ext3_jbd.h&gt;
macro_line|#include &lt;linux/ext3_fs.h&gt;
macro_line|#include &quot;xattr.h&quot;
macro_line|#ifdef CONFIG_EXT3_FS_POSIX_ACL
macro_line|# include &quot;acl.h&quot;
macro_line|#endif
DECL|macro|XATTR_USER_PREFIX
mdefine_line|#define XATTR_USER_PREFIX &quot;user.&quot;
r_static
r_int
DECL|function|ext3_xattr_user_list
id|ext3_xattr_user_list
c_func
(paren
r_char
op_star
id|list
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_int
id|name_len
comma
r_int
id|flags
)paren
(brace
r_const
r_int
id|prefix_len
op_assign
r_sizeof
(paren
id|XATTR_USER_PREFIX
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|XATTR_USER
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|list
)paren
(brace
id|memcpy
c_func
(paren
id|list
comma
id|XATTR_USER_PREFIX
comma
id|prefix_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|list
op_plus
id|prefix_len
comma
id|name
comma
id|name_len
)paren
suffix:semicolon
id|list
(braket
id|prefix_len
op_plus
id|name_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|prefix_len
op_plus
id|name_len
op_plus
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext3_xattr_user_get
id|ext3_xattr_user_get
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|buffer
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|XATTR_USER
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
macro_line|#ifdef CONFIG_EXT3_FS_POSIX_ACL
id|error
op_assign
id|ext3_permission_locked
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
suffix:semicolon
macro_line|#else
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
id|ext3_xattr_get
c_func
(paren
id|inode
comma
id|EXT3_XATTR_INDEX_USER
comma
id|name
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext3_xattr_user_set
id|ext3_xattr_user_set
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|name
comma
r_const
r_void
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;&quot;
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_opt
c_func
(paren
id|inode-&gt;i_sb
comma
id|XATTR_USER
)paren
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|inode-&gt;i_mode
op_amp
id|S_ISVTX
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
macro_line|#ifdef CONFIG_EXT3_FS_POSIX_ACL
id|error
op_assign
id|ext3_permission_locked
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
suffix:semicolon
macro_line|#else
id|error
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
id|ext3_xattr_set
c_func
(paren
id|inode
comma
id|EXT3_XATTR_INDEX_USER
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
)brace
DECL|variable|ext3_xattr_user_handler
r_struct
id|ext3_xattr_handler
id|ext3_xattr_user_handler
op_assign
(brace
dot
id|prefix
op_assign
id|XATTR_USER_PREFIX
comma
dot
id|list
op_assign
id|ext3_xattr_user_list
comma
dot
id|get
op_assign
id|ext3_xattr_user_get
comma
dot
id|set
op_assign
id|ext3_xattr_user_set
comma
)brace
suffix:semicolon
eof
