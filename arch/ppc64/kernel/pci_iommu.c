multiline_comment|/*&n; * arch/ppc64/kernel/pci_iommu.c&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; * &n; * Rewrite, cleanup, new allocation schemes: &n; * Copyright (C) 2004 Olof Johansson, IBM Corporation&n; *&n; * Dynamic DMA mapping support, platform-independent parts.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;pci.h&quot;
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#endif /* CONFIG_PPC_ISERIES */
DECL|macro|DBG
mdefine_line|#define DBG(...)
DECL|function|devnode_table
r_static
r_inline
r_struct
id|iommu_table
op_star
id|devnode_table
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
id|dev
op_assign
id|ppc64_isabridge_dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
r_return
id|ISERIES_DEVNODE
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|iommu_table
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#ifdef CONFIG_PPC_PSERIES
r_return
id|PCI_GET_DN
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|iommu_table
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_PSERIES */
)brace
multiline_comment|/* Allocates a contiguous real buffer and creates mappings over it.&n; * Returns the virtual address of the buffer and sets dma_handle&n; * to the dma address (mapping) of the first page.&n; */
DECL|function|pci_iommu_alloc_consistent
r_void
op_star
id|pci_iommu_alloc_consistent
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
id|dma_handle
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
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
multiline_comment|/* Client asked for way too much space.  This is checked later anyway */
multiline_comment|/* It is easier to debug here for the drivers than in the tce tables.*/
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
l_string|&quot;PCI_DMA: pci_alloc_consistent size too large: 0x%lx&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|DMA_ERROR_CODE
suffix:semicolon
)brace
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|hwdev
)paren
suffix:semicolon
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
id|PCI_DMA_BIDIRECTIONAL
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
DECL|function|pci_iommu_free_consistent
r_void
id|pci_iommu_free_consistent
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
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
r_int
r_int
id|npages
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
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|hwdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbl
)paren
(brace
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
multiline_comment|/* Creates TCEs for a user provided buffer.  The user buffer must be &n; * contiguous real kernel storage (not vmalloc).  The address of the buffer&n; * passed here is the kernel (virtual) address of the buffer.  The buffer&n; * need not be page aligned, the dma_addr_t returned will point to the same&n; * byte within the page as vaddr.&n; */
DECL|function|pci_iommu_map_single
id|dma_addr_t
id|pci_iommu_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
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
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
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
id|PCI_DMA_NONE
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
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|hwdev
)paren
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
l_string|&quot;iommu_alloc failed, tbl %p vaddr %p npages %d&bslash;n&quot;
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
DECL|function|pci_iommu_unmap_single
r_void
id|pci_iommu_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
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
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|npages
op_assign
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
suffix:semicolon
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|hwdev
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
id|npages
)paren
suffix:semicolon
)brace
DECL|function|pci_iommu_map_sg
r_int
id|pci_iommu_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_int
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nelems
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tbl
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|iommu_alloc_sg
c_func
(paren
id|tbl
comma
op_amp
id|pdev-&gt;dev
comma
id|sglist
comma
id|nelems
comma
id|direction
)paren
suffix:semicolon
)brace
DECL|function|pci_iommu_unmap_sg
r_void
id|pci_iommu_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_int
id|direction
)paren
(brace
r_struct
id|iommu_table
op_star
id|tbl
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|tbl
op_assign
id|devnode_table
c_func
(paren
id|pdev
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
id|iommu_free_sg
c_func
(paren
id|tbl
comma
id|sglist
comma
id|nelems
)paren
suffix:semicolon
)brace
multiline_comment|/* We support DMA to/from any memory page via the iommu */
DECL|function|pci_iommu_dma_supported
r_static
r_int
id|pci_iommu_dma_supported
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|u64
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pci_iommu_init
r_void
id|pci_iommu_init
c_func
(paren
r_void
)paren
(brace
id|pci_dma_ops.pci_alloc_consistent
op_assign
id|pci_iommu_alloc_consistent
suffix:semicolon
id|pci_dma_ops.pci_free_consistent
op_assign
id|pci_iommu_free_consistent
suffix:semicolon
id|pci_dma_ops.pci_map_single
op_assign
id|pci_iommu_map_single
suffix:semicolon
id|pci_dma_ops.pci_unmap_single
op_assign
id|pci_iommu_unmap_single
suffix:semicolon
id|pci_dma_ops.pci_map_sg
op_assign
id|pci_iommu_map_sg
suffix:semicolon
id|pci_dma_ops.pci_unmap_sg
op_assign
id|pci_iommu_unmap_sg
suffix:semicolon
id|pci_dma_ops.pci_dma_supported
op_assign
id|pci_iommu_dma_supported
suffix:semicolon
)brace
eof
