multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DQUOT_H__
DECL|macro|__XFS_DQUOT_H__
mdefine_line|#define __XFS_DQUOT_H__
multiline_comment|/*&n; * Dquots are structures that hold quota information about a user or a group,&n; * much like inodes are for files. In fact, dquots share many characteristics&n; * with inodes. However, dquots can also be a centralized resource, relative&n; * to a collection of inodes. In this respect, dquots share some characteristics&n; * of the superblock.&n; * XFS dquots exploit both those in its algorithms. They make every attempt&n; * to not be a bottleneck when quotas are on and have minimal impact, if any,&n; * when quotas are off.&n; */
multiline_comment|/*&n; * The hash chain headers (hash buckets)&n; */
DECL|struct|xfs_dqhash
r_typedef
r_struct
id|xfs_dqhash
(brace
DECL|member|qh_next
r_struct
id|xfs_dquot
op_star
id|qh_next
suffix:semicolon
DECL|member|qh_lock
id|mutex_t
id|qh_lock
suffix:semicolon
DECL|member|qh_version
id|uint
id|qh_version
suffix:semicolon
multiline_comment|/* ever increasing version */
DECL|member|qh_nelems
id|uint
id|qh_nelems
suffix:semicolon
multiline_comment|/* number of dquots on the list */
DECL|typedef|xfs_dqhash_t
)brace
id|xfs_dqhash_t
suffix:semicolon
DECL|struct|xfs_dqlink
r_typedef
r_struct
id|xfs_dqlink
(brace
DECL|member|ql_next
r_struct
id|xfs_dquot
op_star
id|ql_next
suffix:semicolon
multiline_comment|/* forward link */
DECL|member|ql_prevp
r_struct
id|xfs_dquot
op_star
op_star
id|ql_prevp
suffix:semicolon
multiline_comment|/* pointer to prev ql_next */
DECL|typedef|xfs_dqlink_t
)brace
id|xfs_dqlink_t
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * This is the marker which is designed to occupy the first few&n; * bytes of the xfs_dquot_t structure. Even inside this, the freelist pointers&n; * must come first.&n; * This serves as the marker (&quot;sentinel&quot;) when we have to restart list&n; * iterations because of locking considerations.&n; */
DECL|struct|xfs_dqmarker
r_typedef
r_struct
id|xfs_dqmarker
(brace
DECL|member|dqm_flnext
r_struct
id|xfs_dquot
op_star
id|dqm_flnext
suffix:semicolon
multiline_comment|/* link to freelist: must be first */
DECL|member|dqm_flprev
r_struct
id|xfs_dquot
op_star
id|dqm_flprev
suffix:semicolon
DECL|member|dqm_mplist
id|xfs_dqlink_t
id|dqm_mplist
suffix:semicolon
multiline_comment|/* link to mount&squot;s list of dquots */
DECL|member|dqm_hashlist
id|xfs_dqlink_t
id|dqm_hashlist
suffix:semicolon
multiline_comment|/* link to the hash chain */
DECL|member|dqm_flags
id|uint
id|dqm_flags
suffix:semicolon
multiline_comment|/* various flags (XFS_DQ_*) */
DECL|typedef|xfs_dqmarker_t
)brace
id|xfs_dqmarker_t
suffix:semicolon
multiline_comment|/*&n; * The incore dquot structure&n; */
DECL|struct|xfs_dquot
r_typedef
r_struct
id|xfs_dquot
(brace
DECL|member|q_lists
id|xfs_dqmarker_t
id|q_lists
suffix:semicolon
multiline_comment|/* list ptrs, q_flags (marker) */
DECL|member|q_hash
id|xfs_dqhash_t
op_star
id|q_hash
suffix:semicolon
multiline_comment|/* the hashchain header */
DECL|member|q_mount
r_struct
id|xfs_mount
op_star
id|q_mount
suffix:semicolon
multiline_comment|/* filesystem this relates to */
DECL|member|q_transp
r_struct
id|xfs_trans
op_star
id|q_transp
suffix:semicolon
multiline_comment|/* trans this belongs to currently */
DECL|member|q_nrefs
id|uint
id|q_nrefs
suffix:semicolon
multiline_comment|/* # active refs from inodes */
DECL|member|q_blkno
id|xfs_daddr_t
id|q_blkno
suffix:semicolon
multiline_comment|/* blkno of dquot buffer */
DECL|member|q_bufoffset
r_int
id|q_bufoffset
suffix:semicolon
multiline_comment|/* off of dq in buffer (# dquots) */
DECL|member|q_fileoffset
id|xfs_fileoff_t
id|q_fileoffset
suffix:semicolon
multiline_comment|/* offset in quotas file */
DECL|member|q_gdquot
r_struct
id|xfs_dquot
op_star
id|q_gdquot
suffix:semicolon
multiline_comment|/* group dquot, hint only */
DECL|member|q_core
id|xfs_disk_dquot_t
id|q_core
suffix:semicolon
multiline_comment|/* actual usage &amp; quotas */
DECL|member|q_logitem
id|xfs_dq_logitem_t
id|q_logitem
suffix:semicolon
multiline_comment|/* dquot log item */
DECL|member|q_res_bcount
id|xfs_qcnt_t
id|q_res_bcount
suffix:semicolon
multiline_comment|/* total regular nblks used+reserved */
DECL|member|q_res_icount
id|xfs_qcnt_t
id|q_res_icount
suffix:semicolon
multiline_comment|/* total inos allocd+reserved */
DECL|member|q_res_rtbcount
id|xfs_qcnt_t
id|q_res_rtbcount
suffix:semicolon
multiline_comment|/* total realtime blks used+reserved */
DECL|member|q_qlock
id|mutex_t
id|q_qlock
suffix:semicolon
multiline_comment|/* quota lock */
DECL|member|q_flock
id|sema_t
id|q_flock
suffix:semicolon
multiline_comment|/* flush lock */
DECL|member|q_pincount
id|uint
id|q_pincount
suffix:semicolon
multiline_comment|/* pin count for this dquot */
DECL|member|q_pinwait
id|sv_t
id|q_pinwait
suffix:semicolon
multiline_comment|/* sync var for pinning */
macro_line|#ifdef DQUOT_TRACING
DECL|member|q_trace
r_struct
id|ktrace
op_star
id|q_trace
suffix:semicolon
multiline_comment|/* trace header structure */
macro_line|#endif
DECL|typedef|xfs_dquot_t
)brace
id|xfs_dquot_t
suffix:semicolon
DECL|macro|dq_flnext
mdefine_line|#define dq_flnext&t;q_lists.dqm_flnext
DECL|macro|dq_flprev
mdefine_line|#define dq_flprev&t;q_lists.dqm_flprev
DECL|macro|dq_mplist
mdefine_line|#define dq_mplist&t;q_lists.dqm_mplist
DECL|macro|dq_hashlist
mdefine_line|#define dq_hashlist&t;q_lists.dqm_hashlist
DECL|macro|dq_flags
mdefine_line|#define dq_flags&t;q_lists.dqm_flags
DECL|macro|XFS_DQHOLD
mdefine_line|#define XFS_DQHOLD(dqp)&t;&t;((dqp)-&gt;q_nrefs++)
multiline_comment|/*&n; * Quota Accounting flags&n; */
DECL|macro|XFS_ALL_QUOTA_ACCT
mdefine_line|#define XFS_ALL_QUOTA_ACCT&t;(XFS_UQUOTA_ACCT | XFS_GQUOTA_ACCT)
DECL|macro|XFS_ALL_QUOTA_ENFD
mdefine_line|#define XFS_ALL_QUOTA_ENFD&t;(XFS_UQUOTA_ENFD | XFS_GQUOTA_ENFD)
DECL|macro|XFS_ALL_QUOTA_CHKD
mdefine_line|#define XFS_ALL_QUOTA_CHKD&t;(XFS_UQUOTA_CHKD | XFS_GQUOTA_CHKD)
DECL|macro|XFS_ALL_QUOTA_ACTV
mdefine_line|#define XFS_ALL_QUOTA_ACTV&t;(XFS_UQUOTA_ACTIVE | XFS_GQUOTA_ACTIVE)
DECL|macro|XFS_ALL_QUOTA_ACCT_ENFD
mdefine_line|#define XFS_ALL_QUOTA_ACCT_ENFD (XFS_UQUOTA_ACCT|XFS_UQUOTA_ENFD|&bslash;&n;&t;&t;&t;&t; XFS_GQUOTA_ACCT|XFS_GQUOTA_ENFD)
DECL|macro|XFS_IS_QUOTA_RUNNING
mdefine_line|#define XFS_IS_QUOTA_RUNNING(mp)  ((mp)-&gt;m_qflags &amp; XFS_ALL_QUOTA_ACCT)
DECL|macro|XFS_IS_UQUOTA_RUNNING
mdefine_line|#define XFS_IS_UQUOTA_RUNNING(mp) ((mp)-&gt;m_qflags &amp; XFS_UQUOTA_ACCT)
DECL|macro|XFS_IS_GQUOTA_RUNNING
mdefine_line|#define XFS_IS_GQUOTA_RUNNING(mp) ((mp)-&gt;m_qflags &amp; XFS_GQUOTA_ACCT)
multiline_comment|/*&n; * Quota Limit Enforcement flags&n; */
DECL|macro|XFS_IS_QUOTA_ENFORCED
mdefine_line|#define XFS_IS_QUOTA_ENFORCED(mp)&t;((mp)-&gt;m_qflags &amp; XFS_ALL_QUOTA_ENFD)
DECL|macro|XFS_IS_UQUOTA_ENFORCED
mdefine_line|#define XFS_IS_UQUOTA_ENFORCED(mp)&t;((mp)-&gt;m_qflags &amp; XFS_UQUOTA_ENFD)
DECL|macro|XFS_IS_GQUOTA_ENFORCED
mdefine_line|#define XFS_IS_GQUOTA_ENFORCED(mp)&t;((mp)-&gt;m_qflags &amp; XFS_GQUOTA_ENFD)
macro_line|#ifdef DEBUG
r_static
r_inline
r_int
DECL|function|XFS_DQ_IS_LOCKED
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|xfs_dquot_t
op_star
id|dqp
)paren
(brace
r_if
c_cond
(paren
id|mutex_trylock
c_func
(paren
op_amp
id|dqp-&gt;q_qlock
)paren
)paren
(brace
id|mutex_unlock
c_func
(paren
op_amp
id|dqp-&gt;q_qlock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * The following three routines simply manage the q_flock&n; * semaphore embedded in the dquot.  This semaphore synchronizes&n; * processes attempting to flush the in-core dquot back to disk.&n; */
DECL|macro|xfs_dqflock
mdefine_line|#define xfs_dqflock(dqp)&t; { psema(&amp;((dqp)-&gt;q_flock), PINOD | PRECALC);&bslash;&n;&t;&t;&t;&t;   (dqp)-&gt;dq_flags |= XFS_DQ_FLOCKED; }
DECL|macro|xfs_dqfunlock
mdefine_line|#define xfs_dqfunlock(dqp)&t; { ASSERT(valusema(&amp;((dqp)-&gt;q_flock)) &lt;= 0); &bslash;&n;&t;&t;&t;&t;   vsema(&amp;((dqp)-&gt;q_flock)); &bslash;&n;&t;&t;&t;&t;   (dqp)-&gt;dq_flags &amp;= ~(XFS_DQ_FLOCKED); }
DECL|macro|XFS_DQ_PINLOCK
mdefine_line|#define XFS_DQ_PINLOCK(dqp)&t;   mutex_spinlock( &bslash;&n;&t;&t;&t;&t;     &amp;(XFS_DQ_TO_QINF(dqp)-&gt;qi_pinlock))
DECL|macro|XFS_DQ_PINUNLOCK
mdefine_line|#define XFS_DQ_PINUNLOCK(dqp, s)   mutex_spinunlock( &bslash;&n;&t;&t;&t;&t;     &amp;(XFS_DQ_TO_QINF(dqp)-&gt;qi_pinlock), s)
DECL|macro|XFS_DQ_IS_FLUSH_LOCKED
mdefine_line|#define XFS_DQ_IS_FLUSH_LOCKED(dqp) (valusema(&amp;((dqp)-&gt;q_flock)) &lt;= 0)
DECL|macro|XFS_DQ_IS_ON_FREELIST
mdefine_line|#define XFS_DQ_IS_ON_FREELIST(dqp)  ((dqp)-&gt;dq_flnext != (dqp))
DECL|macro|XFS_DQ_IS_DIRTY
mdefine_line|#define XFS_DQ_IS_DIRTY(dqp)&t;((dqp)-&gt;dq_flags &amp; XFS_DQ_DIRTY)
DECL|macro|XFS_QM_ISUDQ
mdefine_line|#define XFS_QM_ISUDQ(dqp)&t;((dqp)-&gt;dq_flags &amp; XFS_DQ_USER)
DECL|macro|XFS_DQ_TO_QINF
mdefine_line|#define XFS_DQ_TO_QINF(dqp)&t;((dqp)-&gt;q_mount-&gt;m_quotainfo)
DECL|macro|XFS_DQ_TO_QIP
mdefine_line|#define XFS_DQ_TO_QIP(dqp)&t;(XFS_QM_ISUDQ(dqp) ? &bslash;&n;&t;&t;&t;&t; XFS_DQ_TO_QINF(dqp)-&gt;qi_uquotaip : &bslash;&n;&t;&t;&t;&t; XFS_DQ_TO_QINF(dqp)-&gt;qi_gquotaip)
DECL|macro|XFS_IS_THIS_QUOTA_OFF
mdefine_line|#define XFS_IS_THIS_QUOTA_OFF(d) (! (XFS_QM_ISUDQ(d) ? &bslash;&n;&t;&t;&t;&t;     (XFS_IS_UQUOTA_ON((d)-&gt;q_mount)) : &bslash;&n;&t;&t;&t;&t;     (XFS_IS_GQUOTA_ON((d)-&gt;q_mount))))
macro_line|#ifdef DQUOT_TRACING
multiline_comment|/*&n; * Dquot Tracing stuff.&n; */
DECL|macro|DQUOT_TRACE_SIZE
mdefine_line|#define DQUOT_TRACE_SIZE&t;64
DECL|macro|DQUOT_KTRACE_ENTRY
mdefine_line|#define DQUOT_KTRACE_ENTRY&t;1
DECL|macro|xfs_dqtrace_entry_ino
mdefine_line|#define xfs_dqtrace_entry_ino(a,b,ip) &bslash;&n;xfs_dqtrace_entry__((a), (b), (void*)__return_address, (ip))
DECL|macro|xfs_dqtrace_entry
mdefine_line|#define xfs_dqtrace_entry(a,b) &bslash;&n;xfs_dqtrace_entry__((a), (b), (void*)__return_address, NULL)
r_extern
r_void
id|xfs_dqtrace_entry__
c_func
(paren
id|xfs_dquot_t
op_star
id|dqp
comma
r_char
op_star
id|func
comma
r_void
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_dqtrace_entry
mdefine_line|#define xfs_dqtrace_entry(a,b)
DECL|macro|xfs_dqtrace_entry_ino
mdefine_line|#define xfs_dqtrace_entry_ino(a,b,ip)
macro_line|#endif
macro_line|#ifdef QUOTADEBUG
r_extern
r_void
id|xfs_qm_dqprint
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_qm_dqprint
mdefine_line|#define xfs_qm_dqprint(a)
macro_line|#endif
r_extern
id|xfs_dquot_t
op_star
id|xfs_qm_dqinit
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_dqid_t
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqdestroy
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqflush
c_func
(paren
id|xfs_dquot_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqpurge
c_func
(paren
id|xfs_dquot_t
op_star
comma
id|uint
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqunpin_wait
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqlock_nowait
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqflock_nowait
c_func
(paren
id|xfs_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_dqflock_pushbuf_wait
c_func
(paren
id|xfs_dquot_t
op_star
id|dqp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_qm_adjust_dqtimers
c_func
(paren
id|xfs_mount_t
op_star
comma
id|xfs_disk_dquot_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_qm_dqwarn
c_func
(paren
id|xfs_disk_dquot_t
op_star
comma
id|uint
)paren
suffix:semicolon
macro_line|#endif /* __XFS_DQUOT_H__ */
eof
