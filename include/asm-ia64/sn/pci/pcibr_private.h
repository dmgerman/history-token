multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIBR_PRIVATE_H
DECL|macro|_ASM_SN_PCI_PCIBR_PRIVATE_H
mdefine_line|#define _ASM_SN_PCI_PCIBR_PRIVATE_H
multiline_comment|/*&n; * pcibr_private.h -- private definitions for pcibr&n; * only the pcibr driver (and its closest friends)&n; * should ever peek into this file.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio_private.h&gt;
macro_line|#include &lt;asm/sn/ksys/l1.h&gt;
multiline_comment|/*&n; * convenience typedefs&n; */
DECL|typedef|pcibr_DMattr_t
r_typedef
r_uint64
id|pcibr_DMattr_t
suffix:semicolon
DECL|typedef|pcibr_ATEattr_t
r_typedef
r_uint32
id|pcibr_ATEattr_t
suffix:semicolon
DECL|typedef|pcibr_info_t
DECL|typedef|pcibr_info_h
r_typedef
r_struct
id|pcibr_info_s
op_star
id|pcibr_info_t
comma
op_star
op_star
id|pcibr_info_h
suffix:semicolon
DECL|typedef|pcibr_soft_t
r_typedef
r_struct
id|pcibr_soft_s
op_star
id|pcibr_soft_t
suffix:semicolon
DECL|typedef|pcibr_soft_slot_t
r_typedef
r_struct
id|pcibr_soft_slot_s
op_star
id|pcibr_soft_slot_t
suffix:semicolon
DECL|typedef|pcibr_hints_t
r_typedef
r_struct
id|pcibr_hints_s
op_star
id|pcibr_hints_t
suffix:semicolon
DECL|typedef|pcibr_intr_list_t
r_typedef
r_struct
id|pcibr_intr_list_s
op_star
id|pcibr_intr_list_t
suffix:semicolon
DECL|typedef|pcibr_intr_wrap_t
r_typedef
r_struct
id|pcibr_intr_wrap_s
op_star
id|pcibr_intr_wrap_t
suffix:semicolon
DECL|typedef|pcibr_intr_cbuf_t
r_typedef
r_struct
id|pcibr_intr_cbuf_s
op_star
id|pcibr_intr_cbuf_t
suffix:semicolon
DECL|typedef|cfg_p
r_typedef
r_volatile
r_int
op_star
id|cfg_p
suffix:semicolon
DECL|typedef|reg_p
r_typedef
r_volatile
id|bridgereg_t
op_star
id|reg_p
suffix:semicolon
multiline_comment|/*&n; * extern functions&n; */
id|cfg_p
id|pcibr_slot_config_addr
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_slot_t
comma
r_int
)paren
suffix:semicolon
id|cfg_p
id|pcibr_func_config_addr
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_bus_t
id|bus
comma
id|pciio_slot_t
comma
id|pciio_function_t
comma
r_int
)paren
suffix:semicolon
r_int
id|pcibr_slot_config_get
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_slot_t
comma
r_int
)paren
suffix:semicolon
r_int
id|pcibr_func_config_get
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_slot_t
comma
id|pciio_function_t
comma
r_int
)paren
suffix:semicolon
r_void
id|pcibr_debug
c_func
(paren
r_uint32
comma
id|vertex_hdl_t
comma
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|pcibr_slot_config_set
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_slot_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|pcibr_func_config_set
c_func
(paren
id|bridge_t
op_star
comma
id|pciio_slot_t
comma
id|pciio_function_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * PCIBR_DEBUG() macro and debug bitmask defines&n; */
multiline_comment|/* low freqency debug events (ie. initialization, resource allocation,...) */
DECL|macro|PCIBR_DEBUG_INIT
mdefine_line|#define PCIBR_DEBUG_INIT&t;0x00000001  /* bridge init */
DECL|macro|PCIBR_DEBUG_HINTS
mdefine_line|#define PCIBR_DEBUG_HINTS&t;0x00000002  /* bridge hints */
DECL|macro|PCIBR_DEBUG_ATTACH
mdefine_line|#define PCIBR_DEBUG_ATTACH&t;0x00000004  /* bridge attach */
DECL|macro|PCIBR_DEBUG_DETACH
mdefine_line|#define PCIBR_DEBUG_DETACH&t;0x00000008  /* bridge detach */
DECL|macro|PCIBR_DEBUG_ATE
mdefine_line|#define PCIBR_DEBUG_ATE&t;&t;0x00000010  /* bridge ATE allocation */
DECL|macro|PCIBR_DEBUG_RRB
mdefine_line|#define PCIBR_DEBUG_RRB&t;&t;0x00000020  /* bridge RRB allocation */
DECL|macro|PCIBR_DEBUG_RBAR
mdefine_line|#define PCIBR_DEBUG_RBAR&t;0x00000040  /* bridge RBAR allocation */
DECL|macro|PCIBR_DEBUG_PROBE
mdefine_line|#define PCIBR_DEBUG_PROBE&t;0x00000080  /* bridge device probing */
DECL|macro|PCIBR_DEBUG_INTR_ERROR
mdefine_line|#define PCIBR_DEBUG_INTR_ERROR  0x00000100  /* bridge error interrupt */
DECL|macro|PCIBR_DEBUG_ERROR_HDLR
mdefine_line|#define PCIBR_DEBUG_ERROR_HDLR  0x00000200  /* bridge error handler */
DECL|macro|PCIBR_DEBUG_CONFIG
mdefine_line|#define PCIBR_DEBUG_CONFIG&t;0x00000400  /* device&squot;s config space */
DECL|macro|PCIBR_DEBUG_BAR
mdefine_line|#define PCIBR_DEBUG_BAR&t;&t;0x00000800  /* device&squot;s BAR allocations */
DECL|macro|PCIBR_DEBUG_INTR_ALLOC
mdefine_line|#define PCIBR_DEBUG_INTR_ALLOC&t;0x00001000  /* device&squot;s intr allocation */
DECL|macro|PCIBR_DEBUG_DEV_ATTACH
mdefine_line|#define PCIBR_DEBUG_DEV_ATTACH&t;0x00002000  /* device&squot;s attach */
DECL|macro|PCIBR_DEBUG_DEV_DETACH
mdefine_line|#define PCIBR_DEBUG_DEV_DETACH&t;0x00004000  /* device&squot;s detach */
DECL|macro|PCIBR_DEBUG_HOTPLUG
mdefine_line|#define PCIBR_DEBUG_HOTPLUG&t;0x00008000
multiline_comment|/* high freqency debug events (ie. map allocation, direct translation,...) */
DECL|macro|PCIBR_DEBUG_DEVREG
mdefine_line|#define PCIBR_DEBUG_DEVREG&t;0x04000000  /* bridges device reg sets */
DECL|macro|PCIBR_DEBUG_PIOMAP
mdefine_line|#define PCIBR_DEBUG_PIOMAP&t;0x08000000  /* pcibr_piomap */
DECL|macro|PCIBR_DEBUG_PIODIR
mdefine_line|#define PCIBR_DEBUG_PIODIR&t;0x10000000  /* pcibr_piotrans */
DECL|macro|PCIBR_DEBUG_DMAMAP
mdefine_line|#define PCIBR_DEBUG_DMAMAP&t;0x20000000  /* pcibr_dmamap */
DECL|macro|PCIBR_DEBUG_DMADIR
mdefine_line|#define PCIBR_DEBUG_DMADIR&t;0x40000000  /* pcibr_dmatrans */
DECL|macro|PCIBR_DEBUG_INTR
mdefine_line|#define PCIBR_DEBUG_INTR&t;0x80000000  /* interrupts */
r_extern
r_char
op_star
id|pcibr_debug_module
suffix:semicolon
r_extern
r_int
id|pcibr_debug_widget
suffix:semicolon
r_extern
r_int
id|pcibr_debug_slot
suffix:semicolon
r_extern
r_uint32
id|pcibr_debug_mask
suffix:semicolon
multiline_comment|/* For low frequency events (ie. initialization, resource allocation,...) */
DECL|macro|PCIBR_DEBUG_ALWAYS
mdefine_line|#define PCIBR_DEBUG_ALWAYS(args) pcibr_debug args ;
multiline_comment|/* XXX: habeck: maybe make PCIBR_DEBUG() always available?  Even in non-&n; * debug kernels?  If tracing isn&squot;t enabled (i.e pcibr_debug_mask isn&squot;t&n; * set, then the overhead for this macro is just an extra &squot;if&squot; check.&n; */
multiline_comment|/* For high frequency events (ie. map allocation, direct translation,...) */
macro_line|#if 1 || DEBUG
DECL|macro|PCIBR_DEBUG
mdefine_line|#define PCIBR_DEBUG(args) PCIBR_DEBUG_ALWAYS(args)
macro_line|#else&t;/* DEBUG */
DECL|macro|PCIBR_DEBUG
mdefine_line|#define PCIBR_DEBUG(args)
macro_line|#endif&t;/* DEBUG */
multiline_comment|/*&n; * Bridge sets up PIO using this information.&n; */
DECL|struct|pcibr_piomap_s
r_struct
id|pcibr_piomap_s
(brace
DECL|member|bp_pp
r_struct
id|pciio_piomap_s
id|bp_pp
suffix:semicolon
multiline_comment|/* generic stuff */
DECL|macro|bp_flags
mdefine_line|#define&t;bp_flags&t;bp_pp.pp_flags&t;/* PCIBR_PIOMAP flags */
DECL|macro|bp_dev
mdefine_line|#define&t;bp_dev&t;&t;bp_pp.pp_dev&t;/* associated pci card */
DECL|macro|bp_slot
mdefine_line|#define&t;bp_slot&t;&t;bp_pp.pp_slot&t;/* which slot the card is in */
DECL|macro|bp_space
mdefine_line|#define&t;bp_space&t;bp_pp.pp_space&t;/* which address space */
DECL|macro|bp_pciaddr
mdefine_line|#define&t;bp_pciaddr&t;bp_pp.pp_pciaddr&t;/* starting offset of mapping */
DECL|macro|bp_mapsz
mdefine_line|#define&t;bp_mapsz&t;bp_pp.pp_mapsz&t;/* size of this mapping */
DECL|macro|bp_kvaddr
mdefine_line|#define&t;bp_kvaddr&t;bp_pp.pp_kvaddr&t;/* kernel virtual address to use */
DECL|member|bp_xtalk_addr
id|iopaddr_t
id|bp_xtalk_addr
suffix:semicolon
multiline_comment|/* corresponding xtalk address */
DECL|member|bp_xtalk_pio
id|xtalk_piomap_t
id|bp_xtalk_pio
suffix:semicolon
multiline_comment|/* corresponding xtalk resource */
DECL|member|bp_next
id|pcibr_piomap_t
id|bp_next
suffix:semicolon
multiline_comment|/* Next piomap on the list */
DECL|member|bp_soft
id|pcibr_soft_t
id|bp_soft
suffix:semicolon
multiline_comment|/* backpointer to bridge soft data */
DECL|member|bp_toc
id|atomic_t
id|bp_toc
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* PCI timeout counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * Bridge sets up DMA using this information.&n; */
DECL|struct|pcibr_dmamap_s
r_struct
id|pcibr_dmamap_s
(brace
DECL|member|bd_pd
r_struct
id|pciio_dmamap_s
id|bd_pd
suffix:semicolon
DECL|macro|bd_flags
mdefine_line|#define&t;bd_flags&t;bd_pd.pd_flags&t;/* PCIBR_DMAMAP flags */
DECL|macro|bd_dev
mdefine_line|#define&t;bd_dev&t;&t;bd_pd.pd_dev&t;/* associated pci card */
DECL|macro|bd_slot
mdefine_line|#define&t;bd_slot&t;&t;bd_pd.pd_slot&t;/* which slot the card is in */
DECL|member|bd_soft
r_struct
id|pcibr_soft_s
op_star
id|bd_soft
suffix:semicolon
multiline_comment|/* pcibr soft state backptr */
DECL|member|bd_xtalk
id|xtalk_dmamap_t
id|bd_xtalk
suffix:semicolon
multiline_comment|/* associated xtalk resources */
DECL|member|bd_max_size
r_int
id|bd_max_size
suffix:semicolon
multiline_comment|/* maximum size of mapping */
DECL|member|bd_xio_port
id|xwidgetnum_t
id|bd_xio_port
suffix:semicolon
multiline_comment|/* target XIO port */
DECL|member|bd_xio_addr
id|iopaddr_t
id|bd_xio_addr
suffix:semicolon
multiline_comment|/* target XIO address */
DECL|member|bd_pci_addr
id|iopaddr_t
id|bd_pci_addr
suffix:semicolon
multiline_comment|/* via PCI address */
DECL|member|bd_ate_index
r_int
id|bd_ate_index
suffix:semicolon
multiline_comment|/* Address Translation Entry Index */
DECL|member|bd_ate_count
r_int
id|bd_ate_count
suffix:semicolon
multiline_comment|/* number of ATE&squot;s allocated */
DECL|member|bd_ate_ptr
id|bridge_ate_p
id|bd_ate_ptr
suffix:semicolon
multiline_comment|/* where to write first ATE */
DECL|member|bd_ate_proto
id|bridge_ate_t
id|bd_ate_proto
suffix:semicolon
multiline_comment|/* prototype ATE (for xioaddr=0) */
DECL|member|bd_ate_prime
id|bridge_ate_t
id|bd_ate_prime
suffix:semicolon
multiline_comment|/* value of 1st ATE written */
)brace
suffix:semicolon
DECL|macro|IBUFSIZE
mdefine_line|#define&t;IBUFSIZE&t;5&t;&t;/* size of circular buffer (holds 4) */
multiline_comment|/*&n; * Circular buffer used for interrupt processing&n; */
DECL|struct|pcibr_intr_cbuf_s
r_struct
id|pcibr_intr_cbuf_s
(brace
DECL|member|ib_lock
id|spinlock_t
id|ib_lock
suffix:semicolon
multiline_comment|/* cbuf &squot;put&squot; lock */
DECL|member|ib_in
r_int
id|ib_in
suffix:semicolon
multiline_comment|/* index of next free entry */
DECL|member|ib_out
r_int
id|ib_out
suffix:semicolon
multiline_comment|/* index of next full entry */
DECL|member|ib_cbuf
id|pcibr_intr_wrap_t
id|ib_cbuf
(braket
id|IBUFSIZE
)braket
suffix:semicolon
multiline_comment|/* circular buffer of wrap  */
)brace
suffix:semicolon
multiline_comment|/*&n; * Bridge sets up interrupts using this information.&n; */
DECL|struct|pcibr_intr_s
r_struct
id|pcibr_intr_s
(brace
DECL|member|bi_pi
r_struct
id|pciio_intr_s
id|bi_pi
suffix:semicolon
DECL|macro|bi_flags
mdefine_line|#define&t;bi_flags&t;bi_pi.pi_flags&t;/* PCIBR_INTR flags */
DECL|macro|bi_dev
mdefine_line|#define&t;bi_dev&t;&t;bi_pi.pi_dev&t;/* associated pci card */
DECL|macro|bi_lines
mdefine_line|#define&t;bi_lines&t;bi_pi.pi_lines&t;/* which PCI interrupt line(s) */
DECL|macro|bi_func
mdefine_line|#define bi_func&t;&t;bi_pi.pi_func&t;/* handler function (when connected) */
DECL|macro|bi_arg
mdefine_line|#define bi_arg&t;&t;bi_pi.pi_arg&t;/* handler parameter (when connected) */
DECL|macro|bi_mustruncpu
mdefine_line|#define bi_mustruncpu&t;bi_pi.pi_mustruncpu /* Where we must run. */
DECL|macro|bi_irq
mdefine_line|#define bi_irq&t;&t;bi_pi.pi_irq&t;/* IRQ assigned. */
DECL|macro|bi_cpu
mdefine_line|#define bi_cpu&t;&t;bi_pi.pi_cpu&t;/* cpu assigned. */
DECL|member|bi_ibits
r_int
id|bi_ibits
suffix:semicolon
multiline_comment|/* which Bridge interrupt bit(s) */
DECL|member|bi_soft
id|pcibr_soft_t
id|bi_soft
suffix:semicolon
multiline_comment|/* shortcut to soft info */
DECL|member|bi_ibuf
r_struct
id|pcibr_intr_cbuf_s
id|bi_ibuf
suffix:semicolon
multiline_comment|/* circular buffer of wrap ptrs */
DECL|member|bi_last_intr
r_int
id|bi_last_intr
suffix:semicolon
multiline_comment|/* For Shub lb lost intr. bug */
)brace
suffix:semicolon
multiline_comment|/* &n; * PCIBR_INFO_SLOT_GET_EXT returns the external slot number that the card&n; * resides in.  (i.e the slot number silk screened on the back of the I/O &n; * brick).  PCIBR_INFO_SLOT_GET_INT returns the internal slot (or device)&n; * number used by the pcibr code to represent that external slot (i.e to &n; * set bit patterns in BRIDGE/PIC registers to represent the device, or to&n; * offset into an array, or ...).&n; *&n; * In BRIDGE and XBRIDGE the external slot and internal device numbering &n; * are the same.  (0-&gt;0, 1-&gt;1, 2-&gt;2,... 7-&gt;7)  BUT in the PIC the external&n; * slot number is always 1 greater than the internal device number (1-&gt;0, &n; * 2-&gt;1, 3-&gt;2, 4-&gt;3).  This is due to the fact that the PCI-X spec requires&n; * that the &squot;bridge&squot; (i.e PIC) be designated as &squot;device 0&squot;, thus external&n; * slot numbering can&squot;t start at zero.&n; *&n; * PCIBR_DEVICE_TO_SLOT converts an internal device number to an external&n; * slot number.  NOTE: PCIIO_SLOT_NONE stays as PCIIO_SLOT_NONE.&n; *&n; * PCIBR_SLOT_TO_DEVICE converts an external slot number to an internal&n; * device number.  NOTE: PCIIO_SLOT_NONE stays as PCIIO_SLOT_NONE.&n; */
DECL|macro|PCIBR_INFO_SLOT_GET_EXT
mdefine_line|#define PCIBR_INFO_SLOT_GET_EXT(info)&t;    (((pcibr_info_t)info)-&gt;f_slot)
DECL|macro|PCIBR_INFO_SLOT_GET_INT
mdefine_line|#define PCIBR_INFO_SLOT_GET_INT(info)&t;    (((pcibr_info_t)info)-&gt;f_dev)
DECL|macro|PCIBR_DEVICE_TO_SLOT
mdefine_line|#define PCIBR_DEVICE_TO_SLOT(pcibr_soft, dev_num) &bslash;&n;&t;(((dev_num) != PCIIO_SLOT_NONE) ? &bslash;&n;&t;    (IS_PIC_SOFT((pcibr_soft)) ? ((dev_num) + 1) : (dev_num)) : &bslash;&n;&t;    PCIIO_SLOT_NONE)
DECL|macro|PCIBR_SLOT_TO_DEVICE
mdefine_line|#define PCIBR_SLOT_TO_DEVICE(pcibr_soft, slot) &bslash;&n;        (((slot) != PCIIO_SLOT_NONE) ? &bslash;&n;            (IS_PIC_SOFT((pcibr_soft)) ? ((slot) - 1) : (slot)) : &bslash;&n;            PCIIO_SLOT_NONE)
multiline_comment|/*&n; * per-connect point pcibr data, including standard pciio data in-line:&n; */
DECL|struct|pcibr_info_s
r_struct
id|pcibr_info_s
(brace
DECL|member|f_c
r_struct
id|pciio_info_s
id|f_c
suffix:semicolon
multiline_comment|/* MUST BE FIRST. */
DECL|macro|f_vertex
mdefine_line|#define&t;f_vertex&t;f_c.c_vertex&t;/* back pointer to vertex */
DECL|macro|f_bus
mdefine_line|#define&t;f_bus&t;&t;f_c.c_bus&t;/* which bus the card is in */
DECL|macro|f_slot
mdefine_line|#define&t;f_slot&t;&t;f_c.c_slot&t;/* which slot the card is in */
DECL|macro|f_func
mdefine_line|#define&t;f_func&t;&t;f_c.c_func&t;/* which func (on multi-func cards) */
DECL|macro|f_vendor
mdefine_line|#define&t;f_vendor&t;f_c.c_vendor&t;/* PCI card &quot;vendor&quot; code */
DECL|macro|f_device
mdefine_line|#define&t;f_device&t;f_c.c_device&t;/* PCI card &quot;device&quot; code */
DECL|macro|f_master
mdefine_line|#define&t;f_master&t;f_c.c_master&t;/* PCI bus provider */
DECL|macro|f_mfast
mdefine_line|#define&t;f_mfast&t;&t;f_c.c_mfast&t;/* cached fastinfo from c_master */
DECL|macro|f_pops
mdefine_line|#define&t;f_pops&t;&t;f_c.c_pops&t;/* cached provider from c_master */
DECL|macro|f_efunc
mdefine_line|#define&t;f_efunc&t;&t;f_c.c_efunc&t;/* error handling function */
DECL|macro|f_einfo
mdefine_line|#define&t;f_einfo&t;&t;f_c.c_einfo&t;/* first parameter for efunc */
DECL|macro|f_window
mdefine_line|#define f_window        f_c.c_window    /* state of BASE regs */
DECL|macro|f_rwindow
mdefine_line|#define&t;f_rwindow&t;f_c.c_rwindow&t;/* expansion ROM BASE regs */
DECL|macro|f_rbase
mdefine_line|#define&t;f_rbase&t;&t;f_c.c_rbase&t;/* expansion ROM base */
DECL|macro|f_rsize
mdefine_line|#define&t;f_rsize&t;&t;f_c.c_rsize&t;/* expansion ROM size */
DECL|macro|f_piospace
mdefine_line|#define f_piospace      f_c.c_piospace  /* additional I/O spaces allocated */
multiline_comment|/* pcibr-specific connection state */
DECL|member|f_ibit
r_int
id|f_ibit
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Bridge bit for each INTx */
DECL|member|f_piomap
id|pcibr_piomap_t
id|f_piomap
suffix:semicolon
DECL|member|f_att_det_error
r_int
id|f_att_det_error
suffix:semicolon
DECL|member|f_dev
id|pciio_slot_t
id|f_dev
suffix:semicolon
multiline_comment|/* which device the card represents */
DECL|member|f_pcix_cap
id|cap_pcix_type0_t
op_star
id|f_pcix_cap
suffix:semicolon
multiline_comment|/* pointer to the pcix capability */
)brace
suffix:semicolon
multiline_comment|/* =====================================================================&n; *          Shared Interrupt Information&n; */
DECL|struct|pcibr_intr_list_s
r_struct
id|pcibr_intr_list_s
(brace
DECL|member|il_next
id|pcibr_intr_list_t
id|il_next
suffix:semicolon
DECL|member|il_intr
id|pcibr_intr_t
id|il_intr
suffix:semicolon
DECL|member|il_wrbf
r_volatile
id|bridgereg_t
op_star
id|il_wrbf
suffix:semicolon
multiline_comment|/* ptr to b_wr_req_buf[] */
)brace
suffix:semicolon
multiline_comment|/* =====================================================================&n; *          Interrupt Wrapper Data&n; */
DECL|struct|pcibr_intr_wrap_s
r_struct
id|pcibr_intr_wrap_s
(brace
DECL|member|iw_soft
id|pcibr_soft_t
id|iw_soft
suffix:semicolon
multiline_comment|/* which bridge */
DECL|member|iw_stat
r_volatile
id|bridgereg_t
op_star
id|iw_stat
suffix:semicolon
multiline_comment|/* ptr to b_int_status */
DECL|member|iw_ibit
id|bridgereg_t
id|iw_ibit
suffix:semicolon
multiline_comment|/* bit in b_int_status */
DECL|member|iw_list
id|pcibr_intr_list_t
id|iw_list
suffix:semicolon
multiline_comment|/* ghostbusters! */
DECL|member|iw_hdlrcnt
r_int
id|iw_hdlrcnt
suffix:semicolon
multiline_comment|/* running handler count */
DECL|member|iw_shared
r_int
id|iw_shared
suffix:semicolon
multiline_comment|/* if Bridge bit is shared */
DECL|member|iw_connected
r_int
id|iw_connected
suffix:semicolon
multiline_comment|/* if already connected */
)brace
suffix:semicolon
DECL|macro|PCIBR_ISR_ERR_START
mdefine_line|#define&t;PCIBR_ISR_ERR_START&t;&t;8
DECL|macro|PCIBR_ISR_MAX_ERRS_BRIDGE
mdefine_line|#define PCIBR_ISR_MAX_ERRS_BRIDGE &t;32
DECL|macro|PCIBR_ISR_MAX_ERRS_PIC
mdefine_line|#define PCIBR_ISR_MAX_ERRS_PIC&t;&t;45
DECL|macro|PCIBR_ISR_MAX_ERRS
mdefine_line|#define PCIBR_ISR_MAX_ERRS&t;PCIBR_ISR_MAX_ERRS_PIC
multiline_comment|/*&n; * PCI Base Address Register window allocation constants.&n; * To reduce the size of the internal resource mapping structures, do&n; * not use the entire PCI bus I/O address space&n; */
DECL|macro|PCIBR_BUS_IO_BASE
mdefine_line|#define PCIBR_BUS_IO_BASE      0x100000
DECL|macro|PCIBR_BUS_IO_MAX
mdefine_line|#define PCIBR_BUS_IO_MAX       0x0FFFFFFF
DECL|macro|PCIBR_BUS_IO_PAGE
mdefine_line|#define PCIBR_BUS_IO_PAGE      0x100000
DECL|macro|PCIBR_BUS_SWIN_BASE
mdefine_line|#define PCIBR_BUS_SWIN_BASE    _PAGESZ
DECL|macro|PCIBR_BUS_SWIN_MAX
mdefine_line|#define PCIBR_BUS_SWIN_MAX     0x000FFFFF
DECL|macro|PCIBR_BUS_SWIN_PAGE
mdefine_line|#define PCIBR_BUS_SWIN_PAGE    _PAGESZ
DECL|macro|PCIBR_BUS_MEM_BASE
mdefine_line|#define PCIBR_BUS_MEM_BASE     0x200000
DECL|macro|PCIBR_BUS_MEM_MAX
mdefine_line|#define PCIBR_BUS_MEM_MAX      0x3FFFFFFF
DECL|macro|PCIBR_BUS_MEM_PAGE
mdefine_line|#define PCIBR_BUS_MEM_PAGE     0x100000
multiline_comment|/* defines for pcibr_soft_s-&gt;bs_bridge_type */
DECL|macro|PCIBR_BRIDGETYPE_BRIDGE
mdefine_line|#define PCIBR_BRIDGETYPE_BRIDGE&t;&t;0
DECL|macro|PCIBR_BRIDGETYPE_XBRIDGE
mdefine_line|#define PCIBR_BRIDGETYPE_XBRIDGE&t;1
DECL|macro|PCIBR_BRIDGETYPE_PIC
mdefine_line|#define PCIBR_BRIDGETYPE_PIC&t;&t;2
DECL|macro|IS_XBRIDGE_SOFT
mdefine_line|#define IS_XBRIDGE_SOFT(ps) (ps-&gt;bs_bridge_type == PCIBR_BRIDGETYPE_XBRIDGE)
DECL|macro|IS_PIC_SOFT
mdefine_line|#define IS_PIC_SOFT(ps)     (ps-&gt;bs_bridge_type == PCIBR_BRIDGETYPE_PIC)
DECL|macro|IS_PIC_BUSNUM_SOFT
mdefine_line|#define IS_PIC_BUSNUM_SOFT(ps, bus)&t;&bslash;&n;&t;&t;(IS_PIC_SOFT(ps) &amp;&amp; ((ps)-&gt;bs_busnum == (bus)))
DECL|macro|IS_BRIDGE_SOFT
mdefine_line|#define IS_BRIDGE_SOFT(ps)  (ps-&gt;bs_bridge_type == PCIBR_BRIDGETYPE_BRIDGE)
DECL|macro|IS_XBRIDGE_OR_PIC_SOFT
mdefine_line|#define IS_XBRIDGE_OR_PIC_SOFT(ps) (IS_XBRIDGE_SOFT(ps) || IS_PIC_SOFT(ps))
multiline_comment|/*&n; * Runtime checks for workarounds.&n; */
DECL|macro|PCIBR_WAR_ENABLED
mdefine_line|#define PCIBR_WAR_ENABLED(pv, pcibr_soft) &bslash;&n;&t;((1 &lt;&lt; XWIDGET_PART_REV_NUM_REV(pcibr_soft-&gt;bs_rev_num)) &amp; pv)
multiline_comment|/*&n; * Defines for individual WARs. Each is a bitmask of applicable&n; * part revision numbers. (1 &lt;&lt; 1) == rev A, (1 &lt;&lt; 2) == rev B, etc.&n; */
DECL|macro|PV854697
mdefine_line|#define PV854697 (~0)     /* PIC: write 64bit regs as 64bits. permanent */
DECL|macro|PV854827
mdefine_line|#define PV854827 (~0)     /* PIC: fake widget 0xf presence bit. permanent */
DECL|macro|PV855271
mdefine_line|#define PV855271 (1 &lt;&lt; 1) /* PIC: PIC: use virt chan iff 64-bit device. */
DECL|macro|PV855272
mdefine_line|#define PV855272 (1 &lt;&lt; 1) /* PIC: runaway interrupt WAR */
DECL|macro|PV856155
mdefine_line|#define PV856155 (1 &lt;&lt; 1) /* PIC: arbitration WAR */
DECL|macro|PV856864
mdefine_line|#define PV856864 (1 &lt;&lt; 1) /* PIC: lower timeout to free TNUMs quicker */
DECL|macro|PV856866
mdefine_line|#define PV856866 (1 &lt;&lt; 1) /* PIC: avoid rrb&squot;s 0/1/8/9. */
DECL|macro|PV862253
mdefine_line|#define PV862253 (1 &lt;&lt; 1) /* PIC: don&squot;t enable write req RAM parity checking */
DECL|macro|PV867308
mdefine_line|#define PV867308 (3 &lt;&lt; 1) /* PIC: make LLP error interrupts FATAL for PIC */
multiline_comment|/* defines for pcibr_soft_s-&gt;bs_bridge_mode */
DECL|macro|PCIBR_BRIDGEMODE_PCI_33
mdefine_line|#define PCIBR_BRIDGEMODE_PCI_33&t;&t;0x0
DECL|macro|PCIBR_BRIDGEMODE_PCI_66
mdefine_line|#define PCIBR_BRIDGEMODE_PCI_66&t;&t;0x2
DECL|macro|PCIBR_BRIDGEMODE_PCIX_66
mdefine_line|#define PCIBR_BRIDGEMODE_PCIX_66&t;0x3
DECL|macro|PCIBR_BRIDGEMODE_PCIX_100
mdefine_line|#define PCIBR_BRIDGEMODE_PCIX_100&t;0x5
DECL|macro|PCIBR_BRIDGEMODE_PCIX_133
mdefine_line|#define PCIBR_BRIDGEMODE_PCIX_133&t;0x7
DECL|macro|BUSSPEED_MASK
mdefine_line|#define BUSSPEED_MASK&t;&t;&t;0x6
DECL|macro|BUSTYPE_MASK
mdefine_line|#define BUSTYPE_MASK&t;&t;&t;0x1
DECL|macro|IS_PCI
mdefine_line|#define IS_PCI(ps)&t;(!IS_PCIX(ps))
DECL|macro|IS_PCIX
mdefine_line|#define IS_PCIX(ps)&t;((ps)-&gt;bs_bridge_mode &amp; BUSTYPE_MASK)
DECL|macro|IS_33MHZ
mdefine_line|#define IS_33MHZ(ps)&t;((ps)-&gt;bs_bridge_mode == PCIBR_BRIDGEMODE_PCI_33)
DECL|macro|IS_66MHZ
mdefine_line|#define IS_66MHZ(ps)&t;(((ps)-&gt;bs_bridge_mode == PCIBR_BRIDGEMODE_PCI_66) || &bslash;&n;&t;&t;&t; ((ps)-&gt;bs_bridge_mode == PCIBR_BRIDGEMODE_PCIX_66))
DECL|macro|IS_100MHZ
mdefine_line|#define IS_100MHZ(ps)&t;((ps)-&gt;bs_bridge_mode == PCIBR_BRIDGEMODE_PCIX_100)
DECL|macro|IS_133MHZ
mdefine_line|#define IS_133MHZ(ps)&t;((ps)-&gt;bs_bridge_mode == PCIBR_BRIDGEMODE_PCIX_133)
multiline_comment|/* Number of PCI slots.   NOTE: this works as long as the first slot&n; * is zero.  Otherwise use ((ps-&gt;bs_max_slot+1) - ps-&gt;bs_min_slot)&n; */
DECL|macro|PCIBR_NUM_SLOTS
mdefine_line|#define PCIBR_NUM_SLOTS(ps) (ps-&gt;bs_max_slot+1)
multiline_comment|/* =====================================================================&n; *            Bridge Device State structure&n; *&n; *      one instance of this structure is kept for each&n; *      Bridge ASIC in the system.&n; */
DECL|struct|pcibr_soft_s
r_struct
id|pcibr_soft_s
(brace
DECL|member|bs_conn
id|vertex_hdl_t
id|bs_conn
suffix:semicolon
multiline_comment|/* xtalk connection point */
DECL|member|bs_vhdl
id|vertex_hdl_t
id|bs_vhdl
suffix:semicolon
multiline_comment|/* vertex owned by pcibr */
DECL|member|bs_int_enable
r_uint64
id|bs_int_enable
suffix:semicolon
multiline_comment|/* Mask of enabled intrs */
DECL|member|bs_base
id|bridge_t
op_star
id|bs_base
suffix:semicolon
multiline_comment|/* PIO pointer to Bridge chip */
DECL|member|bs_name
r_char
op_star
id|bs_name
suffix:semicolon
multiline_comment|/* hw graph name */
DECL|member|bs_xid
id|xwidgetnum_t
id|bs_xid
suffix:semicolon
multiline_comment|/* Bridge&squot;s xtalk ID number */
DECL|member|bs_master
id|vertex_hdl_t
id|bs_master
suffix:semicolon
multiline_comment|/* xtalk master vertex */
DECL|member|bs_mxid
id|xwidgetnum_t
id|bs_mxid
suffix:semicolon
multiline_comment|/* master&squot;s xtalk ID number */
DECL|member|bs_first_slot
id|pciio_slot_t
id|bs_first_slot
suffix:semicolon
multiline_comment|/* first existing slot */
DECL|member|bs_last_slot
id|pciio_slot_t
id|bs_last_slot
suffix:semicolon
multiline_comment|/* last existing slot */
DECL|member|bs_last_reset
id|pciio_slot_t
id|bs_last_reset
suffix:semicolon
multiline_comment|/* last slot to reset */
DECL|member|bs_min_slot
id|pciio_slot_t
id|bs_min_slot
suffix:semicolon
multiline_comment|/* lowest possible slot */
DECL|member|bs_max_slot
id|pciio_slot_t
id|bs_max_slot
suffix:semicolon
multiline_comment|/* highest possible slot */
DECL|member|bs_peers_soft
id|pcibr_soft_t
id|bs_peers_soft
suffix:semicolon
multiline_comment|/* PICs other bus&squot;s soft */
DECL|member|bs_busnum
r_int
id|bs_busnum
suffix:semicolon
multiline_comment|/* PIC has two pci busses */
DECL|member|bs_dir_xbase
id|iopaddr_t
id|bs_dir_xbase
suffix:semicolon
multiline_comment|/* xtalk address for 32-bit PCI direct map */
DECL|member|bs_dir_xport
id|xwidgetnum_t
id|bs_dir_xport
suffix:semicolon
multiline_comment|/* xtalk port for 32-bit PCI direct map */
DECL|member|bs_int_ate_resource
r_struct
id|resource
id|bs_int_ate_resource
suffix:semicolon
multiline_comment|/* root resource for internal ATEs */
DECL|member|bs_ext_ate_resource
r_struct
id|resource
id|bs_ext_ate_resource
suffix:semicolon
multiline_comment|/* root resource for external ATEs */
DECL|member|bs_allocated_ate_res
r_void
op_star
id|bs_allocated_ate_res
suffix:semicolon
multiline_comment|/* resource struct allocated */
DECL|member|bs_int_ate_size
r_int
id|bs_int_ate_size
suffix:semicolon
multiline_comment|/* number of internal ates */
DECL|member|bs_bridge_type
r_int
id|bs_bridge_type
suffix:semicolon
multiline_comment|/* see defines above */
DECL|member|bs_bridge_mode
r_int
id|bs_bridge_mode
suffix:semicolon
multiline_comment|/* see defines above */
DECL|member|bs_rev_num
r_int
id|bs_rev_num
suffix:semicolon
multiline_comment|/* revision number of Bridge */
multiline_comment|/* bs_dma_flags are the forced dma flags used on all DMAs. Used for&n;     * working around ASIC rev issues and protocol specific requirements&n;     */
DECL|member|bs_dma_flags
r_int
id|bs_dma_flags
suffix:semicolon
multiline_comment|/* forced DMA flags */
DECL|member|bs_moduleid
id|moduleid_t
id|bs_moduleid
suffix:semicolon
multiline_comment|/* io brick moduleid */
DECL|member|bs_bricktype
r_int
id|bs_bricktype
suffix:semicolon
multiline_comment|/* io brick type */
multiline_comment|/*&n;     * Lock used primarily to get mutual exclusion while managing any&n;     * bridge resources..&n;     */
DECL|member|bs_lock
id|spinlock_t
id|bs_lock
suffix:semicolon
DECL|member|bs_noslot_conn
id|vertex_hdl_t
id|bs_noslot_conn
suffix:semicolon
multiline_comment|/* NO-SLOT connection point */
DECL|member|bs_noslot_info
id|pcibr_info_t
id|bs_noslot_info
suffix:semicolon
DECL|struct|pcibr_soft_slot_s
r_struct
id|pcibr_soft_slot_s
(brace
multiline_comment|/* information we keep about each CFG slot */
multiline_comment|/* some devices (ioc3 in non-slotted&n;&t; * configurations, sometimes) make use&n;&t; * of more than one REQ/GNT/INT* signal&n;&t; * sets. The slot corresponding to the&n;&t; * IDSEL that the device responds to is&n;&t; * called the host slot; the slot&n;&t; * numbers that the device is stealing&n;&t; * REQ/GNT/INT bits from are known as&n;&t; * the guest slots.&n;&t; */
DECL|member|has_host
r_int
id|has_host
suffix:semicolon
DECL|member|host_slot
id|pciio_slot_t
id|host_slot
suffix:semicolon
DECL|member|slot_conn
id|vertex_hdl_t
id|slot_conn
suffix:semicolon
multiline_comment|/* PCI Hot-Plug status word */
DECL|member|slot_status
r_int
id|slot_status
suffix:semicolon
multiline_comment|/* Potentially several connection points&n;&t; * for this slot. bss_ninfo is how many,&n;&t; * and bss_infos is a pointer to&n;&t; * an array pcibr_info_t values (which are&n;&t; * pointers to pcibr_info structs, stored&n;&t; * as device_info in connection ponts).&n;&t; */
DECL|member|bss_ninfo
r_int
id|bss_ninfo
suffix:semicolon
DECL|member|bss_infos
id|pcibr_info_h
id|bss_infos
suffix:semicolon
multiline_comment|/* Temporary Compatibility Macros, for&n;&t; * stuff that has moved out of bs_slot&n;&t; * and into the info structure. These&n;&t; * will go away when their users have&n;&t; * converted over to multifunction-&n;&t; * friendly use of bss_{ninfo,infos}.&n;&t; */
DECL|macro|bss_vendor_id
mdefine_line|#define&t;bss_vendor_id&t;bss_infos[0]-&gt;f_vendor
DECL|macro|bss_device_id
mdefine_line|#define&t;bss_device_id&t;bss_infos[0]-&gt;f_device
DECL|macro|bss_window
mdefine_line|#define&t;bss_window&t;bss_infos[0]-&gt;f_window
DECL|macro|bssw_space
mdefine_line|#define&t;bssw_space&t;w_space
DECL|macro|bssw_base
mdefine_line|#define&t;bssw_base&t;w_base
DECL|macro|bssw_size
mdefine_line|#define&t;bssw_size&t;w_size
multiline_comment|/* Where is DevIO(x) pointing? */
multiline_comment|/* bssd_space is NONE if it is not assigned. */
r_struct
(brace
DECL|member|bssd_space
id|pciio_space_t
id|bssd_space
suffix:semicolon
DECL|member|bssd_base
id|iopaddr_t
id|bssd_base
suffix:semicolon
DECL|member|bssd_ref_cnt
r_int
id|bssd_ref_cnt
suffix:semicolon
DECL|member|bss_devio
)brace
id|bss_devio
suffix:semicolon
multiline_comment|/* Shadow value for Device(x) register,&n;&t; * so we don&squot;t have to go to the chip.&n;&t; */
DECL|member|bss_device
id|bridgereg_t
id|bss_device
suffix:semicolon
multiline_comment|/* Number of sets on GBR/REALTIME bit outstanding&n;&t; * Used by Priority I/O for tracking reservations&n;&t; */
DECL|member|bss_pri_uctr
r_int
id|bss_pri_uctr
suffix:semicolon
multiline_comment|/* Number of &quot;uses&quot; of PMU, 32-bit direct,&n;&t; * and 64-bit direct DMA (0:none, &lt;0: trans,&n;&t; * &gt;0: how many dmamaps). Device(x) bits&n;&t; * controlling attribute of each kind of&n;&t; * channel can&squot;t be changed by dmamap_alloc&n;&t; * or dmatrans if the controlling counter&n;&t; * is nonzero. dmatrans is forever.&n;&t; */
DECL|member|bss_pmu_uctr
r_int
id|bss_pmu_uctr
suffix:semicolon
DECL|member|bss_d32_uctr
r_int
id|bss_d32_uctr
suffix:semicolon
DECL|member|bss_d64_uctr
r_int
id|bss_d64_uctr
suffix:semicolon
multiline_comment|/* When the contents of mapping configuration&n;&t; * information is locked down by dmatrans,&n;&t; * repeated checks of the same flags should&n;&t; * be shortcircuited for efficiency.&n;&t; */
DECL|member|bss_d64_base
id|iopaddr_t
id|bss_d64_base
suffix:semicolon
DECL|member|bss_d64_flags
r_int
id|bss_d64_flags
suffix:semicolon
DECL|member|bss_d32_base
id|iopaddr_t
id|bss_d32_base
suffix:semicolon
DECL|member|bss_d32_flags
r_int
id|bss_d32_flags
suffix:semicolon
multiline_comment|/* Shadow information used for implementing&n;&t; * Bridge Hardware WAR #484930&n;&t; */
DECL|member|bss_ext_ates_active
id|atomic_t
id|bss_ext_ates_active
suffix:semicolon
DECL|member|bss_cmd_pointer
r_volatile
r_int
op_star
id|bss_cmd_pointer
suffix:semicolon
DECL|member|bss_cmd_shadow
r_int
id|bss_cmd_shadow
suffix:semicolon
DECL|member|bs_slot
)brace
id|bs_slot
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bs_intr_bits
id|pcibr_intr_bits_f
op_star
id|bs_intr_bits
suffix:semicolon
multiline_comment|/* PIC PCI-X Read Buffer Management :&n;     * bs_pcix_num_funcs: the total number of PCI-X functions&n;     *  on the bus&n;     * bs_pcix_split_tot: total number of outstanding split&n;     *  transactions requested by all functions on the bus&n;     * bs_pcix_rbar_percent_allowed: the percentage of the&n;     *  total number of buffers a function requested that are &n;     *  available to it, not including the 1 RBAR guaranteed &n;     *  to it.&n;     * bs_pcix_rbar_inuse: number of RBARs in use.&n;     * bs_pcix_rbar_avail: number of RBARs available.  NOTE:&n;     *  this value can go negative if we oversubscribe the &n;     *  RBARs.  (i.e.  We have 16 RBARs but 17 functions).&n;     */
DECL|member|bs_pcix_num_funcs
r_int
id|bs_pcix_num_funcs
suffix:semicolon
DECL|member|bs_pcix_split_tot
r_int
id|bs_pcix_split_tot
suffix:semicolon
DECL|member|bs_pcix_rbar_percent_allowed
r_int
id|bs_pcix_rbar_percent_allowed
suffix:semicolon
DECL|member|bs_pcix_rbar_inuse
r_int
id|bs_pcix_rbar_inuse
suffix:semicolon
DECL|member|bs_pcix_rbar_avail
r_int
id|bs_pcix_rbar_avail
suffix:semicolon
multiline_comment|/* RRB MANAGEMENT&n;     * bs_rrb_fixed: bitmap of slots whose RRB&n;     *&t;allocations we should not &quot;automatically&quot; change&n;     * bs_rrb_avail: number of RRBs that have not&n;     *  been allocated or reserved for {even,odd} slots&n;     * bs_rrb_res: number of RRBs currently reserved for the&n;     *&t;use of the index slot number&n;     * bs_rrb_res_dflt: number of RRBs reserved at boot&n;     *  time for the use of the index slot number&n;     * bs_rrb_valid: number of RRBs currently marked valid&n;     *&t;for the indexed slot/vchan number; array[slot][vchan]&n;     * bs_rrb_valid_dflt: number of RRBs marked valid at boot&n;     *  time for the indexed slot/vchan number; array[slot][vchan]&n;     */
DECL|member|bs_rrb_fixed
r_int
id|bs_rrb_fixed
suffix:semicolon
DECL|member|bs_rrb_avail
r_int
id|bs_rrb_avail
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bs_rrb_res
r_int
id|bs_rrb_res
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bs_rrb_res_dflt
r_int
id|bs_rrb_res_dflt
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bs_rrb_valid
r_int
id|bs_rrb_valid
(braket
l_int|8
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bs_rrb_valid_dflt
r_int
id|bs_rrb_valid_dflt
(braket
l_int|8
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* Each Bridge interrupt bit has a single XIO&n;&t; * interrupt channel allocated.&n;&t; */
DECL|member|bsi_xtalk_intr
id|xtalk_intr_t
id|bsi_xtalk_intr
suffix:semicolon
multiline_comment|/*&n;&t; * A wrapper structure is associated with each&n;&t; * Bridge interrupt bit.&n;&t; */
DECL|member|bsi_pcibr_intr_wrap
r_struct
id|pcibr_intr_wrap_s
id|bsi_pcibr_intr_wrap
suffix:semicolon
DECL|member|bs_intr
)brace
id|bs_intr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bsi_err_intr
id|xtalk_intr_t
id|bsi_err_intr
suffix:semicolon
multiline_comment|/*&n;     * We stash away some information in this structure on getting&n;     * an error interrupt. This information is used during PIO read/&n;     * write error handling.&n;     *&n;     * As it stands now, we do not re-enable the error interrupt&n;     * till the error is resolved. Error resolution happens either at&n;     * bus error time for PIO Read errors (~100 microseconds), or at&n;     * the scheduled timeout time for PIO write errors (~milliseconds).&n;     * If this delay causes problems, we may need to move towards&n;     * a different scheme..&n;     *&n;     * Note that there is no locking while looking at this data structure.&n;     * There should not be any race between bus error code and&n;     * error interrupt code.. will look into this if needed.&n;     *&n;     * NOTE: The above discussion of error interrupt processing is&n;     *       no longer true. Whether it should again be true, is&n;     *       being looked into.&n;     */
DECL|struct|br_errintr_info
r_struct
id|br_errintr_info
(brace
DECL|member|bserr_toutcnt
r_int
id|bserr_toutcnt
suffix:semicolon
macro_line|#ifdef LATER
DECL|member|bserr_toutid
id|toid_t
id|bserr_toutid
suffix:semicolon
multiline_comment|/* Timeout started by errintr */
macro_line|#endif&t;/* LATER */
DECL|member|bserr_addr
id|iopaddr_t
id|bserr_addr
suffix:semicolon
multiline_comment|/* Address where error occured */
DECL|member|bserr_intstat
r_uint64
id|bserr_intstat
suffix:semicolon
multiline_comment|/* interrupts active at error dump */
DECL|member|bs_errinfo
)brace
id|bs_errinfo
suffix:semicolon
multiline_comment|/*&n;     * PCI Bus Space allocation data structure.&n;     *&n;     * The resource mapping functions rmalloc() and rmfree() are used&n;     * to manage the PCI bus I/O, small window, and memory  address &n;     * spaces.&n;     *&n;     * This info is used to assign PCI bus space addresses to cards&n;     * via their BARs and to the callers of the pcibr_piospace_alloc()&n;     * interface.&n;     *&n;     * Users of the pcibr_piospace_alloc() interface, such as the VME&n;     * Universe chip, need PCI bus space that is not acquired by BARs.&n;     * Most of these users need &quot;large&quot; amounts of PIO space (typically&n;     * in Megabytes), and they generally tend to take once and never&n;     * release. &n;     */
DECL|member|bs_io_win_map
r_struct
id|pciio_win_map_s
id|bs_io_win_map
suffix:semicolon
multiline_comment|/* I/O addr space */
DECL|member|bs_swin_map
r_struct
id|pciio_win_map_s
id|bs_swin_map
suffix:semicolon
multiline_comment|/* Small window addr space */
DECL|member|bs_mem_win_map
r_struct
id|pciio_win_map_s
id|bs_mem_win_map
suffix:semicolon
multiline_comment|/* Memory addr space */
DECL|member|bs_io_win_root_resource
r_struct
id|resource
id|bs_io_win_root_resource
suffix:semicolon
multiline_comment|/* I/O addr space */
DECL|member|bs_swin_root_resource
r_struct
id|resource
id|bs_swin_root_resource
suffix:semicolon
multiline_comment|/* Small window addr space */
DECL|member|bs_mem_win_root_resource
r_struct
id|resource
id|bs_mem_win_root_resource
suffix:semicolon
multiline_comment|/* Memory addr space */
DECL|member|bs_bus_addr_status
r_int
id|bs_bus_addr_status
suffix:semicolon
multiline_comment|/* Bus space status */
DECL|macro|PCIBR_BUS_ADDR_MEM_FREED
mdefine_line|#define PCIBR_BUS_ADDR_MEM_FREED       1  /* Reserved PROM mem addr freed */
DECL|macro|PCIBR_BUS_ADDR_IO_FREED
mdefine_line|#define PCIBR_BUS_ADDR_IO_FREED        2  /* Reserved PROM I/O addr freed */
DECL|struct|bs_errintr_stat_s
r_struct
id|bs_errintr_stat_s
(brace
DECL|member|bs_errcount_total
r_uint32
id|bs_errcount_total
suffix:semicolon
DECL|member|bs_lasterr_timestamp
r_uint32
id|bs_lasterr_timestamp
suffix:semicolon
DECL|member|bs_lasterr_snapshot
r_uint32
id|bs_lasterr_snapshot
suffix:semicolon
DECL|member|bs_errintr_stat
)brace
id|bs_errintr_stat
(braket
id|PCIBR_ISR_MAX_ERRS
)braket
suffix:semicolon
multiline_comment|/*&n;     * Bridge-wide endianness control for&n;     * large-window PIO mappings&n;     *&n;     * These fields are set to PCIIO_BYTE_SWAP&n;     * or PCIIO_WORD_VALUES once the swapper&n;     * has been configured, one way or the other,&n;     * for the direct windows. If they are zero,&n;     * nobody has a PIO mapping through that window,&n;     * and the swapper can be set either way.&n;     */
DECL|member|bs_pio_end_io
r_int
id|bs_pio_end_io
suffix:semicolon
DECL|member|bs_pio_end_mem
r_int
id|bs_pio_end_mem
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCIBR_ERRTIME_THRESHOLD
mdefine_line|#define&t;PCIBR_ERRTIME_THRESHOLD&t;&t;(100)
DECL|macro|PCIBR_ERRRATE_THRESHOLD
mdefine_line|#define&t;PCIBR_ERRRATE_THRESHOLD&t;&t;(100)
multiline_comment|/*&n; * pcibr will respond to hints dropped in its vertex&n; * using the following structure.&n; */
DECL|struct|pcibr_hints_s
r_struct
id|pcibr_hints_s
(brace
multiline_comment|/* ph_host_slot is actually +1 so &quot;0&quot; means &quot;no host&quot; */
DECL|member|ph_host_slot
id|pciio_slot_t
id|ph_host_slot
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* REQ/GNT/INT in use by ... */
DECL|member|ph_rrb_fixed
r_int
id|ph_rrb_fixed
suffix:semicolon
multiline_comment|/* do not change RRB allocations */
DECL|member|ph_hands_off
r_int
id|ph_hands_off
suffix:semicolon
multiline_comment|/* prevent further pcibr operations */
DECL|member|rrb_alloc_funct
id|rrb_alloc_funct_t
id|rrb_alloc_funct
suffix:semicolon
multiline_comment|/* do dynamic rrb allocation */
DECL|member|ph_intr_bits
id|pcibr_intr_bits_f
op_star
id|ph_intr_bits
suffix:semicolon
multiline_comment|/* map PCI INT[ABCD] to Bridge Int(n) */
)brace
suffix:semicolon
multiline_comment|/*&n; * Number of bridge non-fatal error interrupts we can see before&n; * we decide to disable that interrupt.&n; */
DECL|macro|PCIBR_ERRINTR_DISABLE_LEVEL
mdefine_line|#define&t;PCIBR_ERRINTR_DISABLE_LEVEL&t;10000
multiline_comment|/* =====================================================================&n; *    Bridge (pcibr) state management functions&n; *&n; *      pcibr_soft_get is here because we do it in a lot&n; *      of places and I want to make sure they all stay&n; *      in step with each other.&n; *&n; *      pcibr_soft_set is here because I want it to be&n; *      closely associated with pcibr_soft_get, even&n; *      though it is only called in one place.&n; */
DECL|macro|pcibr_soft_get
mdefine_line|#define pcibr_soft_get(v)       ((pcibr_soft_t)hwgraph_fastinfo_get((v)))
DECL|macro|pcibr_soft_set
mdefine_line|#define pcibr_soft_set(v,i)     (hwgraph_fastinfo_set((v), (arbitrary_info_t)(i)))
multiline_comment|/*&n; * mem alloc/free macros&n; */
DECL|macro|NEWAf
mdefine_line|#define NEWAf(ptr,n,f)&t;(ptr = snia_kmem_zalloc((n)*sizeof (*(ptr)), (f&amp;PCIIO_NOSLEEP)?KM_NOSLEEP:KM_SLEEP))
DECL|macro|NEWA
mdefine_line|#define NEWA(ptr,n)&t;(ptr = snia_kmem_zalloc((n)*sizeof (*(ptr)), KM_SLEEP))
DECL|macro|DELA
mdefine_line|#define DELA(ptr,n)&t;(kfree(ptr))
DECL|macro|NEWf
mdefine_line|#define NEWf(ptr,f)&t;NEWAf(ptr,1,f)
DECL|macro|NEW
mdefine_line|#define NEW(ptr)&t;NEWA(ptr,1)
DECL|macro|DEL
mdefine_line|#define DEL(ptr)&t;DELA(ptr,1)
multiline_comment|/*&n; * Additional PIO spaces per slot are&n; * recorded in this structure.&n; */
DECL|struct|pciio_piospace_s
r_struct
id|pciio_piospace_s
(brace
DECL|member|next
id|pciio_piospace_t
id|next
suffix:semicolon
multiline_comment|/* another space for this device */
DECL|member|free
r_char
id|free
suffix:semicolon
multiline_comment|/* 1 if free, 0 if in use */
DECL|member|space
id|pciio_space_t
id|space
suffix:semicolon
multiline_comment|/* Which space is in use */
DECL|member|start
id|iopaddr_t
id|start
suffix:semicolon
multiline_comment|/* Starting address of the PIO space */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* size of PIO space */
)brace
suffix:semicolon
multiline_comment|/* Use io spin locks. This ensures that all the PIO writes from a particular&n; * CPU to a particular IO device are synched before the start of the next&n; * set of PIO operations to the same device.&n; */
macro_line|#ifdef PCI_LATER
DECL|macro|pcibr_lock
mdefine_line|#define pcibr_lock(pcibr_soft)&t;&t;io_splock(pcibr_soft-&gt;bs_lock)
DECL|macro|pcibr_unlock
mdefine_line|#define pcibr_unlock(pcibr_soft, s)&t;io_spunlock(pcibr_soft-&gt;bs_lock,s)
macro_line|#else
DECL|macro|pcibr_lock
mdefine_line|#define pcibr_lock(pcibr_soft)&t;&t;1
DECL|macro|pcibr_unlock
mdefine_line|#define pcibr_unlock(pcibr_soft, s)&t;
macro_line|#endif&t;/* PCI_LATER */
DECL|macro|PCIBR_VALID_SLOT
mdefine_line|#define PCIBR_VALID_SLOT(ps, s)     (s &lt; PCIBR_NUM_SLOTS(ps))
DECL|macro|PCIBR_D64_BASE_UNSET
mdefine_line|#define PCIBR_D64_BASE_UNSET    (0xFFFFFFFFFFFFFFFF)
DECL|macro|PCIBR_D32_BASE_UNSET
mdefine_line|#define PCIBR_D32_BASE_UNSET    (0xFFFFFFFF)
DECL|macro|INFO_LBL_PCIBR_ASIC_REV
mdefine_line|#define INFO_LBL_PCIBR_ASIC_REV &quot;_pcibr_asic_rev&quot;
DECL|macro|PCIBR_SOFT_LIST
mdefine_line|#define PCIBR_SOFT_LIST 1
macro_line|#if PCIBR_SOFT_LIST
DECL|typedef|pcibr_list_p
r_typedef
r_struct
id|pcibr_list_s
op_star
id|pcibr_list_p
suffix:semicolon
DECL|struct|pcibr_list_s
r_struct
id|pcibr_list_s
(brace
DECL|member|bl_next
id|pcibr_list_p
id|bl_next
suffix:semicolon
DECL|member|bl_soft
id|pcibr_soft_t
id|bl_soft
suffix:semicolon
DECL|member|bl_vhdl
id|vertex_hdl_t
id|bl_vhdl
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* PCIBR_SOFT_LIST */
singleline_comment|// Devices per widget: 2 buses, 2 slots per bus, 8 functions per slot.
DECL|macro|DEV_PER_WIDGET
mdefine_line|#define DEV_PER_WIDGET (2*2*8)
DECL|struct|sn_flush_device_list
r_struct
id|sn_flush_device_list
(brace
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|pin
r_int
id|pin
suffix:semicolon
DECL|struct|bar_list
r_struct
id|bar_list
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|bar_list
)brace
id|bar_list
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
DECL|member|force_int_addr
r_int
r_int
id|force_int_addr
suffix:semicolon
DECL|member|flush_addr
r_volatile
r_int
r_int
id|flush_addr
suffix:semicolon
DECL|member|flush_lock
id|spinlock_t
id|flush_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sn_flush_nasid_entry
r_struct
id|sn_flush_nasid_entry
(brace
DECL|member|widget_p
r_struct
id|sn_flush_device_list
op_star
op_star
id|widget_p
suffix:semicolon
DECL|member|iio_itte1
r_int
r_int
id|iio_itte1
suffix:semicolon
DECL|member|iio_itte2
r_int
r_int
id|iio_itte2
suffix:semicolon
DECL|member|iio_itte3
r_int
r_int
id|iio_itte3
suffix:semicolon
DECL|member|iio_itte4
r_int
r_int
id|iio_itte4
suffix:semicolon
DECL|member|iio_itte5
r_int
r_int
id|iio_itte5
suffix:semicolon
DECL|member|iio_itte6
r_int
r_int
id|iio_itte6
suffix:semicolon
DECL|member|iio_itte7
r_int
r_int
id|iio_itte7
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_PCI_PCIBR_PRIVATE_H */
eof
