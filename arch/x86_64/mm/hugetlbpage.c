multiline_comment|/*&n; * x86-64 Huge TLB Page Support for Kernel.&n; *&n; * Copyright (C) 2002, Rohit Seth &lt;rohit.seth@intel.com&gt;&n; * Minor hacks by Andi Kleen for x86-64&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/err.h&gt;
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
DECL|variable|hugetlb_vm_ops
r_struct
id|vm_operations_struct
id|hugetlb_vm_ops
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|htlbpage_freelist
)paren
suffix:semicolon
DECL|variable|htlbpage_lock
r_static
id|spinlock_t
id|htlbpage_lock
op_assign
id|SPIN_LOCK_UNLOCKED
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
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|htlbpage_freelist
)paren
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
id|page
op_assign
id|list_entry
c_func
(paren
id|htlbpage_freelist.next
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
DECL|function|huge_pte_alloc
r_static
id|pte_t
op_star
id|huge_pte_alloc
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
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
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
id|addr
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
id|addr
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|pmd
suffix:semicolon
)brace
DECL|function|huge_pte_offset
r_static
id|pte_t
op_star
id|huge_pte_offset
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
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
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
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_return
(paren
id|pte_t
op_star
)paren
id|pmd
suffix:semicolon
)brace
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry) {pte_val(entry) |= (_PAGE_PRESENT | _PAGE_PSE);}
DECL|function|set_huge_pte
r_static
r_void
id|set_huge_pte
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
)brace
r_int
DECL|function|copy_hugetlb_page_range
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
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|htlbpage_freelist
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
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
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
id|j
comma
id|lcount
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|map
suffix:semicolon
r_extern
r_int
id|htlbzone_pages
suffix:semicolon
r_extern
r_struct
id|list_head
id|htlbpage_freelist
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
id|alloc_pages
c_func
(paren
id|__GFP_HIGHMEM
comma
id|HUGETLB_PAGE_ORDER
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
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|htlbpage_freelist
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
id|htlbzone_pages
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|map
op_assign
id|page
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
r_return
(paren
r_int
)paren
id|htlbzone_pages
suffix:semicolon
)brace
multiline_comment|/* This will likely not work because of fragmentation. */
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
comma
id|j
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
id|htlbpage_max
suffix:semicolon
op_increment
id|i
)paren
(brace
id|page
op_assign
id|alloc_pages
c_func
(paren
id|__GFP_HIGHMEM
comma
id|HUGETLB_PAGE_ORDER
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
suffix:semicolon
op_increment
id|j
)paren
id|SetPageReserved
c_func
(paren
op_amp
id|page
(braket
id|j
)braket
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|htlbpage_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|htlbpage_freelist
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
id|module_init
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
eof
