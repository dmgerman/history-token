macro_line|#ifndef ASMARM_PCI_H
DECL|macro|ASMARM_PCI_H
mdefine_line|#define ASMARM_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/arch/hardware.h&gt;
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
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_struct
id|pci_dev
suffix:semicolon
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
id|handle
)paren
suffix:semicolon
multiline_comment|/* Free and unmap a consistent DMA buffer.&n; * cpu_addr is what was returned from pci_alloc_consistent,&n; * size must be the same as what as passed into pci_alloc_consistent,&n; * and likewise dma_addr must be the same as what *dma_addrp was set to.&n; *&n; * References to the memory and mappings associated with cpu_addr/dma_addr&n; * past this call are illegal.&n; */
r_static
r_inline
r_void
DECL|function|pci_free_consistent
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
(brace
id|consistent_free
c_func
(paren
id|vaddr
comma
id|size
comma
id|dma_handle
)paren
suffix:semicolon
)brace
multiline_comment|/* Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
r_static
r_inline
id|dma_addr_t
DECL|function|pci_map_single
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
macro_line|#ifdef CONFIG_SA1111
r_extern
id|dma_addr_t
id|sa1111_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * for SA1111 these functions are &quot;magic&quot; and relocate buffers.  We&n;&t; * only need to do these if hwdev is non-null; otherwise we expect&n;&t; * the buffer to already be suitable for DMA.&n;&t; */
r_if
c_cond
(paren
id|hwdev
op_ne
l_int|NULL
)paren
r_return
id|sa1111_map_single
c_func
(paren
id|hwdev
comma
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Unmap a single streaming mode DMA translation.  The dma_addr and size&n; * must match what was provided for in a previous pci_map_single call.  All&n; * other usages are undefined.&n; *&n; * After this call, reads by the cpu to the buffer are guarenteed to see&n; * whatever the device wrote there.&n; */
r_static
r_inline
r_void
DECL|function|pci_unmap_single
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
macro_line|#ifdef CONFIG_SA1111
r_extern
r_void
id|sa1111_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_ne
l_int|NULL
)paren
id|sa1111_unmap_single
c_func
(paren
id|hwdev
comma
id|dma_addr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* nothing to do */
)brace
multiline_comment|/* Map a set of buffers described by scatterlist in streaming&n; * mode for DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *       The routine returns the number of addr/length pairs actually&n; *       used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
r_static
r_inline
r_int
DECL|function|pci_map_sg
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
comma
id|sg
op_increment
)paren
(brace
id|consistent_sync
c_func
(paren
id|sg-&gt;address
comma
id|sg-&gt;length
comma
id|direction
)paren
suffix:semicolon
id|sg-&gt;dma_address
op_assign
id|virt_to_bus
c_func
(paren
id|sg-&gt;address
)paren
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/* Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
r_static
r_inline
r_void
DECL|function|pci_unmap_sg
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
multiline_comment|/* nothing to do */
)brace
multiline_comment|/* Make physical memory consistent for a single&n; * streaming mode DMA translation after a transfer.&n; *&n; * If you perform a pci_map_single() but wish to interrogate the&n; * buffer using the cpu, yet do not wish to teardown the PCI dma&n; * mapping, you must call this function before doing so.  At the&n; * next point you give the PCI dma address back to the card, the&n; * device again owns the buffer.&n; */
r_static
r_inline
r_void
DECL|function|pci_dma_sync_single
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
r_static
r_inline
r_void
DECL|function|pci_dma_sync_sg
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
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nelems
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
id|consistent_sync
c_func
(paren
id|sg-&gt;address
comma
id|sg-&gt;length
comma
id|direction
)paren
suffix:semicolon
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
id|dma_addr_t
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(PDEV)&t;(0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
