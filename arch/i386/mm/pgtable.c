multiline_comment|/*&n; *  linux/arch/i386/mm/pgtable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
r_int
id|highmem
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6ldkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|for_each_pgdat
c_func
(paren
id|pgdat
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pgdat-&gt;node_spanned_pages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|page
op_assign
id|pgdat-&gt;node_mem_map
op_plus
id|i
suffix:semicolon
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
id|highmem
op_increment
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
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Associate a virtual page frame with a given physical page frame &n; * and protection flags for that frame.&n; */
DECL|function|set_pte_pfn
r_static
r_void
id|set_pte_pfn
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|pfn
comma
id|pgprot_t
id|flags
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
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|pgd_index
c_func
(paren
id|vaddr
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
(brace
id|BUG
c_func
(paren
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
id|vaddr
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
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* &lt;pfn,flags&gt; stored as-is, to permit clearing entries */
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|pfn
comma
id|flags
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * It&squot;s enough to flush this one mapping.&n;&t; * (PGE mappings get flushed as well)&n;&t; */
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Associate a large virtual page frame with a given physical page frame &n; * and protection flags for that frame. pfn is for the base of the page,&n; * vaddr is what the page gets mapped to - both must be properly aligned. &n; * The pmd must already be instantiated. Assumes PAE mode.&n; */
DECL|function|set_pmd_pfn
r_void
id|set_pmd_pfn
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|pfn
comma
id|pgprot_t
id|flags
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
r_if
c_cond
(paren
id|vaddr
op_amp
(paren
id|PMD_SIZE
op_minus
l_int|1
)paren
)paren
(brace
multiline_comment|/* vaddr is misaligned */
id|printk
(paren
l_string|&quot;set_pmd_pfn: vaddr misaligned&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* BUG(); */
)brace
r_if
c_cond
(paren
id|pfn
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
)paren
(brace
multiline_comment|/* pfn is misaligned */
id|printk
(paren
l_string|&quot;set_pmd_pfn: pfn misaligned&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* BUG(); */
)brace
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|pgd_index
c_func
(paren
id|vaddr
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
(brace
id|printk
(paren
l_string|&quot;set_pmd_pfn: pgd_none&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* BUG(); */
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|pfn_pmd
c_func
(paren
id|pfn
comma
id|flags
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * It&squot;s enough to flush this one mapping.&n;&t; * (PGE mappings get flushed as well)&n;&t; */
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
DECL|function|__set_fixmap
r_void
id|__set_fixmap
(paren
r_enum
id|fixed_addresses
id|idx
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|flags
)paren
(brace
r_int
r_int
id|address
op_assign
id|__fix_to_virt
c_func
(paren
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|__end_of_fixed_addresses
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|set_pte_pfn
c_func
(paren
id|address
comma
id|phys
op_rshift
id|PAGE_SHIFT
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_one_kernel
id|pte_t
op_star
id|pte_alloc_one_kernel
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
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_alloc_one
r_struct
id|page
op_star
id|pte_alloc_one
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
)paren
(brace
r_struct
id|page
op_star
id|pte
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHPTE
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
op_or
id|__GFP_REPEAT
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|pte
)paren
id|clear_highpage
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pmd_ctor
r_void
id|pmd_ctor
c_func
(paren
r_void
op_star
id|pmd
comma
id|kmem_cache_t
op_star
id|cache
comma
r_int
r_int
id|flags
)paren
(brace
id|memset
c_func
(paren
id|pmd
comma
l_int|0
comma
id|PTRS_PER_PMD
op_star
r_sizeof
(paren
id|pmd_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * List of all pgd&squot;s needed for non-PAE so it can invalidate entries&n; * in both cached and uncached pgd&squot;s; not needed for PAE since the&n; * kernel pmd is shared. If PAE were not to share the pmd a similar&n; * tactic would be needed. This is essentially codepath-based locking&n; * against pageattr.c; it is the unique case in which a valid change&n; * of kernel pagetables can&squot;t be lazily synchronized by vmalloc faults.&n; * vmalloc faults work because attached pagetables are never freed.&n; * The locking scheme was chosen on the basis of manfred&squot;s&n; * recommendations and having no core impact whatsoever.&n; * -- wli&n; */
DECL|variable|pgd_lock
id|spinlock_t
id|pgd_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|pgd_list
r_struct
id|page
op_star
id|pgd_list
suffix:semicolon
DECL|function|pgd_list_add
r_static
r_inline
r_void
id|pgd_list_add
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|page-&gt;index
op_assign
(paren
r_int
r_int
)paren
id|pgd_list
suffix:semicolon
r_if
c_cond
(paren
id|pgd_list
)paren
id|pgd_list
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
op_amp
id|page-&gt;index
suffix:semicolon
id|pgd_list
op_assign
id|page
suffix:semicolon
id|page
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
op_amp
id|pgd_list
suffix:semicolon
)brace
DECL|function|pgd_list_del
r_static
r_inline
r_void
id|pgd_list_del
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_struct
id|page
op_star
id|next
comma
op_star
op_star
id|pprev
comma
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|next
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page-&gt;index
suffix:semicolon
id|pprev
op_assign
(paren
r_struct
id|page
op_star
op_star
)paren
id|page
op_member_access_from_pointer
r_private
suffix:semicolon
op_star
id|pprev
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
id|next
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
id|pprev
suffix:semicolon
)brace
DECL|function|pgd_ctor
r_void
id|pgd_ctor
c_func
(paren
r_void
op_star
id|pgd
comma
id|kmem_cache_t
op_star
id|cache
comma
r_int
r_int
id|unused
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|PTRS_PER_PMD
op_eq
l_int|1
)paren
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
id|pgd_t
op_star
)paren
id|pgd
op_plus
id|USER_PTRS_PER_PGD
comma
id|swapper_pg_dir
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PTRS_PER_PMD
OG
l_int|1
)paren
r_return
suffix:semicolon
id|pgd_list_add
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pgd
comma
l_int|0
comma
id|USER_PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* never called when PTRS_PER_PMD &gt; 1 */
DECL|function|pgd_dtor
r_void
id|pgd_dtor
c_func
(paren
r_void
op_star
id|pgd
comma
id|kmem_cache_t
op_star
id|cache
comma
r_int
r_int
id|unused
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* can be called from interrupt context */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
id|pgd_list_del
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pgd_alloc
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
id|i
suffix:semicolon
id|pgd_t
op_star
id|pgd
op_assign
id|kmem_cache_alloc
c_func
(paren
id|pgd_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PTRS_PER_PMD
op_eq
l_int|1
op_logical_or
op_logical_neg
id|pgd
)paren
r_return
id|pgd
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
id|USER_PTRS_PER_PGD
suffix:semicolon
op_increment
id|i
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|kmem_cache_alloc
c_func
(paren
id|pmd_cache
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_goto
id|out_oom
suffix:semicolon
id|set_pgd
c_func
(paren
op_amp
id|pgd
(braket
id|i
)braket
comma
id|__pgd
c_func
(paren
l_int|1
op_plus
id|__pa
c_func
(paren
(paren
id|u64
)paren
(paren
(paren
id|u32
)paren
id|pmd
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
id|out_oom
suffix:colon
r_for
c_loop
(paren
id|i
op_decrement
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|kmem_cache_free
c_func
(paren
id|pmd_cache
comma
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|pgd_val
c_func
(paren
id|pgd
(braket
id|i
)braket
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|pgd_cache
comma
id|pgd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pgd_free
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* in the PAE case user pgd entries are overwritten before usage */
r_if
c_cond
(paren
id|PTRS_PER_PMD
OG
l_int|1
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|USER_PTRS_PER_PGD
suffix:semicolon
op_increment
id|i
)paren
id|kmem_cache_free
c_func
(paren
id|pmd_cache
comma
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|pgd_val
c_func
(paren
id|pgd
(braket
id|i
)braket
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* in the non-PAE case, clear_page_tables() clears user pgd entries */
id|kmem_cache_free
c_func
(paren
id|pgd_cache
comma
id|pgd
)paren
suffix:semicolon
)brace
eof
