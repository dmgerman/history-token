macro_line|#ifndef __LINUX_COMPILER_H
DECL|macro|__LINUX_COMPILER_H
mdefine_line|#define __LINUX_COMPILER_H
macro_line|#ifdef __CHECKER__
DECL|macro|__user
macro_line|# define __user&t;&t;__attribute__((noderef, address_space(1)))
DECL|macro|__kernel
macro_line|# define __kernel&t;/* default address space */
macro_line|#else
DECL|macro|__user
macro_line|# define __user
DECL|macro|__kernel
macro_line|# define __kernel
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#if __GNUC__ &gt; 3
macro_line|# include &lt;linux/compiler-gcc+.h&gt;&t;/* catch-all for GCC 4, 5, etc. */
macro_line|#elif __GNUC__ == 3
macro_line|# include &lt;linux/compiler-gcc3.h&gt;
macro_line|#elif __GNUC__ == 2
macro_line|# include &lt;linux/compiler-gcc2.h&gt;
macro_line|#else
macro_line|# error Sorry, your compiler is too old/not recognized.
macro_line|#endif
macro_line|#endif
multiline_comment|/* Intel compiler defines __GNUC__. So we will overwrite implementations&n; * coming from above header files here&n; */
macro_line|#ifdef __INTEL_COMPILER
macro_line|# include &lt;linux/compiler-intel.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Generic compiler-dependent macros required for kernel&n; * build go below this comment. Actual compiler/compiler version&n; * specific implementations come from the above header files&n; */
DECL|macro|likely
mdefine_line|#define likely(x)&t;__builtin_expect(!!(x), 1)
DECL|macro|unlikely
mdefine_line|#define unlikely(x)&t;__builtin_expect(!!(x), 0)
multiline_comment|/*&n; * Allow us to mark functions as &squot;deprecated&squot; and have gcc emit a nice&n; * warning for each use, in hopes of speeding the functions removal.&n; * Usage is:&n; * &t;&t;int __deprecated foo(void)&n; */
macro_line|#ifndef __deprecated
DECL|macro|__deprecated
macro_line|# define __deprecated&t;&t;/* unimplemented */
macro_line|#endif
multiline_comment|/*&n; * Allow us to avoid &squot;defined but not used&squot; warnings on functions and data,&n; * as well as force them to be emitted to the assembly file.&n; *&n; * As of gcc 3.3, static functions that are not marked with attribute((used))&n; * may be elided from the assembly file.  As of gcc 3.3, static data not so&n; * marked will not be elided, but this may change in a future gcc version.&n; *&n; * In prior versions of gcc, such functions and data would be emitted, but&n; * would be warned about except with attribute((unused)).&n; */
macro_line|#ifndef __attribute_used__
DECL|macro|__attribute_used__
macro_line|# define __attribute_used__&t;/* unimplemented */
macro_line|#endif
multiline_comment|/*&n; * From the GCC manual:&n; *&n; * Many functions have no effects except the return value and their&n; * return value depends only on the parameters and/or global&n; * variables.  Such a function can be subject to common subexpression&n; * elimination and loop optimization just as an arithmetic operator&n; * would be.&n; * [...]&n; */
macro_line|#ifndef __attribute_pure__
DECL|macro|__attribute_pure__
macro_line|# define __attribute_pure__&t;/* unimplemented */
macro_line|#endif
multiline_comment|/* Optimization barrier */
macro_line|#ifndef barrier
DECL|macro|barrier
macro_line|# define barrier() __memory_barrier()
macro_line|#endif
macro_line|#ifndef RELOC_HIDE
DECL|macro|RELOC_HIDE
macro_line|# define RELOC_HIDE(ptr, off)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __ptr;&t;&t;&t;&t;&t;&bslash;&n;     __ptr = (unsigned long) (ptr);&t;&t;&t;&t;&bslash;&n;    (typeof(ptr)) (__ptr + (off)); })
macro_line|#endif
macro_line|#endif /* __LINUX_COMPILER_H */
eof
