multiline_comment|/*&n; * include/asm-sh/dreamcast/dma.h&n; *&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_SH_DREAMCAST_DMA_H
DECL|macro|__ASM_SH_DREAMCAST_DMA_H
mdefine_line|#define __ASM_SH_DREAMCAST_DMA_H
multiline_comment|/* Number of DMA channels */
DECL|macro|ONCHIP_NR_DMA_CHANNELS
mdefine_line|#define ONCHIP_NR_DMA_CHANNELS&t;4
DECL|macro|G2_NR_DMA_CHANNELS
mdefine_line|#define G2_NR_DMA_CHANNELS&t;4
DECL|macro|PVR2_NR_DMA_CHANNELS
mdefine_line|#define PVR2_NR_DMA_CHANNELS&t;1
multiline_comment|/* Channels for cascading */
DECL|macro|PVR2_CASCADE_CHAN
mdefine_line|#define PVR2_CASCADE_CHAN&t;2
DECL|macro|G2_CASCADE_CHAN
mdefine_line|#define G2_CASCADE_CHAN&t;&t;3
multiline_comment|/* PVR2 DMA Registers */
DECL|macro|PVR2_DMA_BASE
mdefine_line|#define PVR2_DMA_BASE&t;&t;0xa05f6800
DECL|macro|PVR2_DMA_ADDR
mdefine_line|#define PVR2_DMA_ADDR&t;&t;(PVR2_DMA_BASE + 0)
DECL|macro|PVR2_DMA_COUNT
mdefine_line|#define PVR2_DMA_COUNT&t;&t;(PVR2_DMA_BASE + 4)
DECL|macro|PVR2_DMA_MODE
mdefine_line|#define PVR2_DMA_MODE&t;&t;(PVR2_DMA_BASE + 8)
DECL|macro|PVR2_DMA_LMMODE0
mdefine_line|#define PVR2_DMA_LMMODE0&t;(PVR2_DMA_BASE + 132)
DECL|macro|PVR2_DMA_LMMODE1
mdefine_line|#define PVR2_DMA_LMMODE1&t;(PVR2_DMA_BASE + 136)
multiline_comment|/* G2 DMA Register */
DECL|macro|G2_DMA_BASE
mdefine_line|#define G2_DMA_BASE&t;&t;0xa05f7800
macro_line|#endif /* __ASM_SH_DREAMCAST_DMA_H */
eof
