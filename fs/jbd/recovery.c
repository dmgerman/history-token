multiline_comment|/*&n; * linux/fs/recovery.c&n; * &n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;, 1999&n; *&n; * Copyright 1999-2000 Red Hat Software --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Journal recovery routines for the generic filesystem journaling code;&n; * part of the ext2fs journaling system.  &n; */
macro_line|#ifndef __KERNEL__
macro_line|#include &quot;jfs_user.h&quot;
macro_line|#else
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/jbd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Maintain information about the progress of the recovery job, so that&n; * the different passes can carry information between them. &n; */
DECL|struct|recovery_info
r_struct
id|recovery_info
(brace
DECL|member|start_transaction
id|tid_t
id|start_transaction
suffix:semicolon
DECL|member|end_transaction
id|tid_t
id|end_transaction
suffix:semicolon
DECL|member|nr_replays
r_int
id|nr_replays
suffix:semicolon
DECL|member|nr_revokes
r_int
id|nr_revokes
suffix:semicolon
DECL|member|nr_revoke_hits
r_int
id|nr_revoke_hits
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|passtype
DECL|enumerator|PASS_SCAN
DECL|enumerator|PASS_REVOKE
DECL|enumerator|PASS_REPLAY
r_enum
id|passtype
(brace
id|PASS_SCAN
comma
id|PASS_REVOKE
comma
id|PASS_REPLAY
)brace
suffix:semicolon
r_static
r_int
id|do_one_pass
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_struct
id|recovery_info
op_star
id|info
comma
r_enum
id|passtype
id|pass
)paren
suffix:semicolon
r_static
r_int
id|scan_revoke_records
c_func
(paren
id|journal_t
op_star
comma
r_struct
id|buffer_head
op_star
comma
id|tid_t
comma
r_struct
id|recovery_info
op_star
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Release readahead buffers after use */
DECL|function|journal_brelse_array
r_void
id|journal_brelse_array
c_func
(paren
r_struct
id|buffer_head
op_star
id|b
(braket
)braket
comma
r_int
id|n
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|n
op_ge
l_int|0
)paren
id|brelse
(paren
id|b
(braket
id|n
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * When reading from the journal, we are going through the block device&n; * layer directly and so there is no readahead being done for us.  We&n; * need to implement any readahead ourselves if we want it to happen at&n; * all.  Recovery is basically one long sequential read, so make sure we&n; * do the IO in reasonably large chunks.&n; *&n; * This is not so critical that we need to be enormously clever about&n; * the readahead size, though.  128K is a purely arbitrary, good-enough&n; * fixed value.&n; */
DECL|macro|MAXBUF
mdefine_line|#define MAXBUF 8
DECL|function|do_readahead
r_static
r_int
id|do_readahead
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|start
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|max
comma
id|nbufs
comma
id|next
suffix:semicolon
r_int
r_int
id|blocknr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bufs
(braket
id|MAXBUF
)braket
suffix:semicolon
multiline_comment|/* Do up to 128K of readahead */
id|max
op_assign
id|start
op_plus
(paren
l_int|128
op_star
l_int|1024
op_div
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max
OG
id|journal-&gt;j_maxlen
)paren
id|max
op_assign
id|journal-&gt;j_maxlen
suffix:semicolon
multiline_comment|/* Do the readahead itself.  We&squot;ll submit MAXBUF buffer_heads at&n;&t; * a time to the block device IO layer. */
id|nbufs
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|start
suffix:semicolon
id|next
OL
id|max
suffix:semicolon
id|next
op_increment
)paren
(brace
id|err
op_assign
id|journal_bmap
c_func
(paren
id|journal
comma
id|next
comma
op_amp
id|blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;JBD: bad block at offset %u&bslash;n&quot;
comma
id|next
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|bh
op_assign
id|__getblk
c_func
(paren
id|journal-&gt;j_dev
comma
id|blocknr
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
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
)paren
(brace
id|bufs
(braket
id|nbufs
op_increment
)braket
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|nbufs
op_eq
id|MAXBUF
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
id|nbufs
comma
id|bufs
)paren
suffix:semicolon
id|journal_brelse_array
c_func
(paren
id|bufs
comma
id|nbufs
)paren
suffix:semicolon
id|nbufs
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nbufs
)paren
id|ll_rw_block
c_func
(paren
id|READ
comma
id|nbufs
comma
id|bufs
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|failed
suffix:colon
r_if
c_cond
(paren
id|nbufs
)paren
id|journal_brelse_array
c_func
(paren
id|bufs
comma
id|nbufs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Read a block from the journal&n; */
DECL|function|jread
r_static
r_int
id|jread
c_func
(paren
r_struct
id|buffer_head
op_star
op_star
id|bhp
comma
id|journal_t
op_star
id|journal
comma
r_int
r_int
id|offset
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|blocknr
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
op_star
id|bhp
op_assign
l_int|NULL
suffix:semicolon
id|J_ASSERT
(paren
id|offset
OL
id|journal-&gt;j_maxlen
)paren
suffix:semicolon
id|err
op_assign
id|journal_bmap
c_func
(paren
id|journal
comma
id|offset
comma
op_amp
id|blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;JBD: bad block at offset %u&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|bh
op_assign
id|__getblk
c_func
(paren
id|journal-&gt;j_dev
comma
id|blocknr
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
multiline_comment|/* If this is a brand new buffer, start readahead.&n;                   Otherwise, we assume we are already reading it.  */
r_if
c_cond
(paren
op_logical_neg
id|buffer_req
c_func
(paren
id|bh
)paren
)paren
id|do_readahead
c_func
(paren
id|journal
comma
id|offset
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;JBD: Failed to read block at offset %u&bslash;n&quot;
comma
id|offset
)paren
suffix:semicolon
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
op_star
id|bhp
op_assign
id|bh
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Count the number of in-use tags in a journal descriptor block.&n; */
DECL|function|count_tags
r_static
r_int
id|count_tags
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|size
)paren
(brace
r_char
op_star
id|tagp
suffix:semicolon
id|journal_block_tag_t
op_star
id|tag
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
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
r_while
c_loop
(paren
(paren
id|tagp
op_minus
id|bh-&gt;b_data
op_plus
r_sizeof
(paren
id|journal_block_tag_t
)paren
)paren
op_le
id|size
)paren
(brace
id|tag
op_assign
(paren
id|journal_block_tag_t
op_star
)paren
id|tagp
suffix:semicolon
id|nr
op_increment
suffix:semicolon
id|tagp
op_add_assign
r_sizeof
(paren
id|journal_block_tag_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tag-&gt;t_flags
op_amp
id|htonl
c_func
(paren
id|JFS_FLAG_SAME_UUID
)paren
)paren
)paren
id|tagp
op_add_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|tag-&gt;t_flags
op_amp
id|htonl
c_func
(paren
id|JFS_FLAG_LAST_TAG
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/* Make sure we wrap around the log correctly! */
DECL|macro|wrap
mdefine_line|#define wrap(journal, var)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (var &gt;= (journal)-&gt;j_last)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;var -= ((journal)-&gt;j_last - (journal)-&gt;j_first);&t;&bslash;&n;} while (0)
multiline_comment|/**&n; * int journal_recover(journal_t *journal) - recovers a on-disk journal&n; * @journal: the journal to recover&n; * &n; * The primary function for recovering the log contents when mounting a&n; * journaled device.  &n; *&n; * Recovery is done in three passes.  In the first pass, we look for the&n; * end of the log.  In the second, we assemble the list of revoke&n; * blocks.  In the third and final pass, we replay any un-revoked blocks&n; * in the log.  &n; */
DECL|function|journal_recover
r_int
id|journal_recover
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_int
id|err
suffix:semicolon
id|journal_superblock_t
op_star
id|sb
suffix:semicolon
r_struct
id|recovery_info
id|info
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|sb
op_assign
id|journal-&gt;j_superblock
suffix:semicolon
multiline_comment|/* &n;&t; * The journal superblock&squot;s s_start field (the current log head)&n;&t; * is always zero if, and only if, the journal was cleanly&n;&t; * unmounted.  &n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_start
)paren
(brace
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;No recovery required, last transaction %d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|sb-&gt;s_sequence
)paren
)paren
suffix:semicolon
id|journal-&gt;j_transaction_sequence
op_assign
id|ntohl
c_func
(paren
id|sb-&gt;s_sequence
)paren
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|err
op_assign
id|do_one_pass
c_func
(paren
id|journal
comma
op_amp
id|info
comma
id|PASS_SCAN
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|do_one_pass
c_func
(paren
id|journal
comma
op_amp
id|info
comma
id|PASS_REVOKE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|do_one_pass
c_func
(paren
id|journal
comma
op_amp
id|info
comma
id|PASS_REPLAY
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|0
comma
l_string|&quot;JBD: recovery, exit status %d, &quot;
l_string|&quot;recovered transactions %u to %u&bslash;n&quot;
comma
id|err
comma
id|info.start_transaction
comma
id|info.end_transaction
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|0
comma
l_string|&quot;JBD: Replayed %d and revoked %d/%d blocks&bslash;n&quot;
comma
id|info.nr_replays
comma
id|info.nr_revoke_hits
comma
id|info.nr_revokes
)paren
suffix:semicolon
multiline_comment|/* Restart the log at the next transaction ID, thus invalidating&n;&t; * any existing commit records in the log. */
id|journal-&gt;j_transaction_sequence
op_assign
op_increment
id|info.end_transaction
suffix:semicolon
id|journal_clear_revoke
c_func
(paren
id|journal
)paren
suffix:semicolon
id|sync_blockdev
c_func
(paren
id|journal-&gt;j_fs_dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/**&n; * int journal_skip_recovery() - Start journal and wipe exiting records &n; * @journal: journal to startup&n; * &n; * Locate any valid recovery information from the journal and set up the&n; * journal structures in memory to ignore it (presumably because the&n; * caller has evidence that it is out of date).  &n; * This function does&squot;nt appear to be exorted..&n; *&n; * We perform one pass over the journal to allow us to tell the user how&n; * much recovery information is being erased, and to let us initialise&n; * the journal transaction sequence numbers to the next unused ID. &n; */
DECL|function|journal_skip_recovery
r_int
id|journal_skip_recovery
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_int
id|err
suffix:semicolon
id|journal_superblock_t
op_star
id|sb
suffix:semicolon
r_struct
id|recovery_info
id|info
suffix:semicolon
id|memset
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|sb
op_assign
id|journal-&gt;j_superblock
suffix:semicolon
id|err
op_assign
id|do_one_pass
c_func
(paren
id|journal
comma
op_amp
id|info
comma
id|PASS_SCAN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JBD: error %d scanning journal&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
op_increment
id|journal-&gt;j_transaction_sequence
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef CONFIG_JBD_DEBUG
r_int
id|dropped
op_assign
id|info.end_transaction
op_minus
id|ntohl
c_func
(paren
id|sb-&gt;s_sequence
)paren
suffix:semicolon
macro_line|#endif
id|jbd_debug
c_func
(paren
l_int|0
comma
l_string|&quot;JBD: ignoring %d transaction%s from the journal.&bslash;n&quot;
comma
id|dropped
comma
(paren
id|dropped
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|journal-&gt;j_transaction_sequence
op_assign
op_increment
id|info.end_transaction
suffix:semicolon
)brace
id|journal-&gt;j_tail
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|do_one_pass
r_static
r_int
id|do_one_pass
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_struct
id|recovery_info
op_star
id|info
comma
r_enum
id|passtype
id|pass
)paren
(brace
r_int
r_int
id|first_commit_ID
comma
id|next_commit_ID
suffix:semicolon
r_int
r_int
id|next_log_block
suffix:semicolon
r_int
id|err
comma
id|success
op_assign
l_int|0
suffix:semicolon
id|journal_superblock_t
op_star
id|sb
suffix:semicolon
id|journal_header_t
op_star
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
r_int
id|sequence
suffix:semicolon
r_int
id|blocktype
suffix:semicolon
multiline_comment|/* Precompute the maximum metadata descriptors in a descriptor block */
r_int
id|MAX_BLOCKS_PER_DESC
suffix:semicolon
id|MAX_BLOCKS_PER_DESC
op_assign
(paren
(paren
id|journal-&gt;j_blocksize
op_minus
r_sizeof
(paren
id|journal_header_t
)paren
)paren
op_div
r_sizeof
(paren
id|journal_block_tag_t
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * First thing is to establish what we expect to find in the log&n;&t; * (in terms of transaction IDs), and where (in terms of log&n;&t; * block offsets): query the superblock.  &n;&t; */
id|sb
op_assign
id|journal-&gt;j_superblock
suffix:semicolon
id|next_commit_ID
op_assign
id|ntohl
c_func
(paren
id|sb-&gt;s_sequence
)paren
suffix:semicolon
id|next_log_block
op_assign
id|ntohl
c_func
(paren
id|sb-&gt;s_start
)paren
suffix:semicolon
id|first_commit_ID
op_assign
id|next_commit_ID
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
id|PASS_SCAN
)paren
id|info-&gt;start_transaction
op_assign
id|first_commit_ID
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|1
comma
l_string|&quot;Starting recovery pass %d&bslash;n&quot;
comma
id|pass
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now we walk through the log, transaction by transaction,&n;&t; * making sure that each transaction has a commit block in the&n;&t; * expected place.  Each complete transaction gets replayed back&n;&t; * into the main filesystem. &n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|flags
suffix:semicolon
r_char
op_star
id|tagp
suffix:semicolon
id|journal_block_tag_t
op_star
id|tag
suffix:semicolon
r_struct
id|buffer_head
op_star
id|obh
suffix:semicolon
r_struct
id|buffer_head
op_star
id|nbh
suffix:semicolon
multiline_comment|/* If we already know where to stop the log traversal,&n;&t;&t; * check right now that we haven&squot;t gone past the end of&n;&t;&t; * the log. */
r_if
c_cond
(paren
id|pass
op_ne
id|PASS_SCAN
)paren
r_if
c_cond
(paren
id|tid_geq
c_func
(paren
id|next_commit_ID
comma
id|info-&gt;end_transaction
)paren
)paren
r_break
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|2
comma
l_string|&quot;Scanning for sequence ID %u at %lu/%lu&bslash;n&quot;
comma
id|next_commit_ID
comma
id|next_log_block
comma
id|journal-&gt;j_last
)paren
suffix:semicolon
multiline_comment|/* Skip over each chunk of the transaction looking&n;&t;&t; * either the next descriptor block or the final commit&n;&t;&t; * record. */
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;JBD: checking block %ld&bslash;n&quot;
comma
id|next_log_block
)paren
suffix:semicolon
id|err
op_assign
id|jread
c_func
(paren
op_amp
id|bh
comma
id|journal
comma
id|next_log_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|failed
suffix:semicolon
id|next_log_block
op_increment
suffix:semicolon
id|wrap
c_func
(paren
id|journal
comma
id|next_log_block
)paren
suffix:semicolon
multiline_comment|/* What kind of buffer is it? &n;&t;&t; * &n;&t;&t; * If it is a descriptor block, check that it has the&n;&t;&t; * expected sequence number.  Otherwise, we&squot;re all done&n;&t;&t; * here. */
id|tmp
op_assign
(paren
id|journal_header_t
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;h_magic
op_ne
id|htonl
c_func
(paren
id|JFS_MAGIC_NUMBER
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|blocktype
op_assign
id|ntohl
c_func
(paren
id|tmp-&gt;h_blocktype
)paren
suffix:semicolon
id|sequence
op_assign
id|ntohl
c_func
(paren
id|tmp-&gt;h_sequence
)paren
suffix:semicolon
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;Found magic %d, sequence %d&bslash;n&quot;
comma
id|blocktype
comma
id|sequence
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sequence
op_ne
id|next_commit_ID
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* OK, we have a valid descriptor block which matches&n;&t;&t; * all of the sequence number checks.  What are we going&n;&t;&t; * to do with it?  That depends on the pass... */
r_switch
c_cond
(paren
id|blocktype
)paren
(brace
r_case
id|JFS_DESCRIPTOR_BLOCK
suffix:colon
multiline_comment|/* If it is a valid descriptor block, replay it&n;&t;&t;&t; * in pass REPLAY; otherwise, just skip over the&n;&t;&t;&t; * blocks it describes. */
r_if
c_cond
(paren
id|pass
op_ne
id|PASS_REPLAY
)paren
(brace
id|next_log_block
op_add_assign
id|count_tags
c_func
(paren
id|bh
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
id|wrap
c_func
(paren
id|journal
comma
id|next_log_block
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* A descriptor block: we can now write all of&n;&t;&t;&t; * the data blocks.  Yay, useful work is finally&n;&t;&t;&t; * getting done here! */
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
r_while
c_loop
(paren
(paren
id|tagp
op_minus
id|bh-&gt;b_data
op_plus
r_sizeof
(paren
id|journal_block_tag_t
)paren
)paren
op_le
id|journal-&gt;j_blocksize
)paren
(brace
r_int
r_int
id|io_block
suffix:semicolon
id|tag
op_assign
(paren
id|journal_block_tag_t
op_star
)paren
id|tagp
suffix:semicolon
id|flags
op_assign
id|ntohl
c_func
(paren
id|tag-&gt;t_flags
)paren
suffix:semicolon
id|io_block
op_assign
id|next_log_block
op_increment
suffix:semicolon
id|wrap
c_func
(paren
id|journal
comma
id|next_log_block
)paren
suffix:semicolon
id|err
op_assign
id|jread
c_func
(paren
op_amp
id|obh
comma
id|journal
comma
id|io_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
multiline_comment|/* Recover what we can, but&n;&t;&t;&t;&t;&t; * report failure at the end. */
id|success
op_assign
id|err
suffix:semicolon
id|printk
(paren
id|KERN_ERR
l_string|&quot;JBD: IO error %d recovering &quot;
l_string|&quot;block %ld in log&bslash;n&quot;
comma
id|err
comma
id|io_block
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|blocknr
suffix:semicolon
id|J_ASSERT
c_func
(paren
id|obh
op_ne
l_int|NULL
)paren
suffix:semicolon
id|blocknr
op_assign
id|ntohl
c_func
(paren
id|tag-&gt;t_blocknr
)paren
suffix:semicolon
multiline_comment|/* If the block has been&n;&t;&t;&t;&t;&t; * revoked, then we&squot;re all done&n;&t;&t;&t;&t;&t; * here. */
r_if
c_cond
(paren
id|journal_test_revoke
(paren
id|journal
comma
id|blocknr
comma
id|next_commit_ID
)paren
)paren
(brace
id|brelse
c_func
(paren
id|obh
)paren
suffix:semicolon
op_increment
id|info-&gt;nr_revoke_hits
suffix:semicolon
r_goto
id|skip_write
suffix:semicolon
)brace
multiline_comment|/* Find a buffer for the new&n;&t;&t;&t;&t;&t; * data being restored */
id|nbh
op_assign
id|__getblk
c_func
(paren
id|journal-&gt;j_fs_dev
comma
id|blocknr
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JBD: Out of memory &quot;
l_string|&quot;during recovery.&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|obh
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|lock_buffer
c_func
(paren
id|nbh
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|nbh-&gt;b_data
comma
id|obh-&gt;b_data
comma
id|journal-&gt;j_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|JFS_FLAG_ESCAPE
)paren
(brace
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|bh-&gt;b_data
)paren
op_assign
id|htonl
c_func
(paren
id|JFS_MAGIC_NUMBER
)paren
suffix:semicolon
)brace
id|BUFFER_TRACE
c_func
(paren
id|nbh
comma
l_string|&quot;marking dirty&quot;
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|nbh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|nbh
)paren
suffix:semicolon
id|BUFFER_TRACE
c_func
(paren
id|nbh
comma
l_string|&quot;marking uptodate&quot;
)paren
suffix:semicolon
op_increment
id|info-&gt;nr_replays
suffix:semicolon
multiline_comment|/* ll_rw_block(WRITE, 1, &amp;nbh); */
id|unlock_buffer
c_func
(paren
id|nbh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|obh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|nbh
)paren
suffix:semicolon
)brace
id|skip_write
suffix:colon
id|tagp
op_add_assign
r_sizeof
(paren
id|journal_block_tag_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|JFS_FLAG_SAME_UUID
)paren
)paren
id|tagp
op_add_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|JFS_FLAG_LAST_TAG
)paren
r_break
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|JFS_COMMIT_BLOCK
suffix:colon
multiline_comment|/* Found an expected commit block: not much to&n;&t;&t;&t; * do other than move on to the next sequence&n;&t;&t;&t; * number. */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|next_commit_ID
op_increment
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|JFS_REVOKE_BLOCK
suffix:colon
multiline_comment|/* If we aren&squot;t in the REVOKE pass, then we can&n;&t;&t;&t; * just skip over this block. */
r_if
c_cond
(paren
id|pass
op_ne
id|PASS_REVOKE
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|err
op_assign
id|scan_revoke_records
c_func
(paren
id|journal
comma
id|bh
comma
id|next_commit_ID
comma
id|info
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|failed
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|jbd_debug
c_func
(paren
l_int|3
comma
l_string|&quot;Unrecognised magic %d, end of scan.&bslash;n&quot;
comma
id|blocktype
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|done
suffix:colon
multiline_comment|/* &n;&t; * We broke out of the log scan loop: either we came to the&n;&t; * known end of the log or we found an unexpected block in the&n;&t; * log.  If the latter happened, then we know that the &quot;current&quot;&n;&t; * transaction marks the end of the valid log.&n;&t; */
r_if
c_cond
(paren
id|pass
op_eq
id|PASS_SCAN
)paren
id|info-&gt;end_transaction
op_assign
id|next_commit_ID
suffix:semicolon
r_else
(brace
multiline_comment|/* It&squot;s really bad news if different passes end up at&n;&t;&t; * different places (but possible due to IO errors). */
r_if
c_cond
(paren
id|info-&gt;end_transaction
op_ne
id|next_commit_ID
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;JBD: recovery pass %d ended at &quot;
l_string|&quot;transaction %u, expected %u&bslash;n&quot;
comma
id|pass
comma
id|next_commit_ID
comma
id|info-&gt;end_transaction
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|success
)paren
id|success
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
id|success
suffix:semicolon
id|failed
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Scan a revoke record, marking all blocks mentioned as revoked. */
DECL|function|scan_revoke_records
r_static
r_int
id|scan_revoke_records
c_func
(paren
id|journal_t
op_star
id|journal
comma
r_struct
id|buffer_head
op_star
id|bh
comma
id|tid_t
id|sequence
comma
r_struct
id|recovery_info
op_star
id|info
)paren
(brace
id|journal_revoke_header_t
op_star
id|header
suffix:semicolon
r_int
id|offset
comma
id|max
suffix:semicolon
id|header
op_assign
(paren
id|journal_revoke_header_t
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|offset
op_assign
r_sizeof
(paren
id|journal_revoke_header_t
)paren
suffix:semicolon
id|max
op_assign
id|ntohl
c_func
(paren
id|header-&gt;r_count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|max
)paren
(brace
r_int
r_int
id|blocknr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|blocknr
op_assign
id|ntohl
c_func
(paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
)paren
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|4
suffix:semicolon
id|err
op_assign
id|journal_set_revoke
c_func
(paren
id|journal
comma
id|blocknr
comma
id|sequence
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
op_increment
id|info-&gt;nr_revokes
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
