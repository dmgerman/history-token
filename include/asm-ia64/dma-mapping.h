macro_line|#ifndef _ASM_IA64_DMA_MAPPING_H
DECL|macro|_ASM_IA64_DMA_MAPPING_H
mdefine_line|#define _ASM_IA64_DMA_MAPPING_H
multiline_comment|/*&n; * Copyright (C) 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|dma_alloc_coherent
mdefine_line|#define dma_alloc_coherent&t;platform_dma_alloc_coherent
DECL|macro|dma_alloc_noncoherent
mdefine_line|#define dma_alloc_noncoherent&t;platform_dma_alloc_coherent&t;/* coherent mem. is cheap */
DECL|macro|dma_free_coherent
mdefine_line|#define dma_free_coherent&t;platform_dma_free_coherent
DECL|macro|dma_free_noncoherent
mdefine_line|#define dma_free_noncoherent&t;platform_dma_free_coherent
DECL|macro|dma_map_single
mdefine_line|#define dma_map_single&t;&t;platform_dma_map_single
DECL|macro|dma_map_sg
mdefine_line|#define dma_map_sg&t;&t;platform_dma_map_sg
DECL|macro|dma_unmap_single
mdefine_line|#define dma_unmap_single&t;platform_dma_unmap_single
DECL|macro|dma_unmap_sg
mdefine_line|#define dma_unmap_sg&t;&t;platform_dma_unmap_sg
DECL|macro|dma_sync_single
mdefine_line|#define dma_sync_single&t;&t;platform_dma_sync_single
DECL|macro|dma_sync_sg
mdefine_line|#define dma_sync_sg&t;&t;platform_dma_sync_sg
DECL|macro|dma_map_page
mdefine_line|#define dma_map_page(dev, pg, off, size, dir)&t;&t;&t;&t;&bslash;&n;&t;dma_map_single(dev, page_address(pg) + (off), (size), (dir))
DECL|macro|dma_unmap_page
mdefine_line|#define dma_unmap_page(dev, dma_addr, size, dir)&t;&t;&t;&bslash;&n;&t;dma_unmap_single(dev, dma_addr, size, dir)
multiline_comment|/*&n; * Rest of this file is part of the &quot;Advanced DMA API&quot;.  Use at your own risk.&n; * See Documentation/DMA-API.txt for details.&n; */
DECL|macro|dma_sync_single_range
mdefine_line|#define dma_sync_single_range(dev, dma_handle, offset, size, dir)&t;&bslash;&n;&t;dma_sync_single(dev, dma_handle, size, dir)
DECL|macro|dma_supported
mdefine_line|#define dma_supported&t;&t;platform_dma_supported
r_static
r_inline
r_int
DECL|function|dma_set_mask
id|dma_set_mask
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
r_return
op_minus
id|EIO
suffix:semicolon
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
(paren
r_void
)paren
(brace
r_extern
r_int
id|ia64_max_cacheline_size
suffix:semicolon
r_return
id|ia64_max_cacheline_size
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_cache_sync
id|dma_cache_sync
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
id|dir
)paren
(brace
multiline_comment|/*&n;&t; * IA-64 is cache-coherent, so this is mostly a no-op.  However, we do need to&n;&t; * ensure that dma_cache_sync() enforces order, hence the mb().&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(dma_handle)&t;(1)&t;/* all we do is coherent memory... */
macro_line|#endif /* _ASM_IA64_DMA_MAPPING_H */
eof
