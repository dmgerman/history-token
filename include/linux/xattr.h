multiline_comment|/*&n;  File: linux/xattr.h&n;&n;  Extended attributes handling.&n;&n;  Copyright (C) 2001 by Andreas Gruenbacher &lt;a.gruenbacher@computer.org&gt;&n;  Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n;  Copyright (c) 2004 Red Hat, Inc., James Morris &lt;jmorris@redhat.com&gt;&n;*/
macro_line|#ifndef _LINUX_XATTR_H
DECL|macro|_LINUX_XATTR_H
mdefine_line|#define _LINUX_XATTR_H
DECL|macro|XATTR_CREATE
mdefine_line|#define XATTR_CREATE&t;0x1&t;/* set value, fail if attr already exists */
DECL|macro|XATTR_REPLACE
mdefine_line|#define XATTR_REPLACE&t;0x2&t;/* set value, fail if attr does not exist */
DECL|macro|XATTR_SECURITY_PREFIX
mdefine_line|#define XATTR_SECURITY_PREFIX&t;&quot;security.&quot;
DECL|struct|xattr_handler
r_struct
id|xattr_handler
(brace
DECL|member|prefix
r_char
op_star
id|prefix
suffix:semicolon
DECL|member|list
r_int
(paren
op_star
id|list
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|list
comma
r_int
id|list_size
comma
r_const
r_char
op_star
id|name
comma
r_int
id|name_len
)paren
suffix:semicolon
DECL|member|get
r_int
(paren
op_star
id|get
)paren
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
suffix:semicolon
DECL|member|set
r_int
(paren
op_star
id|set
)paren
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
suffix:semicolon
)brace
suffix:semicolon
id|ssize_t
id|generic_getxattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
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
suffix:semicolon
id|ssize_t
id|generic_listxattr
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
id|buffer_size
)paren
suffix:semicolon
r_int
id|generic_setxattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
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
suffix:semicolon
r_int
id|generic_removexattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_XATTR_H */
eof
