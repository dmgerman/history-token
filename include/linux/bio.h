multiline_comment|/*&n; * New 2.5 block I/O model&n; *&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or mo&n; * it under the terms of the GNU General Public License as publishe&n; * the Free Software Foundation; either version 2 of the License, o&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n;&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; */
macro_line|#ifndef __LINUX_BIO_H
DECL|macro|__LINUX_BIO_H
mdefine_line|#define __LINUX_BIO_H
DECL|macro|BIO_DEBUG
mdefine_line|#define BIO_DEBUG
macro_line|#ifdef BIO_DEBUG
DECL|macro|BIO_BUG_ON
mdefine_line|#define BIO_BUG_ON&t;BUG_ON
macro_line|#else
DECL|macro|BIO_BUG_ON
mdefine_line|#define BIO_BUG_ON
macro_line|#endif
multiline_comment|/*&n; * hash profiling stuff..&n; */
DECL|macro|BIO_HASH_PROFILING
mdefine_line|#define BIO_HASH_PROFILING
DECL|macro|BLKHASHPROF
mdefine_line|#define BLKHASHPROF&t;_IOR(0x12,108,sizeof(struct bio_hash_stats))
DECL|macro|BLKHASHCLEAR
mdefine_line|#define BLKHASHCLEAR&t;_IO(0x12,109)
DECL|macro|MAX_PROFILE_BUCKETS
mdefine_line|#define MAX_PROFILE_BUCKETS&t;64
DECL|struct|bio_hash_stats
r_struct
id|bio_hash_stats
(brace
DECL|member|nr_lookups
id|atomic_t
id|nr_lookups
suffix:semicolon
DECL|member|nr_hits
id|atomic_t
id|nr_hits
suffix:semicolon
DECL|member|nr_inserts
id|atomic_t
id|nr_inserts
suffix:semicolon
DECL|member|nr_entries
id|atomic_t
id|nr_entries
suffix:semicolon
DECL|member|max_entries
id|atomic_t
id|max_entries
suffix:semicolon
DECL|member|max_bucket_size
id|atomic_t
id|max_bucket_size
suffix:semicolon
DECL|member|bucket_size
id|atomic_t
id|bucket_size
(braket
id|MAX_PROFILE_BUCKETS
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
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
DECL|struct|bio_vec_list
r_struct
id|bio_vec_list
(brace
DECL|member|bvl_cnt
r_int
r_int
id|bvl_cnt
suffix:semicolon
multiline_comment|/* how may bio_vec&squot;s */
DECL|member|bvl_idx
r_int
r_int
id|bvl_idx
suffix:semicolon
multiline_comment|/* current index into bvl_vec */
DECL|member|bvl_size
r_int
r_int
id|bvl_size
suffix:semicolon
multiline_comment|/* total size in bytes */
DECL|member|bvl_max
r_int
r_int
id|bvl_max
suffix:semicolon
multiline_comment|/* max bvl_vecs we can hold, used&n;&t;&t;&t;&t;&t;   as index into pool */
DECL|member|bvl_vec
r_struct
id|bio_vec
id|bvl_vec
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* the iovec array */
)brace
suffix:semicolon
DECL|struct|bio_hash_s
r_typedef
r_struct
id|bio_hash_s
(brace
DECL|member|next_hash
r_struct
id|bio_hash_s
op_star
id|next_hash
suffix:semicolon
DECL|member|pprev_hash
r_struct
id|bio_hash_s
op_star
op_star
id|pprev_hash
suffix:semicolon
DECL|member|valid_counter
r_int
r_int
id|valid_counter
suffix:semicolon
DECL|typedef|bio_hash_t
)brace
id|bio_hash_t
suffix:semicolon
DECL|struct|bio_hash_bucket
r_struct
id|bio_hash_bucket
(brace
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|hash
id|bio_hash_t
op_star
id|hash
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|macro|BIO_HASH_BITS
mdefine_line|#define BIO_HASH_BITS&t;(bio_hash_bits)
DECL|macro|BIO_HASH_SIZE
mdefine_line|#define BIO_HASH_SIZE&t;(1UL &lt;&lt; BIO_HASH_BITS)
multiline_comment|/*&n; * shamelessly stolen from the list.h implementation&n; */
DECL|macro|hash_entry
mdefine_line|#define hash_entry(ptr, type, member)&t;&bslash;&n;&t;((type *)((char *)(ptr)-(unsigned long)(&amp;((type *)0)-&gt;member)))
DECL|macro|bio_hash_entry
mdefine_line|#define bio_hash_entry(ptr)&t;&t;&bslash;&n;&t;hash_entry((ptr), struct bio, bi_hash)
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
DECL|member|bi_hash
id|bio_hash_t
id|bi_hash
suffix:semicolon
DECL|member|bi_cnt
id|atomic_t
id|bi_cnt
suffix:semicolon
multiline_comment|/* pin count */
DECL|member|bi_dev
id|kdev_t
id|bi_dev
suffix:semicolon
multiline_comment|/* will be block device */
DECL|member|bi_io_vec
r_struct
id|bio_vec_list
op_star
id|bi_io_vec
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
DECL|member|bi_end_io
r_int
(paren
op_star
id|bi_end_io
)paren
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
id|nr_sectors
)paren
suffix:semicolon
DECL|member|bi_private
r_void
op_star
id|bi_private
suffix:semicolon
DECL|member|bi_hash_desc
r_void
op_star
id|bi_hash_desc
suffix:semicolon
multiline_comment|/* cookie for hash */
DECL|member|bi_destructor
r_void
(paren
op_star
id|bi_destructor
)paren
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
multiline_comment|/* destructor */
)brace
suffix:semicolon
DECL|macro|BIO_SECTOR_BITS
mdefine_line|#define BIO_SECTOR_BITS&t;9
DECL|macro|BIO_OFFSET_MASK
mdefine_line|#define BIO_OFFSET_MASK&t;((1UL &lt;&lt; (PAGE_CACHE_SHIFT - BIO_SECTOR_BITS)) - 1)
DECL|macro|BIO_PAGE_MASK
mdefine_line|#define BIO_PAGE_MASK&t;(PAGE_CACHE_SIZE - 1)
multiline_comment|/*&n; * bio flags&n; */
DECL|macro|BIO_UPTODATE
mdefine_line|#define BIO_UPTODATE&t;0&t;/* ok after I/O completion */
DECL|macro|BIO_RW_BLOCK
mdefine_line|#define BIO_RW_BLOCK&t;1&t;/* RW_AHEAD set, and read/write would block */
DECL|macro|BIO_EOF
mdefine_line|#define BIO_EOF&t;&t;2&t;/* out-out-bounds error */
DECL|macro|BIO_PREBUILT
mdefine_line|#define BIO_PREBUILT&t;3&t;/* not merged big */
DECL|macro|BIO_CLONED
mdefine_line|#define BIO_CLONED&t;4&t;/* doesn&squot;t own data */
DECL|macro|bio_is_hashed
mdefine_line|#define bio_is_hashed(bio)&t;((bio)-&gt;bi_hash.pprev_hash)
multiline_comment|/*&n; * bio bi_rw flags&n; *&n; * bit 0 -- read (not set) or write (set)&n; * bit 1 -- rw-ahead when set&n; * bit 2 -- barrier&n; */
DECL|macro|BIO_RW
mdefine_line|#define BIO_RW&t;&t;0
DECL|macro|BIO_RW_AHEAD
mdefine_line|#define BIO_RW_AHEAD&t;1
DECL|macro|BIO_BARRIER
mdefine_line|#define BIO_BARRIER&t;2
multiline_comment|/*&n; * various member access, note that bio_data should of course not be used&n; * on highmem page vectors&n; */
DECL|macro|bio_iovec_idx
mdefine_line|#define bio_iovec_idx(bio, idx)&t;(&amp;((bio)-&gt;bi_io_vec-&gt;bvl_vec[(idx)]))
DECL|macro|bio_iovec
mdefine_line|#define bio_iovec(bio)&t;&t;bio_iovec_idx((bio), (bio)-&gt;bi_io_vec-&gt;bvl_idx)
DECL|macro|bio_page
mdefine_line|#define bio_page(bio)&t;&t;bio_iovec((bio))-&gt;bv_page
DECL|macro|bio_size
mdefine_line|#define bio_size(bio)&t;&t;((bio)-&gt;bi_io_vec-&gt;bvl_size)
DECL|macro|bio_offset
mdefine_line|#define bio_offset(bio)&t;&t;bio_iovec((bio))-&gt;bv_offset
DECL|macro|bio_sectors
mdefine_line|#define bio_sectors(bio)&t;(bio_size((bio)) &gt;&gt; BIO_SECTOR_BITS)
DECL|macro|bio_data
mdefine_line|#define bio_data(bio)&t;&t;(page_address(bio_page((bio))) + bio_offset((bio)))
DECL|macro|bio_barrier
mdefine_line|#define bio_barrier(bio)&t;((bio)-&gt;bi_rw &amp; (1 &lt;&lt; BIO_BARRIER))
multiline_comment|/*&n; * will die&n; */
DECL|macro|bio_to_phys
mdefine_line|#define bio_to_phys(bio)&t;(page_to_phys(bio_page((bio))) + bio_offset((bio)))
DECL|macro|bvec_to_phys
mdefine_line|#define bvec_to_phys(bv)&t;(page_to_phys((bv)-&gt;bv_page) + (bv)-&gt;bv_offset)
multiline_comment|/*&n; * hack to avoid doing 64-bit calculations on 32-bit archs, instead use a&n; * pseudo-pfn check to do segment coalescing&n; */
DECL|macro|bio_sec_pfn
mdefine_line|#define bio_sec_pfn(bio) &bslash;&n;&t;((((bio_page(bio) - bio_page(bio)-&gt;zone-&gt;zone_mem_map) &lt;&lt; PAGE_SHIFT) / bio_size(bio)) + (bio_offset(bio) &gt;&gt; 9))
multiline_comment|/*&n; * queues that have highmem support enabled may still need to revert to&n; * PIO transfers occasionally and thus map high pages temporarily. For&n; * permanent PIO fall back, user is probably better off disabling highmem&n; * I/O completely on that queue (see ide-dma for example)&n; */
DECL|macro|bio_kmap
mdefine_line|#define bio_kmap(bio)&t;kmap(bio_page((bio))) + bio_offset((bio))
DECL|macro|bio_kunmap
mdefine_line|#define bio_kunmap(bio)&t;kunmap(bio_page((bio)))
DECL|macro|BIO_CONTIG
mdefine_line|#define BIO_CONTIG(bio, nxt) &bslash;&n;&t;(bio_to_phys((bio)) + bio_size((bio)) == bio_to_phys((nxt)))
DECL|macro|__BIO_PHYS_4G
mdefine_line|#define __BIO_PHYS_4G(addr1, addr2) &bslash;&n;&t;(((addr1) | 0xffffffff) == (((addr2) -1 ) | 0xffffffff))
DECL|macro|BIO_PHYS_4G
mdefine_line|#define BIO_PHYS_4G(b1, b2) &bslash;&n;&t;__BIO_PHYS_4G(bio_to_phys((b1)), bio_to_phys((b2)) + bio_size((b2)))
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
DECL|macro|bio_io_error
mdefine_line|#define bio_io_error(bio) bio_endio((bio), 0, bio_sectors((bio)))
DECL|macro|bio_for_each_segment
mdefine_line|#define bio_for_each_segment(bvl, bio, i)&t;&t;&t;&t;&bslash;&n;&t;for (bvl = bio_iovec((bio)), i = (bio)-&gt;bi_io_vec-&gt;bvl_idx;&t;&bslash;&n;&t;     i &lt; (bio)-&gt;bi_io_vec-&gt;bvl_cnt;&t;&t;&t;&t;&bslash;&n;&t;     bvl++, i++)
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
multiline_comment|/*&n; * the hash stuff is pretty closely tied to the request queue (needed for&n; * locking etc anyway, and it&squot;s in no way an attempt at a generic hash)&n; */
r_struct
id|request_queue
suffix:semicolon
r_extern
r_inline
r_void
id|bio_hash_remove
c_func
(paren
r_struct
id|bio
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|bio_hash_add
c_func
(paren
r_struct
id|bio
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_inline
r_struct
id|bio
op_star
id|bio_hash_find
c_func
(paren
id|kdev_t
comma
id|sector_t
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|bio_hash_add_unique
c_func
(paren
r_struct
id|bio
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bio_hash_invalidate
c_func
(paren
r_struct
id|request_queue
op_star
comma
id|kdev_t
)paren
suffix:semicolon
r_extern
r_int
id|bio_endio
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
