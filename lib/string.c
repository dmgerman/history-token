multiline_comment|/*&n; *  linux/lib/string.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * stupid library routines.. The optimized versions should generally be found&n; * as inline code in &lt;asm-xx/string.h&gt;&n; *&n; * These are buggy as well..&n; *&n; * * Fri Jun 25 1999, Ingo Oeser &lt;ioe@informatik.tu-chemnitz.de&gt;&n; * -  Added strsep() which will replace strtok() soon (because strsep() is&n; *    reentrant and should be faster). Use only strsep() in new code, please.&n; *&n; * * Sat Feb 09 2002, Jason Thomas &lt;jason@topic.com.au&gt;,&n; *                    Matthew Hawkins &lt;matt@mh.dropbear.id.au&gt;&n; * -  Kissed strtok() goodbye&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifndef __HAVE_ARCH_STRNICMP
multiline_comment|/**&n; * strnicmp - Case insensitive, length-limited string comparison&n; * @s1: One string&n; * @s2: The other string&n; * @len: the maximum number of characters to compare&n; */
DECL|function|strnicmp
r_int
id|strnicmp
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
comma
r_int
id|len
)paren
(brace
multiline_comment|/* Yes, Virginia, it had better be unsigned */
r_int
r_char
id|c1
comma
id|c2
suffix:semicolon
id|c1
op_assign
l_int|0
suffix:semicolon
id|c2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_do
(brace
id|c1
op_assign
op_star
id|s1
suffix:semicolon
id|c2
op_assign
op_star
id|s2
suffix:semicolon
id|s1
op_increment
suffix:semicolon
id|s2
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c2
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_eq
id|c2
)paren
r_continue
suffix:semicolon
id|c1
op_assign
id|tolower
c_func
(paren
id|c1
)paren
suffix:semicolon
id|c2
op_assign
id|tolower
c_func
(paren
id|c2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
)paren
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|c1
op_minus
(paren
r_int
)paren
id|c2
suffix:semicolon
)brace
DECL|variable|strnicmp
id|EXPORT_SYMBOL
c_func
(paren
id|strnicmp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCPY
multiline_comment|/**&n; * strcpy - Copy a %NUL terminated string&n; * @dest: Where to copy the string to&n; * @src: Where to copy the string from&n; */
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
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCPY
multiline_comment|/**&n; * strncpy - Copy a length-limited, %NUL-terminated string&n; * @dest: Where to copy the string to&n; * @src: Where to copy the string from&n; * @count: The maximum number of bytes to copy&n; *&n; * The result is not %NUL-terminated if the source exceeds&n; * @count bytes.&n; */
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
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|tmp
op_assign
op_star
id|src
)paren
op_ne
l_int|0
)paren
id|src
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRLCPY
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
id|strlen
c_func
(paren
id|src
)paren
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
id|memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|dest
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCAT
multiline_comment|/**&n; * strcat - Append one %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; */
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
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
op_star
id|dest
)paren
id|dest
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCAT
multiline_comment|/**&n; * strncat - Append a length-limited, %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; * @count: The maximum numbers of bytes to copy&n; *&n; * Note that in contrast to strncpy, strncat ensures the result is&n; * terminated.&n; */
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
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_while
c_loop
(paren
op_star
id|dest
)paren
id|dest
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
op_eq
l_int|0
)paren
(brace
op_star
id|dest
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|tmp
suffix:semicolon
)brace
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRLCAT
multiline_comment|/**&n; * strlcat - Append a length-limited, %NUL-terminated string to another&n; * @dest: The string to be appended to&n; * @src: The string to append to it&n; * @count: The size of the destination buffer.&n; */
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
id|count
)paren
(brace
r_int
id|dsize
op_assign
id|strlen
c_func
(paren
id|dest
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|src
)paren
suffix:semicolon
r_int
id|res
op_assign
id|dsize
op_plus
id|len
suffix:semicolon
multiline_comment|/* This would be a bug */
id|BUG_ON
c_func
(paren
id|dsize
op_ge
id|count
)paren
suffix:semicolon
id|dest
op_add_assign
id|dsize
suffix:semicolon
id|count
op_sub_assign
id|dsize
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|count
)paren
id|len
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|dest
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCMP
multiline_comment|/**&n; * strcmp - Compare two strings&n; * @cs: One string&n; * @ct: Another string&n; */
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
r_char
id|__res
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|__res
op_assign
op_star
id|cs
op_minus
op_star
id|ct
op_increment
)paren
op_ne
l_int|0
op_logical_or
op_logical_neg
op_star
id|cs
op_increment
)paren
r_break
suffix:semicolon
)brace
r_return
id|__res
suffix:semicolon
)brace
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCMP
multiline_comment|/**&n; * strncmp - Compare two length-limited strings&n; * @cs: One string&n; * @ct: Another string&n; * @count: The maximum number of bytes to compare&n; */
DECL|function|strncmp
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
r_register
r_int
r_char
id|__res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
(paren
id|__res
op_assign
op_star
id|cs
op_minus
op_star
id|ct
op_increment
)paren
op_ne
l_int|0
op_logical_or
op_logical_neg
op_star
id|cs
op_increment
)paren
r_break
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
id|__res
suffix:semicolon
)brace
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRCHR
multiline_comment|/**&n; * strchr - Find the first occurrence of a character in a string&n; * @s: The string to be searched&n; * @c: The character to search for&n; */
DECL|function|strchr
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
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|s
op_ne
(paren
r_char
)paren
id|c
suffix:semicolon
op_increment
id|s
)paren
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
)brace
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRRCHR
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
r_const
r_char
op_star
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_star
id|p
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
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|p
op_ge
id|s
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNCHR
multiline_comment|/**&n; * strnchr - Find a character in a length limited string&n; * @s: The string to be searched&n; * @count: The number of characters to be searched&n; * @c: The character to search for&n; */
DECL|function|strnchr
r_char
op_star
id|strnchr
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|c
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
op_decrement
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|s
)paren
r_if
c_cond
(paren
op_star
id|s
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
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|strnchr
id|EXPORT_SYMBOL
c_func
(paren
id|strnchr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRLEN
multiline_comment|/**&n; * strlen - Find the length of a string&n; * @s: The string to be sized&n; */
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
r_const
r_char
op_star
id|sc
suffix:semicolon
r_for
c_loop
(paren
id|sc
op_assign
id|s
suffix:semicolon
op_star
id|sc
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|sc
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRNLEN
multiline_comment|/**&n; * strnlen - Find the length of a length-limited string&n; * @s: The string to be sized&n; * @count: The maximum number of bytes to search&n; */
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
id|count
)paren
(brace
r_const
r_char
op_star
id|sc
suffix:semicolon
r_for
c_loop
(paren
id|sc
op_assign
id|s
suffix:semicolon
id|count
op_decrement
op_logical_and
op_star
id|sc
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_return
id|sc
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSPN
multiline_comment|/**&n; * strspn - Calculate the length of the initial substring of @s which only&n; * &t;contain letters in @accept&n; * @s: The string to be searched&n; * @accept: The string to search for&n; */
DECL|function|strspn
r_int
id|strspn
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_const
r_char
op_star
id|accept
)paren
(brace
r_const
r_char
op_star
id|p
suffix:semicolon
r_const
r_char
op_star
id|a
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|s
suffix:semicolon
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|p
)paren
(brace
r_for
c_loop
(paren
id|a
op_assign
id|accept
suffix:semicolon
op_star
id|a
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|a
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
op_star
id|a
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|a
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|count
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|strspn
id|EXPORT_SYMBOL
c_func
(paren
id|strspn
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; * strcspn - Calculate the length of the initial substring of @s which does&n; * &t;not contain letters in @reject&n; * @s: The string to be searched&n; * @reject: The string to avoid&n; */
DECL|function|strcspn
r_int
id|strcspn
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_const
r_char
op_star
id|reject
)paren
(brace
r_const
r_char
op_star
id|p
suffix:semicolon
r_const
r_char
op_star
id|r
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|s
suffix:semicolon
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|p
)paren
(brace
r_for
c_loop
(paren
id|r
op_assign
id|reject
suffix:semicolon
op_star
id|r
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|r
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
op_star
id|r
)paren
r_return
id|count
suffix:semicolon
)brace
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|strcspn
id|EXPORT_SYMBOL
c_func
(paren
id|strcspn
)paren
suffix:semicolon
macro_line|#ifndef __HAVE_ARCH_STRPBRK
multiline_comment|/**&n; * strpbrk - Find the first occurrence of a set of characters&n; * @cs: The string to be searched&n; * @ct: The characters to search for&n; */
DECL|function|strpbrk
r_char
op_star
id|strpbrk
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
r_const
r_char
op_star
id|sc1
comma
op_star
id|sc2
suffix:semicolon
r_for
c_loop
(paren
id|sc1
op_assign
id|cs
suffix:semicolon
op_star
id|sc1
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc1
)paren
(brace
r_for
c_loop
(paren
id|sc2
op_assign
id|ct
suffix:semicolon
op_star
id|sc2
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_increment
id|sc2
)paren
(brace
r_if
c_cond
(paren
op_star
id|sc1
op_eq
op_star
id|sc2
)paren
r_return
(paren
r_char
op_star
)paren
id|sc1
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSEP
multiline_comment|/**&n; * strsep - Split a string into tokens&n; * @s: The string to be searched&n; * @ct: The characters to search for&n; *&n; * strsep() updates @s to point after the token, ready for the next call.&n; *&n; * It returns empty tokens, too, behaving exactly like the libc function&n; * of that name. In fact, it was stolen from glibc2 and de-fancy-fied.&n; * Same semantics, slimmer shape. ;)&n; */
DECL|function|strsep
r_char
op_star
id|strsep
c_func
(paren
r_char
op_star
op_star
id|s
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_char
op_star
id|sbegin
op_assign
op_star
id|s
comma
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
id|sbegin
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|end
op_assign
id|strpbrk
c_func
(paren
id|sbegin
comma
id|ct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
op_star
id|end
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|s
op_assign
id|end
suffix:semicolon
r_return
id|sbegin
suffix:semicolon
)brace
DECL|variable|strsep
id|EXPORT_SYMBOL
c_func
(paren
id|strsep
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMSET
multiline_comment|/**&n; * memset - Fill a region of memory with the given value&n; * @s: Pointer to the start of the area.&n; * @c: The byte to fill the area with&n; * @count: The size of the area.&n; *&n; * Do not use memset() to access IO space, use memset_io() instead.&n; */
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
id|count
)paren
(brace
r_char
op_star
id|xs
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|xs
op_increment
op_assign
id|c
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
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCPY
multiline_comment|/**&n; * memcpy - Copy one area of memory to another&n; * @dest: Where to copy to&n; * @src: Where to copy from&n; * @count: The size of the area.&n; *&n; * You should not use this function to access IO space, use memcpy_toio()&n; * or memcpy_fromio() instead.&n; */
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
id|count
)paren
(brace
r_char
op_star
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
comma
op_star
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMMOVE
multiline_comment|/**&n; * memmove - Copy one area of memory to another&n; * @dest: Where to copy to&n; * @src: Where to copy from&n; * @count: The size of the area.&n; *&n; * Unlike memcpy(), memmove() copes with overlapping areas.&n; */
DECL|function|memmove
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
(brace
r_char
op_star
id|tmp
comma
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|dest
op_le
id|src
)paren
(brace
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
suffix:semicolon
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|dest
op_plus
id|count
suffix:semicolon
id|s
op_assign
(paren
r_char
op_star
)paren
id|src
op_plus
id|count
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
op_decrement
id|tmp
op_assign
op_star
op_decrement
id|s
suffix:semicolon
)brace
r_return
id|dest
suffix:semicolon
)brace
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCMP
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
id|count
)paren
(brace
r_const
r_int
r_char
op_star
id|su1
comma
op_star
id|su2
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|su1
op_assign
id|cs
comma
id|su2
op_assign
id|ct
suffix:semicolon
l_int|0
OL
id|count
suffix:semicolon
op_increment
id|su1
comma
op_increment
id|su2
comma
id|count
op_decrement
)paren
r_if
c_cond
(paren
(paren
id|res
op_assign
op_star
id|su1
op_minus
op_star
id|su2
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMSCAN
multiline_comment|/**&n; * memscan - Find a character in an area of memory.&n; * @addr: The memory area&n; * @c: The byte to search for&n; * @size: The size of the area.&n; *&n; * returns the address of the first occurrence of @c, or 1 byte past&n; * the area if @c is not found&n; */
DECL|function|memscan
r_void
op_star
id|memscan
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|c
comma
r_int
id|size
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
id|c
)paren
r_return
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|p
suffix:semicolon
)brace
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_STRSTR
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
id|strlen
c_func
(paren
id|s2
)paren
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
id|strlen
c_func
(paren
id|s1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|l1
op_ge
id|l2
)paren
(brace
id|l1
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|s1
comma
id|s2
comma
id|l2
)paren
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
l_int|NULL
suffix:semicolon
)brace
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_MEMCHR
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
r_const
r_int
r_char
op_star
id|p
op_assign
id|s
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|c
op_eq
op_star
id|p
op_increment
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|p
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
macro_line|#endif
eof
