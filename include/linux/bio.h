multiline_comment|/*&n; * 2.5 block I/O model&n; *&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; */
macro_line|#ifndef __LINUX_BIO_H
DECL|macro|__LINUX_BIO_H
mdefine_line|#define __LINUX_BIO_H
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
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
DECL|macro|BIO_MAX_PAGES
mdefine_line|#define BIO_MAX_PAGES&t;&t;(256)
DECL|macro|BIO_MAX_SIZE
mdefine_line|#define BIO_MAX_SIZE&t;&t;(BIO_MAX_PAGES &lt;&lt; PAGE_CACHE_SHIFT)
DECL|macro|BIO_MAX_SECTORS
mdefine_line|#define BIO_MAX_SECTORS&t;&t;(BIO_MAX_SIZE &gt;&gt; 9)
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
r_struct
id|bio
suffix:semicolon
DECL|typedef|bio_end_io_t
r_typedef
r_int
(paren
id|bio_end_io_t
)paren
(paren
r_struct
id|bio
op_star
comma
r_int
r_int
comma
r_int
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
DECL|member|bi_bdev
r_struct
id|block_device
op_star
id|bi_bdev
suffix:semicolon
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
DECL|member|bi_max_vecs
r_int
r_int
id|bi_max_vecs
suffix:semicolon
multiline_comment|/* max bvl_vecs we can hold */
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
DECL|macro|BIO_BOUNCED
mdefine_line|#define BIO_BOUNCED&t;5&t;/* bio is a bounce bio */
DECL|macro|bio_flagged
mdefine_line|#define bio_flagged(bio, flag)&t;((bio)-&gt;bi_flags &amp; (1 &lt;&lt; (flag)))
multiline_comment|/*&n; * top 4 bits of bio flags indicate the pool this bio came from&n; */
DECL|macro|BIO_POOL_BITS
mdefine_line|#define BIO_POOL_BITS&t;&t;(4)
DECL|macro|BIO_POOL_OFFSET
mdefine_line|#define BIO_POOL_OFFSET&t;&t;(BITS_PER_LONG - BIO_POOL_BITS)
DECL|macro|BIO_POOL_MASK
mdefine_line|#define BIO_POOL_MASK&t;&t;(1UL &lt;&lt; BIO_POOL_OFFSET)
DECL|macro|BIO_POOL_IDX
mdefine_line|#define BIO_POOL_IDX(bio)&t;((bio)-&gt;bi_flags &gt;&gt; BIO_POOL_OFFSET)&t;
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
mdefine_line|#define bio_barrier(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_RW_BARRIER))
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
mdefine_line|#define bio_io_error(bio, bytes) bio_endio((bio), (bytes), -EIO)
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
r_int
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
id|bio_add_page
c_func
(paren
r_struct
id|bio
op_star
comma
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|bio_get_nr_vecs
c_func
(paren
r_struct
id|block_device
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
multiline_comment|/*&n; * remember to add offset! and never ever reenable interrupts between a&n; * bio_kmap_irq and bio_kunmap_irq!!&n; *&n; * This function MUST be inlined - it plays with the CPU interrupt flags.&n; * Hence the `extern inline&squot;.&n; */
DECL|function|bio_kmap_irq
r_extern
r_inline
r_char
op_star
id|bio_kmap_irq
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/*&n;&t; * might not be a highmem page, but the preempt/irq count&n;&t; * balancing is a lot nicer this way&n;&t; */
id|local_save_flags
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|kmap_atomic
c_func
(paren
id|bio_page
c_func
(paren
id|bio
)paren
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|addr
op_plus
id|bio_offset
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
DECL|function|bio_kunmap_irq
r_extern
r_inline
r_void
id|bio_kunmap_irq
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|ptr
op_assign
(paren
r_int
r_int
)paren
id|buffer
op_amp
id|PAGE_MASK
suffix:semicolon
id|kunmap_atomic
c_func
(paren
(paren
r_void
op_star
)paren
id|ptr
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|bio_kmap_irq
mdefine_line|#define bio_kmap_irq(bio, flags)&t;(bio_data(bio))
DECL|macro|bio_kunmap_irq
mdefine_line|#define bio_kunmap_irq(buf, flags)&t;do { *(flags) = 0; } while (0)
macro_line|#endif
macro_line|#endif /* __LINUX_BIO_H */
eof
