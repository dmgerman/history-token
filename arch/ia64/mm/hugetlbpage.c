multiline_comment|/*&n; * IA-64 Huge TLB Page Support for Kernel.&n; *&n; * Copyright (C) 2002-2004 Rohit Seth &lt;rohit.seth@intel.com&gt;&n; * Copyright (C) 2003-2004 Ken Chen &lt;kenneth.w.chen@intel.com&gt;&n; *&n; * Sep, 2003: add numa support&n; * Feb, 2004: dynamic hugetlb page size via boot parameter&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|htlbpagemem
r_static
r_int
id|htlbpagemem
suffix:semicolon
DECL|variable|htlbpage_max
r_int
id|htlbpage_max
suffix:semicolon
DECL|variable|htlbzone_pages
r_static
r_int
id|htlbzone_pages
suffix:semicolon
DECL|variable|hpage_shift
r_int
r_int
id|hpage_shift
op_assign
id|HPAGE_SHIFT_DEFAULT
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
DECL|variable|htlbpage_lock
r_static
id|spinlock_t
id|htlbpage_lock
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
id|page-&gt;list
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
r_void
id|free_huge_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|function|alloc_hugetlb_page
r_static
r_struct
id|page
op_star
id|alloc_hugetlb_page
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
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
id|htlbpage_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|htlbpagemem
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
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
id|page-&gt;lru.prev
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
r_static
id|pte_t
op_star
DECL|function|huge_pte_alloc
id|huge_pte_alloc
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|taddr
op_assign
id|htlbpage_to_page
c_func
(paren
id|addr
)paren
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
op_assign
l_int|NULL
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|taddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|mm
comma
id|pgd
comma
id|taddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
)paren
id|pte
op_assign
id|pte_alloc_map
c_func
(paren
id|mm
comma
id|pmd
comma
id|taddr
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
r_static
id|pte_t
op_star
DECL|function|huge_pte_offset
id|huge_pte_offset
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|taddr
op_assign
id|htlbpage_to_page
c_func
(paren
id|addr
)paren
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
op_assign
l_int|NULL
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|taddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|taddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|taddr
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry) { pte_val(entry) |= _PAGE_P; }
r_static
r_void
DECL|function|set_huge_pte
id|set_huge_pte
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
r_struct
id|page
op_star
id|page
comma
id|pte_t
op_star
id|page_table
comma
r_int
id|write_access
)paren
(brace
id|pte_t
id|entry
suffix:semicolon
id|mm-&gt;rss
op_add_assign
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_access
)paren
(brace
id|entry
op_assign
id|pte_mkwrite
c_func
(paren
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
id|entry
op_assign
id|pte_wrprotect
c_func
(paren
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
)paren
suffix:semicolon
id|entry
op_assign
id|pte_mkyoung
c_func
(paren
id|entry
)paren
suffix:semicolon
id|mk_pte_huge
c_func
(paren
id|entry
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|page_table
comma
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This function checks for proper alignment of input addr and len parameters.&n; */
DECL|function|is_aligned_hugepage_range
r_int
id|is_aligned_hugepage_range
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_amp
op_complement
id|HPAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|HPAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|REGION_NUMBER
c_func
(paren
id|addr
)paren
op_ne
id|REGION_HPAGE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_hugetlb_page_range
r_int
id|copy_hugetlb_page_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|dst
comma
r_struct
id|mm_struct
op_star
id|src
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|pte_t
op_star
id|src_pte
comma
op_star
id|dst_pte
comma
id|entry
suffix:semicolon
r_struct
id|page
op_star
id|ptepage
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|vma-&gt;vm_start
suffix:semicolon
r_int
r_int
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|end
)paren
(brace
id|dst_pte
op_assign
id|huge_pte_alloc
c_func
(paren
id|dst
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_pte
)paren
r_goto
id|nomem
suffix:semicolon
id|src_pte
op_assign
id|huge_pte_offset
c_func
(paren
id|src
comma
id|addr
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|src_pte
suffix:semicolon
id|ptepage
op_assign
id|pte_page
c_func
(paren
id|entry
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|ptepage
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|dst_pte
comma
id|entry
)paren
suffix:semicolon
id|dst-&gt;rss
op_add_assign
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
id|addr
op_add_assign
id|HPAGE_SIZE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|nomem
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_int
DECL|function|follow_hugetlb_page
id|follow_hugetlb_page
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
r_struct
id|page
op_star
op_star
id|pages
comma
r_struct
id|vm_area_struct
op_star
op_star
id|vmas
comma
r_int
r_int
op_star
id|st
comma
r_int
op_star
id|length
comma
r_int
id|i
)paren
(brace
id|pte_t
op_star
id|ptep
comma
id|pte
suffix:semicolon
r_int
r_int
id|start
op_assign
op_star
id|st
suffix:semicolon
r_int
r_int
id|pstart
suffix:semicolon
r_int
id|len
op_assign
op_star
id|length
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_do
(brace
id|pstart
op_assign
id|start
op_amp
id|HPAGE_MASK
suffix:semicolon
id|ptep
op_assign
id|huge_pte_offset
c_func
(paren
id|mm
comma
id|start
)paren
suffix:semicolon
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
id|back1
suffix:colon
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages
)paren
(brace
id|page
op_add_assign
(paren
(paren
id|start
op_amp
op_complement
id|HPAGE_MASK
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|pages
(braket
id|i
)braket
op_assign
id|page
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vmas
)paren
id|vmas
(braket
id|i
)braket
op_assign
id|vma
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|start
op_amp
id|HPAGE_MASK
)paren
op_eq
id|pstart
)paren
op_logical_and
id|len
op_logical_and
(paren
id|start
OL
id|vma-&gt;vm_end
)paren
)paren
r_goto
id|back1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_logical_and
id|start
OL
id|vma-&gt;vm_end
)paren
suffix:semicolon
op_star
id|length
op_assign
id|len
suffix:semicolon
op_star
id|st
op_assign
id|start
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|hugepage_vma
r_struct
id|vm_area_struct
op_star
id|hugepage_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;used_hugetlb
)paren
(brace
r_if
c_cond
(paren
id|REGION_NUMBER
c_func
(paren
id|addr
)paren
op_eq
id|REGION_HPAGE
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_logical_and
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
r_return
id|vma
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|follow_huge_addr
r_struct
id|page
op_star
id|follow_huge_addr
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
id|addr
comma
r_int
id|write
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|ptep
op_assign
id|huge_pte_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
id|page
op_add_assign
(paren
(paren
id|addr
op_amp
op_complement
id|HPAGE_MASK
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|pmd_huge
r_int
id|pmd_huge
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|page
op_star
DECL|function|follow_huge_pmd
id|follow_huge_pmd
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
comma
id|pmd_t
op_star
id|pmd
comma
r_int
id|write
)paren
(brace
r_return
l_int|NULL
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
id|BUG_ON
c_func
(paren
id|page-&gt;mapping
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|page-&gt;list
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|enqueue_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|htlbpagemem
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
)brace
DECL|function|huge_page_release
r_void
id|huge_page_release
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
op_logical_neg
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
id|free_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Same as generic free_pgtables(), except constant PGDIR_* and pgd_offset&n; * are hugetlb region specific.&n; */
DECL|function|hugetlb_free_pgtables
r_void
id|hugetlb_free_pgtables
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
r_struct
id|vm_area_struct
op_star
id|prev
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
r_int
id|first
op_assign
id|start
op_amp
id|HUGETLB_PGDIR_MASK
suffix:semicolon
r_int
r_int
id|last
op_assign
id|end
op_plus
id|HUGETLB_PGDIR_SIZE
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|start_index
comma
id|end_index
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tlb-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
)paren
(brace
id|prev
op_assign
id|mm-&gt;mmap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
)paren
r_goto
id|no_mmaps
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;vm_end
OG
id|start
)paren
(brace
r_if
c_cond
(paren
id|last
OG
id|prev-&gt;vm_start
)paren
id|last
op_assign
id|prev-&gt;vm_start
suffix:semicolon
r_goto
id|no_mmaps
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|next
op_assign
id|prev-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;vm_start
OL
id|start
)paren
(brace
id|prev
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last
OG
id|next-&gt;vm_start
)paren
id|last
op_assign
id|next-&gt;vm_start
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev-&gt;vm_end
OG
id|first
)paren
id|first
op_assign
id|prev-&gt;vm_end
op_plus
id|HUGETLB_PGDIR_SIZE
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|no_mmaps
suffix:colon
r_if
c_cond
(paren
id|last
OL
id|first
)paren
multiline_comment|/* for arches with discontiguous pgd indices */
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * If the PGD bits are not consecutive in the virtual address, the&n;&t; * old method of shifting the VA &gt;&gt; by PGDIR_SHIFT doesn&squot;t work.&n;&t; */
id|start_index
op_assign
id|pgd_index
c_func
(paren
id|htlbpage_to_page
c_func
(paren
id|first
)paren
)paren
suffix:semicolon
id|end_index
op_assign
id|pgd_index
c_func
(paren
id|htlbpage_to_page
c_func
(paren
id|last
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end_index
OG
id|start_index
)paren
(brace
id|clear_page_tables
c_func
(paren
id|tlb
comma
id|start_index
comma
id|end_index
op_minus
id|start_index
)paren
suffix:semicolon
)brace
)brace
DECL|function|unmap_hugepage_range
r_void
id|unmap_hugepage_range
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
id|end
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
id|pte_t
op_star
id|pte
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|BUG_ON
c_func
(paren
id|start
op_amp
(paren
id|HPAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|end
op_amp
(paren
id|HPAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|address
op_assign
id|start
suffix:semicolon
id|address
OL
id|end
suffix:semicolon
id|address
op_add_assign
id|HPAGE_SIZE
)paren
(brace
id|pte
op_assign
id|huge_pte_offset
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
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
r_continue
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|huge_page_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
id|mm-&gt;rss
op_sub_assign
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
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
DECL|function|hugetlb_prefault
r_int
id|hugetlb_prefault
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
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
id|current-&gt;mm
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|vma-&gt;vm_start
op_amp
op_complement
id|HPAGE_MASK
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|vma-&gt;vm_end
op_amp
op_complement
id|HPAGE_MASK
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|vma-&gt;vm_start
suffix:semicolon
id|addr
OL
id|vma-&gt;vm_end
suffix:semicolon
id|addr
op_add_assign
id|HPAGE_SIZE
)paren
(brace
r_int
r_int
id|idx
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
id|huge_pte_alloc
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
r_continue
suffix:semicolon
id|idx
op_assign
(paren
(paren
id|addr
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|HPAGE_SHIFT
)paren
op_plus
(paren
id|vma-&gt;vm_pgoff
op_rshift
(paren
id|HPAGE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|page
op_assign
id|find_get_page
c_func
(paren
id|mapping
comma
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
multiline_comment|/* charge the fs quota first */
r_if
c_cond
(paren
id|hugetlb_get_quota
c_func
(paren
id|mapping
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|page
op_assign
id|alloc_hugetlb_page
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
id|hugetlb_put_quota
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|add_to_page_cache
c_func
(paren
id|page
comma
id|mapping
comma
id|idx
comma
id|GFP_ATOMIC
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
id|ret
)paren
(brace
id|hugetlb_put_quota
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|free_huge_page
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
id|set_huge_pte
c_func
(paren
id|mm
comma
id|vma
comma
id|page
comma
id|pte
comma
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
suffix:semicolon
)brace
id|out
suffix:colon
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
DECL|function|hugetlb_get_unmapped_area
r_int
r_int
id|hugetlb_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vmm
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|RGN_MAP_LIMIT
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
op_complement
id|HPAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* This code assumes that REGION_HPAGE != 0. */
r_if
c_cond
(paren
(paren
id|REGION_NUMBER
c_func
(paren
id|addr
)paren
op_ne
id|REGION_HPAGE
)paren
op_logical_or
(paren
id|addr
op_amp
(paren
id|HPAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
id|addr
op_assign
id|HPAGE_REGION_BASE
suffix:semicolon
r_else
id|addr
op_assign
id|ALIGN
c_func
(paren
id|addr
comma
id|HPAGE_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vmm
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vmm
op_assign
id|vmm-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vmm || addr &lt; vmm-&gt;vm_end). */
r_if
c_cond
(paren
id|REGION_OFFSET
c_func
(paren
id|addr
)paren
op_plus
id|len
OG
id|RGN_MAP_LIMIT
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vmm
op_logical_or
(paren
id|addr
op_plus
id|len
)paren
op_le
id|vmm-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
id|ALIGN
c_func
(paren
id|vmm-&gt;vm_end
comma
id|HPAGE_SIZE
)paren
suffix:semicolon
)brace
)brace
DECL|function|update_and_free_page
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
id|j
suffix:semicolon
r_struct
id|page
op_star
id|map
suffix:semicolon
id|map
op_assign
id|page
suffix:semicolon
id|htlbzone_pages
op_decrement
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|map-&gt;flags
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
id|map
comma
l_int|0
)paren
suffix:semicolon
id|map
op_increment
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
DECL|function|try_to_free_low
r_int
id|try_to_free_low
c_func
(paren
r_int
id|count
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|map
suffix:semicolon
id|map
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|hugepage_freelists
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|map
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|update_and_free_page
c_func
(paren
id|map
)paren
suffix:semicolon
id|htlbpagemem
op_decrement
suffix:semicolon
id|map
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|page
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|page
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
id|map
op_assign
id|page
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|update_and_free_page
c_func
(paren
id|map
)paren
suffix:semicolon
id|htlbpagemem
op_decrement
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|set_hugetlb_mem_size
r_int
id|set_hugetlb_mem_size
c_func
(paren
r_int
id|count
)paren
(brace
r_int
id|lcount
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
id|lcount
op_assign
id|count
suffix:semicolon
r_else
id|lcount
op_assign
id|count
op_minus
id|htlbzone_pages
suffix:semicolon
r_if
c_cond
(paren
id|lcount
op_eq
l_int|0
)paren
r_return
(paren
r_int
)paren
id|htlbzone_pages
suffix:semicolon
r_if
c_cond
(paren
id|lcount
OG
l_int|0
)paren
(brace
multiline_comment|/* Increase the mem size. */
r_while
c_loop
(paren
id|lcount
op_decrement
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
id|page
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|enqueue_huge_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|htlbpagemem
op_increment
suffix:semicolon
id|htlbzone_pages
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|htlbzone_pages
suffix:semicolon
)brace
multiline_comment|/* Shrink the memory size. */
id|lcount
op_assign
id|try_to_free_low
c_func
(paren
id|lcount
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lcount
op_increment
)paren
(brace
id|page
op_assign
id|alloc_hugetlb_page
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|update_and_free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|htlbzone_pages
suffix:semicolon
)brace
DECL|function|hugetlb_sysctl_handler
r_int
id|hugetlb_sysctl_handler
c_func
(paren
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
op_star
id|buffer
comma
r_int
op_star
id|length
)paren
(brace
id|proc_dointvec
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
id|htlbpage_max
op_assign
id|set_hugetlb_mem_size
c_func
(paren
id|htlbpage_max
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
l_string|&quot;%d&quot;
comma
op_amp
id|htlbpage_max
)paren
op_le
l_int|0
)paren
id|htlbpage_max
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
DECL|function|hugetlb_setup_sz
r_static
r_int
id|__init
id|hugetlb_setup_sz
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|u64
id|tr_pages
suffix:semicolon
r_int
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|ia64_pal_vm_page_size
c_func
(paren
op_amp
id|tr_pages
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
multiline_comment|/*&n;&t;&t; * shouldn&squot;t happen, but just in case.&n;&t;&t; */
id|tr_pages
op_assign
l_int|0x15557000UL
suffix:semicolon
id|size
op_assign
id|memparse
c_func
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_logical_or
(paren
id|size
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|tr_pages
op_amp
id|size
)paren
op_logical_or
id|size
op_le
id|PAGE_SIZE
op_logical_or
id|size
op_ge
(paren
l_int|1UL
op_lshift
id|PAGE_SHIFT
op_lshift
id|MAX_ORDER
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Invalid huge page size specified&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|hpage_shift
op_assign
id|__ffs
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * boot cpu already executed ia64_mmu_init, and has HPAGE_SHIFT_DEFAULT&n;&t; * override here with new page shift.&n;&t; */
id|ia64_set_rr
c_func
(paren
id|HPAGE_REGION_BASE
comma
id|hpage_shift
op_lshift
l_int|2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;hugepagesz=&quot;
comma
id|hugetlb_setup_sz
)paren
suffix:semicolon
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
id|htlbpage_max
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
id|htlbpage_lock
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
id|htlbpage_lock
)paren
suffix:semicolon
)brace
id|htlbpage_max
op_assign
id|htlbpagemem
op_assign
id|htlbzone_pages
op_assign
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Total HugeTLB memory allocated, %ld&bslash;n&quot;
comma
id|htlbpagemem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hugetlb_init
id|__initcall
c_func
(paren
id|hugetlb_init
)paren
suffix:semicolon
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
id|htlbzone_pages
comma
id|htlbpagemem
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
r_if
c_cond
(paren
id|size
OG
(paren
id|htlbpagemem
op_lshift
id|HPAGE_SHIFT
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
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
id|htlbzone_pages
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
id|area
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
eof
