multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_IOBUS_H
DECL|macro|_ASM_SN_IOBUS_H
mdefine_line|#define _ASM_SN_IOBUS_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_struct
id|eframe_s
suffix:semicolon
r_struct
id|piomap
suffix:semicolon
r_struct
id|dmamap
suffix:semicolon
multiline_comment|/* for ilvl_t interrupt level, for use with intr_block_level.  Can&squot;t&n; * typedef twice without causing warnings, and some users of this header&n; * file do not already include driver.h, but expect ilvl_t to be defined,&n; * while others include both, leading to the warning ...&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
DECL|typedef|iobush_t
r_typedef
id|__psunsigned_t
id|iobush_t
suffix:semicolon
macro_line|#if __KERNEL__
multiline_comment|/* adapter handle */
DECL|typedef|adap_t
r_typedef
id|devfs_handle_t
id|adap_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* interrupt function */
DECL|typedef|intr_arg_t
r_typedef
r_void
op_star
id|intr_arg_t
suffix:semicolon
DECL|typedef|intr_func_f
r_typedef
r_void
id|intr_func_f
c_func
(paren
id|intr_arg_t
)paren
suffix:semicolon
DECL|typedef|intr_func_t
r_typedef
id|intr_func_f
op_star
id|intr_func_t
suffix:semicolon
DECL|macro|INTR_ARG
mdefine_line|#define&t;INTR_ARG(n)&t;((intr_arg_t)(__psunsigned_t)(n))
multiline_comment|/* system interrupt resource handle -- returned from intr_alloc */
DECL|typedef|intr_t
r_typedef
r_struct
id|intr_s
op_star
id|intr_t
suffix:semicolon
DECL|macro|INTR_HANDLE_NONE
mdefine_line|#define INTR_HANDLE_NONE ((intr_t)0)
multiline_comment|/*&n; * restore interrupt level value, returned from intr_block_level&n; * for use with intr_unblock_level.&n; */
DECL|typedef|rlvl_t
r_typedef
r_void
op_star
id|rlvl_t
suffix:semicolon
multiline_comment|/* &n; * A basic, platform-independent description of I/O requirements for&n; * a device. This structure is usually formed by lboot based on information &n; * in configuration files.  It contains information about PIO, DMA, and&n; * interrupt requirements for a specific instance of a device.&n; *&n; * The pio description is currently unused.&n; *&n; * The dma description describes bandwidth characteristics and bandwidth&n; * allocation requirements. (TBD)&n; *&n; * The Interrupt information describes the priority of interrupt, desired &n; * destination, policy (TBD), whether this is an error interrupt, etc.  &n; * For now, interrupts are targeted to specific CPUs.&n; */
DECL|struct|device_desc_s
r_typedef
r_struct
id|device_desc_s
(brace
multiline_comment|/* pio description (currently none) */
multiline_comment|/* dma description */
multiline_comment|/* TBD: allocated badwidth requirements */
multiline_comment|/* interrupt description */
DECL|member|intr_target
id|devfs_handle_t
id|intr_target
suffix:semicolon
multiline_comment|/* Hardware locator string */
DECL|member|intr_policy
r_int
id|intr_policy
suffix:semicolon
multiline_comment|/* TBD */
DECL|member|intr_swlevel
id|ilvl_t
id|intr_swlevel
suffix:semicolon
multiline_comment|/* software level for blocking intr */
DECL|member|intr_name
r_char
op_star
id|intr_name
suffix:semicolon
multiline_comment|/* name of interrupt, if any */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|typedef|device_desc_t
)brace
op_star
id|device_desc_t
suffix:semicolon
multiline_comment|/* flag values */
DECL|macro|D_INTR_ISERR
mdefine_line|#define&t;D_INTR_ISERR&t;0x1&t;&t;/* interrupt is for error handling */
DECL|macro|D_IS_ASSOC
mdefine_line|#define D_IS_ASSOC&t;0x2&t;&t;/* descriptor is associated with a dev */
DECL|macro|D_INTR_NOTHREAD
mdefine_line|#define D_INTR_NOTHREAD&t;0x4&t;&t;/* Interrupt handler isn&squot;t threaded. */
DECL|macro|INTR_SWLEVEL_NOTHREAD_DEFAULT
mdefine_line|#define INTR_SWLEVEL_NOTHREAD_DEFAULT &t;0&t;/* Default&n;&t;&t;&t;&t;&t;&t; * Interrupt level in case of&n;&t;&t;&t;&t;&t;&t; * non-threaded interrupt &n;&t;&t;&t;&t;&t;&t; * handlers&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* &n; * Drivers use these interfaces to manage device descriptors.&n; *&n; * To examine defaults:&n; *&t;desc = device_desc_default_get(dev);&n; *&t;device_desc_*_get(desc);&n; *&n; * To modify defaults:&n; *&t;desc = device_desc_default_get(dev);&n; *&t;device_desc_*_set(desc);&n; *&n; * To eliminate defaults:&n; *&t;device_desc_default_set(dev, NULL);&n; *&n; * To override defaults:&n; *&t;desc = device_desc_dup(dev);&n; *&t;device_desc_*_set(desc,...);&n; *&t;use device_desc in calls&n; *&t;device_desc_free(desc);&n; *&n; * Software must not set or eliminate default device descriptors for a device while&n; * concurrently get&squot;ing, dup&squot;ing or using them.  Default device descriptors can be &n; * changed only for a device that is quiescent.  In general, device drivers have no&n; * need to permanently change defaults anyway -- they just override defaults, when&n; * necessary.&n; */
r_extern
id|device_desc_t
id|device_desc_dup
c_func
(paren
id|devfs_handle_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_free
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
id|device_desc_t
id|device_desc_default_get
c_func
(paren
id|devfs_handle_t
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_default_set
c_func
(paren
id|devfs_handle_t
id|dev
comma
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|device_desc_intr_target_get
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
r_int
id|device_desc_intr_policy_get
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
id|ilvl_t
id|device_desc_intr_swlevel_get
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
r_char
op_star
id|device_desc_intr_name_get
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
r_int
id|device_desc_flags_get
c_func
(paren
id|device_desc_t
id|device_desc
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_intr_target_set
c_func
(paren
id|device_desc_t
id|device_desc
comma
id|devfs_handle_t
id|target
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_intr_policy_set
c_func
(paren
id|device_desc_t
id|device_desc
comma
r_int
id|policy
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_intr_swlevel_set
c_func
(paren
id|device_desc_t
id|device_desc
comma
id|ilvl_t
id|swlevel
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_intr_name_set
c_func
(paren
id|device_desc_t
id|device_desc
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|device_desc_flags_set
c_func
(paren
id|device_desc_t
id|device_desc
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* IO state */
macro_line|#ifdef COMMENT
DECL|macro|IO_STATE_EMPTY
mdefine_line|#define IO_STATE_EMPTY&t;&t;&t;0x01&t;/* non-existent */
DECL|macro|IO_STATE_INITIALIZING
mdefine_line|#define IO_STATE_INITIALIZING&t;&t;0x02&t;/* being initialized */
DECL|macro|IO_STATE_ATTACHING
mdefine_line|#define IO_STATE_ATTACHING   &t;&t;0x04    /* becoming active */
DECL|macro|IO_STATE_ACTIVE
mdefine_line|#define IO_STATE_ACTIVE      &t;&t;0x08    /* active */
DECL|macro|IO_STATE_DETACHING
mdefine_line|#define IO_STATE_DETACHING   &t;&t;0x10    /* becoming inactive */
DECL|macro|IO_STATE_INACTIVE
mdefine_line|#define IO_STATE_INACTIVE    &t;&t;0x20    /* not in use */
DECL|macro|IO_STATE_ERROR
mdefine_line|#define IO_STATE_ERROR&t;&t;&t;0x40    /* problems */
DECL|macro|IO_STATE_BAD_HARDWARE
mdefine_line|#define IO_STATE_BAD_HARDWARE&t;&t;0x80&t;/* broken hardware */
macro_line|#endif
r_struct
id|edt
suffix:semicolon
multiline_comment|/* return codes */
DECL|macro|RC_OK
mdefine_line|#define RC_OK&t;&t;&t;&t;0&t;
DECL|macro|RC_ERROR
mdefine_line|#define RC_ERROR&t;&t;&t;1
multiline_comment|/* bus configuration management op code */
DECL|macro|IOBUS_CONFIG_ATTACH
mdefine_line|#define IOBUS_CONFIG_ATTACH&t;&t;0&t;/* vary on */
DECL|macro|IOBUS_CONFIG_DETACH
mdefine_line|#define IOBUS_CONFIG_DETACH&t;&t;1&t;/* vary off */
DECL|macro|IOBUS_CONFIG_RECOVER
mdefine_line|#define IOBUS_CONFIG_RECOVER&t;&t;2&t;/* clear error then vary on */
multiline_comment|/* get low-level PIO handle */
r_extern
r_int
id|pio_geth
c_func
(paren
r_struct
id|piomap
op_star
comma
r_int
id|bus
comma
r_int
id|bus_id
comma
r_int
id|subtype
comma
id|iopaddr_t
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* get low-level DMA handle */
r_extern
r_int
id|dma_geth
c_func
(paren
r_struct
id|dmamap
op_star
comma
r_int
id|bus_type
comma
r_int
id|bus_id
comma
r_int
id|dma_type
comma
r_int
id|npages
comma
r_int
id|page_size
comma
r_int
id|flags
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
multiline_comment|/*&n; * Macros for page number and page offsets, using ps as page size&n; */
DECL|macro|x_pnum
mdefine_line|#define x_pnum(addr, ps) ((__psunsigned_t)(addr) / (__psunsigned_t)(ps))
DECL|macro|x_poff
mdefine_line|#define x_poff(addr, ps) ((__psunsigned_t)(addr) &amp; ((__psunsigned_t)(ps) - 1))
macro_line|#endif /* _ASM_SN_IOBUS_H */
eof
