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
id|memset
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_STRING_H */
eof
