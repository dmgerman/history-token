macro_line|#ifndef _PPC64_TYPES_H
DECL|macro|_PPC64_TYPES_H
mdefine_line|#define _PPC64_TYPES_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * This file is never included by application software unless&n; * explicitly requested (e.g., via linux/types.h) in which case the&n; * application is Linux specific so (user-) name space pollution is&n; * not a major issue.  However, for interoperability, libraries still&n; * need to be careful to avoid a name clashes.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|typedef|umode_t
r_typedef
r_int
r_int
id|umode_t
suffix:semicolon
multiline_comment|/*&n; * __xx is ok: it doesn&squot;t pollute the POSIX namespace. Use these in the&n; * header files exported to user space&n; */
DECL|typedef|__s8
r_typedef
id|__signed__
r_char
id|__s8
suffix:semicolon
DECL|typedef|__u8
r_typedef
r_int
r_char
id|__u8
suffix:semicolon
DECL|typedef|__s16
r_typedef
id|__signed__
r_int
id|__s16
suffix:semicolon
DECL|typedef|__u16
r_typedef
r_int
r_int
id|__u16
suffix:semicolon
DECL|typedef|__s32
r_typedef
id|__signed__
r_int
id|__s32
suffix:semicolon
DECL|typedef|__u32
r_typedef
r_int
r_int
id|__u32
suffix:semicolon
DECL|typedef|__s64
r_typedef
id|__signed__
r_int
id|__s64
suffix:semicolon
DECL|typedef|__u64
r_typedef
r_int
r_int
id|__u64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|u
id|__u32
id|u
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|__vector128
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
id|__vector128
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
DECL|typedef|s8
r_typedef
r_int
r_char
id|s8
suffix:semicolon
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|s16
r_typedef
r_int
r_int
id|s16
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|s32
r_typedef
r_int
r_int
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
DECL|typedef|s64
r_typedef
r_int
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
id|u64
suffix:semicolon
DECL|typedef|vector128
r_typedef
id|__vector128
id|vector128
suffix:semicolon
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 64
DECL|typedef|dma_addr_t
r_typedef
id|u32
id|dma_addr_t
suffix:semicolon
DECL|typedef|dma64_addr_t
r_typedef
id|u64
id|dma64_addr_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PPC64_TYPES_H */
eof
