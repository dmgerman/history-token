macro_line|#ifndef ASMARM_PCI_H
DECL|macro|ASMARM_PCI_H
mdefine_line|#define ASMARM_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/hardware.h&gt; /* for PCIBIOS_MIN_* */
macro_line|#ifdef CONFIG_SA1111
multiline_comment|/*&n; * Keep the SA1111 DMA-mapping tricks until the USB layer gets&n; * properly converted to the new DMA-mapping API, at which time&n; * most of this file can die.&n; */
DECL|macro|SA1111_FAKE_PCIDEV
mdefine_line|#define SA1111_FAKE_PCIDEV ((struct pci_dev *) 1111)
DECL|macro|pcidev_is_sa1111
mdefine_line|#define pcidev_is_sa1111(dev) (dev == SA1111_FAKE_PCIDEV)
macro_line|#else
DECL|macro|pcidev_is_sa1111
mdefine_line|#define pcidev_is_sa1111(dev) (0)
macro_line|#endif
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
multiline_comment|/*&n; * The PCI address space does equal the physical memory address space.&n; * The networking and block device layers use this boolean for bounce&n; * buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS     (0)
r_static
r_inline
r_void
op_star
DECL|function|pci_alloc_consistent
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
(brace
r_int
id|gfp
op_assign
id|GFP_ATOMIC
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
op_logical_or
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
op_logical_or
id|hwdev-&gt;dma_mask
op_ne
l_int|0xffffffff
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
r_return
id|consistent_alloc
c_func
(paren
id|gfp
comma
id|size
comma
id|handle
comma
l_int|0
)paren
suffix:semicolon
)brace
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
id|handle
)paren
(brace
id|dma_free_coherent
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|size
comma
id|vaddr
comma
id|handle
)paren
suffix:semicolon
)brace
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
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
r_return
id|sa1111_map_single
c_func
(paren
id|ptr
comma
id|size
comma
id|dir
)paren
suffix:semicolon
r_return
id|dma_map_single
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|ptr
comma
id|size
comma
id|dir
)paren
suffix:semicolon
)brace
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
id|handle
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sa1111_unmap_single
c_func
(paren
id|handle
comma
id|size
comma
id|dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
id|dma_unmap_single
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|handle
comma
id|size
comma
id|dir
)paren
suffix:semicolon
)brace
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
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
r_return
id|sa1111_map_sg
c_func
(paren
id|sg
comma
id|nents
comma
id|dir
)paren
suffix:semicolon
r_return
id|dma_map_sg
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|sg
comma
id|nents
comma
id|dir
)paren
suffix:semicolon
)brace
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
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sa1111_unmap_sg
c_func
(paren
id|sg
comma
id|nents
comma
id|dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
id|dma_unmap_sg
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|sg
comma
id|nents
comma
id|dir
)paren
suffix:semicolon
)brace
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
id|handle
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sa1111_dma_sync_single
c_func
(paren
id|handle
comma
id|size
comma
id|dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
id|dma_sync_single
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|handle
comma
id|size
comma
id|dir
)paren
suffix:semicolon
)brace
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
id|dir
)paren
(brace
r_if
c_cond
(paren
id|pcidev_is_sa1111
c_func
(paren
id|hwdev
)paren
)paren
(brace
id|sa1111_dma_sync_sg
c_func
(paren
id|sg
comma
id|nelems
comma
id|dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
id|dma_sync_sg
c_func
(paren
id|hwdev
ques
c_cond
op_amp
id|hwdev-&gt;dev
suffix:colon
l_int|NULL
comma
id|sg
comma
id|nelems
comma
id|dir
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * We don&squot;t support DAC DMA cycles.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
multiline_comment|/*&n; * Return the index of the PCI controller for device PDEV.&n; */
DECL|macro|pci_controller_num
mdefine_line|#define pci_controller_num(PDEV)&t;(0)
macro_line|#if defined(CONFIG_SA1111) &amp;&amp; !defined(CONFIG_PCI)
multiline_comment|/*&n; * SA-1111 needs these prototypes even when !defined(CONFIG_PCI)&n; *&n; * kmem_cache style wrapper around pci_alloc_consistent()&n; */
r_struct
id|pci_pool
op_star
id|pci_pool_create
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|size
comma
r_int
id|align
comma
r_int
id|allocation
)paren
suffix:semicolon
r_void
id|pci_pool_destroy
(paren
r_struct
id|pci_pool
op_star
id|pool
)paren
suffix:semicolon
r_void
op_star
id|pci_pool_alloc
(paren
r_struct
id|pci_pool
op_star
id|pool
comma
r_int
id|flags
comma
id|dma_addr_t
op_star
id|handle
)paren
suffix:semicolon
r_void
id|pci_pool_free
(paren
r_struct
id|pci_pool
op_star
id|pool
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|addr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Whether pci_unmap_{single,page} is a nop depends upon the&n; * configuration.&n; */
macro_line|#if defined(CONFIG_PCI) || defined(CONFIG_SA1111)
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
macro_line|#else
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
macro_line|#endif
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
macro_line|#endif
eof
