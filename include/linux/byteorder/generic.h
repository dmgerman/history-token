macro_line|#ifndef _LINUX_BYTEORDER_GENERIC_H
DECL|macro|_LINUX_BYTEORDER_GENERIC_H
mdefine_line|#define _LINUX_BYTEORDER_GENERIC_H
multiline_comment|/*&n; * linux/byteorder_generic.h&n; * Generic Byte-reordering support&n; *&n; * Francois-Rene Rideau &lt;fare@tunes.org&gt; 19970707&n; *    gathered all the good ideas from all asm-foo/byteorder.h into one file,&n; *    cleaned them up.&n; *    I hope it is compliant with non-GCC compilers.&n; *    I decided to put __BYTEORDER_HAS_U64__ in byteorder.h,&n; *    because I wasn&squot;t sure it would be ok to put it in types.h&n; *    Upgraded it to 2.1.43&n; * Francois-Rene Rideau &lt;fare@tunes.org&gt; 19971012&n; *    Upgraded it to 2.1.57&n; *    to please Linus T., replaced huge #ifdef&squot;s between little/big endian&n; *    by nestedly #include&squot;d files.&n; * Francois-Rene Rideau &lt;fare@tunes.org&gt; 19971205&n; *    Made it to 2.1.71; now a facelift:&n; *    Put files under include/linux/byteorder/&n; *    Split swab from generic support.&n; *&n; * TODO:&n; *   = Regular kernel maintainers could also replace all these manual&n; *    byteswap macros that remain, disseminated among drivers,&n; *    after some grep or the sources...&n; *   = Linus might want to rename all these macros and files to fit his taste,&n; *    to fit his personal naming scheme.&n; *   = it seems that a few drivers would also appreciate&n; *    nybble swapping support...&n; *   = every architecture could add their byteswap macro in asm/byteorder.h&n; *    see how some architectures already do (i386, alpha, ppc, etc)&n; *   = cpu_to_beXX and beXX_to_cpu might some day need to be well&n; *    distinguished throughout the kernel. This is not the case currently,&n; *    since little endian, big endian, and pdp endian machines needn&squot;t it.&n; *    But this might be the case for, say, a port of Linux to 20/21 bit&n; *    architectures (and F21 Linux addict around?).&n; */
multiline_comment|/*&n; * The following macros are to be defined by &lt;asm/byteorder.h&gt;:&n; *&n; * Conversion of long and short int between network and host format&n; *&t;ntohl(__u32 x)&n; *&t;ntohs(__u16 x)&n; *&t;htonl(__u32 x)&n; *&t;htons(__u16 x)&n; * It seems that some programs (which? where? or perhaps a standard? POSIX?)&n; * might like the above to be functions, not macros (why?).&n; * if that&squot;s true, then detect them, and take measures.&n; * Anyway, the measure is: define only ___ntohl as a macro instead,&n; * and in a separate file, have&n; * unsigned long inline ntohl(x){return ___ntohl(x);}&n; *&n; * The same for constant arguments&n; *&t;__constant_ntohl(__u32 x)&n; *&t;__constant_ntohs(__u16 x)&n; *&t;__constant_htonl(__u32 x)&n; *&t;__constant_htons(__u16 x)&n; *&n; * Conversion of XX-bit integers (16- 32- or 64-)&n; * between native CPU format and little/big endian format&n; * 64-bit stuff only defined for proper architectures&n; *&t;cpu_to_[bl]eXX(__uXX x)&n; *&t;[bl]eXX_to_cpu(__uXX x)&n; *&n; * The same, but takes a pointer to the value to convert&n; *&t;cpu_to_[bl]eXXp(__uXX x)&n; *&t;[bl]eXX_to_cpup(__uXX x)&n; *&n; * The same, but change in situ&n; *&t;cpu_to_[bl]eXXs(__uXX x)&n; *&t;[bl]eXX_to_cpus(__uXX x)&n; *&n; * See asm-foo/byteorder.h for examples of how to provide&n; * architecture-optimized versions&n; *&n; */
macro_line|#if defined(__KERNEL__)
multiline_comment|/*&n; * inside the kernel, we can use nicknames;&n; * outside of it, we must avoid POSIX namespace pollution...&n; */
DECL|macro|cpu_to_le64
mdefine_line|#define cpu_to_le64 __cpu_to_le64
DECL|macro|le64_to_cpu
mdefine_line|#define le64_to_cpu __le64_to_cpu
DECL|macro|cpu_to_le32
mdefine_line|#define cpu_to_le32 __cpu_to_le32
DECL|macro|le32_to_cpu
mdefine_line|#define le32_to_cpu __le32_to_cpu
DECL|macro|cpu_to_le16
mdefine_line|#define cpu_to_le16 __cpu_to_le16
DECL|macro|le16_to_cpu
mdefine_line|#define le16_to_cpu __le16_to_cpu
DECL|macro|cpu_to_be64
mdefine_line|#define cpu_to_be64 __cpu_to_be64
DECL|macro|be64_to_cpu
mdefine_line|#define be64_to_cpu __be64_to_cpu
DECL|macro|cpu_to_be32
mdefine_line|#define cpu_to_be32 __cpu_to_be32
DECL|macro|be32_to_cpu
mdefine_line|#define be32_to_cpu __be32_to_cpu
DECL|macro|cpu_to_be16
mdefine_line|#define cpu_to_be16 __cpu_to_be16
DECL|macro|be16_to_cpu
mdefine_line|#define be16_to_cpu __be16_to_cpu
DECL|macro|cpu_to_le64p
mdefine_line|#define cpu_to_le64p __cpu_to_le64p
DECL|macro|le64_to_cpup
mdefine_line|#define le64_to_cpup __le64_to_cpup
DECL|macro|cpu_to_le32p
mdefine_line|#define cpu_to_le32p __cpu_to_le32p
DECL|macro|le32_to_cpup
mdefine_line|#define le32_to_cpup __le32_to_cpup
DECL|macro|cpu_to_le16p
mdefine_line|#define cpu_to_le16p __cpu_to_le16p
DECL|macro|le16_to_cpup
mdefine_line|#define le16_to_cpup __le16_to_cpup
DECL|macro|cpu_to_be64p
mdefine_line|#define cpu_to_be64p __cpu_to_be64p
DECL|macro|be64_to_cpup
mdefine_line|#define be64_to_cpup __be64_to_cpup
DECL|macro|cpu_to_be32p
mdefine_line|#define cpu_to_be32p __cpu_to_be32p
DECL|macro|be32_to_cpup
mdefine_line|#define be32_to_cpup __be32_to_cpup
DECL|macro|cpu_to_be16p
mdefine_line|#define cpu_to_be16p __cpu_to_be16p
DECL|macro|be16_to_cpup
mdefine_line|#define be16_to_cpup __be16_to_cpup
DECL|macro|cpu_to_le64s
mdefine_line|#define cpu_to_le64s __cpu_to_le64s
DECL|macro|le64_to_cpus
mdefine_line|#define le64_to_cpus __le64_to_cpus
DECL|macro|cpu_to_le32s
mdefine_line|#define cpu_to_le32s __cpu_to_le32s
DECL|macro|le32_to_cpus
mdefine_line|#define le32_to_cpus __le32_to_cpus
DECL|macro|cpu_to_le16s
mdefine_line|#define cpu_to_le16s __cpu_to_le16s
DECL|macro|le16_to_cpus
mdefine_line|#define le16_to_cpus __le16_to_cpus
DECL|macro|cpu_to_be64s
mdefine_line|#define cpu_to_be64s __cpu_to_be64s
DECL|macro|be64_to_cpus
mdefine_line|#define be64_to_cpus __be64_to_cpus
DECL|macro|cpu_to_be32s
mdefine_line|#define cpu_to_be32s __cpu_to_be32s
DECL|macro|be32_to_cpus
mdefine_line|#define be32_to_cpus __be32_to_cpus
DECL|macro|cpu_to_be16s
mdefine_line|#define cpu_to_be16s __cpu_to_be16s
DECL|macro|be16_to_cpus
mdefine_line|#define be16_to_cpus __be16_to_cpus
macro_line|#endif
multiline_comment|/*&n; * Handle ntohl and suches. These have various compatibility&n; * issues - like we want to give the prototype even though we&n; * also have a macro for them in case some strange program&n; * wants to take the address of the thing or something..&n; *&n; * Note that these used to return a &quot;long&quot; in libc5, even though&n; * long is often 64-bit these days.. Thus the casts.&n; *&n; * They have to be macros in order to do the constant folding&n; * correctly - if the argument passed into a inline function&n; * it is no longer constant according to gcc..&n; */
DECL|macro|ntohl
macro_line|#undef ntohl
DECL|macro|ntohs
macro_line|#undef ntohs
DECL|macro|htonl
macro_line|#undef htonl
DECL|macro|htons
macro_line|#undef htons
multiline_comment|/*&n; * Do the prototypes. Somebody might want to take the&n; * address or some such sick thing..&n; */
macro_line|#if defined(__KERNEL__) || (defined (__GLIBC__) &amp;&amp; __GLIBC__ &gt;= 2)
r_extern
id|__u32
id|ntohl
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|htonl
c_func
(paren
id|__u32
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
r_int
r_int
id|ntohl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htonl
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
r_int
id|ntohs
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
r_int
id|htons
c_func
(paren
r_int
r_int
r_int
)paren
suffix:semicolon
macro_line|#if defined(__GNUC__) &amp;&amp; (__GNUC__ &gt;= 2) &amp;&amp; defined(__OPTIMIZE__)
DECL|macro|___htonl
mdefine_line|#define ___htonl(x) __cpu_to_be32(x)
DECL|macro|___htons
mdefine_line|#define ___htons(x) __cpu_to_be16(x)
DECL|macro|___ntohl
mdefine_line|#define ___ntohl(x) __be32_to_cpu(x)
DECL|macro|___ntohs
mdefine_line|#define ___ntohs(x) __be16_to_cpu(x)
macro_line|#if defined(__KERNEL__) || (defined (__GLIBC__) &amp;&amp; __GLIBC__ &gt;= 2)
DECL|macro|htonl
mdefine_line|#define htonl(x) ___htonl(x)
DECL|macro|ntohl
mdefine_line|#define ntohl(x) ___ntohl(x)
macro_line|#else
DECL|macro|htonl
mdefine_line|#define htonl(x) ((unsigned long)___htonl(x))
DECL|macro|ntohl
mdefine_line|#define ntohl(x) ((unsigned long)___ntohl(x))
macro_line|#endif
DECL|macro|htons
mdefine_line|#define htons(x) ___htons(x)
DECL|macro|ntohs
mdefine_line|#define ntohs(x) ___ntohs(x)
macro_line|#endif /* OPTIMIZE */
macro_line|#endif /* _LINUX_BYTEORDER_GENERIC_H */
eof
