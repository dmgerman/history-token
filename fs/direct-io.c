multiline_comment|/*&n; * fs/direct-io.c&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * O_DIRECT&n; *&n; * 04Jul2002&t;akpm@zip.com.au&n; *&t;&t;Initial version&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * The largest-sized BIO which this code will assemble, in bytes.  Set this&n; * to PAGE_SIZE if your drivers are broken.&n; */
DECL|macro|DIO_BIO_MAX_SIZE
mdefine_line|#define DIO_BIO_MAX_SIZE (16*1024)
multiline_comment|/*&n; * How many user pages to map in one call to get_user_pages().  This determines&n; * the size of a structure on the stack.&n; */
DECL|macro|DIO_PAGES
mdefine_line|#define DIO_PAGES&t;64
DECL|struct|dio
r_struct
id|dio
(brace
multiline_comment|/* BIO submission state */
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
multiline_comment|/* bio under assembly */
DECL|member|bvec
r_struct
id|bio_vec
op_star
id|bvec
suffix:semicolon
multiline_comment|/* current bvec in that bio */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|rw
r_int
id|rw
suffix:semicolon
DECL|member|blkbits
r_int
id|blkbits
suffix:semicolon
multiline_comment|/* doesn&squot;t change */
DECL|member|block_in_file
id|sector_t
id|block_in_file
suffix:semicolon
multiline_comment|/* changes */
DECL|member|blocks_available
r_int
id|blocks_available
suffix:semicolon
multiline_comment|/* At block_in_file.  changes */
DECL|member|final_block_in_request
id|sector_t
id|final_block_in_request
suffix:semicolon
multiline_comment|/* doesn&squot;t change */
DECL|member|first_block_in_page
r_int
id|first_block_in_page
suffix:semicolon
multiline_comment|/* doesn&squot;t change, Used only once */
DECL|member|boundary
r_int
id|boundary
suffix:semicolon
multiline_comment|/* prev block is at a boundary */
DECL|member|reap_counter
r_int
id|reap_counter
suffix:semicolon
multiline_comment|/* rate limit reaping */
DECL|member|get_blocks
id|get_blocks_t
op_star
id|get_blocks
suffix:semicolon
multiline_comment|/* block mapping function */
DECL|member|last_block_in_bio
id|sector_t
id|last_block_in_bio
suffix:semicolon
multiline_comment|/* current final block in bio */
DECL|member|next_block_in_bio
id|sector_t
id|next_block_in_bio
suffix:semicolon
multiline_comment|/* next block to be added to bio */
DECL|member|map_bh
r_struct
id|buffer_head
id|map_bh
suffix:semicolon
multiline_comment|/* last get_blocks() result */
multiline_comment|/* Page fetching state */
DECL|member|curr_page
r_int
id|curr_page
suffix:semicolon
multiline_comment|/* changes */
DECL|member|total_pages
r_int
id|total_pages
suffix:semicolon
multiline_comment|/* doesn&squot;t change */
DECL|member|curr_user_address
r_int
r_int
id|curr_user_address
suffix:semicolon
multiline_comment|/* changes */
multiline_comment|/* Page queue */
DECL|member|pages
r_struct
id|page
op_star
id|pages
(braket
id|DIO_PAGES
)braket
suffix:semicolon
multiline_comment|/* page buffer */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* next page to process */
DECL|member|tail
r_int
id|tail
suffix:semicolon
multiline_comment|/* last valid page + 1 */
DECL|member|page_errors
r_int
id|page_errors
suffix:semicolon
multiline_comment|/* errno from get_user_pages() */
multiline_comment|/* BIO completion state */
DECL|member|bio_count
id|atomic_t
id|bio_count
suffix:semicolon
multiline_comment|/* nr bios in flight */
DECL|member|bio_list_lock
id|spinlock_t
id|bio_list_lock
suffix:semicolon
multiline_comment|/* protects bio_list */
DECL|member|bio_list
r_struct
id|bio
op_star
id|bio_list
suffix:semicolon
multiline_comment|/* singly linked via bi_private */
DECL|member|waiter
r_struct
id|task_struct
op_star
id|waiter
suffix:semicolon
multiline_comment|/* waiting task (NULL if none) */
)brace
suffix:semicolon
multiline_comment|/*&n; * How many pages are in the queue?&n; */
DECL|function|dio_pages_present
r_static
r_inline
r_int
id|dio_pages_present
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_return
id|dio-&gt;tail
op_minus
id|dio-&gt;head
suffix:semicolon
)brace
multiline_comment|/*&n; * Go grab and pin some userspace pages.   Typically we&squot;ll get 64 at a time.&n; */
DECL|function|dio_refill_pages
r_static
r_int
id|dio_refill_pages
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|nr_pages
suffix:semicolon
id|nr_pages
op_assign
id|min
c_func
(paren
id|dio-&gt;total_pages
op_minus
id|dio-&gt;curr_page
comma
id|DIO_PAGES
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|get_user_pages
c_func
(paren
id|current
comma
multiline_comment|/* Task for fault acounting */
id|current-&gt;mm
comma
multiline_comment|/* whose pages? */
id|dio-&gt;curr_user_address
comma
multiline_comment|/* Where from? */
id|nr_pages
comma
multiline_comment|/* How many pages? */
id|dio-&gt;rw
op_eq
id|READ
comma
multiline_comment|/* Write to memory? */
l_int|0
comma
multiline_comment|/* force (?) */
op_amp
id|dio-&gt;pages
(braket
l_int|0
)braket
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* vmas */
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
op_logical_and
id|dio-&gt;blocks_available
op_logical_and
(paren
id|dio-&gt;rw
op_eq
id|WRITE
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * A memory fault, but the filesystem has some outstanding&n;&t;&t; * mapped blocks.  We need to use those blocks up to avoid&n;&t;&t; * leaking stale data in the file.&n;&t;&t; */
r_if
c_cond
(paren
id|dio-&gt;page_errors
op_eq
l_int|0
)paren
id|dio-&gt;page_errors
op_assign
id|ret
suffix:semicolon
id|dio-&gt;pages
(braket
l_int|0
)braket
op_assign
id|ZERO_PAGE
c_func
(paren
id|dio-&gt;cur_user_address
)paren
suffix:semicolon
id|dio-&gt;head
op_assign
l_int|0
suffix:semicolon
id|dio-&gt;tail
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
(brace
id|dio-&gt;curr_user_address
op_add_assign
id|ret
op_star
id|PAGE_SIZE
suffix:semicolon
id|dio-&gt;curr_page
op_add_assign
id|ret
suffix:semicolon
id|dio-&gt;head
op_assign
l_int|0
suffix:semicolon
id|dio-&gt;tail
op_assign
id|ret
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Get another userspace page.  Returns an ERR_PTR on error.  Pages are&n; * buffered inside the dio so that we can call get_user_pages() against a&n; * decent number of pages, less frequently.  To provide nicer use of the&n; * L1 cache.&n; */
DECL|function|dio_get_page
r_static
r_struct
id|page
op_star
id|dio_get_page
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_if
c_cond
(paren
id|dio_pages_present
c_func
(paren
id|dio
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|dio_refill_pages
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dio_pages_present
c_func
(paren
id|dio
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|dio-&gt;pages
(braket
id|dio-&gt;head
op_increment
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * The BIO completion handler simply queues the BIO up for the process-context&n; * handler.&n; *&n; * During I/O bi_private points at the dio.  After I/O, bi_private is used to&n; * implement a singly-linked list of completed BIOs, at dio-&gt;bio_list.&n; */
DECL|function|dio_bio_end_io
r_static
r_int
id|dio_bio_end_io
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|bytes_done
comma
r_int
id|error
)paren
(brace
r_struct
id|dio
op_star
id|dio
op_assign
id|bio-&gt;bi_private
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
id|bio-&gt;bi_private
op_assign
id|dio-&gt;bio_list
suffix:semicolon
id|dio-&gt;bio_list
op_assign
id|bio
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;waiter
)paren
id|wake_up_process
c_func
(paren
id|dio-&gt;waiter
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dio_bio_alloc
id|dio_bio_alloc
c_func
(paren
r_struct
id|dio
op_star
id|dio
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|first_sector
comma
r_int
id|nr_vecs
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|GFP_KERNEL
comma
id|nr_vecs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|bdev
suffix:semicolon
id|bio-&gt;bi_vcnt
op_assign
id|nr_vecs
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_size
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|first_sector
suffix:semicolon
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_page
op_assign
l_int|NULL
suffix:semicolon
id|bio-&gt;bi_end_io
op_assign
id|dio_bio_end_io
suffix:semicolon
id|dio-&gt;bio
op_assign
id|bio
suffix:semicolon
id|dio-&gt;bvec
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* debug */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dio_bio_submit
r_static
r_void
id|dio_bio_submit
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
id|dio-&gt;bio
suffix:semicolon
id|bio-&gt;bi_vcnt
op_assign
id|bio-&gt;bi_idx
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_private
op_assign
id|dio
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dio-&gt;bio_count
)paren
suffix:semicolon
id|submit_bio
c_func
(paren
id|dio-&gt;rw
comma
id|bio
)paren
suffix:semicolon
id|dio-&gt;bio
op_assign
l_int|NULL
suffix:semicolon
id|dio-&gt;bvec
op_assign
l_int|NULL
suffix:semicolon
id|dio-&gt;boundary
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Release any resources in case of a failure&n; */
DECL|function|dio_cleanup
r_static
r_void
id|dio_cleanup
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_while
c_loop
(paren
id|dio_pages_present
c_func
(paren
id|dio
)paren
)paren
id|page_cache_release
c_func
(paren
id|dio_get_page
c_func
(paren
id|dio
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait for the next BIO to complete.  Remove it and return it.&n; */
DECL|function|dio_await_one
r_static
r_struct
id|bio
op_star
id|dio_await_one
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dio-&gt;bio_list
op_eq
l_int|NULL
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;bio_list
op_eq
l_int|NULL
)paren
(brace
id|dio-&gt;waiter
op_assign
id|current
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
id|dio-&gt;waiter
op_assign
l_int|NULL
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
)brace
id|bio
op_assign
id|dio-&gt;bio_list
suffix:semicolon
id|dio-&gt;bio_list
op_assign
id|bio-&gt;bi_private
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|bio
suffix:semicolon
)brace
multiline_comment|/*&n; * Process one completed BIO.  No locks are held.&n; */
DECL|function|dio_bio_complete
r_static
r_int
id|dio_bio_complete
c_func
(paren
r_struct
id|dio
op_star
id|dio
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_const
r_int
id|uptodate
op_assign
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvec
op_assign
id|bio-&gt;bi_io_vec
suffix:semicolon
r_int
id|page_no
suffix:semicolon
r_for
c_loop
(paren
id|page_no
op_assign
l_int|0
suffix:semicolon
id|page_no
OL
id|bio-&gt;bi_vcnt
suffix:semicolon
id|page_no
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|bvec
(braket
id|page_no
)braket
dot
id|bv_page
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;rw
op_eq
id|READ
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dio-&gt;bio_count
)paren
suffix:semicolon
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
r_return
id|uptodate
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait on and process all in-flight BIOs.&n; */
DECL|function|dio_await_completion
r_static
r_int
id|dio_await_completion
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;bio
)paren
id|dio_bio_submit
c_func
(paren
id|dio
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|dio-&gt;bio_count
)paren
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
id|dio_await_one
c_func
(paren
id|dio
)paren
suffix:semicolon
r_int
id|ret2
suffix:semicolon
id|ret2
op_assign
id|dio_bio_complete
c_func
(paren
id|dio
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|ret2
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * A really large O_DIRECT read or write can generate a lot of BIOs.  So&n; * to keep the memory consumption sane we periodically reap any completed BIOs&n; * during the BIO generation phase.&n; *&n; * This also helps to limit the peak amount of pinned userspace memory.&n; */
DECL|function|dio_bio_reap
r_static
r_int
id|dio_bio_reap
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;reap_counter
op_increment
op_ge
l_int|64
)paren
(brace
r_while
c_loop
(paren
id|dio-&gt;bio_list
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
id|bio
op_assign
id|dio-&gt;bio_list
suffix:semicolon
id|dio-&gt;bio_list
op_assign
id|bio-&gt;bi_private
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dio-&gt;bio_list_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|dio_bio_complete
c_func
(paren
id|dio
comma
id|bio
)paren
suffix:semicolon
)brace
id|dio-&gt;reap_counter
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Call into the fs to map some more disk blocks.  We record the current number&n; * of available blocks at dio-&gt;blocks_available.  These are in units of the&n; * fs blocksize, (1 &lt;&lt; inode-&gt;i_blkbits).&n; *&n; * The fs is allowed to map lots of blocks at once.  If it wants to do that,&n; * it uses the passed inode-relative block number as the file offset, as usual.&n; *&n; * get_blocks() is passed the number of i_blkbits-sized blocks which direct_io&n; * has remaining to do.  The fs should not map more than this number of blocks.&n; *&n; * If the fs has mapped a lot of blocks, it should populate bh-&gt;b_size to&n; * indicate how much contiguous disk space has been made available at&n; * bh-&gt;b_blocknr.&n; *&n; * If *any* of the mapped blocks are new, then the fs must set buffer_new().&n; * This isn&squot;t very efficient...&n; *&n; * In the case of filesystem holes: the fs may return an arbitrarily-large&n; * hole by returning an appropriate value in b_size and by clearing&n; * buffer_mapped().  This code _should_ handle that case correctly, but it has&n; * only been tested against single-block holes (b_size == blocksize).&n; */
DECL|function|get_more_blocks
r_static
r_int
id|get_more_blocks
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|buffer_head
op_star
id|map_bh
op_assign
op_amp
id|dio-&gt;map_bh
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;blocks_available
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If there was a memory error and we&squot;ve overwritten all the&n;&t; * mapped blocks then we can now return that memory error&n;&t; */
r_if
c_cond
(paren
id|dio-&gt;page_errors
)paren
(brace
id|ret
op_assign
id|dio-&gt;page_errors
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|map_bh-&gt;b_state
op_assign
l_int|0
suffix:semicolon
id|map_bh-&gt;b_size
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dio-&gt;block_in_file
op_ge
id|dio-&gt;final_block_in_request
)paren
suffix:semicolon
id|ret
op_assign
(paren
op_star
id|dio-&gt;get_blocks
)paren
(paren
id|dio-&gt;inode
comma
id|dio-&gt;block_in_file
comma
id|dio-&gt;final_block_in_request
op_minus
id|dio-&gt;block_in_file
comma
id|map_bh
comma
id|dio-&gt;rw
op_eq
id|WRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|buffer_mapped
c_func
(paren
id|map_bh
)paren
)paren
(brace
id|BUG_ON
c_func
(paren
id|map_bh-&gt;b_size
op_eq
l_int|0
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|map_bh-&gt;b_size
op_amp
(paren
(paren
l_int|1
op_lshift
id|dio-&gt;blkbits
)paren
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|dio-&gt;blocks_available
op_assign
id|map_bh-&gt;b_size
op_rshift
id|dio-&gt;blkbits
suffix:semicolon
multiline_comment|/* blockdevs do not set buffer_new */
r_if
c_cond
(paren
id|buffer_new
c_func
(paren
id|map_bh
)paren
)paren
(brace
id|sector_t
id|block
op_assign
id|map_bh-&gt;b_blocknr
suffix:semicolon
r_int
id|i
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
id|dio-&gt;blocks_available
suffix:semicolon
id|i
op_increment
)paren
id|unmap_underlying_metadata
c_func
(paren
id|map_bh-&gt;b_bdev
comma
id|block
op_increment
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|BUG_ON
c_func
(paren
id|dio-&gt;rw
op_ne
id|READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;bio
)paren
id|dio_bio_submit
c_func
(paren
id|dio
)paren
suffix:semicolon
)brace
id|dio-&gt;next_block_in_bio
op_assign
id|map_bh-&gt;b_blocknr
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Check to see if we can continue to grow the BIO. If not, then send it.&n; */
DECL|function|dio_prep_bio
r_static
r_void
id|dio_prep_bio
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_if
c_cond
(paren
id|dio-&gt;bio
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;bio-&gt;bi_idx
op_eq
id|dio-&gt;bio-&gt;bi_vcnt
op_logical_or
id|dio-&gt;boundary
op_logical_or
id|dio-&gt;last_block_in_bio
op_ne
id|dio-&gt;next_block_in_bio
op_minus
l_int|1
)paren
id|dio_bio_submit
c_func
(paren
id|dio
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * There is no bio.  Make one now.&n; */
DECL|function|dio_new_bio
r_static
r_int
id|dio_new_bio
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
id|sector_t
id|sector
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|dio_bio_reap
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|sector
op_assign
id|dio-&gt;next_block_in_bio
op_lshift
(paren
id|dio-&gt;blkbits
op_minus
l_int|9
)paren
suffix:semicolon
id|ret
op_assign
id|dio_bio_alloc
c_func
(paren
id|dio
comma
id|dio-&gt;map_bh.b_bdev
comma
id|sector
comma
id|DIO_BIO_MAX_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
id|dio-&gt;boundary
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Walk the user pages, and the file, mapping blocks to disk and emitting BIOs.&n; *&n; * Direct IO against a blockdev is different from a file.  Because we can&n; * happily perform page-sized but 512-byte aligned IOs.  It is important that&n; * blockdev IO be able to have fine alignment and large sizes.&n; *&n; * So what we do is to permit the -&gt;get_blocks function to populate bh.b_size&n; * with the size of IO which is permitted at this offset and this i_blkbits.&n; *&n; * For best results, the blockdev should be set up with 512-byte i_blkbits and&n; * it should set b_size to PAGE_SIZE or more inside get_blocks().  This gives&n; * fine alignment but still allows this function to work in PAGE_SIZE units.&n; */
DECL|function|do_direct_IO
r_int
id|do_direct_IO
c_func
(paren
r_struct
id|dio
op_star
id|dio
)paren
(brace
r_const
r_int
id|blkbits
op_assign
id|dio-&gt;blkbits
suffix:semicolon
r_const
r_int
id|blocks_per_page
op_assign
id|PAGE_SIZE
op_rshift
id|blkbits
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|block_in_page
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* The I/O can start at any block offset within the first page */
id|block_in_page
op_assign
id|dio-&gt;first_block_in_page
suffix:semicolon
r_while
c_loop
(paren
id|dio-&gt;block_in_file
OL
id|dio-&gt;final_block_in_request
)paren
(brace
r_int
id|new_page
suffix:semicolon
multiline_comment|/* Need to insert this page into the BIO? */
id|page
op_assign
id|dio_get_page
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|new_page
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|block_in_page
OL
id|blocks_per_page
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_int
id|this_chunk_bytes
suffix:semicolon
multiline_comment|/* # of bytes mapped */
r_int
id|this_chunk_blocks
suffix:semicolon
multiline_comment|/* # of blocks */
r_int
id|u
suffix:semicolon
id|ret
op_assign
id|get_more_blocks
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|fail_release
suffix:semicolon
multiline_comment|/* Handle holes */
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
op_amp
id|dio-&gt;map_bh
)paren
)paren
(brace
r_char
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
op_plus
(paren
id|block_in_page
op_lshift
id|blkbits
)paren
comma
l_int|0
comma
l_int|1
op_lshift
id|blkbits
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|dio-&gt;block_in_file
op_increment
suffix:semicolon
id|dio-&gt;next_block_in_bio
op_increment
suffix:semicolon
id|block_in_page
op_increment
suffix:semicolon
r_goto
id|next_block
suffix:semicolon
)brace
id|dio_prep_bio
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;bio
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
id|dio_new_bio
c_func
(paren
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|fail_release
suffix:semicolon
id|new_page
op_assign
l_int|1
suffix:semicolon
)brace
id|bio
op_assign
id|dio-&gt;bio
suffix:semicolon
r_if
c_cond
(paren
id|new_page
)paren
(brace
id|dio-&gt;bvec
op_assign
op_amp
id|bio-&gt;bi_io_vec
(braket
id|bio-&gt;bi_idx
)braket
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|dio-&gt;bvec-&gt;bv_page
op_assign
id|page
suffix:semicolon
id|dio-&gt;bvec-&gt;bv_len
op_assign
l_int|0
suffix:semicolon
id|dio-&gt;bvec-&gt;bv_offset
op_assign
id|block_in_page
op_lshift
id|blkbits
suffix:semicolon
id|bio-&gt;bi_idx
op_increment
suffix:semicolon
id|new_page
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Work out how much disk we can add to this page */
id|this_chunk_blocks
op_assign
id|dio-&gt;blocks_available
suffix:semicolon
id|u
op_assign
(paren
id|PAGE_SIZE
op_minus
(paren
id|dio-&gt;bvec-&gt;bv_offset
op_plus
id|dio-&gt;bvec-&gt;bv_len
)paren
)paren
op_rshift
id|blkbits
suffix:semicolon
r_if
c_cond
(paren
id|this_chunk_blocks
OG
id|u
)paren
id|this_chunk_blocks
op_assign
id|u
suffix:semicolon
id|u
op_assign
id|dio-&gt;final_block_in_request
op_minus
id|dio-&gt;block_in_file
suffix:semicolon
r_if
c_cond
(paren
id|this_chunk_blocks
OG
id|u
)paren
id|this_chunk_blocks
op_assign
id|u
suffix:semicolon
id|this_chunk_bytes
op_assign
id|this_chunk_blocks
op_lshift
id|blkbits
suffix:semicolon
id|BUG_ON
c_func
(paren
id|this_chunk_bytes
op_eq
l_int|0
)paren
suffix:semicolon
id|dio-&gt;bvec-&gt;bv_len
op_add_assign
id|this_chunk_bytes
suffix:semicolon
id|bio-&gt;bi_size
op_add_assign
id|this_chunk_bytes
suffix:semicolon
id|dio-&gt;next_block_in_bio
op_add_assign
id|this_chunk_blocks
suffix:semicolon
id|dio-&gt;last_block_in_bio
op_assign
id|dio-&gt;next_block_in_bio
op_minus
l_int|1
suffix:semicolon
id|dio-&gt;boundary
op_assign
id|buffer_boundary
c_func
(paren
op_amp
id|dio-&gt;map_bh
)paren
suffix:semicolon
id|dio-&gt;block_in_file
op_add_assign
id|this_chunk_blocks
suffix:semicolon
id|block_in_page
op_add_assign
id|this_chunk_blocks
suffix:semicolon
id|dio-&gt;blocks_available
op_sub_assign
id|this_chunk_blocks
suffix:semicolon
id|next_block
suffix:colon
r_if
c_cond
(paren
id|dio-&gt;block_in_file
OG
id|dio-&gt;final_block_in_request
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dio-&gt;block_in_file
op_eq
id|dio-&gt;final_block_in_request
)paren
r_break
suffix:semicolon
)brace
id|block_in_page
op_assign
l_int|0
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|fail_release
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|direct_io_worker
id|direct_io_worker
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
comma
id|get_blocks_t
id|get_blocks
)paren
(brace
r_const
r_int
id|blkbits
op_assign
id|inode-&gt;i_blkbits
suffix:semicolon
r_int
r_int
id|user_addr
suffix:semicolon
r_int
id|seg
comma
id|ret2
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|dio
id|dio
suffix:semicolon
r_int
id|bytes
comma
id|tot_bytes
op_assign
l_int|0
suffix:semicolon
id|dio.bio
op_assign
l_int|NULL
suffix:semicolon
id|dio.bvec
op_assign
l_int|NULL
suffix:semicolon
id|dio.inode
op_assign
id|inode
suffix:semicolon
id|dio.rw
op_assign
id|rw
suffix:semicolon
id|dio.blkbits
op_assign
id|blkbits
suffix:semicolon
id|dio.block_in_file
op_assign
id|offset
op_rshift
id|blkbits
suffix:semicolon
id|dio.blocks_available
op_assign
l_int|0
suffix:semicolon
id|dio.boundary
op_assign
l_int|0
suffix:semicolon
id|dio.reap_counter
op_assign
l_int|0
suffix:semicolon
id|dio.get_blocks
op_assign
id|get_blocks
suffix:semicolon
id|dio.last_block_in_bio
op_assign
op_minus
l_int|1
suffix:semicolon
id|dio.next_block_in_bio
op_assign
op_minus
l_int|1
suffix:semicolon
id|dio.page_errors
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* BIO completion state */
id|atomic_set
c_func
(paren
op_amp
id|dio.bio_count
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dio.bio_list_lock
)paren
suffix:semicolon
id|dio.bio_list
op_assign
l_int|NULL
suffix:semicolon
id|dio.waiter
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
id|nr_segs
suffix:semicolon
id|seg
op_increment
)paren
(brace
id|user_addr
op_assign
(paren
r_int
r_int
)paren
id|iov
(braket
id|seg
)braket
dot
id|iov_base
suffix:semicolon
id|bytes
op_assign
id|iov
(braket
id|seg
)braket
dot
id|iov_len
suffix:semicolon
multiline_comment|/* Index into the first page of the first block */
id|dio.first_block_in_page
op_assign
(paren
id|user_addr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_rshift
id|blkbits
suffix:semicolon
id|dio.final_block_in_request
op_assign
id|dio.block_in_file
op_plus
(paren
id|bytes
op_rshift
id|blkbits
)paren
suffix:semicolon
multiline_comment|/* Page fetching state */
id|dio.head
op_assign
l_int|0
suffix:semicolon
id|dio.tail
op_assign
l_int|0
suffix:semicolon
id|dio.curr_page
op_assign
l_int|0
suffix:semicolon
id|dio.total_pages
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|user_addr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
(brace
id|dio.total_pages
op_increment
suffix:semicolon
id|bytes
op_sub_assign
id|PAGE_SIZE
op_minus
(paren
id|user_addr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
id|dio.total_pages
op_add_assign
(paren
id|bytes
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|dio.curr_user_address
op_assign
id|user_addr
suffix:semicolon
id|ret
op_assign
id|do_direct_IO
c_func
(paren
op_amp
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|dio_cleanup
c_func
(paren
op_amp
id|dio
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tot_bytes
op_add_assign
id|iov
(braket
id|seg
)braket
dot
id|iov_len
op_minus
(paren
(paren
id|dio.final_block_in_request
op_minus
id|dio.block_in_file
)paren
op_lshift
id|blkbits
)paren
suffix:semicolon
)brace
multiline_comment|/* end iovec loop */
id|ret2
op_assign
id|dio_await_completion
c_func
(paren
op_amp
id|dio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|ret2
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dio.page_errors
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|tot_bytes
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a library function for use by filesystem drivers.&n; */
r_int
DECL|function|generic_direct_IO
id|generic_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
comma
id|get_blocks_t
id|get_blocks
)paren
(brace
r_int
id|seg
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
id|blocksize_mask
op_assign
(paren
l_int|1
op_lshift
id|inode-&gt;i_blkbits
)paren
op_minus
l_int|1
suffix:semicolon
id|ssize_t
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
id|blocksize_mask
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Check the memory alignment.  Blocks cannot straddle pages */
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
id|nr_segs
suffix:semicolon
id|seg
op_increment
)paren
(brace
id|addr
op_assign
(paren
r_int
r_int
)paren
id|iov
(braket
id|seg
)braket
dot
id|iov_base
suffix:semicolon
id|size
op_assign
id|iov
(braket
id|seg
)braket
dot
id|iov_len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
id|blocksize_mask
)paren
op_logical_or
(paren
id|size
op_amp
id|blocksize_mask
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mapping-&gt;nrpages
)paren
(brace
id|retval
op_assign
id|filemap_fdatawrite
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
id|direct_io_worker
c_func
(paren
id|rw
comma
id|inode
comma
id|iov
comma
id|offset
comma
id|nr_segs
comma
id|get_blocks
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
id|ssize_t
DECL|function|generic_file_direct_IO
id|generic_file_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
id|ssize_t
id|retval
suffix:semicolon
id|retval
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|iov
comma
id|offset
comma
id|nr_segs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_mapping-&gt;nrpages
)paren
id|invalidate_inode_pages2
c_func
(paren
id|inode-&gt;i_mapping
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
