multiline_comment|/*&n; *   linux/mm/fremap.c&n; * &n; * Explicit pagetable population and nonlinear (random) mappings support.&n; *&n; * started by Ingo Molnar, Copyright (C) 2002, 2003&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/rmap.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|function|zap_pte
r_static
r_inline
r_void
id|zap_pte
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
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|pte
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|pte
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
id|pte
)paren
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|vma
comma
id|addr
)paren
suffix:semicolon
id|pte
op_assign
id|ptep_clear_flush
c_func
(paren
id|vma
comma
id|addr
comma
id|ptep
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
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|pte
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
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_file
c_func
(paren
id|pte
)paren
)paren
id|free_swap_and_cache
c_func
(paren
id|pte_to_swp_entry
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Install a file page to a given virtual memory address, release any&n; * previously existing mapping.&n; */
DECL|function|install_page
r_int
id|install_page
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
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|prot
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|pte_t
op_star
id|pte
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
id|pte_val
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
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
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
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_goto
id|err_unlock
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_goto
id|err_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * This page may have been truncated. Tell the&n;&t; * caller about it.&n;&t; */
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_mapping
c_func
(paren
id|page
)paren
)paren
r_goto
id|err_unlock
suffix:semicolon
id|zap_pte
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
comma
id|pte
)paren
suffix:semicolon
id|mm-&gt;rss
op_increment
suffix:semicolon
id|flush_icache_page
c_func
(paren
id|vma
comma
id|page
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte
c_func
(paren
id|page
comma
id|prot
)paren
)paren
suffix:semicolon
id|page_add_file_rmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|pte_val
op_assign
op_star
id|pte
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
id|vma
comma
id|addr
comma
id|pte_val
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|err_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|install_page
id|EXPORT_SYMBOL
c_func
(paren
id|install_page
)paren
suffix:semicolon
multiline_comment|/*&n; * Install a file pte to a given virtual memory address, release any&n; * previously existing mapping.&n; */
DECL|function|install_file_pte
r_int
id|install_file_pte
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
r_int
id|pgoff
comma
id|pgprot_t
id|prot
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|pte_t
op_star
id|pte
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
id|pte_val
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
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
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
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_goto
id|err_unlock
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_goto
id|err_unlock
suffix:semicolon
id|zap_pte
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
comma
id|pte
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|pgoff_to_pte
c_func
(paren
id|pgoff
)paren
)paren
suffix:semicolon
id|pte_val
op_assign
op_star
id|pte
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
id|vma
comma
id|addr
comma
id|pte_val
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_unlock
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/***&n; * sys_remap_file_pages - remap arbitrary pages of a shared backing store&n; *                        file within an existing vma.&n; * @start: start of the remapped virtual memory range&n; * @size: size of the remapped virtual memory range&n; * @prot: new protection bits of the range&n; * @pgoff: to be mapped page of the backing store file&n; * @flags: 0 or MAP_NONBLOCKED - the later will cause no IO.&n; *&n; * this syscall works purely via pagetables, so it&squot;s the most efficient&n; * way to map the same (large) file into a given virtual window. Unlike&n; * mmap()/mremap() it does not create any new vmas. The new mappings are&n; * also safe across swapout.&n; *&n; * NOTE: the &squot;prot&squot; parameter right now is ignored, and the vma&squot;s default&n; * protection is used. Arbitrary protections might be implemented in the&n; * future.&n; */
DECL|function|sys_remap_file_pages
id|asmlinkage
r_int
id|sys_remap_file_pages
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
comma
r_int
r_int
id|__prot
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
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|size
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
id|has_write_lock
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|__prot
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Sanitize the syscall parameters:&n;&t; */
id|start
op_assign
id|start
op_amp
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|size
op_amp
id|PAGE_MASK
suffix:semicolon
multiline_comment|/* Does the address range wrap, or is the span zero-sized? */
r_if
c_cond
(paren
id|start
op_plus
id|size
op_le
id|start
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Can we represent this offset inside this architecture&squot;s pte&squot;s? */
macro_line|#if PTE_FILE_MAX_BITS &lt; BITS_PER_LONG
r_if
c_cond
(paren
id|pgoff
op_plus
(paren
id|size
op_rshift
id|PAGE_SHIFT
)paren
op_ge
(paren
l_int|1UL
op_lshift
id|PTE_FILE_MAX_BITS
)paren
)paren
r_return
id|err
suffix:semicolon
macro_line|#endif
multiline_comment|/* We need down_write() to change vma-&gt;vm_flags. */
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retry
suffix:colon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure the vma is shared, that it supports prefaulting,&n;&t; * and that the remapped range is valid and fully within&n;&t; * the single existing vma.  vm_private_data is used as a&n;&t; * swapout cursor in a VM_NONLINEAR vma (unless VM_RESERVED&n;&t; * or VM_LOCKED, but VM_LOCKED could be revoked later on).&n;&t; */
r_if
c_cond
(paren
id|vma
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
op_logical_and
(paren
op_logical_neg
id|vma-&gt;vm_private_data
op_logical_or
(paren
id|vma-&gt;vm_flags
op_amp
(paren
id|VM_NONLINEAR
op_or
id|VM_RESERVED
)paren
)paren
)paren
op_logical_and
id|vma-&gt;vm_ops
op_logical_and
id|vma-&gt;vm_ops-&gt;populate
op_logical_and
id|end
OG
id|start
op_logical_and
id|start
op_ge
id|vma-&gt;vm_start
op_logical_and
id|end
op_le
id|vma-&gt;vm_end
)paren
(brace
multiline_comment|/* Must set VM_NONLINEAR before any pages are populated. */
r_if
c_cond
(paren
id|pgoff
op_ne
id|linear_page_index
c_func
(paren
id|vma
comma
id|start
)paren
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_NONLINEAR
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|has_write_lock
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|has_write_lock
op_assign
l_int|1
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
id|mapping
op_assign
id|vma-&gt;vm_file-&gt;f_mapping
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
id|flush_dcache_mmap_lock
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_NONLINEAR
suffix:semicolon
id|vma_prio_tree_remove
c_func
(paren
id|vma
comma
op_amp
id|mapping-&gt;i_mmap
)paren
suffix:semicolon
id|vma_prio_tree_init
c_func
(paren
id|vma
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|vma-&gt;shared.vm_set.list
comma
op_amp
id|mapping-&gt;i_mmap_nonlinear
)paren
suffix:semicolon
id|flush_dcache_mmap_unlock
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mapping-&gt;i_mmap_lock
)paren
suffix:semicolon
)brace
id|err
op_assign
id|vma-&gt;vm_ops
op_member_access_from_pointer
id|populate
c_func
(paren
id|vma
comma
id|start
comma
id|size
comma
id|vma-&gt;vm_page_prot
comma
id|pgoff
comma
id|flags
op_amp
id|MAP_NONBLOCK
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We can&squot;t clear VM_NONLINEAR because we&squot;d have to do&n;&t;&t; * it after -&gt;populate completes, and that would prevent&n;&t;&t; * downgrading the lock.  (Locks can&squot;t be upgraded).&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|has_write_lock
)paren
)paren
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_else
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
