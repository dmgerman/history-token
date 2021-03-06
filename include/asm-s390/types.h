multiline_comment|/*&n; *  include/asm-s390/types.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/types.h&quot;&n; */
macro_line|#ifndef _S390_TYPES_H
DECL|macro|_S390_TYPES_H
mdefine_line|#define _S390_TYPES_H
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
macro_line|#ifndef __s390x__
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
macro_line|#else /* __s390x__ */
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
macro_line|#endif
multiline_comment|/* A address type so that arithmetic can be done on it &amp; it can be upgraded to&n;   64 bit when necessary &n;*/
DECL|typedef|addr_t
r_typedef
r_int
r_int
id|addr_t
suffix:semicolon
DECL|typedef|saddr_t
r_typedef
id|__signed__
r_int
id|saddr_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * These aren&squot;t exported outside the kernel to avoid name space clashes&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __s390x__
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 32
macro_line|#else
DECL|macro|BITS_PER_LONG
mdefine_line|#define BITS_PER_LONG 64
macro_line|#endif
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
macro_line|#ifndef __s390x__
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
macro_line|#else /* __s390x__ */
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
macro_line|#endif /* __s390x__ */
DECL|typedef|dma_addr_t
r_typedef
id|u32
id|dma_addr_t
suffix:semicolon
DECL|typedef|kmem_bufctl_t
r_typedef
r_int
r_int
id|kmem_bufctl_t
suffix:semicolon
macro_line|#ifndef __s390x__
r_typedef
r_union
(brace
DECL|member|pair
r_int
r_int
r_int
id|pair
suffix:semicolon
r_struct
(brace
DECL|member|even
r_int
r_int
id|even
suffix:semicolon
DECL|member|odd
r_int
r_int
id|odd
suffix:semicolon
DECL|member|subreg
)brace
id|subreg
suffix:semicolon
DECL|typedef|register_pair
)brace
id|register_pair
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
macro_line|#endif /* ! __s390x__   */
macro_line|#endif /* __ASSEMBLY__  */
macro_line|#endif /* __KERNEL__    */
macro_line|#endif /* _S390_TYPES_H */
eof
