macro_line|#ifndef _ASM_M32R_DMA_H
DECL|macro|_ASM_M32R_DMA_H
mdefine_line|#define _ASM_M32R_DMA_H
multiline_comment|/* $Id$ */
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * The maximum address that we can perform a DMA transfer&n; * to on this platform&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS      (PAGE_OFFSET+0x20000000)
macro_line|#endif /* _ASM_M32R_DMA_H */
eof
