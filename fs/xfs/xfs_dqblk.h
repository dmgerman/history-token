multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DQBLK_H__
DECL|macro|__XFS_DQBLK_H__
mdefine_line|#define __XFS_DQBLK_H__
multiline_comment|/*&n; * The ondisk form of a dquot structure.&n; */
DECL|macro|XFS_DQUOT_MAGIC
mdefine_line|#define XFS_DQUOT_MAGIC&t;&t;0x4451&t;&t;/* &squot;DQ&squot; */
DECL|macro|XFS_DQUOT_VERSION
mdefine_line|#define XFS_DQUOT_VERSION&t;(u_int8_t)0x01&t;/* latest version number */
multiline_comment|/*&n; * This is the main portion of the on-disk representation of quota&n; * information for a user. This is the q_core of the xfs_dquot_t that&n; * is kept in kernel memory. We pad this with some more expansion room&n; * to construct the on disk structure.&n; */
DECL|struct|xfs_disk_dquot
r_typedef
r_struct
id|xfs_disk_dquot
(brace
DECL|member|d_magic
multiline_comment|/*16*/
id|u_int16_t
id|d_magic
suffix:semicolon
multiline_comment|/* dquot magic = XFS_DQUOT_MAGIC */
DECL|member|d_version
multiline_comment|/*8 */
id|u_int8_t
id|d_version
suffix:semicolon
multiline_comment|/* dquot version */
DECL|member|d_flags
multiline_comment|/*8 */
id|u_int8_t
id|d_flags
suffix:semicolon
multiline_comment|/* XFS_DQ_USER/PROJ/GROUP */
DECL|member|d_id
multiline_comment|/*32*/
id|xfs_dqid_t
id|d_id
suffix:semicolon
multiline_comment|/* user,project,group id */
DECL|member|d_blk_hardlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_blk_hardlimit
suffix:semicolon
multiline_comment|/* absolute limit on disk blks */
DECL|member|d_blk_softlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_blk_softlimit
suffix:semicolon
multiline_comment|/* preferred limit on disk blks */
DECL|member|d_ino_hardlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_ino_hardlimit
suffix:semicolon
multiline_comment|/* maximum # allocated inodes */
DECL|member|d_ino_softlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_ino_softlimit
suffix:semicolon
multiline_comment|/* preferred inode limit */
DECL|member|d_bcount
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_bcount
suffix:semicolon
multiline_comment|/* disk blocks owned by the user */
DECL|member|d_icount
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_icount
suffix:semicolon
multiline_comment|/* inodes owned by the user */
DECL|member|d_itimer
multiline_comment|/*32*/
id|__int32_t
id|d_itimer
suffix:semicolon
multiline_comment|/* zero if within inode limits if not,&n;&t;&t;&t;&t;&t;   this is when we refuse service */
DECL|member|d_btimer
multiline_comment|/*32*/
id|__int32_t
id|d_btimer
suffix:semicolon
multiline_comment|/* similar to above; for disk blocks */
DECL|member|d_iwarns
multiline_comment|/*16*/
id|xfs_qwarncnt_t
id|d_iwarns
suffix:semicolon
multiline_comment|/* warnings issued wrt num inodes */
DECL|member|d_bwarns
multiline_comment|/*16*/
id|xfs_qwarncnt_t
id|d_bwarns
suffix:semicolon
multiline_comment|/* warnings issued wrt disk blocks */
DECL|member|d_pad0
multiline_comment|/*32*/
id|__int32_t
id|d_pad0
suffix:semicolon
multiline_comment|/* 64 bit align */
DECL|member|d_rtb_hardlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_rtb_hardlimit
suffix:semicolon
multiline_comment|/* absolute limit on realtime blks */
DECL|member|d_rtb_softlimit
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_rtb_softlimit
suffix:semicolon
multiline_comment|/* preferred limit on RT disk blks */
DECL|member|d_rtbcount
multiline_comment|/*64*/
id|xfs_qcnt_t
id|d_rtbcount
suffix:semicolon
multiline_comment|/* realtime blocks owned */
DECL|member|d_rtbtimer
multiline_comment|/*32*/
id|__int32_t
id|d_rtbtimer
suffix:semicolon
multiline_comment|/* similar to above; for RT disk blocks */
DECL|member|d_rtbwarns
multiline_comment|/*16*/
id|xfs_qwarncnt_t
id|d_rtbwarns
suffix:semicolon
multiline_comment|/* warnings issued wrt RT disk blocks */
DECL|member|d_pad
multiline_comment|/*16*/
id|__uint16_t
id|d_pad
suffix:semicolon
DECL|typedef|xfs_disk_dquot_t
)brace
id|xfs_disk_dquot_t
suffix:semicolon
multiline_comment|/*&n; * This is what goes on disk. This is separated from the xfs_disk_dquot because&n; * carrying the unnecessary padding would be a waste of memory.&n; */
DECL|struct|xfs_dqblk
r_typedef
r_struct
id|xfs_dqblk
(brace
DECL|member|dd_diskdq
id|xfs_disk_dquot_t
id|dd_diskdq
suffix:semicolon
multiline_comment|/* portion that lives incore as well */
DECL|member|dd_fill
r_char
id|dd_fill
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* filling for posterity */
DECL|typedef|xfs_dqblk_t
)brace
id|xfs_dqblk_t
suffix:semicolon
multiline_comment|/*&n; * flags for q_flags field in the dquot.&n; */
DECL|macro|XFS_DQ_USER
mdefine_line|#define XFS_DQ_USER&t;&t;0x0001&t;&t;/* a user quota */
multiline_comment|/* #define XFS_DQ_PROJ&t;&t;0x0002&t;&t;-- project quota (IRIX) */
DECL|macro|XFS_DQ_GROUP
mdefine_line|#define XFS_DQ_GROUP&t;&t;0x0004&t;&t;/* a group quota */
DECL|macro|XFS_DQ_FLOCKED
mdefine_line|#define XFS_DQ_FLOCKED&t;&t;0x0008&t;&t;/* flush lock taken */
DECL|macro|XFS_DQ_DIRTY
mdefine_line|#define XFS_DQ_DIRTY&t;&t;0x0010&t;&t;/* dquot is dirty */
DECL|macro|XFS_DQ_WANT
mdefine_line|#define XFS_DQ_WANT&t;&t;0x0020&t;&t;/* for lookup/reclaim race */
DECL|macro|XFS_DQ_INACTIVE
mdefine_line|#define XFS_DQ_INACTIVE&t;&t;0x0040&t;&t;/* dq off mplist &amp; hashlist */
DECL|macro|XFS_DQ_MARKER
mdefine_line|#define XFS_DQ_MARKER&t;&t;0x0080&t;&t;/* sentinel */
multiline_comment|/*&n; * In the worst case, when both user and group quotas are on,&n; * we can have a max of three dquots changing in a single transaction.&n; */
DECL|macro|XFS_DQUOT_LOGRES
mdefine_line|#define XFS_DQUOT_LOGRES(mp)&t;(sizeof(xfs_disk_dquot_t) * 3)
macro_line|#endif&t;/* __XFS_DQBLK_H__ */
eof
