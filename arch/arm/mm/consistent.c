multiline_comment|/*&n; *  linux/arch/arm/mm/consistent.c&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  DMA uncached mapping support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|CONSISTENT_BASE
mdefine_line|#define CONSISTENT_BASE&t;(0xffc00000)
DECL|macro|CONSISTENT_END
mdefine_line|#define CONSISTENT_END&t;(0xffe00000)
DECL|macro|CONSISTENT_OFFSET
mdefine_line|#define CONSISTENT_OFFSET(x)&t;(((unsigned long)(x) - CONSISTENT_BASE) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * This is the page table (2MB) covering uncached, DMA consistent allocations&n; */
DECL|variable|consistent_pte
r_static
id|pte_t
op_star
id|consistent_pte
suffix:semicolon
DECL|variable|consistent_lock
r_static
id|spinlock_t
id|consistent_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * VM region handling support.&n; *&n; * This should become something generic, handling VM region allocations for&n; * vmalloc and similar (ioremap, module space, etc).&n; *&n; * I envisage vmalloc()&squot;s supporting vm_struct becoming:&n; *&n; *  struct vm_struct {&n; *    struct vm_region&t;region;&n; *    unsigned long&t;flags;&n; *    struct page&t;**pages;&n; *    unsigned int&t;nr_pages;&n; *    unsigned long&t;phys_addr;&n; *  };&n; *&n; * get_vm_area() would then call vm_region_alloc with an appropriate&n; * struct vm_region head (eg):&n; *&n; *  struct vm_region vmalloc_head = {&n; *&t;.vm_list&t;= LIST_HEAD_INIT(vmalloc_head.vm_list),&n; *&t;.vm_start&t;= VMALLOC_START,&n; *&t;.vm_end&t;&t;= VMALLOC_END,&n; *  };&n; *&n; * However, vmalloc_head.vm_start is variable (typically, it is dependent on&n; * the amount of RAM found at boot time.)  I would imagine that get_vm_area()&n; * would have to initialise this each time prior to calling vm_region_alloc().&n; */
DECL|struct|vm_region
r_struct
id|vm_region
(brace
DECL|member|vm_list
r_struct
id|list_head
id|vm_list
suffix:semicolon
DECL|member|vm_start
r_int
r_int
id|vm_start
suffix:semicolon
DECL|member|vm_end
r_int
r_int
id|vm_end
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|consistent_head
r_static
r_struct
id|vm_region
id|consistent_head
op_assign
(brace
dot
id|vm_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|consistent_head.vm_list
)paren
comma
dot
id|vm_start
op_assign
id|CONSISTENT_BASE
comma
dot
id|vm_end
op_assign
id|CONSISTENT_END
comma
)brace
suffix:semicolon
macro_line|#if 0
r_static
r_void
id|vm_region_dump
c_func
(paren
r_struct
id|vm_region
op_star
id|head
comma
r_char
op_star
id|fn
)paren
(brace
r_struct
id|vm_region
op_star
id|c
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Consistent Allocation Map (%s):&bslash;n&quot;
comma
id|fn
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|c
comma
op_amp
id|head-&gt;vm_list
comma
id|vm_list
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %p:  %08lx - %08lx   (0x%08x)&bslash;n&quot;
comma
id|c
comma
id|c-&gt;vm_start
comma
id|c-&gt;vm_end
comma
id|c-&gt;vm_end
op_minus
id|c-&gt;vm_start
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|macro|vm_region_dump
mdefine_line|#define vm_region_dump(head,fn)&t;do { } while(0)
macro_line|#endif
DECL|function|vm_region_alloc
r_static
r_int
id|vm_region_alloc
c_func
(paren
r_struct
id|vm_region
op_star
id|head
comma
r_struct
id|vm_region
op_star
r_new
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
op_assign
id|head-&gt;vm_start
comma
id|end
op_assign
id|head-&gt;vm_end
op_minus
id|size
suffix:semicolon
r_struct
id|vm_region
op_star
id|c
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|c
comma
op_amp
id|head-&gt;vm_list
comma
id|vm_list
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
op_plus
id|size
)paren
OL
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
op_plus
id|size
)paren
op_le
id|c-&gt;vm_start
)paren
r_goto
id|found
suffix:semicolon
id|addr
op_assign
id|c-&gt;vm_end
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|end
)paren
r_goto
id|out
suffix:semicolon
)brace
id|found
suffix:colon
multiline_comment|/*&n;&t; * Insert this entry _before_ the one we found.&n;&t; */
id|list_add_tail
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|vm_list
comma
op_amp
id|c-&gt;vm_list
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|vm_start
op_assign
id|addr
suffix:semicolon
r_new
op_member_access_from_pointer
id|vm_end
op_assign
id|addr
op_plus
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|vm_region_find
r_static
r_struct
id|vm_region
op_star
id|vm_region_find
c_func
(paren
r_struct
id|vm_region
op_star
id|head
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|vm_region
op_star
id|c
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|c
comma
op_amp
id|head-&gt;vm_list
comma
id|vm_list
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;vm_start
op_eq
id|addr
)paren
r_goto
id|out
suffix:semicolon
)brace
id|c
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/*&n; * This allocates one page of cache-coherent memory space and returns&n; * both the virtual and a &quot;dma&quot; address to that space.&n; */
DECL|function|consistent_alloc
r_void
op_star
id|consistent_alloc
c_func
(paren
r_int
id|gfp
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|handle
comma
r_int
r_int
id|cache_flags
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|vm_region
op_star
id|c
suffix:semicolon
r_int
r_int
id|order
comma
id|flags
suffix:semicolon
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|consistent_pte
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_alloc: not initialised&bslash;n&quot;
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
id|page
op_assign
id|alloc_pages
c_func
(paren
id|gfp
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|no_page
suffix:semicolon
multiline_comment|/*&n;&t; * Invalidate any data that might be lurking in the&n;&t; * kernel direct-mapped region.&n;&t; */
(brace
r_int
r_int
id|kaddr
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
id|invalidate_dcache_range
c_func
(paren
id|kaddr
comma
id|kaddr
op_plus
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Our housekeeping doesn&squot;t need to come from DMA,&n;&t; * but it must not come from highmem.&n;&t; */
id|c
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vm_region
)paren
comma
id|gfp
op_amp
op_complement
(paren
id|__GFP_DMA
op_or
id|__GFP_HIGHMEM
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_goto
id|no_remap
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
id|vm_region_dump
c_func
(paren
op_amp
id|consistent_head
comma
l_string|&quot;before alloc&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Attempt to allocate a virtual address in the&n;&t; * consistent mapping region.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|vm_region_alloc
c_func
(paren
op_amp
id|consistent_head
comma
id|c
comma
id|size
)paren
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
id|consistent_pte
op_plus
id|CONSISTENT_OFFSET
c_func
(paren
id|c-&gt;vm_start
)paren
suffix:semicolon
r_struct
id|page
op_star
id|end
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|order
)paren
suffix:semicolon
id|pgprot_t
id|prot
op_assign
id|__pgprot
c_func
(paren
id|L_PTE_PRESENT
op_or
id|L_PTE_YOUNG
op_or
id|L_PTE_DIRTY
op_or
id|L_PTE_WRITE
op_or
id|cache_flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the &quot;dma handle&quot;&n;&t;&t; */
op_star
id|handle
op_assign
id|page_to_bus
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|SetPageReserved
c_func
(paren
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
id|page
op_increment
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_sub_assign
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Free the otherwise unused pages.&n;&t;&t; */
r_while
c_loop
(paren
id|page
OL
id|end
)paren
(brace
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
id|ret
op_assign
(paren
r_void
op_star
)paren
id|c-&gt;vm_start
suffix:semicolon
)brace
id|vm_region_dump
c_func
(paren
op_amp
id|consistent_head
comma
l_string|&quot;after alloc&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
id|no_remap
suffix:colon
r_if
c_cond
(paren
id|ret
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
id|__free_pages
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
)brace
id|no_page
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * free a page as defined by the above mapping.&n; */
DECL|function|consistent_free
r_void
id|consistent_free
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
id|dma_addr_t
id|handle
)paren
(brace
r_struct
id|vm_region
op_star
id|c
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
id|vm_region_dump
c_func
(paren
op_amp
id|consistent_head
comma
l_string|&quot;before free&quot;
)paren
suffix:semicolon
id|c
op_assign
id|vm_region_find
c_func
(paren
op_amp
id|consistent_head
comma
(paren
r_int
r_int
)paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_goto
id|no_area
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;vm_end
op_minus
id|c-&gt;vm_start
)paren
op_ne
id|size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_free: wrong size (%ld != %d)&bslash;n&quot;
comma
id|c-&gt;vm_end
op_minus
id|c-&gt;vm_start
comma
id|size
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|size
op_assign
id|c-&gt;vm_end
op_minus
id|c-&gt;vm_start
suffix:semicolon
)brace
id|ptep
op_assign
id|consistent_pte
op_plus
id|CONSISTENT_OFFSET
c_func
(paren
id|c-&gt;vm_start
)paren
suffix:semicolon
r_do
(brace
id|pte_t
id|pte
op_assign
id|ptep_get_and_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_int
r_int
id|pfn
suffix:semicolon
id|ptep
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
id|pte
)paren
op_logical_and
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
id|pfn
op_assign
id|pte_pfn
c_func
(paren
id|pte
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
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;consistent_free: bad page in kernel page &quot;
l_string|&quot;table&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_sub_assign
id|PAGE_SIZE
)paren
suffix:semicolon
id|flush_tlb_kernel_range
c_func
(paren
id|c-&gt;vm_start
comma
id|c-&gt;vm_end
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|c-&gt;vm_list
)paren
suffix:semicolon
id|vm_region_dump
c_func
(paren
op_amp
id|consistent_head
comma
l_string|&quot;after free&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
suffix:semicolon
id|no_area
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_free: trying to free &quot;
l_string|&quot;invalid area: %p&bslash;n&quot;
comma
id|vaddr
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise the consistent memory allocation.&n; */
DECL|function|consistent_init
r_static
r_int
id|__init
id|consistent_init
c_func
(paren
r_void
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
r_do
(brace
id|pgd
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|CONSISTENT_BASE
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|CONSISTENT_BASE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_init: out of pmd tables&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_init: PMD already allocated&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|CONSISTENT_BASE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;consistent_init: out of pte tables&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|consistent_pte
op_assign
id|pte
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|consistent_init
id|core_initcall
c_func
(paren
id|consistent_init
)paren
suffix:semicolon
multiline_comment|/*&n; * make an area consistent.&n; */
DECL|function|consistent_sync
r_void
id|consistent_sync
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_int
r_int
id|start
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|size
suffix:semicolon
r_switch
c_cond
(paren
id|direction
)paren
(brace
r_case
id|DMA_FROM_DEVICE
suffix:colon
multiline_comment|/* invalidate only */
id|invalidate_dcache_range
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_TO_DEVICE
suffix:colon
multiline_comment|/* writeback only */
id|clean_dcache_range
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_BIDIRECTIONAL
suffix:colon
multiline_comment|/* writeback and invalidate */
id|flush_dcache_range
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
eof
