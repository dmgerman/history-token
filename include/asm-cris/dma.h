multiline_comment|/* $Id: dma.h,v 1.2 2001/05/09 12:17:42 johana Exp $ */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;asm/arch/dma.h&gt;
multiline_comment|/* it&squot;s useless on the Etrax, but unfortunately needed by the new&n;   bootmem allocator (but this should do it for this) */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
macro_line|#endif /* _ASM_DMA_H */
eof
