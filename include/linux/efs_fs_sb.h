multiline_comment|/*&n; * efs_fs_sb.h&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from IRIX header files (c) 1988 Silicon Graphics&n; */
macro_line|#ifndef __EFS_FS_SB_H__
DECL|macro|__EFS_FS_SB_H__
mdefine_line|#define __EFS_FS_SB_H__
multiline_comment|/* statfs() magic number for EFS */
DECL|macro|EFS_SUPER_MAGIC
mdefine_line|#define EFS_SUPER_MAGIC&t;0x414A53
multiline_comment|/* EFS superblock magic numbers */
DECL|macro|EFS_MAGIC
mdefine_line|#define EFS_MAGIC&t;0x072959
DECL|macro|EFS_NEWMAGIC
mdefine_line|#define EFS_NEWMAGIC&t;0x07295a
DECL|macro|IS_EFS_MAGIC
mdefine_line|#define IS_EFS_MAGIC(x)&t;((x == EFS_MAGIC) || (x == EFS_NEWMAGIC))
DECL|macro|EFS_SUPER
mdefine_line|#define EFS_SUPER&t;&t;1
DECL|macro|EFS_ROOTINODE
mdefine_line|#define EFS_ROOTINODE&t;&t;2
multiline_comment|/* efs superblock on disk */
DECL|struct|efs_super
r_struct
id|efs_super
(brace
DECL|member|fs_size
r_int32
id|fs_size
suffix:semicolon
multiline_comment|/* size of filesystem, in sectors */
DECL|member|fs_firstcg
r_int32
id|fs_firstcg
suffix:semicolon
multiline_comment|/* bb offset to first cg */
DECL|member|fs_cgfsize
r_int32
id|fs_cgfsize
suffix:semicolon
multiline_comment|/* size of cylinder group in bb&squot;s */
DECL|member|fs_cgisize
r_int
id|fs_cgisize
suffix:semicolon
multiline_comment|/* bb&squot;s of inodes per cylinder group */
DECL|member|fs_sectors
r_int
id|fs_sectors
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|fs_heads
r_int
id|fs_heads
suffix:semicolon
multiline_comment|/* heads per cylinder */
DECL|member|fs_ncg
r_int
id|fs_ncg
suffix:semicolon
multiline_comment|/* # of cylinder groups in filesystem */
DECL|member|fs_dirty
r_int
id|fs_dirty
suffix:semicolon
multiline_comment|/* fs needs to be fsck&squot;d */
DECL|member|fs_time
r_int32
id|fs_time
suffix:semicolon
multiline_comment|/* last super-block update */
DECL|member|fs_magic
r_int32
id|fs_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|fs_fname
r_char
id|fs_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system name */
DECL|member|fs_fpack
r_char
id|fs_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* file system pack name */
DECL|member|fs_bmsize
r_int32
id|fs_bmsize
suffix:semicolon
multiline_comment|/* size of bitmap in bytes */
DECL|member|fs_tfree
r_int32
id|fs_tfree
suffix:semicolon
multiline_comment|/* total free data blocks */
DECL|member|fs_tinode
r_int32
id|fs_tinode
suffix:semicolon
multiline_comment|/* total free inodes */
DECL|member|fs_bmblock
r_int32
id|fs_bmblock
suffix:semicolon
multiline_comment|/* bitmap location. */
DECL|member|fs_replsb
r_int32
id|fs_replsb
suffix:semicolon
multiline_comment|/* Location of replicated superblock. */
DECL|member|fs_lastialloc
r_int32
id|fs_lastialloc
suffix:semicolon
multiline_comment|/* last allocated inode */
DECL|member|fs_spare
r_char
id|fs_spare
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* space for expansion - MUST BE ZERO */
DECL|member|fs_checksum
r_int32
id|fs_checksum
suffix:semicolon
multiline_comment|/* checksum of volume portion of fs */
)brace
suffix:semicolon
multiline_comment|/* efs superblock information in memory */
DECL|struct|efs_sb_info
r_struct
id|efs_sb_info
(brace
DECL|member|fs_magic
r_int32
id|fs_magic
suffix:semicolon
multiline_comment|/* superblock magic number */
DECL|member|fs_start
r_int32
id|fs_start
suffix:semicolon
multiline_comment|/* first block of filesystem */
DECL|member|first_block
r_int32
id|first_block
suffix:semicolon
multiline_comment|/* first data block in filesystem */
DECL|member|total_blocks
r_int32
id|total_blocks
suffix:semicolon
multiline_comment|/* total number of blocks in filesystem */
DECL|member|group_size
r_int32
id|group_size
suffix:semicolon
multiline_comment|/* # of blocks a group consists of */
DECL|member|data_free
r_int32
id|data_free
suffix:semicolon
multiline_comment|/* # of free data blocks */
DECL|member|inode_free
r_int32
id|inode_free
suffix:semicolon
multiline_comment|/* # of free inodes */
DECL|member|inode_blocks
r_int
id|inode_blocks
suffix:semicolon
multiline_comment|/* # of blocks used for inodes in every grp */
DECL|member|total_groups
r_int
id|total_groups
suffix:semicolon
multiline_comment|/* # of groups */
)brace
suffix:semicolon
macro_line|#endif /* __EFS_FS_SB_H__ */
eof
