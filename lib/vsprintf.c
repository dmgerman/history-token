multiline_comment|/*&n; *  linux/lib/vsprintf.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/* vsprintf.c -- Lars Wirzenius &amp; Linus Torvalds. */
multiline_comment|/*&n; * Wirzenius wrote this portably, Torvalds fucked it up :-)&n; */
multiline_comment|/* &n; * Fri Jul 13 2001 Crutcher Dunnavant &lt;crutcher+kernel@datastacks.com&gt;&n; * - changed to provide snprintf and vsnprintf functions&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
multiline_comment|/**&n; * simple_strtoul - convert a string to an unsigned long&n; * @cp: The start of the string&n; * @endp: A pointer to the end of the parsed string will be placed here&n; * @base: The number base to use&n; */
DECL|function|simple_strtoul
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|base
op_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|base
op_assign
l_int|8
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_char|&squot;x&squot;
)paren
op_logical_and
id|isxdigit
c_func
(paren
id|cp
(braket
l_int|1
)braket
)paren
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|base
op_assign
l_int|16
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|isxdigit
c_func
(paren
op_star
id|cp
)paren
op_logical_and
(paren
id|value
op_assign
id|isdigit
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
op_star
id|cp
op_minus
l_char|&squot;0&squot;
suffix:colon
id|toupper
c_func
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
OL
id|base
)paren
(brace
id|result
op_assign
id|result
op_star
id|base
op_plus
id|value
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
(paren
r_char
op_star
)paren
id|cp
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * simple_strtol - convert a string to a signed long&n; * @cp: The start of the string&n; * @endp: A pointer to the end of the parsed string will be placed here&n; * @base: The number base to use&n; */
DECL|function|simple_strtol
r_int
id|simple_strtol
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_return
op_minus
id|simple_strtoul
c_func
(paren
id|cp
op_plus
l_int|1
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
r_return
id|simple_strtoul
c_func
(paren
id|cp
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * simple_strtoull - convert a string to an unsigned long long&n; * @cp: The start of the string&n; * @endp: A pointer to the end of the parsed string will be placed here&n; * @base: The number base to use&n; */
DECL|function|simple_strtoull
r_int
r_int
r_int
id|simple_strtoull
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_int
r_int
r_int
id|result
op_assign
l_int|0
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|base
op_assign
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|base
op_assign
l_int|8
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_char|&squot;x&squot;
)paren
op_logical_and
id|isxdigit
c_func
(paren
id|cp
(braket
l_int|1
)braket
)paren
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|base
op_assign
l_int|16
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|isxdigit
c_func
(paren
op_star
id|cp
)paren
op_logical_and
(paren
id|value
op_assign
id|isdigit
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
op_star
id|cp
op_minus
l_char|&squot;0&squot;
suffix:colon
(paren
id|islower
c_func
(paren
op_star
id|cp
)paren
ques
c_cond
id|toupper
c_func
(paren
op_star
id|cp
)paren
suffix:colon
op_star
id|cp
)paren
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
OL
id|base
)paren
(brace
id|result
op_assign
id|result
op_star
id|base
op_plus
id|value
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
(paren
r_char
op_star
)paren
id|cp
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * simple_strtoll - convert a string to a signed long long&n; * @cp: The start of the string&n; * @endp: A pointer to the end of the parsed string will be placed here&n; * @base: The number base to use&n; */
DECL|function|simple_strtoll
r_int
r_int
id|simple_strtoll
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_return
op_minus
id|simple_strtoull
c_func
(paren
id|cp
op_plus
l_int|1
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
r_return
id|simple_strtoull
c_func
(paren
id|cp
comma
id|endp
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|skip_atoi
r_static
r_int
id|skip_atoi
c_func
(paren
r_const
r_char
op_star
op_star
id|s
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
op_star
op_star
id|s
)paren
)paren
id|i
op_assign
id|i
op_star
l_int|10
op_plus
op_star
(paren
(paren
op_star
id|s
)paren
op_increment
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|ZEROPAD
mdefine_line|#define ZEROPAD&t;1&t;&t;/* pad with zero */
DECL|macro|SIGN
mdefine_line|#define SIGN&t;2&t;&t;/* unsigned/signed long */
DECL|macro|PLUS
mdefine_line|#define PLUS&t;4&t;&t;/* show plus */
DECL|macro|SPACE
mdefine_line|#define SPACE&t;8&t;&t;/* space if plus */
DECL|macro|LEFT
mdefine_line|#define LEFT&t;16&t;&t;/* left justified */
DECL|macro|SPECIAL
mdefine_line|#define SPECIAL&t;32&t;&t;/* 0x */
DECL|macro|LARGE
mdefine_line|#define LARGE&t;64&t;&t;/* use &squot;ABCDEF&squot; instead of &squot;abcdef&squot; */
DECL|function|number
r_static
r_char
op_star
id|number
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|end
comma
r_int
r_int
id|num
comma
r_int
id|base
comma
r_int
id|size
comma
r_int
id|precision
comma
r_int
id|type
)paren
(brace
r_char
id|c
comma
id|sign
comma
id|tmp
(braket
l_int|66
)braket
suffix:semicolon
r_const
r_char
op_star
id|digits
suffix:semicolon
r_static
r_const
r_char
id|small_digits
(braket
)braket
op_assign
l_string|&quot;0123456789abcdefghijklmnopqrstuvwxyz&quot;
suffix:semicolon
r_static
r_const
r_char
id|large_digits
(braket
)braket
op_assign
l_string|&quot;0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;
suffix:semicolon
r_int
id|i
suffix:semicolon
id|digits
op_assign
(paren
id|type
op_amp
id|LARGE
)paren
ques
c_cond
id|large_digits
suffix:colon
id|small_digits
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|LEFT
)paren
id|type
op_and_assign
op_complement
id|ZEROPAD
suffix:semicolon
r_if
c_cond
(paren
id|base
template_param
l_int|36
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
(paren
id|type
op_amp
id|ZEROPAD
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot; &squot;
suffix:semicolon
id|sign
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SIGN
)paren
(brace
r_if
c_cond
(paren
id|num
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|num
op_assign
op_minus
id|num
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|PLUS
)paren
(brace
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_amp
id|SPACE
)paren
(brace
id|sign
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
id|size
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
id|size
op_decrement
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_while
c_loop
(paren
id|num
op_ne
l_int|0
)paren
id|tmp
(braket
id|i
op_increment
)braket
op_assign
id|digits
(braket
id|do_div
c_func
(paren
id|num
comma
id|base
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|precision
)paren
id|precision
op_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|precision
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
(paren
id|ZEROPAD
op_plus
id|LEFT
)paren
)paren
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sign
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
id|sign
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_amp
id|SPECIAL
)paren
(brace
r_if
c_cond
(paren
id|base
op_eq
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|base
op_eq
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_increment
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
id|digits
(braket
l_int|33
)braket
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|type
op_amp
id|LEFT
)paren
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
id|c
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|i
OL
id|precision
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
id|tmp
(braket
id|i
)braket
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buf
op_le
id|end
)paren
op_star
id|buf
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|buf
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/**&n;* vsnprintf - Format a string and place it in a buffer&n;* @buf: The buffer to place the result into&n;* @size: The size of the buffer, including the trailing null space&n;* @fmt: The format string to use&n;* @args: Arguments for the format string&n;*&n;* Call this function if you are already dealing with a va_list.&n;* You probably want snprintf instead.&n; */
DECL|function|vsnprintf
r_int
id|vsnprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_int
r_int
id|num
suffix:semicolon
r_int
id|i
comma
id|base
suffix:semicolon
r_char
op_star
id|str
comma
op_star
id|end
comma
id|c
suffix:semicolon
r_const
r_char
op_star
id|s
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags to number() */
r_int
id|field_width
suffix:semicolon
multiline_comment|/* width of output field */
r_int
id|precision
suffix:semicolon
multiline_comment|/* min. # of digits for integers; max&n;&t;&t;&t;&t;   number of chars for from string */
r_int
id|qualifier
suffix:semicolon
multiline_comment|/* &squot;h&squot;, &squot;l&squot;, or &squot;L&squot; for integer fields */
multiline_comment|/* &squot;z&squot; support added 23/7/1999 S.H.    */
multiline_comment|/* &squot;z&squot; changed to &squot;Z&squot; --davidm 1/25/99 */
id|str
op_assign
id|buf
suffix:semicolon
id|end
op_assign
id|buf
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|buf
op_minus
l_int|1
)paren
(brace
id|end
op_assign
(paren
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|size
op_assign
id|end
op_minus
id|buf
op_plus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
op_star
id|fmt
suffix:semicolon
op_increment
id|str
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* process flags */
id|flags
op_assign
l_int|0
suffix:semicolon
id|repeat
suffix:colon
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* this also skips first &squot;%&squot; */
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;-&squot;
suffix:colon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|flags
op_or_assign
id|PLUS
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
id|flags
op_or_assign
id|SPACE
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;#&squot;
suffix:colon
id|flags
op_or_assign
id|SPECIAL
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_case
l_char|&squot;0&squot;
suffix:colon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* get field width */
id|field_width
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|field_width
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|field_width
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field_width
OL
l_int|0
)paren
(brace
id|field_width
op_assign
op_minus
id|field_width
suffix:semicolon
id|flags
op_or_assign
id|LEFT
suffix:semicolon
)brace
)brace
multiline_comment|/* get the precision */
id|precision
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;.&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|precision
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* it&squot;s the next argument */
id|precision
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|precision
OL
l_int|0
)paren
id|precision
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* get the conversion qualifier */
id|qualifier
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;h&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;L&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|qualifier
op_assign
op_star
id|fmt
suffix:semicolon
op_increment
id|fmt
suffix:semicolon
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
op_logical_and
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
)paren
(brace
id|qualifier
op_assign
l_char|&squot;L&squot;
suffix:semicolon
op_increment
id|fmt
suffix:semicolon
)brace
)brace
multiline_comment|/* default base */
id|base
op_assign
l_int|10
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
)brace
id|c
op_assign
(paren
r_int
r_char
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
id|c
suffix:semicolon
op_increment
id|str
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|field_width
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|s
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
id|s
op_assign
l_string|&quot;&lt;NULL&gt;&quot;
suffix:semicolon
id|len
op_assign
id|strnlen
c_func
(paren
id|s
comma
id|precision
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LEFT
)paren
)paren
(brace
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
op_star
id|s
suffix:semicolon
op_increment
id|str
suffix:semicolon
op_increment
id|s
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|field_width
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
r_if
c_cond
(paren
id|field_width
op_eq
op_minus
l_int|1
)paren
(brace
id|field_width
op_assign
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|flags
op_or_assign
id|ZEROPAD
suffix:semicolon
)brace
id|str
op_assign
id|number
c_func
(paren
id|str
comma
id|end
comma
(paren
r_int
r_int
)paren
id|va_arg
c_func
(paren
id|args
comma
r_void
op_star
)paren
comma
l_int|16
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
multiline_comment|/* FIXME:&n;&t;&t;&t;&t;* What does C99 say about the overflow case here? */
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;Z&squot;
)paren
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
op_star
id|ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|ip
op_assign
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;%&squot;
suffix:colon
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* integer number formats - set up the flags and &quot;break&quot; */
r_case
l_char|&squot;o&squot;
suffix:colon
id|base
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
id|flags
op_or_assign
id|LARGE
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
id|base
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;i&squot;
suffix:colon
id|flags
op_or_assign
id|SIGN
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_increment
id|str
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
)paren
(brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
op_star
id|fmt
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
r_else
(brace
op_decrement
id|fmt
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;L&squot;
)paren
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;l&squot;
)paren
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|qualifier
op_eq
l_char|&squot;h&squot;
)paren
(brace
id|num
op_assign
(paren
r_int
r_int
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
r_else
(brace
id|num
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SIGN
)paren
id|num
op_assign
(paren
r_int
r_int
)paren
id|num
suffix:semicolon
)brace
id|str
op_assign
id|number
c_func
(paren
id|str
comma
id|end
comma
id|num
comma
id|base
comma
id|field_width
comma
id|precision
comma
id|flags
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|str
op_le
id|end
)paren
op_star
id|str
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
multiline_comment|/* don&squot;t write out a null byte if the buf size is zero */
op_star
id|end
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* the trailing null byte doesn&squot;t count towards the total&n;&t;* ++str;&n;&t;*/
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
multiline_comment|/**&n; * snprintf - Format a string and place it in a buffer&n; * @buf: The buffer to place the result into&n; * @size: The size of the buffer, including the trailing null space&n; * @fmt: The format string to use&n; * @...: Arguments for the format string&n; */
DECL|function|snprintf
r_int
id|snprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsnprintf
c_func
(paren
id|buf
comma
id|size
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/**&n; * vsprintf - Format a string and place it in a buffer&n; * @buf: The buffer to place the result into&n; * @fmt: The format string to use&n; * @args: Arguments for the format string&n; *&n; * Call this function if you are already dealing with a va_list.&n; * You probably want sprintf instead.&n; */
DECL|function|vsprintf
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_return
id|vsnprintf
c_func
(paren
id|buf
comma
l_int|0xFFFFFFFFUL
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sprintf - Format a string and place it in a buffer&n; * @buf: The buffer to place the result into&n; * @fmt: The format string to use&n; * @...: Arguments for the format string&n; */
DECL|function|sprintf
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/**&n; * vsscanf - Unformat a buffer into a list of arguments&n; * @buf:&t;input buffer&n; * @fmt:&t;format of buffer&n; * @args:&t;arguments&n; */
DECL|function|vsscanf
r_int
id|vsscanf
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_const
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_int
id|qualifier
suffix:semicolon
r_int
id|base
suffix:semicolon
r_int
id|field_width
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|is_sign
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|fmt
op_logical_and
op_star
id|str
)paren
(brace
multiline_comment|/* skip any white space in format */
multiline_comment|/* white space in format matchs any amount of&n;&t;&t; * white space, including none, in the input.&n;&t;&t; */
r_if
c_cond
(paren
id|isspace
c_func
(paren
op_star
id|fmt
)paren
)paren
(brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|fmt
)paren
)paren
op_increment
id|fmt
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|str
)paren
)paren
op_increment
id|str
suffix:semicolon
)brace
multiline_comment|/* anything that is not a conversion must match exactly */
r_if
c_cond
(paren
op_star
id|fmt
op_ne
l_char|&squot;%&squot;
op_logical_and
op_star
id|fmt
)paren
(brace
r_if
c_cond
(paren
op_star
id|fmt
op_increment
op_ne
op_star
id|str
op_increment
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|fmt
)paren
r_break
suffix:semicolon
op_increment
id|fmt
suffix:semicolon
multiline_comment|/* skip this conversion.&n;&t;&t; * advance both strings to next white space&n;&t;&t; */
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|isspace
c_func
(paren
op_star
id|fmt
)paren
op_logical_and
op_star
id|fmt
)paren
id|fmt
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|isspace
c_func
(paren
op_star
id|str
)paren
op_logical_and
op_star
id|str
)paren
id|str
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* get field width */
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|fmt
)paren
)paren
id|field_width
op_assign
id|skip_atoi
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
multiline_comment|/* get conversion qualifier */
id|qualifier
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;h&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;L&squot;
op_logical_or
op_star
id|fmt
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|qualifier
op_assign
op_star
id|fmt
suffix:semicolon
id|fmt
op_increment
suffix:semicolon
)brace
id|base
op_assign
l_int|10
suffix:semicolon
id|is_sign
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|fmt
op_logical_or
op_logical_neg
op_star
id|str
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|fmt
op_increment
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
(brace
r_char
op_star
id|s
op_assign
(paren
r_char
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field_width
op_eq
op_minus
l_int|1
)paren
id|field_width
op_assign
l_int|1
suffix:semicolon
r_do
(brace
op_star
id|s
op_increment
op_assign
op_star
id|str
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|field_width
op_decrement
OG
l_int|0
op_logical_and
op_star
id|str
)paren
(brace
suffix:semicolon
)brace
id|num
op_increment
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
(brace
r_char
op_star
id|s
op_assign
(paren
r_char
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field_width
op_eq
op_minus
l_int|1
)paren
(brace
id|field_width
op_assign
id|INT_MAX
suffix:semicolon
)brace
multiline_comment|/* first, skip leading white space in buffer */
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|str
)paren
)paren
id|str
op_increment
suffix:semicolon
multiline_comment|/* now copy until next white space */
r_while
c_loop
(paren
op_star
id|str
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|str
)paren
op_logical_and
id|field_width
op_decrement
)paren
(brace
op_star
id|s
op_increment
op_assign
op_star
id|str
op_increment
suffix:semicolon
)brace
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
multiline_comment|/* return number of characters read so far */
(brace
r_int
op_star
id|i
op_assign
(paren
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|i
op_assign
id|str
op_minus
id|buf
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
id|base
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
r_case
l_char|&squot;X&squot;
suffix:colon
id|base
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
id|base
op_assign
l_int|0
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
id|is_sign
op_assign
l_int|1
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
r_break
suffix:semicolon
r_case
l_char|&squot;%&squot;
suffix:colon
multiline_comment|/* looking for &squot;%&squot; in str */
r_if
c_cond
(paren
op_star
id|str
op_increment
op_ne
l_char|&squot;%&squot;
)paren
r_return
id|num
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* invalid format; stop here */
r_return
id|num
suffix:semicolon
)brace
multiline_comment|/* have some sort of integer conversion.&n;&t;&t; * first, skip white space in buffer.&n;&t;&t; */
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|str
)paren
)paren
id|str
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|str
op_logical_or
(paren
id|base
op_eq
l_int|16
op_logical_and
op_logical_neg
id|isxdigit
c_func
(paren
op_star
id|str
)paren
)paren
op_logical_or
(paren
id|base
op_eq
l_int|10
op_logical_and
op_logical_neg
id|isdigit
c_func
(paren
op_star
id|str
)paren
)paren
op_logical_or
(paren
id|base
op_eq
l_int|8
op_logical_and
(paren
op_logical_neg
id|isdigit
c_func
(paren
op_star
id|str
)paren
op_logical_or
op_star
id|str
OG
l_char|&squot;7&squot;
)paren
)paren
op_logical_or
(paren
id|base
op_eq
l_int|0
op_logical_and
op_logical_neg
id|isdigit
c_func
(paren
op_star
id|str
)paren
)paren
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|qualifier
)paren
(brace
r_case
l_char|&squot;h&squot;
suffix:colon
r_if
c_cond
(paren
id|is_sign
)paren
(brace
r_int
op_star
id|s
op_assign
(paren
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|s
op_assign
(paren
r_int
)paren
id|simple_strtol
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
op_star
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
op_star
)paren
suffix:semicolon
op_star
id|s
op_assign
(paren
r_int
r_int
)paren
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
r_if
c_cond
(paren
id|is_sign
)paren
(brace
r_int
op_star
id|l
op_assign
(paren
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|l
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
op_star
id|l
op_assign
(paren
r_int
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
op_star
)paren
suffix:semicolon
op_star
id|l
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;L&squot;
suffix:colon
r_if
c_cond
(paren
id|is_sign
)paren
(brace
r_int
r_int
op_star
id|l
op_assign
(paren
r_int
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
op_star
)paren
suffix:semicolon
op_star
id|l
op_assign
id|simple_strtoll
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
r_int
op_star
id|l
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
r_int
op_star
)paren
suffix:semicolon
op_star
id|l
op_assign
id|simple_strtoull
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;Z&squot;
suffix:colon
(brace
r_int
op_star
id|s
op_assign
(paren
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|s
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|is_sign
)paren
(brace
r_int
op_star
id|i
op_assign
(paren
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
op_star
)paren
suffix:semicolon
op_star
id|i
op_assign
(paren
r_int
)paren
id|simple_strtol
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
op_star
id|i
op_assign
(paren
r_int
r_int
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_int
r_int
op_star
)paren
suffix:semicolon
op_star
id|i
op_assign
(paren
r_int
r_int
)paren
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|next
comma
id|base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|num
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
r_break
suffix:semicolon
id|str
op_assign
id|next
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
multiline_comment|/**&n; * sscanf - Unformat a buffer into a list of arguments&n; * @buf:&t;input buffer&n; * @fmt:&t;formatting of buffer&n; * @...:&t;resulting arguments&n; */
DECL|function|sscanf
r_int
id|sscanf
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsscanf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
