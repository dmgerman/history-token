macro_line|#ifndef __EMU_WRAPPER_H
DECL|macro|__EMU_WRAPPER_H
mdefine_line|#define __EMU_WRAPPER_H
DECL|macro|vma_get_pgoff
mdefine_line|#define vma_get_pgoff(v)&t;&t;((v)-&gt;vm_pgoff)
DECL|macro|PCI_SET_DMA_MASK
mdefine_line|#define PCI_SET_DMA_MASK(pdev,mask)&t;(((pdev)-&gt;dma_mask) = (mask))
macro_line|#endif
eof
