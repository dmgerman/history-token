macro_line|#ifndef _ASM_IA64_STRING_H
DECL|macro|_ASM_IA64_STRING_H
mdefine_line|#define _ASM_IA64_STRING_H
multiline_comment|/*&n; * Here is where we want to put optimized versions of the string&n; * routines.&n; *&n; * Copyright (C) 1998-2000, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;&t;/* remove this once we remove the A-step workaround... */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN&t;1 /* see arch/ia64/lib/strlen.S */
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET&t;1 /* see arch/ia64/lib/memset.S */
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY&t;1 /* see arch/ia64/lib/memcpy.S */
DECL|macro|__HAVE_ARCH_BCOPY
mdefine_line|#define __HAVE_ARCH_BCOPY&t;1 /* see arch/ia64/lib/memcpy.S */
r_extern
id|__kernel_size_t
id|strlen
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
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
r_extern
r_void
op_star
id|__memset_generic
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
id|__bzero
(paren
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|macro|memset
mdefine_line|#define memset(s, c, count)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;void *_s = (s);&t;&t;&t;&t;&t;&bslash;&n;&t;int _c = (c);&t;&t;&t;&t;&t;&bslash;&n;&t;__kernel_size_t _count = (count);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__builtin_constant_p(_c) &amp;&amp; _c == 0)&t;&bslash;&n;&t;&t;__bzero(_s, _count);&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__memset_generic(_s, _c, _count);&t;&bslash;&n;})
macro_line|#endif /* _ASM_IA64_STRING_H */
eof
