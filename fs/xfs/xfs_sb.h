multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SB_H__
DECL|macro|__XFS_SB_H__
mdefine_line|#define&t;__XFS_SB_H__
multiline_comment|/*&n; * Super block&n; * Fits into a sector-sized buffer at address 0 of each allocation group.&n; * Only the first of these is ever updated except during growfs.&n; */
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
DECL|macro|XFS_SB_MAGIC
mdefine_line|#define&t;XFS_SB_MAGIC&t;&t;0x58465342&t;/* &squot;XFSB&squot; */
DECL|macro|XFS_SB_VERSION_1
mdefine_line|#define&t;XFS_SB_VERSION_1&t;1&t;&t;/* 5.3, 6.0.1, 6.1 */
DECL|macro|XFS_SB_VERSION_2
mdefine_line|#define&t;XFS_SB_VERSION_2&t;2&t;&t;/* 6.2 - attributes */
DECL|macro|XFS_SB_VERSION_3
mdefine_line|#define&t;XFS_SB_VERSION_3&t;3&t;&t;/* 6.2 - new inode version */
DECL|macro|XFS_SB_VERSION_4
mdefine_line|#define&t;XFS_SB_VERSION_4&t;4&t;&t;/* 6.2+ - bitmask version */
DECL|macro|XFS_SB_VERSION_NUMBITS
mdefine_line|#define&t;XFS_SB_VERSION_NUMBITS&t;&t;0x000f
DECL|macro|XFS_SB_VERSION_ALLFBITS
mdefine_line|#define&t;XFS_SB_VERSION_ALLFBITS&t;&t;0xfff0
DECL|macro|XFS_SB_VERSION_SASHFBITS
mdefine_line|#define&t;XFS_SB_VERSION_SASHFBITS&t;0xf000
DECL|macro|XFS_SB_VERSION_REALFBITS
mdefine_line|#define&t;XFS_SB_VERSION_REALFBITS&t;0x0ff0
DECL|macro|XFS_SB_VERSION_ATTRBIT
mdefine_line|#define&t;XFS_SB_VERSION_ATTRBIT&t;&t;0x0010
DECL|macro|XFS_SB_VERSION_NLINKBIT
mdefine_line|#define&t;XFS_SB_VERSION_NLINKBIT&t;&t;0x0020
DECL|macro|XFS_SB_VERSION_QUOTABIT
mdefine_line|#define&t;XFS_SB_VERSION_QUOTABIT&t;&t;0x0040
DECL|macro|XFS_SB_VERSION_ALIGNBIT
mdefine_line|#define&t;XFS_SB_VERSION_ALIGNBIT&t;&t;0x0080
DECL|macro|XFS_SB_VERSION_DALIGNBIT
mdefine_line|#define&t;XFS_SB_VERSION_DALIGNBIT&t;0x0100
DECL|macro|XFS_SB_VERSION_SHAREDBIT
mdefine_line|#define&t;XFS_SB_VERSION_SHAREDBIT&t;0x0200
DECL|macro|XFS_SB_VERSION_LOGV2BIT
mdefine_line|#define XFS_SB_VERSION_LOGV2BIT&t;&t;0x0400
DECL|macro|XFS_SB_VERSION_SECTORBIT
mdefine_line|#define XFS_SB_VERSION_SECTORBIT&t;0x0800
DECL|macro|XFS_SB_VERSION_EXTFLGBIT
mdefine_line|#define&t;XFS_SB_VERSION_EXTFLGBIT&t;0x1000
DECL|macro|XFS_SB_VERSION_DIRV2BIT
mdefine_line|#define&t;XFS_SB_VERSION_DIRV2BIT&t;&t;0x2000
DECL|macro|XFS_SB_VERSION_OKSASHFBITS
mdefine_line|#define&t;XFS_SB_VERSION_OKSASHFBITS&t;&bslash;&n;&t;(XFS_SB_VERSION_EXTFLGBIT | &bslash;&n;&t; XFS_SB_VERSION_DIRV2BIT)
DECL|macro|XFS_SB_VERSION_OKREALFBITS
mdefine_line|#define&t;XFS_SB_VERSION_OKREALFBITS&t;&bslash;&n;&t;(XFS_SB_VERSION_ATTRBIT | &bslash;&n;&t; XFS_SB_VERSION_NLINKBIT | &bslash;&n;&t; XFS_SB_VERSION_QUOTABIT | &bslash;&n;&t; XFS_SB_VERSION_ALIGNBIT | &bslash;&n;&t; XFS_SB_VERSION_DALIGNBIT | &bslash;&n;&t; XFS_SB_VERSION_SHAREDBIT | &bslash;&n;&t; XFS_SB_VERSION_LOGV2BIT | &bslash;&n;&t; XFS_SB_VERSION_SECTORBIT)
DECL|macro|XFS_SB_VERSION_OKSASHBITS
mdefine_line|#define&t;XFS_SB_VERSION_OKSASHBITS&t;&bslash;&n;&t;(XFS_SB_VERSION_NUMBITS | &bslash;&n;&t; XFS_SB_VERSION_REALFBITS | &bslash;&n;&t; XFS_SB_VERSION_OKSASHFBITS)
DECL|macro|XFS_SB_VERSION_OKREALBITS
mdefine_line|#define&t;XFS_SB_VERSION_OKREALBITS&t;&bslash;&n;&t;(XFS_SB_VERSION_NUMBITS | &bslash;&n;&t; XFS_SB_VERSION_OKREALFBITS | &bslash;&n;&t; XFS_SB_VERSION_OKSASHFBITS)
DECL|macro|XFS_SB_VERSION_MKFS
mdefine_line|#define XFS_SB_VERSION_MKFS(ia,dia,extflag,dirv2,na,sflag)&t;&bslash;&n;&t;(((ia) || (dia) || (extflag) || (dirv2) || (na) || (sflag)) ? &bslash;&n;&t;&t;(XFS_SB_VERSION_4 | &bslash;&n;&t;&t; ((ia) ? XFS_SB_VERSION_ALIGNBIT : 0) | &bslash;&n;&t;&t; ((dia) ? XFS_SB_VERSION_DALIGNBIT : 0) | &bslash;&n;&t;&t; ((extflag) ? XFS_SB_VERSION_EXTFLGBIT : 0) | &bslash;&n;&t;&t; ((dirv2) ? XFS_SB_VERSION_DIRV2BIT : 0) | &bslash;&n;&t;&t; ((na) ? XFS_SB_VERSION_LOGV2BIT : 0) | &bslash;&n;&t;&t; ((sflag) ? XFS_SB_VERSION_SECTORBIT : 0)) : &bslash;&n;&t;&t;XFS_SB_VERSION_1)
DECL|struct|xfs_sb
r_typedef
r_struct
id|xfs_sb
(brace
DECL|member|sb_magicnum
id|__uint32_t
id|sb_magicnum
suffix:semicolon
multiline_comment|/* magic number == XFS_SB_MAGIC */
DECL|member|sb_blocksize
id|__uint32_t
id|sb_blocksize
suffix:semicolon
multiline_comment|/* logical block size, bytes */
DECL|member|sb_dblocks
id|xfs_drfsbno_t
id|sb_dblocks
suffix:semicolon
multiline_comment|/* number of data blocks */
DECL|member|sb_rblocks
id|xfs_drfsbno_t
id|sb_rblocks
suffix:semicolon
multiline_comment|/* number of realtime blocks */
DECL|member|sb_rextents
id|xfs_drtbno_t
id|sb_rextents
suffix:semicolon
multiline_comment|/* number of realtime extents */
DECL|member|sb_uuid
id|uuid_t
id|sb_uuid
suffix:semicolon
multiline_comment|/* file system unique id */
DECL|member|sb_logstart
id|xfs_dfsbno_t
id|sb_logstart
suffix:semicolon
multiline_comment|/* starting block of log if internal */
DECL|member|sb_rootino
id|xfs_ino_t
id|sb_rootino
suffix:semicolon
multiline_comment|/* root inode number */
DECL|member|sb_rbmino
id|xfs_ino_t
id|sb_rbmino
suffix:semicolon
multiline_comment|/* bitmap inode for realtime extents */
DECL|member|sb_rsumino
id|xfs_ino_t
id|sb_rsumino
suffix:semicolon
multiline_comment|/* summary inode for rt bitmap */
DECL|member|sb_rextsize
id|xfs_agblock_t
id|sb_rextsize
suffix:semicolon
multiline_comment|/* realtime extent size, blocks */
DECL|member|sb_agblocks
id|xfs_agblock_t
id|sb_agblocks
suffix:semicolon
multiline_comment|/* size of an allocation group */
DECL|member|sb_agcount
id|xfs_agnumber_t
id|sb_agcount
suffix:semicolon
multiline_comment|/* number of allocation groups */
DECL|member|sb_rbmblocks
id|xfs_extlen_t
id|sb_rbmblocks
suffix:semicolon
multiline_comment|/* number of rt bitmap blocks */
DECL|member|sb_logblocks
id|xfs_extlen_t
id|sb_logblocks
suffix:semicolon
multiline_comment|/* number of log blocks */
DECL|member|sb_versionnum
id|__uint16_t
id|sb_versionnum
suffix:semicolon
multiline_comment|/* header version == XFS_SB_VERSION */
DECL|member|sb_sectsize
id|__uint16_t
id|sb_sectsize
suffix:semicolon
multiline_comment|/* volume sector size, bytes */
DECL|member|sb_inodesize
id|__uint16_t
id|sb_inodesize
suffix:semicolon
multiline_comment|/* inode size, bytes */
DECL|member|sb_inopblock
id|__uint16_t
id|sb_inopblock
suffix:semicolon
multiline_comment|/* inodes per block */
DECL|member|sb_fname
r_char
id|sb_fname
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* file system name */
DECL|member|sb_blocklog
id|__uint8_t
id|sb_blocklog
suffix:semicolon
multiline_comment|/* log2 of sb_blocksize */
DECL|member|sb_sectlog
id|__uint8_t
id|sb_sectlog
suffix:semicolon
multiline_comment|/* log2 of sb_sectsize */
DECL|member|sb_inodelog
id|__uint8_t
id|sb_inodelog
suffix:semicolon
multiline_comment|/* log2 of sb_inodesize */
DECL|member|sb_inopblog
id|__uint8_t
id|sb_inopblog
suffix:semicolon
multiline_comment|/* log2 of sb_inopblock */
DECL|member|sb_agblklog
id|__uint8_t
id|sb_agblklog
suffix:semicolon
multiline_comment|/* log2 of sb_agblocks (rounded up) */
DECL|member|sb_rextslog
id|__uint8_t
id|sb_rextslog
suffix:semicolon
multiline_comment|/* log2 of sb_rextents */
DECL|member|sb_inprogress
id|__uint8_t
id|sb_inprogress
suffix:semicolon
multiline_comment|/* mkfs is in progress, don&squot;t mount */
DECL|member|sb_imax_pct
id|__uint8_t
id|sb_imax_pct
suffix:semicolon
multiline_comment|/* max % of fs for inode space */
multiline_comment|/* statistics */
multiline_comment|/*&n;&t; * These fields must remain contiguous.  If you really&n;&t; * want to change their layout, make sure you fix the&n;&t; * code in xfs_trans_apply_sb_deltas().&n;&t; */
DECL|member|sb_icount
id|__uint64_t
id|sb_icount
suffix:semicolon
multiline_comment|/* allocated inodes */
DECL|member|sb_ifree
id|__uint64_t
id|sb_ifree
suffix:semicolon
multiline_comment|/* free inodes */
DECL|member|sb_fdblocks
id|__uint64_t
id|sb_fdblocks
suffix:semicolon
multiline_comment|/* free data blocks */
DECL|member|sb_frextents
id|__uint64_t
id|sb_frextents
suffix:semicolon
multiline_comment|/* free realtime extents */
multiline_comment|/*&n;&t; * End contiguous fields.&n;&t; */
DECL|member|sb_uquotino
id|xfs_ino_t
id|sb_uquotino
suffix:semicolon
multiline_comment|/* user quota inode */
DECL|member|sb_gquotino
id|xfs_ino_t
id|sb_gquotino
suffix:semicolon
multiline_comment|/* group quota inode */
DECL|member|sb_qflags
id|__uint16_t
id|sb_qflags
suffix:semicolon
multiline_comment|/* quota flags */
DECL|member|sb_flags
id|__uint8_t
id|sb_flags
suffix:semicolon
multiline_comment|/* misc. flags */
DECL|member|sb_shared_vn
id|__uint8_t
id|sb_shared_vn
suffix:semicolon
multiline_comment|/* shared version number */
DECL|member|sb_inoalignmt
id|xfs_extlen_t
id|sb_inoalignmt
suffix:semicolon
multiline_comment|/* inode chunk alignment, fsblocks */
DECL|member|sb_unit
id|__uint32_t
id|sb_unit
suffix:semicolon
multiline_comment|/* stripe or raid unit */
DECL|member|sb_width
id|__uint32_t
id|sb_width
suffix:semicolon
multiline_comment|/* stripe or raid width */
DECL|member|sb_dirblklog
id|__uint8_t
id|sb_dirblklog
suffix:semicolon
multiline_comment|/* log2 of dir block size (fsbs) */
DECL|member|sb_logsectlog
id|__uint8_t
id|sb_logsectlog
suffix:semicolon
multiline_comment|/* log2 of the log sector size */
DECL|member|sb_logsectsize
id|__uint16_t
id|sb_logsectsize
suffix:semicolon
multiline_comment|/* sector size for the log, bytes */
DECL|member|sb_logsunit
id|__uint32_t
id|sb_logsunit
suffix:semicolon
multiline_comment|/* stripe unit size for the log */
DECL|typedef|xfs_sb_t
)brace
id|xfs_sb_t
suffix:semicolon
multiline_comment|/*&n; * Sequence number values for the fields.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|XFS_SBS_MAGICNUM
DECL|enumerator|XFS_SBS_BLOCKSIZE
DECL|enumerator|XFS_SBS_DBLOCKS
DECL|enumerator|XFS_SBS_RBLOCKS
id|XFS_SBS_MAGICNUM
comma
id|XFS_SBS_BLOCKSIZE
comma
id|XFS_SBS_DBLOCKS
comma
id|XFS_SBS_RBLOCKS
comma
DECL|enumerator|XFS_SBS_REXTENTS
DECL|enumerator|XFS_SBS_UUID
DECL|enumerator|XFS_SBS_LOGSTART
DECL|enumerator|XFS_SBS_ROOTINO
id|XFS_SBS_REXTENTS
comma
id|XFS_SBS_UUID
comma
id|XFS_SBS_LOGSTART
comma
id|XFS_SBS_ROOTINO
comma
DECL|enumerator|XFS_SBS_RBMINO
DECL|enumerator|XFS_SBS_RSUMINO
DECL|enumerator|XFS_SBS_REXTSIZE
DECL|enumerator|XFS_SBS_AGBLOCKS
id|XFS_SBS_RBMINO
comma
id|XFS_SBS_RSUMINO
comma
id|XFS_SBS_REXTSIZE
comma
id|XFS_SBS_AGBLOCKS
comma
DECL|enumerator|XFS_SBS_AGCOUNT
DECL|enumerator|XFS_SBS_RBMBLOCKS
DECL|enumerator|XFS_SBS_LOGBLOCKS
id|XFS_SBS_AGCOUNT
comma
id|XFS_SBS_RBMBLOCKS
comma
id|XFS_SBS_LOGBLOCKS
comma
DECL|enumerator|XFS_SBS_VERSIONNUM
DECL|enumerator|XFS_SBS_SECTSIZE
DECL|enumerator|XFS_SBS_INODESIZE
id|XFS_SBS_VERSIONNUM
comma
id|XFS_SBS_SECTSIZE
comma
id|XFS_SBS_INODESIZE
comma
DECL|enumerator|XFS_SBS_INOPBLOCK
DECL|enumerator|XFS_SBS_FNAME
DECL|enumerator|XFS_SBS_BLOCKLOG
id|XFS_SBS_INOPBLOCK
comma
id|XFS_SBS_FNAME
comma
id|XFS_SBS_BLOCKLOG
comma
DECL|enumerator|XFS_SBS_SECTLOG
DECL|enumerator|XFS_SBS_INODELOG
DECL|enumerator|XFS_SBS_INOPBLOG
DECL|enumerator|XFS_SBS_AGBLKLOG
id|XFS_SBS_SECTLOG
comma
id|XFS_SBS_INODELOG
comma
id|XFS_SBS_INOPBLOG
comma
id|XFS_SBS_AGBLKLOG
comma
DECL|enumerator|XFS_SBS_REXTSLOG
DECL|enumerator|XFS_SBS_INPROGRESS
DECL|enumerator|XFS_SBS_IMAX_PCT
DECL|enumerator|XFS_SBS_ICOUNT
id|XFS_SBS_REXTSLOG
comma
id|XFS_SBS_INPROGRESS
comma
id|XFS_SBS_IMAX_PCT
comma
id|XFS_SBS_ICOUNT
comma
DECL|enumerator|XFS_SBS_IFREE
DECL|enumerator|XFS_SBS_FDBLOCKS
DECL|enumerator|XFS_SBS_FREXTENTS
DECL|enumerator|XFS_SBS_UQUOTINO
id|XFS_SBS_IFREE
comma
id|XFS_SBS_FDBLOCKS
comma
id|XFS_SBS_FREXTENTS
comma
id|XFS_SBS_UQUOTINO
comma
DECL|enumerator|XFS_SBS_GQUOTINO
DECL|enumerator|XFS_SBS_QFLAGS
DECL|enumerator|XFS_SBS_FLAGS
DECL|enumerator|XFS_SBS_SHARED_VN
id|XFS_SBS_GQUOTINO
comma
id|XFS_SBS_QFLAGS
comma
id|XFS_SBS_FLAGS
comma
id|XFS_SBS_SHARED_VN
comma
DECL|enumerator|XFS_SBS_INOALIGNMT
DECL|enumerator|XFS_SBS_UNIT
DECL|enumerator|XFS_SBS_WIDTH
DECL|enumerator|XFS_SBS_DIRBLKLOG
id|XFS_SBS_INOALIGNMT
comma
id|XFS_SBS_UNIT
comma
id|XFS_SBS_WIDTH
comma
id|XFS_SBS_DIRBLKLOG
comma
DECL|enumerator|XFS_SBS_LOGSECTLOG
DECL|enumerator|XFS_SBS_LOGSECTSIZE
DECL|enumerator|XFS_SBS_LOGSUNIT
id|XFS_SBS_LOGSECTLOG
comma
id|XFS_SBS_LOGSECTSIZE
comma
id|XFS_SBS_LOGSUNIT
comma
DECL|enumerator|XFS_SBS_FIELDCOUNT
id|XFS_SBS_FIELDCOUNT
DECL|typedef|xfs_sb_field_t
)brace
id|xfs_sb_field_t
suffix:semicolon
multiline_comment|/*&n; * Mask values, defined based on the xfs_sb_field_t values.&n; * Only define the ones we&squot;re using.&n; */
DECL|macro|XFS_SB_MVAL
mdefine_line|#define&t;XFS_SB_MVAL(x)&t;&t;(1LL &lt;&lt; XFS_SBS_ ## x)
DECL|macro|XFS_SB_UUID
mdefine_line|#define&t;XFS_SB_UUID&t;&t;XFS_SB_MVAL(UUID)
DECL|macro|XFS_SB_FNAME
mdefine_line|#define&t;XFS_SB_FNAME&t;&t;XFS_SB_MVAL(FNAME)
DECL|macro|XFS_SB_ROOTINO
mdefine_line|#define&t;XFS_SB_ROOTINO&t;&t;XFS_SB_MVAL(ROOTINO)
DECL|macro|XFS_SB_RBMINO
mdefine_line|#define&t;XFS_SB_RBMINO&t;&t;XFS_SB_MVAL(RBMINO)
DECL|macro|XFS_SB_RSUMINO
mdefine_line|#define&t;XFS_SB_RSUMINO&t;&t;XFS_SB_MVAL(RSUMINO)
DECL|macro|XFS_SB_VERSIONNUM
mdefine_line|#define&t;XFS_SB_VERSIONNUM&t;XFS_SB_MVAL(VERSIONNUM)
DECL|macro|XFS_SB_UQUOTINO
mdefine_line|#define XFS_SB_UQUOTINO&t;&t;XFS_SB_MVAL(UQUOTINO)
DECL|macro|XFS_SB_GQUOTINO
mdefine_line|#define XFS_SB_GQUOTINO&t;&t;XFS_SB_MVAL(GQUOTINO)
DECL|macro|XFS_SB_QFLAGS
mdefine_line|#define XFS_SB_QFLAGS&t;&t;XFS_SB_MVAL(QFLAGS)
DECL|macro|XFS_SB_SHARED_VN
mdefine_line|#define XFS_SB_SHARED_VN&t;XFS_SB_MVAL(SHARED_VN)
DECL|macro|XFS_SB_UNIT
mdefine_line|#define XFS_SB_UNIT&t;&t;XFS_SB_MVAL(UNIT)
DECL|macro|XFS_SB_WIDTH
mdefine_line|#define XFS_SB_WIDTH&t;&t;XFS_SB_MVAL(WIDTH)
DECL|macro|XFS_SB_NUM_BITS
mdefine_line|#define&t;XFS_SB_NUM_BITS&t;&t;((int)XFS_SBS_FIELDCOUNT)
DECL|macro|XFS_SB_ALL_BITS
mdefine_line|#define&t;XFS_SB_ALL_BITS&t;&t;((1LL &lt;&lt; XFS_SB_NUM_BITS) - 1)
DECL|macro|XFS_SB_MOD_BITS
mdefine_line|#define&t;XFS_SB_MOD_BITS&t;&t;&bslash;&n;&t;(XFS_SB_UUID | XFS_SB_ROOTINO | XFS_SB_RBMINO | XFS_SB_RSUMINO | &bslash;&n;&t; XFS_SB_VERSIONNUM | XFS_SB_UQUOTINO | XFS_SB_GQUOTINO | &bslash;&n;&t; XFS_SB_QFLAGS | XFS_SB_SHARED_VN | XFS_SB_UNIT | XFS_SB_WIDTH)
multiline_comment|/*&n; * Misc. Flags - warning - these will be cleared by xfs_repair unless&n; * a feature bit is set when the flag is used.&n; */
DECL|macro|XFS_SBF_NOFLAGS
mdefine_line|#define XFS_SBF_NOFLAGS&t;&t;0x00&t;/* no flags set */
DECL|macro|XFS_SBF_READONLY
mdefine_line|#define XFS_SBF_READONLY&t;0x01&t;/* only read-only mounts allowed */
multiline_comment|/*&n; * define max. shared version we can interoperate with&n; */
DECL|macro|XFS_SB_MAX_SHARED_VN
mdefine_line|#define XFS_SB_MAX_SHARED_VN&t;0
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_NUM)
r_int
id|xfs_sb_version_num
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_NUM
mdefine_line|#define&t;XFS_SB_VERSION_NUM(sbp)&t;xfs_sb_version_num(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_NUM
mdefine_line|#define&t;XFS_SB_VERSION_NUM(sbp)&t;((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_NUMBITS)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_GOOD_VERSION)
r_int
id|xfs_sb_good_version
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_GOOD_VERSION
mdefine_line|#define&t;XFS_SB_GOOD_VERSION(sbp)&t;xfs_sb_good_version(sbp)
macro_line|#else
DECL|macro|XFS_SB_GOOD_VERSION_INT
mdefine_line|#define&t;XFS_SB_GOOD_VERSION_INT(sbp)&t;&bslash;&n;&t;((((sbp)-&gt;sb_versionnum &gt;= XFS_SB_VERSION_1) &amp;&amp; &bslash;&n;&t;  ((sbp)-&gt;sb_versionnum &lt;= XFS_SB_VERSION_3)) || &bslash;&n;&t; ((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;  !((sbp)-&gt;sb_versionnum &amp; ~XFS_SB_VERSION_OKREALBITS)
macro_line|#ifdef __KERNEL__
DECL|macro|XFS_SB_GOOD_VERSION
mdefine_line|#define&t;XFS_SB_GOOD_VERSION(sbp)&t;&bslash;&n;&t;(XFS_SB_GOOD_VERSION_INT(sbp) &amp;&amp; &bslash;&n;&t;  (sbp)-&gt;sb_shared_vn &lt;= XFS_SB_MAX_SHARED_VN) ))
macro_line|#else
multiline_comment|/*&n; * extra 2 paren&squot;s here (( to unconfuse paren-matching editors&n; * like vi because XFS_SB_GOOD_VERSION_INT is a partial expression&n; * and the two XFS_SB_GOOD_VERSION&squot;s each 2 more close paren&squot;s to&n; * complete the expression.&n; */
DECL|macro|XFS_SB_GOOD_VERSION
mdefine_line|#define XFS_SB_GOOD_VERSION(sbp)&t;&bslash;&n;&t;(XFS_SB_GOOD_VERSION_INT(sbp) &amp;&amp; &bslash;&n;&t;  (!((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_SHAREDBIT) || &bslash;&n;&t;   (sbp)-&gt;sb_shared_vn &lt;= XFS_SB_MAX_SHARED_VN)) ))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
DECL|macro|XFS_SB_GOOD_SASH_VERSION
mdefine_line|#define&t;XFS_SB_GOOD_SASH_VERSION(sbp)&t;&bslash;&n;&t;((((sbp)-&gt;sb_versionnum &gt;= XFS_SB_VERSION_1) &amp;&amp; &bslash;&n;&t;  ((sbp)-&gt;sb_versionnum &lt;= XFS_SB_VERSION_3)) || &bslash;&n;&t; ((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;  !((sbp)-&gt;sb_versionnum &amp; ~XFS_SB_VERSION_OKSASHBITS)))
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_TONEW)
r_int
id|xfs_sb_version_tonew
c_func
(paren
r_int
id|v
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_TONEW
mdefine_line|#define&t;XFS_SB_VERSION_TONEW(v)&t;xfs_sb_version_tonew(v)
macro_line|#else
DECL|macro|XFS_SB_VERSION_TONEW
mdefine_line|#define&t;XFS_SB_VERSION_TONEW(v)&t;&bslash;&n;&t;((((v) == XFS_SB_VERSION_1) ? &bslash;&n;&t;&t;0 : &bslash;&n;&t;&t;(((v) == XFS_SB_VERSION_2) ? &bslash;&n;&t;&t;&t;XFS_SB_VERSION_ATTRBIT : &bslash;&n;&t;&t;&t;(XFS_SB_VERSION_ATTRBIT | XFS_SB_VERSION_NLINKBIT))) | &bslash;&n;&t; XFS_SB_VERSION_4)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_TOOLD)
r_int
id|xfs_sb_version_toold
c_func
(paren
r_int
id|v
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_TOOLD
mdefine_line|#define&t;XFS_SB_VERSION_TOOLD(v)&t;xfs_sb_version_toold(v)
macro_line|#else
DECL|macro|XFS_SB_VERSION_TOOLD
mdefine_line|#define&t;XFS_SB_VERSION_TOOLD(v)&t;&bslash;&n;&t;(((v) &amp; (XFS_SB_VERSION_QUOTABIT | XFS_SB_VERSION_ALIGNBIT)) ? &bslash;&n;&t;&t;0 : &bslash;&n;&t;&t;(((v) &amp; XFS_SB_VERSION_NLINKBIT) ? &bslash;&n;&t;&t;&t;XFS_SB_VERSION_3 : &bslash;&n;&t;&t;&t;(((v) &amp; XFS_SB_VERSION_ATTRBIT) ?  &bslash;&n;&t;&t;&t;&t;XFS_SB_VERSION_2 : &bslash;&n;&t;&t;&t;&t;XFS_SB_VERSION_1)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASATTR)
r_int
id|xfs_sb_version_hasattr
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASATTR
mdefine_line|#define&t;XFS_SB_VERSION_HASATTR(sbp)&t;xfs_sb_version_hasattr(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASATTR
mdefine_line|#define&t;XFS_SB_VERSION_HASATTR(sbp)&t;&bslash;&n;&t;(((sbp)-&gt;sb_versionnum == XFS_SB_VERSION_2) || &bslash;&n;&t; ((sbp)-&gt;sb_versionnum == XFS_SB_VERSION_3) || &bslash;&n;&t; ((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;  ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_ATTRBIT)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDATTR)
r_void
id|xfs_sb_version_addattr
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDATTR
mdefine_line|#define&t;XFS_SB_VERSION_ADDATTR(sbp)&t;xfs_sb_version_addattr(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDATTR
mdefine_line|#define&t;XFS_SB_VERSION_ADDATTR(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t; (((sbp)-&gt;sb_versionnum == XFS_SB_VERSION_1) ? &bslash;&n;&t;&t;XFS_SB_VERSION_2 : &bslash;&n;&t;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) ? &bslash;&n;&t;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_ATTRBIT) : &bslash;&n;&t;&t;&t;(XFS_SB_VERSION_4 | XFS_SB_VERSION_ATTRBIT))))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASNLINK)
r_int
id|xfs_sb_version_hasnlink
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASNLINK
mdefine_line|#define&t;XFS_SB_VERSION_HASNLINK(sbp)&t;xfs_sb_version_hasnlink(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASNLINK
mdefine_line|#define&t;XFS_SB_VERSION_HASNLINK(sbp)&t;&bslash;&n;&t;(((sbp)-&gt;sb_versionnum == XFS_SB_VERSION_3) || &bslash;&n;&t; ((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;  ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_NLINKBIT)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDNLINK)
r_void
id|xfs_sb_version_addnlink
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDNLINK
mdefine_line|#define&t;XFS_SB_VERSION_ADDNLINK(sbp)&t;xfs_sb_version_addnlink(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDNLINK
mdefine_line|#define&t;XFS_SB_VERSION_ADDNLINK(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &lt;= XFS_SB_VERSION_2 ? &bslash;&n;&t;&t;XFS_SB_VERSION_3 : &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_NLINKBIT)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASQUOTA)
r_int
id|xfs_sb_version_hasquota
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASQUOTA
mdefine_line|#define&t;XFS_SB_VERSION_HASQUOTA(sbp)&t;xfs_sb_version_hasquota(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASQUOTA
mdefine_line|#define&t;XFS_SB_VERSION_HASQUOTA(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_QUOTABIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDQUOTA)
r_void
id|xfs_sb_version_addquota
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDQUOTA
mdefine_line|#define&t;XFS_SB_VERSION_ADDQUOTA(sbp)&t;xfs_sb_version_addquota(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDQUOTA
mdefine_line|#define&t;XFS_SB_VERSION_ADDQUOTA(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t; (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4 ? &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_QUOTABIT) : &bslash;&n;&t;&t;(XFS_SB_VERSION_TONEW((sbp)-&gt;sb_versionnum) | &bslash;&n;&t;&t; XFS_SB_VERSION_QUOTABIT)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASALIGN)
r_int
id|xfs_sb_version_hasalign
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASALIGN
mdefine_line|#define&t;XFS_SB_VERSION_HASALIGN(sbp)&t;xfs_sb_version_hasalign(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASALIGN
mdefine_line|#define&t;XFS_SB_VERSION_HASALIGN(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_ALIGNBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_SUBALIGN)
r_void
id|xfs_sb_version_subalign
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_SUBALIGN
mdefine_line|#define&t;XFS_SB_VERSION_SUBALIGN(sbp)&t;xfs_sb_version_subalign(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_SUBALIGN
mdefine_line|#define&t;XFS_SB_VERSION_SUBALIGN(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t; XFS_SB_VERSION_TOOLD((sbp)-&gt;sb_versionnum &amp; ~XFS_SB_VERSION_ALIGNBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASDALIGN)
r_int
id|xfs_sb_version_hasdalign
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASDALIGN
mdefine_line|#define XFS_SB_VERSION_HASDALIGN(sbp)&t;xfs_sb_version_hasdalign(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASDALIGN
mdefine_line|#define XFS_SB_VERSION_HASDALIGN(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_DALIGNBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDDALIGN)
r_int
id|xfs_sb_version_adddalign
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDDALIGN
mdefine_line|#define XFS_SB_VERSION_ADDDALIGN(sbp)&t;xfs_sb_version_adddalign(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDDALIGN
mdefine_line|#define XFS_SB_VERSION_ADDDALIGN(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_DALIGNBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASSHARED)
r_int
id|xfs_sb_version_hasshared
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASSHARED
mdefine_line|#define XFS_SB_VERSION_HASSHARED(sbp)&t;xfs_sb_version_hasshared(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASSHARED
mdefine_line|#define XFS_SB_VERSION_HASSHARED(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_SHAREDBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDSHARED)
r_int
id|xfs_sb_version_addshared
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDSHARED
mdefine_line|#define XFS_SB_VERSION_ADDSHARED(sbp)&t;xfs_sb_version_addshared(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDSHARED
mdefine_line|#define XFS_SB_VERSION_ADDSHARED(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_SHAREDBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_SUBSHARED)
r_int
id|xfs_sb_version_subshared
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_SUBSHARED
mdefine_line|#define XFS_SB_VERSION_SUBSHARED(sbp)&t;xfs_sb_version_subshared(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_SUBSHARED
mdefine_line|#define XFS_SB_VERSION_SUBSHARED(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum &amp; ~XFS_SB_VERSION_SHAREDBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASDIRV2)
r_int
id|xfs_sb_version_hasdirv2
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASDIRV2
mdefine_line|#define XFS_SB_VERSION_HASDIRV2(sbp)&t;xfs_sb_version_hasdirv2(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASDIRV2
mdefine_line|#define XFS_SB_VERSION_HASDIRV2(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_DIRV2BIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASLOGV2)
r_int
id|xfs_sb_version_haslogv2
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASLOGV2
mdefine_line|#define XFS_SB_VERSION_HASLOGV2(sbp)   xfs_sb_version_haslogv2(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASLOGV2
mdefine_line|#define XFS_SB_VERSION_HASLOGV2(sbp)   &bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_LOGV2BIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASEXTFLGBIT)
r_int
id|xfs_sb_version_hasextflgbit
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_HASEXTFLGBIT(sbp)&t;xfs_sb_version_hasextflgbit(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_HASEXTFLGBIT(sbp)&t;&bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t; ((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_EXTFLGBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_ADDEXTFLGBIT)
r_int
id|xfs_sb_version_addextflgbit
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_ADDEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_ADDEXTFLGBIT(sbp)&t;xfs_sb_version_addextflgbit(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_ADDEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_ADDEXTFLGBIT(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum | XFS_SB_VERSION_EXTFLGBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_SUBEXTFLGBIT)
r_int
id|xfs_sb_version_subextflgbit
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_SUBEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_SUBEXTFLGBIT(sbp)&t;xfs_sb_version_subextflgbit(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_SUBEXTFLGBIT
mdefine_line|#define XFS_SB_VERSION_SUBEXTFLGBIT(sbp)&t;&bslash;&n;&t;((sbp)-&gt;sb_versionnum = &bslash;&n;&t;&t;((sbp)-&gt;sb_versionnum &amp; ~XFS_SB_VERSION_EXTFLGBIT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_VERSION_HASSECTOR)
r_int
id|xfs_sb_version_hassector
c_func
(paren
id|xfs_sb_t
op_star
id|sbp
)paren
suffix:semicolon
DECL|macro|XFS_SB_VERSION_HASSECTOR
mdefine_line|#define XFS_SB_VERSION_HASSECTOR(sbp)   xfs_sb_version_hassector(sbp)
macro_line|#else
DECL|macro|XFS_SB_VERSION_HASSECTOR
mdefine_line|#define XFS_SB_VERSION_HASSECTOR(sbp)   &bslash;&n;&t;((XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) &amp;&amp; &bslash;&n;&t;((sbp)-&gt;sb_versionnum &amp; XFS_SB_VERSION_SECTORBIT))
macro_line|#endif
multiline_comment|/*&n; * end of superblock version macros&n; */
DECL|macro|XFS_SB_DADDR
mdefine_line|#define XFS_SB_DADDR&t;((xfs_daddr_t)0)&t;/* daddr in filesystem/ag */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_SB_BLOCK)
id|xfs_agblock_t
id|xfs_sb_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_SB_BLOCK
mdefine_line|#define&t;XFS_SB_BLOCK(mp)&t;xfs_sb_block(mp)
macro_line|#else
DECL|macro|XFS_SB_BLOCK
mdefine_line|#define&t;XFS_SB_BLOCK(mp)&t;XFS_HDR_BLOCK(mp, XFS_SB_DADDR)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_HDR_BLOCK)
id|xfs_agblock_t
id|xfs_hdr_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
suffix:semicolon
DECL|macro|XFS_HDR_BLOCK
mdefine_line|#define&t;XFS_HDR_BLOCK(mp,d)&t;xfs_hdr_block(mp,d)
macro_line|#else
DECL|macro|XFS_HDR_BLOCK
mdefine_line|#define&t;XFS_HDR_BLOCK(mp,d)&t;((xfs_agblock_t)(XFS_BB_TO_FSBT(mp,d)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DADDR_TO_FSB)
id|xfs_fsblock_t
id|xfs_daddr_to_fsb
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_daddr_t
id|d
)paren
suffix:semicolon
DECL|macro|XFS_DADDR_TO_FSB
mdefine_line|#define&t;XFS_DADDR_TO_FSB(mp,d)&t;&t;xfs_daddr_to_fsb(mp,d)
macro_line|#else
DECL|macro|XFS_DADDR_TO_FSB
mdefine_line|#define&t;XFS_DADDR_TO_FSB(mp,d) &bslash;&n;&t;XFS_AGB_TO_FSB(mp, XFS_DADDR_TO_AGNO(mp,d), XFS_DADDR_TO_AGBNO(mp,d))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FSB_TO_DADDR)
id|xfs_daddr_t
id|xfs_fsb_to_daddr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_fsblock_t
id|fsbno
)paren
suffix:semicolon
DECL|macro|XFS_FSB_TO_DADDR
mdefine_line|#define&t;XFS_FSB_TO_DADDR(mp,fsbno)&t;xfs_fsb_to_daddr(mp,fsbno)
macro_line|#else
DECL|macro|XFS_FSB_TO_DADDR
mdefine_line|#define&t;XFS_FSB_TO_DADDR(mp,fsbno) &bslash;&n;&t;XFS_AGB_TO_DADDR(mp, XFS_FSB_TO_AGNO(mp,fsbno), &bslash;&n;&t;&t;&t; XFS_FSB_TO_AGBNO(mp,fsbno))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_SBP)
id|xfs_sb_t
op_star
id|xfs_buf_to_sbp
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_SBP
mdefine_line|#define XFS_BUF_TO_SBP(bp)&t;xfs_buf_to_sbp(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_SBP
mdefine_line|#define XFS_BUF_TO_SBP(bp)&t;((xfs_sb_t *)XFS_BUF_PTR(bp))
macro_line|#endif
multiline_comment|/*&n; * File system sector to basic block conversions.&n; */
DECL|macro|XFS_FSS_TO_BB
mdefine_line|#define XFS_FSS_TO_BB(mp,sec)&t;((sec) &lt;&lt; (mp)-&gt;m_sectbb_log)
DECL|macro|XFS_BB_TO_FSS
mdefine_line|#define XFS_BB_TO_FSS(mp,bb)&t;&bslash;&n;&t;(((bb) + (XFS_FSS_TO_BB(mp,1) - 1)) &gt;&gt; (mp)-&gt;m_sectbb_log)
DECL|macro|XFS_BB_TO_FSST
mdefine_line|#define XFS_BB_TO_FSST(mp,bb)&t;((bb) &gt;&gt; (mp)-&gt;m_sectbb_log)
multiline_comment|/*&n; * File system sector to byte conversions.&n; */
DECL|macro|XFS_FSS_TO_B
mdefine_line|#define XFS_FSS_TO_B(mp,sectno)&t;((xfs_fsize_t)(sectno) &lt;&lt; (mp)-&gt;m_sb.sb_sectlog)
DECL|macro|XFS_B_TO_FSST
mdefine_line|#define XFS_B_TO_FSST(mp,b)&t;(((__uint64_t)(b)) &gt;&gt; (mp)-&gt;m_sb.sb_sectlog)
multiline_comment|/*&n; * File system block to basic block conversions.&n; */
DECL|macro|XFS_FSB_TO_BB
mdefine_line|#define&t;XFS_FSB_TO_BB(mp,fsbno)&t;((fsbno) &lt;&lt; (mp)-&gt;m_blkbb_log)
DECL|macro|XFS_BB_TO_FSB
mdefine_line|#define&t;XFS_BB_TO_FSB(mp,bb)&t;&bslash;&n;&t;(((bb) + (XFS_FSB_TO_BB(mp,1) - 1)) &gt;&gt; (mp)-&gt;m_blkbb_log)
DECL|macro|XFS_BB_TO_FSBT
mdefine_line|#define&t;XFS_BB_TO_FSBT(mp,bb)&t;((bb) &gt;&gt; (mp)-&gt;m_blkbb_log)
DECL|macro|XFS_BB_FSB_OFFSET
mdefine_line|#define&t;XFS_BB_FSB_OFFSET(mp,bb) ((bb) &amp; ((mp)-&gt;m_bsize - 1))
multiline_comment|/*&n; * File system block to byte conversions.&n; */
DECL|macro|XFS_FSB_TO_B
mdefine_line|#define XFS_FSB_TO_B(mp,fsbno)&t;((xfs_fsize_t)(fsbno) &lt;&lt; (mp)-&gt;m_sb.sb_blocklog)
DECL|macro|XFS_B_TO_FSB
mdefine_line|#define XFS_B_TO_FSB(mp,b)&t;&bslash;&n;&t;((((__uint64_t)(b)) + (mp)-&gt;m_blockmask) &gt;&gt; (mp)-&gt;m_sb.sb_blocklog)
DECL|macro|XFS_B_TO_FSBT
mdefine_line|#define XFS_B_TO_FSBT(mp,b)&t;(((__uint64_t)(b)) &gt;&gt; (mp)-&gt;m_sb.sb_blocklog)
DECL|macro|XFS_B_FSB_OFFSET
mdefine_line|#define XFS_B_FSB_OFFSET(mp,b)&t;((b) &amp; (mp)-&gt;m_blockmask)
macro_line|#endif&t;/* __XFS_SB_H__ */
eof
