macro_line|#ifndef _ASM_LINUX_DMA_MAPPING_H
DECL|macro|_ASM_LINUX_DMA_MAPPING_H
mdefine_line|#define _ASM_LINUX_DMA_MAPPING_H
multiline_comment|/* These definitions mirror those in pci.h, so they can be used&n; * interchangeably with their PCI_ counterparts */
DECL|enum|dma_data_direction
r_enum
id|dma_data_direction
(brace
DECL|enumerator|DMA_BIDIRECTIONAL
id|DMA_BIDIRECTIONAL
op_assign
l_int|0
comma
DECL|enumerator|DMA_TO_DEVICE
id|DMA_TO_DEVICE
op_assign
l_int|1
comma
DECL|enumerator|DMA_FROM_DEVICE
id|DMA_FROM_DEVICE
op_assign
l_int|2
comma
DECL|enumerator|DMA_NONE
id|DMA_NONE
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|macro|DMA_64BIT_MASK
mdefine_line|#define DMA_64BIT_MASK&t;0xffffffffffffffffULL
DECL|macro|DMA_32BIT_MASK
mdefine_line|#define DMA_32BIT_MASK&t;0x00000000ffffffffULL
macro_line|#include &lt;asm/dma-mapping.h&gt;
multiline_comment|/* Backwards compat, remove in 2.7.x */
DECL|macro|dma_sync_single
mdefine_line|#define dma_sync_single&t;&t;dma_sync_single_for_cpu
DECL|macro|dma_sync_sg
mdefine_line|#define dma_sync_sg&t;&t;dma_sync_sg_for_cpu
macro_line|#ifndef ARCH_HAS_DMA_GET_REQUIRED_MASK
DECL|function|dma_get_required_mask
r_static
r_inline
id|u64
id|dma_get_required_mask
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_extern
r_int
r_int
id|max_pfn
suffix:semicolon
multiline_comment|/* defined in bootmem.h but may&n;&t;&t;&t;&t;&t; not be included */
id|u32
id|low_totalram
op_assign
(paren
(paren
id|max_pfn
op_minus
l_int|1
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|u32
id|high_totalram
op_assign
(paren
(paren
id|max_pfn
op_minus
l_int|1
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|u64
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|high_totalram
)paren
(brace
multiline_comment|/* convert to mask just covering totalram */
id|low_totalram
op_assign
(paren
l_int|1
op_lshift
(paren
id|fls
c_func
(paren
id|low_totalram
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|low_totalram
op_add_assign
id|low_totalram
op_minus
l_int|1
suffix:semicolon
id|mask
op_assign
id|low_totalram
suffix:semicolon
)brace
r_else
(brace
id|high_totalram
op_assign
(paren
l_int|1
op_lshift
(paren
id|fls
c_func
(paren
id|high_totalram
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|high_totalram
op_add_assign
id|high_totalram
op_minus
l_int|1
suffix:semicolon
id|mask
op_assign
(paren
(paren
(paren
id|u64
)paren
id|high_totalram
)paren
op_lshift
l_int|32
)paren
op_plus
l_int|0xffffffff
suffix:semicolon
)brace
r_return
id|mask
op_amp
op_star
id|dev-&gt;dma_mask
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* flags for the coherent memory api */
DECL|macro|DMA_MEMORY_MAP
mdefine_line|#define&t;DMA_MEMORY_MAP&t;&t;&t;0x01
DECL|macro|DMA_MEMORY_IO
mdefine_line|#define DMA_MEMORY_IO&t;&t;&t;0x02
DECL|macro|DMA_MEMORY_INCLUDES_CHILDREN
mdefine_line|#define DMA_MEMORY_INCLUDES_CHILDREN&t;0x04
DECL|macro|DMA_MEMORY_EXCLUSIVE
mdefine_line|#define DMA_MEMORY_EXCLUSIVE&t;&t;0x08
macro_line|#ifndef ARCH_HAS_DMA_DECLARE_COHERENT_MEMORY
r_static
r_inline
r_int
DECL|function|dma_declare_coherent_memory
id|dma_declare_coherent_memory
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|bus_addr
comma
id|dma_addr_t
id|device_addr
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dma_release_declared_memory
id|dma_release_declared_memory
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
)brace
DECL|function|dma_mark_declared_memory_occupied
r_void
op_star
id|dma_mark_declared_memory_occupied
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|device_addr
comma
r_int
id|size
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
