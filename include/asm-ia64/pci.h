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
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
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
id|pci_dev
suffix:semicolon
multiline_comment|/*&n; * PCI_DMA_BUS_IS_PHYS should be set to 1 if there is _necessarily_ a direct correspondence&n; * between device bus addresses and CPU physical addresses.  Platforms with a hardware I/O&n; * MMU _must_ turn this off to suppress the bounce buffer handling code in the block and&n; * network device layers.  Platforms with separate bus address spaces _must_ turn this off&n; * and provide a device DMA mapping implementation that takes care of the necessary&n; * address translation.&n; *&n; * For now, the ia64 platforms which may have separate/multiple bus address spaces all&n; * have I/O MMUs which support the merging of physically discontiguous buffers, so we can&n; * use that as the sole factor to determine the setting of PCI_DMA_BUS_IS_PHYS.&n; */
r_extern
r_int
r_int
id|ia64_max_iommu_merge_mask
suffix:semicolon
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(ia64_max_iommu_merge_mask == ~0UL)
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
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
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
multiline_comment|/* The ia64 platform always supports 64-bit addressing. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;&t;(1)
DECL|macro|pci_dac_page_to_dma
mdefine_line|#define pci_dac_page_to_dma(dev,pg,off,dir)&t;&t;((dma_addr_t) page_to_bus(pg) + (off))
DECL|macro|pci_dac_dma_to_page
mdefine_line|#define pci_dac_dma_to_page(dev,dma_addr)&t;&t;(virt_to_page(bus_to_virt(dma_addr)))
DECL|macro|pci_dac_dma_to_offset
mdefine_line|#define pci_dac_dma_to_offset(dev,dma_addr)&t;&t;offset_in_page(dma_addr)
DECL|macro|pci_dac_dma_sync_single_for_cpu
mdefine_line|#define pci_dac_dma_sync_single_for_cpu(dev,dma_addr,len,dir)&t;do { } while (0)
DECL|macro|pci_dac_dma_sync_single_for_device
mdefine_line|#define pci_dac_dma_sync_single_for_device(dev,dma_addr,len,dir)&t;do { mb(); } while (0)
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
DECL|member|platform_data
r_void
op_star
id|platform_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_CONTROLLER
mdefine_line|#define PCI_CONTROLLER(busdev) ((struct pci_controller *) busdev-&gt;sysdata)
DECL|macro|pci_domain_nr
mdefine_line|#define pci_domain_nr(busdev)    (PCI_CONTROLLER(busdev)-&gt;segment)
r_extern
r_struct
id|pci_ops
id|pci_root_ops
suffix:semicolon
DECL|function|pci_name_bus
r_static
r_inline
r_int
id|pci_name_bus
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|pci_domain_nr
c_func
(paren
id|bus
)paren
op_eq
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%04x:%02x&quot;
comma
id|pci_domain_nr
c_func
(paren
id|bus
)paren
comma
id|bus-&gt;number
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
r_extern
r_void
id|pcibios_bus_to_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
comma
r_struct
id|pci_bus_region
op_star
id|region
)paren
suffix:semicolon
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
macro_line|#endif /* _ASM_IA64_PCI_H */
eof
