macro_line|#ifndef _H8300_DMA_H
DECL|macro|_H8300_DMA_H
mdefine_line|#define _H8300_DMA_H 
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Set number of channels of DMA on ColdFire for different implementations.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 0
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
multiline_comment|/* These are in kernel/dma.c: */
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* reserve a DMA channel */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
multiline_comment|/* release it again */
macro_line|#endif /* _H8300_DMA_H */
eof
