multiline_comment|/*&n; * linux/include/linux/jbd.h&n; * &n; * Written by Stephen C. Tweedie &lt;sct@redhat.com&gt;&n; *&n; * Copyright 1998-2000 Red Hat, Inc --- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * Definitions for transaction data structures for the buffer cache&n; * filesystem journaling support.&n; */
macro_line|#ifndef _LINUX_JBD_H
DECL|macro|_LINUX_JBD_H
mdefine_line|#define _LINUX_JBD_H
macro_line|#if defined(CONFIG_JBD) || defined(CONFIG_JBD_MODULE) || !defined(__KERNEL__)
multiline_comment|/* Allow this file to be included directly into e2fsprogs */
macro_line|#ifndef __KERNEL__
macro_line|#include &quot;jfs_compat.h&quot;
DECL|macro|JFS_DEBUG
mdefine_line|#define JFS_DEBUG
DECL|macro|jfs_debug
mdefine_line|#define jfs_debug jbd_debug
macro_line|#else
macro_line|#include &lt;linux/journal-head.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#endif
DECL|macro|journal_oom_retry
mdefine_line|#define journal_oom_retry 1
macro_line|#ifdef CONFIG_JBD_DEBUG
multiline_comment|/*&n; * Define JBD_EXPENSIVE_CHECKING to enable more expensive internal&n; * consistency checks.  By default we don&squot;t do this unless&n; * CONFIG_JBD_DEBUG is on.&n; */
DECL|macro|JBD_EXPENSIVE_CHECKING
mdefine_line|#define JBD_EXPENSIVE_CHECKING
r_extern
r_int
id|journal_enable_debug
suffix:semicolon
DECL|macro|jbd_debug
mdefine_line|#define jbd_debug(n, f, a...)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((n) &lt;= journal_enable_debug) {&t;&t;&t;&bslash;&n;&t;&t;&t;printk (KERN_DEBUG &quot;(%s, %d): %s: &quot;,&t;&t;&bslash;&n;&t;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__);&t;&bslash;&n;&t;&t;  &t;printk (f, ## a);&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|jbd_debug
mdefine_line|#define jbd_debug(f, a...)&t;/**/
macro_line|#endif
r_extern
r_void
op_star
id|__jbd_kmalloc
(paren
r_char
op_star
id|where
comma
r_int
id|size
comma
r_int
id|flags
comma
r_int
id|retry
)paren
suffix:semicolon
DECL|macro|jbd_kmalloc
mdefine_line|#define jbd_kmalloc(size, flags) &bslash;&n;&t;__jbd_kmalloc(__FUNCTION__, (size), (flags), journal_oom_retry)
DECL|macro|jbd_rep_kmalloc
mdefine_line|#define jbd_rep_kmalloc(size, flags) &bslash;&n;&t;__jbd_kmalloc(__FUNCTION__, (size), (flags), 1)
DECL|macro|JFS_MIN_JOURNAL_BLOCKS
mdefine_line|#define JFS_MIN_JOURNAL_BLOCKS 1024
macro_line|#ifdef __KERNEL__
DECL|typedef|handle_t
r_typedef
r_struct
id|handle_s
id|handle_t
suffix:semicolon
multiline_comment|/* Atomic operation type */
DECL|typedef|journal_t
r_typedef
r_struct
id|journal_s
id|journal_t
suffix:semicolon
multiline_comment|/* Journal control structure */
macro_line|#endif
multiline_comment|/*&n; * Internal structures used by the logging mechanism:&n; */
DECL|macro|JFS_MAGIC_NUMBER
mdefine_line|#define JFS_MAGIC_NUMBER 0xc03b3998U /* The first 4 bytes of /dev/random! */
multiline_comment|/*&n; * On-disk structures&n; */
multiline_comment|/* &n; * Descriptor block types:&n; */
DECL|macro|JFS_DESCRIPTOR_BLOCK
mdefine_line|#define JFS_DESCRIPTOR_BLOCK&t;1
DECL|macro|JFS_COMMIT_BLOCK
mdefine_line|#define JFS_COMMIT_BLOCK&t;2
DECL|macro|JFS_SUPERBLOCK_V1
mdefine_line|#define JFS_SUPERBLOCK_V1&t;3
DECL|macro|JFS_SUPERBLOCK_V2
mdefine_line|#define JFS_SUPERBLOCK_V2&t;4
DECL|macro|JFS_REVOKE_BLOCK
mdefine_line|#define JFS_REVOKE_BLOCK&t;5
multiline_comment|/*&n; * Standard header for all descriptor blocks:&n; */
DECL|struct|journal_header_s
r_typedef
r_struct
id|journal_header_s
(brace
DECL|member|h_magic
id|__u32
id|h_magic
suffix:semicolon
DECL|member|h_blocktype
id|__u32
id|h_blocktype
suffix:semicolon
DECL|member|h_sequence
id|__u32
id|h_sequence
suffix:semicolon
DECL|typedef|journal_header_t
)brace
id|journal_header_t
suffix:semicolon
multiline_comment|/* &n; * The block tag: used to describe a single buffer in the journal &n; */
DECL|struct|journal_block_tag_s
r_typedef
r_struct
id|journal_block_tag_s
(brace
DECL|member|t_blocknr
id|__u32
id|t_blocknr
suffix:semicolon
multiline_comment|/* The on-disk block number */
DECL|member|t_flags
id|__u32
id|t_flags
suffix:semicolon
multiline_comment|/* See below */
DECL|typedef|journal_block_tag_t
)brace
id|journal_block_tag_t
suffix:semicolon
multiline_comment|/* &n; * The revoke descriptor: used on disk to describe a series of blocks to&n; * be revoked from the log &n; */
DECL|struct|journal_revoke_header_s
r_typedef
r_struct
id|journal_revoke_header_s
(brace
DECL|member|r_header
id|journal_header_t
id|r_header
suffix:semicolon
DECL|member|r_count
r_int
id|r_count
suffix:semicolon
multiline_comment|/* Count of bytes used in the block */
DECL|typedef|journal_revoke_header_t
)brace
id|journal_revoke_header_t
suffix:semicolon
multiline_comment|/* Definitions for the journal tag flags word: */
DECL|macro|JFS_FLAG_ESCAPE
mdefine_line|#define JFS_FLAG_ESCAPE&t;&t;1&t;/* on-disk block is escaped */
DECL|macro|JFS_FLAG_SAME_UUID
mdefine_line|#define JFS_FLAG_SAME_UUID&t;2&t;/* block has same uuid as previous */
DECL|macro|JFS_FLAG_DELETED
mdefine_line|#define JFS_FLAG_DELETED&t;4&t;/* block deleted by this transaction */
DECL|macro|JFS_FLAG_LAST_TAG
mdefine_line|#define JFS_FLAG_LAST_TAG&t;8&t;/* last tag in this descriptor block */
multiline_comment|/*&n; * The journal superblock.  All fields are in big-endian byte order.&n; */
DECL|struct|journal_superblock_s
r_typedef
r_struct
id|journal_superblock_s
(brace
multiline_comment|/* 0x0000 */
DECL|member|s_header
id|journal_header_t
id|s_header
suffix:semicolon
multiline_comment|/* 0x000C */
multiline_comment|/* Static information describing the journal */
DECL|member|s_blocksize
id|__u32
id|s_blocksize
suffix:semicolon
multiline_comment|/* journal device blocksize */
DECL|member|s_maxlen
id|__u32
id|s_maxlen
suffix:semicolon
multiline_comment|/* total blocks in journal file */
DECL|member|s_first
id|__u32
id|s_first
suffix:semicolon
multiline_comment|/* first block of log information */
multiline_comment|/* 0x0018 */
multiline_comment|/* Dynamic information describing the current state of the log */
DECL|member|s_sequence
id|__u32
id|s_sequence
suffix:semicolon
multiline_comment|/* first commit ID expected in log */
DECL|member|s_start
id|__u32
id|s_start
suffix:semicolon
multiline_comment|/* blocknr of start of log */
multiline_comment|/* 0x0020 */
multiline_comment|/* Error value, as set by journal_abort(). */
DECL|member|s_errno
id|__s32
id|s_errno
suffix:semicolon
multiline_comment|/* 0x0024 */
multiline_comment|/* Remaining fields are only valid in a version-2 superblock */
DECL|member|s_feature_compat
id|__u32
id|s_feature_compat
suffix:semicolon
multiline_comment|/* compatible feature set */
DECL|member|s_feature_incompat
id|__u32
id|s_feature_incompat
suffix:semicolon
multiline_comment|/* incompatible feature set */
DECL|member|s_feature_ro_compat
id|__u32
id|s_feature_ro_compat
suffix:semicolon
multiline_comment|/* readonly-compatible feature set */
multiline_comment|/* 0x0030 */
DECL|member|s_uuid
id|__u8
id|s_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 128-bit uuid for journal */
multiline_comment|/* 0x0040 */
DECL|member|s_nr_users
id|__u32
id|s_nr_users
suffix:semicolon
multiline_comment|/* Nr of filesystems sharing log */
DECL|member|s_dynsuper
id|__u32
id|s_dynsuper
suffix:semicolon
multiline_comment|/* Blocknr of dynamic superblock copy*/
multiline_comment|/* 0x0048 */
DECL|member|s_max_transaction
id|__u32
id|s_max_transaction
suffix:semicolon
multiline_comment|/* Limit of journal blocks per trans.*/
DECL|member|s_max_trans_data
id|__u32
id|s_max_trans_data
suffix:semicolon
multiline_comment|/* Limit of data blocks per trans. */
multiline_comment|/* 0x0050 */
DECL|member|s_padding
id|__u32
id|s_padding
(braket
l_int|44
)braket
suffix:semicolon
multiline_comment|/* 0x0100 */
DECL|member|s_users
id|__u8
id|s_users
(braket
l_int|16
op_star
l_int|48
)braket
suffix:semicolon
multiline_comment|/* ids of all fs&squot;es sharing the log */
multiline_comment|/* 0x0400 */
DECL|typedef|journal_superblock_t
)brace
id|journal_superblock_t
suffix:semicolon
DECL|macro|JFS_HAS_COMPAT_FEATURE
mdefine_line|#define JFS_HAS_COMPAT_FEATURE(j,mask)&t;&t;&t;&t;&t;&bslash;&n;&t;((j)-&gt;j_format_version &gt;= 2 &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t; ((j)-&gt;j_superblock-&gt;s_feature_compat &amp; cpu_to_be32((mask))))
DECL|macro|JFS_HAS_RO_COMPAT_FEATURE
mdefine_line|#define JFS_HAS_RO_COMPAT_FEATURE(j,mask)&t;&t;&t;&t;&bslash;&n;&t;((j)-&gt;j_format_version &gt;= 2 &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t; ((j)-&gt;j_superblock-&gt;s_feature_ro_compat &amp; cpu_to_be32((mask))))
DECL|macro|JFS_HAS_INCOMPAT_FEATURE
mdefine_line|#define JFS_HAS_INCOMPAT_FEATURE(j,mask)&t;&t;&t;&t;&bslash;&n;&t;((j)-&gt;j_format_version &gt;= 2 &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t; ((j)-&gt;j_superblock-&gt;s_feature_incompat &amp; cpu_to_be32((mask))))
DECL|macro|JFS_FEATURE_INCOMPAT_REVOKE
mdefine_line|#define JFS_FEATURE_INCOMPAT_REVOKE&t;0x00000001
multiline_comment|/* Features known to this kernel version: */
DECL|macro|JFS_KNOWN_COMPAT_FEATURES
mdefine_line|#define JFS_KNOWN_COMPAT_FEATURES&t;0
DECL|macro|JFS_KNOWN_ROCOMPAT_FEATURES
mdefine_line|#define JFS_KNOWN_ROCOMPAT_FEATURES&t;0
DECL|macro|JFS_KNOWN_INCOMPAT_FEATURES
mdefine_line|#define JFS_KNOWN_INCOMPAT_FEATURES&t;JFS_FEATURE_INCOMPAT_REVOKE
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|JBD_ASSERTIONS
mdefine_line|#define JBD_ASSERTIONS
macro_line|#ifdef JBD_ASSERTIONS
DECL|macro|J_ASSERT
mdefine_line|#define J_ASSERT(assert)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(assert)) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk (KERN_EMERG&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;Assertion failure in %s() at %s:%d: &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;__FUNCTION__, __FILE__, __LINE__, # assert);&t;&bslash;&n;&t;&t;BUG();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#if defined(CONFIG_BUFFER_DEBUG)
r_void
id|buffer_assertion_failure
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
DECL|macro|J_ASSERT_BH
mdefine_line|#define J_ASSERT_BH(bh, expr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!(expr))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;buffer_assertion_failure(bh);&t;&t;&t;&bslash;&n;&t;&t;J_ASSERT(expr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|J_ASSERT_JH
mdefine_line|#define J_ASSERT_JH(jh, expr)&t;J_ASSERT_BH(jh2bh(jh), expr)
macro_line|#else
DECL|macro|J_ASSERT_BH
mdefine_line|#define J_ASSERT_BH(bh, expr)&t;J_ASSERT(expr)
DECL|macro|J_ASSERT_JH
mdefine_line|#define J_ASSERT_JH(jh, expr)&t;J_ASSERT(expr)
macro_line|#endif
macro_line|#else
DECL|macro|J_ASSERT
mdefine_line|#define J_ASSERT(assert)&t;do { } while (0)
macro_line|#endif&t;&t;/* JBD_ASSERTIONS */
DECL|enum|jbd_state_bits
r_enum
id|jbd_state_bits
(brace
DECL|enumerator|BH_JWrite
id|BH_JWrite
op_assign
id|BH_PrivateStart
comma
multiline_comment|/* 1 if being written to log (@@@ DEBUGGING) */
DECL|enumerator|BH_Freed
id|BH_Freed
comma
multiline_comment|/* 1 if buffer has been freed (truncated) */
DECL|enumerator|BH_Revoked
id|BH_Revoked
comma
multiline_comment|/* 1 if buffer has been revoked from the log */
DECL|enumerator|BH_RevokeValid
id|BH_RevokeValid
comma
multiline_comment|/* 1 if buffer revoked flag is valid */
DECL|enumerator|BH_JBDDirty
id|BH_JBDDirty
comma
multiline_comment|/* 1 if buffer is dirty but journaled */
)brace
suffix:semicolon
multiline_comment|/* Return true if the buffer is one which JBD is managing */
DECL|function|buffer_jbd
r_static
r_inline
r_int
id|buffer_jbd
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|__buffer_state
c_func
(paren
id|bh
comma
id|JBD
)paren
suffix:semicolon
)brace
DECL|function|jh2bh
r_static
r_inline
r_struct
id|buffer_head
op_star
id|jh2bh
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
(brace
r_return
id|jh-&gt;b_bh
suffix:semicolon
)brace
DECL|function|bh2jh
r_static
r_inline
r_struct
id|journal_head
op_star
id|bh2jh
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|bh-&gt;b_private
suffix:semicolon
)brace
r_struct
id|jbd_revoke_table_s
suffix:semicolon
multiline_comment|/* The handle_t type represents a single atomic update being performed&n; * by some process.  All filesystem modifications made by the process go&n; * through this handle.  Recursive operations (such as quota operations)&n; * are gathered into a single update.&n; *&n; * The buffer credits field is used to account for journaled buffers&n; * being modified by the running process.  To ensure that there is&n; * enough log space for all outstanding operations, we need to limit the&n; * number of outstanding buffers possible at any time.  When the&n; * operation completes, any buffer credits not used are credited back to&n; * the transaction, so that at all times we know how many buffers the&n; * outstanding updates on a transaction might possibly touch. */
DECL|struct|handle_s
r_struct
id|handle_s
(brace
multiline_comment|/* Which compound transaction is this update a part of? */
DECL|member|h_transaction
id|transaction_t
op_star
id|h_transaction
suffix:semicolon
multiline_comment|/* Number of remaining buffers we are allowed to dirty: */
DECL|member|h_buffer_credits
r_int
id|h_buffer_credits
suffix:semicolon
multiline_comment|/* Reference count on this handle */
DECL|member|h_ref
r_int
id|h_ref
suffix:semicolon
multiline_comment|/* Field for caller&squot;s use to track errors through large fs&n;&t;   operations */
DECL|member|h_err
r_int
id|h_err
suffix:semicolon
multiline_comment|/* Flags */
DECL|member|h_sync
r_int
r_int
id|h_sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* sync-on-close */
DECL|member|h_jdata
r_int
r_int
id|h_jdata
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* force data journaling */
DECL|member|h_aborted
r_int
r_int
id|h_aborted
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* fatal error on handle */
)brace
suffix:semicolon
multiline_comment|/* The transaction_t type is the guts of the journaling mechanism.  It&n; * tracks a compound transaction through its various states:&n; *&n; * RUNNING:&t;accepting new updates&n; * LOCKED:&t;Updates still running but we don&squot;t accept new ones&n; * RUNDOWN:&t;Updates are tidying up but have finished requesting&n; *&t;&t;new buffers to modify (state not used for now)&n; * FLUSH:       All updates complete, but we are still writing to disk&n; * COMMIT:      All data on disk, writing commit record&n; * FINISHED:&t;We still have to keep the transaction for checkpointing.&n; *&n; * The transaction keeps track of all of the buffers modified by a&n; * running transaction, and all of the buffers committed but not yet&n; * flushed to home for finished transactions.&n; */
DECL|struct|transaction_s
r_struct
id|transaction_s
(brace
multiline_comment|/* Pointer to the journal for this transaction. */
DECL|member|t_journal
id|journal_t
op_star
id|t_journal
suffix:semicolon
multiline_comment|/* Sequence number for this transaction */
DECL|member|t_tid
id|tid_t
id|t_tid
suffix:semicolon
multiline_comment|/* Transaction&squot;s current state */
r_enum
(brace
DECL|enumerator|T_RUNNING
id|T_RUNNING
comma
DECL|enumerator|T_LOCKED
id|T_LOCKED
comma
DECL|enumerator|T_RUNDOWN
id|T_RUNDOWN
comma
DECL|enumerator|T_FLUSH
id|T_FLUSH
comma
DECL|enumerator|T_COMMIT
id|T_COMMIT
comma
DECL|enumerator|T_FINISHED
id|T_FINISHED
DECL|member|t_state
)brace
id|t_state
suffix:semicolon
multiline_comment|/* Where in the log does this transaction&squot;s commit start? */
DECL|member|t_log_start
r_int
r_int
id|t_log_start
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of all inodes owned by this&n;           transaction */
multiline_comment|/* AKPM: unused */
DECL|member|t_ilist
r_struct
id|inode
op_star
id|t_ilist
suffix:semicolon
multiline_comment|/* Number of buffers on the t_buffers list */
DECL|member|t_nr_buffers
r_int
id|t_nr_buffers
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of all buffers reserved but not&n;           yet modified by this transaction */
DECL|member|t_reserved_list
r_struct
id|journal_head
op_star
id|t_reserved_list
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of all metadata buffers owned by this&n;           transaction */
DECL|member|t_buffers
r_struct
id|journal_head
op_star
id|t_buffers
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all data buffers still to be&n;&t; * flushed before this transaction can be committed.&n;&t; * Protected by journal_datalist_lock.&n;&t; */
DECL|member|t_sync_datalist
r_struct
id|journal_head
op_star
id|t_sync_datalist
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all writepage data buffers&n;&t; * still to be written before this transaction can be committed.&n;&t; * Protected by journal_datalist_lock.&n;&t; */
DECL|member|t_async_datalist
r_struct
id|journal_head
op_star
id|t_async_datalist
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of all forget buffers (superceded&n;           buffers which we can un-checkpoint once this transaction&n;           commits) */
DECL|member|t_forget
r_struct
id|journal_head
op_star
id|t_forget
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all buffers still to be&n;&t; * flushed before this transaction can be checkpointed.&n;&t; */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|t_checkpoint_list
r_struct
id|journal_head
op_star
id|t_checkpoint_list
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of temporary buffers currently&n;           undergoing IO in the log */
DECL|member|t_iobuf_list
r_struct
id|journal_head
op_star
id|t_iobuf_list
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of metadata buffers being&n;           shadowed by log IO.  The IO buffers on the iobuf list and the&n;           shadow buffers on this list match each other one for one at&n;           all times. */
DECL|member|t_shadow_list
r_struct
id|journal_head
op_star
id|t_shadow_list
suffix:semicolon
multiline_comment|/* Doubly-linked circular list of control buffers being written&n;           to the log. */
DECL|member|t_log_list
r_struct
id|journal_head
op_star
id|t_log_list
suffix:semicolon
multiline_comment|/* Number of outstanding updates running on this transaction */
DECL|member|t_updates
r_int
id|t_updates
suffix:semicolon
multiline_comment|/* Number of buffers reserved for use by all handles in this&n;&t; * transaction handle but not yet modified. */
DECL|member|t_outstanding_credits
r_int
id|t_outstanding_credits
suffix:semicolon
multiline_comment|/*&n;&t; * Forward and backward links for the circular list of all&n;&t; * transactions awaiting checkpoint.&n;&t; */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|t_cpnext
DECL|member|t_cpprev
id|transaction_t
op_star
id|t_cpnext
comma
op_star
id|t_cpprev
suffix:semicolon
multiline_comment|/* When will the transaction expire (become due for commit), in&n;&t; * jiffies ? */
DECL|member|t_expires
r_int
r_int
id|t_expires
suffix:semicolon
multiline_comment|/* How many handles used this transaction? */
DECL|member|t_handle_count
r_int
id|t_handle_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The journal_t maintains all of the journaling state information for a&n; * single filesystem.  It is linked to from the fs superblock structure.&n; * &n; * We use the journal_t to keep track of all outstanding transaction&n; * activity on the filesystem, and to manage the state of the log&n; * writing process. */
DECL|struct|journal_s
r_struct
id|journal_s
(brace
multiline_comment|/* General journaling state flags */
DECL|member|j_flags
r_int
r_int
id|j_flags
suffix:semicolon
multiline_comment|/* Is there an outstanding uncleared error on the journal (from&n;&t; * a prior abort)? */
DECL|member|j_errno
r_int
id|j_errno
suffix:semicolon
multiline_comment|/* The superblock buffer */
DECL|member|j_sb_buffer
r_struct
id|buffer_head
op_star
id|j_sb_buffer
suffix:semicolon
DECL|member|j_superblock
id|journal_superblock_t
op_star
id|j_superblock
suffix:semicolon
multiline_comment|/* Version of the superblock format */
DECL|member|j_format_version
r_int
id|j_format_version
suffix:semicolon
multiline_comment|/* Number of processes waiting to create a barrier lock */
DECL|member|j_barrier_count
r_int
id|j_barrier_count
suffix:semicolon
multiline_comment|/* The barrier lock itself */
DECL|member|j_barrier
r_struct
id|semaphore
id|j_barrier
suffix:semicolon
multiline_comment|/* Transactions: The current running transaction... */
DECL|member|j_running_transaction
id|transaction_t
op_star
id|j_running_transaction
suffix:semicolon
multiline_comment|/* ... the transaction we are pushing to disk ... */
DECL|member|j_committing_transaction
id|transaction_t
op_star
id|j_committing_transaction
suffix:semicolon
multiline_comment|/* ... and a linked circular list of all transactions waiting&n;&t; * for checkpointing. */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|j_checkpoint_transactions
id|transaction_t
op_star
id|j_checkpoint_transactions
suffix:semicolon
multiline_comment|/* Wait queue for waiting for a locked transaction to start&n;           committing, or for a barrier lock to be released */
DECL|member|j_wait_transaction_locked
id|wait_queue_head_t
id|j_wait_transaction_locked
suffix:semicolon
multiline_comment|/* Wait queue for waiting for checkpointing to complete */
DECL|member|j_wait_logspace
id|wait_queue_head_t
id|j_wait_logspace
suffix:semicolon
multiline_comment|/* Wait queue for waiting for commit to complete */
DECL|member|j_wait_done_commit
id|wait_queue_head_t
id|j_wait_done_commit
suffix:semicolon
multiline_comment|/* Wait queue to trigger checkpointing */
DECL|member|j_wait_checkpoint
id|wait_queue_head_t
id|j_wait_checkpoint
suffix:semicolon
multiline_comment|/* Wait queue to trigger commit */
DECL|member|j_wait_commit
id|wait_queue_head_t
id|j_wait_commit
suffix:semicolon
multiline_comment|/* Wait queue to wait for updates to complete */
DECL|member|j_wait_updates
id|wait_queue_head_t
id|j_wait_updates
suffix:semicolon
multiline_comment|/* Semaphore for locking against concurrent checkpoints */
DECL|member|j_checkpoint_sem
r_struct
id|semaphore
id|j_checkpoint_sem
suffix:semicolon
multiline_comment|/* The main journal lock, used by lock_journal() */
DECL|member|j_sem
r_struct
id|semaphore
id|j_sem
suffix:semicolon
multiline_comment|/* Journal head: identifies the first unused block in the journal. */
DECL|member|j_head
r_int
r_int
id|j_head
suffix:semicolon
multiline_comment|/* Journal tail: identifies the oldest still-used block in the&n;&t; * journal. */
DECL|member|j_tail
r_int
r_int
id|j_tail
suffix:semicolon
multiline_comment|/* Journal free: how many free blocks are there in the journal? */
DECL|member|j_free
r_int
r_int
id|j_free
suffix:semicolon
multiline_comment|/* Journal start and end: the block numbers of the first usable&n;&t; * block and one beyond the last usable block in the journal. */
DECL|member|j_first
DECL|member|j_last
r_int
r_int
id|j_first
comma
id|j_last
suffix:semicolon
multiline_comment|/* Device, blocksize and starting block offset for the location&n;&t; * where we store the journal. */
DECL|member|j_dev
id|kdev_t
id|j_dev
suffix:semicolon
DECL|member|j_blocksize
r_int
id|j_blocksize
suffix:semicolon
DECL|member|j_blk_offset
r_int
r_int
id|j_blk_offset
suffix:semicolon
multiline_comment|/* Device which holds the client fs.  For internal journal this&n;&t; * will be equal to j_dev. */
DECL|member|j_fs_dev
id|kdev_t
id|j_fs_dev
suffix:semicolon
multiline_comment|/* Total maximum capacity of the journal region on disk. */
DECL|member|j_maxlen
r_int
r_int
id|j_maxlen
suffix:semicolon
multiline_comment|/* Optional inode where we store the journal.  If present, all&n;&t; * journal block numbers are mapped into this inode via&n;&t; * bmap(). */
DECL|member|j_inode
r_struct
id|inode
op_star
id|j_inode
suffix:semicolon
multiline_comment|/* Sequence number of the oldest transaction in the log */
DECL|member|j_tail_sequence
id|tid_t
id|j_tail_sequence
suffix:semicolon
multiline_comment|/* Sequence number of the next transaction to grant */
DECL|member|j_transaction_sequence
id|tid_t
id|j_transaction_sequence
suffix:semicolon
multiline_comment|/* Sequence number of the most recently committed transaction */
DECL|member|j_commit_sequence
id|tid_t
id|j_commit_sequence
suffix:semicolon
multiline_comment|/* Sequence number of the most recent transaction wanting commit */
DECL|member|j_commit_request
id|tid_t
id|j_commit_request
suffix:semicolon
multiline_comment|/* Journal uuid: identifies the object (filesystem, LVM volume&n;&t; * etc) backed by this journal.  This will eventually be&n;&t; * replaced by an array of uuids, allowing us to index multiple&n;&t; * devices within a single journal and to perform atomic updates&n;&t; * across them.  */
DECL|member|j_uuid
id|__u8
id|j_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Pointer to the current commit thread for this journal */
DECL|member|j_task
r_struct
id|task_struct
op_star
id|j_task
suffix:semicolon
multiline_comment|/* Maximum number of metadata buffers to allow in a single&n;&t; * compound commit transaction */
DECL|member|j_max_transaction_buffers
r_int
id|j_max_transaction_buffers
suffix:semicolon
multiline_comment|/* What is the maximum transaction lifetime before we begin a&n;&t; * commit? */
DECL|member|j_commit_interval
r_int
r_int
id|j_commit_interval
suffix:semicolon
multiline_comment|/* The timer used to wakeup the commit thread: */
DECL|member|j_commit_timer
r_struct
id|timer_list
op_star
id|j_commit_timer
suffix:semicolon
DECL|member|j_commit_timer_active
r_int
id|j_commit_timer_active
suffix:semicolon
multiline_comment|/* Link all journals together - system-wide */
DECL|member|j_all_journals
r_struct
id|list_head
id|j_all_journals
suffix:semicolon
multiline_comment|/* The revoke table: maintains the list of revoked blocks in the&n;           current transaction. */
DECL|member|j_revoke
r_struct
id|jbd_revoke_table_s
op_star
id|j_revoke
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Journal flag definitions &n; */
DECL|macro|JFS_UNMOUNT
mdefine_line|#define JFS_UNMOUNT&t;0x001&t;/* Journal thread is being destroyed */
DECL|macro|JFS_ABORT
mdefine_line|#define JFS_ABORT&t;0x002&t;/* Journaling has been aborted for errors. */
DECL|macro|JFS_ACK_ERR
mdefine_line|#define JFS_ACK_ERR&t;0x004&t;/* The errno in the sb has been acked */
DECL|macro|JFS_FLUSHED
mdefine_line|#define JFS_FLUSHED&t;0x008&t;/* The journal superblock has been flushed */
DECL|macro|JFS_LOADED
mdefine_line|#define JFS_LOADED&t;0x010&t;/* The journal superblock has been loaded */
multiline_comment|/* &n; * Function declarations for the journaling transaction and buffer&n; * management&n; */
multiline_comment|/* Filing buffers */
r_extern
r_void
id|__journal_unfile_buffer
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_unfile_buffer
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__journal_refile_buffer
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_refile_buffer
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__journal_file_buffer
c_func
(paren
r_struct
id|journal_head
op_star
comma
id|transaction_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__journal_free_buffer
c_func
(paren
r_struct
id|journal_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|journal_file_buffer
c_func
(paren
r_struct
id|journal_head
op_star
comma
id|transaction_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__journal_clean_data_list
c_func
(paren
id|transaction_t
op_star
id|transaction
)paren
suffix:semicolon
multiline_comment|/* Log buffer allocation */
r_extern
r_struct
id|journal_head
op_star
id|journal_get_descriptor_buffer
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_int
id|journal_next_log_block
c_func
(paren
id|journal_t
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* Commit management */
r_extern
r_void
id|journal_commit_transaction
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Checkpoint list management */
r_int
id|__journal_clean_checkpoint_list
c_func
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
r_extern
r_void
id|journal_remove_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__journal_remove_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_insert_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
comma
id|transaction_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__journal_insert_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
comma
id|transaction_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Buffer IO */
r_extern
r_int
id|journal_write_metadata_buffer
c_func
(paren
id|transaction_t
op_star
id|transaction
comma
r_struct
id|journal_head
op_star
id|jh_in
comma
r_struct
id|journal_head
op_star
op_star
id|jh_out
comma
r_int
id|blocknr
)paren
suffix:semicolon
multiline_comment|/* Transaction locking */
r_extern
r_void
id|__wait_on_journal
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Journal locking.&n; *&n; * We need to lock the journal during transaction state changes so that&n; * nobody ever tries to take a handle on the running transaction while&n; * we are in the middle of moving it to the commit phase.  &n; *&n; * Note that the locking is completely interrupt unsafe.  We never touch&n; * journal structures from interrupts.&n; *&n; * In 2.2, the BKL was required for lock_journal.  This is no longer&n; * the case.&n; */
DECL|function|lock_journal
r_static
r_inline
r_void
id|lock_journal
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
id|down
c_func
(paren
op_amp
id|journal-&gt;j_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* This returns zero if we acquired the semaphore */
DECL|function|try_lock_journal
r_static
r_inline
r_int
id|try_lock_journal
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_return
id|down_trylock
c_func
(paren
op_amp
id|journal-&gt;j_sem
)paren
suffix:semicolon
)brace
DECL|function|unlock_journal
r_static
r_inline
r_void
id|unlock_journal
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
id|up
c_func
(paren
op_amp
id|journal-&gt;j_sem
)paren
suffix:semicolon
)brace
DECL|function|journal_current_handle
r_static
r_inline
id|handle_t
op_star
id|journal_current_handle
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;journal_info
suffix:semicolon
)brace
multiline_comment|/* The journaling code user interface:&n; *&n; * Create and destroy handles&n; * Register buffer modifications against the current transaction. &n; */
r_extern
id|handle_t
op_star
id|journal_start
c_func
(paren
id|journal_t
op_star
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
id|handle_t
op_star
id|journal_try_start
c_func
(paren
id|journal_t
op_star
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|journal_restart
(paren
id|handle_t
op_star
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|journal_extend
(paren
id|handle_t
op_star
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|journal_get_write_access
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_get_create_access
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_get_undo_access
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_dirty_data
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
id|async
)paren
suffix:semicolon
r_extern
r_int
id|journal_dirty_metadata
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_release_buffer
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_forget
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_sync_buffer
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_flushpage
c_func
(paren
id|journal_t
op_star
comma
r_struct
id|page
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_try_to_free_buffers
c_func
(paren
id|journal_t
op_star
comma
r_struct
id|page
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_stop
c_func
(paren
id|handle_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_flush
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_lock_updates
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_unlock_updates
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
id|journal_t
op_star
id|journal_init_dev
c_func
(paren
id|kdev_t
id|dev
comma
id|kdev_t
id|fs_dev
comma
r_int
id|start
comma
r_int
id|len
comma
r_int
id|bsize
)paren
suffix:semicolon
r_extern
id|journal_t
op_star
id|journal_init_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_update_format
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_check_used_features
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_check_available_features
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_set_features
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_create
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_load
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
r_extern
r_void
id|journal_destroy
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_recover
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
r_extern
r_int
id|journal_wipe
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_skip_recovery
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_update_superblock
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__journal_abort_hard
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__journal_abort_soft
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|journal_abort
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|journal_errno
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_ack_err
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_clear_err
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_bmap
c_func
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_force_commit
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * journal_head management&n; */
r_extern
r_struct
id|journal_head
op_star
id|journal_add_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|journal_remove_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|__journal_remove_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|journal_unlock_journal_head
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
suffix:semicolon
multiline_comment|/* Primary revoke support */
DECL|macro|JOURNAL_REVOKE_DEFAULT_HASH
mdefine_line|#define JOURNAL_REVOKE_DEFAULT_HASH 256
r_extern
r_int
id|journal_init_revoke
c_func
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|journal_destroy_revoke_caches
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|journal_init_revoke_caches
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|journal_destroy_revoke
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_revoke
(paren
id|handle_t
op_star
comma
r_int
r_int
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int
id|journal_cancel_revoke
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|journal_write_revoke_records
c_func
(paren
id|journal_t
op_star
comma
id|transaction_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Recovery revoke support */
r_extern
r_int
id|journal_set_revoke
c_func
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
id|tid_t
)paren
suffix:semicolon
r_extern
r_int
id|journal_test_revoke
c_func
(paren
id|journal_t
op_star
comma
r_int
r_int
comma
id|tid_t
)paren
suffix:semicolon
r_extern
r_void
id|journal_clear_revoke
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
multiline_comment|/* The log thread user interface:&n; *&n; * Request space in the current transaction, and force transaction commit&n; * transitions on demand.&n; */
r_extern
r_int
id|log_space_left
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Called with journal locked */
r_extern
id|tid_t
id|log_start_commit
(paren
id|journal_t
op_star
comma
id|transaction_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|log_wait_commit
(paren
id|journal_t
op_star
comma
id|tid_t
)paren
suffix:semicolon
r_extern
r_int
id|log_do_checkpoint
(paren
id|journal_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|log_wait_for_space
c_func
(paren
id|journal_t
op_star
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
r_void
id|__journal_drop_transaction
c_func
(paren
id|journal_t
op_star
comma
id|transaction_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cleanup_journal_tail
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Reduce journal memory usage by flushing */
r_extern
r_void
id|shrink_journal_memory
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Debugging code only: */
DECL|macro|jbd_ENOSYS
mdefine_line|#define jbd_ENOSYS() &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;printk (KERN_ERR &quot;JBD unimplemented function &quot; __FUNCTION__); &bslash;&n;&t;current-&gt;state = TASK_UNINTERRUPTIBLE;&t;&t;&t;      &bslash;&n;&t;schedule();&t;&t;&t;&t;&t;&t;      &bslash;&n;} while (1)
multiline_comment|/*&n; * is_journal_abort&n; *&n; * Simple test wrapper function to test the JFS_ABORT state flag.  This&n; * bit, when set, indicates that we have had a fatal error somewhere,&n; * either inside the journaling layer or indicated to us by the client&n; * (eg. ext3), and that we and should not commit any further&n; * transactions.  &n; */
DECL|function|is_journal_aborted
r_static
r_inline
r_int
id|is_journal_aborted
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_return
id|journal-&gt;j_flags
op_amp
id|JFS_ABORT
suffix:semicolon
)brace
DECL|function|is_handle_aborted
r_static
r_inline
r_int
id|is_handle_aborted
c_func
(paren
id|handle_t
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
id|handle-&gt;h_aborted
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|is_journal_aborted
c_func
(paren
id|handle-&gt;h_transaction-&gt;t_journal
)paren
suffix:semicolon
)brace
DECL|function|journal_abort_handle
r_static
r_inline
r_void
id|journal_abort_handle
c_func
(paren
id|handle_t
op_star
id|handle
)paren
(brace
id|handle-&gt;h_aborted
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Not all architectures define BUG() */
macro_line|#ifndef BUG
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;        printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;* ((char *) 0) = 0; &bslash;&n; } while (0)
macro_line|#endif /* BUG */
macro_line|#endif /* __KERNEL__   */
multiline_comment|/* Comparison functions for transaction IDs: perform comparisons using&n; * modulo arithmetic so that they work over sequence number wraps. */
DECL|function|tid_gt
r_static
r_inline
r_int
id|tid_gt
c_func
(paren
id|tid_t
id|x
comma
id|tid_t
id|y
)paren
(brace
r_int
id|difference
op_assign
(paren
id|x
op_minus
id|y
)paren
suffix:semicolon
r_return
(paren
id|difference
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|tid_geq
r_static
r_inline
r_int
id|tid_geq
c_func
(paren
id|tid_t
id|x
comma
id|tid_t
id|y
)paren
(brace
r_int
id|difference
op_assign
(paren
id|x
op_minus
id|y
)paren
suffix:semicolon
r_return
(paren
id|difference
op_ge
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_int
id|journal_blocks_per_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/*&n; * Definitions which augment the buffer_head layer&n; */
multiline_comment|/* journaling buffer types */
DECL|macro|BJ_None
mdefine_line|#define BJ_None&t;&t;0&t;/* Not journaled */
DECL|macro|BJ_SyncData
mdefine_line|#define BJ_SyncData&t;1&t;/* Normal data: flush before commit */
DECL|macro|BJ_AsyncData
mdefine_line|#define BJ_AsyncData&t;2&t;/* writepage data: wait on it before commit */
DECL|macro|BJ_Metadata
mdefine_line|#define BJ_Metadata&t;3&t;/* Normal journaled metadata */
DECL|macro|BJ_Forget
mdefine_line|#define BJ_Forget&t;4&t;/* Buffer superceded by this transaction */
DECL|macro|BJ_IO
mdefine_line|#define BJ_IO&t;&t;5&t;/* Buffer is for temporary IO use */
DECL|macro|BJ_Shadow
mdefine_line|#define BJ_Shadow&t;6&t;/* Buffer contents being shadowed to the log */
DECL|macro|BJ_LogCtl
mdefine_line|#define BJ_LogCtl&t;7&t;/* Buffer contains log descriptors */
DECL|macro|BJ_Reserved
mdefine_line|#define BJ_Reserved&t;8&t;/* Buffer is reserved for access by journal */
DECL|macro|BJ_Types
mdefine_line|#define BJ_Types&t;9
r_extern
r_int
id|jbd_blocks_per_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
id|spinlock_t
id|jh_splice_lock
suffix:semicolon
multiline_comment|/*&n; * Once `expr1&squot; has been found true, take jh_splice_lock&n; * and then reevaluate everything.&n; */
DECL|macro|SPLICE_LOCK
mdefine_line|#define SPLICE_LOCK(expr1, expr2)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret = (expr1);&t;&t;&t;&t;&bslash;&n;&t;&t;if (ret) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;spin_lock(&amp;jh_splice_lock);&t;&t;&bslash;&n;&t;&t;&t;ret = (expr1) &amp;&amp; (expr2);&t;&t;&bslash;&n;&t;&t;&t;spin_unlock(&amp;jh_splice_lock);&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * A number of buffer state predicates.  They test for&n; * buffer_jbd() because they are used in core kernel code.&n; *&n; * These will be racy on SMP unless we&squot;re *sure* that the&n; * buffer won&squot;t be detached from the journalling system&n; * in parallel.&n; */
multiline_comment|/* Return true if the buffer is on journal list `list&squot; */
DECL|function|buffer_jlist_eq
r_static
r_inline
r_int
id|buffer_jlist_eq
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|list
)paren
(brace
r_return
id|SPLICE_LOCK
c_func
(paren
id|buffer_jbd
c_func
(paren
id|bh
)paren
comma
id|bh2jh
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|b_jlist
op_eq
id|list
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if this bufer is dirty wrt the journal */
DECL|function|buffer_jdirty
r_static
r_inline
r_int
id|buffer_jdirty
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|buffer_jbd
c_func
(paren
id|bh
)paren
op_logical_and
id|__buffer_state
c_func
(paren
id|bh
comma
id|JBDDirty
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if it&squot;s a data buffer which journalling is managing */
DECL|function|buffer_jbd_data
r_static
r_inline
r_int
id|buffer_jbd_data
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|SPLICE_LOCK
c_func
(paren
id|buffer_jbd
c_func
(paren
id|bh
)paren
comma
id|bh2jh
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|b_jlist
op_eq
id|BJ_SyncData
op_logical_or
id|bh2jh
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|b_jlist
op_eq
id|BJ_AsyncData
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|assert_spin_locked
mdefine_line|#define assert_spin_locked(lock)&t;J_ASSERT(spin_is_locked(lock))
macro_line|#else
DECL|macro|assert_spin_locked
mdefine_line|#define assert_spin_locked(lock)&t;do {} while(0)
macro_line|#endif
DECL|macro|buffer_trace_init
mdefine_line|#define buffer_trace_init(bh)&t;do {} while (0)
DECL|macro|print_buffer_fields
mdefine_line|#define print_buffer_fields(bh)&t;do {} while (0)
DECL|macro|print_buffer_trace
mdefine_line|#define print_buffer_trace(bh)&t;do {} while (0)
DECL|macro|BUFFER_TRACE
mdefine_line|#define BUFFER_TRACE(bh, info)&t;do {} while (0)
DECL|macro|BUFFER_TRACE2
mdefine_line|#define BUFFER_TRACE2(bh, bh2, info)&t;do {} while (0)
DECL|macro|JBUFFER_TRACE
mdefine_line|#define JBUFFER_TRACE(jh, info)&t;do {} while (0)
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* CONFIG_JBD || CONFIG_JBD_MODULE || !__KERNEL__ */
multiline_comment|/*&n; * Compatibility no-ops which allow the kernel to compile without CONFIG_JBD&n; * go here.&n; */
macro_line|#if defined(__KERNEL__) &amp;&amp; !(defined(CONFIG_JBD) || defined(CONFIG_JBD_MODULE))
DECL|macro|J_ASSERT
mdefine_line|#define J_ASSERT(expr)&t;&t;&t;do {} while (0)
DECL|macro|J_ASSERT_BH
mdefine_line|#define J_ASSERT_BH(bh, expr)&t;&t;do {} while (0)
DECL|macro|buffer_jbd
mdefine_line|#define buffer_jbd(bh)&t;&t;&t;0
DECL|macro|buffer_jlist_eq
mdefine_line|#define buffer_jlist_eq(bh, val)&t;0
DECL|macro|journal_buffer_journal_lru
mdefine_line|#define journal_buffer_journal_lru(bh)&t;0
macro_line|#endif&t;/* defined(__KERNEL__) &amp;&amp; !defined(CONFIG_JBD) */
macro_line|#endif&t;/* _LINUX_JBD_H */
eof
