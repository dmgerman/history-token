multiline_comment|/*&n; * linux/fs/commit.c&n; *&n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;, 1998&n; *&n; * Copyright 1998 Red Hat corp --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Journal commit routines for the generic filesystem journaling code;&n; * part of the ext2fs journaling system.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
r_extern
id|spinlock_t
id|journal_datalist_lock
suffix:semicolon
multiline_comment|/*&n; * Default IO end handler for temporary BJ_IO buffer_heads.&n; */
DECL|function|journal_end_buffer_io_sync
r_static
r_void
id|journal_end_buffer_io_sync
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * journal_commit_transaction&n; *&n; * The primary function for committing a transaction to the log.  This&n; * function is called by the journal thread to begin a complete commit.&n; */
DECL|function|journal_commit_transaction
r_void
id|journal_commit_transaction
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
id|transaction_t
op_star
id|commit_transaction
suffix:semicolon
r_struct
id|journal_head
op_star
id|jh
comma
op_star
id|new_jh
comma
op_star
id|descriptor
suffix:semicolon
r_struct
id|journal_head
op_star
id|next_jh
comma
op_star
id|last_jh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|wbuf
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|bufs
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
id|blocknr
suffix:semicolon
r_char
op_star
id|tagp
op_assign
l_int|NULL
suffix:semicolon
id|journal_header_t
op_star
id|header
suffix:semicolon
id|journal_block_tag_t
op_star
id|tag
op_assign
l_int|NULL
suffix:semicolon
r_int
id|space_left
op_assign
l_int|0
suffix:semicolon
r_int
id|first_tag
op_assign
l_int|0
suffix:semicolon
r_int
id|tag_flag
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * First job: lock down the current transaction and wait for&n;&t; * all outstanding updates to complete.&n;&t; */
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* Protect journal-&gt;j_running_transaction */
macro_line|#ifdef COMMIT_STATS
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|summarise_journal_usage
c_func
(paren
id|journal
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
macro_line|#endif
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|journal-&gt;j_running_transaction
op_ne
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|journal-&gt;j_committing_transaction
op_eq
l_int|NULL
)paren
suffix:semicolon
id|commit_transaction
op_assign
id|journal-&gt;j_running_transaction
suffix:semicolon
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_state
op_eq
id|T_RUNNING
)paren
suffix:semicolon
id|jbd_debug
(paren
l_int|1
comma
l_string|&quot;JBD: starting commit of transaction %d&bslash;n&quot;
comma
id|commit_transaction-&gt;t_tid
)paren
suffix:semicolon
id|commit_transaction-&gt;t_state
op_assign
id|T_LOCKED
suffix:semicolon
r_while
c_loop
(paren
id|commit_transaction-&gt;t_updates
op_ne
l_int|0
)paren
(brace
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|sleep_on
c_func
(paren
op_amp
id|journal-&gt;j_wait_updates
)paren
suffix:semicolon
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
)brace
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_outstanding_credits
op_le
id|journal-&gt;j_max_transaction_buffers
)paren
suffix:semicolon
multiline_comment|/* Do we need to erase the effects of a prior journal_flush? */
r_if
c_cond
(paren
id|journal-&gt;j_flags
op_amp
id|JFS_FLUSHED
)paren
(brace
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;super block updated&bslash;n&quot;
)paren
suffix:semicolon
id|journal_update_superblock
c_func
(paren
id|journal
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;superblock not updated&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * First thing we are allowed to do is to discard any remaining&n;&t; * BJ_Reserved buffers.  Note, it is _not_ permissible to assume&n;&t; * that there are no such buffers: if a large filesystem&n;&t; * operation like a truncate needs to split itself over multiple&n;&t; * transactions, then it may try to do a journal_restart() while&n;&t; * there are still BJ_Reserved buffers outstanding.  These must&n;&t; * be released cleanly from the current transaction.&n;&t; *&n;&t; * In this case, the filesystem must still reserve write access&n;&t; * again before modifying the buffer in the new transaction, but&n;&t; * we do not require it to remember exactly which old buffers it&n;&t; * has reserved.  This is consistent with the existing behaviour&n;&t; * that multiple journal_get_write_access() calls to the same&n;&t; * buffer are perfectly permissable.&n;&t; */
r_while
c_loop
(paren
id|commit_transaction-&gt;t_reserved_list
)paren
(brace
id|jh
op_assign
id|commit_transaction-&gt;t_reserved_list
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;reserved, unused: refile&quot;
)paren
suffix:semicolon
id|journal_refile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now try to drop any written-back buffers from the journal&squot;s&n;&t; * checkpoint lists.  We do this *before* commit because it potentially&n;&t; * frees some memory&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|__journal_clean_checkpoint_list
c_func
(paren
id|journal
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
multiline_comment|/* First part of the commit: force the revoke list out to disk.&n;&t; * The revoke code generates its own metadata blocks on disk for this.&n;&t; *&n;&t; * It is important that we do this while the transaction is&n;&t; * still locked.  Generating the revoke records should not&n;&t; * generate any IO stalls, so this should be quick; and doing&n;&t; * the work while we have the transaction locked means that we&n;&t; * only ever have to maintain the revoke list for one&n;&t; * transaction at a time.&n;&t; */
id|jbd_debug
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 1&bslash;n&quot;
)paren
suffix:semicolon
id|journal_write_revoke_records
c_func
(paren
id|journal
comma
id|commit_transaction
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now that we have built the revoke records, we can start&n;&t; * reusing the revoke list for a new running transaction.  We&n;&t; * can now safely start committing the old transaction: time to&n;&t; * get a new running transaction for incoming filesystem updates&n;&t; */
id|commit_transaction-&gt;t_state
op_assign
id|T_FLUSH
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|journal-&gt;j_wait_transaction_locked
)paren
suffix:semicolon
id|journal-&gt;j_committing_transaction
op_assign
id|commit_transaction
suffix:semicolon
id|journal-&gt;j_running_transaction
op_assign
l_int|NULL
suffix:semicolon
id|commit_transaction-&gt;t_log_start
op_assign
id|journal-&gt;j_head
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|jbd_debug
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 2&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now start flushing things to disk, in the order they appear&n;&t; * on the transaction lists.  Data blocks go first.&n;&t; */
multiline_comment|/*&n;&t; * Whenever we unlock the journal and sleep, things can get added&n;&t; * onto -&gt;t_datalist, so we have to keep looping back to write_out_data&n;&t; * until we *know* that the list is empty.&n;&t; */
id|write_out_data
suffix:colon
multiline_comment|/*&n;&t; * Cleanup any flushed data buffers from the data list.  Even in&n;&t; * abort mode, we want to flush this out as soon as possible.&n;&t; *&n;&t; * We take journal_datalist_lock to protect the lists from&n;&t; * journal_try_to_free_buffers().&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|write_out_data_locked
suffix:colon
id|bufs
op_assign
l_int|0
suffix:semicolon
id|next_jh
op_assign
id|commit_transaction-&gt;t_sync_datalist
suffix:semicolon
r_if
c_cond
(paren
id|next_jh
op_eq
l_int|NULL
)paren
r_goto
id|sync_datalist_empty
suffix:semicolon
id|last_jh
op_assign
id|next_jh-&gt;b_tprev
suffix:semicolon
r_do
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|jh
op_assign
id|next_jh
suffix:semicolon
id|next_jh
op_assign
id|jh-&gt;b_tnext
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
op_logical_neg
id|buffer_locked
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
id|buffer_dirty
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
l_string|&quot;start journal writeout&quot;
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
suffix:semicolon
id|wbuf
(braket
id|bufs
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;writeout complete: unfile&quot;
)paren
suffix:semicolon
id|__journal_unfile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
id|jh-&gt;b_transaction
op_assign
l_int|NULL
suffix:semicolon
id|__journal_remove_journal_head
c_func
(paren
id|bh
)paren
suffix:semicolon
id|refile_buffer
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
)brace
)brace
r_if
c_cond
(paren
id|bufs
op_eq
id|ARRAY_SIZE
c_func
(paren
id|wbuf
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Major speedup: start here on the next scan&n;&t;&t;&t; */
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_sync_datalist
op_ne
l_int|0
)paren
suffix:semicolon
id|commit_transaction-&gt;t_sync_datalist
op_assign
id|jh
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|jh
op_ne
id|last_jh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bufs
op_logical_or
id|current-&gt;need_resched
)paren
(brace
id|jbd_debug
c_func
(paren
l_int|2
comma
l_string|&quot;submit %d writes&bslash;n&quot;
comma
id|bufs
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
r_if
c_cond
(paren
id|bufs
)paren
id|ll_rw_block
c_func
(paren
id|WRITE
comma
id|bufs
comma
id|wbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|journal_brelse_array
c_func
(paren
id|wbuf
comma
id|bufs
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|bufs
)paren
r_goto
id|write_out_data_locked
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wait for all previously submitted IO on the data list to complete.&n;&t; */
id|jh
op_assign
id|commit_transaction-&gt;t_sync_datalist
suffix:semicolon
r_if
c_cond
(paren
id|jh
op_eq
l_int|NULL
)paren
r_goto
id|sync_datalist_empty
suffix:semicolon
r_do
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|jh
op_assign
id|jh-&gt;b_tprev
suffix:semicolon
multiline_comment|/* Wait on the last written */
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
multiline_comment|/* the journal_head may have been removed now */
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
r_goto
id|write_out_data
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
(brace
r_goto
id|write_out_data_locked
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|jh
op_ne
id|commit_transaction-&gt;t_sync_datalist
)paren
suffix:semicolon
r_goto
id|write_out_data_locked
suffix:semicolon
id|sync_datalist_empty
suffix:colon
multiline_comment|/*&n;&t; * Wait for all the async writepage data.  As they become unlocked&n;&t; * in end_buffer_io_async(), the only place where they can be&n;&t; * reaped is in try_to_free_buffers(), and we&squot;re locked against&n;&t; * that.&n;&t; */
r_while
c_loop
(paren
(paren
id|jh
op_assign
id|commit_transaction-&gt;t_async_datalist
)paren
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
r_continue
suffix:semicolon
multiline_comment|/* List may have changed */
)brace
r_if
c_cond
(paren
id|jh-&gt;b_next_transaction
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * For writepage() buffers in journalled data mode: a&n;&t;&t;&t; * later transaction may want the buffer for &quot;metadata&quot;&n;&t;&t;&t; */
id|__journal_refile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
)brace
r_else
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;finished async writeout: unfile&quot;
)paren
suffix:semicolon
id|__journal_unfile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
id|jh-&gt;b_transaction
op_assign
l_int|NULL
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
l_string|&quot;finished async writeout: refile&quot;
)paren
suffix:semicolon
multiline_comment|/* It can sometimes be on BUF_LOCKED due to migration&n;&t;&t;&t; * from syncdata to asyncdata */
r_if
c_cond
(paren
id|bh-&gt;b_list
op_ne
id|BUF_CLEAN
)paren
id|refile_buffer
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
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we found any dirty or locked buffers, then we should have&n;&t; * looped back up to the write_out_data label.  If there weren&squot;t&n;&t; * any then journal_clean_data_list should have wiped the list&n;&t; * clean by now, so check that it is in fact empty.&n;&t; */
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_sync_datalist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_async_datalist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|jbd_debug
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 3&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Way to go: we have now written out all of the data for a&n;&t; * transaction!  Now comes the tricky part: we need to write out&n;&t; * metadata.  Loop over the transaction&squot;s entire buffer list:&n;&t; */
id|commit_transaction-&gt;t_state
op_assign
id|T_COMMIT
suffix:semicolon
id|descriptor
op_assign
l_int|0
suffix:semicolon
id|bufs
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|commit_transaction-&gt;t_buffers
)paren
(brace
multiline_comment|/* Find the next buffer to be journaled... */
id|jh
op_assign
id|commit_transaction-&gt;t_buffers
suffix:semicolon
multiline_comment|/* If we&squot;re in abort mode, we just un-journal the buffer and&n;&t;&t;   release it for background writing. */
r_if
c_cond
(paren
id|is_journal_aborted
c_func
(paren
id|journal
)paren
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;journal is aborting: refile&quot;
)paren
suffix:semicolon
id|journal_refile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
multiline_comment|/* If that was the last one, we need to clean up&n;&t;&t;&t; * any descriptor buffers which may have been&n;&t;&t;&t; * already allocated, even if we are now&n;&t;&t;&t; * aborting. */
r_if
c_cond
(paren
op_logical_neg
id|commit_transaction-&gt;t_buffers
)paren
r_goto
id|start_journal_io
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Make sure we have a descriptor block in which to&n;&t;&t;   record the metadata buffer. */
r_if
c_cond
(paren
op_logical_neg
id|descriptor
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|J_ASSERT
(paren
id|bufs
op_eq
l_int|0
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|4
comma
l_string|&quot;JBD: get descriptor&bslash;n&quot;
)paren
suffix:semicolon
id|descriptor
op_assign
id|journal_get_descriptor_buffer
c_func
(paren
id|journal
)paren
suffix:semicolon
id|bh
op_assign
id|jh2bh
c_func
(paren
id|descriptor
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|4
comma
l_string|&quot;JBD: got buffer %ld (%p)&bslash;n&quot;
comma
id|bh-&gt;b_blocknr
comma
id|bh-&gt;b_data
)paren
suffix:semicolon
id|header
op_assign
(paren
id|journal_header_t
op_star
)paren
op_amp
id|bh-&gt;b_data
(braket
l_int|0
)braket
suffix:semicolon
id|header-&gt;h_magic
op_assign
id|htonl
c_func
(paren
id|JFS_MAGIC_NUMBER
)paren
suffix:semicolon
id|header-&gt;h_blocktype
op_assign
id|htonl
c_func
(paren
id|JFS_DESCRIPTOR_BLOCK
)paren
suffix:semicolon
id|header-&gt;h_sequence
op_assign
id|htonl
c_func
(paren
id|commit_transaction-&gt;t_tid
)paren
suffix:semicolon
id|tagp
op_assign
op_amp
id|bh-&gt;b_data
(braket
r_sizeof
(paren
id|journal_header_t
)paren
)braket
suffix:semicolon
id|space_left
op_assign
id|bh-&gt;b_size
op_minus
r_sizeof
(paren
id|journal_header_t
)paren
suffix:semicolon
id|first_tag
op_assign
l_int|1
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
id|wbuf
(braket
id|bufs
op_increment
)braket
op_assign
id|bh
suffix:semicolon
multiline_comment|/* Record it so that we can wait for IO&n;                           completion later */
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;ph3: file as descriptor&quot;
)paren
suffix:semicolon
id|journal_file_buffer
c_func
(paren
id|descriptor
comma
id|commit_transaction
comma
id|BJ_LogCtl
)paren
suffix:semicolon
)brace
multiline_comment|/* Where is the buffer to be written? */
id|blocknr
op_assign
id|journal_next_log_block
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* Bump b_count to prevent truncate from stumbling over&n;                   the shadowed buffer!  @@@ This can go if we ever get&n;                   rid of the BJ_IO/BJ_Shadow pairing of buffers. */
id|atomic_inc
c_func
(paren
op_amp
id|jh2bh
c_func
(paren
id|jh
)paren
op_member_access_from_pointer
id|b_count
)paren
suffix:semicolon
multiline_comment|/* Make a temporary IO buffer with which to write it out&n;                   (this will requeue both the metadata buffer and the&n;                   temporary IO buffer). new_bh goes on BJ_IO*/
id|set_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|jh2bh
c_func
(paren
id|jh
)paren
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * akpm: journal_write_metadata_buffer() sets&n;&t;&t; * new_bh-&gt;b_transaction to commit_transaction.&n;&t;&t; * We need to clean this up before we release new_bh&n;&t;&t; * (which is of type BJ_IO)&n;&t;&t; */
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;ph3: write metadata&quot;
)paren
suffix:semicolon
id|flags
op_assign
id|journal_write_metadata_buffer
c_func
(paren
id|commit_transaction
comma
id|jh
comma
op_amp
id|new_jh
comma
id|blocknr
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|jh2bh
c_func
(paren
id|new_jh
)paren
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
id|wbuf
(braket
id|bufs
op_increment
)braket
op_assign
id|jh2bh
c_func
(paren
id|new_jh
)paren
suffix:semicolon
multiline_comment|/* Record the new block&squot;s tag in the current descriptor&n;                   buffer */
id|tag_flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
l_int|1
)paren
id|tag_flag
op_or_assign
id|JFS_FLAG_ESCAPE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first_tag
)paren
id|tag_flag
op_or_assign
id|JFS_FLAG_SAME_UUID
suffix:semicolon
id|tag
op_assign
(paren
id|journal_block_tag_t
op_star
)paren
id|tagp
suffix:semicolon
id|tag-&gt;t_blocknr
op_assign
id|htonl
c_func
(paren
id|jh2bh
c_func
(paren
id|jh
)paren
op_member_access_from_pointer
id|b_blocknr
)paren
suffix:semicolon
id|tag-&gt;t_flags
op_assign
id|htonl
c_func
(paren
id|tag_flag
)paren
suffix:semicolon
id|tagp
op_add_assign
r_sizeof
(paren
id|journal_block_tag_t
)paren
suffix:semicolon
id|space_left
op_sub_assign
r_sizeof
(paren
id|journal_block_tag_t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_tag
)paren
(brace
id|memcpy
(paren
id|tagp
comma
id|journal-&gt;j_uuid
comma
l_int|16
)paren
suffix:semicolon
id|tagp
op_add_assign
l_int|16
suffix:semicolon
id|space_left
op_sub_assign
l_int|16
suffix:semicolon
id|first_tag
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If there&squot;s no more to do, or if the descriptor is full,&n;&t;&t;   let the IO rip! */
r_if
c_cond
(paren
id|bufs
op_eq
id|ARRAY_SIZE
c_func
(paren
id|wbuf
)paren
op_logical_or
id|commit_transaction-&gt;t_buffers
op_eq
l_int|NULL
op_logical_or
id|space_left
OL
r_sizeof
(paren
id|journal_block_tag_t
)paren
op_plus
l_int|16
)paren
(brace
id|jbd_debug
c_func
(paren
l_int|4
comma
l_string|&quot;JBD: Submit %d IOs&bslash;n&quot;
comma
id|bufs
)paren
suffix:semicolon
multiline_comment|/* Write an end-of-descriptor marker before&n;                           submitting the IOs.  &quot;tag&quot; still points to&n;                           the last tag we set up. */
id|tag-&gt;t_flags
op_or_assign
id|htonl
c_func
(paren
id|JFS_FLAG_LAST_TAG
)paren
suffix:semicolon
id|start_journal_io
suffix:colon
id|unlock_journal
c_func
(paren
id|journal
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
id|bufs
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
id|wbuf
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|BH_Lock
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|BH_Dirty
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
id|bh-&gt;b_end_io
op_assign
id|journal_end_buffer_io_sync
suffix:semicolon
id|submit_bh
c_func
(paren
id|WRITE
comma
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* Force a new descriptor to be generated next&n;                           time round the loop. */
id|descriptor
op_assign
l_int|NULL
suffix:semicolon
id|bufs
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Lo and behold: we have just managed to send a transaction to&n;           the log.  Before we can commit it, wait for the IO so far to&n;           complete.  Control buffers being written are on the&n;           transaction&squot;s t_log_list queue, and metadata buffers are on&n;           the t_iobuf_list queue.&n;&n;&t;   Wait for the transactions in reverse order.  That way we are&n;&t;   less likely to be woken up until all IOs have completed, and&n;&t;   so we incur less scheduling load.&n;&t;*/
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 4&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* akpm: these are BJ_IO, and journal_datalist_lock is not needed */
id|wait_for_iobuf
suffix:colon
r_while
c_loop
(paren
id|commit_transaction-&gt;t_iobuf_list
op_ne
l_int|NULL
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|jh
op_assign
id|commit_transaction-&gt;t_iobuf_list-&gt;b_tprev
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
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
r_goto
id|wait_for_iobuf
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|BH_JWrite
comma
op_amp
id|jh2bh
c_func
(paren
id|jh
)paren
op_member_access_from_pointer
id|b_state
)paren
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;ph4: unfile after journal write&quot;
)paren
suffix:semicolon
id|journal_unfile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * akpm: don&squot;t put back a buffer_head with stale pointers&n;&t;&t; * dangling around.&n;&t;&t; */
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|jh-&gt;b_transaction
op_ne
l_int|NULL
)paren
suffix:semicolon
id|jh-&gt;b_transaction
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * -&gt;t_iobuf_list should contain only dummy buffer_heads&n;&t;&t; * which were created by journal_write_metadata_buffer().&n;&t;&t; */
id|bh
op_assign
id|jh2bh
c_func
(paren
id|jh
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;dumping temporary bh&quot;
)paren
suffix:semicolon
id|journal_unlock_journal_head
c_func
(paren
id|jh
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|J_ASSERT_BH
c_func
(paren
id|bh
comma
id|atomic_read
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|put_unused_buffer_head
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* We also have to unlock and free the corresponding&n;                   shadowed buffer */
id|jh
op_assign
id|commit_transaction-&gt;t_shadow_list-&gt;b_tprev
suffix:semicolon
id|bh
op_assign
id|jh2bh
c_func
(paren
id|jh
)paren
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
id|J_ASSERT_BH
c_func
(paren
id|bh
comma
id|buffer_jdirty
c_func
(paren
id|bh
)paren
)paren
suffix:semicolon
multiline_comment|/* The metadata is now released for reuse, but we need&n;                   to remember it against this transaction so that when&n;                   we finally commit, we can do any checkpointing&n;                   required. */
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;file as BJ_Forget&quot;
)paren
suffix:semicolon
id|journal_file_buffer
c_func
(paren
id|jh
comma
id|commit_transaction
comma
id|BJ_Forget
)paren
suffix:semicolon
multiline_comment|/* Wake up any transactions which were waiting for this&n;&t;&t;   IO to complete */
id|wake_up
c_func
(paren
op_amp
id|bh-&gt;b_wait
)paren
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;brelse shadowed buffer&quot;
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_shadow_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 5&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Here we wait for the revoke record and descriptor record buffers */
id|wait_for_ctlbuf
suffix:colon
r_while
c_loop
(paren
id|commit_transaction-&gt;t_log_list
op_ne
l_int|NULL
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|jh
op_assign
id|commit_transaction-&gt;t_log_list-&gt;b_tprev
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
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
r_goto
id|wait_for_ctlbuf
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;ph5: control buffer writeout done: unfile&quot;
)paren
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
id|journal_unfile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
id|jh-&gt;b_transaction
op_assign
l_int|NULL
suffix:semicolon
id|journal_unlock_journal_head
c_func
(paren
id|jh
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* One for getblk */
multiline_comment|/* AKPM: bforget here */
)brace
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 6&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Done it all: now write the commit record.  We should have&n;&t; * cleaned up our previous buffers by now, so if we are in abort&n;&t; * mode we can now just skip the rest of the journal write&n;&t; * entirely. */
r_if
c_cond
(paren
id|is_journal_aborted
c_func
(paren
id|journal
)paren
)paren
r_goto
id|skip_commit
suffix:semicolon
id|descriptor
op_assign
id|journal_get_descriptor_buffer
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* AKPM: buglet - add `i&squot; to tmp! */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|jh2bh
c_func
(paren
id|descriptor
)paren
op_member_access_from_pointer
id|b_size
suffix:semicolon
id|i
op_add_assign
l_int|512
)paren
(brace
id|journal_header_t
op_star
id|tmp
op_assign
(paren
id|journal_header_t
op_star
)paren
id|jh2bh
c_func
(paren
id|descriptor
)paren
op_member_access_from_pointer
id|b_data
suffix:semicolon
id|tmp-&gt;h_magic
op_assign
id|htonl
c_func
(paren
id|JFS_MAGIC_NUMBER
)paren
suffix:semicolon
id|tmp-&gt;h_blocktype
op_assign
id|htonl
c_func
(paren
id|JFS_COMMIT_BLOCK
)paren
suffix:semicolon
id|tmp-&gt;h_sequence
op_assign
id|htonl
c_func
(paren
id|commit_transaction-&gt;t_tid
)paren
suffix:semicolon
)brace
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|descriptor
comma
l_string|&quot;write commit block&quot;
)paren
suffix:semicolon
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|jh2bh
c_func
(paren
id|descriptor
)paren
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
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
multiline_comment|/* One for getblk() */
id|journal_unlock_journal_head
c_func
(paren
id|descriptor
)paren
suffix:semicolon
)brace
id|lock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
multiline_comment|/* End of a transaction!  Finally, we can do checkpoint&n;           processing: any buffers committed as a result of this&n;           transaction can be removed from any checkpoint list it was on&n;           before. */
id|skip_commit
suffix:colon
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 7&bslash;n&quot;
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_sync_datalist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_async_datalist
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_buffers
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_checkpoint_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_iobuf_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_shadow_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|commit_transaction-&gt;t_log_list
op_eq
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|commit_transaction-&gt;t_forget
)paren
(brace
id|transaction_t
op_star
id|cp_transaction
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|jh
op_assign
id|commit_transaction-&gt;t_forget
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|jh-&gt;b_transaction
op_eq
id|commit_transaction
op_logical_or
id|jh-&gt;b_transaction
op_eq
id|journal-&gt;j_running_transaction
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If there is undo-protected committed data against&n;&t;&t; * this buffer, then we can remove it now.  If it is a&n;&t;&t; * buffer needing such protection, the old frozen_data&n;&t;&t; * field now points to a committed version of the&n;&t;&t; * buffer, so rotate that field to the new committed&n;&t;&t; * data.&n;&t;&t; *&n;&t;&t; * Otherwise, we can just throw away the frozen data now.&n;&t;&t; */
r_if
c_cond
(paren
id|jh-&gt;b_committed_data
)paren
(brace
id|kfree
c_func
(paren
id|jh-&gt;b_committed_data
)paren
suffix:semicolon
id|jh-&gt;b_committed_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|jh-&gt;b_frozen_data
)paren
(brace
id|jh-&gt;b_committed_data
op_assign
id|jh-&gt;b_frozen_data
suffix:semicolon
id|jh-&gt;b_frozen_data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|jh-&gt;b_frozen_data
)paren
(brace
id|kfree
c_func
(paren
id|jh-&gt;b_frozen_data
)paren
suffix:semicolon
id|jh-&gt;b_frozen_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|cp_transaction
op_assign
id|jh-&gt;b_cp_transaction
suffix:semicolon
r_if
c_cond
(paren
id|cp_transaction
)paren
(brace
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;remove from old cp transaction&quot;
)paren
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|commit_transaction
op_ne
id|cp_transaction
)paren
suffix:semicolon
id|__journal_remove_checkpoint
c_func
(paren
id|jh
)paren
suffix:semicolon
)brace
multiline_comment|/* Only re-checkpoint the buffer_head if it is marked&n;&t;&t; * dirty.  If the buffer was added to the BJ_Forget list&n;&t;&t; * by journal_forget, it may no longer be dirty and&n;&t;&t; * there&squot;s no point in keeping a checkpoint record for&n;&t;&t; * it. */
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
id|buffer_jdirty
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
l_string|&quot;add to new checkpointing trans&quot;
)paren
suffix:semicolon
id|__journal_insert_checkpoint
c_func
(paren
id|jh
comma
id|commit_transaction
)paren
suffix:semicolon
id|JBUFFER_TRACE
c_func
(paren
id|jh
comma
l_string|&quot;refile for checkpoint writeback&quot;
)paren
suffix:semicolon
id|__journal_refile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
)brace
r_else
(brace
id|J_ASSERT_BH
c_func
(paren
id|bh
comma
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|jh-&gt;b_next_transaction
op_eq
l_int|NULL
)paren
suffix:semicolon
id|__journal_unfile_buffer
c_func
(paren
id|jh
)paren
suffix:semicolon
id|jh-&gt;b_transaction
op_assign
l_int|0
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
)brace
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Done with this transaction! */
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: commit phase 8&bslash;n&quot;
)paren
suffix:semicolon
id|J_ASSERT
(paren
id|commit_transaction-&gt;t_state
op_eq
id|T_COMMIT
)paren
suffix:semicolon
id|commit_transaction-&gt;t_state
op_assign
id|T_FINISHED
suffix:semicolon
id|J_ASSERT
(paren
id|commit_transaction
op_eq
id|journal-&gt;j_committing_transaction
)paren
suffix:semicolon
id|journal-&gt;j_commit_sequence
op_assign
id|commit_transaction-&gt;t_tid
suffix:semicolon
id|journal-&gt;j_committing_transaction
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_transaction-&gt;t_checkpoint_list
op_eq
l_int|NULL
)paren
(brace
id|__journal_drop_transaction
c_func
(paren
id|journal
comma
id|commit_transaction
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|journal-&gt;j_checkpoint_transactions
op_eq
l_int|NULL
)paren
(brace
id|journal-&gt;j_checkpoint_transactions
op_assign
id|commit_transaction
suffix:semicolon
id|commit_transaction-&gt;t_cpnext
op_assign
id|commit_transaction
suffix:semicolon
id|commit_transaction-&gt;t_cpprev
op_assign
id|commit_transaction
suffix:semicolon
)brace
r_else
(brace
id|commit_transaction-&gt;t_cpnext
op_assign
id|journal-&gt;j_checkpoint_transactions
suffix:semicolon
id|commit_transaction-&gt;t_cpprev
op_assign
id|commit_transaction-&gt;t_cpnext-&gt;t_cpprev
suffix:semicolon
id|commit_transaction-&gt;t_cpnext-&gt;t_cpprev
op_assign
id|commit_transaction
suffix:semicolon
id|commit_transaction-&gt;t_cpprev-&gt;t_cpnext
op_assign
id|commit_transaction
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|journal_datalist_lock
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;JBD: commit %d complete, head %d&bslash;n&quot;
comma
id|journal-&gt;j_commit_sequence
comma
id|journal-&gt;j_tail_sequence
)paren
suffix:semicolon
id|unlock_journal
c_func
(paren
id|journal
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|journal-&gt;j_wait_done_commit
)paren
suffix:semicolon
)brace
eof