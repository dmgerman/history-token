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
multiline_comment|/* device for IFCHR/IFBLK */
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
id|xfs_cfork_q_arch
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_Q_ARCH
mdefine_line|#define&t;XFS_CFORK_Q_ARCH(dcp,arch)          xfs_cfork_q_arch(dcp,arch)
DECL|macro|XFS_CFORK_Q
mdefine_line|#define&t;XFS_CFORK_Q(dcp)                    xfs_cfork_q(dcp)
macro_line|#else
DECL|macro|XFS_CFORK_Q_ARCH
mdefine_line|#define&t;XFS_CFORK_Q_ARCH(dcp,arch)&t;    (!INT_ISZERO((dcp)-&gt;di_forkoff, arch))
DECL|macro|XFS_CFORK_Q
mdefine_line|#define XFS_CFORK_Q(dcp)                    ((dcp)-&gt;di_forkoff != 0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_BOFF)
r_int
id|xfs_cfork_boff_arch
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_BOFF_ARCH
mdefine_line|#define&t;XFS_CFORK_BOFF_ARCH(dcp,arch)&t;    xfs_cfork_boff_arch(dcp,arch)
DECL|macro|XFS_CFORK_BOFF
mdefine_line|#define&t;XFS_CFORK_BOFF(dcp)&t;            xfs_cfork_boff(dcp)
macro_line|#else
DECL|macro|XFS_CFORK_BOFF_ARCH
mdefine_line|#define&t;XFS_CFORK_BOFF_ARCH(dcp,arch)&t;    ((int)(INT_GET((dcp)-&gt;di_forkoff, arch) &lt;&lt; 3))
DECL|macro|XFS_CFORK_BOFF
mdefine_line|#define XFS_CFORK_BOFF(dcp)                 ((int)((dcp)-&gt;di_forkoff &lt;&lt; 3))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_DSIZE)
r_int
id|xfs_cfork_dsize_arch
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
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_DSIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_DSIZE_ARCH(dcp,mp,arch)   xfs_cfork_dsize_arch(dcp,mp,arch)
DECL|macro|XFS_CFORK_DSIZE
mdefine_line|#define&t;XFS_CFORK_DSIZE(dcp,mp)             xfs_cfork_dsize(dcp,mp)
macro_line|#else
DECL|macro|XFS_CFORK_DSIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_DSIZE_ARCH(dcp,mp,arch) &bslash;&n;&t;(XFS_CFORK_Q_ARCH(dcp, arch) ? XFS_CFORK_BOFF_ARCH(dcp, arch) : XFS_LITINO(mp))
DECL|macro|XFS_CFORK_DSIZE
mdefine_line|#define XFS_CFORK_DSIZE(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q(dcp) ? XFS_CFORK_BOFF(dcp) : XFS_LITINO(mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_ASIZE)
r_int
id|xfs_cfork_asize_arch
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
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_ASIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_ASIZE_ARCH(dcp,mp,arch)   xfs_cfork_asize_arch(dcp,mp,arch)
DECL|macro|XFS_CFORK_ASIZE
mdefine_line|#define&t;XFS_CFORK_ASIZE(dcp,mp)             xfs_cfork_asize(dcp,mp)
macro_line|#else
DECL|macro|XFS_CFORK_ASIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_ASIZE_ARCH(dcp,mp,arch) &bslash;&n;&t;(XFS_CFORK_Q_ARCH(dcp, arch) ? XFS_LITINO(mp) - XFS_CFORK_BOFF_ARCH(dcp, arch) : 0)
DECL|macro|XFS_CFORK_ASIZE
mdefine_line|#define XFS_CFORK_ASIZE(dcp,mp) &bslash;&n;&t;(XFS_CFORK_Q(dcp) ? XFS_LITINO(mp) - XFS_CFORK_BOFF(dcp) : 0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_SIZE)
r_int
id|xfs_cfork_size_arch
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
comma
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_SIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_SIZE_ARCH(dcp,mp,w,arch)  xfs_cfork_size_arch(dcp,mp,w,arch)
DECL|macro|XFS_CFORK_SIZE
mdefine_line|#define&t;XFS_CFORK_SIZE(dcp,mp,w)            xfs_cfork_size(dcp,mp,w)
macro_line|#else
DECL|macro|XFS_CFORK_SIZE_ARCH
mdefine_line|#define&t;XFS_CFORK_SIZE_ARCH(dcp,mp,w,arch) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;XFS_CFORK_DSIZE_ARCH(dcp, mp, arch) : XFS_CFORK_ASIZE_ARCH(dcp, mp, arch))
DECL|macro|XFS_CFORK_SIZE
mdefine_line|#define XFS_CFORK_SIZE(dcp,mp,w) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;XFS_CFORK_DSIZE(dcp, mp) : XFS_CFORK_ASIZE(dcp, mp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_DSIZE)
r_int
id|xfs_dfork_dsize_arch
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
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_DSIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_DSIZE_ARCH(dip,mp,arch)   xfs_dfork_dsize_arch(dip,mp,arch)
DECL|macro|XFS_DFORK_DSIZE
mdefine_line|#define&t;XFS_DFORK_DSIZE(dip,mp)             xfs_dfork_dsize(dip,mp)
macro_line|#else
DECL|macro|XFS_DFORK_DSIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_DSIZE_ARCH(dip,mp,arch)   XFS_CFORK_DSIZE_ARCH(&amp;(dip)-&gt;di_core, mp, arch)
DECL|macro|XFS_DFORK_DSIZE
mdefine_line|#define XFS_DFORK_DSIZE(dip,mp)             XFS_DFORK_DSIZE_ARCH(dip,mp,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_ASIZE)
r_int
id|xfs_dfork_asize_arch
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
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_ASIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_ASIZE_ARCH(dip,mp,arch)   xfs_dfork_asize_arch(dip,mp,arch)
DECL|macro|XFS_DFORK_ASIZE
mdefine_line|#define&t;XFS_DFORK_ASIZE(dip,mp)             xfs_dfork_asize(dip,mp)
macro_line|#else
DECL|macro|XFS_DFORK_ASIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_ASIZE_ARCH(dip,mp,arch)   XFS_CFORK_ASIZE_ARCH(&amp;(dip)-&gt;di_core, mp, arch)
DECL|macro|XFS_DFORK_ASIZE
mdefine_line|#define XFS_DFORK_ASIZE(dip,mp)             XFS_DFORK_ASIZE_ARCH(dip,mp,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_SIZE)
r_int
id|xfs_dfork_size_arch
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
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_SIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_SIZE_ARCH(dip,mp,w,arch)  xfs_dfork_size_arch(dip,mp,w,arch)
DECL|macro|XFS_DFORK_SIZE
mdefine_line|#define&t;XFS_DFORK_SIZE(dip,mp,w)            xfs_dfork_size(dip,mp,w)
macro_line|#else
DECL|macro|XFS_DFORK_SIZE_ARCH
mdefine_line|#define&t;XFS_DFORK_SIZE_ARCH(dip,mp,w,arch)  XFS_CFORK_SIZE_ARCH(&amp;(dip)-&gt;di_core, mp, w, arch)
DECL|macro|XFS_DFORK_SIZE
mdefine_line|#define XFS_DFORK_SIZE(dip,mp,w)            XFS_DFORK_SIZE_ARCH(dip,mp,w,ARCH_NOCONVERT)
macro_line|#endif
multiline_comment|/*&n; * Macros for accessing per-fork disk inode information.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_Q)
r_int
id|xfs_dfork_q_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_int
id|xfs_dfork_q
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_Q_ARCH
mdefine_line|#define&t;XFS_DFORK_Q_ARCH(dip,arch)&t;    xfs_dfork_q_arch(dip,arch)
DECL|macro|XFS_DFORK_Q
mdefine_line|#define&t;XFS_DFORK_Q(dip)&t;            xfs_dfork_q(dip)
macro_line|#else
DECL|macro|XFS_DFORK_Q_ARCH
mdefine_line|#define&t;XFS_DFORK_Q_ARCH(dip,arch)&t;    XFS_CFORK_Q_ARCH(&amp;(dip)-&gt;di_core, arch)
DECL|macro|XFS_DFORK_Q
mdefine_line|#define XFS_DFORK_Q(dip)                    XFS_DFORK_Q_ARCH(dip,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_BOFF)
r_int
id|xfs_dfork_boff_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_int
id|xfs_dfork_boff
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_BOFF_ARCH
mdefine_line|#define&t;XFS_DFORK_BOFF_ARCH(dip,arch)&t;    xfs_dfork_boff_arch(dip,arch)
DECL|macro|XFS_DFORK_BOFF
mdefine_line|#define&t;XFS_DFORK_BOFF(dip)&t;            xfs_dfork_boff(dip)
macro_line|#else
DECL|macro|XFS_DFORK_BOFF_ARCH
mdefine_line|#define&t;XFS_DFORK_BOFF_ARCH(dip,arch)&t;    XFS_CFORK_BOFF_ARCH(&amp;(dip)-&gt;di_core, arch)
DECL|macro|XFS_DFORK_BOFF
mdefine_line|#define XFS_DFORK_BOFF(dip)                 XFS_DFORK_BOFF_ARCH(dip,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_DPTR)
r_char
op_star
id|xfs_dfork_dptr_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_DPTR_ARCH
mdefine_line|#define&t;XFS_DFORK_DPTR_ARCH(dip,arch)&t;    xfs_dfork_dptr_arch(dip,arch)
DECL|macro|XFS_DFORK_DPTR
mdefine_line|#define&t;XFS_DFORK_DPTR(dip)&t;            xfs_dfork_dptr(dip)
macro_line|#else
DECL|macro|XFS_DFORK_DPTR_ARCH
mdefine_line|#define&t;XFS_DFORK_DPTR_ARCH(dip,arch)&t;    ((dip)-&gt;di_u.di_c)
DECL|macro|XFS_DFORK_DPTR
mdefine_line|#define XFS_DFORK_DPTR(dip)                 XFS_DFORK_DPTR_ARCH(dip,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_APTR)
r_char
op_star
id|xfs_dfork_aptr_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_APTR_ARCH
mdefine_line|#define&t;XFS_DFORK_APTR_ARCH(dip,arch)       xfs_dfork_aptr_arch(dip,arch)
DECL|macro|XFS_DFORK_APTR
mdefine_line|#define&t;XFS_DFORK_APTR(dip)                 xfs_dfork_aptr(dip)
macro_line|#else
DECL|macro|XFS_DFORK_APTR_ARCH
mdefine_line|#define&t;XFS_DFORK_APTR_ARCH(dip,arch)&t;    ((dip)-&gt;di_u.di_c + XFS_DFORK_BOFF_ARCH(dip, arch))
DECL|macro|XFS_DFORK_APTR
mdefine_line|#define XFS_DFORK_APTR(dip)                 XFS_DFORK_APTR_ARCH(dip,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_PTR)
r_char
op_star
id|xfs_dfork_ptr_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_PTR_ARCH
mdefine_line|#define&t;XFS_DFORK_PTR_ARCH(dip,w,arch)      xfs_dfork_ptr_arch(dip,w,arch)
DECL|macro|XFS_DFORK_PTR
mdefine_line|#define&t;XFS_DFORK_PTR(dip,w)                xfs_dfork_ptr(dip,w)
macro_line|#else
DECL|macro|XFS_DFORK_PTR_ARCH
mdefine_line|#define&t;XFS_DFORK_PTR_ARCH(dip,w,arch)&t;&bslash;&n;&t;((w) == XFS_DATA_FORK ? XFS_DFORK_DPTR_ARCH(dip, arch) : XFS_DFORK_APTR_ARCH(dip, arch))
DECL|macro|XFS_DFORK_PTR
mdefine_line|#define XFS_DFORK_PTR(dip,w)                XFS_DFORK_PTR_ARCH(dip,w,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_FORMAT)
r_int
id|xfs_cfork_format_arch
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_CFORK_FORMAT_ARCH
mdefine_line|#define&t;XFS_CFORK_FORMAT_ARCH(dcp,w,arch)   xfs_cfork_format_arch(dcp,w,arch)
DECL|macro|XFS_CFORK_FORMAT
mdefine_line|#define&t;XFS_CFORK_FORMAT(dcp,w)             xfs_cfork_format(dcp,w)
macro_line|#else
DECL|macro|XFS_CFORK_FORMAT_ARCH
mdefine_line|#define&t;XFS_CFORK_FORMAT_ARCH(dcp,w,arch) &bslash;&n;&t;((w) == XFS_DATA_FORK ? INT_GET((dcp)-&gt;di_format, arch) : INT_GET((dcp)-&gt;di_aformat, arch))
DECL|macro|XFS_CFORK_FORMAT
mdefine_line|#define XFS_CFORK_FORMAT(dcp,w)             XFS_CFORK_FORMAT_ARCH(dcp,w,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_FMT_SET)
r_void
id|xfs_cfork_fmt_set_arch
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
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_CFORK_FMT_SET_ARCH
mdefine_line|#define&t;XFS_CFORK_FMT_SET_ARCH(dcp,w,n,arch) xfs_cfork_fmt_set_arch(dcp,w,n,arch)
DECL|macro|XFS_CFORK_FMT_SET
mdefine_line|#define&t;XFS_CFORK_FMT_SET(dcp,w,n)           xfs_cfork_fmt_set(dcp,w,n)
macro_line|#else
DECL|macro|XFS_CFORK_FMT_SET_ARCH
mdefine_line|#define&t;XFS_CFORK_FMT_SET_ARCH(dcp,w,n,arch) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;(INT_SET((dcp)-&gt;di_format, arch, (n))) : &bslash;&n;&t;&t;(INT_SET((dcp)-&gt;di_aformat, arch, (n))))
DECL|macro|XFS_CFORK_FMT_SET
mdefine_line|#define XFS_CFORK_FMT_SET(dcp,w,n)           XFS_CFORK_FMT_SET_ARCH(dcp,w,n,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_NEXTENTS)
r_int
id|xfs_cfork_nextents_arch
c_func
(paren
id|xfs_dinode_core_t
op_star
id|dcp
comma
r_int
id|w
comma
id|xfs_arch_t
id|arch
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
DECL|macro|XFS_CFORK_NEXTENTS_ARCH
mdefine_line|#define&t;XFS_CFORK_NEXTENTS_ARCH(dcp,w,arch)  xfs_cfork_nextents_arch(dcp,w,arch)
DECL|macro|XFS_CFORK_NEXTENTS
mdefine_line|#define&t;XFS_CFORK_NEXTENTS(dcp,w)            xfs_cfork_nextents(dcp,w)
macro_line|#else
DECL|macro|XFS_CFORK_NEXTENTS_ARCH
mdefine_line|#define&t;XFS_CFORK_NEXTENTS_ARCH(dcp,w,arch) &bslash;&n;&t;((w) == XFS_DATA_FORK ? INT_GET((dcp)-&gt;di_nextents, arch) : INT_GET((dcp)-&gt;di_anextents, arch))
DECL|macro|XFS_CFORK_NEXTENTS
mdefine_line|#define XFS_CFORK_NEXTENTS(dcp,w)            XFS_CFORK_NEXTENTS_ARCH(dcp,w,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CFORK_NEXT_SET)
r_void
id|xfs_cfork_next_set_arch
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
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_CFORK_NEXT_SET_ARCH
mdefine_line|#define&t;XFS_CFORK_NEXT_SET_ARCH(dcp,w,n,arch)&t;xfs_cfork_next_set_arch(dcp,w,n,arch)
DECL|macro|XFS_CFORK_NEXT_SET
mdefine_line|#define&t;XFS_CFORK_NEXT_SET(dcp,w,n)&t;        xfs_cfork_next_set(dcp,w,n)
macro_line|#else
DECL|macro|XFS_CFORK_NEXT_SET_ARCH
mdefine_line|#define&t;XFS_CFORK_NEXT_SET_ARCH(dcp,w,n,arch) &bslash;&n;&t;((w) == XFS_DATA_FORK ? &bslash;&n;&t;&t;(INT_SET((dcp)-&gt;di_nextents, arch, (n))) : &bslash;&n;&t;&t;(INT_SET((dcp)-&gt;di_anextents, arch, (n))))
DECL|macro|XFS_CFORK_NEXT_SET
mdefine_line|#define XFS_CFORK_NEXT_SET(dcp,w,n)             XFS_CFORK_NEXT_SET_ARCH(dcp,w,n,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_FORMAT)
r_int
id|xfs_dfork_format_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_int
id|xfs_dfork_format
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
DECL|macro|XFS_DFORK_FORMAT_ARCH
mdefine_line|#define&t;XFS_DFORK_FORMAT_ARCH(dip,w,arch)   xfs_dfork_format_arch(dip,w,arch)
DECL|macro|XFS_DFORK_FORMAT
mdefine_line|#define&t;XFS_DFORK_FORMAT(dip,w)             xfs_dfork_format(dip,w)
macro_line|#else
DECL|macro|XFS_DFORK_FORMAT_ARCH
mdefine_line|#define&t;XFS_DFORK_FORMAT_ARCH(dip,w,arch)   XFS_CFORK_FORMAT_ARCH(&amp;(dip)-&gt;di_core, w, arch)
DECL|macro|XFS_DFORK_FORMAT
mdefine_line|#define XFS_DFORK_FORMAT(dip,w)             XFS_DFORK_FORMAT_ARCH(dip,w,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_FMT_SET)
r_void
id|xfs_dfork_fmt_set_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
r_int
id|n
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_void
id|xfs_dfork_fmt_set
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_FMT_SET_ARCH
mdefine_line|#define&t;XFS_DFORK_FMT_SET_ARCH(dip,w,n,arch)    xfs_dfork_fmt_set_arch(dip,w,n,arch)
DECL|macro|XFS_DFORK_FMT_SET
mdefine_line|#define&t;XFS_DFORK_FMT_SET(dip,w,n)              xfs_dfork_fmt_set(dip,w,n)
macro_line|#else
DECL|macro|XFS_DFORK_FMT_SET_ARCH
mdefine_line|#define&t;XFS_DFORK_FMT_SET_ARCH(dip,w,n,arch)&t;XFS_CFORK_FMT_SET_ARCH(&amp;(dip)-&gt;di_core, w, n, arch)
DECL|macro|XFS_DFORK_FMT_SET
mdefine_line|#define XFS_DFORK_FMT_SET(dip,w,n)              XFS_DFORK_FMT_SET_ARCH(dip,w,n,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_NEXTENTS)
r_int
id|xfs_dfork_nextents_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
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
DECL|macro|XFS_DFORK_NEXTENTS_ARCH
mdefine_line|#define&t;XFS_DFORK_NEXTENTS_ARCH(dip,w,arch) xfs_dfork_nextents_arch(dip,w,arch)
DECL|macro|XFS_DFORK_NEXTENTS
mdefine_line|#define&t;XFS_DFORK_NEXTENTS(dip,w)           xfs_dfork_nextents(dip,w)
macro_line|#else
DECL|macro|XFS_DFORK_NEXTENTS_ARCH
mdefine_line|#define&t;XFS_DFORK_NEXTENTS_ARCH(dip,w,arch) XFS_CFORK_NEXTENTS_ARCH(&amp;(dip)-&gt;di_core, w, arch)
DECL|macro|XFS_DFORK_NEXTENTS
mdefine_line|#define XFS_DFORK_NEXTENTS(dip,w)           XFS_DFORK_NEXTENTS_ARCH(dip,w,ARCH_NOCONVERT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DFORK_NEXT_SET)
r_void
id|xfs_dfork_next_set_arch
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
r_int
id|n
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
r_void
id|xfs_dfork_next_set
c_func
(paren
id|xfs_dinode_t
op_star
id|dip
comma
r_int
id|w
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_DFORK_NEXT_SET_ARCH
mdefine_line|#define&t;XFS_DFORK_NEXT_SET_ARCH(dip,w,n,arch)   xfs_dfork_next_set_arch(dip,w,n,arch)
DECL|macro|XFS_DFORK_NEXT_SET
mdefine_line|#define&t;XFS_DFORK_NEXT_SET(dip,w,n)             xfs_dfork_next_set(dip,w,n)
macro_line|#else
DECL|macro|XFS_DFORK_NEXT_SET_ARCH
mdefine_line|#define&t;XFS_DFORK_NEXT_SET_ARCH(dip,w,n,arch)&t;XFS_CFORK_NEXT_SET_ARCH(&amp;(dip)-&gt;di_core, w, n, arch)
DECL|macro|XFS_DFORK_NEXT_SET
mdefine_line|#define XFS_DFORK_NEXT_SET(dip,w,n)             XFS_DFORK_NEXT_SET_ARCH(dip,w,n,ARCH_NOCONVERT)
macro_line|#endif
multiline_comment|/*&n; * File types (mode field)&n; */
DECL|macro|IFMT
mdefine_line|#define&t;IFMT&t;&t;0170000&t;&t;/* type of file */
DECL|macro|IFIFO
mdefine_line|#define&t;IFIFO&t;&t;0010000&t;&t;/* named pipe (fifo) */
DECL|macro|IFCHR
mdefine_line|#define&t;IFCHR&t;&t;0020000&t;&t;/* character special */
DECL|macro|IFDIR
mdefine_line|#define&t;IFDIR&t;&t;0040000&t;&t;/* directory */
DECL|macro|IFBLK
mdefine_line|#define&t;IFBLK&t;&t;0060000&t;&t;/* block special */
DECL|macro|IFREG
mdefine_line|#define&t;IFREG&t;&t;0100000&t;&t;/* regular */
DECL|macro|IFLNK
mdefine_line|#define&t;IFLNK&t;&t;0120000&t;&t;/* symbolic link */
DECL|macro|IFSOCK
mdefine_line|#define&t;IFSOCK&t;&t;0140000&t;&t;/* socket */
DECL|macro|IFMNT
mdefine_line|#define&t;IFMNT&t;&t;0160000&t;&t;/* mount point */
multiline_comment|/*&n; * File execution and access modes.&n; */
DECL|macro|ISUID
mdefine_line|#define&t;ISUID&t;&t;04000&t;&t;/* set user id on execution */
DECL|macro|ISGID
mdefine_line|#define&t;ISGID&t;&t;02000&t;&t;/* set group id on execution */
DECL|macro|ISVTX
mdefine_line|#define&t;ISVTX&t;&t;01000&t;&t;/* sticky directory */
DECL|macro|IREAD
mdefine_line|#define&t;IREAD&t;&t;0400&t;&t;/* read, write, execute permissions */
DECL|macro|IWRITE
mdefine_line|#define&t;IWRITE&t;&t;0200
DECL|macro|IEXEC
mdefine_line|#define&t;IEXEC&t;&t;0100
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
mdefine_line|#define XFS_DIFLAG_REALTIME_BIT&t;0&t;/* file&squot;s blocks come from rt area */
DECL|macro|XFS_DIFLAG_PREALLOC_BIT
mdefine_line|#define XFS_DIFLAG_PREALLOC_BIT&t;1&t;/* file space has been preallocated */
DECL|macro|XFS_DIFLAG_NEWRTBM_BIT
mdefine_line|#define&t;XFS_DIFLAG_NEWRTBM_BIT&t;2&t;/* for rtbitmap inode, new format */
DECL|macro|XFS_DIFLAG_REALTIME
mdefine_line|#define XFS_DIFLAG_REALTIME     (1 &lt;&lt; XFS_DIFLAG_REALTIME_BIT)
DECL|macro|XFS_DIFLAG_PREALLOC
mdefine_line|#define XFS_DIFLAG_PREALLOC&t;(1 &lt;&lt; XFS_DIFLAG_PREALLOC_BIT)
DECL|macro|XFS_DIFLAG_NEWRTBM
mdefine_line|#define&t;XFS_DIFLAG_NEWRTBM&t;(1 &lt;&lt; XFS_DIFLAG_NEWRTBM_BIT)
DECL|macro|XFS_DIFLAG_ALL
mdefine_line|#define XFS_DIFLAG_ALL  &bslash;&n;&t;(XFS_DIFLAG_REALTIME|XFS_DIFLAG_PREALLOC|XFS_DIFLAG_NEWRTBM)
macro_line|#endif&t;/* __XFS_DINODE_H__ */
eof
