multiline_comment|/*&n; *  PowerPC version derived from arch/arm/mm/consistent.c&n; *    Copyright (C) 2001 Dan Malek (dmalek@jlc.net)&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * Consistent memory allocators.  Used for DMA devices that want to&n; * share uncached memory with the processor core.  The function return&n; * is the virtual address and &squot;dma_handle&squot; is the physical address.&n; * Mostly stolen from the ARM port, with some changes for PowerPC.&n; *&t;&t;&t;&t;&t;&t;-- Dan&n; *&n; * Reorganized to get rid of the arch-specific consistent_* functions&n; * and provide non-coherent implementations for the DMA API. -Matt&n; *&n; * Added in_interrupt() safe dma_alloc_coherent()/dma_free_coherent()&n; * implementation. This is pulled straight from ARM and barely&n; * modified. -Matt&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
r_int
id|map_page
c_func
(paren
r_int
r_int
id|va
comma
id|phys_addr_t
id|pa
comma
r_int
id|flags
)paren
suffix:semicolon
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * This address range defaults to a value that is safe for all&n; * platforms which currently set CONFIG_NOT_COHERENT_CACHE. It&n; * can be further configured for specific applications under&n; * the &quot;Advanced Setup&quot; menu. -Matt&n; */
DECL|macro|CONSISTENT_BASE
mdefine_line|#define CONSISTENT_BASE&t;(CONFIG_CONSISTENT_START)
DECL|macro|CONSISTENT_END
mdefine_line|#define CONSISTENT_END&t;(CONFIG_CONSISTENT_START + CONFIG_CONSISTENT_SIZE)
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
r_static
r_struct
id|vm_region
op_star
DECL|function|vm_region_alloc
id|vm_region_alloc
c_func
(paren
r_struct
id|vm_region
op_star
id|head
comma
r_int
id|size
comma
r_int
id|gfp
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
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|vm_region
op_star
id|c
comma
op_star
r_new
suffix:semicolon
r_new
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
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_goto
id|out
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
id|nospc
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
id|nospc
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|consistent_lock
comma
id|flags
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
id|nospc
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
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|NULL
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
multiline_comment|/*&n; * Allocate DMA-coherent memory space and return both the kernel remapped&n; * virtual and bus address for that space.&n; */
r_void
op_star
DECL|function|__dma_alloc_coherent
id|__dma_alloc_coherent
c_func
(paren
r_int
id|size
comma
id|dma_addr_t
op_star
id|handle
comma
r_int
id|gfp
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
suffix:semicolon
id|u64
id|mask
op_assign
l_int|0x00ffffff
comma
id|limit
suffix:semicolon
multiline_comment|/* ISA default */
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
l_string|&quot;%s: not initialised&bslash;n&quot;
comma
id|__func__
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
id|limit
op_assign
(paren
id|mask
op_plus
l_int|1
)paren
op_amp
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
(paren
id|limit
op_logical_and
id|size
op_ge
id|limit
)paren
op_logical_or
id|size
op_ge
(paren
id|CONSISTENT_END
op_minus
id|CONSISTENT_BASE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;coherent allocation too big (requested %#x mask %#Lx)&bslash;n&quot;
comma
id|size
comma
id|mask
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_ne
l_int|0xffffffff
)paren
id|gfp
op_or_assign
id|GFP_DMA
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
multiline_comment|/*&n;&t; * Invalidate any data that might be lurking in the&n;&t; * kernel direct-mapped region for device DMA.&n;&t; */
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
id|memset
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|flush_dcache_range
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
multiline_comment|/*&n;&t; * Allocate a virtual address in the consistent mapping region.&n;&t; */
id|c
op_assign
id|vm_region_alloc
c_func
(paren
op_amp
id|consistent_head
comma
id|size
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
id|c
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
id|pgprot_noncached
c_func
(paren
id|PAGE_KERNEL
)paren
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
r_return
(paren
r_void
op_star
)paren
id|c-&gt;vm_start
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
)paren
id|__free_pages
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
id|no_page
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|__dma_alloc_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|__dma_alloc_coherent
)paren
suffix:semicolon
multiline_comment|/*&n; * free a page as defined by the above mapping.&n; */
DECL|function|__dma_free_coherent
r_void
id|__dma_free_coherent
c_func
(paren
r_int
id|size
comma
r_void
op_star
id|vaddr
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
l_string|&quot;%s: freeing wrong coherent size (%ld != %d)&bslash;n&quot;
comma
id|__func__
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
l_string|&quot;%s: bad page in kernel page table&bslash;n&quot;
comma
id|__func__
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
l_string|&quot;%s: trying to free invalid coherent area: %p&bslash;n&quot;
comma
id|__func__
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
DECL|variable|__dma_free_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|__dma_free_coherent
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialise the consistent memory allocation.&n; */
DECL|function|dma_alloc_init
r_static
r_int
id|__init
id|dma_alloc_init
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
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
l_string|&quot;%s: no pmd tables&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
id|WARN_ON
c_func
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
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
l_string|&quot;%s: no pte tables&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
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
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dma_alloc_init
id|core_initcall
c_func
(paren
id|dma_alloc_init
)paren
suffix:semicolon
multiline_comment|/*&n; * make an area consistent.&n; */
DECL|function|__dma_sync
r_void
id|__dma_sync
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
id|DMA_NONE
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
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
)brace
)brace
DECL|variable|__dma_sync
id|EXPORT_SYMBOL
c_func
(paren
id|__dma_sync
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
multiline_comment|/*&n; * __dma_sync_page() implementation for systems using highmem.&n; * In this case, each page of a buffer must be kmapped/kunmapped&n; * in order to have a virtual address for __dma_sync(). This must&n; * not sleep so kmap_atmomic()/kunmap_atomic() are used.&n; *&n; * Note: yes, it is possible and correct to have a buffer extend&n; * beyond the first page.&n; */
DECL|function|__dma_sync_page_highmem
r_static
r_inline
r_void
id|__dma_sync_page_highmem
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_int
id|seg_size
op_assign
id|min
c_func
(paren
(paren
r_int
)paren
id|PAGE_SIZE
comma
id|size
)paren
op_minus
id|offset
suffix:semicolon
r_int
id|cur_size
op_assign
id|seg_size
suffix:semicolon
r_int
r_int
id|flags
comma
id|start
comma
id|seg_offset
op_assign
id|offset
suffix:semicolon
r_int
id|nr_segs
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
op_plus
(paren
id|PAGE_SIZE
op_minus
id|offset
)paren
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_int
id|seg_nr
op_assign
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_do
(brace
id|start
op_assign
(paren
r_int
r_int
)paren
id|kmap_atomic
c_func
(paren
id|page
op_plus
id|seg_nr
comma
id|KM_PPC_SYNC_PAGE
)paren
op_plus
id|seg_offset
suffix:semicolon
multiline_comment|/* Sync this buffer segment */
id|__dma_sync
c_func
(paren
(paren
r_void
op_star
)paren
id|start
comma
id|seg_size
comma
id|direction
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
(paren
r_void
op_star
)paren
id|start
comma
id|KM_PPC_SYNC_PAGE
)paren
suffix:semicolon
id|seg_nr
op_increment
suffix:semicolon
multiline_comment|/* Calculate next buffer segment size */
id|seg_size
op_assign
id|min
c_func
(paren
(paren
r_int
)paren
id|PAGE_SIZE
comma
id|size
op_minus
id|cur_size
)paren
suffix:semicolon
multiline_comment|/* Add the segment size to our running total */
id|cur_size
op_add_assign
id|seg_size
suffix:semicolon
id|seg_offset
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|seg_nr
OL
id|nr_segs
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HIGHMEM */
multiline_comment|/*&n; * __dma_sync_page makes memory consistent. identical to __dma_sync, but&n; * takes a struct page instead of a virtual address&n; */
DECL|function|__dma_sync_page
r_void
id|__dma_sync_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
id|__dma_sync_page_highmem
c_func
(paren
id|page
comma
id|offset
comma
id|size
comma
id|direction
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|start
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
op_plus
id|offset
suffix:semicolon
id|__dma_sync
c_func
(paren
(paren
r_void
op_star
)paren
id|start
comma
id|size
comma
id|direction
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|__dma_sync_page
id|EXPORT_SYMBOL
c_func
(paren
id|__dma_sync_page
)paren
suffix:semicolon
eof
