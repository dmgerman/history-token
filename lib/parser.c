multiline_comment|/*&n; * lib/parser.c - simple parser for mount, etc. options.&n; *&n; * This source code is licensed under the GNU General Public License,&n; * Version 2.  See the file COPYING for more details.&n; */
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/parser.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|function|match_one
r_static
r_int
id|match_one
c_func
(paren
r_char
op_star
id|s
comma
r_char
op_star
id|p
comma
id|substring_t
id|args
(braket
)braket
)paren
(brace
r_char
op_star
id|meta
suffix:semicolon
r_int
id|argc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|len
op_assign
op_minus
l_int|1
suffix:semicolon
id|meta
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|meta
)paren
r_return
id|strcmp
c_func
(paren
id|p
comma
id|s
)paren
op_eq
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|p
comma
id|s
comma
id|meta
op_minus
id|p
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|s
op_add_assign
id|meta
op_minus
id|p
suffix:semicolon
id|p
op_assign
id|meta
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|p
)paren
)paren
id|len
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|s
op_increment
op_ne
l_char|&squot;%&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ge
id|MAX_OPT_ARGS
)paren
r_return
l_int|0
suffix:semicolon
id|args
(braket
id|argc
)braket
dot
id|from
op_assign
id|s
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|p
op_increment
)paren
(brace
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|s
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
op_logical_or
id|len
OG
id|strlen
c_func
(paren
id|s
)paren
)paren
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
id|args
(braket
id|argc
)braket
dot
id|to
op_assign
id|s
op_plus
id|len
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
id|simple_strtol
c_func
(paren
id|s
comma
op_amp
id|args
(braket
id|argc
)braket
dot
id|to
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|num
suffix:semicolon
r_case
l_char|&squot;u&squot;
suffix:colon
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|args
(braket
id|argc
)braket
dot
id|to
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|num
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|args
(braket
id|argc
)braket
dot
id|to
comma
l_int|8
)paren
suffix:semicolon
r_goto
id|num
suffix:semicolon
r_case
l_char|&squot;x&squot;
suffix:colon
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|args
(braket
id|argc
)braket
dot
id|to
comma
l_int|16
)paren
suffix:semicolon
id|num
suffix:colon
r_if
c_cond
(paren
id|args
(braket
id|argc
)braket
dot
id|to
op_eq
id|args
(braket
id|argc
)braket
dot
id|from
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|s
op_assign
id|args
(braket
id|argc
)braket
dot
id|to
suffix:semicolon
id|argc
op_increment
suffix:semicolon
)brace
)brace
DECL|function|match_token
r_int
id|match_token
c_func
(paren
r_char
op_star
id|s
comma
id|match_table_t
id|table
comma
id|substring_t
id|args
(braket
)braket
)paren
(brace
r_struct
id|match_token
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|table
suffix:semicolon
op_logical_neg
id|match_one
c_func
(paren
id|s
comma
id|p-&gt;pattern
comma
id|args
)paren
suffix:semicolon
id|p
op_increment
)paren
suffix:semicolon
r_return
id|p-&gt;token
suffix:semicolon
)brace
DECL|function|match_number
r_static
r_int
id|match_number
c_func
(paren
id|substring_t
op_star
id|s
comma
r_int
op_star
id|result
comma
r_int
id|base
)paren
(brace
r_char
op_star
id|endp
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|s-&gt;to
op_minus
id|s-&gt;from
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|s-&gt;from
comma
id|s-&gt;to
op_minus
id|s-&gt;from
)paren
suffix:semicolon
id|buf
(braket
id|s-&gt;to
op_minus
id|s-&gt;from
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|result
op_assign
id|simple_strtol
c_func
(paren
id|buf
comma
op_amp
id|endp
comma
id|base
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|endp
op_eq
id|buf
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|match_int
r_int
id|match_int
c_func
(paren
id|substring_t
op_star
id|s
comma
r_int
op_star
id|result
)paren
(brace
r_return
id|match_number
c_func
(paren
id|s
comma
id|result
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|match_octal
r_int
id|match_octal
c_func
(paren
id|substring_t
op_star
id|s
comma
r_int
op_star
id|result
)paren
(brace
r_return
id|match_number
c_func
(paren
id|s
comma
id|result
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|match_hex
r_int
id|match_hex
c_func
(paren
id|substring_t
op_star
id|s
comma
r_int
op_star
id|result
)paren
(brace
r_return
id|match_number
c_func
(paren
id|s
comma
id|result
comma
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|match_strcpy
r_void
id|match_strcpy
c_func
(paren
r_char
op_star
id|to
comma
id|substring_t
op_star
id|s
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
id|s-&gt;from
comma
id|s-&gt;to
op_minus
id|s-&gt;from
)paren
suffix:semicolon
id|to
(braket
id|s-&gt;to
op_minus
id|s-&gt;from
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|match_strdup
r_char
op_star
id|match_strdup
c_func
(paren
id|substring_t
op_star
id|s
)paren
(brace
r_char
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
id|s-&gt;to
op_minus
id|s-&gt;from
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|match_strcpy
c_func
(paren
id|p
comma
id|s
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|variable|match_token
id|EXPORT_SYMBOL
c_func
(paren
id|match_token
)paren
suffix:semicolon
DECL|variable|match_int
id|EXPORT_SYMBOL
c_func
(paren
id|match_int
)paren
suffix:semicolon
DECL|variable|match_octal
id|EXPORT_SYMBOL
c_func
(paren
id|match_octal
)paren
suffix:semicolon
DECL|variable|match_hex
id|EXPORT_SYMBOL
c_func
(paren
id|match_hex
)paren
suffix:semicolon
DECL|variable|match_strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|match_strcpy
)paren
suffix:semicolon
DECL|variable|match_strdup
id|EXPORT_SYMBOL
c_func
(paren
id|match_strdup
)paren
suffix:semicolon
eof
