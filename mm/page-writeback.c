multiline_comment|/*&n; * mm/page-writeback.c.&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * Contains functions related to writing back dirty pages at the&n; * address_space level.&n; *&n; * 10Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
multiline_comment|/*&n; * The maximum number of pages to writeout in a single bdflush/kupdate&n; * operation.  We do this so we don&squot;t hold I_LOCK against an inode for&n; * enormous amounts of time, which would block a userspace task which has&n; * been forced to throttle against that inode.  Also, the code reevaluates&n; * the dirty each time it has written this many pages.&n; */
DECL|macro|MAX_WRITEBACK_PAGES
mdefine_line|#define MAX_WRITEBACK_PAGES&t;1024
multiline_comment|/*&n; * After a CPU has dirtied this many pages, balance_dirty_pages_ratelimited&n; * will look to see if it needs to force writeback or throttling.&n; */
DECL|variable|ratelimit_pages
r_static
r_int
id|ratelimit_pages
op_assign
l_int|32
suffix:semicolon
DECL|variable|total_pages
r_static
r_int
id|total_pages
suffix:semicolon
multiline_comment|/* The total number of pages in the machine. */
DECL|variable|dirty_exceeded
r_static
r_int
id|dirty_exceeded
suffix:semicolon
multiline_comment|/* Dirty mem may be over limit */
multiline_comment|/*&n; * When balance_dirty_pages decides that the caller needs to perform some&n; * non-background writeback, this is how many pages it will attempt to write.&n; * It should be somewhat larger than RATELIMIT_PAGES to ensure that reasonably&n; * large amounts of I/O are submitted.&n; */
DECL|function|sync_writeback_pages
r_static
r_inline
r_int
id|sync_writeback_pages
c_func
(paren
r_void
)paren
(brace
r_return
id|ratelimit_pages
op_plus
id|ratelimit_pages
op_div
l_int|2
suffix:semicolon
)brace
multiline_comment|/* The following parameters are exported via /proc/sys/vm */
multiline_comment|/*&n; * Start background writeback (via pdflush) at this percentage&n; */
DECL|variable|dirty_background_ratio
r_int
id|dirty_background_ratio
op_assign
l_int|10
suffix:semicolon
multiline_comment|/*&n; * The generator of dirty data starts writeback at this percentage&n; */
DECL|variable|vm_dirty_ratio
r_int
id|vm_dirty_ratio
op_assign
l_int|40
suffix:semicolon
multiline_comment|/*&n; * The interval between `kupdate&squot;-style writebacks, in centiseconds&n; * (hundredths of a second)&n; */
DECL|variable|dirty_writeback_centisecs
r_int
id|dirty_writeback_centisecs
op_assign
l_int|5
op_star
l_int|100
suffix:semicolon
multiline_comment|/*&n; * The longest number of centiseconds for which data is allowed to remain dirty&n; */
DECL|variable|dirty_expire_centisecs
r_int
id|dirty_expire_centisecs
op_assign
l_int|30
op_star
l_int|100
suffix:semicolon
multiline_comment|/* End of sysctl-exported parameters */
r_static
r_void
id|background_writeout
c_func
(paren
r_int
r_int
id|_min_pages
)paren
suffix:semicolon
multiline_comment|/*&n; * Work out the current dirty-memory clamping and background writeout&n; * thresholds.&n; *&n; * The main aim here is to lower them aggressively if there is a lot of mapped&n; * memory around.  To avoid stressing page reclaim with lots of unreclaimable&n; * pages.  It is better to clamp down on writers than to start swapping, and&n; * performing lots of scanning.&n; *&n; * We only allow 1/2 of the currently-unmapped memory to be dirtied.&n; *&n; * We don&squot;t permit the clamping level to fall below 5% - that is getting rather&n; * excessive.&n; *&n; * We make sure that the background writeout level is below the adjusted&n; * clamping level.&n; */
r_static
r_void
DECL|function|get_dirty_limits
id|get_dirty_limits
c_func
(paren
r_struct
id|page_state
op_star
id|ps
comma
r_int
op_star
id|background
comma
r_int
op_star
id|dirty
)paren
(brace
r_int
id|background_ratio
suffix:semicolon
multiline_comment|/* Percentages */
r_int
id|dirty_ratio
suffix:semicolon
r_int
id|unmapped_ratio
suffix:semicolon
id|get_page_state
c_func
(paren
id|ps
)paren
suffix:semicolon
id|unmapped_ratio
op_assign
l_int|100
op_minus
(paren
id|ps-&gt;nr_mapped
op_star
l_int|100
)paren
op_div
id|total_pages
suffix:semicolon
id|dirty_ratio
op_assign
id|vm_dirty_ratio
suffix:semicolon
r_if
c_cond
(paren
id|dirty_ratio
OG
id|unmapped_ratio
op_div
l_int|2
)paren
id|dirty_ratio
op_assign
id|unmapped_ratio
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|dirty_ratio
OL
l_int|5
)paren
id|dirty_ratio
op_assign
l_int|5
suffix:semicolon
id|background_ratio
op_assign
id|dirty_background_ratio
suffix:semicolon
r_if
c_cond
(paren
id|background_ratio
op_ge
id|dirty_ratio
)paren
id|background_ratio
op_assign
id|dirty_ratio
op_div
l_int|2
suffix:semicolon
op_star
id|background
op_assign
(paren
id|background_ratio
op_star
id|total_pages
)paren
op_div
l_int|100
suffix:semicolon
op_star
id|dirty
op_assign
(paren
id|dirty_ratio
op_star
id|total_pages
)paren
op_div
l_int|100
suffix:semicolon
)brace
multiline_comment|/*&n; * balance_dirty_pages() must be called by processes which are generating dirty&n; * data.  It looks at the number of dirty pages in the machine and will force&n; * the caller to perform writeback if the system is over `vm_dirty_ratio&squot;.&n; * If we&squot;re over `background_thresh&squot; then pdflush is woken to perform some&n; * writeout.&n; */
DECL|function|balance_dirty_pages
r_void
id|balance_dirty_pages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_struct
id|page_state
id|ps
suffix:semicolon
r_int
id|nr_reclaimable
suffix:semicolon
r_int
id|background_thresh
suffix:semicolon
r_int
id|dirty_thresh
suffix:semicolon
r_int
r_int
id|pages_written
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|write_chunk
op_assign
id|sync_writeback_pages
c_func
(paren
)paren
suffix:semicolon
r_struct
id|backing_dev_info
op_star
id|bdi
op_assign
id|mapping-&gt;backing_dev_info
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|bdi
op_assign
id|bdi
comma
dot
id|sync_mode
op_assign
id|WB_SYNC_NONE
comma
dot
id|older_than_this
op_assign
l_int|NULL
comma
dot
id|nr_to_write
op_assign
id|write_chunk
comma
)brace
suffix:semicolon
id|get_dirty_limits
c_func
(paren
op_amp
id|ps
comma
op_amp
id|background_thresh
comma
op_amp
id|dirty_thresh
)paren
suffix:semicolon
id|nr_reclaimable
op_assign
id|ps.nr_dirty
op_plus
id|ps.nr_unstable
suffix:semicolon
r_if
c_cond
(paren
id|nr_reclaimable
op_plus
id|ps.nr_writeback
op_le
id|dirty_thresh
)paren
r_break
suffix:semicolon
id|dirty_exceeded
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Note: nr_reclaimable denotes nr_dirty + nr_unstable.&n;&t;&t; * Unstable writes are a feature of certain networked&n;&t;&t; * filesystems (i.e. NFS) in which data may have been&n;&t;&t; * written to the server&squot;s write cache, but has not yet&n;&t;&t; * been flushed to permanent storage.&n;&t;&t; */
r_if
c_cond
(paren
id|nr_reclaimable
)paren
(brace
id|writeback_inodes
c_func
(paren
op_amp
id|wbc
)paren
suffix:semicolon
id|get_dirty_limits
c_func
(paren
op_amp
id|ps
comma
op_amp
id|background_thresh
comma
op_amp
id|dirty_thresh
)paren
suffix:semicolon
id|nr_reclaimable
op_assign
id|ps.nr_dirty
op_plus
id|ps.nr_unstable
suffix:semicolon
r_if
c_cond
(paren
id|nr_reclaimable
op_plus
id|ps.nr_writeback
op_le
id|dirty_thresh
)paren
r_break
suffix:semicolon
id|pages_written
op_add_assign
id|write_chunk
op_minus
id|wbc.nr_to_write
suffix:semicolon
r_if
c_cond
(paren
id|pages_written
op_ge
id|write_chunk
)paren
r_break
suffix:semicolon
multiline_comment|/* We&squot;ve done our duty */
)brace
id|blk_congestion_wait
c_func
(paren
id|WRITE
comma
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_reclaimable
op_plus
id|ps.nr_writeback
op_le
id|dirty_thresh
)paren
id|dirty_exceeded
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|writeback_in_progress
c_func
(paren
id|bdi
)paren
op_logical_and
id|nr_reclaimable
OG
id|background_thresh
)paren
id|pdflush_operation
c_func
(paren
id|background_writeout
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * balance_dirty_pages_ratelimited - balance dirty memory state&n; * @mapping - address_space which was dirtied&n; *&n; * Processes which are dirtying memory should call in here once for each page&n; * which was newly dirtied.  The function will periodically check the system&squot;s&n; * dirty state and will initiate writeback if needed.&n; *&n; * On really big machines, get_page_state is expensive, so try to avoid calling&n; * it too often (ratelimiting).  But once we&squot;re over the dirty memory limit we&n; * decrease the ratelimiting by a lot, to prevent individual processes from&n; * overshooting the limit by (ratelimit_pages) each.&n; */
DECL|function|balance_dirty_pages_ratelimited
r_void
id|balance_dirty_pages_ratelimited
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_int
comma
id|ratelimits
)paren
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_int
id|ratelimit
suffix:semicolon
id|ratelimit
op_assign
id|ratelimit_pages
suffix:semicolon
r_if
c_cond
(paren
id|dirty_exceeded
)paren
id|ratelimit
op_assign
l_int|8
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|per_cpu
c_func
(paren
id|ratelimits
comma
id|cpu
)paren
op_increment
op_ge
id|ratelimit
)paren
(brace
id|per_cpu
c_func
(paren
id|ratelimits
comma
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
id|balance_dirty_pages
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|balance_dirty_pages_ratelimited
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|balance_dirty_pages_ratelimited
)paren
suffix:semicolon
multiline_comment|/*&n; * writeback at least _min_pages, and keep writing until the amount of dirty&n; * memory is less than the background threshold, or until we&squot;re all clean.&n; */
DECL|function|background_writeout
r_static
r_void
id|background_writeout
c_func
(paren
r_int
r_int
id|_min_pages
)paren
(brace
r_int
id|min_pages
op_assign
id|_min_pages
suffix:semicolon
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|bdi
op_assign
l_int|NULL
comma
dot
id|sync_mode
op_assign
id|WB_SYNC_NONE
comma
dot
id|older_than_this
op_assign
l_int|NULL
comma
dot
id|nr_to_write
op_assign
l_int|0
comma
dot
id|nonblocking
op_assign
l_int|1
comma
)brace
suffix:semicolon
id|CHECK_EMERGENCY_SYNC
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|page_state
id|ps
suffix:semicolon
r_int
id|background_thresh
suffix:semicolon
r_int
id|dirty_thresh
suffix:semicolon
id|get_dirty_limits
c_func
(paren
op_amp
id|ps
comma
op_amp
id|background_thresh
comma
op_amp
id|dirty_thresh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ps.nr_dirty
op_plus
id|ps.nr_unstable
OL
id|background_thresh
op_logical_and
id|min_pages
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|wbc.encountered_congestion
op_assign
l_int|0
suffix:semicolon
id|wbc.nr_to_write
op_assign
id|MAX_WRITEBACK_PAGES
suffix:semicolon
id|writeback_inodes
c_func
(paren
op_amp
id|wbc
)paren
suffix:semicolon
id|min_pages
op_sub_assign
id|MAX_WRITEBACK_PAGES
op_minus
id|wbc.nr_to_write
suffix:semicolon
r_if
c_cond
(paren
id|wbc.nr_to_write
OG
l_int|0
)paren
(brace
multiline_comment|/* Wrote less than expected */
r_if
c_cond
(paren
id|wbc.encountered_congestion
)paren
id|blk_congestion_wait
c_func
(paren
id|WRITE
comma
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Start writeback of `nr_pages&squot; pages.  If `nr_pages&squot; is zero, write back&n; * the whole world.  Returns 0 if a pdflush thread was dispatched.  Returns&n; * -1 if all pdflush threads were busy.&n; */
DECL|function|wakeup_bdflush
r_int
id|wakeup_bdflush
c_func
(paren
r_int
id|nr_pages
)paren
(brace
r_if
c_cond
(paren
id|nr_pages
op_eq
l_int|0
)paren
(brace
r_struct
id|page_state
id|ps
suffix:semicolon
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
id|nr_pages
op_assign
id|ps.nr_dirty
suffix:semicolon
)brace
r_return
id|pdflush_operation
c_func
(paren
id|background_writeout
comma
id|nr_pages
)paren
suffix:semicolon
)brace
DECL|variable|wb_timer
r_static
r_struct
id|timer_list
id|wb_timer
suffix:semicolon
multiline_comment|/*&n; * Periodic writeback of &quot;old&quot; data.&n; *&n; * Define &quot;old&quot;: the first time one of an inode&squot;s pages is dirtied, we mark the&n; * dirtying-time in the inode&squot;s address_space.  So this periodic writeback code&n; * just walks the superblock inode list, writing back any inodes which are&n; * older than a specific point in time.&n; *&n; * Try to run once per dirty_writeback_centisecs.  But if a writeback event&n; * takes longer than a dirty_writeback_centisecs interval, then leave a&n; * one-second gap.&n; *&n; * older_than_this takes precedence over nr_to_write.  So we&squot;ll only write back&n; * all dirty pages if they are all attached to &quot;old&quot; mappings.&n; */
DECL|function|wb_kupdate
r_static
r_void
id|wb_kupdate
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|oldest_jif
suffix:semicolon
r_int
r_int
id|start_jif
suffix:semicolon
r_int
r_int
id|next_jif
suffix:semicolon
r_int
id|nr_to_write
suffix:semicolon
r_struct
id|page_state
id|ps
suffix:semicolon
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|bdi
op_assign
l_int|NULL
comma
dot
id|sync_mode
op_assign
id|WB_SYNC_NONE
comma
dot
id|older_than_this
op_assign
op_amp
id|oldest_jif
comma
dot
id|nr_to_write
op_assign
l_int|0
comma
dot
id|nonblocking
op_assign
l_int|1
comma
dot
id|for_kupdate
op_assign
l_int|1
comma
)brace
suffix:semicolon
id|sync_supers
c_func
(paren
)paren
suffix:semicolon
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
id|oldest_jif
op_assign
id|jiffies
op_minus
(paren
id|dirty_expire_centisecs
op_star
id|HZ
)paren
op_div
l_int|100
suffix:semicolon
id|start_jif
op_assign
id|jiffies
suffix:semicolon
id|next_jif
op_assign
id|start_jif
op_plus
(paren
id|dirty_writeback_centisecs
op_star
id|HZ
)paren
op_div
l_int|100
suffix:semicolon
id|nr_to_write
op_assign
id|ps.nr_dirty
op_plus
id|ps.nr_unstable
suffix:semicolon
r_while
c_loop
(paren
id|nr_to_write
OG
l_int|0
)paren
(brace
id|wbc.encountered_congestion
op_assign
l_int|0
suffix:semicolon
id|wbc.nr_to_write
op_assign
id|MAX_WRITEBACK_PAGES
suffix:semicolon
id|writeback_inodes
c_func
(paren
op_amp
id|wbc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wbc.nr_to_write
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|wbc.encountered_congestion
)paren
id|blk_congestion_wait
c_func
(paren
id|WRITE
comma
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
multiline_comment|/* All the old data is written */
)brace
id|nr_to_write
op_sub_assign
id|MAX_WRITEBACK_PAGES
op_minus
id|wbc.nr_to_write
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|next_jif
comma
id|jiffies
op_plus
id|HZ
)paren
)paren
id|next_jif
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|wb_timer
comma
id|next_jif
)paren
suffix:semicolon
)brace
DECL|function|wb_timer_fn
r_static
r_void
id|wb_timer_fn
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_if
c_cond
(paren
id|pdflush_operation
c_func
(paren
id|wb_kupdate
comma
l_int|0
)paren
OL
l_int|0
)paren
id|mod_timer
c_func
(paren
op_amp
id|wb_timer
comma
id|jiffies
op_plus
id|HZ
)paren
suffix:semicolon
multiline_comment|/* delay 1 second */
)brace
multiline_comment|/*&n; * If ratelimit_pages is too high then we can get into dirty-data overload&n; * if a large number of processes all perform writes at the same time.&n; * If it is too low then SMP machines will call the (expensive) get_page_state&n; * too often.&n; *&n; * Here we set ratelimit_pages to a level which ensures that when all CPUs are&n; * dirtying in parallel, we cannot go more than 3% (1/32) over the dirty memory&n; * thresholds before writeback cuts in.&n; *&n; * But the limit should not be set too high.  Because it also controls the&n; * amount of memory which the balance_dirty_pages() caller has to write back.&n; * If this is too large then the caller will block on the IO queue all the&n; * time.  So limit it to four megabytes - the balance_dirty_pages() caller&n; * will write six megabyte chunks, max.&n; */
DECL|function|set_ratelimit
r_static
r_void
id|set_ratelimit
c_func
(paren
r_void
)paren
(brace
id|ratelimit_pages
op_assign
id|total_pages
op_div
(paren
id|num_online_cpus
c_func
(paren
)paren
op_star
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ratelimit_pages
OL
l_int|16
)paren
id|ratelimit_pages
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|ratelimit_pages
op_star
id|PAGE_CACHE_SIZE
OG
l_int|4096
op_star
l_int|1024
)paren
id|ratelimit_pages
op_assign
(paren
l_int|4096
op_star
l_int|1024
)paren
op_div
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_static
r_int
DECL|function|ratelimit_handler
id|ratelimit_handler
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|u
comma
r_void
op_star
id|v
)paren
(brace
id|set_ratelimit
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ratelimit_nb
r_static
r_struct
id|notifier_block
id|ratelimit_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|ratelimit_handler
comma
dot
id|next
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * If the machine has a large highmem:lowmem ratio then scale back the default&n; * dirty memory thresholds: allowing too much dirty highmem pins an excessive&n; * number of buffer_heads.&n; */
DECL|function|page_writeback_init
r_void
id|__init
id|page_writeback_init
c_func
(paren
r_void
)paren
(brace
r_int
id|buffer_pages
op_assign
id|nr_free_buffer_pages
c_func
(paren
)paren
suffix:semicolon
r_int
id|correction
suffix:semicolon
id|total_pages
op_assign
id|nr_free_pagecache_pages
c_func
(paren
)paren
suffix:semicolon
id|correction
op_assign
(paren
l_int|100
op_star
l_int|4
op_star
id|buffer_pages
)paren
op_div
id|total_pages
suffix:semicolon
r_if
c_cond
(paren
id|correction
OL
l_int|100
)paren
(brace
id|dirty_background_ratio
op_mul_assign
id|correction
suffix:semicolon
id|dirty_background_ratio
op_div_assign
l_int|100
suffix:semicolon
id|vm_dirty_ratio
op_mul_assign
id|correction
suffix:semicolon
id|vm_dirty_ratio
op_div_assign
l_int|100
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|wb_timer
)paren
suffix:semicolon
id|wb_timer.expires
op_assign
id|jiffies
op_plus
(paren
id|dirty_writeback_centisecs
op_star
id|HZ
)paren
op_div
l_int|100
suffix:semicolon
id|wb_timer.data
op_assign
l_int|0
suffix:semicolon
id|wb_timer.function
op_assign
id|wb_timer_fn
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|wb_timer
)paren
suffix:semicolon
id|set_ratelimit
c_func
(paren
)paren
suffix:semicolon
id|register_cpu_notifier
c_func
(paren
op_amp
id|ratelimit_nb
)paren
suffix:semicolon
)brace
DECL|function|do_writepages
r_int
id|do_writepages
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
)paren
(brace
r_if
c_cond
(paren
id|mapping-&gt;a_ops-&gt;writepages
)paren
r_return
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|writepages
c_func
(paren
id|mapping
comma
id|wbc
)paren
suffix:semicolon
r_return
id|generic_writepages
c_func
(paren
id|mapping
comma
id|wbc
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * write_one_page - write out a single page and optionally wait on I/O&n; *&n; * @page - the page to write&n; * @wait - if true, wait on writeout&n; *&n; * The page must be locked by the caller and will be unlocked upon return.&n; *&n; * write_one_page() returns a negative error code if I/O failed.&n; */
DECL|function|write_one_page
r_int
id|write_one_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|wait
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|writeback_control
id|wbc
op_assign
(brace
dot
id|sync_mode
op_assign
id|WB_SYNC_ALL
comma
)brace
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
op_logical_and
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_clear_page_dirty
c_func
(paren
id|page
)paren
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|mapping-&gt;locked_pages
)paren
suffix:semicolon
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|ret
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|writepage
c_func
(paren
id|page
comma
op_amp
id|wbc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
id|wait
)paren
(brace
id|wait_on_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|mapping-&gt;clean_pages
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
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
DECL|variable|write_one_page
id|EXPORT_SYMBOL
c_func
(paren
id|write_one_page
)paren
suffix:semicolon
multiline_comment|/*&n; * Add a page to the dirty page list.&n; *&n; * It is a sad fact of life that this function is called from several places&n; * deeply under spinlocking.  It may not sleep.&n; *&n; * If the page has buffers, the uptodate buffers are set dirty, to preserve&n; * dirty-state coherency between the page and the buffers.  It the page does&n; * not have buffers then when they are later attached they will all be set&n; * dirty.&n; *&n; * The buffers are dirtied before the page is dirtied.  There&squot;s a small race&n; * window in which a writepage caller may see the page cleanness but not the&n; * buffer dirtiness.  That&squot;s fine.  If this code were to set the page dirty&n; * before the buffers, a concurrent writepage caller could clear the page dirty&n; * bit, see a bunch of clean buffers and we&squot;d end up with dirty buffers/clean&n; * page on the dirty page list.&n; *&n; * There is also a small window where the page is dirty, and not on dirty_pages.&n; * Also a possibility that by the time the page is added to dirty_pages, it has&n; * been set clean.  The page lists are somewhat approximate in this regard.&n; * It&squot;s better to have clean pages accidentally attached to dirty_pages than to&n; * leave dirty pages attached to clean_pages.&n; *&n; * We use private_lock to lock against try_to_free_buffers while using the&n; * page&squot;s buffer list.  Also use this to protect against clean buffers being&n; * added to the page after it was set dirty.&n; *&n; * FIXME: may need to call -&gt;reservepage here as well.  That&squot;s rather up to the&n; * address_space though.&n; *&n; * For now, we treat swapper_space specially.  It doesn&squot;t use the normal&n; * block a_ops.&n; *&n; * FIXME: this should move over to fs/buffer.c - buffer_heads have no business in mm/&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|function|__set_page_dirty_buffers
r_int
id|__set_page_dirty_buffers
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
r_const
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mapping
op_eq
l_int|NULL
)paren
(brace
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|buffer_error
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mapping-&gt;private_lock
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
)paren
id|set_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
r_else
id|buffer_error
c_func
(paren
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
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;private_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TestSetPageDirty
c_func
(paren
id|page
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
(brace
multiline_comment|/* Race with truncate? */
r_if
c_cond
(paren
op_logical_neg
id|mapping-&gt;backing_dev_info-&gt;memory_backed
)paren
id|inc_page_state
c_func
(paren
id|nr_dirty
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|mapping-&gt;dirty_pages
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|__mark_inode_dirty
c_func
(paren
id|mapping-&gt;host
comma
id|I_DIRTY_PAGES
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__set_page_dirty_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|__set_page_dirty_buffers
)paren
suffix:semicolon
multiline_comment|/*&n; * For address_spaces which do not use buffers.  Just set the page&squot;s dirty bit&n; * and move it to the dirty_pages list.  Also perform space reservation if&n; * required.&n; *&n; * __set_page_dirty_nobuffers() may return -ENOSPC.  But if it does, the page&n; * is still safe, as long as it actually manages to find some blocks at&n; * writeback time.&n; *&n; * This is also used when a single buffer is being dirtied: we want to set the&n; * page dirty in that case, but not all the buffers.  This is a &quot;bottom-up&quot;&n; * dirtying, whereas __set_page_dirty_buffers() is a &quot;top-down&quot; dirtying.&n; */
DECL|function|__set_page_dirty_nobuffers
r_int
id|__set_page_dirty_nobuffers
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TestSetPageDirty
c_func
(paren
id|page
)paren
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
id|mapping
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
(brace
multiline_comment|/* Race with truncate? */
id|BUG_ON
c_func
(paren
id|page-&gt;mapping
op_ne
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping-&gt;backing_dev_info-&gt;memory_backed
)paren
id|inc_page_state
c_func
(paren
id|nr_dirty
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|mapping-&gt;dirty_pages
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|__mark_inode_dirty
c_func
(paren
id|mapping-&gt;host
comma
id|I_DIRTY_PAGES
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__set_page_dirty_nobuffers
id|EXPORT_SYMBOL
c_func
(paren
id|__set_page_dirty_nobuffers
)paren
suffix:semicolon
multiline_comment|/*&n; * set_page_dirty() is racy if the caller has no reference against&n; * page-&gt;mapping-&gt;host, and if the page is unlocked.  This is because another&n; * CPU could truncate the page off the mapping and then free the mapping.&n; *&n; * Usually, the page _is_ locked, or the caller is a user-space process which&n; * holds a reference on the inode by having an open file.&n; *&n; * In other cases, the page should be locked before running set_page_dirty().&n; */
DECL|function|set_page_dirty_lock
r_int
id|set_page_dirty_lock
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|ret
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
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
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear a page&squot;s dirty flag, while caring for dirty memory accounting. &n; * Returns true if the page was previously dirty.&n; */
DECL|function|test_clear_page_dirty
r_int
id|test_clear_page_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|TestClearPageDirty
c_func
(paren
id|page
)paren
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
id|mapping
op_logical_and
op_logical_neg
id|mapping-&gt;backing_dev_info-&gt;memory_backed
)paren
id|dec_page_state
c_func
(paren
id|nr_dirty
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
DECL|variable|test_clear_page_dirty
id|EXPORT_SYMBOL
c_func
(paren
id|test_clear_page_dirty
)paren
suffix:semicolon
eof
