multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_TARGETHW_
DECL|macro|_TARGETHW_
mdefine_line|#define _TARGETHW_
multiline_comment|/*&n;&t; *  PCI Watermark definition&n;&t; */
macro_line|#ifdef&t;PCI
DECL|macro|RX_WATERMARK
mdefine_line|#define&t;RX_WATERMARK&t;24
DECL|macro|TX_WATERMARK
mdefine_line|#define TX_WATERMARK&t;24
DECL|macro|SK_ML_ID_1
mdefine_line|#define SK_ML_ID_1&t;0x20
DECL|macro|SK_ML_ID_2
mdefine_line|#define SK_ML_ID_2&t;0x30
macro_line|#endif
macro_line|#include&t;&quot;h/skfbi.h&quot;
macro_line|#ifndef TAG_MODE&t;
macro_line|#include&t;&quot;h/fplus.h&quot;
macro_line|#else
macro_line|#include&t;&quot;h/fplustm.h&quot;
macro_line|#endif
macro_line|#ifndef&t;HW_PTR
macro_line|#ifdef  MEM_MAPPED_IO
DECL|macro|HW_PTR
mdefine_line|#define HW_PTR  u_long
macro_line|#else
DECL|macro|HW_PTR
mdefine_line|#define HW_PTR  u_short
macro_line|#endif
macro_line|#endif
macro_line|#ifdef MULT_OEM
DECL|macro|OI_STAT_LAST
mdefine_line|#define&t;OI_STAT_LAST&t;&t;0&t;/* end of OEM data base */
DECL|macro|OI_STAT_PRESENT
mdefine_line|#define&t;OI_STAT_PRESENT&t;&t;1&t;/* entry present but not empty */
DECL|macro|OI_STAT_VALID
mdefine_line|#define&t;OI_STAT_VALID&t;&t;2&t;/* holds valid ID, but is not active */ 
DECL|macro|OI_STAT_ACTIVE
mdefine_line|#define&t;OI_STAT_ACTIVE&t;&t;3&t;/* holds valid ID, entry is active */
multiline_comment|/* active = adapter is supported */
multiline_comment|/* Memory representation of IDs must match representation in adapter. */
DECL|struct|s_oem_ids
r_struct
id|s_oem_ids
(brace
DECL|member|oi_status
id|u_char
id|oi_status
suffix:semicolon
multiline_comment|/* Stat: last, present, valid, active */
DECL|member|oi_mark
id|u_char
id|oi_mark
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* &quot;PID00&quot; .. &quot;PID07&quot; ..&t;*/
DECL|member|oi_id
id|u_char
id|oi_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* id bytes, representation as&t;*/
multiline_comment|/* defined by hardware,&t;&t;*/
macro_line|#ifdef PCI
DECL|member|oi_sub_id
id|u_char
id|oi_sub_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* sub id bytes, representation as */
multiline_comment|/* defined by hardware,&t;&t;*/
macro_line|#endif
macro_line|#ifdef ISA
DECL|member|oi_logo_len
id|u_char
id|oi_logo_len
suffix:semicolon
multiline_comment|/* the length of the adapter logo */
DECL|member|oi_logo
id|u_char
id|oi_logo
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* the adapter logo&t;&t;*/
DECL|member|oi_reserved1
id|u_char
id|oi_reserved1
suffix:semicolon
macro_line|#endif&t;/* ISA */
)brace
suffix:semicolon
macro_line|#endif&t;/* MULT_OEM */
DECL|struct|s_smt_hw
r_struct
id|s_smt_hw
(brace
multiline_comment|/*&n;&t; * global&n;&t; */
DECL|member|iop
id|HW_PTR
id|iop
suffix:semicolon
multiline_comment|/* IO base address */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA channel */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ level */
DECL|member|eprom
r_int
id|eprom
suffix:semicolon
multiline_comment|/* FLASH prom */
macro_line|#ifndef&t;PCI
DECL|member|DmaWriteExtraBytes
r_int
id|DmaWriteExtraBytes
suffix:semicolon
multiline_comment|/* add bytes for DMA write */
macro_line|#endif
macro_line|#ifndef SYNC
DECL|member|n_a_send
id|u_short
id|n_a_send
suffix:semicolon
multiline_comment|/* pending send requests */
macro_line|#endif
macro_line|#if&t;(defined(EISA) || defined(MCA) || defined(PCI))
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* slot number */
DECL|member|max_slots
r_int
id|max_slots
suffix:semicolon
multiline_comment|/* maximum number of slots */
macro_line|#endif
macro_line|#if&t;(defined(PCI) || defined(MCA))
DECL|member|wdog_used
r_int
id|wdog_used
suffix:semicolon
multiline_comment|/* TRUE if the watch dog is used */
macro_line|#endif
macro_line|#ifdef&t;MCA
DECL|member|slot_32
r_int
id|slot_32
suffix:semicolon
multiline_comment|/* 32bit slot (1) or 16bit slot (0) */
DECL|member|rev
r_int
id|rev
suffix:semicolon
multiline_comment|/* Board revision (FMx_REV). */
DECL|member|VFullRead
r_int
id|VFullRead
suffix:semicolon
multiline_comment|/* V_full value for DMA read */
DECL|member|VFullWrite
r_int
id|VFullWrite
suffix:semicolon
multiline_comment|/* V_full value for DMA write */
macro_line|#endif
macro_line|#ifdef&t;EISA
DECL|member|led
r_int
id|led
suffix:semicolon
multiline_comment|/* LED for FE card */
DECL|member|dma_rmode
r_int
id|dma_rmode
suffix:semicolon
multiline_comment|/* read mode */
DECL|member|dma_wmode
r_int
id|dma_wmode
suffix:semicolon
multiline_comment|/* write mode */
DECL|member|dma_emode
r_int
id|dma_emode
suffix:semicolon
multiline_comment|/* extend mode */
multiline_comment|/* DMA controller channel dependent io addresses */
DECL|member|dma_base_word_count
id|u_short
id|dma_base_word_count
suffix:semicolon
DECL|member|dma_base_address
id|u_short
id|dma_base_address
suffix:semicolon
DECL|member|dma_base_address_page
id|u_short
id|dma_base_address_page
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;PCI
DECL|member|pci_handle
id|u_short
id|pci_handle
suffix:semicolon
multiline_comment|/* handle to access the BIOS func */
DECL|member|is_imask
id|u_long
id|is_imask
suffix:semicolon
multiline_comment|/* int maske for the int source reg */
DECL|member|phys_mem_addr
id|u_long
id|phys_mem_addr
suffix:semicolon
multiline_comment|/* physical memory address */
DECL|member|mc_dummy
id|u_short
id|mc_dummy
suffix:semicolon
multiline_comment|/* work around for MC compiler bug */
multiline_comment|/*&n;&t; * state of the hardware&n;&t; */
DECL|member|hw_state
id|u_short
id|hw_state
suffix:semicolon
multiline_comment|/* started or stopped */
DECL|macro|STARTED
mdefine_line|#define&t;STARTED&t;&t;1
DECL|macro|STOPPED
mdefine_line|#define&t;STOPPED&t;&t;0
DECL|member|hw_is_64bit
r_int
id|hw_is_64bit
suffix:semicolon
multiline_comment|/* does we have a 64 bit adapter */
macro_line|#endif
macro_line|#ifdef&t;TAG_MODE
DECL|member|pci_fix_value
id|u_long
id|pci_fix_value
suffix:semicolon
multiline_comment|/* value parsed by PCIFIX */
macro_line|#endif
multiline_comment|/*&n;&t; * hwt.c&n;&t; */
DECL|member|t_start
id|u_long
id|t_start
suffix:semicolon
multiline_comment|/* HWT start */
DECL|member|t_stop
id|u_long
id|t_stop
suffix:semicolon
multiline_comment|/* HWT stop */
DECL|member|timer_activ
id|u_short
id|timer_activ
suffix:semicolon
multiline_comment|/* HWT timer active */
multiline_comment|/*&n;&t; * PIC&n;&t; */
DECL|member|pic_a1
id|u_char
id|pic_a1
suffix:semicolon
DECL|member|pic_21
id|u_char
id|pic_21
suffix:semicolon
multiline_comment|/*&n;&t; * GENERIC ; do not modify beyond this line&n;&t; */
multiline_comment|/*&n;&t; * physical and canonical address&n;&t; */
DECL|member|fddi_home_addr
r_struct
id|fddi_addr
id|fddi_home_addr
suffix:semicolon
DECL|member|fddi_canon_addr
r_struct
id|fddi_addr
id|fddi_canon_addr
suffix:semicolon
DECL|member|fddi_phys_addr
r_struct
id|fddi_addr
id|fddi_phys_addr
suffix:semicolon
multiline_comment|/*&n;&t; * mac variables&n;&t; */
DECL|member|mac_pa
r_struct
id|mac_parameter
id|mac_pa
suffix:semicolon
multiline_comment|/* tmin, tmax, tvx, treq .. */
DECL|member|mac_ct
r_struct
id|mac_counter
id|mac_ct
suffix:semicolon
multiline_comment|/* recv., lost, error  */
DECL|member|mac_ring_is_up
id|u_short
id|mac_ring_is_up
suffix:semicolon
multiline_comment|/* ring is up flag */
DECL|member|fp
r_struct
id|s_smt_fp
id|fp
suffix:semicolon
multiline_comment|/* formac+ */
macro_line|#ifdef MULT_OEM
DECL|member|oem_id
r_struct
id|s_oem_ids
op_star
id|oem_id
suffix:semicolon
multiline_comment|/* pointer to selected id */
DECL|member|oem_min_status
r_int
id|oem_min_status
suffix:semicolon
multiline_comment|/* IDs to take care of */
macro_line|#endif&t;/* MULT_OEM */
)brace
suffix:semicolon
macro_line|#endif
eof
