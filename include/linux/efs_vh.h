multiline_comment|/*&n; * efs_vh.h&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from IRIX header files (c) 1985 MIPS Computer Systems, Inc.&n; */
macro_line|#ifndef __EFS_VH_H__
DECL|macro|__EFS_VH_H__
mdefine_line|#define __EFS_VH_H__
DECL|macro|VHMAGIC
mdefine_line|#define VHMAGIC&t;&t;0xbe5a941&t;/* volume header magic number */
DECL|macro|NPARTAB
mdefine_line|#define NPARTAB&t;&t;16&t;&t;/* 16 unix partitions */
DECL|macro|NVDIR
mdefine_line|#define NVDIR&t;&t;15&t;&t;/* max of 15 directory entries */
DECL|macro|BFNAMESIZE
mdefine_line|#define BFNAMESIZE&t;16&t;&t;/* max 16 chars in boot file name */
DECL|macro|VDNAMESIZE
mdefine_line|#define VDNAMESIZE&t;8
DECL|struct|volume_directory
r_struct
id|volume_directory
(brace
DECL|member|vd_name
r_char
id|vd_name
(braket
id|VDNAMESIZE
)braket
suffix:semicolon
multiline_comment|/* name */
DECL|member|vd_lbn
r_int
id|vd_lbn
suffix:semicolon
multiline_comment|/* logical block number */
DECL|member|vd_nbytes
r_int
id|vd_nbytes
suffix:semicolon
multiline_comment|/* file length in bytes */
)brace
suffix:semicolon
DECL|struct|partition_table
r_struct
id|partition_table
(brace
multiline_comment|/* one per logical partition */
DECL|member|pt_nblks
r_int
id|pt_nblks
suffix:semicolon
multiline_comment|/* # of logical blks in partition */
DECL|member|pt_firstlbn
r_int
id|pt_firstlbn
suffix:semicolon
multiline_comment|/* first lbn of partition */
DECL|member|pt_type
r_int
id|pt_type
suffix:semicolon
multiline_comment|/* use of partition */
)brace
suffix:semicolon
DECL|struct|volume_header
r_struct
id|volume_header
(brace
DECL|member|vh_magic
r_int
id|vh_magic
suffix:semicolon
multiline_comment|/* identifies volume header */
DECL|member|vh_rootpt
r_int
id|vh_rootpt
suffix:semicolon
multiline_comment|/* root partition number */
DECL|member|vh_swappt
r_int
id|vh_swappt
suffix:semicolon
multiline_comment|/* swap partition number */
DECL|member|vh_bootfile
r_char
id|vh_bootfile
(braket
id|BFNAMESIZE
)braket
suffix:semicolon
multiline_comment|/* name of file to boot */
DECL|member|pad
r_char
id|pad
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* device param space */
DECL|member|vh_vd
r_struct
id|volume_directory
id|vh_vd
(braket
id|NVDIR
)braket
suffix:semicolon
multiline_comment|/* other vol hdr contents */
DECL|member|vh_pt
r_struct
id|partition_table
id|vh_pt
(braket
id|NPARTAB
)braket
suffix:semicolon
multiline_comment|/* device partition layout */
DECL|member|vh_csum
r_int
id|vh_csum
suffix:semicolon
multiline_comment|/* volume header checksum */
DECL|member|vh_fill
r_int
id|vh_fill
suffix:semicolon
multiline_comment|/* fill out to 512 bytes */
)brace
suffix:semicolon
multiline_comment|/* partition type sysv is used for EFS format CD-ROM partitions */
DECL|macro|SGI_SYSV
mdefine_line|#define SGI_SYSV&t;0x05
DECL|macro|SGI_EFS
mdefine_line|#define SGI_EFS&t;&t;0x07
DECL|macro|IS_EFS
mdefine_line|#define IS_EFS(x)&t;(((x) == SGI_EFS) || ((x) == SGI_SYSV))
DECL|struct|pt_types
r_struct
id|pt_types
(brace
DECL|member|pt_type
r_int
id|pt_type
suffix:semicolon
DECL|member|pt_name
r_char
op_star
id|pt_name
suffix:semicolon
DECL|variable|sgi_pt_types
)brace
id|sgi_pt_types
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_string|&quot;SGI vh&quot;
)brace
comma
(brace
l_int|0x01
comma
l_string|&quot;SGI trkrepl&quot;
)brace
comma
(brace
l_int|0x02
comma
l_string|&quot;SGI secrepl&quot;
)brace
comma
(brace
l_int|0x03
comma
l_string|&quot;SGI raw&quot;
)brace
comma
(brace
l_int|0x04
comma
l_string|&quot;SGI bsd&quot;
)brace
comma
(brace
id|SGI_SYSV
comma
l_string|&quot;SGI sysv&quot;
)brace
comma
(brace
l_int|0x06
comma
l_string|&quot;SGI vol&quot;
)brace
comma
(brace
id|SGI_EFS
comma
l_string|&quot;SGI efs&quot;
)brace
comma
(brace
l_int|0x08
comma
l_string|&quot;SGI lv&quot;
)brace
comma
(brace
l_int|0x09
comma
l_string|&quot;SGI rlv&quot;
)brace
comma
(brace
l_int|0x0A
comma
l_string|&quot;SGI xfs&quot;
)brace
comma
(brace
l_int|0x0B
comma
l_string|&quot;SGI xfslog&quot;
)brace
comma
(brace
l_int|0x0C
comma
l_string|&quot;SGI xlv&quot;
)brace
comma
(brace
l_int|0x82
comma
l_string|&quot;Linux swap&quot;
)brace
comma
(brace
l_int|0x83
comma
l_string|&quot;Linux native&quot;
)brace
comma
(brace
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
macro_line|#endif /* __EFS_VH_H__ */
eof
