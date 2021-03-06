macro_line|#ifndef _REISER_FS_I
DECL|macro|_REISER_FS_I
mdefine_line|#define _REISER_FS_I
macro_line|#include &lt;linux/list.h&gt;
r_struct
id|reiserfs_journal_list
suffix:semicolon
multiline_comment|/** bitmasks for i_flags field in reiserfs-specific part of inode */
r_typedef
r_enum
(brace
multiline_comment|/** this says what format of key do all items (but stat data) of&n;      an object have.  If this is set, that format is 3.6 otherwise&n;      - 3.5 */
DECL|enumerator|i_item_key_version_mask
id|i_item_key_version_mask
op_assign
l_int|0x0001
comma
multiline_comment|/** If this is unset, object has 3.5 stat data, otherwise, it has&n;      3.6 stat data with 64bit size, 32bit nlink etc. */
DECL|enumerator|i_stat_data_version_mask
id|i_stat_data_version_mask
op_assign
l_int|0x0002
comma
multiline_comment|/** file might need tail packing on close */
DECL|enumerator|i_pack_on_close_mask
id|i_pack_on_close_mask
op_assign
l_int|0x0004
comma
multiline_comment|/** don&squot;t pack tail of file */
DECL|enumerator|i_nopack_mask
id|i_nopack_mask
op_assign
l_int|0x0008
comma
multiline_comment|/** If those is set, &quot;safe link&quot; was created for this file during&n;      truncate or unlink. Safe link is used to avoid leakage of disk&n;      space on crash with some files open, but unlinked. */
DECL|enumerator|i_link_saved_unlink_mask
id|i_link_saved_unlink_mask
op_assign
l_int|0x0010
comma
DECL|enumerator|i_link_saved_truncate_mask
id|i_link_saved_truncate_mask
op_assign
l_int|0x0020
comma
DECL|enumerator|i_has_xattr_dir
id|i_has_xattr_dir
op_assign
l_int|0x0040
comma
DECL|enumerator|i_data_log
id|i_data_log
op_assign
l_int|0x0080
comma
DECL|typedef|reiserfs_inode_flags
)brace
id|reiserfs_inode_flags
suffix:semicolon
DECL|struct|reiserfs_inode_info
r_struct
id|reiserfs_inode_info
(brace
DECL|member|i_key
id|__u32
id|i_key
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* key is still 4 32 bit integers */
multiline_comment|/** transient inode flags that are never stored on disk. Bitmasks&n;      for this field are defined above. */
DECL|member|i_flags
id|__u32
id|i_flags
suffix:semicolon
DECL|member|i_first_direct_byte
id|__u32
id|i_first_direct_byte
suffix:semicolon
singleline_comment|// offset of first byte stored in direct item.
multiline_comment|/* copy of persistent inode flags read from sd_attrs. */
DECL|member|i_attrs
id|__u32
id|i_attrs
suffix:semicolon
DECL|member|i_prealloc_block
r_int
id|i_prealloc_block
suffix:semicolon
multiline_comment|/* first unused block of a sequence of unused blocks */
DECL|member|i_prealloc_count
r_int
id|i_prealloc_count
suffix:semicolon
multiline_comment|/* length of that sequence */
DECL|member|i_prealloc_list
r_struct
id|list_head
id|i_prealloc_list
suffix:semicolon
multiline_comment|/* per-transaction list of inodes which&n;                                       * have preallocated blocks */
DECL|member|new_packing_locality
r_int
id|new_packing_locality
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* new_packig_locality is created; new blocks&n;&t;&t;&t;&t;       * for the contents of this directory should be&n;&t;&t;&t;&t;       * displaced */
multiline_comment|/* we use these for fsync or O_SYNC to decide which transaction&n;    ** needs to be committed in order for this inode to be properly&n;    ** flushed */
DECL|member|i_trans_id
r_int
r_int
id|i_trans_id
suffix:semicolon
DECL|member|i_jl
r_struct
id|reiserfs_journal_list
op_star
id|i_jl
suffix:semicolon
DECL|member|i_acl_access
r_struct
id|posix_acl
op_star
id|i_acl_access
suffix:semicolon
DECL|member|i_acl_default
r_struct
id|posix_acl
op_star
id|i_acl_default
suffix:semicolon
DECL|member|xattr_sem
r_struct
id|rw_semaphore
id|xattr_sem
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
