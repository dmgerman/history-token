multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_QM_H__
DECL|macro|__XFS_QM_H__
mdefine_line|#define __XFS_QM_H__
macro_line|#include &quot;xfs_dquot_item.h&quot;
macro_line|#include &quot;xfs_dquot.h&quot;
macro_line|#include &quot;xfs_quota_priv.h&quot;
macro_line|#include &quot;xfs_qm_stats.h&quot;
r_struct
id|xfs_qm
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_extern
id|mutex_t
id|xfs_Gqm_lock
suffix:semicolon
r_extern
r_struct
id|xfs_qm
op_star
id|xfs_Gqm
suffix:semicolon
r_extern
id|kmem_zone_t
op_star
id|qm_dqzone
suffix:semicolon
r_extern
id|kmem_zone_t
op_star
id|qm_dqtrxzone
suffix:semicolon
multiline_comment|/*&n; * Used in xfs_qm_sync called by xfs_sync to count the max times that it can&n; * iterate over the mountpt&squot;s dquot list in one call.&n; */
DECL|macro|XFS_QM_SYNC_MAX_RESTARTS
mdefine_line|#define XFS_QM_SYNC_MAX_RESTARTS&t;7
multiline_comment|/*&n; * Ditto, for xfs_qm_dqreclaim_one.&n; */
DECL|macro|XFS_QM_RECLAIM_MAX_RESTARTS
mdefine_line|#define XFS_QM_RECLAIM_MAX_RESTARTS&t;4
multiline_comment|/*&n; * Ideal ratio of free to in use dquots. Quota manager makes an attempt&n; * to keep this balance.&n; */
DECL|macro|XFS_QM_DQFREE_RATIO
mdefine_line|#define XFS_QM_DQFREE_RATIO&t;&t;2
multiline_comment|/*&n; * Dquot hashtable constants/threshold values.&n; */
DECL|macro|XFS_QM_NCSIZE_THRESHOLD
mdefine_line|#define XFS_QM_NCSIZE_THRESHOLD&t;&t;5000
DECL|macro|XFS_QM_HASHSIZE_LOW
mdefine_line|#define XFS_QM_HASHSIZE_LOW&t;&t;32
DECL|macro|XFS_QM_HASHSIZE_HIGH
mdefine_line|#define XFS_QM_HASHSIZE_HIGH&t;&t;64
multiline_comment|/*&n; * We output a cmn_err when quotachecking a quota file with more than&n; * this many fsbs.&n; */
DECL|macro|XFS_QM_BIG_QCHECK_NBLKS
mdefine_line|#define XFS_QM_BIG_QCHECK_NBLKS&t;&t;500
multiline_comment|/*&n; * This defines the unit of allocation of dquots.&n; * Currently, it is just one file system block, and a 4K blk contains 30&n; * (136 * 30 = 4080) dquots. It&squot;s probably not worth trying to make&n; * this more dynamic.&n; * XXXsup However, if this number is changed, we have to make sure that we don&squot;t&n; * implicitly assume that we do allocations in chunks of a single filesystem&n; * block in the dquot/xqm code.&n; */
DECL|macro|XFS_DQUOT_CLUSTER_SIZE_FSB
mdefine_line|#define XFS_DQUOT_CLUSTER_SIZE_FSB&t;(xfs_filblks_t)1
multiline_comment|/*&n; * When doing a quotacheck, we log dquot clusters of this many FSBs at most&n; * in a single transaction. We don&squot;t want to ask for too huge a log reservation.&n; */
DECL|macro|XFS_QM_MAX_DQCLUSTER_LOGSZ
mdefine_line|#define XFS_QM_MAX_DQCLUSTER_LOGSZ&t;3
DECL|typedef|xfs_dqlist_t
r_typedef
id|xfs_dqhash_t
id|xfs_dqlist_t
suffix:semicolon
multiline_comment|/*&n; * The freelist head. The first two fields match the first two in the&n; * xfs_dquot_t structure (in xfs_dqmarker_t)&n; */
DECL|struct|xfs_frlist
r_typedef
r_struct
id|xfs_frlist
(brace
DECL|member|qh_next
r_struct
id|xfs_dquot
op_star
id|qh_next
suffix:semicolon
DECL|member|qh_prev
r_struct
id|xfs_dquot
op_star
id|qh_prev
suffix:semicolon
DECL|member|qh_lock
id|mutex_t
id|qh_lock
suffix:semicolon
DECL|member|qh_version
id|uint
id|qh_version
suffix:semicolon
DECL|member|qh_nelems
id|uint
id|qh_nelems
suffix:semicolon
DECL|typedef|xfs_frlist_t
)brace
id|xfs_frlist_t
suffix:semicolon
multiline_comment|/*&n; * Quota Manager (global) structure. Lives only in core.&n; */
DECL|struct|xfs_qm
r_typedef
r_struct
id|xfs_qm
(brace
DECL|member|qm_usr_dqhtable
id|xfs_dqlist_t
op_star
id|qm_usr_dqhtable
suffix:semicolon
multiline_comment|/* udquot hash table */
DECL|member|qm_grp_dqhtable
id|xfs_dqlist_t
op_star
id|qm_grp_dqhtable
suffix:semicolon
multiline_comment|/* gdquot hash table */
DECL|member|qm_dqhashmask
id|uint
id|qm_dqhashmask
suffix:semicolon
multiline_comment|/* # buckets in dq hashtab - 1 */
DECL|member|qm_dqfreelist
id|xfs_frlist_t
id|qm_dqfreelist
suffix:semicolon
multiline_comment|/* freelist of dquots */
DECL|member|qm_totaldquots
id|atomic_t
id|qm_totaldquots
suffix:semicolon
multiline_comment|/* total incore dquots */
DECL|member|qm_nrefs
id|uint
id|qm_nrefs
suffix:semicolon
multiline_comment|/* file systems with quota on */
DECL|member|qm_dqfree_ratio
r_int
id|qm_dqfree_ratio
suffix:semicolon
multiline_comment|/* ratio of free to inuse dquots */
DECL|member|qm_dqzone
id|kmem_zone_t
op_star
id|qm_dqzone
suffix:semicolon
multiline_comment|/* dquot mem-alloc zone */
DECL|member|qm_dqtrxzone
id|kmem_zone_t
op_star
id|qm_dqtrxzone
suffix:semicolon
multiline_comment|/* t_dqinfo of transactions */
DECL|typedef|xfs_qm_t
)brace
id|xfs_qm_t
suffix:semicolon
multiline_comment|/*&n; * Various quota information for individual filesystems.&n; * The mount structure keeps a pointer to this.&n; */
DECL|struct|xfs_quotainfo
r_typedef
r_struct
id|xfs_quotainfo
(brace
DECL|member|qi_uquotaip
id|xfs_inode_t
op_star
id|qi_uquotaip
suffix:semicolon
multiline_comment|/* user quota inode */
DECL|member|qi_gquotaip
id|xfs_inode_t
op_star
id|qi_gquotaip
suffix:semicolon
multiline_comment|/* group quota inode */
DECL|member|qi_pinlock
id|lock_t
id|qi_pinlock
suffix:semicolon
multiline_comment|/* dquot pinning mutex */
DECL|member|qi_dqlist
id|xfs_dqlist_t
id|qi_dqlist
suffix:semicolon
multiline_comment|/* all dquots in filesys */
DECL|member|qi_dqreclaims
r_int
id|qi_dqreclaims
suffix:semicolon
multiline_comment|/* a change here indicates&n;&t;&t;&t;&t;&t;    a removal in the dqlist */
DECL|member|qi_btimelimit
id|time_t
id|qi_btimelimit
suffix:semicolon
multiline_comment|/* limit for blks timer */
DECL|member|qi_itimelimit
id|time_t
id|qi_itimelimit
suffix:semicolon
multiline_comment|/* limit for inodes timer */
DECL|member|qi_rtbtimelimit
id|time_t
id|qi_rtbtimelimit
suffix:semicolon
multiline_comment|/* limit for rt blks timer */
DECL|member|qi_bwarnlimit
id|xfs_qwarncnt_t
id|qi_bwarnlimit
suffix:semicolon
multiline_comment|/* limit for num warnings */
DECL|member|qi_iwarnlimit
id|xfs_qwarncnt_t
id|qi_iwarnlimit
suffix:semicolon
multiline_comment|/* limit for num warnings */
DECL|member|qi_quotaofflock
id|mutex_t
id|qi_quotaofflock
suffix:semicolon
multiline_comment|/* to serialize quotaoff */
DECL|member|qi_dqchunklen
id|xfs_filblks_t
id|qi_dqchunklen
suffix:semicolon
multiline_comment|/* # BBs in a chunk of dqs */
DECL|member|qi_dqperchunk
id|uint
id|qi_dqperchunk
suffix:semicolon
multiline_comment|/* # ondisk dqs in above chunk */
DECL|member|qi_bhardlimit
id|xfs_qcnt_t
id|qi_bhardlimit
suffix:semicolon
multiline_comment|/* default data blk hard limit */
DECL|member|qi_bsoftlimit
id|xfs_qcnt_t
id|qi_bsoftlimit
suffix:semicolon
multiline_comment|/* default data blk soft limit */
DECL|member|qi_ihardlimit
id|xfs_qcnt_t
id|qi_ihardlimit
suffix:semicolon
multiline_comment|/* default inode count hard limit */
DECL|member|qi_isoftlimit
id|xfs_qcnt_t
id|qi_isoftlimit
suffix:semicolon
multiline_comment|/* default inode count soft limit */
DECL|member|qi_rtbhardlimit
id|xfs_qcnt_t
id|qi_rtbhardlimit
suffix:semicolon
multiline_comment|/* default realtime blk hard limit */
DECL|member|qi_rtbsoftlimit
id|xfs_qcnt_t
id|qi_rtbsoftlimit
suffix:semicolon
multiline_comment|/* default realtime blk soft limit */
DECL|typedef|xfs_quotainfo_t
)brace
id|xfs_quotainfo_t
suffix:semicolon
r_extern
id|xfs_dqtrxops_t
id|xfs_trans_dquot_ops
suffix:semicolon
r_extern
r_void
id|xfs_trans_mod_dquot
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_dquot_t
op_star
comma
id|uint
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_trans_reserve_quota_bydquots
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_mount_t
op_star
comma
id|xfs_dquot_t
op_star
comma
id|xfs_dquot_t
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
id|xfs_trans_dqjoin
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_trans_log_dquot
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * We keep the usr and grp dquots separately so that locking will be easier&n; * to do at commit time. All transactions that we know of at this point&n; * affect no more than two dquots of one type. Hence, the TRANS_MAXDQS value.&n; */
DECL|macro|XFS_QM_TRANS_MAXDQS
mdefine_line|#define XFS_QM_TRANS_MAXDQS&t;&t;2
DECL|struct|xfs_dquot_acct
r_typedef
r_struct
id|xfs_dquot_acct
(brace
DECL|member|dqa_usrdquots
id|xfs_dqtrx_t
id|dqa_usrdquots
(braket
id|XFS_QM_TRANS_MAXDQS
)braket
suffix:semicolon
DECL|member|dqa_grpdquots
id|xfs_dqtrx_t
id|dqa_grpdquots
(braket
id|XFS_QM_TRANS_MAXDQS
)braket
suffix:semicolon
DECL|typedef|xfs_dquot_acct_t
)brace
id|xfs_dquot_acct_t
suffix:semicolon
multiline_comment|/*&n; * Users are allowed to have a usage exceeding their softlimit for&n; * a period this long.&n; */
DECL|macro|XFS_QM_BTIMELIMIT
mdefine_line|#define XFS_QM_BTIMELIMIT&t;(7 * 24*60*60)          /* 1 week */
DECL|macro|XFS_QM_RTBTIMELIMIT
mdefine_line|#define XFS_QM_RTBTIMELIMIT&t;(7 * 24*60*60)          /* 1 week */
DECL|macro|XFS_QM_ITIMELIMIT
mdefine_line|#define XFS_QM_ITIMELIMIT&t;(7 * 24*60*60)          /* 1 week */
DECL|macro|XFS_QM_BWARNLIMIT
mdefine_line|#define XFS_QM_BWARNLIMIT&t;5
DECL|macro|XFS_QM_IWARNLIMIT
mdefine_line|#define XFS_QM_IWARNLIMIT&t;5
DECL|macro|XFS_QM_LOCK
mdefine_line|#define XFS_QM_LOCK(xqm)&t;(mutex_lock(&amp;xqm##_lock, PINOD))
DECL|macro|XFS_QM_UNLOCK
mdefine_line|#define XFS_QM_UNLOCK(xqm)&t;(mutex_unlock(&amp;xqm##_lock))
DECL|macro|XFS_QM_HOLD
mdefine_line|#define XFS_QM_HOLD(xqm)&t;((xqm)-&gt;qm_nrefs++)
DECL|macro|XFS_QM_RELE
mdefine_line|#define XFS_QM_RELE(xqm)&t;((xqm)-&gt;qm_nrefs--)
r_extern
r_void
id|xfs_mount_reset_sbqflags
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_init_quotainfo
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_destroy_quotainfo
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_mount_quotas
c_func
(paren
id|xfs_mount_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_mount_quotainit
c_func
(paren
id|xfs_mount_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_quotacheck
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_unmount_quotadestroy
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_unmount_quotas
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_write_sb_changes
c_func
(paren
id|xfs_mount_t
op_star
comma
id|__int64_t
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_sync
c_func
(paren
id|xfs_mount_t
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* dquot stuff */
r_extern
id|boolean_t
id|xfs_qm_dqalloc_incore
c_func
(paren
id|xfs_dquot_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqattach
c_func
(paren
id|xfs_inode_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqdetach
c_func
(paren
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqpurge_all
c_func
(paren
id|xfs_mount_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqrele_all_inodes
c_func
(paren
id|xfs_mount_t
op_star
comma
id|uint
)paren
suffix:semicolon
multiline_comment|/* vop stuff */
r_extern
r_int
id|xfs_qm_vop_dqalloc
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_inode_t
op_star
comma
id|uid_t
comma
id|gid_t
comma
id|uint
comma
id|xfs_dquot_t
op_star
op_star
comma
id|xfs_dquot_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_vop_dqattach_and_dqmod_newinode
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_dquot_t
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_vop_rename_dqattach
c_func
(paren
id|xfs_inode_t
op_star
op_star
)paren
suffix:semicolon
r_extern
id|xfs_dquot_t
op_star
id|xfs_qm_vop_chown
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_dquot_t
op_star
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_vop_chown_reserve
c_func
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
comma
id|xfs_dquot_t
op_star
comma
id|xfs_dquot_t
op_star
comma
id|uint
)paren
suffix:semicolon
multiline_comment|/* list stuff */
r_extern
r_void
id|xfs_qm_freelist_init
c_func
(paren
id|xfs_frlist_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_freelist_destroy
c_func
(paren
id|xfs_frlist_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_freelist_insert
c_func
(paren
id|xfs_frlist_t
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_freelist_append
c_func
(paren
id|xfs_frlist_t
op_star
comma
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_freelist_unlink
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_freelist_lock_nowait
c_func
(paren
id|xfs_qm_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_mplist_nowait
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqhashlock_nowait
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
multiline_comment|/* system call interface */
r_extern
r_int
id|xfs_qm_quotactl
c_func
(paren
id|bhv_desc_t
op_star
comma
r_int
comma
r_int
comma
id|xfs_caddr_t
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_extern
r_int
id|xfs_qm_internalqcheck
c_func
(paren
id|xfs_mount_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_qm_internalqcheck
mdefine_line|#define xfs_qm_internalqcheck(mp)&t;(0)
macro_line|#endif
macro_line|#endif /* __XFS_QM_H__ */
eof
