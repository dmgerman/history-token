multiline_comment|/*&n; *  Name                         : qnx4_fs.h&n; *  Author                       : Richard Frowijn&n; *  Function                     : qnx4 global filesystem definitions&n; *  Version                      : 1.0.2&n; *  Last modified                : 2000-01-31&n; *&n; *  History                      : 23-03-1998 created&n; */
macro_line|#ifndef _LINUX_QNX4_FS_H
DECL|macro|_LINUX_QNX4_FS_H
mdefine_line|#define _LINUX_QNX4_FS_H
macro_line|#include &lt;linux/qnxtypes.h&gt;
DECL|macro|QNX4_ROOT_INO
mdefine_line|#define QNX4_ROOT_INO 1
DECL|macro|QNX4_MAX_XTNTS_PER_XBLK
mdefine_line|#define QNX4_MAX_XTNTS_PER_XBLK&t;60
multiline_comment|/* for di_status */
DECL|macro|QNX4_FILE_USED
mdefine_line|#define QNX4_FILE_USED          0x01
DECL|macro|QNX4_FILE_MODIFIED
mdefine_line|#define QNX4_FILE_MODIFIED      0x02
DECL|macro|QNX4_FILE_BUSY
mdefine_line|#define QNX4_FILE_BUSY          0x04
DECL|macro|QNX4_FILE_LINK
mdefine_line|#define QNX4_FILE_LINK          0x08
DECL|macro|QNX4_FILE_INODE
mdefine_line|#define QNX4_FILE_INODE         0x10
DECL|macro|QNX4_FILE_FSYSCLEAN
mdefine_line|#define QNX4_FILE_FSYSCLEAN     0x20
DECL|macro|QNX4_I_MAP_SLOTS
mdefine_line|#define QNX4_I_MAP_SLOTS&t;8
DECL|macro|QNX4_Z_MAP_SLOTS
mdefine_line|#define QNX4_Z_MAP_SLOTS&t;64
DECL|macro|QNX4_SUPER_MAGIC
mdefine_line|#define QNX4_SUPER_MAGIC&t;0x002f&t;/* qnx4 fs detection */
DECL|macro|QNX4_VALID_FS
mdefine_line|#define QNX4_VALID_FS&t;&t;0x0001&t;/* Clean fs. */
DECL|macro|QNX4_ERROR_FS
mdefine_line|#define QNX4_ERROR_FS&t;&t;0x0002&t;/* fs has errors. */
DECL|macro|QNX4_BLOCK_SIZE
mdefine_line|#define QNX4_BLOCK_SIZE         0x200&t;/* blocksize of 512 bytes */
DECL|macro|QNX4_BLOCK_SIZE_BITS
mdefine_line|#define QNX4_BLOCK_SIZE_BITS    9&t;/* blocksize shift */
DECL|macro|QNX4_DIR_ENTRY_SIZE
mdefine_line|#define QNX4_DIR_ENTRY_SIZE     0x040&t;/* dir entry size of 64 bytes */
DECL|macro|QNX4_DIR_ENTRY_SIZE_BITS
mdefine_line|#define QNX4_DIR_ENTRY_SIZE_BITS 6&t;/* dir entry size shift */
DECL|macro|QNX4_XBLK_ENTRY_SIZE
mdefine_line|#define QNX4_XBLK_ENTRY_SIZE    0x200&t;/* xblk entry size */
DECL|macro|QNX4_INODES_PER_BLOCK
mdefine_line|#define QNX4_INODES_PER_BLOCK   0x08&t;/* 512 / 64 */
multiline_comment|/* for filenames */
DECL|macro|QNX4_SHORT_NAME_MAX
mdefine_line|#define QNX4_SHORT_NAME_MAX&t;16
DECL|macro|QNX4_NAME_MAX
mdefine_line|#define QNX4_NAME_MAX&t;&t;48
multiline_comment|/*&n; * This is the original qnx4 inode layout on disk.&n; */
DECL|struct|qnx4_inode_entry
r_struct
id|qnx4_inode_entry
(brace
DECL|member|di_fname
r_char
id|di_fname
(braket
id|QNX4_SHORT_NAME_MAX
)braket
suffix:semicolon
DECL|member|di_size
id|qnx4_off_t
id|di_size
suffix:semicolon
DECL|member|di_first_xtnt
id|qnx4_xtnt_t
id|di_first_xtnt
suffix:semicolon
DECL|member|di_xblk
id|__u32
id|di_xblk
suffix:semicolon
DECL|member|di_ftime
id|__s32
id|di_ftime
suffix:semicolon
DECL|member|di_mtime
id|__s32
id|di_mtime
suffix:semicolon
DECL|member|di_atime
id|__s32
id|di_atime
suffix:semicolon
DECL|member|di_ctime
id|__s32
id|di_ctime
suffix:semicolon
DECL|member|di_num_xtnts
id|qnx4_nxtnt_t
id|di_num_xtnts
suffix:semicolon
DECL|member|di_mode
id|qnx4_mode_t
id|di_mode
suffix:semicolon
DECL|member|di_uid
id|qnx4_muid_t
id|di_uid
suffix:semicolon
DECL|member|di_gid
id|qnx4_mgid_t
id|di_gid
suffix:semicolon
DECL|member|di_nlink
id|qnx4_nlink_t
id|di_nlink
suffix:semicolon
DECL|member|di_zero
id|__u8
id|di_zero
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|di_type
id|qnx4_ftype_t
id|di_type
suffix:semicolon
DECL|member|di_status
id|__u8
id|di_status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qnx4_link_info
r_struct
id|qnx4_link_info
(brace
DECL|member|dl_fname
r_char
id|dl_fname
(braket
id|QNX4_NAME_MAX
)braket
suffix:semicolon
DECL|member|dl_inode_blk
id|__u32
id|dl_inode_blk
suffix:semicolon
DECL|member|dl_inode_ndx
id|__u8
id|dl_inode_ndx
suffix:semicolon
DECL|member|dl_spare
id|__u8
id|dl_spare
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|dl_status
id|__u8
id|dl_status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qnx4_xblk
r_struct
id|qnx4_xblk
(brace
DECL|member|xblk_next_xblk
id|__u32
id|xblk_next_xblk
suffix:semicolon
DECL|member|xblk_prev_xblk
id|__u32
id|xblk_prev_xblk
suffix:semicolon
DECL|member|xblk_num_xtnts
id|__u8
id|xblk_num_xtnts
suffix:semicolon
DECL|member|xblk_spare
id|__u8
id|xblk_spare
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|xblk_num_blocks
id|__s32
id|xblk_num_blocks
suffix:semicolon
DECL|member|xblk_xtnts
id|qnx4_xtnt_t
id|xblk_xtnts
(braket
id|QNX4_MAX_XTNTS_PER_XBLK
)braket
suffix:semicolon
DECL|member|xblk_signature
r_char
id|xblk_signature
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|xblk_first_xtnt
id|qnx4_xtnt_t
id|xblk_first_xtnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qnx4_super_block
r_struct
id|qnx4_super_block
(brace
DECL|member|RootDir
r_struct
id|qnx4_inode_entry
id|RootDir
suffix:semicolon
DECL|member|Inode
r_struct
id|qnx4_inode_entry
id|Inode
suffix:semicolon
DECL|member|Boot
r_struct
id|qnx4_inode_entry
id|Boot
suffix:semicolon
DECL|member|AltBoot
r_struct
id|qnx4_inode_entry
id|AltBoot
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|QNX4_DEBUG
mdefine_line|#define QNX4_DEBUG 0
macro_line|#if QNX4_DEBUG
DECL|macro|QNX4DEBUG
mdefine_line|#define QNX4DEBUG(X) printk X
macro_line|#else
DECL|macro|QNX4DEBUG
mdefine_line|#define QNX4DEBUG(X) (void) 0
macro_line|#endif
DECL|struct|qnx4_sb_info
r_struct
id|qnx4_sb_info
(brace
DECL|member|sb_buf
r_struct
id|buffer_head
op_star
id|sb_buf
suffix:semicolon
multiline_comment|/* superblock buffer */
DECL|member|sb
r_struct
id|qnx4_super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* our superblock */
DECL|member|Version
r_int
r_int
id|Version
suffix:semicolon
multiline_comment|/* may be useful */
DECL|member|BitMap
r_struct
id|qnx4_inode_entry
op_star
id|BitMap
suffix:semicolon
multiline_comment|/* useful */
)brace
suffix:semicolon
DECL|struct|qnx4_inode_info
r_struct
id|qnx4_inode_info
(brace
DECL|member|raw
r_struct
id|qnx4_inode_entry
id|raw
suffix:semicolon
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|qnx4_lookup
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
)paren
suffix:semicolon
r_extern
r_int
r_int
id|qnx4_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|qnx4_block_map
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|iblock
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|qnx4_getblk
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|qnx4_bread
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_create
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
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|qnx4_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|qnx4_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|qnx4_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|qnx4_dir_operations
suffix:semicolon
r_extern
r_int
id|qnx4_is_free
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_set_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
comma
r_int
id|busy
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_create
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|qnx4_truncate
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
id|qnx4_free_inode
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
id|qnx4_unlink
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
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_rmdir
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
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qnx4_sync_inode
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
id|qnx4_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
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
DECL|function|qnx4_sb
r_static
r_inline
r_struct
id|qnx4_sb_info
op_star
id|qnx4_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;u.generic_sbp
suffix:semicolon
)brace
DECL|function|qnx4_i
r_static
r_inline
r_struct
id|qnx4_inode_info
op_star
id|qnx4_i
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
id|qnx4_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|qnx4_raw_inode
r_static
r_inline
r_struct
id|qnx4_inode_entry
op_star
id|qnx4_raw_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
op_amp
id|qnx4_i
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|raw
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif
eof
