macro_line|#ifndef __PPC64_PCI_H
DECL|macro|__PPC64_PCI_H
mdefine_line|#define __PPC64_PCI_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm-generic/pci-dma-compat.h&gt;
DECL|macro|PCIBIOS_MIN_IO
mdefine_line|#define PCIBIOS_MIN_IO&t;&t;0x1000
DECL|macro|PCIBIOS_MIN_MEM
mdefine_line|#define PCIBIOS_MIN_MEM&t;&t;0x10000000
r_struct
id|pci_dev
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|macro|pcibios_scan_all_fns
mdefine_line|#define pcibios_scan_all_fns(a, b)&t;0
macro_line|#else
r_extern
r_int
id|pcibios_scan_all_fns
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
suffix:semicolon
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
DECL|macro|HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ
mdefine_line|#define HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ
DECL|function|pci_get_legacy_ide_irq
r_static
r_inline
r_int
id|pci_get_legacy_ide_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.pci_get_legacy_ide_irq
)paren
r_return
id|ppc_md
dot
id|pci_get_legacy_ide_irq
c_func
(paren
id|dev
comma
id|channel
)paren
suffix:semicolon
r_return
id|channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
)brace
DECL|macro|HAVE_ARCH_PCI_MWI
mdefine_line|#define HAVE_ARCH_PCI_MWI 1
DECL|function|pcibios_prep_mwi
r_static
r_inline
r_int
id|pcibios_prep_mwi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * We would like to avoid touching the cacheline size or MWI bit&n;&t; * but we cant do that with the current pcibios_prep_mwi &n;&t; * interface. pSeries firmware sets the cacheline size (which is not&n;&t; * the cpu cacheline size in all cases) and hardware treats MWI &n;&t; * the same as memory write. So we dont touch the cacheline size&n;&t; * here and allow the generic code to set the MWI bit.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|dma_mapping_ops
id|pci_dma_ops
suffix:semicolon
multiline_comment|/* For DAC DMA, we currently don&squot;t support it by default, but&n; * we let the platform override this&n; */
DECL|function|pci_dac_dma_supported
r_static
r_inline
r_int
id|pci_dac_dma_supported
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
r_if
c_cond
(paren
id|pci_dma_ops.dac_dma_supported
)paren
r_return
id|pci_dma_ops
dot
id|dac_dma_supported
c_func
(paren
op_amp
id|hwdev-&gt;dev
comma
id|mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|pci_domain_nr
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* Decide whether to display the domain number in /proc */
r_extern
r_int
id|pci_proc_domain
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_struct
id|vm_area_struct
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
multiline_comment|/* pci_unmap_{single,page} is not a nop, thus... */
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
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(0)
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
r_int
id|unmap_bus_range
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_int
id|remap_bus_range
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|pcibios_fixup_device_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|init_phb_dynamic
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
r_extern
r_int
id|pci_read_irq_line
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
r_struct
id|file
suffix:semicolon
r_extern
id|pgprot_t
id|pci_phys_mem_access_prot
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __PPC64_PCI_H */
eof
