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
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/journal-head.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#endif
DECL|macro|journal_oom_retry
mdefine_line|#define journal_oom_retry 1
multiline_comment|/*&n; * Define JBD_PARANIOD_IOFAIL to cause a kernel BUG() if ext3 finds&n; * certain classes of error which can occur due to failed IOs.  Under&n; * normal use we want ext3 to continue after such errors, because&n; * hardware _can_ fail, but for debugging purposes when running tests on&n; * known-good hardware we may want to trap these errors.&n; */
DECL|macro|JBD_PARANOID_IOFAIL
macro_line|#undef JBD_PARANOID_IOFAIL
multiline_comment|/*&n; * The default maximum commit age, in seconds.&n; */
DECL|macro|JBD_DEFAULT_MAX_COMMIT_AGE
mdefine_line|#define JBD_DEFAULT_MAX_COMMIT_AGE 5
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
r_const
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
multiline_comment|/**&n; * typedef handle_t - The handle_t type represents a single atomic update being performed by some process.&n; *&n; * All filesystem modifications made by the process go&n; * through this handle.  Recursive operations (such as quota operations)&n; * are gathered into a single update.&n; *&n; * The buffer credits field is used to account for journaled buffers&n; * being modified by the running process.  To ensure that there is&n; * enough log space for all outstanding operations, we need to limit the&n; * number of outstanding buffers possible at any time.  When the&n; * operation completes, any buffer credits not used are credited back to&n; * the transaction, so that at all times we know how many buffers the&n; * outstanding updates on a transaction might possibly touch. &n; * &n; * This is an opaque datatype.&n; **/
DECL|typedef|handle_t
r_typedef
r_struct
id|handle_s
id|handle_t
suffix:semicolon
multiline_comment|/* Atomic operation type */
multiline_comment|/**&n; * typedef journal_t - The journal_t maintains all of the journaling state information for a single filesystem.&n; *&n; * journal_t is linked to from the fs superblock structure.&n; * &n; * We use the journal_t to keep track of all outstanding transaction&n; * activity on the filesystem, and to manage the state of the log&n; * writing process.&n; *&n; * This is an opaque datatype.&n; **/
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
id|__be32
id|h_magic
suffix:semicolon
DECL|member|h_blocktype
id|__be32
id|h_blocktype
suffix:semicolon
DECL|member|h_sequence
id|__be32
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
id|__be32
id|t_blocknr
suffix:semicolon
multiline_comment|/* The on-disk block number */
DECL|member|t_flags
id|__be32
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
id|__be32
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
id|__be32
id|s_blocksize
suffix:semicolon
multiline_comment|/* journal device blocksize */
DECL|member|s_maxlen
id|__be32
id|s_maxlen
suffix:semicolon
multiline_comment|/* total blocks in journal file */
DECL|member|s_first
id|__be32
id|s_first
suffix:semicolon
multiline_comment|/* first block of log information */
multiline_comment|/* 0x0018 */
multiline_comment|/* Dynamic information describing the current state of the log */
DECL|member|s_sequence
id|__be32
id|s_sequence
suffix:semicolon
multiline_comment|/* first commit ID expected in log */
DECL|member|s_start
id|__be32
id|s_start
suffix:semicolon
multiline_comment|/* blocknr of start of log */
multiline_comment|/* 0x0020 */
multiline_comment|/* Error value, as set by journal_abort(). */
DECL|member|s_errno
id|__be32
id|s_errno
suffix:semicolon
multiline_comment|/* 0x0024 */
multiline_comment|/* Remaining fields are only valid in a version-2 superblock */
DECL|member|s_feature_compat
id|__be32
id|s_feature_compat
suffix:semicolon
multiline_comment|/* compatible feature set */
DECL|member|s_feature_incompat
id|__be32
id|s_feature_incompat
suffix:semicolon
multiline_comment|/* incompatible feature set */
DECL|member|s_feature_ro_compat
id|__be32
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
id|__be32
id|s_nr_users
suffix:semicolon
multiline_comment|/* Nr of filesystems sharing log */
DECL|member|s_dynsuper
id|__be32
id|s_dynsuper
suffix:semicolon
multiline_comment|/* Blocknr of dynamic superblock copy*/
multiline_comment|/* 0x0048 */
DECL|member|s_max_transaction
id|__be32
id|s_max_transaction
suffix:semicolon
multiline_comment|/* Limit of journal blocks per trans.*/
DECL|member|s_max_trans_data
id|__be32
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
macro_line|#include &lt;asm/bug.h&gt;
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
macro_line|#if defined(JBD_PARANOID_IOFAIL)
DECL|macro|J_EXPECT
mdefine_line|#define J_EXPECT(expr, why...)&t;&t;J_ASSERT(expr)
DECL|macro|J_EXPECT_BH
mdefine_line|#define J_EXPECT_BH(bh, expr, why...)&t;J_ASSERT_BH(bh, expr)
DECL|macro|J_EXPECT_JH
mdefine_line|#define J_EXPECT_JH(jh, expr, why...)&t;J_ASSERT_JH(jh, expr)
macro_line|#else
DECL|macro|__journal_expect
mdefine_line|#define __journal_expect(expr, why...)&t;&t;&t;&t;&t;     &bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;int val = (expr);&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;if (!val) {&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;printk(KERN_ERR&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&t;&quot;EXT3-fs unexpected failure: %s;&bslash;n&quot;,# expr); &bslash;&n;&t;&t;&t;printk(KERN_ERR why &quot;&bslash;n&quot;);&t;&t;&t;     &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;val;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;})
DECL|macro|J_EXPECT
mdefine_line|#define J_EXPECT(expr, why...)&t;&t;__journal_expect(expr, ## why)
DECL|macro|J_EXPECT_BH
mdefine_line|#define J_EXPECT_BH(bh, expr, why...)&t;__journal_expect(expr, ## why)
DECL|macro|J_EXPECT_JH
mdefine_line|#define J_EXPECT_JH(jh, expr, why...)&t;__journal_expect(expr, ## why)
macro_line|#endif
DECL|enum|jbd_state_bits
r_enum
id|jbd_state_bits
(brace
DECL|enumerator|BH_JBD
id|BH_JBD
multiline_comment|/* Has an attached ext3 journal_head */
op_assign
id|BH_PrivateStart
comma
DECL|enumerator|BH_JWrite
id|BH_JWrite
comma
multiline_comment|/* Being written to log (@@@ DEBUGGING) */
DECL|enumerator|BH_Freed
id|BH_Freed
comma
multiline_comment|/* Has been freed (truncated) */
DECL|enumerator|BH_Revoked
id|BH_Revoked
comma
multiline_comment|/* Has been revoked from the log */
DECL|enumerator|BH_RevokeValid
id|BH_RevokeValid
comma
multiline_comment|/* Revoked flag is valid */
DECL|enumerator|BH_JBDDirty
id|BH_JBDDirty
comma
multiline_comment|/* Is dirty but journaled */
DECL|enumerator|BH_State
id|BH_State
comma
multiline_comment|/* Pins most journal_head state */
DECL|enumerator|BH_JournalHead
id|BH_JournalHead
comma
multiline_comment|/* Pins bh-&gt;b_private and jh-&gt;b_bh */
DECL|enumerator|BH_Unshadow
id|BH_Unshadow
comma
multiline_comment|/* Dummy bit, for BJ_Shadow wakeup filtering */
)brace
suffix:semicolon
id|BUFFER_FNS
c_func
(paren
id|JBD
comma
id|jbd
)paren
id|BUFFER_FNS
c_func
(paren
id|JWrite
comma
id|jwrite
)paren
id|BUFFER_FNS
c_func
(paren
id|JBDDirty
comma
id|jbddirty
)paren
id|TAS_BUFFER_FNS
c_func
(paren
id|JBDDirty
comma
id|jbddirty
)paren
id|BUFFER_FNS
c_func
(paren
id|Revoked
comma
id|revoked
)paren
id|TAS_BUFFER_FNS
c_func
(paren
id|Revoked
comma
id|revoked
)paren
id|BUFFER_FNS
c_func
(paren
id|RevokeValid
comma
id|revokevalid
)paren
id|TAS_BUFFER_FNS
c_func
(paren
id|RevokeValid
comma
id|revokevalid
)paren
id|BUFFER_FNS
c_func
(paren
id|Freed
comma
id|freed
)paren
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
DECL|function|jbd_lock_bh_state
r_static
r_inline
r_void
id|jbd_lock_bh_state
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|bit_spin_lock
c_func
(paren
id|BH_State
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
DECL|function|jbd_trylock_bh_state
r_static
r_inline
r_int
id|jbd_trylock_bh_state
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|bit_spin_trylock
c_func
(paren
id|BH_State
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
DECL|function|jbd_is_locked_bh_state
r_static
r_inline
r_int
id|jbd_is_locked_bh_state
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_return
id|bit_spin_is_locked
c_func
(paren
id|BH_State
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
DECL|function|jbd_unlock_bh_state
r_static
r_inline
r_void
id|jbd_unlock_bh_state
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|bit_spin_unlock
c_func
(paren
id|BH_State
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
DECL|function|jbd_lock_bh_journal_head
r_static
r_inline
r_void
id|jbd_lock_bh_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|bit_spin_lock
c_func
(paren
id|BH_JournalHead
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
DECL|function|jbd_unlock_bh_journal_head
r_static
r_inline
r_void
id|jbd_unlock_bh_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|bit_spin_unlock
c_func
(paren
id|BH_JournalHead
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
r_struct
id|jbd_revoke_table_s
suffix:semicolon
multiline_comment|/**&n; * struct handle_s - The handle_s type is the concrete type associated with&n; *     handle_t.&n; * @h_transaction: Which compound transaction is this update a part of?&n; * @h_buffer_credits: Number of remaining buffers we are allowed to dirty.&n; * @h_ref: Reference count on this handle&n; * @h_err: Field for caller&squot;s use to track errors through large fs operations&n; * @h_sync: flag for sync-on-close&n; * @h_jdata: flag to force data journaling&n; * @h_aborted: flag indicating fatal error on handle&n; **/
multiline_comment|/* Docbook can&squot;t yet cope with the bit fields, but will leave the documentation&n; * in so it can be fixed later. &n; */
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
multiline_comment|/* Field for caller&squot;s use to track errors through large fs */
multiline_comment|/* operations */
DECL|member|h_err
r_int
id|h_err
suffix:semicolon
multiline_comment|/* Flags [no locking] */
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
multiline_comment|/*&n; * Lock ranking:&n; *&n; *    j_list_lock&n; *      -&gt;jbd_lock_bh_journal_head()&t;(This is &quot;innermost&quot;)&n; *&n; *    j_state_lock&n; *    -&gt;jbd_lock_bh_state()&n; *&n; *    jbd_lock_bh_state()&n; *    -&gt;j_list_lock&n; *&n; *    j_state_lock&n; *    -&gt;t_handle_lock&n; *&n; *    j_state_lock&n; *    -&gt;j_list_lock&t;&t;&t;(journal_unmap_buffer)&n; *&n; */
DECL|struct|transaction_s
r_struct
id|transaction_s
(brace
multiline_comment|/* Pointer to the journal for this transaction. [no locking] */
DECL|member|t_journal
id|journal_t
op_star
id|t_journal
suffix:semicolon
multiline_comment|/* Sequence number for this transaction [no locking] */
DECL|member|t_tid
id|tid_t
id|t_tid
suffix:semicolon
multiline_comment|/*&n;&t; * Transaction&squot;s current state&n;&t; * [no locking - only kjournald alters this]&n;&t; * FIXME: needs barriers&n;&t; * KLUDGE: [use j_state_lock]&n;&t; */
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
multiline_comment|/*&n;&t; * Where in the log does this transaction&squot;s commit start? [no locking]&n;&t; */
DECL|member|t_log_start
r_int
r_int
id|t_log_start
suffix:semicolon
multiline_comment|/* Number of buffers on the t_buffers list [j_list_lock] */
DECL|member|t_nr_buffers
r_int
id|t_nr_buffers
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all buffers reserved but not yet&n;&t; * modified by this transaction [j_list_lock]&n;&t; */
DECL|member|t_reserved_list
r_struct
id|journal_head
op_star
id|t_reserved_list
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all buffers under writeout during&n;&t; * commit [j_list_lock]&n;&t; */
DECL|member|t_locked_list
r_struct
id|journal_head
op_star
id|t_locked_list
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all metadata buffers owned by this&n;&t; * transaction [j_list_lock]&n;&t; */
DECL|member|t_buffers
r_struct
id|journal_head
op_star
id|t_buffers
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all data buffers still to be&n;&t; * flushed before this transaction can be committed [j_list_lock]&n;&t; */
DECL|member|t_sync_datalist
r_struct
id|journal_head
op_star
id|t_sync_datalist
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all forget buffers (superseded&n;&t; * buffers which we can un-checkpoint once this transaction commits)&n;&t; * [j_list_lock]&n;&t; */
DECL|member|t_forget
r_struct
id|journal_head
op_star
id|t_forget
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of all buffers still to be flushed before&n;&t; * this transaction can be checkpointed. [j_list_lock]&n;&t; */
DECL|member|t_checkpoint_list
r_struct
id|journal_head
op_star
id|t_checkpoint_list
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of temporary buffers currently undergoing&n;&t; * IO in the log [j_list_lock]&n;&t; */
DECL|member|t_iobuf_list
r_struct
id|journal_head
op_star
id|t_iobuf_list
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of metadata buffers being shadowed by log&n;&t; * IO.  The IO buffers on the iobuf list and the shadow buffers on this&n;&t; * list match each other one for one at all times. [j_list_lock]&n;&t; */
DECL|member|t_shadow_list
r_struct
id|journal_head
op_star
id|t_shadow_list
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked circular list of control buffers being written to the&n;&t; * log. [j_list_lock]&n;&t; */
DECL|member|t_log_list
r_struct
id|journal_head
op_star
id|t_log_list
suffix:semicolon
multiline_comment|/*&n;&t; * Protects info related to handles&n;&t; */
DECL|member|t_handle_lock
id|spinlock_t
id|t_handle_lock
suffix:semicolon
multiline_comment|/*&n;&t; * Number of outstanding updates running on this transaction&n;&t; * [t_handle_lock]&n;&t; */
DECL|member|t_updates
r_int
id|t_updates
suffix:semicolon
multiline_comment|/*&n;&t; * Number of buffers reserved for use by all handles in this transaction&n;&t; * handle but not yet modified. [t_handle_lock]&n;&t; */
DECL|member|t_outstanding_credits
r_int
id|t_outstanding_credits
suffix:semicolon
multiline_comment|/*&n;&t; * Forward and backward links for the circular list of all transactions&n;&t; * awaiting checkpoint. [j_list_lock]&n;&t; */
DECL|member|t_cpnext
DECL|member|t_cpprev
id|transaction_t
op_star
id|t_cpnext
comma
op_star
id|t_cpprev
suffix:semicolon
multiline_comment|/*&n;&t; * When will the transaction expire (become due for commit), in jiffies?&n;&t; * [no locking]&n;&t; */
DECL|member|t_expires
r_int
r_int
id|t_expires
suffix:semicolon
multiline_comment|/*&n;&t; * How many handles used this transaction? [t_handle_lock]&n;&t; */
DECL|member|t_handle_count
r_int
id|t_handle_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct journal_s - The journal_s type is the concrete type associated with&n; *     journal_t.&n; * @j_flags:  General journaling state flags&n; * @j_errno:  Is there an outstanding uncleared error on the journal (from a&n; *     prior abort)? &n; * @j_sb_buffer: First part of superblock buffer&n; * @j_superblock: Second part of superblock buffer&n; * @j_format_version: Version of the superblock format&n; * @j_barrier_count:  Number of processes waiting to create a barrier lock&n; * @j_barrier: The barrier lock itself&n; * @j_running_transaction: The current running transaction..&n; * @j_committing_transaction: the transaction we are pushing to disk&n; * @j_checkpoint_transactions: a linked circular list of all transactions&n; *  waiting for checkpointing&n; * @j_wait_transaction_locked: Wait queue for waiting for a locked transaction&n; *  to start committing, or for a barrier lock to be released&n; * @j_wait_logspace: Wait queue for waiting for checkpointing to complete&n; * @j_wait_done_commit: Wait queue for waiting for commit to complete &n; * @j_wait_checkpoint:  Wait queue to trigger checkpointing&n; * @j_wait_commit: Wait queue to trigger commit&n; * @j_wait_updates: Wait queue to wait for updates to complete&n; * @j_checkpoint_sem: Semaphore for locking against concurrent checkpoints&n; * @j_head: Journal head - identifies the first unused block in the journal&n; * @j_tail: Journal tail - identifies the oldest still-used block in the&n; *  journal.&n; * @j_free: Journal free - how many free blocks are there in the journal?&n; * @j_first: The block number of the first usable block &n; * @j_last: The block number one beyond the last usable block&n; * @j_dev: Device where we store the journal&n; * @j_blocksize: blocksize for the location where we store the journal.&n; * @j_blk_offset: starting block offset for into the device where we store the&n; *     journal&n; * @j_fs_dev: Device which holds the client fs.  For internal journal this will&n; *     be equal to j_dev&n; * @j_maxlen: Total maximum capacity of the journal region on disk.&n; * @j_inode: Optional inode where we store the journal.  If present, all journal&n; *     block numbers are mapped into this inode via bmap().&n; * @j_tail_sequence:  Sequence number of the oldest transaction in the log &n; * @j_transaction_sequence: Sequence number of the next transaction to grant&n; * @j_commit_sequence: Sequence number of the most recently committed&n; *  transaction&n; * @j_commit_request: Sequence number of the most recent transaction wanting&n; *     commit &n; * @j_uuid: Uuid of client object.&n; * @j_task: Pointer to the current commit thread for this journal&n; * @j_max_transaction_buffers:  Maximum number of metadata buffers to allow in a&n; *     single compound commit transaction&n; * @j_commit_interval: What is the maximum transaction lifetime before we begin&n; *  a commit?&n; * @j_commit_timer:  The timer used to wakeup the commit thread&n; * @j_revoke: The revoke table - maintains the list of revoked blocks in the&n; *     current transaction.&n; */
DECL|struct|journal_s
r_struct
id|journal_s
(brace
multiline_comment|/* General journaling state flags [j_state_lock] */
DECL|member|j_flags
r_int
r_int
id|j_flags
suffix:semicolon
multiline_comment|/*&n;&t; * Is there an outstanding uncleared error on the journal (from a prior&n;&t; * abort)? [j_state_lock]&n;&t; */
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
multiline_comment|/*&n;&t; * Protect the various scalars in the journal&n;&t; */
DECL|member|j_state_lock
id|spinlock_t
id|j_state_lock
suffix:semicolon
multiline_comment|/*&n;&t; * Number of processes waiting to create a barrier lock [j_state_lock]&n;&t; */
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
multiline_comment|/*&n;&t; * Transactions: The current running transaction...&n;&t; * [j_state_lock] [caller holding open handle]&n;&t; */
DECL|member|j_running_transaction
id|transaction_t
op_star
id|j_running_transaction
suffix:semicolon
multiline_comment|/*&n;&t; * the transaction we are pushing to disk&n;&t; * [j_state_lock] [caller holding open handle]&n;&t; */
DECL|member|j_committing_transaction
id|transaction_t
op_star
id|j_committing_transaction
suffix:semicolon
multiline_comment|/*&n;&t; * ... and a linked circular list of all transactions waiting for&n;&t; * checkpointing. [j_list_lock]&n;&t; */
DECL|member|j_checkpoint_transactions
id|transaction_t
op_star
id|j_checkpoint_transactions
suffix:semicolon
multiline_comment|/*&n;&t; * Wait queue for waiting for a locked transaction to start committing,&n;&t; * or for a barrier lock to be released&n;&t; */
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
multiline_comment|/*&n;&t; * Journal head: identifies the first unused block in the journal.&n;&t; * [j_state_lock]&n;&t; */
DECL|member|j_head
r_int
r_int
id|j_head
suffix:semicolon
multiline_comment|/*&n;&t; * Journal tail: identifies the oldest still-used block in the journal.&n;&t; * [j_state_lock]&n;&t; */
DECL|member|j_tail
r_int
r_int
id|j_tail
suffix:semicolon
multiline_comment|/*&n;&t; * Journal free: how many free blocks are there in the journal?&n;&t; * [j_state_lock]&n;&t; */
DECL|member|j_free
r_int
r_int
id|j_free
suffix:semicolon
multiline_comment|/*&n;&t; * Journal start and end: the block numbers of the first usable block&n;&t; * and one beyond the last usable block in the journal. [j_state_lock]&n;&t; */
DECL|member|j_first
r_int
r_int
id|j_first
suffix:semicolon
DECL|member|j_last
r_int
r_int
id|j_last
suffix:semicolon
multiline_comment|/*&n;&t; * Device, blocksize and starting block offset for the location where we&n;&t; * store the journal.&n;&t; */
DECL|member|j_dev
r_struct
id|block_device
op_star
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
multiline_comment|/*&n;&t; * Device which holds the client fs.  For internal journal this will be&n;&t; * equal to j_dev.&n;&t; */
DECL|member|j_fs_dev
r_struct
id|block_device
op_star
id|j_fs_dev
suffix:semicolon
multiline_comment|/* Total maximum capacity of the journal region on disk. */
DECL|member|j_maxlen
r_int
r_int
id|j_maxlen
suffix:semicolon
multiline_comment|/*&n;&t; * Protects the buffer lists and internal buffer state.&n;&t; */
DECL|member|j_list_lock
id|spinlock_t
id|j_list_lock
suffix:semicolon
multiline_comment|/* Optional inode where we store the journal.  If present, all */
multiline_comment|/* journal block numbers are mapped into this inode via */
multiline_comment|/* bmap(). */
DECL|member|j_inode
r_struct
id|inode
op_star
id|j_inode
suffix:semicolon
multiline_comment|/*&n;&t; * Sequence number of the oldest transaction in the log [j_state_lock]&n;&t; */
DECL|member|j_tail_sequence
id|tid_t
id|j_tail_sequence
suffix:semicolon
multiline_comment|/*&n;&t; * Sequence number of the next transaction to grant [j_state_lock]&n;&t; */
DECL|member|j_transaction_sequence
id|tid_t
id|j_transaction_sequence
suffix:semicolon
multiline_comment|/*&n;&t; * Sequence number of the most recently committed transaction&n;&t; * [j_state_lock].&n;&t; */
DECL|member|j_commit_sequence
id|tid_t
id|j_commit_sequence
suffix:semicolon
multiline_comment|/*&n;&t; * Sequence number of the most recent transaction wanting commit&n;&t; * [j_state_lock]&n;&t; */
DECL|member|j_commit_request
id|tid_t
id|j_commit_request
suffix:semicolon
multiline_comment|/*&n;&t; * Journal uuid: identifies the object (filesystem, LVM volume etc)&n;&t; * backed by this journal.  This will eventually be replaced by an array&n;&t; * of uuids, allowing us to index multiple devices within a single&n;&t; * journal and to perform atomic updates across them.&n;&t; */
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
multiline_comment|/*&n;&t; * Maximum number of metadata buffers to allow in a single compound&n;&t; * commit transaction&n;&t; */
DECL|member|j_max_transaction_buffers
r_int
id|j_max_transaction_buffers
suffix:semicolon
multiline_comment|/*&n;&t; * What is the maximum transaction lifetime before we begin a commit?&n;&t; */
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
multiline_comment|/*&n;&t; * The revoke table: maintains the list of revoked blocks in the&n;&t; * current transaction.  [j_revoke_lock]&n;&t; */
DECL|member|j_revoke_lock
id|spinlock_t
id|j_revoke_lock
suffix:semicolon
DECL|member|j_revoke
r_struct
id|jbd_revoke_table_s
op_star
id|j_revoke
suffix:semicolon
DECL|member|j_revoke_table
r_struct
id|jbd_revoke_table_s
op_star
id|j_revoke_table
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * An opaque pointer to fs-private information.  ext3 puts its&n;&t; * superblock pointer here&n;&t; */
DECL|member|j_private
r_void
op_star
id|j_private
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
DECL|macro|JFS_BARRIER
mdefine_line|#define JFS_BARRIER&t;0x020&t;/* Use IDE barriers */
multiline_comment|/* &n; * Function declarations for the journaling transaction and buffer&n; * management&n; */
multiline_comment|/* Filing buffers */
r_extern
r_void
id|journal_unfile_buffer
c_func
(paren
id|journal_t
op_star
comma
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
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
id|journal_t
op_star
comma
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
r_void
id|__journal_remove_checkpoint
c_func
(paren
r_struct
id|journal_head
op_star
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Journal locking.&n; *&n; * We need to lock the journal during transaction state changes so that nobody&n; * ever tries to take a handle on the running transaction while we are in the&n; * middle of moving it to the commit phase.  j_state_lock does this.&n; *&n; * Note that the locking is completely interrupt unsafe.  We never touch&n; * journal structures from interrupts.&n; */
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
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
op_star
id|credits
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
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
op_star
id|credits
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
comma
r_int
id|credits
)paren
suffix:semicolon
r_extern
r_int
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
id|journal_invalidatepage
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
r_struct
id|block_device
op_star
id|bdev
comma
r_struct
id|block_device
op_star
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
r_struct
id|journal_head
op_star
id|journal_grab_journal_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
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
r_void
id|journal_put_journal_head
c_func
(paren
r_struct
id|journal_head
op_star
id|jh
)paren
suffix:semicolon
multiline_comment|/*&n; * handle management&n; */
r_extern
id|kmem_cache_t
op_star
id|jbd_handle_cache
suffix:semicolon
DECL|function|jbd_alloc_handle
r_static
r_inline
id|handle_t
op_star
id|jbd_alloc_handle
c_func
(paren
r_int
id|gfp_flags
)paren
(brace
r_return
id|kmem_cache_alloc
c_func
(paren
id|jbd_handle_cache
comma
id|gfp_flags
)paren
suffix:semicolon
)brace
DECL|function|jbd_free_handle
r_static
r_inline
r_void
id|jbd_free_handle
c_func
(paren
id|handle_t
op_star
id|handle
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|jbd_handle_cache
comma
id|handle
)paren
suffix:semicolon
)brace
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
r_extern
r_void
id|journal_switch_revoke_table
c_func
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
multiline_comment|/*&n; * The log thread user interface:&n; *&n; * Request space in the current transaction, and force transaction commit&n; * transitions on demand.&n; */
r_int
id|__log_space_left
c_func
(paren
id|journal_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Called with journal locked */
r_int
id|log_start_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|tid_t
id|tid
)paren
suffix:semicolon
r_int
id|__log_start_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|tid_t
id|tid
)paren
suffix:semicolon
r_int
id|journal_start_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|tid_t
op_star
id|tid
)paren
suffix:semicolon
r_int
id|journal_force_commit_nested
c_func
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
r_int
id|log_wait_commit
c_func
(paren
id|journal_t
op_star
id|journal
comma
id|tid_t
id|tid
)paren
suffix:semicolon
r_int
id|log_do_checkpoint
c_func
(paren
id|journal_t
op_star
id|journal
)paren
suffix:semicolon
r_void
id|__log_wait_for_space
c_func
(paren
id|journal_t
op_star
id|journal
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
multiline_comment|/* Debugging code only: */
DECL|macro|jbd_ENOSYS
mdefine_line|#define jbd_ENOSYS() &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;           &bslash;&n;&t;printk (KERN_ERR &quot;JBD unimplemented function %s&bslash;n&quot;, __FUNCTION__); &bslash;&n;&t;current-&gt;state = TASK_UNINTERRUPTIBLE;&t;&t;&t;           &bslash;&n;&t;schedule();&t;&t;&t;&t;&t;&t;           &bslash;&n;} while (1)
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
multiline_comment|/*&n; * Return the minimum number of blocks which must be free in the journal&n; * before a new transaction may be started.  Must be called under j_state_lock.&n; */
DECL|function|jbd_space_needed
r_static
r_inline
r_int
id|jbd_space_needed
c_func
(paren
id|journal_t
op_star
id|journal
)paren
(brace
r_int
id|nblocks
op_assign
id|journal-&gt;j_max_transaction_buffers
suffix:semicolon
r_if
c_cond
(paren
id|journal-&gt;j_committing_transaction
)paren
id|nblocks
op_add_assign
id|journal-&gt;j_committing_transaction
op_member_access_from_pointer
id|t_outstanding_credits
suffix:semicolon
r_return
id|nblocks
suffix:semicolon
)brace
multiline_comment|/*&n; * Definitions which augment the buffer_head layer&n; */
multiline_comment|/* journaling buffer types */
DECL|macro|BJ_None
mdefine_line|#define BJ_None&t;&t;0&t;/* Not journaled */
DECL|macro|BJ_SyncData
mdefine_line|#define BJ_SyncData&t;1&t;/* Normal data: flush before commit */
DECL|macro|BJ_Metadata
mdefine_line|#define BJ_Metadata&t;2&t;/* Normal journaled metadata */
DECL|macro|BJ_Forget
mdefine_line|#define BJ_Forget&t;3&t;/* Buffer superseded by this transaction */
DECL|macro|BJ_IO
mdefine_line|#define BJ_IO&t;&t;4&t;/* Buffer is for temporary IO use */
DECL|macro|BJ_Shadow
mdefine_line|#define BJ_Shadow&t;5&t;/* Buffer contents being shadowed to the log */
DECL|macro|BJ_LogCtl
mdefine_line|#define BJ_LogCtl&t;6&t;/* Buffer contains log descriptors */
DECL|macro|BJ_Reserved
mdefine_line|#define BJ_Reserved&t;7&t;/* Buffer is reserved for access by journal */
DECL|macro|BJ_Locked
mdefine_line|#define BJ_Locked&t;8&t;/* Locked for I/O during commit */
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
DECL|macro|journal_buffer_journal_lru
mdefine_line|#define journal_buffer_journal_lru(bh)&t;0
macro_line|#endif&t;/* defined(__KERNEL__) &amp;&amp; !defined(CONFIG_JBD) */
macro_line|#endif&t;/* _LINUX_JBD_H */
eof
