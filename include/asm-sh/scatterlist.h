macro_line|#ifndef __ASM_SH_SCATTERLIST_H
DECL|macro|__ASM_SH_SCATTERLIST_H
mdefine_line|#define __ASM_SH_SCATTERLIST_H
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
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x1fffffff)
macro_line|#endif /* !(__ASM_SH_SCATTERLIST_H) */
eof
