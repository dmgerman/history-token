macro_line|#ifndef _NACA_H
DECL|macro|_NACA_H
mdefine_line|#define _NACA_H
multiline_comment|/* &n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|struct|naca_struct
r_struct
id|naca_struct
(brace
multiline_comment|/* Kernel only data - undefined for user space */
DECL|member|xItVpdAreas
r_void
op_star
id|xItVpdAreas
suffix:semicolon
multiline_comment|/* VPD Data                  0x00 */
DECL|member|xRamDisk
r_void
op_star
id|xRamDisk
suffix:semicolon
multiline_comment|/* iSeries ramdisk           0x08 */
DECL|member|xRamDiskSize
id|u64
id|xRamDiskSize
suffix:semicolon
multiline_comment|/* In pages                  0x10 */
)brace
suffix:semicolon
r_extern
r_struct
id|naca_struct
op_star
id|naca
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|NACA_PAGE
mdefine_line|#define NACA_PAGE      0x4
DECL|macro|NACA_PHYS_ADDR
mdefine_line|#define NACA_PHYS_ADDR (NACA_PAGE&lt;&lt;PAGE_SHIFT)
DECL|macro|NACA_VIRT_ADDR
mdefine_line|#define NACA_VIRT_ADDR (KERNELBASE+NACA_PHYS_ADDR)
macro_line|#endif /* _NACA_H */
eof
