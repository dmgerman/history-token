macro_line|#ifndef _ASM_LINUX_DMA_MAPPING_H
DECL|macro|_ASM_LINUX_DMA_MAPPING_H
mdefine_line|#define _ASM_LINUX_DMA_MAPPING_H
multiline_comment|/* These definitions mirror those in pci.h, so they can be used&n; * interchangeably with their PCI_ counterparts */
DECL|enum|dma_data_direction
r_enum
id|dma_data_direction
(brace
DECL|enumerator|DMA_BIDIRECTIONAL
id|DMA_BIDIRECTIONAL
op_assign
l_int|0
comma
DECL|enumerator|DMA_TO_DEVICE
id|DMA_TO_DEVICE
op_assign
l_int|1
comma
DECL|enumerator|DMA_FROM_DEVICE
id|DMA_FROM_DEVICE
op_assign
l_int|2
comma
DECL|enumerator|DMA_NONE
id|DMA_NONE
op_assign
l_int|3
comma
)brace
suffix:semicolon
macro_line|#include &lt;asm/dma-mapping.h&gt;
macro_line|#endif
eof
