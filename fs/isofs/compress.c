multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *   &n; *   Copyright 2001 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,&n; *   USA; either version 2 of the License, or (at your option) any later&n; *   version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * linux/fs/isofs/compress.c&n; *&n; * Transparent decompression of files on an iso9660 filesystem&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/zlib_fs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;zisofs.h&quot;
multiline_comment|/* This should probably be global. */
DECL|variable|zisofs_sink_page
r_static
r_char
id|zisofs_sink_page
(braket
id|PAGE_CACHE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * This contains the zlib memory allocation and the mutex for the&n; * allocation; this avoids failures at block-decompression time.&n; */
DECL|variable|zisofs_zlib_workspace
r_static
r_void
op_star
id|zisofs_zlib_workspace
suffix:semicolon
DECL|variable|zisofs_zlib_semaphore
r_static
r_struct
id|semaphore
id|zisofs_zlib_semaphore
suffix:semicolon
multiline_comment|/*&n; * When decompressing, we typically obtain more than one page&n; * per reference.  We inject the additional pages into the page&n; * cache as a form of readahead.&n; */
DECL|function|zisofs_readpage
r_static
r_int
id|zisofs_readpage
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
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_int
r_int
id|maxpage
comma
id|xpage
comma
id|fpage
comma
id|blockindex
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|blockptr
comma
id|blockendptr
comma
id|cstart
comma
id|cend
comma
id|csize
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|ptrbh
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|bufsize
op_assign
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
id|bufshift
op_assign
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
id|bufmask
op_assign
id|bufsize
op_minus
l_int|1
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|header_size
op_assign
id|ISOFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_format_parm
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|zisofs_block_shift
op_assign
id|ISOFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_format_parm
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unsigned long zisofs_block_size = 1UL &lt;&lt; zisofs_block_shift; */
r_int
r_int
id|zisofs_block_page_shift
op_assign
id|zisofs_block_shift
op_minus
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
r_int
id|zisofs_block_pages
op_assign
l_int|1UL
op_lshift
id|zisofs_block_page_shift
suffix:semicolon
r_int
r_int
id|zisofs_block_page_mask
op_assign
id|zisofs_block_pages
op_minus
l_int|1
suffix:semicolon
r_struct
id|page
op_star
id|pages
(braket
id|zisofs_block_pages
)braket
suffix:semicolon
r_int
r_int
id|index
op_assign
id|page-&gt;index
suffix:semicolon
r_int
id|indexblocks
suffix:semicolon
multiline_comment|/* We have already been given one page, this is the one&n;&t;   we must do. */
id|xpage
op_assign
id|index
op_amp
id|zisofs_block_page_mask
suffix:semicolon
id|pages
(braket
id|xpage
)braket
op_assign
id|page
suffix:semicolon
multiline_comment|/* The remaining pages need to be allocated and inserted */
id|offset
op_assign
id|index
op_amp
op_complement
id|zisofs_block_page_mask
suffix:semicolon
id|blockindex
op_assign
id|offset
op_rshift
id|zisofs_block_page_shift
suffix:semicolon
id|maxpage
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|maxpage
op_assign
id|min
c_func
(paren
id|zisofs_block_pages
comma
id|maxpage
op_minus
id|offset
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
id|maxpage
suffix:semicolon
id|i
op_increment
comma
id|offset
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|xpage
)paren
(brace
id|pages
(braket
id|i
)braket
op_assign
id|grab_cache_page_nowait
c_func
(paren
id|mapping
comma
id|offset
)paren
suffix:semicolon
)brace
id|page
op_assign
id|pages
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|ClearPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* This is the last page filled, plus one; used in case of abort. */
id|fpage
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Find the pointer to this specific chunk */
multiline_comment|/* Note: we&squot;re not using isonum_731() here because the data is known aligned */
multiline_comment|/* Note: header_size is in 32-bit words (4 bytes) */
id|blockptr
op_assign
(paren
id|header_size
op_plus
id|blockindex
)paren
op_lshift
l_int|2
suffix:semicolon
id|blockendptr
op_assign
id|blockptr
op_plus
l_int|4
suffix:semicolon
id|indexblocks
op_assign
(paren
(paren
id|blockptr
op_xor
id|blockendptr
)paren
op_rshift
id|bufshift
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
id|ptrbh
(braket
l_int|0
)braket
op_assign
id|ptrbh
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|isofs_get_blocks
c_func
(paren
id|inode
comma
id|blockptr
op_rshift
id|bufshift
comma
id|ptrbh
comma
id|indexblocks
)paren
op_ne
id|indexblocks
)paren
(brace
r_if
c_cond
(paren
id|ptrbh
(braket
l_int|0
)braket
)paren
id|brelse
c_func
(paren
id|ptrbh
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: Null buffer on reading block table, inode = %lu, block = %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|blockptr
op_rshift
id|bufshift
)paren
suffix:semicolon
r_goto
id|eio
suffix:semicolon
)brace
id|ll_rw_block
c_func
(paren
id|READ
comma
id|indexblocks
comma
id|ptrbh
)paren
suffix:semicolon
id|bh
op_assign
id|ptrbh
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
comma
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: Failed to read block table, inode = %lu, block = %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|blockptr
op_rshift
id|bufshift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptrbh
(braket
l_int|1
)braket
)paren
id|brelse
c_func
(paren
id|ptrbh
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_goto
id|eio
suffix:semicolon
)brace
id|cstart
op_assign
id|le32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
(paren
id|blockptr
op_amp
id|bufmask
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|indexblocks
op_eq
l_int|2
)paren
(brace
multiline_comment|/* We just crossed a block boundary.  Switch to the next block */
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|ptrbh
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
comma
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: Failed to read block table, inode = %lu, block = %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|blockendptr
op_rshift
id|bufshift
)paren
suffix:semicolon
r_goto
id|eio
suffix:semicolon
)brace
)brace
id|cend
op_assign
id|le32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
(paren
id|blockendptr
op_amp
id|bufmask
)paren
)paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|csize
op_assign
id|cend
op_minus
id|cstart
suffix:semicolon
multiline_comment|/* Now page[] contains an array of pages, any of which can be NULL,&n;&t;   and the locks on which we hold.  We should now read the data and&n;&t;   release the pages.  If the pages are NULL the decompressed data&n;&t;   for that particular page should be discarded. */
r_if
c_cond
(paren
id|csize
op_eq
l_int|0
)paren
(brace
multiline_comment|/* This data block is empty. */
r_for
c_loop
(paren
id|fpage
op_assign
l_int|0
suffix:semicolon
id|fpage
OL
id|maxpage
suffix:semicolon
id|fpage
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|page
op_assign
id|pages
(braket
id|fpage
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpage
op_eq
id|xpage
)paren
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The critical page */
r_else
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* This data block is compressed. */
id|z_stream
id|stream
suffix:semicolon
r_int
id|bail
op_assign
l_int|0
comma
id|left_out
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|zerr
suffix:semicolon
r_int
id|needblocks
op_assign
(paren
id|csize
op_plus
(paren
id|cstart
op_amp
id|bufmask
)paren
op_plus
id|bufmask
)paren
op_rshift
id|bufshift
suffix:semicolon
r_int
id|haveblocks
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhs
(braket
id|needblocks
op_plus
l_int|1
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
op_star
id|bhptr
suffix:semicolon
multiline_comment|/* Because zlib is not thread-safe, do all the I/O at the top. */
id|blockptr
op_assign
id|cstart
op_rshift
id|bufshift
suffix:semicolon
id|memset
c_func
(paren
id|bhs
comma
l_int|0
comma
(paren
id|needblocks
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|buffer_head
op_star
)paren
)paren
suffix:semicolon
id|haveblocks
op_assign
id|isofs_get_blocks
c_func
(paren
id|inode
comma
id|blockptr
comma
id|bhs
comma
id|needblocks
)paren
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|READ
comma
id|haveblocks
comma
id|bhs
)paren
suffix:semicolon
id|bhptr
op_assign
op_amp
id|bhs
(braket
l_int|0
)braket
suffix:semicolon
id|bh
op_assign
op_star
id|bhptr
op_increment
suffix:semicolon
multiline_comment|/* First block is special since it may be fractional.&n;&t;&t;   We also wait for it before grabbing the zlib&n;&t;&t;   semaphore; odds are that the subsequent blocks are&n;&t;&t;   going to come in in short order so we don&squot;t hold&n;&t;&t;   the zlib semaphore longer than necessary. */
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
comma
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: Hit null buffer, fpage = %d, xpage = %d, csize = %ld&bslash;n&quot;
comma
id|fpage
comma
id|xpage
comma
id|csize
)paren
suffix:semicolon
r_goto
id|b_eio
suffix:semicolon
)brace
id|stream.next_in
op_assign
id|bh-&gt;b_data
op_plus
(paren
id|cstart
op_amp
id|bufmask
)paren
suffix:semicolon
id|stream.avail_in
op_assign
id|min
c_func
(paren
id|bufsize
op_minus
(paren
id|cstart
op_amp
id|bufmask
)paren
comma
id|csize
)paren
suffix:semicolon
id|csize
op_sub_assign
id|stream.avail_in
suffix:semicolon
id|stream.workspace
op_assign
id|zisofs_zlib_workspace
suffix:semicolon
id|down
c_func
(paren
op_amp
id|zisofs_zlib_semaphore
)paren
suffix:semicolon
id|zerr
op_assign
id|zlib_fs_inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zerr
op_ne
id|Z_OK
)paren
(brace
r_if
c_cond
(paren
id|err
op_logical_and
id|zerr
op_eq
id|Z_MEM_ERROR
)paren
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: zisofs_inflateInit returned %d&bslash;n&quot;
comma
id|zerr
)paren
suffix:semicolon
r_goto
id|z_eio
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|bail
op_logical_and
id|fpage
OL
id|maxpage
)paren
(brace
id|page
op_assign
id|pages
(braket
id|fpage
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
id|stream.next_out
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|stream.next_out
op_assign
(paren
r_void
op_star
)paren
op_amp
id|zisofs_sink_page
suffix:semicolon
id|stream.avail_out
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|stream.avail_out
)paren
(brace
r_int
id|ao
comma
id|ai
suffix:semicolon
r_if
c_cond
(paren
id|stream.avail_in
op_eq
l_int|0
op_logical_and
id|left_out
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|csize
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;zisofs: ZF read beyond end of input&bslash;n&quot;
)paren
suffix:semicolon
id|bail
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|bh
op_assign
op_star
id|bhptr
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
id|wait_on_buffer
c_func
(paren
id|bh
)paren
comma
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
)paren
(brace
multiline_comment|/* Reached an EIO */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: Hit null buffer, fpage = %d, xpage = %d, csize = %ld&bslash;n&quot;
comma
id|fpage
comma
id|xpage
comma
id|csize
)paren
suffix:semicolon
id|bail
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|stream.next_in
op_assign
id|bh-&gt;b_data
suffix:semicolon
id|stream.avail_in
op_assign
id|min
c_func
(paren
id|csize
comma
id|bufsize
)paren
suffix:semicolon
id|csize
op_sub_assign
id|stream.avail_in
suffix:semicolon
)brace
)brace
id|ao
op_assign
id|stream.avail_out
suffix:semicolon
id|ai
op_assign
id|stream.avail_in
suffix:semicolon
id|zerr
op_assign
id|zlib_fs_inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_SYNC_FLUSH
)paren
suffix:semicolon
id|left_out
op_assign
id|stream.avail_out
suffix:semicolon
r_if
c_cond
(paren
id|zerr
op_eq
id|Z_BUF_ERROR
op_logical_and
id|stream.avail_in
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|zerr
op_ne
id|Z_OK
)paren
(brace
multiline_comment|/* EOF, error, or trying to read beyond end of input */
r_if
c_cond
(paren
id|err
op_logical_and
id|zerr
op_eq
id|Z_MEM_ERROR
)paren
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|zerr
op_ne
id|Z_STREAM_END
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zisofs: zisofs_inflate returned %d, inode = %lu, index = %lu, fpage = %d, xpage = %d, avail_in = %d, avail_out = %d, ai = %d, ao = %d&bslash;n&quot;
comma
id|zerr
comma
id|inode-&gt;i_ino
comma
id|index
comma
id|fpage
comma
id|xpage
comma
id|stream.avail_in
comma
id|stream.avail_out
comma
id|ai
comma
id|ao
)paren
suffix:semicolon
id|bail
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|stream.avail_out
op_logical_and
id|zerr
op_eq
id|Z_STREAM_END
)paren
(brace
multiline_comment|/* Fractional page written before EOF.  This may&n;&t;&t;&t;&t;   be the last page in the file. */
id|memset
c_func
(paren
id|stream.next_out
comma
l_int|0
comma
id|stream.avail_out
)paren
suffix:semicolon
id|stream.avail_out
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|stream.avail_out
)paren
(brace
multiline_comment|/* This page completed */
r_if
c_cond
(paren
id|page
)paren
(brace
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpage
op_eq
id|xpage
)paren
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The critical page */
r_else
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|fpage
op_increment
suffix:semicolon
)brace
)brace
id|zlib_fs_inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|z_eio
suffix:colon
id|up
c_func
(paren
op_amp
id|zisofs_zlib_semaphore
)paren
suffix:semicolon
id|b_eio
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|haveblocks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bhs
(braket
id|i
)braket
)paren
id|brelse
c_func
(paren
id|bhs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|eio
suffix:colon
multiline_comment|/* Release any residual pages, do not SetPageUptodate */
r_while
c_loop
(paren
id|fpage
OL
id|maxpage
)paren
(brace
id|page
op_assign
id|pages
(braket
id|fpage
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpage
op_eq
id|xpage
)paren
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpage
op_ne
id|xpage
)paren
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|fpage
op_increment
suffix:semicolon
)brace
multiline_comment|/* At this point, err contains 0 or -EIO depending on the &quot;critical&quot; page */
r_return
id|err
suffix:semicolon
)brace
DECL|variable|zisofs_aops
r_struct
id|address_space_operations
id|zisofs_aops
op_assign
(brace
id|readpage
suffix:colon
id|zisofs_readpage
comma
multiline_comment|/* No sync_page operation supported? */
multiline_comment|/* No bmap operation supported */
)brace
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|function|zisofs_init
r_int
id|__init
id|zisofs_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|initialized
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;zisofs_init: called more than once&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|zisofs_zlib_workspace
op_assign
id|vmalloc
c_func
(paren
id|zlib_fs_inflate_workspacesize
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zisofs_zlib_workspace
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|zisofs_zlib_semaphore
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zisofs_cleanup
r_void
id|__exit
id|zisofs_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;zisofs_cleanup: called without initialization&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vfree
c_func
(paren
id|zisofs_zlib_workspace
)paren
suffix:semicolon
id|initialized
op_assign
l_int|0
suffix:semicolon
)brace
eof
