multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIIO_PRIVATE_H
DECL|macro|_ASM_SN_PCI_PCIIO_PRIVATE_H
mdefine_line|#define _ASM_SN_PCI_PCIIO_PRIVATE_H
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_defs.h&gt;
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
id|vertex_hdl_t
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
id|vertex_hdl_t
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
id|vertex_hdl_t
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
DECL|member|pi_func
id|intr_func_t
id|pi_func
suffix:semicolon
multiline_comment|/* handler function (when connected) */
DECL|member|pi_arg
id|intr_arg_t
id|pi_arg
suffix:semicolon
multiline_comment|/* handler parameter (when connected) */
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
multiline_comment|/*&n; * Some PCI provider implementations keep track of PCI window Base Address&n; * Register (BAR) address range assignment via the rmalloc()/rmfree() arena&n; * management routines.  These implementations use the following data&n; * structure for each allocation address space (e.g. memory, I/O, small&n; * window, etc.).&n; *&n; * The ``page size&squot;&squot; encodes the minimum allocation unit and must be a power&n; * of 2.  The main use of this allocation ``page size&squot;&squot; is to control the&n; * number of free address ranges that the mapping allocation software will&n; * need to track.  Smaller values will allow more efficient use of the address&n; * ranges but will result in much larger allocation map structures ...  For&n; * instance, if we want to manage allocations for a 256MB address range,&n; * choosing a 1MB allocation page size will result in up to 1MB being wasted&n; * for allocation requests smaller than 1MB.  The worst case allocation&n; * pattern for the allocation software to track would be a pattern of 1MB&n; * allocated, 1MB free.  This results in the need to track up to 128 free&n; * ranges.&n; */
DECL|struct|pciio_win_map_s
r_struct
id|pciio_win_map_s
(brace
DECL|member|wm_map
r_struct
id|map
op_star
id|wm_map
suffix:semicolon
multiline_comment|/* window address map */
DECL|member|wm_page_size
r_int
id|wm_page_size
suffix:semicolon
multiline_comment|/* allocation ``page size&squot;&squot; */
)brace
suffix:semicolon
multiline_comment|/*&n; * Opaque structure used to keep track of window allocation information.&n; */
DECL|struct|pciio_win_alloc_s
r_struct
id|pciio_win_alloc_s
(brace
DECL|member|wa_resource
r_struct
id|resource
op_star
id|wa_resource
suffix:semicolon
multiline_comment|/* window map allocation resource */
DECL|member|wa_base
r_int
r_int
id|wa_base
suffix:semicolon
multiline_comment|/* allocation starting page number */
DECL|member|wa_pages
r_int
id|wa_pages
suffix:semicolon
multiline_comment|/* number of pages in allocation */
)brace
suffix:semicolon
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
id|vertex_hdl_t
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
id|vertex_hdl_t
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
DECL|struct|pciio_win_info_s
r_struct
id|pciio_win_info_s
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
multiline_comment|/* DevIO[] register used to&n;                                                    access this window */
DECL|member|w_win_alloc
r_struct
id|pciio_win_alloc_s
id|w_win_alloc
suffix:semicolon
multiline_comment|/* window allocation cookie */
DECL|member|c_window
)brace
id|c_window
(braket
id|PCI_CFG_BASE_ADDRS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|macro|c_rwindow
mdefine_line|#define c_rwindow&t;c_window[PCI_CFG_BASE_ADDRS]&t;/* EXPANSION ROM window */
DECL|macro|c_rbase
mdefine_line|#define c_rbase&t;&t;c_rwindow.w_base&t;&t;/* EXPANSION ROM base addr */
DECL|macro|c_rsize
mdefine_line|#define c_rsize&t;&t;c_rwindow.w_size&t;&t;/* EXPANSION ROM size (bytes) */
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
