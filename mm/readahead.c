multiline_comment|/*&n; * mm/readahead.c - address_space-level file readahead.&n; *&n; * Copyright (C) 2002, Linus Torvalds&n; *&n; * 09Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
DECL|function|default_unplug_io_fn
r_void
id|default_unplug_io_fn
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
comma
r_struct
id|page
op_star
id|page
)paren
(brace
)brace
DECL|variable|default_unplug_io_fn
id|EXPORT_SYMBOL
c_func
(paren
id|default_unplug_io_fn
)paren
suffix:semicolon
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
dot
id|unplug_io_fn
op_assign
id|default_unplug_io_fn
comma
)brace
suffix:semicolon
DECL|variable|default_backing_dev_info
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|default_backing_dev_info
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialise a struct file&squot;s readahead state.  Assumes that the caller has&n; * memset *ra to zero.&n; */
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
DECL|function|ra_off
r_static
r_inline
r_void
id|ra_off
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
)paren
(brace
id|ra-&gt;start
op_assign
l_int|0
suffix:semicolon
id|ra-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ra-&gt;size
op_assign
op_minus
l_int|1
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
l_int|0
suffix:semicolon
id|ra-&gt;ahead_size
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the initial window size, round to next power of 2 and square&n; * for small size, x 4 for medium, and x 2 for large&n; * for 128k (32 page) max ra&n; * 1-8 page = 32k initial, &gt; 8 page = 128k initial&n; */
DECL|function|get_init_ra_size
r_static
r_int
r_int
id|get_init_ra_size
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|max
)paren
(brace
r_int
r_int
id|newsize
op_assign
id|roundup_pow_of_two
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newsize
op_le
id|max
op_div
l_int|64
)paren
id|newsize
op_assign
id|newsize
op_star
id|newsize
suffix:semicolon
r_else
r_if
c_cond
(paren
id|newsize
op_le
id|max
op_div
l_int|4
)paren
id|newsize
op_assign
id|max
op_div
l_int|4
suffix:semicolon
r_else
id|newsize
op_assign
id|max
suffix:semicolon
r_return
id|newsize
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the new window size, this is called only when I/O is to be submitted,&n; * not for each call to readahead.  If a cache miss occured, reduce next I/O&n; * size, else increase depending on how close to max we are.&n; */
DECL|function|get_next_ra_size
r_static
r_int
r_int
id|get_next_ra_size
c_func
(paren
r_int
r_int
id|cur
comma
r_int
r_int
id|max
comma
r_int
r_int
id|min
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|newsize
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
id|RA_FLAG_MISS
)paren
(brace
id|newsize
op_assign
id|max
c_func
(paren
(paren
id|cur
op_minus
l_int|2
)paren
comma
id|min
)paren
suffix:semicolon
op_star
id|flags
op_and_assign
op_complement
id|RA_FLAG_MISS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cur
OL
id|max
op_div
l_int|16
)paren
(brace
id|newsize
op_assign
l_int|4
op_star
id|cur
suffix:semicolon
)brace
r_else
(brace
id|newsize
op_assign
l_int|2
op_star
id|cur
suffix:semicolon
)brace
r_return
id|min
c_func
(paren
id|newsize
comma
id|max
)paren
suffix:semicolon
)brace
DECL|macro|list_to_page
mdefine_line|#define list_to_page(head) (list_entry((head)-&gt;prev, struct page, lru))
multiline_comment|/**&n; * read_cache_pages - populate an address space with some pages, and&n; * &t;&t;&t;start reads against them.&n; * @mapping: the address_space&n; * @pages: The address of a list_head which contains the target pages.  These&n; *   pages have their -&gt;index populated and are otherwise uninitialised.&n; * @filler: callback routine for filling a single page.&n; * @data: private data for the callback routine.&n; *&n; * Hides the details of the LRU cache etc from the filesystems.&n; */
DECL|function|read_cache_pages
r_int
id|read_cache_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|list_head
op_star
id|pages
comma
r_int
(paren
op_star
id|filler
)paren
(paren
r_void
op_star
comma
r_struct
id|page
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|pagevec
id|lru_pvec
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|pages
)paren
)paren
(brace
id|page
op_assign
id|list_to_page
c_func
(paren
id|pages
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
id|add_to_page_cache
c_func
(paren
id|page
comma
id|mapping
comma
id|page-&gt;index
comma
id|GFP_KERNEL
)paren
)paren
(brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ret
op_assign
id|filler
c_func
(paren
id|data
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
r_if
c_cond
(paren
id|ret
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|pages
)paren
)paren
(brace
r_struct
id|page
op_star
id|victim
suffix:semicolon
id|victim
op_assign
id|list_to_page
c_func
(paren
id|pages
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|victim-&gt;lru
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|victim
)paren
suffix:semicolon
)brace
r_break
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
id|ret
suffix:semicolon
)brace
DECL|variable|read_cache_pages
id|EXPORT_SYMBOL
c_func
(paren
id|read_cache_pages
)paren
suffix:semicolon
DECL|function|read_pages
r_static
r_int
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mapping-&gt;a_ops-&gt;readpages
)paren
(brace
id|ret
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|readpages
c_func
(paren
id|filp
comma
id|mapping
comma
id|pages
comma
id|nr_pages
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|pagevec_init
c_func
(paren
op_amp
id|lru_pvec
comma
l_int|0
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
id|list_to_page
c_func
(paren
id|pages
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
id|add_to_page_cache
c_func
(paren
id|page
comma
id|mapping
comma
id|page-&gt;index
comma
id|GFP_KERNEL
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
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Readahead design.&n; *&n; * The fields in struct file_ra_state represent the most-recently-executed&n; * readahead attempt:&n; *&n; * start:&t;Page index at which we started the readahead&n; * size:&t;Number of pages in that read&n; *              Together, these form the &quot;current window&quot;.&n; *              Together, start and size represent the `readahead window&squot;.&n; * next_size:   The number of pages to read on the next readahead miss.&n; *              Has the magical value -1UL if readahead has been disabled.&n; * prev_page:   The page which the readahead algorithm most-recently inspected.&n; *              prev_page is mainly an optimisation: if page_cache_readahead&n; *&t;&t;sees that it is again being called for a page which it just&n; *&t;&t;looked at, it can return immediately without making any state&n; *&t;&t;changes.&n; * ahead_start,&n; * ahead_size:  Together, these form the &quot;ahead window&quot;.&n; * ra_pages:&t;The externally controlled max readahead for this fd.&n; *&n; * When readahead is in the off state (size == -1UL), readahead is disabled.&n; * In this state, prev_page is used to detect the resumption of sequential I/O.&n; *&n; * The readahead code manages two windows - the &quot;current&quot; and the &quot;ahead&quot;&n; * windows.  The intent is that while the application is walking the pages&n; * in the current window, I/O is underway on the ahead window.  When the&n; * current window is fully traversed, it is replaced by the ahead window&n; * and the ahead window is invalidated.  When this copying happens, the&n; * new current window&squot;s pages are probably still locked.  So&n; * we submit a new batch of I/O immediately, creating a new ahead window.&n; *&n; * So:&n; *&n; *   ----|----------------|----------------|-----&n; *       ^start           ^start+size&n; *                        ^ahead_start     ^ahead_start+ahead_size&n; *&n; *         ^ When this page is read, we submit I/O for the&n; *           ahead window.&n; *&n; * A `readahead hit&squot; occurs when a read request is made against a page which is&n; * the next sequential page. Ahead windowe calculations are done only when it&n; * is time to submit a new IO.  The code ramps up the size agressively at first,&n; * but slow down as it approaches max_readhead.&n; *&n; * Any seek/ramdom IO will result in readahead being turned off.  It will resume&n; * at the first sequential access.&n; *&n; * There is a special-case: if the first page which the application tries to&n; * read happens to be the first page of the file, it is assumed that a linear&n; * read is about to happen and the window is immediately set to the initial size&n; * based on I/O request size and the max_readahead.&n; * &n; * A page request at (start + size) is not a miss at all - it&squot;s just a part of&n; * sequential file reading.&n; *&n; * This function is to be called for every read request, rather than when&n; * it is time to perform readahead.  It is called only oce for the entire I/O&n; * regardless of size unless readahead is unable to start enough I/O to satisfy&n; * the request (I/O request &gt; max_readahead).&n; */
multiline_comment|/*&n; * do_page_cache_readahead actually reads a chunk of disk.  It allocates all&n; * the pages first, then submits them all for I/O. This avoids the very bad&n; * behaviour which would occur if page allocations are causing VM writeback.&n; * We really don&squot;t want to intermingle reads and writes like that.&n; *&n; * Returns the number of pages requested, or the maximum amount of I/O allowed.&n; */
r_static
r_inline
r_int
DECL|function|__do_page_cache_readahead
id|__do_page_cache_readahead
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
id|loff_t
id|isize
op_assign
id|i_size_read
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isize
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
id|isize
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Preallocate as many pages as we will need.&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|mapping-&gt;tree_lock
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
id|spin_unlock_irq
c_func
(paren
op_amp
id|mapping-&gt;tree_lock
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
id|spin_lock_irq
c_func
(paren
op_amp
id|mapping-&gt;tree_lock
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
id|page-&gt;lru
comma
op_amp
id|page_pool
)paren
suffix:semicolon
id|ret
op_increment
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|mapping-&gt;tree_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now start the IO.  We ignore I/O errors - if the page is not&n;&t; * uptodate then the caller will launch readpage again, and&n;&t; * will then handle the error.&n;&t; */
r_if
c_cond
(paren
id|ret
)paren
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
multiline_comment|/*&n; * Chunk the readahead into 2 megabyte units, so that we don&squot;t pin too much&n; * memory at once.&n; */
DECL|function|force_page_cache_readahead
r_int
id|force_page_cache_readahead
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|mapping-&gt;a_ops-&gt;readpage
op_logical_and
op_logical_neg
id|mapping-&gt;a_ops-&gt;readpages
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
id|nr_to_read
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|this_chunk
op_assign
(paren
l_int|2
op_star
l_int|1024
op_star
l_int|1024
)paren
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|this_chunk
OG
id|nr_to_read
)paren
id|this_chunk
op_assign
id|nr_to_read
suffix:semicolon
id|err
op_assign
id|__do_page_cache_readahead
c_func
(paren
id|mapping
comma
id|filp
comma
id|offset
comma
id|this_chunk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|err
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_add_assign
id|err
suffix:semicolon
id|offset
op_add_assign
id|this_chunk
suffix:semicolon
id|nr_to_read
op_sub_assign
id|this_chunk
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Check how effective readahead is being.  If the amount of started IO is&n; * less than expected then the file is partly or fully in pagecache and&n; * readahead isn&squot;t helping.&n; *&n; */
DECL|function|check_ra_success
r_int
id|check_ra_success
c_func
(paren
r_struct
id|file_ra_state
op_star
id|ra
comma
r_int
r_int
id|nr_to_read
comma
r_int
r_int
id|actual
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
id|ra-&gt;cache_hit
op_add_assign
id|nr_to_read
suffix:semicolon
r_if
c_cond
(paren
id|ra-&gt;cache_hit
op_ge
id|VM_MAX_CACHE_HIT
)paren
(brace
id|ra_off
c_func
(paren
id|ra
)paren
suffix:semicolon
id|ra-&gt;flags
op_or_assign
id|RA_FLAG_INCACHE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|ra-&gt;cache_hit
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Issue the I/O. If pages already in cache, increment the hit count until&n; * we exceed max, then turn RA off until we start missing again.&n; */
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
r_return
id|__do_page_cache_readahead
c_func
(paren
id|mapping
comma
id|filp
comma
id|offset
comma
id|nr_to_read
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * page_cache_readahead is the main function.  If performs the adaptive&n; * readahead window size management and submits the readahead I/O.&n; */
r_int
r_int
DECL|function|page_cache_readahead
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
comma
r_int
r_int
id|req_size
)paren
(brace
r_int
r_int
id|max
comma
id|min
suffix:semicolon
r_int
r_int
id|newsize
op_assign
id|req_size
suffix:semicolon
r_int
r_int
id|actual
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Here we detect the case where the application is performing&n;&t; * sub-page sized reads.  We avoid doing extra work and bogusly&n;&t; * perturbing the readahead window expansion logic.&n;&t; * If size is zero, there is no read ahead window so we need one&n;&t; */
r_if
c_cond
(paren
id|offset
op_eq
id|ra-&gt;prev_page
op_logical_and
id|req_size
op_eq
l_int|1
op_logical_and
id|ra-&gt;size
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|max
op_assign
id|get_max_readahead
c_func
(paren
id|ra
)paren
suffix:semicolon
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|ra
)paren
suffix:semicolon
singleline_comment|//&t;maxsane = max_sane_readahead(max);
id|newsize
op_assign
id|min
c_func
(paren
id|req_size
comma
id|max
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newsize
op_eq
l_int|0
op_logical_or
(paren
id|ra-&gt;flags
op_amp
id|RA_FLAG_INCACHE
)paren
)paren
(brace
id|newsize
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
multiline_comment|/* No readahead or file already in cache */
)brace
multiline_comment|/*&n;&t; * Special case - first read.  We&squot;ll assume it&squot;s a whole-file read if&n;&t; * at start of file, and grow the window fast.  Or detect first&n;&t; * sequential access&n;&t; */
r_if
c_cond
(paren
(paren
id|ra-&gt;size
op_eq
l_int|0
op_logical_and
id|offset
op_eq
l_int|0
)paren
multiline_comment|/* first io and start of file */
op_logical_or
(paren
id|ra-&gt;size
op_eq
op_minus
l_int|1
op_logical_and
id|ra-&gt;prev_page
op_eq
id|offset
op_minus
l_int|1
)paren
)paren
(brace
multiline_comment|/* First sequential */
id|ra-&gt;prev_page
op_assign
id|offset
op_plus
id|newsize
op_minus
l_int|1
suffix:semicolon
id|ra-&gt;size
op_assign
id|get_init_ra_size
c_func
(paren
id|newsize
comma
id|max
)paren
suffix:semicolon
id|ra-&gt;start
op_assign
id|offset
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
r_if
c_cond
(paren
op_logical_neg
id|check_ra_success
c_func
(paren
id|ra
comma
id|ra-&gt;size
comma
id|actual
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the request size is larger than our max readahead, we&n;&t;&t; * at least want to be sure that we get 2 IOs in flight and&n;&t;&t; * we know that we will definitly need the new I/O.&n;&t;&t; * once we do this, subsequent calls should be able to overlap&n;&t;&t; * IOs,* thus preventing stalls. so issue the ahead window&n;&t;&t; * immediately.&n;&t;&t; */
r_if
c_cond
(paren
id|req_size
op_ge
id|max
)paren
(brace
id|ra-&gt;ahead_size
op_assign
id|get_next_ra_size
c_func
(paren
id|ra-&gt;size
comma
id|max
comma
id|min
comma
op_amp
id|ra-&gt;flags
)paren
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
id|ra-&gt;start
op_plus
id|ra-&gt;size
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
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now handle the random case:&n;&t; * partial page reads and first access were handled above,&n;&t; * so this must be the next page otherwise it is random&n;&t; */
r_if
c_cond
(paren
(paren
id|offset
op_ne
(paren
id|ra-&gt;prev_page
op_plus
l_int|1
)paren
op_logical_or
(paren
id|ra-&gt;size
op_eq
l_int|0
)paren
)paren
)paren
(brace
id|ra_off
c_func
(paren
id|ra
)paren
suffix:semicolon
id|ra-&gt;prev_page
op_assign
id|offset
op_plus
id|newsize
op_minus
l_int|1
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
id|newsize
)paren
suffix:semicolon
id|check_ra_success
c_func
(paren
id|ra
comma
id|newsize
comma
id|actual
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we get here we are doing sequential IO and this was not the first&n;&t; * occurence (ie we have an existing window)&n;&t; */
r_if
c_cond
(paren
id|ra-&gt;ahead_start
op_eq
l_int|0
)paren
(brace
multiline_comment|/* no ahead window yet */
id|ra-&gt;ahead_size
op_assign
id|get_next_ra_size
c_func
(paren
id|max
c_func
(paren
id|newsize
comma
id|ra-&gt;size
)paren
comma
id|max
comma
id|min
comma
op_amp
id|ra-&gt;flags
)paren
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
id|ra-&gt;start
op_plus
id|ra-&gt;size
suffix:semicolon
id|newsize
op_assign
id|min
(paren
id|newsize
comma
id|ra-&gt;ahead_start
op_minus
id|offset
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|check_ra_success
c_func
(paren
id|ra
comma
id|ra-&gt;ahead_size
comma
id|actual
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Already have an ahead window, check if we crossed into it if so,&n;&t; * shift windows and issue a new ahead window.&n;&t; * Only return the #pages that are in the current window, so that we&n;&t; * get called back on the first page of the ahead window which will&n;&t; * allow us to submit more IO.&n;&t; */
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|newsize
op_minus
l_int|1
)paren
op_ge
id|ra-&gt;ahead_start
)paren
(brace
id|ra-&gt;start
op_assign
id|ra-&gt;ahead_start
suffix:semicolon
id|ra-&gt;size
op_assign
id|ra-&gt;ahead_size
suffix:semicolon
id|ra-&gt;ahead_start
op_assign
id|ra-&gt;ahead_start
op_plus
id|ra-&gt;ahead_size
suffix:semicolon
id|ra-&gt;ahead_size
op_assign
id|get_next_ra_size
c_func
(paren
id|ra-&gt;ahead_size
comma
id|max
comma
id|min
comma
op_amp
id|ra-&gt;flags
)paren
suffix:semicolon
id|newsize
op_assign
id|min
(paren
id|newsize
comma
id|ra-&gt;ahead_start
op_minus
id|offset
)paren
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
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|ra-&gt;prev_page
op_assign
id|offset
op_plus
id|newsize
op_minus
l_int|1
suffix:semicolon
r_return
id|newsize
suffix:semicolon
)brace
multiline_comment|/*&n; * handle_ra_miss() is called when it is known that a page which should have&n; * been present in the pagecache (we just did some readahead there) was in fact&n; * not found.  This will happen if it was evicted by the VM (readahead&n; * thrashing)&n; *&n; * Turn on the cache miss flag in the RA struct, this will cause the RA code&n; * to reduce the RA size on the next read.&n; */
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
comma
id|pgoff_t
id|offset
)paren
(brace
id|ra-&gt;flags
op_or_assign
id|RA_FLAG_MISS
suffix:semicolon
id|ra-&gt;flags
op_and_assign
op_complement
id|RA_FLAG_INCACHE
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a desired number of PAGE_CACHE_SIZE readahead pages, return a&n; * sensible upper limit.&n; */
DECL|function|max_sane_readahead
r_int
r_int
id|max_sane_readahead
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|active
suffix:semicolon
r_int
r_int
id|inactive
suffix:semicolon
r_int
r_int
id|free
suffix:semicolon
id|__get_zone_counts
c_func
(paren
op_amp
id|active
comma
op_amp
id|inactive
comma
op_amp
id|free
comma
id|NODE_DATA
c_func
(paren
id|numa_node_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_return
id|min
c_func
(paren
id|nr
comma
(paren
id|inactive
op_plus
id|free
)paren
op_div
l_int|2
)paren
suffix:semicolon
)brace
eof
