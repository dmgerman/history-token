multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/dma.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *  08-29-2000&t;SJH&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/* DMA is not yet implemented! It should be the same as acorn, copy over.. */
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; * There should not be more than (0xd0000000 - 0xc0000000)&n; * bytes of RAM.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS         0xd0000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS        0
DECL|macro|DMA_S0
mdefine_line|#define DMA_S0                  0
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
