multiline_comment|/*&n; *  linux/mm/mempool.c&n; *&n; *  memory buffer pool support. Such pools are mostly used&n; *  for guaranteed, deadlock-free memory allocations during&n; *  extreme VM load.&n; *&n; *  started by Ingo Molnar, Copyright (C) 2001&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
DECL|function|add_element
r_static
r_void
id|add_element
c_func
(paren
id|mempool_t
op_star
id|pool
comma
r_void
op_star
id|element
)paren
(brace
id|BUG_ON
c_func
(paren
id|pool-&gt;curr_nr
op_ge
id|pool-&gt;min_nr
)paren
suffix:semicolon
id|pool-&gt;elements
(braket
id|pool-&gt;curr_nr
op_increment
)braket
op_assign
id|element
suffix:semicolon
)brace
DECL|function|remove_element
r_static
r_void
op_star
id|remove_element
c_func
(paren
id|mempool_t
op_star
id|pool
)paren
(brace
id|BUG_ON
c_func
(paren
id|pool-&gt;curr_nr
op_le
l_int|0
)paren
suffix:semicolon
r_return
id|pool-&gt;elements
(braket
op_decrement
id|pool-&gt;curr_nr
)braket
suffix:semicolon
)brace
DECL|function|free_pool
r_static
r_void
id|free_pool
c_func
(paren
id|mempool_t
op_star
id|pool
)paren
(brace
r_while
c_loop
(paren
id|pool-&gt;curr_nr
)paren
(brace
r_void
op_star
id|element
op_assign
id|remove_element
c_func
(paren
id|pool
)paren
suffix:semicolon
id|pool
op_member_access_from_pointer
id|free
c_func
(paren
id|element
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|pool-&gt;elements
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pool
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * mempool_create - create a memory pool&n; * @min_nr:    the minimum number of elements guaranteed to be&n; *             allocated for this pool.&n; * @alloc_fn:  user-defined element-allocation function.&n; * @free_fn:   user-defined element-freeing function.&n; * @pool_data: optional private data available to the user-defined functions.&n; *&n; * this function creates and allocates a guaranteed size, preallocated&n; * memory pool. The pool can be used from the mempool_alloc and mempool_free&n; * functions. This function might sleep. Both the alloc_fn() and the free_fn()&n; * functions might sleep - as long as the mempool_alloc function is not called&n; * from IRQ contexts.&n; */
DECL|function|mempool_create
id|mempool_t
op_star
id|mempool_create
c_func
(paren
r_int
id|min_nr
comma
id|mempool_alloc_t
op_star
id|alloc_fn
comma
id|mempool_free_t
op_star
id|free_fn
comma
r_void
op_star
id|pool_data
)paren
(brace
id|mempool_t
op_star
id|pool
suffix:semicolon
id|pool
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|pool
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pool
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|pool
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pool
)paren
)paren
suffix:semicolon
id|pool-&gt;elements
op_assign
id|kmalloc
c_func
(paren
id|min_nr
op_star
r_sizeof
(paren
r_void
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pool-&gt;elements
)paren
(brace
id|kfree
c_func
(paren
id|pool
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|pool-&gt;lock
)paren
suffix:semicolon
id|pool-&gt;min_nr
op_assign
id|min_nr
suffix:semicolon
id|pool-&gt;pool_data
op_assign
id|pool_data
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|pool-&gt;wait
)paren
suffix:semicolon
id|pool-&gt;alloc
op_assign
id|alloc_fn
suffix:semicolon
id|pool-&gt;free
op_assign
id|free_fn
suffix:semicolon
multiline_comment|/*&n;&t; * First pre-allocate the guaranteed number of buffers.&n;&t; */
r_while
c_loop
(paren
id|pool-&gt;curr_nr
OL
id|pool-&gt;min_nr
)paren
(brace
r_void
op_star
id|element
suffix:semicolon
id|element
op_assign
id|pool
op_member_access_from_pointer
id|alloc
c_func
(paren
id|GFP_KERNEL
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|element
)paren
)paren
(brace
id|free_pool
c_func
(paren
id|pool
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|add_element
c_func
(paren
id|pool
comma
id|element
)paren
suffix:semicolon
)brace
r_return
id|pool
suffix:semicolon
)brace
multiline_comment|/**&n; * mempool_resize - resize an existing memory pool&n; * @pool:       pointer to the memory pool which was allocated via&n; *              mempool_create().&n; * @new_min_nr: the new minimum number of elements guaranteed to be&n; *              allocated for this pool.&n; * @gfp_mask:   the usual allocation bitmask.&n; *&n; * This function shrinks/grows the pool. In the case of growing,&n; * it cannot be guaranteed that the pool will be grown to the new&n; * size immediately, but new mempool_free() calls will refill it.&n; *&n; * Note, the caller must guarantee that no mempool_destroy is called&n; * while this function is running. mempool_alloc() &amp; mempool_free()&n; * might be called (eg. from IRQ contexts) while this function executes.&n; */
DECL|function|mempool_resize
r_int
id|mempool_resize
c_func
(paren
id|mempool_t
op_star
id|pool
comma
r_int
id|new_min_nr
comma
r_int
id|gfp_mask
)paren
(brace
r_void
op_star
id|element
suffix:semicolon
r_void
op_star
op_star
id|new_elements
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|BUG_ON
c_func
(paren
id|new_min_nr
op_le
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_min_nr
OL
id|pool-&gt;min_nr
)paren
(brace
r_while
c_loop
(paren
id|pool-&gt;curr_nr
OG
id|new_min_nr
)paren
(brace
id|element
op_assign
id|remove_element
c_func
(paren
id|pool
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|pool
op_member_access_from_pointer
id|free
c_func
(paren
id|element
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|pool-&gt;min_nr
op_assign
id|new_min_nr
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Grow the pool */
id|new_elements
op_assign
id|kmalloc
c_func
(paren
id|new_min_nr
op_star
r_sizeof
(paren
op_star
id|new_elements
)paren
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_elements
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_elements
comma
id|pool-&gt;elements
comma
id|pool-&gt;curr_nr
op_star
r_sizeof
(paren
op_star
id|new_elements
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pool-&gt;elements
)paren
suffix:semicolon
id|pool-&gt;elements
op_assign
id|new_elements
suffix:semicolon
id|pool-&gt;min_nr
op_assign
id|new_min_nr
suffix:semicolon
r_while
c_loop
(paren
id|pool-&gt;curr_nr
OL
id|pool-&gt;min_nr
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|element
op_assign
id|pool
op_member_access_from_pointer
id|alloc
c_func
(paren
id|gfp_mask
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|element
)paren
r_goto
id|out
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;curr_nr
OL
id|pool-&gt;min_nr
)paren
id|add_element
c_func
(paren
id|pool
comma
id|element
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|element
)paren
suffix:semicolon
multiline_comment|/* Raced */
)brace
id|out_unlock
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * mempool_destroy - deallocate a memory pool&n; * @pool:      pointer to the memory pool which was allocated via&n; *             mempool_create().&n; *&n; * this function only sleeps if the free_fn() function sleeps. The caller&n; * has to guarantee that all elements have been returned to the pool (ie:&n; * freed) prior to calling mempool_destroy().&n; */
DECL|function|mempool_destroy
r_void
id|mempool_destroy
c_func
(paren
id|mempool_t
op_star
id|pool
)paren
(brace
r_if
c_cond
(paren
id|pool-&gt;curr_nr
op_ne
id|pool-&gt;min_nr
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* There were outstanding elements */
id|free_pool
c_func
(paren
id|pool
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * mempool_alloc - allocate an element from a specific memory pool&n; * @pool:      pointer to the memory pool which was allocated via&n; *             mempool_create().&n; * @gfp_mask:  the usual allocation bitmask.&n; *&n; * this function only sleeps if the alloc_fn function sleeps or&n; * returns NULL. Note that due to preallocation, this function&n; * *never* fails when called from process contexts. (it might&n; * fail if called from an IRQ context.)&n; */
DECL|function|mempool_alloc
r_void
op_star
id|mempool_alloc
c_func
(paren
id|mempool_t
op_star
id|pool
comma
r_int
id|gfp_mask
)paren
(brace
r_void
op_star
id|element
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_int
id|gfp_nowait
op_assign
id|gfp_mask
op_amp
op_complement
(paren
id|__GFP_WAIT
op_or
id|__GFP_IO
)paren
suffix:semicolon
r_int
id|pf_flags
op_assign
id|current-&gt;flags
suffix:semicolon
id|repeat_alloc
suffix:colon
id|current-&gt;flags
op_or_assign
id|PF_NOWARN
suffix:semicolon
id|element
op_assign
id|pool
op_member_access_from_pointer
id|alloc
c_func
(paren
id|gfp_nowait
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
id|current-&gt;flags
op_assign
id|pf_flags
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|element
op_ne
l_int|NULL
)paren
)paren
r_return
id|element
suffix:semicolon
multiline_comment|/*&n;&t; * If the pool is less than 50% full and we can perform effective&n;&t; * page reclaim then try harder to allocate an element.&n;&t; */
r_if
c_cond
(paren
(paren
id|gfp_mask
op_amp
id|__GFP_FS
)paren
op_logical_and
(paren
id|gfp_mask
op_ne
id|gfp_nowait
)paren
op_logical_and
(paren
id|pool-&gt;curr_nr
op_le
id|pool-&gt;min_nr
op_div
l_int|2
)paren
)paren
(brace
id|element
op_assign
id|pool
op_member_access_from_pointer
id|alloc
c_func
(paren
id|gfp_mask
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|element
op_ne
l_int|NULL
)paren
)paren
r_return
id|element
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Kick the VM at this point.&n;&t; */
id|wakeup_bdflush
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pool-&gt;curr_nr
)paren
)paren
(brace
id|element
op_assign
id|remove_element
c_func
(paren
id|pool
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|element
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* We must not sleep in the GFP_ATOMIC case */
r_if
c_cond
(paren
op_logical_neg
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
op_amp
id|pool-&gt;wait
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pool-&gt;curr_nr
)paren
id|io_schedule
c_func
(paren
)paren
suffix:semicolon
id|finish_wait
c_func
(paren
op_amp
id|pool-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_goto
id|repeat_alloc
suffix:semicolon
)brace
multiline_comment|/**&n; * mempool_free - return an element to the pool.&n; * @element:   pool element pointer.&n; * @pool:      pointer to the memory pool which was allocated via&n; *             mempool_create().&n; *&n; * this function only sleeps if the free_fn() function sleeps.&n; */
DECL|function|mempool_free
r_void
id|mempool_free
c_func
(paren
r_void
op_star
id|element
comma
id|mempool_t
op_star
id|pool
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;curr_nr
OL
id|pool-&gt;min_nr
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;curr_nr
OL
id|pool-&gt;min_nr
)paren
(brace
id|add_element
c_func
(paren
id|pool
comma
id|element
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|pool-&gt;wait
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|pool
op_member_access_from_pointer
id|free
c_func
(paren
id|element
comma
id|pool-&gt;pool_data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A commonly used alloc and free fn.&n; */
DECL|function|mempool_alloc_slab
r_void
op_star
id|mempool_alloc_slab
c_func
(paren
r_int
id|gfp_mask
comma
r_void
op_star
id|pool_data
)paren
(brace
id|kmem_cache_t
op_star
id|mem
op_assign
(paren
id|kmem_cache_t
op_star
)paren
id|pool_data
suffix:semicolon
r_return
id|kmem_cache_alloc
c_func
(paren
id|mem
comma
id|gfp_mask
)paren
suffix:semicolon
)brace
DECL|function|mempool_free_slab
r_void
id|mempool_free_slab
c_func
(paren
r_void
op_star
id|element
comma
r_void
op_star
id|pool_data
)paren
(brace
id|kmem_cache_t
op_star
id|mem
op_assign
(paren
id|kmem_cache_t
op_star
)paren
id|pool_data
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|mem
comma
id|element
)paren
suffix:semicolon
)brace
DECL|variable|mempool_create
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_create
)paren
suffix:semicolon
DECL|variable|mempool_resize
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_resize
)paren
suffix:semicolon
DECL|variable|mempool_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_destroy
)paren
suffix:semicolon
DECL|variable|mempool_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_alloc
)paren
suffix:semicolon
DECL|variable|mempool_free
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_free
)paren
suffix:semicolon
DECL|variable|mempool_alloc_slab
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_alloc_slab
)paren
suffix:semicolon
DECL|variable|mempool_free_slab
id|EXPORT_SYMBOL
c_func
(paren
id|mempool_free_slab
)paren
suffix:semicolon
eof
