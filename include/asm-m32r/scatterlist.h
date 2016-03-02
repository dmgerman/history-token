macro_line|#ifndef _ASM_M32R_SCATTERLIST_H
DECL|macro|_ASM_M32R_SCATTERLIST_H
mdefine_line|#define _ASM_M32R_SCATTERLIST_H
multiline_comment|/* $Id$ */
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Location data is to be transferred to, NULL for&n;                         * highmem page */
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/* Location for highmem page, if any */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* for highmem, page offset */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x1fffffff)
macro_line|#endif /* _ASM_M32R_SCATTERLIST_H */
eof
