macro_line|#ifndef __ASM_CRIS_SCATTERLIST_H
DECL|macro|__ASM_CRIS_SCATTERLIST_H
mdefine_line|#define __ASM_CRIS_SCATTERLIST_H
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
multiline_comment|/* The following is i386 highmem junk - not used by us */
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
)brace
suffix:semicolon
multiline_comment|/* i386 junk */
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x1fffffff)
macro_line|#endif /* !(__ASM_CRIS_SCATTERLIST_H) */
eof
