multiline_comment|/*&n; *&t;mm/mremap.c&n; *&n; *&t;(C) Copyright 1996 Linus Torvalds&n; *&n; *&t;Address space accounting code&t;&lt;alan@redhat.com&gt;&n; *&t;(C) Copyright 2002 Red Hat Inc, All Rights Reserved&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/rmap.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|function|get_one_pte_map_nested
r_static
id|pte_t
op_star
id|get_one_pte_map_nested
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
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pgd_ERROR
c_func
(paren
op_star
id|pgd
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
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
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_map_nested
c_func
(paren
id|pmd
comma
id|addr
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
(brace
id|pte_unmap_nested
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pte
op_assign
l_int|NULL
suffix:semicolon
)brace
id|end
suffix:colon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|page_table_present
r_static
r_inline
r_int
id|page_table_present
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
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
l_int|0
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
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|alloc_one_pte_map
r_static
r_inline
id|pte_t
op_star
id|alloc_one_pte_map
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
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|mm
comma
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
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
r_return
id|pte
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|can_move_one_pte
id|can_move_one_pte
c_func
(paren
id|pte_t
op_star
id|src
comma
r_int
r_int
id|new_addr
)paren
(brace
r_int
id|move
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|src
)paren
)paren
(brace
r_int
r_int
id|pfn
op_assign
id|pte_pfn
c_func
(paren
op_star
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfn_valid
c_func
(paren
id|pfn
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
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
id|move
op_assign
id|mremap_move_anon_rmap
c_func
(paren
id|page
comma
id|new_addr
)paren
suffix:semicolon
)brace
)brace
r_return
id|move
suffix:semicolon
)brace
r_static
r_int
DECL|function|move_one_page
id|move_one_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|old_addr
comma
r_int
r_int
id|new_addr
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
id|error
op_assign
l_int|0
suffix:semicolon
id|pte_t
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|src
op_assign
id|get_one_pte_map_nested
c_func
(paren
id|mm
comma
id|old_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look to see whether alloc_one_pte_map needs to perform a&n;&t;&t; * memory allocation.  If it does then we need to drop the&n;&t;&t; * atomic kmap&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|page_table_present
c_func
(paren
id|mm
comma
id|new_addr
)paren
)paren
(brace
id|pte_unmap_nested
c_func
(paren
id|src
)paren
suffix:semicolon
id|src
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dst
op_assign
id|alloc_one_pte_map
c_func
(paren
id|mm
comma
id|new_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src
op_eq
l_int|NULL
)paren
id|src
op_assign
id|get_one_pte_map_nested
c_func
(paren
id|mm
comma
id|old_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Since alloc_one_pte_map can drop and re-acquire&n;&t;&t; * page_table_lock, we should re-check the src entry...&n;&t;&t; */
r_if
c_cond
(paren
id|src
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|can_move_one_pte
c_func
(paren
id|src
comma
id|new_addr
)paren
)paren
id|error
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_else
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte
op_assign
id|ptep_clear_flush
c_func
(paren
id|vma
comma
id|old_addr
comma
id|src
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|dst
comma
id|pte
)paren
suffix:semicolon
)brace
id|pte_unmap_nested
c_func
(paren
id|src
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
)paren
id|pte_unmap
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|move_page_tables
r_static
r_int
r_int
id|move_page_tables
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|new_addr
comma
r_int
r_int
id|old_addr
comma
r_int
r_int
id|len
comma
r_int
op_star
id|cows
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|old_addr
comma
id|old_addr
op_plus
id|len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is not the clever way to do this, but we&squot;re taking the&n;&t; * easy way out on the assumption that most remappings will be&n;&t; * only a few pages.. This also makes error recovery easier.&n;&t; */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|len
suffix:semicolon
id|offset
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_int
id|ret
op_assign
id|move_one_page
c_func
(paren
id|vma
comma
id|old_addr
op_plus
id|offset
comma
id|new_addr
op_plus
id|offset
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The anonmm objrmap can only track anon page movements&n;&t;&t; * if the page is exclusive to one mm.  In the rare case&n;&t;&t; * when mremap move is applied to a shared page, break&n;&t;&t; * COW (take a copy of the page) to make it exclusive.&n;&t;&t; * If shared while on swap, page will be copied when&n;&t;&t; * brought back in (if it&squot;s still shared by then).&n;&t;&t; */
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|EAGAIN
)paren
(brace
id|ret
op_assign
id|make_page_exclusive
c_func
(paren
id|vma
comma
id|old_addr
op_plus
id|offset
)paren
suffix:semicolon
id|offset
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
(paren
op_star
id|cows
)paren
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|move_vma
r_static
r_int
r_int
id|move_vma
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|old_addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|new_addr
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
id|vm_area_struct
op_star
id|new_vma
suffix:semicolon
r_int
r_int
id|vm_flags
op_assign
id|vma-&gt;vm_flags
suffix:semicolon
r_int
r_int
id|new_pgoff
suffix:semicolon
r_int
r_int
id|moved_len
suffix:semicolon
r_int
r_int
id|excess
op_assign
l_int|0
suffix:semicolon
r_int
id|split
op_assign
l_int|0
suffix:semicolon
r_int
id|cows
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We&squot;d prefer to avoid failure later on in do_munmap:&n;&t; * which may split one vma into three before unmapping.&n;&t; */
r_if
c_cond
(paren
id|mm-&gt;map_count
op_ge
id|sysctl_max_map_count
op_minus
l_int|3
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|new_pgoff
op_assign
id|vma-&gt;vm_pgoff
op_plus
(paren
(paren
id|old_addr
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|new_vma
op_assign
id|copy_vma
c_func
(paren
op_amp
id|vma
comma
id|new_addr
comma
id|new_len
comma
id|new_pgoff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_vma
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|moved_len
op_assign
id|move_page_tables
c_func
(paren
id|vma
comma
id|new_addr
comma
id|old_addr
comma
id|old_len
comma
op_amp
id|cows
)paren
suffix:semicolon
r_if
c_cond
(paren
id|moved_len
OL
id|old_len
)paren
(brace
multiline_comment|/*&n;&t;&t; * On error, move entries back from new area to old,&n;&t;&t; * which will succeed since page tables still there,&n;&t;&t; * and then proceed to unmap new area instead of old.&n;&t;&t; */
id|move_page_tables
c_func
(paren
id|new_vma
comma
id|old_addr
comma
id|new_addr
comma
id|moved_len
comma
op_amp
id|cows
)paren
suffix:semicolon
id|vma
op_assign
id|new_vma
suffix:semicolon
id|old_len
op_assign
id|new_len
suffix:semicolon
id|old_addr
op_assign
id|new_addr
suffix:semicolon
id|new_addr
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cows
)paren
multiline_comment|/* Downgrade or remove this message later */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: mremap moved %d cows&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|cows
)paren
suffix:semicolon
multiline_comment|/* Conceal VM_ACCOUNT so old reservation is not undone */
r_if
c_cond
(paren
id|vm_flags
op_amp
id|VM_ACCOUNT
)paren
(brace
id|vma-&gt;vm_flags
op_and_assign
op_complement
id|VM_ACCOUNT
suffix:semicolon
id|excess
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
op_minus
id|old_len
suffix:semicolon
r_if
c_cond
(paren
id|old_addr
OG
id|vma-&gt;vm_start
op_logical_and
id|old_addr
op_plus
id|old_len
OL
id|vma-&gt;vm_end
)paren
id|split
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_munmap
c_func
(paren
id|mm
comma
id|old_addr
comma
id|old_len
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* OOM: unable to split vma, just get accounts right */
id|vm_unacct_memory
c_func
(paren
id|excess
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|excess
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Restore VM_ACCOUNT if one or two pieces of vma left */
r_if
c_cond
(paren
id|excess
)paren
(brace
id|vma-&gt;vm_flags
op_or_assign
id|VM_ACCOUNT
suffix:semicolon
r_if
c_cond
(paren
id|split
)paren
id|vma-&gt;vm_next-&gt;vm_flags
op_or_assign
id|VM_ACCOUNT
suffix:semicolon
)brace
id|mm-&gt;total_vm
op_add_assign
id|new_len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|vm_flags
op_amp
id|VM_LOCKED
)paren
(brace
id|mm-&gt;locked_vm
op_add_assign
id|new_len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|new_len
OG
id|old_len
)paren
id|make_pages_present
c_func
(paren
id|new_addr
op_plus
id|old_len
comma
id|new_addr
op_plus
id|new_len
)paren
suffix:semicolon
)brace
r_return
id|new_addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Expand (or shrink) an existing mapping, potentially moving it at the&n; * same time (controlled by the MREMAP_MAYMOVE flag and available VM space)&n; *&n; * MREMAP_FIXED option added 5-Dec-1999 by Benjamin LaHaise&n; * This option implies MREMAP_MAYMOVE.&n; */
DECL|function|do_mremap
r_int
r_int
id|do_mremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
r_int
id|charged
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
(paren
id|MREMAP_FIXED
op_or
id|MREMAP_MAYMOVE
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
id|old_len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|old_len
)paren
suffix:semicolon
id|new_len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|new_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We allow a zero old-len as a special case&n;&t; * for DOS-emu &quot;duplicate shm area&quot; thing. But&n;&t; * a zero new-len is nonsensical.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|new_len
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* new_addr is only valid if MREMAP_FIXED is specified */
r_if
c_cond
(paren
id|flags
op_amp
id|MREMAP_FIXED
)paren
(brace
r_if
c_cond
(paren
id|new_addr
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MREMAP_MAYMOVE
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|new_len
OG
id|TASK_SIZE
op_logical_or
id|new_addr
OG
id|TASK_SIZE
op_minus
id|new_len
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Check if the location we&squot;re moving into overlaps the&n;&t;&t; * old location at all, and fail if it does.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|new_addr
op_le
id|addr
)paren
op_logical_and
(paren
id|new_addr
op_plus
id|new_len
)paren
OG
id|addr
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_le
id|new_addr
)paren
op_logical_and
(paren
id|addr
op_plus
id|old_len
)paren
OG
id|new_addr
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|do_munmap
c_func
(paren
id|current-&gt;mm
comma
id|new_addr
comma
id|new_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Always allow a shrinking remap: that just unmaps&n;&t; * the unnecessary pages..&n;&t; * do_munmap does all the needed commit accounting&n;&t; */
r_if
c_cond
(paren
id|old_len
op_ge
id|new_len
)paren
(brace
id|ret
op_assign
id|do_munmap
c_func
(paren
id|current-&gt;mm
comma
id|addr
op_plus
id|new_len
comma
id|old_len
op_minus
id|new_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
id|old_len
op_ne
id|new_len
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MREMAP_FIXED
)paren
op_logical_or
(paren
id|new_addr
op_eq
id|addr
)paren
)paren
r_goto
id|out
suffix:semicolon
id|old_len
op_assign
id|new_len
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ok, we need to grow..  or relocate.&n;&t; */
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
OG
id|addr
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* We can&squot;t remap across vm area boundaries */
r_if
c_cond
(paren
id|old_len
OG
id|vma-&gt;vm_end
op_minus
id|addr
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_DONTEXPAND
)paren
(brace
r_if
c_cond
(paren
id|new_len
OG
id|old_len
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
(brace
r_int
r_int
id|locked
op_assign
id|current-&gt;mm-&gt;locked_vm
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|locked
op_add_assign
id|new_len
op_minus
id|old_len
suffix:semicolon
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|locked
OG
id|current-&gt;rlim
(braket
id|RLIMIT_MEMLOCK
)braket
dot
id|rlim_cur
)paren
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;mm-&gt;total_vm
op_lshift
id|PAGE_SHIFT
)paren
op_plus
(paren
id|new_len
op_minus
id|old_len
)paren
OG
id|current-&gt;rlim
(braket
id|RLIMIT_AS
)braket
dot
id|rlim_cur
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_ACCOUNT
)paren
(brace
id|charged
op_assign
(paren
id|new_len
op_minus
id|old_len
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|security_vm_enough_memory
c_func
(paren
id|charged
)paren
)paren
r_goto
id|out_nc
suffix:semicolon
)brace
multiline_comment|/* old_len exactly to the end of the area..&n;&t; * And we&squot;re not relocating the area.&n;&t; */
r_if
c_cond
(paren
id|old_len
op_eq
id|vma-&gt;vm_end
op_minus
id|addr
op_logical_and
op_logical_neg
(paren
(paren
id|flags
op_amp
id|MREMAP_FIXED
)paren
op_logical_and
(paren
id|addr
op_ne
id|new_addr
)paren
)paren
op_logical_and
(paren
id|old_len
op_ne
id|new_len
op_logical_or
op_logical_neg
(paren
id|flags
op_amp
id|MREMAP_MAYMOVE
)paren
)paren
)paren
(brace
r_int
r_int
id|max_addr
op_assign
id|TASK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_next
)paren
id|max_addr
op_assign
id|vma-&gt;vm_next-&gt;vm_start
suffix:semicolon
multiline_comment|/* can we just expand the current mapping? */
r_if
c_cond
(paren
id|max_addr
op_minus
id|addr
op_ge
id|new_len
)paren
(brace
r_int
id|pages
op_assign
(paren
id|new_len
op_minus
id|old_len
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|vma-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|addr
op_plus
id|new_len
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vma-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
id|current-&gt;mm-&gt;total_vm
op_add_assign
id|pages
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
(brace
id|current-&gt;mm-&gt;locked_vm
op_add_assign
id|pages
suffix:semicolon
id|make_pages_present
c_func
(paren
id|addr
op_plus
id|old_len
comma
id|addr
op_plus
id|new_len
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|addr
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * We weren&squot;t able to just expand or shrink the area,&n;&t; * we need to create a new one and move it..&n;&t; */
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MREMAP_MAYMOVE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MREMAP_FIXED
)paren
)paren
(brace
r_int
r_int
id|map_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_MAYSHARE
)paren
id|map_flags
op_or_assign
id|MAP_SHARED
suffix:semicolon
id|new_addr
op_assign
id|get_unmapped_area
c_func
(paren
id|vma-&gt;vm_file
comma
l_int|0
comma
id|new_len
comma
id|vma-&gt;vm_pgoff
comma
id|map_flags
)paren
suffix:semicolon
id|ret
op_assign
id|new_addr
suffix:semicolon
r_if
c_cond
(paren
id|new_addr
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|move_vma
c_func
(paren
id|vma
comma
id|addr
comma
id|old_len
comma
id|new_len
comma
id|new_addr
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
op_amp
op_complement
id|PAGE_MASK
)paren
id|vm_unacct_memory
c_func
(paren
id|charged
)paren
suffix:semicolon
id|out_nc
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_mremap
id|asmlinkage
r_int
r_int
id|sys_mremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|do_mremap
c_func
(paren
id|addr
comma
id|old_len
comma
id|new_len
comma
id|flags
comma
id|new_addr
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
