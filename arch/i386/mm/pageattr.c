multiline_comment|/* &n; * Copyright 2002 Andi Kleen, SuSE Labs. &n; * Thanks to Ben LaHaise for precious feedback.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|function|lookup_address
r_static
r_inline
id|pte_t
op_star
id|lookup_address
c_func
(paren
r_int
r_int
id|address
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|address
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
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
l_int|NULL
suffix:semicolon
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
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pmd_large
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
(paren
id|pte_t
op_star
)paren
id|pmd
suffix:semicolon
r_return
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
)brace
DECL|function|split_large_page
r_static
r_struct
id|page
op_star
id|split_large_page
c_func
(paren
r_int
r_int
id|address
comma
id|pgprot_t
id|prot
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|page
op_star
id|base
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|0
)paren
suffix:semicolon
id|pte_t
op_star
id|pbase
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
r_return
l_int|NULL
suffix:semicolon
id|address
op_assign
id|__pa
c_func
(paren
id|address
)paren
suffix:semicolon
id|addr
op_assign
id|address
op_amp
id|LARGE_PAGE_MASK
suffix:semicolon
id|pbase
op_assign
(paren
id|pte_t
op_star
)paren
id|page_address
c_func
(paren
id|base
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
id|PTRS_PER_PTE
suffix:semicolon
id|i
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|pbase
(braket
id|i
)braket
op_assign
id|pfn_pte
c_func
(paren
id|addr
op_rshift
id|PAGE_SHIFT
comma
id|addr
op_eq
id|address
ques
c_cond
id|prot
suffix:colon
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
r_return
id|base
suffix:semicolon
)brace
DECL|function|flush_kernel_map
r_static
r_void
id|flush_kernel_map
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
multiline_comment|/* Could use CLFLUSH here if the CPU supports it (Hammer,P4) */
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
op_ge
l_int|4
)paren
id|asm
r_volatile
(paren
l_string|&quot;wbinvd&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Flush all to work around Errata in early athlons regarding &n;&t; * large page flushing. &n;&t; */
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|set_pmd_pte
r_static
r_void
id|set_pmd_pte
c_func
(paren
id|pte_t
op_star
id|kpte
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
id|set_pte_atomic
c_func
(paren
id|kpte
comma
id|pte
)paren
suffix:semicolon
multiline_comment|/* change init_mm */
macro_line|#ifndef CONFIG_X86_PAE
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mmlist_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|init_mm.mmlist
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|mm_struct
comma
id|mmlist
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
comma
id|address
)paren
suffix:semicolon
id|set_pte_atomic
c_func
(paren
(paren
id|pte_t
op_star
)paren
id|pmd
comma
id|pte
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mmlist_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* &n; * No more special protections in this 2/4MB area - revert to a&n; * large page again. &n; */
DECL|function|revert_page
r_static
r_inline
r_void
id|revert_page
c_func
(paren
r_struct
id|page
op_star
id|kpte_page
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|linear
op_assign
(paren
id|pte_t
op_star
)paren
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
comma
id|address
)paren
suffix:semicolon
id|set_pmd_pte
c_func
(paren
id|linear
comma
id|address
comma
id|pfn_pte
c_func
(paren
(paren
id|__pa
c_func
(paren
id|address
)paren
op_amp
id|LARGE_PAGE_MASK
)paren
op_rshift
id|PAGE_SHIFT
comma
id|PAGE_KERNEL_LARGE
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|__change_page_attr
id|__change_page_attr
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|prot
comma
r_struct
id|page
op_star
op_star
id|oldpage
)paren
(brace
id|pte_t
op_star
id|kpte
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_struct
id|page
op_star
id|kpte_page
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
r_if
c_cond
(paren
id|page
op_ge
id|highmem_start_page
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|address
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|kpte
op_assign
id|lookup_address
c_func
(paren
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kpte
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kpte_page
op_assign
id|virt_to_page
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|kpte
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgprot_val
c_func
(paren
id|prot
)paren
op_ne
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|kpte
)paren
op_amp
id|_PAGE_PSE
)paren
op_eq
l_int|0
)paren
(brace
id|pte_t
id|old
op_assign
op_star
id|kpte
suffix:semicolon
id|pte_t
id|standard
op_assign
id|mk_pte
c_func
(paren
id|page
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
id|set_pte_atomic
c_func
(paren
id|kpte
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
r_if
c_cond
(paren
id|pte_same
c_func
(paren
id|old
comma
id|standard
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|kpte_page-&gt;count
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|page
op_star
id|split
op_assign
id|split_large_page
c_func
(paren
id|address
comma
id|prot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|split
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|kpte_page-&gt;count
)paren
suffix:semicolon
id|set_pmd_pte
c_func
(paren
id|kpte
comma
id|address
comma
id|mk_pte
c_func
(paren
id|split
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|kpte
)paren
op_amp
id|_PAGE_PSE
)paren
op_eq
l_int|0
)paren
(brace
id|set_pte_atomic
c_func
(paren
id|kpte
comma
id|mk_pte
c_func
(paren
id|page
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kpte_page-&gt;count
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu_has_pse
op_logical_and
(paren
id|atomic_read
c_func
(paren
op_amp
id|kpte_page-&gt;count
)paren
op_eq
l_int|1
)paren
)paren
(brace
op_star
id|oldpage
op_assign
id|kpte_page
suffix:semicolon
id|revert_page
c_func
(paren
id|kpte_page
comma
id|address
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_map
r_static
r_inline
r_void
id|flush_map
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP 
id|smp_call_function
c_func
(paren
id|flush_kernel_map
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif&t;
id|flush_kernel_map
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|struct|deferred_page
r_struct
id|deferred_page
(brace
DECL|member|next
r_struct
id|deferred_page
op_star
id|next
suffix:semicolon
DECL|member|fpage
r_struct
id|page
op_star
id|fpage
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|df_list
r_static
r_struct
id|deferred_page
op_star
id|df_list
suffix:semicolon
multiline_comment|/* protected by init_mm.mmap_sem */
multiline_comment|/*&n; * Change the page attributes of an page in the linear mapping.&n; *&n; * This should be used when a page is mapped with a different caching policy&n; * than write-back somewhere - some CPUs do not like it when mappings with&n; * different caching policies exist. This changes the page attributes of the&n; * in kernel linear mapping too.&n; * &n; * The caller needs to ensure that there are no conflicting mappings elsewhere.&n; * This function only deals with the kernel linear map.&n; * &n; * Caller must call global_flush_tlb() after this.&n; */
DECL|function|change_page_attr
r_int
id|change_page_attr
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|numpages
comma
id|pgprot_t
id|prot
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|fpage
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|init_mm.mmap_sem
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
id|numpages
suffix:semicolon
id|i
op_increment
comma
id|page
op_increment
)paren
(brace
id|fpage
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
id|__change_page_attr
c_func
(paren
id|page
comma
id|prot
comma
op_amp
id|fpage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|fpage
)paren
(brace
r_struct
id|deferred_page
op_star
id|df
suffix:semicolon
id|df
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|deferred_page
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|df
)paren
(brace
id|flush_map
c_func
(paren
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|fpage
)paren
suffix:semicolon
)brace
r_else
(brace
id|df-&gt;next
op_assign
id|df_list
suffix:semicolon
id|df-&gt;fpage
op_assign
id|fpage
suffix:semicolon
id|df_list
op_assign
id|df
suffix:semicolon
)brace
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|init_mm.mmap_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|global_flush_tlb
r_void
id|global_flush_tlb
c_func
(paren
r_void
)paren
(brace
r_struct
id|deferred_page
op_star
id|df
comma
op_star
id|next_df
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|init_mm.mmap_sem
)paren
suffix:semicolon
id|df
op_assign
id|xchg
c_func
(paren
op_amp
id|df_list
comma
l_int|NULL
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|init_mm.mmap_sem
)paren
suffix:semicolon
id|flush_map
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|df
suffix:semicolon
id|df
op_assign
id|next_df
)paren
(brace
id|next_df
op_assign
id|df-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|df-&gt;fpage
)paren
id|__free_page
c_func
(paren
id|df-&gt;fpage
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|df
)paren
suffix:semicolon
)brace
)brace
DECL|variable|change_page_attr
id|EXPORT_SYMBOL
c_func
(paren
id|change_page_attr
)paren
suffix:semicolon
DECL|variable|global_flush_tlb
id|EXPORT_SYMBOL
c_func
(paren
id|global_flush_tlb
)paren
suffix:semicolon
eof
