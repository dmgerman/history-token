macro_line|#ifndef _ALPHA_DMA_MAPPING_H
DECL|macro|_ALPHA_DMA_MAPPING_H
mdefine_line|#define _ALPHA_DMA_MAPPING_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|dma_map_single
mdefine_line|#define dma_map_single(dev, va, size, dir)&t;&t;&bslash;&n;&t;&t;pci_map_single(alpha_gendev_to_pci(dev), va, size, dir)
DECL|macro|dma_unmap_single
mdefine_line|#define dma_unmap_single(dev, addr, size, dir)&t;&t;&bslash;&n;&t;&t;pci_unmap_single(alpha_gendev_to_pci(dev), addr, size, dir)
DECL|macro|dma_alloc_coherent
mdefine_line|#define dma_alloc_coherent(dev, size, addr, gfp)&t;&bslash;&n;&t;&t;pci_alloc_consistent(alpha_gendev_to_pci(dev), size, addr)
DECL|macro|dma_free_coherent
mdefine_line|#define dma_free_coherent(dev, size, va, addr)&t;&t;&bslash;&n;&t;&t;pci_free_consistent(alpha_gendev_to_pci(dev), size, va, addr)
DECL|macro|dma_map_page
mdefine_line|#define dma_map_page(dev, page, off, size, dir)&t;&t;&bslash;&n;&t;&t;pci_map_single(alpha_gendev_to_pci(dev), page, off, size, dir)
DECL|macro|dma_unmap_page
mdefine_line|#define dma_unmap_page(dev, addr, size, dir)&t;&t;&bslash;&n;&t;&t;pci_unmap_page(alpha_gendev_to_pci(dev), addr, size, dir)
DECL|macro|dma_map_sg
mdefine_line|#define dma_map_sg(dev, sg, nents, dir)&t;&t;&t;&bslash;&n;&t;&t;pci_map_sg(alpha_gendev_to_pci(dev), sg, nents, dir)
DECL|macro|dma_unmap_sg
mdefine_line|#define dma_unmap_sg(dev, sg, nents, dir)&t;&t;&bslash;&n;&t;&t;pci_unmap_sg(alpha_gendev_to_pci(dev), sg, nents, dir)
DECL|macro|dma_supported
mdefine_line|#define dma_supported(dev, mask)&t;&t;&t;&bslash;&n;&t;&t;pci_dma_supported(alpha_gendev_to_pci(dev), mask)
DECL|macro|dma_mapping_error
mdefine_line|#define dma_mapping_error(addr)&t;&t;&t;&t;&bslash;&n;&t;&t;pci_dma_mapping_error(addr)
macro_line|#else&t;/* no PCI - no IOMMU. */
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
suffix:semicolon
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
suffix:semicolon
DECL|macro|dma_free_coherent
mdefine_line|#define dma_free_coherent(dev, size, va, addr)&t;&t;&bslash;&n;&t;&t;free_pages((unsigned long)va, get_order(size))
DECL|macro|dma_supported
mdefine_line|#define dma_supported(dev, mask)&t;&t;(mask &lt; 0x00ffffffUL ? 0 : 1)
DECL|macro|dma_map_single
mdefine_line|#define dma_map_single(dev, va, size, dir)&t;virt_to_phys(va)
DECL|macro|dma_map_page
mdefine_line|#define dma_map_page(dev, page, off, size, dir)&t;(page_to_pa(page) + off)
DECL|macro|dma_unmap_single
mdefine_line|#define dma_unmap_single(dev, addr, size, dir)&t;do { } while (0)
DECL|macro|dma_unmap_page
mdefine_line|#define dma_unmap_page(dev, addr, size, dir)&t;do { } while (0)
DECL|macro|dma_unmap_sg
mdefine_line|#define dma_unmap_sg(dev, sg, nents, dir)&t;do { } while (0)
DECL|macro|dma_mapping_error
mdefine_line|#define dma_mapping_error(addr)  (0)
macro_line|#endif&t;/* !CONFIG_PCI */
DECL|macro|dma_alloc_noncoherent
mdefine_line|#define dma_alloc_noncoherent(d, s, h, f)&t;dma_alloc_coherent(d, s, h, f)
DECL|macro|dma_free_noncoherent
mdefine_line|#define dma_free_noncoherent(d, s, v, h)&t;dma_free_coherent(d, s, v, h)
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(dev)&t;&t;&t;(1)
r_int
id|dma_set_mask
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
suffix:semicolon
DECL|macro|dma_sync_single_for_cpu
mdefine_line|#define dma_sync_single_for_cpu(dev, addr, size, dir)&t;  do { } while (0)
DECL|macro|dma_sync_single_for_device
mdefine_line|#define dma_sync_single_for_device(dev, addr, size, dir)  do { } while (0)
DECL|macro|dma_sync_single_range
mdefine_line|#define dma_sync_single_range(dev, addr, off, size, dir)  do { } while (0)
DECL|macro|dma_sync_sg_for_cpu
mdefine_line|#define dma_sync_sg_for_cpu(dev, sg, nents, dir)&t;  do { } while (0)
DECL|macro|dma_sync_sg_for_device
mdefine_line|#define dma_sync_sg_for_device(dev, sg, nents, dir)&t;  do { } while (0)
DECL|macro|dma_cache_sync
mdefine_line|#define dma_cache_sync(va, size, dir)&t;&t;&t;  do { } while (0)
DECL|macro|dma_get_cache_alignment
mdefine_line|#define dma_get_cache_alignment()&t;&t;&t;  L1_CACHE_BYTES
macro_line|#endif&t;/* _ALPHA_DMA_MAPPING_H */
eof
