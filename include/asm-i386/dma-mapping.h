macro_line|#ifndef _ASM_I386_DMA_MAPPING_H
DECL|macro|_ASM_I386_DMA_MAPPING_H
mdefine_line|#define _ASM_I386_DMA_MAPPING_H
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
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
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
r_return
id|virt_to_phys
c_func
(paren
id|ptr
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
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|sg
(braket
id|i
)braket
dot
id|page
)paren
suffix:semicolon
id|sg
(braket
id|i
)braket
dot
id|dma_address
op_assign
id|page_to_phys
c_func
(paren
id|sg
(braket
id|i
)braket
dot
id|page
)paren
op_plus
id|sg
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
)brace
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
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
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
r_return
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
id|offset
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
id|direction
op_eq
id|DMA_NONE
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single_for_cpu
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
(brace
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single_for_device
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
(brace
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single_range_for_cpu
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
(brace
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_single_range_for_device
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
(brace
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_sg_for_cpu
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
(brace
)brace
r_static
r_inline
r_void
DECL|function|dma_sync_sg_for_device
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
(brace
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dma_mapping_error
id|dma_mapping_error
c_func
(paren
id|dma_addr_t
id|dma_addr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/*&n;         * we fall back to GFP_DMA when the mask isn&squot;t all 1s,&n;         * so we can&squot;t guarantee allocations that must be&n;         * within a tighter range than GFP_DMA..&n;         */
r_if
c_cond
(paren
id|mask
OL
l_int|0x00ffffff
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/* no easy way to get cache size on all x86, so return the&n;&t; * maximum possible, to be safe */
r_return
(paren
l_int|1
op_lshift
id|L1_CACHE_SHIFT_MAX
)paren
suffix:semicolon
)brace
DECL|macro|dma_is_consistent
mdefine_line|#define dma_is_consistent(d)&t;(1)
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
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
