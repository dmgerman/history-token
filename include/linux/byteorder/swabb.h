macro_line|#ifndef _LINUX_BYTEORDER_SWABB_H
DECL|macro|_LINUX_BYTEORDER_SWABB_H
mdefine_line|#define _LINUX_BYTEORDER_SWABB_H
multiline_comment|/*&n; * linux/byteorder/swabb.h&n; * SWAp Bytes Bizarrely&n; *&t;swaHHXX[ps]?(foo)&n; *&n; * Support for obNUXIous pdp-endian and other bizarre architectures.&n; * Will Linux ever run on such ancient beasts? if not, this file&n; * will be but a programming pearl. Still, it&squot;s a reminder that we&n; * shouldn&squot;t be making too many assumptions when trying to be portable.&n; *&n; */
multiline_comment|/*&n; * Meaning of the names I chose (vaxlinux people feel free to correct them):&n; * swahw32&t;swap 16-bit half-words in a 32-bit word&n; * swahb32&t;swap 8-bit halves of each 16-bit half-word in a 32-bit word&n; *&n; * No 64-bit support yet. I don&squot;t know NUXI conventions for long longs.&n; * I guarantee it will be a mess when it&squot;s there, though :-&gt;&n; * It will be even worse if there are conflicting 64-bit conventions.&n; * Hopefully, no one ever used 64-bit objects on NUXI machines.&n; *&n; */
DECL|macro|___swahw32
mdefine_line|#define ___swahw32(x) &bslash;&n;({ &bslash;&n;&t;__u32 __x = (x); &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0x0000ffffUL) &lt;&lt; 16) | &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0xffff0000UL) &gt;&gt; 16) )); &bslash;&n;})
DECL|macro|___swahb32
mdefine_line|#define ___swahb32(x) &bslash;&n;({ &bslash;&n;&t;__u32 __x = (x); &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0x00ff00ffUL) &lt;&lt; 8) | &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0xff00ff00UL) &gt;&gt; 8) )); &bslash;&n;})
DECL|macro|___constant_swahw32
mdefine_line|#define ___constant_swahw32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x0000ffffUL) &lt;&lt; 16) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xffff0000UL) &gt;&gt; 16) ))
DECL|macro|___constant_swahb32
mdefine_line|#define ___constant_swahb32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x00ff00ffUL) &lt;&lt; 8) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xff00ff00UL) &gt;&gt; 8) ))
multiline_comment|/*&n; * provide defaults when no architecture-specific optimization is detected&n; */
macro_line|#ifndef __arch__swahw32
DECL|macro|__arch__swahw32
macro_line|#  define __arch__swahw32(x) ___swahw32(x)
macro_line|#endif
macro_line|#ifndef __arch__swahb32
DECL|macro|__arch__swahb32
macro_line|#  define __arch__swahb32(x) ___swahb32(x)
macro_line|#endif
macro_line|#ifndef __arch__swahw32p
DECL|macro|__arch__swahw32p
macro_line|#  define __arch__swahw32p(x) __swahw32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swahb32p
DECL|macro|__arch__swahb32p
macro_line|#  define __arch__swahb32p(x) __swahb32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swahw32s
DECL|macro|__arch__swahw32s
macro_line|#  define __arch__swahw32s(x) do { *(x) = __swahw32p((x)); } while (0)
macro_line|#endif
macro_line|#ifndef __arch__swahb32s
DECL|macro|__arch__swahb32s
macro_line|#  define __arch__swahb32s(x) do { *(x) = __swahb32p((x)); } while (0)
macro_line|#endif
multiline_comment|/*&n; * Allow constant folding&n; */
macro_line|#if defined(__GNUC__) &amp;&amp; (__GNUC__ &gt;= 2) &amp;&amp; defined(__OPTIMIZE__)
DECL|macro|__swahw32
macro_line|#  define __swahw32(x) &bslash;&n;(__builtin_constant_p((__u32)(x)) ? &bslash;&n; ___swahw32((x)) : &bslash;&n; __fswahw32((x)))
DECL|macro|__swahb32
macro_line|#  define __swahb32(x) &bslash;&n;(__builtin_constant_p((__u32)(x)) ? &bslash;&n; ___swahb32((x)) : &bslash;&n; __fswahb32((x)))
macro_line|#else
DECL|macro|__swahw32
macro_line|#  define __swahw32(x) __fswahw32(x)
DECL|macro|__swahb32
macro_line|#  define __swahb32(x) __fswahb32(x)
macro_line|#endif /* OPTIMIZE */
DECL|function|__fswahw32
r_extern
id|__inline__
id|__const__
id|__u32
id|__fswahw32
c_func
(paren
id|__u32
id|x
)paren
(brace
r_return
id|__arch__swahw32
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swahw32p
r_extern
id|__inline__
id|__u32
id|__swahw32p
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
r_return
id|__arch__swahw32p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swahw32s
r_extern
id|__inline__
r_void
id|__swahw32s
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
id|__arch__swahw32s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__fswahb32
r_extern
id|__inline__
id|__const__
id|__u32
id|__fswahb32
c_func
(paren
id|__u32
id|x
)paren
(brace
r_return
id|__arch__swahb32
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swahb32p
r_extern
id|__inline__
id|__u32
id|__swahb32p
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
r_return
id|__arch__swahb32p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swahb32s
r_extern
id|__inline__
r_void
id|__swahb32s
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
id|__arch__swahb32s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef __BYTEORDER_HAS_U64__
multiline_comment|/*&n; * Not supported yet&n; */
macro_line|#endif /* __BYTEORDER_HAS_U64__ */
macro_line|#if defined(__KERNEL__)
DECL|macro|swahw32
mdefine_line|#define swahw32 __swahw32
DECL|macro|swahb32
mdefine_line|#define swahb32 __swahb32
DECL|macro|swahw32p
mdefine_line|#define swahw32p __swahw32p
DECL|macro|swahb32p
mdefine_line|#define swahb32p __swahb32p
DECL|macro|swahw32s
mdefine_line|#define swahw32s __swahw32s
DECL|macro|swahb32s
mdefine_line|#define swahb32s __swahb32s
macro_line|#endif
macro_line|#endif /* _LINUX_BYTEORDER_SWABB_H */
eof
