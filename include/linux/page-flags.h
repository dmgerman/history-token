multiline_comment|/*&n; * Macros for manipulating and testing page-&gt;flags&n; */
macro_line|#ifndef PAGE_FLAGS_H
DECL|macro|PAGE_FLAGS_H
mdefine_line|#define PAGE_FLAGS_H
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
DECL|macro|PG_compound
mdefine_line|#define PG_compound&t;&t;15&t;/* Part of a compound page */
DECL|macro|PG_swapcache
mdefine_line|#define PG_swapcache&t;&t;16&t;/* Swap page: swp_entry_t in private */
DECL|macro|PG_mappedtodisk
mdefine_line|#define PG_mappedtodisk&t;&t;17&t;/* Has blocks allocated on-disk */
DECL|macro|PG_reclaim
mdefine_line|#define PG_reclaim&t;&t;18&t;/* To be reclaimed asap */
DECL|macro|PG_nosave_free
mdefine_line|#define PG_nosave_free&t;&t;19&t;/* Free, should not be written */
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
DECL|member|nr_unstable
r_int
r_int
id|nr_unstable
suffix:semicolon
multiline_comment|/* NFS unstable pages */
DECL|member|nr_page_table_pages
r_int
r_int
id|nr_page_table_pages
suffix:semicolon
multiline_comment|/* Pages used for pagetables */
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
DECL|member|pgalloc_high
r_int
r_int
id|pgalloc_high
suffix:semicolon
multiline_comment|/* page allocations */
DECL|member|pgalloc_normal
r_int
r_int
id|pgalloc_normal
suffix:semicolon
DECL|member|pgalloc_dma
r_int
r_int
id|pgalloc_dma
suffix:semicolon
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
DECL|member|pgrefill_high
r_int
r_int
id|pgrefill_high
suffix:semicolon
multiline_comment|/* inspected in refill_inactive_zone */
DECL|member|pgrefill_normal
r_int
r_int
id|pgrefill_normal
suffix:semicolon
DECL|member|pgrefill_dma
r_int
r_int
id|pgrefill_dma
suffix:semicolon
DECL|member|pgsteal_high
r_int
r_int
id|pgsteal_high
suffix:semicolon
multiline_comment|/* total highmem pages reclaimed */
DECL|member|pgsteal_normal
r_int
r_int
id|pgsteal_normal
suffix:semicolon
DECL|member|pgsteal_dma
r_int
r_int
id|pgsteal_dma
suffix:semicolon
DECL|member|pgscan_kswapd_high
r_int
r_int
id|pgscan_kswapd_high
suffix:semicolon
multiline_comment|/* total highmem pages scanned */
DECL|member|pgscan_kswapd_normal
r_int
r_int
id|pgscan_kswapd_normal
suffix:semicolon
DECL|member|pgscan_kswapd_dma
r_int
r_int
id|pgscan_kswapd_dma
suffix:semicolon
DECL|member|pgscan_direct_high
r_int
r_int
id|pgscan_direct_high
suffix:semicolon
multiline_comment|/* total highmem pages scanned */
DECL|member|pgscan_direct_normal
r_int
r_int
id|pgscan_direct_normal
suffix:semicolon
DECL|member|pgscan_direct_dma
r_int
r_int
id|pgscan_direct_dma
suffix:semicolon
DECL|member|pginodesteal
r_int
r_int
id|pginodesteal
suffix:semicolon
multiline_comment|/* pages reclaimed via inode freeing */
DECL|member|slabs_scanned
r_int
r_int
id|slabs_scanned
suffix:semicolon
multiline_comment|/* slab objects scanned */
DECL|member|kswapd_steal
r_int
r_int
id|kswapd_steal
suffix:semicolon
multiline_comment|/* pages reclaimed by kswapd */
DECL|member|kswapd_inodesteal
r_int
r_int
id|kswapd_inodesteal
suffix:semicolon
multiline_comment|/* reclaimed via kswapd inode freeing */
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
)brace
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
r_extern
r_int
r_int
id|__read_page_state
c_func
(paren
r_int
id|offset
)paren
suffix:semicolon
DECL|macro|read_page_state
mdefine_line|#define read_page_state(member) &bslash;&n;&t;__read_page_state(offsetof(struct page_state, member))
DECL|macro|mod_page_state
mdefine_line|#define mod_page_state(member, delta)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get_cpu_var(page_states).member += (delta);&t;&t;&bslash;&n;&t;&t;local_irq_restore(flags);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|inc_page_state
mdefine_line|#define inc_page_state(member)&t;mod_page_state(member, 1UL)
DECL|macro|dec_page_state
mdefine_line|#define dec_page_state(member)&t;mod_page_state(member, 0UL - 1)
DECL|macro|add_page_state
mdefine_line|#define add_page_state(member,delta) mod_page_state(member, (delta))
DECL|macro|sub_page_state
mdefine_line|#define sub_page_state(member,delta) mod_page_state(member, 0UL - (delta))
DECL|macro|mod_page_state_zone
mdefine_line|#define mod_page_state_zone(zone, member, delta)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long flags;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (is_highmem(zone))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_cpu_var(page_states).member##_high += (delta);&bslash;&n;&t;&t;else if (is_normal(zone))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_cpu_var(page_states).member##_normal += (delta);&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__get_cpu_var(page_states).member##_dma += (delta);&bslash;&n;&t;&t;local_irq_restore(flags);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
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
macro_line|#ifndef SetPageUptodate
DECL|macro|SetPageUptodate
mdefine_line|#define SetPageUptodate(page)&t;set_bit(PG_uptodate, &amp;(page)-&gt;flags)
macro_line|#endif
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
DECL|macro|TestClearPageSlab
mdefine_line|#define TestClearPageSlab(page)&t;test_and_clear_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|TestSetPageSlab
mdefine_line|#define TestSetPageSlab(page)&t;test_and_set_bit(PG_slab, &amp;(page)-&gt;flags)
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
DECL|macro|ClearPageChecked
mdefine_line|#define ClearPageChecked(page)&t;clear_bit(PG_checked, &amp;(page)-&gt;flags)
DECL|macro|PageReserved
mdefine_line|#define PageReserved(page)&t;test_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|SetPageReserved
mdefine_line|#define SetPageReserved(page)&t;set_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|ClearPageReserved
mdefine_line|#define ClearPageReserved(page)&t;clear_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|__ClearPageReserved
mdefine_line|#define __ClearPageReserved(page)&t;__clear_bit(PG_reserved, &amp;(page)-&gt;flags)
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
DECL|macro|PageNosaveFree
mdefine_line|#define PageNosaveFree(page)&t;test_bit(PG_nosave_free, &amp;(page)-&gt;flags)
DECL|macro|SetPageNosaveFree
mdefine_line|#define SetPageNosaveFree(page)&t;set_bit(PG_nosave_free, &amp;(page)-&gt;flags)
DECL|macro|ClearPageNosaveFree
mdefine_line|#define ClearPageNosaveFree(page)&t;&t;clear_bit(PG_nosave_free, &amp;(page)-&gt;flags)
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
DECL|macro|PageCompound
mdefine_line|#define PageCompound(page)&t;test_bit(PG_compound, &amp;(page)-&gt;flags)
DECL|macro|SetPageCompound
mdefine_line|#define SetPageCompound(page)&t;set_bit(PG_compound, &amp;(page)-&gt;flags)
DECL|macro|ClearPageCompound
mdefine_line|#define ClearPageCompound(page)&t;clear_bit(PG_compound, &amp;(page)-&gt;flags)
macro_line|#ifdef CONFIG_SWAP
DECL|macro|PageSwapCache
mdefine_line|#define PageSwapCache(page)&t;test_bit(PG_swapcache, &amp;(page)-&gt;flags)
DECL|macro|SetPageSwapCache
mdefine_line|#define SetPageSwapCache(page)&t;set_bit(PG_swapcache, &amp;(page)-&gt;flags)
DECL|macro|ClearPageSwapCache
mdefine_line|#define ClearPageSwapCache(page) clear_bit(PG_swapcache, &amp;(page)-&gt;flags)
macro_line|#else
DECL|macro|PageSwapCache
mdefine_line|#define PageSwapCache(page)&t;0
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
r_int
id|__clear_page_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|test_clear_page_writeback
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|test_set_page_writeback
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
DECL|function|set_page_writeback
r_static
r_inline
r_void
id|set_page_writeback
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|test_set_page_writeback
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* PAGE_FLAGS_H */
eof
