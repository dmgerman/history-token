multiline_comment|/*&n; * linux/fs/ext2/xattr_trusted.c&n; * Handler for trusted extended attributes.&n; *&n; * Copyright (C) 2003 by Andreas Gruenbacher, &lt;a.gruenbacher@computer.org&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &quot;xattr.h&quot;
DECL|macro|XATTR_TRUSTED_PREFIX
mdefine_line|#define XATTR_TRUSTED_PREFIX &quot;trusted.&quot;
r_static
r_int
DECL|function|ext2_xattr_trusted_list
id|ext2_xattr_trusted_list
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
id|XATTR_TRUSTED_PREFIX
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|flags
op_amp
id|XATTR_KERNEL_CONTEXT
)paren
op_logical_or
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
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
id|XATTR_TRUSTED_PREFIX
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
DECL|function|ext2_xattr_trusted_get
id|ext2_xattr_trusted_get
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
(paren
(paren
id|flags
op_amp
id|XATTR_KERNEL_CONTEXT
)paren
op_logical_or
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|ext2_xattr_get
c_func
(paren
id|inode
comma
id|EXT2_XATTR_INDEX_TRUSTED
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
DECL|function|ext2_xattr_trusted_set
id|ext2_xattr_trusted_set
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
(paren
(paren
id|flags
op_amp
id|XATTR_KERNEL_CONTEXT
)paren
op_logical_or
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|ext2_xattr_set
c_func
(paren
id|inode
comma
id|EXT2_XATTR_INDEX_TRUSTED
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
DECL|variable|ext2_xattr_trusted_handler
r_struct
id|ext2_xattr_handler
id|ext2_xattr_trusted_handler
op_assign
(brace
dot
id|prefix
op_assign
id|XATTR_TRUSTED_PREFIX
comma
dot
id|list
op_assign
id|ext2_xattr_trusted_list
comma
dot
id|get
op_assign
id|ext2_xattr_trusted_get
comma
dot
id|set
op_assign
id|ext2_xattr_trusted_set
comma
)brace
suffix:semicolon
eof
