multiline_comment|/*&n; * Copyright (C) 2001, 2002 Sistina Software (UK) Limited.&n; *&n; * This file is released under the GPL.&n; */
macro_line|#include &quot;dm.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|variable|_name
r_static
r_const
r_char
op_star
id|_name
op_assign
id|DM_NAME
suffix:semicolon
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES (1 &lt;&lt; KDEV_MINOR_BITS)
DECL|variable|major
r_static
r_int
id|major
op_assign
l_int|0
suffix:semicolon
DECL|variable|_major
r_static
r_int
id|_major
op_assign
l_int|0
suffix:semicolon
DECL|struct|dm_io
r_struct
id|dm_io
(brace
DECL|member|md
r_struct
id|mapped_device
op_star
id|md
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
DECL|member|io_count
id|atomic_t
id|io_count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|deferred_io
r_struct
id|deferred_io
(brace
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
DECL|member|next
r_struct
id|deferred_io
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Bits for the md-&gt;flags field.&n; */
DECL|macro|DMF_BLOCK_IO
mdefine_line|#define DMF_BLOCK_IO 0
DECL|macro|DMF_SUSPENDED
mdefine_line|#define DMF_SUSPENDED 1
DECL|struct|mapped_device
r_struct
id|mapped_device
(brace
DECL|member|lock
r_struct
id|rw_semaphore
id|lock
suffix:semicolon
DECL|member|holders
id|atomic_t
id|holders
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|queue
id|request_queue_t
id|queue
suffix:semicolon
DECL|member|disk
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
multiline_comment|/*&n;&t; * A list of ios that arrived while we were suspended.&n;&t; */
DECL|member|pending
id|atomic_t
id|pending
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|deferred
r_struct
id|deferred_io
op_star
id|deferred
suffix:semicolon
multiline_comment|/*&n;&t; * The current mapping.&n;&t; */
DECL|member|map
r_struct
id|dm_table
op_star
id|map
suffix:semicolon
multiline_comment|/*&n;&t; * io objects are allocated from here.&n;&t; */
DECL|member|io_pool
id|mempool_t
op_star
id|io_pool
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MIN_IOS
mdefine_line|#define MIN_IOS 256
DECL|variable|_io_cache
r_static
id|kmem_cache_t
op_star
id|_io_cache
suffix:semicolon
DECL|function|local_init
r_static
id|__init
r_int
id|local_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
multiline_comment|/* allocate a slab for the dm_ios */
id|_io_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;dm io&quot;
comma
r_sizeof
(paren
r_struct
id|dm_io
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
op_logical_neg
id|_io_cache
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|_major
op_assign
id|major
suffix:semicolon
id|r
op_assign
id|register_blkdev
c_func
(paren
id|_major
comma
id|_name
comma
op_amp
id|dm_blk_dops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
id|DMERR
c_func
(paren
l_string|&quot;register_blkdev failed&quot;
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|_io_cache
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|_major
)paren
id|_major
op_assign
id|r
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|local_exit
r_static
r_void
id|local_exit
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|_io_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister_blkdev
c_func
(paren
id|_major
comma
id|_name
)paren
OL
l_int|0
)paren
id|DMERR
c_func
(paren
l_string|&quot;devfs_unregister_blkdev failed&quot;
)paren
suffix:semicolon
id|_major
op_assign
l_int|0
suffix:semicolon
id|DMINFO
c_func
(paren
l_string|&quot;cleaned up&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We have a lot of init/exit functions, so it seems easier to&n; * store them in an array.  The disposable macro &squot;xx&squot;&n; * expands a prefix into a pair of function names.&n; */
r_static
r_struct
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|exit
r_void
(paren
op_star
m_exit
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|_inits
)brace
id|_inits
(braket
)braket
op_assign
(brace
DECL|macro|xx
mdefine_line|#define xx(n) {n ## _init, n ## _exit},
id|xx
c_func
(paren
id|local
)paren
id|xx
c_func
(paren
id|dm_target
)paren
id|xx
c_func
(paren
id|dm_linear
)paren
id|xx
c_func
(paren
id|dm_stripe
)paren
id|xx
c_func
(paren
id|dm_interface
)paren
DECL|macro|xx
macro_line|#undef xx
)brace
suffix:semicolon
DECL|function|dm_init
r_static
r_int
id|__init
id|dm_init
c_func
(paren
r_void
)paren
(brace
r_const
r_int
id|count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|_inits
)paren
suffix:semicolon
r_int
id|r
comma
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r
op_assign
id|_inits
(braket
id|i
)braket
dot
id|init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_goto
id|bad
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|_inits
(braket
id|i
)braket
dot
m_exit
(paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|dm_exit
r_static
r_void
id|__exit
id|dm_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
id|ARRAY_SIZE
c_func
(paren
id|_inits
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|_inits
(braket
id|i
)braket
dot
m_exit
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Block device functions&n; */
DECL|function|dm_blk_open
r_static
r_int
id|dm_blk_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|mapped_device
op_star
id|md
suffix:semicolon
id|md
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|dm_get
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_blk_close
r_static
r_int
id|dm_blk_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|mapped_device
op_star
id|md
suffix:semicolon
id|md
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|dm_put
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_io
r_static
r_inline
r_struct
id|dm_io
op_star
id|alloc_io
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_return
id|mempool_alloc
c_func
(paren
id|md-&gt;io_pool
comma
id|GFP_NOIO
)paren
suffix:semicolon
)brace
DECL|function|free_io
r_static
r_inline
r_void
id|free_io
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|dm_io
op_star
id|io
)paren
(brace
id|mempool_free
c_func
(paren
id|io
comma
id|md-&gt;io_pool
)paren
suffix:semicolon
)brace
DECL|function|alloc_deferred
r_static
r_inline
r_struct
id|deferred_io
op_star
id|alloc_deferred
c_func
(paren
r_void
)paren
(brace
r_return
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|deferred_io
)paren
comma
id|GFP_NOIO
)paren
suffix:semicolon
)brace
DECL|function|free_deferred
r_static
r_inline
r_void
id|free_deferred
c_func
(paren
r_struct
id|deferred_io
op_star
id|di
)paren
(brace
id|kfree
c_func
(paren
id|di
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add the bio to the list of deferred io.&n; */
DECL|function|queue_io
r_static
r_int
id|queue_io
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|deferred_io
op_star
id|di
suffix:semicolon
id|di
op_assign
id|alloc_deferred
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|di
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|DMF_BLOCK_IO
comma
op_amp
id|md-&gt;flags
)paren
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|free_deferred
c_func
(paren
id|di
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|di-&gt;bio
op_assign
id|bio
suffix:semicolon
id|di-&gt;next
op_assign
id|md-&gt;deferred
suffix:semicolon
id|md-&gt;deferred
op_assign
id|di
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* deferred successfully */
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * CRUD START:&n; *   A more elegant soln is in the works that uses the queue&n; *   merge fn, unfortunately there are a couple of changes to&n; *   the block layer that I want to make for this.  So in the&n; *   interests of getting something for people to use I give&n; *   you this clearly demarcated crap.&n; *---------------------------------------------------------------*/
multiline_comment|/*&n; * Decrements the number of outstanding ios that a bio has been&n; * cloned into, completing the original io if necc.&n; */
DECL|function|dec_pending
r_static
r_inline
r_void
id|dec_pending
c_func
(paren
r_struct
id|dm_io
op_star
id|io
comma
r_int
id|error
)paren
(brace
r_static
id|spinlock_t
id|_uptodate_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|_uptodate_lock
comma
id|flags
)paren
suffix:semicolon
id|io-&gt;error
op_assign
id|error
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|_uptodate_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|io-&gt;io_count
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|io-&gt;md-&gt;pending
)paren
)paren
multiline_comment|/* nudge anyone waiting on suspend queue */
id|wake_up
c_func
(paren
op_amp
id|io-&gt;md-&gt;wait
)paren
suffix:semicolon
id|bio_endio
c_func
(paren
id|io-&gt;bio
comma
id|io-&gt;error
ques
c_cond
l_int|0
suffix:colon
id|io-&gt;bio-&gt;bi_size
comma
id|io-&gt;error
)paren
suffix:semicolon
id|free_io
c_func
(paren
id|io-&gt;md
comma
id|io
)paren
suffix:semicolon
)brace
)brace
DECL|function|clone_endio
r_static
r_int
id|clone_endio
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|done
comma
r_int
id|error
)paren
(brace
r_struct
id|dm_io
op_star
id|io
op_assign
id|bio-&gt;bi_private
suffix:semicolon
multiline_comment|/*&n;&t; * Only call dec_pending if the clone has completely&n;&t; * finished.  If a partial io errors I&squot;m assuming it won&squot;t&n;&t; * be requeued.  FIXME: check this.&n;&t; */
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|bio-&gt;bi_size
)paren
(brace
id|dec_pending
c_func
(paren
id|io
comma
id|error
)paren
suffix:semicolon
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|max_io_len
r_static
id|sector_t
id|max_io_len
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
id|sector_t
id|sector
comma
r_struct
id|dm_target
op_star
id|ti
)paren
(brace
id|sector_t
id|len
op_assign
id|ti-&gt;len
suffix:semicolon
multiline_comment|/* FIXME: obey io_restrictions ! */
multiline_comment|/*&n;&t; * Does the target need to split even further ?&n;&t; */
r_if
c_cond
(paren
id|ti-&gt;split_io
)paren
(brace
id|sector_t
id|boundary
suffix:semicolon
id|sector_t
id|offset
op_assign
id|sector
op_minus
id|ti-&gt;begin
suffix:semicolon
id|boundary
op_assign
id|dm_round_up
c_func
(paren
id|offset
op_plus
l_int|1
comma
id|ti-&gt;split_io
)paren
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|boundary
)paren
id|len
op_assign
id|boundary
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|__map_bio
r_static
r_void
id|__map_bio
c_func
(paren
r_struct
id|dm_target
op_star
id|ti
comma
r_struct
id|bio
op_star
id|clone
)paren
(brace
r_struct
id|dm_io
op_star
id|io
op_assign
id|clone-&gt;bi_private
suffix:semicolon
r_int
id|r
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity checks.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|clone-&gt;bi_size
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Map the clone.  If r == 0 we don&squot;t need to do&n;&t; * anything, the target has assumed ownership of&n;&t; * this io.&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|io-&gt;io_count
)paren
suffix:semicolon
id|r
op_assign
id|ti-&gt;type
op_member_access_from_pointer
id|map
c_func
(paren
id|ti
comma
id|clone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|0
)paren
multiline_comment|/* the bio has been remapped so dispatch it */
id|generic_make_request
c_func
(paren
id|clone
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
multiline_comment|/* error the io and bail out */
id|dec_pending
c_func
(paren
id|io
comma
op_minus
id|EIO
)paren
suffix:semicolon
)brace
DECL|struct|clone_info
r_struct
id|clone_info
(brace
DECL|member|md
r_struct
id|mapped_device
op_star
id|md
suffix:semicolon
DECL|member|bio
r_struct
id|bio
op_star
id|bio
suffix:semicolon
DECL|member|io
r_struct
id|dm_io
op_star
id|io
suffix:semicolon
DECL|member|sector
id|sector_t
id|sector
suffix:semicolon
DECL|member|sector_count
id|sector_t
id|sector_count
suffix:semicolon
DECL|member|idx
r_int
r_int
id|idx
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Issues a little bio that just does the back end of a split page.&n; */
DECL|function|__split_page
r_static
r_void
id|__split_page
c_func
(paren
r_struct
id|clone_info
op_star
id|ci
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|dm_target
op_star
id|ti
op_assign
id|dm_table_find_target
c_func
(paren
id|ci-&gt;md-&gt;map
comma
id|ci-&gt;sector
)paren
suffix:semicolon
r_struct
id|bio
op_star
id|clone
comma
op_star
id|bio
op_assign
id|ci-&gt;bio
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bv
op_assign
id|bio-&gt;bi_io_vec
op_plus
id|ci-&gt;idx
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|ci-&gt;sector_count
)paren
id|len
op_assign
id|ci-&gt;sector_count
suffix:semicolon
id|clone
op_assign
id|bio_alloc
c_func
(paren
id|GFP_NOIO
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|clone-&gt;bi_io_vec
comma
id|bv
comma
r_sizeof
(paren
op_star
id|bv
)paren
)paren
suffix:semicolon
id|clone-&gt;bi_sector
op_assign
id|ci-&gt;sector
suffix:semicolon
id|clone-&gt;bi_bdev
op_assign
id|bio-&gt;bi_bdev
suffix:semicolon
id|clone-&gt;bi_rw
op_assign
id|bio-&gt;bi_rw
suffix:semicolon
id|clone-&gt;bi_vcnt
op_assign
l_int|1
suffix:semicolon
id|clone-&gt;bi_size
op_assign
id|len
op_lshift
id|SECTOR_SHIFT
suffix:semicolon
id|clone-&gt;bi_end_io
op_assign
id|clone_endio
suffix:semicolon
id|clone-&gt;bi_private
op_assign
id|ci-&gt;io
suffix:semicolon
id|clone-&gt;bi_io_vec-&gt;bv_offset
op_assign
id|bv-&gt;bv_len
op_minus
id|clone-&gt;bi_size
suffix:semicolon
id|clone-&gt;bi_io_vec-&gt;bv_len
op_assign
id|clone-&gt;bi_size
suffix:semicolon
id|ci-&gt;sector
op_add_assign
id|len
suffix:semicolon
id|ci-&gt;sector_count
op_sub_assign
id|len
suffix:semicolon
id|__map_bio
c_func
(paren
id|ti
comma
id|clone
)paren
suffix:semicolon
)brace
DECL|function|__clone_and_map
r_static
r_void
id|__clone_and_map
c_func
(paren
r_struct
id|clone_info
op_star
id|ci
)paren
(brace
r_struct
id|bio
op_star
id|clone
comma
op_star
id|bio
op_assign
id|ci-&gt;bio
suffix:semicolon
r_struct
id|dm_target
op_star
id|ti
op_assign
id|dm_table_find_target
c_func
(paren
id|ci-&gt;md-&gt;map
comma
id|ci-&gt;sector
)paren
suffix:semicolon
id|sector_t
id|len
op_assign
id|max_io_len
c_func
(paren
id|ci-&gt;md
comma
id|bio-&gt;bi_sector
comma
id|ti
)paren
suffix:semicolon
multiline_comment|/* shorter than current target ? */
r_if
c_cond
(paren
id|ci-&gt;sector_count
OL
id|len
)paren
id|len
op_assign
id|ci-&gt;sector_count
suffix:semicolon
multiline_comment|/* create the clone */
id|clone
op_assign
id|bio_clone
c_func
(paren
id|ci-&gt;bio
comma
id|GFP_NOIO
)paren
suffix:semicolon
id|clone-&gt;bi_sector
op_assign
id|ci-&gt;sector
suffix:semicolon
id|clone-&gt;bi_idx
op_assign
id|ci-&gt;idx
suffix:semicolon
id|clone-&gt;bi_size
op_assign
id|len
op_lshift
id|SECTOR_SHIFT
suffix:semicolon
id|clone-&gt;bi_end_io
op_assign
id|clone_endio
suffix:semicolon
id|clone-&gt;bi_private
op_assign
id|ci-&gt;io
suffix:semicolon
multiline_comment|/* adjust the remaining io */
id|ci-&gt;sector
op_add_assign
id|len
suffix:semicolon
id|ci-&gt;sector_count
op_sub_assign
id|len
suffix:semicolon
id|__map_bio
c_func
(paren
id|ti
comma
id|clone
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we are not performing all remaining io in this&n;&t; * clone then we need to calculate ci-&gt;idx for the next&n;&t; * time round.&n;&t; */
r_if
c_cond
(paren
id|ci-&gt;sector_count
)paren
(brace
r_while
c_loop
(paren
id|len
)paren
(brace
r_struct
id|bio_vec
op_star
id|bv
op_assign
id|clone-&gt;bi_io_vec
op_plus
id|ci-&gt;idx
suffix:semicolon
id|sector_t
id|bv_len
op_assign
id|bv-&gt;bv_len
op_rshift
id|SECTOR_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|bv_len
op_le
id|len
)paren
id|len
op_sub_assign
id|bv_len
suffix:semicolon
r_else
(brace
id|__split_page
c_func
(paren
id|ci
comma
id|bv_len
op_minus
id|len
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
id|ci-&gt;idx
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Split the bio into several clones.&n; */
DECL|function|__split_bio
r_static
r_void
id|__split_bio
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|clone_info
id|ci
suffix:semicolon
id|ci.md
op_assign
id|md
suffix:semicolon
id|ci.bio
op_assign
id|bio
suffix:semicolon
id|ci.io
op_assign
id|alloc_io
c_func
(paren
id|md
)paren
suffix:semicolon
id|ci.io-&gt;error
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ci.io-&gt;io_count
comma
l_int|1
)paren
suffix:semicolon
id|ci.io-&gt;bio
op_assign
id|bio
suffix:semicolon
id|ci.io-&gt;md
op_assign
id|md
suffix:semicolon
id|ci.sector
op_assign
id|bio-&gt;bi_sector
suffix:semicolon
id|ci.sector_count
op_assign
id|bio_sectors
c_func
(paren
id|bio
)paren
suffix:semicolon
id|ci.idx
op_assign
l_int|0
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|md-&gt;pending
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ci.sector_count
)paren
id|__clone_and_map
c_func
(paren
op_amp
id|ci
)paren
suffix:semicolon
multiline_comment|/* drop the extra reference count */
id|dec_pending
c_func
(paren
id|ci.io
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * CRUD END&n; *---------------------------------------------------------------*/
multiline_comment|/*&n; * The request function that just remaps the bio built up by&n; * dm_merge_bvec.&n; */
DECL|function|dm_request
r_static
r_int
id|dm_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|mapped_device
op_star
id|md
op_assign
id|q-&gt;queuedata
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re suspended we have to queue&n;&t; * this io for later.&n;&t; */
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|DMF_BLOCK_IO
comma
op_amp
id|md-&gt;flags
)paren
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio_rw
c_func
(paren
id|bio
)paren
op_eq
id|READA
)paren
(brace
id|bio_io_error
c_func
(paren
id|bio
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|r
op_assign
id|queue_io
c_func
(paren
id|md
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
id|bio_io_error
c_func
(paren
id|bio
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* deferred successfully */
multiline_comment|/*&n;&t;&t; * We&squot;re in a while loop, because someone could suspend&n;&t;&t; * before we get to the following read lock.&n;&t;&t; */
id|down_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
)brace
id|__split_bio
c_func
(paren
id|md
comma
id|bio
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-----------------------------------------------------------------&n; * A bitset is used to keep track of allocated minor numbers.&n; *---------------------------------------------------------------*/
DECL|variable|_minor_lock
r_static
id|spinlock_t
id|_minor_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|_minor_bits
r_static
r_int
r_int
id|_minor_bits
(braket
id|MAX_DEVICES
op_div
id|BITS_PER_LONG
)braket
suffix:semicolon
DECL|function|free_minor
r_static
r_void
id|free_minor
c_func
(paren
r_int
id|minor
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|minor
comma
id|_minor_bits
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * See if the device with a specific minor # is free.&n; */
DECL|function|specific_minor
r_static
r_int
id|specific_minor
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
id|r
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|MAX_DEVICES
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;request for a mapped_device beyond MAX_DEVICES (%d)&quot;
comma
id|MAX_DEVICES
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|minor
comma
id|_minor_bits
)paren
)paren
id|r
op_assign
id|minor
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|next_free_minor
r_static
r_int
id|next_free_minor
c_func
(paren
r_void
)paren
(brace
r_int
id|minor
comma
id|r
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
id|minor
op_assign
id|find_first_zero_bit
c_func
(paren
id|_minor_bits
comma
id|MAX_DEVICES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ne
id|MAX_DEVICES
)paren
(brace
id|set_bit
c_func
(paren
id|minor
comma
id|_minor_bits
)paren
suffix:semicolon
id|r
op_assign
id|minor
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|_minor_lock
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and initialise a blank device with a given minor.&n; */
DECL|function|alloc_dev
r_static
r_struct
id|mapped_device
op_star
id|alloc_dev
c_func
(paren
r_int
id|minor
)paren
(brace
r_struct
id|mapped_device
op_star
id|md
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|md
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|md
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;unable to allocate device, out of memory.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* get a minor number for the dev */
id|minor
op_assign
(paren
id|minor
OL
l_int|0
)paren
ques
c_cond
id|next_free_minor
c_func
(paren
)paren
suffix:colon
id|specific_minor
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|DMWARN
c_func
(paren
l_string|&quot;allocating minor %d.&quot;
comma
id|minor
)paren
suffix:semicolon
id|memset
c_func
(paren
id|md
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|md
)paren
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|md-&gt;holders
comma
l_int|1
)paren
suffix:semicolon
id|md-&gt;queue.queuedata
op_assign
id|md
suffix:semicolon
id|blk_queue_make_request
c_func
(paren
op_amp
id|md-&gt;queue
comma
id|dm_request
)paren
suffix:semicolon
id|md-&gt;io_pool
op_assign
id|mempool_create
c_func
(paren
id|MIN_IOS
comma
id|mempool_alloc_slab
comma
id|mempool_free_slab
comma
id|_io_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|md-&gt;io_pool
)paren
(brace
id|free_minor
c_func
(paren
id|md-&gt;disk-&gt;first_minor
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|md-&gt;disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|md-&gt;disk
)paren
(brace
id|mempool_destroy
c_func
(paren
id|md-&gt;io_pool
)paren
suffix:semicolon
id|free_minor
c_func
(paren
id|md-&gt;disk-&gt;first_minor
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|md-&gt;disk-&gt;major
op_assign
id|_major
suffix:semicolon
id|md-&gt;disk-&gt;first_minor
op_assign
id|minor
suffix:semicolon
id|md-&gt;disk-&gt;fops
op_assign
op_amp
id|dm_blk_dops
suffix:semicolon
id|md-&gt;disk-&gt;queue
op_assign
op_amp
id|md-&gt;queue
suffix:semicolon
id|md-&gt;disk-&gt;private_data
op_assign
id|md
suffix:semicolon
id|sprintf
c_func
(paren
id|md-&gt;disk-&gt;disk_name
comma
l_string|&quot;dm-%d&quot;
comma
id|minor
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|md-&gt;pending
comma
l_int|0
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|md-&gt;wait
)paren
suffix:semicolon
r_return
id|md
suffix:semicolon
)brace
DECL|function|free_dev
r_static
r_void
id|free_dev
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
id|free_minor
c_func
(paren
id|md-&gt;disk-&gt;first_minor
)paren
suffix:semicolon
id|mempool_destroy
c_func
(paren
id|md-&gt;io_pool
)paren
suffix:semicolon
id|del_gendisk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|md-&gt;disk
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|md
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bind a table to the device.&n; */
DECL|function|__bind
r_static
r_int
id|__bind
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|dm_table
op_star
id|t
)paren
(brace
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|md-&gt;queue
suffix:semicolon
id|sector_t
id|size
suffix:semicolon
id|md-&gt;map
op_assign
id|t
suffix:semicolon
id|size
op_assign
id|dm_table_get_size
c_func
(paren
id|t
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|md-&gt;disk
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|dm_table_get
c_func
(paren
id|t
)paren
suffix:semicolon
id|dm_table_set_restrictions
c_func
(paren
id|t
comma
id|q
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__unbind
r_static
r_void
id|__unbind
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
id|dm_table_put
c_func
(paren
id|md-&gt;map
)paren
suffix:semicolon
id|md-&gt;map
op_assign
l_int|NULL
suffix:semicolon
id|set_capacity
c_func
(paren
id|md-&gt;disk
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Constructor for a new device.&n; */
DECL|function|dm_create
r_int
id|dm_create
c_func
(paren
r_int
id|minor
comma
r_struct
id|dm_table
op_star
id|table
comma
r_struct
id|mapped_device
op_star
op_star
id|result
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|mapped_device
op_star
id|md
suffix:semicolon
id|md
op_assign
id|alloc_dev
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|md
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|r
op_assign
id|__bind
c_func
(paren
id|md
comma
id|table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|free_dev
c_func
(paren
id|md
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
op_star
id|result
op_assign
id|md
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_get
r_void
id|dm_get
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|md-&gt;holders
)paren
suffix:semicolon
)brace
DECL|function|dm_put
r_void
id|dm_put
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|md-&gt;holders
)paren
)paren
(brace
id|DMWARN
c_func
(paren
l_string|&quot;destroying md&quot;
)paren
suffix:semicolon
id|__unbind
c_func
(paren
id|md
)paren
suffix:semicolon
id|free_dev
c_func
(paren
id|md
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Requeue the deferred bios by calling generic_make_request.&n; */
DECL|function|flush_deferred_io
r_static
r_void
id|flush_deferred_io
c_func
(paren
r_struct
id|deferred_io
op_star
id|c
)paren
(brace
r_struct
id|deferred_io
op_star
id|n
suffix:semicolon
r_while
c_loop
(paren
id|c
)paren
(brace
id|n
op_assign
id|c-&gt;next
suffix:semicolon
id|generic_make_request
c_func
(paren
id|c-&gt;bio
)paren
suffix:semicolon
id|free_deferred
c_func
(paren
id|c
)paren
suffix:semicolon
id|c
op_assign
id|n
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Swap in a new table (destroying old one).&n; */
DECL|function|dm_swap_table
r_int
id|dm_swap_table
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
comma
r_struct
id|dm_table
op_star
id|table
)paren
(brace
r_int
id|r
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* device must be suspended */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|DMF_SUSPENDED
comma
op_amp
id|md-&gt;flags
)paren
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|__unbind
c_func
(paren
id|md
)paren
suffix:semicolon
id|r
op_assign
id|__bind
c_func
(paren
id|md
comma
id|table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to be able to change a mapping table under a mounted&n; * filesystem.  For example we might want to move some data in&n; * the background.  Before the table can be swapped with&n; * dm_bind_table, dm_suspend must be called to flush any in&n; * flight bios and ensure that any further io gets deferred.&n; */
DECL|function|dm_suspend
r_int
id|dm_suspend
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First we set the BLOCK_IO flag so no more ios will be&n;&t; * mapped.&n;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|DMF_BLOCK_IO
comma
op_amp
id|md-&gt;flags
)paren
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|DMF_BLOCK_IO
comma
op_amp
id|md-&gt;flags
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|md-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Then we wait for the already mapped ios to&n;&t; * complete.&n;&t; */
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|md-&gt;pending
)paren
)paren
r_break
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|md-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|DMF_SUSPENDED
comma
op_amp
id|md-&gt;flags
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm_resume
r_int
id|dm_resume
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_struct
id|deferred_io
op_star
id|def
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|DMF_SUSPENDED
comma
op_amp
id|md-&gt;flags
)paren
op_logical_or
op_logical_neg
id|dm_table_get_size
c_func
(paren
id|md-&gt;map
)paren
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|DMF_SUSPENDED
comma
op_amp
id|md-&gt;flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|DMF_BLOCK_IO
comma
op_amp
id|md-&gt;flags
)paren
suffix:semicolon
id|def
op_assign
id|md-&gt;deferred
suffix:semicolon
id|md-&gt;deferred
op_assign
l_int|NULL
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|flush_deferred_io
c_func
(paren
id|def
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The gendisk is only valid as long as you have a reference&n; * count on &squot;md&squot;.&n; */
DECL|function|dm_disk
r_struct
id|gendisk
op_star
id|dm_disk
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_return
id|md-&gt;disk
suffix:semicolon
)brace
DECL|function|dm_get_table
r_struct
id|dm_table
op_star
id|dm_get_table
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_struct
id|dm_table
op_star
id|t
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
id|t
op_assign
id|md-&gt;map
suffix:semicolon
id|dm_table_get
c_func
(paren
id|t
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|md-&gt;lock
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|dm_suspended
r_int
id|dm_suspended
c_func
(paren
r_struct
id|mapped_device
op_star
id|md
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|DMF_SUSPENDED
comma
op_amp
id|md-&gt;flags
)paren
suffix:semicolon
)brace
DECL|variable|dm_blk_dops
r_struct
id|block_device_operations
id|dm_blk_dops
op_assign
(brace
dot
id|open
op_assign
id|dm_blk_open
comma
dot
id|release
op_assign
id|dm_blk_close
comma
dot
id|owner
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
multiline_comment|/*&n; * module hooks&n; */
DECL|variable|dm_init
id|module_init
c_func
(paren
id|dm_init
)paren
suffix:semicolon
DECL|variable|dm_exit
id|module_exit
c_func
(paren
id|dm_exit
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|major
comma
l_string|&quot;The major number of the device mapper&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|DM_NAME
l_string|&quot; driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Joe Thornber &lt;thornber@sistina.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
