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
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|cpa_lock
)paren
suffix:semicolon
DECL|variable|df_list
r_static
r_struct
id|list_head
id|df_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|df_list
)paren
suffix:semicolon
DECL|function|lookup_address
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
id|pud_t
op_star
id|pud
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
id|pud_none
c_func
(paren
op_star
id|pud
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
id|pud
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
suffix:semicolon
id|pte_t
op_star
id|pbase
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cpa_lock
)paren
suffix:semicolon
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
id|spin_lock_irq
c_func
(paren
op_amp
id|cpa_lock
)paren
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
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|set_pte_atomic
c_func
(paren
id|kpte
comma
id|pte
)paren
suffix:semicolon
multiline_comment|/* change init_mm */
r_if
c_cond
(paren
id|PTRS_PER_PMD
OG
l_int|1
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pgd_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|pgd_list
suffix:semicolon
id|page
suffix:semicolon
id|page
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page-&gt;index
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pud_t
op_star
id|pud
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
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
id|pud_offset
c_func
(paren
id|pgd_offset_k
c_func
(paren
id|address
)paren
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
id|BUG_ON
c_func
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
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
id|kpte
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
id|kpte_page
op_assign
id|split
suffix:semicolon
)brace
id|get_page
c_func
(paren
id|kpte_page
)paren
suffix:semicolon
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
id|__put_page
c_func
(paren
id|kpte_page
)paren
suffix:semicolon
)brace
r_else
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the pte was reserved, it means it was created at boot&n;&t; * time (not via split_large_page) and in turn we must not&n;&t; * replace it with a largepage.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|kpte_page
)paren
)paren
(brace
multiline_comment|/* memleak and potential failed 2M page regeneration */
id|BUG_ON
c_func
(paren
op_logical_neg
id|page_count
c_func
(paren
id|kpte_page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_pse
op_logical_and
(paren
id|page_count
c_func
(paren
id|kpte_page
)paren
op_eq
l_int|1
)paren
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|kpte_page-&gt;lru
comma
op_amp
id|df_list
)paren
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
id|on_each_cpu
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
)brace
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|cpa_lock
comma
id|flags
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
id|err
op_assign
id|__change_page_attr
c_func
(paren
id|page
comma
id|prot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cpa_lock
comma
id|flags
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
id|LIST_HEAD
c_func
(paren
id|l
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|n
suffix:semicolon
id|BUG_ON
c_func
(paren
id|irqs_disabled
c_func
(paren
)paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|cpa_lock
)paren
suffix:semicolon
id|list_splice_init
c_func
(paren
op_amp
id|df_list
comma
op_amp
id|l
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cpa_lock
)paren
suffix:semicolon
id|flush_map
c_func
(paren
)paren
suffix:semicolon
id|n
op_assign
id|l.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ne
op_amp
id|l
)paren
(brace
r_struct
id|page
op_star
id|pg
op_assign
id|list_entry
c_func
(paren
id|n
comma
r_struct
id|page
comma
id|lru
)paren
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
id|__free_page
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_DEBUG_PAGEALLOC
DECL|function|kernel_map_pages
r_void
id|kernel_map_pages
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
r_int
id|enable
)paren
(brace
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* the return value is ignored - the calls cannot fail,&n;&t; * large pages are disabled at boot time.&n;&t; */
id|change_page_attr
c_func
(paren
id|page
comma
id|numpages
comma
id|enable
ques
c_cond
id|PAGE_KERNEL
suffix:colon
id|__pgprot
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* we should perform an IPI and flush all tlbs,&n;&t; * but that can deadlock-&gt;flush only current cpu.&n;&t; */
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
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
