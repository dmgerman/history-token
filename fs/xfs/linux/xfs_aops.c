multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
id|STATIC
r_int
id|delalloc_convert
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
id|STATIC
r_int
DECL|function|map_blocks
id|map_blocks
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|offset
comma
id|ssize_t
id|count
comma
id|page_buf_bmap_t
op_star
id|pbmapp
comma
r_int
id|flags
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
comma
id|nmaps
op_assign
l_int|1
suffix:semicolon
id|retry
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|PBF_FILE_ALLOCATE
)paren
(brace
id|VOP_STRATEGY
c_func
(paren
id|vp
comma
id|offset
comma
id|count
comma
id|flags
comma
l_int|NULL
comma
id|pbmapp
comma
op_amp
id|nmaps
comma
id|error
)paren
suffix:semicolon
)brace
r_else
(brace
id|VOP_BMAP
c_func
(paren
id|vp
comma
id|offset
comma
id|count
comma
id|flags
comma
l_int|NULL
comma
id|pbmapp
comma
op_amp
id|nmaps
comma
id|error
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|PBF_WRITE
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|flags
op_amp
id|PBF_DIRECT
)paren
op_logical_and
id|nmaps
op_logical_and
(paren
id|pbmapp-&gt;pbm_flags
op_amp
id|PBMF_DELAY
)paren
)paren
)paren
(brace
id|flags
op_assign
id|PBF_WRITE
op_or
id|PBF_FILE_ALLOCATE
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
id|VMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * match_offset_to_mapping&n; * Finds the corresponding mapping in block @map array of the&n; * given @offset within a @page.&n; */
id|STATIC
id|page_buf_bmap_t
op_star
DECL|function|match_offset_to_mapping
id|match_offset_to_mapping
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|page_buf_bmap_t
op_star
id|map
comma
r_int
r_int
id|offset
)paren
(brace
id|loff_t
id|full_offset
suffix:semicolon
multiline_comment|/* offset from start of file */
id|ASSERT
c_func
(paren
id|offset
OL
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|full_offset
op_assign
id|page-&gt;index
suffix:semicolon
multiline_comment|/* NB: using 64bit number */
id|full_offset
op_lshift_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* offset from file start */
id|full_offset
op_add_assign
id|offset
suffix:semicolon
multiline_comment|/* offset from page start */
r_if
c_cond
(paren
id|full_offset
OL
id|map-&gt;pbm_offset
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;pbm_offset
op_plus
id|map-&gt;pbm_bsize
OG
id|full_offset
)paren
r_return
id|map
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|map_buffer_at_offset
id|map_buffer_at_offset
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
r_int
id|offset
comma
r_int
id|block_bits
comma
id|page_buf_bmap_t
op_star
id|mp
)paren
(brace
id|page_buf_daddr_t
id|bn
suffix:semicolon
id|loff_t
id|delta
suffix:semicolon
r_int
id|sector_shift
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
(paren
id|mp-&gt;pbm_flags
op_amp
id|PBMF_HOLE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
(paren
id|mp-&gt;pbm_flags
op_amp
id|PBMF_DELAY
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
(paren
id|mp-&gt;pbm_flags
op_amp
id|PBMF_UNWRITTEN
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|mp-&gt;pbm_bn
op_ne
id|PAGE_BUF_DADDR_NULL
)paren
suffix:semicolon
id|delta
op_assign
id|page-&gt;index
suffix:semicolon
id|delta
op_lshift_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|delta
op_add_assign
id|offset
suffix:semicolon
id|delta
op_sub_assign
id|mp-&gt;pbm_offset
suffix:semicolon
id|delta
op_rshift_assign
id|block_bits
suffix:semicolon
id|sector_shift
op_assign
id|block_bits
op_minus
l_int|9
suffix:semicolon
id|bn
op_assign
id|mp-&gt;pbm_bn
op_rshift
id|sector_shift
suffix:semicolon
id|bn
op_add_assign
id|delta
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|bn
op_lshift
id|sector_shift
)paren
op_ge
id|mp-&gt;pbm_bn
)paren
suffix:semicolon
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|bn
suffix:semicolon
id|bh-&gt;b_bdev
op_assign
id|mp-&gt;pbm_target-&gt;pbr_bdev
suffix:semicolon
id|set_buffer_mapped
c_func
(paren
id|bh
)paren
suffix:semicolon
id|clear_buffer_delay
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert delalloc space to real space, do not flush the&n; * data out to disk, that will be done by the caller.&n; */
id|STATIC
r_int
DECL|function|release_page
id|release_page
c_func
(paren
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
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
r_int
id|end_index
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Are we off the end of the file ? */
r_if
c_cond
(paren
id|page-&gt;index
op_ge
id|end_index
)paren
(brace
r_int
id|offset
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page-&gt;index
op_ge
id|end_index
op_plus
l_int|1
)paren
op_logical_or
op_logical_neg
id|offset
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|ret
op_assign
id|delalloc_convert
c_func
(paren
id|inode
comma
id|page
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|block_invalidatepage
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert delalloc or unmapped space to real space and flush out&n; * to disk.&n; */
id|STATIC
r_int
DECL|function|write_full_page
id|write_full_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|delalloc
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
r_int
id|end_index
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Are we off the end of the file ? */
r_if
c_cond
(paren
id|page-&gt;index
op_ge
id|end_index
)paren
(brace
r_int
id|offset
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page-&gt;index
op_ge
id|end_index
op_plus
l_int|1
)paren
op_logical_or
op_logical_neg
id|offset
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
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
id|ret
op_assign
id|delalloc_convert
c_func
(paren
id|inode
comma
id|page
comma
l_int|1
comma
id|delalloc
op_eq
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * If it&squot;s delalloc and we have nowhere to put it,&n;&t;&t; * throw it away.&n;&t;&t; */
r_if
c_cond
(paren
id|delalloc
)paren
id|block_invalidatepage
c_func
(paren
id|page
comma
l_int|0
)paren
suffix:semicolon
id|ClearPageUptodate
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
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Look for a page at index which is unlocked and not mapped&n; * yet - clustering for mmap write case.&n; */
id|STATIC
r_int
r_int
DECL|function|probe_unmapped_page
id|probe_unmapped_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
comma
r_int
r_int
id|pg_offset
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|page
op_assign
id|find_get_page
c_func
(paren
id|mapping
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|0
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
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
id|PageDirty
c_func
(paren
id|page
)paren
)paren
(brace
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
id|ret
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_else
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|head
suffix:semicolon
id|bh
op_assign
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buffer_mapped
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
(brace
r_break
suffix:semicolon
)brace
id|ret
op_add_assign
id|bh-&gt;b_size
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
id|pg_offset
)paren
r_break
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
)brace
)brace
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
r_return
id|ret
suffix:semicolon
)brace
id|STATIC
r_int
r_int
DECL|function|probe_unmapped_cluster
id|probe_unmapped_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|startpage
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|buffer_head
op_star
id|head
)paren
(brace
r_int
r_int
id|tindex
comma
id|tlast
suffix:semicolon
r_int
r_int
id|len
comma
id|total
op_assign
l_int|0
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
multiline_comment|/* First sum forwards in this page */
r_do
(brace
r_if
c_cond
(paren
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
r_break
suffix:semicolon
id|total
op_add_assign
id|bh-&gt;b_size
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
multiline_comment|/* if we reached the end of the page, sum forwards in&n;&t; * following pages.&n;&t; */
r_if
c_cond
(paren
id|bh
op_eq
id|head
)paren
(brace
id|tlast
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|tindex
op_assign
id|startpage-&gt;index
op_plus
l_int|1
suffix:semicolon
id|tindex
OL
id|tlast
suffix:semicolon
id|tindex
op_increment
)paren
(brace
id|len
op_assign
id|probe_unmapped_page
c_func
(paren
id|mapping
comma
id|tindex
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
id|total
op_add_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tindex
op_eq
id|tlast
)paren
op_logical_and
(paren
id|inode-&gt;i_size
op_amp
op_complement
id|PAGE_CACHE_MASK
)paren
)paren
(brace
id|len
op_assign
id|probe_unmapped_page
c_func
(paren
id|mapping
comma
id|tindex
comma
id|inode-&gt;i_size
op_amp
op_complement
id|PAGE_CACHE_MASK
)paren
suffix:semicolon
id|total
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_return
id|total
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for a given page (index) in the inode &amp; test if it is delayed.&n; * Returns page locked and with an extra reference count.&n; */
id|STATIC
r_struct
id|page
op_star
DECL|function|probe_page
id|probe_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|index
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|find_get_page
c_func
(paren
id|inode-&gt;i_mapping
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|NULL
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
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
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
id|bh
comma
op_star
id|head
suffix:semicolon
id|bh
op_assign
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buffer_delay
c_func
(paren
id|bh
)paren
)paren
r_return
id|page
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
)brace
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
r_return
l_int|NULL
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|submit_page
id|submit_page
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
id|bh_arr
(braket
)braket
comma
r_int
id|cnt
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
suffix:semicolon
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
r_if
c_cond
(paren
id|cnt
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|bh_arr
(braket
id|i
)braket
suffix:semicolon
id|mark_buffer_async_write
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
id|clear_buffer_dirty
c_func
(paren
id|bh
)paren
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
id|submit_bh
c_func
(paren
id|WRITE
comma
id|bh_arr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
id|end_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|map_page
id|map_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
id|page_buf_bmap_t
op_star
id|maps
comma
r_struct
id|buffer_head
op_star
id|bh_arr
(braket
)braket
comma
r_int
id|startio
comma
r_int
id|all_bh
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|head
suffix:semicolon
id|page_buf_bmap_t
op_star
id|mp
op_assign
id|maps
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|end
comma
id|offset
comma
id|end_index
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|index
op_assign
l_int|0
suffix:semicolon
r_int
id|bbits
op_assign
id|inode-&gt;i_blkbits
suffix:semicolon
id|end_index
op_assign
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OL
id|end_index
)paren
(brace
id|end
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_else
(brace
id|end
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|bh
op_assign
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
id|offset
op_assign
id|i
op_lshift
id|bbits
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|buffer_mapped
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_delay
c_func
(paren
id|bh
)paren
op_logical_and
id|all_bh
)paren
(brace
r_if
c_cond
(paren
id|startio
op_logical_and
(paren
id|offset
OL
id|end
)paren
)paren
(brace
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh_arr
(braket
id|index
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|tmp
op_assign
id|match_offset_to_mapping
c_func
(paren
id|page
comma
id|mp
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_continue
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
(paren
id|tmp-&gt;pbm_flags
op_amp
id|PBMF_HOLE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
(paren
id|tmp-&gt;pbm_flags
op_amp
id|PBMF_DELAY
)paren
)paren
suffix:semicolon
id|map_buffer_at_offset
c_func
(paren
id|page
comma
id|bh
comma
id|offset
comma
id|bbits
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startio
op_logical_and
(paren
id|offset
OL
id|end
)paren
)paren
(brace
id|bh_arr
(braket
id|index
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|i
op_increment
comma
(paren
id|bh
op_assign
id|bh-&gt;b_this_page
)paren
op_ne
id|head
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate &amp; map buffers for page given the extent map. Write it out.&n; * except for the original page of a writepage, this is called on&n; * delalloc pages only, for the original page it is possible that&n; * the page has no mapping at all.&n; */
id|STATIC
r_void
DECL|function|convert_page
id|convert_page
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
id|page_buf_bmap_t
op_star
id|maps
comma
r_int
id|startio
comma
r_int
id|all_bh
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh_arr
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
r_int
id|cnt
suffix:semicolon
id|cnt
op_assign
id|map_page
c_func
(paren
id|inode
comma
id|page
comma
id|maps
comma
id|bh_arr
comma
id|startio
comma
id|all_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startio
)paren
(brace
id|submit_page
c_func
(paren
id|page
comma
id|bh_arr
comma
id|cnt
)paren
suffix:semicolon
)brace
r_else
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert &amp; write out a cluster of pages in the same extent as defined&n; * by mp and following the start page.&n; */
id|STATIC
r_void
DECL|function|cluster_write
id|cluster_write
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|tindex
comma
id|page_buf_bmap_t
op_star
id|mp
comma
r_int
id|startio
comma
r_int
id|all_bh
)paren
(brace
r_int
r_int
id|tlast
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|tlast
op_assign
(paren
id|mp-&gt;pbm_offset
op_plus
id|mp-&gt;pbm_bsize
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|tindex
OL
id|tlast
suffix:semicolon
id|tindex
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|probe_page
c_func
(paren
id|inode
comma
id|tindex
)paren
)paren
)paren
r_break
suffix:semicolon
id|convert_page
c_func
(paren
id|inode
comma
id|page
comma
id|mp
comma
id|startio
comma
id|all_bh
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Calling this without allocate_space set means we are being asked to&n; * flush a dirty buffer head. When called with async_write set then we&n; * are coming from writepage. A writepage call with allocate_space set&n; * means we are being asked to write out all of the page which is before&n; * EOF and therefore need to allocate space for unmapped portions of the&n; * page.&n; */
id|STATIC
r_int
DECL|function|delalloc_convert
id|delalloc_convert
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
multiline_comment|/* inode containing page */
r_struct
id|page
op_star
id|page
comma
multiline_comment|/* page to convert - locked */
r_int
id|startio
comma
multiline_comment|/* start io on the page */
r_int
id|allocate_space
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|head
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh_arr
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
id|page_buf_bmap_t
op_star
id|mp
comma
id|map
suffix:semicolon
r_int
id|i
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
r_int
id|len
comma
id|err
suffix:semicolon
r_int
r_int
id|p_offset
op_assign
l_int|0
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
id|loff_t
id|end_offset
suffix:semicolon
id|offset
op_assign
(paren
id|loff_t
)paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|end_offset
op_assign
id|offset
op_plus
id|PAGE_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|end_offset
OG
id|inode-&gt;i_size
)paren
id|end_offset
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|bh
op_assign
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
id|mp
op_assign
l_int|NULL
suffix:semicolon
id|len
op_assign
id|bh-&gt;b_size
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|startio
)paren
(brace
r_goto
id|next_bh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp
)paren
(brace
id|mp
op_assign
id|match_offset_to_mapping
c_func
(paren
id|page
comma
op_amp
id|map
comma
id|p_offset
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer_delay
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
(brace
id|err
op_assign
id|map_blocks
c_func
(paren
id|inode
comma
id|offset
comma
id|len
comma
op_amp
id|map
comma
id|PBF_WRITE
op_or
id|PBF_FILE_ALLOCATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
id|mp
op_assign
id|match_offset_to_mapping
c_func
(paren
id|page
comma
op_amp
id|map
comma
id|p_offset
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp
)paren
(brace
id|map_buffer_at_offset
c_func
(paren
id|page
comma
id|bh
comma
id|p_offset
comma
id|inode-&gt;i_blkbits
comma
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startio
)paren
(brace
id|bh_arr
(braket
id|cnt
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
op_logical_and
id|allocate_space
)paren
(brace
r_int
id|size
suffix:semicolon
multiline_comment|/* Getting here implies an unmapped buffer was found,&n;&t;&t;&t; * and we are in a path where we need to write the&n;&t;&t;&t; * whole page out.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|mp
)paren
(brace
id|size
op_assign
id|probe_unmapped_cluster
c_func
(paren
id|inode
comma
id|page
comma
id|bh
comma
id|head
)paren
suffix:semicolon
id|err
op_assign
id|map_blocks
c_func
(paren
id|inode
comma
id|offset
comma
id|size
comma
op_amp
id|map
comma
id|PBF_WRITE
op_or
id|PBF_DIRECT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
id|mp
op_assign
id|match_offset_to_mapping
c_func
(paren
id|page
comma
op_amp
id|map
comma
id|p_offset
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mp
)paren
(brace
id|map_buffer_at_offset
c_func
(paren
id|page
comma
id|bh
comma
id|p_offset
comma
id|inode-&gt;i_blkbits
comma
id|mp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startio
)paren
(brace
id|bh_arr
(braket
id|cnt
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_else
(brace
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|startio
op_logical_and
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
id|buffer_dirty
c_func
(paren
id|bh
)paren
op_logical_or
id|allocate_space
)paren
(brace
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh_arr
(braket
id|cnt
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
)brace
id|next_bh
suffix:colon
id|offset
op_add_assign
id|len
suffix:semicolon
id|p_offset
op_add_assign
id|len
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|end_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startio
)paren
id|submit_page
c_func
(paren
id|page
comma
id|bh_arr
comma
id|cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mp
)paren
id|cluster_write
c_func
(paren
id|inode
comma
id|page-&gt;index
op_plus
l_int|1
comma
id|mp
comma
id|startio
comma
id|allocate_space
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
id|unlock_buffer
c_func
(paren
id|bh_arr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_get_block_core
id|linvfs_get_block_core
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_int
id|blocks
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
comma
r_int
id|direct
comma
id|page_buf_flags_t
id|flags
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|page_buf_bmap_t
id|pbmap
suffix:semicolon
r_int
id|retpbbm
op_assign
l_int|1
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ssize_t
id|size
suffix:semicolon
id|loff_t
id|offset
op_assign
(paren
id|loff_t
)paren
id|iblock
op_lshift
id|inode-&gt;i_blkbits
suffix:semicolon
r_if
c_cond
(paren
id|blocks
)paren
(brace
id|size
op_assign
id|blocks
op_lshift
id|inode-&gt;i_blkbits
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* If we are doing writes at the end of the file,&n;&t;&t; * allocate in chunks&n;&t;&t; */
r_if
c_cond
(paren
id|create
op_logical_and
(paren
id|offset
op_ge
id|inode-&gt;i_size
)paren
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|PBF_SYNC
)paren
)paren
id|size
op_assign
l_int|1
op_lshift
id|XFS_WRITE_IO_LOG
suffix:semicolon
r_else
id|size
op_assign
l_int|1
op_lshift
id|inode-&gt;i_blkbits
suffix:semicolon
)brace
id|VOP_BMAP
c_func
(paren
id|vp
comma
id|offset
comma
id|size
comma
id|create
ques
c_cond
id|flags
suffix:colon
id|PBF_READ
comma
l_int|NULL
comma
(paren
r_struct
id|page_buf_bmap_s
op_star
)paren
op_amp
id|pbmap
comma
op_amp
id|retpbbm
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|error
suffix:semicolon
r_if
c_cond
(paren
id|retpbbm
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pbmap.pbm_bn
op_ne
id|PAGE_BUF_DADDR_NULL
)paren
(brace
id|page_buf_daddr_t
id|bn
suffix:semicolon
id|loff_t
id|delta
suffix:semicolon
id|delta
op_assign
id|offset
op_minus
id|pbmap.pbm_offset
suffix:semicolon
id|delta
op_rshift_assign
id|inode-&gt;i_blkbits
suffix:semicolon
id|bn
op_assign
id|pbmap.pbm_bn
op_rshift
(paren
id|inode-&gt;i_blkbits
op_minus
l_int|9
)paren
suffix:semicolon
id|bn
op_add_assign
id|delta
suffix:semicolon
id|bh_result-&gt;b_blocknr
op_assign
id|bn
suffix:semicolon
id|bh_result-&gt;b_bdev
op_assign
id|pbmap.pbm_target-&gt;pbr_bdev
suffix:semicolon
id|set_buffer_mapped
c_func
(paren
id|bh_result
)paren
suffix:semicolon
)brace
multiline_comment|/* If we previously allocated a block out beyond eof and&n;&t; * we are now coming back to use it then we will need to&n;&t; * flag it as new even if it has a disk address.&n;&t; */
r_if
c_cond
(paren
id|create
op_logical_and
(paren
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh_result
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh_result
)paren
)paren
op_logical_or
(paren
id|offset
op_ge
id|inode-&gt;i_size
)paren
)paren
)paren
(brace
id|set_buffer_new
c_func
(paren
id|bh_result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pbmap.pbm_flags
op_amp
id|PBMF_DELAY
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|direct
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
id|create
)paren
(brace
id|set_buffer_mapped
c_func
(paren
id|bh_result
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh_result
)paren
suffix:semicolon
)brace
id|bh_result-&gt;b_bdev
op_assign
id|pbmap.pbm_target-&gt;pbr_bdev
suffix:semicolon
id|set_buffer_delay
c_func
(paren
id|bh_result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|blocks
)paren
(brace
id|size
op_assign
(paren
id|pbmap.pbm_bsize
op_minus
id|pbmap.pbm_delta
)paren
suffix:semicolon
id|bh_result-&gt;b_size
op_assign
id|min_t
c_func
(paren
id|ssize_t
comma
id|size
comma
id|blocks
op_lshift
id|inode-&gt;i_blkbits
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|linvfs_get_block
id|linvfs_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_return
id|linvfs_get_block_core
c_func
(paren
id|inode
comma
id|iblock
comma
l_int|0
comma
id|bh_result
comma
id|create
comma
l_int|0
comma
id|PBF_WRITE
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_get_block_sync
id|linvfs_get_block_sync
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_return
id|linvfs_get_block_core
c_func
(paren
id|inode
comma
id|iblock
comma
l_int|0
comma
id|bh_result
comma
id|create
comma
l_int|0
comma
id|PBF_SYNC
op_or
id|PBF_WRITE
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_get_blocks_direct
id|linvfs_get_blocks_direct
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_int
r_int
id|max_blocks
comma
r_struct
id|buffer_head
op_star
id|bh_result
comma
r_int
id|create
)paren
(brace
r_return
id|linvfs_get_block_core
c_func
(paren
id|inode
comma
id|iblock
comma
id|max_blocks
comma
id|bh_result
comma
id|create
comma
l_int|1
comma
id|PBF_WRITE
op_or
id|PBF_DIRECT
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_direct_IO
id|linvfs_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
id|loff_t
id|offset
comma
r_int
r_int
id|nr_segs
)paren
(brace
r_return
id|generic_direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|iov
comma
id|offset
comma
id|nr_segs
comma
id|linvfs_get_blocks_direct
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_bmap
id|linvfs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
id|block
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|mapping-&gt;host
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* block&t;     - Linux disk blocks    512b */
multiline_comment|/* bmap input offset - bytes&t;&t;      1b */
multiline_comment|/* bmap output bn    - XFS BBs&t;&t;    512b */
multiline_comment|/* bmap output delta - bytes&t;&t;      1b */
id|vn_trace_entry
c_func
(paren
id|vp
comma
l_string|&quot;linvfs_bmap&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|VOP_RWLOCK
c_func
(paren
id|vp
comma
id|VRWLOCK_READ
)paren
suffix:semicolon
id|VOP_FLUSH_PAGES
c_func
(paren
id|vp
comma
(paren
id|xfs_off_t
)paren
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
comma
id|FI_REMAPF
comma
id|error
)paren
suffix:semicolon
id|VOP_RWUNLOCK
c_func
(paren
id|vp
comma
id|VRWLOCK_READ
)paren
suffix:semicolon
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|linvfs_get_block
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_readpage
id|linvfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|unused
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|mpage_readpage
c_func
(paren
id|page
comma
id|linvfs_get_block
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_readpages
id|linvfs_readpages
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
)paren
(brace
r_return
id|mpage_readpages
c_func
(paren
id|mapping
comma
id|pages
comma
id|nr_pages
comma
id|linvfs_get_block
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|count_page_state
id|count_page_state
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
op_star
id|nr_delalloc
comma
r_int
op_star
id|nr_unmapped
)paren
(brace
op_star
id|nr_delalloc
op_assign
op_star
id|nr_unmapped
op_assign
l_int|0
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
id|bh
comma
op_star
id|head
suffix:semicolon
id|bh
op_assign
id|head
op_assign
id|page_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
(paren
op_star
id|nr_unmapped
)paren
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_delay
c_func
(paren
id|bh
)paren
)paren
r_continue
suffix:semicolon
(paren
op_star
id|nr_delalloc
)paren
op_increment
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
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_writepage
id|linvfs_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|need_trans
suffix:semicolon
r_int
id|nr_delalloc
comma
id|nr_unmapped
suffix:semicolon
r_if
c_cond
(paren
id|count_page_state
c_func
(paren
id|page
comma
op_amp
id|nr_delalloc
comma
op_amp
id|nr_unmapped
)paren
)paren
(brace
id|need_trans
op_assign
id|nr_delalloc
op_plus
id|nr_unmapped
suffix:semicolon
)brace
r_else
(brace
id|need_trans
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|current-&gt;flags
op_amp
(paren
id|PF_FSTRANS
)paren
)paren
op_logical_and
id|need_trans
)paren
r_goto
id|out_fail
suffix:semicolon
id|error
op_assign
id|write_full_page
c_func
(paren
id|page
comma
id|nr_delalloc
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
id|out_fail
suffix:colon
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
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_prepare_write
id|linvfs_prepare_write
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
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
)paren
(brace
r_if
c_cond
(paren
id|file
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
)paren
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|linvfs_get_block_sync
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|linvfs_get_block
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This gets a page into cleanable state - page locked on entry&n; * kept locked on exit. If the page is marked dirty we should&n; * not come this way.&n; */
id|STATIC
r_int
DECL|function|linvfs_release_page
id|linvfs_release_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|gfp_mask
)paren
(brace
r_int
id|need_trans
suffix:semicolon
r_int
id|nr_delalloc
comma
id|nr_unmapped
suffix:semicolon
r_if
c_cond
(paren
id|count_page_state
c_func
(paren
id|page
comma
op_amp
id|nr_delalloc
comma
op_amp
id|nr_unmapped
)paren
)paren
(brace
id|need_trans
op_assign
id|nr_delalloc
suffix:semicolon
)brace
r_else
(brace
id|need_trans
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|need_trans
op_eq
l_int|0
)paren
(brace
r_return
id|try_to_free_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_FS
)paren
(brace
r_if
c_cond
(paren
id|release_page
c_func
(paren
id|page
)paren
op_eq
l_int|0
)paren
r_return
id|try_to_free_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|linvfs_aops
r_struct
id|address_space_operations
id|linvfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|linvfs_readpage
comma
dot
id|readpages
op_assign
id|linvfs_readpages
comma
dot
id|writepage
op_assign
id|linvfs_writepage
comma
dot
id|sync_page
op_assign
id|block_sync_page
comma
dot
id|releasepage
op_assign
id|linvfs_release_page
comma
dot
id|prepare_write
op_assign
id|linvfs_prepare_write
comma
dot
id|commit_write
op_assign
id|generic_commit_write
comma
dot
id|bmap
op_assign
id|linvfs_bmap
comma
dot
id|direct_IO
op_assign
id|linvfs_direct_IO
comma
)brace
suffix:semicolon
eof
