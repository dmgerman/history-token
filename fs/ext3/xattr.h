multiline_comment|/*&n;  File: fs/ext3/xattr.h&n;&n;  On-disk format of extended attributes for the ext3 filesystem.&n;&n;  (C) 2001 Andreas Gruenbacher, &lt;a.gruenbacher@computer.org&gt;&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/xattr.h&gt;
multiline_comment|/* Magic value in attribute blocks */
DECL|macro|EXT3_XATTR_MAGIC
mdefine_line|#define EXT3_XATTR_MAGIC&t;&t;0xEA020000
multiline_comment|/* Maximum number of references to one attribute block */
DECL|macro|EXT3_XATTR_REFCOUNT_MAX
mdefine_line|#define EXT3_XATTR_REFCOUNT_MAX&t;&t;1024
multiline_comment|/* Name indexes */
DECL|macro|EXT3_XATTR_INDEX_MAX
mdefine_line|#define EXT3_XATTR_INDEX_MAX&t;&t;&t;10
DECL|macro|EXT3_XATTR_INDEX_USER
mdefine_line|#define EXT3_XATTR_INDEX_USER&t;&t;&t;1
DECL|macro|EXT3_XATTR_INDEX_POSIX_ACL_ACCESS
mdefine_line|#define EXT3_XATTR_INDEX_POSIX_ACL_ACCESS&t;2
DECL|macro|EXT3_XATTR_INDEX_POSIX_ACL_DEFAULT
mdefine_line|#define EXT3_XATTR_INDEX_POSIX_ACL_DEFAULT&t;3
DECL|struct|ext3_xattr_header
r_struct
id|ext3_xattr_header
(brace
DECL|member|h_magic
id|__u32
id|h_magic
suffix:semicolon
multiline_comment|/* magic number for identification */
DECL|member|h_refcount
id|__u32
id|h_refcount
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|h_blocks
id|__u32
id|h_blocks
suffix:semicolon
multiline_comment|/* number of disk blocks used */
DECL|member|h_hash
id|__u32
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
DECL|struct|ext3_xattr_entry
r_struct
id|ext3_xattr_entry
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
id|__u16
id|e_value_offs
suffix:semicolon
multiline_comment|/* offset in disk block of value */
DECL|member|e_value_block
id|__u32
id|e_value_block
suffix:semicolon
multiline_comment|/* disk block attribute is stored on (n/i) */
DECL|member|e_value_size
id|__u32
id|e_value_size
suffix:semicolon
multiline_comment|/* size of attribute value */
DECL|member|e_hash
id|__u32
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
DECL|macro|EXT3_XATTR_PAD_BITS
mdefine_line|#define EXT3_XATTR_PAD_BITS&t;&t;2
DECL|macro|EXT3_XATTR_PAD
mdefine_line|#define EXT3_XATTR_PAD&t;&t;(1&lt;&lt;EXT3_XATTR_PAD_BITS)
DECL|macro|EXT3_XATTR_ROUND
mdefine_line|#define EXT3_XATTR_ROUND&t;&t;(EXT3_XATTR_PAD-1)
DECL|macro|EXT3_XATTR_LEN
mdefine_line|#define EXT3_XATTR_LEN(name_len) &bslash;&n;&t;(((name_len) + EXT3_XATTR_ROUND + &bslash;&n;&t;sizeof(struct ext3_xattr_entry)) &amp; ~EXT3_XATTR_ROUND)
DECL|macro|EXT3_XATTR_NEXT
mdefine_line|#define EXT3_XATTR_NEXT(entry) &bslash;&n;&t;( (struct ext3_xattr_entry *)( &bslash;&n;&t;  (char *)(entry) + EXT3_XATTR_LEN((entry)-&gt;e_name_len)) )
DECL|macro|EXT3_XATTR_SIZE
mdefine_line|#define EXT3_XATTR_SIZE(size) &bslash;&n;&t;(((size) + EXT3_XATTR_ROUND) &amp; ~EXT3_XATTR_ROUND)
macro_line|# ifdef CONFIG_EXT3_FS_XATTR
DECL|struct|ext3_xattr_handler
r_struct
id|ext3_xattr_handler
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
r_extern
r_int
id|ext3_xattr_register
c_func
(paren
r_int
comma
r_struct
id|ext3_xattr_handler
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_xattr_unregister
c_func
(paren
r_int
comma
r_struct
id|ext3_xattr_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_setxattr
c_func
(paren
r_struct
id|dentry
op_star
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
id|ssize_t
id|ext3_getxattr
c_func
(paren
r_struct
id|dentry
op_star
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
id|ssize_t
id|ext3_listxattr
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
id|ext3_removexattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_xattr_get
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
id|ext3_xattr_list
c_func
(paren
r_struct
id|inode
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
id|ext3_xattr_set
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
r_int
id|ext3_xattr_set_handle
c_func
(paren
id|handle_t
op_star
comma
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
id|ext3_xattr_delete_inode
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_xattr_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|init_ext3_xattr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|exit_ext3_xattr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|# else  /* CONFIG_EXT3_FS_XATTR */
DECL|macro|ext3_setxattr
macro_line|#  define ext3_setxattr&t;&t;NULL
DECL|macro|ext3_getxattr
macro_line|#  define ext3_getxattr&t;&t;NULL
DECL|macro|ext3_listxattr
macro_line|#  define ext3_listxattr&t;NULL
DECL|macro|ext3_removexattr
macro_line|#  define ext3_removexattr&t;NULL
r_static
r_inline
r_int
DECL|function|ext3_xattr_get
id|ext3_xattr_get
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
r_int
DECL|function|ext3_xattr_list
id|ext3_xattr_list
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ext3_xattr_set
id|ext3_xattr_set
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
r_int
DECL|function|ext3_xattr_set_handle
id|ext3_xattr_set_handle
c_func
(paren
id|handle_t
op_star
id|handle
comma
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
DECL|function|ext3_xattr_delete_inode
id|ext3_xattr_delete_inode
c_func
(paren
id|handle_t
op_star
id|handle
comma
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
DECL|function|ext3_xattr_put_super
id|ext3_xattr_put_super
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
DECL|function|init_ext3_xattr
id|init_ext3_xattr
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
DECL|function|exit_ext3_xattr
id|exit_ext3_xattr
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|# endif  /* CONFIG_EXT3_FS_XATTR */
r_extern
r_struct
id|ext3_xattr_handler
id|ext3_xattr_user_handler
suffix:semicolon
eof
