macro_line|#ifndef _LINUX_MINIX_FS_H
DECL|macro|_LINUX_MINIX_FS_H
mdefine_line|#define _LINUX_MINIX_FS_H
multiline_comment|/*&n; * The minix filesystem constants/structures&n; */
multiline_comment|/*&n; * Thanks to Kees J Bot for sending me the definitions of the new&n; * minix filesystem (aka V2) with bigger inodes and 32-bit block&n; * pointers.&n; */
DECL|macro|MINIX_ROOT_INO
mdefine_line|#define MINIX_ROOT_INO 1
multiline_comment|/* Not the same as the bogus LINK_MAX in &lt;linux/limits.h&gt;. Oh well. */
DECL|macro|MINIX_LINK_MAX
mdefine_line|#define MINIX_LINK_MAX&t;250
DECL|macro|MINIX2_LINK_MAX
mdefine_line|#define MINIX2_LINK_MAX&t;65530
DECL|macro|MINIX_I_MAP_SLOTS
mdefine_line|#define MINIX_I_MAP_SLOTS&t;8
DECL|macro|MINIX_Z_MAP_SLOTS
mdefine_line|#define MINIX_Z_MAP_SLOTS&t;64
DECL|macro|MINIX_SUPER_MAGIC
mdefine_line|#define MINIX_SUPER_MAGIC&t;0x137F&t;&t;/* original minix fs */
DECL|macro|MINIX_SUPER_MAGIC2
mdefine_line|#define MINIX_SUPER_MAGIC2&t;0x138F&t;&t;/* minix fs, 30 char names */
DECL|macro|MINIX2_SUPER_MAGIC
mdefine_line|#define MINIX2_SUPER_MAGIC&t;0x2468&t;&t;/* minix V2 fs */
DECL|macro|MINIX2_SUPER_MAGIC2
mdefine_line|#define MINIX2_SUPER_MAGIC2&t;0x2478&t;&t;/* minix V2 fs, 30 char names */
DECL|macro|MINIX_VALID_FS
mdefine_line|#define MINIX_VALID_FS&t;&t;0x0001&t;&t;/* Clean fs. */
DECL|macro|MINIX_ERROR_FS
mdefine_line|#define MINIX_ERROR_FS&t;&t;0x0002&t;&t;/* fs has errors. */
DECL|macro|MINIX_INODES_PER_BLOCK
mdefine_line|#define MINIX_INODES_PER_BLOCK ((BLOCK_SIZE)/(sizeof (struct minix_inode)))
DECL|macro|MINIX2_INODES_PER_BLOCK
mdefine_line|#define MINIX2_INODES_PER_BLOCK ((BLOCK_SIZE)/(sizeof (struct minix2_inode)))
multiline_comment|/*&n; * This is the original minix inode layout on disk.&n; * Note the 8-bit gid and atime and ctime.&n; */
DECL|struct|minix_inode
r_struct
id|minix_inode
(brace
DECL|member|i_mode
id|__u16
id|i_mode
suffix:semicolon
DECL|member|i_uid
id|__u16
id|i_uid
suffix:semicolon
DECL|member|i_size
id|__u32
id|i_size
suffix:semicolon
DECL|member|i_time
id|__u32
id|i_time
suffix:semicolon
DECL|member|i_gid
id|__u8
id|i_gid
suffix:semicolon
DECL|member|i_nlinks
id|__u8
id|i_nlinks
suffix:semicolon
DECL|member|i_zone
id|__u16
id|i_zone
(braket
l_int|9
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The new minix inode has all the time entries, as well as&n; * long block numbers and a third indirect block (7+1+1+1&n; * instead of 7+1+1). Also, some previously 8-bit values are&n; * now 16-bit. The inode is now 64 bytes instead of 32.&n; */
DECL|struct|minix2_inode
r_struct
id|minix2_inode
(brace
DECL|member|i_mode
id|__u16
id|i_mode
suffix:semicolon
DECL|member|i_nlinks
id|__u16
id|i_nlinks
suffix:semicolon
DECL|member|i_uid
id|__u16
id|i_uid
suffix:semicolon
DECL|member|i_gid
id|__u16
id|i_gid
suffix:semicolon
DECL|member|i_size
id|__u32
id|i_size
suffix:semicolon
DECL|member|i_atime
id|__u32
id|i_atime
suffix:semicolon
DECL|member|i_mtime
id|__u32
id|i_mtime
suffix:semicolon
DECL|member|i_ctime
id|__u32
id|i_ctime
suffix:semicolon
DECL|member|i_zone
id|__u32
id|i_zone
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * minix super-block data on disk&n; */
DECL|struct|minix_super_block
r_struct
id|minix_super_block
(brace
DECL|member|s_ninodes
id|__u16
id|s_ninodes
suffix:semicolon
DECL|member|s_nzones
id|__u16
id|s_nzones
suffix:semicolon
DECL|member|s_imap_blocks
id|__u16
id|s_imap_blocks
suffix:semicolon
DECL|member|s_zmap_blocks
id|__u16
id|s_zmap_blocks
suffix:semicolon
DECL|member|s_firstdatazone
id|__u16
id|s_firstdatazone
suffix:semicolon
DECL|member|s_log_zone_size
id|__u16
id|s_log_zone_size
suffix:semicolon
DECL|member|s_max_size
id|__u32
id|s_max_size
suffix:semicolon
DECL|member|s_magic
id|__u16
id|s_magic
suffix:semicolon
DECL|member|s_state
id|__u16
id|s_state
suffix:semicolon
DECL|member|s_zones
id|__u32
id|s_zones
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|minix_dir_entry
r_struct
id|minix_dir_entry
(brace
DECL|member|inode
id|__u16
id|inode
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
