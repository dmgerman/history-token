macro_line|#ifndef _ASM_M32R_STRING_H
DECL|macro|_ASM_M32R_STRING_H
mdefine_line|#define _ASM_M32R_STRING_H
multiline_comment|/* $Id$ */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define  __HAVE_ARCH_STRLEN
r_extern
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define  __HAVE_ARCH_MEMCPY
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|__to
comma
id|__const__
r_void
op_star
id|__from
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define  __HAVE_ARCH_MEMSET
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
id|__s
comma
r_int
id|__c
comma
r_int
id|__count
)paren
suffix:semicolon
macro_line|#endif  /* _ASM_M32R_STRING_H */
eof
