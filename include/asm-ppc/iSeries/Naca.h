multiline_comment|/*&n; * Naca.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef&t;_PPC_TYPES_H
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _NACA_H
DECL|macro|_NACA_H
mdefine_line|#define _NACA_H
DECL|struct|Naca
r_struct
id|Naca
(brace
DECL|member|xItVpdAreas64
id|u32
id|xItVpdAreas64
suffix:semicolon
singleline_comment|// Address of ItVpdAreas&t;
DECL|member|xItVpdAreas
r_void
op_star
id|xItVpdAreas
suffix:semicolon
DECL|member|xRamDisk64
id|u32
id|xRamDisk64
suffix:semicolon
singleline_comment|// Address of initial Ramdisk
DECL|member|xRamDisk
id|u32
id|xRamDisk
suffix:semicolon
DECL|member|xRamDiskSize64
id|u32
id|xRamDiskSize64
suffix:semicolon
singleline_comment|// Size of initial Ramdisk
DECL|member|xRamDiskSize
id|u32
id|xRamDiskSize
suffix:semicolon
singleline_comment|// in pages
)brace
suffix:semicolon
macro_line|#endif /* _NACA_H */
eof
