multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_QUOTA_PRIV_H__
DECL|macro|__XFS_QUOTA_PRIV_H__
mdefine_line|#define __XFS_QUOTA_PRIV_H__
multiline_comment|/*&n; * Number of bmaps that we ask from bmapi when doing a quotacheck.&n; * We make this restriction to keep the memory usage to a minimum.&n; */
DECL|macro|XFS_DQITER_MAP_SIZE
mdefine_line|#define XFS_DQITER_MAP_SIZE&t;10
multiline_comment|/* Number of dquots that fit in to a dquot block */
DECL|macro|XFS_QM_DQPERBLK
mdefine_line|#define XFS_QM_DQPERBLK(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqperchunk)
DECL|macro|XFS_ISLOCKED_INODE
mdefine_line|#define XFS_ISLOCKED_INODE(ip)&t;&t;(ismrlocked(&amp;(ip)-&gt;i_lock, &bslash;&n;&t;&t;&t;&t;&t;    MR_UPDATE | MR_ACCESS) != 0)
DECL|macro|XFS_ISLOCKED_INODE_EXCL
mdefine_line|#define XFS_ISLOCKED_INODE_EXCL(ip)&t;(ismrlocked(&amp;(ip)-&gt;i_lock, &bslash;&n;&t;&t;&t;&t;&t;    MR_UPDATE) != 0)
DECL|macro|XFS_DQ_IS_ADDEDTO_TRX
mdefine_line|#define XFS_DQ_IS_ADDEDTO_TRX(t, d)&t;((d)-&gt;q_transp == (t))
DECL|macro|XFS_QI_MPLRECLAIMS
mdefine_line|#define XFS_QI_MPLRECLAIMS(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqreclaims)
DECL|macro|XFS_QI_UQIP
mdefine_line|#define XFS_QI_UQIP(mp)&t;&t;((mp)-&gt;m_quotainfo-&gt;qi_uquotaip)
DECL|macro|XFS_QI_GQIP
mdefine_line|#define XFS_QI_GQIP(mp)&t;&t;((mp)-&gt;m_quotainfo-&gt;qi_gquotaip)
DECL|macro|XFS_QI_DQCHUNKLEN
mdefine_line|#define XFS_QI_DQCHUNKLEN(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqchunklen)
DECL|macro|XFS_QI_BTIMELIMIT
mdefine_line|#define XFS_QI_BTIMELIMIT(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_btimelimit)
DECL|macro|XFS_QI_RTBTIMELIMIT
mdefine_line|#define XFS_QI_RTBTIMELIMIT(mp) ((mp)-&gt;m_quotainfo-&gt;qi_rtbtimelimit)
DECL|macro|XFS_QI_ITIMELIMIT
mdefine_line|#define XFS_QI_ITIMELIMIT(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_itimelimit)
DECL|macro|XFS_QI_BWARNLIMIT
mdefine_line|#define XFS_QI_BWARNLIMIT(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_bwarnlimit)
DECL|macro|XFS_QI_IWARNLIMIT
mdefine_line|#define XFS_QI_IWARNLIMIT(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_iwarnlimit)
DECL|macro|XFS_QI_QOFFLOCK
mdefine_line|#define XFS_QI_QOFFLOCK(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_quotaofflock)
DECL|macro|XFS_QI_MPL_LIST
mdefine_line|#define XFS_QI_MPL_LIST(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqlist)
DECL|macro|XFS_QI_MPLLOCK
mdefine_line|#define XFS_QI_MPLLOCK(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqlist.qh_lock)
DECL|macro|XFS_QI_MPLNEXT
mdefine_line|#define XFS_QI_MPLNEXT(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqlist.qh_next)
DECL|macro|XFS_QI_MPLNDQUOTS
mdefine_line|#define XFS_QI_MPLNDQUOTS(mp)&t;((mp)-&gt;m_quotainfo-&gt;qi_dqlist.qh_nelems)
DECL|macro|XQMLCK
mdefine_line|#define XQMLCK(h)&t;&t;&t;(mutex_lock(&amp;((h)-&gt;qh_lock), PINOD))
DECL|macro|XQMUNLCK
mdefine_line|#define XQMUNLCK(h)&t;&t;&t;(mutex_unlock(&amp;((h)-&gt;qh_lock)))
macro_line|#ifdef DEBUG
r_static
r_inline
r_int
DECL|function|XQMISLCKD
id|XQMISLCKD
c_func
(paren
id|xfs_dqhash_t
op_star
id|h
)paren
(brace
r_if
c_cond
(paren
id|mutex_trylock
c_func
(paren
op_amp
id|h-&gt;qh_lock
)paren
)paren
(brace
id|mutex_unlock
c_func
(paren
op_amp
id|h-&gt;qh_lock
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
DECL|macro|XFS_DQ_HASH_LOCK
mdefine_line|#define XFS_DQ_HASH_LOCK(h)&t;&t;XQMLCK(h)
DECL|macro|XFS_DQ_HASH_UNLOCK
mdefine_line|#define XFS_DQ_HASH_UNLOCK(h)&t;&t;XQMUNLCK(h)
DECL|macro|XFS_DQ_IS_HASH_LOCKED
mdefine_line|#define XFS_DQ_IS_HASH_LOCKED(h)&t;XQMISLCKD(h)
DECL|macro|xfs_qm_mplist_lock
mdefine_line|#define xfs_qm_mplist_lock(mp)&t;&t;XQMLCK(&amp;(XFS_QI_MPL_LIST(mp)))
DECL|macro|xfs_qm_mplist_unlock
mdefine_line|#define xfs_qm_mplist_unlock(mp)&t;XQMUNLCK(&amp;(XFS_QI_MPL_LIST(mp)))
DECL|macro|XFS_QM_IS_MPLIST_LOCKED
mdefine_line|#define XFS_QM_IS_MPLIST_LOCKED(mp)&t;XQMISLCKD(&amp;(XFS_QI_MPL_LIST(mp)))
DECL|macro|xfs_qm_freelist_lock
mdefine_line|#define xfs_qm_freelist_lock(qm)&t;XQMLCK(&amp;((qm)-&gt;qm_dqfreelist))
DECL|macro|xfs_qm_freelist_unlock
mdefine_line|#define xfs_qm_freelist_unlock(qm)&t;XQMUNLCK(&amp;((qm)-&gt;qm_dqfreelist))
DECL|macro|XFS_QM_IS_FREELIST_LOCKED
mdefine_line|#define XFS_QM_IS_FREELIST_LOCKED(qm)&t;XQMISLCKD(&amp;((qm)-&gt;qm_dqfreelist))
multiline_comment|/*&n; * Hash into a bucket in the dquot hash table, based on &lt;mp, id&gt;.&n; */
DECL|macro|XFS_DQ_HASHVAL
mdefine_line|#define XFS_DQ_HASHVAL(mp, id) (((__psunsigned_t)(mp) + &bslash;&n;&t;&t;&t;&t; (__psunsigned_t)(id)) &amp; &bslash;&n;&t;&t;&t;&t;(xfs_Gqm-&gt;qm_dqhashmask - 1))
DECL|macro|XFS_DQ_HASH
mdefine_line|#define XFS_DQ_HASH(mp, id, type)   (type == XFS_DQ_USER ? &bslash;&n;&t;&t;&t;&t;     (xfs_Gqm-&gt;qm_usr_dqhtable + &bslash;&n;&t;&t;&t;&t;      XFS_DQ_HASHVAL(mp, id)) : &bslash;&n;&t;&t;&t;&t;     (xfs_Gqm-&gt;qm_grp_dqhtable + &bslash;&n;&t;&t;&t;&t;      XFS_DQ_HASHVAL(mp, id)))
DECL|macro|XFS_IS_DQTYPE_ON
mdefine_line|#define XFS_IS_DQTYPE_ON(mp, type)   (type == XFS_DQ_USER ? &bslash;&n;&t;&t;&t;&t;      XFS_IS_UQUOTA_ON(mp):XFS_IS_GQUOTA_ON(mp))
DECL|macro|XFS_IS_DQUOT_UNINITIALIZED
mdefine_line|#define XFS_IS_DQUOT_UNINITIALIZED(dqp) ( &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_blk_hardlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_blk_softlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_rtb_hardlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_rtb_softlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_ino_hardlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_ino_softlimit, ARCH_CONVERT) &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_bcount, ARCH_CONVERT)&t;      &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_rtbcount, ARCH_CONVERT)      &amp;&amp; &bslash;&n;&t;INT_ISZERO(dqp-&gt;q_core.d_icount, ARCH_CONVERT))
DECL|macro|HL_PREVP
mdefine_line|#define HL_PREVP&t;dq_hashlist.ql_prevp
DECL|macro|HL_NEXT
mdefine_line|#define HL_NEXT&t;&t;dq_hashlist.ql_next
DECL|macro|MPL_PREVP
mdefine_line|#define MPL_PREVP&t;dq_mplist.ql_prevp
DECL|macro|MPL_NEXT
mdefine_line|#define MPL_NEXT&t;dq_mplist.ql_next
DECL|macro|_LIST_REMOVE
mdefine_line|#define _LIST_REMOVE(h, dqp, PVP, NXT)&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; xfs_dquot_t *d;&t;&t;&t;&t;&bslash;&n;&t;&t; if (((d) = (dqp)-&gt;NXT))&t;&t;&t;&t;&bslash;&n;&t;&t;&t; (d)-&gt;PVP = (dqp)-&gt;PVP;&t;&t;&t;&bslash;&n;&t;&t; *((dqp)-&gt;PVP) = d;&t;&t;&t;&t;&bslash;&n;&t;&t; (dqp)-&gt;NXT = NULL;&t;&t;&t;&t;&bslash;&n;&t;&t; (dqp)-&gt;PVP = NULL;&t;&t;&t;&t;&bslash;&n;&t;&t; (h)-&gt;qh_version++;&t;&t;&t;&t;&bslash;&n;&t;&t; (h)-&gt;qh_nelems--;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|_LIST_INSERT
mdefine_line|#define _LIST_INSERT(h, dqp, PVP, NXT)&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; xfs_dquot_t *d;&t;&t;&t;&t;&bslash;&n;&t;&t; if (((d) = (h)-&gt;qh_next))&t;&t;&t;&bslash;&n;&t;&t;&t; (d)-&gt;PVP = &amp;((dqp)-&gt;NXT);&t;&t;&bslash;&n;&t;&t; (dqp)-&gt;NXT = d;&t;&t;&t;&t;&bslash;&n;&t;&t; (dqp)-&gt;PVP = &amp;((h)-&gt;qh_next);&t;&t;&t;&bslash;&n;&t;&t; (h)-&gt;qh_next = dqp;&t;&t;&t;&t;&bslash;&n;&t;&t; (h)-&gt;qh_version++;&t;&t;&t;&t;&bslash;&n;&t;&t; (h)-&gt;qh_nelems++;&t;&t;&t;&t;&bslash;&n;&t; }
DECL|macro|FOREACH_DQUOT_IN_MP
mdefine_line|#define FOREACH_DQUOT_IN_MP(dqp, mp) &bslash;&n;&t;for ((dqp) = XFS_QI_MPLNEXT(mp); (dqp) != NULL; (dqp) = (dqp)-&gt;MPL_NEXT)
DECL|macro|FOREACH_DQUOT_IN_FREELIST
mdefine_line|#define FOREACH_DQUOT_IN_FREELIST(dqp, qlist)&t;&bslash;&n;for ((dqp) = (qlist)-&gt;qh_next; (dqp) != (xfs_dquot_t *)(qlist); &bslash;&n;     (dqp) = (dqp)-&gt;dq_flnext)
DECL|macro|XQM_HASHLIST_INSERT
mdefine_line|#define XQM_HASHLIST_INSERT(h, dqp)&t;&bslash;&n;&t; _LIST_INSERT(h, dqp, HL_PREVP, HL_NEXT)
DECL|macro|XQM_FREELIST_INSERT
mdefine_line|#define XQM_FREELIST_INSERT(h, dqp)&t;&bslash;&n;&t; xfs_qm_freelist_append(h, dqp)
DECL|macro|XQM_MPLIST_INSERT
mdefine_line|#define XQM_MPLIST_INSERT(h, dqp)&t;&bslash;&n;&t; _LIST_INSERT(h, dqp, MPL_PREVP, MPL_NEXT)
DECL|macro|XQM_HASHLIST_REMOVE
mdefine_line|#define XQM_HASHLIST_REMOVE(h, dqp)&t;&bslash;&n;&t; _LIST_REMOVE(h, dqp, HL_PREVP, HL_NEXT)
DECL|macro|XQM_FREELIST_REMOVE
mdefine_line|#define XQM_FREELIST_REMOVE(dqp)&t;&bslash;&n;&t; xfs_qm_freelist_unlink(dqp)
DECL|macro|XQM_MPLIST_REMOVE
mdefine_line|#define XQM_MPLIST_REMOVE(h, dqp)&t;&bslash;&n;&t;{ _LIST_REMOVE(h, dqp, MPL_PREVP, MPL_NEXT); &bslash;&n;&t;  XFS_QI_MPLRECLAIMS((dqp)-&gt;q_mount)++; }
DECL|macro|XFS_DQ_IS_LOGITEM_INITD
mdefine_line|#define XFS_DQ_IS_LOGITEM_INITD(dqp)&t;((dqp)-&gt;q_logitem.qli_dquot == (dqp))
DECL|macro|XFS_QM_DQP_TO_DQACCT
mdefine_line|#define XFS_QM_DQP_TO_DQACCT(tp, dqp)&t;(XFS_QM_ISUDQ(dqp) ? &bslash;&n;&t;&t;&t;&t;&t; (tp)-&gt;t_dqinfo-&gt;dqa_usrdquots : &bslash;&n;&t;&t;&t;&t;&t; (tp)-&gt;t_dqinfo-&gt;dqa_grpdquots)
DECL|macro|XFS_IS_SUSER_DQUOT
mdefine_line|#define XFS_IS_SUSER_DQUOT(dqp)&t;&t;&bslash;&n;&t;(INT_ISZERO((dqp)-&gt;q_core.d_id, ARCH_CONVERT))
DECL|macro|XFS_PURGE_INODE
mdefine_line|#define XFS_PURGE_INODE(ip)&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&bslash;&n;&t;  vmap_t dqvmap;&t;&t;&bslash;&n;&t;  vnode_t *dqvp;&t;&t;&bslash;&n;&t;  dqvp = XFS_ITOV(ip);&t;&t;&bslash;&n;&t;  VMAP(dqvp, ip, dqvmap);&t;&bslash;&n;&t;  VN_RELE(dqvp);&t;&t;&bslash;&n;&t;}
DECL|macro|DQFLAGTO_TYPESTR
mdefine_line|#define DQFLAGTO_TYPESTR(d)&t;(((d)-&gt;dq_flags &amp; XFS_DQ_USER) ? &quot;USR&quot; : &bslash;&n;&t;&t;&t;&t; (((d)-&gt;dq_flags &amp; XFS_DQ_GROUP) ? &quot;GRP&quot; : &quot;???&quot;))
DECL|macro|DQFLAGTO_DIRTYSTR
mdefine_line|#define DQFLAGTO_DIRTYSTR(d)&t;(XFS_DQ_IS_DIRTY(d) ? &quot;DIRTY&quot; : &quot;NOTDIRTY&quot;)
macro_line|#endif&t;/* __XFS_QUOTA_PRIV_H__ */
eof
