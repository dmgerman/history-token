macro_line|#ifndef __M68K_UNALIGNED_H
DECL|macro|__M68K_UNALIGNED_H
mdefine_line|#define __M68K_UNALIGNED_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_COLDFIRE
multiline_comment|/* Use memmove here, so gcc does not insert a __builtin_memcpy. */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memmove(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memmove((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#else
multiline_comment|/*&n; * The m68k can do unaligned accesses itself. &n; *&n; * The strange macros are there to make sure these can&squot;t&n; * be misused in a way that makes them not work on other&n; * architectures where unaligned accesses aren&squot;t as simple.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) (*(ptr))
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr) ((void)( *(ptr) = (val) ))
macro_line|#endif
macro_line|#endif
eof
