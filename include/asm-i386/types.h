macro_line|#ifndef _I386_TYPES_H
DECL|macro|_I386_TYPES_H
mdefine_line|#define _I386_TYPES_H
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
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 32
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/* DMA addresses come in generic and 64-bit flavours.  */
macro_line|#ifdef CONFIG_HIGHMEM64G
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
macro_line|#ifdef CONFIG_LBD
DECL|typedef|sector_t
r_typedef
id|u64
id|sector_t
suffix:semicolon
DECL|macro|HAVE_SECTOR_T
mdefine_line|#define HAVE_SECTOR_T
macro_line|#endif
DECL|typedef|kmem_bufctl_t
r_typedef
r_int
r_int
id|kmem_bufctl_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
