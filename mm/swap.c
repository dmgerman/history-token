multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; */
multiline_comment|/*&n; * This file contains the default values for the opereation of the&n; * Linux VM subsystem. Fine-tuning documentation can be found in&n; * linux/Documentation/sysctl/vm.txt.&n; * Started 18.12.91&n; * Swap aging added 23.2.95, Stephen Tweedie.&n; * Buffermem limits added 12.3.98, Rik van Riel.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm_inline.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/prefetch.h&gt;
multiline_comment|/* How many pages do we try to swap or page in/out together? */
DECL|variable|page_cluster
r_int
id|page_cluster
suffix:semicolon
multiline_comment|/*&n; * FIXME: speed this up?&n; */
DECL|function|activate_page
r_void
id|activate_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|zone
op_star
id|zone
op_assign
id|page_zone
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageLRU
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|PageActive
c_func
(paren
id|page
)paren
)paren
(brace
id|del_page_from_inactive_list
c_func
(paren
id|zone
comma
id|page
)paren
suffix:semicolon
id|SetPageActive
c_func
(paren
id|page
)paren
suffix:semicolon
id|add_page_to_active_list
c_func
(paren
id|zone
comma
id|page
)paren
suffix:semicolon
id|inc_page_state
c_func
(paren
id|pgactivate
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * lru_cache_add: add a page to the page lists&n; * @page: the page to add&n; */
DECL|variable|lru_add_pvecs
r_static
r_struct
id|pagevec
id|lru_add_pvecs
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|lru_cache_add
r_void
id|lru_cache_add
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|pagevec
op_star
id|pvec
op_assign
op_amp
id|lru_add_pvecs
(braket
id|get_cpu
c_func
(paren
)paren
)braket
suffix:semicolon
id|page_cache_get
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
id|pvec
comma
id|page
)paren
)paren
id|__pagevec_lru_add
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|lru_add_drain
r_void
id|lru_add_drain
c_func
(paren
r_void
)paren
(brace
r_struct
id|pagevec
op_star
id|pvec
op_assign
op_amp
id|lru_add_pvecs
(braket
id|get_cpu
c_func
(paren
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
)paren
id|__pagevec_lru_add
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This path almost never happens for VM activity - pages are normally&n; * freed via pagevecs.  But it gets used by networking.&n; */
DECL|function|__page_cache_release
r_void
id|__page_cache_release
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|zone
op_star
id|zone
op_assign
id|page_zone
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|zone-&gt;lru_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TestClearPageLRU
c_func
(paren
id|page
)paren
)paren
id|del_page_from_lru
c_func
(paren
id|zone
comma
id|page
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
op_ne
l_int|0
)paren
id|page
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|zone-&gt;lru_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
id|free_hot_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Batched page_cache_release().  Decrement the reference count on all the&n; * passed pages.  If it fell to zero then remove the page from the LRU and&n; * free it.&n; *&n; * Avoid taking zone-&gt;lru_lock if possible, but if it is taken, retain it&n; * for the remainder of the operation.&n; *&n; * The locking in this function is against shrink_cache(): we recheck the&n; * page count inside the lock to see whether shrink_cache grabbed the page&n; * via the LRU.  If it did, give up: shrink_cache will free it.&n; */
DECL|function|release_pages
r_void
id|release_pages
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
comma
r_int
id|cold
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pagevec
id|pages_to_free
suffix:semicolon
r_struct
id|zone
op_star
id|zone
op_assign
l_int|NULL
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pages_to_free
comma
id|cold
)paren
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pages
(braket
id|i
)braket
suffix:semicolon
r_struct
id|zone
op_star
id|pagezone
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_or
op_logical_neg
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|pagezone
op_assign
id|page_zone
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pagezone
op_ne
id|zone
)paren
(brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|zone
op_assign
id|pagezone
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|TestClearPageLRU
c_func
(paren
id|page
)paren
)paren
id|del_page_from_lru
c_func
(paren
id|zone
comma
id|page
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
r_if
c_cond
(paren
op_logical_neg
id|pagevec_add
c_func
(paren
op_amp
id|pages_to_free
comma
id|page
)paren
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|__pagevec_free
c_func
(paren
op_amp
id|pages_to_free
)paren
suffix:semicolon
id|pagevec_reinit
c_func
(paren
op_amp
id|pages_to_free
)paren
suffix:semicolon
id|zone
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* No lock is held */
)brace
)brace
)brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|pagevec_free
c_func
(paren
op_amp
id|pages_to_free
)paren
suffix:semicolon
)brace
DECL|function|__pagevec_release
r_void
id|__pagevec_release
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
id|release_pages
c_func
(paren
id|pvec-&gt;pages
comma
id|pagevec_count
c_func
(paren
id|pvec
)paren
comma
id|pvec-&gt;cold
)paren
suffix:semicolon
id|pagevec_reinit
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pagevec_release() for pages which are known to not be on the LRU&n; *&n; * This function reinitialises the caller&squot;s pagevec.&n; */
DECL|function|__pagevec_release_nonlru
r_void
id|__pagevec_release_nonlru
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pagevec
id|pages_to_free
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pages_to_free
comma
id|pvec-&gt;cold
)paren
suffix:semicolon
id|pages_to_free.cold
op_assign
id|pvec-&gt;cold
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
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec-&gt;pages
(braket
id|i
)braket
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
r_if
c_cond
(paren
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
id|pagevec_add
c_func
(paren
op_amp
id|pages_to_free
comma
id|page
)paren
suffix:semicolon
)brace
id|pagevec_free
c_func
(paren
op_amp
id|pages_to_free
)paren
suffix:semicolon
id|pagevec_reinit
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Move all the inactive pages to the head of the inactive list and release&n; * them.  Reinitialises the caller&squot;s pagevec.&n; */
DECL|function|pagevec_deactivate_inactive
r_void
id|pagevec_deactivate_inactive
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|zone
op_star
id|zone
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
op_eq
l_int|0
)paren
r_return
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
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec-&gt;pages
(braket
id|i
)braket
suffix:semicolon
r_struct
id|zone
op_star
id|pagezone
op_assign
id|page_zone
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pagezone
op_ne
id|zone
)paren
(brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|zone
op_assign
id|pagezone
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|PageActive
c_func
(paren
id|page
)paren
op_logical_and
id|PageLRU
c_func
(paren
id|page
)paren
)paren
id|list_move
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|pagezone-&gt;inactive_list
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|__pagevec_release
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add the passed pages to the LRU, then drop the caller&squot;s refcount&n; * on them.  Reinitialises the caller&squot;s pagevec.&n; *&n; * Mapped pages go onto the active list.&n; */
DECL|function|__pagevec_lru_add
r_void
id|__pagevec_lru_add
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|zone
op_star
id|zone
op_assign
l_int|NULL
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
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec-&gt;pages
(braket
id|i
)braket
suffix:semicolon
r_struct
id|zone
op_star
id|pagezone
op_assign
id|page_zone
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pagezone
op_ne
id|zone
)paren
(brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|zone
op_assign
id|pagezone
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
)brace
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
id|page_mapped
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|TestSetPageActive
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
id|add_page_to_active_list
c_func
(paren
id|zone
comma
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|add_page_to_inactive_list
c_func
(paren
id|zone
comma
id|page
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|zone
)paren
id|spin_unlock_irq
c_func
(paren
op_amp
id|zone-&gt;lru_lock
)paren
suffix:semicolon
id|pagevec_release
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to drop buffers from the pages in a pagevec&n; */
DECL|function|pagevec_strip
r_void
id|pagevec_strip
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
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
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pvec-&gt;pages
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|PagePrivate
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
id|try_to_release_page
c_func
(paren
id|page
comma
l_int|0
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
)brace
multiline_comment|/**&n; * pagevec_lookup - gang pagecache lookup&n; * @pvec:&t;Where the resulting pages are placed&n; * @mapping:&t;The address_space to search&n; * @start:&t;The starting page index&n; * @nr_pages:&t;The maximum number of pages&n; *&n; * pagevec_lookup() will search for and return a group of up to @nr_pages pages&n; * in the mapping.  The pages are placed in @pvec.  pagevec_lookup() takes a&n; * reference against the pages in @pvec.&n; *&n; * The search returns a group of mapping-contiguous pages with ascending&n; * indexes.  There may be holes in the indices due to not-present pages.&n; *&n; * pagevec_lookup() returns the number of pages which were found.&n; */
DECL|function|pagevec_lookup
r_int
r_int
id|pagevec_lookup
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
comma
r_struct
id|address_space
op_star
id|mapping
comma
id|pgoff_t
id|start
comma
r_int
r_int
id|nr_pages
)paren
(brace
id|pvec-&gt;nr
op_assign
id|find_get_pages
c_func
(paren
id|mapping
comma
id|start
comma
id|nr_pages
comma
id|pvec-&gt;pages
)paren
suffix:semicolon
r_return
id|pagevec_count
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform any setup for the swap system&n; */
DECL|function|swap_setup
r_void
id|__init
id|swap_setup
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|megs
op_assign
id|num_physpages
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Use a smaller cluster for small-memory machines */
r_if
c_cond
(paren
id|megs
OL
l_int|16
)paren
id|page_cluster
op_assign
l_int|2
suffix:semicolon
r_else
id|page_cluster
op_assign
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t; * Right now other parts of the system means that we&n;&t; * _really_ don&squot;t want to cluster much more&n;&t; */
)brace
eof
