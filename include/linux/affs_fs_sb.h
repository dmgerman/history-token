macro_line|#ifndef _AFFS_FS_SB
DECL|macro|_AFFS_FS_SB
mdefine_line|#define _AFFS_FS_SB
multiline_comment|/*&n; * super-block data in memory&n; *&n; * Block numbers are adjusted for their actual size&n; *&n; */
DECL|struct|affs_bm_info
r_struct
id|affs_bm_info
(brace
DECL|member|bm_key
id|u32
id|bm_key
suffix:semicolon
multiline_comment|/* Disk block number */
DECL|member|bm_free
id|u32
id|bm_free
suffix:semicolon
multiline_comment|/* Free blocks in here */
)brace
suffix:semicolon
DECL|struct|affs_sb_info
r_struct
id|affs_sb_info
(brace
DECL|member|s_partition_size
r_int
id|s_partition_size
suffix:semicolon
multiline_comment|/* Partition size in blocks. */
DECL|member|s_reserved
r_int
id|s_reserved
suffix:semicolon
multiline_comment|/* Number of reserved blocks. */
singleline_comment|//u32 s_blksize;&t;&t;&t;/* Initial device blksize */
DECL|member|s_data_blksize
id|u32
id|s_data_blksize
suffix:semicolon
multiline_comment|/* size of the data block w/o header */
DECL|member|s_root_block
id|u32
id|s_root_block
suffix:semicolon
multiline_comment|/* FFS root block number. */
DECL|member|s_hashsize
r_int
id|s_hashsize
suffix:semicolon
multiline_comment|/* Size of hash table. */
DECL|member|s_flags
r_int
r_int
id|s_flags
suffix:semicolon
multiline_comment|/* See below. */
DECL|member|s_uid
id|uid_t
id|s_uid
suffix:semicolon
multiline_comment|/* uid to override */
DECL|member|s_gid
id|gid_t
id|s_gid
suffix:semicolon
multiline_comment|/* gid to override */
DECL|member|s_mode
id|umode_t
id|s_mode
suffix:semicolon
multiline_comment|/* mode to override */
DECL|member|s_root_bh
r_struct
id|buffer_head
op_star
id|s_root_bh
suffix:semicolon
multiline_comment|/* Cached root block. */
DECL|member|s_bmlock
r_struct
id|semaphore
id|s_bmlock
suffix:semicolon
multiline_comment|/* Protects bitmap access. */
DECL|member|s_bitmap
r_struct
id|affs_bm_info
op_star
id|s_bitmap
suffix:semicolon
multiline_comment|/* Bitmap infos. */
DECL|member|s_bmap_count
id|u32
id|s_bmap_count
suffix:semicolon
multiline_comment|/* # of bitmap blocks. */
DECL|member|s_bmap_bits
id|u32
id|s_bmap_bits
suffix:semicolon
multiline_comment|/* # of bits in one bitmap blocks */
DECL|member|s_last_bmap
id|u32
id|s_last_bmap
suffix:semicolon
DECL|member|s_bmap_bh
r_struct
id|buffer_head
op_star
id|s_bmap_bh
suffix:semicolon
DECL|member|s_prefix
r_char
op_star
id|s_prefix
suffix:semicolon
multiline_comment|/* Prefix for volumes and assigns. */
DECL|member|s_prefix_len
r_int
id|s_prefix_len
suffix:semicolon
multiline_comment|/* Length of prefix. */
DECL|member|s_volume
r_char
id|s_volume
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Volume prefix for absolute symlinks. */
)brace
suffix:semicolon
DECL|macro|SF_INTL
mdefine_line|#define SF_INTL&t;&t;0x0001&t;&t;/* International filesystem. */
DECL|macro|SF_BM_VALID
mdefine_line|#define SF_BM_VALID&t;0x0002&t;&t;/* Bitmap is valid. */
DECL|macro|SF_IMMUTABLE
mdefine_line|#define SF_IMMUTABLE&t;0x0004&t;&t;/* Protection bits cannot be changed */
DECL|macro|SF_QUIET
mdefine_line|#define SF_QUIET&t;0x0008&t;&t;/* chmod errors will be not reported */
DECL|macro|SF_SETUID
mdefine_line|#define SF_SETUID&t;0x0010&t;&t;/* Ignore Amiga uid */
DECL|macro|SF_SETGID
mdefine_line|#define SF_SETGID&t;0x0020&t;&t;/* Ignore Amiga gid */
DECL|macro|SF_SETMODE
mdefine_line|#define SF_SETMODE&t;0x0040&t;&t;/* Ignore Amiga protection bits */
DECL|macro|SF_MUFS
mdefine_line|#define SF_MUFS&t;&t;0x0100&t;&t;/* Use MUFS uid/gid mapping */
DECL|macro|SF_OFS
mdefine_line|#define SF_OFS&t;&t;0x0200&t;&t;/* Old filesystem */
DECL|macro|SF_PREFIX
mdefine_line|#define SF_PREFIX&t;0x0400&t;&t;/* Buffer for prefix is allocated */
DECL|macro|SF_VERBOSE
mdefine_line|#define SF_VERBOSE&t;0x0800&t;&t;/* Talk about fs when mounting */
DECL|macro|SF_READONLY
mdefine_line|#define SF_READONLY&t;0x1000&t;&t;/* Don&squot;t allow to remount rw */
multiline_comment|/* short cut to get to the affs specific sb data */
DECL|function|AFFS_SB
r_static
r_inline
r_struct
id|affs_sb_info
op_star
id|AFFS_SB
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
macro_line|#endif
eof
