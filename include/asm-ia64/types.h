macro_line|#ifndef _ASM_IA64_TYPES_H
DECL|macro|_ASM_IA64_TYPES_H
mdefine_line|#define _ASM_IA64_TYPES_H
multiline_comment|/*&n; * This file is never included by application software unless&n; * explicitly requested (e.g., via linux/types.h) in which case the&n; * application is Linux specific so (user-) name space pollution is&n; * not a major issue.  However, for interoperability, libraries still&n; * need to be careful to avoid a name clashes.&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__IA64_UL
macro_line|# define __IA64_UL(x)&t;&t;(x)
DECL|macro|__IA64_UL_CONST
macro_line|# define __IA64_UL_CONST(x)&t;x
macro_line|#else
DECL|macro|__IA64_UL
macro_line|# define __IA64_UL(x)&t;&t;((unsigned long)(x))
DECL|macro|__IA64_UL_CONST
macro_line|# define __IA64_UL_CONST(x)&t;x##UL
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
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
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
macro_line|# ifdef __KERNEL__
DECL|typedef|s8
r_typedef
id|__s8
id|s8
suffix:semicolon
DECL|typedef|u8
r_typedef
id|__u8
id|u8
suffix:semicolon
DECL|typedef|s16
r_typedef
id|__s16
id|s16
suffix:semicolon
DECL|typedef|u16
r_typedef
id|__u16
id|u16
suffix:semicolon
DECL|typedef|s32
r_typedef
id|__s32
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
id|__u32
id|u32
suffix:semicolon
DECL|typedef|s64
r_typedef
id|__s64
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
id|__u64
id|u64
suffix:semicolon
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 64
multiline_comment|/* DMA addresses are 64-bits wide, in general.  */
DECL|typedef|dma_addr_t
r_typedef
id|u64
id|dma_addr_t
suffix:semicolon
macro_line|# endif /* __KERNEL__ */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_TYPES_H */
eof
