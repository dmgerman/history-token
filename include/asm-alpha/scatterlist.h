macro_line|#ifndef _ALPHA_SCATTERLIST_H
DECL|macro|_ALPHA_SCATTERLIST_H
mdefine_line|#define _ALPHA_SCATTERLIST_H
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Source/target vaddr.  */
DECL|member|alt_address
r_char
op_star
id|alt_address
suffix:semicolon
multiline_comment|/* Location of actual if address is a&n;&t;&t;&t;&t;&t;   dma indirect buffer, else NULL.  */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|dma_length
r_int
r_int
id|dma_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg) ((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)     ((sg)-&gt;dma_length)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (~0UL)
macro_line|#endif /* !(_ALPHA_SCATTERLIST_H) */
eof
