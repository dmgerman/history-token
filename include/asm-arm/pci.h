macro_line|#ifndef ASMARM_PCI_H
DECL|macro|ASMARM_PCI_H
mdefine_line|#define ASMARM_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
macro_line|#include &lt;asm/hardware.h&gt; /* for PCIBIOS_MIN_* */
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
DECL|function|pcibios_set_master
r_static
r_inline
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* No special bus mastering setup handling */
)brace
DECL|function|pcibios_penalize_isa_irq
r_static
r_inline
r_void
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* We don&squot;t do dynamic PCI IRQ allocation */
)brace
multiline_comment|/*&n; * The PCI address space does equal the physical memory address space.&n; * The networking and block device layers use this boolean for bounce&n; * buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS     (0)
multiline_comment|/*&n; * We don&squot;t support DAC DMA cycles.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
multiline_comment|/*&n; * Whether pci_unmap_{single,page} is a nop depends upon the&n; * configuration.&n; */
DECL|macro|DECLARE_PCI_UNMAP_ADDR
mdefine_line|#define DECLARE_PCI_UNMAP_ADDR(ADDR_NAME)&t;dma_addr_t ADDR_NAME;
DECL|macro|DECLARE_PCI_UNMAP_LEN
mdefine_line|#define DECLARE_PCI_UNMAP_LEN(LEN_NAME)&t;&t;__u32 LEN_NAME;
DECL|macro|pci_unmap_addr
mdefine_line|#define pci_unmap_addr(PTR, ADDR_NAME)&t;&t;((PTR)-&gt;ADDR_NAME)
DECL|macro|pci_unmap_addr_set
mdefine_line|#define pci_unmap_addr_set(PTR, ADDR_NAME, VAL)&t;(((PTR)-&gt;ADDR_NAME) = (VAL))
DECL|macro|pci_unmap_len
mdefine_line|#define pci_unmap_len(PTR, LEN_NAME)&t;&t;((PTR)-&gt;LEN_NAME)
DECL|macro|pci_unmap_len_set
mdefine_line|#define pci_unmap_len_set(PTR, LEN_NAME, VAL)&t;(((PTR)-&gt;LEN_NAME) = (VAL))
DECL|macro|HAVE_PCI_MMAP
mdefine_line|#define HAVE_PCI_MMAP
r_extern
r_int
id|pci_mmap_page_range
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus_region
op_star
id|region
comma
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
DECL|function|pcibios_add_platform_entries
r_static
r_inline
r_void
id|pcibios_add_platform_entries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
