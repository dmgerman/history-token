macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
multiline_comment|/*&n; * second extended file system inode data in memory&n; */
DECL|struct|ext2_inode_info
r_struct
id|ext2_inode_info
(brace
DECL|member|i_data
id|__le32
id|i_data
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|i_flags
id|__u32
id|i_flags
suffix:semicolon
DECL|member|i_faddr
id|__u32
id|i_faddr
suffix:semicolon
DECL|member|i_frag_no
id|__u8
id|i_frag_no
suffix:semicolon
DECL|member|i_frag_size
id|__u8
id|i_frag_size
suffix:semicolon
DECL|member|i_state
id|__u16
id|i_state
suffix:semicolon
DECL|member|i_file_acl
id|__u32
id|i_file_acl
suffix:semicolon
DECL|member|i_dir_acl
id|__u32
id|i_dir_acl
suffix:semicolon
DECL|member|i_dtime
id|__u32
id|i_dtime
suffix:semicolon
multiline_comment|/*&n;&t; * i_block_group is the number of the block group which contains&n;&t; * this file&squot;s inode.  Constant across the lifetime of the inode,&n;&t; * it is ued for making block allocation decisions - we try to&n;&t; * place a file&squot;s data blocks near its inode block, and new inodes&n;&t; * near to their parent directory&squot;s inode.&n;&t; */
DECL|member|i_block_group
id|__u32
id|i_block_group
suffix:semicolon
multiline_comment|/*&n;&t; * i_next_alloc_block is the logical (file-relative) number of the&n;&t; * most-recently-allocated block in this file.  Yes, it is misnamed.&n;&t; * We use this for detecting linearly ascending allocation requests.&n;&t; */
DECL|member|i_next_alloc_block
id|__u32
id|i_next_alloc_block
suffix:semicolon
multiline_comment|/*&n;&t; * i_next_alloc_goal is the *physical* companion to i_next_alloc_block.&n;&t; * it the the physical block number of the block which was most-recently&n;&t; * allocated to this file.  This give us the goal (target) for the next&n;&t; * allocation when we detect linearly ascending requests.&n;&t; */
DECL|member|i_next_alloc_goal
id|__u32
id|i_next_alloc_goal
suffix:semicolon
DECL|member|i_prealloc_block
id|__u32
id|i_prealloc_block
suffix:semicolon
DECL|member|i_prealloc_count
id|__u32
id|i_prealloc_count
suffix:semicolon
DECL|member|i_dir_start_lookup
id|__u32
id|i_dir_start_lookup
suffix:semicolon
macro_line|#ifdef CONFIG_EXT2_FS_XATTR
multiline_comment|/*&n;&t; * Extended attributes can be read independently of the main file&n;&t; * data. Taking i_sem even when reading would cause contention&n;&t; * between readers of EAs and writers of regular file data, so&n;&t; * instead we synchronize on xattr_sem when reading or changing&n;&t; * EAs.&n;&t; */
DECL|member|xattr_sem
r_struct
id|rw_semaphore
id|xattr_sem
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EXT2_FS_POSIX_ACL
DECL|member|i_acl
r_struct
id|posix_acl
op_star
id|i_acl
suffix:semicolon
DECL|member|i_default_acl
r_struct
id|posix_acl
op_star
id|i_default_acl
suffix:semicolon
macro_line|#endif
DECL|member|i_meta_lock
id|rwlock_t
id|i_meta_lock
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Inode dynamic state flags&n; */
DECL|macro|EXT2_STATE_NEW
mdefine_line|#define EXT2_STATE_NEW&t;&t;&t;0x00000001 /* inode is newly created */
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/*&n; * Ok, these declarations are also in &lt;linux/kernel.h&gt; but none of the&n; * ext2 source programs needs to include it so they are duplicated here.&n; */
DECL|function|EXT2_I
r_static
r_inline
r_struct
id|ext2_inode_info
op_star
id|EXT2_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|ext2_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
multiline_comment|/* balloc.c */
r_extern
r_int
id|ext2_bg_has_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_bg_num_gdb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
suffix:semicolon
r_extern
r_int
id|ext2_new_block
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
comma
id|__u32
op_star
comma
id|__u32
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_blocks
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_blocks
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_dirs
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_blocks_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext2_group_desc
op_star
id|ext2_get_group_desc
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_int
id|ext2_add_link
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
id|ino_t
id|ext2_inode_by_name
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_make_empty
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
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_find_entry
(paren
r_struct
id|inode
op_star
comma
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
id|ext2_delete_entry
(paren
r_struct
id|ext2_dir_entry_2
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_empty_dir
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_dotdot
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
r_void
id|ext2_set_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ext2_dir_entry_2
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
multiline_comment|/* fsync.c */
r_extern
r_int
id|ext2_sync_file
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
multiline_comment|/* ialloc.c */
r_extern
r_struct
id|inode
op_star
id|ext2_new_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_inodes
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free
(paren
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_void
id|ext2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_write_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_delete_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_sync_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_discard_prealloc
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_truncate
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_setattr
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_set_inode_flags
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_extern
r_int
id|ext2_ioctl
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_void
id|ext2_error
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ext2_warning
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ext2_update_dynamic_rev
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|ext2_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Inodes and files operations&n; */
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|ext2_dir_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|ext2_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ext2_file_operations
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_struct
id|address_space_operations
id|ext2_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|ext2_nobh_aops
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_struct
id|inode_operations
id|ext2_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ext2_special_inode_operations
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|ext2_fast_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ext2_symlink_inode_operations
suffix:semicolon
eof
