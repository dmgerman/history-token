multiline_comment|/*&n; * mm/rmap.c - physical to virtual reverse mappings&n; *&n; * Copyright 2001, Rik van Riel &lt;riel@conectiva.com.br&gt;&n; * Released under the General Public License (GPL).&n; *&n; *&n; * Simple, low overhead pte-based reverse mapping scheme.&n; * This is kept modular because we may want to experiment&n; * with object-based reverse mapping schemes. Please try&n; * to keep this thing as modular as possible.&n; */
multiline_comment|/*&n; * Locking:&n; * - the page-&gt;pte.chain is protected by the PG_chainlock bit,&n; *   which nests within the the mm-&gt;page_table_lock,&n; *   which nests within the page lock.&n; * - because swapout locking is opposite to the locking order&n; *   in the page fault path, the swapout path uses trylocks&n; *   on the mm-&gt;page_table_lock&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/rmap-locking.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/rmap.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* #define DEBUG_RMAP */
multiline_comment|/*&n; * Shared pages have a chain of pte_chain structures, used to locate&n; * all the mappings to this page. We only need a pointer to the pte&n; * here, the page struct for the page table page contains the process&n; * it belongs to and the offset within that process.&n; *&n; * We use an array of pte pointers in this structure to minimise cache misses&n; * while traversing reverse maps.&n; */
DECL|macro|NRPTE
mdefine_line|#define NRPTE ((L1_CACHE_BYTES - sizeof(unsigned long))/sizeof(pte_addr_t))
multiline_comment|/*&n; * next_and_idx encodes both the address of the next pte_chain and the&n; * offset of the highest-index used pte in ptes[].&n; */
DECL|struct|pte_chain
r_struct
id|pte_chain
(brace
DECL|member|next_and_idx
r_int
r_int
id|next_and_idx
suffix:semicolon
DECL|member|ptes
id|pte_addr_t
id|ptes
(braket
id|NRPTE
)braket
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
DECL|variable|pte_chain_cache
id|kmem_cache_t
op_star
id|pte_chain_cache
suffix:semicolon
DECL|function|pte_chain_next
r_static
r_inline
r_struct
id|pte_chain
op_star
id|pte_chain_next
c_func
(paren
r_struct
id|pte_chain
op_star
id|pte_chain
)paren
(brace
r_return
(paren
r_struct
id|pte_chain
op_star
)paren
(paren
id|pte_chain-&gt;next_and_idx
op_amp
op_complement
id|NRPTE
)paren
suffix:semicolon
)brace
DECL|function|pte_chain_ptr
r_static
r_inline
r_struct
id|pte_chain
op_star
id|pte_chain_ptr
c_func
(paren
r_int
r_int
id|pte_chain_addr
)paren
(brace
r_return
(paren
r_struct
id|pte_chain
op_star
)paren
(paren
id|pte_chain_addr
op_amp
op_complement
id|NRPTE
)paren
suffix:semicolon
)brace
DECL|function|pte_chain_idx
r_static
r_inline
r_int
id|pte_chain_idx
c_func
(paren
r_struct
id|pte_chain
op_star
id|pte_chain
)paren
(brace
r_return
id|pte_chain-&gt;next_and_idx
op_amp
id|NRPTE
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|pte_chain_encode
id|pte_chain_encode
c_func
(paren
r_struct
id|pte_chain
op_star
id|pte_chain
comma
r_int
id|idx
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|pte_chain
op_or
id|idx
suffix:semicolon
)brace
multiline_comment|/*&n; * pte_chain list management policy:&n; *&n; * - If a page has a pte_chain list then it is shared by at least two processes,&n; *   because a single sharing uses PageDirect. (Well, this isn&squot;t true yet,&n; *   coz this code doesn&squot;t collapse singletons back to PageDirect on the remove&n; *   path).&n; * - A pte_chain list has free space only in the head member - all succeeding&n; *   members are 100% full.&n; * - If the head element has free space, it occurs in its leading slots.&n; * - All free space in the pte_chain is at the start of the head member.&n; * - Insertion into the pte_chain puts a pte pointer in the last free slot of&n; *   the head member.&n; * - Removal from a pte chain moves the head pte of the head member onto the&n; *   victim pte and frees the head member if it became empty.&n; */
multiline_comment|/**&n; ** VM stuff below this comment&n; **/
multiline_comment|/**&n; * page_referenced - test if the page was referenced&n; * @page: the page to test&n; *&n; * Quick test_and_clear_referenced for all mappings to a page,&n; * returns the number of processes which referenced the page.&n; * Caller needs to hold the pte_chain_lock.&n; *&n; * If the page has a single-entry pte_chain, collapse that back to a PageDirect&n; * representation.  This way, it&squot;s only done under memory pressure.&n; */
DECL|function|page_referenced
r_int
id|page_referenced
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|pte_chain
op_star
id|pc
suffix:semicolon
r_int
id|referenced
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|TestClearPageReferenced
c_func
(paren
id|page
)paren
)paren
id|referenced
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageDirect
c_func
(paren
id|page
)paren
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
id|rmap_ptep_map
c_func
(paren
id|page-&gt;pte.direct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptep_test_and_clear_young
c_func
(paren
id|pte
)paren
)paren
id|referenced
op_increment
suffix:semicolon
id|rmap_ptep_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|nr_chains
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check all the page tables mapping this page. */
r_for
c_loop
(paren
id|pc
op_assign
id|page-&gt;pte.chain
suffix:semicolon
id|pc
suffix:semicolon
id|pc
op_assign
id|pte_chain_next
c_func
(paren
id|pc
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|NRPTE
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
id|pte_addr_t
id|pte_paddr
op_assign
id|pc-&gt;ptes
(braket
id|i
)braket
suffix:semicolon
id|pte_t
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_paddr
)paren
r_break
suffix:semicolon
id|p
op_assign
id|rmap_ptep_map
c_func
(paren
id|pte_paddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptep_test_and_clear_young
c_func
(paren
id|p
)paren
)paren
id|referenced
op_increment
suffix:semicolon
id|rmap_ptep_unmap
c_func
(paren
id|p
)paren
suffix:semicolon
id|nr_chains
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nr_chains
op_eq
l_int|1
)paren
(brace
id|pc
op_assign
id|page-&gt;pte.chain
suffix:semicolon
id|page-&gt;pte.direct
op_assign
id|pc-&gt;ptes
(braket
id|NRPTE
op_minus
l_int|1
)braket
suffix:semicolon
id|SetPageDirect
c_func
(paren
id|page
)paren
suffix:semicolon
id|pc-&gt;ptes
(braket
id|NRPTE
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|__pte_chain_free
c_func
(paren
id|pc
)paren
suffix:semicolon
)brace
)brace
r_return
id|referenced
suffix:semicolon
)brace
multiline_comment|/**&n; * page_add_rmap - add reverse mapping entry to a page&n; * @page: the page to add the mapping to&n; * @ptep: the page table entry mapping this page&n; *&n; * Add a new pte reverse mapping to a page.&n; * The caller needs to hold the mm-&gt;page_table_lock.&n; */
r_struct
id|pte_chain
op_star
DECL|function|page_add_rmap
id|page_add_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pte_t
op_star
id|ptep
comma
r_struct
id|pte_chain
op_star
id|pte_chain
)paren
(brace
id|pte_addr_t
id|pte_paddr
op_assign
id|ptep_to_paddr
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_struct
id|pte_chain
op_star
id|cur_pte_chain
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
)paren
op_logical_or
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_return
id|pte_chain
suffix:semicolon
id|pte_chain_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;pte.direct
op_eq
l_int|0
)paren
(brace
id|page-&gt;pte.direct
op_assign
id|pte_paddr
suffix:semicolon
id|SetPageDirect
c_func
(paren
id|page
)paren
suffix:semicolon
id|inc_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageDirect
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/* Convert a direct pointer into a pte_chain */
id|ClearPageDirect
c_func
(paren
id|page
)paren
suffix:semicolon
id|pte_chain-&gt;ptes
(braket
id|NRPTE
op_minus
l_int|1
)braket
op_assign
id|page-&gt;pte.direct
suffix:semicolon
id|pte_chain-&gt;ptes
(braket
id|NRPTE
op_minus
l_int|2
)braket
op_assign
id|pte_paddr
suffix:semicolon
id|pte_chain-&gt;next_and_idx
op_assign
id|pte_chain_encode
c_func
(paren
l_int|NULL
comma
id|NRPTE
op_minus
l_int|2
)paren
suffix:semicolon
id|page-&gt;pte.direct
op_assign
l_int|0
suffix:semicolon
id|page-&gt;pte.chain
op_assign
id|pte_chain
suffix:semicolon
id|pte_chain
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We consumed it */
r_goto
id|out
suffix:semicolon
)brace
id|cur_pte_chain
op_assign
id|page-&gt;pte.chain
suffix:semicolon
r_if
c_cond
(paren
id|cur_pte_chain-&gt;ptes
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* It&squot;s full */
id|pte_chain-&gt;next_and_idx
op_assign
id|pte_chain_encode
c_func
(paren
id|cur_pte_chain
comma
id|NRPTE
op_minus
l_int|1
)paren
suffix:semicolon
id|page-&gt;pte.chain
op_assign
id|pte_chain
suffix:semicolon
id|pte_chain-&gt;ptes
(braket
id|NRPTE
op_minus
l_int|1
)braket
op_assign
id|pte_paddr
suffix:semicolon
id|pte_chain
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We consumed it */
r_goto
id|out
suffix:semicolon
)brace
id|cur_pte_chain-&gt;ptes
(braket
id|pte_chain_idx
c_func
(paren
id|cur_pte_chain
)paren
op_minus
l_int|1
)braket
op_assign
id|pte_paddr
suffix:semicolon
id|cur_pte_chain-&gt;next_and_idx
op_decrement
suffix:semicolon
id|out
suffix:colon
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|pte_chain
suffix:semicolon
)brace
multiline_comment|/**&n; * page_remove_rmap - take down reverse mapping to a page&n; * @page: page to remove mapping from&n; * @ptep: page table entry to remove&n; *&n; * Removes the reverse mapping from the pte_chain of the page,&n; * after that the caller can clear the page table entry and free&n; * the page.&n; * Caller needs to hold the mm-&gt;page_table_lock.&n; */
DECL|function|page_remove_rmap
r_void
id|page_remove_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_addr_t
id|pte_paddr
op_assign
id|ptep_to_paddr
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_struct
id|pte_chain
op_star
id|pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
)paren
op_logical_or
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
id|pte_chain_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_mapped
c_func
(paren
id|page
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/* remap_page_range() from a driver? */
r_if
c_cond
(paren
id|PageDirect
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;pte.direct
op_eq
id|pte_paddr
)paren
(brace
id|page-&gt;pte.direct
op_assign
l_int|0
suffix:semicolon
id|ClearPageDirect
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|pte_chain
op_star
id|start
op_assign
id|page-&gt;pte.chain
suffix:semicolon
r_struct
id|pte_chain
op_star
id|next
suffix:semicolon
r_int
id|victim_i
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|pc
op_assign
id|start
suffix:semicolon
id|pc
suffix:semicolon
id|pc
op_assign
id|next
)paren
(brace
r_int
id|i
suffix:semicolon
id|next
op_assign
id|pte_chain_next
c_func
(paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
id|prefetch
c_func
(paren
id|next
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pte_chain_idx
c_func
(paren
id|pc
)paren
suffix:semicolon
id|i
OL
id|NRPTE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pte_addr_t
id|pa
op_assign
id|pc-&gt;ptes
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|victim_i
op_eq
op_minus
l_int|1
)paren
id|victim_i
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|pa
op_ne
id|pte_paddr
)paren
r_continue
suffix:semicolon
id|pc-&gt;ptes
(braket
id|i
)braket
op_assign
id|start-&gt;ptes
(braket
id|victim_i
)braket
suffix:semicolon
id|start-&gt;ptes
(braket
id|victim_i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|victim_i
op_eq
id|NRPTE
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Emptied a pte_chain */
id|page-&gt;pte.chain
op_assign
id|pte_chain_next
c_func
(paren
id|start
)paren
suffix:semicolon
id|__pte_chain_free
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
r_else
(brace
id|start-&gt;next_and_idx
op_increment
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|page_mapped
c_func
(paren
id|page
)paren
)paren
id|dec_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|pte_chain_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * try_to_unmap_one - worker function for try_to_unmap&n; * @page: page to unmap&n; * @ptep: page table entry to unmap from page&n; *&n; * Internal helper function for try_to_unmap, called for each page&n; * table entry mapping a page. Because locking order here is opposite&n; * to the locking order used by the page fault path, we use trylocks.&n; * Locking:&n; *&t;    page lock&t;&t;&t;shrink_list(), trylock&n; *&t;&t;pte_chain_lock&t;&t;shrink_list()&n; *&t;&t;    mm-&gt;page_table_lock&t;try_to_unmap_one(), trylock&n; */
r_static
r_int
id|FASTCALL
c_func
(paren
id|try_to_unmap_one
c_func
(paren
r_struct
id|page
op_star
comma
id|pte_addr_t
)paren
)paren
suffix:semicolon
DECL|function|try_to_unmap_one
r_static
r_int
id|try_to_unmap_one
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pte_addr_t
id|paddr
)paren
(brace
id|pte_t
op_star
id|ptep
op_assign
id|rmap_ptep_map
c_func
(paren
id|paddr
)paren
suffix:semicolon
r_int
r_int
id|address
op_assign
id|ptep_to_address
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|ptep_to_mm
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need the page_table_lock to protect us from page faults,&n;&t; * munmap, fork, etc...&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
)paren
(brace
id|rmap_ptep_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_return
id|SWAP_AGAIN
suffix:semicolon
)brace
multiline_comment|/* During mremap, it&squot;s possible pages are not in a VMA. */
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
op_logical_neg
id|vma
)paren
(brace
id|ret
op_assign
id|SWAP_FAIL
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/* The page is mlock()d, we cannot swap it out. */
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
(brace
id|ret
op_assign
id|SWAP_FAIL
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/* Nuke the page table entry. */
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
id|ptep
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
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Store the swap location in the pte.&n;&t;&t; * See handle_pte_fault() ...&n;&t;&t; */
id|swp_entry_t
id|entry
op_assign
(brace
dot
id|val
op_assign
id|page-&gt;index
)brace
suffix:semicolon
id|swap_duplicate
c_func
(paren
id|entry
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|swp_entry_to_pte
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|pte_file
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|pgidx
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If a nonlinear mapping then store the file page offset&n;&t;&t; * in the pte.&n;&t;&t; */
id|pgidx
op_assign
(paren
id|address
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pgidx
op_add_assign
id|vma-&gt;vm_pgoff
suffix:semicolon
id|pgidx
op_rshift_assign
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
op_ne
id|pgidx
)paren
(brace
id|set_pte
c_func
(paren
id|ptep
comma
id|pgoff_to_pte
c_func
(paren
id|page-&gt;index
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte_file
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Move the dirty bit to the physical page now the pte is gone. */
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
id|mm-&gt;rss
op_decrement
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
id|SWAP_SUCCESS
suffix:semicolon
id|out_unlock
suffix:colon
id|rmap_ptep_unmap
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * try_to_unmap - try to remove all page table mappings to a page&n; * @page: the page to get unmapped&n; *&n; * Tries to remove all the page table entries which are mapping this&n; * page, used in the pageout path.  Caller must hold the page lock&n; * and its pte chain lock.  Return values are:&n; *&n; * SWAP_SUCCESS&t;- we succeeded in removing all mappings&n; * SWAP_AGAIN&t;- we missed a trylock, try again later&n; * SWAP_FAIL&t;- the page is unswappable&n; */
DECL|function|try_to_unmap
r_int
id|try_to_unmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|pte_chain
op_star
id|pc
comma
op_star
id|next_pc
comma
op_star
id|start
suffix:semicolon
r_int
id|ret
op_assign
id|SWAP_SUCCESS
suffix:semicolon
r_int
id|victim_i
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* This page should not be on the pageout lists. */
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
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
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We need backing store to swap out a page. */
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapping
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageDirect
c_func
(paren
id|page
)paren
)paren
(brace
id|ret
op_assign
id|try_to_unmap_one
c_func
(paren
id|page
comma
id|page-&gt;pte.direct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|SWAP_SUCCESS
)paren
(brace
id|page-&gt;pte.direct
op_assign
l_int|0
suffix:semicolon
id|ClearPageDirect
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
id|start
op_assign
id|page-&gt;pte.chain
suffix:semicolon
r_for
c_loop
(paren
id|pc
op_assign
id|start
suffix:semicolon
id|pc
suffix:semicolon
id|pc
op_assign
id|next_pc
)paren
(brace
r_int
id|i
suffix:semicolon
id|next_pc
op_assign
id|pte_chain_next
c_func
(paren
id|pc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next_pc
)paren
id|prefetch
c_func
(paren
id|next_pc
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pte_chain_idx
c_func
(paren
id|pc
)paren
suffix:semicolon
id|i
OL
id|NRPTE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pte_addr_t
id|pte_paddr
op_assign
id|pc-&gt;ptes
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_paddr
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|victim_i
op_eq
op_minus
l_int|1
)paren
id|victim_i
op_assign
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|try_to_unmap_one
c_func
(paren
id|page
comma
id|pte_paddr
)paren
)paren
(brace
r_case
id|SWAP_SUCCESS
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * Release a slot.  If we&squot;re releasing the&n;&t;&t;&t;&t; * first pte in the first pte_chain then&n;&t;&t;&t;&t; * pc-&gt;ptes[i] and start-&gt;ptes[victim_i] both&n;&t;&t;&t;&t; * refer to the same thing.  It works out.&n;&t;&t;&t;&t; */
id|pc-&gt;ptes
(braket
id|i
)braket
op_assign
id|start-&gt;ptes
(braket
id|victim_i
)braket
suffix:semicolon
id|start-&gt;ptes
(braket
id|victim_i
)braket
op_assign
l_int|0
suffix:semicolon
id|victim_i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|victim_i
op_eq
id|NRPTE
)paren
(brace
id|page-&gt;pte.chain
op_assign
id|pte_chain_next
c_func
(paren
id|start
)paren
suffix:semicolon
id|__pte_chain_free
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_assign
id|page-&gt;pte.chain
suffix:semicolon
id|victim_i
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|start-&gt;next_and_idx
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SWAP_AGAIN
suffix:colon
multiline_comment|/* Skip this pte, remembering status. */
id|ret
op_assign
id|SWAP_AGAIN
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|SWAP_FAIL
suffix:colon
id|ret
op_assign
id|SWAP_FAIL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|page_mapped
c_func
(paren
id|page
)paren
)paren
id|dec_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; ** No more VM stuff below this comment, only pte_chain helper&n; ** functions.&n; **/
DECL|function|pte_chain_ctor
r_static
r_void
id|pte_chain_ctor
c_func
(paren
r_void
op_star
id|p
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|pte_chain
op_star
id|pc
op_assign
id|p
suffix:semicolon
id|memset
c_func
(paren
id|pc
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pc
)paren
)paren
suffix:semicolon
)brace
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|pte_chain
op_star
comma
id|local_pte_chain
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/**&n; * __pte_chain_free - free pte_chain structure&n; * @pte_chain: pte_chain struct to free&n; */
DECL|function|__pte_chain_free
r_void
id|__pte_chain_free
c_func
(paren
r_struct
id|pte_chain
op_star
id|pte_chain
)paren
(brace
r_struct
id|pte_chain
op_star
op_star
id|pte_chainp
suffix:semicolon
id|pte_chainp
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|local_pte_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_chain-&gt;next_and_idx
)paren
id|pte_chain-&gt;next_and_idx
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pte_chainp
)paren
id|kmem_cache_free
c_func
(paren
id|pte_chain_cache
comma
op_star
id|pte_chainp
)paren
suffix:semicolon
op_star
id|pte_chainp
op_assign
id|pte_chain
suffix:semicolon
id|put_cpu_var
c_func
(paren
id|local_pte_chain
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pte_chain_alloc(): allocate a pte_chain structure for use by page_add_rmap().&n; *&n; * The caller of page_add_rmap() must perform the allocation because&n; * page_add_rmap() is invariably called under spinlock.  Often, page_add_rmap()&n; * will not actually use the pte_chain, because there is space available in one&n; * of the existing pte_chains which are attached to the page.  So the case of&n; * allocating and then freeing a single pte_chain is specially optimised here,&n; * with a one-deep per-cpu cache.&n; */
DECL|function|pte_chain_alloc
r_struct
id|pte_chain
op_star
id|pte_chain_alloc
c_func
(paren
r_int
id|gfp_flags
)paren
(brace
r_struct
id|pte_chain
op_star
id|ret
suffix:semicolon
r_struct
id|pte_chain
op_star
op_star
id|pte_chainp
suffix:semicolon
r_if
c_cond
(paren
id|gfp_flags
op_amp
id|__GFP_WAIT
)paren
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|pte_chainp
op_assign
op_amp
id|get_cpu_var
c_func
(paren
id|local_pte_chain
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pte_chainp
)paren
(brace
id|ret
op_assign
op_star
id|pte_chainp
suffix:semicolon
op_star
id|pte_chainp
op_assign
l_int|NULL
suffix:semicolon
id|put_cpu_var
c_func
(paren
id|local_pte_chain
)paren
suffix:semicolon
)brace
r_else
(brace
id|put_cpu_var
c_func
(paren
id|local_pte_chain
)paren
suffix:semicolon
id|ret
op_assign
id|kmem_cache_alloc
c_func
(paren
id|pte_chain_cache
comma
id|gfp_flags
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pte_chain_init
r_void
id|__init
id|pte_chain_init
c_func
(paren
r_void
)paren
(brace
id|pte_chain_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;pte_chain&quot;
comma
r_sizeof
(paren
r_struct
id|pte_chain
)paren
comma
l_int|0
comma
id|SLAB_MUST_HWCACHE_ALIGN
comma
id|pte_chain_ctor
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_chain_cache
)paren
id|panic
c_func
(paren
l_string|&quot;failed to create pte_chain cache!&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
