macro_line|#ifndef _ASMS390_SCATTERLIST_H
DECL|macro|_ASMS390_SCATTERLIST_H
mdefine_line|#define _ASMS390_SCATTERLIST_H
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
)brace
suffix:semicolon
macro_line|#ifdef __s390x__
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0xffffffffffffffffUL)
macro_line|#else
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0xffffffffUL)
macro_line|#endif
macro_line|#endif /* _ASMS390X_SCATTERLIST_H */
eof
