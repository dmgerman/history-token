multiline_comment|/*&n; * High memory handling common code and variables.&n; *&n; * (C) 1999 Andrea Arcangeli, SuSE GmbH, andrea@suse.de&n; *          Gerhard Wichert, Siemens AG, Gerhard.Wichert@pdb.siemens.de&n; *&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with&n; * 64-bit physical space. With current x86 CPUs this&n; * means up to 64 Gigabytes physical RAM.&n; *&n; * Rewrote high memory support to move the page cache into&n; * high memory. Implemented permanent (schedulable) kmaps&n; * based on Linus&squot; idea.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|page_pool
DECL|variable|isa_page_pool
r_static
id|mempool_t
op_star
id|page_pool
comma
op_star
id|isa_page_pool
suffix:semicolon
DECL|function|page_pool_alloc
r_static
r_void
op_star
id|page_pool_alloc
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
r_int
id|gfp
op_assign
id|gfp_mask
op_or
(paren
r_int
)paren
(paren
r_int
)paren
id|data
suffix:semicolon
r_return
id|alloc_page
c_func
(paren
id|gfp
)paren
suffix:semicolon
)brace
DECL|function|page_pool_free
r_static
r_void
id|page_pool_free
c_func
(paren
r_void
op_star
id|page
comma
r_void
op_star
id|data
)paren
(brace
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Virtual_count is not a pure &quot;count&quot;.&n; *  0 means that it is not mapped, and has not been mapped&n; *    since a TLB flush - it is usable.&n; *  1 means that there are no users, but it has been mapped&n; *    since the last TLB flush - so we can&squot;t use it.&n; *  n means that there are (n-1) current users of it.&n; */
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|pkmap_count
r_static
r_int
id|pkmap_count
(braket
id|LAST_PKMAP
)braket
suffix:semicolon
DECL|variable|last_pkmap_nr
r_static
r_int
r_int
id|last_pkmap_nr
suffix:semicolon
DECL|variable|__cacheline_aligned_in_smp
r_static
id|spinlock_t
id|kmap_lock
id|__cacheline_aligned_in_smp
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pkmap_page_table
id|pte_t
op_star
id|pkmap_page_table
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|pkmap_map_wait
)paren
suffix:semicolon
DECL|function|flush_all_zero_pkmaps
r_static
r_void
id|flush_all_zero_pkmaps
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|flush_cache_all
c_func
(paren
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
id|LAST_PKMAP
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/*&n;&t;&t; * zero means we don&squot;t have anything to do,&n;&t;&t; * &gt;1 means that it is still in use. Only&n;&t;&t; * a count of 1 means that it is free but&n;&t;&t; * needs to be unmapped&n;&t;&t; */
r_if
c_cond
(paren
id|pkmap_count
(braket
id|i
)braket
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
id|pkmap_count
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|pkmap_page_table
(braket
id|i
)braket
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t need an atomic fetch-and-clear op here;&n;&t;&t; * no-one has the page mapped, and cannot get at&n;&t;&t; * its virtual address (and hence PTE) without first&n;&t;&t; * getting the kmap_lock (which is held here).&n;&t;&t; * So no dangers, even with speculative execution.&n;&t;&t; */
id|page
op_assign
id|pte_page
c_func
(paren
id|pkmap_page_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
op_amp
id|pkmap_page_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|set_page_address
c_func
(paren
id|page
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|flush_tlb_kernel_range
c_func
(paren
id|PKMAP_ADDR
c_func
(paren
l_int|0
)paren
comma
id|PKMAP_ADDR
c_func
(paren
id|LAST_PKMAP
)paren
)paren
suffix:semicolon
)brace
DECL|function|map_new_virtual
r_static
r_inline
r_int
r_int
id|map_new_virtual
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
r_int
id|count
suffix:semicolon
id|start
suffix:colon
id|count
op_assign
id|LAST_PKMAP
suffix:semicolon
multiline_comment|/* Find an empty entry */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|last_pkmap_nr
op_assign
(paren
id|last_pkmap_nr
op_plus
l_int|1
)paren
op_amp
id|LAST_PKMAP_MASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|last_pkmap_nr
)paren
(brace
id|flush_all_zero_pkmaps
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|LAST_PKMAP
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pkmap_count
(braket
id|last_pkmap_nr
)braket
)paren
r_break
suffix:semicolon
multiline_comment|/* Found a usable entry */
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Sleep for somebody else to unmap their entries&n;&t;&t; */
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|pkmap_map_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|pkmap_map_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
multiline_comment|/* Somebody else might have mapped it while we slept */
r_if
c_cond
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
r_return
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* Re-start */
r_goto
id|start
suffix:semicolon
)brace
)brace
id|vaddr
op_assign
id|PKMAP_ADDR
c_func
(paren
id|last_pkmap_nr
)paren
suffix:semicolon
id|set_pte
c_func
(paren
op_amp
(paren
id|pkmap_page_table
(braket
id|last_pkmap_nr
)braket
)paren
comma
id|mk_pte
c_func
(paren
id|page
comma
id|kmap_prot
)paren
)paren
suffix:semicolon
id|pkmap_count
(braket
id|last_pkmap_nr
)braket
op_assign
l_int|1
suffix:semicolon
id|set_page_address
c_func
(paren
id|page
comma
(paren
r_void
op_star
)paren
id|vaddr
)paren
suffix:semicolon
r_return
id|vaddr
suffix:semicolon
)brace
DECL|function|kmap_high
r_void
op_star
id|kmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/*&n;&t; * For highmem pages, we can&squot;t trust &quot;virtual&quot; until&n;&t; * after we have the lock.&n;&t; *&n;&t; * We cannot call this from interrupts, as it may block&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vaddr
)paren
id|vaddr
op_assign
id|map_new_virtual
c_func
(paren
id|page
)paren
suffix:semicolon
id|pkmap_count
(braket
id|PKMAP_NR
c_func
(paren
id|vaddr
)paren
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pkmap_count
(braket
id|PKMAP_NR
c_func
(paren
id|vaddr
)paren
)braket
OL
l_int|2
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|vaddr
suffix:semicolon
)brace
DECL|function|kunmap_high
r_void
id|kunmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
r_int
r_int
id|nr
suffix:semicolon
r_int
id|need_wakeup
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vaddr
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|nr
op_assign
id|PKMAP_NR
c_func
(paren
id|vaddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * A count must never go down to zero&n;&t; * without a TLB flush!&n;&t; */
id|need_wakeup
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
op_decrement
id|pkmap_count
(braket
id|nr
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/*&n;&t;&t; * Avoid an unnecessary wake_up() function call.&n;&t;&t; * The common case is pkmap_count[] == 1, but&n;&t;&t; * no waiters.&n;&t;&t; * The tasks queued in the wait-queue are guarded&n;&t;&t; * by both the lock in the wait-queue-head and by&n;&t;&t; * the kmap_lock.  As the kmap_lock is held here,&n;&t;&t; * no need for the wait-queue-head&squot;s lock.  Simply&n;&t;&t; * test if the queue is empty.&n;&t;&t; */
id|need_wakeup
op_assign
id|waitqueue_active
c_func
(paren
op_amp
id|pkmap_map_wait
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kmap_lock
)paren
suffix:semicolon
multiline_comment|/* do wake-up, if needed, race-free outside of the spin lock */
r_if
c_cond
(paren
id|need_wakeup
)paren
id|wake_up
c_func
(paren
op_amp
id|pkmap_map_wait
)paren
suffix:semicolon
)brace
DECL|macro|POOL_SIZE
mdefine_line|#define POOL_SIZE&t;64
DECL|function|init_emergency_pool
r_static
id|__init
r_int
id|init_emergency_pool
c_func
(paren
r_void
)paren
(brace
r_struct
id|sysinfo
id|i
suffix:semicolon
id|si_meminfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
id|si_swapinfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i.totalhigh
)paren
r_return
l_int|0
suffix:semicolon
id|page_pool
op_assign
id|mempool_create
c_func
(paren
id|POOL_SIZE
comma
id|page_pool_alloc
comma
id|page_pool_free
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_pool
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;highmem bounce pool size: %d pages&bslash;n&quot;
comma
id|POOL_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_emergency_pool
id|__initcall
c_func
(paren
id|init_emergency_pool
)paren
suffix:semicolon
multiline_comment|/*&n; * highmem version, map in to vec&n; */
DECL|function|bounce_copy_vec
r_static
r_void
id|bounce_copy_vec
c_func
(paren
r_struct
id|bio_vec
op_star
id|to
comma
r_int
r_char
op_star
id|vfrom
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
op_star
id|vto
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
id|to-&gt;bv_page
comma
id|KM_BOUNCE_READ
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vto
op_plus
id|to-&gt;bv_offset
comma
id|vfrom
comma
id|to-&gt;bv_len
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_BOUNCE_READ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_HIGHMEM */
DECL|macro|bounce_copy_vec
mdefine_line|#define bounce_copy_vec(to, vfrom)&t;&bslash;&n;&t;memcpy(page_address((to)-&gt;bv_page) + (to)-&gt;bv_offset, vfrom, (to)-&gt;bv_len)
macro_line|#endif
DECL|macro|ISA_POOL_SIZE
mdefine_line|#define ISA_POOL_SIZE&t;16
multiline_comment|/*&n; * gets called &quot;every&quot; time someone init&squot;s a queue with BLK_BOUNCE_ISA&n; * as the max address, so check if the pool has already been created.&n; */
DECL|function|init_emergency_isa_pool
r_int
id|init_emergency_isa_pool
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|isa_page_pool
)paren
r_return
l_int|0
suffix:semicolon
id|isa_page_pool
op_assign
id|mempool_create
c_func
(paren
id|ISA_POOL_SIZE
comma
id|page_pool_alloc
comma
id|page_pool_free
comma
(paren
r_void
op_star
)paren
id|__GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isa_page_pool
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;isa bounce pool size: %d pages&bslash;n&quot;
comma
id|ISA_POOL_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Simple bounce buffer support for highmem pages. Depending on the&n; * queue gfp mask set, *to may or may not be a highmem page. kmap it&n; * always, it will do the Right Thing&n; */
DECL|function|copy_to_high_bio_irq
r_static
r_void
id|copy_to_high_bio_irq
c_func
(paren
r_struct
id|bio
op_star
id|to
comma
r_struct
id|bio
op_star
id|from
)paren
(brace
r_int
r_char
op_star
id|vfrom
suffix:semicolon
r_struct
id|bio_vec
op_star
id|tovec
comma
op_star
id|fromvec
suffix:semicolon
r_int
id|i
suffix:semicolon
id|__bio_for_each_segment
c_func
(paren
id|tovec
comma
id|to
comma
id|i
comma
l_int|0
)paren
(brace
id|fromvec
op_assign
id|from-&gt;bi_io_vec
op_plus
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t; * not bounced&n;&t;&t; */
r_if
c_cond
(paren
id|tovec-&gt;bv_page
op_eq
id|fromvec-&gt;bv_page
)paren
r_continue
suffix:semicolon
id|vfrom
op_assign
id|page_address
c_func
(paren
id|fromvec-&gt;bv_page
)paren
op_plus
id|fromvec-&gt;bv_offset
suffix:semicolon
id|bounce_copy_vec
c_func
(paren
id|tovec
comma
id|vfrom
)paren
suffix:semicolon
)brace
)brace
DECL|function|bounce_end_io
r_static
r_void
id|bounce_end_io
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
id|mempool_t
op_star
id|pool
)paren
(brace
r_struct
id|bio
op_star
id|bio_orig
op_assign
id|bio-&gt;bi_private
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvec
comma
op_star
id|org_vec
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
)paren
r_goto
id|out_eio
suffix:semicolon
id|set_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio_orig-&gt;bi_flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * free up bounce indirect pages used&n;&t; */
id|__bio_for_each_segment
c_func
(paren
id|bvec
comma
id|bio
comma
id|i
comma
l_int|0
)paren
(brace
id|org_vec
op_assign
id|bio_orig-&gt;bi_io_vec
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|bvec-&gt;bv_page
op_eq
id|org_vec-&gt;bv_page
)paren
r_continue
suffix:semicolon
id|mempool_free
c_func
(paren
id|bvec-&gt;bv_page
comma
id|pool
)paren
suffix:semicolon
)brace
id|out_eio
suffix:colon
id|bio_endio
c_func
(paren
id|bio_orig
comma
id|bio_orig-&gt;bi_size
comma
l_int|0
)paren
suffix:semicolon
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
)brace
DECL|function|bounce_end_io_write
r_static
r_int
id|bounce_end_io_write
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
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|bounce_end_io
c_func
(paren
id|bio
comma
id|page_pool
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bounce_end_io_write_isa
r_static
r_int
id|bounce_end_io_write_isa
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
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|bounce_end_io
c_func
(paren
id|bio
comma
id|isa_page_pool
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__bounce_end_io_read
r_static
r_void
id|__bounce_end_io_read
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
id|mempool_t
op_star
id|pool
)paren
(brace
r_struct
id|bio
op_star
id|bio_orig
op_assign
id|bio-&gt;bi_private
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
)paren
id|copy_to_high_bio_irq
c_func
(paren
id|bio_orig
comma
id|bio
)paren
suffix:semicolon
id|bounce_end_io
c_func
(paren
id|bio
comma
id|pool
)paren
suffix:semicolon
)brace
DECL|function|bounce_end_io_read
r_static
r_int
id|bounce_end_io_read
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
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|__bounce_end_io_read
c_func
(paren
id|bio
comma
id|page_pool
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bounce_end_io_read_isa
r_static
r_int
id|bounce_end_io_read_isa
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
r_if
c_cond
(paren
id|bio-&gt;bi_size
)paren
r_return
l_int|1
suffix:semicolon
id|__bounce_end_io_read
c_func
(paren
id|bio
comma
id|isa_page_pool
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__blk_queue_bounce
r_static
r_void
id|__blk_queue_bounce
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
op_star
id|bio_orig
comma
id|mempool_t
op_star
id|pool
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|bio
op_star
id|bio
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|rw
op_assign
id|bio_data_dir
c_func
(paren
op_star
id|bio_orig
)paren
suffix:semicolon
r_struct
id|bio_vec
op_star
id|to
comma
op_star
id|from
suffix:semicolon
id|bio_for_each_segment
c_func
(paren
id|from
comma
op_star
id|bio_orig
comma
id|i
)paren
(brace
id|page
op_assign
id|from-&gt;bv_page
suffix:semicolon
multiline_comment|/*&n;&t;&t; * is destination page below bounce pfn?&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|page
op_minus
id|page_zone
c_func
(paren
id|page
)paren
op_member_access_from_pointer
id|zone_mem_map
)paren
op_plus
(paren
id|page_zone
c_func
(paren
id|page
)paren
op_member_access_from_pointer
id|zone_start_pfn
)paren
OL
id|q-&gt;bounce_pfn
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * irk, bounce it&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bio
)paren
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|GFP_NOIO
comma
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_vcnt
)paren
suffix:semicolon
id|to
op_assign
id|bio-&gt;bi_io_vec
op_plus
id|i
suffix:semicolon
id|to-&gt;bv_page
op_assign
id|mempool_alloc
c_func
(paren
id|pool
comma
id|q-&gt;bounce_gfp
)paren
suffix:semicolon
id|to-&gt;bv_len
op_assign
id|from-&gt;bv_len
suffix:semicolon
id|to-&gt;bv_offset
op_assign
id|from-&gt;bv_offset
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
(brace
r_char
op_star
id|vto
comma
op_star
id|vfrom
suffix:semicolon
id|vto
op_assign
id|page_address
c_func
(paren
id|to-&gt;bv_page
)paren
op_plus
id|to-&gt;bv_offset
suffix:semicolon
id|vfrom
op_assign
id|kmap
c_func
(paren
id|from-&gt;bv_page
)paren
op_plus
id|from-&gt;bv_offset
suffix:semicolon
id|memcpy
c_func
(paren
id|vto
comma
id|vfrom
comma
id|to-&gt;bv_len
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|from-&gt;bv_page
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * no pages bounced&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bio
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * at least one page was bounced, fill in possible non-highmem&n;&t; * pages&n;&t; */
id|bio_for_each_segment
c_func
(paren
id|from
comma
op_star
id|bio_orig
comma
id|i
)paren
(brace
id|to
op_assign
id|bio_iovec_idx
c_func
(paren
id|bio
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to-&gt;bv_page
)paren
(brace
id|to-&gt;bv_page
op_assign
id|from-&gt;bv_page
suffix:semicolon
id|to-&gt;bv_len
op_assign
id|from-&gt;bv_len
suffix:semicolon
id|to-&gt;bv_offset
op_assign
id|from-&gt;bv_offset
suffix:semicolon
)brace
)brace
id|bio-&gt;bi_bdev
op_assign
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_bdev
suffix:semicolon
id|bio-&gt;bi_flags
op_or_assign
(paren
l_int|1
op_lshift
id|BIO_BOUNCED
)paren
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_sector
suffix:semicolon
id|bio-&gt;bi_rw
op_assign
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_rw
suffix:semicolon
id|bio-&gt;bi_vcnt
op_assign
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_vcnt
suffix:semicolon
id|bio-&gt;bi_idx
op_assign
l_int|0
suffix:semicolon
id|bio-&gt;bi_size
op_assign
(paren
op_star
id|bio_orig
)paren
op_member_access_from_pointer
id|bi_size
suffix:semicolon
r_if
c_cond
(paren
id|pool
op_eq
id|page_pool
)paren
(brace
id|bio-&gt;bi_end_io
op_assign
id|bounce_end_io_write
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
id|bio-&gt;bi_end_io
op_assign
id|bounce_end_io_read
suffix:semicolon
)brace
r_else
(brace
id|bio-&gt;bi_end_io
op_assign
id|bounce_end_io_write_isa
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
id|bio-&gt;bi_end_io
op_assign
id|bounce_end_io_read_isa
suffix:semicolon
)brace
id|bio-&gt;bi_private
op_assign
op_star
id|bio_orig
suffix:semicolon
op_star
id|bio_orig
op_assign
id|bio
suffix:semicolon
)brace
DECL|function|blk_queue_bounce
r_void
id|blk_queue_bounce
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
op_star
id|bio_orig
)paren
(brace
id|mempool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/*&n;&t; * for non-isa bounce case, just check if the bounce pfn is equal&n;&t; * to or bigger than the highest pfn in the system -- in that case,&n;&t; * don&squot;t waste time iterating over bio segments&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|q-&gt;bounce_gfp
op_amp
id|GFP_DMA
)paren
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;bounce_pfn
op_ge
id|blk_max_pfn
)paren
r_return
suffix:semicolon
id|pool
op_assign
id|page_pool
suffix:semicolon
)brace
r_else
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|isa_page_pool
)paren
suffix:semicolon
id|pool
op_assign
id|isa_page_pool
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * slow path&n;&t; */
id|__blk_queue_bounce
c_func
(paren
id|q
comma
id|bio_orig
comma
id|pool
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_DEBUG_HIGHMEM) &amp;&amp; defined(CONFIG_HIGHMEM)
DECL|function|check_highmem_ptes
r_void
id|check_highmem_ptes
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
comma
id|type
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|KM_TYPE_NR
suffix:semicolon
id|type
op_increment
)paren
(brace
id|idx
op_assign
id|type
op_plus
id|KM_TYPE_NR
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
(paren
id|kmap_pte
op_minus
id|idx
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scheduling with KM_TYPE %d held!&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(HASHED_PAGE_VIRTUAL)
DECL|macro|PA_HASH_ORDER
mdefine_line|#define PA_HASH_ORDER&t;7
multiline_comment|/*&n; * Describes one page-&gt;virtual association&n; */
DECL|struct|page_address_map
r_struct
id|page_address_map
(brace
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|virtual
r_void
op_star
r_virtual
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * page_address_map freelist, allocated from page_address_maps.&n; */
DECL|variable|page_address_pool
r_static
r_struct
id|list_head
id|page_address_pool
suffix:semicolon
multiline_comment|/* freelist */
DECL|variable|pool_lock
r_static
id|spinlock_t
id|pool_lock
suffix:semicolon
multiline_comment|/* protects page_address_pool */
multiline_comment|/*&n; * Hash table bucket&n; */
DECL|struct|page_address_slot
r_static
r_struct
id|page_address_slot
(brace
DECL|member|lh
r_struct
id|list_head
id|lh
suffix:semicolon
multiline_comment|/* List of page_address_maps */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Protect this bucket&squot;s list */
DECL|variable|page_address_htable
)brace
id|____cacheline_aligned_in_smp
id|page_address_htable
(braket
l_int|1
op_lshift
id|PA_HASH_ORDER
)braket
suffix:semicolon
DECL|function|page_slot
r_static
r_struct
id|page_address_slot
op_star
id|page_slot
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
op_amp
id|page_address_htable
(braket
id|hash_ptr
c_func
(paren
id|page
comma
id|PA_HASH_ORDER
)paren
)braket
suffix:semicolon
)brace
DECL|function|page_address
r_void
op_star
id|page_address
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
r_struct
id|page_address_slot
op_star
id|pas
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
id|lowmem_page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|pas
op_assign
id|page_slot
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|pas-&gt;lh
)paren
)paren
(brace
r_struct
id|page_address_map
op_star
id|pam
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pam
comma
op_amp
id|pas-&gt;lh
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|pam-&gt;page
op_eq
id|page
)paren
(brace
id|ret
op_assign
id|pam
op_member_access_from_pointer
r_virtual
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
id|done
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|set_page_address
r_void
id|set_page_address
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_void
op_star
r_virtual
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|page_address_slot
op_star
id|pas
suffix:semicolon
r_struct
id|page_address_map
op_star
id|pam
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|pas
op_assign
id|page_slot
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
r_virtual
)paren
(brace
multiline_comment|/* Add */
id|BUG_ON
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|page_address_pool
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool_lock
comma
id|flags
)paren
suffix:semicolon
id|pam
op_assign
id|list_entry
c_func
(paren
id|page_address_pool.next
comma
r_struct
id|page_address_map
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|pam-&gt;list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool_lock
comma
id|flags
)paren
suffix:semicolon
id|pam-&gt;page
op_assign
id|page
suffix:semicolon
id|pam
op_member_access_from_pointer
r_virtual
op_assign
r_virtual
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|pam-&gt;list
comma
op_amp
id|pas-&gt;lh
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Remove */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|pam
comma
op_amp
id|pas-&gt;lh
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|pam-&gt;page
op_eq
id|page
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|pam-&gt;list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|pam-&gt;list
comma
op_amp
id|page_address_pool
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool_lock
comma
id|flags
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|done
suffix:colon
r_return
suffix:semicolon
)brace
DECL|variable|page_address_maps
r_static
r_struct
id|page_address_map
id|page_address_maps
(braket
id|LAST_PKMAP
)braket
suffix:semicolon
DECL|function|page_address_init
r_void
id|__init
id|page_address_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|page_address_pool
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
id|ARRAY_SIZE
c_func
(paren
id|page_address_maps
)paren
suffix:semicolon
id|i
op_increment
)paren
id|list_add
c_func
(paren
op_amp
id|page_address_maps
(braket
id|i
)braket
dot
id|list
comma
op_amp
id|page_address_pool
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
id|ARRAY_SIZE
c_func
(paren
id|page_address_htable
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|page_address_htable
(braket
id|i
)braket
dot
id|lh
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|page_address_htable
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|pool_lock
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* defined(CONFIG_HIGHMEM) &amp;&amp; !defined(WANT_PAGE_VIRTUAL) */
eof
