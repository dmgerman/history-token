macro_line|#ifndef __ALPHA_PCI_H
DECL|macro|__ALPHA_PCI_H
mdefine_line|#define __ALPHA_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * The following structure is used to manage multiple PCI busses.&n; */
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|resource
suffix:semicolon
r_struct
id|pci_iommu_arena
suffix:semicolon
multiline_comment|/* A controller.  Used to manage multiple PCI busses.  */
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
DECL|member|io_space
r_struct
id|resource
op_star
id|io_space
suffix:semicolon
DECL|member|mem_space
r_struct
id|resource
op_star
id|mem_space
suffix:semicolon
multiline_comment|/* The following are for reporting to userland.  The invariant is&n;&t;   that if we report a BWX-capable dense memory, we do not report&n;&t;   a sparse memory at all, even if it exists.  */
DECL|member|sparse_mem_base
r_int
r_int
id|sparse_mem_base
suffix:semicolon
DECL|member|dense_mem_base
r_int
r_int
id|dense_mem_base
suffix:semicolon
DECL|member|sparse_io_base
r_int
r_int
id|sparse_io_base
suffix:semicolon
DECL|member|dense_io_base
r_int
r_int
id|dense_io_base
suffix:semicolon
multiline_comment|/* This one&squot;s for the kernel only.  It&squot;s in KSEG somewhere.  */
DECL|member|config_space_base
r_int
r_int
id|config_space_base
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|first_busno
r_int
r_int
id|first_busno
suffix:semicolon
DECL|member|last_busno
r_int
r_int
id|last_busno
suffix:semicolon
DECL|member|sg_pci
r_struct
id|pci_iommu_arena
op_star
id|sg_pci
suffix:semicolon
DECL|member|sg_isa
r_struct
id|pci_iommu_arena
op_star
id|sg_isa
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Override the logic in pci_scan_bus for skipping already-configured&n;   bus numbers.  */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;alpha_mv.min_io_address
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;alpha_mv.min_mem_address
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
multiline_comment|/* IOMMU controls.  */
multiline_comment|/* Allocate and map kernel buffer using consistant mode DMA for PCI&n;   device.  Returns non-NULL cpu-view pointer to the buffer if&n;   successful and sets *DMA_ADDRP to the pci side dma address as well,&n;   else DMA_ADDRP is undefined.  */
r_extern
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
id|dma_addr_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Free and unmap a consistant DMA buffer.  CPU_ADDR and DMA_ADDR must&n;   be values that were returned from pci_alloc_consistant.  SIZE must&n;   be the same as what as passed into pci_alloc_consistant.&n;   References to the memory and mappings assosciated with CPU_ADDR or&n;   DMA_ADDR past this call are illegal.  */
r_extern
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
r_void
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/* Map a single buffer of the indicate size for PCI DMA in streaming&n;   mode.  The 32-bit PCI bus mastering address to use is returned.&n;   Once the device is given the dma address, the device owns this memory&n;   until either pci_unmap_single or pci_dma_sync_single is performed.  */
r_extern
id|dma_addr_t
id|pci_map_single
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
multiline_comment|/* Unmap a single streaming mode DMA translation.  The DMA_ADDR and&n;   SIZE must match what was provided for in a previous pci_map_single&n;   call.  All other usages are undefined.  After this call, reads by&n;   the cpu to the buffer are guarenteed to see whatever the device&n;   wrote there.  */
r_extern
r_void
id|pci_unmap_single
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
multiline_comment|/* Map a set of buffers described by scatterlist in streaming mode for&n;   PCI DMA.  This is the scather-gather version of the above&n;   pci_map_single interface.  Here the scatter gather list elements&n;   are each tagged with the appropriate PCI dma address and length.&n;   They are obtained via sg_dma_{address,length}(SG).&n;&n;   NOTE: An implementation may be able to use a smaller number of DMA&n;   address/length pairs than there are SG table elements.  (for&n;   example via virtual mapping capabilities) The routine returns the&n;   number of addr/length pairs actually used, at most nents.&n;&n;   Device ownership issues as mentioned above for pci_map_single are&n;   the same here.  */
r_extern
r_int
id|pci_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Unmap a set of streaming mode DMA translations.  Again, cpu read&n;   rules concerning calls here are the same as for pci_unmap_single()&n;   above.  */
r_extern
r_void
id|pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Make physical memory consistant for a single streaming mode DMA&n;   translation after a transfer.&n;&n;   If you perform a pci_map_single() but wish to interrogate the&n;   buffer using the cpu, yet do not wish to teardown the PCI dma&n;   mapping, you must call this function before doing so.  At the next&n;   point you give the PCI dma address back to the card, the device&n;   again owns the buffer.  */
r_extern
r_inline
r_void
DECL|function|pci_dma_sync_single
id|pci_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
multiline_comment|/* Nothing to do.  */
)brace
multiline_comment|/* Make physical memory consistant for a set of streaming mode DMA&n;   translations after a transfer.  The same as pci_dma_sync_single but&n;   for a scatter-gather list, same rules and usage.  */
r_extern
r_inline
r_void
DECL|function|pci_dma_sync_sg
id|pci_dma_sync_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
multiline_comment|/* Nothing to do.  */
)brace
multiline_comment|/* Return whether the given PCI device DMA address mask can&n;   be supported properly.  For example, if your device can&n;   only drive the low 24-bits during PCI bus mastering, then&n;   you would pass 0x00ffffff as the mask to this function.  */
r_extern
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
suffix:semicolon
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
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Values for the `which&squot; argument to sys_pciconfig_iobase.  */
DECL|macro|IOBASE_HOSE
mdefine_line|#define IOBASE_HOSE&t;&t;0
DECL|macro|IOBASE_SPARSE_MEM
mdefine_line|#define IOBASE_SPARSE_MEM&t;1
DECL|macro|IOBASE_DENSE_MEM
mdefine_line|#define IOBASE_DENSE_MEM&t;2
DECL|macro|IOBASE_SPARSE_IO
mdefine_line|#define IOBASE_SPARSE_IO&t;3
DECL|macro|IOBASE_DENSE_IO
mdefine_line|#define IOBASE_DENSE_IO&t;&t;4
DECL|macro|IOBASE_ROOT_BUS
mdefine_line|#define IOBASE_ROOT_BUS&t;&t;5
DECL|macro|IOBASE_FROM_HOSE
mdefine_line|#define IOBASE_FROM_HOSE&t;0x10000
macro_line|#endif /* __ALPHA_PCI_H */
eof
