multiline_comment|/*&n; *  linux/mm/swap_state.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; *&n; *  Rewritten to use page cache, (C) 1998 Stephen Tweedie&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * swapper_space is a fiction, retained to simplify the path through&n; * vmscan&squot;s shrink_list, to make sync_page look nicer, and to allow&n; * future use of radix_tree tags in the swap cache.&n; */
DECL|variable|swap_aops
r_static
r_struct
id|address_space_operations
id|swap_aops
op_assign
(brace
dot
id|writepage
op_assign
id|swap_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|set_page_dirty
op_assign
id|__set_page_dirty_nobuffers
comma
)brace
suffix:semicolon
DECL|variable|swap_backing_dev_info
r_static
r_struct
id|backing_dev_info
id|swap_backing_dev_info
op_assign
(brace
dot
id|memory_backed
op_assign
l_int|1
comma
multiline_comment|/* Does not contribute to dirty memory */
dot
id|unplug_io_fn
op_assign
id|swap_unplug_io_fn
comma
)brace
suffix:semicolon
DECL|variable|swapper_space
r_struct
id|address_space
id|swapper_space
op_assign
(brace
dot
id|page_tree
op_assign
id|RADIX_TREE_INIT
c_func
(paren
id|GFP_ATOMIC
)paren
comma
dot
id|tree_lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
dot
id|a_ops
op_assign
op_amp
id|swap_aops
comma
dot
id|i_mmap_nonlinear
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|swapper_space.i_mmap_nonlinear
)paren
comma
dot
id|backing_dev_info
op_assign
op_amp
id|swap_backing_dev_info
comma
)brace
suffix:semicolon
DECL|variable|swapper_space
id|EXPORT_SYMBOL
c_func
(paren
id|swapper_space
)paren
suffix:semicolon
DECL|macro|INC_CACHE_INFO
mdefine_line|#define INC_CACHE_INFO(x)&t;do { swap_cache_info.x++; } while (0)
r_static
r_struct
(brace
DECL|member|add_total
r_int
r_int
id|add_total
suffix:semicolon
DECL|member|del_total
r_int
r_int
id|del_total
suffix:semicolon
DECL|member|find_success
r_int
r_int
id|find_success
suffix:semicolon
DECL|member|find_total
r_int
r_int
id|find_total
suffix:semicolon
DECL|member|noent_race
r_int
r_int
id|noent_race
suffix:semicolon
DECL|member|exist_race
r_int
r_int
id|exist_race
suffix:semicolon
DECL|variable|swap_cache_info
)brace
id|swap_cache_info
suffix:semicolon
DECL|function|show_swap_cache_info
r_void
id|show_swap_cache_info
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Swap cache: add %lu, delete %lu, find %lu/%lu, race %lu+%lu&bslash;n&quot;
comma
id|swap_cache_info.add_total
comma
id|swap_cache_info.del_total
comma
id|swap_cache_info.find_success
comma
id|swap_cache_info.find_total
comma
id|swap_cache_info.noent_race
comma
id|swap_cache_info.exist_race
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * __add_to_swap_cache resembles add_to_page_cache on swapper_space,&n; * but sets SwapCache flag and private instead of mapping and index.&n; */
DECL|function|__add_to_swap_cache
r_static
r_int
id|__add_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|swp_entry_t
id|entry
comma
r_int
id|gfp_mask
)paren
(brace
r_int
id|error
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|error
op_assign
id|radix_tree_preload
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|error
op_assign
id|radix_tree_insert
c_func
(paren
op_amp
id|swapper_space.page_tree
comma
id|entry.val
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageLocked
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageSwapCache
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_member_access_from_pointer
r_private
op_assign
id|entry.val
suffix:semicolon
id|total_swapcache_pages
op_increment
suffix:semicolon
id|pagecache_acct
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|radix_tree_preload_end
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|add_to_swap_cache
r_static
r_int
id|add_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|swp_entry_t
id|entry
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|swap_duplicate
c_func
(paren
id|entry
)paren
)paren
(brace
id|INC_CACHE_INFO
c_func
(paren
id|noent_race
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|error
op_assign
id|__add_to_swap_cache
c_func
(paren
id|page
comma
id|entry
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Anon pages are already on the LRU, we don&squot;t run lru_cache_add here.&n;&t; */
r_if
c_cond
(paren
id|error
)paren
(brace
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|EEXIST
)paren
id|INC_CACHE_INFO
c_func
(paren
id|exist_race
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|INC_CACHE_INFO
c_func
(paren
id|add_total
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This must be called only on pages that have&n; * been verified to be in the swap cache.&n; */
DECL|function|__delete_from_swap_cache
r_void
id|__delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|radix_tree_delete
c_func
(paren
op_amp
id|swapper_space.page_tree
comma
id|page
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|page
op_member_access_from_pointer
r_private
op_assign
l_int|0
suffix:semicolon
id|ClearPageSwapCache
c_func
(paren
id|page
)paren
suffix:semicolon
id|total_swapcache_pages
op_decrement
suffix:semicolon
id|pagecache_acct
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|del_total
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * add_to_swap - allocate swap space for a page&n; * @page: page we want to move to swap&n; *&n; * Allocate swap space for the page and add the page to the&n; * swap cache.  Caller needs to hold the page lock. &n; */
DECL|function|add_to_swap
r_int
id|add_to_swap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|swp_entry_t
id|entry
suffix:semicolon
r_int
id|pf_flags
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|entry
op_assign
id|get_swap_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry.val
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Radix-tree node allocations are performing&n;&t;&t; * GFP_ATOMIC allocations under PF_MEMALLOC.  &n;&t;&t; * They can completely exhaust the page allocator.  &n;&t;&t; *&n;&t;&t; * So PF_MEMALLOC is dropped here.  This causes the slab &n;&t;&t; * allocations to fail earlier, so radix-tree nodes will &n;&t;&t; * then be allocated from the mempool reserves.&n;&t;&t; *&n;&t;&t; * We&squot;re still using __GFP_HIGH for radix-tree node&n;&t;&t; * allocations, so some of the emergency pools are available,&n;&t;&t; * just not all of them.&n;&t;&t; */
id|pf_flags
op_assign
id|current-&gt;flags
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_MEMALLOC
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Add it to the swap cache and mark it dirty&n;&t;&t; */
id|err
op_assign
id|__add_to_swap_cache
c_func
(paren
id|page
comma
id|entry
comma
id|GFP_ATOMIC
op_or
id|__GFP_NOWARN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pf_flags
op_amp
id|PF_MEMALLOC
)paren
id|current-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
r_switch
c_cond
(paren
id|err
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Success */
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|add_total
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
op_minus
id|EEXIST
suffix:colon
multiline_comment|/* Raced with &quot;speculative&quot; read_swap_cache_async */
id|INC_CACHE_INFO
c_func
(paren
id|exist_race
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* -ENOMEM radix-tree allocation failure */
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * This must be called only on pages that have&n; * been verified to be in the swap cache and locked.&n; * It will never put the page into the free list,&n; * the caller has a reference on the page.&n; */
DECL|function|delete_from_swap_cache
r_void
id|delete_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|swp_entry_t
id|entry
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|entry.val
op_assign
id|page
op_member_access_from_pointer
r_private
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|__delete_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Strange swizzling function only for use by shmem_writepage&n; */
DECL|function|move_to_swap_cache
r_int
id|move_to_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|swp_entry_t
id|entry
)paren
(brace
r_int
id|err
op_assign
id|__add_to_swap_cache
c_func
(paren
id|page
comma
id|entry
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|remove_from_page_cache
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
multiline_comment|/* pagecache ref */
r_if
c_cond
(paren
op_logical_neg
id|swap_duplicate
c_func
(paren
id|entry
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|add_total
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EEXIST
)paren
id|INC_CACHE_INFO
c_func
(paren
id|exist_race
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Strange swizzling function for shmem_getpage (and shmem_unuse)&n; */
DECL|function|move_from_swap_cache
r_int
id|move_from_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|index
comma
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_int
id|err
op_assign
id|add_to_page_cache
c_func
(paren
id|page
comma
id|mapping
comma
id|index
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|delete_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* shift page from clean_pages to dirty_pages list */
id|ClearPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* &n; * If we are the only user, then try to free up the swap cache. &n; * &n; * Its ok to check for PageSwapCache without the page lock&n; * here because we are going to recheck again inside &n; * exclusive_swap_page() _with_ the lock. &n; * &t;&t;&t;&t;&t;- Marcelo&n; */
DECL|function|free_swap_cache
r_static
r_inline
r_void
id|free_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|TestSetPageLocked
c_func
(paren
id|page
)paren
)paren
(brace
id|remove_exclusive_swap_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Perform a free_page(), also freeing any swap cache associated with&n; * this page if it is the last user of the page. Can not do a lock_page,&n; * as we are holding the page_table_lock spinlock.&n; */
DECL|function|free_page_and_swap_cache
r_void
id|free_page_and_swap_cache
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|free_swap_cache
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
multiline_comment|/*&n; * Passed an array of pages, drop them all from swapcache and then release&n; * them.  They are removed from the LRU and freed if this is their last use.&n; */
DECL|function|free_pages_and_swap_cache
r_void
id|free_pages_and_swap_cache
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|nr
)paren
(brace
r_int
id|chunk
op_assign
l_int|16
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pagep
op_assign
id|pages
suffix:semicolon
id|lru_add_drain
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr
)paren
(brace
r_int
id|todo
op_assign
id|min
c_func
(paren
id|chunk
comma
id|nr
)paren
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
id|todo
suffix:semicolon
id|i
op_increment
)paren
id|free_swap_cache
c_func
(paren
id|pagep
(braket
id|i
)braket
)paren
suffix:semicolon
id|release_pages
c_func
(paren
id|pagep
comma
id|todo
comma
l_int|0
)paren
suffix:semicolon
id|pagep
op_add_assign
id|todo
suffix:semicolon
id|nr
op_sub_assign
id|todo
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Lookup a swap entry in the swap cache. A found page will be returned&n; * unlocked and with its refcount incremented - we rely on the kernel&n; * lock getting page table operations atomic even if we drop the page&n; * lock before returning.&n; */
DECL|function|lookup_swap_cache
r_struct
id|page
op_star
id|lookup_swap_cache
c_func
(paren
id|swp_entry_t
id|entry
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|page
op_assign
id|radix_tree_lookup
c_func
(paren
op_amp
id|swapper_space.page_tree
comma
id|entry.val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|find_success
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|find_total
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/* &n; * Locate a page of swap in physical memory, reserving swap cache space&n; * and reading the disk if it is not already cached.&n; * A failure return means that either the page allocation failed or that&n; * the swap entry is no longer in use.&n; */
DECL|function|read_swap_cache_async
r_struct
id|page
op_star
id|read_swap_cache_async
c_func
(paren
id|swp_entry_t
id|entry
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|page
op_star
id|found_page
comma
op_star
id|new_page
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
r_do
(brace
multiline_comment|/*&n;&t;&t; * First check the swap cache.  Since this is normally&n;&t;&t; * called after lookup_swap_cache() failed, re-calling&n;&t;&t; * that would confuse statistics.&n;&t;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
id|found_page
op_assign
id|radix_tree_lookup
c_func
(paren
op_amp
id|swapper_space.page_tree
comma
id|entry.val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_page
)paren
id|page_cache_get
c_func
(paren
id|found_page
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|swapper_space.tree_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_page
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get a new page to read into from swap.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|new_page
)paren
(brace
id|new_page
op_assign
id|alloc_page_vma
c_func
(paren
id|GFP_HIGHUSER
comma
id|vma
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_page
)paren
r_break
suffix:semicolon
multiline_comment|/* Out of memory */
)brace
multiline_comment|/*&n;&t;&t; * Associate the page with swap entry in the swap cache.&n;&t;&t; * May fail (-ENOENT) if swap entry has been freed since&n;&t;&t; * our caller observed it.  May fail (-EEXIST) if there&n;&t;&t; * is already a page associated with this entry in the&n;&t;&t; * swap cache: added by a racing read_swap_cache_async,&n;&t;&t; * or by try_to_swap_out (or shmem_writepage) re-using&n;&t;&t; * the just freed swap entry for an existing page.&n;&t;&t; * May fail (-ENOMEM) if radix-tree node allocation failed.&n;&t;&t; */
id|err
op_assign
id|add_to_swap_cache
c_func
(paren
id|new_page
comma
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Initiate read into locked page and return.&n;&t;&t;&t; */
id|lru_cache_add_active
c_func
(paren
id|new_page
)paren
suffix:semicolon
id|swap_readpage
c_func
(paren
l_int|NULL
comma
id|new_page
)paren
suffix:semicolon
r_return
id|new_page
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|err
op_ne
op_minus
id|ENOENT
op_logical_and
id|err
op_ne
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_page
)paren
id|page_cache_release
c_func
(paren
id|new_page
)paren
suffix:semicolon
r_return
id|found_page
suffix:semicolon
)brace
eof
