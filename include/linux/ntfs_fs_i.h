macro_line|#ifndef _LINUX_NTFS_FS_I_H
DECL|macro|_LINUX_NTFS_FS_I_H
mdefine_line|#define _LINUX_NTFS_FS_I_H
multiline_comment|/*&n; * Clusters are signed 64-bit values on NTFS volumes. We define two types, LCN&n; * and VCN, to allow for type checking and better code readability.&n; */
DECL|typedef|VCN
r_typedef
id|__s64
id|VCN
suffix:semicolon
DECL|typedef|LCN
r_typedef
id|__s64
id|LCN
suffix:semicolon
multiline_comment|/**&n; * run_list - in memory vcn to lcn mapping array&n; * @vcn:&t;starting vcn of the current array element&n; * @lcn:&t;starting lcn of the current array element&n; * @length:&t;length in clusters of the current array element&n; * &n; * The last vcn (in fact the last vcn + 1) is reached when length == 0.&n; * &n; * When lcn == -1 this means that the count vcns starting at vcn are not &n; * physically allocated (i.e. this is a hole / data is sparse).&n; */
r_typedef
r_struct
(brace
multiline_comment|/* In memory vcn to lcn mapping structure element. */
DECL|member|vcn
id|VCN
id|vcn
suffix:semicolon
multiline_comment|/* vcn = Starting virtual cluster number. */
DECL|member|lcn
id|LCN
id|lcn
suffix:semicolon
multiline_comment|/* lcn = Starting logical cluster number. */
DECL|member|length
id|__s64
id|length
suffix:semicolon
multiline_comment|/* Run length in clusters. */
DECL|typedef|run_list
)brace
id|run_list
suffix:semicolon
multiline_comment|/*&n; * The NTFS in-memory inode structure. It is just used as an extension to the&n; * fields already provided in the VFS inode.&n; */
DECL|struct|ntfs_inode_info
r_struct
id|ntfs_inode_info
(brace
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* Pointer to the inode structure of this&n;&t;&t;&t;&t;   ntfs_inode_info structure. */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* NTFS specific flags describing this inode.&n;&t;&t;&t;&t;   See fs/ntfs/ntfs.h:ntfs_inode_state_bits. */
DECL|member|run_list
id|run_list
op_star
id|run_list
suffix:semicolon
multiline_comment|/* If state has the NI_NonResident bit set,&n;&t;&t;&t;&t;   the run list of the unnamed data attribute&n;&t;&t;&t;&t;   (if a file) or of the index allocation&n;&t;&t;&t;&t;   attribute (directory). If run_list is NULL,&n;&t;&t;&t;&t;   the run list has not been read in or has&n;&t;&t;&t;&t;   been unmapped. If NI_NonResident is clear,&n;&t;&t;&t;&t;   the unnamed data attribute is resident (file)&n;&t;&t;&t;&t;   or there is no $I30 index allocation&n;&t;&t;&t;&t;   attribute (directory). In that case run_list&n;&t;&t;&t;&t;   is always NULL.*/
DECL|member|nr_extents
id|__s32
id|nr_extents
suffix:semicolon
multiline_comment|/* The number of extents[], if this is a base&n;&t;&t;&t;&t;   mft record, -1 if this is an extent record,&n;&t;&t;&t;&t;   and 0 if there are no extents. */
DECL|member|mrec_lock
r_struct
id|rw_semaphore
id|mrec_lock
suffix:semicolon
multiline_comment|/* Lock for serializing access to the&n;&t;&t;&t;&t;   mft record belonging to this inode. */
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/* The page containing the mft record of the&n;&t;&t;&t;&t;   inode. This should only be touched by the&n;&t;&t;&t;&t;   (un)map_mft_record_for_*() functions. Do NOT&n;&t;&t;&t;&t;   touch from anywhere else or the ntfs divil&n;&t;&t;&t;&t;   will appear and take your heart out with a&n;&t;&t;&t;&t;   blunt spoon! You have been warned. (-8 */
r_union
(brace
r_struct
(brace
multiline_comment|/* It is a directory. */
DECL|member|index_block_size
id|__u32
id|index_block_size
suffix:semicolon
multiline_comment|/* Size of an index block. */
DECL|member|index_block_size_bits
id|__u8
id|index_block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the size of an&n;&t;&t;&t;&t;&t;&t;       an index block. */
DECL|member|bmp_size
id|__s64
id|bmp_size
suffix:semicolon
multiline_comment|/* Size of the $I30 bitmap. */
DECL|member|bmp_rl
id|run_list
op_star
id|bmp_rl
suffix:semicolon
multiline_comment|/* Run list for the $I30 bitmap&n;&t;&t;&t;&t;&t;&t;   if it is non-resident. */
)brace
suffix:semicolon
r_struct
(brace
multiline_comment|/* It is a compressed file. */
DECL|member|compression_block_size
id|__u32
id|compression_block_size
suffix:semicolon
multiline_comment|/* Size of a compression&n;&t;&t;&t;&t;&t;&t;         block (cb). */
DECL|member|compression_block_size_bits
id|__u8
id|compression_block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the size&n;&t;&t;&t;&t;&t;&t;&t;     of a cb. */
DECL|member|compression_block_clusters
id|__u8
id|compression_block_clusters
suffix:semicolon
multiline_comment|/* Number of clusters&n;&t;&t;&t;&t;&t;&t;&t;    per compression&n;&t;&t;&t;&t;&t;&t;&t;    block. */
)brace
suffix:semicolon
)brace
suffix:semicolon
r_union
(brace
multiline_comment|/* This union is only used if nr_extents != 0. */
r_struct
(brace
multiline_comment|/* nr_extents &gt; 0 */
DECL|member|i_ino
id|__s64
id|i_ino
suffix:semicolon
multiline_comment|/* The inode number of the&n;&t;&t;&t;&t;&t;&t;   extent mft record. */
DECL|member|i_generation
id|__u32
id|i_generation
suffix:semicolon
multiline_comment|/* The i_generation of the&n;&t;&t;&t;&t;&t;&t;   extent mft record. */
DECL|member|extents
)brace
op_star
id|extents
suffix:semicolon
multiline_comment|/* The currently known of extents, sorted in&n;&t;&t;&t;&t;   ascending order. */
r_struct
(brace
multiline_comment|/* nr_exents == -1 */
DECL|member|i_ino
id|__s64
id|i_ino
suffix:semicolon
multiline_comment|/* The inode number of the base&n;&t;&t;&t;&t;&t;&t;   mft record of this extent. */
DECL|member|i_generation
id|__u32
id|i_generation
suffix:semicolon
multiline_comment|/* The i_generation of the base&n;&t;&t;&t;&t;&t;&t;   mft record. */
DECL|member|base
)brace
id|base
suffix:semicolon
multiline_comment|/* The base mft record of this extent. */
)brace
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_FS_I_H */
eof
