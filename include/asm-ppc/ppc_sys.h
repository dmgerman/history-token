multiline_comment|/*&n; * include/asm-ppc/ppc_sys.h&n; *&n; * PPC system definitions and library functions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_SYS_H
DECL|macro|__ASM_PPC_SYS_H
mdefine_line|#define __ASM_PPC_SYS_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#if defined(CONFIG_83xx)
macro_line|#include &lt;asm/mpc83xx.h&gt;
macro_line|#elif defined(CONFIG_85xx)
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#else
macro_line|#error &quot;need definition of ppc_sys_devices&quot;
macro_line|#endif
DECL|struct|ppc_sys_spec
r_struct
id|ppc_sys_spec
(brace
multiline_comment|/* PPC sys is matched via (ID &amp; mask) == value, id could be&n;&t; * PVR, SVR, IMMR, * etc. */
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|value
id|u32
id|value
suffix:semicolon
DECL|member|num_devices
id|u32
id|num_devices
suffix:semicolon
DECL|member|ppc_sys_name
r_char
op_star
id|ppc_sys_name
suffix:semicolon
DECL|member|device_list
r_enum
id|ppc_sys_devices
op_star
id|device_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* describes all specific chips and which devices they have on them */
r_extern
r_struct
id|ppc_sys_spec
id|ppc_sys_specs
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|ppc_sys_spec
op_star
id|cur_ppc_sys_spec
suffix:semicolon
multiline_comment|/* determine which specific SOC we are */
r_extern
r_void
id|identify_ppc_sys_by_id
c_func
(paren
id|u32
id|id
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|identify_ppc_sys_by_name
c_func
(paren
r_char
op_star
id|name
)paren
id|__init
suffix:semicolon
multiline_comment|/* describes all devices that may exist in a given family of processors */
r_extern
r_struct
id|platform_device
id|ppc_sys_platform_devices
(braket
)braket
suffix:semicolon
multiline_comment|/* allow any platform_device fixup to occur before device is registered */
r_extern
r_int
(paren
op_star
id|ppc_sys_device_fixup
)paren
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* Update all memory resources by paddr, call before platform_device_register */
r_extern
r_void
id|ppc_sys_fixup_mem_resource
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
comma
id|phys_addr_t
id|paddr
)paren
id|__init
suffix:semicolon
multiline_comment|/* Get platform_data pointer out of platform device, call before platform_device_register */
r_extern
r_void
op_star
id|ppc_sys_get_pdata
c_func
(paren
r_enum
id|ppc_sys_devices
id|dev
)paren
id|__init
suffix:semicolon
multiline_comment|/* remove a device from the system */
r_extern
r_void
id|ppc_sys_device_remove
c_func
(paren
r_enum
id|ppc_sys_devices
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ASM_PPC_SYS_H */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
