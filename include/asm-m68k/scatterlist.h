macro_line|#ifndef _M68K_SCATTERLIST_H
DECL|macro|_M68K_SCATTERLIST_H
mdefine_line|#define _M68K_SCATTERLIST_H
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
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
)brace
suffix:semicolon
multiline_comment|/* This is bogus and should go away. */
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif /* !(_M68K_SCATTERLIST_H) */
eof
