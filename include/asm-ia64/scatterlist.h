macro_line|#ifndef _ASM_IA64_SCATTERLIST_H
DECL|macro|_ASM_IA64_SCATTERLIST_H
mdefine_line|#define _ASM_IA64_SCATTERLIST_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999, 2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|orig_address
r_char
op_star
id|orig_address
suffix:semicolon
multiline_comment|/* for use by swiotlb */
multiline_comment|/* These two are only valid if ADDRESS member of this struct is NULL.  */
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
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;(~0UL)
macro_line|#endif /* _ASM_IA64_SCATTERLIST_H */
eof
