multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_PCI_H
DECL|macro|_ASM_PCI_H
mdefine_line|#define _ASM_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
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
multiline_comment|/*&n; * Dynamic DMA mapping stuff.&n; * MIPS has everything mapped statically.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if (defined(CONFIG_DDB5074) || defined(CONFIG_DDB5476))
DECL|macro|PCIBIOS_MIN_IO
macro_line|#undef PCIBIOS_MIN_IO
DECL|macro|PCIBIOS_MIN_MEM
macro_line|#undef PCIBIOS_MIN_MEM
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x0100000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x1000000
macro_line|#endif
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/*&n; * Allocate and map kernel buffer using consistent mode DMA for a device.&n; * hwdev should be valid struct pci_dev pointer for PCI devices,&n; * NULL for PCI-like buses (ISA, EISA).&n; * Returns non-NULL cpu-view pointer to the buffer if successful and&n; * sets *dma_addrp to the pci side dma address as well, else *dma_addrp&n; * is undefined.&n; */
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
multiline_comment|/*&n; * Free and unmap a consistent DMA buffer.&n; * cpu_addr is what was returned from pci_alloc_consistent,&n; * size must be the same as what as passed into pci_alloc_consistent,&n; * and likewise dma_addr must be the same as what *dma_addrp was set to.&n; *&n; * References to the memory and mappings associated with cpu_addr/dma_addr&n; * past this call are illegal.&n; */
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
multiline_comment|/*&n; * Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
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
macro_line|#ifndef CONFIG_COHERENT_IO
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_return
id|virt_to_bus
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unmap a single streaming mode DMA translation.  The dma_addr and size&n; * must match what was provided for in a previous pci_map_single call.  All&n; * other usages are undefined.&n; *&n; * After this call, reads by the cpu to the buffer are guarenteed to see&n; * whatever the device wrote there.&n; */
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
multiline_comment|/* Nothing to do */
)brace
multiline_comment|/*&n; * Map a set of buffers described by scatterlist in streaming&n; * mode for DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *       The routine returns the number of addr/length pairs actually&n; *       used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
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
macro_line|#ifndef CONFIG_COHERENT_IO
r_int
id|i
suffix:semicolon
macro_line|#endif
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
macro_line|#ifndef CONFIG_COHERENT_IO
multiline_comment|/* Make sure that gcc doesn&squot;t leave the empty loop body.  */
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
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|sg-&gt;address
comma
id|sg-&gt;length
)paren
suffix:semicolon
macro_line|#endif
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/*&n; * Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
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
multiline_comment|/* Nothing to do */
)brace
multiline_comment|/*&n; * Make physical memory consistent for a single&n; * streaming mode DMA translation after a transfer.&n; *&n; * If you perform a pci_map_single() but wish to interrogate the&n; * buffer using the cpu, yet do not wish to teardown the PCI dma&n; * mapping, you must call this function before doing so.  At the&n; * next point you give the PCI dma address back to the card, the&n; * device again owns the buffer.&n; */
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
macro_line|#ifndef CONFIG_COHERENT_IO
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|bus_to_virt
c_func
(paren
id|dma_handle
)paren
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Make physical memory consistent for a set of streaming&n; * mode DMA translations after a transfer.&n; *&n; * The same as pci_dma_sync_single but for a scatter-gather list,&n; * same rules and usage.&n; */
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
macro_line|#ifndef CONFIG_COHERENT_IO
r_int
id|i
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Make sure that gcc doesn&squot;t leave the empty loop body.  */
macro_line|#ifndef CONFIG_COHERENT_IO
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
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|sg-&gt;address
comma
id|sg-&gt;length
)paren
suffix:semicolon
macro_line|#endif
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
id|u64
id|mask
)paren
(brace
multiline_comment|/*&n;&t; * we fall back to GFP_DMA when the mask isn&squot;t all 1s,&n;&t; * so we can&squot;t guarantee allocations that must be&n;&t; * within a tighter range than GFP_DMA..&n;&t; */
r_if
c_cond
(paren
id|mask
OL
l_int|0x1fffffff
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Return the index of the PCI controller for device. */
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(pdev)&t;(0)
multiline_comment|/*&n; * These macros should be used after a pci_map_sg call has been done&n; * to get bus addresses of each of the SG entries and their lengths.&n; * You should only work with the number of sg entries pci_map_sg&n; * returns, or alternatively stop on the first sg_dma_len(sg) which&n; * is 0.&n; */
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;(virt_to_bus((sg)-&gt;address))
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;length)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_PCI_H */
eof
