macro_line|#ifndef __i386_PCI_H
DECL|macro|__i386_PCI_H
mdefine_line|#define __i386_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* for struct page */
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n;   already-configured bus numbers - to be used for buggy BIOSes&n;   or architectures with incomplete PCI setup by the loader */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;0
macro_line|#endif
r_extern
r_int
r_int
id|pci_mem_start
suffix:semicolon
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;(pci_mem_start)
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
r_int
id|bus
)paren
suffix:semicolon
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
r_void
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_struct
id|irq_routing_table
op_star
id|pcibios_get_irq_routing_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pcibios_set_irq_routing
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pin
comma
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* Dynamic DMA mapping stuff.&n; * i386 has everything mapped statically.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
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
multiline_comment|/* This is always fine. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(1)
r_static
id|__inline__
id|dma64_addr_t
DECL|function|pci_dac_page_to_dma
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
(brace
r_return
(paren
(paren
id|dma64_addr_t
)paren
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
(paren
id|dma64_addr_t
)paren
id|offset
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_struct
id|page
op_star
DECL|function|pci_dac_dma_to_page
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
(brace
r_return
id|pfn_to_page
c_func
(paren
id|dma_addr
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_int
r_int
DECL|function|pci_dac_dma_to_offset
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
(brace
r_return
(paren
id|dma_addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|pci_dac_dma_sync_single
id|pci_dac_dma_sync_single
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
(brace
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
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
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* implement the pci_ DMA API in terms of the generic device dma_ one */
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
multiline_comment|/* generic pci stuff */
macro_line|#include &lt;asm-generic/pci.h&gt;
macro_line|#endif /* __i386_PCI_H */
eof
