multiline_comment|/*&n; * linux/fs/checkpoint.c&n; * &n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;, 1999&n; *&n; * Copyright 1999 Red Hat Software --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Checkpoint routines for the generic filesystem journaling code.  &n; * Part of the ext2fs journaling system.  &n; *&n; * Checkpointing is the process of ensuring that a section of the log is&n; * committed fully to disk, so that that portion of the log can be&n; * reused.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
r_extern
id|spinlock_t
id|journal_datalist_lock
suffix:semicolon
multiline_comment|/*&n; * Unlink a buffer from a transaction. &n; *&n; * Called with journal_datalist_lock held.&n; */
DECL|function|__buffer_unlink
r_static
r_inline
r_void
id|__buffer_unlink
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
id|transaction_t
op_star
id|transaction
suffix:semicolon
id|transaction
op_assign
id|jh-&gt;b_cp_transaction
suffix:semicolon
id|jh-&gt;b_cp_transaction
op_assign
l_int|NULL
suffix:semicolon
id|jh-&gt;b_cpnext-&gt;b_cpprev
op_assign
id|jh-&gt;b_cpprev
suffix:semicolon
id|jh-&gt;b_cpprev-&gt;b_cpnext
op_assign
id|jh-&gt;b_cpnext
suffix:semicolon
r_if
c_cond
(paren
id|transaction-&gt;t_checkpoint_list
op_eq
id|jh
)paren
id|transaction-&gt;t_checkpoint_list
op_assign
id|jh-&gt;b_cpnext
suffix:semicolon
r_if
c_cond
(paren
id|transaction-&gt;t_checkpoint_list
op_eq
id|jh
)paren
id|transaction-&gt;t_checkpoint_list
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to release a checkpointed buffer from its transaction.&n; * Returns 1 if we released it.&n; * Requires journal_datalist_lock&n; */
DECL|function|__try_to_free_cp_buf
r_static
r_int
id|__try_to_free_cp_buf
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|jh2bh
c_func
(paren
id|jh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jh-&gt;b_jlist
op_eq
id|BJ_None
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;remove from checkpoint list&quot;
)paren
suffix:semicolon
id|__journal_remove_checkpoint
c_func
(paren
id|jh
)paren
suffix:semicolon
id|__journal_remove_journal_head
c_func
(paren
id|bh
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;release&quot;
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * log_wait_for_space: wait until there is space in the journal.&n; *&n; * Called with the journal already locked, but it will be unlocked if we have&n; * to wait for a checkpoint to free up some space in the log.&n; */
DECL|function|log_wait_for_space
r_void
id|log_wait_for_space
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
id|nblocks
)paren
(brace
r_while
c_loop
(paren
id|log_space_left
c_func
(paren
id|journal
)paren
OL
id|nblocks
)paren
(brace
r_if
c_cond
(paren
id|journal-&gt;j_flags
op_amp
id|JFS_ABORT
)paren
r_return
suffix:semicolon
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|journal-&gt;j_checkpoint_sem
)paren
suffix:semicolon
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* Test again, another process may have checkpointed&n;&t;&t; * while we were waiting for the checkpoint lock */
r_if
c_cond
(paren
id|log_space_left
c_func
(paren
id|journal
)paren
OL
id|nblocks
)paren
(brace
id|log_do_checkpoint
c_func
(paren
id|journal
comma
id|nblocks
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|journal-&gt;j_checkpoint_sem
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Clean up a transaction&squot;s checkpoint list.  &n; *&n; * We wait for any pending IO to complete and make sure any clean&n; * buffers are removed from the transaction. &n; *&n; * Return 1 if we performed any actions which might have destroyed the&n; * checkpoint.  (journal_remove_checkpoint() deletes the transaction when&n; * the last checkpoint buffer is cleansed)&n; *&n; * Called with the journal locked.&n; * Called with journal_datalist_lock held.&n; */
DECL|function|__cleanup_transaction
r_static
r_int
id|__cleanup_transaction
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|transaction_t
op_star
id|transaction
)paren
(brace
r_struct
id|journal_head
op_star
id|jh
comma
op_star
id|next_jh
comma
op_star
id|last_jh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|assert_spin_locked
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|jh
op_assign
id|transaction-&gt;t_checkpoint_list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jh
)paren
r_return
l_int|0
suffix:semicolon
id|last_jh
op_assign
id|jh-&gt;b_cpprev
suffix:semicolon
id|next_jh
op_assign
id|jh
suffix:semicolon
r_do
(brace
id|jh
op_assign
id|next_jh
suffix:semicolon
id|bh
op_assign
id|jh2bh
c_func
(paren
id|jh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_locked
c_func
(paren
id|bh
)paren
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* the journal_head may have gone by now */
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;brelse&quot;
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|out_return_1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|jh-&gt;b_transaction
op_ne
l_int|NULL
)paren
(brace
id|transaction_t
op_star
id|transaction
op_assign
id|jh-&gt;b_transaction
suffix:semicolon
id|tid_t
id|tid
op_assign
id|transaction-&gt;t_tid
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|log_start_commit
c_func
(paren
id|journal
comma
id|transaction
)paren
suffix:semicolon
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|log_wait_commit
c_func
(paren
id|journal
comma
id|tid
)paren
suffix:semicolon
r_goto
id|out_return_1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We used to test for (jh-&gt;b_list != BUF_CLEAN) here.&n;&t;&t; * But unmap_underlying_metadata() can place buffer onto&n;&t;&t; * BUF_CLEAN.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * AKPM: I think the buffer_jdirty test is redundant - it&n;&t;&t; * shouldn&squot;t have NULL b_transaction?&n;&t;&t; */
id|next_jh
op_assign
id|jh-&gt;b_cpnext
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_jdirty
c_func
(paren
id|bh
)paren
)paren
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;remove from checkpoint&quot;
)paren
suffix:semicolon
id|__journal_remove_checkpoint
c_func
(paren
id|jh
)paren
suffix:semicolon
id|__journal_remove_journal_head
c_func
(paren
id|bh
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|jh
op_assign
id|next_jh
suffix:semicolon
)brace
r_while
c_loop
(paren
id|jh
op_ne
id|last_jh
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|out_return_1
suffix:colon
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|NR_BATCH
mdefine_line|#define NR_BATCH&t;64
DECL|function|__flush_batch
r_static
r_void
id|__flush_batch
c_func
(paren
r_struct
id|buffer_head
op_star
op_star
id|bhs
comma
r_int
op_star
id|batch_count
)paren
(brace
r_int
id|i
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|WRITE
comma
op_star
id|batch_count
comma
id|bhs
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
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
op_star
id|batch_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|bhs
(braket
id|i
)braket
suffix:semicolon
id|clear_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;brelse&quot;
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
op_star
id|batch_count
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to flush one buffer from the checkpoint list to disk.&n; *&n; * Return 1 if something happened which requires us to abort the current&n; * scan of the checkpoint list.  &n; *&n; * Called with journal_datalist_lock held.&n; */
DECL|function|__flush_buffer
r_static
r_int
id|__flush_buffer
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_struct
id|journal_head
op_star
id|jh
comma
r_struct
id|buffer_head
op_star
op_star
id|bhs
comma
r_int
op_star
id|batch_count
comma
r_int
op_star
id|drop_count
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|jh2bh
c_func
(paren
id|jh
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer_dirty
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|bh
)paren
op_logical_and
id|jh-&gt;b_jlist
op_eq
id|BJ_None
)paren
(brace
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|jh-&gt;b_transaction
op_eq
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Important: we are about to write the buffer, and&n;&t;&t; * possibly block, while still holding the journal lock.&n;&t;&t; * We cannot afford to let the transaction logic start&n;&t;&t; * messing around with this buffer before we write it to&n;&t;&t; * disk, as that would break recoverability.  &n;&t;&t; */
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;queue&quot;
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
suffix:semicolon
id|J_ASSERT_BH
c_func
(paren
id|bh
comma
op_logical_neg
id|test_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|bh-&gt;b_state
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|bhs
(braket
op_star
id|batch_count
)braket
op_assign
id|bh
suffix:semicolon
(paren
op_star
id|batch_count
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|batch_count
op_eq
id|NR_BATCH
)paren
(brace
id|__flush_batch
c_func
(paren
id|bhs
comma
id|batch_count
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
id|last_buffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|jh-&gt;b_cpnext
op_eq
id|jh
)paren
(brace
multiline_comment|/* We may be about to drop the transaction.  Tell the&n;&t;&t;&t; * caller that the lists have changed.&n;&t;&t;&t; */
id|last_buffer
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__try_to_free_cp_buf
c_func
(paren
id|jh
)paren
)paren
(brace
(paren
op_star
id|drop_count
)paren
op_increment
suffix:semicolon
id|ret
op_assign
id|last_buffer
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform an actual checkpoint.  We don&squot;t write out only enough to&n; * satisfy the current blocked requests: rather we submit a reasonably&n; * sized chunk of the outstanding data to disk at once for&n; * efficiency.  log_wait_for_space() will retry if we didn&squot;t free enough.&n; * &n; * However, we _do_ take into account the amount requested so that once&n; * the IO has been queued, we can return as soon as enough of it has&n; * completed to disk.  &n; *&n; * The journal should be locked before calling this function.&n; */
multiline_comment|/* @@@ `nblocks&squot; is unused.  Should it be used? */
DECL|function|log_do_checkpoint
r_int
id|log_do_checkpoint
(paren
id|journal_t
op_star
id|journal
comma
r_int
id|nblocks
)paren
(brace
id|transaction_t
op_star
id|transaction
comma
op_star
id|last_transaction
comma
op_star
id|next_transaction
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|batch_count
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhs
(braket
id|NR_BATCH
)braket
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;Start checkpoint&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * First thing: if there are any transactions in the log which&n;&t; * don&squot;t need checkpointing, just eliminate them from the&n;&t; * journal straight away.  &n;&t; */
id|result
op_assign
id|cleanup_journal_tail
c_func
(paren
id|journal
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;cleanup_journal_tail returned %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_le
l_int|0
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/*&n;&t; * OK, we need to start writing disk blocks.  Try to free up a&n;&t; * quarter of the log in a single checkpoint if we can.&n;&t; */
multiline_comment|/*&n;&t; * AKPM: check this code.  I had a feeling a while back that it&n;&t; * degenerates into a busy loop at unmount time.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
id|transaction
op_assign
id|journal-&gt;j_checkpoint_transactions
suffix:semicolon
r_if
c_cond
(paren
id|transaction
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
id|last_transaction
op_assign
id|transaction-&gt;t_cpprev
suffix:semicolon
id|next_transaction
op_assign
id|transaction
suffix:semicolon
r_do
(brace
r_struct
id|journal_head
op_star
id|jh
comma
op_star
id|last_jh
comma
op_star
id|next_jh
suffix:semicolon
r_int
id|drop_count
op_assign
l_int|0
suffix:semicolon
r_int
id|cleanup_ret
comma
id|retry
op_assign
l_int|0
suffix:semicolon
id|transaction
op_assign
id|next_transaction
suffix:semicolon
id|next_transaction
op_assign
id|transaction-&gt;t_cpnext
suffix:semicolon
id|jh
op_assign
id|transaction-&gt;t_checkpoint_list
suffix:semicolon
id|last_jh
op_assign
id|jh-&gt;b_cpprev
suffix:semicolon
id|next_jh
op_assign
id|jh
suffix:semicolon
r_do
(brace
id|jh
op_assign
id|next_jh
suffix:semicolon
id|next_jh
op_assign
id|jh-&gt;b_cpnext
suffix:semicolon
id|retry
op_assign
id|__flush_buffer
c_func
(paren
id|journal
comma
id|jh
comma
id|bhs
comma
op_amp
id|batch_count
comma
op_amp
id|drop_count
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|jh
op_ne
id|last_jh
op_logical_and
op_logical_neg
id|retry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|batch_count
)paren
(brace
id|__flush_batch
c_func
(paren
id|bhs
comma
op_amp
id|batch_count
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retry
)paren
r_goto
id|repeat
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We have walked the whole transaction list without&n;&t;&t; * finding anything to write to disk.  We had better be&n;&t;&t; * able to make some progress or we are in trouble. &n;&t;&t; */
id|cleanup_ret
op_assign
id|__cleanup_transaction
c_func
(paren
id|journal
comma
id|transaction
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|drop_count
op_ne
l_int|0
op_logical_or
id|cleanup_ret
op_ne
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
multiline_comment|/* __cleanup may have dropped lock */
)brace
r_while
c_loop
(paren
id|transaction
op_ne
id|last_transaction
)paren
suffix:semicolon
id|done
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|result
op_assign
id|cleanup_journal_tail
c_func
(paren
id|journal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the list of checkpoint transactions for the journal to see if&n; * we have already got rid of any since the last update of the log tail&n; * in the journal superblock.  If so, we can instantly roll the&n; * superblock forward to remove those transactions from the log.&n; * &n; * Return &lt;0 on error, 0 on success, 1 if there was nothing to clean up.&n; * &n; * Called with the journal lock held.&n; *&n; * This is the only part of the journaling code which really needs to be&n; * aware of transaction aborts.  Checkpointing involves writing to the&n; * main filesystem area rather than to the journal, so it can proceed&n; * even in abort state, but we must not update the journal superblock if&n; * we have an abort error outstanding.&n; */
DECL|function|cleanup_journal_tail
r_int
id|cleanup_journal_tail
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
id|transaction_t
op_star
id|transaction
suffix:semicolon
id|tid_t
id|first_tid
suffix:semicolon
r_int
r_int
id|blocknr
comma
id|freed
suffix:semicolon
multiline_comment|/* OK, work out the oldest transaction remaining in the log, and&n;&t; * the log block it starts at. &n;&t; * &n;&t; * If the log is now empty, we need to work out which is the&n;&t; * next transaction ID we will write, and where it will&n;&t; * start. */
multiline_comment|/* j_checkpoint_transactions needs locking */
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|transaction
op_assign
id|journal-&gt;j_checkpoint_transactions
suffix:semicolon
r_if
c_cond
(paren
id|transaction
)paren
(brace
id|first_tid
op_assign
id|transaction-&gt;t_tid
suffix:semicolon
id|blocknr
op_assign
id|transaction-&gt;t_log_start
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|transaction
op_assign
id|journal-&gt;j_committing_transaction
)paren
op_ne
l_int|NULL
)paren
(brace
id|first_tid
op_assign
id|transaction-&gt;t_tid
suffix:semicolon
id|blocknr
op_assign
id|transaction-&gt;t_log_start
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|transaction
op_assign
id|journal-&gt;j_running_transaction
)paren
op_ne
l_int|NULL
)paren
(brace
id|first_tid
op_assign
id|transaction-&gt;t_tid
suffix:semicolon
id|blocknr
op_assign
id|journal-&gt;j_head
suffix:semicolon
)brace
r_else
(brace
id|first_tid
op_assign
id|journal-&gt;j_transaction_sequence
suffix:semicolon
id|blocknr
op_assign
id|journal-&gt;j_head
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|blocknr
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* If the oldest pinned transaction is at the tail of the log&n;           already then there&squot;s not much we can do right now. */
r_if
c_cond
(paren
id|journal-&gt;j_tail_sequence
op_eq
id|first_tid
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* OK, update the superblock to recover the freed space.&n;&t; * Physical blocks come first: have we wrapped beyond the end of&n;&t; * the log?  */
id|freed
op_assign
id|blocknr
op_minus
id|journal-&gt;j_tail
suffix:semicolon
r_if
c_cond
(paren
id|blocknr
OL
id|journal-&gt;j_tail
)paren
id|freed
op_assign
id|freed
op_plus
id|journal-&gt;j_last
op_minus
id|journal-&gt;j_first
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;Cleaning journal tail from %d to %d (offset %lu), &quot;
l_string|&quot;freeing %lu&bslash;n&quot;
comma
id|journal-&gt;j_tail_sequence
comma
id|first_tid
comma
id|blocknr
comma
id|freed
)paren
suffix:semicolon
id|journal-&gt;j_free
op_add_assign
id|freed
suffix:semicolon
id|journal-&gt;j_tail_sequence
op_assign
id|first_tid
suffix:semicolon
id|journal-&gt;j_tail
op_assign
id|blocknr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|journal-&gt;j_flags
op_amp
id|JFS_ABORT
)paren
)paren
id|journal_update_superblock
c_func
(paren
id|journal
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Checkpoint list management */
multiline_comment|/*&n; * journal_clean_checkpoint_list&n; *&n; * Find all the written-back checkpoint buffers in the journal and release them.&n; *&n; * Called with the journal locked.&n; * Called with journal_datalist_lock held.&n; * Returns number of bufers reaped (for debug)&n; */
DECL|function|__journal_clean_checkpoint_list
r_int
id|__journal_clean_checkpoint_list
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
id|transaction_t
op_star
id|transaction
comma
op_star
id|last_transaction
comma
op_star
id|next_transaction
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|transaction
op_assign
id|journal-&gt;j_checkpoint_transactions
suffix:semicolon
r_if
c_cond
(paren
id|transaction
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|last_transaction
op_assign
id|transaction-&gt;t_cpprev
suffix:semicolon
id|next_transaction
op_assign
id|transaction
suffix:semicolon
r_do
(brace
r_struct
id|journal_head
op_star
id|jh
suffix:semicolon
id|transaction
op_assign
id|next_transaction
suffix:semicolon
id|next_transaction
op_assign
id|transaction-&gt;t_cpnext
suffix:semicolon
id|jh
op_assign
id|transaction-&gt;t_checkpoint_list
suffix:semicolon
r_if
c_cond
(paren
id|jh
)paren
(brace
r_struct
id|journal_head
op_star
id|last_jh
op_assign
id|jh-&gt;b_cpprev
suffix:semicolon
r_struct
id|journal_head
op_star
id|next_jh
op_assign
id|jh
suffix:semicolon
r_do
(brace
id|jh
op_assign
id|next_jh
suffix:semicolon
id|next_jh
op_assign
id|jh-&gt;b_cpnext
suffix:semicolon
id|ret
op_add_assign
id|__try_to_free_cp_buf
c_func
(paren
id|jh
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|jh
op_ne
id|last_jh
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|transaction
op_ne
id|last_transaction
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* &n; * journal_remove_checkpoint: called after a buffer has been committed&n; * to disk (either by being write-back flushed to disk, or being&n; * committed to the log).&n; *&n; * We cannot safely clean a transaction out of the log until all of the&n; * buffer updates committed in that transaction have safely been stored&n; * elsewhere on disk.  To achieve this, all of the buffers in a&n; * transaction need to be maintained on the transaction&squot;s checkpoint&n; * list until they have been rewritten, at which point this function is&n; * called to remove the buffer from the existing transaction&squot;s&n; * checkpoint list.  &n; *&n; * This function is called with the journal locked.&n; * This function is called with journal_datalist_lock held.&n; */
DECL|function|__journal_remove_checkpoint
r_void
id|__journal_remove_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
id|transaction_t
op_star
id|transaction
suffix:semicolon
id|journal_t
op_star
id|journal
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;entry&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|transaction
op_assign
id|jh-&gt;b_cp_transaction
)paren
op_eq
l_int|NULL
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;not on transaction&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|journal
op_assign
id|transaction-&gt;t_journal
suffix:semicolon
id|__buffer_unlink
c_func
(paren
id|jh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transaction-&gt;t_checkpoint_list
op_ne
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;transaction has no more buffers&quot;
)paren
suffix:semicolon
multiline_comment|/* There is one special case to worry about: if we have just&n;           pulled the buffer off a committing transaction&squot;s forget list,&n;           then even if the checkpoint list is empty, the transaction&n;           obviously cannot be dropped! */
r_if
c_cond
(paren
id|transaction
op_eq
id|journal-&gt;j_committing_transaction
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;belongs to committing transaction&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* OK, that was the last buffer for the transaction: we can now&n;&t;   safely remove this transaction from the log */
id|__journal_drop_transaction
c_func
(paren
id|journal
comma
id|transaction
)paren
suffix:semicolon
multiline_comment|/* Just in case anybody was waiting for more transactions to be&n;           checkpointed... */
id|wake_up
c_func
(paren
op_amp
id|journal-&gt;j_wait_logspace
)paren
suffix:semicolon
id|out
suffix:colon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;exit&quot;
)paren
suffix:semicolon
)brace
DECL|function|journal_remove_checkpoint
r_void
id|journal_remove_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|__journal_remove_checkpoint
c_func
(paren
id|jh
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * journal_insert_checkpoint: put a committed buffer onto a checkpoint&n; * list so that we know when it is safe to clean the transaction out of&n; * the log.&n; *&n; * Called with the journal locked.&n; * Called with journal_datalist_lock held.&n; */
DECL|function|__journal_insert_checkpoint
r_void
id|__journal_insert_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
comma
id|transaction_t
op_star
id|transaction
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;entry&quot;
)paren
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|buffer_dirty
c_func
(paren
id|jh2bh
c_func
(paren
id|jh
)paren
)paren
op_logical_or
id|buffer_jdirty
c_func
(paren
id|jh2bh
c_func
(paren
id|jh
)paren
)paren
)paren
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|jh-&gt;b_cp_transaction
op_eq
l_int|NULL
)paren
suffix:semicolon
id|assert_spin_locked
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|jh-&gt;b_cp_transaction
op_assign
id|transaction
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transaction-&gt;t_checkpoint_list
)paren
(brace
id|jh-&gt;b_cpnext
op_assign
id|jh-&gt;b_cpprev
op_assign
id|jh
suffix:semicolon
)brace
r_else
(brace
id|jh-&gt;b_cpnext
op_assign
id|transaction-&gt;t_checkpoint_list
suffix:semicolon
id|jh-&gt;b_cpprev
op_assign
id|transaction-&gt;t_checkpoint_list-&gt;b_cpprev
suffix:semicolon
id|jh-&gt;b_cpprev-&gt;b_cpnext
op_assign
id|jh
suffix:semicolon
id|jh-&gt;b_cpnext-&gt;b_cpprev
op_assign
id|jh
suffix:semicolon
)brace
id|transaction-&gt;t_checkpoint_list
op_assign
id|jh
suffix:semicolon
)brace
DECL|function|journal_insert_checkpoint
r_void
id|journal_insert_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
comma
id|transaction_t
op_star
id|transaction
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|__journal_insert_checkpoint
c_func
(paren
id|jh
comma
id|transaction
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We&squot;ve finished with this transaction structure: adios...&n; * &n; * The transaction must have no links except for the checkpoint by this&n; * point.&n; *&n; * Called with the journal locked.&n; * Called with journal_datalist_lock held.&n; */
DECL|function|__journal_drop_transaction
r_void
id|__journal_drop_transaction
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|transaction_t
op_star
id|transaction
)paren
(brace
id|assert_spin_locked
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transaction-&gt;t_cpnext
)paren
(brace
id|transaction-&gt;t_cpnext-&gt;t_cpprev
op_assign
id|transaction-&gt;t_cpprev
suffix:semicolon
id|transaction-&gt;t_cpprev-&gt;t_cpnext
op_assign
id|transaction-&gt;t_cpnext
suffix:semicolon
r_if
c_cond
(paren
id|journal-&gt;j_checkpoint_transactions
op_eq
id|transaction
)paren
id|journal-&gt;j_checkpoint_transactions
op_assign
id|transaction-&gt;t_cpnext
suffix:semicolon
r_if
c_cond
(paren
id|journal-&gt;j_checkpoint_transactions
op_eq
id|transaction
)paren
id|journal-&gt;j_checkpoint_transactions
op_assign
l_int|NULL
suffix:semicolon
)brace
id|J_ASSERT
(paren
id|transaction-&gt;t_ilist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_buffers
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_sync_datalist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_forget
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_iobuf_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_shadow_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_log_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_checkpoint_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_updates
op_eq
l_int|0
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|list_empty
c_func
(paren
op_amp
id|transaction-&gt;t_jcb
)paren
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|transaction-&gt;t_journal-&gt;j_committing_transaction
op_ne
id|transaction
)paren
suffix:semicolon
id|jbd_debug
(paren
l_int|1
comma
l_string|&quot;Dropping transaction %d, all done&bslash;n&quot;
comma
id|transaction-&gt;t_tid
)paren
suffix:semicolon
id|kfree
(paren
id|transaction
)paren
suffix:semicolon
)brace
eof
