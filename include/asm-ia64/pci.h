macro_line|#ifndef _ASM_IA64_PCI_H
DECL|macro|_ASM_IA64_PCI_H
mdefine_line|#define _ASM_IA64_PCI_H
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n; * Can be used to override the logic in pci_scan_bus for skipping&n; * already-configured bus numbers - to be used for buggy BIOSes or&n; * architectures with incomplete PCI setup by the loader.&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()     0
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x10000000
r_struct
id|pci_dev
suffix:semicolon
r_static
r_inline
r_void
DECL|function|pcibios_set_master
id|pcibios_set_master
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* No special bus mastering setup handling */
)brace
r_static
r_inline
r_void
DECL|function|pcibios_penalize_isa_irq
id|pcibios_penalize_isa_irq
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* We don&squot;t do dynamic PCI IRQ allocation */
)brace
multiline_comment|/*&n; * Dynamic DMA mapping API.  See Documentation/DMA-mapping.txt for details.&n; */
DECL|macro|pci_alloc_consistent
mdefine_line|#define pci_alloc_consistent&t;&t;platform_pci_alloc_consistent
DECL|macro|pci_free_consistent
mdefine_line|#define pci_free_consistent&t;&t;platform_pci_free_consistent
DECL|macro|pci_map_single
mdefine_line|#define pci_map_single&t;&t;&t;platform_pci_map_single
DECL|macro|pci_unmap_single
mdefine_line|#define pci_unmap_single&t;&t;platform_pci_unmap_single
DECL|macro|pci_map_sg
mdefine_line|#define pci_map_sg&t;&t;&t;platform_pci_map_sg
DECL|macro|pci_unmap_sg
mdefine_line|#define pci_unmap_sg&t;&t;&t;platform_pci_unmap_sg
DECL|macro|pci_dma_sync_single
mdefine_line|#define pci_dma_sync_single&t;&t;platform_pci_dma_sync_single
DECL|macro|pci_dma_sync_sg
mdefine_line|#define pci_dma_sync_sg&t;&t;&t;platform_pci_dma_sync_sg
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address&t;&t;&t;platform_pci_dma_address
multiline_comment|/*&n; * Return whether the given PCI device DMA address mask can be supported properly.  For&n; * example, if your device can only drive the low 24-bits during PCI bus mastering, then&n; * you would pass 0x00ffffff as the mask to this function.&n; */
r_static
r_inline
r_int
DECL|function|pci_dma_supported
id|pci_dma_supported
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;length)
macro_line|#endif /* _ASM_IA64_PCI_H */
eof
