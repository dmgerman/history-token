multiline_comment|/*&n; * Macros for manipulating and testing page-&gt;flags&n; */
macro_line|#ifndef PAGE_FLAGS_H
DECL|macro|PAGE_FLAGS_H
mdefine_line|#define PAGE_FLAGS_H
multiline_comment|/*&n; * Global page accounting.  One instance per CPU.&n; */
DECL|struct|page_state
r_extern
r_struct
id|page_state
(brace
DECL|member|nr_dirty
r_int
r_int
id|nr_dirty
suffix:semicolon
DECL|member|nr_locked
r_int
r_int
id|nr_locked
suffix:semicolon
DECL|member|nr_pagecache
r_int
r_int
id|nr_pagecache
suffix:semicolon
)brace
id|____cacheline_aligned_in_smp
id|page_states
(braket
id|NR_CPUS
)braket
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
DECL|macro|mod_page_state
mdefine_line|#define mod_page_state(member, delta)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;page_states[smp_processor_id()].member += (delta);&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|inc_page_state
mdefine_line|#define inc_page_state(member)&t;mod_page_state(member, 1UL)
DECL|macro|dec_page_state
mdefine_line|#define dec_page_state(member)&t;mod_page_state(member, 0UL - 1)
multiline_comment|/*&n; * Manipulation of page state flags&n; */
DECL|macro|UnlockPage
mdefine_line|#define UnlockPage(page)&t;unlock_page(page)
DECL|macro|PageLocked
mdefine_line|#define PageLocked(page)&t;test_bit(PG_locked_dontuse, &amp;(page)-&gt;flags)
DECL|macro|SetPageLocked
mdefine_line|#define SetPageLocked(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!test_and_set_bit(PG_locked_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_locked);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|LockPage
mdefine_line|#define LockPage(page)&t;&t;SetPageLocked(page)&t;/* grr.  kill me */
DECL|macro|TryLockPage
mdefine_line|#define TryLockPage(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_set_bit(PG_locked_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&bslash;&n;&t;&t;if (!ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_locked);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ClearPageLocked
mdefine_line|#define ClearPageLocked(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (test_and_clear_bit(PG_locked_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_locked);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|TestClearPageLocked
mdefine_line|#define TestClearPageLocked(page)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_clear_bit(PG_locked_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&t;&bslash;&n;&t;&t;if (ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_locked);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
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
DECL|macro|PageTestandClearReferenced
mdefine_line|#define PageTestandClearReferenced(page)&t;test_and_clear_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|Page_Uptodate
mdefine_line|#define Page_Uptodate(page)&t;test_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|SetPageUptodate
mdefine_line|#define SetPageUptodate(page)&t;set_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|ClearPageUptodate
mdefine_line|#define ClearPageUptodate(page)&t;clear_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|PageDirty
mdefine_line|#define PageDirty(page)&t;&t;test_bit(PG_dirty_dontuse, &amp;(page)-&gt;flags)
DECL|macro|SetPageDirty
mdefine_line|#define SetPageDirty(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!test_and_set_bit(PG_dirty_dontuse,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_dirty);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|TestSetPageDirty
mdefine_line|#define TestSetPageDirty(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_set_bit(PG_dirty_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&t;&bslash;&n;&t;&t;if (!ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;inc_page_state(nr_dirty);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ClearPageDirty
mdefine_line|#define ClearPageDirty(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (test_and_clear_bit(PG_dirty_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags))&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_dirty);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|TestClearPageDirty
mdefine_line|#define TestClearPageDirty(page)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = test_and_clear_bit(PG_dirty_dontuse,&t;&t;&bslash;&n;&t;&t;&t;&t;&amp;(page)-&gt;flags);&t;&t;&t;&bslash;&n;&t;&t;if (ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;dec_page_state(nr_dirty);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
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
DECL|macro|PageSlab
mdefine_line|#define PageSlab(page)&t;&t;test_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|PageSetSlab
mdefine_line|#define PageSetSlab(page)&t;set_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|PageClearSlab
mdefine_line|#define PageClearSlab(page)&t;clear_bit(PG_slab, &amp;(page)-&gt;flags)
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
DECL|macro|__SetPageReserved
mdefine_line|#define __SetPageReserved(page)&t;__set_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|PageLaunder
mdefine_line|#define PageLaunder(page)&t;test_bit(PG_launder, &amp;(page)-&gt;flags)
DECL|macro|SetPageLaunder
mdefine_line|#define SetPageLaunder(page)&t;set_bit(PG_launder, &amp;(page)-&gt;flags)
DECL|macro|SetPagePrivate
mdefine_line|#define SetPagePrivate(page)&t;set_bit(PG_private, &amp;(page)-&gt;flags)
DECL|macro|ClearPagePrivate
mdefine_line|#define ClearPagePrivate(page)&t;clear_bit(PG_private, &amp;(page)-&gt;flags)
DECL|macro|PagePrivate
mdefine_line|#define PagePrivate(page)&t;test_bit(PG_private, &amp;(page)-&gt;flags)
macro_line|#endif&t;/* PAGE_FLAGS_H */
eof
