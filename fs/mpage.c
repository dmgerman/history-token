multiline_comment|/*&n; * fs/mpage.c&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * Contains functions related to preparing and submitting BIOs which contain&n; * multiple pagecache pages.&n; *&n; * 15May2002&t;akpm@zip.com.au&n; *&t;&t;Initial version&n; * 27Jun2002&t;axboe@suse.de&n; *&t;&t;use bio_add_page() to build bio&squot;s just the right size&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/prefetch.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/pagevec.h&gt;
multiline_comment|/*&n; * I/O completion handler for multipage BIOs.&n; *&n; * The mpage code never puts partial pages into a BIO (except for end-of-file).&n; * If a page does not map to a contiguous run of blocks then it simply falls&n; * back to block_read_full_page().&n; *&n; * Why is this?  If a page&squot;s completion depends on a number of different BIOs&n; * which can complete in any order (or at the same time) then determining the&n; * status of that page is hard.  See end_buffer_async_read() for the details.&n; * There is no point in duplicating all that complexity.&n; */
DECL|function|mpage_end_io_read
r_static
r_int
id|mpage_end_io_read
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
id|bio_vec
op_star
id|bvec
op_assign
id|bio-&gt;bi_io_vec
op_plus
id|bio-&gt;bi_vcnt
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
r_do
(brace
r_struct
id|page
op_star
id|page
op_assign
id|bvec-&gt;bv_page
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|bvec
op_ge
id|bio-&gt;bi_io_vec
)paren
id|prefetchw
c_func
(paren
op_amp
id|bvec-&gt;bv_page-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uptodate
)paren
(brace
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageError
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
)brace
r_while
c_loop
(paren
id|bvec
op_ge
id|bio-&gt;bi_io_vec
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
DECL|function|mpage_end_io_write
r_static
r_int
id|mpage_end_io_write
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
id|bio_vec
op_star
id|bvec
op_assign
id|bio-&gt;bi_io_vec
op_plus
id|bio-&gt;bi_vcnt
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
r_do
(brace
r_struct
id|page
op_star
id|page
op_assign
id|bvec-&gt;bv_page
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|bvec
op_ge
id|bio-&gt;bi_io_vec
)paren
id|prefetchw
c_func
(paren
op_amp
id|bvec-&gt;bv_page-&gt;flags
)paren
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
)brace
r_while
c_loop
(paren
id|bvec
op_ge
id|bio-&gt;bi_io_vec
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
DECL|function|mpage_bio_submit
r_struct
id|bio
op_star
id|mpage_bio_submit
c_func
(paren
r_int
id|rw
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|bio-&gt;bi_end_io
op_assign
id|mpage_end_io_read
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
id|bio-&gt;bi_end_io
op_assign
id|mpage_end_io_write
suffix:semicolon
id|submit_bio
c_func
(paren
id|rw
comma
id|bio
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_struct
id|bio
op_star
DECL|function|mpage_alloc
id|mpage_alloc
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|first_sector
comma
r_int
id|nr_vecs
comma
r_int
id|gfp_flags
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
id|nr_vecs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
op_logical_and
(paren
id|current-&gt;flags
op_amp
id|PF_MEMALLOC
)paren
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|bio
op_logical_and
(paren
id|nr_vecs
op_div_assign
l_int|2
)paren
)paren
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|gfp_flags
comma
id|nr_vecs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bio
)paren
(brace
id|bio-&gt;bi_bdev
op_assign
id|bdev
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|first_sector
suffix:semicolon
)brace
r_return
id|bio
suffix:semicolon
)brace
multiline_comment|/*&n; * support function for mpage_readpages.  The fs supplied get_block might&n; * return an up to date buffer.  This is used to map that buffer into&n; * the page, which allows readpage to avoid triggering a duplicate call&n; * to get_block.&n; *&n; * The idea is to avoid adding buffers to pages that don&squot;t already have&n; * them.  So when the buffer is up to date and the page size == block size,&n; * this marks the page up to date instead of adding new buffers.&n; */
r_static
r_void
DECL|function|map_buffer_to_page
id|map_buffer_to_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|page_block
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|buffer_head
op_star
id|page_bh
comma
op_star
id|head
suffix:semicolon
r_int
id|block
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_has_buffers
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * don&squot;t make any buffers if there is only one buffer on&n;&t;&t; * the page and the page just needs to be set up to date&n;&t;&t; */
r_if
c_cond
(paren
id|inode-&gt;i_blkbits
op_eq
id|PAGE_CACHE_SHIFT
op_logical_and
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|create_empty_buffers
c_func
(paren
id|page
comma
l_int|1
op_lshift
id|inode-&gt;i_blkbits
comma
l_int|0
)paren
suffix:semicolon
)brace
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_bh
op_assign
id|head
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|block
op_eq
id|page_block
)paren
(brace
id|page_bh-&gt;b_state
op_assign
id|bh-&gt;b_state
suffix:semicolon
id|page_bh-&gt;b_bdev
op_assign
id|bh-&gt;b_bdev
suffix:semicolon
id|page_bh-&gt;b_blocknr
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
r_break
suffix:semicolon
)brace
id|page_bh
op_assign
id|page_bh-&gt;b_this_page
suffix:semicolon
id|block
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|page_bh
op_ne
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * mpage_readpages - populate an address space with some pages, and&n; *                       start reads against them.&n; *&n; * @mapping: the address_space&n; * @pages: The address of a list_head which contains the target pages.  These&n; *   pages have their -&gt;index populated and are otherwise uninitialised.&n; *&n; *   The page at @pages-&gt;prev has the lowest file offset, and reads should be&n; *   issued in @pages-&gt;prev to @pages-&gt;next order.&n; *&n; * @nr_pages: The number of pages at *@pages&n; * @get_block: The filesystem&squot;s block mapper function.&n; *&n; * This function walks the pages and the blocks within each page, building and&n; * emitting large BIOs.&n; *&n; * If anything unusual happens, such as:&n; *&n; * - encountering a page which has buffers&n; * - encountering a page which has a non-hole after a hole&n; * - encountering a page with non-contiguous blocks&n; *&n; * then this code just gives up and calls the buffer_head-based read function.&n; * It does handle a page which has holes at the end - that is a common case:&n; * the end-of-file on blocksize &lt; PAGE_CACHE_SIZE setups.&n; *&n; * BH_Boundary explanation:&n; *&n; * There is a problem.  The mpage read code assembles several pages, gets all&n; * their disk mappings, and then submits them all.  That&squot;s fine, but obtaining&n; * the disk mappings may require I/O.  Reads of indirect blocks, for example.&n; *&n; * So an mpage read of the first 16 blocks of an ext2 file will cause I/O to be&n; * submitted in the following order:&n; * &t;12 0 1 2 3 4 5 6 7 8 9 10 11 13 14 15 16&n; * because the indirect block has to be read to get the mappings of blocks&n; * 13,14,15,16.  Obviously, this impacts performance.&n; * &n; * So what we do it to allow the filesystem&squot;s get_block() function to set&n; * BH_Boundary when it maps block 11.  BH_Boundary says: mapping of the block&n; * after this one will require I/O against a block which is probably close to&n; * this one.  So you should push what I/O you have currently accumulated.&n; *&n; * This all causes the disk requests to be issued in the correct order.&n; */
r_static
r_struct
id|bio
op_star
DECL|function|do_mpage_readpage
id|do_mpage_readpage
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|nr_pages
comma
id|sector_t
op_star
id|last_block_in_bio
comma
id|get_block_t
id|get_block
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_const
r_int
id|blkbits
op_assign
id|inode-&gt;i_blkbits
suffix:semicolon
r_const
r_int
id|blocks_per_page
op_assign
id|PAGE_CACHE_SIZE
op_rshift
id|blkbits
suffix:semicolon
r_const
r_int
id|blocksize
op_assign
l_int|1
op_lshift
id|blkbits
suffix:semicolon
id|sector_t
id|block_in_file
suffix:semicolon
id|sector_t
id|last_block
suffix:semicolon
id|sector_t
id|blocks
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
r_int
id|page_block
suffix:semicolon
r_int
id|first_hole
op_assign
id|blocks_per_page
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
id|bh
suffix:semicolon
r_int
id|length
suffix:semicolon
r_int
id|fully_mapped
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|page_has_buffers
c_func
(paren
id|page
)paren
)paren
r_goto
id|confused
suffix:semicolon
id|block_in_file
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|blkbits
)paren
suffix:semicolon
id|last_block
op_assign
(paren
id|i_size_read
c_func
(paren
id|inode
)paren
op_plus
id|blocksize
op_minus
l_int|1
)paren
op_rshift
id|blkbits
suffix:semicolon
id|bh.b_page
op_assign
id|page
suffix:semicolon
r_for
c_loop
(paren
id|page_block
op_assign
l_int|0
suffix:semicolon
id|page_block
OL
id|blocks_per_page
suffix:semicolon
id|page_block
op_increment
comma
id|block_in_file
op_increment
)paren
(brace
id|bh.b_state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block_in_file
OL
id|last_block
)paren
(brace
r_if
c_cond
(paren
id|get_block
c_func
(paren
id|inode
comma
id|block_in_file
comma
op_amp
id|bh
comma
l_int|0
)paren
)paren
r_goto
id|confused
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
op_amp
id|bh
)paren
)paren
(brace
id|fully_mapped
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|first_hole
op_eq
id|blocks_per_page
)paren
id|first_hole
op_assign
id|page_block
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* some filesystems will copy data into the page during&n;&t;&t; * the get_block call, in which case we don&squot;t want to&n;&t;&t; * read it again.  map_buffer_to_page copies the data&n;&t;&t; * we just collected from get_block into the page&squot;s buffers&n;&t;&t; * so readpage doesn&squot;t have to repeat the get_block call&n;&t;&t; */
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
op_amp
id|bh
)paren
)paren
(brace
id|map_buffer_to_page
c_func
(paren
id|page
comma
op_amp
id|bh
comma
id|page_block
)paren
suffix:semicolon
r_goto
id|confused
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first_hole
op_ne
id|blocks_per_page
)paren
r_goto
id|confused
suffix:semicolon
multiline_comment|/* hole -&gt; non-hole */
multiline_comment|/* Contiguous blocks? */
r_if
c_cond
(paren
id|page_block
op_logical_and
id|blocks
(braket
id|page_block
op_minus
l_int|1
)braket
op_ne
id|bh.b_blocknr
op_minus
l_int|1
)paren
r_goto
id|confused
suffix:semicolon
id|blocks
(braket
id|page_block
)braket
op_assign
id|bh.b_blocknr
suffix:semicolon
id|bdev
op_assign
id|bh.b_bdev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first_hole
op_ne
id|blocks_per_page
)paren
(brace
r_char
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
op_plus
(paren
id|first_hole
op_lshift
id|blkbits
)paren
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
op_minus
(paren
id|first_hole
op_lshift
id|blkbits
)paren
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_hole
op_eq
l_int|0
)paren
(brace
id|SetPageUptodate
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
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|fully_mapped
)paren
(brace
id|SetPageMappedToDisk
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This page will go to BIO.  Do we need to send this BIO off first?&n;&t; */
r_if
c_cond
(paren
id|bio
op_logical_and
(paren
op_star
id|last_block_in_bio
op_ne
id|blocks
(braket
l_int|0
)braket
op_minus
l_int|1
)paren
)paren
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
id|alloc_new
suffix:colon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
(brace
id|bio
op_assign
id|mpage_alloc
c_func
(paren
id|bdev
comma
id|blocks
(braket
l_int|0
)braket
op_lshift
(paren
id|blkbits
op_minus
l_int|9
)paren
comma
id|nr_pages
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
r_goto
id|confused
suffix:semicolon
)brace
id|length
op_assign
id|first_hole
op_lshift
id|blkbits
suffix:semicolon
r_if
c_cond
(paren
id|bio_add_page
c_func
(paren
id|bio
comma
id|page
comma
id|length
comma
l_int|0
)paren
OL
id|length
)paren
(brace
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
r_goto
id|alloc_new
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer_boundary
c_func
(paren
op_amp
id|bh
)paren
op_logical_or
(paren
id|first_hole
op_ne
id|blocks_per_page
)paren
)paren
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
r_else
op_star
id|last_block_in_bio
op_assign
id|blocks
(braket
id|blocks_per_page
op_minus
l_int|1
)braket
suffix:semicolon
id|out
suffix:colon
r_return
id|bio
suffix:semicolon
id|confused
suffix:colon
r_if
c_cond
(paren
id|bio
)paren
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
id|block_read_full_page
c_func
(paren
id|page
comma
id|get_block
)paren
suffix:semicolon
r_else
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
r_int
DECL|function|mpage_readpages
id|mpage_readpages
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
id|nr_pages
comma
id|get_block_t
id|get_block
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
l_int|NULL
suffix:semicolon
r_int
id|page_idx
suffix:semicolon
id|sector_t
id|last_block_in_bio
op_assign
l_int|0
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
id|lru
)paren
suffix:semicolon
id|prefetchw
c_func
(paren
op_amp
id|page-&gt;flags
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
id|bio
op_assign
id|do_mpage_readpage
c_func
(paren
id|bio
comma
id|page
comma
id|nr_pages
op_minus
id|page_idx
comma
op_amp
id|last_block_in_bio
comma
id|get_block
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|pages
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mpage_readpages
id|EXPORT_SYMBOL
c_func
(paren
id|mpage_readpages
)paren
suffix:semicolon
multiline_comment|/*&n; * This isn&squot;t called much at all&n; */
DECL|function|mpage_readpage
r_int
id|mpage_readpage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|get_block_t
id|get_block
)paren
(brace
r_struct
id|bio
op_star
id|bio
op_assign
l_int|NULL
suffix:semicolon
id|sector_t
id|last_block_in_bio
op_assign
l_int|0
suffix:semicolon
id|bio
op_assign
id|do_mpage_readpage
c_func
(paren
id|bio
comma
id|page
comma
l_int|1
comma
op_amp
id|last_block_in_bio
comma
id|get_block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
id|mpage_bio_submit
c_func
(paren
id|READ
comma
id|bio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mpage_readpage
id|EXPORT_SYMBOL
c_func
(paren
id|mpage_readpage
)paren
suffix:semicolon
multiline_comment|/*&n; * Writing is not so simple.&n; *&n; * If the page has buffers then they will be used for obtaining the disk&n; * mapping.  We only support pages which are fully mapped-and-dirty, with a&n; * special case for pages which are unmapped at the end: end-of-file.&n; *&n; * If the page has no buffers (preferred) then the page is mapped here.&n; *&n; * If all blocks are found to be contiguous then the page can go into the&n; * BIO.  Otherwise fall back to the mapping&squot;s writepage().&n; * &n; * FIXME: This code wants an estimate of how many pages are still to be&n; * written, so it can intelligently allocate a suitably-sized BIO.  For now,&n; * just allocate full-size (16-page) BIOs.&n; */
r_static
r_struct
id|bio
op_star
DECL|function|mpage_writepage
id|mpage_writepage
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_struct
id|page
op_star
id|page
comma
id|get_block_t
id|get_block
comma
id|sector_t
op_star
id|last_block_in_bio
comma
r_int
op_star
id|ret
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_const
r_int
id|blkbits
op_assign
id|inode-&gt;i_blkbits
suffix:semicolon
r_int
r_int
id|end_index
suffix:semicolon
r_const
r_int
id|blocks_per_page
op_assign
id|PAGE_CACHE_SIZE
op_rshift
id|blkbits
suffix:semicolon
id|sector_t
id|last_block
suffix:semicolon
id|sector_t
id|block_in_file
suffix:semicolon
id|sector_t
id|blocks
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
r_int
id|page_block
suffix:semicolon
r_int
id|first_unmapped
op_assign
id|blocks_per_page
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|boundary
op_assign
l_int|0
suffix:semicolon
id|sector_t
id|boundary_block
op_assign
l_int|0
suffix:semicolon
r_struct
id|block_device
op_star
id|boundary_bdev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|length
suffix:semicolon
r_struct
id|buffer_head
id|map_bh
suffix:semicolon
id|loff_t
id|i_size
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
id|page_has_buffers
c_func
(paren
id|page
)paren
)paren
(brace
r_struct
id|buffer_head
op_star
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|head
suffix:semicolon
multiline_comment|/* If they&squot;re all mapped and dirty, do it */
id|page_block
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|BUG_ON
c_func
(paren
id|buffer_locked
c_func
(paren
id|bh
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * unmapped dirty buffers are created by&n;&t;&t;&t;&t; * __set_page_dirty_buffers -&gt; mmapped data&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|buffer_dirty
c_func
(paren
id|bh
)paren
)paren
r_goto
id|confused
suffix:semicolon
r_if
c_cond
(paren
id|first_unmapped
op_eq
id|blocks_per_page
)paren
id|first_unmapped
op_assign
id|page_block
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first_unmapped
op_ne
id|blocks_per_page
)paren
r_goto
id|confused
suffix:semicolon
multiline_comment|/* hole -&gt; non-hole */
r_if
c_cond
(paren
op_logical_neg
id|buffer_dirty
c_func
(paren
id|bh
)paren
op_logical_or
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
r_goto
id|confused
suffix:semicolon
r_if
c_cond
(paren
id|page_block
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_blocknr
op_ne
id|blocks
(braket
id|page_block
op_minus
l_int|1
)braket
op_plus
l_int|1
)paren
r_goto
id|confused
suffix:semicolon
)brace
id|blocks
(braket
id|page_block
op_increment
)braket
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
id|boundary
op_assign
id|buffer_boundary
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boundary
)paren
(brace
id|boundary_block
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
id|boundary_bdev
op_assign
id|bh-&gt;b_bdev
suffix:semicolon
)brace
id|bdev
op_assign
id|bh-&gt;b_bdev
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|bh
op_assign
id|bh-&gt;b_this_page
)paren
op_ne
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_unmapped
)paren
r_goto
id|page_is_mapped
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Page has buffers, but they are all unmapped. The page was&n;&t;&t; * created by pagein or read over a hole which was handled by&n;&t;&t; * block_read_full_page().  If this address_space is also&n;&t;&t; * using mpage_readpages then this can rarely happen.&n;&t;&t; */
r_goto
id|confused
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The page has no buffers: map it to disk&n;&t; */
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|block_in_file
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|blkbits
)paren
suffix:semicolon
id|last_block
op_assign
(paren
id|i_size
op_minus
l_int|1
)paren
op_rshift
id|blkbits
suffix:semicolon
id|map_bh.b_page
op_assign
id|page
suffix:semicolon
r_for
c_loop
(paren
id|page_block
op_assign
l_int|0
suffix:semicolon
id|page_block
OL
id|blocks_per_page
suffix:semicolon
)paren
(brace
id|map_bh.b_state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_block
c_func
(paren
id|inode
comma
id|block_in_file
comma
op_amp
id|map_bh
comma
l_int|1
)paren
)paren
r_goto
id|confused
suffix:semicolon
r_if
c_cond
(paren
id|buffer_new
c_func
(paren
op_amp
id|map_bh
)paren
)paren
id|unmap_underlying_metadata
c_func
(paren
id|map_bh.b_bdev
comma
id|map_bh.b_blocknr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_boundary
c_func
(paren
op_amp
id|map_bh
)paren
)paren
(brace
id|boundary_block
op_assign
id|map_bh.b_blocknr
suffix:semicolon
id|boundary_bdev
op_assign
id|map_bh.b_bdev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page_block
)paren
(brace
r_if
c_cond
(paren
id|map_bh.b_blocknr
op_ne
id|blocks
(braket
id|page_block
op_minus
l_int|1
)braket
op_plus
l_int|1
)paren
r_goto
id|confused
suffix:semicolon
)brace
id|blocks
(braket
id|page_block
op_increment
)braket
op_assign
id|map_bh.b_blocknr
suffix:semicolon
id|boundary
op_assign
id|buffer_boundary
c_func
(paren
op_amp
id|map_bh
)paren
suffix:semicolon
id|bdev
op_assign
id|map_bh.b_bdev
suffix:semicolon
r_if
c_cond
(paren
id|block_in_file
op_eq
id|last_block
)paren
r_break
suffix:semicolon
id|block_in_file
op_increment
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|page_block
op_eq
l_int|0
)paren
suffix:semicolon
id|first_unmapped
op_assign
id|page_block
suffix:semicolon
id|page_is_mapped
suffix:colon
id|end_index
op_assign
id|i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
op_ge
id|end_index
)paren
(brace
multiline_comment|/*&n;&t;&t; * The page straddles i_size.  It must be zeroed out on each&n;&t;&t; * and every writepage invokation because it may be mmapped.&n;&t;&t; * &quot;A file is mapped in multiples of the page size.  For a file&n;&t;&t; * that is not a multiple of the page size, the remaining memory&n;&t;&t; * is zeroed when mapped, and writes to that region are not&n;&t;&t; * written out to the file.&quot;&n;&t;&t; */
r_int
id|offset
op_assign
id|i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OG
id|end_index
op_logical_or
op_logical_neg
id|offset
)paren
r_goto
id|confused
suffix:semicolon
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
op_plus
id|offset
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
op_minus
id|offset
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This page will go to BIO.  Do we need to send this BIO off first?&n;&t; */
r_if
c_cond
(paren
id|bio
op_logical_and
op_star
id|last_block_in_bio
op_ne
id|blocks
(braket
l_int|0
)braket
op_minus
l_int|1
)paren
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
id|alloc_new
suffix:colon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
(brace
id|bio
op_assign
id|mpage_alloc
c_func
(paren
id|bdev
comma
id|blocks
(braket
l_int|0
)braket
op_lshift
(paren
id|blkbits
op_minus
l_int|9
)paren
comma
id|bio_get_nr_vecs
c_func
(paren
id|bdev
)paren
comma
id|GFP_NOFS
op_or
id|__GFP_HIGH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
op_eq
l_int|NULL
)paren
r_goto
id|confused
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Must try to add the page before marking the buffer clean or&n;&t; * the confused fail path above (OOM) will be very confused when&n;&t; * it finds all bh marked clean (i.e. it will not write anything)&n;&t; */
id|length
op_assign
id|first_unmapped
op_lshift
id|blkbits
suffix:semicolon
r_if
c_cond
(paren
id|bio_add_page
c_func
(paren
id|bio
comma
id|page
comma
id|length
comma
l_int|0
)paren
OL
id|length
)paren
(brace
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
r_goto
id|alloc_new
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * OK, we have our BIO, so we can now mark the buffers clean.  Make&n;&t; * sure to only clean buffers which we know we&squot;ll be writing.&n;&t; */
r_if
c_cond
(paren
id|page_has_buffers
c_func
(paren
id|page
)paren
)paren
(brace
r_struct
id|buffer_head
op_star
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|head
suffix:semicolon
r_int
id|buffer_counter
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buffer_counter
op_increment
op_eq
id|first_unmapped
)paren
r_break
suffix:semicolon
id|clear_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
)brace
r_while
c_loop
(paren
id|bh
op_ne
id|head
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we cannot drop the bh if the page is not uptodate&n;&t;&t; * or a concurrent readpage would fail to serialize with the bh&n;&t;&t; * and it would read from disk before we reach the platter.&n;&t;&t; */
r_if
c_cond
(paren
id|buffer_heads_over_limit
op_logical_and
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
id|try_to_free_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|set_page_writeback
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
r_if
c_cond
(paren
id|boundary
op_logical_or
(paren
id|first_unmapped
op_ne
id|blocks_per_page
)paren
)paren
(brace
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boundary_block
)paren
(brace
id|write_boundary_block
c_func
(paren
id|boundary_bdev
comma
id|boundary_block
comma
l_int|1
op_lshift
id|blkbits
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|last_block_in_bio
op_assign
id|blocks
(braket
id|blocks_per_page
op_minus
l_int|1
)braket
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
id|confused
suffix:colon
r_if
c_cond
(paren
id|bio
)paren
id|bio
op_assign
id|mpage_bio_submit
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
op_star
id|ret
op_assign
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|writepage
c_func
(paren
id|page
comma
id|wbc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The caller has a ref on the inode, so *mapping is stable&n;&t; */
r_if
c_cond
(paren
op_star
id|ret
)paren
(brace
r_if
c_cond
(paren
op_star
id|ret
op_eq
op_minus
id|ENOSPC
)paren
id|set_bit
c_func
(paren
id|AS_ENOSPC
comma
op_amp
id|mapping-&gt;flags
)paren
suffix:semicolon
r_else
id|set_bit
c_func
(paren
id|AS_EIO
comma
op_amp
id|mapping-&gt;flags
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|bio
suffix:semicolon
)brace
multiline_comment|/**&n; * mpage_writepages - walk the list of dirty pages of the given&n; * address space and writepage() all of them.&n; * &n; * @mapping: address space structure to write&n; * @wbc: subtract the number of written pages from *@wbc-&gt;nr_to_write&n; * @get_block: the filesystem&squot;s block mapper function.&n; *             If this is NULL then use a_ops-&gt;writepage.  Otherwise, go&n; *             direct-to-BIO.&n; *&n; * This is a library function, which implements the writepages()&n; * address_space_operation.&n; *&n; * If a page is already under I/O, generic_writepages() skips it, even&n; * if it&squot;s dirty.  This is desirable behaviour for memory-cleaning writeback,&n; * but it is INCORRECT for data-integrity system calls such as fsync().  fsync()&n; * and msync() need to guarantee that all the data which was dirty at the time&n; * the call was made get new I/O started against them.  If wbc-&gt;sync_mode is&n; * WB_SYNC_ALL then we were called for data integrity and we must wait for&n; * existing IO to complete.&n; */
r_int
DECL|function|mpage_writepages
id|mpage_writepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|writeback_control
op_star
id|wbc
comma
id|get_block_t
id|get_block
)paren
(brace
r_struct
id|backing_dev_info
op_star
id|bdi
op_assign
id|mapping-&gt;backing_dev_info
suffix:semicolon
r_struct
id|bio
op_star
id|bio
op_assign
l_int|NULL
suffix:semicolon
id|sector_t
id|last_block_in_bio
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|done
op_assign
l_int|0
suffix:semicolon
r_int
(paren
op_star
id|writepage
)paren
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
suffix:semicolon
r_struct
id|pagevec
id|pvec
suffix:semicolon
r_int
id|nr_pages
suffix:semicolon
id|pgoff_t
id|index
suffix:semicolon
id|pgoff_t
id|end
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Inclusive */
r_int
id|scanned
op_assign
l_int|0
suffix:semicolon
r_int
id|is_range
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|wbc-&gt;nonblocking
op_logical_and
id|bdi_write_congested
c_func
(paren
id|bdi
)paren
)paren
(brace
id|wbc-&gt;encountered_congestion
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|writepage
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|get_block
op_eq
l_int|NULL
)paren
id|writepage
op_assign
id|mapping-&gt;a_ops-&gt;writepage
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
r_if
c_cond
(paren
id|wbc-&gt;sync_mode
op_eq
id|WB_SYNC_NONE
)paren
(brace
id|index
op_assign
id|mapping-&gt;writeback_index
suffix:semicolon
multiline_comment|/* Start from prev offset */
)brace
r_else
(brace
id|index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* whole-file sweep */
id|scanned
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wbc-&gt;start
op_logical_or
id|wbc-&gt;end
)paren
(brace
id|index
op_assign
id|wbc-&gt;start
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|end
op_assign
id|wbc-&gt;end
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|is_range
op_assign
l_int|1
suffix:semicolon
id|scanned
op_assign
l_int|1
suffix:semicolon
)brace
id|retry
suffix:colon
r_while
c_loop
(paren
op_logical_neg
id|done
op_logical_and
(paren
id|nr_pages
op_assign
id|pagevec_lookup_tag
c_func
(paren
op_amp
id|pvec
comma
id|mapping
comma
op_amp
id|index
comma
id|PAGECACHE_TAG_DIRTY
comma
id|min
c_func
(paren
id|end
op_minus
id|index
comma
(paren
id|pgoff_t
)paren
id|PAGEVEC_SIZE
op_minus
l_int|1
)paren
op_plus
l_int|1
)paren
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|scanned
op_assign
l_int|1
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
id|nr_pages
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
multiline_comment|/*&n;&t;&t;&t; * At this point we hold neither mapping-&gt;tree_lock nor&n;&t;&t;&t; * lock on the page itself: the page may be truncated or&n;&t;&t;&t; * invalidated (changing page-&gt;mapping to NULL), or even&n;&t;&t;&t; * swizzled back from swapper_space to tmpfs file&n;&t;&t;&t; * mapping&n;&t;&t;&t; */
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|page-&gt;mapping
op_ne
id|mapping
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
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|is_range
)paren
op_logical_and
id|page-&gt;index
OG
id|end
)paren
(brace
id|done
op_assign
l_int|1
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wbc-&gt;sync_mode
op_ne
id|WB_SYNC_NONE
)paren
id|wait_on_page_writeback
c_func
(paren
id|page
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
op_logical_or
op_logical_neg
id|clear_page_dirty_for_io
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
r_if
c_cond
(paren
id|writepage
)paren
(brace
id|ret
op_assign
(paren
op_star
id|writepage
)paren
(paren
id|page
comma
id|wbc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOSPC
)paren
id|set_bit
c_func
(paren
id|AS_ENOSPC
comma
op_amp
id|mapping-&gt;flags
)paren
suffix:semicolon
r_else
id|set_bit
c_func
(paren
id|AS_EIO
comma
op_amp
id|mapping-&gt;flags
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|bio
op_assign
id|mpage_writepage
c_func
(paren
id|bio
comma
id|page
comma
id|get_block
comma
op_amp
id|last_block_in_bio
comma
op_amp
id|ret
comma
id|wbc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_logical_or
(paren
op_decrement
(paren
id|wbc-&gt;nr_to_write
)paren
op_le
l_int|0
)paren
)paren
id|done
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|wbc-&gt;nonblocking
op_logical_and
id|bdi_write_congested
c_func
(paren
id|bdi
)paren
)paren
(brace
id|wbc-&gt;encountered_congestion
op_assign
l_int|1
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
)brace
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
op_logical_neg
id|scanned
op_logical_and
op_logical_neg
id|done
)paren
(brace
multiline_comment|/*&n;&t;&t; * We hit the last page and there is more work to be done: wrap&n;&t;&t; * back to the start of the file&n;&t;&t; */
id|scanned
op_assign
l_int|1
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_range
)paren
id|mapping-&gt;writeback_index
op_assign
id|index
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
id|mpage_bio_submit
c_func
(paren
id|WRITE
comma
id|bio
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|mpage_writepages
id|EXPORT_SYMBOL
c_func
(paren
id|mpage_writepages
)paren
suffix:semicolon
eof
