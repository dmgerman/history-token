multiline_comment|/*&n;  File: fs/ext2/acl.h&n;&n;  (C) 2001 Andreas Gruenbacher, &lt;a.gruenbacher@computer.org&gt;&n;*/
macro_line|#include &lt;linux/xattr_acl.h&gt;
DECL|macro|EXT2_ACL_VERSION
mdefine_line|#define EXT2_ACL_VERSION&t;0x0001
DECL|macro|EXT2_ACL_MAX_ENTRIES
mdefine_line|#define EXT2_ACL_MAX_ENTRIES&t;32
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
DECL|typedef|ext2_acl_entry
)brace
id|ext2_acl_entry
suffix:semicolon
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
DECL|typedef|ext2_acl_entry_short
)brace
id|ext2_acl_entry_short
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|a_version
id|__u32
id|a_version
suffix:semicolon
DECL|typedef|ext2_acl_header
)brace
id|ext2_acl_header
suffix:semicolon
DECL|function|ext2_acl_size
r_static
r_inline
r_int
id|ext2_acl_size
c_func
(paren
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
op_le
l_int|4
)paren
(brace
r_return
r_sizeof
(paren
id|ext2_acl_header
)paren
op_plus
id|count
op_star
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
r_sizeof
(paren
id|ext2_acl_header
)paren
op_plus
l_int|4
op_star
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
op_plus
(paren
id|count
op_minus
l_int|4
)paren
op_star
r_sizeof
(paren
id|ext2_acl_entry
)paren
suffix:semicolon
)brace
)brace
DECL|function|ext2_acl_count
r_static
r_inline
r_int
id|ext2_acl_count
c_func
(paren
r_int
id|size
)paren
(brace
id|ssize_t
id|s
suffix:semicolon
id|size
op_sub_assign
r_sizeof
(paren
id|ext2_acl_header
)paren
suffix:semicolon
id|s
op_assign
id|size
op_minus
l_int|4
op_star
r_sizeof
(paren
id|ext2_acl_entry_short
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|size
op_mod
r_sizeof
(paren
id|ext2_acl_entry_short
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
id|ext2_acl_entry_short
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|s
op_mod
r_sizeof
(paren
id|ext2_acl_entry
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|s
op_div
r_sizeof
(paren
id|ext2_acl_entry
)paren
op_plus
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_EXT2_FS_POSIX_ACL
multiline_comment|/* Value for inode-&gt;u.ext2_i.i_acl and inode-&gt;u.ext2_i.i_default_acl&n;   if the ACL has not been cached */
DECL|macro|EXT2_ACL_NOT_CACHED
mdefine_line|#define EXT2_ACL_NOT_CACHED ((void *)-1)
multiline_comment|/* acl.c */
r_extern
r_int
id|ext2_permission
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
r_extern
r_int
id|ext2_acl_chmod
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_init_acl
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
r_extern
r_int
id|init_ext2_acl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|exit_ext2_acl
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|ext2_permission
mdefine_line|#define ext2_permission NULL
DECL|macro|ext2_get_acl
mdefine_line|#define ext2_get_acl&t;NULL
DECL|macro|ext2_set_acl
mdefine_line|#define ext2_set_acl&t;NULL
r_static
r_inline
r_int
DECL|function|ext2_acl_chmod
id|ext2_acl_chmod
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ext2_init_acl
r_static
r_inline
r_int
id|ext2_init_acl
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
id|inode-&gt;i_mode
op_and_assign
op_complement
id|current-&gt;fs-&gt;umask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
