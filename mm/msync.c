multiline_comment|/*&n; *&t;linux/mm/msync.c&n; *&n; * Copyright (C) 1994-1999  Linus Torvalds&n; */
multiline_comment|/*&n; * The msync() system call.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Called with mm-&gt;page_table_lock held to protect against other&n; * threads/the swapper from ripping pte&squot;s out from under us.&n; */
DECL|function|filemap_sync_pte
r_static
r_int
id|filemap_sync_pte
c_func
(paren
id|pte_t
op_star
id|ptep
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
r_int
id|flags
)paren
(brace
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_int
r_int
id|pfn
op_assign
id|pte_pfn
c_func
(paren
id|pte
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
id|pte_present
c_func
(paren
id|pte
)paren
op_logical_and
id|pfn_valid
c_func
(paren
id|pfn
)paren
)paren
(brace
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
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
(paren
id|ptep_clear_flush_dirty
c_func
(paren
id|vma
comma
id|address
comma
id|ptep
)paren
op_logical_or
id|page_test_and_clear_dirty
c_func
(paren
id|page
)paren
)paren
)paren
id|set_page_dirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|filemap_sync_pte_range
r_static
r_int
id|filemap_sync_pte_range
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
id|end
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|flags
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|error
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
l_int|0
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
l_int|0
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
r_if
c_cond
(paren
(paren
id|address
op_amp
id|PMD_MASK
)paren
op_ne
(paren
id|end
op_amp
id|PMD_MASK
)paren
)paren
id|end
op_assign
(paren
id|address
op_amp
id|PMD_MASK
)paren
op_plus
id|PMD_SIZE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|error
op_or_assign
id|filemap_sync_pte
c_func
(paren
id|pte
comma
id|vma
comma
id|address
comma
id|flags
)paren
suffix:semicolon
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
r_return
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync_pmd_range
r_static
r_inline
r_int
id|filemap_sync_pmd_range
c_func
(paren
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|flags
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|pud_none
c_func
(paren
op_star
id|pud
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pud_bad
c_func
(paren
op_star
id|pud
)paren
)paren
(brace
id|pud_ERROR
c_func
(paren
op_star
id|pud
)paren
suffix:semicolon
id|pud_clear
c_func
(paren
id|pud
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|address
op_amp
id|PUD_MASK
)paren
op_ne
(paren
id|end
op_amp
id|PUD_MASK
)paren
)paren
id|end
op_assign
(paren
id|address
op_amp
id|PUD_MASK
)paren
op_plus
id|PUD_SIZE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|error
op_or_assign
id|filemap_sync_pte_range
c_func
(paren
id|pmd
comma
id|address
comma
id|end
comma
id|vma
comma
id|flags
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
r_return
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync_pud_range
r_static
r_inline
r_int
id|filemap_sync_pud_range
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
id|end
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|flags
)paren
(brace
id|pud_t
op_star
id|pud
suffix:semicolon
r_int
id|error
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
l_int|0
suffix:semicolon
)brace
id|pud
op_assign
id|pud_offset
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
(paren
id|address
op_amp
id|PGDIR_MASK
)paren
op_ne
(paren
id|end
op_amp
id|PGDIR_MASK
)paren
)paren
id|end
op_assign
(paren
id|address
op_amp
id|PGDIR_MASK
)paren
op_plus
id|PGDIR_SIZE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|error
op_or_assign
id|filemap_sync_pmd_range
c_func
(paren
id|pud
comma
id|address
comma
id|end
comma
id|vma
comma
id|flags
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PUD_SIZE
)paren
op_amp
id|PUD_MASK
suffix:semicolon
id|pud
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
id|error
suffix:semicolon
)brace
DECL|function|filemap_sync
r_static
r_int
id|filemap_sync
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
id|size
comma
r_int
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Aquire the lock early; it may be possible to avoid dropping&n;&t; * and reaquiring it repeatedly.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|vma-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|address
comma
id|end
)paren
suffix:semicolon
multiline_comment|/* For hugepages we can&squot;t go walking the page table normally,&n;&t; * but that&squot;s ok, hugetlbfs is memory based, so we don&squot;t need&n;&t; * to do anything more on an msync() */
r_if
c_cond
(paren
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
r_goto
id|out
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
r_for
c_loop
(paren
id|i
op_assign
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
id|i
op_le
id|pgd_index
c_func
(paren
id|end
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|next
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
id|next
op_le
id|address
op_logical_or
id|next
OG
id|end
)paren
id|next
op_assign
id|end
suffix:semicolon
id|error
op_or_assign
id|filemap_sync_pud_range
c_func
(paren
id|pgd
comma
id|address
comma
id|next
comma
id|vma
comma
id|flags
)paren
suffix:semicolon
id|address
op_assign
id|next
suffix:semicolon
id|pgd
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Why flush ? filemap_sync_pte already flushed the tlbs with the&n;&t; * dirty bits.&n;&t; */
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|end
op_minus
id|size
comma
id|end
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|vma-&gt;vm_mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * MS_SYNC syncs the entire file - including mappings.&n; *&n; * MS_ASYNC does not start I/O (it used to, up to 2.5.67).  Instead, it just&n; * marks the relevant pages dirty.  The application may now run fsync() to&n; * write out the dirty pages and wait on the writeout and check the result.&n; * Or the application may run fadvise(FADV_DONTNEED) against the fd to start&n; * async writeout immediately.&n; * So my _not_ starting I/O in MS_ASYNC we provide complete flexibility to&n; * applications.&n; */
DECL|function|msync_interval
r_static
r_int
id|msync_interval
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
r_int
id|flags
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|vma-&gt;vm_file
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|MS_INVALIDATE
)paren
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|file
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
)paren
(brace
id|ret
op_assign
id|filemap_sync
c_func
(paren
id|vma
comma
id|start
comma
id|end
op_minus
id|start
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
(paren
id|flags
op_amp
id|MS_SYNC
)paren
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|file-&gt;f_mapping
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ret
op_assign
id|filemap_fdatawrite
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;fsync
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * We don&squot;t take i_sem here because mmap_sem&n;&t;&t;&t;&t; * is already held.&n;&t;&t;&t;&t; */
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|fsync
c_func
(paren
id|file
comma
id|file-&gt;f_dentry
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_and
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|err
suffix:semicolon
)brace
id|err
op_assign
id|filemap_fdatawait
c_func
(paren
id|mapping
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|err
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_msync
id|asmlinkage
r_int
id|sys_msync
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
id|flags
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|unmapped_error
comma
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MS_SYNC
)paren
id|current-&gt;flags
op_or_assign
id|PF_SYNCWRITE
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
op_complement
(paren
id|MS_ASYNC
op_or
id|MS_INVALIDATE
op_or
id|MS_SYNC
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|start
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
(paren
id|flags
op_amp
id|MS_ASYNC
)paren
op_logical_and
(paren
id|flags
op_amp
id|MS_SYNC
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|len
op_assign
(paren
id|len
op_plus
op_complement
id|PAGE_MASK
)paren
op_amp
id|PAGE_MASK
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
r_goto
id|out
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * If the interval [start,end) covers some unmapped address ranges,&n;&t; * just ignore them, but return -ENOMEM at the end.&n;&t; */
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|start
)paren
suffix:semicolon
id|unmapped_error
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* Still start &lt; end. */
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
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Here start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|start
OL
id|vma-&gt;vm_start
)paren
(brace
id|unmapped_error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end. */
r_if
c_cond
(paren
id|end
op_le
id|vma-&gt;vm_end
)paren
(brace
r_if
c_cond
(paren
id|start
OL
id|end
)paren
(brace
id|error
op_assign
id|msync_interval
c_func
(paren
id|vma
comma
id|start
comma
id|end
comma
id|flags
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
)brace
id|error
op_assign
id|unmapped_error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Here vma-&gt;vm_start &lt;= start &lt; vma-&gt;vm_end &lt; end. */
id|error
op_assign
id|msync_interval
c_func
(paren
id|vma
comma
id|start
comma
id|vma-&gt;vm_end
comma
id|flags
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
id|start
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_SYNCWRITE
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
