multiline_comment|/*&n; * BK Id: SCCS/s.scatterlist.h 1.9 10/15/01 22:51:33 paulus&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SCATTERLIST_H
DECL|macro|_PPC_SCATTERLIST_H
mdefine_line|#define _PPC_SCATTERLIST_H
macro_line|#include &lt;asm/dma.h&gt;
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Location data is to be transferred to,&n;&t;&t;&t;&t; * or NULL for highmem page */
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
multiline_comment|/* phys/bus dma address&t;&t; */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* length&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * These macros should be used after a pci_map_sg call has been done&n; * to get bus addresses of each of the SG entries and their lengths.&n; * You should only work with the number of sg entries pci_map_sg&n; * returns, or alternatively stop on the first sg_dma_len(sg) which&n; * is 0.&n; */
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)      ((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)          ((sg)-&gt;length)
macro_line|#endif /* !(_PPC_SCATTERLIST_H) */
macro_line|#endif /* __KERNEL__ */
eof
