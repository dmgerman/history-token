macro_line|#ifndef _ASMARM_SCATTERLIST_H
DECL|macro|_ASMARM_SCATTERLIST_H
mdefine_line|#define _ASMARM_SCATTERLIST_H
macro_line|#include &lt;asm/types.h&gt;
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
multiline_comment|/* buffer page&t;&t;&t; */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* buffer offset&t;&t; */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
multiline_comment|/* dma address&t;&t;&t; */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* length&t;&t;&t; */
DECL|member|__address
r_char
op_star
id|__address
suffix:semicolon
multiline_comment|/* for set_dma_addr&t;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * These macros should be used after a pci_map_sg call has been done&n; * to get bus addresses of each of the SG entries and their lengths.&n; * You should only work with the number of sg entries pci_map_sg&n; * returns, or alternatively stop on the first sg_dma_len(sg) which&n; * is 0.&n; */
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)      ((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)          ((sg)-&gt;length)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0xffffffff)
macro_line|#endif /* _ASMARM_SCATTERLIST_H */
eof
