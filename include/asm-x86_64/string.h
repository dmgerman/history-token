macro_line|#ifndef _X86_64_STRING_H_
DECL|macro|_X86_64_STRING_H_
mdefine_line|#define _X86_64_STRING_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|struct_cpy
mdefine_line|#define struct_cpy(x,y) (*(x)=*(y))
DECL|macro|__HAVE_ARCH_MEMCMP
mdefine_line|#define __HAVE_ARCH_MEMCMP
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
DECL|macro|memset
mdefine_line|#define memset __builtin_memset
DECL|macro|memcpy
mdefine_line|#define memcpy __builtin_memcpy
DECL|macro|memcmp
mdefine_line|#define memcmp __builtin_memcmp
multiline_comment|/* Work around &quot;undefined reference to strlen&quot; linker errors.  */
multiline_comment|/* #define strlen __builtin_strlen */
DECL|macro|__HAVE_ARCH_STRLEN
mdefine_line|#define __HAVE_ARCH_STRLEN
DECL|function|strlen
r_static
r_inline
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
id|d0
suffix:semicolon
r_register
r_int
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %0&bslash;n&bslash;t&quot;
l_string|&quot;decl %0&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0xffffffff
)paren
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
r_extern
r_char
op_star
id|strstr
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
