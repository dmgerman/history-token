multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_QUOTA_H__
DECL|macro|__XFS_QUOTA_H__
mdefine_line|#define __XFS_QUOTA_H__
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
multiline_comment|/*&n; * Disk quotas status in m_qflags, and also sb_qflags. 16 bits.&n; */
DECL|macro|XFS_UQUOTA_ACCT
mdefine_line|#define XFS_UQUOTA_ACCT 0x0001&t;/* user quota accounting ON */
DECL|macro|XFS_UQUOTA_ENFD
mdefine_line|#define XFS_UQUOTA_ENFD 0x0002&t;/* user quota limits enforced */
DECL|macro|XFS_UQUOTA_CHKD
mdefine_line|#define XFS_UQUOTA_CHKD 0x0004&t;/* quotacheck run on usr quotas */
DECL|macro|XFS_PQUOTA_ACCT
mdefine_line|#define XFS_PQUOTA_ACCT 0x0008&t;/* (IRIX) project quota accounting ON */
DECL|macro|XFS_GQUOTA_ENFD
mdefine_line|#define XFS_GQUOTA_ENFD 0x0010&t;/* group quota limits enforced */
DECL|macro|XFS_GQUOTA_CHKD
mdefine_line|#define XFS_GQUOTA_CHKD 0x0020&t;/* quotacheck run on grp quotas */
DECL|macro|XFS_GQUOTA_ACCT
mdefine_line|#define XFS_GQUOTA_ACCT 0x0040&t;/* group quota accounting ON */
multiline_comment|/*&n; * Incore only flags for quotaoff - these bits get cleared when quota(s)&n; * are in the process of getting turned off. These flags are in m_qflags but&n; * never in sb_qflags.&n; */
DECL|macro|XFS_UQUOTA_ACTIVE
mdefine_line|#define XFS_UQUOTA_ACTIVE&t;0x0080&t;/* uquotas are being turned off */
DECL|macro|XFS_GQUOTA_ACTIVE
mdefine_line|#define XFS_GQUOTA_ACTIVE&t;0x0100&t;/* gquotas are being turned off */
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
mdefine_line|#define XFS_QMOPT_DOWARN&t;0x0000400 /* increase warning cnt if necessary */
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
mdefine_line|#define XFS_TRANS_DQ_RES_RTBLKS XFS_QMOPT_RES_RTBLKS
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
multiline_comment|/*&n; * This check is done typically without holding the inode lock;&n; * that may seem racey, but it is harmless in the context that it is used.&n; * The inode cannot go inactive as long a reference is kept, and&n; * therefore if dquot(s) were attached, they&squot;ll stay consistent.&n; * If, for example, the ownership of the inode changes while&n; * we didnt have the inode locked, the appropriate dquot(s) will be&n; * attached atomically.&n; */
DECL|macro|XFS_NOT_DQATTACHED
mdefine_line|#define XFS_NOT_DQATTACHED(mp, ip) ((XFS_IS_UQUOTA_ON(mp) &amp;&amp;&bslash;&n;&t;&t;&t;&t;     (ip)-&gt;i_udquot == NULL) || &bslash;&n;&t;&t;&t;&t;    (XFS_IS_GQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (ip)-&gt;i_gdquot == NULL))
DECL|macro|XFS_QM_NEED_QUOTACHECK
mdefine_line|#define XFS_QM_NEED_QUOTACHECK(mp) ((XFS_IS_UQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (mp-&gt;m_sb.sb_qflags &amp; &bslash;&n;&t;&t;&t;&t;      XFS_UQUOTA_CHKD) == 0) || &bslash;&n;&t;&t;&t;&t;    (XFS_IS_GQUOTA_ON(mp) &amp;&amp; &bslash;&n;&t;&t;&t;&t;     (mp-&gt;m_sb.sb_qflags &amp; &bslash;&n;&t;&t;&t;&t;      XFS_GQUOTA_CHKD) == 0))
DECL|macro|XFS_MOUNT_QUOTA_ALL
mdefine_line|#define XFS_MOUNT_QUOTA_ALL&t;(XFS_UQUOTA_ACCT|XFS_UQUOTA_ENFD|&bslash;&n;&t;&t;&t;&t; XFS_UQUOTA_CHKD|XFS_GQUOTA_ACCT|&bslash;&n;&t;&t;&t;&t; XFS_GQUOTA_ENFD|XFS_GQUOTA_CHKD)
DECL|macro|XFS_MOUNT_QUOTA_MASK
mdefine_line|#define XFS_MOUNT_QUOTA_MASK&t;(XFS_MOUNT_QUOTA_ALL | XFS_UQUOTA_ACTIVE | &bslash;&n;&t;&t;&t;&t; XFS_GQUOTA_ACTIVE)
DECL|macro|XFS_IS_REALTIME_INODE
mdefine_line|#define XFS_IS_REALTIME_INODE(ip) ((ip)-&gt;i_d.di_flags &amp; XFS_DIFLAG_REALTIME)
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_XFS_QUOTA
multiline_comment|/*&n; * External Interface to the XFS disk quota subsystem.&n; */
r_struct
id|xfs_disk_dquot
suffix:semicolon
r_struct
id|xfs_dqhash
suffix:semicolon
r_struct
id|xfs_dquot
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Quota Manager Interface.&n; */
r_extern
r_struct
id|xfs_qm
op_star
id|xfs_qm_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_destroy
c_func
(paren
r_struct
id|xfs_qm
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqflush_all
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqattach
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqpurge_all
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_mount_quotainit
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_unmount_quotadestroy
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_mount_quotas
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_unmount_quotas
c_func
(paren
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqdettach_inode
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_sync
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Dquot interface.&n; */
r_extern
r_void
id|xfs_dqlock
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dqunlock
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dqunlock_nonotify
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dqlock2
c_func
(paren
r_struct
id|xfs_dquot
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqput
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqrele
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
id|xfs_dqid_t
id|xfs_qm_dqid
c_func
(paren
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqget
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|xfs_dqid_t
comma
id|uint
comma
id|uint
comma
r_struct
id|xfs_dquot
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqcheck
c_func
(paren
r_struct
id|xfs_disk_dquot
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
multiline_comment|/*&n; * Vnodeops specific code that should actually be _in_ xfs_vnodeops.c, but&n; * is here because it&squot;s nicer to keep vnodeops (therefore, XFS) lean&n; * and clean.&n; */
r_extern
r_struct
id|xfs_dquot
op_star
id|xfs_qm_vop_chown
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_dquot
op_star
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_vop_dqalloc
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_inode
op_star
comma
id|uid_t
comma
id|gid_t
comma
id|uint
comma
r_struct
id|xfs_dquot
op_star
op_star
comma
r_struct
id|xfs_dquot
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_vop_chown_reserve
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
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
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_vop_rename_dqattach
c_func
(paren
r_struct
id|xfs_inode
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_vop_dqattach_and_dqmod_newinode
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Dquot Transaction interface&n; */
r_extern
r_void
id|xfs_trans_alloc_dqinfo
c_func
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_free_dqinfo
c_func
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_dup_dqinfo
c_func
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
r_extern
r_void
id|xfs_trans_mod_dquot
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_dquot
op_star
comma
id|uint
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_mod_dquot_byino
c_func
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
r_extern
r_void
id|xfs_trans_apply_dquot_deltas
c_func
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_unreserve_and_mod_dquots
c_func
(paren
r_struct
id|xfs_trans
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_trans_reserve_quota_nblks
c_func
(paren
r_struct
id|xfs_trans
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
r_extern
r_int
id|xfs_trans_reserve_quota_bydquots
c_func
(paren
r_struct
id|xfs_trans
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
r_extern
r_void
id|xfs_trans_log_dquot
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_dqjoin
c_func
(paren
r_struct
id|xfs_trans
op_star
comma
r_struct
id|xfs_dquot
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqrele_all_inodes
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
id|uint
)paren
suffix:semicolon
DECL|macro|_XQM_ZONE_DESTROY
macro_line|# define _XQM_ZONE_DESTROY(z)&t;((z)? kmem_cache_destroy(z) : (void)0)
macro_line|#else
DECL|macro|xfs_qm_init
macro_line|# define xfs_qm_init()&t;&t;&t;&t;&t;(NULL)
DECL|macro|xfs_qm_destroy
macro_line|# define xfs_qm_destroy(xqm)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_dqflush_all
macro_line|# define xfs_qm_dqflush_all(m,t)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_dqattach
macro_line|# define xfs_qm_dqattach(i,t)&t;&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_dqpurge_all
macro_line|# define xfs_qm_dqpurge_all(m,t)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_mount_quotainit
macro_line|# define xfs_qm_mount_quotainit(m,t)&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_unmount_quotadestroy
macro_line|# define xfs_qm_unmount_quotadestroy(m)&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_mount_quotas
macro_line|# define xfs_qm_mount_quotas(m)&t;&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_unmount_quotas
macro_line|# define xfs_qm_unmount_quotas(m)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_dqdettach_inode
macro_line|# define xfs_qm_dqdettach_inode(i)&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_sync
macro_line|# define xfs_qm_sync(m,t)&t;&t;&t;&t;(ENOSYS)
DECL|macro|xfs_dqlock
macro_line|# define xfs_dqlock(d)&t;&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_dqunlock
macro_line|# define xfs_dqunlock(d)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_dqunlock_nonotify
macro_line|# define xfs_dqunlock_nonotify(d)&t;&t;&t;do { } while (0)
DECL|macro|xfs_dqlock2
macro_line|# define xfs_dqlock2(d1,d2)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_dqput
macro_line|# define xfs_qm_dqput(d)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_dqrele
macro_line|# define xfs_qm_dqrele(d)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_dqid
macro_line|# define xfs_qm_dqid(d)&t;&t;&t;&t;&t;(-1)
DECL|macro|xfs_qm_dqget
macro_line|# define xfs_qm_dqget(m,i,di,t,f,d)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_dqcheck
macro_line|# define xfs_qm_dqcheck(dd,di,t,f,s)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_trans_alloc_dqinfo
macro_line|# define xfs_trans_alloc_dqinfo(t)&t;&t;&t;do { } while (0)
DECL|macro|xfs_trans_free_dqinfo
macro_line|# define xfs_trans_free_dqinfo(t)&t;&t;&t;do { } while (0)
DECL|macro|xfs_trans_dup_dqinfo
macro_line|# define xfs_trans_dup_dqinfo(t1,t2)&t;&t;&t;do { } while (0)
DECL|macro|xfs_trans_mod_dquot
macro_line|# define xfs_trans_mod_dquot(t,d,f,x)&t;&t;&t;do { } while (0)
DECL|macro|xfs_trans_mod_dquot_byino
macro_line|# define xfs_trans_mod_dquot_byino(t,i,f,x)&t;&t;do { } while (0)
DECL|macro|xfs_trans_apply_dquot_deltas
macro_line|# define xfs_trans_apply_dquot_deltas(t)&t;&t;do { } while (0)
DECL|macro|xfs_trans_unreserve_and_mod_dquots
macro_line|# define xfs_trans_unreserve_and_mod_dquots(t)&t;&t;do { } while (0)
DECL|macro|xfs_trans_reserve_quota_nblks
macro_line|# define xfs_trans_reserve_quota_nblks(t,i,nb,ni,f)&t;(ENOSYS)
DECL|macro|xfs_trans_reserve_quota_bydquots
macro_line|# define xfs_trans_reserve_quota_bydquots(t,x,y,b,i,f)&t;(ENOSYS)
DECL|macro|xfs_trans_log_dquot
macro_line|# define xfs_trans_log_dquot(t,d)&t;&t;&t;do { } while (0)
DECL|macro|xfs_trans_dqjoin
macro_line|# define xfs_trans_dqjoin(t,d)&t;&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_dqrele_all_inodes
macro_line|# define xfs_qm_dqrele_all_inodes(m,t)&t;&t;&t;do { } while (0)
DECL|macro|xfs_qm_vop_chown
macro_line|# define xfs_qm_vop_chown(t,i,d1,d2)&t;&t;&t;(NULL)
DECL|macro|xfs_qm_vop_dqalloc
macro_line|# define xfs_qm_vop_dqalloc(m,i,u,g,f,d1,d2)&t;&t;(ENOSYS)
DECL|macro|xfs_qm_vop_chown_reserve
macro_line|# define xfs_qm_vop_chown_reserve(t,i,d1,d2,f)&t;&t;(ENOSYS)
DECL|macro|xfs_qm_vop_rename_dqattach
macro_line|# define xfs_qm_vop_rename_dqattach(i)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_qm_vop_dqattach_and_dqmod_newinode
macro_line|# define xfs_qm_vop_dqattach_and_dqmod_newinode(t,i,x,y) do { } while (0)
DECL|macro|_XQM_ZONE_DESTROY
macro_line|# define _XQM_ZONE_DESTROY(z)&t;&t;&t;&t;do { } while (0)
macro_line|#endif&t;/* CONFIG_XFS_QUOTA */
multiline_comment|/*&n; * Regular disk block quota reservations&n; */
DECL|macro|xfs_trans_reserve_blkquota
mdefine_line|#define&t;&t;xfs_trans_reserve_blkquota(tp, ip, nblks) &bslash;&n;xfs_trans_reserve_quota_nblks(tp, ip, nblks, 0, XFS_QMOPT_RES_REGBLKS)
DECL|macro|xfs_trans_reserve_blkquota_force
mdefine_line|#define&t;&t;xfs_trans_reserve_blkquota_force(tp, ip, nblks) &bslash;&n;xfs_trans_reserve_quota_nblks(tp, ip, nblks, 0, &bslash;&n;&t;&t;XFS_QMOPT_RES_REGBLKS|XFS_QMOPT_FORCE_RES)
DECL|macro|xfs_trans_unreserve_blkquota
mdefine_line|#define&t;&t;xfs_trans_unreserve_blkquota(tp, ip, nblks) &bslash;&n;(void)xfs_trans_reserve_quota_nblks(tp, ip, -(nblks), 0, XFS_QMOPT_RES_REGBLKS)
DECL|macro|xfs_trans_reserve_quota
mdefine_line|#define&t;&t;xfs_trans_reserve_quota(tp, udq, gdq, nb, ni, f) &bslash;&n;xfs_trans_reserve_quota_bydquots(tp, udq, gdq, nb, ni, f|XFS_QMOPT_RES_REGBLKS)
DECL|macro|xfs_trans_unreserve_quota
mdefine_line|#define&t;&t;xfs_trans_unreserve_quota(tp, ud, gd, b, i, f) &bslash;&n;xfs_trans_reserve_quota_bydquots(tp, ud, gd, -(b), -(i), f|XFS_QMOPT_RES_REGBLKS)
multiline_comment|/*&n; * Realtime disk block quota reservations&n; */
DECL|macro|xfs_trans_reserve_rtblkquota
mdefine_line|#define&t;&t;xfs_trans_reserve_rtblkquota(mp, tp, ip, nblks) &bslash;&n;xfs_trans_reserve_quota_nblks(tp, ip, nblks, 0, XFS_QMOPT_RES_RTBLKS)
DECL|macro|xfs_trans_unreserve_rtblkquota
mdefine_line|#define&t;&t;xfs_trans_unreserve_rtblkquota(tp, ip, nblks) &bslash;&n;(void)xfs_trans_reserve_quota_nblks(tp, ip, -(nblks), 0, XFS_QMOPT_RES_RTBLKS)
DECL|macro|xfs_trans_reserve_rtquota
mdefine_line|#define&t;&t;xfs_trans_reserve_rtquota(mp, tp, uq, pq, blks, f) &bslash;&n;xfs_trans_reserve_quota_bydquots(mp, tp, uq, pq, blks, 0, f|XFS_QMOPT_RES_RTBLKS)
DECL|macro|xfs_trans_unreserve_rtquota
mdefine_line|#define&t;&t;xfs_trans_unreserve_rtquota(tp, uq, pq, blks) &bslash;&n;xfs_trans_reserve_quota_bydquots(tp, uq, pq, -(blks), XFS_QMOPT_RES_RTBLKS)
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_QUOTA_H__ */
eof
