multiline_comment|/*&n; *&t;linux/mm/remap.c&n; *&n; *&t;(C) Copyright 1996 Linus Torvalds&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
r_extern
r_int
id|vm_enough_memory
c_func
(paren
r_int
id|pages
)paren
suffix:semicolon
DECL|function|get_one_pte_map2
r_static
r_inline
id|pte_t
op_star
id|get_one_pte_map2
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
id|pte_offset_map2
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
id|pte_unmap2
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
DECL|function|copy_one_pte
r_static
r_inline
r_int
id|copy_one_pte
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pte_t
op_star
id|src
comma
id|pte_t
op_star
id|dst
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|src
)paren
)paren
(brace
id|pte
op_assign
id|ptep_get_and_clear
c_func
(paren
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
(brace
multiline_comment|/* No dest?  We must put it back. */
id|dst
op_assign
id|src
suffix:semicolon
id|error
op_increment
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|dst
comma
id|pte
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|move_one_page
r_static
r_int
id|move_one_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
id|get_one_pte_map2
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
id|error
op_assign
id|copy_one_pte
c_func
(paren
id|mm
comma
id|src
comma
id|dst
)paren
suffix:semicolon
id|pte_unmap2
c_func
(paren
id|src
)paren
suffix:semicolon
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
id|offset
op_assign
id|len
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
r_while
c_loop
(paren
id|offset
)paren
(brace
id|offset
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|move_one_page
c_func
(paren
id|mm
comma
id|old_addr
op_plus
id|offset
comma
id|new_addr
op_plus
id|offset
)paren
)paren
r_goto
id|oops_we_failed
suffix:semicolon
)brace
id|flush_tlb_range
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, the move failed because we didn&squot;t have enough pages for&n;&t; * the new page table tree. This is unlikely, but we have to&n;&t; * take the possibility into account. In that case we just move&n;&t; * all the pages back (this will work, because we still have&n;&t; * the old page tables)&n;&t; */
id|oops_we_failed
suffix:colon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|new_addr
comma
id|new_addr
op_plus
id|len
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|offset
op_add_assign
id|PAGE_SIZE
)paren
OL
id|len
)paren
id|move_one_page
c_func
(paren
id|mm
comma
id|new_addr
op_plus
id|offset
comma
id|old_addr
op_plus
id|offset
)paren
suffix:semicolon
id|zap_page_range
c_func
(paren
id|vma
comma
id|new_addr
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|move_vma
r_static
r_inline
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
comma
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
r_int
id|allocated_vma
suffix:semicolon
id|new_vma
op_assign
l_int|NULL
suffix:semicolon
id|next
op_assign
id|find_vma_prev
c_func
(paren
id|mm
comma
id|new_addr
comma
op_amp
id|prev
)paren
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
id|prev
op_logical_and
id|prev-&gt;vm_end
op_eq
id|new_addr
op_logical_and
id|can_vma_merge
c_func
(paren
id|prev
comma
id|vma-&gt;vm_flags
)paren
op_logical_and
op_logical_neg
id|vma-&gt;vm_file
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|prev-&gt;vm_end
op_assign
id|new_addr
op_plus
id|new_len
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|new_vma
op_assign
id|prev
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
id|prev-&gt;vm_next
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;vm_end
op_eq
id|next-&gt;vm_start
op_logical_and
id|can_vma_merge
c_func
(paren
id|next
comma
id|prev-&gt;vm_flags
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|prev-&gt;vm_end
op_assign
id|next-&gt;vm_end
suffix:semicolon
id|__vma_unlink
c_func
(paren
id|mm
comma
id|next
comma
id|prev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|mm-&gt;map_count
op_decrement
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|vm_area_cachep
comma
id|next
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|next-&gt;vm_start
op_eq
id|new_addr
op_plus
id|new_len
op_logical_and
id|can_vma_merge
c_func
(paren
id|next
comma
id|vma-&gt;vm_flags
)paren
op_logical_and
op_logical_neg
id|vma-&gt;vm_file
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|next-&gt;vm_start
op_assign
id|new_addr
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|new_vma
op_assign
id|next
suffix:semicolon
)brace
)brace
r_else
(brace
id|prev
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|new_addr
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_logical_and
id|prev-&gt;vm_end
op_eq
id|new_addr
op_logical_and
id|can_vma_merge
c_func
(paren
id|prev
comma
id|vma-&gt;vm_flags
)paren
op_logical_and
op_logical_neg
id|vma-&gt;vm_file
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|prev-&gt;vm_end
op_assign
id|new_addr
op_plus
id|new_len
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|new_vma
op_assign
id|prev
suffix:semicolon
)brace
)brace
id|allocated_vma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_vma
)paren
(brace
id|new_vma
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vm_area_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_vma
)paren
r_goto
id|out
suffix:semicolon
id|allocated_vma
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|move_page_tables
c_func
(paren
id|vma
comma
id|new_addr
comma
id|addr
comma
id|old_len
)paren
)paren
(brace
r_if
c_cond
(paren
id|allocated_vma
)paren
(brace
op_star
id|new_vma
op_assign
op_star
id|vma
suffix:semicolon
id|new_vma-&gt;vm_start
op_assign
id|new_addr
suffix:semicolon
id|new_vma-&gt;vm_end
op_assign
id|new_addr
op_plus
id|new_len
suffix:semicolon
id|new_vma-&gt;vm_pgoff
op_add_assign
(paren
id|addr
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|new_vma-&gt;vm_raend
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|new_vma-&gt;vm_file
)paren
id|get_file
c_func
(paren
id|new_vma-&gt;vm_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_vma-&gt;vm_ops
op_logical_and
id|new_vma-&gt;vm_ops-&gt;open
)paren
id|new_vma-&gt;vm_ops
op_member_access_from_pointer
id|open
c_func
(paren
id|new_vma
)paren
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|new_vma
)paren
suffix:semicolon
)brace
id|do_munmap
c_func
(paren
id|current-&gt;mm
comma
id|addr
comma
id|old_len
)paren
suffix:semicolon
id|current-&gt;mm-&gt;total_vm
op_add_assign
id|new_len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|new_vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
(brace
id|current-&gt;mm-&gt;locked_vm
op_add_assign
id|new_len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|make_pages_present
c_func
(paren
id|new_vma-&gt;vm_start
comma
id|new_vma-&gt;vm_end
)paren
suffix:semicolon
)brace
r_return
id|new_addr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|allocated_vma
)paren
id|kmem_cache_free
c_func
(paren
id|vm_area_cachep
comma
id|new_vma
)paren
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|ENOMEM
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
)brace
multiline_comment|/*&n;&t; * Always allow a shrinking remap: that just unmaps&n;&t; * the unnecessary pages..&n;&t; */
id|ret
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|old_len
op_ge
id|new_len
)paren
(brace
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
multiline_comment|/* Private writable mapping? Check memory availability.. */
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_SHARED
op_or
id|VM_WRITE
)paren
)paren
op_eq
id|VM_WRITE
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|MAP_NORESERVE
)paren
op_logical_and
op_logical_neg
id|vm_enough_memory
c_func
(paren
(paren
id|new_len
op_minus
id|old_len
)paren
op_rshift
id|PAGE_SHIFT
)paren
)paren
r_goto
id|out
suffix:semicolon
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
id|VM_SHARED
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
