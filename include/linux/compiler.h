macro_line|#ifndef __LINUX_COMPILER_H
DECL|macro|__LINUX_COMPILER_H
mdefine_line|#define __LINUX_COMPILER_H
macro_line|#ifdef __CHECKER__
DECL|macro|__user
mdefine_line|#define __user&t;__attribute__((noderef, address_space(1)))
DECL|macro|__kernel
mdefine_line|#define __kernel&t;/* default address space */
macro_line|#else
DECL|macro|__user
mdefine_line|#define __user
DECL|macro|__kernel
mdefine_line|#define __kernel
macro_line|#endif
macro_line|#if (__GNUC__ &gt; 3) || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 1)
DECL|macro|inline
mdefine_line|#define inline&t;&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline__
mdefine_line|#define __inline__&t;__inline__ __attribute__((always_inline))
DECL|macro|__inline
mdefine_line|#define __inline&t;__inline__ __attribute__((always_inline))
macro_line|#endif
multiline_comment|/* Somewhere in the middle of the GCC 2.96 development cycle, we implemented&n;   a mechanism by which the user can annotate likely branch directions and&n;   expect the blocks to be reordered appropriately.  Define __builtin_expect&n;   to nothing for earlier compilers.  */
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(x, expected_value) (x)
macro_line|#endif
DECL|macro|likely
mdefine_line|#define likely(x)&t;__builtin_expect((x),1)
DECL|macro|unlikely
mdefine_line|#define unlikely(x)&t;__builtin_expect((x),0)
multiline_comment|/*&n; * Allow us to mark functions as &squot;deprecated&squot; and have gcc emit a nice&n; * warning for each use, in hopes of speeding the functions removal.&n; * Usage is:&n; * &t;&t;int __deprecated foo(void)&n; */
macro_line|#if ( __GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt; 0 ) || __GNUC__ &gt; 3
DECL|macro|__deprecated
mdefine_line|#define __deprecated&t;__attribute__((deprecated))
macro_line|#else
DECL|macro|__deprecated
mdefine_line|#define __deprecated
macro_line|#endif
multiline_comment|/*&n; * Allow us to avoid &squot;defined but not used&squot; warnings on functions and data,&n; * as well as force them to be emitted to the assembly file.&n; *&n; * As of gcc 3.3, static functions that are not marked with attribute((used))&n; * may be elided from the assembly file.  As of gcc 3.3, static data not so&n; * marked will not be elided, but this may change in a future gcc version.&n; *&n; * In prior versions of gcc, such functions and data would be emitted, but&n; * would be warned about except with attribute((unused)).&n; */
macro_line|#if __GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 3 || __GNUC__ &gt; 3
DECL|macro|__attribute_used__
mdefine_line|#define __attribute_used__&t;__attribute__((__used__))
macro_line|#else
DECL|macro|__attribute_used__
mdefine_line|#define __attribute_used__&t;__attribute__((__unused__))
macro_line|#endif
multiline_comment|/*&n; * From the GCC manual:&n; *&n; * Many functions have no effects except the return value and their&n; * return value depends only on the parameters and/or global&n; * variables.  Such a function can be subject to common subexpression&n; * elimination and loop optimization just as an arithmetic operator&n; * would be.&n; * [...]&n; * The attribute `pure&squot; is not implemented in GCC versions earlier&n; * than 2.96.&n; */
macro_line|#if (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR &gt;= 96) || __GNUC__ &gt; 2
DECL|macro|__attribute_pure__
mdefine_line|#define __attribute_pure__&t;__attribute__((pure))
macro_line|#else
DECL|macro|__attribute_pure__
mdefine_line|#define __attribute_pure__&t;/* unimplemented */
macro_line|#endif
multiline_comment|/* This macro obfuscates arithmetic on a variable address so that gcc&n;   shouldn&squot;t recognize the original var, and make assumptions about it */
DECL|macro|RELOC_HIDE
mdefine_line|#define RELOC_HIDE(ptr, off)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __ptr;&t;&t;&t;&t;&t;&bslash;&n;    __asm__ (&quot;&quot; : &quot;=g&quot;(__ptr) : &quot;0&quot;(ptr));&t;&t;&bslash;&n;    (typeof(ptr)) (__ptr + (off)); })
macro_line|#endif /* __LINUX_COMPILER_H */
eof
