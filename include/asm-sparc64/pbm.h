multiline_comment|/* $Id: pbm.h,v 1.23 2001/01/11 16:26:45 davem Exp $&n; * pbm.h: UltraSparc PCI controller software state.&n; *&n; * Copyright (C) 1997, 1998, 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __SPARC64_PBM_H
DECL|macro|__SPARC64_PBM_H
mdefine_line|#define __SPARC64_PBM_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* The abstraction used here is that there are PCI controllers,&n; * each with one (Sabre) or two (PSYCHO/SCHIZO) PCI bus modules&n; * underneath.  Each PCI bus module uses an IOMMU (shared by both&n; * PBMs of a controller, or per-PBM), and if a streaming buffer&n; * is present, each PCI bus module has it&squot;s own. (ie. the IOMMU&n; * might be shared between PBMs, the STC is never shared)&n; * Furthermore, each PCI bus module controls it&squot;s own autonomous&n; * PCI bus.&n; */
DECL|macro|PBM_LOGCLUSTERS
mdefine_line|#define PBM_LOGCLUSTERS 3
DECL|macro|PBM_NCLUSTERS
mdefine_line|#define PBM_NCLUSTERS (1 &lt;&lt; PBM_LOGCLUSTERS)
r_struct
id|pci_controller_info
suffix:semicolon
multiline_comment|/* This contains the software state necessary to drive a PCI&n; * controller&squot;s IOMMU.&n; */
DECL|struct|pci_iommu
r_struct
id|pci_iommu
(brace
multiline_comment|/* This protects the controller&squot;s IOMMU and all&n;&t; * streaming buffers underneath.&n;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Context allocator. */
DECL|member|iommu_cur_ctx
r_int
r_int
id|iommu_cur_ctx
suffix:semicolon
multiline_comment|/* IOMMU page table, a linear array of ioptes. */
DECL|member|page_table
id|iopte_t
op_star
id|page_table
suffix:semicolon
multiline_comment|/* The page table itself. */
DECL|member|page_table_sz_bits
r_int
id|page_table_sz_bits
suffix:semicolon
multiline_comment|/* log2 of ow many pages does it map? */
multiline_comment|/* Base PCI memory space address where IOMMU mappings&n;&t; * begin.&n;&t; */
DECL|member|page_table_map_base
id|u32
id|page_table_map_base
suffix:semicolon
multiline_comment|/* IOMMU Controller Registers */
DECL|member|iommu_control
r_int
r_int
id|iommu_control
suffix:semicolon
multiline_comment|/* IOMMU control register */
DECL|member|iommu_tsbbase
r_int
r_int
id|iommu_tsbbase
suffix:semicolon
multiline_comment|/* IOMMU page table base register */
DECL|member|iommu_flush
r_int
r_int
id|iommu_flush
suffix:semicolon
multiline_comment|/* IOMMU page flush register */
DECL|member|iommu_ctxflush
r_int
r_int
id|iommu_ctxflush
suffix:semicolon
multiline_comment|/* IOMMU context flush register */
multiline_comment|/* This is a register in the PCI controller, which if&n;&t; * read will have no side-effects but will guarentee&n;&t; * completion of all previous writes into IOMMU/STC.&n;&t; */
DECL|member|write_complete_reg
r_int
r_int
id|write_complete_reg
suffix:semicolon
multiline_comment|/* The lowest used consistent mapping entry.  Since&n;&t; * we allocate consistent maps out of cluster 0 this&n;&t; * is relative to the beginning of closter 0.&n;&t; */
DECL|member|lowest_consistent_map
id|u32
id|lowest_consistent_map
suffix:semicolon
multiline_comment|/* If PBM_NCLUSTERS is ever decreased to 4 or lower,&n;&t; * or if largest supported page_table_sz * 8K goes above&n;&t; * 2GB, you must increase the size of the type of&n;&t; * these counters.  You have been duly warned. -DaveM&n;&t; */
r_struct
(brace
DECL|member|next
id|u16
id|next
suffix:semicolon
DECL|member|flush
id|u16
id|flush
suffix:semicolon
DECL|member|alloc_info
)brace
id|alloc_info
(braket
id|PBM_NCLUSTERS
)braket
suffix:semicolon
multiline_comment|/* Here a PCI controller driver describes the areas of&n;&t; * PCI memory space where DMA to/from physical memory&n;&t; * are addressed.  Drivers interrogate the PCI layer&n;&t; * if their device has addressing limitations.  They&n;&t; * do so via pci_dma_supported, and pass in a mask of&n;&t; * DMA address bits their device can actually drive.&n;&t; *&n;&t; * The test for being usable is:&n;&t; * &t;(device_mask &amp; dma_addr_mask) == dma_addr_mask&n;&t; */
DECL|member|dma_addr_mask
id|u32
id|dma_addr_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This describes a PCI bus module&squot;s streaming buffer. */
DECL|struct|pci_strbuf
r_struct
id|pci_strbuf
(brace
DECL|member|strbuf_enabled
r_int
id|strbuf_enabled
suffix:semicolon
multiline_comment|/* Present and using it? */
multiline_comment|/* Streaming Buffer Control Registers */
DECL|member|strbuf_control
r_int
r_int
id|strbuf_control
suffix:semicolon
multiline_comment|/* STC control register */
DECL|member|strbuf_pflush
r_int
r_int
id|strbuf_pflush
suffix:semicolon
multiline_comment|/* STC page flush register */
DECL|member|strbuf_fsync
r_int
r_int
id|strbuf_fsync
suffix:semicolon
multiline_comment|/* STC flush synchronization reg */
DECL|member|strbuf_ctxflush
r_int
r_int
id|strbuf_ctxflush
suffix:semicolon
multiline_comment|/* STC context flush register */
DECL|member|strbuf_ctxmatch_base
r_int
r_int
id|strbuf_ctxmatch_base
suffix:semicolon
multiline_comment|/* STC context flush match reg */
DECL|member|strbuf_flushflag_pa
r_int
r_int
id|strbuf_flushflag_pa
suffix:semicolon
multiline_comment|/* Physical address of flush flag */
DECL|member|strbuf_flushflag
r_volatile
r_int
r_int
op_star
id|strbuf_flushflag
suffix:semicolon
multiline_comment|/* The flush flag itself */
multiline_comment|/* And this is the actual flush flag area.&n;&t; * We allocate extra because the chips require&n;&t; * a 64-byte aligned area.&n;&t; */
DECL|member|__flushflag_buf
r_volatile
r_int
r_int
id|__flushflag_buf
(braket
(paren
l_int|64
op_plus
(paren
l_int|64
op_minus
l_int|1
)paren
)paren
op_div
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_STC_FLUSHFLAG_INIT
mdefine_line|#define PCI_STC_FLUSHFLAG_INIT(STC) &bslash;&n;&t;(*((STC)-&gt;strbuf_flushflag) = 0UL)
DECL|macro|PCI_STC_FLUSHFLAG_SET
mdefine_line|#define PCI_STC_FLUSHFLAG_SET(STC) &bslash;&n;&t;(*((STC)-&gt;strbuf_flushflag) != 0UL)
multiline_comment|/* There can be quite a few ranges and interrupt maps on a PCI&n; * segment.  Thus...&n; */
DECL|macro|PROM_PCIRNG_MAX
mdefine_line|#define PROM_PCIRNG_MAX&t;&t;64
DECL|macro|PROM_PCIIMAP_MAX
mdefine_line|#define PROM_PCIIMAP_MAX&t;64
DECL|struct|pci_pbm_info
r_struct
id|pci_pbm_info
(brace
multiline_comment|/* PCI controller we sit under. */
DECL|member|parent
r_struct
id|pci_controller_info
op_star
id|parent
suffix:semicolon
multiline_comment|/* Name used for top-level resources. */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* OBP specific information. */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|pbm_ranges
r_struct
id|linux_prom_pci_ranges
id|pbm_ranges
(braket
id|PROM_PCIRNG_MAX
)braket
suffix:semicolon
DECL|member|num_pbm_ranges
r_int
id|num_pbm_ranges
suffix:semicolon
DECL|member|pbm_intmap
r_struct
id|linux_prom_pci_intmap
id|pbm_intmap
(braket
id|PROM_PCIIMAP_MAX
)braket
suffix:semicolon
DECL|member|num_pbm_intmap
r_int
id|num_pbm_intmap
suffix:semicolon
DECL|member|pbm_intmask
r_struct
id|linux_prom_pci_intmask
id|pbm_intmask
suffix:semicolon
multiline_comment|/* PBM I/O and Memory space resources. */
DECL|member|io_space
r_struct
id|resource
id|io_space
suffix:semicolon
DECL|member|mem_space
r_struct
id|resource
id|mem_space
suffix:semicolon
multiline_comment|/* State of 66MHz capabilities on this PBM. */
DECL|member|is_66mhz_capable
r_int
id|is_66mhz_capable
suffix:semicolon
DECL|member|all_devs_66mhz
r_int
id|all_devs_66mhz
suffix:semicolon
multiline_comment|/* This PBM&squot;s streaming buffer. */
DECL|member|stc
r_struct
id|pci_strbuf
id|stc
suffix:semicolon
multiline_comment|/* IOMMU state, potentially shared by both PBM segments. */
DECL|member|iommu
r_struct
id|pci_iommu
op_star
id|iommu
suffix:semicolon
multiline_comment|/* Now things for the actual PCI bus probes. */
DECL|member|pci_first_busno
r_int
r_int
id|pci_first_busno
suffix:semicolon
DECL|member|pci_last_busno
r_int
r_int
id|pci_last_busno
suffix:semicolon
DECL|member|pci_bus
r_struct
id|pci_bus
op_star
id|pci_bus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_controller_info
r_struct
id|pci_controller_info
(brace
multiline_comment|/* List of all PCI controllers. */
DECL|member|next
r_struct
id|pci_controller_info
op_star
id|next
suffix:semicolon
multiline_comment|/* Physical address base of controller registers&n;&t; * and PCI config space.&n;&t; */
DECL|member|controller_regs
r_int
r_int
id|controller_regs
suffix:semicolon
DECL|member|config_space
r_int
r_int
id|config_space
suffix:semicolon
multiline_comment|/* Opaque 32-bit system bus Port ID. */
DECL|member|portid
id|u32
id|portid
suffix:semicolon
multiline_comment|/* Each controller gets a unique index, used mostly for&n;&t; * error logging purposes.&n;&t; */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* The PCI bus modules controlled by us. */
DECL|member|pbm_A
r_struct
id|pci_pbm_info
id|pbm_A
suffix:semicolon
DECL|member|pbm_B
r_struct
id|pci_pbm_info
id|pbm_B
suffix:semicolon
multiline_comment|/* Operations which are controller specific. */
DECL|member|scan_bus
r_void
(paren
op_star
id|scan_bus
)paren
(paren
r_struct
id|pci_controller_info
op_star
)paren
suffix:semicolon
DECL|member|irq_build
r_int
r_int
(paren
op_star
id|irq_build
)paren
(paren
r_struct
id|pci_controller_info
op_star
comma
r_struct
id|pci_dev
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|base_address_update
r_void
(paren
op_star
id|base_address_update
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|resource_adjust
r_void
(paren
op_star
id|resource_adjust
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|resource
op_star
comma
r_struct
id|resource
op_star
)paren
suffix:semicolon
multiline_comment|/* Now things for the actual PCI bus probes. */
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|pci_first_busno
r_int
r_int
id|pci_first_busno
suffix:semicolon
DECL|member|pci_last_busno
r_int
r_int
id|pci_last_busno
suffix:semicolon
DECL|member|starfire_cookie
r_void
op_star
id|starfire_cookie
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PCI devices which are not bridges have this placed in their pci_dev&n; * sysdata member.  This makes OBP aware PCI device drivers easier to&n; * code.&n; */
DECL|struct|pcidev_cookie
r_struct
id|pcidev_cookie
(brace
DECL|member|pbm
r_struct
id|pci_pbm_info
op_star
id|pbm
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_regs
r_struct
id|linux_prom_pci_registers
id|prom_regs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_prom_regs
r_int
id|num_prom_regs
suffix:semicolon
DECL|member|prom_assignments
r_struct
id|linux_prom_pci_registers
id|prom_assignments
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_prom_assignments
r_int
id|num_prom_assignments
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Currently these are the same across all PCI controllers&n; * we support.  Someday they may not be...&n; */
DECL|macro|PCI_IRQ_IGN
mdefine_line|#define PCI_IRQ_IGN&t;0x000007c0&t;/* Interrupt Group Number */
DECL|macro|PCI_IRQ_INO
mdefine_line|#define PCI_IRQ_INO&t;0x0000003f&t;/* Interrupt Number */
macro_line|#endif /* !(__SPARC64_PBM_H) */
eof
