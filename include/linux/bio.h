multiline_comment|/*&n; * 2.5 block I/O model&n; *&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; */
macro_line|#ifndef __LINUX_BIO_H
DECL|macro|__LINUX_BIO_H
mdefine_line|#define __LINUX_BIO_H
multiline_comment|/* Platforms may set this to teach the BIO layer about IOMMU hardware. */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef BIO_VMERGE_BOUNDARY
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;0
macro_line|#endif
DECL|macro|BIO_DEBUG
mdefine_line|#define BIO_DEBUG
macro_line|#ifdef BIO_DEBUG
DECL|macro|BIO_BUG_ON
mdefine_line|#define BIO_BUG_ON&t;BUG_ON
macro_line|#else
DECL|macro|BIO_BUG_ON
mdefine_line|#define BIO_BUG_ON
macro_line|#endif
DECL|macro|BIO_MAX_SECTORS
mdefine_line|#define BIO_MAX_SECTORS&t;128
DECL|macro|BIO_MAX_SIZE
mdefine_line|#define BIO_MAX_SIZE&t;(BIO_MAX_SECTORS &lt;&lt; 9)
multiline_comment|/*&n; * was unsigned short, but we might as well be ready for &gt; 64kB I/O pages&n; */
DECL|struct|bio_vec
r_struct
id|bio_vec
(brace
DECL|member|bv_page
r_struct
id|page
op_star
id|bv_page
suffix:semicolon
DECL|member|bv_len
r_int
r_int
id|bv_len
suffix:semicolon
DECL|member|bv_offset
r_int
r_int
id|bv_offset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * weee, c forward decl...&n; */
r_struct
id|bio
suffix:semicolon
DECL|typedef|bio_end_io_t
r_typedef
r_void
(paren
id|bio_end_io_t
)paren
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
DECL|typedef|bio_destructor_t
r_typedef
r_void
(paren
id|bio_destructor_t
)paren
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * main unit of I/O for the block layer and lower layers (ie drivers and&n; * stacking drivers)&n; */
DECL|struct|bio
r_struct
id|bio
(brace
DECL|member|bi_sector
id|sector_t
id|bi_sector
suffix:semicolon
DECL|member|bi_next
r_struct
id|bio
op_star
id|bi_next
suffix:semicolon
multiline_comment|/* request queue link */
DECL|member|bi_dev
id|kdev_t
id|bi_dev
suffix:semicolon
multiline_comment|/* will be block device */
DECL|member|bi_flags
r_int
r_int
id|bi_flags
suffix:semicolon
multiline_comment|/* status, command, etc */
DECL|member|bi_rw
r_int
r_int
id|bi_rw
suffix:semicolon
multiline_comment|/* bottom bits READ/WRITE,&n;&t;&t;&t;&t;&t;&t; * top bits priority&n;&t;&t;&t;&t;&t;&t; */
DECL|member|bi_vcnt
r_int
r_int
id|bi_vcnt
suffix:semicolon
multiline_comment|/* how many bio_vec&squot;s */
DECL|member|bi_idx
r_int
r_int
id|bi_idx
suffix:semicolon
multiline_comment|/* current index into bvl_vec */
multiline_comment|/* Number of segments in this BIO after&n;&t; * physical address coalescing is performed.&n;&t; */
DECL|member|bi_phys_segments
r_int
r_int
id|bi_phys_segments
suffix:semicolon
multiline_comment|/* Number of segments after physical and DMA remapping&n;&t; * hardware coalescing is performed.&n;&t; */
DECL|member|bi_hw_segments
r_int
r_int
id|bi_hw_segments
suffix:semicolon
DECL|member|bi_size
r_int
r_int
id|bi_size
suffix:semicolon
multiline_comment|/* residual I/O count */
DECL|member|bi_max
r_int
r_int
id|bi_max
suffix:semicolon
multiline_comment|/* max bvl_vecs we can hold,&n;&t;&t;&t;&t;&t;&t;   used as index into pool */
DECL|member|bi_io_vec
r_struct
id|bio_vec
op_star
id|bi_io_vec
suffix:semicolon
multiline_comment|/* the actual vec list */
DECL|member|bi_end_io
id|bio_end_io_t
op_star
id|bi_end_io
suffix:semicolon
DECL|member|bi_cnt
id|atomic_t
id|bi_cnt
suffix:semicolon
multiline_comment|/* pin count */
DECL|member|bi_private
r_void
op_star
id|bi_private
suffix:semicolon
DECL|member|bi_destructor
id|bio_destructor_t
op_star
id|bi_destructor
suffix:semicolon
multiline_comment|/* destructor */
)brace
suffix:semicolon
multiline_comment|/*&n; * bio flags&n; */
DECL|macro|BIO_UPTODATE
mdefine_line|#define BIO_UPTODATE&t;0&t;/* ok after I/O completion */
DECL|macro|BIO_RW_BLOCK
mdefine_line|#define BIO_RW_BLOCK&t;1&t;/* RW_AHEAD set, and read/write would block */
DECL|macro|BIO_EOF
mdefine_line|#define BIO_EOF&t;&t;2&t;/* out-out-bounds error */
DECL|macro|BIO_SEG_VALID
mdefine_line|#define BIO_SEG_VALID&t;3&t;/* nr_hw_seg valid */
DECL|macro|BIO_CLONED
mdefine_line|#define BIO_CLONED&t;4&t;/* doesn&squot;t own data */
multiline_comment|/*&n; * bio bi_rw flags&n; *&n; * bit 0 -- read (not set) or write (set)&n; * bit 1 -- rw-ahead when set&n; * bit 2 -- barrier&n; */
DECL|macro|BIO_RW
mdefine_line|#define BIO_RW&t;&t;0
DECL|macro|BIO_RW_AHEAD
mdefine_line|#define BIO_RW_AHEAD&t;1
DECL|macro|BIO_RW_BARRIER
mdefine_line|#define BIO_RW_BARRIER&t;2
multiline_comment|/*&n; * various member access, note that bio_data should of course not be used&n; * on highmem page vectors&n; */
DECL|macro|bio_iovec_idx
mdefine_line|#define bio_iovec_idx(bio, idx)&t;(&amp;((bio)-&gt;bi_io_vec[(idx)]))
DECL|macro|bio_iovec
mdefine_line|#define bio_iovec(bio)&t;&t;bio_iovec_idx((bio), (bio)-&gt;bi_idx)
DECL|macro|bio_page
mdefine_line|#define bio_page(bio)&t;&t;bio_iovec((bio))-&gt;bv_page
DECL|macro|bio_offset
mdefine_line|#define bio_offset(bio)&t;&t;bio_iovec((bio))-&gt;bv_offset
DECL|macro|bio_sectors
mdefine_line|#define bio_sectors(bio)&t;((bio)-&gt;bi_size &gt;&gt; 9)
DECL|macro|bio_data
mdefine_line|#define bio_data(bio)&t;&t;(page_address(bio_page((bio))) + bio_offset((bio)))
DECL|macro|bio_barrier
mdefine_line|#define bio_barrier(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_BARRIER))
multiline_comment|/*&n; * will die&n; */
DECL|macro|bio_to_phys
mdefine_line|#define bio_to_phys(bio)&t;(page_to_phys(bio_page((bio))) + (unsigned long) bio_offset((bio)))
DECL|macro|bvec_to_phys
mdefine_line|#define bvec_to_phys(bv)&t;(page_to_phys((bv)-&gt;bv_page) + (unsigned long) (bv)-&gt;bv_offset)
multiline_comment|/*&n; * queues that have highmem support enabled may still need to revert to&n; * PIO transfers occasionally and thus map high pages temporarily. For&n; * permanent PIO fall back, user is probably better off disabling highmem&n; * I/O completely on that queue (see ide-dma for example)&n; */
DECL|macro|__bio_kmap
mdefine_line|#define __bio_kmap(bio, idx) (kmap(bio_iovec_idx((bio), (idx))-&gt;bv_page) + bio_iovec_idx((bio), (idx))-&gt;bv_offset)
DECL|macro|bio_kmap
mdefine_line|#define bio_kmap(bio)&t;__bio_kmap((bio), (bio)-&gt;bi_idx)
DECL|macro|__bio_kunmap
mdefine_line|#define __bio_kunmap(bio, idx)&t;kunmap(bio_iovec_idx((bio), (idx))-&gt;bv_page)
DECL|macro|bio_kunmap
mdefine_line|#define bio_kunmap(bio)&t;&t;__bio_kunmap((bio), (bio)-&gt;bi_idx)
multiline_comment|/*&n; * merge helpers etc&n; */
DECL|macro|__BVEC_END
mdefine_line|#define __BVEC_END(bio)&t;&t;bio_iovec_idx((bio), (bio)-&gt;bi_vcnt - 1)
DECL|macro|__BVEC_START
mdefine_line|#define __BVEC_START(bio)&t;bio_iovec_idx((bio), 0)
DECL|macro|BIOVEC_PHYS_MERGEABLE
mdefine_line|#define BIOVEC_PHYS_MERGEABLE(vec1, vec2)&t;&bslash;&n;&t;((bvec_to_phys((vec1)) + (vec1)-&gt;bv_len) == bvec_to_phys((vec2)))
DECL|macro|BIOVEC_VIRT_MERGEABLE
mdefine_line|#define BIOVEC_VIRT_MERGEABLE(vec1, vec2)&t;&bslash;&n;&t;((((bvec_to_phys((vec1)) + (vec1)-&gt;bv_len) | bvec_to_phys((vec2))) &amp; (BIO_VMERGE_BOUNDARY - 1)) == 0)
DECL|macro|__BIO_SEG_BOUNDARY
mdefine_line|#define __BIO_SEG_BOUNDARY(addr1, addr2, mask) &bslash;&n;&t;(((addr1) | (mask)) == (((addr2) - 1) | (mask)))
DECL|macro|BIOVEC_SEG_BOUNDARY
mdefine_line|#define BIOVEC_SEG_BOUNDARY(q, b1, b2) &bslash;&n;&t;__BIO_SEG_BOUNDARY(bvec_to_phys((b1)), bvec_to_phys((b2)) + (b2)-&gt;bv_len, (q)-&gt;seg_boundary_mask)
DECL|macro|BIO_SEG_BOUNDARY
mdefine_line|#define BIO_SEG_BOUNDARY(q, b1, b2) &bslash;&n;&t;BIOVEC_SEG_BOUNDARY((q), __BVEC_END((b1)), __BVEC_START((b2)))
DECL|macro|bio_io_error
mdefine_line|#define bio_io_error(bio) bio_endio((bio), 0)
multiline_comment|/*&n; * drivers should not use the __ version unless they _really_ want to&n; * run through the entire bio and not just pending pieces&n; */
DECL|macro|__bio_for_each_segment
mdefine_line|#define __bio_for_each_segment(bvl, bio, i, start_idx)&t;&t;&t;&bslash;&n;&t;for (bvl = bio_iovec_idx((bio), (start_idx)), i = (start_idx);&t;&bslash;&n;&t;     i &lt; (bio)-&gt;bi_vcnt;&t;&t;&t;&t;&t;&bslash;&n;&t;     bvl++, i++)
DECL|macro|bio_for_each_segment
mdefine_line|#define bio_for_each_segment(bvl, bio, i)&t;&t;&t;&t;&bslash;&n;&t;__bio_for_each_segment(bvl, bio, i, (bio)-&gt;bi_idx)
multiline_comment|/*&n; * get a reference to a bio, so it won&squot;t disappear. the intended use is&n; * something like:&n; *&n; * bio_get(bio);&n; * submit_bio(rw, bio);&n; * if (bio-&gt;bi_flags ...)&n; *&t;do_something&n; * bio_put(bio);&n; *&n; * without the bio_get(), it could potentially complete I/O before submit_bio&n; * returns. and then bio would be freed memory when if (bio-&gt;bi_flags ...)&n; * runs&n; */
DECL|macro|bio_get
mdefine_line|#define bio_get(bio)&t;atomic_inc(&amp;(bio)-&gt;bi_cnt)
r_extern
r_struct
id|bio
op_star
id|bio_alloc
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bio_put
c_func
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bio_endio
c_func
(paren
r_struct
id|bio
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|request_queue
suffix:semicolon
r_extern
r_inline
r_int
id|bio_phys_segments
c_func
(paren
r_struct
id|request_queue
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|bio_hw_segments
c_func
(paren
r_struct
id|request_queue
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|__bio_clone
c_func
(paren
r_struct
id|bio
op_star
comma
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|bio
op_star
id|bio_clone
c_func
(paren
r_struct
id|bio
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|bio
op_star
id|bio_copy
c_func
(paren
r_struct
id|bio
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|bio_init
c_func
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_int
id|bio_ioctl
c_func
(paren
id|kdev_t
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_BIO_H */
eof
