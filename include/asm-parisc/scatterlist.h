macro_line|#ifndef _ASM_PARISC_SCATTERLIST_H
DECL|macro|_ASM_PARISC_SCATTERLIST_H
mdefine_line|#define _ASM_PARISC_SCATTERLIST_H
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
multiline_comment|/* an IOVA can be 64-bits on some PA-Risc platforms. */
DECL|member|iova
id|dma_addr_t
id|iova
suffix:semicolon
multiline_comment|/* I/O Virtual Address */
DECL|member|iova_length
id|__u32
id|iova_length
suffix:semicolon
multiline_comment|/* bytes mapped */
)brace
suffix:semicolon
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg) ((sg)-&gt;iova)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)     ((sg)-&gt;iova_length)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (~0UL)
macro_line|#endif /* _ASM_PARISC_SCATTERLIST_H */
eof
