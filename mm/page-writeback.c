multiline_comment|/*&n; * mm/page-writeback.c.&n; *&n; * Copyright (C) 2002, Linus Torvalds.&n; *&n; * Contains functions related to writing back dirty pages at the&n; * address_space level.&n; *&n; * 10Apr2002&t;akpm@zip.com.au&n; *&t;&t;Initial version&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/writeback.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
multiline_comment|/*&n; * The maximum number of pages to writeout in a single bdflush/kupdate&n; * operation.  We do this so we don&squot;t hold I_LOCK against an inode for&n; * enormous amounts of time, which would block a userspace task which has&n; * been forced to throttle against that inode.&n; */
DECL|macro|MAX_WRITEBACK_PAGES
mdefine_line|#define MAX_WRITEBACK_PAGES&t;1024
multiline_comment|/*&n; * Memory thresholds, in percentages&n; * FIXME: expose these via /proc or whatever.&n; */
multiline_comment|/*&n; * Start background writeback (via pdflush) at this level&n; */
DECL|variable|dirty_background_ratio
r_static
r_int
id|dirty_background_ratio
op_assign
l_int|40
suffix:semicolon
multiline_comment|/*&n; * The generator of dirty data starts async writeback at this level&n; */
DECL|variable|dirty_async_ratio
r_static
r_int
id|dirty_async_ratio
op_assign
l_int|50
suffix:semicolon
multiline_comment|/*&n; * The generator of dirty data performs sync writeout at this level&n; */
DECL|variable|dirty_sync_ratio
r_static
r_int
id|dirty_sync_ratio
op_assign
l_int|60
suffix:semicolon
r_static
r_void
id|background_writeout
c_func
(paren
r_int
r_int
id|unused
)paren
suffix:semicolon
multiline_comment|/*&n; * balance_dirty_pages() must be called by processes which are&n; * generating dirty data.  It looks at the number of dirty pages&n; * in the machine and either:&n; *&n; * - Starts background writeback or&n; * - Causes the caller to perform async writeback or&n; * - Causes the caller to perform synchronous writeback, then&n; *   tells a pdflush thread to perform more writeback or&n; * - Does nothing at all.&n; *&n; * balance_dirty_pages() can sleep.&n; *&n; * FIXME: WB_SYNC_LAST doesn&squot;t actually work.  It waits on the last dirty&n; * inode on the superblock list.  It should wait when nr_to_write is&n; * exhausted.  Doesn&squot;t seem to matter.&n; */
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
r_const
r_int
id|tot
op_assign
id|nr_free_pagecache_pages
c_func
(paren
)paren
suffix:semicolon
r_struct
id|page_state
id|ps
suffix:semicolon
r_int
id|background_thresh
comma
id|async_thresh
comma
id|sync_thresh
suffix:semicolon
r_int
r_int
id|dirty_and_writeback
suffix:semicolon
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
id|dirty_and_writeback
op_assign
id|ps.nr_dirty
op_plus
id|ps.nr_writeback
suffix:semicolon
id|background_thresh
op_assign
(paren
id|dirty_background_ratio
op_star
id|tot
)paren
op_div
l_int|100
suffix:semicolon
id|async_thresh
op_assign
(paren
id|dirty_async_ratio
op_star
id|tot
)paren
op_div
l_int|100
suffix:semicolon
id|sync_thresh
op_assign
(paren
id|dirty_sync_ratio
op_star
id|tot
)paren
op_div
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|dirty_and_writeback
OG
id|sync_thresh
)paren
(brace
r_int
id|nr_to_write
op_assign
l_int|1500
suffix:semicolon
id|writeback_unlocked_inodes
c_func
(paren
op_amp
id|nr_to_write
comma
id|WB_SYNC_LAST
comma
l_int|NULL
)paren
suffix:semicolon
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dirty_and_writeback
OG
id|async_thresh
)paren
(brace
r_int
id|nr_to_write
op_assign
l_int|1500
suffix:semicolon
id|writeback_unlocked_inodes
c_func
(paren
op_amp
id|nr_to_write
comma
id|WB_SYNC_NONE
comma
l_int|NULL
)paren
suffix:semicolon
id|get_page_state
c_func
(paren
op_amp
id|ps
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|writeback_in_progress
c_func
(paren
id|mapping-&gt;backing_dev_info
)paren
op_logical_and
id|ps.nr_dirty
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
multiline_comment|/**&n; * balance_dirty_pages_ratelimited - balance dirty memory state&n; * @mapping - address_space which was dirtied&n; *&n; * Processes which are dirtying memory should call in here once for each page&n; * which was newly dirtied.  The function will periodically check the system&squot;s&n; * dirty state and will initiate writeback if needed.&n; *&n; * balance_dirty_pages_ratelimited() may sleep.&n; */
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
r_struct
id|rate_limit_struct
(brace
r_int
id|count
suffix:semicolon
)brace
id|____cacheline_aligned
id|ratelimits
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|cpu
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
id|ratelimits
(braket
id|cpu
)braket
dot
id|count
op_increment
op_ge
l_int|1000
)paren
(brace
id|ratelimits
(braket
id|cpu
)braket
dot
id|count
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
r_const
r_int
id|tot
op_assign
id|nr_free_pagecache_pages
c_func
(paren
)paren
suffix:semicolon
r_const
r_int
id|background_thresh
op_assign
(paren
id|dirty_background_ratio
op_star
id|tot
)paren
op_div
l_int|100
suffix:semicolon
r_int
id|min_pages
op_assign
id|_min_pages
suffix:semicolon
r_int
id|nr_to_write
suffix:semicolon
r_do
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
r_if
c_cond
(paren
id|ps.nr_dirty
OL
id|background_thresh
op_logical_and
id|min_pages
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|nr_to_write
op_assign
id|MAX_WRITEBACK_PAGES
suffix:semicolon
id|writeback_unlocked_inodes
c_func
(paren
op_amp
id|nr_to_write
comma
id|WB_SYNC_NONE
comma
l_int|NULL
)paren
suffix:semicolon
id|min_pages
op_sub_assign
id|MAX_WRITEBACK_PAGES
op_minus
id|nr_to_write
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nr_to_write
op_le
l_int|0
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start heavy writeback of everything.&n; */
DECL|function|wakeup_bdflush
r_void
id|wakeup_bdflush
c_func
(paren
r_void
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
id|pdflush_operation
c_func
(paren
id|background_writeout
comma
id|ps.nr_dirty
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The interval between `kupdate&squot;-style writebacks.&n; *&n; * Traditional kupdate writes back data which is 30-35 seconds old.&n; * This one does that, but it also writes back just 1/6th of the dirty&n; * data.  This is to avoid great I/O storms.&n; *&n; * We chunk the writes up and yield, to permit any throttled page-allocators&n; * to perform their I/O against a large file.&n; */
DECL|variable|wb_writeback_jifs
r_static
r_int
id|wb_writeback_jifs
op_assign
l_int|5
op_star
id|HZ
suffix:semicolon
DECL|variable|wb_timer
r_static
r_struct
id|timer_list
id|wb_timer
suffix:semicolon
multiline_comment|/*&n; * Periodic writeback of &quot;old&quot; data.&n; *&n; * Define &quot;old&quot;: the first time one of an inode&squot;s pages is dirtied, we mark the&n; * dirtying-time in the inode&squot;s address_space.  So this periodic writeback code&n; * just walks the superblock inode list, writing back any inodes which are&n; * older than a specific point in time.&n; *&n; * Try to run once per wb_writeback_jifs jiffies.  But if a writeback event&n; * takes longer than a wb_writeback_jifs interval, then leave a one-second&n; * gap.&n; *&n; * older_than_this takes precedence over nr_to_write.  So we&squot;ll only write back&n; * all dirty pages if they are all attached to &quot;old&quot; mappings.&n; */
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
r_struct
id|page_state
id|ps
suffix:semicolon
r_int
id|nr_to_write
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
l_int|30
op_star
id|HZ
suffix:semicolon
id|start_jif
op_assign
id|jiffies
suffix:semicolon
id|next_jif
op_assign
id|start_jif
op_plus
id|wb_writeback_jifs
suffix:semicolon
id|nr_to_write
op_assign
id|ps.nr_dirty
suffix:semicolon
id|writeback_unlocked_inodes
c_func
(paren
op_amp
id|nr_to_write
comma
id|WB_SYNC_NONE
comma
op_amp
id|oldest_jif
)paren
suffix:semicolon
id|blk_run_queues
c_func
(paren
)paren
suffix:semicolon
id|yield
c_func
(paren
)paren
suffix:semicolon
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
)brace
DECL|function|wb_timer_init
r_static
r_int
id|__init
id|wb_timer_init
c_func
(paren
r_void
)paren
(brace
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
id|wb_writeback_jifs
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|wb_timer_init
id|module_init
c_func
(paren
id|wb_timer_init
)paren
suffix:semicolon
multiline_comment|/*&n; * A library function, which implements the vm_writeback a_op.  It&squot;s fairly&n; * lame at this time.  The idea is: the VM wants to liberate this page,&n; * so we pass the page to the address_space and give the fs the opportunity&n; * to write out lots of pages around this one.  It allows extent-based&n; * filesytems to do intelligent things.  It lets delayed-allocate filesystems&n; * perform better file layout.  It lets the address_space opportunistically&n; * write back disk-contiguous pages which are in other zones.&n; *&n; * FIXME: the VM wants to start I/O against *this* page.  Because its zone&n; * is under pressure.  But this function may start writeout against a&n; * totally different set of pages.  Unlikely to be a huge problem, but if it&n; * is, we could just writepage the page if it is still (PageDirty &amp;&amp;&n; * !PageWriteback) (See below).&n; *&n; * Another option is to just reposition page-&gt;mapping-&gt;dirty_pages so we&n; * *know* that the page will be written.  That will work fine, but seems&n; * unpleasant.  (If the page is not for-sure on -&gt;dirty_pages we&squot;re dead).&n; * Plus it assumes that the address_space is performing writeback in&n; * -&gt;dirty_pages order.&n; *&n; * So.  The proper fix is to leave the page locked-and-dirty and to pass&n; * it all the way down.&n; */
DECL|function|generic_vm_writeback
r_int
id|generic_vm_writeback
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
op_star
id|nr_to_write
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t own this inode, and we don&squot;t want the address_space&n;&t; * vanishing while writeback is walking its pages.&n;&t; */
id|inode
op_assign
id|igrab
c_func
(paren
id|inode
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
id|inode
)paren
(brace
id|writeback_mapping
c_func
(paren
id|inode-&gt;i_mapping
comma
id|nr_to_write
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This iput() will internally call ext2_discard_prealloc(),&n;&t;&t; * which is rather bogus.  But there is no other way of&n;&t;&t; * dropping our ref to the inode.  However, there&squot;s no harm&n;&t;&t; * in dropping the prealloc, because there probably isn&squot;t any.&n;&t;&t; * Just a waste of cycles.&n;&t;&t; */
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|PageWriteback
c_func
(paren
id|page
)paren
op_logical_and
id|PageDirty
c_func
(paren
id|page
)paren
)paren
(brace
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageWriteback
c_func
(paren
id|page
)paren
op_logical_and
id|TestClearPageDirty
c_func
(paren
id|page
)paren
)paren
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|writepage
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|generic_vm_writeback
id|EXPORT_SYMBOL
c_func
(paren
id|generic_vm_writeback
)paren
suffix:semicolon
multiline_comment|/**&n; * generic_writeback_mapping - walk the list of dirty pages of the given&n; * address space and writepage() all of them.&n; * &n; * @mapping: address space structure to write&n; * @nr_to_write: subtract the number of written pages from *@nr_to_write&n; *&n; * This is a library function, which implements the writeback_mapping()&n; * address_space_operation.&n; *&n; * (The next two paragraphs refer to code which isn&squot;t here yet, but they&n; *  explain the presence of address_space.io_pages)&n; *&n; * Pages can be moved from clean_pages or locked_pages onto dirty_pages&n; * at any time - it&squot;s not possible to lock against that.  So pages which&n; * have already been added to a BIO may magically reappear on the dirty_pages&n; * list.  And generic_writeback_mapping() will again try to lock those pages.&n; * But I/O has not yet been started against the page.  Thus deadlock.&n; *&n; * To avoid this, the entire contents of the dirty_pages list are moved&n; * onto io_pages up-front.  We then walk io_pages, locking the&n; * pages and submitting them for I/O, moving them to locked_pages.&n; *&n; * This has the added benefit of preventing a livelock which would otherwise&n; * occur if pages are being dirtied faster than we can write them out.&n; *&n; * If a page is already under I/O, generic_writeback_mapping() skips it, even&n; * if it&squot;s dirty.  This is desirable behaviour for memory-cleaning writeback,&n; * but it is INCORRECT for data-integrity system calls such as fsync().  fsync()&n; * and msync() need to guarentee that all the data which was dirty at the time&n; * the call was made get new I/O started against them.  The way to do this is&n; * to run filemap_fdatawait() before calling filemap_fdatawrite().&n; *&n; * It&squot;s fairly rare for PageWriteback pages to be on -&gt;dirty_pages.  It&n; * means that someone redirtied the page while it was under I/O.&n; */
DECL|function|generic_writeback_mapping
r_int
id|generic_writeback_mapping
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
op_star
id|nr_to_write
)paren
(brace
r_int
(paren
op_star
id|writepage
)paren
(paren
r_struct
id|page
op_star
)paren
op_assign
id|mapping-&gt;a_ops-&gt;writepage
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|done
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|list_splice
c_func
(paren
op_amp
id|mapping-&gt;dirty_pages
comma
op_amp
id|mapping-&gt;io_pages
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mapping-&gt;dirty_pages
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;io_pages
)paren
op_logical_and
op_logical_neg
id|done
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|list_entry
c_func
(paren
id|mapping-&gt;io_pages.prev
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
op_amp
id|page-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|PageDirty
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
id|mapping-&gt;dirty_pages
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|PageDirty
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
id|mapping-&gt;clean_pages
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* It may have been removed from swapcache: check -&gt;mapping */
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
id|TestClearPageDirty
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|PageWriteback
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/* FIXME: batch this up */
r_if
c_cond
(paren
op_logical_neg
id|PageActive
c_func
(paren
id|page
)paren
op_logical_and
id|PageLRU
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
id|pagemap_lru_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageActive
c_func
(paren
id|page
)paren
op_logical_and
id|PageLRU
c_func
(paren
id|page
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|inactive_list
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
)brace
id|err
op_assign
id|writepage
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|err
suffix:semicolon
r_if
c_cond
(paren
id|nr_to_write
op_logical_and
op_decrement
(paren
op_star
id|nr_to_write
)paren
op_le
l_int|0
)paren
id|done
op_assign
l_int|1
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
id|write_lock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;io_pages
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Put the rest back, in the correct order.&n;&t;&t; */
id|list_splice
c_func
(paren
op_amp
id|mapping-&gt;io_pages
comma
id|mapping-&gt;dirty_pages.prev
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|mapping-&gt;io_pages
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|generic_writeback_mapping
id|EXPORT_SYMBOL
c_func
(paren
id|generic_writeback_mapping
)paren
suffix:semicolon
DECL|function|writeback_mapping
r_int
id|writeback_mapping
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
op_star
id|nr_to_write
)paren
(brace
r_if
c_cond
(paren
id|mapping-&gt;a_ops-&gt;writeback_mapping
)paren
r_return
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|writeback_mapping
c_func
(paren
id|mapping
comma
id|nr_to_write
)paren
suffix:semicolon
r_return
id|generic_writeback_mapping
c_func
(paren
id|mapping
comma
id|nr_to_write
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
id|write_lock
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
id|TestClearPageDirty
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
id|write_unlock
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
id|write_unlock
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
op_logical_and
op_logical_neg
id|PageSwapCache
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
id|write_lock
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
id|write_unlock
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
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;private_lock
)paren
suffix:semicolon
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
id|write_lock
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
id|write_unlock
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
eof
