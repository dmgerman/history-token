macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SCATTERLIST_H
DECL|macro|_PPC_SCATTERLIST_H
mdefine_line|#define _PPC_SCATTERLIST_H
macro_line|#include &lt;asm/dma.h&gt;
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
DECL|member|alt_address
r_char
op_star
id|alt_address
suffix:semicolon
multiline_comment|/* Location of actual if address is a &n;&t;&t;&t; * dma indirect buffer.  NULL otherwise */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(_PPC_SCATTERLIST_H) */
macro_line|#endif /* __KERNEL__ */
eof
