macro_line|#ifndef _ASM_IA64_SCATTERLIST_H
DECL|macro|_ASM_IA64_SCATTERLIST_H
mdefine_line|#define _ASM_IA64_SCATTERLIST_H
multiline_comment|/*&n; * Copyright (C) 1998-1999, 2001-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
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
multiline_comment|/* buffer length */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
DECL|member|dma_length
r_int
r_int
id|dma_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* _ASM_IA64_SCATTERLIST_H */
eof
