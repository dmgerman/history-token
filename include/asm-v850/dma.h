macro_line|#ifndef __V850_DMA_H__
DECL|macro|__V850_DMA_H__
mdefine_line|#define __V850_DMA_H__
multiline_comment|/* What should this be?  */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;0xFFFFFFFF
multiline_comment|/* reserve a DMA channel */
r_extern
r_int
id|request_dma
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
multiline_comment|/* release it again */
r_extern
r_void
id|free_dma
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy    (0)
macro_line|#endif
macro_line|#endif /* __V850_DMA_H__ */
eof
