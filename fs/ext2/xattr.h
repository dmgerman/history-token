multiline_comment|/*&n;  File: linux/ext2_xattr.h&n;&n;  On-disk format of extended attributes for the ext2 filesystem.&n;&n;  (C) 2001 Andreas Gruenbacher, &lt;a.gruenbacher@computer.org&gt;&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
multiline_comment|/* Magic value in attribute blocks */
DECL|macro|EXT2_XATTR_MAGIC
mdefine_line|#define EXT2_XATTR_MAGIC&t;&t;0xEA020000
multiline_comment|/* Maximum number of references to one attribute block */
DECL|macro|EXT2_XATTR_REFCOUNT_MAX
mdefine_line|#define EXT2_XATTR_REFCOUNT_MAX&t;&t;1024
multiline_comment|/* Name indexes */
DECL|macro|EXT2_XATTR_INDEX_MAX
mdefine_line|#define EXT2_XATTR_INDEX_MAX&t;&t;&t;10
DECL|macro|EXT2_XATTR_INDEX_USER
mdefine_line|#define EXT2_XATTR_INDEX_USER&t;&t;&t;1
DECL|macro|EXT2_XATTR_INDEX_POSIX_ACL_ACCESS
mdefine_line|#define EXT2_XATTR_INDEX_POSIX_ACL_ACCESS&t;2
DECL|macro|EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT
mdefine_line|#define EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT&t;3
DECL|macro|EXT2_XATTR_INDEX_TRUSTED
mdefine_line|#define EXT2_XATTR_INDEX_TRUSTED&t;&t;4
DECL|macro|EXT2_XATTR_INDEX_LUSTRE
mdefine_line|#define&t;EXT2_XATTR_INDEX_LUSTRE&t;&t;&t;5
DECL|macro|EXT2_XATTR_INDEX_SECURITY
mdefine_line|#define EXT2_XATTR_INDEX_SECURITY&t;        6
DECL|struct|ext2_xattr_header
r_struct
id|ext2_xattr_header
(brace
DECL|member|h_magic
id|__le32
id|h_magic
suffix:semicolon
multiline_comment|/* magic number for identification */
DECL|member|h_refcount
id|__le32
id|h_refcount
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|h_blocks
id|__le32
id|h_blocks
suffix:semicolon
multiline_comment|/* number of disk blocks used */
DECL|member|h_hash
id|__le32
id|h_hash
suffix:semicolon
multiline_comment|/* hash value of all attributes */
DECL|member|h_reserved
id|__u32
id|h_reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* zero right now */
)brace
suffix:semicolon
DECL|struct|ext2_xattr_entry
r_struct
id|ext2_xattr_entry
(brace
DECL|member|e_name_len
id|__u8
id|e_name_len
suffix:semicolon
multiline_comment|/* length of name */
DECL|member|e_name_index
id|__u8
id|e_name_index
suffix:semicolon
multiline_comment|/* attribute name index */
DECL|member|e_value_offs
id|__le16
id|e_value_offs
suffix:semicolon
multiline_comment|/* offset in disk block of value */
DECL|member|e_value_block
id|__le32
id|e_value_block
suffix:semicolon
multiline_comment|/* disk block attribute is stored on (n/i) */
DECL|member|e_value_size
id|__le32
id|e_value_size
suffix:semicolon
multiline_comment|/* size of attribute value */
DECL|member|e_hash
id|__le32
id|e_hash
suffix:semicolon
multiline_comment|/* hash value of name and value */
DECL|member|e_name
r_char
id|e_name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* attribute name */
)brace
suffix:semicolon
DECL|macro|EXT2_XATTR_PAD_BITS
mdefine_line|#define EXT2_XATTR_PAD_BITS&t;&t;2
DECL|macro|EXT2_XATTR_PAD
mdefine_line|#define EXT2_XATTR_PAD&t;&t;(1&lt;&lt;EXT2_XATTR_PAD_BITS)
DECL|macro|EXT2_XATTR_ROUND
mdefine_line|#define EXT2_XATTR_ROUND&t;&t;(EXT2_XATTR_PAD-1)
DECL|macro|EXT2_XATTR_LEN
mdefine_line|#define EXT2_XATTR_LEN(name_len) &bslash;&n;&t;(((name_len) + EXT2_XATTR_ROUND + &bslash;&n;&t;sizeof(struct ext2_xattr_entry)) &amp; ~EXT2_XATTR_ROUND)
DECL|macro|EXT2_XATTR_NEXT
mdefine_line|#define EXT2_XATTR_NEXT(entry) &bslash;&n;&t;( (struct ext2_xattr_entry *)( &bslash;&n;&t;  (char *)(entry) + EXT2_XATTR_LEN((entry)-&gt;e_name_len)) )
DECL|macro|EXT2_XATTR_SIZE
mdefine_line|#define EXT2_XATTR_SIZE(size) &bslash;&n;&t;(((size) + EXT2_XATTR_ROUND) &amp; ~EXT2_XATTR_ROUND)
macro_line|# ifdef CONFIG_EXT2_FS_XATTR
r_extern
r_struct
id|xattr_handler
id|ext2_xattr_user_handler
suffix:semicolon
r_extern
r_struct
id|xattr_handler
id|ext2_xattr_trusted_handler
suffix:semicolon
r_extern
r_struct
id|xattr_handler
id|ext2_xattr_acl_access_handler
suffix:semicolon
r_extern
r_struct
id|xattr_handler
id|ext2_xattr_acl_default_handler
suffix:semicolon
r_extern
r_struct
id|xattr_handler
id|ext2_xattr_security_handler
suffix:semicolon
r_extern
id|ssize_t
id|ext2_listxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_xattr_get
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_xattr_set
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_const
r_char
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_xattr_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_xattr_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|init_ext2_xattr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|exit_ext2_xattr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|xattr_handler
op_star
id|ext2_xattr_handlers
(braket
)braket
suffix:semicolon
macro_line|# else  /* CONFIG_EXT2_FS_XATTR */
r_static
r_inline
r_int
DECL|function|ext2_xattr_get
id|ext2_xattr_get
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|name_index
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
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ext2_xattr_set
id|ext2_xattr_set
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|name_index
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
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ext2_xattr_delete_inode
id|ext2_xattr_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|ext2_xattr_put_super
id|ext2_xattr_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
)brace
r_static
r_inline
r_int
DECL|function|init_ext2_xattr
id|init_ext2_xattr
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|exit_ext2_xattr
id|exit_ext2_xattr
c_func
(paren
r_void
)paren
(brace
)brace
DECL|macro|ext2_xattr_handlers
mdefine_line|#define ext2_xattr_handlers NULL
macro_line|# endif  /* CONFIG_EXT2_FS_XATTR */
eof
