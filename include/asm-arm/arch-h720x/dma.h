multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/dma.h&n; *&n; * Architecture DMA routes&n; *&n; * Copyright (C) 1997.1998 Russell King&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; * There should not be more than (0xd0000000 - 0xc0000000)&n; * bytes of RAM.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xd0000000
macro_line|#if defined (CONFIG_CPU_H7201)
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;3
macro_line|#elif defined (CONFIG_CPU_H7202)
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;4
macro_line|#else
macro_line|#error processor definition missmatch
macro_line|#endif
macro_line|#endif /* __ASM_ARCH_DMA_H */
eof
