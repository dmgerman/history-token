multiline_comment|/*&n; * mm/readahead.c - address_space-level file readahead.&n; *&n; * Copyright (C) 2002, Linus Torvalds&n; *&n; * 09Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
multiline_comment|/*&n; * The readahead logic manages two readahead windows.  The &quot;current&quot;&n; * and the &quot;ahead&quot; windows.&n; *&n; * VM_MAX_READAHEAD specifies, in kilobytes, the maximum size of&n; * each of the two windows.  So the amount of readahead which is&n; * in front of the file pointer varies between VM_MAX_READAHEAD and&n; * VM_MAX_READAHEAD * 2.&n; *&n; * VM_MAX_READAHEAD only applies if the underlying request queue&n; * has a zero value of ra_sectors.&n; */
multiline_comment|/*&n; * Return max readahead size for this inode in number-of-pages.&n; */
DECL|function|get_max_readahead
r_static
r_int
id|get_max_readahead
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|blk_ra_kbytes
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_bdev
)paren
(brace
id|blk_ra_kbytes
op_assign
id|blk_get_readahead
c_func
(paren
id|inode-&gt;i_sb-&gt;s_bdev
)paren
op_div
l_int|2
suffix:semicolon
)brace
r_return
id|blk_ra_kbytes
op_rshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|get_min_readahead
r_static
r_int
id|get_min_readahead
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|ret
op_assign
id|VM_MIN_READAHEAD
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|2
)paren
id|ret
op_assign
l_int|2
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Readahead design.&n; *&n; * The fields in struct file_ra_state represent the most-recently-executed&n; * readahead attempt:&n; *&n; * start:&t;Page index at which we started the readahead&n; * size:&t;Number of pages in that read&n; *              Together, these form the &quot;current window&quot;.&n; *              Together, start and size represent the `readahead window&squot;.&n; * next_size:   The number of pages to read on the next readahead miss.&n; * prev_page:   The page which the readahead algorithm most-recently inspected.&n; *              prev_page is mainly an optimisation: if page_cache_readahead&n; *&t;&t;sees that it is again being called for a page which it just&n; *&t;&t;looked at, it can return immediately without making any state&n; *&t;&t;changes.&n; * ahead_start,&n; * ahead_size:  Together, these form the &quot;ahead window&quot;.&n; *&n; * The readahead code manages two windows - the &quot;current&quot; and the &quot;ahead&quot;&n; * windows.  The intent is that while the application is walking the pages&n; * in the current window, I/O is underway on the ahead window.  When the&n; * current window is fully traversed, it is replaced by the ahead window&n; * and the ahead window is invalidated.  When this copying happens, the&n; * new current window&squot;s pages are probably still locked.  When I/O has&n; * completed, we submit a new batch of I/O, creating a new ahead window.&n; *&n; * So:&n; *&n; *   ----|----------------|----------------|-----&n; *       ^start           ^start+size&n; *                        ^ahead_start     ^ahead_start+ahead_size&n; *&n; *         ^ When this page is read, we submit I/O for the&n; *           ahead window.&n; *&n; * A `readahead hit&squot; occurs when a read request is made against a page which is&n; * inside the current window.  Hits are good, and the window size (next_size)&n; * is grown aggressively when hits occur.  Two pages are added to the next&n; * window size on each hit, which will end up doubling the next window size by&n; * the time I/O is submitted for it.&n; *&n; * If readahead hits are more sparse (say, the application is only reading&n; * every second page) then the window will build more slowly.&n; *&n; * On a readahead miss (the application seeked away) the readahead window is&n; * shrunk by 25%.  We don&squot;t want to drop it too aggressively, because it is a&n; * good assumption that an application which has built a good readahead window&n; * will continue to perform linear reads.  Either at the new file position, or&n; * at the old one after another seek.&n; *&n; * There is a special-case: if the first page which the application tries to&n; * read happens to be the first page of the file, it is assumed that a linear&n; * read is about to happen and the window is immediately set to half of the&n; * device maximum.&n; * &n; * A page request at (start + size) is not a miss at all - it&squot;s just a part of&n; * sequential file reading.&n; *&n; * This function is to be called for every page which is read, rather than when&n; * it is time to perform readahead.  This is so the readahead algorithm can&n; * centrally work out the access patterns.  This could be costly with many tiny&n; * read()s, so we specifically optimise for that case with prev_page.&n; */
multiline_comment|/*&n; * do_page_cache_readahead actually reads a chunk of disk.  It allocates all&n; * the pages first, then submits them all for I/O. This avoids the very bad&n; * behaviour which would occur if page allocations are causing VM writeback.&n; * We really don&squot;t want to intermingle reads and writes like that.&n; */
DECL|function|do_page_cache_readahead
r_void
id|do_page_cache_readahead
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|address_space
op_star
id|mapping
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping
suffix:semicolon
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
id|nr_to_really_read
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
r_return
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
id|read_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
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
id|read_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_continue
suffix:semicolon
id|page
op_assign
id|page_cache_alloc
c_func
(paren
id|mapping
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
id|nr_to_really_read
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now start the IO.  We ignore I/O errors - if the page is not&n;&t; * uptodate then the caller will launch readpage again, and&n;&t; * will then handle the error.&n;&t; */
r_for
c_loop
(paren
id|page_idx
op_assign
l_int|0
suffix:semicolon
id|page_idx
OL
id|nr_to_really_read
suffix:semicolon
id|page_idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|page_pool
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|page
op_assign
id|list_entry
c_func
(paren
id|page_pool.prev
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
id|add_to_page_cache_unique
c_func
(paren
id|page
comma
id|mapping
comma
id|page-&gt;index
)paren
)paren
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|readpage
c_func
(paren
id|file
comma
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
multiline_comment|/*&n;&t; * Do this now, rather than at the next wait_on_page().&n;&t; */
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|page_pool
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * page_cache_readahead is the main function.  If performs the adaptive&n; * readahead window size management and submits the readahead I/O.&n; */
DECL|function|page_cache_readahead
r_void
id|page_cache_readahead
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping-&gt;host
suffix:semicolon
r_struct
id|file_ra_state
op_star
id|ra
op_assign
op_amp
id|file-&gt;f_ra
suffix:semicolon
r_int
r_int
id|max
suffix:semicolon
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/*&n;&t; * Here we detect the case where the application is performing&n;&t; * sub-page sized reads.  We avoid doing extra work and bogusly&n;&t; * perturbing the readahead window expansion logic.&n;&t; * If next_size is zero, this is the very first read for this&n;&t; * file handle.&n;&t; */
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
id|max
op_assign
id|get_max_readahead
c_func
(paren
id|inode
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
id|inode
)paren
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
id|do_page_cache_readahead
c_func
(paren
id|file
comma
id|offset
comma
id|ra-&gt;size
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * This read request is within the current window.  It&n;&t;&t; * is time to submit I/O for the ahead window while&n;&t;&t; * the application is crunching through the current&n;&t;&t; * window.&n;&t;&t; */
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
id|do_page_cache_readahead
c_func
(paren
id|file
comma
id|ra-&gt;ahead_start
comma
id|ra-&gt;ahead_size
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
id|file
op_star
id|file
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
id|target
suffix:semicolon
r_int
r_int
id|backward
suffix:semicolon
r_const
r_int
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_mapping-&gt;host
)paren
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_ra.next_size
OL
id|min
)paren
id|file-&gt;f_ra.next_size
op_assign
id|min
suffix:semicolon
id|target
op_assign
id|offset
suffix:semicolon
id|backward
op_assign
id|file-&gt;f_ra.next_size
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
id|file
comma
id|target
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * handle_ra_thrashing() is called when it is known that a page which should&n; * have been present (it&squot;s inside the readahead window) was in fact evicted by&n; * the VM.&n; *&n; * We shrink the readahead window by three pages.  This is because we grow it&n; * by two pages on a readahead hit.  Theory being that the readahead window&n; * size will stabilise around the maximum level at which there isn&squot;t any&n; * thrashing.&n; */
DECL|function|handle_ra_thrashing
r_void
id|handle_ra_thrashing
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
r_int
r_int
id|min
op_assign
id|get_min_readahead
c_func
(paren
id|inode
)paren
suffix:semicolon
id|file-&gt;f_ra.next_size
op_sub_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_ra.next_size
OL
id|min
)paren
id|file-&gt;f_ra.next_size
op_assign
id|min
suffix:semicolon
)brace
eof
