macro_line|#ifndef _M68K_DMA_H
DECL|macro|_M68K_DMA_H
mdefine_line|#define _M68K_DMA_H 1
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* it&squot;s useless on the m68k, but unfortunately needed by the new&n;   bootmem allocator (but this should do it for this) */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
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
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy    (0)
macro_line|#endif
macro_line|#endif /* _M68K_DMA_H */
eof
