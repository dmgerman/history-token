macro_line|#ifndef __PPC64_PCI_H
DECL|macro|__PPC64_PCI_H
mdefine_line|#define __PPC64_PCI_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Values for the `which&squot; argument to sys_pciconfig_iobase syscall.  */
DECL|macro|IOBASE_BRIDGE_NUMBER
mdefine_line|#define IOBASE_BRIDGE_NUMBER&t;0
DECL|macro|IOBASE_MEMORY
mdefine_line|#define IOBASE_MEMORY&t;&t;1
DECL|macro|IOBASE_IO
mdefine_line|#define IOBASE_IO&t;&t;2
DECL|macro|IOBASE_ISA_IO
mdefine_line|#define IOBASE_ISA_IO           3
DECL|macro|IOBASE_ISA_MEM
mdefine_line|#define IOBASE_ISA_MEM          4
multiline_comment|/* Can be used to override the logic in pci_scan_bus for skipping&n; * already-configured bus numbers - to be used for buggy BIOSes&n; * or architectures with incomplete PCI setup by the loader.&n; */
r_extern
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
suffix:semicolon
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
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
r_struct
id|pci_dev
suffix:semicolon
DECL|macro|REG_SAVE_SIZE
mdefine_line|#define REG_SAVE_SIZE 64
multiline_comment|/************************************************************************&n; * Structure to hold the data for PCI Register Save/Restore functions.  *&n; ************************************************************************/
DECL|struct|pci_config_reg_save_area
r_struct
id|pci_config_reg_save_area
(brace
DECL|member|PciDev
r_struct
id|pci_dev
op_star
id|PciDev
suffix:semicolon
multiline_comment|/* Pointer to device(Sanity Check)     */
DECL|member|Flags
r_int
id|Flags
suffix:semicolon
multiline_comment|/* Control &amp; Info Flags                */
DECL|member|RCode
r_int
id|RCode
suffix:semicolon
multiline_comment|/* Return Code on Save/Restore         */
DECL|member|Register
r_int
id|Register
suffix:semicolon
multiline_comment|/* Pointer to current register.        */
DECL|member|Regs
id|u8
id|Regs
(braket
id|REG_SAVE_SIZE
)braket
suffix:semicolon
multiline_comment|/* Save Area                           */
)brace
suffix:semicolon
multiline_comment|/************************************************************************&n; * Functions to support device reset                                    *&n; ************************************************************************/
r_extern
r_int
id|pci_reset_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pci_save_config_regs
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|pci_config_reg_save_area
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pci_restore_config_regs
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|pci_config_reg_save_area
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|pci_card_location
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
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
r_extern
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
suffix:semicolon
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
r_extern
r_void
id|pSeries_pcibios_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/* nothing to do */
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
DECL|macro|sg_dma_address
mdefine_line|#define sg_dma_address(sg)&t;((sg)-&gt;dma_address)
DECL|macro|sg_dma_len
mdefine_line|#define sg_dma_len(sg)&t;&t;((sg)-&gt;dma_length)
DECL|macro|pci_map_page
mdefine_line|#define pci_map_page(dev, page, off, size, dir) &bslash;&n;&t;&t;pci_map_single(dev, (page_address(page) + (off)), size, dir)
DECL|macro|pci_unmap_page
mdefine_line|#define pci_unmap_page(dev,addr,sz,dir) pci_unmap_single(dev,addr,sz,dir)
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
DECL|macro|pci_dac_dma_supported
mdefine_line|#define pci_dac_dma_supported(pci_dev, mask)&t;(0)
multiline_comment|/* The PCI address space does equal the physical memory&n; * address space.  The networking and block device layers use&n; * this boolean for bounce buffer decisions.&n; */
DECL|macro|PCI_DMA_BUS_IS_PHYS
mdefine_line|#define PCI_DMA_BUS_IS_PHYS&t;(0)
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __PPC64_PCI_H */
eof
