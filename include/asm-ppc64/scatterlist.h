macro_line|#ifndef _PPC64_SCATTERLIST_H
DECL|macro|_PPC64_SCATTERLIST_H
mdefine_line|#define _PPC64_SCATTERLIST_H
multiline_comment|/*&n; * Copyright (C) 2001 PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
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
multiline_comment|/* For TCE support */
DECL|member|dma_address
id|u32
id|dma_address
suffix:semicolon
DECL|member|dma_length
id|u32
id|dma_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* !(_PPC64_SCATTERLIST_H) */
eof
