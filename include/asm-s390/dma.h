multiline_comment|/*&n; *  include/asm-s390/delay.h&n; *&n; *  S390 version&n; *&n; *  This file exists so that an #include &lt;dma.h&gt; doesn&squot;t break anything.&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS         0x80000000
macro_line|#endif /* _ASM_DMA_H */
eof
