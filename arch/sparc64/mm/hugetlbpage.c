multiline_comment|/*&n; * SPARC64 Huge TLB page support.&n; *&n; * Copyright (C) 2002, 2003 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
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
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
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
id|addr
)paren
suffix:semicolon
)brace
r_return
id|pte
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
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
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
r_if
c_cond
(paren
id|pmd
)paren
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry) do { pte_val(entry) |= _PAGE_SZHUGE; } while (0)
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
r_int
r_int
id|i
suffix:semicolon
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
l_int|1
op_lshift
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_pte
c_func
(paren
id|page_table
comma
id|entry
)paren
suffix:semicolon
id|page_table
op_increment
suffix:semicolon
id|pte_val
c_func
(paren
id|entry
)paren
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
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
r_int
id|i
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|src_pte
op_logical_or
id|pte_none
c_func
(paren
op_star
id|src_pte
)paren
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
l_int|1
op_lshift
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_pte
c_func
(paren
id|dst_pte
comma
id|entry
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|entry
)paren
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|dst_pte
op_increment
suffix:semicolon
)brace
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
DECL|function|follow_hugetlb_page
r_int
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
id|position
comma
r_int
op_star
id|length
comma
r_int
id|i
)paren
(brace
r_int
r_int
id|vaddr
op_assign
op_star
id|position
suffix:semicolon
r_int
id|remainder
op_assign
op_star
id|length
suffix:semicolon
id|WARN_ON
c_func
(paren
op_logical_neg
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|vaddr
OL
id|vma-&gt;vm_end
op_logical_and
id|remainder
)paren
(brace
r_if
c_cond
(paren
id|pages
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|pte
op_assign
id|huge_pte_offset
c_func
(paren
id|mm
comma
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* hugetlb should be locked, and hence, prefaulted */
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte
op_logical_or
id|pte_none
c_func
(paren
op_star
id|pte
)paren
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
id|WARN_ON
c_func
(paren
op_logical_neg
id|PageCompound
c_func
(paren
id|page
)paren
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
id|vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
op_decrement
id|remainder
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
op_star
id|length
op_assign
id|remainder
suffix:semicolon
op_star
id|position
op_assign
id|vaddr
suffix:semicolon
r_return
id|i
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
id|address
comma
r_int
id|write
)paren
(brace
r_return
l_int|NULL
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
r_return
l_int|NULL
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
DECL|function|follow_huge_pmd
r_struct
id|page
op_star
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
r_int
id|i
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
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte
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
l_int|1
op_lshift
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
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
id|alloc_huge_page
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
eof
