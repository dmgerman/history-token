multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIIO_PRIVATE_H
DECL|macro|_ASM_SN_PCI_PCIIO_PRIVATE_H
mdefine_line|#define _ASM_SN_PCI_PCIIO_PRIVATE_H
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
multiline_comment|/*&n; * pciio_private.h -- private definitions for pciio&n; * PCI drivers should NOT include this file.&n; */
macro_line|#ident &quot;sys/PCI/pciio_private: $Revision: 1.13 $&quot;
multiline_comment|/*&n; * All PCI providers set up PIO using this information.&n; */
DECL|struct|pciio_piomap_s
r_struct
id|pciio_piomap_s
(brace
DECL|member|pp_flags
r_int
id|pp_flags
suffix:semicolon
multiline_comment|/* PCIIO_PIOMAP flags */
DECL|member|pp_dev
id|devfs_handle_t
id|pp_dev
suffix:semicolon
multiline_comment|/* associated pci card */
DECL|member|pp_slot
id|pciio_slot_t
id|pp_slot
suffix:semicolon
multiline_comment|/* which slot the card is in */
DECL|member|pp_space
id|pciio_space_t
id|pp_space
suffix:semicolon
multiline_comment|/* which address space */
DECL|member|pp_pciaddr
id|iopaddr_t
id|pp_pciaddr
suffix:semicolon
multiline_comment|/* starting offset of mapping */
DECL|member|pp_mapsz
r_int
id|pp_mapsz
suffix:semicolon
multiline_comment|/* size of this mapping */
DECL|member|pp_kvaddr
id|caddr_t
id|pp_kvaddr
suffix:semicolon
multiline_comment|/* kernel virtual address to use */
)brace
suffix:semicolon
multiline_comment|/*&n; * All PCI providers set up DMA using this information.&n; */
DECL|struct|pciio_dmamap_s
r_struct
id|pciio_dmamap_s
(brace
DECL|member|pd_flags
r_int
id|pd_flags
suffix:semicolon
multiline_comment|/* PCIIO_DMAMAP flags */
DECL|member|pd_dev
id|devfs_handle_t
id|pd_dev
suffix:semicolon
multiline_comment|/* associated pci card */
DECL|member|pd_slot
id|pciio_slot_t
id|pd_slot
suffix:semicolon
multiline_comment|/* which slot the card is in */
)brace
suffix:semicolon
multiline_comment|/*&n; * All PCI providers set up interrupts using this information.&n; */
DECL|struct|pciio_intr_s
r_struct
id|pciio_intr_s
(brace
DECL|member|pi_flags
r_int
id|pi_flags
suffix:semicolon
multiline_comment|/* PCIIO_INTR flags */
DECL|member|pi_dev
id|devfs_handle_t
id|pi_dev
suffix:semicolon
multiline_comment|/* associated pci card */
DECL|member|pi_dev_desc
id|device_desc_t
id|pi_dev_desc
suffix:semicolon
multiline_comment|/* override device descriptor */
DECL|member|pi_lines
id|pciio_intr_line_t
id|pi_lines
suffix:semicolon
multiline_comment|/* which interrupt line(s) */
DECL|member|pi_mustruncpu
id|cpuid_t
id|pi_mustruncpu
suffix:semicolon
multiline_comment|/* Where we must run. */
DECL|member|pi_irq
r_int
id|pi_irq
suffix:semicolon
multiline_comment|/* IRQ assigned */
DECL|member|pi_cpu
r_int
id|pi_cpu
suffix:semicolon
multiline_comment|/* cpu assigned */
)brace
suffix:semicolon
multiline_comment|/* PCIIO_INTR (pi_flags) flags */
DECL|macro|PCIIO_INTR_CONNECTED
mdefine_line|#define PCIIO_INTR_CONNECTED&t;1&t;/* interrupt handler/thread has been connected */
DECL|macro|PCIIO_INTR_NOTHREAD
mdefine_line|#define PCIIO_INTR_NOTHREAD&t;2&t;/* interrupt handler wants to be called at interrupt level */
multiline_comment|/*&n; * Each PCI Card has one of these.&n; */
DECL|struct|pciio_info_s
r_struct
id|pciio_info_s
(brace
DECL|member|c_fingerprint
r_char
op_star
id|c_fingerprint
suffix:semicolon
DECL|member|c_vertex
id|devfs_handle_t
id|c_vertex
suffix:semicolon
multiline_comment|/* back pointer to vertex */
DECL|member|c_bus
id|pciio_bus_t
id|c_bus
suffix:semicolon
multiline_comment|/* which bus the card is in */
DECL|member|c_slot
id|pciio_slot_t
id|c_slot
suffix:semicolon
multiline_comment|/* which slot the card is in */
DECL|member|c_func
id|pciio_function_t
id|c_func
suffix:semicolon
multiline_comment|/* which func (on multi-func cards) */
DECL|member|c_vendor
id|pciio_vendor_id_t
id|c_vendor
suffix:semicolon
multiline_comment|/* PCI card &quot;vendor&quot; code */
DECL|member|c_device
id|pciio_device_id_t
id|c_device
suffix:semicolon
multiline_comment|/* PCI card &quot;device&quot; code */
DECL|member|c_master
id|devfs_handle_t
id|c_master
suffix:semicolon
multiline_comment|/* PCI bus provider */
DECL|member|c_mfast
id|arbitrary_info_t
id|c_mfast
suffix:semicolon
multiline_comment|/* cached fastinfo from c_master */
DECL|member|c_pops
id|pciio_provider_t
op_star
id|c_pops
suffix:semicolon
multiline_comment|/* cached provider from c_master */
DECL|member|c_efunc
id|error_handler_f
op_star
id|c_efunc
suffix:semicolon
multiline_comment|/* error handling function */
DECL|member|c_einfo
id|error_handler_arg_t
id|c_einfo
suffix:semicolon
multiline_comment|/* first parameter for efunc */
r_struct
(brace
multiline_comment|/* state of BASE regs */
DECL|member|w_space
id|pciio_space_t
id|w_space
suffix:semicolon
DECL|member|w_base
id|iopaddr_t
id|w_base
suffix:semicolon
DECL|member|w_size
r_int
id|w_size
suffix:semicolon
DECL|member|w_devio_index
r_int
id|w_devio_index
suffix:semicolon
multiline_comment|/* DevIO[] register used to&n;                                                   access this window */
DECL|member|c_window
)brace
id|c_window
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|c_rbase
r_int
id|c_rbase
suffix:semicolon
multiline_comment|/* EXPANSION ROM base addr */
DECL|member|c_rsize
r_int
id|c_rsize
suffix:semicolon
multiline_comment|/* EXPANSION ROM size (bytes) */
DECL|member|c_piospace
id|pciio_piospace_t
id|c_piospace
suffix:semicolon
multiline_comment|/* additional I/O spaces allocated */
)brace
suffix:semicolon
r_extern
r_char
id|pciio_info_fingerprint
(braket
)braket
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_PCI_PCIIO_PRIVATE_H */
eof
