multiline_comment|/*&n; *  linux/mm/swap_state.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; *&n; *  Rewritten to use page cache, (C) 1998 Stephen Tweedie&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * We may have stale swap cache pages in memory: notice&n; * them here and get rid of the unnecessary final write.&n; */
DECL|function|swap_writepage
r_static
r_int
id|swap_writepage
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
id|remove_exclusive_swap_page
c_func
(paren
id|page
)paren
)paren
(brace
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|rw_swap_page
c_func
(paren
id|WRITE
comma
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|swap_aops
r_static
r_struct
id|address_space_operations
id|swap_aops
op_assign
(brace
id|writepage
suffix:colon
id|swap_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
)brace
suffix:semicolon
DECL|variable|swapper_space
r_struct
id|address_space
id|swapper_space
op_assign
(brace
id|LIST_HEAD_INIT
c_func
(paren
id|swapper_space.clean_pages
)paren
comma
id|LIST_HEAD_INIT
c_func
(paren
id|swapper_space.dirty_pages
)paren
comma
id|LIST_HEAD_INIT
c_func
(paren
id|swapper_space.locked_pages
)paren
comma
l_int|0
comma
multiline_comment|/* nrpages&t;*/
op_amp
id|swap_aops
comma
)brace
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
DECL|macro|INC_CACHE_INFO
mdefine_line|#define INC_CACHE_INFO(x)&t;(swap_cache_info.x++)
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
macro_line|#else
DECL|macro|INC_CACHE_INFO
mdefine_line|#define INC_CACHE_INFO(x)&t;do { } while (0)
macro_line|#endif
DECL|function|add_to_swap_cache
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
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
id|BUG
c_func
(paren
)paren
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
r_if
c_cond
(paren
id|add_to_page_cache_unique
c_func
(paren
id|page
comma
op_amp
id|swapper_space
comma
id|entry.val
comma
id|page_hash
c_func
(paren
op_amp
id|swapper_space
comma
id|entry.val
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|exist_race
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|PageSwapCache
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
r_if
c_cond
(paren
op_logical_neg
id|PageSwapCache
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
id|ClearPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|__remove_inode_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|INC_CACHE_INFO
c_func
(paren
id|del_total
)paren
suffix:semicolon
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
id|block_flushpage
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|entry.val
op_assign
id|page-&gt;index
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagecache_lock
)paren
suffix:semicolon
id|__delete_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pagecache_lock
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
multiline_comment|/* &n;&t; * If we are the only user, then try to free up the swap cache. &n;&t; * &n;&t; * Its ok to check for PageSwapCache without the page lock&n;&t; * here because we are going to recheck again inside &n;&t; * exclusive_swap_page() _with_ the lock. &n;&t; * &t;&t;&t;&t;&t;- Marcelo&n;&t; */
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
id|TryLockPage
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
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
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
id|found
suffix:semicolon
id|found
op_assign
id|find_get_page
c_func
(paren
op_amp
id|swapper_space
comma
id|entry.val
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unsafe to assert PageSwapCache and mapping on page found:&n;&t; * if SMP nothing prevents swapoff from deleting this page from&n;&t; * the swap cache at this moment.  find_lock_page would prevent&n;&t; * that, but no need to change: we _have_ got the right page.&n;&t; */
id|INC_CACHE_INFO
c_func
(paren
id|find_total
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
id|INC_CACHE_INFO
c_func
(paren
id|find_success
)paren
suffix:semicolon
r_return
id|found
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
multiline_comment|/*&n;&t;&t; * First check the swap cache.  Since this is normally&n;&t;&t; * called after lookup_swap_cache() failed, re-calling&n;&t;&t; * that would confuse statistics: use find_get_page()&n;&t;&t; * directly.&n;&t;&t; */
id|found_page
op_assign
id|find_get_page
c_func
(paren
op_amp
id|swapper_space
comma
id|entry.val
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
id|alloc_page
c_func
(paren
id|GFP_HIGHUSER
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
multiline_comment|/*&n;&t;&t; * Associate the page with swap entry in the swap cache.&n;&t;&t; * May fail (-ENOENT) if swap entry has been freed since&n;&t;&t; * our caller observed it.  May fail (-EEXIST) if there&n;&t;&t; * is already a page associated with this entry in the&n;&t;&t; * swap cache: added by a racing read_swap_cache_async,&n;&t;&t; * or by try_to_swap_out (or shmem_writepage) re-using&n;&t;&t; * the just freed swap entry for an existing page.&n;&t;&t; */
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
id|rw_swap_page
c_func
(paren
id|READ
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
