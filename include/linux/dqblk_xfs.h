multiline_comment|/*&n; * Copyright (c) 1995-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2.1 of the GNU Lesser General Public License&n; * as published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU Lesser General Public&n; * License along with this program; if not, write the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307,&n; * USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef _LINUX_XQM_H
DECL|macro|_LINUX_XQM_H
mdefine_line|#define _LINUX_XQM_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Disk quota - quotactl(2) commands for the XFS Quota Manager (XQM).&n; */
DECL|macro|XQM_CMD
mdefine_line|#define XQM_CMD(x)&t;((&squot;X&squot;&lt;&lt;8)+(x))&t;/* note: forms first QCMD argument */
DECL|macro|Q_XQUOTAON
mdefine_line|#define Q_XQUOTAON&t;XQM_CMD(0x1)&t;/* enable accounting/enforcement */
DECL|macro|Q_XQUOTAOFF
mdefine_line|#define Q_XQUOTAOFF&t;XQM_CMD(0x2)&t;/* disable accounting/enforcement */
DECL|macro|Q_XGETQUOTA
mdefine_line|#define Q_XGETQUOTA&t;XQM_CMD(0x3)&t;/* get disk limits and usage */
DECL|macro|Q_XSETQLIM
mdefine_line|#define Q_XSETQLIM&t;XQM_CMD(0x4)&t;/* set disk limits */
DECL|macro|Q_XGETQSTAT
mdefine_line|#define Q_XGETQSTAT&t;XQM_CMD(0x5)&t;/* get quota subsystem status */
DECL|macro|Q_XQUOTARM
mdefine_line|#define Q_XQUOTARM&t;XQM_CMD(0x6)&t;/* free disk space used by dquots */
multiline_comment|/*&n; * fs_disk_quota structure:&n; *&n; * This contains the current quota information regarding a user/proj/group.&n; * It is 64-bit aligned, and all the blk units are in BBs (Basic Blocks) of&n; * 512 bytes.&n; */
DECL|macro|FS_DQUOT_VERSION
mdefine_line|#define FS_DQUOT_VERSION&t;1&t;/* fs_disk_quota.d_version */
DECL|struct|fs_disk_quota
r_typedef
r_struct
id|fs_disk_quota
(brace
DECL|member|d_version
id|__s8
id|d_version
suffix:semicolon
multiline_comment|/* version of this structure */
DECL|member|d_flags
id|__s8
id|d_flags
suffix:semicolon
multiline_comment|/* XFS_{USER,PROJ,GROUP}_QUOTA */
DECL|member|d_fieldmask
id|__u16
id|d_fieldmask
suffix:semicolon
multiline_comment|/* field specifier */
DECL|member|d_id
id|__u32
id|d_id
suffix:semicolon
multiline_comment|/* user, project, or group ID */
DECL|member|d_blk_hardlimit
id|__u64
id|d_blk_hardlimit
suffix:semicolon
multiline_comment|/* absolute limit on disk blks */
DECL|member|d_blk_softlimit
id|__u64
id|d_blk_softlimit
suffix:semicolon
multiline_comment|/* preferred limit on disk blks */
DECL|member|d_ino_hardlimit
id|__u64
id|d_ino_hardlimit
suffix:semicolon
multiline_comment|/* maximum # allocated inodes */
DECL|member|d_ino_softlimit
id|__u64
id|d_ino_softlimit
suffix:semicolon
multiline_comment|/* preferred inode limit */
DECL|member|d_bcount
id|__u64
id|d_bcount
suffix:semicolon
multiline_comment|/* # disk blocks owned by the user */
DECL|member|d_icount
id|__u64
id|d_icount
suffix:semicolon
multiline_comment|/* # inodes owned by the user */
DECL|member|d_itimer
id|__s32
id|d_itimer
suffix:semicolon
multiline_comment|/* zero if within inode limits */
multiline_comment|/* if not, we refuse service */
DECL|member|d_btimer
id|__s32
id|d_btimer
suffix:semicolon
multiline_comment|/* similar to above; for disk blocks */
DECL|member|d_iwarns
id|__u16
id|d_iwarns
suffix:semicolon
multiline_comment|/* # warnings issued wrt num inodes */
DECL|member|d_bwarns
id|__u16
id|d_bwarns
suffix:semicolon
multiline_comment|/* # warnings issued wrt disk blocks */
DECL|member|d_padding2
id|__s32
id|d_padding2
suffix:semicolon
multiline_comment|/* padding2 - for future use */
DECL|member|d_rtb_hardlimit
id|__u64
id|d_rtb_hardlimit
suffix:semicolon
multiline_comment|/* absolute limit on realtime blks */
DECL|member|d_rtb_softlimit
id|__u64
id|d_rtb_softlimit
suffix:semicolon
multiline_comment|/* preferred limit on RT disk blks */
DECL|member|d_rtbcount
id|__u64
id|d_rtbcount
suffix:semicolon
multiline_comment|/* # realtime blocks owned */
DECL|member|d_rtbtimer
id|__s32
id|d_rtbtimer
suffix:semicolon
multiline_comment|/* similar to above; for RT disk blks */
DECL|member|d_rtbwarns
id|__u16
id|d_rtbwarns
suffix:semicolon
multiline_comment|/* # warnings issued wrt RT disk blks */
DECL|member|d_padding3
id|__s16
id|d_padding3
suffix:semicolon
multiline_comment|/* padding3 - for future use */
DECL|member|d_padding4
r_char
id|d_padding4
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* yet more padding */
DECL|typedef|fs_disk_quota_t
)brace
id|fs_disk_quota_t
suffix:semicolon
multiline_comment|/*&n; * These fields are sent to Q_XSETQLIM to specify fields that need to change.&n; */
DECL|macro|FS_DQ_ISOFT
mdefine_line|#define FS_DQ_ISOFT&t;(1&lt;&lt;0)
DECL|macro|FS_DQ_IHARD
mdefine_line|#define FS_DQ_IHARD&t;(1&lt;&lt;1)
DECL|macro|FS_DQ_BSOFT
mdefine_line|#define FS_DQ_BSOFT&t;(1&lt;&lt;2)
DECL|macro|FS_DQ_BHARD
mdefine_line|#define FS_DQ_BHARD &t;(1&lt;&lt;3)
DECL|macro|FS_DQ_RTBSOFT
mdefine_line|#define FS_DQ_RTBSOFT&t;(1&lt;&lt;4)
DECL|macro|FS_DQ_RTBHARD
mdefine_line|#define FS_DQ_RTBHARD&t;(1&lt;&lt;5)
DECL|macro|FS_DQ_LIMIT_MASK
mdefine_line|#define FS_DQ_LIMIT_MASK&t;(FS_DQ_ISOFT | FS_DQ_IHARD | FS_DQ_BSOFT | &bslash;&n;&t;&t;&t;&t; FS_DQ_BHARD | FS_DQ_RTBSOFT | FS_DQ_RTBHARD)
multiline_comment|/*&n; * These timers can only be set in super user&squot;s dquot. For others, timers are&n; * automatically started and stopped. Superusers timer values set the limits&n; * for the rest.  In case these values are zero, the DQ_{F,B}TIMELIMIT values&n; * defined below are used. &n; * These values also apply only to the d_fieldmask field for Q_XSETQLIM.&n; */
DECL|macro|FS_DQ_BTIMER
mdefine_line|#define FS_DQ_BTIMER&t;(1&lt;&lt;6)
DECL|macro|FS_DQ_ITIMER
mdefine_line|#define FS_DQ_ITIMER&t;(1&lt;&lt;7)
DECL|macro|FS_DQ_RTBTIMER
mdefine_line|#define FS_DQ_RTBTIMER &t;(1&lt;&lt;8)
DECL|macro|FS_DQ_TIMER_MASK
mdefine_line|#define FS_DQ_TIMER_MASK&t;(FS_DQ_BTIMER | FS_DQ_ITIMER | FS_DQ_RTBTIMER)
multiline_comment|/*&n; * The following constants define the default amount of time given a user&n; * before the soft limits are treated as hard limits (usually resulting&n; * in an allocation failure).  These may be modified by the quotactl(2)&n; * system call with the Q_XSETQLIM command.&n; */
DECL|macro|DQ_FTIMELIMIT
mdefine_line|#define&t;DQ_FTIMELIMIT&t;(7 * 24*60*60)&t;&t;/* 1 week */
DECL|macro|DQ_BTIMELIMIT
mdefine_line|#define&t;DQ_BTIMELIMIT&t;(7 * 24*60*60)&t;&t;/* 1 week */
multiline_comment|/*&n; * Various flags related to quotactl(2).  Only relevant to XFS filesystems.&n; */
DECL|macro|XFS_QUOTA_UDQ_ACCT
mdefine_line|#define XFS_QUOTA_UDQ_ACCT&t;(1&lt;&lt;0)  /* user quota accounting */
DECL|macro|XFS_QUOTA_UDQ_ENFD
mdefine_line|#define XFS_QUOTA_UDQ_ENFD&t;(1&lt;&lt;1)  /* user quota limits enforcement */
DECL|macro|XFS_QUOTA_GDQ_ACCT
mdefine_line|#define XFS_QUOTA_GDQ_ACCT&t;(1&lt;&lt;2)  /* group quota accounting */
DECL|macro|XFS_QUOTA_GDQ_ENFD
mdefine_line|#define XFS_QUOTA_GDQ_ENFD&t;(1&lt;&lt;3)  /* group quota limits enforcement */
DECL|macro|XFS_USER_QUOTA
mdefine_line|#define XFS_USER_QUOTA&t;&t;(1&lt;&lt;0)&t;/* user quota type */
DECL|macro|XFS_PROJ_QUOTA
mdefine_line|#define XFS_PROJ_QUOTA&t;&t;(1&lt;&lt;1)&t;/* (IRIX) project quota type */
DECL|macro|XFS_GROUP_QUOTA
mdefine_line|#define XFS_GROUP_QUOTA&t;&t;(1&lt;&lt;2)&t;/* group quota type */
multiline_comment|/*&n; * fs_quota_stat is the struct returned in Q_XGETQSTAT for a given file system.&n; * Provides a centralized way to get meta infomation about the quota subsystem.&n; * eg. space taken up for user and group quotas, number of dquots currently&n; * incore.&n; */
DECL|macro|FS_QSTAT_VERSION
mdefine_line|#define FS_QSTAT_VERSION&t;1&t;/* fs_quota_stat.qs_version */
multiline_comment|/*&n; * Some basic infomation about &squot;quota files&squot;.&n; */
DECL|struct|fs_qfilestat
r_typedef
r_struct
id|fs_qfilestat
(brace
DECL|member|qfs_ino
id|__u64
id|qfs_ino
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|qfs_nblks
id|__u64
id|qfs_nblks
suffix:semicolon
multiline_comment|/* number of BBs 512-byte-blks */
DECL|member|qfs_nextents
id|__u32
id|qfs_nextents
suffix:semicolon
multiline_comment|/* number of extents */
DECL|typedef|fs_qfilestat_t
)brace
id|fs_qfilestat_t
suffix:semicolon
DECL|struct|fs_quota_stat
r_typedef
r_struct
id|fs_quota_stat
(brace
DECL|member|qs_version
id|__s8
id|qs_version
suffix:semicolon
multiline_comment|/* version number for future changes */
DECL|member|qs_flags
id|__u16
id|qs_flags
suffix:semicolon
multiline_comment|/* XFS_QUOTA_{U,P,G}DQ_{ACCT,ENFD} */
DECL|member|qs_pad
id|__s8
id|qs_pad
suffix:semicolon
multiline_comment|/* unused */
DECL|member|qs_uquota
id|fs_qfilestat_t
id|qs_uquota
suffix:semicolon
multiline_comment|/* user quota storage information */
DECL|member|qs_gquota
id|fs_qfilestat_t
id|qs_gquota
suffix:semicolon
multiline_comment|/* group quota storage information */
DECL|member|qs_incoredqs
id|__u32
id|qs_incoredqs
suffix:semicolon
multiline_comment|/* number of dquots incore */
DECL|member|qs_btimelimit
id|__s32
id|qs_btimelimit
suffix:semicolon
multiline_comment|/* limit for blks timer */
DECL|member|qs_itimelimit
id|__s32
id|qs_itimelimit
suffix:semicolon
multiline_comment|/* limit for inodes timer */
DECL|member|qs_rtbtimelimit
id|__s32
id|qs_rtbtimelimit
suffix:semicolon
multiline_comment|/* limit for rt blks timer */
DECL|member|qs_bwarnlimit
id|__u16
id|qs_bwarnlimit
suffix:semicolon
multiline_comment|/* limit for num warnings */
DECL|member|qs_iwarnlimit
id|__u16
id|qs_iwarnlimit
suffix:semicolon
multiline_comment|/* limit for num warnings */
DECL|typedef|fs_quota_stat_t
)brace
id|fs_quota_stat_t
suffix:semicolon
macro_line|#endif&t;/* _LINUX_XQM_H */
eof
