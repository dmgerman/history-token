macro_line|#ifndef _LINUX_BYTEORDER_SWAB_H
DECL|macro|_LINUX_BYTEORDER_SWAB_H
mdefine_line|#define _LINUX_BYTEORDER_SWAB_H
multiline_comment|/*&n; * linux/byteorder/swab.h&n; * Byte-swapping, independently from CPU endianness&n; *&t;swabXX[ps]?(foo)&n; *&n; * Francois-Rene Rideau &lt;fare@tunes.org&gt; 19971205&n; *    separated swab functions from cpu_to_XX,&n; *    to clean up support for bizarre-endian architectures.&n; *&n; * See asm-i386/byteorder.h and suches for examples of how to provide&n; * architecture-dependent optimized versions&n; *&n; */
multiline_comment|/* casts are necessary for constants, because we never know how for sure&n; * how U/UL/ULL map to __u16, __u32, __u64. At least not in a portable way.&n; */
DECL|macro|___swab16
mdefine_line|#define ___swab16(x) &bslash;&n;({ &bslash;&n;&t;__u16 __x = (x); &bslash;&n;&t;((__u16)( &bslash;&n;&t;&t;(((__u16)(__x) &amp; (__u16)0x00ffU) &lt;&lt; 8) | &bslash;&n;&t;&t;(((__u16)(__x) &amp; (__u16)0xff00U) &gt;&gt; 8) )); &bslash;&n;})
DECL|macro|___swab32
mdefine_line|#define ___swab32(x) &bslash;&n;({ &bslash;&n;&t;__u32 __x = (x); &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0x000000ffUL) &lt;&lt; 24) | &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;&t;&t;(((__u32)(__x) &amp; (__u32)0xff000000UL) &gt;&gt; 24) )); &bslash;&n;})
DECL|macro|___swab64
mdefine_line|#define ___swab64(x) &bslash;&n;({ &bslash;&n;&t;__u64 __x = (x); &bslash;&n;&t;((__u64)( &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x00000000000000ffULL) &lt;&lt; 56) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x000000000000ff00ULL) &lt;&lt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x0000000000ff0000ULL) &lt;&lt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x00000000ff000000ULL) &lt;&lt;  8) | &bslash;&n;&t;        (__u64)(((__u64)(__x) &amp; (__u64)0x000000ff00000000ULL) &gt;&gt;  8) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x0000ff0000000000ULL) &gt;&gt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0x00ff000000000000ULL) &gt;&gt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(__x) &amp; (__u64)0xff00000000000000ULL) &gt;&gt; 56) )); &bslash;&n;})
DECL|macro|___constant_swab16
mdefine_line|#define ___constant_swab16(x) &bslash;&n;&t;((__u16)( &bslash;&n;&t;&t;(((__u16)(x) &amp; (__u16)0x00ffU) &lt;&lt; 8) | &bslash;&n;&t;&t;(((__u16)(x) &amp; (__u16)0xff00U) &gt;&gt; 8) ))
DECL|macro|___constant_swab32
mdefine_line|#define ___constant_swab32(x) &bslash;&n;&t;((__u32)( &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x000000ffUL) &lt;&lt; 24) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;&t;&t;(((__u32)(x) &amp; (__u32)0xff000000UL) &gt;&gt; 24) ))
DECL|macro|___constant_swab64
mdefine_line|#define ___constant_swab64(x) &bslash;&n;&t;((__u64)( &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00000000000000ffULL) &lt;&lt; 56) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x000000000000ff00ULL) &lt;&lt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x0000000000ff0000ULL) &lt;&lt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00000000ff000000ULL) &lt;&lt;  8) | &bslash;&n;&t;        (__u64)(((__u64)(x) &amp; (__u64)0x000000ff00000000ULL) &gt;&gt;  8) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x0000ff0000000000ULL) &gt;&gt; 24) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0x00ff000000000000ULL) &gt;&gt; 40) | &bslash;&n;&t;&t;(__u64)(((__u64)(x) &amp; (__u64)0xff00000000000000ULL) &gt;&gt; 56) ))
multiline_comment|/*&n; * provide defaults when no architecture-specific optimization is detected&n; */
macro_line|#ifndef __arch__swab16
DECL|macro|__arch__swab16
macro_line|#  define __arch__swab16(x) ({ __u16 __tmp = (x) ; ___swab16(__tmp); })
macro_line|#endif
macro_line|#ifndef __arch__swab32
DECL|macro|__arch__swab32
macro_line|#  define __arch__swab32(x) ({ __u32 __tmp = (x) ; ___swab32(__tmp); })
macro_line|#endif
macro_line|#ifndef __arch__swab64
DECL|macro|__arch__swab64
macro_line|#  define __arch__swab64(x) ({ __u64 __tmp = (x) ; ___swab64(__tmp); })
macro_line|#endif
macro_line|#ifndef __arch__swab16p
DECL|macro|__arch__swab16p
macro_line|#  define __arch__swab16p(x) __arch__swab16(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab32p
DECL|macro|__arch__swab32p
macro_line|#  define __arch__swab32p(x) __arch__swab32(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab64p
DECL|macro|__arch__swab64p
macro_line|#  define __arch__swab64p(x) __arch__swab64(*(x))
macro_line|#endif
macro_line|#ifndef __arch__swab16s
DECL|macro|__arch__swab16s
macro_line|#  define __arch__swab16s(x) do { *(x) = __arch__swab16p((x)); } while (0)
macro_line|#endif
macro_line|#ifndef __arch__swab32s
DECL|macro|__arch__swab32s
macro_line|#  define __arch__swab32s(x) do { *(x) = __arch__swab32p((x)); } while (0)
macro_line|#endif
macro_line|#ifndef __arch__swab64s
DECL|macro|__arch__swab64s
macro_line|#  define __arch__swab64s(x) do { *(x) = __arch__swab64p((x)); } while (0)
macro_line|#endif
multiline_comment|/*&n; * Allow constant folding&n; */
macro_line|#if defined(__GNUC__) &amp;&amp; (__GNUC__ &gt;= 2) &amp;&amp; defined(__OPTIMIZE__)
DECL|macro|__swab16
macro_line|#  define __swab16(x) &bslash;&n;(__builtin_constant_p((__u16)(x)) ? &bslash;&n; ___swab16((x)) : &bslash;&n; __fswab16((x)))
DECL|macro|__swab32
macro_line|#  define __swab32(x) &bslash;&n;(__builtin_constant_p((__u32)(x)) ? &bslash;&n; ___swab32((x)) : &bslash;&n; __fswab32((x)))
DECL|macro|__swab64
macro_line|#  define __swab64(x) &bslash;&n;(__builtin_constant_p((__u64)(x)) ? &bslash;&n; ___swab64((x)) : &bslash;&n; __fswab64((x)))
macro_line|#else
DECL|macro|__swab16
macro_line|#  define __swab16(x) __fswab16(x)
DECL|macro|__swab32
macro_line|#  define __swab32(x) __fswab32(x)
DECL|macro|__swab64
macro_line|#  define __swab64(x) __fswab64(x)
macro_line|#endif /* OPTIMIZE */
DECL|function|__fswab16
r_static
id|__inline__
id|__const__
id|__u16
id|__fswab16
c_func
(paren
id|__u16
id|x
)paren
(brace
r_return
id|__arch__swab16
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab16p
r_static
id|__inline__
id|__u16
id|__swab16p
c_func
(paren
id|__u16
op_star
id|x
)paren
(brace
r_return
id|__arch__swab16p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab16s
r_static
id|__inline__
r_void
id|__swab16s
c_func
(paren
id|__u16
op_star
id|addr
)paren
(brace
id|__arch__swab16s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__fswab32
r_static
id|__inline__
id|__const__
id|__u32
id|__fswab32
c_func
(paren
id|__u32
id|x
)paren
(brace
r_return
id|__arch__swab32
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab32p
r_static
id|__inline__
id|__u32
id|__swab32p
c_func
(paren
id|__u32
op_star
id|x
)paren
(brace
r_return
id|__arch__swab32p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab32s
r_static
id|__inline__
r_void
id|__swab32s
c_func
(paren
id|__u32
op_star
id|addr
)paren
(brace
id|__arch__swab32s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#ifdef __BYTEORDER_HAS_U64__
DECL|function|__fswab64
r_static
id|__inline__
id|__const__
id|__u64
id|__fswab64
c_func
(paren
id|__u64
id|x
)paren
(brace
macro_line|#  ifdef __SWAB_64_THRU_32__
id|__u32
id|h
op_assign
id|x
op_rshift
l_int|32
suffix:semicolon
id|__u32
id|l
op_assign
id|x
op_amp
(paren
(paren
l_int|1ULL
op_lshift
l_int|32
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
id|__u64
)paren
id|__swab32
c_func
(paren
id|l
)paren
)paren
op_lshift
l_int|32
)paren
op_or
(paren
(paren
id|__u64
)paren
(paren
id|__swab32
c_func
(paren
id|h
)paren
)paren
)paren
suffix:semicolon
macro_line|#  else
r_return
id|__arch__swab64
c_func
(paren
id|x
)paren
suffix:semicolon
macro_line|#  endif
)brace
DECL|function|__swab64p
r_static
id|__inline__
id|__u64
id|__swab64p
c_func
(paren
id|__u64
op_star
id|x
)paren
(brace
r_return
id|__arch__swab64p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|__swab64s
r_static
id|__inline__
r_void
id|__swab64s
c_func
(paren
id|__u64
op_star
id|addr
)paren
(brace
id|__arch__swab64s
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif /* __BYTEORDER_HAS_U64__ */
macro_line|#if defined(__KERNEL__)
DECL|macro|swab16
mdefine_line|#define swab16 __swab16
DECL|macro|swab32
mdefine_line|#define swab32 __swab32
DECL|macro|swab64
mdefine_line|#define swab64 __swab64
DECL|macro|swab16p
mdefine_line|#define swab16p __swab16p
DECL|macro|swab32p
mdefine_line|#define swab32p __swab32p
DECL|macro|swab64p
mdefine_line|#define swab64p __swab64p
DECL|macro|swab16s
mdefine_line|#define swab16s __swab16s
DECL|macro|swab32s
mdefine_line|#define swab32s __swab32s
DECL|macro|swab64s
mdefine_line|#define swab64s __swab64s
macro_line|#endif
macro_line|#endif /* _LINUX_BYTEORDER_SWAB_H */
eof
