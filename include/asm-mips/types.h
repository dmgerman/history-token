multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_TYPES_H
DECL|macro|_ASM_TYPES_H
mdefine_line|#define _ASM_TYPES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_MIPS32
DECL|typedef|umode_t
r_typedef
r_int
r_int
id|umode_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|typedef|umode_t
r_typedef
r_int
r_int
id|umode_t
suffix:semicolon
macro_line|#endif
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
macro_line|#if (_MIPS_SZLONG == 64)
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
macro_line|#else
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
DECL|typedef|__s64
r_typedef
id|__signed__
r_int
r_int
id|__s64
suffix:semicolon
DECL|typedef|__u64
r_typedef
r_int
r_int
r_int
id|__u64
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG _MIPS_SZLONG
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|s8
r_typedef
id|__signed
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
id|__signed
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
id|__signed
r_int
id|s32
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#if (_MIPS_SZLONG == 64)
DECL|typedef|s64
r_typedef
id|__signed__
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
id|u64
suffix:semicolon
macro_line|#else
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
DECL|typedef|s64
r_typedef
id|__signed__
r_int
r_int
id|s64
suffix:semicolon
DECL|typedef|u64
r_typedef
r_int
r_int
r_int
id|u64
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#if (defined(CONFIG_HIGHMEM) &amp;&amp; defined(CONFIG_64BIT_PHYS_ADDR)) &bslash;&n;    || defined(CONFIG_MIPS64)
DECL|typedef|dma_addr_t
r_typedef
id|u64
id|dma_addr_t
suffix:semicolon
macro_line|#else
DECL|typedef|dma_addr_t
r_typedef
id|u32
id|dma_addr_t
suffix:semicolon
macro_line|#endif
DECL|typedef|dma64_addr_t
r_typedef
id|u64
id|dma64_addr_t
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t use phys_t.  You&squot;ve been warned.&n; */
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
DECL|typedef|phys_t
r_typedef
r_int
r_int
r_int
id|phys_t
suffix:semicolon
macro_line|#else
DECL|typedef|phys_t
r_typedef
r_int
r_int
id|phys_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LBD
DECL|typedef|sector_t
r_typedef
id|u64
id|sector_t
suffix:semicolon
DECL|macro|HAVE_SECTOR_T
mdefine_line|#define HAVE_SECTOR_T
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_TYPES_H */
eof
