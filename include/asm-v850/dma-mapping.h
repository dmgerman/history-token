macro_line|#ifndef __V850_DMA_MAPPING_H__
DECL|macro|__V850_DMA_MAPPING_H__
mdefine_line|#define __V850_DMA_MAPPING_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm-generic/dma-mapping.h&gt;
macro_line|#else
macro_line|#include &lt;asm-generic/dma-mapping-broken.h&gt;
macro_line|#endif
macro_line|#endif /* __V850_DMA_MAPPING_H__ */
eof
