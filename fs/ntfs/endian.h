multiline_comment|/*&n; * endian.h - Defines for endianness handling in NTFS Linux kernel driver.&n; *&t;      Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_ENDIAN_H
DECL|macro|_LINUX_NTFS_ENDIAN_H
mdefine_line|#define _LINUX_NTFS_ENDIAN_H
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * Signed endianness conversion defines.&n; */
DECL|macro|sle16_to_cpu
mdefine_line|#define sle16_to_cpu(x)&t;&t;((s16)__le16_to_cpu((s16)(x)))
DECL|macro|sle32_to_cpu
mdefine_line|#define sle32_to_cpu(x)&t;&t;((s32)__le32_to_cpu((s32)(x)))
DECL|macro|sle64_to_cpu
mdefine_line|#define sle64_to_cpu(x)&t;&t;((s64)__le64_to_cpu((s64)(x)))
DECL|macro|sle16_to_cpup
mdefine_line|#define sle16_to_cpup(x)&t;((s16)__le16_to_cpu(*(s16*)(x)))
DECL|macro|sle32_to_cpup
mdefine_line|#define sle32_to_cpup(x)&t;((s32)__le32_to_cpu(*(s32*)(x)))
DECL|macro|sle64_to_cpup
mdefine_line|#define sle64_to_cpup(x)&t;((s64)__le64_to_cpu(*(s64*)(x)))
DECL|macro|cpu_to_sle16
mdefine_line|#define cpu_to_sle16(x)&t;&t;((s16)__cpu_to_le16((s16)(x)))
DECL|macro|cpu_to_sle32
mdefine_line|#define cpu_to_sle32(x)&t;&t;((s32)__cpu_to_le32((s32)(x)))
DECL|macro|cpu_to_sle64
mdefine_line|#define cpu_to_sle64(x)&t;&t;((s64)__cpu_to_le64((s64)(x)))
DECL|macro|cpu_to_sle16p
mdefine_line|#define cpu_to_sle16p(x)&t;((s16)__cpu_to_le16(*(s16*)(x)))
DECL|macro|cpu_to_sle32p
mdefine_line|#define cpu_to_sle32p(x)&t;((s32)__cpu_to_le32(*(s32*)(x)))
DECL|macro|cpu_to_sle64p
mdefine_line|#define cpu_to_sle64p(x)&t;((s64)__cpu_to_le64(*(s64*)(x)))
macro_line|#endif /* _LINUX_NTFS_ENDIAN_H */
eof
