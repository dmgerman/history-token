multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; *&n; *  PowerPC version derived from arch/arm/mm/consistent.c&n; *    Copyright (C) 2001 Dan Malek (dmalek@jlc.net)&n; *&n; *  linux/arch/arm/mm/consistent.c&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * Consistent memory allocators.  Used for DMA devices that want to&n; * share uncached memory with the processor core.  The function return&n; * is the virtual address and &squot;dma_handle&squot; is the physical address.&n; * Mostly stolen from the ARM port, with some changes for PowerPC.&n; *&t;&t;&t;&t;&t;&t;-- Dan&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
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
macro_line|#include &lt;linux/pci.h&gt;
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
r_extern
r_int
id|get_pteptr
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
comma
id|pte_t
op_star
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/* This function will allocate the requested contiguous pages and&n; * map them into the kernel&squot;s vmalloc() space.  This is done so we&n; * get unique mapping for these pages, outside of the kernel&squot;s 1:1&n; * virtual:physical mapping.  This is necessary so we can cover large&n; * portions of the kernel with single large page TLB entries, and&n; * still get unique uncached pages for consistent DMA.&n; */
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
id|dma_handle
)paren
(brace
r_int
id|order
comma
id|err
comma
id|i
suffix:semicolon
r_int
r_int
id|page
comma
id|va
comma
id|pa
comma
id|flags
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Only allocate page size areas.&n;&t;*/
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
id|__get_free_pages
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
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * we need to ensure that there are no cachelines in use,&n;&t; * or worse dirty in this area.&n;&t; */
id|invalidate_dcache_range
c_func
(paren
id|page
comma
id|page
op_plus
id|size
)paren
suffix:semicolon
multiline_comment|/* Allocate some common virtual space to map the new pages.&n;&t;*/
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_ALLOC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|area
op_eq
l_int|0
)paren
(brace
id|free_pages
c_func
(paren
id|page
comma
id|order
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|va
op_assign
id|VMALLOC_VMADDR
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
id|ret
op_assign
(paren
r_void
op_star
)paren
id|va
suffix:semicolon
multiline_comment|/* This gives us the real physical address of the first page.&n;&t;*/
op_star
id|dma_handle
op_assign
id|pa
op_assign
id|virt_to_bus
c_func
(paren
id|page
)paren
suffix:semicolon
id|flags
op_assign
id|_PAGE_KERNEL
op_or
id|_PAGE_NO_CACHE
suffix:semicolon
id|err
op_assign
l_int|0
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
id|size
op_logical_and
id|err
op_eq
l_int|0
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
id|err
op_assign
id|map_page
c_func
(paren
id|va
op_plus
id|i
comma
id|pa
op_plus
id|i
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
id|va
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * free page(s) as defined by the above mapping.&n; */
DECL|function|consistent_free
r_void
id|consistent_free
c_func
(paren
r_void
op_star
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
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
id|PCI_DMA_NONE
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_case
id|PCI_DMA_FROMDEVICE
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
id|PCI_DMA_TODEVICE
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
id|PCI_DMA_BIDIRECTIONAL
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
multiline_comment|/*&n; * consistent_sync_page make a page are consistent. identical&n; * to consistent_sync, but takes a struct page instead of a virtual address&n; */
DECL|function|consistent_sync_page
r_void
id|consistent_sync_page
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
r_int
id|start
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
(paren
id|page
op_member_access_from_pointer
r_virtual
)paren
op_plus
id|offset
suffix:semicolon
id|consistent_sync
c_func
(paren
id|start
comma
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
eof
