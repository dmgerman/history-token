multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_trans_priv.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
id|STATIC
r_void
id|xfs_ail_insert
c_func
(paren
id|xfs_ail_entry_t
op_star
comma
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
id|STATIC
id|xfs_log_item_t
op_star
id|xfs_ail_delete
c_func
(paren
id|xfs_ail_entry_t
op_star
comma
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
id|STATIC
id|xfs_log_item_t
op_star
id|xfs_ail_min
c_func
(paren
id|xfs_ail_entry_t
op_star
)paren
suffix:semicolon
id|STATIC
id|xfs_log_item_t
op_star
id|xfs_ail_next
c_func
(paren
id|xfs_ail_entry_t
op_star
comma
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|STATIC
r_void
id|xfs_ail_check
c_func
(paren
id|xfs_ail_entry_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_ail_check
mdefine_line|#define&t;xfs_ail_check(a)
macro_line|#endif /* DEBUG */
multiline_comment|/*&n; * This is called by the log manager code to determine the LSN&n; * of the tail of the log.  This is exactly the LSN of the first&n; * item in the AIL.  If the AIL is empty, then this function&n; * returns 0.&n; *&n; * We need the AIL lock in order to get a coherent read of the&n; * lsn of the last item in the AIL.&n; */
id|xfs_lsn_t
DECL|function|xfs_trans_tail_ail
id|xfs_trans_tail_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|xfs_lsn_t
id|lsn
suffix:semicolon
id|xfs_log_item_t
op_star
id|lip
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|lip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lip
op_eq
l_int|NULL
)paren
(brace
id|lsn
op_assign
(paren
id|xfs_lsn_t
)paren
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|lsn
op_assign
id|lip-&gt;li_lsn
suffix:semicolon
)brace
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
id|lsn
suffix:semicolon
)brace
multiline_comment|/*&n; * xfs_trans_push_ail&n; *&n; * This routine is called to move the tail of the AIL&n; * forward.  It does this by trying to flush items in the AIL&n; * whose lsns are below the given threshold_lsn.&n; *&n; * The routine returns the lsn of the tail of the log.&n; */
id|xfs_lsn_t
DECL|function|xfs_trans_push_ail
id|xfs_trans_push_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_lsn_t
id|threshold_lsn
)paren
(brace
id|xfs_lsn_t
id|lsn
suffix:semicolon
id|xfs_log_item_t
op_star
id|lip
suffix:semicolon
r_int
id|gen
suffix:semicolon
r_int
id|restarts
suffix:semicolon
r_int
id|lock_result
suffix:semicolon
r_int
id|flush_log
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
DECL|macro|XFS_TRANS_PUSH_AIL_RESTARTS
mdefine_line|#define&t;XFS_TRANS_PUSH_AIL_RESTARTS&t;10
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|lip
op_assign
id|xfs_trans_first_ail
c_func
(paren
id|mp
comma
op_amp
id|gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lip
op_eq
l_int|NULL
op_logical_or
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Just return if the AIL is empty.&n;&t;&t; */
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
(paren
id|xfs_lsn_t
)paren
l_int|0
suffix:semicolon
)brace
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * While the item we are looking at is below the given threshold&n;&t; * try to flush it out.  Make sure to limit the number of times&n;&t; * we allow xfs_trans_next_ail() to restart scanning from the&n;&t; * beginning of the list.  We&squot;d like not to stop until we&squot;ve at least&n;&t; * tried to push on everything in the AIL with an LSN less than&n;&t; * the given threshold. However, we may give up before that if&n;&t; * we realize that we&squot;ve been holding the AIL_LOCK for &squot;too long&squot;,&n;&t; * blocking interrupts. Currently, too long is &lt; 500us roughly.&n;&t; */
id|flush_log
op_assign
l_int|0
suffix:semicolon
id|restarts
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|restarts
OL
id|XFS_TRANS_PUSH_AIL_RESTARTS
)paren
op_logical_and
(paren
id|XFS_LSN_CMP
c_func
(paren
id|lip-&gt;li_lsn
comma
id|threshold_lsn
)paren
OL
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we can lock the item without sleeping, unlock&n;&t;&t; * the AIL lock and flush the item.  Then re-grab the&n;&t;&t; * AIL lock so we can look for the next item on the&n;&t;&t; * AIL.  Since we unlock the AIL while we flush the&n;&t;&t; * item, the next routine may start over again at the&n;&t;&t; * the beginning of the list if anything has changed.&n;&t;&t; * That is what the generation count is for.&n;&t;&t; *&n;&t;&t; * If we can&squot;t lock the item, either its holder will flush&n;&t;&t; * it or it is already being flushed or it is being relogged.&n;&t;&t; * In any of these case it is being taken care of and we&n;&t;&t; * can just skip to the next item in the list.&n;&t;&t; */
id|lock_result
op_assign
id|IOP_TRYLOCK
c_func
(paren
id|lip
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|lock_result
)paren
(brace
r_case
id|XFS_ITEM_SUCCESS
suffix:colon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_success
)paren
suffix:semicolon
id|IOP_PUSH
c_func
(paren
id|lip
)paren
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_ITEM_PUSHBUF
suffix:colon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_pushbuf
)paren
suffix:semicolon
macro_line|#ifdef XFSRACEDEBUG
id|delay_for_intr
c_func
(paren
)paren
suffix:semicolon
id|delay
c_func
(paren
l_int|300
)paren
suffix:semicolon
macro_line|#endif
id|ASSERT
c_func
(paren
id|lip-&gt;li_ops-&gt;iop_pushbuf
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lip
)paren
suffix:semicolon
id|IOP_PUSHBUF
c_func
(paren
id|lip
)paren
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_ITEM_PINNED
suffix:colon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_pinned
)paren
suffix:semicolon
id|flush_log
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_ITEM_LOCKED
suffix:colon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_locked
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFS_ITEM_FLUSHING
suffix:colon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_flushing
)paren
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
r_break
suffix:semicolon
)brace
id|lip
op_assign
id|xfs_trans_next_ail
c_func
(paren
id|mp
comma
id|lip
comma
op_amp
id|gen
comma
op_amp
id|restarts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lip
op_eq
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Just return if we shut down during the last try.&n;&t;&t;&t; */
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
(paren
id|xfs_lsn_t
)paren
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|flush_log
)paren
(brace
multiline_comment|/*&n;&t;&t; * If something we need to push out was pinned, then&n;&t;&t; * push out the log so it will become unpinned and&n;&t;&t; * move forward in the AIL.&n;&t;&t; */
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_flush
)paren
suffix:semicolon
id|xfs_log_force
c_func
(paren
id|mp
comma
(paren
id|xfs_lsn_t
)paren
l_int|0
comma
id|XFS_LOG_FORCE
)paren
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
id|lip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lip
op_eq
l_int|NULL
)paren
(brace
id|lsn
op_assign
(paren
id|xfs_lsn_t
)paren
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|lsn
op_assign
id|lip-&gt;li_lsn
suffix:semicolon
)brace
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_return
id|lsn
suffix:semicolon
)brace
multiline_comment|/* xfs_trans_push_ail */
multiline_comment|/*&n; * This is to be called when an item is unlocked that may have&n; * been in the AIL.  It will wake up the first member of the AIL&n; * wait list if this item&squot;s unlocking might allow it to progress.&n; * If the item is in the AIL, then we need to get the AIL lock&n; * while doing our checking so we don&squot;t race with someone going&n; * to sleep waiting for this event in xfs_trans_push_ail().&n; */
r_void
DECL|function|xfs_trans_unlocked_item
id|xfs_trans_unlocked_item
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_log_item_t
op_star
id|lip
)paren
(brace
id|xfs_log_item_t
op_star
id|min_lip
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re forcibly shutting down, we may have&n;&t; * unlocked log items arbitrarily. The last thing&n;&t; * we want to do is to move the tail of the log&n;&t; * over some potentially valid data.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|lip-&gt;li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
op_logical_or
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is the one case where we can call into xfs_ail_min()&n;&t; * without holding the AIL lock because we only care about the&n;&t; * case where we are at the tail of the AIL.  If the object isn&squot;t&n;&t; * at the tail, it doesn&squot;t matter what result we get back.  This&n;&t; * is slightly racy because since we were just unlocked, we could&n;&t; * go to sleep between the call to xfs_ail_min and the call to&n;&t; * xfs_log_move_tail, have someone else lock us, commit to us disk,&n;&t; * move us out of the tail of the AIL, and then we wake up.  However,&n;&t; * the call to xfs_log_move_tail() doesn&squot;t do anything if there&squot;s&n;&t; * not enough free space to wake people up so we&squot;re safe calling it.&n;&t; */
id|min_lip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
id|mp-&gt;m_ail
)paren
suffix:semicolon
r_if
c_cond
(paren
id|min_lip
op_eq
id|lip
)paren
id|xfs_log_move_tail
c_func
(paren
id|mp
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* xfs_trans_unlocked_item */
multiline_comment|/*&n; * Update the position of the item in the AIL with the new&n; * lsn.  If it is not yet in the AIL, add it.  Otherwise, move&n; * it to its new position by removing it and re-adding it.&n; *&n; * Wakeup anyone with an lsn less than the item&squot;s lsn.  If the item&n; * we move in the AIL is the minimum one, update the tail lsn in the&n; * log manager.&n; *&n; * Increment the AIL&squot;s generation count to indicate that the tree&n; * has changed.&n; *&n; * This function must be called with the AIL lock held.  The lock&n; * is dropped before returning, so the caller must pass in the&n; * cookie returned by AIL_LOCK.&n; */
r_void
DECL|function|xfs_trans_update_ail
id|xfs_trans_update_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_log_item_t
op_star
id|lip
comma
id|xfs_lsn_t
id|lsn
comma
r_int
r_int
id|s
)paren
(brace
id|xfs_ail_entry_t
op_star
id|ailp
suffix:semicolon
id|xfs_log_item_t
op_star
id|dlip
op_assign
l_int|NULL
suffix:semicolon
id|xfs_log_item_t
op_star
id|mlip
suffix:semicolon
multiline_comment|/* ptr to minimum lip */
id|ailp
op_assign
op_amp
(paren
id|mp-&gt;m_ail
)paren
suffix:semicolon
id|mlip
op_assign
id|xfs_ail_min
c_func
(paren
id|ailp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lip-&gt;li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
(brace
id|dlip
op_assign
id|xfs_ail_delete
c_func
(paren
id|ailp
comma
id|lip
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dlip
op_eq
id|lip
)paren
suffix:semicolon
)brace
r_else
(brace
id|lip-&gt;li_flags
op_or_assign
id|XFS_LI_IN_AIL
suffix:semicolon
)brace
id|lip-&gt;li_lsn
op_assign
id|lsn
suffix:semicolon
id|xfs_ail_insert
c_func
(paren
id|ailp
comma
id|lip
)paren
suffix:semicolon
id|mp-&gt;m_ail_gen
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|mlip
op_eq
id|dlip
)paren
(brace
id|mlip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|xfs_log_move_tail
c_func
(paren
id|mp
comma
id|mlip-&gt;li_lsn
)paren
suffix:semicolon
)brace
r_else
(brace
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* xfs_trans_update_ail */
multiline_comment|/*&n; * Delete the given item from the AIL.  It must already be in&n; * the AIL.&n; *&n; * Wakeup anyone with an lsn less than item&squot;s lsn.    If the item&n; * we delete in the AIL is the minimum one, update the tail lsn in the&n; * log manager.&n; *&n; * Clear the IN_AIL flag from the item, reset its lsn to 0, and&n; * bump the AIL&squot;s generation count to indicate that the tree&n; * has changed.&n; *&n; * This function must be called with the AIL lock held.  The lock&n; * is dropped before returning, so the caller must pass in the&n; * cookie returned by AIL_LOCK.&n; */
r_void
DECL|function|xfs_trans_delete_ail
id|xfs_trans_delete_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_log_item_t
op_star
id|lip
comma
r_int
r_int
id|s
)paren
(brace
id|xfs_ail_entry_t
op_star
id|ailp
suffix:semicolon
id|xfs_log_item_t
op_star
id|dlip
suffix:semicolon
id|xfs_log_item_t
op_star
id|mlip
suffix:semicolon
r_if
c_cond
(paren
id|lip-&gt;li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
(brace
id|ailp
op_assign
op_amp
(paren
id|mp-&gt;m_ail
)paren
suffix:semicolon
id|mlip
op_assign
id|xfs_ail_min
c_func
(paren
id|ailp
)paren
suffix:semicolon
id|dlip
op_assign
id|xfs_ail_delete
c_func
(paren
id|ailp
comma
id|lip
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dlip
op_eq
id|lip
)paren
suffix:semicolon
id|lip-&gt;li_flags
op_and_assign
op_complement
id|XFS_LI_IN_AIL
suffix:semicolon
id|lip-&gt;li_lsn
op_assign
l_int|0
suffix:semicolon
id|mp-&gt;m_ail_gen
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|mlip
op_eq
id|dlip
)paren
(brace
id|mlip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|xfs_log_move_tail
c_func
(paren
id|mp
comma
(paren
id|mlip
ques
c_cond
id|mlip-&gt;li_lsn
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * If the file system is not being shutdown, we are in&n;&t;&t; * serious trouble if we get to this stage.&n;&t;&t; */
r_if
c_cond
(paren
id|XFS_FORCED_SHUTDOWN
c_func
(paren
id|mp
)paren
)paren
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_else
(brace
id|xfs_cmn_err
c_func
(paren
id|XFS_PTAG_AILDELETE
comma
id|CE_ALERT
comma
id|mp
comma
l_string|&quot;xfs_trans_delete_ail: attempting to delete a log item that is not in the AIL&quot;
)paren
suffix:semicolon
id|xfs_force_shutdown
c_func
(paren
id|mp
comma
id|XFS_CORRUPT_INCORE
)paren
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Return the item in the AIL with the smallest lsn.&n; * Return the current tree generation number for use&n; * in calls to xfs_trans_next_ail().&n; */
id|xfs_log_item_t
op_star
DECL|function|xfs_trans_first_ail
id|xfs_trans_first_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
r_int
op_star
id|gen
)paren
(brace
id|xfs_log_item_t
op_star
id|lip
suffix:semicolon
id|lip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
op_star
id|gen
op_assign
(paren
r_int
)paren
id|mp-&gt;m_ail_gen
suffix:semicolon
r_return
(paren
id|lip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If the generation count of the tree has not changed since the&n; * caller last took something from the AIL, then return the elmt&n; * in the tree which follows the one given.  If the count has changed,&n; * then return the minimum elmt of the AIL and bump the restarts counter&n; * if one is given.&n; */
id|xfs_log_item_t
op_star
DECL|function|xfs_trans_next_ail
id|xfs_trans_next_ail
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_log_item_t
op_star
id|lip
comma
r_int
op_star
id|gen
comma
r_int
op_star
id|restarts
)paren
(brace
id|xfs_log_item_t
op_star
id|nlip
suffix:semicolon
id|ASSERT
c_func
(paren
id|mp
op_logical_and
id|lip
op_logical_and
id|gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;m_ail_gen
op_eq
op_star
id|gen
)paren
(brace
id|nlip
op_assign
id|xfs_ail_next
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
comma
id|lip
)paren
suffix:semicolon
)brace
r_else
(brace
id|nlip
op_assign
id|xfs_ail_min
c_func
(paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
)paren
suffix:semicolon
op_star
id|gen
op_assign
(paren
r_int
)paren
id|mp-&gt;m_ail_gen
suffix:semicolon
r_if
c_cond
(paren
id|restarts
op_ne
l_int|NULL
)paren
(brace
id|XFS_STATS_INC
c_func
(paren
id|xs_push_ail_restarts
)paren
suffix:semicolon
(paren
op_star
id|restarts
)paren
op_increment
suffix:semicolon
)brace
)brace
r_return
(paren
id|nlip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The active item list (AIL) is a doubly linked list of log&n; * items sorted by ascending lsn.  The base of the list is&n; * a forw/back pointer pair embedded in the xfs mount structure.&n; * The base is initialized with both pointers pointing to the&n; * base.  This case always needs to be distinguished, because&n; * the base has no lsn to look at.  We almost always insert&n; * at the end of the list, so on inserts we search from the&n; * end of the list to find where the new item belongs.&n; */
multiline_comment|/*&n; * Initialize the doubly linked list to point only to itself.&n; */
r_void
DECL|function|xfs_trans_ail_init
id|xfs_trans_ail_init
c_func
(paren
id|xfs_mount_t
op_star
id|mp
)paren
(brace
id|mp-&gt;m_ail.ail_forw
op_assign
(paren
id|xfs_log_item_t
op_star
)paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
suffix:semicolon
id|mp-&gt;m_ail.ail_back
op_assign
(paren
id|xfs_log_item_t
op_star
)paren
op_amp
(paren
id|mp-&gt;m_ail
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert the given log item into the AIL.&n; * We almost always insert at the end of the list, so on inserts&n; * we search from the end of the list to find where the&n; * new item belongs.&n; */
id|STATIC
r_void
DECL|function|xfs_ail_insert
id|xfs_ail_insert
c_func
(paren
id|xfs_ail_entry_t
op_star
id|base
comma
id|xfs_log_item_t
op_star
id|lip
)paren
multiline_comment|/* ARGSUSED */
(brace
id|xfs_log_item_t
op_star
id|next_lip
suffix:semicolon
multiline_comment|/*&n;&t; * If the list is empty, just insert the item.&n;&t; */
r_if
c_cond
(paren
id|base-&gt;ail_back
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
id|base-&gt;ail_forw
op_assign
id|lip
suffix:semicolon
id|base-&gt;ail_back
op_assign
id|lip
suffix:semicolon
id|lip-&gt;li_ail.ail_forw
op_assign
(paren
id|xfs_log_item_t
op_star
)paren
id|base
suffix:semicolon
id|lip-&gt;li_ail.ail_back
op_assign
(paren
id|xfs_log_item_t
op_star
)paren
id|base
suffix:semicolon
r_return
suffix:semicolon
)brace
id|next_lip
op_assign
id|base-&gt;ail_back
suffix:semicolon
r_while
c_loop
(paren
(paren
id|next_lip
op_ne
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
op_logical_and
(paren
id|XFS_LSN_CMP
c_func
(paren
id|next_lip-&gt;li_lsn
comma
id|lip-&gt;li_lsn
)paren
OG
l_int|0
)paren
)paren
(brace
id|next_lip
op_assign
id|next_lip-&gt;li_ail.ail_back
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
(paren
id|next_lip
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
op_logical_or
(paren
id|XFS_LSN_CMP
c_func
(paren
id|next_lip-&gt;li_lsn
comma
id|lip-&gt;li_lsn
)paren
op_le
l_int|0
)paren
)paren
suffix:semicolon
id|lip-&gt;li_ail.ail_forw
op_assign
id|next_lip-&gt;li_ail.ail_forw
suffix:semicolon
id|lip-&gt;li_ail.ail_back
op_assign
id|next_lip
suffix:semicolon
id|next_lip-&gt;li_ail.ail_forw
op_assign
id|lip
suffix:semicolon
id|lip-&gt;li_ail.ail_forw-&gt;li_ail.ail_back
op_assign
id|lip
suffix:semicolon
id|xfs_ail_check
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete the given item from the AIL.  Return a pointer to the item.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_log_item_t
op_star
DECL|function|xfs_ail_delete
id|xfs_ail_delete
c_func
(paren
id|xfs_ail_entry_t
op_star
id|base
comma
id|xfs_log_item_t
op_star
id|lip
)paren
multiline_comment|/* ARGSUSED */
(brace
id|lip-&gt;li_ail.ail_forw-&gt;li_ail.ail_back
op_assign
id|lip-&gt;li_ail.ail_back
suffix:semicolon
id|lip-&gt;li_ail.ail_back-&gt;li_ail.ail_forw
op_assign
id|lip-&gt;li_ail.ail_forw
suffix:semicolon
id|lip-&gt;li_ail.ail_forw
op_assign
l_int|NULL
suffix:semicolon
id|lip-&gt;li_ail.ail_back
op_assign
l_int|NULL
suffix:semicolon
id|xfs_ail_check
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|lip
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a pointer to the first item in the AIL.&n; * If the AIL is empty, then return NULL.&n; */
id|STATIC
id|xfs_log_item_t
op_star
DECL|function|xfs_ail_min
id|xfs_ail_min
c_func
(paren
id|xfs_ail_entry_t
op_star
id|base
)paren
multiline_comment|/* ARGSUSED */
(brace
r_register
id|xfs_log_item_t
op_star
id|forw
op_assign
id|base-&gt;ail_forw
suffix:semicolon
r_if
c_cond
(paren
id|forw
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|forw
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a pointer to the item which follows&n; * the given item in the AIL.  If the given item&n; * is the last item in the list, then return NULL.&n; */
id|STATIC
id|xfs_log_item_t
op_star
DECL|function|xfs_ail_next
id|xfs_ail_next
c_func
(paren
id|xfs_ail_entry_t
op_star
id|base
comma
id|xfs_log_item_t
op_star
id|lip
)paren
multiline_comment|/* ARGSUSED */
(brace
r_if
c_cond
(paren
id|lip-&gt;li_ail.ail_forw
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|lip-&gt;li_ail.ail_forw
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
multiline_comment|/*&n; * Check that the list is sorted as it should be.&n; */
id|STATIC
r_void
DECL|function|xfs_ail_check
id|xfs_ail_check
c_func
(paren
id|xfs_ail_entry_t
op_star
id|base
)paren
(brace
id|xfs_log_item_t
op_star
id|lip
suffix:semicolon
id|xfs_log_item_t
op_star
id|prev_lip
suffix:semicolon
id|lip
op_assign
id|base-&gt;ail_forw
suffix:semicolon
r_if
c_cond
(paren
id|lip
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
multiline_comment|/*&n;&t;&t; * Make sure the pointers are correct when the list&n;&t;&t; * is empty.&n;&t;&t; */
id|ASSERT
c_func
(paren
id|base-&gt;ail_back
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Walk the list checking forward and backward pointers,&n;&t; * lsn ordering, and that every entry has the XFS_LI_IN_AIL&n;&t; * flag set.&n;&t; */
id|prev_lip
op_assign
(paren
id|xfs_log_item_t
op_star
)paren
id|base
suffix:semicolon
r_while
c_loop
(paren
id|lip
op_ne
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
r_if
c_cond
(paren
id|prev_lip
op_ne
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
(brace
id|ASSERT
c_func
(paren
id|prev_lip-&gt;li_ail.ail_forw
op_eq
id|lip
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_LSN_CMP
c_func
(paren
id|prev_lip-&gt;li_lsn
comma
id|lip-&gt;li_lsn
)paren
op_le
l_int|0
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|lip-&gt;li_ail.ail_back
op_eq
id|prev_lip
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|lip-&gt;li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|prev_lip
op_assign
id|lip
suffix:semicolon
id|lip
op_assign
id|lip-&gt;li_ail.ail_forw
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|lip
op_eq
(paren
id|xfs_log_item_t
op_star
)paren
id|base
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|base-&gt;ail_back
op_eq
id|prev_lip
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG */
eof
