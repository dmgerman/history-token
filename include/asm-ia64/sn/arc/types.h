multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1999,2001-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * Copyright 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SN_ARC_TYPES_H
DECL|macro|_ASM_SN_ARC_TYPES_H
mdefine_line|#define _ASM_SN_ARC_TYPES_H
DECL|typedef|CHAR
r_typedef
r_char
id|CHAR
suffix:semicolon
DECL|typedef|SHORT
r_typedef
r_int
id|SHORT
suffix:semicolon
DECL|typedef|LARGE_INTEGER
r_typedef
r_int
id|LARGE_INTEGER
id|__attribute__
(paren
(paren
id|__mode__
(paren
id|__DI__
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|LONG
r_typedef
r_int
id|LONG
id|__attribute__
(paren
(paren
id|__mode__
(paren
id|__DI__
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
DECL|typedef|USHORT
r_typedef
r_int
r_int
id|USHORT
suffix:semicolon
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
id|__attribute__
(paren
(paren
id|__mode__
(paren
id|__DI__
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|VOID
r_typedef
r_void
id|VOID
suffix:semicolon
multiline_comment|/* The pointer types.  We&squot;re 64-bit and the firmware is also 64-bit, so&n;   live is sane ...  */
DECL|typedef|_PCHAR
r_typedef
id|CHAR
op_star
id|_PCHAR
suffix:semicolon
DECL|typedef|_PSHORT
r_typedef
id|SHORT
op_star
id|_PSHORT
suffix:semicolon
DECL|typedef|_PLARGE_INTEGER
r_typedef
id|LARGE_INTEGER
op_star
id|_PLARGE_INTEGER
suffix:semicolon
DECL|typedef|_PLONG
r_typedef
id|LONG
op_star
id|_PLONG
suffix:semicolon
DECL|typedef|_PUCHAR
r_typedef
id|UCHAR
op_star
id|_PUCHAR
suffix:semicolon
DECL|typedef|_PUSHORT
r_typedef
id|USHORT
op_star
id|_PUSHORT
suffix:semicolon
DECL|typedef|_PULONG
r_typedef
id|ULONG
op_star
id|_PULONG
suffix:semicolon
DECL|typedef|_PVOID
r_typedef
id|VOID
op_star
id|_PVOID
suffix:semicolon
DECL|typedef|PCHAR
r_typedef
id|CHAR
op_star
id|PCHAR
suffix:semicolon
DECL|typedef|PSHORT
r_typedef
id|SHORT
op_star
id|PSHORT
suffix:semicolon
DECL|typedef|PLARGE_INTEGER
r_typedef
id|LARGE_INTEGER
op_star
id|PLARGE_INTEGER
suffix:semicolon
DECL|typedef|PLONG
r_typedef
id|LONG
op_star
id|PLONG
suffix:semicolon
DECL|typedef|PUCHAR
r_typedef
id|UCHAR
op_star
id|PUCHAR
suffix:semicolon
DECL|typedef|PUSHORT
r_typedef
id|USHORT
op_star
id|PUSHORT
suffix:semicolon
DECL|typedef|PULONG
r_typedef
id|ULONG
op_star
id|PULONG
suffix:semicolon
DECL|typedef|PVOID
r_typedef
id|VOID
op_star
id|PVOID
suffix:semicolon
macro_line|#endif /* _ASM_SN_ARC_TYPES_H */
eof
