macro_line|#ifndef __ASM_ARM_STRING_H
DECL|macro|__ASM_ARM_STRING_H
mdefine_line|#define __ASM_ARM_STRING_H
multiline_comment|/*&n; * We don&squot;t do inline string functions, since the&n; * optimised inline asm versions are not small.&n; */
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR
r_extern
r_char
op_star
id|strrchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR
r_extern
r_char
op_star
id|strchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
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
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR
r_extern
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_MEMZERO
mdefine_line|#define __HAVE_ARCH_MEMZERO
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
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
id|__memzero
c_func
(paren
r_void
op_star
id|ptr
comma
id|__kernel_size_t
id|n
)paren
suffix:semicolon
DECL|macro|memset
mdefine_line|#define memset(p,v,n)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((n) != 0) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (__builtin_constant_p((v)) &amp;&amp; (v) == 0)&t;&bslash;&n;&t;&t;&t;&t;__memzero((p),(n));&t;&t;&t;&bslash;&n;&t;&t;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;memset((p),(v),(n));&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(p);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|memzero
mdefine_line|#define memzero(p,n) ({ if ((n) != 0) __memzero((p),(n)); (p); })
macro_line|#endif
eof
