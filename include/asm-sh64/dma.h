macro_line|#ifndef __ASM_SH64_DMA_H
DECL|macro|__ASM_SH64_DMA_H
mdefine_line|#define __ASM_SH64_DMA_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/dma.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;4
multiline_comment|/*&n; * SH5 can DMA in any memory area.&n; *&n; * The static definition is dodgy because it should limit&n; * the highest DMA-able address based on the actual&n; * Physical memory available. This is actually performed&n; * at run time in defining the memory allowed to DMA_ZONE.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;~(NPHYS_MASK)
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;&t;0
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;&t;1
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* __ASM_SH64_DMA_H */
eof
