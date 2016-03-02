macro_line|#ifndef __ASM_SH_PCI_H
DECL|macro|__ASM_SH_PCI_H
mdefine_line|#define __ASM_SH_PCI_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/dma-mapping.h&gt;
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n;   already-configured bus numbers - to be used for buggy BIOSes&n;   or architectures with incomplete PCI setup by the loader */
DECL|macro|pcibios_assign_all_busses
mdefine_line|#define pcibios_assign_all_busses()&t;1
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
multiline_comment|/*&n; * A board can define one or more PCI channels that represent built-in (or&n; * external) PCI controllers.&n; */
DECL|struct|pci_channel
r_struct
id|pci_channel
(brace
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
DECL|member|first_devfn
r_int
id|first_devfn
suffix:semicolon
DECL|member|last_devfn
r_int
id|last_devfn
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Each board initializes this array and terminates it with a NULL entry.&n; */
r_extern
r_struct
id|pci_channel
id|board_pci_channels
(braket
)braket
suffix:semicolon
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;board_pci_channels-&gt;io_resource-&gt;start
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;board_pci_channels-&gt;mem_resource-&gt;start
r_struct
id|pci_dev
suffix:semicolon
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
multiline_comment|/* Dynamic DMA mapping stuff.&n; * SuperH has everything mapped statically like x86.&n; */
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(1)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* pci_unmap_{single,page} being a nop depends upon the&n; * configuration.&n; */
macro_line|#ifdef CONFIG_SH_PCIDMA_NONCOHERENT
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
multiline_comment|/* Not supporting more than 32-bit PCI bus addresses now, but&n; * must satisfy references to this function.  Change if needed.&n; */
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask) (0)
multiline_comment|/* These macros should be used after a pci_map_sg call has been done&n; * to get bus addresses of each of the SG entries and their lengths.&n; * You should only work with the number of sg entries pci_map_sg&n; * returns, or alternatively stop on the first sg_dma_len(sg) which&n; * is 0.&n; */
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;(virt_to_bus((sg)-&gt;dma_address))
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;length)
multiline_comment|/* Board-specific fixup routines. */
r_extern
r_void
id|pcibios_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_AUTO
r_extern
r_int
id|pciauto_assign_resources
c_func
(paren
r_int
id|busno
comma
r_struct
id|pci_channel
op_star
id|hose
)paren
suffix:semicolon
macro_line|#endif
DECL|function|pcibios_add_platform_entries
r_static
r_inline
r_void
id|pcibios_add_platform_entries
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* generic pci stuff */
macro_line|#include &lt;asm-generic/pci.h&gt;
multiline_comment|/* generic DMA-mapping stuff */
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
macro_line|#endif /* __ASM_SH_PCI_H */
eof
