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
multiline_comment|/* Dynamic DMA Mapping stuff, stolen from i386&n; * &t;++ajoshi&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
multiline_comment|/* Allocate and map kernel buffer using consistent mode DMA for a device.&n; * hwdev should be valid struct pci_dev pointer for PCI devices,&n; * NULL for PCI-like buses (ISA, EISA).&n; * Returns non-NULL cpu-view pointer to the buffer if successful and&n; * sets *dma_addrp to the pci side dma address as well, else *dma_addrp&n; * is undefined.&n; */
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
multiline_comment|/* Free and unmap a consistent DMA buffer.&n; * cpu_addr is what was returned from pci_alloc_consistent,&n; * size must be the same as what as passed into pci_alloc_consistent,&n; * and likewise dma_addr must be the same as what *dma_addrp was set to.&n; *&n; * References to the memory and mappings associated with cpu_addr/dma_addr&n; * past this call are illegal.&n; */
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
multiline_comment|/* Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
DECL|function|pci_map_single
r_static
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
id|consistent_sync
c_func
(paren
id|ptr
comma
id|size
comma
id|direction
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
r_static
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
multiline_comment|/*&n; * pci_{map,unmap}_single_page maps a kernel page to a dma_addr_t. identical&n; * to pci_map_single, but takes a struct page instead of a virtual address&n; */
DECL|function|pci_map_page
r_static
r_inline
id|dma_addr_t
id|pci_map_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
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
(paren
id|page
op_minus
id|mem_map
)paren
op_star
id|PAGE_SIZE
op_plus
id|PCI_DRAM_OFFSET
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|pci_unmap_page
r_static
r_inline
r_void
id|pci_unmap_page
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|dma_address
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
multiline_comment|/* Nothing to do */
)brace
multiline_comment|/* Map a set of buffers described by scatterlist in streaming&n; * mode for DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *       The routine returns the number of addr/length pairs actually&n; *       used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
DECL|function|pci_map_sg
r_static
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
r_int
id|i
suffix:semicolon
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
multiline_comment|/*&n;&t; * temporary 2.4 hack&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sg
(braket
id|i
)braket
dot
id|page
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|sg
(braket
id|i
)braket
dot
id|dma_address
op_assign
id|page_to_bus
c_func
(paren
id|sg
(braket
id|i
)braket
dot
id|page
)paren
op_plus
id|sg
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/* Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
DECL|function|pci_unmap_sg
r_static
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
multiline_comment|/* Make physical memory consistent for a single&n; * streaming mode DMA translation after a transfer.&n; *&n; * If you perform a pci_map_single() but wish to interrogate the&n; * buffer using the cpu, yet do not wish to teardown the PCI dma&n; * mapping, you must call this function before doing so.  At the&n; * next point you give the PCI dma address back to the card, the&n; * device again owns the buffer.&n; */
DECL|function|pci_dma_sync_single
r_static
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
id|consistent_sync
c_func
(paren
id|bus_to_virt
c_func
(paren
id|dma_handle
)paren
comma
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
multiline_comment|/* Make physical memory consistent for a set of streaming&n; * mode DMA translations after a transfer.&n; *&n; * The same as pci_dma_sync_single but for a scatter-gather list,&n; * same rules and usage.&n; */
DECL|function|pci_dma_sync_sg
r_static
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
multiline_comment|/*&n; * At present there are very few 32-bit PPC machines that can have&n; * memory above the 4GB point, and we don&squot;t support that.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
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
id|dma64_addr_t
)paren
id|page_to_bus
c_func
(paren
id|page
)paren
op_plus
id|offset
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
id|mem_map
op_plus
(paren
r_int
r_int
)paren
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
multiline_comment|/* Nothing to do. */
)brace
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|macro|pci_domain_nr
mdefine_line|#define pci_domain_nr(bus) ((struct pci_controller *)(bus)-&gt;sysdata)-&gt;index
multiline_comment|/* Set the name of the bus as it appears in /proc/bus/pci */
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
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __PPC_PCI_H */
eof
