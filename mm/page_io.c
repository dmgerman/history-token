multiline_comment|/*&n; *  linux/mm/page_io.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, &n; *  Asynchronous swapping added 30.12.95. Stephen Tweedie&n; *  Removed race in async swapping. 14.4.1996. Bruno Haible&n; *  Add swap of shared pages through the page cache. 20.2.1998. Stephen Tweedie&n; *  Always use brw_page, life becomes simpler. 12 May 1998 Eric Biederman&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * Reads or writes a swap page.&n; * wait=1: start I/O and wait for completion. wait=0: start asynchronous I/O.&n; *&n; * Important prevention of race condition: the caller *must* atomically &n; * create a unique swap cache entry for this swap page before calling&n; * rw_swap_page, and must lock that page.  By ensuring that there is a&n; * single page of memory reserved for the swap entry, the normal VM page&n; * lock on that page also doubles as a lock on swap entries.  Having only&n; * one lock to deal with per swap entry (rather than locking swap and memory&n; * independently) also makes it easier to make certain swapping operations&n; * atomic, which is particularly important when we are trying to ensure &n; * that shared pages stay shared while being swapped.&n; */
DECL|function|rw_swap_page_base
r_static
r_int
id|rw_swap_page_base
c_func
(paren
r_int
id|rw
comma
id|swp_entry_t
id|entry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|sector_t
id|zones
(braket
id|PAGE_SIZE
op_div
l_int|512
)braket
suffix:semicolon
r_int
id|zones_used
suffix:semicolon
r_int
id|block_size
suffix:semicolon
r_struct
id|inode
op_star
id|swapf
op_assign
l_int|0
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
(brace
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kstat.pswpin
op_increment
suffix:semicolon
)brace
r_else
id|kstat.pswpout
op_increment
suffix:semicolon
id|get_swaphandle_info
c_func
(paren
id|entry
comma
op_amp
id|offset
comma
op_amp
id|swapf
)paren
suffix:semicolon
id|bdev
op_assign
id|swapf-&gt;i_bdev
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
(brace
id|zones
(braket
l_int|0
)braket
op_assign
id|offset
suffix:semicolon
id|zones_used
op_assign
l_int|1
suffix:semicolon
id|block_size
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|block
op_assign
id|offset
op_lshift
(paren
id|PAGE_SHIFT
op_minus
id|swapf-&gt;i_sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|block_size
op_assign
id|swapf-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|PAGE_SIZE
suffix:semicolon
id|i
op_increment
comma
id|j
op_add_assign
id|block_size
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|zones
(braket
id|i
)braket
op_assign
id|bmap
c_func
(paren
id|swapf
comma
id|block
op_increment
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rw_swap_page: bad swap file&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|zones_used
op_assign
id|i
suffix:semicolon
id|bdev
op_assign
id|swapf-&gt;i_sb-&gt;s_bdev
suffix:semicolon
)brace
multiline_comment|/* block_size == PAGE_SIZE/zones_used */
id|brw_page
c_func
(paren
id|rw
comma
id|page
comma
id|bdev
comma
id|zones
comma
id|block_size
)paren
suffix:semicolon
multiline_comment|/* Note! For consistency we do all of the logic,&n; &t; * decrementing the page count, and unlocking the page in the&n; &t; * swap lock map - in the IO completion handler.&n; &t; */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * A simple wrapper so the base function doesn&squot;t need to enforce&n; * that all swap pages go through the swap cache! We verify that:&n; *  - the page is locked&n; *  - it&squot;s marked as being swap-cache&n; *  - it&squot;s associated with the swap inode&n; */
DECL|function|rw_swap_page
r_void
id|rw_swap_page
c_func
(paren
r_int
id|rw
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|swp_entry_t
id|entry
suffix:semicolon
id|entry.val
op_assign
id|page-&gt;index
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
id|PAGE_BUG
c_func
(paren
id|page
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
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rw_swap_page_base
c_func
(paren
id|rw
comma
id|entry
comma
id|page
)paren
)paren
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The swap lock map insists that pages be in the page cache!&n; * Therefore we can&squot;t use it.  Later when we can remove the need for the&n; * lock map and we can reduce the number of functions exported.&n; */
DECL|function|rw_swap_page_nolock
r_void
id|rw_swap_page_nolock
c_func
(paren
r_int
id|rw
comma
id|swp_entry_t
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|buf
)paren
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
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* needs sync_page to wait I/O completation */
id|page-&gt;mapping
op_assign
op_amp
id|swapper_space
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rw_swap_page_base
c_func
(paren
id|rw
comma
id|entry
comma
id|page
)paren
)paren
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
id|page-&gt;mapping
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
