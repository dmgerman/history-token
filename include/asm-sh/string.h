macro_line|#ifndef __ASM_SH_STRING_H
DECL|macro|__ASM_SH_STRING_H
mdefine_line|#define __ASM_SH_STRING_H
multiline_comment|/*&n; * Copyright (C) 1999 Niibe Yutaka&n; * But consider these trivial functions to be public domain.&n; */
DECL|macro|__HAVE_ARCH_STRCPY
mdefine_line|#define __HAVE_ARCH_STRCPY
DECL|function|strcpy
r_static
id|__inline__
r_char
op_star
id|strcpy
c_func
(paren
r_char
op_star
id|__dest
comma
r_const
r_char
op_star
id|__src
)paren
(brace
r_register
r_char
op_star
id|__xdest
op_assign
id|__dest
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%1+, %2&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;%2, @%0&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq&t;#0, %2&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__src
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|__src
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|__xdest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRNCPY
mdefine_line|#define __HAVE_ARCH_STRNCPY
DECL|function|strncpy
r_static
id|__inline__
r_char
op_star
id|strncpy
c_func
(paren
r_char
op_star
id|__dest
comma
r_const
r_char
op_star
id|__src
comma
r_int
id|__n
)paren
(brace
r_register
r_char
op_star
id|__xdest
op_assign
id|__dest
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
r_if
c_cond
(paren
id|__n
op_eq
l_int|0
)paren
r_return
id|__xdest
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;mov.b&t;@%1+, %2&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;%2, @%0&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq&t;#0, %2&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; cmp/eq&t;%5,%1&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;#1, %0&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__src
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__dest
)paren
comma
l_string|&quot;1&quot;
(paren
id|__src
)paren
comma
l_string|&quot;r&quot;
(paren
id|__src
op_plus
id|__n
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|__xdest
suffix:semicolon
)brace
DECL|macro|__HAVE_ARCH_STRCMP
mdefine_line|#define __HAVE_ARCH_STRCMP
DECL|function|strcmp
r_static
id|__inline__
r_int
id|strcmp
c_func
(paren
r_const
r_char
op_star
id|__cs
comma
r_const
r_char
op_star
id|__ct
)paren
(brace
r_register
r_int
id|__res
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov.b&t;@%1+, %3&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%0+, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq #0, %3&bslash;n&bslash;t&quot;
l_string|&quot;bt&t;2f&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq %2, %3&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; mov.b&t;@%1+, %3&bslash;n&bslash;t&quot;
l_string|&quot;add&t;#-2, %1&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%3, %2&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|__ct
)paren
suffix:colon
l_string|&quot;t&quot;
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
id|__inline__
r_int
id|strncmp
c_func
(paren
r_const
r_char
op_star
id|__cs
comma
r_const
r_char
op_star
id|__ct
comma
r_int
id|__n
)paren
(brace
r_register
r_int
id|__res
suffix:semicolon
r_int
r_int
id|__dummy
suffix:semicolon
r_if
c_cond
(paren
id|__n
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov.b&t;@%1+, %3&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%0+, %2&bslash;n&bslash;t&quot;
l_string|&quot;cmp/eq %6, %0&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; cmp/eq #0, %3&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;3f&bslash;n&bslash;t&quot;
l_string|&quot; cmp/eq %3, %2&bslash;n&bslash;t&quot;
l_string|&quot;bt/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; mov.b&t;@%1+, %3&bslash;n&bslash;t&quot;
l_string|&quot;add&t;#-2, %1&bslash;n&bslash;t&quot;
l_string|&quot;mov.b&t;@%1, %3&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%3, %2&bslash;n&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__cs
)paren
comma
l_string|&quot;1&quot;
(paren
id|__ct
)paren
comma
l_string|&quot;r&quot;
(paren
id|__cs
op_plus
id|__n
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
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
id|__s
comma
r_int
id|__c
comma
r_int
id|__count
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
id|__dest
comma
id|__const__
r_void
op_star
id|__src
comma
r_int
id|__n
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
id|__s
comma
r_int
id|__c
comma
r_int
id|__n
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
r_extern
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_STRING_H */
eof
