multiline_comment|/*&n; *  linux/arch/arm/mm/consistent.c&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Dynamic DMA mapping support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/*&n; * This allocates one page of cache-coherent memory space and returns&n; * both the virtual and a &quot;dma&quot; address to that space.&n; *&n; * We should allow this function to be called from interrupt context.&n; * However, we call ioremap, which needs to fiddle around with various&n; * things (like the vmlist_lock, and allocating page tables).  These&n; * things aren&squot;t interrupt safe (yet).&n; *&n; * Note that this does *not* zero the allocated area!&n; */
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
r_struct
id|page
op_star
id|page
comma
op_star
id|end
comma
op_star
id|free
suffix:semicolon
r_int
r_int
id|order
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
multiline_comment|/* FIXME */
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
op_star
id|dma_handle
op_assign
id|page_to_bus
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
id|__ioremap
c_func
(paren
id|page_to_phys
c_func
(paren
id|page
)paren
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_goto
id|no_remap
suffix:semicolon
macro_line|#if 0 /* ioremap_does_flush_cache_all */
(brace
r_void
op_star
id|virt
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we need to ensure that there are no cachelines in use, or&n;&t;&t; * worse dirty in this area.  Really, we don&squot;t need to do&n;&t;&t; * this since __ioremap does a flush_cache_all() anyway. --rmk&n;&t;&t; */
id|invalidate_dcache_range
c_func
(paren
id|virt
comma
id|virt
op_plus
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * free wasted pages.  We skip the first page since we know&n;&t; * that it will have count = 1 and won&squot;t require freeing.&n;&t; * We also mark the pages in use as reserved so that&n;&t; * remap_page_range works.&n;&t; */
id|free
op_assign
id|page
op_plus
(paren
id|size
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
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
r_for
c_loop
(paren
suffix:semicolon
id|page
OL
id|end
suffix:semicolon
id|page
op_increment
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
r_if
c_cond
(paren
id|page
op_ge
id|free
)paren
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|SetPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|no_remap
suffix:colon
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
DECL|function|pci_alloc_consistent
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|handle
)paren
(brace
r_int
id|gfp
op_assign
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
op_logical_or
id|hwdev-&gt;dma_mask
op_ne
l_int|0xffffffff
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
r_return
id|consistent_alloc
c_func
(paren
id|gfp
comma
id|size
comma
id|handle
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * free a page as defined by the above mapping.  We expressly forbid&n; * calling this from interrupt context.&n; */
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
id|page
op_star
id|page
comma
op_star
id|end
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
multiline_comment|/*&n;&t; * More messing around with the MM internals.  This is&n;&t; * sick, but then so is remap_page_range().&n;&t; */
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|bus_to_virt
c_func
(paren
id|handle
)paren
)paren
suffix:semicolon
id|end
op_assign
id|page
op_plus
(paren
id|size
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|page
OL
id|end
suffix:semicolon
id|page
op_increment
)paren
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|__iounmap
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
eof
