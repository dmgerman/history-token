multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/dma.h&n; *&n; *  Copyright (C) 1996-1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Acorn Archimedes/A5000 architecture virtual DMA&n; *  implementation&n; *&n; *  Modifications:&n; *   04-04-1998&t;RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0x03000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;3
multiline_comment|/* ARC */
DECL|macro|DMA_VIRTUAL_FLOPPY0
mdefine_line|#define DMA_VIRTUAL_FLOPPY0&t;0
DECL|macro|DMA_VIRTUAL_FLOPPY1
mdefine_line|#define DMA_VIRTUAL_FLOPPY1&t;1
DECL|macro|DMA_VIRTUAL_SOUND
mdefine_line|#define DMA_VIRTUAL_SOUND&t;2
multiline_comment|/* A5K */
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY&t;&t;DMA_VIRTUAL_FLOPPY0
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
