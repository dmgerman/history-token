macro_line|#ifndef _M68KNOMMU_STRING_H_
DECL|macro|_M68KNOMMU_STRING_H_
mdefine_line|#define _M68KNOMMU_STRING_H_
macro_line|#ifdef __KERNEL__ /* only set these up for kernel code */
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
DECL|function|strcpy
r_static
r_inline
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
id|xdest
op_assign
id|dest
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|function|strncpy
r_static
r_inline
r_char
op_star
id|strncpy
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
comma
r_int
id|n
)paren
(brace
r_char
op_star
id|xdest
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_return
id|xdest
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&bslash;tmoveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=d&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|src
)paren
comma
l_string|&quot;2&quot;
(paren
id|n
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|xdest
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_COLDFIRE
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP
DECL|function|strcmp
r_static
r_inline
r_int
id|strcmp
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_char
id|__res
suffix:semicolon
id|__asm__
(paren
l_string|&quot;1:&bslash;tmoveb %0@+,%2&bslash;n&bslash;t&quot;
multiline_comment|/* get *cs */
l_string|&quot;cmpb %1@+,%2&bslash;n&bslash;t&quot;
multiline_comment|/* compare a byte */
l_string|&quot;jne  2f&bslash;n&bslash;t&quot;
multiline_comment|/* not equal, break out */
l_string|&quot;tstb %2&bslash;n&bslash;t&quot;
multiline_comment|/* at end of cs? */
l_string|&quot;jne  1b&bslash;n&bslash;t&quot;
multiline_comment|/* no, keep going */
l_string|&quot;jra  3f&bslash;n&bslash;t&quot;
multiline_comment|/* strings are equal */
l_string|&quot;2:&bslash;tsubb %1@-,%2&bslash;n&bslash;t&quot;
multiline_comment|/* *cs - *ct */
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ct
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|ct
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP
DECL|function|strncmp
r_static
r_inline
r_int
id|strncmp
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
comma
r_int
id|count
)paren
(brace
r_char
id|__res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
(paren
l_string|&quot;1:&bslash;tmovb %0@+,%3&bslash;n&bslash;t&quot;
multiline_comment|/* get *cs */
l_string|&quot;cmpb   %1@+,%3&bslash;n&bslash;t&quot;
multiline_comment|/* compare a byte */
l_string|&quot;jne    3f&bslash;n&bslash;t&quot;
multiline_comment|/* not equal, break out */
l_string|&quot;tstb   %3&bslash;n&bslash;t&quot;
multiline_comment|/* at end of cs? */
l_string|&quot;jeq    4f&bslash;n&bslash;t&quot;
multiline_comment|/* yes, all done */
l_string|&quot;subql  #1,%2&bslash;n&bslash;t&quot;
multiline_comment|/* no, adjust count */
l_string|&quot;jne    1b&bslash;n&bslash;t&quot;
multiline_comment|/* more to do, keep going */
l_string|&quot;2:&bslash;tmoveq #0,%3&bslash;n&bslash;t&quot;
multiline_comment|/* strings are equal */
l_string|&quot;jra    4f&bslash;n&bslash;t&quot;
l_string|&quot;3:&bslash;tsubb %1@-,%3&bslash;n&bslash;t&quot;
multiline_comment|/* *cs - *ct */
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ct
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|__res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|ct
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_COLDFIRE */
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
id|s
comma
r_int
id|c
comma
r_int
id|count
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
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#else /* KERNEL */
multiline_comment|/*&n; *&t;let user libraries deal with these,&n; *&t;IMHO the kernel has no place defining these functions for user apps&n; */
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY 1
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY 1
DECL|macro|__HAVE_ARCH_STRCAT
mdefine_line|#define __HAVE_ARCH_STRCAT 1
DECL|macro|__HAVE_ARCH_STRNCAT
mdefine_line|#define __HAVE_ARCH_STRNCAT 1
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP 1
DECL|macro|__HAVE_ARCH_STRNCMP
mdefine_line|#define __HAVE_ARCH_STRNCMP 1
DECL|macro|__HAVE_ARCH_STRNICMP
mdefine_line|#define __HAVE_ARCH_STRNICMP 1
DECL|macro|__HAVE_ARCH_STRCHR
mdefine_line|#define __HAVE_ARCH_STRCHR 1
DECL|macro|__HAVE_ARCH_STRRCHR
mdefine_line|#define __HAVE_ARCH_STRRCHR 1
DECL|macro|__HAVE_ARCH_STRSTR
mdefine_line|#define __HAVE_ARCH_STRSTR 1
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN 1
DECL|macro|__HAVE_ARCH_STRNLEN
mdefine_line|#define __HAVE_ARCH_STRNLEN 1
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET 1
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY 1
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE 1
DECL|macro|__HAVE_ARCH_MEMSCAN
mdefine_line|#define __HAVE_ARCH_MEMSCAN 1
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP 1
DECL|macro|__HAVE_ARCH_MEMCHR
mdefine_line|#define __HAVE_ARCH_MEMCHR 1
DECL|macro|__HAVE_ARCH_STRTOK
mdefine_line|#define __HAVE_ARCH_STRTOK 1
macro_line|#endif /* KERNEL */
macro_line|#endif /* _M68K_STRING_H_ */
eof
