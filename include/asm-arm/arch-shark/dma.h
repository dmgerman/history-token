multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/dma.h&n; *&n; * by Alexander Schulz &lt;aschulz@netwinder.org&gt;&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
multiline_comment|/* Use only the lowest 4MB, nothing else works.&n; * The rest is not DMAable. See dev /  .properties&n; * in OpenFirmware.&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xC0400000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;8
DECL|macro|DMA_ISA_CASCADE
mdefine_line|#define DMA_ISA_CASCADE         4
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
