macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
macro_line|#include &lt;linux/reiserfs_xattr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|XATTR_TRUSTED_PREFIX
mdefine_line|#define XATTR_TRUSTED_PREFIX &quot;trusted.&quot;
r_static
r_int
DECL|function|trusted_get
id|trusted_get
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
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
OL
r_sizeof
(paren
id|XATTR_TRUSTED_PREFIX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_xattrs
(paren
id|inode-&gt;i_sb
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
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
id|is_reiserfs_priv_object
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|reiserfs_xattr_get
(paren
id|inode
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
DECL|function|trusted_set
id|trusted_set
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
id|strlen
c_func
(paren
id|name
)paren
OL
r_sizeof
(paren
id|XATTR_TRUSTED_PREFIX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_xattrs
(paren
id|inode-&gt;i_sb
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
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
id|is_reiserfs_priv_object
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
id|reiserfs_xattr_set
(paren
id|inode
comma
id|name
comma
id|buffer
comma
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|trusted_del
id|trusted_del
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
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
OL
r_sizeof
(paren
id|XATTR_TRUSTED_PREFIX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_xattrs
(paren
id|inode-&gt;i_sb
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
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
id|is_reiserfs_priv_object
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|trusted_list
id|trusted_list
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
r_int
id|namelen
comma
r_char
op_star
id|out
)paren
(brace
r_int
id|len
op_assign
id|namelen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reiserfs_xattrs
(paren
id|inode-&gt;i_sb
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
op_logical_or
id|is_reiserfs_priv_object
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|memcpy
(paren
id|out
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|trusted_handler
r_struct
id|reiserfs_xattr_handler
id|trusted_handler
op_assign
(brace
dot
id|prefix
op_assign
id|XATTR_TRUSTED_PREFIX
comma
dot
id|get
op_assign
id|trusted_get
comma
dot
id|set
op_assign
id|trusted_set
comma
dot
id|del
op_assign
id|trusted_del
comma
dot
id|list
op_assign
id|trusted_list
comma
)brace
suffix:semicolon
eof
