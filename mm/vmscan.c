multiline_comment|/*&n; *  linux/mm/vmscan.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, Stephen Tweedie.&n; *  kswapd added: 7.1.96  sct&n; *  Removed kswapd_ctl limits, and swap out as many pages as needed&n; *  to bring the system back to freepages.high: 2.4.97, Rik van Riel.&n; *  Zone aware kswapd started 02/00, Kanoj Sarcar (kanoj@sgi.com).&n; *  Multiqueue VM started 5.8.00, Rik van Riel.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;/* for try_to_release_page() */
macro_line|#include &lt;linux/pagevec.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
multiline_comment|/*&n; * The &quot;priority&quot; of VM scanning is how much of the queues we&n; * will scan in one go. A value of 6 for DEF_PRIORITY implies&n; * that we&squot;ll scan 1/64th of the queues (&quot;queue_length &gt;&gt; 6&quot;)&n; * during a normal aging round.&n; */
DECL|macro|DEF_PRIORITY
mdefine_line|#define DEF_PRIORITY (6)
macro_line|#ifdef ARCH_HAS_PREFETCH
DECL|macro|prefetch_prev_lru_page
mdefine_line|#define prefetch_prev_lru_page(_page, _base, _field)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_page)-&gt;lru.prev != _base) {&t;&t;&t;&bslash;&n;&t;&t;&t;struct page *prev;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;prev = list_entry(_page-&gt;lru.prev,&t;&t;&bslash;&n;&t;&t;&t;&t;&t;struct page, lru);&t;&t;&bslash;&n;&t;&t;&t;prefetch(&amp;prev-&gt;_field);&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|prefetch_prev_lru_page
mdefine_line|#define prefetch_prev_lru_page(_page, _base, _field) do { } while (0)
macro_line|#endif
macro_line|#ifdef ARCH_HAS_PREFETCHW
DECL|macro|prefetchw_prev_lru_page
mdefine_line|#define prefetchw_prev_lru_page(_page, _base, _field)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_page)-&gt;lru.prev != _base) {&t;&t;&t;&bslash;&n;&t;&t;&t;struct page *prev;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;prev = list_entry(_page-&gt;lru.prev,&t;&t;&bslash;&n;&t;&t;&t;&t;&t;struct page, lru);&t;&t;&bslash;&n;&t;&t;&t;prefetchw(&amp;prev-&gt;_field);&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|prefetchw_prev_lru_page
mdefine_line|#define prefetchw_prev_lru_page(_page, _base, _field) do { } while (0)
macro_line|#endif
multiline_comment|/* Must be called with page&squot;s pte_chain_lock held. */
DECL|function|page_mapping_inuse
r_static
r_inline
r_int
id|page_mapping_inuse
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
multiline_comment|/* Page is in somebody&squot;s page tables. */
r_if
c_cond
(paren
id|page-&gt;pte.chain
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* XXX: does this happen ? */
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* File is mmap&squot;d by somebody. */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap
)paren
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_shared
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|is_page_cache_freeable
r_static
r_inline
r_int
id|is_page_cache_freeable
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|page_count
c_func
(paren
id|page
)paren
op_minus
op_logical_neg
op_logical_neg
id|PagePrivate
c_func
(paren
id|page
)paren
op_eq
l_int|2
suffix:semicolon
)brace
r_static
multiline_comment|/* inline */
r_int
DECL|function|shrink_list
id|shrink_list
c_func
(paren
r_struct
id|list_head
op_star
id|page_list
comma
r_int
id|nr_pages
comma
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|priority
comma
r_int
op_star
id|max_scan
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|ret_pages
)paren
suffix:semicolon
r_struct
id|pagevec
id|freed_pvec
suffix:semicolon
r_const
r_int
id|nr_pages_in
op_assign
id|nr_pages
suffix:semicolon
r_int
id|pgactivate
op_assign
l_int|0
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|freed_pvec
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|page_list
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|may_enter_fs
suffix:semicolon
id|page
op_assign
id|list_entry
c_func
(paren
id|page_list-&gt;prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memclass
c_func
(paren
id|page_zone
c_func
(paren
id|page
)paren
comma
id|classzone
)paren
)paren
r_goto
id|keep
suffix:semicolon
r_if
c_cond
(paren
id|TestSetPageLocked
c_func
(paren
id|page
)paren
)paren
r_goto
id|keep
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageActive
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|may_enter_fs
op_assign
(paren
id|gfp_mask
op_amp
id|__GFP_FS
)paren
op_logical_or
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
op_logical_and
(paren
id|gfp_mask
op_amp
id|__GFP_IO
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|may_enter_fs
)paren
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* throttling */
r_else
r_goto
id|keep_locked
suffix:semicolon
)brace
id|pte_chain_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_referenced
c_func
(paren
id|page
)paren
op_logical_and
id|page_mapping_inuse
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/* In active use or really unfreeable.  Activate it. */
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|activate_locked
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Anonymous process memory without backing store. Try to&n;&t;&t; * allocate it some swap space here.&n;&t;&t; *&n;&t;&t; * XXX: implement swap clustering ?&n;&t;&t; */
r_if
c_cond
(paren
id|page-&gt;pte.chain
op_logical_and
op_logical_neg
id|page-&gt;mapping
op_logical_and
op_logical_neg
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
(brace
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_to_swap
c_func
(paren
id|page
)paren
)paren
r_goto
id|activate_locked
suffix:semicolon
id|pte_chain_lock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The page is mapped into the page tables of one or more&n;&t;&t; * processes. Try to unmap it here.&n;&t;&t; */
r_if
c_cond
(paren
id|page-&gt;pte.chain
)paren
(brace
r_switch
c_cond
(paren
id|try_to_unmap
c_func
(paren
id|page
)paren
)paren
(brace
r_case
id|SWAP_ERROR
suffix:colon
r_case
id|SWAP_FAIL
suffix:colon
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|activate_locked
suffix:semicolon
r_case
id|SWAP_AGAIN
suffix:colon
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|keep_locked
suffix:semicolon
r_case
id|SWAP_SUCCESS
suffix:colon
suffix:semicolon
multiline_comment|/* try to free the page below */
)brace
)brace
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
multiline_comment|/*&n;&t;&t; * FIXME: this is CPU-inefficient for shared mappings.&n;&t;&t; * try_to_unmap() will set the page dirty and -&gt;vm_writeback&n;&t;&t; * will write it.  So we&squot;re back to page-at-a-time writepage&n;&t;&t; * in LRU order.&n;&t;&t; */
r_if
c_cond
(paren
id|PageDirty
c_func
(paren
id|page
)paren
op_logical_and
id|is_page_cache_freeable
c_func
(paren
id|page
)paren
op_logical_and
id|mapping
op_logical_and
id|may_enter_fs
)paren
(brace
r_int
(paren
op_star
id|writeback
)paren
(paren
r_struct
id|page
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_const
r_int
id|cluster_size
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
r_int
id|nr_to_write
op_assign
id|cluster_size
suffix:semicolon
id|writeback
op_assign
id|mapping-&gt;a_ops-&gt;vm_writeback
suffix:semicolon
r_if
c_cond
(paren
id|writeback
op_eq
l_int|NULL
)paren
id|writeback
op_assign
id|generic_vm_writeback
suffix:semicolon
(paren
op_star
id|writeback
)paren
(paren
id|page
comma
op_amp
id|nr_to_write
)paren
suffix:semicolon
op_star
id|max_scan
op_sub_assign
(paren
id|cluster_size
op_minus
id|nr_to_write
)paren
suffix:semicolon
r_goto
id|keep
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If the page has buffers, try to free the buffer mappings&n;&t;&t; * associated with this page. If we succeed we try to free&n;&t;&t; * the page as well.&n;&t;&t; *&n;&t;&t; * We do this even if the page is PageDirty().&n;&t;&t; * try_to_release_page() does not perform I/O, but it is&n;&t;&t; * possible for a page to have PageDirty set, but it is actually&n;&t;&t; * clean (all its buffers are clean).  This happens if the&n;&t;&t; * buffers were written out directly, with submit_bh(). ext3&n;&t;&t; * will do this, as well as the blockdev mapping. &n;&t;&t; * try_to_release_page() will discover that cleanness and will&n;&t;&t; * drop the buffers and mark the page clean - it can be freed.&n;&t;&t; *&n;&t;&t; * Rarely, pages can have buffers and no -&gt;mapping.  These are&n;&t;&t; * the pages which were not successfully invalidated in&n;&t;&t; * truncate_complete_page().  We try to drop those buffers here&n;&t;&t; * and if that worked, and the page is no longer mapped into&n;&t;&t; * process address space (page_count == 0) it can be freed.&n;&t;&t; * Otherwise, leave the page on the LRU so it is swappable.&n;&t;&t; */
r_if
c_cond
(paren
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_to_release_page
c_func
(paren
id|page
comma
l_int|0
)paren
)paren
r_goto
id|keep_locked
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
op_logical_and
id|page_count
c_func
(paren
id|page
)paren
op_eq
l_int|1
)paren
r_goto
id|free_it
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
r_goto
id|keep_locked
suffix:semicolon
multiline_comment|/* truncate got there first */
id|write_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The non-racy check for busy page.  It is critical to check&n;&t;&t; * PageDirty _after_ making sure that the page is freeable and&n;&t;&t; * not in use by anybody. &t;(pagecache + us == 2)&n;&t;&t; */
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
op_ne
l_int|2
op_logical_or
id|PageDirty
c_func
(paren
id|page
)paren
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_goto
id|keep_locked
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
id|swp_entry_t
id|swap
op_assign
(brace
dot
id|val
op_assign
id|page-&gt;index
)brace
suffix:semicolon
id|__delete_from_swap_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|swap
)paren
suffix:semicolon
)brace
r_else
(brace
id|__remove_from_page_cache
c_func
(paren
id|page
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
)brace
id|__put_page
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* The pagecache ref */
id|free_it
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|nr_pages
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pagevec_add
c_func
(paren
op_amp
id|freed_pvec
comma
id|page
)paren
)paren
id|__pagevec_release_nonlru
c_func
(paren
op_amp
id|freed_pvec
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|activate_locked
suffix:colon
id|SetPageActive
c_func
(paren
id|page
)paren
suffix:semicolon
id|pgactivate
op_increment
suffix:semicolon
id|keep_locked
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|keep
suffix:colon
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|ret_pages
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageLRU
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
id|list_splice
c_func
(paren
op_amp
id|ret_pages
comma
id|page_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
op_amp
id|freed_pvec
)paren
)paren
id|__pagevec_release_nonlru
c_func
(paren
op_amp
id|freed_pvec
)paren
suffix:semicolon
id|KERNEL_STAT_ADD
c_func
(paren
id|pgsteal
comma
id|nr_pages_in
op_minus
id|nr_pages
)paren
suffix:semicolon
id|KERNEL_STAT_ADD
c_func
(paren
id|pgactivate
comma
id|pgactivate
)paren
suffix:semicolon
r_return
id|nr_pages
suffix:semicolon
)brace
multiline_comment|/*&n; * pagemap_lru_lock is heavily contented.  We relieve it by quickly privatising&n; * a batch of pages and working on them outside the lock.  Any pages which were&n; * not freed will be added back to the LRU.&n; *&n; * shrink_cache() is passed the number of pages to try to free, and returns&n; * the number which are yet-to-free.&n; *&n; * For pagecache intensive workloads, the first loop here is the hottest spot&n; * in the kernel (apart from the copy_*_user functions).&n; */
r_static
multiline_comment|/* inline */
r_int
DECL|function|shrink_cache
id|shrink_cache
c_func
(paren
r_int
id|nr_pages
comma
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|priority
comma
r_int
id|max_scan
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|page_list
)paren
suffix:semicolon
r_struct
id|pagevec
id|pvec
suffix:semicolon
r_int
id|nr_to_process
suffix:semicolon
multiline_comment|/*&n;&t; * Try to ensure that we free `nr_pages&squot; pages in one pass of the loop.&n;&t; */
id|nr_to_process
op_assign
id|nr_pages
suffix:semicolon
r_if
c_cond
(paren
id|nr_to_process
OL
id|SWAP_CLUSTER_MAX
)paren
id|nr_to_process
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|lru_add_drain
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|max_scan
OG
l_int|0
op_logical_and
id|nr_pages
OG
l_int|0
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|n
OL
id|nr_to_process
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|inactive_list
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|inactive_list.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|prefetchw_prev_lru_page
c_func
(paren
id|page
comma
op_amp
id|inactive_list
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TestClearPageLRU
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
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* It is currently in pagevec_release() */
id|SetPageLRU
c_func
(paren
id|page
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|inactive_list
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|page_list
)paren
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|n
op_increment
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|page_list
)paren
)paren
r_goto
id|done
suffix:semicolon
id|max_scan
op_sub_assign
id|n
suffix:semicolon
id|mod_page_state
c_func
(paren
id|nr_inactive
comma
op_minus
id|n
)paren
suffix:semicolon
id|KERNEL_STAT_ADD
c_func
(paren
id|pgscan
comma
id|n
)paren
suffix:semicolon
id|nr_pages
op_assign
id|shrink_list
c_func
(paren
op_amp
id|page_list
comma
id|nr_pages
comma
id|classzone
comma
id|gfp_mask
comma
id|priority
comma
op_amp
id|max_scan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
op_logical_and
id|list_empty
c_func
(paren
op_amp
id|page_list
)paren
)paren
r_goto
id|done
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Put back any unfreeable pages.&n;&t;&t; */
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|page_list
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|page_list.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TestSetPageLRU
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
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageActive
c_func
(paren
id|page
)paren
)paren
id|__add_page_to_active_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|add_page_to_inactive_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pagevec_add
c_func
(paren
op_amp
id|pvec
comma
id|page
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
id|__pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
id|done
suffix:colon
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
r_return
id|nr_pages
suffix:semicolon
)brace
multiline_comment|/*&n; * This moves pages from the active list to the inactive list.&n; *&n; * We move them the other way if the page is referenced by one or more&n; * processes, from rmap.&n; *&n; * If the pages are mostly unmapped, the processing is fast and it is&n; * appropriate to hold pagemap_lru_lock across the whole operation.  But if&n; * the pages are mapped, the processing is slow (page_referenced()) so we&n; * should drop pagemap_lru_lock around each page.  It&squot;s impossible to balance&n; * this, so instead we remove the pages from the LRU while processing them.&n; * It is safe to rely on PG_active against the non-LRU pages in here because&n; * nobody will play with that bit on a non-LRU page.&n; *&n; * The downside is that we have to touch page-&gt;count against each page.&n; * But we had to alter page-&gt;flags anyway.&n; */
DECL|function|refill_inactive
r_static
multiline_comment|/* inline */
r_void
id|refill_inactive
c_func
(paren
r_const
r_int
id|nr_pages_in
)paren
(brace
r_int
id|pgdeactivate
op_assign
l_int|0
suffix:semicolon
r_int
id|nr_pages
op_assign
id|nr_pages_in
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|l_hold
)paren
suffix:semicolon
multiline_comment|/* The pages which were snipped off */
id|LIST_HEAD
c_func
(paren
id|l_inactive
)paren
suffix:semicolon
multiline_comment|/* Pages to go onto the inactive_list */
id|LIST_HEAD
c_func
(paren
id|l_active
)paren
suffix:semicolon
multiline_comment|/* Pages to go onto the active_list */
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|pagevec
id|pvec
suffix:semicolon
id|lru_add_drain
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr_pages
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|active_list
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|active_list.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|prefetchw_prev_lru_page
c_func
(paren
id|page
comma
op_amp
id|active_list
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TestClearPageLRU
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
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|l_hold
)paren
suffix:semicolon
id|nr_pages
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|l_hold
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|l_hold.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;pte.chain
)paren
(brace
id|pte_chain_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;pte.chain
op_logical_and
id|page_referenced
c_func
(paren
id|page
)paren
)paren
(brace
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|l_active
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|l_inactive
)paren
suffix:semicolon
id|pgdeactivate
op_increment
suffix:semicolon
)brace
id|pagevec_init
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|l_inactive
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|l_inactive.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|prefetchw_prev_lru_page
c_func
(paren
id|page
comma
op_amp
id|l_inactive
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TestSetPageLRU
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
id|TestClearPageActive
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
id|list_move
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|inactive_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pagevec_add
c_func
(paren
op_amp
id|pvec
comma
id|page
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
id|__pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|l_active
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|l_active.prev
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|prefetchw_prev_lru_page
c_func
(paren
id|page
comma
op_amp
id|l_active
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TestSetPageLRU
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageActive
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|active_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pagevec_add
c_func
(paren
op_amp
id|pvec
comma
id|page
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
id|__pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|_pagemap_lru_lock
)paren
suffix:semicolon
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|mod_page_state
c_func
(paren
id|nr_active
comma
op_minus
id|pgdeactivate
)paren
suffix:semicolon
id|mod_page_state
c_func
(paren
id|nr_inactive
comma
id|pgdeactivate
)paren
suffix:semicolon
id|KERNEL_STAT_ADD
c_func
(paren
id|pgscan
comma
id|nr_pages_in
op_minus
id|nr_pages
)paren
suffix:semicolon
id|KERNEL_STAT_ADD
c_func
(paren
id|pgdeactivate
comma
id|pgdeactivate
)paren
suffix:semicolon
)brace
r_static
multiline_comment|/* inline */
r_int
DECL|function|shrink_caches
id|shrink_caches
c_func
(paren
id|zone_t
op_star
id|classzone
comma
r_int
id|priority
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|nr_pages
)paren
(brace
r_int
r_int
id|ratio
suffix:semicolon
r_struct
id|page_state
id|ps
suffix:semicolon
r_int
id|max_scan
suffix:semicolon
r_static
id|atomic_t
id|nr_to_refill
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kmem_cache_reap
c_func
(paren
id|gfp_mask
)paren
op_ge
id|nr_pages
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Try to keep the active list 2/3 of the size of the cache.  And&n;&t; * make sure that refill_inactive is given a decent number of pages.&n;&t; *&n;&t; * The &quot;ratio+1&quot; here is important.  With pagecache-intensive workloads&n;&t; * the inactive list is huge, and `ratio&squot; evaluates to zero all the&n;&t; * time.  Which pins the active list memory.  So we add one to `ratio&squot;&n;&t; * just to make sure that the kernel will slowly sift through the&n;&t; * active list.&n;&t; */
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
id|ratio
op_assign
(paren
r_int
r_int
)paren
id|nr_pages
op_star
id|ps.nr_active
op_div
(paren
(paren
id|ps.nr_inactive
op_or
l_int|1
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|atomic_add
c_func
(paren
id|ratio
op_plus
l_int|1
comma
op_amp
id|nr_to_refill
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|nr_to_refill
)paren
OG
id|SWAP_CLUSTER_MAX
)paren
(brace
id|atomic_sub
c_func
(paren
id|SWAP_CLUSTER_MAX
comma
op_amp
id|nr_to_refill
)paren
suffix:semicolon
id|refill_inactive
c_func
(paren
id|SWAP_CLUSTER_MAX
)paren
suffix:semicolon
)brace
id|max_scan
op_assign
id|ps.nr_inactive
op_div
id|priority
suffix:semicolon
id|nr_pages
op_assign
id|shrink_cache
c_func
(paren
id|nr_pages
comma
id|classzone
comma
id|gfp_mask
comma
id|priority
comma
id|max_scan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|wakeup_bdflush
c_func
(paren
)paren
suffix:semicolon
id|shrink_dcache_memory
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/* After shrinking the dcache, get rid of unused inodes too .. */
id|shrink_icache_memory
c_func
(paren
l_int|1
comma
id|gfp_mask
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_QUOTA
id|shrink_dqcache_memory
c_func
(paren
id|DEF_PRIORITY
comma
id|gfp_mask
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nr_pages
suffix:semicolon
)brace
DECL|function|try_to_free_pages
r_int
id|try_to_free_pages
c_func
(paren
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
(brace
r_int
id|priority
op_assign
id|DEF_PRIORITY
suffix:semicolon
r_int
id|nr_pages
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
id|KERNEL_STAT_INC
c_func
(paren
id|pageoutrun
)paren
suffix:semicolon
r_do
(brace
id|nr_pages
op_assign
id|shrink_caches
c_func
(paren
id|classzone
comma
id|priority
comma
id|gfp_mask
comma
id|nr_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|priority
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Hmm.. Cache shrink failed - time to kill something?&n;&t; * Mhwahahhaha! This is the part I really like. Giggle.&n;&t; */
id|out_of_memory
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kswapd_wait
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|kswapd_wait
)paren
suffix:semicolon
DECL|function|check_classzone_need_balance
r_static
r_int
id|check_classzone_need_balance
c_func
(paren
id|zone_t
op_star
id|classzone
)paren
(brace
id|zone_t
op_star
id|first_classzone
suffix:semicolon
id|first_classzone
op_assign
id|classzone-&gt;zone_pgdat-&gt;node_zones
suffix:semicolon
r_while
c_loop
(paren
id|classzone
op_ge
id|first_classzone
)paren
(brace
r_if
c_cond
(paren
id|classzone-&gt;free_pages
OG
id|classzone-&gt;pages_high
)paren
r_return
l_int|0
suffix:semicolon
id|classzone
op_decrement
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kswapd_balance_pgdat
r_static
r_int
id|kswapd_balance_pgdat
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
r_int
id|need_more_balance
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pgdat-&gt;nr_zones
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|i
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zone-&gt;need_balance
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_to_free_pages
c_func
(paren
id|zone
comma
id|GFP_KSWAPD
comma
l_int|0
)paren
)paren
(brace
id|zone-&gt;need_balance
op_assign
l_int|0
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_classzone_need_balance
c_func
(paren
id|zone
)paren
)paren
id|need_more_balance
op_assign
l_int|1
suffix:semicolon
r_else
id|zone-&gt;need_balance
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|need_more_balance
suffix:semicolon
)brace
DECL|function|kswapd_balance
r_static
r_void
id|kswapd_balance
c_func
(paren
r_void
)paren
(brace
r_int
id|need_more_balance
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_do
(brace
id|need_more_balance
op_assign
l_int|0
suffix:semicolon
id|pgdat
op_assign
id|pgdat_list
suffix:semicolon
r_do
id|need_more_balance
op_or_assign
id|kswapd_balance_pgdat
c_func
(paren
id|pgdat
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pgdat
op_assign
id|pgdat-&gt;pgdat_next
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|need_more_balance
)paren
suffix:semicolon
)brace
DECL|function|kswapd_can_sleep_pgdat
r_static
r_int
id|kswapd_can_sleep_pgdat
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
id|zone_t
op_star
id|zone
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pgdat-&gt;nr_zones
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zone-&gt;need_balance
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kswapd_can_sleep
r_static
r_int
id|kswapd_can_sleep
c_func
(paren
r_void
)paren
(brace
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
id|pgdat
op_assign
id|pgdat_list
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|kswapd_can_sleep_pgdat
c_func
(paren
id|pgdat
)paren
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|pgdat
op_assign
id|pgdat-&gt;pgdat_next
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The background pageout daemon, started as a kernel thread&n; * from the init process. &n; *&n; * This basically trickles out pages so that we have _some_&n; * free memory available even if there is no other activity&n; * that frees anything up. This is needed for things like routing&n; * etc, where we otherwise might have all activity going on in&n; * asynchronous contexts that cannot page things out.&n; *&n; * If there are applications that are active memory-allocators&n; * (most normal use), this basically shouldn&squot;t matter.&n; */
DECL|function|kswapd
r_int
id|kswapd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;kswapd&quot;
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|tsk-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the memory management that we&squot;re a &quot;memory allocator&quot;,&n;&t; * and that if we need more memory we should get access to it&n;&t; * regardless (see &quot;__alloc_pages()&quot;). &quot;kswapd&quot; should&n;&t; * never get caught in the normal page freeing logic.&n;&t; *&n;&t; * (Kswapd normally doesn&squot;t need memory anyway, but sometimes&n;&t; * you need a small amount of memory in order to be able to&n;&t; * page out something else, and this flag essentially protects&n;&t; * us from recursively trying to free more memory as we&squot;re&n;&t; * trying to free the first piece of memory in the first place).&n;&t; */
id|tsk-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
multiline_comment|/*&n;&t; * Kswapd main loop.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
id|refrigerator
c_func
(paren
id|PF_IOTHREAD
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kswapd_can_sleep
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we actually get into a low-memory situation,&n;&t;&t; * the processes needing more memory will wake us&n;&t;&t; * up on a more timely basis.&n;&t;&t; */
id|kswapd_balance
c_func
(paren
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|kswapd_init
r_static
r_int
id|__init
id|kswapd_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Starting kswapd&bslash;n&quot;
)paren
suffix:semicolon
id|swap_setup
c_func
(paren
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|kswapd
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGNAL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|kswapd_init
)paren
eof
