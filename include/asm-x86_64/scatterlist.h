macro_line|#ifndef _X8664_SCATTERLIST_H
DECL|macro|_X8664_SCATTERLIST_H
mdefine_line|#define _X8664_SCATTERLIST_H
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif 
eof
