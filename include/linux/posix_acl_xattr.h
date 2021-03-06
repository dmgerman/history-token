multiline_comment|/*&n;  File: linux/posix_acl_xattr.h&n;&n;  Extended attribute system call representation of Access Control Lists.&n;&n;  Copyright (C) 2000 by Andreas Gruenbacher &lt;a.gruenbacher@computer.org&gt;&n;  Copyright (C) 2002 SGI - Silicon Graphics, Inc &lt;linux-xfs@oss.sgi.com&gt;&n; */
macro_line|#ifndef _POSIX_ACL_XATTR_H
DECL|macro|_POSIX_ACL_XATTR_H
mdefine_line|#define _POSIX_ACL_XATTR_H
macro_line|#include &lt;linux/posix_acl.h&gt;
multiline_comment|/* Extended attribute names */
DECL|macro|POSIX_ACL_XATTR_ACCESS
mdefine_line|#define POSIX_ACL_XATTR_ACCESS&t;&quot;system.posix_acl_access&quot;
DECL|macro|POSIX_ACL_XATTR_DEFAULT
mdefine_line|#define POSIX_ACL_XATTR_DEFAULT&t;&quot;system.posix_acl_default&quot;
multiline_comment|/* Supported ACL a_version fields */
DECL|macro|POSIX_ACL_XATTR_VERSION
mdefine_line|#define POSIX_ACL_XATTR_VERSION&t;0x0002
multiline_comment|/* An undefined entry e_id value */
DECL|macro|ACL_UNDEFINED_ID
mdefine_line|#define ACL_UNDEFINED_ID&t;(-1)
r_typedef
r_struct
(brace
DECL|member|e_tag
id|__u16
id|e_tag
suffix:semicolon
DECL|member|e_perm
id|__u16
id|e_perm
suffix:semicolon
DECL|member|e_id
id|__u32
id|e_id
suffix:semicolon
DECL|typedef|posix_acl_xattr_entry
)brace
id|posix_acl_xattr_entry
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|a_version
id|__u32
id|a_version
suffix:semicolon
DECL|member|a_entries
id|posix_acl_xattr_entry
id|a_entries
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|posix_acl_xattr_header
)brace
id|posix_acl_xattr_header
suffix:semicolon
r_static
r_inline
r_int
DECL|function|posix_acl_xattr_size
id|posix_acl_xattr_size
c_func
(paren
r_int
id|count
)paren
(brace
r_return
(paren
r_sizeof
(paren
id|posix_acl_xattr_header
)paren
op_plus
(paren
id|count
op_star
r_sizeof
(paren
id|posix_acl_xattr_entry
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|posix_acl_xattr_count
id|posix_acl_xattr_count
c_func
(paren
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|posix_acl_xattr_header
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|size
op_sub_assign
r_sizeof
(paren
id|posix_acl_xattr_header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_mod
r_sizeof
(paren
id|posix_acl_xattr_entry
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|size
op_div
r_sizeof
(paren
id|posix_acl_xattr_entry
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* _POSIX_ACL_XATTR_H */
eof
