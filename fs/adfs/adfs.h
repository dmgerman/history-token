multiline_comment|/* Internal data structures for ADFS */
DECL|macro|ADFS_FREE_FRAG
mdefine_line|#define ADFS_FREE_FRAG&t;&t; 0
DECL|macro|ADFS_BAD_FRAG
mdefine_line|#define ADFS_BAD_FRAG&t;&t; 1
DECL|macro|ADFS_ROOT_FRAG
mdefine_line|#define ADFS_ROOT_FRAG&t;&t; 2
DECL|macro|ADFS_NDA_OWNER_READ
mdefine_line|#define ADFS_NDA_OWNER_READ&t;(1 &lt;&lt; 0)
DECL|macro|ADFS_NDA_OWNER_WRITE
mdefine_line|#define ADFS_NDA_OWNER_WRITE&t;(1 &lt;&lt; 1)
DECL|macro|ADFS_NDA_LOCKED
mdefine_line|#define ADFS_NDA_LOCKED&t;&t;(1 &lt;&lt; 2)
DECL|macro|ADFS_NDA_DIRECTORY
mdefine_line|#define ADFS_NDA_DIRECTORY&t;(1 &lt;&lt; 3)
DECL|macro|ADFS_NDA_EXECUTE
mdefine_line|#define ADFS_NDA_EXECUTE&t;(1 &lt;&lt; 4)
DECL|macro|ADFS_NDA_PUBLIC_READ
mdefine_line|#define ADFS_NDA_PUBLIC_READ&t;(1 &lt;&lt; 5)
DECL|macro|ADFS_NDA_PUBLIC_WRITE
mdefine_line|#define ADFS_NDA_PUBLIC_WRITE&t;(1 &lt;&lt; 6)
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;dir_f.h&quot;
r_struct
id|buffer_head
suffix:semicolon
multiline_comment|/*&n; * Directory handling&n; */
DECL|struct|adfs_dir
r_struct
id|adfs_dir
(brace
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
DECL|member|nr_buffers
r_int
id|nr_buffers
suffix:semicolon
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
DECL|member|parent_id
r_int
r_int
id|parent_id
suffix:semicolon
DECL|member|dirhead
r_struct
id|adfs_dirheader
id|dirhead
suffix:semicolon
DECL|member|dirtail
r_union
id|adfs_dirtail
id|dirtail
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the overall maximum name length&n; */
DECL|macro|ADFS_MAX_NAME_LEN
mdefine_line|#define ADFS_MAX_NAME_LEN&t;256
DECL|struct|object_info
r_struct
id|object_info
(brace
DECL|member|parent_id
id|__u32
id|parent_id
suffix:semicolon
multiline_comment|/* parent object id&t;*/
DECL|member|file_id
id|__u32
id|file_id
suffix:semicolon
multiline_comment|/* object id&t;&t;*/
DECL|member|loadaddr
id|__u32
id|loadaddr
suffix:semicolon
multiline_comment|/* load address&t;&t;*/
DECL|member|execaddr
id|__u32
id|execaddr
suffix:semicolon
multiline_comment|/* execution address&t;*/
DECL|member|size
id|__u32
id|size
suffix:semicolon
multiline_comment|/* size&t;&t;&t;*/
DECL|member|attr
id|__u8
id|attr
suffix:semicolon
multiline_comment|/* RISC OS attributes&t;*/
DECL|member|name_len
r_int
r_char
id|name_len
suffix:semicolon
multiline_comment|/* name length&t;&t;*/
DECL|member|name
r_char
id|name
(braket
id|ADFS_MAX_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* file name&t;&t;*/
)brace
suffix:semicolon
DECL|struct|adfs_dir_ops
r_struct
id|adfs_dir_ops
(brace
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|id
comma
r_int
r_int
id|sz
comma
r_struct
id|adfs_dir
op_star
id|dir
)paren
suffix:semicolon
DECL|member|setpos
r_int
(paren
op_star
id|setpos
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_int
r_int
id|fpos
)paren
suffix:semicolon
DECL|member|getnext
r_int
(paren
op_star
id|getnext
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
DECL|member|update
r_int
(paren
op_star
id|update
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|adfs_dir
op_star
id|dir
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adfs_discmap
r_struct
id|adfs_discmap
(brace
DECL|member|dm_bh
r_struct
id|buffer_head
op_star
id|dm_bh
suffix:semicolon
DECL|member|dm_startblk
id|__u32
id|dm_startblk
suffix:semicolon
DECL|member|dm_startbit
r_int
r_int
id|dm_startbit
suffix:semicolon
DECL|member|dm_endbit
r_int
r_int
id|dm_endbit
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* dir stuff */
multiline_comment|/* Inode stuff */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
r_int
id|adfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|block
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|create
)paren
suffix:semicolon
macro_line|#else
r_int
id|adfs_bmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|block
)paren
suffix:semicolon
macro_line|#endif
r_struct
id|inode
op_star
id|adfs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
r_void
id|adfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|adfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|unused
)paren
suffix:semicolon
r_int
id|adfs_notify_change
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
id|attr
)paren
suffix:semicolon
multiline_comment|/* map.c */
r_extern
r_int
id|adfs_map_lookup
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|frag_id
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
r_int
id|adfs_map_free
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
multiline_comment|/* Misc */
r_void
id|__adfs_error
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|adfs_error
mdefine_line|#define adfs_error(sb, fmt...) __adfs_error(sb, __FUNCTION__, fmt)
multiline_comment|/* namei.c */
r_extern
r_struct
id|dentry
op_star
id|adfs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
multiline_comment|/* super.c */
multiline_comment|/*&n; * Inodes and file operations&n; */
multiline_comment|/* dir_*.c */
r_extern
r_struct
id|inode_operations
id|adfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|adfs_dir_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|adfs_dentry_operations
suffix:semicolon
r_extern
r_struct
id|adfs_dir_ops
id|adfs_f_dir_ops
suffix:semicolon
r_extern
r_struct
id|adfs_dir_ops
id|adfs_fplus_dir_ops
suffix:semicolon
r_extern
r_int
id|adfs_dir_update
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|object_info
op_star
id|obj
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|adfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|adfs_file_operations
suffix:semicolon
DECL|function|signed_asl
r_extern
r_inline
id|__u32
id|signed_asl
c_func
(paren
id|__u32
id|val
comma
r_int
r_int
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
op_ge
l_int|0
)paren
id|val
op_lshift_assign
id|shift
suffix:semicolon
r_else
id|val
op_rshift_assign
op_minus
id|shift
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate the address of a block in an object given the block offset&n; * and the object identity.&n; *&n; * The root directory ID should always be looked up in the map [3.4]&n; */
r_extern
r_inline
r_int
DECL|function|__adfs_block_map
id|__adfs_block_map
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|object_id
comma
r_int
r_int
id|block
)paren
(brace
r_if
c_cond
(paren
id|object_id
op_amp
l_int|255
)paren
(brace
r_int
r_int
id|off
suffix:semicolon
id|off
op_assign
(paren
id|object_id
op_amp
l_int|255
)paren
op_minus
l_int|1
suffix:semicolon
id|block
op_add_assign
id|off
op_lshift
id|ADFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_log2sharesize
suffix:semicolon
)brace
r_return
id|adfs_map_lookup
c_func
(paren
id|sb
comma
id|object_id
op_rshift
l_int|8
comma
id|block
)paren
suffix:semicolon
)brace
eof
