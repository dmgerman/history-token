macro_line|#ifndef _AFFS_FS_SB
DECL|macro|_AFFS_FS_SB
mdefine_line|#define _AFFS_FS_SB
multiline_comment|/*&n; * super-block data in memory&n; *&n; * Block numbers are adjusted for their actual size&n; *&n; */
DECL|macro|MAX_ZONES
mdefine_line|#define MAX_ZONES&t;&t;8
DECL|macro|AFFS_DATA_MIN_FREE
mdefine_line|#define AFFS_DATA_MIN_FREE&t;512&t;/* Number of free blocks in zone for data blocks */
DECL|macro|AFFS_HDR_MIN_FREE
mdefine_line|#define AFFS_HDR_MIN_FREE&t;128&t;/* Same for header blocks */
DECL|macro|AFFS_ZONE_SIZE
mdefine_line|#define AFFS_ZONE_SIZE&t;&t;1024&t;/* Blocks per alloc zone, must be multiple of 32 */
DECL|struct|affs_bm_info
r_struct
id|affs_bm_info
(brace
DECL|member|bm_bh
r_struct
id|buffer_head
op_star
id|bm_bh
suffix:semicolon
multiline_comment|/* Buffer head if loaded (bm_count &gt; 0) */
DECL|member|bm_firstblk
id|s32
id|bm_firstblk
suffix:semicolon
multiline_comment|/* Block number of first bit in this map */
DECL|member|bm_key
id|s32
id|bm_key
suffix:semicolon
multiline_comment|/* Disk block number */
DECL|member|bm_count
r_int
id|bm_count
suffix:semicolon
multiline_comment|/* Usage counter */
)brace
suffix:semicolon
DECL|struct|affs_alloc_zone
r_struct
id|affs_alloc_zone
(brace
DECL|member|az_size
r_int
id|az_size
suffix:semicolon
multiline_comment|/* Size of this allocation zone in double words */
DECL|member|az_count
r_int
id|az_count
suffix:semicolon
multiline_comment|/* Number of users */
DECL|member|az_free
r_int
id|az_free
suffix:semicolon
multiline_comment|/* Free blocks in here (no. of bits) */
)brace
suffix:semicolon
DECL|struct|affs_zone
r_struct
id|affs_zone
(brace
DECL|member|z_ino
r_int
r_int
id|z_ino
suffix:semicolon
multiline_comment|/* Associated inode number */
DECL|member|z_bm
r_struct
id|affs_bm_info
op_star
id|z_bm
suffix:semicolon
multiline_comment|/* Zone lies in this bitmap */
DECL|member|z_start
r_int
id|z_start
suffix:semicolon
multiline_comment|/* Index of first word in bitmap */
DECL|member|z_end
r_int
id|z_end
suffix:semicolon
multiline_comment|/* Index of last word in zone + 1 */
DECL|member|z_az_no
r_int
id|z_az_no
suffix:semicolon
multiline_comment|/* Zone number */
DECL|member|z_lru_time
r_int
r_int
id|z_lru_time
suffix:semicolon
multiline_comment|/* Time of last usage */
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
DECL|member|s_blksize
r_int
id|s_blksize
suffix:semicolon
multiline_comment|/* Initial device blksize */
DECL|member|s_root_block
id|s32
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
id|s16
id|s_uid
suffix:semicolon
multiline_comment|/* uid to override */
DECL|member|s_gid
id|s16
id|s_gid
suffix:semicolon
multiline_comment|/* gid to override */
DECL|member|s_mode
id|umode_t
id|s_mode
suffix:semicolon
multiline_comment|/* mode to override */
DECL|member|s_reserved
r_int
id|s_reserved
suffix:semicolon
multiline_comment|/* Number of reserved blocks. */
DECL|member|s_root_bh
r_struct
id|buffer_head
op_star
id|s_root_bh
suffix:semicolon
multiline_comment|/* Cached root block. */
DECL|member|s_bitmap
r_struct
id|affs_bm_info
op_star
id|s_bitmap
suffix:semicolon
multiline_comment|/* Bitmap infos. */
DECL|member|s_bm_count
r_int
id|s_bm_count
suffix:semicolon
multiline_comment|/* Number of bitmap blocks. */
DECL|member|s_nextzone
r_int
id|s_nextzone
suffix:semicolon
multiline_comment|/* Next zone to look for free blocks. */
DECL|member|s_num_az
r_int
id|s_num_az
suffix:semicolon
multiline_comment|/* Total number of alloc zones. */
DECL|member|s_zones
r_struct
id|affs_zone
op_star
id|s_zones
suffix:semicolon
multiline_comment|/* The zones themselves. */
DECL|member|s_alloc
r_struct
id|affs_alloc_zone
op_star
id|s_alloc
suffix:semicolon
multiline_comment|/* The allocation zones. */
DECL|member|s_zonemap
r_char
op_star
id|s_zonemap
suffix:semicolon
multiline_comment|/* Bitmap for allocation zones. */
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
macro_line|#endif
eof
