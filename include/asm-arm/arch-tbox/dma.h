multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/dma.h&n; *&n; * Architecture DMA routines.  We have to contend with the bizarre DMA&n; * machine built into the Tbox hardware.&n; *&n; * Copyright (C) 1998 Philip Blundell&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * DMA channel definitions.  Some of these are physically strange but&n; * we sort it out inside dma.c so the user never has to care.  The&n; * exception is the double-buffering which we can&squot;t really abstract&n; * away sensibly.&n; */
DECL|macro|DMA_VIDEO
mdefine_line|#define DMA_VIDEO&t;&t;&t;0
DECL|macro|DMA_MPEG_B
mdefine_line|#define DMA_MPEG_B&t;&t;&t;1
DECL|macro|DMA_AUDIO_B
mdefine_line|#define DMA_AUDIO_B&t;&t;&t;2
DECL|macro|DMA_ASHRX_B
mdefine_line|#define DMA_ASHRX_B&t;&t;&t;3
DECL|macro|DMA_ASHTX
mdefine_line|#define DMA_ASHTX&t;&t;&t;4
DECL|macro|DMA_MPEG
mdefine_line|#define DMA_MPEG&t;&t;&t;5
DECL|macro|DMA_AUDIO
mdefine_line|#define DMA_AUDIO&t;&t;&t;6
DECL|macro|DMA_ASHRX
mdefine_line|#define DMA_ASHRX&t;&t;&t;7
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;&t;0&t;/* XXX */
multiline_comment|/*&n; * This is the maximum DMA address that can be DMAd to.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
eof
