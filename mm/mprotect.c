multiline_comment|/*&n; *  mm/mprotect.c&n; *&n; *  (C) Copyright 1994 Linus Torvalds&n; *  (C) Copyright 2002 Christoph Hellwig&n; *&n; *  Address space accounting code&t;&lt;alan@redhat.com&gt;&n; *  (C) Copyright 2002 Red Hat Inc, All Rights Reserved&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
r_static
r_inline
r_void
DECL|function|change_pte_range
id|change_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|end
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
r_return
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
r_return
suffix:semicolon
)brace
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
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
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
id|pte_t
id|entry
suffix:semicolon
multiline_comment|/* Avoid an SMP race with hardware updated dirty/clean&n;&t;&t;&t; * bits by wiping the pte and then setting the new pte&n;&t;&t;&t; * into place.&n;&t;&t;&t; */
id|entry
op_assign
id|ptep_get_and_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|pte_modify
c_func
(paren
id|entry
comma
id|newprot
)paren
)paren
suffix:semicolon
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
)brace
r_static
r_inline
r_void
DECL|function|change_pmd_range
id|change_pmd_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|end
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
r_return
suffix:semicolon
)brace
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
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
id|change_pte_range
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|newprot
)paren
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
)brace
r_static
r_void
DECL|function|change_protection
id|change_protection
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
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|beg
op_assign
id|start
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|start
)paren
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|beg
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
r_do
(brace
id|change_pmd_range
c_func
(paren
id|dir
comma
id|start
comma
id|end
op_minus
id|start
comma
id|newprot
)paren
suffix:semicolon
id|start
op_assign
(paren
id|start
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
op_logical_and
(paren
id|start
OL
id|end
)paren
)paren
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|beg
comma
id|end
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to merge a vma with the previous flag, return 1 if successful or 0 if it&n; * was impossible.&n; */
r_static
r_int
DECL|function|mprotect_attempt_merge
id|mprotect_attempt_merge
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
id|prev
comma
r_int
r_int
id|end
comma
r_int
id|newflags
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prev
op_logical_or
op_logical_neg
id|vma
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;vm_end
op_ne
id|vma-&gt;vm_start
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|can_vma_merge
c_func
(paren
id|prev
comma
id|newflags
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_file
op_logical_or
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the whole area changes to the protection of the previous one&n;&t; * we can just get rid of it.&n;&t; */
r_if
c_cond
(paren
id|end
op_eq
id|vma-&gt;vm_end
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
id|end
suffix:semicolon
id|__vma_unlink
c_func
(paren
id|mm
comma
id|vma
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
id|kmem_cache_free
c_func
(paren
id|vm_area_cachep
comma
id|vma
)paren
suffix:semicolon
id|mm-&gt;map_count
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Otherwise extend it.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|prev-&gt;vm_end
op_assign
id|end
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|end
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|mprotect_fixup
id|mprotect_fixup
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
op_star
id|pprev
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
r_int
id|newflags
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
id|charged
op_assign
l_int|0
suffix:semicolon
id|pgprot_t
id|newprot
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|newflags
op_eq
id|vma-&gt;vm_flags
)paren
(brace
op_star
id|pprev
op_assign
id|vma
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we make a private mapping writable we increase our commit;&n;&t; * but (without finer accounting) cannot reduce our commit if we&n;&t; * make it unwritable again.&n;&t; *&n;&t; * FIXME? We haven&squot;t defined a VM_NORESERVE flag, so mprotecting&n;&t; * a MAP_NORESERVE private mapping to writable will now reserve.&n;&t; */
r_if
c_cond
(paren
id|newflags
op_amp
id|VM_WRITE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_ACCOUNT
op_or
id|VM_WRITE
op_or
id|VM_SHARED
)paren
)paren
)paren
(brace
id|charged
op_assign
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vm_enough_memory
c_func
(paren
id|charged
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|newflags
op_or_assign
id|VM_ACCOUNT
suffix:semicolon
)brace
)brace
id|newprot
op_assign
id|protection_map
(braket
id|newflags
op_amp
l_int|0xf
)braket
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
id|vma-&gt;vm_start
)paren
(brace
multiline_comment|/*&n;&t;&t; * Try to merge with the previous vma.&n;&t;&t; */
r_if
c_cond
(paren
id|mprotect_attempt_merge
c_func
(paren
id|vma
comma
op_star
id|pprev
comma
id|end
comma
id|newflags
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|start
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
op_ne
id|vma-&gt;vm_end
)paren
(brace
id|error
op_assign
id|split_vma
c_func
(paren
id|mm
comma
id|vma
comma
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|newflags
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|newprot
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|change_protection
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
id|newprot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|vm_unacct_memory
c_func
(paren
id|charged
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_mprotect
id|sys_mprotect
c_func
(paren
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
r_int
id|prot
)paren
(brace
r_int
r_int
id|nstart
comma
id|end
comma
id|tmp
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
comma
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
op_complement
(paren
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
op_or
id|PROT_SEM
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
r_return
l_int|0
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma_prev
c_func
(paren
id|current-&gt;mm
comma
id|start
comma
op_amp
id|prev
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
OG
id|start
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|nstart
op_assign
id|start
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|newflags
suffix:semicolon
r_int
id|last
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Here we know that  vma-&gt;vm_start &lt;= nstart &lt; vma-&gt;vm_end. */
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
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|newflags
op_assign
id|prot
op_or
(paren
id|vma-&gt;vm_flags
op_amp
op_complement
(paren
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|newflags
op_amp
op_complement
(paren
id|newflags
op_rshift
l_int|4
)paren
)paren
op_amp
l_int|0xf
)paren
(brace
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
id|security_ops
op_member_access_from_pointer
id|file_mprotect
c_func
(paren
id|vma
comma
id|prot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
OG
id|end
)paren
(brace
id|error
op_assign
id|mprotect_fixup
c_func
(paren
id|vma
comma
op_amp
id|prev
comma
id|nstart
comma
id|end
comma
id|newflags
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_eq
id|end
)paren
id|last
op_assign
l_int|1
suffix:semicolon
id|tmp
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|next
op_assign
id|vma-&gt;vm_next
suffix:semicolon
id|error
op_assign
id|mprotect_fixup
c_func
(paren
id|vma
comma
op_amp
id|prev
comma
id|nstart
comma
id|tmp
comma
id|newflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|last
)paren
r_break
suffix:semicolon
id|nstart
op_assign
id|tmp
suffix:semicolon
id|vma
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|vma-&gt;vm_start
op_ne
id|nstart
)paren
(brace
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|next
op_logical_and
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
op_logical_and
op_logical_neg
id|prev-&gt;vm_file
op_logical_and
op_logical_neg
(paren
id|prev-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|prev-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
id|prev-&gt;vm_end
op_assign
id|next-&gt;vm_end
suffix:semicolon
id|__vma_unlink
c_func
(paren
id|prev-&gt;vm_mm
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
id|prev-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|vm_area_cachep
comma
id|next
)paren
suffix:semicolon
id|prev-&gt;vm_mm-&gt;map_count
op_decrement
suffix:semicolon
)brace
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
