multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000  Ani Joshi &lt;ajoshi@unixbox.com&gt;&n; * Copyright (C) 2000, 2001  Ralf Baechle &lt;ralf@gnu.org&gt;&n; * swiped from i386, and cloned for MIPS by Geert, polished by Ralf.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/pci/bridge.h&gt;
DECL|macro|pdev_to_baddr
mdefine_line|#define pdev_to_baddr(pdev, addr) &bslash;&n;&t;(BRIDGE_CONTROLLER(pdev-&gt;bus)-&gt;baddr + (addr))
DECL|macro|dev_to_baddr
mdefine_line|#define dev_to_baddr(dev, addr) &bslash;&n;&t;pdev_to_baddr(to_pci_dev(dev), (addr))
DECL|function|dma_alloc_noncoherent
r_void
op_star
id|dma_alloc_noncoherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
comma
r_int
id|gfp
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
multiline_comment|/* ignore region specifiers */
id|gfp
op_and_assign
op_complement
(paren
id|__GFP_DMA
op_or
id|__GFP_HIGHMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
op_logical_or
(paren
op_star
id|dev-&gt;dma_mask
OL
l_int|0xffffffff
)paren
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|gfp
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
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
op_star
id|dma_handle
op_assign
id|dev_to_baddr
c_func
(paren
id|dev
comma
id|virt_to_phys
c_func
(paren
id|ret
)paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dma_alloc_noncoherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_alloc_noncoherent
)paren
suffix:semicolon
r_void
op_star
id|dma_alloc_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
comma
r_int
id|gfp
)paren
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;dma_alloc_noncoherent&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|dma_alloc_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_alloc_coherent
)paren
suffix:semicolon
DECL|function|dma_free_noncoherent
r_void
id|dma_free_noncoherent
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|addr
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
id|free_pages
c_func
(paren
id|addr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
DECL|variable|dma_free_noncoherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_free_noncoherent
)paren
suffix:semicolon
r_void
id|dma_free_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|__attribute__
c_func
(paren
(paren
id|alias
c_func
(paren
l_string|&quot;dma_free_noncoherent&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|dma_free_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_free_coherent
)paren
suffix:semicolon
DECL|function|dma_map_single
id|dma_addr_t
id|dma_map_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|ptr
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
r_return
id|dev_to_baddr
c_func
(paren
id|dev
comma
id|__pa
c_func
(paren
id|ptr
)paren
)paren
suffix:semicolon
)brace
DECL|variable|dma_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|dma_map_single
)paren
suffix:semicolon
DECL|function|dma_unmap_single
r_void
id|dma_unmap_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_addr
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
)brace
DECL|variable|dma_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|dma_unmap_single
)paren
suffix:semicolon
DECL|function|dma_map_sg
r_int
id|dma_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
id|sg-&gt;dma_address
op_assign
(paren
id|dma_addr_t
)paren
id|dev_to_baddr
c_func
(paren
id|dev
comma
id|page_to_phys
c_func
(paren
id|sg-&gt;page
)paren
op_plus
id|sg-&gt;offset
)paren
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
DECL|variable|dma_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|dma_map_sg
)paren
suffix:semicolon
DECL|function|dma_map_page
id|dma_addr_t
id|dma_map_page
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
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
r_return
id|dev_to_baddr
c_func
(paren
id|dev
comma
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|variable|dma_map_page
id|EXPORT_SYMBOL
c_func
(paren
id|dma_map_page
)paren
suffix:semicolon
DECL|function|dma_unmap_page
r_void
id|dma_unmap_page
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_address
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
)brace
DECL|variable|dma_unmap_page
id|EXPORT_SYMBOL
c_func
(paren
id|dma_unmap_page
)paren
suffix:semicolon
DECL|function|dma_unmap_sg
r_void
id|dma_unmap_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nhwentries
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
)brace
DECL|variable|dma_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|dma_unmap_sg
)paren
suffix:semicolon
DECL|function|dma_sync_single
r_void
id|dma_sync_single
c_func
(paren
r_struct
id|device
op_star
id|dev
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
)brace
DECL|variable|dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|dma_sync_single
)paren
suffix:semicolon
DECL|function|dma_sync_single_range
r_void
id|dma_sync_single_range
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
r_int
id|offset
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
)brace
DECL|variable|dma_sync_single_range
id|EXPORT_SYMBOL
c_func
(paren
id|dma_sync_single_range
)paren
suffix:semicolon
DECL|function|dma_sync_sg
r_void
id|dma_sync_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nelems
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
)brace
DECL|variable|dma_sync_sg
id|EXPORT_SYMBOL
c_func
(paren
id|dma_sync_sg
)paren
suffix:semicolon
DECL|function|dma_supported
r_int
id|dma_supported
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
multiline_comment|/*&n;&t; * we fall back to GFP_DMA when the mask isn&squot;t all 1s,&n;&t; * so we can&squot;t guarantee allocations that must be&n;&t; * within a tighter range than GFP_DMA..&n;&t; */
r_if
c_cond
(paren
id|mask
OL
l_int|0x00ffffff
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|dma_supported
)paren
suffix:semicolon
DECL|function|dma_is_consistent
r_int
id|dma_is_consistent
c_func
(paren
id|dma_addr_t
id|dma_addr
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|dma_is_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_is_consistent
)paren
suffix:semicolon
DECL|function|dma_cache_sync
r_void
id|dma_cache_sync
c_func
(paren
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
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
)brace
DECL|variable|dma_cache_sync
id|EXPORT_SYMBOL
c_func
(paren
id|dma_cache_sync
)paren
suffix:semicolon
DECL|function|pci_dac_page_to_dma
id|dma64_addr_t
id|pci_dac_page_to_dma
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
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
id|direction
)paren
(brace
id|dma64_addr_t
id|addr
op_assign
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
r_return
(paren
id|dma64_addr_t
)paren
id|pdev_to_baddr
c_func
(paren
id|pdev
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|variable|dma_cache_sync
id|EXPORT_SYMBOL
c_func
(paren
id|dma_cache_sync
)paren
suffix:semicolon
DECL|function|pci_dac_dma_to_page
r_struct
id|page
op_star
id|pci_dac_dma_to_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
)paren
(brace
r_struct
id|bridge_controller
op_star
id|bc
op_assign
id|BRIDGE_CONTROLLER
c_func
(paren
id|pdev-&gt;bus
)paren
suffix:semicolon
r_return
id|pfn_to_page
c_func
(paren
(paren
id|dma_addr
op_minus
id|bc-&gt;baddr
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|variable|pci_dac_dma_to_page
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_to_page
)paren
suffix:semicolon
DECL|function|pci_dac_dma_to_offset
r_int
r_int
id|pci_dac_dma_to_offset
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
)paren
(brace
r_return
id|dma_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
)brace
DECL|variable|pci_dac_dma_to_offset
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_to_offset
)paren
suffix:semicolon
DECL|function|pci_dac_dma_sync_single
r_void
id|pci_dac_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
comma
r_int
id|len
comma
r_int
id|direction
)paren
(brace
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
)brace
DECL|variable|pci_dac_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_sync_single
)paren
suffix:semicolon
eof
