multiline_comment|/*&n; * arch/ppc64/kernel/iommu.c&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; * &n; * Rewrite, cleanup, new allocation schemes, virtual merging: &n; * Copyright (C) 2004 Olof Johansson, IBM Corporation&n; *               and  Ben. Herrenschmidt, IBM Corporation&n; *&n; * Dynamic DMA mapping support, bus-independent parts.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|macro|DBG
mdefine_line|#define DBG(...)
macro_line|#ifdef CONFIG_IOMMU_VMERGE
DECL|variable|novmerge
r_static
r_int
id|novmerge
op_assign
l_int|0
suffix:semicolon
macro_line|#else
DECL|variable|novmerge
r_static
r_int
id|novmerge
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
DECL|function|setup_iommu
r_static
r_int
id|__init
id|setup_iommu
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;novmerge&quot;
)paren
)paren
id|novmerge
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;vmerge&quot;
)paren
)paren
id|novmerge
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;iommu=&quot;
comma
id|setup_iommu
)paren
suffix:semicolon
DECL|function|iommu_range_alloc
r_static
r_int
r_int
id|iommu_range_alloc
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
r_int
id|npages
comma
r_int
r_int
op_star
id|handle
)paren
(brace
r_int
r_int
id|n
comma
id|end
comma
id|i
comma
id|start
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
r_int
id|largealloc
op_assign
id|npages
OG
l_int|15
suffix:semicolon
r_int
id|pass
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This allocator was derived from x86_64&squot;s bit string search */
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|npages
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|DMA_ERROR_CODE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|handle
op_logical_and
op_star
id|handle
)paren
id|start
op_assign
op_star
id|handle
suffix:semicolon
r_else
id|start
op_assign
id|largealloc
ques
c_cond
id|tbl-&gt;it_largehint
suffix:colon
id|tbl-&gt;it_hint
suffix:semicolon
multiline_comment|/* Use only half of the table for small allocs (15 pages or less) */
id|limit
op_assign
id|largealloc
ques
c_cond
id|tbl-&gt;it_mapsize
suffix:colon
id|tbl-&gt;it_halfpoint
suffix:semicolon
r_if
c_cond
(paren
id|largealloc
op_logical_and
id|start
OL
id|tbl-&gt;it_halfpoint
)paren
id|start
op_assign
id|tbl-&gt;it_halfpoint
suffix:semicolon
multiline_comment|/* The case below can happen if we have a small segment appended&n;&t; * to a large, or when the previous alloc was at the very end of&n;&t; * the available space. If so, go back to the initial start.&n;&t; */
r_if
c_cond
(paren
id|start
op_ge
id|limit
)paren
id|start
op_assign
id|largealloc
ques
c_cond
id|tbl-&gt;it_largehint
suffix:colon
id|tbl-&gt;it_hint
suffix:semicolon
id|again
suffix:colon
id|n
op_assign
id|find_next_zero_bit
c_func
(paren
id|tbl-&gt;it_map
comma
id|limit
comma
id|start
)paren
suffix:semicolon
id|end
op_assign
id|n
op_plus
id|npages
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|end
op_ge
id|limit
)paren
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pass
OL
l_int|2
)paren
)paren
(brace
multiline_comment|/* First failure, just rescan the half of the table.&n;&t;&t;&t; * Second failure, rescan the other half of the table.&n;&t;&t;&t; */
id|start
op_assign
(paren
id|largealloc
op_xor
id|pass
)paren
ques
c_cond
id|tbl-&gt;it_halfpoint
suffix:colon
l_int|0
suffix:semicolon
id|limit
op_assign
id|pass
ques
c_cond
id|tbl-&gt;it_mapsize
suffix:colon
id|limit
suffix:semicolon
id|pass
op_increment
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Third failure, give up */
r_return
id|DMA_ERROR_CODE
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
id|n
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|tbl-&gt;it_map
)paren
)paren
(brace
id|start
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|n
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
id|__set_bit
c_func
(paren
id|i
comma
id|tbl-&gt;it_map
)paren
suffix:semicolon
multiline_comment|/* Bump the hint to a new block for small allocs. */
r_if
c_cond
(paren
id|largealloc
)paren
(brace
multiline_comment|/* Don&squot;t bump to new block to avoid fragmentation */
id|tbl-&gt;it_largehint
op_assign
id|end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Overflow will be taken care of at the next allocation */
id|tbl-&gt;it_hint
op_assign
(paren
id|end
op_plus
id|tbl-&gt;it_blocksize
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|tbl-&gt;it_blocksize
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Update handle for SG allocations */
r_if
c_cond
(paren
id|handle
)paren
op_star
id|handle
op_assign
id|end
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|iommu_alloc
r_static
id|dma_addr_t
id|iommu_alloc
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_void
op_star
id|page
comma
r_int
r_int
id|npages
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
r_int
id|entry
comma
id|flags
suffix:semicolon
id|dma_addr_t
id|ret
op_assign
id|DMA_ERROR_CODE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|entry
op_assign
id|iommu_range_alloc
c_func
(paren
id|tbl
comma
id|npages
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|entry
op_eq
id|DMA_ERROR_CODE
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
id|DMA_ERROR_CODE
suffix:semicolon
)brace
id|entry
op_add_assign
id|tbl-&gt;it_offset
suffix:semicolon
multiline_comment|/* Offset into real TCE table */
id|ret
op_assign
id|entry
op_lshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Set the return dma address */
multiline_comment|/* Put the TCEs in the HW table */
id|ppc_md
dot
id|tce_build
c_func
(paren
id|tbl
comma
id|entry
comma
id|npages
comma
(paren
r_int
r_int
)paren
id|page
op_amp
id|PAGE_MASK
comma
id|direction
)paren
suffix:semicolon
multiline_comment|/* Flush/invalidate TLB caches if necessary */
r_if
c_cond
(paren
id|ppc_md.tce_flush
)paren
id|ppc_md
dot
id|tce_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Make sure updates are seen by hardware */
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__iommu_free
r_static
r_void
id|__iommu_free
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
id|dma_addr_t
id|dma_addr
comma
r_int
r_int
id|npages
)paren
(brace
r_int
r_int
id|entry
comma
id|free_entry
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|entry
op_assign
id|dma_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|free_entry
op_assign
id|entry
op_minus
id|tbl-&gt;it_offset
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|free_entry
op_plus
id|npages
)paren
OG
id|tbl-&gt;it_mapsize
)paren
op_logical_or
(paren
id|entry
OL
id|tbl-&gt;it_offset
)paren
)paren
(brace
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;iommu_free: invalid entry&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tentry     = 0x%lx&bslash;n&quot;
comma
id|entry
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tdma_addr  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|dma_addr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tTable     = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tbus#      = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_busno
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tmapsize   = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_mapsize
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tstartOff  = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_offset
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;tindex     = 0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|tbl-&gt;it_index
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|ppc_md
dot
id|tce_free
c_func
(paren
id|tbl
comma
id|entry
comma
id|npages
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
id|npages
suffix:semicolon
id|i
op_increment
)paren
id|__clear_bit
c_func
(paren
id|free_entry
op_plus
id|i
comma
id|tbl-&gt;it_map
)paren
suffix:semicolon
)brace
DECL|function|iommu_free
r_static
r_void
id|iommu_free
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
id|dma_addr_t
id|dma_addr
comma
r_int
r_int
id|npages
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|__iommu_free
c_func
(paren
id|tbl
comma
id|dma_addr
comma
id|npages
)paren
suffix:semicolon
multiline_comment|/* Make sure TLB cache is flushed if the HW needs it. We do&n;&t; * not do an mb() here on purpose, it is not needed on any of&n;&t; * the current platforms.&n;&t; */
r_if
c_cond
(paren
id|ppc_md.tce_flush
)paren
id|ppc_md
dot
id|tce_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iommu_map_sg
r_int
id|iommu_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|iommu_table
op_star
id|tbl
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
id|dma_addr_t
id|dma_next
comma
id|dma_addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|scatterlist
op_star
id|s
comma
op_star
id|outs
comma
op_star
id|segstart
suffix:semicolon
r_int
id|outcount
suffix:semicolon
r_int
r_int
id|handle
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nelems
op_eq
l_int|0
)paren
op_logical_or
op_logical_neg
id|tbl
)paren
r_return
l_int|0
suffix:semicolon
id|outs
op_assign
id|s
op_assign
id|segstart
op_assign
op_amp
id|sglist
(braket
l_int|0
)braket
suffix:semicolon
id|outcount
op_assign
l_int|1
suffix:semicolon
id|handle
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Init first segment length for backout at failure */
id|outs-&gt;dma_length
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;mapping %d elements:&bslash;n&quot;
comma
id|nelems
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|outs
suffix:semicolon
id|nelems
suffix:semicolon
id|nelems
op_decrement
comma
id|s
op_increment
)paren
(brace
r_int
r_int
id|vaddr
comma
id|npages
comma
id|entry
comma
id|slen
suffix:semicolon
id|slen
op_assign
id|s-&gt;length
suffix:semicolon
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|slen
op_eq
l_int|0
)paren
(brace
id|dma_next
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Allocate iommu entries for that segment */
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|s-&gt;page
)paren
op_plus
id|s-&gt;offset
suffix:semicolon
id|npages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|vaddr
op_plus
id|slen
)paren
op_minus
(paren
id|vaddr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|npages
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|entry
op_assign
id|iommu_range_alloc
c_func
(paren
id|tbl
comma
id|npages
comma
op_amp
id|handle
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  - vaddr: %lx, size: %lx&bslash;n&quot;
comma
id|vaddr
comma
id|slen
)paren
suffix:semicolon
multiline_comment|/* Handle failure */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|entry
op_eq
id|DMA_ERROR_CODE
)paren
)paren
(brace
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;iommu_alloc failed, tbl %p vaddr %lx&quot;
l_string|&quot; npages %lx&bslash;n&quot;
comma
id|tbl
comma
id|vaddr
comma
id|npages
)paren
suffix:semicolon
r_goto
id|failure
suffix:semicolon
)brace
multiline_comment|/* Convert entry to a dma_addr_t */
id|entry
op_add_assign
id|tbl-&gt;it_offset
suffix:semicolon
id|dma_addr
op_assign
id|entry
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|dma_addr
op_or_assign
id|s-&gt;offset
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  - %lx pages, entry: %lx, dma_addr: %lx&bslash;n&quot;
comma
id|npages
comma
id|entry
comma
id|dma_addr
)paren
suffix:semicolon
multiline_comment|/* Insert into HW table */
id|ppc_md
dot
id|tce_build
c_func
(paren
id|tbl
comma
id|entry
comma
id|npages
comma
id|vaddr
op_amp
id|PAGE_MASK
comma
id|direction
)paren
suffix:semicolon
multiline_comment|/* If we are in an open segment, try merging */
r_if
c_cond
(paren
id|segstart
op_ne
id|s
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;  - trying merge...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* We cannot merge if:&n;&t;&t;&t; * - allocated dma_addr isn&squot;t contiguous to previous allocation&n;&t;&t;&t; */
r_if
c_cond
(paren
id|novmerge
op_logical_or
(paren
id|dma_addr
op_ne
id|dma_next
)paren
)paren
(brace
multiline_comment|/* Can&squot;t merge: create a new segment */
id|segstart
op_assign
id|s
suffix:semicolon
id|outcount
op_increment
suffix:semicolon
id|outs
op_increment
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;    can&squot;t merge, new segment.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|outs-&gt;dma_length
op_add_assign
id|s-&gt;length
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;    merged, new len: %lx&bslash;n&quot;
comma
id|outs-&gt;dma_length
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|segstart
op_eq
id|s
)paren
(brace
multiline_comment|/* This is a new segment, fill entries */
id|DBG
c_func
(paren
l_string|&quot;  - filling new segment.&bslash;n&quot;
)paren
suffix:semicolon
id|outs-&gt;dma_address
op_assign
id|dma_addr
suffix:semicolon
id|outs-&gt;dma_length
op_assign
id|slen
suffix:semicolon
)brace
multiline_comment|/* Calculate next page pointer for contiguous check */
id|dma_next
op_assign
id|dma_addr
op_plus
id|slen
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;  - dma next is: %lx&bslash;n&quot;
comma
id|dma_next
)paren
suffix:semicolon
)brace
multiline_comment|/* Flush/invalidate TLB caches if necessary */
r_if
c_cond
(paren
id|ppc_md.tce_flush
)paren
id|ppc_md
dot
id|tce_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Make sure updates are seen by hardware */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;mapped %d elements:&bslash;n&quot;
comma
id|outcount
)paren
suffix:semicolon
multiline_comment|/* For the sake of iommu_free_sg, we clear out the length in the&n;&t; * next entry of the sglist if we didn&squot;t fill the list completely&n;&t; */
r_if
c_cond
(paren
id|outcount
OL
id|nelems
)paren
(brace
id|outs
op_increment
suffix:semicolon
id|outs-&gt;dma_address
op_assign
id|DMA_ERROR_CODE
suffix:semicolon
id|outs-&gt;dma_length
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|outcount
suffix:semicolon
id|failure
suffix:colon
r_for
c_loop
(paren
id|s
op_assign
op_amp
id|sglist
(braket
l_int|0
)braket
suffix:semicolon
id|s
op_le
id|outs
suffix:semicolon
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;dma_length
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|vaddr
comma
id|npages
suffix:semicolon
id|vaddr
op_assign
id|s-&gt;dma_address
op_amp
id|PAGE_MASK
suffix:semicolon
id|npages
op_assign
(paren
id|PAGE_ALIGN
c_func
(paren
id|s-&gt;dma_address
op_plus
id|s-&gt;dma_length
)paren
op_minus
id|vaddr
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|__iommu_free
c_func
(paren
id|tbl
comma
id|vaddr
comma
id|npages
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iommu_unmap_sg
r_void
id|iommu_unmap_sg
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tbl
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nelems
op_decrement
)paren
(brace
r_int
r_int
id|npages
suffix:semicolon
id|dma_addr_t
id|dma_handle
op_assign
id|sglist-&gt;dma_address
suffix:semicolon
r_if
c_cond
(paren
id|sglist-&gt;dma_length
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|npages
op_assign
(paren
id|PAGE_ALIGN
c_func
(paren
id|dma_handle
op_plus
id|sglist-&gt;dma_length
)paren
op_minus
(paren
id|dma_handle
op_amp
id|PAGE_MASK
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|__iommu_free
c_func
(paren
id|tbl
comma
id|dma_handle
comma
id|npages
)paren
suffix:semicolon
id|sglist
op_increment
suffix:semicolon
)brace
multiline_comment|/* Flush/invalidate TLBs if necessary. As for iommu_free(), we&n;&t; * do not do an mb() here, the affected platforms do not need it&n;&t; * when freeing.&n;&t; */
r_if
c_cond
(paren
id|ppc_md.tce_flush
)paren
id|ppc_md
dot
id|tce_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|tbl-&gt;it_lock
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Build a iommu_table structure.  This contains a bit map which&n; * is used to manage allocation of the tce space.&n; */
DECL|function|iommu_init_table
r_struct
id|iommu_table
op_star
id|iommu_init_table
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
)paren
(brace
r_int
r_int
id|sz
suffix:semicolon
r_static
r_int
id|welcomed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* it_size is in pages, it_mapsize in number of entries */
id|tbl-&gt;it_mapsize
op_assign
(paren
id|tbl-&gt;it_size
op_lshift
id|PAGE_SHIFT
)paren
op_div
id|tbl-&gt;it_entrysize
suffix:semicolon
multiline_comment|/* Set aside 1/4 of the table for large allocations. */
id|tbl-&gt;it_halfpoint
op_assign
id|tbl-&gt;it_mapsize
op_star
l_int|3
op_div
l_int|4
suffix:semicolon
multiline_comment|/* number of bytes needed for the bitmap */
id|sz
op_assign
(paren
id|tbl-&gt;it_mapsize
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
id|tbl-&gt;it_map
op_assign
(paren
r_int
r_int
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|get_order
c_func
(paren
id|sz
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tbl-&gt;it_map
)paren
id|panic
c_func
(paren
l_string|&quot;iommu_init_table: Can&squot;t allocate %ld bytes&bslash;n&quot;
comma
id|sz
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tbl-&gt;it_map
comma
l_int|0
comma
id|sz
)paren
suffix:semicolon
id|tbl-&gt;it_hint
op_assign
l_int|0
suffix:semicolon
id|tbl-&gt;it_largehint
op_assign
id|tbl-&gt;it_halfpoint
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|tbl-&gt;it_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|welcomed
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IOMMU table initialized, virtual merging %s&bslash;n&quot;
comma
id|novmerge
ques
c_cond
l_string|&quot;disabled&quot;
suffix:colon
l_string|&quot;enabled&quot;
)paren
suffix:semicolon
id|welcomed
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|tbl
suffix:semicolon
)brace
multiline_comment|/* Creates TCEs for a user provided buffer.  The user buffer must be&n; * contiguous real kernel storage (not vmalloc).  The address of the buffer&n; * passed here is the kernel (virtual) address of the buffer.  The buffer&n; * need not be page aligned, the dma_addr_t returned will point to the same&n; * byte within the page as vaddr.&n; */
DECL|function|iommu_map_single
id|dma_addr_t
id|iommu_map_single
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
id|dma_addr_t
id|dma_handle
op_assign
id|DMA_ERROR_CODE
suffix:semicolon
r_int
r_int
id|uaddr
suffix:semicolon
r_int
r_int
id|npages
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|uaddr
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
id|npages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|uaddr
op_plus
id|size
)paren
op_minus
(paren
id|uaddr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|npages
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
id|dma_handle
op_assign
id|iommu_alloc
c_func
(paren
id|tbl
comma
id|vaddr
comma
id|npages
comma
id|direction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_handle
op_eq
id|DMA_ERROR_CODE
)paren
(brace
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;iommu_alloc failed, &quot;
l_string|&quot;tbl %p vaddr %p npages %d&bslash;n&quot;
comma
id|tbl
comma
id|vaddr
comma
id|npages
)paren
suffix:semicolon
)brace
)brace
r_else
id|dma_handle
op_or_assign
(paren
id|uaddr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
r_return
id|dma_handle
suffix:semicolon
)brace
DECL|function|iommu_unmap_single
r_void
id|iommu_unmap_single
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
id|iommu_free
c_func
(paren
id|tbl
comma
id|dma_handle
comma
(paren
id|PAGE_ALIGN
c_func
(paren
id|dma_handle
op_plus
id|size
)paren
op_minus
(paren
id|dma_handle
op_amp
id|PAGE_MASK
)paren
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocates a contiguous real buffer and creates mappings over it.&n; * Returns the virtual address of the buffer and sets dma_handle&n; * to the dma address (mapping) of the first page.&n; */
DECL|function|iommu_alloc_consistent
r_void
op_star
id|iommu_alloc_consistent
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
(brace
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|dma_addr_t
id|mapping
suffix:semicolon
r_int
r_int
id|npages
comma
id|order
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|npages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Client asked for way too much space.  This is checked later&n;&t; * anyway.  It is easier to debug here for the drivers than in&n;&t; * the tce tables.&n;&t; */
r_if
c_cond
(paren
id|order
op_ge
id|IOMAP_MAX_ORDER
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iommu_alloc_consistent size too large: 0x%lx&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tbl
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Alloc enough pages (and possibly more) */
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Set up tces to cover the allocated range */
id|mapping
op_assign
id|iommu_alloc
c_func
(paren
id|tbl
comma
id|ret
comma
id|npages
comma
id|DMA_BIDIRECTIONAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapping
op_eq
id|DMA_ERROR_CODE
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|ret
comma
id|order
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
op_star
id|dma_handle
op_assign
id|mapping
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|iommu_free_consistent
r_void
id|iommu_free_consistent
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_int
r_int
id|npages
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|npages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_free
c_func
(paren
id|tbl
comma
id|dma_handle
comma
id|npages
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
)brace
eof
