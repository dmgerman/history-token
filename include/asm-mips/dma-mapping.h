macro_line|#ifndef _ASM_DMA_MAPPING_H
DECL|macro|_ASM_DMA_MAPPING_H
mdefine_line|#define _ASM_DMA_MAPPING_H
macro_line|#include &lt;asm/cache.h&gt;
DECL|macro|dma_alloc_noncoherent
mdefine_line|#define dma_alloc_noncoherent(d, s, h, f) dma_alloc_coherent(d, s, h, f)
DECL|macro|dma_free_noncoherent
mdefine_line|#define dma_free_noncoherent(d, s, v, h) dma_free_coherent(d, s, v, h)
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
macro_line|#ifdef CONFIG_MAPPED_DMA_IO
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#else
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
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_return
id|bus_to_baddr
c_func
(paren
id|hwdev-&gt;bus
comma
id|__pa
c_func
(paren
id|ptr
)paren
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
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|DMA_TO_DEVICE
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
id|baddr_to_bus
c_func
(paren
id|hwdev-&gt;bus
comma
id|dma_addr
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|dma_cache_wback_inv
c_func
(paren
id|addr
op_plus
id|sg-&gt;offset
comma
id|sg-&gt;length
)paren
suffix:semicolon
id|sg-&gt;dma_address
op_assign
(paren
id|dma_addr_t
)paren
id|bus_to_baddr
c_func
(paren
id|hwdev-&gt;bus
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
r_int
r_int
id|addr
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|addr
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
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_return
id|bus_to_baddr
c_func
(paren
id|hwdev-&gt;bus
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
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|DMA_TO_DEVICE
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
id|baddr_to_bus
c_func
(paren
id|hwdev-&gt;bus
comma
id|dma_address
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_TO_DEVICE
)paren
r_return
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
id|nhwentries
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|sg-&gt;page
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|dma_cache_wback_inv
c_func
(paren
id|addr
op_plus
id|sg-&gt;offset
comma
id|sg-&gt;length
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|addr
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|addr
op_assign
id|baddr_to_bus
c_func
(paren
id|hwdev-&gt;bus
comma
id|dma_handle
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
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
r_int
r_int
id|addr
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|addr
op_assign
id|baddr_to_bus
c_func
(paren
id|hwdev-&gt;bus
comma
id|dma_handle
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|size
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
macro_line|#ifdef CONFIG_NONCOHERENT_IO
r_int
id|i
suffix:semicolon
macro_line|#endif
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
multiline_comment|/* Make sure that gcc doesn&squot;t leave the empty loop body.  */
macro_line|#ifdef CONFIG_NONCOHERENT_IO
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nelems
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
comma
id|sg-&gt;length
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_MAPPED_DMA_IO  */
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
macro_line|#ifdef CONFIG_NONCOHERENT_IO
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(d)&t;(0)
macro_line|#else
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(d)&t;(1)
macro_line|#endif
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
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_DMA_MAPPING_H */
eof
