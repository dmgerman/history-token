macro_line|#ifndef M68KNOMMU_PCI_H
DECL|macro|M68KNOMMU_PCI_H
mdefine_line|#define&t;M68KNOMMU_PCI_H
macro_line|#include &lt;asm-m68k/pci.h&gt;
macro_line|#ifdef CONFIG_COMEMPCI
multiline_comment|/*&n; *&t;These are pretty much arbitary with the CoMEM implementation.&n; *&t;We have the whole address space to ourselves.&n; */
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x100
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x00010000
multiline_comment|/*&n; * Return whether the given PCI device DMA address mask can&n; * be supported properly.  For example, if your device can&n; * only drive the low 24-bits during PCI bus mastering, then&n; * you would pass 0x00ffffff as the mask to this function.&n; */
DECL|function|pci_dma_supported
r_static
r_inline
r_int
id|pci_dma_supported
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|u64
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Not supporting more than 32-bit PCI bus addresses now, but&n; * must satisfy references to this function.  Change if needed.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask) (0)
macro_line|#endif /* CONFIG_COMEMPCI */
macro_line|#endif /* M68KNOMMU_PCI_H */
eof
