multiline_comment|/*&n; * mm/truncate.c - code for taking down pages from address_spaces&n; *&n; * Copyright (C) 2002, Linus Torvalds&n; *&n; * 10Sep2002&t;akpm@zip.com.au&n; *&t;&t;Initial version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;/* grr. try_to_release_page,&n;&t;&t;&t;&t;   block_invalidatepage */
DECL|function|do_invalidatepage
r_static
r_int
id|do_invalidatepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
)paren
(brace
r_int
(paren
op_star
id|invalidatepage
)paren
(paren
r_struct
id|page
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|invalidatepage
op_assign
id|page-&gt;mapping-&gt;a_ops-&gt;invalidatepage
suffix:semicolon
r_if
c_cond
(paren
id|invalidatepage
op_eq
l_int|NULL
)paren
id|invalidatepage
op_assign
id|block_invalidatepage
suffix:semicolon
r_return
(paren
op_star
id|invalidatepage
)paren
(paren
id|page
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|truncate_partial_page
r_static
r_inline
r_void
id|truncate_partial_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|partial
)paren
(brace
id|memclear_highpage_flush
c_func
(paren
id|page
comma
id|partial
comma
id|PAGE_CACHE_SIZE
op_minus
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
id|do_invalidatepage
c_func
(paren
id|page
comma
id|partial
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If truncate cannot remove the fs-private metadata from the page, the page&n; * becomes anonymous.  It will be left on the LRU and may even be mapped into&n; * user pagetables if we&squot;re racing with filemap_nopage().&n; *&n; * We need to bale out if page-&gt;mapping is no longer equal to the original&n; * mapping.  This happens a) when the VM reclaimed the page while we waited on&n; * its lock, b) when a concurrent invalidate_inode_pages got there first and&n; * c) when tmpfs swizzles a page between a tmpfs inode and swapper_space.&n; */
r_static
r_void
DECL|function|truncate_complete_page
id|truncate_complete_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_ne
id|mapping
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|PagePrivate
c_func
(paren
id|page
)paren
)paren
id|do_invalidatepage
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|clear_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|ClearPageMappedToDisk
c_func
(paren
id|page
)paren
suffix:semicolon
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
)brace
multiline_comment|/*&n; * This is for invalidate_inode_pages().  That function can be called at&n; * any time, and is not supposed to throw away dirty pages.  But pages can&n; * be marked dirty at any time too.  So we re-check the dirtiness inside&n; * -&gt;page_lock.  That provides exclusion against the __set_page_dirty&n; * functions.&n; */
r_static
r_void
DECL|function|invalidate_complete_page
id|invalidate_complete_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_ne
id|mapping
)paren
r_return
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
id|try_to_release_page
c_func
(paren
id|page
comma
l_int|0
)paren
)paren
r_return
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|ClearPageUptodate
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
)brace
)brace
multiline_comment|/**&n; * truncate_inode_pages - truncate *all* the pages from an offset&n; * @mapping: mapping to truncate&n; * @lstart: offset from which to truncate&n; *&n; * Truncate the page cache at a set offset, removing the pages that are beyond&n; * that offset (and zeroing out partial pages).&n; *&n; * Truncate takes two passes - the first pass is nonblocking.  It will not&n; * block on page locks and it will not block on writeback.  The second pass&n; * will wait.  This is to prevent as much IO as possible in the affected region.&n; * The first pass will remove most pages, so the search cost of the second pass&n; * is low.&n; *&n; * When looking at page-&gt;index outside the page lock we need to be careful to&n; * copy it into a local to avoid races (it could change at any time).&n; *&n; * We pass down the cache-hot hint to the page freeing code.  Even if the&n; * mapping is large, it is probably the case that the final pages are the most&n; * recently touched, and freeing happens in ascending file offset order.&n; *&n; * Called under (and serialised by) inode-&gt;i_sem.&n; */
DECL|function|truncate_inode_pages
r_void
id|truncate_inode_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|loff_t
id|lstart
)paren
(brace
r_const
id|pgoff_t
id|start
op_assign
(paren
id|lstart
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_const
r_int
id|partial
op_assign
id|lstart
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_struct
id|pagevec
id|pvec
suffix:semicolon
id|pgoff_t
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pvec
comma
l_int|0
)paren
suffix:semicolon
id|next
op_assign
id|start
suffix:semicolon
r_while
c_loop
(paren
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
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
op_amp
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
id|pvec.pages
(braket
id|i
)braket
suffix:semicolon
id|pgoff_t
id|page_index
op_assign
id|page-&gt;index
suffix:semicolon
r_if
c_cond
(paren
id|page_index
OG
id|next
)paren
id|next
op_assign
id|page_index
suffix:semicolon
id|next
op_increment
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
r_continue
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
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|truncate_complete_page
c_func
(paren
id|mapping
comma
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
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|find_lock_page
c_func
(paren
id|mapping
comma
id|start
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
id|truncate_partial_page
c_func
(paren
id|page
comma
id|partial
)paren
suffix:semicolon
id|unlock_page
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
)brace
id|next
op_assign
id|start
suffix:semicolon
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
op_logical_neg
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
r_if
c_cond
(paren
id|next
op_eq
id|start
)paren
r_break
suffix:semicolon
id|next
op_assign
id|start
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
op_amp
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
id|pvec.pages
(braket
id|i
)braket
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OG
id|next
)paren
id|next
op_assign
id|page-&gt;index
suffix:semicolon
id|next
op_increment
suffix:semicolon
id|truncate_complete_page
c_func
(paren
id|mapping
comma
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
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lstart
op_eq
l_int|0
op_logical_and
id|mapping-&gt;nrpages
)paren
id|printk
c_func
(paren
l_string|&quot;%s: I goofed!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * invalidate_inode_pages - Invalidate all the unlocked pages of one inode&n; * @inode: the inode which pages we want to invalidate&n; *&n; * This function only removes the unlocked pages, if you want to&n; * remove all the pages of one inode, you must call truncate_inode_pages.&n; *&n; * invalidate_inode_pages() will not block on IO activity. It will not&n; * invalidate pages which are dirty, locked, under writeback or mapped into&n; * pagetables.&n; */
DECL|function|invalidate_inode_pages
r_void
id|invalidate_inode_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_struct
id|pagevec
id|pvec
suffix:semicolon
id|pgoff_t
id|next
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pvec
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
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
op_amp
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
id|pvec.pages
(braket
id|i
)braket
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
(brace
id|next
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page-&gt;index
OG
id|next
)paren
id|next
op_assign
id|page-&gt;index
suffix:semicolon
id|next
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageDirty
c_func
(paren
id|page
)paren
op_logical_or
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
r_goto
id|unlock
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
r_goto
id|unlock
suffix:semicolon
id|invalidate_complete_page
c_func
(paren
id|mapping
comma
id|page
)paren
suffix:semicolon
id|unlock
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * invalidate_inode_pages2 - remove all unmapped pages from an address_space&n; * @mapping - the address_space&n; *&n; * invalidate_inode_pages2() is like truncate_inode_pages(), except for the case&n; * where the page is seen to be mapped into process pagetables.  In that case,&n; * the page is marked clean but is left attached to its address_space.&n; *&n; * FIXME: invalidate_inode_pages2() is probably trivially livelockable.&n; */
DECL|function|invalidate_inode_pages2
r_void
id|invalidate_inode_pages2
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_struct
id|pagevec
id|pvec
suffix:semicolon
id|pgoff_t
id|next
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|pvec
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pagevec_lookup
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
id|next
comma
id|PAGEVEC_SIZE
)paren
)paren
(brace
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
op_amp
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
id|pvec.pages
(braket
id|i
)braket
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
op_eq
id|mapping
)paren
(brace
multiline_comment|/* truncate race? */
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
id|next
op_assign
id|page-&gt;index
op_plus
l_int|1
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
id|clear_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|invalidate_complete_page
c_func
(paren
id|mapping
comma
id|page
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|pagevec_release
c_func
(paren
op_amp
id|pvec
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
eof
