macro_line|#ifndef __PPC_PCI_H
DECL|macro|__PPC_PCI_H
mdefine_line|#define __PPC_PCI_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* Values for the `which&squot; argument to sys_pciconfig_iobase syscall.  */
DECL|macro|IOBASE_BRIDGE_NUMBER
mdefine_line|#define IOBASE_BRIDGE_NUMBER&t;0
DECL|macro|IOBASE_MEMORY
mdefine_line|#define IOBASE_MEMORY&t;&t;1
DECL|macro|IOBASE_IO
mdefine_line|#define IOBASE_IO&t;&t;2
DECL|macro|IOBASE_ISA_IO
mdefine_line|#define IOBASE_ISA_IO&t;&t;3
DECL|macro|IOBASE_ISA_MEM
mdefine_line|#define IOBASE_ISA_MEM&t;&t;4
r_extern
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x10000000
DECL|function|pcibios_set_master
r_extern
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
r_extern
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
r_extern
r_int
r_int
id|pci_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/*&n; * The PCI bus bridge can translate addresses issued by the processor(s)&n; * into a different address on the PCI bus.  On 32-bit cpus, we assume&n; * this mapping is 1-1, but on 64-bit systems it often isn&squot;t.&n; * &n; * Obsolete ! Drivers should now use pci_resource_to_bus&n; */
r_extern
r_int
r_int
id|phys_to_bus
c_func
(paren
r_int
r_int
id|pa
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_phys_to_bus
c_func
(paren
r_int
r_int
id|pa
comma
r_int
id|busnr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_bus_to_phys
c_func
(paren
r_int
r_int
id|ba
comma
r_int
id|busnr
)paren
suffix:semicolon
multiline_comment|/* Dynamic DMA Mapping stuff&n; * &t;++ajoshi&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|pci_dev
suffix:semicolon
r_extern
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
suffix:semicolon
r_extern
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
suffix:semicolon
DECL|function|pci_map_single
r_extern
r_inline
id|dma_addr_t
id|pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|virt_to_bus
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
DECL|function|pci_unmap_single
r_extern
r_inline
r_void
id|pci_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
DECL|function|pci_map_sg
r_extern
r_inline
r_int
id|pci_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|nents
suffix:semicolon
)brace
DECL|function|pci_unmap_sg
r_extern
r_inline
r_void
id|pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
DECL|function|pci_dma_sync_single
r_extern
r_inline
r_void
id|pci_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
DECL|function|pci_dma_sync_sg
r_extern
r_inline
r_void
id|pci_dma_sync_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nelems
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
multiline_comment|/* Return whether the given PCI device DMA address mask can&n; * be supported properly.  For example, if your device can&n; * only drive the low 24-bits during PCI bus mastering, then&n; * you would pass 0x00ffffff as the mask to this function.&n; */
DECL|function|pci_dma_supported
r_extern
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
id|dma_addr_t
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
r_extern
r_int
id|pci_controller_num
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* Map a range of PCI memory or I/O space for a device into user space */
r_int
id|pci_mmap_page_range
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
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
multiline_comment|/* Tell drivers/pci/proc.c that we have pci_mmap_page_range() */
DECL|macro|HAVE_PCI_MMAP
mdefine_line|#define HAVE_PCI_MMAP&t;1
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;(virt_to_bus((sg)-&gt;address))
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;length)
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __PPC_PCI_H */
eof
