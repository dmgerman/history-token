multiline_comment|/*&n; *  linux/mm/swap.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; */
multiline_comment|/*&n; * This file contains the default values for the opereation of the&n; * Linux VM subsystem. Fine-tuning documentation can be found in&n; * linux/Documentation/sysctl/vm.txt.&n; * Started 18.12.91&n; * Swap aging added 23.2.95, Stephen Tweedie.&n; * Buffermem limits added 12.3.98, Rik van Riel.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_to/from_user */
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* How many pages do we try to swap or page in/out together? */
DECL|variable|page_cluster
r_int
id|page_cluster
suffix:semicolon
DECL|variable|pager_daemon
id|pager_daemon_t
id|pager_daemon
op_assign
(brace
l_int|512
comma
multiline_comment|/* base number for calculating the number of tries */
id|SWAP_CLUSTER_MAX
comma
multiline_comment|/* minimum number of tries */
l_int|8
comma
multiline_comment|/* do swap I/O in clusters of this size */
)brace
suffix:semicolon
multiline_comment|/*&n; * Move an inactive page to the active list.&n; */
DECL|function|activate_page_nolock
r_static
r_inline
r_void
id|activate_page_nolock
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
id|page
)paren
suffix:semicolon
id|add_page_to_active_list
c_func
(paren
id|page
)paren
suffix:semicolon
id|KERNEL_STAT_INC
c_func
(paren
id|pgactivate
)paren
suffix:semicolon
)brace
)brace
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
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|activate_page_nolock
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * lru_cache_add: add a page to the page lists&n; * @page: the page to add&n; */
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
r_if
c_cond
(paren
op_logical_neg
id|TestSetPageLRU
c_func
(paren
id|page
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|add_page_to_inactive_list
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * __lru_cache_del: remove a page from the page lists&n; * @page: the page to add&n; *&n; * This function is for when the caller already holds&n; * the pagemap_lru_lock.&n; */
DECL|function|__lru_cache_del
r_void
id|__lru_cache_del
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
id|TestClearPageLRU
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|PageActive
c_func
(paren
id|page
)paren
)paren
(brace
id|del_page_from_active_list
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|del_page_from_inactive_list
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * lru_cache_del: remove a page from the page lists&n; * @page: the page to remove&n; */
DECL|function|lru_cache_del
r_void
id|lru_cache_del
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|__lru_cache_del
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
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
