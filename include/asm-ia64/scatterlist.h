macro_line|#ifndef _ASM_IA64_SCATTERLIST_H
DECL|macro|_ASM_IA64_SCATTERLIST_H
mdefine_line|#define _ASM_IA64_SCATTERLIST_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* location data is to be transferred to */
DECL|member|orig_address
r_char
op_star
id|orig_address
suffix:semicolon
multiline_comment|/* Save away the original buffer address (used by pci-dma.c) */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* buffer length */
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* _ASM_IA64_SCATTERLIST_H */
eof
