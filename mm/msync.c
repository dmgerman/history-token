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
DECL|function|sync_pte_range
r_static
r_void
id|sync_pte_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
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
r_do
(brace
r_int
r_int
id|pfn
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
id|ptep_clear_flush_dirty
c_func
(paren
id|vma
comma
id|addr
comma
id|pte
)paren
op_logical_or
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
)brace
r_while
c_loop
(paren
id|pte
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|addr
op_ne
id|end
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
DECL|function|sync_pmd_range
r_static
r_inline
r_void
id|sync_pmd_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|addr
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pmd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none_or_clear_bad
c_func
(paren
id|pmd
)paren
)paren
r_continue
suffix:semicolon
id|sync_pte_range
c_func
(paren
id|vma
comma
id|pmd
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pmd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
DECL|function|sync_pud_range
r_static
r_inline
r_void
id|sync_pud_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pud_t
op_star
id|pud
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pud
op_assign
id|pud_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pud_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pud_none_or_clear_bad
c_func
(paren
id|pud
)paren
)paren
r_continue
suffix:semicolon
id|sync_pmd_range
c_func
(paren
id|vma
comma
id|pud
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pud
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
DECL|function|sync_page_range
r_static
r_void
id|sync_page_range
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
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
r_int
id|next
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
r_return
suffix:semicolon
id|BUG_ON
c_func
(paren
id|addr
op_ge
id|end
)paren
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
id|flush_cache_range
c_func
(paren
id|vma
comma
id|addr
comma
id|end
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pgd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none_or_clear_bad
c_func
(paren
id|pgd
)paren
)paren
r_continue
suffix:semicolon
id|sync_pud_range
c_func
(paren
id|vma
comma
id|pgd
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
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
macro_line|#ifdef CONFIG_PREEMPT
DECL|function|filemap_sync
r_static
r_inline
r_void
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
id|addr
comma
r_int
r_int
id|end
)paren
(brace
r_const
r_int
id|chunk
op_assign
l_int|64
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* bytes */
r_int
r_int
id|next
suffix:semicolon
r_do
(brace
id|next
op_assign
id|addr
op_plus
id|chunk
suffix:semicolon
r_if
c_cond
(paren
id|next
OG
id|end
op_logical_or
id|next
OL
id|addr
)paren
id|next
op_assign
id|end
suffix:semicolon
id|sync_page_range
c_func
(paren
id|vma
comma
id|addr
comma
id|next
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|filemap_sync
r_static
r_inline
r_void
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
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|sync_page_range
c_func
(paren
id|vma
comma
id|addr
comma
id|end
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|addr
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
id|filemap_sync
c_func
(paren
id|vma
comma
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MS_SYNC
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
