multiline_comment|/*&n; *  arch/s390/lib/string.c&n; *    Optimized string functions&n; *&n; *  S390 version&n; *    Copyright (C) 2004 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
DECL|macro|IN_ARCH_STRING_C
mdefine_line|#define IN_ARCH_STRING_C 1
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Helper functions to find the end of a string&n; */
DECL|function|__strend
r_static
r_inline
r_char
op_star
id|__strend
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_register
r_int
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|r0
)paren
comma
l_string|&quot;+a&quot;
(paren
id|s
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|r0
suffix:semicolon
)brace
DECL|function|__strnend
r_static
r_inline
r_char
op_star
id|__strnend
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_register
r_int
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|s
op_plus
id|n
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|p
)paren
comma
l_string|&quot;+a&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|r0
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
)brace
multiline_comment|/**&n; * strlen - Find the length of a string&n; * @s: The string to be sized&n; *&n; * returns the length of @s&n; */
DECL|function|strlen
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
r_return
id|__strend
c_func
(paren
id|s
)paren
op_minus
id|s
suffix:semicolon
)brace
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
multiline_comment|/**&n; * strnlen - Find the length of a length-limited string&n; * @s: The string to be sized&n; * @n: The maximum number of bytes to search&n; *&n; * returns the minimum of the length of @s and @n&n; */
DECL|function|strnlen
r_int
id|strnlen
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_return
id|__strnend
c_func
(paren
id|s
comma
id|n
)paren
op_minus
id|s
suffix:semicolon
)brace
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
)paren
suffix:semicolon
multiline_comment|/**&n; * strcpy - Copy a %NUL terminated string&n; * @dest: Where to copy the string to&n; * @src: Where to copy the string from&n; *&n; * returns a pointer to @dest&n; */
DECL|function|strcpy
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
r_register
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|ret
op_assign
id|dest
suffix:semicolon
id|asm
r_volatile
(paren
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
l_string|&quot;d&quot;
(paren
id|r0
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
multiline_comment|/**&n; * strlcpy - Copy a %NUL terminated string into a sized buffer&n; * @dest: Where to copy the string to&n; * @src: Where to copy the string from&n; * @size: size of destination buffer&n; *&n; * Compatible with *BSD: the result is always a valid&n; * NUL-terminated string that fits in the buffer (unless,&n; * of course, the buffer size is zero). It does not pad&n; * out the result like strncpy() does.&n; */
DECL|function|strlcpy
r_int
id|strlcpy
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
id|size
)paren
(brace
r_int
id|ret
op_assign
id|__strend
c_func
(paren
id|src
)paren
op_minus
id|src
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
r_int
id|len
op_assign
(paren
id|ret
op_ge
id|size
)paren
ques
c_cond
id|size
op_minus
l_int|1
suffix:colon
id|ret
suffix:semicolon
id|dest
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|__builtin_memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|strlcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strlcpy
)paren
suffix:semicolon
multiline_comment|/**&n; * strncpy - Copy a length-limited, %NUL-terminated string&n; * @dest: Where to copy the string to&n; * @src: Where to copy the string from&n; * @n: The maximum number of bytes to copy&n; *&n; * The result is not %NUL-terminated if the source exceeds&n; * @n bytes.&n; */
DECL|function|strncpy
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
r_int
id|len
op_assign
id|__strnend
c_func
(paren
id|src
comma
id|n
)paren
op_minus
id|src
suffix:semicolon
id|__builtin_memset
c_func
(paren
id|dest
op_plus
id|len
comma
l_int|0
comma
id|n
op_minus
id|len
)paren
suffix:semicolon
id|__builtin_memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
multiline_comment|/**&n; * strcat - Append one %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; *&n; * returns a pointer to @dest&n; */
DECL|function|strcat
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
r_register
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
r_char
op_star
id|ret
op_assign
id|dest
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;1: mvst  %0,%2&bslash;n&quot;
l_string|&quot;   jo    1b&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;+a&quot;
(paren
id|dest
)paren
comma
l_string|&quot;+a&quot;
(paren
id|src
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|r0
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0UL
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
multiline_comment|/**&n; * strlcat - Append a length-limited, %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; * @n: The size of the destination buffer.&n; */
DECL|function|strlcat
r_int
id|strlcat
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
r_int
id|dsize
op_assign
id|__strend
c_func
(paren
id|dest
)paren
op_minus
id|dest
suffix:semicolon
r_int
id|len
op_assign
id|__strend
c_func
(paren
id|src
)paren
op_minus
id|src
suffix:semicolon
r_int
id|res
op_assign
id|dsize
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|dsize
OL
id|n
)paren
(brace
id|dest
op_add_assign
id|dsize
suffix:semicolon
id|n
op_sub_assign
id|dsize
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|n
)paren
id|len
op_assign
id|n
op_minus
l_int|1
suffix:semicolon
id|dest
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|__builtin_memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|variable|strlcat
id|EXPORT_SYMBOL
c_func
(paren
id|strlcat
)paren
suffix:semicolon
multiline_comment|/**&n; * strncat - Append a length-limited, %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; * @n: The maximum numbers of bytes to copy&n; *&n; * returns a pointer to @dest&n; *&n; * Note that in contrast to strncpy, strncat ensures the result is&n; * terminated.&n; */
DECL|function|strncat
r_char
op_star
id|strncat
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
r_int
id|len
op_assign
id|__strnend
c_func
(paren
id|src
comma
id|n
)paren
op_minus
id|src
suffix:semicolon
r_char
op_star
id|p
op_assign
id|__strend
c_func
(paren
id|dest
)paren
suffix:semicolon
id|p
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|__builtin_memcpy
c_func
(paren
id|p
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
multiline_comment|/**&n; * strcmp - Compare two strings&n; * @cs: One string&n; * @ct: Another string&n; *&n; * returns   0 if @cs and @ct are equal,&n; *         &lt; 0 if @cs is less than @ct&n; *         &gt; 0 if @cs is greater than @ct&n; */
DECL|function|strcmp
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
r_register
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: clst %2,%3&bslash;n&quot;
l_string|&quot;   jo   0b&bslash;n&quot;
l_string|&quot;   je   1f&bslash;n&quot;
l_string|&quot;   ic   %0,0(%2)&bslash;n&quot;
l_string|&quot;   ic   %1,0(%3)&bslash;n&quot;
l_string|&quot;   sr   %0,%1&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|ret
)paren
comma
l_string|&quot;+d&quot;
(paren
id|r0
)paren
comma
l_string|&quot;+a&quot;
(paren
id|cs
)paren
comma
l_string|&quot;+a&quot;
(paren
id|ct
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
multiline_comment|/**&n; * strrchr - Find the last occurrence of a character in a string&n; * @s: The string to be searched&n; * @c: The character to search for&n; */
DECL|function|strrchr
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
(brace
r_int
id|len
op_assign
id|__strend
c_func
(paren
id|s
)paren
op_minus
id|s
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
r_do
(brace
r_if
c_cond
(paren
id|s
(braket
id|len
)braket
op_eq
(paren
r_char
)paren
id|c
)paren
r_return
(paren
r_char
op_star
)paren
id|s
op_plus
id|len
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
OG
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
multiline_comment|/**&n; * strstr - Find the first substring in a %NUL terminated string&n; * @s1: The string to be searched&n; * @s2: The string to search for&n; */
DECL|function|strstr
r_char
op_star
id|strstr
c_func
(paren
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
)paren
(brace
r_int
id|l1
comma
id|l2
suffix:semicolon
id|l2
op_assign
id|__strend
c_func
(paren
id|s2
)paren
op_minus
id|s2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l2
)paren
r_return
(paren
r_char
op_star
)paren
id|s1
suffix:semicolon
id|l1
op_assign
id|__strend
c_func
(paren
id|s1
)paren
op_minus
id|s1
suffix:semicolon
r_while
c_loop
(paren
id|l1
op_decrement
op_ge
id|l2
)paren
(brace
r_register
r_int
r_int
id|r2
id|asm
c_func
(paren
l_string|&quot;2&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|s1
suffix:semicolon
r_register
r_int
r_int
id|r3
id|asm
c_func
(paren
l_string|&quot;3&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|l2
suffix:semicolon
r_register
r_int
r_int
id|r4
id|asm
c_func
(paren
l_string|&quot;4&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|s2
suffix:semicolon
r_register
r_int
r_int
id|r5
id|asm
c_func
(paren
l_string|&quot;5&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|l2
suffix:semicolon
r_int
id|cc
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: clcle %1,%3,0&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|cc
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r2
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r3
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r4
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r5
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cc
)paren
r_return
(paren
r_char
op_star
)paren
id|s1
suffix:semicolon
id|s1
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
multiline_comment|/**&n; * memchr - Find a character in an area of memory.&n; * @s: The memory area&n; * @c: The byte to search for&n; * @n: The size of the area.&n; *&n; * returns the address of the first occurrence of @c, or %NULL&n; * if @c is not found&n; */
DECL|function|memchr
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|s
comma
r_int
id|c
comma
r_int
id|n
)paren
(brace
r_register
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
(paren
r_char
)paren
id|c
suffix:semicolon
r_const
r_void
op_star
id|ret
op_assign
id|s
op_plus
id|n
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   jl&t;1f&bslash;n&quot;
l_string|&quot;   la    %0,0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;+a&quot;
(paren
id|ret
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|r0
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
multiline_comment|/**&n; * memcmp - Compare two areas of memory&n; * @cs: One area of memory&n; * @ct: Another area of memory&n; * @count: The size of the area.&n; */
DECL|function|memcmp
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
id|n
)paren
(brace
r_register
r_int
r_int
id|r2
id|asm
c_func
(paren
l_string|&quot;2&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|cs
suffix:semicolon
r_register
r_int
r_int
id|r3
id|asm
c_func
(paren
l_string|&quot;3&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|n
suffix:semicolon
r_register
r_int
r_int
id|r4
id|asm
c_func
(paren
l_string|&quot;4&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|ct
suffix:semicolon
r_register
r_int
r_int
id|r5
id|asm
c_func
(paren
l_string|&quot;5&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|n
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: clcle %1,%3,0&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
l_string|&quot;   ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ret
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r2
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r3
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r4
)paren
comma
l_string|&quot;+a&quot;
(paren
id|r5
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ret
op_assign
op_star
(paren
r_char
op_star
)paren
id|r2
op_minus
op_star
(paren
r_char
op_star
)paren
id|r4
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
multiline_comment|/**&n; * memscan - Find a character in an area of memory.&n; * @s: The memory area&n; * @c: The byte to search for&n; * @n: The size of the area.&n; *&n; * returns the address of the first occurrence of @c, or 1 byte past&n; * the area if @c is not found&n; */
DECL|function|memscan
r_void
op_star
id|memscan
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
id|n
)paren
(brace
r_register
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;0&quot;
)paren
op_assign
(paren
r_char
)paren
id|c
suffix:semicolon
r_const
r_void
op_star
id|ret
op_assign
id|s
op_plus
id|n
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;0: srst  %0,%1&bslash;n&quot;
l_string|&quot;   jo    0b&bslash;n&quot;
suffix:colon
l_string|&quot;+a&quot;
(paren
id|ret
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|r0
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
multiline_comment|/**&n; * memcpy - Copy one area of memory to another&n; * @dest: Where to copy to&n; * @src: Where to copy from&n; * @n: The size of the area.&n; *&n; * returns a pointer to @dest&n; */
DECL|function|memcpy
r_void
op_star
id|memcpy
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
id|n
)paren
(brace
r_return
id|__builtin_memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|n
)paren
suffix:semicolon
)brace
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
multiline_comment|/**&n; * memset - Fill a region of memory with the given value&n; * @s: Pointer to the start of the area.&n; * @c: The byte to fill the area with&n; * @n: The size of the area.&n; *&n; * returns a pointer to @s&n; */
DECL|function|memset
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
id|n
)paren
(brace
r_char
op_star
id|xs
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|0
)paren
r_return
id|__builtin_memset
c_func
(paren
id|s
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
id|xs
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
r_do
(brace
op_star
id|xs
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|n
OG
l_int|0
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
eof
