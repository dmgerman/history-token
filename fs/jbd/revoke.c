multiline_comment|/*&n; * linux/fs/revoke.c&n; * &n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;, 2000&n; *&n; * Copyright 2000 Red Hat corp --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Journal revoke routines for the generic filesystem journaling code;&n; * part of the ext2fs journaling system.&n; *&n; * Revoke is the mechanism used to prevent old log records for deleted&n; * metadata from being replayed on top of newer data using the same&n; * blocks.  The revoke mechanism is used in two separate places:&n; * &n; * + Commit: during commit we write the entire list of the current&n; *   transaction&squot;s revoked blocks to the journal&n; * &n; * + Recovery: during recovery we record the transaction ID of all&n; *   revoked blocks.  If there are multiple revoke records in the log&n; *   for a single block, only the last one counts, and if there is a log&n; *   entry for a block beyond the last revoke, then that log entry still&n; *   gets replayed.&n; *&n; * We can get interactions between revokes and new log data within a&n; * single transaction:&n; *&n; * Block is revoked and then journaled:&n; *   The desired end result is the journaling of the new block, so we &n; *   cancel the revoke before the transaction commits.&n; *&n; * Block is journaled and then revoked:&n; *   The revoke must take precedence over the write of the block, so we&n; *   need either to cancel the journal entry or to write the revoke&n; *   later in the log than the log block.  In this case, we choose the&n; *   latter: journaling a block cancels any revoke record for that block&n; *   in the current transaction, so any revoke for that block in the&n; *   transaction must have happened after the block was journaled and so&n; *   the revoke must take precedence.&n; *&n; * Block is revoked and then written as data: &n; *   The data write is allowed to succeed, but the revoke is _not_&n; *   cancelled.  We still need to prevent old log records from&n; *   overwriting the new data.  We don&squot;t even need to clear the revoke&n; *   bit here.&n; *&n; * Revoke information on buffers is a tri-state value:&n; *&n; * RevokeValid clear:&t;no cached revoke status, need to look it up&n; * RevokeValid set, Revoked clear:&n; *&t;&t;&t;buffer has not been revoked, and cancel_revoke&n; *&t;&t;&t;need do nothing.&n; * RevokeValid set, Revoked set:&n; *&t;&t;&t;buffer has been revoked.  &n; */
macro_line|#ifndef __KERNEL__
macro_line|#include &quot;jfs_user.h&quot;
macro_line|#else
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#endif
DECL|variable|revoke_record_cache
r_static
id|kmem_cache_t
op_star
id|revoke_record_cache
suffix:semicolon
DECL|variable|revoke_table_cache
r_static
id|kmem_cache_t
op_star
id|revoke_table_cache
suffix:semicolon
multiline_comment|/* Each revoke record represents one single revoked block.  During&n;   journal replay, this involves recording the transaction ID of the&n;   last transaction to revoke this block. */
DECL|struct|jbd_revoke_record_s
r_struct
id|jbd_revoke_record_s
(brace
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
DECL|member|sequence
id|tid_t
id|sequence
suffix:semicolon
multiline_comment|/* Used for recovery only */
DECL|member|blocknr
r_int
r_int
id|blocknr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The revoke table is just a simple hash table of revoke records. */
DECL|struct|jbd_revoke_table_s
r_struct
id|jbd_revoke_table_s
(brace
multiline_comment|/* It is conceivable that we might want a larger hash table&n;&t; * for recovery.  Must be a power of two. */
DECL|member|hash_size
r_int
id|hash_size
suffix:semicolon
DECL|member|hash_shift
r_int
id|hash_shift
suffix:semicolon
DECL|member|hash_table
r_struct
id|list_head
op_star
id|hash_table
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_static
r_void
id|write_one_revoke_record
c_func
(paren
id|journal_t
op_star
comma
id|transaction_t
op_star
comma
r_struct
id|journal_head
op_star
op_star
comma
r_int
op_star
comma
r_struct
id|jbd_revoke_record_s
op_star
)paren
suffix:semicolon
r_static
r_void
id|flush_descriptor
c_func
(paren
id|journal_t
op_star
comma
r_struct
id|journal_head
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Utility functions to maintain the revoke table */
multiline_comment|/* Borrowed from buffer.c: this is a tried and tested block hash function */
DECL|function|hash
r_static
r_inline
r_int
id|hash
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|block
)paren
(brace
r_struct
id|jbd_revoke_table_s
op_star
id|table
op_assign
id|journal-&gt;j_revoke
suffix:semicolon
r_int
id|hash_shift
op_assign
id|table-&gt;hash_shift
suffix:semicolon
r_return
(paren
(paren
id|block
op_lshift
(paren
id|hash_shift
op_minus
l_int|6
)paren
)paren
op_xor
(paren
id|block
op_rshift
l_int|13
)paren
op_xor
(paren
id|block
op_lshift
(paren
id|hash_shift
op_minus
l_int|12
)paren
)paren
)paren
op_amp
(paren
id|table-&gt;hash_size
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|insert_revoke_hash
r_int
id|insert_revoke_hash
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|blocknr
comma
id|tid_t
id|seq
)paren
(brace
r_struct
id|list_head
op_star
id|hash_list
suffix:semicolon
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
id|repeat
suffix:colon
id|record
op_assign
id|kmem_cache_alloc
c_func
(paren
id|revoke_record_cache
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|record
)paren
r_goto
id|oom
suffix:semicolon
id|record-&gt;sequence
op_assign
id|seq
suffix:semicolon
id|record-&gt;blocknr
op_assign
id|blocknr
suffix:semicolon
id|hash_list
op_assign
op_amp
id|journal-&gt;j_revoke-&gt;hash_table
(braket
id|hash
c_func
(paren
id|journal
comma
id|blocknr
)paren
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|record-&gt;hash
comma
id|hash_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|oom
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|journal_oom_retry
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;ENOMEM in %s, retrying&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* Find a revoke record in the journal&squot;s hash table. */
DECL|function|find_revoke_record
r_static
r_struct
id|jbd_revoke_record_s
op_star
id|find_revoke_record
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|blocknr
)paren
(brace
r_struct
id|list_head
op_star
id|hash_list
suffix:semicolon
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
id|hash_list
op_assign
op_amp
id|journal-&gt;j_revoke-&gt;hash_table
(braket
id|hash
c_func
(paren
id|journal
comma
id|blocknr
)paren
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
id|record
op_assign
(paren
r_struct
id|jbd_revoke_record_s
op_star
)paren
id|hash_list-&gt;next
suffix:semicolon
r_while
c_loop
(paren
op_amp
(paren
id|record-&gt;hash
)paren
op_ne
id|hash_list
)paren
(brace
r_if
c_cond
(paren
id|record-&gt;blocknr
op_eq
id|blocknr
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
r_return
id|record
suffix:semicolon
)brace
id|record
op_assign
(paren
r_struct
id|jbd_revoke_record_s
op_star
)paren
id|record-&gt;hash.next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|journal_init_revoke_caches
r_int
id|__init
id|journal_init_revoke_caches
c_func
(paren
r_void
)paren
(brace
id|revoke_record_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;revoke_record&quot;
comma
r_sizeof
(paren
r_struct
id|jbd_revoke_record_s
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revoke_record_cache
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|revoke_table_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;revoke_table&quot;
comma
r_sizeof
(paren
r_struct
id|jbd_revoke_table_s
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revoke_table_cache
op_eq
l_int|0
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|revoke_record_cache
)paren
suffix:semicolon
id|revoke_record_cache
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|journal_destroy_revoke_caches
r_void
id|journal_destroy_revoke_caches
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|revoke_record_cache
)paren
suffix:semicolon
id|revoke_record_cache
op_assign
l_int|NULL
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|revoke_table_cache
)paren
suffix:semicolon
id|revoke_table_cache
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Initialise the revoke table for a given journal to a given size. */
DECL|function|journal_init_revoke
r_int
id|journal_init_revoke
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
id|hash_size
)paren
(brace
r_int
id|shift
comma
id|tmp
suffix:semicolon
id|J_ASSERT
(paren
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
op_eq
l_int|NULL
)paren
suffix:semicolon
id|shift
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|hash_size
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_rshift_assign
l_int|1UL
)paren
op_ne
l_int|0UL
)paren
(brace
id|shift
op_increment
suffix:semicolon
)brace
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
op_assign
id|kmem_cache_alloc
c_func
(paren
id|revoke_table_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|journal-&gt;j_revoke
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Check that the hash_size is a power of two */
id|J_ASSERT
(paren
(paren
id|hash_size
op_amp
(paren
id|hash_size
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_size
op_assign
id|hash_size
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_shift
op_assign
id|shift
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_table
op_assign
id|kmalloc
c_func
(paren
id|hash_size
op_star
r_sizeof
(paren
r_struct
id|list_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|journal-&gt;j_revoke-&gt;hash_table
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|journal-&gt;j_revoke
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|hash_size
suffix:semicolon
id|tmp
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|journal-&gt;j_revoke-&gt;hash_table
(braket
id|tmp
)braket
)paren
suffix:semicolon
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
op_assign
id|kmem_cache_alloc
c_func
(paren
id|revoke_table_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
)paren
(brace
id|kfree
c_func
(paren
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
op_member_access_from_pointer
id|hash_table
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|journal-&gt;j_revoke
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Check that the hash_size is a power of two */
id|J_ASSERT
(paren
(paren
id|hash_size
op_amp
(paren
id|hash_size
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_size
op_assign
id|hash_size
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_shift
op_assign
id|shift
suffix:semicolon
id|journal-&gt;j_revoke-&gt;hash_table
op_assign
id|kmalloc
c_func
(paren
id|hash_size
op_star
r_sizeof
(paren
r_struct
id|list_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|journal-&gt;j_revoke-&gt;hash_table
)paren
(brace
id|kfree
c_func
(paren
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
op_member_access_from_pointer
id|hash_table
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|journal-&gt;j_revoke
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|hash_size
suffix:semicolon
id|tmp
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|journal-&gt;j_revoke-&gt;hash_table
(braket
id|tmp
)braket
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Destoy a journal&squot;s revoke table.  The table must already be empty! */
DECL|function|journal_destroy_revoke
r_void
id|journal_destroy_revoke
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_struct
id|jbd_revoke_table_s
op_star
id|table
suffix:semicolon
r_struct
id|list_head
op_star
id|hash_list
suffix:semicolon
r_int
id|i
suffix:semicolon
id|table
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table
)paren
r_return
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
id|table-&gt;hash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hash_list
op_assign
op_amp
id|table-&gt;hash_table
(braket
id|i
)braket
suffix:semicolon
id|J_ASSERT
(paren
id|list_empty
c_func
(paren
id|hash_list
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|table-&gt;hash_table
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|table
)paren
suffix:semicolon
id|journal-&gt;j_revoke
op_assign
l_int|NULL
suffix:semicolon
id|table
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table
)paren
r_return
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
id|table-&gt;hash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hash_list
op_assign
op_amp
id|table-&gt;hash_table
(braket
id|i
)braket
suffix:semicolon
id|J_ASSERT
(paren
id|list_empty
c_func
(paren
id|hash_list
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|table-&gt;hash_table
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_table_cache
comma
id|table
)paren
suffix:semicolon
id|journal-&gt;j_revoke
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/* &n; * journal_revoke: revoke a given buffer_head from the journal.  This&n; * prevents the block from being replayed during recovery if we take a&n; * crash after this current transaction commits.  Any subsequent&n; * metadata writes of the buffer in this transaction cancel the&n; * revoke.  &n; *&n; * Note that this call may block --- it is up to the caller to make&n; * sure that there are no further calls to journal_write_metadata&n; * before the revoke is complete.  In ext3, this implies calling the&n; * revoke before clearing the block bitmap when we are deleting&n; * metadata. &n; *&n; * Revoke performs a journal_forget on any buffer_head passed in as a&n; * parameter, but does _not_ forget the buffer_head if the bh was only&n; * found implicitly. &n; *&n; * bh_in may not be a journalled buffer - it may have come off&n; * the hash tables without an attached journal_head.&n; *&n; * If bh_in is non-zero, journal_revoke() will decrement its b_count&n; * by one.&n; */
DECL|function|journal_revoke
r_int
id|journal_revoke
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_int
r_int
id|blocknr
comma
r_struct
id|buffer_head
op_star
id|bh_in
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|journal_t
op_star
id|journal
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh_in
)paren
id|BUFFER_TRACE
c_func
(paren
id|bh_in
comma
l_string|&quot;enter&quot;
)paren
suffix:semicolon
id|journal
op_assign
id|handle-&gt;h_transaction-&gt;t_journal
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|journal_set_features
c_func
(paren
id|journal
comma
l_int|0
comma
l_int|0
comma
id|JFS_FEATURE_INCOMPAT_REVOKE
)paren
)paren
(brace
id|J_ASSERT
(paren
op_logical_neg
l_string|&quot;Cannot set revoke feature!&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bdev
op_assign
id|journal-&gt;j_fs_dev
suffix:semicolon
id|bh
op_assign
id|bh_in
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|bh
op_assign
id|__find_get_block
c_func
(paren
id|bdev
comma
id|blocknr
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|BUFFER_TRACE
c_func
(paren
id|bh
comma
l_string|&quot;found on hash&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef JBD_EXPENSIVE_CHECKING
r_else
(brace
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
multiline_comment|/* If there is a different buffer_head lying around in&n;&t;&t; * memory anywhere... */
id|bh2
op_assign
id|__find_get_block
c_func
(paren
id|bdev
comma
id|blocknr
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh2
)paren
(brace
multiline_comment|/* ... and it has RevokeValid status... */
r_if
c_cond
(paren
id|bh2
op_ne
id|bh
op_logical_and
id|buffer_revokevalid
c_func
(paren
id|bh2
)paren
)paren
multiline_comment|/* ...then it better be revoked too,&n;&t;&t;&t;&t; * since it&squot;s illegal to create a revoke&n;&t;&t;&t;&t; * record against a buffer_head which is&n;&t;&t;&t;&t; * not marked revoked --- that would&n;&t;&t;&t;&t; * risk missing a subsequent revoke&n;&t;&t;&t;&t; * cancel. */
id|J_ASSERT_BH
c_func
(paren
id|bh2
comma
id|buffer_revoked
c_func
(paren
id|bh2
)paren
)paren
suffix:semicolon
id|put_bh
c_func
(paren
id|bh2
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* We really ought not ever to revoke twice in a row without&n;           first having the revoke cancelled: it&squot;s illegal to free a&n;           block twice without allocating it in between! */
r_if
c_cond
(paren
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|J_EXPECT_BH
c_func
(paren
id|bh
comma
op_logical_neg
id|buffer_revoked
c_func
(paren
id|bh
)paren
comma
l_string|&quot;inconsistent data on disk&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh_in
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|set_buffer_revoked
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_buffer_revokevalid
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh_in
)paren
(brace
id|BUFFER_TRACE
c_func
(paren
id|bh_in
comma
l_string|&quot;call journal_forget&quot;
)paren
suffix:semicolon
id|journal_forget
c_func
(paren
id|handle
comma
id|bh_in
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
l_string|&quot;call brelse&quot;
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
id|jbd_debug
c_func
(paren
l_int|2
comma
l_string|&quot;insert revoke for block %lu, bh_in=%p&bslash;n&quot;
comma
id|blocknr
comma
id|bh_in
)paren
suffix:semicolon
id|err
op_assign
id|insert_revoke_hash
c_func
(paren
id|journal
comma
id|blocknr
comma
id|handle-&gt;h_transaction-&gt;t_tid
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|bh_in
comma
l_string|&quot;exit&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Cancel an outstanding revoke.  For use only internally by the&n; * journaling code (called from journal_get_write_access).&n; *&n; * We trust buffer_revoked() on the buffer if the buffer is already&n; * being journaled: if there is no revoke pending on the buffer, then we&n; * don&squot;t do anything here.&n; *&n; * This would break if it were possible for a buffer to be revoked and&n; * discarded, and then reallocated within the same transaction.  In such&n; * a case we would have lost the revoked bit, but when we arrived here&n; * the second time we would still have a pending revoke to cancel.  So,&n; * do not trust the Revoked bit on buffers unless RevokeValid is also&n; * set.&n; *&n; * The caller must have the journal locked.&n; */
DECL|function|journal_cancel_revoke
r_int
id|journal_cancel_revoke
c_func
(paren
id|handle_t
op_star
id|handle
comma
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
id|journal_t
op_star
id|journal
op_assign
id|handle-&gt;h_transaction-&gt;t_journal
suffix:semicolon
r_int
id|need_cancel
suffix:semicolon
r_int
id|did_revoke
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* akpm: debug */
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
id|jbd_debug
c_func
(paren
l_int|4
comma
l_string|&quot;journal_head %p, cancelling revoke&bslash;n&quot;
comma
id|jh
)paren
suffix:semicolon
multiline_comment|/* Is the existing Revoke bit valid?  If so, we trust it, and&n;&t; * only perform the full cancel if the revoke bit is set.  If&n;&t; * not, we can&squot;t trust the revoke bit, and we need to do the&n;&t; * full search for a revoke record. */
r_if
c_cond
(paren
id|test_set_buffer_revokevalid
c_func
(paren
id|bh
)paren
)paren
(brace
id|need_cancel
op_assign
id|test_clear_buffer_revoked
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
(brace
id|need_cancel
op_assign
l_int|1
suffix:semicolon
id|clear_buffer_revoked
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|need_cancel
)paren
(brace
id|record
op_assign
id|find_revoke_record
c_func
(paren
id|journal
comma
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|record
)paren
(brace
id|jbd_debug
c_func
(paren
l_int|4
comma
l_string|&quot;cancelled existing revoke on &quot;
l_string|&quot;blocknr %llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|record-&gt;hash
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|journal-&gt;j_revoke_lock
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_record_cache
comma
id|record
)paren
suffix:semicolon
id|did_revoke
op_assign
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#ifdef JBD_EXPENSIVE_CHECKING
multiline_comment|/* There better not be one left behind by now! */
id|record
op_assign
id|find_revoke_record
c_func
(paren
id|journal
comma
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
id|J_ASSERT_JH
c_func
(paren
id|jh
comma
id|record
op_eq
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Finally, have we just cleared revoke on an unhashed&n;&t; * buffer_head?  If so, we&squot;d better make sure we clear the&n;&t; * revoked status on any hashed alias too, otherwise the revoke&n;&t; * state machine will get very upset later on. */
r_if
c_cond
(paren
id|need_cancel
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh2
suffix:semicolon
id|bh2
op_assign
id|__find_get_block
c_func
(paren
id|bh-&gt;b_bdev
comma
id|bh-&gt;b_blocknr
comma
id|bh-&gt;b_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh2
)paren
(brace
r_if
c_cond
(paren
id|bh2
op_ne
id|bh
)paren
id|clear_buffer_revoked
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|__brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
)brace
)brace
r_return
id|did_revoke
suffix:semicolon
)brace
multiline_comment|/* journal_switch_revoke table select j_revoke for next transaction&n; * we do not want to suspend any processing until all revokes are&n; * written -bzzz&n; */
DECL|function|journal_switch_revoke_table
r_void
id|journal_switch_revoke_table
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|journal-&gt;j_revoke
op_eq
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
)paren
id|journal-&gt;j_revoke
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|journal-&gt;j_revoke
op_assign
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
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
id|journal-&gt;j_revoke-&gt;hash_size
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|journal-&gt;j_revoke-&gt;hash_table
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write revoke records to the journal for all entries in the current&n; * revoke hash, deleting the entries as we go.&n; *&n; * Called with the journal lock held.&n; */
DECL|function|journal_write_revoke_records
r_void
id|journal_write_revoke_records
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
id|descriptor
suffix:semicolon
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
r_struct
id|jbd_revoke_table_s
op_star
id|revoke
suffix:semicolon
r_struct
id|list_head
op_star
id|hash_list
suffix:semicolon
r_int
id|i
comma
id|offset
comma
id|count
suffix:semicolon
id|descriptor
op_assign
l_int|NULL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* select revoke table for committing transaction */
id|revoke
op_assign
id|journal-&gt;j_revoke
op_eq
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
ques
c_cond
id|journal-&gt;j_revoke_table
(braket
l_int|1
)braket
suffix:colon
id|journal-&gt;j_revoke_table
(braket
l_int|0
)braket
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
id|revoke-&gt;hash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hash_list
op_assign
op_amp
id|revoke-&gt;hash_table
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|hash_list
)paren
)paren
(brace
id|record
op_assign
(paren
r_struct
id|jbd_revoke_record_s
op_star
)paren
id|hash_list-&gt;next
suffix:semicolon
id|write_one_revoke_record
c_func
(paren
id|journal
comma
id|transaction
comma
op_amp
id|descriptor
comma
op_amp
id|offset
comma
id|record
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|record-&gt;hash
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_record_cache
comma
id|record
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|descriptor
)paren
id|flush_descriptor
c_func
(paren
id|journal
comma
id|descriptor
comma
id|offset
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;Wrote %d revoke records&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Write out one revoke record.  We need to create a new descriptor&n; * block if the old one is full or if we have not already created one.  &n; */
DECL|function|write_one_revoke_record
r_static
r_void
id|write_one_revoke_record
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|transaction_t
op_star
id|transaction
comma
r_struct
id|journal_head
op_star
op_star
id|descriptorp
comma
r_int
op_star
id|offsetp
comma
r_struct
id|jbd_revoke_record_s
op_star
id|record
)paren
(brace
r_struct
id|journal_head
op_star
id|descriptor
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|journal_header_t
op_star
id|header
suffix:semicolon
multiline_comment|/* If we are already aborting, this all becomes a noop.  We&n;           still need to go round the loop in&n;           journal_write_revoke_records in order to free all of the&n;           revoke records: only the IO to the journal is omitted. */
r_if
c_cond
(paren
id|is_journal_aborted
c_func
(paren
id|journal
)paren
)paren
r_return
suffix:semicolon
id|descriptor
op_assign
op_star
id|descriptorp
suffix:semicolon
id|offset
op_assign
op_star
id|offsetp
suffix:semicolon
multiline_comment|/* Make sure we have a descriptor with space left for the record */
r_if
c_cond
(paren
id|descriptor
)paren
(brace
r_if
c_cond
(paren
id|offset
op_eq
id|journal-&gt;j_blocksize
)paren
(brace
id|flush_descriptor
c_func
(paren
id|journal
comma
id|descriptor
comma
id|offset
)paren
suffix:semicolon
id|descriptor
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|descriptor
)paren
(brace
id|descriptor
op_assign
id|journal_get_descriptor_buffer
c_func
(paren
id|journal
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|descriptor
)paren
r_return
suffix:semicolon
id|header
op_assign
(paren
id|journal_header_t
op_star
)paren
op_amp
id|jh2bh
c_func
(paren
id|descriptor
)paren
op_member_access_from_pointer
id|b_data
(braket
l_int|0
)braket
suffix:semicolon
id|header-&gt;h_magic
op_assign
id|cpu_to_be32
c_func
(paren
id|JFS_MAGIC_NUMBER
)paren
suffix:semicolon
id|header-&gt;h_blocktype
op_assign
id|cpu_to_be32
c_func
(paren
id|JFS_REVOKE_BLOCK
)paren
suffix:semicolon
id|header-&gt;h_sequence
op_assign
id|cpu_to_be32
c_func
(paren
id|transaction-&gt;t_tid
)paren
suffix:semicolon
multiline_comment|/* Record it so that we can wait for IO completion later */
id|JBUFFER_TRACE
c_func
(paren
id|descriptor
comma
l_string|&quot;file as BJ_LogCtl&quot;
)paren
suffix:semicolon
id|journal_file_buffer
c_func
(paren
id|descriptor
comma
id|transaction
comma
id|BJ_LogCtl
)paren
suffix:semicolon
id|offset
op_assign
r_sizeof
(paren
id|journal_revoke_header_t
)paren
suffix:semicolon
op_star
id|descriptorp
op_assign
id|descriptor
suffix:semicolon
)brace
op_star
(paren
(paren
id|__be32
op_star
)paren
(paren
op_amp
id|jh2bh
c_func
(paren
id|descriptor
)paren
op_member_access_from_pointer
id|b_data
(braket
id|offset
)braket
)paren
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|record-&gt;blocknr
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|4
suffix:semicolon
op_star
id|offsetp
op_assign
id|offset
suffix:semicolon
)brace
multiline_comment|/* &n; * Flush a revoke descriptor out to the journal.  If we are aborting,&n; * this is a noop; otherwise we are generating a buffer which needs to&n; * be waited for during commit, so it has to go onto the appropriate&n; * journal buffer list.&n; */
DECL|function|flush_descriptor
r_static
r_void
id|flush_descriptor
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_struct
id|journal_head
op_star
id|descriptor
comma
r_int
id|offset
)paren
(brace
id|journal_revoke_header_t
op_star
id|header
suffix:semicolon
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
id|put_bh
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|header
op_assign
(paren
id|journal_revoke_header_t
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
id|header-&gt;r_count
op_assign
id|cpu_to_be32
c_func
(paren
id|offset
)paren
suffix:semicolon
id|set_buffer_jwrite
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
l_string|&quot;write&quot;
)paren
suffix:semicolon
id|set_buffer_dirty
c_func
(paren
id|bh
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
)brace
macro_line|#endif
multiline_comment|/* &n; * Revoke support for recovery.&n; *&n; * Recovery needs to be able to:&n; *&n; *  record all revoke records, including the tid of the latest instance&n; *  of each revoke in the journal&n; *&n; *  check whether a given block in a given transaction should be replayed&n; *  (ie. has not been revoked by a revoke record in that or a subsequent&n; *  transaction)&n; * &n; *  empty the revoke table after recovery.&n; */
multiline_comment|/*&n; * First, setting revoke records.  We create a new revoke record for&n; * every block ever revoked in the log as we scan it for recovery, and&n; * we update the existing records if we find multiple revokes for a&n; * single block. &n; */
DECL|function|journal_set_revoke
r_int
id|journal_set_revoke
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|blocknr
comma
id|tid_t
id|sequence
)paren
(brace
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
id|record
op_assign
id|find_revoke_record
c_func
(paren
id|journal
comma
id|blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|record
)paren
(brace
multiline_comment|/* If we have multiple occurrences, only record the&n;&t;&t; * latest sequence number in the hashed record */
r_if
c_cond
(paren
id|tid_gt
c_func
(paren
id|sequence
comma
id|record-&gt;sequence
)paren
)paren
id|record-&gt;sequence
op_assign
id|sequence
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|insert_revoke_hash
c_func
(paren
id|journal
comma
id|blocknr
comma
id|sequence
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Test revoke records.  For a given block referenced in the log, has&n; * that block been revoked?  A revoke record with a given transaction&n; * sequence number revokes all blocks in that transaction and earlier&n; * ones, but later transactions still need replayed.&n; */
DECL|function|journal_test_revoke
r_int
id|journal_test_revoke
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|blocknr
comma
id|tid_t
id|sequence
)paren
(brace
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
id|record
op_assign
id|find_revoke_record
c_func
(paren
id|journal
comma
id|blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|record
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tid_gt
c_func
(paren
id|sequence
comma
id|record-&gt;sequence
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Finally, once recovery is over, we need to clear the revoke table so&n; * that it can be reused by the running filesystem.&n; */
DECL|function|journal_clear_revoke
r_void
id|journal_clear_revoke
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|hash_list
suffix:semicolon
r_struct
id|jbd_revoke_record_s
op_star
id|record
suffix:semicolon
r_struct
id|jbd_revoke_table_s
op_star
id|revoke
suffix:semicolon
id|revoke
op_assign
id|journal-&gt;j_revoke
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
id|revoke-&gt;hash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hash_list
op_assign
op_amp
id|revoke-&gt;hash_table
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|hash_list
)paren
)paren
(brace
id|record
op_assign
(paren
r_struct
id|jbd_revoke_record_s
op_star
)paren
id|hash_list-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|record-&gt;hash
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|revoke_record_cache
comma
id|record
)paren
suffix:semicolon
)brace
)brace
)brace
eof
