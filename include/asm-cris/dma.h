multiline_comment|/* $Id: dma.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $&n; * linux/include/asm/dma.h: Defines for using and allocating dma channels.&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
multiline_comment|/* it&squot;s useless on the Etrax, but unfortunately needed by the new&n;   bootmem allocator (but this should do it for this) */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
multiline_comment|/* TODO: check nbr of channels on Etrax-100LX */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;10
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
multiline_comment|/* release it */
macro_line|#endif /* _ASM_DMA_H */
eof
