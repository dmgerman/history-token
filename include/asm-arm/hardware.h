multiline_comment|/*&n; *  linux/include/asm-arm/hardware.h&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Common hardware definitions&n; */
macro_line|#ifndef __ASM_HARDWARE_H
DECL|macro|__ASM_HARDWARE_H
mdefine_line|#define __ASM_HARDWARE_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_struct
id|platform_device
suffix:semicolon
r_extern
r_int
id|platform_add_devices
c_func
(paren
r_struct
id|platform_device
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|platform_add_device
c_func
(paren
r_struct
id|platform_device
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
