multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_PCI_PCIBR_PRIVATE_H
DECL|macro|_ASM_SN_PCI_PCIBR_PRIVATE_H
mdefine_line|#define _ASM_SN_PCI_PCIBR_PRIVATE_H
multiline_comment|/*&n; * pcibr_private.h -- private definitions for pcibr&n; * only the pcibr driver (and its closest friends)&n; * should ever peek into this file.&n; */
macro_line|#include &lt;asm/sn/pci/pciio_private.h&gt;
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
r_int
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
mdefine_line|#define&t;bi_func&t;&t;bi_pi.pi_func&t;/* handler function (when connected) */
DECL|macro|bi_arg
mdefine_line|#define&t;bi_arg&t;&t;bi_pi.pi_arg&t;/* handler parameter (when connected) */
DECL|macro|bi_tinfo
mdefine_line|#define bi_tinfo&t;bi_pi.pi_tinfo&t;/* Thread info (when connected) */
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
)brace
suffix:semicolon
multiline_comment|/*&n; * per-connect point pcibr data, including&n; * standard pciio data in-line:&n; */
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
mdefine_line|#define&t;f_window&t;f_c.c_window&t;/* state of BASE regs */
DECL|macro|f_rbase
mdefine_line|#define&t;f_rbase&t;&t;f_c.c_rbase&t;/* expansion rom base */
DECL|macro|f_rsize
mdefine_line|#define&t;f_rsize&t;&t;f_c.c_rsize&t;/* expansion rom size */
DECL|macro|f_piospace
mdefine_line|#define&t;f_piospace&t;f_c.c_piospace&t;/* additional I/O spaces allocated */
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
DECL|member|iw_intr
id|bridgereg_t
id|iw_intr
suffix:semicolon
multiline_comment|/* bits in b_int_status */
DECL|member|iw_list
id|pcibr_intr_list_t
id|iw_list
suffix:semicolon
multiline_comment|/* ghostbusters! */
)brace
suffix:semicolon
DECL|macro|PCIBR_ISR_ERR_START
mdefine_line|#define&t;PCIBR_ISR_ERR_START&t;8
DECL|macro|PCIBR_ISR_MAX_ERRS
mdefine_line|#define PCIBR_ISR_MAX_ERRS &t;32
multiline_comment|/* =====================================================================&n; *            Bridge Device State structure&n; *&n; *      one instance of this structure is kept for each&n; *      Bridge ASIC in the system.&n; */
DECL|struct|pcibr_soft_s
r_struct
id|pcibr_soft_s
(brace
DECL|member|bs_conn
id|devfs_handle_t
id|bs_conn
suffix:semicolon
multiline_comment|/* xtalk connection point */
DECL|member|bs_vhdl
id|devfs_handle_t
id|bs_vhdl
suffix:semicolon
multiline_comment|/* vertex owned by pcibr */
DECL|member|bs_int_enable
r_int
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
id|devfs_handle_t
id|bs_master
suffix:semicolon
multiline_comment|/* xtalk master vertex */
DECL|member|bs_mxid
id|xwidgetnum_t
id|bs_mxid
suffix:semicolon
multiline_comment|/* master&squot;s xtalk ID number */
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
DECL|member|bs_int_ate_map
r_struct
id|map
op_star
id|bs_int_ate_map
suffix:semicolon
multiline_comment|/* rmalloc map for internal ATEs */
DECL|member|bs_ext_ate_map
r_struct
id|map
op_star
id|bs_ext_ate_map
suffix:semicolon
multiline_comment|/* rmalloc map for external ATEs */
DECL|member|bs_int_ate_size
r_int
id|bs_int_ate_size
suffix:semicolon
multiline_comment|/* number of internal ates */
DECL|member|bs_xbridge
r_int
id|bs_xbridge
suffix:semicolon
multiline_comment|/* if 1 then xbridge */
DECL|member|bs_rev_num
r_int
id|bs_rev_num
suffix:semicolon
multiline_comment|/* revision number of Bridge */
DECL|member|bs_dma_flags
r_int
id|bs_dma_flags
suffix:semicolon
multiline_comment|/* revision-implied DMA flags */
multiline_comment|/*&n;     * Lock used primarily to get mutual exclusion while managing any&n;     * bridge resources..&n;     */
DECL|member|bs_lock
id|lock_t
id|bs_lock
suffix:semicolon
DECL|member|bs_noslot_conn
id|devfs_handle_t
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
id|devfs_handle_t
id|slot_conn
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
r_int
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
multiline_comment|/* RRB MANAGEMENT&n;     * bs_rrb_fixed: bitmap of slots whose RRB&n;     *&t;allocations we should not &quot;automatically&quot; change&n;     * bs_rrb_avail: number of RRBs that have not&n;     *  been allocated or reserved for {even,odd} slots&n;     * bs_rrb_res: number of RRBs reserved for the&n;     *&t;use of the index slot number&n;     * bs_rrb_valid: number of RRBs marked valid&n;     *&t;for the indexed slot number; indexes 8-15&n;     *&t;are for the virtual channels for slots 0-7.&n;     */
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
DECL|member|bs_rrb_valid
r_int
id|bs_rrb_valid
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* Each Bridge interrupt bit has a single XIO&n;&t; * interrupt channel allocated.&n;&t; */
DECL|member|bsi_xtalk_intr
id|xtalk_intr_t
id|bsi_xtalk_intr
suffix:semicolon
multiline_comment|/*&n;&t; * We do not like sharing PCI interrrupt lines&n;&t; * between devices, but the Origin 200 PCI&n;&t; * layout forces us to do so.&n;&t; */
DECL|member|bsi_pcibr_intr_list
id|pcibr_intr_list_t
id|bsi_pcibr_intr_list
suffix:semicolon
DECL|member|bsi_pcibr_intr_wrap
id|pcibr_intr_wrap_t
id|bsi_pcibr_intr_wrap
suffix:semicolon
DECL|member|bsi_pcibr_wrap_set
r_int
id|bsi_pcibr_wrap_set
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
multiline_comment|/*&n;     * We stash away some information in this structure on getting&n;     * an error interrupt. This information is used during PIO read/&n;     * write error handling.&n;     *&n;     * As it stands now, we do not re-enable the error interrupt&n;     * till the error is resolved. Error resolution happens either at&n;     * bus error time for PIO Read errors (~100 microseconds), or at&n;     * the scheduled timeout time for PIO write errors (~milliseconds).&n;     * If this delay causes problems, we may need to move towards&n;     * a different scheme..&n;     *&n;     * Note that there is no locking while looking at this data structure.&n;     * There should not be any race between bus error code and&n;     * error interrupt code.. will look into this if needed.&n;     */
DECL|struct|br_errintr_info
r_struct
id|br_errintr_info
(brace
DECL|member|bserr_toutcnt
r_int
id|bserr_toutcnt
suffix:semicolon
macro_line|#ifdef IRIX
DECL|member|bserr_toutid
id|toid_t
id|bserr_toutid
suffix:semicolon
multiline_comment|/* Timeout started by errintr */
macro_line|#endif
DECL|member|bserr_addr
id|iopaddr_t
id|bserr_addr
suffix:semicolon
multiline_comment|/* Address where error occurred */
DECL|member|bserr_intstat
id|bridgereg_t
id|bserr_intstat
suffix:semicolon
multiline_comment|/* interrupts active at error time */
DECL|member|bs_errinfo
)brace
id|bs_errinfo
suffix:semicolon
multiline_comment|/*&n;     * PCI Bus Space allocation data structure.&n;     * This info is used to satisfy the callers of pcibr_piospace_alloc&n;     * interface. Most of these users need &quot;large&quot; amounts of PIO&n;     * space (typically in Megabytes), and they generally tend to&n;     * take once and never release..&n;     * For Now use a simple algorithm to manage it. On allocation,&n;     * Update the _base field to reflect next free address.&n;     *&n;     * Freeing does nothing.. So, once allocated, it&squot;s gone for good.&n;     */
DECL|struct|br_pcisp_info
r_struct
id|br_pcisp_info
(brace
DECL|member|pci_io_base
id|iopaddr_t
id|pci_io_base
suffix:semicolon
DECL|member|pci_io_last
id|iopaddr_t
id|pci_io_last
suffix:semicolon
DECL|member|pci_swin_base
id|iopaddr_t
id|pci_swin_base
suffix:semicolon
DECL|member|pci_swin_last
id|iopaddr_t
id|pci_swin_last
suffix:semicolon
DECL|member|pci_mem_base
id|iopaddr_t
id|pci_mem_base
suffix:semicolon
DECL|member|pci_mem_last
id|iopaddr_t
id|pci_mem_last
suffix:semicolon
DECL|member|bs_spinfo
)brace
id|bs_spinfo
suffix:semicolon
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
r_extern
r_int
id|pcibr_prefetch_enable_rev
comma
id|pcibr_wg_enable_rev
suffix:semicolon
multiline_comment|/*&n; * Number of bridge non-fatal error interrupts we can see before&n; * we decide to disable that interrupt.&n; */
DECL|macro|PCIBR_ERRINTR_DISABLE_LEVEL
mdefine_line|#define&t;PCIBR_ERRINTR_DISABLE_LEVEL&t;10000
multiline_comment|/* =====================================================================&n; *    Bridge (pcibr) state management functions&n; *&n; *      pcibr_soft_get is here because we do it in a lot&n; *      of places and I want to make sure they all stay&n; *      in step with each other.&n; *&n; *      pcibr_soft_set is here because I want it to be&n; *      closely associated with pcibr_soft_get, even&n; *      though it is only called in one place.&n; */
DECL|macro|pcibr_soft_get
mdefine_line|#define pcibr_soft_get(v)       ((pcibr_soft_t)hwgraph_fastinfo_get((v)))
DECL|macro|pcibr_soft_set
mdefine_line|#define pcibr_soft_set(v,i)     (hwgraph_fastinfo_set((v), (arbitrary_info_t)(i)))
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_PCI_PCIBR_PRIVATE_H */
eof
