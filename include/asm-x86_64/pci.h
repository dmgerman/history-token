macro_line|#ifndef __x8664_PCI_H
DECL|macro|__x8664_PCI_H
mdefine_line|#define __x8664_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/mm.h&gt; /* for struct page */
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
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
r_extern
r_int
id|no_iommu
comma
id|force_iommu
suffix:semicolon
r_extern
r_int
r_int
id|pci_mem_start
suffix:semicolon
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;(pci_mem_start)
DECL|macro|PCIBIOS_MIN_CARDBUS_IO
mdefine_line|#define PCIBIOS_MIN_CARDBUS_IO&t;0x4000
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
r_extern
r_int
(paren
op_star
id|pci_config_read
)paren
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pci_config_write
)paren
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
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
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_struct
id|pci_dev
suffix:semicolon
r_extern
r_int
id|iommu_setup
c_func
(paren
r_char
op_star
id|opt
)paren
suffix:semicolon
r_extern
id|dma_addr_t
id|bad_dma_address
suffix:semicolon
DECL|macro|pci_dma_error
mdefine_line|#define pci_dma_error(x) ((x) == bad_dma_address)
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
macro_line|#ifdef CONFIG_GART_IOMMU
multiline_comment|/* Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
r_extern
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
suffix:semicolon
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
id|addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
suffix:semicolon
multiline_comment|/*&n; * pci_{map,unmap}_single_page maps a kernel page to a dma_addr_t. identical&n; * to pci_map_single, but takes a struct page instead of a virtual address&n; */
DECL|macro|pci_map_page
mdefine_line|#define pci_map_page(dev,page,offset,size,dir) &bslash;&n;&t;pci_map_single((dev), page_address(page)+(offset), (size), (dir)) 
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
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
)brace
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
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
)brace
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions&n; *&n; * On AMD64 it mostly equals, but we set it to zero to tell some subsystems&n; * that an IOMMU is available.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(no_iommu ? 1 : 0) 
multiline_comment|/* We lie slightly when the IOMMU is forced to get the device to &n;   use SAC instead of DAC. */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(force_iommu ? 0 : 1)
macro_line|#else
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
id|dma_addr_t
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|ptr
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * This is gross, but what should I do.&n;&t; * Unfortunately drivers do not test the return value of this.&n; */
r_if
c_cond
(paren
(paren
id|addr
op_plus
id|size
)paren
op_amp
op_complement
id|hwdev-&gt;dma_mask
)paren
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
r_return
id|addr
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
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Nothing to do */
)brace
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
id|dma_addr_t
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
id|addr
op_assign
id|page_to_pfn
c_func
(paren
id|page
)paren
op_star
id|PAGE_SIZE
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_plus
id|size
)paren
op_amp
op_complement
id|hwdev-&gt;dma_mask
)paren
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
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
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
id|flush_write_buffers
c_func
(paren
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
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
id|flush_write_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;1
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;1
macro_line|#endif
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
DECL|macro|pci_unmap_page
mdefine_line|#define pci_unmap_page pci_unmap_single
multiline_comment|/* Return whether the given PCI device DMA address mask can&n; * be supported properly.  For example, if your device can&n; * only drive the low 24-bits during PCI bus mastering, then&n; * you would pass 0x00ffffff as the mask to this function.&n; */
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
id|u64
id|mask
)paren
suffix:semicolon
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
id|virt_to_page
c_func
(paren
id|__va
c_func
(paren
id|dma_addr
)paren
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
multiline_comment|/* generic pci stuff */
macro_line|#include &lt;asm-generic/pci.h&gt;
macro_line|#endif /* __x8664_PCI_H */
eof
