macro_line|#ifndef _ASM_SPARC_DMA_MAPPING_H
DECL|macro|_ASM_SPARC_DMA_MAPPING_H
mdefine_line|#define _ASM_SPARC_DMA_MAPPING_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm-generic/dma-mapping.h&gt;
macro_line|#else
DECL|function|dma_alloc_coherent
r_static
r_inline
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
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dma_free_coherent
r_static
r_inline
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
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* PCI */
macro_line|#endif /* _ASM_SPARC_DMA_MAPPING_H */
eof
