macro_line|#ifndef _ASM_CRIS_STRING_H
DECL|macro|_ASM_CRIS_STRING_H
mdefine_line|#define _ASM_CRIS_STRING_H
multiline_comment|/* the optimized memcpy is in arch/cris/lib/string.c */
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
r_int
)paren
suffix:semicolon
multiline_comment|/* New and improved.  In arch/cris/lib/memset.c */
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
