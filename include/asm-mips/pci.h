multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_PCI_H
DECL|macro|_ASM_PCI_H
mdefine_line|#define _ASM_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This file essentially defines the interface between board&n; * specific PCI code and MIPS common PCI code.  Should potentially put&n; * into include/asm/pci.h file.&n; */
macro_line|#include &lt;linux/ioport.h&gt;
multiline_comment|/*&n; * Each pci channel is a top-level PCI bus seem by CPU.  A machine  with&n; * multiple PCI channels may have multiple PCI host controllers or a&n; * single controller supporting multiple channels.&n; */
DECL|struct|pci_controller
r_struct
id|pci_controller
(brace
DECL|member|next
r_struct
id|pci_controller
op_star
id|next
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
DECL|member|mem_offset
r_int
r_int
id|mem_offset
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
DECL|member|io_offset
r_int
r_int
id|io_offset
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* For compatibility with current (as of July 2003) pciutils&n;&t;   and XFree86. Eventually will be removed. */
DECL|member|need_domain_info
r_int
r_int
id|need_domain_info
suffix:semicolon
DECL|member|iommu
r_int
id|iommu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used by boards to register their PCI busses before the actual scanning.&n; */
r_extern
r_struct
id|pci_controller
op_star
id|alloc_pci_controller
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|register_pci_controller
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
suffix:semicolon
multiline_comment|/*&n; * board supplied pci irq fixup routine&n; */
r_extern
r_int
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
suffix:semicolon
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n;   already-configured bus numbers - to be used for buggy BIOSes&n;   or architectures with incomplete PCI setup by the loader */
r_extern
r_int
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
r_extern
r_int
r_int
id|PCIBIOS_MIN_IO
suffix:semicolon
r_extern
r_int
r_int
id|PCIBIOS_MIN_MEM
suffix:semicolon
DECL|macro|PCIBIOS_MIN_CARDBUS_IO
mdefine_line|#define PCIBIOS_MIN_CARDBUS_IO&t;0x4000
r_extern
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Dynamic DMA mapping stuff.&n; * MIPS has everything mapped statically.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/*&n; * The PCI address space does equal the physical memory address space.  The&n; * networking and block device layers use this boolean for bounce buffer&n; * decisions.  This is set if any hose does not have an IOMMU.&n; */
r_extern
r_int
r_int
id|PCI_DMA_BUS_IS_PHYS
suffix:semicolon
macro_line|#ifdef CONFIG_MAPPED_DMA_IO
multiline_comment|/* pci_unmap_{single,page} is not a nop, thus... */
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
macro_line|#else /* CONFIG_MAPPED_DMA_IO  */
multiline_comment|/* pci_unmap_{page,single} is a nop so... */
DECL|macro|DECLARE_PCI_UNMAP_ADDR
mdefine_line|#define DECLARE_PCI_UNMAP_ADDR(ADDR_NAME)
DECL|macro|DECLARE_PCI_UNMAP_LEN
mdefine_line|#define DECLARE_PCI_UNMAP_LEN(LEN_NAME)
DECL|macro|pci_unmap_addr
mdefine_line|#define pci_unmap_addr(PTR, ADDR_NAME)&t;&t;(0)
DECL|macro|pci_unmap_addr_set
mdefine_line|#define pci_unmap_addr_set(PTR, ADDR_NAME, VAL)&t;do { } while (0)
DECL|macro|pci_unmap_len
mdefine_line|#define pci_unmap_len(PTR, LEN_NAME)&t;&t;(0)
DECL|macro|pci_unmap_len_set
mdefine_line|#define pci_unmap_len_set(PTR, LEN_NAME, VAL)&t;do { } while (0)
macro_line|#endif /* CONFIG_MAPPED_DMA_IO  */
multiline_comment|/* This is always fine. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(1)
r_extern
id|dma64_addr_t
id|pci_dac_page_to_dma
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
comma
r_int
id|direction
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|pci_dac_dma_to_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_dac_dma_to_offset
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
)paren
suffix:semicolon
r_extern
r_void
id|pci_dac_dma_sync_single_for_cpu
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
comma
r_int
id|len
comma
r_int
id|direction
)paren
suffix:semicolon
r_extern
r_void
id|pci_dac_dma_sync_single_for_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|dma64_addr_t
id|dma_addr
comma
r_int
id|len
comma
r_int
id|direction
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
macro_line|#ifdef CONFIG_PCI_DOMAINS
DECL|macro|pci_domain_nr
mdefine_line|#define pci_domain_nr(bus) ((struct pci_controller *)(bus)-&gt;sysdata)-&gt;index
r_static
r_inline
r_int
DECL|function|pci_name_bus
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
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|hose-&gt;need_domain_info
op_eq
l_int|0
)paren
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
id|hose-&gt;index
comma
id|bus-&gt;number
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI_DOMAINS */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* implement the pci_ DMA API in terms of the generic device dma_ one */
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
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
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
r_extern
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* _ASM_PCI_H */
eof
