multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/dma.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
multiline_comment|/* No DMA as the rest of the world see it */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
multiline_comment|/*&n; * Descriptor structure for PXA&squot;s DMA engine&n; * Note: this structure must always be aligned to a 16-byte boundary.&n; */
r_typedef
r_struct
(brace
DECL|member|ddadr
r_volatile
id|u32
id|ddadr
suffix:semicolon
multiline_comment|/* Points to the next descriptor + flags */
DECL|member|dsadr
r_volatile
id|u32
id|dsadr
suffix:semicolon
multiline_comment|/* DSADR value for the current transfer */
DECL|member|dtadr
r_volatile
id|u32
id|dtadr
suffix:semicolon
multiline_comment|/* DTADR value for the current transfer */
DECL|member|dcmd
r_volatile
id|u32
id|dcmd
suffix:semicolon
multiline_comment|/* DCMD value for the current transfer */
DECL|typedef|pxa_dma_desc
)brace
id|pxa_dma_desc
suffix:semicolon
multiline_comment|/*&n; * DMA registration&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMA_PRIO_HIGH
id|DMA_PRIO_HIGH
op_assign
l_int|0
comma
DECL|enumerator|DMA_PRIO_MEDIUM
id|DMA_PRIO_MEDIUM
op_assign
l_int|4
comma
DECL|enumerator|DMA_PRIO_LOW
id|DMA_PRIO_LOW
op_assign
l_int|8
DECL|typedef|pxa_dma_prio
)brace
id|pxa_dma_prio
suffix:semicolon
r_int
id|pxa_request_dma
(paren
r_char
op_star
id|name
comma
id|pxa_dma_prio
id|prio
comma
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_void
id|pxa_free_dma
(paren
r_int
id|dma_ch
)paren
suffix:semicolon
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
