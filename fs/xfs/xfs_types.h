multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_TYPES_H__
DECL|macro|__XFS_TYPES_H__
mdefine_line|#define&t;__XFS_TYPES_H__
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * POSIX Extensions&n; */
DECL|typedef|uchar_t
r_typedef
r_int
r_char
id|uchar_t
suffix:semicolon
DECL|typedef|ushort_t
r_typedef
r_int
r_int
id|ushort_t
suffix:semicolon
DECL|typedef|uint_t
r_typedef
r_int
r_int
id|uint_t
suffix:semicolon
DECL|typedef|ulong_t
r_typedef
r_int
r_int
id|ulong_t
suffix:semicolon
multiline_comment|/*&n; * Additional type declarations for XFS&n; */
DECL|typedef|__int8_t
r_typedef
r_int
r_char
id|__int8_t
suffix:semicolon
DECL|typedef|__uint8_t
r_typedef
r_int
r_char
id|__uint8_t
suffix:semicolon
DECL|typedef|__int16_t
r_typedef
r_int
r_int
r_int
id|__int16_t
suffix:semicolon
DECL|typedef|__uint16_t
r_typedef
r_int
r_int
r_int
id|__uint16_t
suffix:semicolon
DECL|typedef|__int32_t
r_typedef
r_int
r_int
id|__int32_t
suffix:semicolon
DECL|typedef|__uint32_t
r_typedef
r_int
r_int
id|__uint32_t
suffix:semicolon
DECL|typedef|__int64_t
r_typedef
r_int
r_int
r_int
r_int
id|__int64_t
suffix:semicolon
DECL|typedef|__uint64_t
r_typedef
r_int
r_int
r_int
r_int
id|__uint64_t
suffix:semicolon
DECL|enumerator|B_FALSE
DECL|enumerator|B_TRUE
DECL|typedef|boolean_t
r_typedef
r_enum
(brace
id|B_FALSE
comma
id|B_TRUE
)brace
id|boolean_t
suffix:semicolon
DECL|typedef|prid_t
r_typedef
id|__int64_t
id|prid_t
suffix:semicolon
multiline_comment|/* project ID */
DECL|typedef|inst_t
r_typedef
id|__uint32_t
id|inst_t
suffix:semicolon
multiline_comment|/* an instruction */
DECL|typedef|xfs_off_t
r_typedef
id|__u64
id|xfs_off_t
suffix:semicolon
DECL|typedef|xfs_ino_t
r_typedef
id|__u64
id|xfs_ino_t
suffix:semicolon
multiline_comment|/* &lt;inode&gt; type */
DECL|typedef|xfs_daddr_t
r_typedef
id|__s64
id|xfs_daddr_t
suffix:semicolon
multiline_comment|/* &lt;disk address&gt; type */
DECL|typedef|xfs_caddr_t
r_typedef
r_char
op_star
id|xfs_caddr_t
suffix:semicolon
multiline_comment|/* &lt;core address&gt; type */
DECL|typedef|xfs_dev_t
r_typedef
id|__u32
id|xfs_dev_t
suffix:semicolon
multiline_comment|/* __psint_t is the same size as a pointer */
macro_line|#if (BITS_PER_LONG == 32)
DECL|typedef|__psint_t
r_typedef
id|__int32_t
id|__psint_t
suffix:semicolon
DECL|typedef|__psunsigned_t
r_typedef
id|__uint32_t
id|__psunsigned_t
suffix:semicolon
macro_line|#elif (BITS_PER_LONG == 64)
DECL|typedef|__psint_t
r_typedef
id|__int64_t
id|__psint_t
suffix:semicolon
DECL|typedef|__psunsigned_t
r_typedef
id|__uint64_t
id|__psunsigned_t
suffix:semicolon
macro_line|#else
macro_line|#error BITS_PER_LONG must be 32 or 64
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Some types are conditional depending on the target system.&n; * XFS_BIG_BLKNOS needs block layer disk addresses to be 64 bits.&n; * XFS_BIG_INUMS needs the VFS inode number to be 64 bits, as well&n; * as requiring XFS_BIG_BLKNOS to be set.&n; */
macro_line|#if defined(CONFIG_LBD) || (defined(HAVE_SECTOR_T) &amp;&amp; (BITS_PER_LONG == 64))
DECL|macro|XFS_BIG_BLKNOS
macro_line|# define XFS_BIG_BLKNOS&t;1
macro_line|# if BITS_PER_LONG == 64
DECL|macro|XFS_BIG_INUMS
macro_line|#  define XFS_BIG_INUMS&t;1
macro_line|# else
DECL|macro|XFS_BIG_INUMS
macro_line|#  define XFS_BIG_INUMS&t;0
macro_line|# endif
macro_line|#else
DECL|macro|XFS_BIG_BLKNOS
macro_line|# define XFS_BIG_BLKNOS&t;0
DECL|macro|XFS_BIG_INUMS
macro_line|# define XFS_BIG_INUMS&t;0
macro_line|#endif
DECL|typedef|xfs_agblock_t
r_typedef
id|__uint32_t
id|xfs_agblock_t
suffix:semicolon
multiline_comment|/* blockno in alloc. group */
DECL|typedef|xfs_extlen_t
r_typedef
id|__uint32_t
id|xfs_extlen_t
suffix:semicolon
multiline_comment|/* extent length in blocks */
DECL|typedef|xfs_agnumber_t
r_typedef
id|__uint32_t
id|xfs_agnumber_t
suffix:semicolon
multiline_comment|/* allocation group number */
DECL|typedef|xfs_extnum_t
r_typedef
id|__int32_t
id|xfs_extnum_t
suffix:semicolon
multiline_comment|/* # of extents in a file */
DECL|typedef|xfs_aextnum_t
r_typedef
id|__int16_t
id|xfs_aextnum_t
suffix:semicolon
multiline_comment|/* # extents in an attribute fork */
DECL|typedef|xfs_fsize_t
r_typedef
id|__int64_t
id|xfs_fsize_t
suffix:semicolon
multiline_comment|/* bytes in a file */
DECL|typedef|xfs_ufsize_t
r_typedef
id|__uint64_t
id|xfs_ufsize_t
suffix:semicolon
multiline_comment|/* unsigned bytes in a file */
DECL|typedef|xfs_suminfo_t
r_typedef
id|__int32_t
id|xfs_suminfo_t
suffix:semicolon
multiline_comment|/* type of bitmap summary info */
DECL|typedef|xfs_rtword_t
r_typedef
id|__int32_t
id|xfs_rtword_t
suffix:semicolon
multiline_comment|/* word type for bitmap manipulations */
DECL|typedef|xfs_lsn_t
r_typedef
id|__int64_t
id|xfs_lsn_t
suffix:semicolon
multiline_comment|/* log sequence number */
DECL|typedef|xfs_tid_t
r_typedef
id|__int32_t
id|xfs_tid_t
suffix:semicolon
multiline_comment|/* transaction identifier */
DECL|typedef|xfs_dablk_t
r_typedef
id|__uint32_t
id|xfs_dablk_t
suffix:semicolon
multiline_comment|/* dir/attr block number (in file) */
DECL|typedef|xfs_dahash_t
r_typedef
id|__uint32_t
id|xfs_dahash_t
suffix:semicolon
multiline_comment|/* dir/attr hash value */
DECL|typedef|xfs_prid_t
r_typedef
id|__uint16_t
id|xfs_prid_t
suffix:semicolon
multiline_comment|/* prid_t truncated to 16bits in XFS */
multiline_comment|/*&n; * These types are 64 bits on disk but are either 32 or 64 bits in memory.&n; * Disk based types:&n; */
DECL|typedef|xfs_dfsbno_t
r_typedef
id|__uint64_t
id|xfs_dfsbno_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_drfsbno_t
r_typedef
id|__uint64_t
id|xfs_drfsbno_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_drtbno_t
r_typedef
id|__uint64_t
id|xfs_drtbno_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_dfiloff_t
r_typedef
id|__uint64_t
id|xfs_dfiloff_t
suffix:semicolon
multiline_comment|/* block number in a file */
DECL|typedef|xfs_dfilblks_t
r_typedef
id|__uint64_t
id|xfs_dfilblks_t
suffix:semicolon
multiline_comment|/* number of blocks in a file */
multiline_comment|/*&n; * Memory based types are conditional.&n; */
macro_line|#if XFS_BIG_BLKNOS
DECL|typedef|xfs_fsblock_t
r_typedef
id|__uint64_t
id|xfs_fsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_rfsblock_t
r_typedef
id|__uint64_t
id|xfs_rfsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_rtblock_t
r_typedef
id|__uint64_t
id|xfs_rtblock_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_srtblock_t
r_typedef
id|__int64_t
id|xfs_srtblock_t
suffix:semicolon
multiline_comment|/* signed version of xfs_rtblock_t */
macro_line|#else
DECL|typedef|xfs_fsblock_t
r_typedef
id|__uint32_t
id|xfs_fsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (agno|agbno) */
DECL|typedef|xfs_rfsblock_t
r_typedef
id|__uint32_t
id|xfs_rfsblock_t
suffix:semicolon
multiline_comment|/* blockno in filesystem (raw) */
DECL|typedef|xfs_rtblock_t
r_typedef
id|__uint32_t
id|xfs_rtblock_t
suffix:semicolon
multiline_comment|/* extent (block) in realtime area */
DECL|typedef|xfs_srtblock_t
r_typedef
id|__int32_t
id|xfs_srtblock_t
suffix:semicolon
multiline_comment|/* signed version of xfs_rtblock_t */
macro_line|#endif
DECL|typedef|xfs_fileoff_t
r_typedef
id|__uint64_t
id|xfs_fileoff_t
suffix:semicolon
multiline_comment|/* block number in a file */
DECL|typedef|xfs_sfiloff_t
r_typedef
id|__int64_t
id|xfs_sfiloff_t
suffix:semicolon
multiline_comment|/* signed block number in a file */
DECL|typedef|xfs_filblks_t
r_typedef
id|__uint64_t
id|xfs_filblks_t
suffix:semicolon
multiline_comment|/* number of blocks in a file */
DECL|typedef|xfs_arch_t
r_typedef
id|__uint8_t
id|xfs_arch_t
suffix:semicolon
multiline_comment|/* architecture of an xfs fs */
multiline_comment|/*&n; * Null values for the types.&n; */
DECL|macro|NULLDFSBNO
mdefine_line|#define&t;NULLDFSBNO&t;((xfs_dfsbno_t)-1)
DECL|macro|NULLDRFSBNO
mdefine_line|#define&t;NULLDRFSBNO&t;((xfs_drfsbno_t)-1)
DECL|macro|NULLDRTBNO
mdefine_line|#define&t;NULLDRTBNO&t;((xfs_drtbno_t)-1)
DECL|macro|NULLDFILOFF
mdefine_line|#define&t;NULLDFILOFF&t;((xfs_dfiloff_t)-1)
DECL|macro|NULLFSBLOCK
mdefine_line|#define&t;NULLFSBLOCK&t;((xfs_fsblock_t)-1)
DECL|macro|NULLRFSBLOCK
mdefine_line|#define&t;NULLRFSBLOCK&t;((xfs_rfsblock_t)-1)
DECL|macro|NULLRTBLOCK
mdefine_line|#define&t;NULLRTBLOCK&t;((xfs_rtblock_t)-1)
DECL|macro|NULLFILEOFF
mdefine_line|#define&t;NULLFILEOFF&t;((xfs_fileoff_t)-1)
DECL|macro|NULLAGBLOCK
mdefine_line|#define&t;NULLAGBLOCK&t;((xfs_agblock_t)-1)
DECL|macro|NULLAGNUMBER
mdefine_line|#define&t;NULLAGNUMBER&t;((xfs_agnumber_t)-1)
DECL|macro|NULLEXTNUM
mdefine_line|#define&t;NULLEXTNUM&t;((xfs_extnum_t)-1)
DECL|macro|NULLCOMMITLSN
mdefine_line|#define NULLCOMMITLSN&t;((xfs_lsn_t)-1)
multiline_comment|/*&n; * Max values for extlen, extnum, aextnum.&n; */
DECL|macro|MAXEXTLEN
mdefine_line|#define&t;MAXEXTLEN&t;((xfs_extlen_t)0x001fffff)&t;/* 21 bits */
DECL|macro|MAXEXTNUM
mdefine_line|#define&t;MAXEXTNUM&t;((xfs_extnum_t)0x7fffffff)&t;/* signed int */
DECL|macro|MAXAEXTNUM
mdefine_line|#define&t;MAXAEXTNUM&t;((xfs_aextnum_t)0x7fff)&t;&t;/* signed short */
multiline_comment|/*&n; * MAXNAMELEN is the length (including the terminating null) of&n; * the longest permissible file (component) name.&n; */
DECL|macro|MAXNAMELEN
mdefine_line|#define MAXNAMELEN&t;256
DECL|struct|xfs_dirent
r_typedef
r_struct
id|xfs_dirent
(brace
multiline_comment|/* data from readdir() */
DECL|member|d_ino
id|xfs_ino_t
id|d_ino
suffix:semicolon
multiline_comment|/* inode number of entry */
DECL|member|d_off
id|xfs_off_t
id|d_off
suffix:semicolon
multiline_comment|/* offset of disk directory entry */
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this record */
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name of file */
DECL|typedef|xfs_dirent_t
)brace
id|xfs_dirent_t
suffix:semicolon
DECL|macro|DIRENTBASESIZE
mdefine_line|#define DIRENTBASESIZE&t;&t;(((xfs_dirent_t *)0)-&gt;d_name - (char *)0)
DECL|macro|DIRENTSIZE
mdefine_line|#define DIRENTSIZE(namelen)&t;&bslash;&n;&t;((DIRENTBASESIZE + (namelen) + &bslash;&n;&t;&t;sizeof(xfs_off_t)) &amp; ~(sizeof(xfs_off_t) - 1))
r_typedef
r_enum
(brace
DECL|enumerator|XFS_LOOKUP_EQi
DECL|enumerator|XFS_LOOKUP_LEi
DECL|enumerator|XFS_LOOKUP_GEi
id|XFS_LOOKUP_EQi
comma
id|XFS_LOOKUP_LEi
comma
id|XFS_LOOKUP_GEi
DECL|typedef|xfs_lookup_t
)brace
id|xfs_lookup_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|XFS_BTNUM_BNOi
DECL|enumerator|XFS_BTNUM_CNTi
DECL|enumerator|XFS_BTNUM_BMAPi
DECL|enumerator|XFS_BTNUM_INOi
id|XFS_BTNUM_BNOi
comma
id|XFS_BTNUM_CNTi
comma
id|XFS_BTNUM_BMAPi
comma
id|XFS_BTNUM_INOi
comma
DECL|enumerator|XFS_BTNUM_MAX
id|XFS_BTNUM_MAX
DECL|typedef|xfs_btnum_t
)brace
id|xfs_btnum_t
suffix:semicolon
macro_line|#endif&t;/* !__XFS_TYPES_H */
eof
