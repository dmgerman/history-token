multiline_comment|/*&n; * Macros for manipulating and testing page-&gt;flags&n; */
macro_line|#ifndef PAGE_FLAGS_H
DECL|macro|PAGE_FLAGS_H
mdefine_line|#define PAGE_FLAGS_H
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
multiline_comment|/*&n; * Various page-&gt;flags bits:&n; *&n; * PG_reserved is set for special pages, which can never be swapped out. Some&n; * of them might not even exist (eg empty_bad_page)...&n; *&n; * The PG_private bitflag is set if page-&gt;private contains a valid value.&n; *&n; * During disk I/O, PG_locked is used. This bit is set before I/O and&n; * reset when I/O completes. page_waitqueue(page) is a wait queue of all tasks&n; * waiting for the I/O on this page to complete.&n; *&n; * PG_uptodate tells whether the page&squot;s contents is valid.  When a read&n; * completes, the page becomes uptodate, unless a disk I/O error happened.&n; *&n; * For choosing which pages to swap out, inode pages carry a PG_referenced bit,&n; * which is set any time the system accesses that page through the (mapping,&n; * index) hash table.  This referenced bit, together with the referenced bit&n; * in the page tables, is used to manipulate page-&gt;age and move the page across&n; * the active, inactive_dirty and inactive_clean lists.&n; *&n; * Note that the referenced bit, the page-&gt;lru list_head and the active,&n; * inactive_dirty and inactive_clean lists are protected by the&n; * zone-&gt;lru_lock, and *NOT* by the usual PG_locked bit!&n; *&n; * PG_error is set to indicate that an I/O error occurred on this page.&n; *&n; * PG_arch_1 is an architecture specific page state bit.  The generic code&n; * guarantees that this bit is cleared for a page when it first is entered into&n; * the page cache.&n; *&n; * PG_highmem pages are not permanently mapped into the kernel virtual address&n; * space, they need to be kmapped separately for doing IO on the pages.  The&n; * struct page (these bits with information) are always mapped into kernel&n; * address space...&n; */
multiline_comment|/*&n; * Don&squot;t use the *_dontuse flags.  Use the macros.  Otherwise you&squot;ll break&n; * locked- and dirty-page accounting.  The top eight bits of page-&gt;flags are&n; * used for page-&gt;zone, so putting flag bits there doesn&squot;t work.&n; */
DECL|macro|PG_locked
mdefine_line|#define PG_locked&t; &t; 0&t;/* Page is locked. Don&squot;t touch. */
DECL|macro|PG_error
mdefine_line|#define PG_error&t;&t; 1
DECL|macro|PG_referenced
mdefine_line|#define PG_referenced&t;&t; 2
DECL|macro|PG_uptodate
mdefine_line|#define PG_uptodate&t;&t; 3
DECL|macro|PG_dirty
mdefine_line|#define PG_dirty&t; &t; 4
DECL|macro|PG_lru
mdefine_line|#define PG_lru&t;&t;&t; 5
DECL|macro|PG_active
mdefine_line|#define PG_active&t;&t; 6
DECL|macro|PG_slab
mdefine_line|#define PG_slab&t;&t;&t; 7&t;/* slab debug (Suparna wants this) */
DECL|macro|PG_highmem
mdefine_line|#define PG_highmem&t;&t; 8
DECL|macro|PG_checked
mdefine_line|#define PG_checked&t;&t; 9&t;/* kill me in 2.5.&lt;early&gt;. */
DECL|macro|PG_arch_1
mdefine_line|#define PG_arch_1&t;&t;10
DECL|macro|PG_reserved
mdefine_line|#define PG_reserved&t;&t;11
DECL|macro|PG_private
mdefine_line|#define PG_private&t;&t;12&t;/* Has something at -&gt;private */
DECL|macro|PG_writeback
mdefine_line|#define PG_writeback&t;&t;13&t;/* Page is under writeback */
DECL|macro|PG_nosave
mdefine_line|#define PG_nosave&t;&t;14&t;/* Used for system suspend/resume */
DECL|macro|PG_chainlock
mdefine_line|#define PG_chainlock&t;&t;15&t;/* lock bit for -&gt;pte_chain */
DECL|macro|PG_direct
mdefine_line|#define PG_direct&t;&t;16&t;/* -&gt;pte_chain points directly at pte */
DECL|macro|PG_mappedtodisk
mdefine_line|#define PG_mappedtodisk&t;&t;17&t;/* Has blocks allocated on-disk */
DECL|macro|PG_reclaim
mdefine_line|#define PG_reclaim&t;&t;18&t;/* To be recalimed asap */
multiline_comment|/*&n; * Global page accounting.  One instance per CPU.  Only unsigned longs are&n; * allowed.&n; */
DECL|struct|page_state
r_struct
id|page_state
(brace
DECL|member|nr_dirty
r_int
r_int
id|nr_dirty
suffix:semicolon
multiline_comment|/* Dirty writeable pages */
DECL|member|nr_writeback
r_int
r_int
id|nr_writeback
suffix:semicolon
multiline_comment|/* Pages under writeback */
DECL|member|nr_pagecache
r_int
r_int
id|nr_pagecache
suffix:semicolon
multiline_comment|/* Pages in pagecache */
DECL|member|nr_page_table_pages
r_int
r_int
id|nr_page_table_pages
suffix:semicolon
multiline_comment|/* Pages used for pagetables */
DECL|member|nr_reverse_maps
r_int
r_int
id|nr_reverse_maps
suffix:semicolon
multiline_comment|/* includes PageDirect */
DECL|member|nr_mapped
r_int
r_int
id|nr_mapped
suffix:semicolon
multiline_comment|/* mapped into pagetables */
DECL|member|nr_slab
r_int
r_int
id|nr_slab
suffix:semicolon
multiline_comment|/* In slab */
DECL|macro|GET_PAGE_STATE_LAST
mdefine_line|#define GET_PAGE_STATE_LAST nr_slab
multiline_comment|/*&n;&t; * The below are zeroed by get_page_state().  Use get_full_page_state()&n;&t; * to add up all these.&n;&t; */
DECL|member|pgpgin
r_int
r_int
id|pgpgin
suffix:semicolon
multiline_comment|/* Disk reads */
DECL|member|pgpgout
r_int
r_int
id|pgpgout
suffix:semicolon
multiline_comment|/* Disk writes */
DECL|member|pswpin
r_int
r_int
id|pswpin
suffix:semicolon
multiline_comment|/* swap reads */
DECL|member|pswpout
r_int
r_int
id|pswpout
suffix:semicolon
multiline_comment|/* swap writes */
DECL|member|pgalloc
r_int
r_int
id|pgalloc
suffix:semicolon
multiline_comment|/* page allocations */
DECL|member|pgfree
r_int
r_int
id|pgfree
suffix:semicolon
multiline_comment|/* page freeings */
DECL|member|pgactivate
r_int
r_int
id|pgactivate
suffix:semicolon
multiline_comment|/* pages moved inactive-&gt;active */
DECL|member|pgdeactivate
r_int
r_int
id|pgdeactivate
suffix:semicolon
multiline_comment|/* pages moved active-&gt;inactive */
DECL|member|pgfault
r_int
r_int
id|pgfault
suffix:semicolon
multiline_comment|/* faults (major+minor) */
DECL|member|pgmajfault
r_int
r_int
id|pgmajfault
suffix:semicolon
multiline_comment|/* faults (major only) */
DECL|member|pgscan
r_int
r_int
id|pgscan
suffix:semicolon
multiline_comment|/* pages scanned by page reclaim */
DECL|member|pgrefill
r_int
r_int
id|pgrefill
suffix:semicolon
multiline_comment|/* inspected in refill_inactive_zone */
DECL|member|pgsteal
r_int
r_int
id|pgsteal
suffix:semicolon
multiline_comment|/* total pages reclaimed */
DECL|member|kswapd_steal
r_int
r_int
id|kswapd_steal
suffix:semicolon
multiline_comment|/* pages reclaimed by kswapd */
DECL|member|pageoutrun
r_int
r_int
id|pageoutrun
suffix:semicolon
multiline_comment|/* kswapd&squot;s calls to page reclaim */
DECL|member|allocstall
r_int
r_int
id|allocstall
suffix:semicolon
multiline_comment|/* direct reclaim calls */
DECL|member|pgrotated
r_int
r_int
id|pgrotated
suffix:semicolon
multiline_comment|/* pages rotated to tail of the LRU */
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|page_state
comma
id|page_states
)paren
suffix:semicolon
r_extern
r_void
id|get_page_state
c_func
(paren
r_struct
id|page_state
op_star
id|ret
)paren
suffix:semicolon
r_extern
r_void
id|get_full_page_state
c_func
(paren
r_struct
id|page_state
op_star
id|ret
)paren
suffix:semicolon
DECL|macro|mod_page_state
mdefine_line|#define mod_page_state(member, delta)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_cpu_var(page_states).member += (delta);&t;&t;&bslash;&n;&t;&t;local_irq_restore(flags);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|inc_page_state
mdefine_line|#define inc_page_state(member)&t;mod_page_state(member, 1UL)
DECL|macro|dec_page_state
mdefine_line|#define dec_page_state(member)&t;mod_page_state(member, 0UL - 1)
multiline_comment|/*&n; * Manipulation of page state flags&n; */
DECL|macro|PageLocked
mdefine_line|#define PageLocked(page)&t;&t;&bslash;&n;&t;&t;test_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|SetPageLocked
mdefine_line|#define SetPageLocked(page)&t;&t;&bslash;&n;&t;&t;set_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageLocked
mdefine_line|#define TestSetPageLocked(page)&t;&t;&bslash;&n;&t;&t;test_and_set_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|ClearPageLocked
mdefine_line|#define ClearPageLocked(page)&t;&t;&bslash;&n;&t;&t;clear_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageLocked
mdefine_line|#define TestClearPageLocked(page)&t;&bslash;&n;&t;&t;test_and_clear_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|PageError
mdefine_line|#define PageError(page)&t;&t;test_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|SetPageError
mdefine_line|#define SetPageError(page)&t;set_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|ClearPageError
mdefine_line|#define ClearPageError(page)&t;clear_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|PageReferenced
mdefine_line|#define PageReferenced(page)&t;test_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|SetPageReferenced
mdefine_line|#define SetPageReferenced(page)&t;set_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|ClearPageReferenced
mdefine_line|#define ClearPageReferenced(page)&t;clear_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageReferenced
mdefine_line|#define TestClearPageReferenced(page) test_and_clear_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|PageUptodate
mdefine_line|#define PageUptodate(page)&t;test_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|SetPageUptodate
mdefine_line|#define SetPageUptodate(page)&t;set_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|ClearPageUptodate
mdefine_line|#define ClearPageUptodate(page)&t;clear_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|PageDirty
mdefine_line|#define PageDirty(page)&t;&t;test_bit(PG_dirty, &amp;(page)-&gt;flags)
DECL|macro|SetPageDirty
mdefine_line|#define SetPageDirty(page)&t;set_bit(PG_dirty, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageDirty
mdefine_line|#define TestSetPageDirty(page)&t;test_and_set_bit(PG_dirty, &amp;(page)-&gt;flags)
DECL|macro|ClearPageDirty
mdefine_line|#define ClearPageDirty(page)&t;clear_bit(PG_dirty, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageDirty
mdefine_line|#define TestClearPageDirty(page) test_and_clear_bit(PG_dirty, &amp;(page)-&gt;flags)
DECL|macro|SetPageLRU
mdefine_line|#define SetPageLRU(page)&t;set_bit(PG_lru, &amp;(page)-&gt;flags)
DECL|macro|PageLRU
mdefine_line|#define PageLRU(page)&t;&t;test_bit(PG_lru, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageLRU
mdefine_line|#define TestSetPageLRU(page)&t;test_and_set_bit(PG_lru, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageLRU
mdefine_line|#define TestClearPageLRU(page)&t;test_and_clear_bit(PG_lru, &amp;(page)-&gt;flags)
DECL|macro|PageActive
mdefine_line|#define PageActive(page)&t;test_bit(PG_active, &amp;(page)-&gt;flags)
DECL|macro|SetPageActive
mdefine_line|#define SetPageActive(page)&t;set_bit(PG_active, &amp;(page)-&gt;flags)
DECL|macro|ClearPageActive
mdefine_line|#define ClearPageActive(page)&t;clear_bit(PG_active, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageActive
mdefine_line|#define TestClearPageActive(page) test_and_clear_bit(PG_active, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageActive
mdefine_line|#define TestSetPageActive(page) test_and_set_bit(PG_active, &amp;(page)-&gt;flags)
DECL|macro|PageSlab
mdefine_line|#define PageSlab(page)&t;&t;test_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|SetPageSlab
mdefine_line|#define SetPageSlab(page)&t;set_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|ClearPageSlab
mdefine_line|#define ClearPageSlab(page)&t;clear_bit(PG_slab, &amp;(page)-&gt;flags)
macro_line|#ifdef CONFIG_HIGHMEM
DECL|macro|PageHighMem
mdefine_line|#define PageHighMem(page)&t;test_bit(PG_highmem, &amp;(page)-&gt;flags)
macro_line|#else
DECL|macro|PageHighMem
mdefine_line|#define PageHighMem(page)&t;0 /* needed to optimize away at compile time */
macro_line|#endif
DECL|macro|PageChecked
mdefine_line|#define PageChecked(page)&t;test_bit(PG_checked, &amp;(page)-&gt;flags)
DECL|macro|SetPageChecked
mdefine_line|#define SetPageChecked(page)&t;set_bit(PG_checked, &amp;(page)-&gt;flags)
DECL|macro|PageReserved
mdefine_line|#define PageReserved(page)&t;test_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|SetPageReserved
mdefine_line|#define SetPageReserved(page)&t;set_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|ClearPageReserved
mdefine_line|#define ClearPageReserved(page)&t;clear_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|SetPagePrivate
mdefine_line|#define SetPagePrivate(page)&t;set_bit(PG_private, &amp;(page)-&gt;flags)
DECL|macro|ClearPagePrivate
mdefine_line|#define ClearPagePrivate(page)&t;clear_bit(PG_private, &amp;(page)-&gt;flags)
DECL|macro|PagePrivate
mdefine_line|#define PagePrivate(page)&t;test_bit(PG_private, &amp;(page)-&gt;flags)
DECL|macro|PageWriteback
mdefine_line|#define PageWriteback(page)&t;test_bit(PG_writeback, &amp;(page)-&gt;flags)
DECL|macro|SetPageWriteback
mdefine_line|#define SetPageWriteback(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!test_and_set_bit(PG_writeback,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_writeback);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|TestSetPageWriteback
mdefine_line|#define TestSetPageWriteback(page)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_set_bit(PG_writeback,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&bslash;&n;&t;&t;if (!ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_writeback);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ClearPageWriteback
mdefine_line|#define ClearPageWriteback(page)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (test_and_clear_bit(PG_writeback,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_writeback);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|TestClearPageWriteback
mdefine_line|#define TestClearPageWriteback(page)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_clear_bit(PG_writeback,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&t;&bslash;&n;&t;&t;if (ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_writeback);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|PageNosave
mdefine_line|#define PageNosave(page)&t;test_bit(PG_nosave, &amp;(page)-&gt;flags)
DECL|macro|SetPageNosave
mdefine_line|#define SetPageNosave(page)&t;set_bit(PG_nosave, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageNosave
mdefine_line|#define TestSetPageNosave(page)&t;test_and_set_bit(PG_nosave, &amp;(page)-&gt;flags)
DECL|macro|ClearPageNosave
mdefine_line|#define ClearPageNosave(page)&t;&t;clear_bit(PG_nosave, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageNosave
mdefine_line|#define TestClearPageNosave(page)&t;test_and_clear_bit(PG_nosave, &amp;(page)-&gt;flags)
DECL|macro|PageDirect
mdefine_line|#define PageDirect(page)&t;test_bit(PG_direct, &amp;(page)-&gt;flags)
DECL|macro|SetPageDirect
mdefine_line|#define SetPageDirect(page)&t;set_bit(PG_direct, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageDirect
mdefine_line|#define TestSetPageDirect(page)&t;test_and_set_bit(PG_direct, &amp;(page)-&gt;flags)
DECL|macro|ClearPageDirect
mdefine_line|#define ClearPageDirect(page)&t;&t;clear_bit(PG_direct, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageDirect
mdefine_line|#define TestClearPageDirect(page)&t;test_and_clear_bit(PG_direct, &amp;(page)-&gt;flags)
DECL|macro|PageMappedToDisk
mdefine_line|#define PageMappedToDisk(page)&t;test_bit(PG_mappedtodisk, &amp;(page)-&gt;flags)
DECL|macro|SetPageMappedToDisk
mdefine_line|#define SetPageMappedToDisk(page) set_bit(PG_mappedtodisk, &amp;(page)-&gt;flags)
DECL|macro|ClearPageMappedToDisk
mdefine_line|#define ClearPageMappedToDisk(page) clear_bit(PG_mappedtodisk, &amp;(page)-&gt;flags)
DECL|macro|PageReclaim
mdefine_line|#define PageReclaim(page)&t;test_bit(PG_reclaim, &amp;(page)-&gt;flags)
DECL|macro|SetPageReclaim
mdefine_line|#define SetPageReclaim(page)&t;set_bit(PG_reclaim, &amp;(page)-&gt;flags)
DECL|macro|ClearPageReclaim
mdefine_line|#define ClearPageReclaim(page)&t;clear_bit(PG_reclaim, &amp;(page)-&gt;flags)
DECL|macro|TestClearPageReclaim
mdefine_line|#define TestClearPageReclaim(page) test_and_clear_bit(PG_reclaim, &amp;(page)-&gt;flags)
multiline_comment|/*&n; * The PageSwapCache predicate doesn&squot;t use a PG_flag at this time,&n; * but it may again do so one day.&n; */
macro_line|#ifdef CONFIG_SWAP
r_extern
r_struct
id|address_space
id|swapper_space
suffix:semicolon
DECL|macro|PageSwapCache
mdefine_line|#define PageSwapCache(page) ((page)-&gt;mapping == &amp;swapper_space)
macro_line|#else
DECL|macro|PageSwapCache
mdefine_line|#define PageSwapCache(page) 0
macro_line|#endif
r_struct
id|page
suffix:semicolon
multiline_comment|/* forward declaration */
r_int
id|test_clear_page_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|function|clear_page_dirty
r_static
r_inline
r_void
id|clear_page_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|test_clear_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* PAGE_FLAGS_H */
eof
