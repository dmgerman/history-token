multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_QUOTA_H__
DECL|macro|__XFS_QUOTA_H__
mdefine_line|#define __XFS_QUOTA_H__
multiline_comment|/*&n; * The ondisk form of a dquot structure.&n; */
DECL|macro|XFS_DQUOT_MAGIC
mdefine_line|#define XFS_DQUOT_MAGIC&t;&t;0x4451&t;&t;/* &squot;DQ&squot; */
DECL|macro|XFS_DQUOT_VERSION
mdefine_line|#define XFS_DQUOT_VERSION&t;(u_int8_t)0x01&t;/* latest version number */
multiline_comment|/*&n; * uid_t and gid_t are hard-coded to 32 bits in the inode.&n; * Hence, an &squot;id&squot; in a dquot is 32 bits..&n; */
DECL|typedef|xfs_dqid_t
r_typedef
id|__int32_t
id|xfs_dqid_t
suffix:semicolon
multiline_comment|/*&n; * Eventhough users may not have quota limits occupying all 64-bits,&n; * they may need 64-bit accounting. Hence, 64-bit quota-counters,&n; * and quota-limits. This is a waste in the common case, but hey ...&n; */
DECL|typedef|xfs_qcnt_t
r_typedef
id|__uint64_t
id|xfs_qcnt_t
suffix:semicolon
DECL|typedef|xfs_qwarncnt_t
r_typedef
id|__uint16_t
id|xfs_qwarncnt_t
suffix:semicolon
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
multiline_comment|/*&n; * These are the structures used to lay out dquots and quotaoff&n; * records on the log. Quite similar to those of inodes.&n; */
multiline_comment|/*&n; * log format struct for dquots.&n; * The first two fields must be the type and size fitting into&n; * 32 bits : log_recovery code assumes that.&n; */
DECL|struct|xfs_dq_logformat
r_typedef
r_struct
id|xfs_dq_logformat
(brace
DECL|member|qlf_type
id|__uint16_t
id|qlf_type
suffix:semicolon
multiline_comment|/* dquot log item type */
DECL|member|qlf_size
id|__uint16_t
id|qlf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|qlf_id
id|xfs_dqid_t
id|qlf_id
suffix:semicolon
multiline_comment|/* usr/grp id number : 32 bits */
DECL|member|qlf_blkno
id|__int64_t
id|qlf_blkno
suffix:semicolon
multiline_comment|/* blkno of dquot buffer */
DECL|member|qlf_len
id|__int32_t
id|qlf_len
suffix:semicolon
multiline_comment|/* len of dquot buffer */
DECL|member|qlf_boffset
id|__uint32_t
id|qlf_boffset
suffix:semicolon
multiline_comment|/* off of dquot in buffer */
DECL|typedef|xfs_dq_logformat_t
)brace
id|xfs_dq_logformat_t
suffix:semicolon
multiline_comment|/*&n; * log format struct for QUOTAOFF records.&n; * The first two fields must be the type and size fitting into&n; * 32 bits : log_recovery code assumes that.&n; * We write two LI_QUOTAOFF logitems per quotaoff, the last one keeps a pointer&n; * to the first and ensures that the first logitem is taken out of the AIL&n; * only when the last one is securely committed.&n; */
DECL|struct|xfs_qoff_logformat
r_typedef
r_struct
id|xfs_qoff_logformat
(brace
DECL|member|qf_type
r_int
r_int
id|qf_type
suffix:semicolon
multiline_comment|/* quotaoff log item type */
DECL|member|qf_size
r_int
r_int
id|qf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|qf_flags
r_int
r_int
id|qf_flags
suffix:semicolon
multiline_comment|/* USR and/or GRP */
DECL|member|qf_pad
r_char
id|qf_pad
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* padding for future */
DECL|typedef|xfs_qoff_logformat_t
)brace
id|xfs_qoff_logformat_t
suffix:semicolon
multiline_comment|/*&n; * Disk quotas status in m_qflags, and also sb_qflags. 16 bits.&n; */
DECL|macro|XFS_UQUOTA_ACCT
mdefine_line|#define XFS_UQUOTA_ACCT&t;0x0001  /* user quota accounting ON */
DECL|macro|XFS_UQUOTA_ENFD
mdefine_line|#define XFS_UQUOTA_ENFD&t;0x0002  /* user quota limits enforced */
DECL|macro|XFS_UQUOTA_CHKD
mdefine_line|#define XFS_UQUOTA_CHKD&t;0x0004  /* quotacheck run on usr quotas */
DECL|macro|XFS_PQUOTA_ACCT
mdefine_line|#define XFS_PQUOTA_ACCT&t;0x0008  /* (IRIX) project quota accounting ON */
DECL|macro|XFS_GQUOTA_ENFD
mdefine_line|#define XFS_GQUOTA_ENFD&t;0x0010  /* group quota limits enforced */
DECL|macro|XFS_GQUOTA_CHKD
mdefine_line|#define XFS_GQUOTA_CHKD&t;0x0020  /* quotacheck run on grp quotas */
DECL|macro|XFS_GQUOTA_ACCT
mdefine_line|#define XFS_GQUOTA_ACCT&t;0x0040  /* group quota accounting ON */
multiline_comment|/*&n; * Incore only flags for quotaoff - these bits get cleared when quota(s)&n; * are in the process of getting turned off. These flags are in m_qflags but&n; * never in sb_qflags.&n; */
DECL|macro|XFS_UQUOTA_ACTIVE
mdefine_line|#define XFS_UQUOTA_ACTIVE&t;0x0080  /* uquotas are being turned off */
DECL|macro|XFS_GQUOTA_ACTIVE
mdefine_line|#define XFS_GQUOTA_ACTIVE&t;0x0100  /* gquotas are being turned off */
multiline_comment|/*&n; * Checking XFS_IS_*QUOTA_ON() while holding any inode lock guarantees&n; * quota will be not be switched off as long as that inode lock is held.&n; */
DECL|macro|XFS_IS_QUOTA_ON
mdefine_line|#define XFS_IS_QUOTA_ON(mp)&t;((mp)-&gt;m_qflags &amp; (XFS_UQUOTA_ACTIVE | &bslash;&n;&t;&t;&t;&t;&t;&t;   XFS_GQUOTA_ACTIVE))
DECL|macro|XFS_IS_UQUOTA_ON
mdefine_line|#define XFS_IS_UQUOTA_ON(mp)&t;((mp)-&gt;m_qflags &amp; XFS_UQUOTA_ACTIVE)
DECL|macro|XFS_IS_GQUOTA_ON
mdefine_line|#define XFS_IS_GQUOTA_ON(mp)&t;((mp)-&gt;m_qflags &amp; XFS_GQUOTA_ACTIVE)
multiline_comment|/*&n; * Flags to tell various functions what to do. Not all of these are meaningful&n; * to a single function. None of these XFS_QMOPT_* flags are meant to have&n; * persistent values (ie. their values can and will change between versions)&n; */
DECL|macro|XFS_QMOPT_DQLOCK
mdefine_line|#define XFS_QMOPT_DQLOCK&t;0x0000001 /* dqlock */
DECL|macro|XFS_QMOPT_DQALLOC
mdefine_line|#define XFS_QMOPT_DQALLOC&t;0x0000002 /* alloc dquot ondisk if needed */
DECL|macro|XFS_QMOPT_UQUOTA
mdefine_line|#define XFS_QMOPT_UQUOTA&t;0x0000004 /* user dquot requested */
DECL|macro|XFS_QMOPT_GQUOTA
mdefine_line|#define XFS_QMOPT_GQUOTA&t;0x0000008 /* group dquot requested */
DECL|macro|XFS_QMOPT_FORCE_RES
mdefine_line|#define XFS_QMOPT_FORCE_RES&t;0x0000010 /* ignore quota limits */
DECL|macro|XFS_QMOPT_DQSUSER
mdefine_line|#define XFS_QMOPT_DQSUSER&t;0x0000020 /* don&squot;t cache super users dquot */
DECL|macro|XFS_QMOPT_SBVERSION
mdefine_line|#define XFS_QMOPT_SBVERSION&t;0x0000040 /* change superblock version num */
DECL|macro|XFS_QMOPT_QUOTAOFF
mdefine_line|#define XFS_QMOPT_QUOTAOFF&t;0x0000080 /* quotas are being turned off */
DECL|macro|XFS_QMOPT_UMOUNTING
mdefine_line|#define XFS_QMOPT_UMOUNTING&t;0x0000100 /* filesys is being unmounted */
DECL|macro|XFS_QMOPT_DOLOG
mdefine_line|#define XFS_QMOPT_DOLOG&t;&t;0x0000200 /* log buf changes (in quotacheck) */
DECL|macro|XFS_QMOPT_DOWARN
mdefine_line|#define XFS_QMOPT_DOWARN        0x0000400 /* increase warning cnt if necessary */
DECL|macro|XFS_QMOPT_ILOCKED
mdefine_line|#define XFS_QMOPT_ILOCKED&t;0x0000800 /* inode is already locked (excl) */
DECL|macro|XFS_QMOPT_DQREPAIR
mdefine_line|#define XFS_QMOPT_DQREPAIR&t;0x0001000 /* repair dquot, if damaged. */
multiline_comment|/*&n; * flags to xfs_trans_mod_dquot to indicate which field needs to be&n; * modified.&n; */
DECL|macro|XFS_QMOPT_RES_REGBLKS
mdefine_line|#define XFS_QMOPT_RES_REGBLKS&t;0x0010000
DECL|macro|XFS_QMOPT_RES_RTBLKS
mdefine_line|#define XFS_QMOPT_RES_RTBLKS&t;0x0020000
DECL|macro|XFS_QMOPT_BCOUNT
mdefine_line|#define XFS_QMOPT_BCOUNT&t;0x0040000
DECL|macro|XFS_QMOPT_ICOUNT
mdefine_line|#define XFS_QMOPT_ICOUNT&t;0x0080000
DECL|macro|XFS_QMOPT_RTBCOUNT
mdefine_line|#define XFS_QMOPT_RTBCOUNT&t;0x0100000
DECL|macro|XFS_QMOPT_DELBCOUNT
mdefine_line|#define XFS_QMOPT_DELBCOUNT&t;0x0200000
DECL|macro|XFS_QMOPT_DELRTBCOUNT
mdefine_line|#define XFS_QMOPT_DELRTBCOUNT&t;0x0400000
DECL|macro|XFS_QMOPT_RES_INOS
mdefine_line|#define XFS_QMOPT_RES_INOS&t;0x0800000
multiline_comment|/*&n; * flags for dqflush and dqflush_all.&n; */
DECL|macro|XFS_QMOPT_SYNC
mdefine_line|#define XFS_QMOPT_SYNC&t;&t;0x1000000
DECL|macro|XFS_QMOPT_ASYNC
mdefine_line|#define XFS_QMOPT_ASYNC&t;&t;0x2000000
DECL|macro|XFS_QMOPT_DELWRI
mdefine_line|#define XFS_QMOPT_DELWRI&t;0x4000000
multiline_comment|/*&n; * flags for dqalloc.&n; */
DECL|macro|XFS_QMOPT_INHERIT
mdefine_line|#define XFS_QMOPT_INHERIT&t;0x8000000
multiline_comment|/*&n; * flags to xfs_trans_mod_dquot.&n; */
DECL|macro|XFS_TRANS_DQ_RES_BLKS
mdefine_line|#define XFS_TRANS_DQ_RES_BLKS&t;XFS_QMOPT_RES_REGBLKS
DECL|macro|XFS_TRANS_DQ_RES_RTBLKS
mdefine_line|#define XFS_TRANS_DQ_RES_RTBLKS&t;XFS_QMOPT_RES_RTBLKS
DECL|macro|XFS_TRANS_DQ_RES_INOS
mdefine_line|#define XFS_TRANS_DQ_RES_INOS&t;XFS_QMOPT_RES_INOS
DECL|macro|XFS_TRANS_DQ_BCOUNT
mdefine_line|#define XFS_TRANS_DQ_BCOUNT&t;XFS_QMOPT_BCOUNT
DECL|macro|XFS_TRANS_DQ_DELBCOUNT
mdefine_line|#define XFS_TRANS_DQ_DELBCOUNT&t;XFS_QMOPT_DELBCOUNT
DECL|macro|XFS_TRANS_DQ_ICOUNT
mdefine_line|#define XFS_TRANS_DQ_ICOUNT&t;XFS_QMOPT_ICOUNT
DECL|macro|XFS_TRANS_DQ_RTBCOUNT
mdefine_line|#define XFS_TRANS_DQ_RTBCOUNT&t;XFS_QMOPT_RTBCOUNT
DECL|macro|XFS_TRANS_DQ_DELRTBCOUNT
mdefine_line|#define XFS_TRANS_DQ_DELRTBCOUNT XFS_QMOPT_DELRTBCOUNT
DECL|macro|XFS_QMOPT_QUOTALL
mdefine_line|#define XFS_QMOPT_QUOTALL&t;(XFS_QMOPT_UQUOTA|XFS_QMOPT_GQUOTA)
DECL|macro|XFS_QMOPT_RESBLK_MASK
mdefine_line|#define XFS_QMOPT_RESBLK_MASK&t;(XFS_QMOPT_RES_REGBLKS | XFS_QMOPT_RES_RTBLKS)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This check is done typically without holding the inode lock;&n; * that may seem racey, but it is harmless in the context that it is used.&n; * The inode cannot go inactive as long a reference is kept, and&n; * therefore if dquot(s) were attached, they&squot;ll stay consistent.&n; * If, for example, the ownership of the inode changes while&n; * we didn&squot;t have the inode locked, the appropriate dquot(s) will be&n; * attached atomically.&n; */
DECL|macro|XFS_NOT_DQATTACHED
mdefine_line|#define XFS_NOT_DQATTACHED(mp, ip) ((XFS_IS_UQUOTA_ON(mp) &amp;&amp;&bslash;&n;&t;&t;&t;&t;     (ip)-&gt;i_udquot == NULL) || &bslash;&n;&t;&t;&t;&t;    (XFS_IS_GQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (ip)-&gt;i_gdquot == NULL))
DECL|macro|XFS_QM_NEED_QUOTACHECK
mdefine_line|#define XFS_QM_NEED_QUOTACHECK(mp) ((XFS_IS_UQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (mp-&gt;m_sb.sb_qflags &amp; &bslash;&n;&t;&t;&t;&t;      XFS_UQUOTA_CHKD) == 0) || &bslash;&n;&t;&t;&t;&t;    (XFS_IS_GQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (mp-&gt;m_sb.sb_qflags &amp; &bslash;&n;&t;&t;&t;&t;      XFS_GQUOTA_CHKD) == 0))
DECL|macro|XFS_MOUNT_QUOTA_ALL
mdefine_line|#define XFS_MOUNT_QUOTA_ALL&t;(XFS_UQUOTA_ACCT|XFS_UQUOTA_ENFD|&bslash;&n;&t;&t;&t;&t; XFS_UQUOTA_CHKD|XFS_GQUOTA_ACCT|&bslash;&n;&t;&t;&t;&t; XFS_GQUOTA_ENFD|XFS_GQUOTA_CHKD)
DECL|macro|XFS_MOUNT_QUOTA_MASK
mdefine_line|#define XFS_MOUNT_QUOTA_MASK&t;(XFS_MOUNT_QUOTA_ALL | XFS_UQUOTA_ACTIVE | &bslash;&n;&t;&t;&t;&t; XFS_GQUOTA_ACTIVE)
multiline_comment|/*&n; * The structure kept inside the xfs_trans_t keep track of dquot changes&n; * within a transaction and apply them later.&n; */
DECL|struct|xfs_dqtrx
r_typedef
r_struct
id|xfs_dqtrx
(brace
DECL|member|qt_dquot
r_struct
id|xfs_dquot
op_star
id|qt_dquot
suffix:semicolon
multiline_comment|/* the dquot this refers to */
DECL|member|qt_blk_res
id|ulong
id|qt_blk_res
suffix:semicolon
multiline_comment|/* blks reserved on a dquot */
DECL|member|qt_blk_res_used
id|ulong
id|qt_blk_res_used
suffix:semicolon
multiline_comment|/* blks used from the reservation */
DECL|member|qt_ino_res
id|ulong
id|qt_ino_res
suffix:semicolon
multiline_comment|/* inode reserved on a dquot */
DECL|member|qt_ino_res_used
id|ulong
id|qt_ino_res_used
suffix:semicolon
multiline_comment|/* inodes used from the reservation */
DECL|member|qt_bcount_delta
r_int
id|qt_bcount_delta
suffix:semicolon
multiline_comment|/* dquot blk count changes */
DECL|member|qt_delbcnt_delta
r_int
id|qt_delbcnt_delta
suffix:semicolon
multiline_comment|/* delayed dquot blk count changes */
DECL|member|qt_icount_delta
r_int
id|qt_icount_delta
suffix:semicolon
multiline_comment|/* dquot inode count changes */
DECL|member|qt_rtblk_res
id|ulong
id|qt_rtblk_res
suffix:semicolon
multiline_comment|/* # blks reserved on a dquot */
DECL|member|qt_rtblk_res_used
id|ulong
id|qt_rtblk_res_used
suffix:semicolon
multiline_comment|/* # blks used from reservation */
DECL|member|qt_rtbcount_delta
r_int
id|qt_rtbcount_delta
suffix:semicolon
multiline_comment|/* dquot realtime blk changes */
DECL|member|qt_delrtb_delta
r_int
id|qt_delrtb_delta
suffix:semicolon
multiline_comment|/* delayed RT blk count changes */
DECL|typedef|xfs_dqtrx_t
)brace
id|xfs_dqtrx_t
suffix:semicolon
multiline_comment|/*&n; * Dquot transaction functions, used if quota is enabled.&n; */
DECL|typedef|qo_dup_dqinfo_t
r_typedef
r_void
(paren
op_star
id|qo_dup_dqinfo_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
DECL|typedef|qo_mod_dquot_byino_t
r_typedef
r_void
(paren
op_star
id|qo_mod_dquot_byino_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|uint
comma
r_int
)paren
suffix:semicolon
DECL|typedef|qo_free_dqinfo_t
r_typedef
r_void
(paren
op_star
id|qo_free_dqinfo_t
)paren
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
DECL|typedef|qo_apply_dquot_deltas_t
r_typedef
r_void
(paren
op_star
id|qo_apply_dquot_deltas_t
)paren
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
DECL|typedef|qo_unreserve_and_mod_dquots_t
r_typedef
r_void
(paren
op_star
id|qo_unreserve_and_mod_dquots_t
)paren
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
DECL|typedef|qo_reserve_quota_nblks_t
r_typedef
r_int
(paren
op_star
id|qo_reserve_quota_nblks_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_int
comma
r_int
comma
id|uint
)paren
suffix:semicolon
DECL|typedef|qo_reserve_quota_bydquots_t
r_typedef
r_int
(paren
op_star
id|qo_reserve_quota_bydquots_t
)paren
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
r_int
comma
r_int
comma
id|uint
)paren
suffix:semicolon
DECL|struct|xfs_dqtrxops
r_typedef
r_struct
id|xfs_dqtrxops
(brace
DECL|member|qo_dup_dqinfo
id|qo_dup_dqinfo_t
id|qo_dup_dqinfo
suffix:semicolon
DECL|member|qo_free_dqinfo
id|qo_free_dqinfo_t
id|qo_free_dqinfo
suffix:semicolon
DECL|member|qo_mod_dquot_byino
id|qo_mod_dquot_byino_t
id|qo_mod_dquot_byino
suffix:semicolon
DECL|member|qo_apply_dquot_deltas
id|qo_apply_dquot_deltas_t
id|qo_apply_dquot_deltas
suffix:semicolon
DECL|member|qo_reserve_quota_nblks
id|qo_reserve_quota_nblks_t
id|qo_reserve_quota_nblks
suffix:semicolon
DECL|member|qo_reserve_quota_bydquots
id|qo_reserve_quota_bydquots_t
id|qo_reserve_quota_bydquots
suffix:semicolon
DECL|member|qo_unreserve_and_mod_dquots
id|qo_unreserve_and_mod_dquots_t
id|qo_unreserve_and_mod_dquots
suffix:semicolon
DECL|typedef|xfs_dqtrxops_t
)brace
id|xfs_dqtrxops_t
suffix:semicolon
DECL|macro|XFS_DQTRXOP
mdefine_line|#define XFS_DQTRXOP(mp, tp, op, args...) &bslash;&n;&t;&t;&t;((mp)-&gt;m_qm_ops.xfs_dqtrxops ? &bslash;&n;&t;&t;&t;((mp)-&gt;m_qm_ops.xfs_dqtrxops-&gt;op)(tp, ## args) : 0)
DECL|macro|XFS_TRANS_DUP_DQINFO
mdefine_line|#define XFS_TRANS_DUP_DQINFO(mp, otp, ntp) &bslash;&n;&t;XFS_DQTRXOP(mp, otp, qo_dup_dqinfo, ntp)
DECL|macro|XFS_TRANS_FREE_DQINFO
mdefine_line|#define XFS_TRANS_FREE_DQINFO(mp, tp) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_free_dqinfo)
DECL|macro|XFS_TRANS_MOD_DQUOT_BYINO
mdefine_line|#define XFS_TRANS_MOD_DQUOT_BYINO(mp, tp, ip, field, delta) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_mod_dquot_byino, ip, field, delta)
DECL|macro|XFS_TRANS_APPLY_DQUOT_DELTAS
mdefine_line|#define XFS_TRANS_APPLY_DQUOT_DELTAS(mp, tp) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_apply_dquot_deltas)
DECL|macro|XFS_TRANS_RESERVE_QUOTA_NBLKS
mdefine_line|#define XFS_TRANS_RESERVE_QUOTA_NBLKS(mp, tp, ip, nblks, ninos, fl) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_reserve_quota_nblks, mp, ip, nblks, ninos, fl)
DECL|macro|XFS_TRANS_RESERVE_QUOTA_BYDQUOTS
mdefine_line|#define XFS_TRANS_RESERVE_QUOTA_BYDQUOTS(mp, tp, ud, gd, nb, ni, fl) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_reserve_quota_bydquots, mp, ud, gd, nb, ni, fl)
DECL|macro|XFS_TRANS_UNRESERVE_AND_MOD_DQUOTS
mdefine_line|#define XFS_TRANS_UNRESERVE_AND_MOD_DQUOTS(mp, tp) &bslash;&n;&t;XFS_DQTRXOP(mp, tp, qo_unreserve_and_mod_dquots)
DECL|macro|XFS_TRANS_RESERVE_BLKQUOTA
mdefine_line|#define XFS_TRANS_RESERVE_BLKQUOTA(mp, tp, ip, nblks) &bslash;&n;&t;XFS_TRANS_RESERVE_QUOTA_NBLKS(mp, tp, ip, nblks, 0, &bslash;&n;&t;&t;&t;&t;XFS_QMOPT_RES_REGBLKS)
DECL|macro|XFS_TRANS_RESERVE_BLKQUOTA_FORCE
mdefine_line|#define XFS_TRANS_RESERVE_BLKQUOTA_FORCE(mp, tp, ip, nblks) &bslash;&n;&t;XFS_TRANS_RESERVE_QUOTA_NBLKS(mp, tp, ip, nblks, 0, &bslash;&n;&t;&t;&t;&t;XFS_QMOPT_RES_REGBLKS | XFS_QMOPT_FORCE_RES)
DECL|macro|XFS_TRANS_UNRESERVE_BLKQUOTA
mdefine_line|#define XFS_TRANS_UNRESERVE_BLKQUOTA(mp, tp, ip, nblks) &bslash;&n;&t;XFS_TRANS_RESERVE_QUOTA_NBLKS(mp, tp, ip, -(nblks), 0, &bslash;&n;&t;&t;&t;&t;XFS_QMOPT_RES_REGBLKS)
DECL|macro|XFS_TRANS_RESERVE_QUOTA
mdefine_line|#define XFS_TRANS_RESERVE_QUOTA(mp, tp, ud, gd, nb, ni, f) &bslash;&n;&t;XFS_TRANS_RESERVE_QUOTA_BYDQUOTS(mp, tp, ud, gd, nb, ni, &bslash;&n;&t;&t;&t;&t;f | XFS_QMOPT_RES_REGBLKS)
DECL|macro|XFS_TRANS_UNRESERVE_QUOTA
mdefine_line|#define XFS_TRANS_UNRESERVE_QUOTA(mp, tp, ud, gd, nb, ni, f) &bslash;&n;&t;XFS_TRANS_RESERVE_QUOTA_BYDQUOTS(mp, tp, ud, gd, -(nb), -(ni), &bslash;&n;&t;&t;&t;&t;f | XFS_QMOPT_RES_REGBLKS)
r_extern
r_int
id|xfs_qm_dqcheck
c_func
(paren
id|xfs_disk_dquot_t
op_star
comma
id|xfs_dqid_t
comma
id|uint
comma
id|uint
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|bhv_vfsops
id|xfs_qmops
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_QUOTA_H__ */
eof
