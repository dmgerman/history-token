multiline_comment|/* $Id: scatterlist.h,v 1.9 1999/12/17 12:32:15 jj Exp $ */
macro_line|#ifndef _SPARC64_SCATTERLIST_H
DECL|macro|_SPARC64_SCATTERLIST_H
mdefine_line|#define _SPARC64_SCATTERLIST_H
macro_line|#include &lt;asm/page.h&gt;
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Location data is to be transferred to */
DECL|member|alt_address
r_char
op_star
id|alt_address
suffix:semicolon
multiline_comment|/* Location of actual if address is a &n;&t;&t;&t; * dma indirect buffer.  NULL otherwise */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|dvma_address
id|__u32
id|dvma_address
suffix:semicolon
multiline_comment|/* A place to hang host-specific addresses at. */
DECL|member|dvma_length
id|__u32
id|dvma_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg) ((sg)-&gt;dvma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)     ((sg)-&gt;dvma_length)
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* !(_SPARC64_SCATTERLIST_H) */
eof
