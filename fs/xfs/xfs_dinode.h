multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DINODE_H__
DECL|macro|__XFS_DINODE_H__
mdefine_line|#define&t;__XFS_DINODE_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
DECL|macro|XFS_DINODE_VERSION_1
mdefine_line|#define&t;XFS_DINODE_VERSION_1&t;1
DECL|macro|XFS_DINODE_VERSION_2
mdefine_line|#define&t;XFS_DINODE_VERSION_2&t;2
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DINODE_GOOD_VERSION)
r_int
id|xfs_dinode_good_version
c_func
(paren
r_int
id|v
)paren
suffix:semicolon
DECL|macro|XFS_DINODE_GOOD_VERSION
mdefine_line|#define XFS_DINODE_GOOD_VERSION(v)&t;xfs_dinode_good_version(v)
macro_line|#else
DECL|macro|XFS_DINODE_GOOD_VERSION
mdefine_line|#define XFS_DINODE_GOOD_VERSION(v)&t;(((v) == XFS_DINODE_VERSION_1) || &bslash;&n;&t;&t;&t;&t;&t; ((v) == XFS_DINODE_VERSION_2))
macro_line|#endif
DECL|macro|XFS_DINODE_MAGIC
mdefine_line|#define&t;XFS_DINODE_MAGIC&t;0x494e&t;/* &squot;IN&squot; */
multiline_comment|/*&n; * Disk inode structure.&n; * This is just the header; the inode is expanded to fill a variable size&n; * with the last field expanding.  It is split into the core and &quot;other&quot;&n; * because we only need the core part in the in-core inode.&n; */
DECL|struct|xfs_timestamp
r_typedef
r_struct
id|xfs_timestamp
(brace
DECL|member|t_sec
id|__int32_t
id|t_sec
suffix:semicolon
multiline_comment|/* timestamp seconds */
DECL|member|t_nsec
id|__int32_t
id|t_nsec
suffix:semicolon
multiline_comment|/* timestamp nanoseconds */
DECL|typedef|xfs_timestamp_t
)brace
id|xfs_timestamp_t
suffix:semicolon
multiline_comment|/*&n; * Note: Coordinate changes to this structure with the XFS_DI_* #defines&n; * below and the offsets table in xfs_ialloc_log_di().&n; */
DECL|struct|xfs_dinode_core
r_typedef
r_struct
id|xfs_dinode_core
(brace
DECL|member|di_magic
id|__uint16_t
id|di_magic
suffix:semicolon
multiline_comment|/* inode magic # = XFS_DINODE_MAGIC */
DECL|member|di_mode
id|__uint16_t
id|di_mode
suffix:semicolon
multiline_comment|/* mode and type of file */
DECL|member|di_version
id|__int8_t
id|di_version
suffix:semicolon
multiline_comment|/* inode version */
DECL|member|di_format
id|__int8_t
id|di_format
suffix:semicolon
multiline_comment|/* format of di_c data */
DECL|member|di_onlink
id|__uint16_t
id|di_onlink
suffix:semicolon
multiline_comment|/* old number of links to file */
DECL|member|di_uid
id|__uint32_t
id|di_uid
suffix:semicolon
multiline_comment|/* owner&squot;s user id */
DECL|member|di_gid
id|__uint32_t
id|di_gid
suffix:semicolon
multiline_comment|/* owner&squot;s group id */
DECL|member|di_nlink
id|__uint32_t
id|di_nlink
suffix:semicolon
multiline_comment|/* number of links to file */
DECL|member|di_projid
id|__uint16_t
id|di_projid
suffix:semicolon
multiline_comment|/* owner&squot;s project id */
DECL|member|di_pad
id|__uint8_t
id|di_pad
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* unused, zeroed space */
DECL|member|di_flushiter
id|__uint16_t
id|di_flushiter
suffix:semicolon
multiline_comment|/* incremented on flush */
DECL|member|di_atime
id|xfs_timestamp_t
id|di_atime
suffix:semicolon
multiline_comment|/* time last accessed */
DECL|member|di_mtime
id|xfs_timestamp_t
id|di_mtime
suffix:semicolon
multiline_comment|/* time last modified */
DECL|member|di_ctime
id|xfs_timestamp_t
id|di_ctime
suffix:semicolon
multiline_comment|/* time created/inode modified */
DECL|member|di_size
id|xfs_fsize_t
id|di_size
suffix:semicolon
multiline_comment|/* number of bytes in file */
DECL|member|di_nblocks
id|xfs_drfsbno_t
id|di_nblocks
suffix:semicolon
multiline_comment|/* # of direct &amp; btree blocks used */
DECL|member|di_extsize
id|xfs_extlen_t
id|di_extsize
suffix:semicolon
multiline_comment|/* basic/minimum extent size for file */
DECL|member|di_nextents
id|xfs_extnum_t
id|di_nextents
suffix:semicolon
multiline_comment|/* number of extents in data fork */
DECL|member|di_anextents
id|xfs_aextnum_t
id|di_anextents
suffix:semicolon
multiline_comment|/* number of extents in attribute fork*/
DECL|member|di_forkoff
id|__uint8_t
id|di_forkoff
suffix:semicolon
multiline_comment|/* attr fork offs, &lt;&lt;3 for 64b align */
DECL|member|di_aformat
id|__int8_t
id|di_aformat
suffix:semicolon
multiline_comment|/* format of attr fork&squot;s data */
DECL|member|di_dmevmask
id|__uint32_t
id|di_dmevmask
suffix:semicolon
multiline_comment|/* DMIG event mask */
DECL|member|di_dmstate
id|__uint16_t
id|di_dmstate
suffix:semicolon
multiline_comment|/* DMIG state info */
DECL|member|di_flags
id|__uint16_t
id|di_flags
suffix:semicolon
multiline_comment|/* random flags, XFS_DIFLAG_... */
DECL|member|di_gen
id|__uint32_t
id|di_gen
suffix:semicolon
multiline_comment|/* generation number */
DECL|typedef|xfs_dinode_core_t
)brace
id|xfs_dinode_core_t
suffix:semicolon
DECL|macro|DI_MAX_FLUSH
mdefine_line|#define DI_MAX_FLUSH 0xffff
DECL|struct|xfs_dinode
r_typedef
r_struct
id|xfs_dinode
(brace
DECL|member|di_core
id|xfs_dinode_core_t
id|di_core
suffix:semicolon
multiline_comment|/*&n;&t; * In adding anything between the core and the union, be&n;&t; * sure to update the macros like XFS_LITINO below and&n;&t; * XFS_BMAP_RBLOCK_DSIZE in xfs_bmap_btree.h.&n;&t; */
DECL|member|di_next_unlinked
id|xfs_agino_t
id|di_next_unlinked
suffix:semicolon
multiline_comment|/* agi unlinked list ptr */
r_union
(brace
DECL|member|di_bmbt
id|xfs_bmdr_block_t
id|di_bmbt
suffix:semicolon
multiline_comment|/* btree root block */
DECL|member|di_bmx
id|xfs_bmbt_rec_32_t
id|di_bmx
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* extent list */
DECL|member|di_dirsf
id|xfs_dir_shortform_t
id|di_dirsf
suffix:semicolon
multiline_comment|/* shortform directory */
DECL|member|di_dir2sf
id|xfs_dir2_sf_t
id|di_dir2sf
suffix:semicolon
multiline_comment|/* shortform directory v2 */
DECL|member|di_c
r_char
id|di_c
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* local contents */
DECL|member|di_dev
id|xfs_dev_t
id|di_dev
suffix:semicolon
multiline_comment|/* device for S_IFCHR/S_IFBLK */
DECL|member|di_muuid
id|uuid_t
id|di_muuid
suffix:semicolon
multiline_comment|/* mount point value */
DECL|member|di_symlink
r_char
id|di_symlink
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* local symbolic link */
DECL|member|di_u
)brace
id|di_u
suffix:semicolon
r_union
(brace
DECL|member|di_abmbt
id|xfs_bmdr_block_t
id|di_abmbt
suffix:semicolon
multiline_comment|/* btree root block */
DECL|member|di_abmx
id|xfs_bmbt_rec_32_t
id|di_abmx
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* extent list */
DECL|member|di_attrsf
id|xfs_attr_shortform_t
id|di_attrsf
suffix:semicolon
multiline_comment|/* shortform attribute list */
DECL|member|di_a
)brace
id|di_a
suffix:semicolon
DECL|typedef|xfs_dinode_t
)brace
id|xfs_dinode_t
suffix:semicolon
multiline_comment|/*&n; * The 32 bit link count in the inode theoretically maxes out at UINT_MAX.&n; * Since the pathconf interface is signed, we use 2^31 - 1 instead.&n; * The old inode format had a 16 bit link count, so its maximum is USHRT_MAX.&n; */
DECL|macro|XFS_MAXLINK
mdefine_line|#define&t;XFS_MAXLINK&t;&t;((1U &lt;&lt; 31) - 1U)
DECL|macro|XFS_MAXLINK_1
mdefine_line|#define&t;XFS_MAXLINK_1&t;&t;65535U
multiline_comment|/*&n; * Bit names for logging disk inodes only&n; */
DECL|macro|XFS_DI_MAGIC
mdefine_line|#define&t;XFS_DI_MAGIC&t;&t;0x0000001
DECL|macro|XFS_DI_MODE
mdefine_line|#define&t;XFS_DI_MODE&t;&t;0x0000002
DECL|macro|XFS_DI_VERSION
mdefine_line|#define&t;XFS_DI_VERSION&t;&t;0x0000004
DECL|macro|XFS_DI_FORMAT
mdefine_line|#define&t;XFS_DI_FORMAT&t;&t;0x0000008
DECL|macro|XFS_DI_ONLINK
mdefine_line|#define&t;XFS_DI_ONLINK&t;&t;0x0000010
DECL|macro|XFS_DI_UID
mdefine_line|#define&t;XFS_DI_UID&t;&t;0x0000020
DECL|macro|XFS_DI_GID
mdefine_line|#define&t;XFS_DI_GID&t;&t;0x0000040
DECL|macro|XFS_DI_NLINK
mdefine_line|#define&t;XFS_DI_NLINK&t;&t;0x0000080
DECL|macro|XFS_DI_PROJID
mdefine_line|#define&t;XFS_DI_PROJID&t;&t;0x0000100
DECL|macro|XFS_DI_PAD
mdefine_line|#define&t;XFS_DI_PAD&t;&t;0x0000200
DECL|macro|XFS_DI_ATIME
mdefine_line|#define&t;XFS_DI_ATIME&t;&t;0x0000400
DECL|macro|XFS_DI_MTIME
mdefine_line|#define&t;XFS_DI_MTIME&t;&t;0x0000800
DECL|macro|XFS_DI_CTIME
mdefine_line|#define&t;XFS_DI_CTIME&t;&t;0x0001000
DECL|macro|XFS_DI_SIZE
mdefine_line|#define&t;XFS_DI_SIZE&t;&t;0x0002000
DECL|macro|XFS_DI_NBLOCKS
mdefine_line|#define&t;XFS_DI_NBLOCKS&t;&t;0x0004000
DECL|macro|XFS_DI_EXTSIZE
mdefine_line|#define&t;XFS_DI_EXTSIZE&t;&t;0x0008000
DECL|macro|XFS_DI_NEXTENTS
mdefine_line|#define&t;XFS_DI_NEXTENTS&t;&t;0x0010000
DECL|macro|XFS_DI_NAEXTENTS
mdefine_line|#define&t;XFS_DI_NAEXTENTS&t;0x0020000
DECL|macro|XFS_DI_FORKOFF
mdefine_line|#define&t;XFS_DI_FORKOFF&t;&t;0x0040000
DECL|macro|XFS_DI_AFORMAT
mdefine_line|#define&t;XFS_DI_AFORMAT&t;&t;0x0080000
DECL|macro|XFS_DI_DMEVMASK
mdefine_line|#define&t;XFS_DI_DMEVMASK&t;&t;0x0100000
DECL|macro|XFS_DI_DMSTATE
mdefine_line|#define&t;XFS_DI_DMSTATE&t;&t;0x0200000
DECL|macro|XFS_DI_FLAGS
mdefine_line|#define&t;XFS_DI_FLAGS&t;&t;0x0400000
DECL|macro|XFS_DI_GEN
mdefine_line|#define&t;XFS_DI_GEN&t;&t;0x0800000
DECL|macro|XFS_DI_NEXT_UNLINKED
mdefine_line|#define&t;XFS_DI_NEXT_UNLINKED&t;0x1000000
DECL|macro|XFS_DI_U
mdefine_line|#define&t;XFS_DI_U&t;&t;0x2000000
DECL|macro|XFS_DI_A
mdefine_line|#define&t;XFS_DI_A&t;&t;0x4000000
DECL|macro|XFS_DI_NUM_BITS
mdefine_line|#define&t;XFS_DI_NUM_BITS&t;&t;27
DECL|macro|XFS_DI_ALL_BITS
mdefine_line|#define&t;XFS_DI_ALL_BITS&t;&t;((1 &lt;&lt; XFS_DI_NUM_BITS) - 1)
DECL|macro|XFS_DI_CORE_BITS
mdefine_line|#define&t;XFS_DI_CORE_BITS&t;(XFS_DI_ALL_BITS &amp; ~(XFS_DI_U|XFS_DI_A))
multiline_comment|/*&n; * Values for di_format&n; */
DECL|enum|xfs_dinode_fmt
r_typedef
r_enum
id|xfs_dinode_fmt
(brace
DECL|enumerator|XFS_DINODE_FMT_DEV
id|XFS_DINODE_FMT_DEV
comma
multiline_comment|/* CHR, BLK: di_dev */
DECL|enumerator|XFS_DINODE_FMT_LOCAL
id|XFS_DINODE_FMT_LOCAL
comma
multiline_comment|/* DIR, REG: di_c */
multiline_comment|/* LNK: di_symlink */
DECL|enumerator|XFS_DINODE_FMT_EXTENTS
id|XFS_DINODE_FMT_EXTENTS
comma
multiline_comment|/* DIR, REG, LNK: di_bmx */
DECL|enumerator|XFS_DINODE_FMT_BTREE
id|XFS_DINODE_FMT_BTREE
comma
multiline_comment|/* DIR, REG, LNK: di_bmbt */
DECL|enumerator|XFS_DINODE_FMT_UUID
id|XFS_DINODE_FMT_UUID
multiline_comment|/* MNT: di_uuid */
DECL|typedef|xfs_dinode_fmt_t
)brace
id|xfs_dinode_fmt_t
suffix:semicolon
multiline_comment|/*&n; * Inode minimum and maximum sizes.&n; */
DECL|macro|XFS_DINODE_MIN_LOG
mdefine_line|#define&t;XFS_DINODE_MIN_LOG&t;8
DECL|macro|XFS_DINODE_MAX_LOG
mdefine_line|#define&t;XFS_DINODE_MAX_LOG&t;11
DECL|macro|XFS_DINODE_MIN_SIZE
mdefine_line|#define&t;XFS_DINODE_MIN_SIZE&t;(1 &lt;&lt; XFS_DINODE_MIN_LOG)
DECL|macro|XFS_DINODE_MAX_SIZE
mdefine_line|#define&t;XFS_DINODE_MAX_SIZE&t;(1 &lt;&lt; XFS_DINODE_MAX_LOG)
multiline_comment|/*&n; * Inode size for given fs.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LITINO)
r_int
id|xfs_litino
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_LITINO
mdefine_line|#define&t;XFS_LITINO(mp)&t;&t;xfs_litino(mp)
macro_line|#else
DECL|macro|XFS_LITINO
mdefine_line|#define&t;XFS_LITINO(mp)&t;((mp)-&gt;m_litino)
macro_line|#endif
DECL|macro|XFS_BROOT_SIZE_ADJ
mdefine_line|#define&t;XFS_BROOT_SIZE_ADJ&t;&bslash;&n;&t;(sizeof(xfs_bmbt_block_t) - sizeof(xfs_bmdr_block_t))
multiline_comment|/*&n; * Fork identifiers.  Here so utilities can use them without including&n; * xfs_inode.h.&n; */
DECL|macro|XFS_DATA_FORK
mdefine_line|#define&t;XFS_DATA_FORK&t;0
DECL|macro|XFS_ATTR_FORK
mdefine_line|#define&t;XFS_ATTR_FORK&t;1
multiline_comment|/*&n; * Inode data &amp; attribute fork sizes, per inode.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_Q)
r_int
id|xfs_cfork_q_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
)paren
suffix:semicolon
r_int
id|xfs_cfork_q
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_Q_DISK
mdefine_line|#define&t;XFS_CFORK_Q_DISK(dcp)               xfs_cfork_q_disk(dcp)
DECL|macro|XFS_CFORK_Q
mdefine_line|#define&t;XFS_CFORK_Q(dcp)                    xfs_cfork_q(dcp)
macro_line|#else
DECL|macro|XFS_CFORK_Q_DISK
mdefine_line|#define&t;XFS_CFORK_Q_DISK(dcp)&t;&t;    (!INT_ISZERO((dcp)-&gt;di_forkoff, ARCH_CONVERT))
DECL|macro|XFS_CFORK_Q
mdefine_line|#define XFS_CFORK_Q(dcp)                    ((dcp)-&gt;di_forkoff != 0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_BOFF)
r_int
id|xfs_cfork_boff_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
)paren
suffix:semicolon
r_int
id|xfs_cfork_boff
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_BOFF_DISK
mdefine_line|#define&t;XFS_CFORK_BOFF_DISK(dcp)&t;    xfs_cfork_boff_disk(dcp)
DECL|macro|XFS_CFORK_BOFF
mdefine_line|#define&t;XFS_CFORK_BOFF(dcp)&t;            xfs_cfork_boff(dcp)
macro_line|#else
DECL|macro|XFS_CFORK_BOFF_DISK
mdefine_line|#define&t;XFS_CFORK_BOFF_DISK(dcp)&t;    ((int)(INT_GET((dcp)-&gt;di_forkoff, ARCH_CONVERT) &lt;&lt; 3))
DECL|macro|XFS_CFORK_BOFF
mdefine_line|#define XFS_CFORK_BOFF(dcp)                 ((int)((dcp)-&gt;di_forkoff &lt;&lt; 3))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_DSIZE)
r_int
id|xfs_cfork_dsize_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_cfork_dsize
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_DSIZE_DISK
mdefine_line|#define&t;XFS_CFORK_DSIZE_DISK(dcp,mp)        xfs_cfork_dsize_disk(dcp,mp)
DECL|macro|XFS_CFORK_DSIZE
mdefine_line|#define&t;XFS_CFORK_DSIZE(dcp,mp)             xfs_cfork_dsize(dcp,mp)
macro_line|#else
DECL|macro|XFS_CFORK_DSIZE_DISK
mdefine_line|#define&t;XFS_CFORK_DSIZE_DISK(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q_DISK(dcp) ? XFS_CFORK_BOFF_DISK(dcp) : XFS_LITINO(mp))
DECL|macro|XFS_CFORK_DSIZE
mdefine_line|#define XFS_CFORK_DSIZE(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q(dcp) ? XFS_CFORK_BOFF(dcp) : XFS_LITINO(mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_ASIZE)
r_int
id|xfs_cfork_asize_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_int
id|xfs_cfork_asize
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_ASIZE_DISK
mdefine_line|#define&t;XFS_CFORK_ASIZE_DISK(dcp,mp)        xfs_cfork_asize_disk(dcp,mp)
DECL|macro|XFS_CFORK_ASIZE
mdefine_line|#define&t;XFS_CFORK_ASIZE(dcp,mp)             xfs_cfork_asize(dcp,mp)
macro_line|#else
DECL|macro|XFS_CFORK_ASIZE_DISK
mdefine_line|#define&t;XFS_CFORK_ASIZE_DISK(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q_DISK(dcp) ? XFS_LITINO(mp) - XFS_CFORK_BOFF_DISK(dcp) : 0)
DECL|macro|XFS_CFORK_ASIZE
mdefine_line|#define XFS_CFORK_ASIZE(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q(dcp) ? XFS_LITINO(mp) - XFS_CFORK_BOFF(dcp) : 0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_SIZE)
r_int
id|xfs_cfork_size_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|w
)paren
suffix:semicolon
r_int
id|xfs_cfork_size
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_SIZE_DISK
mdefine_line|#define&t;XFS_CFORK_SIZE_DISK(dcp,mp,w)       xfs_cfork_size_disk(dcp,mp,w)
DECL|macro|XFS_CFORK_SIZE
mdefine_line|#define&t;XFS_CFORK_SIZE(dcp,mp,w)            xfs_cfork_size(dcp,mp,w)
macro_line|#else
DECL|macro|XFS_CFORK_SIZE_DISK
mdefine_line|#define&t;XFS_CFORK_SIZE_DISK(dcp,mp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;XFS_CFORK_DSIZE_DISK(dcp, mp) : &bslash;&n;&t; &t;XFS_CFORK_ASIZE_DISK(dcp, mp))
DECL|macro|XFS_CFORK_SIZE
mdefine_line|#define XFS_CFORK_SIZE(dcp,mp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;XFS_CFORK_DSIZE(dcp, mp) : XFS_CFORK_ASIZE(dcp, mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_DSIZE)
r_int
id|xfs_dfork_dsize
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_DSIZE
mdefine_line|#define&t;XFS_DFORK_DSIZE(dip,mp)             xfs_dfork_dsize(dip,mp)
macro_line|#else
DECL|macro|XFS_DFORK_DSIZE
mdefine_line|#define XFS_DFORK_DSIZE(dip,mp)             XFS_CFORK_DSIZE_DISK(&amp;(dip)-&gt;di_core, mp)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_ASIZE)
r_int
id|xfs_dfork_asize
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_ASIZE
mdefine_line|#define&t;XFS_DFORK_ASIZE(dip,mp)             xfs_dfork_asize(dip,mp)
macro_line|#else
DECL|macro|XFS_DFORK_ASIZE
mdefine_line|#define XFS_DFORK_ASIZE(dip,mp)             XFS_CFORK_ASIZE_DISK(&amp;(dip)-&gt;di_core, mp)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_SIZE)
r_int
id|xfs_dfork_size
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_SIZE
mdefine_line|#define&t;XFS_DFORK_SIZE(dip,mp,w)            xfs_dfork_size(dip,mp,w)
macro_line|#else
DECL|macro|XFS_DFORK_SIZE
mdefine_line|#define&t;XFS_DFORK_SIZE(dip,mp,w)&t;    XFS_CFORK_SIZE_DISK(&amp;(dip)-&gt;di_core, mp, w)
macro_line|#endif
multiline_comment|/*&n; * Macros for accessing per-fork disk inode information.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_Q)
r_int
id|xfs_dfork_q
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_Q
mdefine_line|#define&t;XFS_DFORK_Q(dip)&t;            xfs_dfork_q(dip)
macro_line|#else
DECL|macro|XFS_DFORK_Q
mdefine_line|#define&t;XFS_DFORK_Q(dip)                    XFS_CFORK_Q_DISK(&amp;(dip)-&gt;di_core)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_BOFF)
r_int
id|xfs_dfork_boff
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_BOFF
mdefine_line|#define&t;XFS_DFORK_BOFF(dip)&t;&t;    xfs_dfork_boff(dip)
macro_line|#else
DECL|macro|XFS_DFORK_BOFF
mdefine_line|#define&t;XFS_DFORK_BOFF(dip)&t;&t;    XFS_CFORK_BOFF_DISK(&amp;(dip)-&gt;di_core)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_DPTR)
r_char
op_star
id|xfs_dfork_dptr
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_DPTR
mdefine_line|#define&t;XFS_DFORK_DPTR(dip)&t;            xfs_dfork_dptr(dip)
macro_line|#else
DECL|macro|XFS_DFORK_DPTR
mdefine_line|#define&t;XFS_DFORK_DPTR(dip)&t;&t;    ((dip)-&gt;di_u.di_c)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_APTR)
r_char
op_star
id|xfs_dfork_aptr
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_APTR
mdefine_line|#define&t;XFS_DFORK_APTR(dip)                 xfs_dfork_aptr(dip)
macro_line|#else
DECL|macro|XFS_DFORK_APTR
mdefine_line|#define&t;XFS_DFORK_APTR(dip)&t;&t;    ((dip)-&gt;di_u.di_c + XFS_DFORK_BOFF(dip))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_PTR)
r_char
op_star
id|xfs_dfork_ptr
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_PTR
mdefine_line|#define&t;XFS_DFORK_PTR(dip,w)                xfs_dfork_ptr(dip,w)
macro_line|#else
DECL|macro|XFS_DFORK_PTR
mdefine_line|#define&t;XFS_DFORK_PTR(dip,w)&t;&bslash;&n;&t;((w) == XFS_DATA_FORK ? XFS_DFORK_DPTR(dip) : XFS_DFORK_APTR(dip))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_FORMAT)
r_int
id|xfs_cfork_format
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_FORMAT
mdefine_line|#define&t;XFS_CFORK_FORMAT(dcp,w)             xfs_cfork_format(dcp,w)
macro_line|#else
DECL|macro|XFS_CFORK_FORMAT
mdefine_line|#define&t;XFS_CFORK_FORMAT(dcp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? (dcp)-&gt;di_format : (dcp)-&gt;di_aformat)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_FMT_SET)
r_void
id|xfs_cfork_fmt_set
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_FMT_SET
mdefine_line|#define&t;XFS_CFORK_FMT_SET(dcp,w,n)           xfs_cfork_fmt_set(dcp,w,n)
macro_line|#else
DECL|macro|XFS_CFORK_FMT_SET
mdefine_line|#define&t;XFS_CFORK_FMT_SET(dcp,w,n) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;((dcp)-&gt;di_format = (n)) : &bslash;&n;&t;&t;((dcp)-&gt;di_aformat = (n)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_NEXTENTS)
r_int
id|xfs_cfork_nextents_disk
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
)paren
suffix:semicolon
r_int
id|xfs_cfork_nextents
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_NEXTENTS_DISK
mdefine_line|#define&t;XFS_CFORK_NEXTENTS_DISK(dcp,w)       xfs_cfork_nextents_disk(dcp,w)
DECL|macro|XFS_CFORK_NEXTENTS
mdefine_line|#define&t;XFS_CFORK_NEXTENTS(dcp,w)            xfs_cfork_nextents(dcp,w)
macro_line|#else
DECL|macro|XFS_CFORK_NEXTENTS_DISK
mdefine_line|#define&t;XFS_CFORK_NEXTENTS_DISK(dcp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t; &t;INT_GET((dcp)-&gt;di_nextents, ARCH_CONVERT) : &bslash;&n;&t; &t;INT_GET((dcp)-&gt;di_anextents, ARCH_CONVERT))
DECL|macro|XFS_CFORK_NEXTENTS
mdefine_line|#define XFS_CFORK_NEXTENTS(dcp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? (dcp)-&gt;di_nextents : (dcp)-&gt;di_anextents)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_NEXT_SET)
r_void
id|xfs_cfork_next_set
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_CFORK_NEXT_SET
mdefine_line|#define&t;XFS_CFORK_NEXT_SET(dcp,w,n)&t;        xfs_cfork_next_set(dcp,w,n)
macro_line|#else
DECL|macro|XFS_CFORK_NEXT_SET
mdefine_line|#define&t;XFS_CFORK_NEXT_SET(dcp,w,n) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;((dcp)-&gt;di_nextents = (n)) : &bslash;&n;&t;&t;((dcp)-&gt;di_anextents = (n)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_NEXTENTS)
r_int
id|xfs_dfork_nextents
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_NEXTENTS
mdefine_line|#define&t;XFS_DFORK_NEXTENTS(dip,w) xfs_dfork_nextents(dip,w)
macro_line|#else
DECL|macro|XFS_DFORK_NEXTENTS
mdefine_line|#define&t;XFS_DFORK_NEXTENTS(dip,w) XFS_CFORK_NEXTENTS_DISK(&amp;(dip)-&gt;di_core, w)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_DINODE)
id|xfs_dinode_t
op_star
id|xfs_buf_to_dinode
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_DINODE
mdefine_line|#define&t;XFS_BUF_TO_DINODE(bp)&t;xfs_buf_to_dinode(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_DINODE
mdefine_line|#define&t;XFS_BUF_TO_DINODE(bp)&t;((xfs_dinode_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
multiline_comment|/*&n; * Values for di_flags&n; * There should be a one-to-one correspondence between these flags and the&n; * XFS_XFLAG_s.&n; */
DECL|macro|XFS_DIFLAG_REALTIME_BIT
mdefine_line|#define XFS_DIFLAG_REALTIME_BIT  0&t;/* file&squot;s blocks come from rt area */
DECL|macro|XFS_DIFLAG_PREALLOC_BIT
mdefine_line|#define XFS_DIFLAG_PREALLOC_BIT  1&t;/* file space has been preallocated */
DECL|macro|XFS_DIFLAG_NEWRTBM_BIT
mdefine_line|#define XFS_DIFLAG_NEWRTBM_BIT   2&t;/* for rtbitmap inode, new format */
DECL|macro|XFS_DIFLAG_IMMUTABLE_BIT
mdefine_line|#define XFS_DIFLAG_IMMUTABLE_BIT 3&t;/* inode is immutable */
DECL|macro|XFS_DIFLAG_APPEND_BIT
mdefine_line|#define XFS_DIFLAG_APPEND_BIT    4&t;/* inode is append-only */
DECL|macro|XFS_DIFLAG_SYNC_BIT
mdefine_line|#define XFS_DIFLAG_SYNC_BIT      5&t;/* inode is written synchronously */
DECL|macro|XFS_DIFLAG_NOATIME_BIT
mdefine_line|#define XFS_DIFLAG_NOATIME_BIT   6&t;/* do not update atime */
DECL|macro|XFS_DIFLAG_NODUMP_BIT
mdefine_line|#define XFS_DIFLAG_NODUMP_BIT    7&t;/* do not dump */
DECL|macro|XFS_DIFLAG_RTINHERIT_BIT
mdefine_line|#define XFS_DIFLAG_RTINHERIT_BIT 8&t;/* create with realtime bit set */
DECL|macro|XFS_DIFLAG_PROJINHERIT_BIT
mdefine_line|#define XFS_DIFLAG_PROJINHERIT_BIT  9&t;/* create with parents projid */
DECL|macro|XFS_DIFLAG_NOSYMLINKS_BIT
mdefine_line|#define XFS_DIFLAG_NOSYMLINKS_BIT  10&t;/* disallow symlink creation */
DECL|macro|XFS_DIFLAG_REALTIME
mdefine_line|#define XFS_DIFLAG_REALTIME      (1 &lt;&lt; XFS_DIFLAG_REALTIME_BIT)
DECL|macro|XFS_DIFLAG_PREALLOC
mdefine_line|#define XFS_DIFLAG_PREALLOC      (1 &lt;&lt; XFS_DIFLAG_PREALLOC_BIT)
DECL|macro|XFS_DIFLAG_NEWRTBM
mdefine_line|#define XFS_DIFLAG_NEWRTBM       (1 &lt;&lt; XFS_DIFLAG_NEWRTBM_BIT)
DECL|macro|XFS_DIFLAG_IMMUTABLE
mdefine_line|#define XFS_DIFLAG_IMMUTABLE     (1 &lt;&lt; XFS_DIFLAG_IMMUTABLE_BIT)
DECL|macro|XFS_DIFLAG_APPEND
mdefine_line|#define XFS_DIFLAG_APPEND        (1 &lt;&lt; XFS_DIFLAG_APPEND_BIT)
DECL|macro|XFS_DIFLAG_SYNC
mdefine_line|#define XFS_DIFLAG_SYNC          (1 &lt;&lt; XFS_DIFLAG_SYNC_BIT)
DECL|macro|XFS_DIFLAG_NOATIME
mdefine_line|#define XFS_DIFLAG_NOATIME       (1 &lt;&lt; XFS_DIFLAG_NOATIME_BIT)
DECL|macro|XFS_DIFLAG_NODUMP
mdefine_line|#define XFS_DIFLAG_NODUMP        (1 &lt;&lt; XFS_DIFLAG_NODUMP_BIT)
DECL|macro|XFS_DIFLAG_RTINHERIT
mdefine_line|#define XFS_DIFLAG_RTINHERIT     (1 &lt;&lt; XFS_DIFLAG_RTINHERIT_BIT)
DECL|macro|XFS_DIFLAG_PROJINHERIT
mdefine_line|#define XFS_DIFLAG_PROJINHERIT   (1 &lt;&lt; XFS_DIFLAG_PROJINHERIT_BIT)
DECL|macro|XFS_DIFLAG_NOSYMLINKS
mdefine_line|#define XFS_DIFLAG_NOSYMLINKS    (1 &lt;&lt; XFS_DIFLAG_NOSYMLINKS_BIT)
DECL|macro|XFS_DIFLAG_ANY
mdefine_line|#define XFS_DIFLAG_ANY &bslash;&n;&t;(XFS_DIFLAG_REALTIME | XFS_DIFLAG_PREALLOC | XFS_DIFLAG_NEWRTBM | &bslash;&n;&t; XFS_DIFLAG_IMMUTABLE | XFS_DIFLAG_APPEND | XFS_DIFLAG_SYNC | &bslash;&n;&t; XFS_DIFLAG_NOATIME | XFS_DIFLAG_NODUMP | XFS_DIFLAG_RTINHERIT | &bslash;&n;&t; XFS_DIFLAG_PROJINHERIT | XFS_DIFLAG_NOSYMLINKS)
macro_line|#endif&t;/* __XFS_DINODE_H__ */
eof
