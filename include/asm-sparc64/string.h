multiline_comment|/* $Id: string.h,v 1.20 2001/09/27 04:36:24 kanoj Exp $&n; * string.h: External definitions for optimized assembly string&n; *           routines for the Linux Kernel.&n; *&n; * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996,1997,1999 Jakub Jelinek (jakub@redhat.com)&n; */
macro_line|#ifndef __SPARC64_STRING_H__
DECL|macro|__SPARC64_STRING_H__
mdefine_line|#define __SPARC64_STRING_H__
multiline_comment|/* Really, userland/ksyms should not see any of this stuff. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/asi.h&gt;
r_extern
r_void
op_star
id|__memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#ifndef EXPORT_SYMTAB_STROPS
multiline_comment|/* First the mem*() things. */
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
r_extern
r_void
op_star
id|__builtin_memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|function|__constant_memset
r_static
r_inline
r_void
op_star
id|__constant_memset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|c
comma
id|__kernel_size_t
id|count
)paren
(brace
r_extern
id|__kernel_size_t
id|__bzero
c_func
(paren
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|__bzero
c_func
(paren
id|s
comma
id|count
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
r_else
r_return
id|__memset
c_func
(paren
id|s
comma
id|c
comma
id|count
)paren
suffix:semicolon
)brace
DECL|macro|memset
macro_line|#undef memset
DECL|macro|memset
mdefine_line|#define memset(s, c, count) &bslash;&n;((__builtin_constant_p(count) &amp;&amp; (count) &lt;= 32) ? &bslash;&n; __builtin_memset((s), (c), (count)) : &bslash;&n; (__builtin_constant_p(c) ? &bslash;&n;  __constant_memset((s), (c), (count)) : &bslash;&n;  __memset((s), (c), (count))))
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN
DECL|macro|memscan
macro_line|#undef memscan
DECL|macro|memscan
mdefine_line|#define memscan(__arg0, __char, __arg2)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern void *__memscan_zero(void *, size_t);&t;&t;&t;&bslash;&n;&t;extern void *__memscan_generic(void *, int, size_t);&t;&t;&bslash;&n;&t;void *__retval, *__addr = (__arg0);&t;&t;&t;&t;&bslash;&n;&t;size_t __size = (__arg2);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if(__builtin_constant_p(__char) &amp;&amp; !(__char))&t;&t;&t;&bslash;&n;&t;&t;__retval = __memscan_zero(__addr, __size);&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__retval = __memscan_generic(__addr, (__char), __size);&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__retval;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP
r_extern
r_int
id|memcmp
c_func
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
multiline_comment|/* Now the str*() stuff... */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
r_extern
id|__kernel_size_t
id|strlen
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP
r_extern
r_int
id|strncmp
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#endif /* !EXPORT_SYMTAB_STROPS */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(__SPARC64_STRING_H__) */
eof
