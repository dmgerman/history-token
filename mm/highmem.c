multiline_comment|/*&n; * High memory handling common code and variables.&n; *&n; * (C) 1999 Andrea Arcangeli, SuSE GmbH, andrea@suse.de&n; *          Gerhard Wichert, Siemens AG, Gerhard.Wichert@pdb.siemens.de&n; *&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with&n; * 64-bit physical space. With current x86 CPUs this&n; * means up to 64 Gigabytes physical RAM.&n; *&n; * Rewrote high memory support to move the page cache into&n; * high memory. Implemented permanent (schedulable) kmaps&n; * based on Linus&squot; idea.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
multiline_comment|/*&n; * Virtual_count is not a pure &quot;count&quot;.&n; *  0 means that it is not mapped, and has not been mapped&n; *    since a TLB flush - it is usable.&n; *  1 means that there are no users, but it has been mapped&n; *    since the last TLB flush - so we can&squot;t use it.&n; *  n means that there are (n-1) current users of it.&n; */
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
DECL|variable|kmap_lock
r_static
id|spinlock_t
id|kmap_lock
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
id|page
op_member_access_from_pointer
r_virtual
op_assign
l_int|NULL
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
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
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
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
id|page
op_member_access_from_pointer
r_virtual
)paren
r_return
(paren
r_int
r_int
)paren
id|page
op_member_access_from_pointer
r_virtual
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
id|page
op_member_access_from_pointer
r_virtual
op_assign
(paren
r_void
op_star
)paren
id|vaddr
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
id|page
op_member_access_from_pointer
r_virtual
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
id|page
op_member_access_from_pointer
r_virtual
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
mdefine_line|#define POOL_SIZE 32
multiline_comment|/*&n; * This lock gets no contention at all, normally.&n; */
DECL|variable|emergency_lock
r_static
id|spinlock_t
id|emergency_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|nr_emergency_pages
r_int
id|nr_emergency_pages
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|emergency_pages
)paren
suffix:semicolon
DECL|variable|nr_emergency_bhs
r_int
id|nr_emergency_bhs
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|emergency_bhs
)paren
suffix:semicolon
multiline_comment|/*&n; * Simple bounce buffer support for highmem pages.&n; * This will be moved to the block layer in 2.5.&n; */
DECL|function|copy_from_high_bh
r_static
r_inline
r_void
id|copy_from_high_bh
(paren
r_struct
id|buffer_head
op_star
id|to
comma
r_struct
id|buffer_head
op_star
id|from
)paren
(brace
r_struct
id|page
op_star
id|p_from
suffix:semicolon
r_char
op_star
id|vfrom
suffix:semicolon
id|p_from
op_assign
id|from-&gt;b_page
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
id|p_from
comma
id|KM_BOUNCE_WRITE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to-&gt;b_data
comma
id|vfrom
op_plus
id|bh_offset
c_func
(paren
id|from
)paren
comma
id|to-&gt;b_size
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_BOUNCE_WRITE
)paren
suffix:semicolon
)brace
DECL|function|copy_to_high_bh_irq
r_static
r_inline
r_void
id|copy_to_high_bh_irq
(paren
r_struct
id|buffer_head
op_star
id|to
comma
r_struct
id|buffer_head
op_star
id|from
)paren
(brace
r_struct
id|page
op_star
id|p_to
suffix:semicolon
r_char
op_star
id|vto
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|p_to
op_assign
id|to-&gt;b_page
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
id|p_to
comma
id|KM_BOUNCE_READ
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vto
op_plus
id|bh_offset
c_func
(paren
id|to
)paren
comma
id|from-&gt;b_data
comma
id|to-&gt;b_size
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
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|bounce_end_io
r_static
r_inline
r_void
id|bounce_end_io
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh_orig
op_assign
(paren
r_struct
id|buffer_head
op_star
)paren
(paren
id|bh-&gt;b_private
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|bh_orig
op_member_access_from_pointer
id|b_end_io
c_func
(paren
id|bh_orig
comma
id|uptodate
)paren
suffix:semicolon
id|page
op_assign
id|bh-&gt;b_page
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emergency_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_emergency_pages
op_ge
id|POOL_SIZE
)paren
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t; * We are abusing page-&gt;list to manage&n;&t;&t; * the highmem emergency pool:&n;&t;&t; */
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|emergency_pages
)paren
suffix:semicolon
id|nr_emergency_pages
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_emergency_bhs
op_ge
id|POOL_SIZE
)paren
(brace
macro_line|#ifdef HIGHMEM_DEBUG
multiline_comment|/* Don&squot;t clobber the constructed slab cache */
id|init_waitqueue_head
c_func
(paren
op_amp
id|bh-&gt;b_wait
)paren
suffix:semicolon
macro_line|#endif
id|kmem_cache_free
c_func
(paren
id|bh_cachep
comma
id|bh
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Ditto in the bh case, here we abuse b_inode_buffers:&n;&t;&t; */
id|list_add
c_func
(paren
op_amp
id|bh-&gt;b_inode_buffers
comma
op_amp
id|emergency_bhs
)paren
suffix:semicolon
id|nr_emergency_bhs
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emergency_lock
comma
id|flags
)paren
suffix:semicolon
)brace
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
id|spin_lock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr_emergency_pages
OL
id|POOL_SIZE
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;couldn&squot;t refill highmem emergency pages&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|emergency_pages
)paren
suffix:semicolon
id|nr_emergency_pages
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nr_emergency_bhs
OL
id|POOL_SIZE
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|kmem_cache_alloc
c_func
(paren
id|bh_cachep
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;couldn&squot;t refill highmem emergency bhs&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|bh-&gt;b_inode_buffers
comma
op_amp
id|emergency_bhs
)paren
suffix:semicolon
id|nr_emergency_bhs
op_increment
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;allocated %d pages and %d bhs reserved for the highmem bounces&bslash;n&quot;
comma
id|nr_emergency_pages
comma
id|nr_emergency_bhs
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
DECL|function|bounce_end_io_write
r_static
r_void
id|bounce_end_io_write
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
id|bounce_end_io
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
)brace
DECL|function|bounce_end_io_read
r_static
r_void
id|bounce_end_io_read
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh_orig
op_assign
(paren
r_struct
id|buffer_head
op_star
)paren
(paren
id|bh-&gt;b_private
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uptodate
)paren
id|copy_to_high_bh_irq
c_func
(paren
id|bh_orig
comma
id|bh
)paren
suffix:semicolon
id|bounce_end_io
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
)brace
DECL|function|alloc_bounce_page
r_struct
id|page
op_star
id|alloc_bounce_page
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|repeat_alloc
suffix:colon
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_NOHIGHIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_return
id|page
suffix:semicolon
multiline_comment|/*&n;&t; * No luck. First, kick the VM so it doesnt idle around while&n;&t; * we are using up our emergency rations.&n;&t; */
id|wakeup_bdflush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to allocate from the emergency pool.&n;&t; */
id|tmp
op_assign
op_amp
id|emergency_pages
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|tmp
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|tmp-&gt;next
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|tmp-&gt;next
)paren
suffix:semicolon
id|nr_emergency_pages
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_return
id|page
suffix:semicolon
multiline_comment|/* we need to wait I/O completion */
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat_alloc
suffix:semicolon
)brace
DECL|function|alloc_bounce_bh
r_struct
id|buffer_head
op_star
id|alloc_bounce_bh
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|repeat_alloc
suffix:colon
id|bh
op_assign
id|kmem_cache_alloc
c_func
(paren
id|bh_cachep
comma
id|SLAB_NOHIGHIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
r_return
id|bh
suffix:semicolon
multiline_comment|/*&n;&t; * No luck. First, kick the VM so it doesnt idle around while&n;&t; * we are using up our emergency rations.&n;&t; */
id|wakeup_bdflush
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to allocate from the emergency pool.&n;&t; */
id|tmp
op_assign
op_amp
id|emergency_bhs
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|tmp
)paren
)paren
(brace
id|bh
op_assign
id|list_entry
c_func
(paren
id|tmp-&gt;next
comma
r_struct
id|buffer_head
comma
id|b_inode_buffers
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|tmp-&gt;next
)paren
suffix:semicolon
id|nr_emergency_bhs
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|emergency_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
r_return
id|bh
suffix:semicolon
multiline_comment|/* we need to wait I/O completion */
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat_alloc
suffix:semicolon
)brace
DECL|function|create_bounce
r_struct
id|buffer_head
op_star
id|create_bounce
c_func
(paren
r_int
id|rw
comma
r_struct
id|buffer_head
op_star
id|bh_orig
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|bh_orig-&gt;b_page
)paren
)paren
r_return
id|bh_orig
suffix:semicolon
id|bh
op_assign
id|alloc_bounce_bh
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is wasteful for 1k buffers, but this is a stopgap measure&n;&t; * and we are being ineffective anyway. This approach simplifies&n;&t; * things immensly. On boxes with more than 4GB RAM this should&n;&t; * not be an issue anyway.&n;&t; */
id|page
op_assign
id|alloc_bounce_page
c_func
(paren
)paren
suffix:semicolon
id|set_bh_page
c_func
(paren
id|bh
comma
id|page
comma
l_int|0
)paren
suffix:semicolon
id|bh-&gt;b_next
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|bh_orig-&gt;b_blocknr
suffix:semicolon
id|bh-&gt;b_size
op_assign
id|bh_orig-&gt;b_size
suffix:semicolon
id|bh-&gt;b_list
op_assign
op_minus
l_int|1
suffix:semicolon
id|bh-&gt;b_dev
op_assign
id|bh_orig-&gt;b_dev
suffix:semicolon
id|bh-&gt;b_count
op_assign
id|bh_orig-&gt;b_count
suffix:semicolon
id|bh-&gt;b_rdev
op_assign
id|bh_orig-&gt;b_rdev
suffix:semicolon
id|bh-&gt;b_state
op_assign
id|bh_orig-&gt;b_state
suffix:semicolon
macro_line|#ifdef HIGHMEM_DEBUG
id|bh-&gt;b_flushtime
op_assign
id|jiffies
suffix:semicolon
id|bh-&gt;b_next_free
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_prev_free
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* bh-&gt;b_this_page */
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_pprev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* bh-&gt;b_page */
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
(brace
id|bh-&gt;b_end_io
op_assign
id|bounce_end_io_write
suffix:semicolon
id|copy_from_high_bh
c_func
(paren
id|bh
comma
id|bh_orig
)paren
suffix:semicolon
)brace
r_else
id|bh-&gt;b_end_io
op_assign
id|bounce_end_io_read
suffix:semicolon
id|bh-&gt;b_private
op_assign
(paren
r_void
op_star
)paren
id|bh_orig
suffix:semicolon
id|bh-&gt;b_rsector
op_assign
id|bh_orig-&gt;b_rsector
suffix:semicolon
macro_line|#ifdef HIGHMEM_DEBUG
id|memset
c_func
(paren
op_amp
id|bh-&gt;b_wait
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|bh-&gt;b_wait
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|bh
suffix:semicolon
)brace
eof
