multiline_comment|/*&n; *  include/asm-s390x/dma.h&n; *&n; *  S390 version&n; */
macro_line|#ifndef _ASM_DMA_H
DECL|macro|_ASM_DMA_H
mdefine_line|#define _ASM_DMA_H
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
multiline_comment|/* The I/O subsystem can access only memory below 2GB.&n;   We use the existing DMA zone mechanism to handle this. */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS         0x80000000
macro_line|#endif /* _ASM_DMA_H */
eof
