macro_line|#ifndef _LINUX_NTFS_FS_SB_H
DECL|macro|_LINUX_NTFS_FS_SB_H
mdefine_line|#define _LINUX_NTFS_FS_SB_H
multiline_comment|/* 2-byte Unicode character type. */
DECL|typedef|uchar_t
r_typedef
id|__u16
id|uchar_t
suffix:semicolon
multiline_comment|/*&n; * The NTFS in memory super block structure.&n; */
DECL|struct|ntfs_sb_info
r_struct
id|ntfs_sb_info
(brace
multiline_comment|/*&n;&t; * FIXME: Reorder to have commonly used together element within the&n;&t; * same cache line, aiming at a cache line size of 32 bytes. Aim for&n;&t; * 64 bytes for less commonly used together elements. Put most commonly&n;&t; * used elements to front of structure. Obviously do this only when the&n;&t; * structure has stabilized... (AIA)&n;&t; */
multiline_comment|/* Device specifics. */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* Pointer back to the super_block,&n;&t;&t;&t;&t;&t;   so we don&squot;t have to get the offset&n;&t;&t;&t;&t;&t;   every time. */
DECL|member|nr_blocks
id|LCN
id|nr_blocks
suffix:semicolon
multiline_comment|/* Number of NTFS_BLOCK_SIZE bytes&n;&t;&t;&t;&t;&t;   sized blocks on the device. */
multiline_comment|/* Configuration provided by user at mount time. */
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
multiline_comment|/* uid that files will be mounted as. */
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
multiline_comment|/* gid that files will be mounted as. */
DECL|member|fmask
id|mode_t
id|fmask
suffix:semicolon
multiline_comment|/* The mask for file permissions. */
DECL|member|dmask
id|mode_t
id|dmask
suffix:semicolon
multiline_comment|/* The mask for directory&n;&t;&t;&t;&t;&t;   permissions. */
DECL|member|mft_zone_multiplier
id|__u8
id|mft_zone_multiplier
suffix:semicolon
multiline_comment|/* Initial mft zone multiplier. */
DECL|member|on_errors
id|__u8
id|on_errors
suffix:semicolon
multiline_comment|/* What to do on file system errors. */
multiline_comment|/* NTFS bootsector provided information. */
DECL|member|sector_size
id|__u16
id|sector_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|sector_size_bits
id|__u8
id|sector_size_bits
suffix:semicolon
multiline_comment|/* log2(sector_size) */
DECL|member|cluster_size
id|__u32
id|cluster_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|cluster_size_mask
id|__u32
id|cluster_size_mask
suffix:semicolon
multiline_comment|/* cluster_size - 1 */
DECL|member|cluster_size_bits
id|__u8
id|cluster_size_bits
suffix:semicolon
multiline_comment|/* log2(cluster_size) */
DECL|member|mft_record_size
id|__u32
id|mft_record_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|mft_record_size_mask
id|__u32
id|mft_record_size_mask
suffix:semicolon
multiline_comment|/* mft_record_size - 1 */
DECL|member|mft_record_size_bits
id|__u8
id|mft_record_size_bits
suffix:semicolon
multiline_comment|/* log2(mft_record_size) */
DECL|member|index_record_size
id|__u32
id|index_record_size
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|index_record_size_mask
id|__u32
id|index_record_size_mask
suffix:semicolon
multiline_comment|/* index_record_size - 1 */
DECL|member|index_record_size_bits
id|__u8
id|index_record_size_bits
suffix:semicolon
multiline_comment|/* log2(index_record_size) */
r_union
(brace
DECL|member|nr_clusters
id|LCN
id|nr_clusters
suffix:semicolon
multiline_comment|/* Volume size in clusters. */
DECL|member|nr_lcn_bits
id|LCN
id|nr_lcn_bits
suffix:semicolon
multiline_comment|/* Number of bits in lcn bitmap. */
)brace
suffix:semicolon
DECL|member|mft_lcn
id|LCN
id|mft_lcn
suffix:semicolon
multiline_comment|/* Cluster location of mft data. */
DECL|member|mftmirr_lcn
id|LCN
id|mftmirr_lcn
suffix:semicolon
multiline_comment|/* Cluster location of copy of mft. */
DECL|member|serial_no
id|__u64
id|serial_no
suffix:semicolon
multiline_comment|/* The volume serial number. */
multiline_comment|/* Mount specific NTFS information. */
DECL|member|upcase_len
id|__u32
id|upcase_len
suffix:semicolon
multiline_comment|/* Number of entries in upcase[]. */
DECL|member|upcase
id|uchar_t
op_star
id|upcase
suffix:semicolon
multiline_comment|/* The upcase table. */
DECL|member|mft_zone_start
id|LCN
id|mft_zone_start
suffix:semicolon
multiline_comment|/* First cluster of the mft zone. */
DECL|member|mft_zone_end
id|LCN
id|mft_zone_end
suffix:semicolon
multiline_comment|/* First cluster beyond the mft zone. */
DECL|member|mft_ino
r_struct
id|inode
op_star
id|mft_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $MFT. */
DECL|member|mftbmp_lock
r_struct
id|rw_semaphore
id|mftbmp_lock
suffix:semicolon
multiline_comment|/* Lock for serializing accesses to the&n;&t;&t;&t;&t;&t;    mft record bitmap ($MFT/$BITMAP). */
r_union
(brace
DECL|member|nr_mft_records
id|__s64
id|nr_mft_records
suffix:semicolon
multiline_comment|/* Number of records in the mft. */
DECL|member|nr_mft_bits
id|__s64
id|nr_mft_bits
suffix:semicolon
multiline_comment|/* Number of bits in mft bitmap. */
)brace
suffix:semicolon
DECL|member|mftbmp_mapping
r_struct
id|address_space
id|mftbmp_mapping
suffix:semicolon
multiline_comment|/* Page cache for $MFT/$BITMAP. */
DECL|member|mftbmp_rl
id|run_list
op_star
id|mftbmp_rl
suffix:semicolon
multiline_comment|/* Run list for $MFT/$BITMAP. */
DECL|member|mftmirr_ino
r_struct
id|inode
op_star
id|mftmirr_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $MFTMirr. */
DECL|member|lcnbmp_ino
r_struct
id|inode
op_star
id|lcnbmp_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Bitmap. */
DECL|member|lcnbmp_lock
r_struct
id|rw_semaphore
id|lcnbmp_lock
suffix:semicolon
multiline_comment|/* Lock for serializing accesses to the&n;&t;&t;&t;&t;&t;    cluster bitmap ($Bitmap/$DATA). */
DECL|member|vol_ino
r_struct
id|inode
op_star
id|vol_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Volume. */
DECL|member|vol_flags
r_int
r_int
id|vol_flags
suffix:semicolon
multiline_comment|/* Volume flags (VOLUME_*). */
DECL|member|major_ver
id|__u8
id|major_ver
suffix:semicolon
multiline_comment|/* Ntfs major version of volume. */
DECL|member|minor_ver
id|__u8
id|minor_ver
suffix:semicolon
multiline_comment|/* Ntfs minor version of volume. */
DECL|member|root_ino
r_struct
id|inode
op_star
id|root_ino
suffix:semicolon
multiline_comment|/* The VFS inode of the root&n;&t;&t;&t;&t;&t;   directory. */
DECL|member|secure_ino
r_struct
id|inode
op_star
id|secure_ino
suffix:semicolon
multiline_comment|/* The VFS inode of $Secure (NTFS3.0+&n;&t;&t;&t;&t;&t;   only, otherwise NULL). */
DECL|member|nls_map
r_struct
id|nls_table
op_star
id|nls_map
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_FS_SB_H */
eof
