macro_line|#ifndef _ASM_DMA_MAPPING_H
DECL|macro|_ASM_DMA_MAPPING_H
mdefine_line|#define _ASM_DMA_MAPPING_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
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
id|flag
)paren
suffix:semicolon
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
id|flag
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|dma_sync_single_for_cpu
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
suffix:semicolon
r_extern
r_void
id|dma_sync_single_for_device
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
suffix:semicolon
r_extern
r_void
id|dma_sync_single_range_for_cpu
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
suffix:semicolon
r_extern
r_void
id|dma_sync_single_range_for_device
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
suffix:semicolon
r_extern
r_void
id|dma_sync_sg_for_cpu
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
suffix:semicolon
r_extern
r_void
id|dma_sync_sg_for_device
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
suffix:semicolon
r_extern
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
suffix:semicolon
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
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dma_mask
op_logical_or
op_logical_neg
id|dma_supported
c_func
(paren
id|dev
comma
id|mask
)paren
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
op_star
id|dev-&gt;dma_mask
op_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/* XXX Largest on any MIPS */
r_return
l_int|128
suffix:semicolon
)brace
r_extern
r_int
id|dma_is_consistent
c_func
(paren
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#endif /* _ASM_DMA_MAPPING_H */
eof
