macro_line|#ifndef _ASM_IA64_PCI_H
DECL|macro|_ASM_IA64_PCI_H
mdefine_line|#define _ASM_IA64_PCI_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
multiline_comment|/*&n; * Can be used to override the logic in pci_scan_bus for skipping already-configured bus&n; * numbers - to be used for buggy BIOSes or architectures with incomplete PCI setup by the&n; * loader.&n; */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()     0
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x10000000
r_void
id|pcibios_config_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pcibios_scan_root
c_func
(paren
r_void
op_star
id|acpi_handle
comma
r_int
id|segment
comma
r_int
id|bus
)paren
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/*&n; * The PCI address space does equal the physical memory address space.&n; * The networking and block device layers use this boolean for bounce&n; * buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
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
DECL|macro|HAVE_ARCH_PCI_MWI
mdefine_line|#define HAVE_ARCH_PCI_MWI 1
r_extern
r_int
id|pcibios_prep_mwi
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
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
DECL|macro|pci_dma_supported
mdefine_line|#define pci_dma_supported&t;&t;platform_pci_dma_supported
multiline_comment|/* pci_unmap_{single,page} is not a nop, thus... */
DECL|macro|DECLARE_PCI_UNMAP_ADDR
mdefine_line|#define DECLARE_PCI_UNMAP_ADDR(ADDR_NAME)&t;&bslash;&n;&t;dma_addr_t ADDR_NAME;
DECL|macro|DECLARE_PCI_UNMAP_LEN
mdefine_line|#define DECLARE_PCI_UNMAP_LEN(LEN_NAME)&t;&t;&bslash;&n;&t;__u32 LEN_NAME;
DECL|macro|pci_unmap_addr
mdefine_line|#define pci_unmap_addr(PTR, ADDR_NAME)&t;&t;&t;&bslash;&n;&t;((PTR)-&gt;ADDR_NAME)
DECL|macro|pci_unmap_addr_set
mdefine_line|#define pci_unmap_addr_set(PTR, ADDR_NAME, VAL)&t;&t;&bslash;&n;&t;(((PTR)-&gt;ADDR_NAME) = (VAL))
DECL|macro|pci_unmap_len
mdefine_line|#define pci_unmap_len(PTR, LEN_NAME)&t;&t;&t;&bslash;&n;&t;((PTR)-&gt;LEN_NAME)
DECL|macro|pci_unmap_len_set
mdefine_line|#define pci_unmap_len_set(PTR, LEN_NAME, VAL)&t;&t;&bslash;&n;&t;(((PTR)-&gt;LEN_NAME) = (VAL))
DECL|macro|pci_map_page
mdefine_line|#define pci_map_page(dev,pg,off,size,dir)&t;&t;&t;&t;&bslash;&n;&t;pci_map_single((dev), page_address(pg) + (off), (size), (dir))
DECL|macro|pci_unmap_page
mdefine_line|#define pci_unmap_page(dev,dma_addr,size,dir)&t;&t;&t;&t;&bslash;&n;&t;pci_unmap_single((dev), (dma_addr), (size), (dir))
multiline_comment|/* The ia64 platform always supports 64-bit addressing. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(1)
DECL|macro|pci_dac_page_to_dma
mdefine_line|#define pci_dac_page_to_dma(dev,pg,off,dir)&t;((dma_addr_t) page_to_bus(pg) + (off))
DECL|macro|pci_dac_dma_to_page
mdefine_line|#define pci_dac_dma_to_page(dev,dma_addr)&t;(virt_to_page(bus_to_virt(dma_addr)))
DECL|macro|pci_dac_dma_to_offset
mdefine_line|#define pci_dac_dma_to_offset(dev,dma_addr)&t;((dma_addr) &amp; ~PAGE_MASK)
DECL|macro|pci_dac_dma_sync_single
mdefine_line|#define pci_dac_dma_sync_single(dev,dma_addr,len,dir)&t;do { /* nothing */ } while (0)
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(PDEV)&t;(0)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;dma_length)
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;((sg)-&gt;dma_address)
DECL|macro|HAVE_PCI_MMAP
mdefine_line|#define HAVE_PCI_MMAP
r_extern
r_int
id|pci_mmap_page_range
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
DECL|struct|pci_window
r_struct
id|pci_window
(brace
DECL|member|resource
r_struct
id|resource
id|resource
suffix:semicolon
DECL|member|offset
id|u64
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_controller
r_struct
id|pci_controller
(brace
DECL|member|acpi_handle
r_void
op_star
id|acpi_handle
suffix:semicolon
DECL|member|iommu
r_void
op_star
id|iommu
suffix:semicolon
DECL|member|segment
r_int
id|segment
suffix:semicolon
DECL|member|windows
r_int
r_int
id|windows
suffix:semicolon
DECL|member|window
r_struct
id|pci_window
op_star
id|window
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_CONTROLLER
mdefine_line|#define PCI_CONTROLLER(busdev) ((struct pci_controller *) busdev-&gt;sysdata)
DECL|macro|PCI_SEGMENT
mdefine_line|#define PCI_SEGMENT(busdev)    (PCI_CONTROLLER(busdev)-&gt;segment)
multiline_comment|/* generic pci stuff */
macro_line|#include &lt;asm-generic/pci.h&gt;
macro_line|#endif /* _ASM_IA64_PCI_H */
eof
