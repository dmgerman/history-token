multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_PCI_H
DECL|macro|_ASM_PCI_H
mdefine_line|#define _ASM_PCI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
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
multiline_comment|/*&n; * Dynamic DMA mapping stuff.&n; * MIPS has everything mapped statically.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if defined(CONFIG_DDB5074) || defined(CONFIG_DDB5476)
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
multiline_comment|/*&n; * The PCI address space does equal the physical memory address space.  The&n; * networking and block device layers use this boolean for bounce buffer&n; * decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
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
DECL|function|pci_dac_page_to_dma
r_static
r_inline
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
(brace
id|dma64_addr_t
id|addr
op_assign
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
r_return
(paren
id|dma64_addr_t
)paren
id|bus_to_baddr
c_func
(paren
id|pdev-&gt;bus
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pci_dac_dma_to_page
r_static
r_inline
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
(brace
r_int
r_int
id|poff
op_assign
id|baddr_to_bus
c_func
(paren
id|pdev-&gt;bus
comma
id|dma_addr
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
id|mem_map
op_plus
id|poff
suffix:semicolon
)brace
DECL|function|pci_dac_dma_to_offset
r_static
r_inline
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
(brace
r_return
id|dma_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
)brace
DECL|function|pci_dac_dma_sync_single
r_static
r_inline
r_void
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
r_int
r_int
id|addr
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
id|addr
op_assign
id|baddr_to_bus
c_func
(paren
id|pdev-&gt;bus
comma
id|dma_addr
)paren
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|addr
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* implement the pci_ DMA API in terms of the generic device dma_ one */
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
multiline_comment|/* generic pci stuff */
macro_line|#include &lt;asm-generic/pci.h&gt;
macro_line|#endif /* _ASM_PCI_H */
eof
