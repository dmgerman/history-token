multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/dma.h&n; *&n; *  Architecture DMA routines&n; *&n; *  Copyright (C) 1998,1999 Russell King&n; *  Copyright (C) 1998,1999 Philip Blundell&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
multiline_comment|/*&n; * The 21285 has two internal DMA channels; we call these 8 and 9.&n; * On CATS hardware we have an additional eight ISA dma channels&n; * numbered 0..7.&n; */
DECL|macro|_ISA_DMA
mdefine_line|#define _ISA_DMA(x)&t;&t;(0+(x))
DECL|macro|_DC21285_DMA
mdefine_line|#define _DC21285_DMA(x)&t;&t;(8+(x))
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;10
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY&t;&t;_ISA_DMA(2)
DECL|macro|DMA_ISA_CASCADE
mdefine_line|#define DMA_ISA_CASCADE&t;&t;_ISA_DMA(4)
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
