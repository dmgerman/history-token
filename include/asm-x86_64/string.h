macro_line|#ifndef _X86_64_STRING_H_
DECL|macro|_X86_64_STRING_H_
mdefine_line|#define _X86_64_STRING_H_
macro_line|#ifdef __KERNEL__
DECL|macro|struct_cpy
mdefine_line|#define struct_cpy(x,y) (*(x)=*(y))
multiline_comment|/* Written 2002 by Andi Kleen */
multiline_comment|/* Only used for special circumstances. Stolen from i386/string.h */
DECL|function|__inline_memcpy
r_static
r_inline
r_void
op_star
id|__inline_memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|n
)paren
(brace
r_int
r_int
id|d0
comma
id|d1
comma
id|d2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rep ; movsl&bslash;n&bslash;t&quot;
l_string|&quot;testb $2,%b4&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;1:&bslash;ttestb $1,%b4&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|n
op_div
l_int|4
)paren
comma
l_string|&quot;q&quot;
(paren
id|n
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_int
)paren
id|to
)paren
comma
l_string|&quot;2&quot;
(paren
(paren
r_int
)paren
id|from
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
multiline_comment|/* Even with __builtin_ the compiler may decide to use the out of line&n;   function. */
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY 1
r_extern
r_void
op_star
id|__memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|memcpy
mdefine_line|#define memcpy(dst,src,len) &bslash;&n;&t;({ size_t __len = (len);&t;&t;&t;&t;&bslash;&n;&t;   void *__ret;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   if (__builtin_constant_p(len) &amp;&amp; __len &gt;= 64)&t;&bslash;&n;&t;&t; __ret = __memcpy((dst),(src),__len);&t;&t;&bslash;&n;&t;   else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; __ret = __builtin_memcpy((dst),(src),__len);&t;&bslash;&n;&t;   __ret; }) 
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|memset
mdefine_line|#define memset __builtin_memset
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Use C out of line version for memcmp */
DECL|macro|memcmp
mdefine_line|#define memcmp __builtin_memcmp
r_int
id|memcmp
c_func
(paren
r_const
r_void
op_star
id|cs
comma
r_const
r_void
op_star
id|ct
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* out of line string functions use always C versions */
DECL|macro|strlen
mdefine_line|#define strlen __builtin_strlen
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
DECL|macro|strcpy
mdefine_line|#define strcpy __builtin_strcpy
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
suffix:semicolon
DECL|macro|strcat
mdefine_line|#define strcat __builtin_strcat
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
suffix:semicolon
DECL|macro|strcmp
mdefine_line|#define strcmp __builtin_strcmp
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
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
