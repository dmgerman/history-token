multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.3  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*&n; * Source file for kernel interface to kernel log facility&n; */
macro_line|#include &quot;eicon.h&quot;
macro_line|#include &quot;sys.h&quot;
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|MAX
macro_line|#undef MAX
DECL|macro|MIN
macro_line|#undef MIN
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;divalog.h&quot;
macro_line|#include &quot;uxio.h&quot;
multiline_comment|/*&n; * Implementation of printf and sprintf for kernel&n; */
DECL|macro|MAX_BUFF
mdefine_line|#define MAX_BUFF    (80)        /* limit size of temporary buffers */
DECL|macro|WRITE_CHAR
mdefine_line|#define WRITE_CHAR(BUFFER, SIZE, C) &bslash;&n;  if (--(SIZE) &lt; 0) { (BUFFER)--; *(BUFFER) = &squot;&bslash;0&squot;; return; } *(BUFFER)++ = (C)
multiline_comment|/*&n; * convert a number to decimal ASCII&n; */
r_static
DECL|function|do_decimal
r_void
id|do_decimal
c_func
(paren
r_char
op_star
id|temp
comma
r_int
id|temp_len
comma
r_int
r_int
id|value
comma
r_char
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|temp_len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
(paren
(paren
id|value
op_mod
l_int|10
)paren
op_plus
(paren
r_int
)paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|value
op_div_assign
l_int|10
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
(paren
id|temp_len
op_minus
l_int|1
)paren
suffix:semicolon
id|temp
(braket
id|i
)braket
op_eq
l_char|&squot;0&squot;
suffix:semicolon
id|i
op_decrement
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
(brace
op_star
id|s
op_increment
op_assign
id|temp
(braket
id|i
op_decrement
)braket
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * convert a number to octal ASCII&n; */
r_static
DECL|function|do_octal
r_void
id|do_octal
c_func
(paren
r_char
op_star
id|temp
comma
r_int
r_int
id|value
comma
r_char
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
(braket
id|i
)braket
op_assign
(paren
r_char
)paren
(paren
(paren
id|value
op_amp
l_int|07
)paren
op_plus
(paren
r_int
)paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|3
suffix:semicolon
)brace
id|temp
(braket
l_int|11
)braket
op_and_assign
l_char|&squot;3&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|11
suffix:semicolon
id|temp
(braket
id|i
)braket
op_eq
l_char|&squot;0&squot;
suffix:semicolon
id|i
op_decrement
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
(brace
op_star
id|s
op_increment
op_assign
id|temp
(braket
id|i
op_decrement
)braket
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * convert a number to hex ASCII&n; */
r_static
DECL|function|do_hex
r_void
id|do_hex
c_func
(paren
r_char
op_star
id|temp
comma
r_int
r_int
id|value
comma
r_char
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_char
op_star
id|dec_to_hex
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
id|temp
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
(braket
id|i
)braket
op_assign
id|dec_to_hex
(braket
id|value
op_amp
l_int|0x0f
)braket
suffix:semicolon
id|value
op_rshift_assign
l_int|4
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|8
suffix:semicolon
id|temp
(braket
id|i
)braket
op_eq
l_char|&squot;0&squot;
suffix:semicolon
id|i
op_decrement
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ge
l_int|0
)paren
(brace
op_star
id|s
op_increment
op_assign
id|temp
(braket
id|i
op_decrement
)braket
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * convert a buffer to ASCII HEX&n; */
r_static
DECL|function|do_buffer
r_void
id|do_buffer
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_char
op_star
id|s
)paren
(brace
r_static
r_char
id|hex_char
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_char
op_star
id|b
op_assign
id|buffer
suffix:semicolon
r_int
id|hex_byte
suffix:semicolon
r_int
id|nybble
suffix:semicolon
id|length
op_assign
(paren
id|length
op_ge
(paren
(paren
id|MAX_BUFF
op_div
l_int|3
)paren
op_plus
l_int|1
)paren
)paren
ques
c_cond
(paren
id|MAX_BUFF
op_div
l_int|3
)paren
suffix:colon
id|length
suffix:semicolon
r_while
c_loop
(paren
id|length
)paren
(brace
id|hex_byte
op_assign
(paren
r_int
)paren
op_star
id|b
op_increment
suffix:semicolon
id|nybble
op_assign
(paren
id|hex_byte
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
op_star
id|s
op_increment
op_assign
id|hex_char
(braket
id|nybble
)braket
suffix:semicolon
id|nybble
op_assign
id|hex_byte
op_amp
l_int|0xf
suffix:semicolon
op_star
id|s
op_increment
op_assign
id|hex_char
(braket
id|nybble
)braket
suffix:semicolon
op_star
id|s
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Body of sprintf function: behaves just like standard sprintf, except we&n; * have an extra argument (buffer size) which we use to ensure we don&squot;t&n; * overflow&n; */
DECL|function|Divas_vsprintf
r_void
id|Divas_vsprintf
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|size
comma
r_char
op_star
id|fmt
comma
id|va_list
id|argptr
)paren
(brace
r_char
id|c
suffix:semicolon
multiline_comment|/* single character buffer */
r_int
id|i
suffix:semicolon
multiline_comment|/* handy scratch counter */
r_int
id|f
suffix:semicolon
multiline_comment|/* format character (after %) */
r_char
op_star
id|str
suffix:semicolon
multiline_comment|/* pointer into string */
r_char
id|temp
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* temp buffer used in printing numbers */
r_char
id|string
(braket
id|MAX_BUFF
)braket
suffix:semicolon
multiline_comment|/* output from number conversion */
r_int
id|length
suffix:semicolon
multiline_comment|/* length of string &quot;str&quot; */
r_char
id|fill
suffix:semicolon
multiline_comment|/* fill character &squot; &squot; or &squot;0&squot; */
id|boolean_t
id|leftjust
suffix:semicolon
multiline_comment|/* TRUE if left justified, else right justified */
r_int
id|fmax
comma
id|fmin
suffix:semicolon
multiline_comment|/* field specifiers % MIN . MAX s */
r_int
id|leading
suffix:semicolon
multiline_comment|/* number of leading/trailing fill characters */
r_char
id|sign
suffix:semicolon
multiline_comment|/* set to &squot;-&squot; for negative decimals */
r_int
id|number
suffix:semicolon
multiline_comment|/* numeric argument */
r_char
op_star
id|buff_ptr
suffix:semicolon
multiline_comment|/* pointer to user&squot;s buffer of hex data */
r_int
id|buff_len
suffix:semicolon
multiline_comment|/* length of hex data */
multiline_comment|/* make sure we have somthing to write into */
r_if
c_cond
(paren
(paren
op_logical_neg
id|buffer
)paren
op_logical_or
(paren
id|size
op_le
l_int|0
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|TRUE
)paren
(brace
multiline_comment|/* echo characters until end or &squot;%&squot; encountered */
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|fmt
op_increment
)paren
op_ne
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
op_star
id|buffer
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
suffix:semicolon
)brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/* echo %% as % */
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;%&squot;
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
op_star
id|fmt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* %- turns on left-justify */
r_if
c_cond
(paren
(paren
id|leftjust
op_assign
(paren
id|boolean_t
)paren
(paren
(paren
op_star
id|fmt
op_eq
l_char|&squot;-&squot;
)paren
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
)paren
)paren
)paren
(brace
id|fmt
op_increment
suffix:semicolon
)brace
multiline_comment|/* %0 turns on zero filling */
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|fill
op_assign
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|fill
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
multiline_comment|/* minium field width specifier for %d, u, x, c, s */
id|fmin
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;*&squot;
)paren
(brace
id|fmin
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|fmt
op_increment
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
l_char|&squot;0&squot;
op_le
op_star
id|fmt
op_logical_and
op_star
id|fmt
op_le
l_char|&squot;9&squot;
)paren
(brace
id|fmin
op_assign
(paren
id|fmin
op_star
l_int|10
)paren
op_plus
(paren
op_star
id|fmt
op_increment
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* maximum string width specifier for %s */
id|fmax
op_assign
l_int|0
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
r_if
c_cond
(paren
op_star
(paren
op_increment
id|fmt
)paren
op_eq
l_char|&squot;*&squot;
)paren
(brace
id|fmax
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|fmt
op_increment
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
l_char|&squot;0&squot;
op_le
op_star
id|fmt
op_logical_and
op_star
id|fmt
op_le
l_char|&squot;9&squot;
)paren
(brace
id|fmax
op_assign
(paren
id|fmax
op_star
l_int|10
)paren
op_plus
(paren
op_star
id|fmt
op_increment
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* skip over &squot;l&squot; option (ints are assumed same size as longs) */
r_if
c_cond
(paren
op_star
id|fmt
op_eq
l_char|&squot;l&squot;
)paren
(brace
id|fmt
op_increment
suffix:semicolon
)brace
multiline_comment|/* get the format chacater */
r_if
c_cond
(paren
op_logical_neg
(paren
id|f
op_assign
op_star
id|fmt
op_increment
)paren
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
op_star
id|buffer
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sign
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* sign == &squot;-&squot; for negative decimal */
id|str
op_assign
id|string
suffix:semicolon
r_switch
c_cond
(paren
id|f
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
id|string
(braket
l_int|0
)braket
op_assign
(paren
r_char
)paren
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|string
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
id|fill
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|str
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_char
op_star
)paren
suffix:semicolon
id|fill
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;d&squot;
suffix:colon
id|number
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|number
OL
l_int|0
)paren
(brace
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|number
op_assign
op_minus
id|number
suffix:semicolon
)brace
id|do_decimal
c_func
(paren
id|temp
comma
id|DIM
c_func
(paren
id|temp
)paren
comma
(paren
r_int
r_int
)paren
id|number
comma
id|str
)paren
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;U&squot;
suffix:colon
r_case
l_char|&squot;u&squot;
suffix:colon
id|number
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|do_decimal
c_func
(paren
id|temp
comma
id|DIM
c_func
(paren
id|temp
)paren
comma
(paren
r_int
r_int
)paren
id|number
comma
id|str
)paren
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;O&squot;
suffix:colon
r_case
l_char|&squot;o&squot;
suffix:colon
id|number
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|do_octal
c_func
(paren
id|temp
comma
(paren
r_int
r_int
)paren
id|number
comma
id|str
)paren
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;X&squot;
suffix:colon
r_case
l_char|&squot;x&squot;
suffix:colon
id|number
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|do_hex
c_func
(paren
id|temp
comma
(paren
r_int
r_int
)paren
id|number
comma
id|str
)paren
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;H&squot;
suffix:colon
r_case
l_char|&squot;h&squot;
suffix:colon
id|buff_ptr
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_char
op_star
)paren
suffix:semicolon
id|buff_len
op_assign
id|va_arg
c_func
(paren
id|argptr
comma
r_int
)paren
suffix:semicolon
id|do_buffer
c_func
(paren
id|buff_ptr
comma
id|buff_len
comma
id|str
)paren
suffix:semicolon
id|fmax
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
(paren
(paren
r_char
)paren
id|f
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* get the length of the string */
id|length
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|str
(braket
id|length
)braket
)paren
(brace
id|length
op_increment
suffix:semicolon
)brace
multiline_comment|/* make sure we have fmax and fmin values that are O.K. */
r_if
c_cond
(paren
id|fmin
OG
id|DIM
c_func
(paren
id|string
)paren
op_logical_or
id|fmin
OL
l_int|0
)paren
(brace
id|fmin
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fmax
OG
id|DIM
c_func
(paren
id|string
)paren
op_logical_or
id|fmax
OL
l_int|0
)paren
(brace
id|fmax
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* figure out how many leading characters thare are */
id|leading
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fmax
op_logical_or
id|fmin
)paren
(brace
r_if
c_cond
(paren
id|fmax
)paren
(brace
r_if
c_cond
(paren
id|length
OG
id|fmax
)paren
(brace
id|length
op_assign
id|fmax
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fmin
)paren
(brace
id|leading
op_assign
id|fmin
op_minus
id|length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sign
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|leading
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/* output sign now, if fill is numeric */
r_if
c_cond
(paren
id|sign
op_eq
l_char|&squot;-&squot;
op_logical_and
id|fill
op_eq
l_char|&squot;0&squot;
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* if right justified, output fill characters */
r_if
c_cond
(paren
op_logical_neg
id|leftjust
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|leading
suffix:semicolon
id|i
op_increment
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
id|fill
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* output sign now, if fill is spaces */
r_if
c_cond
(paren
id|sign
op_eq
l_char|&squot;-&squot;
op_logical_and
id|fill
op_eq
l_char|&squot; &squot;
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* now the actual value */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
id|str
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* if left justified, fill out with the fill character */
r_if
c_cond
(paren
id|leftjust
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|leading
suffix:semicolon
id|i
op_increment
)paren
(brace
id|WRITE_CHAR
c_func
(paren
id|buffer
comma
id|size
comma
id|fill
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; * sprintf for kernel&n; *&n; * call our vsprintf assuming user has a big buffer....&n; */
DECL|function|DivasSprintf
r_void
id|DivasSprintf
c_func
(paren
r_char
op_star
id|buffer
comma
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
id|argptr
suffix:semicolon
multiline_comment|/* pointer to additional args */
id|va_start
c_func
(paren
id|argptr
comma
id|fmt
)paren
suffix:semicolon
id|Divas_vsprintf
c_func
(paren
id|buffer
comma
l_int|1024
comma
id|fmt
comma
id|argptr
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|argptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|DivasPrintf
r_void
id|DivasPrintf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|klog_t
id|log
suffix:semicolon
multiline_comment|/* log entry buffer */
id|va_list
id|argptr
suffix:semicolon
multiline_comment|/* pointer to additional args */
id|va_start
c_func
(paren
id|argptr
comma
id|fmt
)paren
suffix:semicolon
multiline_comment|/* clear log entry */
id|bzero
c_func
(paren
(paren
id|caddr_t
)paren
op_amp
id|log
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
id|log.card
op_assign
op_minus
l_int|1
suffix:semicolon
id|log.type
op_assign
id|KLOG_TEXT_MSG
suffix:semicolon
multiline_comment|/* time stamp the entry */
id|log.time_stamp
op_assign
id|UxTimeGet
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* call vsprintf to format the user&squot;s information */
id|Divas_vsprintf
c_func
(paren
id|log.buffer
comma
id|DIM
c_func
(paren
id|log.buffer
)paren
comma
id|fmt
comma
id|argptr
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|argptr
)paren
suffix:semicolon
multiline_comment|/* send to the log streams driver and return */
id|DivasLogAdd
c_func
(paren
op_amp
id|log
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
