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
multiline_comment|/* These macros should be used after a pci_map_sg call has been done&n; * to get bus addresses of each of the SG entries and their lengths.&n; * You should only work with the number of sg entries pci_map_sg&n; * returns.&n; */
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)     ((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)         ((sg)-&gt;length)
macro_line|#endif 
eof
