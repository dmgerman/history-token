multiline_comment|/* $Id: scatterlist.h,v 1.7 2001/10/30 04:34:57 davem Exp $ */
macro_line|#ifndef _SPARC_SCATTERLIST_H
DECL|macro|_SPARC_SCATTERLIST_H
mdefine_line|#define _SPARC_SCATTERLIST_H
macro_line|#include &lt;linux/types.h&gt;
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
mdefine_line|#define ISA_DMA_THRESHOLD (~0UL)
macro_line|#endif /* !(_SPARC_SCATTERLIST_H) */
eof
