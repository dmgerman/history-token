multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_DRIVER_H
DECL|macro|_ASM_IA64_SN_DRIVER_H
mdefine_line|#define _ASM_IA64_SN_DRIVER_H
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n;** Interface for device driver handle management.&n;**&n;** These functions are mostly for use by the loadable driver code, and&n;** for use by I/O bus infrastructure code.&n;*/
DECL|typedef|device_driver_t
r_typedef
r_struct
id|device_driver_s
op_star
id|device_driver_t
suffix:semicolon
multiline_comment|/* == Driver thread priority support == */
DECL|typedef|ilvl_t
r_typedef
r_int
id|ilvl_t
suffix:semicolon
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
DECL|typedef|iobush_t
r_typedef
id|__psunsigned_t
id|iobush_t
suffix:semicolon
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
macro_line|#endif /* _ASM_IA64_SN_DRIVER_H */
eof
