multiline_comment|/*&n; * mm/rmap.c - physical to virtual reverse mappings&n; *&n; * Copyright 2001, Rik van Riel &lt;riel@conectiva.com.br&gt;&n; * Released under the General Public License (GPL).&n; *&n; * Simple, low overhead reverse mapping scheme.&n; * Please try to keep this thing as modular as possible.&n; *&n; * Provides methods for unmapping each kind of mapped page:&n; * the anon methods track anonymous pages, and&n; * the file methods track pages belonging to an inode.&n; *&n; * Original design by Rik van Riel &lt;riel@conectiva.com.br&gt; 2001&n; * File methods by Dave McCracken &lt;dmccr@us.ibm.com&gt; 2003, 2004&n; * Anonymous methods by Andrea Arcangeli &lt;andrea@suse.de&gt; 2004&n; * Contributions by Hugh Dickins &lt;hugh@veritas.com&gt; 2003, 2004&n; */
multiline_comment|/*&n; * Locking: see &quot;Lock ordering&quot; summary in filemap.c.&n; * In swapout, page_map_lock is held on entry to page_referenced and&n; * try_to_unmap, so they trylock for i_mmap_lock and page_table_lock.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/rmap.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
singleline_comment|//#define RMAP_DEBUG /* can be enabled only for debugging */
DECL|variable|anon_vma_cachep
id|kmem_cache_t
op_star
id|anon_vma_cachep
suffix:semicolon
DECL|function|validate_anon_vma
r_static
r_inline
r_void
id|validate_anon_vma
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|find_vma
)paren
(brace
macro_line|#ifdef RMAP_DEBUG
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|find_vma-&gt;anon_vma
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|mapcount
op_assign
l_int|0
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|anon_vma-&gt;head
comma
id|anon_vma_node
)paren
(brace
id|mapcount
op_increment
suffix:semicolon
id|BUG_ON
c_func
(paren
id|mapcount
OG
l_int|100000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_eq
id|find_vma
)paren
id|found
op_assign
l_int|1
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|found
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* This must be called under the mmap_sem. */
DECL|function|anon_vma_prepare
r_int
id|anon_vma_prepare
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|vma-&gt;anon_vma
suffix:semicolon
id|might_sleep
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
op_logical_neg
id|anon_vma
)paren
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_struct
id|anon_vma
op_star
id|allocated
op_assign
l_int|NULL
suffix:semicolon
id|anon_vma
op_assign
id|find_mergeable_anon_vma
c_func
(paren
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|anon_vma
)paren
(brace
id|anon_vma
op_assign
id|anon_vma_alloc
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
op_logical_neg
id|anon_vma
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|allocated
op_assign
id|anon_vma
suffix:semicolon
)brace
multiline_comment|/* page_table_lock to protect against threads */
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|vma-&gt;anon_vma
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|allocated
)paren
id|spin_lock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|vma-&gt;anon_vma
op_assign
id|anon_vma
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|vma-&gt;anon_vma_node
comma
op_amp
id|anon_vma-&gt;head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allocated
)paren
id|spin_unlock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|allocated
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|allocated
)paren
)paren
id|anon_vma_free
c_func
(paren
id|allocated
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__anon_vma_merge
r_void
id|__anon_vma_merge
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|vm_area_struct
op_star
id|next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;anon_vma
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|next-&gt;anon_vma
)paren
suffix:semicolon
id|vma-&gt;anon_vma
op_assign
id|next-&gt;anon_vma
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|vma-&gt;anon_vma_node
comma
op_amp
id|next-&gt;anon_vma_node
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* if they&squot;re both non-null they must be the same */
id|BUG_ON
c_func
(paren
id|vma-&gt;anon_vma
op_ne
id|next-&gt;anon_vma
)paren
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|next-&gt;anon_vma_node
)paren
suffix:semicolon
)brace
DECL|function|__anon_vma_link
r_void
id|__anon_vma_link
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|vma-&gt;anon_vma
suffix:semicolon
r_if
c_cond
(paren
id|anon_vma
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|vma-&gt;anon_vma_node
comma
op_amp
id|anon_vma-&gt;head
)paren
suffix:semicolon
id|validate_anon_vma
c_func
(paren
id|vma
)paren
suffix:semicolon
)brace
)brace
DECL|function|anon_vma_link
r_void
id|anon_vma_link
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|vma-&gt;anon_vma
suffix:semicolon
r_if
c_cond
(paren
id|anon_vma
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|vma-&gt;anon_vma_node
comma
op_amp
id|anon_vma-&gt;head
)paren
suffix:semicolon
id|validate_anon_vma
c_func
(paren
id|vma
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|anon_vma_unlink
r_void
id|anon_vma_unlink
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|vma-&gt;anon_vma
suffix:semicolon
r_int
id|empty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|anon_vma
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|validate_anon_vma
c_func
(paren
id|vma
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|vma-&gt;anon_vma_node
)paren
suffix:semicolon
multiline_comment|/* We must garbage collect the anon_vma if it&squot;s empty */
id|empty
op_assign
id|list_empty
c_func
(paren
op_amp
id|anon_vma-&gt;head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|empty
)paren
id|anon_vma_free
c_func
(paren
id|anon_vma
)paren
suffix:semicolon
)brace
DECL|function|anon_vma_ctor
r_static
r_void
id|anon_vma_ctor
c_func
(paren
r_void
op_star
id|data
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
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|data
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|anon_vma-&gt;head
)paren
suffix:semicolon
)brace
)brace
DECL|function|anon_vma_init
r_void
id|__init
id|anon_vma_init
c_func
(paren
r_void
)paren
(brace
id|anon_vma_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;anon_vma&quot;
comma
r_sizeof
(paren
r_struct
id|anon_vma
)paren
comma
l_int|0
comma
id|SLAB_PANIC
comma
id|anon_vma_ctor
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* this needs the page-&gt;flags PG_maplock held */
DECL|function|clear_page_anon
r_static
r_inline
r_void
id|clear_page_anon
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|page-&gt;mapping
)paren
suffix:semicolon
id|page-&gt;mapping
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * At what user virtual address is page expected in vma?&n; */
r_static
r_inline
r_int
r_int
DECL|function|vma_address
id|vma_address
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|pgoff_t
id|pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|address
op_assign
id|vma-&gt;vm_start
op_plus
(paren
(paren
id|pgoff
op_minus
id|vma-&gt;vm_pgoff
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|address
OL
id|vma-&gt;vm_start
op_logical_or
id|address
op_ge
id|vma-&gt;vm_end
)paren
)paren
(brace
multiline_comment|/* page should be within any vma from prio_tree_next */
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageAnon
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|address
suffix:semicolon
)brace
multiline_comment|/*&n; * Subfunctions of page_referenced: page_referenced_one called&n; * repeatedly from either page_referenced_anon or page_referenced_file.&n; */
DECL|function|page_referenced_one
r_static
r_int
id|page_referenced_one
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
op_star
id|mapcount
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|referenced
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm-&gt;rss
)paren
r_goto
id|out
suffix:semicolon
id|address
op_assign
id|vma_address
c_func
(paren
id|page
comma
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_eq
op_minus
id|EFAULT
)paren
r_goto
id|out
suffix:semicolon
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
r_goto
id|out
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
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
id|pgd_present
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
r_goto
id|out_unmap
suffix:semicolon
r_if
c_cond
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
op_ne
id|pte_pfn
c_func
(paren
op_star
id|pte
)paren
)paren
r_goto
id|out_unmap
suffix:semicolon
r_if
c_cond
(paren
id|ptep_clear_flush_young
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
)paren
id|referenced
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|current-&gt;mm
op_logical_and
id|has_swap_token
c_func
(paren
id|mm
)paren
)paren
id|referenced
op_increment
suffix:semicolon
(paren
op_star
id|mapcount
)paren
op_decrement
suffix:semicolon
id|out_unmap
suffix:colon
id|pte_unmap
c_func
(paren
id|pte
)paren
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
id|out
suffix:colon
r_return
id|referenced
suffix:semicolon
)brace
DECL|function|page_referenced_anon
r_static
r_inline
r_int
id|page_referenced_anon
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
id|mapcount
op_assign
id|page-&gt;mapcount
suffix:semicolon
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
(paren
r_void
op_star
)paren
id|page-&gt;mapping
op_minus
id|PAGE_MAPPING_ANON
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|referenced
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|anon_vma-&gt;head
)paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|anon_vma-&gt;head
comma
id|anon_vma_node
)paren
(brace
id|referenced
op_add_assign
id|page_referenced_one
c_func
(paren
id|page
comma
id|vma
comma
op_amp
id|mapcount
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapcount
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
r_return
id|referenced
suffix:semicolon
)brace
multiline_comment|/**&n; * page_referenced_file - referenced check for object-based rmap&n; * @page: the page we&squot;re checking references on.&n; *&n; * For an object-based mapped page, find all the places it is mapped and&n; * check/clear the referenced flag.  This is done by following the page-&gt;mapping&n; * pointer, then walking the chain of vmas it holds.  It returns the number&n; * of references it found.&n; *&n; * This function is only called from page_referenced for object-based pages.&n; *&n; * The spinlock address_space-&gt;i_mmap_lock is tried.  If it can&squot;t be gotten,&n; * assume a reference count of 0, so try_to_unmap will then have a go.&n; */
DECL|function|page_referenced_file
r_static
r_inline
r_int
id|page_referenced_file
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
id|mapcount
op_assign
id|page-&gt;mapcount
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
id|pgoff_t
id|pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|prio_tree_iter
id|iter
suffix:semicolon
r_int
id|referenced
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|vma_prio_tree_foreach
c_func
(paren
id|vma
comma
op_amp
id|iter
comma
op_amp
id|mapping-&gt;i_mmap
comma
id|pgoff
comma
id|pgoff
)paren
(brace
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_LOCKED
op_or
id|VM_MAYSHARE
)paren
)paren
op_eq
(paren
id|VM_LOCKED
op_or
id|VM_MAYSHARE
)paren
)paren
(brace
id|referenced
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|referenced
op_add_assign
id|page_referenced_one
c_func
(paren
id|page
comma
id|vma
comma
op_amp
id|mapcount
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapcount
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
r_return
id|referenced
suffix:semicolon
)brace
multiline_comment|/**&n; * page_referenced - test if the page was referenced&n; * @page: the page to test&n; *&n; * Quick test_and_clear_referenced for all mappings to a page,&n; * returns the number of ptes which referenced the page.&n; * Caller needs to hold the rmap lock.&n; */
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
r_int
id|referenced
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|page_test_and_clear_young
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
id|page-&gt;mapcount
op_logical_and
id|page-&gt;mapping
)paren
(brace
r_if
c_cond
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
id|referenced
op_add_assign
id|page_referenced_anon
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|referenced
op_add_assign
id|page_referenced_file
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|referenced
suffix:semicolon
)brace
multiline_comment|/**&n; * page_add_anon_rmap - add pte mapping to an anonymous page&n; * @page:&t;the page to add the mapping to&n; * @vma:&t;the vm area in which the mapping is added&n; * @address:&t;the user virtual address mapped&n; *&n; * The caller needs to hold the mm-&gt;page_table_lock.&n; */
DECL|function|page_add_anon_rmap
r_void
id|page_add_anon_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
id|vma-&gt;anon_vma
suffix:semicolon
id|pgoff_t
id|index
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|anon_vma
)paren
suffix:semicolon
id|anon_vma
op_assign
(paren
r_void
op_star
)paren
id|anon_vma
op_plus
id|PAGE_MAPPING_ANON
suffix:semicolon
id|index
op_assign
(paren
id|address
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|index
op_add_assign
id|vma-&gt;vm_pgoff
suffix:semicolon
id|index
op_rshift_assign
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
suffix:semicolon
id|page_map_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
(brace
id|BUG_ON
c_func
(paren
id|page-&gt;mapping
)paren
suffix:semicolon
id|page-&gt;index
op_assign
id|index
suffix:semicolon
id|page-&gt;mapping
op_assign
(paren
r_struct
id|address_space
op_star
)paren
id|anon_vma
suffix:semicolon
id|inc_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
)brace
r_else
(brace
id|BUG_ON
c_func
(paren
id|page-&gt;index
op_ne
id|index
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|page-&gt;mapping
op_ne
(paren
r_struct
id|address_space
op_star
)paren
id|anon_vma
)paren
suffix:semicolon
)brace
id|page-&gt;mapcount
op_increment
suffix:semicolon
id|page_map_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * page_add_file_rmap - add pte mapping to a file page&n; * @page: the page to add the mapping to&n; *&n; * The caller needs to hold the mm-&gt;page_table_lock.&n; */
DECL|function|page_add_file_rmap
r_void
id|page_add_file_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
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
id|page_map_lock
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
id|inc_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
id|page-&gt;mapcount
op_increment
suffix:semicolon
id|page_map_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * page_remove_rmap - take down pte mapping from a page&n; * @page: page to remove mapping from&n; *&n; * Caller needs to hold the mm-&gt;page_table_lock.&n; */
DECL|function|page_remove_rmap
r_void
id|page_remove_rmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
suffix:semicolon
id|page_map_lock
c_func
(paren
id|page
)paren
suffix:semicolon
id|page-&gt;mapcount
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
(brace
r_if
c_cond
(paren
id|page_test_and_clear_dirty
c_func
(paren
id|page
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
id|clear_page_anon
c_func
(paren
id|page
)paren
suffix:semicolon
id|dec_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
)brace
id|page_map_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Subfunctions of try_to_unmap: try_to_unmap_one called&n; * repeatedly from either try_to_unmap_anon or try_to_unmap_file.&n; */
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|pteval
suffix:semicolon
r_int
id|ret
op_assign
id|SWAP_AGAIN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm-&gt;rss
)paren
r_goto
id|out
suffix:semicolon
id|address
op_assign
id|vma_address
c_func
(paren
id|page
comma
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_eq
op_minus
id|EFAULT
)paren
r_goto
id|out
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
r_goto
id|out
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
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
id|pgd_present
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
r_goto
id|out_unmap
suffix:semicolon
r_if
c_cond
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
op_ne
id|pte_pfn
c_func
(paren
op_star
id|pte
)paren
)paren
r_goto
id|out_unmap
suffix:semicolon
multiline_comment|/*&n;&t; * If the page is mlock()d, we cannot swap it out.&n;&t; * If it&squot;s recently referenced (perhaps page_referenced&n;&t; * skipped over this mm) then we should reactivate it.&n;&t; */
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_LOCKED
op_or
id|VM_RESERVED
)paren
)paren
op_logical_or
id|ptep_clear_flush_young
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
)paren
(brace
id|ret
op_assign
id|SWAP_FAIL
suffix:semicolon
r_goto
id|out_unmap
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Don&squot;t pull an anonymous page out from under get_user_pages.&n;&t; * GUP carefully breaks COW and raises page count (while holding&n;&t; * page_table_lock, as we have here) to make sure that the page&n;&t; * cannot be freed.  If we unmap that page here, a user write&n;&t; * access to the virtual address will bring back the page, but&n;&t; * its raised count will (ironically) be taken to mean it&squot;s not&n;&t; * an exclusive swap page, do_wp_page will replace it by a copy&n;&t; * page, and the user never get to see the data GUP was holding&n;&t; * the original page for.&n;&t; *&n;&t; * This test is also useful for when swapoff (unuse_process) has&n;&t; * to drop page lock: its reference to the page stops existing&n;&t; * ptes from being unmapped, so swapoff can make progress.&n;&t; */
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
op_logical_and
id|page_count
c_func
(paren
id|page
)paren
op_ne
id|page-&gt;mapcount
op_plus
l_int|2
)paren
(brace
id|ret
op_assign
id|SWAP_FAIL
suffix:semicolon
r_goto
id|out_unmap
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
id|pteval
op_assign
id|ptep_clear_flush
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
suffix:semicolon
multiline_comment|/* Move the dirty bit to the physical page now the pte is gone. */
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|pteval
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
(brace
id|swp_entry_t
id|entry
op_assign
(brace
dot
id|val
op_assign
id|page
op_member_access_from_pointer
r_private
)brace
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Store the swap location in the pte.&n;&t;&t; * See handle_pte_fault() ...&n;&t;&t; */
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
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
id|pte
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
id|pte
)paren
)paren
suffix:semicolon
)brace
id|mm-&gt;rss
op_decrement
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
suffix:semicolon
id|page-&gt;mapcount
op_decrement
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|out_unmap
suffix:colon
id|pte_unmap
c_func
(paren
id|pte
)paren
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
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * objrmap doesn&squot;t work for nonlinear VMAs because the assumption that&n; * offset-into-file correlates with offset-into-virtual-addresses does not hold.&n; * Consequently, given a particular page and its -&gt;index, we cannot locate the&n; * ptes which are mapping that page without an exhaustive linear search.&n; *&n; * So what this code does is a mini &quot;virtual scan&quot; of each nonlinear VMA which&n; * maps the file to which the target page belongs.  The -&gt;vm_private_data field&n; * holds the current cursor into that scan.  Successive searches will circulate&n; * around the vma&squot;s virtual address space.&n; *&n; * So as more replacement pressure is applied to the pages in a nonlinear VMA,&n; * more scanning pressure is placed against them as well.   Eventually pages&n; * will become fully unmapped and are eligible for eviction.&n; *&n; * For very sparsely populated VMAs this is a little inefficient - chances are&n; * there there won&squot;t be many ptes located within the scan cluster.  In this case&n; * maybe we could scan further - to the end of the pte page, perhaps.&n; */
DECL|macro|CLUSTER_SIZE
mdefine_line|#define CLUSTER_SIZE&t;min(32*PAGE_SIZE, PMD_SIZE)
DECL|macro|CLUSTER_MASK
mdefine_line|#define CLUSTER_MASK&t;(~(CLUSTER_SIZE - 1))
DECL|function|try_to_unmap_cluster
r_static
r_int
id|try_to_unmap_cluster
c_func
(paren
r_int
r_int
id|cursor
comma
r_int
r_int
op_star
id|mapcount
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|pteval
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|pfn
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
r_return
id|SWAP_FAIL
suffix:semicolon
id|address
op_assign
(paren
id|vma-&gt;vm_start
op_plus
id|cursor
)paren
op_amp
id|CLUSTER_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|CLUSTER_SIZE
suffix:semicolon
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
r_if
c_cond
(paren
id|end
OG
id|vma-&gt;vm_end
)paren
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
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
id|pgd_present
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
r_for
c_loop
(paren
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|address
OL
id|end
suffix:semicolon
id|pte
op_increment
comma
id|address
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
r_continue
suffix:semicolon
id|pfn
op_assign
id|pte_pfn
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|pfn
)paren
)paren
r_continue
suffix:semicolon
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ptep_clear_flush_young
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Nuke the page table entry. */
id|flush_cache_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
id|pteval
op_assign
id|ptep_clear_flush
c_func
(paren
id|vma
comma
id|address
comma
id|pte
)paren
suffix:semicolon
multiline_comment|/* If nonlinear, store the file page offset in the pte. */
r_if
c_cond
(paren
id|page-&gt;index
op_ne
id|linear_page_index
c_func
(paren
id|vma
comma
id|address
)paren
)paren
id|set_pte
c_func
(paren
id|pte
comma
id|pgoff_to_pte
c_func
(paren
id|page-&gt;index
)paren
)paren
suffix:semicolon
multiline_comment|/* Move the dirty bit to the physical page now the pte is gone. */
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|pteval
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_remove_rmap
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
id|mm-&gt;rss
op_decrement
suffix:semicolon
(paren
op_star
id|mapcount
)paren
op_decrement
suffix:semicolon
)brace
id|pte_unmap
c_func
(paren
id|pte
)paren
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
id|SWAP_AGAIN
suffix:semicolon
)brace
DECL|function|try_to_unmap_anon
r_static
r_inline
r_int
id|try_to_unmap_anon
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|anon_vma
op_star
id|anon_vma
op_assign
(paren
r_void
op_star
)paren
id|page-&gt;mapping
op_minus
id|PAGE_MAPPING_ANON
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|ret
op_assign
id|SWAP_AGAIN
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|list_empty
c_func
(paren
op_amp
id|anon_vma-&gt;head
)paren
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|anon_vma-&gt;head
comma
id|anon_vma_node
)paren
(brace
id|ret
op_assign
id|try_to_unmap_one
c_func
(paren
id|page
comma
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|SWAP_FAIL
op_logical_or
op_logical_neg
id|page-&gt;mapcount
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|anon_vma-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * try_to_unmap_file - unmap file page using the object-based rmap method&n; * @page: the page to unmap&n; *&n; * Find all the mappings of a page using the mapping pointer and the vma chains&n; * contained in the address_space struct it points to.&n; *&n; * This function is only called from try_to_unmap for object-based pages.&n; *&n; * The spinlock address_space-&gt;i_mmap_lock is tried.  If it can&squot;t be gotten,&n; * return a temporary error.&n; */
DECL|function|try_to_unmap_file
r_static
r_inline
r_int
id|try_to_unmap_file
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
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
id|pgoff_t
id|pgoff
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|prio_tree_iter
id|iter
suffix:semicolon
r_int
id|ret
op_assign
id|SWAP_AGAIN
suffix:semicolon
r_int
r_int
id|cursor
suffix:semicolon
r_int
r_int
id|max_nl_cursor
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|max_nl_size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|mapcount
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
)paren
r_return
id|ret
suffix:semicolon
id|vma_prio_tree_foreach
c_func
(paren
id|vma
comma
op_amp
id|iter
comma
op_amp
id|mapping-&gt;i_mmap
comma
id|pgoff
comma
id|pgoff
)paren
(brace
id|ret
op_assign
id|try_to_unmap_one
c_func
(paren
id|page
comma
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|SWAP_FAIL
op_logical_or
op_logical_neg
id|page-&gt;mapcount
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_nonlinear
)paren
)paren
r_goto
id|out
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|mapping-&gt;i_mmap_nonlinear
comma
id|shared.vm_set.list
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_LOCKED
op_or
id|VM_RESERVED
)paren
)paren
r_continue
suffix:semicolon
id|cursor
op_assign
(paren
r_int
r_int
)paren
id|vma-&gt;vm_private_data
suffix:semicolon
r_if
c_cond
(paren
id|cursor
OG
id|max_nl_cursor
)paren
id|max_nl_cursor
op_assign
id|cursor
suffix:semicolon
id|cursor
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|cursor
OG
id|max_nl_size
)paren
id|max_nl_size
op_assign
id|cursor
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_nl_size
op_eq
l_int|0
)paren
multiline_comment|/* any nonlinears locked or reserved */
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t try to search for this page in the nonlinear vmas,&n;&t; * and page_referenced wouldn&squot;t have found it anyway.  Instead&n;&t; * just walk the nonlinear vmas trying to age and unmap some.&n;&t; * The mapcount of the page we came in with is irrelevant,&n;&t; * but even so use it as a guide to how hard we should try?&n;&t; */
id|mapcount
op_assign
id|page-&gt;mapcount
suffix:semicolon
id|page_map_unlock
c_func
(paren
id|page
)paren
suffix:semicolon
id|cond_resched_lock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
id|max_nl_size
op_assign
(paren
id|max_nl_size
op_plus
id|CLUSTER_SIZE
op_minus
l_int|1
)paren
op_amp
id|CLUSTER_MASK
suffix:semicolon
r_if
c_cond
(paren
id|max_nl_cursor
op_eq
l_int|0
)paren
id|max_nl_cursor
op_assign
id|CLUSTER_SIZE
suffix:semicolon
r_do
(brace
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|mapping-&gt;i_mmap_nonlinear
comma
id|shared.vm_set.list
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_LOCKED
op_or
id|VM_RESERVED
)paren
)paren
r_continue
suffix:semicolon
id|cursor
op_assign
(paren
r_int
r_int
)paren
id|vma-&gt;vm_private_data
suffix:semicolon
r_while
c_loop
(paren
id|vma-&gt;vm_mm-&gt;rss
op_logical_and
id|cursor
OL
id|max_nl_cursor
op_logical_and
id|cursor
OL
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
(brace
id|ret
op_assign
id|try_to_unmap_cluster
c_func
(paren
id|cursor
comma
op_amp
id|mapcount
comma
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|SWAP_FAIL
)paren
r_break
suffix:semicolon
id|cursor
op_add_assign
id|CLUSTER_SIZE
suffix:semicolon
id|vma-&gt;vm_private_data
op_assign
(paren
r_void
op_star
)paren
id|cursor
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|mapcount
op_le
l_int|0
)paren
r_goto
id|relock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
id|SWAP_FAIL
)paren
id|vma-&gt;vm_private_data
op_assign
(paren
r_void
op_star
)paren
id|max_nl_cursor
suffix:semicolon
id|ret
op_assign
id|SWAP_AGAIN
suffix:semicolon
)brace
id|cond_resched_lock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
id|max_nl_cursor
op_add_assign
id|CLUSTER_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|max_nl_cursor
op_le
id|max_nl_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t loop forever (perhaps all the remaining pages are&n;&t; * in locked vmas).  Reset cursor on all unreserved nonlinear&n;&t; * vmas, now forgetting on which ones it had fallen behind.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|vma
comma
op_amp
id|mapping-&gt;i_mmap_nonlinear
comma
id|shared.vm_set.list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_RESERVED
)paren
)paren
id|vma-&gt;vm_private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|relock
suffix:colon
id|page_map_lock
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * try_to_unmap - try to remove all page table mappings to a page&n; * @page: the page to get unmapped&n; *&n; * Tries to remove all the page table entries which are mapping this&n; * page, used in the pageout path.  Caller must hold the page lock&n; * and its rmap lock.  Return values are:&n; *&n; * SWAP_SUCCESS&t;- we succeeded in removing all mappings&n; * SWAP_AGAIN&t;- we missed a trylock, try again later&n; * SWAP_FAIL&t;- the page is unswappable&n; */
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
r_int
id|ret
suffix:semicolon
id|BUG_ON
c_func
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
id|ret
op_assign
id|try_to_unmap_anon
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|try_to_unmap_file
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;mapcount
)paren
(brace
r_if
c_cond
(paren
id|page_test_and_clear_dirty
c_func
(paren
id|page
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageAnon
c_func
(paren
id|page
)paren
)paren
id|clear_page_anon
c_func
(paren
id|page
)paren
suffix:semicolon
id|dec_page_state
c_func
(paren
id|nr_mapped
)paren
suffix:semicolon
id|ret
op_assign
id|SWAP_SUCCESS
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
