multiline_comment|/*&n; *  include/asm-s390/string.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; */
macro_line|#ifndef _S390_STRING_H_
DECL|macro|_S390_STRING_H_
mdefine_line|#define _S390_STRING_H_
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _LINUX_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|macro|__HAVE_ARCH_MEMMOVE
macro_line|#undef __HAVE_ARCH_MEMMOVE
DECL|macro|__HAVE_ARCH_STRNICMP
macro_line|#undef __HAVE_ARCH_STRNICMP
DECL|macro|__HAVE_ARCH_STRNCAT
macro_line|#undef __HAVE_ARCH_STRNCAT
DECL|macro|__HAVE_ARCH_STRNCMP
macro_line|#undef __HAVE_ARCH_STRNCMP
DECL|macro|__HAVE_ARCH_STRCHR
macro_line|#undef __HAVE_ARCH_STRCHR
DECL|macro|__HAVE_ARCH_STRRCHR
macro_line|#undef __HAVE_ARCH_STRRCHR
DECL|macro|__HAVE_ARCH_STRNLEN
macro_line|#undef __HAVE_ARCH_STRNLEN
DECL|macro|__HAVE_ARCH_STRSPN
macro_line|#undef __HAVE_ARCH_STRSPN
DECL|macro|__HAVE_ARCH_STRPBRK
macro_line|#undef __HAVE_ARCH_STRPBRK
DECL|macro|__HAVE_ARCH_STRTOK
macro_line|#undef __HAVE_ARCH_STRTOK
DECL|macro|__HAVE_ARCH_BCOPY
macro_line|#undef __HAVE_ARCH_BCOPY
DECL|macro|__HAVE_ARCH_MEMCMP
macro_line|#undef __HAVE_ARCH_MEMCMP
DECL|macro|__HAVE_ARCH_MEMSCAN
macro_line|#undef __HAVE_ARCH_MEMSCAN
DECL|macro|__HAVE_ARCH_STRSTR
macro_line|#undef __HAVE_ARCH_STRSTR
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
DECL|function|memchr
r_extern
r_inline
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|cs
comma
r_int
id|c
comma
r_int
id|count
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lr    0,%2&bslash;n&quot;
l_string|&quot;   la    %0,0(%3,%1)&bslash;n&quot;
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   brc   13,1f&bslash;n&quot;
l_string|&quot;   slr   %0,%0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;d&quot;
(paren
id|c
)paren
comma
l_string|&quot;d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|strcpy
r_extern
id|__inline__
r_char
op_star
id|strcpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    0,0&bslash;n&quot;
l_string|&quot;0: mvst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&quot;
suffix:colon
l_string|&quot;+&amp;a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|src
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|strlen
r_extern
id|__inline__
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|len
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    0,0&bslash;n&quot;
l_string|&quot;   lr    %0,%1&bslash;n&quot;
l_string|&quot;0: srst  0,%0&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   lr    %0,0&bslash;n&quot;
l_string|&quot;   sr    %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|strcat
r_extern
id|__inline__
r_char
op_star
id|strcat
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   sr    0,0&bslash;n&quot;
l_string|&quot;0: srst  0,%0&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   lr    %0,0&bslash;n&quot;
l_string|&quot;   sr    0,0&bslash;n&quot;
l_string|&quot;1: mvst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    1b&quot;
suffix:colon
l_string|&quot;+&amp;a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|src
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __S390_STRING_H_ */
eof
