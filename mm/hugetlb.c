multiline_comment|/*&n; * Generic hugetlb support.&n; * (C) William Irwin, April 2004&n; */
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
DECL|variable|hugetlb_zero
DECL|variable|hugetlb_infinity
r_const
r_int
r_int
id|hugetlb_zero
op_assign
l_int|0
comma
id|hugetlb_infinity
op_assign
op_complement
l_int|0UL
suffix:semicolon
DECL|variable|nr_huge_pages
DECL|variable|free_huge_pages
r_static
r_int
r_int
id|nr_huge_pages
comma
id|free_huge_pages
suffix:semicolon
DECL|variable|max_huge_pages
r_int
r_int
id|max_huge_pages
suffix:semicolon
DECL|variable|hugepage_freelists
r_static
r_struct
id|list_head
id|hugepage_freelists
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|hugetlb_lock
r_static
id|spinlock_t
id|hugetlb_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|enqueue_huge_page
r_static
r_void
id|enqueue_huge_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;lru
comma
op_amp
id|hugepage_freelists
(braket
id|page_zone
c_func
(paren
id|page
)paren
op_member_access_from_pointer
id|zone_pgdat-&gt;node_id
)braket
)paren
suffix:semicolon
)brace
DECL|function|dequeue_huge_page
r_static
r_struct
id|page
op_star
id|dequeue_huge_page
c_func
(paren
r_void
)paren
(brace
r_int
id|nid
op_assign
id|numa_node_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|hugepage_freelists
(braket
id|nid
)braket
)paren
)paren
(brace
r_for
c_loop
(paren
id|nid
op_assign
l_int|0
suffix:semicolon
id|nid
OL
id|MAX_NUMNODES
suffix:semicolon
op_increment
id|nid
)paren
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|hugepage_freelists
(braket
id|nid
)braket
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nid
op_ge
l_int|0
op_logical_and
id|nid
OL
id|MAX_NUMNODES
op_logical_and
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|hugepage_freelists
(braket
id|nid
)braket
)paren
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|hugepage_freelists
(braket
id|nid
)braket
dot
id|next
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
)brace
DECL|function|alloc_fresh_huge_page
r_static
r_struct
id|page
op_star
id|alloc_fresh_huge_page
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|nid
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|alloc_pages_node
c_func
(paren
id|nid
comma
id|GFP_HIGHUSER
op_or
id|__GFP_COMP
comma
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
id|nid
op_assign
(paren
id|nid
op_plus
l_int|1
)paren
op_mod
id|numnodes
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|free_huge_page
r_void
id|free_huge_page
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
id|page_count
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
id|page
(braket
l_int|1
)braket
dot
id|mapping
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
id|enqueue_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_huge_pages
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
)brace
DECL|function|alloc_huge_page
r_struct
id|page
op_star
id|alloc_huge_page
c_func
(paren
r_void
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
id|page
op_assign
id|dequeue_huge_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|free_huge_pages
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|page
(braket
l_int|1
)braket
dot
id|mapping
op_assign
(paren
r_void
op_star
)paren
id|free_huge_page
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
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
op_increment
id|i
)paren
id|clear_highpage
c_func
(paren
op_amp
id|page
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|hugetlb_init
r_static
r_int
id|__init
id|hugetlb_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|page
op_star
id|page
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
id|MAX_NUMNODES
suffix:semicolon
op_increment
id|i
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hugepage_freelists
(braket
id|i
)braket
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
id|max_huge_pages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|page
op_assign
id|alloc_fresh_huge_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_break
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
id|enqueue_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
)brace
id|max_huge_pages
op_assign
id|free_huge_pages
op_assign
id|nr_huge_pages
op_assign
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Total HugeTLB memory allocated, %ld&bslash;n&quot;
comma
id|free_huge_pages
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hugetlb_init
id|module_init
c_func
(paren
id|hugetlb_init
)paren
suffix:semicolon
DECL|function|hugetlb_setup
r_static
r_int
id|__init
id|hugetlb_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|s
comma
l_string|&quot;%lu&quot;
comma
op_amp
id|max_huge_pages
)paren
op_le
l_int|0
)paren
id|max_huge_pages
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;hugepages=&quot;
comma
id|hugetlb_setup
)paren
suffix:semicolon
DECL|function|update_and_free_page
r_static
r_void
id|update_and_free_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|i
suffix:semicolon
id|nr_huge_pages
op_decrement
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
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page
(braket
id|i
)braket
dot
id|flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|PG_locked
op_or
l_int|1
op_lshift
id|PG_error
op_or
l_int|1
op_lshift
id|PG_referenced
op_or
l_int|1
op_lshift
id|PG_dirty
op_or
l_int|1
op_lshift
id|PG_active
op_or
l_int|1
op_lshift
id|PG_reserved
op_or
l_int|1
op_lshift
id|PG_private
op_or
l_int|1
op_lshift
id|PG_writeback
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
op_amp
id|page
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_pages
c_func
(paren
id|page
comma
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HIGHMEM
DECL|function|try_to_free_low
r_static
r_int
id|try_to_free_low
c_func
(paren
r_int
r_int
id|count
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
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NUMNODES
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|page
comma
op_amp
id|hugepage_freelists
(braket
id|i
)braket
comma
id|lru
)paren
(brace
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|page-&gt;lru
)paren
suffix:semicolon
id|update_and_free_page
c_func
(paren
id|page
)paren
suffix:semicolon
op_decrement
id|free_huge_pages
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#else
DECL|function|try_to_free_low
r_static
r_inline
r_int
id|try_to_free_low
c_func
(paren
r_int
r_int
id|count
)paren
(brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
DECL|function|set_max_huge_pages
r_static
r_int
r_int
id|set_max_huge_pages
c_func
(paren
r_int
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
OG
id|nr_huge_pages
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|alloc_fresh_huge_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|nr_huge_pages
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
id|enqueue_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|free_huge_pages
op_increment
suffix:semicolon
id|nr_huge_pages
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ge
id|nr_huge_pages
)paren
r_return
id|nr_huge_pages
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hugetlb_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
id|try_to_free_low
c_func
(paren
id|count
)paren
suffix:semicolon
id|count
OL
id|nr_huge_pages
suffix:semicolon
op_decrement
id|free_huge_pages
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|dequeue_huge_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_break
suffix:semicolon
id|update_and_free_page
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
id|hugetlb_lock
)paren
suffix:semicolon
r_return
id|nr_huge_pages
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SYSCTL
DECL|function|hugetlb_sysctl_handler
r_int
id|hugetlb_sysctl_handler
c_func
(paren
r_struct
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|file
comma
r_void
id|__user
op_star
id|buffer
comma
r_int
op_star
id|length
)paren
(brace
id|proc_doulongvec_minmax
c_func
(paren
id|table
comma
id|write
comma
id|file
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
id|max_huge_pages
op_assign
id|set_max_huge_pages
c_func
(paren
id|max_huge_pages
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SYSCTL */
DECL|function|hugetlb_report_meminfo
r_int
id|hugetlb_report_meminfo
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;HugePages_Total: %5lu&bslash;n&quot;
l_string|&quot;HugePages_Free:  %5lu&bslash;n&quot;
l_string|&quot;Hugepagesize:    %5lu kB&bslash;n&quot;
comma
id|nr_huge_pages
comma
id|free_huge_pages
comma
id|HPAGE_SIZE
op_div
l_int|1024
)paren
suffix:semicolon
)brace
DECL|function|is_hugepage_mem_enough
r_int
id|is_hugepage_mem_enough
c_func
(paren
r_int
id|size
)paren
(brace
r_return
(paren
id|size
op_plus
op_complement
id|HPAGE_MASK
)paren
op_div
id|HPAGE_SIZE
op_le
id|free_huge_pages
suffix:semicolon
)brace
multiline_comment|/* Return the number pages of memory we physically have, in PAGE_SIZE units. */
DECL|function|hugetlb_total_pages
r_int
r_int
id|hugetlb_total_pages
c_func
(paren
r_void
)paren
(brace
r_return
id|nr_huge_pages
op_star
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|variable|hugetlb_total_pages
id|EXPORT_SYMBOL
c_func
(paren
id|hugetlb_total_pages
)paren
suffix:semicolon
multiline_comment|/*&n; * We cannot handle pagefaults against hugetlb pages at all.  They cause&n; * handle_mm_fault() to try to instantiate regular-sized pages in the&n; * hugegpage VMA.  do_page_fault() is supposed to trap this, so BUG is we get&n; * this far.&n; */
DECL|function|hugetlb_nopage
r_static
r_struct
id|page
op_star
id|hugetlb_nopage
c_func
(paren
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
op_star
id|unused
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|hugetlb_vm_ops
r_struct
id|vm_operations_struct
id|hugetlb_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|hugetlb_nopage
comma
)brace
suffix:semicolon
DECL|function|zap_hugepage_range
r_void
id|zap_hugepage_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|length
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|unmap_hugepage_range
c_func
(paren
id|vma
comma
id|start
comma
id|start
op_plus
id|length
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
)brace
eof
