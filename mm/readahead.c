multiline_comment|/*&n; * mm/readahead.c - address_space-level file readahead.&n; *&n; * Copyright (C) 2002, Linus Torvalds&n; *&n; * 09Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
DECL|variable|default_backing_dev_info
r_struct
id|backing_dev_info
id|default_backing_dev_info
op_assign
(brace
dot
id|ra_pages
op_assign
(paren
id|VM_MAX_READAHEAD
op_star
l_int|1024
)paren
op_div
id|PAGE_CACHE_SIZE
comma
dot
id|state
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialise a struct file&squot;s readahead state&n; */
r_void
DECL|function|file_ra_state_init
id|file_ra_state_init
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
comma
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
id|memset
c_func
(paren
id|ra
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ra
)paren
)paren
suffix:semicolon
id|ra-&gt;ra_pages
op_assign
id|mapping-&gt;backing_dev_info-&gt;ra_pages
suffix:semicolon
)brace
multiline_comment|/*&n; * Return max readahead size for this inode in number-of-pages.&n; */
DECL|function|get_max_readahead
r_static
r_inline
r_int
r_int
id|get_max_readahead
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
)paren
(brace
r_return
id|ra-&gt;ra_pages
suffix:semicolon
)brace
DECL|function|get_min_readahead
r_static
r_inline
r_int
r_int
id|get_min_readahead
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
)paren
(brace
r_return
(paren
id|VM_MIN_READAHEAD
op_star
l_int|1024
)paren
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_static
r_int
DECL|function|read_pages
id|read_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file
op_star
id|filp
comma
r_struct
id|list_head
op_star
id|pages
comma
r_int
id|nr_pages
)paren
(brace
r_int
id|page_idx
suffix:semicolon
r_struct
id|pagevec
id|lru_pvec
suffix:semicolon
id|pagevec_init
c_func
(paren
op_amp
id|lru_pvec
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;a_ops-&gt;readpages
)paren
r_return
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|readpages
c_func
(paren
id|mapping
comma
id|pages
comma
id|nr_pages
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page_idx
op_assign
l_int|0
suffix:semicolon
id|page_idx
OL
id|nr_pages
suffix:semicolon
id|page_idx
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|list_entry
c_func
(paren
id|pages-&gt;prev
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_to_page_cache
c_func
(paren
id|page
comma
id|mapping
comma
id|page-&gt;index
)paren
)paren
(brace
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|readpage
c_func
(paren
id|filp
comma
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
id|lru_pvec
comma
id|page
)paren
)paren
id|__pagevec_lru_add
c_func
(paren
op_amp
id|lru_pvec
)paren
suffix:semicolon
)brace
r_else
(brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
id|pagevec_lru_add
c_func
(paren
op_amp
id|lru_pvec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Readahead design.&n; *&n; * The fields in struct file_ra_state represent the most-recently-executed&n; * readahead attempt:&n; *&n; * start:&t;Page index at which we started the readahead&n; * size:&t;Number of pages in that read&n; *              Together, these form the &quot;current window&quot;.&n; *              Together, start and size represent the `readahead window&squot;.&n; * next_size:   The number of pages to read on the next readahead miss.&n; *              Has the magical value -1UL if readahead has been disabled.&n; * prev_page:   The page which the readahead algorithm most-recently inspected.&n; *              prev_page is mainly an optimisation: if page_cache_readahead&n; *&t;&t;sees that it is again being called for a page which it just&n; *&t;&t;looked at, it can return immediately without making any state&n; *&t;&t;changes.&n; * ahead_start,&n; * ahead_size:  Together, these form the &quot;ahead window&quot;.&n; * ra_pages:&t;The externally controlled max readahead for this fd.&n; *&n; * The readahead code manages two windows - the &quot;current&quot; and the &quot;ahead&quot;&n; * windows.  The intent is that while the application is walking the pages&n; * in the current window, I/O is underway on the ahead window.  When the&n; * current window is fully traversed, it is replaced by the ahead window&n; * and the ahead window is invalidated.  When this copying happens, the&n; * new current window&squot;s pages are probably still locked.  When I/O has&n; * completed, we submit a new batch of I/O, creating a new ahead window.&n; *&n; * So:&n; *&n; *   ----|----------------|----------------|-----&n; *       ^start           ^start+size&n; *                        ^ahead_start     ^ahead_start+ahead_size&n; *&n; *         ^ When this page is read, we submit I/O for the&n; *           ahead window.&n; *&n; * A `readahead hit&squot; occurs when a read request is made against a page which is&n; * inside the current window.  Hits are good, and the window size (next_size)&n; * is grown aggressively when hits occur.  Two pages are added to the next&n; * window size on each hit, which will end up doubling the next window size by&n; * the time I/O is submitted for it.&n; *&n; * If readahead hits are more sparse (say, the application is only reading&n; * every second page) then the window will build more slowly.&n; *&n; * On a readahead miss (the application seeked away) the readahead window is&n; * shrunk by 25%.  We don&squot;t want to drop it too aggressively, because it is a&n; * good assumption that an application which has built a good readahead window&n; * will continue to perform linear reads.  Either at the new file position, or&n; * at the old one after another seek.&n; *&n; * There is a special-case: if the first page which the application tries to&n; * read happens to be the first page of the file, it is assumed that a linear&n; * read is about to happen and the window is immediately set to half of the&n; * device maximum.&n; * &n; * A page request at (start + size) is not a miss at all - it&squot;s just a part of&n; * sequential file reading.&n; *&n; * This function is to be called for every page which is read, rather than when&n; * it is time to perform readahead.  This is so the readahead algorithm can&n; * centrally work out the access patterns.  This could be costly with many tiny&n; * read()s, so we specifically optimise for that case with prev_page.&n; */
multiline_comment|/*&n; * do_page_cache_readahead actually reads a chunk of disk.  It allocates all&n; * the pages first, then submits them all for I/O. This avoids the very bad&n; * behaviour which would occur if page allocations are causing VM writeback.&n; * We really don&squot;t want to intermingle reads and writes like that.&n; *&n; * Returns the number of pages which actually had IO started against them.&n; */
DECL|function|do_page_cache_readahead
r_int
id|do_page_cache_readahead
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|nr_to_read
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|mapping-&gt;host
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|end_index
suffix:semicolon
multiline_comment|/* The last page we want to read */
id|LIST_HEAD
c_func
(paren
id|page_pool
)paren
suffix:semicolon
r_int
id|page_idx
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_size
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|end_index
op_assign
(paren
(paren
id|inode-&gt;i_size
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Preallocate as many pages as we will need.&n;&t; */
id|read_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page_idx
op_assign
l_int|0
suffix:semicolon
id|page_idx
OL
id|nr_to_read
suffix:semicolon
id|page_idx
op_increment
)paren
(brace
r_int
r_int
id|page_offset
op_assign
id|offset
op_plus
id|page_idx
suffix:semicolon
r_if
c_cond
(paren
id|page_offset
OG
id|end_index
)paren
r_break
suffix:semicolon
id|page
op_assign
id|radix_tree_lookup
c_func
(paren
op_amp
id|mapping-&gt;page_tree
comma
id|page_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_continue
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|page
op_assign
id|page_cache_alloc_cold
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_break
suffix:semicolon
id|page-&gt;index
op_assign
id|page_offset
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|page_pool
)paren
suffix:semicolon
id|ret
op_increment
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now start the IO.  We ignore I/O errors - if the page is not&n;&t; * uptodate then the caller will launch readpage again, and&n;&t; * will then handle the error.&n;&t; */
r_if
c_cond
(paren
id|ret
)paren
(brace
id|read_pages
c_func
(paren
id|mapping
comma
id|filp
comma
op_amp
id|page_pool
comma
id|ret
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|page_pool
)paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Check how effective readahead is being.  If the amount of started IO is&n; * less than expected then the file is partly or fully in pagecache and&n; * readahead isn&squot;t helping.  Shrink the window.&n; *&n; * But don&squot;t shrink it too much - the application may read the same page&n; * occasionally.&n; */
r_static
r_inline
r_void
DECL|function|check_ra_success
id|check_ra_success
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
comma
id|pgoff_t
id|attempt
comma
id|pgoff_t
id|actual
comma
id|pgoff_t
id|orig_next_size
)paren
(brace
r_if
c_cond
(paren
id|actual
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|orig_next_size
OG
l_int|1
)paren
(brace
id|ra-&gt;next_size
op_assign
id|orig_next_size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;ahead_size
)paren
id|ra-&gt;ahead_size
op_assign
id|ra-&gt;next_size
suffix:semicolon
)brace
r_else
(brace
id|ra-&gt;next_size
op_assign
op_minus
l_int|1UL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * page_cache_readahead is the main function.  If performs the adaptive&n; * readahead window size management and submits the readahead I/O.&n; */
DECL|function|page_cache_readahead
r_void
id|page_cache_readahead
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file_ra_state
op_star
id|ra
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
)paren
(brace
r_int
id|max
suffix:semicolon
r_int
id|min
suffix:semicolon
r_int
id|orig_next_size
suffix:semicolon
r_int
id|actual
suffix:semicolon
multiline_comment|/*&n;&t; * Here we detect the case where the application is performing&n;&t; * sub-page sized reads.  We avoid doing extra work and bogusly&n;&t; * perturbing the readahead window expansion logic.&n;&t; * If next_size is zero, this is the very first read for this&n;&t; * file handle, or the window is maximally shrunk.&n;&t; */
r_if
c_cond
(paren
id|offset
op_eq
id|ra-&gt;prev_page
)paren
(brace
r_if
c_cond
(paren
id|ra-&gt;next_size
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ra-&gt;next_size
op_eq
op_minus
l_int|1UL
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Maximally shrunk */
id|max
op_assign
id|get_max_readahead
c_func
(paren
id|ra
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* No readahead */
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|ra
)paren
suffix:semicolon
id|orig_next_size
op_assign
id|ra-&gt;next_size
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;next_size
op_eq
l_int|0
op_logical_and
id|offset
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Special case - first read from first page.&n;&t;&t; * We&squot;ll assume it&squot;s a whole-file read, and&n;&t;&t; * grow the window fast.&n;&t;&t; */
id|ra-&gt;next_size
op_assign
id|max
op_div
l_int|2
suffix:semicolon
r_goto
id|do_io
suffix:semicolon
)brace
id|ra-&gt;prev_page
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|ra-&gt;start
op_logical_and
id|offset
op_le
(paren
id|ra-&gt;start
op_plus
id|ra-&gt;size
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * A readahead hit.  Either inside the window, or one&n;&t;&t; * page beyond the end.  Expand the next readahead size.&n;&t;&t; */
id|ra-&gt;next_size
op_add_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * A miss - lseek, pread, etc.  Shrink the readahead&n;&t;&t; * window by 25%.&n;&t;&t; */
id|ra-&gt;next_size
op_sub_assign
id|ra-&gt;next_size
op_div
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ra-&gt;next_size
OG
id|max
)paren
id|ra-&gt;next_size
op_assign
id|max
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;next_size
OL
id|min
)paren
id|ra-&gt;next_size
op_assign
id|min
suffix:semicolon
multiline_comment|/*&n;&t; * Is this request outside the current window?&n;&t; */
r_if
c_cond
(paren
id|offset
OL
id|ra-&gt;start
op_logical_or
id|offset
op_ge
(paren
id|ra-&gt;start
op_plus
id|ra-&gt;size
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * A miss against the current window.  Have we merely&n;&t;&t; * advanced into the ahead window?&n;&t;&t; */
r_if
c_cond
(paren
id|offset
op_eq
id|ra-&gt;ahead_start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Yes, we have.  The ahead window now becomes&n;&t;&t;&t; * the current window.&n;&t;&t;&t; */
id|ra-&gt;start
op_assign
id|ra-&gt;ahead_start
suffix:semicolon
id|ra-&gt;size
op_assign
id|ra-&gt;ahead_size
suffix:semicolon
id|ra-&gt;prev_page
op_assign
id|ra-&gt;start
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
l_int|0
suffix:semicolon
id|ra-&gt;ahead_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Control now returns, probably to sleep until I/O&n;&t;&t;&t; * completes against the first ahead page.&n;&t;&t;&t; * When the second page in the old ahead window is&n;&t;&t;&t; * requested, control will return here and more I/O&n;&t;&t;&t; * will be submitted to build the new ahead window.&n;&t;&t;&t; */
r_goto
id|out
suffix:semicolon
)brace
id|do_io
suffix:colon
multiline_comment|/*&n;&t;&t; * This is the &quot;unusual&quot; path.  We come here during&n;&t;&t; * startup or after an lseek.  We invalidate the&n;&t;&t; * ahead window and get some I/O underway for the new&n;&t;&t; * current window.&n;&t;&t; */
id|ra-&gt;start
op_assign
id|offset
suffix:semicolon
id|ra-&gt;size
op_assign
id|ra-&gt;next_size
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Invalidate these */
id|ra-&gt;ahead_size
op_assign
l_int|0
suffix:semicolon
id|actual
op_assign
id|do_page_cache_readahead
c_func
(paren
id|mapping
comma
id|filp
comma
id|offset
comma
id|ra-&gt;size
)paren
suffix:semicolon
id|check_ra_success
c_func
(paren
id|ra
comma
id|ra-&gt;size
comma
id|actual
comma
id|orig_next_size
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * This read request is within the current window.  It is time&n;&t;&t; * to submit I/O for the ahead window while the application is&n;&t;&t; * crunching through the current window.&n;&t;&t; */
r_if
c_cond
(paren
id|ra-&gt;ahead_start
op_eq
l_int|0
)paren
(brace
id|ra-&gt;ahead_start
op_assign
id|ra-&gt;start
op_plus
id|ra-&gt;size
suffix:semicolon
id|ra-&gt;ahead_size
op_assign
id|ra-&gt;next_size
suffix:semicolon
id|actual
op_assign
id|do_page_cache_readahead
c_func
(paren
id|mapping
comma
id|filp
comma
id|ra-&gt;ahead_start
comma
id|ra-&gt;ahead_size
)paren
suffix:semicolon
id|check_ra_success
c_func
(paren
id|ra
comma
id|ra-&gt;ahead_size
comma
id|actual
comma
id|orig_next_size
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * For mmap reads (typically executables) the access pattern is fairly random,&n; * but somewhat ascending.  So readaround favours pages beyond the target one.&n; * We also boost the window size, as it can easily shrink due to misses.&n; */
DECL|function|page_cache_readaround
r_void
id|page_cache_readaround
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file_ra_state
op_star
id|ra
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|ra-&gt;next_size
op_ne
op_minus
l_int|1UL
)paren
(brace
r_const
r_int
r_int
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|ra
)paren
op_star
l_int|2
suffix:semicolon
r_int
r_int
id|target
suffix:semicolon
r_int
r_int
id|backward
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If next_size is zero then leave it alone, because that&squot;s a&n;&t;&t; * readahead startup state.&n;&t;&t; */
r_if
c_cond
(paren
id|ra-&gt;next_size
op_logical_and
id|ra-&gt;next_size
OL
id|min
)paren
id|ra-&gt;next_size
op_assign
id|min
suffix:semicolon
id|target
op_assign
id|offset
suffix:semicolon
id|backward
op_assign
id|ra-&gt;next_size
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|backward
OG
id|target
)paren
id|target
op_assign
l_int|0
suffix:semicolon
r_else
id|target
op_sub_assign
id|backward
suffix:semicolon
id|page_cache_readahead
c_func
(paren
id|mapping
comma
id|ra
comma
id|filp
comma
id|target
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * handle_ra_miss() is called when it is known that a page which should have&n; * been present in the pagecache (we just did some readahead there) was in fact&n; * not found.  This will happen if it was evicted by the VM (readahead&n; * thrashing) or if the readahead window is maximally shrunk.&n; *&n; * If the window has been maximally shrunk (next_size == 0) then bump it up&n; * again to resume readahead.&n; *&n; * Otherwise we&squot;re thrashing, so shrink the readahead window by three pages.&n; * This is because it is grown by two pages on a readahead hit.  Theory being&n; * that the readahead window size will stabilise around the maximum level at&n; * which there is no thrashing.&n; */
DECL|function|handle_ra_miss
r_void
id|handle_ra_miss
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file_ra_state
op_star
id|ra
)paren
(brace
r_const
r_int
r_int
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|ra
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;next_size
op_eq
op_minus
l_int|1UL
)paren
(brace
id|ra-&gt;next_size
op_assign
id|min
suffix:semicolon
)brace
r_else
(brace
id|ra-&gt;next_size
op_sub_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;next_size
OL
id|min
)paren
id|ra-&gt;next_size
op_assign
id|min
suffix:semicolon
)brace
)brace
eof
