macro_line|#ifndef __PPC_PCI_H
DECL|macro|__PPC_PCI_H
mdefine_line|#define __PPC_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
r_struct
id|pci_dev
suffix:semicolon
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
multiline_comment|/*&n; * Set this to 1 if you want the kernel to re-assign all PCI&n; * bus numbers&n; */
r_extern
r_int
id|pci_assign_all_busses
suffix:semicolon
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;(pci_assign_all_busses)
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
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
multiline_comment|/*&n; * The PCI bus bridge can translate addresses issued by the processor(s)&n; * into a different address on the PCI bus.  On 32-bit cpus, we assume&n; * this mapping is 1-1, but on 64-bit systems it often isn&squot;t.&n; *&n; * Obsolete ! Drivers should now use pci_resource_to_bus&n; */
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
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS     (1)
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
multiline_comment|/*&n; * At present there are very few 32-bit PPC machines that can have&n; * memory above the 4GB point, and we don&squot;t support that.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|macro|pci_domain_nr
mdefine_line|#define pci_domain_nr(bus) ((struct pci_controller *)(bus)-&gt;sysdata)-&gt;index
multiline_comment|/* Set the name of the bus as it appears in /proc/bus/pci */
DECL|function|pci_proc_domain
r_static
r_inline
r_int
id|pci_proc_domain
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|pcibios_add_platform_entries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __PPC_PCI_H */
eof
