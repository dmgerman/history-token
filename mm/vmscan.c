multiline_comment|/*&n; *  linux/mm/vmscan.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Swap reorganised 29.12.95, Stephen Tweedie.&n; *  kswapd added: 7.1.96  sct&n; *  Removed kswapd_ctl limits, and swap out as many pages as needed&n; *  to bring the system back to freepages.high: 2.4.97, Rik van Riel.&n; *  Zone aware kswapd started 02/00, Kanoj Sarcar (kanoj@sgi.com).&n; *  Multiqueue VM started 5.8.00, Rik van Riel.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * The &quot;priority&quot; of VM scanning is how much of the queues we&n; * will scan in one go. A value of 6 for DEF_PRIORITY implies&n; * that we&squot;ll scan 1/64th of the queues (&quot;queue_length &gt;&gt; 6&quot;)&n; * during a normal aging round.&n; */
DECL|macro|DEF_PRIORITY
mdefine_line|#define DEF_PRIORITY (6)
multiline_comment|/*&n; * The swap-out function returns 1 if it successfully&n; * scanned all the pages it was asked to (`count&squot;).&n; * It returns zero if it couldn&squot;t do anything,&n; *&n; * rss may decrease because pages are shared, but this&n; * doesn&squot;t count as having freed a page.&n; */
multiline_comment|/* mm-&gt;page_table_lock is held. mmap_sem is not held */
DECL|function|try_to_swap_out
r_static
r_inline
r_int
id|try_to_swap_out
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|page_table
comma
r_struct
id|page
op_star
id|page
comma
id|zone_t
op_star
id|classzone
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|swp_entry_t
id|entry
suffix:semicolon
multiline_comment|/* Don&squot;t look at this pte if it&squot;s been accessed recently. */
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
op_logical_or
id|ptep_test_and_clear_young
c_func
(paren
id|page_table
)paren
)paren
(brace
id|mark_page_accessed
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t bother unmapping pages that are active */
r_if
c_cond
(paren
id|PageActive
c_func
(paren
id|page
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t bother replenishing zones not under pressure.. */
r_if
c_cond
(paren
op_logical_neg
id|memclass
c_func
(paren
id|page_zone
c_func
(paren
id|page
)paren
comma
id|classzone
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|TryLockPage
c_func
(paren
id|page
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* From this point on, the odds are that we&squot;re going to&n;&t; * nuke this pte, so read and clear the pte.  This hook&n;&t; * is needed on CPUs which update the accessed and dirty&n;&t; * bits in hardware.&n;&t; */
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|pte
op_assign
id|ptep_get_and_clear
c_func
(paren
id|page_table
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|pte
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Is the page already in the swap cache? If so, then&n;&t; * we can just drop our reference to it without doing&n;&t; * any IO - it&squot;s already up-to-date on disk.&n;&t; */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
id|entry.val
op_assign
id|page-&gt;index
suffix:semicolon
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
id|set_swap_pte
suffix:colon
id|set_pte
c_func
(paren
id|page_table
comma
id|swp_entry_to_pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|drop_pte
suffix:colon
id|mm-&gt;rss
op_decrement
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
(brace
r_int
id|freeable
op_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
op_logical_neg
op_logical_neg
id|page-&gt;buffers
op_le
l_int|2
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|freeable
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Is it a clean page? Then it must be recoverable&n;&t; * by just paging it in again, and we can just drop&n;&t; * it..  or if it&squot;s dirty but has backing store,&n;&t; * just mark the page dirty and drop it.&n;&t; *&n;&t; * However, this won&squot;t actually free any real&n;&t; * memory, as the page will just be in the page cache&n;&t; * somewhere, and as such we should just continue&n;&t; * our scan.&n;&t; *&n;&t; * Basically, this just makes it possible for us to do&n;&t; * some real work in the future in &quot;refill_inactive()&quot;.&n;&t; */
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
r_goto
id|drop_pte
suffix:semicolon
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
r_goto
id|drop_pte
suffix:semicolon
multiline_comment|/*&n;&t; * Anonymous buffercache pages can be left behind by&n;&t; * concurrent truncate and pagefault.&n;&t; */
r_if
c_cond
(paren
id|page-&gt;buffers
)paren
r_goto
id|preserve
suffix:semicolon
multiline_comment|/*&n;&t; * This is a dirty, swappable page.  First of all,&n;&t; * get a suitable swap entry for it, and make sure&n;&t; * we have the swap cache set up to associate the&n;&t; * page with that swap entry.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|entry
op_assign
id|get_swap_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry.val
)paren
r_break
suffix:semicolon
multiline_comment|/* Add it to the swap cache and mark it dirty&n;&t;&t; * (adding to the page cache will clear the dirty&n;&t;&t; * and uptodate bits, so we need to do it again)&n;&t;&t; */
r_switch
c_cond
(paren
id|add_to_swap_cache
c_func
(paren
id|page
comma
id|entry
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Success */
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|set_swap_pte
suffix:semicolon
r_case
op_minus
id|ENOMEM
suffix:colon
multiline_comment|/* radix-tree allocation */
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_goto
id|preserve
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* ENOENT: raced */
r_break
suffix:semicolon
)brace
multiline_comment|/* Raced with &quot;speculative&quot; read_swap_cache_async */
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/* No swap space left */
id|preserve
suffix:colon
id|set_pte
c_func
(paren
id|page_table
comma
id|pte
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* mm-&gt;page_table_lock is held. mmap_sem is not held */
DECL|function|swap_out_pmd
r_static
r_inline
r_int
id|swap_out_pmd
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|count
comma
id|zone_t
op_star
id|classzone
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|pmd_end
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|dir
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|pmd_end
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|pmd_end
)paren
id|end
op_assign
id|pmd_end
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VALID_PAGE
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
id|count
op_sub_assign
id|try_to_swap_out
c_func
(paren
id|mm
comma
id|vma
comma
id|address
comma
id|pte
comma
id|page
comma
id|classzone
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
op_minus
l_int|1
)paren
suffix:semicolon
id|mm-&gt;swap_address
op_assign
id|address
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* mm-&gt;page_table_lock is held. mmap_sem is not held */
DECL|function|swap_out_pgd
r_static
r_inline
r_int
id|swap_out_pgd
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|count
comma
id|zone_t
op_star
id|classzone
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|pgd_end
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|pgd_ERROR
c_func
(paren
op_star
id|dir
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|pgd_end
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|pgd_end
op_logical_and
(paren
id|end
OG
id|pgd_end
)paren
)paren
id|end
op_assign
id|pgd_end
suffix:semicolon
r_do
(brace
id|count
op_assign
id|swap_out_pmd
c_func
(paren
id|mm
comma
id|vma
comma
id|pmd
comma
id|address
comma
id|end
comma
id|count
comma
id|classzone
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_break
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* mm-&gt;page_table_lock is held. mmap_sem is not held */
DECL|function|swap_out_vma
r_static
r_inline
r_int
id|swap_out_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|count
comma
id|zone_t
op_star
id|classzone
)paren
(brace
id|pgd_t
op_star
id|pgdir
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* Don&squot;t swap out areas which are reserved */
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_RESERVED
)paren
r_return
id|count
suffix:semicolon
id|pgdir
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|count
op_assign
id|swap_out_pgd
c_func
(paren
id|mm
comma
id|vma
comma
id|pgdir
comma
id|address
comma
id|end
comma
id|count
comma
id|classzone
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_break
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgdir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* Placeholder for swap_out(): may be updated by fork.c:mmput() */
DECL|variable|swap_mm
r_struct
id|mm_struct
op_star
id|swap_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
multiline_comment|/*&n; * Returns remaining count of pages to be swapped out by followup call.&n; */
DECL|function|swap_out_mm
r_static
r_inline
r_int
id|swap_out_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
id|count
comma
r_int
op_star
id|mmcounter
comma
id|zone_t
op_star
id|classzone
)paren
(brace
r_int
r_int
id|address
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/*&n;&t; * Find the proper vm-area after freezing the vma chain &n;&t; * and ptes.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|address
op_assign
id|mm-&gt;swap_address
suffix:semicolon
r_if
c_cond
(paren
id|address
op_eq
id|TASK_SIZE
op_logical_or
id|swap_mm
op_ne
id|mm
)paren
(brace
multiline_comment|/* We raced: don&squot;t count this mm but try again */
op_increment
op_star
id|mmcounter
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
)paren
(brace
r_if
c_cond
(paren
id|address
OL
id|vma-&gt;vm_start
)paren
id|address
op_assign
id|vma-&gt;vm_start
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|count
op_assign
id|swap_out_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|address
comma
id|count
comma
id|classzone
)paren
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_goto
id|out_unlock
suffix:semicolon
id|address
op_assign
id|vma-&gt;vm_start
suffix:semicolon
)brace
)brace
multiline_comment|/* Indicate that we reached the end of address space */
id|mm-&gt;swap_address
op_assign
id|TASK_SIZE
suffix:semicolon
id|out_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
id|FASTCALL
c_func
(paren
id|swap_out
c_func
(paren
r_int
r_int
id|priority
comma
r_int
r_int
id|gfp_mask
comma
id|zone_t
op_star
id|classzone
)paren
)paren
suffix:semicolon
DECL|function|swap_out
r_static
r_int
id|swap_out
c_func
(paren
r_int
r_int
id|priority
comma
r_int
r_int
id|gfp_mask
comma
id|zone_t
op_star
id|classzone
)paren
(brace
r_int
id|counter
comma
id|nr_pages
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|counter
op_assign
id|mmlist_nr
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
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
)brace
id|spin_lock
c_func
(paren
op_amp
id|mmlist_lock
)paren
suffix:semicolon
id|mm
op_assign
id|swap_mm
suffix:semicolon
r_while
c_loop
(paren
id|mm-&gt;swap_address
op_eq
id|TASK_SIZE
op_logical_or
id|mm
op_eq
op_amp
id|init_mm
)paren
(brace
id|mm-&gt;swap_address
op_assign
l_int|0
suffix:semicolon
id|mm
op_assign
id|list_entry
c_func
(paren
id|mm-&gt;mmlist.next
comma
r_struct
id|mm_struct
comma
id|mmlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|swap_mm
)paren
r_goto
id|empty
suffix:semicolon
id|swap_mm
op_assign
id|mm
suffix:semicolon
)brace
multiline_comment|/* Make sure the mm doesn&squot;t disappear when we drop the lock.. */
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mmlist_lock
)paren
suffix:semicolon
id|nr_pages
op_assign
id|swap_out_mm
c_func
(paren
id|mm
comma
id|nr_pages
comma
op_amp
id|counter
comma
id|classzone
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_pages
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|counter
op_ge
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|empty
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mmlist_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|FASTCALL
c_func
(paren
id|shrink_cache
c_func
(paren
r_int
id|nr_pages
comma
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|priority
)paren
)paren
suffix:semicolon
DECL|function|shrink_cache
r_static
r_int
id|shrink_cache
c_func
(paren
r_int
id|nr_pages
comma
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|priority
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_int
id|max_scan
op_assign
id|nr_inactive_pages
op_div
id|priority
suffix:semicolon
r_int
id|max_mapped
op_assign
id|nr_pages
op_lshift
(paren
l_int|9
op_minus
id|priority
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|max_scan
op_ge
l_int|0
op_logical_and
(paren
id|entry
op_assign
id|inactive_list.prev
)paren
op_ne
op_amp
id|inactive_list
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
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
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|page
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|PageLRU
c_func
(paren
id|page
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|PageActive
c_func
(paren
id|page
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|entry
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|entry
comma
op_amp
id|inactive_list
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Zero page counts can happen because we unlink the pages&n;&t;&t; * _after_ decrementing the usage count..&n;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|page_count
c_func
(paren
id|page
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memclass
c_func
(paren
id|page_zone
c_func
(paren
id|page
)paren
comma
id|classzone
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Racy check to avoid trylocking when not worthwhile */
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;buffers
op_logical_and
(paren
id|page_count
c_func
(paren
id|page
)paren
op_ne
l_int|1
op_logical_or
op_logical_neg
id|page-&gt;mapping
)paren
)paren
r_goto
id|page_mapped
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The page is locked. IO in progress?&n;&t;&t; * Move it to the back of the list.&n;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|TryLockPage
c_func
(paren
id|page
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|PageLaunder
c_func
(paren
id|page
)paren
op_logical_and
(paren
id|gfp_mask
op_amp
id|__GFP_FS
)paren
)paren
(brace
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
id|pagemap_lru_lock
)paren
suffix:semicolon
id|wait_on_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
id|PageDirty
c_func
(paren
id|page
)paren
op_logical_and
id|is_page_cache_freeable
c_func
(paren
id|page
)paren
op_logical_and
id|mapping
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * It is not critical here to write it only if&n;&t;&t;&t; * the page is unmapped beause any direct writer&n;&t;&t;&t; * like O_DIRECT would set the PG_dirty bitflag&n;&t;&t;&t; * on the phisical page after having successfully&n;&t;&t;&t; * pinned it and after the I/O to the page is finished,&n;&t;&t;&t; * so the direct writes to the page cannot get lost.&n;&t;&t;&t; */
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
suffix:semicolon
id|writepage
op_assign
id|mapping-&gt;a_ops-&gt;writepage
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gfp_mask
op_amp
id|__GFP_FS
)paren
op_logical_and
id|writepage
)paren
(brace
id|ClearPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageLaunder
c_func
(paren
id|page
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
id|pagemap_lru_lock
)paren
suffix:semicolon
id|writepage
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * If the page has buffers, try to free the buffer mappings&n;&t;&t; * associated with this page. If we succeed we try to free&n;&t;&t; * the page as well.&n;&t;&t; */
r_if
c_cond
(paren
id|page-&gt;buffers
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
multiline_comment|/* avoid to free a locked page */
id|page_cache_get
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|try_to_release_page
c_func
(paren
id|page
comma
id|gfp_mask
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * We must not allow an anon page&n;&t;&t;&t;&t;&t; * with no buffers to be visible on&n;&t;&t;&t;&t;&t; * the LRU, so we unlock the page after&n;&t;&t;&t;&t;&t; * taking the lru lock&n;&t;&t;&t;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|__lru_cache_del
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* effectively free the page here */
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|nr_pages
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * The page is still in pagecache so undo the stuff&n;&t;&t;&t;&t;&t; * before the try_to_release_page since we&squot;ve not&n;&t;&t;&t;&t;&t; * finished and we can now try the next step.&n;&t;&t;&t;&t;&t; */
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* failed to drop the buffers so stop here */
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * This is the non-racy check for busy page.&n;&t;&t; */
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
r_if
c_cond
(paren
id|is_page_cache_freeable
c_func
(paren
id|page
)paren
)paren
r_goto
id|page_freeable
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
)brace
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_mapped
suffix:colon
r_if
c_cond
(paren
op_decrement
id|max_mapped
op_ge
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Alert! We&squot;ve found too many mapped pages on the&n;&t;&t; * inactive list, so we start swapping out now!&n;&t;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|swap_out
c_func
(paren
id|priority
comma
id|gfp_mask
comma
id|classzone
)paren
suffix:semicolon
r_return
id|nr_pages
suffix:semicolon
id|page_freeable
suffix:colon
multiline_comment|/*&n;&t;&t; * It is critical to check PageDirty _after_ we made sure&n;&t;&t; * the page is freeable* so not in use by anybody.&n;&t;&t; */
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
id|write_unlock
c_func
(paren
op_amp
id|mapping-&gt;page_lock
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* point of no return */
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
)paren
(brace
id|__remove_inode_page
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
)brace
r_else
(brace
id|swp_entry_t
id|swap
suffix:semicolon
id|swap.val
op_assign
id|page-&gt;index
suffix:semicolon
id|__delete_from_swap_cache
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
id|swap_free
c_func
(paren
id|swap
)paren
suffix:semicolon
)brace
id|__lru_cache_del
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* effectively free the page here */
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|nr_pages
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
r_return
id|nr_pages
suffix:semicolon
)brace
multiline_comment|/*&n; * This moves pages from the active list to&n; * the inactive list.&n; *&n; * We move them the other way when we see the&n; * reference bit on the page.&n; */
DECL|function|refill_inactive
r_static
r_void
id|refill_inactive
c_func
(paren
r_int
id|nr_pages
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pagemap_lru_lock
)paren
suffix:semicolon
id|entry
op_assign
id|active_list.prev
suffix:semicolon
r_while
c_loop
(paren
id|nr_pages
op_decrement
op_logical_and
id|entry
op_ne
op_amp
id|active_list
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|PageTestandClearReferenced
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
id|active_list
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|del_page_from_active_list
c_func
(paren
id|page
)paren
suffix:semicolon
id|add_page_to_inactive_list
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageReferenced
c_func
(paren
id|page
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
r_static
r_int
id|FASTCALL
c_func
(paren
id|shrink_caches
c_func
(paren
id|zone_t
op_star
id|classzone
comma
r_int
id|priority
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|nr_pages
)paren
)paren
suffix:semicolon
DECL|function|shrink_caches
r_static
r_int
id|shrink_caches
c_func
(paren
id|zone_t
op_star
id|classzone
comma
r_int
id|priority
comma
r_int
r_int
id|gfp_mask
comma
r_int
id|nr_pages
)paren
(brace
r_int
id|chunk_size
op_assign
id|nr_pages
suffix:semicolon
r_int
r_int
id|ratio
suffix:semicolon
id|nr_pages
op_sub_assign
id|kmem_cache_reap
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|nr_pages
op_assign
id|chunk_size
suffix:semicolon
multiline_comment|/* try to keep the active list 2/3 of the size of the cache */
id|ratio
op_assign
(paren
r_int
r_int
)paren
id|nr_pages
op_star
id|nr_active_pages
op_div
(paren
(paren
id|nr_inactive_pages
op_plus
l_int|1
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|refill_inactive
c_func
(paren
id|ratio
)paren
suffix:semicolon
id|nr_pages
op_assign
id|shrink_cache
c_func
(paren
id|nr_pages
comma
id|classzone
comma
id|gfp_mask
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|shrink_dcache_memory
c_func
(paren
id|priority
comma
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/* After shrinking the dcache, get rid of unused inodes too .. */
id|shrink_icache_memory
c_func
(paren
l_int|1
comma
id|gfp_mask
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_QUOTA
id|shrink_dqcache_memory
c_func
(paren
id|DEF_PRIORITY
comma
id|gfp_mask
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nr_pages
suffix:semicolon
)brace
DECL|function|try_to_free_pages
r_int
id|try_to_free_pages
c_func
(paren
id|zone_t
op_star
id|classzone
comma
r_int
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
(brace
r_int
id|priority
op_assign
id|DEF_PRIORITY
suffix:semicolon
r_int
id|nr_pages
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
r_do
(brace
id|nr_pages
op_assign
id|shrink_caches
c_func
(paren
id|classzone
comma
id|priority
comma
id|gfp_mask
comma
id|nr_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_pages
op_le
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|priority
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Hmm.. Cache shrink failed - time to kill something?&n;&t; * Mhwahahhaha! This is the part I really like. Giggle.&n;&t; */
id|out_of_memory
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kswapd_wait
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|kswapd_wait
)paren
suffix:semicolon
DECL|function|check_classzone_need_balance
r_static
r_int
id|check_classzone_need_balance
c_func
(paren
id|zone_t
op_star
id|classzone
)paren
(brace
id|zone_t
op_star
id|first_classzone
suffix:semicolon
id|first_classzone
op_assign
id|classzone-&gt;zone_pgdat-&gt;node_zones
suffix:semicolon
r_while
c_loop
(paren
id|classzone
op_ge
id|first_classzone
)paren
(brace
r_if
c_cond
(paren
id|classzone-&gt;free_pages
OG
id|classzone-&gt;pages_high
)paren
r_return
l_int|0
suffix:semicolon
id|classzone
op_decrement
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kswapd_balance_pgdat
r_static
r_int
id|kswapd_balance_pgdat
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
r_int
id|need_more_balance
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|zone_t
op_star
id|zone
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pgdat-&gt;nr_zones
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|i
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zone-&gt;need_balance
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_to_free_pages
c_func
(paren
id|zone
comma
id|GFP_KSWAPD
comma
l_int|0
)paren
)paren
(brace
id|zone-&gt;need_balance
op_assign
l_int|0
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_classzone_need_balance
c_func
(paren
id|zone
)paren
)paren
id|need_more_balance
op_assign
l_int|1
suffix:semicolon
r_else
id|zone-&gt;need_balance
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|need_more_balance
suffix:semicolon
)brace
DECL|function|kswapd_balance
r_static
r_void
id|kswapd_balance
c_func
(paren
r_void
)paren
(brace
r_int
id|need_more_balance
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_do
(brace
id|need_more_balance
op_assign
l_int|0
suffix:semicolon
id|pgdat
op_assign
id|pgdat_list
suffix:semicolon
r_do
id|need_more_balance
op_or_assign
id|kswapd_balance_pgdat
c_func
(paren
id|pgdat
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pgdat
op_assign
id|pgdat-&gt;node_next
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|need_more_balance
)paren
suffix:semicolon
)brace
DECL|function|kswapd_can_sleep_pgdat
r_static
r_int
id|kswapd_can_sleep_pgdat
c_func
(paren
id|pg_data_t
op_star
id|pgdat
)paren
(brace
id|zone_t
op_star
id|zone
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pgdat-&gt;nr_zones
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|zone
op_assign
id|pgdat-&gt;node_zones
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|zone-&gt;need_balance
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kswapd_can_sleep
r_static
r_int
id|kswapd_can_sleep
c_func
(paren
r_void
)paren
(brace
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
id|pgdat
op_assign
id|pgdat_list
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|kswapd_can_sleep_pgdat
c_func
(paren
id|pgdat
)paren
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|pgdat
op_assign
id|pgdat-&gt;node_next
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The background pageout daemon, started as a kernel thread&n; * from the init process. &n; *&n; * This basically trickles out pages so that we have _some_&n; * free memory available even if there is no other activity&n; * that frees anything up. This is needed for things like routing&n; * etc, where we otherwise might have all activity going on in&n; * asynchronous contexts that cannot page things out.&n; *&n; * If there are applications that are active memory-allocators&n; * (most normal use), this basically shouldn&squot;t matter.&n; */
DECL|function|kswapd
r_int
id|kswapd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;kswapd&quot;
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|tsk-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the memory management that we&squot;re a &quot;memory allocator&quot;,&n;&t; * and that if we need more memory we should get access to it&n;&t; * regardless (see &quot;__alloc_pages()&quot;). &quot;kswapd&quot; should&n;&t; * never get caught in the normal page freeing logic.&n;&t; *&n;&t; * (Kswapd normally doesn&squot;t need memory anyway, but sometimes&n;&t; * you need a small amount of memory in order to be able to&n;&t; * page out something else, and this flag essentially protects&n;&t; * us from recursively trying to free more memory as we&squot;re&n;&t; * trying to free the first piece of memory in the first place).&n;&t; */
id|tsk-&gt;flags
op_or_assign
id|PF_MEMALLOC
suffix:semicolon
multiline_comment|/*&n;&t; * Kswapd main loop.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kswapd_can_sleep
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|kswapd_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we actually get into a low-memory situation,&n;&t;&t; * the processes needing more memory will wake us&n;&t;&t; * up on a more timely basis.&n;&t;&t; */
id|kswapd_balance
c_func
(paren
)paren
suffix:semicolon
id|run_task_queue
c_func
(paren
op_amp
id|tq_disk
)paren
suffix:semicolon
)brace
)brace
DECL|function|kswapd_init
r_static
r_int
id|__init
id|kswapd_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Starting kswapd&bslash;n&quot;
)paren
suffix:semicolon
id|swap_setup
c_func
(paren
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|kswapd
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGNAL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|kswapd_init
)paren
eof
