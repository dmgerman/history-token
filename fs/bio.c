multiline_comment|/*&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
DECL|macro|BIO_POOL_SIZE
mdefine_line|#define BIO_POOL_SIZE 256
DECL|variable|bio_pool
r_static
id|mempool_t
op_star
id|bio_pool
suffix:semicolon
DECL|variable|bio_slab
r_static
id|kmem_cache_t
op_star
id|bio_slab
suffix:semicolon
DECL|macro|BIOVEC_NR_POOLS
mdefine_line|#define BIOVEC_NR_POOLS 6
DECL|struct|biovec_pool
r_struct
id|biovec_pool
(brace
DECL|member|nr_vecs
r_int
id|nr_vecs
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|slab
id|kmem_cache_t
op_star
id|slab
suffix:semicolon
DECL|member|pool
id|mempool_t
op_star
id|pool
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * if you change this list, also change bvec_alloc or things will&n; * break badly! cannot be bigger than what you can fit into an&n; * unsigned short&n; */
DECL|macro|BV
mdefine_line|#define BV(x) { x, &quot;biovec-&quot; #x }
DECL|variable|bvec_array
r_static
r_struct
id|biovec_pool
id|bvec_array
(braket
id|BIOVEC_NR_POOLS
)braket
op_assign
(brace
id|BV
c_func
(paren
l_int|1
)paren
comma
id|BV
c_func
(paren
l_int|4
)paren
comma
id|BV
c_func
(paren
l_int|16
)paren
comma
id|BV
c_func
(paren
l_int|64
)paren
comma
id|BV
c_func
(paren
l_int|128
)paren
comma
id|BV
c_func
(paren
id|BIO_MAX_PAGES
)paren
comma
)brace
suffix:semicolon
DECL|macro|BV
macro_line|#undef BV
DECL|function|slab_pool_alloc
r_static
r_void
op_star
id|slab_pool_alloc
c_func
(paren
r_int
id|gfp_mask
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|kmem_cache_alloc
c_func
(paren
id|data
comma
id|gfp_mask
)paren
suffix:semicolon
)brace
DECL|function|slab_pool_free
r_static
r_void
id|slab_pool_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_void
op_star
id|data
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|data
comma
id|ptr
)paren
suffix:semicolon
)brace
DECL|function|bvec_alloc
r_static
r_inline
r_struct
id|bio_vec
op_star
id|bvec_alloc
c_func
(paren
r_int
id|gfp_mask
comma
r_int
id|nr
comma
r_int
op_star
id|idx
)paren
(brace
r_struct
id|biovec_pool
op_star
id|bp
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvl
suffix:semicolon
multiline_comment|/*&n;&t; * see comment near bvec_array define!&n;&t; */
r_switch
c_cond
(paren
id|nr
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|idx
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
dot
dot
dot
l_int|4
suffix:colon
op_star
id|idx
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
dot
dot
dot
l_int|16
suffix:colon
op_star
id|idx
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
dot
dot
dot
l_int|64
suffix:colon
op_star
id|idx
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|65
dot
dot
dot
l_int|128
suffix:colon
op_star
id|idx
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|129
dot
dot
dot
id|BIO_MAX_PAGES
suffix:colon
op_star
id|idx
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * idx now points to the pool we want to allocate from&n;&t; */
id|bp
op_assign
id|bvec_array
op_plus
op_star
id|idx
suffix:semicolon
id|bvl
op_assign
id|mempool_alloc
c_func
(paren
id|bp-&gt;pool
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bvl
)paren
id|memset
c_func
(paren
id|bvl
comma
l_int|0
comma
id|bp-&gt;nr_vecs
op_star
r_sizeof
(paren
r_struct
id|bio_vec
)paren
)paren
suffix:semicolon
r_return
id|bvl
suffix:semicolon
)brace
multiline_comment|/*&n; * default destructor for a bio allocated with bio_alloc()&n; */
DECL|function|bio_destructor
r_void
id|bio_destructor
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|biovec_pool
op_star
id|bp
op_assign
id|bvec_array
op_plus
id|bio-&gt;bi_max
suffix:semicolon
id|BIO_BUG_ON
c_func
(paren
id|bio-&gt;bi_max
op_ge
id|BIOVEC_NR_POOLS
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * cloned bio doesn&squot;t own the veclist&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bio_flagged
c_func
(paren
id|bio
comma
id|BIO_CLONED
)paren
)paren
id|mempool_free
c_func
(paren
id|bio-&gt;bi_io_vec
comma
id|bp-&gt;pool
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|bio
comma
id|bio_pool
)paren
suffix:semicolon
)brace
DECL|function|bio_init
r_inline
r_void
id|bio_init
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|bio-&gt;bi_next
op_assign
l_int|NULL
suffix:semicolon
id|bio-&gt;bi_flags
op_assign
l_int|1
op_lshift
id|BIO_UPTODATE
suffix:semicolon
id|bio-&gt;bi_rw
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_vcnt
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_phys_segments
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_hw_segments
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_size
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_end_io
op_assign
l_int|NULL
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|bio-&gt;bi_cnt
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * bio_alloc - allocate a bio for I/O&n; * @gfp_mask:   the GFP_ mask given to the slab allocator&n; * @nr_iovecs:&t;number of iovecs to pre-allocate&n; *&n; * Description:&n; *   bio_alloc will first try it&squot;s on mempool to satisfy the allocation.&n; *   If %__GFP_WAIT is set then we will block on the internal pool waiting&n; *   for a &amp;struct bio to become free.&n; **/
DECL|function|bio_alloc
r_struct
id|bio
op_star
id|bio_alloc
c_func
(paren
r_int
id|gfp_mask
comma
r_int
id|nr_iovecs
)paren
(brace
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvl
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_NOWARN
suffix:semicolon
id|bio
op_assign
id|mempool_alloc
c_func
(paren
id|bio_pool
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|bio
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_iovecs
op_logical_or
(paren
id|bvl
op_assign
id|bvec_alloc
c_func
(paren
id|gfp_mask
comma
id|nr_iovecs
comma
op_amp
id|bio-&gt;bi_max
)paren
)paren
)paren
(brace
id|bio_init
c_func
(paren
id|bio
)paren
suffix:semicolon
id|bio-&gt;bi_destructor
op_assign
id|bio_destructor
suffix:semicolon
id|bio-&gt;bi_io_vec
op_assign
id|bvl
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|mempool_free
c_func
(paren
id|bio
comma
id|bio_pool
)paren
suffix:semicolon
id|bio
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_NOWARN
suffix:semicolon
r_return
id|bio
suffix:semicolon
)brace
multiline_comment|/**&n; * bio_put - release a reference to a bio&n; * @bio:   bio to release reference to&n; *&n; * Description:&n; *   Put a reference to a &amp;struct bio, either one you have gotten with&n; *   bio_alloc or bio_get. The last put of a bio will free it.&n; **/
DECL|function|bio_put
r_void
id|bio_put
c_func
(paren
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|BIO_BUG_ON
c_func
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|bio-&gt;bi_cnt
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * last put frees it&n;&t; */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|bio-&gt;bi_cnt
)paren
)paren
(brace
id|bio-&gt;bi_next
op_assign
l_int|NULL
suffix:semicolon
id|bio
op_member_access_from_pointer
id|bi_destructor
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
)brace
DECL|function|bio_phys_segments
r_inline
r_int
id|bio_phys_segments
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|bio_flagged
c_func
(paren
id|bio
comma
id|BIO_SEG_VALID
)paren
)paren
)paren
id|blk_recount_segments
c_func
(paren
id|q
comma
id|bio
)paren
suffix:semicolon
r_return
id|bio-&gt;bi_phys_segments
suffix:semicolon
)brace
DECL|function|bio_hw_segments
r_inline
r_int
id|bio_hw_segments
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|bio_flagged
c_func
(paren
id|bio
comma
id|BIO_SEG_VALID
)paren
)paren
)paren
id|blk_recount_segments
c_func
(paren
id|q
comma
id|bio
)paren
suffix:semicolon
r_return
id|bio-&gt;bi_hw_segments
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;__bio_clone&t;-&t;clone a bio&n; * &t;@bio: destination bio&n; * &t;@bio_src: bio to clone&n; *&n; *&t;Clone a &amp;bio. Caller will own the returned bio, but not&n; *&t;the actual data it points to. Reference count of returned&n; * &t;bio will be one.&n; */
DECL|function|__bio_clone
r_inline
r_void
id|__bio_clone
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_struct
id|bio
op_star
id|bio_src
)paren
(brace
id|bio-&gt;bi_io_vec
op_assign
id|bio_src-&gt;bi_io_vec
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|bio_src-&gt;bi_sector
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|bio_src-&gt;bi_bdev
suffix:semicolon
id|bio-&gt;bi_flags
op_or_assign
l_int|1
op_lshift
id|BIO_CLONED
suffix:semicolon
id|bio-&gt;bi_rw
op_assign
id|bio_src-&gt;bi_rw
suffix:semicolon
multiline_comment|/*&n;&t; * notes -- maybe just leave bi_idx alone. bi_max has no use&n;&t; * on a cloned bio. assume identical mapping for the clone&n;&t; */
id|bio-&gt;bi_vcnt
op_assign
id|bio_src-&gt;bi_vcnt
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
id|bio_src-&gt;bi_idx
suffix:semicolon
r_if
c_cond
(paren
id|bio_flagged
c_func
(paren
id|bio
comma
id|BIO_SEG_VALID
)paren
)paren
(brace
id|bio-&gt;bi_phys_segments
op_assign
id|bio_src-&gt;bi_phys_segments
suffix:semicolon
id|bio-&gt;bi_hw_segments
op_assign
id|bio_src-&gt;bi_hw_segments
suffix:semicolon
id|bio-&gt;bi_flags
op_or_assign
(paren
l_int|1
op_lshift
id|BIO_SEG_VALID
)paren
suffix:semicolon
)brace
id|bio-&gt;bi_size
op_assign
id|bio_src-&gt;bi_size
suffix:semicolon
id|bio-&gt;bi_max
op_assign
id|bio_src-&gt;bi_max
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bio_clone&t;-&t;clone a bio&n; *&t;@bio: bio to clone&n; *&t;@gfp_mask: allocation priority&n; *&n; * &t;Like __bio_clone, only also allocates the returned bio&n; */
DECL|function|bio_clone
r_struct
id|bio
op_star
id|bio_clone
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
id|gfp_mask
)paren
(brace
r_struct
id|bio
op_star
id|b
op_assign
id|bio_alloc
c_func
(paren
id|gfp_mask
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
id|__bio_clone
c_func
(paren
id|b
comma
id|bio
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bio_copy&t;-&t;create copy of a bio&n; *&t;@bio: bio to copy&n; *&t;@gfp_mask: allocation priority&n; *&t;@copy: copy data to allocated bio&n; *&n; *&t;Create a copy of a &amp;bio. Caller will own the returned bio and&n; *&t;the actual data it points to. Reference count of returned&n; * &t;bio will be one.&n; */
DECL|function|bio_copy
r_struct
id|bio
op_star
id|bio_copy
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
id|gfp_mask
comma
r_int
id|copy
)paren
(brace
r_struct
id|bio
op_star
id|b
op_assign
id|bio_alloc
c_func
(paren
id|gfp_mask
comma
id|bio-&gt;bi_vcnt
)paren
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* gcc silly */
r_struct
id|bio_vec
op_star
id|bv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|b
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * iterate iovec list and alloc pages + copy data&n;&t; */
id|__bio_for_each_segment
c_func
(paren
id|bv
comma
id|bio
comma
id|i
comma
l_int|0
)paren
(brace
r_struct
id|bio_vec
op_star
id|bbv
op_assign
op_amp
id|b-&gt;bi_io_vec
(braket
id|i
)braket
suffix:semicolon
r_char
op_star
id|vfrom
comma
op_star
id|vto
suffix:semicolon
id|bbv-&gt;bv_page
op_assign
id|alloc_page
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bbv-&gt;bv_page
op_eq
l_int|NULL
)paren
r_goto
id|oom
suffix:semicolon
id|bbv-&gt;bv_len
op_assign
id|bv-&gt;bv_len
suffix:semicolon
id|bbv-&gt;bv_offset
op_assign
id|bv-&gt;bv_offset
suffix:semicolon
multiline_comment|/*&n;&t;&t; * if doing a copy for a READ request, no need&n;&t;&t; * to memcpy page data&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|copy
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
(brace
id|vfrom
op_assign
id|kmap
c_func
(paren
id|bv-&gt;bv_page
)paren
suffix:semicolon
id|vto
op_assign
id|kmap
c_func
(paren
id|bbv-&gt;bv_page
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
id|bv-&gt;bv_page
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
id|bbv-&gt;bv_page
comma
id|KM_BIO_DST_IRQ
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|vto
op_plus
id|bbv-&gt;bv_offset
comma
id|vfrom
op_plus
id|bv-&gt;bv_offset
comma
id|bv-&gt;bv_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gfp_mask
op_amp
id|__GFP_WAIT
)paren
(brace
id|kunmap
c_func
(paren
id|bbv-&gt;bv_page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|bv-&gt;bv_page
)paren
suffix:semicolon
)brace
r_else
(brace
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_BIO_DST_IRQ
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
id|b-&gt;bi_sector
op_assign
id|bio-&gt;bi_sector
suffix:semicolon
id|b-&gt;bi_bdev
op_assign
id|bio-&gt;bi_bdev
suffix:semicolon
id|b-&gt;bi_rw
op_assign
id|bio-&gt;bi_rw
suffix:semicolon
id|b-&gt;bi_vcnt
op_assign
id|bio-&gt;bi_vcnt
suffix:semicolon
id|b-&gt;bi_size
op_assign
id|bio-&gt;bi_size
suffix:semicolon
r_return
id|b
suffix:semicolon
id|oom
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
id|__free_page
c_func
(paren
id|b-&gt;bi_io_vec
(braket
id|i
)braket
dot
id|bv_page
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|b
comma
id|bio_pool
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;bio_add_page&t;-&t;attempt to add page to bio&n; *&t;@bio: destination bio&n; *&t;@page: page to add&n; *&t;@len: vec entry length&n; *&t;@offset: vec entry offset&n; *&n; *&t;Attempt to add a page to the bio_vec maplist. This can fail for a&n; *&t;number of reasons, such as the bio being full or target block&n; *&t;device limitations.&n; */
DECL|function|bio_add_page
r_int
id|bio_add_page
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
r_int
id|len
comma
r_int
r_int
id|offset
)paren
(brace
id|request_queue_t
op_star
id|q
op_assign
id|bdev_get_queue
c_func
(paren
id|bio-&gt;bi_bdev
)paren
suffix:semicolon
r_int
id|fail_segments
op_assign
l_int|0
comma
id|retried_segments
op_assign
l_int|0
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvec
suffix:semicolon
multiline_comment|/*&n;&t; * cloned bio must not modify vec list&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|bio_flagged
c_func
(paren
id|bio
comma
id|BIO_CLONED
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: change bi_max?&n;&t; */
id|BUG_ON
c_func
(paren
id|bio-&gt;bi_max
OG
id|BIOVEC_NR_POOLS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_vcnt
op_ge
id|bvec_array
(braket
id|bio-&gt;bi_max
)braket
dot
id|nr_vecs
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|bio-&gt;bi_size
op_plus
id|len
)paren
op_rshift
l_int|9
)paren
OG
id|q-&gt;max_sectors
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * we might loose a segment or two here, but rather that than&n;&t; * make this too complex.&n;&t; */
id|retry_segments
suffix:colon
r_if
c_cond
(paren
id|bio_phys_segments
c_func
(paren
id|q
comma
id|bio
)paren
op_ge
id|q-&gt;max_phys_segments
op_logical_or
id|bio_hw_segments
c_func
(paren
id|q
comma
id|bio
)paren
op_ge
id|q-&gt;max_hw_segments
)paren
id|fail_segments
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fail_segments
)paren
(brace
r_if
c_cond
(paren
id|retried_segments
)paren
r_return
l_int|1
suffix:semicolon
id|bio-&gt;bi_flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|BIO_SEG_VALID
)paren
suffix:semicolon
id|retried_segments
op_assign
l_int|1
suffix:semicolon
r_goto
id|retry_segments
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * setup the new entry, we might clear it again later if we&n;&t; * cannot add the page&n;&t; */
id|bvec
op_assign
op_amp
id|bio-&gt;bi_io_vec
(braket
id|bio-&gt;bi_vcnt
)braket
suffix:semicolon
id|bvec-&gt;bv_page
op_assign
id|page
suffix:semicolon
id|bvec-&gt;bv_len
op_assign
id|len
suffix:semicolon
id|bvec-&gt;bv_offset
op_assign
id|offset
suffix:semicolon
multiline_comment|/*&n;&t; * if queue has other restrictions (eg varying max sector size&n;&t; * depending on offset), it can specify a merge_bvec_fn in the&n;&t; * queue to get further control&n;&t; */
r_if
c_cond
(paren
id|q-&gt;merge_bvec_fn
op_logical_and
id|q
op_member_access_from_pointer
id|merge_bvec_fn
c_func
(paren
id|q
comma
id|bio
comma
id|bvec
)paren
)paren
(brace
id|bvec-&gt;bv_page
op_assign
l_int|NULL
suffix:semicolon
id|bvec-&gt;bv_len
op_assign
l_int|0
suffix:semicolon
id|bvec-&gt;bv_offset
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|bio-&gt;bi_vcnt
op_increment
suffix:semicolon
id|bio-&gt;bi_phys_segments
op_increment
suffix:semicolon
id|bio-&gt;bi_hw_segments
op_increment
suffix:semicolon
id|bio-&gt;bi_size
op_add_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bio_end_io_kio
r_static
r_int
id|bio_end_io_kio
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
id|error
)paren
(brace
r_struct
id|kiobuf
op_star
id|kio
op_assign
(paren
r_struct
id|kiobuf
op_star
)paren
id|bio-&gt;bi_private
suffix:semicolon
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|end_kio_request
c_func
(paren
id|kio
comma
id|error
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
multiline_comment|/**&n; * ll_rw_kio - submit a &amp;struct kiobuf for I/O&n; * @rw:   %READ or %WRITE&n; * @kio:   the kiobuf to do I/O on&n; * @bdev:   target device&n; * @sector:   start location on disk&n; *&n; * Description:&n; *   ll_rw_kio will map the page list inside the &amp;struct kiobuf to&n; *   &amp;struct bio and queue them for I/O. The kiobuf given must describe&n; *   a continous range of data, and must be fully prepared for I/O.&n; **/
DECL|function|ll_rw_kio
r_void
id|ll_rw_kio
c_func
(paren
r_int
id|rw
comma
r_struct
id|kiobuf
op_star
id|kio
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|sector
)paren
(brace
r_int
id|i
comma
id|offset
comma
id|size
comma
id|err
comma
id|map_i
comma
id|total_nr_pages
comma
id|nr_pages
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rw
op_amp
id|WRITE
)paren
op_logical_and
id|bdev_read_only
c_func
(paren
id|bdev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_bio: WRITE to ro device %s&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|kio-&gt;nr_pages
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * maybe kio is bigger than the max we can easily map into a bio.&n;&t; * if so, split it up in appropriately sized chunks.&n;&t; */
id|total_nr_pages
op_assign
id|kio-&gt;nr_pages
suffix:semicolon
id|offset
op_assign
id|kio-&gt;offset
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|kio-&gt;length
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|kio-&gt;io_count
comma
l_int|1
)paren
suffix:semicolon
id|map_i
op_assign
l_int|0
suffix:semicolon
id|next_chunk
suffix:colon
id|nr_pages
op_assign
id|BIO_MAX_PAGES
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
OG
id|total_nr_pages
)paren
id|nr_pages
op_assign
id|total_nr_pages
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|kio-&gt;io_count
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * allocate bio and do initial setup&n;&t; */
r_if
c_cond
(paren
(paren
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|GFP_NOIO
comma
id|nr_pages
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bio-&gt;bi_sector
op_assign
id|sector
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|bdev
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_end_io
op_assign
id|bio_end_io_kio
suffix:semicolon
id|bio-&gt;bi_private
op_assign
id|kio
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
comma
id|map_i
op_increment
)paren
(brace
r_int
id|nbytes
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OG
id|size
)paren
id|nbytes
op_assign
id|size
suffix:semicolon
id|BUG_ON
c_func
(paren
id|kio-&gt;maplist
(braket
id|map_i
)braket
op_eq
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * if we can&squot;t add this page to the bio, submit for i/o&n;&t;&t; * and alloc a new one if needed&n;&t;&t; */
r_if
c_cond
(paren
id|bio_add_page
c_func
(paren
id|bio
comma
id|kio-&gt;maplist
(braket
id|map_i
)braket
comma
id|nbytes
comma
id|offset
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * kiobuf only has an offset into the first page&n;&t;&t; */
id|offset
op_assign
l_int|0
suffix:semicolon
id|sector
op_add_assign
id|nbytes
op_rshift
l_int|9
suffix:semicolon
id|size
op_sub_assign
id|nbytes
suffix:semicolon
id|total_nr_pages
op_decrement
suffix:semicolon
id|kio-&gt;offset
op_add_assign
id|nbytes
suffix:semicolon
)brace
id|submit_bio
c_func
(paren
id|rw
comma
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|total_nr_pages
)paren
r_goto
id|next_chunk
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ll_rw_kio: size %d left (kio %d)&bslash;n&quot;
comma
id|size
comma
id|kio-&gt;length
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|err
)paren
id|kio-&gt;errno
op_assign
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * final atomic_dec of io_count to match our initial setting of 1.&n;&t; * I/O may or may not have completed at this point, final completion&n;&t; * handler is only run on last decrement.&n;&t; */
id|end_kio_request
c_func
(paren
id|kio
comma
op_logical_neg
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * bio_endio - end I/O on a bio&n; * @bio:&t;bio&n; * @bytes_done:&t;number of bytes completed&n; * @error:&t;error, if any&n; *&n; * Description:&n; *   bio_endio() will end I/O @bytes_done number of bytes. This may be just&n; *   a partial part of the bio, or it may be the whole bio. bio_endio() is&n; *   the preferred way to end I/O on a bio, it takes care of decrementing&n; *   bi_size and clearing BIO_UPTODATE on error. @error is 0 on success, and&n; *   and one of the established -Exxxx (-EIO, for instance) error values in&n; *   case something went wrong.&n; **/
DECL|function|bio_endio
r_int
id|bio_endio
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
id|error
)paren
(brace
r_if
c_cond
(paren
id|error
)paren
id|clear_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|bytes_done
OG
id|bio-&gt;bi_size
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: want %u bytes done, only %u left&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|bytes_done
comma
id|bio-&gt;bi_size
)paren
suffix:semicolon
id|bytes_done
op_assign
id|bio-&gt;bi_size
suffix:semicolon
)brace
id|bio-&gt;bi_size
op_sub_assign
id|bytes_done
suffix:semicolon
r_return
id|bio
op_member_access_from_pointer
id|bi_end_io
c_func
(paren
id|bio
comma
id|bytes_done
comma
id|error
)paren
suffix:semicolon
)brace
DECL|function|biovec_init_pools
r_static
r_void
id|__init
id|biovec_init_pools
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|size
comma
id|megabytes
comma
id|pool_entries
op_assign
id|BIO_POOL_SIZE
suffix:semicolon
r_int
id|scale
op_assign
id|BIOVEC_NR_POOLS
suffix:semicolon
id|megabytes
op_assign
id|nr_free_pages
c_func
(paren
)paren
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * find out where to start scaling&n;&t; */
r_if
c_cond
(paren
id|megabytes
op_le
l_int|16
)paren
id|scale
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|megabytes
op_le
l_int|32
)paren
id|scale
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|megabytes
op_le
l_int|64
)paren
id|scale
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|megabytes
op_le
l_int|96
)paren
id|scale
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|megabytes
op_le
l_int|128
)paren
id|scale
op_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * scale number of entries&n;&t; */
id|pool_entries
op_assign
id|megabytes
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|pool_entries
OG
l_int|256
)paren
id|pool_entries
op_assign
l_int|256
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
id|BIOVEC_NR_POOLS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|biovec_pool
op_star
id|bp
op_assign
id|bvec_array
op_plus
id|i
suffix:semicolon
id|size
op_assign
id|bp-&gt;nr_vecs
op_star
r_sizeof
(paren
r_struct
id|bio_vec
)paren
suffix:semicolon
id|bp-&gt;slab
op_assign
id|kmem_cache_create
c_func
(paren
id|bp-&gt;name
comma
id|size
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp-&gt;slab
)paren
id|panic
c_func
(paren
l_string|&quot;biovec: can&squot;t init slab cache&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|scale
)paren
id|pool_entries
op_rshift_assign
l_int|1
suffix:semicolon
id|bp-&gt;pool
op_assign
id|mempool_create
c_func
(paren
id|pool_entries
comma
id|slab_pool_alloc
comma
id|slab_pool_free
comma
id|bp-&gt;slab
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp-&gt;pool
)paren
id|panic
c_func
(paren
l_string|&quot;biovec: can&squot;t init mempool&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;biovec pool[%d]: %3d bvecs: %3d entries (%d bytes)&bslash;n&quot;
comma
id|i
comma
id|bp-&gt;nr_vecs
comma
id|pool_entries
comma
id|size
)paren
suffix:semicolon
)brace
)brace
DECL|function|init_bio
r_static
r_int
id|__init
id|init_bio
c_func
(paren
r_void
)paren
(brace
id|bio_slab
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bio&quot;
comma
r_sizeof
(paren
r_struct
id|bio
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bio_slab
)paren
id|panic
c_func
(paren
l_string|&quot;bio: can&squot;t create slab cache&bslash;n&quot;
)paren
suffix:semicolon
id|bio_pool
op_assign
id|mempool_create
c_func
(paren
id|BIO_POOL_SIZE
comma
id|slab_pool_alloc
comma
id|slab_pool_free
comma
id|bio_slab
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bio_pool
)paren
id|panic
c_func
(paren
l_string|&quot;bio: can&squot;t create mempool&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;BIO: pool of %d setup, %ZuKb (%Zd bytes/bio)&bslash;n&quot;
comma
id|BIO_POOL_SIZE
comma
id|BIO_POOL_SIZE
op_star
r_sizeof
(paren
r_struct
id|bio
)paren
op_rshift
l_int|10
comma
r_sizeof
(paren
r_struct
id|bio
)paren
)paren
suffix:semicolon
id|biovec_init_pools
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_bio
id|module_init
c_func
(paren
id|init_bio
)paren
suffix:semicolon
DECL|variable|bio_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|bio_alloc
)paren
suffix:semicolon
DECL|variable|bio_put
id|EXPORT_SYMBOL
c_func
(paren
id|bio_put
)paren
suffix:semicolon
DECL|variable|ll_rw_kio
id|EXPORT_SYMBOL
c_func
(paren
id|ll_rw_kio
)paren
suffix:semicolon
DECL|variable|bio_endio
id|EXPORT_SYMBOL
c_func
(paren
id|bio_endio
)paren
suffix:semicolon
DECL|variable|bio_init
id|EXPORT_SYMBOL
c_func
(paren
id|bio_init
)paren
suffix:semicolon
DECL|variable|bio_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bio_copy
)paren
suffix:semicolon
DECL|variable|__bio_clone
id|EXPORT_SYMBOL
c_func
(paren
id|__bio_clone
)paren
suffix:semicolon
DECL|variable|bio_clone
id|EXPORT_SYMBOL
c_func
(paren
id|bio_clone
)paren
suffix:semicolon
DECL|variable|bio_phys_segments
id|EXPORT_SYMBOL
c_func
(paren
id|bio_phys_segments
)paren
suffix:semicolon
DECL|variable|bio_hw_segments
id|EXPORT_SYMBOL
c_func
(paren
id|bio_hw_segments
)paren
suffix:semicolon
DECL|variable|bio_add_page
id|EXPORT_SYMBOL
c_func
(paren
id|bio_add_page
)paren
suffix:semicolon
eof
