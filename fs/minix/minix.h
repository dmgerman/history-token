macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
multiline_comment|/*&n; * change the define below to 0 if you want names &gt; info-&gt;s_namelen chars to be&n; * truncated. Else they will be disallowed (ENAMETOOLONG).&n; */
DECL|macro|NO_TRUNCATE
mdefine_line|#define NO_TRUNCATE 1
DECL|macro|INODE_VERSION
mdefine_line|#define INODE_VERSION(inode)&t;minix_sb(inode-&gt;i_sb)-&gt;s_version
DECL|macro|MINIX_V1
mdefine_line|#define MINIX_V1&t;&t;0x0001&t;&t;/* original minix fs */
DECL|macro|MINIX_V2
mdefine_line|#define MINIX_V2&t;&t;0x0002&t;&t;/* minix V2 fs */
multiline_comment|/*&n; * minix fs inode data in memory&n; */
DECL|struct|minix_inode_info
r_struct
id|minix_inode_info
(brace
r_union
(brace
DECL|member|i1_data
id|__u16
id|i1_data
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|i2_data
id|__u32
id|i2_data
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * minix super-block data in memory&n; */
DECL|struct|minix_sb_info
r_struct
id|minix_sb_info
(brace
DECL|member|s_ninodes
r_int
r_int
id|s_ninodes
suffix:semicolon
DECL|member|s_nzones
r_int
r_int
id|s_nzones
suffix:semicolon
DECL|member|s_imap_blocks
r_int
r_int
id|s_imap_blocks
suffix:semicolon
DECL|member|s_zmap_blocks
r_int
r_int
id|s_zmap_blocks
suffix:semicolon
DECL|member|s_firstdatazone
r_int
r_int
id|s_firstdatazone
suffix:semicolon
DECL|member|s_log_zone_size
r_int
r_int
id|s_log_zone_size
suffix:semicolon
DECL|member|s_max_size
r_int
r_int
id|s_max_size
suffix:semicolon
DECL|member|s_dirsize
r_int
id|s_dirsize
suffix:semicolon
DECL|member|s_namelen
r_int
id|s_namelen
suffix:semicolon
DECL|member|s_link_max
r_int
id|s_link_max
suffix:semicolon
DECL|member|s_imap
r_struct
id|buffer_head
op_star
op_star
id|s_imap
suffix:semicolon
DECL|member|s_zmap
r_struct
id|buffer_head
op_star
op_star
id|s_zmap
suffix:semicolon
DECL|member|s_sbh
r_struct
id|buffer_head
op_star
id|s_sbh
suffix:semicolon
DECL|member|s_ms
r_struct
id|minix_super_block
op_star
id|s_ms
suffix:semicolon
DECL|member|s_mount_state
r_int
r_int
id|s_mount_state
suffix:semicolon
DECL|member|s_version
r_int
r_int
id|s_version
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|minix_inode
op_star
id|minix_V1_raw_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|ino_t
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|minix2_inode
op_star
id|minix_V2_raw_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|ino_t
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|minix_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|dir
comma
r_int
op_star
id|error
)paren
suffix:semicolon
r_extern
r_void
id|minix_free_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
r_int
id|minix_count_free_inodes
c_func
(paren
r_struct
id|minix_sb_info
op_star
id|sbi
)paren
suffix:semicolon
r_extern
r_int
id|minix_new_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|minix_free_block
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
r_extern
r_int
r_int
id|minix_count_free_blocks
c_func
(paren
r_struct
id|minix_sb_info
op_star
id|sbi
)paren
suffix:semicolon
r_extern
r_int
id|minix_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|kstat
op_star
)paren
suffix:semicolon
r_extern
r_void
id|V2_minix_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|V1_minix_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|V2_minix_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|minix_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|minix_sync_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|minix_set_inode
c_func
(paren
r_struct
id|inode
op_star
comma
id|dev_t
)paren
suffix:semicolon
r_extern
r_int
id|V1_minix_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|V2_minix_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|V1_minix_blocks
c_func
(paren
id|loff_t
)paren
suffix:semicolon
r_extern
r_int
id|V2_minix_blocks
c_func
(paren
id|loff_t
)paren
suffix:semicolon
r_extern
r_struct
id|minix_dir_entry
op_star
id|minix_find_entry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|minix_add_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|minix_delete_entry
c_func
(paren
r_struct
id|minix_dir_entry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|minix_make_empty
c_func
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
id|minix_empty_dir
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|minix_set_link
c_func
(paren
r_struct
id|minix_dir_entry
op_star
comma
r_struct
id|page
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|minix_dir_entry
op_star
id|minix_dotdot
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
id|ino_t
id|minix_inode_by_name
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|minix_sync_file
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|minix_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|minix_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|minix_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|minix_dir_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|minix_dentry_operations
suffix:semicolon
DECL|function|minix_sb
r_static
r_inline
r_struct
id|minix_sb_info
op_star
id|minix_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|function|minix_i
r_static
r_inline
r_struct
id|minix_inode_info
op_star
id|minix_i
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|minix_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
eof
