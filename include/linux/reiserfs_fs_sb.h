multiline_comment|/* Copyright 1996-2000 Hans Reiser, see reiserfs/README for licensing&n; * and copyright details */
macro_line|#ifndef _LINUX_REISER_FS_SB
DECL|macro|_LINUX_REISER_FS_SB
mdefine_line|#define _LINUX_REISER_FS_SB
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#endif
singleline_comment|//
singleline_comment|// super block&squot;s field values
singleline_comment|//
multiline_comment|/*#define REISERFS_VERSION 0 undistributed bitmap */
multiline_comment|/*#define REISERFS_VERSION 1 distributed bitmap and resizer*/
DECL|macro|REISERFS_VERSION_2
mdefine_line|#define REISERFS_VERSION_2 2 /* distributed bitmap, resizer, 64-bit, etc*/
DECL|macro|UNSET_HASH
mdefine_line|#define UNSET_HASH 0 
singleline_comment|// read_super will guess about, what hash names
singleline_comment|// in directories were sorted with
DECL|macro|TEA_HASH
mdefine_line|#define TEA_HASH  1
DECL|macro|YURA_HASH
mdefine_line|#define YURA_HASH 2
DECL|macro|R5_HASH
mdefine_line|#define R5_HASH   3
DECL|macro|DEFAULT_HASH
mdefine_line|#define DEFAULT_HASH R5_HASH
multiline_comment|/* this is the on disk super block */
DECL|struct|reiserfs_super_block
r_struct
id|reiserfs_super_block
(brace
DECL|member|s_block_count
id|__u32
id|s_block_count
suffix:semicolon
DECL|member|s_free_blocks
id|__u32
id|s_free_blocks
suffix:semicolon
multiline_comment|/* free blocks count    */
DECL|member|s_root_block
id|__u32
id|s_root_block
suffix:semicolon
multiline_comment|/* root block number    */
DECL|member|s_journal_block
id|__u32
id|s_journal_block
suffix:semicolon
multiline_comment|/* journal block number    */
DECL|member|s_journal_dev
id|__u32
id|s_journal_dev
suffix:semicolon
multiline_comment|/* journal device number  */
multiline_comment|/* Since journal size is currently a #define in a header file, if &n;  ** someone creates a disk with a 16MB journal and moves it to a &n;  ** system with 32MB journal default, they will overflow their journal &n;  ** when they mount the disk.  s_orig_journal_size, plus some checks&n;  ** while mounting (inside journal_init) prevent that from happening&n;  */
multiline_comment|/* great comment Chris. Thanks.  -Hans */
DECL|member|s_orig_journal_size
id|__u32
id|s_orig_journal_size
suffix:semicolon
DECL|member|s_journal_trans_max
id|__u32
id|s_journal_trans_max
suffix:semicolon
multiline_comment|/* max number of blocks in a transaction.  */
DECL|member|s_journal_block_count
id|__u32
id|s_journal_block_count
suffix:semicolon
multiline_comment|/* total size of the journal. can change over time  */
DECL|member|s_journal_max_batch
id|__u32
id|s_journal_max_batch
suffix:semicolon
multiline_comment|/* max number of blocks to batch into a trans */
DECL|member|s_journal_max_commit_age
id|__u32
id|s_journal_max_commit_age
suffix:semicolon
multiline_comment|/* in seconds, how old can an async commit be */
DECL|member|s_journal_max_trans_age
id|__u32
id|s_journal_max_trans_age
suffix:semicolon
multiline_comment|/* in seconds, how old can a transaction be */
DECL|member|s_blocksize
id|__u16
id|s_blocksize
suffix:semicolon
multiline_comment|/* block size           */
DECL|member|s_oid_maxsize
id|__u16
id|s_oid_maxsize
suffix:semicolon
multiline_comment|/* max size of object id array, see get_objectid() commentary  */
DECL|member|s_oid_cursize
id|__u16
id|s_oid_cursize
suffix:semicolon
multiline_comment|/* current size of object id array */
DECL|member|s_state
id|__u16
id|s_state
suffix:semicolon
multiline_comment|/* valid or error       */
DECL|member|s_magic
r_char
id|s_magic
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* reiserfs magic string indicates that file system is reiserfs */
DECL|member|s_hash_function_code
id|__u32
id|s_hash_function_code
suffix:semicolon
multiline_comment|/* indicate, what hash function is being use to sort names in a directory*/
DECL|member|s_tree_height
id|__u16
id|s_tree_height
suffix:semicolon
multiline_comment|/* height of disk tree */
DECL|member|s_bmap_nr
id|__u16
id|s_bmap_nr
suffix:semicolon
multiline_comment|/* amount of bitmap blocks needed to address each block of file system */
DECL|member|s_version
id|__u16
id|s_version
suffix:semicolon
multiline_comment|/* I&squot;d prefer it if this was a string,&n;                                   something like &quot;3.6.4&quot;, and maybe&n;                                   16 bytes long mostly unused. We&n;                                   don&squot;t need to save bytes in the&n;                                   superblock. -Hans */
DECL|member|s_reserved
id|__u16
id|s_reserved
suffix:semicolon
DECL|member|s_unused
r_char
id|s_unused
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* zero filled by mkreiserfs */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|SB_SIZE
mdefine_line|#define SB_SIZE (sizeof(struct reiserfs_super_block))
multiline_comment|/* this is the super from 3.5.X, where X &gt;= 10 */
DECL|struct|reiserfs_super_block_v1
r_struct
id|reiserfs_super_block_v1
(brace
DECL|member|s_block_count
id|__u32
id|s_block_count
suffix:semicolon
multiline_comment|/* blocks count         */
DECL|member|s_free_blocks
id|__u32
id|s_free_blocks
suffix:semicolon
multiline_comment|/* free blocks count    */
DECL|member|s_root_block
id|__u32
id|s_root_block
suffix:semicolon
multiline_comment|/* root block number    */
DECL|member|s_journal_block
id|__u32
id|s_journal_block
suffix:semicolon
multiline_comment|/* journal block number    */
DECL|member|s_journal_dev
id|__u32
id|s_journal_dev
suffix:semicolon
multiline_comment|/* journal device number  */
DECL|member|s_orig_journal_size
id|__u32
id|s_orig_journal_size
suffix:semicolon
multiline_comment|/* size of the journal on FS creation.  used to make sure they don&squot;t overflow it */
DECL|member|s_journal_trans_max
id|__u32
id|s_journal_trans_max
suffix:semicolon
multiline_comment|/* max number of blocks in a transaction.  */
DECL|member|s_journal_block_count
id|__u32
id|s_journal_block_count
suffix:semicolon
multiline_comment|/* total size of the journal. can change over time  */
DECL|member|s_journal_max_batch
id|__u32
id|s_journal_max_batch
suffix:semicolon
multiline_comment|/* max number of blocks to batch into a trans */
DECL|member|s_journal_max_commit_age
id|__u32
id|s_journal_max_commit_age
suffix:semicolon
multiline_comment|/* in seconds, how old can an async commit be */
DECL|member|s_journal_max_trans_age
id|__u32
id|s_journal_max_trans_age
suffix:semicolon
multiline_comment|/* in seconds, how old can a transaction be */
DECL|member|s_blocksize
id|__u16
id|s_blocksize
suffix:semicolon
multiline_comment|/* block size           */
DECL|member|s_oid_maxsize
id|__u16
id|s_oid_maxsize
suffix:semicolon
multiline_comment|/* max size of object id array, see get_objectid() commentary  */
DECL|member|s_oid_cursize
id|__u16
id|s_oid_cursize
suffix:semicolon
multiline_comment|/* current size of object id array */
DECL|member|s_state
id|__u16
id|s_state
suffix:semicolon
multiline_comment|/* valid or error       */
DECL|member|s_magic
r_char
id|s_magic
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reiserfs magic string indicates that file system is reiserfs */
DECL|member|s_tree_height
id|__u16
id|s_tree_height
suffix:semicolon
multiline_comment|/* height of disk tree */
DECL|member|s_bmap_nr
id|__u16
id|s_bmap_nr
suffix:semicolon
multiline_comment|/* amount of bitmap blocks needed to address each block of file system */
DECL|member|s_reserved
id|__u32
id|s_reserved
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|SB_SIZE_V1
mdefine_line|#define SB_SIZE_V1 (sizeof(struct reiserfs_super_block_v1))
multiline_comment|/* LOGGING -- */
multiline_comment|/* These all interelate for performance.  &n;**&n;** If the journal block count is smaller than n transactions, you lose speed. &n;** I don&squot;t know what n is yet, I&squot;m guessing 8-16.&n;**&n;** typical transaction size depends on the application, how often fsync is&n;** called, and how many metadata blocks you dirty in a 30 second period.  &n;** The more small files (&lt;16k) you use, the larger your transactions will&n;** be.&n;** &n;** If your journal fills faster than dirty buffers get flushed to disk, it must flush them before allowing the journal&n;** to wrap, which slows things down.  If you need high speed meta data updates, the journal should be big enough&n;** to prevent wrapping before dirty meta blocks get to disk.&n;**&n;** If the batch max is smaller than the transaction max, you&squot;ll waste space at the end of the journal&n;** because journal_end sets the next transaction to start at 0 if the next transaction has any chance of wrapping.&n;**&n;** The large the batch max age, the better the speed, and the more meta data changes you&squot;ll lose after a crash.&n;**&n;*/
multiline_comment|/* don&squot;t mess with these for a while */
multiline_comment|/* we have a node size define somewhere in reiserfs_fs.h. -Hans */
DECL|macro|JOURNAL_BLOCK_SIZE
mdefine_line|#define JOURNAL_BLOCK_SIZE  4096 /* BUG gotta get rid of this */
DECL|macro|JOURNAL_MAX_CNODE
mdefine_line|#define JOURNAL_MAX_CNODE   1500 /* max cnodes to allocate. */
DECL|macro|JOURNAL_TRANS_MAX
mdefine_line|#define JOURNAL_TRANS_MAX 1024   /* biggest possible single transaction, don&squot;t change for now (8/3/99) */
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
DECL|member|dev
id|kdev_t
id|dev
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
r_char
op_star
comma
r_int
)paren
suffix:semicolon
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
)brace
suffix:semicolon
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
mdefine_line|#define reiserfs_r5_hash(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; FORCE_R5_HASH))
DECL|macro|reiserfs_rupasov_hash
mdefine_line|#define reiserfs_rupasov_hash(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; FORCE_RUPASOV_HASH))
DECL|macro|reiserfs_tea_hash
mdefine_line|#define reiserfs_tea_hash(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; FORCE_TEA_HASH))
DECL|macro|reiserfs_hash_detect
mdefine_line|#define reiserfs_hash_detect(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; FORCE_HASH_DETECT))
DECL|macro|reiserfs_no_border
mdefine_line|#define reiserfs_no_border(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_NO_BORDER))
DECL|macro|reiserfs_no_unhashed_relocation
mdefine_line|#define reiserfs_no_unhashed_relocation(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_NO_UNHASHED_RELOCATION))
DECL|macro|reiserfs_hashed_relocation
mdefine_line|#define reiserfs_hashed_relocation(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_HASHED_RELOCATION))
DECL|macro|reiserfs_test4
mdefine_line|#define reiserfs_test4(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_TEST4))
DECL|macro|dont_have_tails
mdefine_line|#define dont_have_tails(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; NOTAIL))
DECL|macro|replay_only
mdefine_line|#define replay_only(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REPLAYONLY))
DECL|macro|reiserfs_dont_log
mdefine_line|#define reiserfs_dont_log(s) ((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_NOLOG))
DECL|macro|old_format_only
mdefine_line|#define old_format_only(s) ((SB_VERSION(s) != REISERFS_VERSION_2) &amp;&amp; !((s)-&gt;u.reiserfs_sb.s_mount_opt &amp; (1 &lt;&lt; REISERFS_CONVERT)))
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
mdefine_line|#define SB_BUFFER_WITH_SB(s) ((s)-&gt;u.reiserfs_sb.s_sbh)
DECL|macro|SB_JOURNAL
mdefine_line|#define SB_JOURNAL(s) ((s)-&gt;u.reiserfs_sb.s_journal)
DECL|macro|SB_JOURNAL_LIST
mdefine_line|#define SB_JOURNAL_LIST(s) (SB_JOURNAL(s)-&gt;j_journal_list)
DECL|macro|SB_JOURNAL_LIST_INDEX
mdefine_line|#define SB_JOURNAL_LIST_INDEX(s) (SB_JOURNAL(s)-&gt;j_journal_list_index) 
DECL|macro|SB_JOURNAL_LEN_FREE
mdefine_line|#define SB_JOURNAL_LEN_FREE(s) (SB_JOURNAL(s)-&gt;j_journal_len_free) 
DECL|macro|SB_AP_BITMAP
mdefine_line|#define SB_AP_BITMAP(s) ((s)-&gt;u.reiserfs_sb.s_ap_bitmap)
singleline_comment|// on-disk super block fields converted to cpu form
DECL|macro|SB_DISK_SUPER_BLOCK
mdefine_line|#define SB_DISK_SUPER_BLOCK(s) ((s)-&gt;u.reiserfs_sb.s_rs)
DECL|macro|SB_BLOCK_COUNT
mdefine_line|#define SB_BLOCK_COUNT(s) le32_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_block_count))
DECL|macro|SB_FREE_BLOCKS
mdefine_line|#define SB_FREE_BLOCKS(s) le32_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_free_blocks))
DECL|macro|SB_REISERFS_MAGIC
mdefine_line|#define SB_REISERFS_MAGIC(s) (SB_DISK_SUPER_BLOCK(s)-&gt;s_magic)
DECL|macro|SB_ROOT_BLOCK
mdefine_line|#define SB_ROOT_BLOCK(s) le32_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_root_block))
DECL|macro|SB_TREE_HEIGHT
mdefine_line|#define SB_TREE_HEIGHT(s) le16_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_tree_height))
DECL|macro|SB_REISERFS_STATE
mdefine_line|#define SB_REISERFS_STATE(s) le16_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_state))
DECL|macro|SB_VERSION
mdefine_line|#define SB_VERSION(s) le16_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_version))
DECL|macro|SB_BMAP_NR
mdefine_line|#define SB_BMAP_NR(s) le16_to_cpu ((SB_DISK_SUPER_BLOCK(s)-&gt;s_bmap_nr))
DECL|macro|PUT_SB_BLOCK_COUNT
mdefine_line|#define PUT_SB_BLOCK_COUNT(s, val)    do { SB_DISK_SUPER_BLOCK(s)-&gt;s_block_count = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_FREE_BLOCKS
mdefine_line|#define PUT_SB_FREE_BLOCKS(s, val)    do { SB_DISK_SUPER_BLOCK(s)-&gt;s_free_blocks = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_ROOT_BLOCK
mdefine_line|#define PUT_SB_ROOT_BLOCK(s, val)     do { SB_DISK_SUPER_BLOCK(s)-&gt;s_root_block = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_TREE_HEIGHT
mdefine_line|#define PUT_SB_TREE_HEIGHT(s, val)    do { SB_DISK_SUPER_BLOCK(s)-&gt;s_tree_height = cpu_to_le16(val); } while (0)
DECL|macro|PUT_SB_REISERFS_STATE
mdefine_line|#define PUT_SB_REISERFS_STATE(s, val) do { SB_DISK_SUPER_BLOCK(s)-&gt;s_state = cpu_to_le16(val); } while (0) 
DECL|macro|PUT_SB_VERSION
mdefine_line|#define PUT_SB_VERSION(s, val)        do { SB_DISK_SUPER_BLOCK(s)-&gt;s_version = cpu_to_le16(val); } while (0)
DECL|macro|PUT_SB_BMAP_NR
mdefine_line|#define PUT_SB_BMAP_NR(s, val)           do { SB_DISK_SUPER_BLOCK(s)-&gt;s_bmap_nr = cpu_to_le16 (val); } while (0)
macro_line|#endif&t;/* _LINUX_REISER_FS_SB */
eof
