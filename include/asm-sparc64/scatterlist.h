multiline_comment|/* $Id: scatterlist.h,v 1.10 2001/10/09 02:24:35 davem Exp $ */
macro_line|#ifndef _SPARC64_SCATTERLIST_H
DECL|macro|_SPARC64_SCATTERLIST_H
mdefine_line|#define _SPARC64_SCATTERLIST_H
macro_line|#include &lt;asm/page.h&gt;
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
multiline_comment|/* This will disappear in 2.5.x */
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* These two are only valid if ADDRESS member of this&n;&t; * struct is NULL.&n;&t; */
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
DECL|member|dma_length
id|__u32
id|dma_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)     &t;((sg)-&gt;dma_length)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* !(_SPARC64_SCATTERLIST_H) */
eof
