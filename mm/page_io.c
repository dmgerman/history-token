multiline_comment|/*&n; *  linux/mm/page_io.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, &n; *  Asynchronous swapping added 30.12.95. Stephen Tweedie&n; *  Removed race in async swapping. 14.4.1996. Bruno Haible&n; *  Add swap of shared pages through the page cache. 20.2.1998. Stephen Tweedie&n; *  Always use brw_page, life becomes simpler. 12 May 1998 Eric Biederman&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;/* for block_sync_page() */
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_static
r_struct
id|bio
op_star
DECL|function|get_swap_bio
id|get_swap_bio
c_func
(paren
r_int
id|gfp_flags
comma
r_struct
id|page
op_star
id|page
comma
id|bio_end_io_t
id|end_io
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|gfp_flags
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|sis
suffix:semicolon
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
id|entry.val
op_assign
id|page-&gt;index
suffix:semicolon
id|sis
op_assign
id|get_swap_info_struct
c_func
(paren
id|swp_type
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|map_swap_page
c_func
(paren
id|sis
comma
id|swp_offset
c_func
(paren
id|entry
)paren
)paren
op_star
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|sis-&gt;bdev
suffix:semicolon
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_page
op_assign
id|page
suffix:semicolon
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_offset
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_vcnt
op_assign
l_int|1
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|bio-&gt;bi_end_io
op_assign
id|end_io
suffix:semicolon
)brace
r_return
id|bio
suffix:semicolon
)brace
DECL|function|end_swap_bio_write
r_static
r_int
id|end_swap_bio_write
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|bytes_done
comma
r_int
id|err
)paren
(brace
r_const
r_int
id|uptodate
op_assign
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_page
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|end_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|end_swap_bio_read
r_static
r_int
id|end_swap_bio_read
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|bytes_done
comma
r_int
id|err
)paren
(brace
r_const
r_int
id|uptodate
op_assign
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|bio-&gt;bi_io_vec
(braket
l_int|0
)braket
dot
id|bv_page
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
(brace
id|SetPageError
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
)brace
r_else
(brace
id|SetPageUptodate
c_func
(paren
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
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We may have stale swap cache pages in memory: notice&n; * them here and get rid of the unnecessary final write.&n; */
DECL|function|swap_writepage
r_int
id|swap_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
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
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bio
op_assign
id|get_swap_bio
c_func
(paren
id|GFP_NOIO
comma
id|page
comma
id|end_swap_bio_write
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
(brace
id|set_page_dirty
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
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|inc_page_state
c_func
(paren
id|pswpout
)paren
suffix:semicolon
id|SetPageWriteback
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
id|submit_bio
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|swap_readpage
r_int
id|swap_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|bio
op_assign
id|get_swap_bio
c_func
(paren
id|GFP_KERNEL
comma
id|page
comma
id|end_swap_bio_read
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|inc_page_state
c_func
(paren
id|pswpin
)paren
suffix:semicolon
id|submit_bio
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|swap_aops
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
id|readpage
op_assign
id|swap_readpage
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
macro_line|#if defined(CONFIG_SOFTWARE_SUSPEND) || defined(CONFIG_PM_DISK)
multiline_comment|/*&n; * A scruffy utility function to read or write an arbitrary swap page&n; * and wait on the I/O.  The caller must have a ref on the page.&n; */
DECL|function|rw_swap_page_sync
r_int
id|rw_swap_page_sync
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
id|ret
suffix:semicolon
r_struct
id|writeback_control
id|swap_wbc
op_assign
(brace
dot
id|sync_mode
op_assign
id|WB_SYNC_ALL
comma
)brace
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|page-&gt;mapping
)paren
suffix:semicolon
id|ret
op_assign
id|add_to_page_cache
c_func
(paren
id|page
comma
op_amp
id|swapper_space
comma
id|entry.val
comma
id|GFP_NOIO
op_or
id|__GFP_NOFAIL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * get one more reference to make page non-exclusive so&n;&t; * remove_exclusive_swap_page won&squot;t mess with it.&n;&t; */
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
(brace
id|ret
op_assign
id|swap_readpage
c_func
(paren
l_int|NULL
comma
id|page
)paren
suffix:semicolon
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|swap_writepage
c_func
(paren
id|page
comma
op_amp
id|swap_wbc
)paren
suffix:semicolon
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|lock_page
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
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* For add_to_page_cache() */
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
op_logical_or
id|PageError
c_func
(paren
id|page
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
