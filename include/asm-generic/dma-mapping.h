multiline_comment|/* Copyright (C) 2002 by James.Bottomley@HansenPartnership.com &n; *&n; * Implements the generic device dma API via the existing pci_ one&n; * for unconverted architectures&n; */
macro_line|#ifndef _ASM_GENERIC_DMA_MAPPING_H
DECL|macro|_ASM_GENERIC_DMA_MAPPING_H
mdefine_line|#define _ASM_GENERIC_DMA_MAPPING_H
multiline_comment|/* we implement the API below in terms of the existing PCI one,&n; * so include it */
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* need struct page definitions */
macro_line|#include &lt;linux/mm.h&gt;
r_static
r_inline
r_int
DECL|function|dma_supported
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
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_dma_supported
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|mask
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dma_set_mask
id|dma_set_mask
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u64
id|dma_mask
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_set_dma_mask
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_mask
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|dma_alloc_coherent
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
id|flag
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
op_logical_or
(paren
id|flag
op_amp
id|GFP_ATOMIC
)paren
op_ne
id|GFP_ATOMIC
)paren
suffix:semicolon
r_return
id|pci_alloc_consistent
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_free_coherent
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
id|cpu_addr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|size
comma
id|cpu_addr
comma
id|dma_handle
)paren
suffix:semicolon
)brace
r_static
r_inline
id|dma_addr_t
DECL|function|dma_map_single
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
id|cpu_addr
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_map_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|cpu_addr
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_unmap_single
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_unmap_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_addr
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
id|dma_addr_t
DECL|function|dma_map_page
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_map_page
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|page
comma
id|offset
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_unmap_page
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_unmap_page
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_address
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dma_map_sg
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
id|BUG_ON
c_func
(paren
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
r_return
id|pci_map_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nents
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_unmap_sg
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_unmap_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nhwentries
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_dma_sync_single
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|dma_handle
comma
id|size
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_sg
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
id|dev-&gt;bus
op_ne
op_amp
id|pci_bus_type
)paren
suffix:semicolon
id|pci_dma_sync_sg
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
comma
id|sg
comma
id|nelems
comma
(paren
r_int
)paren
id|direction
)paren
suffix:semicolon
)brace
multiline_comment|/* Now for the API extensions over the pci_ one */
DECL|macro|dma_alloc_noncoherent
mdefine_line|#define dma_alloc_noncoherent(d, s, h, f) dma_alloc_coherent(d, s, h, f)
DECL|macro|dma_free_noncoherent
mdefine_line|#define dma_free_noncoherent(d, s, v, h) dma_free_coherent(d, s, v, h)
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(d)&t;(1)
r_static
r_inline
r_int
DECL|function|dma_get_cache_alignment
id|dma_get_cache_alignment
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* no easy way to get cache size on all processors, so return&n;&t; * the maximum possible, to be safe */
r_return
(paren
l_int|1
op_lshift
id|L1_CACHE_SHIFT_MAX
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single_range
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
multiline_comment|/* just sync everything, that&squot;s all the pci API can do */
id|dma_sync_single
c_func
(paren
id|dev
comma
id|dma_handle
comma
id|offset
op_plus
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_cache_sync
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
multiline_comment|/* could define this in terms of the dma_cache ... operations,&n;&t; * but if you get this on a platform, you should convert the platform&n;&t; * to using the generic device DMA API */
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
