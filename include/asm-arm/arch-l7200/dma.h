multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/dma.h&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; * There should not be more than (0xd0000000 - 0xc0000000)&n; * bytes of RAM.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xd0000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
DECL|macro|DMA_0
mdefine_line|#define DMA_0&t;&t;&t;0
DECL|macro|DMA_1
mdefine_line|#define DMA_1&t;&t;&t;1
DECL|macro|DMA_2
mdefine_line|#define DMA_2&t;&t;&t;2
DECL|macro|DMA_3
mdefine_line|#define DMA_3&t;&t;&t;3
DECL|macro|DMA_S0
mdefine_line|#define DMA_S0&t;&t;&t;4
DECL|macro|DMA_S1
mdefine_line|#define DMA_S1&t;&t;&t;5
DECL|macro|DMA_VIRTUAL_FLOPPY
mdefine_line|#define DMA_VIRTUAL_FLOPPY&t;6
DECL|macro|DMA_VIRTUAL_SOUND
mdefine_line|#define DMA_VIRTUAL_SOUND&t;7
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY&t;&t;DMA_VIRTUAL_FLOPPY
macro_line|#endif
eof
