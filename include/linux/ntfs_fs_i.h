macro_line|#ifndef _LINUX_NTFS_FS_I_H
DECL|macro|_LINUX_NTFS_FS_I_H
mdefine_line|#define _LINUX_NTFS_FS_I_H
multiline_comment|/* Forward declarations, to keep number of mutual includes low */
r_struct
id|ntfs_attribute
suffix:semicolon
r_struct
id|ntfs_sb_info
suffix:semicolon
multiline_comment|/* Duplicate definitions from ntfs/ntfstypes.h */
macro_line|#ifndef NTFS_INTEGRAL_TYPES
DECL|macro|NTFS_INTEGRAL_TYPES
mdefine_line|#define NTFS_INTEGRAL_TYPES
DECL|typedef|ntfs_u8
r_typedef
id|u8
id|ntfs_u8
suffix:semicolon
DECL|typedef|ntfs_u16
r_typedef
id|u16
id|ntfs_u16
suffix:semicolon
DECL|typedef|ntfs_u32
r_typedef
id|u32
id|ntfs_u32
suffix:semicolon
DECL|typedef|ntfs_u64
r_typedef
id|u64
id|ntfs_u64
suffix:semicolon
DECL|typedef|ntfs_s8
r_typedef
id|s8
id|ntfs_s8
suffix:semicolon
DECL|typedef|ntfs_s16
r_typedef
id|s16
id|ntfs_s16
suffix:semicolon
DECL|typedef|ntfs_s32
r_typedef
id|s32
id|ntfs_s32
suffix:semicolon
DECL|typedef|ntfs_s64
r_typedef
id|s64
id|ntfs_s64
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTMODE_T
DECL|macro|NTMODE_T
mdefine_line|#define NTMODE_T
DECL|typedef|ntmode_t
r_typedef
id|__kernel_mode_t
id|ntmode_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_UID_T
DECL|macro|NTFS_UID_T
mdefine_line|#define NTFS_UID_T
DECL|typedef|ntfs_uid_t
r_typedef
id|uid_t
id|ntfs_uid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_GID_T
DECL|macro|NTFS_GID_T
mdefine_line|#define NTFS_GID_T
DECL|typedef|ntfs_gid_t
r_typedef
id|gid_t
id|ntfs_gid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_SIZE_T
DECL|macro|NTFS_SIZE_T
mdefine_line|#define NTFS_SIZE_T
DECL|typedef|ntfs_size_t
r_typedef
id|__kernel_size_t
id|ntfs_size_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_TIME_T
DECL|macro|NTFS_TIME_T
mdefine_line|#define NTFS_TIME_T
DECL|typedef|ntfs_time_t
r_typedef
id|__kernel_time_t
id|ntfs_time_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* unicode character type */
macro_line|#ifndef NTFS_WCHAR_T
DECL|macro|NTFS_WCHAR_T
mdefine_line|#define NTFS_WCHAR_T
DECL|typedef|ntfs_wchar_t
r_typedef
id|u16
id|ntfs_wchar_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* file offset */
macro_line|#ifndef NTFS_OFFSET_T
DECL|macro|NTFS_OFFSET_T
mdefine_line|#define NTFS_OFFSET_T
DECL|typedef|ntfs_offset_t
r_typedef
id|s64
id|ntfs_offset_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* UTC */
macro_line|#ifndef NTFS_TIME64_T
DECL|macro|NTFS_TIME64_T
mdefine_line|#define NTFS_TIME64_T
DECL|typedef|ntfs_time64_t
r_typedef
id|u64
id|ntfs_time64_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * This is really signed long long. So we support only volumes up to 2Tb. This&n; * is ok as Win2k also only uses 32-bits to store clusters.&n; * Whatever you do keep this a SIGNED value or a lot of NTFS users with&n; * corrupted filesystems will lynch you! It causes massive fs corruption when&n; * unsigned due to the nature of many checks relying on being performed on&n; * signed quantities. (AIA)&n; */
macro_line|#ifndef NTFS_CLUSTER_T
DECL|macro|NTFS_CLUSTER_T
mdefine_line|#define NTFS_CLUSTER_T
DECL|typedef|ntfs_cluster_t
r_typedef
id|s32
id|ntfs_cluster_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Definition of the NTFS in-memory inode structure. */
DECL|struct|ntfs_inode_info
r_struct
id|ntfs_inode_info
(brace
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|vol
r_struct
id|ntfs_sb_info
op_star
id|vol
suffix:semicolon
DECL|member|i_number
r_int
r_int
id|i_number
suffix:semicolon
multiline_comment|/* Should be really 48 bits. */
DECL|member|sequence_number
id|__u16
id|sequence_number
suffix:semicolon
multiline_comment|/* The current sequence number. */
DECL|member|attr
r_int
r_char
op_star
id|attr
suffix:semicolon
multiline_comment|/* Array of the attributes. */
DECL|member|attr_count
r_int
id|attr_count
suffix:semicolon
multiline_comment|/* Size of attrs[]. */
DECL|member|attrs
r_struct
id|ntfs_attribute
op_star
id|attrs
suffix:semicolon
DECL|member|record_count
r_int
id|record_count
suffix:semicolon
multiline_comment|/* Size of records[]. */
DECL|member|records
r_int
op_star
id|records
suffix:semicolon
multiline_comment|/* Array of the record numbers of the $Mft whose &n;&t;&t;       * attributes have been inserted in the inode. */
r_union
(brace
r_struct
(brace
DECL|member|recordsize
r_int
id|recordsize
suffix:semicolon
DECL|member|clusters_per_record
r_int
id|clusters_per_record
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
