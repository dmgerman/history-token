multiline_comment|/*&n; *&t;Definitions of structures for vfsv0 quota format&n; */
macro_line|#ifndef _LINUX_QUOTAIO_V2_H
DECL|macro|_LINUX_QUOTAIO_V2_H
mdefine_line|#define _LINUX_QUOTAIO_V2_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/quota.h&gt;
multiline_comment|/*&n; * Definitions of magics and versions of current quota files&n; */
DECL|macro|V2_INITQMAGICS
mdefine_line|#define V2_INITQMAGICS {&bslash;&n;&t;0xd9c01f11,&t;/* USRQUOTA */&bslash;&n;&t;0xd9c01927&t;/* GRPQUOTA */&bslash;&n;}
DECL|macro|V2_INITQVERSIONS
mdefine_line|#define V2_INITQVERSIONS {&bslash;&n;&t;0,&t;&t;/* USRQUOTA */&bslash;&n;&t;0&t;&t;/* GRPQUOTA */&bslash;&n;}
multiline_comment|/*&n; * The following structure defines the format of the disk quota file&n; * (as it appears on disk) - the file is a radix tree whose leaves point&n; * to blocks of these structures.&n; */
DECL|struct|v2_disk_dqblk
r_struct
id|v2_disk_dqblk
(brace
DECL|member|dqb_id
id|__u32
id|dqb_id
suffix:semicolon
multiline_comment|/* id this quota applies to */
DECL|member|dqb_ihardlimit
id|__u32
id|dqb_ihardlimit
suffix:semicolon
multiline_comment|/* absolute limit on allocated inodes */
DECL|member|dqb_isoftlimit
id|__u32
id|dqb_isoftlimit
suffix:semicolon
multiline_comment|/* preferred inode limit */
DECL|member|dqb_curinodes
id|__u32
id|dqb_curinodes
suffix:semicolon
multiline_comment|/* current # allocated inodes */
DECL|member|dqb_bhardlimit
id|__u32
id|dqb_bhardlimit
suffix:semicolon
multiline_comment|/* absolute limit on disk space (in QUOTABLOCK_SIZE) */
DECL|member|dqb_bsoftlimit
id|__u32
id|dqb_bsoftlimit
suffix:semicolon
multiline_comment|/* preferred limit on disk space (in QUOTABLOCK_SIZE) */
DECL|member|dqb_curspace
id|__u64
id|dqb_curspace
suffix:semicolon
multiline_comment|/* current space occupied (in bytes) */
DECL|member|dqb_btime
id|__u64
id|dqb_btime
suffix:semicolon
multiline_comment|/* time limit for excessive disk use */
DECL|member|dqb_itime
id|__u64
id|dqb_itime
suffix:semicolon
multiline_comment|/* time limit for excessive inode use */
)brace
suffix:semicolon
multiline_comment|/*&n; * Here are header structures as written on disk and their in-memory copies&n; */
multiline_comment|/* First generic header */
DECL|struct|v2_disk_dqheader
r_struct
id|v2_disk_dqheader
(brace
DECL|member|dqh_magic
id|__u32
id|dqh_magic
suffix:semicolon
multiline_comment|/* Magic number identifying file */
DECL|member|dqh_version
id|__u32
id|dqh_version
suffix:semicolon
multiline_comment|/* File version */
)brace
suffix:semicolon
multiline_comment|/* Header with type and version specific information */
DECL|struct|v2_disk_dqinfo
r_struct
id|v2_disk_dqinfo
(brace
DECL|member|dqi_bgrace
id|__u32
id|dqi_bgrace
suffix:semicolon
multiline_comment|/* Time before block soft limit becomes hard limit */
DECL|member|dqi_igrace
id|__u32
id|dqi_igrace
suffix:semicolon
multiline_comment|/* Time before inode soft limit becomes hard limit */
DECL|member|dqi_flags
id|__u32
id|dqi_flags
suffix:semicolon
multiline_comment|/* Flags for quotafile (DQF_*) */
DECL|member|dqi_blocks
id|__u32
id|dqi_blocks
suffix:semicolon
multiline_comment|/* Number of blocks in file */
DECL|member|dqi_free_blk
id|__u32
id|dqi_free_blk
suffix:semicolon
multiline_comment|/* Number of first free block in the list */
DECL|member|dqi_free_entry
id|__u32
id|dqi_free_entry
suffix:semicolon
multiline_comment|/* Number of block with at least one free entry */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Structure of header of block with quota structures. It is padded to 16 bytes so&n; *  there will be space for exactly 18 quota-entries in a block&n; */
DECL|struct|v2_disk_dqdbheader
r_struct
id|v2_disk_dqdbheader
(brace
DECL|member|dqdh_next_free
id|__u32
id|dqdh_next_free
suffix:semicolon
multiline_comment|/* Number of next block with free entry */
DECL|member|dqdh_prev_free
id|__u32
id|dqdh_prev_free
suffix:semicolon
multiline_comment|/* Number of previous block with free entry */
DECL|member|dqdh_entries
id|__u16
id|dqdh_entries
suffix:semicolon
multiline_comment|/* Number of valid entries in block */
DECL|member|dqdh_pad1
id|__u16
id|dqdh_pad1
suffix:semicolon
DECL|member|dqdh_pad2
id|__u32
id|dqdh_pad2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|V2_DQINFOOFF
mdefine_line|#define V2_DQINFOOFF&t;sizeof(struct v2_disk_dqheader)&t;/* Offset of info header in file */
DECL|macro|V2_DQBLKSIZE_BITS
mdefine_line|#define V2_DQBLKSIZE_BITS&t;10
DECL|macro|V2_DQBLKSIZE
mdefine_line|#define V2_DQBLKSIZE&t;(1 &lt;&lt; V2_DQBLKSIZE_BITS)&t;/* Size of block with quota structures */
DECL|macro|V2_DQTREEOFF
mdefine_line|#define V2_DQTREEOFF&t;1&t;&t;/* Offset of tree in file in blocks */
DECL|macro|V2_DQTREEDEPTH
mdefine_line|#define V2_DQTREEDEPTH&t;4&t;&t;/* Depth of quota tree */
DECL|macro|V2_DQSTRINBLK
mdefine_line|#define V2_DQSTRINBLK&t;((V2_DQBLKSIZE - sizeof(struct v2_disk_dqdbheader)) / sizeof(struct v2_disk_dqblk))&t;/* Number of entries in one blocks */
macro_line|#endif /* _LINUX_QUOTAIO_V2_H */
eof
