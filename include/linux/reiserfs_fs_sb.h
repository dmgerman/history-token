multiline_comment|/* Copyright 1996-2000 Hans Reiser, see reiserfs/README for licensing&n; * and copyright details */
macro_line|#ifndef _LINUX_REISER_FS_SB
DECL|macro|_LINUX_REISER_FS_SB
mdefine_line|#define _LINUX_REISER_FS_SB
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#endif
multiline_comment|/* struct reiserfs_super_block accessors/mutators&n; * since this is a disk structure, it will always be in &n; * little endian format. */
DECL|macro|sb_block_count
mdefine_line|#define sb_block_count(sbp)         (le32_to_cpu((sbp)-&gt;s_v1.s_block_count))
DECL|macro|set_sb_block_count
mdefine_line|#define set_sb_block_count(sbp,v)   ((sbp)-&gt;s_v1.s_block_count = cpu_to_le32(v))
DECL|macro|sb_free_blocks
mdefine_line|#define sb_free_blocks(sbp)         (le32_to_cpu((sbp)-&gt;s_v1.s_free_blocks))
DECL|macro|set_sb_free_blocks
mdefine_line|#define set_sb_free_blocks(sbp,v)   ((sbp)-&gt;s_v1.s_free_blocks = cpu_to_le32(v))
DECL|macro|sb_root_block
mdefine_line|#define sb_root_block(sbp)          (le32_to_cpu((sbp)-&gt;s_v1.s_root_block))
DECL|macro|set_sb_root_block
mdefine_line|#define set_sb_root_block(sbp,v)    ((sbp)-&gt;s_v1.s_root_block = cpu_to_le32(v))
DECL|macro|sb_jp_journal_1st_block
mdefine_line|#define sb_jp_journal_1st_block(sbp)  &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_1st_block))
DECL|macro|set_sb_jp_journal_1st_block
mdefine_line|#define set_sb_jp_journal_1st_block(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_1st_block = cpu_to_le32(v))
DECL|macro|sb_jp_journal_dev
mdefine_line|#define sb_jp_journal_dev(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_dev))
DECL|macro|set_sb_jp_journal_dev
mdefine_line|#define set_sb_jp_journal_dev(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_dev = cpu_to_le32(v))
DECL|macro|sb_jp_journal_size
mdefine_line|#define sb_jp_journal_size(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_size))
DECL|macro|set_sb_jp_journal_size
mdefine_line|#define set_sb_jp_journal_size(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_size = cpu_to_le32(v))
DECL|macro|sb_jp_journal_trans_max
mdefine_line|#define sb_jp_journal_trans_max(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_trans_max))
DECL|macro|set_sb_jp_journal_trans_max
mdefine_line|#define set_sb_jp_journal_trans_max(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_trans_max = cpu_to_le32(v))
DECL|macro|sb_jp_journal_magic
mdefine_line|#define sb_jp_journal_magic(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_magic))
DECL|macro|set_sb_jp_journal_magic
mdefine_line|#define set_sb_jp_journal_magic(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_magic = cpu_to_le32(v))
DECL|macro|sb_jp_journal_max_batch
mdefine_line|#define sb_jp_journal_max_batch(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_max_batch))
DECL|macro|set_sb_jp_journal_max_batch
mdefine_line|#define set_sb_jp_journal_max_batch(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_max_batch = cpu_to_le32(v))
DECL|macro|sb_jp_jourmal_max_commit_age
mdefine_line|#define sb_jp_jourmal_max_commit_age(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_journal.jp_journal_max_commit_age))
DECL|macro|set_sb_jp_journal_max_commit_age
mdefine_line|#define set_sb_jp_journal_max_commit_age(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_journal.jp_journal_max_commit_age = cpu_to_le32(v))
DECL|macro|sb_blocksize
mdefine_line|#define sb_blocksize(sbp)          (le16_to_cpu((sbp)-&gt;s_v1.s_blocksize))
DECL|macro|set_sb_blocksize
mdefine_line|#define set_sb_blocksize(sbp,v)    ((sbp)-&gt;s_v1.s_blocksize = cpu_to_le16(v))
DECL|macro|sb_oid_maxsize
mdefine_line|#define sb_oid_maxsize(sbp)        (le16_to_cpu((sbp)-&gt;s_v1.s_oid_maxsize))
DECL|macro|set_sb_oid_maxsize
mdefine_line|#define set_sb_oid_maxsize(sbp,v)  ((sbp)-&gt;s_v1.s_oid_maxsize = cpu_to_le16(v))
DECL|macro|sb_oid_cursize
mdefine_line|#define sb_oid_cursize(sbp)        (le16_to_cpu((sbp)-&gt;s_v1.s_oid_cursize))
DECL|macro|set_sb_oid_cursize
mdefine_line|#define set_sb_oid_cursize(sbp,v)  ((sbp)-&gt;s_v1.s_oid_cursize = cpu_to_le16(v))
DECL|macro|sb_umount_state
mdefine_line|#define sb_umount_state(sbp)       (le16_to_cpu((sbp)-&gt;s_v1.s_umount_state))
DECL|macro|set_sb_umount_state
mdefine_line|#define set_sb_umount_state(sbp,v) ((sbp)-&gt;s_v1.s_umount_state = cpu_to_le16(v))
DECL|macro|sb_fs_state
mdefine_line|#define sb_fs_state(sbp)           (le16_to_cpu((sbp)-&gt;s_v1.s_fs_state))
DECL|macro|set_sb_fs_state
mdefine_line|#define set_sb_fs_state(sbp,v)     ((sbp)-&gt;s_v1.s_fs_state = cpu_to_le16(v)) 
DECL|macro|sb_hash_function_code
mdefine_line|#define sb_hash_function_code(sbp) &bslash;&n;              (le32_to_cpu((sbp)-&gt;s_v1.s_hash_function_code))
DECL|macro|set_sb_hash_function_code
mdefine_line|#define set_sb_hash_function_code(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_hash_function_code = cpu_to_le32(v))
DECL|macro|sb_tree_height
mdefine_line|#define sb_tree_height(sbp)        (le16_to_cpu((sbp)-&gt;s_v1.s_tree_height))
DECL|macro|set_sb_tree_height
mdefine_line|#define set_sb_tree_height(sbp,v)  ((sbp)-&gt;s_v1.s_tree_height = cpu_to_le16(v))
DECL|macro|sb_bmap_nr
mdefine_line|#define sb_bmap_nr(sbp)            (le16_to_cpu((sbp)-&gt;s_v1.s_bmap_nr))
DECL|macro|set_sb_bmap_nr
mdefine_line|#define set_sb_bmap_nr(sbp,v)      ((sbp)-&gt;s_v1.s_bmap_nr = cpu_to_le16(v))
DECL|macro|sb_version
mdefine_line|#define sb_version(sbp)            (le16_to_cpu((sbp)-&gt;s_v1.s_version))
DECL|macro|set_sb_version
mdefine_line|#define set_sb_version(sbp,v)      ((sbp)-&gt;s_v1.s_version = cpu_to_le16(v))
DECL|macro|sb_reserved_for_journal
mdefine_line|#define sb_reserved_for_journal(sbp) &bslash;&n;              (le16_to_cpu((sbp)-&gt;s_v1.s_reserved_for_journal))
DECL|macro|set_sb_reserved_for_journal
mdefine_line|#define set_sb_reserved_for_journal(sbp,v) &bslash;&n;              ((sbp)-&gt;s_v1.s_reserved_for_journal = cpu_to_le16(v))
multiline_comment|/* LOGGING -- */
multiline_comment|/* These all interelate for performance.  &n;**&n;** If the journal block count is smaller than n transactions, you lose speed. &n;** I don&squot;t know what n is yet, I&squot;m guessing 8-16.&n;**&n;** typical transaction size depends on the application, how often fsync is&n;** called, and how many metadata blocks you dirty in a 30 second period.  &n;** The more small files (&lt;16k) you use, the larger your transactions will&n;** be.&n;** &n;** If your journal fills faster than dirty buffers get flushed to disk, it must flush them before allowing the journal&n;** to wrap, which slows things down.  If you need high speed meta data updates, the journal should be big enough&n;** to prevent wrapping before dirty meta blocks get to disk.&n;**&n;** If the batch max is smaller than the transaction max, you&squot;ll waste space at the end of the journal&n;** because journal_end sets the next transaction to start at 0 if the next transaction has any chance of wrapping.&n;**&n;** The large the batch max age, the better the speed, and the more meta data changes you&squot;ll lose after a crash.&n;**&n;*/
multiline_comment|/* don&squot;t mess with these for a while */
multiline_comment|/* we have a node size define somewhere in reiserfs_fs.h. -Hans */
DECL|macro|JOURNAL_BLOCK_SIZE
mdefine_line|#define JOURNAL_BLOCK_SIZE  4096 /* BUG gotta get rid of this */
DECL|macro|JOURNAL_MAX_CNODE
mdefine_line|#define JOURNAL_MAX_CNODE   1500 /* max cnodes to allocate. */
DECL|macro|JOURNAL_HASH_SIZE
mdefine_line|#define JOURNAL_HASH_SIZE 8192   
DECL|macro|JOURNAL_NUM_BITMAPS
mdefine_line|#define JOURNAL_NUM_BITMAPS 5 /* number of copies of the bitmaps to have floating.  Must be &gt;= 2 */
DECL|macro|JOURNAL_LIST_COUNT
mdefine_line|#define JOURNAL_LIST_COUNT 64
multiline_comment|/* these are bh_state bit flag offset numbers, for use in the buffer head */
DECL|macro|BH_JDirty
mdefine_line|#define BH_JDirty       16      /* journal data needs to be written before buffer can be marked dirty */
DECL|macro|BH_JDirty_wait
mdefine_line|#define BH_JDirty_wait 18&t;/* commit is done, buffer marked dirty */
DECL|macro|BH_JNew
mdefine_line|#define BH_JNew 19&t;&t;/* buffer allocated during this transaction, no need to write if freed during this trans too */
multiline_comment|/* ugly.  metadata blocks must be prepared before they can be logged.  &n;** prepared means unlocked and cleaned.  If the block is prepared, but not&n;** logged for some reason, any bits cleared while preparing it must be &n;** set again.&n;*/
DECL|macro|BH_JPrepared
mdefine_line|#define BH_JPrepared 20&t;&t;/* block has been prepared for the log */
DECL|macro|BH_JRestore_dirty
mdefine_line|#define BH_JRestore_dirty 22    /* restore the dirty bit later */
multiline_comment|/* One of these for every block in every transaction&n;** Each one is in two hash tables.  First, a hash of the current transaction, and after journal_end, a&n;** hash of all the in memory transactions.&n;** next and prev are used by the current transaction (journal_hash).&n;** hnext and hprev are used by journal_list_hash.  If a block is in more than one transaction, the journal_list_hash&n;** links it in multiple times.  This allows flush_journal_list to remove just the cnode belonging&n;** to a given transaction.&n;*/
DECL|struct|reiserfs_journal_cnode
r_struct
id|reiserfs_journal_cnode
(brace
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
multiline_comment|/* real buffer head */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* dev of real buffer head */
DECL|member|blocknr
r_int
r_int
id|blocknr
suffix:semicolon
multiline_comment|/* block number of real buffer head, == 0 when buffer on disk */
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|jlist
r_struct
id|reiserfs_journal_list
op_star
id|jlist
suffix:semicolon
multiline_comment|/* journal list this cnode lives in */
DECL|member|next
r_struct
id|reiserfs_journal_cnode
op_star
id|next
suffix:semicolon
multiline_comment|/* next in transaction list */
DECL|member|prev
r_struct
id|reiserfs_journal_cnode
op_star
id|prev
suffix:semicolon
multiline_comment|/* prev in transaction list */
DECL|member|hprev
r_struct
id|reiserfs_journal_cnode
op_star
id|hprev
suffix:semicolon
multiline_comment|/* prev in hash list */
DECL|member|hnext
r_struct
id|reiserfs_journal_cnode
op_star
id|hnext
suffix:semicolon
multiline_comment|/* next in hash list */
)brace
suffix:semicolon
DECL|struct|reiserfs_bitmap_node
r_struct
id|reiserfs_bitmap_node
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reiserfs_list_bitmap
r_struct
id|reiserfs_list_bitmap
(brace
DECL|member|journal_list
r_struct
id|reiserfs_journal_list
op_star
id|journal_list
suffix:semicolon
DECL|member|bitmaps
r_struct
id|reiserfs_bitmap_node
op_star
op_star
id|bitmaps
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;** transaction handle which is passed around for all journal calls&n;*/
DECL|struct|reiserfs_transaction_handle
r_struct
id|reiserfs_transaction_handle
(brace
multiline_comment|/* ifdef it. -Hans */
DECL|member|t_caller
r_char
op_star
id|t_caller
suffix:semicolon
multiline_comment|/* debugging use */
DECL|member|t_blocks_logged
r_int
id|t_blocks_logged
suffix:semicolon
multiline_comment|/* number of blocks this writer has logged */
DECL|member|t_blocks_allocated
r_int
id|t_blocks_allocated
suffix:semicolon
multiline_comment|/* number of blocks this writer allocated */
DECL|member|t_trans_id
r_int
r_int
id|t_trans_id
suffix:semicolon
multiline_comment|/* sanity check, equals the current trans id */
DECL|member|t_super
r_struct
id|super_block
op_star
id|t_super
suffix:semicolon
multiline_comment|/* super for this FS when journal_begin was &n;                                   called. saves calls to reiserfs_get_super */
)brace
suffix:semicolon
multiline_comment|/*&n;** one of these for each transaction.  The most important part here is the j_realblock.&n;** this list of cnodes is used to hash all the blocks in all the commits, to mark all the&n;** real buffer heads dirty once all the commits hit the disk,&n;** and to make sure every real block in a transaction is on disk before allowing the log area&n;** to be overwritten */
DECL|struct|reiserfs_journal_list
r_struct
id|reiserfs_journal_list
(brace
DECL|member|j_start
r_int
r_int
id|j_start
suffix:semicolon
DECL|member|j_len
r_int
r_int
id|j_len
suffix:semicolon
DECL|member|j_nonzerolen
id|atomic_t
id|j_nonzerolen
suffix:semicolon
DECL|member|j_commit_left
id|atomic_t
id|j_commit_left
suffix:semicolon
DECL|member|j_flushing
id|atomic_t
id|j_flushing
suffix:semicolon
DECL|member|j_commit_flushing
id|atomic_t
id|j_commit_flushing
suffix:semicolon
DECL|member|j_older_commits_done
id|atomic_t
id|j_older_commits_done
suffix:semicolon
multiline_comment|/* all commits older than this on disk*/
DECL|member|j_trans_id
r_int
r_int
id|j_trans_id
suffix:semicolon
DECL|member|j_timestamp
id|time_t
id|j_timestamp
suffix:semicolon
DECL|member|j_list_bitmap
r_struct
id|reiserfs_list_bitmap
op_star
id|j_list_bitmap
suffix:semicolon
DECL|member|j_commit_bh
r_struct
id|buffer_head
op_star
id|j_commit_bh
suffix:semicolon
multiline_comment|/* commit buffer head */
DECL|member|j_realblock
r_struct
id|reiserfs_journal_cnode
op_star
id|j_realblock
suffix:semicolon
DECL|member|j_freedlist
r_struct
id|reiserfs_journal_cnode
op_star
id|j_freedlist
suffix:semicolon
multiline_comment|/* list of buffers that were freed during this trans.  free each of these on flush */
DECL|member|j_commit_wait
id|wait_queue_head_t
id|j_commit_wait
suffix:semicolon
multiline_comment|/* wait for all the commit blocks to be flushed */
DECL|member|j_flush_wait
id|wait_queue_head_t
id|j_flush_wait
suffix:semicolon
multiline_comment|/* wait for all the real blocks to be flushed */
)brace
suffix:semicolon
r_struct
id|reiserfs_page_list
suffix:semicolon
multiline_comment|/* defined in reiserfs_fs.h */
DECL|struct|reiserfs_journal
r_struct
id|reiserfs_journal
(brace
DECL|member|j_ap_blocks
r_struct
id|buffer_head
op_star
op_star
id|j_ap_blocks
suffix:semicolon
multiline_comment|/* journal blocks on disk */
DECL|member|j_last
r_struct
id|reiserfs_journal_cnode
op_star
id|j_last
suffix:semicolon
multiline_comment|/* newest journal block */
DECL|member|j_first
r_struct
id|reiserfs_journal_cnode
op_star
id|j_first
suffix:semicolon
multiline_comment|/*  oldest journal block.  start here for traverse */
DECL|member|j_dev
id|kdev_t
id|j_dev
suffix:semicolon
DECL|member|j_dev_file
r_struct
id|file
op_star
id|j_dev_file
suffix:semicolon
DECL|member|j_dev_bd
r_struct
id|block_device
op_star
id|j_dev_bd
suffix:semicolon
DECL|member|j_1st_reserved_block
r_int
id|j_1st_reserved_block
suffix:semicolon
multiline_comment|/* first block on s_dev of reserved area journal */
DECL|member|j_state
r_int
id|j_state
suffix:semicolon
DECL|member|j_trans_id
r_int
r_int
id|j_trans_id
suffix:semicolon
DECL|member|j_mount_id
r_int
r_int
id|j_mount_id
suffix:semicolon
DECL|member|j_start
r_int
r_int
id|j_start
suffix:semicolon
multiline_comment|/* start of current waiting commit (index into j_ap_blocks) */
DECL|member|j_len
r_int
r_int
id|j_len
suffix:semicolon
multiline_comment|/* lenght of current waiting commit */
DECL|member|j_len_alloc
r_int
r_int
id|j_len_alloc
suffix:semicolon
multiline_comment|/* number of buffers requested by journal_begin() */
DECL|member|j_wcount
id|atomic_t
id|j_wcount
suffix:semicolon
multiline_comment|/* count of writers for current commit */
DECL|member|j_bcount
r_int
r_int
id|j_bcount
suffix:semicolon
multiline_comment|/* batch count. allows turning X transactions into 1 */
DECL|member|j_first_unflushed_offset
r_int
r_int
id|j_first_unflushed_offset
suffix:semicolon
multiline_comment|/* first unflushed transactions offset */
DECL|member|j_last_flush_trans_id
r_int
r_int
id|j_last_flush_trans_id
suffix:semicolon
multiline_comment|/* last fully flushed journal timestamp */
DECL|member|j_header_bh
r_struct
id|buffer_head
op_star
id|j_header_bh
suffix:semicolon
multiline_comment|/* j_flush_pages must be flushed before the current transaction can&n;  ** commit&n;  */
DECL|member|j_flush_pages
r_struct
id|reiserfs_page_list
op_star
id|j_flush_pages
suffix:semicolon
DECL|member|j_trans_start_time
id|time_t
id|j_trans_start_time
suffix:semicolon
multiline_comment|/* time this transaction started */
DECL|member|j_wait
id|wait_queue_head_t
id|j_wait
suffix:semicolon
multiline_comment|/* wait  journal_end to finish I/O */
DECL|member|j_wlock
id|atomic_t
id|j_wlock
suffix:semicolon
multiline_comment|/* lock for j_wait */
DECL|member|j_join_wait
id|wait_queue_head_t
id|j_join_wait
suffix:semicolon
multiline_comment|/* wait for current transaction to finish before starting new one */
DECL|member|j_jlock
id|atomic_t
id|j_jlock
suffix:semicolon
multiline_comment|/* lock for j_join_wait */
DECL|member|j_journal_list_index
r_int
id|j_journal_list_index
suffix:semicolon
multiline_comment|/* journal list number of the current trans */
DECL|member|j_list_bitmap_index
r_int
id|j_list_bitmap_index
suffix:semicolon
multiline_comment|/* number of next list bitmap to use */
DECL|member|j_must_wait
r_int
id|j_must_wait
suffix:semicolon
multiline_comment|/* no more journal begins allowed. MUST sleep on j_join_wait */
DECL|member|j_next_full_flush
r_int
id|j_next_full_flush
suffix:semicolon
multiline_comment|/* next journal_end will flush all journal list */
DECL|member|j_next_async_flush
r_int
id|j_next_async_flush
suffix:semicolon
multiline_comment|/* next journal_end will flush all async commits */
DECL|member|j_cnode_used
r_int
id|j_cnode_used
suffix:semicolon
multiline_comment|/* number of cnodes on the used list */
DECL|member|j_cnode_free
r_int
id|j_cnode_free
suffix:semicolon
multiline_comment|/* number of cnodes on the free list */
DECL|member|s_journal_trans_max
r_int
r_int
id|s_journal_trans_max
suffix:semicolon
multiline_comment|/* max number of blocks in a transaction.  */
DECL|member|s_journal_max_batch
r_int
r_int
id|s_journal_max_batch
suffix:semicolon
multiline_comment|/* max number of blocks to batch into a trans */
DECL|member|s_journal_max_commit_age
r_int
r_int
id|s_journal_max_commit_age
suffix:semicolon
multiline_comment|/* in seconds, how old can an async commit be */
DECL|member|s_journal_max_trans_age
r_int
r_int
id|s_journal_max_trans_age
suffix:semicolon
multiline_comment|/* in seconds, how old can a transaction be */
DECL|member|j_cnode_free_list
r_struct
id|reiserfs_journal_cnode
op_star
id|j_cnode_free_list
suffix:semicolon
DECL|member|j_cnode_free_orig
r_struct
id|reiserfs_journal_cnode
op_star
id|j_cnode_free_orig
suffix:semicolon
multiline_comment|/* orig pointer returned from vmalloc */
DECL|member|j_free_bitmap_nodes
r_int
id|j_free_bitmap_nodes
suffix:semicolon
DECL|member|j_used_bitmap_nodes
r_int
id|j_used_bitmap_nodes
suffix:semicolon
DECL|member|j_bitmap_nodes
r_struct
id|list_head
id|j_bitmap_nodes
suffix:semicolon
DECL|member|j_dirty_buffers
r_struct
id|list_head
id|j_dirty_buffers
suffix:semicolon
DECL|member|j_list_bitmap
r_struct
id|reiserfs_list_bitmap
id|j_list_bitmap
(braket
id|JOURNAL_NUM_BITMAPS
)braket
suffix:semicolon
multiline_comment|/* array of bitmaps to record the deleted blocks */
DECL|member|j_journal_list
r_struct
id|reiserfs_journal_list
id|j_journal_list
(braket
id|JOURNAL_LIST_COUNT
)braket
suffix:semicolon
multiline_comment|/* array of all the journal lists */
DECL|member|j_hash_table
r_struct
id|reiserfs_journal_cnode
op_star
id|j_hash_table
(braket
id|JOURNAL_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/* hash table for real buffer heads in current trans */
DECL|member|j_list_hash_table
r_struct
id|reiserfs_journal_cnode
op_star
id|j_list_hash_table
(braket
id|JOURNAL_HASH_SIZE
)braket
suffix:semicolon
multiline_comment|/* hash table for all the real buffer heads in all &n;  &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;the transactions */
DECL|member|j_prealloc_list
r_struct
id|list_head
id|j_prealloc_list
suffix:semicolon
multiline_comment|/* list of inodes which have preallocated blocks */
)brace
suffix:semicolon
DECL|macro|JOURNAL_DESC_MAGIC
mdefine_line|#define JOURNAL_DESC_MAGIC &quot;ReIsErLB&quot; /* ick.  magic string to find desc blocks in the journal */
DECL|typedef|hashf_t
r_typedef
id|__u32
(paren
op_star
id|hashf_t
)paren
(paren
r_const
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|proc_dir_entry
suffix:semicolon
macro_line|#if defined( CONFIG_PROC_FS ) &amp;&amp; defined( CONFIG_REISERFS_PROC_INFO )
DECL|typedef|stat_cnt_t
r_typedef
r_int
r_int
r_int
id|stat_cnt_t
suffix:semicolon
DECL|struct|reiserfs_proc_info_data
r_typedef
r_struct
id|reiserfs_proc_info_data
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|exiting
r_int
id|exiting
suffix:semicolon
DECL|member|max_hash_collisions
r_int
id|max_hash_collisions
suffix:semicolon
DECL|member|breads
id|stat_cnt_t
id|breads
suffix:semicolon
DECL|member|bread_miss
id|stat_cnt_t
id|bread_miss
suffix:semicolon
DECL|member|search_by_key
id|stat_cnt_t
id|search_by_key
suffix:semicolon
DECL|member|search_by_key_fs_changed
id|stat_cnt_t
id|search_by_key_fs_changed
suffix:semicolon
DECL|member|search_by_key_restarted
id|stat_cnt_t
id|search_by_key_restarted
suffix:semicolon
DECL|member|leaked_oid
id|stat_cnt_t
id|leaked_oid
suffix:semicolon
DECL|member|leaves_removable
id|stat_cnt_t
id|leaves_removable
suffix:semicolon
multiline_comment|/* balances per level. Use explicit 5 as MAX_HEIGHT is not visible yet. */
DECL|member|balance_at
id|stat_cnt_t
id|balance_at
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
multiline_comment|/* sbk == search_by_key */
DECL|member|sbk_read_at
id|stat_cnt_t
id|sbk_read_at
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|sbk_fs_changed
id|stat_cnt_t
id|sbk_fs_changed
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|sbk_restarted
id|stat_cnt_t
id|sbk_restarted
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|items_at
id|stat_cnt_t
id|items_at
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|free_at
id|stat_cnt_t
id|free_at
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|can_node_be_removed
id|stat_cnt_t
id|can_node_be_removed
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|lnum
r_int
r_int
id|lnum
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|rnum
r_int
r_int
id|rnum
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|lbytes
r_int
r_int
id|lbytes
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|rbytes
r_int
r_int
id|rbytes
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|get_neighbors
id|stat_cnt_t
id|get_neighbors
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|get_neighbors_restart
id|stat_cnt_t
id|get_neighbors_restart
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|need_l_neighbor
id|stat_cnt_t
id|need_l_neighbor
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|need_r_neighbor
id|stat_cnt_t
id|need_r_neighbor
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|free_block
id|stat_cnt_t
id|free_block
suffix:semicolon
DECL|struct|__find_forward_stats
r_struct
id|__find_forward_stats
(brace
DECL|member|call
id|stat_cnt_t
id|call
suffix:semicolon
DECL|member|wait
id|stat_cnt_t
id|wait
suffix:semicolon
DECL|member|bmap
id|stat_cnt_t
id|bmap
suffix:semicolon
DECL|member|retry
id|stat_cnt_t
id|retry
suffix:semicolon
DECL|member|in_journal_hint
id|stat_cnt_t
id|in_journal_hint
suffix:semicolon
DECL|member|in_journal_out
id|stat_cnt_t
id|in_journal_out
suffix:semicolon
DECL|member|find_forward
)brace
id|find_forward
suffix:semicolon
DECL|struct|__journal_stats
r_struct
id|__journal_stats
(brace
DECL|member|in_journal
id|stat_cnt_t
id|in_journal
suffix:semicolon
DECL|member|in_journal_bitmap
id|stat_cnt_t
id|in_journal_bitmap
suffix:semicolon
DECL|member|in_journal_reusable
id|stat_cnt_t
id|in_journal_reusable
suffix:semicolon
DECL|member|lock_journal
id|stat_cnt_t
id|lock_journal
suffix:semicolon
DECL|member|lock_journal_wait
id|stat_cnt_t
id|lock_journal_wait
suffix:semicolon
DECL|member|journal_being
id|stat_cnt_t
id|journal_being
suffix:semicolon
DECL|member|journal_relock_writers
id|stat_cnt_t
id|journal_relock_writers
suffix:semicolon
DECL|member|journal_relock_wcount
id|stat_cnt_t
id|journal_relock_wcount
suffix:semicolon
DECL|member|mark_dirty
id|stat_cnt_t
id|mark_dirty
suffix:semicolon
DECL|member|mark_dirty_already
id|stat_cnt_t
id|mark_dirty_already
suffix:semicolon
DECL|member|mark_dirty_notjournal
id|stat_cnt_t
id|mark_dirty_notjournal
suffix:semicolon
DECL|member|restore_prepared
id|stat_cnt_t
id|restore_prepared
suffix:semicolon
DECL|member|prepare
id|stat_cnt_t
id|prepare
suffix:semicolon
DECL|member|prepare_retry
id|stat_cnt_t
id|prepare_retry
suffix:semicolon
DECL|member|journal
)brace
id|journal
suffix:semicolon
DECL|typedef|reiserfs_proc_info_data_t
)brace
id|reiserfs_proc_info_data_t
suffix:semicolon
macro_line|#else
DECL|struct|reiserfs_proc_info_data
r_typedef
r_struct
id|reiserfs_proc_info_data
DECL|typedef|reiserfs_proc_info_data_t
(brace
)brace
id|reiserfs_proc_info_data_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* reiserfs union of in-core super block data */
DECL|struct|reiserfs_sb_info
r_struct
id|reiserfs_sb_info
(brace
DECL|member|s_sbh
r_struct
id|buffer_head
op_star
id|s_sbh
suffix:semicolon
multiline_comment|/* Buffer containing the super block */
multiline_comment|/* both the comment and the choice of&n;                                   name are unclear for s_rs -Hans */
DECL|member|s_rs
r_struct
id|reiserfs_super_block
op_star
id|s_rs
suffix:semicolon
multiline_comment|/* Pointer to the super block in the buffer */
DECL|member|s_ap_bitmap
r_struct
id|buffer_head
op_star
op_star
id|s_ap_bitmap
suffix:semicolon
multiline_comment|/* array of buffers, holding block bitmap */
DECL|member|s_journal
r_struct
id|reiserfs_journal
op_star
id|s_journal
suffix:semicolon
multiline_comment|/* pointer to journal information */
DECL|member|s_mount_state
r_int
r_int
id|s_mount_state
suffix:semicolon
multiline_comment|/* reiserfs state (valid, invalid) */
multiline_comment|/* Comment? -Hans */
DECL|member|end_io_handler
r_void
(paren
op_star
id|end_io_handler
)paren
(paren
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|s_hash_function
id|hashf_t
id|s_hash_function
suffix:semicolon
multiline_comment|/* pointer to function which is used&n;                                   to sort names in directory. Set on&n;                                   mount */
DECL|member|s_mount_opt
r_int
r_int
id|s_mount_opt
suffix:semicolon
multiline_comment|/* reiserfs&squot;s mount options are set&n;                                   here (currently - NOTAIL, NOLOG,&n;                                   REPLAYONLY) */
multiline_comment|/* Comment? -Hans */
DECL|member|s_wait
id|wait_queue_head_t
id|s_wait
suffix:semicolon
multiline_comment|/* To be obsoleted soon by per buffer seals.. -Hans */
DECL|member|s_generation_counter
id|atomic_t
id|s_generation_counter
suffix:semicolon
singleline_comment|// increased by one every time the
singleline_comment|// tree gets re-balanced
DECL|member|s_properties
r_int
r_int
id|s_properties
suffix:semicolon
multiline_comment|/* File system properties. Currently holds&n;&t;&t;&t;&t;     on-disk FS format */
multiline_comment|/* session statistics */
DECL|member|s_kmallocs
r_int
id|s_kmallocs
suffix:semicolon
DECL|member|s_disk_reads
r_int
id|s_disk_reads
suffix:semicolon
DECL|member|s_disk_writes
r_int
id|s_disk_writes
suffix:semicolon
DECL|member|s_fix_nodes
r_int
id|s_fix_nodes
suffix:semicolon
DECL|member|s_do_balance
r_int
id|s_do_balance
suffix:semicolon
DECL|member|s_unneeded_left_neighbor
r_int
id|s_unneeded_left_neighbor
suffix:semicolon
DECL|member|s_good_search_by_key_reada
r_int
id|s_good_search_by_key_reada
suffix:semicolon
DECL|member|s_bmaps
r_int
id|s_bmaps
suffix:semicolon
DECL|member|s_bmaps_without_search
r_int
id|s_bmaps_without_search
suffix:semicolon
DECL|member|s_direct2indirect
r_int
id|s_direct2indirect
suffix:semicolon
DECL|member|s_indirect2direct
r_int
id|s_indirect2direct
suffix:semicolon
multiline_comment|/* set up when it&squot;s ok for reiserfs_read_inode2() to read from&n;&t;   disk inode with nlink==0. Currently this is only used during&n;&t;   finish_unfinished() processing at mount time */
DECL|member|s_is_unlinked_ok
r_int
id|s_is_unlinked_ok
suffix:semicolon
DECL|member|s_proc_info_data
id|reiserfs_proc_info_data_t
id|s_proc_info_data
suffix:semicolon
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Definitions of reiserfs on-disk properties: */
DECL|macro|REISERFS_3_5
mdefine_line|#define REISERFS_3_5 0
DECL|macro|REISERFS_3_6
mdefine_line|#define REISERFS_3_6 1
multiline_comment|/* Mount options */
DECL|macro|NOTAIL
mdefine_line|#define NOTAIL 0  /* -o notail: no tails will be created in a session */
DECL|macro|REPLAYONLY
mdefine_line|#define REPLAYONLY 3 /* replay journal and return 0. Use by fsck */
DECL|macro|REISERFS_NOLOG
mdefine_line|#define REISERFS_NOLOG 4      /* -o nolog: turn journalling off */
DECL|macro|REISERFS_CONVERT
mdefine_line|#define REISERFS_CONVERT 5    /* -o conv: causes conversion of old&n;                                 format super block to the new&n;                                 format. If not specified - old&n;                                 partition will be dealt with in a&n;                                 manner of 3.5.x */
multiline_comment|/* -o hash={tea, rupasov, r5, detect} is meant for properly mounting &n;** reiserfs disks from 3.5.19 or earlier.  99% of the time, this option&n;** is not required.  If the normal autodection code can&squot;t determine which&n;** hash to use (because both hases had the same value for a file)&n;** use this option to force a specific hash.  It won&squot;t allow you to override&n;** the existing hash on the FS, so if you have a tea hash disk, and mount&n;** with -o hash=rupasov, the mount will fail.&n;*/
DECL|macro|FORCE_TEA_HASH
mdefine_line|#define FORCE_TEA_HASH 6      /* try to force tea hash on mount */
DECL|macro|FORCE_RUPASOV_HASH
mdefine_line|#define FORCE_RUPASOV_HASH 7  /* try to force rupasov hash on mount */
DECL|macro|FORCE_R5_HASH
mdefine_line|#define FORCE_R5_HASH 8       /* try to force rupasov hash on mount */
DECL|macro|FORCE_HASH_DETECT
mdefine_line|#define FORCE_HASH_DETECT 9   /* try to detect hash function on mount */
multiline_comment|/* used for testing experimental features, makes benchmarking new&n;   features with and without more convenient, should never be used by&n;   users in any code shipped to users (ideally) */
DECL|macro|REISERFS_NO_BORDER
mdefine_line|#define REISERFS_NO_BORDER 11
DECL|macro|REISERFS_NO_UNHASHED_RELOCATION
mdefine_line|#define REISERFS_NO_UNHASHED_RELOCATION 12
DECL|macro|REISERFS_HASHED_RELOCATION
mdefine_line|#define REISERFS_HASHED_RELOCATION 13
DECL|macro|REISERFS_TEST4
mdefine_line|#define REISERFS_TEST4 14 
DECL|macro|REISERFS_TEST1
mdefine_line|#define REISERFS_TEST1 11
DECL|macro|REISERFS_TEST2
mdefine_line|#define REISERFS_TEST2 12
DECL|macro|REISERFS_TEST3
mdefine_line|#define REISERFS_TEST3 13
DECL|macro|REISERFS_TEST4
mdefine_line|#define REISERFS_TEST4 14 
DECL|macro|reiserfs_r5_hash
mdefine_line|#define reiserfs_r5_hash(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; FORCE_R5_HASH))
DECL|macro|reiserfs_rupasov_hash
mdefine_line|#define reiserfs_rupasov_hash(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; FORCE_RUPASOV_HASH))
DECL|macro|reiserfs_tea_hash
mdefine_line|#define reiserfs_tea_hash(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; FORCE_TEA_HASH))
DECL|macro|reiserfs_hash_detect
mdefine_line|#define reiserfs_hash_detect(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; FORCE_HASH_DETECT))
DECL|macro|reiserfs_no_border
mdefine_line|#define reiserfs_no_border(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_NO_BORDER))
DECL|macro|reiserfs_no_unhashed_relocation
mdefine_line|#define reiserfs_no_unhashed_relocation(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_NO_UNHASHED_RELOCATION))
DECL|macro|reiserfs_hashed_relocation
mdefine_line|#define reiserfs_hashed_relocation(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_HASHED_RELOCATION))
DECL|macro|reiserfs_test4
mdefine_line|#define reiserfs_test4(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_TEST4))
DECL|macro|dont_have_tails
mdefine_line|#define dont_have_tails(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; NOTAIL))
DECL|macro|replay_only
mdefine_line|#define replay_only(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REPLAYONLY))
DECL|macro|reiserfs_dont_log
mdefine_line|#define reiserfs_dont_log(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_NOLOG))
DECL|macro|old_format_only
mdefine_line|#define old_format_only(s) (REISERFS_SB(s)-&gt;s_properties &amp; (1 &lt;&lt; REISERFS_3_5))
DECL|macro|convert_reiserfs
mdefine_line|#define convert_reiserfs(s) (REISERFS_SB(s)-&gt;s_mount_opt &amp; (1 &lt;&lt; REISERFS_CONVERT))
r_void
id|reiserfs_file_buffer
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|list
)paren
suffix:semicolon
r_int
id|reiserfs_is_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_int
id|journal_mark_dirty
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|flush_old_commits
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
)paren
suffix:semicolon
r_int
id|show_reiserfs_locks
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|reiserfs_resize
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|CARRY_ON
mdefine_line|#define CARRY_ON                0
DECL|macro|SCHEDULE_OCCURRED
mdefine_line|#define SCHEDULE_OCCURRED       1
DECL|macro|SB_BUFFER_WITH_SB
mdefine_line|#define SB_BUFFER_WITH_SB(s) (REISERFS_SB(s)-&gt;s_sbh)
DECL|macro|SB_JOURNAL
mdefine_line|#define SB_JOURNAL(s) (REISERFS_SB(s)-&gt;s_journal)
DECL|macro|SB_JOURNAL_1st_RESERVED_BLOCK
mdefine_line|#define SB_JOURNAL_1st_RESERVED_BLOCK(s) (SB_JOURNAL(s)-&gt;j_1st_reserved_block)
DECL|macro|SB_JOURNAL_LIST
mdefine_line|#define SB_JOURNAL_LIST(s) (SB_JOURNAL(s)-&gt;j_journal_list)
DECL|macro|SB_JOURNAL_LIST_INDEX
mdefine_line|#define SB_JOURNAL_LIST_INDEX(s) (SB_JOURNAL(s)-&gt;j_journal_list_index) 
DECL|macro|SB_JOURNAL_LEN_FREE
mdefine_line|#define SB_JOURNAL_LEN_FREE(s) (SB_JOURNAL(s)-&gt;j_journal_len_free) 
DECL|macro|SB_AP_BITMAP
mdefine_line|#define SB_AP_BITMAP(s) (REISERFS_SB(s)-&gt;s_ap_bitmap)
DECL|macro|SB_DISK_JOURNAL_HEAD
mdefine_line|#define SB_DISK_JOURNAL_HEAD(s) (SB_JOURNAL(s)-&gt;j_header_bh-&gt;)
DECL|macro|SB_JOURNAL_TRANS_MAX
mdefine_line|#define SB_JOURNAL_TRANS_MAX(s)      (SB_JOURNAL(s)-&gt;s_journal_trans_max)
DECL|macro|SB_JOURNAL_MAX_BATCH
mdefine_line|#define SB_JOURNAL_MAX_BATCH(s)      (SB_JOURNAL(s)-&gt;s_journal_max_batch)
DECL|macro|SB_JOURNAL_MAX_COMMIT_AGE
mdefine_line|#define SB_JOURNAL_MAX_COMMIT_AGE(s) (SB_JOURNAL(s)-&gt;s_journal_max_commit_age)
DECL|macro|SB_JOURNAL_MAX_TRANS_AGE
mdefine_line|#define SB_JOURNAL_MAX_TRANS_AGE(s)  (SB_JOURNAL(s)-&gt;s_journal_max_trans_age)
DECL|macro|SB_JOURNAL_DEV
mdefine_line|#define SB_JOURNAL_DEV(s)            (SB_JOURNAL(s)-&gt;j_dev)
macro_line|#endif&t;/* _LINUX_REISER_FS_SB */
eof
