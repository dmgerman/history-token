macro_line|#ifndef __ASM_MIPS_SCATTERLIST_H
DECL|macro|__ASM_MIPS_SCATTERLIST_H
mdefine_line|#define __ASM_MIPS_SCATTERLIST_H
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
DECL|member|dvma_address
id|__u32
id|dvma_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mmu_sglist
r_struct
id|mmu_sglist
(brace
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
DECL|member|__dont_touch
r_char
op_star
id|__dont_touch
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|dvma_addr
id|__u32
id|dvma_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif /* __ASM_MIPS_SCATTERLIST_H */
eof
