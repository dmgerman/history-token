macro_line|#ifndef __LINUX_COMPILER_H
DECL|macro|__LINUX_COMPILER_H
mdefine_line|#define __LINUX_COMPILER_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef __CHECKER__
DECL|macro|__user
macro_line|# define __user&t;&t;__attribute__((noderef, address_space(1)))
DECL|macro|__kernel
macro_line|# define __kernel&t;/* default address space */
DECL|macro|__safe
macro_line|# define __safe&t;&t;__attribute__((safe))
DECL|macro|__force
macro_line|# define __force&t;__attribute__((force))
DECL|macro|__iomem
macro_line|# define __iomem&t;__attribute__((noderef, address_space(2)))
DECL|macro|__acquires
macro_line|# define __acquires(x)&t;__attribute__((context(0,1)))
DECL|macro|__releases
macro_line|# define __releases(x)&t;__attribute__((context(1,0)))
DECL|macro|__acquire
macro_line|# define __acquire(x)&t;__context__(1)
DECL|macro|__release
macro_line|# define __release(x)&t;__context__(-1)
DECL|macro|__cond_lock
macro_line|# define __cond_lock(x)&t;((x) ? ({ __context__(1); 1; }) : 0)
r_extern
r_void
id|__chk_user_ptr
c_func
(paren
r_void
id|__user
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__chk_io_ptr
c_func
(paren
r_void
id|__iomem
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|__user
macro_line|# define __user
DECL|macro|__kernel
macro_line|# define __kernel
DECL|macro|__safe
macro_line|# define __safe
DECL|macro|__force
macro_line|# define __force
DECL|macro|__iomem
macro_line|# define __iomem
DECL|macro|__chk_user_ptr
macro_line|# define __chk_user_ptr(x) (void)0
DECL|macro|__chk_io_ptr
macro_line|# define __chk_io_ptr(x) (void)0
DECL|macro|__builtin_warning
macro_line|# define __builtin_warning(x, y...) (1)
DECL|macro|__acquires
macro_line|# define __acquires(x)
DECL|macro|__releases
macro_line|# define __releases(x)
DECL|macro|__acquire
macro_line|# define __acquire(x) (void)0
DECL|macro|__release
macro_line|# define __release(x) (void)0
DECL|macro|__cond_lock
macro_line|# define __cond_lock(x) (x)
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#if __GNUC__ &gt; 3
macro_line|# include &lt;linux/compiler-gcc+.h&gt;&t;/* catch-all for GCC 4, 5, etc. */
macro_line|#elif __GNUC__ == 3
macro_line|# include &lt;linux/compiler-gcc3.h&gt;
macro_line|#elif __GNUC__ == 2
macro_line|# include &lt;linux/compiler-gcc2.h&gt;
macro_line|#else
macro_line|# error Sorry, your compiler is too old/not recognized.
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
multiline_comment|/* Optimization barrier */
macro_line|#ifndef barrier
DECL|macro|barrier
macro_line|# define barrier() __memory_barrier()
macro_line|#endif
macro_line|#ifndef RELOC_HIDE
DECL|macro|RELOC_HIDE
macro_line|# define RELOC_HIDE(ptr, off)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __ptr;&t;&t;&t;&t;&t;&bslash;&n;     __ptr = (unsigned long) (ptr);&t;&t;&t;&t;&bslash;&n;    (typeof(ptr)) (__ptr + (off)); })
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Allow us to mark functions as &squot;deprecated&squot; and have gcc emit a nice&n; * warning for each use, in hopes of speeding the functions removal.&n; * Usage is:&n; * &t;&t;int __deprecated foo(void)&n; */
macro_line|#ifndef __deprecated
DECL|macro|__deprecated
macro_line|# define __deprecated&t;&t;/* unimplemented */
macro_line|#endif
macro_line|#ifndef __must_check
DECL|macro|__must_check
mdefine_line|#define __must_check
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
multiline_comment|/*&n; * From the GCC manual:&n; *&n; * Many functions do not examine any values except their arguments,&n; * and have no effects except the return value.  Basically this is&n; * just slightly more strict class than the `pure&squot; attribute above,&n; * since function is not allowed to read global memory.&n; *&n; * Note that a function that has pointer arguments and examines the&n; * data pointed to must _not_ be declared `const&squot;.  Likewise, a&n; * function that calls a non-`const&squot; function usually must not be&n; * `const&squot;.  It does not make sense for a `const&squot; function to return&n; * `void&squot;.&n; */
macro_line|#ifndef __attribute_const__
DECL|macro|__attribute_const__
macro_line|# define __attribute_const__&t;/* unimplemented */
macro_line|#endif
macro_line|#ifndef noinline
DECL|macro|noinline
mdefine_line|#define noinline
macro_line|#endif
macro_line|#ifndef __always_inline
DECL|macro|__always_inline
mdefine_line|#define __always_inline inline
macro_line|#endif
macro_line|#endif /* __LINUX_COMPILER_H */
eof
