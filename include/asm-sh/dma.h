macro_line|#ifndef __ASM_SH_DMA_H
DECL|macro|__ASM_SH_DMA_H
mdefine_line|#define __ASM_SH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
multiline_comment|/* The maximum address that we can perform a DMA transfer to on this platform */
multiline_comment|/* Don&squot;t define MAX_DMA_ADDRESS; it&squot;s useless on the SuperH and any&n;   occurrence should be flagged as an error.  */
multiline_comment|/* But... */
multiline_comment|/* XXX: This is not applicable to SuperH, just needed for alloc_bootmem */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS      (PAGE_OFFSET+0x10000000)
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
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* __ASM_SH_DMA_H */
eof
