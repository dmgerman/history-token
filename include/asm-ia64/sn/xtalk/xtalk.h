multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_XTALK_XTALK_H
DECL|macro|_ASM_IA64_SN_XTALK_XTALK_H
mdefine_line|#define _ASM_IA64_SN_XTALK_XTALK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;asm/sn/sgi.h&quot;
macro_line|#endif
multiline_comment|/*&n; * xtalk.h -- platform-independent crosstalk interface&n; */
multiline_comment|/*&n; * User-level device driver visible types&n; */
DECL|typedef|xwidgetnum_t
r_typedef
r_char
id|xwidgetnum_t
suffix:semicolon
multiline_comment|/* xtalk widget number  (0..15) */
DECL|macro|XWIDGET_NONE
mdefine_line|#define XWIDGET_NONE&t;&t;(-1)
DECL|typedef|xwidget_part_num_t
r_typedef
r_int
id|xwidget_part_num_t
suffix:semicolon
multiline_comment|/* xtalk widget part number */
DECL|macro|XWIDGET_PART_NUM_NONE
mdefine_line|#define XWIDGET_PART_NUM_NONE&t;(-1)
DECL|typedef|xwidget_rev_num_t
r_typedef
r_int
id|xwidget_rev_num_t
suffix:semicolon
multiline_comment|/* xtalk widget revision number */
DECL|macro|XWIDGET_REV_NUM_NONE
mdefine_line|#define XWIDGET_REV_NUM_NONE&t;(-1)
DECL|typedef|xwidget_mfg_num_t
r_typedef
r_int
id|xwidget_mfg_num_t
suffix:semicolon
multiline_comment|/* xtalk widget manufacturing ID */
DECL|macro|XWIDGET_MFG_NUM_NONE
mdefine_line|#define XWIDGET_MFG_NUM_NONE&t;(-1)
DECL|typedef|xtalk_piomap_t
r_typedef
r_struct
id|xtalk_piomap_s
op_star
id|xtalk_piomap_t
suffix:semicolon
multiline_comment|/* It is often convenient to fold the XIO target port&n; * number into the XIO address.&n; */
DECL|macro|XIO_NOWHERE
mdefine_line|#define&t;XIO_NOWHERE&t;(0xFFFFFFFFFFFFFFFFull)
DECL|macro|XIO_ADDR_BITS
mdefine_line|#define&t;XIO_ADDR_BITS&t;(0x0000FFFFFFFFFFFFull)
DECL|macro|XIO_PORT_BITS
mdefine_line|#define&t;XIO_PORT_BITS&t;(0xF000000000000000ull)
DECL|macro|XIO_PORT_SHIFT
mdefine_line|#define&t;XIO_PORT_SHIFT&t;(60)
DECL|macro|XIO_PACKED
mdefine_line|#define&t;XIO_PACKED(x)&t;(((x)&amp;XIO_PORT_BITS) != 0)
DECL|macro|XIO_ADDR
mdefine_line|#define&t;XIO_ADDR(x)&t;((x)&amp;XIO_ADDR_BITS)
DECL|macro|XIO_PORT
mdefine_line|#define&t;XIO_PORT(x)&t;((xwidgetnum_t)(((x)&amp;XIO_PORT_BITS) &gt;&gt; XIO_PORT_SHIFT))
DECL|macro|XIO_PACK
mdefine_line|#define&t;XIO_PACK(p,o)&t;((((uint64_t)(p))&lt;&lt;XIO_PORT_SHIFT) | ((o)&amp;XIO_ADDR_BITS))
multiline_comment|/*&n; * Kernel/driver only definitions&n; */
macro_line|#if __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/alenlist.h&gt;
macro_line|#include &lt;asm/sn/ioerror.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/dmamap.h&gt;
r_struct
id|xwidget_hwid_s
suffix:semicolon
multiline_comment|/*&n; *    Acceptable flag bits for xtalk service calls&n; *&n; * XTALK_FIXED: require that mappings be established&n; *&t;using fixed sharable resources; address&n; *&t;translation results will be permanently&n; *&t;available. (PIOMAP_FIXED and DMAMAP_FIXED are&n; *&t;the same numeric value and are acceptable).&n; * XTALK_NOSLEEP: if any part of the operation would&n; *&t;sleep waiting for resoruces, return an error&n; *&t;instead. (PIOMAP_NOSLEEP and DMAMAP_NOSLEEP are&n; *&t;the same numeric value and are acceptable).&n; * XTALK_INPLACE: when operating on alenlist structures,&n; *&t;reuse the source alenlist rather than creating a&n; *&t;new one. (PIOMAP_INPLACE and DMAMAP_INPLACE are&n; *&t;the same numeric value and are acceptable).&n; */
DECL|macro|XTALK_FIXED
mdefine_line|#define&t;XTALK_FIXED&t;&t;DMAMAP_FIXED
DECL|macro|XTALK_NOSLEEP
mdefine_line|#define&t;XTALK_NOSLEEP&t;&t;DMAMAP_NOSLEEP
DECL|macro|XTALK_INPLACE
mdefine_line|#define&t;XTALK_INPLACE&t;&t;DMAMAP_INPLACE
multiline_comment|/* PIO MANAGEMENT */
r_typedef
id|xtalk_piomap_t
DECL|typedef|xtalk_piomap_alloc_f
id|xtalk_piomap_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* set up mapping for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* map for this xtalk_addr range */
r_int
id|byte_count
comma
r_int
id|byte_count_max
comma
multiline_comment|/* maximum size of a mapping */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in sys/pio.h */
r_typedef
r_void
DECL|typedef|xtalk_piomap_free_f
id|xtalk_piomap_free_f
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_typedef
id|caddr_t
DECL|typedef|xtalk_piomap_addr_f
id|xtalk_piomap_addr_f
(paren
id|xtalk_piomap_t
id|xtalk_piomap
comma
multiline_comment|/* mapping resources */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* map for this xtalk address */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_typedef
r_void
DECL|typedef|xtalk_piomap_done_f
id|xtalk_piomap_done_f
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_typedef
id|caddr_t
DECL|typedef|xtalk_piotrans_addr_f
id|xtalk_piotrans_addr_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* Crosstalk address */
r_int
id|byte_count
comma
multiline_comment|/* map this many bytes */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* (currently unused) */
r_extern
id|caddr_t
id|xtalk_pio_addr
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* Crosstalk address */
r_int
id|byte_count
comma
multiline_comment|/* map this many bytes */
id|xtalk_piomap_t
op_star
id|xtalk_piomapp
comma
multiline_comment|/* RETURNS mapping resources */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* (currently unused) */
multiline_comment|/* DMA MANAGEMENT */
DECL|typedef|xtalk_dmamap_t
r_typedef
r_struct
id|xtalk_dmamap_s
op_star
id|xtalk_dmamap_t
suffix:semicolon
r_typedef
id|xtalk_dmamap_t
DECL|typedef|xtalk_dmamap_alloc_f
id|xtalk_dmamap_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* set up mappings for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
r_int
id|byte_count_max
comma
multiline_comment|/* max size of a mapping */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_typedef
r_void
DECL|typedef|xtalk_dmamap_free_f
id|xtalk_dmamap_free_f
(paren
id|xtalk_dmamap_t
id|dmamap
)paren
suffix:semicolon
r_typedef
id|iopaddr_t
DECL|typedef|xtalk_dmamap_addr_f
id|xtalk_dmamap_addr_f
(paren
id|xtalk_dmamap_t
id|dmamap
comma
multiline_comment|/* use these mapping resources */
id|paddr_t
id|paddr
comma
multiline_comment|/* map for this address */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_typedef
id|alenlist_t
DECL|typedef|xtalk_dmamap_list_f
id|xtalk_dmamap_list_f
(paren
id|xtalk_dmamap_t
id|dmamap
comma
multiline_comment|/* use these mapping resources */
id|alenlist_t
id|alenlist
comma
multiline_comment|/* map this address/length list */
r_int
id|flags
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_dmamap_done_f
id|xtalk_dmamap_done_f
(paren
id|xtalk_dmamap_t
id|dmamap
)paren
suffix:semicolon
r_typedef
id|iopaddr_t
DECL|typedef|xtalk_dmatrans_addr_f
id|xtalk_dmatrans_addr_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|paddr_t
id|paddr
comma
multiline_comment|/* system physical address */
r_int
id|byte_count
comma
multiline_comment|/* length */
r_int
id|flags
)paren
suffix:semicolon
r_typedef
id|alenlist_t
DECL|typedef|xtalk_dmatrans_list_f
id|xtalk_dmatrans_list_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|alenlist_t
id|palenlist
comma
multiline_comment|/* system address/length list */
r_int
id|flags
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_dmamap_drain_f
id|xtalk_dmamap_drain_f
(paren
id|xtalk_dmamap_t
id|map
)paren
suffix:semicolon
multiline_comment|/* drain this map&squot;s channel */
r_typedef
r_void
DECL|typedef|xtalk_dmaaddr_drain_f
id|xtalk_dmaaddr_drain_f
(paren
id|vertex_hdl_t
id|vhdl
comma
multiline_comment|/* drain channel from this device */
id|paddr_t
id|addr
comma
multiline_comment|/* to this physical address */
r_int
id|bytes
)paren
suffix:semicolon
multiline_comment|/* for this many bytes */
r_typedef
r_void
DECL|typedef|xtalk_dmalist_drain_f
id|xtalk_dmalist_drain_f
(paren
id|vertex_hdl_t
id|vhdl
comma
multiline_comment|/* drain channel from this device */
id|alenlist_t
id|list
)paren
suffix:semicolon
multiline_comment|/* for this set of physical blocks */
multiline_comment|/* INTERRUPT MANAGEMENT */
multiline_comment|/*&n; * A xtalk interrupt resource handle.  When resources are allocated&n; * in order to satisfy a xtalk_intr_alloc request, a xtalk_intr handle&n; * is returned.  xtalk_intr_connect associates a software handler with&n;&n; * these system resources.&n; */
DECL|typedef|xtalk_intr_t
r_typedef
r_struct
id|xtalk_intr_s
op_star
id|xtalk_intr_t
suffix:semicolon
multiline_comment|/*&n; * When a crosstalk device connects an interrupt, it passes in a function&n; * that knows how to set its xtalk interrupt register appropriately.  The&n; * low-level interrupt code may invoke this function later in order to&n; * migrate an interrupt transparently to the device driver(s) that use this&n; * interrupt.&n; *&n; * The argument passed to this function contains enough information for a&n; * crosstalk device to (re-)target an interrupt.  A function of this type&n; * must be supplied by every crosstalk driver.&n; */
r_typedef
r_int
DECL|typedef|xtalk_intr_setfunc_f
id|xtalk_intr_setfunc_f
(paren
id|xtalk_intr_t
id|intr_hdl
)paren
suffix:semicolon
multiline_comment|/* interrupt handle */
r_typedef
id|xtalk_intr_t
DECL|typedef|xtalk_intr_alloc_f
id|xtalk_intr_alloc_f
(paren
id|vertex_hdl_t
id|dev
comma
multiline_comment|/* which crosstalk device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|vertex_hdl_t
id|owner_dev
)paren
suffix:semicolon
multiline_comment|/* owner of this intr */
r_typedef
r_void
DECL|typedef|xtalk_intr_free_f
id|xtalk_intr_free_f
(paren
id|xtalk_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_typedef
r_int
DECL|typedef|xtalk_intr_connect_f
id|xtalk_intr_connect_f
(paren
id|xtalk_intr_t
id|intr_hdl
comma
multiline_comment|/* xtalk intr resource handle */
id|intr_func_t
id|intr_func
comma
multiline_comment|/* xtalk intr handler */
r_void
op_star
id|intr_arg
comma
multiline_comment|/* arg to intr handler */
id|xtalk_intr_setfunc_f
op_star
id|setfunc
comma
multiline_comment|/* func to set intr hw */
r_void
op_star
id|setfunc_arg
)paren
suffix:semicolon
multiline_comment|/* arg to setfunc */
r_typedef
r_void
DECL|typedef|xtalk_intr_disconnect_f
id|xtalk_intr_disconnect_f
(paren
id|xtalk_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_typedef
id|vertex_hdl_t
DECL|typedef|xtalk_intr_cpu_get_f
id|xtalk_intr_cpu_get_f
(paren
id|xtalk_intr_t
id|intr_hdl
)paren
suffix:semicolon
multiline_comment|/* xtalk intr resource handle */
multiline_comment|/* CONFIGURATION MANAGEMENT */
r_typedef
r_void
DECL|typedef|xtalk_provider_startup_f
id|xtalk_provider_startup_f
(paren
id|vertex_hdl_t
id|xtalk_provider
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_provider_shutdown_f
id|xtalk_provider_shutdown_f
(paren
id|vertex_hdl_t
id|xtalk_provider
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_widgetdev_enable_f
id|xtalk_widgetdev_enable_f
(paren
id|vertex_hdl_t
comma
r_int
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_widgetdev_shutdown_f
id|xtalk_widgetdev_shutdown_f
(paren
id|vertex_hdl_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Early Action Support */
r_typedef
id|caddr_t
DECL|typedef|xtalk_early_piotrans_addr_f
id|xtalk_early_piotrans_addr_f
(paren
id|xwidget_part_num_t
id|part_num
comma
id|xwidget_mfg_num_t
id|mfg_num
comma
r_int
id|which
comma
id|iopaddr_t
id|xtalk_addr
comma
r_int
id|byte_count
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * Adapters that provide a crosstalk interface adhere to this software interface.&n; */
DECL|struct|xtalk_provider_s
r_typedef
r_struct
id|xtalk_provider_s
(brace
multiline_comment|/* PIO MANAGEMENT */
DECL|member|piomap_alloc
id|xtalk_piomap_alloc_f
op_star
id|piomap_alloc
suffix:semicolon
DECL|member|piomap_free
id|xtalk_piomap_free_f
op_star
id|piomap_free
suffix:semicolon
DECL|member|piomap_addr
id|xtalk_piomap_addr_f
op_star
id|piomap_addr
suffix:semicolon
DECL|member|piomap_done
id|xtalk_piomap_done_f
op_star
id|piomap_done
suffix:semicolon
DECL|member|piotrans_addr
id|xtalk_piotrans_addr_f
op_star
id|piotrans_addr
suffix:semicolon
multiline_comment|/* DMA MANAGEMENT */
DECL|member|dmamap_alloc
id|xtalk_dmamap_alloc_f
op_star
id|dmamap_alloc
suffix:semicolon
DECL|member|dmamap_free
id|xtalk_dmamap_free_f
op_star
id|dmamap_free
suffix:semicolon
DECL|member|dmamap_addr
id|xtalk_dmamap_addr_f
op_star
id|dmamap_addr
suffix:semicolon
DECL|member|dmamap_list
id|xtalk_dmamap_list_f
op_star
id|dmamap_list
suffix:semicolon
DECL|member|dmamap_done
id|xtalk_dmamap_done_f
op_star
id|dmamap_done
suffix:semicolon
DECL|member|dmatrans_addr
id|xtalk_dmatrans_addr_f
op_star
id|dmatrans_addr
suffix:semicolon
DECL|member|dmatrans_list
id|xtalk_dmatrans_list_f
op_star
id|dmatrans_list
suffix:semicolon
DECL|member|dmamap_drain
id|xtalk_dmamap_drain_f
op_star
id|dmamap_drain
suffix:semicolon
DECL|member|dmaaddr_drain
id|xtalk_dmaaddr_drain_f
op_star
id|dmaaddr_drain
suffix:semicolon
DECL|member|dmalist_drain
id|xtalk_dmalist_drain_f
op_star
id|dmalist_drain
suffix:semicolon
multiline_comment|/* INTERRUPT MANAGEMENT */
DECL|member|intr_alloc
id|xtalk_intr_alloc_f
op_star
id|intr_alloc
suffix:semicolon
DECL|member|intr_alloc_nothd
id|xtalk_intr_alloc_f
op_star
id|intr_alloc_nothd
suffix:semicolon
DECL|member|intr_free
id|xtalk_intr_free_f
op_star
id|intr_free
suffix:semicolon
DECL|member|intr_connect
id|xtalk_intr_connect_f
op_star
id|intr_connect
suffix:semicolon
DECL|member|intr_disconnect
id|xtalk_intr_disconnect_f
op_star
id|intr_disconnect
suffix:semicolon
multiline_comment|/* CONFIGURATION MANAGEMENT */
DECL|member|provider_startup
id|xtalk_provider_startup_f
op_star
id|provider_startup
suffix:semicolon
DECL|member|provider_shutdown
id|xtalk_provider_shutdown_f
op_star
id|provider_shutdown
suffix:semicolon
multiline_comment|/* Error Management     */
DECL|typedef|xtalk_provider_t
)brace
id|xtalk_provider_t
suffix:semicolon
multiline_comment|/* Crosstalk devices use these standard Crosstalk provider interfaces */
r_extern
id|xtalk_piomap_alloc_f
id|xtalk_piomap_alloc
suffix:semicolon
r_extern
id|xtalk_piomap_free_f
id|xtalk_piomap_free
suffix:semicolon
r_extern
id|xtalk_piomap_addr_f
id|xtalk_piomap_addr
suffix:semicolon
r_extern
id|xtalk_piomap_done_f
id|xtalk_piomap_done
suffix:semicolon
r_extern
id|xtalk_piotrans_addr_f
id|xtalk_piotrans_addr
suffix:semicolon
r_extern
id|xtalk_dmamap_alloc_f
id|xtalk_dmamap_alloc
suffix:semicolon
r_extern
id|xtalk_dmamap_free_f
id|xtalk_dmamap_free
suffix:semicolon
r_extern
id|xtalk_dmamap_addr_f
id|xtalk_dmamap_addr
suffix:semicolon
r_extern
id|xtalk_dmamap_list_f
id|xtalk_dmamap_list
suffix:semicolon
r_extern
id|xtalk_dmamap_done_f
id|xtalk_dmamap_done
suffix:semicolon
r_extern
id|xtalk_dmatrans_addr_f
id|xtalk_dmatrans_addr
suffix:semicolon
r_extern
id|xtalk_dmatrans_list_f
id|xtalk_dmatrans_list
suffix:semicolon
r_extern
id|xtalk_dmamap_drain_f
id|xtalk_dmamap_drain
suffix:semicolon
r_extern
id|xtalk_dmaaddr_drain_f
id|xtalk_dmaaddr_drain
suffix:semicolon
r_extern
id|xtalk_dmalist_drain_f
id|xtalk_dmalist_drain
suffix:semicolon
r_extern
id|xtalk_intr_alloc_f
id|xtalk_intr_alloc
suffix:semicolon
r_extern
id|xtalk_intr_alloc_f
id|xtalk_intr_alloc_nothd
suffix:semicolon
r_extern
id|xtalk_intr_free_f
id|xtalk_intr_free
suffix:semicolon
r_extern
id|xtalk_intr_connect_f
id|xtalk_intr_connect
suffix:semicolon
r_extern
id|xtalk_intr_disconnect_f
id|xtalk_intr_disconnect
suffix:semicolon
r_extern
id|xtalk_intr_cpu_get_f
id|xtalk_intr_cpu_get
suffix:semicolon
r_extern
id|xtalk_provider_startup_f
id|xtalk_provider_startup
suffix:semicolon
r_extern
id|xtalk_provider_shutdown_f
id|xtalk_provider_shutdown
suffix:semicolon
r_extern
id|xtalk_widgetdev_enable_f
id|xtalk_widgetdev_enable
suffix:semicolon
r_extern
id|xtalk_widgetdev_shutdown_f
id|xtalk_widgetdev_shutdown
suffix:semicolon
r_extern
id|xtalk_early_piotrans_addr_f
id|xtalk_early_piotrans_addr
suffix:semicolon
multiline_comment|/* error management */
r_extern
r_int
id|xtalk_error_handler
c_func
(paren
id|vertex_hdl_t
comma
r_int
comma
id|ioerror_mode_t
comma
id|ioerror_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic crosstalk interface, for use with all crosstalk providers&n; * and all crosstalk devices.&n; */
DECL|typedef|xtalk_intr_vector_t
r_typedef
id|unchar
id|xtalk_intr_vector_t
suffix:semicolon
multiline_comment|/* crosstalk interrupt vector (0..255) */
DECL|macro|XTALK_INTR_VECTOR_NONE
mdefine_line|#define XTALK_INTR_VECTOR_NONE&t;(xtalk_intr_vector_t)0
multiline_comment|/* Generic crosstalk interrupt interfaces */
r_extern
id|vertex_hdl_t
id|xtalk_intr_dev_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
r_extern
id|xwidgetnum_t
id|xtalk_intr_target_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
r_extern
id|xtalk_intr_vector_t
id|xtalk_intr_vector_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|xtalk_intr_addr_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
id|xtalk_intr_cpu_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
r_extern
r_void
op_star
id|xtalk_intr_sfarg_get
c_func
(paren
id|xtalk_intr_t
id|xtalk_intr
)paren
suffix:semicolon
multiline_comment|/* Generic crosstalk pio interfaces */
r_extern
id|vertex_hdl_t
id|xtalk_pio_dev_get
c_func
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_extern
id|xwidgetnum_t
id|xtalk_pio_target_get
c_func
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|xtalk_pio_xtalk_addr_get
c_func
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_extern
r_int
id|xtalk_pio_mapsz_get
c_func
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
r_extern
id|caddr_t
id|xtalk_pio_kvaddr_get
c_func
(paren
id|xtalk_piomap_t
id|xtalk_piomap
)paren
suffix:semicolon
multiline_comment|/* Generic crosstalk dma interfaces */
r_extern
id|vertex_hdl_t
id|xtalk_dma_dev_get
c_func
(paren
id|xtalk_dmamap_t
id|xtalk_dmamap
)paren
suffix:semicolon
r_extern
id|xwidgetnum_t
id|xtalk_dma_target_get
c_func
(paren
id|xtalk_dmamap_t
id|xtalk_dmamap
)paren
suffix:semicolon
multiline_comment|/* Register/unregister Crosstalk providers and get implementation handle */
r_extern
r_void
id|xtalk_set_early_piotrans_addr
c_func
(paren
id|xtalk_early_piotrans_addr_f
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xtalk_provider_register
c_func
(paren
id|vertex_hdl_t
id|provider
comma
id|xtalk_provider_t
op_star
id|xtalk_fns
)paren
suffix:semicolon
r_extern
r_void
id|xtalk_provider_unregister
c_func
(paren
id|vertex_hdl_t
id|provider
)paren
suffix:semicolon
r_extern
id|xtalk_provider_t
op_star
id|xtalk_provider_fns_get
c_func
(paren
id|vertex_hdl_t
id|provider
)paren
suffix:semicolon
multiline_comment|/* Crosstalk Switch generic layer, for use by initialization code */
r_extern
r_void
id|xswitch_census
c_func
(paren
id|vertex_hdl_t
id|xswitchv
)paren
suffix:semicolon
r_extern
r_void
id|xswitch_init_widgets
c_func
(paren
id|vertex_hdl_t
id|xswitchv
)paren
suffix:semicolon
multiline_comment|/* early init interrupt management */
r_typedef
r_void
DECL|typedef|xwidget_intr_preset_f
id|xwidget_intr_preset_f
(paren
r_void
op_star
id|which_widget
comma
r_int
id|which_widget_intr
comma
id|xwidgetnum_t
id|targ
comma
id|iopaddr_t
id|addr
comma
id|xtalk_intr_vector_t
id|vect
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_intr_prealloc_f
id|xtalk_intr_prealloc_f
(paren
r_void
op_star
id|which_xtalk
comma
id|xtalk_intr_vector_t
id|xtalk_vector
comma
id|xwidget_intr_preset_f
op_star
id|preset_func
comma
r_void
op_star
id|which_widget
comma
r_int
id|which_widget_intr
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|xtalk_intr_preconn_f
id|xtalk_intr_preconn_f
(paren
r_void
op_star
id|which_xtalk
comma
id|xtalk_intr_vector_t
id|xtalk_vector
comma
id|intr_func_t
id|intr_func
comma
id|intr_arg_t
id|intr_arg
)paren
suffix:semicolon
DECL|macro|XTALK_ADDR_TO_UPPER
mdefine_line|#define XTALK_ADDR_TO_UPPER(xtalk_addr) (((iopaddr_t)(xtalk_addr) &gt;&gt; 32) &amp; 0xffff)
DECL|macro|XTALK_ADDR_TO_LOWER
mdefine_line|#define XTALK_ADDR_TO_LOWER(xtalk_addr) ((iopaddr_t)(xtalk_addr) &amp; 0xffffffff)
DECL|typedef|xtalk_intr_setfunc_t
r_typedef
id|xtalk_intr_setfunc_f
op_star
id|xtalk_intr_setfunc_t
suffix:semicolon
DECL|typedef|xtalk_iter_f
r_typedef
r_void
id|xtalk_iter_f
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
suffix:semicolon
r_extern
r_void
id|xtalk_iterate
c_func
(paren
r_char
op_star
id|prefix
comma
id|xtalk_iter_f
op_star
id|func
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_XTALK_XTALK_H */
eof
