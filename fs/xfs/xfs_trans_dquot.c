multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
macro_line|#include &lt;xfs_quota_priv.h&gt;
multiline_comment|/*&n; * Add the locked dquot to the transaction.&n; * The dquot must be locked, and it cannot be associated with any&n; * transaction.&n; */
r_void
DECL|function|xfs_trans_dqjoin
id|xfs_trans_dqjoin
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|dqp
)paren
(brace
id|xfs_dq_logitem_t
op_star
id|lp
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
id|XFS_DQ_IS_ADDEDTO_TRX
c_func
(paren
id|tp
comma
id|dqp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOGITEM_INITD
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|lp
op_assign
op_amp
id|dqp-&gt;q_logitem
suffix:semicolon
multiline_comment|/*&n;&t; * Get a log_item_desc to point at the new item.&n;&t; */
(paren
r_void
)paren
id|xfs_trans_add_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
(paren
id|lp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize i_transp so we can later determine if this dquot is&n;&t; * associated with this transaction.&n;&t; */
id|dqp-&gt;q_transp
op_assign
id|tp
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to mark the dquot as needing&n; * to be logged when the transaction is committed.  The dquot must&n; * already be associated with the given transaction.&n; * Note that it marks the entire transaction as dirty. In the ordinary&n; * case, this gets called via xfs_trans_commit, after the transaction&n; * is already dirty. However, there&squot;s nothing stop this from getting&n; * called directly, as done by xfs_qm_scall_setqlim. Hence, the TRANS_DIRTY&n; * flag.&n; */
r_void
DECL|function|xfs_trans_log_dquot
id|xfs_trans_log_dquot
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|dqp
)paren
(brace
id|xfs_log_item_desc_t
op_star
id|lidp
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_ADDEDTO_TRX
c_func
(paren
id|tp
comma
id|dqp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|lidp
op_assign
id|xfs_trans_find_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
(paren
op_amp
id|dqp-&gt;q_logitem
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lidp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|tp-&gt;t_flags
op_or_assign
id|XFS_TRANS_DIRTY
suffix:semicolon
id|lidp-&gt;lid_flags
op_or_assign
id|XFS_LID_DIRTY
suffix:semicolon
)brace
multiline_comment|/*&n; * Carry forward whatever is left of the quota blk reservation to&n; * the spanky new transaction&n; */
r_void
DECL|function|xfs_trans_dup_dqinfo
id|xfs_trans_dup_dqinfo
c_func
(paren
id|xfs_trans_t
op_star
id|otp
comma
id|xfs_trans_t
op_star
id|ntp
)paren
(brace
id|xfs_dqtrx_t
op_star
id|oq
comma
op_star
id|nq
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|xfs_dqtrx_t
op_star
id|oqa
comma
op_star
id|nqa
suffix:semicolon
id|xfs_trans_alloc_dqinfo
c_func
(paren
id|ntp
)paren
suffix:semicolon
id|oqa
op_assign
id|otp-&gt;t_dqinfo-&gt;dqa_usrdquots
suffix:semicolon
id|nqa
op_assign
id|ntp-&gt;t_dqinfo-&gt;dqa_usrdquots
suffix:semicolon
multiline_comment|/*&n;&t; * Because the quota blk reservation is carried forward,&n;&t; * it is also necessary to carry forward the DQ_DIRTY flag.&n;&t; */
r_if
c_cond
(paren
id|otp-&gt;t_flags
op_amp
id|XFS_TRANS_DQ_DIRTY
)paren
(brace
id|ntp-&gt;t_flags
op_or_assign
id|XFS_TRANS_DQ_DIRTY
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFS_QM_TRANS_MAXDQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|oqa
(braket
id|i
)braket
dot
id|qt_dquot
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|oq
op_assign
op_amp
id|oqa
(braket
id|i
)braket
suffix:semicolon
id|nq
op_assign
op_amp
id|nqa
(braket
id|i
)braket
suffix:semicolon
id|nq-&gt;qt_dquot
op_assign
id|oq-&gt;qt_dquot
suffix:semicolon
id|nq-&gt;qt_bcount_delta
op_assign
id|nq-&gt;qt_icount_delta
op_assign
l_int|0
suffix:semicolon
id|nq-&gt;qt_rtbcount_delta
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Transfer whatever is left of the reservations.&n;&t;&t;&t; */
id|nq-&gt;qt_blk_res
op_assign
id|oq-&gt;qt_blk_res
op_minus
id|oq-&gt;qt_blk_res_used
suffix:semicolon
id|oq-&gt;qt_blk_res
op_assign
id|oq-&gt;qt_blk_res_used
suffix:semicolon
id|nq-&gt;qt_rtblk_res
op_assign
id|oq-&gt;qt_rtblk_res
op_minus
id|oq-&gt;qt_rtblk_res_used
suffix:semicolon
id|oq-&gt;qt_rtblk_res
op_assign
id|oq-&gt;qt_rtblk_res_used
suffix:semicolon
id|nq-&gt;qt_ino_res
op_assign
id|oq-&gt;qt_ino_res
op_minus
id|oq-&gt;qt_ino_res_used
suffix:semicolon
id|oq-&gt;qt_ino_res
op_assign
id|oq-&gt;qt_ino_res_used
suffix:semicolon
)brace
id|oqa
op_assign
id|otp-&gt;t_dqinfo-&gt;dqa_grpdquots
suffix:semicolon
id|nqa
op_assign
id|ntp-&gt;t_dqinfo-&gt;dqa_grpdquots
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Wrap around mod_dquot to account for both user and group quotas.&n; */
r_void
DECL|function|xfs_trans_mod_dquot_byino
id|xfs_trans_mod_dquot_byino
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
comma
id|uint
id|field
comma
r_int
id|delta
)paren
(brace
id|ASSERT
c_func
(paren
id|tp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;t_dqinfo
op_eq
l_int|NULL
)paren
id|xfs_trans_alloc_dqinfo
c_func
(paren
id|tp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|XFS_IS_UQUOTA_ON
c_func
(paren
id|tp-&gt;t_mountp
)paren
op_logical_and
id|ip-&gt;i_udquot
)paren
(brace
(paren
r_void
)paren
id|xfs_trans_mod_dquot
c_func
(paren
id|tp
comma
id|ip-&gt;i_udquot
comma
id|field
comma
id|delta
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|XFS_IS_GQUOTA_ON
c_func
(paren
id|tp-&gt;t_mountp
)paren
op_logical_and
id|ip-&gt;i_gdquot
)paren
(brace
(paren
r_void
)paren
id|xfs_trans_mod_dquot
c_func
(paren
id|tp
comma
id|ip-&gt;i_gdquot
comma
id|field
comma
id|delta
)paren
suffix:semicolon
)brace
)brace
id|STATIC
id|xfs_dqtrx_t
op_star
DECL|function|xfs_trans_get_dqtrx
id|xfs_trans_get_dqtrx
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|dqp
)paren
(brace
r_int
id|i
suffix:semicolon
id|xfs_dqtrx_t
op_star
id|qa
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFS_QM_TRANS_MAXDQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|qa
op_assign
id|XFS_QM_DQP_TO_DQACCT
c_func
(paren
id|tp
comma
id|dqp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qa
(braket
id|i
)braket
dot
id|qt_dquot
op_eq
l_int|NULL
op_logical_or
id|qa
(braket
id|i
)braket
dot
id|qt_dquot
op_eq
id|dqp
)paren
(brace
r_return
(paren
op_amp
id|qa
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make the changes in the transaction structure.&n; * The moral equivalent to xfs_trans_mod_sb().&n; * We don&squot;t touch any fields in the dquot, so we don&squot;t care&n; * if it&squot;s locked or not (most of the time it won&squot;t be).&n; */
r_void
DECL|function|xfs_trans_mod_dquot
id|xfs_trans_mod_dquot
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|dqp
comma
id|uint
id|field
comma
r_int
id|delta
)paren
(brace
id|xfs_dqtrx_t
op_star
id|qtrx
suffix:semicolon
id|ASSERT
c_func
(paren
id|tp
)paren
suffix:semicolon
id|qtrx
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;t_dqinfo
op_eq
l_int|NULL
)paren
id|xfs_trans_alloc_dqinfo
c_func
(paren
id|tp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find either the first free slot or the slot that belongs&n;&t; * to this dquot.&n;&t; */
id|qtrx
op_assign
id|xfs_trans_get_dqtrx
c_func
(paren
id|tp
comma
id|dqp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|qtrx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qtrx-&gt;qt_dquot
op_eq
l_int|NULL
)paren
id|qtrx-&gt;qt_dquot
op_assign
id|dqp
suffix:semicolon
r_switch
c_cond
(paren
id|field
)paren
(brace
multiline_comment|/*&n;&t;&t; * regular disk blk reservation&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_RES_BLKS
suffix:colon
id|qtrx-&gt;qt_blk_res
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * inode reservation&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_RES_INOS
suffix:colon
id|qtrx-&gt;qt_ino_res
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * disk blocks used.&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_BCOUNT
suffix:colon
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
op_logical_and
id|delta
OG
l_int|0
)paren
(brace
id|qtrx-&gt;qt_blk_res_used
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
id|ASSERT
c_func
(paren
id|qtrx-&gt;qt_blk_res
op_ge
id|qtrx-&gt;qt_blk_res_used
)paren
suffix:semicolon
)brace
id|qtrx-&gt;qt_bcount_delta
op_add_assign
id|delta
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_TRANS_DQ_DELBCOUNT
suffix:colon
id|qtrx-&gt;qt_delbcnt_delta
op_add_assign
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Inode Count&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_ICOUNT
suffix:colon
r_if
c_cond
(paren
id|qtrx-&gt;qt_ino_res
op_logical_and
id|delta
OG
l_int|0
)paren
(brace
id|qtrx-&gt;qt_ino_res_used
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
id|ASSERT
c_func
(paren
id|qtrx-&gt;qt_ino_res
op_ge
id|qtrx-&gt;qt_ino_res_used
)paren
suffix:semicolon
)brace
id|qtrx-&gt;qt_icount_delta
op_add_assign
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * rtblk reservation&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_RES_RTBLKS
suffix:colon
id|qtrx-&gt;qt_rtblk_res
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * rtblk count&n;&t;&t; */
r_case
id|XFS_TRANS_DQ_RTBCOUNT
suffix:colon
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtblk_res
op_logical_and
id|delta
OG
l_int|0
)paren
(brace
id|qtrx-&gt;qt_rtblk_res_used
op_add_assign
(paren
id|ulong
)paren
id|delta
suffix:semicolon
id|ASSERT
c_func
(paren
id|qtrx-&gt;qt_rtblk_res
op_ge
id|qtrx-&gt;qt_rtblk_res_used
)paren
suffix:semicolon
)brace
id|qtrx-&gt;qt_rtbcount_delta
op_add_assign
id|delta
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_TRANS_DQ_DELRTBCOUNT
suffix:colon
id|qtrx-&gt;qt_delrtb_delta
op_add_assign
id|delta
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|tp-&gt;t_flags
op_or_assign
id|XFS_TRANS_DQ_DIRTY
suffix:semicolon
)brace
multiline_comment|/*&n; * Given an array of dqtrx structures, lock all the dquots associated&n; * and join them to the transaction, provided they have been modified.&n; * We know that the highest number of dquots (of one type - usr OR grp),&n; * involved in a transaction is 2 and that both usr and grp combined - 3.&n; * So, we don&squot;t attempt to make this very generic.&n; */
id|STATIC
r_void
DECL|function|xfs_trans_dqlockedjoin
id|xfs_trans_dqlockedjoin
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dqtrx_t
op_star
id|q
)paren
(brace
id|ASSERT
c_func
(paren
id|q
(braket
l_int|0
)braket
dot
id|qt_dquot
op_ne
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
(braket
l_int|1
)braket
dot
id|qt_dquot
op_eq
l_int|NULL
)paren
(brace
id|xfs_dqlock
c_func
(paren
id|q
(braket
l_int|0
)braket
dot
id|qt_dquot
)paren
suffix:semicolon
id|xfs_trans_dqjoin
c_func
(paren
id|tp
comma
id|q
(braket
l_int|0
)braket
dot
id|qt_dquot
)paren
suffix:semicolon
)brace
r_else
(brace
id|ASSERT
c_func
(paren
id|XFS_QM_TRANS_MAXDQS
op_eq
l_int|2
)paren
suffix:semicolon
id|xfs_dqlock2
c_func
(paren
id|q
(braket
l_int|0
)braket
dot
id|qt_dquot
comma
id|q
(braket
l_int|1
)braket
dot
id|qt_dquot
)paren
suffix:semicolon
id|xfs_trans_dqjoin
c_func
(paren
id|tp
comma
id|q
(braket
l_int|0
)braket
dot
id|qt_dquot
)paren
suffix:semicolon
id|xfs_trans_dqjoin
c_func
(paren
id|tp
comma
id|q
(braket
l_int|1
)braket
dot
id|qt_dquot
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called by xfs_trans_commit() and similar in spirit to&n; * xfs_trans_apply_sb_deltas().&n; * Go thru all the dquots belonging to this transaction and modify the&n; * INCORE dquot to reflect the actual usages.&n; * Unreserve just the reservations done by this transaction&n; * dquot is still left locked at exit.&n; */
r_void
DECL|function|xfs_trans_apply_dquot_deltas
id|xfs_trans_apply_dquot_deltas
c_func
(paren
id|xfs_trans_t
op_star
id|tp
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|xfs_dqtrx_t
op_star
id|qtrx
comma
op_star
id|qa
suffix:semicolon
id|xfs_disk_dquot_t
op_star
id|d
suffix:semicolon
r_int
id|totalbdelta
suffix:semicolon
r_int
id|totalrtbdelta
suffix:semicolon
id|ASSERT
c_func
(paren
id|tp-&gt;t_dqinfo
)paren
suffix:semicolon
id|qa
op_assign
id|tp-&gt;t_dqinfo-&gt;dqa_usrdquots
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|qa
(braket
l_int|0
)braket
dot
id|qt_dquot
op_eq
l_int|NULL
)paren
(brace
id|qa
op_assign
id|tp-&gt;t_dqinfo-&gt;dqa_grpdquots
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Lock all of the dquots and join them to the transaction.&n;&t;&t; */
id|xfs_trans_dqlockedjoin
c_func
(paren
id|tp
comma
id|qa
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFS_QM_TRANS_MAXDQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|qtrx
op_assign
op_amp
id|qa
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The array of dquots is filled&n;&t;&t;&t; * sequentially, not sparsely.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|dqp
op_assign
id|qtrx-&gt;qt_dquot
)paren
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_ADDEDTO_TRX
c_func
(paren
id|tp
comma
id|dqp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * adjust the actual number of blocks used&n;&t;&t;&t; */
id|d
op_assign
op_amp
id|dqp-&gt;q_core
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The issue here is - sometimes we don&squot;t make a blkquota&n;&t;&t;&t; * reservation intentionally to be fair to users&n;&t;&t;&t; * (when the amount is small). On the other hand,&n;&t;&t;&t; * delayed allocs do make reservations, but that&squot;s&n;&t;&t;&t; * outside of a transaction, so we have no&n;&t;&t;&t; * idea how much was really reserved.&n;&t;&t;&t; * So, here we&squot;ve accumulated delayed allocation blks and&n;&t;&t;&t; * non-delay blks. The assumption is that the&n;&t;&t;&t; * delayed ones are always reserved (outside of a&n;&t;&t;&t; * transaction), and the others may or may not have&n;&t;&t;&t; * quota reservations.&n;&t;&t;&t; */
id|totalbdelta
op_assign
id|qtrx-&gt;qt_bcount_delta
op_plus
id|qtrx-&gt;qt_delbcnt_delta
suffix:semicolon
id|totalrtbdelta
op_assign
id|qtrx-&gt;qt_rtbcount_delta
op_plus
id|qtrx-&gt;qt_delrtb_delta
suffix:semicolon
macro_line|#ifdef QUOTADEBUG
r_if
c_cond
(paren
id|totalbdelta
OL
l_int|0
)paren
id|ASSERT
c_func
(paren
id|INT_GET
c_func
(paren
id|d-&gt;d_bcount
comma
id|ARCH_CONVERT
)paren
op_ge
(paren
id|xfs_qcnt_t
)paren
op_minus
id|totalbdelta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|totalrtbdelta
OL
l_int|0
)paren
id|ASSERT
c_func
(paren
id|INT_GET
c_func
(paren
id|d-&gt;d_rtbcount
comma
id|ARCH_CONVERT
)paren
op_ge
(paren
id|xfs_qcnt_t
)paren
op_minus
id|totalrtbdelta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qtrx-&gt;qt_icount_delta
OL
l_int|0
)paren
id|ASSERT
c_func
(paren
id|INT_GET
c_func
(paren
id|d-&gt;d_icount
comma
id|ARCH_CONVERT
)paren
op_ge
(paren
id|xfs_qcnt_t
)paren
op_minus
id|qtrx-&gt;qt_icount_delta
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|totalbdelta
)paren
id|INT_MOD
c_func
(paren
id|d-&gt;d_bcount
comma
id|ARCH_CONVERT
comma
(paren
id|xfs_qcnt_t
)paren
id|totalbdelta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qtrx-&gt;qt_icount_delta
)paren
id|INT_MOD
c_func
(paren
id|d-&gt;d_icount
comma
id|ARCH_CONVERT
comma
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_icount_delta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|totalrtbdelta
)paren
id|INT_MOD
c_func
(paren
id|d-&gt;d_rtbcount
comma
id|ARCH_CONVERT
comma
(paren
id|xfs_qcnt_t
)paren
id|totalrtbdelta
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Start/reset the timer(s) if needed.&n;&t;&t;&t; */
id|xfs_qm_adjust_dqtimers
c_func
(paren
id|tp-&gt;t_mountp
comma
id|d
)paren
suffix:semicolon
id|dqp-&gt;dq_flags
op_or_assign
id|XFS_DQ_DIRTY
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * add this to the list of items to get logged&n;&t;&t;&t; */
id|xfs_trans_log_dquot
c_func
(paren
id|tp
comma
id|dqp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Take off what&squot;s left of the original reservation.&n;&t;&t;&t; * In case of delayed allocations, there&squot;s no&n;&t;&t;&t; * reservation that a transaction structure knows of.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
op_ne
id|qtrx-&gt;qt_blk_res_used
)paren
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
OG
id|qtrx-&gt;qt_blk_res_used
)paren
id|dqp-&gt;q_res_bcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
(paren
id|qtrx-&gt;qt_blk_res
op_minus
id|qtrx-&gt;qt_blk_res_used
)paren
suffix:semicolon
r_else
id|dqp-&gt;q_res_bcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
(paren
id|qtrx-&gt;qt_blk_res_used
op_minus
id|qtrx-&gt;qt_blk_res
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * These blks were never reserved, either inside&n;&t;&t;&t;&t; * a transaction or outside one (in a delayed&n;&t;&t;&t;&t; * allocation). Also, this isn&squot;t always a&n;&t;&t;&t;&t; * negative number since we sometimes&n;&t;&t;&t;&t; * deliberately skip quota reservations.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|qtrx-&gt;qt_bcount_delta
)paren
(brace
id|dqp-&gt;q_res_bcount
op_add_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_bcount_delta
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t; * Adjust the RT reservation.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtblk_res
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
op_ne
id|qtrx-&gt;qt_blk_res_used
)paren
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtblk_res
OG
id|qtrx-&gt;qt_rtblk_res_used
)paren
id|dqp-&gt;q_res_rtbcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
(paren
id|qtrx-&gt;qt_rtblk_res
op_minus
id|qtrx-&gt;qt_rtblk_res_used
)paren
suffix:semicolon
r_else
id|dqp-&gt;q_res_rtbcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
(paren
id|qtrx-&gt;qt_rtblk_res_used
op_minus
id|qtrx-&gt;qt_rtblk_res
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtbcount_delta
)paren
id|dqp-&gt;q_res_rtbcount
op_add_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_rtbcount_delta
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Adjust the inode reservation.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|qtrx-&gt;qt_ino_res
op_ne
l_int|0
)paren
(brace
id|ASSERT
c_func
(paren
id|qtrx-&gt;qt_ino_res
op_ge
id|qtrx-&gt;qt_ino_res_used
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qtrx-&gt;qt_ino_res
OG
id|qtrx-&gt;qt_ino_res_used
)paren
id|dqp-&gt;q_res_icount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
(paren
id|qtrx-&gt;qt_ino_res
op_minus
id|qtrx-&gt;qt_ino_res_used
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_icount_delta
)paren
id|dqp-&gt;q_res_icount
op_add_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_icount_delta
suffix:semicolon
)brace
macro_line|#ifdef QUOTADEBUG
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtblk_res
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;RT res %d for 0x%p&bslash;n&quot;
comma
(paren
r_int
)paren
id|qtrx-&gt;qt_rtblk_res
comma
id|dqp
)paren
suffix:semicolon
macro_line|#endif
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_bcount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_bcount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_icount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_icount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_rtbcount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_rtbcount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Do the group quotas next&n;&t;&t; */
id|qa
op_assign
id|tp-&gt;t_dqinfo-&gt;dqa_grpdquots
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Release the reservations, and adjust the dquots accordingly.&n; * This is called only when the transaction is being aborted. If by&n; * any chance we have done dquot modifications incore (ie. deltas) already,&n; * we simply throw those away, since that&squot;s the expected behavior&n; * when a transaction is curtailed without a commit.&n; */
r_void
DECL|function|xfs_trans_unreserve_and_mod_dquots
id|xfs_trans_unreserve_and_mod_dquots
c_func
(paren
id|xfs_trans_t
op_star
id|tp
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|xfs_dqtrx_t
op_star
id|qtrx
comma
op_star
id|qa
suffix:semicolon
id|boolean_t
id|locked
suffix:semicolon
id|ASSERT
c_func
(paren
id|tp-&gt;t_dqinfo
)paren
suffix:semicolon
id|qa
op_assign
id|tp-&gt;t_dqinfo-&gt;dqa_usrdquots
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|XFS_QM_TRANS_MAXDQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|qtrx
op_assign
op_amp
id|qa
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We assume that the array of dquots is filled&n;&t;&t;&t; * sequentially, not sparsely.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|dqp
op_assign
id|qtrx-&gt;qt_dquot
)paren
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Unreserve the original reservation. We don&squot;t care&n;&t;&t;&t; * about the number of blocks used field, or deltas.&n;&t;&t;&t; * Also we don&squot;t bother to zero the fields.&n;&t;&t;&t; */
id|locked
op_assign
id|B_FALSE
suffix:semicolon
r_if
c_cond
(paren
id|qtrx-&gt;qt_blk_res
)paren
(brace
id|xfs_dqlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|locked
op_assign
id|B_TRUE
suffix:semicolon
id|dqp-&gt;q_res_bcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_blk_res
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_ino_res
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
(brace
id|xfs_dqlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|locked
op_assign
id|B_TRUE
suffix:semicolon
)brace
id|dqp-&gt;q_res_icount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_ino_res
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qtrx-&gt;qt_rtblk_res
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|locked
)paren
(brace
id|xfs_dqlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|locked
op_assign
id|B_TRUE
suffix:semicolon
)brace
id|dqp-&gt;q_res_rtbcount
op_sub_assign
(paren
id|xfs_qcnt_t
)paren
id|qtrx-&gt;qt_rtblk_res
suffix:semicolon
)brace
r_if
c_cond
(paren
id|locked
)paren
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
id|qa
op_assign
id|tp-&gt;t_dqinfo-&gt;dqa_grpdquots
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This reserves disk blocks and inodes against a dquot.&n; * Flags indicate if the dquot is to be locked here and also&n; * if the blk reservation is for RT or regular blocks.&n; * Sending in XFS_QMOPT_FORCE_RES flag skips the quota check.&n; * Returns EDQUOT if quota is exceeded.&n; */
id|STATIC
r_int
DECL|function|xfs_trans_dqresv
id|xfs_trans_dqresv
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|dqp
comma
r_int
id|nblks
comma
r_int
id|ninos
comma
id|uint
id|flags
)paren
(brace
r_int
id|error
suffix:semicolon
id|xfs_qcnt_t
id|hardlimit
suffix:semicolon
id|xfs_qcnt_t
id|softlimit
suffix:semicolon
id|time_t
id|btimer
suffix:semicolon
id|xfs_qcnt_t
op_star
id|resbcountp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_QMOPT_DQLOCK
)paren
)paren
(brace
id|xfs_dqlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|XFS_TRANS_DQ_RES_BLKS
)paren
(brace
id|hardlimit
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_blk_hardlimit
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|softlimit
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_blk_softlimit
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|btimer
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_btimer
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|resbcountp
op_assign
op_amp
id|dqp-&gt;q_res_bcount
suffix:semicolon
)brace
r_else
(brace
id|ASSERT
c_func
(paren
id|flags
op_amp
id|XFS_TRANS_DQ_RES_RTBLKS
)paren
suffix:semicolon
id|hardlimit
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_rtb_hardlimit
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|softlimit
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_rtb_softlimit
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|btimer
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_rtbtimer
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|resbcountp
op_assign
op_amp
id|dqp-&gt;q_res_rtbcount
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|XFS_QMOPT_FORCE_RES
)paren
op_eq
l_int|0
op_logical_and
op_logical_neg
id|INT_ISZERO
c_func
(paren
id|dqp-&gt;q_core.d_id
comma
id|ARCH_CONVERT
)paren
op_logical_and
id|XFS_IS_QUOTA_ENFORCED
c_func
(paren
id|dqp-&gt;q_mount
)paren
)paren
(brace
macro_line|#ifdef QUOTADEBUG
id|printk
c_func
(paren
l_string|&quot;BLK Res: nblks=%ld + resbcount=%Ld &gt; hardlimit=%Ld?&bslash;n&quot;
comma
id|nblks
comma
op_star
id|resbcountp
comma
id|hardlimit
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|nblks
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * dquot is locked already. See if we&squot;d go over the&n;&t;&t;&t; * hardlimit or exceed the timelimit if we allocate&n;&t;&t;&t; * nblks.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|hardlimit
OG
l_int|0ULL
op_logical_and
(paren
id|hardlimit
op_le
id|nblks
op_plus
op_star
id|resbcountp
)paren
)paren
(brace
id|error
op_assign
id|EDQUOT
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|softlimit
OG
l_int|0ULL
op_logical_and
(paren
id|softlimit
op_le
id|nblks
op_plus
op_star
id|resbcountp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * If timer or warnings has expired,&n;&t;&t;&t;&t; * return EDQUOT&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|btimer
op_ne
l_int|0
op_logical_and
id|CURRENT_TIME
OG
id|btimer
)paren
op_logical_or
(paren
op_logical_neg
id|INT_ISZERO
c_func
(paren
id|dqp-&gt;q_core.d_bwarns
comma
id|ARCH_CONVERT
)paren
op_logical_and
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_bwarns
comma
id|ARCH_CONVERT
)paren
op_ge
id|XFS_QI_BWARNLIMIT
c_func
(paren
id|dqp-&gt;q_mount
)paren
)paren
)paren
(brace
id|error
op_assign
id|EDQUOT
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|ninos
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_ino_hardlimit
comma
id|ARCH_CONVERT
)paren
OG
l_int|0ULL
op_logical_and
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_icount
comma
id|ARCH_CONVERT
)paren
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_ino_hardlimit
comma
id|ARCH_CONVERT
)paren
)paren
(brace
id|error
op_assign
id|EDQUOT
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_ino_softlimit
comma
id|ARCH_CONVERT
)paren
OG
l_int|0ULL
op_logical_and
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_icount
comma
id|ARCH_CONVERT
)paren
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_ino_softlimit
comma
id|ARCH_CONVERT
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * If timer or warnings has expired,&n;&t;&t;&t;&t; * return EDQUOT&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|INT_ISZERO
c_func
(paren
id|dqp-&gt;q_core.d_itimer
comma
id|ARCH_CONVERT
)paren
op_logical_and
id|CURRENT_TIME
OG
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_itimer
comma
id|ARCH_CONVERT
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|INT_ISZERO
c_func
(paren
id|dqp-&gt;q_core.d_iwarns
comma
id|ARCH_CONVERT
)paren
op_logical_and
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_iwarns
comma
id|ARCH_CONVERT
)paren
op_ge
id|XFS_QI_IWARNLIMIT
c_func
(paren
id|dqp-&gt;q_mount
)paren
)paren
)paren
(brace
id|error
op_assign
id|EDQUOT
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Change the reservation, but not the actual usage.&n;&t; * Note that q_res_bcount = q_core.d_bcount + resv&n;&t; */
(paren
op_star
id|resbcountp
)paren
op_add_assign
(paren
id|xfs_qcnt_t
)paren
id|nblks
suffix:semicolon
r_if
c_cond
(paren
id|ninos
op_ne
l_int|0
)paren
id|dqp-&gt;q_res_icount
op_add_assign
(paren
id|xfs_qcnt_t
)paren
id|ninos
suffix:semicolon
multiline_comment|/*&n;&t; * note the reservation amt in the trans struct too,&n;&t; * so that the transaction knows how much was reserved by&n;&t; * it against this particular dquot.&n;&t; * We don&squot;t do this when we are reserving for a delayed allocation,&n;&t; * because we don&squot;t have the luxury of a transaction envelope then.&n;&t; */
r_if
c_cond
(paren
id|tp
)paren
(brace
id|ASSERT
c_func
(paren
id|tp-&gt;t_dqinfo
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|flags
op_amp
id|XFS_QMOPT_RESBLK_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nblks
op_ne
l_int|0
)paren
id|xfs_trans_mod_dquot
c_func
(paren
id|tp
comma
id|dqp
comma
id|flags
op_amp
id|XFS_QMOPT_RESBLK_MASK
comma
id|nblks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ninos
op_ne
l_int|0
)paren
id|xfs_trans_mod_dquot
c_func
(paren
id|tp
comma
id|dqp
comma
id|XFS_TRANS_DQ_RES_INOS
comma
id|ninos
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_bcount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_bcount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_rtbcount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_rtbcount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dqp-&gt;q_res_icount
op_ge
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_icount
comma
id|ARCH_CONVERT
)paren
)paren
suffix:semicolon
id|error_return
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|XFS_QMOPT_DQLOCK
)paren
)paren
(brace
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a dquot(s), make disk block and/or inode reservations against them.&n; * The fact that this does the reservation against both the usr and&n; * grp quotas is important, because this follows a both-or-nothing&n; * approach.&n; *&n; * flags = XFS_QMOPT_DQLOCK indicate if dquot(s) need to be locked.&n; *&t;   XFS_QMOPT_FORCE_RES evades limit enforcement. Used by chown.&n; *&t;   XFS_TRANS_DQ_RES_BLKS reserves regular disk blocks&n; *&t;   XFS_TRANS_DQ_RES_RTBLKS reserves realtime disk blocks&n; * dquots are unlocked on return, if they were not locked by caller.&n; */
r_int
DECL|function|xfs_trans_reserve_quota_bydquots
id|xfs_trans_reserve_quota_bydquots
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_dquot_t
op_star
id|udqp
comma
id|xfs_dquot_t
op_star
id|gdqp
comma
r_int
id|nblks
comma
r_int
id|ninos
comma
id|uint
id|flags
)paren
(brace
r_int
id|resvd
suffix:semicolon
r_if
c_cond
(paren
id|tp
op_logical_and
id|tp-&gt;t_dqinfo
op_eq
l_int|NULL
)paren
id|xfs_trans_alloc_dqinfo
c_func
(paren
id|tp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|flags
op_amp
id|XFS_QMOPT_RESBLK_MASK
)paren
suffix:semicolon
id|resvd
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|udqp
)paren
(brace
r_if
c_cond
(paren
id|xfs_trans_dqresv
c_func
(paren
id|tp
comma
id|udqp
comma
id|nblks
comma
id|ninos
comma
id|flags
)paren
)paren
r_return
(paren
id|EDQUOT
)paren
suffix:semicolon
id|resvd
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gdqp
)paren
(brace
r_if
c_cond
(paren
id|xfs_trans_dqresv
c_func
(paren
id|tp
comma
id|gdqp
comma
id|nblks
comma
id|ninos
comma
id|flags
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * can&squot;t do it, so backout previous reservation&n;&t;&t;&t; */
r_if
c_cond
(paren
id|resvd
)paren
(brace
id|xfs_trans_dqresv
c_func
(paren
id|tp
comma
id|udqp
comma
op_minus
id|nblks
comma
op_minus
id|ninos
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
(paren
id|EDQUOT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Didnt change anything critical, so, no need to log&n;&t; */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lock the dquot and change the reservation if we can.&n; * This doesnt change the actual usage, just the reservation.&n; * The inode sent in is locked.&n; *&n; * Returns 0 on success, EDQUOT or other errors otherwise&n; */
r_int
DECL|function|xfs_trans_reserve_quota_nblks
id|xfs_trans_reserve_quota_nblks
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|nblks
comma
r_int
id|ninos
comma
id|uint
id|type
)paren
(brace
r_int
id|error
suffix:semicolon
macro_line|#ifdef QUOTADEBUG
r_if
c_cond
(paren
id|ip-&gt;i_udquot
)paren
id|ASSERT
c_func
(paren
op_logical_neg
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|ip-&gt;i_udquot
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_gdquot
)paren
id|ASSERT
c_func
(paren
op_logical_neg
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|ip-&gt;i_gdquot
)paren
)paren
suffix:semicolon
macro_line|#endif
id|ASSERT
c_func
(paren
id|XFS_ISLOCKED_INODE_EXCL
c_func
(paren
id|ip
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_IS_QUOTA_RUNNING
c_func
(paren
id|ip-&gt;i_mount
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|type
op_amp
op_complement
id|XFS_QMOPT_FORCE_RES
)paren
op_eq
id|XFS_TRANS_DQ_RES_RTBLKS
op_logical_or
(paren
id|type
op_amp
op_complement
id|XFS_QMOPT_FORCE_RES
)paren
op_eq
id|XFS_TRANS_DQ_RES_BLKS
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve nblks against these dquots, with trans as the mediator.&n;&t; */
id|error
op_assign
id|xfs_trans_reserve_quota_bydquots
c_func
(paren
id|tp
comma
id|ip-&gt;i_udquot
comma
id|ip-&gt;i_gdquot
comma
id|nblks
comma
id|ninos
comma
id|type
)paren
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called to allocate a quotaoff log item.&n; */
id|xfs_qoff_logitem_t
op_star
DECL|function|xfs_trans_get_qoff_item
id|xfs_trans_get_qoff_item
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_qoff_logitem_t
op_star
id|startqoff
comma
id|uint
id|flags
)paren
(brace
id|xfs_qoff_logitem_t
op_star
id|q
suffix:semicolon
id|ASSERT
c_func
(paren
id|tp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|q
op_assign
id|xfs_qm_qoff_logitem_init
c_func
(paren
id|tp-&gt;t_mountp
comma
id|startqoff
comma
id|flags
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|q
op_ne
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get a log_item_desc to point at the new item.&n;&t; */
(paren
r_void
)paren
id|xfs_trans_add_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|q
)paren
suffix:semicolon
r_return
(paren
id|q
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to mark the quotaoff logitem as needing&n; * to be logged when the transaction is committed.  The logitem must&n; * already be associated with the given transaction.&n; */
r_void
DECL|function|xfs_trans_log_quotaoff_item
id|xfs_trans_log_quotaoff_item
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_qoff_logitem_t
op_star
id|qlp
)paren
(brace
id|xfs_log_item_desc_t
op_star
id|lidp
suffix:semicolon
id|lidp
op_assign
id|xfs_trans_find_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|qlp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lidp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|tp-&gt;t_flags
op_or_assign
id|XFS_TRANS_DIRTY
suffix:semicolon
id|lidp-&gt;lid_flags
op_or_assign
id|XFS_LID_DIRTY
suffix:semicolon
)brace
r_void
DECL|function|xfs_trans_alloc_dqinfo
id|xfs_trans_alloc_dqinfo
c_func
(paren
id|xfs_trans_t
op_star
id|tp
)paren
(brace
(paren
id|tp
)paren
op_member_access_from_pointer
id|t_dqinfo
op_assign
id|kmem_zone_zalloc
c_func
(paren
id|xfs_Gqm-&gt;qm_dqtrxzone
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
r_void
DECL|function|xfs_trans_free_dqinfo
id|xfs_trans_free_dqinfo
c_func
(paren
id|xfs_trans_t
op_star
id|tp
)paren
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_Gqm-&gt;qm_dqtrxzone
comma
(paren
id|tp
)paren
op_member_access_from_pointer
id|t_dqinfo
)paren
suffix:semicolon
(paren
id|tp
)paren
op_member_access_from_pointer
id|t_dqinfo
op_assign
l_int|NULL
suffix:semicolon
)brace
eof