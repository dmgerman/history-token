multiline_comment|/*&n; * 2.5 block I/O model&n; *&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; */
macro_line|#ifndef __LINUX_BIO_H
DECL|macro|__LINUX_BIO_H
mdefine_line|#define __LINUX_BIO_H
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
multiline_comment|/* Platforms may set this to teach the BIO layer about IOMMU hardware. */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if defined(BIO_VMERGE_MAX_SIZE) &amp;&amp; defined(BIO_VMERGE_BOUNDARY)
DECL|macro|BIOVEC_VIRT_START_SIZE
mdefine_line|#define BIOVEC_VIRT_START_SIZE(x) (bvec_to_phys(x) &amp; (BIO_VMERGE_BOUNDARY - 1))
DECL|macro|BIOVEC_VIRT_OVERSIZE
mdefine_line|#define BIOVEC_VIRT_OVERSIZE(x)&t;((x) &gt; BIO_VMERGE_MAX_SIZE)
macro_line|#else
DECL|macro|BIOVEC_VIRT_START_SIZE
mdefine_line|#define BIOVEC_VIRT_START_SIZE(x)&t;0
DECL|macro|BIOVEC_VIRT_OVERSIZE
mdefine_line|#define BIOVEC_VIRT_OVERSIZE(x)&t;&t;0
macro_line|#endif
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
multiline_comment|/*&n;&t; * To keep track of the max hw size, we account for the&n;&t; * sizes of the first and last virtually mergeable segments&n;&t; * in this bio&n;&t; */
DECL|member|bi_hw_front_size
r_int
r_int
id|bi_hw_front_size
suffix:semicolon
DECL|member|bi_hw_back_size
r_int
r_int
id|bi_hw_back_size
suffix:semicolon
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
DECL|macro|BIO_USER_MAPPED
mdefine_line|#define BIO_USER_MAPPED 6&t;/* contains user pages */
DECL|macro|BIO_EOPNOTSUPP
mdefine_line|#define BIO_EOPNOTSUPP&t;7&t;/* not supported */
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
multiline_comment|/*&n; * bio bi_rw flags&n; *&n; * bit 0 -- read (not set) or write (set)&n; * bit 1 -- rw-ahead when set&n; * bit 2 -- barrier&n; * bit 3 -- fail fast, don&squot;t want low level driver retries&n; * bit 4 -- synchronous I/O hint: the block layer will unplug immediately&n; */
DECL|macro|BIO_RW
mdefine_line|#define BIO_RW&t;&t;0
DECL|macro|BIO_RW_AHEAD
mdefine_line|#define BIO_RW_AHEAD&t;1
DECL|macro|BIO_RW_BARRIER
mdefine_line|#define BIO_RW_BARRIER&t;2
DECL|macro|BIO_RW_FAILFAST
mdefine_line|#define BIO_RW_FAILFAST&t;3
DECL|macro|BIO_RW_SYNC
mdefine_line|#define BIO_RW_SYNC&t;4
multiline_comment|/*&n; * various member access, note that bio_data should of course not be used&n; * on highmem page vectors&n; */
DECL|macro|bio_iovec_idx
mdefine_line|#define bio_iovec_idx(bio, idx)&t;(&amp;((bio)-&gt;bi_io_vec[(idx)]))
DECL|macro|bio_iovec
mdefine_line|#define bio_iovec(bio)&t;&t;bio_iovec_idx((bio), (bio)-&gt;bi_idx)
DECL|macro|bio_page
mdefine_line|#define bio_page(bio)&t;&t;bio_iovec((bio))-&gt;bv_page
DECL|macro|bio_offset
mdefine_line|#define bio_offset(bio)&t;&t;bio_iovec((bio))-&gt;bv_offset
DECL|macro|bio_segments
mdefine_line|#define bio_segments(bio)&t;((bio)-&gt;bi_vcnt - (bio)-&gt;bi_idx)
DECL|macro|bio_sectors
mdefine_line|#define bio_sectors(bio)&t;((bio)-&gt;bi_size &gt;&gt; 9)
DECL|macro|bio_cur_sectors
mdefine_line|#define bio_cur_sectors(bio)&t;(bio_iovec(bio)-&gt;bv_len &gt;&gt; 9)
DECL|macro|bio_data
mdefine_line|#define bio_data(bio)&t;&t;(page_address(bio_page((bio))) + bio_offset((bio)))
DECL|macro|bio_barrier
mdefine_line|#define bio_barrier(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_RW_BARRIER))
DECL|macro|bio_sync
mdefine_line|#define bio_sync(bio)&t;&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_RW_SYNC))
DECL|macro|bio_failfast
mdefine_line|#define bio_failfast(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_RW_FAILFAST))
DECL|macro|bio_rw_ahead
mdefine_line|#define bio_rw_ahead(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_RW_AHEAD))
multiline_comment|/*&n; * will die&n; */
DECL|macro|bio_to_phys
mdefine_line|#define bio_to_phys(bio)&t;(page_to_phys(bio_page((bio))) + (unsigned long) bio_offset((bio)))
DECL|macro|bvec_to_phys
mdefine_line|#define bvec_to_phys(bv)&t;(page_to_phys((bv)-&gt;bv_page) + (unsigned long) (bv)-&gt;bv_offset)
multiline_comment|/*&n; * queues that have highmem support enabled may still need to revert to&n; * PIO transfers occasionally and thus map high pages temporarily. For&n; * permanent PIO fall back, user is probably better off disabling highmem&n; * I/O completely on that queue (see ide-dma for example)&n; */
DECL|macro|__bio_kmap_atomic
mdefine_line|#define __bio_kmap_atomic(bio, idx, kmtype)&t;&t;&t;&t;&bslash;&n;&t;(kmap_atomic(bio_iovec_idx((bio), (idx))-&gt;bv_page, kmtype) +&t;&bslash;&n;&t;&t;bio_iovec_idx((bio), (idx))-&gt;bv_offset)
DECL|macro|__bio_kunmap_atomic
mdefine_line|#define __bio_kunmap_atomic(addr, kmtype) kunmap_atomic(addr, kmtype)
multiline_comment|/*&n; * merge helpers etc&n; */
DECL|macro|__BVEC_END
mdefine_line|#define __BVEC_END(bio)&t;&t;bio_iovec_idx((bio), (bio)-&gt;bi_vcnt - 1)
DECL|macro|__BVEC_START
mdefine_line|#define __BVEC_START(bio)&t;bio_iovec_idx((bio), (bio)-&gt;bi_idx)
multiline_comment|/*&n; * allow arch override, for eg virtualized architectures (put in asm/io.h)&n; */
macro_line|#ifndef BIOVEC_PHYS_MERGEABLE
DECL|macro|BIOVEC_PHYS_MERGEABLE
mdefine_line|#define BIOVEC_PHYS_MERGEABLE(vec1, vec2)&t;&bslash;&n;&t;((bvec_to_phys((vec1)) + (vec1)-&gt;bv_len) == bvec_to_phys((vec2)))
macro_line|#endif
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
multiline_comment|/*&n; * A bio_pair is used when we need to split a bio.&n; * This can only happen for a bio that refers to just one&n; * page of data, and in the unusual situation when the&n; * page crosses a chunk/device boundary&n; *&n; * The address of the master bio is stored in bio1.bi_private&n; * The address of the pool the pair was allocated from is stored&n; *   in bio2.bi_private&n; */
DECL|struct|bio_pair
r_struct
id|bio_pair
(brace
DECL|member|bio1
DECL|member|bio2
r_struct
id|bio
id|bio1
comma
id|bio2
suffix:semicolon
DECL|member|bv1
DECL|member|bv2
r_struct
id|bio_vec
id|bv1
comma
id|bv2
suffix:semicolon
DECL|member|cnt
id|atomic_t
id|cnt
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|bio_pair
op_star
id|bio_split
c_func
(paren
r_struct
id|bio
op_star
id|bi
comma
id|mempool_t
op_star
id|pool
comma
r_int
id|first_sectors
)paren
suffix:semicolon
r_extern
id|mempool_t
op_star
id|bio_split_pool
suffix:semicolon
r_extern
r_void
id|bio_pair_release
c_func
(paren
r_struct
id|bio_pair
op_star
id|dbio
)paren
suffix:semicolon
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
r_extern
r_struct
id|bio
op_star
id|bio_map_user
c_func
(paren
r_struct
id|request_queue
op_star
comma
r_struct
id|block_device
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bio_unmap_user
c_func
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bio_set_pages_dirty
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
suffix:semicolon
r_extern
r_void
id|bio_check_pages_dirty
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
suffix:semicolon
r_extern
r_struct
id|bio
op_star
id|bio_copy_user
c_func
(paren
r_struct
id|request_queue
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|bio_uncopy_user
c_func
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
multiline_comment|/*&n; * remember to add offset! and never ever reenable interrupts between a&n; * bvec_kmap_irq and bvec_kunmap_irq!!&n; *&n; * This function MUST be inlined - it plays with the CPU interrupt flags.&n; * Hence the `extern inline&squot;.&n; */
DECL|function|bvec_kmap_irq
r_extern
r_inline
r_char
op_star
id|bvec_kmap_irq
c_func
(paren
r_struct
id|bio_vec
op_star
id|bvec
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
id|local_irq_save
c_func
(paren
op_star
id|flags
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
id|bvec-&gt;bv_page
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|addr
op_plus
id|bvec-&gt;bv_offset
suffix:semicolon
)brace
DECL|function|bvec_kunmap_irq
r_extern
r_inline
r_void
id|bvec_kunmap_irq
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
DECL|macro|bvec_kmap_irq
mdefine_line|#define bvec_kmap_irq(bvec, flags)&t;(page_address((bvec)-&gt;bv_page) + (bvec)-&gt;bv_offset)
DECL|macro|bvec_kunmap_irq
mdefine_line|#define bvec_kunmap_irq(buf, flags)&t;do { *(flags) = 0; } while (0)
macro_line|#endif
DECL|function|__bio_kmap_irq
r_extern
r_inline
r_char
op_star
id|__bio_kmap_irq
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|idx
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_return
id|bvec_kmap_irq
c_func
(paren
id|bio_iovec_idx
c_func
(paren
id|bio
comma
id|idx
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|__bio_kunmap_irq
mdefine_line|#define __bio_kunmap_irq(buf, flags)&t;bvec_kunmap_irq(buf, flags)
DECL|macro|bio_kmap_irq
mdefine_line|#define bio_kmap_irq(bio, flags) &bslash;&n;&t;__bio_kmap_irq((bio), (bio)-&gt;bi_idx, (flags))
DECL|macro|bio_kunmap_irq
mdefine_line|#define bio_kunmap_irq(buf,flags)&t;__bio_kunmap_irq(buf, flags)
macro_line|#endif /* __LINUX_BIO_H */
eof
