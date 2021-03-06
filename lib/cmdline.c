multiline_comment|/*&n; * linux/lib/cmdline.c&n; * Helper functions generally used for parsing kernel command line&n; * and module options.&n; *&n; * Code and copyrights come from init/main.c and arch/i386/kernel/setup.c.&n; *&n; * This source code is licensed under the GNU General Public License,&n; * Version 2.  See the file COPYING for more details.&n; *&n; * GNU Indent formatting options for this file: -kr -i8 -npsl -pcs&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/**&n; *&t;get_option - Parse integer from an option string&n; *&t;@str: option string&n; *&t;@pint: (output) integer value parsed from @str&n; *&n; *&t;Read an int from an option string; if available accept a subsequent&n; *&t;comma as well.&n; *&n; *&t;Return values:&n; *&t;0 : no int in string&n; *&t;1 : int found, no subsequent comma&n; *&t;2 : int found including a subsequent comma&n; */
DECL|function|get_option
r_int
id|get_option
(paren
r_char
op_star
op_star
id|str
comma
r_int
op_star
id|pint
)paren
(brace
r_char
op_star
id|cur
op_assign
op_star
id|str
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cur
op_logical_or
op_logical_neg
(paren
op_star
id|cur
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|pint
op_assign
id|simple_strtol
(paren
id|cur
comma
id|str
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur
op_eq
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|str
op_eq
l_char|&squot;,&squot;
)paren
(brace
(paren
op_star
id|str
)paren
op_increment
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_options - Parse a string into a list of integers&n; *&t;@str: String to be parsed&n; *&t;@nints: size of integer array&n; *&t;@ints: integer array&n; *&n; *&t;This function parses a string containing a comma-separated&n; *&t;list of integers.  The parse halts when the array is&n; *&t;full, or when no more numbers can be retrieved from the&n; *&t;string.&n; *&n; *&t;Return value is the character in the string which caused&n; *&t;the parse to end (typically a null terminator, if @str is&n; *&t;completely parseable).&n; */
DECL|function|get_options
r_char
op_star
id|get_options
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|nints
comma
r_int
op_star
id|ints
)paren
(brace
r_int
id|res
comma
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|nints
)paren
(brace
id|res
op_assign
id|get_option
(paren
(paren
r_char
op_star
op_star
)paren
op_amp
id|str
comma
id|ints
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|1
)paren
r_break
suffix:semicolon
)brace
id|ints
(braket
l_int|0
)braket
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|str
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;memparse - parse a string with mem suffixes into a number&n; *&t;@ptr: Where parse begins&n; *&t;@retptr: (output) Pointer to next char after parse completes&n; *&n; *&t;Parses a string into a number.  The number stored at @ptr is&n; *&t;potentially suffixed with %K (for kilobytes, or 1024 bytes),&n; *&t;%M (for megabytes, or 1048576 bytes), or %G (for gigabytes, or&n; *&t;1073741824).  If the number is suffixed with K, M, or G, then&n; *&t;the return value is the number multiplied by one kilobyte, one&n; *&t;megabyte, or one gigabyte, respectively.&n; */
DECL|function|memparse
r_int
r_int
r_int
id|memparse
(paren
r_char
op_star
id|ptr
comma
r_char
op_star
op_star
id|retptr
)paren
(brace
r_int
r_int
r_int
id|ret
op_assign
id|simple_strtoull
(paren
id|ptr
comma
id|retptr
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
op_star
op_star
id|retptr
)paren
(brace
r_case
l_char|&squot;G&squot;
suffix:colon
r_case
l_char|&squot;g&squot;
suffix:colon
id|ret
op_lshift_assign
l_int|10
suffix:semicolon
r_case
l_char|&squot;M&squot;
suffix:colon
r_case
l_char|&squot;m&squot;
suffix:colon
id|ret
op_lshift_assign
l_int|10
suffix:semicolon
r_case
l_char|&squot;K&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
id|ret
op_lshift_assign
l_int|10
suffix:semicolon
(paren
op_star
id|retptr
)paren
op_increment
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|memparse
id|EXPORT_SYMBOL
c_func
(paren
id|memparse
)paren
suffix:semicolon
DECL|variable|get_option
id|EXPORT_SYMBOL
c_func
(paren
id|get_option
)paren
suffix:semicolon
DECL|variable|get_options
id|EXPORT_SYMBOL
c_func
(paren
id|get_options
)paren
suffix:semicolon
eof
