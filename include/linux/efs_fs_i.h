multiline_comment|/*&n; * efs_fs_i.h&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from IRIX header files (c) 1988 Silicon Graphics&n; */
macro_line|#ifndef&t;__EFS_FS_I_H__
DECL|macro|__EFS_FS_I_H__
mdefine_line|#define&t;__EFS_FS_I_H__
DECL|typedef|efs_block_t
r_typedef
r_int32
id|efs_block_t
suffix:semicolon
DECL|typedef|efs_ino_t
r_typedef
r_uint32
id|efs_ino_t
suffix:semicolon
DECL|macro|EFS_DIRECTEXTENTS
mdefine_line|#define&t;EFS_DIRECTEXTENTS&t;12
multiline_comment|/*&n; * layout of an extent, in memory and on disk. 8 bytes exactly.&n; */
DECL|union|extent_u
r_typedef
r_union
id|extent_u
(brace
DECL|member|raw
r_int
r_char
id|raw
(braket
l_int|8
)braket
suffix:semicolon
DECL|struct|extent_s
r_struct
id|extent_s
(brace
DECL|member|ex_magic
r_int
r_int
id|ex_magic
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* magic # (zero) */
DECL|member|ex_bn
r_int
r_int
id|ex_bn
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* basic block */
DECL|member|ex_length
r_int
r_int
id|ex_length
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* numblocks in this extent */
DECL|member|ex_offset
r_int
r_int
id|ex_offset
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* logical offset into file */
DECL|member|cooked
)brace
id|cooked
suffix:semicolon
DECL|typedef|efs_extent
)brace
id|efs_extent
suffix:semicolon
DECL|struct|edevs
r_typedef
r_struct
id|edevs
(brace
DECL|member|odev
r_int
id|odev
suffix:semicolon
DECL|member|ndev
r_int
r_int
id|ndev
suffix:semicolon
DECL|typedef|efs_devs
)brace
id|efs_devs
suffix:semicolon
multiline_comment|/*&n; * extent based filesystem inode as it appears on disk.  The efs inode&n; * is exactly 128 bytes long.&n; */
DECL|struct|efs_dinode
r_struct
id|efs_dinode
(brace
DECL|member|di_mode
id|u_short
id|di_mode
suffix:semicolon
multiline_comment|/* mode and type of file */
DECL|member|di_nlink
r_int
id|di_nlink
suffix:semicolon
multiline_comment|/* number of links to file */
DECL|member|di_uid
id|u_short
id|di_uid
suffix:semicolon
multiline_comment|/* owner&squot;s user id */
DECL|member|di_gid
id|u_short
id|di_gid
suffix:semicolon
multiline_comment|/* owner&squot;s group id */
DECL|member|di_size
r_int32
id|di_size
suffix:semicolon
multiline_comment|/* number of bytes in file */
DECL|member|di_atime
r_int32
id|di_atime
suffix:semicolon
multiline_comment|/* time last accessed */
DECL|member|di_mtime
r_int32
id|di_mtime
suffix:semicolon
multiline_comment|/* time last modified */
DECL|member|di_ctime
r_int32
id|di_ctime
suffix:semicolon
multiline_comment|/* time created */
DECL|member|di_gen
r_uint32
id|di_gen
suffix:semicolon
multiline_comment|/* generation number */
DECL|member|di_numextents
r_int
id|di_numextents
suffix:semicolon
multiline_comment|/* # of extents */
DECL|member|di_version
id|u_char
id|di_version
suffix:semicolon
multiline_comment|/* version of inode */
DECL|member|di_spare
id|u_char
id|di_spare
suffix:semicolon
multiline_comment|/* spare - used by AFS */
DECL|union|di_addr
r_union
id|di_addr
(brace
DECL|member|di_extents
id|efs_extent
id|di_extents
(braket
id|EFS_DIRECTEXTENTS
)braket
suffix:semicolon
DECL|member|di_dev
id|efs_devs
id|di_dev
suffix:semicolon
multiline_comment|/* device for IFCHR/IFBLK */
DECL|member|di_u
)brace
id|di_u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* efs inode storage in memory */
DECL|struct|efs_inode_info
r_struct
id|efs_inode_info
(brace
DECL|member|numextents
r_int
id|numextents
suffix:semicolon
DECL|member|lastextent
r_int
id|lastextent
suffix:semicolon
DECL|member|extents
id|efs_extent
id|extents
(braket
id|EFS_DIRECTEXTENTS
)braket
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __EFS_FS_I_H__ */
eof
