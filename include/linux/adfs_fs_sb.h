multiline_comment|/*&n; *  linux/include/linux/adfs_fs_sb.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; */
macro_line|#ifndef _ADFS_FS_SB
DECL|macro|_ADFS_FS_SB
mdefine_line|#define _ADFS_FS_SB
multiline_comment|/*&n; * Forward-declare this&n; */
r_struct
id|adfs_discmap
suffix:semicolon
r_struct
id|adfs_dir_ops
suffix:semicolon
multiline_comment|/*&n; * ADFS file system superblock data in memory&n; */
DECL|struct|adfs_sb_info
r_struct
id|adfs_sb_info
(brace
DECL|member|s_map
r_struct
id|adfs_discmap
op_star
id|s_map
suffix:semicolon
multiline_comment|/* bh list containing map&t;&t; */
DECL|member|s_dir
r_struct
id|adfs_dir_ops
op_star
id|s_dir
suffix:semicolon
multiline_comment|/* directory operations&t;&t;&t; */
DECL|member|s_uid
id|uid_t
id|s_uid
suffix:semicolon
multiline_comment|/* owner uid&t;&t;&t;&t; */
DECL|member|s_gid
id|gid_t
id|s_gid
suffix:semicolon
multiline_comment|/* owner gid&t;&t;&t;&t; */
DECL|member|s_owner_mask
id|umode_t
id|s_owner_mask
suffix:semicolon
multiline_comment|/* ADFS owner perm -&gt; unix perm&t;&t; */
DECL|member|s_other_mask
id|umode_t
id|s_other_mask
suffix:semicolon
multiline_comment|/* ADFS other perm -&gt; unix perm&t;&t; */
DECL|member|s_ids_per_zone
id|__u32
id|s_ids_per_zone
suffix:semicolon
multiline_comment|/* max. no ids in one zone&t;&t; */
DECL|member|s_idlen
id|__u32
id|s_idlen
suffix:semicolon
multiline_comment|/* length of ID in map&t;&t;&t; */
DECL|member|s_map_size
id|__u32
id|s_map_size
suffix:semicolon
multiline_comment|/* sector size of a map&t;&t;&t; */
DECL|member|s_size
r_int
r_int
id|s_size
suffix:semicolon
multiline_comment|/* total size (in blocks) of this fs&t; */
DECL|member|s_map2blk
r_int
r_int
id|s_map2blk
suffix:semicolon
multiline_comment|/* shift left by this for map-&gt;sector&t; */
DECL|member|s_log2sharesize
r_int
r_int
id|s_log2sharesize
suffix:semicolon
multiline_comment|/* log2 share size&t;&t;&t; */
DECL|member|s_version
r_int
r_int
id|s_version
suffix:semicolon
multiline_comment|/* disc format version&t;&t;&t; */
DECL|member|s_namelen
r_int
r_int
id|s_namelen
suffix:semicolon
multiline_comment|/* maximum number of characters in name&t; */
)brace
suffix:semicolon
macro_line|#endif
eof
